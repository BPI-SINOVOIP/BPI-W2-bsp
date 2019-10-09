/*
 * g22xx-regulator-core.c - GMT-G22xx series Regulator core functions
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "g22xx: " fmt

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
int g22xx_of_parse_cb(struct device_node *np,
	const struct regulator_desc *desc, struct regulator_config *config)
{
	struct g22xx_desc *gd = config->driver_data;
	struct device_node *child;
	unsigned int val;

	child = of_get_child_by_name(np, "regulator-state-coldboot");
	if (!child)
		child = of_get_child_by_name(np, "regulator-state-mem");
	if (child) {
		struct regulator_state *state = &gd->state_coldboot;

		if (of_property_read_bool(child, "regulator-on-in-suspend"))
			state->enabled = true;

		if (of_property_read_bool(child, "regulator-off-in-suspend"))
			state->disabled = true;

		if (!of_property_read_u32(child, "regulator-suspend-microvolt",
			&val))
			state->uV = val;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(g22xx_of_parse_cb);

/* regulator_ops */
static int g22xx_regulator_set_mode_regmap(struct regulator_dev *rdev,
	unsigned int mode)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);
	unsigned int val = 0;

	if (g22xx_is_ldo(gd))
		val = (mode & REGULATOR_MODE_IDLE) ? 2 : 0;
	else
		val =  (mode & REGULATOR_MODE_FAST) ? 2 : 0;
	return regmap_field_write(gd->nmode, val);
}

static unsigned int g22xx_regulator_get_mode_regmap(struct regulator_dev *rdev)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);
	unsigned int val;
	int ret;

	ret = regmap_field_read(gd->nmode, &val);
	if (ret)
		return 0;

	if (g22xx_is_ldo(gd) && val == 2)
		return REGULATOR_MODE_IDLE;
	else if (val == 2)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}


static int g22xx_set_voltage_time_sel(struct regulator_dev *rdev,
	unsigned int old_selector, unsigned int new_selector)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	if (new_selector > old_selector)
		return gd->delay_volt_up;
	return 0;
}

static int g22xx_set_suspend_enable(struct regulator_dev *rdev)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(gd->smode, 0x1);
	return 0;
}

static int g22xx_set_suspend_disable(struct regulator_dev *rdev)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(gd->smode, 0x3);
	return 0;
}

static int g22xx_set_suspend_voltage(struct regulator_dev *rdev,
	int uV)
{
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);
	int vsel;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	vsel = regulator_map_voltage_iterate(gd->rdev, uV, uV);
	if (vsel < 0)
		return -EINVAL;

	if (!gd->smode || !gd->svo)
		return -EINVAL;

	regmap_field_write(gd->smode, 0x2);
	regmap_field_write(gd->svo, vsel);
	return 0;
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
	.set_voltage_time_sel = g22xx_set_voltage_time_sel,
	.set_suspend_voltage  = g22xx_set_suspend_voltage,
	.set_suspend_enable   = g22xx_set_suspend_enable,
	.set_suspend_disable  = g22xx_set_suspend_disable,
};
EXPORT_SYMBOL_GPL(g22xx_regulator_ops);

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
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);
	struct regulator_state *state;

	state = &gd->rdev->constraints->state_mem;
	*state = is_coldboot ? gd->state_coldboot : gd->state_mem;
}
EXPORT_SYMBOL_GPL(g22xx_prepare_suspend_state);

/* sysfs */
static ssize_t g22xx_print_state(char *buf, int state)
{
	if (state > 0)
		return sprintf(buf, "enabled\n");
	else if (state == 0)
		return sprintf(buf, "disabled\n");
	else
		return sprintf(buf, "unknown\n");
}

static ssize_t g22xx_suspend_mem_state_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	return g22xx_print_state(buf, gd->state_mem.enabled);
}
static DEVICE_ATTR(g22xx_suspend_mem_state, 0444,
	g22xx_suspend_mem_state_show, NULL);

static ssize_t g22xx_suspend_coldboot_uV_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	return sprintf(buf, "%d\n", gd->state_coldboot.uV);
}
static DEVICE_ATTR(g22xx_suspend_coldboot_microvolts, 0444,
	g22xx_suspend_coldboot_uV_show, NULL);

static ssize_t g22xx_suspend_coldboot_state_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	return g22xx_print_state(buf, gd->state_coldboot.enabled);
}
static DEVICE_ATTR(g22xx_suspend_coldboot_state, 0444,
	g22xx_suspend_coldboot_state_show, NULL);

static ssize_t g22xx_suspend_mem_uV_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	struct g22xx_desc *gd = to_g22xx_desc(rdev->desc);

	return sprintf(buf, "%d\n", gd->state_mem.uV);
}
static DEVICE_ATTR(g22xx_suspend_mem_microvolts, 0444,
	g22xx_suspend_mem_uV_show, NULL);

