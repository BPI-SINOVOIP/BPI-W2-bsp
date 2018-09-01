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
#include <soc/realtek/rtk_usb.h>
#include <soc/realtek/rtk_chip.h>

struct rtk_usb {
	struct power_ctrl_reg {
		u32 usb_ctrl;
		/* Port 0~2 */
		u32 usb0_sram_pwr3;
		u32 usb0_sram_pwr4;
		/* l4_icg */
		u32 p0_l4_icg;
		u32 p1_l4_icg;
	} power_ctrl_reg;

	bool usb_power_cut;
};

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
	case USB_PORT_2:
		if (rtk_usb->power_ctrl_reg.p1_l4_icg) {
			pr_info("%s set l4_icg port %d\n", __func__, port_num);
			reg = ioremap(rtk_usb->power_ctrl_reg.p1_l4_icg, 0x4);
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

	if (rtk_usb->usb_power_cut &&
		    rtk_usb->power_ctrl_reg.usb_ctrl &&
		    rtk_usb->power_ctrl_reg.usb0_sram_pwr3 &&
		    rtk_usb->power_ctrl_reg.usb0_sram_pwr4) {
		void __iomem *usb0_sram_pwr3 =
			    ioremap(rtk_usb->power_ctrl_reg.usb0_sram_pwr3, 0x4);
		void __iomem *usb0_sram_pwr4 =
			    ioremap(rtk_usb->power_ctrl_reg.usb0_sram_pwr4, 0x4);
		void __iomem *usb_ctrl = ioremap(rtk_usb->power_ctrl_reg.usb_ctrl, 0x4);

		pr_info("%s power_%s ([0x%x=0x%08x)\n", __func__, power_on?"on":"off",
			    rtk_usb->power_ctrl_reg.usb_ctrl, readl(usb_ctrl));
		if (power_on) {
			writel((BIT(0) | BIT(1) | BIT(4) | BIT(5) |BIT(6)) |
				     readl(usb_ctrl), usb_ctrl);
			writel(0x00000f00, usb0_sram_pwr4);
			writel(~(BIT(8) | BIT(9)) & readl(usb_ctrl), usb_ctrl);
		} else {
			writel((BIT(8) | BIT(9)) | readl(usb_ctrl), usb_ctrl);
			// port0-port2 sram
			writel(0, usb0_sram_pwr3);
			writel(0x00000f01, usb0_sram_pwr4);
			writel(~(BIT(0) | BIT(1) | BIT(4) | BIT(5) |BIT(6)) &
				     readl(usb_ctrl), usb_ctrl);
		}
		pr_info("set power_domain %s ([0x%x]=0x%08x)\n", power_on?"on":"off",
			    rtk_usb->power_ctrl_reg.usb_ctrl, readl(usb_ctrl));
		iounmap(usb_ctrl);
		iounmap(usb0_sram_pwr3);
		iounmap(usb0_sram_pwr4);
	}
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

struct rtk_usb *rtk_usb_soc_init(struct device_node *sub_node)
{
	if (!rtk_usb)
		rtk_usb = kzalloc(sizeof(struct rtk_usb), GFP_KERNEL);

	pr_info("%s START (%s)\n", __func__, __FILE__);
	if (sub_node) {
		pr_debug("%s sub_node %s\n", __func__, sub_node->name);
		of_property_read_u32(sub_node,
			    "usb_ctrl", &rtk_usb->power_ctrl_reg.usb_ctrl);
		/* Port 0~2 */
		of_property_read_u32(sub_node,
			    "usb0_sram_pwr3",
			    &rtk_usb->power_ctrl_reg.usb0_sram_pwr3);
		of_property_read_u32(sub_node,
			    "usb0_sram_pwr4",
			    &rtk_usb->power_ctrl_reg.usb0_sram_pwr4);

		of_property_read_u32(sub_node,
			    "p0_l4_icg", &rtk_usb->power_ctrl_reg.p0_l4_icg);
		of_property_read_u32(sub_node,
			    "p1_l4_icg", &rtk_usb->power_ctrl_reg.p1_l4_icg);

		if (of_property_read_bool(sub_node, "usb_power_cut"))
			rtk_usb->usb_power_cut = true;
		else
			rtk_usb->usb_power_cut = false;

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
