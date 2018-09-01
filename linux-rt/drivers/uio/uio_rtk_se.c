/*
 * Copyright (C) 2015-2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/uio_driver.h>
#include <linux/pm_runtime.h>

#include "reg_se.h"
#include "uio_rtk_se.h"
#include "uio_helper.h"

struct se_uio_info {
	struct uio_info info;
	struct device *dev;
	void __iomem *base;
	struct clk *clk;
	int irq;
	int suspend;
	int should_resume;
};

static SEREG_INFO se_reg;

enum {
	SeClearWriteData = 0,
	SeWriteData = BIT(0),
	SeGo = BIT(1),
	SeEndianSwap = BIT(2),
};

static inline void rtk_se_init_reg(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);
	struct uio_info *info = &priv->info;
	struct se_hw *se_hw = info->mem[1].internal_addr;
	int i;
	SEREG_INFO *reg_info = (SEREG_INFO *)priv->base;

	for (i = 0; i < SE_NUM_ENGINES; i++) {
		/* Stop Streaming Engine */
		reg_info->SeCtrl[i].Value = (SeGo | SeClearWriteData);
		reg_info->SeCtrl[i].Value = (SeWriteData);
		reg_info->SeCmdBase[i].Value = se_hw->engine[i].CmdBase;
		reg_info->SeCmdReadPtr[i].Value = se_hw->engine[i].CmdBase;
		reg_info->SeCmdWritePtr[i].Value = se_hw->engine[i].CmdBase;
		reg_info->SeCmdLimit[i].Value = se_hw->engine[i].CmdLimit;
		reg_info->SeInstCntL[i].Value = 0;
		reg_info->SeInstCntH[i].Value = 0;

		dev_info(dev,
			"[SE] Engine[%d] Ctrl:%08x Base:%08x ReadPtr:%08x WritePtr:%08x Limit:%08x\n",
			i,
			reg_info->SeCtrl[i].Value,
			reg_info->SeCmdBase[i].Value,
			reg_info->SeCmdReadPtr[i].Value,
			reg_info->SeCmdWritePtr[i].Value,
			reg_info->SeCmdLimit[i].Value);

		se_hw->engine[i].CmdWritePtr = se_hw->engine[i].CmdBase;
	}
}

static inline void rtk_se_enable_icg(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);
	unsigned int val;

	val = readl(priv->base + 0x80c);
	val &= ~0xf8000000;
	writel(val, priv->base + 0x80c);
}

static void rtk_se_init_drv(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);
	struct uio_info *info = &priv->info;
	struct se_hw *se_hw = info->mem[1].internal_addr;
	void *virt = info->mem[2].internal_addr;
	dma_addr_t phys = info->mem[2].addr;
	int i;

	for (i = 0 ; i < SE_NUM_ENGINES ; i++) {
		struct se_engine *eng = &se_hw->engine[i];

		eng->CmdBuf   = (unsigned long)virt + SE_CMDBUF_SIZE * i;
		eng->CmdBase  = phys + SE_CMDBUF_SIZE * i;
		eng->CmdLimit = eng->CmdBase + SE_CMDBUF_SIZE;
		eng->BufSize  = SE_CMDBUF_SIZE;
	}

	rtk_se_init_reg(dev);
	rtk_se_enable_icg(dev);
}

static irqreturn_t rtk_se_irq_handler(int irq, struct uio_info *info)
{
	struct se_uio_info *priv = container_of(info, struct se_uio_info, info);
	SEREG_INFO *reg_info = (SEREG_INFO *)priv->base;
	int i;

	pr_debug("[SE] interrupt...\n");

	for (i = 0 ; i < SE_NUM_ENGINES ; i++) {
		if (reg_info->SeInte[i].Fields.com_empty &&
			reg_info->SeInts[i].Fields.com_empty) {

			pr_debug("[SE] smq empty interrupt...\n");
			reg_info->SeInte[i].Value = 0x8;
#if 0
			if ((reg_info->SeCtrl[i].Value & 0x2) &&
				((reg_info->SeIdle[i].Value & 0x1) == 0)) {
				//dbg_info("%s se is not idle", DEV_NAME);
			}
#endif
		}
	}

	return IRQ_HANDLED;
}

