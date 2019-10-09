/*
 * Realtek PCIe host controller driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */
#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include <linux/of_pci.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/resource.h>
#include <linux/signal.h>
#include <linux/types.h>
#include <linux/reset-helper.h>
#include <linux/reset.h>
#include <linux/suspend.h>
#include <linux/kthread.h>
#include <linux/spinlock.h>
#include "pcie-rtd139x.h"


spinlock_t rtk_pcie_139x_lock;
#define PCIE_IO_2K_MASK  0xFFFFF800
#define PCIE_IO_4K_MASK  0xFFFFF000
#define PCIE_IO_64K_MASK 0xFFFF0000


static void __iomem *PCIE_CTRL_BASE;
static void __iomem *PCIE_CFG_BASE;


static void __iomem *SYSTEM_BASE1;
static void __iomem *SYSTEM_BASE2;


static u32 PCIE_MMIO_PHY_ADDR;
static u32 PCIE_MMIO_PHY_ADDR_LEN;

static u32 pcie_gpio_29;


static u32 speed_mode;


#define cfg_direct_access false

static struct clk *pcie_clk;
static struct reset_control *rstn_pcie_stitch;
static struct reset_control *rstn_pcie;
static struct reset_control *rstn_pcie_core;
static struct reset_control *rstn_pcie_power;
static struct reset_control *rstn_pcie_nonstitch;
static struct reset_control *rstn_pcie_phy;
static struct reset_control *rstn_pcie_phy_mdio;
static struct reset_control *rstn_pcie_sgmii_mdio;

static struct pci_bus *bus;
static struct platform_device *local_pdev;

static void rtk_pcie_139x_ctrl_write(unsigned long addr, unsigned int val)
{
	writel(val, addr + PCIE_CTRL_BASE);
}

static unsigned int rtk_pcie_139x_ctrl_read(unsigned long addr)
{
	unsigned int val = readl(addr + PCIE_CTRL_BASE);
	return val;
}

static void rtk_pcie_139x_direct_cfg_write(unsigned long addr, unsigned int val)
{
	writel(val, addr + PCIE_CFG_BASE);
}

static void rtk_pcie_139x_direct_cfg_write_word(unsigned long addr, u16 val)
{
	writew(val, addr + PCIE_CFG_BASE);
}

static void rtk_pcie_139x_direct_cfg_write_byte(unsigned long addr, u8 val)
{
	writeb(val, addr + PCIE_CFG_BASE);
}

static unsigned int rtk_pcie_139x_direct_cfg_read(unsigned long addr)
{
	unsigned int val = readl(addr + PCIE_CFG_BASE);
	return val;
}

static u16 rtk_pcie_139x_direct_cfg_read_word(unsigned long addr)
{
	u16 val = readw(addr + PCIE_CFG_BASE);
	return val;
}

static u8 rtk_pcie_139x_direct_cfg_read_byte(unsigned long addr)
{
	u8 val = readb(addr + PCIE_CFG_BASE);
	return val;
}


u32 rtk_pcie_139x_mmio_start(void)
{
	return PCIE_MMIO_PHY_ADDR;
}

u32 rtk_pcie_139x_mmio_end(void)
{
	return (PCIE_MMIO_PHY_ADDR + (PCIE_MMIO_PHY_ADDR_LEN - 1));
}

u32 rtk_pcie_139x_mmio_len(void)
{
	return PCIE_MMIO_PHY_ADDR_LEN;
}

