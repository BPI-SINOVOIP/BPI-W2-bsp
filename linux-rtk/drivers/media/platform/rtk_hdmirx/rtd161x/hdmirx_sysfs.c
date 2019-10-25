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

#if HDMI_REPEATER_SUPPORT
extern int Get_Hdmi_repeater_mode(void);
extern void Set_Hdmi_repeater_mode(int enable);
#endif

static DEFINE_MUTEX(hdmirx_sysfs_lock);

static const char * const avi_s[] = {
	"No Data", "Overscanned", "Underscanned", "Future"
};

static const char * const avi_b[] = {
	"Bar Data not present", "V Bar Info present",
	"H Bar Info present", "V&H Bar Info present"
};

static const char * const avi_a[] = {
	"No Active Format Information",
	"Active Format Information present"
};

static const char * const avi_y[] = {
	"RGB", "YCbCr4:2:2", "YCbCr4:4:4", "YCbCr4:2:0",
	"Reserved", "Reserved", "Reserved", "IDO-Defined"
};

static const char * const avi_r[] = {
	"No AFD Specified", "Reserved", "Reserved", "Reserved",
	"Greater than 16:9", "Reserved", "Reserved", "Reserved",
	"Same as Picture", "4:3(Center)", "16:9(Center)", "14:9(Center)",
	"Reserved", "4:3 image alternative 14:9 center",
	"16:9 image alternative 14:9 center",
	"16:9 image alternative 4:3 center"
};

static const char * const avi_m[] = {
	"No Data", "4:3", "16:9", "Reserved"
};

static const char * const avi_c[] = {
	"No Data", "SMPTE 170M", "ITU-R BT.709", "Extended Colorimetry"
};

static const char * const avi_sc[] = {
	"Unknown", "Horizontally", "Vertically", "Horizontally & Vertically"
};

static const char * const avi_q[] = {
	"Default", "Limited Range", "Full Rnage", "Reserved"
};

static const char * const avi_ec[] = {
	"xvYCC601", "xvYCC709", "sYCC601", "AdobeYCC601",
	"AdobeRGB", "ITU-R BT.2020 Y'cC'bcC'rc",
	"ITU-R BT.2020 R'G'B' or Y'C'bC'r", "Reserved"
};

static const char * const avi_itc[] = {
	"No data", "IT content"
};

static const char * const avi_pr[] = {
	"No Repetition", "Pixel Data sent 2 times",
	"Pixel Data sent 3 times", "Pixel Data sent 4 times",
	"Pixel Data sent 5 times", "Pixel Data sent 6 times",
	"Pixel Data sent 7 times", "Pixel Data sent 8 times",
	"Pixel Data sent 9 times", "Pixel Data sent 10 times",
	"Reserved", "Reserved",
	"Reserved", "Reserved",
	"Reserved", "Reserved",
};

static const char * const avi_cn[] = {
	"Graphics", "Photo", "Cinema", "Game"
};

static const char * const avi_yq[] = {
	"Limited Range", "Full Range", "Reserved", "Reserved"
};

static const char * const spd_source_info[] = {
	"unknown", "Digital STB", "DVD player", "D-VHS",
	"HDD Videorecorder", "DVC", "DSC", "Video CD",
	"Game", "PC general", "BD Super Audio CD", "HD DVD",
	"PMP", "Reserved", "Reserved", "Reserved"
};

static const char * const audio_cc[] = {
	"Refer to Stream Header", "2 channels", "3 channels", "4 channels",
	"5 channels", "6 channels", "7 channels", "8 channels"
};

static const char * const audio_ct[] = {
	"Refer to Stream Header", "L-PCM", "AC-3", "MPEG-1",
	"MP3", "MPEG2", "AAC LC", "DTS",
	"ATRAC", "One Bit Audio", "Enhanced AC-3", "DTS-HD",
	"MAT", "DST", "WMA Pro", "Refer to Audio CXT"
};

static const char * const audio_ss[] = {
	"Refer to Stream Header", "16 bit", "20 bit", "24 bit"
};

static const char * const audio_sf[] = {
	"Refer to Stream Header", "32 kHz", "44.1 kHz", "48 kHz",
	"88.2 kHz", "96 kHz", "176.4 kHz", "192 kHz"
};

