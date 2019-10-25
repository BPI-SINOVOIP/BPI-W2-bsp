/*
 * cc-platform.c - clock controller platform code
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/bitops.h>
#include <linux/pm.h>
#include <soc/realtek/rtk_mmio.h>
#include "common.h"

static int cc_suspend(struct device *dev)
{
	int i;
	struct cc_platform_data *ccd = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);

	for (i = 0; i < ccd->clk_num; i++)
		clk_pm_data_save(&ccd->pm_data[i]);

	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static int cc_resume(struct device *dev)
{
	int i;
	struct cc_platform_data *ccd = dev_get_drvdata(dev);

	dev_info(dev, "enter %s\n", __func__);

	for (i = ccd->clk_num - 1; i >= 0; i--)
		clk_pm_data_restore(&ccd->pm_data[i]);

	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

const struct dev_pm_ops cc_pm_ops = {
	.suspend_noirq = cc_suspend,
	.resume_noirq  = cc_resume,
};

struct cc_platform_data *devm_cc_alloc_platform_data(struct device *dev,
						     int max_clk)
{
	struct cc_platform_data *ccd;

	ccd = devm_kzalloc(dev, sizeof(*ccd), GFP_KERNEL);
	if (!ccd)
		return NULL;
	ccd->clk_num = max_clk;
	ccd->data.clk_num = max_clk;
	ccd->data.clks = devm_kcalloc(dev, max_clk,
		sizeof(*ccd->data.clks), GFP_KERNEL);
	if (!ccd->data.clks)
		return NULL;
#ifdef CONFIG_PM
	ccd->pm_data = devm_kcalloc(dev, max_clk,
		sizeof(*ccd->pm_data), GFP_KERNEL);
	if (!ccd->pm_data)
		return NULL;
#endif
	return ccd;
}

int cc_probe_platform(struct platform_device *pdev,
		      struct cc_platform_data *ccd,
		      int (*init_cb)(struct device *dev))
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	void __iomem *reg;
	struct regmap *regmap;
	int offset = 0;
	int ret;

	if (!init_cb || !ccd)
		return -EINVAL;

	/* register access */
	reg = of_iomap(np, 0);
	regmap = of_get_rtk_mmio_regmap_with_offset(np, 0, &offset);
	if (!reg && IS_ERR_OR_NULL(regmap))
		return -EINVAL;
	if (IS_ERR(regmap))
		regmap = NULL;

	ccd->init_data.reg = reg;
	if (regmap) {
		dev_info(dev, "use mmio regmap\n");
		ccd->init_data.offset = offset;
		ccd->init_data.regmap = regmap;
	}

	platform_set_drvdata(pdev, ccd);

	ret = init_cb(dev);
	if (ret)
		dev_err(dev, "failed in %pF: %d\n", init_cb, ret);

	ret = of_clk_add_provider(np, of_clk_src_onecell_get, &ccd->data);
	if (ret)
		dev_err(dev, "failed to add clk provider: %d\n", ret);

	dev_info(dev, "initialized\n");
	return 0;
}

