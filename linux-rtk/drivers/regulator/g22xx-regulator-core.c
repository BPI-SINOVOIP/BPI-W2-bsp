/*
 * GMT-G22XX serise PMIC regulator core functions
 *
 * Copyright (C) 2018-2019 Realtek Semiconductor Corporation
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

#include <linux/bitops.h>
#include <linux/of.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/suspend.h>
#include <linux/sysfs.h>
#include <linux/uaccess.h>
#include "g22xx-regulator.h"

/* of_parse_cb */
int g22xx_regulator_of_parse_cb(struct device_node *np,
	const struct regulator_desc *desc, struct regulator_config *config)
{
	struct g22xx_regulator_data *data = config->driver_data;
	struct device_node *child;
	unsigned int val;

	child = of_get_child_by_name(np, "regulator-state-coldboot");
	if (!child)
		child = of_get_child_by_name(np, "regulator-state-mem");
	if (child) {
		struct regulator_state *state = &data->state_coldboot;

		if (of_property_read_bool(child, "regulator-on-in-suspend"))
			state->enabled = true;

		if (of_property_read_bool(child, "regulator-off-in-suspend"))
			state->disabled = true;

		if (!of_property_read_u32(child, "regulator-suspend-microvolt",
			&val))
			state->uV = val;
	}

	if (desc->n_voltages == 1 && desc->fixed_uV == 0) {
		u32 min = 0, max = 0;

		of_property_read_u32(np, "regulator-min-microvolt", &min);
		of_property_read_u32(np, "regulator-max-microvolt", &max);
		WARN_ON(min != max);
		data->fixed_uV = max;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(g22xx_regulator_of_parse_cb);

unsigned int g22xx_regulator_dc_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case G22XX_DC_MODE_FORCE_PWM:
		return REGULATOR_MODE_FAST;
	default:
		break;
	}
	return REGULATOR_MODE_NORMAL;
}
EXPORT_SYMBOL_GPL(g22xx_regulator_dc_of_map_mode);

unsigned int g22xx_regulator_ldo_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case G22XX_LDO_MODE_ECO:
		return REGULATOR_MODE_IDLE;
	default:
		break;
	}
	return REGULATOR_MODE_NORMAL;
}
EXPORT_SYMBOL_GPL(g22xx_regulator_ldo_of_map_mode);

/* regulator_ops */
static int g22xx_regulator_set_mode_regmap(struct regulator_dev *rdev,
	unsigned int mode)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);
	struct g22xx_regulator_desc *gd = data->gd;
	unsigned int val = 0;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	if (!data->nmode)
		return -EINVAL;

	if (g22xx_regulator_type_is_ldo(gd))
		val = (mode & REGULATOR_MODE_IDLE) ? 2 : 0;
	else
		val =  (mode & REGULATOR_MODE_FAST) ? 2 : 0;

	dev_dbg(rdev_get_dev(rdev), "%s: val=%02x\n", __func__, val);
	return regmap_field_write(data->nmode, val);
}

static unsigned int g22xx_regulator_get_mode_regmap(struct regulator_dev *rdev)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);
	struct g22xx_regulator_desc *gd = data->gd;
	unsigned int val;
	int ret;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	if (!data->nmode)
		return -EINVAL;

	ret = regmap_field_read(data->nmode, &val);
	if (ret)
		return 0;

	dev_dbg(rdev_get_dev(rdev), "%s: val=%02x\n", __func__, val);

	if (g22xx_regulator_type_is_ldo(gd) && val == 2)
		return REGULATOR_MODE_IDLE;
	else if (val == 2)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}


static int g22xx_set_suspend_enable(struct regulator_dev *rdev)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(data->smode, 0x1);
	return 0;
}

static int g22xx_set_suspend_disable(struct regulator_dev *rdev)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	if (!data->smode)
		return -EINVAL;
	regmap_field_write(data->smode, 0x3);
	return 0;
}

static int g22xx_set_suspend_voltage(struct regulator_dev *rdev,
	int uV)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);
	int vsel;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	vsel = regulator_map_voltage_iterate(rdev, uV, uV);
	if (vsel < 0)
		return -EINVAL;

	if (!data->smode || !data->svsel)
		return -EINVAL;

	regmap_field_write(data->smode, 0x2);
	regmap_field_write(data->svsel, vsel);
	return 0;
}

static int g22xx_regulator_get_voltage_fixed(struct regulator_dev *rdev)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);

	if (data->fixed_uV)
		return data->fixed_uV;
	return -EINVAL;
}

const struct regulator_ops g22xx_regulator_ops = {
	.list_voltage         = regulator_list_voltage_table,
	.map_voltage          = regulator_map_voltage_iterate,
	.set_voltage_sel      = regulator_set_voltage_sel_regmap,
	.get_voltage_sel      = regulator_get_voltage_sel_regmap,
	.enable               = regulator_enable_regmap,
	.disable              = regulator_disable_regmap,
	.is_enabled           = regulator_is_enabled_regmap,
	.get_mode             = g22xx_regulator_get_mode_regmap,
	.set_mode             = g22xx_regulator_set_mode_regmap,
	.set_suspend_voltage  = g22xx_set_suspend_voltage,
	.set_suspend_enable   = g22xx_set_suspend_enable,
	.set_suspend_disable  = g22xx_set_suspend_disable,
};
EXPORT_SYMBOL_GPL(g22xx_regulator_ops);

