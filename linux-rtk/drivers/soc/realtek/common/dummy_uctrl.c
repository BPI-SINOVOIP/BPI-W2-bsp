/*
 * rtd139x_uctrl.c - Userspace Control Interface for RTD-139x
 *
 * Copyright (C) 2016-2017, Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017  Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "uctrl: " fmt

#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#define RTK_UCTRL_IOCTL_MAGIC 0xEB
#define RTK_UCTRL_IOCTL_NONE _IO(RTK_UCTRL_IOCTL_MAGIC,  0x00)
/* v1.0 */
#define RTK_UCTRL_IOCTL_CLK_EN_TP_SET _IO(RTK_UCTRL_IOCTL_MAGIC, 0x01)
#define RTK_UCTRL_IOCTL_CLK_EN_TP_CLEAR _IO(RTK_UCTRL_IOCTL_MAGIC, 0x02)
#define RTK_UCTRL_IOCTL_CLK_EN_TP_STATE \
	_IOR(RTK_UCTRL_IOCTL_MAGIC, 0x03, unsigned int)
#define RTK_UCTRL_IOCTL_RSTN_TP_SET _IO(RTK_UCTRL_IOCTL_MAGIC,  0x04)
#define RTK_UCTRL_IOCTL_RSTN_TP_CLEAR _IO(RTK_UCTRL_IOCTL_MAGIC,  0x05)
#define RTK_UCTRL_IOCTL_RSTN_TP_STATE \
	_IOR(RTK_UCTRL_IOCTL_MAGIC, 0x06, unsigned int)
/* v1.1 */
#define RTK_UCTRL_IOCTL_GET_VERSION \
	_IOR(RTK_UCTRL_IOCTL_MAGIC, 0x10, unsigned int)
#define RTK_UCTRL_IOCTL_SET \
	_IOW(RTK_UCTRL_IOCTL_MAGIC, 0x11, unsigned int)
#define RTK_UCTRL_IOCTL_CLEAR \
	_IOW(RTK_UCTRL_IOCTL_MAGIC, 0x12, unsigned int)
#define RTK_UCTRL_IOCTL_STATE \
	_IOWR(RTK_UCTRL_IOCTL_MAGIC, 0x13, unsigned int)

static long rtk_uctrl_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	int ret = 0;
	int state = 1;

	switch (cmd) {
	case RTK_UCTRL_IOCTL_CLK_EN_TP_SET:
	case RTK_UCTRL_IOCTL_CLK_EN_TP_CLEAR:
	case RTK_UCTRL_IOCTL_RSTN_TP_SET:
	case RTK_UCTRL_IOCTL_RSTN_TP_CLEAR:
		return -EINVAL;
	case RTK_UCTRL_IOCTL_SET:
	case RTK_UCTRL_IOCTL_CLEAR:
		break;
	default:
		ret = copy_to_user((unsigned int __user *)arg,
			&state, sizeof(unsigned int));
		break;
	}


	return ret;
}

static long rtk_uctrl_compact_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	return rtk_uctrl_ioctl(filp, cmd, (unsigned long)arg);
}

static int rtk_uctrl_open(struct inode *inode, struct file *filp)
{
	return 0;
}


static int rtk_uctrl_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static const struct file_operations rtk_uctrl_fops = {
	.owner          = THIS_MODULE,
	.open           = rtk_uctrl_open,
	.unlocked_ioctl = rtk_uctrl_ioctl,
	.compat_ioctl   = rtk_uctrl_compact_ioctl,
	.release        = rtk_uctrl_release,
};

static struct miscdevice mdev;

static int __init rtk_uctrl_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;

	dev_info(dev, "[UCTRL] %s\n", __func__);

	mdev.minor  = MISC_DYNAMIC_MINOR;
	mdev.name   = "uctrl";
	mdev.fops   = &rtk_uctrl_fops;
	mdev.parent = NULL;

	ret = misc_register(&mdev);
	if (ret) {
		pr_err("Failed to register misc device: %d\n", ret);
		return ret;
	}

	return 0;
}

static const struct of_device_id rtk_uctrl_match[] = {
	{.compatible = "realtek,userspace-control"},
	{}
};

static struct platform_driver rtk_uctrl_driver = {
	.probe = rtk_uctrl_probe,
	.driver = {
		.name = "rtk-uctrl",
		.of_match_table = rtk_uctrl_match,
	},
};

static int __init rtk_uctrl_init(void)
{
	return platform_driver_register(&rtk_uctrl_driver);
}
late_initcall(rtk_uctrl_init);
