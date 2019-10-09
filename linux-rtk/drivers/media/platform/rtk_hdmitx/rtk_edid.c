/*
 * rtk_edid.c - RTK hdmitx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * Based on linux/drivers/gpu/drm/drm_edid.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <sound/pcm.h>
#include <drm/drm_edid.h>
#include <drm/drm_crtc.h>

#include "rtk_edid.h"
#include "hdmitx.h"
#include "hdmitx_api.h"
#include "hdmitx_rpc.h"

#define EDID_EST_TIMINGS 16
#define EDID_STD_TIMINGS 8
#define EDID_DETAILED_TIMINGS 4

struct edid_information hdmitx_edid_info;

static const char default_edid[] = {/* 1080P */
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4A, 0x8B, 0x95, 0x12, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x1A, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78, 0x8A, 0xA5, 0x8E, 0xA6, 0x54, 0x4A, 0x9C, 0x26,
	0x12, 0x45, 0x46, 0x21, 0x08, 0x00, 0xD1, 0xC0, 0x81, 0xC0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
	0x45, 0x00, 0x20, 0xC2, 0x31, 0x00, 0x00, 0x1E, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E, 0x20,
	0x6E, 0x28, 0x55, 0x00, 0x20, 0xC2, 0x31, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x32,
	0x4B, 0x18, 0x3C, 0x0B, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC,
	0x00, 0x52, 0x54, 0x44, 0x31, 0x32, 0x39, 0x35, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xAC,
	0x02, 0x03, 0x20, 0x71, 0x83, 0x01, 0x00, 0x00, 0x67, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x3C,
	0x47, 0x90, 0x1F, 0x05, 0x14, 0x04, 0x11, 0x02, 0x23, 0x09, 0x7F, 0x07, 0xE3, 0x05, 0x03, 0x00,
	0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x20, 0xC2, 0x31, 0x00,
	0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7D
};


