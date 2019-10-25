/*
 * GMT-G22XX series PMIC MFD core
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

#include <linux/regmap.h>
#include <linux/mfd/core.h>
#include <linux/mfd/g22xx.h>

static struct mfd_cell g2227_devs[] = {
	{
		.name = "g22xx-powerkey",
		.of_compatible = "gmt,g22xx-powerkey",
	},
	{
		.name = "g22xx-poweroff",
		.of_compatible = "gmt,g22xx-poweroff",
	},
	{
		.name = "g2227-regulator",
		.of_compatible = "gmt,g2227-regulator",
	},
};

static struct mfd_cell g2237_devs[] = {
	{
		.name = "g22xx-powerkey",
		.of_compatible = "gmt,g22xx-powerkey",
	},
	{
		.name = "g22xx-poweroff",
		.of_compatible = "gmt,g22xx-poweroff",
	},
	{
		.name = "g2237-regulator",
		.of_compatible = "gmt,g2237-regulator",
	},
};

int g22xx_device_init(struct g22xx_device *gdev)
{
	switch (gdev->chip_id) {
	case G22XX_DEVICE_ID_G2227:
		return devm_mfd_add_devices(gdev->dev, PLATFORM_DEVID_NONE,
			g2227_devs, ARRAY_SIZE(g2227_devs), 0, 0, 0);
	case G22XX_DEVICE_ID_G2237:
		return devm_mfd_add_devices(gdev->dev, PLATFORM_DEVID_NONE,
			g2237_devs, ARRAY_SIZE(g2237_devs), 0, 0, 0);
	default:
		return -EINVAL;
	}
	return 0;
}

void g22xx_device_exit(struct g22xx_device *gdev)
{}
