/*
 * rtd16xx_suspend.c - power management driver
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
#include <linux/gpio_keys.h>
#include <linux/platform_device.h>
#include <linux/input-event-codes.h>
#include <asm/system_misc.h>
#include <asm/cacheflush.h>
#include <asm/suspend.h>
#include <soc/realtek/memory.h>

#include "gpio-rtd16xx-suspend.h"

#define DEV_NAME "RTD16xx_gpio-suspend"


char wu_en[SUSPEND_ISO_GPIO_SIZE];
char wu_act[SUSPEND_ISO_GPIO_SIZE];

char out_en[SUSPEND_ISO_GPIO_SIZE];
char out_act[SUSPEND_ISO_GPIO_SIZE];

EXPORT_SYMBOL(wu_en);
EXPORT_SYMBOL(wu_act);

void rtk_suspend_gpio_output_change_suspend(void)
{
	int i = 0;
	int tmp;

	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (!out_en[i])
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			out_act[i] ? "HIGH" : "LOW");
		tmp = out_act[i] ? 1 : 0;
		gpio_direction_output(i + SUSPEND_ISO_GPIO_BASE, tmp);
	}
}

void rtk_suspend_gpio_output_change_resume(void)
{
	int i = 0;
	int tmp;

	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (!out_en[i])
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			out_act[i] ? "LOW" : "HIGH");
		tmp = out_act[i] ? 0 : 1;
		gpio_direction_output(i + SUSPEND_ISO_GPIO_BASE, tmp);
	}
}



static void rtk_gpio_init_wu(struct device_node *nd)
{
	const u32 *prop_en;
	const u32 *prop_act;
	int wu_gpio_en = 0;
	int wu_gpio_act = 0;
	int wu_gpio_list = 0;
	int en;
	int act;
	int wu_gpio;
	int gpio_iso_num;
	int tmp;
	int i = 0;

	wu_gpio_list = of_gpio_named_count(nd, "wakeup-gpio-list");
	prop_en = of_get_property(nd, "wakeup-gpio-enable", &wu_gpio_en);
	prop_act = of_get_property(nd, "wakeup-gpio-activity", &wu_gpio_act);
	wu_gpio_en  /= sizeof(u32);
	wu_gpio_act /= sizeof(u32);

	pr_info("[%s] wakeup-gpio Cnt: en(%d) act(%d) list(%d)\n",
		DEV_NAME, wu_gpio_en, wu_gpio_act, wu_gpio_list);

	if (wu_gpio_en != 0 && (wu_gpio_en == wu_gpio_act)
		&& (wu_gpio_act == wu_gpio_list)) {

		for (i = 0 ; i < wu_gpio_list ; i++) {
			en  = of_read_number(prop_en, 1 + i);
			act = of_read_number(prop_act, 1 + i);
			wu_gpio = of_get_named_gpio(nd, "wakeup-gpio-list", i);
			gpio_iso_num = wu_gpio - SUSPEND_ISO_GPIO_BASE;

			if (!en) {
				pr_err("[%s] wakeup-gpio[%d] States is disable! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, wu_gpio);
				continue;
			}

			tmp = gpio_iso_num < 0 || gpio_iso_num;
			if (tmp >= SUSPEND_ISO_GPIO_SIZE) {
				pr_err("[%s] wakeup-gpio[%d] Out of iso range! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, wu_gpio);
				continue;
			}

			if (gpio_request(wu_gpio, nd->name)) {
				pr_err("[%s] wakeup-gpio[%d] Request failed! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, wu_gpio);
			} else {
				//gpio_free(wu_gpio);
			}

			gpio_direction_input(wu_gpio);

			pr_info("[%s] wakeup-gpio[%d] Successful registration! (en:%d act:%d gpio:%d)\n",
				DEV_NAME, i, en, act, wu_gpio);

			wu_en[gpio_iso_num] = en ? 1 : 0;
			wu_act[gpio_iso_num] = act ? 1 : 0;
		}
	}
}

static void rtk_gpio_init_out(struct device_node *nd)
{
	const u32 *prop_en;
	const u32 *prop_act;
	int out_gpio_en = 0;
	int out_gpio_act = 0;
	int out_gpio_list = 0;
	int en;
	int act;
	int gpio_iso_num;
	int output_change_gpio;
	int i = 0;

	out_gpio_list = of_gpio_named_count(nd, "gpio-output-change-list");
	prop_en = of_get_property(nd, "gpio-output-change-enable",
		&out_gpio_en);
	prop_act = of_get_property(nd, "gpio-output-change-activity",
		&out_gpio_act);
	out_gpio_en /= sizeof(u32);
	out_gpio_act /= sizeof(u32);

	pr_info("[%s] gpio-output-change Cnt: en(%d) act(%d) list(%d)\n",
			DEV_NAME, out_gpio_en, out_gpio_act, out_gpio_list);

	if (out_gpio_en != 0 && (out_gpio_en == out_gpio_act)
		&& (out_gpio_act == out_gpio_list)) {

		for (i = 0 ; i < out_gpio_list ; i++) {
			en  = of_read_number(prop_en, 1 + i);
			act = of_read_number(prop_act, 1 + i);
			output_change_gpio = of_get_named_gpio(nd,
				"gpio-output-change-list", i);
			gpio_iso_num = output_change_gpio -
				SUSPEND_ISO_GPIO_BASE;

			if (!en) {
				pr_err("[%s] gpio-output-change[%d] States is disable! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, output_change_gpio);
				continue;
			}

			if (gpio_iso_num < 0 ||
				gpio_iso_num >= SUSPEND_ISO_GPIO_SIZE) {
				pr_err("[%s] gpio-output-change[%d] Out of iso range! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, output_change_gpio);
				continue;
			}

			if (gpio_request(output_change_gpio, nd->name)) {
				pr_err("[%s] gpio-output-change[%d] Request failed! (en:%d act:%d gpio:%d)\n",
					DEV_NAME, i, en, act, output_change_gpio);
			} else {
				gpio_free(output_change_gpio);
			}

			pr_info("[%s] gpio-output-change[%d] Successful registration! (en:%d act:%d gpio:%d)\n",
				DEV_NAME, i, en, act, output_change_gpio);

			out_en[gpio_iso_num] = en ? 1:0;
			out_act[gpio_iso_num] = act ? 1:0;
		}
	}
}

#ifdef CONFIG_KEYBOARD_GPIO

static int rtk_gpio_keys_init_button(struct device_node *pp,
				     struct gpio_keys_button *button)
{
	enum of_gpio_flags flags;
	u32 idx;

	button->gpio = of_get_gpio_flags(pp, 0, &flags);
	if (button->gpio < 0) {
		pr_err("failed to get gpio flags: %d\n", button->gpio);
		return button->gpio;
	} else {
		button->active_low = (flags & OF_GPIO_ACTIVE_LOW) ? 1 : 0;
	}

	pr_info("%s: get gpio%d, flags=%x\n", __func__, button->gpio, flags);
	idx = button->gpio - SUSPEND_ISO_GPIO_BASE;

	if (of_property_read_u32(pp, "linux,code", &button->code))
		return -EINVAL;

	button->desc = of_get_property(pp, "label", NULL);

	if (of_property_read_u32(pp, "linux,input-type", &button->type))
		button->type = EV_KEY;

	if (of_property_read_bool(pp, "wakeup-source")) {
		pr_err("%s: gpio%d is wakeup-source\n", __func__, button->gpio);

		wu_en[idx] = 1;
		wu_act[idx] = (flags & OF_GPIO_ACTIVE_LOW) ? 0 : 1;
	}

	button->can_disable = !!of_get_property(pp, "linux,can-disable", NULL);

	if (of_property_read_u32(pp, "debounce-interval",
				 &button->debounce_interval))
		button->debounce_interval = 5;

	return 0;
}

static struct platform_device *gpio_keys_pdev;

static void rtk_gpio_keys_init(struct device_node *np)
{
	struct platform_device *pdev;
	struct gpio_keys_platform_data *pdata;
	struct device_node *pp;
	int nbuttons;
	int i;
	int ret = -ENOMEM;

	pdev = kzalloc(sizeof(*pdev), GFP_KERNEL);
	if (!pdev) {
		pr_err("%s: failed to alloc platform_device\n",
			__func__);
		return;
	}
	pdev->name = "gpio-keys";
	pdev->id   = -1;

	pdata = kzalloc(sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		pr_err("%s: failed to alloc gpio_keys_platform_data\n",
			__func__);
		goto free_pdev;
	}

	nbuttons = of_get_available_child_count(np);
	pdata->buttons = kcalloc(nbuttons, sizeof(*pdata->buttons), GFP_KERNEL);
	if (!pdata->buttons) {
		pr_err("%s: failed to alloc gpio_keys_button\n", __func__);
		goto free_pdata;
	}
	pdata->nbuttons = nbuttons;

	pdata->rep = !!of_get_property(np, "autorepeat", NULL);
	of_property_read_string(np, "label", &pdata->name);
	i = 0;
	for_each_available_child_of_node(np, pp) {
		ret = rtk_gpio_keys_init_button(pp, pdata->buttons + i);
		if (ret) {
			pr_err("%s: failed to init button%d from dt: %d\n",
				__func__, i, ret);
			goto free_buttons;
		}
		i++;
	}

	pdev->dev.platform_data = pdata;
	ret = platform_device_register(pdev);
	if (ret) {
		pr_err("%s: failed to register platform_device: %d\n",
			__func__, ret);
		goto free_buttons;
	}
	gpio_keys_pdev = pdev;
	pr_info("%s: ready\n", __func__);
	return;
free_buttons:
	kfree(pdata->buttons);
free_pdata:
	kfree(pdata);
free_pdev:
	kfree(pdev);
}
#else

static inline void rtk_gpio_keys_init(struct device_node *np)
{}

#endif /* CONFIG_KEYBOARD_GPIO */

