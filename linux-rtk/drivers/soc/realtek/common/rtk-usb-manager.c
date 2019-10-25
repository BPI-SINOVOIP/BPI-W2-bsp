/*
 *  rtk-usb-manager.c RTK Manager Driver for All USB.
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
//#define DEBUG

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/usb.h>
#include <linux/usb/otg.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/reset.h>
#include <linux/clk.h>   // clk_get
#include <linux/clk-provider.h>
#include <linux/suspend.h>
#include <linux/regulator/consumer.h>
#include <soc/realtek/rtk_chip.h>
#include <soc/realtek/rtk_usb.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>

#define CRT_SOFT_RESET1 	0x0
#define CRT_SOFT_RESET2 	0x4
#define CRT_CLOCK_ENABLE1 	0xc

struct gpio_data {
	int gpio_num;

	int enable_port;
	int enable_port_mask; /* bit 0~3 mapping to port 0~3*/
	/*port GPIO*/
	/* port power on off */
	bool power_enable;
	bool power_low_active;

	struct device_node *node;
};

struct port_data {
	int port_num;

	struct gpio_data *power_gpio;

	/* port mapping to host */
	struct device_node *mac_node;
	struct device_node *slave_mac_node; /* for ohci */
	struct device_node *type_c_node;

	int enable;
	int enable_mask; /* bit 0: master; bit 1: slave */
	bool is_type_c;

	struct device_node *node;
};

struct manager_data {
	void __iomem *crt_base;
	struct device *dev;

	struct port_data port0;
	struct port_data port1;
	struct port_data port2;
	struct port_data port3;

	/* usb power gpio */
	struct gpio_data gpio0;
	struct gpio_data gpio1;
	struct gpio_data gpio2;
	struct gpio_data gpio3;

	bool disable_usb;

	bool usb_iso_mode;
	bool en_usb_storage_reprobe;
	bool rescue_usb;
	bool dis_hub_autosuspend;

	struct rtk_usb *rtk_usb;

	struct workqueue_struct *wq_usb_manager;

#ifdef CONFIG_DYNAMIC_DEBUG
	struct dentry *debug_dir;
#endif

	struct mutex lock;
};

/* [ROOT_CAUSE]: quirk device result in compatibility issue
 * [SOLUTION]: clear port power and reset port if got error
 * commit 42e905e60eaadd3fd8374db23dc644b98080717e
 */
extern int RTK_usb_probe_device(struct device *dev);
extern int RTK_usb_unbind_device(struct device *dev);

int RTK_usb_reprobe_usb_storage(struct usb_device *udev)
{
	struct device_node *node;
	struct platform_device *pdev = NULL;
	static struct manager_data *data = NULL;

	if (data == NULL) {
		node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL) {
			data = platform_get_drvdata(pdev);
		}
	}
	if (data == NULL) {
		pr_err("%s ERROR no manager_data", __func__);
		return -ENODEV;
	}

	/* [ROOT_CAUSE]: quirk device result in compatibility issue
	 * [SOLUTION]: clear port power and reset port if got error
	 * commit 42e905e60eaadd3fd8374db23dc644b98080717e
	 * [DEV_FIX]MediaNAS_V0.1 can't recognise the 5411 hub after power on
	 * [SOLUTION] dont unbind and probe again after usb_add_device , and set it as quirk device
	 * commit 75b83399dcf5e38ae39ce16d730f5824fccbb3bf
	 * [DEV_FIX]xhci hub 2.0  can't be recognize after unplug and plug again
	 * commit fbb4cc12d549b5193d51e88d6d0bc916a6e4d5d3
	 * [ROOT_CAUSE] USB hdd can't be mounted cuz scsi not stable during power-on stage
	 * commit dbb572028226bba6b504ff859fe3f05e5b7efbdf
	 * [ROOT_CAUSE] USB hdd can't be mounted cuz scsi not stable during power-on stage
	 * commit 8fa320af443950c0dbc9875546159d9c57cd97f2
	 * [ROOT_CAUSE]config USB device error ,result in NULL pointer
	 * commit 0d7ba5cbee8ff84a99f926a0a00128fe9c6c6104
	 * [ROOT_CAUSE] usb SATA not stable after power on
	 * commit ba77afca700fa8586607fcfa9091b863f4a3b620
	 * [ROOT_CAUSE] if se config err , udev->actconfig will be NULL
	 * commit 2ebede9fe6b6347ecf446a06e958dfd0a671b27d
	 */
	//hcy added for quirk HDD
	if (data->en_usb_storage_reprobe) {
		int usb_storage = 0;
		int i;

		if (udev->actconfig) {
			for (i = 0; i < 1/*udev->actconfig->desc.bNumInterfaces*/; i++) {
				struct usb_host_config *config = udev->actconfig;
				struct usb_interface *intf = config->interface[i];
				struct usb_interface_descriptor *desc;
				desc = &intf->cur_altsetting->desc;

				dev_info(&udev->dev , "bInterfaceClass = %d "
					    "(jiffies 0x%2x = %d ms)\n",  desc->bInterfaceClass,
					    jiffies - INITIAL_JIFFIES,
					    jiffies_to_msecs(jiffies - INITIAL_JIFFIES));
				if (desc->bInterfaceClass == USB_CLASS_MASS_STORAGE) {
					usb_storage = 1;
					break;
				}
			}
		}

		if ((jiffies - INITIAL_JIFFIES) < 0x400
			    && (usb_storage ||
			    udev->descriptor.bDeviceClass == USB_CLASS_MASS_STORAGE)) {
			msleep(100);
			dev_info(&udev->dev , "%s unbind-probe dev_name = %s "
				    "(jiffies= 0x%2x = %d ms)\n", __func__,
				    dev_name(&udev->dev), jiffies - INITIAL_JIFFIES,
				    jiffies_to_msecs(jiffies - INITIAL_JIFFIES));
			RTK_usb_unbind_device(&udev->dev);
			//hcy added for waiting some scsi HDD stable after power on
			if (data->rescue_usb) {
				dev_err(&udev->dev ,"** rescue type **\n");
				msleep(5000);
			} else {
				msleep(10000);
			}

			dev_info(&udev->dev , "%s bind-probe dev_name = %s "
				    "(jiffies= 0x%2x = %d ms)\n", __func__,
				    dev_name(&udev->dev), jiffies - INITIAL_JIFFIES,
				    jiffies_to_msecs(jiffies - INITIAL_JIFFIES));
			RTK_usb_probe_device(&udev->dev);
		}
	}
	return 0;
}

bool RTK_usb_disable_hub_autosuspend(void)
{
	struct device_node *node;
	struct platform_device *pdev = NULL;
	static struct manager_data *data = NULL;

	if (data == NULL) {
		node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL) {
			data = platform_get_drvdata(pdev);
		}
	}
	if (data == NULL) {
		pr_err("%s ERROR no manager_data", __func__);
		return false;
	}

	return data->dis_hub_autosuspend;
}

