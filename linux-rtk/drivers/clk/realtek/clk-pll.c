/*
 * clk-pll.c - Realtek clk-pll & clk-pll-div implementation
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
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

#include <linux/io.h>
#include <linux/slab.h>
#include <linux/clk-provider.h>
#include <linux/clk.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include "common.h"
#include "clk-pll.h"

#define ck_dbg(clk, fmt, ...) \
	pr_debug("%pC: %s:" fmt, clk, __func__, ##__VA_ARGS__)

#define DEFUALT_OSC_RATE                (27000000)
#define DEFAULT_MAX_OC_DONE_RETRY       (20000)

/*
 * Since table lookup is used for freq selection, default osc rate is required
 * for validation.
 */
unsigned long default_osc_rate = DEFUALT_OSC_RATE;

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

DEFINE_SIMPLE_ATTRIBUTE(clk_pll_rate_op,
			clk_pll_debugfs_u64_get,
			clk_pll_debugfs_u64_set,
			"%llu\n");


static int clk_pll_conf_show(struct seq_file *s, void *data)
{
	struct clk_hw *hw = s->private;
	struct clk_pll *pll = to_clk_pll(hw);
	const struct freq_table *ftbl = pll->freq_tbl;

	seq_printf(s, "%pC\n", hw->clk);
	seq_printf(s, "raw_conf: 0x%08x\n", pll->conf);

	if (pll->ops == &clk_pll_ops || pll->ops == &clk_pll_div_ops) {
		seq_printf(s, "freq-tbl-entries:\n");
		for ( ; !IS_FREQ_TABLE_END(ftbl); ftbl++)
			seq_printf(s, "   %10lu : %08x\n", ftbl->rate, ftbl->val);
	}

	if (pll->ops == &clk_pll_div_ops) {
		struct clk_pll_div *plld = to_clk_pll_div(hw);
		const struct div_table *dtbl = plld->div_tbl;

		seq_printf(s, "div-tbl-entries:\n");
		for ( ; !IS_DIV_TABLE_END(dtbl); dtbl++)
			seq_printf(s, "  %10lu : %2d(0x%02x)\n", dtbl->rate, dtbl->div, dtbl->val);
	}

	return 0;
}

static int clk_pll_conf_open(struct inode *inode, struct file *file)
{
	return single_open(file, clk_pll_conf_show, inode->i_private);
}

static const struct file_operations clk_pll_conf_fops = {
	.open           = clk_pll_conf_open,
	.read           = seq_read,
	.llseek         = seq_lseek,
	.release        = single_release,
};

static int clk_pll_debug_init(struct clk_hw *hw, struct dentry *d)
{
	debugfs_create_file("rtk_clk_rate", 0644, d, hw, &clk_pll_rate_op);
	debugfs_create_file("clk_pll_conf", S_IRUGO, d, hw, &clk_pll_conf_fops);
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
		pr_debug("%s: closest rate for %lu is %lu\n", __func__,
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

static void __clk_pll_set_pow_reg(struct clk_pll *pll, int on)
{
	unsigned int pow = (pll->conf & CLK_PLL_CONF_POW_LOC_CTL3) ? 0x8 : 0x4;

	if (on) {
		clk_reg_update(&pll->base, pll->pll_offset + pow, 0x7, 0x3);
		if (pll->conf & CLK_PLL_CONF_FREQ_LOC_SSC1) {
			u32 val = clk_reg_read(&pll->base, pll->ssc_offset + 0x0);

			/*
			 * For those PLL with SCC used only the default
			 * freq, the oc_en would nerver to be set.
			 * Help to set it here.
			 */
			if ((val & 0x7) != 0x5)
				clk_reg_update(&pll->base, pll->ssc_offset + 0x0, 0x7, 0x5);
		}
		udelay(200);
	} else {
		clk_reg_update(&pll->base, pll->pll_offset + pow, 0x7, 0x4);
	}
}

static int clk_pll_enable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	if (clk_pll_has_pow(pll))
		__clk_pll_set_pow_reg(pll, 1);
	pll->status &= ~CLK_PLL_DISABLED;
	return 0;
}

static void clk_pll_disable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	if (clk_pll_has_pow(pll))
		__clk_pll_set_pow_reg(pll, 0);
	pll->status |= CLK_PLL_DISABLED;
}

static void clk_pll_disable_unused(struct clk_hw *hw)
{
	pr_info("%pC: %s\n", hw->clk, __func__);
	clk_pll_disable(hw);
}

static int clk_pll_is_enabled(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	unsigned int pow = (pll->conf & CLK_PLL_CONF_POW_LOC_CTL3) ? 0x8 : 0x4;
	int val;

	if (clk_pll_has_pow(pll))
		val = clk_reg_read(&pll->base, pll->pll_offset + pow);
	else
		val = !(pll->status & CLK_PLL_DISABLED);
	return !!(val & 0x1);
}