static const char * const drm_eotf[] = {
	"Traditional gamma - SDR Luminance Range",
	"Traditional gamma - HDR Luminance Range",
	"SMPTE ST 2084 [40]",
	"Hybrid Log-Gamma (HLG) based on ITU-R BT.2100-0 [50]",
	"Reserved", "Reserved", "Reserved", "Reserved"
};

static ssize_t hdmirx_edid_version_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", HdmiRx_GetEDID_version()?"2.0":"1.4");
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

static ssize_t hdmirx_edid_version_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
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

static void dump_avi_infoframe(void)
{
	if (hdmi_rx.avi_t.type_code != INFOFRAME_AVI) {
		pr_err("No AVI InfoFrame\n");
		return;
	}

	pr_err("Type Code: 0x%02x\n", hdmi_rx.avi_t.type_code);
	pr_err("Version Number: %u\n", hdmi_rx.avi_t.ver);
	pr_err("Length of InfoFrame: %u\n", hdmi_rx.avi_t.len);
	pr_err("Scan Information: %s\n", avi_s[hdmi_rx.avi_t.S&0x3]);
	pr_err("Bar Data Present: %s\n", avi_b[hdmi_rx.avi_t.B&0x3]);
	pr_err("Active Format Present: %s\n", avi_a[hdmi_rx.avi_t.A&0x1]);
	pr_err("RGB or YCbCr: %s\n", avi_y[hdmi_rx.avi_t.Y&0x7]);
	pr_err("Active Portion Aspect Ratio: %s\n", avi_r[hdmi_rx.avi_t.R&0xF]);
	pr_err("Picture Aspect Ratio: %s\n", avi_m[hdmi_rx.avi_t.M&0x3]);
	pr_err("Colorimetry: %s\n", avi_c[hdmi_rx.avi_t.C&0x3]);
	pr_err("Non-Uniform Picture: %s\n", avi_c[hdmi_rx.avi_t.C&0x3]);
	pr_err("Non-Uniform Picture Scaling: %s\n",
		avi_sc[hdmi_rx.avi_t.SC&0x3]);
	pr_err("RGB Quanitzation Range: %s\n", avi_q[hdmi_rx.avi_t.Q&0x3]);
	pr_err("Extended Colorimetry: %s\n", avi_ec[hdmi_rx.avi_t.EC&0x7]);
	pr_err("IT content: %s\n", avi_itc[hdmi_rx.avi_t.ITC&0x1]);
	pr_err("VIC: %u\n", hdmi_rx.avi_t.VIC);
	pr_err("Pixel Repetition Factor: %s\n", avi_pr[hdmi_rx.avi_t.PR&0xF]);
	pr_err("IT Content Type: %s\n", avi_cn[hdmi_rx.avi_t.CN&0x3]);
	pr_err("YCC Quantization Range: %s\n", avi_yq[hdmi_rx.avi_t.YQ&0x3]);
	pr_err("ETB: %02x%02x\n",
		hdmi_rx.avi_t.ETB15_08, hdmi_rx.avi_t.ETB07_00);
	pr_err("SBB: %02x%02x\n",
		hdmi_rx.avi_t.SBB15_08, hdmi_rx.avi_t.SBB07_00);
	pr_err("ELB: %02x%02x\n",
		hdmi_rx.avi_t.ELB15_08, hdmi_rx.avi_t.ELB07_00);
	pr_err("SRB: %02x%02x\n",
		hdmi_rx.avi_t.SRB15_08, hdmi_rx.avi_t.SRB07_00);
}

