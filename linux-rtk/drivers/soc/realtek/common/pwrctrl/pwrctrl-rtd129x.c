/*
 * Power Controller for RTD-129x SoC
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/pm_domain.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/suspend.h>
#include <soc/realtek/power-control.h>
#include <dt-bindings/power/rtk,power-rtd129x.h>
#include "pwrctrl_driver.h"
#include "pwrctrl-pd.h"

/* crt power control items */
static struct rtk_sram_pd gpu_pd = {
	.core = {
		.init = rtk_sram_pd_init,
		.pd.name = "gpu_pd",
		.pc.name = "pctrl_gpu",
		.pc.ops = &rtk_sram_async_ops,
		.flags = RTK_PD_NO_GENPD,
	},
	.pwr_offset = 0x394,
	.pwr5_offset = 0x3ac,
	.last_sd_ch = 0x3,
	.flags = RTK_SRAM_PD_NO_ISO_POW | RTK_SRAM_PD_NON_CONTIGUOUS_PWR,
	.expired_time = 1,
};

static struct rtk_sram_pd ve1_pd  = {
	.core = {
		.init = rtk_sram_pd_init,
		.pd.name = "ve1_pd",
		.pc.name = "pctrl_ve1",
		.pc.ops = &rtk_sram_async_ops,
		.flags = RTK_PD_NO_GENPD,
	},
	.pwr_offset = 0x380,
	.pwr5_offset = 0x3a8,
	.iso_offset = 0x400,
	.iso_shift = 0,
	.last_sd_ch = 0xf,
	.rstn_name = "ve1",
	.flags = RTK_SRAM_PD_NON_CONTIGUOUS_PWR,
	.expired_time = 10,
};

static struct rtk_sram_pd ve2_pd  = {
	.core = {
		.init = rtk_sram_pd_init,
		.pd.name = "ve2_pd",
		.pc.name = "pctrl_ve2",
		.pc.ops = &rtk_sram_async_ops,
		.flags = RTK_PD_NO_GENPD,
	},
	.pwr_offset = 0x3c0,
	.iso_offset = 0x400,
	.iso_shift = 4,
	.last_sd_ch = 0xf,
	.rstn_name = "ve2",
	.expired_time = 10,
};

static struct rtk_sram_pd ve3_pd  = {
	.core = {
		.init = rtk_sram_pd_init,
		.pd.name = "ve3_pd",
		.pc.name = "pctrl_ve3",
		.pc.ops = &rtk_sram_async_ops,
		.flags = RTK_PD_NO_GENPD,
	},
	.pwr_offset = 0x3e0,
	.iso_offset = 0x400,
	.iso_shift = 6,
	.last_sd_ch = 0xf,
	.rstn_name = "ve3",
	.expired_time = 10,
};

static struct rtk_sram_pd nat_pd  = {
	.core = {
		.init = rtk_sram_pd_init,
		.pd.name = "nat_pd",
		.pc.name = "pctrl_nat_pd",
		.pc.ops = &rtk_sram_ops,
	},
	.pwr_offset = 0x420,
	.iso_offset = 0x400,
	.iso_shift = 18,
	.last_sd_ch = 0xf,
	.rstn_name = "nat",
};

static struct rtk_sram_ch_pd disp_se_pd = {
	.core = {
		.init = rtk_sram_ch_pd_init,
		.pd.name = "se_pd",
		.pc.name = "pctrl_se_pd",
		.pc.ops = &rtk_sram_ch_ops,
	},
	.pwr_offset = 0x360,
	.shift = 5,
	.width = 3,
};

static struct rtk_sram_ch_pd disp_mipi_pd = {
	.core = {
		.init = rtk_sram_ch_pd_init,
		.pd.name = "mipi_pd",
		.pc.name = "pctrl_mipi_pd",
		.pc.ops = &rtk_sram_ch_ops,
	},
	.pwr_offset = 0x360,
	.shift = 8,
	.width = 1,
};

static struct rtk_sram_ch_pd disp_hdmirx_pd = {
	.core = {
		.init = rtk_sram_ch_pd_init,
		.pd.name = "hdmirx_pd",
		.pc.name = "pctrl_hdmirx_pd",
		.pc.ops = &rtk_sram_ch_ops,
	},
	.pwr_offset = 0x360,
	.shift = 11,
	.width = 4,
};

static struct pwrctrl_pd *crt_ppds[PD_MAX] = {
	[PD_SRAM_VE1]         = &ve1_pd.core,
	[PD_SRAM_VE2]         = &ve2_pd.core,
	[PD_SRAM_VE3]         = &ve3_pd.core,
	[PD_SRAM_NAT]         = &nat_pd.core,
	[PD_SRAM_GPU]         = &gpu_pd.core,
	[PD_SRAM_DISP_SE]     = &disp_se_pd.core,
	[PD_SRAM_DISP_MIPI]   = &disp_mipi_pd.core,
	[PD_SRAM_DISP_HDMIRX] = &disp_hdmirx_pd.core,
};

static struct power_controller_data crt_data = {
	.ppds = crt_ppds,
	.num_ppds = ARRAY_SIZE(crt_ppds),
};

static const struct of_device_id power_controller_match[];

static int power_controller_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct power_controller_data *pcd;
	const struct of_device_id *id;

	dev_info(dev, "%s\n", __func__);

	/* get controller data */
	id = of_match_node(power_controller_match, dev->of_node);
	if (!id)
		return -ENODEV;

	pcd = (struct power_controller_data *)id->data;
	dev_set_drvdata(dev, pcd);
	power_controller_init_pds(dev, pcd);

	return 0;
}

static const struct of_device_id power_controller_match[] = {
	{.compatible = "realtek,rtd129x-crt-power", .data = &crt_data},
	{}
};

static struct platform_driver power_controller_driver = {
	.probe = power_controller_probe,
	.driver = {
		.name   = "rtd129x-pc",
		.of_match_table = power_controller_match,
		.pm = &power_controller_pm_ops,
	},
};

static int __init power_controller_init(void)
{
	return platform_driver_register(&power_controller_driver);
}
arch_initcall(power_controller_init);
