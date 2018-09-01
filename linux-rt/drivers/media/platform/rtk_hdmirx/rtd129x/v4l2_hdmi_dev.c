/*
 * v4l2_hdmi_dev.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/switch.h>
#include <linux/time.h>

#include "v4l2_hdmi_dev.h"
#include "hdmirx_video_dev.h"
#include "hdmirx_wrapper.h"
#include "mipi_wrapper.h"
#include "hdmirx_reg.h"
#include "hdmirx_sysfs.h"
#include "hdmirx_clk_ctrl.h"
#include "hdcp2p2_dev.h"

#include "rx_drv/hdmiInternal.h"
#include "rx_drv/hdmiEDID.h"

#define MAX_WIDTH 4096
#define MAX_HEIGHT 2160

static struct task_struct *hdmi_hw_tsk;
static void __iomem *clk90k_vaddr[2];
/*=================== extern Variable/Function ===================*/
extern void __iomem *hdmi_rx_base[HDMI_RX_REG_BLOCK_NUM];
extern MIPI_TOP_INFO mipi_top;
extern HDMI_INFO_T hdmi;
extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;
extern HDMIRX_DTS_EDID_TBL_T hdmirx_edid;
extern int hdmi_stream_on;
extern int hdmi_timestamp_mode;// 0:system time, 1:90KHz timer

extern int Cbus_GetRx5v(void);
extern void Hdmi_SetHPD(char high);
extern void drvif_Hdmi_Init(void);
extern void drvif_Hdmi_InitSrc(unsigned char channel);
extern void drvif_Hdmi_Release(void);
extern HDMI_bool drvif_Hdmi_DetectMode(void);
extern HDMI_bool drvif_Hdmi_CheckMode(void);
extern void rtd_hdmiPhy_ISR(void);

extern unsigned int rtk_suspend_wakeup_flags_get(void);
/*======================================================*/
static inline void update_hdmirx_switch_state(struct v4l2_hdmi_dev *dev);

int hdmirx_queue_init(struct v4l2_hdmi_dev *dev, struct vb2_queue *q, enum v4l2_memory memory)
{
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF; /* | VB2_READ; */
	q->drv_priv = dev;
	q->buf_struct_size = sizeof(struct hdmi_buffer);
	q->ops = &hdmi_qops;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->dev = &dev->vdev.dev;

	if (memory == V4L2_MEMORY_USERPTR) {
		q->mem_ops = &vb2_vmalloc_memops;
	} else if (memory == V4L2_MEMORY_DMABUF) {
		q->mem_ops = &vb2_dma_contig_memops;
	} else if (memory == V4L2_MEMORY_MMAP) {
		q->mem_ops = &vb2_dma_contig_memops;
	} else {
		HDMIRX_ERROR("[%s] Invalid io mode:%d", __func__, memory);
		return -EINVAL;
	}

	return vb2_queue_init(q);
}

int hdmi_queue_setup(struct vb2_queue *vq,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[], struct device *alloc_devs[])
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);
	struct hdmi_dmaqueue *dma_q = &dev->hdmidq;
	unsigned long size;

	HDMIRX_INFO("[%s] outfmt(%u) width(%u) height(%u)",
		__func__, dev->outfmt, dev->width, dev->height);

	atomic_set(&dma_q->qcnt, 0);
	atomic_set(&dma_q->rcnt, 0);

	if (dev->outfmt >= OUT_ARGB)
		size = dev->width * dev->height * dev->bpp / 8;
	else
		size = roundup16(dev->width) * roundup16(dev->height) * dev->bpp / 8;

	if (size == 0)
		return -EINVAL;

	if (*nbuffers == 0)
		*nbuffers = 32;

	*nplanes = 1;

	sizes[0] = size;

	HDMIRX_INFO("[%s] count=%d, size=%ld", __func__, *nbuffers, size);
	return 0;
}