int rtk_usb_manager_is_iso_mode(struct device *usb_dev)
{
	static struct manager_data *s_data = NULL;
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;
	struct device *dev = NULL;

	if (s_data == NULL) {
		node = of_find_compatible_node(NULL, NULL, "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL)
			s_data = platform_get_drvdata(pdev);
	}
	data = s_data;
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}
	dev = data->dev;
	if (data->usb_iso_mode) {
		dev_dbg(data->dev, "%s is usb_iso_mode", __func__);
		return 1;
	} else {
		dev_dbg(data->dev, "%s Not usb_iso_mode", __func__);
		return 0;
	}
}

int rtk_usb_manager_schedule_work(struct device *usb_dev,
	    struct work_struct *work) {
	struct device_node *node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;

	if (node != NULL)
		pdev = of_find_device_by_node(node);
	if (pdev != NULL) {
		data = platform_get_drvdata(pdev);
	}
	if (data == NULL) {
		pr_err("%s ERROR no manager_data", __func__);
		return -ENODEV;
	}
    dev_dbg(data->dev, "%s Enter ..\n", __func__);

	dev_info(data->dev, "%s for %s", __func__, dev_name(usb_dev));

	if (work == NULL) {
		dev_err(data->dev, "%s, work is NULL", __func__);
		return -1;
	}
	mutex_lock(&data->lock);

	queue_work(data->wq_usb_manager, work);

	mutex_unlock(&data->lock);

    dev_dbg(data->dev, "%s Exit ..\n", __func__);
	return 0;
}

/* enable hw_pm (L4 ICG)
 *   The hw_pm function will be reset after doing soft_reset, so
 *   only enable is provided.
 */
static __maybe_unused void __rtk_usb_set_hw_pm_enable(struct manager_data *data)
{
	struct device *dev = data->dev;
	bool on = true;

	if (!data->rtk_usb)
		return;

	dev_dbg(dev, "set usb_hw_pm\n");

	/* for hw_pm, enable is equal to power_off */
	if (data->port0.port_num >= 0)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_0, on);
	if (data->port1.port_num >= 0)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_1, on);
	if (data->port2.port_num >= 0)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_2, on);
	if (data->port3.port_num >= 0)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_3, on);
}

/* set usb charger power */
static __maybe_unused void __usb_set_charger_power(
	    struct manager_data *data, bool power_on)
{
	struct device *dev = data->dev;
	unsigned int val = 0;

	if (!data->rtk_usb)
		return;

	if (power_on) {
		if (data->port0.port_num >= 0)
			val |= BIT(0);
		if (data->port1.port_num >= 0)
			val |= BIT(1);
		if (data->port2.port_num >= 0)
			val |= BIT(2);
		if (data->port3.port_num >= 0)
			val |= BIT(3);
	}

	dev_dbg(dev, "%s set usb_charger %x\n", __func__, val);

	rtk_usb_set_charger_power(data->rtk_usb, val);
}

/* set usb power domain */
static void __usb_set_pd_power(struct manager_data* data, bool power_on)
{
	struct device *dev = data->dev;

	if (power_on && !data->disable_usb) {
		if (!data->rtk_usb)
			return;
		rtk_usb_iso_power_ctrl(data->rtk_usb, true);
	} else {
		if (!data->rtk_usb)
			return;
		rtk_usb_iso_power_ctrl(data->rtk_usb, false);
	}
}

static inline struct reset_control *USB_reset_get(struct device *dev,
	    const char *str)
{
	struct reset_control *reset;

	reset = reset_control_get(dev, str);
	if (IS_ERR(reset)) {
		dev_dbg(dev, "No controller reset %s\n", str);
		reset = NULL;
	}
	return reset;
}

static inline void USB_reset_put(struct reset_control *reset)
{
	if (reset) {
		reset_control_put(reset);
	}
}

static inline int USB_reset_deassert(struct reset_control *reset)
{
	if (!reset) return 0;

	return reset_control_deassert(reset);
}

static inline int USB_reset_assert(struct reset_control *reset)
{
	if (!reset) return 0;

	return reset_control_assert(reset);
}

static inline struct clk *USB_clk_get(struct device *dev, const char *str)
{
	struct clk *clk;

	clk = clk_get(dev, str);
	if (IS_ERR(clk)) {
		dev_dbg(dev, "No clk %s\n", str);
		clk = NULL;
	}
	return clk;
}

