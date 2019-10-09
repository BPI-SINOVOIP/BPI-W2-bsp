/*
 *  phy-rtk-usb3.c RTK usb3.0 phy driver
 *
 * copyright (c) 2017 realtek semiconductor corporation
 *
 * this program is free software; you can redistribute it and/or modify
 * it under the terms of the gnu general public license as published by
 * the free software foundation; either version 2 of the license, or
 * (at your option) any later version.
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/usb/otg.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/usb/ch11.h>
#include <linux/uaccess.h>
#include <linux/debugfs.h>

#include "phy-rtk-usb.h"

#define RTK_USB3PHY_NAME "rtk-usb3phy"

struct reg_addr {
	void __iomem *REG_MDIO_CTL;
};

struct phy_data {
	int size;
	u8 *addr;
	u16 *data;

	u16 saved_trim_value;//=0xFFFF;
	u8 connected;//=0;

	bool do_toggle;
	bool use_default_parameter;
};

#define WAIT_VBUSY_RETRY	3
#define USB_ST_BUSY		BIT(7)

static int rtk_usb_phy3_wait_vbusy(struct reg_addr *regAddr)
{
	return utmi_wait_register(regAddr->REG_MDIO_CTL, BIT(7), 0);
}

static u32 rtk_usb_phy_read(struct reg_addr *regAddr, char addr)
{
	volatile unsigned int regVal;

	regVal = (addr << 8);

	writel(regVal, regAddr->REG_MDIO_CTL);

	rtk_usb_phy3_wait_vbusy(regAddr);

	return readl(regAddr->REG_MDIO_CTL);
}

static int rtk_usb_phy_write(struct reg_addr *regAddr, char addr, u16 data)
{
	volatile unsigned int regVal;

	regVal = BIT(0)     |
			(addr << 8) |
			(data <<16);

	writel(regVal, regAddr->REG_MDIO_CTL);

	rtk_usb_phy3_wait_vbusy(regAddr);

	return 0;
}

static void rtk_usb_phy_shutdown(struct usb_phy *phy)
{
	/* Todo */
}

void do_rtk_usb3_phy_toggle(struct rtk_usb_phy_s *rtk_phy, int index, bool isConnect);

static int do_rtk_usb_phy_init(struct usb_phy *phy, int phy_index)
{
	struct rtk_usb_phy_s *rtk_phy = (struct rtk_usb_phy_s*) phy;
	struct reg_addr *regAddr =
		    &((struct reg_addr *)rtk_phy->reg_addr)[phy_index];
	struct phy_data *phy_data =
		    &((struct phy_data *)rtk_phy->phy_data)[phy_index];
	int index = 0;
	u8 *addr = phy_data->addr;
	u16 *data = phy_data->data;

	dev_info(phy->dev, "%s Init RTK USB 3.0 PHY phy#%d\n", __func__, phy_index);

	if (phy_data->use_default_parameter) {
		dev_info(phy->dev, "%s phy#%d use default parameter\n",
			    __func__, phy_index);
		goto do_toggle;
	}

	for (index = 0; index < phy_data->size; index++) {
		rtk_usb_phy_write(regAddr, *(addr + index), *(data + index));
	}

	for (index = 0; index < phy_data->size; index++)
		dev_dbg(phy->dev, "[USB3_PHY], addr = 0x%02x, data = 0x%08x\n",
				*(addr + index), rtk_usb_phy_read(regAddr, *(addr + index)));

do_toggle:
	do_rtk_usb3_phy_toggle(rtk_phy, phy_index, false);

	return 0;
}

static int rtk_usb_phy_init(struct usb_phy *phy)
{
	struct rtk_usb_phy_s *rtk_phy = (struct rtk_usb_phy_s*) phy;
	int ret = 0;
	int i;

	dev_info(phy->dev, "%s Init RTK USB 3.0 PHY\n", __func__);
	for (i = 0; i < rtk_phy->phyN; i++) {
		ret = do_rtk_usb_phy_init(phy, i);
	}
	dev_info(phy->dev, "%s Initialized RTK USB 3.0 PHY\n", __func__);
	return ret;
}