const struct regulator_ops g22xx_regulator_fixed_uV_ops = {
	.enable               = regulator_enable_regmap,
	.disable              = regulator_disable_regmap,
	.is_enabled           = regulator_is_enabled_regmap,
	.get_mode             = g22xx_regulator_get_mode_regmap,
	.set_mode             = g22xx_regulator_set_mode_regmap,
	.set_suspend_voltage  = g22xx_set_suspend_voltage,
	.set_suspend_enable   = g22xx_set_suspend_enable,
	.set_suspend_disable  = g22xx_set_suspend_disable,
	.get_voltage          = g22xx_regulator_get_voltage_fixed,
};
EXPORT_SYMBOL_GPL(g22xx_regulator_fixed_uV_ops);

/* helper function */
/*
 * g22xx_prepare_suspend_state - prepare g22xx suspend state, copy the correct
 *                               state into state_mem of decs, then call
 *                               regulator_suspend_prepare() to do regulator
 *                               suspend.
 *
 * @rdev:        regulator device
 * @is_coldboot: state selection
 */
void g22xx_prepare_suspend_state(struct regulator_dev *rdev,
	int is_coldboot)
{
	struct g22xx_regulator_data *data = rdev_get_drvdata(rdev);
	struct regulator_state *state;

	state = &rdev->constraints->state_mem;
	*state = is_coldboot ? data->state_coldboot : data->state_mem;

	dev_info(rdev_get_dev(rdev), "%s: state={enabled=%d, disabled=%d, mode=%d, uV=%d}, is_coldboot=%d\n",
		__func__, state->enabled, state->disabled, state->mode,
		state->uV, is_coldboot);
}
EXPORT_SYMBOL_GPL(g22xx_prepare_suspend_state);

static struct regmap_field *create_regmap_field(
		struct g22xx_regulator_device *grdev,
		u32 reg,
		u32 mask)
{
	u32 msb = fls(mask) - 1;
	u32 lsb = ffs(mask) - 1;
	struct reg_field map = REG_FIELD(reg, lsb, msb);
	struct regmap_field *rmap;

	if (reg == 0 && mask == 0)
		return NULL;

	dev_dbg(grdev->dev, "reg=%02x, mask=%02x, lsb=%d, msb=%d\n",
		reg, mask, lsb, msb);
	rmap = devm_regmap_field_alloc(grdev->dev, grdev->regmap, map);
	if (IS_ERR(rmap)) {
		dev_err(grdev->dev, "regmap_field_alloc() for (reg=%02x, mask=%02x) returns %ld\n",
			reg, mask, PTR_ERR(rmap));
	}
	return rmap;
}

struct regulator_dev *g22xx_regulator_register(
		struct g22xx_regulator_device *grdev,
		struct g22xx_regulator_desc *gd)
{
	struct device *dev = grdev->dev;
	struct g22xx_regulator_data *data;
	struct regulator_config config = {};
	struct regulation_constraints *c;


	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return ERR_PTR(-ENOMEM);

	data->gd = gd;

	data->nmode = create_regmap_field(grdev, gd->nmode_reg, gd->nmode_mask);
	if (IS_ERR(data->nmode))
		return ERR_CAST(data->nmode);
	data->smode = create_regmap_field(grdev, gd->smode_reg, gd->smode_mask);
	if (IS_ERR(data->smode))
		return ERR_CAST(data->smode);
	data->svsel = create_regmap_field(grdev, gd->svsel_reg, gd->svsel_mask);
	if (IS_ERR(data->svsel))
		return ERR_CAST(data->svsel);

	config.dev         = grdev->dev;
	config.regmap      = grdev->regmap;
	config.driver_data = data;

	data->rdev = devm_regulator_register(dev, &gd->desc, &config);
	if (IS_ERR(data->rdev))
		return data->rdev;

	c = data->rdev->constraints;

	/*
	 * copy state_mem to data for mem/coldboot switching. if there is no
	 * sleep uV and mode, set the state to enable
	 */
	data->state_mem = c->state_mem;
	if (data->state_mem.uV == 0 && data->state_mem.disabled == 0) {
		data->state_mem.enabled = true;
		c->state_mem = data->state_mem;
	}
	if (data->state_coldboot.uV == 0 && data->state_coldboot.disabled == 0)
		data->state_coldboot.enabled = true;

	/* enable change mode */
	c->valid_modes_mask |= REGULATOR_MODE_NORMAL;
	if (g22xx_regulator_type_is_ldo(data->gd))
		c->valid_modes_mask |= REGULATOR_MODE_IDLE;
	else
		c->valid_modes_mask |= REGULATOR_MODE_FAST;
	c->valid_ops_mask |= REGULATOR_CHANGE_MODE;

	list_add_tail(&data->list, &grdev->list);

	return data->rdev;
}
EXPORT_SYMBOL_GPL(g22xx_regulator_register);


