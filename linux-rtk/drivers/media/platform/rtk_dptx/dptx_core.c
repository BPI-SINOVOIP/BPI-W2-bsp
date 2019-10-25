/*
 *  dptx_core.c - RTK display port driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/reset.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#include "dptx_core.h"
#include "dptx_aux_channel.h"

#define DPTX_RES_MAX 0xFF
#define EDID_SIZE 256
static int dptxHpdDetect = 0;
extern struct ion_device *rtk_phoenix_ion_device;

const char dptx_kylin_support_vic[] = {
	VIC_1280X720P60,
	VIC_1920X1080P60,
	VIC_3840X2160P30,
	VIC_3840X2160P60,
};

const char dptx_thor_support_vic[] = {
	VIC_1280X720P60,
	VIC_1920X1080P60,
	VIC_3840X2160P30,
	VIC_1024X768P60,
	VIC_1440X768P60,
	VIC_1440X900P60,
	VIC_1280X800P60,
	VIC_960X544P60,
};

static void rtk_hdmi_power_on(void)
{
	void __iomem *chk_reg;
	unsigned int i;

	chk_reg = ioremap(0x98000190, 0x1);
	writel(0x11a, chk_reg);
	for(i = 0; i < 4096 ; i++);
	writel(0x1be, chk_reg);
	for(i = 0; i < 4096 ; i++);
	writel(0xbf, chk_reg);
	for(i = 0; i < 4096 ; i++);
	iounmap(chk_reg);
}

static int rtk_tveint_en(struct rtk_dptx_device *dptx_dev, int en)
{
	struct device *dev = dptx_dev->dev;
	void  __iomem *tve_reg;
	void  __iomem *vdac_reg;
	unsigned int reg, reg1;
	bool clken;
	int ret = -1;

	/* check tve clock enable or not */
	clken = __clk_is_enabled(dptx_dev->tve_clk);
	if(!clken) {
		dev_info(dev, "tve clock is disable, ignore\n");
		return ret;
	}

	tve_reg = ioremap(0x9801801c, 0x1);
	vdac_reg = ioremap(0x980183a0, 0x1);
	reg = readl(tve_reg);

	if((reg & 0x4) && !en) {
		reg1 = readl(vdac_reg);
		reg1 = reg1 & ~0x40000000;
		writel(reg1, vdac_reg);
		writel(0x4, tve_reg);
		ret = 0;
	} else if(!(reg & 0x4) && en) {
		writel(0x5, tve_reg);
		ret = 0;
	}
	iounmap(tve_reg);
	iounmap(vdac_reg);
	if(ret < 0)
		dev_info(dev, "tve interrupt = 0x%x, ignore\n", reg);
	return ret;
}

static void rtk_dptx_disable(struct rtk_dptx_device *dptx_dev)
{
	int ret;

	dptx_dev->dptx_en = 0;
	ret = reset_control_status(dptx_dev->lvds_rst);
	if (ret)
		return;
	rtk_tveint_en(dptx_dev, 0);
	dptx_lvdsint_en(&dptx_dev->hwinfo, 0);
	msleep(20);

	dptx_close_phy(&dptx_dev->hwinfo);
	reset_control_assert(dptx_dev->lvds_rst);
	dptx_close_pll(&dptx_dev->hwinfo);
}

static void rtk_dptx_enable(struct rtk_dptx_device *dptx_dev)
{
	int ret = 0;
	int status;

	status = reset_control_status(dptx_dev->lvds_rst);
	if (!status) {
		ret = rtk_tveint_en(dptx_dev, 0);
		dptx_lvdsint_en(&dptx_dev->hwinfo, 0);
		msleep(20);

		dptx_close_phy(&dptx_dev->hwinfo);
		reset_control_assert(dptx_dev->lvds_rst);
		dptx_close_pll(&dptx_dev->hwinfo);
	}

	dptx_pixelpll_setting(&dptx_dev->hwinfo);
	reset_control_deassert(dptx_dev->lvds_rst);

	dptx_dppll_setting(&dptx_dev->hwinfo);
	dptx_initial(&dptx_dev->hwinfo);

	if(!status && ret == 0)
		rtk_tveint_en(dptx_dev, 1);

	dptx_dev->dptx_en = 1;
}

