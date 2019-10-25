/*
 * power_control_driver.h - for driver implementation
 *
 * Copyright (C) 2016,2018,2019 Realtek Semiconductor Corporation
 * Copyright (C) 2016,2018,2019 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __POWER_CONTROL_DRIVER_H
#define __POWER_CONTROL_DRIVER_H

struct device_node;
struct power_control;
struct dentry;
#include <linux/atomic.h>
#include <linux/list.h>
#include <linux/notifier.h>

/**
 * struct power_control_ops
 */
struct power_control_ops {
	int (*power_on)(struct power_control *);
	int (*power_off)(struct power_control *);
	int (*is_powered_on)(struct power_control *);
	int (*init)(struct power_control *);
	int (*power_off_unused)(struct power_control *);
};

struct power_control {
	struct list_head list;
	const char *name;
	const struct power_control_ops *ops;
	struct device_node *of_node;

	atomic_t usage_cnt;
	unsigned long flags;
	struct raw_notifier_head notifier_head;
#ifdef CONFIG_POWER_CONTROL_DEBUGFS
	struct dentry *debugfs;
#endif
	atomic_t power_cnt;
};

#define POWER_CONTROL_FLAG_ASYNC_POWER_OFF        (0x1)
#define POWER_CONTROL_FLAG_SHARED_POWER           (0x2)
#define POWER_CONTROL_FLAG_IGNORE_UNUSED          (0x4)

struct of_phandle_args;

struct power_control_onecell_data {
	struct power_control **controls;
	unsigned int num_controls;
};

typedef struct power_control *(*power_control_xlate_t)(struct of_phandle_args *args, void *data);
int of_power_control_add_provider(struct device_node *np,
				  power_control_xlate_t xlate,
				  void *data);
void of_power_control_del_provider(struct device_node *np);
struct power_control *of_power_control_xlate_simple(struct of_phandle_args *args,
						    void *data);
struct power_control *of_power_control_xlate_onecell(struct of_phandle_args *args,
						     void *data);
struct power_control *of_power_control_get_from_provider(struct of_phandle_args *args);

int power_control_get_internal(struct power_control *pwrctrl);
void power_control_put_internal(struct power_control *pwrctrl);

int __power_control_notify_power_off_start(struct power_control *pwrctrl);
int __power_control_notify_power_off_done(struct power_control *pwrctrl);


#endif
