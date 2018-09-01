/*
 *  phy-rtk-rle0599.c RTK rle0599 usb2.0 phy driver
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
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <soc/realtek/rtd129x_efuse.h>

#include "phy-rtk-usb.h"
#ifdef CONFIG_USB_PATCH_ON_RTK
/* Add global lock for emmc issue*/
#include <soc/realtek/rtd129x_lockapi.h>
#endif


#define RTK_USB_RLE0599_PHY_NAME "rtk-usb-phy-rle0599"

struct reg_addr {
	void __iomem *REG_WRAP_VStatusOut2;
	void __iomem *REG_EHCI_INSNREG05;
};

struct phy_data {
	int page0_size;
	struct rtk_usb_phy_data_s *page0;
	int page1_size;
	struct rtk_usb_phy_data_s *page1;

	bool check_efuse;
	u8 efuse_usb_dp_dm;
};

static u8 efuse_usb_dp_dm_table[0x10] = {0xe0, 0x80, 0x84, 0x88, 0x8c, 0x90, 0x94, 0x98,
					 0x9c, 0xa0, 0xa4, 0xa8, 0xac, 0xb0, 0xb4, 0xb8};

#define WAIT_VBUSY_RETRY	3

#define OFFEST_PHY_READ 0x20

#define USB_ST_BUSY		BIT(17)

static DEFINE_SPINLOCK(rtk_phy_lock);

static char rtk_usb_phy_read(struct rtk_usb_phy_s *rtk_phy, char addr)
{
	volatile unsigned int regVal;
	struct reg_addr *regAddr = rtk_phy->reg_addr;
	void __iomem *REG_EHCI_INSNREG05 = regAddr->REG_EHCI_INSNREG05;

	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << 13) | 	// Port num
			 (1 << 12) |	// vload
			 ((addr & 0x0f) << 8);	// vcontrol
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal &= ~(1 << 12);
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << 13) | 	// Port num
			 (1 << 12) |	// vload
			 ((addr & 0xf0) << 4);	// vcontrol
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = high nibble of addr, VLoadM = 0
	regVal &= ~(1 << 12);
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	smp_rmb();
	regVal = phy_read(REG_EHCI_INSNREG05);

	return (char) (regVal & 0xff);
}

static int rtk_usb_phy_write(struct rtk_usb_phy_s *rtk_phy, char addr, char data)
{
	volatile unsigned int regVal;
	struct reg_addr *regAddr = rtk_phy->reg_addr;
	void __iomem *REG_WRAP_VStatusOut2 = regAddr->REG_WRAP_VStatusOut2;
	void __iomem *REG_EHCI_INSNREG05 = regAddr->REG_EHCI_INSNREG05;

	//printk("[%s:%d], addr = 0x%x, data = 0x%x\n", __FUNCTION__, __LINE__, addr, data);

#ifdef CONFIG_USB_PATCH_ON_RTK
	/* Add global lock for emmc issue*/
	unsigned long flags;
	rtk_lockapi_lock(flags,__FUNCTION__);
#endif
	//write data to VStatusOut2 (data output to phy)
	phy_write(REG_WRAP_VStatusOut2, (u32) data);
#ifdef CONFIG_USB_PATCH_ON_RTK
	/* Add global lock for emmc issue*/
	rtk_lockapi_unlock(flags,__FUNCTION__);
#endif

	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 1
	regVal = (1 << 13) | 	// Port num
			 (1 << 12) |	// vload
			 ((addr & 0x0f) << 8);	// vcontrol
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = low nibble of addr, VLoadM = 0
	regVal &= ~(1 << 12);
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = high nibble of addr, VLoadM = 1
	regVal = (1 << 13) | 	// Port num
			 (1 << 12) |	// vload
			 ((addr & 0xf0) << 4);	// vcontrol
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	// VCtrl = high nibble of addr, VLoadM = 0
	regVal &= ~(1 << 12);
	phy_write(REG_EHCI_INSNREG05, regVal);
	utmi_wait_register(REG_EHCI_INSNREG05, USB_ST_BUSY, 0);

	return 0;
}

static int rtk_usb_phy_set_page(struct rtk_usb_phy_s *rtk_phy, int page)
{
	return rtk_usb_phy_write(rtk_phy, 0xf4, page == 0 ? 0x9b : 0xbb);
}

