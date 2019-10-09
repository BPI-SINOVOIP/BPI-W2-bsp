/*
 * clk-pll.c - Realtek clk-pll & clk-pll-div implementation
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/io.h>
#include <linux/slab.h>
#include <linux/clk-provider.h>
#include <linux/clk.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include "common.h"
#include "clk-pll.h"

#define DEFUALT_OSC_RATE  27000000
#define DEFAULT_OC_EN_DISABLE_RATE 199999999
static unsigned long default_osc_rate = DEFUALT_OSC_RATE;

static int clk_pll_debugfs_u64_set(void *data, u64 val)
{
	struct clk_hw *hw = data;

	clk_set_rate(hw->clk, (unsigned long)(val));
	return 0;
}

static int clk_pll_debugfs_u64_get(void *data, u64 *val)
{
	struct clk_hw *hw = data;

	*val = (u64)clk_get_rate(hw->clk);
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(clk_pll_rate_op, clk_pll_debugfs_u64_get,
	clk_pll_debugfs_u64_set, "%llu\n");

static int clk_pll_debug_init(struct clk_hw *hw, struct dentry *dentry)
{
	debugfs_create_file("rtk_clk_rate", 0644, dentry, hw, &clk_pll_rate_op);
	return 0;
}

static const struct freq_table *ftbl_find_by_rate(const struct freq_table *ftbl,
	unsigned long rate)
{
	unsigned long best_rate = 0;
	const struct freq_table *best = NULL;

	for ( ; !IS_FREQ_TABLE_END(ftbl); ftbl++) {
		if (ftbl->rate == rate)
			return ftbl;

		if (ftbl->rate > rate)
			continue;

		if ((rate - best_rate) > (rate - ftbl->rate)) {
			best_rate = ftbl->rate;
			best = ftbl;
		}
	}

	if (best)
		pr_debug("%s: closest rate  for %lu is %lu\n", __func__,
			rate, best->rate);

	return best;
}

static const struct freq_table *ftbl_find_by_val(const struct freq_table *ftbl,
	unsigned long value)
{
	while (!IS_FREQ_TABLE_END(ftbl)) {
		if (ftbl->val == (value & ftbl->mask))
			return ftbl;
		ftbl++;
	}
	return NULL;
};

static const struct div_table *dtbl_find_by_rate(const struct div_table *dtbl,
	unsigned long rate)
{
	while (!IS_DIV_TABLE_END(dtbl)) {
		if (rate >= dtbl->rate)
			return dtbl;
		dtbl++;
	}
	return NULL;
}

static const struct div_table *dtbl_find_by_val(const struct div_table *dtbl,
	unsigned int val)
{
	while (!IS_DIV_TABLE_END(dtbl)) {
		if (val == dtbl->val)
			return dtbl;
		dtbl++;
	}
	return NULL;
}

static int clk_pll_prepare(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	pr_debug("%s: %s\n", clk_hw_get_name(hw), __func__);

	pll->status |= CLK_PLL_PREPARED;
	__hw_set_pow(pll, 1);

	return 0;
}

static void clk_pll_unprepare(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	pr_debug("%s: %s\n", clk_hw_get_name(hw), __func__);

	pll->status &= ~CLK_PLL_PREPARED;
	__hw_set_pow(pll, 0);
}

static void clk_pll_unprepare_unused(struct clk_hw *hw)
{
	pr_info("%s: %s\n", clk_hw_get_name(hw), __func__);
	clk_pll_unprepare(hw);
}

static int clk_pll_is_prepared(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	int val;

	val = __hw_is_pow(pll);
	if (val < 0)
		val = !!(pll->status & CLK_PLL_PREPARED);
	return val;
}

static long clk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	const struct freq_table *ftblv = NULL;

	WARN_ON_ONCE(*parent_rate != default_osc_rate);

	ftblv = ftbl_find_by_rate(pll->freq_tbl, rate);
	if (!ftblv)
		return 0;

	return ftblv->rate;
}

static unsigned long clk_pll_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	const char *clk_name = clk_hw_get_name(hw);
	unsigned long flags = 0;
	const struct freq_table *ftblv;
	unsigned int val;

	WARN_ON_ONCE(parent_rate != default_osc_rate);

	flags = clk_pll_lock(pll);
	val = clk_reg_read(&pll->base, pll->pll_offset);
	clk_pll_unlock(pll, flags);

	/* if oc_en is not set */
	if (__hw_is_oc(pll) == 0)
		return DEFAULT_OC_EN_DISABLE_RATE;

	ftblv = ftbl_find_by_val(pll->freq_tbl, val);
	WARN(!ftblv, "%s: %s: ftbl_find_by_val() failed with %08x\n",
		clk_name, __func__, val);

	return ftblv ? ftblv->rate : 0;
}

static int clk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	const char *clk_name = clk_hw_get_name(hw);
	unsigned long flags = 0;
	const struct freq_table *freq;
	int ret = 0;

	WARN_ON_ONCE(parent_rate != default_osc_rate);

	freq = ftbl_find_by_rate(pll->freq_tbl, rate);
	if (!freq) {
		pr_err("%s: %s: ftbl_find_by_rate() failed with %lu\n",
			clk_name, __func__, rate);
		return -EINVAL;
	}

	pr_debug("%s: %s: set rate=%ld, val=0x%08x, mask=0x%08x\n",
		clk_name, __func__, freq->rate, freq->val, freq->mask);

	flags = clk_pll_lock(pll);
	__hw_set_rate_prepare(pll);
	clk_reg_update(&pll->base, pll->pll_offset, freq->mask, freq->val);
	ret = __hw_set_rate_done(pll);
	clk_pll_unlock(pll, flags);

	if (ret == -ETIME)
		pr_warn("%s: %s: __hw_set_rate_done() returns timeout\n",
			clk_name, __func__);

	return 0;
}

