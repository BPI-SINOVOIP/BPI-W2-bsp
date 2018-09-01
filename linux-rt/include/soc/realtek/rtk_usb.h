/*
 * rtk_usb.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __RTK_USB_H_INCLUDED_
#define __RTK_USB_H_INCLUDED_

struct device_node;
struct rtk_usb;

enum usb_port_num {
	USB_PORT_0 = 0,
	USB_PORT_1 = 1,
	USB_PORT_2 = 2,
	USB_PORT_3 = 3,
};

struct rtk_usb *rtk_usb_soc_init(struct device_node *node);

int rtk_usb_soc_free(struct rtk_usb **rtk_usb);

int rtk_usb_port_suspend_resume(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool is_suspend);

int rtk_usb_set_hw_l4icg_on_off(struct rtk_usb *rtk_usb,
	    enum usb_port_num port_num, bool on);

int rtk_usb_iso_power_ctrl(struct rtk_usb *rtk_usb,
	    bool power_on);

void rtk_usb_set_charger_power(struct rtk_usb *rtk_usb, unsigned int val);

#endif // __RTK_USB_H_INCLUDED_
