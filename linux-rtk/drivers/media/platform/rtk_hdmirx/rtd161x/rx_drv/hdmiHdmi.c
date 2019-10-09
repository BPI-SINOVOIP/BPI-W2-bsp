/*
 * hdmiHdmi.c - RTK hdmi rx driver
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/gpio.h>

#include "hdmirx_wrapper.h"
#include "hdmiInternal.h"

/*
 * Marco or Definitions
 */
#define CLK_STABLE_CNT		8
#define TMDS_CLOCK_TOLERANCE()	MAX(hdmi_rx.timing_t.tmds_clk_b>>7, 5) /* 6G tolerance should be larger */

#define NO_DRM_INFO_MAX		6
#define NO_AVI_INFO_MAX		6
#define NO_VSI_INFO_MAX		6
#define NO_SPD_INFO_MAX		25 /* 40ms * 25 = 1000 ms */
#define NO_SPD_CLEAR_PACKET	0
#define NO_AUDIO_INFO_MAX	6
#define HDCP_RESET_CNT		30 /* The counter for keeping HDCP 1.4 or 2.2 in no signal state, if timeout, turn on both 1.4 & 2.2*/ 

/*
 * Const Declarations
 */
const VIDEO_DPLL_RATIO_T dpll_ratio[] = {
	{15, 15, 1, 1},	/* 24 bits */
	{12, 15, 4, 5},	/* 30 bits */
	{10, 15, 2, 3},	/* 36 bits */
	{15, 30, 1, 2},	/* 48 bits */
};

const VIDEO_DPLL_FIX_T video_pll_main_param[]= {
	{30, 0, 0b010, 0b100},
	{62, 3, 0b010, 0b111},
	{30, 1, 0b010, 0b100},
	{ 6, 0, 0b000, 0b100},
	{14, 3, 0b001, 0b101},	
	{ 6, 1, 0b000, 0b100},
	{ 6, 2, 0b000, 0b100},
	{ 6, 3, 0b000, 0b100},
	{ 6, 4, 0b000, 0b100},
	{ 6, 6, 0b000, 0b100},
	{ 2, 3, 0b000, 0b100},
	{ 2, 4, 0b000, 0b100},
};

const VIDEO_DPLL_RANGE_T video_pll_others_param[]= {
	{ 6, 10, 0b000, 0b100},
	{11, 18, 0b000, 0b111},
	{19, 30, 0b001, 0b110},
	{31, 48, 0b010, 0b110},	
};

const HDMI_AUDIO_PLL_PARAM_T hdmi_audiopll_param[] = {
	{  32000,  2,   20,  2,  8,  1,  0x1D, 0xDC,  "32K"},
	{  44100,  2,   20,  2,  6,  1,  0xFC, 0x68,  "44.1K"},
	{  48000,  2,   22,  2,  6,  1,  0x07, 0x40,  "48K"},
	{  88200,  2,   20,  1,  6,  1,  0xFE, 0x7A,  "88.2K"},
	{  96000,  2,   22,  1,  6,  1,  0x07, 0x40,  "96K"},
	{ 176400,  2,   20,  1,  6,  0,  0xFE, 0x7A,  "176.4K"},
	{ 192000,  2,   22,  1,  6,  0,  0x07, 0x40,  "192K"},
#if AUDIO_OVER_192K
	{ 352800,  2,   22,  1,  6,  0,  0x07, 0x40,  "352.8K"},
	{ 705600,  2,   22,  1,  6,  0,  0x07, 0x40,  "705.6K"},
	{1411200,  2,   22,  1,  6,  0,  0x07, 0x40,  "1411.2K"},
	{1536000,  2,   22,  1,  6,  0,  0x07, 0x40,  "1536K"},
#endif
};

const unsigned int AUDIO_CHANNEL_STATUS[] = {
	44100,
	0, /* 0 indicate standard no support */
	48000,
	32000,
	22000,
	0,
	24000,
	0,
	88200,
	0,
	96000,
	0,
	176400,
	0,
	192000,
	0,
};


const char *colormetry_name[]  = {
	"HDMI_COLORIMETRY_NOSPECIFIED",
	"HDMI_COLORIMETRY_601",
	"HDMI_COLORIMETRY_709",
	"HDMI_COLORIMETRY_XYYCC601",
	"HDMI_COLORIMETRY_XYYCC709",
	"HDMI_COLORIMETRY_SYCC601",
	"HDMI_COLORIMETRY_ADOBE_YCC601",
	"HDMI_COLORIMETRY_ADOBE_RGB",
};

const char *depth_name[] = {

	"HDMI_COLOR_DEPTH_8B",
	"HDMI_COLOR_DEPTH_10B",
	"HDMI_COLOR_DEPTH_12B",
	"HDMI_COLOR_DEPTH_16B",

};

const char *colorspace_name[] = {
	"COLOR_RGB",
	"COLOR_YUV422",
	"COLOR_YUV444",
	"COLOR_YUV420",
	"COLOR_UNKNOW"
};

const char *hdmi_3d_name[] = {
	"HDMI3D_FRAME_PACKING",
	"HDMI3D_FIELD_ALTERNATIVE",
	"HDMI3D_LINE_ALTERNATIVE",
	"HDMI3D_SIDE_BY_SIDE_FULL",
	"HDMI3D_L_DEPTH",

	"HDMI3D_L_DEPTH_GPX",
	"HDMI3D_TOP_AND_BOTTOM",
	"HDMI3D_RSV0",
	"HDMI3D_SIDE_BY_SIDE_HALF",
	"HDMI3D_LINE_BY_LINE",

	"HDMI3D_VERTICAL_STRIPE",
	"HDMI3D_CHECKER_BOARD",
	"HDMI3D_REALID",
	"HDMI3D_SENSIO",
	"HDMI3D_RSV1",

	"HDMI3D_2D_ONLY",
};


/*
 * Variables
 */
HDMI_PORT_INFO_T	hdmi_rx;

static unsigned int bNeedDebBeforeDisp = 0;
static unsigned int DispDebCnt = 0;
static unsigned int DispDebCondition = 0;

#if HDMI_TOGGLE_HPD_Z0_ENABLE
unsigned char hdmi_toggle_hpd_z0_flag = 0;
HDMI_DC_ON_STATE_E hdmi_dc_on_delay_state = HDMI_DC_ON_NONE;
#endif

#if HDMI_STR_TOGGLE_HPD_ENABLE
HDMI_STR_HPD_TOGGLE_STATE_E hdmi_str_toggle_hpd_state = HDMI_STR_HPD_TOGGLE_NONE;
#endif

#if HDMI_DISPLAY_DELAY_ENABLE
unsigned char hdmi_delay_display_enable = _DISABLE;
HDMI_DISPLAY_DELAY_STATE_STATE_E hdmi_delay_display_state = HDMI_DISPLAY_DELAY_NONE;
#endif

#if 1
HDMI_SPECIFIC_DEVICE_E hdmi_specific_device = HDMI_SPECIFIC_DEVICE_NONE;
#endif


/*
 * Funtion Declarations
 */


void hdmi_fix_green_line(void);


unsigned char hdmi_update_vsi(void);
unsigned char hdmi_update_avi(void);
unsigned char hdmi_update_spd(void);
unsigned char hdmi_update_audiopkt(void);
unsigned char hdmi_update_drm(void);
unsigned char hdmi_update_rsv0_packet(unsigned char len, unsigned char *buf);
unsigned char hdmi_update_rsv1_packet(unsigned char len, unsigned char *buf);
unsigned char hdmi_update_rsv2_packet(unsigned char len, unsigned char *buf);
unsigned char hdmi_update_rsv3_packet(unsigned char len, unsigned char *buf);
unsigned char hdmi_check_spd_name(unsigned char *vendor_name);
unsigned char hdmi_check_spd_prod(unsigned char *prod_desc);

unsigned char hdmi_compatibility_check(void);
unsigned char hdmi_check_avi_colorimetry_info(unsigned char ucInit);
unsigned char hdmi_no_SPD_packetInfo(void);
unsigned char hdmi_check_deb_condition_beforeDisp(unsigned char ucInit);
unsigned char hdmi_check_hdcp_condition(unsigned char ucInit);


void hdmi_init(void)
{
	HDMIRX_INFO("%s\n", __func__);

	lib_hdmi_power(0);

	hdmi_check_hdcp_condition(TRUE);

	lib_hdmi_phy_init();

	hdmi_port_var_init();

	lib_hdmi_power(1);

	lib_hdmi_tmds_init();

	lib_hdmi_mac_init();

	hdmi_audio_close();

	rxphy_init_struct();

	rxphy_isr_set(1);

	lib_hdmi_gcp_ackg_header_parsing_mode();
	lib_hdmi_valid_format_condition();
	lib_hdmi_misc_variable_initial();

	HDMIRX_INFO("%s done\n", __func__);

}

void hdmi_release_source(void)
{
	rxphy_isr_set(0);
	lib_hdmi_power(0);

	hdmi_disconnect_source();
}

void hdmi_disconnect_source(void)
{
	/* Keep PHY_ISR in active, keep power on */
	lib_hdmi_video_output(0);/* Blanking screen in step 1 */
	hdmi_port_var_init();

	lib_hdmi_video_output(0);/* Close again, avoid re-open in detect_mode */
	hdmi_audio_close();

#ifdef HDMI_VIDEO_WD_ENABLE
	hdmi_watchdog_apply(_DISABLE, HDMI_WD_ALL_COND);
#endif
}

void hdmi_port_select(void)
{
	/* Reset all mac functions */
	hdmi_rx_reg_mask32(HDMI_PORT_SWITCH,
		~HDMI_PORT_SWITCH_port_sel_mask,
		HDMI_PORT_SWITCH_port_sel(0), HDMI_RX_MAC);

	lib_hdmi_video_output(0);
}

void hdmi_port_var_init(void)
{
	SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
	SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);

	SET_H_INTERLACE(0);
	SET_H_MODE(MODE_HDMI);
	SET_H_COLOR_DEPTH(HDMI_COLOR_DEPTH_8B);
	SET_H_COLOR_SPACE(COLOR_RGB);

	SET_H_3DFORMAT(HDMI3D_2D_ONLY);

	hdmi_audio_var_init();
}

unsigned char hdmi_detect_mode(void)
{
	unsigned char ret_val;
	unsigned char yuv_fmt;

	ret_val = _MODE_NOSIGNAL;

	if (GET_H_VIDEO_FSM() > MAIN_FSM_HDMI_SETUP_VEDIO_PLL) {
		if (hdmi_check_condition_change())
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
	}

	switch (GET_H_VIDEO_FSM()) {
	case MAIN_FSM_HDMI_WAIT_SYNC:
		if (hdmi_wait_sync())
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
		else
			goto exit;
	break;

	case MAIN_FSM_HDMI_SETUP_VEDIO_PLL:
		if (hdmi_setup_video_pll()) {
			hdmi_check_deb_condition_beforeDisp(TRUE);
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_MEASURE);
		} else {
			goto exit;
		}
	break;

	case MAIN_FSM_HDMI_MEASURE:
		if (hdmi_measure()) {
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_DISPLAY_ON);
		} else {
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
			ret_val = _MODE_DETECT;
			goto exit;
		}
		break;

	case MAIN_FSM_HDMI_DISPLAY_ON:
		if (hdmi_display_on()) {

			if (lib_hdmi_get_avmute() && !lib_hdmi_get_bch_2bit_error()) {
				HDMI_PRINTF("[WARNING] AVMUTE...\n");
				SET_H_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
				goto exit;
			}

			if (hdmi_check_condition_change()) {
				SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
				goto exit;
			}

			if (!hdmi_compatibility_check()) {
				SET_H_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
				goto exit;
			}

			lib_hdmi_char_err_rst(0);
			HDMI_PRINTF("FSM_HDMI_DISPLAY_ON OK\n");
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_VIDEO_READY);
			ret_val = _MODE_SUCCESS;

			/* Enable rx wrapper detect */
			yuv_fmt = hdmirx_wrapper_convert_color_fmt(hdmi_rx.timing_t.colorspace);
			set_hdmirx_wrapper_control_0(-1, -1, -1, -1, yuv_fmt, -1);
			hdmirx_state.detect_done = 1;
			set_hdmirx_wrapper_interrupt_en(0, 0, 1);
		} else {
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
			ret_val = _MODE_DETECT;
		}
		break;

	case MAIN_FSM_HDMI_VIDEO_READY:
		if (hdmi_video_ready()) {
			ret_val = _MODE_SUCCESS;
		} else {
			SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
			ret_val = _MODE_NOSIGNAL;
		}
		break;

	default:
		break;
	}

exit:
	return ret_val;
}

unsigned char hdmi_check_condition_change(void)
{
	unsigned int phy_clk;

	if (!rxphy_is_clk_stable()) {
		return TRUE;
	}

	phy_clk = rxphy_get_clk();

	if (phy_clk < VALID_MIN_CLOCK) {
		HDMI_PRINTF("invalid clock\n");
		return TRUE;
	}

	if (HDMI_ABS(phy_clk, hdmi_rx.timing_t.tmds_clk_b) > TMDS_CLOCK_TOLERANCE()) {
		HDMI_PRINTF("clock change\n");
		return TRUE;
	}

	if (GET_H_MODE() == MODE_HDMI) {
		if (GET_H_COLOR_SPACE() != hdmi_get_colorspace_reg()) {
			HDMI_PRINTF("colorspace chg from %d to %d\n",
				GET_H_COLOR_SPACE(), hdmi_get_colorspace_reg());
			return TRUE;
		}

		if (GET_H_COLOR_DEPTH() != lib_hdmi_get_color_depth()) {
			HDMI_PRINTF("color depth chage\n");
			return TRUE;
		}
	}

	if (GET_H_MODE() != hdmi_get_hdmi_mode_reg()) {
		HDMI_PRINTF("HDMI/DVI chg from %d to %d\n", GET_H_MODE(), (!GET_H_MODE()));
		return TRUE;
	}

	return FALSE;
}

unsigned char hdmi_wait_sync(void)
{
	unsigned int curr_clk;

#if HDMI_TOGGLE_HPD_Z0_ENABLE
	lib_hdmi_toggle_hpd_z0_check(FALSE);
#endif

	curr_clk = rxphy_get_clk();
	if ((curr_clk < VALID_MIN_CLOCK) ||
		(HDMI_ABS(hdmi_rx.timing_t.tmds_clk_b, curr_clk) > TMDS_CLOCK_TOLERANCE())) {
		/* Set false if clock is invalid or changed */
		hdmi_rx.timing_t.tmds_clk_b = curr_clk;
		hdmi_rx.timing_t.tmds_clk_stable_cnt = 0;
		if (hdmi_rx.timing_t.is_interlace) {
			lib_hdmi_clear_interlace_reg();
			hdmi_rx.timing_t.is_interlace = 0;
		}
		return FALSE;
	}

	if (hdmi_rx.timing_t.tmds_clk_stable_cnt < CLK_STABLE_CNT) {
		/* Set false if clock is unstable */
		hdmi_rx.timing_t.tmds_clk_stable_cnt++;
		return FALSE;
	}
	hdmi_rx.timing_t.tmds_clk_b = curr_clk;

	if (!rxphy_get_setphy_done()) {
		/* HDMI_PRINTF("Wait for set_phy(p%d)\n", port); */
		return FALSE;
	}

	hdmi_open_err_detect();
	lib_hdmi_set_repeat_auto();
	lib_hdmi_set_colorspace_auto();

	lib_hdmi_bch_error_clr();

	hdmi_audio_var_init();
	hdmi_reset_all_infoframe();
	lib_hdmi_audio_set_hbr_manual_mode(0, 0);
	lib_hdmi_audio_clear_hdr_status();

#if HDMI_AVI_INFO_COLORIMETRY_ENABLE
	hdmi_check_avi_colorimetry_info(TRUE);
#endif

	return TRUE;
}

unsigned char hdmi_setup_video_pll(void)
{
	HDMI_PRINTF("FSM_HDMI_SETUP_VEDIO_PLL\n");

	hdmi_port_select();

#ifdef HDMI_VIDEO_WD_ENABLE
	/* Enable Video and Audio, to prevent Tx HDMI have no audio, the watch dog not work */
	hdmi_watchdog_apply(_DISABLE, HDMI_WD_ALL_COND);
#endif

	SET_H_COLOR_DEPTH((HDMI_COLOR_DEPTH_T)lib_hdmi_get_color_depth());
	SET_H_MODE((HDMI_DVI_MODE_T)hdmi_get_hdmi_mode_reg());
	SET_H_PIXEL_REPEAT(lib_hdmi_get_pixelrepeat());

	if (GET_H_MODE() == MODE_DVI) {
		lib_hdmi_set_repeat_manual(0);
		lib_hdmi_set_colorspace_manual(0);
	} else {
		lib_hdmi_set_repeat_auto();
		lib_hdmi_set_colorspace_auto();
	}

	SET_H_COLOR_SPACE((HDMI_COLOR_SPACE_T)hdmi_get_colorspace_reg());
	SET_H_INTERLACE(lib_hdmi_get_is_interlace(HDMI_MS_DIRECT));
	lib_hdmi_clear_interlace_reg();

	if (!lib_hdmi_set_video_pll(hdmi_rx.timing_t.tmds_clk_b,
		hdmi_rx.timing_t.colordepth,
		hdmi_rx.timing_t.is_interlace,
		hdmi_rx.timing_t.colorspace==COLOR_YUV420))
		return FALSE;

	return TRUE;
}

unsigned char hdmi_measure(void)
{
	HDMI_PRINTF("FSM_HDMI_MEASURE\n");

	lib_hdmi_meas_select_port();
	lib_hdmi_video_output(1);
	lib_hdmi_crc_check();

	/* TODO: Check timing */
	if (0) {
		hdmi_rx.meas_retry_cnt++;
		if (hdmi_rx.meas_retry_cnt > MEAS_RETRY_LIMIT) {
			rxphy_reset_setphy_proc();

#if HDMI2p0
			/*
			 * To prevent Tx unstable, pixel clock unstable, but large than VALID_MIN_CLOCK
			 * it will let toggle function NG
			 * pixel clock stable + measure NG
			 */
			hdmi2p0_inc_scdc_toggle();
#endif

#if HDMI_STR_TOGGLE_HPD_ENABLE
			if (lib_hdmi_get_str_toggle_hpd_state() == HDMI_STR_HPD_TOGGLE_READY) {
				Hdmi_SetHPD(0);
				HDMI_DELAYMS(HDMI_STR_TOGGLE_HPD_MS);
				HDMI_PRINTF("STR on HPD Toggle\n");
				Hdmi_SetHPD(1);
				lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_NONE);
			}
#endif
		}
		return FALSE;
	}

	hdmi_check_crc_0();

	return TRUE;
}

unsigned char hdmi_display_on(void)
{
	if (GET_H_COLOR_SPACE() != hdmi_get_colorspace_reg()) {
		HDMI_PRINTF("D-CS chg from %d to %d\n",
			GET_H_COLOR_SPACE(), hdmi_get_colorspace_reg());
		return FALSE;
	}
	if (GET_H_COLOR_DEPTH() != lib_hdmi_get_color_depth()) {
		HDMI_PRINTF("D-CD chg from %d to %d\n",
			GET_H_COLOR_DEPTH(), lib_hdmi_get_color_depth());
		return FALSE;
	}
	if (GET_H_PIXEL_REPEAT() != lib_hdmi_get_pixelrepeat()) {
		HDMI_PRINTF("D-PR chg from %d to %d\n",
			GET_H_PIXEL_REPEAT(), lib_hdmi_get_pixelrepeat());
		return FALSE;
	}
	if (GET_H_INTERLACE() != lib_hdmi_get_is_interlace(HDMI_MS_DIRECT)) {
		HDMI_PRINTF("D-IP chg from %d to %d\n",
			GET_H_INTERLACE(), (!GET_H_INTERLACE()));
		return FALSE;
	}

	hdmi_fix_green_line();

#ifdef HDMI_VIDEO_WD_ENABLE
	hdmi_watchdog_apply(_ENABLE, (HDMI_WD_VIDEO_COND | HDMI_WD_AUDIO_COND));
#endif

	if (GET_H_MODE()) {
		SET_H_VIDEO_FORMAT((HDMI_HVF_E)hdmi_get_video_format_reg());
		SET_H_3DFORMAT((HDMI_3D_T)hdmi_get_3d_structure_reg());
	}

	HDMI_PRINTF("bHDMIColorSpace = %s\n",
		GET_H_COLOR_SPACE() < (sizeof(colorspace_name)/4)  ? colorspace_name[GET_H_COLOR_SPACE()] : "UNDEFINED");
	HDMI_PRINTF("IsInterlaced = %d\n", GET_H_INTERLACE());
	HDMI_PRINTF("bIsHDMIDVI = %d\n", GET_H_MODE());
	HDMI_PRINTF("PixelRepeat = %d\n", GET_H_PIXEL_REPEAT());
	HDMI_PRINTF("ColorDepth = %s\n", GET_H_COLOR_DEPTH() < (sizeof(depth_name)/4)  ? depth_name[GET_H_COLOR_DEPTH()] : "UNDEFINED");
	HDMI_PRINTF("ColorMetry = %s\n",
		hdmi_get_colorimetry() < (sizeof(colormetry_name)/4)  ? colormetry_name[hdmi_get_colorimetry()]: "UNDEFINED");
	HDMI_PRINTF("3D Format  = %s\n", GET_H_3DFORMAT() < (sizeof(hdmi_3d_name)/4) ? hdmi_3d_name[GET_H_3DFORMAT()] : "UNDEFINED");

	return TRUE;
}

unsigned char hdmi_video_ready(void)
{
	/* To prevent picture have short time garbage before display */
	if (lib_hdmi_get_avmute() && !lib_hdmi_get_bch_2bit_error()) {
		HDMI_PRINTF("[WARNING] AVMUTE 2...\n");
		SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);
		return FALSE;
	}

	return TRUE;
}


unsigned char hdmi_check_mode(void)
{
	if (lib_hdmi_get_avmute() && (lib_hdmi_is_wdm_enable() || !lib_hdmi_get_bch_2bit_error())) {
		lib_hdmi_video_output(0);
		lib_hdmi_audio_output(0);
		HDMI_PRINTF("check_mode: [WARNING] AVMUTE 3...\n");
		return FALSE;
	}

	if (GET_H_VIDEO_FSM() != MAIN_FSM_HDMI_VIDEO_READY) {
		HDMI_PRINTF("check_mode: changed_1\n");
		return FALSE;
	}

	if (hdmi_check_condition_change()) {
		lib_hdmi_video_output(0);
		lib_hdmi_audio_output(0);
		HDMI_PRINTF("check_mode: changed_2\n");
		return FALSE;
	}

#if HDMI_INT_PRO_CHG_FLAG_ENABLE
	if (lib_hdmi_get_is_interlace_change() == TRUE) {
		HDMI_PRINTF("interlace chg\n");
		return FALSE;
	}
#else //#if HDMI_INT_PRO_CHG_FLAG_ENABLE
	if (GET_H_INTERLACE() != hdmi_get_interlace_conti_mode()) {
		HDMI_PRINTF("check_mode: interlace chg from %d to %d\n", GET_H_INTERLACE(), (!GET_H_INTERLACE()));
		return FALSE;
	}
#endif //#if HDMI_INT_PRO_CHG_FLAG_ENABLE


#if 1/* BITERR_PATCH */
	if (hdmi_rx.timing_t.tmds_clk_b > 2900) {
		/* > 3G */
		if (hdmi_char_err_detection()) {
			if (hdmi_is_long_cable()) {
				hdmi_dfe_recovery_6g_long_cable();
			}
		}
	} else if (hdmi_rx.timing_t.tmds_clk_b > 1042) {
		/* > 1.1G */
		if (hdmi_bit_err_detection()) {
		//	hdmi_dfe_recovery_mi_speed();
		}
	}
#endif

	return TRUE;
}

