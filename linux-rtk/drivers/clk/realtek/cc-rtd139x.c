/*
 * cc-rtd139x.c - RTD139x clock controller
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "rtk-clk: " fmt

#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/bitops.h>
#include "common.h"
#include "clk-pll.h"
#include "clk-mmio-gate.h"
#include "clk-mmio-mux.h"
#include <dt-bindings/clock/rtk,clock-rtd139x.h>

static DEFINE_SPINLOCK(clk_div_lock);

#define _D(_rate, _div, _val) \
{ \
	.rate = _rate, \
	.div = _div, \
	.val = _val, \
}

#define _NF(_rate, _n, _f) \
{ \
	.rate = _rate, \
	.mask = 0x7FFFF, \
	.val = ((_n) << 11) | (_f), \
}

#define _MNO(_rate, _m, _n, _o) \
{ \
	.rate = _rate, \
	.mask = 0x63FF0, \
	.val = ((_m) << 4) | ((_n) << 12) | ((_o) << 17), \
}

#define SCPU_FREQ_SEL1  0x02
#define SCPU_FREQ_SEL7  0x80

#define SCPU_FREQ_DIV1   (1)

#define SCPU_FREQ_DIV2   (0 | SCPU_FREQ_SEL1)
#define SCPU_FREQ_DIV4   (1 | SCPU_FREQ_SEL1)

#define SCPU_FREQ_DIV3   ((3 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV5   ((5 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV6   ((6 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV7   ((7 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV8   ((8 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV10  ((10 << 2) | SCPU_FREQ_SEL7)
#define SCPU_FREQ_DIV13  ((13 << 2) | SCPU_FREQ_SEL7)

#define SCPU_FREQ_DUMMY0  (0)
#define SCPU_FREQ_DUMMY1  (0 | SCPU_FREQ_SEL7)

static const struct div_table scpu_div_tbl[] = {
	_D(1000000000,  1, SCPU_FREQ_DIV1),
	_D(500000000,   2, SCPU_FREQ_DIV2),
	_D(250000000,   4, SCPU_FREQ_DIV4),
	_D(200000000,   8, SCPU_FREQ_DIV8),
	_D(100000000,  10, SCPU_FREQ_DIV10),
	/* special cases, only for mapping val and div */
	_D(-1,  1, SCPU_FREQ_DUMMY0),
	_D(-1,  3, SCPU_FREQ_DUMMY1),
	DIV_TABLE_END
};

static const struct freq_table scpu_tbl[] = {
	_NF(1000000000, 34,   75),
	_NF(1100000000, 37, 1517),
	_NF(1200000000, 41,  910),
	_NF(1300000000, 45,  303),
	_NF(1400000000, 48, 1745),
	_NF(1500000000, 52, 1137),
	_NF(1600000000, 56,  530),
	_NF(1800000000, 63, 1365),
	/* special cases */
	_NF(1000000000, 35,    0),
	_NF(1800000000, 65,    0),
	_NF(1800000000, 64,    0),
	_NF(1400000001, 45,  301),
	_NF(1500000001, 45,  302),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_scpu = {
	.div_offset = 0x30,
	.div_shift  = 6,
	.div_width  = 8,
	.div_tbl = scpu_div_tbl,
	.lock = &clk_div_lock,
	.clkp = {
		.flags = CLK_PLL_LSM_STEP_HIGH,
		.ssc_offset = 0x500,
		.pll_offset = 0x504,
		.rdy_offset = 0x51c,
		.pow_offset = CLK_OFFSET_INVALID,
		.freq_tbl = scpu_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name = "pll_scpu",
			.ops = &clk_pll_div_ops,
			.parent_names = (const char *[]){ "osc27M" },
			.num_parents = 1,
			.flags = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
		},
	},
};

#define BUS_FREQ_DIV1  1
#define BUS_FREQ_DIV2  2
#define BUS_FREQ_DIV4  3

static const struct div_table bus_div_tbl[] = {
	_D(257000000,  1, BUS_FREQ_DIV1),
	_D(129000000,  2, BUS_FREQ_DIV2),
	_D(65000000,   4, BUS_FREQ_DIV4),
	_D(-1,  1, 0),
	DIV_TABLE_END
};

/* NOTE: PDIV = 1 */
static const struct freq_table bus_tbl[] = {
	_NF(513000000, 35,    0),
	_NF(400000000, 26, 1289),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_bus = {
	.div_offset = 0x30,
	.div_shift  = 0,
	.div_width  = 2,
	.div_tbl = bus_div_tbl,
	.lock = &clk_div_lock,
	.clkp = {
		.ssc_offset = 0x520,
		.pll_offset = 0x524,
		.rdy_offset = 0x53c,
		.pow_offset = CLK_OFFSET_INVALID,
		.freq_tbl = bus_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name = "pll_bus",
			.ops = &clk_pll_div_ops,
			.parent_names = (const char *[]){ "osc27M" },
			.num_parents = 1,
			.flags = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
		},
	},
};

