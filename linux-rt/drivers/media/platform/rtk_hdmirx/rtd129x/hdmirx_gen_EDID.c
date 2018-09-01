/*
 * hdmirx_gen_EDID.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/string.h>

#define COLOR_RGB		0
#define COLOR_YUV422	1
#define COLOR_YUV444	2

#define VIC_480P		2
#define VIC_576P		17
#define VIC_720P60		4
#define VIC_1080I60		5
#define VIC_1080P60		16
#define VIC_2160P30		95
#define VIC_2160P60		97

unsigned char base_block[128] = {
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
	0x4A, 0x8B, 0x95, 0x12, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x1A, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78,
	0x8A, 0xA5, 0x8E, 0xA6, 0x54, 0x4A, 0x9C, 0x26,
	0x12, 0x45, 0x46, 0x00, 0x00, 0x00, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
	0x00, 0xFC, 0x00, 0x52, 0x54, 0x44, 0x31, 0x32,
	0x39, 0x35, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02
};

unsigned char cea_hdader_rgb[4] = {0x02, 0x03, 0x1A, 0x41};
unsigned char cea_hdader_yuv422[4] = {0x02, 0x03, 0x1A, 0x51};
unsigned char cea_hdader_yuv444[4] = {0x02, 0x03, 0x1A, 0x61};
unsigned char speaker_alloc[4] = {0x83, 0x01, 0x00, 0x00};
unsigned char vendor_specific[8] = {0x67, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x3C};
unsigned char vendor_specific2p0[8] = {0x67, 0xD8, 0x5D, 0xC4, 0x01, 0x78, 0x80, 0x00};
unsigned char audio_data[4] = {0x23, 0x09, 0x7F, 0x07};
unsigned char colorimetry[4] = {0xE3, 0x05, 0x00, 0x00};
unsigned char detailed_timing[18] = {
	0x8F, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,
	0x10, 0x3E, 0x96, 0x00, 0x20, 0x58, 0x32, 0x00,
	0x00, 0x18
};


/**
 * gernerate_EDID - Generate specific EDID
 * @color: 0 - RGB, 1 - YUV422, 2 - YUV444
 * @vic: Video ID Code
 * @edid_buf: 256 bytes buffer
 */
void gernerate_EDID(unsigned char color, unsigned char vic, unsigned char *edid_buf)
{
	unsigned int index = 0;
	unsigned int i;
	unsigned int sum = 0;

	memset(edid_buf, 0, 256);

	/* Base block */
	memcpy(&edid_buf[index], base_block, sizeof(base_block));
	index += sizeof(base_block);

	/* CEA header */
	switch (color) {
	case COLOR_RGB:
		memcpy(&edid_buf[index], cea_hdader_rgb, sizeof(cea_hdader_rgb));
		break;
	case COLOR_YUV422:
		memcpy(&edid_buf[index], cea_hdader_yuv422, sizeof(cea_hdader_yuv422));
		break;
	case COLOR_YUV444:
		memcpy(&edid_buf[index], cea_hdader_yuv444, sizeof(cea_hdader_yuv444));
		break;
	default:
		memcpy(&edid_buf[index], cea_hdader_rgb, sizeof(cea_hdader_rgb));
		break;
	}
	index += sizeof(cea_hdader_rgb);

	/* Speaker Allocation */
	memcpy(&edid_buf[index], speaker_alloc, sizeof(speaker_alloc));
	index += sizeof(speaker_alloc);

	/* Vendor Specific 1.4b */
	memcpy(&edid_buf[index], vendor_specific, sizeof(vendor_specific));
	index += sizeof(vendor_specific);

	/* Vendor Specific 2.0 */
	if (vic > 64) {
		memcpy(&edid_buf[index], vendor_specific2p0, sizeof(vendor_specific2p0));
		index += sizeof(vendor_specific2p0);
	}

	/* Video Data */
	edid_buf[index++] = 0x41;
	edid_buf[index++] = vic;

	/* Audio Data */
	memcpy(&edid_buf[index], audio_data, sizeof(audio_data));
	index += sizeof(audio_data);

	/* Colorimetry */
	memcpy(&edid_buf[index], colorimetry, sizeof(colorimetry));
	index += sizeof(colorimetry);

	/* Detailed Timing */
	memcpy(&edid_buf[index], detailed_timing, sizeof(detailed_timing));
	index += sizeof(detailed_timing);

	/* Calculate and set checksum */
	for (i = 0x80; i < 0xFF; i++)
		sum += edid_buf[i];
	edid_buf[0xFF] = (0x100-(sum&0xFF))&0xFF;

}

