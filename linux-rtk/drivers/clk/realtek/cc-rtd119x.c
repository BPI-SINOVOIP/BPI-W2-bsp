/*
 * cc-rtd119x.c - RTD119x clock controller
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corporation
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
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/bitops.h>
#include <linux/platform_device.h>
#include "common.h"
#include "clk-pll.h"
#include "clk-mmio-gate.h"
#include "clk-mmio-mux.h"
#include "clk_regmap.h"
#include <dt-bindings/clock/rtk,clock-rtd119x.h>

#define DEFAULT_PARENT_OSC27M    (const char *[]){ "osc27M" }
static DEFINE_SPINLOCK(clk_div_lock);

#define NF_MASK    0x1FFFFC00
#define MNO_MASK   0x030FF800
#define MN_MASK    0x07FC0000

#define CLK_PLL_TYPE_NF       \
	(CLK_PLL_CONF_FREQ_LOC_CTL2)
#define CLK_PLL_TYPE_MNO      \
	(CLK_PLL_CONF_FREQ_LOC_CTL1 | CLK_PLL_CONF_POW_LOC_CTL2)
#define CLK_PLL_TYPE_MN       \
	(CLK_PLL_CONF_FREQ_LOC_CTL1 | CLK_PLL_CONF_POW_LOC_CTL3)

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
	_D(600000000, 1, SCPU_FREQ_DIV1),
	_D(290000000, 2, SCPU_FREQ_DIV2),
	_D(1,         4, SCPU_FREQ_DIV4),
	DIV_TABLE_END
};

static const struct div_table scpu_div_tbl_rev2[] = {
	_D(700000000, 1, SCPU_FREQ_DIV1),
	_D(350000000, 2, SCPU_FREQ_DIV2),
	_D(290000000, 4, SCPU_FREQ_DIV4),
	DIV_TABLE_END
};

static const struct freq_table scpu_tbl[] = {
	_NF(720000000,  25, 1364),
	_NF(780000000,  27, 1820),
	_NF(800000000,  28, 1290),
	_NF(1000000000, 36,   75),
	_NF(1160000000, 41, 1159),
	_NF(1200000000, 43,  910),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_scpu = {
	.div_offset = PLL_DIV,
	.div_shift  = SCPU_FREQ_SEL_SHIFT,
	.div_width  = SCPU_FREQ_SEL_WIDTH,
	.div_tbl    = scpu_div_tbl_rev2,
	.lock       = &clk_div_lock,
	.clkp       = {
		.conf         = CLK_PLL_TYPE_NF,
		.pll_offset   = PLL_SCPU1,
		.freq_tbl     = scpu_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name         = "pll_scpu",
			.ops          = &clk_pll_div_ops,
			.parent_names = DEFAULT_PARENT_OSC27M,
			.num_parents  = 1,
			.flags        = CLK_IGNORE_UNUSED |
					CLK_GET_RATE_NOCACHE,
		},
	},
};

static const struct div_table bus_div_tbl[] = {
	_D(250000000, 2, BUS_FREQ_DIV1),
	_D(1,         4, BUS_FREQ_DIV2),
	DIV_TABLE_END
};

static const struct freq_table bus_tbl[] = {
	_MN(459000000, 15, 0),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_bus = {
	.div_offset = PLL_DIV,
	.div_shift  = BUS_FREQ_SEL_SHIFT,
	.div_width  = BUS_FREQ_SEL_WIDTH,
	.div_tbl    = bus_div_tbl,
	.lock       = &clk_div_lock,
	.clkp       = {
		.conf         = CLK_PLL_TYPE_MN,
		.pll_offset   = PLL_BUS1,
		.freq_tbl     = bus_tbl,
		.base.hw.init = &(struct clk_init_data) {
			.name         = "pll_bus",
			.ops          = &clk_pll_div_ops,
			.parent_names = DEFAULT_PARENT_OSC27M,
			.num_parents  = 1,
			.flags        = CLK_IGNORE_UNUSED |
					CLK_GET_RATE_NOCACHE,
		},
	},
};

static struct clk_fixed_factor clk_sys = {
	.div     = 1,
	.mult    = 1,
	.hw.init = &(struct clk_init_data) {
		.name         = "clk_sys",
		.ops          = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_bus" },
		.num_parents  = 1,
		.flags        = 0,
	},
};

static const struct freq_table dcsb_tbl[] = {
	_MN(351000000, 11, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_dcsb = {
	.pll_offset   = PLL_DCSB1,
	.freq_tbl     = dcsb_tbl,
	.conf         = CLK_PLL_TYPE_MN,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_dcsb",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_fixed_factor clk_sysh = {
	.div     = 1,
	.mult    = 1,
	.hw.init = &(struct clk_init_data) {
		.name         = "clk_sysh",
		.ops          = &clk_fixed_factor_ops,
		.parent_names = (const char *[]){ "pll_dscb" },
		.num_parents  = 1,
		.flags        = CLK_SET_RATE_PARENT,
	},
};

static const struct freq_table gpu_tbl[] = {
	_MNO(378000000, 12, 0, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_gpu = {
	.conf         = CLK_PLL_TYPE_MNO,
	.pll_offset   = PLL_GPU1,
	.freq_tbl     = gpu_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_gpu",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_composite_init_data clk_gpu_init = {
	.mux_offset   = CLK_OFFSET_INVALID,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_GPU,
	.parent_names =  (const char *[]){ "pll_gpu", },
	.num_parents  = 1,
	.name         = "clk_gpu",
	.flags = CLK_SET_RATE_PARENT,

};

static const struct freq_table vcpu_tbl[] = {
	_MNO(243000000,  7, 0, 0),
	_MNO(324000000, 10, 0, 0),
	_MNO(405000000, 13, 0, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_vcpu = {
	.conf         = CLK_PLL_TYPE_MNO,
	.pll_offset   = PLL_VPU1,
	.freq_tbl     = vcpu_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_vcpu",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_composite_init_data clk_ve_init = {
	.mux_offset   = CLK_OFFSET_INVALID,
	.gate_offset  = CLOCK_ENABLE2,
	.gate_shift   = CLK_EN_VCPU,
	.parent_names = (const char *[]){ "pll_vcpu", },
	.num_parents  = 1,
	.name         = "clk_ve",
	.flags        = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve1_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE1_SEL_WIDTH,
	.mux_shift    = CLK_VE1_SEL_SHIFT,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_VE_H264,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_ve",
		"clk_ve",
	},
	.num_parents  = 4,
	.name         = "clk_ve1",
	.flags        = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE2_SEL_WIDTH,
	.mux_shift    = CLK_VE2_SEL_SHIFT,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_VE_H265,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_ve",
		"clk_ve",
	},
	.num_parents  = 4,
	.name         = "clk_ve2",
	.flags        = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_bpu_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE2_BPU_SEL_WIDTH,
	.mux_shift    = CLK_VE2_BPU_SEL_SHIFT,
	.gate_offset  = CLK_OFFSET_INVALID,
	.parent_names =  (const char *[]){
		"clk_sys",
		"clk_sysh",
		"clk_gpu",
		"clk_gpu",
	},
	.num_parents  = 4,
	.name         = "clk_ve2_bpu",
	.flags        = CLK_IGNORE_UNUSED | CLK_SET_RATE_PARENT |
			CLK_SET_RATE_NO_REPARENT,
};

static struct clk_hw *clk_reg_list[] = {
	[CC_PLL_SCPU]   = &__clk_pll_div_hw(&pll_scpu),
	[CC_PLL_BUS]    = &__clk_pll_div_hw(&pll_bus),
	[CC_PLL_DCSB]   = &__clk_pll_hw(&pll_dcsb),
	[CC_PLL_GPU]    = &__clk_pll_hw(&pll_gpu),
	[CC_PLL_VCPU]   = &__clk_pll_hw(&pll_vcpu),
	[CC_CLK_SYS]    = &clk_sys.hw,
	[CC_CLK_SYSH]   = &clk_sysh.hw,
};

static struct clk_composite_init_data *composite_clks[] = {
	[CC_CLK_GPU]     = &clk_gpu_init,
	[CC_CLK_VE]      = &clk_ve_init,
	[CC_CLK_VE1]     = &clk_ve1_init,
	[CC_CLK_VE2]     = &clk_ve2_init,
	[CC_CLK_VE2_BPU] = &clk_ve2_bpu_init,
};

static int rtd119x_cc_init_clocks(struct device *dev)
{
	struct cc_platform_data *ccd = dev_get_drvdata(dev);
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
			dev_err(dev, "%s: failed in cc_init_hw: %d\n",
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
			dev_err(dev, "%s: failed in cc_init_composite_clk: %d\n",
				name, ret);
			continue;
		}
	}

	return 0;
}

static int rtd119x_cc_probe(struct platform_device *pdev)
{
	struct cc_platform_data *ccd;

	ccd = devm_cc_alloc_platform_data(&pdev->dev, CC_CLK_MAX);
	if (!ccd)
		return -ENOMEM;

	platform_set_drvdata(pdev, ccd);
	return cc_probe_platform(pdev, ccd, rtd119x_cc_init_clocks);
}

static const struct of_device_id rtd119x_cc_match[] = {
	{ .compatible = "realtek,clock-controller", },
	{}
};

static struct platform_driver rtd119x_cc_driver = {
	.probe = rtd119x_cc_probe,
	.driver = {
		.name = "rtk-rtd119x-cc",
		.of_match_table = rtd119x_cc_match,
		.pm = &cc_pm_ops,
	},
};

static int __init rtd119x_cc_init(void)
{
	return platform_driver_register(&rtd119x_cc_driver);
}
core_initcall(rtd119x_cc_init);
