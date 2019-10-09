/*
 * rtd16xx_suspend_fs.c - power management driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/reboot.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/cpu_pm.h>
#include <linux/vmalloc.h>
#include <linux/tick.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/irqchip/arm-gic.h>
#include <linux/psci.h>
#include <asm/system_misc.h>
#include <asm/cacheflush.h>
#include <asm/suspend.h>
#include <soc/realtek/memory.h>
#include <soc/realtek/rtk_cpu.h>
#include <uapi/linux/psci.h>

#include "rtd16xx_suspend.h"

unsigned int suspend_context;
extern struct suspend_param *pcpu_data;
extern struct kobj_attribute rtk_suspend_gpio_wakeup_en_attr;
extern struct kobj_attribute rtk_suspend_gpio_wakeup_act_attr;
extern struct kobj_attribute rtk_suspend_gpio_out_en_attr;
extern struct kobj_attribute rtk_suspend_gpio_out_act_attr;

const char *const rtk_suspend_wakeup_states[eWAKEUP_ON_MAX] = {
	[eWAKEUP_ON_LAN] = "lan",
	[eWAKEUP_ON_IR] = "ir",
	[eWAKEUP_ON_GPIO] = "gpio",
	[eWAKEUP_ON_ALARM] = "alarm",
	[eWAKEUP_ON_TIMER] = "timer",
	[eWAKEUP_ON_CEC] = "cec",
};

const char *const rtk_suspend_resume_states[RESUME_MAX_STATE] = {
	[RESUME_NONE] = "none",
	[RESUME_UNKNOW] = "unknow",
	[RESUME_IR] = "ir",
	[RESUME_GPIO] = "gpio",
	[RESUME_LAN] = "lan",
	[RESUME_ALARM] = "alarm",
	[RESUME_TIMER] = "timer",
	[RESUME_CEC] = "cec",
};

const char *const rtk_suspend_states[MAX_SUSPEND_MODE] = {
	[SUSPEND_TO_RAM] = "ram",
	[SUSPEND_TO_COOLBOOT] = "coolboot",
	[SUSPEND_TO_WFI] = "wfi",
};

#define RTK_SUSPEND_ATTR(_name) \
{ \
	.attr = {.name = #_name, .mode = 0644}, \
	.show =  rtk_suspend_##_name##_show, \
	.store = rtk_suspend_##_name##_store, \
}

static enum _suspend_wakeup rtk_suspend_decode_wakeup(const char *buf,
	size_t n)
{
	const char *const *s;
	char *p;
	int len;
	int i;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	for (i = 0 ; i < eWAKEUP_ON_MAX ; i++) {
		s = &rtk_suspend_wakeup_states[i];
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
			return i;
	}

	return eWAKEUP_ON_MAX;
}

static ssize_t rtk_suspend_wakeup_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val = pcpu_data->wakeup_source;

	for (i = 0 ; i < eWAKEUP_ON_MAX ; i++) {

		if (val & (0x1U << i))
			n += sprintf(buf + n, " * ");
		else
			n += sprintf(buf + n, "   ");
		n += sprintf(buf + n, "%s\n", rtk_suspend_wakeup_states[i]);
	}
	n += sprintf(buf + n, "\n");
	return n;
}

static ssize_t rtk_suspend_wakeup_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	enum _suspend_wakeup wakeup = rtk_suspend_decode_wakeup(buf, count);

	if (wakeup < eWAKEUP_ON_MAX) {
		pcpu_data->wakeup_source ^= (0x1U << wakeup);
		return count;
	}
	return -ENOMEM;
}

static ssize_t rtk_suspend_timer_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, " %d sec (reciprocal timer)\n",
		pcpu_data->timerout_val);
}

static ssize_t rtk_suspend_timer_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;

	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val > (AUDIO_RECIPROCAL_TIMER_GET(-1UL)))
		return -ENOMEM;

	pcpu_data->timerout_val = val;
	return count;
}

static ssize_t rtk_suspend_context_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", suspend_context);
}

static ssize_t rtk_suspend_context_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	suspend_context = val;
	return count;
}

static struct kobj_attribute rtk_suspend_wakeup_attr =
	RTK_SUSPEND_ATTR(wakeup);
static struct kobj_attribute rtk_suspend_timer_attr =
	RTK_SUSPEND_ATTR(timer);
static struct kobj_attribute rtk_suspend_context_attr =
	RTK_SUSPEND_ATTR(context);

static struct attribute *rtk_suspend_attrs[] = {
	&rtk_suspend_wakeup_attr.attr,
	&rtk_suspend_timer_attr.attr,
	&rtk_suspend_context_attr.attr,
	&rtk_suspend_gpio_wakeup_en_attr.attr,
	&rtk_suspend_gpio_wakeup_act_attr.attr,
	&rtk_suspend_gpio_out_en_attr.attr,
	&rtk_suspend_gpio_out_act_attr.attr,
	NULL,
};

static struct attribute_group rtk_suspend_attr_group = {
	.attrs = rtk_suspend_attrs,
};

static struct kobject *rtk_suspend_kobj;

static int __init suspend_sysfs_init(void)
{
	int ret;

	pcpu_data->wakeup_source = 0;
	pcpu_data->timerout_val = 0;

	rtk_suspend_kobj = kobject_create_and_add("suspend", kernel_kobj);
	if (!rtk_suspend_kobj)
		return -ENOMEM;
	ret = sysfs_create_group(rtk_suspend_kobj, &rtk_suspend_attr_group);
	if (ret)
		kobject_put(rtk_suspend_kobj);
	return ret;
}

module_init(suspend_sysfs_init);
