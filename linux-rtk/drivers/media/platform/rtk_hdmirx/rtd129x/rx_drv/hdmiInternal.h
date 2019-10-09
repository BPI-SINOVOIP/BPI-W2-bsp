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
#define HDMI_PRINTF(format, ...)	pr_info("[HDMI RX DBG]" format, ## __VA_ARGS__)
#else
#define HDMI_PRINTF(format, ...)	do {} while(0)
#endif

#ifndef UINT8
	typedef int INT32;
	typedef unsigned int UINT32;
	typedef unsigned short	UINT16;
	typedef char	UINT8;
#endif

#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

#ifndef ABS
#define ABS(x, y)				((x > y) ? (x-y) : (y-x))
#endif

#define _AUDIO_128_TIMES		1
#define _AUDIO_256_TIMES		2

#define HDMI_AUDIO_PCM	0
#define HDMI_AUDIO_NPCM	1

typedef  unsigned char HDMI_bool;

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

#define HDMI2p0	 1 /* HDMI2.0 */
#define HDMI_REPEATER_SUPPORT  1

#define HDMI_PHY_IDLE_PATCH_ENABLE	1
#define HDMI_PHY_IDLE_PATCH_COUNT 15

/* hdmi_z0_set */
#define LN_Z300POW	0x10
#define LN_CK	0x08
#define LN_B	0x04
#define LN_G	0x02
#define LN_R	0x01
#define LN_ALL (LN_Z300POW|LN_CK|LN_B|LN_G|LN_R)

#define HDMI_ABS(x, y)		((x > y) ? (x-y) : (y-x))

#define HDMI_DELAYUS(x)    do{ udelay(x); }while(0)
#define HDMI_DELAYMS(x)    do{ if(in_atomic()) mdelay(x); else msleep(x); }while(0)

#define HDMI_CONST		const

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

typedef enum _HDMI_CHANNEL_TYPE{
	HDMI_CHANNEL0 = 0,
} HDMI_CHANNEL_TYPE;

typedef enum {
	HDMI_MS_MODE_ONESHOT = 0,
	HDMI_MS_MODE_CONTINUOUS_INIT,
	HDMI_MS_MODE_CONTINUOUS_CHECK,
	HDMI_MS_MODE_ONESHOT_INIT,
	HDMI_MS_MODE_ONESHOT_GET_RESULT,
	HDMI_MS_MODE_ONESHOT_POLARITY_FIXED,
} HDMI_MS_MODE_T;

typedef enum {
	MAIN_FSM_HDMI_SETUP_VEDIO_PLL = 0,
	MAIN_FSM_HDMI_MEASURE,
	MAIN_FSM_HDMI_MEASURE_ACTIVE_SPACE,
	MAIN_FSM_HDMI_WAIT_READY,
	MAIN_FSM_HDMI_DISPLAY_ON,
} HDMI_MAIN_FSM_T;

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

typedef struct	{
	char *name;
	int progressive;
	unsigned int h_act_len;
	unsigned int v_act_len;
	unsigned int lr_v_act_len;
	unsigned int v_active_space1;
	unsigned int v_active_space2;
} HDMI_ACTIVE_SPACE_TABLE_T;

typedef struct {
	unsigned char SM;
	unsigned char SN;
	unsigned char RatioM;
	unsigned char RatioN;
} VIDEO_DPLL_RATIO_T;

typedef struct {
	int freq;
	unsigned char coeff;
	unsigned char rate;
} HDMI_AUDIO_PLL_COEFF_T;

typedef struct {
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
	char *band_name;
} HDMI_PHY_PARAM_T;

typedef struct {
	unsigned short b;
	unsigned short b_pre;
	unsigned short b_count;
	unsigned short b_debouce_count;
	u_int8_t b_mhl_debounce;
	HDMI_bool b_change;
	HDMI_bool avi_info_in;
	unsigned short avi_info_miss_cnt;
	unsigned short LG_patch_timer;
	unsigned short timer;
	short	 hotplug_timer;
	unsigned short hotplug_delay_count;
	unsigned char DEF_ready;
	unsigned char measure_ready;
	unsigned char detect_done;
	unsigned char audio_detect_done;
	unsigned char hdcp_state;/* enum HDCPRX_STATE */
} HDMIRX_IOCTL_STRUCT_T;

typedef struct {
	HDMIRX_APSTATUS_T apstatus;
	unsigned int idle_count;
} HDMIRX_PHY_IDLE_PATCH_T;

