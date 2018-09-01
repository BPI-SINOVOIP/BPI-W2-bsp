/*
 * regback.c - xen regulator backend driver
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <xen/xen.h>
#include <xen/events.h>
#include <xen/xenbus.h>

#include "xencec.h"

struct cec_back_info {
	struct xenbus_device *dev;
	
	struct task_struct *task;
	wait_queue_head_t wq;

	struct cec_back_ring ring;
	void *ringp;
	unsigned int irq;
	int ring_connected;

	int rsp_id;
};

extern void *get_cecdev_from_node(struct inode *inode);

static inline void ring_send_rsp(struct cec_back_info *info,
			int req_id, int ret, int err, void *ptr, char *data)
{
	struct cec_response *rsp;
	int notify;

	rsp = RING_GET_RESPONSE(&info->ring, info->ring.rsp_prod_pvt++);
	rsp->rsp_id = info->rsp_id++;
	rsp->req_id = req_id;
	rsp->retval = ret;
	rsp->errval = err;
	rsp->ptr = ptr;
	if(ret > 0)
		memcpy(&rsp->data, data, ret);

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&info->ring, notify);
	if (notify)
		notify_remote_via_irq(info->irq);
}

static int cec_work_to_do(struct cec_back_info *info)
{
	if (!info->ring_connected)
		return 0;

	if (likely(RING_HAS_UNCONSUMED_REQUESTS(&info->ring)))
		return 1;

	return 0;
}

static int cec_back_enable(cec_device *dev, unsigned long arg)
{
	cec_driver* drv = to_cec_driver(dev->dev.driver);
	return drv->enable(dev, (arg) ? 1 : 0);
}

static int cec_back_set_rxmask(cec_device *dev, unsigned long arg)
{
	cec_driver* drv = to_cec_driver(dev->dev.driver);
	return drv->set_rx_mask(dev, (unsigned short)arg | 0x8000);
}

static int cec_back_set_logical(cec_device *dev, unsigned long arg)
{
	unsigned short rx_mask;
	cec_driver* drv = to_cec_driver(dev->dev.driver);

	rx_mask = (unsigned char)arg;
	if (rx_mask > 0xF) {
		pr_err("%s: invalid logical addr %d\n", __func__, rx_mask);
		return -EFAULT;
	}
	rx_mask = (1 << rx_mask);
	return drv->set_rx_mask(dev, rx_mask | 0x8000);
}

static int cec_back_set_physical(cec_device *dev, unsigned long arg)
{
	cec_driver* drv = to_cec_driver(dev->dev.driver);
	return drv->set_physical_addr(dev, (unsigned short) arg);
}

static int cec_back_send_msg(cec_device *dev, char *data, int len)
{
	cec_driver* drv = to_cec_driver(dev->dev.driver);
	cm_buff *cmb;

	if ((cmb = alloc_cmb(len)) == NULL)
		return -ENOMEM;
	memcpy(cmb_put(cmb, len), data, len);

	return drv->xmit(dev, cmb, 0);
}

static int cec_back_rcv_msg(cec_device *dev, char *data, int len)
{
	cec_driver* drv = to_cec_driver(dev->dev.driver);
	cm_buff *cmb = NULL;

	cmb = drv->read(dev, NONBLOCK);
	if (cmb) {
		if (cmb->len > len) {
			pr_err("%s: msg size more than buffer\n", __func__);
			kfree_cmb(cmb);
			return -ENOMEM;
		}
		len = cmb->len;
		memcpy(data, cmb->data, cmb->len);
		kfree_cmb(cmb);
		return len;
	}
	return -EFAULT;
}

static void *cec_back_open(char *name)
{
	struct path path;
	struct inode *inode;
	void *dev = NULL;
	int ret;

	ret = kern_path(name, LOOKUP_FOLLOW, &path);
	if(ret) {
		pr_err("%s: can't find file path %s\n", __func__, name);
		return NULL;
	}
	inode = path.dentry->d_inode;
	if(inode)
		dev = get_cecdev_from_node(inode);

	return dev;
}

static int cec_kthread(void *arg)
{
	struct cec_back_info *info = arg;
	int ret = 0;
	int err = 0;
	void *ptr = NULL;
	char data[CEC_CMB_LENGTH];

	pr_info("%s\n", __func__);

	while (!kthread_should_stop()) {
		wait_event_interruptible(info->wq, 
			cec_work_to_do(info) || kthread_should_stop()); 
		while (cec_work_to_do(info)) {
			int rp = info->ring.sring->req_prod;
			int rc = info->ring.req_cons;
			struct cec_request *req;

			if (rc == rp)
				break;
			while (rc != rp) {
				req = RING_GET_REQUEST(&info->ring, rc);
				rc ++;
				switch(req->op) {
				case CEC_OP_OPEN:
					ptr = cec_back_open(req->cec_name);
					break;
				case CEC_OP_ENABLE:
					ret = cec_back_enable(req->dev, req->arg);
					break;
				case CEC_OP_SET_RXMASK:
					ret = cec_back_set_rxmask(req->dev, req->arg);
					break;
				case CEC_OP_SET_LOGICAL:
					ret = cec_back_set_logical(req->dev, req->arg);
					break;
				case CEC_OP_SET_PHYSICAL:
					ret = cec_back_set_physical(req->dev, req->arg);
					break;
				case CEC_OP_SEND_MSG:
					ret = cec_back_send_msg(req->dev, req->data, req->len);
					break;
				case CEC_OP_RCV_MSG:
					ret = cec_back_rcv_msg(req->dev, data, req->len);
					break;
				case CEC_OP_STANDBY:
					break;
				case CEC_OP_CEC_VER:
					break;
				case CEC_OP_VENDER_ID:
					break;
				}
                		ring_send_rsp(info, req->req_id, ret, err, ptr, data);
			}
			info->ring.req_cons = rc;
			info->ring.sring->req_event = rc + 1;
		}
	}
	info->task = NULL;
	return 0;
}

static irqreturn_t cec_back_interrupt(int irq, void *dev_id)
{
	struct cec_back_info *info = dev_id;

	wake_up(&info->wq);
	return IRQ_HANDLED;
}

static int connect_ring(struct cec_back_info *info)
{
	unsigned int evtchn;
	unsigned int ring_ref;
	grant_ref_t gref;
	struct cec_sring *sring;
	int ret;
	const char * msg;

	msg = "xenbus_scanf::event-channel";
	ret = xenbus_scanf(XBT_NIL, info->dev->otherend,
				"event-channel", "%u", &evtchn);
	if (ret < 0)
		goto error;

	msg = "xenbus_scanf::ring-ref";
	ret = xenbus_scanf(XBT_NIL, info->dev->otherend,
				"ring-ref", "%u", &ring_ref);
	if (ret < 0)
		goto error;

	msg = "xenbus_map_ring_valloc";
	gref = ring_ref;
	ret = xenbus_map_ring_valloc(info->dev, &gref, 1, &info->ringp);
	if (ret)
		goto error;
	sring = (struct cec_sring *)info->ringp;
	BACK_RING_INIT(&info->ring, sring, PAGE_SIZE);
    
	msg = "bind_interdomain_evtchn_to_irqhandler";
	ret = bind_interdomain_evtchn_to_irqhandler(info->dev->otherend_id,
			evtchn, cec_back_interrupt, 0, "cec-backend", info);
	if (ret < 0)
		goto unmap;
	info->irq = ret;

	info->ring_connected = 1;   
	return 0;    
unmap:
	xenbus_unmap_ring_vfree(info->dev, info->ringp);
error:
	pr_err("Failed at %s: %d\n", msg, ret);
	return ret;
}

static void disconnect_ring(struct cec_back_info *info)
{
	info->ring_connected = 0;

	if (info->irq) {
		unbind_from_irqhandler(info->irq, info);
		info->irq = 0;
	}

	if (info->ringp) {
		xenbus_unmap_ring_vfree(info->dev, info->ringp);
		info->ringp = NULL;
	}
}

static void frontend_changed(struct xenbus_device *dev,
		enum xenbus_state frontend_state)
{
	struct cec_back_info *info = dev_get_drvdata(&dev->dev);
    
	pr_info("cec %s: FE %s BE %s\n", __func__,
		xenbus_strstate(frontend_state), xenbus_strstate(dev->state));
	switch (frontend_state) {
	case XenbusStateInitialising:
		if (dev->state == XenbusStateClosed)
			xenbus_switch_state(dev, XenbusStateInitWait);
		break;

	case XenbusStateInitialised:
	case XenbusStateConnected:
		if (dev->state == XenbusStateConnected)
			break;
		if (connect_ring(info))
			break;
		info->task = kthread_run(cec_kthread, info, "%s", "cec-back");
		xenbus_switch_state(dev, XenbusStateConnected);
		break;
	case XenbusStateClosing:
		xenbus_switch_state(dev, XenbusStateClosing);
		break;
	case XenbusStateClosed:
		kthread_stop(info->task);
		disconnect_ring(info);
		xenbus_switch_state(dev, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;
	case XenbusStateUnknown:
		device_unregister(&dev->dev);
		break;
	default:
		pr_err("cec %s: not support\n", __func__);
		break;
	}
	return;
}

static int cec_back_probe(struct xenbus_device *dev,
		const struct xenbus_device_id *id)
{
	struct cec_back_info *info;
	int ret;

	pr_info("%s start\n", __func__);
	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	dev_set_drvdata(&dev->dev, info);
	
	init_waitqueue_head(&info->wq);
//	info->task = kthread_run(cec_kthread, info, "%s", "cec-back");

	ret = xenbus_switch_state(dev, XenbusStateInitWait);
	if (ret)
		pr_err("Failed to xenbus_switch_state: %d\n", ret);
	return 0;
}

static int cec_back_remove(struct xenbus_device *dev)
{
	struct cec_back_info *info = dev_get_drvdata(&dev->dev);

	pr_info("%s\n", __func__);
	if (info->task != NULL)
		kthread_stop(info->task);
	disconnect_ring(info);
	kfree(info);
	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}

static const struct xenbus_device_id cec_back_ids[] = {
	{ "cec" },
	{ "" }
};

static struct xenbus_driver cec_back_driver = {
	.ids = cec_back_ids,
	.probe = cec_back_probe,
	.remove = cec_back_remove,
	.otherend_changed = frontend_changed,
};

static int __init xen_cec_back_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	/* only exists in dom0 */
	if (!xen_initial_domain())
		return -ENODEV;

	printk(KERN_ERR "%s start\n", __func__);
	return xenbus_register_backend(&cec_back_driver);
}
late_initcall(xen_cec_back_init);
