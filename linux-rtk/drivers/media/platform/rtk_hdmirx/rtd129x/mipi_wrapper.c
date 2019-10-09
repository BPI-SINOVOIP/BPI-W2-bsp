/*
 * mipi_wrapper.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "v4l2_hdmi_dev.h"
#include "mipi_wrapper.h"
#include "hdmirx_reg.h"
#include "hdmirx_clk_ctrl.h"

#include "rx_drv/hdmiInternal.h"

MIPI_TOP_INFO mipi_top;

/*=================== extern Variable/Function ===================*/
extern HDMI_INFO_T hdmi;
extern int hdmi_stream_on;

extern HDMI_ERR_T Hdmi_CheckConditionChange(void);
extern void hdmirx_wrapper_isr(void);
extern void set_hdmirx_wrapper_control_0(int fifo_stage, int fw_dma_en,
	int polarity_set_en, int polarity_set, int yuv_fmt, int hdmirx_en);
extern void restartHdmiRxWrapperDetection(void);
#ifdef CONFIG_RTK_HDCPRX_2P2
extern void  Hdmi_HDCP_2_2_msg_hander(void);
#endif
extern void start_hdcp1x_repeater_work(void);
/*======================================================*/

extern struct ion_device *rtk_phoenix_ion_device;

void register_mipi_ion(struct v4l2_hdmi_dev *dev)
{
	struct mipi_ion_buf *ion_buf;
	unsigned long size;
	size_t len;
	int ret_val;

	size = dev->width * dev->height * dev->bpp/8;
	/* Increase 1/8 size for prevent MIPI write out of range */
	size = roundup(size*9/8, 4096);

	ion_buf = &dev->ion_buf;
	ion_buf->client = ion_client_create(rtk_phoenix_ion_device, "hdmirx");

	ion_buf->handle = ion_alloc(ion_buf->client, size, 4096,
		RTK_PHOENIX_ION_HEAP_MEDIA_MASK,
		ION_FLAG_NONCACHED | ION_FLAG_HWIPACC);

	if (IS_ERR(ion_buf->handle))
		HDMIRX_ERROR("%s ion_alloc fail", __func__);

	ret_val = ion_phys(ion_buf->client, ion_buf->handle, &ion_buf->phys_addr, &len);
	if (ret_val != 0)
		HDMIRX_ERROR("%s ion_phys fail", __func__);

	HDMIRX_INFO(" ion_addr=0x%08lx size=%zd", ion_buf->phys_addr, len);
}

void deregister_mipi_ion(struct v4l2_hdmi_dev *dev)
{
	struct mipi_ion_buf *ion_buf;

	ion_buf = &dev->ion_buf;

	if (ion_buf->client != NULL) {
		HDMIRX_INFO("%s", __func__);
		ion_free(ion_buf->client, ion_buf->handle);
		ion_buf->client = NULL;
	}
}

void mipi_reset_work_func(struct work_struct *work)
{
	hdmirx_reset_control(RST_MIPI, CTL_DISABLE);
	hdmirx_reset_control(RST_MIPI, CTL_ENABLE);
}

void stop_mipi_process(void)
{
	set_enable_mipi(0);
	/* Stop DMA */
	set_hdmirx_wrapper_control_0(-1, 0, -1, -1, -1, -1);
	/* Reset mipi clock */
	schedule_work(&mipi_top.mipi_reset_work);

	hdmi_stream_on = 0;
	mipi_top.mipi_init = 0;
}

