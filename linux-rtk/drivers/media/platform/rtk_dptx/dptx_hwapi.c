/*
 *  dptx_hwapi.c - RTK display port driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>

#include "dptx_hwapi.h"

#define RTK_VO_SET 0
#define AUDIO_ON 1 

unsigned char tDPTX_DRV_TABLE[48] =
{
// Pre-emphasis->    0                    1                    2                    3
// VoltageSwing
/* 0 */      0x00, 0x00, 0x03,    0x00, 0x07, 0x05,    0x00, 0x0C, 0x05,    0x01, 0x09, 0x06,
/* 1 */      0x00, 0x00, 0x05,    0x00, 0x07, 0x05,    0x00, 0x0C, 0x05,    0x00, 0x0C, 0x05,
/* 2 */      0x00, 0x00, 0x09,    0x00, 0x0C, 0x09,    0x00, 0x0C, 0x09,    0x00, 0x0C, 0x09,
/* 3 */      0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,
};

#define GET_BIT0(x) (x & 0x1)
#define GET_BIT1(x) ((x & (0x1<<1))>>1)
#define GET_BIT2(x) ((x & (0x1<<2))>>2)
#define GET_BIT3(x) ((x & (0x1<<3))>>3)
#define GET_BIT4(x) ((x & (0x1<<4))>>4)
#define GET_BIT5(x) ((x & (0x1<<5))>>5)
#define GET_BIT6(x) ((x & (0x1<<6))>>6)
#define GET_BIT7(x) ((x & (0x1<<7))>>7)

#define GET_LANE_VOL_SWING(x,y) (x->LTInfo.LaneAdj[y] & 0x03)
#define SET_LANE_VOL_SWING(x,y,z) (x->LTInfo.LaneAdj[y] = ((x->LTInfo.LaneAdj[y] & 0xFC) | (z)))
#define SET_LANE_VOL_SWING_MAX(x,y) (x->LTInfo.LaneAdj[y] |= _BIT2)
#define CLR_LANE_VOL_SWING_MAX(x,y) (x->LTInfo.LaneAdj[y] &= ~_BIT2)

#define GET_LANE_PRE_EMPHASIS(x,y) ((x->LTInfo.LaneAdj[y] & (_BIT4 | _BIT3)) >> 3)
#define SET_LANE_PRE_EMPHASIS(x,y,z) (x->LTInfo.LaneAdj[y] = ((x->LTInfo.LaneAdj[y] & ~(_BIT4 | _BIT3)) | ((z) << 3)))
#define SET_LANE_PRE_EMPHASIS_MAX(x,y) (x->LTInfo.LaneAdj[y] |= _BIT5)
#define CLR_LANE_PRE_EMPHASIS_MAX(x,y) (x->LTInfo.LaneAdj[y] &= ~_BIT5)

#define GET_LANE0_CR_DONE(x) ((x->LTInfo.Lane01LTStatus & _BIT0) == _BIT0)
#define GET_LANE1_CR_DONE(x) ((x->LTInfo.Lane01LTStatus & _BIT4) == _BIT4)
#define GET_LANE2_CR_DONE(x) ((x->LTInfo.Lane23LTStatus & _BIT0) == _BIT0)
#define GET_LANE3_CR_DONE(x) ((x->LTInfo.Lane23LTStatus & _BIT4) == _BIT4)

#define GET_LANE0_EQ_DONE(x) ((x->LTInfo.Lane01LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_LANE1_EQ_DONE(x) ((x->LTInfo.Lane01LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))
#define GET_LANE2_EQ_DONE(x) ((x->LTInfo.Lane23LTStatus & (_BIT1 | _BIT2)) == (_BIT1 | _BIT2))
#define GET_LANE3_EQ_DONE(x) ((x->LTInfo.Lane23LTStatus & (_BIT5 | _BIT6)) == (_BIT5 | _BIT6))

#define GET_LANE0_ADJ_VOL_SWING(x) (x->LTInfo.AdjReqLane01 & (_BIT1 | _BIT0))
#define SET_LANE0_ADJ_VOL_SWING(x,y) (x->LTInfo.AdjReqLane01 = ((x->LTInfo.AdjReqLane01 & ~(_BIT1 | _BIT0)) | (y)))

#define GET_LANE1_ADJ_VOL_SWING(x) ((x->LTInfo.AdjReqLane01 & (_BIT5 | _BIT4)) >> 4)
#define SET_LANE1_ADJ_VOL_SWING(x,y) (x->LTInfo.AdjReqLane01 = ((x->LTInfo.AdjReqLane01 & ~(_BIT5 | _BIT4)) | ((y) << 4)))

#define GET_LANE2_ADJ_VOL_SWING(x) (x->LTInfo.AdjReqLane23 & (_BIT1 | _BIT0))
#define SET_LANE2_ADJ_VOL_SWING(x,y) (x->LTInfo.AdjReqLane23 = ((x->LTInfo.AdjReqLane23 & ~(_BIT1 | _BIT0)) | (y)))

#define GET_LANE3_ADJ_VOL_SWING(x) ((x->LTInfo.AdjReqLane23 & (_BIT5 | _BIT4)) >> 4)
#define SET_LANE3_ADJ_VOL_SWING(x,y) (x->LTInfo.AdjReqLane23 = ((x->LTInfo.AdjReqLane23 & ~(_BIT5 | _BIT4)) | ((y) << 4)))

#define GET_LANE0_ADJ_PRE_EMPHASIS(x) ((x->LTInfo.AdjReqLane01 & (_BIT3 | _BIT2)) >> 2)
#define SET_LANE0_ADJ_PRE_EMPHASIS(x,y) (x->LTInfo.AdjReqLane01 = ((x->LTInfo.AdjReqLane01 & ~(_BIT3 | _BIT2)) | ((y) << 2)))

#define GET_LANE1_ADJ_PRE_EMPHASIS(x) ((x->LTInfo.AdjReqLane01 & (_BIT7 | _BIT6)) >> 6)
#define SET_LANE1_ADJ_PRE_EMPHASIS(x,y) (x->LTInfo.AdjReqLane01 = ((x->LTInfo.AdjReqLane01 & ~(_BIT7 | _BIT6)) | ((y) << 6)))

#define GET_LANE2_ADJ_PRE_EMPHASIS(x) ((x->LTInfo.AdjReqLane23 & (_BIT3 | _BIT2)) >> 2)
#define SET_LANE2_ADJ_PRE_EMPHASIS(x,y) (x->LTInfo.AdjReqLane23 = ((x->LTInfo.AdjReqLane23 & ~(_BIT3 | _BIT2)) | ((y) << 2)))

#define GET_LANE3_ADJ_PRE_EMPHASIS(x) ((x->LTInfo.AdjReqLane23 & (_BIT7 | _BIT6)) >> 6)
#define SET_LANE3_ADJ_PRE_EMPHASIS(x,y) (x->LTInfo.AdjReqLane23 = ((x->LTInfo.AdjReqLane23 & ~(_BIT7 | _BIT6)) | ((y) << 6)))

static int GetBit(void __iomem *base, unsigned int offset, unsigned int mask)
{
	unsigned int reg;

	reg = readl(base + offset);
	reg &= mask;

	return reg;
}

static unsigned int GetReg(void __iomem *base, unsigned int offset)
{
	return readl(base + offset);
}

static void SetBit(void __iomem *base, unsigned int offset,
		unsigned int mask, unsigned int value)
{
	unsigned int reg;

	reg = readl(base + offset);
	reg &= mask;
	reg |= value;
	writel(reg, base + offset);
}

static void SetBitTD(void __iomem *base, unsigned int offset,
		unsigned int mask, unsigned int value)
{
	unsigned int reg;

	reg = readl(base + offset);
	reg &= mask;
	reg |= value;
	writel(reg, base + offset);
	mdelay(1);
}

void SetReg(void __iomem *base, unsigned int offset, unsigned int value)
{
	writel(value, base + offset);
}

void SetRegTD(void __iomem *base, unsigned int offset, unsigned int value)
{
	writel(value, base + offset);
	mdelay(1);
}

static void dptx_aux_reset(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;

	SetReg(base, PBB_A1_DP_RESET_CTRL, 0x20);
	SetReg(base, PBB_A1_DP_RESET_CTRL, 0x0);
}

