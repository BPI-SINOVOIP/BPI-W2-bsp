/**
 * dwc3-rtk.c - Realtek DWC3 Specific Glue layer
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/clk.h>
#include <linux/usb/otg.h>
#include <linux/usb/usb_phy_generic.h>
#include <linux/usb/of.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_chip.h>

#include "../host/xhci.h" //hcy test added
#include "core.h" //hcy test added

#define WRAP_CTR_reg  0x0
#define USB2_PHY_reg  0x70

#define EN_PHY_PLL_PORT0 BIT(12)
#define EN_PHY_PLL_PORT1 BIT(13)
#define DISABLE_MULTI_REQ BIT(1)
#define USB2_PHY_SWITCH_MASK 0x707
#define USB2_PHY_SWITCH_DEVICE 0x0
#define USB2_PHY_SWITCH_HOST 0x606

struct dwc3_rtk {
	struct platform_device	*usb2_phy;
	struct platform_device	*usb3_phy;
	struct device		*dev;

	void __iomem		*regs;
	size_t		regs_size;

	struct clk		*clk;
	struct platform_device *dwc; //hjcy added

	struct work_struct work;
};

#ifdef CONFIG_RTK_USB3PHY
extern void rtk_usb3_phy_toggle(struct usb_phy *usb3_phy, bool isConnect,
	    int port);
#endif

void RTK_dwc3_usb3_phy_toggle(struct device *hcd_dev, bool isConnect, int port)
{
	struct device *dwc3_dev = NULL;
	struct dwc3 *dwc = NULL;
	if (hcd_dev == NULL) return;

	dwc3_dev = hcd_dev->parent;
	if (dwc3_dev == NULL) return;

	dwc = dev_get_drvdata(dwc3_dev);
#ifdef CONFIG_RTK_USB3PHY
	dev_dbg(dwc3_dev, "%s port=%d\n", __func__, port);
	if (dwc != NULL)
		rtk_usb3_phy_toggle(dwc->usb3_phy, isConnect, port);
#endif
}

#ifdef CONFIG_RTK_USB2PHY
extern void rtk_usb2_phy_toggle(struct usb_phy *usb3_phy, bool isConnect,
	    int port);
#endif

int RTK_dwc3_usb2_phy_toggle(struct device *hcd_dev, bool isConnect, int port)
{
	struct device *dwc3_dev = NULL;
	struct dwc3 *dwc = NULL;
	if (hcd_dev == NULL) return -1;

	dwc3_dev = hcd_dev->parent;
	if (dwc3_dev == NULL) return -1;

	dwc = dev_get_drvdata(dwc3_dev);
	if (dwc == NULL) return -1;

#ifdef CONFIG_RTK_USB2PHY
	dev_dbg(dwc3_dev, "%s port=%d\n", __func__, port);
	rtk_usb2_phy_toggle(dwc->usb2_phy, isConnect, port);
#endif
	return 0;
}

static int dwc3_rtk_register_phys(struct dwc3_rtk *rtk)
{
	struct usb_phy_generic_platform_data pdata;
	struct platform_device	*pdev;
	int			ret;

	memset(&pdata, 0x00, sizeof(pdata));

	pdev = platform_device_alloc("usb_phy_generic", PLATFORM_DEVID_AUTO);
	if (!pdev)
		return -ENOMEM;

	rtk->usb2_phy = pdev;
	pdata.type = USB_PHY_TYPE_USB2;

	ret = platform_device_add_data(rtk->usb2_phy, &pdata, sizeof(pdata));
	if (ret)
		goto err1;

	pdev = platform_device_alloc("usb_phy_generic", PLATFORM_DEVID_AUTO);
	if (!pdev) {
		ret = -ENOMEM;
		goto err1;
	}

	rtk->usb3_phy = pdev;
	pdata.type = USB_PHY_TYPE_USB3;

	ret = platform_device_add_data(rtk->usb3_phy, &pdata, sizeof(pdata));
	if (ret)
		goto err2;

	ret = platform_device_add(rtk->usb2_phy);
	if (ret)
		goto err2;

	ret = platform_device_add(rtk->usb3_phy);
	if (ret)
		goto err3;

	return 0;

err3:
	platform_device_del(rtk->usb2_phy);

err2:
	platform_device_put(rtk->usb3_phy);

err1:
	platform_device_put(rtk->usb2_phy);

	return ret;
}

/*
static int dwc3_rtk_remove_child(struct device *dev, void *unused)
{
	struct platform_device *pdev = to_platform_device(dev);

	platform_device_unregister(pdev);

	return 0;
}
*/

