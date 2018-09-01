/*
 * hdmirx_wrapper.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/printk.h>
#include <linux/ratelimit.h>
#include <linux/workqueue.h>

#include "hdmirx_wrapper.h"
#include "v4l2_hdmi_dev.h"
#include "hdmirx_reg.h"
#include "mipi_wrapper.h"

#include "rx_drv/hdmiInternal.h"

/*=================== extern Variable/Function ===================*/
extern HDMI_INFO_T hdmi;
extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;
extern MIPI_TOP_INFO mipi_top;
#if HDMI2p0
extern u_int8_t bHDMI_6G_flag;
#endif

extern HDMI_DVI_MODE_T IsHDMI(void);
#if HDMI_REPEATER_SUPPORT
extern void Set_Hdmitx_PLL(void);
#endif
/*======================================================*/

static void rxdetect_work_fun(struct work_struct *work);
static DECLARE_DELAYED_WORK(rxdetect_work, rxdetect_work_fun);

static void rxdetect_work_fun(struct work_struct *work)
{
	if (hdmi_ioctl_struct.detect_done)
		set_hdmirx_wrapper_interrupt_en(0, 0, 1);
}

const unsigned int resolution_format[17][2] = {
	{ 640,  480},
	{ 720,  480},
	{1280,  720},
	{1920, 1080},
	{1920,  540},
	{ 720,  240},
	{1440,  480},
	{ 720,  576},
	{ 720,  288},
	{1440,  576},
	{ 720,  400},
	{ 800,  600},
	{1024,  768},
	{1280,  960},
	{1280, 1024},
	{3840, 2160},/* For HDMI 1.x 4Kp24/25/30, PacketByte4 VIC=0 */
	{4096, 2160},/* For HDMI 1.x */
};
const unsigned int format_number = sizeof(resolution_format)/sizeof(resolution_format[0]);