static bool dptx_aux_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucWriteArray)
{
	void __iomem *base = hwinfo->reg_base;
	int i;
	unsigned char ucAddrH, ucAddrM, ucAddrL;

	ucAddrH = (ucAddr>>16) & 0xFF;
	ucAddrM = (ucAddr>>8) & 0xFF;
	ucAddrL = ucAddr & 0xFF;
	//Clear fifo & interrupt
	SetBit(base, PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
	SetReg(base, PBD_B1_AUX_IRQ_EVENT, 0x3F);
	//Command request
	SetReg(base, PBD_A4_AUXTX_REQ_CMD, ucAddrH);
	SetReg(base, PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
	SetReg(base, PBD_A6_AUXTX_REQ_ADDR_L, ucAddrL);
	SetReg(base, PBD_A7_AUXTX_REQ_LEN, ((ucLength > 0) ? (ucLength - 1) : 0));

	for(i = 0; i < ucLength; i++)
		SetReg(base, PBD_A8_AUXTX_REQ_DATA, pucWriteArray[i]);
	//Start transfer
	SetBit(base, PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);
	
	if(down_timeout(&hwinfo->sem, 100))
		goto write_fail;

	if(hwinfo->aux_status)
		return true;
write_fail:
	pr_err("%s fail\n", __func__);
	return false;
}

static bool dptx_aux_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucReadArray)
{
	void __iomem *base = hwinfo->reg_base;
	int i;

	unsigned char ucAddrH, ucAddrM, ucAddrL;

	ucAddrH = (ucAddr>>16) & 0xFF;
	ucAddrM = (ucAddr>>8) & 0xFF;
	ucAddrL = ucAddr & 0xFF;
	
	SetReg(base, PBD_B1_AUX_IRQ_EVENT, 0x3F);
	SetBit(base, PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
	SetReg(base, PBD_A4_AUXTX_REQ_CMD, ucAddrH);
	SetReg(base, PBD_A5_AUXTX_REQ_ADDR_M, ucAddrM);
	SetReg(base, PBD_A6_AUXTX_REQ_ADDR_L, ucAddrL);
	
	SetReg(base, PBD_A7_AUXTX_REQ_LEN, ((ucLength > 0) ? (ucLength - 1) : 0));
	SetBit(base, PBD_A3_AUXTX_TRAN_CTRL, ~_BIT0, _BIT0);

	if(down_timeout(&hwinfo->sem, 100))
		goto read_fail;

	if(hwinfo->aux_status) {
		for(i=0; i<ucLength; i++) {
			*pucReadArray = GetReg(base, PBD_AA_AUX_REPLY_DATA);
			pucReadArray++;
		}
		return true;
	}
read_fail:
	pr_err("%s fail\n", __func__);
	return false;
}

static bool dptx_aux_native_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucWriteArray)
{
	ucAddr = ucAddr | (0x80 << 16);
	return dptx_aux_write(hwinfo, ucAddr, ucLength, pucWriteArray);
}

static bool dptx_aux_native_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucReadArray)
{
	ucAddr = ucAddr | (0x90 << 16);	
	return dptx_aux_read(hwinfo, ucAddr, ucLength, pucReadArray);
}

static bool dptx_aux_i2c_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char ucSlaveAddress,
			unsigned char ucLength,
			unsigned char *pucReadArray,
			unsigned char bMOT)
{
	unsigned int ucAddr;

	ucAddr = ((0x00 | bMOT<<6) << 16) | 0x00 << 8 | ucSlaveAddress;

	if(!dptx_aux_write(hwinfo, ucAddr, ucLength, pucReadArray)) {
		if(!dptx_aux_write(hwinfo, ucAddr, ucLength, pucReadArray)) {
			return false;
		}
	}
	return true;
}

static bool dptx_aux_i2c_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char ucSlaveAddress,
			unsigned char ucLength,
			unsigned char *pucReadArray,
			unsigned char bMOT)
{
	unsigned int ucAddr;

	ucAddr = ((0x10 | bMOT<<6) << 16) | 0x00 << 8 | ucSlaveAddress;

	if(!dptx_aux_read(hwinfo, ucAddr, ucLength, pucReadArray)) {
		if(!dptx_aux_read(hwinfo, ucAddr, ucLength, pucReadArray)) {
			return false;
		}
	}
	return true;
}

int dptx_read_edid(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char *ptr, int length)
{
	int i, ret;

	for(i=0; i<length; i++)
		*(ptr+i) = 0;
	
	ret = dptx_aux_i2c_write(hwinfo, 0x50, 1, ptr, 0);
	if(ret==false)
		return -1;
	dptx_aux_i2c_write(hwinfo, 0x50, 1, ptr, 1);
	for(i=0; i<length/16; i++)
		dptx_aux_i2c_read(hwinfo, 0x50, 16, (ptr+i*16), 1);
	return 0;
}

void dptx_phy_set_signal_lv(struct rtk_dptx_hwinfo *hwinfo,
				unsigned char enumLaneX,
				unsigned char ucVoltageSwing,
				unsigned char ucPreEmphasis)
{
	void __iomem *lvds_base = hwinfo->lvds_base;
	unsigned int val;
	unsigned char *tbl, idx;
	
	tbl = tDPTX_DRV_TABLE;

	if(ucVoltageSwing + ucPreEmphasis > 3) {
		if(ucVoltageSwing < 4)
			ucPreEmphasis = 3 - ucVoltageSwing;
		else {
			ucVoltageSwing = 3;
			ucPreEmphasis = 0;
		}
	}
	idx = (ucVoltageSwing * 4 + ucPreEmphasis) * 3;
	val = readl(lvds_base+0x44);
	val = val & ~(0x100000 | 0xF<<(enumLaneX*4));
	val = val | tbl[idx]<<16 | tbl[idx+1]<<(enumLaneX*4) | 0x00f00000;
	writel(val, lvds_base+0x44);
	
	val = readl(lvds_base+0x48);
	val = val & ~(0xF<<(enumLaneX*4)) & ~0xFF000000;
	val = val | tbl[idx+2]<<(enumLaneX*4) | 0x1F000000;
	writel(val, lvds_base+0x48);

	return;
}

void dptx_mlphy_set(struct rtk_dptx_hwinfo *hwinfo)
{
	int i;
	unsigned char swing, emphasis;

	for (i=0; i<hwinfo->DownStreamInfo.LaneNum; i++) {
		swing = GET_LANE_VOL_SWING(hwinfo, i);
		emphasis = GET_LANE_PRE_EMPHASIS(hwinfo, i);
		dptx_phy_set_signal_lv(hwinfo, i, swing, emphasis);
	}
}

void dptx_signal_reset(struct rtk_dptx_hwinfo *hwinfo)
{
	int i;

	for (i=0; i<4; i++) {
		hwinfo->LTInfo.TP1LaneSameVolCnt[i] = 0;

		SET_LANE_VOL_SWING(hwinfo, i, _DP_TX_LEVEL_0);
		CLR_LANE_VOL_SWING_MAX(hwinfo, i);
		SET_LANE_PRE_EMPHASIS(hwinfo, i, _DP_TX_LEVEL_0);
		CLR_LANE_PRE_EMPHASIS_MAX(hwinfo, i);
	}
	dptx_mlphy_set(hwinfo);
}

void dptx_signal_init_set(struct rtk_dptx_hwinfo *hwinfo)
{
	dptx_signal_reset(hwinfo);

/*	switch(GET_DP_TX_DOWNSTREAM_LANE_NUM(hwinfo))
	{
		case _DP_ONE_LANE:

			break;
	}*/
}

void dptx_tp_init_set(struct rtk_dptx_hwinfo *hwinfo)
{
	unsigned char link_rate, link_count;

	hwinfo->LTInfo.LTResult = _DP_TX_TRAINING_NO_RESULT;
	hwinfo->LTInfo.LTState = _DP_TX_TP1;

	link_rate = hwinfo->DownStreamInfo.MaxLinkRate;
	hwinfo->DownStreamInfo.LinkRate = link_rate;

	dptx_signal_init_set(hwinfo);

	//Set Link Rate
	dptx_aux_native_write(hwinfo, 0x100, 1, &link_rate);

	link_count = hwinfo->DownStreamInfo.EnhanceFraming << 7 |
			hwinfo->DownStreamInfo.LaneNum;

	dptx_aux_native_write(hwinfo, 0x101, 1, &link_count);
}

static bool dptx_link_config(struct rtk_dptx_hwinfo *hwinfo)
{
	unsigned char data[16];

	memset(data, 0, sizeof(data));
	data[0] = 0x4C;
	data[1] = 0xE0;
	data[2] = 0x00;

	if (dptx_aux_native_write(hwinfo, 0x300, 3, data) == false)
		return false;
	if (dptx_aux_native_read(hwinfo, 0x0, 16, data)==false)
		return false;
	
	// Step1 : Get DownStream infromation
	if((data[0] != 0x10) && (data[0] != 0x11) && (data[0] != 0x12))
		data[0] = 0x11;

	hwinfo->DownStreamInfo.DPCDRev = data[0];

	if ((data[1] == 0x06) || (data[1] == 0x0A) ||
		((data[0] == 0x12) && (data[1] == 0x14))) {
		if (data[1] > 0xA)
			data[1] = 0xA;
		hwinfo->DownStreamInfo.MaxLinkRate = data[1];
	} else {
		hwinfo->DownStreamInfo.MaxLinkRate = 0x6;
	}
	
	if(hwinfo->out_type == DP_FORMAT_1080P_60)
		hwinfo->DownStreamInfo.LaneNum = _DP_TWO_LANE;
	else if(hwinfo->out_type == DP_FORMAT_2160P_30 ||
			hwinfo->out_type == DP_FORMAT_2160P_60)
		hwinfo->DownStreamInfo.LaneNum = _DP_FOUR_LANE;
	else if(hwinfo->out_type == DP_FORMAT_720P_60 ||
			hwinfo->out_type == DP_FORMAT_1024_768)
		hwinfo->DownStreamInfo.LaneNum = _DP_ONE_LANE;

	hwinfo->DownStreamInfo.EnhanceFraming = (data[2] & _BIT7) >> 7;

	return true;
}