u32 rtk_pcie_139x_read(u32 addr, u8 size)
{
	u32 rval = 0;
	u32 mask;
	u32 translate_val = 0;
	u32 tmp_addr = addr & 0xFFF;
	unsigned long irqL;
	u32 pci_error_status = 0;
	int retry_cnt = 0;
	u8 retry = 5;

	spin_lock_irqsave(&rtk_pcie_139x_lock, irqL);

	/* PCIE1.1 0x9804FCEC, PCIE2.0 0x9803CCEC & 0x9803CC68
	 * can't be used because of 1295 hardware issue.
	 */
	if (tmp_addr == 0xCEC || tmp_addr == 0xC68) {
		mask = PCIE_IO_2K_MASK;
		rtk_pcie_139x_ctrl_write(0xD00, PCIE_IO_2K_MASK);
		translate_val = rtk_pcie_139x_ctrl_read(0xD04);
		rtk_pcie_139x_ctrl_write(0xD04, translate_val | (addr & mask));
	} else if (addr >= 0x10000) {
		mask = PCIE_IO_64K_MASK;
		translate_val = rtk_pcie_139x_ctrl_read(0xD04);
		rtk_pcie_139x_ctrl_write(0xD04, translate_val | (addr & mask));
	} else
		mask = 0x0;

pci_read_139x_retry:

#if 0 /* ToDo: Fix me */

#ifdef CONFIG_RTK_SW_LOCK_API
	/* All RBUS1 driver need to have a workaround
	 * for emmc hardware error.
	 * Need to protect 0xXXXX_X8XX~ 0xXXXX_X9XX.
	 */
	if ((tmp_addr > 0x7FF) && (tmp_addr < 0xA00))
		rtk_lockapi_lock(flags, __func__);
#endif
#endif

	switch (size) {
	case 1:
		rval = rtk_pcie_139x_direct_cfg_read_byte((addr & ~mask));
		break;
	case 2:
		rval = rtk_pcie_139x_direct_cfg_read_word((addr & ~mask));
		break;
	case 4:
		rval = rtk_pcie_139x_direct_cfg_read((addr & ~mask));
		break;
	default:
		pr_info("RTD139X: %s: wrong size %d\n", __func__, size);
		break;
	}
#if 0 /* ToDo: Fix me */

#ifdef CONFIG_RTK_SW_LOCK_API
	if ((tmp_addr > 0x7FF) && (tmp_addr < 0xA00))
		rtk_lockapi_unlock(flags, __func__);
#endif
#endif

	//DLLP error patch
	pci_error_status = rtk_pcie_139x_ctrl_read(0xc7c);
	if (pci_error_status & 0x1F) {
		rtk_pcie_139x_ctrl_write(0xc7c, pci_error_status);
		pr_info("RTD139X: %s: DLLP(#%d) 0x%x reg=0x%x val=0x%x\n",
			__func__, retry_cnt, pci_error_status, addr, rval);

		if (retry_cnt < retry) {
			retry_cnt++;
			goto pci_read_139x_retry;
		}
	}

	/* PCIE1.1 0x9804FCEC, PCIE2.0 0x9803CCEC & 0x9803CC68
	 * can't be used because of 1295 hardware issue.
	 */
	if (tmp_addr == 0xCEC || tmp_addr == 0xC68) {
		rtk_pcie_139x_ctrl_write(0xD04, translate_val);
		rtk_pcie_139x_ctrl_write(0xD00, PCIE_IO_64K_MASK);
	} else if (addr >= 0x10000) {
		rtk_pcie_139x_ctrl_write(0xD04, translate_val);
	}

	spin_unlock_irqrestore(&rtk_pcie_139x_lock, irqL);

	return rval;
}
EXPORT_SYMBOL(rtk_pcie_139x_read);