const HDMI_VIC_TABLE_T hdmi_vic_table[] = {
	/* {width, height, fps, interlace} */
	{   0,    0,  60, 0 }, /* No such vic, set fps=60 for standard timings and DVI mode */
	{ 640,  480,  60, 0 }, /* VIC: 1 */
	{ 720,  480,  60, 0 }, /* VIC: 2 , 480p */
	{ 720,  480,  60, 0 }, /* VIC: 3 */
	{1280,  720,  60, 0 }, /* VIC: 4 , 720p60 */
	{1920, 1080,  60, 1 }, /* VIC: 5, 1080i60 */
	{ 720,  480,  60, 1 }, /* VIC: 6, NTSC */
	{ 720,  480,  60, 1 }, /* VIC: 7, NTSC */
	{ 720,  240,  60, 0 }, /* VIC: 8 */
	{ 720,  240,  60, 0 }, /* VIC: 9 */
	{2880,  480,  60, 1 }, /* VIC: 10 */
	{2880,  480,  60, 1 }, /* VIC: 11 */
	{2880,  240,  60, 0 }, /* VIC: 12 */
	{2880,  240,  60, 0 }, /* VIC: 13 */
	{1440,  480,  60, 0 }, /* VIC: 14 */
	{1440,  480,  60, 0 }, /* VIC: 15 */
	{1920, 1080,  60, 0 }, /* VIC: 16, 1080p60 */
	{ 720,  576,  50, 0 }, /* VIC: 17, 576p */
	{ 720,  576,  50, 0 }, /* VIC: 18 */
	{1280,  720,  50, 0 }, /* VIC: 19, 720p50 */
	{1920, 1080,  50, 1 }, /* VIC: 20, 1080i50 */
	{ 720,  576,  50, 1 }, /* VIC: 21, PAL */
	{ 720,  576,  50, 1 }, /* VIC: 22 */
	{ 720,  288,  50, 0 }, /* VIC: 23 */
	{ 720,  288,  50, 0 }, /* VIC: 24 */
	{2880,  576,  50, 1 }, /* VIC: 25 */
	{2880,  576,  50, 1 }, /* VIC: 26 */
	{2880,  288,  50, 0 }, /* VIC: 27 */
	{2880,  288,  50, 0 }, /* VIC: 28 */
	{1440,  576,  50, 0 }, /* VIC: 29 */
	{1440,  576,  50, 0 }, /* VIC: 30 */
	{1920, 1080,  50, 0 }, /* VIC: 31, 1080p50 */
	{1920, 1080,  24, 0 }, /* VIC: 32 */
	{1920, 1080,  25, 0 }, /* VIC: 33 */
	{1920, 1080,  30, 0 }, /* VIC: 34 */
	{2880,  480,  60, 0 }, /* VIC: 35 */
	{2880,  480,  60, 0 }, /* VIC: 36 */
	{2880,  576,  50, 0 }, /* VIC: 37 */
	{2880,  576,  50, 0 }, /* VIC: 38 */
	{1920, 1080,  50, 1 }, /* VIC: 39 */
	{1920, 1080, 100, 1 }, /* VIC: 40 */
	{1280,  720, 100, 0 }, /* VIC: 41 */
	{ 720,  576, 100, 0 }, /* VIC: 42 */
	{ 720,  576, 100, 0 }, /* VIC: 43 */
	{ 720,  576, 100, 1 }, /* VIC: 44 */
	{ 720,  576, 100, 1 }, /* VIC: 45 */
	{1920, 1080, 120, 1 }, /* VIC: 46 */
	{1280,  720, 120, 0 }, /* VIC: 47 */
	{ 720,  480, 120, 0 }, /* VIC: 48 */
	{ 720,  480, 120, 0 }, /* VIC: 49 */
	{ 720,  480, 120, 1 }, /* VIC: 50 */
	{ 720,  480, 120, 1 }, /* VIC: 51 */
	{ 720,  576, 200, 0 }, /* VIC: 52 */
	{ 720,  576, 200, 0 }, /* VIC: 53 */
	{ 720,  576, 200, 1 }, /* VIC: 54 */
	{ 720,  576, 200, 1 }, /* VIC: 55 */
	{ 720,  480, 240, 0 }, /* VIC: 56 */
	{ 720,  480, 240, 0 }, /* VIC: 57 */
	{ 720,  480, 240, 1 }, /* VIC: 58 */
	{ 720,  480, 240, 1 }, /* VIC: 59 */
	{1280,  720,  24, 0 }, /* VIC: 60 */
	{1280,  720,  25, 0 }, /* VIC: 61 */
	{1280,  720,  30, 0 }, /* VIC: 62 */
	{1920, 1080, 120, 0 }, /* VIC: 63 */
	{1920, 1080, 100, 0 }, /* VIC: 64 */
	{1280,  720,  24, 0 }, /* VIC: 65 */
	{1280,  720,  25, 0 }, /* VIC: 66 */
	{1280,  720,  30, 0 }, /* VIC: 67 */
	{1280,  720,  50, 0 }, /* VIC: 68 */
	{1280,  720,  60, 0 }, /* VIC: 69 */
	{1280,  720, 100, 0 }, /* VIC: 70 */
	{1280,  720, 120, 0 }, /* VIC: 71 */
	{1920, 1080,  24, 0 }, /* VIC: 72 */
	{1920, 1080,  25, 0 }, /* VIC: 73 */
	{1920, 1080,  30, 0 }, /* VIC: 74 */
	{1920, 1080,  50, 0 }, /* VIC: 75 */
	{1920, 1080,  60, 0 }, /* VIC: 76 */
	{1920, 1080, 100, 0 }, /* VIC: 77 */
	{1920, 1080, 120, 0 }, /* VIC: 78 */
	{1680,  720,  24, 0 }, /* VIC: 79 */
	{1680,  720,  25, 0 }, /* VIC: 80 */
	{1680,  720,  30, 0 }, /* VIC: 81 */
	{1680,  720,  50, 0 }, /* VIC: 82 */
	{1680,  720,  60, 0 }, /* VIC: 83 */
	{1680,  720, 100, 0 }, /* VIC: 84 */
	{1680,  720, 120, 0 }, /* VIC: 85 */
	{2560, 1080,  24, 0 }, /* VIC: 86 */
	{2560, 1080,  25, 0 }, /* VIC: 87 */
	{2560, 1080,  30, 0 }, /* VIC: 88 */
	{2560, 1080,  50, 0 }, /* VIC: 89 */
	{2560, 1080,  60, 0 }, /* VIC: 90 */
	{2560, 1080, 100, 0 }, /* VIC: 91 */
	{2560, 1080, 120, 0 }, /* VIC: 92 */
	{3840, 2160,  24, 0 }, /* VIC: 93 */
	{3840, 2160,  25, 0 }, /* VIC: 94 */
	{3840, 2160,  30, 0 }, /* VIC: 95 */
	{3840, 2160,  50, 0 }, /* VIC: 96 */
	{3840, 2160,  60, 0 }, /* VIC: 97 */
	{4096, 2160,  24, 0 }, /* VIC: 98 */
	{4096, 2160,  25, 0 }, /* VIC: 99 */
	{4096, 2160,  30, 0 }, /* VIC: 100 */
	{4096, 2160,  50, 0 }, /* VIC: 101 */
	{4096, 2160,  60, 0 }, /* VIC: 102 */
	{3840, 2160,  24, 0 }, /* VIC: 103 */
	{3840, 2160,  25, 0 }, /* VIC: 104 */
	{3840, 2160,  30, 0 }, /* VIC: 105 */
	{3840, 2160,  50, 0 }, /* VIC: 106 */
	{3840, 2160,  60, 0 }, /* VIC: 107 */
	{3840, 2160,  30, 0 }, /* (108)extened vic: 1 */
	{3840, 2160,  25, 0 }, /* (109)extened vic: 2 */
	{3840, 2160,  24, 0 }, /* (110)extened vic: 3 */
	{4096, 2160,  24, 0 }, /* (111)extened vic: 4 */
};


