/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 * Copyright (C) 2011 Richard Zhao, Linaro <richard.zhao@linaro.org>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Simple multiplexer clock implementation
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

