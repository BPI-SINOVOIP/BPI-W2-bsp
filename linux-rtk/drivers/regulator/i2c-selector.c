/*
 * selector.c - i2c regulator selector
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#define pr_fmt(fmt) "selector: " fmt

#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/suspend.h>
#include <linux/mfd/g2237.h>
#include "internal.h"

extern struct i2c_driver g2237_i2c_driver;
extern struct i2c_driver apw8889_i2c_driver;
enum {
	I2C_SELECTOR_DRIVER_G2237,
	I2C_SELECTOR_DRIVER_APW8889,
};

static struct i2c_driver selector_driver;

static int selector_read_reg(struct i2c_client *i2c, u8 reg, u8 *val)
{
	struct i2c_msg xfer[2];
	int ret = 0;

	xfer[0].addr = i2c->addr;
	xfer[0].flags = 0;
	xfer[0].len = 1;
	xfer[0].buf = &reg;

	xfer[1].addr = i2c->addr;
	xfer[1].flags = I2C_M_RD;
	xfer[1].len = 1;
	xfer[1].buf = val;

	ret = i2c_transfer(i2c->adapter, xfer, 2);
	if (ret == 2)
		return 0;
	else if (ret < 0)
		return ret;
	else
		return -EIO;
}

static int selector_get_selection(struct i2c_client *client)
{
	u8 val;

	selector_read_reg(client, G2237_REG_CHIP_ID, &val);
	if (val == 0x25)
		return I2C_SELECTOR_DRIVER_G2237;
	else
		return I2C_SELECTOR_DRIVER_APW8889;
}

static int selector_match_from_sibling(struct i2c_client *client,
				       struct i2c_driver *selection_drv,
				       struct device_node **out_np,
				       const struct i2c_device_id **out_id)
{
	struct device *dev = &client->dev;
	struct device_node *parent = dev->parent->of_node;
	struct device_node *child;
	char modalias[I2C_NAME_SIZE];
	const struct i2c_device_id *id = selection_drv->id_table;
	int ret;

	while (id->name[0]) {
		for_each_child_of_node(parent, child) {
			ret = of_modalias_node(child, modalias, sizeof(modalias));
			if (ret)
				continue;
			dev_dbg(dev, "%s: compare id=%s modalias=%s\n", child->name,
				id->name, modalias);
			if (!strcmp(id->name, modalias)) {
				*out_np = child;
				*out_id = id;
				return 0;
			}
		}
		id++;
	}
	return -EINVAL;
}

static void selector_update_selector_driver(struct i2c_driver *drv,
					    const struct i2c_driver *src)
{
	WARN_ON(drv->driver.pm);
	WARN_ON(drv->shutdown);
	WARN_ON(drv->remove);

	drv->driver.pm = src->driver.pm;
	drv->shutdown  = src->shutdown;
	drv->remove    = src->remove;
}

static void selector_replace_rdev_np(struct device *dev,
				     struct device_node *selector_np,
				     const char *selection_id)
{
	struct device_node *saved_np = dev->of_node;
	struct device_node *child;
	struct regulator *reg;

	for_each_child_of_node(selector_np, child) {
		if (!of_device_is_compatible(child, "supply-selector"))
			continue;

		dev->of_node = child;
		reg = regulator_get(dev, selection_id);
		if (IS_ERR(reg)) {
			dev_err(dev, "regulator_get() with supply-name %s returns %ld\n",
				selection_id, PTR_ERR(reg));
			continue;
		}

		mutex_lock(&reg->rdev->mutex);
		reg->rdev->dev.of_node = child;
		mutex_unlock(&reg->rdev->mutex);

		regulator_put(reg);
	}

	dev->of_node = saved_np;
}

static int selector_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device_node *np = dev->of_node;
	struct device_node *selection_np;
	const struct i2c_device_id *selection_id;
	struct i2c_driver *selection_driver = NULL;
	int ret;

	dev_info(dev, "%s\n", __func__);

	switch (selector_get_selection(client))
	{
	case I2C_SELECTOR_DRIVER_G2237:
		selection_driver = &g2237_i2c_driver;
		break;
	case I2C_SELECTOR_DRIVER_APW8889:
		selection_driver = &apw8889_i2c_driver;
		break;
	}
	if (!selection_driver) {
		dev_err(dev, "no selection_driver\n");
		return -ENODEV;
	}

	ret = selector_match_from_sibling(client, selection_driver,
		&selection_np, &selection_id);
	if (ret) {
		dev_err(dev, "selector_match_from_sibling() returns %d\n", ret);
		return ret;
	}

	dev_info(dev, "driver=%s\n", selection_driver->driver.name);
	dev_info(dev, "id=%s\n", selection_id->name);
	dev_info(dev, "device_node=%s\n", selection_np->name);

	selector_update_selector_driver(&selector_driver, selection_driver);

	/* update device */
	dev->of_node = selection_np;

	/* probe */
	ret = selection_driver->probe(client, selection_id);
	if (ret)
		return ret;

	selector_replace_rdev_np(dev, np, selection_id->name);
	return 0;
}

static const struct i2c_device_id selector_ids[] = {
	{"regulator-selector", 0},
	{}
};
MODULE_DEVICE_TABLE(i2c, selector_ids);

static struct i2c_driver selector_driver = {
	.driver = {
		.name = "reg-sel",
		.owner = THIS_MODULE,
	},
	.id_table = selector_ids,
	.probe    = selector_probe,
};
module_i2c_driver(selector_driver);

MODULE_DESCRIPTION("Regulator Selector Driver");
MODULE_AUTHOR("Cheng-Yu Lee <cylee12@realtek.com>");
MODULE_LICENSE("GPL");
