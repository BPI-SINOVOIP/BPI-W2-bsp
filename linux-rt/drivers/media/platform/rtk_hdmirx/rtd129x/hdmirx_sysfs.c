/*
 * hdmirx_sysfs.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "v4l2_hdmi_dev.h"
#include "hdmiEDID.h"
#ifdef CONFIG_RTK_HDCPRX_2P2
#include "hdmirx_hdcp2p2.h"
#endif

#include "rx_drv/hdmiInternal.h"

extern HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;
#if HDMI_REPEATER_SUPPORT
extern int Get_Hdmi_repeater_mode(void);
extern void Set_Hdmi_repeater_mode(int enable);
#endif

static DEFINE_MUTEX(hdmirx_sysfs_lock);

static ssize_t hdmirx_edid_version_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", HdmiRx_GetEDID_version()?"2.0":"1.4");
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

static ssize_t hdmirx_edid_version_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	mutex_lock(&hdmirx_sysfs_lock);
	if (sysfs_streq(buf, "1.4"))
		HdmiRx_SetEDID_version(0);
	else if (sysfs_streq(buf, "2.0"))
		HdmiRx_SetEDID_version(1);
	else
		HDMIRX_ERROR("Set EDID version fail, unknown version\n");
	mutex_unlock(&hdmirx_sysfs_lock);
	return size;
}

static ssize_t hdmirx_hdcp1x_en_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", (Is_HdmiRx_hdcp1x_enabled() == true)?"Enable":"Disable");
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

#ifdef CONFIG_RTK_HDCPRX_2P2
static ssize_t hdmirx_hdcp2p2_en_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char *hdcp2p2_str[] = {"Disable", "Enable"};
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	if (Is_HdmiRx_hdcp2p2_enabled() == true)
		ret_count = sprintf(buf, "%s\n", hdcp2p2_str[1]);
	else
		ret_count = sprintf(buf, "%s\n", hdcp2p2_str[0]);
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}
#endif

static ssize_t hdmirx_hdcp_status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char *hdcp_str[] = {"None", "Nego1.x", "1.x", "Nego2.2", "2.2", "Unknow", "Unknow", "Unknow"};
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", hdcp_str[hdmi_ioctl_struct.hdcp_state&0x7]);
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

#if HDMI_REPEATER_SUPPORT
static ssize_t hdmi_repeater_mode_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", Get_Hdmi_repeater_mode()?"ON":"OFF");
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

static ssize_t hdmi_repeater_mode_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
	mutex_lock(&hdmirx_sysfs_lock);
	if (sysfs_streq(buf, "ON") || sysfs_streq(buf, "on"))
		Set_Hdmi_repeater_mode(1);
	else if (sysfs_streq(buf, "OFF") || sysfs_streq(buf, "off"))
		Set_Hdmi_repeater_mode(0);
	else
		HDMIRX_ERROR("Set repeater mode fail, unknown mode\n");
	mutex_unlock(&hdmirx_sysfs_lock);
	return size;
}
#endif

/* /sys/devices/platform/98037000.hdmirx/edid_version */
static DEVICE_ATTR(edid_version, 0644, hdmirx_edid_version_show, hdmirx_edid_version_store);
/* /sys/devices/platform/98037000.hdmirx/hdcp1x_en */
static DEVICE_ATTR(hdcp1x_en, 0444, hdmirx_hdcp1x_en_show, NULL);
#ifdef CONFIG_RTK_HDCPRX_2P2
/* /sys/devices/platform/98037000.hdmirx/hdcp2p2_en */
static DEVICE_ATTR(hdcp2p2_en, 0444, hdmirx_hdcp2p2_en_show, NULL);
#endif
/* /sys/devices/platform/98037000.hdmirx/hdcp_status */
static DEVICE_ATTR(hdcp_status, 0444, hdmirx_hdcp_status_show, NULL);
#if HDMI_REPEATER_SUPPORT
/* /sys/devices/platform/98037000.hdmirx/repeater_mode */
static DEVICE_ATTR(repeater_mode, 0644, hdmi_repeater_mode_show, hdmi_repeater_mode_store);
#endif

void register_hdmirx_sysfs(struct platform_device *pdev)
{
	device_create_file(&pdev->dev, &dev_attr_edid_version);

	device_create_file(&pdev->dev, &dev_attr_hdcp1x_en);
#ifdef CONFIG_RTK_HDCPRX_2P2
	device_create_file(&pdev->dev, &dev_attr_hdcp2p2_en);
#endif
	device_create_file(&pdev->dev, &dev_attr_hdcp_status);

#if HDMI_REPEATER_SUPPORT
	device_create_file(&pdev->dev, &dev_attr_repeater_mode);
#endif
}

