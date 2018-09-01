/*
 * v4l2_hdmi_dev.h - RTK hdmi rx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef V4L2_HDMI_DEV_H
#define V4L2_HDMI_DEV_H

#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/font.h>
#include <linux/mutex.h>
#include <linux/videodev2.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/dma-contiguous.h>
#include <linux/device.h>
#include <linux/fb.h>
#include <linux/switch.h>

#include <media/videobuf2-vmalloc.h>
#include <media/videobuf2-dma-contig.h>
#include <media/videobuf2-core.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-event.h>
#include <media/v4l2-common.h>
#include <media/videobuf2-memops.h>

#include <asm/page.h>
#include <asm/memory.h>

#include "ion/ion.h"
#include "uapi/ion.h"
#include "uapi/ion_rtk.h"


#define __RTK_HDMI_RX_DEBUG__	0

#if __RTK_HDMI_RX_DEBUG__
#define HDMIRX_DEBUG(format, ...) pr_err("[HDMI RX DBG]" format "\n", ## __VA_ARGS__)
#else
#define HDMIRX_DEBUG(format, ...)
#endif

#define HDMIRX_ERROR(format, ...) printk(KERN_ERR "[HDMI RX ERR]" format "\n", ## __VA_ARGS__)
#define HDMIRX_INFO(format, ...) printk(KERN_WARNING "[HDMI RX]" format "\n", ## __VA_ARGS__)


#define roundup16(x)	roundup(x, 16)


/* buffer for one video frame */
struct hdmi_buffer {
	/* common vb2_v4l2_buffer stuff -- must be first */
	struct vb2_buffer vb;
	__u32 flags;
	__u32 field;
	struct v4l2_timecode timecode;
	__u32 sequence;
	/* Private data */
	u32		phys;
	struct list_head	list;
};

struct hdmi_dmaqueue {
	atomic_t			rcnt;/* Number of buffers already processed by hw */
	atomic_t			qcnt;/* Number of buffers waiting for hw process */
	struct list_head	active;
	struct hdmi_buffer	*hwbuf[2];
	unsigned char skip_frame[2];
};

struct mipi_ion_buf {
	struct ion_client *client;
	struct ion_handle *handle;
	ion_phys_addr_t phys_addr;
};

struct v4l2_hdmi_dev {
	struct v4l2_device		v4l2_dev;
	struct video_device		vdev;
	struct switch_dev		sdev;/* Video switch device */
	struct switch_dev		asdev;/* Audio switch device */
	struct switch_dev		hsdev;/* HDCP switch device */

	spinlock_t		slock;
	struct mutex	mutex; /* Protects queue */

	struct hdmi_dmaqueue	   hdmidq;

	/* video capture */
	unsigned int		   width;
	unsigned int		   height;
	unsigned int		   outfmt;
	unsigned int		   bpp;
	struct vb2_queue	   vb_hdmidq;

	struct mipi_ion_buf ion_buf;
};

int hdmi_queue_setup(struct vb2_queue *vq,
		unsigned int *nbuffers, unsigned int *nplanes,
		unsigned int sizes[], struct device *alloc_devs[]);
int hdmi_buffer_prepare(struct vb2_buffer *vb);
void hdmi_buffer_finish(struct vb2_buffer *vb);
void hdmi_buffer_queue(struct vb2_buffer *vb);
int hdmi_start_streaming(struct vb2_queue *vq, unsigned int count);
void hdmi_stop_streaming(struct vb2_queue *vq);
void hdmi_unlock(struct vb2_queue *vq);
void hdmi_lock(struct vb2_queue *vq);

static const struct vb2_ops hdmi_qops = {
	.queue_setup     = hdmi_queue_setup,
	.buf_prepare     = hdmi_buffer_prepare,
	.buf_finish      = hdmi_buffer_finish,
	.buf_queue       = hdmi_buffer_queue,
	.start_streaming = hdmi_start_streaming,
	.stop_streaming  = hdmi_stop_streaming,
	.wait_prepare    = hdmi_unlock,
	.wait_finish     = hdmi_lock,
};

struct mipi_vb2_vmalloc_buf {
	void *vaddr;
	struct page **pages;
	struct vm_area_struct *vma;
	int write;
	u32 size;
	unsigned int n_pages;
	atomic_t refcount;
	struct vb2_vmarea_handler handler;
	struct dma_buf *dbuf;
};

int hdmirx_queue_init(struct v4l2_hdmi_dev *dev, struct vb2_queue *q, enum v4l2_memory memory);
int hdmirx_rtk_drv_probe(struct platform_device *pdev);
int hdmirx_rtk_drv_remove(struct platform_device *pdev);

#endif/* V4L2_HDMI_DEV_H */

