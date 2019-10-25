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
#include <linux/regulator/sy8827e.h>
#include <linux/regmap.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_regmap.h>

struct sy8827e_data {
	const struct regulator_init_data *init_data;
	struct regmap *regmap;
	struct i2c_client *client;
	struct device *dev;
	struct regulator_dev *rdev;

	struct regulator_state state_suspend;
	struct regulator_state state_coldboot;

	struct regmap_field *nmode;
	struct regmap_field *smode;
	struct regmap_field *svsel;
	struct regmap_field *sen;
};

static void sy8827e_regulator_prepare_state_suspend(struct sy8827e_data *data,
	int is_coldboot)
{
	struct regulator_state *state;

	state = &data->rdev->constraints->state_mem;
	*state = is_coldboot ? data->state_coldboot : data->state_suspend;
}

/* of_map_mode */
static unsigned int sy8827e_regulator_of_map_mode(unsigned int mode)
{
	if (mode == 1)
		return REGULATOR_MODE_FAST;
	return REGULATOR_MODE_NORMAL;
}

static unsigned int sy8827e_regulator_get_mode(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	unsigned int val;
	int ret;

	ret = regmap_field_read(data->nmode, &val);
	if (ret)
		return ret;
	return val == 1 ? REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
}

static int sy8827e_regulator_set_mode(struct regulator_dev *rdev,
	unsigned int mode)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	unsigned int val = 0;

	if (mode & REGULATOR_MODE_FAST)
		val = 1;
	regmap_field_write(data->nmode, val);
	return 0;
}

static int sy8827e_regulator_set_suspend_voltage(struct regulator_dev *rdev,
	int uV)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);
	int vsel;

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	vsel = regulator_map_voltage_linear(rdev, uV, uV);
	if (vsel < 0)
		return -EINVAL;

	regmap_field_write(data->sen, 1);
	regmap_field_write(data->svsel, vsel);
	return 0;
}

static int sy8827e_regulator_set_suspend_enable(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(data->sen, 1);
	return 0;
}

static int sy8827e_regulator_set_suspend_disable(struct regulator_dev *rdev)
{
	struct sy8827e_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s\n", __func__);
	regmap_field_write(data->sen, 0);
	return 0;
}


static const struct regulator_ops sy8827e_regulator_ops = {
	.get_voltage_sel     = regulator_get_voltage_sel_regmap,
	.set_voltage_sel     = regulator_set_voltage_sel_regmap,
	.list_voltage        = regulator_list_voltage_linear,
	.map_voltage         = regulator_map_voltage_linear,
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
	.min_uV          = 712500,
	.uV_step         = 12500,
	.n_voltages      = 64,
	.vsel_reg        = SY8827E_REG_VSEL0,
	.vsel_mask       = SY8827E_NSEL0_MASK,
	.enable_reg      = SY8827E_REG_VSEL0,
	.enable_mask     = SY8827E_BUCK_EN0_MASK,
	.enable_val      = SY8827E_BUCK_EN0_MASK,
	.disable_val     = 0,
};

/* regmap */
static const struct reg_default sy8827e_regmap_defaults[] = {
	{ .reg = SY8827E_REG_VSEL0, .def = 0x97, },
	{ .reg = SY8827E_REG_VSEL1, .def = 0x97, },
};

static bool sy8827e_regmap_writeable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SY8827E_REG_VSEL0:
	case SY8827E_REG_VSEL1:
		return true;
	}
	return false;
}

static bool sy8827e_regmap_readable_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SY8827E_REG_VSEL0:
	case SY8827E_REG_VSEL1:
	case SY8827E_REG_ID0:
	case SY8827E_REG_ID1:
		return true;
	}
	return false;
}

static bool sy8827e_regmap_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SY8827E_REG_ID0:
	case SY8827E_REG_ID1:
		return true;
	}
	return false;
}

