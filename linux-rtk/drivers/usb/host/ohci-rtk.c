/*
 *  ohic-rtk.c RTK OHCI HCD (Host Controller Driver)
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/mbus.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/usb.h>
#include <linux/usb/hcd.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/suspend.h>
#include <linux/completion.h>

#define RTK_OHCI_HCD_NAME "rtk-ohci"

extern int usb_disabled(void);

static int ohci_rtk_setup(struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	int ret;

	ohci_dbg(ohci, "ohci_rtk_setup, ohci:%p", ohci);

	ret = ohci_init(ohci);
	if (ret < 0)
		return ret;
	return 0;
}

static int ohci_rtk_dmp_start(struct usb_hcd *hcd)
{
	struct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	int ret;

	ohci_dbg(ohci, "ohci_rtk_dmp_start, ohci:%p", ohci);

	ret = ohci_run(ohci);
	if (ret < 0) {
		printk ("can't start %s", hcd->self.bus_name);
		ohci_stop(hcd);
		return ret;
	}

	return 0;
}

static const struct hc_driver ohci_rtk_dmp_hc_driver = {
	.description =		hcd_name,
	.product_desc =		"Rtk Dmp OHCI",
	.hcd_priv_size =	sizeof(struct ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_MEMORY,

	/*
	 * basic lifecycle operations
	 */
	.reset =		ohci_rtk_setup,
	.start =		ohci_rtk_dmp_start,
	.stop =			ohci_stop,
	.shutdown =		ohci_shutdown,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoint_disable =	ohci_endpoint_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#ifdef	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#endif
	.start_port_reset =	ohci_start_port_reset,
};

struct ohci_rtk {
	struct device *dev;
	struct ohci_hcd *ohci;
	struct usb_phy *phy;
	int irq;

	struct work_struct work;
};

extern void rtk_usb_init_gpio_power_on(struct device *dev);
extern int rtk_usb_manager_schedule_work(struct device *usb_dev, struct work_struct *work);

static void ohci_rtk_probe_work(struct work_struct *work)
{
	struct ohci_rtk *rtk = container_of(work, struct ohci_rtk, work);
	struct device		*dev = rtk->dev;
	struct usb_hcd *hcd = ohci_to_hcd(rtk->ohci);
	struct usb_phy *phy = rtk->phy;
	int irq = rtk->irq;
	int ret = 0;

	unsigned long probe_time = jiffies;

	dev_info(dev, "%s Start ...\n", __func__);

	usb_phy_init(phy);

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (ret) {
		dev_err(dev, "%s: error add hcd\n", __func__);
		usb_put_hcd(hcd);
	}

	rtk_usb_init_gpio_power_on(dev);

	dev_info(dev, "%s End ... ok! (take %d ms)\n", __func__, jiffies_to_msecs(jiffies - probe_time));
	return;
}

