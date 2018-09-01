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
#include <linux/reset-helper.h> // rstc_get
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

struct manager_data {
	void __iomem *crt_base;
	struct device *dev;

	/* port enable/disable */
	int port0;
	int port1;
	int port2;
	int port3;
	/* port mapping to host */
	struct device_node *port0_host_node;
	struct device_node *port1_host_node;
	struct device_node *port2_host_node;
	struct device_node *port2_ohci_node;
	struct device_node *port3_host_node;

	struct device_node *type_c_node;

	bool disable_usb;

	/*port GPIO*/
	unsigned int port0_pow_gpio;
	unsigned int port1_pow_gpio;
	unsigned int port2_pow_gpio;
	unsigned int port3_pow_gpio;
	unsigned int port0_switch_ctrl_gpio;
	/* port power on off */
	bool port0_power_low_active;
	bool port1_power_low_active;
	bool port2_power_low_active;
	bool port3_power_low_active;
	bool port0_pow_enable;
	bool port1_pow_enable;
	bool port2_pow_enable;
	bool port3_pow_enable;

	bool usb_iso_mode;
	bool en_usb_storage_reprobe;
	bool rescue_usb;

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
	if (data->port0)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_0, on);
	if (data->port1)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_1, on);
	if (data->port2)
		rtk_usb_set_hw_l4icg_on_off(data->rtk_usb, USB_PORT_2, on);
	if (data->port3)
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
		val |= data->port0 << 0;
		val |= data->port1 << 1;
		val |= data->port2 << 2;
		val |= data->port3 << 3;
	}

	dev_dbg(dev, "%s set usb_charger %x\n", __func__, val);

	rtk_usb_set_charger_power(data->rtk_usb, val);
}

/* set usb power domain */
static void __usb_set_pd_power(struct manager_data* data, bool power_on)
{
	struct device *dev = data->dev;

	if (power_on &&
		    (data->port0 || data->port1 || data->port2 || data->port3)) {
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

	mdelay(2);

	dev_dbg(dev, "Realtek USB init: Trigger usb clk\n");
	// Trigger USB clk (enable -> disable)
	clk_prepare_enable(clk_usb); // = clk_prepare + clk_enable
	clk_disable_unprepare(clk_usb); // = clk_disable + clk_unprepare
	mdelay(1);

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
	mdelay(1);
	dev_dbg(dev, "Realtek USB init: enable usb clk\n");

	// Enable USB clk
	clk_prepare_enable(clk_usb); // = clk_prepare + clk_enable
	mdelay(2);
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

static int __port0_switch_gpio(struct manager_data *data, bool high)
{
	struct device *dev = data->dev;

	if (data->port0_switch_ctrl_gpio != -1 &&
		    gpio_is_valid(data->port0_switch_ctrl_gpio)) {
		dev_dbg(dev, "%s gpio %d, set to %s\n",
			    __func__, data->port0_switch_ctrl_gpio, high?"high":"low");
		if (gpio_direction_output(data->port0_switch_ctrl_gpio, high))
			dev_err(dev, "%s ERROR switch_ctrl_gpio = 0 fail\n",
				    __func__);
		else
			return 1;
	}

	return 0;
}

int rtk_usb_set_type_c_switch_gpio(struct device *type_c_dev, bool high)
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
	return __port0_switch_gpio(data, high);
}

static int __port0_gpio_on_off(struct manager_data *data, bool on);

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

	ret = __port0_gpio_on_off(data, on);

	mutex_unlock(&data->lock);

	return ret;
}

static int __port0_gpio_on_off(struct manager_data *data, bool on)
{
	struct device *dev = data->dev;
	int ret = 0;
	int gpio = data->port0_pow_gpio;
	bool power_low_active = data->port0_power_low_active;

	if (gpio_is_valid(gpio)) {
		if (gpio_direction_output(gpio, power_low_active?!on:on)) {
			dev_err(dev, "%s ERROR set gpio fail\n", __func__);
			ret = -1;
		} else {
			dev_info(dev, "%s to set port0 power%s %s by gpio (id=%d) OK\n",
				    __func__, power_low_active?" (power_low_active)":"",
				    on?"on":"off", gpio);
			data->port0_pow_enable = on;
		}
	}
	return ret;
}

