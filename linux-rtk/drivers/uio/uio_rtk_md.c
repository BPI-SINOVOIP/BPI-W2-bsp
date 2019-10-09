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
#include "reg_md.h"
#include "uio_rtk_md.h"
#include "uio_helper.h"

struct md_uio_info {
	struct uio_info info;
	struct device *dev;
	void __iomem *base;
	struct clk *clk;
	int irq;
};

enum {
	MdClearWriteData = 0,
	MdWriteData = BIT(0),
	MdGo = BIT(1),
	MdEndianSwap = BIT(2),
};

static inline void rtk_md_init_reg(struct device *dev)
{
	struct md_uio_info *priv = dev_get_drvdata(dev);
	struct uio_info *info = &priv->info;
	struct md_hw *md_hw = info->mem[1].internal_addr;
	int i;

	 MDREG_INFO *reg_info = (MDREG_INFO *)priv->base;

	for (i = 0 ; i < MD_NUM_ENGINES ; i++) {
		/* Stop Moving Data */
		reg_info->MdCtrl[i].Value =
			(MdGo | MdEndianSwap | MdClearWriteData);
		reg_info->MdCtrl[i].Value = (MdEndianSwap | MdWriteData);
		reg_info->MdCmdBase[i].Value = md_hw->engine[i].CmdBase;
		reg_info->MdCmdReadPtr[i].Value = md_hw->engine[i].CmdBase;
		reg_info->MdCmdWritePtr[i].Value = md_hw->engine[i].CmdBase;
		reg_info->MdCmdLimit[i].Value = md_hw->engine[i].CmdLimit;
		reg_info->MdInstCnt[i].Value = 0;

		dev_info(dev, "[MD] Engine[%d] Ctrl:%08x Base:%08x ReadPtr:%08x WritePtr:%08x Limit:%08x\n",
			i,
			reg_info->MdCtrl[i].Value,
			reg_info->MdCmdBase[i].Value,
			reg_info->MdCmdReadPtr[i].Value,
			reg_info->MdCmdWritePtr[i].Value,
			reg_info->MdCmdLimit[i].Value);

		md_hw->engine[i].CmdWritePtr = md_hw->engine[i].CmdBase;
	}
}

static inline void rtk_md_enable_icg(struct device *dev)
{
	struct md_uio_info *priv = dev_get_drvdata(dev);
	unsigned int val;

	val = readl(priv->base + 0x180);
	val |= 0x0000000f;
	writel(val, priv->base + 0x180);
}

static void rtk_md_init_drv(struct device *dev)
{
	struct md_uio_info *priv = dev_get_drvdata(dev);
	struct uio_info *info = &priv->info;
	struct md_hw *md_hw = info->mem[1].internal_addr;
	int i;
	void *virt = info->mem[2].internal_addr;
	dma_addr_t phys = info->mem[2].addr;

	for (i = 0 ; i < MD_NUM_ENGINES ; i++) {
		struct md_engine *eng = &md_hw->engine[i];

		eng->CmdBuf   = (unsigned long)virt + MD_CMDBUF_SIZE * i;
		eng->CmdBase  = phys + MD_CMDBUF_SIZE * i;
		eng->CmdLimit = eng->CmdBase + MD_CMDBUF_SIZE;
		eng->BufSize  = MD_CMDBUF_SIZE;
	}

	rtk_md_init_reg(dev);
	rtk_md_enable_icg(dev);
}

static irqreturn_t md_irq_handler(int irq, struct uio_info *info)
{
	struct md_uio_info *priv = container_of(info, struct md_uio_info, info);
	int i;
	MDREG_INFO *reg_info = (MDREG_INFO *)priv->base;

	pr_debug("[MD] interrupt...\n");

	for (i = 0 ; i < MD_NUM_ENGINES ; i++) {
		if (reg_info->MdInte[i].Fields.smq_empty_en &&
			reg_info->MdInts[i].Fields.smq_empty) {

			pr_debug("[MD] smq empty interrupt...\n");
			reg_info->MdInte[i].Value = 0x8;
		}
	}

	return IRQ_HANDLED;
}


