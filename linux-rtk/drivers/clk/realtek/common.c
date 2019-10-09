/*
 * common.c - Realtek Clock common
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include "common.h"
#include "clk-pll.h"
#include "clk-mmio-gate.h"
#include "clk-mmio-mux.h"

#ifdef CONFIG_COMMON_CLK_REALTEK_DEBUG
static bool clk_debug_enable;

bool is_clk_debug_enabled(void)
{
	return clk_debug_enable;
}

static int __init clk_debug_enable_setup(char *__unused)
{
	clk_debug_enable = true;
	return 1;
}
__setup("clk_debug_enable", clk_debug_enable_setup);
#endif /* CONFIG_COMMON_CLK_REALTEK_DEBUG */

#ifdef CONFIG_PM
int clk_pm_init(struct clk *clk, struct clk_pm_data *pm_data,
	unsigned int pm_flags)
{
	if (!clk)
		return -ENOENT;

	WARN(!pm_data, "no pm_data for pm");
	if (!pm_data)
		return -EINVAL;

	pm_data->clk = clk;
	pm_data->flags = pm_flags;
	return 0;
}


int clk_pm_data_save(struct clk_pm_data *pm_data)
{
	struct clk *clk = pm_data->clk;

	if (!clk)
		return 0;

	if (pm_data->flags & CLK_PM_SUSPEND_PARENT)
		pm_data->parent = clk_get_parent(clk);

	if (pm_data->flags & CLK_PM_SUSPEND_RATE)
		pm_data->rate = clk_get_rate(clk);

	if (pm_data->flags & CLK_PM_SUSPEND_ENABLE) {
		pm_data->enable_cnt = __clk_get_enable_count(clk);

		while (__clk_get_enable_count(clk) > 0)
			clk_disable_unprepare(clk);
	}

	pr_debug("%s: data[f = 0x%x, p = %s, r = %lu, en_cnt = %d]\n",
		__clk_get_name(clk), pm_data->flags,
		__clk_get_name(pm_data->parent), pm_data->rate,
		pm_data->enable_cnt);

	return 0;
}

int clk_pm_data_restore(struct clk_pm_data *pm_data)
{
	struct clk *clk = pm_data->clk;

	if (!clk)
		return 0;

	if (pm_data->flags & CLK_PM_SUSPEND_ENABLE) {
		while (pm_data->enable_cnt > 0) {
			clk_prepare_enable(clk);
			pm_data->enable_cnt--;
		}
	}

	if (pm_data->parent) {
		/* clear the old parent */
		clk_set_parent(clk, NULL);

		/* restore parent */
		clk_set_parent(clk, pm_data->parent);
	}

	if (pm_data->rate) {
		long old;

		old = clk_get_rate(clk);
		clk_set_rate(clk, pm_data->rate);

		pr_debug("%s: %ld -> %ld\n", __clk_get_name(clk),
			old, clk_get_rate(clk));
	}

	return 0;
}
#endif /* CONFIG_PM */

#define CC_CLK_TYPE_OTHERS     0
#define CC_CLK_TYPE_CLK_REG    1
#define CC_CLK_TYPE_CLK_PLL    3
#define CC_CLK_TYPE_CLK_MUX    5
#define CC_CLK_TYPE_CLK_GATE   7

static inline int __hw_to_cc_type(struct clk_hw *hw)
{
	const struct clk_ops *ops = hw->init->ops;

	if (ops == &clk_pll_ops || ops == &clk_pll_div_ops)
		return CC_CLK_TYPE_CLK_PLL;
	if (ops == &clk_mmio_mux_ops)
		return CC_CLK_TYPE_CLK_MUX;
	if (ops == &clk_mmio_gate_ops)
		return CC_CLK_TYPE_CLK_GATE;

	return CC_CLK_TYPE_OTHERS;
}

static inline int cc_set_clk_cell(struct cc_desc *ccd, int i, struct clk *clk)
{
	if (ccd->data.clks[i]) {
		pr_warn("%s: failed to fill %s to cell %d, used by %s\n",
			__func__,
			__clk_get_name(clk), i,
			__clk_get_name(ccd->data.clks[i]));
		return -EINVAL;
	}
	ccd->data.clks[i] = clk;
	return 0;
}

int cc_init_hw(struct device *dev, struct cc_desc *ccd, int cc_index,
	struct clk_hw *hw)
{
	struct clk *clk;
	struct clk_reg *reg = to_clk_reg(hw);
	const char *name = hw->init->name;
	int clk_type;
	unsigned int pm_flags = 0;

#ifdef CONFIG_XEN
	if (of_clk_is_invalid(dev->of_node, name)) {
		dev_notice(dev, "%s not in current domain\n", name);
		return 0;
	}
#endif