void dptx_tp2_lane_adjust(struct rtk_dptx_hwinfo *hwinfo, int lane)
{
	unsigned char swing, emphasis;
	unsigned char adj_swing, adj_emphasis;

	if (lane == _DP_TX_LANE_0) {
		adj_swing = GET_LANE0_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE0_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_1) {
		adj_swing = GET_LANE1_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE1_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_2) {
		adj_swing = GET_LANE2_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE2_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_3) {
		adj_swing = GET_LANE3_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE3_ADJ_PRE_EMPHASIS(hwinfo);
	} else {
		return;
	}
	swing = GET_LANE_VOL_SWING(hwinfo, lane);
	emphasis = GET_LANE_PRE_EMPHASIS(hwinfo, lane);

	if ((swing + adj_emphasis) > _DP_TX_LEVEL_3) {
		adj_emphasis = _DP_TX_LEVEL_3 - swing;
		if (lane == _DP_TX_LANE_0)
			SET_LANE0_ADJ_PRE_EMPHASIS(hwinfo, adj_emphasis);
		if (lane == _DP_TX_LANE_1)
			SET_LANE1_ADJ_PRE_EMPHASIS(hwinfo, adj_emphasis);
		if (lane == _DP_TX_LANE_2)
			SET_LANE2_ADJ_PRE_EMPHASIS(hwinfo, adj_emphasis);
		if (lane == _DP_TX_LANE_3)
			SET_LANE3_ADJ_PRE_EMPHASIS(hwinfo, adj_emphasis);
	}
	SET_LANE_PRE_EMPHASIS(hwinfo, lane, adj_emphasis);
	SET_LANE_VOL_SWING(hwinfo, lane, adj_swing);

	if (adj_swing == _DP_TX_LEVEL_3)
		SET_LANE_VOL_SWING_MAX(hwinfo, lane);
	else
		CLR_LANE_VOL_SWING_MAX(hwinfo, lane);
	if (adj_emphasis == _DP_TX_LEVEL_3)
		SET_LANE_PRE_EMPHASIS_MAX(hwinfo, lane);
	else
		CLR_LANE_PRE_EMPHASIS_MAX(hwinfo, lane);
}

bool dptx_tp1_lane_adjust(struct rtk_dptx_hwinfo *hwinfo, int lane)
{
	unsigned char swing, emphasis;
	unsigned char adj_swing, adj_emphasis;
	int cnt;
	
	if (lane == _DP_TX_LANE_0) {
		adj_swing = GET_LANE0_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE0_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_1) {
		adj_swing = GET_LANE1_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE1_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_2) {
		adj_swing = GET_LANE2_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE2_ADJ_PRE_EMPHASIS(hwinfo);
	} else if (lane == _DP_TX_LANE_3) {
		adj_swing = GET_LANE3_ADJ_VOL_SWING(hwinfo);
		adj_emphasis = GET_LANE3_ADJ_PRE_EMPHASIS(hwinfo);
	} else {
		return false;
	}

	swing = GET_LANE_VOL_SWING(hwinfo, lane);
	emphasis = GET_LANE_PRE_EMPHASIS(hwinfo, lane);

	if ((adj_swing + emphasis) > _DP_TX_LEVEL_3) {
		adj_swing = _DP_TX_LEVEL_3 - emphasis;
		if (lane == _DP_TX_LANE_0)
			SET_LANE0_ADJ_VOL_SWING(hwinfo, adj_swing);
		else if (lane == _DP_TX_LANE_1)
			SET_LANE1_ADJ_VOL_SWING(hwinfo, adj_swing);
		else if (lane == _DP_TX_LANE_2)
			SET_LANE2_ADJ_VOL_SWING(hwinfo, adj_swing);
		else if (lane == _DP_TX_LANE_3)
			SET_LANE3_ADJ_VOL_SWING(hwinfo, adj_swing);
	}
	if (swing == adj_swing) {
		cnt = hwinfo->LTInfo.TP1LaneSameVolCnt[lane]++;
		if(cnt==5 || (cnt==1 && adj_swing == _DP_TX_LEVEL_3)) {
			hwinfo->LTInfo.TP1LaneSameVolCnt[lane] = 0;
			return false;
		}
	} else
		hwinfo->LTInfo.TP1LaneSameVolCnt[lane] = 0;
	
	SET_LANE_VOL_SWING(hwinfo, lane, adj_swing);
	SET_LANE_PRE_EMPHASIS(hwinfo, lane, adj_emphasis);
	if (adj_swing == _DP_TX_LEVEL_3)
		SET_LANE_VOL_SWING_MAX(hwinfo, lane);
	else
		CLR_LANE_VOL_SWING_MAX(hwinfo, lane);
	if (adj_emphasis == _DP_TX_LEVEL_3)
		SET_LANE_PRE_EMPHASIS_MAX(hwinfo, lane);
	else
		CLR_LANE_PRE_EMPHASIS_MAX(hwinfo, lane);

	return true;
}

static unsigned char dptx_train_pattern1(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char data[20];
	int i;

	memset(data, 0, sizeof(data));

	if(hwinfo->LTInfo.LTResult == _DP_TX_TRAINING_NO_RESULT) {
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x10);
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x11);
		data[0] = _DP_TP_1 | _DP_SCRAMBLING_DISABLE;
		for (i=0; i<4; i++)
			data[i+1] = hwinfo->LTInfo.LaneAdj[i];
		dptx_aux_native_write(hwinfo, 0x102, 5, data);
	} else {
		dptx_mlphy_set(hwinfo);
		for (i=0; i<4; i++)
			data[i] = hwinfo->LTInfo.LaneAdj[i];
		dptx_aux_native_write(hwinfo, 0x103, 4, data);
	}

	mdelay(5);

	dptx_aux_native_read(hwinfo, 0x202, 6, data);
	pr_info("DPTX - TP1 : 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n",
			data[0], data[1], data[2], data[4], data[5]);

	hwinfo->LTInfo.Lane01LTStatus = data[0];
	hwinfo->LTInfo.Lane23LTStatus = data[1];
	hwinfo->LTInfo.AdjReqLane01 = data[4];
	hwinfo->LTInfo.AdjReqLane23 = data[5];

	switch(hwinfo->DownStreamInfo.LaneNum) {
	case _DP_FOUR_LANE:
		if((GET_LANE3_CR_DONE(hwinfo) &
			GET_LANE2_CR_DONE(hwinfo)) != true)
			break;
	case _DP_TWO_LANE:
		if((GET_LANE1_CR_DONE(hwinfo)) != true)
			break;
	case _DP_ONE_LANE:
	default:
		if(GET_LANE0_CR_DONE(hwinfo) != true) {
			break;
		} else {
			hwinfo->LTInfo.TP1Cnt = 0;
			return _DP_TX_TP1_PASS;
		}
	}

	if(hwinfo->LTInfo.TP1Cnt >= 5) {
		hwinfo->LTInfo.TP1Cnt = 0;
		return _DP_TX_TP1_ADJUST_FAIL;
	} else
		hwinfo->LTInfo.TP1Cnt++;

	switch(hwinfo->DownStreamInfo.LaneNum) {
	case _DP_FOUR_LANE:
		if(dptx_tp1_lane_adjust(hwinfo, 3) == false)
			return _DP_TX_TP1_ADJUST_FAIL;
		if(dptx_tp1_lane_adjust(hwinfo, 2) == false)
			return _DP_TX_TP1_ADJUST_FAIL;
	case _DP_TWO_LANE:
		if(dptx_tp1_lane_adjust(hwinfo, 1) == false)
			return _DP_TX_TP1_ADJUST_FAIL;
	case _DP_ONE_LANE:
	default:
		if(dptx_tp1_lane_adjust(hwinfo, 0) == false)
			return _DP_TX_TP1_ADJUST_FAIL;
		break;
	}

	return _DP_TX_TP1_FAIL;
}

