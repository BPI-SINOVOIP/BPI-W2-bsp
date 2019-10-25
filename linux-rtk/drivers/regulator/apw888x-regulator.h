 /*
 * apw888x-regulator.h
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
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

#ifndef __APW888X_REGULATOR_H
#define __APW888X_REGULATOR_H

#include <linux/list.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <linux/mfd/apw888x.h>

struct apw888x_regulator_desc {
	struct regulator_desc desc;
	u8 nmode_reg;
	u8 nmode_mask;
	u8 smode_reg;
	u8 smode_mask;
	u8 svsel_reg;
	u8 svsel_mask;
	u8 clamp_reg;
	u8 clamp_mask;
	u8 dischg_reg;
	u8 dischg_mask;
};

struct apw888x_regulator_device {
	struct device *dev;
	struct regmap *regmap;
	struct list_head list;
};

struct apw888x_regulator_data {
	struct list_head list;
	struct regulator_dev *rdev;
	struct apw888x_regulator_desc *desc;

	struct regmap_field *svsel;
	struct regmap_field *smode;
	struct regmap_field *nmode;
	struct regmap_field *clamp;
	struct regmap_field *dischg;

	struct regulator_state state_mem;
	struct regulator_state state_coldboot;

	u32 fixed_uV;
	u32 flags;
};

#define APW888X_DISCHARGE_DISABLE       (0x1)

int apw888x_regulator_of_parse_cb(struct device_node *np,
				  const struct regulator_desc *desc,
				  struct regulator_config *config);
unsigned int apw888x_regulator_dc_of_map_mode(unsigned int mode);
unsigned int apw888x_regulator_ldo_of_map_mode(unsigned int mode);

static inline int apw888x_regulator_type_is_ldo(struct apw888x_regulator_desc *gd)
{
	return gd->desc.of_map_mode == apw888x_regulator_ldo_of_map_mode;
}

extern const struct regulator_ops apw888x_regulator_ops;
extern const struct regulator_ops apw888x_regulator_fixed_uV_ops;

/* helper function */
/*
 * apw888x_prepare_suspend_state - prepare apw888x suspend state, copy the correct
 *                                 state into state_mem of decs, then call
 *                                 regulator_suspend_prepare() to do regulator
 *                                 suspend.
 *
 * @rdev:        regulator device
 * @is_coldboot: state selection
 */
void apw888x_prepare_suspend_state(struct regulator_dev *rdev,
				   int is_coldboot);

#define APW888X_DC_MODE_MASK    (REGULATOR_MODE_NORMAL | REGULATOR_MODE_FAST)
#define APW888X_LDO_MODE_MASK   (REGULATOR_MODE_NORMAL)

int apw888x_regulator_register(struct apw888x_regulator_device *ardev,
			       struct apw888x_regulator_desc *gd);

#endif /* __APW888X_REGULATOR_H */
