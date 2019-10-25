/*
 *  dptx_aux_channel.c - RTK display port aux channel driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include "dptx_aux_channel.h"

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

bool dptx_aux_native_write(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucWriteArray)
{
	ucAddr = ucAddr | (0x80 << 16);
	return dptx_aux_write(hwinfo, ucAddr, ucLength, pucWriteArray);
}

bool dptx_aux_native_read(struct rtk_dptx_hwinfo *hwinfo,
			unsigned int ucAddr,
			unsigned char ucLength,
			unsigned char *pucReadArray)
{
	ucAddr = ucAddr | (0x90 << 16);	
	return dptx_aux_read(hwinfo, ucAddr, ucLength, pucReadArray);
}

bool dptx_aux_i2c_write(struct rtk_dptx_hwinfo *hwinfo,
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

bool dptx_aux_i2c_read(struct rtk_dptx_hwinfo *hwinfo,
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

void dptx_aux_irq_handle(struct rtk_dptx_hwinfo *hwinfo)
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

static void __maybe_unused dptx_aux_physet(struct rtk_dptx_hwinfo *hwinfo)
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

void dptx_aux_initial(struct rtk_dptx_hwinfo *hwinfo)
{
	void __iomem *base = hwinfo->reg_base;

//	dptx_aux_physet(hwinfo);

	// Sync end Pattern Error Handle Disable
	SetBit(base, PBD_F6_AUX_DIG_PHY8, ~_BIT1, _BIT1);
//	SetReg(base, PBD_64_AUX_4, 0xCA);
	// Set Aux Timeout
//	SetReg(base, PBD_A1_AUX_TIMEOUT, 0x95);
	// Power On Aux CH
	SetBit(base, PBD_A0_AUX_TX_CTRL, ~_BIT0, _BIT0);

//	SetBit(base, PBD_65_AUX_5, ~_BIT7, 0);
	SetBit(base, PBD_B2_AUX_IRQ_EN, 0,
		_BIT0 | _BIT1 | _BIT2 | _BIT3 | _BIT4 | _BIT5 | _BIT6 | _BIT7);

//	SetReg(base, PBD_AF_AUX_RETRY_1, 0x2);
//	SetBit(base, PBD_B0_AUX_RETRY_2,
//		~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT5);
//		~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3), _BIT7 | _BIT5);
}

