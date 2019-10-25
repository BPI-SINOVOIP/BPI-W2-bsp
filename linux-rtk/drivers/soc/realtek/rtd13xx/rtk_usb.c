/*
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/usb/otg.h>
#include <soc/realtek/rtk_usb.h>
#include <soc/realtek/rtk_chip.h>

struct rtk_usb {
	struct power_ctrl_reg {
		/* l4_icg */
		u32 p0_l4_icg;
		u32 p1_l4_icg;
		u32 p2_l4_icg;
	} power_ctrl_reg;

	bool usb_power_cut;

	struct type_c {
		int connector_switch_gpio;
		int plug_side_switch_gpio;
	} type_c;

	u32 pcie_usb3phy_sel;
};

#define disable_cc 0x0
#define enable_cc1 0x1
#define enable_cc2 0x2

static struct rtk_usb *rtk_usb;

/* set usb charger power */
void rtk_usb_set_charger_power(struct rtk_usb *rtk_usb, unsigned int val)
{
	if (!rtk_usb)
		return;

	return;
}

int rtk_usb_set_hw_l4icg_on_off(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool on)
{
	void __iomem *reg;

	if (!rtk_usb)
		return 0;

	switch (port_num) {
	case USB_PORT_0:
		if (rtk_usb->power_ctrl_reg.p0_l4_icg) {
			pr_info("%s set l4_icg port %d\n", __func__, port_num);
			reg = ioremap(rtk_usb->power_ctrl_reg.p0_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	case USB_PORT_1:
		if (rtk_usb->power_ctrl_reg.p1_l4_icg) {
			pr_info("%s set l4_icg port %d\n", __func__, port_num);
			reg = ioremap(rtk_usb->power_ctrl_reg.p1_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	case USB_PORT_2:
		if (rtk_usb->power_ctrl_reg.p2_l4_icg) {
			pr_info("%s set l4_icg port %d\n", __func__, port_num);
			reg = ioremap(rtk_usb->power_ctrl_reg.p2_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	default:
		pr_err("%s Error Port num %d\n", __func__, port_num);
		break;
	}

	return 0;
}

int rtk_usb_iso_power_ctrl(struct rtk_usb *rtk_usb,
	    bool power_on)
{
	if (!rtk_usb)
		return 0;

	pr_debug("%s START\n", __func__);

	pr_debug("%s END\n", __func__);
	return 0;
}

int rtk_usb_port_suspend_resume(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool is_suspend)
{
	if (!rtk_usb)
		return 0;

	return 0;
}

int rtk_type_c_init(struct rtk_usb *rtk_usb)
{
	if (!rtk_usb)
		return 0;

	return 0;
}

int rtk_type_c_plug_config(struct rtk_usb *rtk_usb, int dr_mode, int cc)
{
	bool high;

	/* host / device */
	if (dr_mode == USB_DR_MODE_PERIPHERAL) {
		high = true;
	} else if (dr_mode == USB_DR_MODE_HOST) {
		high = false;
	} else {
		goto cc_config;
	}

	if (rtk_usb->type_c.connector_switch_gpio != -1 &&
		    gpio_is_valid(rtk_usb->type_c.connector_switch_gpio)) {
		pr_info("%s Set connector to %s by gpio %d\n",
			    __func__, high?"device":"host",
			    rtk_usb->type_c.connector_switch_gpio);
		if (gpio_direction_output(rtk_usb->type_c.connector_switch_gpio, high))
			pr_err("%s ERROR connector_switch_ctrl_gpio fail\n",
				    __func__);
	}

cc_config:
	/* cc pin */
	/* host / device */
	if (cc == enable_cc1) {
		high = true;
	} else if (cc == enable_cc2) {
		high = false;
	} else {
		goto out;
	}

	if (rtk_usb->type_c.plug_side_switch_gpio != -1 &&
		    gpio_is_valid(rtk_usb->type_c.plug_side_switch_gpio)) {
		pr_info("%s type plug to %s by gpio %d\n",
			    __func__, high?"cc1":"cc2",
			    rtk_usb->type_c.plug_side_switch_gpio);
		if (gpio_direction_output(rtk_usb->type_c.plug_side_switch_gpio, high))
			pr_err("%s set ERROR plug_side_switch_gpio fail\n",
				    __func__);
	}

out:
	return 0;
}

struct rtk_usb *rtk_usb_soc_init(struct device_node *node)
{
	struct device_node *sub_node;

	if (!rtk_usb)
		rtk_usb = kzalloc(sizeof(struct rtk_usb), GFP_KERNEL);

	pr_info("%s START (%s)\n", __func__, __FILE__);

	sub_node = of_get_child_by_name(node, "power_ctrl_reg");
	if (sub_node) {
		pr_debug("%s sub_node %s\n", __func__, sub_node->name);

		of_property_read_u32(sub_node,
			    "p0_l4_icg", &rtk_usb->power_ctrl_reg.p0_l4_icg);
		of_property_read_u32(sub_node,
			    "p1_l4_icg", &rtk_usb->power_ctrl_reg.p1_l4_icg);
		of_property_read_u32(sub_node,
			    "p2_l4_icg", &rtk_usb->power_ctrl_reg.p2_l4_icg);

		if (of_property_read_bool(sub_node, "usb_power_cut"))
			rtk_usb->usb_power_cut = true;
		else
			rtk_usb->usb_power_cut = false;
	}

	sub_node = of_get_child_by_name(node, "type_c");
	if (sub_node) {
		int gpio;
		pr_debug("%s sub_node %s\n", __func__, sub_node->name);

		gpio = of_get_named_gpio(sub_node, "realtek,connector_switch-gpio", 0);
		if (gpio_is_valid(gpio)) {
			rtk_usb->type_c.connector_switch_gpio = gpio;
			pr_info("%s get connector_switch-gpio (id=%d) OK\n",
				    __func__, gpio);
		} else {
			pr_info("connector_switch-gpio no found");
			rtk_usb->type_c.connector_switch_gpio = -1;
		}

		gpio = of_get_named_gpio(sub_node, "realtek,plug_side_switch-gpio", 0);
		if (gpio_is_valid(gpio)) {
			rtk_usb->type_c.plug_side_switch_gpio = gpio;
			pr_info("%s get plug_side_switch-gpio (id=%d) OK\n",
				    __func__, gpio);
		} else {
			pr_info("plug_side_switch-gpio no found");
			rtk_usb->type_c.plug_side_switch_gpio = -1;
		}
	}
	if (of_property_read_u32(node,
			    "pcie_usb3phy_sel", &rtk_usb->pcie_usb3phy_sel)) {
		rtk_usb->pcie_usb3phy_sel = -1;
	} else {
		void __iomem *reg = ioremap(rtk_usb->pcie_usb3phy_sel, 0x4);
		int val = readl(reg) | BIT(6);

		writel(val, reg);

		pr_info("%s: pcie_usb3phy_sel=%x to enable usb3phy (val=0x%x)\n",
			    __func__, rtk_usb->pcie_usb3phy_sel, readl(reg));

		iounmap(reg);
	}

	pr_info("%s END\n", __func__);
	return rtk_usb;
}

int rtk_usb_soc_free(struct rtk_usb **rtk_usb)
{
	if (*rtk_usb) {
		kfree(*rtk_usb);
		*rtk_usb = NULL;
	}
	return 0;
}