static int __usb_init_clock_reset(struct manager_data* data)
{
	struct device *dev = data->dev;
	//void __iomem *crt_reg = data->crt_base;
	/* GET clock */
	struct clk *clk_usb_phy0_to_host = USB_clk_get(dev, "clk_en_phy0_to_host");
	struct clk *clk_usb_phy1_to_host = USB_clk_get(dev, "clk_en_phy1_to_host");
	struct clk *clk_usb_phy2_to_host = USB_clk_get(dev, "clk_en_phy2_to_host");
	struct clk *clk_usb_phy3_to_host = USB_clk_get(dev, "clk_en_phy3_to_host");
	struct clk *clk_usb = USB_clk_get(dev, "clk_en_usb");

	/* GET reset controller */
	struct reset_control *reset_u2phy0 = USB_reset_get(dev, "u2phy0");
	struct reset_control *reset_u2phy1 = USB_reset_get(dev, "u2phy1");
	struct reset_control *reset_u2phy2 = USB_reset_get(dev, "u2phy2");
	struct reset_control *reset_u2phy3 = USB_reset_get(dev, "u2phy3");

	struct reset_control *reset_u3phy0 = USB_reset_get(dev, "u3phy0");
	struct reset_control *reset_u3phy1 = USB_reset_get(dev, "u3phy1");
	struct reset_control *reset_u3phy0_mdio = USB_reset_get(dev, "u3mdio0");
	struct reset_control *reset_u3phy1_mdio = USB_reset_get(dev, "u3mdio1");

	struct reset_control *reset_usb_host0 = USB_reset_get(dev, "usb_host0");
	struct reset_control *reset_usb_host1 = USB_reset_get(dev, "usb_host1");
	struct reset_control *reset_usb_host2 = USB_reset_get(dev, "usb_host2");
	struct reset_control *reset_usb_host3 = USB_reset_get(dev, "usb_host3");
	struct reset_control *reset_usb = USB_reset_get(dev, "usb");
	struct reset_control *reset_type_c = USB_reset_get(dev, "type_c");

	struct reset_control *reset_usb_apply = USB_reset_get(dev, "apply");

	dev_dbg(dev, "Realtek USB init\n");

	USB_reset_assert(reset_u2phy0);
	USB_reset_assert(reset_u2phy1);
	USB_reset_assert(reset_u2phy2);
	USB_reset_assert(reset_u2phy3);
	USB_reset_assert(reset_u3phy0);
	USB_reset_assert(reset_u3phy1);
	USB_reset_assert(reset_u3phy0_mdio);
	USB_reset_assert(reset_u3phy1_mdio);
	USB_reset_assert(reset_usb_host0);
	USB_reset_assert(reset_usb_host1);
	USB_reset_assert(reset_usb_host2);
	USB_reset_assert(reset_usb_host3);
	USB_reset_assert(reset_usb);
	USB_reset_assert(reset_type_c);
	wmb();

	// Enable usb phy reset
	/* DEASSERT: set rstn bit to 1 */
	dev_dbg(dev, "Realtek USB init: Set phy reset to 1\n");
	USB_reset_deassert(reset_u2phy0);
	USB_reset_deassert(reset_u3phy0);
	USB_reset_deassert(reset_u2phy1);
	USB_reset_deassert(reset_u2phy2);
	USB_reset_deassert(reset_u2phy3);
	USB_reset_deassert(reset_u3phy1);

	USB_reset_deassert(reset_usb_apply);

	udelay(300);

	dev_dbg(dev, "Realtek USB init: Trigger usb clk\n");
	// Trigger USB clk (enable -> disable)
	clk_prepare_enable(clk_usb); // = clk_prepare + clk_enable
	clk_disable_unprepare(clk_usb); // = clk_disable + clk_unprepare

	dev_dbg(dev, "Realtek USB init: Set u3phy mdio reset to 1\n");
	// Enable USB reset
	USB_reset_deassert(reset_u3phy0_mdio);
	USB_reset_deassert(reset_u3phy1_mdio);

	USB_reset_deassert(reset_usb_apply);

	dev_dbg(dev, "Realtek USB init: Set usb reset to 1\n");
	USB_reset_deassert(reset_usb_host0);
	USB_reset_deassert(reset_usb_host1);
	USB_reset_deassert(reset_usb_host2);
	USB_reset_deassert(reset_usb_host3);
	USB_reset_deassert(reset_usb);
	USB_reset_deassert(reset_type_c);
	dev_dbg(dev, "Realtek USB init: enable usb clk\n");

	// Enable USB clk
	clk_prepare_enable(clk_usb); // = clk_prepare + clk_enable
	clk_prepare_enable(clk_usb_phy0_to_host); // = clk_prepare + clk_enable
	clk_prepare_enable(clk_usb_phy1_to_host); // = clk_prepare + clk_enable
	clk_prepare_enable(clk_usb_phy2_to_host); // = clk_prepare + clk_enable
	clk_prepare_enable(clk_usb_phy3_to_host); // = clk_prepare + clk_enable

	dev_info(dev, "Realtek USB init OK\n");

	clk_put(clk_usb);
	clk_put(clk_usb_phy0_to_host);
	clk_put(clk_usb_phy1_to_host);
	clk_put(clk_usb_phy2_to_host);
	clk_put(clk_usb_phy3_to_host);

	USB_reset_put(reset_u2phy0);
	USB_reset_put(reset_u2phy1);
	USB_reset_put(reset_u2phy2);
	USB_reset_put(reset_u2phy3);

	USB_reset_put(reset_u3phy0);
	USB_reset_put(reset_u3phy1);
	USB_reset_put(reset_u3phy0_mdio);
	USB_reset_put(reset_u3phy1_mdio);

	USB_reset_put(reset_usb_host0);
	USB_reset_put(reset_usb_host1);
	USB_reset_put(reset_usb_host2);
	USB_reset_put(reset_usb_host3);
	USB_reset_put(reset_usb);
	USB_reset_put(reset_type_c);

	USB_reset_put(reset_usb_apply);

	return 0;
}

static int __usb_clear_clock_reset(struct manager_data* data) {
	struct device *dev = data->dev;
	//void __iomem *crt_reg = data->crt_base;
	/* GET clock */
	struct clk *clk_usb_phy0_to_host = USB_clk_get(dev, "clk_en_phy0_to_host");
	struct clk *clk_usb_phy1_to_host = USB_clk_get(dev, "clk_en_phy1_to_host");
	struct clk *clk_usb_phy2_to_host = USB_clk_get(dev, "clk_en_phy2_to_host");
	struct clk *clk_usb_phy3_to_host = USB_clk_get(dev, "clk_en_phy3_to_host");
	struct clk *clk_usb = USB_clk_get(dev, "clk_en_usb");

	/* GET reset controller */
	struct reset_control *reset_u2phy0 = USB_reset_get(dev, "u2phy0");
	struct reset_control *reset_u2phy1 = USB_reset_get(dev, "u2phy1");
	struct reset_control *reset_u2phy2 = USB_reset_get(dev, "u2phy2");
	struct reset_control *reset_u2phy3 = USB_reset_get(dev, "u2phy3");

	struct reset_control *reset_u3phy0 = USB_reset_get(dev, "u3phy0");
	struct reset_control *reset_u3phy1 = USB_reset_get(dev, "u3phy1");
	struct reset_control *reset_u3phy0_mdio = USB_reset_get(dev, "u3mdio0");
	struct reset_control *reset_u3phy1_mdio = USB_reset_get(dev, "u3mdio1");

	struct reset_control *reset_usb_host0 = USB_reset_get(dev, "usb_host0");
	struct reset_control *reset_usb_host1 = USB_reset_get(dev, "usb_host1");
	struct reset_control *reset_usb_host2 = USB_reset_get(dev, "usb_host2");
	struct reset_control *reset_usb_host3 = USB_reset_get(dev, "usb_host3");
	struct reset_control *reset_usb = USB_reset_get(dev, "usb");
	struct reset_control *reset_type_c = USB_reset_get(dev, "type_c");

	struct reset_control *reset_usb_apply = USB_reset_get(dev, "apply");

	dev_dbg(dev, "Realtek USB clear clock and reset\n");

	USB_reset_assert(reset_u2phy0);
	USB_reset_assert(reset_u2phy1);
	USB_reset_assert(reset_u2phy2);
	USB_reset_assert(reset_u2phy3);
	USB_reset_assert(reset_u3phy0);
	USB_reset_assert(reset_u3phy1);
	USB_reset_assert(reset_u3phy0_mdio);
	USB_reset_assert(reset_u3phy1_mdio);
	USB_reset_assert(reset_usb_host0);
	USB_reset_assert(reset_usb_host1);
	USB_reset_assert(reset_usb_host2);
	USB_reset_assert(reset_usb_host3);
	USB_reset_assert(reset_usb);
	USB_reset_assert(reset_type_c);
	wmb();

	clk_disable_unprepare(clk_usb); // = clk_disable + clk_unprepare
	clk_disable_unprepare(clk_usb_phy0_to_host); // = clk_disable + clk_unprepare
	clk_disable_unprepare(clk_usb_phy1_to_host); // = clk_disable + clk_unprepare
	clk_disable_unprepare(clk_usb_phy2_to_host); // = clk_disable + clk_unprepare
	clk_disable_unprepare(clk_usb_phy3_to_host); // = clk_disable + clk_unprepare

	dev_info(dev, "Realtek USB clear clock and reset... OK\n");

	clk_put(clk_usb);
	clk_put(clk_usb_phy0_to_host);
	clk_put(clk_usb_phy1_to_host);
	clk_put(clk_usb_phy2_to_host);
	clk_put(clk_usb_phy3_to_host);

	USB_reset_put(reset_u2phy0);
	USB_reset_put(reset_u2phy1);
	USB_reset_put(reset_u2phy2);
	USB_reset_put(reset_u2phy3);

	USB_reset_put(reset_u3phy0);
	USB_reset_put(reset_u3phy1);
	USB_reset_put(reset_u3phy0_mdio);
	USB_reset_put(reset_u3phy1_mdio);

	USB_reset_put(reset_usb_host0);
	USB_reset_put(reset_usb_host1);
	USB_reset_put(reset_usb_host2);
	USB_reset_put(reset_usb_host3);
	USB_reset_put(reset_usb);
	USB_reset_put(reset_type_c);

	USB_reset_put(reset_usb_apply);

	return 0;
}

