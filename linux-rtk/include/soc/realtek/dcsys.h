/*
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __SOC_REALTEK_DCSYS_H_INCLUDED
#define __SOC_REALTEK_DCSYS_H_INCLUDED

enum {
	DCSYS_PERFCNT_ID_TOTAL_0,
	DCSYS_PERFCNT_ID_TOTAL_1,
	DCSYS_PERFCNT_ID_SYSH_0,
	DCSYS_PERFCNT_ID_SYSH_1,
	DCSYS_PERFCNT_ID_SYSH_2,
	DCSYS_PERFCNT_ID_SYSH_3,
	DCSYS_PERFCNT_ID_SYSH_4,
	DCSYS_PERFCNT_ID_SYSH_5,
	DCSYS_PERFCNT_ID_SYSH_6,
	DCSYS_PERFCNT_ID_SYSH_7,
	DCSYS_PERFCNT_ID_SYS_0,
	DCSYS_PERFCNT_ID_SYS_1,
	DCSYS_PERFCNT_ID_SYS_2,
};

#define DCSYS_PROG_DCSEL_MASK           (0x80)
#define DCSYS_PROG_DCSEL_DC0            (0x00)
#define DCSYS_PROG_DCSEL_DC1            (0x80)
#define DCSYS_PROG_BRIDGE_ID_MASK       (0x78)

/* platform prog_sel definitions */
#define KYLIN_PROG_SEL_VO               (0x00)
#define KYLIN_PROG_SEL_AIO              (0x0a)
#define KYLIN_PROG_SEL_CP               (0x11)
#define KYLIN_PROG_SEL_MD               (0x13)
#define KYLIN_PROG_SEL_NAT2             (0x14)
#define KYLIN_PROG_SEL_JPEG             (0x15)
#define KYLIN_PROG_SEL_TP               (0x17)
#define KYLIN_PROG_SEL_NAT              (0x12)
#define KYLIN_PROG_SEL_GPU              (0x19)
#define KYLIN_PROG_SEL_SCPU             (0x20)
#define KYLIN_PROG_SEL_KCPU             (0x21)
#define KYLIN_PROG_SEL_ACPU             (0x23)
#define KYLIN_PROG_SEL_AEE              (0x28)
#define KYLIN_PROG_SEL_ADE              (0x29)
#define KYLIN_PROG_SEL_USB              (0x2a)
#define KYLIN_PROG_SEL_ETN              (0x2e)
#define KYLIN_PROG_SEL_VE1              (0x30)
#define KYLIN_PROG_SEL_VE2              (0x31)
#define KYLIN_PROG_SEL_VE3              (0x32)
#define KYLIN_PROG_SEL_SE               (0x38)
#define KYLIN_PROG_SEL_MIPI             (0x40)
#define KYLIN_PROG_SEL_SATA             (0x48)
#define KYLIN_PROG_SEL_CR               (0x50)
#define KYLIN_PROG_SEL_NF               (0x53)
#define KYLIN_PROG_SEL_PCIE0            (0x54)
#define KYLIN_PROG_SEL_PCIE1            (0x56)

