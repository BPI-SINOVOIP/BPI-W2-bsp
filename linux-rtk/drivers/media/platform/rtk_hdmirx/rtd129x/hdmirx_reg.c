/*
 * hdmirx_reg.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "asm/io.h"
#include "hdmirx_reg.h"

void __iomem *hdmi_rx_base[HDMI_RX_REG_BLOCK_NUM];


unsigned int hdmi_rx_reg_read32 (unsigned int addr_offset, HDMI_RX_REG_BASE_TYPE type)
{
	return readl(hdmi_rx_base[type] + addr_offset);
}

void hdmi_rx_reg_write32 (unsigned int addr_offset, unsigned int value, HDMI_RX_REG_BASE_TYPE type)
{
	writel(value, hdmi_rx_base[type] + addr_offset);
}

void hdmi_rx_reg_mask32(unsigned int addr_offset, unsigned int andMask,
	unsigned int orMask, HDMI_RX_REG_BASE_TYPE type)
{
	hdmi_rx_reg_write32(addr_offset, ((hdmi_rx_reg_read32(addr_offset, type) & (andMask)) | (orMask)), type);
}