static int __port1_gpio_on_off(struct manager_data *data, bool on) {
	struct device *dev = data->dev;
	int port1_pow_gpio = data->port1_pow_gpio;
	bool power_low_active = data->port1_power_low_active;

	if (gpio_is_valid(port1_pow_gpio)) {
		if (gpio_request(port1_pow_gpio, "port1_pow_gpio"))    //request gpio
			dev_err(dev, "%s ERROR Request port1_pow_gpio (id=%d) fail\n",
				   __func__, port1_pow_gpio);
		else if (port1_pow_gpio != -1) {
			if (gpio_direction_output(port1_pow_gpio, power_low_active?!on:on)) {
				dev_err(dev, "%s ERROR port1 power %s fail\n",
					    __func__, on?"on":"off");
			} else {
				dev_info(dev, "%s to set port1 power%s %s by gpio (id=%d) OK\n",
					    __func__, power_low_active?" (power_low_active)":"",
					    on?"on":"off", port1_pow_gpio);
				data->port1_pow_enable = on;
			}
			gpio_free(port1_pow_gpio);
		}
	}
	return 0;
}

static int __port2_gpio_on_off(struct manager_data *data, bool on) {
	struct device *dev = data->dev;
	int port2_pow_gpio = data->port2_pow_gpio;
	bool power_low_active = data->port2_power_low_active;

	if (gpio_is_valid(port2_pow_gpio)) {
		if (gpio_request(port2_pow_gpio, "port2_pow_gpio"))    //request gpio
			dev_err(dev, "%s ERROR Request port1_pow_gpio (id=%d) fail\n",
				   __func__, port2_pow_gpio);
		else if (port2_pow_gpio != -1) {
			if (gpio_direction_output(port2_pow_gpio,
				    power_low_active?!on:on)) {
				dev_err(dev, "%s ERROR port2 power %s fail\n",
					    __func__, on?"on":"off");
			} else {
				dev_info(dev, "%s to set port2 power%s %s by gpio (id=%d) OK\n",
					    __func__, power_low_active?" (power_low_active)":"",
					    on?"on":"off", port2_pow_gpio);
				data->port2_pow_enable = on;
			}
			gpio_free(port2_pow_gpio);
		}
	}
	return 0;
}

static int __port3_gpio_on_off(struct manager_data *data, bool on) {
	struct device *dev = data->dev;
	int port3_pow_gpio = data->port3_pow_gpio;
	bool power_low_active = data->port3_power_low_active;

	if (gpio_is_valid(port3_pow_gpio)) {
		if (gpio_request(port3_pow_gpio, "port3_pow_gpio")) //request gpio
			dev_err(dev, "%s ERROR Request port3_pow_gpio (id=%d) fail\n",
				    __func__, port3_pow_gpio);
		else if (port3_pow_gpio != -1) {
			if (gpio_direction_output(port3_pow_gpio,
				    power_low_active?!on:on)) {
				dev_err(dev, "%s ERROR port3 power %s fail\n",
					    __func__, on?"on":"off");
			} else {
				dev_info(dev, "%s to set port3 power%s %s by gpio (id=%d) OK\n",
					    __func__, power_low_active?" (power_low_active)":"",
					    on?"on":"off", port3_pow_gpio);
				data->port3_pow_enable = on;
			}
			gpio_free(port3_pow_gpio);
		}
	}
	return 0;
}