unsigned char hdmirx_wrapper_convert_color_fmt(HDMI_COLOR_SPACE_T color)
{
	unsigned char yuv_fmt;

	switch (color) {
	case COLOR_RGB:
		yuv_fmt = 0;
		break;
	case COLOR_YUV422:
		yuv_fmt = 2;
		break;
	case COLOR_YUV444:
	case COLOR_YUV420:/* YUV420to444 */
		yuv_fmt = 1;
		break;
	default:
		yuv_fmt = 0;
		HDMIRX_ERROR("[%s] Unsupported color(%u)", __func__, color);
		break;
	}

	return yuv_fmt;
}

void set_hdmirx_wrapper_interrupt_en(int ver_err_en, int hor_err_en, int polarity_detect_en)
{
	unsigned int reg_val;

	reg_val = hdmi_rx_reg_read32(HDMIRX_WRAPPER_INTERRUPT_EN, HDMI_RX_HDMI_WRAPPER);

	if (ver_err_en >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_INTERRUPT_EN_ver_err_en_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_INTERRUPT_EN_ver_err_en(ver_err_en);
	}
	if (hor_err_en >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_INTERRUPT_EN_hor_err_en_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_INTERRUPT_EN_hor_err_en(hor_err_en);
	}
	if (polarity_detect_en >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_INTERRUPT_EN_polarity_detect_en_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_INTERRUPT_EN_polarity_detect_en(polarity_detect_en);
	}
	hdmi_rx_reg_write32(HDMIRX_WRAPPER_INTERRUPT_EN, reg_val, HDMI_RX_HDMI_WRAPPER);
}


void set_hdmirx_wrapper_active_pixels(unsigned int v_pixel, unsigned int h_pixel)
{
	hdmi_rx_reg_write32(HDMIRX_WRAPPER_ACTIVE_PIXELS,
		HDMIRX_WRAPPER_ACTIVE_PIXELS_set_ver_width(v_pixel) |
		HDMIRX_WRAPPER_ACTIVE_PIXELS_set_hor_width(h_pixel), HDMI_RX_HDMI_WRAPPER);
}


void set_hdmirx_wrapper_hor_threshold(unsigned int h_threshold)
{
	hdmi_rx_reg_write32(HDMIRX_WRAPPER_HOR_THRESHOLD,
		HDMIRX_WRAPPER_HOR_THRESHOLD_hor_threshold(h_threshold), HDMI_RX_HDMI_WRAPPER);
}


