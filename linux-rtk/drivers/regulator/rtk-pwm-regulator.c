/*
 * rtk-pwm-regulator.c - Realtek PWM Regulator Driver
 *
 * Copyright (C) 2018,2019 Realtek Semiconductor Corporation
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
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pwm.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regulator/machine.h>
#include <linux/slab.h>

struct pwm_voltage {
	unsigned int volt;
	unsigned int duty;
	unsigned int period;
};

struct pwm_regulator_data {
	struct regulator_desc desc;
	const struct regulator_init_data *init_data;
	struct pwm_device *pwm;
	struct pwm_voltage *volt_table;
	int n_volts;
	int sel;
};

static int rtk_pwm_regulator_get_voltage(struct regulator_dev *rdev)
{
	struct pwm_regulator_data *data = rdev_get_drvdata(rdev);

	return data->volt_table[data->sel].volt;
}

static int rtk_pwm_regulator_set_voltage(struct regulator_dev *rdev,
	int min_uV, int max_uV, unsigned *selector)
{
	struct pwm_regulator_data *data = rdev_get_drvdata(rdev);
	struct pwm_voltage *p = NULL;
	int i;
	int best_volt = INT_MAX;

	for (i = 0; i < data->n_volts; i++) {
		if (data->volt_table[i].volt < best_volt &&
			data->volt_table[i].volt >= min_uV &&
			data->volt_table[i].volt <= max_uV) {
			p = &data->volt_table[i];
			best_volt = data->volt_table[i].volt;
			if (selector)
				*selector = i;
		}
	}

	if (!p)
		return -EINVAL;

	pwm_config(data->pwm, p->duty, p->period);
	data->sel = *selector;

	return 0;
}

static int rtk_pwm_regulator_list_voltage(struct regulator_dev *rdev,
	unsigned selector)
{
	struct pwm_regulator_data *data = rdev_get_drvdata(rdev);

	if (selector >= data->n_volts)
		return -EINVAL;

	return data->volt_table[selector].volt;
}

static int rtk_pwm_regulator_enable(struct regulator_dev *dev)
{
	struct pwm_regulator_data *data = rdev_get_drvdata(dev);

	return pwm_enable(data->pwm);
}

static int rtk_pwm_regulator_disable(struct regulator_dev *dev)
{
	struct pwm_regulator_data *data = rdev_get_drvdata(dev);

	pwm_disable(data->pwm);
	return 0;
}
static struct regulator_ops rtk_pwm_regulator_ops  = {
	.list_voltage = rtk_pwm_regulator_list_voltage,
	.set_voltage  = rtk_pwm_regulator_set_voltage,
	.get_voltage  = rtk_pwm_regulator_get_voltage,
	.enable       = rtk_pwm_regulator_enable,
	.disable      = rtk_pwm_regulator_disable,
};

static const struct regulator_desc common_desc = {
	.owner       = THIS_MODULE,
	.name        = "rtk-pwm-regulator",
	.ops         = &rtk_pwm_regulator_ops,
	.type        = REGULATOR_VOLTAGE,
	.supply_name = "pwm",
};

static int of_parse_voltage_table(struct device *dev, struct device_node *np,
	struct pwm_regulator_data *data)
{
	unsigned int len = 0;
	int i;
	struct pwm_voltage *pvolt;
	int prop_len;
	const unsigned int *prop_val;

	prop_val = of_get_property(np, "voltage-table", &prop_len);
	prop_len /= sizeof(unsigned int);
	if (!prop_val || (prop_len / 3) == 0 || (prop_len % 3) != 0)
		return -EINVAL;

	len = prop_len / 3;
	pvolt = devm_kcalloc(dev, sizeof(*data->volt_table), len, GFP_KERNEL);
	if (!pvolt)
		return -ENOMEM;

	for (i = 0; i < len; i++) {
		pvolt[i].volt   = of_read_number(prop_val++, 1);
		pvolt[i].duty   = of_read_number(prop_val++, 1);
		pvolt[i].period = of_read_number(prop_val++, 1);

		dev_dbg(dev, "%s: volt_table[%d]: v=%d d=%d p=%d\n", __func__,
			i, pvolt[i].volt, pvolt[i].duty, pvolt[i].period);
	}

	data->volt_table = pvolt;
	data->n_volts = len;
	return 0;
}

static int of_config_pwm_regulator(struct device *dev, struct device_node *np,
	struct pwm_regulator_data *data)
{
	const struct regulator_init_data *init_data;
	int ret;

	data->pwm = devm_of_pwm_get(dev, np, NULL);
	if (IS_ERR(data->pwm)) {
		ret = PTR_ERR(data->pwm);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get pwm: %d\n", ret);
		return ret;
	}

	init_data = of_get_regulator_init_data(dev, np, &data->desc);
	if (!init_data) {
		dev_err(dev, "failed to get regulator_init_data\n");
		return -ENOMEM;
	}
	data->init_data = init_data;

	ret = of_parse_voltage_table(dev, np, data);
	if (ret) {
		dev_err(dev, "failed to parse voltage-table: %d\n", ret);
		return ret;
	}

	return 0;
}

static int rtk_pwm_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct pwm_regulator_data *data;
	struct regulator_config config = { 0 };
	struct regulator_dev *rdev;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	memcpy(&data->desc, &common_desc, sizeof(common_desc));

	ret = of_config_pwm_regulator(dev, dev->of_node, data);
	if (ret)
		return ret;

	config.of_node     = dev->of_node;
	config.dev         = dev;
	config.driver_data = data;
	config.init_data   = data->init_data;

	ret = pwm_adjust_config(data->pwm);
	if (ret)
		return ret;

	rdev = devm_regulator_register(dev, &data->desc, &config);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(dev, "failed to register regulator: %d\n", ret);
		return ret;
	}

	dev_info(dev, "initialized");
	return 0;
}

static const struct of_device_id rtk_pwm_regulator_ids[] = {
	{.compatible = "realtek,pwm-regulator" },
	{}
};

static struct platform_driver rtk_pwm_regulator_driver = {
	.probe  = rtk_pwm_regulator_probe,
	.driver = {
		.name   = "rtk-pwm-regulator",
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(rtk_pwm_regulator_ids),
	},
};
module_platform_driver(rtk_pwm_regulator_driver);

