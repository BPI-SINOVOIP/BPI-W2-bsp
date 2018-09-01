/*
 * sensor.c - Realtek generic thermal sensor driver
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2017-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/thermal.h>
#include "../thermal_core.h"
#include "sensor.h"

static LIST_HEAD(sensor_device_list);
static const struct thermal_zone_of_device_ops thermal_sensor_ops;
static const struct of_device_id thermal_sensor_of_match[];

static struct thermal_sensor_device *tz_to_tdev(struct thermal_zone_device *tz)
{
	struct thermal_sensor_device *pos;

	list_for_each_entry(pos, &sensor_device_list, list)
		if (pos->tz == tz)
			return pos;
	return NULL;
}

static int thermal_sensor_set_mode(struct thermal_zone_device *tz,
	enum thermal_device_mode mode)
{
	struct thermal_instance *pos;
	struct thermal_sensor_device *tdev = tz_to_tdev(tz);

	if (mode  == THERMAL_DEVICE_DISABLED) {
		/*
		 * do original of_thermal_ops->set_mode to update its internal
		 * status and clear polling_delay.
		 */
		tdev->set_mode(tz, mode);

		/* clear passive and passive_delay */
		mutex_lock(&tz->lock);
		tz->passive = 0;
		tz->passive_delay = 0;
		cancel_delayed_work(&tz->poll_queue);
		mutex_unlock(&tz->lock);

		/* reset cdev state */
		list_for_each_entry(pos, &tz->thermal_instances, tz_node) {
			if (pos->target == THERMAL_NO_TARGET)
				continue;
			pos->target = THERMAL_NO_TARGET;
			pos->cdev->updated = false;
		}

		/* update cdev */
		list_for_each_entry(pos, &tz->thermal_instances, tz_node)
			thermal_cdev_update(pos->cdev);

	} else {
		mutex_lock(&tz->lock);
		tz->passive_delay = tdev->passive_delay;
		mutex_unlock(&tz->lock);
		tdev->set_mode(tz, mode);
	}

	return 0;
}

static int thermal_sensor_device_add(struct device *dev,
	struct thermal_sensor_device *tdev,
	const struct thermal_sensor_desc *desc)
{
	tdev->dev = dev;
	tdev->ops = &thermal_sensor_ops;
	tdev->desc = desc;

	tdev->sensors = devm_kcalloc(dev, desc->num_sensors,
		sizeof(*tdev->sensors), GFP_KERNEL);
	if (!tdev->sensors)
		return -ENOMEM;

	thermal_sensor_hw_init(tdev);
	thermal_sensor_hw_reset(tdev);

	tdev->tz = thermal_zone_of_sensor_register(dev, 0, tdev, tdev->ops);
	if (IS_ERR(tdev->tz))
		return PTR_ERR(tdev->tz);

	list_add(&tdev->list, &sensor_device_list);
	tdev->passive_delay = tdev->tz->passive_delay;
	tdev->polling_delay = tdev->tz->polling_delay;
	tdev->set_mode = tdev->tz->ops->set_mode;
	tdev->tz->ops->set_mode = thermal_sensor_set_mode;
	return 0;
}

void thermal_sensor_device_remove(struct thermal_sensor_device *tdev)
{
	list_del(&tdev->list);
	thermal_zone_of_sensor_unregister(tdev->dev, tdev->tz);
	thermal_sensor_hw_exit(tdev);
}

static int thermal_sensor_get_temp(void *data, int *temp)
{
	struct thermal_sensor_device *tdev = data;
	int ret;

	ret = thermal_sensor_hw_get_temp(tdev, temp);
	dev_dbg(tdev->dev, "temp=%d\n", *temp);
	return ret;
}

static int thermal_sensor_get_trend(void *data, int i,
	enum thermal_trend *trend)
{
	struct thermal_sensor_device *tdev = data;
	struct thermal_zone_device *tz = tdev->tz;
	const struct thermal_trip *trip;
	int delta;

