/*
 *  dptx_hdcp.c - RTK display port hdcp driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/random.h>
#include <linux/delay.h>
#include "dptx_hdcp.h"
#include "dptx_aux_channel.h"

unsigned char ksv[5] = {0x0};
unsigned char private[320] = {0x0};

void dptx_hdcp_change_state(struct rtk_dptx_hwinfo *hwinfo, int state)
{
	struct DPTxHDCPAuthInfo *hdcp = &hwinfo->HDCPInfo;

	hdcp->AuthState = state;
	hdcp->AuthStateChange = true;
}

static void dptx_hdcp_encrypt_en(struct rtk_dptx_hwinfo *hwinfo, int en)
{
	void __iomem *base = hwinfo->reg_base;

	if (en)
		SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, _BIT1);
	else
        	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT1, 0x00);
}

void dptx_hdcp_set_privatekey(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	int i;

	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, _BIT3);
	for (i=0; i<320; i++)
		SetReg(base, PBB_32_DP_HDCP_KEY_DL_PORT, private[i]);
	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, 0);
}

void dptx_hdcp_check_capability(struct rtk_dptx_hwinfo *hwinfo)
{
	struct DPTxHDCPAuthInfo *hdcp = &hwinfo->HDCPInfo;
	unsigned char data[20];

	hdcp->IsHDCPSupported = false;
	hdcp->IsDownstreamRepeater = false;

	if (dptx_aux_native_read(hwinfo, 0x68028, 1, data)) {
		if (data[0] & (unsigned char)_BIT0)
			hdcp->IsHDCPSupported = true;
		if (data[0] & (unsigned char)_BIT1)
			hdcp->IsDownstreamRepeater = true;
	}
	pr_info("dptx - HDCP = %d, Repeater = %d\n", hdcp->IsHDCPSupported, hdcp->IsDownstreamRepeater);
}

static bool dptx_hdcp_check_bksv(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char data[20];
	bool ret = false;

	dptx_aux_native_read(hwinfo, 0x68000, 5, data);

	SetReg(base, PBB_4F_BKSV_0, data[0]);
	SetReg(base, PBB_50_BKSV_1, data[1]);
	SetReg(base, PBB_51_BKSV_2, data[2]);
	SetReg(base, PBB_52_BKSV_3, data[3]);
	SetReg(base, PBB_53_BKSV_4, data[4]);
	
	// Turn on circuit that check BKSV
	SetBit(base, PBB_56_DP_HDCP_TX, ~_BIT2, _BIT2);

	msleep(10);

	pr_err("bksv reg = 0x%x\n", GetReg(base, PBB_56_DP_HDCP_TX));
	if ((GetReg(base, PBB_56_DP_HDCP_TX) & _BIT1) == _BIT1) {
		if ((GetReg(base, PBB_56_DP_HDCP_TX) & _BIT0) == 0)
			ret = true;
	}
	SetBit(base, PBB_56_DP_HDCP_TX, ~_BIT2, 0x00);
	
	return ret;
}

static void dptx_hdcp_auth1_gen_an(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char data[20];
	int i;
	unsigned int rand;

	// Write an_gen_start = 1 , and An gen start to run
	SetBit(base, PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, _BIT3);

	// Write reg_freerun_init an initial value
	rand = get_random_int();
	pr_err("dptx gen random = 0x%x\n", rand);
	SetReg(base, PBB_58_DP_HDCP_AN_SEED, rand);

	// Write reg_freerun_init_en 0 to 1 to load init value
	SetBit(base, PBB_56_DP_HDCP_TX, ~_BIT3, _BIT3);

	msleep(10);

	// Write an_gen_start = 0 , An gen stop
	SetBit(base, PBB_31_DPTX_HDCP_CTRL2, ~_BIT3, 0x00);

	// Disable load init value
	SetBit(base, PBB_56_DP_HDCP_TX, ~_BIT3, 0x00);

	for (i=0; i<8; i++)
		data[i] = GetReg(base, PBB_3B_AN_BYTE_0 - i*4);
	
	dptx_aux_native_write(hwinfo, 0x6800c, 8, data);

	for (i=0; i<5; i++)
		data[i] = ksv[i];
	dptx_aux_native_write(hwinfo, 0x68007, 5, data);
}

static bool dptx_hdcp_auth1_gen_km(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	bool ret = false;

	// Turn on computation
	SetBit(base, PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, _BIT1);

	msleep(10);
	if (GetReg(base, PBB_31_DPTX_HDCP_CTRL2) & _BIT0)
		ret = true;

	SetBit(base, PBB_31_DPTX_HDCP_CTRL2, ~_BIT1, 0x00);

	return ret;
}

static bool dptx_hdcp_auth1_compare_r0(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	unsigned char cnt = 0;
	unsigned char data[20];

	pr_err("enter %s\n", __func__);
	do {
		dptx_aux_native_read(hwinfo, 0x68005, 2, data);
		if (GetReg(base, PBB_4C_R0_BYTE_LSB) == data[0] &&
			GetReg(base, PBB_4B_R0_BYTE_MSB) == data[1])
			return true;
		msleep(10);
		cnt ++;
	} while (cnt < 3);
	pr_err("exit %s fail\n", __func__);

	return false;
}

static bool dptx_hdcp_auth1_proc(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;
	struct DPTxHDCPAuthInfo *hdcp = &hwinfo->HDCPInfo;
	bool ret;

	pr_err("enter %s\n", __func__);
	// Enable DP Tx HDCP Tx function .
	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT0, _BIT0);

	// Step1: Read Bcap from DPCD
	dptx_hdcp_check_capability(hwinfo);

	if (!hdcp->IsHDCPSupported)
		return false;

	if (!dptx_hdcp_check_bksv(hwinfo)) {
		pr_err("check bksv error\n");
		hdcp->AuthStart = false;
		return false;
	}
	// Step3: Generate An
	dptx_hdcp_auth1_gen_an(hwinfo);

	ret = dptx_hdcp_auth1_gen_km(hwinfo);
	pr_err("exit %s %d\n", __func__, ret);

	return ret;
}

void dptx_hdcp_initial(struct rtk_dptx_hwinfo *hwinfo)
{
	struct DPTxHDCPAuthInfo *hdcp = &hwinfo->HDCPInfo;
	void __iomem *base = hwinfo->reg_base;
	int i;

	dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_IDLE);
	// Set ECF by FW mode
	SetBit(base, PBB_64_HDCP_ECF_BYTE0, ~_BIT7, 0x00);

	// Set HPD 1ms Timer to  2ms
	SetBit(base, PBB_73_HPD_TIMER1, ~(_BIT3 | _BIT2 | _BIT1 | _BIT0), (_BIT3 | _BIT2 | _BIT0));
	SetReg(base, PBB_75_HPD_TIMER3, 0x2C);
	// Set HPD 10ms Timer to  2ms
	SetReg(base, PBB_78_HPD_TIMER6, 0x0D);
	SetReg(base, PBB_79_HPD_TIMER7, 0x2C);
	// Enable HPD Detection
	SetBit(base, PBB_70_HPD_CTRL, ~_BIT7, 0x00);
	SetBit(base, PBB_70_HPD_CTRL, ~_BIT7, _BIT7);
	// Clear HPD IRQ Flag
	SetReg(base, PBB_71_HPD_IRQ, 0xFE);
	// Enable Short IRQ and Disable Long IRQ
	SetBit(base, PBB_72_HPD_IRQ_EN, ~(_BIT6 | _BIT5), _BIT6 | _BIT7 | _BIT5);

	// Clear HDCP Flag
	hdcp->AuthStart = false;
	hdcp->AuthHold = false;
	
	// Set private key
	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, _BIT3);
	for (i=0; i<320; i++)
		SetReg(base, PBB_32_DP_HDCP_KEY_DL_PORT, private[i]);
	SetBit(base, PBB_30_DPTX_HDCP_CTRL1, ~_BIT3, 0);
}

void dptx_hdcp_handler(struct rtk_dptx_hwinfo *hwinfo)
{
	struct DPTxHDCPAuthInfo *hdcp = &hwinfo->HDCPInfo;
//	bool ret;

	hdcp->AuthDownstreamEvent = _DP_HDCP_AUTH_EVENT_NONE;
	
	switch (hdcp->AuthState) {
	case _DP_HDCP_STATE_IDLE:
		pr_err("enter state _DP_HDCP_STATE_IDLE)\n");
		if (hdcp->AuthStateChange == true) {
			hdcp->AuthStateChange = false;
			hdcp->R0Timeout = false;
			hdcp->VReadyTimeout = false;
			hdcp->PollingVReady = false;
			hdcp->VReadyBit = false;
			hdcp->AuthHold = false;
			hdcp->BInfoDevice = 0;
			hdcp->BInfoDepth = 0;
			dptx_hdcp_encrypt_en(hwinfo, 0);
			dptx_hdcp_check_capability(hwinfo);
			dptx_hdcp_set_privatekey(hwinfo);

			memset(hwinfo->ksvfifo, 0, sizeof(hwinfo->ksvfifo));
		}
		if (hdcp->IsHDCPSupported && hwinfo->LTInfo.LTResult == _DP_TX_TRAINING_PASS) {
			hdcp->AuthStart = false;
			dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_AUTH_1);
		}
		break;
	case _DP_HDCP_STATE_AUTH_1:
		pr_err("enter state _DP_HDCP_STATE_AUTH_1\n");
		if (hdcp->AuthStateChange) {
			hdcp->AuthStateChange = false;
			hdcp->AuthHold = true;

			if (dptx_hdcp_auth1_proc(hwinfo) == true)
				dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_AUTH_1_COMPARE_R0);
			else
				dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_IDLE);
		}
		break;
	case _DP_HDCP_STATE_AUTH_1_COMPARE_R0:
		pr_err("enter state _DP_HDCP_STATE_AUTH_1_COMPARE_R0\n");
		if (hdcp->AuthStateChange) {
			hdcp->AuthStateChange = false;
			msleep(100);
			if (dptx_hdcp_auth1_compare_r0(hwinfo))
				dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_AUTH_PASS);
			else
				dptx_hdcp_change_state(hwinfo, _DP_HDCP_STATE_IDLE);
		}
		break;
	case _DP_HDCP_STATE_AUTH_PASS:
		if (hdcp->AuthStateChange) {
			hdcp->AuthStateChange = false;
			pr_err("AUTH_PASS enable encryption\n");
			dptx_hdcp_encrypt_en(hwinfo, 1);
		}
		break;
	default:
		break;
	}
}
