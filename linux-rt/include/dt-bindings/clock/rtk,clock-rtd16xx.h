#ifndef __DT_BINDINGS_RTK_CLOCK_RTD16XX_H
#define __DT_BINDINGS_RTK_CLOCK_RTD16XX_H

/* 0x98000050 */
#define CLK_EN_MISC             0
#define CLK_EN_PCIE0            2
#define CLK_EN_DIP              4
#define CLK_EN_GSPI             6
#define CLK_EN_PCR              8
#define CLK_EN_ISO_MISC        10
#define CLK_EN_SDS             12
#define CLK_EN_HDMI            14
#define CLK_EN_AIO             16
#define CLK_EN_GPU             18
#define CLK_EN_VE1             20
#define CLK_EN_VE2             22
#define CLK_EN_TVE             24
#define CLK_EN_VO              26
#define CLK_EN_LSADC           28
#define CLK_EN_SE              30

/* 0x98000054 */
#define CLK_EN_DCU              0
#define CLK_EN_CP               2
#define CLK_EN_MD               4
#define CLK_EN_TP               6
#define CLK_EN_RSA              8
#define CLK_EN_NF              10
#define CLK_EN_EMMC            12
#define CLK_EN_SD              14
#define CLK_EN_SDIO_IP         16
#define CLK_EN_MIPI            18
#define CLK_EN_EMMC_IP         20
#define CLK_EN_SDIO            22
#define CLK_EN_SD_IP           24
#define CLK_EN_CABLERX         26
#define CLK_EN_TPB             28
#define CLK_EN_MISC_SC1        30

/* 0x98000058 */
#define CLK_EN_MISC_I2C_3       0
#define CLK_EN_SCPU             2
#define CLK_EN_JPEG             4
#define CLK_EN_ACPU             6
#define CLK_EN_AE               8
#define CLK_EN_MISC_SC0        10
#define CLK_EN_AIO_AU_CODEC    12
#define CLK_EN_AIO_MOD         14
#define CLK_EN_AIO_DA          16
#define CLK_EN_AIO_HDMI        18
#define CLK_EN_AIO_SPDIF       20
#define CLK_EN_AIO_I2S         22
#define CLK_EN_AIO_MCLK        24
#define CLK_EN_HDMIRX          26
#define CLK_EN_HSE             28
#define CLK_EN_UR2             30

/* 0x9800005C */
#define CLK_EN_UR1              0
#define CLK_EN_FAN              2
#define CLK_EN_DCPHY_0          4
#define CLK_EN_DCPHY_1          6
#define CLK_EN_SATA_WRAP_SYS    8
#define CLK_EN_SATA_WRAP_SYSH  10
#define CLK_EN_SATA_MAC_SYSH   12
#define CLK_EN_R2RDSC          14
#define CLK_EN_PCIE1           18
#define CLK_EN_MISC_I2C_4      20
#define CLK_EN_MISC_I2C_5      22
#define CLK_EN_TSIO            24
#define CLK_EN_VE3             26
#define CLK_EN_EDP             28
#define CLK_EN_TSIO_TRX        30

/* 0x9800708C */
#define CLK_EN_MISC_MIX         0
#define CLK_EN_MISC_VFD         1
#define CLK_EN_MISC_CEC0        2
#define CLK_EN_CBUSRX_SYS       3
#define CLK_EN_CBUSTX_SYS       4
#define CLK_EN_CBUS_SYS         5
#define CLK_EN_CBUS_OSC         6
#define CLK_EN_MISC_IR          7
#define CLK_EN_MISC_UR0         8
#define CLK_EN_I2C0             9
#define CLK_EN_I2C1            10
#define CLK_EN_ETN_250M        11
#define CLK_EN_ETN_SYS         12
#define CLK_EN_USB_DRD         13
#define CLK_EN_USB_HOST        14
#define CLK_EN_USB_U3_HOST     15
#define CLK_EN_USB             16

/* CC */
#define CC_PLL_SCPU             0
#define CC_PLL_BUS              2
#define CC_CLK_SYS              3
#define CC_CLK_SYS_SB2          4
#define CC_PLL_DCSB             5
#define CC_CLK_SYSH             6
#define CC_PLL_DDSA             7
#define CC_PLL_DDSB             8
#define CC_PLL_GPU              9
#define CC_CLK_GPU             10
#define CC_PLL_VE1             11
#define CC_PLL_VE2             12
#define CC_CLK_VE1             13
#define CC_CLK_VE2             14
#define CC_CLK_VE3             15
#define CC_CLK_VE2_BPU         16
#define CC_CLK_MAX             17

#endif /* __DT_BINDINGS_RTK_CLOCK_RTD16XX_H */


