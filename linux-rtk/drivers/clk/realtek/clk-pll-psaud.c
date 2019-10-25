/*
 * clk-pll-psaud.c - PLL_PSAUDXA
 *
 * Copyright (c) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *       Cheng-Yu Lee <cylee12@realtek.com>
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

#include <linux/clk-provider.h>
#include "common.h"
#include "clk-pll.h"

static int clk_pll_psaud_enable(struct clk_hw *hw)
{
	struct clk_pll_psaud *pll = to_clk_pll_psaud(hw);
	u32 mask = 0, val = 0;

	if (pll->id == CLK_PLL_PSAUD1A) {
		mask = 0x3;
		val = 0x1;
	} else {
		mask = 0xc;
		val = 0x4;
	}
	clk_reg_update(&pll->base, pll->reg + 4, mask, val);
	return 0;
}

static void clk_pll_psaud_disable(struct clk_hw *hw)
{
	struct clk_pll_psaud *pll = to_clk_pll_psaud(hw);
	u32 mask = 0, val = 0;

	if (pll->id == CLK_PLL_PSAUD1A) {
		mask = 0x3;
		val = 0x3;
	} else {
		mask = 0xc;
		val = 0xc;
	}
	clk_reg_update(&pll->base, pll->reg + 4, mask, val);
}

static void clk_pll_psaud_disable_unused(struct clk_hw *hw)
{
	pr_info("%pC: %s\n", hw->clk, __func__);
	clk_pll_psaud_disable(hw);
}

static int clk_pll_psaud_is_enabled(struct clk_hw *hw)
{
	struct clk_pll_psaud *pll = to_clk_pll_psaud(hw);
	u32 val;

	val = clk_reg_read(&pll->base, pll->reg + 4);
	if (pll->id == CLK_PLL_PSAUD1A)
		val &= 0x3;
	else
		val >>= 2;
	return val == 0x1;
}

static long clk_pll_psaud_round_rate(struct clk_hw *hw,
				     unsigned long rate,
				     unsigned long *parent_rate)
{
	if (WARN_ON_ONCE(*parent_rate != default_osc_rate))
		return -EINVAL;
	return 49192000;
}

static int clk_pll_psaud_set_rate(struct clk_hw *hw,
				  unsigned long rate,
				  unsigned long parent_rate)
{
	struct clk_pll_psaud *pll = to_clk_pll_psaud(hw);
	u32 rsel = 0;
	u32 mask = 0, val = 0;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return -EINVAL;

	if (WARN_ON_ONCE(rate != 45158400 && rate != 49192000))
		return -EINVAL;

	if (rate == 45158400)
		rsel = 1;
	if (pll->id == CLK_PLL_PSAUD1A) {
		val  = 0x6a0 | (rsel << 8);
		mask = 0x7e0;
	} else {
		val  = 0x19 | (rsel << 2);
		mask = 0x1f;
	}
	clk_reg_update(&pll->base, pll->reg, mask, val);
	return 0;
}

static unsigned long clk_pll_psaud_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct clk_pll_psaud *pll = to_clk_pll_psaud(hw);
	u32 val;
	u32 rsel = 0;

	if (WARN_ON_ONCE(parent_rate != default_osc_rate))
		return 0;

	val = clk_reg_read(&pll->base, pll->reg);

	if (pll->id == CLK_PLL_PSAUD1A)
		rsel = !!(val & BIT(8));
	else
		rsel = !!(val & BIT(2));

	return rsel ? 45158400 : 49192000;
}

const struct clk_ops clk_pll_psaud_ops = {
	.enable         = clk_pll_psaud_enable,
	.disable        = clk_pll_psaud_disable,
	.disable_unused = clk_pll_psaud_disable_unused,
	.is_enabled     = clk_pll_psaud_is_enabled,
	.set_rate       = clk_pll_psaud_set_rate,
	.round_rate     = clk_pll_psaud_round_rate,
	.recalc_rate    = clk_pll_psaud_recalc_rate,
};