static int ohci_rtk_drv_probe(struct platform_device *pdev)
{
	struct usb_hcd *hcd;
	struct ohci_hcd *ohci;
	void *reg_base;
	struct resource res;
	int irq;
	int ret;
	struct usb_phy *phy;
	unsigned long probe_time = jiffies;

	if (usb_disabled())
		return -ENODEV;

	dev_info(&pdev->dev, "Probe Realtek-SoC USB OHCI Host Controller\n");

	//phy = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
	phy = devm_usb_get_phy_by_phandle(&pdev->dev, "usb-phy", 0);
	if (IS_ERR(phy)) {
		dev_err(&pdev->dev, "No usb phy found\n");
		return -ENODEV;
	}

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev,
			"Found HC with no IRQ. Check %s setup!\n",
			dev_name(&pdev->dev));
		return -ENODEV;
	}

	if (of_address_to_resource(pdev->dev.of_node, 0, &res)) {
		dev_err(&pdev->dev,
			"Found HC with no register addr. Check %s setup!\n",
			dev_name(&pdev->dev));
		return -ENODEV;
	}

	/*
	 * Right now device-tree probed devices don't get dma_mask
	 * set. Since shared usb code relies on it, set it here for
	 * now. Once we have dma capability bindings this can go away.
	 */
	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
	if (!pdev->dev.coherent_dma_mask)
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	hcd = usb_create_hcd(&ohci_rtk_dmp_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	reg_base = of_iomap(pdev->dev.of_node, 0);
	if (!reg_base) {
		dev_err(&pdev->dev, "ioremap failed\n");
		ret = -ENOMEM;
		goto err2;
	}

	if (readl(reg_base) == 0xdeadbeef) {
		dev_err(&pdev->dev, "%s error read ohci registers\n", __func__);
		ret = -ENODEV;
		goto err2;
	}

	hcd->regs = reg_base;

	ohci = hcd_to_ohci(hcd);

	ohci_hcd_init(ohci);

#ifdef CONFIG_USB_PATCH_ON_RTK
	if (pdev->dev.of_node) {
		u32 wrap_reg = 0;
		of_property_read_u32(pdev->dev.of_node, "wrap_reg", &wrap_reg);
		if (wrap_reg)
			ohci->wrap_reg = ioremap(wrap_reg, 0x4);
		else
			ohci->wrap_reg = NULL;
	}
#endif

	if (of_property_read_bool(pdev->dev.of_node, "delay_probe_work")) {
		struct ohci_rtk *rtk;
		rtk = devm_kzalloc(&pdev->dev, sizeof(*rtk), GFP_KERNEL);
		if (!rtk) {
			dev_err(&pdev->dev, "not enough memory\n");
			ret = -ENOMEM;
			goto err2;
		}
		rtk->dev = &pdev->dev;
		rtk->ohci = ohci;
		rtk->phy = phy;
		rtk->irq = irq;
		INIT_WORK(&rtk->work, ohci_rtk_probe_work);
		if (of_property_read_bool(pdev->dev.of_node, "ordered_probe"))
			rtk_usb_manager_schedule_work(&pdev->dev, &rtk->work);
		else
			schedule_work(&rtk->work);
	} else {
		usb_phy_init(phy);

		ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
		if (ret) {
			dev_err(&pdev->dev, "failed to add hcd with err %d\n", ret);
			goto err2;
		}
	}

	platform_set_drvdata(pdev, hcd);

	dev_info(&pdev->dev, "%s OK (take %d ms)\n", __func__, jiffies_to_msecs(jiffies - probe_time));
	return 0;

err2:
	irq_dispose_mapping(irq);
//err1:
	usb_put_hcd(hcd);
	return ret;
}

static int ohci_rtk_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_remove_hcd(hcd);

	iounmap(hcd->regs);

#ifdef CONFIG_USB_PATCH_ON_RTK
	if (hcd) {
		struct ohci_hcd *ohci;
		ohci = hcd_to_ohci(hcd);
		if (ohci->wrap_reg)
			__iounmap(ohci->wrap_reg);
	}
#endif

	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

#ifdef CONFIG_USB_PATCH_ON_RTK
extern int usb_runtime_suspend(struct device *dev);

