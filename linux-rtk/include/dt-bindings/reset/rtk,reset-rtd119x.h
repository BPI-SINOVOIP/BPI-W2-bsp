#ifndef __DT_BINDINGS_RTK_RESET_RTD119X_H
#define __DT_BINDINGS_RTK_RESET_RTD119X_H

/* 0x18000000 */
#define RSTN_MISC               0
#define RSTN_RNG                1
#define RSTN_USB3_POW           2
#define RSTN_GSPI               3
#define RSTN_USB3_P0_MDIO       4
#define RSTN_VE_H265            5
#define RSTN_USB                6
#define RSTN_USB_PHY0           8
#define RSTN_USB_PHY1           9
#define RSTN_HDMIRX            11
#define RSTN_HDMI              12
#define RSTN_ETN               14
#define RSTN_AIO               15
#define RSTN_GPU               16
#define RSTN_VE_H264           17
#define RSTN_VE_JPEG           18
#define RSTN_TVE               19
#define RSTN_VO                20
#define RSTN_LVDS              21
#define RSTN_SE                22
#define RSTN_DCU               23
#define RSTN_DC_PHY            24
#define RSTN_CP                25
#define RSTN_MD                26
#define RSTN_TP                27
#define RSTN_AE                28
#define RSTN_NF                29
#define RSTN_MIPI              30

/* 0x18000004 */
#define RSTN_ACPU               0
#define RSTN_VCPU               1
#define RSTN_PCR_CNT            9
#define RSTN_CR                10
#define RSTN_EMMC              11
#define RSTN_SDIO              12
#define RSTN_I2C_5             18
#define RSTN_RTC               20
#define RSTN_I2C_4             23
#define RSTN_I2C_3             24
#define RSTN_I2C_2             25
#define RSTN_I2C_1             26
#define RSTN_UR1               28

/* 0x18007088 */
#define IRSTN_VFD               0
#define IRSTN_IR                1
#define IRSTN_CEC0              2
#define IRSTN_CEC1              3
#define IRSTN_DP                4
#define IRSTN_CBUSTX            5
#define IRSTN_CBUSRX            6
#define IRSTN_EFUSE             7
#define IRSTN_UR0               8
#define IRSTN_GMAC              9
#define IRSTN_GPHY             10
#define IRSTN_I2C_0            11
#define IRSTN_I2C_6            12
#define IRSTN_CBUS             13

#endif
