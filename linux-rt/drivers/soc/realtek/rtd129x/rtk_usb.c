/*
 * rtk_usb.c
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/slab.h>
#include <linux/io.h>
#include <linux/of.h>
#include <soc/realtek/power-control.h>
#include <soc/realtek/rtk_usb.h>
#include <soc/realtek/rtk_chip.h>

struct rtk_usb {
	struct power_ctrl_reg {
		u32 usb_ctrl;
		/* Port 0~2 */
		u32 usb0_sram_pwr;
		u32 usb0_sram_pwr_ctrl;
		/* Port 3 */
		u32 usb1_sram_pwr;
		u32 usb1_sram_pwr_ctrl;
		/* l4_icg */
		u32 p0_l4_icg;
		u32 p1_l4_icg;
		u32 p2_l4_icg;
		u32 p3_l4_icg;

		/* for power cut */
		u32 usb_phy_ctrl;

		u32 p0_utmi_reset;
		u32 p1_utmi_reset;
		u32 p2_utmi_reset;
		u32 p3_utmi_reset;

		u32 p0_pipe_reset;
		u32 p1_pipe_reset;
		u32 p2_pipe_reset;
		u32 p3_pipe_reset;

		/* for suspend */
		u32 p0_gusb2phycfg;
		u32 p0_gusb3pipectl;

		u32 p1_gusb2phycfg;
		u32 p1_gusb3pipectl;

		u32 p2_gusb2phycfg;
		u32 p2_gusb3pipectl;

		u32 p3_gusb2phycfg;
		u32 p3_gusb3pipectl;

		u32 usb_charger;
	} power_ctrl_reg;

	bool usb_power_cut;
};

static struct rtk_usb *rtk_usb;