typedef struct {
	unsigned char *uncache;
	void *cache;
	unsigned long phyaddr;
	unsigned int size;
} HDMI_CAPTURE_BUFFER_T;

typedef struct {
	unsigned char BKsv[5];
	unsigned char Key[320];
} HDCP_KEY_T;

#if (defined ENABLE_HDCPKEY_ENDIAN_SWAP)
typedef struct {
	unsigned char BKsv[5];
	unsigned char Key[328];
} HDCP_KEY_T1;
#endif

typedef struct {
	HDMI_COLOR_DEPTH_T depth;
	HDMI_COLOR_SPACE_T color;
	HDMI_COLORIMETRY_T	colorimetry;
	char progressive;/* 0 --> interlaced ; 1 --> progressive */
	HDMI_3D_T hdmi_3dformat;

	unsigned int v_total;
	unsigned int h_total;
	unsigned int v_act_len;
	unsigned int h_act_len;
	unsigned int v_act_sta;
	unsigned int h_act_sta;
	unsigned int h_sync_high;
	unsigned int v_freq;
	unsigned int h_freq;
	unsigned int polarity;
	unsigned int mode_id;
	unsigned int modetable_index;

	/* only for fram packing */
	unsigned int v_active_space1;
	unsigned int v_active_space2;

	/* quincunx */
	unsigned int quincunx_en;
	unsigned int quincunx_mode;

} HDMI_TIMING_T;


/* share with VO DMA */
typedef struct {
	HDMI_TIMING_T *ptx_timing;
	HDMI_TIMING_T *pgen_timing;
	/* for 3d */
	unsigned int frame_rate_x2;
	unsigned int enable_4xxto4xx;
	unsigned int pixel_bits;

	int down_sample_number;

	int enable;/* 3d global enable */
	/* video ring buffer */
	unsigned int cap_rp;/* W: Video R:System */
	unsigned int cap_wp;/* W: System R:Video */
	int cap_size;
	HDMI_CAPTURE_BUFFER_T cap_buffer_pool;
	HDMI_CAPTURE_BUFFER_T cap_buffer[8];
	/* freeze */
	unsigned int vodma_freeze;/* W: System R:Video */
	unsigned int hdmi_freeze;
	unsigned int force_2d;/* 0: 3d  1:L only 2:R only  */
	/* pull down 22 */
	unsigned int pulldown22;
	HDMI_COLOR_SPACE_T	cap_color_fmt;
	int cap_pixel_bits;
	HDMI_COLOR_DEPTH_T cap_colordepth;
	HDMI_COLOR_SPACE_T cap_colorspace;
	HDMI_TIMING_T vodma_timing;
	HDMI_3D_OPMODE_T opmode;
	HDMI_CAPTURE_BUFFER_T cap_total_buffer;
} HDMI_3DDMA_CTRL_T;


typedef struct {
	unsigned int Info;  /* [0:1] Color Space */
						/* [2] IsInterlace */
						/* [3] is hdmi/dvi */
						/* [4:7] color depth */
						/* [8] current channel */

	unsigned char FSM; /* [0:3] Video FSM */
					   /*  [4:7] Audio FSM */

	unsigned short b;

#if (defined ENABLE_HDCPKEY_ENDIAN_SWAP)
	HDCP_KEY_T1 *hdcpkey;
#else
	HDCP_KEY_T *hdcpkey;
#endif

#ifdef CONFIG_RTK_HDCP1x_REPEATER
	unsigned char tx_hdcp_state;
#endif

	HDMI_TIMING_T  tx_timing;
	HDMI_TIMING_T  gen_timing;
	HDMI_TIMING_T  vodma_timing;

	unsigned int timer;
	int		fast_boot_source;
	/* user defined 3d parameter */
	int		force_all_3d_disable;
	int		force_2dto3d_enable;
	HDMI_3D_T force_2dto3d_mode;
	int		force_3dto2d_enable;
	int		force_3dto2d_lr_sel;
	HDMI_PATH_POLICY_T path_policy;
	int		enable_3ddma;
	int hw_pattern_gen_enable;
	HDMI_PTG_MODE_T hw_pattern_gen_mode;
	HDMI_3D_OPMODE_T   hw_hdmi_dma;
	int		hw_dither12x10_enable;
	int		hw_dither10x8_enable;
	int		hw_4xxto4xx_enable;

	int		hw_rgbtoyuv_enable;

	int		resume;
	int		exit_check;
	int		hdmi3d_capability;
	unsigned int vsync_cnt;
	HDMI_CAPTURE_BUFFER_T total_buffer;
	HDMI_3DDMA_CTRL_T hdmi_3dctrl;
	HDMI_3DDMA_CTRL_T *hdmi3dctrl_cache;
	unsigned long hdmi3dctrl_phyaddr;
	unsigned char hdmi_spd_device_info;

	/* HPD */
	int rx_5v_state;
	int gpio_hpd_ctrl;
	int gpio_5v_det;

	unsigned int audio_freq;
	unsigned char spdif_type;/* 0:LPCM,1:Non-LPCM */
} HDMI_INFO_T;

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
#define HDMI_AUDIO_SUPPORT_NON_PCM()		(1)
#define HDMI_AUDIO_IS_LPCM()  ((hdmi_rx_reg_read32(HDMI_SR, HDMI_RX_MAC) & _BIT4) == 0)

