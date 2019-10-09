/*
 *  dptx_core.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DPTX_CORE_H__
#define __DPTX_CORE_H__

#include <linux/miscdevice.h>
#include <linux/switch.h>
#include <linux/semaphore.h>

#include "dptx_hwapi.h"
#include "dptx_edid.h"
#include "dptx_rpc.h"

#define TX_SUPPORT_MAX 25
//#define TESTING

#define DPTX_DEBUG(format, ...)
#define DPTX_ERR(format, ...) printk(KERN_ERR "[DPTX_ERR] " format, ## __VA_ARGS__)

enum {
	DPTX_GET_SINK_CAPABILITY,
	DPTX_GET_RAW_EDID,
	DPTX_GET_LINK_STATUS,
	DPTX_GET_VIDEO_CONFIG,
	DPTX_SEND_AVMUTE,
	DPTX_CONFIG_TV_SYSTEM,
	DPTX_CONFIG_AVI_INFO,
	DPTX_SET_FREQUNCY,
	DPTX_SEND_AUDIO_MUTE,
	DPTX_SEND_AUDIO_VSDB_DATA,
	DPTX_SEND_AUDIO_EDID2,
	DPTX_CHECK_TMDS_SRC,
	// new added ioctl from kernel 4.9
	DPTX_GET_EDID_SUPPORT_LIST,
	DPTX_GET_OUTPUT_FORMAT,
	DPTX_SET_OUTPUT_FORMAT,
};

enum DPTX_VIDEO_ID_CODE {
	VIC_720X480P60 = 2,
	VIC_1280X720P60 = 4,
	VIC_1920X1080I60 = 5,
	VIC_720X480I60 = 6,
	VIC_1920X1080P60 = 16,
	VIC_720X576P50 = 17,
	VIC_1280X720P50 = 19,
	VIC_1920X1080I50 = 20,
	VIC_720X576I50 = 21,
	VIC_1920X1080P50 = 31,
	VIC_1920X1080P24 = 32,
	VIC_1920X1080P25 = 33,
	VIC_1920X1080P30 = 34,
	VIC_3840X2160P24 = 93,
	VIC_3840X2160P25 = 94,
	VIC_3840X2160P30 = 95,
	VIC_3840X2160P50 = 96,
	VIC_3840X2160P60 = 97,
	VIC_4096X2160P24 = 98,
	VIC_4096X2160P25 = 99,
	VIC_4096X2160P30 = 100,
	VIC_4096X2160P50 = 101,
	VIC_4096X2160P60 = 102,
};

struct dptx_format_setting {
	unsigned char mode;
	unsigned char vic;
	unsigned char display_mode; // same source, different source..
	unsigned char reserved1;
};

struct dptx_format_support {
	unsigned char vic;
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
};

struct dptx_support_list {
	struct dptx_format_support tx_support[TX_SUPPORT_MAX];
	unsigned int tx_support_size;
};

struct rtk_dptx_switch {
	struct switch_dev sw;
	struct delayed_work work;

	int hpd_irq;
	int hpd_gpio;
	unsigned int state;
};

struct rtk_dptx_device {
	struct device *dev;
	struct miscdevice miscdev;
	struct rtk_dptx_switch swdev;
	struct rtk_dptx_hwinfo hwinfo;
	struct dptx_format_setting format;
	struct dptx_support_list list;
	struct ion_client *rpc_ion_client;

	struct clk *tve_clk;
	struct reset_control *lvds_rst;
	asoc_dptx_t cap;
	
	unsigned int ignore_edid;
	unsigned int dptx_irq;
};

int register_dptx_switch(struct rtk_dptx_device *dptx_dev);
#endif  //__DPTX_CORE_H__
