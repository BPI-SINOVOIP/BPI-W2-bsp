/*
 * hdcp_lib_hw.c - RTK hdcp tx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>

#include "hdcp_top.h"
#include "hdcp.h"
#include "hdcp_ddc.h"
#include "hdmitx_reg.h"

static void hdcp_lib_read_an(uint8_t *an);
static int hdcp_lib_generateKm(uint8_t *Bksv);

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_check_repeater_bit_in_tx
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_check_repeater_bit_in_tx(void)
{
	int ret_value;

	ret_value = HDMI_HDCP_CR_get_downstrisrepeater(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR));

	return ret_value;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_read_an
 *-----------------------------------------------------------------------------
 */
static void hdcp_lib_read_an(uint8_t *an)
{
	unsigned int temp;

	/*
	 * Convert HDCP An from bit endien to little endien
	 * HDCP An should stored in little endien,	but HDCP HW store in big endien
	 */

	temp = RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_ANLR);/* HDCP_ANLR => An LSB */

	an[0] = temp & 0x0ff;
	an[1] = (temp >> 8) & 0xff;
	an[2] = (temp >> 16) & 0xff;
	an[3] = (temp >> 24) & 0xff;

	temp = RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_ANMR);/* HDCP_ANMR => An MSB */

	an[4] = temp & 0x0ff;
	an[5] = (temp >> 8) & 0xff;
	an[6] = (temp >> 16) & 0xff;
	an[7] = (temp >> 24) & 0xff;

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_generate_an (Generate An using HDCP HW)
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_generate_an(uint8_t *an)
{
	int retry = 0;

	/* Get An */
	/* get An influence from CRC64 */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en9(0) |
		HDMI_HDCP_AUTH_ddpken(0) |
		HDMI_HDCP_AUTH_write_en8(0) |
		HDMI_HDCP_AUTH_resetkmacc(0) |
		HDMI_HDCP_AUTH_write_en7(0) |
		HDMI_HDCP_AUTH_update_an(0) |
		HDMI_HDCP_AUTH_write_en6(1) |
		HDMI_HDCP_AUTH_aninfreq(1) |
		HDMI_HDCP_AUTH_write_en5(0) |
		HDMI_HDCP_AUTH_seedload(0) |
		HDMI_HDCP_AUTH_write_en4(0) |
		HDMI_HDCP_AUTH_deviceauthenticated(0) |
		HDMI_HDCP_AUTH_write_en3(0) |
		HDMI_HDCP_AUTH_forcetounauthenticated(0) |
		HDMI_HDCP_AUTH_write_en2(0) |
		HDMI_HDCP_AUTH_authcompute(0) |
		HDMI_HDCP_AUTH_write_en1(0) |
		HDMI_HDCP_AUTH_authrequest(0));

	/* set An Influence Mode, influence will be load from AnIR0, AnIR1 */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
		HDMI_HDCP_CR_write_en4(1) |
		HDMI_HDCP_CR_en1_1_feature(1) |
		HDMI_HDCP_CR_write_en3(0) |
		HDMI_HDCP_CR_downstrisrepeater(0) |
		HDMI_HDCP_CR_write_en2(1) |
		HDMI_HDCP_CR_aninfluencemode(1) |
		HDMI_HDCP_CR_write_en1(0) |
		HDMI_HDCP_CR_hdcp_encryptenable(0));

	/* trigger to get An */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en9(0) |
		HDMI_HDCP_AUTH_ddpken(0) |
		HDMI_HDCP_AUTH_write_en8(0) |
		HDMI_HDCP_AUTH_resetkmacc(0) |
		HDMI_HDCP_AUTH_write_en7(0) |
		HDMI_HDCP_AUTH_update_an(0) |
		HDMI_HDCP_AUTH_write_en6(0) |
		HDMI_HDCP_AUTH_aninfreq(0) |
		HDMI_HDCP_AUTH_write_en5(0) |
		HDMI_HDCP_AUTH_seedload(0) |
		HDMI_HDCP_AUTH_write_en4(0) |
		HDMI_HDCP_AUTH_deviceauthenticated(0) |
		HDMI_HDCP_AUTH_write_en3(0) |
		HDMI_HDCP_AUTH_forcetounauthenticated(0) |
		HDMI_HDCP_AUTH_write_en2(0) |
		HDMI_HDCP_AUTH_authcompute(0) |
		HDMI_HDCP_AUTH_write_en1(1) |
		HDMI_HDCP_AUTH_authrequest(1));

	/* check if An is ready */
	while (!HDMI_HDCP_SR_get_anready(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SR))) {
		mdelay(100);

		if (retry >= 5)
			return -HDCP_AUTH_FAILURE;

		retry++;
	}

	/*
	 * Leave An influence mode
	 * Set use internal rander bit generator
	 */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
		HDMI_HDCP_CR_write_en4(1) |
		HDMI_HDCP_CR_en1_1_feature(1) |
		HDMI_HDCP_CR_write_en3(0) |
		HDMI_HDCP_CR_downstrisrepeater(0) |
		HDMI_HDCP_CR_write_en2(1) |
		HDMI_HDCP_CR_aninfluencemode(0) |
		HDMI_HDCP_CR_write_en1(0) |
		HDMI_HDCP_CR_hdcp_encryptenable(0));

	hdcp_lib_read_an(an);

	HDCP_DEBUG("AN1: %x %x %x %x %x %x %x %x",
		an[0], an[1], an[2], an[3], an[4], an[5], an[6], an[7]);

	return HDCP_OK;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_set_repeater_bit_in_tx
 *-----------------------------------------------------------------------------
 */