void hdmi_reset_video_state(void)
{
	SET_H_VIDEO_FSM(MAIN_FSM_HDMI_WAIT_SYNC);

	SET_H_INTERLACE(0);
	SET_H_MODE(MODE_HDMI);
	SET_H_COLOR_DEPTH(HDMI_COLOR_DEPTH_8B);
	SET_H_COLOR_SPACE(COLOR_RGB);

	SET_H_3DFORMAT(HDMI3D_2D_ONLY);
}

unsigned char hdmi_get_video_state(void)
{
	return GET_H_VIDEO_FSM();
}

void hdmi_reset_meas_counter(void)
{
	hdmi_rx.meas_retry_cnt = 0;
}

void hdmi_check_crc_0(void)
{
	if (lib_hdmi_read_crc())
		return;

	HDMI_PRINTF("CRC=00000000000, cs=%d\n", GET_H_COLOR_SPACE());

	if (GET_H_COLOR_SPACE() == COLOR_YUV420) {
		lib_hdmi_420_en(0);
		HDMI_DELAYMS(20);
		lib_hdmi_420_en(1);
	}
}


#if HDMI2p0
void hdmi2p0_check_tmds_config(void)
{
	unsigned char cfg, hail_hydra;

	cfg = lib_hdmi2p0_get_tmds_config();

	hail_hydra = (hdmi_rx.scramble_flag|hdmi_rx.clock40x_flag);


	if (hdmi_rx.hdmi2p0_tmds_toggle_flag > 10) {
		hdmi_rx.scramble_flag = ((cfg&_BIT0) != 0);
		hdmi_rx.clock40x_flag = ((cfg&_BIT1) != 0);
	} else if (hdmi_rx.hdmi2p0_tmds_toggle_flag > 2) {
		hdmi_rx.scramble_flag = ((cfg&_BIT0) == 0);
		hdmi_rx.clock40x_flag = ((cfg&_BIT1) == 0);
		//HDMI_PRINTF("HDMI2.0 swap\n");
	} else {
		hdmi_rx.scramble_flag = ((cfg&_BIT0) != 0);
		hdmi_rx.clock40x_flag = ((cfg&_BIT1) != 0);
	}

	if (!hail_hydra && (hdmi_rx.scramble_flag||hdmi_rx.clock40x_flag)) {
		HDMI_PRINTF("HDMI2.0 SCDC: got it\n");
	}

}

unsigned char hdmi2p0_get_scramble_flag(void)
{
	return hdmi_rx.scramble_flag;
}

unsigned char hdmi2p0_get_clock40x_flag(void)
{
	return hdmi_rx.clock40x_flag;
}

void hdmi2p0_fource_6g(void)
{
	hdmi_rx.scramble_flag = 1;
	hdmi_rx.clock40x_flag = 1;
}

void hdmi2p0_detect_config(void)
{
	lib_hdmi2p0_scramble_enable(hdmi_rx.scramble_flag);

}

void hdmi2p0_reset_scdc_toggle(void)
{
	hdmi_rx.hdmi2p0_tmds_toggle_flag = 0;
}

void hdmi2p0_inc_scdc_toggle(void)
{
	if(hdmi_rx.hdmi2p0_tmds_toggle_flag >= 0xfe)
		hdmi_rx.hdmi2p0_tmds_toggle_flag = 0;
	else
	hdmi_rx.hdmi2p0_tmds_toggle_flag++;
}


#endif

unsigned char hdmi_get_timing(HDMI_TIMING_T *ptiming)
{
	if (GET_H_VIDEO_FSM() == MAIN_FSM_HDMI_VIDEO_READY) {
		memcpy(ptiming, &hdmi_rx.timing_t, sizeof(HDMI_TIMING_T));
		return TRUE;
	} else {
		memset(ptiming, 0, sizeof(HDMI_TIMING_T));
		return FALSE;
	}

	return FALSE;
}

unsigned char hdmi_get_interlace_conti_mode(void)
{
unsigned char is_intc= 0;

	if (hdmi_rx.vs_cnt > 3) {
		is_intc = lib_hdmi_get_is_interlace(HDMI_MS_DIRECT);
		lib_hdmi_clear_interlace_reg();
		hdmi_rx.vs_cnt = 0;
		return is_intc;
	} else {
		lib_hdmi_vsync_checked();
		hdmi_rx.vs_cnt++;
		return hdmi_rx.timing_t.is_interlace;
	}

}

unsigned char hdmi_get_is_interlace(void)
{
	return GET_H_INTERLACE();
}

unsigned char hdmi_get_hdmi_mode_reg(void)
{
#if HDMI2p0
	if (hdmi2p0_get_clock40x_flag() || hdmi2p0_get_scramble_flag()) {
		return TRUE;
	}
#endif

	return lib_hdmi_is_hdmi_mode();

}

unsigned char hdmi_get_hdmi_mode(void)
{
	return GET_H_MODE();
}

unsigned char hdmi_get_colordepth(void)
{
	return GET_H_COLOR_DEPTH();
}

unsigned char hdmi_get_colorspace_reg(void)
{
	if (!hdmi_get_hdmi_mode_reg()) {
		return COLOR_RGB;
	}

	return lib_hdmi_get_colorspace();
}

unsigned char hdmi_get_colorspace(void)
{
	if (GET_H_COLOR_SPACE() == COLOR_YUV420)
		return COLOR_YUV444;
	else
		return GET_H_COLOR_SPACE();

}

unsigned char hdmi_get_video_format_reg(void)
{
	if (hdmi_rx.vsi_t.Length == 0)
		return HVF_NO;

	return lib_hdmi_get_video_format();
}

unsigned char hdmi_get_video_format(void)
{
	return GET_H_VIDEO_FORMAT();
}

unsigned char hdmi_get_3d_structure_reg(void)
{
	if (hdmi_rx.vsi_t.Length == 0)
		return HDMI3D_2D_ONLY;

	if (lib_hdmi_get_video_format() != HVF_3D)
		return HDMI3D_2D_ONLY;
	else
		return lib_hdmi_get_3d_structure();
}


unsigned char hdmi_get_3d_structure(void)
{
	if (hdmi_rx.vsi_t.Length == 0)
		return HDMI3D_2D_ONLY;

	return GET_H_3DFORMAT();
}

unsigned char hdmi_get_colorimetry(void)
{
	if (hdmi_rx.avi_t.len == 0) return 0;

	return (hdmi_rx.avi_t.C == 3)?
		(hdmi_rx.avi_t.EC+HDMI_COLORIMETRY_XYYCC601):hdmi_rx.avi_t.C;
}

unsigned char hdmi_get_color_range(void)
{
	if (hdmi_rx.avi_t.len == 0)
		return 0;

	if (hdmi_rx.avi_t.Y == 0) {	// RGB
		return hdmi_rx.avi_t.Q;
	} else if (hdmi_rx.avi_t.Y == 1 || hdmi_rx.avi_t.Y == 2 || hdmi_rx.avi_t.Y == 3) {	// YUV
		return (hdmi_rx.avi_t.YQ<3)?(hdmi_rx.avi_t.YQ+1):MODE_RAG_DEFAULT;
	} else {
		return MODE_RAG_DEFAULT;
	}
}

unsigned char hdmi_get_audio_coding_type(unsigned char *code_type)
{
	if (hdmi_rx.audiopkt_t.len == 0)
		return 0;

	*code_type = hdmi_rx.audiopkt_t.CT;
	if (hdmi_rx.audiopkt_t.CT == 0)
		*code_type = lib_hdmi_audio_get_channel_status15_0(0xFF00, 8);

	return 1;
}

unsigned int hdmi_get_tmds_clockx10(void)
{
	if (GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE)
		return 0;
	return (lib_hdmi_get_clock()*270)>>8;
}

void hdmi_fix_green_line(void) //k3l need to check
{
	if (GET_H_COLOR_SPACE() == COLOR_RGB)
		lib_hdmi_tmds_out_ctrl(1, 0, 0, 0);
	else
		lib_hdmi_tmds_out_ctrl(0, 0x8000, 0x1000, 0x8000);
}


void hdmi_audio_var_init(void)
{
	hdmi_rx.audio_t.coding_type= 0;
	hdmi_rx.audio_t.audio_freq = 0;
	hdmi_rx.audio_t.sr_mismatch_cnt = 0;
	hdmi_rx.audio_t.track_mode_tgl = 0;
}

unsigned char hdmi_audio_is_pll_ready(void)
{
	unsigned char timeout;

	for (timeout = 0; timeout < 5; timeout++) {
		lib_hdmi_audio_clear_phase_error();
		HDMI_DELAYMS(20);
		if (!(lib_hdmi_audio_is_pll_unlock()||lib_hdmi_audio_is_fifo_overflow()||lib_hdmi_audio_is_fifo_underflow()))
			return TRUE;
		lib_hdmi_audio_wclr_pll_unlock();
		lib_hdmi_audio_wclr_fifo_overflow();
		lib_hdmi_audio_wclr_fifo_underflow();
	}

	HDMI_PRINTF("[ERR] FIFO Unstable = %x\n", hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	return FALSE;

}

unsigned char hdmi_audio_set_pll(unsigned int freq, unsigned char ucACR_N,HDMI_AUDIO_TRACK_MODE track_mode)
{
	u_int8_t i;
	int timeout = 10;
	u_int32_t I_Code = 0, S = 0;
	unsigned int clk;

	for (i = 0; i < 7; i++) {
		if (hdmi_audiopll_param[i].freq == freq)
			goto PLL_SETTING;
	}
	HDMI_PRINTF( "Unsupport audio freq = %d\n", freq);
	return FALSE;

PLL_SETTING:

	clk = hdmi_rx.timing_t.tmds_clk_b;

	/* (2)audio output enable = auto mode */
	hdmi_rx_reg_mask32(HDMI_AFCR, ~_BIT6, _BIT6, HDMI_RX_MAC);

	/* (3)Disable trend and boundary tracking */
	hdmi_rx_reg_mask32(HDMI_WDCR0, ~HDMI_WDCR0_bt_track_en_mask, 0x0, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_PSCR, ~(_BIT3 |_BIT2), 0x0, HDMI_RX_MAC);
	/* Update Double Buffer */
	hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4 , _BIT4, HDMI_RX_MAC);

	/* (4)FSM back to Pre-mode */
	hdmi_rx_reg_mask32(HDMI_AVMCR , ~_BIT5, 0x0, HDMI_RX_MAC);

	/* (5)Disable N/CTS tracking */
	/* CTS has glitch not to tracking disable */
	hdmi_rx_reg_mask32(HDMI_AUDIO_CTS_UP_BOUND, ~_BIT20, 0x0, HDMI_RX_MAC);
	/* N has glitch not to tracking disable */
	hdmi_rx_reg_mask32(HDMI_AUDIO_N_UP_BOUND, ~_BIT20, 0x0, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_PSCR, ~_BIT4, 0x00, HDMI_RX_MAC);
	/* Update Double Buffer */
	hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);

	/*(6)Disable SDM*/
	hdmi_rx_reg_mask32(HDMI_AAPNR, ~_BIT1, 0x0, HDMI_RX_MAC);

	/*(7)Disable PLL*/
	hdmi_rx_reg_mask32(HDMI_APLLCR1, ~HDMI_APLLCR1_dpll_rstb_mask, 0x0, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~(HDMI_APLLCR1_dpll_freeze_mask|HDMI_APLLCR1_dpll_vcorstb_mask|HDMI_APLLCR1_dpll_pow_mask),
		(HDMI_APLLCR1_dpll_freeze_mask ), HDMI_RX_MAC);

	/* (8)resetS &S1 code to avoid dead lock */
	/* PLL output clk sel from crystal */
	hdmi_rx_reg_mask32(HDMI_CMCR,  ~( _BIT6|_BIT5), 0x0, HDMI_RX_MAC);
	/* S1 & S2 code clear to 0 , to avoid dead lock */
	hdmi_rx_reg_write32(HDMI_SCAPR, 0x00, HDMI_RX_MAC);
	/* Update Double Buffer */
	hdmi_rx_reg_mask32(HDMI_CMCR,~_BIT4 , _BIT4, HDMI_RX_MAC);
    HDMI_DELAYUS(10);
    /* PLL output clk sel from VCO */
	hdmi_rx_reg_mask32(HDMI_CMCR, ~( _BIT6|_BIT5), (_BIT6), HDMI_RX_MAC);
	/* Update Double Buffer */
	hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);

	/*(9)D code*/
	hdmi_rx_reg_write32(HDMI_DCAPR0,
		(hdmi_audiopll_param[i].D_HighByte << 8) | hdmi_audiopll_param[i].D_LowByte, HDMI_RX_MAC);
	/* Enable Double Buffer for K/M/S/D/O */
	hdmi_rx_reg_mask32(HDMI_CMCR, ~(HDMI_CMCR_dbdcb_mask), HDMI_CMCR_dbdcb(1), HDMI_RX_MAC);

	/*(10)Initial PLL*/
	/* Set audio PLL N code */
	if (hdmi_audiopll_param[i].N < 2) {
		hdmi_rx_reg_mask32(HDMI_APLLCR0,
			~(HDMI_APLLCR0_dpll_m_mask | HDMI_APLLCR0_dpll_o_mask | HDMI_APLLCR0_dpll_bpsin_mask | HDMI_APLLCR0_dpll_n_mask), 	
			HDMI_APLLCR0_dpll_m(hdmi_audiopll_param[i].M - 2) | HDMI_APLLCR0_dpll_o(hdmi_audiopll_param[i].O) |
			HDMI_APLLCR0_dpll_bpsin(1) | HDMI_APLLCR0_dpll_n(0), HDMI_RX_MAC);
	} else {
		hdmi_rx_reg_mask32(HDMI_APLLCR0,
			~(HDMI_APLLCR0_dpll_m_mask |HDMI_APLLCR0_dpll_o_mask |HDMI_APLLCR0_dpll_bpsin_mask | HDMI_APLLCR0_dpll_n_mask),
			HDMI_APLLCR0_dpll_m(hdmi_audiopll_param[i].M - 2) | HDMI_APLLCR0_dpll_o(hdmi_audiopll_param[i].O) |
			HDMI_APLLCR0_dpll_bpsin(0) | HDMI_APLLCR0_dpll_n(hdmi_audiopll_param[i].N-2), HDMI_RX_MAC);
	}
	/* Enable Double Buffer for K/M/S/D/O */
	hdmi_rx_reg_mask32(HDMI_CMCR,~(HDMI_CMCR_dbdcb_mask),HDMI_CMCR_dbdcb(1), HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDMI_SCAPR,
		(hdmi_audiopll_param[i].S1) ? ((hdmi_audiopll_param[i].S / 2) | 0x80) : (hdmi_audiopll_param[i].S / 2),
		HDMI_RX_MAC);
	/* S1 code */
	hdmi_rx_reg_write32(HDMI_PRESET_S_CODE1, 0xf800, HDMI_RX_MAC);
	/* Set Icp 4u */
	hdmi_rx_reg_mask32(HDMI_APLLCR0, ~(_BIT2|_BIT1|_BIT0), _BIT0, HDMI_RX_MAC);
	/* Set RS=26k */
	hdmi_rx_reg_mask32(HDMI_APLLCR0,
		~(_BIT5|_BIT4|_BIT3), (_BIT5| _BIT3), HDMI_RX_MAC);
	/* Set CS=42pf */
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~(HDMI_APLLCR1_dpll_CS_MASK), (HDMI_APLLCR1_dpll_CS_35P), HDMI_RX_MAC);
	/* Set CP=1.5pf */
	hdmi_rx_reg_mask32(HDMI_APLLCR1, ~(_BIT22|_BIT21), _BIT21, HDMI_RX_MAC);
	/* Enable PLL */
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~(HDMI_APLLCR1_dpll_stoppsw_mask | HDMI_APLLCR1_dpll_pow_mask),
		(HDMI_APLLCR1_dpll_pow_mask | HDMI_APLLCR1_dpll_stoppsw_mask),
		HDMI_RX_MAC);
	/* RST */
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~(HDMI_APLLCR1_dpll_vcorstb_mask), (HDMI_APLLCR1_dpll_vcorstb_mask), HDMI_RX_MAC);

	HDMI_PRINTF(" m = %x\n o = %x\n s = %x\n ",
		hdmi_audiopll_param[i].M, hdmi_audiopll_param[i].O, hdmi_audiopll_param[i].S);
	/* Wait PLL Stable */
	HDMI_DELAYUS(1);
	/* PLL un-freeze */
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~HDMI_APLLCR1_dpll_rstb_mask, HDMI_APLLCR1_dpll_rstb_mask, HDMI_RX_MAC);
	/* Wait PLL stable */
	HDMI_DELAYUS(40);
	hdmi_rx_reg_mask32(HDMI_APLLCR1,
		~HDMI_APLLCR1_dpll_freeze_mask, 0x0, HDMI_RX_MAC);

	/* (11)Enable SDM */
	hdmi_rx_reg_mask32(HDMI_AAPNR,
		~HDMI_AAPNR_esdm_mask, HDMI_AAPNR_esdm_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);

	if (track_mode == HDMI_AUDIO_N_CTS_TREND_BOUND) {
		HDMI_PRINTF("\n *****N/CTS Trend& Boundary Tracking*****\n");
		/*
		 * (12)Enable N/CTS tracking
		 * Modify N/CTS tracking parameter  USER:kistlin DATE:2011/08/04
		 * for phase error count source Fpec = Fdds = Fvco/4
		 * PEpec x Tpec = delta(Tvco)xNxSxPLLO = Tvco(1/8)(D[15:0]/2^16)xNxSxPLLO
		 * D[15:0] = PEpec x Tpec /[Tvco(1/8)(1//2^16)xNxSxPLLO]
		 * and D[15:0] = PEpec x (1/8)Icode
		 * Icode calculate I code =2^24/(N*S*PLLO)
		 *
		 * for phase error count source = fvco/4,fdds
		 * Icode calculate I code =2*2048*2^10/(N*S*PLLO)
		 */
		if (hdmi_audiopll_param[i].S1)
			S = hdmi_audiopll_param[i].S*2;
		else
			S = hdmi_audiopll_param[i].S;

		HDMI_PRINTF("S = %d , ACR_N=%d, hdmi_audiopll_param[i].O = %d\n",
			S, ucACR_N, hdmi_audiopll_param[i].O );

		if (ucACR_N) {
			I_Code =16*1024*1024/(ucACR_N*S*(hdmi_audiopll_param[i].O<<1));
		} else
			I_Code = 0x02;

		/* HDMI_PRINTF( "I Code = %d\n", I_Code); */
		/* HDMI_PRINTF( "tmp1 = %d\n", tmp1); */

		/* Set I code of Ncts[15:8] */
		hdmi_rx_reg_write32(HDMI_ICPSNCR0, I_Code, HDMI_RX_MAC);
		/* Set P code of Ncts [15:8] */
		hdmi_rx_reg_write32(HDMI_PCPSNCR0, 0x0, HDMI_RX_MAC);
		/* N_CTS tracking re-enable toggle function enable */
		hdmi_rx_reg_mask32(HDMI_NPECR,
			~HDMI_NPECR_ncts_re_enable_off_en_mask,
			HDMI_NPECR_ncts_re_enable_off_en_mask, HDMI_RX_MAC);
		/* Enable N_CTS tracking & set FIFO depth */
		hdmi_rx_reg_write32(HDMI_PSCR, 0x92, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);

		/* Phase error threshold */
		hdmi_rx_reg_write32(HDMI_PETR, 0x1e, HDMI_RX_MAC);
		for (timeout = 0; timeout < 25; timeout++) {
			hdmi_rx_reg_mask32(HDMI_SR, ~_BIT3, _BIT3, HDMI_RX_MAC);
			hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
			HDMI_DELAYMS(20);
			if ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
			HDMI_PRINTF("PLL 1st check not lock = %x\n", hdmi_rx_reg_read32(HDMI_NCPER, HDMI_RX_MAC));
		else
			HDMI_PRINTF("PLL 1st check lock count = %d\n", timeout);

		/* Sisable N_CTS tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR, ~HDMI_PSCR_etcn_mask, 0, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR,
			~HDMI_CMCR_dbdcb_mask, HDMI_CMCR_dbdcb_mask, HDMI_RX_MAC);
		/* N_CTS tracking re-enable toggle function disable */
		hdmi_rx_reg_mask32(HDMI_NPECR,
			~HDMI_NPECR_ncts_re_enable_off_en_mask, 0, HDMI_RX_MAC);
		/* Set I code of Ncts[15:8] */
		hdmi_rx_reg_write32(HDMI_ICPSNCR0,
			HDMI_ICPSNCR0_ich(0)|HDMI_ICPSNCR0_icl(0x02), HDMI_RX_MAC);
		/* Set P code of Ncts [15:8] */
		hdmi_rx_reg_write32(HDMI_PCPSNCR0,
			HDMI_PCPSNCR0_pch(0x20)|HDMI_PCPSNCR0_pcl(0x0), HDMI_RX_MAC);
		/* Enable N_CTS tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR,
			~HDMI_PSCR_etcn_mask, HDMI_PSCR_etcn_mask, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR,
			~HDMI_CMCR_dbdcb_mask, HDMI_CMCR_dbdcb_mask, HDMI_RX_MAC);
		/* N&CTS boundary set */
		lib_hdmi_audio_cts_bound(clk);
		lib_hdmi_audio_n_bound(freq);

		/* CTS has glitch not to tracking enable */
		hdmi_rx_reg_mask32(HDMI_AUDIO_CTS_UP_BOUND, ~_BIT20, _BIT20, HDMI_RX_MAC);
		/* N has glitch not to tracking enable */
		hdmi_rx_reg_mask32(HDMI_AUDIO_N_UP_BOUND, ~_BIT20, _BIT20, HDMI_RX_MAC);

		/*(13)Wait PLL lock by N&CTS tracking*/
		hdmi_rx_reg_write32(HDMI_PETR, 0x1e, HDMI_RX_MAC);/* Phase error threshold */
		for (timeout = 0; timeout < 25; timeout++) {
			hdmi_rx_reg_mask32(HDMI_SR, ~_BIT3, _BIT3, HDMI_RX_MAC);
			hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
			HDMI_DELAYMS(20);
			if ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & (_BIT3)) == 0)
				break;
		}

		if (timeout == 25)
			HDMI_PRINTF("PLL not lock = %x\n", hdmi_rx_reg_read32(HDMI_NCPER, HDMI_RX_MAC));
		else
			HDMI_PRINTF("PLL lock count = %d\n", timeout);

		/*(14)FSM Initial*/
		hdmi_rx_reg_write32(HDMI_FBR, 0x74, HDMI_RX_MAC);
		/* FSM entry Pre-mode (AOC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT6, _BIT6, HDMI_RX_MAC);
		/* FSM entry next step (AOMC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT5 ,_BIT5, HDMI_RX_MAC);
		/* Wait fifo to target fifo level */
		HDMI_DELAYUS(1);

		/*(15)Enable trend and boundary tracking*/
		/* Set I code  of trend [15:8] */
		hdmi_rx_reg_write32(HDMI_ICTPSR0, 0x0005, HDMI_RX_MAC);
		/* Set P code of trend [15:8] */
		hdmi_rx_reg_write32(HDMI_PCTPSR0, 0x02FF, HDMI_RX_MAC);
		/* Set I code of bnd [15:8] */
		hdmi_rx_reg_write32(HDMI_ICBPSR0, 0x0005, HDMI_RX_MAC);
		/* Set P code of bnd [15:8] */
		hdmi_rx_reg_write32(HDMI_PCBPSR0, 0x02FF, HDMI_RX_MAC);
		/* Set Boundary Tracking Update Response Time */
		hdmi_rx_reg_write32(HDMI_STBPR, 0x01, HDMI_RX_MAC);
		/* Enable trend and boundary tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR, ~(_BIT3|_BIT2), (_BIT3|_BIT2), HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);
		HDMI_DELAYMS(20);
		/* Enable trend and boundary tracking */
		hdmi_rx_reg_mask32(HDMI_WDCR0,
			~HDMI_WDCR0_bt_track_en_mask,
			HDMI_WDCR0_bt_track_en_mask, HDMI_RX_MAC);
	} else if(track_mode == HDMI_AUDIO_TREND_BOUND) {
		HDMI_PRINTF("\n ***** TREND_BOUND Tracking*****\n");
		/* (14)FSM Initial */
		hdmi_rx_reg_write32(HDMI_FBR, 0x74, HDMI_RX_MAC);
		/* FSM entry Pre-mode (AOC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT6, _BIT6, HDMI_RX_MAC);
		/* FSM entry next step (AOMC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT5, _BIT5, HDMI_RX_MAC);
		/* Wait fifo to target fifo level */
		HDMI_DELAYUS(1);

		/* (15)Enable trend and boundary tracking */
		/* Set I code  of trend [15:8] */
		hdmi_rx_reg_write32(HDMI_ICTPSR0, 0x0005, HDMI_RX_MAC);
		/* Set P code of trend [15:8] */
		hdmi_rx_reg_write32(HDMI_PCTPSR0, 0x02FF, HDMI_RX_MAC);
		/* Set I code of bnd [15:8] */
		hdmi_rx_reg_write32(HDMI_ICBPSR0, 0x0001, HDMI_RX_MAC);
		/* Set P code of bnd [15:8] */
		hdmi_rx_reg_write32(HDMI_PCBPSR0, 0x2000, HDMI_RX_MAC);
		/* Set Boundary Tracking Update Response Time */
		hdmi_rx_reg_write32(HDMI_STBPR, 0x01, HDMI_RX_MAC);
		/* FIFO depth tracking */
		hdmi_rx_reg_write32(HDMI_PSCR,
			HDMI_PSCR_fdint(4)|HDMI_PSCR_etcn(0)|HDMI_PSCR_etfd(1)|
			HDMI_PSCR_etfbc(1)|HDMI_PSCR_pecs(2),
			HDMI_RX_MAC);
		/* <1>Enable trend and boundary tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR, ~(_BIT3|_BIT2), (_BIT3|_BIT2), HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);
		HDMI_DELAYMS(20);
		/* <2>Enable trend and boundary tracking */
		hdmi_rx_reg_mask32(HDMI_WDCR0,
			~HDMI_WDCR0_bt_track_en_mask, HDMI_WDCR0_bt_track_en_mask, HDMI_RX_MAC);

	} else {
		/*  H/W N/CTS Tracking */
		HDMI_PRINTF("\n ***** N/CTS Tracking*****\n");
		/*(12)Enable N/CTS tracking*/
		if (hdmi_audiopll_param[i].S1)
			S = hdmi_audiopll_param[i].S*2;
		else
			S = hdmi_audiopll_param[i].S;

		HDMI_PRINTF("S = %d , ACR_N=%d, hdmi_audiopll_param[i].O = %d\n",
			S, ucACR_N, hdmi_audiopll_param[i].O);

		if (ucACR_N)
			I_Code =16*1024*1024/(ucACR_N*S*(hdmi_audiopll_param[i].O<<1));
		else
			I_Code = 0x02;

		/* HDMI_PRINTF("I Code = %d\n", I_Code); */
		/* HDMI_PRINTF("tmp1 = %d\n", tmp1); */

		/* Set I code of Ncts[15:8] */
		hdmi_rx_reg_write32(HDMI_ICPSNCR0, I_Code, HDMI_RX_MAC);
		/* Set P code of Ncts [15:8] */
		hdmi_rx_reg_write32(HDMI_PCPSNCR0, 0x0000, HDMI_RX_MAC);
		/* N_CTS tracking re-enable toggle function enable */
		hdmi_rx_reg_mask32(HDMI_NPECR,
			~HDMI_NPECR_ncts_re_enable_off_en_mask,
			HDMI_NPECR_ncts_re_enable_off_en_mask, HDMI_RX_MAC);
		/* Enable N_CTS tracking & set FIFO depth */
		hdmi_rx_reg_write32(HDMI_PSCR, 0x92, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);

		/* Phase error threshold */
		hdmi_rx_reg_write32(HDMI_PETR, 0x1e, HDMI_RX_MAC);
		for (timeout = 0; timeout < 25; timeout++) {
			hdmi_rx_reg_mask32(HDMI_SR, ~_BIT3, _BIT3, HDMI_RX_MAC);
			hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
			HDMI_DELAYMS(20);
			if ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & _BIT3) == 0)
				break;
		}

		if (timeout == 25)
			HDMI_PRINTF("PLL 1st check not lock = %x\n", hdmi_rx_reg_read32(HDMI_NCPER, HDMI_RX_MAC));
		else
			HDMI_PRINTF("PLL 1st check lock count = %d\n", timeout);

		/* Disable N_CTS tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR, ~_BIT4, 0, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4, _BIT4, HDMI_RX_MAC);
		/* N_CTS tracking re-enable toggle function disable */
		hdmi_rx_reg_mask32(HDMI_NPECR,
			~HDMI_NPECR_ncts_re_enable_off_en_mask, 0, HDMI_RX_MAC);
		/* Set I code of Ncts[15:8] */
		hdmi_rx_reg_write32(HDMI_ICPSNCR0, 0x0002, HDMI_RX_MAC);
		/* Set P code of Ncts [15:8] */
		hdmi_rx_reg_write32(HDMI_PCPSNCR0, 0x2000, HDMI_RX_MAC);
		/* Enable N_CTS tracking */
		hdmi_rx_reg_mask32(HDMI_PSCR, ~_BIT4, _BIT4, HDMI_RX_MAC);
		/* Update Double Buffer */
		hdmi_rx_reg_mask32(HDMI_CMCR, ~_BIT4 , _BIT4, HDMI_RX_MAC);

		/* N&CTS boundary set */
		lib_hdmi_audio_cts_bound(clk);
		lib_hdmi_audio_n_bound(freq);

		/* CTS has glitch not to tracking enable */
		hdmi_rx_reg_mask32(HDMI_AUDIO_CTS_UP_BOUND, ~_BIT20, _BIT20, HDMI_RX_MAC);
		/* N has glitch not to tracking enable */
		hdmi_rx_reg_mask32(HDMI_AUDIO_N_UP_BOUND, ~_BIT20, _BIT20, HDMI_RX_MAC);

		/*(13)Wait PLL lock by N&CTS tracking*/
		/* Phase error threshold */
		hdmi_rx_reg_write32(HDMI_PETR, 0x1e, HDMI_RX_MAC);
		for (timeout = 0; timeout < 25; timeout++) {
			hdmi_rx_reg_mask32(HDMI_SR, ~_BIT3, _BIT3, HDMI_RX_MAC);
			hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
			HDMI_DELAYMS(20);
			if ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & _BIT3) == 0)
				break;
		}

		if (timeout == 25)
			HDMI_PRINTF("PLL not lock = %x\n", hdmi_rx_reg_read32(HDMI_NCPER, HDMI_RX_MAC));
		else
			HDMI_PRINTF("PLL lock count = %d\n", timeout);

		/* (14)FSM Initial */
		/* Target FIFO depth = 14 ,Boundary address distance = 7 */
		hdmi_rx_reg_write32(HDMI_FBR, 0x77, HDMI_RX_MAC);
		/* FSM entry Pre-mode (AOC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT6, _BIT6, HDMI_RX_MAC);
		/* FSM entry next step (AOMC=1) */
		hdmi_rx_reg_mask32(HDMI_AVMCR, ~_BIT5, _BIT5, HDMI_RX_MAC);
		/* Wait fifo to target fifo level */
		HDMI_DELAYUS(1);
	}