void rtk_pcie_139x_write(u32 addr, u8 size, u32 wval)
{
	u32 mask;
	u32 translate_val = 0;
	u32 tmp_addr = addr & 0xFFF;
	unsigned long irqL;

	spin_lock_irqsave(&rtk_pcie_139x_lock, irqL);

	/* PCIE1.1 0x9804FCEC, PCIE2.0 0x9803CCEC & 0x9803CC68
	 * can't be used because of 1295 hardware issue.
	 */
	if (tmp_addr == 0xCEC || tmp_addr == 0xC68) {
		mask = PCIE_IO_2K_MASK;
		rtk_pcie_139x_ctrl_write(0xD00, PCIE_IO_2K_MASK);
		translate_val = rtk_pcie_139x_ctrl_read(0xD04);
		rtk_pcie_139x_ctrl_write(0xD04, translate_val | (addr & mask));
	} else if (addr >= 0x10000) {
		mask = PCIE_IO_64K_MASK;
		translate_val = rtk_pcie_139x_ctrl_read(0xD04);
		rtk_pcie_139x_ctrl_write(0xD04, translate_val | (addr & mask));
	} else
		mask = 0x0;
#if 0 /* ToDo: Fix me */
#ifdef CONFIG_RTK_SW_LOCK_API
	/* All RBUS1 driver need to have a workaround
	 * for emmc hardware error.
	 * Need to protect 0xXXXX_X8XX~ 0xXXXX_X9XX.
	 */
	if ((tmp_addr > 0x7FF) && (tmp_addr < 0xA00))
		rtk_lockapi_lock(flags, __func__);
#endif
#endif

	switch (size) {
	case 1:
		rtk_pcie_139x_direct_cfg_write_byte((addr&~mask), wval);
		break;
	case 2:
		rtk_pcie_139x_direct_cfg_write_word((addr&~mask), wval);
		break;
	case 4:
		rtk_pcie_139x_direct_cfg_write((addr&~mask), wval);
		break;
	default:
		pr_info("RTD139X: %s: wrong size %d\n", __func__, size);
		break;
	}

#if 0 /* ToDo: Fix me */
#ifdef CONFIG_RTK_SW_LOCK_API
	if ((tmp_addr > 0x7FF) && (tmp_addr < 0xA00))
		rtk_lockapi_unlock(flags, __func__);
#endif
#endif

	/* PCIE1.1 0x9804FCEC, PCIE2.0 0x9803CCEC & 0x9803CC68
	 * can't be used because of 1295 hardware issue.
	 */
	if (tmp_addr == 0xCEC || tmp_addr == 0xC68) {
		rtk_pcie_139x_ctrl_write(0xD04, translate_val);
		rtk_pcie_139x_ctrl_write(0xD00, PCIE_IO_64K_MASK);
	} else if (addr >= 0x10000) {
		rtk_pcie_139x_ctrl_write(0xD04, translate_val);
	}

	spin_unlock_irqrestore(&rtk_pcie_139x_lock, irqL);
}
EXPORT_SYMBOL(rtk_pcie_139x_write);

static int _indirect_cfg_write(unsigned long addr,
					unsigned long data,
					unsigned char size)
{
	unsigned long status;
	unsigned char mask;
	int try_count = 1000;

	if (ADDR_TO_DEVICE_NO(addr) != 0)
		return PCIBIOS_DEVICE_NOT_FOUND;

	mask = _pci_byte_mask(addr, size);

	if (!mask)
		return PCIBIOS_SET_FAILED;

	data = (data << _pci_bit_shift(addr)) & _pci_bit_mask(mask);

	rtk_pcie_139x_ctrl_write(PCIE_INDIR_CTR, 0x12);
	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, CFG_ST_ERROR|CFG_ST_DONE);
	rtk_pcie_139x_ctrl_write(PCIE_CFG_ADDR, addr);
	rtk_pcie_139x_ctrl_write(PCIE_CFG_WDATA, data);

	if (size == 4)
		rtk_pcie_139x_ctrl_write(PCIE_CFG_EN, 0x1);
	else
		rtk_pcie_139x_ctrl_write(PCIE_CFG_EN,
			BYTE_CNT(mask) | BYTE_EN | WRRD_EN(1));

	rtk_pcie_139x_ctrl_write(PCIE_CFG_CT, GO_CT);

	do {
		status = rtk_pcie_139x_ctrl_read(PCIE_CFG_ST);
		udelay(50);
	} while (!(status & CFG_ST_DONE) && try_count--);

	if (try_count < 0) {
		PCI_CFG_WARNING("Write config data (%p) failed - timeout\n",
				(void *) addr);
		goto error_occur;
	}

	if (rtk_pcie_139x_ctrl_read(PCIE_CFG_ST) & CFG_ST_ERROR) {
		if (status & CFG_ST_DETEC_PAR_ERROR)
			PCI_CFG_WARNING("Write config data failed - PAR error detected\n");
		if (status & CFG_ST_SIGNAL_SYS_ERROR)
			PCI_CFG_WARNING("Write config data failed - system error\n");
		if (status & CFG_ST_REC_MASTER_ABORT)
			PCI_CFG_WARNING("Write config data failed - master abort\n");
		if (status & CFG_ST_REC_TARGET_ABORT)
			PCI_CFG_WARNING("Write config data failed - target abort\n");
		if (status & CFG_ST_SIG_TAR_ABORT)
			PCI_CFG_WARNING("Write config data failed - tar abort\n");

		goto error_occur;
	}

	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, CFG_ST_ERROR|CFG_ST_DONE);

	return PCIBIOS_SUCCESSFUL;

error_occur:

	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, CFG_ST_ERROR|CFG_ST_DONE);

	return PCIBIOS_SET_FAILED;
}

