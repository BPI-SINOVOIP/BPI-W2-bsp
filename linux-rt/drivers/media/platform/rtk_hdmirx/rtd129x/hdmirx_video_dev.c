/*
 * hdmirx_video_dev.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "hdmirx_video_dev.h"

#include "v4l2_hdmi_dev.h"
#include "hdmirx_video_dev.h"
#include "hdmirx_wrapper.h"
#include "mipi_wrapper.h"
#include "hdmirx_reg.h"

#include "rx_drv/hdmiInternal.h"
#include "rx_drv/hdmiEDID.h"

#define HDMI_MEASURE_RETRY_TIMES 10

int hdmi_stream_on = 0;
int hdmi_timestamp_mode = 0;/* 0:system time, 1:90KHz timer */

struct hdmirx_format_desc {
	char *name;
	__u32 fcc;
};
const struct hdmirx_format_desc hdmi_rx_fmts[] = {
	{
		.name		= "RAW8",
		.fcc		= V4L2_PIX_FMT_SGRBG8,
	},
	{
		.name		= "RAW10",
		.fcc		= V4L2_PIX_FMT_SGRBG10,
	},
	{
		.name		= "Y/CbCr 4:2:2",
		.fcc		= V4L2_PIX_FMT_NV16,
	},
	{
		.name		= "YUV 4:2:0 (NV12)",
		.fcc		= V4L2_PIX_FMT_NV12,
	},
	{
		.name		= "YUV 4:2:0 (NV21)",
		.fcc		= V4L2_PIX_FMT_NV21,
	},
	{
		.name		= "ARGB",
		.fcc		= V4L2_PIX_FMT_RGB32,
	},
	{
		.name		= "BGRA",
		.fcc		= V4L2_PIX_FMT_BGR32,
	}
};
#define V4L2_HDMI_RX_SUPPORT_FMT_NUM  (sizeof(hdmi_rx_fmts)/sizeof(struct hdmirx_format_desc))

/*=================== extern Variable/Function ===================*/
extern MIPI_TOP_INFO mipi_top;
extern HDMI_INFO_T hdmi;
extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;

extern char Hdmi_IsbReady(void);
extern int Hdmi_get_b_value(void);
extern unsigned int rx_pitch_measurement(unsigned int output_h, MIPI_OUT_COLOR_SPACE_T output_color);
extern void HdmiRx_enable_hdcp(unsigned char *bksv, unsigned char *device_key);
#ifdef CONFIG_RTK_HDCPRX_2P2
extern void HdmiRx_enable_hdcp2p2(unsigned char *key);
#endif
#if HDMI_REPEATER_SUPPORT
void Set_Hdmi_repeater_mode(int enable);
#endif
/*======================================================*/

MIPI_OUT_COLOR_SPACE_T V4L2_format_parse(unsigned int pixelformat)
{
	MIPI_OUT_COLOR_SPACE_T output_color;

	switch (pixelformat) {
	case V4L2_PIX_FMT_NV12:
		mipi_top.uv_seq = UV_NV12;
		output_color = OUT_8BIT_YUV420;
		break;
	case V4L2_PIX_FMT_NV21:
		/* main */
		mipi_top.uv_seq = UV_NV21;
		output_color = OUT_8BIT_YUV420;
		break;
#if 0
	case V4L2_PIX_FMT_RGB32:
		output_color = OUT_BGRA;// byte 0~3: ARGB
		break;
#endif
	case V4L2_PIX_FMT_BGR32:
		/* byte 0~3: BGRA, for HAL_PIXEL_FORMAT_BGRA_8888 */
		output_color = OUT_ARGB;
		break;
	case V4L2_PIX_FMT_NV16:
		output_color = OUT_8BIT_YUV422;
		break;
	default:
		/* FCC2ASCII */
		HDMIRX_ERROR("Unsupported pixel format: %c%c%c%c",
			((char *)(&pixelformat))[0], ((char *)(&pixelformat))[1],
			((char *)(&pixelformat))[2], ((char *)(&pixelformat))[3]);
		output_color = OUT_UNKNOW;
		break;
	}

	return  output_color;
}