static void rtk_gpio_init(struct device_node *nd)
{
	rtk_gpio_init_wu(nd);
	rtk_gpio_init_out(nd);
	rtk_gpio_keys_init(nd);
}

void rtk_gpio_suspend_init(struct device_node *node)
{

	memset(wu_en, 0, sizeof(wu_en));
	memset(wu_act, 0, sizeof(wu_act));
	memset(out_en, 0, sizeof(out_en));
	memset(out_act, 0, sizeof(out_act));
	rtk_gpio_init(node);
}

//subsys_initcall(rtk_suspend_init);

#ifdef CONFIG_SYSFS
#define RTK_SUSPEND_ATTR(_name) \
{ \
	.attr = {.name = #_name, .mode = 0644}, \
	.show =  rtk_suspend_##_name##_show, \
	.store = rtk_suspend_##_name##_store, \
}

static ssize_t rtk_suspend_gpio_wakeup_en_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;


	n += sprintf(buf + n, " En | GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (wu_en[i])
			n += sprintf(buf + n, "  * | %d\n", i);
		else
			n += sprintf(buf + n, "	| %d\n", i);
	}
	n += sprintf(buf + n, "\n");
	return n;

}

static ssize_t rtk_suspend_gpio_wakeup_en_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#else

	if (val < GPIO_WAKEUP_EN_BITS)
		rtk_suspend_gpio_wakeup_en_set(
			rtk_suspend_gpio_wakeup_en_get() ^ (0x1U << val));
	else if ((val >= GPIO_WAKEUP_EN_BITS) && (val < GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS))
		rtk_suspend_gpio_wakeup_en2_set(
			rtk_suspend_gpio_wakeup_en2_get() ^ (0x1U <<
			(val-GPIO_WAKEUP_EN_BITS)));
	return count;