#if 0
	/* (16)Wait FIFO stable */
	for (timeout = 0; timeout < 5; timeout++) {
		hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
		HDMI_DELAYMS(20);
		if ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & (_BIT3|_BIT2|_BIT1)) == 0)
			break;
		hdmi_rx_reg_mask32(HDMI_SR, ~(_BIT3|_BIT2|_BIT1), (_BIT3|_BIT2|_BIT1), HDMI_RX_MAC);
	}

	if (timeout == 5)
		HDMI_PRINTF("FIFO Unstable = %x \n", hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	else
		HDMI_PRINTF("FIFO timeout count = %d\n", timeout);

	HDMI_PRINTF("HDMI_AVMCR_reg = %x\n", hdmi_rx_reg_read32(HDMI_AVMCR, HDMI_RX_MAC));
#endif
	return TRUE;

}

unsigned int hdmi_audio_freq_correction(unsigned int freq)
{
	const unsigned int b_ratio = 1000;

	freq *= 10;
	if((freq >= (31700*b_ratio/100)) && (freq <= (32300*b_ratio/100)))
		freq = 32000;
	else if((freq >= (43500*b_ratio/100)) && (freq <= (44600*b_ratio/100)))
		freq = 44100;
	else if((freq >= 47500*b_ratio/100) && (freq <= (48500*b_ratio/100)))
		freq = 48000;
	else if((freq >= (87700*b_ratio/100)) && (freq <= (88700*b_ratio/100)))
		freq = 88200;
	else if((freq >= (95500*b_ratio/100)) && (freq <= (96500*b_ratio/100)))
		freq = 96000;
	else if((freq >= (175400*b_ratio/100)) && (freq <= (177400*b_ratio/100)))
		freq = 176400;
	else if((freq >= (191000*b_ratio/100)) && (freq <= (193000*b_ratio/100)))
		freq = 192000;
#if AUDIO_OVER_192K
	else if ((freq >= (351800*b_ratio/100)) && (freq <= (353800*b_ratio/100)))
		freq = 352800;
	else if ((freq >= (383000*b_ratio/100)) && (freq <= (385000*b_ratio/100)))
		freq = 384000;
	else if ((freq >= (704600*b_ratio/100)) && (freq <= (706600*b_ratio/100)))
		freq = 705600;
	else if ((freq >= (767000*b_ratio/100)) && (freq <= (769000*b_ratio/100)))
		freq = 768000;
	else if ((freq >= (1401200*b_ratio/100)) && (freq <= (1421200*b_ratio/100)))
		freq = 1411200;
	else if ((freq >= (1526000*b_ratio/100))&& (freq <= (1546000*b_ratio/100)))
		freq = 1536000;
#endif
	else
		freq = 0;


	return freq;
}

void hdmi_audio_get_freq(HDMI_AUDIO_FREQ_T *freq, HDMI_AUDIO_TRACK_MODE *track_mode)
{

	unsigned long cts, n, b;
	unsigned char count = 0;

	freq->ACR_freq = 0;
	freq->AudioInfo_freq = 0;
	freq->SPDIF_freq = 0;
	freq->ACR_N = 0;

	/* Set trigger to get CTS&N and LPCM Channel Status Info */

	/* Start Pop up N_CTS value */
	lib_hdmi_audio_pop_n_cts();

	/* Clear Info Frame update indicator */
	lib_hdmi_audio_clear_fs();

	if (!hdmi_audio_wait_acr())
		HDMI_PRINTF("No N/CTS packet\n");

	for (count = 0; count < 15; count++) {
		if (lib_hdmi_audio_pop_n_cts_done() && lib_hdmi_audio_fs_from_cs())
			break;

		HDMI_DELAYUS(10000);
	}

	if (count >= 15)
		HDMI_PRINTF("[ERR] POP UP TIME OUT\n");

	HDMI_PRINTF("POP UP TIME %d\n",count);

	/* debug options: bit0 or bit1 */
	if (lib_hdmi_audio_fs_from_cs())
		freq->SPDIF_freq = AUDIO_CHANNEL_STATUS[lib_hdmi_audio_get_freq_from_cs()];

	HDMI_PRINTF("*************** SPDIF freq=%ld\n", freq->SPDIF_freq);

	/* Get Audio Frequency from CTS&N */

	cts = lib_hdmi_audio_get_cts();
	n = lib_hdmi_audio_get_n();
	b = hdmi_rx.timing_t.tmds_clk_b;
	freq->ACR_N = n;

	HDMI_PRINTF("(cts=%ld)(n=%ld)(b=%ld)\n", cts, n, b);

	if (cts == 0 || n == 0 || b == 0)
		return;

	/*
	 * 128fs = 1024/b * fx * N / CTS  =>  fs = (1024 * fx *N)/(128 * b * CTS) = (8 * fx *N)/(b*CTS)
	 * calculate freq in 0.1kHz unit
	 * freq = (unsigned long)8 * 2 * 10000 * HDMI_RTD_XTAL/ cts * n / ((unsigned long)b * 1000);
	 */
	freq->ACR_freq = ((((270000 * b)/256)/128) * n) / (cts);
	freq->ACR_freq *= 100;
	freq->ACR_freq = hdmi_audio_freq_correction(freq->ACR_freq);

	/* HBR mode */
	if (lib_hdmi_audio_get_hbr_manual_mode()) {
		if (freq->ACR_freq != 192000) {
			HDMI_PRINTF("WARNING!!! HBR need to equal 192K(%ld)\n", freq->ACR_freq);
			freq->ACR_freq = 192000;
		}
	}

	*track_mode = HDMI_AUDIO_N_CTS_TREND_BOUND;

}

unsigned char hdmi_audio_detect(void)
{
	#define MATCH_THRD	15
	unsigned char result = FALSE;
	HDMI_AUDIO_FREQ_T t, t2;
	HDMI_AUDIO_TRACK_MODE track_mode;
	static unsigned int spdif_freq;

	if (((GET_H_VIDEO_FSM() != MAIN_FSM_HDMI_DISPLAY_ON) && (GET_H_VIDEO_FSM() != MAIN_FSM_HDMI_VIDEO_READY)) ||
		(lib_hdmi_get_avmute() && !lib_hdmi_get_bch_2bit_error()) ||
		(hdmi_rx.timing_t.tmds_clk_b < VALID_MIN_CLOCK)) {

		lib_hdmi_audio_output(0);
		SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		return FALSE;
	}

	switch (GET_H_AUDIO_FSM()) {
	case AUDIO_FSM_AUDIO_START:
		/* HDMI_PRINTF("AUDIO_FSM_AUDIO_START\n"); */
		SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		lib_hdmi_audio_init();

		lib_hdmi_audio_set_hbr_manual_mode(0, 0);
		hdmi_rx.audio_t.sr_mismatch_cnt = 0;

		/* Wait for audio sample packet */
#if AUDIO_HBR_DETECT
		if (!hdmi_audio_wait_2_samples())
			break;
#else
		if (!hdmi_audio_wait_sample())
			break;
#endif

		SET_H_AUDIO_FSM(AUDIO_FSM_FREQ_DETECT);

		break;
	case AUDIO_FSM_FREQ_DETECT:
		HDMI_PRINTF("AUDIO_FSM_FREQ_DETECT\n");

#ifdef HDMI_VIDEO_WD_ENABLE
		hdmi_watchdog_apply(_DISABLE, HDMI_WD_AUDIO_COND);
#endif

		hdmi_audio_get_freq(&t, &track_mode);
		hdmi_audio_get_freq(&t2, &track_mode);
		HDMI_PRINTF("Hdmi_GetAudioFreq t=%ld\n", t.ACR_freq);
		HDMI_PRINTF("Hdmi_GetAudioFreq t2=%ld\n", t2.ACR_freq);

		if ((t.ACR_freq != 0) && (t.ACR_freq == t2.ACR_freq)) {
			if (HDMI_ABS(t.ACR_freq, t.SPDIF_freq) > (t.ACR_freq/20)) {

				HDMI_PRINTF("[HDMI] Freq in N/CTS and CS are not match!!(cnt=%d)\n",
					hdmi_rx.audio_t.sr_mismatch_cnt);

				if (lib_hdmi_audio_get_hbr_manual_mode()) {
					/* HBRr mode */
					HDMI_PRINTF("Audio HBR mode\n");
				} else{
					if (hdmi_rx.audio_t.sr_mismatch_cnt < MATCH_THRD) {
						hdmi_rx.audio_t.sr_mismatch_cnt++;
						break;
					} else {
						hdmi_rx.audio_t.sr_mismatch_cnt = 0;
					}
				}
			}

			if (hdmi_rx.audio_t.track_mode_tgl == 1) {
				hdmi_rx.audio_t.track_mode_tgl = 0;
				if (hdmi_audio_set_pll(t.ACR_freq, t.ACR_N, track_mode)) {
					SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_WAIT_PLL_READY);
					spdif_freq = t.SPDIF_freq;
					break;
				}
			} else {
				hdmi_rx.audio_t.track_mode_tgl = 1;
				if (hdmi_audio_set_pll(t.ACR_freq, t.ACR_N, HDMI_AUDIO_TREND_BOUND)) {
					SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_WAIT_PLL_READY);
					spdif_freq = t.SPDIF_freq;
					break;
				}
			}
		} else {
			if ((t.ACR_freq == 0)||(t2.ACR_freq == 0)) {
				/* cts = 0,use t.SPDIF_freq and force to trend_boundary tracking */
				if (hdmi_audio_set_pll(t.SPDIF_freq, t.ACR_N, HDMI_AUDIO_TREND_BOUND)) {
					if (t.SPDIF_freq == t2.SPDIF_freq) {
						SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_WAIT_PLL_READY);
						spdif_freq = t.SPDIF_freq;
						break;
					}
				}
			}
		}
		break;
	case AUDIO_FSM_AUDIO_WAIT_PLL_READY:
		HDMI_PRINTF("AUDIO_FSM_AUDIO_WAIT_PLL_READY\n");

		if (!hdmi_audio_is_pll_ready()) {
			SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
			return FALSE;
		}

		SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START_OUT);
		break;
	case AUDIO_FSM_AUDIO_START_OUT:
		HDMI_PRINTF("AUDIO_FSM_AUDIO_START_OUT\n");

		lib_hdmi_audio_generate();
		lib_hdmi_audio_output(1);

#ifdef HDMI_VIDEO_WD_ENABLE
		hdmi_watchdog_apply(_ENABLE, HDMI_WD_AUDIO_COND);
#endif

		SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_CHECK);
		result = TRUE;

		hdmi_rx.audio_t.coding_type = lib_hdmi_audio_is_nonpcm();
		hdmi_rx.audio_t.audio_freq = spdif_freq;

		break;
	case AUDIO_FSM_AUDIO_CHECK:
		hdmi_rx.audio_t.track_mode_tgl = 0;

		if (!hdmi_audio_is_pll_ready()) {
			lib_hdmi_audio_output(0);
			SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		}

		if (!lib_hdmi_audio_is_output()) {
			lib_hdmi_audio_output(0);
			SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		}

		if (hdmi_rx.audio_t.coding_type != lib_hdmi_audio_is_nonpcm()) {
			lib_hdmi_audio_output(0);
			SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
			HDMI_PRINTF("Audio Type change=%d\n", lib_hdmi_audio_is_nonpcm());
		}
		break;
	default:
		SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		break;
	}

	return result;
}

void hdmi_audio_close(void)
{
	lib_hdmi_audio_output(0);

	SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
}

void hdmi_audio_reset_status(void)
{
	SET_H_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
}

unsigned char hdmi_audio_get_current_status(void)
{
	return GET_H_AUDIO_FSM();
}

/* Audio Clock Regeneration (N/CTS) */
unsigned char hdmi_audio_wait_acr(void)
{
	
	unsigned char i, bch_err;

	lib_hdmi_set_rsv_packet_type(0, 0x01);
	lib_hdmi_clear_rsv_packet0_status();

	for (i = 0; i < 5; i++) {
		if (hdmi_update_rsv0_packet(1, &bch_err)) {
			/* acr no checksum bit, do not check */
			return ((bch_err & 0x1f) == 0);
		}
		HDMI_DELAYMS(10);
	}

	return FALSE;
}

/* Audio Sample (L-PCM and IEC 61937 compressed formats) */
unsigned char hdmi_audio_wait_sample(void)
{
	unsigned char i, buf[2];

	lib_hdmi_set_rsv_packet_type(0, 0x02);
	lib_hdmi_clear_rsv_packet0_status();

	for (i = 0; i < 5; i++) {
		if (hdmi_update_rsv0_packet(2, buf)) {
			lib_hdmi_audio_set_hbr_manual_mode(1, 0);
			return TRUE;
		}
		HDMI_DELAYMS(10);
	}

	return FALSE;
}

/* Audio Sample (02) (L-PCM and IEC 61937 compressed formats) */
unsigned char hdmi_audio_wait_2_samples(void)
{
	/* HBR sample (09) */
	unsigned char i, buf[9];

	/* Is packet_02 in reserved_0? */
	lib_hdmi_set_rsv_packet_type(0, 0x02);
	lib_hdmi_clear_rsv_packet0_status();

	/* Is packet_09 in reserved_1? */
	lib_hdmi_set_rsv_packet_type(1, 0x09);
	lib_hdmi_clear_rsv_packet1_status();

	for (i = 0; i < 5; i++) {
		if (hdmi_update_rsv1_packet(9, buf) || lib_hdmi_audio_get_hbr_mode()) {
			lib_hdmi_audio_set_hbr_manual_mode(1, 1);
			HDMI_PRINTF("Got HBR packet\n");
			return TRUE;
		}
		HDMI_DELAYMS(10);
	}

	if (hdmi_update_rsv0_packet(2, buf)) {
		/* follow up Merlin-1 setting, review this later */
		lib_hdmi_audio_set_hbr_manual_mode(1, 0);
		return TRUE;
	}

	return FALSE;
}

