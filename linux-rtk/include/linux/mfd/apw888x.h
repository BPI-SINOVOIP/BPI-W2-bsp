/*
 * Anpec APW888X series PMIC MFD
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
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

#ifndef __LINUX_MFD_APW888X_H
#define __LINUX_MFD_APW888X_H

#include <linux/regmap.h>

struct apw888x_device {
	u32 chip_id;
	u32 chip_rev;
	struct device *dev;
	struct regmap *regmap;
};

int apw888x_device_init(struct apw888x_device *gdev);
void apw888x_device_exit(struct apw888x_device *gdev);

#define APW888X_DEVICE_ID_APW8889       (8889)
#define APW888X_DEVICE_ID_APW8886       (8886)

#endif /* __LINUX_MFD_APW888X_H */