__attribute__((weak))
int rtk_type_c_init(struct rtk_usb *rtk_usb)
{
	pr_info("%s no implement by rtk_usb\n", __func__);
}

__attribute__((weak))
int rtk_type_c_plug_config(struct rtk_usb *rtk_usb, int dr_mode, int cc)
{
	pr_info("%s no implement by rtk_usb\n", __func__);
}

int rtk_usb_type_c_init(struct device *type_c_dev)
{
	static struct manager_data *s_data = NULL;
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;
	struct device *dev = NULL;

	if (s_data == NULL) {
		node = of_find_compatible_node(NULL, NULL, "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL)
			s_data = platform_get_drvdata(pdev);
	}
	data = s_data;
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}
	dev = data->dev;
	if (data->rtk_usb)
		rtk_type_c_init(data->rtk_usb);
	else
		dev_info(data->dev, "%s No rtk_usb data", __func__);

	return 0;
}

int rtk_usb_type_c_plug_config(struct device *type_c_dev,
	    int dr_mode, int cc)
{
	static struct manager_data *s_data = NULL;
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;
	struct device *dev = NULL;

	if (s_data == NULL) {
		node = of_find_compatible_node(NULL, NULL, "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL)
			s_data = platform_get_drvdata(pdev);
	}
	data = s_data;
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}
	dev = data->dev;
	if (data->rtk_usb)
		rtk_type_c_plug_config(data->rtk_usb, dr_mode, cc);
	else
		dev_info(data->dev, "%s No rtk_usb data", __func__);

	return 0;
}

static int __usb_port_power_on_off(struct device *dev,
	    struct port_data *port, bool on,
	    struct device_node *node);

int rtk_usb_type_c_power_on_off(struct device *type_c_dev, bool on) {
	static struct manager_data *s_data = NULL;
	struct device_node *node = NULL;
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;
	int ret;

	if (s_data == NULL) {
		node = of_find_compatible_node(NULL, NULL, "Realtek,usb-manager");
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL)
			s_data = platform_get_drvdata(pdev);
	}
	data = s_data;
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}

	dev_dbg(data->dev, "%s power %s for %s", __func__,
			on?"on":"off", dev_name(type_c_dev));

	mutex_lock(&data->lock);

	ret = __usb_port_power_on_off(data->dev, &data->port0, on,
		    type_c_dev->of_node);
	if (ret)
		ret = __usb_port_power_on_off(data->dev, &data->port1, on,
			    type_c_dev->of_node);
	if (ret)
		ret = __usb_port_power_on_off(data->dev, &data->port2, on,
			    type_c_dev->of_node);
	if (ret)
		ret = __usb_port_power_on_off(data->dev, &data->port3, on,
			    type_c_dev->of_node);

	mutex_unlock(&data->lock);

	return ret;
}

static int __gpio_on_off(struct device *dev, int port, struct gpio_data *gpio, bool on)
{
	int ret = 0;
	int gpio_num = gpio->gpio_num;
	int enable_port_mask = gpio->enable_port_mask;
	bool power_low_active = gpio->power_low_active;

	if (gpio->gpio_num < 0) {
		dev_dbg(dev, "%s No gpio config\n", __func__);
		return 0;
	}

	if (on) {
		gpio->enable_port |= BIT(port);
		if ((gpio->enable_port & enable_port_mask) != enable_port_mask) {
			dev_info(dev, "gpio_num=%d enable_port=0x%x enable_port_mask=0x%x "
				    " ==> No turn on\n",
				    gpio->gpio_num, gpio->enable_port, enable_port_mask);
			return -1;
		}
	} else {
		gpio->enable_port &= ~BIT(port);
		if (gpio->enable_port != 0) {
			dev_info(dev, "gpio_num=%d enable_port=0x%x enable_port_mask=0x%x "
				    " ==> No turn off\n",
				    gpio->gpio_num, gpio->enable_port, gpio->enable_port_mask);
			return -1;
		}
	}

	if (gpio_is_valid(gpio_num)) {
		if (gpio_request(gpio_num, "usb_power_gpio")) {   //request gpio
			dev_err(dev, "%s ERROR Request gpio_num (id=%d) fail\n",
				   __func__, gpio_num);
		} else {
			if (gpio_direction_output(gpio_num, power_low_active?!on:on)) {
				dev_err(dev, "%s ERROR set gpio fail\n", __func__);
				ret = -1;
			} else {
				dev_info(dev, "%s to set power%s %s by gpio (id=%d) OK\n",
					    __func__, power_low_active?" (power_low_active)":"",
					    on?"on":"off", gpio_num);
				gpio->power_enable = on;
			}
			gpio_free(gpio_num);
		}
	}
	return ret;
}

static int __usb_port_power_on_off(struct device *dev,
	    struct port_data *port, bool on,
	    struct device_node *node)
{
	struct device_node *usb_node;

	int enable_mask = port->enable_mask;

	if (port->is_type_c) {
		if (port->type_c_node && node &&
			    port->type_c_node->phandle == node->phandle) {
			dev_info(dev, "%s port%d is type_c\n",
			    __func__, port->port_num);
			usb_node = port->mac_node;
		} else {
			return -1;
		}
	} else {
		usb_node = node;
	}

	if (port->mac_node && usb_node &&
		    port->mac_node->phandle == usb_node->phandle) {
		if (on)
			port->enable |= BIT(0);
		else
			port->enable &= ~BIT(0);
	} else if (port->slave_mac_node && usb_node &&
		    port->slave_mac_node->phandle == usb_node->phandle) {
		if (on)
			port->enable |= BIT(1);
		else
			port->enable &= ~BIT(1);
	} else {
		dev_dbg(dev, "%s port%d is not match\n", __func__, port->port_num);
		return -1;
	}

	dev_info(dev, "%s port%d power=%s enable=0x%x enable_mask=0x%x\n",
		    __func__, port->port_num, on?"on":"off",
		    port->enable, port->enable_mask);
	if (((port->enable & enable_mask) == enable_mask) ||
		    (!port->enable && !on)) {
		if (port->power_gpio)
			__gpio_on_off(dev, port->port_num, port->power_gpio, on);
		else
			dev_info(dev, "%s port%d no gpio\n", __func__, port->port_num);
	}
	return 0;
}