#define GET_HDMI_COLOR_SPACE()		((HDMI_COLOR_SPACE_T) (hdmi.Info & (_BIT0 | _BIT1)))
#define GET_HDMI_ISINTERLACE()		((hdmi.Info & (_BIT2)) >> 2)
#define GET_ISHDMI()				((HDMI_DVI_MODE_T)((hdmi.Info & _BIT3) >> 3))
#define GET_HDMI_CHANNEL()			((hdmi.Info & (_BIT8 | _BIT9)) >> 8)
#define GET_HDMI_CD()				((hdmi.Info & (0xf0)) >> 4)
#define GET_HDMI_DEONLY_MODE()		((hdmi.Info & _BIT10) >> 10)
#define GET_HDMI_AVMUTE_MODE()		((hdmi.Info & _BIT11) >> 11)
#define GET_HDMI_AUDIO_LAYOUT()     ((hdmi.Info & _BIT12) >> 12)
#define GET_IS_FIRST_CHECK_MODE()	((hdmi.Info & _BIT13) >> 13)
#define GET_IS_FIRST_DETECT_MODE()	((hdmi.Info & _BIT14) >> 14)
#define GET_DVI_AUDIO_PATH_SETUP()	((hdmi.Info & _BIT15) >> 15)
#define GET_HDMI_AUDIO_PATH_SETUP()	((hdmi.Info & _BIT16) >> 16)

#define GET_HDMI_AUDIO_TYPE()		((hdmi.Info & _BIT17) >> 17)
#define GET_HDMI_HBR_MODE()         ((hdmi.Info & _BIT18) >> 18)
#define GET_HDMI_BOOT_FIRST_RUN()	((hdmi.Info & _BIT19) >> 19)
#define GET_HDMI_FASTER_BOOT_EN()	((hdmi.Info & _BIT20) >> 20)
#define GET_HDMI_FASTER_SWITCH_EN()	((hdmi.Info & _BIT21) >> 21)
#define GET_HDMI_RGB_Q_RANGE()		((HDMI_RGB_YUV_RANGE_MODE_T)(hdmi.Info & (_BIT22|_BIT23)) >> 22)
#define GET_HDMI_OSD_MODE()			((hdmi.Info & (_BIT29 | _BIT30)) >> 29)

#define GET_HDMI_VIDEO_FSM()		(hdmi.FSM & 0x0F)
#define GET_HDMI_AUDIO_FSM()		((hdmi.FSM & 0xF0) >> 4)

#define SET_HDMI_COLOR_SPACE(x)		(hdmi.Info = ((hdmi.Info & ~(_BIT0 | _BIT1))  | (((unsigned int) x & 0x03))))
#define SET_HDMI_CD(x)				(hdmi.Info = ((hdmi.Info & ~(0xf0))  | (((unsigned int) x & 0x0f) << 4)))
#define SET_HDMI_ISINTERLACE(x)		do {hdmi.Info = ((hdmi.Info & (~_BIT2))  | (((unsigned int) x & 0x01) << 2)); \
											 hdmi.tx_timing.progressive = (x == 0);} while(0)