static int __usb_port_suspend(struct manager_data *data) {
	struct device *dev = data->dev;
	bool is_suspend = true;

	if (!data->rtk_usb)
		return;

	dev_info(dev, "%s", __func__);
	if (data->port0) {
		dev_dbg(dev, "set port 0 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_0, is_suspend);
	}
	if (data->port1) {
		dev_dbg(dev, "set port 1 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_1, is_suspend);
	}
	if (data->port2) {
		dev_dbg(dev, "set port 2 phy suspend\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_2, is_suspend);
	}
	if (data->port3) {
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
	if (data->port0) {
		dev_dbg(dev, "set port 0 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_0, is_suspend);
	}
	if (data->port1) {
		dev_dbg(dev, "set port 1 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_1, is_suspend);
	}
	if (data->port2) {
		dev_dbg(dev, "set port 2 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_2, is_suspend);
	}
	if (data->port3) {
		dev_dbg(dev, "set port 3 phy resume\n");
		rtk_usb_port_suspend_resume(data->rtk_usb, USB_PORT_3, is_suspend);
	}
	return 0;
}

static int __usb_port_gpio_off(struct manager_data *data) {
	struct device *dev = data->dev;
	bool off = false;

	dev_info(dev, "%s", __func__);
	if (data->port0) {
		struct device_node *node = data->port0_host_node;
		struct device_node *next_node;
		int dr_mode = USB_DR_MODE_UNKNOWN;

		if (node)
			next_node = of_get_next_child(node, NULL);
		if (next_node) {
			struct platform_device *pdev;
			pdev = of_find_device_by_node(next_node);
			dr_mode = usb_get_dr_mode(&pdev->dev);

			next_node = of_get_next_child(node, next_node);
		}
		/* For type c port power on/off for type c driver disable */
		if (USB_DR_MODE_HOST == dr_mode &&
			    !of_device_is_available(next_node)) {
			dev_info(data->dev, "%s Type c Node is disable ==> power off port0",
				    data->port0_host_node->name);
			__port0_gpio_on_off(data, off);
		}
	}
	if (data->port1) {
		__port1_gpio_on_off(data, off);
	}
	if (data->port2) {
		__port2_gpio_on_off(data, off);
	}
	if (data->port3) {
		__port3_gpio_on_off(data, off);
	}
	return 0;
}

static int __usb_port_gpio_on(struct manager_data *data) {
	struct device *dev = data->dev;
	bool on = true;

	dev_info(dev, "%s", __func__);
	if (data->port0) {
		struct device_node *node = data->port0_host_node;
		struct device_node *next_node;
		int dr_mode = USB_DR_MODE_UNKNOWN;

		if (node)
			next_node = of_get_next_child(node, NULL);
		if (next_node) {
			struct platform_device *pdev;
			pdev = of_find_device_by_node(next_node);
			dr_mode = usb_get_dr_mode(&pdev->dev);

			next_node = of_get_next_child(node, next_node);
		}
		/* For type c port power on/off for type c driver disable */
		if (USB_DR_MODE_HOST == dr_mode &&
			    !of_device_is_available(next_node)) {
			dev_info(data->dev, "%s Type c Node is disable ==> power on port0",
				    data->port0_host_node->name);
			__port0_switch_gpio(data, false);
			__port0_gpio_on_off(data, on);
		}
	}
	if (data->port1) {
		__port1_gpio_on_off(data, on);
	}
	if (data->port2) {
		__port2_gpio_on_off(data, on);
	}
	if (data->port3) {
		__port3_gpio_on_off(data, on);
	}
	return 0;
}

int rtk_usb_init_gpio_power_on(struct device *usb_dev) {
	struct device_node *usb_node = usb_dev->of_node;
	struct device_node *node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
	struct platform_device *pdev = NULL;
	struct manager_data *data = NULL;
	bool on = true;

	if (node != NULL)
		pdev = of_find_device_by_node(node);
	if (pdev != NULL) {
		data = platform_get_drvdata(pdev);
	}
	if (data == NULL) {
		dev_err(data->dev, "%s ERROR no manager_data", __func__);
		return -ENODEV;
	}

	dev_info(data->dev, "%s for %s", __func__, dev_name(usb_dev));
	mutex_lock(&data->lock);
	if (data->port0 && (data->port0_host_node->phandle == usb_node->phandle)) {
		struct device_node *node = data->port0_host_node;
		struct device_node *next_node;
		int dr_mode = USB_DR_MODE_UNKNOWN;

		if (node)
			next_node = of_get_next_child(node, NULL);
		if (next_node) {
			struct platform_device *pdev;
			pdev = of_find_device_by_node(next_node);
			dr_mode = usb_get_dr_mode(&pdev->dev);

			next_node = of_get_next_child(node, next_node);
		}
		/* For type c port power on/off for type c driver disable */
		if (USB_DR_MODE_HOST == dr_mode &&
			    !of_device_is_available(next_node)) {
			dev_info(data->dev, "%s Type c Node is disable ==> power on port0",
				    data->port0_host_node->name);
			__port0_switch_gpio(data, false);
			__port0_gpio_on_off(data, on);
		}
	}
	if (data->port1 || data->port2) {
		static int count = 0;
		if (data->port1_host_node->phandle == usb_node->phandle)
			count++;
		if (data->port2_host_node->phandle == usb_node->phandle)
			count++;
		if (data->port2_ohci_node &&
			    data->port2_ohci_node->phandle == usb_node->phandle)
			count++;

		if (count == (data->port1 + data->port2)) {
			dev_dbg(data->dev, "%s %s power on port 1 and port 2",
				    __func__, dev_name(usb_dev));
			__port1_gpio_on_off(data, on);
			__port2_gpio_on_off(data, on);
			count = 0;
		}
	}
	if (data->port3 && (data->port3_host_node->phandle == usb_node->phandle)) {
		dev_dbg(data->dev, "%s %s power on port 3",
			    __func__, dev_name(usb_dev));
		__port3_gpio_on_off(data, on);
	}

	mutex_unlock(&data->lock);
	return 0;
}

int rtk_usb_host_gpio_power_on(void)
{
        struct device_node *node = of_find_compatible_node(NULL, NULL,
                    "Realtek,usb-manager");
        struct platform_device *pdev = NULL;
        struct manager_data *data = NULL;
        bool on = true;

        if (node != NULL)
                pdev = of_find_device_by_node(node);
        if (pdev != NULL) {
                data = platform_get_drvdata(pdev);
        }

        if (data == NULL) {
                dev_err(data->dev, "%s ERROR no manager_data", __func__);
                return -ENODEV;
        }

	__port1_gpio_on_off(data, on);
	__port2_gpio_on_off(data, on);

	return 0;
}
EXPORT_SYMBOL(rtk_usb_host_gpio_power_on);

int rtk_usb_host_gpio_power_off(void)
{
        struct device_node *node = of_find_compatible_node(NULL, NULL,
                    "Realtek,usb-manager");
        struct platform_device *pdev = NULL;
        struct manager_data *data = NULL;
        bool off = false;

        if (node != NULL)
                pdev = of_find_device_by_node(node);
        if (pdev != NULL) {
                data = platform_get_drvdata(pdev);
        }

        if (data == NULL) {
                dev_err(data->dev, "%s ERROR no manager_data", __func__);
                return -ENODEV;
        }

	__port1_gpio_on_off(data, off);
	__port2_gpio_on_off(data, off);

	return 0;
}
EXPORT_SYMBOL(rtk_usb_host_gpio_power_off);

static int __usb_gpio_init(struct manager_data *data) {
	bool off = false;

	data->port0_pow_enable = off;
	data->port1_pow_enable = off;
	data->port2_pow_enable = off;
	data->port3_pow_enable = off;

	__port0_gpio_on_off(data, off);
	__port1_gpio_on_off(data, off);
	__port2_gpio_on_off(data, off);
	__port3_gpio_on_off(data, off);

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

	__usb_gpio_init(data);

	__rtk_usb_set_hw_pm_enable(data);

	dev_dbg(dev, "Realtek USB init Done\n");

	return 0;
}

#ifdef CONFIG_DYNAMIC_DEBUG
static int rtk_port0_power_show(struct seq_file *s, void *unused)
{
	struct manager_data		*data = s->private;

	seq_printf(s, "To Control Port 0 (DWC3 DRD power)\n");
	seq_printf(s, "echo \"on\" > port0_power\n");
	seq_printf(s, "echo \"off\" > port0_power\n");
	seq_printf(s, "\n");
	seq_printf(s, "Now port0 %s\n", data->port0_pow_enable?"on":"off");

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

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		__port0_gpio_on_off(data, true);
	} else if (!strncmp(buf, "off", 3)) {
		__port0_gpio_on_off(data, false);
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
	seq_printf(s, "Now port1 %s\n", data->port1_pow_enable?"on":"off");

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

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		__port1_gpio_on_off(data, true);
	} else if (!strncmp(buf, "off", 3)) {
		__port1_gpio_on_off(data, false);
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
	seq_printf(s, "Now port2 %s\n", data->port2_pow_enable?"on":"off");

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

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		__port2_gpio_on_off(data, true);
	} else if (!strncmp(buf, "off", 3)) {
		__port2_gpio_on_off(data, false);
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
	seq_printf(s, "Now port3 %s\n", data->port3_pow_enable?"on":"off");

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

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	mutex_lock(&data->lock);
	if (!strncmp(buf, "on", 2)) {
		__port3_gpio_on_off(data, true);
	} else if (!strncmp(buf, "off", 3)) {
		__port3_gpio_on_off(data, false);
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

static u32 rtk_usb_reg_addr = 0;
static u32 rtk_usb_reg_value = 0;

static int rtk_usb_reg_show(struct seq_file *s, void *unused)
{
	//struct manager_data		*data = s->private;
	void __iomem *addr;
	if (rtk_usb_reg_addr) {
		addr = ioremap(rtk_usb_reg_addr, 0x4);
		seq_printf(s, "Register Addr 0x%x = 0x%x\n",
			    rtk_usb_reg_addr, readl(addr));

		iounmap(addr);
	} else {
		seq_printf(s, "read register: (1) echo \"0x98XXXXXX\" > "
			    "reg (2) cat reg\n");
		seq_printf(s, "write register: (1) echo \"0x98XXXXXX value\" > "
			    "reg (2) cat reg\n");
	}
	return 0;
}

static int rtk_usb_reg_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb_reg_show, inode->i_private);
}

static ssize_t rtk_usb_reg_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buffer[40] = "";
	char *buf = buffer;

	u32 addr, value;
	int ret;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "0x98", 4)) {
		ret = sscanf(buf, "%x %x", &addr, &value);
		if (addr >= 0x98000000 && addr <= 0x98200000) {
			rtk_usb_reg_addr = addr;
			if (ret > 1) {
				void __iomem *v_addr = ioremap(rtk_usb_reg_addr, 0x4);
				rtk_usb_reg_value = value;
				writel(rtk_usb_reg_value, v_addr);
				iounmap(v_addr);
			}
		} else
			dev_err(data->dev, "Error: to set addr = 0x%x, value = 0x%x\n",
				    addr, value);
	} else
		rtk_usb_reg_addr = 0;

	return count;
}

static const struct file_operations rtk_usb_reg_fops = {
	.open			= rtk_usb_reg_open,
	.write			= rtk_usb_reg_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_usb_debug_show(struct seq_file *s, void *unused)
{
	//struct manager_data		*data = s->private;

	seq_printf(s, "To Enable/Disable Debug register\n");
	seq_printf(s, "echo \"enable\" > debug\n");
	seq_printf(s, "echo \"disable\" > debug\n");

	return 0;
}

static int rtk_usb_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb_debug_show, inode->i_private);
}

static ssize_t rtk_usb_debug_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	static struct dentry *reg_file = NULL;
	struct seq_file		*s = file->private_data;
	struct manager_data		*data = s->private;
	char			buf[32];

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "enable", 6)) {
		if (!reg_file)
		reg_file = debugfs_create_file("reg", S_IRUGO | S_IWUSR, data->debug_dir,
				data, &rtk_usb_reg_fops);
	} else if (!strncmp(buf, "disable", 7)) {
		debugfs_remove(reg_file);
		reg_file = NULL;
	}

	return count;
}

