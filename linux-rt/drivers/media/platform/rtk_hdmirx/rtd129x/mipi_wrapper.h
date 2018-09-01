/*
 * mipi_wrapper.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _MIPI_WRAPPER_H_
#define _MIPI_WRAPPER_H_

typedef struct {
	unsigned int dst_fmt;
	unsigned int src_fmt;
	unsigned int src_sel;
	unsigned int yuv420_uv_seq;
	unsigned int vs;
	unsigned int vs_near;
	unsigned int vs_yodd;
	unsigned int vs_codd;
	unsigned int hs;
	unsigned int hs_yodd;
	unsigned int hs_codd;
	unsigned int yuv420_fmt;
	unsigned int ccs_data_format;
	unsigned int yuv_to_rgb;
	unsigned int chroma_ds_mode;
	unsigned int chroma_ds_en;
	unsigned int chroma_us_mode;
	unsigned int chroma_us_en;
	unsigned int hdmirx_interlace_en;
	unsigned int hdmirx_interlace_polarity;
	unsigned int int_en4;
	unsigned int int_en3;
	unsigned int int_en2;
	unsigned int int_en1;
	unsigned int int_en0;
	unsigned int en;
} MIPI_REG;

typedef enum {
	OUT_8BIT_YUV422   = 0x2,
	OUT_8BIT_YUV420   = 0x3,
	OUT_10BIT_YUV422  = 0x4,
	OUT_10BIT_YUV420  = 0x5,
	OUT_ARGB  = 0x10,
	OUT_ARBG  = 0x11,
	OUT_AGRB  = 0x12,
	OUT_AGBR  = 0x13,
	OUT_ABRG  = 0x14,
	OUT_ABGR  = 0x15,
	OUT_RGBA  = 0x16,
	OUT_RBGA  = 0x17,
	OUT_GRBA  = 0x18,
	OUT_GBRA  = 0x19,
	OUT_BRGA  = 0x1A,
	OUT_BGRA  = 0x1B,
	OUT_UNKNOW
} MIPI_OUT_COLOR_SPACE_T;

typedef enum {
	IN_RGB888 = 0x0,
	IN_YUV444 = 0x1,
	IN_YUV422 = 0x2,
	IN_UNKNOW
} MIPI_IN_COLOR_SPACE_T;

typedef enum {
	UV_NV12 = 0x0,/* U0V0U1V1 */
	UV_NV21 = 0x1,/* V0U0V1U1 */
} MIPI_YUV420_UV_SEQ;

typedef struct {
	char hdmi_rx_init;
	char mipi_init;
	unsigned int src_sel; /* 0:mipi; 1:hdmi_rx */
	unsigned int h_input_len;
	unsigned int v_input_len;
	MIPI_IN_COLOR_SPACE_T input_color;
	unsigned int h_output_len;
	unsigned int v_output_len;
	MIPI_OUT_COLOR_SPACE_T output_color;
	MIPI_YUV420_UV_SEQ uv_seq;
	int pitch;
	struct work_struct mipi_reset_work;
} MIPI_TOP_INFO;

enum {
	DEMUX8   = 0x0,
	DEMUX16  = 0x1,
	DEMUX32  = 0x2,
};

enum {
	Onelane  = 0x0,
	fourlane = 0x1,
};

enum {
	disable = 0x0,
	enable  = 0x1,
};

enum {
	dvi_bit_8  = 0x0,
	div_bit_16 = 0x1,
	div_bit_32 = 0x2,
};

enum {
	posedge = 0x0,
	negedge = 0x1,
};

enum YUV_SRC_SEL {
	SEL_UYVY  = 0x0,
	SEL_VYUY  = 0x1,
	SEL_YVYU  = 0x2,
	SEL_YUYV  = 0x3,
};

enum DEC_FORMAT {
	RAW8_dec_format    = 0x0,
	RAW10_dec_format   = 0x1,
	YUV422_dec_format  = 0x2,
	JPEG_dec_format    = 0x3,
	RAW12_dec_format   = 0x4,
};

enum {
	DTYPE_YUY8    =	   0x1E,
	DTYPE_MJPEG   =    0x31,
};

void register_mipi_ion(struct v4l2_hdmi_dev *dev);
void deregister_mipi_ion(struct v4l2_hdmi_dev *dev);
void mipi_reset_work_func(struct work_struct *work);
void stop_mipi_process(void);
void set_mipi_env(void);
void set_enable_mipi(unsigned char enable);
void set_mipi_type(unsigned int type);
void set_video_dest_addr(int addr1y, int addr1uv, int addr2y, int addr2uv);
void set_video_DDR_start_addr(struct v4l2_hdmi_dev *dev);
void setup_mipi(void);
irqreturn_t hdmirx_mipi_isr(int irq, void *dev_id);
#endif/* _MIPI_WRAPPER_H_ */
