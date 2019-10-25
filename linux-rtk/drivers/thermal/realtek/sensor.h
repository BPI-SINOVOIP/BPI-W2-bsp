/*
 * Copyright (C) 2018 Realtek Semiconductor Corporation
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
 *
 */

#ifndef __REALTEK_THERMAL_H
#define __REALTEK_THERMAL_H

#include <linux/device.h>
#include <linux/list.h>
#include <linux/thermal.h>
#include <linux/notifier.h>
#include <linux/ktime.h>

struct thermal_sensor_device;
struct thermal_cooling_device;

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
	ktime_t ts_reset;
};

struct thermal_sensor_device {
	struct device *dev;
	const struct thermal_zone_of_device_ops *ops;
	struct thermal_zone_device *tz;
	struct list_head list;
	int passive_delay;
	int polling_delay;

	const struct thermal_sensor_desc *desc;
	struct thermal_sensor *sensors;
	struct thermal_zone_device_ops *old_ops;

#ifdef CONFIG_RTK_THERMAL_EOH
	unsigned int eoh_state;
#define THERMAL_SENSOR_EOH_NONE    0
#define THERMAL_SENSOR_EOH_START   1
#define THERMAL_SENSOR_EOH_POLL    2
	unsigned int eoh_freq;
	unsigned int eoh_restore_ms;
	ktime_t eoh_time;
	struct notifier_block eoh_cpufreq_nb;
#endif /* CONFIG_RTK_THERMAL_EOH */
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
		if (!ret)
			continue;
		dev_warn(tdev->dev, "failed to init sensor%d: %d\n", i, ret);
	}
}

static inline void thermal_sensor_hw_exit(struct thermal_sensor_device *tdev)
{
	const struct thermal_sensor_desc *desc = tdev->desc;
	int i;

	if (!desc->hw_ops->exit)
		return;

	for (i = 0; i < desc->num_sensors; i++)
		desc->hw_ops->exit(tdev, i);
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
extern const struct thermal_sensor_desc rtd13xx_sensor_desc;

/* helper function */
static inline int __signext(int signb, unsigned int v)
{
	int x = 31 - signb;

	return ((int)(v << x)) >> x;
}

static inline bool cdev_is_cpufreq(struct thermal_cooling_device *cdev)
{
	return !strncmp("thermal-cpufreq-0", cdev->type, THERMAL_NAME_LENGTH);
}


#ifdef CONFIG_RTK_THERMAL_EOH
void thermal_sensor_eoh_handle_restore(struct thermal_sensor_device *tdev);
void thermal_sensor_eoh_handle_overheat(struct thermal_sensor_device *tdev,
					int i, enum thermal_trend trend);
int thermal_sensor_add_eoh(struct thermal_sensor_device *tdev);
void thermal_sensor_remove_eoh(struct thermal_sensor_device *tdev);
#else

static inline
void thermal_sensor_eoh_handle_restore(struct thermal_sensor_device *tdev)
{
}

static inline
void thermal_sensor_eoh_handle_overheat(struct thermal_sensor_device *tdev,
					int i, enum thermal_trend trend)
{
}

static inline
int thermal_sensor_add_eoh(struct thermal_sensor_device *tdev)
{
	return 0;
}

static inline
void thermal_sensor_remove_eoh(struct thermal_sensor_device *tdev)
{
}

#endif /* CONFIG_RTK_THERMAL_EOH */

#endif