static struct clk_fixed_factor clk_sys = {
	.div = 1,
	.mult = 1,
	.hw.init = &(struct clk_init_data) {
		.name = "clk_sys",
		.ops = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_bus" },
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	},
};

static struct clk_mmio_mux clk_sys_sb2 = {
	.mux_offset = 0x18,
	.mask = BIT(1) - 1,
	.shift = 0,
	.base.hw.init = &(struct clk_init_data) {
		.name = "clk_sys_sb2",
		.ops = &clk_mmio_mux_ops,
		.parent_names = (const char *[]){
			"clk_sys",
			"osc27M",
		},
		.num_parents = 2,
		.flags = 0,
	},
};

static int clk_sys_sb2_notifier(struct notifier_block *nb, unsigned long action,
	void *data)
{
	struct clk_hw *hw = &clk_sys_sb2.base.hw, *phw = NULL;

	switch (action) {
	case PRE_RATE_CHANGE:
		phw = clk_hw_get_parent_by_index(hw, 1);
		break;

	case POST_RATE_CHANGE:
	case ABORT_RATE_CHANGE:
		phw = clk_hw_get_parent_by_index(hw, 0);
		break;
	}

	if (phw)
		clk_set_parent(hw->clk, phw->clk);
	return NOTIFY_OK;
}

static struct notifier_block clk_sys_sb2_nb = {
	.notifier_call = clk_sys_sb2_notifier,
};

#define DCSB_FREQ_DIV1  1
#define DCSB_FREQ_DIV2  2
#define DCSB_FREQ_DIV4  3

static const struct div_table bus_h_div_tbl[] = {
	_D(250000000,  1, DCSB_FREQ_DIV1),
	_D(125000000,  2, DCSB_FREQ_DIV2),
	_D(62500000,   4, DCSB_FREQ_DIV4),
	_D(-1, 1, 0),
	DIV_TABLE_END
};

/* NOTE: PDIV = 1 */
static const struct freq_table bus_h_tbl[] = {
	_NF(500000000, 34,    0),
	_NF(450000000, 30,  682),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_bus_h = {
	.div_offset = 0x30,
	.div_shift  = 2,
	.div_width  = 2,
	.div_tbl = bus_h_div_tbl,
	.lock = &clk_div_lock,
	.clkp = {
		.ssc_offset = 0x540,
		.pll_offset = 0x544,
		.rdy_offset = 0x55c,
		.pow_offset = CLK_OFFSET_INVALID,
		.freq_tbl = bus_h_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name = "pll_bus_h",
			.ops = &clk_pll_div_ops,
			.parent_names = (const char *[]){ "osc27M" },
			.num_parents = 1,
			.flags = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
		},
	},
};

static struct clk_fixed_factor clk_sysh = {
	.div = 1,
	.mult = 1,
	.hw.init = &(struct clk_init_data) {
		.name = "clk_sysh",
		.ops = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_bus_h" },
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	},
};