/* Add Workaround to fixed EHCI/OHCI Wrapper can't work simultaneously */
int RTK_ohci_force_suspend(const char *func)
{
	static struct ohci_hcd *s_ohci = NULL;
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;
	struct usb_hcd *hcd = NULL;
	struct ohci_hcd *ohci = NULL;
	unsigned long	flags;

	if (s_ohci == NULL) {
		node = of_find_compatible_node(NULL, NULL, "Realtek,rtd129x-ohci");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL) {
			hcd = platform_get_drvdata(pdev);
			s_ohci = hcd_to_ohci(hcd);
		}
	} else
		ohci = s_ohci;

	if (ohci) {
		u32 hc_control;
		int resuming;

		spin_lock_irqsave(&ohci->lock, flags);
		resuming = ohci->resuming;
		spin_unlock_irqrestore(&ohci->lock, flags);

		if (resuming) {
			ohci_dbg(ohci, "%s wait for resuming done !!\n", __func__);
			if (!wait_for_completion_timeout(&ohci->resuming_done, msecs_to_jiffies(1000))) {
				ohci_info(ohci,
					"%s timed out on wait resuming_done\n", __func__);
			}
		}

		spin_lock_irqsave(&ohci->lock, flags);
		hc_control = ohci_readl (ohci, &ohci->regs->control);
		if ((hc_control&OHCI_CTRL_HCFS) == OHCI_USB_OPER) {
#ifdef CONFIG_PM
			ohci_info(ohci, "%s force suspend by %s\n",
					__func__, func);
			ohci_rh_suspend(ohci, 1);
#else
			ohci_err(ohci, "%s NO build config CONFIG_PM!!\n", __func__);
#endif
		}
		spin_unlock_irqrestore (&ohci->lock, flags);

	} else
		pr_debug("%s NO OHCI !!!\n", __func__);
	return 0;
}
#endif //CONFIG_USB_PATCH_ON_RTK

#ifdef CONFIG_PM
static int rtk_ohci_suspend(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct platform_device *pdev = to_platform_device(dev);
	struct usb_phy *phy;
	bool do_wakeup = device_may_wakeup(dev);
	int rc = 0;

	dev_info(dev, "[USB] Enter %s", __func__);

	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		goto out;
	}
	dev_info(dev, "[USB] %s Suspend mode\n", __func__);

	rc = ohci_suspend(hcd, do_wakeup);

	phy = devm_usb_get_phy_by_phandle(&pdev->dev, "usb-phy", 0);
	if (IS_ERR(phy)) {
		dev_err(&pdev->dev, "No usb phy found\n");
		return -ENODEV;
	} else {
		usb_phy_shutdown(phy);
	}
out:
	dev_info(dev, "[USB] Exit %s", __func__);
	return rc;
}

static int rtk_ohci_resume(struct device *dev)
{
	struct usb_hcd *hcd = dev_get_drvdata(dev);
	struct platform_device *pdev = to_platform_device(dev);
	struct usb_phy *phy;

	dev_info(dev, "[USB] Enter %s", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		goto out;
	}
	dev_info(dev, "[USB] %s Suspend mode\n", __func__);

	phy = devm_usb_get_phy_by_phandle(&pdev->dev, "usb-phy", 0);
	if (IS_ERR(phy)) {
		dev_err(&pdev->dev, "No usb phy found\n");
		return -ENODEV;
	} else {
		usb_phy_init(phy);
	}

	ohci_resume(hcd, false);
out:
	dev_info(dev, "[USB] Exit %s", __func__);
	return 0;
}
#else
#define rtk_ohci_suspend       NULL
#define rtk_ohci_resume        NULL
#endif

static const struct dev_pm_ops rtk_ohci_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(rtk_ohci_suspend, rtk_ohci_resume)
	//SET_LATE_SYSTEM_SLEEP_PM_OPS(rtk_ohci_suspend, rtk_ohci_resume)
};

static const struct of_device_id ohci_rtk_dt_ids[] = {
	{ .compatible = "Realtek,rtk119x-ohci", },
	{ .compatible = "Realtek,rtd129x-ohci", },
	{},
};
MODULE_DEVICE_TABLE(of, ohci_rtk_dt_ids);

static struct platform_driver ohci_rtk_driver = {
	.probe		= ohci_rtk_drv_probe,
	.remove		= ohci_rtk_drv_remove,
	.shutdown	= usb_hcd_platform_shutdown,
	.driver		= {
		.name	= RTK_OHCI_HCD_NAME,
		.owner	= THIS_MODULE,
		.pm		= &rtk_ohci_pm_ops,
		.of_match_table = of_match_ptr(ohci_rtk_dt_ids),
	},
};

MODULE_ALIAS("platform:" RTK_OHCI_HCD_NAME);