void set_hdmirx_wrapper_control_0(int fifo_stage, int fw_dma_en,
	int polarity_set_en, int polarity_set, int yuv_fmt, int hdmirx_en)
{
	unsigned int reg_val;

	reg_val = hdmi_rx_reg_read32(HDMIRX_WRAPPER_CONTROL_0, HDMI_RX_HDMI_WRAPPER);

	if (fifo_stage >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_CONTROL_0_fifo_stage_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_CONTROL_0_fifo_stage(fifo_stage);
	}
	if (fw_dma_en >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_CONTROL_0_fw_dma_en_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_CONTROL_0_fw_dma_en(fw_dma_en);
	}
	if (polarity_set_en >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_CONTROL_0_polarity_set_en_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_CONTROL_0_polarity_set_en(polarity_set_en);
	}
	if (polarity_set >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_CONTROL_0_polarity_set_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_CONTROL_0_polarity_set(polarity_set);
	}
	if (yuv_fmt >= 0) {
		reg_val = reg_val & (~HDMIRX_WRAPPER_CONTROL_0_yuv_fmt_mask);
		reg_val = reg_val | HDMIRX_WRAPPER_CONTROL_0_yuv_fmt(yuv_fmt);
	}
	if (hdmirx_en >= 0) {
		reg_val = reg_val &
			(~(HDMIRX_WRAPPER_CONTROL_0_reg_clken_hdmirx_mask |
			HDMIRX_WRAPPER_CONTROL_0_hdmirx_en_mask));

		reg_val = reg_val |
			HDMIRX_WRAPPER_CONTROL_0_reg_clken_hdmirx(hdmirx_en) |
			HDMIRX_WRAPPER_CONTROL_0_hdmirx_en(hdmirx_en);
	}
	hdmi_rx_reg_write32(HDMIRX_WRAPPER_CONTROL_0, reg_val, HDMI_RX_HDMI_WRAPPER);

}

unsigned int hdmirx_wrapper_get_active_line(void)
{
	unsigned int buf0;

	buf0 = HDMIRX_WRAPPER_MONITOR_1_get_line_buf0(hdmi_rx_reg_read32(HDMIRX_WRAPPER_MONITOR_1, HDMI_RX_HDMI_WRAPPER));
	return buf0;
}

unsigned int hdmirx_wrapper_get_active_pixel(void)
{
	unsigned int reg01;
	unsigned int buf0;

	reg01 = hdmi_rx_reg_read32(HDMIRX_WRAPPER_DEN_BUF01, HDMI_RX_HDMI_WRAPPER);
	buf0 = HDMIRX_WRAPPER_DEN_BUF01_get_den_buf0(reg01);
	return buf0;
}

static inline unsigned int check_hdmirx_resolution_match(void)
{
	unsigned int active_pixel, active_line, height;
	unsigned int i, vic;
	unsigned char color_fmt;

	vic = 0;
	if (IsHDMI())
		vic = drvif_Hdmi_AVI_VIC();

	active_pixel =	hdmirx_wrapper_get_active_pixel();
	active_line = hdmirx_wrapper_get_active_line();
	color_fmt = hdmirx_wrapper_convert_color_fmt(GET_HDMI_COLOR_SPACE());

	if (hdmi_vic_table[vic].interlace)
		height = active_line*2;
	else
		height = active_line;

	if ((active_pixel == hdmi_vic_table[vic].width) &&
		(height == hdmi_vic_table[vic].height) && vic) {

		mipi_top.h_input_len = active_pixel;
		mipi_top.v_input_len = active_line;
		mipi_top.input_color = color_fmt;

		HDMIRX_INFO("Check resolution match => Width(%u) Height(%u) VIC(%u)",
			active_pixel, height, vic);
		return 1;
	} else if (vic == 0) {
		/* Support standard timings and DVI mode */
		for (i = 0; i < format_number; i++) {
			if ((active_pixel == resolution_format[i][0]) &&
				(active_line == resolution_format[i][1])) {

				mipi_top.h_input_len = active_pixel;
				mipi_top.v_input_len = active_line;
				mipi_top.input_color = color_fmt;

				HDMIRX_INFO("Check resolution match => Width(%u) Height(%u) DIV",
					active_pixel, height);
				return 1;
			}
		}
	}

	HDMIRX_INFO("Check resolution not match => active_pixel(%u) active_line(%u) VIC(%u)",
		active_pixel, active_line, vic);

	return 0;
}

void restartHdmiRxWrapperDetection(void)
{
	unsigned char hdcp_state;

	stop_mipi_process();
	set_hdmirx_wrapper_interrupt_en(0, 0, 0);
	SET_HDMI_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
	SET_HDMI_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
	set_hdmirx_wrapper_control_0(-1, 0, -1, -1, -1, -1);/* Stop DMA */
	set_hdmirx_wrapper_hor_threshold(HDMI_MIN_SUPPORT_H_PIXEL);
#if HDMI2p0
	bHDMI_6G_flag = 0;
#endif

	hdcp_state = hdmi_ioctl_struct.hdcp_state;
	memset(&hdmi_ioctl_struct, 0, sizeof(hdmi_ioctl_struct));
	/* Keep hdcp state, clear when cable unplugged */
	hdmi_ioctl_struct.hdcp_state = hdcp_state;
}

