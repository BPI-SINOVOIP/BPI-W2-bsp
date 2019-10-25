/*
 * reset-rtd16xx.c - Realtek RTD-16xx Reset Controller
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *	Cheng-Yu Lee <cylee12@realtek.com>
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

#include <linux/platform_device.h>
#include <linux/pm.h>
#include <soc/realtek/rtk_chip.h>
#include <dt-bindings/reset/rtk,reset.h>
#include <dt-bindings/reset/rtk,reset-rtd16xx.h>
#include "common.h"
#include "reset.h"

static struct rc_reg_desc rtd16xx_rc_desc[] = {
	{ .offset = 0x00, .write_en = 1, },
	{ .offset = 0x04, .write_en = 1, },
	{ .offset = 0x08, .write_en = 1, .pm_ignore_bits = 0x50150000, },
	{ .offset = 0x0c, .write_en = 1, .pm_ignore_bits = 0x40000000, },
	{ .offset = RC_INVALID_OFFSET, },
	{ .offset = 0x14, .write_en = 1, .pm_ignore_bits = 0x00140014, },
	{ .offset = 0x68, .write_en = 1, },
};

static unsigned long rtd16xx_rc_id_xlate(struct rc_platform_data *data,
					 unsigned long id)
{
	unsigned long ret = id;

	if (data->chip_rev != RTD_CHIP_A00) {
		switch (id) {
		case RSTN_HSE:
			ret =  RSTN_HSE_2;
			break;
		case RSTN_R2RDSC:
			ret =  RSTN_R2RDSC_2;
			break;
		case RSTN_EMMC:
			ret =  RSTN_EMMC_2;
			break;
		case RSTN_NF:
			ret =  RSTN_NF_2;
			break;
		case RSTN_MD:
			ret =  RSTN_MD_2;
			break;
		case RSTN_TPB:
			ret =  RSTN_TPB_2;
			break;
		case RSTN_TP:
			ret =  RSTN_TP_2;
			break;
		case RSTN_MIPI:
			ret =  RSTN_MIPI_2;
			break;
		}
	}
	if (ret != id)
		pr_debug("%s: id: %lx -> %lx\n", __func__, id, ret);
	return ret;
}

static struct rc_platform_data rtd16xx_rc_platform_data = {
	.desc     = rtd16xx_rc_desc,
	.num_desc = ARRAY_SIZE(rtd16xx_rc_desc),
	.id_xlate = rtd16xx_rc_id_xlate,
};

static int rtd16xx_rc_probe(struct platform_device *pdev)
{
	return rc_probe_platform(pdev, &rtd16xx_rc_platform_data);
}

static const struct of_device_id rtd16xx_rc_match[] = {
	{ .compatible = "realtek,rtd16xx-reset-controller", },
	{}
};

static struct platform_driver rtd16xx_rc_driver = {
	.probe = rtd16xx_rc_probe,
	.driver = {
		.name   = "rtk-rtd16xx-reset",
		.of_match_table = rtd16xx_rc_match,
		.pm = &rc_pm_ops,
	},
};

static int __init rtd16xx_rc_init(void)
{
	return platform_driver_register(&rtd16xx_rc_driver);
}
core_initcall(rtd16xx_rc_init);

