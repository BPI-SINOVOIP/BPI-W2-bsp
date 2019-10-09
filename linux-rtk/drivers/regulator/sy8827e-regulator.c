/*
 * sy8827e-regulator.c - Silergy-SY8827E Regulator Driver
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "sy8827e: " fmt

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_regmap.h>

/* reg_field id */
enum {
	SY8827E_REG_FIELD_BUCK_EN0,
	SY8827E_REG_FIELD_MODE0,
	SY8827E_REG_FIELD_NSEL0,
	SY8827E_REG_FIELD_BUCK_EN1,
	SY8827E_REG_FIELD_MODE1,
	SY8827E_REG_FIELD_NSEL1,
	SY8827E_REG_FIELD_VENDOR,
	SY8827E_REG_FIELD_DIE_ID,
	SY8827E_REG_FIELD_DIE_REV,
	SY8827E_REG_FIELD_MAX,
};

struct sy8827e_data {
	struct regulator_desc desc;
	const struct regulator_init_data *init_data;
	struct regmap *regmap;
	struct i2c_client *client;
	struct device *dev;
	struct regulator_dev *rdev;
	struct regmap_field *maps[SY8827E_REG_FIELD_MAX];
	struct regulator_state state_suspend;
	struct regulator_state state_coldboot;
};

static void sy8827e_regulator_prepare_state_suspend(struct sy8827e_data *data,
	int is_coldboot)
{
	struct regulator_state *state;

	state = &data->rdev->constraints->state_mem;
	*state = is_coldboot ? data->state_coldboot : data->state_suspend;
}

/* reg_field */
static const struct reg_field regs[SY8827E_REG_FIELD_MAX] __initconst = {
	[SY8827E_REG_FIELD_BUCK_EN0] = REG_FIELD(0x00, 7, 7),
	[SY8827E_REG_FIELD_MODE0]    = REG_FIELD(0x00, 6, 6),
	[SY8827E_REG_FIELD_NSEL0]    = REG_FIELD(0x00, 0, 5),
	[SY8827E_REG_FIELD_BUCK_EN1] = REG_FIELD(0x01, 7, 7),
	[SY8827E_REG_FIELD_MODE1]    = REG_FIELD(0x01, 6, 6),
	[SY8827E_REG_FIELD_NSEL1]    = REG_FIELD(0x01, 0, 5),
	[SY8827E_REG_FIELD_VENDOR]   = REG_FIELD(0x03, 5, 7),
	[SY8827E_REG_FIELD_DIE_ID]   = REG_FIELD(0x04, 0, 3),
	[SY8827E_REG_FIELD_DIE_REV]  = REG_FIELD(0x05, 0, 3),
};

/* of_map_mode */
static unsigned int sy8827e_regulator_of_map_mode(unsigned int mode)
{
	if (mode == 1)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}

static const struct regulator_linear_range linear_ranges[] = {
	REGULATOR_LINEAR_RANGE(712500,  0x00, 0x3F, 12500),
};

static unsigned int sy8827e_regulator_get_mode(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	struct regmap_field **maps = data->maps;
	unsigned int val;
	int ret;

	ret = regmap_field_read(maps[SY8827E_REG_FIELD_MODE0], &val);
	if (ret)
		return ret;
	return val == 1 ? REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
}

static int sy8827e_regulator_set_mode(struct regulator_dev *rdev,
	unsigned int mode)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	struct regmap_field **maps = data->maps;
	unsigned int val = 0;

	if (mode & REGULATOR_MODE_FAST)
		val = 1;
	regmap_field_write(maps[SY8827E_REG_FIELD_MODE0], val);
	return 0;
}

static int sy8827e_regulator_set_suspend_voltage(struct regulator_dev *rdev,
	int uV)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	struct regmap_field **maps = data->maps;
	int vsel;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	vsel = regulator_map_voltage_linear_range(rdev, uV, uV);
	if (vsel < 0)
		return -EINVAL;

	regmap_field_write(maps[SY8827E_REG_FIELD_BUCK_EN1], 1);
	regmap_field_write(maps[SY8827E_REG_FIELD_NSEL1], vsel);
	return 0;
}

static int sy8827e_regulator_set_suspend_enable(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	struct regmap_field **maps = data->maps;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(maps[SY8827E_REG_FIELD_BUCK_EN1], 1);
	return 0;
}

