/*
 * hdmirx_hdcp.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "hdmiInternal.h"
#include "mipi_wrapper.h"

#ifdef CONFIG_RTK_HDCP1x_REPEATER
#include <soc/realtek/rtk_sha1.h>
extern unsigned long long hdcp_calculate_m0(unsigned long long aksv_value, unsigned long long an_val);
#endif

/* HDCP Bcaps */
#define BCAPS_HDMI_RESERVED	_BIT7
#define BCAPS_REPEATER		_BIT6
#define BCAPS_READY			_BIT5
#define BCAPS_FAST			_BIT4
#define BCAPS_1_1FEATURES	_BIT1
#define BCAPS_FAST_REAUTH	_BIT0

#define HDCP_BCAPS_DVI        (BCAPS_HDMI_RESERVED | BCAPS_FAST_REAUTH)
#define HDCP_BCAPS_HDMI       (BCAPS_HDMI_RESERVED | BCAPS_1_1FEATURES | BCAPS_FAST_REAUTH)
#define HDCP_BCAPS_REPEATER   (HDCP_BCAPS_HDMI | BCAPS_REPEATER)

/*=================== extern Variable/Function ===================*/
extern MIPI_TOP_INFO mipi_top;
extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;
extern HDMI_INFO_T hdmi;

extern void Hdmi_SetHPD(char high);
/*======================================================*/


#ifdef CONFIG_RTK_HDCPRX_2P2
extern void Hdmi_HDCP_2_2_Init(void);
#endif
#ifdef CONFIG_RTK_HDCPRX_1P4_TEE
extern void CA_hdcp1p4_load(void);
extern unsigned char TA_HDCP1p4_Load_flag;
extern int TEE2p1_Flag;
#endif

#ifdef CONFIG_RTK_HDCP1x_REPEATER
#define HDCP_MAX_KSV	5
struct hdcp_ksvlist_info tx_ksv_info;
#define CHECK_INTERVAL 5000
#define CHECK_TIMES 5

static void hdcp1x_repeater_work_fun(struct work_struct *work);
static DECLARE_WORK(hdcp1x_repeater_work, hdcp1x_repeater_work_fun);
#endif

HDCP_KEY_T rx_key;
static unsigned char hdcpkey_enable = false;

/**
 * Hdmi_HdcpPortCWrite -
 *      HDCP DDC port setting download function with auto-address increase
 *      where HDCP port ddc address for HOST side is 0x74/0x75
 *
 * @addr: hdcp register address
 * @data: data pointer
 * @num: length data
 */
void inline Hdmi_HdcpPortCWrite(unsigned char addr, HDMI_CONST unsigned char *value, unsigned char num)
{
	hdmi_rx_reg_mask32(HDCP_PCR, ~_BIT0, 0, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_AP, addr, HDMI_RX_MAC);

	while (num--)
		hdmi_rx_reg_write32(HDCP_DP, *(value++), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDCP_PCR, ~_BIT0, _BIT0, HDMI_RX_MAC);
}

/**
 * Hdmi_HdcpPortWrite -
 *      HDCP DDC port setting download function
 *      where HDCP port ddc address for HOST side is 0x74/0x75
 *
 * @addr: hdcp register address
 * @value: data
 */
void Hdmi_HdcpPortWrite(unsigned int addr, unsigned int value)
{
	hdmi_rx_reg_write32(HDCP_AP, addr, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_DP, value, HDMI_RX_MAC);
}

/**
 * Hdmi_HdcpPortRead -
 *      HDCP DDC port setting read function
 *      where HDCP port ddc address for HOST side is 0x74/0x75
 *
 * @addr: hdcp register address
 *
 * Return: data
 */
unsigned char Hdmi_HdcpPortRead(unsigned int addr)
{
	hdmi_rx_reg_write32(HDCP_AP, addr, HDMI_RX_MAC);
	return hdmi_rx_reg_read32(HDCP_DP, HDMI_RX_MAC);
}


