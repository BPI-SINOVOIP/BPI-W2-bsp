/*
 * rtk_pcie.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

void rtk_pcie1_write(u32 addr, u8 size, u32 wval);
u32 rtk_pcie1_read(u32 addr, u8 size);
void rtk_pcie2_write(u32 addr, u8 size, u32 wval);
u32 rtk_pcie2_read(u32 addr, u8 size);
u32 rtk_pcie_mmio_start(void);
u32 rtk_pcie_mmio_end(void);
u32 rtk_pcie_mmio_len(void);
u32 rtk_pcie2_mmio_start(void);
u32 rtk_pcie2_mmio_end(void);
u32 rtk_pcie2_mmio_len(void);
