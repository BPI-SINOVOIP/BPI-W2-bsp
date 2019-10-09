/*
 * hdmirx_wrapper.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDMIRX_WRAPPER_H__
#define __HDMIRX_WRAPPER_H__

#define HDMI_MIN_SUPPORT_H_PIXEL    0x40

typedef struct  {
	unsigned int width;
	unsigned int height;
	unsigned int fps;
	unsigned int interlace;
} HDMI_VIC_TABLE_T;

extern const HDMI_VIC_TABLE_T hdmi_vic_table[];

unsigned char hdmirx_wrapper_convert_color_fmt(unsigned char color);
void set_hdmirx_wrapper_interrupt_en(int ver_err_en, int hor_err_en, int polarity_detect_en);
void set_hdmirx_wrapper_active_pixels(unsigned int v_pixel, unsigned int h_pixel);
void set_hdmirx_wrapper_hor_threshold(unsigned int h_threshold);
unsigned int hdmirx_wrapper_get_active_line(void);
unsigned int hdmirx_wrapper_get_active_pixel(void);
void set_hdmirx_wrapper_control_0(int fifo_stage, int fw_dma_en,
	int polarity_set_en, int polarity_set, int yuv_fmt, int hdmirx_en);
void restartHdmiRxWrapperDetection(void);
void hdmirx_wrapper_isr(void);
void hdmi_related_wrapper_init(void);
#endif/* __HDMIRX_WRAPPER_H__ */
