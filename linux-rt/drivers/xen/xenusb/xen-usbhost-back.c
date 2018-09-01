/*
 * xen-usbback.c
 *
 * Xen USB backend driver.
 *
 */

#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/usb.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/kref.h>
#include <linux/usb/ch11.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <xen/xen.h>
#include <xen/balloon.h>
#include <xen/events.h>
#include <xen/xenbus.h>
#include <xen/grant_table.h>
#include <xen/page.h>

extern int rtk_usb_host_gpio_power_on(void);
extern int rtk_usb_host_gpio_power_off(void);
extern void evtirq_put(unsigned int irq);

static struct timer_list usbhost_poweron_timer;

struct usbback_info {
	domid_t domid;
	unsigned long handle;
	struct xenbus_device *xbdev;
	unsigned int real_irq;
	unsigned int irq;
	void __iomem *base;
};

static int usbhost_poweron(void)
{
	rtk_usb_host_gpio_power_on();
}

static void usbhost_poweron_init_timer(void)
{
	init_timer(&usbhost_poweron_timer);
	usbhost_poweron_timer.function = usbhost_poweron;
	usbhost_poweron_timer.data = ((unsigned long) 0);
	usbhost_poweron_timer.expires = jiffies + 5*HZ;
	add_timer(&usbhost_poweron_timer);
}

static irqreturn_t usbback_usb_isr(int irq, void *dev_id)
{
        struct usbback_info *info = (struct usbback_info *)dev_id;

	if (info->irq && readl(info->base+0x4)) {
		writel((0x1 << 8) | readl(info->base+0x150), info->base+0x150); /* mask host irq */
		notify_remote_via_irq(info->irq);
	}

        return IRQ_HANDLED;
}

static void usbback_disconnect(struct usbback_info *usbif)
{
	writel((0x1 << 8) | readl(usbif->base+0x150), usbif->base+0x150); /* mask host irq */
	rtk_usb_host_gpio_power_off();
	mdelay(1200);

	return ;
}

static void usbback_free(struct usbback_info *usbif)
{
	kfree(usbif);

	return;
}

static int usbback_remove(struct xenbus_device *dev)
{
	struct usbback_info *usbif = dev_get_drvdata(&dev->dev);

	if (!usbif)
		return 0;

	evtirq_put(usbif->irq);

	usbif->irq = 0;

	free_irq(usbif->real_irq, usbif);

	usbback_free(usbif);

	dev_set_drvdata(&dev->dev, NULL);

	return 0;
}

static struct usbback_info *usbback_alloc(domid_t domid, unsigned long handle)
{
	struct usbback_info *usbif;

	usbif = kzalloc(sizeof(struct usbback_info), GFP_KERNEL);
	if (!usbif)
		return NULL;

	usbif->domid = domid;
	usbif->handle = handle;

	return usbif;
}

static int rtk_dwc3_host_irq_init(struct usbback_info *usbif)
{
	int irq;
        struct device_node *np = NULL;
	int ret = 0;

        np = of_find_node_by_name(NULL, "rtk_dwc3_u2host");
        if(np == NULL) {
                printk(KERN_ERR "get node point fail!!!!!!\n");
		return -1;
        } else {
		irq = irq_of_parse_and_map(np, 0);
		usbif->real_irq = irq;

		usbif->base = of_iomap(np, 0);
		if (!usbif->base) {
			printk(KERN_ERR "base iomap fail.\n");
			return -EINVAL;
		}
        }

        if (request_irq(irq, usbback_usb_isr, IRQF_SHARED, "XEN-USB-HOST", (void *)usbif) < 0)
        {
                printk(KERN_ERR "unable to request irq:%d\n", irq);
		return -1;
        }

	return ret;
}

