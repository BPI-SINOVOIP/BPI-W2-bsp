/*
 * hdmirx_hdcp2p2.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "v4l2_hdmi_dev.h"
#include "hdmiInternal.h"

static unsigned char lc128_key[16];
static unsigned char hdcp2p2key_enable = false;

unsigned char wait_init = 0;
struct hdcp2p2_wait_event hdcp2p2_wait;
struct hdcp2p2_wait_event stream_wait;

unsigned char Repeater_clear_repeater_bit;
/*=================== extern Variable/Function ===================*/
extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;

extern void Hdmi_HdcpPortWrite(unsigned char addr, unsigned char value);
/*======================================================*/



/* HDCP2-2  global variable */
unsigned char g_bmsg_id;
unsigned char g_RX_state;
unsigned char g_Rx_Send_State;

unsigned char TX_msg_id[864];
unsigned char stream_manage_msg[10];
unsigned char stream_manage_flag;
unsigned char bLen;

unsigned int b_Tx_Len;

#define HDCP_RXstatus_addr    0x70
/* Message ID*/
#define IDEL                    0   /* TX=>RX */
#define AKE_INIT                2   /* TX=>RX */
#define AKE_Send_Cert           3   /* RX=>TX */
#define AKE_NO_Stored_Km        4   /* TX=>RX */
#define AKE_Stored_Km           5   /* TX=>RX */
#define AKE_Send_H_prime        7   /* RX=>TX */
#define AKE_Send_Pariring_Info  8   /* RX=>TX */
#define LC_Init                 9   /* TX=>RX */
#define LC_Send_L_prime         10  /* RX=>TX */
#define SKE_Send_Eks            11  /* TX=>RX */
/* Repeaterauth Message ID*/
#define REPEATERAUTH_SEND_RECEIVERID_LIST	12  /* RX=>TX */
#define REPEATERAUTH_SEND_ACK				15  /* TX=>RX */
#define REPEATERAUTH_STREAM_MANAGE			16  /* TX=>RX */
#define REPEATERAUTH_STREAM_READY			17  /* RX=>TX */

/* RX send FSM*/
#define  RX_FSM_SEND_START		1
#define  RX_FSM_WAIT			2
#define  RX_FSM_FINISH			3

/* HDCP 2.2 OFFSET */
#define Write_Message_offset	0x60
#define Rxstatus_offset			0x70
#define Read_Message_offset		0x80

struct work_struct hdcp2p2_msg_work;
struct work_struct repeaterauth_stream_work;
static DEFINE_MUTEX(hdcprx2p2_lock);

void Hdmi_HDCP_2_2_msg_work_func(struct work_struct *work);
void repeaterauth_stream_work_func(struct work_struct *work);


char Get_Hdmi_hdcp_2_2_Write_Message(void)
{
	unsigned int wr_msg_done;

	wr_msg_done = HDCP_2P2_SR0_get_irq_wr_msg_done(hdmi_rx_reg_read32(HDCP_2P2_SR0, HDMI_RX_MAC));
	if (wr_msg_done)
		return 1;
	else
		return 0;
}

char Get_Hdmi_hdcp_2_2_Read_Message(void)
{
	unsigned int rd_msg_done;

	rd_msg_done = HDCP_2P2_SR0_get_irq_rd_msg_done(hdmi_rx_reg_read32(HDCP_2P2_SR0, HDMI_RX_MAC));
	if (rd_msg_done)
		return 1;
	else
		return 0;
}

void Clear_Hdmi_hdcp_2_2_Read_Status(void)
{
	hdmi_rx_reg_write32(HDCP_2P2_SR0, HDCP_2P2_SR0_irq_rd_msg_done_mask, HDMI_RX_MAC);
}

