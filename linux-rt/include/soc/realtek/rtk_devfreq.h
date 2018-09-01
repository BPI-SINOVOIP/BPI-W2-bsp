/*
 * Realtek Devfreq API - exchange information between devfreq device and
 *                       devfreq event device.
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_DEVFREQ_H__
#define __SOC_REALTEK_DEVFREQ_H__

#include <linux/devfreq-event.h>

#define RTK_DEVFREQ_EVENT_DATA_MAGIC 0x1234abcd

struct rtk_devfreq_event_data {
	struct devfreq_event_data data;
	unsigned int magic;
	int scaling;
};

#define to_rtk_devfreq_event_data(_data) container_of(_data, \
	struct rtk_devfreq_event_data, data)

static inline int rtk_devfreq_get_system_scaling(
	struct devfreq_event_data *data)
{
	struct rtk_devfreq_event_data *p = to_rtk_devfreq_event_data(data);

	if (p->magic != RTK_DEVFREQ_EVENT_DATA_MAGIC)
		return -EINVAL;

	return p->scaling;
}

static inline void rtk_devfreq_event_data_init(struct rtk_devfreq_event_data *p)
{
	p->magic = RTK_DEVFREQ_EVENT_DATA_MAGIC;
	p->scaling = -EINVAL;
}

#endif