static int sy8827e_regulator_set_suspend_disable(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	struct regmap_field **maps = data->maps;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(maps[SY8827E_REG_FIELD_BUCK_EN1], 0);
	return 0;
}


static const struct regulator_ops sy8827e_regulator_ops = {
	.get_voltage_sel     = regulator_get_voltage_sel_regmap,
	.set_voltage_sel     = regulator_set_voltage_sel_regmap,
	.list_voltage        = regulator_list_voltage_linear_range,
	.map_voltage         = regulator_map_voltage_linear_range,
	.enable              = regulator_enable_regmap,
	.disable             = regulator_disable_regmap,
	.is_enabled          = regulator_is_enabled_regmap,
	.get_mode            = sy8827e_regulator_get_mode,
	.set_mode            = sy8827e_regulator_set_mode,
	.set_suspend_voltage = sy8827e_regulator_set_suspend_voltage,
	.set_suspend_enable  = sy8827e_regulator_set_suspend_enable,
	.set_suspend_disable = sy8827e_regulator_set_suspend_disable,
};

static const struct regulator_desc sy8827e_desc = {
	.owner           = THIS_MODULE,
	.name            = "silergy-sy8827e",
	.ops             = &sy8827e_regulator_ops,
	.type            = REGULATOR_VOLTAGE,
	.of_map_mode     = sy8827e_regulator_of_map_mode,
	.linear_ranges   = linear_ranges,
	.n_linear_ranges = ARRAY_SIZE(linear_ranges),
	.vsel_reg        = 0x0,
	.vsel_mask       = 0x3f,
	.enable_reg      = 0x0,
	.enable_mask     = BIT(7),
	.enable_val      = BIT(7),
	.disable_val     = 0,
};

/* regmap */
static const struct reg_default sy8827e_regmap_defaults[] = {
	{ .reg = 0x00, .def = 0xA7, },
	{ .reg = 0x01, .def = 0xA7, },
	{ .reg = 0x02, .def = 0x80, },
};

static bool sy8827e_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	return reg <= 2;
}

static bool sy8827e_regmap_readable_reg(struct device *dev, unsigned int reg)
{
	return 1;
}

static bool sy8827e_regmap_precious_reg(struct device *dev, unsigned int reg)
{
	return reg >= 3;
}

static const struct regmap_config sy8827e_regmap_config_no_cache = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x05,
	.writeable_reg    = sy8827e_regmap_writeable_reg,
	.readable_reg     = sy8827e_regmap_readable_reg,
	.precious_reg     = sy8827e_regmap_precious_reg,
};

static const struct regmap_config sy8827e_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x05,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = sy8827e_regmap_defaults,
	.num_reg_defaults = ARRAY_SIZE(sy8827e_regmap_defaults),
	.writeable_reg    = sy8827e_regmap_writeable_reg,
	.readable_reg     = sy8827e_regmap_readable_reg,
	.precious_reg     = sy8827e_regmap_precious_reg,
};

/* pm */
static int sy8827e_regulator_suspend(struct device *dev)
{
	struct sy8827e_data *data = dev_get_drvdata(dev);

#ifdef CONFIG_SUSPEND
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY)
		goto done;
#endif
	dev_info(dev, "Enter %s\n", __func__);
	sy8827e_regulator_prepare_state_suspend(data, 0);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
done:
	return 0;
}

static const struct dev_pm_ops sy8827e_regulator_pm_ops = {
	.suspend = sy8827e_regulator_suspend,
};

static int of_parse_regulator_state(struct device_node *np,
	struct regulator_state *state)
{
	unsigned int val;

	if (!np)
		return -ENOENT;

	if (of_property_read_bool(np, "regulator-on-in-suspend"))
		state->enabled = true;

	if (of_property_read_bool(np, "regulator-off-in-suspend"))
		state->disabled = true;

	if (!of_property_read_u32(np, "regulator-suspend-microvolt", &val))
		state->uV = val;

	/* if no config */
	if (state->uV == 0 && state->disabled == 0)
		state->enabled = true;

	return 0;
}

static int of_config_sy8827e_regulator(struct device *dev,
	struct device_node *np, struct sy8827e_data *data)
{
	const struct regulator_init_data *init_data;
	struct device_node *child;

