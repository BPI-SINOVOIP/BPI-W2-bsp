/*
 * xen-usbfront.c
 *
 * Xen USB Virtual Host Controller driver
 *
 */

#include <linux/module.h>
#include <linux/usb.h>
#include <linux/list.h>
#include <linux/usb/hcd.h>
#include <linux/io.h>
#include <xen/xen.h>
#include <xen/xenbus.h>
#include <xen/grant_table.h>
#include <xen/events.h>
#include <xen/page.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>

#define DEVICETREE_NODENAME	"rtk_dwc3_u2host"

#ifdef CONFIG_PM
int port1_pow_gpio = -1;
int port2_pow_gpio = -1;
bool power_low_active;
#endif

struct usbfront_info {
	struct xenbus_device *xbdev;
	evtchn_port_t evtchn;
	int irq;
};

int rtk_xen_usb_host_irq = 0;
EXPORT_SYMBOL(rtk_xen_usb_host_irq);

static void __iomem *host_regs = NULL;
void rtk_hostirq_unmask(void)
{
        if(host_regs) {
                writel((readl(host_regs+0x150) & 0xFFFFFEFF), host_regs+0x150);
        }
}
EXPORT_SYMBOL(rtk_hostirq_unmask);

static void *xenusb_unflatten_dt_alloc(void **mem, unsigned long size,
                                       unsigned long align)
{
        void *res;

        *mem = PTR_ALIGN(*mem, align);
        res = *mem;
        *mem += size;

        return res;
}

static struct property * create_new_property(char* name, void *value, int value_len)
{
        struct property *new_prop;
        void *mem;
        int malloc_size = 0;

        malloc_size = strlen(name)+1;
        malloc_size += value_len;
        malloc_size += sizeof(struct property);

        mem = kzalloc(malloc_size + 4, GFP_KERNEL);
        memset(mem, 0, malloc_size + 4);
        new_prop = xenusb_unflatten_dt_alloc(&mem, sizeof(struct property),
                                        __alignof__(struct property));
        new_prop->value = xenusb_unflatten_dt_alloc(&mem, value_len, 1);
        new_prop->name = (char*)xenusb_unflatten_dt_alloc(&mem, strlen(name)+1, 1);

        memcpy(new_prop->value, value, value_len);
        new_prop->length = value_len;
        strcpy(new_prop->name, name);

        return new_prop;
}

static void usbfront_destroy_rings(struct usbfront_info *info)
{
	if (info->irq) {
		info->irq = 0;
	}
}

static int usbfront_setup_rings(struct xenbus_device *dev,
				struct usbfront_info *info)
{
	int err;
	struct device_node *np;
        struct property *prop;
        const char *str;
        const char *str2;

	err = xenbus_alloc_evtchn(dev, &info->evtchn);
	if (err) {
		xenbus_dev_fatal(dev, err, "xenbus_alloc_evtchn");
		goto fail;
	}

	err = bind_evtchn_to_irq(info->evtchn);
	if (err <= 0) {
		xenbus_dev_fatal(dev, err, "bind_evtchn_to_irq");
		goto fail;
	}

	info->irq = err;

	rtk_xen_usb_host_irq = info->irq;

	np = of_find_node_by_name(NULL, DEVICETREE_NODENAME);
        if(np != NULL) {
                of_property_read_string(np, "status", &str);
                prop = create_new_property("status", "okay", sizeof("okay"));
                of_update_property(np, prop);
		of_property_read_string(np, "status", &str2);

                err = of_platform_populate(np, NULL, NULL, NULL);
                if (err) {
                        printk(KERN_ERR "%s() failed to add dwc3 core.\n", __func__);
                }
        }	

	return 0;

fail:
	usbfront_destroy_rings(info);

	return err;
}

static int usbfront_talk_to_backend(struct xenbus_device *dev,
				    struct usbfront_info *info)
{
	const char *message;
	struct xenbus_transaction xbt;
	int err;

	err = usbfront_setup_rings(dev, info);
	if (err)
		return err;

again:
	err = xenbus_transaction_start(&xbt);
	if (err) {
		xenbus_dev_fatal(dev, err, "starting transaction");
		goto destroy_ring;
	}

	err = xenbus_printf(xbt, dev->nodename, "event-channel", "%u",
			    info->evtchn);
	if (err) {
		message = "writing event-channel";
		goto abort_transaction;
	}

