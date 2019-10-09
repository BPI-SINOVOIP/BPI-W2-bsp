/**
 *  * dwc3-rtk-type_c.c - Realtek DWC3 Type C driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#undef DEBUG

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/usb/otg.h>
#include <linux/syscalls.h>
#include <linux/suspend.h>
#include <soc/realtek/rtk_chip.h>

#include "core.h"
#include "dwc3-rtk-drd.h"

#ifdef CONFIG_DUAL_ROLE_USB_INTF
#include <linux/usb/class-dual-role.h>
#endif

#ifdef CONFIG_USB_TYPE_C_RTK_RTS5400
extern bool rtk_rts5400_is_UFP_attached(void);
extern bool rtk_rts5400_is_enabled(void);
extern int rtk_rts5400_set_type_c_soft_reset(void);
#endif

extern int rtk_usb_type_c_power_on_off(struct device *usb_dev, bool on);
extern int rtk_usb_set_type_c_switch_gpio(struct device *type_c_dev, bool high);

struct type_c_data {
	void __iomem *wrap_base;
	void __iomem *type_c_reg_base;
	struct device *dev;

	enum rtd_chip_id chip_id;
	enum rtd_chip_revision chip_revision;

	/*GPIO*/
	unsigned int rd_ctrl_gpio;

	/*Parameters*/
	u32 cc1_rp;
	u32 cc1_rp_code;
	u32 cc1_rd_code;
	u32 cc1_vref_ufp;
	u32 cc1_vref_dfp_usb;
	u32 cc1_vref_dfp_1_5;
	u32 cc1_vref_dfp_3_0;
	u32 cc2_rp;
	u32 cc2_rp_code;
	u32 cc2_rd_code;
	u32 cc2_vref_ufp;
	u32 cc2_vref_dfp_usb;
	u32 cc2_vref_dfp_1_5;
	u32 cc2_vref_dfp_3_0;
	u32 debounce_val;// 1b,1us 7f,4.7us
	int rd_config;
#define INTERNAL_Rd 1
#define EXTERNAL_Rd 0
	int cc_dfp_mode;

	struct dwc3 *dwc;
	int dwc3_mode;
	int cur_mode;
	bool is_drd_mode;

	// type_c state
	int connect_change;
#define CONNECT_CHANGE 1
#define CONNECT_NO_CHANGE 0
	int in_host_mode;
#define IN_HOST_MODE 1
#define IN_DEVICE_MODE 0
	int is_attach;
#define IN_ATTACH 1
#define TO_ATTACH 1
#define IN_DETACH 0
#define TO_DETACH 0
	int at_cc1;
#define AT_CC1 1
#define AT_CC2 0

	u32 int_status;
	u32 cc_status;
	spinlock_t		lock;
	struct delayed_work   delayed_work;

	struct work_struct start_work;

	/* boot time check device mode transfer to host mode*/
	bool check_at_boot;
	int boot_check_time;
	struct delayed_work boot_check_work;

	bool debug;
#ifdef CONFIG_DYNAMIC_DEBUG
	struct dentry		*debug_dir;
#endif
#ifdef CONFIG_DUAL_ROLE_USB_INTF
	struct dual_role_phy_instance *drp;
#endif
};

// wrapper register offset for USB2 PHY
#define USB2_PHY_reg  0x70
#define USB2_PHY_SWITCH_MASK 0x707
#define USB2_PHY_SWITCH_DEVICE 0x0
#define USB2_PHY_SWITCH_HOST 0x606

// Type C register offset
#define USB_TYPEC_CTRL_CC1_0 0x0
#define USB_TYPEC_CTRL_CC1_1 0x4
#define USB_TYPEC_CTRL_CC2_0 0x8
#define USB_TYPEC_CTRL_CC2_1 0xC
#define USB_TYPEC_STS        0x10
#define USB_TYPEC_CTRL       0x14
#define USB_DBUS_PWR_CTRL    0x18

// Bit mapping USB_TYPEC_CTRL_CC1_0 and USB_TYPEC_CTRL_CC2_0
#define EN_EXTERNAL_RD BIT(29) /* only for rtd1395 */
#define EN_SWITCH BIT(29)
#define Txout_sel BIT(28)
#define Rxin_sel BIT(27)
#define SWITCH_MASK (EN_SWITCH | Txout_sel | Rxin_sel)
#define enable_cc1 EN_SWITCH
#define enable_cc2 (EN_SWITCH | Txout_sel | Rxin_sel)
#define disable_cc ~SWITCH_MASK
#define rp4pk_code(val) ((0x1f & val) << 22)
#define code_rp4pk(val) ((val >> 22) & 0x1f)
#define rp36k_code(val) ((0x1f & val) << 17)
#define code_rp36k(val) ((val >> 17) & 0x1f)
#define rp12k_code(val) ((0x1f & val) << 12)
#define code_rp12k(val) ((val >> 12) & 0x1f)
#define rd_code(val) ((0x1f & val) << 7)
#define code_rd(val) ((val >> 7) & 0x1f)
#define cc_mode(val) ((0x3 & val) << 5)
#define En_rp4p7k BIT(4)
#define En_rp36k BIT(3)
#define En_rp12k BIT(2)
#define En_rd BIT(1)
#define En_cc_det BIT(0)

#define CC_MODE_UFP 0x0
#define CC_MODE_DFP_USB 0x1
#define CC_MODE_DFP_1_5 0x2
#define CC_MODE_DFP_3_0 0x3

// Bit mapping USB_TYPEC_CTRL_CC1_1 and USB_TYPEC_CTRL_CC2_1
#define vref_2p6v(val) ((0x7 & val) << 26)
#define vref_1p23v(val) ((0xf & val) << 22)
#define vref_0p8v(val) ((0xf & val) << 18)
#define vref_0p66v(val) ((0xf & val) << 14)
#define vref_0p4v(val) ((0x7 & val) << 11)
#define vref_0p2v(val) ((0x7 & val) << 8)
#define vref_1_1p6v(val) ((0xf & val) << 4)
#define vref_0_1p6v(val) ((0xf & val) << 0)

#define decode_2p6v(val) ((val >> 26) & 0x7)
#define decode_1p23v(val) ((val >> 22) & 0xf)
#define decode_0p8v(val) ((val >> 18) & 0xf)
#define decode_0p66v(val) ((val >> 14) & 0xf)
#define decode_0p4v(val) ((val >> 11) & 0x7)
#define decode_0p2v(val) ((val >> 8) & 0x7)
#define decode_1_1p6v(val) ((val >> 4) & 0xf)
#define decode_0_1p6v(val) ((val >> 0) & 0xf)
// Bit mapping USB_TYPEC_STS
#define det_sts 0x7
#define cc1_det_sts (det_sts)
#define cc2_det_sts (det_sts << 3)
#define det_sts_ra 0x1
#define det_sts_rd 0x3
#define det_sts_rp 0x1
#define cc1_det_sts_ra (det_sts_ra)
#define cc1_det_sts_rd (det_sts_rd)
#define cc1_det_sts_rp (det_sts_rp)
#define cc2_det_sts_ra (det_sts_ra << 3)
#define cc2_det_sts_rd (det_sts_rd << 3)
#define cc2_det_sts_rp (det_sts_rp << 3)

// Bit mapping USB_TYPEC_CTRL
#define cc2_int_en BIT(11)
#define cc1_int_en BIT(10)
#define cc2_int_sts BIT(9)
#define cc1_int_sts BIT(8)
#define debounce_time_MASK 0xff
#define ENABLE_TYPE_C_DETECT (cc1_int_en | cc2_int_en)
#define all_cc_int_sts (cc1_int_sts | cc2_int_sts)

// Parameter
#define DETECT_TIME 50 //ms

static void enable_writel(int value, void __iomem *addr)
{
	writel(value | readl(addr),  addr);
}

static void disable_writel(int value, void __iomem *addr)
{
	writel(~value & readl(addr),  addr);
}

static init_type_c_mode(struct type_c_data *type_c)
{
	if (type_c->chip_id == CHIP_ID_RTD1619) {
		void __iomem *drd_wrap_base = type_c->wrap_base;
		void __iomem *u3host_u3port_dis = ioremap(0x98013e60, 0x4);
		int cc_set_offect = 0x194;

		dev_info(type_c->dev, "%s: disable u3host u3phy for CHIP_ID_RTD1619\n",
				    __func__);
		enable_writel(BIT(8), u3host_u3port_dis);
		enable_writel(BIT(0), drd_wrap_base + cc_set_offect);

		iounmap(u3host_u3port_dis);
	}
}

static void switch_type_c_plug_side(struct type_c_data *type_c, int cc)
{
	if ((type_c->chip_id & 0xFFF0) == CHIP_ID_RTD129X) {
		void __iomem *type_c_reg_base = type_c->type_c_reg_base;
		int value;

		value = (~SWITCH_MASK & readl(type_c_reg_base));
		value |= cc;
		writel(value, type_c_reg_base);
	} else if (type_c->chip_id == CHIP_ID_RTD1619) {
		void __iomem *drd_wrap_base = type_c->wrap_base;
		void __iomem *u3host_wrap_base = ioremap(0x98013e00, 0xf);
		int clock_offset = 0xc;
		int cc_set_offect = 0x194;

		if (cc == disable_cc) {
			dev_info(type_c->dev, "%s: disable drd u3phy for CHIP_ID_RTD1619\n",
				__func__);
		} else {
			disable_writel(BIT(1), drd_wrap_base + clock_offset);
			disable_writel(BIT(1), u3host_wrap_base + clock_offset);
			if (cc == enable_cc1) {
				disable_writel(BIT(1), drd_wrap_base + cc_set_offect);
				dev_info(type_c->dev, "%s: enable_cc1 drd u3phy for "
					    "CHIP_ID_RTD1619\n", __func__);
			} else if (cc == enable_cc2) {
				enable_writel(BIT(1), drd_wrap_base + cc_set_offect);
				dev_info(type_c->dev, "%s: enable_cc2 drd u3phy for "
					    "CHIP_ID_RTD1619\n", __func__);
			}
			enable_writel(BIT(1), drd_wrap_base + clock_offset);
			enable_writel(BIT(1), u3host_wrap_base + clock_offset);
		}
		iounmap(u3host_wrap_base);
	}
}

