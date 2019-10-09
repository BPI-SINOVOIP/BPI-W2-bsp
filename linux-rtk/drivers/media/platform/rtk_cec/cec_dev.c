/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "cec.h"
#include "cec_dev.h"

#define MAX_CEC_CNT	4
static cec_dev node_list[MAX_CEC_CNT];
static dev_t devno_base;
static struct class *cec_dev_class;

void *get_cecdev_from_node(struct inode *inode)
{
	unsigned int i = iminor(inode);
	void *dev = NULL;

	if (!node_list[i].device)
		return NULL;

	dev = dev_get_drvdata(node_list[i].device);

	return dev;
}

int create_cec_dev_node(cec_device *device)
{
	int i;

	for (i = 0; i < MAX_CEC_CNT; i++) {
		if (node_list[i].device != NULL)
			continue;
		if (cdev_add(&node_list[i].cdev, devno_base + i, 1) < 0) {
			pr_err("cec err : register character dev failed\n");
			return -1;
		}
		node_list[i].device = device_create(
				cec_dev_class,
				NULL,
				devno_base + i,
				device,
				"cec-%d",
				i);
		return 0;
	}
	return -1;
}

void remove_cec_dev_node(cec_device *device)
{
	int i = 0;

	for (i = 0; i < MAX_CEC_CNT; i++) {
		if (node_list[i].device &&
			dev_get_drvdata(node_list[i].device) == (void *)device) {
			device_destroy(cec_dev_class, devno_base + i);
			cdev_del(&node_list[i].cdev);
			node_list[i].device = NULL;
		}
	}
}

static int cec_dev_open(struct inode *inode, struct file *file)
{
	unsigned int i = iminor(inode);
	cec_device *dev;

	if (!node_list[i].device)
		return -ENODEV;

	dev = (cec_device *)dev_get_drvdata(node_list[i].device);

	if (dev) {
		file->private_data = dev;
		return 0;
	}
	return -ENODEV;
}

static int cec_dev_release(struct inode *inode, struct file *file)
{
	unsigned int i = iminor(inode);
	cec_device *dev;
	cec_driver *drv;

	if (node_list[i].device) {
		dev = (cec_device *)dev_get_drvdata(node_list[i].device);
		drv = (cec_driver *)to_cec_driver(dev->dev.driver);
		drv->enable(dev, 0xf0);
	}
	return 0;
}