static int rtk_se_save_reg(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);
	int i;
	uint8_t *regbak = (uint8_t *)&se_reg;
	uint8_t *reghw = (uint8_t *)priv->base;

	dev_info(dev, "[SE] Enter %s\n", __func__);

	for (i = 0; i < sizeof(SEREG_INFO); i += 4) {
		/* skip reserved registers to avoid sb2 timeout issue */
		if (i >= 0x64 && i < 0x70)
			continue; /* Reserved */
		if (i >= 0xF4 && i < 0x128)
			continue; /* Reserved */
		if (i >= 0x440 && i < 0x458)
			continue; /* Reserved */
		if (i >= 0x4CC && i < 0x4E0)
			continue; /* Reserved */
		if (i >= 0x504 && i < 0x510)
			continue; /* Reserved */

		dev_dbg(dev, "offset=%03x val=%08x to mem", i, *(uint32_t *)(reghw + i));
		*(uint32_t *)(regbak + i) = *(uint32_t *)(reghw + i);
	}

	dev_info(dev, "[SE] Exit %s\n", __func__);
	priv->suspend = 1;

	return 0;
}

static int rtk_se_restore_reg(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);
	uint8_t *regbak = (uint8_t *)&se_reg;
	uint8_t *reghw = (uint8_t *)priv->base;
	int i;
	SEREG_INFO *reg_info = (SEREG_INFO *)priv->base;

	dev_info(dev, "[SE] Enter %s\n", __func__);

	for (i = 0; i < sizeof(SEREG_INFO); i += 4) {
		/* skip restoring reserved, read-only, special registers */
		if (i >= 0x30 && i < 0x3C)
			continue; /* SRWORDCNT */
		if (i >= 0x40 && i < 0x4C)
			continue; /* CLR_FMT */
		if (i >= 0x64 && i < 0x70)
			continue; /* Reserved */
		if (i >= 0xF4 && i < 0x128)
			continue; /* Reserved */
		if (i >= 0x440 && i < 0x458)
			continue; /* Reserved */
		if (i >= 0x458 && i < 0x464)
			continue; /* CTRL */
		if (i >= 0x474 && i < 0x480)
			continue; /* INTS */
		if (i >= 0x48C && i < 0x498)
			continue; /* INSTCNT */
		if (i == 0x4C8)
			continue; /* CLUT_LOCK_ST */
		if (i >= 0x4CC && i < 0x4E0)
			continue; /* Reserved */
		if (i >= 0x4F8 && i < 0x504)
			continue; /* SYNC_VO_LOCATION */
		if (i >= 0x504 && i < 0x510)
			continue; /* Reserved */
		if (i >= 0x510 && i < 0x51C)
			continue; /* INSTCNT_H */

		dev_dbg(dev, "offset=%03x val=%08x to reg", i, *(uint32_t *)(regbak + i));
		*(uint32_t *)(reghw + i) = *(uint32_t *)(regbak + i);
	}

	se_reg.SeColorFormat[0].Fields.write_enable1 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable2 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable5 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable6 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable7 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable8 = 1;
	se_reg.SeColorFormat[0].Fields.write_enable10 = 1;
	reg_info->SeColorFormat[0].Value = se_reg.SeColorFormat[0].Value;
	se_reg.SeColorFormat[1].Fields.write_enable1 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable2 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable5 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable6 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable7 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable8 = 1;
	se_reg.SeColorFormat[1].Fields.write_enable10 = 1;
	reg_info->SeColorFormat[1].Value = se_reg.SeColorFormat[1].Value;
	se_reg.SeColorFormat[2].Fields.write_enable1 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable2 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable5 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable6 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable7 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable8 = 1;
	se_reg.SeColorFormat[2].Fields.write_enable10 = 1;
	reg_info->SeColorFormat[2].Value = se_reg.SeColorFormat[2].Value;

	/* clear interrupt status? */
	reg_info->SeInts[0].Value = se_reg.SeInts[0].Value;
	reg_info->SeInts[1].Value = se_reg.SeInts[1].Value;
	reg_info->SeInts[2].Value = se_reg.SeInts[2].Value;

	/* restore the go bit? */
	reg_info->SeCtrl[0].Value = se_reg.SeCtrl[0].Value;
	reg_info->SeCtrl[1].Value = se_reg.SeCtrl[1].Value;
	reg_info->SeCtrl[2].Value = se_reg.SeCtrl[2].Value;

	dev_info(dev, "[SE] Exit %s\n", __func__);
	priv->suspend = 0;

	return 0;
}

static int rtk_se_runtime_suspend(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	rtk_se_save_reg(dev);
	clk_disable_unprepare(priv->clk);
	return 0;
}

static int rtk_se_runtime_resume(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	clk_prepare_enable(priv->clk);
	rtk_se_restore_reg(dev);
	return 0;
}

static int rtk_se_suspend(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	if (priv->suspend)
		return 0;

	rtk_se_runtime_suspend(dev);
	priv->should_resume = 1;

	return 0;
}

static int rtk_se_resume(struct device *dev)
{
	struct se_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	if (priv->should_resume)
		rtk_se_runtime_resume(dev);
	priv->should_resume = 0;

	return 0;
}


