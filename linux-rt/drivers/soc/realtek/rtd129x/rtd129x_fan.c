/*
 * rtd129x_fan.c - fan driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/slab.h>
#include <linux/reset-helper.h>
#include <linux/reset.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/pwm.h>

#define REG_FAN_CTRL 0x0
#define REG_FAN_DEBOUNCE 0x4
#define REG_FAN_TIMER_TV 0x8
#define REG_FAN_TIMER_CV 0xC
#define REG_FAN_COUNTER_CV 0x10

#define FAN_EN BIT(0)
#define FAN_INT_EN BIT(1)

#define FAN_DEBOUNCE_W_EN BIT(3)
#define FAN_DEBOUNCE_MASK 0x7

#define FAN_DEBOUNCE_DEFAULT 0x0
#define FAN_TIMER_TV_DEFAULT 0x100

#define SB2_MUXPAD4_FAN_EN_MASK (0x3 << 22)
#define SB2_MUXPAD4_FAN_EN (0x2 << 22)

struct rtk_fan_data {
	void __iomem *reg_base;

	struct device *dev;
	struct pwm_device *pwm;

	int fan_debounce;
	int timer_target;
	uint64_t speed;

	int ctrl_speed;
#define MAX_CTRL_SPEED 10
};

static int rtk_fan_enable(struct rtk_fan_data *fan_data) {
	void __iomem *reg_base = fan_data->reg_base;

	writel(FAN_EN | FAN_INT_EN, reg_base + REG_FAN_CTRL);

	dev_dbg(fan_data->dev, "%s REG_FAN_CTRL=0x%x",
			__func__, readl(reg_base + REG_FAN_CTRL));

	return 0;
}

static int rtk_fan_disable(struct rtk_fan_data *fan_data) {
	void __iomem *reg_base = fan_data->reg_base;

	writel(0x0, reg_base + REG_FAN_CTRL);

	dev_dbg(fan_data->dev, "%s REG_FAN_CTRL=0x%x",
			__func__, readl(reg_base + REG_FAN_CTRL));

	return 0;
}

static int rtk_fan_get_debound_time(struct rtk_fan_data *fan_data) {
	void __iomem *reg_base = fan_data->reg_base;
	int fan_debounce;

	fan_debounce = readl(reg_base + REG_FAN_DEBOUNCE) & FAN_DEBOUNCE_MASK;

	if (fan_debounce != fan_data->fan_debounce) {
		dev_err(fan_data->dev, "%s ERROR fan_debounce = %x, but set fan_debounce = %x",
			__func__, fan_debounce, fan_data->fan_debounce);
	}
	return fan_debounce;
}

static int rtk_fan_set_debound_time(struct rtk_fan_data *fan_data, int fan_debounce_new) {
	void __iomem *reg_base = fan_data->reg_base;
	int fan_debounce;

	fan_debounce = rtk_fan_get_debound_time(fan_data);
	if (fan_debounce != fan_debounce_new) {
		writel(FAN_DEBOUNCE_W_EN |
				(fan_debounce_new & FAN_DEBOUNCE_MASK),
				reg_base + REG_FAN_DEBOUNCE);
		fan_data->fan_debounce = fan_debounce;
	}
	return 0;
}

static int rtk_fan_get_timer_target(struct rtk_fan_data *fan_data) {
	void __iomem *reg_base = fan_data->reg_base;
	int timer_target;

	timer_target = readl(reg_base + REG_FAN_TIMER_TV);

	if (timer_target != fan_data->timer_target) {
		dev_err(fan_data->dev, "%s ERROR timer_target = %d, but set timer_target = %d",
			__func__, timer_target, fan_data->timer_target);
	}
	return timer_target;
}

static int rtk_fan_set_timer_target(struct rtk_fan_data *fan_data, int timer_target_new) {
	void __iomem *reg_base = fan_data->reg_base;
	int timer_target;

	timer_target = rtk_fan_get_timer_target(fan_data);
	if (timer_target != timer_target_new) {
		writel(timer_target_new, reg_base + REG_FAN_TIMER_TV);
		fan_data->timer_target = timer_target_new;
	}
	return 0;
}

static int rtk_fan_get_speed(struct rtk_fan_data *fan_data) {
	return fan_data->speed;
}

static int rtk_fan_ctrl_speed(struct rtk_fan_data *fan_data, int ctrl_speed) {
	if (ctrl_speed > MAX_CTRL_SPEED) ctrl_speed = MAX_CTRL_SPEED;

	if (fan_data->pwm) {
		int period_ns = pwm_get_period(fan_data->pwm);
		int duty_ns = period_ns * ctrl_speed / MAX_CTRL_SPEED;
		dev_dbg(fan_data->dev, "%s to set pwm default duty_ns =%d,  period_ns = %d!",
		__func__, duty_ns, period_ns);
		pwm_config(fan_data->pwm, duty_ns, period_ns);
	}
	fan_data->ctrl_speed = ctrl_speed;
}

static int rtk_fan_compute_speed(struct rtk_fan_data *fan_data) {
	void __iomem *reg_base = fan_data->reg_base;

	int timer_target, counter_value;
	uint64_t factor = 90000*60/2;
	uint64_t speed;

	timer_target = fan_data->timer_target;
	counter_value = readl(reg_base + REG_FAN_COUNTER_CV);

	//(9801bc10[31:0]/2) / (9801bc08[31:0]/90000/60)
	speed = (counter_value * factor) / timer_target;

	fan_data->speed = speed;

	dev_dbg(fan_data->dev, "%s speed =%u, timer_target=%d, counter_value=%d\n", __func__, speed, timer_target, counter_value);

	return 0;
}

static irqreturn_t rtk_fan_irq(int irq, void *data) {
	struct rtk_fan_data *fan_data = (struct rtk_fan_data *) data;
	struct device *dev = fan_data->dev;
	unsigned long flags;

	dev_dbg(dev, "%s Enter ...", __func__);

	rtk_fan_compute_speed(fan_data);

	dev_dbg(dev, "%s Exit ...", __func__);
	return IRQ_HANDLED;
}

static ssize_t fan_debounce_show(struct device *dev, struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "%d\n", rtk_fan_get_debound_time(fan_data));
}

static ssize_t fan_debounce_store(struct device *dev, struct device_attribute *attr,
		const char *buffer, size_t size) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);
	int ret;
	int value;

	ret = sscanf(buffer, "%d", &value);
	if (ret != 1)
		return -EINVAL;

	rtk_fan_set_debound_time(fan_data, value);

	return size;
}

static ssize_t fan_timer_target_show(struct device *dev,
		struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "%d\n", rtk_fan_get_timer_target(fan_data));
}

static ssize_t fan_timer_target_store(struct device *dev, struct device_attribute *attr,
		const char *buffer, size_t size) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);
	int ret;
	int value;

	ret = sscanf(buffer, "%d", &value);
	if (ret != 1)
		return -EINVAL;

	rtk_fan_set_timer_target(fan_data, value);

	return size;
}

static ssize_t fan_timer_value_show(struct device *dev,
		struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "real-time timer value %d\n", readl(fan_data->reg_base + REG_FAN_TIMER_CV));
}

static ssize_t fan_counter_value_show(struct device *dev,
		struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "real-time counter value %d\n", readl(fan_data->reg_base + REG_FAN_COUNTER_CV));
}

static ssize_t fan_speed_show(struct device *dev,
		struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "%u\n", rtk_fan_get_speed(fan_data));
}

static ssize_t fan_ctrl_speed_show(struct device *dev,
		struct device_attribute *attr, char *buffer) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);

	return sprintf(buffer, "now %d of %d (set 0~10)\n", fan_data->ctrl_speed, MAX_CTRL_SPEED);
}

static ssize_t fan_ctrl_speed_store(struct device *dev, struct device_attribute *attr,
		const char *buffer, size_t size) {
	struct rtk_fan_data *fan_data = dev_get_drvdata(dev);
	int ret;
	int value;

	ret = sscanf(buffer, "%d", &value);
	if (ret != 1)
		return -EINVAL;

	rtk_fan_disable(fan_data);

	rtk_fan_ctrl_speed(fan_data, value);

	rtk_fan_enable(fan_data);

	return size;
}

static DEVICE_ATTR(fan_debounce, 0644, fan_debounce_show, fan_debounce_store);
static DEVICE_ATTR(fan_timer_target, 0644, fan_timer_target_show, fan_timer_target_store);
static DEVICE_ATTR_RO(fan_timer_value);
static DEVICE_ATTR_RO(fan_counter_value);
static DEVICE_ATTR_RO(fan_speed);
static DEVICE_ATTR(fan_ctrl_speed, 0644, fan_ctrl_speed_show, fan_ctrl_speed_store);

static const struct attribute *rtk_fan_attrs[] = {
	&dev_attr_fan_debounce.attr,
	&dev_attr_fan_timer_target.attr,
	&dev_attr_fan_timer_value.attr,
	&dev_attr_fan_counter_value.attr,
	&dev_attr_fan_speed.attr,
	&dev_attr_fan_ctrl_speed.attr,
	NULL
};

static int rtk_fan_create_sysfs(struct rtk_fan_data *fan_data)
{
	struct device *dev = fan_data->dev;
	int retval;

	retval = sysfs_create_files(&dev->kobj,
			(const struct attribute **)rtk_fan_attrs);

	return retval;
}

static int rtk_fan_init(struct rtk_fan_data *fan_data, struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	struct device_node *node = pdev->dev.of_node;
	int ret;
	int fan_debounce, timer_target;
	u32 value;

	/* GET clock */
	struct clk *clk_fan = clk_get(NULL, "clk_en_fan");
	/* GET reset controller */
	struct reset_control *reset_fan = rstc_get("rstn_fan");

	reset_control_deassert(reset_fan);
	clk_prepare_enable(clk_fan);

	ret = of_property_read_u32(node, "fan_debounce",
					&fan_debounce);
	if (ret < 0) {
		dev_info(dev, "%s NO set debounce time!", __func__);
		fan_debounce = FAN_DEBOUNCE_DEFAULT;
	}
	rtk_fan_set_debound_time(fan_data, fan_debounce);

	ret = of_property_read_u32(node, "timer_target",
					&timer_target);
	if (ret < 0) {
		dev_info(dev, "%s NO set timer_target!", __func__);
		timer_target = FAN_TIMER_TV_DEFAULT;
	}

	fan_data->pwm = pwm_get(dev, NULL);

	rtk_fan_ctrl_speed(fan_data, MAX_CTRL_SPEED / 2);

	rtk_fan_set_timer_target(fan_data, timer_target);

	rtk_fan_enable(fan_data);

	return 0;
}