void hdcp_lib_set_repeater_bit_in_tx(enum hdcp_repeater rx_mode)
{
	HDCP_DEBUG("hdcp_lib_set_repeater_bit_in_tx() value=%d", rx_mode);

	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
		HDMI_HDCP_CR_write_en4(1) |
		HDMI_HDCP_CR_en1_1_feature(1) |
		HDMI_HDCP_CR_write_en3(1) |
		HDMI_HDCP_CR_downstrisrepeater(rx_mode) |
		HDMI_HDCP_CR_write_en2(0) |
		HDMI_HDCP_CR_aninfluencemode(0) |
		HDMI_HDCP_CR_write_en1(0) |
		HDMI_HDCP_CR_hdcp_encryptenable(0));
}

void hdcp_lib_set_wider_window(void)
{
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_OWR,
		HDMI_HDCP_OWR_write_en2(1) | HDMI_HDCP_OWR_hdcpoppwinend(526) |
		HDMI_HDCP_OWR_write_en1(1) | HDMI_HDCP_OWR_hdcpoppwinstart(510));
}

void hdcp_lib_set_ri_interrupt(enum ri_state state)
{
	if (state == HDCP_RI_ON) {
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_INTEN,
			HDMI_INTEN_enriupdint(1) |
			HDMI_INTEN_enpjupdint(0) |
			HDMI_INTEN_write_data(1));
	} else {
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_INTEN,
			HDMI_INTEN_enriupdint(0) |
			HDMI_INTEN_enpjupdint(0) |
			HDMI_INTEN_write_data(1));
	}
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_set_encryption
 *-----------------------------------------------------------------------------
 */
