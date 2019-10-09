/*
 *  dptx_hwapi.h - RTK display port driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DPTX_HWAPI_H__
#define __DPTX_HWAPI_H__

#include <linux/fs.h>
#include <linux/io.h>
#include "dptx_reg.h"

enum
{
	DP_FORMAT_720P_60 = 0,
	DP_FORMAT_1024_768,
	DP_FORMAT_1080P_60,
	DP_FORMAT_2160P_30,
	DP_FORMAT_2160P_60,
};

enum
{
	_DP_ONE_LANE = 1,
	_DP_TWO_LANE = 2,
	_DP_FOUR_LANE = 4,
};

enum
{
	_DP_TX_LEVEL_0 = 0x00,
	_DP_TX_LEVEL_1,
	_DP_TX_LEVEL_2,
	_DP_TX_LEVEL_3,
};

enum
{
	_DP_TX_LANE_0 = 0x00,
	_DP_TX_LANE_1,
	_DP_TX_LANE_2,
	_DP_TX_LANE_3,
};

enum
{
	_DP_TP_NONE = 0x00,
	_DP_TP_1,
	_DP_TP_2,
	_DP_TP_3,
};

enum
{
	_DP_TX_TP1 = 0x00,
	_DP_TX_TP2,
	_DP_TX_TP_END,
};

enum
{
	_DP_TX_TRAINING_NO_RESULT = 0x00,
	_DP_TX_TP1_FAIL,
	_DP_TX_TP2_FAIL,
	_DP_TX_TP1_ADJUST_FAIL,
	_DP_TX_TP2_ADJUST_FAIL,
	_DP_TX_TP1_PASS,
	_DP_TX_TP2_PASS,
	_DP_TX_TRAINING_PASS,
	_DP_TX_TRAINING_FAIL,
};

enum
{
	_DP_LANE0_MAX_POST_CURSOR2_REACHED = _BIT2,
	_DP_LANE1_MAX_POST_CURSOR2_REACHED = _BIT6,
	_DP_LANE2_MAX_POST_CURSOR2_REACHED = _BIT2,
	_DP_LANE3_MAX_POST_CURSOR2_REACHED = _BIT6,
	_DP_SCRAMBLING_DISABLE = _BIT5,
};

enum
{
    _SEC_PACKET_TYPE_AUDIO_TIMESTAMP = 0x01,
    _SEC_PACKET_TYPE_AUDIO_STREAM = 0x02,
    _SEC_PACKET_TYPE_VSC = 0x07,
    _SEC_PACKET_TYPE_INFOFRAME_AVI = 0x0A,
    _SEC_PACKET_TYPE_INFOFRAME_AUDIO = 0x0C,
    _SEC_PACKET_TYPE_INFOFRAME_MPEG = 0x0D,
    _SEC_PACKET_TYPE_INFOFRAME_RSV = 0x0F,
};

struct DPTxDownStreamInfo
{
	unsigned char DPCDRev;
	unsigned char PeerDeviceType : 3;
	unsigned char LinkRate;
	unsigned char LaneNum : 3;
	unsigned char MSGCapStatus : 1;
	unsigned char DPPlugStatus : 1;
	unsigned char DPPlugChange : 1;
	unsigned char LegacyPlugStatus : 1;
	unsigned char EnhanceFraming : 1;
	unsigned char AlternateSrCapable : 1;
	unsigned char FramingChangeCapable : 1;
	unsigned char SSCSupport : 1;
	unsigned char TP3Support : 1;
	unsigned char NumberOfSDP : 1;
	unsigned char NumberOfSDPSink : 1;
	unsigned char MaxLinkRate;
	unsigned char DownStreamInfoReady : 1;
	unsigned char UpRequestCap : 1;
};

struct DPTxInputInfo
{
	unsigned char ColorDepth : 3;
	unsigned char ColorSpace : 3;
	unsigned char AudioReadyToPlay : 1;
	unsigned char AudioFrequency;
	unsigned char AudioChannelCount : 3;
	unsigned short InputPixelClk;
	unsigned char InterlaceMode : 1;
	unsigned char InterlaceVTotalNumber : 1;
	unsigned short HorizontalDataEnablePeriod;
};

struct DPTxLTInfo
{
	unsigned char LTState : 2;
	unsigned char LTResult : 4;
	unsigned char TP1LaneSameVolCnt[4];
	unsigned char TP1Cnt : 3;
	unsigned char TP2Cnt : 3;
	unsigned char LinkPBNPerTimeSlot;
	unsigned char LaneAdj[4];
	unsigned char Lane01LTStatus;
	unsigned char Lane23LTStatus;
	unsigned char LaneAlignStatus;
	unsigned char AdjReqLane01;
	unsigned char AdjReqLane23;
};

struct rtk_dptx_hwinfo {
	void __iomem *reg_base;
	void __iomem *pll_base;
	void __iomem *lvds_base;
	void __iomem *vo_base;
	
	struct DPTxDownStreamInfo DownStreamInfo;
	struct DPTxInputInfo InputInfo;
	struct DPTxLTInfo LTInfo;
	
	int out_type;
	int aux_status;
	struct semaphore sem;
};

void dptx_pixelpll_setting(struct rtk_dptx_hwinfo *hwinfo);
void dptx_dppll_setting(struct rtk_dptx_hwinfo *hwinfo);
void dptx_irq_handle(struct rtk_dptx_hwinfo *hwinfo);
void dptx_initial(struct rtk_dptx_hwinfo *hwinfo);

void dptx_close_phy(struct rtk_dptx_hwinfo *hwinfo);
void dptx_close_pll(struct rtk_dptx_hwinfo *hwinfo);

int dptx_read_edid(struct rtk_dptx_hwinfo *hwinfo,
		unsigned char *ptr, int length);
bool dptx_config_tv_system(struct rtk_dptx_hwinfo *hwinfo);
#endif  //__DPTX_HWAPI_H__
