#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/types.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "xencec.h"

static struct cec_front_info *front_info = NULL;

static long xen_cec_ioctl( struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct miscdevice *mdev = filp->private_data;
	struct cec_front_info *info = front_info;
	void *dev = dev_get_drvdata(mdev->this_device);;

	if (!dev)
		return -ENODEV;
	
	switch (cmd) {
	case CEC_ENABLE:
	case CEC_SET_RX_MASK:
	case CEC_SET_LOGICAL_ADDRESS:
	case CEC_SET_PHYSICAL_ADDRESS:
	case CEC_SET_STANDBY_MODE:
	case CEC_SET_CEC_VERSION:
	case CEC_SET_DEVICE_VENDOR_ID:
	case CEC_SET_RETRY_NUM:
		return cec_front_set_param(info, dev, cmd, arg);
	default:
		return -1;
	}
}

long xen_cec_compat_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct miscdevice *mdev = filp->private_data;
	struct cec_front_info *info = front_info;
	void *dev = dev_get_drvdata(mdev->this_device);
	cec_msg  msg;
	char data[CEC_CMB_LENGTH];
	unsigned int temp[4];
	int ret=0;

	if (!dev)
		return -ENODEV;
	if (!filp->f_op->unlocked_ioctl)
		return -ENOTTY;

	switch(cmd) {
	case CEC_ENABLE:
	case CEC_SET_RX_MASK:
	case CEC_SET_LOGICAL_ADDRESS:
	case CEC_SET_PHYSICAL_ADDRESS:
	case CEC_SET_STANDBY_MODE:
	case CEC_SET_CEC_VERSION:
	case CEC_SET_DEVICE_VENDOR_ID:
	case CEC_SET_RETRY_NUM:
		ret = filp->f_op->unlocked_ioctl(filp, cmd,
				(unsigned long)compat_ptr(arg));
		break;
	case CEC_SEND_MESSAGE:
		if (copy_from_user(&temp, (void __user *)arg, sizeof(cec_msg)))
			return -EFAULT;
		msg.buf = (unsigned char *)(unsigned long)temp[0];
		msg.len = (unsigned char)temp[1];
		if(msg.len >= CEC_CMB_LENGTH) {
			pr_err("%s: length overflow\n", __func__);
			return -EFAULT;
		}
		if (copy_from_user(data, (unsigned char __user *)compat_ptr((unsigned long)msg.buf), msg.len))
			return -EFAULT;
		ret = cec_front_send_message(info, dev, data, msg.len);
		break;
	case CEC_RCV_MESSAGE:
		if (copy_from_user(&temp, (void __user *)arg, sizeof(cec_msg)))
			return -EFAULT;
		msg.buf = (unsigned char *)(unsigned long)temp[0];
		msg.len = (unsigned char)temp[1];
		ret = cec_front_rcv_message(info, dev, data, msg.len);
		if (ret<0)
			return -EFAULT;
		if (copy_to_user((unsigned char __user *)msg.buf, data, ret))
			return -EFAULT;
		break;
	default:
		return -EFAULT;
	}
	return ret;
}

int xen_cec_open(struct inode *inode, struct file *filp)
{
	struct miscdevice *dev = filp->private_data;
	struct cec_front_info *info = front_info;
	const char *msg;
	char path[CEC_NAME_LENGTH];
	void *devptr = NULL;

	msg = "nonseekable open";
	if (nonseekable_open(inode, filp))
		goto fail;

	msg = "cec_front_open";
	sprintf(path, "/dev/%s", dev->name);
//	sprintf(path, "/dev/cec-0");
	devptr = cec_front_open(info, path);
	if(!devptr)
		goto fail;
	dev_set_drvdata(dev->this_device, devptr);

	return 0;
fail:
	pr_err("%s: fail at %s\n", __func__, msg);
	return -1;
}

const struct file_operations xen_cec_fops = {
	.owner		= THIS_MODULE,
	.open		= xen_cec_open,
	.unlocked_ioctl	= xen_cec_ioctl,
	.compat_ioctl	= xen_cec_compat_ioctl,
	.poll		= NULL,
};

struct miscdevice cecdev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "cec-0",
	.fops = &xen_cec_fops,
};

static int xen_cec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const char *msg;

	msg = "register misc dev";
	if (misc_register(&cecdev))
		goto fail;
	
	return 0;
fail:
	dev_err(dev, "%s: fail at %s\n", __func__, msg);
	return -1; 
}

static const struct of_device_id xen_cec_ids[] = {
	{ .compatible = "xen,cec", },
	{},
};
MODULE_DEVICE_TABLE(of, xen_cec_ids);

static struct platform_driver xen_cec_driver = {
	.probe = xen_cec_probe,
	.driver = {
		.name = "xen_cec",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(xen_cec_ids),
	},
};

int xen_cec_register(struct cec_front_info *info)
{
	const char *msg;

	msg = "platform_driver_register";
	if (platform_driver_register(&xen_cec_driver))
		goto fail;

	front_info = info;
	return 0;
fail:
	pr_err("%s: fail at %s\n", __func__, msg);
	return -1;
}

void xen_cec_unregister(void)
{
	if(front_info != NULL)
		platform_driver_unregister(&xen_cec_driver);
	front_info = NULL;
}