static int __usb_port_suspend(struct manager_data *data) {
	struct device *dev = data->dev;
	bool is_suspend = true;

	if (!data->rtk_usb)
		return;

	dev_info(dev, "%s", __func__);
	if (data->port0.port_num >= 0) {
		dev_dbg(dev, "set port 0 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_0, is_suspend);
	}
	if (data->port1.port_num >= 0) {
		dev_dbg(dev, "set port 1 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_1, is_suspend);
	}
	if (data->port2.port_num >= 0) {
		dev_dbg(dev, "set port 2 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_2, is_suspend);
	}
	if (data->port3.port_num >= 0) {
		dev_dbg(dev, "set port 3 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_3, is_suspend);
	}
	return 0;
}

static int __usb_port_resume(struct manager_data *data) {
	struct device *dev = data->dev;
	//void __iomem *reg_u3_port;
	//void __iomem *reg_u2_port;
	bool is_suspend = false;

	if (!data->rtk_usb)
		return;

	dev_info(dev, "%s", __func__);
	if (data->port0.port_num >= 0) {
		dev_dbg(dev, "set port 0 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_0, is_suspend);
	}
	if (data->port1.port_num >= 0) {
		dev_dbg(dev, "set port 1 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_1, is_suspend);
	}
	if (data->port2.port_num >= 0) {
		dev_dbg(dev, "set port 2 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_2, is_suspend);
	}
	if (data->port3.port_num >= 0) {
		dev_dbg(dev, "set port 3 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_3, is_suspend);
	}
	return 0;
}

static int __usb_port_gpio_off(struct manager_data *data)
{
	struct device *dev = data->dev;
	struct device_node *usb_node;
	bool off = false;

	dev_info(dev, "%s", __func__);
	mutex_lock(&data->lock);

	usb_node = data->port0.mac_node;
	__usb_port_power_on_off(data->dev, &data->port0, off, usb_node);
	usb_node = data->port0.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port0, off, usb_node);

	usb_node = data->port1.mac_node;
	__usb_port_power_on_off(data->dev, &data->port1, off, usb_node);
	usb_node = data->port1.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port1, off, usb_node);

	usb_node = data->port2.mac_node;
	__usb_port_power_on_off(data->dev, &data->port2, off, usb_node);
	usb_node = data->port2.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port2, off, usb_node);

	usb_node = data->port3.mac_node;
	__usb_port_power_on_off(data->dev, &data->port3, off, usb_node);
	usb_node = data->port3.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port3, off, usb_node);

	mutex_unlock(&data->lock);

	return 0;
}

static int __usb_port_gpio_on(struct manager_data *data) {
	struct device *dev = data->dev;
	struct device_node *usb_node;
	bool on = true;

	dev_info(dev, "%s", __func__);

	mutex_lock(&data->lock);

	usb_node = data->port0.mac_node;
	__usb_port_power_on_off(data->dev, &data->port0, on, usb_node);
	usb_node = data->port0.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port0, on, usb_node);

	usb_node = data->port1.mac_node;
	__usb_port_power_on_off(data->dev, &data->port1, on, usb_node);
	usb_node = data->port1.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port1, on, usb_node);

	usb_node = data->port2.mac_node;
	__usb_port_power_on_off(data->dev, &data->port2, on, usb_node);
	usb_node = data->port2.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port2, on, usb_node);

	usb_node = data->port3.mac_node;
	__usb_port_power_on_off(data->dev, &data->port3, on, usb_node);
	usb_node = data->port3.slave_mac_node;
	__usb_port_power_on_off(data->dev, &data->port3, on, usb_node);

	mutex_unlock(&data->lock);

	return 0;
}

int rtk_usb_init_port_power_on(struct device *usb_dev)
{
	struct device_node *usb_node = usb_dev->of_node;
	struct device_node *node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
	struct platform_device *pdev = NULL;
	static struct manager_data *data = NULL;
	bool on = true;

	if (data == NULL) {
		if (node != NULL)
			pdev = of_find_device_by_node(node);
		if (pdev != NULL) {
			data = platform_get_drvdata(pdev);
		}
	}
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}

	dev_info(data->dev, "%s for %s", __func__, dev_name(usb_dev));
	mutex_lock(&data->lock);

	__usb_port_power_on_off(data->dev, &data->port0, on, usb_node);
	__usb_port_power_on_off(data->dev, &data->port1, on, usb_node);
	__usb_port_power_on_off(data->dev, &data->port2, on, usb_node);
	__usb_port_power_on_off(data->dev, &data->port3, on, usb_node);

	mutex_unlock(&data->lock);
	return 0;
}

static void __usb_gpio_init(struct device *dev, struct gpio_data *gpio)
{
	bool off = false;

	gpio->enable_port = 0;
	__gpio_on_off(dev, -1, gpio, off);

}
static int rtk_usb_gpio_init(struct manager_data *data)
{
	__usb_gpio_init(data->dev, &data->gpio0);
	__usb_gpio_init(data->dev, &data->gpio1);
	__usb_gpio_init(data->dev, &data->gpio2);
	__usb_gpio_init(data->dev, &data->gpio3);

	return 0;
}

static int rtk_usb_manager_init(struct manager_data *data) {
	struct device *dev = data->dev;

	dev_dbg(dev, "Realtek USB init ....\n");

	__usb_set_pd_power(data, 1);

	if (data->disable_usb) {
		dev_err(dev, "Realtek USB No any usb be enabled ....\n");
		return 0;
	}

	__usb_init_clock_reset(data);

	rtk_usb_gpio_init(data);

	__rtk_usb_set_hw_pm_enable(data);

	dev_dbg(dev, "Realtek USB init Done\n");

	return 0;
}

#ifdef CONFIG_DYNAMIC_DEBUG
static int rtk_port0_power_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "To Control Port 0\n");
	seq_printf(s, "echo \"on\" > port0_power\n");
	seq_printf(s, "echo \"off\" > port0_power\n");
	seq_printf(s, "\n");
	if (data->port0.power_gpio) {
		struct gpio_data *gpio = data->port0.power_gpio;

		seq_printf(s, "Now port0 %s\n", gpio->power_enable?"on":"off");
	} else {
		seq_printf(s, "port0 No control gpio\n");
	}

	return 0;
}

static int rtk_port0_power_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_port0_power_show, inode->i_private);
}

static ssize_t rtk_port0_power_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40];
	char *buf = buffer;
	struct device_node *usb_node;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		usb_node = data->port0.mac_node;
		__usb_port_power_on_off(data->dev, &data->port0, true, usb_node);
		usb_node = data->port0.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port0, true, usb_node);
	} else if (!strncmp(buf, "off", 3)) {
		usb_node = data->port0.mac_node;
		__usb_port_power_on_off(data->dev, &data->port0, false, usb_node);
		usb_node = data->port0.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port0, false, usb_node);
	} else
		dev_err(data->dev, "UNKNOWN input (%s)", buf);

	mutex_unlock(&data->lock);
	return count;
}

static const struct file_operations rtk_port0_power_fops = {
	.open			= rtk_port0_power_open,
	.write			= rtk_port0_power_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_port1_power_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "To Control Port 1 (DWC3 u2host power)\n");
	seq_printf(s, "echo \"on\" > port1_power\n");
	seq_printf(s, "echo \"off\" > port1_power\n");
	seq_printf(s, "\n");
	if (data->port1.power_gpio) {
		struct gpio_data *gpio = data->port1.power_gpio;

		seq_printf(s, "Now port1 %s\n", gpio->power_enable?"on":"off");
	} else {
		seq_printf(s, "port1 No control gpio\n");
	}
	return 0;
}