void hdcp_lib_set_encryption(enum encryption_state enc_state)
{
	int rx_mode;

	rx_mode = hdcp_lib_check_repeater_bit_in_tx();

	if (enc_state == HDCP_ENC_ON) {
		/* set HDCP module to authenticated state */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
			HDMI_HDCP_AUTH_write_en9(0) | HDMI_HDCP_AUTH_ddpken(0) |
			HDMI_HDCP_AUTH_write_en8(0) | HDMI_HDCP_AUTH_resetkmacc(0) |
			HDMI_HDCP_AUTH_write_en7(0) | HDMI_HDCP_AUTH_update_an(0) |
			HDMI_HDCP_AUTH_write_en6(0) | HDMI_HDCP_AUTH_aninfreq(0) |
			HDMI_HDCP_AUTH_write_en5(0) | HDMI_HDCP_AUTH_seedload(0) |
			HDMI_HDCP_AUTH_write_en4(1) | HDMI_HDCP_AUTH_deviceauthenticated(1) |
			HDMI_HDCP_AUTH_write_en3(0) | HDMI_HDCP_AUTH_forcetounauthenticated(0) |
			HDMI_HDCP_AUTH_write_en2(0) | HDMI_HDCP_AUTH_authcompute(0) |
			HDMI_HDCP_AUTH_write_en1(0) | HDMI_HDCP_AUTH_authrequest(0));

		/* start encryption */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
			HDMI_HDCP_CR_write_en4(1) | HDMI_HDCP_CR_en1_1_feature(1) |
			HDMI_HDCP_CR_write_en3(0) | HDMI_HDCP_CR_downstrisrepeater(rx_mode) |
			HDMI_HDCP_CR_write_en2(0) | HDMI_HDCP_CR_aninfluencemode(0) |
			HDMI_HDCP_CR_write_en1(1) | HDMI_HDCP_CR_hdcp_encryptenable(1));

	} else if (enc_state == HDCP_ENC_OFF) {

		/* disable link integry check */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_INTEN,
			HDMI_INTEN_enriupdint(1) |
			HDMI_INTEN_enpjupdint(1) |
			HDMI_INTEN_write_data(0));

		/* force Encryption disable */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
			HDMI_HDCP_CR_write_en4(1) | HDMI_HDCP_CR_en1_1_feature(1) |
			HDMI_HDCP_CR_write_en3(0) | HDMI_HDCP_CR_downstrisrepeater(rx_mode) |
			HDMI_HDCP_CR_write_en2(0) | HDMI_HDCP_CR_aninfluencemode(0) |
			HDMI_HDCP_CR_write_en1(1) | HDMI_HDCP_CR_hdcp_encryptenable(0));

		/* force HDCP module to unauthenticated state */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
			HDMI_HDCP_AUTH_write_en9(0) | HDMI_HDCP_AUTH_ddpken(0) |
			HDMI_HDCP_AUTH_write_en8(0) | HDMI_HDCP_AUTH_resetkmacc(0) |
			HDMI_HDCP_AUTH_write_en7(0) | HDMI_HDCP_AUTH_update_an(0) |
			HDMI_HDCP_AUTH_write_en6(0) | HDMI_HDCP_AUTH_aninfreq(0) |
			HDMI_HDCP_AUTH_write_en5(0) | HDMI_HDCP_AUTH_seedload(0) |
			HDMI_HDCP_AUTH_write_en4(0) | HDMI_HDCP_AUTH_deviceauthenticated(0) |
			HDMI_HDCP_AUTH_write_en3(1) | HDMI_HDCP_AUTH_forcetounauthenticated(1) |
			HDMI_HDCP_AUTH_write_en2(0) | HDMI_HDCP_AUTH_authcompute(0) |
			HDMI_HDCP_AUTH_write_en1(0) | HDMI_HDCP_AUTH_authrequest(0));

	} else {
		HDCP_ERROR("unknown ENC state");
	}

	if (hdcp.print_messages)
		HDCP_DEBUG("Encryption state changed: %s HDCP_AUTH_reg: %02x",
			enc_state == HDCP_ENC_OFF ? "OFF" : "ON",
			RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH));

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_SHA_append_bstatus_M0
 *-----------------------------------------------------------------------------
 */