int out_color_to_bpp(MIPI_OUT_COLOR_SPACE_T output_color)
{
	int bpp;

	switch (output_color) {
	case OUT_8BIT_YUV420:
		/* V4L2_PIX_FMT_NV12, V4L2_PIX_FMT_NV21 */
		bpp = 12;
		break;
	case OUT_ARGB:
		/* V4L2_PIX_FMT_BGR32 */
		bpp = 32;
		break;
	case OUT_10BIT_YUV422:
		bpp = 32;
		break;
	default:
		/* all other ARGB formats */
		bpp = 32;
		break;
	}

	return bpp;
}

static long v4l2_hdmi_do_ioctl(struct file *file, unsigned int cmd, void *arg)
{
	long ret = 0;
	struct video_device *vdev = video_devdata(file);
	struct v4l2_hdmi_dev *dev = video_drvdata(file);

	/* HDMIRX_DEBUG(" ioctl TYPE(0x%x) NR(%u) SIZE(%u)",  _IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd)); */

	switch (cmd) {
	case VIDIOC_QUERYCAP:
	{
		struct v4l2_capability *cap = arg;

		/* HDMIRX_INFO(" ioctl VIDIOC_QUERYCAP"); */
		memset(cap, 0, sizeof(*cap));

		strlcpy(cap->driver, "v4l2_mipi_top", sizeof(cap->driver));
		strlcpy(cap->card, vdev->name, sizeof(cap->card));

		cap->version = LINUX_VERSION_CODE;
		cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
		break;
	}
	case VIDIOC_CROPCAP:
	{
		struct v4l2_cropcap *ccap = arg;

		ccap->bounds.left = 0;
		ccap->bounds.top = 0;

		ccap->bounds.width = 4096;
		ccap->bounds.height = 2160;

		ccap->defrect = ccap->bounds;

		ccap->pixelaspect.numerator = 1;
		ccap->pixelaspect.denominator = 1;
		break;
	}
	case VIDIOC_G_CROP:
	case VIDIOC_S_CROP:
		ret = -EINVAL;
		break;
	case VIDIOC_ENUM_FMT:
	{
		struct v4l2_fmtdesc *fmt = arg;
		struct hdmirx_format_desc *format;
		enum v4l2_buf_type type = fmt->type;
		__u32 index = fmt->index;

		/* HDMIRX_INFO(" ioctl VIDIOC_ENUM_FMT"); */
		memset(fmt, 0, sizeof(*fmt));
		fmt->index = index;
		fmt->type = type;

		if (fmt->index >= V4L2_HDMI_RX_SUPPORT_FMT_NUM) {
			ret = -EINVAL;
			goto exit;
		}

		format = &hdmi_rx_fmts[fmt->index];
		fmt->flags = V4L2_FMT_FLAG_COMPRESSED;

		strlcpy(fmt->description, format->name, sizeof(fmt->description));
		fmt->description[sizeof(fmt->description) - 1] = 0;

		fmt->pixelformat = format->fcc;
		break;
	}
	case VIDIOC_ENUM_FRAMESIZES:
	{
		struct v4l2_frmsizeenum *fsize = arg;
		int v_len;

		/* HDMIRX_INFO(" ioctl VIDIOC_ENUM_FRAMESIZES"); */
		/* Look for the given pixel format */
		if (((hdmi_ioctl_struct.measure_ready == 0) && (mipi_top.src_sel == 1)) ||
			(fsize->index != 0)) {
			ret = -EINVAL;
			goto exit;
		}

		if (!hdmi.tx_timing.progressive)
			v_len = mipi_top.v_input_len << 1;
		else
			v_len = mipi_top.v_input_len;

		fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
		fsize->stepwise.min_width = (mipi_top.h_input_len)/32;
		fsize->stepwise.max_width = mipi_top.h_input_len;
		fsize->stepwise.step_width = 1;
		fsize->stepwise.min_height = v_len/32;
		fsize->stepwise.max_height = v_len;
		fsize->stepwise.step_height = 1;
		HDMIRX_INFO("Act_hor:%u, Act_ver:%u", mipi_top.h_input_len, mipi_top.v_input_len);
		break;
	}
	case VIDIOC_ENUM_FRAMEINTERVALS:
	{
		struct v4l2_frmivalenum *fival = arg;

		if (fival->index != 0) {
			ret = -EINVAL;
			goto exit;
		}

		fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
		fival->discrete.numerator = 1;
		if (mipi_top.src_sel == 1) {
			unsigned int vic;

			vic = drvif_Hdmi_AVI_VIC();
			if (hdmi_vic_table[vic].interlace)
				fival->discrete.denominator = hdmi_vic_table[vic].fps/2;
			else
				fival->discrete.denominator = hdmi_vic_table[vic].fps;
		} else {
				fival->discrete.denominator = 60;
		}
		break;
	}
	case VIDIOC_S_FMT:
	{
		struct v4l2_format *fmt = arg;
		int v_len;

		dev->width = fmt->fmt.pix.width;
		dev->height = fmt->fmt.pix.height;
		dev->outfmt = V4L2_format_parse(fmt->fmt.pix.pixelformat);
		dev->bpp = out_color_to_bpp(dev->outfmt);
		HDMIRX_INFO(" ioctl VIDIOC_S_FMT,%dx%d,color=0x%x",
			fmt->fmt.pix.width, fmt->fmt.pix.height, dev->outfmt);

		if (!hdmi.tx_timing.progressive)
			v_len = mipi_top.v_input_len << 1;
		else
			v_len = mipi_top.v_input_len;

		mipi_top.h_output_len = fmt->fmt.pix.width;
		mipi_top.v_output_len = fmt->fmt.pix.height;
		mipi_top.output_color = dev->outfmt;
		mipi_top.pitch = rx_pitch_measurement(mipi_top.h_output_len, mipi_top.output_color);

		mipi_top.mipi_init = 0;
		if ((v_len) && (v_len < mipi_top.v_output_len)) {
			HDMIRX_ERROR("[v_size error :%d<%d]", v_len, mipi_top.v_output_len);
			ret = -EINVAL;
			goto exit;
		}

		if ((mipi_top.h_input_len) && (mipi_top.h_input_len < mipi_top.v_output_len)) {
			HDMIRX_ERROR("[h_size error :%d<%d]",
				mipi_top.h_input_len, mipi_top.v_output_len);
			ret = -EINVAL;
			goto exit;
		}

		HDMIRX_INFO(" ioctl VIDIOC_S_FMT,output v(%u) h(%u) color(%u) pitch(%u)",
			mipi_top.h_output_len, mipi_top.v_output_len,
			mipi_top.output_color, mipi_top.pitch);
		break;
	}
	case VIDIOC_S_PARM:
		/* Set USB camera frame rate, unused in RX */

		/* HDMIRX_INFO("Not support fps change"); */
		break;
	case VIDIOC_REQBUFS:
	{
		/* Buffers & streaming */
		struct vb2_queue *vq;
		struct v4l2_requestbuffers *rb = (struct v4l2_requestbuffers *)arg;

		HDMIRX_INFO(" ioctl VIDIOC_REQBUFS count=%d, type=%d, memory=%d",
			rb->count, rb->type, rb->memory);

		/* Initialize queue */
		vq = &dev->vb_hdmidq;
		ret = hdmirx_queue_init(dev, vq, rb->memory);
		if (ret) {
			HDMIRX_ERROR("hdmirx_queue_init failed: %ld", ret);
			goto exit;
		}

		ret = vb2_reqbufs(vq, rb);
		if (ret) {
			HDMIRX_ERROR("vb2_reqbufs failed: %ld", ret);
			goto exit;
		}
		break;
	}
	case VIDIOC_QUERYBUF:
	{
		struct v4l2_buffer *buf = arg;

		/*
		 * HDMIRX_INFO(" ioctl VIDIOC_QUERYBUF index(%u) type(%u) length(%u)",
		 *	buf->index,buf->type,buf->length);
		 */
		ret = vb2_querybuf(&dev->vb_hdmidq, buf);

		if (ret < 0)
			HDMIRX_ERROR(" ioctl VIDIOC_QUERYBUF fail");
		break;
	}
	case VIDIOC_QBUF:
	{
		struct v4l2_buffer *buf = arg;

		/* HDMIRX_INFO(" ioctl VIDIOC_QBUF"); */

		ret = vb2_qbuf(&dev->vb_hdmidq, buf);

		if (ret < 0)
			HDMIRX_ERROR(" ioctl VIDIOC_QBUF fail");
		break;
	}
	case VIDIOC_DQBUF:
	{
		struct v4l2_buffer *buf = arg;

		/*HDMIRX_INFO(" ioctl VIDIOC_DQBUF"); */

		ret = vb2_dqbuf(&dev->vb_hdmidq, buf, file->f_flags & O_NONBLOCK);
		if (ret == 0)
			atomic_dec(&dev->hdmidq.rcnt);

		/* Avoid userspace seeing broken frames on hotplug or switching tv system */
		if (unlikely(ret == 0 && hdmi_stream_on == 0))
			ret = -EINVAL;

		break;
	}
	case VIDIOC_STREAMON:
	{
		HDMIRX_INFO(" ioctl VIDIOC_STREAMON");

		vb2_streamon(&dev->vb_hdmidq, dev->vb_hdmidq.type);

		break;
	}
	case VIDIOC_STREAMOFF:
	{
		struct vb2_queue *vq;

		HDMIRX_INFO(" ioctl VIDIOC_STREAMOFF");

		vb2_streamoff(&dev->vb_hdmidq, dev->vb_hdmidq.type);

		/* Release queue */
		vq = &dev->vb_hdmidq;
		vb2_queue_release(vq);

		hdmi_timestamp_mode = 0;

		break;
	}
	case VIDIOC_QUERY_MIPI_IN_TYPE:
	{
		struct v4l2_mipi_in_type *in_type = arg;

		/* HDMIRX_INFO(" ioctl VIDIOC_MIPI_IN_TYPE"); */

		in_type->input_type = mipi_top.src_sel;
		break;
	}
	case VIDIOC_SET_MIPI_IN_TYPE:
		/* HDMIRX_INFO(" ioctl VIDIOC_SET_MIPI_IN_TYPE"); */

		break;
	case VIDIOC_ENABLE_RX_HDCP:
	{
		struct rx_hdcp_key *rx_key;

		HDMIRX_INFO("ioctl VIDIOC_ENABLE_RX_HDCP\n");

#ifndef CONFIG_RTK_HDCP_1x
		HDMIRX_ERROR("Enable HDCP fail because HDCP TX is disabled");
		break;
#endif

		rx_key = arg;

#ifdef CONFIG_RTK_HDCPRX_2P2
		HdmiRx_enable_hdcp2p2(rx_key->licensed);
#endif
		if ((rx_key->ksv[0] == 0) && (rx_key->ksv[1] == 0) &&
			(rx_key->ksv[2] == 0) && (rx_key->ksv[3] == 0) &&
			(rx_key->ksv[4] == 0))
			HDMIRX_INFO("[HDCP1.4] Empty key, should be TEE case");

		HdmiRx_enable_hdcp(rx_key->ksv, rx_key->private_key);
		break;
	}
	case VIDIOC_SET_TIMESTAMP_MODE:
	{
		int *mode = arg;

		HDMIRX_INFO("ioctl VIDIOC_SET_TIMESTAMP_MODE\n");

		hdmi_timestamp_mode = (int)*mode;

		break;
	}
#if HDMI_REPEATER_SUPPORT
	case VIDIOC_SET_REPEATER_MODE:
	{
		int *repeater_mode = arg;

		HDMIRX_INFO("ioctl VIDIOC_SET_REPEATER_MODE\n");

		Set_Hdmi_repeater_mode((int)*repeater_mode);

		break;
	}
#endif
	case VIDIOC_SET_EDID_TABLE:
	{
		/* EDID 256Bytes */
		HDMIRX_INFO("ioctl VIDIOC_SET_EDID_TABLE\n");

		HdmiRx_ChangeCurrentEDID(arg);

		break;
	}
	default:
		HDMIRX_ERROR("Unknown ioctl TYPE(0x%x) NR(%u) SIZE(%u)",
			_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));
		ret = -ENOTTY;
		break;
	}