static unsigned char dptx_train_pattern2(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char data[20];
	int i;

	if(hwinfo->LTInfo.LTResult == _DP_TX_TP1_PASS) {
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x20);
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x21);
		data[0] = _DP_TP_2 | _DP_SCRAMBLING_DISABLE;
		for (i=0; i<4; i++)
			data[i+1] = hwinfo->LTInfo.LaneAdj[i];
		dptx_aux_native_write(hwinfo, 0x102, 5, data);
	} else {
		dptx_mlphy_set(hwinfo);
		for (i=0; i<4; i++)
			data[i] = hwinfo->LTInfo.LaneAdj[i];
		dptx_aux_native_write(hwinfo, 0x103, 4, data);
	}

	mdelay(5);

	dptx_aux_native_read(hwinfo, 0x202, 6, data);
	hwinfo->LTInfo.Lane01LTStatus = data[0];
	hwinfo->LTInfo.Lane23LTStatus = data[1];
	hwinfo->LTInfo.LaneAlignStatus = data[2];
	hwinfo->LTInfo.AdjReqLane01 = data[4];
	hwinfo->LTInfo.AdjReqLane23 = data[5];
	pr_info("DPTX - TP2 : 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n",
			data[0], data[1], data[2], data[4], data[5]);

	switch(hwinfo->DownStreamInfo.LaneNum) {
	case _DP_FOUR_LANE:
		if((GET_LANE3_CR_DONE(hwinfo) &
			GET_LANE2_CR_DONE(hwinfo)) != true) {
			hwinfo->LTInfo.TP2Cnt = 0;
			return _DP_TX_TP2_ADJUST_FAIL;
		}
		if((GET_LANE3_EQ_DONE(hwinfo) &
			GET_LANE2_EQ_DONE(hwinfo)) != true)
			break;
	case _DP_TWO_LANE:
		if((GET_LANE1_CR_DONE(hwinfo)) != true) {
			hwinfo->LTInfo.TP2Cnt = 0;
			return _DP_TX_TP2_ADJUST_FAIL;
		}
		if((GET_LANE1_EQ_DONE(hwinfo)) != true)
			break;
	case _DP_ONE_LANE:
	default:
		if(GET_LANE0_CR_DONE(hwinfo) != true) {
			hwinfo->LTInfo.TP2Cnt = 0;
			return _DP_TX_TP2_ADJUST_FAIL;
		}
		if(GET_LANE0_EQ_DONE(hwinfo) != true) {
			break;
		} else {
			hwinfo->LTInfo.TP2Cnt = 0;
			return _DP_TX_TP2_PASS;
		}
		break;
	}
	if(hwinfo->LTInfo.TP2Cnt >= 5) {
		hwinfo->LTInfo.TP2Cnt = 0;
		return _DP_TX_TP2_ADJUST_FAIL;
	} else
		hwinfo->LTInfo.TP2Cnt++;

	switch(hwinfo->DownStreamInfo.LaneNum) {
		case _DP_FOUR_LANE:
			dptx_tp2_lane_adjust(hwinfo, 3);
			dptx_tp2_lane_adjust(hwinfo, 2);
		case _DP_TWO_LANE:
			dptx_tp2_lane_adjust(hwinfo, 1);
		case _DP_ONE_LANE:
		default:
			dptx_tp2_lane_adjust(hwinfo, 0);
			break;
	}

	return _DP_TX_TP2_FAIL;
}

void dptx_train_pattern_end(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char data[20];

	data[0] = _DP_TP_NONE;
	dptx_aux_native_write(hwinfo, 0x102, 1, data);

	if(hwinfo->LTInfo.LTResult == _DP_TX_TRAINING_PASS) {
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x40);
		SetReg(base, PBB_01_DPTX_ML_PAT_SEL, 0x41);
	}
}

bool dptx_link_training(struct rtk_dptx_hwinfo *hwinfo)
{
	unsigned char data[20];
	unsigned char ret;

	if (dptx_link_config(hwinfo) == false)
		return false;
	
	data[0] = 0x1;
	dptx_aux_native_write(hwinfo, 0x600, 1, data);

	dptx_tp_init_set(hwinfo);

START_TRAIN:
	switch (hwinfo->LTInfo.LTState) {
	case _DP_TX_TP1:
		ret = dptx_train_pattern1(hwinfo);
		hwinfo->LTInfo.LTResult = ret;
		if (ret == _DP_TX_TP1_PASS) {
			pr_info("DPTX - TP1 training success\n");
			hwinfo->LTInfo.LTState = _DP_TX_TP2;
		} else if (ret == _DP_TX_TP1_ADJUST_FAIL) {
			pr_err("DPTX - TP1 training fail\n");
			hwinfo->LTInfo.LTResult =
						_DP_TX_TRAINING_FAIL;
			return false;
		}
		break;
	case _DP_TX_TP2:
		ret = dptx_train_pattern2(hwinfo);
		hwinfo->LTInfo.LTResult = ret;
		if (ret == _DP_TX_TP2_PASS) {
			pr_info("DPTX - TP2 training success\n");
			hwinfo->LTInfo.LTState = _DP_TX_TP_END;
		} else if(ret == _DP_TX_TP2_ADJUST_FAIL) {
			pr_err("DPTX - TP2 training fail\n");
			dptx_train_pattern_end(hwinfo);
			return false;
		}
		break;
	case _DP_TX_TP_END:
		hwinfo->LTInfo.LTResult = _DP_TX_TRAINING_PASS;
		dptx_train_pattern_end(hwinfo);
		break;
	}

	if(hwinfo->LTInfo.LTResult != _DP_TX_TRAINING_PASS &&
		hwinfo->LTInfo.LTResult != _DP_TX_TRAINING_FAIL)
		goto START_TRAIN;

	return true;
}

void dptx_pixelpll_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->pll_base;

	SetBitTD(base, PLL_HDMI, ~_BIT3, _BIT3);
	SetBitTD(base, PLL_HDMI_LDO1, ~_BIT6, 0);

	if (hwinfo->out_type == DP_FORMAT_1024_768) {
		SetRegTD(base, PLL_PIXEL1, 0x934701a2);
		SetRegTD(base, PLL_PIXEL1, 0x934741a2);
		SetRegTD(base, PLL_SSC_DIG_PIXEL1, 0xcf1c);
	} else if (hwinfo->out_type == DP_FORMAT_1080P_60) {
		SetRegTD(base, PLL_PIXEL1, 0x93470192);
		SetRegTD(base, PLL_PIXEL1, 0x93474192);
		SetRegTD(base, PLL_SSC_DIG_PIXEL1, 0xf000);
	} else if (hwinfo->out_type == DP_FORMAT_2160P_60) {
		SetRegTD(base, PLL_PIXEL1, 0x93470182);
		SetRegTD(base, PLL_PIXEL1, 0x93474182);
		SetRegTD(base, PLL_SSC_DIG_PIXEL1, 0x1b815);
	} else if (hwinfo->out_type == DP_FORMAT_2160P_30) {
		SetRegTD(base, PLL_PIXEL1, 0x93470182);
		SetRegTD(base, PLL_PIXEL1, 0x93474182);
		SetRegTD(base, PLL_SSC_DIG_PIXEL1, 0xF000);
	} else {
		SetRegTD(base, PLL_PIXEL1, 0x934701a2);
		SetRegTD(base, PLL_PIXEL1, 0x934741a2);
		SetRegTD(base, PLL_SSC_DIG_PIXEL1, 0xF000);
	}

	SetRegTD(base, PLL_PIXEL2, 0x1e01);
	SetRegTD(base, PLL_SSC_DIG_PIXEL2, 0x501008);
	SetRegTD(base, PLL_SSC_DIG_PIXEL0, 0xd);
}

void dptx_dppll_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *pll_base = hwinfo->pll_base;
	void __iomem *lvds_base = hwinfo->lvds_base;

	/* Disable iso control */
	SetRegTD(pll_base, DISP_PLL_DIV2, 0x440000);
	SetRegTD(lvds_base, AIF_MISC, 0x1003301);
	SetRegTD(pll_base, DISP_PLL_DIV2, 0x420000);

	/* DP PLL setting */
	SetRegTD(pll_base, PLL_EDP1, 0x9A356007);
	SetRegTD(pll_base, PLL_EDP2, 0x3);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP0, 0xc);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP1, 0x30800);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP3, 0x30480);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP4, 0x1100);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP2, 0x501068);
	SetRegTD(pll_base, PLL_SSC_DIG_EDP0, 0xd);
}

static void dptx_aux_physet(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	
	SetBit(base, PBD_61_AUX_1, ~(_BIT7 | _BIT6 | _BIT5), _BIT7);
	SetBit(base, PBD_61_AUX_1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0),
				(_BIT3 | _BIT2 | _BIT1 | _BIT0));
	SetBit(base, PBD_62_AUX_2, ~(_BIT5 | _BIT0), _BIT5 |_BIT0);
	SetBit(base, PBD_66_AUX_6, ~(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0),
				(_BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0));
	SetReg(base, PBD_67_DIG_TX_03, 0xFF);
}

