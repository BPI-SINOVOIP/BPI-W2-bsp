/*
 * rtk_edid.h - RTK hdmitx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _RTK_EDID_H_
#define _RTK_EDID_H_

#include "hdmitx.h"

#define HDMI_1PX_IDENTIFIER 0x000C03
#define HDMI_2P0_IDENTIFIER 0xC45DD8

extern struct edid_information hdmitx_edid_info;

int rtk_edid_header_is_valid(const u8 *raw_edid);
bool rtk_edid_block_valid(u8 *raw_edid, int block);
bool rtk_detect_hdmi_monitor(struct edid *edid);
struct edid *rtk_get_base_edid(void);
struct edid *rtk_get_edid(asoc_hdmi_t *hdmi);
int rtk_do_probe_ddc_edid(unsigned char *buf, int block, int len);
bool rtk_edid_is_valid(struct edid *edid);
int rtk_add_edid_modes(struct edid *edid, struct sink_capabilities_t *sink_cap);
void rtk_edid_to_eld(struct edid *edid, struct sink_capabilities_t *sink_cap);

void print_established_modes(u32 est_format);
void print_cea_modes(u64 cea_format, u64 cea_format2, u64 cea_format2_420);
void print_deep_color(u32 var);
void print_color_formats(u32 var);
void print_color_space(u8 var);
void hdmi_print_raw_edid(unsigned char *edid);

/* rtk_edid_filter.c */
int rtk_filter_specific_profuct_vic(struct edid *edid,
	struct sink_capabilities_t *sink_cap);

#endif /* _RTK_EDID_H_*/
