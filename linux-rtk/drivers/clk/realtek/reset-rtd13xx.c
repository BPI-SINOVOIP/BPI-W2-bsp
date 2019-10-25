/*
 * reset-rtd13xx.c - Realtek RTD-13xx Reset Controller
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
#include <dt-bindings/reset/rtk,reset-rtd13xx.h>
#include "common.h"
#include "reset.h"

static struct rc_reg_desc rtd13xx_rc_desc[] = {
	{ .offset = 0x00, .write_en = 1, },
	{ .offset = 0x04, .write_en = 1, },
	{ .offset = 0x08, .write_en = 1, .pm_ignore_bits = 0x50150000, },
	{ .offset = 0x0c, .write_en = 1, .pm_ignore_bits = 0x40000000, },
	{ .offset = RC_INVALID_OFFSET, },
	{ .offset = 0x14, .write_en = 1, .pm_ignore_bits = 0x00140014, },
	{ .offset = 0x68, .write_en = 1, },
	{ .offset = 0x88, .write_en = 1, },
	{ .offset = 0x90, .write_en = 1, },
	{ .offset = 0x94, .write_en = 1, },
	{ .offset = 0x454, },
	{ .offset = 0x458, },
	{ .offset = RC_INVALID_OFFSET, },
	{ .offset = RC_INVALID_OFFSET, },
	{ .offset = 0x464, },
};

static struct rc_platform_data rtd13xx_rc_platform_data = {
	.desc     = rtd13xx_rc_desc,
	.num_desc = ARRAY_SIZE(rtd13xx_rc_desc),
};

static int rtd13xx_rc_probe(struct platform_device *pdev)
{
	return rc_probe_platform(pdev, &rtd13xx_rc_platform_data);
}

static const struct of_device_id rtd13xx_rc_match[] = {
	{ .compatible = "realtek,rtd13xx-reset-controller", },
	{}
};

static struct platform_driver rtd13xx_rc_driver = {
	.probe = rtd13xx_rc_probe,
	.driver = {
		.name   = "rtk-rtd13xx-reset",
		.of_match_table = rtd13xx_rc_match,
		.pm = &rc_pm_ops,
	},
};

static int __init rtd13xx_rc_init(void)
{
	return platform_driver_register(&rtd13xx_rc_driver);
}
core_initcall(rtd13xx_rc_init);