static unsigned int vic_to_vo_standard(struct rtk_dptx_hwinfo *hwinfo,
			unsigned char vic)
{
	unsigned int standard;

	switch(vic) {
	case VIC_1280X720P60:
		hwinfo->out_type = DP_FORMAT_720P_60;
		standard = VO_STANDARD_DP_FORMAT_1280_720P_60;
		break;
	case VIC_1920X1080P60:
		hwinfo->out_type = DP_FORMAT_1080P_60;
		standard = VO_STANDARD_DP_FORMAT_1920_1080P_60;
		break;
	case VIC_3840X2160P30:
		hwinfo->out_type = DP_FORMAT_2160P_30;
		standard = VO_STANDARD_DP_FORMAT_2160P_30;
		break;
	case VIC_3840X2160P60:
		hwinfo->out_type = DP_FORMAT_2160P_60;
		standard = VO_STANDARD_DP_FORMAT_3840_2160P_60;
		break;
	case VIC_1024X768P60:
		hwinfo->out_type = DP_FORMAT_1024_768;
		standard = VO_STANDARD_DP_FORMAT_1024_768P_60;
		break;
	case VIC_1440X768P60:
		hwinfo->out_type = DP_FORMAT_1440_768;
		standard = VO_STANDARD_DP_FORMAT_1440_768P_60;
		break;
	case VIC_1440X900P60:
		hwinfo->out_type = DP_FORMAT_1440_900;
		standard = VO_STANDARD_DP_FORMAT_1440_900P_60;
		break;
	case VIC_1280X800P60:
		hwinfo->out_type = DP_FORMAT_1280_800;
		standard = VO_STANDARD_DP_FORMAT_1280_800P_60;
		break;
	case VIC_960X544P60:
		hwinfo->out_type = DP_FORMAT_960_544;
		standard = VO_STANDARD_DP_FORMAT_960_544P_60;
		break;
	default:
		hwinfo->out_type = DP_FORMAT_1024_768;
		standard = VO_STANDARD_DP_FORMAT_1024_768P_60;
		break;
	}
	return standard;
}

static unsigned char vo_standard_to_vic(unsigned int vo)
{
	switch(vo) {
	case VO_STANDARD_DP_FORMAT_1280_720P_60:
		return VIC_1280X720P60;
	case VO_STANDARD_DP_FORMAT_1920_1080P_60:
		return VIC_1920X1080P60;
	case VO_STANDARD_DP_FORMAT_2160P_30:
		return VIC_3840X2160P30;
	case VO_STANDARD_DP_FORMAT_3840_2160P_60:
		return VIC_3840X2160P60;
	case VO_STANDARD_DP_FORMAT_1024_768P_60:
		return VIC_1024X768P60;
	case VO_STANDARD_DP_FORMAT_1440_768P_60:
		return VIC_1440X768P60;
	case VO_STANDARD_DP_FORMAT_1440_900P_60:
		return VIC_1440X900P60;
	case VO_STANDARD_DP_FORMAT_1280_800P_60:
		return VIC_1280X800P60;
	case VO_STANDARD_DP_FORMAT_960_544P_60:
		return VIC_960X544P60;
	default:
		return VIC_1280X720P60;
	}
}

void gen_dptx_format_support(struct rtk_dptx_device *dptx_dev,
				struct sink_capabilities_t *sink_cap)
{
	struct dptx_support_list *list = &dptx_dev->list;
	struct dptx_format_support *support = list->tx_support;
	struct device *dev = dptx_dev->dev;
	int i;
	unsigned long long vic;
	unsigned char extended_vic;
	unsigned long long vic2;
	unsigned long long vic2_420;
	int offset;
	int size;
	const char *support_vic;

	vic = sink_cap->vic;
	extended_vic = sink_cap->extended_vic;
	vic2 = sink_cap->vic2;
	vic2_420 = sink_cap->vic2_420;

	memset(support, 0, sizeof(struct dptx_support_list));
	/* SD 16:9->4:3 */
	if (vic & BIT(2))
		vic |= BIT(1);
	if (vic & BIT(6))
		vic |= BIT(5);
	if (vic & BIT(17))
		vic |= BIT(16);
	if (vic & BIT(21))
		vic |= BIT(20);

