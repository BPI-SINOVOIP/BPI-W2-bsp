/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

//#include <common/rtl865x_common.h>
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_queue.h>
#include <net/rtl/rtl_nic.h>
#include <net/rtl/rtl865x_fdb_api.h>

int32 lan_restrict_getBlockAddr(int32 port , const unsigned char *swap_addr);
extern int __init lan_restrict_init(void);
extern int	 lan_restrict_rcv(struct sk_buff *skb, struct net_device *dev);
extern int32 lan_restrict_CheckStatusByport(int32 port);