void dptx_initial(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;

//	dptx_aux_physet(hwinfo);

//	SetReg(base, PBD_64_AUX_4, 0xCA);
	// Set ECF by FW mode
	SetBit(base, PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);
	// Set Aux Timeout
//	SetReg(base, PBD_A1_AUX_TIMEOUT, 0x95);
	// Power On Aux CH
	SetBit(base, PBD_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);

//	SetBit(base, PBD_65_AUX_5, ~_BIT7, 0);
	// Sync end Pattern Error Handle Disable
	SetBit(base, PBD_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);
	// Enable Short IRQ and Disable Long IRQ
	SetBit(base, PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6);
	// Set DP TX CLK divider
	SetReg(base, PBB_A3_DPTX_IRQ_CTRL, 0x80);

	SetBit(base, PBB_C9_ARBITER_CTRL, ~_BIT0, _BIT0);

//	SetReg(base, PBB_E0_DPTX_CLK_GEN, 0x21);
	SetBit(base, PBD_B2_AUX_IRQ_EN, 0,
		_BIT0 | _BIT1 | _BIT2 | _BIT3 | _BIT4 | _BIT5 | _BIT6 | _BIT7);

	SetBit(base, PBB_C7_VBID, ~_BIT1, _BIT1);
//	SetReg(base, PBD_AF_AUX_RETRY_1, 0x2);
//	SetBit(base, PBD_B0_AUX_RETRY_2,
//		~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
//		~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7 | _BIT5);
}

void dptx_close_phy(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	void __iomem *lvds_base = hwinfo->lvds_base;

	SetReg(base, PBB_00_DP_PHY_CTRL, 0x1);
	SetReg(lvds_base, AIF_EDP1, 0);
}

void dptx_close_pll(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->pll_base;

	SetRegTD(base, PLL_EDP2, 0);
	SetBitTD(base, PLL_EDP1, ~_BIT31, 0);

	SetRegTD(base, PLL_SSC_DIG_PIXEL0, 0x8);
	SetBitTD(base, PLL_PIXEL2, ~_BIT0, 0);
	SetBitTD(base, PLL_PIXEL1, ~_BIT31, 0);
}

static unsigned char dptx_audio_get_parity(unsigned char ucHeader)
{
	unsigned char ucParity = 0;

	ucParity |= ((unsigned char)(GET_BIT1(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT6(ucHeader))) << 7;
	ucParity |= ((unsigned char)(GET_BIT0(ucHeader) ^ GET_BIT1(ucHeader) ^ GET_BIT3(ucHeader) ^ GET_BIT5(ucHeader))) << 6;
	ucParity |= ((unsigned char)(GET_BIT0(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT4(ucHeader) ^ GET_BIT7(ucHeader))) << 5;
	ucParity |= ((unsigned char)(GET_BIT2(ucHeader) ^ GET_BIT3(ucHeader) ^ GET_BIT7(ucHeader))) << 4;
	ucParity |= ((unsigned char)(GET_BIT1(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT3(ucHeader) ^ GET_BIT6(ucHeader) ^ GET_BIT7(ucHeader))) << 3;
	ucParity |= ((unsigned char)(GET_BIT0(ucHeader) ^ GET_BIT1(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT3(ucHeader) ^ GET_BIT5(ucHeader) ^ GET_BIT6(ucHeader))) << 2;
	ucParity |= ((unsigned char)(GET_BIT0(ucHeader) ^ GET_BIT1(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT4(ucHeader) ^ GET_BIT5(ucHeader) ^ GET_BIT7(ucHeader))) << 1;
	ucParity |= (GET_BIT0(ucHeader) ^ GET_BIT2(ucHeader) ^ GET_BIT3(ucHeader) ^ GET_BIT4(ucHeader) ^ GET_BIT7(ucHeader));

	return ucParity;
}

static void dptx_set_sec_header(struct rtk_dptx_hwinfo *hwinfo,
			int enumPackettype)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char pucData[4];

	memset(pucData, 0, sizeof(pucData));
	pucData[0] = 0x00;
	pucData[1] = enumPackettype;
	SetBit(base, PBC_7B_SEC_PH_PACKET_TYPE, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), pucData[1]);
	switch(enumPackettype)
	{
		case _SEC_PACKET_TYPE_AUDIO_TIMESTAMP:
			pucData[2] = 0x17;
			pucData[3] = 0x44; //(_DP_VERSION_1_1 << 2);
			break;
		case _SEC_PACKET_TYPE_VSC:
			pucData[2] = 0x01;
			pucData[3] = 0x01;
			break;
		case _SEC_PACKET_TYPE_INFOFRAME_AVI:
		case _SEC_PACKET_TYPE_INFOFRAME_AUDIO:
		case _SEC_PACKET_TYPE_INFOFRAME_MPEG:
			pucData[1] = 0x84;
			pucData[2] = 0x1B;
			pucData[3] = 0x44;

			SetReg(base, PBC_26_SEC_INFO_AUD_DB0, 0x11);
			SetReg(base, PBC_27_SEC_INFO_AUD_DB1, 0x0F);
			break;
		case _SEC_PACKET_TYPE_AUDIO_STREAM:
			pucData[2] = 0x00;
			pucData[3] = 0x01;
			break;
		case _SEC_PACKET_TYPE_INFOFRAME_RSV:
			pucData[1] = 0x83;
			pucData[2] = 0x01;
			pucData[3] = 0x08;
			break;
		default:
			break;
	}
	// Set Header Byte
	SetReg(base, PBC_73_SEC_PH_HB0, pucData[0]);
	SetReg(base, PBC_74_SEC_PH_HB1, pucData[1]);
	SetReg(base, PBC_75_SEC_PH_HB2, pucData[2]);
	SetReg(base, PBC_76_SEC_PH_HB3, pucData[3]);
	// Set Parity Byte
	SetReg(base, PBC_77_SEC_PH_PB0, dptx_audio_get_parity(pucData[0]));
	SetReg(base, PBC_78_SEC_PH_PB1, dptx_audio_get_parity(pucData[1]));
	SetReg(base, PBC_79_SEC_PH_PB2, dptx_audio_get_parity(pucData[2]));
	SetReg(base, PBC_7A_SEC_PH_PB3, dptx_audio_get_parity(pucData[3]));
	// Set Double Buffer
	SetBit(base, PBC_02_SEC_DBUF_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

static void dptx_audio_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char pucData[6];

	// Set 2 channel layout and audio source from I2S
	SetBit(base, PBC_18_AUD_FUNCTION_CTRL1, ~(_BIT7 | _BIT6), 0x00);
	pucData[0] = 20;

//	((WORD *)pucData)[0] = 2 + ((8 + pucData[0]) / hwinfo->DownStreamInfo.LaneNum;
//	((WORD *)pucData)[1] = (DWORD)(((WORD *)pucData)[1] - hwinfo->TxInputInfo.HorizontalDataEnablePeriod * 7 / 10;
//	if(((WORD *)pucData)[1] > ((WORD *)pucData)[0])
//		((WORD *)pucData)[2] = ((WORD *)pucData)[1] - ((WORD *)pucData)[0];
//	else
//		((WORD *)pucData)[2] = 0;
	
//	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, pucData[4]);
//	SetReg(base, PBB_D5_ARBITER_SEC_END_CNT_LB, pucData[5]);
	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, 0x00);
	SetReg(base, PBB_D5_ARBITER_SEC_END_CNT_LB, 0x10);

}

void dptx_sst_audioplay_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;

	SetBit(base, PBC_00_SEC_FUNCTION_CTRL, ~_BIT0, 0x00);
	SetReg(base, PBC_47_AUD_FUNCTION_CTRL2, 0x4F);
	SetReg(base, PBC_48_AUD_FUNCTION_CTRL3, 0x04);
	SetReg(base, PBC_19_AUD_PAYLOAD_B3, 0x80);

	dptx_audio_setting(hwinfo);
	// Set Maud	
	SetReg(base, PBC_20_AUD_TS_MAUD_H, 0x0);
	SetReg(base, PBC_21_AUD_TS_MAUD_M, 0x2);
	SetReg(base, PBC_22_AUD_TS_MAUD_L, 0x0);
	// Sed Naud
	SetReg(base, PBC_23_AUD_TS_NAUD_H, 0x0);
	SetReg(base, PBC_24_AUD_TS_NAUD_M, 0x15);
	SetReg(base, PBC_25_AUD_TS_NAUD_L, 0xf9);
	
	// Set Header for Audio Timestamp
	dptx_set_sec_header(hwinfo, _SEC_PACKET_TYPE_AUDIO_TIMESTAMP);
	// Set Header for Audio Info-frame
	dptx_set_sec_header(hwinfo, _SEC_PACKET_TYPE_INFOFRAME_AUDIO);
	// Set Header for Audio Stream
	dptx_set_sec_header(hwinfo, _SEC_PACKET_TYPE_AUDIO_STREAM);

	SetBit(base, PBC_00_SEC_FUNCTION_CTRL, ~(_BIT3 | _BIT1 | _BIT0), (_BIT3 | _BIT1 | _BIT0));
	SetBit(base, PBC_8F_DPTX_I2S_CTRL, ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT1 | _BIT0), (_BIT7 | _BIT1 | _BIT0));

	SetReg(base, PBC_85_CH_STATUS_0, 0x04);
	SetReg(base, PBC_86_CH_STATUS_1, 0x00);
	SetReg(base, PBC_87_CH_STATUS_2, 0x00);
	SetReg(base, PBC_88_CH_STATUS_3, 0x02);
	SetReg(base, PBC_89_CH_STATUS_4, 0x0b);

	SetBit(base, PBB_C7_VBID, ~_BIT2, 0x00);
}

void dptx_sst_displayformat_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	// Disable HW Auto Calculate H Delay
	SetBit(base, PBB_D3_LFIFO_WL_SET, ~_BIT7, 0x00);

	SetBit(base, PBB_A1_DP_RESET_CTRL, ~_BIT7, _BIT7);
	SetBit(base, PBB_A1_DP_RESET_CTRL, ~_BIT7, 0x00);
	switch (hwinfo->out_type) {
	case DP_FORMAT_1024_768:
		SetReg(base, PBB_CD_TU_DATA_SIZE0, 0x2e);
		SetReg(base, PBB_CE_TU_DATA_SIZE1, 0x01);
		SetReg(base, PBB_CA_V_DATA_PER_LINE0, 0xc);
		SetReg(base, PBB_CB_V_DATA_PER_LINE1, 0x00);
		break;
	case DP_FORMAT_720P_60:
		SetReg(base, PBB_CD_TU_DATA_SIZE0, 0x35);
		SetReg(base, PBB_CE_TU_DATA_SIZE1, 0x0);
		SetReg(base, PBB_CA_V_DATA_PER_LINE0, 0xf);
		SetReg(base, PBB_CB_V_DATA_PER_LINE1, 0x00);
		break;	
	case DP_FORMAT_1080P_60:
	case DP_FORMAT_2160P_30:
		SetReg(base, PBB_CD_TU_DATA_SIZE0, 0x35);
		SetReg(base, PBB_CE_TU_DATA_SIZE1, 0x0);
		SetReg(base, PBB_CA_V_DATA_PER_LINE0, 0xb);
		SetReg(base, PBB_CB_V_DATA_PER_LINE1, 0x40);
		break;
	case DP_FORMAT_2160P_60:
		SetReg(base, PBB_CD_TU_DATA_SIZE0, 0x3e);
		SetReg(base, PBB_CE_TU_DATA_SIZE1, 0x0);
		SetReg(base, PBB_CA_V_DATA_PER_LINE0, 0x7);
		SetReg(base, PBB_CB_V_DATA_PER_LINE1, 0x80);
		break;
	default:
		break;
	}
	SetReg(base, PBB_D3_LFIFO_WL_SET, 0xC0);
}

