#ifndef __DT_BINDINGS_RTK_RESET_RTD139X_H
#define __DT_BINDINGS_RTK_RESET_RTD139X_H

/* 0x98000000 */
#define RSTN_MISC               0
#define RSTN_DIP                1
#define RSTN_GSPI               2
#define RSTN_SDS                3
#define RSTN_SDS_REG            4
#define RSTN_HDMI              12
#define RSTN_VE1               13
#define RSTN_VE2               14
#define RSTN_VE1_WRAPPER       15
#define RSTN_AIO               17
#define RSTN_GPU               18
#define RSTN_TVE               19
#define RSTN_VO                20
#define RSTN_LSADC             21
#define RSTN_SE                22
#define RSTN_HSE               23
#define RSTN_DC_PHY            24
#define RSTN_CP                25
#define RSTN_MD                26
#define RSTN_TP                27
#define RSTN_AE                28
#define RSTN_NF                29
#define RSTN_MIPI              30
#define RSTN_RSA               31

/* 0x98000004 */
#define RSTN_JPEG               1
#define RSTN_PCIE0_STITCH       6
#define RSTN_PCIE0_PHY          7
#define RSTN_PCIE0              8
#define RSTN_PCR_CNT            9
#define RSTN_CR                10
#define RSTN_EMMC              11
#define RSTN_SDIO              12
#define RSTN_PCIE0_CORE        13
#define RSTN_PCIE0_POWER       14
#define RSTN_PCIE0_NONSTITCH   15
#define RSTN_I2C_5             16
#define RSTN_I2C_1             26
#define RSTN_UR2               27
#define RSTN_UR1               28
#define RSTN_MISC_SC           29
#define RSTN_SDS_PHY           31

/* 0x98000008 */
#define RSTN_SB2                0

/* 0x98000050 */
#define RSTN_DCPHY_CRT          0
#define RSTN_HDMIRX             5
#define RSTN_FAN               11
#define RSTN_HDMIRX_WRAP       12
#define RSTN_PCIE0_PHY_MDIO    13
#define RSTN_DISP              15
#define RSTN_PCIE0_SGMII_MDIO  16

/* 0x98000088 */
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
#define IRSTN_I2C_1            12
#define IRSTN_CBUS             13
#define IRSTN_USB_DRD          14
#define IRSTN_USB_HOST         15
#define IRSTN_USB_PHY_0        16
#define IRSTN_USB_PHY_1        17
#define IRSTN_USB_PHY_2        18
#define IRSTN_USB              19
#define IRSTN_TYPE_C           20

#endif
