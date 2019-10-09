/*
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __REALTEK_THERMAL_H
#define __REALTEK_THERMAL_H

#include <linux/device.h>
#include <linux/list.h>
#include <linux/thermal.h>

struct thermal_sensor_device;

struct thermal_sensor_hw_ops {
	int (*init)(struct thermal_sensor_device *, int);
	void (*exit)(struct thermal_sensor_device *, int);
	void (*reset)(struct thermal_sensor_device *, int);
	int (*get_temp)(struct thermal_sensor_device *, int, int *);
};

struct thermal_sensor_desc {
	int num_sensors;
	const struct thermal_sensor_hw_ops *hw_ops;
};

struct thermal_sensor {
	void __iomem *reg;
	bool available;
	int calibration_data;
	int weight;
};

struct thermal_sensor_device {
	struct device *dev;
	const struct thermal_zone_of_device_ops *ops;
	struct thermal_zone_device *tz;
	struct list_head list;
	int passive_delay;
	int polling_delay;
	int (*set_mode)(struct thermal_zone_device *tz,
		enum thermal_device_mode mode);

	const struct thermal_sensor_desc *desc;
	struct thermal_sensor *sensors;
};

static inline void thermal_sensor_hw_init(struct thermal_sensor_device *tdev)
{
	const struct thermal_sensor_desc *desc = tdev->desc;
	int i;
	int ret;

	if (!desc->hw_ops->init)
		return;

	for (i = 0; i < desc->num_sensors; i++) {
		ret = desc->hw_ops->init(tdev, i);
		if (ret)
			dev_warn(tdev->dev, "init sensor%d returns %d\n", i, ret);
	}
}

static inline void thermal_sensor_hw_exit(struct thermal_sensor_device *tdev)
{
	const struct thermal_sensor_desc *desc = tdev->desc;
	int i;

	if (!desc->hw_ops->exit)
		return;

	for (i = 0; i < desc->num_sensors; i++) {
		desc->hw_ops->exit(tdev, i);
	}
}

static inline void thermal_sensor_hw_reset(struct thermal_sensor_device *tdev)
{
	const struct thermal_sensor_desc *desc = tdev->desc;
	int i;

	if (!desc->hw_ops->reset)
		return;

	for (i = 0; i < desc->num_sensors; i++)
		desc->hw_ops->reset(tdev, i);
}

static inline int thermal_sensor_hw_get_temp(struct thermal_sensor_device *tdev,
	int *temp)
{
	const struct thermal_sensor_desc *desc = tdev->desc;
	int ret;
	int i;
	int t, max_t = INT_MIN;

	if (!desc->hw_ops->get_temp)
		return -EINVAL;

	for (i = 0; i < desc->num_sensors; i++) {
		ret = desc->hw_ops->get_temp(tdev, i, &t);
		if (ret == 0 && max_t < t)
			max_t = t;
	}
	*temp = max_t;
	return 0;
}

extern const struct thermal_sensor_desc rtd119x_sensor_desc;
extern const struct thermal_sensor_desc rtd129x_sensor_desc;
extern const struct thermal_sensor_desc rtd139x_sensor_desc;
extern const struct thermal_sensor_desc rtd16xx_sensor_desc;

#endif