void do_rtk_usb3_phy_toggle(struct rtk_usb_phy_s *rtk_phy, int i,
	    bool isConnect)
{
	struct reg_addr *regAddr = &((struct reg_addr *)rtk_phy->reg_addr)[i];
	struct phy_data *phy_data = &((struct phy_data *)rtk_phy->phy_data)[i];

	if (phy_data && !phy_data->do_toggle) return;

	if (phy_data) {
		u8 *addr = phy_data->addr;
		u16 *data = phy_data->data;
		size_t index;

		for (index = 0; index < phy_data->size; index++) {
			if (*(addr + index) == 0x09) {
				mdelay(1);
				dev_info(rtk_phy->dev, "%s ########## to toggle PHY addr 0x09 "
					    "BIT(9)\n", __func__);
				rtk_usb_phy_write(regAddr, *(addr + index),
					    *(data + index) & (~BIT(9)));
				mdelay(1);
				rtk_usb_phy_write(regAddr, *(addr + index), *(data + index));
			}
		}
		dev_info(rtk_phy->dev, "%s ########## PHY addr 0x1f = 0x%08x\n",
			    __func__, rtk_usb_phy_read(regAddr, 0x1f));
	}
}

void rtk_usb3_phy_toggle(struct usb_phy *usb3_phy, bool isConnect, int port)
{
	int index = port;
	struct rtk_usb_phy_s *rtk_phy = NULL;

	if (usb3_phy != NULL && usb3_phy->dev != NULL)
		rtk_phy = dev_get_drvdata(usb3_phy->dev);

	if (rtk_phy == NULL) {
		pr_err("%s ERROR! NO this device\n", __func__);
		return;
	}

	do_rtk_usb3_phy_toggle(rtk_phy, index, isConnect);
}
EXPORT_SYMBOL(rtk_usb3_phy_toggle);

#ifdef CONFIG_DYNAMIC_DEBUG
extern struct dentry *create_phy_debug_root(void);

static int rtk_usb3_parameter_show(struct seq_file *s, void *unused)
{
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	int i, index;

	for (i = 0; i < rtk_phy->phyN; i++) {
		struct reg_addr *regAddr = &((struct reg_addr *)rtk_phy->reg_addr)[i];
		struct phy_data *phy_data = &((struct phy_data *)rtk_phy->phy_data)[i];
		u8 *addr = phy_data->addr;

		seq_printf(s, "[USB3_PHY] PHY %d\n", i);

		for (index = 0; index < phy_data->size; index++)
			seq_printf(s, "[USB3_PHY], addr = 0x%02x, data = 0x%08x\n",
				    *(addr + index),
				    rtk_usb_phy_read(regAddr, *(addr + index)));
	}
	return 0;
}

static int rtk_usb3_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb3_parameter_show, inode->i_private);
}

static const struct file_operations rtk_usb3_parameter_fops = {
	.open			= rtk_usb3_parameter_open,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_usb3_set_parameter_show(struct seq_file *s, void *unused)
{
	//struct rtk_usb_phy_s	*rtk_phy = s->private;

	seq_printf(s, "Set Phy parameter by following command\n");
	seq_printf(s, "echo \"phy_num addr value\" > set_parameter\n");
	seq_printf(s, "echo \"0 0x00 0x4008\" > set_parameter\n");
	seq_printf(s, "echo \"0 0x21 0x88AA\" > set_parameter\n");

	return 0;
}

static int rtk_usb3_set_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb3_set_parameter_show, inode->i_private);
}

