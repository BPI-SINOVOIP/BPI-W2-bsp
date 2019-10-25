/*
 * sensor-eoh.c - External Overheat Handler
 *
 * Copyright (C) 2019 Realtek Semiconductor Corporation
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

#include <linux/slab.h>
#include <linux/thermal.h>
#include <linux/cpufreq.h>
#include <linux/of.h>
#include "../thermal_core.h"
#include "sensor.h"

void thermal_sensor_eoh_handle_restore(struct thermal_sensor_device *tdev)
{
	unsigned int cpu = cpumask_any(cpu_online_mask);
	ktime_t delta;

	if (!tdev->eoh_freq)
		return;

	delta = ktime_sub(ktime_get(), tdev->eoh_time);
	if (ktime_to_ms(delta) < (s64)tdev->eoh_restore_ms)
		return;

	tdev->eoh_freq = 0;
	tdev->eoh_state = THERMAL_SENSOR_EOH_NONE;
	dev_dbg(tdev->dev, "eoh: restore policy\n");
	cpufreq_update_policy(cpu);
}

void thermal_sensor_eoh_handle_overheat(struct thermal_sensor_device *tdev,
					int i, enum thermal_trend trend)
{
	struct thermal_zone_device *tz = tdev->tz;
	struct thermal_instance *pos;

	if (trend != THERMAL_TREND_RAISE_FULL &&
	    trend != THERMAL_TREND_RAISING)
		return;

	list_for_each_entry(pos, &tz->thermal_instances, tz_node) {
		if (pos->trip != i)
			continue;
		if (!cdev_is_cpufreq(pos->cdev))
			continue;

		dev_dbg(tdev->dev, "eoh: overheat\n");
		tdev->eoh_state = THERMAL_SENSOR_EOH_START;
		tdev->eoh_time = ktime_get();
		break;
	}
}


static int thermal_sensor_eoh_cpufreq_cb(struct notifier_block *nb,
					 unsigned long event, void *data)
{
	struct cpufreq_policy *policy = data;
	struct thermal_sensor_device *tdev = container_of(nb,
		struct thermal_sensor_device, eoh_cpufreq_nb);

	if (event != CPUFREQ_ADJUST)
		return NOTIFY_DONE;

	if (tdev->eoh_state == THERMAL_SENSOR_EOH_START) {
		if (tdev->eoh_freq != 0 && tdev->eoh_freq < policy->max)
			return NOTIFY_DONE;

		tdev->eoh_freq = policy->max;
		tdev->eoh_state = THERMAL_SENSOR_EOH_POLL;
		dev_dbg(tdev->dev, "eoh: save freq=%u\n", tdev->eoh_freq);
		return NOTIFY_OK;
	} else if (tdev->eoh_state == THERMAL_SENSOR_EOH_POLL) {
		if (!tdev->eoh_freq)
			return NOTIFY_DONE;
		cpufreq_verify_within_limits(policy, 0, tdev->eoh_freq);
		dev_dbg(tdev->dev, "eoh: apply freq=%u\n", policy->max);
		return NOTIFY_OK;
	}
	return NOTIFY_DONE;
}

int thermal_sensor_add_eoh(struct thermal_sensor_device *tdev)
{
	struct device *dev = tdev->dev;
	struct device_node *np = dev->of_node;

	if (of_property_read_u32(np, "eoh-restore-ms", &tdev->eoh_restore_ms))
		tdev->eoh_restore_ms = 2000;

	tdev->eoh_cpufreq_nb.notifier_call = thermal_sensor_eoh_cpufreq_cb;
	tdev->eoh_cpufreq_nb.priority = -1;
	cpufreq_register_notifier(&tdev->eoh_cpufreq_nb,
		CPUFREQ_POLICY_NOTIFIER);
	return 0;
}

void thermal_sensor_remove_eoh(struct thermal_sensor_device *tdev)
{
	cpufreq_unregister_notifier(&tdev->eoh_cpufreq_nb,
		CPUFREQ_POLICY_NOTIFIER);
}