static void switch_dwc3_mode(struct type_c_data *type_c, int dr_mode)
{
	if (!type_c->is_drd_mode)
		dr_mode = type_c->dwc3_mode;
	dev_dbg(type_c->dev, "%s START....", __func__);

	type_c->cur_mode = dr_mode;
	type_c->dwc->dr_mode = dr_mode;

	switch (dr_mode) {
	case USB_DR_MODE_PERIPHERAL:
		dev_info(type_c->dev, "%s dr_mode=USB_DR_MODE_PERIPHERAL\n",
			    __func__);
#ifdef CONFIG_USB_RTK_DWC3_DRD_MODE
		dwc3_drd_to_device(type_c->dwc);
#else
		dev_err(type_c->dev, "NO add config CONFIG_USB_RTK_DWC3_DRD_MODE");
#endif
		mdelay(10);
		writel(USB2_PHY_SWITCH_DEVICE |
			    (~USB2_PHY_SWITCH_MASK &
			    readl(type_c->wrap_base + USB2_PHY_reg)),
			    type_c->wrap_base + USB2_PHY_reg);

		break;
	case USB_DR_MODE_HOST:
		dev_info(type_c->dev, "%s dr_mode=USB_DR_MODE_HOST\n", __func__);
#ifdef CONFIG_USB_RTK_DWC3_DRD_MODE
		dwc3_drd_to_host(type_c->dwc);
#else
		dev_err(type_c->dev, "NO add config CONFIG_USB_RTK_DWC3_DRD_MODE");
#endif
		mdelay(10);
		writel(USB2_PHY_SWITCH_HOST |
			    (~USB2_PHY_SWITCH_MASK &
			    readl(type_c->wrap_base + USB2_PHY_reg)),
			    type_c->wrap_base + USB2_PHY_reg);
		break;
	default:
		dev_info(type_c->dev, "%s dr_mode=%d\n", __func__, dr_mode);
		//mdelay(10);
#ifdef CONFIG_USB_RTK_DWC3_DRD_MODE
		dwc3_drd_to_stop_all(type_c->dwc);
#else
		dev_err(type_c->dev, "NO add config CONFIG_USB_RTK_DWC3_DRD_MODE");
#endif
	}
	dev_dbg(type_c->dev, "%s END....", __func__);
}

/* device attached / detached */
int device_attached(struct type_c_data *type_c, u32 enable_cc)
{
	struct device		*dev = type_c->dev;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;

	cancel_delayed_work(&type_c->delayed_work);

	switch_dwc3_mode(type_c, USB_DR_MODE_HOST);

	switch_type_c_plug_side(type_c, enable_cc);

	dev_info(dev, "%s to enable power\n", __func__);
	if (rtk_usb_type_c_power_on_off(dev, true))
		dev_err(dev, "%s to enable type c power Fail\n", __func__);
	else
		dev_dbg(dev, "%s to enable type c power OK\n", __func__);

	if (rtk_usb_set_type_c_switch_gpio(dev, true))
		dev_info(dev, "%s to set switch_ctrl_gpio GPIO to high "
			    "for 1395 QA board\n", __func__);

	enable_writel(ENABLE_TYPE_C_DETECT, type_c_reg_base + USB_TYPEC_CTRL);
	return 0;
}

int device_detached(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;

	disable_writel(ENABLE_TYPE_C_DETECT, type_c_reg_base + USB_TYPEC_CTRL);

	dev_info(dev, "%s to disable power\n", __func__);
	if (rtk_usb_type_c_power_on_off(dev, false))
		dev_err(dev, "%s to disable type c power Fail\n", __func__);
	else
		dev_dbg(dev, "%s to disable type c power OK\n", __func__);

	switch_type_c_plug_side(type_c, disable_cc);

	msleep(1000);

	switch_dwc3_mode(type_c, 0);

	dev_dbg(dev, "%s start new schedule_delayed_work\n", __func__);
	schedule_delayed_work(&type_c->delayed_work,
			msecs_to_jiffies(DETECT_TIME));
	dev_dbg(dev, "%s ok new schedule_delayed_work\n", __func__);

	return 0;
}

/* host connect /disconnect*/
int host_connected(struct type_c_data *type_c, u32 enable_cc)
{
	struct device		*dev = type_c->dev;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;

	dev_info(dev, "%s: a Host connect\n", __func__);

	cancel_delayed_work(&type_c->delayed_work);

	switch_dwc3_mode(type_c, USB_DR_MODE_PERIPHERAL);

	switch_type_c_plug_side(type_c, enable_cc);

	enable_writel(ENABLE_TYPE_C_DETECT, type_c_reg_base + USB_TYPEC_CTRL);
	return 0;
}

int host_disconnected(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;

	dev_info(dev, "%s: a Host disconnect\n", __func__);

	disable_writel(ENABLE_TYPE_C_DETECT, type_c_reg_base + USB_TYPEC_CTRL);

	switch_type_c_plug_side(type_c, disable_cc);

	msleep(1000);

	switch_dwc3_mode(type_c, 0);

	schedule_delayed_work(&type_c->delayed_work, msecs_to_jiffies(DETECT_TIME));

	return 0;
}

/* detect host device switch */
static int detect_device(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	//struct device_node	*node = dev->of_node;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;
	unsigned int gpio = type_c->rd_ctrl_gpio;
	u32 cc1_config, cc2_config, default_ctrl;
	int cc_mode_sel = type_c->cc_dfp_mode;

	default_ctrl = readl(type_c_reg_base + USB_TYPEC_CTRL) & debounce_time_MASK;
	writel(default_ctrl, type_c_reg_base + USB_TYPEC_CTRL);

	disable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	disable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);

	if (gpio != -1 && gpio_is_valid(gpio)) {
		if (gpio_direction_output(gpio, 1))
			dev_err(dev, "%s ERROR rd_ctrl_gpio=1 fail\n", __func__);
	}

	switch (cc_mode_sel) {
	case CC_MODE_DFP_USB:
		writel(type_c->cc1_vref_dfp_usb, type_c_reg_base + USB_TYPEC_CTRL_CC1_1);
		writel(type_c->cc2_vref_dfp_usb, type_c_reg_base + USB_TYPEC_CTRL_CC2_1);
		break;
	case CC_MODE_DFP_1_5:
		writel(type_c->cc1_vref_dfp_1_5, type_c_reg_base + USB_TYPEC_CTRL_CC1_1);
		writel(type_c->cc2_vref_dfp_1_5, type_c_reg_base + USB_TYPEC_CTRL_CC2_1);
		break;
	case CC_MODE_DFP_3_0:
		writel(type_c->cc1_vref_dfp_3_0, type_c_reg_base + USB_TYPEC_CTRL_CC1_1);
		writel(type_c->cc2_vref_dfp_3_0, type_c_reg_base + USB_TYPEC_CTRL_CC2_1);
		break;
	default:
		dev_err(dev, "%s ERROR cc_mode_sel=%d\n", __func__, cc_mode_sel);
		break;
	}
	cc1_config = type_c->cc1_rp | type_c->cc1_rp_code | cc_mode(cc_mode_sel);
	cc2_config = type_c->cc2_rp | type_c->cc2_rp_code | cc_mode(cc_mode_sel);

	writel(cc1_config, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	writel(cc2_config, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);

	wmb();

	mdelay(1);
	enable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	enable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);

	return 0;
}

static int detect_host(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	//struct device_node	*node = dev->of_node;
	void __iomem *type_c_reg_base = type_c->type_c_reg_base;
	unsigned int gpio = type_c->rd_ctrl_gpio;
	u32 cc1_config, cc2_config, default_ctrl;
	u32 cc_rd = En_rd;

	if (type_c->check_at_boot || (type_c->rd_config == EXTERNAL_Rd)) {
		if ((type_c->chip_id & 0xFFF0) == CHIP_ID_RTD129X) {
			cc_rd = 0;
		} else {
			dev_info(dev, "%s external Rd is build on chip, "
				    "set EN_EXTERNAL_RD Bit 29\n", __func__);
			cc_rd = EN_EXTERNAL_RD;
		}
	}

	default_ctrl = readl(type_c_reg_base + USB_TYPEC_CTRL) & debounce_time_MASK;
	writel(default_ctrl, type_c_reg_base + USB_TYPEC_CTRL);

	disable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	disable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);

	writel(type_c->cc1_vref_ufp, type_c_reg_base + USB_TYPEC_CTRL_CC1_1);
	writel(type_c->cc2_vref_ufp, type_c_reg_base + USB_TYPEC_CTRL_CC2_1);

	cc1_config = cc_rd | type_c->cc1_rd_code | cc_mode(CC_MODE_UFP);
	cc2_config = cc_rd | type_c->cc2_rd_code | cc_mode(CC_MODE_UFP);

	writel(cc1_config, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	writel(cc2_config, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);

	if (cc_rd && gpio != -1 && gpio_is_valid(gpio)) {
		// use internal Rd
		if (gpio_direction_output(gpio, 1))
			dev_err(dev, "%s ERROR rd_ctrl_gpio=1 fail\n", __func__);
	} else if (gpio != -1 && gpio_is_valid(gpio)) {
		// use external Rd
		if (gpio_direction_output(gpio, 0))
			dev_err(dev, "%s ERROR rd_ctrl_gpio=0 fail\n", __func__);
	}
	wmb();

	mdelay(1);
	enable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC1_0);
	mdelay(2); // add a delay to avoid error cc2 interrupt on cc_status=0x0
	enable_writel(En_cc_det, type_c_reg_base + USB_TYPEC_CTRL_CC2_0);
	mdelay(1); // add a delay to avoid error cc2 interrupt on cc_status=0x0

	return 0;
}

