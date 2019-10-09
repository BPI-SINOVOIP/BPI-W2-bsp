/*
 * clk-mmio-mux.h - multiplexer clock with regmap
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __CLK_REALTEK_CLK_MMIO_MUX_H
#define __CLK_REALTEK_CLK_MMIO_MUX_H

#include "common.h"

/**
 * struct clk_mmio_mux - multiplexer clock with regmap
 *
 * @base:       handle for common, hw and register access interfaces
 * @mux_offset: offset from base register
 * @mask:       mask of multiplexer bit field
 * @shift:      shift to multiplexer bit field
 * @lock:       register lock
 */
struct clk_mmio_mux {
	struct clk_reg base;
	int mux_offset;
	unsigned int mask;
	unsigned int shift;
	spinlock_t *lock;
};

#define to_clk_mmio_mux(_hw) \
	container_of(to_clk_reg(_hw), struct clk_mmio_mux, base)
#define __clk_mmio_mux_hw(_ptr) __clk_reg_hw(&(_ptr)->base)

extern const struct clk_ops clk_mmio_mux_ops;

#endif