int hdmi_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);
	struct hdmi_buffer *buf = container_of(vb, struct hdmi_buffer, vb);
	unsigned long size;

	if (dev->width	< 48 || dev->width	> MAX_WIDTH ||
		dev->height < 32 || dev->height > MAX_HEIGHT)
		return -EINVAL;

	if (dev->outfmt >= OUT_ARGB)
		size = dev->width * dev->height * dev->bpp / 8;
	else
		size = roundup16(dev->width) * roundup16(dev->height) * dev->bpp / 8;

	if (vb2_plane_size(vb, 0) < size) {
		HDMIRX_ERROR("[%s] data will not fit into plane (%lu < %lu)",
			__func__, vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	vb2_set_plane_payload(&buf->vb, 0, size);

	if (vq->memory == V4L2_MEMORY_USERPTR) {
		struct mipi_vb2_vmalloc_buf *vb2_buf;
		unsigned long pfn;

		vb2_buf = vb->planes[0].mem_priv;
		follow_pfn(vb2_buf->vma, vb->planes[0].m.userptr, &pfn);
		buf->phys = __pfn_to_phys(pfn);
	} else if (vq->memory == V4L2_MEMORY_DMABUF) {
		buf->phys = vb2_dma_contig_plane_dma_addr(vb, 0);
	} else if (vq->memory == V4L2_MEMORY_MMAP) {
		dma_addr_t *addr = vb2_plane_cookie(vb, 0);

		buf->phys = *addr;
	}

	return 0;
}

void hdmi_buffer_finish(struct vb2_buffer *vb)
{
	u64 clk90k_value;

	if (hdmi_timestamp_mode) {
		/* 90KHz timer, Read LO first to ensure the correct */
		clk90k_value = readl(clk90k_vaddr[0]);
		clk90k_value = (clk90k_value<<32) | readl(clk90k_vaddr[1]);
		vb->timestamp = clk90k_value;
	} else {
		/* System timer */
		vb->timestamp = ktime_get_ns();
	}
}

void hdmi_buffer_queue(struct vb2_buffer *vb)
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	struct hdmi_buffer *buf = container_of(vb, struct hdmi_buffer, vb);
	struct hdmi_dmaqueue *hdmidq = &dev->hdmidq;
	unsigned long flags = 0;

	spin_lock_irqsave(&dev->slock, flags);
	list_add_tail(&buf->list, &hdmidq->active);
	atomic_inc(&hdmidq->qcnt);
	spin_unlock_irqrestore(&dev->slock, flags);

}

int hdmi_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);

	HDMIRX_INFO("[%s]", __func__);

	register_mipi_ion(dev);

	set_video_DDR_start_addr(dev);

	/* Enable mipi */
	setup_mipi();
	hdmi_stream_on = 1;

	return 0;
}

void hdmi_stop_generating(struct v4l2_hdmi_dev *dev)
{
	struct hdmi_dmaqueue *dma_q = &dev->hdmidq;

	HDMIRX_INFO("[%s]", __func__);

	/*
	 * Typical driver might need to wait here until dma engine stops.
	 * In this case we can abort imiedetly, so it's just a noop.
	 */

	/* Release all active buffers */
	while (!list_empty(&dma_q->active)) {
		struct hdmi_buffer *buf;

		buf = list_entry(dma_q->active.next, struct hdmi_buffer, list);
		list_del(&buf->list);
		vb2_buffer_done(&buf->vb, VB2_BUF_STATE_ERROR);
		HDMIRX_INFO("Release[%p/%d] done", buf, buf->vb.index);
	}

	if (dma_q->hwbuf[0] != NULL) {
		vb2_buffer_done(&dma_q->hwbuf[0]->vb, VB2_BUF_STATE_ERROR);
		dma_q->hwbuf[0] = NULL;
		HDMIRX_INFO("Release hwbuf[0] done");
	}

	if (dma_q->hwbuf[1] != NULL) {
		vb2_buffer_done(&dma_q->hwbuf[1]->vb, VB2_BUF_STATE_ERROR);
		dma_q->hwbuf[1] = NULL;
		HDMIRX_INFO("Release hwbuf[1] done");
	}

}