	/* Merge extended_vic to vic2 */
	if (extended_vic & BIT(1))
		vic2 |= BIT(30);
	if (extended_vic & BIT(2))
		vic2 |= BIT(29);
	if (extended_vic & BIT(3))
		vic2 |= BIT(28);
	if (extended_vic & BIT(4))
		vic2 |= BIT(33);

	if (dptx_dev->hwinfo.chip_id == CHIP_ID_RTD1619) {
		size = sizeof(dptx_thor_support_vic);
		support_vic = dptx_thor_support_vic;
	} else {
		size = sizeof(dptx_kylin_support_vic);
		support_vic = dptx_kylin_support_vic;
	}
	offset = 0;
	for (i=0; i<size; i++) {
		if (support_vic[i] <= 64) {
			if (vic & BIT(support_vic[i]-1)) {
				dev_info(dev, "support vic = %d\n", support_vic[i]);
				support[offset].vic = support_vic[i];
				offset++;
			}
		} else {
			if (vic2 & BIT(support_vic[i]-64)) {
				dev_info(dev, "dptx support vic = %d\n", support_vic[i]);
				support[offset].vic = support_vic[i];
				offset++;
			} else if (vic2_420 & BIT(support_vic[i]-65)) {
				dev_info(dev, "dptx support vic = %d\n", support_vic[i]);
				support[offset].vic = support_vic[i];
				offset++;
			}
		}
	}
	list->tx_support_size = offset;
}