#endif
}

static ssize_t rtk_suspend_gpio_wakeup_act_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;

	n += sprintf(buf + n, " Act| GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (!wu_en[i])
			n += sprintf(buf + n, "	| %d\n", i);
		else if (wu_act[i])
			n += sprintf(buf + n, "  H | %d\n", i);
		else
			n += sprintf(buf + n, "  L | %d\n", i);
	}
	n += sprintf(buf + n, "\n");

	return n;
}

static ssize_t rtk_suspend_gpio_wakeup_act_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#else

	if (val < GPIO_WAKEUP_ACT_BITS) {
		tmp = (0x1U << val);
		if (rtk_suspend_gpio_wakeup_en_get() & tmp)
			rtk_suspend_gpio_wakeup_act_set(
				rtk_suspend_gpio_wakeup_act_get() ^ tmp);
	} else {
		tmp = (0x1U << (val - GPIO_WAKEUP_ACT_BITS));
		if (rtk_suspend_gpio_wakeup_en2_get() & tmp) {
			rtk_suspend_gpio_wakeup_act2_set(
				rtk_suspend_gpio_wakeup_act2_get() ^
				(0x1U << (val-GPIO_WAKEUP_ACT_BITS)));
		}
	}

	return count;
#endif

}

static ssize_t rtk_suspend_gpio_out_en_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;

	n += sprintf(buf + n, " En | GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (out_en[i])
			n += sprintf(buf + n, "  * | %d\n", i);
		else
			n += sprintf(buf + n, "	| %d\n", i);
	}

	n += sprintf(buf + n, "\n");
	return n;

}