static int initialized=0;
void rtk_usb_phy_shutdown(struct usb_phy *phy)
{
	/* Todo */
	initialized = 0;
}

static int updated_phy_parameter_by_efuse(struct rtk_usb_phy_s *rtk_usb_phy){
	u8 value = 0;
	int size = 4;
	int shift = 0;
	int offest = 0x1dc;
	int mask = (BIT(size) - 1);
	struct phy_data *phy_data = rtk_usb_phy->phy_data;
	struct rtk_usb_phy_data_s *phy_page0_default_setting = phy_data->page0;
	int i;

#if 0
	value = (efuse_readb(offest) << shift) & mask;
	dev_dbg(rtk_usb_phy->dev, "Get Efuse EFUSE_USB_DP_DM %x Mask %x\n",
		    efuse_readb(offest), mask);
#else
	pr_err("%s(): ERROR Need implement efuse_readb\n", __func__);
#endif
	phy_data->efuse_usb_dp_dm = value;

	for (i = 0; i<phy_data->page0_size; i++) {
		if ((phy_page0_default_setting + i)->addr == 0xe0) {
			(phy_page0_default_setting + i)->data = efuse_usb_dp_dm_table[value & mask];
			dev_dbg(rtk_usb_phy->dev, "Set addr %x value %x\n",
				(phy_page0_default_setting + i)->addr,
				(phy_page0_default_setting + i)->data);
		}
	}
	return 0;
}

void rtk_rle0599_phy_toggle(struct usb_phy *usb2_phy, bool isConnect);

int rtk_usb_phy_init(struct usb_phy* phy)
{
	int i;
	int ret=0;
	unsigned long flags;

	struct rtk_usb_phy_s *rtk_phy = (struct rtk_usb_phy_s*) phy;
	//struct reg_addr *regAddr = rtk_phy->reg_addr;
	struct phy_data *phy_data = rtk_phy->phy_data;
	struct rtk_usb_phy_data_s *phy_page0_default_setting = phy_data->page0;
	struct rtk_usb_phy_data_s *phy_page1_default_setting = phy_data->page1;

	spin_lock_irqsave(&rtk_phy_lock, flags);

	if (initialized) goto out;

	dev_info(phy->dev, "Init RTK USB phy-rle0599\n");

	if (phy_data->check_efuse)
		updated_phy_parameter_by_efuse(rtk_phy);

	/* Set page 0 */
	//printk("[%s:%d], Set page 0\n", __FUNCTION__, __LINE__);
	rtk_usb_phy_set_page(rtk_phy, 0);

	for (i=0; i<phy_data->page0_size; i++) {
		if (rtk_usb_phy_write(rtk_phy, (phy_page0_default_setting + i)->addr, (phy_page0_default_setting + i)->data)) {
			dev_err(phy->dev, "[%s:%d], page0 Error : addr = 0x%x, value = 0x%x\n",
				__FUNCTION__, __LINE__,
				(phy_page0_default_setting + i)->addr,
				(phy_page0_default_setting + i)->data);
			return -1;
		} else {
			dev_dbg(phy->dev, "[%s:%d], page0 Good : addr = 0x%x, value = 0x%x\n",
				__FUNCTION__, __LINE__,
				(phy_page0_default_setting + i)->addr,
				rtk_usb_phy_read(rtk_phy, (phy_page0_default_setting + i)->addr - OFFEST_PHY_READ));
		}
	}

	/* Set page 1 */
	//printk("[%s:%d], Set page 1\n", __FUNCTION__, __LINE__);
	rtk_usb_phy_set_page(rtk_phy, 1);

	for (i = 0; i < phy_data->page1_size; i++) {
		if (rtk_usb_phy_write(rtk_phy, (phy_page1_default_setting + i)->addr, (phy_page1_default_setting + i)->data)) {
			dev_err(phy->dev, "[%s:%d], page1 Error : addr = 0x%x, value = 0x%x\n",
				__FUNCTION__, __LINE__,
				(phy_page1_default_setting + i)->addr,
				(phy_page1_default_setting + i)->data);
			ret = -1;
			goto out;
		} else {
				dev_dbg(phy->dev, "[%s:%d], page1 Good : addr = 0x%x, value = 0x%x\n",
				__FUNCTION__, __LINE__,
				(phy_page1_default_setting + i)->addr,
				rtk_usb_phy_read(rtk_phy, (phy_page1_default_setting + i)->addr - OFFEST_PHY_READ));
		}
	}

	rtk_rle0599_phy_toggle(phy, false);

	initialized = 1;

	dev_info(phy->dev, "%s Initialized RTK USB PHY rle0599\n", __FILE__);
out:
	spin_unlock_irqrestore(&rtk_phy_lock, flags);
	return ret;
}

