/* rtk_dc_sys_dbg.h - DC system bus debug driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

static void __iomem *DCSYS_BASE;

struct module_id {
	int id;
	char *name;
};

#ifdef CONFIG_ARCH_RTD119X

#define MODULE_NUM 17

#define B_VO 0x00
#define B_SB0 0x01
#define B_SB1 0x02
#define B_GPU 0x03
#define B_CPU 0x04
#define B_SB2 0x04
#define B_SB3 0x05
#define B_VE 0x06
#define B_SE 0x07
#define B_MIPI 0x08

//#define M_OSD	0x00	//not inplement in phoenix
//#define M_V1 0x01	//not inplement in phoenix
#define M_AIO 0x02
#define M_CR 0x00
#define M_CP 0x01
#define M_USB 0x02
#define M_NF 0x03
#define M_ETN 0x06
#define M_TP 0x07
#define M_GPU 0x01
#define M_ACPU 0x00
#define M_AEE 0x00
#define M_ADE 0x01
#define M_MD 0x03
#define M_JPEG 0x05
#define M_HIF 0x06
#define M_VE 0x00
#define M_SE 0x00
#define M_MIPI 0x00

#define AIO_ID ((B_SB0 << 3) | M_AIO)
#define CR_ID ((B_SB1 << 3) | M_CR)
#define CP_ID ((B_SB1 << 3) | M_CP)
#define USB_ID ((B_SB1 << 3) | M_USB)
#define NF_ID ((B_SB1 << 3) | M_NF)
#define ETN_ID ((B_SB1 << 3) | M_ETN)
#define TP_ID ((B_SB1 << 3) | M_TP)
#define GPU_ID ((B_GPU << 3) | M_GPU)
#define ACPU_ID ((B_SB2 << 3) | M_ACPU)
#define AEE_ID ((B_SB3 << 3) | M_AEE)
#define ADE_ID ((B_SB3 << 3) | M_ADE)
#define MD_ID ((B_SB3 << 3) | M_MD)
#define JPEG_ID ((B_SB3 << 3) | M_JPEG)
#define HIF_ID ((B_SB3 << 3) | M_HIF)
#define VE_ID ((B_VE << 3) | M_VE)
#define SE_ID ((B_SE << 3) | M_SE)
#define MIPI_ID ((B_MIPI << 3) | M_MIPI)

struct module_id module_table[MODULE_NUM] = {
	{AIO_ID, "AIO"},
	{CR_ID, "CR"},
	{CP_ID, "CP"},
	{USB_ID, "USB"},
	{NF_ID, "NF"},
	{ETN_ID, "ETN"},
	{TP_ID, "TP"},
	{GPU_ID, "GPU"},
	{ACPU_ID, "ACPU"},
	{AEE_ID, "AEE"},
	{ADE_ID, "ADE"},
	{MD_ID, "MD"},
	{JPEG_ID, "JPEG"},
	{HIF_ID, "HIF"},
	{VE_ID, "VE"},
	{SE_ID, "SE"},
	{MIPI_ID, "MIPI"},
};
#endif

/* Module ID table*/
#ifdef CONFIG_ARCH_RTD129x

#define MODULE_NUM 27

#define B_VO 0x00
#define B_SB0 0x01
#define B_SB1 0x02
#define B_GPU 0x03
#define B_CPU 0x04
#define B_SB2 0x04
#define B_SB3 0x05
#define B_SB4 0x10
#define B_VE 0x06
#define B_SE 0x07
#define B_MIPI 0x08
#define B_SATA 0x09

#define M_VO1 0x00
#define M_AIO 0x02
#define M_CP 0x01
#define M_NAT 0x02
#define M_MD 0x03
#define M_NAT2 0x04
#define M_JPEG 0x05
#define M_TP 0x07
#define M_GPU 0x01
#define M_NWC 0x00
#define M_SWC 0x01
#define M_ACPU 0x03
#define M_HIF 0x04
#define M_AEE 0x00
#define M_ADE 0x01
#define M_USB 0x02
#define M_ETN 0x06
#define M_CR 0x00
#define M_NF 0x03
#define M_PCIE0 0x04
#define M_PCIE1 0x06
#define M_VE1 0x00
#define M_VE2 0x01
#define M_VE3 0x02
#define M_SE 0x00
#define M_MIPI 0x00
#define M_SATA 0x00