#ifdef CONFIG_RTK_HDCP1x_REPEATER
void HdmiRx_save_tx_ksv(struct hdcp_ksvlist_info *tx_ksv)
{
	memcpy(&tx_ksv_info, tx_ksv, sizeof(tx_ksv_info));

	hdmi.tx_hdcp_state = 1;
	HDMIRX_INFO("TX ksv ready");

	HDMI_PRINTF("TX ksv info:\n");
	HDMI_PRINTF("device_count(%u)\n", tx_ksv_info.device_count);
	HDMI_PRINTF("Bstatus(0x%02x%02x)\n", tx_ksv_info.bstatus[1], tx_ksv_info.bstatus[0]);
	HDMI_PRINTF("Bksv(0x%02x %02x %02x %02x %02x)\n",
		tx_ksv_info.Bksv[4], tx_ksv_info.Bksv[3], tx_ksv_info.Bksv[2],
		tx_ksv_info.Bksv[1], tx_ksv_info.Bksv[0]);
}

struct hdcp_ksvlist_info *HdmiRx_get_tx_ksv(void)
{
	return &tx_ksv_info;
}

void HdmiRx_disable_bcaps_ready(void)
{
	unsigned int tmp_value;

	if ((!mipi_top.hdmi_rx_init) || (!hdmi.tx_hdcp_state))/* Already disable */
		return;

	HDMI_PRINTF("%s\n", __func__);
	/* Disable Bcaps READY(Bit5) */
	tmp_value = Hdmi_HdcpPortRead(0x40)&0xDF;/* set bit 5 to 0 */
	Hdmi_HdcpPortWrite(0x40, tmp_value);
	hdmi.tx_hdcp_state = 0;
}

void HdmiRx_set_bstatus(unsigned char byte1, unsigned char byte0)
{
	if (!mipi_top.hdmi_rx_init)
		return;
	HDMI_PRINTF("%s\n", __func__);

	if ((byte1&0xF) < 0x7)/* less than seven levels */
		byte1 = (0x1<<4)|((byte1&0xF)+1);
	else/* Topology error */
		byte1 = (0x1<<4)|0xF;

	if (byte0 < HDCP_MAX_KSV)/* less than HDCP_MAX_KSV downstream devices */
		byte0 = byte0+1;
	else/* Topology error */
		byte0 = 0xFF;

	Hdmi_HdcpPortWrite(0x41, byte0);
	Hdmi_HdcpPortWrite(0x42, byte1);
}

/**
 * hdcprx_set_bcaps_ready - Enable/Disable Bcaps READY(Bit5)
 * @enable: 0 disable, 1 enable
 */
void hdcprx_set_bcaps_ready(unsigned char enable)
{
	unsigned int tmp_value;

	tmp_value = Hdmi_HdcpPortRead(0x40);
	if (enable)
		tmp_value |= 0x20;
	else
		tmp_value = Hdmi_HdcpPortRead(0x40)&0xDF;

	Hdmi_HdcpPortWrite(0x40, tmp_value);
}