static long rtk_dptx_ioctl(struct file* filp, 
			unsigned int cmd, unsigned long arg)
{
	struct rtk_dptx_device *dptx_dev = filp->private_data;
	struct rtk_dptx_hwinfo *hwinfo = &dptx_dev->hwinfo;
	struct device *dev = dptx_dev->dev;
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM rpc;
	struct dptx_format_setting *format = &dptx_dev->format;
	struct dptx_support_list *list = &dptx_dev->list;
	struct edid *edid;
	asoc_dptx_t* cap = &dptx_dev->cap;
	int mode;
	int value;
	int ret;

	switch(cmd) {
	case DPTX_CONFIG_TV_SYSTEM:
		if (copy_from_user(&rpc, (void __user *)arg, sizeof(rpc))) {
			dev_err(dev, "[%s] failed to copy from user !\n", __func__);
			return -EFAULT;
		}
		mode = rpc.videoInfo.pedType;
		switch(mode) {
		case VO_STANDARD_DP_FORMAT_1920_1080P_60:
			hwinfo->out_type = DP_FORMAT_1080P_60;
			break;
		case VO_STANDARD_DP_FORMAT_2160P_30:
			hwinfo->out_type = DP_FORMAT_2160P_30;
			break;
		case VO_STANDARD_DP_FORMAT_3840_2160P_60:
			hwinfo->out_type = DP_FORMAT_2160P_60;
			break;
		case VO_STANDARD_DP_FORMAT_1280_720P_60:
			hwinfo->out_type = DP_FORMAT_720P_60;
			break;
		case VO_STANDARD_DP_FORMAT_1024_768P_60:
			hwinfo->out_type = DP_FORMAT_1024_768;
			break;
		}
		rtk_dptx_enable(dptx_dev);
		if(dptx_config_tv_system(&dptx_dev->hwinfo) == true)
			RPC_TOAGENT_DPTX_Config_TV_System(dptx_dev->rpc_ion_client, &rpc);
		break;

	case DPTX_GET_SINK_CAPABILITY:
	case DPTX_GET_RAW_EDID:
	case DPTX_GET_EDID_SUPPORT_LIST:
		if (!dptx_dev->dptx_en)
			rtk_dptx_enable(dptx_dev);
		if (dptx_dev->ignore_edid)
			return -EFAULT;
		if (!dptx_dev->ignore_edid && !(cap->sink_cap_available)) {
			ret = dptx_read_edid(&dptx_dev->hwinfo, cap->edid_ptr, EDID_SIZE);
			if (ret < 0) {
				dev_err(dev, "Read EDID fail\n");
				return -EFAULT;
			}
			edid = (struct edid *)cap->edid_ptr;
			memset(&cap->sink_cap, 0, sizeof(struct sink_capabilities_t));
			dptx_add_edid_modes(edid, &cap->sink_cap);
			cap->sink_cap_available = true;
		}

		if(cmd == DPTX_GET_SINK_CAPABILITY) {
			if(copy_to_user((void __user *)arg, &cap->sink_cap, sizeof(cap->sink_cap))) {
				dev_err(dev, "[%s] failed to copy to user !\n", __func__);
				return -EFAULT;
			}
		} else if (cmd == DPTX_GET_RAW_EDID) {
			if(copy_to_user((void __user *)arg, &cap->edid_ptr, EDID_SIZE)) {
				dev_err(dev, "[%s] failed to copy to user !\n", __func__);
				return -EFAULT;
			}
		} else {
			gen_dptx_format_support(dptx_dev, &dptx_dev->cap.sink_cap);
			if (copy_to_user((void __user *)arg, list, sizeof(struct dptx_support_list))) {
				dev_err(dev, "[%s] failed to copy to user !\n", __func__);
				return -EFAULT;
			}
		}
		break;
	case DPTX_GET_OUTPUT_FORMAT:
		RPC_TOAGENT_DPTX_QUERY_TV_System(dptx_dev->rpc_ion_client, &rpc);
		format->vic = vo_standard_to_vic(rpc.videoInfo.pedType);
		format->display_mode = rpc.interfaceType;
		dev_info(dev, "dptx format vic = %d, display_mode = %d\n", format->vic, format->display_mode);

		if (copy_to_user((void __user *)arg, format, sizeof(struct dptx_format_setting))) {
			dev_err(dev, "[%s] failed to copy to user !\n", __func__);
			return -EFAULT;
		}
		break;
	case DPTX_SET_OUTPUT_FORMAT:
		if (copy_from_user(format, (void __user *)arg, sizeof(format))) {
			dev_err(dev, "[%s] copy from user fail\n", __func__);
			break;
		}
		RPC_TOAGENT_DPTX_QUERY_TV_System(dptx_dev->rpc_ion_client, &rpc);

		rpc.videoInfo.pedType = vic_to_vo_standard(hwinfo, format->vic);
		rpc.interfaceType = format->display_mode;
		dev_info(dev, "dptx set format vo = %d, display_mode = %d\n", rpc.videoInfo.pedType, rpc.interfaceType);
		if (rpc.interfaceType < VO_DISPLAY_PORT_ONLY ||
			rpc.interfaceType > VO_HDMI_AND_DP_DIFF_SOURCE_WITH_CVBS)
		{
			rtk_dptx_disable(dptx_dev);
			RPC_TOAGENT_DPTX_Config_TV_System(dptx_dev->rpc_ion_client, &rpc);
			return 0;
		}
		rtk_dptx_enable(dptx_dev);
		if(dptx_config_tv_system(&dptx_dev->hwinfo) == true)
			RPC_TOAGENT_DPTX_Config_TV_System(dptx_dev->rpc_ion_client, &rpc);
		break;
	case DPTX_HOTPLUG_DETECTION:
		if (copy_from_user(&value, (void __user *)arg, sizeof(value))) {
			DPTX_ERR("%s:failed to copy from user !", __func__);
			return -EFAULT;
		}

		dptxHpdDetect = value;
		if(value == 0)
		{
			dptx_dev->isr_signal = true;
			wake_up_interruptible(&dptx_dev->hpd_wait);
		}
		return ret;
	case DPTX_WAIT_HOTPLUG:
		value = dptx_switch_get_state(&dptx_dev->swdev);
		wait_event_interruptible(dptx_dev->hpd_wait, (((dptx_dev->isr_signal == true)&&(value!=switch_get_state(&dptx_dev->swdev.sw))) || (!dptxHpdDetect)));
		dptx_dev->isr_signal = false;
		value = dptx_switch_get_state(&dptx_dev->swdev);
		if (copy_to_user((void __user *)arg,&value,sizeof(value))) {
			DPTX_ERR("%s:failed to copy to user ! ", __func__);
			return -EFAULT;
		}

		return ret;
	default:
		dev_err(dev, "[%s] unknown ioctl cmd %08x\n", __func__, cmd);
		return -EFAULT;
	}
	return 0;
}

