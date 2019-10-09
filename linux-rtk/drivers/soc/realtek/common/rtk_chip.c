/*
 * rtk_chip.c - chip info ioctl
 *
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>

#include <soc/realtek/rtk_chip.h>

#define RTK_CHIP_IOCTL_GET_ID  _IOR('C', 0x01, unsigned int)
#define RTK_CHIP_IOCTL_GET_REV _IOR('C', 0x02, unsigned int)

static long rtk_chip_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	int ret = 0;
	unsigned int val;

	switch (cmd) {
	case RTK_CHIP_IOCTL_GET_ID:
		val = get_rtd_chip_id();
		break;
	case RTK_CHIP_IOCTL_GET_REV:
		val = get_rtd_chip_revision();
		break;
	}

	ret = copy_to_user((unsigned int __user *)arg,
		&val, sizeof(unsigned int));

	return ret;
}

static long rtk_chip_compact_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	return rtk_chip_ioctl(filp, cmd, (unsigned long)arg);
}

static const struct file_operations rtk_chip_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = rtk_chip_ioctl,
	.compat_ioctl   = rtk_chip_compact_ioctl,
};

static struct miscdevice mdev = {
	.minor  = MISC_DYNAMIC_MINOR,
	.name   = "chip",
	.fops   = &rtk_chip_fops,
};

static int __init chip_info_init(void)
{
	int ret;

	ret = misc_register(&mdev);
	if (ret)
		pr_err("Failed to register misc device: %d\n", ret);
	return ret;
}
module_init(chip_info_init);
