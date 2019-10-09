/*
 * hdmiInternal.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __HDMI_INTERNAL_H_
#define __HDMI_INTERNAL_H_

#include <linux/delay.h>

#include "v4l2_hdmi_dev.h"
#include "hdmirx_reg.h"
#include "hdcp2p2_dev.h"

#define HDMI_INTERNAL_DEBUG 0

#if HDMI_INTERNAL_DEBUG
#define HDMI_PRINTF(format, ...)	pr_err("[HDMI RX DBG]" format "\n", ## __VA_ARGS__)
#else
#define HDMI_PRINTF(format, ...)	do {} while(0)
#endif

#ifndef UINT8
	typedef unsigned char UINT8;
	typedef int INT32;
	typedef unsigned int UINT32;
#endif

#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

#ifndef _ENABLE
#define _ENABLE	1
#endif

#ifndef _DISABLE
#define _DISABLE	0
#endif

#ifndef ABS
#define ABS(x, y)				((x > y) ? (x-y) : (y-x))
#endif

#ifndef MAX
	#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
	#define MIN(a, b)           (((a) < (b)) ? (a) : (b))
#endif

typedef  unsigned char HDMI_bool;

#define HDMI2p0	 1 /* HDMI2.0 */
#define HDMI_REPEATER_SUPPORT  1
#define AUDIO_HBR_DETECT       1
#define AUDIO_OVER_192K        1
#define BIST_DFE_SCAN          0
#define MEASURE_FROM_TMDS_CLOCK 0 /*  0: PIXEL CLOCK  1:TMDS CLOCK */
#define TMDS_ERR_DET_SHORT_PERIOD  1
#define HDMI_INT_PRO_CHG_FLAG_ENABLE  1

/* Video WatchDog function enable */
#define HDMI_VIDEO_WD_ENABLE   1
#define HDMI_WD_VIDEO_COND     _BIT0
#define HDMI_WD_AUDIO_COND     _BIT1
#define HDMI_WD_VSC_COND       _BIT2
#define HDMI_WD_ALL_COND       (HDMI_WD_VIDEO_COND | HDMI_WD_AUDIO_COND | HDMI_WD_VSC_COND)

/* For fix colorimetry NG case */
#define HDMI_AVI_INFO_COLORIMETRY_ENABLE        1
#define HDMI_AVI_INFO_COLORIMETRY_DEBOUNCE_CNT  25

/* STB DC off/on, will send AV mute after display, let it flicker */
#define HDMI_TOGGLE_HPD_Z0_ENABLE    1
#define HDMI_START_TOGGLE_HPD_Z0_MS  5000
#define HDMI_TOGGLE_HPD_Z0_MS        400/* some times NG at 100 ~ 200, 500 ms is good */
#define HDMI_DC_ON_DELAY_MS          5000

/* STR TV and STB DC off/on together, It will keep to send AVMute, can not display */
#define HDMI_STR_TOGGLE_HPD_ENABLE   1
#define HDMI_STR_TOGGLE_HPD_MS       400

/* For Tx output stable clock => unstbale => stable*/
#define HDMI_DISPLAY_DELAY_ENABLE         1
#define HDMI_DISPLAY_DELAY_LHB_755_MS     600
#define HDMI_DISPLAY_DELAY_LHB_755_MS_2   200
#define HDMI_DISPLAY_DELAY_ROKU_ULTRA_4640R_MS     1500/* >1500ms OK */
#define HDMI_DISPLAY_DELAY_SAMSUNG_GX_HC630CH_MS   2000/* >1500ms OK */
#define HDMI_DISPLAY_DELAY_KT_STB_KAO_CT1100_MS    500/* >500ms OK */

/* Fix Tx send stable clock at first, and check HDCP later */
#define HDMI_CHECK_HDCP_ENABLE            0
#define HDMI_HDCP_DEBOUNCE_CNT            25

#define VALID_MIN_CLOCK         116
#define MEAS_RETRY_LIMIT        6

#define DISP_DEB_CNT_APPLETV   2
#define DISP_DEB_CNT_PC40000   2


/* lib_hdmi_z0_set */
#define LN_Z300POW	0x10
#define LN_CK	0x08
#define LN_B	0x04
#define LN_G	0x02
#define LN_R	0x01
#define LN_ALL (LN_Z300POW|LN_CK|LN_B|LN_G|LN_R)

/* lib_hdmi_valid_format_condition */
#define HDMI_PK_GB_NUM   1
#define HDMI_VD_GB_NUM   1
#define HDMI_PK_PRE_NUM  3
#define HDMI_VD_PRE_NUM  3

#define HDMI_ABS(x, y)		((x > y) ? (x-y) : (y-x))

#define HDMI_DELAYUS(x)    usleep_range(x, x+10)
#define HDMI_DELAYMS(x)    msleep(x)

#define HDMI_CONST		const