#ifdef CONFIG_64BIT
static long rtk_dptx_compat_ioctl(struct file* filp,
			unsigned int cmd, unsigned long arg)
{
	long (*ioctl)(struct file*, unsigned int, unsigned long);

	if (!filp->f_op->unlocked_ioctl)
		return -ENOTTY;

	ioctl = filp->f_op->unlocked_ioctl;

	switch(cmd) {
	case DPTX_GET_SINK_CAPABILITY:
	case DPTX_GET_RAW_EDID:
	case DPTX_CONFIG_TV_SYSTEM:
	case DPTX_GET_EDID_SUPPORT_LIST:
	case DPTX_GET_OUTPUT_FORMAT:
	case DPTX_SET_OUTPUT_FORMAT:
		return ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
	default:
		break;
	}
	return 0;
}
#endif /* end of CONFIG_64BIT */

static ssize_t rtk_dptx_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *pos)
{
	struct rtk_dptx_device *dptx_dev = filp->private_data;
	struct device *dev = dptx_dev->dev;
	char resolution;

	if (!dptx_dev->selftest)
		return count;
	if (copy_from_user(&resolution, (void __user *)buf, sizeof(char))) {
		dev_err(dev, "[%s] failed to copy from user !\n", __func__);
		return -EFAULT;
	}

	if (resolution == '0') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_720P_60;
	} else if (resolution == '1') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_1080P_60;
	} else if (resolution == '2') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_1024_768;
	} else if (resolution == '3') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_1280_800;
	} else if (resolution == '4') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_1440_768;
	} else if (resolution == '5') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_1440_900;
	} else if (resolution == '6') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_960_544;
	} else if (resolution == '7') {
		dptx_dev->hwinfo.out_type = DP_FORMAT_2160P_30;
	} else {
		dev_err(dev, "'0' = DP_FORMAT_720P_60\n");
		dev_err(dev, "'1' = DP_FORMAT_1080P_60\n");
		dev_err(dev, "'2' = DP_FORMAT_1024_768\n");
		dev_err(dev, "'3' = DP_FORMAT_1280_800\n");
		dev_err(dev, "'4' = DP_FORMAT_1440_768\n");
		dev_err(dev, "'5' = DP_FORMAT_1440_900\n");
		dev_err(dev, "'6' = DP_FORMAT_960_544\n");
		dev_err(dev, "'7' = DP_FORMAT_2160P_30\n");
		return count;
	}

	rtk_dptx_enable(dptx_dev);
	dptx_config_tv_system(&dptx_dev->hwinfo);

	return count;
}

int rtk_dptx_open(struct inode *inode, struct file *filp)
{
	struct miscdevice *misc = filp->private_data;
	struct rtk_dptx_device *dptx_dev =
			container_of(misc, struct rtk_dptx_device, miscdev);

	if (nonseekable_open(inode, filp))
		return -ENODEV;

	filp->private_data = dptx_dev;
	
	return 0;
}

static struct file_operations dptx_fops = {
	.owner = THIS_MODULE,
	.open = rtk_dptx_open,
	.write = rtk_dptx_write,
	.unlocked_ioctl = rtk_dptx_ioctl,
#ifdef CONFIG_64BIT
	.compat_ioctl = rtk_dptx_compat_ioctl,
#endif /* end of CONFIG_64BIT */
};

static irqreturn_t rtk_dptx_isr(int irq, void *dev_id)
{
	struct rtk_dptx_device *dptx_dev = (struct rtk_dptx_device *)dev_id;

	dptx_aux_irq_handle(&dptx_dev->hwinfo);

	return IRQ_HANDLED;
}

