/*
 * rpm_sysgs.c - Runtime PM SysFs for Debug
 *
 * Copyright (C) 2018, Realtek Semiconductor Corporation
 * Copyright (C) 2018, Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/device.h>
#include <linux/list.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>

struct rpm_debug_data {
	struct list_head list;
	struct device *dev;
	int suspend_cnt;
};

static LIST_HEAD(pm_list);

static struct rpm_debug_data *dev_to_data(struct device *dev)
{
	struct rpm_debug_data *pos;

	list_for_each_entry(pos, &pm_list, list)
		if (pos->dev == dev)
			return pos;
	return NULL;
}

static const char ctrl_suspend[] = "suspend";
static const char ctrl_resume[] = "resume";

static ssize_t dbgctrl_show(struct device *dev, struct device_attribute *attr,
	char *buf)
{
	struct rpm_debug_data *data = dev_to_data(dev);

	return sprintf(buf, "suspend_cnt: %d\n", data->suspend_cnt);
}


static ssize_t dbgctrl_store(struct device *dev, struct device_attribute *attr,
	const char *buf, size_t n)
{
	struct rpm_debug_data *data = dev_to_data(dev);

	if (!strncmp(buf, ctrl_suspend, sizeof(ctrl_suspend) - 1)) {
		pm_runtime_put_sync_suspend(dev);
		data->suspend_cnt++;
	} else if (!strncmp(buf, ctrl_resume, sizeof(ctrl_resume) - 1)) {
		pm_runtime_get_sync(dev);
		data->suspend_cnt--;
	} else
		n = -EINVAL;
	return n;
}

static DEVICE_ATTR(dbgctrl, 0644, dbgctrl_show, dbgctrl_store);

static struct attribute *rpm_debug_attrs[] = {
	&dev_attr_dbgctrl.attr,
	NULL
};

static struct attribute_group rpm_debug_attr_group = {
	.name   = power_group_name,
	.attrs  = rpm_debug_attrs,
};

static int create_rpm_debug_data(struct device *dev)
{
	struct rpm_debug_data *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->dev = dev;
	list_add(&data->list, &pm_list);
	return 0;
}

static void free_rpm_debug_data(struct device *dev)
{
	struct rpm_debug_data *data = dev_to_data(dev);

	list_del(&data->list);
	kfree(data);
}

int rpm_debug_sysfs_add(struct device *dev)
{
	int ret;

	ret = create_rpm_debug_data(dev);
	if (ret)
		return ret;

	if (pm_runtime_callbacks_present(dev)) {
		ret = sysfs_merge_group(&dev->kobj, &rpm_debug_attr_group);
		if (ret)
			goto error;
	}
	return 0;
error:
	free_rpm_debug_data(dev);
	return ret;
}

void rpm_debug_sysfs_remove(struct device *dev)
{
	sysfs_unmerge_group(&dev->kobj, &rpm_debug_attr_group);
	free_rpm_debug_data(dev);
}

