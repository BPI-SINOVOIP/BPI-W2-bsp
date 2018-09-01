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

#ifndef RTK_PCIE_H_
#define RTK_PCIE_H_

#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of.h>

#define PCI_INFO(fmt, args...) pr_info("[RTK PCIE] INFO," fmt, ## args)
#define PCI_WARNING(fmt, args...) pr_warn("[RTK PCIE] WARNING," fmt, ## args)
#define PCI_CFG_WARNING(fmt, args...) \
	pr_alert("[RTK PCIE] CFG WARNING," fmt, ## args)

/* SB2 for PCI */
#define SB2_PCI_BASE0 0x00000030
#define SB2_PCI_BASE1 0x00000034
#define SB2_PCI_BASE2 0x00000038
#define SB2_PCI_BASE3 0x0000003C
#define SB2_PCI_MASK0 0x00000040
#define SB2_PCI_MASK1 0x00000044
#define SB2_PCI_MASK2 0x00000048
#define SB2_PCI_MASK3 0x0000004C
#define SB2_PCI_TRAN0 0x00000050
#define SB2_PCI_TRAN1 0x00000054
#define SB2_PCI_TRAN2 0x00000058
#define SB2_PCI_TRAN3 0x0000005C
#define SB2_PCI_CTRL 0x00000060

/* PCIE Bridge */
#define PCIE_SYS_CTR 0x00000C00U
#define TRANS_EN (1 << 20)
#define PHY_MMIO_TYPE (1 << 19)
#define PHY_MDIO_OE (1 << 18)
#define PHY_MDIO_RSTN (1 << 17)
#define APP_INIT_RST (1 << 16)
#define LOOPBACK_EN (1 << 9)
#define DIR_REQ_INFO_EN (1 << 8)
#define RX_LANE_REVERSAL_EN (1 << 7)
#define TX_LANE_REVERSAL_EN (1 << 6)
#define INDOR_CFG_EN (1 << 5)
#define DIR_CFG_EN (1 << 4)
#define RCV_ADDR0_EN (1 << 3)
#define RCV_ADDR1_EN (1 << 2)
#define APP_LTSSM_EN (1 << 1)
#define RCV_TRANS_EN (1)

#define DVR_INT_CTR 0x00000C04U
#define DVR_GNR_INT 0x00000C08U

#define S_INTP_PCIE_LEGACY_MSI_INT 14
#define S_INTP_PM_TO_ACK_INT 13
#define S_INTP_CFG_SYS_ERR_RC_INT 12
#define S_INTP_PCIE_LEGACY_INT 11
#define S_INTP_CFG_RSDM_VENDOR_MSG_INT 10
#define S_INTP_CFG_PME_MSI 9
#define S_INTP_CFG_PME_INT 8
#define S_INTP_CFG_AER_RC_MSI 7
#define S_INTP_CFG_AER_RC_ERR 6
#define S_INTP_RTGT 5 /* Slave Receiver Interrupt */
#define S_INTP_RCPL /* Master Receiver Interrupt */
#define S_INTP_DIR_CFG 3 /* Direct CFG Interrupt */
#define S_INTP_DIR_MIO 2 /* Direct MIO Interrupt */
#define S_INTP_CFG 1 /* Indirect CFG Interrupt */
#define S_INTP_MIO 0 /* Indirect MIO Interrupt */
#define INTP_PCIE_LEGACY_MSI_INT (1 << INTP_PCIE_LEGACY_MSI_INT)
#define INTP_PM_TO_ACK_INT (1 << INTP_PM_TO_ACK_INT)
#define INTP_CFG_SYS_ERR_RC_INT (1 << INTP_CFG_SYS_ERR_RC_INT)
#define INTP_PCIE_LEGACY_INT (1 << INTP_PCIE_LEGACY_INT)
#define INTP_CFG_RSDM_VENDOR_MSG_INT (1 << INTP_CFG_RSDM_VENDOR_MSG_INT)
#define INTP_CFG_PME_MSI (1 << INTP_CFG_PME_MSI)
#define INTP_CFG_PME_INT (1 << INTP_CFG_PME_INT)
#define INTP_CFG_AER_RC_MSI (1 << INTP_CFG_AER_RC_MSI)
#define INTP_CFG_AER_RC_ERR (1 << INTP_CFG_AER_RC_ERR)
#define INTP_RTGT (1 << INTP_RTGT)
#define INTP_RCPL (1 << INTP_RCPL)
#define INTP_DIR_CFG (1 << INTP_DIR_CFG)
#define INTP_DIR_MIO (1 << INTP_DIR_MIO)
#define INTP_CFG (1 << INTP_CFG)
#define INTP_MIO (1 << INTP_MIO)

#define DVR_PCIE_INT 0x00000C0CU
#define PCIE_INTP_INTD (0x1U << 3)
#define PCIE_INTP_INTC (0x1U << 2)
#define PCIE_INTP_INTB (0x1U << 1)
#define PCIE_INTP_INTA (0x1U)

#define PCIE_DBI_CTR 0x00000C10U
#define DBI_IO_ACCESS (0x1U << 9)
#define DBI_ROM_ACCESS (0x1U << 8)
#define DBI_BAR_NUM(x) ((x & 0x7) << 5)
#define DBI_FUNC_NUM(x) ((x & 0x7) << 2)
#define DBI_SC2_ACCESS (0x1U << 1)
#define DBI_CMD_ACCESS (0x1U)

#define PCIE_INDIR_CTR 0x00000C14
#define PCIE_DIR_CTR 0x00000018U
#define REQ_INFO_ALIGN (0x1U << 13)
#define REQ_INFO_ATTR(x) ((x & 0x3) << 11)
#define REQ_INFO_EP (0x1U << 10)
#define REQ_INFO_TC(x) ((x & 0x7) << 7)
#define REQ_INFO_TYPE(x) ((x & 0x1F) << 2)
#define REQ_INFO_FMT(x) (x & 0x3)

#define PCIE_MDIO_CTR 0x00000C1CU
#define MDIO_DATA(x) ((x & 0xFFFF) << 16) /* MDIO Data */
#define MDIO_PHY_ADDR(x) ((x & 0x7) << 13) /* MDIO PHY Address */
#define MDIO_REG_ADDR(x) ((x & 0x1F) << 8) /* MDIO Register Address */
#define MDIO_BUSY (0x1U << 7)
#define MDIO_ST(x) ((x & 0x03) << 5) /* MDIO Host Control State Monitor */
#define MDIO_RDY (0x1U << 4) /* MDIO PREAMBLE Signal Monitor */
#define MDIO_RATE(x) ((x & 0x3) << 2) /* MDIO Clock Rate */
#define CLK_SYS_1_32(x) 0 /* MDIO Clock Rate = 1/32 */
#define CLK_SYS_1_16(x) 1 /* MDIO Clock Rate = 1/16 */
#define CLK_SYS_1_8(x) 2 /* MDIO Clock Rate = 1/8 */
#define CLK_SYS_1_4(x) 3 /* MDIO Clock Rate = 1/4 */
#define MDIO_SRST (0x1U << 1)
#define MDIO_RDWR(x) (x & 0x1) /* MDIO Read/Write : 0 read, 1 write */

/*
 * Address Translation
 * PCI-E Bridge provides 2 set of control registers
 * for inbound address translation
 */
#define PCIE_BASE0 0x00000C20U
#define PCIE_BASE1 0x00000C24U
#define PCIE_MASK0 0x00000C28U
#define PCIE_MASK1 0x00000C2CU
#define PCIE_TRAN0 0x00000C30U
#define PCIE_TRAN1 0x00000C34U

/*
 * Configuration Access
 * the following registers are used to access configuration
 * space
 */
#define PCIE_CFG_CT 0x00000C38U
#define GO_CT (0x1U)

#define PCIE_CFG_EN 0x00000C3CU
#define BUS_NUM(x) ((x & 0xFF) << 16) /* Bus number */
#define DEV_NUM(x) ((x & 0xF) << 11) /* Device number */
#define FUN_NUM(x) ((x & 0x7) << 8) /* Function number */
#define BYTE_CNT(x) ((x & 0xF) << 4) /* Byte enable bits */
#define ERROR_EN(x) ((x & 0x1) << 2) /* Enable error timeout counter */
#define BYTE_EN (0x1 << 1) /* Byte enable bits enable */
#define WRRD_EN(x) (x & 0x01)
#define WRITE_CFG WRRD_EN(1)
#define READ_CFG WRRD_EN(0)

#define PCIE_CFG_ST 0x00000C40U
#define CFG_ST_ERROR (0x1U << 1)
#define CFG_ST_DONE 0x1U

#define PCIE_CFG_ADDR 0x00000C44U
#define PCIE_CFG_WDATA 0x00000C48U
#define PCIE_CFG_RDATA 0x00000C4CU

/*
 * Memory / IO Access
 * the following registers are used to access configuration
 * space
 */
#define PCIE_MIO_CT 0x00000C50U
#define PCIE_MIO_EN 0x00000C54U

#define TIMEOUT_CNT_VAL(x) ((x & 0xFFFFFFF) << 8)

#define PCIE_MIO_ST 0x00000C58U
#define PCIE_MIO_ADDR 0x00000C5CU
#define PCIE_MIO_WDATA 0x00000C60U
#define PCIE_MIO_RDATA 0x00000C64U

/* MISC */
#define PCIE_CTR 0x00000C68U
#define PCIE_PWR_CTR 0x00000C6CU
#define PCIE_DBG 0x00000C70U
#define PCIE_DIR_ST 0x00000C74U /* Status for Direct Access */
#define CFG_RERROR_ST (0x1U << 1)
#define MIO_RERROR_ST (0x1U)

#define PCIE_DIR_EN 0x00000C78U
#define TIMEOUT_EN (0x1U)

#define PCIE_MAC_ST 0x00000CB4
#define RDLH_LINK_UP (0x1U << 14)
#define PM_XTLH_BLOCK_TLP (0x1U << 13)
#define CFG_BUS_MASTER_EN (0x1U << 12)
#define CFG_PM_NO_SOFT_RST (0x1U << 11)
#define XMLH_LINK_UP (0x1U << 10)
#define LINK_REQ_RST_NOT (0x1U << 9)
#define XMLH_LTSSM_STATE(x) ((x & 0xF) << 4)
#define PM_CURNT_STATE(x) ((x & 0x7) << 1)
#define CFG_CLK_REQ_N (0x1U)

/* PCI-E RC registers */
#define PCI_CFG_REG 0x00000000U /* PCI compatible registers */
#define PCIE_DEV_REG 0x00000040U /* PCI-E Device Configuration Space */
#define PCIE_EXT_REG 0x00000100U /* PCI-E Extend Configuration Space */
#define PCIE_DVR_REG 0x00000C00U /* DVR space register */

#define CFG(addr) (PCI_CFG_REG + (addr))
#define BAR1 0x10
#define BAR2 0x14
#define BAR3 0x18
#define BAR4 0x1C

#define CFG_ST_DETEC_PAR_ERROR (1 << 31)
#define CFG_ST_SIGNAL_SYS_ERROR (1 << 30)
#define CFG_ST_REC_MASTER_ABORT (1 << 29)
#define CFG_ST_REC_TARGET_ABORT (1 << 28)
#define CFG_ST_SIG_TAR_ABORT (1 << 27)

#define TIMEOUT_RESOLUTION 1
#define PCIE_CONNECT_TIMEOUT 60

#define RBUS1_TIMEOUT(x) ((x & 0x7) << 2)
#define RBUS_TIMEOUT(x) (x & 0x3)

#define ADDR_TO_DEVICE_NO(addr) ((addr >> 19) & 0x1F)

static unsigned long _pci_bit_mask(unsigned char byte_mask)
{
	int i;
	unsigned long mask = 0;

	for (i = 0; i < 4; i++) {
		if ((byte_mask >> i) & 0x1)
			mask |= (0xFF << (i << 3));
	}

	return mask;
}

static unsigned long _pci_bit_shift(unsigned long addr)
{
	return ((addr & 0x3) << 3);
}

static unsigned long _pci_byte_mask(unsigned long addr, unsigned char size)
{
	unsigned char offset = (addr & 0x03);

	switch (size) {
	case 0x01:
		return 0x1 << offset;
	case 0x02:
		if (offset <= 2)
			return 0x3 << offset;

		PCI_CFG_WARNING(
			"data cross dword boundrary (addr=%p, length=2)\n",
			(void *) addr);

		break;

	case 0x03:
		if (offset <= 1)
			return 0x7 << offset;

		PCI_CFG_WARNING(
			"data cross dword boundrary (addr=%p, length=3)\n",
			(void *) addr);
		break;

	case 0x04:
		if (offset == 0)
			return 0xF;

		PCI_CFG_WARNING(
			"data cross dword boundrary (addr=%p, length=4)\n",
			(void *) addr);
		break;

	default:
		PCI_CFG_WARNING("size %d should between 1~4\n", size);
	}
	return 0;
}

static unsigned long _pci_address_conversion(struct pci_bus *bus,
	unsigned int devfn, int reg)
{
	int busno = bus->number;
	int dev = PCI_SLOT(devfn);
	int func = PCI_FUNC(devfn);

	return (busno << 24) | (dev << 19) | (func << 16) | reg;
}

#endif /* RTK_PCIE_H_ */