void HW_Cipher_Setting(unsigned char *lc128)
{
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~(HDCP_2P2_CR_fw_mode_riv_mask),
		HDCP_2P2_CR_fw_mode_riv_mask, HDMI_RX_MAC);

	/* lc 128 */
	hdmi_rx_reg_mask32(HDCP_2P2_LC0, ~HDCP_2P2_LC0_lc_mask,
		(lc128[15]|(lc128[14]<<8)|(lc128[13]<<16)|(lc128[12]<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_LC1, ~HDCP_2P2_LC1_lc_mask,
		(lc128[11]|(lc128[10]<<8)|(lc128[9]<<16)|(lc128[8]<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_LC2, ~HDCP_2P2_LC2_lc_mask,
		(lc128[7]|(lc128[6]<<8)|(lc128[5]<<16)|(lc128[4]<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_LC3, ~HDCP_2P2_LC3_lc_mask,
		(lc128[3]|(lc128[2]<<8)|(lc128[1]<<16)|(lc128[0]<<24)), HDMI_RX_MAC);
}

void Set_Rx_status_Ready(void)
{

	hdmi_rx_reg_write32(HDCP_AP, 0x71, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_DP, (0x1 << 2), HDMI_RX_MAC);
}

void DownStream_done(void)
{
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_downstream_done_mask,
		HDCP_2P2_CR_downstream_done_mask, HDMI_RX_MAC);
}
void KS_Setting(unsigned char *bKs)
{
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~(HDCP_2P2_CR_fw_mode_riv_mask), HDCP_2P2_CR_fw_mode_riv_mask, HDMI_RX_MAC);
	/* Initial ks value */
	hdmi_rx_reg_mask32(HDCP_2P2_KS0, ~HDCP_2P2_KS0_ks_mask,
		((*(bKs+15))|((*(bKs+14))<<8)|((*(bKs+13))<<16)|((*(bKs+12))<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_KS1, ~HDCP_2P2_KS1_ks_mask,
		((*(bKs+11))|((*(bKs+10))<<8)|((*(bKs+9))<<16)|((*(bKs+8))<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_KS2, ~HDCP_2P2_KS2_ks_mask,
		((*(bKs+7))|((*(bKs+6))<<8)|((*(bKs+5))<<16)|((*(bKs+4))<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_KS3, ~HDCP_2P2_KS3_ks_mask,
		((*(bKs+3))|((*(bKs+2))<<8)|((*(bKs+1))<<16)|((*bKs)<<24)), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_ks_done_mask,
		HDCP_2P2_CR_ks_done_mask, HDMI_RX_MAC);

	HDMIRX_INFO("[HDCP2.2]Set KS");
	HDMIRX_DEBUG("[HDCP2.2]KS_Setting bKs  = 0x%x , 0x%x ,0x%x ,0x%x ,0x%x ,0x%x ,0x%x ,0x%x",
		(*bKs), *(bKs+1), *(bKs+2), *(bKs+3), *(bKs+4), *(bKs+5), *(bKs+6), *(bKs+7));
}

void Riv_Setting(unsigned char *bRiv)
{
	hdmi_rx_reg_mask32(HDCP_2P2_RIV0, ~HDCP_2P2_RIV0_riv_mask,
		(*(bRiv+7)|(*(bRiv+6)<<8)|(*(bRiv+5)<<16)|(*(bRiv+4)<<24)), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_RIV1, ~HDCP_2P2_RIV1_riv_mask,
		(*(bRiv+3)|(*(bRiv+2)<<8)|(*(bRiv+1)<<16)|((*bRiv)<<24)), HDMI_RX_MAC);

	HDMIRX_INFO("[HDCP2.2]Set Riv");
	HDMIRX_DEBUG("[HDCP2.2]Riv_Setting bRiv = 0x%x , 0x%x ,0x%x ,0x%x ,0x%x ,0x%x ,0x%x ,0x%x",
		(*bRiv), *(bRiv+1), *(bRiv+2), *(bRiv+3), *(bRiv+4), *(bRiv+5), *(bRiv+6), *(bRiv+7));
	hdmi_ioctl_struct.hdcp_state = HDCPRX_STATE_2P2_ON;/* HDCP 2.2 nego success */
}

void init_hdcp2p2_waitqueue(void)
{
	if (wait_init)
		return;

	spin_lock_init(&hdcp2p2_wait.slock);
	init_waitqueue_head(&hdcp2p2_wait.read_wq);
	hdcp2p2_wait.condition = false;

	spin_lock_init(&stream_wait.slock);
	init_waitqueue_head(&stream_wait.read_wq);
	stream_wait.condition = false;

	wait_init = 1;
}

void HdmiRx_enable_hdcp2p2(unsigned char *key)
{
	if (hdcp2p2key_enable)/* Already save the key, return */
		return;

	if ((key[0] == 0) && (key[1] == 0) && (key[2] == 0) &&
		(key[3] == 0) && (key[4] == 0))
		HDMIRX_INFO("[HDCP2.2] Empty key, should be TEE case");

	memset(&lc128_key, 0, sizeof(lc128_key));
	memcpy(&lc128_key, key, sizeof(lc128_key));

	HDMIRX_INFO("[HDCP2.2] HDCP RX INIT");

	hdcp2p2key_enable = true;
}

unsigned char Is_HdmiRx_hdcp2p2_enabled(void)
{
	return hdcp2p2key_enable;
}

void Hdmi_HDCP_2_2_Init(void)
{
	static unsigned char init_work_flag = 0;

	HDMIRX_INFO("[HDCP2.2] Hdmi_HDCP_2_2_Init");

	Repeater_clear_repeater_bit = 0;

	if (!hdcp2p2key_enable) {
		HDMIRX_INFO("[HDCP2.2] key not ready");
		return;
	}

	/* Init msg work */
	if (!init_work_flag) {
		INIT_WORK(&hdcp2p2_msg_work, Hdmi_HDCP_2_2_msg_work_func);
		INIT_WORK(&repeaterauth_stream_work, repeaterauth_stream_work_func);
		init_work_flag = 1;
	}

	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_hdcp_2p2_en_mask,
		0, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDCP_2P2_SR1, ~HDCP_2P2_SR1_irq_wr_msg_done_en_mask,
		HDCP_2P2_SR1_irq_wr_msg_done_en_mask, HDMI_RX_MAC);

	/* Should not set cipher when TEE path on */
	if (lc128_key[0] || lc128_key[1] || lc128_key[2] ||
		lc128_key[3] || lc128_key[4])
		HW_Cipher_Setting(&lc128_key[0]);/* SET Lc  */

	/* enable hdcp 2.2 HW interrupt */
	Hdmi_HdcpPortWrite(0x50, 0x04);/* support hdcp2.2 */
	hdmi_rx_reg_mask32(HDCP_2P2_SR1, ~HDCP_2P2_SR1_irq_wr_msg_done_en_mask,
		HDCP_2P2_SR1_irq_wr_msg_done_en_mask, HDMI_RX_MAC);
}

char  Hdmi_HDCP2_2_Write_Data_to_TX(unsigned char *bSendData, unsigned int wLen)
{
	unsigned int i;

	if (bSendData == NULL)
		return FALSE;

	HDMI_PRINTF("[HDCP2.2] bSendData(%d)\n", bSendData[0]);

	mutex_lock(&hdcprx2p2_lock);

	for (i = 0; i < wLen; i++) {
		hdmi_rx_reg_write32(HDCP_MSAP, i, HDMI_RX_MAC);
		hdmi_rx_reg_write32(HDCP_MSDP, *(bSendData+i), HDMI_RX_MAC);
	}

	hdmi_rx_reg_write32(HDCP_AP, HDCP_RXstatus_addr, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_DP, (wLen&0xFF), HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_AP, HDCP_RXstatus_addr+1, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDCP_DP, ((wLen&0x3FF)>>8), HDMI_RX_MAC);

	mutex_unlock(&hdcprx2p2_lock);

	return TRUE;
}

void Hdmi_HDCP_2_2_Force_Cipher(void)
{
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~(HDCP_2P2_CR_switch_state_mask),
		HDCP_2P2_CR_switch_state(0x10), HDMI_RX_MAC);/* set authenticated */
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~(HDCP_2P2_CR_apply_state_mask | HDCP_2P2_CR_fw_mode_riv_mask),
		(HDCP_2P2_CR_apply_state_mask | HDCP_2P2_CR_fw_mode_riv_mask), HDMI_RX_MAC);

}

void Hdmi_HDCP_2_2_msg_work_func(struct work_struct *work)
{
	unsigned long flags;

	spin_lock_irqsave(&hdcp2p2_wait.slock, flags);
	hdcp2p2_wait.condition = true;
	wake_up_interruptible(&hdcp2p2_wait.read_wq);
	spin_unlock_irqrestore(&hdcp2p2_wait.slock, flags);
}

void repeaterauth_stream_work_func(struct work_struct *work)
{
	unsigned long flags;

	spin_lock_irqsave(&stream_wait.slock, flags);
	stream_wait.condition = true;
	wake_up_interruptible(&stream_wait.read_wq);
	spin_unlock_irqrestore(&stream_wait.slock, flags);
}

void  Hdmi_HDCP_2_2_msg_hander(void)
{
	unsigned char i;
	/* GET TX mesage */
	if (Get_Hdmi_hdcp_2_2_Write_Message()) {
		/* Must close hdcp1.4 when discover hdcp2.2 */
		if (HDCP_CR_get_hdcp_en(hdmi_rx_reg_read32(HDCP_CR, HDMI_RX_MAC))) {
			hdmi_rx_reg_mask32(HDCP_CR, ~HDCP_CR_hdcp_en_mask, 0, HDMI_RX_MAC);
			HDMIRX_INFO("[HDCP2.2] Discover 2.2, disable 1.4");
		}
		/* Open hdcp2p2 */
		hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_hdcp_2p2_en_mask,
			HDCP_2P2_CR_hdcp_2p2_en_mask, HDMI_RX_MAC);
		hdmi_rx_reg_write32(HDCP_MSAP, 0, HDMI_RX_MAC);
		g_bmsg_id = hdmi_rx_reg_read32(HDCP_MSDP, HDMI_RX_MAC);
		TX_msg_id[0] = g_bmsg_id;
		HDMI_PRINTF("[HDCP2.2] bmsg_id  =%x\n", g_bmsg_id);

		g_Rx_Send_State = RX_FSM_SEND_START;
		switch (g_bmsg_id) {
		case AKE_INIT:
			HDMIRX_INFO("[HDCP2.2] AKE_INIT");
			/* Discover HDCP 2.2 */
			hdmi_ioctl_struct.hdcp_state = HDCPRX_STATE_2P2_DISCOVER;
			g_RX_state = AKE_Send_Cert;
			bLen = 11;
			stream_manage_flag = 0;
			break;
		case AKE_NO_Stored_Km:
			HDMIRX_INFO("[HDCP2.2] AKE_NO_Stored_Km");
			g_RX_state =  AKE_Send_H_prime;
			bLen = 128;
			break;
		case AKE_Stored_Km:
			HDMIRX_INFO("[HDCP2.2] AKE_Stored_Km");
			g_RX_state =  AKE_Send_H_prime;
			bLen = 32;
			break;
		case LC_Init:
			/* HDMIRX_INFO("[HDCP2.2] LC_Init"); */
			/* Need reply in 20ms */
			g_RX_state = LC_Send_L_prime;
			bLen = 8;
			break;
		case SKE_Send_Eks:
			HDMIRX_INFO("[HDCP2.2] SKE_Send_Eks");
			hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_switch_state_mask,
				HDCP_2P2_CR_switch_state(0x01), HDMI_RX_MAC);
			hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_apply_state_mask,
				HDCP_2P2_CR_apply_state_mask, HDMI_RX_MAC);
			bLen = 24;
			break;
		case REPEATERAUTH_SEND_ACK:
			bLen = 16;
			break;
		case REPEATERAUTH_STREAM_MANAGE:
			/* HDMIRX_INFO("[HDCP2.2] REPEATERAUTH_STREAM_MANAGE"); */
			bLen = 7; /* k=1 */
			break;
		default:
			bLen = 0;
			HDMI_PRINTF("[HDCP2.2] Unknown message\n");
			break;
		}

		if (g_bmsg_id != REPEATERAUTH_STREAM_MANAGE) {
			for (i = 1; i <= bLen; i++)
				TX_msg_id[i] = hdmi_rx_reg_read32(HDCP_MSDP, HDMI_RX_MAC);
		} else {
			stream_manage_flag = 1;
			stream_manage_msg[0] = g_bmsg_id;
			for (i = 1; i <= 7; i++)
				stream_manage_msg[i] = hdmi_rx_reg_read32(HDCP_MSDP, HDMI_RX_MAC);
		}

		/* For HW Cipher setting */
		if (g_bmsg_id == SKE_Send_Eks)
			Riv_Setting((&(TX_msg_id[17])));/* Set Riv address */

		/* Clear interrupt */
		hdmi_rx_reg_write32(HDCP_2P2_SR0, HDCP_2P2_SR0_irq_wr_msg_done_mask, HDMI_RX_MAC);
		hdmi_rx_reg_write32(HDMI_INTCR, 0x80, HDMI_RX_MAC);

		if (g_bmsg_id != REPEATERAUTH_STREAM_MANAGE)
			schedule_work(&hdcp2p2_msg_work);
		else
			schedule_work(&repeaterauth_stream_work);
	}

}

int get_hdcp2p2_msg(struct rx_hdcp22_msg *msg)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&hdcp2p2_wait.slock, flags);
	hdcp2p2_wait.condition = false;
	spin_unlock_irqrestore(&hdcp2p2_wait.slock, flags);

	wait_event_interruptible(hdcp2p2_wait.read_wq, hdcp2p2_wait.condition);

	msg->g_RX_state = g_RX_state;
	for (i = 0; i <= bLen; i++)
		msg->msg[i] = TX_msg_id[i];
	msg->bLen = bLen;

	return 0;
}

int write_hdcp2p2_msg_to_tx(struct rx_hdcp22_msg *msg)
{

	Hdmi_HDCP2_2_Write_Data_to_TX(msg->msg, msg->bLen);

	return 0;
}

int get_stream_msg(struct rx_hdcp22_msg *msg)
{
	int i;
	unsigned long flags;

	HDMIRX_INFO("[HDCP2.2] get_stream_msg enter");

	spin_lock_irqsave(&stream_wait.slock, flags);
	stream_wait.condition = false;
	spin_unlock_irqrestore(&stream_wait.slock, flags);

	wait_event_interruptible(stream_wait.read_wq, stream_wait.condition);

	msg->bLen = 7;
	for (i = 0; i <= 7; i++)
		msg->msg[i] = stream_manage_msg[i];

	HDMIRX_INFO("[HDCP2.2] get_stream_msg exit");

	return 0;
}

void set_hdcp2p2_condition(void)
{
	unsigned long flags;

	spin_lock_irqsave(&hdcp2p2_wait.slock, flags);
	hdcp2p2_wait.condition = true;
	wake_up_interruptible(&hdcp2p2_wait.read_wq);
	spin_unlock_irqrestore(&hdcp2p2_wait.slock, flags);
}

int set_hdcp2p2_ks(struct rx_hdcp22_ks *ks)
{
	KS_Setting(&ks->bks[0]);

	return 0;
}

int get_hdcp2p2_msg_done(int *done)
{
	*done = (int)Get_Hdmi_hdcp_2_2_Read_Message();
	return 0;
}

int set_hdcp2p2_switch_state(int *state)
{
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_switch_state_mask,
		HDCP_2P2_CR_switch_state(0x10), HDMI_RX_MAC); /* authenticated */
	hdmi_rx_reg_mask32(HDCP_2P2_CR, ~HDCP_2P2_CR_apply_state_mask,
		HDCP_2P2_CR_apply_state_mask, HDMI_RX_MAC);

	return 0;
}
