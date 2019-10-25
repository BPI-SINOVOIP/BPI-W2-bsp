/*
 * Realtek CPU cache supply coordinator
 *
 * Copyright (c) 2019, Realtek Semiconductor Corporation
 *
 * Author:
 *        Cheng-Yu Lee <cylee12@realtek.com>
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

#define pr_fmt(fmt) "rtk-ccsc: " fmt
#include <linux/cpufreq.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>

struct rtk_ccsc_data {
	struct device *dev;
	struct notifier_block nb;
	struct regulator *supply;
};

static int rtk_ccsc_cb(struct notifier_block *nb, unsigned long action, void *p)
{
	struct rtk_ccsc_data *data = container_of(nb, struct rtk_ccsc_data, nb);
	struct pre_voltage_change_data *pvcd = p;
	int target_uV;
	int ret;

	if (action != REGULATOR_EVENT_PRE_VOLTAGE_CHANGE)
		return  NOTIFY_DONE;

	if (pvcd->min_uV > 1050000)
		target_uV = 1000000;
	else if (pvcd->min_uV > 1000000)
		target_uV = 950000;
	else
		target_uV = 900000;

	ret = regulator_set_voltage(data->supply, target_uV, target_uV);
	if (ret)
		dev_warn(data->dev, "failed to set supply: %d\n", ret);

	return NOTIFY_OK;
}

static int rtk_ccsc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_ccsc_data *data;
	struct regulator *cpu_supply;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->dev = dev;
	data->supply = devm_regulator_get_optional(dev, "ldo3");
	ret = PTR_ERR(data->supply);
	if (ret < 0) {
		if (ret == -EPROBE_DEFER || ret == -ENODEV) {
			dev_dbg(dev, "ldo3: not ready\n");
			return -EPROBE_DEFER;
		}
		dev_err(dev, "failed to get regulator: %d\n", ret);
		return ret;
	}

	data->nb.notifier_call = rtk_ccsc_cb;

	cpu_supply = regulator_get_optional(dev, "cpudvs");
	if (IS_ERR(cpu_supply)) {
		ret = PTR_ERR(cpu_supply);
		dev_err(dev, "cpu_supply: failed to get regulator: %d\n", ret);
		return ret;
	}
	regulator_register_notifier(cpu_supply, &data->nb);
	regulator_put(cpu_supply);
	dev_info(dev, "initialized\n");
	return 0;
}

static struct platform_driver rtk_ccsc_driver = {
	.probe = rtk_ccsc_probe,
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-ccsc",
	},
};

static int __init rtk_ccsc_init(void)
{
	int ret;
	struct platform_device *pdev;

	ret = platform_driver_register(&rtk_ccsc_driver);
	if (ret) {
		pr_err("failed to register platform driver: %d\n", ret);
		return ret;
	}

	pdev = platform_device_register_simple("rtk-ccsc", PLATFORM_DEVID_NONE, NULL, 0);
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		pr_err("failed to register platform driver: %d\n", ret);
		platform_driver_unregister(&rtk_ccsc_driver);
		return ret;
	}
	return 0;
}
module_init(rtk_ccsc_init);
