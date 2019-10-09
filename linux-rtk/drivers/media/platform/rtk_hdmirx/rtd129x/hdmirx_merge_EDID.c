/*
 * hdmirx_merge_EDID.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "v4l2_hdmi_dev.h"
#include "hdmiEDID.h"
#include "hdmitx.h"

const unsigned char base_block[128] = {
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4A, 0x8B, 0x95, 0x12, 0x00, 0x00, 0x00, 0x00,
	0xFF, 0x1A, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78, 0x8A, 0xA5, 0x8E, 0xA6, 0x54, 0x4A, 0x9C, 0x26,
	0x12, 0x45, 0x46, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x52, 0x54, 0x44, 0x31, 0x32,
	0x39, 0x35, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02
};

const unsigned char speaker_alloc[4] = {
	0x83, 0x01, 0x00, 0x00
};
const unsigned int speaker_alloc_size = sizeof(speaker_alloc);

const unsigned char vendor_specific[8] = {
	0x67, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x00, 0x3C
};
const unsigned int vendor_specific_size = sizeof(vendor_specific);

const unsigned char colorimetry[4] = {
	0xE3, 0x05, 0x00, 0x00
};
const unsigned int colorimetry_size = sizeof(colorimetry);

/**
 * int rx_video_support - RX support VIC list
 */
#define VIDEO_ARRAY_SIZE 9
const int rx_video_support[VIDEO_ARRAY_SIZE] = {
	2, 4, 5, 16, 17, 20, 31, 32, 34
};

/**
 * Audio format code
 * 0x1:PCM,  0x2:AC-3,  0x3:MPEG1-L1/L2,  0x4:MPEG1-L3(MP3)
 * 0x5:MPEG2(multi-ch),  0x6:AAC,  0x7:DTS,  0x8: ATRAC
 * 0x9:One-Bit Audio,  0xa:AC-3 Plus,  0xb:DTS-HD,  0xc:MLP(TrueHD)
 * 0xd:DST,  0xe:WMA Pro
 */
#define AUDIO_ARRAY_SIZE 6
const struct Audio_desc rx_audio_support[AUDIO_ARRAY_SIZE] = {
	/* PCM: 2CH, 32/44.1/48/88.2/96/176.4/192, 16bit/20bit/24bit */
	{.coding_type = 0x1,
	 .channel_count = 2,
	 .sample_freq_all = 0x7F,
	 .sample_size_all = 0x7,},
	/* AC3: 6CH, 32/44.1/48, MaxBitRate 640kHz */
	{.coding_type = 0x2,
	 .channel_count = 6,
	 .sample_freq_all = 0x7,
	 .max_bit_rate_divided_by_8KHz = 0x50,},
	/* DTS: 6CH, 32/44.1/48, MaxBitRate 1536kHz */
	{.coding_type = 0x7,
	 .channel_count = 6,
	 .sample_freq_all = 0x7,
	 .max_bit_rate_divided_by_8KHz = 0xC0,},
	/* AAC: 8CH, 32/44.1/48/88.2/96, MaxBitRate 2040kHz */
	{.coding_type = 0x6,
	 .channel_count = 8,
	 .sample_freq_all = 0x1F,
	 .max_bit_rate_divided_by_8KHz = 0xFF,},
	/* DTS-HD: 6CH, 32/44.1/48 */
	{.coding_type = 0xB,
	 .channel_count = 6,
	 .sample_freq_all = 0x7,},
	/* AC-3 Plus: 8CH, 32/44.1/48 */
	{.coding_type = 0xA,
	 .channel_count = 8,
	 .sample_freq_all = 0x7,},
};

/**
 * struct merge_edid_data
 * @color_formats: [Bit2] YUV422, [Bit1] YUV444, [Bit0] RGB
 * @video_size: number of VICs in video_list
 * @video_list: merged VICs
 * @audio_size: number of audio data in audio_list
 * @audio_list: merged audio data
 */
struct merge_edid_data {
	int color_formats;
	int	video_size;
	int video_list[VIDEO_ARRAY_SIZE];
	int audio_size;
	struct Audio_desc audio_list[AUDIO_ARRAY_SIZE];
};

