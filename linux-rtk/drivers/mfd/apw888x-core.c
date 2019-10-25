/*
 * GMT-APW888X series PMIC MFD core
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
#include <linux/mfd/apw888x.h>

static struct mfd_cell apw8889_devs[] = {
	{
		.name = "g22xx-powerkey",
		.of_compatible = "gmt,g22xx-powerkey",
	},
	{
		.name = "g22xx-poweroff",
		.of_compatible = "gmt,g22xx-poweroff",
	},
	{
		.name = "apw8889-regulator",
		.of_compatible = "anpec,apw8889-regulator",
	},
};

static struct mfd_cell apw8886_devs[] = {
	{
		.name = "g22xx-powerkey",
		.of_compatible = "gmt,g22xx-powerkey",
	},
	{
		.name = "g22xx-poweroff",
		.of_compatible = "gmt,g22xx-poweroff",
	},
	{
		.name = "apw8886-regulator",
		.of_compatible = "anpec,apw8886-regulator",
	},
};

int apw888x_device_init(struct apw888x_device *adev)
{
	switch (adev->chip_id) {
	case APW888X_DEVICE_ID_APW8889:
		return devm_mfd_add_devices(adev->dev, PLATFORM_DEVID_NONE,
			apw8889_devs, ARRAY_SIZE(apw8889_devs), 0, 0, 0);
	case APW888X_DEVICE_ID_APW8886:
		return devm_mfd_add_devices(adev->dev, PLATFORM_DEVID_NONE,
			apw8886_devs, ARRAY_SIZE(apw8886_devs), 0, 0, 0);
	default:
		return -EINVAL;
	}
	return 0;
}

void apw888x_device_exit(struct apw888x_device *adev)
{}