static struct attribute *g22xx_dev_attrs[] = {
	&dev_attr_g22xx_suspend_mem_state.attr,
	&dev_attr_g22xx_suspend_mem_microvolts.attr,
	&dev_attr_g22xx_suspend_coldboot_state.attr,
	&dev_attr_g22xx_suspend_coldboot_microvolts.attr,
	NULL
};

static const struct attribute_group g22xx_dev_group = {
	.name = "realtek",
	.attrs = g22xx_dev_attrs,
};

static int g22xx_add_sysfs(struct device *dev)
{
	return sysfs_create_group(&dev->kobj, &g22xx_dev_group);
}

static inline void g22xx_init_regmap_field_one(struct regmap_field **dst,
	struct regmap_field *src)
{
	if (src)
		*dst = src;
}

static inline void g22xx_init_desc(struct g22xx_desc *gd,
	struct g22xx_desc_initdata *data, struct regmap_field **maps)
{
	const struct reg_field *rf;

	g22xx_init_regmap_field_one(&gd->on,    maps[data->idx_on]);
	g22xx_init_regmap_field_one(&gd->nvo,   maps[data->idx_nvo]);
	g22xx_init_regmap_field_one(&gd->svo,   maps[data->idx_svo]);
	g22xx_init_regmap_field_one(&gd->nmode, maps[data->idx_nmode]);
	g22xx_init_regmap_field_one(&gd->smode, maps[data->idx_smode]);

	if (data->idx_on != G22XX_REG_FIELD_INVALID) {
		rf = &data->regs[data->idx_on];
		gd->desc.enable_reg  = rf->reg;
		gd->desc.enable_mask = GENMASK(rf->msb, rf->lsb);
	}

	if (data->idx_nvo != G22XX_REG_FIELD_INVALID) {
		rf = &data->regs[data->idx_nvo];
		gd->desc.vsel_reg  = rf->reg;
		gd->desc.vsel_mask = GENMASK(rf->msb, rf->lsb);
	}
}


int g22xx_regulator_register(struct g22xx_device *gdev, struct g22xx_desc *gd,
	struct g22xx_desc_initdata *data)
{
	struct regulator_config config = {};
	struct regulation_constraints *c;

	g22xx_init_desc(gd, data, gdev->maps);

	config.dev = gdev->dev;
	config.driver_data = gd;
	config.regmap = gdev->regmap;

	gd->rdev = devm_regulator_register(gdev->dev, &gd->desc, &config);
	if (IS_ERR(gd->rdev))
		return PTR_ERR(gd->rdev);

	c = gd->rdev->constraints;

	/*
	 * copy state_mem to gd for mem/coldboot switching. if there is no
	 * sleep uV and mode, set the state to enable
	 */
	gd->state_mem = c->state_mem;
	if (gd->state_mem.uV == 0 && gd->state_mem.disabled == 0) {
		gd->state_mem.enabled = true;
		c->state_mem = gd->state_mem;
	}
	if (gd->state_coldboot.uV == 0 && gd->state_coldboot.disabled == 0)
		gd->state_coldboot.enabled = true;

	/* enable change mode */
	if (g22xx_is_ldo(gd))
		c->valid_modes_mask |= REGULATOR_MODE_NORMAL
			| REGULATOR_MODE_IDLE;
	else
		c->valid_modes_mask |= REGULATOR_MODE_NORMAL
			| REGULATOR_MODE_FAST;
	c->valid_ops_mask |= REGULATOR_CHANGE_MODE;

	g22xx_add_sysfs(&gd->rdev->dev);

	return 0;
}
EXPORT_SYMBOL_GPL(g22xx_regulator_register);

/* pm_power_off */
static struct regmap_field *g22xx_softoff;

static void g22xx_pm_power_off(void)
{
	if (WARN_ON(g22xx_softoff == NULL))
		return;

	pr_info("[PMIC] %s\n", __func__);
	regmap_field_write(g22xx_softoff, 0x1);
}

int g22xx_setup_pm_power_off(struct device *dev, struct regmap_field *map)
{
	if (!dev->of_node)
		return -ENOENT;

	if (!of_device_is_system_power_controller(dev->of_node))
		return 0;

	if (pm_power_off && pm_power_off != g22xx_pm_power_off)
		return -EBUSY;

	g22xx_softoff = map;
	pm_power_off = g22xx_pm_power_off;
	return 1;
}
EXPORT_SYMBOL_GPL(g22xx_setup_pm_power_off);

/* bootargs */
static bool g22xx_regcache_disable;

bool g22xx_regcache_disabled(void)
{
	return g22xx_regcache_disable;
}
EXPORT_SYMBOL_GPL(g22xx_regcache_disabled);

static int __init g22xx_regmap_setup(char *__unused)
{
	g22xx_regcache_disable = true;
	return 1;
}
__setup("g22xx_no_regcache", g22xx_regmap_setup);