static int rtk_port1_power_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_port1_power_show, inode->i_private);
}

static ssize_t rtk_port1_power_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40];
	char *buf = buffer;
	struct device_node *usb_node;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		usb_node = data->port1.mac_node;
		__usb_port_power_on_off(data->dev, &data->port1, true, usb_node);
		usb_node = data->port1.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port1, true, usb_node);
	} else if (!strncmp(buf, "off", 3)) {
		usb_node = data->port1.mac_node;
		__usb_port_power_on_off(data->dev, &data->port1, false, usb_node);
		usb_node = data->port1.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port1, false, usb_node);
	} else
		dev_err(data->dev, "UNKNOWN input (%s)", buf);

	mutex_unlock(&data->lock);
	return count;
}

static const struct file_operations rtk_port1_power_fops = {
	.open			= rtk_port1_power_open,
	.write			= rtk_port1_power_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_port2_power_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "To Control Port 2 (EHCI/OHCI power)\n");
	seq_printf(s, "echo \"on\" > port2_power\n");
	seq_printf(s, "echo \"off\" > port2_power\n");
	seq_printf(s, "\n");
	if (data->port2.power_gpio) {
		struct gpio_data *gpio = data->port2.power_gpio;

		seq_printf(s, "Now port2 %s\n", gpio->power_enable?"on":"off");
	} else {
		seq_printf(s, "port2 No control gpio\n");
	}
	return 0;
}

static int rtk_port2_power_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_port2_power_show, inode->i_private);
}

static ssize_t rtk_port2_power_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40];
	char *buf = buffer;
	struct device_node *usb_node;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		usb_node = data->port2.mac_node;
		__usb_port_power_on_off(data->dev, &data->port2, true, usb_node);
		usb_node = data->port2.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port2, true, usb_node);

	} else if (!strncmp(buf, "off", 3)) {
		usb_node = data->port2.mac_node;
		__usb_port_power_on_off(data->dev, &data->port2, false, usb_node);
		usb_node = data->port2.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port2, false, usb_node);
	} else
		dev_err(data->dev, "UNKNOWN input (%s)", buf);

	mutex_unlock(&data->lock);
	return count;
}

static const struct file_operations rtk_port2_power_fops = {
	.open			= rtk_port2_power_open,
	.write			= rtk_port2_power_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_port3_power_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "To Control Port 3 (DWC3 u3host power)\n");
	seq_printf(s, "echo \"on\" > port3_power\n");
	seq_printf(s, "echo \"off\" > port3_power\n");
	seq_printf(s, "\n");
	if (data->port3.power_gpio) {
		struct gpio_data *gpio = data->port3.power_gpio;

		seq_printf(s, "Now port3 %s\n", gpio->power_enable?"on":"off");
	} else {
		seq_printf(s, "port3 No control gpio\n");
	}
	return 0;
}

static int rtk_port3_power_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_port3_power_show, inode->i_private);
}

static ssize_t rtk_port3_power_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40];
	char *buf = buffer;
	struct device_node *usb_node;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		usb_node = data->port3.mac_node;
		__usb_port_power_on_off(data->dev, &data->port3, true, usb_node);
		usb_node = data->port3.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port3, true, usb_node);
	} else if (!strncmp(buf, "off", 3)) {
		usb_node = data->port3.mac_node;
		__usb_port_power_on_off(data->dev, &data->port3, false, usb_node);
		usb_node = data->port3.slave_mac_node;
		__usb_port_power_on_off(data->dev, &data->port3, false, usb_node);
	} else
		dev_err(data->dev, "UNKNOWN input (%s)", buf);

	mutex_unlock(&data->lock);
	return count;
}

static const struct file_operations rtk_port3_power_fops = {
	.open			= rtk_port3_power_open,
	.write			= rtk_port3_power_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_iso_mode_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	mutex_lock(&data->lock);

	seq_printf(s, "usb_iso_mode %s\n", data->usb_iso_mode?"Enable":"Disable");

	mutex_unlock(&data->lock);

	return 0;
}

static int rtk_iso_mode_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_iso_mode_show, inode->i_private);
}

static ssize_t rtk_iso_mode_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40];
	char *buf = buffer;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "enable", 6)) {
		data->usb_iso_mode = true;
	} else if (!strncmp(buf, "disable", 7)) {
		data->usb_iso_mode = false;
	} else
		dev_err(data->dev, "UNKNOWN input (%s)", buf);

	mutex_unlock(&data->lock);
	return count;
}

static const struct file_operations rtk_iso_mode_fops = {
	.open			= rtk_iso_mode_open,
	.write			= rtk_iso_mode_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static void __debug_dump_gpio_info(struct seq_file *s, struct gpio_data *gpio)
{
	if (!gpio)
		return;

	seq_printf(s, "    gpio info:\n");
	if (gpio->gpio_num < 0) {
		seq_printf(s, "        No gpio\n");
		return;
	}
	seq_printf(s, "       gpio_num=%d\n", gpio->gpio_num);
	seq_printf(s, "       enable_port=0x%x enable_port_mask=0x%x\n",
		    gpio->enable_port, gpio->enable_port_mask);
	seq_printf(s, "       power %s%s\n",
		    gpio->power_enable?"enable":"disable",
		    gpio->power_low_active?" (power_low_active)":"");
}

static void __debug_dump_port_info(struct seq_file *s, struct port_data *port)
{
	if (port->port_num < 0)
		return 0;

	seq_printf(s, "port%d info:\n", port->port_num);
	seq_printf(s, "    port_num=%d\n", port->port_num);
	seq_printf(s, "    power_gpio@%p\n", port->power_gpio);
	__debug_dump_gpio_info(s, port->power_gpio);
	seq_printf(s, "    mac_node=%s\n",
		    port->mac_node?port->mac_node->name:"NULL");
	seq_printf(s, "    slave_mac_node=%s\n",
		    port->slave_mac_node?port->slave_mac_node->name:"NULL");
	seq_printf(s, "    type_c=%s\n",
		    port->type_c_node?port->type_c_node->name:"NULL");
	seq_printf(s, "    enable=0x%x (enable_mask=0x%x)\n",
		    port->enable, port->enable_mask);
	seq_printf(s, "    is%s type_c port\n", port->is_type_c?"":" not");
}

static int rtk_usb_debug_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "rtk usb manager info:\n");
	__debug_dump_port_info(s, &data->port0);
	__debug_dump_port_info(s, &data->port1);
	__debug_dump_port_info(s, &data->port2);
	__debug_dump_port_info(s, &data->port3);

	return 0;
}

static int rtk_usb_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb_debug_show, inode->i_private);
}