void hdmi_stop_streaming(struct vb2_queue *vq)
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);

	HDMIRX_INFO("[%s]", __func__);

	if (is_clock_enabled(CLK_MIPI) && hdmi.rx_5v_state)
		stop_mipi_process();

	hdmi_stop_generating(dev);

	deregister_mipi_ion(dev);
}

void hdmi_unlock(struct vb2_queue *vq)
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);

	mutex_unlock(&dev->mutex);
}

void hdmi_lock(struct vb2_queue *vq)
{
	struct v4l2_hdmi_dev *dev = vb2_get_drv_priv(vq);

	mutex_lock(&dev->mutex);
}

void  rx5v_do_task(struct v4l2_hdmi_dev *dev)
{
	int state;

	if (hdmi.gpio_5v_det < 0)
		state = Cbus_GetRx5v();
	else
		state = gpio_get_value(hdmi.gpio_5v_det);

	if (!state && hdmi.rx_5v_state) {
		/* RX unplugged */
		HDMIRX_INFO("Cable Unplugged");

		stop_mipi_process();
		/* Stop DMA */
		set_hdmirx_wrapper_control_0(-1, 0, -1, -1, -1, -1);
		/* Disable wrapper interrupt */
		set_hdmirx_wrapper_interrupt_en(0, 0, 0);
		drvif_Hdmi_Release();
		memset(&hdmi_ioctl_struct, 0, sizeof(hdmi_ioctl_struct));
		SET_HDMI_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
		SET_HDMI_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		mipi_top.hdmi_rx_init = 0;

		hdmi.rx_5v_state = 0;
		Hdmi_SetHPD(0);

		/* Delay for RX service turn off audio, prevent AudioFW crash */
		update_hdmirx_switch_state(dev);
		usleep_range(280000, 300000);

		/* Stop hdmirx */
		set_hdmirx_wrapper_control_0(-1, -1, -1, -1, -1, 0);
		/* Disable RX clock */
		hdmirx_clock_control(CLK_HDMIRX|CLK_RXWRAP|CLK_MIPI, CTL_DISABLE);
	} else if (state && !hdmi.rx_5v_state) {
		/* RX plugged */
		HDMIRX_INFO("Cable Plugged");

		/* Enable RX clock */
		hdmirx_clock_control(CLK_HDMIRX|CLK_RXWRAP|CLK_MIPI, CTL_ENABLE);
		/* Enable hdmirx */
		set_hdmirx_wrapper_control_0(-1, -1, -1, -1, -1, 1);
		hdmi.rx_5v_state = 1;
	}
}

void hdmi_rx_process(void)
{
	unsigned char ret;
	static int state = 0;

	if (mipi_top.hdmi_rx_init == 0) {
		hdmi_related_wrapper_init();
		HdmiRx_EnableEDID();
		drvif_Hdmi_Init();
		drvif_Hdmi_InitSrc(HDMI_CHANNEL0);
		mipi_top.hdmi_rx_init = 1;
		state = 0;
		Hdmi_SetHPD(1);/* set hotplug pin high */
	}

	switch (state) {
	case 0:
		if (hdmi_ioctl_struct.DEF_ready) {
			if (drvif_Hdmi_DetectMode() == _MODE_SUCCESS)
				state++;
		}
		break;
	case 1:
		ret = drvif_Hdmi_CheckMode();
		if ((ret == FALSE) && hdmi_ioctl_struct.detect_done) {
			HDMIRX_INFO("Check mode is false, restart HDMI Rx wrapper detection ret(%d)\n", ret);
			state = 0;
			restartHdmiRxWrapperDetection();
		} else if (hdmi_ioctl_struct.detect_done == 0) {
			HDMIRX_INFO("Check mode is fine, but detect_done=0 ret(%d)\n", ret);
			state = 0;
		}
		break;
	default:
		state = 0;
		break;
	}
}