exit:
	return ret;
}

long v4l2_hdmi_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	if (0) {
		pr_info("v4l2_hdmi_ioctl(");
		v4l_printk_ioctl(NULL, cmd);
		pr_info(")\n");
	}
	HDMIRX_DEBUG(" ioctl TYPE(0x%x) NR(%u) SIZE(%u)",
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));
	ret = video_usercopy(file, cmd, arg, v4l2_hdmi_do_ioctl);
	HDMIRX_DEBUG(" return ioctl TYPE(0x%x) NR(%u) SIZE(%u)",
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));
	return ret;
}

long compat_v4l2_hdmi_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret_val;
	struct compat_v4l2_buffer *c_buf;
	struct v4l2_buffer buf;

	if (!file->f_op->unlocked_ioctl) {
		ret_val = -ENOTTY;
		goto exit;
	}

	switch (cmd) {
	case VIDIOC_QUERYBUF:
	case VIDIOC_QBUF:
	case VIDIOC_DQBUF:
		memset(&buf, 0, sizeof(buf));
		c_buf = (void __user *)(unsigned long)compat_ptr(arg);
		buf.index = c_buf->index;
		buf.type = c_buf->type;
		buf.bytesused = c_buf->bytesused;
		buf.flags = c_buf->flags;
		buf.field = c_buf->field;

		if (copy_from_user(&buf.timestamp, &c_buf->timestamp, sizeof(c_buf->timestamp)))
			HDMIRX_ERROR("copy_from_user fail");

		if (copy_from_user(&buf.timecode, &c_buf->timecode, sizeof(c_buf->timecode)))
			HDMIRX_ERROR("copy_from_user fail");

		buf.m.offset = c_buf->compat_m.offset;
		buf.m.userptr = (unsigned long)compat_ptr(c_buf->compat_m.userptr);
		buf.m.fd = c_buf->compat_m.fd;
		buf.length = c_buf->length;
		buf.reserved2 = c_buf->reserved2;
		buf.reserved = c_buf->reserved;
		ret_val = v4l2_hdmi_do_ioctl(file, cmd, &buf);
		break;
	default:
		ret_val = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;
	}