	err = xenbus_transaction_end(xbt, 0);
	if (err) {
		if (err == -EAGAIN)
			goto again;
		xenbus_dev_fatal(dev, err, "completing transaction");
		goto destroy_ring;
	}

	return 0;

abort_transaction:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, err, "%s", message);

destroy_ring:
	usbfront_destroy_rings(info);

	return err;
}

static int usbfront_connect(struct xenbus_device *dev)
{
	struct usbfront_info *info = dev_get_drvdata(&dev->dev);
	int err;

	err = usbfront_talk_to_backend(dev, info);
	if (err)
		return err;

	return 0;
}

static void usbfront_disconnect(struct xenbus_device *dev)
{
	struct usbfront_info *info = dev_get_drvdata(&dev->dev);

	if (info->irq) {
		evtchn_put(info->evtchn);
		info->irq = 0;
	}

	if (info->evtchn) {
		xenbus_free_evtchn(dev, info->evtchn);
		info->evtchn = 0;
	}

	xenbus_frontend_closed(dev);
}

static void usbfront_backend_changed(struct xenbus_device *dev,
			    enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateInitialising:
	case XenbusStateReconfiguring:
	case XenbusStateReconfigured:
	case XenbusStateUnknown:
		break;

	case XenbusStateInitWait:
	case XenbusStateInitialised:
	case XenbusStateConnected:
		if (dev->state != XenbusStateInitialising)
			break;
		if (!usbfront_connect(dev))
			xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosed:
		if (dev->state == XenbusStateClosed)
			break;
		/* Missed the backend's Closing state -- fallthrough */
	case XenbusStateClosing:
		usbfront_disconnect(dev);
		break;

	default:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 backend_state);
		break;
	}
}

static int usbfront_remove(struct xenbus_device *dev)
{
	struct usbfront_info *info = dev_get_drvdata(&dev->dev);

	usbfront_destroy_rings(info);

        kfree(info);

        dev_set_drvdata(&dev->dev, NULL);

	return 0;
}

static struct usbfront_info *usbfront_alloc(domid_t domid)
{
        struct usbfront_info *info;

        info = kzalloc(sizeof(struct usbfront_info), GFP_KERNEL);
        if (!info)
                return NULL;

        return info;
}

static int usbfront_probe(struct xenbus_device *dev,
			  const struct xenbus_device_id *id)
{
	struct usbfront_info *info;

	if (usb_disabled())
		return -ENODEV;

	info = usbfront_alloc(dev->otherend_id);
        if (!info) {
                xenbus_dev_fatal(dev, -ENOMEM, "allocating frontend interface");
                return -ENOMEM;
        }

	dev->dev.driver_data = info;

	dev_set_drvdata(&dev->dev, info);

	host_regs = ioremap(0x98013C00, 0x200);
	
	return 0;
}

static const struct xenbus_device_id usbfront_ids[] = {
	{ "vusbhost" },
	{ "" },
};

static struct xenbus_driver usbfront_driver = {
	.ids			= usbfront_ids,
	.probe			= usbfront_probe,
	.otherend_changed	= usbfront_backend_changed,
	.remove			= usbfront_remove,
};

static int rtk_usbhost_frontend_probe(struct platform_device *pdev)
{
        struct device_node *np;

        np = of_find_node_by_name(NULL, "rtk_usb_power_manager");
        if(np == NULL) {
                printk(KERN_ERR "get usb-manager node point fail!!!!!!\n");
        } else {
		port1_pow_gpio = of_get_named_gpio(np, "realtek,port1-power-gpio", 0);
		if (gpio_is_valid(port1_pow_gpio)) {
			printk(KERN_INFO "%s get port1-power-gpio (id=%d) OK\n", __func__, port1_pow_gpio);
		} else {
			printk(KERN_INFO "port1-power-gpio no found\n");
		}

		port2_pow_gpio = of_get_named_gpio(np, "realtek,port2-power-gpio", 0);
		if (gpio_is_valid(port2_pow_gpio)) {
			printk(KERN_INFO "%s get port2-power-gpio (id=%d) OK\n", __func__, port2_pow_gpio);
		} else {
			printk(KERN_INFO "port2-power-gpio no found\n");
		}

		if (of_property_read_bool(np, "power_low_active"))
			power_low_active = true;
		else
			power_low_active = false;
	}

	if (!xen_domain())
		return -ENODEV;

	return xenbus_register_frontend(&usbfront_driver);
}

