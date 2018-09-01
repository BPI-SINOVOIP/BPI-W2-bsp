/*
 * compat_hdmitx.c - RTK hdmitx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/compat.h>
#include <linux/fs.h>

#include "compat_hdmitx.h"

#if defined(CONFIG_ARCH_MULTI_V7)
/**
 * compat_hdmitx_ioctl - ioctl function of hdmitx miscdev
 * @file: hdmitx miscdev to be registered
 * @cmd: control command
 * @arg: arguments
 *
 * Return: 0 on success, -E* on failure
 */
long compat_hdmitx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret_value = -EFAULT;

	if (!file->f_op->unlocked_ioctl) {
		ret_value = -ENOTTY;
		goto exit;
	}

	switch (cmd) {
	case HDMI_GET_SINK_CAPABILITY:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_RAW_EDID:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_CHECK_LINK_STATUS:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_VIDEO_CONFIG:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SEND_AVMUTE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_CONFIG_TV_SYSTEM:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_CONFIG_AVI_INFO:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SET_FREQUNCY:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SEND_AUDIO_MUTE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SEND_AUDIO_VSDB_DATA:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SEND_AUDIO_EDID2:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_CHECK_TMDS_SRC:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_CHECK_Rx_Sense:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_EXT_BLK_COUNT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_EXTENDED_EDID:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_QUERY_DISPLAY_STANDARD:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SEND_VOUT_EDID_DATA:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_EDID_SUPPORT_LIST:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_SET_OUTPUT_FORMAT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;

	case HDMI_GET_OUTPUT_FORMAT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;
	case HDMI_SET_VO_INTERFACE_TYPE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd, arg);
		break;
	default:
		ret_value = -EFAULT;
	}

exit:
	return ret_value;
}
#else
/**
 * compat_hdmitx_ioctl - ioctl function of hdmitx miscdev
 * @file: hdmitx miscdev to be registered
 * @cmd: control command
 * @arg: arguments
 *
 * Return: 0 on success, -E* on failure
 */
long compat_hdmitx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret_value = -EFAULT;

	if (!file->f_op->unlocked_ioctl) {
		ret_value = -ENOTTY;
		goto exit;
	}

	switch (cmd) {
	case HDMI_GET_SINK_CAPABILITY:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_RAW_EDID:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_CHECK_LINK_STATUS:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_VIDEO_CONFIG:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SEND_AVMUTE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_CONFIG_TV_SYSTEM:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_CONFIG_AVI_INFO:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SET_FREQUNCY:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SEND_AUDIO_MUTE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SEND_AUDIO_VSDB_DATA:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SEND_AUDIO_EDID2:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_CHECK_TMDS_SRC:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_CHECK_Rx_Sense:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_EXT_BLK_COUNT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_EXTENDED_EDID:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_QUERY_DISPLAY_STANDARD:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SEND_VOUT_EDID_DATA:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_EDID_SUPPORT_LIST:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_SET_OUTPUT_FORMAT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;

	case HDMI_GET_OUTPUT_FORMAT:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;
	case HDMI_SET_VO_INTERFACE_TYPE:
		ret_value = file->f_op->unlocked_ioctl(file, cmd,
						(unsigned long)compat_ptr(arg));
		break;
	default:
		ret_value = -EFAULT;
	}

exit:
	return ret_value;
}
#endif /* CONFIG_ARCH_MULTI_V7 */

