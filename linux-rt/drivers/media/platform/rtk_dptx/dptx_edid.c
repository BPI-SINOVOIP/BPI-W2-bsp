/*
 *  dptx_edid.c - RTK display port driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <sound/pcm.h>

#include "dptx_edid.h"

#define DPTX_EDID_DEBUG 1

#if DPTX_EDID_DEBUG
#define DPTX_EDID_DBG(format, ...) pr_info("[DPTX_EDID_DBG] " format, ## __VA_ARGS__)
#else
#define DPTX_EDID_DBG(format, ...)
#endif

#define DPTX_EDID_ERR(format, ...) pr_err("[DPTX_EDID_ERR] " format, ## __VA_ARGS__)

#define EDID_EST_TIMINGS 16
#define EDID_DETAILED_TIMINGS 4
#define EDID_STANDARD_TIMINGS 8

//Tag Code
#define AUDIO_BLOCK	0x01
#define VIDEO_BLOCK     0x02
#define VENDOR_BLOCK    0x03
#define SPEAKER_BLOCK	0x04
#define VESA_DISPLAY_TRANSFER_BLOCK	0x05
#define USE_EXTENDED_TAG	0x07

//Extended Tag Codes
#define VIDEO_CAPABILITY_DATA_BLOCK			0x00
#define VENDOR_SPECIFIC_VIDEO_DATA_BLOCK	0x01
#define VESA_DISPLAY_DEVICE_DATA_BLOCK		0x02
#define VESA_VIDEO_TIMING_BLOCK_EXTENSION	0x03
#define COLORIMETRY_DATA_BLOCK				0x05
#define HDR_STATIC_METADATA_DATA_BLOCK		0x06
#define YCBCR420_VIDEO_DATA_BLOCK			0x0E
#define YCBCR420_CAPABILITY_MAP_DATA_BLOCK	0x0F
#define VENDOR_SPECIFIC_AUDIO_DATA_BLOCK	0x11
#define INFOFRAME_DATA_BLOCK				0x20

#define EDID_BASIC_AUDIO	(1 << 6)
#define EDID_CEA_YCRCB444	(1 << 5)
#define EDID_CEA_YCRCB422	(1 << 4)
#define EDID_CEA_VCDB_QS	(1 << 6)

struct edid_info dptx_edid_info;

static const u8 edid_header[] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};

static u8 vdb[16] = {0x00};

struct detailed_mode_closure {
	struct sink_capabilities_t *cap;
	struct edid *edid;
	bool preferred;
	u32 quirks;
	int modes;
};

typedef void detailed_cb(struct detailed_timing *timing, void *closure);

/*
 * Probably taken from CEA-861 spec.
 * This table is converted from xorg's hw/xfree86/modes/xf86EdidModes.c.
 */