exit:
	return ret_val;
}

int v4l2_mipi_top_open(struct file *filp)
{
	struct video_device *vdev = video_devdata(filp);
	struct v4l2_fh *fh = kzalloc(sizeof(*fh), GFP_KERNEL);

	filp->private_data = fh;
	if (fh == NULL)
		return -ENOMEM;
	v4l2_fh_init(fh, vdev);
	v4l2_fh_add(fh);

	return 0;
}

static ssize_t show_hdmirx_bufcnt(struct device *cd, struct device_attribute *attr, char *buf)
{
	struct video_device *vfd = container_of(cd, struct video_device, dev);
	struct v4l2_hdmi_dev *dev = (struct v4l2_hdmi_dev *)video_get_drvdata(vfd);
	struct hdmi_dmaqueue *hdmidq = &dev->hdmidq;

	return sprintf(buf, "qcnt:%d rcnt:%d\n", atomic_read(&hdmidq->qcnt), atomic_read(&hdmidq->rcnt));
}

static const char * const type[] = {"MIPI", "HDMIRx"};
static const char * const status[] = {"NotReady", "Ready"};
static const char * const color[] = {"RGB", "YUV444", "YUV422"};
static const char * const sm[] = {"Interlaced", "Progressive"};
static ssize_t show_hdmirx_video_info(struct device *cd, struct device_attribute *attr, char *buf)
{
	ssize_t ret_count;
	unsigned char type_index, status_index, mode_index, color_index;
	unsigned int width = 0, height = 0, vic = 0, fps = 0;

	type_index = mipi_top.src_sel&0x1;
	status_index = hdmi_ioctl_struct.measure_ready&0x1;
	width = mipi_top.h_input_len;
	height = mipi_top.v_input_len;
	mode_index = hdmi.tx_timing.progressive&0x1;
	color_index = mipi_top.input_color&0x3;

	if (mode_index == 0) /* interlaced mode */
		height *= 2;

	if (hdmi_ioctl_struct.measure_ready)
		vic = drvif_Hdmi_AVI_VIC();
	else
		vic = 0;

	fps = hdmi_vic_table[vic].fps;


	ret_count = sprintf(buf, "Type:%s\nStatus:%s\nWidth:%u\nHeight:%u\nScanMode:%s\nColor:%s\nFps:%u\n",
		type[type_index], status[status_index],
		width, height, sm[mode_index], color[color_index], fps);

	return ret_count;
}