static long clk_pll_round_rate(struct clk_hw *hw,
			       unsigned long rate,
			       unsigned long *parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	const struct freq_table *ftblv = NULL;

	if (WARN_ON_ONCE(*parent_rate != default_osc_rate))
		return 0;

	// TODO: return closest rate
	ftblv = ftbl_find_by_rate(pll->freq_tbl, rate);
	if (!ftblv)
		return 0;

	return ftblv->rate;
}

static unsigned int __clk_pll_get_rate_reg(struct clk_pll *pll)
{
	unsigned int val;

	if (pll->conf & CLK_PLL_CONF_FREQ_LOC_CTL2)
		val = clk_reg_read(&pll->base, pll->pll_offset + 0x4);
	else if (pll->conf & CLK_PLL_CONF_FREQ_LOC_SSC1)
		val = clk_reg_read(&pll->base, pll->ssc_offset + 0x4);
	else
		val = clk_reg_read(&pll->base, pll->pll_offset + 0x0);
	return val;
}

static unsigned long clk_pll_recalc_rate(struct clk_hw *hw,
					 unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	unsigned long flags = 0;
	const struct freq_table *fv;
	unsigned int val;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return 0;

	flags = clk_pll_lock(pll);
	val = __clk_pll_get_rate_reg(pll);
	clk_pll_unlock(pll, flags);

	fv = ftbl_find_by_val(pll->freq_tbl, val);
	WARN(!fv, "%pC: invalid f-tbl entry for %08x\n", hw->clk, val);
	return fv ? fv->rate : 0;
}

static inline int __clk_pll_set_rate_reg(struct clk_pll *pll, u32 mask, u32 val)
{
	struct clk_hw *hw = &pll->base.hw;
	int ret = 0;

	if (pll->conf & CLK_PLL_CONF_FREQ_LOC_CTL2) {
		clk_reg_update(&pll->base, pll->pll_offset + 0x4, mask, val);
		clk_reg_update(&pll->base, pll->pll_offset + 0x8, 0x1, 0x0);
		clk_reg_update(&pll->base, pll->pll_offset + 0x8, 0x1, 0x1);
	} else if (pll->conf & CLK_PLL_CONF_FREQ_LOC_SSC1) {
		int retry = DEFAULT_MAX_OC_DONE_RETRY;

		clk_reg_update(&pll->base, pll->ssc_offset + 0x0, 0x7, 0x4);
		clk_reg_update(&pll->base, pll->ssc_offset + 0x4, mask, val);
		clk_reg_update(&pll->base, pll->ssc_offset + 0x0, 0x7, 0x5);

		if (clk_pll_has_pow(pll) && !clk_pll_is_enabled(hw))
			return 0;

		ret = -ETIME;
		while (--retry > 0) {
			udelay(1);
			if (clk_reg_read_notrace(&pll->base, pll->ssc_offset + 0x1c) & BIT(20)) {
				ret = 0;
				break;
			}
		}
		pr_debug("%pC: %s: retry left=%d\n", hw->clk, __func__, retry);
	} else {
		clk_reg_update(&pll->base, pll->pll_offset, mask, val);
	}
	return ret;
}

static int clk_pll_set_rate(struct clk_hw *hw,
			    unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	unsigned long flags = 0;
	const struct freq_table *fv;
	int ret = 0;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return 0;

	fv = ftbl_find_by_rate(pll->freq_tbl, rate);
	if (WARN(!fv, "%pC: invalid f-tbl entry for %lu\n", hw->clk, rate))
		return -EINVAL;

	pr_debug("%pC: %s: target rate=%ld, val=0x%08x, mask=0x%08x\n",
		hw->clk, __func__, fv->rate, fv->val, fv->mask);

	flags = clk_pll_lock(pll);
	ret = __clk_pll_set_rate_reg(pll, fv->mask, fv->val);
	clk_pll_unlock(pll, flags);
	if (ret == -ETIME)
		pr_warn("%pC %s: wait pll ready timeout\n", hw->clk, __func__);
	return 0;
}

static void __clk_pll_div_set_div_reg(struct clk_pll_div *plld, unsigned int val)
{
	unsigned int m = (BIT(plld->div_width) - 1) << plld->div_shift;
	unsigned int s = plld->div_shift;

	clk_reg_update(&plld->clkp.base, plld->div_offset, m, val << s);
}

static unsigned int __clk_pll_div_get_div_reg(struct clk_pll_div *plld)
{
	unsigned int m = (BIT(plld->div_width) - 1) << plld->div_shift;
	unsigned int s = plld->div_shift;

	return (clk_reg_read(&plld->clkp.base, plld->div_offset) & m) >> s;
}


