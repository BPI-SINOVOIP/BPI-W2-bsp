/*
 * xen-regfront.c - xen regulator frontend driver
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "regif-fe: " fmt

#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/of_regulator.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <xen/xen.h>
#include <xen/events.h>
#include <xen/xenbus.h>
#include <xen/grant_table.h>
#include "xen-regback/regif.h"

#define DEBUG 0

#if DEBUG
#define PR_DEBUG(...) pr_err(__VA_ARGS__);
#else
#define PR_DEBUG(...)
#endif

struct regif_front_info {
	struct xenbus_device *dev;

	struct regif_front_ring ring;
	int ring_ref;
	unsigned int evtchn;
	unsigned int irq;

	int connected;

	struct mutex lock;
	volatile int wait_done;
	int req_id;

	char name_buf[1024];
};

static LIST_HEAD(regif_list);

struct regif_regulator {
	struct list_head list;
	struct regif_front_info *info;
	struct regulator_dev *rdev;
	struct regulator_desc desc;
	unsigned int *volt_table;
};

static inline struct regif_request *ring_new_req(struct regif_front_info *info)
{
	struct regif_request *req = RING_GET_REQUEST(&info->ring, info->ring.req_prod_pvt);
	info->ring.req_prod_pvt++;
	req->req_id = info->req_id++;
	return req;
}

static inline void ring_push_req(struct regif_front_info *info)
{
	int notify;
	info->wait_done = 0;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&info->ring, notify);
	if (notify)
		notify_remote_via_irq(info->irq);
}

static inline int ring_wait_rsp(struct regif_front_info *info)
{
#define RETRY_CONUNT 2000
	int i;
	for (i = 0; i < RETRY_CONUNT; i++) {
		if (info->wait_done)
			return i;
		udelay(100);
	}
	pr_info("%s timeout\n", __func__);
	return -EINVAL;
}

static inline struct regif_response * ring_get_rsp(struct regif_front_info *info)
{
	struct regif_response *rsp = RING_GET_RESPONSE(&info->ring, info->ring.rsp_cons++);
	int more_to_do;

again:
	RING_FINAL_CHECK_FOR_RESPONSES(&info->ring, more_to_do);
	if (more_to_do) {
		struct regif_response *rsp_1 =
			RING_GET_RESPONSE(&info->ring, info->ring.rsp_cons++);

		pr_info("multiple response\n");
		pr_info("rsp_id  = %d\n", rsp_1->rsp_id);
		pr_info("req_id  = %d\n", rsp_1->req_id);
		pr_info("op      = %s\n", regif_op_string(rsp_1->op));
		pr_info("rdev_id = %d\n", rsp_1->rdev_id);
		pr_info("retval  = %d\n", rsp_1->retval);
		pr_info("errval  = %d\n", rsp_1->errval);

		goto again;
	}

	return rsp;
}

static struct regif_response *ring_send_req_ang_get_rsp(struct regif_front_info *info)
{
	ring_push_req(info);
	if (ring_wait_rsp(info) < 0)
		return NULL;
	return ring_get_rsp(info);
}

/**
 * GET_FROM_BE - a helper macro
 * @_info: fe info
 * @_op: REGIF_OP_*
 * @_id: rdev_id
 * @_sel_name: member name to be set, if no value use 'dummy'
 * @_sel_val: value of @_sel_name to be set
 * @_fail_label: goto this label when failed
 */
