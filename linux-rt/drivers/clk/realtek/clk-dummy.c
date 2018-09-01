/*
 * clk-dummy.c - dummy clk
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/clk-provider.h>

static int clk_dummy_prepare(struct clk_hw *hw)
{
	return 0;
}
static int clk_dummy_enable(struct clk_hw *hw)
{
	return 0;
}
static void clk_dummy_disable(struct clk_hw *hw)
{
	return;
}
static void clk_dummy_unprepare(struct clk_hw *hw)
{
	return;
}

static const struct clk_ops clk_dummy_ops = {
	.prepare = clk_dummy_prepare,
	.enable = clk_dummy_enable,
	.disable = clk_dummy_disable,
	.unprepare = clk_dummy_unprepare,
};

struct clk_hw *clk_hw_register_dummy(struct device *dev,
		const char *name, const char *parent_name, unsigned long flags)
{
	struct clk_hw *hw;
	struct clk_init_data init;
	int ret;

	hw = kzalloc(sizeof(*hw), GFP_KERNEL);
	if (!hw)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_dummy_ops;
	init.flags = flags | CLK_IS_BASIC;
	init.parent_names = (parent_name ? &parent_name: NULL);
	init.num_parents = (parent_name ? 1 : 0);

	hw->init = &init;

	ret = clk_hw_register(dev, hw);
	if (ret) {
		kfree(hw);
		hw = ERR_PTR(ret);
	}

	return hw;
}
EXPORT_SYMBOL_GPL(clk_hw_register_dummy);

struct clk *clk_register_dummy(struct device *dev,
		const char *name, const char *parent_name, unsigned long flags)
{
	struct clk_hw *hw;

	hw = clk_hw_register_dummy(dev, name, parent_name, flags);
	if (IS_ERR(hw))
		return ERR_CAST(hw);
	return hw->clk;
}
EXPORT_SYMBOL_GPL(clk_register_dummy);

void clk_unregister_dummy(struct clk *clk)
{
	struct clk_hw *hw;

	hw = __clk_get_hw(clk);
	if (!hw)
		return;

	clk_unregister(clk);
	kfree(hw);
}
EXPORT_SYMBOL_GPL(clk_unregister_dummy);

void clk_hw_unregister_dummy(struct clk_hw *hw)
{
	clk_hw_unregister(hw);
	kfree(hw);
}
EXPORT_SYMBOL_GPL(clk_hw_unregister_dummy);

#if CONFIG_OF
static struct clk *_of_clk_dummy_setup(struct device_node *node)
{
	struct clk *clk;
	const char *clk_name = node->name;
	u32 rate;
	int ret;

	if (of_property_read_u32(node, "clock-frequency", &rate))
		return ERR_PTR(-EIO);

	of_property_read_string(node, "clock-output-names", &clk_name);

	clk = clk_register_dummy(NULL, clk_name, NULL, 0);
	if (IS_ERR(clk))
		return clk;

	ret = of_clk_add_provider(node, of_clk_src_simple_get, clk);
	if (ret) {
		clk_unregister(clk);
		return ERR_PTR(ret);
	}

	return clk;
}

/**
 * of_clk_dummy_setup() - Setup function for simple fixed rate clock
 */
void __init of_clk_dummy_setup(struct device_node *node)
{
	_of_clk_dummy_setup(node);
}
CLK_OF_DECLARE(clk_dummy, "dummy-clock", of_clk_dummy_setup);

static int of_clk_dummy_remove(struct platform_device *pdev)
{
	struct clk *clk = platform_get_drvdata(pdev);

	clk_unregister_dummy(clk);

	return 0;
}

static int of_clk_dummy_probe(struct platform_device *pdev)
{
	struct clk *clk;

	/*
	 * This function is not executed when of_clk_dummy_setup
	 * succeeded.
	 */
	clk = _of_clk_dummy_setup(pdev->dev.of_node);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	platform_set_drvdata(pdev, clk);

	return 0;
}

static const struct of_device_id of_clk_dummy_ids[] = {
	{ .compatible = "dummy-clock" },
	{ }
};
MODULE_DEVICE_TABLE(of, of_clk_dummy_ids);

static struct platform_driver of_clk_dummy_driver = {
	.driver = {
		.name = "of_clk_dummy",
		.of_match_table = of_clk_dummy_ids,
	},
	.probe = of_clk_dummy_probe,
	.remove = of_clk_dummy_remove,
};
builtin_platform_driver(of_clk_dummy_driver);
#endif