struct merge_edid_data edid_data;

void merge_video_data(uint64_t vic)
{
	int i;

	HDMIRX_INFO("Merge EDID video data, vic(0x%016llx)", vic);

	edid_data.video_size = 0;
	for (i = 0; i < VIDEO_ARRAY_SIZE; i++) {

		if (vic & BIT(rx_video_support[i]-1)) {
			edid_data.video_list[edid_data.video_size] = rx_video_support[i];
			edid_data.video_size++;
		}
	}

	/* Dump match VICs */
	for (i = 0; i < edid_data.video_size; i++)
		HDMIRX_DEBUG("Index(%d) VIC(%d)", i, edid_data.video_list[i]);

	if (edid_data.video_size == 0) {
		HDMIRX_INFO("Merge EDID video data fail, no one match");
		edid_data.video_size = 2;
		edid_data.video_list[0] = 32;
		edid_data.video_list[1] = 34;
	}
}

int get_audio_index(unsigned char	coding_type)
{
	unsigned int i;

	for (i = 0; i < AUDIO_ARRAY_SIZE; i++) {
		if (coding_type == rx_audio_support[i].coding_type)
			return i;
	}

	return -1;
}

void merge_audio_data(struct Audio_Data *audio_data)
{
	unsigned int i, j;
	unsigned char coding_type;
	unsigned char tx_temp, rx_temp;
	int index;

	HDMIRX_INFO("Merge EDID audio data, ADB_length(%d)", audio_data->ADB_length);

	j = 0;
	for (i = 0; i < audio_data->ADB_length; i++) {
		index = get_audio_index(audio_data->ADB[i].coding_type);
		if (index >= 0) {
			coding_type = audio_data->ADB[i].coding_type;
			edid_data.audio_list[j].coding_type = coding_type;

			tx_temp = audio_data->ADB[i].channel_count;
			rx_temp = rx_audio_support[index].channel_count;
			edid_data.audio_list[j].channel_count = min(tx_temp, rx_temp);

			tx_temp = audio_data->ADB[i].sample_freq_all;
			rx_temp = rx_audio_support[index].sample_freq_all;
			edid_data.audio_list[j].sample_freq_all = tx_temp & rx_temp;

			if (coding_type == 0x1) {
				tx_temp = audio_data->ADB[i].sample_size_all;
				rx_temp = rx_audio_support[index].sample_size_all;
				edid_data.audio_list[j].sample_size_all = tx_temp & rx_temp;
			} else if ((coding_type >= 2) && (coding_type <= 8)) {
				tx_temp = audio_data->ADB[i].max_bit_rate_divided_by_8KHz;
				rx_temp = rx_audio_support[index].max_bit_rate_divided_by_8KHz;
				edid_data.audio_list[j].max_bit_rate_divided_by_8KHz = min(tx_temp, rx_temp);
			}

			j++;
		}
	}
	edid_data.audio_size = j;

	HDMIRX_INFO("Merge_EDID, number of match audio format(%u)", edid_data.audio_size);
	/* Dump match audio */
	for (i = 0; i < edid_data.audio_size; i++) {
		HDMIRX_DEBUG("coding_type(%u)", edid_data.audio_list[i].coding_type);
		HDMIRX_DEBUG("channel_count(%u)", edid_data.audio_list[i].channel_count);
		HDMIRX_DEBUG("sample_freq_all(0x%x)", edid_data.audio_list[i].sample_freq_all);
		HDMIRX_DEBUG("sample_size_all(0x%x)", edid_data.audio_list[i].sample_size_all);
		HDMIRX_DEBUG("max_bit_rate_divided_by_8KHz(0x%x)", edid_data.audio_list[i].max_bit_rate_divided_by_8KHz);
	}

	if (edid_data.audio_size == 0) {
		HDMIRX_INFO("Merge EDID audio data fail, no one match");
		edid_data.audio_size = 1;
		edid_data.audio_list[0].coding_type = 0x1;
		edid_data.audio_list[0].channel_count = 0x2;
		edid_data.audio_list[0].sample_freq_all = 0x6;
		edid_data.audio_list[0].sample_size_all = 0x0;
	}
}