void Hdmi_SetHPD(char high)
{
	HDMIRX_INFO("Set HPD(%u)", high);

	if (high) {
#if HDMI2p0
		hdmi_rx_reg_mask32(HDMI_SCDC_CR,
			~HDMI_SCDC_CR_scdc_reset_mask, 0, HDMI_RX_MAC);
#endif

		gpio_direction_output(hdmi_rx.gpio_hpd_ctrl, 0);

	} else {
#if HDMI2p0
		hdmi_rx_reg_mask32(HDMI_SCDC_CR,
			~HDMI_SCDC_CR_scdc_reset_mask,
			HDMI_SCDC_CR_scdc_reset_mask, HDMI_RX_MAC);
#endif

		gpio_direction_output(hdmi_rx.gpio_hpd_ctrl, 1);
	}
}


void hdmi_check_connection_state(void)
{
	unsigned char conn_st;

	// TODO: Move to 5V detect flow
	conn_st = 1;

	if (conn_st != hdmi_rx.rx_5v_state) {
		if (conn_st) {
			/* Reset CED until measure done */
			lib_hdmi_char_err_rst(1);
		} else {
#if HDMI2p0
			lib_hdmi2p0_reset_scdc();
			lib_hdmi2p0_scramble_enable(0);
#endif	
			lib_hdmi_clear_avmute();

#if HDMI_TOGGLE_HPD_Z0_ENABLE
			lib_hdmi_set_toggle_hpd_z0_flag(FALSE);
#endif

			lib_hdmi_misc_variable_initial();
		}
	}

	//hdmi_rx.cable_conn = conn_st;
}


void hdmi_reset_all_infoframe(void)
{
	memset(&hdmi_rx.vsi_t, 0, sizeof(HDMI_VSI_T));
	hdmi_rx.no_vsi_cnt = 0;
	lib_hdmi_clear_fvs_received_status();
	lib_hdmi_clear_vs_received_status();

	memset(&hdmi_rx.avi_t, 0, sizeof(HDMI_AVI_T));
	hdmi_rx.no_avi_cnt = 0;
	lib_hdmi_clear_avi_received_status();

	memset(&hdmi_rx.spd_t, 0, sizeof(HDMI_SPD_T));
	hdmi_rx.no_spd_cnt = 0;
	lib_hdmi_clear_spd_received_status();

	memset(&hdmi_rx.audiopkt_t, 0, sizeof(HDMI_AUDIO_T));
	hdmi_rx.no_audiopkt_cnt = 0;
	lib_hdmi_clear_audiopkt_received_status();

	memset(&hdmi_rx.drm_t, 0, sizeof(HDMI_DRM_T));
	hdmi_rx.no_drm_cnt = 0;
	lib_hdmi_clear_drm_received_status();

}

void hdmi_update_infoframe(void)
{
	unsigned char is_drm_here = hdmi_rx.drm_t.type_code;
	unsigned char is_avi_here = hdmi_rx.avi_t.type_code;
	unsigned char is_spd_here = hdmi_rx.spd_t.type_code;
	unsigned char is_audio_here = hdmi_rx.audiopkt_t.type_code;
	unsigned char is_vsi_here = hdmi_rx.vsi_t.VSIF_Version;/* vsi has 2 version-type (861-G) */

	if (GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE || GET_H_MODE() != MODE_HDMI)
		return;

	if (hdmi_update_drm()) {
		hdmi_rx.no_drm_cnt = 0;
	} else {
		if (++hdmi_rx.no_drm_cnt > NO_DRM_INFO_MAX) {
			memset(&hdmi_rx.drm_t, 0, sizeof(HDMI_DRM_T));
			hdmi_rx.no_drm_cnt = 0;
		}
	}

	if (hdmi_update_avi()) {
		hdmi_rx.no_avi_cnt = 0;
	} else {
		if (++hdmi_rx.no_avi_cnt > NO_AVI_INFO_MAX) {
			memset(&hdmi_rx.avi_t, 0, sizeof(HDMI_AVI_T));
			hdmi_rx.no_avi_cnt = 0;
		}
	}

	if (hdmi_update_vsi()) {
		hdmi_rx.no_vsi_cnt = 0;
	} else {
		if (++hdmi_rx.no_vsi_cnt > NO_VSI_INFO_MAX) {
			memset(&hdmi_rx.vsi_t, 0, sizeof(HDMI_VSI_T));
			hdmi_rx.no_vsi_cnt = 0;
		}
	}

	if (hdmi_update_spd()) {
		hdmi_rx.no_spd_cnt = 0;
	} else {
#if NO_SPD_CLEAR_PACKET
		if (++hdmi_rx.no_spd_cnt > NO_SPD_INFO_MAX) {
			memset(&hdmi_rx.spd_t, 0, sizeof(HDMI_SPD_T));
			hdmi_rx.no_spd_cnt = 0;
		}
#endif
	}

	if (hdmi_update_audiopkt()) {
		hdmi_rx.no_audiopkt_cnt = 0;
	} else {
		if (++hdmi_rx.no_audiopkt_cnt > NO_AUDIO_INFO_MAX) {
			memset(&hdmi_rx.audiopkt_t, 0, sizeof(HDMI_AUDIO_T));
			hdmi_rx.no_audiopkt_cnt = 0;
		}
	}

	if (is_drm_here != hdmi_rx.drm_t.type_code) {
		HDMI_PRINTF("DRM INFO=%d\n", hdmi_rx.drm_t.type_code);
	}
	if (is_avi_here != hdmi_rx.avi_t.type_code) {
		HDMI_PRINTF("AVI INFO=%d\n", hdmi_rx.avi_t.type_code);
	}
	if (is_spd_here != hdmi_rx.spd_t.type_code) {
		HDMI_PRINTF("SPD INFO=%d\n", hdmi_rx.spd_t.type_code);
	}
	if (is_audio_here != hdmi_rx.audiopkt_t.type_code) {
		HDMI_PRINTF("AUD INFO=%d\n", hdmi_rx.audiopkt_t.type_code);
	}
	if (is_vsi_here != hdmi_rx.vsi_t.VSIF_Version) {
		HDMI_PRINTF("VSI INFO=%d (%x,%x,%x)\n",
			hdmi_rx.vsi_t.VSIF_Version, hdmi_rx.vsi_t.Reg_ID[0],
			hdmi_rx.vsi_t.Reg_ID[1], hdmi_rx.vsi_t.Reg_ID[2]);
		/*
		 * 0xd8, 0x5d, 0xc4 is hdmi2.0 FVSPS (QD980 Forum VS)
		 * 0x03, 0x0c, 0x00 is hdmi1.4 VSPS or Dolby (QD980 LLC VS)
		 * QD980 has a bug, it needs to toggle & apply twice then send correct info.
		 */
	}

}

unsigned char hdmi_get_hdmi_mode_infoframe(void)
{
	if (GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_DISPLAY_ON)
		return 0;

	if (GET_H_MODE() == MODE_HDMI)
		return 1;

	return 0;
}

unsigned char hdmi_get_vs_infoframe(HDMI_VSI_T *p_vsi_t)
{
	if ((GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE) ||
		(GET_H_MODE() != MODE_HDMI))
		return 0;

	if (hdmi_rx.vsi_t.VSIF_TypeCode == 0)
		return 0;

	memcpy(p_vsi_t, &hdmi_rx.vsi_t, sizeof(HDMI_VSI_T));
	return 1;
}

unsigned char hdmi_get_avi_infoframe(HDMI_AVI_T *p_avi_t)
{
	if ((GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE) ||
		(GET_H_MODE() != MODE_HDMI))
		return 0;

	if (hdmi_rx.avi_t.type_code == 0)
		return 0;

	memcpy(p_avi_t, &hdmi_rx.avi_t, sizeof(HDMI_AVI_T));
	return 1;
}

unsigned char hdmi_get_spd_infoframe(HDMI_SPD_T *p_spd_t)
{
	if ((GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE) ||
		(GET_H_MODE() != MODE_HDMI))
		return 0;

	if (hdmi_rx.spd_t.type_code == 0)
		return 0;

	memcpy(p_spd_t, &hdmi_rx.spd_t, sizeof(HDMI_SPD_T));
	return 1;
}

unsigned char hdmi_get_audio_infoframe(HDMI_AUDIO_T *p_audio_t)
{
	if ((GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_MEASURE) ||
		(GET_H_MODE() != MODE_HDMI))
		return 0;

	if (hdmi_rx.audiopkt_t.type_code == 0)
		return 0;

	memcpy(p_audio_t, &hdmi_rx.audiopkt_t, sizeof(HDMI_AUDIO_T));
	return 1;
}

unsigned char hdmi_get_drm_infoframe(HDMI_DRM_T *p_drm_t)
{
	if ((GET_H_VIDEO_FSM() < MAIN_FSM_HDMI_VIDEO_READY) ||
		(GET_H_MODE() != MODE_HDMI))
		return 0;

	if (hdmi_rx.drm_t.type_code == 0)
		return 0;

	memcpy(p_drm_t, &hdmi_rx.drm_t, sizeof(HDMI_DRM_T));
	return 1;
}

#define VSI_PKT_LEN      31
#define VSI_PKT_CONT_LEN 12
unsigned char hdmi_update_vsi(void)
{
	unsigned char sta_pos;
	unsigned char len;
	unsigned char pkt_buf[VSI_PKT_LEN] = {0};
	unsigned char len_extend;

#if HDMI2p0
	if (lib_hdmi_is_fvs_received()) {
		lib_hdmi_clear_fvs_received_status();
		sta_pos = 253;
		len = 11;
	} else 
#endif
	if (lib_hdmi_is_vs_received()) {
		lib_hdmi_clear_vs_received_status();
		sta_pos = 203;
		len = 18;
	} else {
		return FALSE;
	}


	lib_hdmi_read_packet_sram(sta_pos, len, pkt_buf);

	/*
	 * pkt_buf[0]; => version
	 * pkt_buf[1]; => len
	 * pkt_buf[2]; => checksum
	 */

	if (sta_pos == 203) {
		if (pkt_buf[1] > 15) {
			/* len > 15 */
			len_extend = pkt_buf[1] - 15;

			if(len_extend >= VSI_PKT_CONT_LEN)
				lib_hdmi_read_packet_sram(323, VSI_PKT_CONT_LEN, &pkt_buf[18]);
			else
				lib_hdmi_read_packet_sram(323, len_extend, &pkt_buf[18]);

			len = pkt_buf[1] + 3;
		}
	}
	hdmi_rx.vsi_t.VSIF_TypeCode = 0x81;
	/* use len for memcpy because copy size will be 11 or 18 */
	memcpy(&hdmi_rx.vsi_t.VSIF_Version, pkt_buf, len);

	return TRUE;
}

#define AVI_PKT_LEN 	  16
#define AVI_PKT_CONT_LEN  14
#define AVI_PKT_TOTAL_LEN (AVI_PKT_LEN + AVI_PKT_CONT_LEN)
unsigned char hdmi_update_avi(void)
{
	unsigned char pkt_buf[AVI_PKT_TOTAL_LEN] = {0};
	unsigned char len_extend;

	if (!lib_hdmi_is_avi_received())
		return FALSE;

	lib_hdmi_clear_avi_received_status();

	lib_hdmi_read_packet_sram(1, AVI_PKT_LEN, pkt_buf);
	pkt_buf[2] = pkt_buf[1];/* len */
	pkt_buf[1] = pkt_buf[0];/* version */
	pkt_buf[0] = 0x82;

	if (pkt_buf[2] > 13) {
		len_extend = pkt_buf[2] - 13;

		if (len_extend >= AVI_PKT_CONT_LEN)
			lib_hdmi_read_packet_sram(335, AVI_PKT_CONT_LEN, &pkt_buf[16]);
		else
			lib_hdmi_read_packet_sram(335, len_extend, &pkt_buf[16]);
	}

	memcpy(&hdmi_rx.avi_t, pkt_buf, sizeof(HDMI_AVI_T));
	return TRUE;
}

#define SPD_PKT_LEN	28
unsigned char hdmi_update_spd(void)
{	
	unsigned char pkt_buf[SPD_PKT_LEN] = {0};

	if (!lib_hdmi_is_spd_received())
		return FALSE;

	lib_hdmi_clear_spd_received_status();

	lib_hdmi_read_packet_sram(295, SPD_PKT_LEN, pkt_buf);
	pkt_buf[2] = pkt_buf[1];/* len */
	pkt_buf[1] = pkt_buf[0];/* version */
	pkt_buf[0] = 0x83;

	memcpy(&hdmi_rx.spd_t, pkt_buf, sizeof(HDMI_SPD_T));
	return TRUE;
}

#define AUDIO_PKT_LEN 13
unsigned char hdmi_update_audiopkt(void)
{
	unsigned char pkt_buf[AUDIO_PKT_LEN] = {0};

	if (!lib_hdmi_is_audiopkt_received())
		return FALSE;

	lib_hdmi_clear_audiopkt_received_status();

	lib_hdmi_read_packet_sram(18, AUDIO_PKT_LEN, pkt_buf);
	pkt_buf[2] = pkt_buf[1];/* len */
	pkt_buf[1] = pkt_buf[0];/* version */
	pkt_buf[0] = 0x84;

	memcpy(&hdmi_rx.audiopkt_t, pkt_buf, AUDIO_PKT_LEN);
	return TRUE;

}

#define DRM_PKT_LEN	29
unsigned char hdmi_update_drm(void)
{
	unsigned char pkt_buf[DRM_PKT_LEN] = {0};

	if (!lib_hdmi_is_drm_received())
		return FALSE;

	lib_hdmi_clear_drm_received_status();

	lib_hdmi_read_packet_sram(265, DRM_PKT_LEN, pkt_buf);

	((unsigned char*)(&hdmi_rx.drm_t))[2] = pkt_buf[1];/* len */
	((unsigned char*)(&hdmi_rx.drm_t))[1] = pkt_buf[0];/* version */
	((unsigned char*)(&hdmi_rx.drm_t))[0] = 0x87;/* Info Frame Type */

	hdmi_rx.drm_t.eEOTFtype  = pkt_buf[3];
	hdmi_rx.drm_t.eMeta_Desc = pkt_buf[4];
	hdmi_rx.drm_t.display_primaries_x0 = pkt_buf[5]|(pkt_buf[6]<<8);
	hdmi_rx.drm_t.display_primaries_y0 = pkt_buf[7]|(pkt_buf[8]<<8);
	hdmi_rx.drm_t.display_primaries_x1 = pkt_buf[9]|(pkt_buf[10]<<8);
	hdmi_rx.drm_t.display_primaries_y1 = pkt_buf[11]|(pkt_buf[12]<<8);
	hdmi_rx.drm_t.display_primaries_x2 = pkt_buf[13]|(pkt_buf[14]<<8);
	hdmi_rx.drm_t.display_primaries_y2 = pkt_buf[15]|(pkt_buf[16]<<8);
	hdmi_rx.drm_t.white_point_x = pkt_buf[17]|(pkt_buf[18]<<8);
	hdmi_rx.drm_t.white_point_y = pkt_buf[19]|(pkt_buf[20]<<8);
	hdmi_rx.drm_t.max_display_mastering_luminance = pkt_buf[21]|(pkt_buf[22]<<8);
	hdmi_rx.drm_t.min_display_mastering_luminance = pkt_buf[23]|(pkt_buf[24]<<8);
	hdmi_rx.drm_t.maximum_content_light_level = pkt_buf[25]|(pkt_buf[26]<<8);
	hdmi_rx.drm_t.maximum_frame_average_light_level = pkt_buf[27]|(pkt_buf[28]<<8);

	return TRUE;
}


unsigned char hdmi_update_rsv0_packet(unsigned char len, unsigned char *buf)
{
	if (!lib_hdmi_is_rsv_packet0_received())
		return FALSE;

	lib_hdmi_read_packet_sram(78, len, buf);
	return TRUE;
}

unsigned char hdmi_update_rsv1_packet(unsigned char len, unsigned char *buf)
{
	if (!lib_hdmi_is_rsv_packet1_received())
		return FALSE;

	lib_hdmi_read_packet_sram(109, len, buf);
	return TRUE;
}

unsigned char hdmi_update_rsv2_packet(unsigned char len, unsigned char *buf)
{
	if (!lib_hdmi_is_rsv_packet2_received())
		return FALSE;

	lib_hdmi_read_packet_sram(140, len, buf);
	return TRUE;
}

unsigned char hdmi_update_rsv3_packet(unsigned char len, unsigned char *buf)
{
	if (!lib_hdmi_is_rsv_packet3_received())
		return FALSE;

	lib_hdmi_read_packet_sram(171, len, buf);
	return TRUE;
}


unsigned char hdmi_check_spd_name(unsigned char *vendor_name)
{
	unsigned char i;

	if (hdmi_rx.spd_t.type_code == 0)
		return 0;

#if 0
	HDMI_PRINTF("VendorName [%x, %x, %x, %x, %x, %x, %x, %x]\n",
		hdmi_rx.spd_t.VendorName[0], hdmi_rx.spd_t.VendorName[1],
		hdmi_rx.spd_t.VendorName[2], hdmi_rx.spd_t.VendorName[3],
		hdmi_rx.spd_t.VendorName[4], hdmi_rx.spd_t.VendorName[5],
		hdmi_rx.spd_t.VendorName[6], hdmi_rx.spd_t.VendorName[7]);
#endif

	for (i = 0; i < 8; i++) {
		if (hdmi_rx.spd_t.VendorName[i] != vendor_name[i])
			return 0;
	}

	return 1;
}

unsigned char hdmi_check_spd_prod(unsigned char *prod_desc)
{
	unsigned char i;

	if (hdmi_rx.spd_t.type_code == 0)
		return 0;

#if 0
	HDMI_PRINTF("ProductDesc [%x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x]\n",
		hdmi_rx.spd_t.ProductDesc[0], hdmi_rx.spd_t.ProductDesc[1],
		hdmi_rx.spd_t.ProductDesc[2], hdmi_rx.spd_t.ProductDesc[3],
		hdmi_rx.spd_t.ProductDesc[4], hdmi_rx.spd_t.ProductDesc[5],
		hdmi_rx.spd_t.ProductDesc[6], hdmi_rx.spd_t.ProductDesc[7],
		hdmi_rx.spd_t.ProductDesc[8], hdmi_rx.spd_t.ProductDesc[9],
		hdmi_rx.spd_t.ProductDesc[10], hdmi_rx.spd_t.ProductDesc[11],
		hdmi_rx.spd_t.ProductDesc[12], hdmi_rx.spd_t.ProductDesc[13],
		hdmi_rx.spd_t.ProductDesc[14], hdmi_rx.spd_t.ProductDesc[15]);
#endif

	for (i = 0; i < 16; i++) {
		if (hdmi_rx.spd_t.ProductDesc[i] != prod_desc[i])
			return 0;
	}

	return 1;
}


unsigned char hdmi_compatibility_check(void)
{
	HDMI_POOR_DEV_T btv_stb = {
		{0x42, 0x72, 0x6f, 0x61, 0x64, 0x63, 0x6f, 0x6d},
		{0x53, 0x54, 0x42, 0x20, 0x52, 0x65, 0x66, 0x73, 0x77, 0x20, 0x44, 0x65, 0x73, 0x69, 0x67, 0x6e}};

#if HDMI_TOGGLE_HPD_Z0_ENABLE
	/* [STB-14] KT UHD STB (IC1000) */
	HDMI_POOR_DEV_T kt_stb_IC1000 = {
		{0x4b, 0x61, 0x6f, 0x6e, 0x00, 0x63, 0x6f, 0x6d},
		{0x49, 0x43, 0x31, 0x30, 0x30, 0x30, 0x00, 0x63, 0x65, 0x20, 0x42, 0x6f, 0x61, 0x72, 0x64, 0x00}};

#endif
#if HDMI_STR_TOGGLE_HPD_ENABLE
	/* [STB-20] IC1100 - KT olleh GiGA UHD tv STB */
	HDMI_POOR_DEV_T kt_stb_IC1100 = {
		{0x4b, 0x61, 0x6f, 0x6e, 0x00, 0x63, 0x6f, 0x6d},
		{0x49, 0x43, 0x31, 0x31, 0x30, 0x30, 0x00, 0x63, 0x65, 0x20, 0x42, 0x6f, 0x61, 0x72, 0x64, 0x00}};

	HDMI_POOR_DEV_T kt_stb_GX_KT600EJ = {
		{0x53, 0x61, 0x6d, 0x73, 0x75, 0x6e, 0x67, 0x0},
		{0x47, 0x58, 0x2d, 0x4b, 0x54, 0x36, 0x30, 0x30, 0x45, 0x4a, 0x0, 0x6f, 0x61, 0x72, 0x64, 0x0}};
#endif

#if HDMI_DISPLAY_DELAY_ENABLE
	/* LHB755 - LG */
	HDMI_POOR_DEV_T LHB755 = {
		{0x4d, 0x54, 0x4b, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x42, 0x44, 0x20, 0x50, 0x4c, 0x41, 0x59, 0x45, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

	HDMI_POOR_DEV_T Samsung_GX_HC630CH = {
		{0x42, 0x72, 0x6f, 0x61, 0x64, 0x63, 0x6f, 0x6d},
		{0x53, 0x54, 0x42, 0x20, 0x47, 0x58, 0x36, 0x33, 0x30, 0x43, 0x48, 0x0, 0x61, 0x72, 0x64, 0x0}};
#endif /* End of #if HDMI_DISPLAY_DELAY_ENABLE */


#if HDMI_TOGGLE_HPD_Z0_ENABLE
	lib_hdmi_set_toggle_hpd_z0_flag(FALSE);
#endif

#if HDMI_STR_TOGGLE_HPD_ENABLE
	lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_NONE);
#endif 

	if (hdmi_check_spd_name(btv_stb.spd_vn_name) && hdmi_check_spd_prod(btv_stb.psd_pd_desc)) {
		/* SKbox transient garbage */
		HDMI_PRINTF("This is SKBOX!!!!!!!\n");
		/* lib_hdmi_hdcp_port_write(0xC4, 0x8); */
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_SK_STB);
	}
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	else if (hdmi_check_spd_name(kt_stb_IC1000.spd_vn_name) && hdmi_check_spd_prod(kt_stb_IC1000.psd_pd_desc)) {
		/* SKbox transient garbage */
		HDMI_PRINTF("This is KT STB IC1000 !!!!!!!\n");
		lib_hdmi_set_toggle_hpd_z0_flag(TRUE);
		lib_hdmi_dc_on_delay_check(TRUE);
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_KT_STB_IC1000);
	}
#endif
#if HDMI_STR_TOGGLE_HPD_ENABLE
	else if (hdmi_check_spd_name(kt_stb_IC1100.spd_vn_name) && hdmi_check_spd_prod(kt_stb_IC1100.psd_pd_desc)) {
		/* KT STB and TV STR off/on, can not display */
		HDMI_PRINTF("This is KT STB IC1100 !!!!!!!\n");
		lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_ENTER);
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_KT_STB_IC1100);
	} else if (hdmi_check_spd_name(kt_stb_GX_KT600EJ.spd_vn_name) && hdmi_check_spd_prod(kt_stb_GX_KT600EJ.psd_pd_desc)) {
		/* KT STB and TV STR off/on, no signal */
		HDMI_PRINTF("This is KT STB kt_stb_GX_KT600EJ !!!!!!!\n");
		lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_ENTER);
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_KT_STB_KT600EJ);
	}