void rtk_rle0599_phy_toggle(struct usb_phy *usb2_phy, bool isConnect)
{
	struct rtk_usb_phy_s *rtk_phy = NULL;
	struct phy_data *phy_data = NULL;

	if (usb2_phy != NULL && usb2_phy->dev != NULL)
		rtk_phy = dev_get_drvdata(usb2_phy->dev);

	if (rtk_phy == NULL) {
		pr_err("%s %s ERROR! NO this device", __FILE__, __func__);
		return;
	}

	phy_data = rtk_phy->phy_data;
	if (phy_data) {
		int i;
		struct rtk_usb_phy_data_s *phy_page0_default_setting = phy_data->page0;
		struct rtk_usb_phy_data_s *phy_page1_default_setting = phy_data->page1;
		/* Set page 0 */
		rtk_usb_phy_set_page(rtk_phy, 0);
		for (i=0; i<phy_data->page0_size; i++) {
			if ((phy_page0_default_setting + i)->addr == 0xE7) {
				if (isConnect) {
					rtk_usb_phy_write(rtk_phy, (phy_page0_default_setting + i)->addr,
							(phy_page0_default_setting + i)->data & (~(BIT(4) | BIT(5) | BIT(6))));
				} else {
					rtk_usb_phy_write(rtk_phy, (phy_page0_default_setting + i)->addr,
							(phy_page0_default_setting + i)->data | (BIT(4) | BIT(5) | BIT(6)));
				}
				dev_dbg(rtk_phy->dev, "%s %sconnect to set Page0 0xE7 = %x\n", __func__,
					isConnect?"":"dis",
					rtk_usb_phy_read(rtk_phy, (phy_page0_default_setting + i)->addr));
			}
		}

		/* Set page 1 */
		rtk_usb_phy_set_page(rtk_phy, 1);

		for (i=0; i < phy_data->page1_size; i++) {
			if ((phy_page1_default_setting + i)->addr == 0xe0) {
				dev_info(rtk_phy->dev, "%s ########## to toggle Page1 addr 0xe0 BIT(2)\n", __func__);
				rtk_usb_phy_write(rtk_phy, (phy_page1_default_setting + i)->addr,
										  ((phy_page1_default_setting + i)->data) & (~BIT(2)));
				mdelay(1);
				rtk_usb_phy_write(rtk_phy, (phy_page1_default_setting + i)->addr,
										  (phy_page1_default_setting + i)->data);
			}
		}
	}
}
EXPORT_SYMBOL(rtk_rle0599_phy_toggle);

#ifdef CONFIG_DYNAMIC_DEBUG
extern struct dentry *create_phy_debug_root(void);

static int rtk_rle0599_parameter_show(struct seq_file *s, void *unused)
{
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	struct phy_data *phy_data = rtk_phy->phy_data;
	struct rtk_usb_phy_data_s *phy_page0_default_setting = phy_data->page0;
	struct rtk_usb_phy_data_s *phy_page1_default_setting = phy_data->page1;
	int i;
	unsigned long flags;

	seq_printf(s, "Page 0:\n");
	spin_lock_irqsave(&rtk_phy_lock, flags);
	/* Set page 0 */
	rtk_usb_phy_set_page(rtk_phy, 0);

	for (i=0; i<phy_data->page0_size; i++) {
		seq_printf(s, "Page 0: addr = 0x%x, value = 0x%x\n",
			(phy_page0_default_setting + i)->addr,
			rtk_usb_phy_read(rtk_phy, (phy_page0_default_setting + i)->addr - OFFEST_PHY_READ));
	}

	seq_printf(s, "Page 1:\n");
	/* Set page 1 */
	rtk_usb_phy_set_page(rtk_phy, 1);

	for (i = 0; i < phy_data->page1_size; i++) {
		seq_printf(s, "Page 1: addr = 0x%x, value = 0x%x\n",
			(phy_page1_default_setting + i)->addr,
			rtk_usb_phy_read(rtk_phy, (phy_page1_default_setting + i)->addr - OFFEST_PHY_READ));
	}

	spin_unlock_irqrestore(&rtk_phy_lock, flags);

	return 0;
}