typedef enum {
	HDMI_ERR_NO = 0,
	HDMI_EER_GENERIC,
	HDMI_ERR_ONMS_ONESHOT,
	HDMI_ERR_ONMS_CONTINUOUS_INIT,
	HDMI_ERR_ONMS_CONTINUOUS_CHECK,
	HDMI_ERR_ONMS_WRONG_TIMING,
	HDMI_ERR_ONMS_WRONG_PARAM,
	HDMI_ERR_3D_WRONG_OPMODE,
	HDMI_ERR_3D_NO_MEM,
	HDMI_ERR_4XXTO4XX_WRONG_PARAM,
	HDMI_EER_MEASURE_ACTIVESPACE_FAIL,
	HDMI_EER_VODMA_NOT_READY,
} HDMI_ERR_T;

enum _MODE_RESULT {
	_MODE_NOSIGNAL	= 0xFF,
	_MODE_NOSUPPORT = 0xFE,
	_MODE_NOCABLE	= 0xFD,
	_MODE_SUCCESS	= 0xFC,
	_MODE_DETECT	= 0xFB,
	_MDOE_UNDKOWN	= 0xFA,
};
#define MEASURE_FAIL  _MODE_DETECT

typedef enum {
	MODE_DVI = 0x0,
	MODE_HDMI,
	MODE_UNKNOW
} HDMI_DVI_MODE_T;

typedef enum {
	HDMI_MS_MODE_ONESHOT = 0,
	HDMI_MS_MODE_CONTINUOUS_INIT,
	HDMI_MS_MODE_CONTINUOUS_CHECK,
	HDMI_MS_MODE_ONESHOT_INIT,
	HDMI_MS_MODE_ONESHOT_GET_RESULT,
	HDMI_MS_MODE_ONESHOT_POLARITY_FIXED,
} HDMI_MS_MODE_T;

typedef enum {
	AUDIO_FSM_AUDIO_START = 0,
	AUDIO_FSM_FREQ_DETECT,
	AUDIO_FSM_AUDIO_WAIT_TO_START,
	AUDIO_FSM_AUDIO_START_OUT,
	AUDIO_FSM_AUDIO_WAIT_PLL_READY,
	AUDIO_FSM_AUDIO_CHECK
} HDMI_AUDIO_FSM_T;

typedef enum {
	AUDIO_FORMAT_LPCM = 0,
	AUDIO_FORMAT_NONLPCM
} HDMI_AUDIO_FORMAT_T;

typedef enum {
	HDMI_MS_ONESHOT = 0,
	HDMI_MS_CONTINUOUS,
	HDMI_MS_DIRECT
} HDMI_MS_T;

typedef enum {
	HDMI_AUDIO_N_CTS_TREND_BOUND = 0,
	HDMI_AUDIO_TREND_BOUND,
	HDMI_AUDIO_N_CTS,
} HDMI_AUDIO_TRACK_MODE;

typedef enum {
	HDMIRX_DETECT_FAIL = 0,
	HDMIRX_DETECT_SUCCESS,
	HDMIRX_DETECT_AVMUTE,
	HDMIRX_CHECK_MODE,
	HDMIRX_RELEASED,
} HDMIRX_APSTATUS_T;

typedef enum {
	IOCTRL_HDMI_PHY_START = 0,
	IOCTRL_HDMI_PHY_STOP,
	IOCTRL_HDMI_GET_STRUCT,
	IOCTRL_HDMI_SET_TIMER,
	IOCTRL_HDMI_GET_TIMER,
	IOCTRL_HDMI_AUDIO_PLL_SAMPLE_START,
	IOCTRL_HDMI_AUDIO_PLL_SAMPLE_STOP,
	IOCTRL_HDMI_AUDIO_PLL_SAMPLE_DUMP,
	IOCTRL_HDMI_SET_APSTATUS
}  HDMIRX_IOCTL_T;

typedef enum {
	MODE_RAG_DEFAULT	= 0x0,
	MODE_RAG_LIMIT,
	MODE_RAG_FULL,
	MODE_RAG_UNKNOW
} HDMI_RGB_YUV_RANGE_MODE_T;

typedef enum {
	HDMI_COLORIMETRY_NOSPECIFIED = 0,
	HDMI_COLORIMETRY_601,
	HDMI_COLORIMETRY_709,
	HDMI_COLORIMETRY_XYYCC601,
	HDMI_COLORIMETRY_XYYCC709,
	HDMI_COLORIMETRY_SYCC601,
	HDMI_COLORIMETRY_ADOBE_YCC601,
	HDMI_COLORIMETRY_ADOBE_RGB,
} HDMI_COLORIMETRY_T;

typedef enum {
	COLOR_RGB = 0x00,
	COLOR_YUV422,
	COLOR_YUV444,
	COLOR_YUV420,
	COLOR_UNKNOW
} HDMI_COLOR_SPACE_T;

