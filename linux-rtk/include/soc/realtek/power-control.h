/*
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef SOC_REALTEK_POWER_CONTROL_H
#define SOC_REALTEK_POWER_CONTROL_H

struct device_node;
struct power_control;

#include <linux/types.h>

#ifdef CONFIG_POWER_CONTROL
const char *power_control_get_name(struct power_control *pctrl);
int power_control_power_on(struct power_control *pctrl);
int power_control_power_off(struct power_control *pctrl);
int power_control_is_powered_on(struct power_control *pctrl);
struct power_control *power_control_get(const char *name);
struct power_control *of_power_control_get_by_index(struct device_node *node,
	int index);
struct power_control *of_power_control_get(struct device_node *node,
	const char *id);
bool power_control_is_match(const struct power_control *a,
	const struct power_control *b);
int power_control_register(struct power_control *pctrl);
void power_control_unregister(struct power_control *pctrl);
#else

static inline
const char *power_control_get_name(struct power_control *pctrl)
{
	return NULL;
}

static inline
int power_control_power_on(struct power_control *pctrl)
{
	return -EINVAL;
}

static inline int power_control_power_off(struct power_control *pctrl)
{
	return -EINVAL;
}

static inline int power_control_is_powered_on(struct power_control *pctrl)
{
	return -EINVAL;
}

static inline struct power_control *power_control_get(const char *name)
{
	return ERR_PTR(-EINVAL);
}

static inline struct power_control *of_power_control_get_by_index(
	struct device_node *node, int index)
{
	return ERR_PTR(-EINVAL);
}

static inline struct power_control *of_power_control_get(
	struct device_node *node, const char *id)
{
	return ERR_PTR(-EINVAL);
}

static inline bool power_control_is_match(const struct power_control *a,
	const struct power_control *b)
{
	return true;
}

static inline int power_control_register(struct power_control *pctrl)
{
	return -EINVAL;
}

static inline void power_control_unregister(struct power_control *pctrl)
{
}

#endif

static inline int power_control_enable_hw_pm(struct power_control *pctrl)
{
	return power_control_power_off(pctrl);
}

static inline int power_control_disable_hw_pm(struct power_control *pctrl)
{
	return power_control_power_on(pctrl);
}

#endif
