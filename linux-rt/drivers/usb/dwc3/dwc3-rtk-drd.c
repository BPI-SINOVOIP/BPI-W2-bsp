/**
 * dwc3-rtk-drd.c - Realtek DWC3 Specific Glue layer
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/of.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/usb/composite.h>

#include "core.h"
#include "gadget.h"
#include "io.h"
#include "dwc3-rtk-drd.h"

extern int rtk_dwc3_drd_core_soft_reset(struct dwc3 *dwc);
extern int rtk_dwc3_drd_event_buffers_setup(struct dwc3 *dwc);
extern int dwc3_gadget_restart(struct dwc3 *dwc);
extern int dwc3_gadget_stop_on_switch(struct dwc3 *dwc);


struct usb_gadget_driver *rtk_dwc3_set_and_get_usb_gadget_driver(
	    struct usb_gadget_driver *driver)
{
	static struct usb_gadget_driver *gadget_driver = NULL;
	struct usb_gadget_driver *local_driver = gadget_driver;

	gadget_driver = driver;

	return local_driver;
}
EXPORT_SYMBOL_GPL(rtk_dwc3_set_and_get_usb_gadget_driver);

int dwc3_drd_to_host(struct dwc3 *dwc)
{
	int ret;
	unsigned long timeout;
	//unsigned long flags = 0;
	u32 reg;

	dev_info(dwc->dev, "%s START....", __func__);
	if (dwc->has_gadget) {
		if (dwc->gadget_driver != NULL) {
			rtk_dwc3_set_and_get_usb_gadget_driver(dwc->gadget_driver);
			usb_gadget_unregister_driver(dwc->gadget_driver);
		}
		dwc3_gadget_exit(dwc);
	}
	wmb();

	if (dwc->has_xhci) {
		dev_info(dwc->dev, "%s Now is host", __func__);
		return 0;
	}

	/* issue device SoftReset too */
	timeout = jiffies + msecs_to_jiffies(500);
	dwc3_writel(dwc->regs, DWC3_DCTL, DWC3_DCTL_CSFTRST);
	do {
		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		if (!(reg & DWC3_DCTL_CSFTRST))
			break;

		if (time_after(jiffies, timeout)) {
			dev_err(dwc->dev, "Reset Timed Out\n");
			ret = -ETIMEDOUT;
			goto err0;
		}

		cpu_relax();
	} while (true);

	dev_info(dwc->dev, "%s: call dwc3_core_soft_reset\n", __func__);
	ret = rtk_dwc3_drd_core_soft_reset(dwc);
	if (ret) {
		dev_err(dwc->dev, "soft reset failed\n");
		goto err0;
	}

//	spin_lock_irqsave(&dwc->lock, flags);
	ret = rtk_dwc3_drd_event_buffers_setup(dwc);
	if (ret) {
		dev_err(dwc->dev, "failed to setup event buffers\n");
		goto err0;
	}

	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_HOST);

	ret = dwc3_host_init(dwc);
	if (ret) {
		dev_err(dwc->dev, "failed to init host\n");
		goto err0;
	}
err0:
//	spin_unlock_irqrestore(&dwc->lock, flags);
	dev_info(dwc->dev, "%s END....", __func__);
	return ret;
}

int dwc3_drd_to_device(struct dwc3 *dwc)
{
	int ret;
	unsigned long timeout, flags = 0;
	u32 reg;

	dev_info(dwc->dev, "%s START....", __func__);

	if (dwc->has_xhci) {
		dev_info(dwc->dev, "%s dwc3_host_exit", __func__);
		dwc3_host_exit(dwc);
	}
	wmb();

	if (dwc->has_gadget) {
		dev_info(dwc->dev, "%s Now is gadget", __func__);
		return 0;
	}

	/* issue device SoftReset too */
	timeout = jiffies + msecs_to_jiffies(500);
	dwc3_writel(dwc->regs, DWC3_DCTL, DWC3_DCTL_CSFTRST);
	do {
		reg = dwc3_readl(dwc->regs, DWC3_DCTL);
		if (!(reg & DWC3_DCTL_CSFTRST))
			break;

		if (time_after(jiffies, timeout)) {
			dev_err(dwc->dev, "Reset Timed Out\n");
			ret = -ETIMEDOUT;
			goto err0;
		}

		cpu_relax();
	} while (true);

	ret = rtk_dwc3_drd_core_soft_reset(dwc);
	if (ret) {
		dev_err(dwc->dev, "soft reset failed\n");
		goto err0;
	}

	spin_lock_irqsave(&dwc->lock, flags);

	ret = rtk_dwc3_drd_event_buffers_setup(dwc);
	if (ret) {
		dev_err(dwc->dev, "failed to setup event buffers\n");
		goto err0;
	}

	dwc3_set_mode(dwc, DWC3_GCTL_PRTCAP_DEVICE);

	spin_unlock_irqrestore(&dwc->lock, flags);

	ret = dwc3_gadget_init(dwc);
	if (ret) {
		dev_err(dwc->dev, "failed to init gadget\n");
		goto err0;
	} else {
		struct usb_gadget_driver *driver =
			    rtk_dwc3_set_and_get_usb_gadget_driver(NULL);
		if (driver)
			ret = usb_gadget_probe_driver(driver);
	}
	if (ret) {
		dev_err(dwc->dev, "failed to usb_gadget probe gadget_driver\n");
		goto err0;
	}
err0:
	dev_info(dwc->dev, "%s END....", __func__);
	return ret;
}

int dwc3_drd_to_stop_all(struct dwc3 *dwc)
{
	int ret = 0;

	dev_info(dwc->dev, "%s START....", __func__);
	if (dwc->has_xhci)
		dwc3_host_exit(dwc);
	if (dwc->has_gadget) {
		if (dwc->gadget_driver != NULL) {
			rtk_dwc3_set_and_get_usb_gadget_driver(dwc->gadget_driver);
			usb_gadget_unregister_driver(dwc->gadget_driver);
		}
		dwc3_gadget_exit(dwc);
	}
	wmb();
	dev_info(dwc->dev, "%s END....", __func__);
	return ret;
}