#define VO1_ID ((B_VO << 3) | M_VO1)
#define AIO_ID ((B_SB0 << 3) | M_AIO)
#define CP_ID ((B_SB1 << 3) | M_CP)
#define NAT_ID ((B_SB1 << 3) | M_NAT)
#define MD_ID ((B_SB1 << 3) | M_MD)
#define NAT2_ID ((B_SB1 << 3) | M_NAT2)
#define JPEG_ID ((B_SB1 << 3) | M_JPEG)
#define TP_ID ((B_SB1 << 3) | M_TP)
#define GPU_ID ((B_GPU << 3) | M_GPU)
#define CPU_NWC_ID ((B_CPU << 3) | M_NWC)
#define CPU_SWC_ID ((B_CPU << 3) | M_SWC)
#define ACPU_ID ((B_SB2 << 3) | M_ACPU)
#define HIF_ID ((B_SB2 << 3) | M_HIF)
#define AEE_ID ((B_SB3 << 3) | M_AEE)
#define ADE_ID ((B_SB3 << 3) | M_ADE)
#define USB_ID ((B_SB3 << 3) | M_USB)
#define ETN_ID ((B_SB3 << 3) | M_ETN)
#define CR_ID ((B_SB4 << 3) | M_CR)
#define NF_ID ((B_SB4 << 3) | M_NF)
#define PCIE0_ID ((B_SB4 << 3) | M_PCIE0)
#define PCIE1_ID ((B_SB4 << 3) | M_PCIE1)
#define VE1_ID ((B_VE << 3) | M_VE1)
#define VE2_ID ((B_VE << 3) | M_VE2)
#define VE3_ID ((B_VE << 3) | M_VE3)
#define SE_ID ((B_SE << 3) | M_SE)
#define MIPI_ID ((B_MIPI << 3) | M_MIPI)
#define SATA_ID ((B_SATA << 3) | M_SATA)

struct module_id module_table[MODULE_NUM] = {
	{VO1_ID, "VO1"},
	{AIO_ID, "AIO"},
	{CP_ID, "CP"},
	{NAT_ID, "NAT"},
	{MD_ID, "MD"},
	{NAT2_ID, "NAT2"},
	{JPEG_ID, "JPEG"},
	{TP_ID, "TP"},
	{GPU_ID, "GPU"},
	{CPU_NWC_ID, "SCPU_NWC"},
	{CPU_SWC_ID, "SCPU_SWC"},
	{ACPU_ID, "ACPU"},
	{HIF_ID, "HIF"},
	{AEE_ID, "AEE"},
	{ADE_ID, "ADE"},
	{USB_ID, "USB"},
	{ETN_ID, "ETN"},
	{CR_ID, "CR"},
	{NF_ID, "NF"},
	{PCIE0_ID, "PCIE0"},
	{PCIE1_ID, "PCIE1"},
	{VE1_ID, "VE1"},
	{VE2_ID, "VE2"},
	{VE3_ID, "VE3"},
	{SE_ID, "SE"},
	{MIPI_ID, "MIPI"},
	{SATA_ID, "SATA"},
};

#endif /* CONFIG_ARCH_RTD129x */

#ifdef CONFIG_ARCH_RTD139x

#define MODULE_NUM 28

#define B_VO 0x00
#define B_SB0 0x01
#define B_SB1 0x02
#define B_GPU 0x03
#define B_CPU 0x04
#define B_SB2 0x04
#define B_SB3 0x05
#define B_SB4 0x10
#define B_VE 0x06
#define B_SE 0x07
#define B_MIPI 0x08
#define B_SATA 0x09
#define B_DIP 0x11
#define B_HSE 0x12

