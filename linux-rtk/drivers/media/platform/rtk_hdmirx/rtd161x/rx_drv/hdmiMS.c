/*
 * hdmiMS.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "hdmiInternal.h"

/*=================== extern Variable/Function ===================*/
#if HDMI2p0
extern u_int8_t   bHDMI_420_Space;/* For YUV420 */
#endif
extern HDMI_CONST VIDEO_DPLL_RATIO_T dpll_ratio[];

extern unsigned int hdmirx_wrapper_get_active_pixel(void);
extern unsigned int hdmirx_wrapper_get_active_line(void);
/*======================================================*/


#if HDMI_INTERNAL_DEBUG/* RD test */
int Hdmi_CRC_check(void)
{
	UINT8 tmo = 50;
	unsigned int crc_result;
	static unsigned int pre_crc_result = 0;

	/* Disable CRC check */
	hdmi_rx_reg_mask32(TMDS_CRCC, ~TMDS_CRCC_crcc_mask, 0, HDMI_RX_MAC);
	/* Enable CRC check */
	hdmi_rx_reg_mask32(TMDS_CRCC, ~TMDS_CRCC_crcc_mask, TMDS_CRCC_crcc(1), HDMI_RX_MAC);

	/* Wait CRC done bit */
	while (!(hdmi_rx_reg_read32(TMDS_CRCC, HDMI_RX_MAC)&TMDS_CRCC_crc_done_mask)) {
		usleep_range(10000, 15000);/* 10~15ms */
		if (!tmo--) {
			/* HDMI_PRINTF("[HDMI] WARNING: FAIL: Wait CRC Timeout !!!\n"); */
			HDMIRX_INFO("CRC check timeout");
			return FALSE;
		}
	}

	crc_result = hdmi_rx_reg_read32(TMDS_CRCO0, HDMI_RX_MAC);

	if (crc_result != pre_crc_result) {
		pre_crc_result = crc_result;
		HDMIRX_INFO("CRC result changed (0x%08x)", crc_result);
	}

	return TRUE;
}
#endif

unsigned char Hdmi_WaitVsync(int num)
{
	int i;

	hdmi_rx_reg_mask32(HDMI_TMDS_CTRL, ~TMDS_CTRL_yo_mask, TMDS_CTRL_yo(1), HDMI_RX_MAC);

	for (i = 0; i < num; i++) {
		/* Wait vsync done */
		if (TMDS_CTRL_get_yo(hdmi_rx_reg_read32(HDMI_TMDS_CTRL, HDMI_RX_MAC)))
			return 1;

		usleep_range(10000, 15000);/* 10~15ms */
	}

	HDMI_PRINTF("Wait vsync timeout\n");
	return 0;
}

unsigned int Hdmi_GetVSyncCountInit(void)
{
	hdmi_rx.vs_cnt = 0;

	return hdmi.vsync_cnt;
}
unsigned int Hdmi_GetVSyncCount(void)
{
	if (TMDS_CTRL_get_yo(hdmi_rx_reg_read32(HDMI_TMDS_CTRL, HDMI_RX_MAC))) {
		hdmi_rx_reg_mask32(HDMI_TMDS_CTRL, ~HDMI_TMDS_CTRL_yo_mask, HDMI_TMDS_CTRL_yo(1), HDMI_RX_MAC);
		hdmi.vsync_cnt++;
	}

	return hdmi.vsync_cnt;
}

HDMI_COLORIMETRY_T Hdmi_GetColorimetry(void)
{
	unsigned int C, EC;

	hdmi_rx_reg_write32(HDMI_PSAP, 0x0, HDMI_RX_MAC);
	if (hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC) != 0)
		return HDMI_COLORIMETRY_NOSPECIFIED;

	hdmi_rx_reg_write32(HDMI_PSAP, 0x5, HDMI_RX_MAC);
	C = ((hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC) >> 6) & 0x03);
	hdmi_rx_reg_write32(HDMI_PSAP, 0x6, HDMI_RX_MAC);
	EC = ((hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC) >> 4) & 0x07);

	if (C != 0x03) {
		return (HDMI_COLORIMETRY_T) C;
	} else {
		return (HDMI_COLORIMETRY_T) (HDMI_COLORIMETRY_XYYCC601 + EC);
	}

}

char Hdmi_GetPixelDownSample(void)
{
	if (HDMI_VCR_get_prdsam(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC))) {
		return HDMI_VCR_get_dsc_r(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	} else {
		return HDMI_VCR_get_dsc(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	}
}

int Hdmi_GetColorDepth(void)
{
	return TMDS_DPC0_dpc_cd(hdmi_rx_reg_read32(TMDS_DPC0, HDMI_RX_MAC));
}

int hdmi_onms_measure(HDMI_TIMING_T *timing)
{
	timing->h_act_len = hdmirx_wrapper_get_active_pixel();
	timing->v_act_len = hdmirx_wrapper_get_active_line();

	timing->h_total = timing->h_act_len;
	timing->v_total = timing->v_act_len;

	if ((timing->h_act_len == 0) || (timing->v_act_len == 0) ||
		(timing->h_total == 0) || (timing->v_total == 0))
		return HDMI_ERR_ONMS_WRONG_TIMING;
	else
		return HDMI_ERR_NO;
}