static ssize_t rtk_usb3_set_parameter_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	struct reg_addr * regAddr;
	struct phy_data *phy_data;
	u8 *addr;
	u16 *data;
	int index, i;
	char buffer[40];
	char *buf = buffer;
	u32 _addr;
	u32 value;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	sscanf(buf, "%d", &i);
	buf = buf + 1;

	regAddr = &((struct reg_addr *)rtk_phy->reg_addr)[i];
	phy_data = &((struct phy_data *)rtk_phy->phy_data)[i];
	addr = phy_data->addr;
	data = phy_data->data;

	buf = skip_spaces(buf);
	sscanf(buf, "%x %x", &_addr, &value);

	for (index = 0; index < phy_data->size; index++) {
		if (_addr == *(addr + index)) {
			*(data + index) = value;
			rtk_usb_phy_write(regAddr, *(addr + index), *(data + index));
		}
	}

	return count;
}

static const struct file_operations rtk_usb3_set_parameter_fops = {
	.open			= rtk_usb3_set_parameter_open,
	.write			= rtk_usb3_set_parameter_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_usb3_toggle_show(struct seq_file *s, void *unused)
{
	//struct rtk_usb_phy_s		*rtk_phy = s->private;

	seq_printf(s, "ehco 1 to toggle Page1 addr 0xe0 BIT(2)\n");

	return 0;
}

static int rtk_usb3_toggle_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_usb3_toggle_show, inode->i_private);
}

static ssize_t rtk_usb3_toggle_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	char			buf[32];

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "1", 1))
		rtk_usb3_phy_toggle(&rtk_phy->phy, false, 0);

	return count;
}

