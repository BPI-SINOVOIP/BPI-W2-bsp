/*
 * hdcp_lib.c - RTK hdcp tx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

#include "hdcp_top.h"
#include "hdcp_lib_hw.h"
#include "hdcp.h"
#include "hdcp_ddc.h"

#include "hdmitx_reg.h"


#ifdef CONFIG_RTK_HDCP1x_REPEATER
/* RX function, for HDCP repeater */
extern void HdmiRx_save_tx_ksv(struct hdcp_ksvlist_info *tx_ksv);
extern void HdmiRx_set_bstatus(unsigned char byte1, unsigned char byte0);
#endif

static int hdcp_lib_read_aksv(uint8_t *ksv_data);
static int hdcp_lib_initiate_step1(void);
static int hdcp_lib_check_ksv(uint8_t ksv[5]);

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_read_aksv
 *-----------------------------------------------------------------------------
 */
static int hdcp_lib_read_aksv(uint8_t *ksv_data)
{
	if (hdcp.hdcp_enabled == 0)
		return -HDCP_CANCELLED_AUTH;

	*(ksv_data+0) = hdcp.en_ctrl->Aksv[0];
	*(ksv_data+1) = hdcp.en_ctrl->Aksv[1];
	*(ksv_data+2) = hdcp.en_ctrl->Aksv[2];
	*(ksv_data+3) = hdcp.en_ctrl->Aksv[3];
	*(ksv_data+4) = hdcp.en_ctrl->Aksv[4];

	return HDCP_OK;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_check_ksv
 *-----------------------------------------------------------------------------
 */
static int hdcp_lib_check_ksv(uint8_t ksv[5])
{
	int i;
	int j;
	int zero;
	int one;

	zero = 0;
	one = 0;
	for (i = 0; i < 5; i++) {
		/* Count number of zero / one */
		for (j = 0; j < 8; j++) {
			if (ksv[i] & (0x01 << j))
				one++;
			else
				zero++;
		}
	}

	if (one == zero)
		return HDCP_OK;
	else
		return -HDCP_AKSV_ERROR;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_initiate_step1
 *-----------------------------------------------------------------------------
 */
static int hdcp_lib_initiate_step1(void)
{
	/*
	 * HDCP authentication steps:
	 *   1) Read Bksv - check validity (is HDMI Rx supporting HDCP ?)
	 *   2) Initializes HDCP (CP reset release)
	 *   3) Read Bcaps - is HDMI Rx a repeater ?
	 *   *** First part authentication ***
	 *   4) Read Bksv - check validity (is HDMI Rx supporting HDCP ?)
	 *   5) Generates An
	 *   6) DDC: Writes An, Aksv
	 *   7) DDC: Write Bksv
	 */
	int status = HDCP_OK;
	int i;
	uint8_t an_ksv_data[5];
	uint8_t an_bksv_data[5];
	uint8_t rx_type;
	uint8_t genAn[8];

	/* HDCP_DEBUG("[%s] %s  %d :%u\n", __FILE__, __func__, __LINE__, jiffies_to_msecs(jiffies)); */
	/* Generate An */
	status = hdcp_lib_generate_an(genAn);

	if (status != HDCP_OK)
		return status;

	HDCP_DEBUG("AN: %x %x %x %x %x %x %x %x",
		genAn[0], genAn[1], genAn[2], genAn[3],
		genAn[4], genAn[5], genAn[6], genAn[7]);

	status = hdcp_lib_read_aksv(an_ksv_data);
	if (status != HDCP_OK)
		return status;

	HDCP_DEBUG("AKSV: %02x %02x %02x %02x %02x",
		an_ksv_data[0], an_ksv_data[1], an_ksv_data[2],
		an_ksv_data[3], an_ksv_data[4]);

	status = hdcp_lib_check_ksv(an_ksv_data);
	if (status != HDCP_OK) {
		HDCP_ERROR("AKSV error (number of,0 and 1)\n");
		HDCP_ERROR("AKSV: %02x %02x %02x %02x %02x",
			an_ksv_data[0], an_ksv_data[1], an_ksv_data[2],
			an_ksv_data[3], an_ksv_data[4]);
		return status;
	}
	memcpy(ksvlist_info.Aksv, an_ksv_data, sizeof(an_ksv_data));

	/* DDC: Write An */
	if (ddc_write(DDC_AN_LEN, DDC_AN_ADDR, genAn))
		return -DDC_ERROR;

	/* DDC: Write AKSV */
	if (ddc_write(DDC_AKSV_LEN, DDC_AKSV_ADDR, an_ksv_data))
		return -DDC_ERROR;

	/* Read BCAPS to determine if HDCP RX is a repeater */
	if (ddc_read(DDC_BCAPS_LEN, DDC_BCAPS_ADDR, &rx_type))
		return -DDC_ERROR;

	rx_type = FLD_GET(rx_type, DDC_BIT_REPEATER, DDC_BIT_REPEATER);

	/* Set repeater bit in HDCP CTRL */
	if (rx_type == 1) {

		hdcp_lib_set_repeater_bit_in_tx(HDCP_REPEATER);

		HDCP_DEBUG("HDCP RX is a repeater");
	} else {

		hdcp_lib_set_repeater_bit_in_tx(HDCP_RECEIVER);

		HDCP_DEBUG("HDCP RX is a receiver");
	}

	/* DDC: Read BKSV from RX */
	for (i = 0; i < 2; i++) {/* Retry for CTS 1A-05 */
		if (ddc_read(DDC_BKSV_LEN, DDC_BKSV_ADDR, an_bksv_data) && (i == 1)) {
			return -DDC_ERROR;
		} else {
			if (hdcp_lib_check_ksv(an_bksv_data) && (i == 1)) {
				HDCP_ERROR("BKSV: %02x %02x %02x %02x %02x",
					an_bksv_data[0], an_bksv_data[1], an_bksv_data[2],
					an_bksv_data[3], an_bksv_data[4]);
				return -HDCP_AKSV_ERROR;
			}
		}
	}

	memcpy(ksvlist_info.Bksv, an_bksv_data, sizeof(an_bksv_data));

	HDCP_DEBUG("BKSV: %02x %02x %02x %02x %02x",
		an_bksv_data[0], an_bksv_data[1], an_bksv_data[2],
		an_bksv_data[3], an_bksv_data[4]);

	HDCP_DEBUG("PK: %02x %02x %02x %02x %02x",
		hdcp.en_ctrl->PK[0], hdcp.en_ctrl->PK[1], hdcp.en_ctrl->PK[2],
		hdcp.en_ctrl->PK[3], hdcp.en_ctrl->PK[4]);

	/* Authentication 1st step initiated HERE */
	status = hdcp_lib_write_bksv(an_bksv_data);

	return status;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_step1_start
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_step1_start(void)
{
	int status;

	/* HDCP_DEBUG("[%s] %s  %d :%u\n", __FILE__, __func__, __LINE__, jiffies_to_msecs(jiffies)); */

#if 0
	/* Set AV Mute if needed */
	if (hdcp.av_mute_needed)
		hdcp_lib_set_av_mute(AV_MUTE_SET);

	/* Must turn encryption off when AVMUTE */
		hdcp_lib_set_encryption(HDCP_ENC_OFF);
#endif
	status = hdcp_lib_initiate_step1();

	return status;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_r0_check
 *----------------------------------------------------------------------------
 */
int hdcp_lib_r0_check(void)
{
	uint8_t ro_rx[2] = {0, 0};
	uint8_t ro_tx[2] = {0, 0};

	/* DDC: Read Ri' from RX */
	if (ddc_read(DDC_Ri_LEN, DDC_Ri_ADDR, ro_rx))
		return -DDC_ERROR;

	ro_tx[0] = (RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_LIR)>>8)&0xff;
	ro_tx[1] = (RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_LIR)>>16)&0xff;

	/* Compare values */
	if ((ro_rx[0] == ro_tx[0]) && (ro_rx[1] == ro_tx[1])) {
		HDCP_DEBUG("ROTX: %x%x RORX:%x%x\n", ro_tx[0], ro_tx[1], ro_rx[0], ro_rx[1]);
		return HDCP_OK;
	} else {
		HDCP_ERROR("ROTX: %x%x RORX:%x%x\n", ro_tx[0], ro_tx[1], ro_rx[0], ro_rx[1]);
		return -HDCP_AUTH_FAILURE;
	}

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_auto_ri_check
 *-----------------------------------------------------------------------------
 */
void hdcp_lib_auto_ri_check(bool state)
{
	void *irq_dev_id = (void *)&hdcp.hdcp_irq_num;

	if (state == true) {

		hdcp_lib_set_wider_window();

		if (request_irq(hdcp.hdcp_irq_num, HDCP_interrupt_handler, IRQF_SHARED, "rtk_hdcp", irq_dev_id)) {
			HDCP_ERROR("request HDCP irq failed");
		} else {
			HDCP_DEBUG("request HDCP irq %d", hdcp.hdcp_irq_num);

			hdcp_lib_set_ri_interrupt(HDCP_RI_ON);
		}
	} else {
		hdcp_lib_set_ri_interrupt(HDCP_RI_OFF);
	}

	HDCP_DEBUG("[%s] %s  %d :%u ,state=%s\n", __FILE__, __func__, __LINE__,
		jiffies_to_msecs(jiffies), state == true ? "ON" : "OFF");
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_polling_bcaps_rdy_check
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_polling_bcaps_rdy_check(void)
{
	uint8_t ready_bit;
	int i;

	/*
	 * State A8:Wait for Ready.
	 * sets up 5 secs timer and polls the Receiver's READY bit.
	 */
	for (i = 0; i < 50; i++) {
		ready_bit = 0;
		if (ddc_read(DDC_BCAPS_LEN, DDC_BCAPS_ADDR, &ready_bit))
			HDCP_ERROR("I2c error, read Bcaps failed");

		if (FLD_GET(ready_bit, DDC_BIT_READY, DDC_BIT_READY)) {
			HDCP_DEBUG("Bcaps ready bit asserted");
			return HDCP_OK;
		} else {
			usleep_range(100000, 110000);
		}
	}

	return -HDCP_AUTH_FAILURE;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_step1_r0_check
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_step1_r0_check(void)
{
	int status = HDCP_OK;

	/*
	 * HDCP authentication steps:
	 * 1) DDC: Read M0'
	 * 2) Compare M0 and M0'
	 * if Rx is a receiver: switch to authentication step 3
	 * 3) Enable encryption / auto Ri check / disable AV mute
	 * if Rx is a repeater: switch to authentication step 2
	 * 3) Get M0 from HDMI IP and store it for further processing (V)
	 * 4) Enable encryption / auto Ri check / auto BCAPS RDY polling
	 *     Disable AV mute
	 */

	/* HDCP_DEBUG("[%s] %s  %d :%u\n", __FILE__,__FUNCTION__,__LINE__,jiffies_to_msecs(jiffies)); */

	status = hdcp_lib_r0_check();
	if (status < 0)
		return status;

	/* Authentication 1st step done */

	/*
	 * Now prepare 2nd step authentication in case of RX repeater and
	 * enable encryption / Ri check
	 */

	if (!hdcp_lib_check_repeater_bit_in_tx()) {
		/* Receiver: enable encryption and auto Ri check */
		hdcp_lib_set_encryption(HDCP_ENC_ON);

		hdcp_lib_auto_ri_check(true);
	}

	return status;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_dump_sha
 *-----------------------------------------------------------------------------
 */
static void __maybe_unused
hdcp_lib_dump_sha(struct hdcp_sha_in *sha)
{
	int i;

	pr_info("sha.byte_counter= %d\n", sha->byte_counter);

	pr_info("sha.vprime=[ ");
	for (i = 0; i < MAX_SHA_VPRIME_SIZE; i++)
		pr_info("0x%x,", sha->vprime[i]);

	pr_info("]\n");
	pr_info("sha.data=[ ");

	for (i = 0; i < sha->byte_counter; i++)
		pr_info("0x%x,", sha->data[i]);

	pr_info("]\n");
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_verify_V
 *-----------------------------------------------------------------------------
 */
static void __maybe_unused
hdcp_lib_dump_SHA_block(uint8_t *sha_blk)
{
	int i;

	for (i = 0; i < SHA_BLK_SIZE/4; i++)
		HDCP_DEBUG("sha_blk[%2d,%2d,%2d,%2d]= %2x, %2x, %2x, %2x,",
			4*i+0, 4*i+1, 4*i+2, 4*i+3,
			sha_blk[4*i+0], sha_blk[4*i+1], sha_blk[4*i+2], sha_blk[4*i+3]);

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_step2
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_step2(void)
{
	/*
	 * HDCP authentication steps:
	 *   1) Disable auto Ri check
	 *   2) DDC: read BStatus (nb of devices, MAX_DEV
	 */
	uint8_t bstatus[2] = {0};
	int status = HDCP_OK;
	int i;

	HDCP_DEBUG("[%s] %s  %d :%u", __FILE__, __func__, __LINE__, jiffies_to_msecs(jiffies));

	status = hdcp_lib_polling_bcaps_rdy_check();
	if (status != HDCP_OK) {
		HDCP_ERROR("polling Bcaps ready failed\n");
#ifndef CONFIG_RTK_HDCP1x_REPEATER
		return status;
#endif
	}

	/* DDC: Read Bstatus (1st byte) from Rx */
	if (ddc_read(DDC_BSTATUS_LEN, DDC_BSTATUS_ADDR, bstatus))
		return -DDC_ERROR;

	HDCP_DEBUG("bstatus=0x%x,0x%x", bstatus[0], bstatus[1]);

#ifdef CONFIG_RTK_HDCP1x_REPEATER
		HdmiRx_set_bstatus(bstatus[1], bstatus[0]);

		if (status != HDCP_OK)
			return status;
#endif

	/* Check BStatus topology errors */
	if (bstatus[0] & DDC_BSTATUS0_MAX_DEVS) {
		HDCP_ERROR("MAX_DEV_EXCEEDED set");
		return -HDCP_AUTH_FAILURE;
	}

	if (bstatus[1] & DDC_BSTATUS1_MAX_CASC) {
		HDCP_ERROR("MAX_CASCADE_EXCEEDED set");
		return -HDCP_AUTH_FAILURE;
	}

	HDCP_DEBUG("Retrieving KSV list...");
	/* Get KSV list size */
	sha_input.byte_counter = (bstatus[0] & DDC_BSTATUS0_DEV_COUNT) * 5;

	/* Clear all SHA input data */
	/* TODO: should be done earlier at HDCP init */
	memset(sha_input.data, 0, MAX_SHA_DATA_SIZE);

	/* DDC: read KSV list */
	if (sha_input.byte_counter) {
		if (ddc_read(sha_input.byte_counter, DDC_KSV_FIFO_ADDR, (uint8_t *)&sha_input.data)) {
			return -DDC_ERROR;
		} else {
			ksvlist_info.device_count = (bstatus[0] & DDC_BSTATUS0_DEV_COUNT);
			memcpy(ksvlist_info.ksvlist, sha_input.data, sizeof(ksvlist_info.ksvlist));
			memcpy(ksvlist_info.bstatus, bstatus, sizeof(ksvlist_info.bstatus));
#ifdef CONFIG_RTK_HDCP1x_REPEATER
			/* Send KSV list to RX immediately for Repeater CTS 3C-II */
			HdmiRx_save_tx_ksv(&ksvlist_info);
#endif
		}
	}

	/* Read and add Bstatus */
	hdcp_lib_SHA_append_bstatus_M0(&sha_input, bstatus);

	/* Read V' */
	for (i = 0; i < 5; i++) {
		if (ddc_read(DDC_V_LEN, DDC_V_ADDR+DDC_V_LEN*i, sha_input.vprime+DDC_V_LEN*i))
			return -DDC_ERROR;

		HDCP_DEBUG("sha_input.vprime[%d]=%x,%x,%x,%x\n", DDC_V_LEN*i,
			sha_input.vprime[DDC_V_LEN*i+0], sha_input.vprime[DDC_V_LEN*i+1],
			sha_input.vprime[DDC_V_LEN*i+2], sha_input.vprime[DDC_V_LEN*i+3]);
	}
	/* hdcp_lib_dump_sha(&sha_input); */

	status = hdcp_lib_compute_V(&sha_input);
	if (status != HDCP_OK)
		goto sha_err;

	status = hdcp_lib_verify_V(&sha_input);

	if (status == HDCP_OK) {
		/* Re-enable Ri check */
		/* Receiver: enable encryption and auto Ri check */
		hdcp_lib_set_encryption(HDCP_ENC_ON);

		hdcp_lib_auto_ri_check(true);

#ifdef CONFIG_RTK_HDCP1x_REPEATER
		HdmiRx_save_tx_ksv(&ksvlist_info);
#endif
	}

sha_err:
	return status;
}

int hdcp_lib_query_sink_hdcp_capable(void)
{
	uint8_t an_bksv_data[5];
	int i;
	int retry = 6;

	/* HDCP CTS 1A-04: Continue to read the HDCP port for 9 seconds */
	for (i = 0; i < retry; i++) {
		if (ddc_read(DDC_BKSV_LEN, DDC_BKSV_ADDR, an_bksv_data)) {
			HDCP_ERROR("Read BKSV error %d time(s)", i);
		} else {

			if (hdcp_lib_check_ksv(an_bksv_data))
				HDCP_ERROR("Check BKSV error(%d)", i);
			else
				return 0;
		}
		msleep(1500);
	}

	return -HDCP_AKSV_ERROR;
}

void hdcp_lib_dump_22_cipher_setting(void)
{
	HDCP_DEBUG("HDCP_2_2_HW_RIV_1=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_RIV_1));
	HDCP_DEBUG("HDCP_2_2_HW_RIV_2=0x08%x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_RIV_2));

	HDCP_DEBUG("HDCP_2_2_SW_KEY_1_1=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_1));
	HDCP_DEBUG("HDCP_2_2_SW_KEY_1_2=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_2));
	HDCP_DEBUG("HDCP_2_2_SW_KEY_1_3=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_3));
	HDCP_DEBUG("HDCP_2_2_SW_KEY_1_4=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_4));

	HDCP_DEBUG("HDCP_2_2_HW_FRAME_NUM_1=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_1));
	HDCP_DEBUG("HDCP_2_2_HW_FRAME_NUM_2=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_2));

	HDCP_DEBUG("HDCP_2_2_HW_FRAME_NUM_ADD_1=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_ADD_1));
	HDCP_DEBUG("HDCP_2_2_HW_FRAME_NUM_ADD_2=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_ADD_2));

	HDCP_DEBUG("HDCP_2_2_HW_DATA_NUM=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_DATA_NUM));

	HDCP_DEBUG("HDCP_2_2_HW_DATA_NUM_ADD=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_DATA_NUM_ADD));

	HDCP_DEBUG("HDCP_2_2_CTRL=0x%08x",
		RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_CTRL));

}

void hdcp_lib_set_1x_state_machine_for_22_cipher(void)
{
	/* set HDCP 1.4 state machine */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en1(1)|HDMI_HDCP_AUTH_authrequest(1));
	udelay(1);
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en2(1)|HDMI_HDCP_AUTH_authcompute(1));
	udelay(1);
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en4(1)|HDMI_HDCP_AUTH_deviceauthenticated(1));

}

void hdcp_lib_set_22_cipher(struct HDCP_22_CIPHER_INFO *arg)
{
	if (arg->hdcp_22_en == 1)
		hdcp_lib_set_1x_state_machine_for_22_cipher();

	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_CTRL,
		HDMI_HDCP_2_2_CTRL_write_en4(1)|HDMI_HDCP_2_2_CTRL_hdcp_2_2_en(arg->hdcp_22_en));

	/* riv           : hw_riv_1_(1-2) */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_RIV_1,
		arg->riv[0]|(arg->riv[1]<<8)|(arg->riv[2]<<16)|(arg->riv[3]<<24));
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_RIV_2,
		arg->riv[4]|(arg->riv[5]<<8)|(arg->riv[6]<<16)|(arg->riv[7]<<24));

	/* ks_xor_lc128  : sw_key_1_(1-4) */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_1,
		(arg->ks_xor_lc128[0])|
		(arg->ks_xor_lc128[1]<<8)|
		(arg->ks_xor_lc128[2]<<16)|
		(arg->ks_xor_lc128[3]<<24));
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_2,
		(arg->ks_xor_lc128[4])|
		(arg->ks_xor_lc128[5]<<8)|
		(arg->ks_xor_lc128[6]<<16)|
		(arg->ks_xor_lc128[7]<<24));
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_3,
		(arg->ks_xor_lc128[8])|
		(arg->ks_xor_lc128[9]<<8)|
		(arg->ks_xor_lc128[10]<<16)|
		(arg->ks_xor_lc128[11]<<24));
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_SW_KEY_1_4,
		(arg->ks_xor_lc128[12])|
		(arg->ks_xor_lc128[13]<<8)|
		(arg->ks_xor_lc128[14]<<16)|
		(arg->ks_xor_lc128[15]<<24));

	/* frame_num     : frame_num_(1-2) */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_1, (u32)arg->frame_num);
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_2, (u32)(arg->frame_num>>32));

	/* frame_num_add : frame_num_add_(1-2)	*/
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_ADD_1, (u32)arg->frame_num_add);

	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_FRAME_NUM_ADD_2, (u32)(arg->frame_num_add>>32));

	/* data_num      : data_num */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_DATA_NUM, arg->data_num);

	/* data_num_add  : data_num_add */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_HW_DATA_NUM_ADD, arg->data_num_add);

	/* aes_sw_en     : hdcp_22_ctrl:aes_sw_en */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_CTRL,
		HDMI_HDCP_2_2_CTRL_write_en3(1)|HDMI_HDCP_2_2_CTRL_aes_sw_en(1));/* always set to SW mode first */

	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_2_2_CTRL,
		HDMI_HDCP_2_2_CTRL_write_en3(1)|HDMI_HDCP_2_2_CTRL_aes_sw_en(arg->aes_sw_en));

	/* hdcp_lib_dump_22_cipher_setting(); */

}

void hdcp_lib_control_22_cipher(int control_flag)
{
	if (control_flag == HDCP_22_CIPHER_RESUME) {
		/* Enable HDCP22 encrypt */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
			HDMI_HDCP_CR_write_en4(1)|HDMI_HDCP_CR_en1_1_feature(1)|
			HDMI_HDCP_CR_write_en1(1)|HDMI_HDCP_CR_hdcp_encryptenable(1));
		HDCP_INFO("Enable 22 enc");
	} else {
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
			HDMI_HDCP_CR_write_en1(1)|HDMI_HDCP_CR_hdcp_encryptenable(0));
		HDCP_INFO("Disable 22 enc");
	}

}