void hdcp_lib_SHA_append_bstatus_M0(struct hdcp_sha_in *sha, uint8_t *data)
{
	uint32_t MILSW;
	uint32_t MIMSW;

	sha->data[sha->byte_counter++] = data[0];
	sha->data[sha->byte_counter++] = data[1];

	MILSW = RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_MILSW);
	MIMSW = RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_MIMSW);

	memcpy((void *)&sha->data[sha->byte_counter], &MILSW, sizeof(MILSW));
	sha->byte_counter += sizeof(MILSW);
	memcpy((void *)&sha->data[sha->byte_counter], &MIMSW, sizeof(MIMSW));
	sha->byte_counter += sizeof(MIMSW);

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_compute_V
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_compute_V(struct hdcp_sha_in *sha)
{
	int blk_num = 0;
	uint8_t sha_blk[64];
	uint32_t sha_wd;
	int i, j, retry = 0;
	int sha_no_padding_len = (sha->byte_counter/32);
	int sha_data_len_in_bit = sha->byte_counter*8;

	/* calculate SHA data(w/o padding) length in byte */
	if (sha->byte_counter & (32-1))
		sha_no_padding_len++;

	/* padding */
	sha->data[sha->byte_counter++] = 0x80;
	sha->data[sha->byte_counter++] = 0x0;

	/* total length= Ksv list + Bstatus + M0 + padding*2 + SHA data len(bytes)	*/
	blk_num = (sha->byte_counter + sha_no_padding_len)/SHA_BLK_SIZE;
	if ((sha->byte_counter + sha_no_padding_len) & (SHA_BLK_SIZE-1))
		blk_num++;

	for (j = 0; j < blk_num; j++) {
		memset(sha_blk, 0, SHA_BLK_SIZE);
		memcpy(sha_blk, (void *)&sha->data[SHA_BLK_SIZE*j], SHA_BLK_SIZE);

		/*fill data length(bits) of the last blk */
		if (j == (blk_num-1)) {
			for (i = 0; i < sha_no_padding_len; i++) {
				sha_blk[SHA_BLK_SIZE-1-i] = sha_data_len_in_bit % 256;
				sha_data_len_in_bit /= 256;
			}
		}

		/* hdcp_lib_dump_SHA_block(sha_blk); */

		/* reset pointer */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHACR,
			HDMI_HDCP_SHACR_shastart(0) | HDMI_HDCP_SHACR_shafirst(0) |
			HDMI_HDCP_SHACR_rstshaptr(1) | HDMI_HDCP_SHACR_write_data(1));

		/* 16 = SHA_BLK_SIZE/word */
		for (i = 0; i < 16; i++) {
			sha_wd = (sha_blk[4*i+0]<<24) | (sha_blk[4*i+1]<<16) |
				(sha_blk[4*i+2]<<8) | (sha_blk[4*i+3]<<0);/* change endian */

			HDCP_DEBUG("sha_blk[%2d,%2d,%2d,%2d]= %2x %2x %2x %2x, sha_wd=%x\n",
				4*i+0, 4*i+1, 4*i+2, 4*i+3,
				sha_blk[4*i+0], sha_blk[4*i+1], sha_blk[4*i+2], sha_blk[4*i+3],
				sha_wd);
			WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHADR, HDMI_HDCP_SHADR_sha_data(sha_wd));/* push first 512bits data */
		}

		if (j == 0) {
			WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHACR,
				HDMI_HDCP_SHACR_shastart(1) | HDMI_HDCP_SHACR_shafirst(1) |
				HDMI_HDCP_SHACR_rstshaptr(0) | HDMI_HDCP_SHACR_write_data(1));/* set first and start */
		} else {
			WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHACR,
				HDMI_HDCP_SHACR_shastart(0) | HDMI_HDCP_SHACR_shafirst(1) |
				HDMI_HDCP_SHACR_rstshaptr(0) | HDMI_HDCP_SHACR_write_data(0));/* reset first bit */

			WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHACR,
				HDMI_HDCP_SHACR_shastart(1) | HDMI_HDCP_SHACR_shafirst(0) |
				HDMI_HDCP_SHACR_rstshaptr(0) | HDMI_HDCP_SHACR_write_data(1));/*set start */
		}
	}

	/* wait for ready */
	while (!HDMI_HDCP_SHARR_get_shaready(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHARR))) {
		mdelay(100);
		if (retry >= 20) {
			HDCP_ERROR("2rd step authentication : compute V failed\n");
			return -HDCP_SHA1_ERROR;
		}
		retry++;
	}

	HDCP_INFO("2rd step authentication : compute V is done\n");

	return HDCP_OK;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_verify_V
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_verify_V(struct hdcp_sha_in *sha)
{
	int i;
	int retry;
	uint32_t data;

	retry = 0;
	for (i = 0; i < SHA1_HASH_SIZE; i++) {
		memcpy(&data, (void *)&sha->vprime[DDC_V_LEN*i], sizeof(data));
		HDCP_DEBUG("2rd step authentication : v data=%x", data);
		/* should not swap */
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHADR, HDMI_HDCP_SHADR_sha_data(data));
	}

	/* wait for ready */
	while (!HDMI_HDCP_SHARR_get_shaready(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHARR))) {

		mdelay(100);
		if (retry >= 30) {
			HDCP_ERROR("2rd step authentication : timeout of shaready;verify V failed\n");
			return -HDCP_SHA1_ERROR;
		}
		retry++;
	}

	if (HDMI_HDCP_SHARR_get_vmatch(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SHARR))) {
		HDCP_INFO("2rd step authentication : verify V passed");
		return HDCP_OK;
	} else {
		HDCP_ERROR("2rd step authentication : verify V failed");
		return -HDCP_SHA1_ERROR;
	}

}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_generateKm
 *-----------------------------------------------------------------------------
 */
