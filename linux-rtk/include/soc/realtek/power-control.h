/*
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_POWER_CONTROL_H_INCLUDED
#define __SOC_REALTEK_POWER_CONTROL_H_INCLUDED

struct device_node;
struct power_control;

#include <linux/types.h>

/* power-control notifier actions */
#define POWER_CONTROL_ACTION_PRE_POWER_ON         (0x01)
#define POWER_CONTROL_ACTION_POST_POWER_ON        (0x02)
#define POWER_CONTROL_ACTION_POWER_ON_ABORT       (0x03)
#define POWER_CONTROL_ACTION_POWER_ON_IGNORE      (0x04)
#define POWER_CONTROL_ACTION_PRE_POWER_OFF        (0x11)
#define POWER_CONTROL_ACTION_POST_POWER_OFF       (0x12)

#ifdef CONFIG_POWER_CONTROL
int power_control_init(struct power_control *pwrctrl);
int power_control_power_on(struct power_control *pwrctrl);
int power_control_power_off(struct power_control *pwrctrl);
int power_control_is_powered_on(struct power_control *pwrctrl);

struct power_control *power_control_get(const char *name);
struct power_control *of_power_control_get_by_index(struct device_node *node,
						    int index);
struct power_control *of_power_control_get(struct device_node *node,
					   const char *id);
void power_control_put(struct power_control *pwrctrl);

int power_control_register(struct power_control *pwrctrl);
void power_control_unregister(struct power_control *pwrctrl);

int power_control_register_notifier(struct power_control *pwrctrl,
				    struct notifier_block *nb);
void power_control_unregister_notifier(struct power_control *pwrctrl,
				       struct notifier_block *nb);

#else

static inline int power_control_power_on(struct power_control *pwrctrl)
{
	return -EINVAL;
}

static inline int power_control_power_off(struct power_control *pwrctrl)
{
	return -EINVAL;
}

static inline int power_control_is_powered_on(struct power_control *pwrctrl)
{
	return -EINVAL;
}

static inline struct power_control *power_control_get(const char *name)
{
	return ERR_PTR(-EINVAL);
}

static inline struct power_control *of_power_control_get_by_index(struct device_node *node,
								  int index)
{
	return ERR_PTR(-EINVAL);
}

static inline struct power_control *of_power_control_get(struct device_node *node,
							 const char *id)
{
	return ERR_PTR(-EINVAL);
}

static inline void power_control_put(struct power_control *pwrctrl)
{
}

static inline int power_control_register(struct power_control *pwrctrl)
{
	return -EINVAL;
}

static inline void power_control_unregister(struct power_control *pwrctrl)
{
}

static inline int power_control_register_notifier(struct power_control *pwrctrl,
						  struct notifier_block *nb)
{
	return -EINVAL;
}

static inline void power_control_unregister_notifier(struct power_control *pwrctrl,
						     struct notifier_block *nb)
{
}

#endif

static inline int power_control_enable_hw_pm(struct power_control *pwrctrl)
{
	return power_control_power_off(pwrctrl);
}

static inline int power_control_disable_hw_pm(struct power_control *pwrctrl)
{
	return power_control_power_on(pwrctrl);
}

#endif
