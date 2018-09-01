/*
 * xenbus.c - xenbus for regulator backend driver
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "regif-be: " fmt

#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <xen/xen.h>
#include <xen/events.h>
#include <xen/xenbus.h>
#include "regif.h"
#include "common.h"

#define PR_REQ(_req, _fmt, ...) \
	pr_debug("%d: %s " _fmt, (_req)->req_id, regif_op_string((_req)->op), __VA_ARGS__);

struct regif_back_info {
	struct xenbus_device *dev;

	struct regif_back_ring ring;
	void * ringp;
	unsigned int irq;

	struct task_struct *regifd;
	wait_queue_head_t wq;

	int ring_connected;

	struct mutex lock;
	int rsp_id;

};

static inline void ring_create_rsp(struct regif_back_info *info, int req_id, int ret, int err)
{
	struct regif_response *rsp;

	rsp = RING_GET_RESPONSE(&info->ring, info->ring.rsp_prod_pvt++);
	rsp->rsp_id = info->rsp_id++;
	rsp->req_id = req_id;
	rsp->retval = ret;
	rsp->errval = err;
}

static inline void ring_push_rsp(struct regif_back_info *info)
{
	int notify;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&info->ring, notify);
	if (notify)
		notify_remote_via_irq(info->irq);
}

static inline void ring_send_rsp(struct regif_back_info *info, int req_id, int ret, int err)
{
	ring_create_rsp(info, req_id, ret, err);
	ring_push_rsp(info);
}


static int regif_work_to_do(struct regif_back_info *info)
{
	if (!info->ring_connected)
		return 0;

	if (likely(RING_HAS_UNCONSUMED_REQUESTS(&info->ring)))
		return 1;

	return 0;
}

static int regif_kthread(void *arg)
{
	struct regif_back_info *info = arg;

	pr_info("%s\n", __func__);

	while (!kthread_should_stop()) {
		wait_event_interruptible(info->wq,
			regif_work_to_do(info) || kthread_should_stop());

		while (regif_work_to_do(info)) {
			int rp = info->ring.sring->req_prod;
			int rc = info->ring.req_cons;
			struct regif_request *req;
			int err;
			int ret;

			if (rc == rp)
				break;

			while (rc != rp) {
				req = RING_GET_REQUEST(&info->ring, rc);
				rc ++;
				err = REGIF_OK;
				ret = 0;

				switch(req->op) {
				case REGIF_OP_BIND_NAME:
				    PR_REQ(req, "name = %s\n", req->regulator_name);
				    ret = vreg_regulator_get(&info->dev->dev, req->regulator_name);
				    break;

				case REGIF_OP_GET_N_VOLTAGES:
				    PR_REQ(req, "rdev_id = %d\n", req->rdev_id);
				    ret = vreg_regulator_count_voltages(req->rdev_id);
				    break;

				case REGIF_OP_GET_VOLT_TABLE_N:
				    PR_REQ(req, "rdev_id = %d, vsel = %d\n", req->rdev_id, req->vsel);
				    ret = vreg_regulator_list_voltage(req->rdev_id, req->vsel);
				    break;

				case REGIF_OP_GET_CONSTRAINTS:
				    PR_REQ(req, "rdev_id = %d, csel = %d\n", req->rdev_id, req->csel);
				    ret = vreg_regulator_get_constraints(req->rdev_id, req->csel);
				    break;

				case REGIF_OP_SET_VOLT:
				    PR_REQ(req, "rdev_id = %d, vsel = %d\n", req->rdev_id, req->vsel);
				    ret = vreg_regulator_set_volt(req->rdev_id, req->vsel);
				    break;

				case REGIF_OP_GET_VOLT:
				    PR_REQ(req, "rdev_id = %d\n", req->rdev_id);
				    ret = vreg_regulator_get_volt(req->rdev_id);
				    break;
				}

				ring_send_rsp(info, req->req_id, ret, err);
			}

			info->ring.req_cons = rc;
			info->ring.sring->req_event = rc + 1;
		}
	}

	return 0;
}


static irqreturn_t regif_back_interrupt(int irq, void *dev_id)
{
	struct regif_back_info *info = dev_id;
	wake_up(&info->wq);
	return IRQ_HANDLED;
}

static int connect_ring(struct regif_back_info *info)
{
	unsigned int evtchn;
	unsigned int ring_ref;
	grant_ref_t gref;
	struct regif_sring *sring;
	int ret;
	const char * msg;

	msg = "xenbus_scanf::event-channel";
	ret = xenbus_scanf(XBT_NIL, info->dev->otherend, "event-channel", "%u", &evtchn);
	if (ret < 0)
		goto error;

	msg = "xenbus_scanf::ring-ref";
	ret = xenbus_scanf(XBT_NIL, info->dev->otherend, "ring-ref", "%u", &ring_ref);
	if (ret < 0)
		goto error;

	msg = "xenbus_map_ring_valloc";
	gref = ring_ref;
	ret = xenbus_map_ring_valloc(info->dev, &gref, 1, &info->ringp);
	if (ret)
		goto error;
	sring = (struct regif_sring *)info->ringp;
	BACK_RING_INIT(&info->ring, sring, PAGE_SIZE);


	msg = "bind_interdomain_evtchn_to_irqhandler";
	ret = bind_interdomain_evtchn_to_irqhandler(info->dev->otherend_id, evtchn,
		regif_back_interrupt, 0, "regif-backend", info);
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

static void disconnect_ring(struct regif_back_info *info)
{
	if (info->irq) {
		unbind_from_irqhandler(info->irq, info);
		info->irq = 0;
	}

	if (info->ringp) {
		xenbus_unmap_ring_vfree(info->dev, info->ringp);
		info->ringp = NULL;
	}

	info->ring_connected = 0;
}

static void frontend_changed(struct xenbus_device *dev,
	enum xenbus_state frontend_state)
{
	struct regif_back_info *info = dev_get_drvdata(&dev->dev);

	pr_info("%s: FE %s BE %s\n", __func__, xenbus_strstate(frontend_state), xenbus_strstate(dev->state));

	switch (frontend_state) {
	case XenbusStateInitialising:
		if (dev->state == XenbusStateClosed) {
			xenbus_switch_state(dev, XenbusStateInitWait);
		}
		break;

	case XenbusStateInitialised:
	case XenbusStateConnected:
		if (dev->state == XenbusStateConnected)
			break;

		if(connect_ring(info))
			break;

		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosing:
		xenbus_switch_state(dev, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		vreg_reset();
		disconnect_ring(info);
		xenbus_switch_state(dev, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;
	case XenbusStateUnknown:
		device_unregister(&dev->dev);
		break;

	default:
		break;
	}
}

static int regif_back_probe(struct xenbus_device *dev,
	const struct xenbus_device_id *id)
{
	int ret;
	struct regif_back_info *info;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info) {
		return -ENOMEM;
	}

	info->dev = dev;
	dev_set_drvdata(&dev->dev, info);

	init_waitqueue_head(&info->wq);
	info->regifd = kthread_run(regif_kthread, info, "%s", "regif-back");

	ret = xenbus_switch_state(dev, XenbusStateInitWait);
	if (ret)
		pr_err("Failed to xenbus_switch_state: %d\n", ret);

	return 0;
}

static int regif_back_remove(struct xenbus_device *dev)
{
	struct regif_back_info *info = dev_get_drvdata(&dev->dev);

	pr_info("%s\n", __func__);

	kthread_stop(info->regifd);
	vreg_reset();
	disconnect_ring(info);
	kfree(info);
	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}


static const struct xenbus_device_id regif_back_ids[] = {
	{ "vreg" },
	{ "" }
};

static struct xenbus_driver regif_back_driver = {
	.ids = regif_back_ids,
	.probe = regif_back_probe,
	.remove = regif_back_remove,
	.otherend_changed = frontend_changed,
};


int xen_regif_xenbus_init(void)
{
	return xenbus_register_backend(&regif_back_driver);
}