	dev_info(dev, "%s: %s\n", __func__, name);

	clk_type = __hw_to_cc_type(hw);
	switch (clk_type) {
	case CC_CLK_TYPE_CLK_PLL:
		clk_reg_init(reg, &ccd->init_data);
		clk_pll_init(hw);
		pm_flags = CLK_PM_SUSPEND_RATE;
		break;

	case CC_CLK_TYPE_CLK_MUX:
		clk_reg_init(reg, &ccd->init_data);
		pm_flags = CLK_PM_SUSPEND_PARENT;
		break;

	case CC_CLK_TYPE_CLK_GATE:
		clk_reg_init(reg, &ccd->init_data);
		pm_flags = CLK_PM_SUSPEND_ENABLE;
		break;

	case CC_CLK_TYPE_CLK_REG:
		clk_reg_init(reg, &ccd->init_data);
		break;

	default:
		break;
	}

	clk = clk_register(dev, hw);
	if (IS_ERR(clk))
		return PTR_ERR(clk);
	clk_register_clkdev(clk, name, NULL);
	cc_set_clk_cell(ccd, cc_index, hw->clk);
	if (pm_flags)
		clk_pm_init(clk, &ccd->pm_data[cc_index], pm_flags);
	return 0;
}

static struct clk *clk_reg_create_composite_clk(struct device *dev,
	struct clk_reg_init_data *reg,
	struct clk_composite_init_data *init)
{
	struct clk_mmio_gate *gate = NULL;
	const struct clk_ops *gate_op = NULL;
	struct clk_mmio_mux *mux = NULL;
	const struct clk_ops *mux_op = NULL;
	struct clk *clk;

	if (init->mux_offset != CLK_OFFSET_INVALID) {
		mux = kzalloc(sizeof(*mux), GFP_KERNEL);
		mux->mux_offset = init->mux_offset;
		mux->mask = BIT(init->mux_width) - 1;
		mux->shift = init->mux_shift;

		clk_reg_init(&mux->base, reg);
		mux_op = &clk_mmio_mux_ops;
	}

	if (init->gate_offset != CLK_OFFSET_INVALID) {
		gate = kzalloc(sizeof(*gate), GFP_KERNEL);
		gate->gate_offset = init->gate_offset;
		gate->bit_idx = init->gate_shift;
		gate->flags = init->gate_flags;

		clk_reg_init(&gate->base, reg);
		gate_op = &clk_mmio_gate_ops;

		if (is_clk_debug_enabled()) {
			/* parse reg from dt */
			gate->ref = of_rdbg_get_info(dev->of_node, 0,
				init->gate_offset);
			if (gate->ref)
				dev_err(dev, "rdbg add %s\n", init->name);
		}
	}

	clk = clk_register_composite(NULL, init->name, init->parent_names,
		init->num_parents,
		mux ? &__clk_mmio_mux_hw(mux) : NULL, mux_op,
		NULL, NULL,
		gate ? &__clk_mmio_gate_hw(gate) : NULL, gate_op,
		init->flags);
	if (IS_ERR(clk)) {
		kfree(mux);
		kfree(gate);
	}
	return clk;
}

int cc_init_composite_clk(struct device *dev, struct cc_desc *ccd, int cc_index,
	struct clk_composite_init_data *init)
{
	struct clk *clk;
	const char *name = init->name;
	unsigned int pm_flags = 0;

#ifdef CONFIG_XEN
	if (of_clk_is_invalid(dev->of_node, name)) {
		dev_notice(dev, "%s not in current domain\n", name);
		return 0;
	}
#endif

	dev_info(dev, "%s: %s\n", __func__, name);

	clk = clk_reg_create_composite_clk(dev, &ccd->init_data, init);
	if (IS_ERR(clk))
		return PTR_ERR(clk);
	init->clk = clk;

	clk_register_clkdev(clk, init->name, NULL);
	cc_set_clk_cell(ccd, cc_index, clk);
	/* init clk pm */
	if (CLK_OFFSET_IS_VALID(init->mux_offset))
		pm_flags |= CLK_PM_SUSPEND_PARENT;
	if (CLK_OFFSET_IS_VALID(init->gate_offset))
		pm_flags |=  CLK_PM_SUSPEND_ENABLE;
	clk_pm_init(clk, &ccd->pm_data[cc_index], pm_flags);
	return 0;
}