static const struct file_operations rtk_usb_debug_fops = {
	.open			= rtk_usb_debug_open,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static inline void create_debug_files(struct manager_data *data) {

	dev_err(data->dev, "%s", __func__);

	data->debug_dir = debugfs_create_dir("usb_manager", usb_debug_root);
	if (!data->debug_dir) {
		dev_err(data->dev, "%s Error debug_dir is NULL", __func__);
		return;
	}

	if (data->port0.port_num >= 0
			&& !debugfs_create_file("port0_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port0_power_fops))
		goto file_error;

	if (data->port1.port_num >= 0
			&& !debugfs_create_file("port1_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port1_power_fops))
		goto file_error;

	if (data->port2.port_num >= 0
			&& !debugfs_create_file("port2_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port2_power_fops))
		goto file_error;

	if (data->port3.port_num >= 0
			&& !debugfs_create_file("port3_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port3_power_fops))
		goto file_error;

	if (!debugfs_create_file("usb_iso_mode", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_iso_mode_fops))
		goto file_error;

	if (!debugfs_create_file("debug", S_IRUGO, data->debug_dir, data,
						&rtk_usb_debug_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(data->debug_dir);
}
#endif //CONFIG_DYNAMIC_DEBUG

static inline int __of_parse_gpio_setting(struct manager_data *data,
	    struct gpio_data *gpio,
	    struct device_node *sub_node)
{
	int gpio_num;

	if (!sub_node) {
		gpio->gpio_num = -1;
		return -1;
	}

	gpio->node = sub_node;

	gpio_num = of_get_named_gpio(sub_node, "realtek,power-gpio", 0);
	if (gpio_is_valid(gpio_num)) {
		gpio->gpio_num = gpio_num;
 	} else {
		gpio->gpio_num = -1;
		dev_info(data->dev, "%s power-gpio no found\n", __func__);
		return -1;
	}

	if (of_property_read_bool(sub_node, "power_low_active")) {
		gpio->power_low_active = true;
	} else {
		gpio->power_low_active = false;
	}

	return 0;
}

static int parse_gpio_setting(struct manager_data *data,
	    struct device_node *node)
{
	struct device *dev = data->dev;
	struct device_node	*sub_node;

	sub_node = of_get_child_by_name(node, "gpio0");

	if (__of_parse_gpio_setting(data, &data->gpio0, sub_node)) {
		dev_dbg(dev, "node gpio0 no found in dts\n");
	} else {
		dev_info(dev, "%s get power-gpio (id=%d) OK\n",
			    __func__, data->gpio0.gpio_num);
	}

	sub_node = of_get_child_by_name(node, "gpio1");
	if (__of_parse_gpio_setting(data, &data->gpio1, sub_node)) {
		dev_dbg(dev, "node gpio1 no found in dts\n");
	} else {
		dev_info(dev, "%s get power-gpio (id=%d) OK\n",
			    __func__, data->gpio1.gpio_num);
	}

	sub_node = of_get_child_by_name(node, "gpio2");
	if (__of_parse_gpio_setting(data, &data->gpio2, sub_node)) {
		dev_dbg(dev, "node gpio2 no found in dts\n");
	} else {
		dev_info(dev, "%s get power-gpio (id=%d) OK\n",
			    __func__, data->gpio2.gpio_num);
	}

	sub_node = of_get_child_by_name(node, "gpio3");
	if (__of_parse_gpio_setting(data, &data->gpio3, sub_node)) {
		dev_dbg(dev, "node gpio3 no found in dts\n");
	} else {
		dev_info(dev, "%s get power-gpio (id=%d) OK\n", __func__,
			    __func__, data->gpio3.gpio_num);
	}

	return 0;
}

static inline struct gpio_data *__of_parse_port_gpio_mapping(
	    struct manager_data *data,
	    struct device_node *port_node, int port_num)
{
	struct device_node *gpio_node;
	struct gpio_data *gpio;

	gpio_node = of_parse_phandle(port_node, "gpio", 0);

	gpio = &data->gpio0;
	if (gpio->gpio_num >= 0 &&
		    gpio->node &&  gpio_node &&
		    gpio->node->phandle == gpio_node->phandle) {
		gpio->enable_port_mask |= BIT(port_num);
		dev_info(data->dev, "%s port%d mapping gpio_num=%d\n",
			    __func__, port_num, gpio->gpio_num);
		return gpio;
	}

	gpio = &data->gpio1;
	if (gpio->gpio_num >= 0 &&
		    gpio->node &&  gpio_node &&
		    gpio->node->phandle == gpio_node->phandle) {
		gpio->enable_port_mask |= BIT(port_num);
		dev_info(data->dev, "%s port%d mapping gpio_num=%d\n",
			    __func__, port_num, gpio->gpio_num);
		return gpio;
	}

	gpio = &data->gpio2;
	if (gpio->gpio_num >= 0 &&
		    gpio->node &&  gpio_node &&
		    gpio->node->phandle == gpio_node->phandle) {
		gpio->enable_port_mask |= BIT(port_num);
		dev_info(data->dev, "%s port%d mapping gpio_num=%d\n",
			    __func__, port_num, gpio->gpio_num);
		return gpio;
	}

	gpio = &data->gpio3;
	if (gpio->gpio_num >= 0 &&
		    gpio->node &&  gpio_node &&
		    gpio->node->phandle == gpio_node->phandle) {
		gpio->enable_port_mask |= BIT(port_num);
		dev_info(data->dev, "%s port%d mapping gpio_num=%d\n",
			    __func__, port_num, gpio->gpio_num);
		return gpio;
	}

	dev_info(data->dev, "%s port%d No mapping GPIO\n", __func__, port_num);
	return NULL;
}

static inline void __of_parse_port_setting(struct manager_data *data,
	    struct port_data *port,
	    struct device_node *port_node, int port_num)
{
	if (!port_node) {
		port->port_num = -1;
		return;
	}
	port->port_num = port_num;

	port->mac_node = of_parse_phandle(port_node, "usb", 0);
	port->slave_mac_node = of_parse_phandle(port_node, "usb", 1);
	port->type_c_node = of_parse_phandle(port_node, "type_c", 0);

	port->enable = 0;
	port->enable_mask = 0;
	port->is_type_c = false;

	if (port->mac_node &&
		    of_device_is_available(port->mac_node)) {
		pr_info("mac_node: %s status is okay\n",
			    port->mac_node->name);
		port->enable_mask |= BIT(0);
	}
	if (port->slave_mac_node &&
		    of_device_is_available(port->slave_mac_node)) {
		pr_info("slave_mac_node: %s status is okay\n",
			    port->slave_mac_node->name);
		port->enable_mask |= BIT(1);
	}
	if (port->type_c_node &&
		    of_device_is_available(port->type_c_node)) {
		pr_info("type_c_node: %s status is okay\n",
			    port->type_c_node->name);
		port->is_type_c = true;
	}

	if (port->enable_mask)
		port->power_gpio = __of_parse_port_gpio_mapping(data,
			    port_node, port->port_num);

	port->node = port_node;
}

static int parse_port_setting(struct manager_data *data,
	    struct device_node *node)
{
	struct device_node	*sub_node;
	struct port_data *port;

	data->disable_usb = true;

	sub_node = of_get_child_by_name(node, "port0");
	__of_parse_port_setting(data, &data->port0, sub_node, 0);
	sub_node = of_get_child_by_name(node, "port1");
	__of_parse_port_setting(data, &data->port1, sub_node, 1);
	sub_node = of_get_child_by_name(node, "port2");
	__of_parse_port_setting(data, &data->port2, sub_node, 2);
	sub_node = of_get_child_by_name(node, "port3");
	__of_parse_port_setting(data, &data->port3, sub_node, 3);

	if (data->port0.port_num >= 0 || data->port1.port_num >= 0 ||
		    data->port2.port_num >= 0 || data->port3.port_num >= 0) {
		data->disable_usb = false;
	}

	return 0;
}

static int rtk_usb_manager_probe(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct device_node	*node = dev->of_node;
	struct device_node	*sub_node;
	struct device_node	*np;
	struct manager_data 	*data;
	unsigned int gpio;
	int ret = 0;
	unsigned long probe_time = jiffies;

	dev_info(dev, "ENTER %s", __func__);
	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->crt_base = of_iomap(pdev->dev.of_node, 0);
	if (data->crt_base == NULL) {
		dev_err(&pdev->dev, "error mapping memory for crt_base\n");
		ret = -EFAULT;
		goto err1;
	}
	data->dev = dev;

	if (node && of_device_is_available(node)) {
		if (of_property_read_bool(node, "usb_iso_mode"))
			data->usb_iso_mode = true;
		else
			data->usb_iso_mode = false;

		if (of_property_read_bool(node, "en_usb_storage_reprobe"))
			data->en_usb_storage_reprobe = true;
		else
			data->en_usb_storage_reprobe = false;

		if (of_property_read_bool(node, "rescue_usb"))
			data->rescue_usb = true;
		else
			data->rescue_usb = false;

		if (of_property_read_bool(node, "dis_hub_autosuspend"))
			data->dis_hub_autosuspend = true;
		else
			data->dis_hub_autosuspend = false;
	}

	if (node && of_device_is_available(node)) {

		ret = parse_gpio_setting(data, node);

		ret = parse_port_setting(data, node);

		sub_node = of_get_child_by_name(node, "rtk_usb");
		if (sub_node) {
			data->rtk_usb = rtk_usb_soc_init(sub_node);
		} else {
			data->rtk_usb = NULL;
		}
	}

	mutex_init(&data->lock);

	rtk_usb_manager_init(data);

	platform_set_drvdata(pdev, data);

	data->wq_usb_manager = create_singlethread_workqueue("rtk_usb_manager");

#ifdef CONFIG_DYNAMIC_DEBUG
	create_debug_files(data);
#endif

	dev_info(&pdev->dev, "%s OK (take %d ms)\n", __func__,
		    jiffies_to_msecs(jiffies - probe_time));
	return 0;

err1:
	dev_err(&pdev->dev, "%s: Probe fail, %d\n", __func__, ret);

	return ret;
}

static int rtk_usb_manager_remove(struct platform_device *pdev) {
	dev_info(&pdev->dev, "%s\n", __func__);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id rtk_usb_manager_match[] = {
	{ .compatible = "Realtek,usb-manager" },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_usb_manager_match);
#endif

#ifdef CONFIG_PM_SLEEP

static int rtk_usb_manager_prepare(struct device *dev) {
	struct manager_data *data = dev_get_drvdata(dev);
	int ret = 0;

	dev_info(dev, "[USB] Enter %s\n", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
	} else {
		dev_info(dev,  "[USB] %s Suspend mode\n", __func__);
	}
	dev_info(dev, "[USB] Exit %s\n", __func__);
	return ret;
}

static void rtk_usb_manager_complete(struct device *dev) {
	struct manager_data *data = dev_get_drvdata(dev);

	dev_info(dev, "[USB] Enter %s\n", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		dev_info(dev, "[USB] %s S1 (Standby mode)\n", __func__);
	} else {
		dev_info(dev, "[USB] %s S3 (Suspend-to-RAM mode)\n", __func__);
	}
	dev_info(dev, "[USB] Exit %s\n", __func__);
}

static int rtk_usb_manager_suspend(struct device *dev) {
	struct manager_data *data = dev_get_drvdata(dev);

	dev_info(dev, "[USB] Enter %s\n", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		dev_info(dev, "[USB] %s S1 (Standby mode)\n", __func__);
	} else {
		//For suspend mode
		dev_info(dev, "[USB] %s S3 (Suspend-to-RAM mode) %susb_iso_mode\n",
			    __func__, data->usb_iso_mode?"":"NOT ");
		if (!data->usb_iso_mode) {
			__usb_port_gpio_off(data);
			__usb_set_pd_power(data, 0);
		} else {
			__usb_port_suspend(data);
		}

	}
	dev_info(dev, "[USB] Exit %s\n", __func__);
	return 0;
}

static int rtk_usb_manager_resume(struct device *dev) {
	struct manager_data *data = dev_get_drvdata(dev);
	struct clk *clk_usb = USB_clk_get(NULL, "clk_en_usb");

	dev_info(dev, "[USB] Enter %s\n", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		dev_info(dev, "[USB] %s S1 (Standby mode)\n", __func__);
	} else {
		//For suspend mode
		dev_info(dev, "[USB] %s S3 (Suspend-to-RAM mode) %susb_iso_mode\n",
			    __func__, data->usb_iso_mode?"":"NOT ");

		if (!data->usb_iso_mode) {
			__usb_set_pd_power(data, 1);

			clk_disable_unprepare(clk_usb); // = clk_disable + clk_unprepare
			__usb_init_clock_reset(data);

			__rtk_usb_set_hw_pm_enable(data);

		} else {
			__usb_port_resume(data);
		}
		__usb_port_gpio_on(data);
	}
	dev_info(dev, "[USB] Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_usb_manager_pm_ops = {
	.prepare = rtk_usb_manager_prepare,
	.complete = rtk_usb_manager_complete,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(rtk_usb_manager_suspend, rtk_usb_manager_resume)
};

#define DEV_PM_OPS	(&rtk_usb_manager_pm_ops)
#else
#define DEV_PM_OPS	NULL
#endif /* CONFIG_PM_SLEEP */

static void rtk_usb_manager_shutdown(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct manager_data *data = dev_get_drvdata(dev);

	dev_info(dev, "[USB] Enter %s S5 (shutdown)\n",
		    __func__);

	rtk_usb_gpio_init(data);
	__usb_set_pd_power(data, 0);
	__usb_clear_clock_reset(data);

	dev_info(dev, "[USB] Exit %s\n", __func__);
	return 0;
}

static struct platform_driver rtk_usb_manager_driver = {
	.probe		= rtk_usb_manager_probe,
	.remove		= rtk_usb_manager_remove,
	.driver		= {
		.name	= "rtk-usb-manager",
		.of_match_table = of_match_ptr(rtk_usb_manager_match),
		.pm = DEV_PM_OPS,
	},
	.shutdown = rtk_usb_manager_shutdown,
};

static int __init rtk_usb_manager_driver_init(void) {
	return platform_driver_register(&(rtk_usb_manager_driver));
}
subsys_initcall(rtk_usb_manager_driver_init);

static void __exit rtk_usb_manager_driver_exit(void) {
	platform_driver_unregister(&(rtk_usb_manager_driver));
}

MODULE_ALIAS("platform:rtk-usb-manager");
MODULE_LICENSE("GPL");