#define GET_FROM_BE(_info, _op, _id, _sel_name, _sel_val, _fail_label)  \
({                                              \
	struct regif_request *_req;                 \
	struct regif_response *_rsp;                \
	_req = ring_new_req(_info);                 \
	_req->op = _op;                             \
	_req->rdev_id = _id;                        \
	_req->_sel_name = _sel_val;                 \
				                                \
	_rsp = ring_send_req_ang_get_rsp(_info);    \
	if (!_rsp)                                  \
		goto _fail_label;                       \
	PR_DEBUG("id = %d, op = %s, sel = %s/%d, ret = %d \n", _id, regif_op_string(_op), #_sel_val, _sel_val, _rsp->retval); \
				                                \
	_rsp->retval;                               \
})

static int regif_front_set_voltage_sel(struct regulator_dev *rdev, unsigned sel)
{
	struct regif_front_info *info = rdev_get_drvdata(rdev);
	int ret = 0;

	if (!info->connected)
		return -EPERM;

	mutex_lock(&info->lock);
	ret = GET_FROM_BE(info, REGIF_OP_SET_VOLT, rdev->desc->id,
		vsel, sel, fail);
fail:
	mutex_unlock(&info->lock);

	return 0;
}

static int regif_front_get_voltage(struct regulator_dev *rdev)
{
	struct regif_front_info *info = rdev_get_drvdata(rdev);
	int ret = -EINVAL;

	if (!info->connected)
		return -EPERM;

	mutex_lock(&info->lock);
	ret = GET_FROM_BE(info, REGIF_OP_GET_VOLT, rdev->desc->id,
		dummy, 0, fail);
fail:
	mutex_unlock(&info->lock);

	return ret;
}

static struct regulator_ops frontend_regulator_ops = {
	.list_voltage    = regulator_list_voltage_table,
	.map_voltage     = regulator_map_voltage_iterate,
	.set_voltage_sel = regif_front_set_voltage_sel,
	.get_voltage     = regif_front_get_voltage,
};

struct regulator_dev *regif_regulator_register(struct xenbus_device *dev,
	const char *name,
	const struct regulator_config *config)
{
	const char *msg;
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);
	struct regif_regulator *rr;
	struct regulator_dev *rdev = NULL;
	int rdev_id;

	struct regulator_config cfg;
	struct regulator_init_data init_data;

	struct regif_request *req;
	struct regif_response *rsp;
	int i;
	struct device_node *child;
	unsigned int ivolt;


	if (!info->connected)
		return NULL;

	rr = kzalloc(sizeof(*rr), GFP_KERNEL);
	if (!rr)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&info->lock);

	msg = "get::id";
	req = ring_new_req(info);
	req->op = REGIF_OP_BIND_NAME;
	strncpy(req->regulator_name, name, REGIF_NAME_LENGTH);

	rsp = ring_send_req_ang_get_rsp(info);
	if (!rsp)
		goto fail;
	rdev_id = rsp->retval;

	msg = "get::n_voltages";
	rr->desc.n_voltages = GET_FROM_BE(info, REGIF_OP_GET_N_VOLTAGES, rdev_id, dummy, 0, fail);

	msg = "alloc::volt_table";
	rr->volt_table = kzalloc(sizeof(*rr->volt_table) * rr->desc.n_voltages,
		GFP_KERNEL);
	if (!rr->volt_table)
		goto fail;

	msg = "get::volt_table";
	for (i = 0; i < rr->desc.n_voltages; i++)
	{
		rr->volt_table[i] = GET_FROM_BE(info, REGIF_OP_GET_VOLT_TABLE_N, rdev_id, vsel, i, fail);
	}


	rr->desc.name  = name;
	rr->desc.id    = rdev_id;
	rr->desc.type  = REGULATOR_VOLTAGE,
	rr->desc.owner = THIS_MODULE,
	rr->desc.ops   = &frontend_regulator_ops;
	rr->desc.volt_table = rr->volt_table;

	memcpy(&cfg, config, sizeof(cfg));
	if (cfg.init_data) {
		memcpy(&init_data, cfg.init_data, sizeof(init_data));
	} else {
		memset(&init_data, 0, sizeof(init_data));
	}
	cfg.init_data = &init_data;

	for_each_child_of_node(dev->dev.of_node, child) {
		const char *match_name = of_get_property(child, "regulator-compatible", NULL);
		if (!match_name)
			match_name = child->name;

		if (strcmp(name, match_name))
			continue;

		cfg.of_node = child;
		break;
	}

	/* try get name from of_node */
	if (cfg.of_node) {
		init_data.constraints.name =
			of_get_property(cfg.of_node, "regulator-name", NULL);
	}

	if (!init_data.constraints.name)
		init_data.constraints.name = name;

	msg = "get::constraints";
	init_data.constraints.max_uV = GET_FROM_BE(info, REGIF_OP_GET_CONSTRAINTS,
		rdev_id, csel, VREG_CONSTRAINTS_MAX_VOLT, fail);
	init_data.constraints.min_uV = GET_FROM_BE(info, REGIF_OP_GET_CONSTRAINTS,
		rdev_id, csel, VREG_CONSTRAINTS_MIN_VOLT, fail);
	init_data.constraints.boot_on = GET_FROM_BE(info, REGIF_OP_GET_CONSTRAINTS,
		rdev_id, csel, VREG_CONSTRAINTS_BOOT_ON, fail);
	init_data.constraints.always_on = GET_FROM_BE(info, REGIF_OP_GET_CONSTRAINTS,
		rdev_id, csel, VREG_CONSTRAINTS_ALWAYS_ON, fail);
	init_data.constraints.valid_ops_mask = GET_FROM_BE(info, REGIF_OP_GET_CONSTRAINTS,
		rdev_id, csel, VREG_CONSTRAINTS_VALID_OPS, fail);

	mutex_unlock(&info->lock);

	rdev = devm_regulator_register(&dev->dev, &rr->desc, &cfg);
	if (IS_ERR_OR_NULL(rdev))
		goto fail_unlocked;

	rr->rdev = rdev;
	list_add(&rr->list, &regif_list);

	/* regulator is ready now */
	if (!of_property_read_u32(cfg.of_node, "regulator-init-microvolt",
		&ivolt)) {
		int ret;

		ret = regulator_map_voltage_iterate(rdev, ivolt, ivolt);
		pr_info("init-microvolt = %u, sel = %d\n", ivolt, ret);
		ret = regif_front_set_voltage_sel(rdev, ret);
		if (ret)
			pr_err("set init-volt returns %d\n", ret);
   }


	return rdev;