#define HERCULES_PROG_SEL_VO            (0x00)
#define HERCULES_PROG_SEL_AIO           (0x0a)
#define HERCULES_PROG_SEL_CP            (0x11)
#define HERCULES_PROG_SEL_MD            (0x13)
#define HERCULES_PROG_SEL_JPEG          (0x15)
#define HERCULES_PROG_SEL_GPU           (0x19)
#define HERCULES_PROG_SEL_TP            (0x17)
#define HERCULES_PROG_SEL_SCPU          (0x20)
#define HERCULES_PROG_SEL_HIF           (0x22)
#define HERCULES_PROG_SEL_ACPU          (0x23)
#define HERCULES_PROG_SEL_SCPU_SWC      (0x25)
#define HERCULES_PROG_SEL_AEE           (0x28)
#define HERCULES_PROG_SEL_ADE           (0x29)
#define HERCULES_PROG_SEL_USB           (0x2a)
#define HERCULES_PROG_SEL_SD            (0x2b)
#define HERCULES_PROG_SEL_PCIE          (0x2c)
#define HERCULES_PROG_SEL_SDIO          (0x2d)
#define HERCULES_PROG_SEL_ETN           (0x2e)
#define HERCULES_PROG_SEL_VE1           (0x30)
#define HERCULES_PROG_SEL_VE2           (0x31)
#define HERCULES_PROG_SEL_SE            (0x38)
#define HERCULES_PROG_SEL_MIPI          (0x40)
#define HERCULES_PROG_SEL_EMMC          (0x50)
#define HERCULES_PROG_SEL_NF            (0x53)
#define HERCULES_PROG_SEL_DIP           (0x58)
#define HERCULES_PROG_SEL_HSE_REE       (0x60)
#define HERCULES_PROG_SEL_HSE_TEE       (0x65)

#define THOR_PROG_SEL_VO                (0x00)
#define THOR_PROG_SEL_AIO               (0x0A)
#define THOR_PROG_SEL_R2RDSC            (0x10)
#define THOR_PROG_SEL_CP                (0x11)
#define THOR_PROG_SEL_AEE               (0x12)
#define THOR_PROG_SEL_MD                (0x13)
#define THOR_PROG_SEL_ADE               (0x14)
#define THOR_PROG_SEL_JPEG              (0x15)
#define THOR_PROG_SEL_TPB               (0x16)
#define THOR_PROG_SEL_TP                (0x17)
#define THOR_PROG_SEL_GPU               (0x19)
#define THOR_PROG_SEL_SCPU              (0x20)
#define THOR_PROG_SEL_SCPU_NWC          (0x25)
#define THOR_PROG_SEL_ACPU              (0x23)
#define THOR_PROG_SEL_HIF               (0x22)
#define THOR_PROG_SEL_USB               (0x2A)
#define THOR_PROG_SEL_PCIE              (0x2C)
#define THOR_PROG_SEL_SDIO              (0x2D)
#define THOR_PROG_SEL_EMMC              (0x50)
#define THOR_PROG_SEL_VE1               (0x30)
#define THOR_PROG_SEL_VE2               (0x31)
#define THOR_PROG_SEL_VE3               (0x32)
#define THOR_PROG_SEL_SE                (0x38)
#define THOR_PROG_SEL_MIPI              (0x40)
#define THOR_PROG_SEL_SATA              (0x48)
#define THOR_PROG_SEL_ETN               (0x2E)
#define THOR_PROG_SEL_SD                (0x51)
#define THOR_PROG_SEL_PCIE_2_SATA       (0x52)
#define THOR_PROG_SEL_NF                (0x53)
#define THOR_PROG_SEL_TSIO              (0x54)
#define THOR_PROG_SEL_DIP               (0x58)
#define THOR_PROG_SEL_HSE_REE           (0x60)
#define THOR_PROG_SEL_HSE_TEE           (0x65)


#define DCSYS_CA_DC_SEL_MASK            (0x8)
#define DCSYS_CA_DC_SEL_DC0             (0x0)
#define DCSYS_CA_DC_SEL_DC1             (0x8)
#define DCSYS_CA_SEL_MASK               (0x7)

#define DCSYS_CA_SEL_NONE               (0x0)
#define DCSYS_CA_SEL_VE1                (0x1)
#define DCSYS_CA_SEL_SE                 (0x2)
#define DCSYS_CA_SEL_GPU                (0x3)
#define DCSYS_CA_SEL_SATA               (0x4)
#define DCSYS_CA_SEL_VE2                (0x5)
#define DCSYS_CA_SEL_DIP                (0x6)
#define DCSYS_CA_SEL_HSE                (0x7)


#endif