static int rtk_rle0599_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_rle0599_parameter_show, inode->i_private);
}

static const struct file_operations rtk_rle0599_parameter_fops = {
	.open			= rtk_rle0599_parameter_open,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_rle0599_set_parameter_show(struct seq_file *s, void *unused)
{
	//struct rtk_usb_phy_s	*rtk_phy = s->private;

	seq_printf(s, "Set Phy parameter by following command\n");
	seq_printf(s, "echo \"page addr value\" > set_parameter\n");
	seq_printf(s, "echo \"page0 0xE1 0x30\" > set_parameter\n");
	seq_printf(s, "echo \"page1 0xE1 0xEF\" > set_parameter\n");

	return 0;
}

static int rtk_rle0599_set_parameter_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_rle0599_set_parameter_show, inode->i_private);
}

static ssize_t rtk_rle0599_set_parameter_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	struct phy_data *phy_data = rtk_phy->phy_data;
	struct rtk_usb_phy_data_s *phy_page0_default_setting = phy_data->page0;
	struct rtk_usb_phy_data_s *phy_page1_default_setting = phy_data->page1;
	unsigned long		flags;
	char			buffer[40];
	char *buf = buffer;
	int i;
	u32 addr;
	u32 value;

	if (copy_from_user(&buffer, ubuf, min_t(size_t, sizeof(buffer) - 1, count)))
		return -EFAULT;

	spin_lock_irqsave(&rtk_phy_lock, flags);
	if (!strncmp(buf, "page0", 5)) {
		buf = buf + 5;
		buf = skip_spaces(buf);
		sscanf(buf, "%x %x", &addr, &value);

		rtk_usb_phy_set_page(rtk_phy, 0);
		for (i = 0; i<phy_data->page0_size; i++) {
			if ((phy_page0_default_setting + i)->addr == addr) {
				(phy_page0_default_setting + i)->data = value;
				if (rtk_usb_phy_write(rtk_phy, (phy_page0_default_setting + i)->addr,
						(phy_page0_default_setting + i)->data))
					dev_err(rtk_phy->dev, "[%s:%d], page0 Error : addr = 0x%x, value = 0x%x\n",
						__FUNCTION__, __LINE__,
						(phy_page0_default_setting + i)->addr,
						(phy_page0_default_setting + i)->data);
				else
					dev_dbg(rtk_phy->dev, "[%s:%d], page0 Good : addr = 0x%x, value = 0x%x\n",
						__FUNCTION__, __LINE__,
						(phy_page0_default_setting + i)->addr,
						rtk_usb_phy_read(rtk_phy, (phy_page0_default_setting + i)->addr - OFFEST_PHY_READ));
			}
		}
	} else if (!strncmp(buf, "page1", 5)) {
		buf = buf + 5;
		buf = skip_spaces(buf);
		sscanf(buf, "%x %x", &addr, &value);

		rtk_usb_phy_set_page(rtk_phy, 1);
		for (i = 0; i<phy_data->page1_size; i++) {
			if ((phy_page1_default_setting + i)->addr == addr) {
				(phy_page1_default_setting + i)->data = value;
				if (rtk_usb_phy_write(rtk_phy, (phy_page1_default_setting + i)->addr,
						(phy_page1_default_setting + i)->data))
					dev_err(rtk_phy->dev, "[%s:%d], page1 Error : addr = 0x%x, value = 0x%x\n",
						__FUNCTION__, __LINE__,
						(phy_page1_default_setting + i)->addr,
						(phy_page1_default_setting + i)->data);
				else
					dev_dbg(rtk_phy->dev, "[%s:%d], page1 Good : addr = 0x%x, value = 0x%x\n",
						__FUNCTION__, __LINE__,
						(phy_page1_default_setting + i)->addr,
						rtk_usb_phy_read(rtk_phy, (phy_page1_default_setting + i)->addr - OFFEST_PHY_READ));
			}
		}
	} else
		dev_err(rtk_phy->dev, "UNKNOWN input (%s)", buf);

	spin_unlock_irqrestore(&rtk_phy_lock, flags);
	return count;
}