/**
 * gernerate_EDID - Generate specific EDID
 * @data: Input EDID info
 * @edid_buf: Output EDID buffer, 256bytes
 *  Retn : N/A
 */
void gernerate_EDID(struct merge_edid_data *data, unsigned char *edid_buf)
{
	unsigned int i;
	unsigned int index = 0;
	unsigned int data_block_size;
	unsigned int sum = 0;

	memset(edid_buf, 0, 256);

	/* Base block 128Bytes */
	memcpy(&edid_buf[index], base_block, sizeof(base_block));
	index += sizeof(base_block);

	/* Skip CEA Header */
	index += 4;
	data_block_size = 4;

	/* Speaker Allocation	*/
	memcpy(&edid_buf[index], speaker_alloc, speaker_alloc_size);
	index += speaker_alloc_size;
	data_block_size += speaker_alloc_size;

	/* Vendor Specific 1.4b */
	memcpy(&edid_buf[index], vendor_specific, vendor_specific_size);
	index += vendor_specific_size;
	data_block_size += vendor_specific_size;

	/* Video Data */
	edid_buf[index] = (0x2<<5) | (data->video_size);
	index++;
	data_block_size++;
	for (i = 0; i < data->video_size; i++)
		edid_buf[index++] = data->video_list[i];

	data_block_size += data->video_size;

	/* Audio Data */
	edid_buf[index] = (0x1<<5) | (data->audio_size*3);
	index++;
	data_block_size++;
	for (i = 0; i < data->audio_size; i++) {
		edid_buf[index++] = ((data->audio_list[i].coding_type & 0xF) << 3) |
							((data->audio_list[i].channel_count - 1) & 0x7);
		edid_buf[index++] = data->audio_list[i].sample_freq_all;

		if (data->audio_list[i].coding_type == 1) {
			edid_buf[index++] = data->audio_list[i].sample_size_all;
		} else if ((data->audio_list[i].coding_type >= 2) &&
					(data->audio_list[i].coding_type <= 8)) {
			edid_buf[index++] = data->audio_list[i].max_bit_rate_divided_by_8KHz;
		} else {
			edid_buf[index++] = 0;
		}
	}
	data_block_size += data->audio_size*3;

	/* Colorimetry */
	memcpy(&edid_buf[index], colorimetry, colorimetry_size);
	index += colorimetry_size;
	data_block_size += colorimetry_size;

	/* CEA Header */
	edid_buf[0x80] = 0x02;
	edid_buf[0x81] = 0x03;
	edid_buf[0x82] = data_block_size;
	edid_buf[0x83] = BIT(6);/* Audio */
	if (data->color_formats & DRM_COLOR_FORMAT_YCRCB444)
		edid_buf[0x83] |= BIT(5);
	if (data->color_formats & DRM_COLOR_FORMAT_YCRCB422)
		edid_buf[0x83] |= BIT(4);

	/* Calculate and set checksum */
	for (i = 0x80; i < 0xFF; i++)
		sum += edid_buf[i];
	edid_buf[0xFF] = (0x100-(sum&0xFF))&0xFF;

}

void hdmirx_merge_EDID(struct sink_capabilities_t *sink_cap)
{
	int i;
	unsigned char edid_buf[256];

	memset(&edid_data, 0, sizeof(edid_data));

	edid_data.color_formats = sink_cap->display_info.color_formats;

	merge_video_data(sink_cap->vic);

	merge_audio_data(&sink_cap->audio_data);

	gernerate_EDID(&edid_data, edid_buf);

	HdmiRx_ChangeCurrentEDID(edid_buf);

	for (i = 0; i < 16; i++) {
		HDMIRX_DEBUG("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
			edid_buf[i*16], edid_buf[i*16+1], edid_buf[i*16+2], edid_buf[i*16+3],
			edid_buf[i*16+4], edid_buf[i*16+5], edid_buf[i*16+6], edid_buf[i*16+7],
			edid_buf[i*16+8], edid_buf[i*16+9], edid_buf[i*16+10], edid_buf[i*16+11],
			edid_buf[i*16+12], edid_buf[i*16+13], edid_buf[i*16+14], edid_buf[i*16+15]);
	}
}