static const char * const lpcm[] = {"LPCM", "Non-LPCM", "N/A"};
static ssize_t show_hdmirx_audio_info(struct device *cd,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count;
	unsigned int audio_ready = 0, freq = 0, lpcm_index = 2;

	audio_ready = hdmi_ioctl_struct.audio_detect_done;

	if (audio_ready) {
		freq = hdmi.audio_freq;
		lpcm_index = hdmi.spdif_type&0x1;
	}

	ret_count = sprintf(buf, "Ready:%u\n", audio_ready);

	ret_count += sprintf(buf+ret_count, "Freq:%u\n", freq);
	ret_count += sprintf(buf+ret_count, "SPDIF Type:%s\n", lpcm[lpcm_index]);

	return ret_count;
}

/* /sys/class/video4linux/video250/hdmirx_bufcnt */
static DEVICE_ATTR(hdmirx_bufcnt, 0444, show_hdmirx_bufcnt, NULL);
/* /sys/class/video4linux/video250/hdmirx_video_info */
static DEVICE_ATTR(hdmirx_video_info, 0444, show_hdmirx_video_info, NULL);
/* /sys/class/video4linux/video250/hdmirx_audio_info */
static DEVICE_ATTR(hdmirx_audio_info, 0444, show_hdmirx_audio_info, NULL);

