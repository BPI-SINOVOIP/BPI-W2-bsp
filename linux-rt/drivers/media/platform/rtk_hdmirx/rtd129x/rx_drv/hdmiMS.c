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
extern HDMI_INFO_T hdmi;
extern HDMI_CONST VIDEO_DPLL_RATIO_T dpll_ratio[];

extern unsigned int hdmirx_wrapper_get_active_pixel(void);
extern unsigned int hdmirx_wrapper_get_active_line(void);
/*======================================================*/


HDMI_ACTIVE_SPACE_TABLE_T hdmi_active_space_table[] = {
	{ "1080P FramePacking",  1, 1920,  1080*2 + 45, 1080, 45, 0 },
	{ "720P FramePacking",	1, 1280,  720*2 + 30, 720, 30, 0 },
	{ "480P FramePacking",	1, 720,  480*2 + 45, 480, 45, 0 },
	{ "576P FramePacking",	1, 720,  576*2 + 49, 576, 49, 0 },
	{ "1080I FramePacking",  0, 1920,  540*4 + 22 + 23*2, 540, 23, 22 },
	{ "576I FramePacking",	0, 720,  288*4 + 32 + 21*2, 288, 21, 32 },
	{ "480I FramePacking",	0, 720,  240*4 + 22 + 23*2, 240, 23, 22 },
	{ NULL,  1, 1920,  520, 40, 0 },
};

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

	hdmi_rx_reg_mask32(TMDS_CTRL, ~TMDS_CTRL_yo_mask, TMDS_CTRL_yo(1), HDMI_RX_MAC);

	for (i = 0; i < num; i++) {
		/* Wait vsync done */
		if (TMDS_CTRL_get_yo(hdmi_rx_reg_read32(TMDS_CTRL, HDMI_RX_MAC)))
			return 1;

		usleep_range(10000, 15000);/* 10~15ms */
	}

	HDMI_PRINTF("Wait vsync timeout\n");
	return 0;
}

unsigned int Hdmi_GetVSyncCountInit(void)
{
	hdmi.vsync_cnt = 0;

	return hdmi.vsync_cnt;
}
unsigned int Hdmi_GetVSyncCount(void)
{
	if (TMDS_CTRL_get_yo(hdmi_rx_reg_read32(TMDS_CTRL, HDMI_RX_MAC))) {
		hdmi_rx_reg_mask32(TMDS_CTRL, ~TMDS_CTRL_yo_mask, TMDS_CTRL_yo(1), HDMI_RX_MAC);
		hdmi.vsync_cnt++;
	}

	return hdmi.vsync_cnt;
}