static inline void update_hdmirx_switch_state(struct v4l2_hdmi_dev *dev)
{
	unsigned char hdcp_state = 0;
	static unsigned char audio_count = 0;

	if (hdmi_ioctl_struct.measure_ready != switch_get_state(&dev->sdev)) {
		switch_set_state(&dev->sdev, hdmi_ioctl_struct.measure_ready);
		pr_err("\033[0;31m[HDMI RX] switch hdmi rx state to %d\033[m\n",
			hdmi_ioctl_struct.measure_ready);
	}


	if (!hdmi_ioctl_struct.audio_detect_done)
		audio_count = 0;

	if (hdmi_ioctl_struct.audio_detect_done != switch_get_state(&dev->asdev)) {
		if (hdmi_ioctl_struct.audio_detect_done)
			audio_count++;

		if ((!hdmi_ioctl_struct.audio_detect_done) || (audio_count >= 10)) {
			switch_set_state(&dev->asdev, hdmi_ioctl_struct.audio_detect_done);
			HDMIRX_INFO("switch audio detect state to %d", hdmi_ioctl_struct.audio_detect_done);
		}
	}

	if ((hdmi_ioctl_struct.hdcp_state == HDCPRX_STATE_1PX_ON) ||
		(hdmi_ioctl_struct.hdcp_state == HDCPRX_STATE_2P2_ON))
		hdcp_state = 1;

	if (hdcp_state != switch_get_state(&dev->hsdev)) {
		switch_set_state(&dev->hsdev, hdcp_state);
		HDMIRX_INFO("switch hdcp state to %d", hdcp_state);
	}
}

static int mipi_top_thread(void *arg)
{
	unsigned int i;
	struct v4l2_hdmi_dev *dev = arg;

	for (;;) {
		if (kthread_should_stop())
			break;

		rx5v_do_task(dev);

		if (mipi_top.src_sel == 1) {
			if (hdmi.rx_5v_state) {
				hdmi_rx_process();
				for (i = 0; i < 3; i++) {
					update_hdmirx_switch_state(dev);
					usleep_range(70000, 75000);/* 70ms~75ms */
					if (mipi_top.hdmi_rx_init)
						rtd_hdmiPhy_ISR();
				}
			} else {
				msleep(250);
			}
		}

	}
	return 0;
}