int register_video_device(struct v4l2_hdmi_dev *hdmi_dev)
{
	int ret;
	struct video_device *video_dev;

	HDMIRX_INFO("[%s]", __func__);

	video_dev = &hdmi_dev->vdev;
	*video_dev = hdmi_template;
	video_dev->v4l2_dev = &hdmi_dev->v4l2_dev;
	video_dev->queue = &hdmi_dev->vb_hdmidq;

	dma_set_coherent_mask(&video_dev->dev, DMA_BIT_MASK(32));
	/*
	 * Provide a mutex to v4l2 core. It will be used to protect
	 * all fops and v4l2 ioctls.
	 */
	video_dev->lock = &hdmi_dev->mutex;
	video_set_drvdata(video_dev, hdmi_dev);
	ret = video_register_device(video_dev, VFL_TYPE_GRABBER, 250);
	if (ret < 0)
		return ret;

	ret = device_create_file(&video_dev->dev, &dev_attr_hdmirx_bufcnt);
	if (ret < 0)
		goto unreg_vdev;
	ret = device_create_file(&video_dev->dev, &dev_attr_hdmirx_video_info);
	if (ret < 0)
		goto unreg_vdev;
	ret = device_create_file(&video_dev->dev, &dev_attr_hdmirx_audio_info);
	if (ret < 0)
		goto unreg_vdev;

	return 0;

unreg_vdev:
	video_unregister_device(video_dev);
	return ret;
}