static void dump_vsi_infoframe(void)
{
	if (hdmi_rx.vsi_t.type_code != INFOFRAME_VSI) {
		pr_err("No VSI InfoFrame\n");
		return;
	}

	pr_err("Type Code: 0x%02x\n", hdmi_rx.vsi_t.type_code);
	pr_err("Version Number: %u\n", hdmi_rx.vsi_t.ver);
	pr_err("Length of InfoFrame: %u\n", hdmi_rx.vsi_t.len);
	pr_err("IEEE Reg ID: %02x %02x %02x\n",
		hdmi_rx.vsi_t.Reg_ID[0], hdmi_rx.vsi_t.Reg_ID[1],
		hdmi_rx.vsi_t.Reg_ID[2]);
	pr_err("Vendor-Specific Payload:\n");
	pr_err("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
		hdmi_rx.vsi_t.Payload[0], hdmi_rx.vsi_t.Payload[1],
		hdmi_rx.vsi_t.Payload[2], hdmi_rx.vsi_t.Payload[3],
		hdmi_rx.vsi_t.Payload[4], hdmi_rx.vsi_t.Payload[5],
		hdmi_rx.vsi_t.Payload[6], hdmi_rx.vsi_t.Payload[7],
		hdmi_rx.vsi_t.Payload[8], hdmi_rx.vsi_t.Payload[9]);
	pr_err("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
		hdmi_rx.vsi_t.Payload[10], hdmi_rx.vsi_t.Payload[11],
		hdmi_rx.vsi_t.Payload[12], hdmi_rx.vsi_t.Payload[13],
		hdmi_rx.vsi_t.Payload[14], hdmi_rx.vsi_t.Payload[15],
		hdmi_rx.vsi_t.Payload[16], hdmi_rx.vsi_t.Payload[17],
		hdmi_rx.vsi_t.Payload[18], hdmi_rx.vsi_t.Payload[19]);
	pr_err("%02x %02x %02x %02x %02x\n",
		hdmi_rx.vsi_t.Payload[20], hdmi_rx.vsi_t.Payload[21],
		hdmi_rx.vsi_t.Payload[22], hdmi_rx.vsi_t.Payload[23],
		hdmi_rx.vsi_t.Payload[24]);

}

static void dump_spd_infoframe(void)
{
	if (hdmi_rx.spd_t.type_code != INFOFRAME_SPD) {
		pr_err("No SPD InfoFrame\n");
		return;
	}

	pr_err("Type Code: 0x%02x\n", hdmi_rx.spd_t.type_code);
	pr_err("Version Number: %u\n", hdmi_rx.spd_t.ver);
	pr_err("Length of InfoFrame: %u\n", hdmi_rx.spd_t.len);
	pr_err("Vendor Name: %c%c%c%c%c%c%c%c\n",
		hdmi_rx.spd_t.VendorName[0], hdmi_rx.spd_t.VendorName[1],
		hdmi_rx.spd_t.VendorName[2], hdmi_rx.spd_t.VendorName[3],
		hdmi_rx.spd_t.VendorName[4], hdmi_rx.spd_t.VendorName[5],
		hdmi_rx.spd_t.VendorName[6], hdmi_rx.spd_t.VendorName[7]);
	pr_err("Product Description: %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
		hdmi_rx.spd_t.ProductDesc[0], hdmi_rx.spd_t.ProductDesc[1],
		hdmi_rx.spd_t.ProductDesc[2], hdmi_rx.spd_t.ProductDesc[3],
		hdmi_rx.spd_t.ProductDesc[4], hdmi_rx.spd_t.ProductDesc[5],
		hdmi_rx.spd_t.ProductDesc[6], hdmi_rx.spd_t.ProductDesc[7],
		hdmi_rx.spd_t.ProductDesc[8], hdmi_rx.spd_t.ProductDesc[9],
		hdmi_rx.spd_t.ProductDesc[10], hdmi_rx.spd_t.ProductDesc[11],
		hdmi_rx.spd_t.ProductDesc[12], hdmi_rx.spd_t.ProductDesc[13],
		hdmi_rx.spd_t.ProductDesc[14], hdmi_rx.spd_t.ProductDesc[15]);

	if (hdmi_rx.spd_t.SourceInfo < 0xF)
		pr_err("Source Information: %s\n",
			spd_source_info[hdmi_rx.spd_t.SourceInfo]);
	else
		pr_err("Source Information: Reserved\n");

}

