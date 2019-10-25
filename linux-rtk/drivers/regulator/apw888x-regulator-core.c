 /*
 * apw888x-regulator-core.c - Anpec APW888X Series PMIC common code
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

#include <linux/module.h>
#include <linux/list.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <linux/of.h>
#include <linux/mfd/apw888x.h>
#include <dt-bindings/regulator/anpec,apw888x.h>
#include "apw888x-regulator.h"

int apw888x_regulator_of_parse_cb(struct device_node *np,
				  const struct regulator_desc *desc,
				  struct regulator_config *config)
{
	struct apw888x_regulator_data *data = config->driver_data;
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

	if (of_find_property(np, "apw888x-discharge-disable", NULL))
		data->flags |= APW888X_DISCHARGE_DISABLE;

	return 0;
}

unsigned int apw888x_regulator_dc_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case APW8889_DC_MODE_FORCE_PWM:
		return REGULATOR_MODE_FAST;
	default:
		break;
	}
	return REGULATOR_MODE_NORMAL;
}

unsigned int apw888x_regulator_ldo_of_map_mode(unsigned int mode)
{
	return REGULATOR_MODE_NORMAL;
}

/* regulator_ops */
static int apw888x_regulator_set_mode_regmap(struct regulator_dev *rdev,
					     unsigned int mode)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
	struct apw888x_regulator_desc *gd = data->desc;
	unsigned int val = 0;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	if (!data->nmode)
		return -EINVAL;

	if (apw888x_regulator_type_is_ldo(gd))
		val = 0;
	else
		val = (mode & REGULATOR_MODE_FAST) ? 2 : 0;

	dev_dbg(rdev_get_dev(rdev), "%s: val=%02x\n", __func__, val);
	return regmap_field_write(data->nmode, val);
}

static unsigned int apw888x_regulator_get_mode_regmap(struct regulator_dev *rdev)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
	struct apw888x_regulator_desc *gd = data->desc;
	unsigned int val;
	int ret;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	if (!data->nmode)
		return -EINVAL;

	ret = regmap_field_read(data->nmode, &val);
	if (ret)
		return 0;

	dev_dbg(rdev_get_dev(rdev), "%s: val=%02x\n", __func__, val);

	if (apw888x_regulator_type_is_ldo(gd) && val == 2)
		return REGULATOR_MODE_IDLE;
	else if (val == 2)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}


static int apw888x_set_suspend_enable(struct regulator_dev *rdev)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(data->smode, 0x2);
	return 0;
}

static int apw888x_set_suspend_disable(struct regulator_dev *rdev)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
	struct device *dev = rdev_get_dev(rdev);

	dev_dbg(dev, "%s\n", __func__);
	if (!data->smode)
		return -EINVAL;
	regmap_field_write(data->smode, 0x3);

	if (data->dischg && (data->flags & APW888X_DISCHARGE_DISABLE)) {
		dev_info(dev, "%s: set dischg disabled\n", __func__);
		regmap_field_write(data->dischg, 0);
	}
	return 0;
}

static int apw888x_set_suspend_voltage(struct regulator_dev *rdev,
				       int uV)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
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

static int apw888x_regulator_get_voltage_fixed(struct regulator_dev *rdev)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);

	if (data->fixed_uV)
		return data->fixed_uV;
	return -EINVAL;
}

static int apw888x_regulator_set_clamp_en(struct regulator_dev *rdev,
					  int enable)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);

	if (!data->clamp)
		return -EINVAL;
	dev_dbg(rdev_get_dev(rdev), "%s: set clamp_en val=%x\n",
		__func__, enable);
	return regmap_field_write(data->clamp, enable);
}

static int apw888x_regulator_get_clamp_en(struct regulator_dev *rdev)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
	unsigned int enable;
	int ret;

	if (!data->clamp)
		return -EINVAL;
	ret = regmap_field_read(data->clamp, &enable);
	if (!ret)
		dev_dbg(rdev_get_dev(rdev), "%s: get clamp_en val=%x\n",
			__func__, enable);
	return ret ? ret : enable;
}

