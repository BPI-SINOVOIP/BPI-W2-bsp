/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef RTL865X_IP_API_H
#define RTL865X_IP_API_H

#define IP_TYPE_NAPT            0x00
#define IP_TYPE_NAT             0x01
#define IP_TYPE_LOCALSERVER     0x02
#define IP_TYPE_RESERVED        0x03

int32 rtl865x_addIp(ipaddr_t intIp, ipaddr_t extIp, uint32 ip_type);
int32 rtl865x_delIp(ipaddr_t extIp);
#endif