#endif/* End of #if HDMI_STR_TOGGLE_HPD_ENABLE */
#if HDMI_DISPLAY_DELAY_ENABLE
	else if (hdmi_check_spd_name(LHB755.spd_vn_name) && hdmi_check_spd_prod(LHB755.psd_pd_desc)) {
		/* LHB755 - LG, change timing flicker */
		HDMI_PRINTF("This is DVD LHB755 !!!!!!!\n");
		lib_hdmi_set_delay_display_enable(_ENABLE);
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_LHB_755);

		if (lib_hdmi_get_delay_display_state() == HDMI_DISPLAY_DELAY_NONE) {
			lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_INIT);
			lib_hdmi_delay_check_before_display(TRUE);
		}
	}
	else if (hdmi_check_spd_name(Samsung_GX_HC630CH.spd_vn_name) && hdmi_check_spd_prod(Samsung_GX_HC630CH.psd_pd_desc)) {
		/* HDMI_SPECIFIC_DEVICE_SAMSUNG_GX_HC630CH change resolution flicker */
		HDMI_PRINTF("This is SAMSUNG_GX_HC630CH !!!!!!!\n");
		lib_hdmi_set_delay_display_enable(_ENABLE);
		lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_SAMSUNG_GX_HC630CH);

		if (lib_hdmi_get_delay_display_state() == HDMI_DISPLAY_DELAY_NONE) {
			lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_INIT);
			lib_hdmi_delay_check_before_display(TRUE);
		}
	} else if(0 == hdmi_rx.spd_t.type_code) {

		if ((hdmi_rx.timing_t.h_act_len == 3840) &&
			(hdmi_rx.timing_t.v_act_len == 2160) &&
			(hdmi_rx.avi_t.VIC == 97)) {

			if (hdmi_no_SPD_packetInfo() == TRUE) {

				if (lib_hdmi_hdcp14_is_onoff() == _ENABLE) {
					if ((GET_H_COLOR_SPACE() == COLOR_YUV420) && (GET_H_COLOR_DEPTH() == HDMI_COLOR_DEPTH_10B)) {
						HDMI_PRINTF("This is GiGa_Genie_KAO_CT1100_LB @ 4K2K !!!!!!!\n");
						lib_hdmi_set_delay_display_enable(_ENABLE);
						lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_KT_STB_KAO_CT1100);

						if (lib_hdmi_get_delay_display_state() ==HDMI_DISPLAY_DELAY_NONE) {
							lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_INIT);
							lib_hdmi_delay_check_before_display(TRUE);
						}
					}
				}
			}
		}
	}
#endif/* End of #if HDMI_DISPLAY_DELAY_ENABLE */


#if HDMI_AVI_INFO_COLORIMETRY_ENABLE
	if (hdmi_check_avi_colorimetry_info(FALSE) == FALSE) {
		SET_H_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
		return FALSE;
	}
#endif

#if HDMI_CHECK_HDCP_ENABLE
	if (hdmi_check_hdcp_condition(FALSE) == FALSE) {
		SET_H_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
		return FALSE;
	}
#endif

	hdmi_check_deb_condition_beforeDisp(FALSE);

	return TRUE;

}


/* To fix blu-ray player, NS-BRDVD short time unstable */
unsigned char hdmi_check_stable_before_display(void)
{
	if (bNeedDebBeforeDisp == 1) {
		if( DispDebCnt > 0 ) {
			HDMI_PRINTF("------>debouncing =%d, %d\n", bNeedDebBeforeDisp, DispDebCnt);
			DispDebCnt--;
			return FALSE;
		}
	}
	bNeedDebBeforeDisp = 0;
	DispDebCondition = 0;

#if HDMI_DISPLAY_DELAY_ENABLE
	lib_hdmi_set_delay_display_enable(_DISABLE);
	lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_NONE);
#endif

	if (GET_H_VIDEO_FSM() != MAIN_FSM_HDMI_VIDEO_READY) {
		HDMI_PRINTF("B-check_mode_changed_1\n");
		return FALSE;
	}

#if HDMI_TOGGLE_HPD_Z0_ENABLE
	if (lib_hdmi_dc_on_delay_check(FALSE) == FALSE)
		return FALSE;
#endif

	if (hdmi_check_condition_change()) {
		lib_hdmi_video_output(0);
		lib_hdmi_audio_output(0);
		HDMI_PRINTF("B-check_mode_changed_2\n");
		return FALSE;
	}

#if HDMI_INT_PRO_CHG_FLAG_ENABLE
	if (lib_hdmi_get_is_interlace_change() == TRUE) {
		HDMI_PRINTF("B-interlace chg\n");
		return FALSE;
	}
#else
	if (GET_H_INTERLACE() != hdmi_get_interlace_conti_mode()) {
		HDMI_PRINTF("B-interlace chg from %d to %d\n", GET_H_INTERLACE(), (!GET_H_INTERLACE()));
		return FALSE;
	}
#endif

	return TRUE;
}


unsigned char hdmi_watchdog_apply(unsigned char Enable, unsigned char Condition)
{
#ifdef HDMI_VIDEO_WD_ENABLE
	UINT8 ucEnable_WatchDog = FALSE;
	static UINT8 ucWatchDog_Mask = 0x00;

	if (Enable == _ENABLE)
		ucWatchDog_Mask = ucWatchDog_Mask | Condition;
	else
		ucWatchDog_Mask = ucWatchDog_Mask & (~Condition);

	if ((ucWatchDog_Mask & (HDMI_WD_VIDEO_COND | HDMI_WD_AUDIO_COND | HDMI_WD_VSC_COND)) == HDMI_WD_ALL_COND)
		ucEnable_WatchDog = TRUE;
	else
		ucEnable_WatchDog = FALSE;

	if (GET_H_MODE() == MODE_DVI)
		ucEnable_WatchDog = _DISABLE;

	if (ucEnable_WatchDog == _ENABLE) {
		lib_hdmi_wdm_enable(1);
		lib_hdmi_auto_avmute_enable(1);
	} else {
		lib_hdmi_wdm_enable(0);
		lib_hdmi_auto_avmute_enable(0);
	}
#endif/* End of #ifdef HDMI_VIDEO_WD_ENABLE */

	return FALSE;
}


unsigned char hdmi_check_avi_colorimetry_info(unsigned char ucInit)
{
#if HDMI_AVI_INFO_COLORIMETRY_ENABLE
	static unsigned char avi_debounce;

	if(ucInit == TRUE) {
		avi_debounce = HDMI_AVI_INFO_COLORIMETRY_DEBOUNCE_CNT;
		return TRUE;
	}

	if (GET_H_MODE() == MODE_DVI)
		return TRUE;

	/* 160ms/times */
	if (hdmi_rx.avi_t.type_code == 2) {

		if (hdmi_rx.avi_t.len == 0) {
			/* For other case */
		} else {
			if ((hdmi_rx.avi_t.EC == 0) && (hdmi_rx.avi_t.C == 0)) {
				if (avi_debounce) {
					/* Just for 2 depth = LG Bluray BP-550 + Speaker YAMAHA YSP-5600 special case, wait more time */
					if((hdmi_rx.spd_t.VendorName[0] == 0x59) && (hdmi_rx.spd_t.VendorName[1] == 0x61)
						&& (hdmi_rx.spd_t.VendorName[2] == 0x6d) && (hdmi_rx.spd_t.VendorName[3] == 0x61)
						&& (hdmi_rx.spd_t.VendorName[4] == 0x68) && (hdmi_rx.spd_t.VendorName[5] == 0x61)
						&& (hdmi_rx.spd_t.VendorName[6] == 0x00) && (hdmi_rx.spd_t.VendorName[7]) == 0x00) {

						avi_debounce--;
						HDMI_PRINTF("EC /C avi_debounce1=%x\n", avi_debounce);
						return FALSE;
					}
#if 0
					HDMI_PRINTF("VendorName [%x, %x, %x, %x, %x, %x, %x, %x]\n", hdmi_rx.spd_t.VendorName[0],
						hdmi_rx.spd_t.VendorName[1], hdmi_rx.spd_t.VendorName[2],
						hdmi_rx.spd_t.VendorName[3], hdmi_rx.spd_t.VendorName[4],
						hdmi_rx.spd_t.VendorName[5], hdmi_rx.spd_t.VendorName[6],
						hdmi_rx.spd_t.VendorName[7]);

					HDMI_PRINTF("EC /C avi_debounce1 exit\n");
#endif
				}
			}
		}
	}
#endif/* End of #if HDMI_AVI_INFO_COLORIMETRY_ENABLE */

	return TRUE;
}


unsigned char hdmi_no_SPD_packetInfo(void)
{
	if((hdmi_rx.spd_t.VendorName[0] == 0) && (hdmi_rx.spd_t.VendorName[1] == 0) &&
		(hdmi_rx.spd_t.VendorName[2] == 0) && (hdmi_rx.spd_t.VendorName[3] == 0) &&
		(hdmi_rx.spd_t.VendorName[4] == 0) && (hdmi_rx.spd_t.VendorName[5] == 0) &&
		(hdmi_rx.spd_t.VendorName[6] == 0) && (hdmi_rx.spd_t.VendorName[7] == 0)) {

		if((hdmi_rx.spd_t.ProductDesc[0] == 0) && (hdmi_rx.spd_t.ProductDesc[1] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[2] == 0) && (hdmi_rx.spd_t.ProductDesc[3] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[4] == 0) && (hdmi_rx.spd_t.ProductDesc[5] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[6] == 0) && (hdmi_rx.spd_t.ProductDesc[7] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[8] == 0) && (hdmi_rx.spd_t.ProductDesc[9] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[10] == 0) && (hdmi_rx.spd_t.ProductDesc[11] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[12] == 0) && (hdmi_rx.spd_t.ProductDesc[13] == 0) &&
			(hdmi_rx.spd_t.ProductDesc[14] == 0) && (hdmi_rx.spd_t.ProductDesc[15] == 0))
			return TRUE;
	}
	return FALSE;
}


unsigned char hdmi_check_deb_condition_beforeDisp(unsigned char ucInit)
{
	unsigned int cur_v_act_len = hdmi_rx.timing_t.v_act_len;
	unsigned int cur_h_act_len = hdmi_rx.timing_t.h_act_len;

	if (ucInit == TRUE) {
		if (bNeedDebBeforeDisp == 0 ) {
			DispDebCnt = 0;
		}
		return TRUE;
	}

	if (((cur_h_act_len == 1280 && cur_v_act_len == 720) || (cur_h_act_len ==1360 && cur_v_act_len == 768)
		||(cur_h_act_len ==1920 && cur_v_act_len == 540) || (cur_h_act_len == 3840 && cur_v_act_len == 2160))
		&& (lib_hdmi_hdcp14_is_onoff() == _ENABLE)
		&& (hdmi_no_SPD_packetInfo() == TRUE)) {

		HDMI_PRINTF("...............checking h/v= (%d, %d) [%d-%d], c=%d, vic=%d\n",
			cur_h_act_len, cur_v_act_len, bNeedDebBeforeDisp, DispDebCondition, DispDebCnt, hdmi_rx.avi_t.VIC);

		//deb start point: condition1
		if( (cur_h_act_len==1360 && cur_v_act_len == 768) && (bNeedDebBeforeDisp == 0) && (hdmi_rx.avi_t.VIC == 0))
		{
			bNeedDebBeforeDisp = 1;
			DispDebCnt = DISP_DEB_CNT_APPLETV;
			DispDebCondition = 1;

			HDMI_PRINTF("**************************** disp deb start1!!\n");
		}

		//deb again: condition2 =1360x768->1280x720
		if((cur_h_act_len==1280 && cur_v_act_len == 720) && (DispDebCondition==1))
		{
			DispDebCnt = DISP_DEB_CNT_APPLETV;
			DispDebCondition = 2;

			HDMI_PRINTF("**************************** disp deb start2!!\n");
		}

		//LewisLee DATE:2016/12/22
		//WOSQRTK-10354, PC40000
		// 3840x2160 timing, HDMI cable plug in/out will flicker
		if( (cur_h_act_len == 3840 && cur_v_act_len == 2160) && (bNeedDebBeforeDisp == 0) && (hdmi_rx.avi_t.VIC == 0))
		{
			bNeedDebBeforeDisp = 1;
			DispDebCnt = DISP_DEB_CNT_PC40000;
			DispDebCondition = 3;

			HDMI_PRINTF("**************************** disp deb start3!!\n");
		}
	}
	else {

		DispDebCondition = 0;
		DispDebCnt = 0;
		bNeedDebBeforeDisp = 0;
	}

	return TRUE;
}

//==========================================

//USER:LewisLee Date:2016/10/08
//Fix TV power on, PS 4 flocker
//No HDCP => stable clock => display => HDCP => flicker => display
unsigned char hdmi_check_hdcp_condition(unsigned char ucInit)
{
#if HDMI_CHECK_HDCP_ENABLE
	hdmi_p0_port0_hdcp_flag1_RBUS hdmi_p0_port0_hdcp_flag1_reg;
	static unsigned char HDCP_debounce;

	if (ucInit == TRUE) {
		HDCP_debounce = HDMI_HDCP_DEBOUNCE_CNT;
		return TRUE;
	}

	if (GET_H_MODE() == MODE_DVI)
		return TRUE;

	if (HDCP_debounce == 0)
		return TRUE;

#if 0
	HDMI_PRINTF("VendorName [%x, %x, %x, %x, %x, %x, %x, %x]\n", hdmi_rx.spd_t.VendorName[0],
		hdmi_rx.spd_t.VendorName[1], hdmi_rx.spd_t.VendorName[2],
		hdmi_rx.spd_t.VendorName[3], hdmi_rx.spd_t.VendorName[4],
		hdmi_rx.spd_t.VendorName[5], hdmi_rx.spd_t.VendorName[6],
		hdmi_rx.spd_t.VendorName[7]);

	HDMI_PRINTF("ProductDesc [%x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x, %x]\n",
		hdmi_rx.spd_t.ProductDesc[0], hdmi_rx.spd_t.ProductDesc[1],
		hdmi_rx.spd_t.ProductDesc[2], hdmi_rx.spd_t.ProductDesc[3],
		hdmi_rx.spd_t.ProductDesc[4], hdmi_rx.spd_t.ProductDesc[5],
		hdmi_rx.spd_t.ProductDesc[6], hdmi_rx.spd_t.ProductDesc[7],
		hdmi_rx.spd_t.ProductDesc[8], hdmi_rx.spd_t.ProductDesc[9],
		hdmi_rx.spd_t.ProductDesc[10], hdmi_rx.spd_t.ProductDesc[11],
		hdmi_rx.spd_t.ProductDesc[12], hdmi_rx.spd_t.ProductDesc[13],
		hdmi_rx.spd_t.ProductDesc[14], hdmi_rx.spd_t.ProductDesc[15] );
#endif //#if 0

	// 160ms/times
	// VendorName = SCEI
	if((hdmi_rx.spd_t.VendorName[0] == 0x53) && (hdmi_rx.spd_t.VendorName[1] == 0x43) &&
		(hdmi_rx.spd_t.VendorName[2] == 0x45) && (hdmi_rx.spd_t.VendorName[3] == 0x49) &&
		(hdmi_rx.spd_t.VendorName[4] == 0x00) && (hdmi_rx.spd_t.VendorName[5] == 0x00) &&
		(hdmi_rx.spd_t.VendorName[6] == 0x00) && (hdmi_rx.spd_t.VendorName[7] == 0x00)) {

		// ProductDesc = PS4
		if((hdmi_rx.spd_t.ProductDesc[0] == 0x50) && (hdmi_rx.spd_t.ProductDesc[1] == 0x53)
			&& (hdmi_rx.spd_t.ProductDesc[2] == 0x34) && (hdmi_rx.spd_t.ProductDesc[3] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[4] == 0x00) && (hdmi_rx.spd_t.ProductDesc[5] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[6] == 0x00) && (hdmi_rx.spd_t.ProductDesc[7] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[8] == 0x00) && (hdmi_rx.spd_t.ProductDesc[9] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[10] == 0x00) && (hdmi_rx.spd_t.ProductDesc[11] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[12] == 0x00) && (hdmi_rx.spd_t.ProductDesc[13] == 0x00)
			&& (hdmi_rx.spd_t.ProductDesc[14] == 0x00) && (hdmi_rx.spd_t.ProductDesc[15]) == 0x00) {

				hdmi_p0_port0_hdcp_flag1_reg.regValue = hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC);

				if((hdmi_p0_port0_hdcp_flag1_reg.wr_aksv_flag == 0) && (0 == hdmi_p0_port0_hdcp_flag1_reg.rd_ri_flag)) {
					//Need check HDCP 1.4 or 2.2
					HDCP_debounce--;

					HDMI_PRINTF("[HDCP] HDCP_debounce=%x\n", HDCP_debounce);
					if (lib_hdmi_hdcp14_is_onoff() == _ENABLE)
						return FALSE;
				}
			}
	}

	HDCP_debounce = 0; // need check it can clear in here or not

//	HDMI_PRINTF("[HDCP] HDCP_debounce exit\n");
#endif //#if HDMI_CHECK_HDCP_ENABLE

	return TRUE;
}


unsigned char hdmi_get_avmute(void)
{
	if (GET_H_VIDEO_FSM() == MAIN_FSM_HDMI_VIDEO_READY) {
		if (lib_hdmi_get_avmute() && !lib_hdmi_get_bch_2bit_error()) {
			HDMI_PRINTF("This is AVMUTE\n");
			return TRUE;
		}
	}

	return FALSE;
}


/*********************************************************************************
*
*	hdmi_lib.c
*
*********************************************************************************/

