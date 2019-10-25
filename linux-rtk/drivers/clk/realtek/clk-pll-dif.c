/*
 * clk-pll-dif.c - PLL_DIF
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
#include <linux/clk.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include "common.h"
#include "clk-pll.h"

static int clk_pll_dif_enable(struct clk_hw *hw)
{
	struct clk_pll_dif *pll = to_clk_pll_dif(hw);

	pr_debug("%pC: %s\n", hw->clk, __func__);

	clk_reg_write(&pll->base, pll->pll_offset + 0x0C, 0x00000048);
	clk_reg_write(&pll->base, pll->pll_offset + 0x08, 0x00020c00);
	clk_reg_write(&pll->base, pll->pll_offset + 0x04, 0x204004ca);
	clk_reg_write(&pll->base, pll->pll_offset + 0x00, 0x8000a000);
	udelay(100);

	clk_reg_write(&pll->base, pll->pll_offset + 0x08, 0x00420c00);
	udelay(50);

	clk_reg_write(&pll->base, pll->pll_offset + 0x08, 0x00420c03);
	udelay(200);

	clk_reg_write(&pll->base, pll->pll_offset + 0x0C, 0x00000078);
	udelay(100);

	clk_reg_write(&pll->base, pll->pll_offset + 0x04, 0x204084ca);

	/* ssc control */
	clk_reg_write(&pll->base, pll->ssc_offset + 0x00, 0x00000004);
	clk_reg_write(&pll->base, pll->ssc_offset + 0x04, 0x00006800);
	clk_reg_write(&pll->base, pll->ssc_offset + 0x0C, 0x00000000);
	clk_reg_write(&pll->base, pll->ssc_offset + 0x10, 0x00000000);
	clk_reg_write(&pll->base, pll->ssc_offset + 0x08, 0x001e1f98);
	clk_reg_write(&pll->base, pll->ssc_offset + 0x00, 0x00000005);
	pll->status &= ~CLK_PLL_DISABLED;

	return 0;
}

static void clk_pll_dif_disable(struct clk_hw *hw)
{
	struct clk_pll_dif *pll = to_clk_pll_dif(hw);

	pr_debug("%pC: %s\n", hw->clk, __func__);
	clk_reg_update(&pll->base, pll->pll_offset + 0x04, 0x00080000, 0x0);
	clk_reg_update(&pll->base, pll->pll_offset + 0x08, 0x00400C03, 0x0);
	clk_reg_update(&pll->base, pll->pll_offset + 0x0C, 0x00000038, 0x0);

	clk_reg_write(&pll->base, pll->ssc_offset + 0x00, 0x00000004);
	pll->status |= CLK_PLL_DISABLED;
}

static int clk_pll_dif_is_enabled(struct clk_hw *hw)
{
	struct clk_pll_dif *pll = to_clk_pll_dif(hw);

	pr_debug("%pC: %s\n", hw->clk, __func__);
	return !(pll->status & CLK_PLL_DISABLED);
}

static void clk_pll_dif_disable_unused(struct clk_hw *hw)
{
	pr_info("%pC: %s\n", hw->clk, __func__);
	clk_pll_dif_disable(hw);
}

const struct clk_ops clk_pll_dif_ops = {
	.enable           = clk_pll_dif_enable,
	.disable          = clk_pll_dif_disable,
	.disable_unused   = clk_pll_dif_disable_unused,
	.is_enabled       = clk_pll_dif_is_enabled,
};