typedef enum {
	HDMI_COLOR_DEPTH_8B = 0,
	HDMI_COLOR_DEPTH_10B,
	HDMI_COLOR_DEPTH_12B,
	HDMI_COLOR_DEPTH_16B,
} HDMI_COLOR_DEPTH_T;

typedef enum {
	HDMI_3D_OPMODE_DISABLE = 0,
	HDMI_3D_OPMODE_HW,
	HDMI_3D_OPMODE_HW_2DONLY_L,
	HDMI_3D_OPMODE_HW_2DONLY_R,
	HDMI_3D_OPMODE_SW,
	HDMI_3D_OPMODE_HW_NODMA
} HDMI_3D_OPMODE_T;

typedef enum {
	HDMI_PTG_MODE_BACKGROUD_ONLY,
	HDMI_PTG_MODE_H_COLOR_BAR,
	HDMI_PTG_MODE_V_COLOR_BAR,
	HDMI_PTG_MODE_H_GREDIENT,
	HDMI_PTG_MODE_V_GREDIENT,
	HDMI_PTG_MODE_HV_GREDIENT,
	HDMI_PTG_MODE_BITMAP,
	HDMI_PTG_CROSS_COLOR_SEQ0,
	HDMI_PTG_CROSS_COLOR_SEQ1,
	HDMI_PTG_CROSS_COLOR_SEQ2,
	HDMI_PTG_CROSS_COLOR_SEQ3,
} HDMI_PTG_MODE_T;

typedef enum {
	HDMI_PATH_POLICY_2D_ONLY = 0,
	HDMI_PATH_POLICY_3D_NODMA,
	HDMI_PATH_POLICY_3D_DMA
} HDMI_PATH_POLICY_T;

typedef enum {
	HVF_NO,
	HVF_EXT,
	HVF_3D,
	HVF_RESERVED
} HDMI_HVF_E;

typedef enum {
	HDMI3D_FRAME_PACKING = 0,
	HDMI3D_FIELD_ALTERNATIVE = 1,
	HDMI3D_LINE_ALTERNATIVE = 2,
	HDMI3D_SIDE_BY_SIDE_FULL = 3,
	HDMI3D_L_DEPTH = 4,
	HDMI3D_L_DEPTH_GPX = 5,
	HDMI3D_TOP_AND_BOTTOM = 6,
	HDMI3D_FRAMESEQUENCE = 7,
	HDMI3D_SIDE_BY_SIDE_HALF = 8,
	/* --- new 3D format --- */
	HDMI3D_LINE_BY_LINE = 9,
	HDMI3D_VERTICAL_STRIPE = 10,
	HDMI3D_CHECKER_BOARD = 11,
	HDMI3D_REALID = 12,
	HDMI3D_SENSIO = 13,
	/* ------------------- */
	HDMI3D_RSV1,
	HDMI3D_2D_ONLY,
	HDMI3D_UNKOWN = 0xFFFFFFFF
} HDMI_3D_T;

typedef enum {
	HDCPRX_STATE_NONE = 0,
	HDCPRX_STATE_1PX_DISCOVER = 1,
	HDCPRX_STATE_1PX_ON = 2,
	HDCPRX_STATE_2P2_DISCOVER = 3,
	HDCPRX_STATE_2P2_ON = 4
} HDCPRX_STATE;

typedef enum _HDMI_DC_ON_STATE_ {
	HDMI_DC_ON_NONE = 0,
	HDMI_DC_ON_ENABLE_DELAY,
	HDMI_DC_ON_START_TIME,
	HDMI_DC_ON_FINISH,
	HDMI_DC_ON_UNKNOW
} HDMI_DC_ON_STATE_E;

typedef enum _HDMI_STR_HPD_TOGGLE_STATE_ {
	HDMI_STR_HPD_TOGGLE_NONE = 0,
	HDMI_STR_HPD_TOGGLE_ENTER,
	HDMI_STR_HPD_TOGGLE_READY,
	HDMI_STR_HPD_TOGGLE_UNKNOW,
} HDMI_STR_HPD_TOGGLE_STATE_E;

typedef enum _HDMI_DISPLAY_DELAY_STATE_ {
	HDMI_DISPLAY_DELAY_NONE = 0,
	HDMI_DISPLAY_DELAY_INIT,
	HDMI_DISPLAY_DELAY_START,
	HDMI_DISPLAY_DELAY_FINISH,
} HDMI_DISPLAY_DELAY_STATE_STATE_E;

typedef enum _HDMI_SPECIFIC_DEVICE_ {
	HDMI_SPECIFIC_DEVICE_NONE = 0,
	HDMI_SPECIFIC_DEVICE_SK_STB,
	HDMI_SPECIFIC_DEVICE_KT_STB_IC1000,
	HDMI_SPECIFIC_DEVICE_KT_STB_IC1100,
	HDMI_SPECIFIC_DEVICE_KT_STB_KT600EJ,
	HDMI_SPECIFIC_DEVICE_LHB_755,
	HDMI_SPECIFIC_DEVICE_ROKU_ULTRA_4640R,
	HDMI_SPECIFIC_DEVICE_SAMSUNG_GX_HC630CH,
	HDMI_SPECIFIC_DEVICE_KT_STB_KAO_CT1100,
} HDMI_SPECIFIC_DEVICE_E;