void Hdmi_Hdcp1xRepeaterAuth(void)
{
	UINT8 aksv_reg[5], an_reg[8];
	unsigned long long AKSV = 0, An = 0;
	unsigned char *sha_data_buffer;
	unsigned int sha_index;
	unsigned char sha1[SHA1_DIGEST_SIZE];
	unsigned long long Mi;
	int k;
	unsigned int i, reg_value, Bstatus;
	struct hdcp_ksvlist_info *tx_ksv;

	tx_ksv = HdmiRx_get_tx_ksv();

	/* Wait TX ready, Max 1.5 s */
	for (i = 0; i < 15; i++) {
		if (hdmi.tx_hdcp_state)
			break;

		usleep_range(100000, 110000);
	}

	if (!hdmi.tx_hdcp_state) {
		HDMIRX_INFO("HDCP TX not ready");
		goto exit;
	}

	/* Alloc sha buffer: Bksv(5Bytes), KSV list(5Bytes for each ksv), Bstatus(2Bytes), M0'(8Bytes) */
	sha_data_buffer = kmalloc((5*(tx_ksv->device_count+1)+10)*sizeof(unsigned char), GFP_KERNEL);

	hdmi_rx_reg_mask32(HDCP_PCR, ~(_BIT1|_BIT0), _BIT1, HDMI_RX_MAC);
	/* Set KSV list */
	for (sha_index = 0; sha_index < 5; sha_index++) {
		/* HDMIRX_INFO("HdcpPortWrite(0x%03x):0x%02x",0x43+(sha_index<<8),tx_ksv->Bksv[sha_index]); */
		Hdmi_HdcpPortWrite(0x43+(sha_index<<8)/*ksvfifo_ptr*/, tx_ksv->Bksv[sha_index]);
		sha_data_buffer[sha_index] = tx_ksv->Bksv[sha_index];
	}

	for (sha_index = 5; sha_index < 5*(tx_ksv->device_count+1); sha_index++) {
		/* HDMIRX_INFO("HdcpPortWrite(0x%03x):0x%02x",0x43+(sha_index<<8),tx_ksv->ksvlist[sha_index-5]); */
		Hdmi_HdcpPortWrite(0x43+(sha_index<<8)/*ksvfifo_ptr*/, tx_ksv->ksvlist[sha_index-5]);
		sha_data_buffer[sha_index] = tx_ksv->ksvlist[sha_index-5];
	}

	if (hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC)&HDCP_FLAG1_wr_aksv_flag_mask) {
		HDMIRX_INFO("New AKSV after set KVS list");
		goto free_exit;
	}

	/* Set Bstatus, HDMI_MODE[12] MAX_CASCADE_EXCEEDED[11] DEPTH[10:8] DEVICE_COUNT[6:0] */
	/* Bstatus[15:8] */
	if ((tx_ksv->bstatus[1]&0xF) < 0x7)/* less than seven levels */
		Bstatus = (0x1<<12) | ((tx_ksv->bstatus[1]+1)<<8);
	else/* Topology error */
		Bstatus = (0x1<<12) | (0xF<<8);

	/* Bstatus[15:8]|Bstatus[7:0] */
	if (tx_ksv->bstatus[0] < HDCP_MAX_KSV)/* less than HDCP_MAX_KSV downstream devices */
		Bstatus = Bstatus | (tx_ksv->bstatus[0]+1);
	else/* Topology error */
		Bstatus = Bstatus | 0xFF;

	Hdmi_HdcpPortWrite(0x41, Bstatus & 0xFF);
	Hdmi_HdcpPortWrite(0x42, (Bstatus>>8)&0xFF);
	sha_data_buffer[sha_index++] = Bstatus & 0xFF;
	sha_data_buffer[sha_index++] = (Bstatus>>8)&0xFF;

	/* Readback Bstatus */
	HDMIRX_INFO("HDCP Bstatus:Byte1=0x%02x Byte2=0x%02x",
		Hdmi_HdcpPortRead(0x41), Hdmi_HdcpPortRead(0x42));

	if (hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC) & HDCP_FLAG1_wr_aksv_flag_mask) {
		HDMIRX_INFO("New AKSV after get Bstatus");
		goto free_exit;
	}

	/* Read AKSV */
	aksv_reg[0] = Hdmi_HdcpPortRead(0x10);/* [7:0] */
	aksv_reg[1] = Hdmi_HdcpPortRead(0x11);/* [15:8] */
	aksv_reg[2] = Hdmi_HdcpPortRead(0x12);/* [23:16] */
	aksv_reg[3] = Hdmi_HdcpPortRead(0x13);/* [31:24] */
	aksv_reg[4] = Hdmi_HdcpPortRead(0x14);/* [39:32] */
	AKSV = 0;
	for (k = 4; k >= 0; k--)
		AKSV = AKSV<<8 | aksv_reg[k];

	 HDMIRX_DEBUG("HDCP i=%d AKSV Flag = %x, %x ,%x ,%x, %x AKSV(%llx)",
		i, aksv_reg[0], aksv_reg[1], aksv_reg[2], aksv_reg[3], aksv_reg[4], AKSV);

	/* Read An */
	an_reg[0] = Hdmi_HdcpPortRead(0x18);/* [7:0] */
	an_reg[1] = Hdmi_HdcpPortRead(0x19);/* [15:8] */
	an_reg[2] = Hdmi_HdcpPortRead(0x1A);
	an_reg[3] = Hdmi_HdcpPortRead(0x1B);
	an_reg[4] = Hdmi_HdcpPortRead(0x1C);
	an_reg[5] = Hdmi_HdcpPortRead(0x1D);
	an_reg[6] = Hdmi_HdcpPortRead(0x1E);
	an_reg[7] = Hdmi_HdcpPortRead(0x1F);/* [63:56] */
	for (k = 7; k >= 0; k--)
		An = (An<<8) | an_reg[k];

	HDMIRX_DEBUG("HDCP An = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x ,0x%llx",
		an_reg[0], an_reg[1], an_reg[2], an_reg[3],
		an_reg[4], an_reg[5], an_reg[6], an_reg[7], An);

	/* Calcuate V' */
	Mi = hdcp_calculate_m0(AKSV, An);

	for (k = 0; k < 8; k++)
		sha_data_buffer[sha_index++] = (Mi>>(k*8))&0xFF;

	/*
	 * SHA-1 example
	 * Input "Hello" --> Output "f7ff9e8b7bb2e09b70935a5d785e0cc5d9d0abf0"
	 * char source[5]={'H', 'e', 'l', 'l', 'o'};
	 * sha1[0]=0xf7, sha1[1]=0xff, ..., sha1[19]=0xf0
	 */
	memset(sha1, 0, SHA1_DIGEST_SIZE*sizeof(unsigned char));
	MCP_SHA1_Get_Hash(sha_data_buffer, sha_index/*source length*/, sha1);

	/*
	 * for (k = 0; k < 20; k++)
	 *	HDMIRX_INFO("sha1[%u]=0x%02x", k, sha1[k]);
	 */

	/* Set V' */
	/* SHA-1 H0b */
	Hdmi_HdcpPortWrite(0x20, sha1[3]);
	Hdmi_HdcpPortWrite(0x21, sha1[2]);
	Hdmi_HdcpPortWrite(0x22, sha1[1]);
	Hdmi_HdcpPortWrite(0x23, sha1[0]);
	/* SHA-1 H1 */
	Hdmi_HdcpPortWrite(0x24, sha1[7]);
	Hdmi_HdcpPortWrite(0x25, sha1[6]);
	Hdmi_HdcpPortWrite(0x26, sha1[5]);
	Hdmi_HdcpPortWrite(0x27, sha1[4]);
	/* SHA-1 H2 */
	Hdmi_HdcpPortWrite(0x28, sha1[11]);
	Hdmi_HdcpPortWrite(0x29, sha1[10]);
	Hdmi_HdcpPortWrite(0x2A, sha1[9]);
	Hdmi_HdcpPortWrite(0x2B, sha1[8]);
	/* SHA-1 H3 */
	Hdmi_HdcpPortWrite(0x2C, sha1[15]);
	Hdmi_HdcpPortWrite(0x2D, sha1[14]);
	Hdmi_HdcpPortWrite(0x2E, sha1[13]);
	Hdmi_HdcpPortWrite(0x2F, sha1[12]);
	/* SHA-1 H4 */
	Hdmi_HdcpPortWrite(0x30, sha1[19]);
	Hdmi_HdcpPortWrite(0x31, sha1[18]);
	Hdmi_HdcpPortWrite(0x32, sha1[17]);
	Hdmi_HdcpPortWrite(0x33, sha1[16]);

	/* Reset AP address */
	hdmi_rx_reg_write32(HDCP_AP, 0x43, HDMI_RX_MAC);

	/* Dump V' */
	/*
	 * for (k = 0; k < 20; k++)
	 *	HDMIRX_INFO("ReadBack V'(%u):0x%02x", k, Hdmi_HdcpPortRead(0x20+k));
	 */

	/* For CTS 3C-I-03, TE write An twice */
	for (k = 0; k < CHECK_TIMES; k++) {
		usleep_range(CHECK_INTERVAL, CHECK_INTERVAL+10);
		reg_value = hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC);
		if (reg_value & HDCP_FLAG1_wr_aksv_flag_mask) {
			HDMIRX_INFO("New AKSV after set V'(%u)", k);
			goto free_exit;
		}
	}

	/* Enable Bcaps READY(Bit5) */
	if (hdmi.tx_hdcp_state)
		hdcprx_set_bcaps_ready(1);
	else
		HDMIRX_INFO("HDCP TX not ready");

	/* For 3C-I-04 */
	for (k = 0; k < CHECK_TIMES*10; k++) {
		usleep_range(CHECK_INTERVAL, CHECK_INTERVAL+10);
		reg_value = hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC);
		if (reg_value & HDCP_FLAG1_wr_aksv_flag_mask) {
			hdcprx_set_bcaps_ready(0);
			HDMIRX_INFO("New AKSV after Bcaps READY(%u)", k);
			goto free_exit;
		}
	}