fail:
	mutex_unlock(&info->lock);
fail_unlocked:
	if (rr->volt_table)
		kfree(rr->volt_table);

	if (rr)
		kfree(rr);
	return rdev;;
}

static void free_regulators(void)
{
	struct list_head * it = NULL;
	list_for_each(it, &regif_list) {
		struct regif_regulator * rr = list_entry(it, struct regif_regulator, list);
		regulator_unregister(rr->rdev);
		if (rr->volt_table)
			kfree(rr->volt_table);
		kfree(rr);
	}
	INIT_LIST_HEAD(&regif_list);
}

static irqreturn_t regif_front_interrupt(int irq, void *dev_id)
{
	struct regif_front_info *info = dev_id;

	info->wait_done = 1;

	return IRQ_HANDLED;
}

static void init_regulator(struct xenbus_device *dev)
{
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);
	int err;
	char *s, *n;
	int final;

	/* get a list */
	xenbus_scanf(XBT_NIL, dev->nodename, "regulator", "%s", info->name_buf);
	pr_info("regulator(s) = %s\n",  info->name_buf);

	/* attach to DT, so child nodes can be found when register */
	dev->dev.of_node = of_find_compatible_node(NULL, NULL, "xen,vreg");

	final = 0;
	for (s = n = info->name_buf; !final; n++)
	{
		struct regulator_config cfg = {};
		struct regulator_dev *rdev;

		if (*n == 0)
			final = 1;
		if (*n == ':')
			*n = 0;
		if (*n != 0)
			continue;

		cfg.dev = &dev->dev;
		cfg.driver_data = info;

		rdev = regif_regulator_register(dev, s, &cfg);
		if (IS_ERR_OR_NULL(rdev)) {
			err = PTR_ERR(rdev);
			dev_err(&dev->dev, "Failed to register regulator : %d\n", err);
		}

		s = n + 1;
	}
}

static void free_ring(struct xenbus_device *dev)
{
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);

	if (info->irq) {
		unbind_from_irqhandler(info->irq, info);
		info->irq = 0;
	}

	if (info->evtchn) {
		xenbus_free_evtchn(dev, info->evtchn);
		info->evtchn = 0;
	}

	if (info->ring_ref != 0) {
		gnttab_end_foreign_access(info->ring_ref, 0, (unsigned long)info->ring.sring);
		info->ring_ref = 0;
	}

	info->connected = 0;
}