bool Hdmi_GetInterlace(HDMI_MS_MODE_T mode)
{
	static unsigned int count_now, count_target;
	static unsigned char wrap_around;
	static int progressive = 0;
	progressive = !GET_HDMI_ISINTERLACE();

	switch (mode) {
	case HDMI_MS_MODE_ONESHOT:
		/* Clear status, prepare to check interlace/progressive */
		hdmi_rx_reg_mask32(HDMI_VCR, ~(HDMI_VCR_se_mask|HDMI_VCR_eot_mask|HDMI_VCR_int_pro_chg_flag_mask), HDMI_VCR_eot_mask, HDMI_RX_MAC);
		Hdmi_WaitVsync(15);
		Hdmi_WaitVsync(15);/* Wait vsync twice for interlace mode */
		if (hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & HDMI_VCR_eot_mask) {
			/* Interlace mode */
			/* HDMIRX_INFO("interlaced mode"); */
			progressive = 0;
			return 1;
		} else {
			/* HDMIRX_INFO(" Progressive mode"); */
			progressive = 1;
			return 0;
		}
		break;

	case HDMI_MS_MODE_CONTINUOUS_INIT:
		/* Clear status */
		hdmi_rx_reg_mask32(HDMI_VCR, ~HDMI_VCR_eot_mask, HDMI_VCR_eot(1), HDMI_RX_MAC);
		Hdmi_GetVSyncCountInit();
		count_now = Hdmi_GetVSyncCount();
		count_target = count_now + 4;
		if (count_target < count_now)
			wrap_around = 1;
		break;

	case HDMI_MS_MODE_CONTINUOUS_CHECK:
		if (count_now > Hdmi_GetVSyncCount())
			wrap_around = 0;

		count_now = Hdmi_GetVSyncCount();
		if (count_now  > count_target && wrap_around == 0) {
			if (hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & _BIT6)
				progressive = 0;/* Interlace mode */
			else
				progressive = 1;

			Hdmi_GetInterlace(HDMI_MS_MODE_CONTINUOUS_INIT);
		}
		break;
	default:
		break;
	}

	if (progressive)
		return 0;
	else
		return 1;
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

HDMI_ERR_T Hdmi_MeasureActiveSpace(HDMI_TIMING_T *tx_timing, HDMI_TIMING_T *gen_timing)
{
	int i = 0;
	int fields;

	HDMI_PRINTF("tx_timing->h_act_len = %d\n", tx_timing->h_act_len);
	HDMI_PRINTF("tx_timing->v_act_len = %d\n", tx_timing->v_act_len);

	while (hdmi_active_space_table[i].name) {
			HDMI_PRINTF(" hdmi_active_space_table[%d].h_act_len = %d\n", i, hdmi_active_space_table[i].h_act_len);
			HDMI_PRINTF(" hdmi_active_space_table[%d].v_act_len = %d\n", i, hdmi_active_space_table[i].v_act_len);

		if (tx_timing->h_act_len == hdmi_active_space_table[i].h_act_len && tx_timing->v_act_len == hdmi_active_space_table[i].v_act_len) {
			gen_timing->v_act_len = hdmi_active_space_table[i].lr_v_act_len;
			tx_timing->v_active_space1 = hdmi_active_space_table[i].v_active_space1;
			tx_timing->v_active_space2 = hdmi_active_space_table[i].v_active_space2;
			gen_timing->v_active_space1 = hdmi_active_space_table[i].v_active_space1;
			gen_timing->v_active_space2 = hdmi_active_space_table[i].v_active_space2;
			gen_timing->progressive = hdmi_active_space_table[i].progressive;
			fields = gen_timing->progressive ? 2 : 4;
			/* gen_timing->progressive = tx_timing->progressive; */
			gen_timing->color = tx_timing->color;
			gen_timing->depth = tx_timing->depth;

			gen_timing->v_freq = tx_timing->v_freq * fields;
			gen_timing->v_total = tx_timing->v_total / fields;
			gen_timing->h_freq = tx_timing->h_freq;
			gen_timing->h_act_len = tx_timing->h_act_len;
			gen_timing->h_total = tx_timing->h_total;
			gen_timing->h_act_sta = tx_timing->h_act_sta;
			gen_timing->v_act_sta = tx_timing->v_act_sta;
			HDMI_PRINTF("%s\n", hdmi_active_space_table[i].name);
			return HDMI_ERR_NO;
		}
		i++;
	}

	gen_timing->progressive = 1;
	fields = gen_timing->progressive ? 2 : 4;
	/* gen_timing->progressive = tx_timing->progressive; */
	gen_timing->color = tx_timing->color;
	gen_timing->depth = tx_timing->depth;

	gen_timing->v_freq = tx_timing->v_freq * fields;
	gen_timing->v_total = tx_timing->v_total / fields;
	gen_timing->h_freq = tx_timing->h_freq;
	gen_timing->h_act_len = tx_timing->h_act_len;
	gen_timing->h_total = tx_timing->h_total;
	gen_timing->h_act_sta = tx_timing->h_act_sta;
	gen_timing->v_act_sta = tx_timing->v_act_sta;
	gen_timing->v_act_len = (tx_timing->v_act_len - tx_timing->v_act_sta) / 2;
	gen_timing->v_active_space1 = tx_timing->v_act_sta;
	gen_timing->v_active_space2 = 0;
	tx_timing->v_active_space1 = tx_timing->v_act_sta;
	tx_timing->v_active_space2 = 0;

	HDMI_PRINTF("Unknow frame packing fomat and force to 2D\n");

	return HDMI_EER_MEASURE_ACTIVESPACE_FAIL;
}

HDMI_3D_T Hdmi_Get3DInfo(HDMI_MS_MODE_T mode)
{
	char   timeout = 10;
	HDMI_3D_T result;

	switch (mode) {
	case HDMI_MS_MODE_ONESHOT:
		hdmi_rx_reg_mask32(HDMI_PTRSV1, ~0x00FF00, 0x81<<8, HDMI_RX_MAC);
		/* Clear RSV2 indicator */
		hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_pis_6_mask, HDMI_RX_MAC);

		for (timeout = 12; timeout > 0; timeout--) {
			HDMI_DELAYMS(10);
			if (hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC) & HDMI_GPVS_pis_6_mask) {
				/* if 3D format indication present is absent, return 2D anyway */
				if (HDMI_VIDEO_FORMAT_get_hvf(hdmi_rx_reg_read32(HDMI_VIDEO_FORMAT, HDMI_RX_MAC)) != 0x02)
					return HDMI3D_2D_ONLY;
				else
					return (HDMI_3D_T) HDMI_3D_FORMAT_get_hdmi_3d_structure(hdmi_rx_reg_read32(HDMI_3D_FORMAT, HDMI_RX_MAC));
			}
		}
		if (timeout == 0)
			HDMI_PRINTF("Hdmi_Get3DInfo timeout\n");
		return HDMI3D_2D_ONLY;
		break;

	case HDMI_MS_MODE_ONESHOT_INIT:
		/* Packet Type = 0x81(HDMI Vendor Specific InfoFrame) */
		hdmi_rx_reg_mask32(HDMI_PTRSV1, 0xffff00ff, 0x00008100, HDMI_RX_MAC);
		/*Clear RSV2 indicator*/
		hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_pis_6_mask, HDMI_RX_MAC);
		break;

	case HDMI_MS_MODE_ONESHOT_GET_RESULT:
		if (hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC) & HDMI_GPVS_pis_6_mask) {
			/* if 3D format indication present is absent, return 2D anyway */
			if (HDMI_VIDEO_FORMAT_get_hvf(hdmi_rx_reg_read32(HDMI_VIDEO_FORMAT, HDMI_RX_MAC)) != 0x02)
				result = HDMI3D_2D_ONLY;
			else
				result = (HDMI_3D_T) HDMI_3D_FORMAT_get_hdmi_3d_structure(hdmi_rx_reg_read32(HDMI_3D_FORMAT, HDMI_RX_MAC));

			switch ((unsigned int)result) {
			case HDMI3D_FRAME_PACKING:
			case HDMI3D_LINE_ALTERNATIVE:
			case HDMI3D_2D_ONLY:
			case HDMI3D_SIDE_BY_SIDE_FULL:
			case HDMI3D_TOP_AND_BOTTOM:
				break;
			default:
				HDMI_PRINTF("3D mode %d not support\n", result);
				return HDMI3D_2D_ONLY;
				break;
			}
			return result;
		} else {
			return HDMI3D_2D_ONLY;
		}
		break;
	default:
		return HDMI3D_UNKOWN;
		break;
	}

	return HDMI3D_UNKOWN;
}