free_exit:
	/* Free sha data buffer */
	kfree(sha_data_buffer);
exit:
	return;
}

static void hdcp1x_repeater_work_fun(struct work_struct *work)
{
	Hdmi_Hdcp1xRepeaterAuth();
	hdmi_rx_reg_mask32(HDCP_FLAG2, ~HDCP_FLAG2_irq_aksv_en_mask,
		HDCP_FLAG2_irq_aksv_en_mask, HDMI_RX_MAC);/* Enable AKSV interrupt */
}

void start_hdcp1x_repeater_work(void)
{
	hdcprx_set_bcaps_ready(0);

	hdmi_ioctl_struct.hdcp_state = HDCPRX_STATE_1PX_DISCOVER;/*  Discover HDCP 1.x */

	if (hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & _BIT0)/* HDMI mode */
		schedule_work(&hdcp1x_repeater_work);
}
#endif

void Hdmi_HdcpFSM(void)
{
	UINT32 hdcp_status_flag;

	hdcp_status_flag = hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC);

	/* Get TX write Aksv */
	if (HDCP_FLAG1_get_wr_aksv_flag(hdcp_status_flag)) {
#ifdef CONFIG_RTK_HDCPRX_2P2
		/* Disable HDCP 2.2 */
		if (HDCP_2P2_CR_hdcp_2p2_en(hdmi_rx_reg_read32(HDCP_2P2_CR, HDMI_RX_MAC))) {

			hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_hdcp_2p2_en_mask,
				0, HDMI_RX_MAC);
			HDMIRX_INFO("[HDCP] Discover 1.x, disable 2.2");
		}