static int rtk_dptx_probe(struct platform_device *pdev)
{
	struct rtk_dptx_device *dptx_dev;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct reset_control *rstc;
	struct clk *clk;
	int i, idx;
	unsigned char *edid_ptr;
	unsigned int irq;

	dev_info(dev, "[%s] start\n", __func__);

	dptx_dev = devm_kzalloc(dev, sizeof(struct rtk_dptx_device), GFP_KERNEL);
	if (IS_ERR(dptx_dev))
		return PTR_ERR(dptx_dev);

	edid_ptr = devm_kzalloc(dev, sizeof(unsigned char)*EDID_SIZE, GFP_KERNEL);
	if (IS_ERR(edid_ptr))
		return PTR_ERR(edid_ptr);

	dev->platform_data = dptx_dev;
	dptx_dev->dev = dev;
	dptx_dev->cap.edid_ptr = edid_ptr;

	dptx_dev->rpc_ion_client = ion_client_create(
			rtk_phoenix_ion_device, "dptx_driver");

	dptx_dev->hwinfo.chip_id = get_rtd_chip_id();
	dptx_dev->hwinfo.chip_revision = get_rtd_chip_revision();

	of_property_read_u32(node, "self-test", &dptx_dev->selftest);
	if (dptx_dev->selftest) {
		rtk_hdmi_power_on();
		dptx_dev->hwinfo.vo_en = 1;
	}

	/* get clock & reset resource from devic tree */
	idx = of_property_match_string(node, "clock-names", "clk_en_tve");
	dptx_dev->tve_clk = clk_get(dev, "clk_en_tve");
	clk_prepare_enable(dptx_dev->tve_clk);
	for (i=0; i<DPTX_RES_MAX; i++) {
		if (i==idx)
			continue;
		clk = of_clk_get(node, i);
		if (!IS_ERR(clk)) {
			clk_prepare_enable(clk);
			clk_put(clk);
		} else {
			break;
		}
	}
	if (dptx_dev->hwinfo.chip_id == CHIP_ID_RTD1619) {
		clk = clk_get(dev, "clk_en_tsio_trx");
		clk_disable_unprepare(clk);
		clk_put(clk);
	}

	if (dptx_dev->hwinfo.chip_id == CHIP_ID_RTD1619)
		idx = of_property_match_string(node, "reset-names", "edp");
	else
		idx = of_property_match_string(node, "reset-names", "lvds");

	dptx_dev->lvds_rst = of_reset_control_get_by_index(node, idx);
	for (i=0; i<DPTX_RES_MAX; i++) {
		if (i==idx)
			continue;
		rstc = of_reset_control_get_by_index(node, i);
		if (!IS_ERR(rstc))
			reset_control_deassert(rstc);	
		else
			break;
	}

	sema_init(&dptx_dev->hwinfo.sem, 0);
	dptx_dev->hwinfo.reg_base = of_iomap(dev->of_node, 0);
	dptx_dev->hwinfo.pll_base = of_iomap(dev->of_node, 1);
	dptx_dev->hwinfo.lvds_base = of_iomap(dev->of_node, 2);
	dptx_dev->hwinfo.vo_base = of_iomap(dev->of_node, 3);

	/* get other resource from device tree */
	of_property_read_u32(node, "ignore-edid", &dptx_dev->ignore_edid);

	irq = irq_of_parse_and_map(node, 0);
	if (request_irq(irq, rtk_dptx_isr, IRQF_SHARED, "DP_TX", dptx_dev)) {
		dev_err(dev, "[%s] request irq fail\n", __func__);
		return -ENODEV;
	}
	dptx_dev->dptx_irq = irq;

	/* register misc device */
	dptx_dev->miscdev.minor = MISC_DYNAMIC_MINOR;
	dptx_dev->miscdev.name = "dptx";
	dptx_dev->miscdev.mode = 0666;
	dptx_dev->miscdev.fops = &dptx_fops;
	if(misc_register(&dptx_dev->miscdev)) {
		dev_err(dev, "[%s] misc register fail\n", __func__);
		return -ENODEV;
	}
	
	dptx_dev->hwinfo.out_type = DP_FORMAT_1080P_60;

	if (dptx_dev->selftest)
		rtk_dptx_enable(dptx_dev);

	register_dptx_switch(dptx_dev);

	dev_info(dev, "[%s] finished\n", __func__);
	dptx_dev->isr_signal = false;
	init_waitqueue_head(&dptx_dev->hpd_wait);
	return 0;
}

static const struct of_device_id rtk_dptx_dt_ids[] = {
	{ .compatible = "Realtek,rtk-dptx", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_dptx_dt_ids);

static struct platform_driver rtk_dptx_driver = {
	.probe = rtk_dptx_probe,
	.driver = {
		.name = "rtk_dptx",
		.owner = THIS_MODULE, 
		.of_match_table = of_match_ptr(rtk_dptx_dt_ids),
	},
};

static int __init rtk_dptx_init(void)
{
	if (platform_driver_register(&rtk_dptx_driver)) {
		return -EFAULT;
	}
	return 0;
}

static void __exit rtk_dptx_exit(void)
{

}

module_init(rtk_dptx_init);
module_exit(rtk_dptx_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek Display Port kernel module");