static int _indirect_cfg_read(unsigned long addr, u32 *pdata,
						unsigned char size)
{
	unsigned long status;
	unsigned char mask;
	int try_count = 20000;

	if (ADDR_TO_DEVICE_NO(addr) != 0)
		return PCIBIOS_DEVICE_NOT_FOUND;

	mask = _pci_byte_mask(addr, size);

	if (!mask)
		return PCIBIOS_SET_FAILED;

	rtk_pcie_139x_ctrl_write(PCIE_INDIR_CTR, 0x10);
	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, 0x3);
	rtk_pcie_139x_ctrl_write(PCIE_CFG_ADDR, (addr & ~0x3));
	rtk_pcie_139x_ctrl_write(PCIE_CFG_EN,
			BYTE_CNT(mask) | BYTE_EN | WRRD_EN(0));
	rtk_pcie_139x_ctrl_write(PCIE_CFG_CT, GO_CT);

	do {
		status = rtk_pcie_139x_ctrl_read(PCIE_CFG_ST);
		udelay(50);
	} while (!(status & CFG_ST_DONE) && try_count--);

	if (try_count < 0) {
		PCI_CFG_WARNING("Read config data (%p) failed - timeout\n",
								(void *) addr);
		goto error_occur;
	}

	if (rtk_pcie_139x_ctrl_read(PCIE_CFG_ST) & CFG_ST_ERROR) {
		if (status & CFG_ST_DETEC_PAR_ERROR)
			PCI_CFG_WARNING("Read config data failed - PAR error detected\n");
		if (status & CFG_ST_SIGNAL_SYS_ERROR)
			PCI_CFG_WARNING("Read config data failed - system error\n");
		if (status & CFG_ST_REC_MASTER_ABORT)
			PCI_CFG_WARNING("Read config data failed - master abort\n");
		if (status & CFG_ST_REC_TARGET_ABORT)
			PCI_CFG_WARNING("Read config data failed - target abort\n");
		if (status & CFG_ST_SIG_TAR_ABORT)
			PCI_CFG_WARNING("Read config data failed - tar abort\n");
		goto error_occur;
	}

	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, 0x3);

	*pdata = (rtk_pcie_139x_ctrl_read(PCIE_CFG_RDATA) & _pci_bit_mask(mask))
							>> _pci_bit_shift(addr);
	return PCIBIOS_SUCCESSFUL;

error_occur:
	rtk_pcie_139x_ctrl_write(PCIE_CFG_ST, 0x3);
	return PCIBIOS_SET_FAILED;
}

static int rtk_pcie_139x_rd_conf(struct pci_bus *bus, unsigned int devfn,
			     int reg, int size, u32 *pval)
{
	unsigned long address;
	int ret = PCIBIOS_DEVICE_NOT_FOUND;
	u32 val = 0;
	u8 retry = 5;


again:
	if (bus->number == 1 && PCI_SLOT(devfn) == 0 && PCI_FUNC(devfn) == 0) {
		if (cfg_direct_access) {

			rtk_pcie_139x_ctrl_write(0xD00, 0xFFFFF000);

			if (size == 1)
				*pval = rtk_pcie_139x_direct_cfg_read_byte(reg);
			else if (size == 2)
				*pval = rtk_pcie_139x_direct_cfg_read_word(reg);
			else if (size == 4)
				*pval = rtk_pcie_139x_direct_cfg_read(reg);

			rtk_pcie_139x_ctrl_write(0xD00, 0xFFF00000);

			ret = PCIBIOS_SUCCESSFUL;

		} else {
			address = _pci_address_conversion(bus, devfn, reg);
			ret = _indirect_cfg_read(address, pval, size);
		}
	}

	val = rtk_pcie_139x_ctrl_read(0xC7C);
	if ((val & 0x1f) && retry) {
		rtk_pcie_139x_ctrl_write(0xC7C, val);
		retry--;
		dev_err(&bus->dev, "pcie dllp error occur = 0x%x\n", val);
		goto again;
	}

	//dev_info(&bus->dev, "rtk_pcie_139x_rd_conf reg = 0x%x, devfun:%d, size=%d, *pval = 0x%x\n",
	//							reg, devfn, size, *pval);

	return ret;
}