static void dptx_sstmsa_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;

	SetBit(base, PBB_A1_DP_RESET_CTRL, ~_BIT6, _BIT6);
	SetBit(base, PBB_A1_DP_RESET_CTRL, ~_BIT6, 0x00);
	
	switch (hwinfo->out_type) {
	case DP_FORMAT_1024_768:
		SetReg(base, PBB_B7_MN_STRM_ATTR_HTT_M, 0x5);
		SetReg(base, PBB_B8_MN_STRM_ATTR_HTT_L, 0x40);
		SetReg(base, PBB_B9_MN_STRM_ATTR_HST_M, 0x1);
		SetReg(base, PBB_BA_MN_STRM_ATTR_HST_L, 0x29);
		SetReg(base, PBB_BB_MN_STRM_ATTR_HWD_M, 0x4);
		SetReg(base, PBB_BC_MN_STRM_ATTR_HWD_L, 0x00);
		SetReg(base, PBB_BD_MN_STRM_ATTR_HSW_M, 0x80);
		SetReg(base, PBB_BE_MN_STRM_ATTR_HSW_L, 0x88);
		SetReg(base, PBB_BF_MN_STRM_ATTR_VTTE_M, 0x3);
		SetReg(base, PBB_C0_MN_STRM_ATTR_VTTE_L, 0x26);
		SetReg(base, PBB_C2_MN_STRM_ATTR_VST_L, 0x24);
		SetReg(base, PBB_C3_MN_STRM_ATTR_VHT_M, 0x3);
		SetReg(base, PBB_C4_MN_STRM_ATTR_VHT_L, 0x00);
		SetReg(base, PBB_C5_MN_STRM_ATTR_VSW_M, 0x80);
		SetReg(base, PBB_C6_MN_STRM_ATTR_VSW_L, 0x6);
		SetReg(base, PBB_B5_MSA_MISC0, 0x20);
		break;
	case DP_FORMAT_720P_60:
		SetReg(base, PBB_B7_MN_STRM_ATTR_HTT_M, 0x6);
		SetReg(base, PBB_B8_MN_STRM_ATTR_HTT_L, 0x72);
		SetReg(base, PBB_B9_MN_STRM_ATTR_HST_M, 0x01);
		SetReg(base, PBB_BA_MN_STRM_ATTR_HST_L, 0x33);
		SetReg(base, PBB_BB_MN_STRM_ATTR_HWD_M, 0x5);
		SetReg(base, PBB_BC_MN_STRM_ATTR_HWD_L, 0x00);
		SetReg(base, PBB_BD_MN_STRM_ATTR_HSW_M, 0x0);
		SetReg(base, PBB_BE_MN_STRM_ATTR_HSW_L, 0x28);
		SetReg(base, PBB_BF_MN_STRM_ATTR_VTTE_M, 0x2);
		SetReg(base, PBB_C0_MN_STRM_ATTR_VTTE_L, 0xee);
		SetReg(base, PBB_C2_MN_STRM_ATTR_VST_L, 0x1a);
		SetReg(base, PBB_C3_MN_STRM_ATTR_VHT_M, 0x2);
		SetReg(base, PBB_C4_MN_STRM_ATTR_VHT_L, 0xd0);
		SetReg(base, PBB_C5_MN_STRM_ATTR_VSW_M, 0x0);
		SetReg(base, PBB_C6_MN_STRM_ATTR_VSW_L, 0x5);
		SetReg(base, PBB_B5_MSA_MISC0, 0x20);
		break;
	case DP_FORMAT_1080P_60:
		SetReg(base, PBB_B7_MN_STRM_ATTR_HTT_M, 0x8);
		SetReg(base, PBB_B8_MN_STRM_ATTR_HTT_L, 0x98);
		SetReg(base, PBB_B9_MN_STRM_ATTR_HST_M, 0x00);
		SetReg(base, PBB_BA_MN_STRM_ATTR_HST_L, 0xC1);
		SetReg(base, PBB_BB_MN_STRM_ATTR_HWD_M, 0x7);
		SetReg(base, PBB_BC_MN_STRM_ATTR_HWD_L, 0x80);
		SetReg(base, PBB_BD_MN_STRM_ATTR_HSW_M, 0x0);
		SetReg(base, PBB_BE_MN_STRM_ATTR_HSW_L, 0x2C);
		SetReg(base, PBB_BF_MN_STRM_ATTR_VTTE_M, 0x4);
		SetReg(base, PBB_C0_MN_STRM_ATTR_VTTE_L, 0x65);
		SetReg(base, PBB_C2_MN_STRM_ATTR_VST_L, 0x2A);
		SetReg(base, PBB_C3_MN_STRM_ATTR_VHT_M, 0x4);
		SetReg(base, PBB_C4_MN_STRM_ATTR_VHT_L, 0x38);
		SetReg(base, PBB_C5_MN_STRM_ATTR_VSW_M, 0x0);
		SetReg(base, PBB_C6_MN_STRM_ATTR_VSW_L, 0x5);
		SetReg(base, PBB_B5_MSA_MISC0, 0x20);
		break;
	case DP_FORMAT_2160P_30:
		SetReg(base, PBB_B7_MN_STRM_ATTR_HTT_M, 0x13);
		SetReg(base, PBB_B8_MN_STRM_ATTR_HTT_L, 0x30);
		SetReg(base, PBB_B9_MN_STRM_ATTR_HST_M, 0x01);
		SetReg(base, PBB_BA_MN_STRM_ATTR_HST_L, 0x81);
		SetReg(base, PBB_BB_MN_STRM_ATTR_HWD_M, 0xf);
		SetReg(base, PBB_BC_MN_STRM_ATTR_HWD_L, 0x00);
		SetReg(base, PBB_BD_MN_STRM_ATTR_HSW_M, 0x0);
		SetReg(base, PBB_BE_MN_STRM_ATTR_HSW_L, 0x58);
		SetReg(base, PBB_BF_MN_STRM_ATTR_VTTE_M, 0x8);
		SetReg(base, PBB_C0_MN_STRM_ATTR_VTTE_L, 0xca);
		SetReg(base, PBB_C2_MN_STRM_ATTR_VST_L, 0x53);
		SetReg(base, PBB_C3_MN_STRM_ATTR_VHT_M, 0x8);
		SetReg(base, PBB_C4_MN_STRM_ATTR_VHT_L, 0x70);
		SetReg(base, PBB_C5_MN_STRM_ATTR_VSW_M, 0x0);
		SetReg(base, PBB_C6_MN_STRM_ATTR_VSW_L, 0xa);
		SetReg(base, PBB_B5_MSA_MISC0, 0x20);
		break;
	case DP_FORMAT_2160P_60:
		SetReg(base, PBB_B7_MN_STRM_ATTR_HTT_M, 0xf);
		SetReg(base, PBB_B8_MN_STRM_ATTR_HTT_L, 0x50);
		SetReg(base, PBB_BA_MN_STRM_ATTR_HST_L, 0x49);
		SetReg(base, PBB_BB_MN_STRM_ATTR_HWD_M, 0xf);
		SetReg(base, PBB_BC_MN_STRM_ATTR_HWD_L, 0x00);
		SetReg(base, PBB_BD_MN_STRM_ATTR_HSW_M, 0x0);
		SetReg(base, PBB_BE_MN_STRM_ATTR_HSW_L, 0x20);
		SetReg(base, PBB_BF_MN_STRM_ATTR_VTTE_M, 0x8);
		SetReg(base, PBB_C0_MN_STRM_ATTR_VTTE_L, 0xae);
		SetReg(base, PBB_C2_MN_STRM_ATTR_VST_L, 0xf);
		SetReg(base, PBB_C3_MN_STRM_ATTR_VHT_M, 0x8);
		SetReg(base, PBB_C4_MN_STRM_ATTR_VHT_L, 0x70);
		SetReg(base, PBB_C5_MN_STRM_ATTR_VSW_M, 0x0);
		SetReg(base, PBB_C6_MN_STRM_ATTR_VSW_L, 0x8);
		SetReg(base, PBB_B5_MSA_MISC0, 0x3a);
		break;
	}
	SetBit(base, PBB_B4_MSA_CTRL, ~_BIT7, _BIT7);
}