	init_data = of_get_regulator_init_data(dev, np, &data->desc);
	if (!init_data)	{
		dev_err(dev, "of_get_regulator_init_data() returns NULL\n");
		return -ENOMEM;
	}
	data->init_data = init_data;

	child = of_get_child_by_name(np, "regulator-state-mem");
	if (child)
		of_parse_regulator_state(child, &data->state_suspend);


	child = of_get_child_by_name(np, "regulator-state-coldboot");
	if (child)
		of_parse_regulator_state(child, &data->state_coldboot);
	else
		data->state_coldboot = data->state_suspend;

	return 0;
}

static int sy8827e_regulator_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *np = dev->of_node;
	struct sy8827e_data *data;
	struct regulator_config config = { 0 };
	struct regmap *regmap;
	struct regulation_constraints *c;
	const struct regmap_config *cfg;
	struct regmap_field **maps;
	int i, ret;

	dev_info(dev, "%s\n", __func__);

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	maps = data->maps;
#if 0
	/* bootargs: disable regcache */
	if (g22xx_regcache_disabled()) {
		dev_info(dev, "no regcache\n");
		cfg = &sy8827e_regmap_config_no_cache;
	} else
		cfg = &sy8827e_regmap_config;
#else
	cfg = &sy8827e_regmap_config;
#endif
	regmap = devm_rtk_regmap_i2c_init(dev, client, &sy8827e_regmap_config);
	if (IS_ERR(regmap))
		return -EINVAL;

	/* convert all reg_field to regmap_field */
	for (i = 0; i < SY8827E_REG_FIELD_MAX; i++) {
		struct regmap_field *rf;

		rf = devm_regmap_field_alloc(dev, regmap, regs[i]);
		if (IS_ERR(rf)) {
			ret = PTR_ERR(rf);
			dev_err(dev, "Failed to alloc regmap field %d: %d\n",
				i, ret);
			return ret;
		}
		maps[i] = rf;
	}

	data->regmap = regmap;
	data->client = client;
	data->dev    = dev;
	memcpy(&data->desc, &sy8827e_desc, sizeof(data->desc));

	ret = of_config_sy8827e_regulator(dev, np, data);
	if (ret) {
		dev_err(dev, "of_config_sy8827e_regulator() returns %d\n", ret);
		return ret;
	}

	/* if not config from dt */
	if (data->state_suspend.uV == 0 && data->state_suspend.disabled == 0)
		data->state_suspend.enabled = true;
	if (data->state_coldboot.uV == 0 && data->state_coldboot.disabled == 0)
		data->state_coldboot.enabled = true;

	/* enable opmode */
	c = (void *)&data->init_data->constraints;
	c->valid_modes_mask |= REGULATOR_MODE_NORMAL | REGULATOR_MODE_FAST;
	c->valid_ops_mask |= REGULATOR_CHANGE_MODE;

	config.of_node     = np;
	config.dev         = dev;
	config.driver_data = data;
	config.init_data   = data->init_data;
	config.regmap      = regmap;

	data->rdev = devm_regulator_register(dev, &data->desc, &config);
	if (IS_ERR(data->rdev)) {
		ret = PTR_ERR(data->rdev);
		dev_err(dev, "regulator_register() returns %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, data);

	return 0;
}

static void sy8827e_regulator_shutdown(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct sy8827e_data *data = i2c_get_clientdata(client);

	dev_info(dev, "Enter %s\n", __func__);
	sy8827e_regulator_prepare_state_suspend(data, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "Exit %s\n", __func__);
}

static const struct i2c_device_id sy8827e_regulator_ids[] = {
	{"silergy,sy8827e", 0},
	{"silergy-sy8827e", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, sy8827e_regulator_ids);

static struct i2c_driver sy8827e_regulator_driver = {
	.driver = {
		.name = "silergy-sy8827e",
		.owner = THIS_MODULE,
		.pm = &sy8827e_regulator_pm_ops,
	},
	.id_table = sy8827e_regulator_ids,
	.probe    = sy8827e_regulator_probe,
	.shutdown = sy8827e_regulator_shutdown,
};
module_i2c_driver(sy8827e_regulator_driver);

MODULE_DESCRIPTION("Silergy-SY8827E Regulator Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");