static long cec_dev_ioctl(struct file *file, unsigned int cmd,
						unsigned long arg)
{
	cec_device *dev = (cec_device *) file->private_data;
	cec_driver *drv;
	cec_msg  msg;
	cm_buff *cmb = NULL;
	int len;
	unsigned short rx_mask;
	unsigned int result;

	if (!dev)
		return -ENODEV;

	drv = (cec_driver *)to_cec_driver(dev->dev.driver);

	switch (cmd) {
	case CEC_ENABLE:
		dev_info(&dev->dev, "ioctl - ENABLE\n");
		return drv->enable(dev, (arg) ? 1 : 0);

	case CEC_SET_RX_MASK:
		dev_info(&dev->dev, "ioctl - SET_RX_MASK\n");
		return drv->set_rx_mask(dev, (unsigned short) arg | 0x8000);

	case CEC_SET_LOGICAL_ADDRESS:
		dev_info(&dev->dev, "ioctl - SET_LOGICAL_ADDRESS\n");

		rx_mask = (unsigned char) arg;
		if (rx_mask > 0xF) {
			dev_err(&dev->dev,
				"invalid logical address %d\n", rx_mask);
			return -EFAULT;
		}
		rx_mask = (1 << rx_mask);
		return drv->set_rx_mask(dev, rx_mask | 0x8000);

	case CEC_SET_PHYSICAL_ADDRESS:
		dev_info(&dev->dev, "ioctl - SET_PHYSICAL_ADDRESS\n");
		return drv->set_physical_addr(dev, (unsigned short) arg);

	case CEC_GET_PHYSICAL_ADDRESS:
		dev_info(&dev->dev, "ioctl - GET_PHYSICAL_ADDRESS\n");
		return drv->get_physical_addr(dev);

	case CEC_SEND_MESSAGE:
		dev_info(&dev->dev, "ioctl - SEND_MESSAGE\n");
		if (copy_from_user(&msg, (cec_msg __user *)arg, sizeof(msg)))
			return -EFAULT;

		cmb = alloc_cmb(msg.len);
		if (cmb == NULL)
			return -ENOMEM;
		if (copy_from_user(cmb_put(cmb, msg.len),
			(unsigned char __user *)msg.buf, msg.len))
			return -EFAULT;

		return drv->xmit(dev, cmb, 0);

	case CEC_RCV_MESSAGE:
		if (copy_from_user(&msg, (cec_msg __user *)arg, sizeof(msg)))
			return -EFAULT;
		cmb = drv->read(dev, (file->f_flags & O_NONBLOCK) ? NONBLOCK : 0);
		if (!cmb)
			return -EFAULT;

		if (cmb->len > msg.len) {
			dev_err(&dev->dev,
				"rcv failed, msg size %d, buffer size %d\n",
				cmb->len, msg.len);
			kfree_cmb(cmb);
			return -ENOMEM;
		}
		len = cmb->len;
		result = copy_to_user((unsigned char __user *)msg.buf,
					cmb->data, cmb->len) ? -EFAULT : 0;
	/*	if (result < 0) {
			dev_err(&dev->dev, "copy msg to user failed\n");
			kfree_cmb(cmb);
			return result;
		}*/
		kfree_cmb(cmb);
		return len;

	case CEC_SET_STANDBY_MODE:
		return drv->set_stanby_mode(dev, (unsigned long) arg);

	case CEC_SET_CEC_VERSION:
		return drv->set_cec_version(dev, (unsigned char) arg);

	case CEC_SET_DEVICE_VENDOR_ID:
		return drv->set_device_vendor_id(dev, (unsigned long) arg);

	case CEC_SET_RETRY_NUM:
		return drv->set_retry_num(dev, (unsigned long) arg);
	default:
		dev_err(&dev->dev, "unknown ioctl cmd %08x\n", cmd);
		return -EFAULT;
	}
}
#ifdef CONFIG_64BIT
long cec_dev_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long (*ioctl)(struct file*, unsigned int, unsigned long);
	cec_device *dev = (cec_device *)file->private_data;
	cec_driver *drv;
	cec_msg  msg;
	cm_buff *cmb = NULL;
	unsigned int temp[4];
	int len;
	unsigned int result;

	if (!dev)
		return -ENODEV;

	drv = (cec_driver *)to_cec_driver(dev->dev.driver);

	if (!file->f_op->unlocked_ioctl)
		return -ENOTTY;
	ioctl = file->f_op->unlocked_ioctl;

	switch (cmd) {
	case CEC_ENABLE:
	case CEC_SET_RX_MASK:
	case CEC_SET_LOGICAL_ADDRESS:
	case CEC_SET_PHYSICAL_ADDRESS:
		return ioctl(file, cmd, (unsigned long)compat_ptr(arg));

	case CEC_SEND_MESSAGE:
		if (copy_from_user(&temp, (void __user *)arg, sizeof(msg)))
			return -EFAULT;
		msg.buf = (unsigned char *)(unsigned long)temp[0];
		msg.len = (unsigned char)temp[1];

		cmb = alloc_cmb(msg.len);
		if (cmb == NULL)
			return -ENOMEM;

		if (copy_from_user(cmb_put(cmb, msg.len),
			(unsigned char __user *)compat_ptr((unsigned long)msg.buf),
			msg.len))
			return -EFAULT;
		return drv->xmit(dev, cmb, 0);

	case CEC_RCV_MESSAGE:
		if (copy_from_user(&temp, (cec_msg __user *)compat_ptr(arg),
					sizeof(msg)))
			return -EFAULT;
		msg.buf = (unsigned char *)(unsigned long)temp[0];
		msg.len = (unsigned char)temp[1];

		cmb = drv->read(dev, (file->f_flags & O_NONBLOCK) ? NONBLOCK : 0);
		if (!cmb)
			return -EFAULT;
		if (cmb->len > msg.len) {
			dev_err(&dev->dev,
				"rcv failed, msg size %d, buffer size %d\n",
				cmb->len, msg.len);
			kfree_cmb(cmb);
			return -ENOMEM;
		}
		len = cmb->len;
		result = copy_to_user((unsigned char __user *) msg.buf,
					cmb->data, cmb->len) ? -EFAULT : 0;
/*		if (result < 0) {
			dev_err(&dev->dev, "copy msg to user failed\n");
			kfree_cmb(cmb);
			return result;
		}*/
		kfree_cmb(cmb);
		return len;

	case CEC_SET_STANDBY_MODE:
	case CEC_SET_CEC_VERSION:
	case CEC_SET_DEVICE_VENDOR_ID:
	case CEC_SET_RETRY_NUM:
		return ioctl(file, cmd, (unsigned long)compat_ptr(arg));

	default:
		return -EFAULT;
	}
}
#endif
static const struct file_operations cec_dev_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl	= cec_dev_ioctl,
	.open = cec_dev_open,
	.release = cec_dev_release,
#ifdef CONFIG_64BIT
	.compat_ioctl = cec_dev_compat_ioctl,
#endif
};

static int __init cec_dev_module_init(void)
{
	int i;
	unsigned int result = 0;

	if (alloc_chrdev_region(&devno_base, 0, MAX_CEC_CNT, "cec") != 0)
		return -EFAULT;

	for (i = 0; i < MAX_CEC_CNT; i++) {
		cdev_init(&node_list[i].cdev, &cec_dev_fops);
		node_list[i].device = NULL;
	}

	cec_dev_class = class_create(THIS_MODULE, "cec-dev");

	if (IS_ERR(cec_dev_class)) {
		result = PTR_ERR(cec_dev_class);
		goto err_create_class_failed;
	}
	return 0;

err_create_class_failed:
	unregister_chrdev_region(devno_base, MAX_CEC_CNT);
	return result;
}

static void __exit cec_dev_module_exit(void)
{
	int i = 0;
	cec_device *dev;

	for (i = 0; i < MAX_CEC_CNT; i++) {
		if (!node_list[i].device)
			continue;
		dev = dev_get_drvdata(node_list[i].device);
		remove_cec_dev_node(dev);
	}

	unregister_chrdev_region(devno_base, MAX_CEC_CNT);
	class_destroy(cec_dev_class);
}

module_init(cec_dev_module_init);
module_exit(cec_dev_module_exit);
