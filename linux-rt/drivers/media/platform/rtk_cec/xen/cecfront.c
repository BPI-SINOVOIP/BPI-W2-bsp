#include <linux/module.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <xen/xen.h>
#include <xen/events.h>
#include <xen/xenbus.h>
#include <xen/grant_table.h>
#include "xencec.h"

static inline struct cec_request *ring_new_req(struct cec_front_info *info)
{
	struct cec_request *req;

	req = RING_GET_REQUEST(&info->ring, info->ring.req_prod_pvt);
	info->ring.req_prod_pvt++;
	req->req_id = info->req_id++;
	return req;
}

static inline void ring_push_req(struct cec_front_info *info)
{
	int notify;
	info->wait_done = 0;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&info->ring, notify);
	if (notify)
		notify_remote_via_irq(info->irq);
}

static inline int ring_wait_rsp(struct cec_front_info *info)
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

static inline struct cec_response * ring_get_rsp(struct cec_front_info *info)
{
	struct cec_response *rsp;
	int more_to_do;

	rsp = RING_GET_RESPONSE(&info->ring, info->ring.rsp_cons++);
again:
	RING_FINAL_CHECK_FOR_RESPONSES(&info->ring, more_to_do);
	if (more_to_do) {
		struct cec_response *rsp_1 =
			RING_GET_RESPONSE(&info->ring, info->ring.rsp_cons++);
		pr_info("multiple response\n");
		pr_info("rsp_id  = %d\n", rsp_1->rsp_id);
		pr_info("req_id  = %d\n", rsp_1->req_id);
//		pr_info("op      = %s\n", regif_op_string(rsp_1->op));
		pr_info("rdev_id = %d\n", rsp_1->rdev_id);
		pr_info("retval  = %d\n", rsp_1->retval);
		pr_info("errval  = %d\n", rsp_1->errval);

		goto again;
	}
	return rsp;
}

static struct cec_response *ring_send_req_ang_get_rsp(struct cec_front_info *info)
{
	ring_push_req(info);
	if (ring_wait_rsp(info) < 0)
		return NULL;
	return ring_get_rsp(info);
}

int cec_front_set_param(struct cec_front_info *info, void *dev,
				unsigned int cmd, unsigned long arg)
{
	struct cec_request *req;
	struct cec_response *rsp;
	
	mutex_lock(&info->lock);
	req = ring_new_req(info);
	switch (cmd) {
	case CEC_ENABLE:
		req->op = CEC_OP_ENABLE;
		break;
	case CEC_SET_RX_MASK:
		req->op = CEC_OP_SET_RXMASK;
		break;
	case CEC_SET_LOGICAL_ADDRESS:
		req->op = CEC_OP_SET_LOGICAL;
		break;
	case CEC_SET_PHYSICAL_ADDRESS:
		req->op = CEC_OP_SET_PHYSICAL;
		break;
	case CEC_SET_STANDBY_MODE:
		req->op = CEC_OP_STANDBY;
		break;
	case CEC_SET_CEC_VERSION:
		req->op = CEC_OP_CEC_VER;
		break;
	case CEC_SET_DEVICE_VENDOR_ID:
		req->op = CEC_OP_VENDER_ID;
		break;
	case CEC_SET_RETRY_NUM:
		req->op = CEC_OP_RETRY_NUM;
		break;
	}
	req->arg = arg;
	req->dev = dev;
	rsp = ring_send_req_ang_get_rsp(info);
	mutex_unlock(&info->lock);
	if (!rsp)
		return -1;
	return 0;
}

int cec_front_send_message(struct cec_front_info *info, void *dev, char *data, int len)
{
	struct cec_request *req;
	struct cec_response *rsp;

	mutex_lock(&info->lock);

	req = ring_new_req(info);
	req->op = CEC_OP_SEND_MSG;
	memcpy(req->data, data, len);
	req->len = len;
	req->dev = dev;
	rsp = ring_send_req_ang_get_rsp(info);

	mutex_unlock(&info->lock);

	if (!rsp)
		return -1;
	return rsp->retval;
}