static int hdcp_lib_generateKm(uint8_t *Bksv)
{
	int i, j;
	int key0 = 0, key1 = 0;
	unsigned char DK1, DK2, DK3, DK4, DK5, DK6, DK7;
	int retry = 0;

	if (hdcp.hdcp_enabled == 0)
		return -HDCP_CANCELLED_AUTH;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 8; j++) {
			if (Bksv[i] & (1<<j)) {

				DK1 = hdcp.en_ctrl->PK[i*56+j*7];
				DK2 = hdcp.en_ctrl->PK[i*56+j*7+1];
				DK3 = hdcp.en_ctrl->PK[i*56+j*7+2];
				DK4 = hdcp.en_ctrl->PK[i*56+j*7+3];
				DK5 = hdcp.en_ctrl->PK[i*56+j*7+4];
				DK6 = hdcp.en_ctrl->PK[i*56+j*7+5];
				DK7 = hdcp.en_ctrl->PK[i*56+j*7+6];
				key1 = DK7&0x0ff;
				key1 = (key1<<8)|DK6;
				key1 = (key1<<8)|DK5;
				key1 = (key1<<8)|DK4;
				key0 = DK3&0x0ff;
				key0 = (key0<<8)|DK2;
				key0 = (key0<<8)|DK1;

				/* write to HW */
				WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_DPKLR,
					HDMI_HDCP_DPKLR_ddpklsb24(key0) |
					HDMI_HDCP_DPKLR_dpkencpnt(0x55));
				WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_DPKMR,
					HDMI_HDCP_DPKMR_ddpkmsw(key1));

				/* trigger accumulation */
				WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
					HDMI_HDCP_AUTH_write_en9(1) |
					HDMI_HDCP_AUTH_ddpken(1) |
					HDMI_HDCP_AUTH_write_en8(0) |
					HDMI_HDCP_AUTH_resetkmacc(0) |
					HDMI_HDCP_AUTH_write_en7(0) |
					HDMI_HDCP_AUTH_update_an(0) |
					HDMI_HDCP_AUTH_write_en6(0) |
					HDMI_HDCP_AUTH_aninfreq(0) |
					HDMI_HDCP_AUTH_write_en5(0) |
					HDMI_HDCP_AUTH_seedload(0) |
					HDMI_HDCP_AUTH_write_en4(0) |
					HDMI_HDCP_AUTH_deviceauthenticated(0) |
					HDMI_HDCP_AUTH_write_en3(0) |
					HDMI_HDCP_AUTH_forcetounauthenticated(0) |
					HDMI_HDCP_AUTH_write_en2(0) |
					HDMI_HDCP_AUTH_authcompute(0) |
					HDMI_HDCP_AUTH_write_en1(0) |
					HDMI_HDCP_AUTH_authrequest(0));

				/* wait HW accumulation */
				while (!HDMI_HDCP_SR_get_curdpkaccdone(RD_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_SR)))
					retry++;

			}
		}
	}

	return HDCP_OK;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_write_bksv
 *-----------------------------------------------------------------------------
 */
