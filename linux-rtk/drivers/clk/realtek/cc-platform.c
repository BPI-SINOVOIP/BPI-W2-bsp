/*
 * cc-platform.c - clock controller platform driver
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "rtk-clk: " fmt

#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/bitops.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_mmio.h>
#include "common.h"

static int rtk_cc_suspend(struct device *dev)
{
	int i;
	struct cc_desc *ccd = dev_get_drvdata(dev);

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		return 0;
#endif
	dev_info(dev, "[CLK] Enter %s\n", __func__);

	for (i = 0; i < cc_clock_num(); i++)
		clk_pm_data_save(&ccd->pm_data[i]);

	dev_info(dev, "[CLK] Exit %s\n", __func__);
	return 0;
}

static int rtk_cc_resume(struct device *dev)
{
	int i;
	struct cc_desc *ccd = dev_get_drvdata(dev);
#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		return 0;
#endif
	dev_info(dev, "[CLK] Enter %s\n", __func__);

	for (i = cc_clock_num() - 1; i >= 0; i--)
		clk_pm_data_restore(&ccd->pm_data[i]);

	dev_info(dev, "[CLK] Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_cc_pm_ops = {
	.suspend_noirq = rtk_cc_suspend,
	.resume_noirq = rtk_cc_resume,
};

static int rtk_cc_probe(struct platform_device *pdev)
{
	struct cc_desc *ccd;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	void __iomem *reg;
	struct regmap *regmap;
	int offset = 0;
	int ret;

	dev_info(dev, "[CLK] %s\n", __func__);

	ccd = devm_cc_alloc(dev, cc_clock_num());
	if (!ccd)
		return -ENOMEM;

	/* register access */
	reg = of_iomap(np, 0);
	regmap = of_get_rtk_mmio_regmap_with_offset(np, 0, &offset);
	if (!reg && IS_ERR_OR_NULL(regmap))
		return -EINVAL;
	if (IS_ERR(regmap))
		regmap = NULL;

	ccd->init_data.flags = CLK_REG_FAST_ACCESS,
	ccd->init_data.private_offset = 0x100,
	ccd->init_data.reg = reg;
	if (regmap) {
		dev_info(dev, "use mmio regmap\n");
		ccd->init_data.offset = offset;
		ccd->init_data.regmap = regmap;
	}

	platform_set_drvdata(pdev, ccd);

	ret = cc_init_clocks(dev);
	if (ret)
		dev_err(dev, "rtk_cc_init_clocks() returns %d\n", ret);

	ret = of_clk_add_provider(np, of_clk_src_onecell_get, &ccd->data);
	if (ret)
		dev_err(dev, "of_clk_add_provider() returns %d\n", ret);

	return 0;
}

static const struct of_device_id rtk_cc_match[] = {
	{.compatible = "realtek,clock-controller"},
	{}
};

static struct platform_driver rtk_cc_driver = {
	.probe = rtk_cc_probe,
	.driver = {
		.name = "rtk-cc",
		.of_match_table = rtk_cc_match,
		.pm = &rtk_cc_pm_ops,
	},
};

static int __init rtk_cc_init(void)
{
	return platform_driver_register(&rtk_cc_driver);
}
core_initcall(rtk_cc_init);