static int rtk_usbhost_frontend_remove(struct platform_device *pdev)
{
	xenbus_unregister_driver(&usbfront_driver);

	return 0;
}

static struct platform_device rtk_usbhost_frontend_device = {
	.name = "rtk-usbhost-frontend",
};

#ifdef CONFIG_PM
static void rtk_usbport_power_on_off(bool on)
{
	if (gpio_is_valid(port1_pow_gpio)) {
                if (gpio_request(port1_pow_gpio, "port1_pow_gpio"))
                        printk(KERN_ERR "%s ERROR Request port1_pow_gpio (id=%d) fail\n", __func__, port1_pow_gpio);
                else if (port1_pow_gpio != -1) {
                        if (gpio_direction_output(port1_pow_gpio, power_low_active?!on:on)) {
                                printk(KERN_INFO "%s ERROR port1 power %s fail\n", __func__, on?"on":"off");
                        } else {
                                printk(KERN_INFO "%s to set port1 power %s by gpio (id=%d) OK\n", __func__, on?"on":"off", port1_pow_gpio);
                        }
                        gpio_free(port1_pow_gpio);
                }
        }

	if (gpio_is_valid(port2_pow_gpio)) {
                if (gpio_request(port2_pow_gpio, "port2_pow_gpio"))
                        printk(KERN_ERR "%s ERROR Request port1_pow_gpio (id=%d) fail\n", __func__, port2_pow_gpio);
                else if (port2_pow_gpio != -1) {
                        if (gpio_direction_output(port2_pow_gpio, power_low_active?!on:on)) {
                                printk(KERN_INFO "%s ERROR port2 power %s fail\n", __func__, on?"on":"off");
                        } else {
                                printk(KERN_INFO "%s to set port2 power %s by gpio (id=%d) OK\n", __func__, on?"on":"off", port2_pow_gpio);
                        }
                        gpio_free(port2_pow_gpio);
                }
        }

	return;
}

static int rtk_usbhost_frontend_pm_suspend(struct device *dev)
{
	int ret = 0;

	rtk_usbport_power_on_off(false);

	return ret;
}

static int rtk_usbhost_frontend_pm_resume(struct device *dev)
{
	int ret = 0;

	rtk_usbport_power_on_off(true);

	return ret;
}

static const struct dev_pm_ops rtk_usbhost_frontend_pm_ops = {
        SET_SYSTEM_SLEEP_PM_OPS(rtk_usbhost_frontend_pm_suspend, rtk_usbhost_frontend_pm_resume)
};
#endif

static struct platform_driver rtk_usbhost_frontend_driver = {
	.driver = {
		.name  = "rtk-usbhost-frontend",
		.owner = THIS_MODULE,
#ifdef CONFIG_PM
                .pm = &rtk_usbhost_frontend_pm_ops,
#endif

	},
        .probe = rtk_usbhost_frontend_probe,
        .remove = rtk_usbhost_frontend_remove,
};

static int __init usbfront_init(void)
{
	int err;

	err = platform_device_register(&rtk_usbhost_frontend_device);
	if (err) {
		printk(KERN_ERR "%s(#%d): platform_device_register failed(%d)\n", __func__, __LINE__, err);
		return err;
	}

	err = platform_driver_register(&rtk_usbhost_frontend_driver);
	if (err) {
		printk(KERN_ERR "%s(#%d): platform_driver_register fail(%d)\n", __func__, __LINE__, err);
		goto dev_reg_fail;
	}

	return err;

dev_reg_fail:
	platform_device_unregister(&rtk_usbhost_frontend_device);

	return err;
}
module_init(usbfront_init);

static void __exit usbfront_exit(void)
{
	platform_device_unregister(&rtk_usbhost_frontend_device);
	platform_driver_unregister(&rtk_usbhost_frontend_driver);
}
module_exit(usbfront_exit);


MODULE_ALIAS("xen-frontend:usb-host-irq");
MODULE_AUTHOR("Realtek");
MODULE_DESCRIPTION("Xen USB HOST IRQ frontend driver (usbfront)");
MODULE_LICENSE("Dual BSD/GPL");

