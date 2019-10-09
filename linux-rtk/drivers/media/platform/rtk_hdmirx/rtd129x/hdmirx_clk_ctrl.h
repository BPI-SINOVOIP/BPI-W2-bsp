/*
 * hdmirx_clk_ctrl.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#include "v4l2_hdmi_dev.h"

typedef enum {
	CLK_HDMIRX	= 0x1,
	CLK_RXWRAP	= 0x2,
	CLK_MIPI	= 0x4,
	CLK_CBUS	= 0x8,
	CLK_ALL		= 0xF,
	RST_MIPI	= 0x10,
	RST_CBUS	= 0x20,
	RST_RXWRAP	= 0x40,
	RST_HDMIRX	= 0x80
} HDMI_CLK_TYPE;

typedef enum {
	CTL_DISABLE	= 0,
	CTL_ENABLE	= 1
} HDMI_CLK_CTL;

unsigned char is_clock_enabled(HDMI_CLK_TYPE clk_type);
void hdmirx_reset_control(HDMI_CLK_TYPE clk_type, HDMI_CLK_CTL enable);
void hdmirx_clock_control(HDMI_CLK_TYPE clk_type, HDMI_CLK_CTL enable);
void hdmirx_clock_init(struct platform_device *pdev);

