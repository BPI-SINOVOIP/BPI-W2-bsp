/*
 * cc-rtd119x.c - RTD119x clock controller
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
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
#include <dt-bindings/clock/rtk,clock-rtd119x.h>

static DEFINE_SPINLOCK(clk_div_lock);

#define NF_MASK    0x1FFFFC00
#define MNO_MASK   0x030FF800
#define MN_MASK    0x07FC0000

#define _D(_rate, _div, _val) \
{ \
	.rate = _rate, \
	.div = _div, \
	.val = _val, \
}

#define _NF(_rate, _n, _f) \
{ \
	.rate = _rate, \
	.mask = NF_MASK, \
	.val = ((_n) << 21) | ((_f) << 10), \
}

#define _MNO(_rate, _m, _n, _o) \
{ \
	.rate = _rate, \
	.mask = MNO_MASK, \
	.val = ((_m) << 11) | ((_n) << 18) | ((_o) << 24), \
}

#define _MN(_rate, _m, _n) \
{ \
	.rate = _rate, .mask = MN_MASK, \
	.val = ((_m) << 18) | ((_n) << 25), \
}

static const struct div_table scpu_div_tbl[] = {
	_D(600000000, 1, 0),
	_D(290000000, 2, 2),
	/* for div-reg map */
	_D(0, 1, 1),
	_D(0, 4, 3),
	DIV_TABLE_END
};

static const struct div_table scpu_div_tbl_rev2[] = {
	_D(700000000, 1, 0),
	_D(350000000, 2, 2),
	_D(290000000, 4, 3),
	/* for div-reg map */
	_D(0, 1, 1),
	DIV_TABLE_END
};
// 03942801
static const struct freq_table scpu_tbl[] = {
	_NF(780000000,  27, 1820),
	_NF(800000000,  28, 1290),
	_NF(1000000000, 36,   75),
	_NF(1160000000, 41, 1159),
	_NF(1200000000, 43,  910),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_scpu = {
	.div_offset = 0x30,
	.div_shift  = 7,
	.div_width  = 2,
	.div_tbl = scpu_div_tbl_rev2,
	.lock = &clk_div_lock,
	.clkp = {
		.flags = 0,
		.pow_offset = CLK_OFFSET_INVALID,
		.pll_offset = 0x104,
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

static const struct div_table bus_div_tbl[] = {
	_D(250000000, 2, 0),
	_D(0, 4, 1),
	DIV_TABLE_END
};

static const struct freq_table bus_tbl[] = {
	_MN(459000000, 15, 0),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_bus = {
	.div_offset = 0x30,
	.div_shift  = 0,
	.div_width  = 1,
	.div_tbl = bus_div_tbl,
	.lock = &clk_div_lock,
	.clkp = {
		.flags = 0,
		.pll_offset = 0x164,
		.pow_offset = 0x16c,
		.freq_tbl   = bus_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name = "pll_bus",
			.ops  = &clk_pll_div_ops,
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
		.ops  = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_bus" },
		.num_parents = 1,
		.flags = 0,
	},
};

static const struct freq_table dcsb_tbl[] = {
	_MN(351000000, 11, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_dcsb = {
	.flags = 0,
	.pll_offset = 0x1b0,
	.pow_offset = 0x1b8,
	.freq_tbl   = dcsb_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_dcsb",
		.ops  = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_fixed_factor clk_sysh = {
	.div = 1,
	.mult = 1,
	.hw.init = &(struct clk_init_data) {
		.name = "clk_sysh",
		.ops  = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_dscb" },
		.num_parents = 1,
		.flags = 0,
	},
};

static const struct freq_table gpu_tbl[] = {
	_MNO(378000000, 12, 0, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_gpu = {
	.flags = 0,
	.pll_offset = 0x1c0,
	.pow_offset = 0x1c4,
	.freq_tbl = gpu_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_gpu",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	},
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT,
};

static struct clk_composite_init_data clk_gpu_init = {
	.mux_offset = CLK_OFFSET_INVALID,
	.gate_offset = 0x0c,
	.gate_shift = CLK_EN_GPU,
	.parent_names =  (const char *[]){
		"pll_gpu",
	},
	.num_parents = 1,
	.name = "clk_gpu",

};

static const struct freq_table vcpu_tbl[] = {
	_MNO(324000000, 10, 0, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_vcpu = {
	.flags = 0,
	.pll_offset = 0x114,
	.pow_offset = 0x118,
	.freq_tbl = vcpu_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name = "pll_vcpu",
		.ops = &clk_pll_ops,
		.parent_names = (const char *[]){ "osc27M" },
		.num_parents = 1,
		.flags = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_composite_init_data clk_ve_init = {
	.mux_offset  = CLK_OFFSET_INVALID,
	.gate_offset = 0x10,
	.gate_shift  = CLK_EN_VCPU,
	.parent_names =  (const char *[]){
		"pll_vcpu",
	},
	.num_parents = 1,
	.name = "clk_ve",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve1_init = {
	.mux_offset = 0x4c,
	.mux_width = 2,
	.mux_shift = 0,
	.gate_offset = 0x0c,
	.gate_shift = CLK_EN_VE_H264,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_ve",
		"clk_ve",
	},
	.num_parents = 4,
	.name = "clk_ve1",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_init = {
	.mux_offset = 0x4c,
	.mux_width = 2,
	.mux_shift = 2,
	.gate_offset = 0x0c,
	.gate_shift = CLK_EN_VE_H265,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_ve",
		"clk_ve",
	},
	.num_parents = 4,
	.name = "clk_ve2",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_bpu_init = {
	.mux_offset = 0x4c,
	.mux_width = 2,
	.mux_shift = 4,
	.gate_offset = CLK_OFFSET_INVALID,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_gpu",
		"clk_gpu",
	},
	.num_parents = 4,
	.name = "clk_ve2_bpu",
	.flags = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
		CLK_SET_RATE_NO_REPARENT,
};

static __initdata struct clk_hw *clk_reg_list[] = {
	[CC_PLL_SCPU]   = &__clk_pll_div_hw(&pll_scpu),
	[CC_PLL_BUS]    = &__clk_pll_div_hw(&pll_bus),
	[CC_PLL_DCSB]   = &__clk_pll_hw(&pll_dcsb),
	[CC_PLL_GPU]    = &__clk_pll_hw(&pll_gpu),
	[CC_PLL_VCPU]   = &__clk_pll_hw(&pll_vcpu),
	[CC_CLK_SYS]    = &clk_sys.hw,
	[CC_CLK_SYSH]   = &clk_sysh.hw,
};

static  __initdata struct clk_composite_init_data *composite_clks[] = {
	[CC_CLK_GPU]     = &clk_gpu_init,
	[CC_CLK_VE]      = &clk_ve_init,
	[CC_CLK_VE1]     = &clk_ve1_init,
	[CC_CLK_VE2]     = &clk_ve2_init,
	[CC_CLK_VE2_BPU] = &clk_ve2_bpu_init,
};

int __init cc_init_clocks(struct device *dev)
{
	struct cc_desc *ccd = dev_get_drvdata(dev);
	int i;
	int ret;

	// TODO: check chip rev and (re)set scpu pll div table

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

	return 0;
}

int cc_clock_num(void)
{
	return CC_CLK_MAX;
}