static const struct freq_table ddsx_tbl[] = {
	_NF(432000000, 13, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_ddsa = {
	.ssc_offset = 0x560,
	.pll_offset = 0x564,
	.rdy_offset = 0x57c,
	.pow_offset = 0x128,
	.freq_tbl = ddsx_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_ddsa",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_pll pll_ddsb = {
	.ssc_offset = 0x580,
	.pll_offset = 0x584,
	.rdy_offset = 0x59c,
	.pow_offset = 0x178,
	.freq_tbl = ddsx_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_ddsb",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	},
};

static const struct freq_table gpu_tbl[] = {
	_NF(300000000, 19,  455),
	_NF(400000000, 26, 1289),
	_NF(500000000, 34,   75),
	_NF(600000000, 41,  910),
	_NF(700000000, 48, 1745),
	_NF(750000000, 52, 1137),
	_NF(800000000, 56,  530),
	_NF(850000000, 59, 1971),
	FREQ_TABLE_END
};

static struct clk_pll pll_gpu = {
	.ssc_offset = 0x5a0,
	.pll_offset = 0x5a4,
	.rdy_offset = 0x5bc,
	.pow_offset = 0x1c4,
	.freq_tbl = gpu_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_gpu",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE | CLK_SET_RATE_UNGATE,
	},
};

static struct clk_composite_init_data clk_gpu_init = {
	.mux_offset = CLK_OFFSET_INVALID,
	.gate_offset = 0x0c,
	.gate_shift = 11,
	.parent_names =  (const char *[]){ "pll_gpu" },
	.num_parents = 1,
	.name = "clk_gpu",
	.flags = CLK_SET_RATE_PARENT | CLK_IGNORE_UNUSED,
};

static struct freq_table ve_tbl[] = {
	_MNO(189000000, 12, 0, 1),
	_MNO(270000000, 18, 0, 1),
	_MNO(405000000, 13, 0, 0),
	_MNO(432000000, 14, 0, 0),
	_MNO(459000000, 15, 0, 0),
	_MNO(486000000, 16, 0, 0),
	_MNO(513000000, 17, 0, 0),
	_MNO(540000000, 18, 0, 0),
	_MNO(550000000, 59, 2, 0), // = (59+2) * 27/3
	_MNO(567000000, 19, 0, 0),
	_MNO(594000000, 20, 0, 0),
	_MNO(648000000, 22, 0, 0),
	_MNO(675000000, 23, 0, 0),
	_MNO(702000000, 24, 0, 0),
	_MNO(715000000, 51, 1, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_ve1 = {
	.ssc_offset = CLK_OFFSET_INVALID,
	.pll_offset = 0x114,
	.rdy_offset = CLK_OFFSET_INVALID,
	.pow_offset = 0x118,
	.freq_tbl = ve_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_ve1",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_pll pll_ve2 = {
	.ssc_offset = CLK_OFFSET_INVALID,
	.pll_offset = 0x1d0,
	.rdy_offset = CLK_OFFSET_INVALID,
	.pow_offset = 0x1d4,
	.freq_tbl = ve_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_ve2",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_composite_init_data clk_ve1_init = {
	.mux_offset = 0x4c,
	.mux_width = 3,
	.mux_shift = 0,
	.gate_offset = 0x0c,
	.gate_shift = 12,
	.parent_names =  (const char *[]){
		"pll_ve1",
		"pll_ve2",
		"clk_sysh",
		"clk_sysh",
		"pll_ddsa",
	},
	.num_parents = 5,
	.name = "clk_ve1",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_init = {
	.mux_offset = 0x4c,
	.mux_width = 3,
	.mux_shift = 3,
	.gate_offset = 0x0c,
	.gate_shift = 13,
	.parent_names =  (const char *[]){
		"pll_ve1",
		"pll_ve2",
		"clk_sysh",
		"clk_sysh",
		"pll_ddsa",
	},
	.num_parents = 5,
	.name = "clk_ve2",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_bpu_init = {
	.mux_offset = 0x4c,
	.mux_width = 3,
	.mux_shift = 9,
	.gate_offset = CLK_OFFSET_INVALID,
	.parent_names =  (const char *[]){
		"pll_ve1",
		"pll_ve2",
		"clk_sysh",
		"clk_sysh",
		"pll_ddsa",
	},
	.num_parents = 5,
	.name = "clk_ve2_bpu",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static __initdata struct clk_hw *clk_reg_list[] = {
	[CC_PLL_SCPU]   = &__clk_pll_div_hw(&pll_scpu),
	[CC_PLL_BUS]    = &__clk_pll_div_hw(&pll_bus),
	[CC_PLL_BUS_H]  = &__clk_pll_div_hw(&pll_bus_h),
	[CC_PLL_DDSA]   = &__clk_pll_hw(&pll_ddsa),
	[CC_PLL_DDSB]   = &__clk_pll_hw(&pll_ddsb),
	[CC_PLL_GPU]    = &__clk_pll_hw(&pll_gpu),
	[CC_PLL_VE1]    = &__clk_pll_hw(&pll_ve1),
	[CC_PLL_VE2]    = &__clk_pll_hw(&pll_ve2),
	[CC_CLK_SYS_SB2] = &__clk_mmio_mux_hw(&clk_sys_sb2),
	[CC_CLK_SYS]  = &clk_sys.hw,
	[CC_CLK_SYSH] = &clk_sysh.hw,
};

static  __initdata struct clk_composite_init_data *composite_clks[] = {
	[CC_CLK_GPU] = &clk_gpu_init,
	[CC_CLK_VE1] = &clk_ve1_init,
	[CC_CLK_VE2] = &clk_ve2_init,
	[CC_CLK_VE2_BPU] = &clk_ve2_bpu_init,
};

int __init cc_init_clocks(struct device *dev)
{
	struct cc_desc *ccd = dev_get_drvdata(dev);
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(clk_reg_list); i++) {
		struct clk_hw *hw = clk_reg_list[i];
		const char *name;

		if (!hw)
			continue;

		name = hw->init->name;
		ret = cc_init_hw(dev, ccd, i, hw);
		if (ret) {
			dev_err(dev, "%s: cc_init_hw() returns %d\n",
				name, ret);
			continue;
		}
	}

	for (i = 0; i < ARRAY_SIZE(composite_clks); i++) {
		struct clk_composite_init_data *data = composite_clks[i];
		const char *name;

		if (!data)
			continue;

		name = data->name;
		ret = cc_init_composite_clk(dev, ccd, i, data);
		if (ret) {
			dev_err(dev, "%s: cc_init_composite_clk() returns %d\n",
				name, ret);
			continue;
		}
	}

	if (clk_sys.hw.clk && clk_sys_sb2.base.hw.clk)
		clk_notifier_register(clk_sys.hw.clk, &clk_sys_sb2_nb);

	return 0;
}

int cc_clock_num(void)
{
	return CC_CLK_MAX;
}
