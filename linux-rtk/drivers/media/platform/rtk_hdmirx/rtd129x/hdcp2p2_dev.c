/*
 * hdmirx_hdcp2p2_dev.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/miscdevice.h>

#include "hdcp2p2_dev.h"
#include "hdmirx_hdcp2p2.h"
#include "v4l2_hdmi_dev.h"


struct miscdevice hdcp2p2_mdev;

int hdcp2p2_open(struct inode *inode, struct file *filp)
{
	if (nonseekable_open(inode, filp))
		return -ENODEV;

	return 0;
}

long hdcp2p2_ioctl(struct file *fd, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	unsigned long ret_val;

	HDMIRX_DEBUG("[HDCP2.2]ioctl TYPE(0x%x) NR(%u) SIZE(%u)",
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));

	ret_val = -ENOTTY;

	switch (cmd) {
	case HDCP22IOC_INIT:
		init_hdcp2p2_waitqueue();
		ret_val = 0;
		break;
	case HDCP22IOC_GET_HDCP22_MSG:
		ret_val = get_hdcp2p2_msg(argp);
		break;
	case HDCP22IOC_WRITE_DATA_TO_TX:
		ret_val = write_hdcp2p2_msg_to_tx(argp);
		break;
	case HDCP22IOC_GET_STREAM_MSG:
		ret_val = get_stream_msg(argp);
		break;
	case HDCP22IOC_SET_KS:
		ret_val = set_hdcp2p2_ks(argp);
		break;
	case HDCP22IOC_CLR_MSG_DONE:
		Clear_Hdmi_hdcp_2_2_Read_Status();
		ret_val = 0;
		break;
	case HDCP22IOC_GET_MSG_DONE:
		ret_val = get_hdcp2p2_msg_done(argp);
		break;
	case HDCP22IOC_SET_STATUS_READY:
		Set_Rx_status_Ready();
		ret_val = 0;
		break;
	case HDCP22IOC_SET_DOWNSTREAM_DONE:
		DownStream_done();
		ret_val = 0;
		break;
	case HDCP22IOC_SET_SWITCH_STATE:
		ret_val = set_hdcp2p2_switch_state(argp);
		break;
	default:
		HDMIRX_ERROR("[HDCP2.2]Unknown ioctl TYPE(0x%x) NR(%u) SIZE(%u)",
			_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));
		break;
	}

	return ret_val;
}

long compat_hdcp2p2_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	if (!file->f_op->unlocked_ioctl)
		return -ENOTTY;
	else
		return file->f_op->unlocked_ioctl(file, cmd, (unsigned long)compat_ptr(arg));
}

const struct file_operations rxhdcp2p2_fops = {
	.owner = THIS_MODULE,
	.open = hdcp2p2_open,
	.unlocked_ioctl = hdcp2p2_ioctl,
	.compat_ioctl = compat_hdcp2p2_ioctl,
};

void register_hdcp2p2_device(void)
{

	hdcp2p2_mdev.minor = MISC_DYNAMIC_MINOR;
	hdcp2p2_mdev.name = "rxhdcp2p2";
	hdcp2p2_mdev.mode = 0666;
	hdcp2p2_mdev.fops = &rxhdcp2p2_fops;

	if (misc_register(&hdcp2p2_mdev))
		HDMIRX_ERROR("[HDCP2.2]Register misc dev fail");
}