const struct clk_ops clk_pll_ops = {
	.prepare          = clk_pll_prepare,
	.unprepare        = clk_pll_unprepare,
	.unprepare_unused = clk_pll_unprepare_unused,
	.is_prepared      = clk_pll_is_prepared,
	.round_rate       = clk_pll_round_rate,
	.recalc_rate      = clk_pll_recalc_rate,
	.set_rate         = clk_pll_set_rate,
	.debug_init       = clk_pll_debug_init,
};

static long clk_pll_div_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	const struct div_table *dtblv;

	WARN_ON_ONCE(*parent_rate != default_osc_rate);

	/* lookup div in dtbl */
	dtblv = dtbl_find_by_rate(plld->div_tbl, rate);
	if (!dtblv)
		return 0;

	rate *= dtblv->div;
	rate = clk_pll_round_rate(hw, rate, parent_rate);
	return rate / dtblv->div;
}

static unsigned long clk_pll_div_recalc_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	const char *clk_name = clk_hw_get_name(hw);
	unsigned long rate;
	const struct div_table *dtblv;
	unsigned int val;

	WARN_ON_ONCE(parent_rate != default_osc_rate);

	rate = clk_pll_recalc_rate(hw, parent_rate);

	val = hw_get_div_val(plld);
	dtblv = dtbl_find_by_val(plld->div_tbl, val);
	if (!dtblv)
		return 0;

	rate /= dtblv->div;

	pr_debug("%s: %s: current pll_rate=%lu, div=%d, reg_val=0x%x\n",
		clk_name, __func__, rate, dtblv->div, val);

	return rate;
}

static int clk_pll_div_set_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long parent_rate)
{
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	const char *clk_name = clk_hw_get_name(hw);
	unsigned long flags;
	const struct div_table *ndtblv, *cdtblv;
	unsigned long target;
	unsigned int cur_d;

	WARN_ON_ONCE(parent_rate != default_osc_rate);

	pr_debug("%s: %s: set rate=%lu\n", clk_name, __func__, rate);

	/* find next in the dtbl */
	ndtblv = dtbl_find_by_rate(plld->div_tbl, rate);
	if (!ndtblv) {
		pr_warn("%s: %s: can't find dtblv for %ld\n", clk_name,
			__func__, rate);
		return -EINVAL;
	}

	target = rate * ndtblv->div;

	/* find current in the dtbl */
	cur_d = hw_get_div_val(plld);
	cdtblv = dtbl_find_by_val(plld->div_tbl, cur_d);
	if (!cdtblv)
		return -EINVAL;
	pr_debug("%s: %s: currnet div=%d, reg_val=0x%x\n", clk_name,
		__func__, cdtblv->div, cdtblv->val);

	flags = clk_pll_div_lock(plld);

	/* workaround to prevent glitch */
	if (IS_ENABLED(CONFIG_COMMON_CLK_RTD129X)) {
		struct clk_pll *pll = &plld->clkp;

		if ((pll->flags & CLK_PLL_DIV_WORKAROUND) &&
			ndtblv->val != cdtblv->val &&
			(ndtblv->val == 1 || cdtblv->val == 1)) {
			clk_pll_set_rate(hw, 1000000000, parent_rate);

			pr_debug("%s: %s: set div=%d, reg_val=0x%x\n",
				clk_name, __func__, ndtblv->div, ndtblv->val);
			hw_set_div_val(plld, ndtblv->val);
			cdtblv = ndtblv;
		}
	}

	if (ndtblv->div > cdtblv->div) {
		pr_debug("%s: %s: set div=%d, reg_val=0x%x\n",
			clk_name, __func__, ndtblv->div, ndtblv->val);
		hw_set_div_val(plld, ndtblv->val);
	}

	clk_pll_set_rate(hw, target, parent_rate);

	if (ndtblv->div < cdtblv->div) {
		pr_debug("%s: %s: set div=%d, reg_val=0x%x\n",
			clk_name, __func__, ndtblv->div, ndtblv->val);
		hw_set_div_val(plld, ndtblv->val);
	}

	clk_pll_div_unlock(plld, flags);

	return 0;
}

const struct clk_ops clk_pll_div_ops = {
	.recalc_rate = clk_pll_div_recalc_rate,
	.round_rate  = clk_pll_div_round_rate,
	.set_rate    = clk_pll_div_set_rate,
	.debug_init  = clk_pll_debug_init,
};

int clk_pll_init(struct clk_hw *hw)
{
	const struct clk_init_data *init = hw->init;
	struct clk_pll *pll = to_clk_pll(hw);

	if (init->ops != &clk_pll_ops && init->ops != &clk_pll_div_ops)
		return -EINVAL;

	if (pll->flags & CLK_PLL_REGMAP_BYPASS)
		pll->base.regmap = NULL;

#ifndef CONFIG_COMMON_CLK_RTD119X
	if (pll->flags & CLK_PLL_LSM_STEP_HIGH && SSC_VALID(pll)) {
		unsigned int mask = 0x1ff << 17;
		unsigned int val = 0x1ff << 17;

		clk_reg_update(&pll->base, pll->ssc_offset + 8, mask, val);
	}

	// TODO: 119x ver
#endif
	return 0;
}