void set_mipi_env(void)
{
	HDMIRX_DEBUG("[%s]", __func__);

	/* SEL_DIV_RG */
	hdmi_rx_reg_write32(MIPI_APHY_REG15,
		MIPI_APHY_REG15_SEL_DIV_RG(DEMUX16), HDMI_RX_MIPI_PHY);
	/* Lane mux sel & soft reset */
	hdmi_rx_reg_write32(MIPI_DPHY_REG4,
		MIPI_DPHY_REG4_SL_RG(fourlane) | MIPI_DPHY_REG4_Sw_rst(disable), HDMI_RX_MIPI_PHY);

	/* 4 lane */
	hdmi_rx_reg_write32(MIPI_DPHY_PWDB,
		MIPI_DPHY_PWDB_L3_pwdb(enable) | MIPI_DPHY_PWDB_L2_pwdb(enable) |
		MIPI_DPHY_PWDB_L1_pwdb(enable) | MIPI_DPHY_PWDB_L0_pwdb(enable),
		HDMI_RX_MIPI_PHY);/* Lane1 & Lane2 power on */

	hdmi_rx_reg_write32(MIPI_DPHY_REG0,
		MIPI_DPHY_REG0_Div_sel(div_bit_16) | MIPI_DPHY_REG0_Lane3_en(enable) |
		MIPI_DPHY_REG0_Lane2_en(enable) | MIPI_DPHY_REG0_Lane1_en(enable) |
		MIPI_DPHY_REG0_Lane0_en(enable),
		HDMI_RX_MIPI_PHY);/* 16bit data width, Lane1 & Lane2 enable */

	hdmi_rx_reg_write32(MIPI_DPHY_REG9,
		MIPI_DPHY_REG9_Lane3_clk_edge(posedge) | MIPI_DPHY_REG9_Lane2_clk_edge(posedge) |
		MIPI_DPHY_REG9_Lane1_clk_edge(posedge) | MIPI_DPHY_REG9_Lane0_clk_edge(posedge),
		HDMI_RX_MIPI_PHY);/* Lane CLK edge */

	hdmi_rx_reg_write32(MIPI_DPHY_REG1,
		MIPI_DPHY_REG1_yuv_src_sel(SEL_UYVY) | MIPI_DPHY_REG1_dec_format(YUV422_dec_format),
		HDMI_RX_MIPI_PHY);/* SEL_UYVY //SEL_YUYV & Dec data format for YUV422 */

	hdmi_rx_reg_write32(MIPI_DPHY_REG2, MIPI_DPHY_REG2_D_type(DTYPE_YUY8), HDMI_RX_MIPI_PHY);/* MIPI data type YUV422 8bit */

	hdmi_rx_reg_write32(MIPI_DPHY_REG6,
		MIPI_DPHY_REG6_Dvld_lane1(0x6) | MIPI_DPHY_REG6_Dvld_lane0(0x6),
		HDMI_RX_MIPI_PHY);
	hdmi_rx_reg_write32(MIPI_DPHY_REG7,
		MIPI_DPHY_REG7_Dvld_lane3(0x6) | MIPI_DPHY_REG7_Dvld_lane2(0x6),
		HDMI_RX_MIPI_PHY);

}

unsigned int rx_pitch_measurement(unsigned int output_h, MIPI_OUT_COLOR_SPACE_T output_color)
{
	unsigned int pitch, pitch_factor;

	HDMIRX_INFO("rx_pitch_measurement,output_color=%x\n", output_color);

	switch (output_color) {
	case OUT_8BIT_YUV422:
	case OUT_8BIT_YUV420:
		pitch_factor = 1;
		break;
	case OUT_10BIT_YUV422:
		pitch_factor = 2;
		break;
	default: /* all other RGB case */
		pitch_factor = 4;
		break;
	}

	pitch = output_h * pitch_factor;
	/* pitch has to be n*16 byte */
	if (output_color < OUT_ARGB)
		pitch = roundup16(pitch);

	return pitch;
}

void set_video_DDR_start_addr(struct v4l2_hdmi_dev *dev)
{
	unsigned int addry;
	unsigned int addruv;
	unsigned int offset;
	unsigned long flags = 0;
	struct hdmi_dmaqueue *hdmidq;
	struct mipi_ion_buf *ion_buf;

	hdmidq = &dev->hdmidq;
	ion_buf = &dev->ion_buf;

	offset = roundup16(mipi_top.pitch) * roundup16(mipi_top.v_output_len);

	spin_lock_irqsave(&dev->slock, flags);
	hdmidq->skip_frame[0] = 1;
	hdmidq->skip_frame[1] = 1;

	addry = ion_buf->phys_addr;
	addruv = ion_buf->phys_addr + offset;
	set_video_dest_addr(addry, addruv, addry, addruv);
	spin_unlock_irqrestore(&dev->slock, flags);

	HDMIRX_INFO("[%s] addr1y(0x%08x) addr1uv(0x%08x) addr2y(0x%08x) addr2uv(0x%08x)",
		__func__, addry, addruv, addry, addruv);
}