static ssize_t rtk_suspend_gpio_out_en_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#else

	if (val < GPIO_OUTPUT_CHANGE_EN_BITS)
		rtk_suspend_gpio_out_en_set(
			rtk_suspend_gpio_out_en_get() ^ (0x1U << val));
	else
		rtk_suspend_gpio_out_en2_set(rtk_suspend_gpio_out_en2_get() ^
			(0x1U << (val-GPIO_OUTPUT_CHANGE_EN_BITS)));

	return count;
#endif
}

static ssize_t rtk_suspend_gpio_out_act_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;

	n += sprintf(buf + n, " Act| GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < SUSPEND_ISO_GPIO_SIZE ; i++) {
		if (!out_en[i])
			n += sprintf(buf + n, "	| %d\n", i);
		else if (out_act[i])
			n += sprintf(buf + n, "  H | %d\n", i);
		else
			n += sprintf(buf + n, "  L | %d\n", i);
	}

	n += sprintf(buf + n, "\n");

	return n;
}

static ssize_t rtk_suspend_gpio_out_act_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#else

	if (val < GPIO_OUTPUT_CHANGE_ACT_BITS) {
		if (rtk_suspend_gpio_out_en_get() &  (0x1U << val)) {
			tmp = (0x1U << val);
			rtk_suspend_gpio_out_act_set(
				rtk_suspend_gpio_out_act_get() ^ tmp);
		}
	} else {
		if (rtk_suspend_gpio_out_en2_get() &
			(0x1U << (val-GPIO_OUTPUT_CHANGE_ACT_BITS))) {
			tmp = (0x1U << (val-GPIO_OUTPUT_CHANGE_ACT_BITS));
			rtk_suspend_gpio_out_act2_set(
				rtk_suspend_gpio_out_act2_get() ^ tmp);
		}
	}

	return count;
#endif

}

struct kobj_attribute rtk_suspend_gpio_wakeup_en_attr =
	RTK_SUSPEND_ATTR(gpio_wakeup_en);
struct kobj_attribute rtk_suspend_gpio_wakeup_act_attr =
	RTK_SUSPEND_ATTR(gpio_wakeup_act);
struct kobj_attribute rtk_suspend_gpio_out_en_attr =
	RTK_SUSPEND_ATTR(gpio_out_en);
struct kobj_attribute rtk_suspend_gpio_out_act_attr =
	RTK_SUSPEND_ATTR(gpio_out_act);

EXPORT_SYMBOL(rtk_suspend_gpio_wakeup_en_attr);
EXPORT_SYMBOL(rtk_suspend_gpio_wakeup_act_attr);
EXPORT_SYMBOL(rtk_suspend_gpio_out_en_attr);
EXPORT_SYMBOL(rtk_suspend_gpio_out_act_attr);

#endif