static const struct dev_pm_ops rtk_se_pm_ops = {
	SET_RUNTIME_PM_OPS(rtk_se_runtime_suspend, rtk_se_runtime_resume, NULL)
	SET_SYSTEM_SLEEP_PM_OPS(rtk_se_suspend, rtk_se_resume)
};

static int rtk_se_open(struct uio_info *info, struct inode *inode)
{
	struct se_uio_info *priv = info->priv;

	pm_runtime_get_sync(priv->dev);
	return 0;
}

static int rtk_se_release(struct uio_info *info, struct inode *inode)
{
	struct se_uio_info *priv = info->priv;

	pm_runtime_put_sync(priv->dev);
	return 0;
}

static int rtk_se_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct se_uio_info *priv;
	struct uio_info *info;
	int ret;

	dev_info(dev, "%s\n", __func__);

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_warn(dev, "clk_get() returns %ld\n", PTR_ERR(priv->clk));
		priv->clk = NULL;
	}

	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_err(dev, "platform_get_irq() returns %d\n", ret);
		return ret;
	}
	priv->irq = ret;
	priv->dev = dev;

	info = &priv->info;
	info->mem[0].name = "SE reg space";
	ret = uio_mem_of_iomap(dev, &info->mem[0], 0);
	if (ret) {
		dev_err(dev, "mem0: uio_mem_of_iomap() returns %d\n", ret);
		goto free_uio_mem;
	}
	priv->base = info->mem[0].internal_addr;

	info->mem[1].name = "SE driver data";
	ret = uio_mem_dma_alloc(dev, &info->mem[1], sizeof(struct se_hw),
		GFP_KERNEL);
	if (ret) {
		dev_err(dev, "mem1: uio_mem_dma_alloc() returns %d\n", ret);
		goto free_uio_mem;
	}

	info->mem[2].name = "SE command queue";
	ret = uio_mem_dma_alloc(dev, &info->mem[2],
		SE_CMDBUF_SIZE * SE_NUM_ENGINES, GFP_KERNEL | GFP_DMA);
	if (ret) {
		dev_err(dev, "mem2: uio_mem_dma_alloc() returns %d\n", ret);
		goto free_uio_mem;
	}

	dev_info(dev, "irq=%d\n", priv->irq);
	uio_mem_print(dev, &info->mem[0]);
	uio_mem_print(dev, &info->mem[1]);
	uio_mem_print(dev, &info->mem[2]);

#ifdef CONFIG_UIO_ASSIGN_MINOR
	info->minor = 251;
#endif
	info->version = "0.0.1";
	info->name = "RTK-SE";
	info->irq = priv->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = rtk_se_irq_handler;
	info->open = rtk_se_open;
	info->release = rtk_se_release;
	info->priv = priv;

	ret = uio_register_device(dev, info);
	if (ret) {
		dev_err(dev, "uio_register_device() returns %d\n", ret);
		goto free_uio_mem;
	}

	ret = uio_reset_control_deassert(dev, NULL);
	if (ret)
		dev_warn(dev, "uio_reset_control_deassert() returns %d\n", ret);

	platform_set_drvdata(pdev, priv);

	/* enable runtime pm */
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	/* do resume */
	clk_prepare_enable(priv->clk);
	priv->suspend = 0;
	pm_runtime_get_noresume(dev);

	/* init se */
	rtk_se_init_drv(dev);
	pm_runtime_put_sync(dev);

	return 0;

free_uio_mem:
	uio_mem_dma_free(dev, &info->mem[2]);
	uio_mem_dma_free(dev, &info->mem[1]);
	uio_mem_iounmap(dev, &info->mem[0]);

	return ret;
}

static int rtk_se_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct se_uio_info *priv = platform_get_drvdata(pdev);
	struct uio_info *info = &priv->info;

	dev_info(dev, "%s\n", __func__);
	pm_runtime_disable(dev);
	uio_reset_control_assert(dev, NULL);
	platform_set_drvdata(pdev, NULL);
	uio_unregister_device(info);
	uio_mem_dma_free(dev, &info->mem[2]);
	uio_mem_dma_free(dev, &info->mem[1]);
	uio_mem_iounmap(dev, &info->mem[0]);
	return 0;
}


static const struct of_device_id rtk_se_ids[] = {
	{ .compatible = "realtek,se" },
	{}
};

static struct platform_driver rtk_se_driver = {
	.probe = rtk_se_probe,
	.remove = rtk_se_remove,
	.driver = {
		.name = "rtk-se",
		.owner = THIS_MODULE,
		.of_match_table = rtk_se_ids,
		.pm = &rtk_se_pm_ops,
	},
};
module_platform_driver_probe(rtk_se_driver, rtk_se_probe);