#endif
		hdmi_ioctl_struct.hdcp_state = HDCPRX_STATE_1PX_DISCOVER;/*  Discover HDCP 1.x */

#ifndef CONFIG_RTK_HDCP1x_REPEATER
		hdmi_rx_reg_write32(HDCP_FLAG1, HDCP_FLAG1_wr_aksv_flag_mask, HDMI_RX_MAC); /* Clear Aksv flag */
#endif
	}

	if (HDCP_FLAG1_get_rd_ri_flag(hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC)))
		hdmi_rx_reg_write32(HDCP_FLAG1, HDCP_FLAG1_rd_ri_flag_mask, HDMI_RX_MAC);/* Clear Read Ri flag */

	if (hdmi_ioctl_struct.hdcp_state == HDCPRX_STATE_1PX_DISCOVER) {
		/* Get Ri means HDCP 1.x nego success */
		if (HDCP_FLAG1_get_rd_ri_flag(hdcp_status_flag))
			hdmi_ioctl_struct.hdcp_state = HDCPRX_STATE_1PX_ON;
	}
}

#ifdef CONFIG_RTK_HDCPRX_1P4_TEE
void HDMI_HDCP1p4_TEE_LOAD_KEY(void)
{
	if (TEE2p1_Flag == 0) {
		HDMIRX_ERROR("[HDCP TEE] Load key fail, TEE driver not enable");
		return;
	}

	CA_hdcp1p4_load();

	rx_key.BKsv[0] =  Hdmi_HdcpPortRead(0x0);
	rx_key.BKsv[1] =  Hdmi_HdcpPortRead(0x1);
	rx_key.BKsv[2] =  Hdmi_HdcpPortRead(0x2);
	rx_key.BKsv[3] =  Hdmi_HdcpPortRead(0x3);
	rx_key.BKsv[4] =  Hdmi_HdcpPortRead(0x4);
	HDMIRX_INFO("[HDCP TEE] BKSV = %02x %02x %02x %02x %02x",
		rx_key.BKsv[0], rx_key.BKsv[1], rx_key.BKsv[2],
		rx_key.BKsv[3], rx_key.BKsv[4]);

}
#endif

