/*
 * Power Control DebugFS
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/debugfs.h>
#include <soc/realtek/power-control.h>
#include "pwrctrl_driver.h"

static struct dentry *power_control_root;

static const char * const last_str[] = {
	[POWER_CONTROL_ACT_NONE] = "NONE",
	[POWER_CONTROL_ACT_CALL_ON] = "POWER_ON",
	[POWER_CONTROL_ACT_CALL_OFF] = "POWER_OFF",
};

static int power_control_summary_show(struct seq_file *s, void *data)
{
	struct list_head *it = NULL;
	char pow_str[20];

	seq_printf(s, "%-28s %-5s %-9s %3s = %8s - %8s %s\n",
			"POWER_CONTROL_NAME", "TYPE", "STATE",
			"X", "CNT_ON", "CNT_OFF", "LAST_CALL");

	__list_lock();

	list_for_each(it, &power_control_list) {
		struct power_control *pctrl = to_power_control(it);
		struct power_control_stat *st = &pctrl->stat;
		int is_powered = power_control_is_powered_on(pctrl);

		if (is_powered < 0)
			snprintf(pow_str, sizeof(pow_str), "ERRNO(%d)",
				is_powered);
		else
			strncpy(pow_str, is_powered ? "ON" : "OFF",
				sizeof(pow_str));


		seq_printf(s, "%-28s %-5s %-9s %3d   %8d   %8d %s\n",
			pctrl->name,
			"POWER",
			pow_str,
			st->count_x,
			st->count_on,
			st->count_off,
			last_str[st->last_act]
		);
	}

	__list_unlock();

	return 0;

}

static int power_control_summary_open(struct inode *inode, struct file *file)
{
	return single_open(file, power_control_summary_show, NULL);
}

static const struct file_operations power_control_summary_ops = {
	.owner   = THIS_MODULE,
	.open    = power_control_summary_open,
	.read    = seq_read,
	.release = single_release,
};

static int __init power_control_debugfs_arch_init(void)
{
	power_control_root = debugfs_create_dir("power_control", NULL);
	return 0;
}
arch_initcall(power_control_debugfs_arch_init);

static int __init power_control_debugfs_init(void)
{
	debugfs_create_file("power_control_summary", 0444,
		power_control_root, NULL, &power_control_summary_ops);
	return 0;
}
late_initcall(power_control_debugfs_init);

static int power_conrol_debugfs_set(void *data, u64 val)
{
	struct power_control *pctrl = data;
	int is_powered = power_control_is_powered_on(pctrl);
	int ret = 0;

	if (val == 1 && is_powered == 0)
		power_control_power_on(pctrl);
	else if (val == 0 && is_powered == 1)
		power_control_power_off(pctrl);
	else
		ret = -EINVAL;
	return ret;
}
static int power_conrol_debugfs_get(void *data, u64 *val)
{
	struct power_control *pctrl = data;
	int is_powered = power_control_is_powered_on(pctrl);

	*val = is_powered;
	return is_powered < 0 ? -EINVAL : 0;
}
DEFINE_SIMPLE_ATTRIBUTE(power_conrol_power_fops, power_conrol_debugfs_get,
	power_conrol_debugfs_set, "%lld\n");

int power_control_add_debugfs(struct power_control *pctrl)
{
	struct dentry *d;

	if (pctrl->debugfs)
		return -EINVAL;

	pctrl->debugfs = debugfs_create_dir(pctrl->name, power_control_root);
	if (!pctrl->debugfs)
		return -ENOMEM;

	d = debugfs_create_file("power", 0644, pctrl->debugfs, pctrl,
		&power_conrol_power_fops);
	if (!d) {
		pr_err("%s: failed to add debugfs\n", pctrl->name);
		return -ENOMEM;
	}
	return 0;
}