int hdmirx_rtk_drv_probe(struct platform_device *pdev)
{
	int ret, i;
	u32 irq;
	struct v4l2_hdmi_dev *hdmi_dev;
	struct switch_dev *sdev;/* video switch device */
	struct switch_dev *asdev;/* audio switch device */
	struct switch_dev *hsdev; /* hdcp switch device */
	const u32 *edid_table_pro;
	int edid_cell_size;
	HDMIRX_DTS_EDID_TBL_T dts_edid_table;

	/* Get clock controller */
	hdmirx_clock_init(pdev);

	/* Release reset, enable clock */
	hdmirx_clock_control(CLK_ALL, CTL_ENABLE);

	/* Disable RX clock for saving power */
	hdmirx_clock_control(CLK_HDMIRX | CLK_RXWRAP | CLK_MIPI, CTL_DISABLE);

	if (WARN_ON(!(pdev->dev.of_node))) {
		HDMIRX_ERROR("[%s] No device node", __func__);
		ret = -ENODEV;
		goto exit;
	}

	/* Initialize global variables */
	memset(&mipi_top, 0, sizeof(mipi_top));
	memset(&hdmi, 0, sizeof(hdmi));
	memset(&hdmi_ioctl_struct, 0, sizeof(hdmi_ioctl_struct));
	memset(&hdmirx_edid, 0, sizeof(hdmirx_edid));

	for (i = 0; i < HDMI_RX_REG_BLOCK_NUM; i++) {
		hdmi_rx_base[i] = of_iomap(pdev->dev.of_node, i);
		WARN(!(hdmi_rx_base[i]), "Unable to map HDMI RX base registers\n");
	}

	/* 90KHz timer */
	clk90k_vaddr[0] = ioremap(0x9801B540, 0x4);/* LK90K_LO */
	clk90k_vaddr[1] = ioremap(0x9801B544, 0x4);/* CLK90K_HI */

	/* Save EDID table */
	edid_table_pro = of_get_property(pdev->dev.of_node, "Realtek,edid-table", &edid_cell_size);
	if (edid_table_pro && (edid_cell_size == 1024)) {
		edid_cell_size = edid_cell_size / 4;/*Each Read is 4bytes (1world), so divide it by 4*/
		for (i = 0; i < edid_cell_size; i++)
			dts_edid_table.EDID[i] = (unsigned char) of_read_number(edid_table_pro, 1 + i);

		HdmiRx_Save_DTS_EDID_Table(&dts_edid_table);
	} else {
		HDMIRX_ERROR("[%s] Parsing EDID table content failed", __func__);
	}

	/* Save HDMI2.0 EDID table */
	edid_table_pro = of_get_property(pdev->dev.of_node, "Realtek,edid2p0-table", &edid_cell_size);
	if (edid_table_pro && (edid_cell_size == 1024)) {
		/*Each Read is 4bytes (1world), so divide it by 4*/
		edid_cell_size = edid_cell_size / 4;
		for (i = 0; i < edid_cell_size; i++)
			dts_edid_table.EDID[i] = (unsigned char) of_read_number(edid_table_pro, 1 + i);

		HdmiRx_Save_DTS_EDID2p0_Table(&dts_edid_table);
	} else {
		HDMIRX_ERROR("[%s] Parsing 2.0 EDID table content failed", __func__);
	}

	/* HPD control GPIO */
	hdmi.gpio_hpd_ctrl = of_get_named_gpio(pdev->dev.of_node, "gpio-rx-hpd-ctrl", 0);
	if (hdmi.gpio_hpd_ctrl < 0) {
		HDMIRX_ERROR("Get gpio-rx-hpd-ctrl fail");
		ret = -ENODEV;
		goto exit;
	} else {
		HDMIRX_INFO("HPD control gpio(%d)", hdmi.gpio_hpd_ctrl);
		if (!gpio_is_valid(hdmi.gpio_hpd_ctrl))
			HDMIRX_ERROR("gpio %d is not valid", hdmi.gpio_hpd_ctrl);
		if (gpio_request(hdmi.gpio_hpd_ctrl, pdev->dev.of_node->name))
			HDMIRX_ERROR("Request gpio %d fail", hdmi.gpio_hpd_ctrl);
	}
	Hdmi_SetHPD(0);

	/* 5V detect GPIO */
	hdmi.gpio_5v_det = of_get_named_gpio(pdev->dev.of_node, "gpio-5v-detect", 0);
	if (hdmi.gpio_5v_det < 0) {
		HDMIRX_INFO("Use cbus 5V detect");
	} else {
		HDMIRX_INFO("5V detect gpio(%d)", hdmi.gpio_5v_det);
		if (!gpio_is_valid(hdmi.gpio_5v_det))
			HDMIRX_ERROR("gpio %d is not valid", hdmi.gpio_5v_det);
		if (gpio_request(hdmi.gpio_5v_det, pdev->dev.of_node->name))
			HDMIRX_ERROR("Request gpio %d fail", hdmi.gpio_5v_det);

		gpio_direction_input(hdmi.gpio_5v_det);
	}

	/* Register v4l2 device */
	hdmi_dev = kzalloc(sizeof(*hdmi_dev), GFP_KERNEL);
	if (!hdmi_dev) {
		HDMIRX_ERROR("[%s] kzalloc fail", __func__);
		ret = -ENOMEM;
		goto exit;
	}
	snprintf(hdmi_dev->v4l2_dev.name, sizeof(hdmi_dev->v4l2_dev.name), "v4l2_mipi_top");
	ret = v4l2_device_register(NULL, &hdmi_dev->v4l2_dev);
	if (ret < 0) {
		HDMIRX_ERROR("[%s] Register v4l2 device fail", __func__);
		goto free_dev;
	}
	if (ret)
		goto free_dev;

	pdev->dev.platform_data = hdmi_dev;

	/* Set default value */
	hdmi_dev->width = 1920;
	hdmi_dev->height = 1080;
	hdmi_dev->bpp = 12;/* OUT_YUV420 */

	mipi_top.src_sel = 1;

	/* Initialize locks */
	spin_lock_init(&hdmi_dev->slock);
	mutex_init(&hdmi_dev->mutex);

	/* Init video dma queues */
	INIT_LIST_HEAD(&hdmi_dev->hdmidq.active);

	if (register_video_device(hdmi_dev) < 0) {
		HDMIRX_ERROR("[%s] Register video device fail", __func__);
		goto free_dev;
	}

	/* Register interrupt handle */
	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	WARN(!(irq), "[HDMI RX] irq map fail\n");
	if (request_irq(irq, hdmirx_mipi_isr, IRQF_SHARED, "mipi", hdmi_dev))
		HDMIRX_ERROR("Cannot register IRQ %d", irq);
	else
		HDMIRX_INFO("mipi irq(%d)", irq);

	/* Register switch device */
	sdev = &hdmi_dev->sdev;
	memset(sdev, 0, sizeof(*sdev));
	sdev->name = "rx_video";
	ret = switch_dev_register(sdev);
	if (ret < 0)
		goto unreg_vdev;
	switch_set_state(&hdmi_dev->sdev, 0);

	/* Register audio switch device */
	asdev = &hdmi_dev->asdev;
	memset(asdev, 0, sizeof(*asdev));
	asdev->name = "rx_audio";
	ret = switch_dev_register(asdev);
	if (ret < 0)
		goto unreg_vdev;
	switch_set_state(&hdmi_dev->asdev, 0);

	/* Register hdcp switch device */
	hsdev = &hdmi_dev->hsdev;
	hsdev->name = "rx_hdcp";
	ret = switch_dev_register(hsdev);
	if (ret < 0)
		goto unreg_vdev;
	switch_set_state(&hdmi_dev->hsdev, 0);

	/* Register sysfs */
	register_hdmirx_sysfs(pdev);

#ifdef CONFIG_RTK_HDCPRX_2P2
	register_hdcp2p2_device();
#endif

	/* Init reset MIPI clock work function */
	INIT_WORK(&mipi_top.mipi_reset_work, mipi_reset_work_func);

	/* HDMI RX thread */
	hdmi_hw_tsk = kthread_create(mipi_top_thread, hdmi_dev, "mipi_hw_thread");
	if (IS_ERR(hdmi_hw_tsk)) {
		ret = PTR_ERR(hdmi_hw_tsk);
		hdmi_hw_tsk = NULL;
		goto unreg_vdev;
	}
	wake_up_process(hdmi_hw_tsk);

	return 0;

unreg_vdev:
	video_unregister_device(&hdmi_dev->vdev);
free_dev:
	kfree(hdmi_dev);
exit:
	return ret;
}