static const struct file_operations rtk_usb_debug_fops = {
	.open			= rtk_usb_debug_open,
	.write			= rtk_usb_debug_write,
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

	if (data->port0
			&& !debugfs_create_file("port0_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port0_power_fops))
		goto file_error;

	if (data->port1
			&& !debugfs_create_file("port1_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port1_power_fops))
		goto file_error;

	if (data->port2
			&& !debugfs_create_file("port2_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port2_power_fops))
		goto file_error;

	if (data->port3
			&& !debugfs_create_file("port3_power", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_port3_power_fops))
		goto file_error;

	if (!debugfs_create_file("usb_iso_mode", S_IRUGO | S_IWUSR,
					data->debug_dir, data, &rtk_iso_mode_fops))
		goto file_error;

	if (!debugfs_create_file("debug", S_IRUGO | S_IWUSR, data->debug_dir, data,
						&rtk_usb_debug_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(data->debug_dir);
}
#endif //CONFIG_DYNAMIC_DEBUG

static int rtk_usb_manager_probe(struct platform_device *pdev) {
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
		gpio = of_get_named_gpio(node, "realtek,port0-power-gpio", 0);

		if (gpio_is_valid(gpio)) {
			data->port0_pow_gpio = gpio;
			dev_dbg(dev, "%s get port0-power-gpio (id=%d) OK\n", __func__, gpio);
		 } else {
			data->port0_pow_gpio = -1;
			dev_err(dev, "port0-power-gpio no found");
		}

		gpio = of_get_named_gpio(node, "realtek,port1-power-gpio", 0);
		if (gpio_is_valid(gpio)) {
			data->port1_pow_gpio = gpio;
			dev_dbg(dev, "%s get port1-power-gpio (id=%d) OK\n", __func__, gpio);
		 } else {
			data->port1_pow_gpio = -1;
			dev_err(dev, "port1-power-gpio no found");
		}

		gpio = of_get_named_gpio(node, "realtek,port2-power-gpio", 0);
		if (gpio_is_valid(gpio)) {
			data->port2_pow_gpio = gpio;
			dev_dbg(dev, "%s get port2-power-gpio (id=%d) OK\n", __func__, gpio);
		 } else {
			data->port2_pow_gpio = -1;
			dev_err(dev, "port2-power-gpio no found");
		}

		gpio = of_get_named_gpio(node, "realtek,port3-power-gpio", 0);
		if (gpio_is_valid(gpio)) {
			data->port3_pow_gpio = gpio;
			dev_dbg(dev, "%s get port-power-gpio (id=%d) OK\n", __func__, gpio);
		 } else {
			data->port3_pow_gpio = -1;
			dev_dbg(dev, "port3-power-gpio no found");
		}
	}

	if (node && of_device_is_available(node)) {
		gpio = of_get_named_gpio(node, "realtek,port0_switch_ctrl-gpio", 0);

		if (gpio_is_valid(gpio)) {
			data->port0_switch_ctrl_gpio = gpio;
			dev_info(dev, "%s get switch_ctrl-gpio (id=%d) OK\n",
				    __func__, gpio);
		} else {
			dev_err(dev, "Error switch_ctrl-gpio no found");
			data->port0_switch_ctrl_gpio = -1;
		}
	}

	if (node && of_device_is_available(node)) {
		data->port0_host_node = of_parse_phandle(node, "port0", 0);
		data->port1_host_node = of_parse_phandle(node, "port1", 0);
		data->port2_host_node = of_parse_phandle(node, "port2", 0);
		data->port2_ohci_node = of_parse_phandle(node, "port2", 1);
		data->port3_host_node = of_parse_phandle(node, "port3", 0);

		data->type_c_node = of_parse_phandle(node, "type_c", 0);

		data->disable_usb = true;
		data->port0 = 0;
		if (data->port0_host_node &&
			    of_device_is_available(data->port0_host_node)) {
			dev_info(dev, "Port 0 %s status is okay",
				    data->port0_host_node->name);
			data->port0++;
		}

		np = of_find_node_by_name(NULL, "rtk_dwc3_u2host");
		if (of_property_read_bool(np, "usbhost_backend"))
			data->port1 = 1;
		else
			data->port1 = 0;

		if (data->port1_host_node &&
			    of_device_is_available(data->port1_host_node)) {
			dev_err(dev, "Port 1 %s status is okay",
				    data->port1_host_node->name);
			data->port1++;
		}

		if (of_property_read_bool(np, "usbhost_backend"))
			data->port2 = 1;
		else
			data->port2 = 0;
		
		if (data->port2_host_node &&
			    of_device_is_available(data->port2_host_node)) {
			dev_err(dev, "Port 2 %s status is okay",
				    data->port2_host_node->name);
			data->port2++;
		}
		if (data->port2_ohci_node &&
			    of_device_is_available(data->port2_ohci_node)) {
			dev_err(dev, "Port 2 %s status is okay",
				    data->port2_ohci_node->name);
			data->port2++;
		}

		data->port3 = 0;
		if (data->port3_host_node &&
			    of_device_is_available(data->port3_host_node)) {
			dev_err(dev, "Port 3 %s status is okay",
				    data->port3_host_node->name);
			data->port3++;
		}
		if (data->port0 || data->port1 || data->port2 || data->port3) {
			data->disable_usb = false;
		}

		if (of_property_read_bool(node, "power_low_active")) {
			data->port0_power_low_active = true;
			data->port1_power_low_active = true;
			data->port2_power_low_active = true;
			data->port3_power_low_active = true;
		} else {
			data->port0_power_low_active = false;
			data->port1_power_low_active = false;
			data->port2_power_low_active = false;
			data->port3_power_low_active = false;
		}

		if (of_property_read_bool(node, "port0_power_low_active"))
			data->port0_power_low_active = true;
		if (of_property_read_bool(node, "port1_power_low_active"))
			data->port1_power_low_active = true;
		if (of_property_read_bool(node, "port2_power_low_active"))
			data->port2_power_low_active = true;
		if (of_property_read_bool(node, "port3_power_low_active"))
			data->port3_power_low_active = true;

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
	}

	sub_node = of_get_child_by_name(node, "power_ctrl_reg");
	if (sub_node) {
		data->rtk_usb = rtk_usb_soc_init(sub_node);
	} else {
		data->rtk_usb = NULL;
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

	__usb_gpio_init(data);
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