void dptx_sst_setting(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	bool bMvidHWMode = true;
	unsigned char ucValidHwMvidMeaCnt = 0;
	unsigned short usLoopCnt = 0;
	unsigned short usMeasureTime = 0;
	unsigned int ulHwMvidMin = 0xFFFFFFFF;
	unsigned int ulHwMvidMax = 0x00000000;
	unsigned int pucData[6];
	int i;

	pucData[0] = 0;
	pucData[1] = 0x8000;
	pucData[2] = 0;
	pucData[3] = 0;

	hwinfo->DownStreamInfo.LinkRate = 1;
	pucData[0] = hwinfo->InputInfo.InputPixelClk * pucData[1];
	pucData[0] /= (hwinfo->DownStreamInfo.SSCSupport == true) ?
		(270 * hwinfo->DownStreamInfo.LinkRate *9975 / 10000) :
		(270 * hwinfo->DownStreamInfo.LinkRate);
	usMeasureTime = (unsigned short)(pucData[1] /
		( (hwinfo->DownStreamInfo.SSCSupport == true) ?
		(27 * hwinfo->DownStreamInfo.LinkRate *9975 / 10000) :
		(27 * hwinfo->DownStreamInfo.LinkRate)) / 5);
	usMeasureTime *= 2;

	for (i=0; i<10; i++) {
		// Enable HW Mvid measure
		SetBit(base, PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, _BIT7);
		// Delay time for one HW mvid measurement period time
		for(usLoopCnt = 0; usLoopCnt < usMeasureTime; usLoopCnt++)
			udelay(5);
		// Disable HW Mvid measure
		SetBit(base, PBB_A8_MN_VID_AUTO_EN_1, ~_BIT7, 0x00);

		pucData[2] = ((GetReg(base, PBB_AF_MVID_AUTO_H) << 16)
			| (GetReg(base, PBB_B0_MVID_AUTO_M) << 8)
			| GetReg(base, PBB_B1_MVID_AUTO_L));
		if (pucData[2] == 0) {
			SetReg(base, PBB_A9_MN_M_VID_H,
				*((unsigned char *)pucData+2));
			SetReg(base, PBB_AA_MN_M_VID_M,
				*((unsigned char *)pucData+1));
			SetReg(base, PBB_AB_MN_M_VID_L,
				*((unsigned char *)pucData+0));

			bMvidHWMode = false;
			break;
		}
		if(abs(pucData[0] - pucData[2]) > pucData[0] >> 2)
			continue;
		if(pucData[3] == 0) {
			if(pucData[2] < ulHwMvidMin)
				ulHwMvidMin = pucData[2];
			if(pucData[2] > ulHwMvidMax)
				ulHwMvidMax = pucData[2];
			pucData[3] = pucData[2];

			ucValidHwMvidMeaCnt++;
			continue;
		}
		if(abs(((pucData[3] + (ucValidHwMvidMeaCnt / 2)) /
			ucValidHwMvidMeaCnt) - pucData[2]) < 0x50) {
			if(pucData[2] < ulHwMvidMin)
				ulHwMvidMin = pucData[2];
			if(pucData[2] > ulHwMvidMax)
				ulHwMvidMax = pucData[2];
			pucData[3] += pucData[2];

			ucValidHwMvidMeaCnt++;
		}
	}

	if(bMvidHWMode == true) {
		if(ucValidHwMvidMeaCnt > 2) {
			pucData[3] -= ulHwMvidMax + ulHwMvidMin;
			ucValidHwMvidMeaCnt -= 2;
			pucData[3] = ((pucData[3] + (ucValidHwMvidMeaCnt / 2))
					/ ucValidHwMvidMeaCnt);
			if(abs(pucData[0] - pucData[3]) > (pucData[0] >> 1))
				pucData[3] = pucData[0];
		} else
			pucData[3] = pucData[0];

		SetReg(base, PBB_A9_MN_M_VID_H, *((unsigned char *)pucData+14));
		SetReg(base, PBB_AA_MN_M_VID_M, *((unsigned char *)pucData+13));
		SetReg(base, PBB_AB_MN_M_VID_L, *((unsigned char *)pucData+12));
	}
	SetReg(base, PBB_AC_MN_N_VID_H, *((unsigned char *)pucData+6));
	SetReg(base, PBB_AD_MN_N_VID_M, *((unsigned char *)pucData+5));
	SetReg(base, PBB_AE_MN_N_VID_L, *((unsigned char *)pucData+4));
	SetBit(base, PBB_B4_MSA_CTRL, ~_BIT6, 0x00);
	SetBit(base, PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);

	dptx_sstmsa_setting(hwinfo);
	dptx_sst_displayformat_setting(hwinfo);

	SetReg(base, PBB_A4_PG_FIFO_CTRL, 0xFF);
	
#if defined(AUDIO_ON) && AUDIO_ON
	dptx_sst_audioplay_setting(hwinfo);
#else
	SetReg(base, PBB_C7_VBID, 0x4);
	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, 0);
#endif
}

void dptx_irq_handle(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned int reg;

	reg = GetReg(base, PBD_B1_AUX_IRQ_EVENT);

	if((reg & _BIT5)==_BIT5) {
		hwinfo->aux_status = 1;
		up(&hwinfo->sem);
	} else {
		pr_err("not expect interrupt 0x%x\n", reg);
		hwinfo->aux_status = 0;
		dptx_aux_reset(hwinfo);
		up(&hwinfo->sem);
	}
	
	SetReg(base, PBD_B1_AUX_IRQ_EVENT, 0x3F);
	SetBit(base, PBD_AB_AUX_FIFO_CTRL, ~(_BIT1 | _BIT0), (_BIT1 | _BIT0));
}

void vo_common_setting(void __iomem *pll_base, void __iomem *vo_base)
{
	writel(0x10C167, pll_base + 0x260);
	writel(0x7, pll_base + 0x264);
	writel(0x3, pll_base + 0x264);
	mdelay(10);
	writel(0x10, vo_base + 0x8);
	writel(0x3, vo_base);
	writel(0x5, vo_base + 0x4);
	writel(0x1401, vo_base + 0x28);
	writel(0x2000000, vo_base + 0x38);
	writel(0x3000000, vo_base + 0x3c);

#ifndef TESTING
	writel(0x8000800, vo_base + 0xdfc);
	writel(0x800, vo_base + 0xe00);
	writel(0xed83e80, vo_base + 0xe04);
	writel(0x3c410c99, vo_base + 0xe08);
	writel(0x0, vo_base + 0xe0C);
	writel(0x150cda, vo_base + 0xe10);
	writel(0xc4a, vo_base + 0xe14);
#else
	writel(0x8000000, vo_base + 0xdfc);
	writel(0x0, vo_base + 0xe00);
	writel(0x8000000, vo_base + 0xe04);
	writel(0x800, vo_base + 0xe08);
	writel(0x0, vo_base + 0xe0C);
	writel(0x0, vo_base + 0xe10);
	writel(0x0, vo_base + 0xe14);
	writel(0x3, vo_base);
#endif
}