static int rtk_pcie_139x_wr_conf(struct pci_bus *bus, unsigned int devfn,
			     int reg, int size, u32 val)
{
	unsigned long address;
	int ret = PCIBIOS_DEVICE_NOT_FOUND;

	//dev_info(&bus->dev, "rtk_pcie_139x_wr_conf reg = 0x%x, val = 0x%x\n",
	//							reg, val);

	if (bus->number == 1 && PCI_SLOT(devfn) == 0 && PCI_FUNC(devfn) == 0) {
		if ((reg == 0x10) || (reg == 0x18) ||
				(reg == 0x20) || (reg == 0x24)) {
			if ((val & 0x98070000) == 0x98070000 || (val & 0x98060000) == 0x98060000 ) {
				rtk_pcie_139x_ctrl_write(0xD04,
						(val&0xfffffff0));
			}
		}

		if (cfg_direct_access) {
			rtk_pcie_139x_ctrl_write(0xD00, 0xFFFFF000);

			if (size == 1)
				rtk_pcie_139x_direct_cfg_write_byte(reg, val);
			else if (size == 2)
				rtk_pcie_139x_direct_cfg_write_word(reg, val);
			else if (size == 4)
				rtk_pcie_139x_direct_cfg_write(reg, val);

			rtk_pcie_139x_ctrl_write(0xD00, 0xFFF00000);
			ret = PCIBIOS_SUCCESSFUL;

		} else {
			address = _pci_address_conversion(bus, devfn, reg);
			ret = _indirect_cfg_write(address, val, size);
		}
	}

	return ret;
}

static struct pci_ops rtk_pcie_139x_ops = {
	.read = rtk_pcie_139x_rd_conf,
	.write = rtk_pcie_139x_wr_conf,
};

static int rtk_pcie_139x_hw_initial(struct device *dev)
{
	bool pci_link_detected;
	int timeout = 0;
	int ret = 0;
	u32 val;
	u32 *phy;
	int size = 0, i = 0;

	/* 0x9801C814[2:0] = 1 */
	val = readl(SYSTEM_BASE1 + 0x14);
	val &= (~0x7);
	val |= 0x1;
	writel(val, SYSTEM_BASE1 + 0x14);

	/* 0x9801C804[3:0] = 0  --PCIE */
	val = readl(SYSTEM_BASE1 + 0x4);
	val &= (~0xf);
	writel(val, SYSTEM_BASE1);

	/* 0x9801C808[7:0] = 1 */
	writeb(0x1, SYSTEM_BASE1 + 0x8);

	reset_control_deassert(rstn_pcie_stitch);
	reset_control_deassert(rstn_pcie);
	reset_control_deassert(rstn_pcie_core);
	reset_control_deassert(rstn_pcie_power);
	reset_control_deassert(rstn_pcie_nonstitch);
	reset_control_deassert(rstn_pcie_phy);
	reset_control_deassert(rstn_pcie_phy_mdio);
	reset_control_deassert(rstn_pcie_sgmii_mdio);

	ret = clk_prepare_enable(pcie_clk);

	if (ret) {
		dev_err(dev, "unable to enable pcie1_clk clock\n");
		clk_disable_unprepare(pcie_clk);
		return -EINVAL;
	}


	rtk_pcie_139x_ctrl_write(0xC00, 0x00140010);

	if (speed_mode == 0) {
		rtk_pcie_139x_ctrl_write(0x0A0,
			(rtk_pcie_139x_ctrl_read(0x0A0)&0xFFFFFFF0)|0x00000001);
	}


	/*phy mdio setting*/
	size = of_property_count_u32_elems(dev->of_node, "phys");
	phy = kmalloc(size * sizeof(u32), GFP_KERNEL);
	of_property_read_u32_array(dev->of_node, "phys", phy, size);
	for (i = 0; i < size; i++) {
		rtk_pcie_139x_ctrl_write(0xC1C, phy[i]);
		mdelay(1);
	}
	kfree(phy);

	// after phy mdio set
	ret = gpio_direction_output(pcie_gpio_29, 0);
	mdelay(100);
	ret = gpio_direction_output(pcie_gpio_29, 1);


	/* set to MMIO */
	if (cfg_direct_access)
		rtk_pcie_139x_ctrl_write(0xC00, 0x00BE0002);
	else
		rtk_pcie_139x_ctrl_write(0xC00, 0x001E0022);

	mdelay(50);

	/* #Link initial setting */
	rtk_pcie_139x_ctrl_write(0x710, 0x00010120);

	do {
		pci_link_detected = (rtk_pcie_139x_ctrl_read(0xCB4) & 0x800);
		if (!pci_link_detected) {
			mdelay(TIMEOUT_RESOLUTION);
			timeout += TIMEOUT_RESOLUTION;
		}
	} while (!pci_link_detected && timeout < PCIE_CONNECT_TIMEOUT);

	if (pci_link_detected) {
		dev_err(dev, "PCIE device has link up in slot 2\n");
	} else {
		reset_control_assert(rstn_pcie_stitch);
		reset_control_assert(rstn_pcie);
		reset_control_assert(rstn_pcie_core);
		reset_control_assert(rstn_pcie_power);
		reset_control_assert(rstn_pcie_nonstitch);
		reset_control_assert(rstn_pcie_phy);
		reset_control_assert(rstn_pcie_phy_mdio);
		reset_control_assert(rstn_pcie_sgmii_mdio);

		clk_disable_unprepare(pcie_clk);
		gpio_free(pcie_gpio_29);

		dev_err(dev, "PCIE device has link down in slot 2\n");
		return -ENODEV;
	}


	/* make sure DBI is working */
	rtk_pcie_139x_ctrl_write(0x04, 0x00000007);

	if (cfg_direct_access) {
		/* #Base 1 */
		rtk_pcie_139x_ctrl_write(0xD08, 0x98061000);

		/* #Mask 1 */
		rtk_pcie_139x_ctrl_write(0xD0C, 0xFFFFF000);

		/* #translate for CFG R/W */
		rtk_pcie_139x_ctrl_write(0xD10, 0x00000000);
	}
	/* #Base 0 */
	rtk_pcie_139x_ctrl_write(0xCFC, 0x98062000);

	/* #Mask 0 */
	rtk_pcie_139x_ctrl_write(0xD00, 0xFFF00000);

	/* #translate for MMIO R/W */
	rtk_pcie_139x_ctrl_write(0xD04, 0x00000000);


	/* prevent pcie hang if dllp error occur*/
	rtk_pcie_139x_ctrl_write(0xC78, 0x200001);

	/* set limit and base register */
	rtk_pcie_139x_ctrl_write(0x20, 0x0000FFF0);
	rtk_pcie_139x_ctrl_write(0x24, 0x0000FFF0);

	return ret;
}