/* set usb charger power */
void rtk_usb_set_charger_power(struct rtk_usb *rtk_usb, unsigned int val)
{
	void __iomem *reg_charger;

	if (!rtk_usb || !rtk_usb->power_ctrl_reg.usb_charger) return;

	reg_charger  = ioremap(rtk_usb->power_ctrl_reg.usb_charger, 0x4);

	pr_debug("set usb_charger to 0x%08x\n", val);

	writel(val, reg_charger);

	iounmap(reg_charger);
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
			reg = ioremap(rtk_usb->power_ctrl_reg.p0_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	case USB_PORT_1:
		if (rtk_usb->power_ctrl_reg.p1_l4_icg) {
			reg = ioremap(rtk_usb->power_ctrl_reg.p1_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	case USB_PORT_2:
		if (rtk_usb->power_ctrl_reg.p2_l4_icg) {
			reg = ioremap(rtk_usb->power_ctrl_reg.p3_l4_icg, 0x4);
			writel((on&BIT(0)) | readl(reg), reg);
			iounmap(reg);
		}
		break;
	case USB_PORT_3:
		if (rtk_usb->power_ctrl_reg.p3_l4_icg) {
			reg = ioremap(rtk_usb->power_ctrl_reg.p3_l4_icg, 0x4);
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

static int __isolate_phy_from_a_to_d(struct rtk_usb *rtk_usb)
{
	void __iomem *reg;

	/* isolate UPHY A->D */
	if (!rtk_usb) return 0;

	pr_debug("%s START\n", __func__);

	pr_debug("set USB Analog phy power off\n");

	if (rtk_usb->power_ctrl_reg.usb_phy_ctrl) {
		reg = ioremap(rtk_usb->power_ctrl_reg.usb_phy_ctrl, 0x4);
		writel(BIT(0) | BIT(1) | readl(reg), reg);
		iounmap(reg);
	}
	if (rtk_usb->power_ctrl_reg.p0_utmi_reset) {
		reg = ioremap(rtk_usb->power_ctrl_reg.p0_utmi_reset, 0x4);
		writel(BIT(0) | readl(reg), reg);
		iounmap(reg);
	}
	if (rtk_usb->power_ctrl_reg.p1_utmi_reset) {
		reg = ioremap(rtk_usb->power_ctrl_reg.p1_utmi_reset, 0x4);
		writel(BIT(0) | readl(reg), reg);
		iounmap(reg);
	}
	if (rtk_usb->power_ctrl_reg.p2_utmi_reset) {
		reg = ioremap(rtk_usb->power_ctrl_reg.p2_utmi_reset, 0x4);
		writel(BIT(0) | readl(reg), reg);
		iounmap(reg);
	}
	if (get_rtd_chip_id() == CHIP_ID_RTD1296 &&
		    rtk_usb->power_ctrl_reg.p3_utmi_reset) {
		reg = ioremap(rtk_usb->power_ctrl_reg.p3_utmi_reset, 0x4);
		writel(BIT(0) | readl(reg), reg);
		iounmap(reg);
	}
	if (rtk_usb->power_ctrl_reg.usb_ctrl) {
		reg = ioremap(rtk_usb->power_ctrl_reg.usb_ctrl, 0x4);
		writel(~(BIT(4) | BIT(5) | BIT(6)) & readl(reg), reg);

		iounmap(reg);
	}
	pr_debug("%s END\n", __func__);

	return 0;
}

static inline void __power_control_set_power(const char *name, bool power_on)
{
	struct power_control * pctrl = power_control_get(name);
	if (!pctrl) {
		pr_debug("%s: Failed to get power_control %s\n",  __func__, name);
		return;
	}

	if (power_on)
		power_control_power_on(pctrl);
	else
		power_control_power_off(pctrl);
}

int rtk_usb_iso_power_ctrl(struct rtk_usb *rtk_usb,
	    bool power_on)
{
	if (!rtk_usb) return 0;

	pr_debug("%s START\n", __func__);

	if (rtk_usb->power_ctrl_reg.usb_ctrl &&
		    rtk_usb->power_ctrl_reg.usb0_sram_pwr &&
		    rtk_usb->power_ctrl_reg.usb0_sram_pwr_ctrl &&
		    rtk_usb->power_ctrl_reg.usb1_sram_pwr &&
		    rtk_usb->power_ctrl_reg.usb1_sram_pwr_ctrl) {
		void __iomem *usb_ctrl =
			    ioremap(rtk_usb->power_ctrl_reg.usb_ctrl, 0x4);
		void __iomem *usb0_sram_pwr =
			    ioremap(rtk_usb->power_ctrl_reg.usb0_sram_pwr, 0x4);
		void __iomem *usb0_sram_pwr_ctrl =
			    ioremap(rtk_usb->power_ctrl_reg.usb0_sram_pwr_ctrl, 0x4);
		void __iomem *usb1_sram_pwr =
			    ioremap(rtk_usb->power_ctrl_reg.usb1_sram_pwr, 0x4);
		void __iomem *usb1_sram_pwr_ctrl =
			   ioremap(rtk_usb->power_ctrl_reg.usb1_sram_pwr_ctrl, 0x4);

		pr_info("%s power_%s ([0x%x=0x%08x)\n", __func__, power_on?"on":"off",
			    rtk_usb->power_ctrl_reg.usb_ctrl, readl(usb_ctrl));

		if (power_on) {
			pr_debug("%s power_on\n", __func__);

			pr_debug("set usb_power_domain/p0 on\n");
#if 1
			/* set power gating control */
				writel((BIT(0) | BIT(4) | BIT(6)) |
				     readl(usb_ctrl), usb_ctrl);
			/* port0-port2 sram power */
			//writel(0, usb0_sram_pwr);
			writel(0x00000f00, usb0_sram_pwr_ctrl);
			/* port3 sram power */
			if (get_rtd_chip_id() == CHIP_ID_RTD1296) {
				pr_info("set usb_power_domain/p3 on\n");
				writel((BIT(1) | BIT(5)) |
				     readl(usb_ctrl), usb_ctrl);
				//writel(0, usb1_sram_pwr);
				if (get_rtd_chip_revision() < RTD_CHIP_A01)
					writel(0x00000f05, usb1_sram_pwr_ctrl);
				else
					writel(0x00000f00, usb1_sram_pwr_ctrl);
			}
			/* disable isolation cell */
			writel(~(BIT(8) | BIT(9)) & readl(usb_ctrl), usb_ctrl);
#else
			__power_control_set_power("pctrl_usb_p0_mac", 1);
			__power_control_set_power("pctrl_usb_p0_phy", 1);
			__power_control_set_power("pctrl_usb_p0_iso", 0);
			if (get_rtd_chip_id() == CHIP_ID_RTD1296) {
				pr_info("set usb_power_domain/p3 on\n");
				__power_control_set_power("pctrl_usb_p3_phy", 1);
				__power_control_set_power("pctrl_usb_p3_mac", 1);
				__power_control_set_power("pctrl_usb_p3_iso", 0);
			}
#endif
		} else {
			pr_debug("%s power_off\n", __func__);
			__isolate_phy_from_a_to_d(rtk_usb);
			if (rtk_usb->usb_power_cut &&
				    get_rtd_chip_revision() >= RTD_CHIP_B00) {
				writel((BIT(8) | BIT(9)) | readl(usb_ctrl), usb_ctrl);
				// port0-port2 sram
				writel(0, usb0_sram_pwr);
				writel(0x00000f01, usb0_sram_pwr_ctrl);
				// port3 sram
				writel(0, usb1_sram_pwr);
				if (get_rtd_chip_revision() < RTD_CHIP_A01)
					writel(0x00000f06, usb1_sram_pwr_ctrl);
				else
					writel(0x00000f01, usb1_sram_pwr_ctrl);

				writel(~(BIT(0) | BIT(1) | BIT(4) | BIT(5) |BIT(6)) &
				     readl(usb_ctrl), usb_ctrl);
			}
		}
		pr_info("set power_domain %s ([0x%x]=0x%08x)\n", power_on?"on":"off",
			    rtk_usb->power_ctrl_reg.usb_ctrl, readl(usb_ctrl));
		iounmap(usb_ctrl);
		iounmap(usb0_sram_pwr);
		iounmap(usb0_sram_pwr_ctrl);
		iounmap(usb1_sram_pwr);
		iounmap(usb1_sram_pwr_ctrl);
	}
	pr_debug("%s END\n", __func__);

	return 0;
}

int rtk_usb_port_suspend_resume(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool is_suspend)
{
	void __iomem *reg_u3_port;
	void __iomem *reg_u2_port;

	if (!rtk_usb) return 0;

	pr_debug("%s START\n", __func__);
	switch (port_num) {
	case USB_PORT_0:
		pr_debug("set port 0 phy suspend\n");
		if (rtk_usb->power_ctrl_reg.p0_gusb3pipectl) {
			reg_u3_port = ioremap(rtk_usb->power_ctrl_reg.p0_gusb3pipectl, 0x4);
			if (is_suspend)
				writel(readl(reg_u3_port) | BIT(17), reg_u3_port);
			else
				writel(readl(reg_u3_port) & ~BIT(17), reg_u3_port);
			iounmap(reg_u3_port);
		}
		if (rtk_usb->power_ctrl_reg.p0_gusb2phycfg) {
			reg_u2_port = ioremap(rtk_usb->power_ctrl_reg.p0_gusb2phycfg, 0x4);
			if (is_suspend)
				writel(readl(reg_u2_port) | BIT(6), reg_u2_port);
			else
				writel(readl(reg_u2_port) & ~BIT(6), reg_u2_port);
			iounmap(reg_u2_port);
		}
	break;
	case USB_PORT_1:
		pr_debug("set port 1 phy suspend\n");
		if (rtk_usb->power_ctrl_reg.p1_gusb3pipectl) {
			reg_u3_port = ioremap(rtk_usb->power_ctrl_reg.p1_gusb3pipectl, 0x4);
			writel(readl(reg_u3_port) | BIT(17), reg_u3_port);
			iounmap(reg_u3_port);
		}
		if (rtk_usb->power_ctrl_reg.p1_gusb2phycfg) {
			reg_u2_port = ioremap(rtk_usb->power_ctrl_reg.p1_gusb2phycfg, 0x4);
			writel(readl(reg_u2_port) | BIT(6), reg_u2_port);
			iounmap(reg_u2_port);
		}
	break;
	case USB_PORT_2:
		pr_debug("TODO set port 2 phy suspend\n");
	break;
	case USB_PORT_3:
		pr_debug("set port 3 phy suspend\n");
		if (rtk_usb->power_ctrl_reg.p3_gusb3pipectl) {
			reg_u3_port = ioremap(rtk_usb->power_ctrl_reg.p3_gusb3pipectl, 0x4);
			writel(readl(reg_u3_port) | BIT(17), reg_u3_port);
			iounmap(reg_u3_port);
		}
		if (rtk_usb->power_ctrl_reg.p3_gusb2phycfg) {
			reg_u2_port = ioremap(rtk_usb->power_ctrl_reg.p3_gusb2phycfg, 0x4);
			writel(readl(reg_u2_port) | BIT(6), reg_u2_port);
			iounmap(reg_u2_port);
		}
	break;
	default:
		pr_err("Error port num %d\n", port_num);
	}
	pr_debug("%s END\n", __func__);
	return 0;
}

struct rtk_usb *rtk_usb_soc_init(struct device_node *sub_node)
{
	if (!rtk_usb)
		rtk_usb = kzalloc(sizeof(struct rtk_usb), GFP_KERNEL);

	pr_debug("%s START\n", __func__);
	if (sub_node) {
		pr_debug("%s sub_node %s\n", __func__, sub_node->name);
		of_property_read_u32(sub_node,
			    "usb_ctrl", &rtk_usb->power_ctrl_reg.usb_ctrl);
		/* Port 0~2 */
		of_property_read_u32(sub_node,
			    "usb0_sram_pwr", &rtk_usb->power_ctrl_reg.usb0_sram_pwr);
		of_property_read_u32(sub_node,
			    "usb0_sram_pwr_ctrl",
			    &rtk_usb->power_ctrl_reg.usb0_sram_pwr_ctrl);
		/* Port 3 */
		of_property_read_u32(sub_node,
			    "usb1_sram_pwr", &rtk_usb->power_ctrl_reg.usb1_sram_pwr);
		of_property_read_u32(sub_node,
			    "usb1_sram_pwr_ctrl",
			    &rtk_usb->power_ctrl_reg.usb1_sram_pwr_ctrl);

		of_property_read_u32(sub_node,
			    "p0_l4_icg", &rtk_usb->power_ctrl_reg.p0_l4_icg);
		of_property_read_u32(sub_node,
			    "p1_l4_icg", &rtk_usb->power_ctrl_reg.p1_l4_icg);
		of_property_read_u32(sub_node,
			    "p2_l4_icg", &rtk_usb->power_ctrl_reg.p2_l4_icg);
		of_property_read_u32(sub_node,
			    "p3_l4_icg", &rtk_usb->power_ctrl_reg.p3_l4_icg);

		/* for power cut */
		of_property_read_u32(sub_node,
			    "usb_phy_ctrl", &rtk_usb->power_ctrl_reg.usb_phy_ctrl);

		of_property_read_u32(sub_node,
			    "p0_utmi_reset", &rtk_usb->power_ctrl_reg.p0_utmi_reset);
		of_property_read_u32(sub_node,
			    "p1_utmi_reset", &rtk_usb->power_ctrl_reg.p1_utmi_reset);
		of_property_read_u32(sub_node,
			    "p2_utmi_reset", &rtk_usb->power_ctrl_reg.p2_utmi_reset);
		of_property_read_u32(sub_node,
			    "p3_utmi_reset", &rtk_usb->power_ctrl_reg.p3_utmi_reset);

		of_property_read_u32(sub_node,
			    "p0_pipe_reset", &rtk_usb->power_ctrl_reg.p0_pipe_reset);
		of_property_read_u32(sub_node,
			    "p1_pipe_reset", &rtk_usb->power_ctrl_reg.p1_pipe_reset);
		of_property_read_u32(sub_node,
			    "p2_pipe_reset", &rtk_usb->power_ctrl_reg.p2_pipe_reset);
		of_property_read_u32(sub_node,
			    "p3_pipe_reset", &rtk_usb->power_ctrl_reg.p3_pipe_reset);

		/* for suspend */
		of_property_read_u32(sub_node,
			    "p0_gusb2phycfg", &rtk_usb->power_ctrl_reg.p0_gusb2phycfg);
		of_property_read_u32(sub_node,
			    "p0_gusb3pipectl", &rtk_usb->power_ctrl_reg.p0_gusb3pipectl);

		of_property_read_u32(sub_node,
			    "p1_gusb2phycfg", &rtk_usb->power_ctrl_reg.p1_gusb2phycfg);
		of_property_read_u32(sub_node,
			    "p1_gusb3pipectl", &rtk_usb->power_ctrl_reg.p1_gusb3pipectl);

		of_property_read_u32(sub_node,
			    "p2_gusb2phycfg", &rtk_usb->power_ctrl_reg.p2_gusb2phycfg);
		of_property_read_u32(sub_node,
			    "p2_gusb3pipectl", &rtk_usb->power_ctrl_reg.p2_gusb3pipectl);

		of_property_read_u32(sub_node,
			    "p3_gusb2phycfg", &rtk_usb->power_ctrl_reg.p3_gusb2phycfg);
		of_property_read_u32(sub_node,
			    "p3_gusb3pipectl", &rtk_usb->power_ctrl_reg.p3_gusb3pipectl);

		of_property_read_u32(sub_node,
			    "usb_charger", &rtk_usb->power_ctrl_reg.usb_charger);

		if (of_property_read_bool(sub_node, "usb_power_cut"))
			rtk_usb->usb_power_cut = true;
		else
			rtk_usb->usb_power_cut = false;

	}
	pr_debug("%s END\n", __func__);

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
