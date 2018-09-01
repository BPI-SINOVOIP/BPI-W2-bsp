/*
 * SPI driver for DW SPI Core on Realtek RTD139x platform
 *
 * Copyright (c) 2017 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/spi/spi.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/interrupt.h>
#include <linux/suspend.h>
#include <linux/clk.h>
#include <linux/reset.h>
#include <linux/io.h>

#include "spi-dw.h"

#define DRIVER_NAME "dw_spi_rtd139x"
#define SPI_Wra_CTRL 0

struct rtk_spi {
	struct dw_spi dws;

	void __iomem *spi_wrapper;
	struct clk *clk;
	struct reset_control *rstc;
	struct device *dev;
};

static inline struct rtk_spi *rtk_spi_to_hw(struct spi_device *spi)
{
	struct dw_spi *dws = spi_master_get_devdata(spi->master); 
	struct rtk_spi *hw = container_of(dws, struct rtk_spi, dws);

	return hw;
	//return spi_master_get_devdata(sdev->master);
}

void rtk_spi_wrap_ctrl(struct spi_device *spi,  int val)
{
	struct rtk_spi *hw = rtk_spi_to_hw(spi);
	__raw_writel(val, hw->spi_wrapper + SPI_Wra_CTRL);
}
EXPORT_SYMBOL_GPL(rtk_spi_wrap_ctrl);


static int rtk_spi_probe(struct platform_device *pdev)
{
	struct rtk_spi *hw;
	struct dw_spi *dws;
	struct clk *clk = clk_get(&pdev->dev, NULL);
	struct reset_control *rstc = reset_control_get(&pdev->dev, NULL);
	u32 val;
	int err = -ENODEV;

	if (WARN_ON(!(pdev->dev.of_node)))
	{
		pr_err("[SPI] Error: No node\n");
		return err;
	}

	hw = devm_kzalloc(&pdev->dev, sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	dws = &hw->dws;
	/* Enable clk and release reset module */
	reset_control_deassert(rstc);	/* release reset */
	clk_prepare_enable(clk);	/* enable clk */

	dev_set_drvdata(&pdev->dev, hw);

	/* Find and map resources */
	dws->regs = of_iomap(pdev->dev.of_node, 0);
	if (IS_ERR(dws->regs)) {
		dev_err(&pdev->dev, "[SPI] DW SPI region map failed, addr 0x%p\n", dws->regs);
		goto exit;
	}
	hw->spi_wrapper = of_iomap(pdev->dev.of_node, 1);

	if (IS_ERR(dws->regs)) {
		dev_err(&pdev->dev, "[SPI] SPI wrapper region map failed, addr 0x%p\n", hw->spi_wrapper);
		goto exit;
	}

	dws->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (dws->irq < 0) {
		dev_err(&pdev->dev, "[SPI] no irq resource?\n");
		err = -ENXIO;
		goto exit;
	}

	if (!of_property_read_u32(pdev->dev.of_node, "num-chipselect", &val))
		dws->num_cs = val;
	if (!of_property_read_u32(pdev->dev.of_node, "bus-num", &val))
		dws->bus_num = val;
	if (!of_property_read_u32(pdev->dev.of_node, "clock-frequency", &val))
		dws->max_freq = val;

	hw->clk = clk;
	hw->rstc = rstc;
	hw->dev = &pdev->dev;
	/* call setup function */
	err = dw_spi_add_host(&pdev->dev, &hw->dws);
	if (err) {
		pr_err("[SPI] Init failed, ret = %d\n", err);
		goto exit;
	}
	dev_info(&pdev->dev, "[SPI] base 0x%p, irq %d\n", hw->dws.regs, hw->dws.irq);

	return 0;

exit:
	/* Disable clk and reset module */
	reset_control_assert(hw->rstc);	/* reset */
	clk_disable_unprepare(hw->clk);	/* disable clk */
	reset_control_put(rstc);
	dev_set_drvdata(&pdev->dev, NULL);
	return err;
}

static int rtk_spi_remove(struct platform_device *dev)
{
	struct rtk_spi *hw = platform_get_drvdata(dev);
	struct dw_spi *dws = &hw->dws;

	dw_spi_remove_host(dws);

	/* Disable clk and reset module */
	reset_control_assert(hw->rstc);	/* reset */
	clk_disable_unprepare(hw->clk);	/* disable clk */
	reset_control_put(hw->rstc);

	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}


#ifdef CONFIG_PM_SLEEP

static int rtk_spi_suspend(struct device *dev)
{
	struct rtk_spi *hw = dev_get_drvdata(dev);
	struct dw_spi *dws = &hw->dws;
	int ret;

	printk(KERN_ERR "[SPI] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[SPI] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[SPI] %s Suspend mode\n", __func__);
	}

	ret = dw_spi_suspend_host(dws);

	printk(KERN_ERR "[SPI] Exit %s\n", __func__);

	return ret;
}

static int rtk_spi_resume(struct device *dev)
{
	struct rtk_spi *hw = dev_get_drvdata(dev);
	struct dw_spi *dws = &hw->dws;
	int ret;

	printk(KERN_ERR "[SPI] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[SPI] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[SPI] %s Suspend mode\n", __func__);
	}

	ret = dw_spi_resume_host(dws);

	printk(KERN_ERR "[SPI] Exit %s\n", __func__);

	return ret;
}

static SIMPLE_DEV_PM_OPS(rtk_spi_pm_ops, rtk_spi_suspend, rtk_spi_resume);

#define RTK_SPI_PM_OPS	(&rtk_spi_pm_ops)

#else /* CONFIG_PM_SLEEP */
#define RTK_SPI_PM_OPS	NULL
#endif /* CONFIG_PM_SLEEP */


static const struct of_device_id rtk_spi_match[] = {
	{ .compatible = "Realtek,rtk-dw-apb-ssi", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_spi_match);

static struct platform_driver rtk_spi_driver = {
	.probe = rtk_spi_probe,
	.remove = rtk_spi_remove,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.pm = RTK_SPI_PM_OPS,
		.of_match_table = of_match_ptr(rtk_spi_match),
	},
};
module_platform_driver(rtk_spi_driver);

MODULE_AUTHOR("Eric Wang <ericwang@realtek.com>");
MODULE_DESCRIPTION("SPI driver for DW SPI Core on RTK RTD139x platform");
MODULE_LICENSE("GPL v2");