static void dump_audio_infoframe(void)
{
	if (hdmi_rx.audiopkt_t.type_code != INFOFRAME_AUDIO) {
		pr_err("No AUDIO InfoFrame\n");
		return;
	}

	pr_err("Type Code: 0x%02x\n", hdmi_rx.audiopkt_t.type_code);
	pr_err("Version Number: %u\n", hdmi_rx.audiopkt_t.ver);
	pr_err("Length of InfoFrame: %u\n", hdmi_rx.audiopkt_t.len);
	pr_err("Audio Channel Count: %s\n",
		audio_cc[hdmi_rx.audiopkt_t.CC&0x7]);
	pr_err("Audio Coding Type: %s\n", audio_ct[hdmi_rx.audiopkt_t.CT&0xF]);
	pr_err("Sample Size: %s\n", audio_ss[hdmi_rx.audiopkt_t.SS&0x3]);
	pr_err("Sample Frequency: %s\n", audio_sf[hdmi_rx.audiopkt_t.SF&0x7]);
	pr_err("CXT: %02x\n", hdmi_rx.audiopkt_t.CXT);
	pr_err("CA: %02x\n", hdmi_rx.audiopkt_t.CA);
	pr_err("LFEPBL: %02x\n", hdmi_rx.audiopkt_t.LFEPBL);
	pr_err("Level Shift Value: %udB\n", hdmi_rx.audiopkt_t.LSV);
	pr_err("DM_INH: %u\n", hdmi_rx.audiopkt_t.DM_INH);
}

static void dump_drm_infoframe(void)
{
	if (hdmi_rx.drm_t.type_code != INFOFRAME_DRM) {
		pr_err("No DRM InfoFrame\n");
		return;
	}

	pr_err("Type Code: 0x%02x\n", hdmi_rx.drm_t.type_code);
	pr_err("Version Number: %u\n", hdmi_rx.drm_t.ver);
	pr_err("Length of InfoFrame: %u\n", hdmi_rx.drm_t.len);
	pr_err("EOTF: %s\n", drm_eotf[hdmi_rx.drm_t.eEOTFtype&0x7]);
	pr_err("Static_Metadata_Descriptor_ID: %u\n", hdmi_rx.drm_t.eMeta_Desc);

	if (hdmi_rx.drm_t.display_primaries_x0 >= 0xC350)
		pr_err("display_primaries_x0: 1.00000\n");
	else
		pr_err("display_primaries_x0: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_x0 * 2);

	if (hdmi_rx.drm_t.display_primaries_y0 >= 0xC350)
		pr_err("display_primaries_y0: 1.00000\n");
	else
		pr_err("display_primaries_y0: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_y0 * 2);

	if (hdmi_rx.drm_t.display_primaries_x1 >= 0xC350)
		pr_err("display_primaries_x1: 1.00000\n");
	else
		pr_err("display_primaries_x1: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_x1 * 2);

	if (hdmi_rx.drm_t.display_primaries_y1 >= 0xC350)
		pr_err("display_primaries_y1: 1.00000\n");
	else
		pr_err("display_primaries_y1: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_y1 * 2);

	if (hdmi_rx.drm_t.display_primaries_x2 >= 0xC350)
		pr_err("display_primaries_x2: 1.00000\n");
	else
		pr_err("display_primaries_x2: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_x2 * 2);

	if (hdmi_rx.drm_t.display_primaries_y2 >= 0xC350)
		pr_err("display_primaries_y2: 1.00000\n");
	else
		pr_err("display_primaries_y2: 0.%05u\n",
			hdmi_rx.drm_t.display_primaries_y2 * 2);

	if (hdmi_rx.drm_t.white_point_x >= 0xC350)
		pr_err("white_point_x: 1.00000\n");
	else
		pr_err("white_point_x: 0.%05u\n",
			hdmi_rx.drm_t.white_point_x * 2);

	if (hdmi_rx.drm_t.white_point_y >= 0xC350)
		pr_err("white_point_y: 1.00000\n");
	else
		pr_err("white_point_y: 0.%05u\n",
			hdmi_rx.drm_t.white_point_y * 2);

	pr_err("max_display_mastering_luminance: %05u cd/m2\n",
			hdmi_rx.drm_t.max_display_mastering_luminance);

	pr_err("max_display_mastering_luminance: %u.%05u cd/m2\n",
			hdmi_rx.drm_t.min_display_mastering_luminance / 10000,
			hdmi_rx.drm_t.min_display_mastering_luminance % 10000);

	pr_err("maximum_content_light_level: %05u cd/m2\n",
			hdmi_rx.drm_t.maximum_content_light_level);

	pr_err("maximum_frame_average_light_level: %05u cd/m2\n",
			hdmi_rx.drm_t.maximum_frame_average_light_level);
}


static ssize_t hdmirx_infoframe_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);

	ret_count = sprintf(buf, "avi: %s\n",
		(hdmi_rx.avi_t.type_code == INFOFRAME_AVI)?"Y":"n");

	ret_count += sprintf(buf + ret_count, "vsi: %s\n",
		(hdmi_rx.vsi_t.type_code == INFOFRAME_VSI)?"Y":"n");

	ret_count += sprintf(buf + ret_count, "spd: %s\n",
		(hdmi_rx.spd_t.type_code == INFOFRAME_SPD)?"Y":"n");

	ret_count += sprintf(buf + ret_count, "audio: %s\n",
		(hdmi_rx.audiopkt_t.type_code == INFOFRAME_AUDIO)?"Y":"n");

	ret_count += sprintf(buf + ret_count, "drm: %s\n",
		(hdmi_rx.drm_t.type_code == INFOFRAME_DRM)?"Y":"n");

	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

static ssize_t hdmirx_infoframe_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	mutex_lock(&hdmirx_sysfs_lock);

	if (sysfs_streq(buf, "avi"))
		dump_avi_infoframe();
	else if (sysfs_streq(buf, "vsi"))
		dump_vsi_infoframe();
	else if (sysfs_streq(buf, "spd"))
		dump_spd_infoframe();
	else if (sysfs_streq(buf, "audio"))
		dump_audio_infoframe();
	else if (sysfs_streq(buf, "drm"))
		dump_drm_infoframe();

	mutex_unlock(&hdmirx_sysfs_lock);

	return size;
}

static ssize_t hdmirx_hdcp1x_en_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);

	ret_count = sprintf(buf, "%s\n",
		(Is_HdmiRx_hdcp1x_enabled() == true)?"Enable":"Disable");

	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

#ifdef CONFIG_RTK_HDCPRX_2P2
static ssize_t hdmirx_hdcp2p2_en_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);

	ret_count = sprintf(buf, "%s\n",
		(Is_HdmiRx_hdcp2p2_enabled() == true)?"Enable":"Disable");

	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}