int hdmirx_rtk_drv_remove(struct platform_device *pdev)
{
	struct fb_info *info = platform_get_drvdata(pdev);

	HDMIRX_INFO("driver remove\n");
	if (info) {
		unregister_framebuffer(info);
		framebuffer_release(info);
	}
	return 0;
}

#ifdef CONFIG_SUSPEND
static int hdmirx_rtk_drv_suspend(struct device *dev)
{
	struct platform_device *pdev;
	struct v4l2_hdmi_dev *hdmi_dev;

	HDMIRX_INFO(" Enter %s", __func__);

	kthread_stop(hdmi_hw_tsk);

	/* Switch rx state to 0 */
	pdev = to_platform_device(dev);
	hdmi_dev = pdev->dev.platform_data;
	if (switch_get_state(&hdmi_dev->sdev)) {
		pr_err("\033[0;31m[HDMI RX] switch hdmi rx state to %d\033[m\n", 0);
		switch_set_state(&hdmi_dev->sdev, 0);
	}

	if (hdmi.rx_5v_state) {
		stop_mipi_process();
		/* Stop DMA */
		set_hdmirx_wrapper_control_0(-1, 0, -1, -1, -1, -1);
		/* Disable wrapper interrupt */
		set_hdmirx_wrapper_interrupt_en(0, 0, 0);
		drvif_Hdmi_Release();
		memset(&hdmi_ioctl_struct, 0, sizeof(hdmi_ioctl_struct));
		SET_HDMI_VIDEO_FSM(MAIN_FSM_HDMI_SETUP_VEDIO_PLL);
		SET_HDMI_AUDIO_FSM(AUDIO_FSM_AUDIO_START);
		mipi_top.hdmi_rx_init = 0;
		hdmi.rx_5v_state = 0;

		/* Stop hdmirx */
		set_hdmirx_wrapper_control_0(-1, -1, -1, -1, -1, 0);
		/* Disable  RX clock */
		hdmirx_clock_control(CLK_HDMIRX | CLK_RXWRAP | CLK_MIPI, CTL_DISABLE);
	}

	Hdmi_SetHPD(0);

	if (rtk_suspend_wakeup_flags_get()&(0x1U << 5))
		HDMIRX_INFO("CEC wakeup is enabled, skip turn off cbus clock");
	else
		hdmirx_clock_control(CLK_CBUS, CTL_DISABLE);/* Disable  Cbus clock */

	HDMIRX_INFO(" Exit %s", __func__);
	return 0;
}