#define M_VO1 0x00
#define M_AIO 0x02
#define M_CP 0x01
#define M_MD 0x03
#define M_JPEG 0x05
#define M_TP 0x07
#define M_GPU 0x01
#define M_NWC 0x00
#define M_SWC 0x05
#define M_ACPU 0x03
#define M_HIF 0x02
#define M_AEE 0x00
#define M_ADE 0x01
#define M_USB 0x02
#define M_SD 0x03
#define M_PCIE 0x04
#define M_SDIO 0x05
#define M_ETN 0x06
#define M_EMMC 0x00
#define M_NF 0x03
#define M_VE1 0x00
#define M_VE2 0x01
#define M_SE 0x00
#define M_MIPI 0x00
#define M_SATA 0x00
#define M_DIP 0x00
#define M_HSE_REE 0x00
#define M_HSE_TEE 0x05

#define VO1_ID ((B_VO << 3) | M_VO1)
#define AIO_ID ((B_SB0 << 3) | M_AIO)
#define CP_ID ((B_SB1 << 3) | M_CP)
#define MD_ID ((B_SB1 << 3) | M_MD)
#define JPEG_ID ((B_SB1 << 3) | M_JPEG)
#define TP_ID ((B_SB1 << 3) | M_TP)
#define GPU_ID ((B_GPU << 3) | M_GPU)
#define CPU_NWC_ID ((B_CPU << 3) | M_NWC)
#define CPU_SWC_ID ((B_CPU << 3) | M_SWC)
#define ACPU_ID ((B_SB2 << 3) | M_ACPU)
#define HIF_ID ((B_SB2 << 3) | M_HIF)
#define AEE_ID ((B_SB3 << 3) | M_AEE)
#define ADE_ID ((B_SB3 << 3) | M_ADE)
#define USB_ID ((B_SB3 << 3) | M_USB)
#define SD_ID ((B_SB3 << 3) | M_SD)
#define PCIE_ID ((B_SB3 << 3) | M_PCIE)
#define SDIO_ID ((B_SB3 << 3) | M_SDIO)
#define ETN_ID ((B_SB3 << 3) | M_ETN)
#define EMMC_ID ((B_SB4 << 3) | M_EMMC)
#define NF_ID ((B_SB4 << 3) | M_NF)
#define VE1_ID ((B_VE << 3) | M_VE1)
#define VE2_ID ((B_VE << 3) | M_VE2)
#define SE_ID ((B_SE << 3) | M_SE)
#define MIPI_ID ((B_MIPI << 3) | M_MIPI)
#define SATA_ID ((B_SATA << 3) | M_SATA)
#define DIP_ID ((B_DIP << 3) | M_DIP)
#define HSE_REE_ID ((B_HSE << 3) | M_HSE_REE)
#define HSE_TEE_ID ((B_HSE << 3) | M_HSE_TEE)

struct module_id module_table[MODULE_NUM] = {
	{VO1_ID, "VO1"},
	{AIO_ID, "AIO"},
	{CP_ID, "CP"},
	{MD_ID, "MD"},
	{JPEG_ID, "JPEG"},
	{TP_ID, "TP"},
	{GPU_ID, "GPU"},
	{CPU_NWC_ID, "SCPU_NWC"},
	{CPU_SWC_ID, "SCPU_SWC"},
	{ACPU_ID, "ACPU"},
	{HIF_ID, "HIF"},
	{AEE_ID, "AEE"},
	{ADE_ID, "ADE"},
	{USB_ID, "USB"},
	{SD_ID, "SD"},
	{PCIE_ID, "PCIE"},
	{SDIO_ID, "SDIO"},
	{ETN_ID, "ETN"},
	{EMMC_ID, "EMMC"},
	{NF_ID, "NF"},
	{VE1_ID, "VE1"},
	{VE2_ID, "VE2"},
	{SE_ID, "SE"},
	{MIPI_ID, "MIPI"},
	{SATA_ID, "SATA"},
	{DIP_ID, "DIP"},
	{HSE_REE_ID, "HSE_REE"},
	{HSE_TEE_ID, "HSE_TEE"},
};
#endif /* CONFIG_ARCH_RTD139x */

#ifdef CONFIG_ARCH_RTD16xx

#define MODULE_NUM 28