void lib_hdmi_power(unsigned char enable)
{

	if (enable) {
		/* Enable PLL TMDS, RGB clock output */
		hdmi_rx_reg_mask32(HDMI_TMDS_OUTCTL,
			~(HDMI_TMDS_OUTCTL_tbcoe_mask | HDMI_TMDS_OUTCTL_tgcoe_mask | HDMI_TMDS_OUTCTL_trcoe_mask | HDMI_TMDS_OUTCTL_ocke_mask),
			(HDMI_TMDS_OUTCTL_tbcoe(1) | HDMI_TMDS_OUTCTL_tgcoe(1) | HDMI_TMDS_OUTCTL_trcoe(1) | HDMI_TMDS_OUTCTL_ocke(1)),
			HDMI_RX_MAC);
		hdmi_rx_reg_mask32(LDO, ~LDO_reg_p0_ldo_pow_mask, LDO_reg_p0_ldo_pow_mask, HDMI_RX_PHY);


		lib_hdmi_z0_set(LN_ALL, 1);

		hdmi_rx_reg_mask32(MBIAS,
			~MBIAS_reg_mbias_en_mask, MBIAS_reg_mbias_en_mask, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(Z0POW,
			~Z0POW_reg_z0_z300pow_mask, Z0POW_reg_z0_z300pow(1), HDMI_RX_PHY);

	} else {
		/* Disable PLL TMDS, RGB clock output */
		hdmi_rx_reg_mask32(HDMI_TMDS_OUTCTL,
			~(HDMI_TMDS_OUTCTL_tbcoe_mask | HDMI_TMDS_OUTCTL_tgcoe_mask | HDMI_TMDS_OUTCTL_trcoe_mask | HDMI_TMDS_OUTCTL_ocke_mask),
			(HDMI_TMDS_OUTCTL_tbcoe(0) | HDMI_TMDS_OUTCTL_tgcoe(0) | HDMI_TMDS_OUTCTL_trcoe(0) | HDMI_TMDS_OUTCTL_ocke(0)),
			HDMI_RX_MAC);

		lib_hdmi_z0_set(LN_ALL, 0);

		hdmi_rx_reg_mask32(MBIAS, ~MBIAS_reg_mbias_en_mask, 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(Z0POW, ~Z0POW_reg_z0_z300pow_mask, Z0POW_reg_z0_z300pow(0), HDMI_RX_PHY);
	}

}

void lib_hdmi_tmds_init(void)
{
	hdmi_rx_reg_mask32(HDMI_PORT_SWITCH,
		~HDMI_PORT_SWITCH_port_sel_mask,
		HDMI_PORT_SWITCH_port_sel(0), HDMI_RX_MAC);

	/* Port0 select */
	hdmi_rx_reg_mask32(MD,
		~MD_reg_ck_ckdet_mask, MD_get_reg_ck_ckdet(1), HDMI_RX_PHY);

	/* Enable TMDS input */
	hdmi_rx_reg_mask32(HDMI_TMDS_PWDCTL,
		~(HDMI_TMDS_PWDCTL_ebip_mask|HDMI_TMDS_PWDCTL_egip_mask|HDMI_TMDS_PWDCTL_erip_mask|HDMI_TMDS_PWDCTL_ecc_mask),
		(HDMI_TMDS_PWDCTL_ebip_mask|HDMI_TMDS_PWDCTL_egip_mask|HDMI_TMDS_PWDCTL_erip_mask|HDMI_TMDS_PWDCTL_ecc_mask),
		HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_VCR,
		~HDMI_VCR_iclk_sel_mask, HDMI_VCR_iclk_sel(0), HDMI_RX_MAC);
	/* Measure input clock source sel */
	hdmi_rx_reg_mask32(HDMI_TMDS_CPS,
		~HDMI_TMDS_CPS_clkv_meas_sel_mask, HDMI_TMDS_CPS_clkv_meas_sel(3), HDMI_RX_MAC);

}

void lib_hdmi_mac_init(void)
{
	hdmi_rx_reg_mask32(HDMI_PHY_FIFO_CR1,
		~((HDMI_PHY_FIFO_CR1_port0_bclk_inv_mask|HDMI_PHY_FIFO_CR1_port0_gclk_inv_mask|HDMI_PHY_FIFO_CR1_port0_rclk_inv_mask)),
		(HDMI_PHY_FIFO_CR1_port0_bclk_inv_mask|HDMI_PHY_FIFO_CR1_port0_gclk_inv_mask|HDMI_PHY_FIFO_CR1_port0_rclk_inv_mask),
		HDMI_RX_MAC);

	lib_hdmi_mac_afifo_enable();

	/* 20161018: SL8800 HDCP CTS1.4, contiune test without disconnect tmds_clock */
	/* hdcp cts1.4 : Bstatus (MSB): 0x00 */
	hdmi_rx_reg_write32(HDMI_SCR, 0x163, HDMI_RX_MAC);
	/* Enable Audio FIFO */
	hdmi_rx_reg_mask32(HDMI_AFCR,
		~(HDMI_AFCR_audio_test_enable_mask|0x07), 0x06, HDMI_RX_MAC);
	/* Enable video & audio output */
	hdmi_rx_reg_write32(HDMI_AVMCR, 0x48, HDMI_RX_MAC);
	/* Disable watch dog */
	hdmi_rx_reg_write32(HDMI_WDCR0, 0x00, HDMI_RX_MAC);


#if HDMI2p0
	hdmi_rx_reg_mask32(HDMI_SCDC_CR,
		~HDMI_SCDC_CR_scdc_en_mask, HDMI_SCDC_CR_scdc_en_mask, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_2P0_CR,
		~HDMI_2P0_CR_hdmi_2p0_en_mask,
		HDMI_2P0_CR_hdmi_2p0_en_mask, HDMI_RX_MAC);
	/*  HDMI2.0/10.4.1.2/Sink Devices compliant with this version of the specification shall set Sink Version = 1 */
	lib_hdmi_scdc_write(0x01, 0x01);
#endif

	hdmi_rx_reg_mask32(HDMI_HDCP_PCR,
		~(HDMI_HDCP_PCR_km_clk_sel_mask|HDMI_HDCP_PCR_hdcp_vs_sel_mask),
		(HDMI_HDCP_PCR_km_clk_sel_mask|HDMI_HDCP_PCR_hdcp_vs_sel_mask), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_VCR,
		~(HDMI_VCR_prdsam_mask|HDMI_VCR_csam_mask),
		HDMI_VCR_prdsam(1)|HDMI_VCR_csam(1), HDMI_RX_MAC);

	hdmi_rx_reg_write32(HDMI_MAGCR0, 0xE000, HDMI_RX_MAC);

	hdmi_rx_reg_write32(HDMI_INTCR, 0, HDMI_RX_MAC);
	/* Not inverse EVEN/ODD */
	hdmi_rx_reg_mask32(HDMI_VCR, ~(HDMI_VCR_eoi_mask), 0, HDMI_RX_MAC);
	/* Disable packet variation Watch Dog */
	hdmi_rx_reg_mask32(HDMI_PAMICR, ~HDMI_PAMICR_icpvsb_mask, 0x00, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_TMDS_ERRC,
		~HDMI_TMDS_ERRC_nl_mask, HDMI_TMDS_ERRC_nl(3), HDMI_RX_MAC);
	/*  Enable BCH Function */
	hdmi_rx_reg_mask32(HDMI_BCHCR,
		~(HDMI_BCHCR_pe_mask|HDMI_BCHCR_bche_mask|HDMI_BCHCR_enrwe_mask|HDMI_BCHCR_spcss_mask),
		(HDMI_BCHCR_pe_mask|HDMI_BCHCR_bche_mask|HDMI_BCHCR_enrwe_mask|HDMI_BCHCR_spcss_mask),
		HDMI_RX_MAC);
	/* Clear Audio Watch Dog and Set X: 15 */
	hdmi_rx_reg_mask32(HDMI_WDCR0, ~0xFFDF9E, 0x00, HDMI_RX_MAC);

#if MEASURE_FROM_TMDS_CLOCK
	hdmi_rx_reg_mask32(HDMI_CTS_FIFO_CTL,
		~(HDMI_CTS_FIFO_CTL_offms_clock_sel_mask), 0x0, HDMI_RX_MAC);
#else
	hdmi_rx_reg_mask32(HDMI_CTS_FIFO_CTL,
		~(HDMI_CTS_FIFO_CTL_offms_clock_sel_mask),
		HDMI_CTS_FIFO_CTL_offms_clock_sel_mask, HDMI_RX_MAC);
#endif

	/* Reset CED until measure done */
	lib_hdmi_char_err_rst(1);

	/* When ac on, need this for hdcp auth, otherwise no clock in MSHG-800 */
	lib_hdmi_mac_release();

}

unsigned char lib_hdmi_hdcp14_is_onoff(void)
{
	unsigned char hdcp_en;

	hdcp_en = HDMI_HDCP_CR_get_hdcp_en(hdmi_rx_reg_read32(HDMI_HDCP_CR, HDMI_RX_MAC));
	return hdcp_en;
}

void lib_hdmi_meas_select_port(void)
{
	hdmi_rx_reg_mask32(HDMI_PORT_SWITCH,
		~HDMI_PORT_SWITCH_offms_port_sel_mask,
		HDMI_PORT_SWITCH_offms_port_sel(0), HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_rgb_status_ready(void)
{
	unsigned int rgb_cd;
	unsigned char ready;

	ready = 0;

	rgb_cd = hdmi_rx_reg_read32(HDMI_TMDS_CTRL, HDMI_RX_MAC) & HDMI_TMDS_CTRL_rgbcd_mask;
	if (rgb_cd == HDMI_TMDS_CTRL_rgbcd_mask)
		ready = 1;

	return ready;
}

void lib_hdmi_clear_rgb_status(void)
{
	hdmi_rx_reg_write32(HDMI_TMDS_CTRL,
		HDMI_TMDS_CTRL_rgbcd_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_vsync_checked(void)
{
	unsigned char i;

	hdmi_rx_reg_write32(HDMI_TMDS_CTRL, HDMI_TMDS_CTRL_yo_mask, HDMI_RX_MAC);
	for (i = 0; i < 15; i++) {
		if (HDMI_TMDS_CTRL_get_yo(hdmi_rx_reg_read32(HDMI_TMDS_CTRL, HDMI_RX_MAC)))
			return TRUE;

		HDMI_DELAYUS(5000);
	}

	HDMI_PRINTF("[WARNING] Vsync cannot seen?\n");
	return FALSE;
}

unsigned char lib_hdmi_get_color_depth(void)
{
	unsigned char cd;

	cd = HDMI_TMDS_DPC0_dpc_cd(hdmi_rx_reg_read32(HDMI_TMDS_DPC0, HDMI_RX_MAC));
	if (cd > 3)
		return (cd-4);
	else
		return 0;
}

void lib_hdmi_clear_interlace_reg(void)
{
	unsigned int val;

#if HDMI_INT_PRO_CHG_FLAG_ENABLE
	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask));
	hdmi_rx_reg_write32(HDMI_VCR,
		(val|HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask), HDMI_RX_MAC);
#else
	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask));
	hdmi_rx_reg_write32(HDMI_VCR, (val|HDMI_VCR_eot_mask|HDMI_VCR_se_mask), HDMI_RX_MAC);
#endif

	/* Reset vsync */
	hdmi_rx_reg_write32(HDMI_TMDS_CTRL, HDMI_TMDS_CTRL_yo_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_get_is_interlace(HDMI_MS_T ms_mode)
{
	unsigned char i;

	if (ms_mode == HDMI_MS_ONESHOT) {
		lib_hdmi_clear_interlace_reg();
		for (i = 0; i < 4; i++)
			lib_hdmi_vsync_checked();
	}

	if (HDMI_VCR_get_se(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC))) {
		lib_hdmi_clear_interlace_reg();
		return 0;
	} else {
		return HDMI_VCR_get_eot(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	}
}

unsigned char lib_hdmi_get_is_interlace_change(void)
{
#if HDMI_INT_PRO_CHG_FLAG_ENABLE
	if (HDMI_VCR_get_int_pro_chg_flag(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC)))
		return TRUE;
#endif

	return FALSE;
}

void lib_hdmi_set_repeat_manual(unsigned char rep_value)
{
	unsigned int val;

	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask|HDMI_VCR_prdsam_mask));
	hdmi_rx_reg_write32(HDMI_VCR, val, HDMI_RX_MAC);

	val &= ~HDMI_VCR_dsc_mask;
	hdmi_rx_reg_write32(HDMI_VCR, val|HDMI_VCR_dsc(rep_value), HDMI_RX_MAC);
}

void lib_hdmi_set_repeat_auto(void)
{
	unsigned int val;

	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask));
	hdmi_rx_reg_write32(HDMI_VCR, val|HDMI_VCR_prdsam_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_get_pixelrepeat(void)
{
	if (HDMI_VCR_get_prdsam(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC)))
		return HDMI_VCR_get_dsc_r(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	else
		return HDMI_VCR_get_dsc(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));

}

void lib_hdmi_set_colorspace_manual(unsigned char color_space)
{
	unsigned int val;

	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask|HDMI_VCR_csam_mask));
	hdmi_rx_reg_write32(HDMI_VCR, val, HDMI_RX_MAC);

	HDMI_DELAYMS(20);

	val &= ~HDMI_VCR_csc_mask;
	hdmi_rx_reg_write32(HDMI_VCR, val|HDMI_VCR_csc(color_space), HDMI_RX_MAC);
}

void lib_hdmi_set_colorspace_auto(void)
{
	unsigned int val;

	val = hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC) & (~(HDMI_VCR_int_pro_chg_flag_mask|HDMI_VCR_eot_mask|HDMI_VCR_se_mask));
	hdmi_rx_reg_write32(HDMI_VCR, val|HDMI_VCR_csam_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_get_colorspace(void)
{
	unsigned char csc;

	if (HDMI_VCR_get_csam(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC)))
		csc = HDMI_VCR_get_csc_r(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	else
		csc = HDMI_VCR_get_csc(hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));

	return csc;
}

unsigned char lib_hdmi_is_hdmi_mode(void)
{
	unsigned char mode;
	unsigned int scr_val;

	mode = MODE_DVI;

	scr_val = hdmi_rx_reg_read32(HDMI_SCR, HDMI_RX_MAC);
	if (HDMI_SCR_get_mode(scr_val)) {
		if (HDMI_SCR_get_msmode(scr_val))
			mode = MODE_HDMI;
		goto exit;
	}

	scr_val = hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC);
	if (HDMI_SR_get_mode(scr_val))
		mode = MODE_HDMI;

exit:
	return mode;
}

#define AVI_Data_BYTE4     7
#define VSIF_PB4           209
#define VSIF_PB5           210
unsigned char lib_hdmi_get_vic(void)
{
	unsigned char reg_val;
	unsigned char vic;

	hdmi_rx_reg_write32(HDMI_PSAP, AVI_Data_BYTE4, HDMI_RX_MAC);

	vic = (hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC)) & 0x7F;

	if (vic == 0) {
		/* Get extened VIC */
		hdmi_rx_reg_write32(HDMI_PSAP, VSIF_PB4, HDMI_RX_MAC);
		reg_val = hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC);

		if ((reg_val>>5) == 1) {
				/* HDMI_Video_Format==1 */
				hdmi_rx_reg_write32(HDMI_PSAP, VSIF_PB5, HDMI_RX_MAC);
				reg_val = hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC);
				HDMIRX_DEBUG("Extended_VIC=%u", reg_val);
				/* hdmi_vic_table 108~111 */
				switch (reg_val) {
				case 1:
					vic = 108;
					break;
				case 2:
					vic = 109;
					break;
				case 3:
					vic = 110;
					break;
				case 4:
					vic = 111;
					break;
				default:
					vic = 0;
					break;
				}
		}
	} else if (vic > 107) {
		vic = 0;
	}

	return vic;

}

unsigned char lib_hdmi_get_video_format(void)
{
	unsigned char format;

	format = HDMI_VIDEO_FORMAT_get_hvf(hdmi_rx_reg_read32(HDMI_VIDEO_FORMAT, HDMI_RX_MAC));
	return format;
}

unsigned char lib_hdmi_get_3d_structure(void)
{
	unsigned char _3d_struct;

	_3d_struct = HDMI_3D_FORMAT_get_hdmi_3d_structure(hdmi_rx_reg_read32(HDMI_3D_FORMAT, HDMI_RX_MAC));
	return _3d_struct;
}

/**
 * lib_hdmi_get_3d_extdata
 *
 * Return:
 * 3D Ext Data
 * Horizontal sub-sampling
 * 0000:Odd/Left picture, Odd/Right picture
 * 0001:Odd/Left picture, Even/Right picture
 * 0010:Even/Left picture, Odd/Right picture
 * 0011:Even/Left picture, Even/Right picture
 * Quincunx matrix
 * 0100:Odd/Left picture, Odd/Right picture
 * 0101:Odd/Left picture, Even/Right picture
 * 0110:Even/Left picture, Odd/Right picture
 * 0111:Even/Left picture, Even/Right picture
 */
unsigned char lib_hdmi_get_3d_extdata(void)
{
	unsigned char _3d_extdata;

	_3d_extdata = HDMI_3D_FORMAT_get_hdmi_3d_ext_data(hdmi_rx_reg_read32(HDMI_3D_FORMAT, HDMI_RX_MAC));
	return _3d_extdata;
}

/**
 * lib_hdmi_get_vsi_vic
 *
 * Return:
 * HDMI_VIC
 * 0x01:4Kx2K@30Hz
 * 0x02:4Kx2K@25Hz
 * 0x03:4Kx2K@24Hz
 * 0x04:4Kx2K@24Hz(SMPTE)
 */
unsigned char lib_hdmi_get_vsi_vic(void)
{
	unsigned char vsi_vic;

	vsi_vic = HDMI_VIDEO_FORMAT_get_hdmi_vic(hdmi_rx_reg_read32(HDMI_VIDEO_FORMAT, HDMI_RX_MAC));
	return vsi_vic;
}


#define FVCO_MIN  250
#define FVCO_MAX  500
unsigned char lib_hdmi_set_video_pll(unsigned int b_clk, unsigned char cd, unsigned char is_interlace, unsigned char is_420)
{
	/*
	 * Fin =   Fxtal * b / 256
	 * Target vco = ( Fin * m / n )     , TagretVco_HB = 500 ,  TagretVco_LB=250
	 * Fin * m / n / 2^o / 2 * s = pixel clock = Fin * [24/30, 24/36, 24/48] ,  [10bits, 12bits,16bits]
	 *
	 * FVCO = Fin * m / n
	 * Fin = TMDS clock = pixel clock * SN/SM   --> pixel clock = Fin * SM / SN
	 * pixel clock = FVCO / 2^o / 2*s
	 * Fin * SM / SN = FVCO / 2^o / 2*s
	 * FVCO = Fin *  2^o * 2*s * SM/SN
	 * FVCO = Fin * 2^o * s * [24/30 * 2, 24/36 * 2, 24/48 * 2] --> Fin * 2^o * s * [8/5,4/3,1]
	 * 250 <  ( Fin * m / n )  < 500  -->  250 <   Fin * 2^o * s * [ 8/5 , 4/3, 1 ]   < 500
	 */
	unsigned char enable_2x = 0;
	unsigned int large_ratio, Smean, Stest, m, n, o, fvco;
	unsigned long pixel_clockx1024;
	unsigned int bpsin, fpfd1024;
	unsigned int i, j, tabsize;
	unsigned char dpll_rs, dpll_ip;


	hdmi_rx_reg_mask32(HDMI_YUV420_CR, ~(HDMI_YUV420_CR_en_mask), 0, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0, ~(HDMI_TMDS_DPC_SET0_dpc_en_mask), 0, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	/* Disable PLL */
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_pow_mask|HDMI_VPLLCR1_dpll_vcorstb_mask|HDMI_VPLLCR1_dpll_stoppsw_mask),
		0, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_rstb_mask), 0, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_freeze_mask),
		HDMI_VPLLCR1_dpll_freeze_mask, HDMI_RX_MAC);

	/*
	 * tmds clock = b * 27 / 256
	 * tmds clock = pixel clock * SN/SM --> b* 27 / 256 = pixel clock * SN/SM
	 * pixel clock = b * 27 * M / (SN * 256)
	 * pixel clock * 1024 = b * 27 * M * 1024 / (N * 256)
	 */
	pixel_clockx1024 = ((unsigned long)b_clk * 27 * dpll_ratio[cd].SM * 1024) / (dpll_ratio[cd].SN * 256);
	HDMI_PRINTF("pixel_clock = %ld\n", pixel_clockx1024);
	if (pixel_clockx1024 == 0) {
		HDMI_PRINTF("[ERR] pixel_clockx1024 is zero=%d,%d\n", b_clk, cd);
		return FALSE;
	}

	enable_2x = is_interlace;

	if ((pixel_clockx1024 < (160 * 1024) && enable_2x == 0) || (is_420)) {
		/* If pixel_clock is under 160MHz then enable 2X clock maybe for DI */
		enable_2x = 1;
	}


	/* Interlace must 2x */
	if (enable_2x) {
		large_ratio = 2;
		hdmi_rx_reg_mask32(HDMI_TMDS_CPS,
			~HDMI_TMDS_CPS_pll_div2_en_mask,
			HDMI_TMDS_CPS_pll_div2_en(1), HDMI_RX_MAC);
	} else {
		large_ratio = 1;
		hdmi_rx_reg_mask32(HDMI_TMDS_CPS,
			~HDMI_TMDS_CPS_pll_div2_en_mask,
			HDMI_TMDS_CPS_pll_div2_en(0), HDMI_RX_MAC);
	}


	if  (cd || enable_2x) {
		hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0,
			~HDMI_TMDS_DPC_SET0_dpc_bypass_dis_mask,
			HDMI_TMDS_DPC_SET0_dpc_bypass_dis(1), HDMI_RX_MAC);
	} else {
		hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0,
			~HDMI_TMDS_DPC_SET0_dpc_bypass_dis_mask,
			HDMI_TMDS_DPC_SET0_dpc_bypass_dis(0), HDMI_RX_MAC);
	}

	if (large_ratio != 1)
		pixel_clockx1024 <<= 1;

	/*
	 *  s = smean
	 * FVCO_MIN * 1024 / 2^o / 2s <= pixel_clock1024
	 * (pixel_clock1024 * 2^o) * 2s >= FVCO_MIN * 1024
	 * (pixel_clock1024 * 2) * 2s >= FVCO_MIN * 1024
	 * ex: s = 0 , 2s = Stest = 1 (no div)
	 * ex: s = 1 , 2s = Stest = 2 (div 2)
	 */
	o = 1;
	Smean = 0;
	Stest = 1;
	while (pixel_clockx1024 <= (200*1024)) {
		if (Smean == 0)
			Stest = 1;
		else
			Stest = Smean * 2;
		/* 2---> 2^o */
		if (((pixel_clockx1024*2)*Stest) >= (FVCO_MIN*1024))
			break;
		Smean++;
	};

	if (pixel_clockx1024 > (200*1024)) {
		/* >200MHz */
		o = 0;
		Smean = 0;
	}
#if 0
	else if (pixel_clockx1024 > (100*1024)) {
		/* 100MHz ~200MHz */
		o = 1;
		Smean = 0;
	} else if (pixel_clockx1024 > (50*1024)) {
		/* 50MHz ~100MHz */
		o = 1;
		Smean = 1;
	} else if (pixel_clockx1024 > (25*1024)) {
		/* 25MHz ~50MHz */
		o = 1;
		Smean = 2;
	} else {
		/* 13.5MHz~25MHz */
		o = 1;
		Smean = 4;
	}

	HDMI_PRINTF("Smean =  %d\n", Smean);

	if (Smean == 0)
		Stest = 1;
	else
		Stest = Smean * 2;
#endif

	/*
	 * FVCO = Fin * m / n
	 * Fin = TMDS clock = pixel clock * SN/SM   --> pixel clock = Fin * SM / SN
	 * pixel clock = FVCO / 2^o / 2*s *  (1/large_ratio)
	 * Fin * SM / SN = FVCO / 2^o / 2*s * (1/large_ratio)
	 * FVCO = Fin *  2^o * 2*s * SM/SN * large_ratio
	 * Fin * m / n = Fin * 2^o * 2*s * SM/SN * large_ratio
	 * m/n = 2^o * 2*s * SM/SN * large_ratio
	 * when n determined, m = SM * (2*s) * n * large_ratio * 2^o / SN
	 * m = (SM * (2*s) * n * large_ratio ) << o / SN
	 */
	n = 0;
	do {
		n += dpll_ratio[cd].RatioN;
		m = ((dpll_ratio[cd].RatioM * Stest * n * large_ratio)<<o) / dpll_ratio[cd].RatioN;
		/* HDMI_PRINTF( "step1%d %d\n", m, n); */
	} while (n < 2);

	/* M code must >= 6 */
	while (m < 8) {
		n += dpll_ratio[cd].RatioN;
		m = ((dpll_ratio[cd].RatioM * Stest * n * large_ratio)<<o) / dpll_ratio[cd].RatioN;
		/* HDMI_PRINTF( "step2:%d %d\n", m, n); */
	}


	if (n > 8) {
		n = 0;
		do {
			n += dpll_ratio[cd].RatioN;
			m = ((dpll_ratio[cd].RatioM * Stest * n * large_ratio)<<o) / dpll_ratio[cd].RatioN;
			/* HDMI_PRINTF( "step3:%d %d\n", m, n); */
		} while (n < 2);
	}


	fvco = (b_clk * 27 * m) / (256 * n);


	/* mag2 PLL bug  m min must > 1 , or PLL will crash */
	while (m < 3) {
		n <<= 1;
		m <<= 1;
	}
	if (n > 9)
		HDMI_PRINTF("[ERR] m=%d, n=%d > 9\n", m, n);

	/* HDMI_PRINTF("***************TMDS=%d\n", b_clk); */
	/* HDMI_PRINTF("***************cd=%d\n", cd); */
	/* HDMI_PRINTF("***************m=%d\n", m); */
	/* HDMI_PRINTF("***************n=%d\n", n); */
	/* HDMI_PRINTF("***************o=%d\n", o); */
	/* HDMI_PRINTF("***************s=%d\n", Smean); */
	/* HDMI_PRINTF("***************fraction1=%d\n", fraction1); */
	/* HDMI_PRINTF("***************fraction2=%d\n", fraction2); */
	/* HDMI_PRINTF("***************pixel_clockx1024=%ld\n", pixel_clockx1024); */
	/* HDMI_PRINTF("***************fvco=%d MHz\n", fvco); */
	/* HDMI_PRINTF("***************larget=%d\n", large_ratio); */
	HDMI_PRINTF("fvco=%d MHz\n", fvco);



#if 0
	/*
	 * Icp x (N/M) x (27M/Fin) = 0.95uA
	 * Icp x (N/M) x (27M/(27Mx1024/b) = 0.95
	 * Icp x (N/M) x (b/1024) = 0.95
	 * Icp x (N/M) x (b/1024) x 100 = 95
	 * Icp = (Mx1024x95)/(Nxbx100)
	 */
	unsigned int fraction1, fraction2;

	fraction1 = ((unsigned long)m*95*4*b_clk / (n*256*100));/* 2bit fractional part */
	fraction2 = 0x00;
	/* HDMI_PRINTF("***************fraction1=%d\n", fraction1); */

	if (fraction1 >= 10)
		fraction1 -= 10;

	if (fraction1 >= 40) {
		/* 2bit fractional part */
		fraction1 -= 40;
		fraction2 |= 0x04;
	}

	if (fraction1 >= 20) {
		/* 2bit fractional part */
		fraction1 -= 20;
		fraction2 |= 0x02;
	}

	if (fraction1 >= 10) {
		/* 2bit fractional part */
		fraction1 -= 10;
		fraction2 |= 0x01;
	}
	/* HDMI_PRINTF("***************fraction2=%d\n", fraction2); */
	/* fraction2 |= 0x18; */

