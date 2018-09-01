/*
 * rtd129x_efuse.h - Realtek eFuse Header
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * Author: Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _RTD129x_EFUSE_H_
#define _RTD129x_EFUSE_H_ 

#define EFUSE_MEM_SIZE         0x00000800
#define EFUSE_OTP_SIZE         0x00000400
#define EFUSE_MAX_ENTRY_SIZE   128

/* eFuse Pattern ID */
#define EFUSE_UUID                    0
#define EFUSE_ETN_PHY                 1
#define EFUSE_ETN_PHY_RC              2
#define EFUSE_ETN_PHY_R               3
#define EFUSE_ETN_PHY_AMP             4
#define EFUSE_ETN_PHY_ADC             5
#define EFUSE_PWR_ID                  6
#define EFUSE_PACKAGE_ID              7
#define EFUSE_USB_CC_EN               8
#define EFUSE_USB_CC1_4_7_K_CAL       9
#define EFUSE_USB_CC1_12_K_CAL       10
#define EFUSE_USB_CC2_4_7_K_CAL      11
#define EFUSE_USB_CC2_12_K_CAL       12
#define EFUSE_TOP_IDDQ               13
#define EFUSE_CPU_IDDQ               14
#define EFUSE_USB_DP_DM              15
#define EFUSE_CC_CAL                 16
#define EFUSE_CHIP_ID                17
#define EFUSE_PROG_RVD               18

u8  efuse_readb(unsigned long addr);
u16 efuse_readw(unsigned long addr);
u32 efuse_readl(unsigned long addr);
u64 efuse_readq(unsigned long addr);
int efuse_read_pattern(int id, unsigned char *buf, int *size);

#endif /* _RTD129x_EFUSE_H_ */