static void dwc3_rtk_int_dr_mode(struct dwc3_rtk *rtk, int dr_mode)
{
	switch (dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		writel(USB2_PHY_SWITCH_DEVICE |
			    (~USB2_PHY_SWITCH_MASK & readl(rtk->regs + USB2_PHY_reg)),
			    rtk->regs + USB2_PHY_reg);
		break;
	case USB_DR_MODE_HOST:
		writel(USB2_PHY_SWITCH_HOST |
			    (~USB2_PHY_SWITCH_MASK & readl(rtk->regs + USB2_PHY_reg)),
			    rtk->regs + USB2_PHY_reg);
		break;
	case USB_DR_MODE_OTG:
		//writel(BIT(11) , rtk->regs + USB2_PHY_reg);
		dev_info(rtk->dev, "%s: USB_DR_MODE_OTG\n", __func__);
		break;
	}
}

static int dwc3_rtk_init(struct dwc3_rtk *rtk)
{
	struct device		*dev = rtk->dev;
	//struct device_node	*node = dev->of_node;
	void __iomem		*regs = rtk->regs;

	if ((get_rtd_chip_id() == CHIP_ID_RTD1295 ||
		    get_rtd_chip_id() == CHIP_ID_RTD1296) &&
		    get_rtd_chip_revision() == RTD_CHIP_A00) {
		writel(DISABLE_MULTI_REQ | readl(regs + WRAP_CTR_reg),
				regs + WRAP_CTR_reg);
		dev_info(dev, "[bug fixed] 1295/1296 A00: add workaround to "
			    "disable multiple request for D-Bus");
	}

	if (get_rtd_chip_id() == CHIP_ID_RTD1395) {
		writel(EN_PHY_PLL_PORT1 | readl(regs + USB2_PHY_reg),
			    regs + USB2_PHY_reg);
		dev_info(dev, "[bug fixed] 1395 add workaround to "
			    "disable usb2 port 2 suspend!");

	}
	return 0;
}

extern void rtk_usb_init_gpio_power_on(struct device *dev);
extern int rtk_usb_manager_schedule_work(struct device *usb_dev, struct work_struct *work);

static int dwc3_rtk_probe_dwc3core(struct dwc3_rtk *rtk)
{
	struct device		*dev = rtk->dev;
	struct device_node	*node = dev->of_node;
	struct device_node	*next_node;
	int    ret = 0;

	dwc3_rtk_init(rtk);

	if (node) {
		ret = of_platform_populate(node, NULL, NULL, dev);
		if (ret) {
			dev_err(dev, "failed to add dwc3 core\n");
			return ret;
		}
		/* hcy adde below */
		//node =  of_find_compatible_node(NULL, NULL, "synopsys,dwc3");
		next_node = of_get_next_child(node, NULL);
		if (next_node != NULL) {
			struct device *next_dev;
			int dr_mode;

			rtk->dwc = of_find_device_by_node(next_node);
			next_dev = &(rtk->dwc)->dev;
			dr_mode = usb_get_dr_mode(next_dev);
			dwc3_rtk_int_dr_mode(rtk, dr_mode);
		}
	}

	rtk_usb_init_gpio_power_on(dev);

	return ret;
}

static void dwc3_rtk_probe_work(struct work_struct *work)
{
	struct dwc3_rtk *rtk = container_of(work, struct dwc3_rtk, work);
	struct device		*dev = rtk->dev;
	int    ret = 0;

	unsigned long probe_time = jiffies;

	dev_info(dev, "%s Start ...\n", __func__);

	ret = dwc3_rtk_probe_dwc3core(rtk);

	if (ret)
		dev_err(dev, "%s failed to add dwc3 core\n", __func__);

	dev_info(dev, "%s End ... ok! (take %d ms)\n", __func__,
		    jiffies_to_msecs(jiffies - probe_time));
}