#else

	tabsize = sizeof(video_pll_main_param)/sizeof(VIDEO_DPLL_FIX_T);

	/* Search main table */
	for (i = 0; i < tabsize; ++i) {
		if (((m - 2) == video_pll_main_param[i].dpll_M) && ((n - 2) == video_pll_main_param[i].dpll_N)) {
			dpll_ip = video_pll_main_param[i].dpll_IP;
			dpll_rs = video_pll_main_param[i].dpll_RS;
			break;
		}
	}

	/* Search other table,  if not fiind in main table */
	if (i >= tabsize) {
		/* fpfd = fin/(DPLL_BPSIN + (1-DPLL_BPSIN) * (DPLL_N+2)) */
		bpsin = HDMI_VPLLCR0_get_dpll_bpsin(hdmi_rx_reg_read32(HDMI_VPLLCR0, HDMI_RX_MAC));

		fpfd1024 = (b_clk * 27 * 1024 / 256) / (bpsin + ((1-bpsin) * n));

		/* (13.5 - 0.3) * 1024 = 13516  ,  (40+0.3) * 1024 = 41267  (margin +- 0.3M) */
		if ((fpfd1024 < 13516) || (fpfd1024 > 41267))/* margin +- 0.3M */
			HDMI_PRINTF("[WARNING] fpfd is not correct range %d \n", fpfd1024);

		for (j = 0; j < 4; ++j) {
			if (((m - 2) >= video_pll_others_param[j].min_M) &&
				((m - 2) <= video_pll_others_param[j].max_M)) {

				dpll_ip = video_pll_others_param[j].dpll_IP;
				dpll_rs = video_pll_others_param[j].dpll_RS;
				break;
			}
		}

		if (j == 4) {
			dpll_ip = 2;
			dpll_rs = 3;
			HDMI_PRINTF("[ERROR] video pll table not find\n");
		}
	}


	/* HDMI_PRINTF("***************ip=%d\n", dpll_ip); */
	/* HDMI_PRINTF("***************rs=%d\n", dpll_rs); */

#endif

	/* Set video PLL parameter */
	hdmi_rx_reg_write32(HDMI_VPLLCR0,
		HDMI_VPLLCR0_dpll_m(m-2) | HDMI_VPLLCR0_dpll_o(o) |
		HDMI_VPLLCR0_dpll_n(n-2) | HDMI_VPLLCR0_dpll_rs(dpll_rs) |
		HDMI_VPLLCR0_dpll_ip(dpll_ip), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_cp_mask | HDMI_VPLLCR1_dpll_cs_mask),
		HDMI_VPLLCR1_dpll_cp(1) | HDMI_VPLLCR1_dpll_cs(3), HDMI_RX_MAC);
	/* Set video PLL output divider */
	hdmi_rx_reg_write32(HDMI_MN_SCLKG_DIVS, Smean, HDMI_RX_MAC);
	/* Video PLL double buffer load */
	hdmi_rx_reg_mask32(HDMI_MN_SCLKG_CTRL,
		~HDMI_MN_SCLKG_CTRL_sclkg_dbuf_mask,
		HDMI_MN_SCLKG_CTRL_sclkg_dbuf_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);

	/* Video PLL power enable */
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_ldo_pow_mask),
		HDMI_VPLLCR1_dpll_ldo_pow_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~(HDMI_VPLLCR1_dpll_pow_mask|HDMI_VPLLCR1_dpll_stoppsw_mask),
		HDMI_VPLLCR1_dpll_pow_mask|HDMI_VPLLCR1_dpll_stoppsw_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~HDMI_VPLLCR1_dpll_vcorstb_mask, HDMI_VPLLCR1_dpll_vcorstb_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~HDMI_VPLLCR1_dpll_rstb_mask, HDMI_VPLLCR1_dpll_rstb_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(40);
	hdmi_rx_reg_mask32(HDMI_VPLLCR1,
		~HDMI_VPLLCR1_dpll_freeze_mask, 0, HDMI_RX_MAC);

	/* PLL clock need to enable ouput before pll_pow and 420_en on */
	lib_hdmi_video_output(1);

	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0,
		~(HDMI_TMDS_DPC_SET0_dpc_en_mask), HDMI_TMDS_DPC_SET0_dpc_en_mask, HDMI_RX_MAC);
	HDMI_DELAYUS(1);
	hdmi_rx_reg_mask32(HDMI_YUV420_CR,
		~(HDMI_YUV420_CR_en_mask), HDMI_YUV420_CR_en(is_420), HDMI_RX_MAC);

	return TRUE;
}