typedef enum {
	MAIN_FSM_HDMI_WAIT_SYNC,
	MAIN_FSM_HDMI_SETUP_VEDIO_PLL,
	MAIN_FSM_HDMI_MEASURE,
	MAIN_FSM_HDMI_MEASURE_ACTIVE_SPACE,
	MAIN_FSM_HDMI_WAIT_READY,
	MAIN_FSM_HDMI_DISPLAY_ON,
	MAIN_FSM_HDMI_VIDEO_READY
} HDMI_MAIN_FSM_T;

typedef struct {
	unsigned char spd_vn_name[8];
	unsigned char psd_pd_desc[16];
} HDMI_POOR_DEV_T;

typedef struct	{
	char name[25];
	int progressive;
	unsigned int h_act_len;
	unsigned int v_act_len;
	unsigned int lr_v_act_len;
	unsigned int v_active_space1;
	unsigned int v_active_space2;
} HDMI_ACTIVE_SPACE_TABLE_T;

typedef struct {
	unsigned char VSIF_TypeCode;
	unsigned char VSIF_Version;
	unsigned char Length;
	unsigned char Checksum;
	unsigned char Reg_ID[3];
	unsigned char Payload[25];
} HDMI_VSI_T;

typedef struct {
	unsigned char type_code;
	unsigned char ver;
	unsigned char len;
	unsigned int  S:2;
	unsigned int  B:2;
	unsigned int  A:1;
	unsigned int  Y:3;
	unsigned int  R:4;
	unsigned int  M:2;
	unsigned int  C:2;
	unsigned int  SC:2;
	unsigned int  Q:2;
	unsigned int  EC:3;
	unsigned int  ITC:1;
	unsigned int  VIC:8;
	unsigned int  PR:4;
	unsigned int  CN:2;
	unsigned int  YQ:2;
	unsigned char ETB07_00;
	unsigned char ETB15_08;
	unsigned char SBB07_00;
	unsigned char SBB15_08;
	unsigned char ELB07_00;
	unsigned char ELB15_08;
	unsigned char SRB07_00;
	unsigned char SRB15_08;
} HDMI_AVI_T;

typedef struct {
	unsigned char type_code;
	unsigned char ver;
	unsigned char len;
	unsigned char VendorName[8];
	unsigned char ProductDesc[16];
	unsigned char SourceInfo;
} HDMI_SPD_T;

typedef struct {
	unsigned char type_code;
	unsigned char ver;
	unsigned char len;
	unsigned int  CC:3;
	unsigned int  F13:1;
	unsigned int  CT:4;
	unsigned int  SS:2;
	unsigned int  SF:3;
	unsigned int  F27_25:3;
	unsigned int  CXT:5;
	unsigned int  F37_35:3;
	unsigned int  CA:8;
	unsigned int  LFEPBL:2;
	unsigned int  F52:1;
	unsigned int  LSV:4;
	unsigned int  DM_INH:1;
	unsigned char F67_60;
	unsigned char F77_70;
	unsigned char F87_80;
	unsigned char F97_90;
	unsigned char F107_100;
} HDMI_AUDIO_T;

typedef struct {
	unsigned char type_code;
	unsigned char ver;
	unsigned char len;
	unsigned char  eEOTFtype;
	unsigned char  eMeta_Desc;
	unsigned short display_primaries_x0;
	unsigned short display_primaries_y0;
	unsigned short display_primaries_x1;
	unsigned short display_primaries_y1;
	unsigned short display_primaries_x2;
	unsigned short display_primaries_y2;
	unsigned short white_point_x;
	unsigned short white_point_y;
	unsigned short max_display_mastering_luminance;
	unsigned short min_display_mastering_luminance;
	unsigned short maximum_content_light_level;
	unsigned short maximum_frame_average_light_level;
	unsigned char  reserved;
} __attribute__((packed)) HDMI_DRM_T;

typedef struct {
	unsigned char SM;
	unsigned char SN;
	unsigned char RatioM;
	unsigned char RatioN;
} VIDEO_DPLL_RATIO_T;

typedef struct {
	unsigned char dpll_M;
	unsigned char dpll_N;
	unsigned char dpll_IP;
	unsigned char dpll_RS;
} VIDEO_DPLL_FIX_T;

typedef struct {
	unsigned char min_M;
	unsigned char max_M;
	unsigned char dpll_IP;
	unsigned char dpll_RS;
} VIDEO_DPLL_RANGE_T;

typedef struct {
	int freq;
	unsigned char coeff;
	unsigned char rate;
} HDMI_AUDIO_PLL_COEFF_T;