/**
 * Hdmi_HdcpInit -HDCP initial function
 */
void Hdmi_HdcpInit(void)
{
	int i;

	if (!hdcpkey_enable)
		return;

	HDMIRX_INFO("[HDCP] Hdmi_HdcpInit");

	/* Disable HDCP and clear HDCP address */
	hdmi_rx_reg_write32(HDCP_CR, 0x06, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDCP_PCR, ~HDCP_PCR_km_clk_sel_mask,
		HDCP_PCR_km_clk_sel_mask, HDMI_RX_MAC);

	/* Clear Data Port */
	hdmi_rx_reg_mask32(HDCP_PCR, ~_BIT0, 0, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_AP, 0x00, HDMI_RX_MAC);
	for (i = 0; i < 640; i++) {
		hdmi_rx_reg_write32(HDCP_AP, 0x43 + (i<<8), HDMI_RX_MAC);
		hdmi_rx_reg_write32(HDCP_DP, 0x00, HDMI_RX_MAC);
	}

	hdmi_rx_reg_write32(HDCP_AP, 0x00, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_PCR, ~_BIT0, _BIT0, HDMI_RX_MAC);

#ifdef CONFIG_RTK_HDCPRX_1P4_TEE
	HDMI_HDCP1p4_TEE_LOAD_KEY();
#else
	/* Write device private key */
	for (i = 0; i < 320; i++)
		hdmi_rx_reg_write32(HDCP_DKAP, rx_key.Key[i], HDMI_RX_MAC);
#endif

	/* Write BKsv into DDC channel */
	Hdmi_HdcpPortCWrite(0x00, rx_key.BKsv, 5);

#ifdef CONFIG_RTK_HDCPRX_2P2
	Hdmi_HDCP_2_2_Init();
	HDMI_PRINTF("HDCP2Vision = %x", Hdmi_HdcpPortRead(0x50));
#endif
	hdmi_rx_reg_write32(HDCP_CR, 0x00, HDMI_RX_MAC);

#ifdef CONFIG_RTK_HDCP1x_REPEATER
	/* Set Bcaps, repeater mode */
	Hdmi_HdcpPortWrite(0x40, HDCP_BCAPS_REPEATER);
	/* BIT6:repeater */
	hdmi_rx_reg_mask32(HDCP_CR, ~(_BIT7|_BIT0|_BIT6),
		(_BIT7|_BIT0|_BIT6), HDMI_RX_MAC);
	/* Keep old setting */
	Hdmi_HdcpPortWrite(0xc4, 0x00);
	/* Enable AKSV interrupt */
	hdmi_rx_reg_mask32(HDCP_FLAG2, ~HDCP_FLAG2_irq_aksv_en_mask,
		HDCP_FLAG2_irq_aksv_en_mask, HDMI_RX_MAC);
#else
	/* Set Bcaps */
	Hdmi_HdcpPortWrite(0x40, HDCP_BCAPS_HDMI);
	/* Enable HDCP function for all */
	hdmi_rx_reg_mask32(HDCP_CR, ~(_BIT7|_BIT0),
		(_BIT7|_BIT0), HDMI_RX_MAC);/* for New_AC_Mode Enable, fix simplay bug */
#endif

}

void HdmiRx_enable_hdcp(unsigned char *bksv, unsigned char *device_key)
{
	/* Return when already save the key */
	if (hdcpkey_enable)
		return;

	memset(&rx_key, 0, sizeof(rx_key));
	memcpy(&rx_key.BKsv, bksv, 5);
	memcpy(&rx_key.Key, device_key, 320);

	hdcpkey_enable = true;
	HDMIRX_INFO("HdmiRx_enable_hdcp");

	if (mipi_top.hdmi_rx_init) {
		Hdmi_SetHPD(0);
		Hdmi_HdcpInit();
		HDMI_DELAYMS(500);
		Hdmi_SetHPD(1);
	}

}

unsigned char Is_HdmiRx_hdcp1x_enabled(void)
{
	return hdcpkey_enable;
}