static const struct drm_display_mode edid_est_modes[] = {
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 40000, 800, 840,
		   968, 1056, 0, 600, 601, 605, 628, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@60Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 36000, 800, 824,
		   896, 1024, 0, 600, 601, 603,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@56Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 656,
		   720, 840, 0, 480, 481, 484, 500, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@75Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 31500, 640, 664,
		   704,  832, 0, 480, 489, 491, 520, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@72Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 30240, 640, 704,
		   768,  864, 0, 480, 483, 486, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@67Hz */
	{ DRM_MODE("640x480", DRM_MODE_TYPE_DRIVER, 25200, 640, 656,
		   752, 800, 0, 480, 490, 492, 525, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 640x480@60Hz */
	{ DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 35500, 720, 738,
		   846, 900, 0, 400, 421, 423,  449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 720x400@88Hz */
	{ DRM_MODE("720x400", DRM_MODE_TYPE_DRIVER, 28320, 720, 738,
		   846,  900, 0, 400, 412, 414, 449, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 720x400@70Hz */
	{ DRM_MODE("1280x1024", DRM_MODE_TYPE_DRIVER, 135000, 1280, 1296,
		   1440, 1688, 0, 1024, 1025, 1028, 1066, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1280x1024@75Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 78800, 1024, 1040,
		   1136, 1312, 0,  768, 769, 772, 800, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1024x768@75Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 75000, 1024, 1048,
		   1184, 1328, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 1024x768@70Hz */
	{ DRM_MODE("1024x768", DRM_MODE_TYPE_DRIVER, 65000, 1024, 1048,
		   1184, 1344, 0,  768, 771, 777, 806, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 1024x768@60Hz */
	{ DRM_MODE("1024x768i", DRM_MODE_TYPE_DRIVER, 44900, 1024, 1032,
		   1208, 1264, 0, 768, 768, 776, 817, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_INTERLACE) }, /* 1024x768@43Hz */
	{ DRM_MODE("832x624", DRM_MODE_TYPE_DRIVER, 57284, 832, 864,
		   928, 1152, 0, 624, 625, 628, 667, 0,
		   DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC) }, /* 832x624@75Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 49500, 800, 816,
		   896, 1056, 0, 600, 601, 604,  625, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@75Hz */
	{ DRM_MODE("800x600", DRM_MODE_TYPE_DRIVER, 50000, 800, 856,
		   976, 1040, 0, 600, 637, 643, 666, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 800x600@72Hz */
	{ DRM_MODE("1152x864", DRM_MODE_TYPE_DRIVER, 108000, 1152, 1216,
		   1344, 1600, 0,  864, 865, 868, 900, 0,
		   DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC) }, /* 1152x864@75Hz */
};

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


static const u8 edid_header[] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};

static u8 svds[32] = {0x00};//Short Video Descriptors


struct detailed_mode_closure {
	struct sink_capabilities_t *cap;
	struct edid *edid;
	bool preferred;
	u32 quirks;
	int modes;
};

typedef void detailed_cb(struct detailed_timing *timing, void *closure);
void hdmi_print_raw_edid(unsigned char *edid);

int rtk_edid_header_is_valid(const u8 *raw_edid)
{
	int i, score = 0;

	for (i = 0; i < sizeof(edid_header); i++)
		if (raw_edid[i] == edid_header[i])
			score++;

	return score;
}

bool rtk_edid_block_valid(u8 *raw_edid, int block)
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
		HDMI_ERROR("EDID checksum is invalid, remainder is %d", csum);

		/* allow CEA to slide through, switches mangle this */
		if (raw_edid[0] != 0x02)
			goto bad;
	}

	/* per-block-type checks */
	switch (raw_edid[0]) {
	case 0: /* base */
		if (edid->version != 1) {
			HDMI_ERROR("EDID has major version %d, instead of 1", edid->version);
			goto bad;
		}

		if (edid->revision > 4)
			HDMI_DEBUG("EDID minor > 4, assuming backward compatibility");
		break;

	default:
		break;
	}

	return 1;

bad:
    hdmitx_set_error_code(HDMI_ERROR_INVALID_EDID);
	if (raw_edid) {
		HDMI_ERROR("Raw EDID:");
		print_hex_dump(KERN_ERR, " \t", DUMP_PREFIX_NONE, 16, 1, raw_edid, EDID_LENGTH, false);
	}
	return 0;
}

bool rtk_edid_is_valid(struct edid *edid)
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

void print_established_modes(u32 est_format)
{
	int i, freq;

	printk("\n%12s : \n", "EST TIMEINGS");

	for (i = 0; i <= EDID_EST_TIMINGS; i++) {
		if ((est_format >> i) & 1) {
			freq = ((edid_est_modes[i].clock*1000)/(edid_est_modes[i].htotal*edid_est_modes[i].vtotal));
			printk("%12s   [%d]%s @%d Hz\n", " ", i, edid_est_modes[i].name, freq);
		}
	}

}

static int add_established_modes(struct edid *edid, u32 *est_format)
{
	unsigned long est_bits = edid->established_timings.t1 |
		(edid->established_timings.t2 << 8) |
		((edid->established_timings.mfg_rsvd & 0x80) << 9);
	int i, modes = 0;

	for (i = 0; i <= EDID_EST_TIMINGS; i++) {
		if (est_bits & (1<<i))
			modes++;
	}

	*est_format = est_bits;

	return modes;
}

void print_cea_modes(u64 cea_format, u64 cea_format2, u64 cea_format2_420)
{
	int i, freq;

	if (cea_format == 0) {
		HDMI_INFO("no matching video format found");
		return;
	}

	HDMI_INFO(" VIDEO DATA: ");

	for (i = 0; i < ARRAY_SIZE(edid_cea_modes); i++) {

		if (i < 64) {
			if ((cea_format >> i) & 1ULL) {
				if (edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq = ((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq = ((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				HDMI_INFO("[%02d]%-10s @%d Hz", i+1, edid_cea_modes[i].name, freq);
			}
		} else if (i < 128) {
			if ((cea_format2 >> (i-64)) & 1ULL) {
				if (edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq = ((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq = ((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				HDMI_INFO("[%02d]%-10s @%d Hz", i+1, edid_cea_modes[i].name, freq);
			}
		}
	}

	for (i = 64; i < ARRAY_SIZE(edid_cea_modes); i++) {
		if (i < 128) {
			if ((cea_format2_420 >> (i-64)) & 1ULL) {
				if (edid_cea_modes[i].flags & DRM_MODE_FLAG_INTERLACE)
					freq = ((edid_cea_modes[i].clock*1000)/((edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal)/2));
				else
					freq = ((edid_cea_modes[i].clock*1000)/(edid_cea_modes[i].htotal*edid_cea_modes[i].vtotal));
				HDMI_INFO("[%02d]%-10s @%d Hz(YCbCr420)", i+1, edid_cea_modes[i].name, freq);
			}
		}
	}

}

/* Tag Code */
#define AUDIO_BLOCK	0x01
#define VIDEO_BLOCK     0x02
#define VENDOR_BLOCK    0x03
#define SPEAKER_BLOCK	0x04
#define VESA_DISPLAY_TRANSFER_BLOCK	0x05
#define USE_EXTENDED_TAG	0x07

/* Extended Tag Codes */
#define VIDEO_CAPABILITY_DATA_BLOCK			0x00
#define VENDOR_SPECIFIC_VIDEO_DATA_BLOCK	0x01
#define VESA_DISPLAY_DEVICE_DATA_BLOCK		0x02
#define VESA_VIDEO_TIMING_BLOCK_EXTENSION	0x03
#define COLORIMETRY_DATA_BLOCK				0x05
#define HDR_STATIC_METADATA_DATA_BLOCK		0x06
#define HDR_DYNAMIC_METADATA_DATA_BLOCK		0x07
#define VIDEO_FORMAT_PERFERENCE_DATA_BLOCK	0x0D
#define YCBCR420_VIDEO_DATA_BLOCK			0x0E
#define YCBCR420_CAPABILITY_MAP_DATA_BLOCK	0x0F
#define VENDOR_SPECIFIC_AUDIO_DATA_BLOCK	0x11
#define ROOM_CONFIGURATION_DATA_BLOCK		0x13
#define SPEAKER_LOCATION_DATA_BLOCK			0x14
#define INFOFRAME_DATA_BLOCK				0x20

#define EDID_BASIC_AUDIO	(1 << 6)
#define EDID_CEA_YCRCB444	(1 << 5)
#define EDID_CEA_YCRCB422	(1 << 4)
#define EDID_CEA_VCDB_QS	(1 << 6)

/**
 * Search EDID for CEA extension block.
 */
u8 *rtk_find_cea_extension(struct edid *edid)
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

static int do_cea_modes(u8 *db, u8 len, u64 *cea_format, u64 *cea_format2)
{
	u8 *mode;
	u64 cea_mode = 0;
	int modes = 0;

	memset(&svds, 0, sizeof(svds));/* Clear svds */

	for (mode = db; mode < db + len; mode++) {

		cea_mode = (*mode & 127) - 1; /* CEA modes are numbered 1..127 */
		if (cea_mode < ARRAY_SIZE(edid_cea_modes)) {

			if (cea_mode <= 63)
				*cea_format |= 1ULL<<cea_mode;
			else if (cea_mode <= 127)
				*cea_format2 |= 1ULL<<(cea_mode-64);

			if ((mode-db) < 32)
				svds[mode-db] = (*mode & 127);

			modes++;
		}
	}

	return modes;
}

static void do_cea_420modes(u8 *db, u8 len, u64 *cea_420format)
{
	u8 *mode;
	u64 cea_mode = 0;

	for (mode = db; mode < db + len; mode++) {
		cea_mode = (*mode & 127) - 1; /* CEA modes are numbered 1..127 */
		if (cea_mode < ARRAY_SIZE(edid_cea_modes)) {
			if (cea_mode >= 64)
				*cea_420format |= 1ULL<<(cea_mode-64);
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
	u8 *cea = rtk_find_cea_extension(edid);
	u8 *db;
	u8 dbl;
	int modes = 0;

	if (cea && cea_revision(cea) >= 3) {
		int i, start, end;

		if (cea_db_offsets(cea, &start, &end))
			return 0;

		for_each_cea_db(cea, i, start, end) {
			db = &cea[i];
			dbl = cea_db_payload_len(db);

			if (cea_db_tag(db) == VIDEO_BLOCK)
				modes += do_cea_modes(db+1, dbl, video_format, video_format2);
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

	/* Prevent overwrite 2.0 ID */
	if (hdmitx_edid_info.hdmi_id != HDMI_2P0_IDENTIFIER)
		hdmitx_edid_info.hdmi_id = hdmi_id;

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

	hdmitx_edid_info.hdmi_id = hdmi_id;

	return hdmi_id == HDMI_2P0_IDENTIFIER;
}

static const char * const dpc_str[] = {
	"6 bit", "8 bit", "10 bit", "12 bit",
	"14 bit", "16 bit"
};
void print_deep_color(u32 var)
{
	int i;

	printk("[HDMITx]Color Bit Depth: ");
	for (i = 0; i < 6; i++) {
		if ((var >> i) & 1)
			printk("%s,", dpc_str[i]);
	}
	printk("\n");
}

static const char * const color_format_str[] = {
	"RGB444", "YCrCb444", "YCrCb422"
};
void print_color_formats(u32 var)
{
	int i;

	printk("[HDMITx]COLOR FORMAT: ");
	for (i = 0; i < 3; i++) {
		if ((var >> i) & 1)
			printk("%s,", color_format_str[i]);
	}
	printk("\n");
}

static const char * const color_space_str[] = {
	"xyYCC601", "xvYCC709", "sYCC601", "AdobeYCC601",
	"AdobeRGB", "BT2020_cYCC", "BT2020_YCC", "BT2020_RGB"
};
void print_color_space(u8 var)
{
	int i;

	printk("[HDMITx]COLORIMETRY: ");
	for (i = 0; i < 8; i++) {
		if ((var >> i) & 1)
			printk("%s, ", color_space_str[i]);
	}
	printk("\n");
}

static void rtk_add_display_info(struct edid *edid, struct Video_Display_Info *info)
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
		/* info->bpc |= RTK_EDID_DIGITAL_DEPTH_6; */
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
		/* info->bpc |= RTK_EDID_DIGITAL_DEPTH_14; */
		break;
	case DRM_EDID_DIGITAL_DEPTH_16:
		/* info->bpc |= RTK_EDID_DIGITAL_DEPTH_16; */
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
	unsigned int i, n;
	u8 *det_base = ext + 5;

	if (ext[0x01] != 1)
		return; /* unknown version */

	n = min_t(unsigned int, ext[0x02], 6);
	for (i = 0; i < n; i++)
		cb((struct detailed_timing *)(det_base + 18 * i), closure);
}

static void rtk_for_each_detailed_block(u8 *raw_edid, detailed_cb *cb, void *closure)
{
	int i;
	struct edid *edid = (struct edid *)raw_edid;

	if (edid == NULL)
		return;

	/* Parsing No.1-4 Detailed Timing Descriptor of basic edid, start from 0x36 */
	for (i = 0; i < EDID_DETAILED_TIMINGS; i++)
		cb(&(edid->detailed_timings[i]), closure);

	/* Parsing Detailed Timing Descriptor of extension blk */
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
static void rtk_drm_mode_do_interlace_quirk(struct drm_display_mode *mode, struct detailed_pixel_timing *pt)
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

int rtk_drm_mode_vrefresh(const struct drm_display_mode *mode)
{
	int refresh = 0;
	unsigned int calc_val;

	if (mode->vrefresh > 0) {
		refresh = mode->vrefresh;
	} else if (mode->htotal > 0 && mode->vtotal > 0) {
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
static struct drm_display_mode *rtk_drm_mode_detailed(struct edid *edid, struct detailed_timing *timing, u32 quirks)
{
	struct drm_display_mode *mode;

	struct detailed_pixel_timing *pt = &timing->data.pixel_data;
	unsigned int hactive = (pt->hactive_hblank_hi & 0xf0) << 4 | pt->hactive_lo;
	unsigned int vactive = (pt->vactive_vblank_hi & 0xf0) << 4 | pt->vactive_lo;
	unsigned int hblank = (pt->hactive_hblank_hi & 0xf) << 8 | pt->hblank_lo;
	unsigned int vblank = (pt->vactive_vblank_hi & 0xf) << 8 | pt->vblank_lo;
	unsigned int hsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc0) << 2 | pt->hsync_offset_lo;
	unsigned int hsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x30) << 4 | pt->hsync_pulse_width_lo;
	unsigned int vsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc) << 2 | pt->vsync_offset_pulse_width_lo >> 4;
	unsigned int vsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x3) << 4 | (pt->vsync_offset_pulse_width_lo & 0xf);

	/* ignore tiny modes */
	if (hactive < 64 || vactive < 64)
		return NULL;

	mode = kzalloc(sizeof(struct drm_display_mode), GFP_KERNEL);
	if (!mode)
		return NULL;

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

	rtk_drm_mode_do_interlace_quirk(mode, pt);

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

		newmode = rtk_drm_mode_detailed(closure->edid, timing, closure->quirks);

		if (!newmode) {
			return;
		} else {
			HDMI_DEBUG("[%s] Detailied Timing: Hdisplay(%u), Vdisplay(%u), Clock(%u), vrefresh(%u), flags(0x%x)", __func__,
				newmode->hdisplay, newmode->vdisplay, newmode->clock, newmode->vrefresh, newmode->flags);

			for (j = 0; j < ARRAY_SIZE(edid_cea_modes); j++) {
				if (newmode->hdisplay == edid_cea_modes[j].hdisplay &&
					newmode->vdisplay == edid_cea_modes[j].vdisplay &&
					newmode->clock == edid_cea_modes[j].clock &&
					newmode->vrefresh == edid_cea_modes[j].vrefresh &&
				  ((newmode->flags & DRM_MODE_FLAG_INTERLACE) == (edid_cea_modes[j].flags & DRM_MODE_FLAG_INTERLACE))) {
					HDMI_DEBUG("[%s] vic=%d", __func__, j+1);
					if (j < 64)
						closure->cap->vic |= 1ULL << j;
					else if (j < 128)
						closure->cap->vic2 |= 1ULL << (j-64);

					closure->modes++;
				}
			}
		}
		kfree(newmode);
	}
}

int rtk_add_detailed_modes(struct sink_capabilities_t *sink_cap, struct edid *edid, u32 quirks)
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


int rtk_add_edid_modes(struct edid *edid, struct sink_capabilities_t *sink_cap)
{
	int num_modes = 0;
	u32 quirks = 0;

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

	num_modes += rtk_add_detailed_modes(sink_cap, edid, quirks);
	HDMI_INFO("Detailed Timing Descriptor");
	print_cea_modes(sink_cap->vic, sink_cap->vic2, sink_cap->vic2_420);

	//num_modes += add_cvt_modes(connector, edid);
	//num_modes += add_standard_modes(connector, edid);
	num_modes += add_established_modes(edid, &sink_cap->est_modes);
	//if (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)
		//num_modes += add_inferred_modes(connector, edid);

	num_modes += add_cea_modes(edid, &sink_cap->vic, &sink_cap->vic2);
	rtk_add_display_info(edid, &sink_cap->display_info);

	return num_modes;
}

static void monitor_name(struct detailed_timing *t, void *data)
{
	if (t->data.other_data.type == EDID_DETAIL_MONITOR_NAME)
		*(u8 **)data = t->data.other_data.data.str.str;
}

/**
 * parse_hdmi_VideoCapability_db - parse video capability data block
 * @sink_cap: sink_capabilities_t
 * @db: video capability data block
 *
 * bit   7   6      5         4        3         2         1          0
 *      QY/QS/S_PT1/S_PT0/S_IT1/S_IT0/S_CE1/S_CE0
 */
static void parse_hdmi_VideoCapability_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	sink_cap->vout_edid_data.vcdb = db[2];
	HDMI_DEBUG("[%s] vcdb(0x%02x)", __func__, sink_cap->vout_edid_data.vcdb);
}

/**
 * parse_VendorSpecificVideo_db - parse vendor specific video data block
 * @sink_cap: sink_capabilities_t
 * @db: vendor specific video data block
 *
 * Only store dolby vision/HDR10+ information
 */
static void parse_VendorSpecificVideo_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	struct VIDEO_RPC_VOUT_EDID_DATA *hdr_data;
	unsigned int i;
	unsigned char length;
	unsigned char oui[3];

	length = db[0]&0x1F;
	if (length < 4) {
		HDMI_ERROR("Wrong length in VENDOR_SPECIFIC_VIDEO_DATA_BLOCK");
		goto exit;
	}

	oui[0] = db[2];
	oui[1] = db[3];
	oui[2] = db[4];

	if (length < 5) {
		HDMI_ERROR("No additional payload in VENDOR_SPECIFIC_VIDEO_DATA_BLOCK");
		goto exit;
	}

	hdr_data = &sink_cap->vout_edid_data;

	if ((oui[0] == 0x46) && (oui[1] == 0xD0) && (oui[2] == 0x00)) {
		/* Get Dolby Vision VSVDB payload */
		if (length > 25) {
			HDMI_ERROR("Unknow Dolby Vision version");
			goto exit;
		}
		hdr_data->dolby_len = length-4;
		for (i = 5; i <= length; i++)
			hdr_data->dolby_data[i-5] = db[i];
	} else if ((oui[0] == 0x8B) && (oui[1] == 0x84) && (oui[2] == 0x90)) {
		/* Get HDR10+ */
		hdr_data->hdr10_plus = db[5];
		HDMI_INFO("Found HDR10+ in EDID");
	}

exit:
	return;
}

/**
 * parse_hdmi_colorimetry_db - parse colorimetry data block
 * @sink_cap: sink_capabilities_t
 * @db: colorimetry data block
 *
 * bit         7                   6                    5                4                   3                2             1             0
 *     BT2020_RGB/BT2020_YCC/BT2020_cYCC/AdobeRGB/AdobeYCC601/sYCC601/xvYCC709/xvYCC601
 */
static void parse_hdmi_colorimetry_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	sink_cap->color_space = db[2];
	sink_cap->vout_edid_data.color_space = db[2];
	hdmitx_edid_info.colorimetry = db[2];
	HDMI_DEBUG("[%s] color_space(0x%02x)", __func__, sink_cap->color_space);
}

/**
 * parse_hdmi_hdr_db - parse hdr static metadata data block
 * @sink_cap: sink_capabilities_t
 * @db: video capability data block
 */
static void parse_hdmi_hdr_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	unsigned char length;

	length = db[0]&0x1F;
	if (length >= 3)
		sink_cap->vout_edid_data.metadata_len = length-1;
	else
		sink_cap->vout_edid_data.metadata_len = 2;

	sink_cap->vout_edid_data.et = db[2];
	sink_cap->vout_edid_data.sm = db[3];

	if (length >= 4)
		sink_cap->vout_edid_data.max_luminace = db[4];

	if (length >= 5)
		sink_cap->vout_edid_data.max_frame_avg = db[5];

	if (length >= 6)
		sink_cap->vout_edid_data.min_luminace = db[6];

	HDMI_DEBUG("[%s] et(0x%02x) db(0x%02x) max_lum(0x%02x) max_frame_avg(0x%02x), min_lum(0x%02x)", __func__,
						sink_cap->vout_edid_data.et,
						sink_cap->vout_edid_data.sm,
						sink_cap->vout_edid_data.max_luminace,
						sink_cap->vout_edid_data.max_frame_avg,
						sink_cap->vout_edid_data.min_luminace);

}

/* YCbCr 4:2:0 Video Data Block */
static void parse_hdmi_ycbcr420_video_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	int dbl;

	dbl = cea_db_payload_len(db);
	do_cea_420modes((u8 *)(db+2), dbl-1, &sink_cap->vic2_420);
	HDMI_DEBUG("[%s] vic2_420(0x%08x%08x)", __func__,
		(u32)(sink_cap->vic2_420>>32),
		(u32)(sink_cap->vic2_420&0xFFFFFFFF));
}

/* YCbCr 4:2:0 Capability Map Data Block(Y420CMDB) */
static void parse_hdmi_ycbcr420_cm_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	int dbl;
	u8 *bit_map;
	u8 map_size, byte_count, bit_count;
	u64 vic;

	dbl = cea_db_payload_len(db);

	map_size = dbl-1;
	bit_map = (u8 *)(db+2);

	if (map_size == 0) {
		/* Empty-CapMap, all SVDs support Y420 */
		HDMI_DEBUG("Y420CMDB does not include Capability Bit Map");
		byte_count = 0;
		while ((svds[byte_count] != 0) && (byte_count < 32)) {
			vic = svds[byte_count];
			if (vic >= 65)
				sink_cap->vic2_420 |= 1ULL<<(vic-65);
			byte_count++;
		}
	}

	for (byte_count = 0; byte_count < map_size; byte_count++) {
		for (bit_count = 0; bit_count < 8; bit_count++) {
			if (*bit_map & (0x1 << bit_count)) {
				vic = svds[byte_count*8+bit_count];
				if (vic >= 65)
					sink_cap->vic2_420 |= 1ULL<<(vic-65);
			}
		}
		bit_map++;/* next bit map */
	}

	HDMI_DEBUG("[%s] vic2_420(0x%08x%08x)", __func__,
		(u32)(sink_cap->vic2_420>>32),
		(u32)(sink_cap->vic2_420&0xFFFFFFFF));
}

static bool parse_hdmi_extdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	int dbl;

	if (cea_db_tag(db) != USE_EXTENDED_TAG)
		return false;

	dbl = cea_db_payload_len(db);

	switch (*(db+1)) {
	case VIDEO_CAPABILITY_DATA_BLOCK:
		HDMI_DEBUG("[%s] VIDEO_CAPABILITY_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_hdmi_VideoCapability_db(sink_cap, db);
		break;
	case VENDOR_SPECIFIC_VIDEO_DATA_BLOCK:
		HDMI_DEBUG("[%s] VENDOR_SPECIFIC_VIDEO_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_VendorSpecificVideo_db(sink_cap, db);
		break;
	case VESA_DISPLAY_DEVICE_DATA_BLOCK:
		HDMI_DEBUG("[%s] VESA_DISPLAY_DEVICE_DATA_BLOCK (%u bytes)", __func__, dbl);
		break;
	case VESA_VIDEO_TIMING_BLOCK_EXTENSION:
		HDMI_DEBUG("[%s] VESA_VIDEO_TIMING_BLOCK_EXTENSION (%u bytes)", __func__, dbl);
		break;
	case COLORIMETRY_DATA_BLOCK:
		HDMI_DEBUG("[%s] COLORIMETRY_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_hdmi_colorimetry_db(sink_cap, db);
		break;
	case HDR_STATIC_METADATA_DATA_BLOCK:
		HDMI_DEBUG("[%s] HDR_STATIC_METADATA_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_hdmi_hdr_db(sink_cap, db);
		break;
	case YCBCR420_VIDEO_DATA_BLOCK:
		HDMI_DEBUG("[%s] YCBCR420_VIDEO_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_hdmi_ycbcr420_video_db(sink_cap, db);
		break;
	case YCBCR420_CAPABILITY_MAP_DATA_BLOCK:
		HDMI_DEBUG("[%s] YCBCR420_CAPABILITY_MAP_DATA_BLOCK (%u bytes)", __func__, dbl);
		parse_hdmi_ycbcr420_cm_db(sink_cap, db);
		break;
	case VENDOR_SPECIFIC_AUDIO_DATA_BLOCK:
		HDMI_DEBUG("[%s] VENDOR_SPECIFIC_AUDIO_DATA_BLOCK (%u bytes)", __func__, dbl);
		break;
	case INFOFRAME_DATA_BLOCK:
		HDMI_DEBUG("[%s] INFOFRAME_DATA_BLOCK (%u bytes)", __func__, dbl);
		break;
	default:
		HDMI_INFO("[%s] Unknow Extend Tag(%u) (%u bytes)", __func__, *(db+1), dbl);
		break;
	} /* end of switch (*(db+1)) */

	return true;
}

static void parse_hdmi_vsdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	u8 len = cea_db_payload_len(db);
	u8 HDMI_Video_present = 0;
	int offset = 0;

	int multi_present = 0;
	int i;
	u8 vic_len = 0, hdmi_3d_len = 0;
	u8 specific_3d_len, specific_3d_index, specific_3d_format, index;
	u16 mask = 0;

	if (len >= 4) {
		sink_cap->cec_phy_addr[0] = db[4];
		sink_cap->cec_phy_addr[1] = db[5];
	}

	if (len >= 6) {
		sink_cap->eld[5] |= (db[6] >> 7) & 1;  /* Supports_AI */
		sink_cap->DC_Y444 = (db[6] >> 3) & 1;  /* Supports 4:4:4 in deep color modes */
		if ((db[6] >> 4) & 1)
			sink_cap->display_info.bpc |= RTK_EDID_DIGITAL_DEPTH_10;
		if ((db[6] >> 5) & 1)
			sink_cap->display_info.bpc |= RTK_EDID_DIGITAL_DEPTH_12;
		sink_cap->dvi_dual = db[6] & 1;
	}
	if (len >= 7)
		sink_cap->max_tmds_clock = db[7] * 5;
	if (len >= 8) {
		sink_cap->latency_present[0] = db[8] >> 7; /* Latency_Fields_Present */
		sink_cap->latency_present[1] = (db[8] >> 6) & 1; /* I_Latency_Fields_Present */
		HDMI_Video_present = (db[8] >> 5) & 1; /* HDMI_Video_Present */
	}

	if (db[8] & (1 << 7)) {
		offset += 2;
		if (len >= 9)
			sink_cap->video_latency[0] = db[9];
		if (len >= 10)
			sink_cap->audio_latency[0] = db[10];
	}

	/* I_Latency_Fields_Present */
	if (db[8] & (1 << 6)) {
		offset += 2;
		if (len >= 11)
			sink_cap->video_latency[1] = db[11];
		if (len >= 12)
			sink_cap->audio_latency[1] = db[12];
	}

	if (HDMI_Video_present) {
		offset++;
		if (len >= 8+offset) {
			sink_cap->_3D_present = (db[8+offset] >> 7) & 1;
			multi_present = (db[8+offset] & 0x60) >> 5;
			/* printk("present offset=%d db[8+offset]=0x%x\n",offset,db[8+offset]); */
		}

		offset++;
		if (len >= 8+offset) {
			vic_len = db[8+offset] >> 5;
			hdmi_3d_len = db[8+offset] & 0x1f;
		}

		for (i = 1; i <= vic_len; i++) {
			sink_cap->extended_vic |= (1 << db[8+offset+i]);
			HDMI_DEBUG("sink_cap-> extended_vic = %x db[8+%d+%d]=%x",
				sink_cap->extended_vic, offset, i, db[8+offset+i]);
		}

		for (i = 0; i < vic_len && len >= (9 + offset + i); i++) {
			u8 vic;

			vic = db[9 + offset + i];
		}
		offset += 1 + vic_len;

		/* 3D_Structure_ALL */
		if (multi_present == 1 || multi_present == 2) {
			sink_cap->structure_all = (db[8 + offset] << 8) | db[9 + offset];/* 3D_Structure_ALL_15..0 */

			if (multi_present == 1) {
				/* assigns 3D formats to all of the VICs listed in the first 16 entries */
				mask = 0xffff;
				offset += 2;
			} else if (multi_present == 2) {
				mask = (db[10 + offset] << 8) | db[11 + offset];
				offset += 4;
			} else {
				mask = 0;
			}

			/* 3D_MASK */
			if (mask != 0) {
				for (i = 0; i < 16 ; i++) {
					if ((mask >> i) & 1) {
						sink_cap->_3D_vic[i] = svds[i];
						HDMI_DEBUG("sink_cap->_3D_vic[%d]=%d", i, sink_cap->_3D_vic[i]);
					}
				}
			}
		}

		/* Check specific 3D, 2D_VIC_order and 3D_Structure*/
		if (hdmi_3d_len > multi_present*2) {

			specific_3d_len = hdmi_3d_len-multi_present*2;
			HDMI_DEBUG("specific_3d_len=%u", specific_3d_len);
			index = 0;
			for (i = 0; i < specific_3d_len; i++) {

				specific_3d_format = db[8+offset+i]&0xF;
				specific_3d_index = (db[8+offset+i]>>4)&0xF;
				switch (specific_3d_format) {
				case 0:/* Frame packing */
					HDMI_DEBUG("specific_3d[%d]=VIC(%u) Frame packing", i, svds[specific_3d_index]);
					if (index < 18) {
						sink_cap->spec_3d[index].vic = svds[specific_3d_index];
						sink_cap->spec_3d[index].format = 0;
						index++;
					}
					break;
				case 6:/* Top-and-Bottom */
					HDMI_DEBUG("specific_3d[%d]=VIC(%u) Top-and-Bottom", i, svds[specific_3d_index]);
					if (index < 18) {
						sink_cap->spec_3d[index].vic = svds[specific_3d_index];
						sink_cap->spec_3d[index].format = 6;
						index++;
					}
					break;
				case 8:/* Side-by-Side(Half) */
					HDMI_DEBUG("specific_3d[%d]=VIC(%u) Side-by-Side", i, svds[specific_3d_index]);
					if (index < 18) {
						sink_cap->spec_3d[index].vic = svds[specific_3d_index];
						sink_cap->spec_3d[index].format = 8;
						index++;
					}
					i++;/* Skip 1byte(3D_Detail) */
					break;
				default:
					break;
				}
			}
		} /* end of if (hdmi_3d_len > multi_present*2) */
	} /* end of if (HDMI_Video_present) */

	HDMI_DEBUG("cec addr:0x%x 0x%x", sink_cap->cec_phy_addr[0], sink_cap->cec_phy_addr[1]);
	HDMI_DEBUG("HDMI: DVI dual %d, max TMDS clock %d",
			sink_cap->dvi_dual, sink_cap->max_tmds_clock);
	HDMI_DEBUG("latency present %d %d, video latency %d %d, audio latency %d %d",
		(int) sink_cap->latency_present[0],
		(int) sink_cap->latency_present[1],
		sink_cap->video_latency[0],
		sink_cap->video_latency[1],
		sink_cap->audio_latency[0],
		sink_cap->audio_latency[1]);

	HDMI_DEBUG("HDMI 3D: HDMI_Video_present 0x%x _3D_present 0x%x ,multi_present 0x%x",
		HDMI_Video_present, sink_cap->_3D_present, multi_present);
	HDMI_DEBUG("vic_len %d,hdmi_3d_len %d", vic_len, hdmi_3d_len);
	HDMI_DEBUG("structure_all 0x%x,mask 0x%x", sink_cap->structure_all, mask);

}

static void parse_hdmi_forum_vsdb(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	hdmitx_edid_info.max_tmds_char_rate = db[5]*5;
	hdmitx_edid_info.scdc_capable = db[6];
	hdmitx_edid_info.dc_420 = db[7]&0x7;
}

static void parse_hdmi_audio_db(struct sink_capabilities_t *sink_cap, const u8 *db)
{
	unsigned char *sad;/* Short Audio Descriptor */
	unsigned char sad_count;
	unsigned char len;
	unsigned char i;
	unsigned char j;

	unsigned char coding_type;
	unsigned char channel_count;
	unsigned char sample_freq_all;
	unsigned char sample_size_all;
	unsigned char max_bit_rate_divided_by_8KHz;

	len = cea_db_payload_len(db);
	if ((len%3) != 0) {
		HDMI_ERROR("Invalid length in audio data block, skip parse");
		return;
	}

	sad_count = len/3;
	sad = &db[1];

	/* Start from the basic audio settings */
	i = sink_cap->audio_data.ADB_length/3;
	while ((sad_count > 0) && (i < 10)) {

		sample_size_all = 0;
		max_bit_rate_divided_by_8KHz = 0;

		coding_type = ((sad[0] & 0x78)>>3);
		channel_count = max(2, ((sad[0]&7)+1));
		sample_freq_all = sad[1];

		if (coding_type == 0x01) /* PCM */
			sample_size_all = sad[2];
		else
			max_bit_rate_divided_by_8KHz = sad[2];

		for (j = 0; j < i; j++) {
			if (coding_type == sink_cap->audio_data.ADB[j].coding_type) {
				/* Merge same type */
				sink_cap->audio_data.ADB[j].channel_count =
					max(channel_count, sink_cap->audio_data.ADB[j].channel_count);

				sink_cap->audio_data.ADB[j].sample_freq_all |= sample_freq_all;

				if (coding_type == 0x01)
					sink_cap->audio_data.ADB[j].sample_size_all |= sample_size_all;
				else
					sink_cap->audio_data.ADB[j].max_bit_rate_divided_by_8KHz =
						max(max_bit_rate_divided_by_8KHz, sink_cap->audio_data.ADB[j].max_bit_rate_divided_by_8KHz);
				break;
			}
		}

		if (j >= i) {
			sink_cap->audio_data.ADB[i].coding_type = coding_type;
			sink_cap->audio_data.ADB[i].channel_count = channel_count;
			sink_cap->audio_data.ADB[i].sample_freq_all = sample_freq_all;
			sink_cap->audio_data.ADB[i].sample_size_all = sample_size_all;
			sink_cap->audio_data.ADB[i].max_bit_rate_divided_by_8KHz = max_bit_rate_divided_by_8KHz;
			sink_cap->audio_data.ADB_length += 3;
			i++;
		}

		sad += 3;
		sad_count -= 1;
	}

}

void rtk_edid_to_eld(struct edid *edid, struct sink_capabilities_t *sink_cap)
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
		HDMI_ERROR("ELD: no CEA Extension found");
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
	HDMI_DEBUG("ELD monitor %s", eld + 20);

	eld[0] = 2 << 3;/* ELD version: 2 */

	eld[16] = edid->mfg_id[0];
	eld[17] = edid->mfg_id[1];
	eld[18] = edid->prod_code[0];
	eld[19] = edid->prod_code[1];

	/* Color characteristics */
	sink_cap->vout_edid_data.red_green_lo = edid->red_green_lo;
	sink_cap->vout_edid_data.black_white_lo = edid->black_white_lo;
	sink_cap->vout_edid_data.red_x = edid->red_x;
	sink_cap->vout_edid_data.red_y = edid->red_y;
	sink_cap->vout_edid_data.green_x = edid->green_x;
	sink_cap->vout_edid_data.green_y = edid->green_y;
	sink_cap->vout_edid_data.blue_x = edid->blue_x;
	sink_cap->vout_edid_data.blue_y = edid->blue_y;
	sink_cap->vout_edid_data.white_x = edid->white_x;
	sink_cap->vout_edid_data.white_y = edid->white_y;

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
				HDMI_DEBUG("[%s] AUDIO_BLOCK (%u bytes)", __func__, dbl);
				parse_hdmi_audio_db(sink_cap, db);

				sad_count = dbl / 3;
				if (dbl >= 1)
					memcpy(eld + 20 + mnl, &db[1], dbl);
				break;
			case VIDEO_BLOCK:
				HDMI_DEBUG("[%s] VIDEO_BLOCK (%u bytes)", __func__, dbl);
				break;
			case SPEAKER_BLOCK:
				/* Speaker Allocation Data Block */
				HDMI_DEBUG("[%s] SPEAKER_BLOCK (%u bytes)", __func__, dbl);
				if (dbl >= 1) {
					eld[7] = db[1];
					sink_cap->audio_data.SADB_length = dbl;
					memcpy(sink_cap->audio_data.SADB, &db[1], sizeof(sink_cap->audio_data.SADB));
				}
				break;
			case VENDOR_BLOCK:
				/* HDMI Vendor-Specific Data Block */
				HDMI_DEBUG("[%s] VENDOR_BLOCK (%u bytes)", __func__, dbl);
				if (cea_db_is_hdmi_vsdb(db))
					parse_hdmi_vsdb(sink_cap, db);

				if (cea_db_is_hdmi_forum_vsdb(db))/* HDMI 2.0 */
					parse_hdmi_forum_vsdb(sink_cap, db);
				break;
			case VESA_DISPLAY_TRANSFER_BLOCK:
				HDMI_DEBUG("[%s] VESA_DISPLAY_TRANSFER_BLOCK (%u bytes)", __func__, dbl);
				break;
			case USE_EXTENDED_TAG:
				/* HDMI USE_EXTENDED_TAG Block */
				parse_hdmi_extdb(sink_cap, db);
				break;
			default:
				HDMI_INFO("[%s] Unknow tag(0x%x)", __func__, cea_db_tag(db));
				break;
			}
		} /*end of for_each_cea_db(cea, i, start, end) */
		HDMI_INFO("HDMI version:%s", (hdmitx_edid_info.hdmi_id == HDMI_2P0_IDENTIFIER)?"2.0":"1.4");
	}
	eld[5] |= sad_count << 4;
	eld[2] = (20 + mnl + sad_count * 3 + 3) / 4;

	HDMI_DEBUG("ELD size %d, SAD count %d", (int)eld[2], sad_count);
}

bool rtk_detect_hdmi_monitor(struct edid *edid)
{
	u8 *edid_ext;
	int i;
	int start_offset;
	int end_offset;

	edid_ext = rtk_find_cea_extension(edid);
	if (!edid_ext)
		return false;

	if (cea_db_offsets(edid_ext, &start_offset, &end_offset))
		return false;

	/*
	 * Because HDMI identifier is in Vendor Specific Block,
	 * search it from all data blocks of CEA extension.
	 */
	for_each_cea_db(edid_ext, i, start_offset, end_offset) {
		if (cea_db_is_hdmi_vsdb(&edid_ext[i]))
			return true;
	}

	return false;
}

#define DDC_SEGMENT_ADDR 0x30
int rtk_do_probe_ddc_edid(unsigned char *buf, int block, int len)
{
	struct i2c_adapter *p_adap;
	unsigned char bus_id = 1;
	int i;
	int retry = 5;
	int ret;
	struct i2c_msg msgs[3];
	unsigned char start = block * EDID_LENGTH;
	unsigned char segment = block >> 1;
	unsigned char xfers = segment ? 3 : 2;

	msgs[0].addr = DDC_SEGMENT_ADDR;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &segment;

	msgs[1].addr = DDC_ADDR;
	msgs[1].flags = 0;
	msgs[1].len = 1;
	msgs[1].buf = &start;

	msgs[2].addr = DDC_ADDR;
	msgs[2].flags = I2C_M_RD;
	msgs[2].len = len;
	msgs[2].buf = buf;

	p_adap = i2c_get_adapter(bus_id);
	if (p_adap == NULL) {
		HDMI_ERROR("hdmi get adapter %d failed", bus_id);
		hdmitx_set_error_code(HDMI_ERROR_I2C_ERROR);
		return -ENODEV;
	}

	/* Delay 500 ms after HDMI hot-plug to solve read EDID first time fail */
	msleep(500);

	for (i = 0; i < retry; i++) {
		/* Slow down I2C speed when retry */
		switch (i) {
		case 1:
			HDMI_INFO("Set I2C 80 kbps");
			msgs[0].flags = I2C_M_LOW_SPEED_80;
			msgs[1].flags = I2C_M_LOW_SPEED_80;
			msgs[2].flags = I2C_M_LOW_SPEED_80|I2C_M_RD;
			break;
		case 2:
			HDMI_INFO("Set I2C 66 kbps");
			msgs[0].flags = I2C_M_LOW_SPEED_66;
			msgs[1].flags = I2C_M_LOW_SPEED_66;
			msgs[2].flags = I2C_M_LOW_SPEED_66|I2C_M_RD;
			break;
		case 3:
			HDMI_INFO("Set I2C 33 kbps");
			msgs[0].flags = I2C_M_LOW_SPEED_33;
			msgs[1].flags = I2C_M_LOW_SPEED_33;
			msgs[2].flags = I2C_M_LOW_SPEED_33|I2C_M_RD;
			break;
		case 4:
			HDMI_INFO("Set I2C 10 kbps");
			msgs[0].flags = I2C_M_LOW_SPEED_10;
			msgs[1].flags = I2C_M_LOW_SPEED_10;
			msgs[2].flags = I2C_M_LOW_SPEED_10|I2C_M_RD;
			break;
		default:
			/* Default I2C speed is 100 kbps */
			break;
		}

		ret = i2c_transfer(p_adap, &msgs[3 - xfers], xfers);
		if (ret == xfers)
			return 0;

		ret = show_hpd_status(true);
		if (ret) {
			msleep(500);
			hdmitx_set_error_code(HDMI_ERROR_I2C_ERROR);
			HDMI_ERROR("I2C1 retry %d time(s)", i);
		} else {
			hdmitx_set_error_code(HDMI_ERROR_HPD);
			HDMI_ERROR("stop I2C1 retry %d time(s), pulled out ", i);
			break;
		}
	} /* end of for(i = 0; i < retry; i++) */

	return -1;
}

static u8 *rtk_do_get_edid(void)
{
	int i;
	int j = 0;
	int valid_extensions = 0;
	u8 *block;
	u8 *new;
	int bad_edid_counter = 0;

	block = kmalloc(EDID_LENGTH, GFP_KERNEL);
	if (block == NULL) {
		hdmitx_set_error_code(HDMI_ERROR_NO_MEMORY);
		return NULL;
	}

	/* base block fetch */
	for (i = 0; i < 4; i++) {
		if (rtk_do_probe_ddc_edid(block, 0, EDID_LENGTH))
			goto out;
		if (rtk_edid_block_valid(block, 0)) {
			/* Copy Base block(128bytes) to hdmitx_edid_info */
			memcpy(&hdmitx_edid_info, block, EDID_LENGTH);
			break;
		}
	}
	if (i == 4)
		goto carp;

	/* if there's no extensions, we're done */
	if (block[0x7e] == 0)
		return block;

	new = krealloc(block, (block[0x7e] + 1) * EDID_LENGTH, GFP_KERNEL);
	if (!new) {
		hdmitx_set_error_code(HDMI_ERROR_NO_MEMORY);
		goto out;
	}
	block = new;

	for (j = 1; j <= block[0x7e]; j++) {
		for (i = 0; i < 4; i++) {
			if (rtk_do_probe_ddc_edid(block + (valid_extensions + 1) * EDID_LENGTH, j, EDID_LENGTH))
				goto out;
			if (rtk_edid_block_valid(block + (valid_extensions + 1) * EDID_LENGTH, j)) {
				valid_extensions++;
				break;
			}
		}

		if (i == 4)
			bad_edid_counter++;
	}

	if (valid_extensions != block[0x7e]) {
		block[EDID_LENGTH-1] += block[0x7e] - valid_extensions;
		block[0x7e] = valid_extensions;
		new = krealloc(block, (valid_extensions + 1) * EDID_LENGTH, GFP_KERNEL);
		if (!new) {
			hdmitx_set_error_code(HDMI_ERROR_NO_MEMORY);
			goto out;
		}
		block = new;
	}

	return block;

carp:
	bad_edid_counter++;
	HDMI_ERROR("bad_edid_counter=%d ", bad_edid_counter);

out:
	kfree(block);
	return NULL;
}

/**
 * rtk_get_base_edid - get base block of EDID
 */
struct edid *rtk_get_base_edid(void)
{
	struct edid *base_edid;
	int ret_val;

	base_edid = kmalloc(EDID_LENGTH, GFP_KERNEL);
	if (base_edid == NULL) {
		HDMI_ERROR("%s kmalloc fail", __func__);
		goto out;
	}

	ret_val = rtk_do_probe_ddc_edid((u8 *)base_edid, 0, EDID_LENGTH);
	if (ret_val != 0) {
		HDMI_ERROR("%s fail", __func__);
		kfree(base_edid);
		base_edid = NULL;
	}

out:
	return base_edid;
}

struct edid *rtk_get_edid(asoc_hdmi_t *hdmi)
{
	struct edid *edid = NULL;
	u8 *block;

	hdmi->edid_ptr = rtk_do_get_edid();
	if (hdmi->edid_ptr == NULL) {

		block = kmalloc(EDID_LENGTH*2, GFP_KERNEL);
		if (block == NULL) {
			hdmitx_set_error_code(HDMI_ERROR_NO_MEMORY);
			return NULL;
		}

		HDMI_ERROR("Get EDID fail, assign default EDID");
		memcpy(block, default_edid, EDID_LENGTH*2);
		hdmi->edid_ptr = block;
	}

	edid = (struct edid *)hdmi->edid_ptr;

	return edid;
}

void hdmi_print_raw_edid(unsigned char *edid)
{
	int i;

	if (edid == NULL)
		return;

	HDMI_INFO("RAW EDID:");

	for (i = 0; i < (edid[0x7e]+1)*EDID_LENGTH; i += 16)
		HDMI_INFO("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,",
			edid[i], edid[i+1], edid[i+2], edid[i+3], edid[i+4], edid[i+5], edid[i+6], edid[i+7],
			edid[i+8], edid[i+9], edid[i+10], edid[i+11], edid[i+12], edid[i+13], edid[i+14], edid[i+15]);

}