void lib_hdmi_video_output(unsigned char on)
{
	if (on)
		hdmi_rx_reg_mask32(HDMI_AVMCR,
			~HDMI_AVMCR_ve_mask, HDMI_AVMCR_ve_mask, HDMI_RX_MAC);
	else
		hdmi_rx_reg_mask32(HDMI_AVMCR,
			~HDMI_AVMCR_ve_mask, 0, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_video_output(void)
{
	unsigned char ve;

	ve = HDMI_AVMCR_get_ve(hdmi_rx_reg_read32(HDMI_AVMCR, HDMI_RX_MAC));
	return ve;
}

void lib_hdmi_clear_avmute(void)
{
	hdmi_rx_reg_mask32(HDMI_AVMCR,
		~(HDMI_AVMCR_avmute_flag_mask), HDMI_AVMCR_avmute_flag_mask, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_AVMCR,
		~(HDMI_AVMCR_avmute_flag_mask), 0, HDMI_RX_MAC);
}

unsigned char lib_hdmi_get_avmute(void)
{
	unsigned char avmute;

	avmute = HDMI_SR_get_avmute(hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	return avmute;
}

unsigned char lib_hdmi_get_bch_1bit_error(void)
{
	unsigned char bches;

	bches = HDMI_BCHCR_get_bches(hdmi_rx_reg_read32(HDMI_BCHCR, HDMI_RX_MAC));
	return bches;
}

unsigned char lib_hdmi_get_bch_2bit_error(void)
{
	unsigned char bches2;

	bches2 = HDMI_BCHCR_get_bches2(hdmi_rx_reg_read32(HDMI_BCHCR, HDMI_RX_MAC));
	return bches2;
}

void lib_hdmi_bch_error_clr(void)
{
	hdmi_rx_reg_mask32(HDMI_BCHCR,
		~(HDMI_BCHCR_bches_mask|HDMI_BCHCR_bches2_mask),
		(HDMI_BCHCR_bches_mask|HDMI_BCHCR_bches2_mask), HDMI_RX_MAC);
}

void lib_hdmi_wdm_enable(unsigned char enable)
{
	hdmi_rx_reg_mask32(HDMI_WDCR0,
		~HDMI_WDCR0_wdm_mask, HDMI_WDCR0_wdm(enable), HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_wdm_enable(void)
{
	unsigned char wdm;

	wdm = HDMI_WDCR0_get_wdm(hdmi_rx_reg_read32(HDMI_WDCR0, HDMI_RX_MAC));
	return wdm;
}

void lib_hdmi_auto_avmute_enable(unsigned char enable)
{
	hdmi_rx_reg_mask32(HDMI_WDCR0,
		~HDMI_WDCR0_asmfe_mask, HDMI_WDCR0_asmfe(enable), HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_auto_avmute_enable(void)
{
	unsigned char asmfe;

	asmfe = HDMI_WDCR0_get_asmfe(hdmi_rx_reg_read32(HDMI_WDCR0, HDMI_RX_MAC));
	return asmfe;
}

void lib_hdmi_tmds_out_ctrl(unsigned char bypass, unsigned int r, unsigned int g, unsigned int b)
{
	hdmi_rx_reg_mask32(HDMI_TMDS_OUT_CTRL,
		~(HDMI_TMDS_OUT_CTRL_tmds_bypass_mask),
		HDMI_TMDS_OUT_CTRL_tmds_bypass(bypass), HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDMI_TMDS_ROUT, r, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDMI_TMDS_GOUT, g, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDMI_TMDS_BOUT, b, HDMI_RX_MAC);
}


void lib_hdmi_mac_afifo_enable(void)
{
	hdmi_rx_reg_mask32(HDMI_PHY_FIFO_CR0,
		~((HDMI_PHY_FIFO_CR0_port0_b_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_b_flush_mask|
		HDMI_PHY_FIFO_CR0_port0_g_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_g_flush_mask|
		HDMI_PHY_FIFO_CR0_port0_r_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_r_flush_mask)),
		(HDMI_PHY_FIFO_CR0_port0_b_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_b_flush_mask|
		HDMI_PHY_FIFO_CR0_port0_g_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_g_flush_mask|
		HDMI_PHY_FIFO_CR0_port0_r_afifo_en_mask|HDMI_PHY_FIFO_CR0_port0_r_flush_mask),
		HDMI_RX_MAC);
}

void lib_hdmi_420_en(unsigned char en)
{
	hdmi_rx_reg_mask32(HDMI_YUV420_CR,
		~HDMI_YUV420_CR_en_mask, HDMI_YUV420_CR_get_en(en), HDMI_RX_MAC);
}

void lib_hdmi_crc_check(void)
{
	hdmi_rx_reg_write32(HDMI_TMDS_CRCC,
		HDMI_TMDS_CRCC_crc_r_en_mask|HDMI_TMDS_CRCC_crc_g_en_mask|HDMI_TMDS_CRCC_crc_b_en_mask|
		HDMI_TMDS_CRCC_crc_nonstable_mask|HDMI_TMDS_CRCC_crcc_mask, HDMI_RX_MAC);
}

unsigned int lib_hdmi_read_crc(void)
{
	return hdmi_rx_reg_read32(HDMI_TMDS_CRCO0, HDMI_RX_MAC);
}


#if HDMI2p0
unsigned char lib_hdmi_scdc_read(unsigned char addr)
{
	hdmi_rx_reg_write32(HDMI_SCDC_AP, addr, HDMI_RX_MAC);
	return hdmi_rx_reg_read32(HDMI_SCDC_DP, HDMI_RX_MAC);
}

void lib_hdmi_scdc_write(unsigned char addr, unsigned char value)
{
	hdmi_rx_reg_write32(HDMI_SCDC_AP, addr, HDMI_RX_MAC);
	hdmi_rx_reg_write32(HDMI_SCDC_DP, value, HDMI_RX_MAC);
}

unsigned char lib_hdmi2p0_get_tmds_config(void)
{
	return lib_hdmi_scdc_read(0x20);
}

void lib_hdmi2p0_reset_scdc(void)
{
	hdmi_rx_reg_mask32(HDMI_SCDC_CR,
		~HDMI_SCDC_CR_scdc_reset_mask,
		HDMI_SCDC_CR_scdc_reset_mask, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_SCDC_CR,
		~HDMI_SCDC_CR_scdc_reset_mask, 0, HDMI_RX_MAC);
	HDMI_PRINTF("HDMI2.0 SCDC: clear\n");
}

void lib_hdmi2p0_scdc_update_flag(void)
{
	/* HDMI2.0 spec: 10.4.1.3 */
	if (((lib_hdmi_scdc_read(0x10)&_BIT2) == _BIT2)) {
		lib_hdmi_scdc_write(0x10, 0x00);
		lib_hdmi_scdc_write(0x10, 0x04);
	}
}

void lib_hdmi2p0_scramble_enable(unsigned char on_off)
{
	if (on_off) {
		/* HDMI_PRINTF("HDMI2.0 Scramble Enable\n"); */
		/* For RGB bug */
		hdmi_rx_reg_mask32(HDMI_SCR,
			~(HDMI_SCR_dvi_reset_ds_cm_en_mask), 0, HDMI_RX_MAC);
		/* Force scramble mode for no scramble bug */
		hdmi_rx_reg_mask32(HDMI_SCR_CR,
			~(HDMI_SCR_CR_scr_en_fw_mask|HDMI_SCR_CR_scr_auto_mask),
			HDMI_SCR_CR_scr_en_fw_mask, HDMI_RX_MAC);
		/* For 6G audio bug setting */
		hdmi_rx_reg_mask32(HDMI_SCR,
			~(HDMI_SCR_mode_mask|HDMI_SCR_msmode_mask),
			(HDMI_SCR_mode_mask|HDMI_SCR_msmode_mask), HDMI_RX_MAC);
	} else {
		/* HDMI_PRINTF("HDMI2.0 Scramble disable\n"); */
		hdmi_rx_reg_mask32(HDMI_SCR,
			~(HDMI_SCR_dvi_reset_ds_cm_en_mask),
			HDMI_SCR_dvi_reset_ds_cm_en_mask, HDMI_RX_MAC);
		/* For 6G audio bug setting */
		/* Force scramble mode for no scramble bug */
		hdmi_rx_reg_mask32(HDMI_SCR_CR,
			~(HDMI_SCR_CR_scr_en_fw_mask|HDMI_SCR_CR_scr_auto_mask),
			0, HDMI_RX_MAC);
		/* For 6G audio bug setting */
		hdmi_rx_reg_mask32(HDMI_SCR,
			~(HDMI_SCR_mode_mask|HDMI_SCR_msmode_mask), 0, HDMI_RX_MAC);
	}
}

#endif


void lib_hdmi_read_packet_sram(unsigned int start_addr, unsigned char len, unsigned char *pbuf)
{
	unsigned char i;

	hdmi_rx_reg_write32(HDMI_PSAP, start_addr, HDMI_RX_MAC);
	for (i = 0; i < len; i++) {
		hdmi_rx_reg_write32(HDMI_PSAP, start_addr+i, HDMI_RX_MAC);
		pbuf[i] = hdmi_rx_reg_read32(HDMI_PSDP, HDMI_RX_MAC);
	}
}

unsigned char lib_hdmi_is_fvs_received(void)
{
	return HDMI_GPVS_get_fvsps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_fvs_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_fvsps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_vs_received(void)
{
	return HDMI_GPVS_get_vsps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_vs_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_vsps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_avi_received(void)
{
	return HDMI_GPVS_get_avips(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_avi_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_avips_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_spd_received(void)
{
	return HDMI_GPVS_get_spdps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_spd_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_spdps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_audiopkt_received(void)
{
	return HDMI_GPVS_get_aps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_audiopkt_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_aps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_drm_received(void)
{
	return HDMI_GPVS_get_drmps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_drm_received_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_drmps_mask, HDMI_RX_MAC);
}


void lib_hdmi_set_rsv_packet_type(unsigned char index, unsigned char pkt_type)
{
	hdmi_rx_reg_mask32(HDMI_PTRSV1,
		~(HDMI_PTRSV1_pt0_mask<<(index<<3)),
		pkt_type<<(index<<3), HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_rsv_packet0_received(void)
{
	return HDMI_GPVS_get_rsv0ps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
}

void lib_hdmi_clear_rsv_packet0_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_rsv0ps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_rsv_packet1_received(void)
{
	unsigned char rsv1ps;

	rsv1ps = HDMI_GPVS_get_rsv1ps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
	return rsv1ps;
}

void lib_hdmi_clear_rsv_packet1_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_rsv1ps_mask, HDMI_RX_MAC);
}


unsigned char lib_hdmi_is_rsv_packet2_received(void)
{
	unsigned char rsv2ps;

	rsv2ps = HDMI_GPVS_get_rsv2ps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
	return rsv2ps;
}

void lib_hdmi_clear_rsv_packet2_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_rsv2ps_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_is_rsv_packet3_received(void)
{
	unsigned char rsv3ps;

	rsv3ps = HDMI_GPVS_get_rsv3ps(hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC));
	return rsv3ps;
}

void lib_hdmi_clear_rsv_packet3_status(void)
{
	hdmi_rx_reg_write32(HDMI_GPVS, HDMI_GPVS_rsv3ps_mask, HDMI_RX_MAC);
}


void lib_hdmi_gcp_ackg_header_parsing_mode(void)
{
	hdmi_rx_reg_mask32(HDMI_SCR,
		~HDMI_SCR_packet_header_parsing_mode_mask,
		HDMI_SCR_packet_header_parsing_mode(1),
		HDMI_RX_MAC);
}

void lib_hdmi_valid_format_condition(void)
{
	hdmi_rx_reg_mask32(HDMI_TMDS_CPS,
		~(HDMI_TMDS_CPS_pk_gb_num_mask | HDMI_TMDS_CPS_vd_gb_num_mask |
		HDMI_TMDS_CPS_pk_pre_num_mask | HDMI_TMDS_CPS_vd_pre_num_mask),
		(HDMI_TMDS_CPS_pk_gb_num(HDMI_PK_GB_NUM) | HDMI_TMDS_CPS_vd_gb_num(HDMI_VD_GB_NUM) |
		HDMI_TMDS_CPS_pk_pre_num(HDMI_PK_PRE_NUM) | HDMI_TMDS_CPS_vd_pre_num(HDMI_VD_PRE_NUM)),
		HDMI_RX_MAC);
}

void lib_hdmi_audio_init(void)
{
	/* Clear Overflow,Underflow,phase_non_lock, auto load double buffter */
	hdmi_rx_reg_write32(HDMI_DBCR, 0x00, HDMI_RX_MAC);
	/* Disable audio watch dog */
	hdmi_rx_reg_mask32(HDMI_WDCR0, ~HDMI_WDCR0_awdck_mask, 0x00, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_WDCR0,
		~(HDMI_WDCR0_awdfu_mask|HDMI_WDCR0_awdfo_mask|HDMI_WDCR0_awdap_mask|HDMI_WDCR0_awdct_mask),
		0x0, HDMI_RX_MAC);

	lib_hdmi_audio_output(0);

	/*Disable FIFO trend tracking*/
	hdmi_rx_reg_write32(HDMI_PSCR, 0xE2, HDMI_RX_MAC);
	/*Update Double Buffer*/
	hdmi_rx_reg_write32(HDMI_CMCR, 0x50, HDMI_RX_MAC);/* K code=2 */

	hdmi_rx_reg_mask32(HDMI_WDCR0,
		~(HDMI_WDCR0_wdm_mask|HDMI_WDCR0_asmfe_mask),
		HDMI_WDCR0_wdm(0)|HDMI_WDCR0_asmfe(0), HDMI_RX_MAC);

}

unsigned char lib_hdmi_audio_is_nonpcm(void)
{
	return HDMI_SR_get_spdiftype(hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
}

void lib_hdmi_audio_pop_n_cts(void)
{
	hdmi_rx_reg_mask32(HDMI_ACRCR,
		~(HDMI_ACRCR_pucnr_mask|HDMI_ACRCR_pucsr_mask),
		(HDMI_ACRCR_pucnr_mask|HDMI_ACRCR_pucsr_mask), HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_pop_n_cts_done(void)
{
	return ((hdmi_rx_reg_read32(HDMI_ACRCR, HDMI_RX_MAC) & (HDMI_ACRCR_pucnr_mask|HDMI_ACRCR_pucsr_mask)) == 0);
}

unsigned int lib_hdmi_audio_get_n(void)
{
	unsigned int n;

	n = HDMI_ACRSR1_get_n(hdmi_rx_reg_read32(HDMI_ACRSR1, HDMI_RX_MAC));
	return n;
}

unsigned int lib_hdmi_audio_get_cts(void)
{
	unsigned int cts;

	cts = HDMI_ACRSR0_get_cts(hdmi_rx_reg_read32(HDMI_ACRSR0, HDMI_RX_MAC));
	return cts;
}


void lib_hdmi_audio_clear_fs(void)
{
	hdmi_rx_reg_write32(HDMI_ASR0,
		(HDMI_ASR0_fsre_mask|HDMI_ASR0_fsif_mask|HDMI_ASR0_fscs_mask), HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_fs_from_cs(void)
{
	unsigned char fbcs;

	fbcs = HDMI_ASR0_fscs(hdmi_rx_reg_read32(HDMI_ASR0, HDMI_RX_MAC));
	return fbcs;
}

unsigned char lib_hdmi_audio_get_freq_from_cs(void)
{
	unsigned char fbcs;

	fbcs = HDMI_ASR1_get_fbcs(hdmi_rx_reg_read32(HDMI_ASR1, HDMI_RX_MAC));
	return fbcs;
}

void lib_hdmi_audio_cts_bound(unsigned int clk)
{
	unsigned long cts_up, cts_low;

	if (clk > 5600) {
		/* 6G timing */
		cts_up = 0xfffff;
		cts_low = 445500 *7/8;
	} else if (clk > 2750) {
		/* 3G timing */
		cts_up = 421875 * 9/8;
		cts_low = 222750 * 7/8;
	} else if (clk > 1380) {
		/* 148M */
		cts_up = 421875 * 9/8;
		cts_low = 140625 * 7/8;
	} else if (clk > 660) {
		cts_up = 234375 * 9/8;
		cts_low = 74250 * 7/8 ;
	} else {
		cts_up = 60060 * 9/8;
		cts_low = 25200 * 7/8;
	}

	hdmi_rx_reg_mask32(HDMI_AUDIO_CTS_UP_BOUND,
		~(HDMI_AUDIO_CTS_UP_BOUND_cts_up_bound_mask),
		HDMI_AUDIO_CTS_UP_BOUND_cts_up_bound(cts_up), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_AUDIO_CTS_LOW_BOUND,
		~HDMI_AUDIO_CTS_LOW_BOUND_cts_low_bound_mask,
		HDMI_AUDIO_CTS_LOW_BOUND_cts_low_bound(cts_low), HDMI_RX_MAC);
}

void lib_hdmi_audio_n_bound(unsigned int freq)
{
	int N_up, N_low;

	if (freq > 190000) {
		/* 192k */
		N_up = 46592 *9/8;
		N_low = 20480 * 7/8 ;
	} else if (freq > 170000) {
		/* 176.4 */
		N_up = 71344 * 9/8;
		N_low = 17836 * 7/8;
	} else if (freq >80000) {
		/* 96 k 88.2k */
		N_up = 35672 * 9/8;
		N_low = 8918 * 7/8;
	} else {
		/* 32k  44.1k  48k */
		N_up = 17836 * 9/8;
		N_low = 3072 * 7/8;
	}

	hdmi_rx_reg_mask32(HDMI_AUDIO_N_UP_BOUND,
		~(HDMI_AUDIO_N_UP_BOUND_n_up_bound_mask),
		HDMI_AUDIO_N_UP_BOUND_n_up_bound(N_up), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_AUDIO_N_LOW_BOUND,
		~HDMI_AUDIO_N_LOW_BOUND_n_low_bound_mask,
		HDMI_AUDIO_N_LOW_BOUND_n_low_bound(N_low), HDMI_RX_MAC);

	HDMI_PRINTF("freq = %d Audio_N_Bound H = %d , L =%d\n", freq, N_up, N_low);
}


unsigned char lib_hdmi_audio_is_pll_unlock(void)
{
	unsigned char pllsts;

	pllsts = HDMI_SR_get_pllsts(hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	return pllsts;
}

void lib_hdmi_audio_wclr_pll_unlock(void)
{
	hdmi_rx_reg_write32(HDMI_SR, HDMI_SR_pllsts_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_is_fifo_overflow(void)
{
	unsigned char fifo_of;

	fifo_of = HDMI_SR_get_afifoof(hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	return fifo_of;
}

void lib_hdmi_audio_wclr_fifo_overflow(void)
{
	hdmi_rx_reg_write32(HDMI_SR, HDMI_SR_afifoof_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_is_fifo_underflow(void)
{
	unsigned char fifo_uf;

	fifo_uf = HDMI_SR_get_afifouf(hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC));
	return fifo_uf;
}

void lib_hdmi_audio_wclr_fifo_underflow(void)
{
	hdmi_rx_reg_write32(HDMI_SR, HDMI_SR_afifouf_mask, HDMI_RX_MAC);
}

void lib_hdmi_audio_clear_phase_error(void)
{
	hdmi_rx_reg_write32(HDMI_NCPER, 0xff, HDMI_RX_MAC);
}


void lib_hdmi_audio_generate(void)
{
	unsigned char i;
	unsigned int d_code;

	hdmi_rx_reg_mask32(HDMI_DBCR, 0xF0, 0x0F, HDMI_RX_MAC);

	d_code = hdmi_rx_reg_read32(HDMI_APLLCR3, HDMI_RX_MAC);

	for (i = 0; i < 5; i++) {
		if (d_code == hdmi_rx_reg_read32(HDMI_APLLCR3, HDMI_RX_MAC))
			break;
	}

	/* Pre-set D code */
	hdmi_rx_reg_write32(HDMI_DCAPR0, d_code, HDMI_RX_MAC);
	/* Pre-disable N/CTS tracking & FIFO depth */
	hdmi_rx_reg_write32(HDMI_PSCR, 0xE2, HDMI_RX_MAC);

	/* Enable audio Overflow & Underflow watch dog but not Audio type wdg */
	hdmi_rx_reg_mask32(HDMI_WDCR0,
		~(_BIT1|_BIT2|_BIT3|_BIT4), (_BIT1|_BIT2|_BIT3|_BIT4), HDMI_RX_MAC);
	/* Enable audio tmds clock  watch dog */
	hdmi_rx_reg_mask32(HDMI_WDCR0, ~_BIT15, _BIT15, HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_is_output(void)
{
	unsigned char aomc;

	aomc = HDMI_AVMCR_get_aomc(hdmi_rx_reg_read32(HDMI_AVMCR, HDMI_RX_MAC));

	return aomc;
}


void lib_hdmi_audio_output(unsigned char on)
{
	if (on) {
		hdmi_rx_reg_mask32(HDMI_AVMCR,
			~(HDMI_AVMCR_aoc_mask|HDMI_AVMCR_aomc_mask),
			(HDMI_AVMCR_aoc_mask|HDMI_AVMCR_aomc_mask), HDMI_RX_MAC);
		hdmi_rx_reg_mask32(HDMI_AOCR,
			~(HDMI_AOCR_spdifo1_mask|HDMI_AOCR_spdifo2_mask|
			HDMI_AOCR_spdifo3_mask|HDMI_AOCR_spdifo4_mask|
			HDMI_AOCR_i2so1_mask|HDMI_AOCR_i2so2_mask|
			HDMI_AOCR_i2so3_mask|HDMI_AOCR_i2so4_mask),
			(HDMI_AOCR_spdifo1_mask|HDMI_AOCR_spdifo2_mask|
			HDMI_AOCR_spdifo3_mask|HDMI_AOCR_spdifo4_mask|
			HDMI_AOCR_i2so1_mask|HDMI_AOCR_i2so2_mask|
			HDMI_AOCR_i2so3_mask|HDMI_AOCR_i2so4_mask),
			HDMI_RX_MAC);
	} else {
		hdmi_rx_reg_mask32(HDMI_AOCR,
			~(HDMI_AOCR_spdifo1_mask|HDMI_AOCR_spdifo2_mask|
			HDMI_AOCR_spdifo3_mask|HDMI_AOCR_spdifo4_mask|
			HDMI_AOCR_i2so1_mask|HDMI_AOCR_i2so2_mask|
			HDMI_AOCR_i2so3_mask|HDMI_AOCR_i2so4_mask),
			0, HDMI_RX_MAC);

		hdmi_rx_reg_mask32(HDMI_AVMCR,
			~(HDMI_AVMCR_aoc_mask|HDMI_AVMCR_aomc_mask),
			HDMI_AVMCR_aoc_mask, HDMI_RX_MAC);
	}
}

void lib_hdmi_audio_set_hbr_manual_mode(unsigned char manu, unsigned char mode_fw)
{
	hdmi_rx_reg_mask32(HDMI_HIGH_BIT_RATE_AUDIO_PACKET,
		~(HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_manual_mask |
		HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_fw_mask),
		HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_manual(manu) |
		HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_fw(mode_fw),
		HDMI_RX_MAC);

	/* Write 1 clear */
	hdmi_rx_reg_mask32(HDMI_HIGH_BIT_RATE_AUDIO_PACKET,
		~(HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_mask),
		HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode(1), HDMI_RX_MAC);
}

void lib_hdmi_audio_clear_hdr_status(void)
{
	hdmi_rx_reg_mask32(HDMI_HIGH_BIT_RATE_AUDIO_PACKET,
		~HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_mask,
		HDMI_HIGH_BIT_RATE_AUDIO_PACKET_hbr_audio_mode_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_audio_get_hbr_manual_mode(void)
{
	unsigned char manual_mode;

	manual_mode = HDMI_HIGH_BIT_RATE_AUDIO_PACKET_get_hbr_audio_mode_fw(hdmi_rx_reg_read32(HDMI_HIGH_BIT_RATE_AUDIO_PACKET, HDMI_RX_MAC));

	return manual_mode;
}


unsigned char lib_hdmi_audio_get_hbr_mode(void)
{
	unsigned char hbr_mode;

	hbr_mode = HDMI_HIGH_BIT_RATE_AUDIO_PACKET_get_hbr_audio_mode(hdmi_rx_reg_read32(HDMI_HIGH_BIT_RATE_AUDIO_PACKET, HDMI_RX_MAC));

	return hbr_mode;
}

unsigned char lib_hdmi_audio_get_channel_status15_0(unsigned int bitmask, unsigned int bitshift)
{
	hdmi_rx_reg_write32(HDMI_ACRCR, HDMI_ACRCR_pucsr_mask, HDMI_RX_MAC);
	HDMI_DELAYMS(80);
	return ((bitmask&(hdmi_rx_reg_read32(HDMI_ACS0, HDMI_RX_MAC)))>>bitshift);
}

unsigned char lib_hdmi_audio_get_channel_status39_16(unsigned int bitmask, unsigned int bitshift)
{
	hdmi_rx_reg_write32(HDMI_ACRCR, HDMI_ACRCR_pucsr_mask, HDMI_RX_MAC);
	HDMI_DELAYMS(80);
	return ((bitmask&(hdmi_rx_reg_read32(HDMI_ACS1, HDMI_RX_MAC)))>>bitshift);
}

void lib_hdmi_set_toggle_hpd_z0_flag(unsigned char uc_flag)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	/* HDMI_PRINTF("lib_hdmi_set_toggle_hpd_z0_flag=%d\n", uc_flag); */
	hdmi_toggle_hpd_z0_flag = uc_flag;
#endif
}

unsigned char lib_hdmi_get_toggle_hpd_z0_flag(void)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	return hdmi_toggle_hpd_z0_flag;
#endif

	return FALSE;
}

unsigned char lib_hdmi_toggle_hpd_z0_check(unsigned char ucInit)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	static unsigned int start_time = 0;
	static unsigned int current_time = 0;

	if (lib_hdmi_get_toggle_hpd_z0_flag() == FALSE)
		return TRUE;

	if (ucInit == TRUE) {
		/* Need to think, if start time almost overflow */
		start_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;
		current_time = start_time;
		HDMI_PRINTF("lib_hdmi_toggle_hpd_z0_check, start=%d\n", start_time);
		return TRUE;
	}

	current_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;

	if (current_time >= start_time) {
		if (current_time - start_time >= HDMI_START_TOGGLE_HPD_Z0_MS) {
			Hdmi_SetHPD(0);
			lib_hdmi_z0_set(LN_ALL, 0);
			HDMI_DELAYMS(HDMI_TOGGLE_HPD_Z0_MS);
			lib_hdmi_z0_set(LN_ALL, 1);
			Hdmi_SetHPD(1);
			HDMI_PRINTF("lib_hdmi_toggle_hpd_z0_check, time=%d\n", current_time);
			lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_ENABLE_DELAY);
			lib_hdmi_set_toggle_hpd_z0_flag(FALSE);
		}
	} else {
		/* current_time <= start_time */
		HDMI_PRINTF("lib_hdmi_toggle_hpd_z0_check over, start_time=%d, current_time=%d\n", start_time, current_time);
		lib_hdmi_set_toggle_hpd_z0_flag(FALSE);
	}
#endif /* End of #if HDMI_TOGGLE_HPD_Z0_ENABLE */

	return TRUE;
}

void lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_STATE_E state)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	/* HDMI_PRINTF("lib_hdmi_set_dc_on_delay_state=%d\n", state); */
	hdmi_dc_on_delay_state = state;
#endif
}

HDMI_DC_ON_STATE_E lib_hdmi_get_dc_on_delay_state(void)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	return hdmi_dc_on_delay_state;
#endif

	return HDMI_DC_ON_NONE;
}

unsigned char lib_hdmi_dc_on_delay_check(unsigned char ucInit)
{
#if HDMI_TOGGLE_HPD_Z0_ENABLE
	static unsigned int start_time = 0;
	static unsigned int current_time = 0;

	if (lib_hdmi_get_toggle_hpd_z0_flag() == FALSE)
		return TRUE;

	if (ucInit == TRUE) {
		if (lib_hdmi_get_dc_on_delay_state() != HDMI_DC_ON_ENABLE_DELAY)
			return TRUE;

		lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_START_TIME);
		/* Need to think, if start time almost overflow */
		start_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;
		current_time = start_time;
		HDMI_PRINTF("lib_hdmi_dc_on_delay_check, start=%d\n", start_time);
		return TRUE;
	}

	if (lib_hdmi_get_dc_on_delay_state() != HDMI_DC_ON_START_TIME)
		return TRUE;

	current_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;

	if (current_time >= start_time) {
		if (current_time - start_time >= HDMI_DC_ON_DELAY_MS) {
			HDMI_PRINTF("lib_hdmi_dc_on_delay_check, time=%d\n", current_time);
			lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_FINISH);
			return TRUE;
		}
	} else {
		/* current_time <= start_time */
		HDMI_PRINTF("lib_hdmi_dc_on_delay_check over, start_time=%d, current_time=%d\n", start_time, current_time);
		lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_NONE);
		return TRUE;
	}

	return FALSE;
#endif/* End of #if HDMI_TOGGLE_HPD_Z0_ENABLE */

	return TRUE;
}

void lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_STATE_E state)
{
#if HDMI_STR_TOGGLE_HPD_ENABLE
	/* HDMI_PRINTF("lib_hdmi_set_str_toggle_hpd_state=%d\n", state); */
	hdmi_str_toggle_hpd_state = state;
#endif
}

HDMI_STR_HPD_TOGGLE_STATE_E lib_hdmi_get_str_toggle_hpd_state(void)
{
#if HDMI_STR_TOGGLE_HPD_ENABLE
	return hdmi_str_toggle_hpd_state;
#endif

	return HDMI_STR_HPD_TOGGLE_NONE;
}

void lib_hdmi_set_delay_display_enable(unsigned char ucEnable)
{
#if HDMI_DISPLAY_DELAY_ENABLE
	/* HDMI_PRINTF("lib_hdmi_set_delay_display_enable=%d\n", ucEnable); */
	hdmi_delay_display_enable = ucEnable;
#endif
}

unsigned char lib_hdmi_get_delay_display_enable(void)
{
#if HDMI_DISPLAY_DELAY_ENABLE
	return hdmi_delay_display_enable;
#endif

	return _DISABLE;
}

void lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_STATE_STATE_E state)
{
#if HDMI_DISPLAY_DELAY_ENABLE
	/* HDMI_PRINTF("lib_hdmi_set_delay_display_state=%d\n", state); */
	hdmi_delay_display_state = state;
#endif
}

HDMI_DISPLAY_DELAY_STATE_STATE_E lib_hdmi_get_delay_display_state(void)
{
#if HDMI_DISPLAY_DELAY_ENABLE
	return hdmi_delay_display_state;
#endif

	return HDMI_DISPLAY_DELAY_NONE;
}

unsigned char lib_hdmi_delay_check_before_display(unsigned char ucInit)
{
#if HDMI_DISPLAY_DELAY_ENABLE
	static unsigned int start_time = 0;
	static unsigned int current_time = 0;
	unsigned int Delay_Time = 0;

	if (lib_hdmi_get_delay_display_enable() == _DISABLE)
		return TRUE;

	if (ucInit == TRUE) {
		if (lib_hdmi_get_delay_display_state() == HDMI_DISPLAY_DELAY_INIT) {
			lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_START);
			/* Need to think, if start time almost overflow */
			start_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;
			current_time = start_time;
			HDMI_PRINTF("lib_hdmi_delay_check_before_display, start=%d\n", start_time);
		}
		return TRUE;
	}

	if (lib_hdmi_get_delay_display_state() != HDMI_DISPLAY_DELAY_START)
		return TRUE;

	Delay_Time = lib_hdmi_get_delay_display_time();
	current_time = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K)/90;

	if (current_time >= start_time) {
		if (current_time - start_time >= Delay_Time) {
			HDMI_PRINTF("lib_hdmi_delay_check_before_display, time=%d\n", current_time);
			lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_FINISH);
			return TRUE;
		}
	} else {
		/* current_time <= start_time */
		HDMI_PRINTF("lib_hdmi_delay_check_before_display over, start_time=%d, current_time=%d\n", start_time, current_time);
		lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_FINISH);
		return TRUE;
	}

	return FALSE;
#endif/* End of #if HDMI_DISPLAY_DELAY_ENABLE */

	return TRUE;
}

unsigned int lib_hdmi_get_delay_display_time(void)
{
	unsigned int DelayTime = 0;/* ms */

	switch (lib_hdmi_get_specific_device()) {
	case HDMI_SPECIFIC_DEVICE_LHB_755:
		DelayTime = HDMI_DISPLAY_DELAY_LHB_755_MS;
		break;

	case HDMI_SPECIFIC_DEVICE_ROKU_ULTRA_4640R:
		DelayTime = HDMI_DISPLAY_DELAY_ROKU_ULTRA_4640R_MS;
		break;

	case HDMI_SPECIFIC_DEVICE_SAMSUNG_GX_HC630CH:
		DelayTime = HDMI_DISPLAY_DELAY_SAMSUNG_GX_HC630CH_MS;
		break;

	case HDMI_SPECIFIC_DEVICE_KT_STB_KAO_CT1100:
		DelayTime = HDMI_DISPLAY_DELAY_KT_STB_KAO_CT1100_MS;
		break;

	default:
		DelayTime = 0;
		break;
	}

	return DelayTime;
}


void lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_E device)
{
	/* HDMI_PRINTF("lib_hdmi_set_specific_device=%d\n", device); */
	hdmi_specific_device = device;
}

HDMI_SPECIFIC_DEVICE_E lib_hdmi_get_specific_device(void)
{
	return hdmi_specific_device;
}

void lib_hdmi_misc_variable_initial(void)
{
	lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_NONE);

#if HDMI_DISPLAY_DELAY_ENABLE
	lib_hdmi_set_delay_display_enable(_DISABLE);
	lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_NONE);
#endif
}

u64 lib_hdmi_get_clk90k(void)
{
	u64 clk90k_value;

	/* 90KHz timer, Read LO first to ensure the correct */
	clk90k_value = hdmi_rx_reg_read32(MIS_SCPU_CLK90K_LO ,HDMI_RX_CLK90K);
	clk90k_value = (clk90k_value<<32) | hdmi_rx_reg_read32(MIS_SCPU_CLK90K_HI ,HDMI_RX_CLK90K);

	return clk90k_value;
}

void lib_hdmi_dbg_reg_dump(void)
{
	#define AUDIO_REG_DBG 1
	#define VIDEO_REG_DBG 1

	HDMI_PRINTF("===================Dump Reg Start===================\n");
#if AUDIO_REG_DBG
	HDMI_PRINTF("###################Audio Part Begin###################\n");
	HDMI_PRINTF("SR=%x AFCR=%x\n",
		hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC));

	HDMI_PRINTF("ASR0=%x ASR1=%x\n",
		hdmi_rx_reg_read32(HDMI_ASR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_ASR1, HDMI_RX_MAC));

	HDMI_PRINTF("APLLCR0=%x APLLCR1=%x APLLCR2=%x APLLCR3=%x\n",
		hdmi_rx_reg_read32(HDMI_APLLCR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_APLLCR1, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_APLLCR2, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_APLLCR3, HDMI_RX_MAC));

	HDMI_PRINTF("ACRCR= %x ACRSR0=%x ACRSR1=%x\n",
		hdmi_rx_reg_read32(HDMI_ACRCR, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_ACRSR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_ACRSR1, HDMI_RX_MAC));

	HDMI_PRINTF("CTS_UP_BOUND=%x  CTS_LOW_BOUND=%x\n",
		hdmi_rx_reg_read32(HDMI_AUDIO_CTS_UP_BOUND, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_AUDIO_CTS_LOW_BOUND, HDMI_RX_MAC));

	HDMI_PRINTF("N_UP_BOUND=%x  N_LOW_BOUND=%x\n",
		hdmi_rx_reg_read32(HDMI_AUDIO_N_UP_BOUND, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_AUDIO_N_LOW_BOUND, HDMI_RX_MAC));

	HDMI_PRINTF("INTCR=%x SR_CHG=%x AOCR=%x\n",
		hdmi_rx_reg_read32(HDMI_INTCR, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_AUDIO_SAMPLE_RATE_CHANGE_IRQ, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_AOCR, HDMI_RX_MAC));

	HDMI_PRINTF("###################Audio Part End###################\n");
#endif

#if VIDEO_REG_DBG
	HDMI_PRINTF("###################TMDS Channel Status Begin###################\n");
	HDMI_PRINTF("TMDS_CTRL=%x TMDS_OUTCTL=%x\n",
		hdmi_rx_reg_read32(HDMI_TMDS_CTRL, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_TMDS_OUTCTL, HDMI_RX_MAC));
	HDMI_PRINTF("###################TMDS Channel Status End###################\n");


	HDMI_PRINTF("###################Deep Color Status Begin###################\n");
	HDMI_PRINTF("DPC_SET2=%x DPC_SET3=%x\n",
		hdmi_rx_reg_read32(HDMI_TMDS_DPC_SET2, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_TMDS_DPC_SET3, HDMI_RX_MAC));
	HDMI_PRINTF("###################Deep Color Status End###################\n");


	HDMI_PRINTF("###################Data Enable Error Status Begin###################\n");
	HDMI_PRINTF("DET_STS=%x\n",
		hdmi_rx_reg_read32(HDMI_TMDS_DET_STS, HDMI_RX_MAC));
	HDMI_PRINTF("###################Data Enable Error Status End###################\n");

	HDMI_PRINTF("###################Video Data Error Detect Begin###################\n");
	HDMI_PRINTF("BIT_ERR_B=%x BIT_ERR_G=%x BIT_ERR_R=%x\n",
		hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_B, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_G, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_R, HDMI_RX_MAC));
	HDMI_PRINTF("TREC4_ERR_B=%x TREC4_ERR_G=%x TREC4_ERR_R=%x\n",
		hdmi_rx_reg_read32(HDMI_TERC4_ERR_STATUS_B, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_TERC4_ERR_STATUS_G, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_TERC4_ERR_STATUS_R, HDMI_RX_MAC));
	HDMI_PRINTF("BCH_ERR=%x\n", hdmi_rx_reg_read32(HDMI_BCHCR, HDMI_RX_MAC));
	HDMI_PRINTF("###################Video Data Error Detect End###################\n");


	HDMI_PRINTF("################### Video Control Register Begin###################\n");
	HDMI_PRINTF("VCR=%x\n", hdmi_rx_reg_read32(HDMI_VCR, HDMI_RX_MAC));
	HDMI_PRINTF("###################Video Control Register End###################\n");

	HDMI_PRINTF("###################Guard Band Error Status Begin###################\n");
	HDMI_PRINTF("BCSR=%x\n", hdmi_rx_reg_read32(HDMI_BCSR, HDMI_RX_MAC));
	HDMI_PRINTF("###################Guard Band Error Status End###################\n");


	HDMI_PRINTF("###################PRBS Status Begin###################\n");
	HDMI_PRINTF("PRBS_R=%x PRBS_G=%x PRBS_B=%x\n",
		hdmi_rx_reg_read32(HDMI_PRBS_R_CTRL, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_PRBS_G_CTRL, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_PRBS_B_CTRL, HDMI_RX_MAC));
	HDMI_PRINTF("###################PRBS Status End###################\n");


	HDMI_PRINTF("###################Asynchronous Fifo Status Begin###################\n");
	HDMI_PRINTF("FIFO_SR0=%x FIFO_SR1=%x\n",
		hdmi_rx_reg_read32(HDMI_PHY_FIFO_SR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_PHY_FIFO_SR1, HDMI_RX_MAC));

	HDMI_PRINTF("CHSR=%x\n", hdmi_rx_reg_read32(HDMI_CH_SR, HDMI_RX_MAC));
	HDMI_PRINTF("###################PHY Asynchronous Fifo Status End###################\n");


	HDMI_PRINTF("###################Asynchronous Fifo Status Begin###################\n");
	HDMI_PRINTF("FIFO_SR0=%x FIFO_SR1=%x\n",
		hdmi_rx_reg_read32(HDMI_PHY_FIFO_SR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_PHY_FIFO_SR1, HDMI_RX_MAC));

	HDMI_PRINTF("CHSR=%x\n", hdmi_rx_reg_read32(HDMI_CH_SR, HDMI_RX_MAC));
	HDMI_PRINTF("###################PHY Asynchronous Fifo Status End###################\n");

#if HDMI2p0
	HDMI_PRINTF("###################Scramble Status Begin###################\n");
	HDMI_PRINTF("SCR_CR=%x\n", hdmi_rx_reg_read32(HDMI_SCR_CR, HDMI_RX_MAC));
	HDMI_PRINTF("###################Scramble Status End###################\n");


	HDMI_PRINTF("###################CED Status Begin###################\n");
	HDMI_PRINTF("CER_SR0=%x CER_SR1=%x CER_SR2=%x\n",
		hdmi_rx_reg_read32(HDMI_CERSR0, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_CERSR1, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_CERSR2, HDMI_RX_MAC));

	HDMI_PRINTF("CER_SR3=%x CER_SR4=%x\n",
		hdmi_rx_reg_read32(HDMI_CERSR3, HDMI_RX_MAC),
		hdmi_rx_reg_read32(HDMI_CERSR4, HDMI_RX_MAC));
	HDMI_PRINTF("###################CED Statuss End###################\n");


	HDMI_PRINTF("###################YUV420 FIFO Status Begin###################\n");
	HDMI_PRINTF("YUV420_CR=%x\n",
		hdmi_rx_reg_read32(HDMI_YUV420_CR, HDMI_RX_MAC));
	HDMI_PRINTF("###################YUV420 FIFO Status End###################\n");


	HDMI_PRINTF("###################PMM CLK Status Begin###################\n");
	HDMI_PRINTF("CLK_DET_SR=%x\n",
		hdmi_rx_reg_read32(HDMI_ACDRCLKDETSR, HDMI_RX_MAC));
	HDMI_PRINTF("###################PMM CLK Status End###################\n");
#endif

#endif

	HDMI_PRINTF("===================Dump Reg End===================\n");

}