static inline void print_uio_mem(struct device *dev, struct uio_info *info,
	int index)
{
	struct uio_mem *umem = &info->mem[index];

	dev_info(dev,
		"mem[%d] phys:0x%pa virt:0x%p size:0x%pa type:%d name:%s\n",
		index, &umem->addr, umem->internal_addr, &umem->size,
		umem->memtype, umem->name);
}

static int rtk_md_runtime_suspend(struct device *dev)
{
	struct md_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	clk_disable_unprepare(priv->clk);
	return 0;
}

static int rtk_md_runtime_resume(struct device *dev)
{
	struct md_uio_info *priv = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);
	clk_prepare_enable(priv->clk);
	return 0;
}

static const struct dev_pm_ops rtk_md_pm_ops = {
	SET_RUNTIME_PM_OPS(rtk_md_runtime_suspend, rtk_md_runtime_resume, NULL)
};

static int rtk_md_open(struct uio_info *info, struct inode *inode)
{
	struct md_uio_info *priv = info->priv;

	pm_runtime_get_sync(priv->dev);
	return 0;
}

static int rtk_md_release(struct uio_info *info, struct inode *inode)
{
	struct md_uio_info *priv = info->priv;

	pm_runtime_put_sync(priv->dev);
	return 0;
}

static int rtk_md_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct md_uio_info *priv;
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

	info->mem[0].name = "MD reg space";
	ret = uio_mem_of_iomap(dev, &info->mem[0], 0);
	if (ret) {
		dev_err(dev, "mem0: uio_mem_of_iomap() returns %d\n", ret);
		goto free_uio_mem;
	}
	priv->base = info->mem[0].internal_addr;

	info->mem[1].name = "MD driver data";
	ret = uio_mem_dma_alloc(dev, &info->mem[1], sizeof(struct md_hw),
		GFP_KERNEL);
	if (ret) {
		dev_err(dev, "mem1: uio_mem_dma_alloc() returns %d\n", ret);
		goto free_uio_mem;
	}

	info->mem[2].name = "MD command queue";
	ret = uio_mem_dma_alloc(dev, &info->mem[2],
		MD_CMDBUF_SIZE * MD_NUM_ENGINES, GFP_KERNEL | GFP_DMA);
	if (ret) {
		dev_err(dev, "mem2: uio_mem_dma_alloc() returns %d\n", ret);
		goto free_uio_mem;
	}

	dev_info(dev, "irq=%d\n", priv->irq);
	uio_mem_print(dev, &info->mem[0]);
	uio_mem_print(dev, &info->mem[1]);
	uio_mem_print(dev, &info->mem[2]);

#ifdef CONFIG_UIO_ASSIGN_MINOR
	info->minor = 252;
#endif
	info->version = "0.0.1";
	info->name = "RTK-MD";
	info->irq = priv->irq;
	info->irq_flags = IRQF_SHARED;
	info->handler = md_irq_handler;
	info->open = rtk_md_open;
	info->release = rtk_md_release;
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
	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);

	/* init md */
	pm_runtime_get_sync(dev);
	rtk_md_init_drv(dev);
	pm_runtime_put_sync(dev);

	return 0;

free_uio_mem:
	uio_mem_dma_free(dev, &info->mem[2]);
	uio_mem_dma_free(dev, &info->mem[1]);
	uio_mem_iounmap(dev, &info->mem[0]);

	return ret;
}

static int rtk_md_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct md_uio_info *priv = platform_get_drvdata(pdev);
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

static const struct of_device_id rtk_md_ids[] = {
	{ .compatible = "realtek,md" },
	{}
};

static struct platform_driver rtk_md_driver = {
	.probe = rtk_md_probe,
	.remove = rtk_md_remove,
	.driver = {
		.name = "rtk-md",
		.owner = THIS_MODULE,
		.of_match_table = rtk_md_ids,
		.pm = &rtk_md_pm_ops,
	},
};
module_platform_driver_probe(rtk_md_driver, rtk_md_probe);
