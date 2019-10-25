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
	} power_ctrl_reg;

	bool usb_power_cut;
};

static struct rtk_usb *rtk_usb;

/* set usb charger power */
void rtk_usb_set_charger_power(struct rtk_usb *rtk_usb, unsigned int val)
{
	if (!rtk_usb) return;
}

int rtk_usb_set_hw_l4icg_on_off(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool on)
{
	if (!rtk_usb)
		return 0;

	return 0;
}

static int __isolate_phy_from_a_to_d(struct rtk_usb *rtk_usb)
{
	/* isolate UPHY A->D */
	if (!rtk_usb) return 0;

	return 0;
}

int rtk_usb_iso_power_ctrl(struct rtk_usb *rtk_usb,
	    bool power_on)
{
	if (!rtk_usb) return 0;

	return 0;
}

int rtk_usb_port_suspend_resume(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool is_suspend)
{
	if (!rtk_usb) return 0;

	return 0;
}

struct rtk_usb *rtk_usb_soc_init(struct device_node *sub_node)
{
	if (!rtk_usb)
		rtk_usb = kzalloc(sizeof(struct rtk_usb), GFP_KERNEL);

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