void set_mipi_type(unsigned int type)
{
	unsigned int reg_val;

	HDMIRX_DEBUG("[%s] type(%u)", __func__, type);

	reg_val = hdmi_rx_reg_read32(MIPI_TYPE, HDMI_RX_MIPI);

	reg_val = reg_val & (~MIPI_TYPE_mipi_type_mask);

	hdmi_rx_reg_write32(MIPI_TYPE, reg_val | MIPI_TYPE_mipi_type(type), HDMI_RX_MIPI);
}

void set_pic_dest_addr(int addry, int addruv)
{
	if (addry >= 0)
		hdmi_rx_reg_write32(MIPI_SA2, addry, HDMI_RX_MIPI);


	if (addruv >= 0)
		hdmi_rx_reg_write32(MIPI_SA2_UV, addruv, HDMI_RX_MIPI);

}

void set_pic_dest_size(unsigned int dst_width, unsigned int pitch)
{

	hdmi_rx_reg_write32(MIPI_SIZE1,
		MIPI_SIZE1_dst_width_pic(dst_width) | MIPI_SIZE1_pitch_pic(pitch), HDMI_RX_MIPI);
}

void set_video_dest_addr(int addr1y, int addr1uv, int addr2y, int addr2uv)
{
	if (addr1y >= 0)
		hdmi_rx_reg_write32(MIPI_SA0, addr1y, HDMI_RX_MIPI);

	if (addr1uv >= 0)
		hdmi_rx_reg_write32(MIPI_SA0_UV, addr1uv, HDMI_RX_MIPI);

	if (addr2y >= 0)
		hdmi_rx_reg_write32(MIPI_SA1, addr2y, HDMI_RX_MIPI);

	if (addr2uv >= 0)
		hdmi_rx_reg_write32(MIPI_SA1_UV, addr2uv, HDMI_RX_MIPI);
}

void set_video_dest_size(unsigned int dst_width, unsigned int pitch)
{

	hdmi_rx_reg_write32(MIPI_SIZE0,
		MIPI_SIZE0_dst_width_video(dst_width) | MIPI_SIZE0_pitch_video(pitch), HDMI_RX_MIPI);
}

void set_video_src_size(unsigned int src_width)
{
	unsigned int reg_val;

	reg_val = hdmi_rx_reg_read32(MIPI_SIZE2, HDMI_RX_MIPI);
	reg_val = reg_val & (~MIPI_SIZE2_src_width_video_mask);
	hdmi_rx_reg_write32(MIPI_SIZE2, reg_val | MIPI_SIZE2_src_width_video(src_width), HDMI_RX_MIPI);
}

void set_init_mipi_value(MIPI_REG *mipi_reg)
{
	unsigned int reg_val = 0;

	reg_val = (mipi_reg->dst_fmt << 27) |
			(mipi_reg->src_fmt << 25) |
			(mipi_reg->src_sel << 24) |
			(mipi_reg->yuv420_uv_seq << 23) |
			(mipi_reg->vs << 22) |
			(mipi_reg->vs_near << 21) |
			(mipi_reg->vs_yodd << 20) |
			(mipi_reg->vs_codd << 19) |
			(mipi_reg->hs << 18) |
			(mipi_reg->hs_yodd << 17) |
			(mipi_reg->hs_codd << 16) |
			(mipi_reg->yuv420_fmt << 15) |
			(mipi_reg->ccs_data_format << 13) |
			(mipi_reg->yuv_to_rgb << 12) |
			(mipi_reg->chroma_ds_mode << 11) |
			(mipi_reg->chroma_ds_en << 10) |
			(mipi_reg->chroma_us_mode << 9) |
			(mipi_reg->chroma_us_en << 8) |
			(mipi_reg->hdmirx_interlace_en << 7) |
			(mipi_reg->hdmirx_interlace_polarity << 6) |
			(mipi_reg->int_en4 << 5) |
			(mipi_reg->int_en3 << 4) |
			(mipi_reg->int_en2 << 3) |
			(mipi_reg->int_en1 << 2) |
			(mipi_reg->int_en0 << 1) |
			(mipi_reg->en);

	hdmi_rx_reg_write32(MIPI, reg_val, HDMI_RX_MIPI);
	HDMIRX_INFO("Set MIPI=0x%08x", reg_val);
	HDMIRX_INFO("Read MIPI=0x%08x", hdmi_rx_reg_read32(MIPI, HDMI_RX_MIPI));
}