#define SET_ISHDMI(x)				(hdmi.Info =	((hdmi.Info & ~_BIT3)  | (((unsigned int) x & 0x01) << 3)))
#define SET_HDMI_CHANNEL(x) 		(hdmi.Info =	((hdmi.Info & ~(_BIT8 | _BIT9))  | (((unsigned int) x & 0x03) << 8)))
#define SET_HDMI_DEONLY_MODE(x) 	(hdmi.Info = ((hdmi.Info & (~_BIT10))  | (((unsigned int) x & 0x01) << 10)))
#define SET_HDMI_AVMUTE_MODE(x) 	(hdmi.Info = ((hdmi.Info & (~_BIT11))  | (((unsigned int) x & 0x01) << 11)))
#define SET_HDMI_AUDIO_LAYOUT(x)	(hdmi.Info = ((hdmi.Info & (~_BIT12))  | (((unsigned int) x & 0x01) << 12)))
#define SET_IS_FIRST_CHECK_MODE(x)	(hdmi.Info = ((hdmi.Info & (~_BIT13))  | (((unsigned int) x & 0x01) << 13)))
#define SET_IS_FIRST_DETECT_MODE(x) (hdmi.Info = ((hdmi.Info & (~_BIT14))  | (((unsigned int) x & 0x01) << 14)))
#define SET_DVI_AUDIO_PATH_SETUP(x) (hdmi.Info = ((hdmi.Info & (~_BIT15))  | (((unsigned int) x & 0x01) << 15)))
#define SET_HDMI_AUDIO_PATH_SETUP(x)(hdmi.Info = ((hdmi.Info & (~_BIT16))  | (((unsigned int) x & 0x01) << 16)))

#define SET_HDMI_AUDIO_TYPE(x)		(hdmi.Info = ((hdmi.Info & (~_BIT17))  | (((unsigned int) x & 0x01) << 17)))
#define SET_HDMI_HBR_MODE(x)		(hdmi.Info = ((hdmi.Info & (~_BIT18))  | (((unsigned int) x & 0x01) << 18)))
#define SET_HDMI_BOOT_FIRST_RUN(x)	(hdmi.Info = ((hdmi.Info & (~_BIT19))  | (((unsigned int) x & 0x01) << 19)))
#define SET_HDMI_FASTER_BOOT_EN(x)	(hdmi.Info = ((hdmi.Info & (~_BIT20))  | (((unsigned int) x & 0x01) << 20)))
#define SET_HDMI_FASTER_SWITCH_EN(x)(hdmi.Info = ((hdmi.Info & (~_BIT21))  | (((unsigned int) x & 0x01) << 21)))
#define SET_HDMI_RGB_Q_RANGE(x) 	(hdmi.Info = ((hdmi.Info & (~(_BIT22|_BIT23)))	| (((unsigned int) x & 0x03) << 22)))
#define SET_HDMI_OSD_MODE(x)		(hdmi.Info = ((hdmi.Info & ~(_BIT29 | _BIT30))	| (((unsigned int) x & 0x03) << 29)))
#define SET_HDMI_VIDEO_FSM(x)		(hdmi.FSM = (hdmi.FSM & 0xF0) | ((unsigned char) x & 0x0F))
#define SET_HDMI_AUDIO_FSM(x)		(hdmi.FSM = (hdmi.FSM & 0x0F) | (((unsigned char) x & 0x0F) << 4))

/*=================== hdmiMS ===================*/
#if HDMI_INTERNAL_DEBUG
int Hdmi_CRC_check(void);
#endif
unsigned char Hdmi_WaitVsync(int num);
unsigned int Hdmi_GetVSyncCountInit(void);
unsigned int Hdmi_GetVSyncCount(void);
bool Hdmi_GetInterlace(HDMI_MS_MODE_T mode);
HDMI_COLORIMETRY_T Hdmi_GetColorimetry(void);
HDMI_ERR_T Hdmi_MeasureActiveSpace(HDMI_TIMING_T *tx_timing, HDMI_TIMING_T *gen_timing);
HDMI_3D_T Hdmi_Get3DInfo(HDMI_MS_MODE_T mode);
unsigned char Hdmi_Get3DExtInfo(void);
void Hdmi_Get3DGenTiming(HDMI_TIMING_T *tx_timing, HDMI_TIMING_T *gen_timing);

/*=================== hdmirx_hdcp ===================*/
void Hdmi_HdcpInit(void);
unsigned char Is_HdmiRx_hdcp1x_enabled(void);


/*=================== hdmiHdmi ===================*/
unsigned char drvif_Hdmi_AVI_VIC(void);
#if HDMI2p0
void drvif_Hdmi2p0_Scdc_Reset(void);
void drvif_Hdmi2p0_Error_Count(void);
void TMDS_6G_Recovery(void);
#endif


#endif /* __HDMI_INTERNAL_H_ */