static const struct file_operations rtk_usb3_toggle_fops = {
	.open			= rtk_usb3_toggle_open,
	.write			= rtk_usb3_toggle_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static inline void create_debug_files(struct rtk_usb_phy_s *rtk_phy) {
	struct dentry *phy_debug_root = NULL;

	dev_dbg(rtk_phy->dev, "%s", __func__);

	phy_debug_root = create_phy_debug_root();

	if (!phy_debug_root) {
		dev_err(rtk_phy->dev, "%s Error phy_debug_root is NULL", __func__);
		return;
	}
	rtk_phy->debug_dir = debugfs_create_dir(dev_name(rtk_phy->dev), phy_debug_root);
	if (!rtk_phy->debug_dir) {
		dev_err(rtk_phy->dev, "%s Error debug_dir is NULL", __func__);
		return;
	}

	if (!debugfs_create_file("parameter", S_IRUGO, rtk_phy->debug_dir, rtk_phy,
		    &rtk_usb3_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("set_parameter", S_IRUGO | S_IWUSR, rtk_phy->debug_dir, rtk_phy,
		    &rtk_usb3_set_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("toggle", S_IRUGO | S_IWUSR, rtk_phy->debug_dir, rtk_phy,
		    &rtk_usb3_toggle_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(rtk_phy->debug_dir);
}
#endif //CONFIG_DYNAMIC_DEBUG

static int rtk_usb3phy_probe(struct platform_device *pdev)
{
	struct rtk_usb_phy_s *rtk_usb_phy;
	struct device *dev = &pdev->dev;
	int phyN;
	int i,ret = 0;

	rtk_usb_phy = devm_kzalloc(dev, sizeof(*rtk_usb_phy), GFP_KERNEL);
	if (!rtk_usb_phy)
		return -ENOMEM;

	rtk_usb_phy->dev			= &pdev->dev;
	rtk_usb_phy->phy.dev		= rtk_usb_phy->dev;
	rtk_usb_phy->phy.label		= RTK_USB3PHY_NAME;
	rtk_usb_phy->phy.init		= rtk_usb_phy_init;
	rtk_usb_phy->phy.shutdown	= rtk_usb_phy_shutdown;

	if (!dev->of_node) {
		dev_err(dev, "%s %d No device node\n", __func__, __LINE__);
		goto err;
	}

	ret = of_property_read_u32_index(dev->of_node, "phyN", 0,
		    &phyN);
	if (ret) goto err;

	rtk_usb_phy->phyN = phyN;

	rtk_usb_phy->reg_addr = devm_kzalloc(dev,
		    sizeof(struct reg_addr) * phyN, GFP_KERNEL);
	if (!rtk_usb_phy->reg_addr)
		return -ENOMEM;
	rtk_usb_phy->phy_data = devm_kzalloc(dev,
		    sizeof(struct phy_data) * phyN, GFP_KERNEL);
	if (!rtk_usb_phy->phy_data)
		return -ENOMEM;

	for (i = 0; i < phyN; i++) {
		struct reg_addr *addr = &((struct reg_addr *)rtk_usb_phy->reg_addr)[i];
		struct phy_data *phy_data =
			    &((struct phy_data *)rtk_usb_phy->phy_data)[i];

		char phy_name[5];
		struct device_node *sub_node;

		addr->REG_MDIO_CTL = of_iomap(dev->of_node, i);
		dev_dbg(dev, "%s %d #%d REG_MDIO_CTL=%p\n",
			    __func__, __LINE__, i, addr->REG_MDIO_CTL);

		snprintf(phy_name, 5, "phy%d", i);

		sub_node = of_get_child_by_name(dev->of_node, phy_name);
		if (!sub_node) {
			dev_err(dev, "%s %d No device sub node for %s\n",
				    __func__, __LINE__, phy_name);
			goto err;
		}

		phy_data->saved_trim_value = 0xFFFF;
		phy_data->connected = 0;

		ret = of_property_read_u32_index(sub_node, "phy_data_size", 0, &phy_data->size);
		if (ret)
			goto err;
		phy_data->addr = devm_kzalloc(dev, sizeof(u8)*phy_data->size, GFP_KERNEL);
		if (!phy_data->addr)
			return -ENOMEM;
		phy_data->data = devm_kzalloc(dev, sizeof(u16)*phy_data->size, GFP_KERNEL);
		if (!phy_data->data)
			return -ENOMEM;
		ret = of_property_read_u8_array(sub_node, "phy_data_addr", phy_data->addr, phy_data->size);
		if (ret)
			goto err;
		ret = of_property_read_u16_array(sub_node, "phy_data_revA", phy_data->data, phy_data->size);
		if (ret)
			goto err;

		if (of_property_read_bool(sub_node, "do_toggle"))
			phy_data->do_toggle = true;
		else
			phy_data->do_toggle = false;

		if (of_property_read_bool(sub_node, "use_default_parameter"))
			phy_data->use_default_parameter = true;
		else
			phy_data->use_default_parameter = false;
	}

	platform_set_drvdata(pdev, rtk_usb_phy);

	//ret = usb_add_phy(&rtk_usb_phy->phy, USB_PHY_TYPE_USB3);
	//if (ret)
	//	goto err;

#ifdef CONFIG_DYNAMIC_DEBUG
	create_debug_files(rtk_usb_phy);
#endif

	dev_info(&pdev->dev, "%s Probe RTK USB 3.0 PHY\n", __FILE__);
err:
	return ret;
}

static int rtk_usb3phy_remove(struct platform_device *pdev)
{
	//struct rtk_usb_phy_s *rtk_usb_phy = platform_get_drvdata(pdev);

	//usb_remove_phy(&rtk_usb_phy->phy);

	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id usbphy_rtk_dt_match[] = {
	{ .compatible = "Realtek,usb3phy", },
	{ .compatible = "Realtek,rtk119x-usb3phy", },
	{ .compatible = "Realtek,rtd129x-usb3phy", },
	{},
};
MODULE_DEVICE_TABLE(of, usbphy_rtk_dt_match);
#endif

static struct platform_driver rtk_usb3phy_driver = {
	.probe		= rtk_usb3phy_probe,
	.remove		= rtk_usb3phy_remove,
	.driver		= {
		.name	= RTK_USB3PHY_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(usbphy_rtk_dt_match),
	},
};

module_platform_driver(rtk_usb3phy_driver);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" RTK_USB3PHY_NAME);
