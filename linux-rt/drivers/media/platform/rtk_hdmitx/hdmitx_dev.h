/*
 * hdmitx_dev.h - RTK hdmitx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDMITX_DEV_H__
#define __HDMITX_DEV_H__

#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/switch.h>
#include <linux/miscdevice.h>


typedef struct {
	char *name;
	struct miscdevice miscdev;
	struct switch_dev sdev;
	struct device dev;
	void __iomem *reg_base;
	struct reset_control *reset_hdmi;
	struct clk *clk_hdmi;
	int hpd_gpio;
	unsigned int hpd_irq;
} hdmitx_device_t;


#define to_hdmitx_device(x)  container_of(x, hdmitx_device_t, dev)

static inline void *hdmitx_get_drvdata(hdmitx_device_t *device)
{
	return dev_get_drvdata(&device->dev);
}

static inline void hdmitx_set_drvdata(hdmitx_device_t *device, void *data)
{
	struct device *dev = &device->dev;

	dev_set_drvdata(dev, data);
}

extern int register_hdmitx_switchdev(hdmitx_device_t *device);
extern void deregister_hdmitx_switchdev(hdmitx_device_t *device);
extern int show_hpd_status(bool real_time);
extern int rtk_hdmitx_switch_suspend(void);
extern int rtk_hdmitx_switch_resume(void);

int hdmitx_get_raw_edid(unsigned char *edid);

#endif /* __HDMITX_DEV__H__ */