static const struct file_operations rtk_rle0599_set_parameter_fops = {
	.open			= rtk_rle0599_set_parameter_open,
	.write			= rtk_rle0599_set_parameter_write,
	.read			= seq_read,
	.llseek			= seq_lseek,
	.release		= single_release,
};

static int rtk_rle0599_toggle_show(struct seq_file *s, void *unused)
{
	//struct rtk_usb_phy_s		*rtk_phy = s->private;

	seq_printf(s, "ehco 1 to toggle Page1 addr 0xe0 BIT(2)\n");

	return 0;
}

static int rtk_rle0599_toggle_open(struct inode *inode, struct file *file)
{
	return single_open(file, rtk_rle0599_toggle_show, inode->i_private);
}

static ssize_t rtk_rle0599_toggle_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	struct seq_file		*s = file->private_data;
	struct rtk_usb_phy_s		*rtk_phy = s->private;
	char			buf[32];

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "1", 1))
		rtk_rle0599_phy_toggle(&rtk_phy->phy, false);

	return count;
}

static const struct file_operations rtk_rle0599_toggle_fops = {
	.open			= rtk_rle0599_toggle_open,
	.write			= rtk_rle0599_toggle_write,
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
						&rtk_rle0599_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("set_parameter", S_IRUGO | S_IWUSR, rtk_phy->debug_dir, rtk_phy,
						&rtk_rle0599_set_parameter_fops))
		goto file_error;

	if (!debugfs_create_file("toggle", S_IRUGO | S_IWUSR, rtk_phy->debug_dir, rtk_phy,
						&rtk_rle0599_toggle_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(rtk_phy->debug_dir);
}
#endif //CONFIG_DYNAMIC_DEBUG

static int rtk_usb_rle0599_phy_probe(struct platform_device *pdev)
{
	struct rtk_usb_phy_s *rtk_usb_phy;
	struct device *dev = &pdev->dev;
	int	ret = 0;
	struct reg_addr *addr;
	struct phy_data *phy_data;
	int phy_data_page0_size, phy_data_page1_size;

	rtk_usb_phy = devm_kzalloc(dev, sizeof(*rtk_usb_phy), GFP_KERNEL);
	if (!rtk_usb_phy)
		return -ENOMEM;

	rtk_usb_phy->dev			= &pdev->dev;
	rtk_usb_phy->phy.dev		= rtk_usb_phy->dev;
	rtk_usb_phy->phy.label		= RTK_USB_RLE0599_PHY_NAME;
	rtk_usb_phy->phy.init		= rtk_usb_phy_init;
	rtk_usb_phy->phy.shutdown	= rtk_usb_phy_shutdown;

	if (dev->of_node) {
		ret = of_property_read_u32_index(dev->of_node, "phyN", 0, &rtk_usb_phy->phyN);
		if (ret) goto err;
		dev_dbg(dev, "%s %s phyN=%d\n", __FILE__, __func__, rtk_usb_phy->phyN);
		addr = devm_kzalloc(dev, sizeof(*addr), GFP_KERNEL);
		if (!addr) return -ENOMEM;

		addr->REG_WRAP_VStatusOut2 = of_iomap(dev->of_node, 0);
		addr->REG_EHCI_INSNREG05   = of_iomap(dev->of_node, 1);

		rtk_usb_phy->reg_addr = addr;

		dev_dbg(dev, "%s %s REG_WRAP_VStatusOut2=%p\n", __FILE__, __func__, addr->REG_WRAP_VStatusOut2);
		dev_dbg(dev, "%s %s REG_EHCI_INSNREG05=%p\n", __FILE__, __func__, addr->REG_EHCI_INSNREG05);
		ret = of_property_read_u32_index(dev->of_node, "phy_data_page0_size", 0, &phy_data_page0_size);
		if (ret) goto err;
		ret = of_property_read_u32_index(dev->of_node, "phy_data_page1_size", 0, &phy_data_page1_size);
		if (ret) goto err;

		dev_dbg(dev, "%s %s phy_data_page0_size=%d, phy_data_page1_size=%d\n",
					__FILE__, __func__, phy_data_page0_size, phy_data_page1_size);
	}

	phy_data = devm_kzalloc(dev, sizeof(*phy_data), GFP_KERNEL);
	if (!phy_data)
		return -ENOMEM;
	phy_data->page0_size = phy_data_page0_size;
	phy_data->page0 = devm_kzalloc(dev, sizeof(struct rtk_usb_phy_data_s)*phy_data_page0_size, GFP_KERNEL);
	if (!phy_data->page0)
		return -ENOMEM;
	phy_data->page1_size = phy_data_page1_size;
	phy_data->page1 = devm_kzalloc(dev, sizeof(struct rtk_usb_phy_data_s)*phy_data_page1_size, GFP_KERNEL);
	if (!phy_data->page1)
		return -ENOMEM;

	if (dev->of_node) {
		char tmp_addr[phy_data_page0_size];
		char tmp_data[phy_data_page0_size];
		int i = 0;
		ret = of_property_read_u8_array(dev->of_node, "phy_data_page0_addr", tmp_addr, phy_data_page0_size);
		if (ret) goto err;
		ret = of_property_read_u8_array(dev->of_node, "phy_data_page0_data", tmp_data, phy_data_page0_size);
		if (ret) goto err;
		for (i = 0; i < phy_data_page0_size; i++) {
			struct rtk_usb_phy_data_s *phy_data_page0 = (phy_data->page0 + i);
			phy_data_page0->addr = tmp_addr[i];
			phy_data_page0->data = tmp_data[i];
		}
		ret = of_property_read_u8_array(dev->of_node, "phy_data_page1_addr", tmp_addr, phy_data_page1_size);
		if (ret) goto err;
		ret = of_property_read_u8_array(dev->of_node, "phy_data_page1_data", tmp_data, phy_data_page1_size);
		if (ret) goto err;
		for (i = 0; i < phy_data_page1_size; i++) {
			struct rtk_usb_phy_data_s *phy_data_page1 = (phy_data->page1 + i);
			phy_data_page1->addr = tmp_addr[i];
			phy_data_page1->data = tmp_data[i];
		}
		rtk_usb_phy->phy_data = phy_data;

		if (of_property_read_bool(dev->of_node, "check_efuse"))
			phy_data->check_efuse = true;
		else
			phy_data->check_efuse = false;
	}

#if 0
	/* Due to usb_add_phy only support one USB2_phy and one USB3_phy
	 * DWC3 use USB2_phy and USB3_phy, EHCI don't add it
	 */
	ret = usb_add_phy(&rtk_usb_phy->phy, USB_PHY_TYPE_USB2);
	if (ret)
		goto err;
#endif

	platform_set_drvdata(pdev, rtk_usb_phy);

#ifdef CONFIG_DYNAMIC_DEBUG
	create_debug_files(rtk_usb_phy);
#endif

	dev_info(&pdev->dev, "Probe RTK USB 2.0 RLE0599 PHY\n");

err:
	return ret;
}

static int rtk_usb_rle0599_phy_remove(struct platform_device *pdev)
{
//	struct rtk_usb_phy_s *rtk_usb_phy = platform_get_drvdata(pdev);

#if 0
	/* Due to usb_add_phy only support one USB2_phy and one USB3_phy
	 * DWC3 use USB2_phy and USB3_phy, EHCI don't add it
	 */
	usb_remove_phy(&rtk_usb_phy->phy);
#endif

	return 0;
}

static const struct of_device_id usb_phy_rle0599_rtk_dt_ids[] = {
	{ .compatible = "Realtek,rtk119x-usb_phy_rle0599", },
	{ .compatible = "Realtek,rtd129x-usb_phy_rle0599", },
	{},
};
MODULE_DEVICE_TABLE(of, usb_phy_rle0599_rtk_dt_ids);

static struct platform_driver rtk_usb_rle0599_phy_driver = {
	.probe		= rtk_usb_rle0599_phy_probe,
	.remove		= rtk_usb_rle0599_phy_remove,
	.driver		= {
		.name	= RTK_USB_RLE0599_PHY_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(usb_phy_rle0599_rtk_dt_ids),
	},
};

module_platform_driver(rtk_usb_rle0599_phy_driver);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" RTK_USB_RLE0599_PHY_NAME);
