/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

struct rtl819x_vlan_4k {
	u16	vid;
	u8	untag;
	u8	member;
	u8	fid;
};

#define RTL819X_PORT_NUM_CPU		6
#define RTL819X_NUM_PORTS		7
#define RTL819X_NUM_VLANS		16
#define RTL819X_NUM_VIDS		4096
#define RTL819X_FIDMAX			2


#define RTL819X_HW_PORT_NUM_CPU	8
#define RTL819X_HW_CPUPORT_MASK	(1 << RTL819X_HW_PORT_NUM_CPU)
#define RTL819X_HW_PORT_ALL_MASK	0x7f // (port0~port6)

int rtl819x_swconfig_init(struct net_device *netdev);