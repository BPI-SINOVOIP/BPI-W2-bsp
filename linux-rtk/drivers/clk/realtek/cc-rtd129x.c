/*
 * cc-rtd129x.c - RTD129x clock controller
 *
 * Copyright (C) 2017,2019 Realtek Semiconductor Corporation
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
#include <dt-bindings/clock/rtk,clock-rtd129x.h>

#define DEFAULT_PARENT_OSC27M    (const char *[]){ "osc27M" }
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

#define CLK_PLL_TYPE_SSC                \
	(CLK_PLL_CONF_FREQ_LOC_SSC1)
#define CLK_PLL_TYPE_SSC_POW0           \
	(CLK_PLL_CONF_FREQ_LOC_SSC1 | CLK_PLL_CONF_POW_LOC_CTL2)
#define CLK_PLL_TYPE_SSC_POW1           \
	(CLK_PLL_CONF_FREQ_LOC_SSC1 | CLK_PLL_CONF_POW_LOC_CTL3)
#define CLK_PLL_TYPE_POW                \
	(CLK_PLL_CONF_FREQ_LOC_CTL1 | CLK_PLL_CONF_POW_LOC_CTL2)

static const struct div_table scpu_div_tbl[] = {
	_D(1000000000, 1, SCPU_FREQ_DIV1),
	_D(500000000,  2, SCPU_FREQ_DIV2),
	_D(250000000,  4, SCPU_FREQ_DIV4),
	DIV_TABLE_END
};

static const struct freq_table scpu_tbl[] = {
	_NF(1000000000, 34,   75),
	_NF(1100000000, 37, 1517),
	_NF(1200000000, 41,  910),
	_NF(1300000000, 45,  303),
	_NF(1400000000, 48, 1745),
	_NF(1500000000, 52, 1137),
	_NF(1600000000, 56,  531),
	_NF(1800000000, 63, 1365),
	/* special cases */
	_NF(1200000000, 41, 1024),
	_NF(1300000000, 45, 1024),
	_NF(1503000000, 48, 1744),
	FREQ_TABLE_END
};

