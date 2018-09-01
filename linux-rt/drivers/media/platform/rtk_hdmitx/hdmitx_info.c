/*
 * hdmitx_info.c - RTK hdmitx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/platform_device.h>

#include <drm/drm_edid.h>
#include <drm/drm_crtc.h>

#include "hdmitx.h"
#include "hdmitx_api.h"
#include "hdmitx_rpc.h"
#include "rtk_edid.h"

struct vic_format_info {
	unsigned char vic;
	unsigned int width;
	unsigned int height;
	unsigned char fps;
	unsigned char interlace;
};

const struct vic_format_info vic_format_table[] = {
	{  0,    0,    0,  0, 0},
	{  2,  720,  480, 60, 0},
	{  4, 1280,  720, 60, 0},
	{  5, 1920, 1080, 60, 1},
	{  6,  720,  480, 60, 1},
	{ 16, 1920, 1080, 60, 0},
	{ 17,  720,  576, 50, 0},
	{ 19, 1280,  720, 50, 0},
	{ 20, 1920, 1080, 50, 1},
	{ 21,  720,  576, 50, 1},
	{ 31, 1920, 1080, 50, 0},
	{ 32, 1920, 1080, 24, 0},
	{ 33, 1920, 1080, 25, 0},
	{ 34, 1920, 1080, 30, 0},
	{ 93, 3840, 2160, 24, 0},
	{ 94, 3840, 2160, 25, 0},
	{ 95, 3840, 2160, 30, 0},
	{ 96, 3840, 2160, 50, 0},
	{ 97, 3840, 2160, 60, 0},
	{ 98, 4096, 2160, 24, 0},
	{ 99, 4096, 2160, 25, 0},
	{100, 4096, 2160, 30, 0},
	{101, 4096, 2160, 50, 0},
	{102, 4096, 2160, 60, 0},
};
const unsigned int vic_format_number = sizeof(vic_format_table)/sizeof(vic_format_table[0]);

/* EISA ID is based upon compressed ASCII */
const unsigned char eisa_id[] = {
	' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', ' ', ' ', ' ', ' ', ' '
};

static const char * const mode[] = {
	"OFF", "DVI", "HDMI", "Unknow"
};

static const char * const pixel_format[] = {
	"RGB", "YUV422", "YUV444", "YUV420"
};

static const char * const colorimetry[] = {
	"No Data", "SMPTE 170M", "ITU 709", "Extend"
};

static const char * const extended_colorimetry[] = {
	"xvYCC601", "xvYCC709", "sYCC601", "AdobeYCC601",
	"AdobeRGB", "BT2020YcCbcCrx", "BT2020RGB", "Reserved"
};

static const char * const format3d[] = {
	"N/A", "FramePacking", "Side-by-Side", "Top-and-Bottom",
	"FramePacking", "Side-by-Side", "Top-and-Bottom", "N/A"
};

static const char * const hdr_mode[] = {
	"AUTO", "DV", "SDR", "GAMMA",
	"HDR10", "FUTURE", "INPUT", "12B_YUV422",
	"10B_YUV444", "10B_RGB444", "12B_YUV444", "12B_RGB444",
	"DV_ON_INPUT", "DV_ON_LOW_LATENCY_12B422", "Unknow", "Unknow"
};

static const char * const vo_type[] = {
	"ANALOG_AND_DIGITAL",
	"ANALOG_ONLY",
	"DIGITAL_ONLY",
	"DISPLAY_PORT_ONLY",
	"HDMI_AND_DISPLAY_PORT_SAME_SOURCE",
	"HDMI_AND_DISPLAY_PORT_DIFF_SOURCE",
	"DISPLAY_PORT_AND_CVBS_SAME_SOURCE",
	"HDMI_AND_DP_DIFF_SOURCE_WITH_CVBS",
	"FORCE_DP_OFF"
};

static const char * const yes_no[] = {
	"No", "Yes"
};

unsigned char get_vic_format_table_index(unsigned char vic)
{
	int i;
	unsigned char index;

	index = 0;
	for (i = 0; i < vic_format_number; i++) {
		if (vic == vic_format_table[i].vic) {
			index = i;
			break;
		}
	}

	return index;
}