typedef struct {
	unsigned int  freq;
	unsigned char N;
	unsigned char M;
	unsigned char O;
	unsigned char S;
	unsigned char S1;
	unsigned int D_HighByte;
	unsigned int D_LowByte;
	const char *sample_rate;
} HDMI_AUDIO_PLL_PARAM_T;


/**
 * HDMI_AUDIO_FREQ_T
 * @ACR_freq: Audio Frequency from ACR
 * @AudioInfo_freq: Audio Frequency from Audio Info Frame
 * @SPDIF_freq: Audio Frequency from SPDIF Channel Status Info
 */
typedef struct {
	unsigned long ACR_freq;
	unsigned long AudioInfo_freq;
	unsigned long SPDIF_freq;
	unsigned int ACR_N;
} HDMI_AUDIO_FREQ_T;

typedef struct {
	u_int16_t b_upper;
	u_int16_t b_lower;
	u_int16_t M_code;
	u_int16_t N_code;

	u_int8_t PI_DIV;
	u_int8_t DEMUX;
	u_int8_t RATE_SEL;
	u_int8_t CK_LDOD;
	u_int8_t CK_CS;

	u_int8_t CK_RS;
	u_int8_t EQ_adj;
	u_int8_t CDR_bias;
	u_int8_t CDR_KP;
	u_int8_t CDR_KP2;

	u_int8_t CDR_KI;
	u_int8_t CDR_KD;
	u_int8_t EQ_gain;
	u_int8_t EQ_bias;
	u_int8_t CK_Icp;

	u_int8_t PR;
	u_int8_t pscaler;
	u_int8_t vsel_ldo;
	u_int8_t CMU_SEL_D4;
	u_int8_t Icp_DUL;

	u_int8_t PI_CSEL;
	u_int8_t PI_CURRENT;
	u_int8_t PI_ISEL;
	u_int8_t EN_CAP;
	u_int8_t CMU_KVCO;
	const char band_name[30];
} HDMI_PHY_PARAM_T;

typedef struct {
	u_int16_t fvco_upper;
	u_int16_t fvco_lower;
	u_int8_t CMU_KVCO;
	u_int8_t EN_CAP;
	u_int8_t CCO_BAND_SEL;
	u_int8_t PI_ISEL;
	u_int8_t PI_CSEL;
} HDMI_PHY_PARAM2_T;

typedef struct {
	unsigned char DEF_ready;
	unsigned char measure_ready;
	unsigned char detect_done;
	unsigned char audio_detect_done;
	unsigned char hdcp_state;/* enum HDCPRX_STATE */
} HDMIRX_STATE_STRUCT_T;

typedef struct {
	HDMIRX_APSTATUS_T apstatus;
	unsigned int idle_count;
} HDMIRX_PHY_IDLE_PATCH_T;

typedef struct {
	unsigned char BKsv[5];
	unsigned char Key[320];
} HDCP_KEY_T;

typedef struct {
	unsigned int v_total;
	unsigned int h_total;
	unsigned int v_act_len;
	unsigned int h_act_len;
	unsigned int v_act_sta;
	unsigned int h_act_sta;
	unsigned int v_freq;
	unsigned int h_freq;
	unsigned int polarity;
	unsigned int mode_id;
	unsigned int modetable_index;
	unsigned char is_interlace;

	HDMI_DVI_MODE_T 	mode;
	HDMI_COLOR_DEPTH_T colordepth;
	HDMI_COLOR_SPACE_T colorspace;
	HDMI_COLORIMETRY_T  colorimetry;
	unsigned char pixel_repeat;

	HDMI_HVF_E hvf;
	HDMI_3D_T h3dformat;

	unsigned int tmds_clk_b;

	unsigned char tmds_clk_stable_cnt;

	/* Only for fram packing */
	unsigned int v_active_space1;
	unsigned int v_active_space2;
} HDMI_TIMING_T;


typedef struct {
	unsigned char coding_type;/* 0=pcm; 1=nonpcm */
	unsigned int audio_freq;
	unsigned char sr_mismatch_cnt;
	unsigned char track_mode_tgl;
} HDMI_AUDIO_STATE;

typedef struct {
	HDMI_PHY_PARAM_T phy_param_t;

	HDMI_TIMING_T timing_t;
	HDMI_AUDIO_STATE audio_t;

	HDMI_AVI_T avi_t;
	HDMI_VSI_T vsi_t;
	HDMI_SPD_T spd_t;
	HDMI_AUDIO_T audiopkt_t;
	HDMI_DRM_T drm_t;
	unsigned char no_avi_cnt;
	unsigned char no_vsi_cnt;
	unsigned char no_spd_cnt;
	unsigned char no_audiopkt_cnt;
	unsigned char no_drm_cnt;

	HDMI_MAIN_FSM_T video_fsm;
	HDMI_AUDIO_FSM_T audio_fsm;

#if HDMI2p0
	unsigned char scramble_flag;
	unsigned char clock40x_flag;
	unsigned char hdmi2p0_tmds_toggle_flag;
#endif

	unsigned char vs_cnt;

	unsigned char meas_retry_cnt;

#ifdef CONFIG_RTK_HDCP1x_REPEATER
	unsigned char tx_hdcp_state;
#endif

	/* HPD */
	int rx_5v_state;
	int gpio_hpd_ctrl;
	int gpio_5v_det;

} HDMI_PORT_INFO_T;

