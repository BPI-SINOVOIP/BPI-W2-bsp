/*
 * clk-mmio-mux.c - this file is based on clk-mux.c
 *
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

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/err.h>
#include "clk-mmio-mux.h"

static u8 clk_mmio_mux_get_parent(struct clk_hw *hw)
{
	struct clk_mmio_mux *mux = to_clk_mmio_mux(hw);
	int num_parents = clk_hw_get_num_parents(hw);
	u32 val;
	unsigned long flags = 0;

	if (mux->lock)
		spin_lock_irqsave(mux->lock, flags);

	val = clk_reg_read(&mux->base, mux->mux_offset) >> mux->shift;
	if (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);

	val &= mux->mask;
	if (val >= num_parents)
		return -EINVAL;

	return val;
}

static int clk_mmio_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct clk_mmio_mux *mux = to_clk_mmio_mux(hw);
	unsigned long flags = 0;

	if (mux->lock)
		spin_lock_irqsave(mux->lock, flags);

	clk_reg_update(&mux->base, mux->mux_offset, mux->mask << mux->shift,
		index << mux->shift);

	if (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	return 0;
}

const struct clk_ops clk_mmio_mux_ops = {
	.get_parent = clk_mmio_mux_get_parent,
	.set_parent = clk_mmio_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
};
EXPORT_SYMBOL_GPL(clk_mmio_mux_ops);

const struct clk_ops clk_mmio_mux_ro_ops = {
	.get_parent = clk_mmio_mux_get_parent,
};
EXPORT_SYMBOL_GPL(clk_mmio_mux_ro_ops);

