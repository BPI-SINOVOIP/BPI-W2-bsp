/*
 * cgc.c - clock-gate controller
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * Author:
 *	Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
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
#include "clk-mmio-gate.h"

#define MAX_CLOCK_GATES  32

struct cgc_desc {
	const char *names[MAX_CLOCK_GATES];
	int num_names;
	unsigned int flags;
	unsigned int pm_mask;
	unsigned int ignore_unsed_mask;
};

/* flags */
#define CGC_FLAGS_HAS_WEB  0x1

struct cgc_data {
	struct device *dev;
	struct cgc_desc desc;
	struct clk_reg_init_data init_data;
	struct clk_onecell_data clk_data;
	unsigned int pm_data;
};


static inline int cgc_has_web(struct cgc_data *cgcd)
{
	return !!(cgcd->desc.flags & CGC_FLAGS_HAS_WEB);
}

static int init_clk_gates(struct cgc_data *cgcd)
{
	int i;
	struct cgc_desc *desc = &cgcd->desc;
	struct clk_onecell_data *data = &cgcd->clk_data;
	struct device *dev = cgcd->dev;
	struct device_node *np = dev->of_node;
	unsigned int flags = 0;
	unsigned int num_clks = desc->num_names;
	const char *name = NULL;
	int ret = 0;

	if (cgc_has_web(cgcd)) {
		flags |= CLK_MMIO_GATE_HAS_WRITE_EN;
		num_clks *= 2;
	}

	data->clks = kcalloc(num_clks, sizeof(struct clk *), GFP_KERNEL);
	if (!data->clks)
		return -ENOMEM;
	data->clk_num = num_clks;

	for (i = 0; i < desc->num_names; i++) {
		struct clk_mmio_gate *gate;
		struct clk_init_data init = { 0 };
		struct clk *clk;
		int idx = cgc_has_web(cgcd) ? i * 2 : i;

		name = desc->names[i];
		if (!name || !name[0] || !strncmp(name, "unused", 6))
			continue;

		/* setup clk init data */
		init.name = name;
		init.ops = &clk_mmio_gate_ops;
		init.flags = CLK_IS_BASIC;
		if (desc->ignore_unsed_mask & BIT(i))
			init.flags |= CLK_IGNORE_UNUSED;

		gate = kzalloc(sizeof(*gate), GFP_KERNEL);
		if  (!gate) {
			ret = -ENOMEM;
			break;
		}

		/* setup init data for specific clk type */
		gate->bit_idx = idx;
		gate->base.hw.init = &init;
		gate->flags = flags;
		clk_reg_init(&gate->base, &cgcd->init_data);

		/* register clk */
		clk = clk_register(NULL, &gate->base.hw);
		if (IS_ERR(clk)) {
			dev_err(dev, "%s: failed to register: %ld\n",
				name, PTR_ERR(clk));
			ret = PTR_ERR(clk);
			break;
		}
		data->clks[idx] = clk;

		dev_dbg(dev, "name-index=%d, clk-index=%d, clk-name=%s\n",
			i, idx, name);

		/* register clkdev */
		clk_register_clkdev(clk, name, NULL);
	}

	if (ret)
		dev_err(dev, "failed to init %s(%d): %d\n", name, i, ret);

	return of_clk_add_provider(np, of_clk_src_onecell_get, data);
}