static int apw888x_regulator_set_voltage_sel_regmap(struct regulator_dev *rdev,
						    unsigned sel)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);

	if (data->clamp)
		apw888x_regulator_set_clamp_en(rdev, sel < 0x34);
	return regulator_set_voltage_sel_regmap(rdev, sel);
}

const struct regulator_ops apw888x_regulator_ops = {
	.list_voltage         = regulator_list_voltage_linear,
	.map_voltage          = regulator_map_voltage_linear,
	.set_voltage_sel      = apw888x_regulator_set_voltage_sel_regmap,
	.get_voltage_sel      = regulator_get_voltage_sel_regmap,
	.enable               = regulator_enable_regmap,
	.disable              = regulator_disable_regmap,
	.is_enabled           = regulator_is_enabled_regmap,
	.get_mode             = apw888x_regulator_get_mode_regmap,
	.set_mode             = apw888x_regulator_set_mode_regmap,
	.set_suspend_voltage  = apw888x_set_suspend_voltage,
	.set_suspend_enable   = apw888x_set_suspend_enable,
	.set_suspend_disable  = apw888x_set_suspend_disable,
};

const struct regulator_ops apw888x_regulator_fixed_uV_ops = {
	.enable               = regulator_enable_regmap,
	.disable              = regulator_disable_regmap,
	.is_enabled           = regulator_is_enabled_regmap,
	.get_mode             = apw888x_regulator_get_mode_regmap,
	.set_mode             = apw888x_regulator_set_mode_regmap,
	.set_suspend_voltage  = apw888x_set_suspend_voltage,
	.set_suspend_enable   = apw888x_set_suspend_enable,
	.set_suspend_disable  = apw888x_set_suspend_disable,
	.get_voltage          = apw888x_regulator_get_voltage_fixed,
};

/* helper function */
/*
 * apw888x_prepare_suspend_state - prepare apw888x suspend state, copy the correct
 *                                state into state_mem of decs, then call
 *                                regulator_suspend_prepare() to do regulator
 *                                suspend.
 *
 * @rdev:        regulator device
 * @is_coldboot: state selection
 */
void apw888x_prepare_suspend_state(struct regulator_dev *rdev,
				   int is_coldboot)
{
	struct apw888x_regulator_data *data = rdev_get_drvdata(rdev);
	struct regulator_state *state;

	state = &rdev->constraints->state_mem;
	*state = is_coldboot ? data->state_coldboot : data->state_mem;

	dev_info(rdev_get_dev(rdev), "%s: state={enabled=%d, disabled=%d, mode=%d, uV=%d}, is_coldboot=%d\n",
		__func__, state->enabled, state->disabled, state->mode,
		state->uV, is_coldboot);
}

static struct regmap_field *create_regmap_field(struct apw888x_regulator_device *ardev,
	u32 reg, u32 mask)
{
	u32 msb = fls(mask) - 1;
	u32 lsb = ffs(mask) - 1;
	struct reg_field map = REG_FIELD(reg, lsb, msb);
	struct regmap_field *rmap;

	if (reg == 0 && mask == 0)
		return NULL;

	dev_dbg(ardev->dev, "reg=%02x, mask=%02x, lsb=%d, msb=%d\n",
		reg, mask, lsb, msb);
	rmap = devm_regmap_field_alloc(ardev->dev, ardev->regmap, map);
	if (IS_ERR(rmap)) {
		dev_err(ardev->dev, "regmap_field_alloc() for (reg=%02x, mask=%02x) returns %ld\n",
			reg, mask, PTR_ERR(rmap));
	}
	return rmap;
}

static inline void setup_regulator_state(struct regulator_state *state)
{
	/*
	 * copy state_mem to data for mem/coldboot switching. if there is no
	 * sleep uV and mode, set the state to enable
	 */
	if (state->uV != 0)
		return;
	if (state->disabled)
		return;
	state->enabled = true;
}

