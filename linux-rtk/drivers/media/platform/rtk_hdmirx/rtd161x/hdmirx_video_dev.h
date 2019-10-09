/*
 * hdmirx_video_dev.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _HDMIRX_VIDEO_DEV_H_
#define _HDMIRX_VIDEO_DEV_H_


#include "v4l2_hdmi_dev.h"

long v4l2_hdmi_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
long compat_v4l2_hdmi_ioctl(struct file *file, unsigned int cmd, unsigned long arg);
int v4l2_mipi_top_open(struct file *filp);

struct compat_v4l2_plane {
	__u32			bytesused;
	__u32			length;
	union {
		__u32		mem_offset;
		__u32		userptr;
		__s32		fd;
	} m;
	__u32			data_offset;
	__u32			reserved[11];
};

struct compat_v4l2_buffer {
	__u32			index;
	__u32			type;
	__u32			bytesused;
	__u32			flags;
	__u32			field;
	struct timeval		timestamp;
	struct v4l2_timecode	timecode;
	__u32			sequence;

	/* memory location */
	__u32			memory;
	union {
		__u32           offset;
		__u32			userptr;
		struct compat_v4l2_plane *planes;
		__s32		fd;
	} compat_m;
	__u32			length;
	__u32			reserved2;
	__u32			reserved;
};

static const struct v4l2_file_operations hdmi_fops = {
	.owner			= THIS_MODULE,
	.open			= v4l2_mipi_top_open,
	.release		= vb2_fop_release,
	.read			= vb2_fop_read,
	.poll			= vb2_fop_poll,
	.unlocked_ioctl = v4l2_hdmi_ioctl, /* V4L2 ioctl handler */
	.compat_ioctl32	= compat_v4l2_hdmi_ioctl,
	.mmap			= vb2_fop_mmap,
};

static const struct video_device hdmi_template = {
	.name		= "v4l2_mipi_top",
	.fops		= &hdmi_fops,
	.release	= video_device_release_empty,
};

int register_video_device(struct v4l2_hdmi_dev *hdmi_dev);

#endif/* _HDMIRX_VIDEO_DEV_H_ */