static struct clk_pll_div pll_scpu = {
	.div_offset = PLL_DIV,
	.div_shift  = SCPU_FREQ_SEL_SHIFT,
	.div_width  = SCPU_FREQ_SEL_WIDTH,
	.div_tbl    = scpu_div_tbl,
	.lock       = &clk_div_lock,
	.clkp       = {
		.conf         = CLK_PLL_TYPE_SSC,
		.flags        = CLK_PLL_DIV_WORKAROUND,
		.ssc_offset   = PLL_SSC_DIG_SCPU0,
		.pll_offset   = CLK_OFFSET_INVALID,
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

static const struct freq_table bus_tbl[] = {
	_NF(200000000,  4,  835),
	_NF(243000000,  6,    0),
	_NF(256000000,  6, 1024),
	_NF(256000000,  6,  986),
	_NF(257000000,  6, 1061),
	_NF(459000000, 14,    0),
	_NF(486000000, 15,    0),
	_NF(482000000, 14, 1744),
	_NF(513000000, 16,    0),
	_NF(540000000, 17,    0),
	FREQ_TABLE_END
};

static const struct div_table bus_div_tbl[] = {
	_D(256000000,  1, BUS_FREQ_DIV1),
	_D(1,          2, BUS_FREQ_DIV2),
	DIV_TABLE_END
};

static struct clk_pll_div pll_bus = {
	.div_offset = PLL_DIV,
	.div_shift  = BUS_FREQ_SEL_SHIFT,
	.div_width  = BUS_FREQ_SEL_WIDTH,
	.div_tbl    = bus_div_tbl,
	.lock       = &clk_div_lock,
	.clkp       = {
		.conf         = CLK_PLL_TYPE_SSC,
		.ssc_offset   = PLL_SSC_DIG_BUS0,
		.pll_offset   = CLK_OFFSET_INVALID,
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
		.flags        = CLK_SET_RATE_PARENT,
	},
};


static struct clk_mmio_mux clk_sys_sb2 = {
	.mux_offset   = GROUP1_CK_SEL,
	.mask         = BIT(1) - 1,
	.shift        = 0,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "clk_sys_sb2",
		.ops          = &clk_mmio_mux_ops,
		.parent_names = (const char *[]){ "clk_sys", "osc27M", },
		.num_parents  = 2,
		.flags        = 0,
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

static struct clk_pll pll_bus_h = {
	.conf         = CLK_PLL_TYPE_SSC,
	.ssc_offset   = PLL_SSC_DIG_BUSH0,
	.pll_offset   = CLK_OFFSET_INVALID,
	.freq_tbl     = bus_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_bus_h",
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
		.parent_names = (const char *[]){ "pll_bus_h" },
		.num_parents  = 1,
		.flags        = CLK_SET_RATE_PARENT,
	},
};

static const struct freq_table ddsx_tbl[] = {
	_NF(432000000, 13, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_ddsa = {
	.conf         = CLK_PLL_TYPE_SSC_POW1,
	.ssc_offset   = PLL_SSC_DIG_DDSA0,
	.pll_offset   = PLL_DDSA1,
	.freq_tbl     = ddsx_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_ddsa",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_IGNORE_UNUSED | CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_pll pll_ddsb = {
	.conf         = CLK_PLL_TYPE_SSC_POW0,
	.ssc_offset   = PLL_SSC_DIG_DDSB0,
	.pll_offset   = PLL_DDSB1,
	.freq_tbl     = ddsx_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_ddsb",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_GET_RATE_NOCACHE,
	},
};

static const struct freq_table gpu_tbl[] = {
	_NF(300000000,  8,  227),
	_NF(320000000,  8, 1744),
	_NF(340000000,  9, 1213),
	_NF(360000000, 10,  682),
	_NF(380000000, 11,  151),
	_NF(400000000, 11, 1668),
	_NF(420000000, 12, 1137),
	_NF(440000000, 13,  606),
	_NF(460000000, 14,   75),
	_NF(480000000, 14, 1592),
	_NF(500000000, 15, 1061),
	_NF(520000000, 16,  530),
	_NF(540000000, 17,    0),
	_NF(560000000, 17, 1517),
	_NF(580000000, 18,  986),
	_NF(600000000, 19,  455),
	_NF(620000000, 19, 1972),
	_NF(640000000, 20, 1441),
	_NF(660000000, 21,  910),
	_NF(680000000, 22,  379),
	_NF(460000000, 13, 1365),
	FREQ_TABLE_END
};

static struct clk_pll pll_gpu = {
	.conf         = CLK_PLL_TYPE_SSC_POW0,
	.ssc_offset   = PLL_SSC_DIG_GPU0,
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
	.parent_names = (const char *[]){ "pll_gpu" },
	.num_parents  = 1,
	.name         = "clk_gpu",
	.flags        = CLK_SET_RATE_PARENT,
};

static struct freq_table ve_tbl[] = {
	_MNO(189000000,  5, 0, 0),
	_MNO(270000000,  8, 0, 0),
	_MNO(405000000, 13, 0, 0),
	_MNO(432000000, 14, 0, 0),
	_MNO(459000000, 15, 0, 0),
	_MNO(486000000, 16, 0, 0),
	_MNO(513000000, 17, 0, 0),
	_MNO(540000000, 18, 0, 0),
	_MNO(567000000, 19, 0, 0),
	_MNO(594000000, 20, 0, 0),
	_MNO(648000000, 22, 0, 0),
	_MNO(675000000, 23, 0, 0),
	_MNO(702000000, 24, 0, 0),
	_MNO(715000000, 51, 1, 0),
	FREQ_TABLE_END
};

static struct clk_pll pll_ve1 = {
	.conf         = CLK_PLL_TYPE_POW,
	.ssc_offset   = CLK_OFFSET_INVALID,
	.pll_offset   = PLL_VE1_1,
	.freq_tbl     = ve_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_ve1",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_pll pll_ve2 = {
	.conf         = CLK_PLL_TYPE_POW,
	.ssc_offset   = CLK_OFFSET_INVALID,
	.pll_offset   = PLL_VE2_1,
	.freq_tbl     = ve_tbl,
	.base.hw.init = &(struct clk_init_data) {
		.name         = "pll_ve2",
		.ops          = &clk_pll_ops,
		.parent_names = DEFAULT_PARENT_OSC27M,
		.num_parents  = 1,
		.flags        = CLK_GET_RATE_NOCACHE,
	},
};

static struct clk_composite_init_data clk_ve1_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE1_SEL_WIDTH,
	.mux_shift    = CLK_VE1_SEL_SHIFT,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_VE1,
	.parent_names = (const char *[]){
		"clk_sysh",
		"pll_ve1",
		"pll_ve2",
		"pll_ve2",
	},
	.num_parents  = 4,
	.name         = "clk_ve1",
	.flags        = CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve2_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE2_SEL_WIDTH,
	.mux_shift    = CLK_VE2_SEL_SHIFT,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_VE2,
	.parent_names = (const char *[]){
		"clk_sysh",
		"pll_ve1",
		"pll_ve2",
		"pll_ve2",
	},
	.num_parents  = 4,
	.name         = "clk_ve2",
	.flags        = CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
};

static struct clk_composite_init_data clk_ve3_init = {
	.mux_offset   = VE_CKSEL,
	.mux_width    = CLK_VE3_SEL_WIDTH,
	.mux_shift    = CLK_VE3_SEL_SHIFT,
	.gate_offset  = CLOCK_ENABLE1,
	.gate_shift   = CLK_EN_VE3,
	.parent_names =  (const char *[]){
		"clk_sysh",
		"pll_ve1",
		"pll_ve2",
		"pll_ve2",
	},
	.num_parents  = 4,
	.name         = "clk_ve3",
	.flags        = CLK_SET_RATE_PARENT | CLK_SET_RATE_NO_REPARENT,
};

static struct clk_hw *clk_reg_list[] = {
	[CC_PLL_SCPU]    = &__clk_pll_div_hw(&pll_scpu),
	[CC_PLL_BUS]     = &__clk_pll_div_hw(&pll_bus),
	[CC_PLL_BUS_H]   = &__clk_pll_hw(&pll_bus_h),
	[CC_PLL_DDSA]    = &__clk_pll_hw(&pll_ddsa),
	[CC_PLL_DDSB]    = &__clk_pll_hw(&pll_ddsb),
	[CC_PLL_GPU]     = &__clk_pll_hw(&pll_gpu),
	[CC_PLL_VE1]     = &__clk_pll_hw(&pll_ve1),
	[CC_PLL_VE2]     = &__clk_pll_hw(&pll_ve2),
	[CC_CLK_SYS_SB2] = &__clk_mmio_mux_hw(&clk_sys_sb2),
	[CC_CLK_SYS]     = &clk_sys.hw,
	[CC_CLK_SYSH]    = &clk_sysh.hw,
};

static  struct clk_composite_init_data *composite_clks[] = {
	[CC_CLK_GPU]     = &clk_gpu_init,
	[CC_CLK_VE1]     = &clk_ve1_init,
	[CC_CLK_VE2]     = &clk_ve2_init,
	[CC_CLK_VE3]     = &clk_ve3_init,
};

static int rtd129x_cc_init_clocks(struct device *dev)
{
	struct cc_platform_data *ccd = dev_get_drvdata(dev);
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

	if (clk_sys.hw.clk && clk_sys_sb2.base.hw.clk)
		clk_notifier_register(clk_sys.hw.clk, &clk_sys_sb2_nb);
	/* set alias */
	clk_add_alias("jpeg", NULL, "clk_en_jpeg", NULL);

	return 0;
}

static int rtd129x_cc_probe(struct platform_device *pdev)
{
	struct cc_platform_data *ccd;

	ccd = devm_cc_alloc_platform_data(&pdev->dev, CC_CLK_MAX);
	if (!ccd)
		return -ENOMEM;

	platform_set_drvdata(pdev, ccd);
	return cc_probe_platform(pdev, ccd, rtd129x_cc_init_clocks);
}

static const struct of_device_id rtd129x_cc_match[] = {
	{ .compatible = "realtek,clock-controller", },
	{}
};

static struct platform_driver rtd129x_cc_driver = {
	.probe = rtd129x_cc_probe,
	.driver = {
		.name = "rtk-rtd129x-cc",
		.of_match_table = rtd129x_cc_match,
		.pm = &cc_pm_ops,
	},
};

static int __init rtd129x_cc_init(void)
{
	return platform_driver_register(&rtd129x_cc_driver);
}
core_initcall(rtd129x_cc_init);