#endif

static const char * const hdcp_str[] = {
	"None", "Nego1.x", "1.x", "Nego2.2",
	"2.2", "Unknow", "Unknow", "Unknow"
};
static ssize_t hdmirx_hdcp_status_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", hdcp_str[hdmirx_state.hdcp_state&0x7]);
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

#if HDMI_REPEATER_SUPPORT
static ssize_t hdmi_repeater_mode_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	ssize_t ret_count = 0;

	mutex_lock(&hdmirx_sysfs_lock);
	ret_count = sprintf(buf, "%s\n", Get_Hdmi_repeater_mode()?"ON":"OFF");
	mutex_unlock(&hdmirx_sysfs_lock);

	return ret_count;
}

static ssize_t hdmi_repeater_mode_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
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
static DEVICE_ATTR(edid_version, 0644,
	hdmirx_edid_version_show, hdmirx_edid_version_store);
/* /sys/devices/platform/98037000.hdmirx/infoframe */
static DEVICE_ATTR(infoframe, 0644,
	hdmirx_infoframe_show, hdmirx_infoframe_store);
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
static DEVICE_ATTR(repeater_mode, 0644,
	hdmi_repeater_mode_show, hdmi_repeater_mode_store);
#endif

void register_hdmirx_sysfs(struct platform_device *pdev)
{
	device_create_file(&pdev->dev, &dev_attr_edid_version);
	device_create_file(&pdev->dev, &dev_attr_infoframe);

	device_create_file(&pdev->dev, &dev_attr_hdcp1x_en);
#ifdef CONFIG_RTK_HDCPRX_2P2
	device_create_file(&pdev->dev, &dev_attr_hdcp2p2_en);
#endif
	device_create_file(&pdev->dev, &dev_attr_hdcp_status);

#if HDMI_REPEATER_SUPPORT
	device_create_file(&pdev->dev, &dev_attr_repeater_mode);
#endif
}

