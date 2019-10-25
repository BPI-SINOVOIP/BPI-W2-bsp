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
#include <linux/of_platform.h>
#include <linux/reset.h>
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
		u32 drd_wrap_base; /* 0x98013200 */
		u32 u3host_wrap_base; /* 0x98013e00 */
		u32 drd_u3_portsc; /* 0x98020430 */
		u32 drd_u3_sus_en; /* 0x980282c0 */
		u32 u3host_u3_sus_en; /*0x980582c0 */
	} type_c;
};

static struct rtk_usb *rtk_usb;

#define disable_cc 0x0
#define enable_cc1 0x1
#define enable_cc2 0x2

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

int rtk_usb_iso_power_ctrl(struct rtk_usb *rtk_usb,
	    bool power_on)
{
	struct platform_device *pdev;
	struct device_node *node;
	struct device *dev;
	struct reset_control *reset_u2phy0;
	struct reset_control *reset_u2phy1;
	struct reset_control *reset_u2phy2;
	struct reset_control *reset_u2phy3;
	struct reset_control *reset_u3phy0;
	struct reset_control *reset_u3phy1;
	struct reset_control *reset_usb_apply;

	if (!rtk_usb)
		return 0;

	pr_debug("%s START power %s\n", __func__, power_on?"on":"off");

	node = of_find_compatible_node(NULL, NULL,
		    "Realtek,usb-manager");
	if (node != NULL)
		pdev = of_find_device_by_node(node);
	if (pdev != NULL) {
		dev = &pdev->dev;
	} else {
		pr_err("%s ERROR no usb-manager", __func__);
		return -ENODEV;
	}

	/* GET reset controller */
	reset_u2phy0 = USB_reset_get(dev, "u2phy0");
	reset_u2phy1 = USB_reset_get(dev, "u2phy1");
	reset_u2phy2 = USB_reset_get(dev, "u2phy2");
	reset_u2phy3 = USB_reset_get(dev, "u2phy3");

	reset_u3phy0 = USB_reset_get(dev, "u3phy0");
	reset_u3phy1 = USB_reset_get(dev, "u3phy1");

	reset_usb_apply = USB_reset_get(dev, "apply");

	if (rtk_usb->usb_power_cut) {
		if (power_on) {
			// Enable usb phy reset
			/* DEASSERT: set rstn bit to 1 */
			pr_debug("usb power cut No set phy reset by rtk_usb\n");
		} else {
			pr_debug("usb power cut set phy reset to 0\n");
			USB_reset_assert(reset_u2phy0);
			USB_reset_assert(reset_u2phy1);
			USB_reset_assert(reset_u2phy2);
			USB_reset_assert(reset_u2phy3);
			USB_reset_assert(reset_u3phy0);
			USB_reset_assert(reset_u3phy1);

			USB_reset_assert(reset_usb_apply);
		}
	}
	pr_debug("Realtek RTD16xx USB power %s OK\n", power_on?"on":"off");

	USB_reset_put(reset_u2phy0);
	USB_reset_put(reset_u2phy1);
	USB_reset_put(reset_u2phy2);
	USB_reset_put(reset_u2phy3);

	USB_reset_put(reset_u3phy0);
	USB_reset_put(reset_u3phy1);

	USB_reset_put(reset_usb_apply);

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
	void __iomem *drd_wrap_base, *drd_cc_setting;
	void __iomem *u3host_wrap_base, *u3host_mac_ctrl;
	int val_u3_tc_mode, val_u3host_mac_ctrl;

	if (!rtk_usb->type_c.drd_wrap_base ||
		    !rtk_usb->type_c.u3host_wrap_base ||
		    !rtk_usb->type_c.drd_u3_portsc ||
		    !rtk_usb->type_c.drd_u3_sus_en ||
		    !rtk_usb->type_c.u3host_u3_sus_en) {
		pr_err("%s: Error! No RTD1619 type_c reg\n", __func__);
		return -1;
	}

	drd_wrap_base = ioremap(rtk_usb->type_c.drd_wrap_base, 0x200);
	drd_cc_setting = drd_wrap_base + 0x194;
	u3host_wrap_base = ioremap(rtk_usb->type_c.u3host_wrap_base, 0x200);
	u3host_mac_ctrl = u3host_wrap_base + 0x60;
	val_u3_tc_mode = BIT(0) | readl(drd_cc_setting);
	val_u3host_mac_ctrl = BIT(8) | readl(u3host_mac_ctrl);

	writel(val_u3_tc_mode, drd_cc_setting);
	writel(val_u3host_mac_ctrl, u3host_mac_ctrl);

	pr_info("%s: set type_c mode (0x%x) and disable u3host u3 port (0x%x) "
		    "for RTD1619\n",
		    __func__, readl(drd_cc_setting), readl(u3host_mac_ctrl));

	iounmap(drd_wrap_base);
	iounmap(u3host_mac_ctrl);
}