int host_device_switch_detection(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	int ret = 0;
	unsigned long		flags;

	spin_lock_irqsave(&type_c->lock, flags);
	if (type_c->debug)
		dev_dbg(dev, "ENTER %s", __func__);
	if (type_c->in_host_mode) {
		type_c->in_host_mode = IN_DEVICE_MODE;
		detect_host(type_c);
		if (type_c->debug)
			dev_dbg(dev, "Now device mode $$$$");
	} else {
		type_c->in_host_mode = IN_HOST_MODE;
		detect_device(type_c);
		if (type_c->debug)
			dev_dbg(dev, "Now host mode   ####");
	}
	spin_unlock_irqrestore(&type_c->lock, flags);

	return ret;
}

int detect_type_c_state(struct type_c_data *type_c)
{
	struct device *dev = type_c->dev;
	u32 int_status, cc_status, cc_status_check;
	unsigned long		flags;

	spin_lock_irqsave(&type_c->lock, flags);

	int_status = readl(type_c->type_c_reg_base + USB_TYPEC_CTRL);
	cc_status = readl(type_c->type_c_reg_base + USB_TYPEC_STS);

	type_c->connect_change = CONNECT_NO_CHANGE;

	switch (type_c->in_host_mode) {
	case IN_HOST_MODE:
		switch (type_c->is_attach) {
		case IN_ATTACH:
			if (((cc_status & cc1_det_sts) == cc1_det_sts) &&
				    (type_c->at_cc1 == AT_CC1)) {
				dev_dbg(dev, "IN host mode and cc1 device detach "
					    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_DETACH;
				type_c->connect_change = CONNECT_CHANGE;
			} else if (((cc_status & cc2_det_sts) == cc2_det_sts) &&
				    (type_c->at_cc1 == AT_CC2)) {
				dev_dbg(dev, "IN host mode and cc2 device detach "
				    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_DETACH;
				type_c->connect_change = CONNECT_CHANGE;
			}
		break;
		case IN_DETACH:
			cc_status_check = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			if (cc_status_check != (cc1_det_sts | cc2_det_sts)) {
				if (in_interrupt()) {
					mdelay(300);
				} else {
					spin_unlock_irqrestore(&type_c->lock, flags);
					msleep(300);
					spin_lock_irqsave(&type_c->lock, flags);
				}
				cc_status_check = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			}
			if (cc_status != cc_status_check) {
				dev_warn(dev, "IN_HOST_MODE: cc_status (0x%x) != "
					    "cc_status_check (0x%x)\n",
					    cc_status, cc_status_check);
				cc_status = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			}

			if ((cc_status & cc1_det_sts) == cc1_det_sts_rd) {
				dev_dbg(dev, "IN host mode and cc1 device attach "
					    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_ATTACH;
				type_c->at_cc1 = AT_CC1;
				type_c->connect_change = CONNECT_CHANGE;
			} else if ((cc_status & cc2_det_sts) == cc2_det_sts_rd) {
				dev_dbg(dev, "In host mode and cc2 device attach "
					    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_ATTACH;
				type_c->at_cc1 = AT_CC2;
				type_c->connect_change = CONNECT_CHANGE;
			}
		break;
		default:
			dev_err(dev, "IN host_mode and error attach state (is_attach=%d)",
				    type_c->is_attach);
		}
	break;
	case IN_DEVICE_MODE:
		switch (type_c->is_attach) {
		case IN_ATTACH:
			if ((cc_status & cc1_det_sts) < cc1_det_sts_rp &&
				    type_c->at_cc1 == AT_CC1) {
				dev_dbg(dev,"IN device mode and cc1 host disconnect "
					    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_DETACH;
				type_c->connect_change = CONNECT_CHANGE;
			} else if ((cc_status & cc2_det_sts) < cc2_det_sts_rp &&
				    type_c->at_cc1 == AT_CC2) {
				dev_dbg(dev,"IN device mode and cc2 host connect "
					    "(cc_status=0x%x)", cc_status);
				type_c->is_attach = TO_DETACH;
				type_c->connect_change = CONNECT_CHANGE;
			}
		break;
		case IN_DETACH:
			cc_status_check = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			if (cc_status_check != 0x0) {
				if (in_interrupt()) {
					mdelay(300);
				} else {
					spin_unlock_irqrestore(&type_c->lock, flags);
					msleep(300);
					spin_lock_irqsave(&type_c->lock, flags);
				}
				cc_status_check = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			}
			if (cc_status != cc_status_check) {
				dev_warn(dev, "IN_DEVICE_MODE: cc_status (0x%x) != "
					    "cc_status_check (0x%x)\n",
					    cc_status, cc_status_check);
				cc_status = readl(type_c->type_c_reg_base + USB_TYPEC_STS);
			}

			if ((cc_status & cc1_det_sts) >= cc1_det_sts_rp) {
				dev_dbg(dev,"IN device mode and cc1 host connect "
					    "(cc_status=0x%x)", cc_status);
				type_c->at_cc1 = AT_CC1;
				type_c->is_attach = TO_ATTACH;
				type_c->connect_change = CONNECT_CHANGE;
			} else if ((cc_status & cc2_det_sts) >= cc2_det_sts_rp) {
				dev_dbg(dev,"IN device mode and cc2 host connect "
					    "(cc_status=0x%x)", cc_status);
				type_c->at_cc1 = AT_CC2;
				type_c->is_attach = TO_ATTACH;
				type_c->connect_change = CONNECT_CHANGE;
			}
		break;
		default:
			dev_err(dev, "IN device_mode and error attach state (is_attach=%d)",
				    type_c->is_attach);
		}
	break;
	default:
		dev_err(dev, "error host or device mode (in_host_mode=%d)",
			    type_c->in_host_mode);
	}

	type_c->int_status = int_status;
	type_c->cc_status = cc_status;

	spin_unlock_irqrestore(&type_c->lock, flags);
	return 0;
}

void host_device_switch(struct work_struct *work)
{
	struct type_c_data *type_c = container_of(work,
		    struct type_c_data, delayed_work.work);
	struct device		*dev = type_c->dev;
	unsigned long		flags;
	int connect_change = 0;
	int in_host_mode = 0;
	int is_attach = 0;
	int at_cc1 = 0;

	if (type_c->debug) dev_dbg(type_c->dev, "ENTER %s", __func__);

	if (type_c->is_attach == IN_DETACH && !type_c->connect_change) {
		if (type_c->is_drd_mode)
			host_device_switch_detection(type_c);
		detect_type_c_state(type_c);
	}

	spin_lock_irqsave(&type_c->lock, flags);
	if (type_c->connect_change) {
		connect_change = type_c->connect_change;
		in_host_mode = type_c->in_host_mode;
		is_attach = type_c->is_attach;
		at_cc1 = type_c->at_cc1;
		type_c->connect_change = CONNECT_NO_CHANGE;
	} else {
		schedule_delayed_work(&type_c->delayed_work,
			    msecs_to_jiffies(DETECT_TIME));
	}

	spin_unlock_irqrestore(&type_c->lock, flags);

	if (connect_change) {
		dev_info(dev, "%s: usb cable connection change\n", __func__);
#ifdef CONFIG_USB_TYPE_C_RTK_RTS5400
		if (type_c->check_at_boot
				&& rtk_rts5400_is_enabled()
				&& rtk_rts5400_is_UFP_attached()) {
			u32 enable_cc = at_cc1?enable_cc1:enable_cc2;
			dev_info(dev, "%s: In Device mode, role swap to Host mode\n",
				    __func__);
			switch_dwc3_mode(type_c, USB_DR_MODE_HOST);
			switch_type_c_plug_side(type_c, enable_cc);

			rtk_rts5400_set_type_c_soft_reset();

			type_c->check_at_boot = false;
		} else
#endif //CONFIG_USB_TYPE_C_RTK_RTS5400
		if (in_host_mode) {
			if (is_attach && at_cc1)
				device_attached(type_c, enable_cc1);
			else if (is_attach && !at_cc1)
				device_attached(type_c, enable_cc2);
			else
				device_detached(type_c);
		} else {
			if (is_attach && at_cc1)
				host_connected(type_c, enable_cc1);
			else if (is_attach && !at_cc1)
				host_connected(type_c, enable_cc2);
			else
				host_disconnected(type_c);
		}
		dev_err(dev, "Connection change OK: IN %s mode to %s %s at %s "
			    "(cc_status=0x%x)\n",
			    in_host_mode?"host":"device",
			    in_host_mode?
			        (is_attach?"attach":"detach"):
			        (is_attach?"connect":"disconnect"),
			    in_host_mode?"device":"host",
			    at_cc1?"cc1":"cc2", type_c->cc_status);

	}

	/* For special case, some boards use type c power and need use host mode.
	 * After 30s, We switch to host mode if in device mode but no host connect.
	 */
	if (type_c->check_at_boot) {
		if (type_c->is_drd_mode && connect_change &&
			(in_host_mode == IN_DEVICE_MODE) && is_attach) {
			dev_info(dev, "%s: In Device mode check connection at boot time\n",
				    __func__);
			schedule_delayed_work(&type_c->boot_check_work,
				    msecs_to_jiffies(type_c->boot_check_time));
		}
		type_c->check_at_boot = false;
	}
}

void boot_time_check(struct work_struct *work)
{
	struct type_c_data *type_c = container_of(work,
		    struct type_c_data, boot_check_work.work);
	struct device		*dev = type_c->dev;
	int at_cc1, in_host_mode, is_attach;
	unsigned long		flags;

	spin_lock_irqsave(&type_c->lock, flags);

	at_cc1 = type_c->at_cc1;
	in_host_mode = type_c->in_host_mode;
	is_attach = type_c->is_attach;

	spin_unlock_irqrestore(&type_c->lock, flags);

	if (type_c->is_drd_mode &&
			(in_host_mode == IN_DEVICE_MODE) && is_attach) {
		int no_host_connect = 0;
		int no_run_gadget = 0;
		u32 enable_cc = at_cc1?enable_cc1:enable_cc2;
		u32 dsts = dwc3_readl(type_c->dwc->regs, DWC3_DSTS);
		u32 dctl = dwc3_readl(type_c->dwc->regs, DWC3_DCTL);

		dev_info(dev, "%s: Device mode check DSTS=%x DCTL=%x\n", __func__,
				dsts, dctl);
		no_host_connect = (dsts & 0x0003FFF8) == BIT(17);
		no_run_gadget = (dctl & BIT(31)) == 0x0;
		if (no_host_connect || no_run_gadget) {
			switch_type_c_plug_side(type_c, disable_cc);
			mdelay(100);
			dev_info(dev, "%s: In Device mode, NO host connect at boot time "
				    "(After %dms), switch to Host mode\n",
				    __func__, type_c->boot_check_time);
			switch_dwc3_mode(type_c, USB_DR_MODE_HOST);
			switch_type_c_plug_side(type_c, enable_cc);
			/* for rtd1395 lion-skin*/
			if (rtk_usb_set_type_c_switch_gpio(dev, false)) {
				rtk_usb_type_c_power_on_off(dev, true);
			}
		}
	}
}

irqreturn_t type_c_detect_irq(int irq, void *__data)
{
	struct type_c_data 	*type_c = (struct type_c_data *) __data;
	struct device 		*dev = type_c->dev;
	unsigned long		flags;
	//u32 int_status, cc_status;

	detect_type_c_state(type_c);

	spin_lock_irqsave(&type_c->lock, flags);

	if (type_c->connect_change) {
		dev_info(dev, "%s: IN %s mode to %s %s (at %s interrupt) "
			    "int_status=0x%x, cc_status=0x%x",
			    __func__,
			    type_c->in_host_mode?"host":"device",
			    type_c->in_host_mode?
			        (type_c->is_attach?"attach":"detach"):
			        (type_c->is_attach?"connect":"disconnect"),
			    type_c->in_host_mode?"device":"host",
			    type_c->at_cc1?"cc1":"cc2",
			    type_c->int_status, type_c->cc_status);

		//clear interrupt status
		disable_writel(all_cc_int_sts,
			    type_c->type_c_reg_base + USB_TYPEC_CTRL);

		cancel_delayed_work(&type_c->delayed_work);
		schedule_delayed_work(&type_c->delayed_work, msecs_to_jiffies(0));
#ifdef CONFIG_DUAL_ROLE_USB_INTF
		if (type_c->drp)
			dual_role_instance_changed(type_c->drp);
#endif
	} else {
		static int local_count = 0;
		if (local_count++ > 10) {
			//clear interrupt status
			disable_writel(all_cc_int_sts,
			    type_c->type_c_reg_base + USB_TYPEC_CTRL);
			local_count = 0;
		}
		if (type_c->debug)
			dev_dbg(dev, "%s: ###NO change### Status: IN %s mode %s %s "
				    "(at %s interrupt) int_status=0x%x, cc_status=0x%x",
				__func__,
				type_c->in_host_mode?"host":"device",
				type_c->in_host_mode?
					(type_c->is_attach?"attach":"detach"):
					(type_c->is_attach?"connect":"disconnect"),
				type_c->in_host_mode?"device":"host",
				type_c->at_cc1?"cc1":"cc2", type_c->int_status, type_c->cc_status);
	}

	spin_unlock_irqrestore(&type_c->lock, flags);

	return IRQ_HANDLED;
}

#ifdef CONFIG_DYNAMIC_DEBUG
static int type_c_parameter_show(struct seq_file *s, void *unused)
{
	struct type_c_data		*type_c = s->private;
	unsigned long		flags;

	spin_lock_irqsave(&type_c->lock, flags);

	seq_printf(s, "Rd control gpio: %d\n", type_c->rd_ctrl_gpio);
	seq_printf(s, "cc_dfp_mode %s\n",
		    ({ char *tmp;
		     switch (type_c->cc_dfp_mode) {
		     case CC_MODE_DFP_USB: tmp = "CC_MODE_DFP_USB"; break;
		     case CC_MODE_DFP_1_5: tmp = "CC_MODE_DFP_1_5"; break;
		     case CC_MODE_DFP_3_0: tmp = "CC_MODE_DFP_3_0"; break;
		     default: tmp = "?"; break;
		     } tmp;}));
	seq_printf(s, "cc1_rp 0x%x\n", type_c->cc1_rp);
	seq_printf(s, "cc1_rp_code 0x%x\n",
		    ({ int tmp;
		     switch (type_c->cc_dfp_mode) {
		     case CC_MODE_DFP_USB:
		        tmp = code_rp12k(type_c->cc1_rp_code); break;
		     case CC_MODE_DFP_1_5:
		        tmp = code_rp36k(type_c->cc1_rp_code); break;
		     case CC_MODE_DFP_3_0:
		        tmp = code_rp4pk(type_c->cc1_rp_code); break;
		     default: tmp = -1; break;
		    } tmp;}));
	seq_printf(s, "cc1_rd_code 0x%x (using %s Rd)\n",
		    code_rd(type_c->cc1_rd_code),
		    type_c->rd_config?"internal":"external");
	seq_printf(s, "cc1_vref_ufp     vref_1p23v 0x%x vref_0p66v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_1p23v(type_c->cc1_vref_ufp),
		    decode_0p66v(type_c->cc1_vref_ufp),
		    decode_0p2v(type_c->cc1_vref_ufp));
	seq_printf(s, "cc1_vref_dfp_usb vref_0_1p6v 0x%x vref_0p2v 0x%x\n",
		    decode_0_1p6v(type_c->cc1_vref_dfp_usb),
		    decode_0p2v(type_c->cc1_vref_dfp_usb));
	seq_printf(s, "cc1_vref_dfp_1_5 vref_1_1p6v 0x%x vref_0p4v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_1_1p6v(type_c->cc1_vref_dfp_1_5),
		    decode_0p4v(type_c->cc1_vref_dfp_1_5),
		    decode_0p2v(type_c->cc1_vref_dfp_1_5));
	seq_printf(s, "cc1_vref_dfp_3_0 vref_2p6v   0x%x vref_0p8v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_2p6v(type_c->cc1_vref_dfp_3_0),
		    decode_0p8v(type_c->cc1_vref_dfp_3_0),
		    decode_0p2v(type_c->cc1_vref_dfp_3_0));
	seq_printf(s, "cc2_rp 0x%x\n", type_c->cc2_rp);
	seq_printf(s, "cc2_rp_code 0x%x\n",
		    ({ int tmp;
		     switch (type_c->cc_dfp_mode) {
		     case CC_MODE_DFP_USB: tmp = code_rp12k(type_c->cc2_rp_code); break;
		     case CC_MODE_DFP_1_5: tmp = code_rp36k(type_c->cc2_rp_code); break;
		     case CC_MODE_DFP_3_0: tmp = code_rp4pk(type_c->cc2_rp_code); break;
		     default: tmp = -1; break;
		    } tmp;}));
	seq_printf(s, "cc2_rd_code 0x%x (using %s Rd)\n",
		    code_rd(type_c->cc2_rd_code),
		    type_c->rd_config?"internal":"external");
	seq_printf(s, "cc2_vref_ufp     vref_1p23v 0x%x vref_0p66v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_1p23v(type_c->cc2_vref_ufp),
		    decode_0p66v(type_c->cc2_vref_ufp),
		    decode_0p2v(type_c->cc2_vref_ufp));
	seq_printf(s, "cc2_vref_dfp_usb vref_0_1p6v 0x%x vref_0p2v 0x%x\n",
		    decode_0_1p6v(type_c->cc2_vref_dfp_usb),
		    decode_0p2v(type_c->cc2_vref_dfp_usb));
	seq_printf(s, "cc2_vref_dfp_1_5 vref_1_1p6v 0x%x vref_0p4v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_1_1p6v(type_c->cc2_vref_dfp_1_5),
		    decode_0p4v(type_c->cc2_vref_dfp_1_5),
		    decode_0p2v(type_c->cc2_vref_dfp_1_5));
	seq_printf(s, "cc2_vref_dfp_3_0 vref_2p6v   0x%x vref_0p8v 0x%x "
		    "vref_0p2v 0x%x\n",
		    decode_2p6v(type_c->cc2_vref_dfp_3_0),
		    decode_0p8v(type_c->cc2_vref_dfp_3_0),
		    decode_0p2v(type_c->cc2_vref_dfp_3_0));
	seq_printf(s, "debounce_val 0x%x\n", type_c->debounce_val);
	seq_printf(s, "\n");

	seq_printf(s, "dwc3_mode %s (%s)\n",
		    ({ char *tmp;
		     switch (type_c->dwc3_mode) {
		     case USB_DR_MODE_PERIPHERAL: tmp = "USB_DR_MODE_PERIPHERAL"; break;
		     case USB_DR_MODE_HOST: tmp = "USB_DR_MODE_HOST"; break;
		     default: tmp = "USB_DR_MODE_UNKNOWN"; break;
		    } tmp;}),
		    type_c->is_drd_mode?"is DRD":"Not DRD");

	spin_unlock_irqrestore(&type_c->lock, flags);

	return 0;
}

static int type_c_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, type_c_parameter_show, inode->i_private);
}

static const struct file_operations type_c_parameter_fops = {
	.open			= type_c_parameter_open,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int type_c_set_parameter_show(struct seq_file *s, void *unused)
{
	//struct type_c_data		*type_c = s->private;

	seq_printf(s, "cc_dfp_mode [CC_MODE_DFP_USB|CC_MODE_DFP_1_5|"
		    "CC_MODE_DFP_3_0]\n");
	seq_printf(s, "rd_config [internal|external]");
	seq_printf(s, "cc1_rp_code 0x_value\n");
	seq_printf(s, "cc1_rd_code 0x_value\n");
	seq_printf(s, "cc1_vref_ufp_vref_1p23v 0x_value\n");
	seq_printf(s, "cc1_vref_ufp_vref_0p66v 0x_value\n");
	seq_printf(s, "cc1_vref_ufp_vref_0p2v  0x_value\n");
	seq_printf(s, "cc1_vref_dfp_usb_vref_1p6v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_usb_vref_0p2v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_1_5_vref_1p6v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_1_5_vref_0p4v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_1_5_vref_0p2v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_3_0_vref_2p6v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_3_0_vref_0p8v 0x_value\n");
	seq_printf(s, "cc1_vref_dfp_3_0_vref_0p2v 0x_value\n");
	seq_printf(s, "cc2_rp_code 0x_value\n");
	seq_printf(s, "cc2_rd_code 0x_value\n");
	seq_printf(s, "cc2_vref_ufp_vref_1p23v 0x_value\n");
	seq_printf(s, "cc2_vref_ufp_vref_0p66v 0x_value\n");
	seq_printf(s, "cc2_vref_ufp_vref_0p2v  0x_value\n");
	seq_printf(s, "cc2_vref_dfp_usb_vref_1p6v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_usb_vref_0p2v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_1_5_vref_1p6v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_1_5_vref_0p4v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_1_5_vref_0p2v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_3_0_vref_2p6v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_3_0_vref_0p8v 0x_value\n");
	seq_printf(s, "cc2_vref_dfp_3_0_vref_0p2v 0x_value\n");
	seq_printf(s, "debounce_val value\n");

	return 0;
}

static int type_c_set_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, type_c_set_parameter_show, inode->i_private);
}

static ssize_t type_c_set_parameter_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct type_c_data		*type_c = s->private;
	unsigned long		flags;
	char			buffer[40];
	char *buf = buffer;
	u32 value;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	spin_lock_irqsave(&type_c->lock, flags);
	if (!strncmp(buf, "cc_dfp_mode", 11)) {
		buf = buf + 11;
		buf = skip_spaces(buf);
		if (!strncmp(buf, "CC_MODE_DFP_USB", 15)) {
			type_c->cc_dfp_mode = CC_MODE_DFP_USB;
			type_c->cc1_rp = En_rp12k;
			type_c->cc2_rp = En_rp12k;
		} else if (!strncmp(buf, "CC_MODE_DFP_1_5", 15)) {
			type_c->cc_dfp_mode = CC_MODE_DFP_1_5;
			type_c->cc1_rp = En_rp36k;
			type_c->cc2_rp = En_rp36k;
		} else if (!strncmp(buf, "CC_MODE_DFP_3_0", 15)) {
			type_c->cc_dfp_mode = CC_MODE_DFP_3_0;
			type_c->cc1_rp = En_rp4p7k;
			type_c->cc2_rp = En_rp4p7k;
		} else {
			dev_err(type_c->dev, "cc_dfp_mode UNKNOWN (%s)", buf);
		}
	} else if (!strncmp(buf, "rd_config", 9)) {
		buf = buf + 9;
		buf = skip_spaces(buf);
		if (!strncmp(buf, "internal", 8))
			type_c->rd_config = INTERNAL_Rd;
		else if (!strncmp(buf, "external", 8))
			type_c->rd_config = EXTERNAL_Rd;
		else
			dev_err(type_c->dev, "rd_config UNKNOWN (%s)", buf);

	} else if (!strncmp(buf, "cc1_rp_code", 11)) {
		buf = buf + 11;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		if (type_c->cc_dfp_mode == CC_MODE_DFP_USB)
			type_c->cc1_rp_code = rp12k_code(value);
		else if (type_c->cc_dfp_mode == CC_MODE_DFP_1_5)
			type_c->cc1_rp_code = rp36k_code(value);
		else if (type_c->cc_dfp_mode == CC_MODE_DFP_3_0)
			type_c->cc1_rp_code = rp4pk_code(value);
	} else if (!strncmp(buf, "cc1_rd_code", 11)) {
		buf = buf + 11;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_rd_code = rd_code(value);
	} else if (!strncmp(buf, "cc1_vref_ufp_vref_1p23v", 23)) {
		buf = buf + 23;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_ufp = (type_c->cc1_vref_ufp & (~vref_1p23v(0xf))) |
			    vref_1p23v(value);
	} else if (!strncmp(buf, "cc1_vref_ufp_vref_0p66v", 23)) {
		buf = buf + 23;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_ufp = (type_c->cc1_vref_ufp & (~vref_0p66v(0xf))) |
			    vref_0p66v(value);
	} else if (!strncmp(buf, "cc1_vref_ufp_vref_0p2v", 22)) {
		buf = buf + 22;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_ufp = (type_c->cc1_vref_ufp & (~vref_0p2v(0x7))) |
			    vref_0p2v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_usb_vref_1p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_usb = (type_c->cc1_vref_dfp_usb &
			    (~vref_0_1p6v(0xf))) | vref_0_1p6v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_usb_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_usb = (type_c->cc1_vref_dfp_usb &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_1_5_vref_1p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_1_5 = (type_c->cc1_vref_dfp_1_5 &
			    (~vref_1_1p6v(0xf))) | vref_1_1p6v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_1_5_vref_0p4v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_1_5 = (type_c->cc1_vref_dfp_1_5 &
			    (~vref_0p4v(0x7))) | vref_0p4v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_1_5_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_1_5 = (type_c->cc1_vref_dfp_1_5 &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_3_0_vref_2p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_ufp = (type_c->cc1_vref_dfp_1_5 & (~vref_2p6v(0x7))) |
			    vref_2p6v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_3_0_vref_0p8v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_3_0 = (type_c->cc1_vref_dfp_3_0 &
			    (~vref_0p8v(0xf))) | vref_0p8v(value);
	} else if (!strncmp(buf, "cc1_vref_dfp_3_0_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc1_vref_dfp_3_0 = (type_c->cc1_vref_dfp_3_0 &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "cc2_rp_code", 11)) {
		buf = buf + 11;
		buf = skip_spaces(buf);
		sscanf(buf, "%d", &value);
		if (type_c->cc_dfp_mode == CC_MODE_DFP_USB)
			type_c->cc2_rp_code = rp12k_code(value);
		else if (type_c->cc_dfp_mode == CC_MODE_DFP_1_5)
			type_c->cc2_rp_code = rp36k_code(value);
		else if (type_c->cc_dfp_mode == CC_MODE_DFP_3_0)
			type_c->cc2_rp_code = rp4pk_code(value);
	} else if (!strncmp(buf, "cc2_rd_code", 11)) {
		buf = buf + 11;
		buf = skip_spaces(buf);
		sscanf(buf, "%d", &value);
		type_c->cc2_rd_code = rd_code(value);
	} else if (!strncmp(buf, "cc2_vref_ufp_vref_1p23v", 23)) {
		buf = buf + 23;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_ufp = (type_c->cc2_vref_ufp & (~vref_1p23v(0xf))) |
			    vref_1p23v(value);
	} else if (!strncmp(buf, "cc2_vref_ufp_vref_0p66v", 23)) {
		buf = buf + 23;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_ufp = (type_c->cc2_vref_ufp & (~vref_0p66v(0xf))) |
			    vref_0p66v(value);
	} else if (!strncmp(buf, "cc2_vref_ufp_vref_0p2v", 22)) {
		buf = buf + 22;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_ufp = (type_c->cc2_vref_ufp & (~vref_0p2v(0x7))) |
			    vref_0p2v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_usb_vref_1p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_usb = (type_c->cc2_vref_dfp_usb &
			    (~vref_0_1p6v(0xf))) | vref_0_1p6v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_usb_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_usb = (type_c->cc2_vref_dfp_usb &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_1_5_vref_1p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_1_5 = (type_c->cc2_vref_dfp_1_5 &
			    (~vref_1_1p6v(0xf))) | vref_1_1p6v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_1_5_vref_0p4v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_1_5 = (type_c->cc2_vref_dfp_1_5 &
			    (~vref_0p4v(0x7))) | vref_0p4v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_1_5_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_1_5 = (type_c->cc2_vref_dfp_1_5 &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_3_0_vref_2p6v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_3_0 = (type_c->cc2_vref_dfp_3_0 &
			    (~vref_2p6v(0x7))) | vref_2p6v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_3_0_vref_0p8v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_3_0 = (type_c->cc2_vref_dfp_3_0 &
			    (~vref_0p8v(0xf))) | vref_0p8v(value);
	} else if (!strncmp(buf, "cc2_vref_dfp_3_0_vref_0p2v", 26)) {
		buf = buf + 26;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->cc2_vref_dfp_3_0 = (type_c->cc2_vref_dfp_3_0 &
			    (~vref_0p2v(0x7))) | vref_0p2v(value);
	} else if (!strncmp(buf, "debounce_val", 12)) {
		buf = buf + 12;
		buf = skip_spaces(buf);
		sscanf(buf, "%x", &value);
		type_c->debounce_val = value;
	} else
		dev_err(type_c->dev, "UNKNOWN input (%s)", buf);

	spin_unlock_irqrestore(&type_c->lock, flags);
	return count;
}

static const struct file_operations type_c_set_parameter_fops = {
	.open			= type_c_set_parameter_open,
	.write			= type_c_set_parameter_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int type_c_status_show(struct seq_file *s, void *unused)
{
	struct type_c_data		*type_c = s->private;
	unsigned long		flags;

	spin_lock_irqsave(&type_c->lock, flags);

	seq_printf(s, "cur_mode %s\n",
		    ({ char *tmp;
		     switch (type_c->cur_mode) {
		     case USB_DR_MODE_PERIPHERAL:
		        tmp = "USB_DR_MODE_PERIPHERAL"; break;
		     case USB_DR_MODE_HOST: tmp = "USB_DR_MODE_HOST"; break;
		     default: tmp = "USB_DR_MODE_UNKNOWN"; break;
		    } tmp;}));

	seq_printf(s, "In %s mode %s %s at %s (cc_status=0x%x)\n",
		    type_c->in_host_mode?"host":"device",
		    type_c->in_host_mode?
		        (type_c->is_attach?"attach":"detach"):
		        (type_c->is_attach?"connect":"disconnect"),
		    type_c->in_host_mode?"device":"host",
		    type_c->at_cc1?"cc1":"cc2", type_c->cc_status);

	spin_unlock_irqrestore(&type_c->lock, flags);

	return 0;
}

static int type_c_status_open(struct inode *inode, struct file *file)
{
	return single_open(file, type_c_status_show, inode->i_private);
}

static const struct file_operations type_c_status_fops = {
	.open			= type_c_status_open,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int type_c_debug_show(struct seq_file *s, void *unused)
{
	struct type_c_data		*type_c = s->private;

	seq_printf(s, "Debug: %s\n",
				type_c->debug?"Enable":"disable");

	return 0;
}

static int type_c_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, type_c_debug_show, inode->i_private);
}

static ssize_t type_c_debug_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct type_c_data		*type_c = s->private;
	char			buf[32];

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "enable", 6))
		type_c->debug = true;
	else if (!strncmp(buf, "disable", 7))
		type_c->debug = false;

	return count;
}

static const struct file_operations type_c_debug_fops = {
	.open			= type_c_debug_open,
	.write			= type_c_debug_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static inline void create_debug_files(struct type_c_data *type_c)
{
	dev_err(type_c->dev, "%s", __func__);

	type_c->debug_dir = debugfs_create_dir("type_c", usb_debug_root);
	if (!type_c->debug_dir) {
		dev_err(type_c->dev, "%s Error debug_dir is NULL", __func__);
		return;
	}

	if (!debugfs_create_file("parameter", S_IRUGO, type_c->debug_dir, type_c,
		    &type_c_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("set_parameter", S_IRUGO | S_IWUSR,
		    type_c->debug_dir, type_c,
		    &type_c_set_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("status", S_IRUGO, type_c->debug_dir, type_c,
		    &type_c_status_fops))
		goto file_error;

	if (!debugfs_create_file("debug", S_IRUGO | S_IWUSR,
		    type_c->debug_dir, type_c,
		    &type_c_debug_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(type_c->debug_dir);
}
#endif //CONFIG_DYNAMIC_DEBUG

#ifdef CONFIG_DUAL_ROLE_USB_INTF
static enum dual_role_property fusb_drp_properties[] = {
	DUAL_ROLE_PROP_MODE,
	DUAL_ROLE_PROP_PR,
	DUAL_ROLE_PROP_DR,
};

static int dual_role_get_local_prop(struct dual_role_phy_instance *drp,
				enum dual_role_property prop,
				unsigned int *val)
{
	struct type_c_data *type_c = dual_role_get_drvdata(drp);

	if (!type_c) {
		pr_err("driver data not ready\n");
		return -1;
	}
	detect_type_c_state(type_c);

	if(type_c->cur_mode == USB_DR_MODE_PERIPHERAL) {
		if (prop == DUAL_ROLE_PROP_MODE)
			*val = DUAL_ROLE_PROP_MODE_UFP;
		else if(prop == DUAL_ROLE_PROP_PR)
			*val = DUAL_ROLE_PROP_PR_SNK;
		else if(prop == DUAL_ROLE_PROP_DR)
			*val = DUAL_ROLE_PROP_DR_DEVICE;
		else
			return -EINVAL;
	} else if(type_c->cur_mode == USB_DR_MODE_HOST) {
		if (prop == DUAL_ROLE_PROP_MODE)
			*val = DUAL_ROLE_PROP_MODE_DFP;
		else if (prop == DUAL_ROLE_PROP_PR)
			*val = DUAL_ROLE_PROP_PR_SRC;
		else if (prop == DUAL_ROLE_PROP_DR)
			*val = DUAL_ROLE_PROP_DR_HOST;
		else
			return -EINVAL;
	} else {
		if (prop == DUAL_ROLE_PROP_MODE)
			*val = DUAL_ROLE_PROP_MODE_NONE;
		else if (prop == DUAL_ROLE_PROP_PR)
			*val = DUAL_ROLE_PROP_PR_NONE;
		else if (prop == DUAL_ROLE_PROP_DR)
			*val = DUAL_ROLE_PROP_DR_NONE;
		else
			return -EINVAL;
	}

	return 0;
}

static int dual_role_is_writeable(struct dual_role_phy_instance *drp,
				enum dual_role_property prop)
{
	if (prop == DUAL_ROLE_PROP_MODE)
		return 1;
	else
		return 0;
}
#if 0
static int dual_role_set_mode_prop(struct dual_role_phy_instance *drp,
				enum dual_role_property prop,
				const unsigned int *val)
{
	pr_err("%s\n", __func__);
	return 0;
}

static int dual_role_set_prop(struct dual_role_phy_instance *drp,
				enum dual_role_property prop,
				const unsigned int *val)
{
	if (prop == DUAL_ROLE_PROP_MODE)
		return dual_role_set_mode_prop(drp, prop, val);
	else
		return -EINVAL;
}
#endif
#endif

/* Init and probe */
static int dwc3_rtk_type_c_init(struct type_c_data *type_c)
{
	struct device		*dev = type_c->dev;
	u32 debounce_val = type_c->debounce_val;// 1b,1us 7f,4.7us

	enable_writel(debounce_val<<1,
		    type_c->type_c_reg_base + USB_TYPEC_CTRL);
	dev_info(dev, "%s set debounce = 0x%x (check--> 0x%x)\n",
		    __func__, debounce_val,
		    readl(type_c->type_c_reg_base + USB_TYPEC_CTRL));

	if ((type_c->rd_ctrl_gpio != -1) &&
		    gpio_request(type_c->rd_ctrl_gpio, dev->of_node->name))
		dev_err(dev, "%s ERROR Request rd_ctrl_gpio  (id=%d) fail\n",
			   __func__, type_c->rd_ctrl_gpio);

	init_type_c_mode(type_c);

	if (type_c->cur_mode == USB_DR_MODE_UNKNOWN)
		switch_dwc3_mode(type_c, 0);

	if (type_c->dwc3_mode == USB_DR_MODE_HOST) {
		unsigned long		flags;

		spin_lock_irqsave(&type_c->lock, flags);

		dev_info(dev, "DWC3_DRD run in USB_DR_MODE_HOST");
		type_c->in_host_mode = IN_HOST_MODE;
		type_c->is_attach = IN_DETACH;
		type_c->connect_change = CONNECT_NO_CHANGE;
		type_c->cur_mode = USB_DR_MODE_HOST;

		detect_device(type_c);

		spin_unlock_irqrestore(&type_c->lock, flags);

		detect_type_c_state(type_c);

		schedule_delayed_work(&type_c->delayed_work,
			    msecs_to_jiffies(0));
	} else if (type_c->dwc3_mode == USB_DR_MODE_PERIPHERAL) {
		unsigned long		flags;

		spin_lock_irqsave(&type_c->lock, flags);

		dev_info(dev, "DWC3_DRD run in USB_DR_MODE_PERIPHERAL%s",
				type_c->is_drd_mode?" at DRD mode":"");
		type_c->in_host_mode = IN_DEVICE_MODE;
		type_c->is_attach = IN_DETACH;
		type_c->connect_change = CONNECT_NO_CHANGE;
		type_c->cur_mode = USB_DR_MODE_PERIPHERAL;
		type_c->check_at_boot = true;

		detect_host(type_c);

		spin_unlock_irqrestore(&type_c->lock, flags);

		detect_type_c_state(type_c);

		schedule_delayed_work(&type_c->delayed_work,
			    msecs_to_jiffies(0));
	} else {
		dev_err(dev, "DWC3_DRD is USB_DR_MODE_UNKNOWN");
	}
	return 0;
}

extern int rtk_usb_manager_schedule_work(struct device *usb_dev,
	    struct work_struct *work);

static void dwc3_rtk_type_c_probe_work(struct work_struct *work)
{
	struct type_c_data *type_c = container_of(work,
		    struct type_c_data, start_work);
	struct device		*dev = type_c->dev;
	int    ret = 0;

	unsigned long probe_time = jiffies;

	dev_info(dev, "%s Start ...\n", __func__);

	ret = dwc3_rtk_type_c_init(type_c);

	if (ret)
		dev_err(dev, "%s failed to init type_c\n", __func__);

	dev_info(dev, "%s End ... ok! (take %d ms)\n", __func__,
		    jiffies_to_msecs(jiffies - probe_time));
}

static int dwc3_rtk_type_c_probe(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct device_node	*node = dev->of_node;
	struct type_c_data 	*type_c;
	unsigned int gpio;
	int irq;
	int ret = 0;
	unsigned long probe_time = jiffies;
#ifdef CONFIG_DUAL_ROLE_USB_INTF
	struct dual_role_phy_desc *desc;
	struct dual_role_phy_instance *dual_role;
#endif


	dev_info(dev, "ENTER %s", __func__);
	type_c = devm_kzalloc(dev, sizeof(*type_c), GFP_KERNEL);
	if (!type_c)
		return -ENOMEM;

	type_c->wrap_base = of_iomap(pdev->dev.of_node, 0);
	if (type_c->wrap_base == NULL) {
		dev_err(&pdev->dev, "error mapping memory for wrap_base\n");
		ret = -EFAULT;
		goto err1;
	}

	type_c->type_c_reg_base = of_iomap(pdev->dev.of_node, 1);
	if (type_c->type_c_reg_base == NULL) {
		type_c->type_c_reg_base = type_c->wrap_base + 0x14C; // for Kylin case
		dev_warn(&pdev->dev, "No mapping memory for type_c_reg_base!\n");
		dev_warn(&pdev->dev, "Let type_c_reg_base = %p\n",
			    type_c->type_c_reg_base);
	}

	type_c->dev = dev;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "Type C driver with no IRQ. Check %s setup!\n",
				dev_name(&pdev->dev));
		ret = -ENODEV;
		goto err1;
	}

	ret = request_irq(irq, type_c_detect_irq,
			IRQF_SHARED, "type_c_detect", type_c);

	if (node && of_device_is_available(node)) {
		gpio = of_get_named_gpio(node, "realtek,rd_ctrl-gpio", 0);

		if (gpio_is_valid(gpio)) {
			type_c->rd_ctrl_gpio = gpio;
			dev_info(dev, "%s get rd_ctrl-gpio (id=%d) OK\n", __func__, gpio);
		} else {
			dev_err(dev, "Error rd_ctrl-gpio no found");
			type_c->rd_ctrl_gpio = -1;
		}

		ret = of_property_read_u32(node, "boot_check_time",
			&type_c->boot_check_time);
		if (ret) {
			type_c->boot_check_time = 30000; //ms
		}
		dev_info(dev, "Set device mode boot_check_time %d ms\n",
			    type_c->boot_check_time);
	}

	type_c->chip_id = get_rtd_chip_id();
	type_c->chip_revision = get_rtd_chip_revision();

	if (node && of_device_is_available(node)) {
		const char *str;
		u32 val;
		struct device_node *sub_node;
		u8 array_vals[3];
		u32 u32_vals[3];
		u32 default_revision;
		char revision[4] = {0};

		ret = of_property_read_u32(node, "default_revision",
			    &default_revision);
		if (ret) {
			default_revision = 0xA00;
			dev_info(dev, "%s: No set default_revision (use %x)\n",
				    __func__, default_revision);
		}

		if (type_c->chip_revision > default_revision)
			snprintf(revision, 4, "%X", default_revision);
		else
			snprintf(revision, 4, "%X", type_c->chip_revision);
		dev_info(dev, "Chip %x revision is %x (support revision %x) "
			    "to load %s parameter\n",
			    type_c->chip_id, type_c->chip_revision,
			    default_revision, revision);
		sub_node = of_get_child_by_name(node, revision);

		ret = of_property_read_string(sub_node, "cc_dfp_mode", &str);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc_dfp_mode error(%d)\n", __func__, ret);
			goto err1;
		}
		if (!strcmp(str, "dfp_usb")) {
			type_c->cc_dfp_mode = CC_MODE_DFP_USB;
			type_c->cc1_rp = En_rp12k;
			type_c->cc2_rp = En_rp12k;
		} else if (!strcmp(str, "dfp_1_5")) {
			type_c->cc_dfp_mode = CC_MODE_DFP_1_5;
			type_c->cc1_rp = En_rp36k;
			type_c->cc2_rp = En_rp36k;
		} else if (!strcmp(str, "dfp_3_0")) {
			type_c->cc_dfp_mode = CC_MODE_DFP_3_0;
			type_c->cc1_rp = En_rp4p7k;
			type_c->cc2_rp = En_rp4p7k;
		} else {
			dev_err(&pdev->dev, "%s: unknown cc_dfp_mode %s\n", __func__, str);
		}

		//cc1 parameters
		ret = of_property_read_u32(sub_node, "cc1_rp_4p7k_code", &u32_vals[0]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_rp_4p7k_code error(%d)\n",
				    __func__, u32_vals[0]);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc1_rp_36k_code", &u32_vals[1]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_rp_36k_code error(%d)\n", __func__,
				    u32_vals[1]);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc1_rp_12k_code", &u32_vals[2]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_rp_12k_code error(%d)\n",
				    __func__, u32_vals[2]);
			goto err1;
		}
		type_c->cc1_rp_code = rp4pk_code(u32_vals[0])
				| rp36k_code(u32_vals[1])
				| rp12k_code(u32_vals[2]);

		ret = of_property_read_string(sub_node, "rd_config", &str);
		if (ret) {
			dev_err(&pdev->dev, "%s: rd_config error(%d)\n", __func__, ret);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc1_rd_code", &val);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_rd_code error(%d)\n", __func__, ret);
			goto err1;
		}
		if (!strcmp(str, "internal")) {
			type_c->rd_config = INTERNAL_Rd;
			type_c->cc1_rd_code = rd_code(val);
		} else if (!strcmp(str, "external")) {
			type_c->rd_config = EXTERNAL_Rd;
			type_c->cc1_rd_code = 0x0;
		} else {
			dev_err(&pdev->dev, "%s: unknown rd_config %s, cc1_rd_code=%d\n",
				    __func__, str, val);
		}
		ret = of_property_read_u8_array(sub_node, "cc1_vref_ufp",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_vref_ufp error(%d)\n", __func__, ret);
			goto err1;
		}
		type_c->cc1_vref_ufp = vref_1p23v(array_vals[0]) |
			    vref_0p66v(array_vals[1]) | vref_0p2v(array_vals[2]);

		ret = of_property_read_u8_array(sub_node, "cc1_vref_dfp_usb",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_vref_dfp_usb error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc1_vref_dfp_usb = vref_0_1p6v(array_vals[0]) |
			    vref_0p2v(array_vals[1]);

		ret = of_property_read_u8_array(sub_node, "cc1_vref_dfp_1_5",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_vref_dfp_1_5 error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc1_vref_dfp_1_5 = vref_1_1p6v(array_vals[0]) |
			     vref_0p4v(array_vals[1]) | vref_0p2v(array_vals[2]);

		ret = of_property_read_u8_array(sub_node, "cc1_vref_dfp_3_0",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc1_vref_dfp_3_0 error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc1_vref_dfp_3_0 = vref_2p6v(array_vals[0]) |
			    vref_0p8v(array_vals[1]) | vref_0p2v(array_vals[2]);

		//cc2 parameters
		ret = of_property_read_u32(sub_node, "cc2_rp_4p7k_code", &u32_vals[0]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_rp_4p7k_code error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc2_rp_36k_code", &u32_vals[1]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_rp_36k_code error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc2_rp_12k_code", &u32_vals[2]);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_rp_12k_code error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc2_rp_code = rp4pk_code(array_vals[0])
				| rp36k_code(array_vals[1])
				| rp12k_code(array_vals[2]);

		ret = of_property_read_string(sub_node, "rd_config", &str);
		if (ret) {
			dev_err(&pdev->dev, "%s: rd_config error(%d)\n", __func__, ret);
			goto err1;
		}
		ret = of_property_read_u32(sub_node, "cc2_rd_code", &val);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_rd_code error(%d)\n", __func__, ret);
			goto err1;
		}
		if (!strcmp(str, "internal")) {
			type_c->cc2_rd_code = rd_code(val);
		} else if (!strcmp(str, "external")) {
			type_c->cc2_rd_code = 0x0;
		} else {
			dev_err(&pdev->dev, "%s: unknown rd_code %s, cc2_rd_code=%d\n",
				    __func__, str, val);
		}

		ret = of_property_read_u8_array(sub_node, "cc2_vref_ufp",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_vref_ufp error(%d)\n", __func__, ret);
			goto err1;
		}
		type_c->cc2_vref_ufp = vref_1p23v(array_vals[0]) |
			    vref_0p66v(array_vals[1]) | vref_0p2v(array_vals[2]);

		ret = of_property_read_u8_array(sub_node, "cc2_vref_dfp_usb",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_vref_dfp_usb error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc2_vref_dfp_usb = vref_0_1p6v(array_vals[0]) |
			    vref_0p2v(array_vals[1]);

		ret = of_property_read_u8_array(sub_node, "cc2_vref_dfp_1_5",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_vref_dfp_1_5 error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc2_vref_dfp_1_5 = vref_1_1p6v(array_vals[0]) |
			    vref_0p4v(array_vals[1]) | vref_0p2v(array_vals[2]);

		ret = of_property_read_u8_array(sub_node, "cc2_vref_dfp_3_0",
			    array_vals, 3);
		if (ret) {
			dev_err(&pdev->dev, "%s: cc2_vref_dfp_3_0 error(%d)\n",
				    __func__, ret);
			goto err1;
		}
		type_c->cc2_vref_dfp_3_0 = vref_2p6v(array_vals[0]) |
			    vref_0p8v(array_vals[1]) | vref_0p2v(array_vals[2]);

		type_c->debounce_val = 0x7f;// 1b,1us 7f,4.7us
	}

	if (true) {
		struct device_node	*parent_node;
		struct device_node	*next_node;

		parent_node = of_get_parent(node);
		next_node = of_get_next_child(parent_node, NULL);
		if (next_node != NULL) {
			type_c->dwc = platform_get_drvdata(
				    of_find_device_by_node(next_node));
		} else {
			dev_err(dev, "%s No find dwc3_drd", __func__);
			ret = -ENODEV;
			goto err1;
		}
		if (type_c->dwc) {
			type_c->dwc3_mode = type_c->dwc->dr_mode;
		} else {
			dev_err(dev, "%s dwc3_drd device dwc is NULL", __func__);
			ret = -ENODEV;
			goto err1;
		}
	}

	type_c->cur_mode = USB_DR_MODE_UNKNOWN;
	type_c->is_attach = IN_DETACH;
	type_c->is_drd_mode = false;
	if (of_property_read_bool(node, "drd_mode")) {
		if (type_c->dwc3_mode == USB_DR_MODE_PERIPHERAL) {
			type_c->is_drd_mode = true;
			dev_info(dev, "DWC3_DRD is DRD mode");
		} else {
			dev_info(dev, "DWC3_DRD is not DRD mode, "
				   "due to dwc3_mode=USB_DR_MODE_HOST");
		}
	} else {
		dev_dbg(dev, "DWC3_DRD is no drd_mode, and dwc3_mode=%d",
			    type_c->dwc3_mode);
	}

	if (of_property_read_bool(node, "debug")) {
		dev_info(&pdev->dev, "%s device tree set debug flag\n", __func__);
		type_c->debug = true;
	} else {
		type_c->debug = false;
	}

	INIT_DELAYED_WORK(&type_c->delayed_work, host_device_switch);
	INIT_DELAYED_WORK(&type_c->boot_check_work, boot_time_check);

	if (node) {
		if (of_property_read_bool(node, "delay_probe_work")) {
			INIT_WORK(&type_c->start_work, dwc3_rtk_type_c_probe_work);

			if (of_property_read_bool(node, "ordered_probe"))
				rtk_usb_manager_schedule_work(dev, &type_c->start_work);
			else
				schedule_work(&type_c->start_work);
		} else {
			ret = dwc3_rtk_type_c_init(type_c);
			if (ret) {
				dev_err(dev, "%s failed to init type_c\n", __func__);
				goto err1;
			}
		}
	} else {
		dev_err(dev, "no device node, failed to init type_c\n");
		ret = -ENODEV;
		goto err1;
	}

	platform_set_drvdata(pdev, type_c);

#ifdef CONFIG_DYNAMIC_DEBUG
	create_debug_files(type_c);
#endif

#ifdef CONFIG_DUAL_ROLE_USB_INTF
	desc = devm_kzalloc(dev, sizeof(struct dual_role_phy_desc), GFP_KERNEL);
	if (!desc) {
		dev_err(dev, "%s, dual role descriptor malloc fail\n", __func__);
		goto err1;
	}
	desc->name = "dwc3_otg";
	desc->supported_modes = DUAL_ROLE_SUPPORTED_MODES_DFP_AND_UFP;
	desc->get_property = dual_role_get_local_prop;
//	desc->set_property = dual_role_set_prop;
	desc->properties = fusb_drp_properties;
	desc->num_properties = ARRAY_SIZE(fusb_drp_properties);
	desc->property_is_writeable = dual_role_is_writeable;
	dual_role = devm_dual_role_instance_register(dev, desc);
	dual_role->drv_data = type_c;
	type_c->drp = dual_role;
#endif

	dev_info(&pdev->dev, "Exit %s OK (take %d ms)\n", __func__,
		    jiffies_to_msecs(jiffies - probe_time));
	return 0;

err1:
	dev_err(&pdev->dev, "%s: Probe fail, %d\n", __func__, ret);

	return ret;
}

static int dwc3_rtk_type_c_remove(struct platform_device *pdev)
{
	struct device		*dev = &pdev->dev;
	struct type_c_data *type_c = dev_get_drvdata(dev);
	u32 default_ctrl;
	unsigned long		flags;

	dev_info(dev, "[USB] Enter %s", __func__);

	cancel_delayed_work_sync(&type_c->delayed_work);
	flush_delayed_work(&type_c->delayed_work);
	BUG_ON(delayed_work_pending(&type_c->delayed_work));

	cancel_delayed_work_sync(&type_c->boot_check_work);
	flush_delayed_work(&type_c->boot_check_work);
	BUG_ON(delayed_work_pending(&type_c->boot_check_work));

	spin_lock_irqsave(&type_c->lock, flags);
	//disable interrupt
	default_ctrl = readl(type_c->type_c_reg_base + USB_TYPEC_CTRL) &
		    debounce_time_MASK;
	writel(default_ctrl, type_c->type_c_reg_base + USB_TYPEC_CTRL);

	spin_unlock_irqrestore(&type_c->lock, flags);

	dev_info(&pdev->dev, "[USB] Exit %s\n", __func__);
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id rtk_dwc3_type_c_match[] = {
	{ .compatible = "Realtek,dwc3-type_c" },
	{ .compatible = "Realtek,rtd1295-dwc3-type_c" },
	{ .compatible = "Realtek,rtd1296-dwc3-type_c" },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_dwc3_type_c_match);
#endif

#ifdef CONFIG_PM_SLEEP
static int dwc3_rtk_type_c_prepare(struct device *dev) {
	struct type_c_data *type_c = dev_get_drvdata(dev);
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

static void dwc3_rtk_type_c_complete(struct device *dev) {
	struct type_c_data *type_c = dev_get_drvdata(dev);
	unsigned long		flags;

	dev_info(dev, "[USB] Enter %s\n", __func__);
	if (RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		dev_info(dev, "[USB] %s S1 (Standby mode)\n", __func__);
	} else {
		dev_info(dev, "[USB] %s S3 (Suspend-to-RAM mode)\n", __func__);
			spin_lock_irqsave(&type_c->lock, flags);
			switch_type_c_plug_side(type_c, disable_cc);
			spin_unlock_irqrestore(&type_c->lock, flags);

		if ((type_c->chip_id & 0xFFF0) == CHIP_ID_RTD129X) {
			if (rtk_usb_type_c_power_on_off(dev, false))
				dev_err(dev, "%s to disable type c power Fail\n", __func__);
			else
				dev_dbg(dev, "%s to disable type c power OK\n", __func__);
		}

		dwc3_rtk_type_c_init(type_c);
	}
	dev_info(dev, "[USB] Exit %s\n", __func__);
}

static int dwc3_rtk_type_c_suspend(struct device *dev)
{
	struct type_c_data *type_c = dev_get_drvdata(dev);
	u32 default_ctrl;
	unsigned long		flags;

	dev_info(dev, "[USB] Enter %s", __func__);

	cancel_delayed_work_sync(&type_c->delayed_work);
	flush_delayed_work(&type_c->delayed_work);
	BUG_ON(delayed_work_pending(&type_c->delayed_work));

	cancel_delayed_work_sync(&type_c->boot_check_work);
	flush_delayed_work(&type_c->boot_check_work);
	BUG_ON(delayed_work_pending(&type_c->boot_check_work));

	spin_lock_irqsave(&type_c->lock, flags);
	//disable interrupt
	default_ctrl = readl(type_c->type_c_reg_base + USB_TYPEC_CTRL) &
		    debounce_time_MASK;
	writel(default_ctrl, type_c->type_c_reg_base + USB_TYPEC_CTRL);

	spin_unlock_irqrestore(&type_c->lock, flags);

	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		goto out;
	}
	//For suspend mode
	dev_info(dev,  "[USB] %s Suspend mode\n", __func__);

	if (type_c->rd_ctrl_gpio != -1)
		gpio_free(type_c->rd_ctrl_gpio);

out:
	dev_info(dev, "[USB] Exit %s\n", __func__);
	return 0;
}

static int dwc3_rtk_type_c_resume(struct device *dev)
{
	struct type_c_data *type_c = dev_get_drvdata(dev);
	unsigned long		flags;

	dev_info(dev, "[USB] Enter %s", __func__);

	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		//For idle mode
		dev_info(dev, "[USB] %s Idle mode\n", __func__);
		spin_lock_irqsave(&type_c->lock, flags);
		//enable interrupt
		if (type_c->is_attach == IN_ATTACH)
			enable_writel(ENABLE_TYPE_C_DETECT,
			    type_c->type_c_reg_base + USB_TYPEC_CTRL);

		schedule_delayed_work(&type_c->delayed_work, msecs_to_jiffies(1));
		spin_unlock_irqrestore(&type_c->lock, flags);
		goto out;
	} else {
		//For suspend mode
		dev_info(dev, "[USB] %s Suspend mode\n", __func__);

		if (type_c->cur_mode == USB_DR_MODE_HOST) {
			writel(USB2_PHY_SWITCH_HOST |
				    (~USB2_PHY_SWITCH_MASK &
				    readl(type_c->wrap_base + USB2_PHY_reg)),
				    type_c->wrap_base + USB2_PHY_reg);
			dev_info(dev, "%s USB_DR_MODE_HOST to enable power\n", __func__);
			if (rtk_usb_type_c_power_on_off(dev, true))
				dev_err(dev, "%s to enable type c power Fail\n", __func__);
			else
				dev_dbg(dev, "%s to enable type c power OK\n", __func__);
		} else if (type_c->cur_mode == USB_DR_MODE_PERIPHERAL) {
			writel(USB2_PHY_SWITCH_DEVICE |
				    (~USB2_PHY_SWITCH_MASK &
				    readl(type_c->wrap_base + USB2_PHY_reg)),
				    type_c->wrap_base + USB2_PHY_reg);
		}

		spin_lock_irqsave(&type_c->lock, flags);
		if (type_c->is_attach == IN_ATTACH && type_c->at_cc1 == AT_CC1)
			switch_type_c_plug_side(type_c, enable_cc1);
		else if (type_c->is_attach == IN_ATTACH && type_c->at_cc1 == AT_CC2)
			switch_type_c_plug_side(type_c, enable_cc2);
		spin_unlock_irqrestore(&type_c->lock, flags);
	}
out:
	dev_info(dev, "[USB] Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops dwc3_rtk_type_c_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_rtk_type_c_suspend, dwc3_rtk_type_c_resume)
	.prepare = dwc3_rtk_type_c_prepare,
	.complete = dwc3_rtk_type_c_complete,
};

#define DEV_PM_OPS	(&dwc3_rtk_type_c_pm_ops)
#else
#define DEV_PM_OPS	NULL
#endif /* CONFIG_PM_SLEEP */

static struct platform_driver dwc3_rtk_type_c_driver = {
	.probe		= dwc3_rtk_type_c_probe,
	.remove		= dwc3_rtk_type_c_remove,
	.driver		= {
		.name	= "rtk-dwc3-type_c",
		.of_match_table = of_match_ptr(rtk_dwc3_type_c_match),
		.pm = DEV_PM_OPS,
	},
};

static int __init dwc3_rtk_type_c_driver_init(void)
{
	return platform_driver_register(&(dwc3_rtk_type_c_driver));
}
module_init(dwc3_rtk_type_c_driver_init);

static void __exit dwc3_rtk_type_c_driver_exit(void)
{
	platform_driver_unregister(&(dwc3_rtk_type_c_driver));
}
module_exit(dwc3_rtk_type_c_driver_exit);

MODULE_ALIAS("platform:rtk-dwc3-type_c");
MODULE_LICENSE("GPL");