#define B_VO 0x00
#define B_SB0 0x01
#define B_SB1 0x02
#define B_GPU 0x03
#define B_CPU 0x04
#define B_SB2 0x04
#define B_SB3 0x05
#define B_SB4 0x10
#define B_VE 0x06
#define B_SE 0x07
#define B_MIPI 0x08
#define B_SATA 0x09
#define B_DIP 0x11
#define B_HSE 0x12

#define M_VO1 0x00
#define M_AIO 0x02
#define M_CP 0x01
#define M_MD 0x03
#define M_JPEG 0x05
#define M_TP 0x07
#define M_GPU 0x01
#define M_NWC 0x00
#define M_SWC 0x05
#define M_ACPU 0x03
#define M_HIF 0x02
#define M_AEE 0x00
#define M_ADE 0x01
#define M_USB 0x02
#define M_SD 0x03
#define M_PCIE 0x04
#define M_SDIO 0x05
#define M_ETN 0x06
#define M_EMMC 0x00
#define M_NF 0x03
#define M_VE1 0x00
#define M_VE2 0x01
#define M_SE 0x00
#define M_MIPI 0x00
#define M_SATA 0x00
#define M_DIP 0x00
#define M_HSE_REE 0x00
#define M_HSE_TEE 0x05

#define VO1_ID ((B_VO << 3) | M_VO1)
#define AIO_ID ((B_SB0 << 3) | M_AIO)
#define CP_ID ((B_SB1 << 3) | M_CP)
#define MD_ID ((B_SB1 << 3) | M_MD)
#define JPEG_ID ((B_SB1 << 3) | M_JPEG)
#define TP_ID ((B_SB1 << 3) | M_TP)
#define GPU_ID ((B_GPU << 3) | M_GPU)
#define CPU_NWC_ID ((B_CPU << 3) | M_NWC)
#define CPU_SWC_ID ((B_CPU << 3) | M_SWC)
#define ACPU_ID ((B_SB2 << 3) | M_ACPU)
#define HIF_ID ((B_SB2 << 3) | M_HIF)
#define AEE_ID ((B_SB3 << 3) | M_AEE)
#define ADE_ID ((B_SB3 << 3) | M_ADE)
#define USB_ID ((B_SB3 << 3) | M_USB)
#define SD_ID ((B_SB3 << 3) | M_SD)
#define PCIE_ID ((B_SB3 << 3) | M_PCIE)
#define SDIO_ID ((B_SB3 << 3) | M_SDIO)
#define ETN_ID ((B_SB3 << 3) | M_ETN)
#define EMMC_ID ((B_SB4 << 3) | M_EMMC)
#define NF_ID ((B_SB4 << 3) | M_NF)
#define VE1_ID ((B_VE << 3) | M_VE1)
#define VE2_ID ((B_VE << 3) | M_VE2)
#define SE_ID ((B_SE << 3) | M_SE)
#define MIPI_ID ((B_MIPI << 3) | M_MIPI)
#define SATA_ID ((B_SATA << 3) | M_SATA)
#define DIP_ID ((B_DIP << 3) | M_DIP)
#define HSE_REE_ID ((B_HSE << 3) | M_HSE_REE)
#define HSE_TEE_ID ((B_HSE << 3) | M_HSE_TEE)

struct module_id module_table[MODULE_NUM] = {
	{VO1_ID, "VO1"},
	{AIO_ID, "AIO"},
	{CP_ID, "CP"},
	{MD_ID, "MD"},
	{JPEG_ID, "JPEG"},
	{TP_ID, "TP"},
	{GPU_ID, "GPU"},
	{CPU_NWC_ID, "SCPU_NWC"},
	{CPU_SWC_ID, "SCPU_SWC"},
	{ACPU_ID, "ACPU"},
	{HIF_ID, "HIF"},
	{AEE_ID, "AEE"},
	{ADE_ID, "ADE"},
	{USB_ID, "USB"},
	{SD_ID, "SD"},
	{PCIE_ID, "PCIE"},
	{SDIO_ID, "SDIO"},
	{ETN_ID, "ETN"},
	{EMMC_ID, "EMMC"},
	{NF_ID, "NF"},
	{VE1_ID, "VE1"},
	{VE2_ID, "VE2"},
	{SE_ID, "SE"},
	{MIPI_ID, "MIPI"},
	{SATA_ID, "SATA"},
	{DIP_ID, "DIP"},
	{HSE_REE_ID, "HSE_REE"},
	{HSE_TEE_ID, "HSE_TEE"},
};
#endif /* CONFIG_ARCH_RTD16xx */