ssize_t show_hdmitx_info(struct device *cd, struct device_attribute *attr, char *buf)
{
	unsigned int ret_count;
	unsigned int vo_standard;
	unsigned char vic_index;
	unsigned char fps;
	unsigned char color_index;
	unsigned char vo_type_index;
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM hdmitx_tv_system;
	struct hdmi_format_setting format;

	RPC_ToAgent_QueryConfigTvSystem(&hdmitx_tv_system);

	tv_system_to_hdmi_format(&hdmitx_tv_system, &format);

	ret_count = sprintf(buf, "------ HDMI Info -----\n");

	vo_standard = hdmitx_tv_system.videoInfo.standard;

	/* Mode:DVI/HDMI/OFF */
	ret_count += sprintf(buf+ret_count, "Mode: %s\n", mode[format.mode&0x3]);

	/* RTK VO_STANDARD */
	ret_count += sprintf(buf+ret_count, "RTK VO_STANDARD: %u\n",
		vo_standard);

	/* VO interface type */
	vo_type_index = (unsigned char)hdmitx_tv_system.interfaceType;
	if (vo_type_index <= 9)
		ret_count += sprintf(buf+ret_count, "VO type: %s\n", vo_type[vo_type_index]);
	else
		ret_count += sprintf(buf+ret_count, "VO type: Unknow\n");

	if (format.mode == FORMAT_MODE_OFF)
		return ret_count;

	/* VIC */
	ret_count += sprintf(buf+ret_count, "VIC: %u\n",
		format.vic);

	/* Resolution: Width x Height I/P fps */
	vic_index = get_vic_format_table_index(format.vic);

	if (format.freq_shift)
		fps = vic_format_table[vic_index].fps - 1;
	else
		fps = vic_format_table[vic_index].fps;

	ret_count += sprintf(buf+ret_count, "Resolution: %ux%u%s @ %uHz\n",
		vic_format_table[vic_index].width,
		vic_format_table[vic_index].height,
		vic_format_table[vic_index].interlace?"I":"P",
		fps);

	/* Pixel format:RGB/YUV422/YUV444/YUV420 */
	ret_count += sprintf(buf+ret_count, "Pixel format: %s\n",
		pixel_format[format.color&0x3]);

	/* Color depth:8 Bits/10 Bits/12 Bits */
	ret_count += sprintf(buf+ret_count, "Color depth: %u Bits\n",
		format.color_depth);

	/* Colorimetry */
	color_index = (hdmitx_tv_system.hdmiInfo.dataByte2>>6)&0x3;
	if (color_index != 0x3) {
		/* Colorimetry C1:C0 */
		ret_count += sprintf(buf+ret_count, "Colorimetry: %s\n",
				colorimetry[color_index]);
	} else {
		/* Extended Colorimetry EC2:EC1:EC0 */
		color_index = (hdmitx_tv_system.hdmiInfo.dataByte3>>4)&0x7;

		ret_count += sprintf(buf+ret_count, "Colorimetry: %s\n",
				extended_colorimetry[color_index]);
	}

	/* 3D:"N/A"/FramePacking/Side-by-Side/Top-and-Bottom */
	ret_count += sprintf(buf+ret_count, "3D: %s\n",
		format3d[format._3d_format&0x7]);

	/* HDR mode */
	ret_count += sprintf(buf+ret_count, "HDR mode: %s\n",
		hdr_mode[format.hdr&0xF]);

	/* HDMI2.0:YES/NO */
	ret_count += sprintf(buf+ret_count, "HDMI2.0: %s\n",
		yes_no[hdmitx_tv_system.hdmiInfo.hdmi2p0_feature&0x1]);

	/* Scramble:YES/NO */
	ret_count += sprintf(buf+ret_count, "Scramble: %s\n",
		yes_no[(hdmitx_tv_system.hdmiInfo.hdmi2p0_feature>>1)&0x1]);

	return ret_count;
}

ssize_t show_edid_info(struct device *cd, struct device_attribute *attr, char *buf)
{
	unsigned int ret_count;
	unsigned int vendor_id;
	unsigned char id_index[3];

	ret_count = sprintf(buf, "------ EDID Info -----\n");

	vendor_id = hdmitx_edid_info.mfg_id[0];
	vendor_id = (vendor_id<<8) | hdmitx_edid_info.mfg_id[1];
	ret_count += sprintf(buf+ret_count, "Vendor ID:%04x\n", vendor_id);

	if (hdmitx_edid_info.hdmi_id == HDMI_2P0_IDENTIFIER)
		ret_count += sprintf(buf+ret_count, "HDMI version:2.0\n");
	else
		ret_count += sprintf(buf+ret_count, "HDMI version:1.x\n");

	/* EISA ID for manufacturer name, using five-bit codes */
	id_index[0] = (vendor_id>>10)&0x1F;
	id_index[1] = (vendor_id>>5)&0x1F;
	id_index[2] = vendor_id&0x1F;
	ret_count += sprintf(buf+ret_count, "TV name:%c%c%c\n",
					eisa_id[id_index[0]],
					eisa_id[id_index[1]],
					eisa_id[id_index[2]]);

	ret_count += sprintf(buf+ret_count, "ProductCode:%02x%02x\n",
					hdmitx_edid_info.prod_code[1],
					hdmitx_edid_info.prod_code[0]);

	ret_count += sprintf(buf+ret_count, "SerialNumber:%08x\n",
					hdmitx_edid_info.serial);

	ret_count += sprintf(buf+ret_count, "ManufactureYear:%u\n",
					1990+hdmitx_edid_info.mfg_year);

	ret_count += sprintf(buf+ret_count, "ManufactureWeek:%u\n",
					hdmitx_edid_info.mfg_week);

	if (hdmitx_edid_info.hdmi_id == HDMI_2P0_IDENTIFIER) {
		ret_count += sprintf(buf+ret_count,
			"Max TMDS character rate:%u\n",
			hdmitx_edid_info.max_tmds_char_rate);

		ret_count += sprintf(buf+ret_count, "Deep Color 420:0x%x\n",
			hdmitx_edid_info.dc_420);
	}
	return ret_count;
}

/* /sys/devices/platform/9800d000.hdmitx/hdmitx_info */
static DEVICE_ATTR(hdmitx_info, 0444, show_hdmitx_info, NULL);
/* /sys/devices/platform/9800d000.hdmitx/edid_info */
static DEVICE_ATTR(edid_info, 0444, show_edid_info, NULL);

void register_hdmitx_sysfs(struct device *dev)
{
	device_create_file(dev, &dev_attr_hdmitx_info);
	device_create_file(dev, &dev_attr_edid_info);
}

