/*
 * power_control_driver.h - for driver implementation
 *
 * Copyright (C) 2016,2018 Realtek Semiconductor Corporation
 * Copyright (C) 2016,2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _POWER_CONTROL_DRIVER_H_
#define _POWER_CONTROL_DRIVER_H_

struct device_node;
struct power_control;

struct power_control_stat {
	int count_on;
	int count_off;
	int count_x;
	int last_act;
};

/**
 * struct power_control_ops
 *
 */
struct power_control_ops {
	int (*power_on)(struct power_control *);
	int (*power_off)(struct power_control *);
	int (*is_powered_on)(struct power_control *);
};

struct power_control {
	struct list_head list;
	const char *name;
	const struct power_control_ops *ops;
	struct device_node *of_node;
#ifdef CONFIG_POWER_CONTROL_DEBUGFS
	struct dentry *debugfs;
	struct power_control_stat stat;
#endif
};

enum {
	POWER_CONTROL_ACT_NONE,
	POWER_CONTROL_ACT_CALL_ON,
	POWER_CONTROL_ACT_CALL_OFF,
};

static inline void __power_control_stat_update(struct power_control *pctrl,
	int act)
{
#ifdef CONFIG_POWER_CONTROL_DEBUGFS
	struct power_control_stat *st = &pctrl->stat;

	switch (act) {
	case POWER_CONTROL_ACT_CALL_ON:
		st->count_on++;
		st->count_x++;
		st->last_act = POWER_CONTROL_ACT_CALL_ON;
		break;
	case POWER_CONTROL_ACT_CALL_OFF:
		st->count_off++;
		st->count_x--;
		st->last_act = POWER_CONTROL_ACT_CALL_OFF;
		break;
	}
#endif /* CONFIG_POWER_CONTROL_DEBUGFS */
}

/* internal variables */
extern struct mutex power_control_list_lock;
extern int power_control_list_lock_r;
extern struct list_head power_control_list;

static inline void __list_lock(void)
{
	mutex_lock(&power_control_list_lock);
}

static inline void __list_unlock(void)
{
	mutex_unlock(&power_control_list_lock);
}

#define to_power_control(_p) container_of((_p), struct power_control, list)

/* unlocked version API */
struct power_control *__power_control_get(const char *name);
struct power_control *__of_power_control_get_by_index(struct device_node *np,
	int index);
struct power_control *__of_power_control_get(struct device_node *np,
	const char *id);

struct of_phandle_args;

struct power_control_onecell_data {
	struct power_control **controls;
	unsigned int num_controls;
};

typedef struct power_control *(*power_control_xlate_t)(
	struct of_phandle_args *args, void *data);
int of_power_control_add_provider(struct device_node *np,
	power_control_xlate_t xlate, void *data);
void of_power_control_del_provider(struct device_node *np);
struct power_control *of_power_control_xlate_simple(
	struct of_phandle_args *args, void *data);
struct power_control *of_power_control_xlate_onecell(
	struct of_phandle_args *args, void *data);
struct power_control *of_power_control_get_from_provider(
	struct of_phandle_args *args);

#ifdef CONFIG_POWER_CONTROL_DEBUGFS
int power_control_add_debugfs(struct power_control *pctrl);
#else
static inline int power_control_add_debugfs(struct power_control *pctrl)
{
	return -EINVAL;
}
#endif /* CONFIG_POWER_CONTROL_DEBUGFS */

#endif /* _POWER_CONTROL_DRIVER_H_ */
