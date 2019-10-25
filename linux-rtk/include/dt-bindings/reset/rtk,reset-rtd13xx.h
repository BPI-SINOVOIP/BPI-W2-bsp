#ifndef __DT_BINDINGS_RTK_RESET_RTD13XX_H
#define __DT_BINDINGS_RTK_RESET_RTD13XX_H

/* 0x98000000 */
#define RSTN_MISC             0x0100
#define RSTN_DIP              0x0102
#define RSTN_GSPI             0x0104
#define RSTN_SDS              0x0106
#define RSTN_SDS_REG          0x0108
#define RSTN_SDS_PHY          0x010a
#define RSTN_VE1_BIST         0x010c
#define RSTN_VE2_BIST         0x010e
#define RSTN_R2RDSC_BIST      0x0110
#define RSTN_RSA              0x0112
#define RSTN_GPU_BIST         0x0114
#define RSTN_DC_PHY           0x0116
#define RSTN_DCPHY_CRT        0x0118
#define RSTN_LSADC            0x011a
#define RSTN_SE               0x011c
#define RSTN_HSE_BIST         0x011e

/* 0x98000004 */
#define RSTN_JPEG             0x0200
#define RSTN_SD               0x0202
#define RSTN_EMMC_BIST        0x0204
#define RSTN_SDIO             0x0206
#define RSTN_PCR_CNT          0x0208
#define RSTN_PCIE0_STITCH     0x020a
#define RSTN_PCIE0_PHY        0x020c
#define RSTN_PCIE0            0x020e
#define RSTN_PCIE0_CORE       0x0210
#define RSTN_PCIE0_POWER      0x0212
#define RSTN_PCIE0_NONSTITCH  0x0214
#define RSTN_PCIE0_PHY_MDIO   0x0216
#define RSTN_PCIE0_SGMII_MDIO 0x0218
#define RSTN_UR2              0x021a
#define RSTN_UR1              0x021c
#define RSTN_MISC_SC0         0x021e

/* 0x98000008 */
#define RSTN_AE               0x0300
#define RSTN_CABLERX          0x0302
#define RSTN_MD               0x0304
#define RSTN_TP_BIST          0x0306
#define RSTN_NF_BIST          0x0308
#define RSTN_MISC_SC1         0x030a
#define RSTN_I2C_3            0x030c
#define RSTN_FAN              0x030e
#define RSTN_TVE              0x0310
#define RSTN_AIO              0x0312
#define RSTN_VO               0x0314
#define RSTN_MIPI             0x0316
#define RSTN_HDMIRX           0x0318
#define RSTN_HDMIRX_WRAP      0x031a
#define RSTN_HDMI             0x031c
#define RSTN_DISP             0x031e

/* 0x9800000C */
#define RSTN_SATA_PHY_POW1    0x0400
#define RSTN_SATA_PHY_POW0    0x0402
#define RSTN_SATA_MDIO1       0x0404
#define RSTN_SATA_MDIO0       0x0406
#define RSTN_SATA_WRAP        0x0408
#define RSTN_SATA_MAC_P1      0x040a
#define RSTN_SATA_MAC_P0      0x040c
#define RSTN_SATA_MAC_COM     0x040e
#define RSTN_PCIE1_STITCH     0x0410
#define RSTN_PCIE1_PHY        0x0412
#define RSTN_PCIE1            0x0414
#define RSTN_PCIE1_CORE       0x0416
#define RSTN_PCIE1_POWER      0x0418
#define RSTN_PCIE1_NONSTITCH  0x041a
#define RSTN_PCIE1_PHY_MDIO   0x041c
#define RSTN_HDMITOP          0x041e

/* 0x98000010 */
#define RSTN_SB2              0x0500

/* 0x98000014 */
#define RSTN_RNG              0x0600
#define RSTN_DCU              0x0602
#define RSTN_ACPU             0x0604
#define RSTN_VE1              0x0606
#define RSTN_VE3              0x060a
#define RSTN_HSE              0x060e
#define RSTN_CP               0x0610
#define RSTN_R2RDSC           0x0616
#define RSTN_TP               0x061a
#define RSTN_TPB              0x061c
#define RSTN_TPC              0x061e

/* 0x98000068 */
#define RSTN_TPB_BIST         0x0700
#define RSTN_I2C_4            0x0702
#define RSTN_I2C_5            0x0704
#define RSTN_TSIO             0x0706
#define RSTN_VE3_BIST         0x0708
#define RSTN_EDP              0x070a
#define RSTN_CP_BIST          0x070c
#define RSTN_DCU_BIST         0x070e
#define RSTN_KT_BIST          0x0710
#define RSTN_AKL_BIST         0x0712
#define RSTN_TPC_BIST         0x0714
#define RSTN_ACPU_BIST        0x0718
#define RSTN_SPI2EMMC         0x071a
#define RSTN_EARC             0x071c

/* 0x98000088 */
#define RSTN_DSC              0x0800
#define RSTN_ND               0x0802
#define RSTN_AKL              0x0804
#define RSTN_SCE              0x0806
#define RSTN_KT               0x0808

/* 0x98000090 */
#define RSTN_PCIE2_STITCH     0x0900
#define RSTN_PCIE2_PHY        0x0902
#define RSTN_PCIE2            0x0904
#define RSTN_PCIE2_CORE       0x0906
#define RSTN_PCIE2_POWER      0x0908
#define RSTN_PCIE2_NONSTITCH  0x090a
#define RSTN_PCIE2_PHY_MDIO   0x090c
#define RSTN_DCPHY_UMCTL2     0x090e

/* 0x98000094 */
#define RSTN_NF               0x0a00

/* 0x98000454 */
#define RSTN_EMMC             0x0b00

/* 0x98000458 */
#define RSTN_GPU              0x0c00

/* 0x9800045c */

/* 0x98000460 */

/* 0x98000464 */
#define RSTN_VE2              0x0f00

/* 0x98007088 */
#define RSTN_IR                 1
#define RSTN_CEC0               2
#define RSTN_CEC1               3
#define RSTN_ISO_GSPI           4
#define RSTN_CBUSTX             5
#define RSTN_CBUSRX             6
#define RSTN_LSADC_ECOA2        7
#define RSTN_UR0                8
#define RSTN_GMAC               9
#define RSTN_GPHY              10
#define RSTN_I2C_0             11
#define RSTN_I2C_1             12
#define RSTN_CBUS              13
#define RSTN_USB_DRD           14
#define RSTN_USB_HOST          15
#define RSTN_USB_PHY_0         16
#define RSTN_USB_PHY_1         17
#define RSTN_USB_PHY_2         18
#define RSTN_USB               19
#define RSTN_TYPE_C            20
#define RSTN_USB_U3_HOST       21
#define RSTN_USB3_PHY0_POW     22
#define RSTN_USB3_P0_MDIO      23
#define RSTN_USB3_PHY1_POW     24
#define RSTN_USB3_P1_MDIO      25

#endif /* __DT_BINDINGS_RTK_RESET_RTD13XX_H */