#ifdef CONFIG_RTK_HDCP1x_REPEATER
#define HDCP_Aksv_SIZE 5
#define KSVLIST_SIZE   640
struct hdcp_ksvlist_info {
	uint8_t Aksv[HDCP_Aksv_SIZE];
	uint8_t ksvlist[KSVLIST_SIZE];
	uint8_t bstatus[2];
	uint32_t device_count;
	uint8_t Bksv[HDCP_Aksv_SIZE];
};
#endif

struct hdcp2p2_wait_event {
	spinlock_t slock;
	wait_queue_head_t read_wq;
	unsigned int condition;
};

/*
 * HDMI Driver Private MARCO
 */
#define SET_H_VIDEO_FSM(fsm)	(hdmi_rx.video_fsm = fsm)
#define SET_H_AUDIO_FSM(fsm)	(hdmi_rx.audio_fsm = fsm)
	
#define SET_H_INTERLACE(interlace)	(hdmi_rx.timing_t.is_interlace = interlace)
#define SET_H_MODE(m)		(hdmi_rx.timing_t.mode = m)
#define SET_H_COLOR_DEPTH(color)	(hdmi_rx.timing_t.colordepth= color)
#define SET_H_COLOR_SPACE(color)	(hdmi_rx.timing_t.colorspace = color)
#define SET_H_PIXEL_REPEAT(pr)	(hdmi_rx.timing_t.pixel_repeat = pr)
#define SET_H_VIDEO_FORMAT(fmt)	(hdmi_rx.timing_t.hvf = fmt)
#define SET_H_3DFORMAT(fmt) 	(hdmi_rx.timing_t.h3dformat = fmt)
	
#define SET_AUDIO_TYPE(type)	(hdmi_rx.audio_type = type)
	
#define GET_H_VIDEO_FSM()		(hdmi_rx.video_fsm)
#define GET_H_AUDIO_FSM()		(hdmi_rx.audio_fsm)
	
#define GET_H_INTERLACE()		(hdmi_rx.timing_t.is_interlace)
#define GET_H_MODE()		(hdmi_rx.timing_t.mode)
#define GET_H_COLOR_DEPTH()	(hdmi_rx.timing_t.colordepth)
#define GET_H_COLOR_SPACE()	(hdmi_rx.timing_t.colorspace)
#define GET_H_PIXEL_REPEAT()	(hdmi_rx.timing_t.pixel_repeat)
#define GET_H_VIDEO_FORMAT() 	(hdmi_rx.timing_t.hvf)
#define GET_H_3DFORMAT() 		(hdmi_rx.timing_t.h3dformat)
	
#define GET_AUDIO_TYPE()		(hdmi_rx.audio_type)

extern HDMI_PORT_INFO_T	hdmi_rx;
extern HDMIRX_STATE_STRUCT_T hdmirx_state;

/* hdmiPhy*/
extern void lib_hdmi_phy_init(void);
extern int rxphy_isr(void);
extern void rxphy_init_struct(void);
extern void rxphy_isr_set(unsigned char en);
extern unsigned char rxphy_is_clk_stable(void);
extern unsigned int rxphy_get_clk(void);
extern unsigned char rxphy_get_setphy_done(void);
extern void hdmi_open_err_detect(void);
extern unsigned char lib_hdmi_is_clk_ready(void);
extern unsigned int lib_hdmi_get_clock(void);
extern void lib_hdmi_trigger_measure_start(void);
extern void rxphy_reset_setphy_proc(void);
extern unsigned char hdmi_char_err_detection(void);
extern unsigned char hdmi_is_long_cable(void);
extern void hdmi_dfe_recovery_6g_long_cable(void);
extern void lib_hdmi_trigger_measure_stop(void);
extern void hdmi_set_phy(unsigned int b);
extern unsigned char hdmi_dfe_record(unsigned int clk);
extern unsigned char hdmi_dfe_close(unsigned int clk, unsigned char phy_state);
extern void hdmi_dfe_hi_speed(unsigned int b_clk);
extern void hdmi_dfe_mi_speed(unsigned int b_clk);
extern void lib_hdmi_mac_release(void);
extern void hdmi_dfe_6g_long_cable_patch(void);
extern void hdmi_dump_dfe_para(void);
extern void lib_hdmi_ck_md_ref_sel(void);
extern void lib_hdmi_z0_set(unsigned char lane, unsigned char enable);