int hdcp_lib_write_bksv(uint8_t *ksv_data)
{
	int status = HDCP_OK;

	/* force Encryption disable */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_CR,
		HDMI_HDCP_CR_write_en4(1) |
		HDMI_HDCP_CR_en1_1_feature(1) |
		HDMI_HDCP_CR_write_en3(0) |
		HDMI_HDCP_CR_downstrisrepeater(0) |
		HDMI_HDCP_CR_write_en2(0) |
		HDMI_HDCP_CR_aninfluencemode(0) |
		HDMI_HDCP_CR_write_en1(1) |
		HDMI_HDCP_CR_hdcp_encryptenable(0));

	/* reset Km accumulation */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en9(0) |
		HDMI_HDCP_AUTH_ddpken(0) |
		HDMI_HDCP_AUTH_write_en8(1) |
		HDMI_HDCP_AUTH_resetkmacc(1) |
		HDMI_HDCP_AUTH_write_en7(0) |
		HDMI_HDCP_AUTH_update_an(0) |
		HDMI_HDCP_AUTH_write_en6(0) |
		HDMI_HDCP_AUTH_aninfreq(0) |
		HDMI_HDCP_AUTH_write_en5(0) |
		HDMI_HDCP_AUTH_seedload(0) |
		HDMI_HDCP_AUTH_write_en4(0) |
		HDMI_HDCP_AUTH_deviceauthenticated(0) |
		HDMI_HDCP_AUTH_write_en3(0) |
		HDMI_HDCP_AUTH_forcetounauthenticated(0) |
		HDMI_HDCP_AUTH_write_en2(0) |
		HDMI_HDCP_AUTH_authcompute(0) |
		HDMI_HDCP_AUTH_write_en1(0) |
		HDMI_HDCP_AUTH_authrequest(0));

	status = hdcp_lib_generateKm(ksv_data);
	if (status != HDCP_OK)
		return status;

	/* disable Ri update interrupt */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_INTEN,
		HDMI_INTEN_enriupdint(1) |
		HDMI_INTEN_enpjupdint(0) |
		HDMI_INTEN_write_data(0));

	/* clear Ri updated pending bit */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_INTST,
		HDMI_INTST_riupdated(0) | HDMI_INTST_pjupdated(0));

	/* trigger hdcpBlockCipher at authentication */
	WR_REG_32(hdcp.hdcp_base_addr, HDMI_HDCP_AUTH,
		HDMI_HDCP_AUTH_write_en9(0) |
		HDMI_HDCP_AUTH_ddpken(0) |
		HDMI_HDCP_AUTH_write_en8(0) |
		HDMI_HDCP_AUTH_resetkmacc(0) |
		HDMI_HDCP_AUTH_write_en7(0) |
		HDMI_HDCP_AUTH_update_an(0) |
		HDMI_HDCP_AUTH_write_en6(0) |
		HDMI_HDCP_AUTH_aninfreq(0) |
		HDMI_HDCP_AUTH_write_en5(0) |
		HDMI_HDCP_AUTH_seedload(0) |
		HDMI_HDCP_AUTH_write_en4(0) |
		HDMI_HDCP_AUTH_deviceauthenticated(0) |
		HDMI_HDCP_AUTH_write_en3(0) |
		HDMI_HDCP_AUTH_forcetounauthenticated(0) |
		HDMI_HDCP_AUTH_write_en2(1) |
		HDMI_HDCP_AUTH_authcompute(1) |
		HDMI_HDCP_AUTH_write_en1(0) |
		HDMI_HDCP_AUTH_authrequest(0));

	return status;
}

/*-----------------------------------------------------------------------------
 * Function: hdcp_lib_set_av_mute
 *-----------------------------------------------------------------------------
 */
void hdcp_lib_set_av_mute(enum av_mute av_mute_state)
{
	/* spin_lock_irqsave(&hdcp.spinlock, flags); */

	if (av_mute_state == AV_MUTE_SET) {
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_GCPCR,
			HDMI_GCPCR_enablegcp(1) | HDMI_GCPCR_gcp_clearavmute(1) |
			HDMI_GCPCR_gcp_setavmute(1) | HDMI_GCPCR_write_data(0));

		WR_REG_32(hdcp.hdcp_base_addr, HDMI_GCPCR,
			HDMI_GCPCR_enablegcp(1) | HDMI_GCPCR_gcp_clearavmute(0) |
			HDMI_GCPCR_gcp_setavmute(1) | HDMI_GCPCR_write_data(1));
	} else if (av_mute_state == AV_MUTE_CLEAR) {
		WR_REG_32(hdcp.hdcp_base_addr, HDMI_GCPCR,
			HDMI_GCPCR_enablegcp(1) | HDMI_GCPCR_gcp_clearavmute(1) |
			HDMI_GCPCR_gcp_setavmute(1) | HDMI_GCPCR_write_data(0));

			WR_REG_32(hdcp.hdcp_base_addr, HDMI_GCPCR,
				HDMI_GCPCR_enablegcp(1) | HDMI_GCPCR_gcp_clearavmute(1) |
				HDMI_GCPCR_gcp_setavmute(0) | HDMI_GCPCR_write_data(1));
	} else {
			HDCP_ERROR("unknown av mute parameter\n");
	}
	/* spin_unlock_irqrestore(&hdcp.spinlock, flags); */

}

