/*
 *  dptx_aux_channel.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DPTX_AUX_CHANNEL_H__
#define __DPTX_AUX_CHANNEL_H__

#include "dptx_hwapi.h"

bool dptx_aux_native_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucWriteArray);

bool dptx_aux_native_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucReadArray);

bool dptx_aux_i2c_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char ucSlaveAddress,
			unsigned char ucLength,
			unsigned char *pucReadArray,
			unsigned char bMOT);

bool dptx_aux_i2c_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char ucSlaveAddress,
			unsigned char ucLength,
			unsigned char *pucReadArray,
			unsigned char bMOT);

void dptx_aux_initial(struct rtk_dptx_hwinfo *hwinfo);
void dptx_aux_irq_handle(struct rtk_dptx_hwinfo *hwinfo);
#endif  //__DPTX_AUX_CHANNEL_H__