/* hdmiHdmi */
extern void Hdmi_SetHPD(char high);
extern void hdmi_init(void);
extern unsigned char hdmi_detect_mode(void);
extern void hdmi_release_source(void);
extern void hdmi_port_var_init(void);
extern void hdmi_audio_close(void);
extern void hdmi_disconnect_source(void);
extern void lib_hdmi_video_output(unsigned char on);
extern unsigned char hdmi_watchdog_apply(unsigned char Enable, unsigned char Condition);
extern void hdmi_audio_var_init(void);
extern unsigned char hdmi_check_condition_change(void);
extern unsigned char hdmi_wait_sync(void);
extern unsigned char hdmi_setup_video_pll(void);
extern unsigned char hdmi_measure(void);
extern unsigned char hdmi_display_on(void);
extern unsigned char hdmi_video_ready(void);
extern unsigned char hdmi_get_colorspace_reg(void);
extern unsigned char hdmi_get_colordepth(void);
extern unsigned char hdmi_get_colorimetry(void);
extern unsigned char hdmi_get_hdmi_mode_reg(void);
extern void hdmi_reset_all_infoframe(void);
extern unsigned char lib_hdmi_get_vic(void);
extern void hdmi_reset_video_state(void);
extern void hdmi_check_connection_state(void);
extern void hdmi2p0_check_tmds_config(void);
extern unsigned char hdmi2p0_get_clock40x_flag(void);
extern void hdmi2p0_reset_scdc_toggle(void);
extern void hdmi2p0_inc_scdc_toggle(void);
extern void hdmi_check_crc_0(void);
extern unsigned char hdmi_get_video_format_reg(void);
extern unsigned char hdmi_get_3d_structure_reg(void);
extern unsigned char hdmi_bit_err_detection(void);
extern void hdmi_reset_meas_counter(void);
extern void hdmi2p0_detect_config(void);
extern unsigned char hdmi_audio_wait_acr(void);


