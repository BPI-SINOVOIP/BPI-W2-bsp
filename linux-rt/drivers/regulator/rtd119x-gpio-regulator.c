/*
 * Pheonix GPIO Regulator
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/of_regulator.h>

struct rtd119x_regulator_data {
	struct regulator_desc desc;
	struct regulator_dev *rdev;
	int gpio[2];
	int sel;
};

static const int vtbl[] = {
	900000, 1050000, 1200000,
};

static const int gpio_val_tbl[] = {
	0, 1, 3,
};

static int rtd119x_gpio_list_voltage(struct regulator_dev *rdev,
	unsigned int sel)
{
	if (!rdev->desc->volt_table) {
		BUG_ON(!rdev->desc->volt_table);
		return -EINVAL;
	}

	dev_dbg(rdev_get_dev(rdev), "%s: sel=%d\n", __func__, sel);

	if (sel >= rdev->desc->n_voltages)
		return -EINVAL;

	return rdev->desc->volt_table[sel];
}

static int rtd119x_gpio_get_voltage_sel(struct regulator_dev *rdev)
{
	struct rtd119x_regulator_data *data = rdev_get_drvdata(rdev);

	dev_dbg(rdev_get_dev(rdev), "%s: sel=%d\n", __func__, data->sel);
	return data->sel;
}

static int rtd119x_gpio_set_voltage_sel(struct regulator_dev *rdev,
	unsigned sel)
{
	struct rtd119x_regulator_data *data = rdev_get_drvdata(rdev);
	int prev_sel = data->sel;
	unsigned char val[2];

	val[0] = gpio_val_tbl[sel] & 0x1;
	val[1] = (gpio_val_tbl[sel] >> 1) & 0x1;

	if (prev_sel < sel) {
		gpio_set_value(data->gpio[0], val[0]);
		if (prev_sel == 0 && sel == 2)
			udelay(20);
		gpio_set_value(data->gpio[1], val[1]);
	} else {
		gpio_set_value(data->gpio[1], val[1]);
		if (prev_sel == 2 && sel == 0)
			udelay(20);
		gpio_set_value(data->gpio[0], val[0]);
	}
	data->sel = sel;
	return 0;
}

static struct regulator_ops rtd119x_gpio_regulator_ops = {
	.list_voltage    = rtd119x_gpio_list_voltage,
	.set_voltage_sel = rtd119x_gpio_set_voltage_sel,
	.get_voltage_sel = rtd119x_gpio_get_voltage_sel,
};

static const struct regulator_desc common_desc = {
	.ops        = &rtd119x_gpio_regulator_ops,
	.n_voltages = ARRAY_SIZE(vtbl),
	.volt_table = vtbl,
	.type       = REGULATOR_VOLTAGE,
	.owner      = THIS_MODULE,
};

static int rtd119x_gpio_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct rtd119x_regulator_data *data;
	struct regulator_config cfg = {};
	const struct regulator_init_data *init_data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->gpio[0] = of_get_gpio(np, 0);
	data->gpio[1] = of_get_gpio(np, 1);
	if (!data->gpio[0] || !data->gpio[1])
		return -ENOMEM;

	ret = devm_gpio_request(dev, data->gpio[0], "voltage control-0");
	if (ret) {
		dev_err(dev, "gpio_request() returns %d for gpio-0\n", ret);
		return ret;
	}

	ret = devm_gpio_request(dev, data->gpio[1], "voltage control-1");
	if (ret) {
		dev_err(dev, "gpio_request() returns %d for gpio-1\n", ret);
		return ret;
	}

	data->sel = 2;
	memcpy(&data->desc, &common_desc, sizeof(struct regulator_desc));
	data->desc.name = devm_kstrdup(dev, np->name, GFP_KERNEL);

	init_data = of_get_regulator_init_data(dev, np, &data->desc);
	if (!init_data) {
		dev_err(dev, "of_get_regulator_init_data() returns NULL\n");
		return -EINVAL;
	}

	cfg.of_node     = np;
	cfg.dev         = dev;
	cfg.init_data   = init_data;
	cfg.driver_data = data;

	data->rdev = devm_regulator_register(dev, &data->desc, &cfg);
	if (IS_ERR(data->rdev)) {
		ret = PTR_ERR(data->rdev);
		dev_err(dev, "regulator_register() returns %d\n", ret);
		return ret;
	}
	return 0;
}


static struct of_device_id rtd119x_gpio_regulator_ids[] = {
	{ .compatible = "realtek,rtd119x-gpio-regulator" },
	{}
};
MODULE_DEVICE_TABLE(of, rtd119x_gpio_regulator_id);

static struct platform_driver rtd119x_gpio_regulator_driver = {
	.probe  = rtd119x_gpio_regulator_probe,
	.driver	= {
		.name	= "rtd119x-gpio-regulator",
		.of_match_table = rtd119x_gpio_regulator_ids,
	},
};
module_platform_driver(rtd119x_gpio_regulator_driver);

MODULE_DESCRIPTION("GPIO Regulator for RTD-119x Platform");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtd119x-gpio-regulator");
