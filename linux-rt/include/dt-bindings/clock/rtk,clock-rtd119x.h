#ifndef __DT_BINDINGS_RTK_CLOCK_RTD119X_H
#define __DT_BINDINGS_RTK_CLOCK_RTD119X_H

/* 0x1800000c */
#define CLK_EN_MISC             0
#define CLK_EN_HDMIRX           1
#define CLK_EN_GSPI             3
#define CLK_EN_USB              4
#define CLK_EN_PCR              5
#define CLK_EN_ISO_MISC         6
#define CLK_EN_HDMI             8
#define CLK_EN_ETN              9
#define CLK_EN_AIO             10
#define CLK_EN_GPU             11
#define CLK_EN_VE_H264         12
#define CLK_EN_VE_JPEG         13
#define CLK_EN_TVE             14
#define CLK_EN_VO              15
#define CLK_EN_LVDS            16
#define CLK_EN_SE              17
#define CLK_EN_DCU             18
#define CLK_EN_CP              19
#define CLK_EN_MD              20
#define CLK_EN_TP              21
#define CLK_EN_NF              23
#define CLK_EN_EMMC            24
#define CLK_EN_CR              25
#define CLK_EN_SDIO_IP         26
#define CLK_EN_MIPI            27
#define CLK_EN_EMMC_IP         28
#define CLK_EN_VE_H265         29
#define CLK_EN_SDIO            30
#define CLK_EN_SD_IP           31

/* 0x18000010 */
#define CLK_EN_MISC_I2C_5       1
#define CLK_EN_SCPU             2
#define CLK_EN_ACPU             4
#define CLK_EN_VCPU             5
#define CLK_EN_MISC_RTC        10
#define CLK_EN_MISC_I2C_4      13
#define CLK_EN_MISC_I2C_3      14
#define CLK_EN_MISC_I2C_2      15
#define CLK_EN_MISC_I2C_1      16
#define CLK_EN_AIO_AU_CODEC    17
#define CLK_EN_AIO_MOD         18
#define CLK_EN_AIO_DA          19
#define CLK_EN_AIO_HDMI        20
#define CLK_EN_AIO_SPDIF       21
#define CLK_EN_AIO_I2S         22
#define CLK_EN_AIO_MCLK        23
#define CLK_EN_UR1             28

/* 0x1800708C */
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
#define CLK_EN_I2C6            10
#define CLK_EN_ETN_250M        11
#define CLK_EN_ETN_SYS         12

/* CC */
#define CC_PLL_SCPU             0
#define CC_PLL_BUS              1
#define CC_CLK_SYS              2
#define CC_PLL_DCSB             3
#define CC_CLK_SYSH             4
#define CC_PLL_GPU              5
#define CC_CLK_GPU              6
#define CC_PLL_VCPU             7
#define CC_CLK_VE               8
#define CC_CLK_VE1              9
#define CC_CLK_VE2             10
#define CC_CLK_VE2_BPU         11
#define CC_CLK_MAX             12

#endif
