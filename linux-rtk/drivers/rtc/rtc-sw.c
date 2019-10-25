/*
 * rtc-sw.c - Realtek SW RTC driver
 *
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/err.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/rtc.h>
#include <linux/jiffies.h>
#include <linux/spinlock.h>
#include <linux/slab.h>

#define TIME_2014_01_01       1388534400
#define SW_RTC_DEFAULT_TIME   TIME_2014_01_01


struct sw_rtc_data {
	struct rtc_device *rtc;

	struct rtc_time time;
	u64 last_jiffies;
	spinlock_t lock;

	struct rtc_time time_alarm;
	struct timer_list timer;
};

static void sw_rtc_alarm_timeout(unsigned long arg)
{
	struct sw_rtc_data *data = (struct sw_rtc_data *)arg;
	unsigned long events = RTC_IRQF | RTC_AF;

	rtc_update_irq(data->rtc, 1, events);
}

static struct sw_rtc_data *create_sw_rtc(void)
{
	struct sw_rtc_data *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	spin_lock_init(&data->lock);
	rtc_time_to_tm(SW_RTC_DEFAULT_TIME, &data->time);
	data->last_jiffies = get_jiffies_64();

	init_timer(&data->timer);
	data->timer.function = sw_rtc_alarm_timeout;
	data->timer.data = (unsigned long)data;
	data->time_alarm = data->time;
	return data;
}

static void destroy_sw_rtc(struct sw_rtc_data *data)
{
	if (timer_pending(&data->timer))
		del_timer(&data->timer);
	kfree(data);
}

static void sw_rtc_update_tm(struct sw_rtc_data *data, struct rtc_time *tm)
{
	spin_lock(&data->lock);
	data->time = *tm;
	data->last_jiffies = get_jiffies_64();
	spin_unlock(&data->lock);
}

static void sw_rtc_get_tm(struct sw_rtc_data *data, struct rtc_time *tm)
{
	time64_t time;
	u64 cur_jiffies = get_jiffies_64();
	u64 delta;

	spin_lock(&data->lock);
	delta = cur_jiffies - data->last_jiffies;
	time = rtc_tm_to_time64(&data->time);
	spin_unlock(&data->lock);

	time += jiffies_to_msecs(delta) / 1000;
	rtc_time64_to_tm(time, tm);
}

static int sw_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	sw_rtc_get_tm(data, tm);
	return rtc_valid_tm(tm);
}

static int sw_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	sw_rtc_update_tm(data, tm);
	return 0;
}

static int sw_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	alrm->time = data->time_alarm;
	alrm->enabled = timer_pending(&data->timer);
	alrm->pending = 0;

	return 0;
}

static int sw_rtc_alarm_start(struct sw_rtc_data *data)
{
	struct rtc_time curr;
	time64_t t_cur, t_alarm, delta;

	sw_rtc_get_tm(data, &curr);

	t_cur = rtc_tm_to_time64(&curr);
	t_alarm = rtc_tm_to_time64(&data->time_alarm);

	if (t_cur >= t_alarm)
		return -EINVAL;
	delta = t_alarm - t_cur;

	data->timer.expires = get_jiffies_64() + msecs_to_jiffies(delta * 1000);
	add_timer(&data->timer);
	return 0;
}

static int sw_rtc_set_alarm(struct device *dev,
	struct rtc_wkalrm *alrm)
{
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	data->time_alarm = alrm->time;
	if (timer_pending(&data->timer)) {
		del_timer(&data->timer);
		sw_rtc_alarm_start(data);
	}

	return 0;
}

static int sw_rtc_alarm_irq_enable(struct device *dev, unsigned int enable)
{
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	if (enable) {
		if (timer_pending(&data->timer))
			del_timer(&data->timer);
		sw_rtc_alarm_start(data);

	} else {
		if (timer_pending(&data->timer))
			del_timer(&data->timer);
	}
	return 0;
}

static const struct rtc_class_ops sw_rtc_ops = {
	.read_time = sw_rtc_read_time,
	.set_time = sw_rtc_set_time,
	.read_alarm = sw_rtc_read_alarm,
	.set_alarm = sw_rtc_set_alarm,
	.alarm_irq_enable = sw_rtc_alarm_irq_enable,
};

static int sw_rtc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sw_rtc_data *data;
	int ret = 0;

	data = create_sw_rtc();
	if (!data) {
		dev_err(dev, "fail to create_sw_rtc\n");
		return -ENOMEM;
	}

	dev_set_drvdata(dev, data);
	device_init_wakeup(dev, true);

	data->rtc = devm_rtc_device_register(&pdev->dev, "rtc-sw", &sw_rtc_ops,
		THIS_MODULE);
	if (IS_ERR(data->rtc)) {
		ret = PTR_ERR(data->rtc);
		dev_err(dev, "rtc_device_register() returns %d\n", ret);
		return ret;
	}

	dev_info(dev, "initialized\n");
	return ret;
}

static int  sw_rtc_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct sw_rtc_data *data = dev_get_drvdata(dev);

	destroy_sw_rtc(data);
	dev_info(dev, "removed\n");
	return 0;
}

static struct platform_driver sw_rtc_driver = {
	.probe = sw_rtc_probe,
	.remove = sw_rtc_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-sw-rtc",
	},
};

static struct platform_device *sw_rtc_dev;

static int __init sw_rtc_init(void)
{
	int ret;

	ret = platform_driver_register(&sw_rtc_driver);
	if (ret) {
		pr_err("%s: platform_driver_register() returns %d\n", __func__, ret);
		return ret;
	}

	sw_rtc_dev = platform_device_register_simple("rtk-sw-rtc", 0, NULL, 0);
	if (IS_ERR(sw_rtc_dev)) {
		ret = PTR_ERR(sw_rtc_dev);
		pr_err("%s: platform_driver_register() returns %d\n", __func__, ret);
		platform_driver_unregister(&sw_rtc_driver);
		return ret;
	}
	return 0;
}
module_init(sw_rtc_init);

static void __exit sw_rtc_exit(void)
{
	platform_device_unregister(sw_rtc_dev);
	platform_driver_unregister(&sw_rtc_driver);
}
module_exit(sw_rtc_exit);