/* hmi_lib*/
extern void lib_hdmi_power(unsigned char enable);
extern void lib_hdmi_tmds_init(void);
extern void lib_hdmi_mac_init(void);
extern void lib_hdmi_gcp_ackg_header_parsing_mode(void);
extern void lib_hdmi_valid_format_condition(void);
extern void lib_hdmi_misc_variable_initial(void);
extern unsigned char lib_hdmi_get_avmute(void);
extern unsigned char lib_hdmi_get_bch_2bit_error(void);
extern void lib_hdmi_char_err_rst(unsigned char rst);
extern unsigned char lib_hdmi_toggle_hpd_z0_check(unsigned char ucInit);
extern void lib_hdmi_clear_interlace_reg(void);
extern void lib_hdmi_set_repeat_auto(void);
extern void lib_hdmi_set_colorspace_auto(void);
extern void lib_hdmi_bch_error_clr(void);
extern void lib_hdmi_audio_set_hbr_manual_mode(unsigned char manu, unsigned char mode_fw);
extern void lib_hdmi_audio_clear_hdr_status(void);
extern void lib_hdmi2p0_scdc_update_flag(void);
extern unsigned char lib_hdmi_get_color_depth(void);
extern unsigned char lib_hdmi_get_pixelrepeat(void);
extern void lib_hdmi_set_colorspace_manual(unsigned char color_space);
extern unsigned char lib_hdmi_get_is_interlace(HDMI_MS_T ms_mode);
extern unsigned char lib_hdmi_set_video_pll(unsigned int b_clk, unsigned char cd, unsigned char is_interlace, unsigned char is_420);
extern void lib_hdmi_meas_select_port(void);
extern void lib_hdmi_crc_check(void);
extern void lib_hdmi_set_str_toggle_hpd_state(HDMI_STR_HPD_TOGGLE_STATE_E state);
extern HDMI_STR_HPD_TOGGLE_STATE_E lib_hdmi_get_str_toggle_hpd_state(void);
extern unsigned char lib_hdmi_is_wdm_enable(void);
extern void lib_hdmi_audio_output(unsigned char on);
extern unsigned char lib_hdmi_get_is_interlace_change(void);
extern unsigned int lib_hdmi_read_crc(void);
extern void lib_hdmi_420_en(unsigned char en);
extern unsigned char lib_hdmi2p0_get_tmds_config(void);
extern void lib_hdmi2p0_scramble_enable(unsigned char on_off);
extern unsigned char lib_hdmi_vsync_checked(void);
extern unsigned char lib_hdmi_is_hdmi_mode(void);
extern unsigned char lib_hdmi_get_colorspace(void);
extern unsigned char lib_hdmi_get_video_format(void);
extern unsigned char lib_hdmi_get_3d_structure(void);
extern unsigned char lib_hdmi_audio_get_channel_status15_0(unsigned int bitmask, unsigned int bitshift);
extern void lib_hdmi_tmds_out_ctrl(unsigned char bypass, unsigned int r, unsigned int g, unsigned int b);
extern void lib_hdmi_audio_clear_phase_error(void);
extern unsigned char lib_hdmi_audio_is_pll_unlock(void);
extern unsigned char lib_hdmi_audio_is_fifo_overflow(void);
extern unsigned char lib_hdmi_audio_is_fifo_underflow(void);
extern void lib_hdmi_audio_wclr_pll_unlock(void);
extern void lib_hdmi_audio_wclr_fifo_overflow(void);
extern void lib_hdmi_audio_wclr_fifo_underflow(void);
extern void lib_hdmi_audio_cts_bound(unsigned int clk);
extern void lib_hdmi_audio_n_bound(unsigned int freq);
extern void lib_hdmi2p0_reset_scdc(void);
extern void lib_hdmi_mac_afifo_enable(void);
extern void lib_hdmi_set_repeat_manual(unsigned char rep_value);
extern void lib_hdmi_audio_pop_n_cts(void);
extern void lib_hdmi_audio_clear_fs(void);
extern unsigned char lib_hdmi_audio_pop_n_cts_done(void);
extern unsigned char lib_hdmi_audio_fs_from_cs(void);
extern unsigned char lib_hdmi_audio_get_freq_from_cs(void);
extern unsigned int lib_hdmi_audio_get_n(void);
extern unsigned int lib_hdmi_audio_get_cts(void);
extern unsigned char lib_hdmi_audio_get_hbr_manual_mode(void);
extern void lib_hdmi_audio_init(void);
extern unsigned char hdmi_audio_wait_2_samples(void);
extern void lib_hdmi_audio_generate(void);
extern unsigned char lib_hdmi_audio_is_nonpcm(void);
extern unsigned char lib_hdmi_audio_is_output(void);
extern void lib_hdmi_set_rsv_packet_type(unsigned char index, unsigned char pkt_type);
extern void lib_hdmi_clear_rsv_packet0_status(void);
extern void lib_hdmi_clear_rsv_packet1_status(void);
extern unsigned char lib_hdmi_audio_get_hbr_mode(void);
extern void lib_hdmi_clear_avmute(void);
extern void lib_hdmi_set_toggle_hpd_z0_flag(unsigned char uc_flag);
extern void lib_hdmi_clear_fvs_received_status(void);
extern void lib_hdmi_clear_vs_received_status(void);
extern void lib_hdmi_clear_avi_received_status(void);
extern void lib_hdmi_clear_spd_received_status(void);
extern void lib_hdmi_clear_audiopkt_received_status(void);
extern void lib_hdmi_clear_drm_received_status(void);
extern unsigned char lib_hdmi_is_fvs_received(void);
extern unsigned char lib_hdmi_is_vs_received(void);
extern unsigned char lib_hdmi_is_avi_received(void);
extern unsigned char lib_hdmi_is_spd_received(void);
extern unsigned char lib_hdmi_is_audiopkt_received(void);
extern unsigned char lib_hdmi_is_drm_received(void);
extern unsigned char lib_hdmi_is_rsv_packet0_received(void);
extern unsigned char lib_hdmi_is_rsv_packet1_received(void);
extern unsigned char lib_hdmi_is_rsv_packet2_received(void);
extern unsigned char lib_hdmi_is_rsv_packet3_received(void);
extern void lib_hdmi_set_specific_device(HDMI_SPECIFIC_DEVICE_E device);
extern unsigned char lib_hdmi_dc_on_delay_check(unsigned char ucInit);
extern void lib_hdmi_set_delay_display_enable(unsigned char ucEnable);
extern HDMI_DISPLAY_DELAY_STATE_STATE_E lib_hdmi_get_delay_display_state(void);
extern void lib_hdmi_set_delay_display_state(HDMI_DISPLAY_DELAY_STATE_STATE_E state);
extern unsigned char lib_hdmi_delay_check_before_display(unsigned char ucInit);
extern unsigned char lib_hdmi_hdcp14_is_onoff(void);
extern void lib_hdmi_wdm_enable(unsigned char enable);
extern void lib_hdmi_auto_avmute_enable(unsigned char enable);
extern unsigned char lib_hdmi_scdc_read(unsigned char addr);
extern void lib_hdmi_scdc_write(unsigned char addr, unsigned char value);
extern void lib_hdmi_read_packet_sram(unsigned int start_addr, unsigned char len, unsigned char *pbuf);
extern void lib_hdmi_set_dc_on_delay_state(HDMI_DC_ON_STATE_E state);
extern unsigned int lib_hdmi_get_delay_display_time(void);
extern HDMI_SPECIFIC_DEVICE_E lib_hdmi_get_specific_device(void);
extern u64 lib_hdmi_get_clk90k(void);


/* hdmirx_hdcp */
extern unsigned char Is_HdmiRx_hdcp1x_enabled(void);

#endif /* __HDMI_INTERNAL_H_ */