static long clk_pll_div_round_rate(struct clk_hw *hw,
				   unsigned long rate,
				   unsigned long *parent_rate)
{
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	const struct div_table *dv;

	if (WARN_ON_ONCE(*parent_rate != default_osc_rate))
		return 0;

	/* lookup div in dtbl */
	dv = dtbl_find_by_rate(plld->div_tbl, rate);
	if (WARN(!dv, "%pC: invalid d-tbl entry for %lu", hw->clk, rate))
		return 0;

	rate *= dv->div;
	rate = clk_pll_round_rate(hw, rate, parent_rate);
	return rate / dv->div;
}

static unsigned long clk_pll_div_recalc_rate(struct clk_hw *hw,
						 unsigned long parent_rate)
{
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	unsigned long rate;
	const struct div_table *dv;
	unsigned int val;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return 0;

	rate = clk_pll_recalc_rate(hw, parent_rate);

	val = __clk_pll_div_get_div_reg(plld);
	dv = dtbl_find_by_val(plld->div_tbl, val);
	if (WARN(!dv, "%pC: invalid d-tbl entry for %lu", hw->clk, rate))
		return 0;

	rate /= dv->div;
	pr_debug("%pC: %s: current rate=%lu, div=%d, reg_val=0x%x\n",
		hw->clk, __func__, rate, dv->div, val);

	return rate;
}

static int clk_pll_div_set_rate(struct clk_hw *hw,
				unsigned long rate,
				unsigned long parent_rate)
{
	struct clk *clk = hw->clk;
	struct clk_pll_div *plld = to_clk_pll_div(hw);
	unsigned long flags;
	const struct div_table *ndv, *cdv;
	unsigned long target;
	unsigned int cur_d;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return -EINVAL;

	/* find next in the dtbl */
	ndv = dtbl_find_by_rate(plld->div_tbl, rate);
	if (WARN(!ndv, "%pC: invalid d-tbl entry for %lu", hw->clk, rate))
		return -EINVAL;

	target = rate * ndv->div;

	/* find current in the dtbl */
	cur_d = __clk_pll_div_get_div_reg(plld);
	cdv = dtbl_find_by_val(plld->div_tbl, cur_d);
	if (WARN(!ndv, "%pC: invalid d-tbl entry for %u", hw->clk, cur_d))
		return -EINVAL;

	ck_dbg(clk, "target rate=%lu\n", rate);
	ck_dbg(clk, "c div=(%d, 0x%x)\n", cdv->div, cdv->val);
	ck_dbg(clk, "n div=(%d, 0x%x)\n", ndv->div, ndv->val);

	flags = clk_pll_div_lock(plld);

	/* workaround to prevent glitch */
	if (IS_ENABLED(CONFIG_COMMON_CLK_RTD129X)) {
		struct clk_pll *pll = &plld->clkp;

		if ((pll->flags & CLK_PLL_DIV_WORKAROUND) &&
			ndv->val != cdv->val &&
			(ndv->val == 1 || cdv->val == 1)) {

			ck_dbg(clk, "apply rate=%u\n", 1000000000);
			clk_pll_set_rate(hw, 1000000000, parent_rate);

			ck_dbg(clk, "apply div=%d, reg_val=0x%x\n", ndv->div, ndv->val);
			__clk_pll_div_set_div_reg(plld, ndv->val);
			cdv = ndv;
		}
	}

	if (ndv->div > cdv->div)
		__clk_pll_div_set_div_reg(plld, ndv->val);
	clk_pll_set_rate(hw, target, parent_rate);
	if (ndv->div < cdv->div)
		__clk_pll_div_set_div_reg(plld, ndv->val);

	clk_pll_div_unlock(plld, flags);

	return 0;
}

const struct clk_ops clk_pll_ops = {
	.debug_init       = clk_pll_debug_init,
	.round_rate       = clk_pll_round_rate,
	.recalc_rate      = clk_pll_recalc_rate,
	.set_rate         = clk_pll_set_rate,
	.enable           = clk_pll_enable,
	.disable          = clk_pll_disable,
	.disable_unused   = clk_pll_disable_unused,
	.is_enabled       = clk_pll_is_enabled,
};

const struct clk_ops clk_pll_div_ops = {
	.debug_init       = clk_pll_debug_init,
	.round_rate       = clk_pll_div_round_rate,
	.recalc_rate      = clk_pll_div_recalc_rate,
	.set_rate         = clk_pll_div_set_rate,
	.enable           = clk_pll_enable,
	.disable          = clk_pll_disable,
	.disable_unused   = clk_pll_disable_unused,
	.is_enabled       = clk_pll_is_enabled,
};

bool clk_hw_is_pll(struct clk_hw *hw)
{
	const struct clk_init_data *init = hw->init;

	if (init->ops == &clk_pll_ops ||
	    init->ops == &clk_pll_div_ops)
		return true;

	return false;
}

int clk_pll_init(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);

	if (!clk_hw_is_pll(hw))
		return -EINVAL;
	pll->ops = hw->init->ops;

	return 0;
}