static int usbback_probe(struct xenbus_device *dev,
			  const struct xenbus_device_id *id)
{
	struct usbback_info *usbif;
	unsigned long handle;
	int ret;

	if (usb_disabled())
		return -ENODEV;

	if (kstrtoul(strrchr(dev->otherend, '/') + 1, 0, &handle))
		return -EINVAL;

	usbif = usbback_alloc(dev->otherend_id, handle);
	if (!usbif) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating backend interface");
		return -ENOMEM;
	}

	ret = rtk_dwc3_host_irq_init(usbif);
	if (ret)
		goto fail;

	usbif->xbdev = dev;
	dev_set_drvdata(&dev->dev, usbif);
	
	ret = xenbus_switch_state(dev, XenbusStateConnected);
	if (ret)
		goto fail;

	return 0;
fail:
	usbback_remove(dev);
	return ret;
}

static int usbback_map(struct usbback_info *usbif,
		      evtchn_port_t evtchn)
{
	int err;

	if (usbif->irq)
		return 0;

	err = bind_interdomain_evtchn_to_irq(usbif->domid, evtchn);
	if (err < 0)
		goto fail_evtchn;

	usbif->irq = err;

	return 0;

fail_evtchn:
	unbind_from_irqhandler(usbif->irq, usbif);
	usbif->irq = 0;

	return err;
}

static int usbback_connect_rings(struct usbback_info *usbif)
{
	struct xenbus_device *dev = usbif->xbdev;
	evtchn_port_t evtchn;
	int err;

	err = xenbus_gather(XBT_NIL, dev->otherend, "event-channel", "%u", &evtchn, NULL);
	if (err) {
		xenbus_dev_fatal(dev, err,
				 "reading %s/ring-ref and event-channel",
				 dev->otherend);
		return err;
	}
	pr_info("xen-pvusb: event-channel %u\n", evtchn);

	err = usbback_map(usbif, evtchn);
	if (err)
		xenbus_dev_fatal(dev, err, "mapping evtchn %u", evtchn);

	writel((readl(usbif->base+0x150) & 0xFFFFFEFF), usbif->base+0x150); /* unmask host irq */

	usbhost_poweron_init_timer();

	return err;
}

static void usbback_frontend_changed(struct xenbus_device *dev,
				     enum xenbus_state frontend_state)
{
	struct usbback_info *usbif = dev_get_drvdata(&dev->dev);

	switch (frontend_state) {
	case XenbusStateInitialised:
	case XenbusStateReconfiguring:
	case XenbusStateReconfigured:
		break;

	case XenbusStateInitialising:
		if (dev->state == XenbusStateClosed) {
			pr_info("xen-pvusb: %s: prepare for reconnect\n",
				dev->nodename);
			xenbus_switch_state(dev, XenbusStateInitWait);
		}
		break;

	case XenbusStateConnected:
		if (dev->state != XenbusStateConnected)
			xenbus_switch_state(dev, XenbusStateConnected);

		if (usbback_connect_rings(usbif))
			break;

		break;

	case XenbusStateClosing:
		usbback_disconnect(usbif);
		xenbus_switch_state(dev, XenbusStateClosing);
		break;

	case XenbusStateClosed:
		xenbus_switch_state(dev, XenbusStateClosed);
		if (xenbus_dev_is_online(dev))
			break;
		/* fall through if not online */
	case XenbusStateUnknown:
		device_unregister(&dev->dev);
		break;

	default:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		break;
	}
}

static const struct xenbus_device_id usbback_ids[] = {
	{ "vusbhost" },
	{ "" },
};

static struct xenbus_driver usbback_driver = {
	.ids			= usbback_ids,
	.probe			= usbback_probe,
	.otherend_changed	= usbback_frontend_changed,
	.remove			= usbback_remove,
};

static int __init usbback_init(void)
{
	int err;

	if (!xen_domain())
		return -ENODEV;

	err = xenbus_register_backend(&usbback_driver);
	if (err)
		goto out_mem;

	return 0;

out_mem:
	return err;
}
module_init(usbback_init);

static void __exit usbback_exit(void)
{
	xenbus_unregister_driver(&usbback_driver);
}
module_exit(usbback_exit);

MODULE_ALIAS("xen-backend:usb-host-irq");
MODULE_AUTHOR("Realtek");
MODULE_DESCRIPTION("Xen USB HOST IRQ backend driver (usbback)");
MODULE_LICENSE("Dual BSD/GPL");