static int hdmirx_rtk_drv_resume(struct device *dev)
{
	struct platform_device *pdev;
	struct v4l2_hdmi_dev *hdmi_dev;

	HDMIRX_INFO("Enter %s", __func__);

	pdev = to_platform_device(dev);
	hdmi_dev = pdev->dev.platform_data;

	/* Release reset, enable clock */
	if (rtk_suspend_wakeup_flags_get()&(0x1U << 5)) {
		hdmirx_clock_control(CLK_HDMIRX | CLK_RXWRAP | CLK_MIPI, CTL_ENABLE);
		HDMIRX_INFO("CEC wakeup is enabled, only turn on hdmirx clock");
	} else {
		hdmirx_clock_control(CLK_ALL, CTL_ENABLE);
	}

	/* Disable RX clock for saving power */
	hdmirx_clock_control(CLK_HDMIRX | CLK_RXWRAP | CLK_MIPI, CTL_DISABLE);

	Hdmi_SetHPD(0);
	hdmi_hw_tsk = kthread_run(mipi_top_thread, hdmi_dev, "mipi_hw_thread");

	HDMIRX_INFO("Exit %s", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_hdmirx_pm_ops = {
	.suspend    = hdmirx_rtk_drv_suspend,
	.resume     = hdmirx_rtk_drv_resume,
};
#endif /* CONFIG_SUSPEND */

static const struct of_device_id hdmirx_rtk_dt_ids[] = {
	{ .compatible = "Realtek,rtk-mipi-top", },
	{},
};

struct platform_driver hdmirx_rtk_driver = {
	.probe  = hdmirx_rtk_drv_probe,
	.remove = hdmirx_rtk_drv_remove,
	.driver = {
		.name   = "rtk-mipi-top",
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(hdmirx_rtk_dt_ids),
#ifdef CONFIG_SUSPEND
		.pm = &rtk_hdmirx_pm_ops,
#endif /* CONFIG_SUSPEND */
	},
};

static int __init hdmirx_init(void)
{
	int retval = 0;

	HDMIRX_INFO("driver init");
	retval = platform_driver_register(&hdmirx_rtk_driver);
	HDMIRX_INFO("driver init done");

	return retval;
}

static void __exit hdmi_exit(void)
{
	HDMIRX_INFO("driver exit");
	// TODO:
	platform_driver_unregister(&hdmirx_rtk_driver);
}

module_init(hdmirx_init);
module_exit(hdmi_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek HDMI RX kernel module");