static const struct drm_display_mode edid_cea_modes[] = {
	/* 1 - 640x480@60Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25175, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 2 - 720x480@60Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 3 - 720x480@60Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 27000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 4 - 1280x720@60Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, },
	/* 5 - 1920x1080i@60Hz */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, },
	/* 6 - 1440x480i@60Hz */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, },
	/* 7 - 1440x480i@60Hz */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, },
	/* 8 - 1440x240@60Hz */
	{ DRM_MODE("1440x240", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1478,
		   1602, 1716, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, },
	/* 9 - 1440x240@60Hz */
	{ DRM_MODE("1440x240", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1478,
		   1602, 1716, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 60, },
	/* 10 - 2880x480i@60Hz */
	{ DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, },
	/* 11 - 2880x480i@60Hz */
	{ DRM_MODE("2880x480i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 60, },
	/* 12 - 2880x240@60Hz */
	{ DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 13 - 2880x240@60Hz */
	{ DRM_MODE("2880x240", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2956,
		   3204, 3432, 0, 240, 244, 247, 262, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 14 - 1440x480@60Hz */
	{ DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 15 - 1440x480@60Hz */
	{ DRM_MODE("1440x480", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1472,
		   1596, 1716, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 16 - 1920x1080@60Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, },
	/* 17 - 720x576@50Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 18 - 720x576@50Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 27000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 19 - 1280x720@50Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, },
	/* 20 - 1920x1080i@50Hz */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, },
	/* 21 - 1440x576i@50Hz */
	{ DRM_MODE("1440x576i", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, },
	/* 22 - 1440x576i@50Hz */
	{ DRM_MODE("1440x576i", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, },
	/* 23 - 1440x288@50Hz */
	{ DRM_MODE("1440x288", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1464,
		   1590, 1728, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, },
	/* 24 - 1440x288@50Hz */
	{ DRM_MODE("1440x288", DRM_MODE_TYPE_DRIVER, 27000, 1440, 1464,
		   1590, 1728, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 50, },
	/* 25 - 2880x576i@50Hz */
	{ DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, },
	/* 26 - 2880x576i@50Hz */
	{ DRM_MODE("2880x576i", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, },
	/* 27 - 2880x288@50Hz */
	{ DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 28 - 2880x288@50Hz */
	{ DRM_MODE("2880x288", DRM_MODE_TYPE_DRIVER, 54000, 2880, 2928,
		   3180, 3456, 0, 288, 290, 293, 312, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 29 - 1440x576@50Hz */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 30 - 1440x576@50Hz */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1592, 1728, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 31 - 1920x1080@50Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, },
	/* 32 - 1920x1080@24Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, },
	/* 33 - 1920x1080@25Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, },
	/* 34 - 1920x1080@30Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, },
	/* 35 - 2880x480@60Hz */
	{ DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 36 - 2880x480@60Hz */
	{ DRM_MODE("2880x480", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2944,
		   3192, 3432, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 60, },
	/* 37 - 2880x576@50Hz */
	{ DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 38 - 2880x576@50Hz */
	{ DRM_MODE("2880x576", DRM_MODE_TYPE_DRIVER, 108000, 2880, 2928,
		   3184, 3456, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 50, },
	/* 39 - 1920x1080i@50Hz */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 72000, 1920, 1952,
		   2120, 2304, 0, 1080, 1126, 1136, 1250, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 50, },
	/* 40 - 1920x1080i@100Hz */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 100, },
	/* 41 - 1280x720@100Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, },
	/* 42 - 720x576@100Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 100, },
	/* 43 - 720x576@100Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 54000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 100, },
	/* 44 - 1440x576i@100Hz */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 100, },
	/* 45 - 1440x576i@100Hz */
	{ DRM_MODE("1440x576", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 100, },
	/* 46 - 1920x1080i@120Hz */
	{ DRM_MODE("1920x1080i", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC |
			DRM_MODE_FLAG_INTERLACE),
	  .vrefresh = 120, },
	/* 47 - 1280x720@120Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 120, },
	/* 48 - 720x480@120Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 120, },
	/* 49 - 720x480@120Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 54000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 120, },
	/* 50 - 1440x480i@120Hz */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 120, },
	/* 51 - 1440x480i@120Hz */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 54000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 120, },
	/* 52 - 720x576@200Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 200, },
	/* 53 - 720x576@200Hz */
	{ DRM_MODE("720x576", DRM_MODE_TYPE_DRIVER, 108000, 720, 732,
		   796, 864, 0, 576, 581, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 200, },
	/* 54 - 1440x576i@200Hz */
	{ DRM_MODE("1440x576i", DRM_MODE_TYPE_DRIVER, 108000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 200, },
	/* 55 - 1440x576i@200Hz */
	{ DRM_MODE("1440x576i", DRM_MODE_TYPE_DRIVER, 108000, 1440, 1464,
		   1590, 1728, 0, 576, 580, 586, 625, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 200, },
	/* 56 - 720x480@240Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 240, },
	/* 57 - 720x480@240Hz */
	{ DRM_MODE("720x480", DRM_MODE_TYPE_DRIVER, 108000, 720, 736,
		   798, 858, 0, 480, 489, 495, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
	  .vrefresh = 240, },
	/* 58 - 1440x480i@240 */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 108000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 240, },
	/* 59 - 1440x480i@240 */
	{ DRM_MODE("1440x480i", DRM_MODE_TYPE_DRIVER, 108000, 1440, 1478,
		   1602, 1716, 0, 480, 488, 494, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC |
			DRM_MODE_FLAG_INTERLACE | DRM_MODE_FLAG_DBLCLK),
	  .vrefresh = 240, },
	/* 60 - 1280x720@24Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, },
	/* 61 - 1280x720@25Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
		   3740, 3960, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, },
	/* 62 - 1280x720@30Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
		   3080, 3300, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, },
	/* 63 - 1920x1080@120Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 120, },
	/* 64 - 1920x1080@100Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 100, },
	/* 65 - 1280x720@24Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 59400, 1280, 3040,
			3080, 3300, 0, 720, 725, 730, 750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 66 - 1280x720@25Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3700,
			3740, 3960, 0, 720, 725, 730, 750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 67 - 1280x720@30Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 3040,
			3080, 3300, 0, 720, 725, 730, 750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 68 - 1280x720@50Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, },
	/* 69 - 1280x720@60Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 74250, 1280, 1390,
		   1430, 1650, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, },
	/* 70 - 1280x720@100Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1720,
		   1760, 1980, 0, 720, 725, 730, 750, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 100, },
	/* 71 - 1280x720@120Hz */
	{ DRM_MODE("1280x720", DRM_MODE_TYPE_DRIVER, 148500, 1280, 1390,
			1430, 1650, 0, 720, 725, 730, 750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 120, },
	/* 72 - 1920x1080@24Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2558,
		   2602, 2750, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 24, },
	/* 73 - 1920x1080@25Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 25, },
	/* 74 - 1920x1080@30Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 74250, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 30, },
	/* 75 - 1920x1080@50Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 50, },
	/* 76 - 1920x1080@60Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 148500, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	  .vrefresh = 60, },
	/* 77 - 1920x1080@100Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2448,
		   2492, 2640, 0, 1080, 1084, 1094, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 100, },
	/* 78 - 1920x1080@120Hz */
	{ DRM_MODE("1920x1080", DRM_MODE_TYPE_DRIVER, 297000, 1920, 2008,
		   2052, 2200, 0, 1080, 1084, 1089, 1125, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 120, },
	/* 79 - 1680x720@24Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400,
			1680, 0, 0, 3300, 0,
			 720, 0, 0,  750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 80 - 1680x720@25Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400,
			1680, 0, 0, 3168, 0,
			 720, 0, 0,  750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 81 - 1680x720@30Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 59400,
			1680, 0, 0, 2640, 0,
			 720, 0, 0,  750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 82 - 1680x720@50Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 82500,
			1680, 0, 0, 2200, 0,
			 720, 0, 0,  750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 50, },
	/* 83 - 1680x720@60Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 99000,
			1680, 0, 0, 2200, 0,
			 720, 0, 0,  750, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 60, },
	/* 84 - 1680x720@100Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 165000,
			1680, 0, 0, 2000, 0,
			 720, 0, 0,  825, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 100, },
	/* 85 - 1680x720@120Hz */
	{ DRM_MODE("1680x720", DRM_MODE_TYPE_DRIVER, 198000,
			1680, 0, 0, 2000, 0,
			 720, 0, 0,  825, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 120, },
	/* 86 - 2560x1080@24Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 99000,
			2560, 0, 0, 3750, 0,
			1080, 0, 0, 1100, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 87 - 2560x1080@25Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 90000,
			2560, 0, 0, 3200, 0,
			1080, 0, 0, 1125, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 88 - 2560x1080@30Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 118800,
			2560, 0, 0, 3520, 0,
			1080, 0, 0, 1125, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 89 - 2560x1080@50Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 185625,
			2560, 0, 0, 3300, 0,
			1080, 0, 0, 1125, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 50, },
	/* 90 - 2560x1080@60Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 198000,
			2560, 0, 0, 3000, 0,
			1080, 0, 0, 1100, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 60, },
	/* 91 - 2560x1080@100Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 371250,
			2560, 0, 0, 2970, 0,
			1080, 0, 0, 1250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 100, },
	/* 92 - 2560x1080@120Hz */
	{ DRM_MODE("2560x1080", DRM_MODE_TYPE_DRIVER, 495000,
			2560, 0, 0, 3300, 0,
			1080, 0, 0, 1250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 120, },
	/* 93 - 3840x2160@24Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 5116, 5204, 5500, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 94 - 3840x2160@25Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 4896, 4984, 5280, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 95 - 3840x2160@30Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 4016, 4104, 4400, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 96 - 3840x2160@50Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000,
			3840, 0, 0, 5280, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 50, },
	/* 97 - 3840x2160@60Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000,
			3840, 0, 0, 4400, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 60, },
	/* 98 - 4096x2160@24Hz */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
			4096, 0, 0, 5500, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 99 - 4096x2160@25Hz */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
			4096, 0, 0, 5280, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 100 - 4096x2160@30Hz */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 297000,
			4096, 0, 0, 4400, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 101 - 4096x2160@50Hz */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000,
			4096, 0, 0, 5280, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 50, },
	/* 102 - 4096x2160@60Hz */
	{ DRM_MODE("4096x2160", DRM_MODE_TYPE_DRIVER, 594000,
			4096, 0, 0, 4400, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 60, },
	/* 103 - 3840x2160@24Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 5116, 5204, 5500, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 24, },
	/* 104 - 3840x2160@25Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 4896, 4984, 5280, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 25, },
	/* 105 - 3840x2160@30Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 297000,
			3840, 4016, 4104, 4400, 0,
			2160, 2168, 2178, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 30, },
	/* 106 - 3840x2160@50Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000,
			3840, 0, 0, 5280, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 50, },
	/* 107 - 3840x2160@60Hz */
	{ DRM_MODE("3840x2160", DRM_MODE_TYPE_DRIVER, 594000,
			3840, 0, 0, 4400, 0,
			2160, 0, 0, 2250, 0,
			DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC),
	 .vrefresh = 60, },
};

static int rtk_edid_header_is_valid(const u8 *raw_edid)
{
	int i, score = 0;

	for (i = 0; i < sizeof(edid_header); i++)
		if (raw_edid[i] == edid_header[i])
			score++;

	return score;
}

static bool rtk_edid_block_valid(u8 *raw_edid, int block)
{
	int i;
	u8 csum = 0;
	struct edid *edid = (struct edid *)raw_edid;

	if (block == 0) {
		int score = rtk_edid_header_is_valid(raw_edid);
		if (score != 8)
			goto bad;		
	}

	for (i = 0; i < EDID_LENGTH; i++)
		csum += raw_edid[i];
	if (csum) {
		DPTX_EDID_ERR("EDID checksum is invalid, remainder is %d\n", csum);		

		/* allow CEA to slide through, switches mangle this */
		if (raw_edid[0] != 0x02)
			goto bad;
	}

	/* per-block-type checks */
	switch (raw_edid[0]) {
	case 0: /* base */
		if (edid->version != 1) {
			DPTX_EDID_DBG("EDID has major version %d, instead of 1\n", edid->version);
			goto bad;
		}

		if (edid->revision > 4)
			DPTX_EDID_DBG("EDID minor > 4, assuming backward compatibility\n");
		break;

	default:
		break;
	}

	return 1;

bad:
	if (raw_edid) {
		DPTX_EDID_DBG("Raw EDID:\n");
		print_hex_dump(KERN_ERR, " \t", DUMP_PREFIX_NONE, 16, 1,raw_edid, EDID_LENGTH, false);
	}
	return 0;
}

static bool rtk_edid_is_valid(struct edid *edid)
{
	int i;
	u8 *raw = (u8 *)edid;

	if (!edid)
		return false;

	for (i = 0; i <= edid->extensions; i++)
		if (!rtk_edid_block_valid(raw + i * EDID_LENGTH, i))
			return false;

	return true;
}

/**
 * Search EDID for CEA extension block.
 */
static u8 *rtk_find_cea_extension(struct edid *edid)
{
	u8 *edid_ext = NULL;
	int i;

	/* No EDID or EDID extensions */
	if (edid == NULL || edid->extensions == 0)
		return NULL;

	/* Find CEA extension */
	for (i = 0; i < edid->extensions; i++) {
		edid_ext = (u8 *)edid + EDID_LENGTH * (i + 1);
		if (edid_ext[0] == CEA_EXT)		
			break;
	}

	if (i == edid->extensions)
		return NULL;

	return edid_ext;
}

static void rtk_add_display_info(struct edid *edid,struct drm_display_info *info)
{
	u8 *edid_ext;

	info->width_mm = edid->width_cm * 10;
	info->height_mm = edid->height_cm * 10;

	/* driver figures it out in this case */
	info->bpc = 0;
	info->color_formats = 0;

	if (edid->revision < 3)
		return;

	if (!(edid->input & DRM_EDID_INPUT_DIGITAL))
		return;

	/* Get data from CEA blocks if present */
	edid_ext = rtk_find_cea_extension(edid);
	if (edid_ext) {
		info->cea_rev = edid_ext[1];

		/* The existence of a CEA block should imply RGB support */
		info->color_formats = DRM_COLOR_FORMAT_RGB444;
		if (edid_ext[3] & EDID_CEA_YCRCB444)
			info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
		if (edid_ext[3] & EDID_CEA_YCRCB422)
			info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
			
	}

	/* Only defined for 1.4 with digital displays */
	if (edid->revision < 4)
		return;
		
	switch (edid->input & DRM_EDID_DIGITAL_DEPTH_MASK) {
	case DRM_EDID_DIGITAL_DEPTH_6:
		//info->bpc |= RTK_EDID_DIGITAL_DEPTH_6;
		break;
	case DRM_EDID_DIGITAL_DEPTH_8:
		info->bpc |= RTK_EDID_DIGITAL_DEPTH_8;
		break;
	case DRM_EDID_DIGITAL_DEPTH_10:
		info->bpc |= RTK_EDID_DIGITAL_DEPTH_10;
		break;
	case DRM_EDID_DIGITAL_DEPTH_12:
		info->bpc |= RTK_EDID_DIGITAL_DEPTH_12;
		break;
	case DRM_EDID_DIGITAL_DEPTH_14:
		//info->bpc |= RTK_EDID_DIGITAL_DEPTH_14;
		break;
	case DRM_EDID_DIGITAL_DEPTH_16:
		//info->bpc |= RTK_EDID_DIGITAL_DEPTH_16;
		break;
	case DRM_EDID_DIGITAL_DEPTH_UNDEF:
	default:
		info->bpc = 0;
		break;
	}

	info->color_formats |= DRM_COLOR_FORMAT_RGB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB444)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB422)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
			
}

static void cea_for_each_detailed_block(u8 *ext, detailed_cb *cb, void *closure)
{
	int i, n = 0;
	u8 d = ext[0x02];
	u8 *det_base = ext + d;

	n = (127 - d) / 18;
	for (i = 0; i < n; i++)
		cb((struct detailed_timing *)(det_base + 18 * i), closure);
}

static void vtb_for_each_detailed_block(u8 *ext, detailed_cb *cb, void *closure)
{
	unsigned int i, n = min((int)ext[0x02], 6);
	u8 *det_base = ext + 5;

	if (ext[0x01] != 1)
		return; /* unknown version */

	for (i = 0; i < n; i++)
		cb((struct detailed_timing *)(det_base + 18 * i), closure);
}

static void rtk_for_each_detailed_block(u8 *raw_edid, detailed_cb *cb, void *closure)
{
	int i;
	struct edid *edid = (struct edid *)raw_edid;

	if (edid == NULL)
		return;
	
	//parsing No.1-4 Detailed Timing Descriptor of basic edid, start from 0x36.
	for (i = 0; i < EDID_DETAILED_TIMINGS; i++) 
		cb(&(edid->detailed_timings[i]), closure);

	//parsing Detailed Timing Descriptor of extension blk.		
	for (i = 1; i <= raw_edid[0x7e]; i++) {
		u8 *ext = raw_edid + (i * EDID_LENGTH);
		switch (*ext) {
		case CEA_EXT:
			cea_for_each_detailed_block(ext, cb, closure);
			break;
		case VTB_EXT:
			vtb_for_each_detailed_block(ext, cb, closure);
			break;
		default:
			break;
		}
	}
}

/*
 * EDID is delightfully ambiguous about how interlaced modes are to be
 * encoded.  Our internal representation is of frame height, but some
 * HDTV detailed timings are encoded as field height.
 *
 * The format list here is from CEA, in frame size.  Technically we
 * should be checking refresh rate too.  Whatever.
 */
static void drm_mode_do_interlace_quirk(struct drm_display_mode *mode,struct detailed_pixel_timing *pt)
{
        int i;
        static const struct {
                int w, h;
        } cea_interlaced[] = {
                { 1920, 1080 },
                {  720,  480 },
                { 1440,  480 },
                { 2880,  480 },
                {  720,  576 },
                { 1440,  576 },
                { 2880,  576 },
        };
 
        if (!(pt->misc & DRM_EDID_PT_INTERLACED))
                return;
 
        for (i = 0; i < ARRAY_SIZE(cea_interlaced); i++) {
                if ((mode->hdisplay == cea_interlaced[i].w) &&
                    (mode->vdisplay == cea_interlaced[i].h / 2)) {
                        mode->vdisplay *= 2;
                        mode->vsync_start *= 2;
                        mode->vsync_end *= 2;
                        mode->vtotal *= 2;
                        mode->vtotal |= 1;
                }
        }
 
        mode->flags |= DRM_MODE_FLAG_INTERLACE;
}

static int rtk_drm_mode_vrefresh(const struct drm_display_mode *mode)
{
        int refresh = 0;
        unsigned int calc_val;

        if (mode->vrefresh > 0)
                refresh = mode->vrefresh;
        else if (mode->htotal > 0 && mode->vtotal > 0) {
                int vtotal;
                vtotal = mode->vtotal;
                /* work out vrefresh the value will be x1000 */
                calc_val = (mode->clock * 1000);
                calc_val /= mode->htotal;
                refresh = (calc_val + vtotal / 2) / vtotal;

                if (mode->flags & DRM_MODE_FLAG_INTERLACE)
                        refresh *= 2;
                if (mode->flags & DRM_MODE_FLAG_DBLSCAN)
                        refresh /= 2;
                if (mode->vscan > 1)
                        refresh /= mode->vscan;
        }
        return refresh;
}

/**
 * drm_mode_detailed - create a new mode from an EDID detailed timing section
 * @edid: EDID block
 * @timing: EDID detailed timing info
 * @quirks: quirks to apply
 *
 * An EDID detailed timing block contains enough info for us to create and
 * return a new struct drm_display_mode.
 */
static struct drm_display_mode *rtk_drm_mode_detailed(struct edid *edid,struct detailed_timing *timing,u32 quirks)
{
	struct drm_display_mode *mode;
		
	struct detailed_pixel_timing *pt = &timing->data.pixel_data;
	unsigned hactive = (pt->hactive_hblank_hi & 0xf0) << 4 | pt->hactive_lo;
	unsigned vactive = (pt->vactive_vblank_hi & 0xf0) << 4 | pt->vactive_lo;
	unsigned hblank = (pt->hactive_hblank_hi & 0xf) << 8 | pt->hblank_lo;
	unsigned vblank = (pt->vactive_vblank_hi & 0xf) << 8 | pt->vblank_lo;
	unsigned hsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc0) << 2 | pt->hsync_offset_lo;
	unsigned hsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x30) << 4 | pt->hsync_pulse_width_lo;
	unsigned vsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc) << 2 | pt->vsync_offset_pulse_width_lo >> 4;
	unsigned vsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x3) << 4 | (pt->vsync_offset_pulse_width_lo & 0xf);
		
	/* ignore tiny modes */
	if (hactive < 64 || vactive < 64)
		return NULL;
		
	mode = kzalloc(sizeof(struct drm_display_mode), GFP_KERNEL);
    if (!mode)
        return NULL;	

//	if (pt->misc & DRM_EDID_PT_STEREO) {
//		HDMI_ERROR("stereo mode not supported");
//		return NULL;
//	}
//	if (!(pt->misc & DRM_EDID_PT_SEPARATE_SYNC)) {
//		HDMI_ERROR("composite sync not supported");
//		return NULL;
//	}
//
//	/* it is incorrect if hsync/vsync width is zero */
//	if (!hsync_pulse_width || !vsync_pulse_width) {
//		HDMI_ERROR("Incorrect Detailed timing.Wrong Hsync/Vsync pulse width");
//		return NULL;
//	}
	
	mode->clock = le16_to_cpu(timing->pixel_clock) * 10;
 
	mode->hdisplay = hactive;
	mode->hsync_start = mode->hdisplay + hsync_offset;
	mode->hsync_end = mode->hsync_start + hsync_pulse_width;
	mode->htotal = mode->hdisplay + hblank;
        
	mode->vdisplay = vactive;
	mode->vsync_start = mode->vdisplay + vsync_offset;
	mode->vsync_end = mode->vsync_start + vsync_pulse_width;
	mode->vtotal = mode->vdisplay + vblank;
	
	/* Some EDIDs have bogus h/vtotal values */
	if (mode->hsync_end > mode->htotal)
		mode->htotal = mode->hsync_end + 1;
	if (mode->vsync_end > mode->vtotal)
		mode->vtotal = mode->vsync_end + 1;
		

	drm_mode_do_interlace_quirk(mode, pt);

	
//	if (quirks & EDID_QUIRK_DETAILED_SYNC_PP) {
//		pt->misc |= DRM_EDID_PT_HSYNC_POSITIVE | DRM_EDID_PT_VSYNC_POSITIVE;
//	}

//	mode->flags |= (pt->misc & DRM_EDID_PT_HSYNC_POSITIVE) ? DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
//	mode->flags |= (pt->misc & DRM_EDID_PT_VSYNC_POSITIVE) ? DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;

//set_size:
//	mode->width_mm = pt->width_mm_lo | (pt->width_height_mm_hi & 0xf0) << 4;
//	mode->height_mm = pt->height_mm_lo | (pt->width_height_mm_hi & 0xf) << 8;
//
//	if (quirks & EDID_QUIRK_DETAILED_IN_CM) {
//		mode->width_mm *= 10;
//		mode->height_mm *= 10;
//	}
		
	mode->vscan = (mode->flags & DRM_MODE_FLAG_DBLSCAN) ? 2 : 1;
	
	mode->vrefresh = rtk_drm_mode_vrefresh(mode);

//	mode->type = DRM_MODE_TYPE_DRIVER;

	return mode;
	
}

static void rtk_do_detailed_mode(struct detailed_timing *timing, void *c)
{
	struct detailed_mode_closure *closure = c;
    struct drm_display_mode *newmode;
	int j;
	
	if (timing->pixel_clock) {	
		
		newmode=rtk_drm_mode_detailed(closure->edid,timing,closure->quirks);
		
		if (!newmode)
			return;
		else
		{
			DPTX_EDID_DBG("[%s] Detailied Timing: Hdisplay(%u), Vdisplay(%u), Clock(%u), vrefresh(%u), flags(0x%x)\n",__FUNCTION__,
							newmode->hdisplay,newmode->vdisplay,newmode->clock,newmode->vrefresh,newmode->flags);

			for (j=0; j< ARRAY_SIZE(edid_cea_modes); j++) 
			{
				if( newmode->hdisplay == edid_cea_modes[j].hdisplay &&
					newmode->vdisplay == edid_cea_modes[j].vdisplay &&
					newmode->clock == edid_cea_modes[j].clock &&
					newmode->vrefresh == edid_cea_modes[j].vrefresh &&
				  ((newmode->flags & DRM_MODE_FLAG_INTERLACE) == (edid_cea_modes[j].flags & DRM_MODE_FLAG_INTERLACE)))
				{	
					DPTX_EDID_DBG("clk = %d, refresh = %d\n", newmode->clock, newmode->vrefresh);
					DPTX_EDID_DBG("[%s] vic=%d\n",__FUNCTION__,j+1);
					if(j<64)
						closure->cap->vic |= 1ULL << j;
					else if(j<128)
						closure->cap->vic2 |= 1ULL << (j-64);

					closure->modes++;					
				}		
			}
		}
		
		kfree(newmode);
	}		
}

static int rtk_add_standard_mode(struct sink_capabilities_t *sink_cap, struct edid *edid)
{
	struct drm_display_mode newmode;
	int i, j;
	int ratio;
	int cnt=0;

	for(i=0; i<EDID_STANDARD_TIMINGS; i++) {
		if(edid->standard_timings[i].hsize == 0x1 &&
			edid->standard_timings[i].vfreq_aspect == 0x1)
			continue;
		newmode.hdisplay = edid->standard_timings[i].hsize * 8 + 248;
		ratio = (edid->standard_timings[i].vfreq_aspect & 0xC0) >> 6;
		if(ratio==0x0)
			newmode.vdisplay = newmode.hdisplay * 10 / 16;
		else if(ratio==0x1)
			newmode.vdisplay = newmode.hdisplay * 3 / 4;
		else if(ratio==0x2)
			newmode.vdisplay = newmode.hdisplay * 4 / 5;
		else if(ratio==0x3)
			newmode.vdisplay = newmode.hdisplay * 9 / 16;
		else
			newmode.vdisplay = 0;

		newmode.vrefresh = (edid->standard_timings[i].vfreq_aspect & 0x3F) + 60;

		DPTX_EDID_DBG("[%s] Standard Timing: Hdisplay(%u), Vdisplay(%u), vrefresh(%u), 0x%x\n",__FUNCTION__,
				newmode.hdisplay, newmode.vdisplay, newmode.vrefresh, edid->standard_timings[i].vfreq_aspect);

		for (j=0; j< ARRAY_SIZE(edid_cea_modes); j++) {
			if( newmode.hdisplay == edid_cea_modes[j].hdisplay &&
				newmode.vdisplay == edid_cea_modes[j].vdisplay &&
				newmode.vrefresh == edid_cea_modes[j].vrefresh) {

				DPTX_EDID_DBG("[%s] vic=%d\n",__FUNCTION__,j+1);
				if(j<64)
					sink_cap->vic |= 1ULL << j;
				else if(j<128)
					sink_cap->vic2 |= 1ULL << (j-64);
				cnt++;
			}
		}
	}
	return cnt;
}

static int rtk_add_detailed_modes(struct sink_capabilities_t *sink_cap, struct edid *edid,u32 quirks)
{
	
	struct detailed_mode_closure closure = {
		sink_cap,
		edid,
		1,
		quirks,
		0
	};

	//if (closure.preferred && !version_greater(edid, 1, 3))
	//	closure.preferred =(edid->features & DRM_EDID_FEATURE_PREFERRED_TIMING);

	rtk_for_each_detailed_block((u8 *)edid, rtk_do_detailed_mode, &closure);

	return closure.modes;
	
}

static int add_established_modes(struct edid *edid, u32 *est_format)
{	
	unsigned long est_bits = edid->established_timings.t1 |
		(edid->established_timings.t2 << 8) |
		((edid->established_timings.mfg_rsvd & 0x80) << 9);
	int i, modes = 0;

	for (i = 0; i <= EDID_EST_TIMINGS; i++) {
		if (est_bits & (1<<i)) {
			modes++;
			}
		}	
		*est_format=est_bits;
	
		return modes;
}

static int do_cea_modes (u8 *db, u8 len, u64 *cea_format, u64 *cea_format2)
{
	u8 * mode; 
	u64 cea_mode=0;
	int modes = 0;
	
	for (mode = db; mode < db + len; mode++)
	{
		cea_mode = (*mode & 127) - 1; /* CEA modes are numbered 1..127 */				
		if (cea_mode < ARRAY_SIZE(edid_cea_modes))
		{
			if(cea_mode<=63)
				*cea_format|= 1ULL<<cea_mode;
			else if(cea_mode<=127)
			{
				*cea_format2|= 1ULL<<(cea_mode-64);

//				if((dptx_edid_info.hdmi_id != HDMI_2P0_IDENTIFIER)&&(cea_mode>=93))//HDMI 1.4 not support 4K VIC
//					dptx_edid_info.hdmi_id = HDMI_2P0_IDENTIFIER;
			}
            if( (mode-db) < 16)
				vdb[mode-db]= *mode;
						
			modes++;			
		}
	}
	
	return modes;
}

static void do_cea_420modes (u8 *db, u8 len, u64 *cea_420format)
{
	u8 * mode;
	u64 cea_mode=0;

	for (mode = db; mode < db + len; mode++)
	{
		cea_mode = (*mode & 127) - 1; /* CEA modes are numbered 1..127 */
		if (cea_mode < ARRAY_SIZE(edid_cea_modes))
		{
			if(cea_mode>=64)
				*cea_420format|= 1ULL<<(cea_mode-64);

		}
	}
}

static int cea_db_payload_len(const u8 *db)
{
	return db[0] & 0x1f;
}

static int cea_db_tag(const u8 *db)
{
	return db[0] >> 5;
}

static int cea_revision(const u8 *cea)
{
	return cea[1];
}

static int cea_db_offsets(const u8 *cea, int *start, int *end)
{
	/* Data block offset in CEA extension block */
	*start = 4;
	*end = cea[2];
	if (*end == 0)
		*end = 127;
	if (*end < 4 || *end > 127)
		return -ERANGE;
	return 0;
}

#define for_each_cea_db(cea, i, start, end) \
	for ((i) = (start); (i) < (end) && (i) + cea_db_payload_len(&(cea)[(i)]) < (end); (i) += cea_db_payload_len(&(cea)[(i)]) + 1)

static int add_cea_modes(struct edid *edid, u64 *video_format, u64 *video_format2)
{
	u8 * cea = rtk_find_cea_extension(edid);
	u8 * db, dbl;
	int modes = 0;

	if (cea && cea_revision(cea) >= 3) {
		int i, start, end;

		if (cea_db_offsets(cea, &start, &end))
			return 0;

		for_each_cea_db(cea, i, start, end) {
			db = &cea[i];
			dbl = cea_db_payload_len(db);

			if (cea_db_tag(db) == VIDEO_BLOCK)
				modes += do_cea_modes (db+1, dbl,video_format,video_format2);
				
		}
	}

	return modes;
}

static bool cea_db_is_hdmi_vsdb(const u8 *db)
{
	int hdmi_id;

	if (cea_db_tag(db) != VENDOR_BLOCK)
		return false;

	if (cea_db_payload_len(db) < 5)
		return false;

	hdmi_id = db[1] | (db[2] << 8) | (db[3] << 16);

	if(dptx_edid_info.hdmi_id!=HDMI_2P0_IDENTIFIER)//Prevent overwrite 2.0 ID
		dptx_edid_info.hdmi_id = hdmi_id;

	return hdmi_id == HDMI_1PX_IDENTIFIER;
}

static bool cea_db_is_hdmi_forum_vsdb(const u8 *db)
{
	int hdmi_id;

	if (cea_db_tag(db) != VENDOR_BLOCK)
		return false;

	if (cea_db_payload_len(db) < 7)
		return false;

	hdmi_id = db[1] | (db[2] << 8) | (db[3] << 16);

	dptx_edid_info.hdmi_id = hdmi_id;

	return hdmi_id == HDMI_2P0_IDENTIFIER;
}

static void print_cea_modes(u64 cea_format, u64 cea_format2, u64 cea_format2_420)
{
	int i,freq;
	
	if(cea_format==0){
		DPTX_EDID_ERR("no matching video format found\n");
		return;
	}
		
	DPTX_EDID_DBG(" VIDEO DATA: \n");
	
	for (i = 0; i < ARRAY_SIZE(edid_cea_modes); i++)
	{
		if(i<64)
		{
			if ((cea_format >> i) & 1ULL)
			{
				if(edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq=((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq=((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				DPTX_EDID_DBG("[%02d]%-10s @%d Hz\n",i+1,edid_cea_modes[i].name,freq);
			}
		}
		else if(i<128)
		{
			if ((cea_format2 >> (i-64)) & 1ULL)
			{
				if(edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq=((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq=((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				DPTX_EDID_DBG("[%02d]%-10s @%d Hz\n",i+1,edid_cea_modes[i].name,freq);
			}
		}
	}

	for (i = 64; i < ARRAY_SIZE(edid_cea_modes); i++)
	{
		if(i<128)
		{
			if ((cea_format2_420 >> (i-64)) & 1ULL)
			{
				if(edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq=((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq=((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				DPTX_EDID_DBG("[%02d]%-10s @%d Hz(YCbCr420)\n",i+1,edid_cea_modes[i].name,freq);
			}
		}
	}

}

static void monitor_name(struct detailed_timing *t, void *data)
{
	if (t->data.other_data.type == EDID_DETAIL_MONITOR_NAME)
		*(u8 **)data = t->data.other_data.data.str.str;
}

/*
bit		7			6			5			4			3			2			1			0
	BT2020_RGB/BT2020_YCC/BT2020_cYCC/AdobeRGB/AdobeYCC601/sYCC601/xvYCC709/xvYCC601/
*/
static void parse_hdmi_colorimetry_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	sink_cap->color_space = db[2];
//	sink_cap->vout_edid_data.color_space = db[2];
	DPTX_EDID_DBG("[%s] color_space(0x%02x)\n", __FUNCTION__, sink_cap->color_space);

}

static void parse_hdmi_hdr_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
/*	sink_cap->vout_edid_data.et = db[2];
	sink_cap->vout_edid_data.sm = db[3];
	sink_cap->vout_edid_data.max_luminace = db[4];
	sink_cap->vout_edid_data.max_frame_avg = db[5];
	sink_cap->vout_edid_data.min_luminace = db[6];
	HDMI_DEBUG("[%s] et(0x%02x) db(0x%02x) max_lum(0x%02x) max_frame_avg(0x%02x), min_lum(0x%02x)",__FUNCTION__,
						sink_cap->vout_edid_data.et,
						sink_cap->vout_edid_data.sm,
						sink_cap->vout_edid_data.max_luminace,
						sink_cap->vout_edid_data.max_frame_avg,
						sink_cap->vout_edid_data.min_luminace);
*/
}

static void parse_hdmi_ycbcr420_video_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	int dbl;

	dbl = cea_db_payload_len(db);
	do_cea_420modes((u8 *)(db+2), dbl-1, &sink_cap->vic2_420);
	DPTX_EDID_DBG("[%s] vic2_420(0x%llx)\n", __FUNCTION__, sink_cap->vic2_420);
}
static bool parse_hdmi_extdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	int dbl;
	
	if (cea_db_tag(db) != USE_EXTENDED_TAG)
		return false;
	
	dbl = cea_db_payload_len(db);
	
	switch (*(db+1)) {
			case VIDEO_CAPABILITY_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] VIDEO_CAPABILITY_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case VENDOR_SPECIFIC_VIDEO_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] VENDOR_SPECIFIC_VIDEO_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case VESA_DISPLAY_DEVICE_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] VESA_DISPLAY_DEVICE_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case VESA_VIDEO_TIMING_BLOCK_EXTENSION:
				DPTX_EDID_DBG("[%s] VESA_VIDEO_TIMING_BLOCK_EXTENSION (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case COLORIMETRY_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] COLORIMETRY_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				parse_hdmi_colorimetry_db(sink_cap,db);
				break;
			case HDR_STATIC_METADATA_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] HDR_STATIC_METADATA_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				parse_hdmi_hdr_db(sink_cap, db);
				break;
			case YCBCR420_VIDEO_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] YCBCR420_VIDEO_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				parse_hdmi_ycbcr420_video_db(sink_cap, db);
				break;
			case YCBCR420_CAPABILITY_MAP_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] YCBCR420_CAPABILITY_MAP_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case VENDOR_SPECIFIC_AUDIO_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] VENDOR_SPECIFIC_AUDIO_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case INFOFRAME_DATA_BLOCK:
				DPTX_EDID_DBG("[%s] INFOFRAME_DATA_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			default:
				DPTX_EDID_DBG("[%s] Unknow Extend Tag(%u) (%u bytes)\n",__FUNCTION__,*(db+1),dbl);
				break;
			}
		
		return true;	
			
}

static void parse_hdmi_vsdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	u8 len = cea_db_payload_len(db);
	u8 HDMI_Video_present=0;
	int offset = 0;

	//int _3D_present=0;
	int multi_present = 0;
	int i;
	u8 vic_len=0, hdmi_3d_len = 0;
	u16 mask=0;
	
	if (len >= 4) {
		sink_cap->cec_phy_addr[0] = db[4];
		sink_cap->cec_phy_addr[1] = db[5];
	}
	
	if (len >= 6) {
		sink_cap->eld[5] |= (db[6] >> 7) & 1;  /* Supports_AI */
		sink_cap->DC_Y444 = (db[6] >> 3) & 1;  /* Supports 4:4:4 in deep color modes */
		if((db[6] >> 4) & 1)
			sink_cap-> display_info.bpc |= RTK_EDID_DIGITAL_DEPTH_10;
		if((db[6] >> 5) & 1)
			sink_cap-> display_info.bpc |= RTK_EDID_DIGITAL_DEPTH_12;
		sink_cap->dvi_dual = db[6] & 1;
	}
	if (len >= 7)
		sink_cap->max_tmds_clock = db[7] * 5;
	if (len >= 8) {
		sink_cap->latency_present[0] = db[8] >> 7; /* Latency_Fields_Present */
		sink_cap->latency_present[1] = (db[8] >> 6) & 1; /* I_Latency_Fields_Present */
		HDMI_Video_present			 = (db[8] >> 5) & 1; /* HDMI_Video_Present */
	}
	
	if (db[8] & (1 << 7)){
		offset += 2;
		if (len >= 9)
			sink_cap->video_latency[0] = db[9];
		if (len >= 10)
			sink_cap->audio_latency[0] = db[10];
	}

	/* I_Latency_Fields_Present */
	if (db[8] & (1 << 6)){	
		offset += 2;
		if (len >= 11)
			sink_cap->video_latency[1] = db[11];
		if (len >= 12)
			sink_cap->audio_latency[1] = db[12];	
	}
	
	if(HDMI_Video_present)
	{
		offset++;
		if (len >= 8+offset){
			//H_3D_present = db[8+offset] & (1 << 7);	
			sink_cap-> _3D_present = (db[8+offset] >> 7) & 1;	
			multi_present= (db[8+offset] & 0x60) >> 5;
			//printk("present offset=%d db[8+offset]=0x%x\n",offset,db[8+offset]);
		}
		
		offset++;
		if (len >= 8+offset){
			vic_len = db[8+offset] >> 5;
			hdmi_3d_len = db[8+offset] & 0x1f;					
		}
		
		for(i = 1; i <= vic_len; i++)
		{					
			sink_cap-> extended_vic |= (1 << db[8+offset+i]);
			DPTX_EDID_DBG("sink_cap-> extended_vic = %x db[8+%d+%d]=%x\n", sink_cap-> extended_vic,offset,i,db[8+offset+i]);
		}
			
		for (i = 0; i < vic_len && len >= (9 + offset + i); i++) {
			u8 vic;
			vic = db[9 + offset + i];
		}
		offset += 1 + vic_len;
	
		/* 3D_Structure_ALL */
		if(multi_present == 1 || multi_present == 2)
			sink_cap->structure_all = (db[8 + offset] << 8) | db[9 + offset];
								
		/* check if 3D_MASK is present */
		if (multi_present == 2){
			mask = (db[10 + offset] << 8) | db[11 + offset];				
	
			for (i = 0; i < 16 ; i++){
				if((mask>>i) & 1){
				sink_cap->_3D_vic[i]= vdb[i];
				DPTX_EDID_DBG("sink_cap->_3D_vic[%d]=%d\n",i,sink_cap->_3D_vic[i]);
				}
			}
			
		}				
		else
			mask = 0xffff;
	}	
	
	DPTX_EDID_DBG("cec addr:0x%x 0x%x\n",sink_cap->cec_phy_addr[0],sink_cap->cec_phy_addr[1]);	
	DPTX_EDID_DBG("HDMI: DVI dual %d, "
		    "max TMDS clock %d, "
		    "latency present %d %d, "
		    "video latency %d %d, "
		    "audio latency %d %d\n",
		    sink_cap->dvi_dual,
		    sink_cap->max_tmds_clock,
	      (int) sink_cap->latency_present[0],
	      (int) sink_cap->latency_present[1],
		    sink_cap->video_latency[0],
		    sink_cap->video_latency[1],
		    sink_cap->audio_latency[0],
		    sink_cap->audio_latency[1]);
			
	DPTX_EDID_DBG("HDMI 3D: HDMI_Video_present 0x%x _3D_present 0x%x ,multi_present 0x%x\n",HDMI_Video_present,sink_cap-> _3D_present,multi_present);
	DPTX_EDID_DBG("vic_len %d,hdmi_3d_len %d\n",vic_len,hdmi_3d_len);
	DPTX_EDID_DBG("structure_all 0x%x,mask 0x%x\n",sink_cap->structure_all,mask);
				
}

static void parse_hdmi_forum_vsdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	dptx_edid_info.max_tmds_char_rate = db[5]*5;
	dptx_edid_info.dc_420 = db[7]&0x7;
}

static unsigned rates_mask[] = {
	SNDRV_PCM_RATE_32000,
	SNDRV_PCM_RATE_44100,
	SNDRV_PCM_RATE_48000,
	SNDRV_PCM_RATE_88200,
	SNDRV_PCM_RATE_96000,
	SNDRV_PCM_RATE_176400,
	SNDRV_PCM_RATE_192000,
};

static void rtk_parse_eld(uint8_t *eld,struct sink_capabilities_t *sink_cap)
{
	uint8_t *sad;
	unsigned char eld_ver,mnl, sad_count, rates, rate_mask;
	unsigned max_channels;
	int i=0;

	eld_ver = eld[0] >> 3;
	if (eld_ver != 2 && eld_ver != 31)
		return;

	mnl = eld[4] & 0x1f;
	if (mnl > 16)
		return;

	sad_count = eld[5] >> 4;
	sad = eld + 20 + mnl;

    sink_cap-> audio_data.ADB_length = sad_count*3 ;
	/* Start from the basic audio settings */
	max_channels = 2;
	rates = 7;
	while (sad_count > 0) {

        sink_cap-> audio_data.ADB[i].coding_type = ((sad[0] & 0x78)>>3);
		sink_cap-> audio_data.ADB[i].channel_count = max((unsigned)sink_cap->audio_data.ADB[i].channel_count,((sad[0]&7)+1u));		
		sink_cap-> audio_data.ADB[i].sample_freq_all |= sad[1];
		
		if(sink_cap-> audio_data.ADB[i].coding_type == 0x01) /* PCM */
			sink_cap-> audio_data.ADB[i].sample_size_all = sad[2];	
		else
			sink_cap-> audio_data.ADB[i].max_bit_rate_divided_by_8KHz = sad[2]; 
	
		switch (sad[0] & 0x78) {
		case 0x08: /* PCM */
			max_channels = max(max_channels,((sad[0]&7)+1u));
			rates |= sad[1];
			break;
		}
		sad += 3;
		sad_count -= 1;
        i++;
	}

	for (rate_mask = i = 0; i < ARRAY_SIZE(rates_mask); i++)
		if (rates & 1 << i)
			rate_mask |= rates_mask[i];

	//sink_cap->sampling_rate_cap = rate_mask;
	//sink_cap->max_channel_cap = max_channels;
	
}

void dptx_edid_to_eld(struct edid *edid, struct sink_capabilities_t *sink_cap)
{
	unsigned char *eld = sink_cap->eld;
	u8 *cea;
	u8 *name;
	u8 *db;
	int sad_count = 0;
	int mnl;
	int dbl;

	memset(eld, 0, sizeof(sink_cap->eld));

	cea = rtk_find_cea_extension(edid);
	if (!cea) {
		DPTX_EDID_ERR("ELD: no CEA Extension found\n");
		return;
	}

	name = NULL;
	rtk_for_each_detailed_block((u8 *)edid, monitor_name, &name);
	for (mnl = 0; name && mnl < 13; mnl++) {
		if (name[mnl] == 0x0a)
			break;
		eld[20 + mnl] = name[mnl];
	}
	eld[4] = (cea[1] << 5) | mnl;
	DPTX_EDID_DBG("ELD monitor %s\n", eld + 20);

	eld[0] = 2 << 3;		/* ELD version: 2 */

	eld[16] = edid->mfg_id[0];
	eld[17] = edid->mfg_id[1];
	eld[18] = edid->prod_code[0];
	eld[19] = edid->prod_code[1];

	/* Color characteristics */
/*	sink_cap->vout_edid_data.red_green_lo = edid->red_green_lo;
	sink_cap->vout_edid_data.black_white_lo = edid->black_white_lo;
	sink_cap->vout_edid_data.red_x = edid->red_x;
	sink_cap->vout_edid_data.red_y = edid->red_y;
	sink_cap->vout_edid_data.green_x = edid->green_x;
	sink_cap->vout_edid_data.green_y = edid->green_y;
	sink_cap->vout_edid_data.blue_x = edid->blue_x;
	sink_cap->vout_edid_data.blue_y = edid->blue_y;
	sink_cap->vout_edid_data.white_x = edid->white_x;
	sink_cap->vout_edid_data.white_y = edid->white_y;*/

	if (cea_revision(cea) >= 3) {
		int i, start, end;

		if (cea_db_offsets(cea, &start, &end)) {
			start = 0;
			end = 0;
		}

		for_each_cea_db(cea, i, start, end) {
			db = &cea[i];
			dbl = cea_db_payload_len(db);

			switch (cea_db_tag(db)) {
			case AUDIO_BLOCK:
				/* Audio Data Block, contains SADs */
				DPTX_EDID_DBG("[%s] AUDIO_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				sad_count = dbl / 3;
				if (dbl >= 1)
					memcpy(eld + 20 + mnl, &db[1], dbl);
				break;
			case VIDEO_BLOCK:
				DPTX_EDID_DBG("[%s] VIDEO_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case SPEAKER_BLOCK:
				/* Speaker Allocation Data Block */
				DPTX_EDID_DBG("[%s] SPEAKER_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				if (dbl >= 1){
					eld[7] = db[1];					
					sink_cap-> audio_data.SADB_length= dbl;
					memcpy(sink_cap-> audio_data.SADB ,&db[1],sizeof(sink_cap->audio_data.SADB));
				}
				break;
			case VENDOR_BLOCK:
				/* HDMI Vendor-Specific Data Block */
				DPTX_EDID_DBG("[%s] VENDOR_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				if (cea_db_is_hdmi_vsdb(db))
					parse_hdmi_vsdb(sink_cap, db);

				if(cea_db_is_hdmi_forum_vsdb(db))//HDMI 2.0
					parse_hdmi_forum_vsdb(sink_cap, db);
				break;
			case VESA_DISPLAY_TRANSFER_BLOCK:
				DPTX_EDID_DBG("[%s] VESA_DISPLAY_TRANSFER_BLOCK (%u bytes)\n",__FUNCTION__,dbl);
				break;
			case USE_EXTENDED_TAG:
				/* HDMI USE_EXTENDED_TAG Block */
				parse_hdmi_extdb(sink_cap, db);
				break;	
			default:
				DPTX_EDID_ERR("[%s] Unknow tag(0x%x)\n", __FUNCTION__, cea_db_tag(db));
				break;
			}
		}
	}
	eld[5] |= sad_count << 4;
	eld[2] = (20 + mnl + sad_count * 3 + 3) / 4;

	DPTX_EDID_DBG("ELD size %d, SAD count %d\n", (int)eld[2], sad_count);

	rtk_parse_eld(eld,sink_cap);
}

int dptx_add_edid_modes(struct edid *edid, struct sink_capabilities_t *sink_cap)
{
	int num_modes = 0;
	u32 quirks=0;

	if (edid == NULL) 
		return 0;
	
	if (!rtk_edid_is_valid(edid)) 
		return 0;
	
	/*
	 * EDID spec says modes should be preferred in this order:
	 * - preferred detailed mode
	 * - other detailed modes from base block
	 * - detailed modes from extension blocks
	 * - CVT 3-byte code modes
	 * - standard timing codes
	 * - established timing codes
	 * - modes inferred from GTF or CVT range information
	 *
	 * We get this pretty much right.
	 *
	 * XXX order for additional mode types in extension blocks?
	 */
	
	num_modes +=rtk_add_standard_mode(sink_cap, edid);
	num_modes +=rtk_add_detailed_modes(sink_cap,edid,quirks);
	DPTX_EDID_DBG("Detailed Timing Descriptor\n");
	print_cea_modes(sink_cap->vic, sink_cap->vic2, sink_cap->vic2_420);
	
	//num_modes += add_cvt_modes(connector, edid);
	//num_modes += add_standard_modes(connector, edid);
	num_modes += add_established_modes(edid,&sink_cap->est_modes);
	//if (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)
		//num_modes += add_inferred_modes(connector, edid);
	
	num_modes += add_cea_modes(edid,&sink_cap->vic,&sink_cap->vic2);
	rtk_add_display_info(edid,&sink_cap->display_info);
	
	return num_modes;
}