void set_enable_mipi(unsigned char enable)
{
	unsigned int reg_val;

	hdmi_rx_reg_mask32(MIPI,
		~(MIPI_int_en0_mask | MIPI_int_en1_mask | MIPI_int_en2_mask |
		MIPI_int_en3_mask | MIPI_int_en4_mask | MIPI_en_mask),
		MIPI_int_en0(enable) | MIPI_int_en1(enable) | MIPI_int_en2(enable) |
		MIPI_int_en3(enable) | MIPI_int_en4(enable) | MIPI_en(enable),
		HDMI_RX_MIPI);

	if (enable == 0) {
		reg_val = hdmi_rx_reg_read32(MIPI_INT_ST, HDMI_RX_MIPI);
		hdmi_rx_reg_write32(MIPI_INT_ST, reg_val, HDMI_RX_MIPI);
	}
}

void set_hs_scaler(unsigned int hsi_offset, unsigned int hsi_phase, unsigned int hsd_out, unsigned int hsd_delta)
{
	hdmi_rx_reg_write32(SCALER_HSI,
		SCALER_HSI_hsi_offset(hsi_offset) |
		SCALER_HSI_hsi_phase(hsi_phase), HDMI_RX_MIPI);

	hdmi_rx_reg_write32(SCALER_HSD,
		SCALER_HSD_hsd_out(hsd_out) |
		SCALER_HSD_hsd_delta(hsd_delta), HDMI_RX_MIPI);

	HDMIRX_INFO("hsd_out=0x%x,hsd_delta=0x%x", hsd_out, hsd_delta);
}

void set_hs_coeff(void)
{
	unsigned int reg_val;

	/* for Y */
	reg_val = (0x400<<16) | 0x400;
	hdmi_rx_reg_write32(SCALER_HSYNC0, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC1, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC2, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC3, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC4, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC5, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC6, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSYNC7, reg_val, HDMI_RX_MIPI);

	/* for U,V */
	hdmi_rx_reg_write32(SCALER_HSCC0, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC1, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC2, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC3, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC4, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC5, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC6, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_HSCC7, reg_val, HDMI_RX_MIPI);
}

void set_vs_scaler(unsigned int vsi_offset, unsigned int vsi_phase, unsigned int vsd_out, unsigned int vsd_delta)
{
	hdmi_rx_reg_write32(SCALER_VSI,
		SCALER_VSI_vsi_offset(vsi_offset) |
		SCALER_VSI_vsi_phase(vsi_phase), HDMI_RX_MIPI);

	hdmi_rx_reg_write32(SCALER_VSD,
		SCALER_VSD_vsd_out(vsd_out) |
		SCALER_VSD_vsd_delta(vsd_delta), HDMI_RX_MIPI);

	HDMIRX_INFO("vsd_out=0x%x,vsd_delta=0x%x\n", vsd_out, vsd_delta);
}

