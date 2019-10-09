/*
 *  dptx_switch.c - RTK display port driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>

#include "dptx_core.h"

#define DPTX_SWITCH_NAME "dptx"

static irqreturn_t rtk_hpd_isr(int irq, void *dev_id)
{
	struct rtk_dptx_switch *swdev = (struct rtk_dptx_switch *)dev_id;

	schedule_delayed_work(&swdev->work, 1);

	return IRQ_HANDLED;
}

static ssize_t dptx_switch_print_state(struct switch_dev *sdev, char *buffer)
{
	struct rtk_dptx_switch *swdev = 
			container_of(sdev, struct rtk_dptx_switch, sw);

	return sprintf(buffer, "%d", swdev->state);
}

int dptx_switch_get_state(struct rtk_dptx_switch *swdev)
{
	swdev->state = gpio_get_value(swdev->hpd_gpio);
	return swdev->state;
}

static void dptx_switch_work_func(struct work_struct *work)
{
	struct rtk_dptx_switch *swdev =
			container_of(work, struct rtk_dptx_switch, work.work);
	struct rtk_dptx_device *dptx_dev =
			container_of(swdev, struct rtk_dptx_device, swdev);
	struct device *dev = dptx_dev->dev;
	int ret;
	unsigned char *block;
	struct edid *edid;

	swdev->state = gpio_get_value(swdev->hpd_gpio);
	if (swdev->state != switch_get_state(&swdev->sw))
		dev_info(dev, "%s\n", swdev->state?"plugged in":"pulled out");
	else
		return;

	if (swdev->state) {
		if (!dptx_dev->ignore_edid) {
			ret = dptx_read_edid(&dptx_dev->hwinfo,
				dptx_dev->cap.edid_ptr, 256);
			if (ret < 0) {
				dev_err(dev, "Read EDID fail\n");
#ifdef TESTING
				dptx_config_tv_system(&dptx_dev->hwinfo);
#endif
				return;
			}
		}
		block = dptx_dev->cap.edid_ptr;
		dptx_dev->cap.sink_cap_available = true;

		edid = (struct edid *)dptx_dev->cap.edid_ptr;
		memset(&dptx_dev->cap.sink_cap, 0,
			sizeof(struct sink_capabilities_t));
		dptx_add_edid_modes(edid, &dptx_dev->cap.sink_cap);
#ifdef TESTING
		dptx_config_tv_system(&dptx_dev->hwinfo);
#endif
	}
	switch_set_state(&swdev->sw, swdev->state);
}

int rtk_dptx_switch_suspend(struct rtk_dptx_device *dptx_dev)
{
	struct rtk_dptx_switch *swdev = &dptx_dev->swdev;

	disable_irq(swdev->hpd_irq);

	swdev->state = 0;
	switch_set_state(&swdev->sw, swdev->state);
	return 0;
}

int rtk_dptx_switch_resume(struct rtk_dptx_device *dptx_dev)
{
	struct rtk_dptx_switch *swdev = &dptx_dev->swdev;

	disable_irq(swdev->hpd_irq);
	schedule_delayed_work(&swdev->work, 10);
	return 0;
}

int register_dptx_switch(struct rtk_dptx_device *dptx_dev)
{
	struct device *dev = dptx_dev->dev;
	struct device_node *hpd;
	struct rtk_dptx_switch *swdev;
	int irq;
	int gpio;

	swdev = &dptx_dev->swdev;

	hpd = of_get_child_by_name(dev->of_node, "dp_hpd");
	if (IS_ERR(hpd)) {
		dev_err(dev, "[%s] can't get hot plug child node\n", __func__);
		goto fail;
	}

	gpio = of_get_gpio(hpd, 0);
	if (gpio_request(gpio, hpd->name)) {
		dev_err(dev, "[%s] can't get hot plug gpio\n", __func__);
		goto fail;
	}
	gpio_direction_input(gpio);
	gpio_set_debounce(gpio, 30*1000);
	swdev->hpd_gpio = gpio;

	irq = irq_of_parse_and_map(hpd, 0);
	irq_set_irq_type(irq, IRQ_TYPE_EDGE_BOTH);
	if (request_irq(irq, rtk_hpd_isr, IRQF_SHARED, "DP_HPD", swdev)) {
		dev_err(dev, "[%s] request hot plug irq fail\n", __func__);
		goto fail;
	}
	swdev->hpd_irq = irq;

	swdev->sw.name = DPTX_SWITCH_NAME;
	swdev->sw.print_state = dptx_switch_print_state;
	if (switch_dev_register(&swdev->sw) < 0) {
		dev_err(dev, "[%s] register switch device err\n", __func__);
		goto fail;
	}

	INIT_DELAYED_WORK(&swdev->work, dptx_switch_work_func);

	switch_set_state(&swdev->sw, 0);
	schedule_delayed_work(&swdev->work, 200);
fail:
	return -1;
}