static int rtk_cgc_suspend(struct device *dev)
{
	struct cgc_data *cgcd = dev_get_drvdata(dev);
	struct clk_reg clk_reg;

	dev_info(dev, "enter %s\n", __func__);

	/* create a clk_reg for read/write reg */
	clk_reg_init(&clk_reg, &cgcd->init_data);
	cgcd->pm_data = clk_reg_read(&clk_reg, 0);
	dev_dbg(dev, "save pm_data=%08x\n", cgcd->pm_data);

	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static int rtk_cgc_resume(struct device *dev)
{
	struct cgc_data *cgcd = dev_get_drvdata(dev);
	struct clk_reg clk_reg;
	int mask;
	int val;

	dev_info(dev, "enter %s\n", __func__);

	clk_reg_init(&clk_reg, &cgcd->init_data);
	mask = cgcd->desc.pm_mask;
	val  = cgcd->pm_data;

	if (cgc_has_web(cgcd)) {
		mask |= cgcd->desc.pm_mask << 1;
		val  |= cgcd->desc.pm_mask << 1;
	}

	dev_dbg(dev, "restore mask=%08x, val=%08x, pm_data=%08x\n",
		mask, val, cgcd->pm_data);
	clk_reg_update(&clk_reg, 0, mask, val);

	dev_info(dev, "exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_cgc_pm_ops = {
	.suspend_noirq = rtk_cgc_suspend,
	.resume_noirq = rtk_cgc_resume,
};

static int of_get_cgc_desc(struct device_node *np, struct cgc_desc *desc)
{
	struct property *prop;
	const char *s;
	int ret;
	int i;

	if (of_property_read_bool(np, "has-write-en") ||
	    of_property_read_bool(np, "realtek,has-web"))
		desc->flags |= CGC_FLAGS_HAS_WEB;

	ret = of_property_count_strings(np, "clock-output-names");
	if (ret < 0)
		return ret;
	desc->num_names = ret;

	ret = of_property_read_string_array(np, "clock-output-names",
					    desc->names, desc->num_names);
	if (ret != desc->num_names)
		return -EINVAL;
	if (ret < 0)
		return ret;

	desc->ignore_unsed_mask = 0;
	of_property_for_each_string(np, "ignore-unused-clocks", prop, s) {
		ret = of_property_match_string(np, "clock-output-names", s);
		if (ret < 0)
			continue;
		desc->ignore_unsed_mask |= BIT(ret);
	}

	desc->pm_mask = 0;
	i = 0;
	of_property_for_each_string(np, "clock-output-names", prop, s) {
		if (s && s[0] && strncmp(s, "unused", 6) &&
		    !of_clk_is_ignore_pm(np, s))
			desc->pm_mask |= BIT(i);
		i += (desc->flags & CGC_FLAGS_HAS_WEB) ? 2 : 1;
	}
	return 0;
}

static int devm_of_get_clk_reg_init_data(struct device *dev,
					 int index,
					 struct clk_reg_init_data *idata)
{
	struct device_node *np = dev->of_node;
	struct regmap *regmap;
	int offset = 0;
	struct resource r;
	int ret;

	regmap = of_get_rtk_mmio_regmap_with_offset(np, index, &offset);
	if (!IS_ERR_OR_NULL(regmap)) {
		idata->regmap = regmap;
		idata->offset = offset;
		return 0;
	}

	ret = of_address_to_resource(np, index, &r);
	if (ret)
		return ret;
	idata->reg = devm_ioremap(dev, r.start, resource_size(&r));
	return idata->reg ? 0 : -ENOMEM;
}


static int rtk_cgc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct cgc_data *cgcd;
	int ret;

	cgcd = devm_kzalloc(dev, sizeof(*cgcd), GFP_KERNEL);
	if (!cgcd)
		return -ENOMEM;

	cgcd->dev = dev;

	ret = of_get_cgc_desc(np, &cgcd->desc);
	if (ret) {
		dev_err(dev, "failed to get cgc_desc: %d\n", ret);
		return ret;
	}

	ret = devm_of_get_clk_reg_init_data(dev, 0, &cgcd->init_data);
	if (ret) {
		dev_err(dev, "failed to get clk_reg_init_data: %d", ret);
		return ret;
	}

	platform_set_drvdata(pdev, cgcd);
	init_clk_gates(cgcd);
	dev_info(dev, "initialized");
	return 0;
}

static const struct of_device_id rtk_cgc_match[] = {
	{.compatible = "realtek,clock-gate-controller"},
	{}
};

static struct platform_driver rtk_cgc_driver = {
	.probe = rtk_cgc_probe,
	.driver = {
		.name = "rtk-cgc",
		.of_match_table = rtk_cgc_match,
		.pm = &rtk_cgc_pm_ops,
	},
};

static int __init rtk_cgc_init(void)
{
	return platform_driver_register(&rtk_cgc_driver);
}
core_initcall(rtk_cgc_init);
