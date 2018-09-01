/*
 * hdmirx_reg.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDMIRX_REG_H__
#define __HDMIRX_REG_H__

#include "HDMI_fw.h"
#include "HDMIRXDDC_fw.h"
#include "DFE_fw.h"
#include "DFE_HDMI_RX_PHY_fw.h"
#include "hdmirx_wrapper_reg.h"
#include "mipi_wrapper_reg.h"
#include "mipi_aphy_reg.h"
#include "mipi_dphy_reg.h"
#include "misc_reg.h"


/* Definitions of Bits */
#define _ZERO                       0x00
#define _BIT0                       0x01
#define _BIT1                       0x02
#define _BIT2                       0x04
#define _BIT3                       0x08
#define _BIT4                       0x10
#define _BIT5                       0x20
#define _BIT6                       0x40
#define _BIT7                       0x80
#define _BIT8                       0x0100
#define _BIT9                       0x0200
#define _BIT10                      0x0400
#define _BIT11                      0x0800
#define _BIT12                      0x1000
#define _BIT13                      0x2000
#define _BIT14                      0x4000
#define _BIT15                      0x8000
#define _BIT16                      0x10000
#define _BIT17                      0x20000
#define _BIT18                      0x40000
#define _BIT19                      0x80000
#define _BIT20                      0x100000
#define _BIT21                      0x200000
#define _BIT22                      0x400000
#define _BIT23                      0x800000
#define _BIT24                      0x1000000
#define _BIT25                      0x2000000
#define _BIT26                      0x4000000
#define _BIT27                      0x8000000
#define _BIT28                      0x10000000
#define _BIT29                      0x20000000
#define _BIT30                      0x40000000
#define _BIT31                      0x80000000

typedef enum {
	HDMI_TX_CBUS = 0,
	HDMI_RX_MAC = 1,
	HDMI_RX_MHL = 1,
	HDMI_RX_PHY = 1,
	HDMI_RX_DFE = 1,
	HDMI_RX_HDMI_WRAPPER = 2,
	HDMI_RX_DDC = 3,
	HDMI_RX_MIPI_PHY = 4,
	HDMI_RX_MIPI = 5,
	HDMI_RX_CLK90K = 6,
	HDMI_RX_REG_BLOCK_NUM = 7
} HDMI_RX_REG_BASE_TYPE;


unsigned int hdmi_rx_reg_read32 (unsigned int addr_offset, HDMI_RX_REG_BASE_TYPE type);
void hdmi_rx_reg_write32(unsigned int addr_offset, unsigned int value, HDMI_RX_REG_BASE_TYPE type);
void hdmi_rx_reg_mask32(unsigned int addr_offset, unsigned int andMask,
	unsigned int orMask, HDMI_RX_REG_BASE_TYPE type);

#endif/* __HDMIRX_REG_H__ */