	/* .get_trend will be call at thermal_zone_register. */
	if (!tz || !of_thermal_is_trip_valid(tz, i))
		return -EINVAL;

	trip = of_thermal_get_trip_points(tz) + i;
	delta = tz->temperature - trip->temperature;

	if (-500 < delta && delta < 500)
		*trend = THERMAL_TREND_STABLE;
	else if (delta > 5000)
		*trend = THERMAL_TREND_RAISE_FULL;
	else if (delta > 0)
		*trend = THERMAL_TREND_RAISING;
	else
		*trend = THERMAL_TREND_DROPPING;

	dev_dbg(tdev->dev, "trip%d, delta=%d, trend=%d\n", i,
		delta, *trend);
	return 0;
}

static const struct thermal_zone_of_device_ops thermal_sensor_ops = {
	.get_temp  = thermal_sensor_get_temp,
	.get_trend = thermal_sensor_get_trend,
};

static int thermal_sensor_resume(struct device *dev)
{
	struct thermal_sensor_device *tdev = dev_get_drvdata(dev);

	dev_info(dev, "Enter %s\n", __func__);
	thermal_sensor_hw_reset(tdev);
	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops thermal_sensor_pm_ops = {
	.resume = thermal_sensor_resume,
};

static int thermal_sensor_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct thermal_sensor_device *tdev;
	int ret = 0;
	const struct of_device_id *id;
	const struct thermal_sensor_desc *desc;

	dev_info(dev, "%s\n", __func__);

	id = of_match_node(thermal_sensor_of_match, np);
	if (id)
		desc = id->data;

	if (!id || !desc)
		return -EINVAL;

	tdev = devm_kzalloc(dev, sizeof(*tdev), GFP_KERNEL);
	if (!tdev)
		return -ENOMEM;

	ret = thermal_sensor_device_add(dev, tdev, desc);
	if (ret)
		dev_err(dev, "thermal_sensor_add() returns %d\n", ret);
	platform_set_drvdata(pdev, tdev);
	return 0;
}

static int thermal_sensor_remove(struct platform_device *pdev)
{
	struct thermal_sensor_device *tdev = platform_get_drvdata(pdev);

	thermal_sensor_device_remove(tdev);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static void thermal_sensor_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct thermal_sensor_device *tdev = platform_get_drvdata(pdev);

	dev_info(dev, "%s: stop tz_dev\n", __func__);
	tdev->tz->ops->set_mode(tdev->tz, THERMAL_DEVICE_DISABLED);
};


static const struct of_device_id thermal_sensor_of_match[] = {
#ifdef CONFIG_RTK_THERMAL_RTD119X
	{
		.compatible = "realtek,rtd119x-thermal-sensor",
		.data = &rtd119x_sensor_desc,
	},
#endif
#ifdef CONFIG_RTK_THERMAL_RTD129X
	{
		.compatible = "realtek,rtd129x-thermal-sensor",
		.data = &rtd129x_sensor_desc,
	},
#endif
#ifdef CONFIG_RTK_THERMAL_RTD139X
	{
		.compatible = "realtek,rtd139x-thermal-sensor",
		.data = &rtd139x_sensor_desc,
	},
#endif
#ifdef CONFIG_RTK_THERMAL_RTD16XX
	{
		.compatible = "realtek,rtd16xx-thermal-sensor",
		.data = &rtd16xx_sensor_desc,
	},
#endif
	{}
};

static struct platform_driver thermal_sensor_drv = {
	.driver = {
		.name   = "rtk-thermal-sensor",
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(thermal_sensor_of_match),
		.pm = &thermal_sensor_pm_ops,
	},
	.probe    = thermal_sensor_probe,
	.remove   = thermal_sensor_remove,
	.shutdown = thermal_sensor_shutdown,
};

static int __init thermal_sensor_probe_init(void)
{
	return platform_driver_register(&thermal_sensor_drv);
}
late_initcall(thermal_sensor_probe_init);