void dptx_set_720p_1lane(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *lvds_base = hwinfo->lvds_base;
	void __iomem *base = hwinfo->reg_base;
	void __iomem *vo_base = hwinfo->vo_base;

#if RTK_VO_SET
	void __iomem *pll_base = hwinfo->pll_base;
	vo_common_setting(pll_base, vo_base);
#else
	SetReg(base, PBB_C8_VBID_FW_CTL, 0x1);
#endif
	hwinfo->InputInfo.InputPixelClk = 74;

	SetReg(lvds_base, CT_CTRL, 0);
	SetReg(lvds_base, DH_WIDTH, 0x28);
	SetReg(lvds_base, DH_TOTAL, 0x6720672);
	SetReg(lvds_base, DH_DEN_START_END, 0x0fb05fb);
	SetReg(lvds_base, DV_DEN_START_END_F1, 0x1a02ea);
	SetReg(lvds_base, DV_TOTAL, 0x2ee);
	SetReg(lvds_base, DV_VS_START_END_F1, 0x10006);
#if RTK_VO_SET
	SetReg(lvds_base, DV_SYNC_INT, 0x800002eb);
	
	writel(0x500, vo_base + 0x48);
	writel(0x500, vo_base + 0x4c);
	writel(0x5002d0, vo_base + 0x68);
	writel(0x50002d0, vo_base + 0xd78);
#else
	SetReg(lvds_base, DV_SYNC_INT, 0x000002eb);
#endif
	dptx_sst_setting(hwinfo);

	SetReg(base, PBB_00_DP_PHY_CTRL, 0x14);
	SetReg(base, PBB_A0_DP_MAC_CTRL, 0x5);
	SetReg(lvds_base, AIF_EDP1, 0x1);
	SetReg(base, PBC_A7_DPTX_SFIFO_CTRL0, 0x80);
	SetReg(base, PBB_0D_DPTX_PHY_CTRL, 0x15);

#if RTK_VO_SET
	writel(0x47, vo_base + 0xec4);
	writel(0x3, vo_base + 0x20);
	writel(0x3, vo_base + 0xe78);
#else
	writel(0x3, vo_base + 0xe78);
#endif
}

void dptx_set_1080p_2lane(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *lvds_base = hwinfo->lvds_base;
	void __iomem *base = hwinfo->reg_base;
	void __iomem *vo_base = hwinfo->vo_base;

#if RTK_VO_SET
	void __iomem *pll_base = hwinfo->pll_base;
	vo_common_setting(pll_base, vo_base);
#else
	SetReg(base, PBB_C8_VBID_FW_CTL, 0x1);
#endif
	hwinfo->InputInfo.InputPixelClk = 148; 

	SetReg(lvds_base, CT_CTRL, 0);
	SetReg(lvds_base, DH_WIDTH, 0x2C);
	SetReg(lvds_base, DH_TOTAL, 0x8980898);
	SetReg(lvds_base, DH_DEN_START_END, 0xb70837);
	SetReg(lvds_base, DV_DEN_START_END_F1, 0x2A0462);
	SetReg(lvds_base, DV_TOTAL, 0x465);
	SetReg(lvds_base, DV_VS_START_END_F1, 0x10006);
#if RTK_VO_SET
	SetReg(lvds_base, DV_SYNC_INT, 0x80000463);
	
	writel(0x780, vo_base + 0x48);
	writel(0x780, vo_base + 0x4c);
	writel(0x780438, vo_base + 0x68);
	writel(0x7800438, vo_base + 0xd78);
#else
	SetReg(lvds_base, DV_SYNC_INT, 0x00000463);
#endif
	dptx_sst_setting(hwinfo);
	
	SetReg(base, PBB_00_DP_PHY_CTRL, 0x38);

	SetReg(base, PBB_A0_DP_MAC_CTRL, 0x6);
	SetReg(lvds_base, AIF_EDP1, 0x3);
	SetReg(base, PBC_A7_DPTX_SFIFO_CTRL0, 0x80);
//	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, 0);
	SetReg(base, PBB_0D_DPTX_PHY_CTRL, 0x15);

//	SetBit(base, PBB_A8_MN_VID_AUTO_EN_1, ~(_BIT7 | _BIT6), _BIT6);
#if RTK_VO_SET
	writel(0x47, vo_base + 0xec4);
	writel(0x3, vo_base + 0x20);
	writel(0x3, vo_base + 0xe78);
#else
	writel(0x3, vo_base + 0xe78);
#endif
}

void dptx_set_2160p30_4lane(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	void __iomem *lvds_base = hwinfo->lvds_base;
	void __iomem *vo_base = hwinfo->vo_base;
#if RTK_VO_SET
	void __iomem *pll_base = hwinfo->pll_base;
	vo_common_setting(pll_base, vo_base);
#else
	SetReg(base, PBB_C8_VBID_FW_CTL, 0x1);
#endif

	hwinfo->InputInfo.InputPixelClk = 297; 

	SetReg(lvds_base, CT_CTRL, 0);
	SetReg(lvds_base, DH_WIDTH, 0x58);
	SetReg(lvds_base, DH_TOTAL, 0x11301130);
	SetReg(lvds_base, DH_DEN_START_END, 0x1771077);
	SetReg(lvds_base, DV_DEN_START_END_F1, 0x5308c3);
	SetReg(lvds_base, DV_TOTAL, 0x8ca);
	SetReg(lvds_base, DV_VS_START_END_F1, 0x1000b);
#if RTK_VO_SET
	SetReg(lvds_base, DV_SYNC_INT, 0x800008c4);
	
	writel(0xf00, vo_base + 0x48);
	writel(0xf00, vo_base + 0x4c);
	writel(0xf00870, vo_base + 0x68);
	writel(0xf000870, vo_base + 0xd78);
#else
	SetReg(lvds_base, DV_SYNC_INT, 0x000008c4);
#endif
	dptx_sst_setting(hwinfo);

	SetReg(base, PBB_00_DP_PHY_CTRL, 0xFC);
	SetReg(base, PBB_A0_DP_MAC_CTRL, 0x7);
	SetReg(lvds_base, AIF_EDP1, 0xf);
	
	SetReg(base, PBC_A7_DPTX_SFIFO_CTRL0, 0x80);
//	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, 0);
	SetReg(base, PBB_0D_DPTX_PHY_CTRL, 0x15);

#if RTK_VO_SET
	writel(0x47, vo_base + 0xec4);
	writel(0x3, vo_base + 0x20);
	writel(0x3, vo_base + 0xe78);
#else
	writel(0x3, vo_base + 0xe78);
#endif
}

void dptx_set_2160p60_4lane(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	void __iomem *lvds_base = hwinfo->lvds_base;
	void __iomem *vo_base = hwinfo->vo_base;

#if RTK_VO_SET
	void __iomem *pll_base = hwinfo->pll_base;
	vo_common_setting(pll_base, vo_base);
#else
	SetReg(base, PBB_C8_VBID_FW_CTL, 0x1);
#endif
	hwinfo->InputInfo.InputPixelClk = 522;

	writel(0x1, lvds_base+0x100);
	writel(0x2000, lvds_base+0x108);
	writel(0x0, lvds_base+0x10c);
	writel(0x2000, lvds_base+0x110);
	writel(0x20000000, lvds_base+0x114);
	writel(0x0, lvds_base+0x118);
	writel(0x0, lvds_base+0x11c);

	writel(0x20, lvds_base+0x404);
	writel(0xf500f50, lvds_base+0x408);
	writel(0x3f0f3f, lvds_base+0x40c);
	writel(0xf087f, lvds_base+0x410);
	writel(0x8ae, lvds_base+0x418);
	writel(0x10009, lvds_base+0x41C);
	writel(0x00000880, lvds_base+0x42C);

#if RTK_VO_SET
	writel(0xf00, vo_base + 0x48);
	writel(0xf00, vo_base + 0x4c);
	writel(0xf00870, vo_base + 0x68);
	writel(0xf000870, vo_base + 0xd78);
	writel(0xf00, vo_base + 0x48);
	writel(0xf00, vo_base + 0x4c);
#endif
	dptx_sst_setting(hwinfo);

	SetReg(base, PBB_00_DP_PHY_CTRL, 0xFC);
	SetReg(base, PBB_A0_DP_MAC_CTRL, 0x7);
	writel(0xf, lvds_base + 0x40);

	SetReg(base, PBC_A7_DPTX_SFIFO_CTRL0, 0x80);
//	SetReg(base, PBB_D4_ARBITER_SEC_END_CNT_HB, 0);
	SetReg(base, PBB_0D_DPTX_PHY_CTRL, 0x15);
#if RTK_VO_SET
	writel(0x47, vo_base + 0xec4);
	writel(0x3, vo_base + 0x20);
	writel(0x3, vo_base + 0xe78);
#else
	writel(0x3, vo_base + 0xe78);
#endif
}

bool dptx_config_tv_system(struct rtk_dptx_hwinfo *hwinfo)
{
	int mode;
	bool ret;

	mode = hwinfo->out_type;
	switch (mode) {
	case DP_FORMAT_1080P_60:
		dptx_set_1080p_2lane(hwinfo);
		break;
	case DP_FORMAT_2160P_30:
		dptx_set_2160p30_4lane(hwinfo);
		break;
	case DP_FORMAT_2160P_60:
		dptx_set_2160p60_4lane(hwinfo);
		break;
	case DP_FORMAT_720P_60:
	default:
		dptx_set_720p_1lane(hwinfo);
		break;
	}
	ret = dptx_link_training(hwinfo);
	if(ret == false)
		pr_err("DPTX - Link Training fail\n");
	else
		pr_info("DPTX - Link Training Success\n");

	return ret;
}

