/*
 * clk-mmio-gate.h - gating clock with regmap
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __CLK_REALTEK_CLK_MMIO_GATE_H
#define __CLK_REALTEK_CLK_MMIO_GATE_H

#include "common.h"
#include <soc/realtek/rdbg.h>

/**
 * struct clk_mmio_gate - gating clock with regmap
 *
 * @base:        handle for common, hw and register access interfaces
 * @gate_offset: offset from base register
 * @bit_idx:     bit index of gating bit field
 * @shift:       shift to gating bit field
 * @lock:        register lock
 * @flags:       clk_mmio_gate flags
 * @ref:         debug reference
 *
 * Flags:
 * CLK_MMIO_GATE_HAS_WRITE_EN - set write_en bit in (bit_idx+1)
 */
struct clk_mmio_gate {
	struct clk_reg base;
	int gate_offset;
	u8 bit_idx;
	spinlock_t *lock;
	unsigned int flags;

	struct rdbg_info *ref;
};

#define to_clk_mmio_gate(_hw) \
	container_of(to_clk_reg(_hw), struct clk_mmio_gate, base)
#define __clk_mmio_gate_hw(_ptr) __clk_reg_hw(&(_ptr)->base)

/* clk_mmio_gate flags */
#define CLK_MMIO_GATE_HAS_WRITE_EN 0x1

extern const struct clk_ops clk_mmio_gate_ops;

#endif