#define INT2SCPU 0x0
#define INT2ACPU 0x1
#define INT2VCPU 0x2

/* Memory trash detection part */
#define MODE_B0 0
#define W_EN_B2 2
#define INT3_EN_B3 3
#define INT2_EN_B4 4
#define INT1_EN_B5 5
#define CPU_B6 6
#define W_EN4_B8 8
#define INT3_B9 9
#define W_EN3_B10 10
#define INT2_B11 11
#define W_EN2_B12 12
#define INT1_B13 13
#define W_EN1_B14 14
#define ACCESS_T3_B15 15
#define ACCESS_T2_B17 17
#define ACCESS_T1_B19 19
#define ACCESS_T0_B21 21
#define W_EN0_B23 23

#define MOD_ID1_B25 25
#define MOD_ID0_B18 18

#define MEM_TYPE_BIT 30
#define SADDR_BIT 2
#define SADDR_MASK 5
#define EADDR_BIT 2
#define EADDR_MASK 5

#define TYPE_INVAILD 0x0
#define TYPE_R 0x1
#define TYPE_W 0x2
#define TYPE_RW (TYPE_R|TYPE_W)

#define MODE1 0x1
#define MODE2 0x2
#define MODE3 0x3

#define DC_MT_SADDR (DCSYS_BASE + 0x0200)
#define DC_MT_EADDR (DCSYS_BASE + 0x0220)
#define DC_MT_MODE (DCSYS_BASE + 0x0240)
#define DC_MT_TABLE (DCSYS_BASE + 0x0260)
#define DC_MT_ADDCMD_HI (DCSYS_BASE + 0x0280)
#define DC_MT_ADDCMD_LO_0 (DCSYS_BASE + 0x02A0)
#define DC_MT_ADDCMD_LO_1 (DCSYS_BASE + 0x02C0)
#define DC_MT_MISC (DCSYS_BASE + 0x02E0)

#define WRITE_EN(x) (1 << x)
#define ACCESS_TYPE(x, n) (x << n)
#define INIT_EN(x) (1 << x)
#define CPU_TYPE(x) (x << CPU_B6)
#define TRASH_MODE(x) (x << MODE_B0)

#define SADDR(x) (1 << MEM_TYPE_BIT | ((x >> SADDR_MASK) << SADDR_BIT))
#define EADDR(x) ((x >> EADDR_MASK) << EADDR_BIT)

#define INT1_TRIG 0x2000
#define INT2_TRIG 0x800
#define INT3_TRIG 0x200

/* Error command detection part */
#define DC_EC_CTRL (DCSYS_BASE + 0x0300)
#define DC_EC_ADDCMD_HI (DCSYS_BASE + 0x0304)
#define DC_EC_ADDCMD_LO_0 (DCSYS_BASE + 0x0308)
#define DC_EC_ADDCMD_LO_1 (DCSYS_BASE + 0x030C)

#define LARGE_DCSYS1_B30 30
#define LARGE_DCSYS0_B29 29
#define EC_INT_CPU_B27 27
#define EC_INT_EN_B26 26
#define EC_SWAP_EN_B25 25
#define EC_DETECT_EN_B24 24
#define EC_EVER_TRAP1_B23 23
#define EC_EVER_TRAP0_B22 22
#define EC_INT1_B21 21
#define EC_INT0_B20 20
#define OVER_DCSYS1_B19 19
#define OVER_DCSYS0_B18 18

#define WRAP_ERR1_B31 31
#define WRAP_ERR0_B30 30
#define RD_ERR1_B29 29
#define RD_ERR0_B28 28
#define CASE1_B24 24
#define CASE0_B20 20

#define EC_CTRL_EN(x) (1 << x)
#define EC_CPU_TYPE(x) (x << EC_INT_CPU_B27)