static const struct regmap_config sy8827e_regmap_config = {
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_register     = 0x05,
	.cache_type       = REGCACHE_FLAT,
	.reg_defaults     = sy8827e_regmap_defaults,
	.num_reg_defaults = ARRAY_SIZE(sy8827e_regmap_defaults),
	.writeable_reg    = sy8827e_regmap_writeable_reg,
	.readable_reg     = sy8827e_regmap_readable_reg,
	.volatile_reg     = sy8827e_regmap_volatile_reg,
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

	init_data = of_get_regulator_init_data(dev, np, &sy8827e_desc);
	if (!init_data)	{
		dev_err(dev, "failed to get regulator_init_data\n");
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

static struct regmap_field *create_regmap_field(struct sy8827e_data *data,
        u32 reg, u32 mask)
{
	u32 msb = fls(mask) - 1;
	u32 lsb = ffs(mask) - 1;
	struct reg_field map = REG_FIELD(reg, lsb, msb);
	struct regmap_field *rmap;

	if (reg == 0 && mask == 0)
		return NULL;
	dev_dbg(data->dev, "reg=%02x, mask=%02x, lsb=%d, msb=%d\n",
		reg, mask, lsb, msb);
	rmap = devm_regmap_field_alloc(data->dev, data->regmap, map);
	if (IS_ERR(rmap)) {
		dev_err(data->dev, "failed to alloc regmap_field (reg=%02x, mask=%02x): %ld\n",
			reg, mask, PTR_ERR(rmap));
	}
	return rmap;
}

static int sy8827e_init_regmap_fields(struct sy8827e_data *data)
{
	data->sen = create_regmap_field(data, SY8827E_REG_VSEL1, SY8827E_BUCK_EN1_MASK);
	if (IS_ERR(data->sen))
		return PTR_ERR(data->sen);
	data->svsel = create_regmap_field(data, SY8827E_REG_VSEL1, SY8827E_NSEL1_MASK);
	if (IS_ERR(data->svsel))
		return PTR_ERR(data->svsel);
	data->smode = create_regmap_field(data, SY8827E_REG_VSEL1, SY8827E_MODE1_MASK);
	if (IS_ERR(data->smode))
		return PTR_ERR(data->smode);
	data->nmode = create_regmap_field(data, SY8827E_REG_VSEL0, SY8827E_MODE0_MASK);
	if (IS_ERR(data->nmode))
		return PTR_ERR(data->nmode);
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
	int ret;
	u32 chip_id, rev;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	regmap = devm_rtk_regmap_init_i2c(client, &sy8827e_regmap_config);
	if (IS_ERR(regmap))
		return -EINVAL;

	data->regmap = regmap;
	data->client = client;
	data->dev    = dev;

	ret = regmap_read(data->regmap, SY8827E_REG_ID0, &chip_id);
	if (ret) {
		dev_err(dev, "failed to read chip_id: %d\n", ret);
		return ret;
	}
	if (chip_id != 0x88) {
		dev_err(dev, "chip_id(%02x) not match\n", chip_id);
		return -EINVAL;
	}
	regmap_read(data->regmap, SY8827E_REG_ID1, &rev);
	dev_info(dev, "sy8827e(%02x) rev%d\n", chip_id, rev);

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

	ret = sy8827e_init_regmap_fields(data);
	if (ret) {
		dev_err(dev, "sy8827e_init_regmap_fields() returns %d\n", ret);
		return ret;
	}

	/* enable opmode */
	c = (void *)&data->init_data->constraints;
	c->valid_modes_mask |= REGULATOR_MODE_NORMAL | REGULATOR_MODE_FAST;
	c->valid_ops_mask |= REGULATOR_CHANGE_MODE;

	config.of_node     = np;
	config.dev         = dev;
	config.driver_data = data;
	config.init_data   = data->init_data;
	config.regmap      = regmap;

	data->rdev = devm_regulator_register(dev, &sy8827e_desc, &config);
	if (IS_ERR(data->rdev)) {
		ret = PTR_ERR(data->rdev);
		dev_err(dev, "regulator_register() returns %d\n", ret);
		return ret;
	}

	i2c_set_clientdata(client, data);

	dev_info(dev, "initialized\n");
	return 0;
}

static void sy8827e_regulator_shutdown(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct sy8827e_data *data = i2c_get_clientdata(client);

	dev_info(dev, "enter %s\n", __func__);
	sy8827e_regulator_prepare_state_suspend(data, 1);
	regulator_suspend_prepare(PM_SUSPEND_MEM);
	dev_info(dev, "exit %s\n", __func__);
}

static const struct i2c_device_id sy8827e_regulator_ids[] = {
	{"sy8827e", 0},
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