void set_vs_coeff(void)
{
	unsigned int reg_val;

	reg_val = (0x800<<16) | 0x800;
	hdmi_rx_reg_write32(SCALER_VSYC0, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSCC0, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSYC1, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSCC1, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSYC2, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSCC2, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSYC3, reg_val, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(SCALER_VSCC3, reg_val, HDMI_RX_MIPI);
}

void set_alpha(unsigned int alpha)
{

	hdmi_rx_reg_write32(CONSTANT_ALPHA, CONSTANT_ALPHA_alpha(alpha), HDMI_RX_MIPI);
}

void set_YUV2RGB_coeff(void)
{
	hdmi_rx_reg_write32(CS_TRANS0,  0x04a80, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS1,  0x00000, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS2,  0x072c0, HDMI_RX_MIPI);

	hdmi_rx_reg_write32(CS_TRANS3,  0x04a80, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS4,  0x1f260, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS5,  0x1ddd0, HDMI_RX_MIPI);

	hdmi_rx_reg_write32(CS_TRANS6,  0x04a80, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS7,  0x08760, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS8,  0x00000, HDMI_RX_MIPI);

	hdmi_rx_reg_write32(CS_TRANS9,  0x0fc20, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS10, 0x00134, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS11, 0x0fb7c, HDMI_RX_MIPI);
}

void set_RGB2YUV_coeff(void)
{
	/* C1~C3 */
	hdmi_rx_reg_write32(CS_TRANS0,	0x00BB8, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS1,	0x02748, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS2,	0x003F8, HDMI_RX_MIPI);
	/* C4~C6 */
	hdmi_rx_reg_write32(CS_TRANS3,	0x1F988, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS4,	0x1EA60, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS5,	0x01C18, HDMI_RX_MIPI);
	/* C7~C9 */
	hdmi_rx_reg_write32(CS_TRANS6,	0x01C18, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS7,	0x1E6E9, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS8,	0x1FD7B, HDMI_RX_MIPI);
	/* K1~K3 */
	hdmi_rx_reg_write32(CS_TRANS9,	0x00100, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS10, 0x00800, HDMI_RX_MIPI);
	hdmi_rx_reg_write32(CS_TRANS11, 0x00800, HDMI_RX_MIPI);
}

void mipi_scale_down(unsigned int src_width, unsigned int src_height,
	unsigned int dst_width, unsigned int dst_height)
{
	unsigned int delta_num, delta_den, offset, phase;

	if (src_width > dst_width) {
		/* set hs_scaler */
		offset = 0;
		phase = 0;
		delta_num = (src_width / dst_width) << 14;
		delta_den = ((src_width % dst_width)*0x4000) / dst_width;
		/* set_hs_scaler: offset,phase,out,delta */
		set_hs_scaler(offset, phase, dst_width, (delta_num | delta_den));
		set_hs_coeff();
	}

	if (src_height > dst_height) {
		/* set vs_scaler */
		offset = 0;
		phase = 0;
		delta_num = (src_height / dst_height) << 14;
		delta_den = ((src_height % dst_height)*0x4000) / dst_height;
		/* set_vs_scaler: offset,phase,out,delta */
		set_vs_scaler(offset, phase, dst_height, (delta_num | delta_den));
		set_vs_coeff();
	}
}

void setup_mipi(void)
{
	MIPI_REG mipi_reg;
	unsigned int v_input, h_input;

	HDMIRX_INFO("[%s]", __func__);

	set_mipi_env();
	set_mipi_type(0);/* 0:video, 1:pic */

	memset(&mipi_reg, 0, sizeof(MIPI_REG));

	mipi_reg.dst_fmt = mipi_top.output_color;
	mipi_reg.src_fmt = mipi_top.input_color;
	mipi_reg.src_sel = mipi_top.src_sel;
	mipi_reg.yuv420_uv_seq = mipi_top.uv_seq;

	if (!hdmi.tx_timing.progressive)/* Interlace */
		v_input = mipi_top.v_input_len*2;
	else
		v_input = mipi_top.v_input_len;

	h_input = mipi_top.h_input_len;

	if (v_input > mipi_top.v_output_len)
		mipi_reg.vs = 1;

	if (h_input > mipi_top.h_output_len)
		mipi_reg.hs = 1;

	if (mipi_reg.dst_fmt == OUT_10BIT_YUV422)
		mipi_reg.yuv420_fmt = 1;

	/* mipi_reg.ccs_data_format */

	if ((mipi_top.input_color != IN_RGB888) &&
		(mipi_top.output_color >= OUT_ARGB)) {
		/* YUV -> RGB */
		mipi_reg.yuv_to_rgb = 1;
		set_alpha(0xff);
		set_YUV2RGB_coeff();
	} else if ((mipi_top.input_color == IN_RGB888) &&
		(mipi_top.output_color <= OUT_10BIT_YUV420)) {
		/* RGB -> YUV */
		mipi_reg.chroma_ds_mode = 1;/* 0:drop 1:avg */
		mipi_reg.chroma_ds_en = 1;
		mipi_reg.yuv_to_rgb = 1;
		set_RGB2YUV_coeff();
	}

	if ((mipi_top.input_color == IN_YUV444) &&
		(mipi_top.output_color <= OUT_10BIT_YUV420)) {
		mipi_reg.chroma_ds_mode = 1;/* 0:drop 1:avg */
		mipi_reg.chroma_ds_en = 1;
	}

	if ((mipi_top.input_color == IN_YUV422) && (mipi_reg.vs || mipi_reg.hs)) {
		mipi_reg.chroma_us_mode = 0;/* 0:repeat 1:avg */
		mipi_reg.chroma_us_en = 1;
		if (mipi_top.output_color <= OUT_10BIT_YUV420) {
			mipi_reg.chroma_ds_mode = 1;/* 0:drop 1:avg */
			mipi_reg.chroma_ds_en = 1;
		}
	}

	mipi_reg.hdmirx_interlace_en = (!hdmi.tx_timing.progressive);
	/* Set polarity: 0 - Button field first, 1 - Top field first */
	mipi_reg.hdmirx_interlace_polarity = 1;

	mipi_reg.int_en4 = 1;
	mipi_reg.int_en3 = 1;
	mipi_reg.int_en2 = 1;
	mipi_reg.int_en1 = 1;
	mipi_reg.int_en0 = 1;

	mipi_reg.en = 1;

	set_video_dest_size(mipi_top.h_output_len, mipi_top.pitch);
	set_video_src_size(mipi_top.h_input_len);

	mipi_scale_down(h_input, v_input,
		mipi_top.h_output_len, mipi_top.v_output_len);

	hdmi_rx_reg_write32(MIPI_DPHY_REG11,
		MIPI_DPHY_REG11_Esc_lane3_int_flg(1) |
		MIPI_DPHY_REG11_Esc_lane2_int_flg(1) |
		MIPI_DPHY_REG11_Esc_lane1_int_flg(1) |
		MIPI_DPHY_REG11_Esc_lane0_int_flg(1)|
		MIPI_DPHY_REG11_Clk_ulps_int_flg(1)|
		MIPI_DPHY_REG11_Crc16_err_int_flg(1)|
		MIPI_DPHY_REG11_Ecc_crt_int_flg(1)|
		MIPI_DPHY_REG11_Ecc_err_int_flg(1), HDMI_RX_MIPI_PHY);

	set_init_mipi_value(&mipi_reg);
	set_hdmirx_wrapper_control_0(-1, 1, mipi_reg.hdmirx_interlace_en, mipi_reg.hdmirx_interlace_polarity, -1, -1);
	mipi_top.mipi_init = 1;
}

void update_mipi_hw_buffer(int src_index, struct v4l2_hdmi_dev *dev, int buffer_empty)
{
	unsigned long flags;
	unsigned int addry;
	unsigned int addruv;
	unsigned int offset;
	struct hdmi_dmaqueue *hdmidq = &dev->hdmidq;

	offset = roundup16(mipi_top.pitch) * roundup16(mipi_top.v_output_len);

	spin_lock_irqsave(&dev->slock, flags);

	if (hdmidq->skip_frame[src_index] == 0) {
		vb2_buffer_done(&hdmidq->hwbuf[src_index]->vb, VB2_BUF_STATE_DONE);
		atomic_inc(&hdmidq->rcnt);
	}

	if (buffer_empty == 0) {
		hdmidq->hwbuf[src_index] = list_entry(hdmidq->active.next, struct hdmi_buffer, list);
		list_del(&hdmidq->hwbuf[src_index]->list);
		atomic_dec(&hdmidq->qcnt);
		hdmidq->skip_frame[src_index] = 0;

		addry = hdmidq->hwbuf[src_index]->phys;
		addruv = hdmidq->hwbuf[src_index]->phys + offset;
	} else {
		addry = dev->ion_buf.phys_addr;
		addruv = dev->ion_buf.phys_addr + offset;
		hdmidq->skip_frame[src_index] = 1;
		hdmidq->hwbuf[src_index] = NULL;
	}

	spin_unlock_irqrestore(&dev->slock, flags);

	if (src_index == 0)
		set_video_dest_addr(addry, addruv, -1, -1);
	else
		set_video_dest_addr(-1, -1, addry, addruv);
}

void hdmi_hw_buf_update(int src_index, struct v4l2_hdmi_dev *dev)
{
	static int skip_num = 0;
	static int total_num = 0;
	static unsigned long prev_jif = 0;
	unsigned long flags;
	int empty;
	struct hdmi_dmaqueue *hdmidq = &dev->hdmidq;

	if ((mipi_top.src_sel == 1) &&
		(Hdmi_CheckConditionChange() != HDMI_ERR_NO)) {

		HDMIRX_INFO("Condition change, restart detection");
		restartHdmiRxWrapperDetection();
		return;
	}

	if (mipi_top.mipi_init == 0)
		return;

	if (unlikely((jiffies - prev_jif) >= (10 * HZ))) {
		HDMIRX_INFO("skip %d/%d in %lu jiffies\n",
			skip_num, total_num, jiffies - prev_jif);
		prev_jif = jiffies;
		total_num = 0;
		skip_num = 0;
	}
	total_num++;

	spin_lock_irqsave(&dev->slock, flags);
	empty = list_empty(&hdmidq->active);
	spin_unlock_irqrestore(&dev->slock, flags);

	if (empty)
		skip_num++;

	update_mipi_hw_buffer(src_index, dev, empty);
}

irqreturn_t hdmirx_mipi_isr(int irq, void *dev_id)
{
	unsigned int st_reg_val;
	unsigned int reg_val;
	struct v4l2_hdmi_dev *dev = dev_id;

	hdmirx_wrapper_isr();

#ifdef CONFIG_RTK_HDCP1x_REPEATER
	/* Get TX write Aksv */
	if (HDCP_FLAG1_get_wr_aksv_flag(hdmi_rx_reg_read32(HDCP_FLAG1, HDMI_RX_MAC))) {
		/* Disable AKSV interrupt */
		hdmi_rx_reg_mask32(HDCP_FLAG2, ~HDCP_FLAG2_irq_aksv_en_mask,
			0, HDMI_RX_MAC);
		/* Clear Aksv flag */
		hdmi_rx_reg_write32(HDCP_FLAG1, HDCP_FLAG1_wr_aksv_flag_mask, HDMI_RX_MAC);
		/* Clear HDCP interrupt */
		hdmi_rx_reg_write32(HDMI_INTCR, HDMI_INTCR_pending_mask, HDMI_RX_MAC);
		start_hdcp1x_repeater_work();
	}
#endif

#ifdef CONFIG_RTK_HDCPRX_2P2
	Hdmi_HDCP_2_2_msg_hander();

	/* Return isr if dma not enabled */
	if (!HDMIRX_WRAPPER_CONTROL_0_get_fw_dma_en(hdmi_rx_reg_read32(HDMIRX_WRAPPER_CONTROL_0, HDMI_RX_HDMI_WRAPPER)))
		return IRQ_HANDLED;
#endif

	st_reg_val = hdmi_rx_reg_read32(MIPI_INT_ST, HDMI_RX_MIPI);

	if (st_reg_val & 0x30) {
		/* Clear interrupt status */
		hdmi_rx_reg_write32(MIPI_INT_ST, st_reg_val, HDMI_RX_MIPI);

		HDMIRX_INFO("MIPI frame dropped");

		return IRQ_HANDLED;
	}

	reg_val = hdmi_rx_reg_read32(MIPI_TYPE, HDMI_RX_MIPI);
	if (unlikely(reg_val & 0x01)) {
		/* Picture mode */
		if (st_reg_val & MIPI_INT_ST_fm_done2_mask)
			hdmi_rx_reg_write32(MIPI_INT_ST, st_reg_val, HDMI_RX_MIPI);
	} else {
		/* Preview or video mode */
		if (st_reg_val & MIPI_INT_ST_fm_done0_mask)
			hdmi_hw_buf_update(0, dev);
		else if (st_reg_val & MIPI_INT_ST_fm_done1_mask)
			hdmi_hw_buf_update(1, dev);

		/* Clear interrupt status */
		hdmi_rx_reg_write32(MIPI_INT_ST, st_reg_val, HDMI_RX_MIPI);
	}

	return IRQ_HANDLED;
}

