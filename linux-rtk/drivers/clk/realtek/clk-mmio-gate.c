/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
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

#include <linux/slab.h>
#include <linux/clk-provider.h>
#include "clk-mmio-gate.h"

static int clk_mmio_gate_enable(struct clk_hw *hw)
{
	struct clk_mmio_gate *g = to_clk_mmio_gate(hw);
	unsigned long flags = 0;
	unsigned int mask;
	unsigned int val;

	if (g->lock)
		spin_lock_irqsave(g->lock, flags);

	mask = BIT(g->bit_idx);
	val  = BIT(g->bit_idx);

	if (g->flags & CLK_MMIO_GATE_HAS_WRITE_EN) {
		mask |= BIT(g->bit_idx + 1);
		val  |= BIT(g->bit_idx + 1);
	}

	clk_reg_update(&g->base, g->gate_offset, mask, val);

	if (g->lock)
		spin_unlock_irqrestore(g->lock, flags);

	return 0;
}

static void clk_mmio_gate_disable(struct clk_hw *hw)
{
	struct clk_mmio_gate *g = to_clk_mmio_gate(hw);
	unsigned long flags = 0;
	unsigned int mask;
	unsigned int val;

	if (g->lock)
		spin_lock_irqsave(g->lock, flags);

	mask = BIT(g->bit_idx);
	val  = 0;

	if (g->flags & CLK_MMIO_GATE_HAS_WRITE_EN) {
		mask |= BIT(g->bit_idx + 1);
		val  |= BIT(g->bit_idx + 1);
	}

	clk_reg_update(&g->base, g->gate_offset, mask, val);

	if (g->lock)
		spin_unlock_irqrestore(g->lock, flags);
}

static void clk_mmio_gate_disable_unused(struct clk_hw *hw)
{
	pr_info("%s: %s\n", __func__, __clk_get_name(hw->clk));
	clk_mmio_gate_disable(hw);
}

static int clk_mmio_gate_is_enabled(struct clk_hw *hw)
{
	struct clk_mmio_gate *g = to_clk_mmio_gate(hw);
	int ret;
	unsigned long flags = 0;

	if (g->lock)
		spin_lock_irqsave(g->lock, flags);

	ret = !!(clk_reg_read(&g->base, g->gate_offset) & BIT(g->bit_idx));

	if (g->lock)
		spin_unlock_irqrestore(g->lock, flags);

	return ret;
}

const struct clk_ops clk_mmio_gate_ops = {
	.enable = clk_mmio_gate_enable,
	.disable = clk_mmio_gate_disable,
	.disable_unused = clk_mmio_gate_disable_unused,
	.is_enabled = clk_mmio_gate_is_enabled,
};