static int rtk_pcie_139x_probe(struct platform_device *pdev)
{
	int ret = 0;
	int size = 0;
	const u32 *prop;
	struct resource pcie_mmio_res;

	resource_size_t iobase = 0;
	LIST_HEAD(res);

	local_pdev = pdev;

	spin_lock_init(&rtk_pcie_139x_lock);

	dev_info(&pdev->dev, "PCIE host driver initial begin.\n");

	prop = of_get_property(pdev->dev.of_node, "speed-mode", &size);
	if (prop) {
		speed_mode = of_read_number(prop, 1);
		if (speed_mode == 0)
			dev_info(&pdev->dev, "Speed Mode: GEN1\n");
		else if (speed_mode == 1)
			dev_info(&pdev->dev, "Speed Mode: GEN2\n");
	} else {
		speed_mode = 0;
	}

	PCIE_CTRL_BASE = of_iomap(pdev->dev.of_node, 0);
	if (!PCIE_CTRL_BASE) {
		dev_err(&pdev->dev, "pcie no ctrl address\n");
		return -EINVAL;
	}

	PCIE_CFG_BASE = of_iomap(pdev->dev.of_node, 1);
	if (!PCIE_CFG_BASE) {
		dev_err(&pdev->dev, "pcie no cfg address\n");
		return -EINVAL;
	} else {
		of_address_to_resource(pdev->dev.of_node, 1, &pcie_mmio_res);
		PCIE_MMIO_PHY_ADDR = pcie_mmio_res.start;
		PCIE_MMIO_PHY_ADDR_LEN = resource_size(&pcie_mmio_res);
	}


	SYSTEM_BASE1 = of_iomap(pdev->dev.of_node, 2);
	if (!SYSTEM_BASE1) {
		dev_err(&pdev->dev, "pcie no base1 address\n");
		return -EINVAL;
	}

	SYSTEM_BASE2 = of_iomap(pdev->dev.of_node, 3);
	if (!SYSTEM_BASE2) {
		dev_err(&pdev->dev, "pcie no base2 address\n");
		return -EINVAL;
	}



	pcie_gpio_29 = of_get_gpio_flags(pdev->dev.of_node, 0, NULL);
	if (gpio_is_valid(pcie_gpio_29)) {
		ret = gpio_request(pcie_gpio_29, "pcie_gpio(29)");
		if (ret < 0)
			pr_err("%s: can't request gpio %d\n",
						__func__, pcie_gpio_29);
	} else {
		pr_err("%s: gpio %d is not valid\n", __func__, pcie_gpio_29);
	}

	pcie_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pcie_clk)) {
		dev_err(&pdev->dev, "pcie clock source missing or invalid\n");
		return PTR_ERR(pcie_clk);
	}

	rstn_pcie_stitch = devm_reset_control_get(&pdev->dev, "stitch");
	if (rstn_pcie_stitch == NULL) {
		dev_err(&pdev->dev, "stitch source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie = devm_reset_control_get(&pdev->dev, "rstn");
	if (rstn_pcie == NULL) {
		dev_err(&pdev->dev, "rstn_pcie source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_core = devm_reset_control_get(&pdev->dev, "core");
	if (rstn_pcie_core == NULL) {
		dev_err(&pdev->dev, "core source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_power = devm_reset_control_get(&pdev->dev, "power");
	if (rstn_pcie_power == NULL) {
		dev_err(&pdev->dev, "power source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_nonstitch = devm_reset_control_get(&pdev->dev, "nonstitch");
	if (rstn_pcie_nonstitch == NULL) {
		dev_err(&pdev->dev, "nonstitch source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_phy = devm_reset_control_get(&pdev->dev, "phy");
	if (rstn_pcie_phy == NULL) {
		dev_err(&pdev->dev, "phy source missing or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_phy_mdio = devm_reset_control_get(&pdev->dev, "phy_mdio");
	if (rstn_pcie_phy_mdio == NULL) {
		dev_err(&pdev->dev, "phy_mdio source missing. or invalid\n");
		return -EINVAL;
	}

	rstn_pcie_sgmii_mdio = devm_reset_control_get(&pdev->dev, "sgmii_mdio");
	if (rstn_pcie_sgmii_mdio == NULL) {
		dev_err(&pdev->dev, "phy_mdio source missing. or invalid\n");
		return -EINVAL;
	}

	reset_control_assert(rstn_pcie_stitch);
	reset_control_assert(rstn_pcie);
	reset_control_assert(rstn_pcie_core);
	reset_control_assert(rstn_pcie_power);
	reset_control_assert(rstn_pcie_nonstitch);
	reset_control_assert(rstn_pcie_phy);
	reset_control_assert(rstn_pcie_phy_mdio);
	reset_control_assert(rstn_pcie_sgmii_mdio);


	if (rtk_pcie_139x_hw_initial(&pdev->dev) < 0) {
		dev_err(&pdev->dev, "rtk_pcie_139x_hw_initial fail\n");
		return -EINVAL;
	}

	/*-------------------------------------------
	 * Register PCI-E host
	 *-------------------------------------------
	 */

	ret = of_pci_get_host_bridge_resources(pdev->dev.of_node,
					0x1, 0xff, &res, &iobase);
	if (ret)
		return ret;

	bus = pci_create_root_bus(&pdev->dev, 1,
				&rtk_pcie_139x_ops, NULL, &res);

	if (!bus)
		return -ENOMEM;

	pci_scan_child_bus(bus);
	pci_assign_unassigned_bus_resources(bus);
	pci_bus_add_devices(bus);

	dev_info(&pdev->dev, "PCIE host driver initial done.\n");

	return ret;
}
#ifdef CONFIG_SUSPEND
static int rtk_pcie_139x_suspend(struct device *dev)
{
	dev_info(dev, "suspend enter ...\n");

	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		rtk_pcie_139x_ctrl_write(0x178, 0xA3FF0001);
		rtk_pcie_139x_ctrl_write(0x098, 0x400);
		rtk_pcie_139x_ctrl_write(0xC6C, 0x00000031);
		dev_info(dev, "Idle mode\n");
	} else {
		dev_info(dev, "Suspend mode\n");

		reset_control_assert(rstn_pcie_stitch);
		reset_control_assert(rstn_pcie);
		reset_control_assert(rstn_pcie_core);
		reset_control_assert(rstn_pcie_power);
		reset_control_assert(rstn_pcie_nonstitch);
		reset_control_assert(rstn_pcie_phy);
		reset_control_assert(rstn_pcie_phy_mdio);
		reset_control_assert(rstn_pcie_sgmii_mdio);
		clk_disable_unprepare(pcie_clk);
		gpio_free(pcie_gpio_29);

	}

	dev_info(dev, "suspend exit ...\n");

	return 0;
}

static int rtk_pcie_139x_resume(struct device *dev)
{
	int ret = 0;

	dev_info(dev, "resume enter ...\n");

	if (RTK_PM_STATE == PM_SUSPEND_STANDBY) {
		rtk_pcie_139x_ctrl_write(0xC6C, 0x00000032);
		dev_info(dev, "Idle mode\n");
	} else {
		dev_info(dev, "Suspend mode\n");
		if (gpio_is_valid(pcie_gpio_29)) {
			ret = gpio_request(pcie_gpio_29, "pcie_gpio(29)");
			if (ret < 0)
				pr_err("%s: can't request gpio %d\n",
						__func__, pcie_gpio_29);
		} else
			pr_err("%s: gpio %d is not valid\n",
						__func__, pcie_gpio_29);

		reset_control_deassert(rstn_pcie_stitch);
		reset_control_deassert(rstn_pcie);
		reset_control_deassert(rstn_pcie_core);
		reset_control_deassert(rstn_pcie_power);
		reset_control_deassert(rstn_pcie_nonstitch);
		reset_control_deassert(rstn_pcie_phy);
		reset_control_deassert(rstn_pcie_phy_mdio);
		reset_control_deassert(rstn_pcie_sgmii_mdio);
		ret = clk_prepare_enable(pcie_clk);
		if (ret) {
			dev_err(dev, "unable to enable pcie_clk clock\n");
			clk_disable_unprepare(pcie_clk);
			return -EINVAL;
		}
		ret = gpio_direction_output(pcie_gpio_29, 0);
		mdelay(100);
		/*Reset PCIE device, Pull high reset signal.*/
		ret = gpio_direction_output(pcie_gpio_29, 1);

		if (rtk_pcie_139x_hw_initial(dev) < 0) {
			dev_err(dev, "rtk_pcie_139x_hw_initial fail\n");
			return -EINVAL;
		}


		if (cfg_direct_access)
			rtk_pcie_139x_ctrl_write(0xC00, 0x00BE0002);
		else
			rtk_pcie_139x_ctrl_write(0xC00, 0x001E0022);
	}

	dev_info(dev, "resume exit ...\n");

	return ret;
}

static void rtk_pcie_139x_shutdown(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "shutdown enter ...\n");

	dev_info(&pdev->dev, "shutdown mode\n");

	reset_control_assert(rstn_pcie_stitch);
	reset_control_assert(rstn_pcie);
	reset_control_assert(rstn_pcie_core);
	reset_control_assert(rstn_pcie_power);
	reset_control_assert(rstn_pcie_nonstitch);
	reset_control_assert(rstn_pcie_phy);
	reset_control_assert(rstn_pcie_phy_mdio);
	reset_control_assert(rstn_pcie_sgmii_mdio);
	clk_disable_unprepare(pcie_clk);
	gpio_free(pcie_gpio_29);

	dev_info(&pdev->dev, "shutdown exit ...\n");
}


static const struct dev_pm_ops rtk_pcie_139x_pm_ops = {
	.suspend_noirq = rtk_pcie_139x_suspend,
	.resume_noirq = rtk_pcie_139x_resume,
};
#endif //CONFIG_SUSPEND
static const struct of_device_id rtk_pcie_139x_match_table[] = {
	{.compatible = "realtek,rtk139x-pcie",},
	{},
};

static struct platform_driver rtk_pcie_139x_driver = {
	.driver = {
		.name = "[RTD139x PCIE]",
		.of_match_table = of_match_ptr(rtk_pcie_139x_match_table),
#ifdef CONFIG_SUSPEND
		.pm = &rtk_pcie_139x_pm_ops,
#endif
	},
	.probe = rtk_pcie_139x_probe,
	.shutdown = rtk_pcie_139x_shutdown,
};
module_platform_driver(rtk_pcie_139x_driver);

MODULE_AUTHOR("James Tai <james.tai@realtek.com>");
MODULE_DESCRIPTION("Realtek PCIe host controller driver");
MODULE_LICENSE("GPL v2");