#define APW888X_DC_MODE_MASK    (REGULATOR_MODE_NORMAL | REGULATOR_MODE_FAST)
#define APW888X_LDO_MODE_MASK   (REGULATOR_MODE_NORMAL)

static ssize_t apw888x_regulator_clamp_en_store(struct device *dev,
						struct device_attribute *attr,
						const char *buf,
						size_t count)
{
	return -EINVAL;
}

static ssize_t apw888x_regulator_clamp_en_show(struct device *dev,
					       struct device_attribute *attr,
					       char *buf)
{

	struct regulator_dev *rdev = dev_get_drvdata(dev);
	int val = apw888x_regulator_get_clamp_en(rdev);

	switch (val) {
	case 1:
		return sprintf(buf, "enable\n");
	case 0:
		return sprintf(buf, "disable\n");
	case -EINVAL:
		return sprintf(buf, "invalid\n");
	}
	return sprintf(buf, "unknown\n");
}

static DEVICE_ATTR(clamp_en, 0644,
		   apw888x_regulator_clamp_en_show,
		   apw888x_regulator_clamp_en_store);

static struct attribute *apw888x_regulator_dev_attrs[] = {
	&dev_attr_clamp_en.attr,
	NULL
};

static const struct attribute_group apw888x_regulator_dev_group = {
	.name = "apw888x",
	.attrs = apw888x_regulator_dev_attrs,
};

static int apw888x_regulator_add_sysfs(struct device *dev)
{
	return sysfs_create_group(&dev->kobj, &apw888x_regulator_dev_group);
}

int apw888x_regulator_register(struct apw888x_regulator_device *ardev,
			       struct apw888x_regulator_desc *gd)
{
	struct device *dev = ardev->dev;
	struct apw888x_regulator_data *data;
	struct regulator_config config = {};
	struct regulation_constraints *c;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->desc = gd;

	data->nmode = create_regmap_field(ardev, gd->nmode_reg, gd->nmode_mask);
	if (IS_ERR(data->nmode))
		return PTR_ERR(data->nmode);
	data->smode = create_regmap_field(ardev, gd->smode_reg, gd->smode_mask);
	if (IS_ERR(data->smode))
		return PTR_ERR(data->smode);
	data->svsel = create_regmap_field(ardev, gd->svsel_reg, gd->svsel_mask);
	if (IS_ERR(data->svsel))
		return PTR_ERR(data->svsel);
	data->dischg = create_regmap_field(ardev, gd->dischg_reg,
		gd->dischg_mask);
	if (IS_ERR(data->dischg))
		return PTR_ERR(data->dischg);

	if (gd->clamp_reg) {
		data->clamp = create_regmap_field(ardev, gd->clamp_reg, gd->clamp_mask);
		if (IS_ERR(data->clamp))
			return PTR_ERR(data->clamp);
	}

	config.dev         = ardev->dev;
	config.regmap      = ardev->regmap;
	config.driver_data = data;

	data->rdev = devm_regulator_register(dev, &gd->desc, &config);
	if (IS_ERR(data->rdev))
		return PTR_ERR(data->rdev);

	apw888x_regulator_add_sysfs(rdev_get_dev(data->rdev));
	apw888x_regulator_set_clamp_en(data->rdev, 1);

	c = data->rdev->constraints;
	/* setup regulator state */
	setup_regulator_state(&c->state_mem);
	data->state_mem = c->state_mem;
	setup_regulator_state(&data->state_coldboot);
	/* enable change mode */
	c->valid_ops_mask |= REGULATOR_CHANGE_MODE;
	c->valid_modes_mask |= apw888x_regulator_type_is_ldo(data->desc) ?
		APW888X_LDO_MODE_MASK : APW888X_DC_MODE_MASK;
	list_add_tail(&data->list, &ardev->list);
	return 0;
}