static int dwc3_rtk_probe(struct platform_device *pdev)
{
	struct dwc3_rtk	*rtk;
//	struct clk		*clk;
	struct device		*dev = &pdev->dev;
	struct device_node	*node = dev->of_node;

	struct resource         *res;
	void __iomem            *regs;

	int			ret = -ENOMEM;
	unsigned long probe_time = jiffies;

	dev_info(&pdev->dev, "Probe Realtek-SoC USB DWC3 Host Controller\n");

	rtk = devm_kzalloc(dev, sizeof(*rtk), GFP_KERNEL);
	if (!rtk) {
		dev_err(dev, "not enough memory\n");
		goto err1;
	}

	/*
	 * Right now device-tree probed devices don't get dma_mask set.
	 * Since shared usb code relies on it, set it here for now.
	 * Once we move to full device tree support this will vanish off.
	 */
	if (!dev->dma_mask)
		dev->dma_mask = &dev->coherent_dma_mask;
	if (!dev->coherent_dma_mask)
		dev->coherent_dma_mask = DMA_BIT_MASK(32);

	platform_set_drvdata(pdev, rtk);

	ret = dwc3_rtk_register_phys(rtk);
	if (ret) {
		dev_err(dev, "couldn't register PHYs\n");
		goto err1;
	}

	rtk->dev	= dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "missing memory resource\n");
		return -ENODEV;
	}

	regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(regs)) {
		ret = PTR_ERR(regs);
		goto err1;
	}

	rtk->regs = regs;
	rtk->regs_size = resource_size(res);

	if (node) {
		if (of_property_read_bool(node, "delay_probe_work")) {
			INIT_WORK(&rtk->work, dwc3_rtk_probe_work);
			if (of_property_read_bool(node, "ordered_probe"))
				rtk_usb_manager_schedule_work(dev, &rtk->work);
			else
				schedule_work(&rtk->work);
		} else {
			ret = dwc3_rtk_probe_dwc3core(rtk);
			if (ret) {
				dev_err(dev, "%s failed to add dwc3 core\n", __func__);
				goto err2;
			}
		}
	} else {
		dev_err(dev, "no device node, failed to add dwc3 core\n");
		ret = -ENODEV;
		goto err2;
	}
	dev_info(dev, "dwc3_rtk_probe ok! (take %d ms)\n",
		    jiffies_to_msecs(jiffies - probe_time));

	return 0;

err2:
err1:
	return ret;
}

static int dwc3_rtk_remove(struct platform_device *pdev)
{
	struct dwc3_rtk	*rtk = platform_get_drvdata(pdev);

	of_platform_depopulate(rtk->dev);
	//device_for_each_child(&pdev->dev, NULL, dwc3_rtk_remove_child);
	platform_device_unregister(rtk->usb2_phy);
	platform_device_unregister(rtk->usb3_phy);

	clk_disable_unprepare(rtk->clk);

	return 0;
}

static void dwc3_rtk_shutdown(struct platform_device *pdev)
{
	struct dwc3_rtk	*rtk = platform_get_drvdata(pdev);
	struct device		*dev = &pdev->dev;

	dev_info(dev, "dwc3_rtk_shutdown start ...\n");

	of_platform_depopulate(rtk->dev);
	//device_for_each_child(&pdev->dev, NULL, dwc3_rtk_remove_child);
	platform_device_unregister(rtk->usb2_phy);
	platform_device_unregister(rtk->usb3_phy);

	clk_disable_unprepare(rtk->clk);
	dev_info(dev, "dwc3_rtk_shutdown ok!\n");
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id rtk_dwc3_match[] = {
	{ .compatible = "Realtek,dwc3" },
	{ .compatible = "Realtek,rtk119x-dwc3" },
	{ .compatible = "Realtek,rtd129x-dwc3-drd" },
	{ .compatible = "Realtek,rtd129x-dwc3-u2h" },
	{ .compatible = "Realtek,rtd129x-dwc3-u3h" },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_dwc3_match);
#endif

#ifdef CONFIG_PM_SLEEP
static int dwc3_rtk_suspend(struct device *dev)
{
	dev_info(dev, "[USB] Enter %s", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		goto out;
	}
	//For suspend mode
	dev_info(dev,  "[USB] %s Suspend mode\n", __func__);

out:
	dev_info(dev, "[USB] Exit %s", __func__);
	return 0;
}

static int dwc3_rtk_resume(struct device *dev)
{
	struct dwc3_rtk *rtk = dev_get_drvdata(dev);
	struct dwc3 *dwc = platform_get_drvdata(rtk->dwc);

	dev_info(dev, "[USB] Enter %s", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		goto out;
	}
	//For suspend mode
	dev_info(dev,  "[USB] %s Suspend mode\n", __func__);

	dwc3_rtk_init(rtk);

	dwc3_rtk_int_dr_mode(rtk, dwc->dr_mode);

	/* runtime set active to reflect active state. */
	pm_runtime_disable(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

out:
	dev_info(dev, "[USB] Exit %s", __func__);
	return 0;
}

static const struct dev_pm_ops dwc3_rtk_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_rtk_suspend, dwc3_rtk_resume)
};

#define DEV_PM_OPS	(&dwc3_rtk_dev_pm_ops)
#else
#define DEV_PM_OPS	NULL
#endif /* CONFIG_PM_SLEEP */

static struct platform_driver dwc3_rtk_driver = {
	.probe		= dwc3_rtk_probe,
	.remove		= dwc3_rtk_remove,
	.driver		= {
		.name	= "rtk-dwc3",
		.of_match_table = of_match_ptr(rtk_dwc3_match),
		.pm	= DEV_PM_OPS,
	},
	.shutdown 	= dwc3_rtk_shutdown,
};

module_platform_driver(dwc3_rtk_driver);

MODULE_ALIAS("platform:rtk-dwc3");
MODULE_LICENSE("GPL");