int rtk_type_c_plug_config(struct rtk_usb *rtk_usb, int dr_mode, int cc)
{
	void __iomem *drd_wrap_base, *u3host_wrap_base;
	void __iomem *drd_u3phy_pipe_clock, *u3host_u3phy_pipe_clock;
	void __iomem *drd_pclk_u3phy, *u3host_pclk_u3phy;
	void __iomem *drd_tc_mux_ctrl;
	void __iomem *drd_u3_portsc;
	void __iomem *drd_u3_sus_en, *u3host_u3_sus_en;
	int wait_count = 1000;
	int drd_u3_sus_en_status_save, u3host_u3_sus_en_status_save;

	if (!rtk_usb->type_c.drd_wrap_base ||
		    !rtk_usb->type_c.u3host_wrap_base ||
		    !rtk_usb->type_c.drd_u3_portsc ||
		    !rtk_usb->type_c.drd_u3_sus_en ||
		    !rtk_usb->type_c.u3host_u3_sus_en) {
		pr_err("%s: Error! No RTD1619 type_c reg\n", __func__);
		return -1;
	}

	drd_wrap_base = ioremap(rtk_usb->type_c.drd_wrap_base, 0x200);
	u3host_wrap_base = ioremap(rtk_usb->type_c.u3host_wrap_base, 0x100);
	drd_u3phy_pipe_clock = drd_wrap_base + 0xc;
	u3host_u3phy_pipe_clock = u3host_wrap_base + 0xc;
	drd_pclk_u3phy = drd_wrap_base + 0x84;
	u3host_pclk_u3phy = u3host_wrap_base + 0x84;
	drd_tc_mux_ctrl =  drd_wrap_base + 0x194;
	drd_u3_portsc = ioremap(rtk_usb->type_c.drd_u3_portsc, 0x4);
	drd_u3_sus_en = ioremap(rtk_usb->type_c.drd_u3_sus_en, 0x4);
	u3host_u3_sus_en = ioremap(rtk_usb->type_c.u3host_u3_sus_en, 0x4);
	drd_u3_sus_en_status_save = readl(drd_u3_sus_en) & BIT(17);
	u3host_u3_sus_en_status_save = readl(u3host_u3_sus_en) & BIT(17);

	pr_info("%s: dr_mode=%d cc=0x%x\n", __func__, dr_mode, cc);
	/* disable u3phy suspend */
	writel(~BIT(17) & readl(drd_u3_sus_en), drd_u3_sus_en);
	writel(~BIT(17) & readl(u3host_u3_sus_en), u3host_u3_sus_en);

	/* check u3phy clock if resume */
	while (wait_count-- > 0 && (!(readl(drd_pclk_u3phy) & BIT(19)) ||
		!(readl(u3host_pclk_u3phy) & BIT(19)))) {
		pr_info("wait drd/u3host u3phy clock\n");
		mdelay(1);
	};

	if (wait_count < 0) {
		pr_err("wait u3phy clock fail. "
			    "drd=0x%x u3host=0x%x\n",
			    readl(drd_pclk_u3phy), readl(u3host_pclk_u3phy));
	}

	if (cc == disable_cc) {
		pr_info("%s: disable drd u3phy for CHIP_ID_RTD1619\n",
			__func__);
	} else {
		/* push drd u3 port status to disable */
		writel(BIT(1) | readl(drd_u3_portsc), drd_u3_portsc);
		pr_info("%s: disable drd_u3_portsc=0x%x\n",
			    __func__, readl(drd_u3_portsc));

		/* disable u3phy clock */
		writel(~BIT(1) & readl(drd_u3phy_pipe_clock), drd_u3phy_pipe_clock);
		writel(~BIT(1) & readl(u3host_u3phy_pipe_clock),
			    u3host_u3phy_pipe_clock);

		if (cc == enable_cc1) {
			writel(~BIT(1) & readl(drd_tc_mux_ctrl), drd_tc_mux_ctrl);
			pr_info("%s: enable_cc1 drd u3phy for "
				    "CHIP_ID_RTD1619\n", __func__);
		} else if (cc == enable_cc2) {
			writel(BIT(1) | readl(drd_tc_mux_ctrl), drd_tc_mux_ctrl);
			pr_info("%s: enable_cc2 drd u3phy for "
				    "CHIP_ID_RTD1619\n", __func__);
		}
		/* enable u3phy clock */
		writel(BIT(1) | readl(drd_u3phy_pipe_clock), drd_u3phy_pipe_clock);
		writel(BIT(1) | readl(u3host_u3phy_pipe_clock),
			    u3host_u3phy_pipe_clock);

		/* push drd u3 port status to rxDetect */
		writel(BIT(16) | 0xA0 |
			    (readl(drd_u3_portsc) & (~0x1E0)),
			    drd_u3_portsc);
		pr_info("%s: drd_u3_portsc=0x%x\n",
			    __func__, readl(drd_u3_portsc));
	}

		/* enable u3phy suspend */
	pr_info("u3_sus_en_status_save drd=0x%x u3host=0x%x\n",
		    drd_u3_sus_en_status_save, u3host_u3_sus_en_status_save);
	writel(drd_u3_sus_en_status_save | readl(drd_u3_sus_en), drd_u3_sus_en);
	writel(u3host_u3_sus_en_status_save | readl(u3host_u3_sus_en),
		    u3host_u3_sus_en);

	iounmap(drd_u3_portsc);
	iounmap(drd_u3_sus_en);
	iounmap(u3host_u3_sus_en);
	iounmap(u3host_wrap_base);
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
		pr_debug("%s sub_node %s\n", __func__, sub_node->name);

		of_property_read_u32(sub_node,
			    "drd_wrap_base", &rtk_usb->type_c.drd_wrap_base);
		of_property_read_u32(sub_node,
			    "u3host_wrap_base", &rtk_usb->type_c.u3host_wrap_base);
		of_property_read_u32(sub_node,
			    "drd_u3_portsc", &rtk_usb->type_c.drd_u3_portsc);
		of_property_read_u32(sub_node,
			    "drd_u3_sus_en", &rtk_usb->type_c.drd_u3_sus_en);
		of_property_read_u32(sub_node,
			    "u3host_u3_sus_en", &rtk_usb->type_c.u3host_u3_sus_en);
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
