/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#ifndef __SMI_H__
#define __SMI_H__

typedef unsigned int rtk_uint32;
typedef unsigned short rtk_uint16;
typedef unsigned char rtk_uint8;
typedef int rtk_int32;
typedef char rtk_int8;

rtk_int32 smi_reset(rtk_uint32 port, rtk_uint32 pinRST);
rtk_int32 smi_init(rtk_uint32 port, rtk_uint32 pinSCK, rtk_uint32 pinSDA);
rtk_int32 smi_read(rtk_uint32 mAddrs, rtk_uint32 *rData);
rtk_int32 smi_write(rtk_uint32 mAddrs, rtk_uint32 rData);

#endif /* __SMI_H__ */


