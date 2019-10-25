/*
 * reset.h
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

#ifndef __CLK_REALTEK_RESET_H
#define __CLK_REALTEK_RESET_H

#include <linux/reset-controller.h>

#define RC_DESC_ID(_id)           ((_id >> 8) - 1)
#define RC_RESET_ID(_id)          ((_id) & 0xff)
#define RC_RESET_BIT_MASK(_id)    BIT((_id) & 0xff)
#define RC_INVALID_OFFSET         (0xffffffff)

struct rc_reg_desc {
	u32 offset;
	u32 pm_ignore_bits;
	u32 pm_data;
	u32 write_en:1;
};

struct rc_platform_data {
	struct device *dev;
	struct reset_controller_dev rcdev;
	struct rc_reg_desc *desc;
	u32 num_desc;
	u32 chip_rev;
	unsigned long (*id_xlate)(struct rc_platform_data *data,
				  unsigned long id);
	/* register */
	void *reg;

	/* mmio regmap of reg */
	struct regmap *regmap;
	int offset;
};
#define to_rc_platform_data(_p) container_of((_p), struct rc_platform_data, rcdev)

extern const struct dev_pm_ops rc_pm_ops;
int rc_probe_platform(struct platform_device *pdev,
		      struct rc_platform_data *data);
static inline bool rc_is_invalid(struct rc_reg_desc *desc)
{
	return desc->offset == RC_INVALID_OFFSET;
}

#endif /* __CLK_REALTEK_RESET_H */