int cec_front_rcv_message(struct cec_front_info *info, void *dev, char *data, int len)
{
	struct cec_request *req;
	struct cec_response *rsp;

	mutex_lock(&info->lock);

	req = ring_new_req(info);
	req->op = CEC_OP_RCV_MSG;
	req->len = len;
	req->dev = dev;
	rsp = ring_send_req_ang_get_rsp(info);

	mutex_unlock(&info->lock);
	if (!rsp)
		return -1;
	if (rsp->retval<0)
		return rsp->retval;
	
	memcpy(data, rsp->data, rsp->retval);
	return rsp->retval;
}

void *cec_front_open(struct cec_front_info *info, char *path)
{
	const char *msg;
	struct cec_request *req;
	struct cec_response *rsp;

	msg = "get::open";
	req = ring_new_req(info);
	req->op = CEC_OP_OPEN;
	strcpy(req->cec_name, path);
	rsp = ring_send_req_ang_get_rsp(info);
	if (!rsp)
		goto fail;

	return rsp->ptr;
fail:
	pr_err("%s: fail at %s\n", __func__, msg);
	return NULL;
}

static irqreturn_t cec_front_interrupt(int irq, void *dev_id)
{
	struct cec_front_info *info = dev_id;

	info->wait_done = 1;
	return IRQ_HANDLED;
}

static void free_ring(struct xenbus_device *dev)
{
	struct cec_front_info *info = dev_get_drvdata(&dev->dev);

	if (info->irq) {
		unbind_from_irqhandler(info->irq, info);
		info->irq = 0;
	}

	if (info->evtchn) {
		xenbus_free_evtchn(dev, info->evtchn);
		info->evtchn = 0;
	}

	if (info->ring_ref != 0) {
		gnttab_end_foreign_access(info->ring_ref, 0, 
				(unsigned long)info->ring.sring);
		info->ring_ref = 0;
	}
	info->connected = 0;
}

static int setup_ring(struct xenbus_device *dev)
{
	struct cec_front_info *info = dev_get_drvdata(&dev->dev);
	struct cec_sring *sring;
	unsigned long ring_size = PAGE_SIZE;
	int err;
	grant_ref_t gref;
	const char *msg;

	sring = (struct cec_sring *)__get_free_pages
			(GFP_NOIO | __GFP_HIGH, get_order(ring_size));
	if (!sring)
		return -ENOMEM;
	
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
	err = bind_evtchn_to_irqhandler(info->evtchn, 
			cec_front_interrupt, 0, "cec-frontend", info);
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
	struct cec_front_info *info = dev_get_drvdata(&dev->dev);
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
	err = xenbus_printf(xbt, dev->nodename, "event-channel"
						, "%u", info->evtchn);
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
	struct cec_front_info __maybe_unused *info = dev_get_drvdata(&dev->dev);

	pr_info("cec %s: BE %s FE %s\n", __func__,
		xenbus_strstate(backend_state), xenbus_strstate(dev->state));
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
		xen_cec_register(info);
		xenbus_switch_state(dev, XenbusStateConnected);
		break;
	case XenbusStateClosed:
		if (dev->state == XenbusStateClosed)
			break;
	case XenbusStateClosing:
		free_ring(dev);
		xenbus_frontend_closed(dev);
		break;
	default:
		pr_err("cec %s: not support\n", __func__);
		break;
	}
}

static int cec_front_probe(struct xenbus_device *dev,
			const struct xenbus_device_id *id)
{
	struct cec_front_info *info;
    
	info  = devm_kzalloc(&dev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = dev;
	mutex_init(&info->lock);
	dev_set_drvdata(&dev->dev, info);
	return 0;
}

static int cec_front_remove(struct xenbus_device *dev)
{
	struct cec_front_info *info = dev_get_drvdata(&dev->dev);

	free_ring(dev);
	kfree(info);
	dev_set_drvdata(&dev->dev, NULL);
	return 0;
}

static const struct xenbus_device_id cec_front_ids[] = {
	{ "cec" },
	{ "" }
};

static struct xenbus_driver cec_front_driver = {
	.ids    = cec_front_ids,
	.probe  = cec_front_probe,
	.remove = cec_front_remove,
	.otherend_changed = backend_changed,
};

static int __init cec_front_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	return xenbus_register_frontend(&cec_front_driver);
}
module_init(cec_front_init);

static void __exit cec_front_exit(void)
{
	xenbus_unregister_driver(&cec_front_driver);
}
module_exit(cec_front_exit);