static int rtk_fan_probe(struct platform_device *pdev) {
	struct device *dev = &pdev->dev;
	struct device_node *node = NULL;
	struct rtk_fan_data *fan_data;
	int irq, ret;

	dev_info(dev, "%s Enter ..", __func__);
	node = pdev->dev.of_node;
	if (!node) {
		dev_err(dev, "%s Fail to get device tree node", __func__);
		return -ENODEV;
	}

	fan_data = devm_kzalloc(&pdev->dev, sizeof(*fan_data), GFP_KERNEL);
	if (!fan_data) {
		dev_err(dev, "%s No memory!", __func__);
		return -ENOMEM;
	}

	fan_data->dev = dev;

	fan_data->reg_base = of_iomap(node, 0);

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "%s No IRQ. Check %s setup!\n",
				__func__, dev_name(&pdev->dev));
		ret = -ENODEV;
		goto err1;
	}

	ret = request_irq(irq, rtk_fan_irq,
			IRQF_SHARED, "rtk_fan_irq", fan_data);

	if (ret < 0) {
		dev_err(dev, "%s Fail to request_irq (ret=%d)", __func__, ret);
		goto err1;
	}

	ret = rtk_fan_init(fan_data, pdev);
	if (ret < 0) {
		dev_err(dev, "%s Fail to init rtk_fan (ret=%d)", __func__, ret);
		goto err1;
	}

	ret = rtk_fan_create_sysfs(fan_data);
	if (ret < 0) {
		dev_err(dev, "%s Fail to create sysfs (ret=%d)", __func__, ret);
		goto err1;
	}

	platform_set_drvdata(pdev, fan_data);

	dev_info(dev, "%s Exit", __func__);
	return 0;

err1:
	kfree(fan_data);
	dev_err(dev, "%s Probe Fail (ret=%d)", __func__, ret);
	return ret;
}

static int rtk_fan_remove(struct platform_device *pdev) {
	struct rtk_fan_data *fan_data = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);
	if (fan_data)
		kfree(fan_data);

	return 0;
}

static const struct of_device_id rtk_fan_of_match[] = {
	{.compatible = "Realtek,rtd129x-fan",},
	{ /* Sentinel */ },
};

static struct platform_driver rtk_fan_driver = {
	.probe = rtk_fan_probe,
	.remove = rtk_fan_remove,
	.driver = {
		.name = "rtk-fan",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(rtk_fan_of_match),
	},
};

static int __init rtk_fan_probe_init(void)
{
	return platform_driver_probe(&rtk_fan_driver, rtk_fan_probe);
}

late_initcall(rtk_fan_probe_init);