static int setup_ring(struct xenbus_device *dev)
{
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);
	struct regif_sring *sring;
	unsigned long ring_size = PAGE_SIZE;
	int err;
	grant_ref_t gref;
	const char *msg;

	sring = (struct regif_sring *)__get_free_pages(GFP_NOIO | __GFP_HIGH, get_order(ring_size));
	if (!sring) {
		return -ENOMEM;
	}

	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&info->ring, sring, ring_size);

	msg = "xenbus_grant_ring";
	err = xenbus_grant_ring(dev, info->ring.sring, 1, &gref);
	if (err)
		goto fail;
	info->ring_ref = gref;

	msg = "xenbus_alloc_evtchn";
	err = xenbus_alloc_evtchn(dev, &info->evtchn);
	if (err)
		goto fail;

	msg = "bind_evtchn_to_irqhandler";
	err = bind_evtchn_to_irqhandler(info->evtchn, regif_front_interrupt, 0, "regif", info);
	if (err <= 0)
		goto fail;
	info->irq = err;

	return 0;
fail:
	xenbus_dev_fatal(dev, err, "%s\n", msg );
	free_ring(dev);
	return err;
}


static int talk_to_backend(struct xenbus_device *dev)
{
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);
	struct xenbus_transaction xbt;
	int err;
	const char *msg;

	msg = "setup_ring";
	err = setup_ring(dev);
	if (err)
		goto destroy_ring;
again:
	msg = "xenbus_transaction_start";
	err = xenbus_transaction_start(&xbt);
	if (err)
		goto destroy_ring;

	msg = "xenbus_printf::event-channel";
	err = xenbus_printf(xbt, dev->nodename, "event-channel", "%u", info->evtchn);
	if (err)
		goto abort_transaction;

	msg = "xenbus_printf::ring-ref";
	err = xenbus_printf(xbt, dev->nodename, "ring-ref", "%u", info->ring_ref);
	if (err)
		goto abort_transaction;

	msg = "xenbus_transaction_end";
	err = xenbus_transaction_end(xbt, 0);
	if (err == -EAGAIN)
		goto again;
	if (err)
		goto destroy_ring;

	xenbus_switch_state(dev, XenbusStateInitialised);

	info->connected = 1;

	return 0;

abort_transaction:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, err, "%s", msg);
destroy_ring:
	free_ring(dev);
	return err;
}

static void backend_changed(struct xenbus_device *dev,
	enum xenbus_state backend_state)
{
	struct regif_front_info __maybe_unused *info = dev_get_drvdata(&dev->dev);

	pr_info("%s: BE %s FE %s\n", __func__, xenbus_strstate(backend_state), xenbus_strstate(dev->state));

	switch (backend_state) {
	case XenbusStateInitWait:
		if (dev->state != XenbusStateInitialising)
			break;

		if (talk_to_backend(dev))
			break;
		break;

	case XenbusStateConnected:
		if (dev->state == XenbusStateConnected)
			break;

		init_regulator(dev);

		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosed:
		if (dev->state == XenbusStateClosed)
			break;
	case XenbusStateClosing:
		free_regulators();
		free_ring(dev);
		xenbus_frontend_closed(dev);
		break;

	default:
		if (dev->state != XenbusStateClosed)
			break;
		xenbus_switch_state(dev, XenbusStateInitialising);
		break;
	}
}

static int regif_front_probe(struct xenbus_device *dev,
	const struct xenbus_device_id *id)
{
	struct regif_front_info *info;

	info  = devm_kzalloc(&dev->dev, sizeof(*info), GFP_KERNEL);
	if (!info) {
		return -ENOMEM;
	}

	info->dev = dev;
	mutex_init(&info->lock);
	dev_set_drvdata(&dev->dev, info);

	return 0;
}

static int regif_front_remove(struct xenbus_device *dev)
{
	struct regif_front_info *info = dev_get_drvdata(&dev->dev);

	free_ring(dev);

	kfree(info);
	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}

static const struct xenbus_device_id regif_front_ids[] = {
	{ "vreg" },
	{ "" }
};

static struct xenbus_driver regif_front_driver = {
	.ids    = regif_front_ids,
	.probe  = regif_front_probe,
	.remove = regif_front_remove,
	.otherend_changed = backend_changed,
};

static __init int regif_front_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	//if (xen_initial_domain())
	//    return -ENODEV;

	return xenbus_register_frontend(&regif_front_driver);
}
module_init(regif_front_init);

static __exit void regif_front_exit(void)
{
	 xenbus_unregister_driver(&regif_front_driver);
}
module_exit(regif_front_exit);
