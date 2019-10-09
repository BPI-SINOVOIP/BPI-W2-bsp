/*
 *  dptx_edid.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _DPTX_EDID_H_
#define _DPTX_EDID_H_

#include <drm/drm_edid.h>
#include <drm/drm_crtc.h>
#include <linux/types.h>

#define RTK_EDID_DIGITAL_DEPTH_6       (1 << 0)
#define RTK_EDID_DIGITAL_DEPTH_8       (1 << 1)
#define RTK_EDID_DIGITAL_DEPTH_10      (1 << 2)
#define RTK_EDID_DIGITAL_DEPTH_12      (1 << 3)
#define RTK_EDID_DIGITAL_DEPTH_14      (1 << 4)
#define RTK_EDID_DIGITAL_DEPTH_16      (1 << 5)

#define HDMI_1PX_IDENTIFIER 0x000C03
#define HDMI_2P0_IDENTIFIER 0xC45DD8

struct edid_info {
	// ----- Base Block 128 Bytes Begin -----
	u8 header[8];
	/* Vendor & product info */
	u8 mfg_id[2];
	u8 prod_code[2];
	u32 serial; /* FIXME: byte order */
	u8 mfg_week;
	u8 mfg_year;
	/* EDID version */
	u8 version;
	u8 revision;
	/* Display info: */
	u8 input;
	u8 width_cm;
	u8 height_cm;
	u8 gamma;
	u8 features;
	/* Color characteristics */
	u8 red_green_lo;
	u8 black_white_lo;
	u8 red_x;
	u8 red_y;
	u8 green_x;
	u8 green_y;
	u8 blue_x;
	u8 blue_y;
	u8 white_x;
	u8 white_y;
	/* Est. timings and mfg rsvd timings*/
	struct est_timings established_timings;
	/* Standard timings 1-8*/
	struct std_timing standard_timings[8];
	/* Detailing timings 1-4 */
	struct detailed_timing detailed_timings[4];
	/* Number of 128 byte ext. blocks */
	u8 extensions;
	/* Checksum */
	u8 checksum;
	// ----- Base Block 128 Bytes End ----

	u32 hdmi_id;
	u32 max_tmds_char_rate;
	u8 dc_420;//Deep Color420, [Bit2]DC_48bit_420;[Bit1]DC_36bit_420;[Bit0]:DC_30bit_420
} __attribute__((packed));

struct Audio_desc
{
	unsigned char	coding_type;
	unsigned char	channel_count;
	unsigned char	sample_freq_all;
	unsigned char	sample_size_all;
	unsigned char	max_bit_rate_divided_by_8KHz;
};

struct Audio_Data
{
	char ADB_length;	// Audio Data Block
	struct Audio_desc ADB[10];
	char SADB_length;	// Speaker Allocation Data Block
	unsigned char SADB[3];	
};

struct sink_capabilities_t {
	
	unsigned int hdmi_mode;
	//basic
	unsigned int est_modes;
	
	//audio
	//unsigned int max_channel_cap;
	//unsigned int sampling_rate_cap;	
	unsigned char eld[MAX_ELD_BYTES];
	struct Audio_Data audio_data;
	
	//Vendor-Specific Data Block(VSDB)
	unsigned char cec_phy_addr[2];
	bool support_AI;  // needs info from ACP or ISRC packets
	bool DC_Y444;	// 4:4:4 in deep color modes
	unsigned char color_space;  
	bool dvi_dual;	//DVI Dual Link Operation
	int max_tmds_clock;	/* in MHz */
	bool latency_present[2];
	unsigned char video_latency[2];	/* [0]: progressive, [1]: interlaced */
	unsigned char audio_latency[2];
	
	bool _3D_present;
	__u16 structure_all;
	unsigned char _3D_vic[16];
		
	//video
	struct drm_display_info display_info;
	__u64 vic;//VIC 1~64, BIT0=VIC1
	unsigned char extended_vic;
	__u64 vic2;//VIC 65~128, BIT0=VIC65
	__u64 vic2_420;//YCbCr420 format, VIC 65~128, BIT0=VIC65
//	struct VIDEO_RPC_VOUT_EDID_DATA vout_edid_data;
};

typedef struct{
	struct sink_capabilities_t sink_cap;
	bool sink_cap_available;
	unsigned char *edid_ptr;	
}asoc_dptx_t;

int dptx_add_edid_modes(struct edid *edid, struct sink_capabilities_t *sink_cap);

void dptx_edid_to_eld(struct edid *edid, struct sink_capabilities_t *sink_cap);

//extern void rtk_edid_to_eld(struct edid *edid, struct sink_capabilities_t *sink_cap);

//extern bool rtk_edid_block_valid(u8 *raw_edid, int block);

//extern void hdmi_print_raw_edid(unsigned char *edid);

#endif /* _DPTX_EDID_H_ */

