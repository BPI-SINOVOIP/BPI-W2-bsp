/*
 * GMT-G22XX series PMIC MFD
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

#ifndef __LINUX_MFD_G22XX_H
#define __LINUX_MFD_G22XX_H

#include <linux/regmap.h>

struct g22xx_device {
	u32 chip_id;
	u32 chip_rev;
	struct device *dev;
	struct regmap *regmap;
};

int g22xx_device_init(struct g22xx_device *gdev);
void g22xx_device_exit(struct g22xx_device *gdev);

#define G22XX_DEVICE_ID_G2227           (2227)
#define G22XX_DEVICE_ID_G2237           (2237)

#endif