unsigned char Hdmi_Get3DExtInfo(void)
{
	return HDMI_3D_FORMAT_get_hdmi_3d_ext_data(hdmi_rx_reg_read32(HDMI_3D_FORMAT, HDMI_RX_MAC));
}

void Hdmi_Get3DGenTiming(HDMI_TIMING_T *tx_timing, HDMI_TIMING_T *gen_timing)
{
	/* Determine output 3D format */
	switch (hdmi.path_policy) {
	case HDMI_PATH_POLICY_2D_ONLY:
		gen_timing->hdmi_3dformat = HDMI3D_2D_ONLY;
		hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_DISABLE;
		break;
	case HDMI_PATH_POLICY_3D_NODMA:
		hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_DISABLE;
		if (tx_timing->hdmi_3dformat == HDMI3D_FRAME_PACKING)
			gen_timing->hdmi_3dformat = HDMI3D_FRAME_PACKING;
		else
			gen_timing->hdmi_3dformat = HDMI3D_2D_ONLY;
		break;
	case HDMI_PATH_POLICY_3D_DMA:
		if (hdmi.hdmi3d_capability == 0) {
			gen_timing->hdmi_3dformat = HDMI3D_2D_ONLY;
		} else if (hdmi.force_all_3d_disable) {
			gen_timing->hdmi_3dformat = HDMI3D_2D_ONLY;
		} else if (hdmi.force_2dto3d_enable && tx_timing->hdmi_3dformat == HDMI3D_2D_ONLY) {
			gen_timing->hdmi_3dformat = hdmi.force_2dto3d_mode;
			hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_HW;
		} else if (hdmi.force_3dto2d_enable && tx_timing->hdmi_3dformat != HDMI3D_2D_ONLY) {
			if (hdmi.force_3dto2d_lr_sel)
				hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_HW_2DONLY_L;
			else
				hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_HW_2DONLY_R;
		} else {
			gen_timing->hdmi_3dformat = tx_timing->hdmi_3dformat;
			if (gen_timing->hdmi_3dformat != HDMI3D_2D_ONLY)
				hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_HW;
			else
				hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_DISABLE;
		}
		break;
	}

	gen_timing->colorimetry = tx_timing->colorimetry;
	gen_timing->color = tx_timing->color;
	gen_timing->depth = tx_timing->depth;
	gen_timing->quincunx_en = 0;

	switch (gen_timing->hdmi_3dformat) {
	case HDMI3D_2D_ONLY:
		/* 3d convert to 2D , don't do DI */
		if (tx_timing->hdmi_3dformat != HDMI3D_2D_ONLY)
			gen_timing->progressive = 1;
		else
			gen_timing->progressive = tx_timing->progressive;

		gen_timing->v_total = tx_timing->v_total;
		gen_timing->v_act_len = tx_timing->v_act_len;
		gen_timing->v_act_sta = tx_timing->v_act_sta;
		gen_timing->h_total = tx_timing->h_total;
		gen_timing->h_act_len = tx_timing->h_act_len;
		gen_timing->h_act_sta = tx_timing->h_act_sta;
		gen_timing->v_freq = tx_timing->v_freq;
		gen_timing->h_freq = tx_timing->h_freq;
		break;
	case HDMI3D_FRAME_PACKING:
		Hdmi_MeasureActiveSpace(tx_timing, gen_timing);
		break;
	case HDMI3D_LINE_ALTERNATIVE:
		gen_timing->progressive = tx_timing->progressive;
		gen_timing->v_total = tx_timing->v_total/2;
		gen_timing->v_act_len = tx_timing->v_act_len/2;
		gen_timing->v_act_sta = tx_timing->v_act_sta;
		gen_timing->h_total = tx_timing->h_total;
		gen_timing->h_act_len = tx_timing->h_act_len;
		gen_timing->h_act_sta = tx_timing->h_act_sta;
		gen_timing->v_freq = tx_timing->v_freq*2;
		gen_timing->h_freq = tx_timing->h_freq;
		break;
	case HDMI3D_SIDE_BY_SIDE_FULL:
		HDMI_PRINTF("HDMI3D_SIDE_BY_SIDE_FULL\n");
		gen_timing->progressive = tx_timing->progressive;
		gen_timing->v_total = tx_timing->v_total/2;
		gen_timing->v_act_len = tx_timing->v_act_len;
		gen_timing->v_act_sta = tx_timing->v_act_sta;
		gen_timing->h_total = tx_timing->h_total/2;
		gen_timing->h_act_len = tx_timing->h_act_len/2;
		gen_timing->h_act_sta = tx_timing->h_act_sta/2;
		gen_timing->v_freq = tx_timing->v_freq * 2;
		gen_timing->h_freq = tx_timing->h_freq;
		break;
	case HDMI3D_TOP_AND_BOTTOM:
		HDMI_PRINTF("HDMI3D_TOP_AND_BOTTOM\n");
		gen_timing->progressive = tx_timing->progressive;
		gen_timing->v_total = tx_timing->v_total/2;
		gen_timing->v_act_len = tx_timing->v_act_len/2;
		gen_timing->v_act_sta = tx_timing->v_act_sta/2;
		gen_timing->h_total = tx_timing->h_total;
		gen_timing->h_act_len = tx_timing->h_act_len;
		gen_timing->h_act_sta = tx_timing->h_act_sta;
		gen_timing->v_freq = tx_timing->v_freq * 2;
		gen_timing->h_freq = tx_timing->h_freq;
		break;
	case HDMI3D_SIDE_BY_SIDE_HALF:
		HDMI_PRINTF("HDMI3D_SIDE_BY_SIDE_HALF\n");
		gen_timing->progressive = tx_timing->progressive;
		gen_timing->v_total = tx_timing->v_total/2;
		gen_timing->v_act_len = tx_timing->v_act_len;
		gen_timing->v_act_sta = tx_timing->v_act_sta;
		gen_timing->h_total = tx_timing->h_total/2;
		gen_timing->h_act_len = tx_timing->h_act_len/2;
		gen_timing->h_act_sta = tx_timing->h_act_sta/2;
		gen_timing->v_freq = tx_timing->v_freq * 2;
		gen_timing->h_freq = tx_timing->h_freq;
		gen_timing->quincunx_en = tx_timing->quincunx_en;
		gen_timing->quincunx_mode = tx_timing->quincunx_mode;
		break;
	case HDMI3D_FIELD_ALTERNATIVE:
		HDMI_PRINTF("HDMI3D_FIELD_ALTERNATIVE\n");
		gen_timing->progressive = tx_timing->progressive;
		gen_timing->v_total = tx_timing->v_total/2;
		gen_timing->v_act_len = tx_timing->v_act_len;
		gen_timing->v_act_sta = tx_timing->v_act_sta;
		gen_timing->h_total = tx_timing->h_total;
		gen_timing->h_act_len = tx_timing->h_act_len;
		gen_timing->h_act_sta = tx_timing->h_act_sta;
		gen_timing->v_freq = tx_timing->v_freq * 2;
		gen_timing->h_freq = tx_timing->h_freq;
		break;
	default:
		break;
	}

	/* Determine 3D HW PATH format */
	if (hdmi.path_policy == HDMI_PATH_POLICY_3D_NODMA) {
		if (gen_timing->hdmi_3dformat == HDMI3D_FRAME_PACKING &&
			tx_timing->hdmi_3dformat  == HDMI3D_FRAME_PACKING &&
			gen_timing->progressive == 0)
			hdmi.hw_hdmi_dma = HDMI_3D_OPMODE_HW_NODMA;
	}
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


bool Hdmi_MeasureTiming(HDMI_TIMING_T *timing, int b)
{
	unsigned char cd;
	unsigned int Q, D;
	int downsample;

	downsample = Hdmi_GetPixelDownSample();
	cd = Hdmi_GetColorDepth();

	if (hdmi_onms_measure(timing) != HDMI_ERR_NO)
		return FALSE;

	if (downsample != Hdmi_GetPixelDownSample())  {
		HDMI_PRINTF("down sample number change\n");
		return FALSE;
	}

	if (cd != Hdmi_GetColorDepth()) {
		HDMI_PRINTF("color depth change\n");
		return FALSE;
	}

	if (GET_HDMI_ISINTERLACE() != Hdmi_GetInterlace(HDMI_MS_MODE_CONTINUOUS_CHECK)) {
		HDMI_PRINTF("interlace change\n");
		return FALSE;
	}

	timing->progressive = GET_HDMI_ISINTERLACE() == 0;

	/* timing compansation */
	if (GET_HDMI_ISINTERLACE() && GET_HDMI_DEONLY_MODE()) {
		if ((timing->v_total & 0x01) == 1) {
			/* ODD field */
			timing->v_act_sta -= 1;
			timing->v_total -= 1;
		}
	}

	/* Horizontal active width must be even */
	if (timing->h_act_len & 0x01)
		timing->h_act_len -= 1;

	/* To calculate IVFreq */
	if (cd >= 0x04 && cd < 0x08)
		cd = cd - 0x04;
	else
		cd = 0;

	if (b != 0) {
		/* Implement Q = (27000000 * hdmi.b / 256 * RatioM) / RatioN */
		D = ((downsample & 0x0f) + 1) * timing->h_total;

		Q = ((27000000UL * dpll_ratio[cd].RatioM)) / (dpll_ratio[cd].RatioN * 256);
		Q = (hdmi.b * Q);
		Q = ((Q + (D >> 1)) / D);

		timing->h_freq = (Q + 50) / 100;
		timing->v_freq = (Q * 10 + (timing->v_total>>1)) / timing->v_total;

#if HDMI2p0
		if (bHDMI_420_Space == COLOR_YUV420)
			timing->v_freq = 2*timing->v_freq;
#endif
	} else {
		timing->h_freq = 0;
		timing->v_freq = 0;
	}

	HDMI_PRINTF("IVTotal: %d\n", timing->v_total);
	HDMI_PRINTF("IHTotal: %d\n", timing->h_total);

	HDMI_PRINTF("IHWidth:%d\n", timing->h_act_len);
	HDMI_PRINTF("IVHeight:%d\n", timing->v_act_len);

	HDMI_PRINTF("IVStart:%d\n", timing->v_act_sta);
	HDMI_PRINTF("IHStart:%d\n", timing->h_act_sta);

	if (timing->h_freq)
		HDMI_PRINTF("IHFreq:%d\n", timing->h_freq);
	if (timing->v_freq)
		HDMI_PRINTF("IVFreq:%d\n", timing->v_freq);

	return TRUE;

}