static const char * const str_color[] = {"RGB", "YUV444", "YUV422"};
static const char * const str_progressive[] = {"Int", "Prog"};
void hdmirx_wrapper_isr(void)
{
	static unsigned char miss_count = 0;
	unsigned int status;
	unsigned int active_pixel, active_line;

	status = hdmi_rx_reg_read32(HDMIRX_WRAPPER_INTERRUPT_STATUS, HDMI_RX_HDMI_WRAPPER);

	if (unlikely(status == 0)) {
		/* HDMIRX_INFO("do nothing..."); */
		return;
	} else if (HDMIRX_WRAPPER_INTERRUPT_STATUS_get_polarity_detect_sts(status)) {
		/* POLARITY_DETECT, Disable interrupt */
		set_hdmirx_wrapper_interrupt_en(0, 0, 0);

		if (!check_hdmirx_resolution_match()) {
			/* Format not match, re-enable polarity detection if miss_count<3 */
			if (miss_count >= 3) {
				miss_count = 0;
				HDMIRX_INFO("Polarity detect fail: Reset detection...\n");
				restartHdmiRxWrapperDetection();
			} else {
				miss_count++;
				/* Enable wrapper interrupt later */
				schedule_delayed_work(&rxdetect_work, msecs_to_jiffies(1000));
			}
			return;
		}

		HDMIRX_INFO("Polarity detect done: hor(%u) ver(%u) color(%s) I/P(%s)",
			mipi_top.h_input_len, mipi_top.v_input_len,
			str_color[mipi_top.input_color],
			str_progressive[hdmi.tx_timing.progressive]);

		set_hdmirx_wrapper_active_pixels(mipi_top.v_input_len, mipi_top.h_input_len);
		set_hdmirx_wrapper_hor_threshold(mipi_top.h_input_len);

		hdmi_ioctl_struct.measure_ready = 1;

#if HDMI_REPEATER_SUPPORT
		Set_Hdmitx_PLL();
#endif
		/* Format match, enable error detection */
		set_hdmirx_wrapper_interrupt_en(1, 1, 0);
	} else if (HDMIRX_WRAPPER_INTERRUPT_STATUS_get_hor_err_sts(status)) {
		/* HOR_ERR */
		set_hdmirx_wrapper_interrupt_en(0, 0, 0);

		active_pixel =	hdmirx_wrapper_get_active_pixel();
#if 0
		if (mipi_top.h_input_len-active_pixel <= 5) {
			set_hdmirx_wrapper_interrupt_en(1, 1, 0);
			return;
		} else if ((mipi_top.h_input_len == 1920) && (active_pixel == 1921)) {
			set_hdmirx_wrapper_interrupt_en(1, 1, 0);
			return;
		}
#endif
		HDMIRX_INFO("ISR status:%x reenable polarity detection... pixel(%u)\n",
			status, active_pixel);

		miss_count = 0;
		restartHdmiRxWrapperDetection();
		return;
	} else if (HDMIRX_WRAPPER_INTERRUPT_STATUS_get_ver_err_sts(status)) {
		/* VER_ERR */
		set_hdmirx_wrapper_interrupt_en(0, 0, 0);

		active_line = hdmirx_wrapper_get_active_line();
#if 0
		if (mipi_top.v_input_len-active_line <= 5) {
			set_hdmirx_wrapper_interrupt_en(1, 1, 0);
			return;
		} else if ((mipi_top.v_input_len == 1080) && (active_line == 1081)) {
			set_hdmirx_wrapper_interrupt_en(1, 1, 0);
			return;
		}
#endif
		HDMIRX_INFO("ISR status:%x reenable polarity detection... line(%u)\n",
			status, active_line);

		miss_count = 0;
		restartHdmiRxWrapperDetection();
		return;
	}
}


void hdmi_related_wrapper_init(void)
{
	/* HDMIRX_INFO("[%s]",  __func__); */

	/* v,h,polarity */
	set_hdmirx_wrapper_interrupt_en(0, 0, 0);
	/* fifo_stage,fw_dma_en,polarity_set_en,polarity_set,yuv_fmt,hdmirx_en */
	set_hdmirx_wrapper_control_0(1, 0, 0, 0, 0, 1);
	set_hdmirx_wrapper_hor_threshold(HDMI_MIN_SUPPORT_H_PIXEL);
}

