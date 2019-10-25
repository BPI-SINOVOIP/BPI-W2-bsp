/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

/**************************************************************
// Spec Version                  : 0.1.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/7/29 16:34:45
***************************************************************/


#ifndef _SB2_REG_H_INCLUDED_
#define _SB2_REG_H_INCLUDED_
#ifdef  _SB2_USE_STRUCT
typedef struct
{
unsigned int     reserved_0:31;
unsigned int     Semaphore:1;
}SB2_HD_SEM;

typedef struct
{
unsigned int     reserved_0:25;
unsigned int     swcivairq_en:1;
unsigned int     To_en1:1;
unsigned int     To_en:1;
unsigned int     acivairq_en:1;
unsigned int     reserved_1:1;
unsigned int     scivairq_en:1;
unsigned int     write_data:1;
}SB2_INV_INTEN;

typedef struct
{
unsigned int     reserved_0:27;
unsigned int     swciva_int:1;
unsigned int     Aciva_int:1;
unsigned int     reserved_1:1;
unsigned int     Sciva_int:1;
unsigned int     write_data:1;
}SB2_INV_INTSTAT;

typedef struct
{
unsigned int     Inv_adr:32;
}SB2_INV_ADDR;

typedef struct
{
unsigned int     reserved_0:25;
unsigned int     To_thr1:4;
unsigned int     To_thr:3;
}SB2_DEBUG_REG;

typedef struct
{
unsigned int     reserved_0:10;
unsigned int     Wr_hold_cyc:4;
unsigned int     reserved_1:3;
unsigned int     Wwr_cyc:5;
unsigned int     Wr_cyc:5;
unsigned int     Rd_cyc:5;
}SB2_FLASH_CTRL;

typedef struct
{
unsigned int     reserved_0:17;
unsigned int     write_en13:1;
unsigned int     mult_wr_en:1;
unsigned int     write_en11:1;
unsigned int     ac_in_order:1;
unsigned int     write_en9:1;
unsigned int     ac_bypass:1;
unsigned int     write_en7:1;
unsigned int     ac_merge:1;
unsigned int     reserved_1:3;
unsigned int     write_en2:1;
unsigned int     sc_in_order:1;
unsigned int     reserved_2:2;
}SB2_WRAPPER_CTRL;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     enable:1;
}SB2_SCPU_INT_CHECK;

typedef struct
{
unsigned int     Sync:32;
}SB2_SYNC;

typedef struct
{
unsigned int     reserved_0:27;
unsigned int     Dbg_mode:5;
}SB2_DBG;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     write_enable3:1;
unsigned int     sel1:6;
unsigned int     write_enable2:1;
unsigned int     sel0:6;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}SB2_SB2_DEBUG;

typedef struct
{
unsigned int     reserved_0:12;
unsigned int     pcie1_tostat:1;
unsigned int     sata_tostat:1;
unsigned int     pcie0_tostat:1;
unsigned int     etn_tostat:1;
unsigned int     reserved_1:12;
unsigned int     pcie1_tostat_auto:1;
unsigned int     sata_tostat_auto:1;
unsigned int     pcie0_tostat_auto:1;
unsigned int     etn_tostat_auto:1;
}SB2_RBUS1_TOSTAT;

typedef struct
{
unsigned int     reserved_0:30;
unsigned int     clk_gate_dis:1;
unsigned int     speed_up:1;
}SB2_LEXRA_CTRL;

typedef struct
{
unsigned int     reserved_0:20;
unsigned int     int_aswc:1;
unsigned int     int_swca:1;
unsigned int     reserved_1:6;
unsigned int     int_as:1;
unsigned int     reserved_2:1;
unsigned int     int_sa:1;
unsigned int     write_data:1;
}SB2_CPU_INT;

typedef struct
{
unsigned int     reserved_0:20;
unsigned int     int_aswc_en:1;
unsigned int     int_swca_en:1;
unsigned int     reserved_1:6;
unsigned int     int_as_en:1;
unsigned int     reserved_2:1;
unsigned int     int_sa_en:1;
unsigned int     write_data:1;
}SB2_CPU_INT_EN;

typedef struct
{
unsigned int     reserved_0:26;
unsigned int     pending:1;
unsigned int     reserved_1:2;
unsigned int     mask_id:3;
}SB2_DREQ_MASK;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     Chip_id:16;
}SB2_CHIP_ID;

typedef struct
{
unsigned int     Revise_id:16;
unsigned int     reserved_0:16;
}SB2_CHIP_INFO;

typedef struct
{
unsigned int     rom_remap:20;
unsigned int     reserved_0:12;
}SB2_ACPU_ROM_REMAP;

typedef struct
{
unsigned int     gnt_wr_delay:4;
unsigned int     acc_write_delay:4;
unsigned int     reserved_0:4;
unsigned int     did_com:4;
unsigned int     reserved_1:4;
unsigned int     read_comm:4;
unsigned int     reserved_2:4;
unsigned int     addcmd:4;
}SB2_ACPU_DELAY;

typedef struct
{
unsigned int     cbustx_en:1;
unsigned int     cbusiso_en:1;
unsigned int     isomis_en:1;
unsigned int     ae_en:1;
unsigned int     gpu_en:1;
unsigned int     mis_en:1;
unsigned int     rsa_en:1;
unsigned int     dcsb_en:1;
unsigned int     scw_en:1;
unsigned int     sbx_en:1;
unsigned int     sb2_en:1;
unsigned int     md_en:1;
unsigned int     jpeg_en:1;
unsigned int     nat_en:1;
unsigned int     usb3host_2_en:1;
unsigned int     usb3drd_en:1;
unsigned int     usb3host_en:1;
unsigned int     usb2_en:1;
unsigned int     usb_en:1;
unsigned int     dbp4_en:1;
unsigned int     dbp_en:1;
unsigned int     efs_en:1;
unsigned int     etn_en:1;
unsigned int     pcie_en:1;
unsigned int     cr_en:1;
unsigned int     sdio_en:1;
unsigned int     emmc_en:1;
unsigned int     nfs_en:1;
unsigned int     nf_en:1;
unsigned int     sata_en:1;
unsigned int     tp_en:1;
unsigned int     cp_en:1;
}SB2_RBUS_ICG1;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     ve3_en:1;
unsigned int     ve2_en:1;
unsigned int     ve1_en:1;
unsigned int     lvds_en:1;
unsigned int     edp_en:1;
unsigned int     cbusrx_en:1;
unsigned int     hdmir_en:1;
unsigned int     hdmit_en:1;
unsigned int     se_en:1;
unsigned int     mipi_en:1;
unsigned int     dptmx_en:1;
unsigned int     tve_en:1;
unsigned int     voregsram_en:1;
unsigned int     ao_en:1;
unsigned int     vo_en:1;
unsigned int     sys_en:1;
}SB2_RBUS_ICG2;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     tmp11:1;
unsigned int     tmp10:1;
unsigned int     tmp9:1;
unsigned int     tmp8:1;
unsigned int     tmp7:1;
unsigned int     tmp6:1;
unsigned int     tmp5:1;
unsigned int     tmp4:1;
unsigned int     tmp3:1;
unsigned int     tmp2:1;
unsigned int     tmp1:1;
unsigned int     tmp0:1;
unsigned int     mon_en:1;
unsigned int     dbus_en:1;
unsigned int     rbus_en:1;
unsigned int     spi_en:1;
}SB2_RBUS_ICG3;

typedef struct
{
unsigned int     reserved_0:30;
unsigned int     hif_rdata_swap:1;
unsigned int     hif_wdata_swap:1;
}SB2_HIF_CTRL1;

typedef struct
{
unsigned int     reserved_0:20;
unsigned int     write_en6:1;
unsigned int     acpu_rbus_go:1;
unsigned int     reserved_1:2;
unsigned int     write_en4:1;
unsigned int     scpu_rbus_go:1;
unsigned int     write_en3:1;
unsigned int     acpu_dbus_go:1;
unsigned int     reserved_2:4;
}SB2_PC_CTRL;

typedef struct
{
unsigned int     acpu_dbus_acc:32;
}SB2_ACPU_DACC;

typedef struct
{
unsigned int     reserved_0:8;
unsigned int     acpu_dreq_num:24;
}SB2_ACPU_DREQ_NUM;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     acpu_dreq_max:16;
}SB2_ACPU_DREQ_MAX;

typedef struct
{
unsigned int     reserved_0:6;
unsigned int     acpu_dreq_ack:26;
}SB2_ACPU_DREQ_ACK;

typedef struct
{
unsigned int     scpu_rbus_acc:32;
}SB2_SCPU_RACC;

typedef struct
{
unsigned int     scpu_rreq_max:8;
unsigned int     scpu_rreq_num:24;
}SB2_SCPU_RREQ_RLT;

typedef struct
{
unsigned int     acpu_rbus_acc:32;
}SB2_ACPU_RACC;

typedef struct
{
unsigned int     acpu_rreq_max:8;
unsigned int     acpu_rreq_num:24;
}SB2_ACPU_RREQ_RLT;

typedef struct
{
unsigned int     Dbg_start_addr:32;
}SB2_DBG_START;

typedef struct
{
unsigned int     Dbg_end_addr:32;
}SB2_DBG_END;

typedef struct
{
unsigned int     reserved_0:18;
unsigned int     write_en6:1;
unsigned int     Dbg_acpu_chk_en:1;
unsigned int     reserved_1:2;
unsigned int     write_en4:1;
unsigned int     Dbg_scpu_chk_en:1;
unsigned int     write_en3:1;
unsigned int     Dbg_wr_chk:2;
unsigned int     write_en2:1;
unsigned int     Dbg_id_chk:2;
unsigned int     write_en1:1;
unsigned int     Dbg_en:1;
}SB2_DBG_CTRL;

typedef struct
{
unsigned int     dbg_addr:32;
}SB2_DBG_ADDR;

typedef struct
{
unsigned int     reserved_0:26;
unsigned int     acpu_dbg_write:1;
unsigned int     acpu_dbg_dacc:1;
unsigned int     scpu_dbg_write:1;
unsigned int     scpu_dbg_dacc:1;
unsigned int     reserved_1:2;
}SB2_DBG_ADDR1;

typedef struct
{
unsigned int     reserved_0:19;
unsigned int     acpu_int:1;
unsigned int     reserved_1:1;
unsigned int     scpu_int:1;
unsigned int     acpu_int_en:1;
unsigned int     reserved_2:1;
unsigned int     scpu_int_en:1;
unsigned int     acpu_neg_int:1;
unsigned int     reserved_3:1;
unsigned int     scpu_neg_int:1;
unsigned int     acpu_neg_int_en:1;
unsigned int     reserved_4:1;
unsigned int     scpu_neg_int_en:1;
unsigned int     write_data:1;
}SB2_DBG_INT;

typedef struct
{
unsigned int     dbg_wdata:32;
}SB2_DBG_WDATA;

typedef struct
{
unsigned int     data:32;
}SB2_DUMMY;

typedef struct
{
unsigned int     data:32;
}SB2_SHADOW;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     Semaphore:1;
}SB2_HD_SEM_NEW;

typedef struct
{
unsigned int     reserved_0:29;
unsigned int     inva_wr_sec2_en:1;
unsigned int     reserved_1:1;
unsigned int     inva_wr_sec1_en:1;
}SB2_RBUS_INVA_ACC_CTRL;

typedef struct
{
unsigned int     reserved_0:10;
unsigned int     sec1_start:20;
unsigned int     reserved_1:2;
}SB2_RBUS_INVA_ACC_SEC1_START;

typedef struct
{
unsigned int     reserved_0:10;
unsigned int     sec1_end:20;
unsigned int     reserved_1:2;
}SB2_RBUS_INVA_ACC_SEC1_END;

typedef struct
{
unsigned int     reserved_0:10;
unsigned int     sec2_start:20;
unsigned int     reserved_1:2;
}SB2_RBUS_INVA_ACC_SEC2_START;

typedef struct
{
unsigned int     reserved_0:10;
unsigned int     sec2_end:20;
unsigned int     reserved_1:2;
}SB2_RBUS_INVA_ACC_SEC2_END;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     crc_cmp_latch_en:1;
}SB2_RBUS_CMP_CTRL;

typedef struct
{
unsigned int     crc_cmp_expect0:32;
}SB2_RBUS_CMP_DATA0;

typedef struct
{
unsigned int     crc_cmp_expect1:32;
}SB2_RBUS_CMP_DATA1;

typedef struct
{
unsigned int     reserved_0:30;
unsigned int     crc_cmp_result0:1;
unsigned int     crc_cmp_result1:1;
}SB2_RBUS_CMP_RESULT;

typedef struct
{
unsigned int     reserved_0:24;
unsigned int     sb2_bist_rstn:1;
unsigned int     sb2_bist_en:1;
unsigned int     sb2_rom_ls:1;
unsigned int     sb2_rom_rme:1;
unsigned int     sb2_rom_rm:4;
}SB2_BIST_CTRL;

typedef struct
{
unsigned int     reserved_0:15;
unsigned int     sb2_rom_bist_done:1;
unsigned int     reserved_1:16;
}SB2_BIST_STATUS;

typedef struct
{
unsigned int     sb2_misr_dataout_0:32;
}SB2_BIST_MISR_DATAOUT0;

typedef struct
{
unsigned int     sb2_misr_dataout_1:32;
}SB2_BIST_MISR_DATAOUT1;

typedef struct
{
unsigned int     reserved_0:21;
unsigned int     dual_mode:2;
unsigned int     fat_mode:1;
unsigned int     opc:8;
}SB2_SFC_OPCODE;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:11;
unsigned int     dataen:1;
unsigned int     adren:1;
unsigned int     dmycnt:3;
}SB2_SFC_CTL;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     reserved_1:7;
unsigned int     mode:1;
unsigned int     fdiv:8;
}SB2_SFC_SCK;

typedef struct
{
unsigned int     tdt:16;
unsigned int     Phcnt:8;
unsigned int     Plcnt:8;
}SB2_SFC_CE;

typedef struct
{
unsigned int     reserved_0:4;
unsigned int     write_en5:1;
unsigned int     rdy:1;
unsigned int     reserved_1:24;
unsigned int     write_en1:1;
unsigned int     wp_n:1;
}SB2_SFC_WP;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     pos_latch:1;
}SB2_SFC_POS_LATCH;

typedef struct
{
unsigned int     reserved_0:23;
unsigned int     wt_prog_done:1;
unsigned int     rdsr_op:8;
}SB2_SFC_WAIT_WR;

typedef struct
{
unsigned int     reserved_0:23;
unsigned int     wt_prog_en:1;
unsigned int     wr_en_op:8;
}SB2_SFC_EN_WR;

typedef struct
{
unsigned int     reserved_0:27;
unsigned int     sf_dclk_sel:1;
unsigned int     fifo_write_tap:3;
unsigned int     fast_read_en:1;
}SB2_SFC_FAST_RD;

typedef struct
{
unsigned int     delay_clk_tap:32;
}SB2_SFC_SCK_TAP;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     SFC_OPCODE_adr4byte_en:1;
}SB2_SFC_ADR_FOUR_BYTE_EN;

typedef struct
{
unsigned int     reserved_0:8;
unsigned int     tp1_clk:2;
unsigned int     tp1_valid:2;
unsigned int     tp1_sync:2;
unsigned int     tp1_data:2;
unsigned int     reserved_1:4;
unsigned int     tp0_clk:3;
unsigned int     tp0_valid:3;
unsigned int     tp0_sync:3;
unsigned int     tp0_data:3;
}SB2_MUXPAD2;

typedef struct
{
unsigned int     sensor_cko_0:2;
unsigned int     sensor_cko_1:2;
unsigned int     sensor_rst:2;
unsigned int     sensor_stb_0:2;
unsigned int     sensor_stb_1:2;
unsigned int     ejtag_scpu_loc:2;
unsigned int     hi_loc:2;
unsigned int     usb_id:2;
unsigned int     reserved_0:4;
unsigned int     i2c_scl_5:2;
unsigned int     i2c_sda_5:2;
unsigned int     i2c_scl_4:2;
unsigned int     i2c_sda_4:2;
unsigned int     reserved_1:4;
}SB2_MUXPAD3;

typedef struct
{
unsigned int     reserved_0:8;
unsigned int     gpio_9:2;
unsigned int     gpio_8:2;
unsigned int     gpio_7:2;
unsigned int     gpio_6:2;
unsigned int     gpio_5:2;
unsigned int     gpio_4:2;
unsigned int     gpio_3:3;
unsigned int     gpio_2:3;
unsigned int     gpio_1:3;
unsigned int     gpio_0:3;
}SB2_MUXPAD4;

typedef struct
{
unsigned int     reserved_0:23;
unsigned int     tp1_loc:1;
unsigned int     tp0_loc:1;
unsigned int     debug_p2s_enable:1;
unsigned int     ur1_loc:2;
unsigned int     ao_loc:2;
unsigned int     arm_trace_dbg_en:1;
unsigned int     sf_en:1;
}SB2_MUXPAD5;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     tp0_data_smt:1;
unsigned int     tp0_data_e2:1;
unsigned int     tp0_data_pud_en:1;
unsigned int     tp0_data_pud_sel:1;
unsigned int     tp0_valid_smt:1;
unsigned int     tp0_valid_e2:1;
unsigned int     tp0_valid_pud_en:1;
unsigned int     tp0_valid_pud_sel:1;
unsigned int     tp0_sync_smt:1;
unsigned int     tp0_sync_e2:1;
unsigned int     tp0_sync_pud_en:1;
unsigned int     tp0_sync_pud_sel:1;
unsigned int     tp0_clk_smt:1;
unsigned int     tp0_clk_e2:1;
unsigned int     tp0_clk_pud_en:1;
unsigned int     tp0_clk_pud_sel:1;
}SB2_PFUNC_TP0;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     tp1_data_smt:1;
unsigned int     tp1_data_e2:1;
unsigned int     tp1_data_pud_en:1;
unsigned int     tp1_data_pud_sel:1;
unsigned int     tp1_valid_smt:1;
unsigned int     tp1_valid_e2:1;
unsigned int     tp1_valid_pud_en:1;
unsigned int     tp1_valid_pud_sel:1;
unsigned int     tp1_sync_smt:1;
unsigned int     tp1_sync_e2:1;
unsigned int     tp1_sync_pud_en:1;
unsigned int     tp1_sync_pud_sel:1;
unsigned int     tp1_clk_smt:1;
unsigned int     tp1_clk_e2:1;
unsigned int     tp1_clk_pud_en:1;
unsigned int     tp1_clk_pud_sel:1;
}SB2_PFUNC_TP1;

typedef struct
{
unsigned int     reserved_0:8;
unsigned int     i2c_scl_5_smt:1;
unsigned int     i2c_scl_5_e2:1;
unsigned int     i2c_scl_5_pud_en:1;
unsigned int     i2c_scl_5_pud_sel:1;
unsigned int     i2c_sda_5_smt:1;
unsigned int     i2c_sda_5_e2:1;
unsigned int     i2c_sda_5_pud_en:1;
unsigned int     i2c_sda_5_pud_sel:1;
unsigned int     i2c_scl_4_smt:1;
unsigned int     i2c_scl_4_e2:1;
unsigned int     i2c_scl_4_pud_en:1;
unsigned int     i2c_scl_4_pud_sel:1;
unsigned int     i2c_sda_4_smt:1;
unsigned int     i2c_sda_4_e2:1;
unsigned int     i2c_sda_4_pud_en:1;
unsigned int     i2c_sda_4_pud_sel:1;
unsigned int     reserved_1:8;
}SB2_PFUNC_MISC0;

typedef struct
{
unsigned int     gpio_7_smt:1;
unsigned int     gpio_7_e2:1;
unsigned int     gpio_7_pud_en:1;
unsigned int     gpio_7_pud_sel:1;
unsigned int     gpio_6_smt:1;
unsigned int     gpio_6_e2:1;
unsigned int     gpio_6_pud_en:1;
unsigned int     gpio_6_pud_sel:1;
unsigned int     gpio_5_smt:1;
unsigned int     gpio_5_e2:1;
unsigned int     gpio_5_pud_en:1;
unsigned int     gpio_5_pud_sel:1;
unsigned int     gpio_4_smt:1;
unsigned int     gpio_4_e2:1;
unsigned int     gpio_4_pud_en:1;
unsigned int     gpio_4_pud_sel:1;
unsigned int     gpio_3_smt:1;
unsigned int     gpio_3_e2:1;
unsigned int     gpio_3_pud_en:1;
unsigned int     gpio_3_pud_sel:1;
unsigned int     gpio_2_smt:1;
unsigned int     gpio_2_e2:1;
unsigned int     gpio_2_pud_en:1;
unsigned int     gpio_2_pud_sel:1;
unsigned int     gpio_1_smt:1;
unsigned int     gpio_1_e2:1;
unsigned int     gpio_1_pud_en:1;
unsigned int     gpio_1_pud_sel:1;
unsigned int     gpio_0_smt:1;
unsigned int     gpio_0_e2:1;
unsigned int     gpio_0_pud_en:1;
unsigned int     gpio_0_pud_sel:1;
}SB2_PFUNC_MISC1;

typedef struct
{
unsigned int     sensor_cko1_smt:1;
unsigned int     sensor_cko1_e2:1;
unsigned int     sensor_cko1_pud_en:1;
unsigned int     sensor_cko1_pud_sel:1;
unsigned int     sensor_cko0_smt:1;
unsigned int     sensor_cko0_e2:1;
unsigned int     sensor_cko0_pud_en:1;
unsigned int     sensor_cko0_pud_sel:1;
unsigned int     sensor_rst_smt:1;
unsigned int     sensor_rst_e2:1;
unsigned int     sensor_rst_pud_en:1;
unsigned int     sensor_rst_pud_sel:1;
unsigned int     sensor_stb1_smt:1;
unsigned int     sensor_stb1_e2:1;
unsigned int     sensor_stb1_pud_en:1;
unsigned int     sensor_stb1_pud_sel:1;
unsigned int     sensor_stb0_smt:1;
unsigned int     sensor_stb0_e2:1;
unsigned int     sensor_stb0_pud_en:1;
unsigned int     sensor_stb0_pud_sel:1;
unsigned int     usb_id_smt:1;
unsigned int     usb_id_e2:1;
unsigned int     usb_id_pud_en:1;
unsigned int     usb_id_pud_sel:1;
unsigned int     gpio_9_smt:1;
unsigned int     gpio_9_e2:1;
unsigned int     gpio_9_pud_en:1;
unsigned int     gpio_9_pud_sel:1;
unsigned int     gpio_8_smt:1;
unsigned int     gpio_8_e2:1;
unsigned int     gpio_8_pud_en:1;
unsigned int     gpio_8_pud_sel:1;
}SB2_PFUNC_MISC2;

typedef struct
{
unsigned int     reserved_0:5;
unsigned int     boption4_smt:1;
unsigned int     boption4_pud_en:1;
unsigned int     boption4_pud_sel:1;
unsigned int     boption3_smt:1;
unsigned int     boption3_pud_en:1;
unsigned int     boption3_pud_sel:1;
unsigned int     boption1_smt:1;
unsigned int     boption1_pud_en:1;
unsigned int     boption1_pud_sel:1;
unsigned int     boption0_smt:1;
unsigned int     boption0_pud_en:1;
unsigned int     boption0_pud_sel:1;
unsigned int     boption9_smt:1;
unsigned int     boption9_pud_en:1;
unsigned int     boption9_pud_sel:1;
unsigned int     boption8_smt:1;
unsigned int     boption8_pud_en:1;
unsigned int     boption8_pud_sel:1;
unsigned int     boption7_smt:1;
unsigned int     boption7_pud_en:1;
unsigned int     boption7_pud_sel:1;
unsigned int     boption6_smt:1;
unsigned int     boption6_pud_en:1;
unsigned int     boption6_pud_sel:1;
unsigned int     boption5_smt:1;
unsigned int     boption5_pud_en:1;
unsigned int     boption5_pud_sel:1;
}SB2_PFUNC_MISC3;

typedef struct
{
unsigned int     main1_dbg_en:1;
unsigned int     reserved_0:3;
unsigned int     main1_dbg_sel:4;
unsigned int     reserved_1:9;
unsigned int     dbg_en:1;
unsigned int     dbg_loc:2;
unsigned int     dbg_sel0:6;
unsigned int     dbg_sel1:6;
}SB2_DEBUG;

typedef struct
{
unsigned int     reserved_0:3;
unsigned int     mbist_gpu_chip_top_st:1;
unsigned int     mbist_jpeg_st:1;
unsigned int     mbist_ve1_st:1;
unsigned int     mbist_ve2_st:1;
unsigned int     mbist_ve3_st:1;
unsigned int     mbist_rsa_st:1;
unsigned int     mbist_sata_st:1;
unsigned int     mbist_pcie0_st:1;
unsigned int     mbist_pcie1_st:1;
unsigned int     mbist_nat_st:1;
unsigned int     mbist_mipi_st:1;
unsigned int     mbist_usb_st:1;
unsigned int     mbist_se_st:1;
unsigned int     mbist_md_st:1;
unsigned int     mbist_nf_st:1;
unsigned int     mbist_cr_st:1;
unsigned int     mbist_etn_st:1;
unsigned int     mbist_dp_st:1;
unsigned int     mbist_ae_st:1;
unsigned int     mbist_acpu_st:1;
unsigned int     mbist_gpu_st:1;
unsigned int     mbist_tp_st:1;
unsigned int     mbist_aio_st:1;
unsigned int     mbist_pif_st:1;
unsigned int     mbist_hdmi_st:1;
unsigned int     mbist_vo_st:1;
unsigned int     mbist_dc_phy_st:1;
unsigned int     mbist_dc_sys_st:1;
unsigned int     mbist_cp_st:1;
}SB2_MBIST;

typedef struct
{
unsigned int     reserved_0:26;
unsigned int     rgmii0_txd_3_sr:1;
unsigned int     rgmii0_txd_2_sr:1;
unsigned int     rgmii0_txd_1_sr:1;
unsigned int     rgmii0_txd_0_sr:1;
unsigned int     rgmii0_tx_ctl_sr:1;
unsigned int     rgmii0_txc_sr:1;
}SB2_PFUNC_RG0;

typedef struct
{
unsigned int     rgmii0_rx_ctl_smt:1;
unsigned int     rgmii0_rx_ctl_e2:1;
unsigned int     rgmii0_rx_ctl_pud_en:1;
unsigned int     rgmii0_rx_ctl_pud_sel:1;
unsigned int     rgmii0_rxc_smt:1;
unsigned int     rgmii0_rxc_e2:1;
unsigned int     rgmii0_rxc_pud_en:1;
unsigned int     rgmii0_rxc_pud_sel:1;
unsigned int     rgmii0_txd_3_smt:1;
unsigned int     rgmii0_txd_3_e2:1;
unsigned int     rgmii0_txd_3_pud_en:1;
unsigned int     rgmii0_txd_3_pud_sel:1;
unsigned int     rgmii0_txd_2_smt:1;
unsigned int     rgmii0_txd_2_e2:1;
unsigned int     rgmii0_txd_2_pud_en:1;
unsigned int     rgmii0_txd_2_pud_sel:1;
unsigned int     rgmii0_txd_1_smt:1;
unsigned int     rgmii0_txd_1_e2:1;
unsigned int     rgmii0_txd_1_pud_en:1;
unsigned int     rgmii0_txd_1_pud_sel:1;
unsigned int     rgmii0_txd_0_smt:1;
unsigned int     rgmii0_txd_0_e2:1;
unsigned int     rgmii0_txd_0_pud_en:1;
unsigned int     rgmii0_txd_0_pud_sel:1;
unsigned int     rgmii0_tx_ctl_smt:1;
unsigned int     rgmii0_tx_ctl_e2:1;
unsigned int     rgmii0_tx_ctl_pud_en:1;
unsigned int     rgmii0_tx_ctl_pud_sel:1;
unsigned int     rgmii0_txc_smt:1;
unsigned int     rgmii0_txc_e2:1;
unsigned int     rgmii0_txc_pud_en:1;
unsigned int     rgmii0_txc_pud_sel:1;
}SB2_PFUNC_RG1;

typedef struct
{
unsigned int     rgmii0_bias_mode2:1;
unsigned int     rgmii0_bias_mode:1;
unsigned int     rgmii0_bias_dn:3;
unsigned int     rgmii0_bias_dp:3;
unsigned int     rgmii0_mdc_smt:1;
unsigned int     rgmii0_mdc_e2:1;
unsigned int     rgmii0_mdc_pud_en:1;
unsigned int     rgmii0_mdc_pud_sel:1;
unsigned int     rgmii0_mdio_smt:1;
unsigned int     rgmii0_mdio_e2:1;
unsigned int     rgmii0_mdio_pud_en:1;
unsigned int     rgmii0_mdio_pud_sel:1;
unsigned int     rgmii0_rxd_3_smt:1;
unsigned int     rgmii0_rxd_3_e2:1;
unsigned int     rgmii0_rxd_3_pud_en:1;
unsigned int     rgmii0_rxd_3_pud_sel:1;
unsigned int     rgmii0_rxd_2_smt:1;
unsigned int     rgmii0_rxd_2_e2:1;
unsigned int     rgmii0_rxd_2_pud_en:1;
unsigned int     rgmii0_rxd_2_pud_sel:1;
unsigned int     rgmii0_rxd_1_smt:1;
unsigned int     rgmii0_rxd_1_e2:1;
unsigned int     rgmii0_rxd_1_pud_en:1;
unsigned int     rgmii0_rxd_1_pud_sel:1;
unsigned int     rgmii0_rxd_0_smt:1;
unsigned int     rgmii0_rxd_0_e2:1;
unsigned int     rgmii0_rxd_0_pud_en:1;
unsigned int     rgmii0_rxd_0_pud_sel:1;
}SB2_PFUNC_RG2;

typedef struct
{
unsigned int     reserved_0:4;
unsigned int     rgmii0_mdc:2;
unsigned int     rgmii0_mdio:2;
unsigned int     rgmii0_rxd_3:2;
unsigned int     rgmii0_rxd_2:2;
unsigned int     rgmii0_rxd_1:2;
unsigned int     rgmii0_rxd_0:2;
unsigned int     rgmii0_rx_ctl:2;
unsigned int     rgmii0_rxc:2;
unsigned int     rgmii0_txd_3:2;
unsigned int     rgmii0_txd_2:2;
unsigned int     rgmii0_txd_1:2;
unsigned int     rgmii0_txd_0:2;
unsigned int     rgmii0_tx_ctl:2;
unsigned int     rgmii0_txc:2;
}SB2_MUXPAD_RG0;

typedef struct
{
unsigned int     reserved_0:26;
unsigned int     rgmii1_txd_3_sr:1;
unsigned int     rgmii1_txd_2_sr:1;
unsigned int     rgmii1_txd_1_sr:1;
unsigned int     rgmii1_txd_0_sr:1;
unsigned int     rgmii1_tx_ctl_sr:1;
unsigned int     rgmii1_txc_sr:1;
}SB2_PFUNC_RG3;

typedef struct
{
unsigned int     rgmii1_rx_ctl_smt:1;
unsigned int     rgmii1_rx_ctl_e2:1;
unsigned int     rgmii1_rx_ctl_pud_en:1;
unsigned int     rgmii1_rx_ctl_pud_sel:1;
unsigned int     rgmii1_rxc_smt:1;
unsigned int     rgmii1_rxc_e2:1;
unsigned int     rgmii1_rxc_pud_en:1;
unsigned int     rgmii1_rxc_pud_sel:1;
unsigned int     rgmii1_txd_3_smt:1;
unsigned int     rgmii1_txd_3_e2:1;
unsigned int     rgmii1_txd_3_pud_en:1;
unsigned int     rgmii1_txd_3_pud_sel:1;
unsigned int     rgmii1_txd_2_smt:1;
unsigned int     rgmii1_txd_2_e2:1;
unsigned int     rgmii1_txd_2_pud_en:1;
unsigned int     rgmii1_txd_2_pud_sel:1;
unsigned int     rgmii1_txd_1_smt:1;
unsigned int     rgmii1_txd_1_e2:1;
unsigned int     rgmii1_txd_1_pud_en:1;
unsigned int     rgmii1_txd_1_pud_sel:1;
unsigned int     rgmii1_txd_0_smt:1;
unsigned int     rgmii1_txd_0_e2:1;
unsigned int     rgmii1_txd_0_pud_en:1;
unsigned int     rgmii1_txd_0_pud_sel:1;
unsigned int     rgmii1_tx_ctl_smt:1;
unsigned int     rgmii1_tx_ctl_e2:1;
unsigned int     rgmii1_tx_ctl_pud_en:1;
unsigned int     rgmii1_tx_ctl_pud_sel:1;
unsigned int     rgmii1_txc_smt:1;
unsigned int     rgmii1_txc_e2:1;
unsigned int     rgmii1_txc_pud_en:1;
unsigned int     rgmii1_txc_pud_sel:1;
}SB2_PFUNC_RG4;

typedef struct
{
unsigned int     rgmii1_bias_mode2:1;
unsigned int     rgmii1_bias_mode:1;
unsigned int     rgmii1_bias_dn:3;
unsigned int     rgmii1_bias_dp:3;
unsigned int     reserved_0:8;
unsigned int     rgmii1_rxd_3_smt:1;
unsigned int     rgmii1_rxd_3_e2:1;
unsigned int     rgmii1_rxd_3_pud_en:1;
unsigned int     rgmii1_rxd_3_pud_sel:1;
unsigned int     rgmii1_rxd_2_smt:1;
unsigned int     rgmii1_rxd_2_e2:1;
unsigned int     rgmii1_rxd_2_pud_en:1;
unsigned int     rgmii1_rxd_2_pud_sel:1;
unsigned int     rgmii1_rxd_1_smt:1;
unsigned int     rgmii1_rxd_1_e2:1;
unsigned int     rgmii1_rxd_1_pud_en:1;
unsigned int     rgmii1_rxd_1_pud_sel:1;
unsigned int     rgmii1_rxd_0_smt:1;
unsigned int     rgmii1_rxd_0_e2:1;
unsigned int     rgmii1_rxd_0_pud_en:1;
unsigned int     rgmii1_rxd_0_pud_sel:1;
}SB2_PFUNC_RG5;

typedef struct
{
unsigned int     reserved_0:4;
unsigned int     rgmii1_mdc:2;
unsigned int     rgmii1_mdio:2;
unsigned int     rgmii1_rxd_3:2;
unsigned int     rgmii1_rxd_2:2;
unsigned int     rgmii1_rxd_1:2;
unsigned int     rgmii1_rxd_0:2;
unsigned int     rgmii1_rx_ctl:2;
unsigned int     rgmii1_rxc:2;
unsigned int     rgmii1_txd_3:2;
unsigned int     rgmii1_txd_2:2;
unsigned int     rgmii1_txd_1:2;
unsigned int     rgmii1_txd_0:2;
unsigned int     rgmii1_tx_ctl:2;
unsigned int     rgmii1_txc:2;
}SB2_MUXPAD_RG1;

typedef struct
{
unsigned int     reserved_0:23;
unsigned int     sata_sgmii_sel:1;
unsigned int     isolate_sata_sgmii_1:1;
unsigned int     isolate_sata_sgmii_0:1;
unsigned int     sata_rx50_link_1:1;
unsigned int     sata_rx50_link_0:1;
unsigned int     sata_mbias_en_1:1;
unsigned int     sata_mbias_en_0:1;
unsigned int     sata_bg_en_1:1;
unsigned int     sata_bg_en_0:1;
}SB2_SATA_PHY_CTRL;

typedef struct
{
unsigned int     reserved_0:14;
unsigned int     lfsr_mode:1;
unsigned int     lfsr_bypass_1:1;
unsigned int     dbg1_sel:4;
unsigned int     dbg0_sel:4;
unsigned int     reserved_1:2;
unsigned int     corrector_imode:1;
unsigned int     reserved_2:1;
unsigned int     rng_cali_srst:1;
unsigned int     corrector_bypass:1;
unsigned int     clk_hf_sel:1;
unsigned int     rng_srst:1;
}SB2_RNG_CTRL;

typedef struct
{
unsigned int     reserved_0:16;
unsigned int     rosc_d:4;
unsigned int     rosc_res:2;
unsigned int     rosc_div:2;
unsigned int     rosc_gain:2;
unsigned int     rosc_fs:2;
unsigned int     reserved_1:2;
unsigned int     rosc_test:1;
unsigned int     rosc_pow:1;
}SB2_RNG_ANALOG;

typedef struct
{
unsigned int     prd_ub:16;
unsigned int     prd_lb:16;
}SB2_RNG_CALI_CHK;

typedef struct
{
unsigned int     shot_num:12;
unsigned int     cyc_num:3;
unsigned int     wait_num:5;
unsigned int     reserved_0:3;
unsigned int     trig_num:5;
unsigned int     lock:1;
unsigned int     shot_mode:1;
unsigned int     pol:1;
unsigned int     hw_en:1;
}SB2_RNG_CALI_CTRL;

typedef struct
{
unsigned int     reserved_0:8;
unsigned int     hw_d:4;
unsigned int     reserved_1:2;
unsigned int     rosc_lock:1;
unsigned int     cnt_ovflw:1;
unsigned int     cnt:16;
}SB2_RNG_RETURN;

typedef struct
{
unsigned int     prd_ub:16;
unsigned int     prd_lb:16;
}SB2_RNG_LOCK_CHK;

typedef struct
{
unsigned int     reserved_0:12;
unsigned int     exit_num:4;
unsigned int     reserved_1:12;
unsigned int     enter_num:4;
}SB2_RNG_LOCK_CTRL;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     out_ready:1;
}SB2_RNG_RETURN3;

typedef struct
{
unsigned int     valid_bit_num:32;
}SB2_RNG_RETURN4;

typedef struct
{
unsigned int     drop_num:32;
}SB2_RNG_RETURN5;

typedef struct
{
unsigned int     random_out:32;
}SB2_RNG_RESULTR;

typedef struct
{
unsigned int     lfsr_poly_lsb:32;
}SB2_RNG_LFSR_POLY_LSB;

typedef struct
{
unsigned int     lfsr_poly_msb:32;
}SB2_RNG_LFSR_POLY_MSB;

typedef struct
{
unsigned int     dummy_msb:16;
unsigned int     dummy_lsb:16;
}SB2_RNG_DUMMY;

typedef struct
{
unsigned int     reserved_0:31;
unsigned int     gating_en:1;
}SB2_RNG_POWER;

#endif

#define SB2_HD_SEM                                                                   0x9801A000
#define SB2_HD_SEM_reg_addr                                                          "0xD801A000"
#define SB2_HD_SEM_reg                                                               0xD801A000
#define set_SB2_HD_SEM_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_reg)=data)
#define get_SB2_HD_SEM_reg   (*((volatile unsigned int*) SB2_HD_SEM_reg))
#define SB2_HD_SEM_inst_adr                                                          "0x0000"
#define SB2_HD_SEM_inst                                                              0x0000
#define SB2_HD_SEM_Semaphore_shift                                                   (0)
#define SB2_HD_SEM_Semaphore_mask                                                    (0x00000001)
#define SB2_HD_SEM_Semaphore(data)                                                   (0x00000001&((data)<<0))
#define SB2_HD_SEM_Semaphore_src(data)                                               ((0x00000001&(data))>>0)
#define SB2_HD_SEM_get_Semaphore(data)                                               ((0x00000001&(data))>>0)


#define SB2_INV_INTEN                                                                0x9801A004
#define SB2_INV_INTEN_reg_addr                                                       "0xD801A004"
#define SB2_INV_INTEN_reg                                                            0xD801A004
#define set_SB2_INV_INTEN_reg(data)   (*((volatile unsigned int*) SB2_INV_INTEN_reg)=data)
#define get_SB2_INV_INTEN_reg   (*((volatile unsigned int*) SB2_INV_INTEN_reg))
#define SB2_INV_INTEN_inst_adr                                                       "0x0001"
#define SB2_INV_INTEN_inst                                                           0x0001
#define SB2_INV_INTEN_swcivairq_en_shift                                             (6)
#define SB2_INV_INTEN_swcivairq_en_mask                                              (0x00000040)
#define SB2_INV_INTEN_swcivairq_en(data)                                             (0x00000040&((data)<<6))
#define SB2_INV_INTEN_swcivairq_en_src(data)                                         ((0x00000040&(data))>>6)
#define SB2_INV_INTEN_get_swcivairq_en(data)                                         ((0x00000040&(data))>>6)
#define SB2_INV_INTEN_To_en1_shift                                                   (5)
#define SB2_INV_INTEN_To_en1_mask                                                    (0x00000020)
#define SB2_INV_INTEN_To_en1(data)                                                   (0x00000020&((data)<<5))
#define SB2_INV_INTEN_To_en1_src(data)                                               ((0x00000020&(data))>>5)
#define SB2_INV_INTEN_get_To_en1(data)                                               ((0x00000020&(data))>>5)
#define SB2_INV_INTEN_To_en_shift                                                    (4)
#define SB2_INV_INTEN_To_en_mask                                                     (0x00000010)
#define SB2_INV_INTEN_To_en(data)                                                    (0x00000010&((data)<<4))
#define SB2_INV_INTEN_To_en_src(data)                                                ((0x00000010&(data))>>4)
#define SB2_INV_INTEN_get_To_en(data)                                                ((0x00000010&(data))>>4)
#define SB2_INV_INTEN_acivairq_en_shift                                              (3)
#define SB2_INV_INTEN_acivairq_en_mask                                               (0x00000008)
#define SB2_INV_INTEN_acivairq_en(data)                                              (0x00000008&((data)<<3))
#define SB2_INV_INTEN_acivairq_en_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_INV_INTEN_get_acivairq_en(data)                                          ((0x00000008&(data))>>3)
#define SB2_INV_INTEN_scivairq_en_shift                                              (1)
#define SB2_INV_INTEN_scivairq_en_mask                                               (0x00000002)
#define SB2_INV_INTEN_scivairq_en(data)                                              (0x00000002&((data)<<1))
#define SB2_INV_INTEN_scivairq_en_src(data)                                          ((0x00000002&(data))>>1)
#define SB2_INV_INTEN_get_scivairq_en(data)                                          ((0x00000002&(data))>>1)
#define SB2_INV_INTEN_write_data_shift                                               (0)
#define SB2_INV_INTEN_write_data_mask                                                (0x00000001)
#define SB2_INV_INTEN_write_data(data)                                               (0x00000001&((data)<<0))
#define SB2_INV_INTEN_write_data_src(data)                                           ((0x00000001&(data))>>0)
#define SB2_INV_INTEN_get_write_data(data)                                           ((0x00000001&(data))>>0)


#define SB2_INV_INTSTAT                                                              0x9801A008
#define SB2_INV_INTSTAT_reg_addr                                                     "0xD801A008"
#define SB2_INV_INTSTAT_reg                                                          0xD801A008
#define set_SB2_INV_INTSTAT_reg(data)   (*((volatile unsigned int*) SB2_INV_INTSTAT_reg)=data)
#define get_SB2_INV_INTSTAT_reg   (*((volatile unsigned int*) SB2_INV_INTSTAT_reg))
#define SB2_INV_INTSTAT_inst_adr                                                     "0x0002"
#define SB2_INV_INTSTAT_inst                                                         0x0002
#define SB2_INV_INTSTAT_swciva_int_shift                                             (4)
#define SB2_INV_INTSTAT_swciva_int_mask                                              (0x00000010)
#define SB2_INV_INTSTAT_swciva_int(data)                                             (0x00000010&((data)<<4))
#define SB2_INV_INTSTAT_swciva_int_src(data)                                         ((0x00000010&(data))>>4)
#define SB2_INV_INTSTAT_get_swciva_int(data)                                         ((0x00000010&(data))>>4)
#define SB2_INV_INTSTAT_Aciva_int_shift                                              (3)
#define SB2_INV_INTSTAT_Aciva_int_mask                                               (0x00000008)
#define SB2_INV_INTSTAT_Aciva_int(data)                                              (0x00000008&((data)<<3))
#define SB2_INV_INTSTAT_Aciva_int_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_INV_INTSTAT_get_Aciva_int(data)                                          ((0x00000008&(data))>>3)
#define SB2_INV_INTSTAT_Sciva_int_shift                                              (1)
#define SB2_INV_INTSTAT_Sciva_int_mask                                               (0x00000002)
#define SB2_INV_INTSTAT_Sciva_int(data)                                              (0x00000002&((data)<<1))
#define SB2_INV_INTSTAT_Sciva_int_src(data)                                          ((0x00000002&(data))>>1)
#define SB2_INV_INTSTAT_get_Sciva_int(data)                                          ((0x00000002&(data))>>1)
#define SB2_INV_INTSTAT_write_data_shift                                             (0)
#define SB2_INV_INTSTAT_write_data_mask                                              (0x00000001)
#define SB2_INV_INTSTAT_write_data(data)                                             (0x00000001&((data)<<0))
#define SB2_INV_INTSTAT_write_data_src(data)                                         ((0x00000001&(data))>>0)
#define SB2_INV_INTSTAT_get_write_data(data)                                         ((0x00000001&(data))>>0)


#define SB2_INV_ADDR                                                                 0x9801A00C
#define SB2_INV_ADDR_reg_addr                                                        "0xD801A00C"
#define SB2_INV_ADDR_reg                                                             0xD801A00C
#define set_SB2_INV_ADDR_reg(data)   (*((volatile unsigned int*) SB2_INV_ADDR_reg)=data)
#define get_SB2_INV_ADDR_reg   (*((volatile unsigned int*) SB2_INV_ADDR_reg))
#define SB2_INV_ADDR_inst_adr                                                        "0x0003"
#define SB2_INV_ADDR_inst                                                            0x0003
#define SB2_INV_ADDR_Inv_adr_shift                                                   (0)
#define SB2_INV_ADDR_Inv_adr_mask                                                    (0xFFFFFFFF)
#define SB2_INV_ADDR_Inv_adr(data)                                                   (0xFFFFFFFF&((data)<<0))
#define SB2_INV_ADDR_Inv_adr_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define SB2_INV_ADDR_get_Inv_adr(data)                                               ((0xFFFFFFFF&(data))>>0)


#define SB2_DEBUG_REG                                                                0x9801A010
#define SB2_DEBUG_REG_reg_addr                                                       "0xD801A010"
#define SB2_DEBUG_REG_reg                                                            0xD801A010
#define set_SB2_DEBUG_REG_reg(data)   (*((volatile unsigned int*) SB2_DEBUG_REG_reg)=data)
#define get_SB2_DEBUG_REG_reg   (*((volatile unsigned int*) SB2_DEBUG_REG_reg))
#define SB2_DEBUG_REG_inst_adr                                                       "0x0004"
#define SB2_DEBUG_REG_inst                                                           0x0004
#define SB2_DEBUG_REG_To_thr1_shift                                                  (3)
#define SB2_DEBUG_REG_To_thr1_mask                                                   (0x00000078)
#define SB2_DEBUG_REG_To_thr1(data)                                                  (0x00000078&((data)<<3))
#define SB2_DEBUG_REG_To_thr1_src(data)                                              ((0x00000078&(data))>>3)
#define SB2_DEBUG_REG_get_To_thr1(data)                                              ((0x00000078&(data))>>3)
#define SB2_DEBUG_REG_To_thr_shift                                                   (0)
#define SB2_DEBUG_REG_To_thr_mask                                                    (0x00000007)
#define SB2_DEBUG_REG_To_thr(data)                                                   (0x00000007&((data)<<0))
#define SB2_DEBUG_REG_To_thr_src(data)                                               ((0x00000007&(data))>>0)
#define SB2_DEBUG_REG_get_To_thr(data)                                               ((0x00000007&(data))>>0)


#define SB2_FLASH_CTRL                                                               0x9801A014
#define SB2_FLASH_CTRL_reg_addr                                                      "0xD801A014"
#define SB2_FLASH_CTRL_reg                                                           0xD801A014
#define set_SB2_FLASH_CTRL_reg(data)   (*((volatile unsigned int*) SB2_FLASH_CTRL_reg)=data)
#define get_SB2_FLASH_CTRL_reg   (*((volatile unsigned int*) SB2_FLASH_CTRL_reg))
#define SB2_FLASH_CTRL_inst_adr                                                      "0x0005"
#define SB2_FLASH_CTRL_inst                                                          0x0005
#define SB2_FLASH_CTRL_Wr_hold_cyc_shift                                             (18)
#define SB2_FLASH_CTRL_Wr_hold_cyc_mask                                              (0x003C0000)
#define SB2_FLASH_CTRL_Wr_hold_cyc(data)                                             (0x003C0000&((data)<<18))
#define SB2_FLASH_CTRL_Wr_hold_cyc_src(data)                                         ((0x003C0000&(data))>>18)
#define SB2_FLASH_CTRL_get_Wr_hold_cyc(data)                                         ((0x003C0000&(data))>>18)
#define SB2_FLASH_CTRL_Wwr_cyc_shift                                                 (10)
#define SB2_FLASH_CTRL_Wwr_cyc_mask                                                  (0x00007C00)
#define SB2_FLASH_CTRL_Wwr_cyc(data)                                                 (0x00007C00&((data)<<10))
#define SB2_FLASH_CTRL_Wwr_cyc_src(data)                                             ((0x00007C00&(data))>>10)
#define SB2_FLASH_CTRL_get_Wwr_cyc(data)                                             ((0x00007C00&(data))>>10)
#define SB2_FLASH_CTRL_Wr_cyc_shift                                                  (5)
#define SB2_FLASH_CTRL_Wr_cyc_mask                                                   (0x000003E0)
#define SB2_FLASH_CTRL_Wr_cyc(data)                                                  (0x000003E0&((data)<<5))
#define SB2_FLASH_CTRL_Wr_cyc_src(data)                                              ((0x000003E0&(data))>>5)
#define SB2_FLASH_CTRL_get_Wr_cyc(data)                                              ((0x000003E0&(data))>>5)
#define SB2_FLASH_CTRL_Rd_cyc_shift                                                  (0)
#define SB2_FLASH_CTRL_Rd_cyc_mask                                                   (0x0000001F)
#define SB2_FLASH_CTRL_Rd_cyc(data)                                                  (0x0000001F&((data)<<0))
#define SB2_FLASH_CTRL_Rd_cyc_src(data)                                              ((0x0000001F&(data))>>0)
#define SB2_FLASH_CTRL_get_Rd_cyc(data)                                              ((0x0000001F&(data))>>0)


#define SB2_WRAPPER_CTRL                                                             0x9801A018
#define SB2_WRAPPER_CTRL_reg_addr                                                    "0xD801A018"
#define SB2_WRAPPER_CTRL_reg                                                         0xD801A018
#define set_SB2_WRAPPER_CTRL_reg(data)   (*((volatile unsigned int*) SB2_WRAPPER_CTRL_reg)=data)
#define get_SB2_WRAPPER_CTRL_reg   (*((volatile unsigned int*) SB2_WRAPPER_CTRL_reg))
#define SB2_WRAPPER_CTRL_inst_adr                                                    "0x0006"
#define SB2_WRAPPER_CTRL_inst                                                        0x0006
#define SB2_WRAPPER_CTRL_write_en13_shift                                            (14)
#define SB2_WRAPPER_CTRL_write_en13_mask                                             (0x00004000)
#define SB2_WRAPPER_CTRL_write_en13(data)                                            (0x00004000&((data)<<14))
#define SB2_WRAPPER_CTRL_write_en13_src(data)                                        ((0x00004000&(data))>>14)
#define SB2_WRAPPER_CTRL_get_write_en13(data)                                        ((0x00004000&(data))>>14)
#define SB2_WRAPPER_CTRL_mult_wr_en_shift                                            (13)
#define SB2_WRAPPER_CTRL_mult_wr_en_mask                                             (0x00002000)
#define SB2_WRAPPER_CTRL_mult_wr_en(data)                                            (0x00002000&((data)<<13))
#define SB2_WRAPPER_CTRL_mult_wr_en_src(data)                                        ((0x00002000&(data))>>13)
#define SB2_WRAPPER_CTRL_get_mult_wr_en(data)                                        ((0x00002000&(data))>>13)
#define SB2_WRAPPER_CTRL_write_en11_shift                                            (12)
#define SB2_WRAPPER_CTRL_write_en11_mask                                             (0x00001000)
#define SB2_WRAPPER_CTRL_write_en11(data)                                            (0x00001000&((data)<<12))
#define SB2_WRAPPER_CTRL_write_en11_src(data)                                        ((0x00001000&(data))>>12)
#define SB2_WRAPPER_CTRL_get_write_en11(data)                                        ((0x00001000&(data))>>12)
#define SB2_WRAPPER_CTRL_ac_in_order_shift                                           (11)
#define SB2_WRAPPER_CTRL_ac_in_order_mask                                            (0x00000800)
#define SB2_WRAPPER_CTRL_ac_in_order(data)                                           (0x00000800&((data)<<11))
#define SB2_WRAPPER_CTRL_ac_in_order_src(data)                                       ((0x00000800&(data))>>11)
#define SB2_WRAPPER_CTRL_get_ac_in_order(data)                                       ((0x00000800&(data))>>11)
#define SB2_WRAPPER_CTRL_write_en9_shift                                             (10)
#define SB2_WRAPPER_CTRL_write_en9_mask                                              (0x00000400)
#define SB2_WRAPPER_CTRL_write_en9(data)                                             (0x00000400&((data)<<10))
#define SB2_WRAPPER_CTRL_write_en9_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_WRAPPER_CTRL_get_write_en9(data)                                         ((0x00000400&(data))>>10)
#define SB2_WRAPPER_CTRL_ac_bypass_shift                                             (9)
#define SB2_WRAPPER_CTRL_ac_bypass_mask                                              (0x00000200)
#define SB2_WRAPPER_CTRL_ac_bypass(data)                                             (0x00000200&((data)<<9))
#define SB2_WRAPPER_CTRL_ac_bypass_src(data)                                         ((0x00000200&(data))>>9)
#define SB2_WRAPPER_CTRL_get_ac_bypass(data)                                         ((0x00000200&(data))>>9)
#define SB2_WRAPPER_CTRL_write_en7_shift                                             (8)
#define SB2_WRAPPER_CTRL_write_en7_mask                                              (0x00000100)
#define SB2_WRAPPER_CTRL_write_en7(data)                                             (0x00000100&((data)<<8))
#define SB2_WRAPPER_CTRL_write_en7_src(data)                                         ((0x00000100&(data))>>8)
#define SB2_WRAPPER_CTRL_get_write_en7(data)                                         ((0x00000100&(data))>>8)
#define SB2_WRAPPER_CTRL_ac_merge_shift                                              (7)
#define SB2_WRAPPER_CTRL_ac_merge_mask                                               (0x00000080)
#define SB2_WRAPPER_CTRL_ac_merge(data)                                              (0x00000080&((data)<<7))
#define SB2_WRAPPER_CTRL_ac_merge_src(data)                                          ((0x00000080&(data))>>7)
#define SB2_WRAPPER_CTRL_get_ac_merge(data)                                          ((0x00000080&(data))>>7)
#define SB2_WRAPPER_CTRL_write_en2_shift                                             (3)
#define SB2_WRAPPER_CTRL_write_en2_mask                                              (0x00000008)
#define SB2_WRAPPER_CTRL_write_en2(data)                                             (0x00000008&((data)<<3))
#define SB2_WRAPPER_CTRL_write_en2_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_WRAPPER_CTRL_get_write_en2(data)                                         ((0x00000008&(data))>>3)
#define SB2_WRAPPER_CTRL_sc_in_order_shift                                           (2)
#define SB2_WRAPPER_CTRL_sc_in_order_mask                                            (0x00000004)
#define SB2_WRAPPER_CTRL_sc_in_order(data)                                           (0x00000004&((data)<<2))
#define SB2_WRAPPER_CTRL_sc_in_order_src(data)                                       ((0x00000004&(data))>>2)
#define SB2_WRAPPER_CTRL_get_sc_in_order(data)                                       ((0x00000004&(data))>>2)


#define SB2_SCPU_INT_CHECK                                                           0x9801A01C
#define SB2_SCPU_INT_CHECK_reg_addr                                                  "0xD801A01C"
#define SB2_SCPU_INT_CHECK_reg                                                       0xD801A01C
#define set_SB2_SCPU_INT_CHECK_reg(data)   (*((volatile unsigned int*) SB2_SCPU_INT_CHECK_reg)=data)
#define get_SB2_SCPU_INT_CHECK_reg   (*((volatile unsigned int*) SB2_SCPU_INT_CHECK_reg))
#define SB2_SCPU_INT_CHECK_inst_adr                                                  "0x0007"
#define SB2_SCPU_INT_CHECK_inst                                                      0x0007
#define SB2_SCPU_INT_CHECK_enable_shift                                              (0)
#define SB2_SCPU_INT_CHECK_enable_mask                                               (0x00000001)
#define SB2_SCPU_INT_CHECK_enable(data)                                              (0x00000001&((data)<<0))
#define SB2_SCPU_INT_CHECK_enable_src(data)                                          ((0x00000001&(data))>>0)
#define SB2_SCPU_INT_CHECK_get_enable(data)                                          ((0x00000001&(data))>>0)


#define SB2_SYNC                                                                     0x9801A020
#define SB2_SYNC_reg_addr                                                            "0xD801A020"
#define SB2_SYNC_reg                                                                 0xD801A020
#define set_SB2_SYNC_reg(data)   (*((volatile unsigned int*) SB2_SYNC_reg)=data)
#define get_SB2_SYNC_reg   (*((volatile unsigned int*) SB2_SYNC_reg))
#define SB2_SYNC_inst_adr                                                            "0x0008"
#define SB2_SYNC_inst                                                                0x0008
#define SB2_SYNC_Sync_shift                                                          (0)
#define SB2_SYNC_Sync_mask                                                           (0xFFFFFFFF)
#define SB2_SYNC_Sync(data)                                                          (0xFFFFFFFF&((data)<<0))
#define SB2_SYNC_Sync_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define SB2_SYNC_get_Sync(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define SB2_DBG                                                                      0x9801A024
#define SB2_DBG_reg_addr                                                             "0xD801A024"
#define SB2_DBG_reg                                                                  0xD801A024
#define set_SB2_DBG_reg(data)   (*((volatile unsigned int*) SB2_DBG_reg)=data)
#define get_SB2_DBG_reg   (*((volatile unsigned int*) SB2_DBG_reg))
#define SB2_DBG_inst_adr                                                             "0x0009"
#define SB2_DBG_inst                                                                 0x0009
#define SB2_DBG_Dbg_mode_shift                                                       (0)
#define SB2_DBG_Dbg_mode_mask                                                        (0x0000001F)
#define SB2_DBG_Dbg_mode(data)                                                       (0x0000001F&((data)<<0))
#define SB2_DBG_Dbg_mode_src(data)                                                   ((0x0000001F&(data))>>0)
#define SB2_DBG_get_Dbg_mode(data)                                                   ((0x0000001F&(data))>>0)


#define SB2_SB2_DEBUG                                                                0x9801A028
#define SB2_SB2_DEBUG_reg_addr                                                       "0xD801A028"
#define SB2_SB2_DEBUG_reg                                                            0xD801A028
#define set_SB2_SB2_DEBUG_reg(data)   (*((volatile unsigned int*) SB2_SB2_DEBUG_reg)=data)
#define get_SB2_SB2_DEBUG_reg   (*((volatile unsigned int*) SB2_SB2_DEBUG_reg))
#define SB2_SB2_DEBUG_inst_adr                                                       "0x000A"
#define SB2_SB2_DEBUG_inst                                                           0x000A
#define SB2_SB2_DEBUG_write_enable3_shift                                            (15)
#define SB2_SB2_DEBUG_write_enable3_mask                                             (0x00008000)
#define SB2_SB2_DEBUG_write_enable3(data)                                            (0x00008000&((data)<<15))
#define SB2_SB2_DEBUG_write_enable3_src(data)                                        ((0x00008000&(data))>>15)
#define SB2_SB2_DEBUG_get_write_enable3(data)                                        ((0x00008000&(data))>>15)
#define SB2_SB2_DEBUG_sel1_shift                                                     (9)
#define SB2_SB2_DEBUG_sel1_mask                                                      (0x00007E00)
#define SB2_SB2_DEBUG_sel1(data)                                                     (0x00007E00&((data)<<9))
#define SB2_SB2_DEBUG_sel1_src(data)                                                 ((0x00007E00&(data))>>9)
#define SB2_SB2_DEBUG_get_sel1(data)                                                 ((0x00007E00&(data))>>9)
#define SB2_SB2_DEBUG_write_enable2_shift                                            (8)
#define SB2_SB2_DEBUG_write_enable2_mask                                             (0x00000100)
#define SB2_SB2_DEBUG_write_enable2(data)                                            (0x00000100&((data)<<8))
#define SB2_SB2_DEBUG_write_enable2_src(data)                                        ((0x00000100&(data))>>8)
#define SB2_SB2_DEBUG_get_write_enable2(data)                                        ((0x00000100&(data))>>8)
#define SB2_SB2_DEBUG_sel0_shift                                                     (2)
#define SB2_SB2_DEBUG_sel0_mask                                                      (0x000000FC)
#define SB2_SB2_DEBUG_sel0(data)                                                     (0x000000FC&((data)<<2))
#define SB2_SB2_DEBUG_sel0_src(data)                                                 ((0x000000FC&(data))>>2)
#define SB2_SB2_DEBUG_get_sel0(data)                                                 ((0x000000FC&(data))>>2)
#define SB2_SB2_DEBUG_write_enable1_shift                                            (1)
#define SB2_SB2_DEBUG_write_enable1_mask                                             (0x00000002)
#define SB2_SB2_DEBUG_write_enable1(data)                                            (0x00000002&((data)<<1))
#define SB2_SB2_DEBUG_write_enable1_src(data)                                        ((0x00000002&(data))>>1)
#define SB2_SB2_DEBUG_get_write_enable1(data)                                        ((0x00000002&(data))>>1)
#define SB2_SB2_DEBUG_enable_shift                                                   (0)
#define SB2_SB2_DEBUG_enable_mask                                                    (0x00000001)
#define SB2_SB2_DEBUG_enable(data)                                                   (0x00000001&((data)<<0))
#define SB2_SB2_DEBUG_enable_src(data)                                               ((0x00000001&(data))>>0)
#define SB2_SB2_DEBUG_get_enable(data)                                               ((0x00000001&(data))>>0)


#define SB2_RBUS1_TOSTAT                                                             0x9801A02C
#define SB2_RBUS1_TOSTAT_reg_addr                                                    "0xD801A02C"
#define SB2_RBUS1_TOSTAT_reg                                                         0xD801A02C
#define set_SB2_RBUS1_TOSTAT_reg(data)   (*((volatile unsigned int*) SB2_RBUS1_TOSTAT_reg)=data)
#define get_SB2_RBUS1_TOSTAT_reg   (*((volatile unsigned int*) SB2_RBUS1_TOSTAT_reg))
#define SB2_RBUS1_TOSTAT_inst_adr                                                    "0x000B"
#define SB2_RBUS1_TOSTAT_inst                                                        0x000B
#define SB2_RBUS1_TOSTAT_pcie1_tostat_shift                                          (19)
#define SB2_RBUS1_TOSTAT_pcie1_tostat_mask                                           (0x00080000)
#define SB2_RBUS1_TOSTAT_pcie1_tostat(data)                                          (0x00080000&((data)<<19))
#define SB2_RBUS1_TOSTAT_pcie1_tostat_src(data)                                      ((0x00080000&(data))>>19)
#define SB2_RBUS1_TOSTAT_get_pcie1_tostat(data)                                      ((0x00080000&(data))>>19)
#define SB2_RBUS1_TOSTAT_sata_tostat_shift                                           (18)
#define SB2_RBUS1_TOSTAT_sata_tostat_mask                                            (0x00040000)
#define SB2_RBUS1_TOSTAT_sata_tostat(data)                                           (0x00040000&((data)<<18))
#define SB2_RBUS1_TOSTAT_sata_tostat_src(data)                                       ((0x00040000&(data))>>18)
#define SB2_RBUS1_TOSTAT_get_sata_tostat(data)                                       ((0x00040000&(data))>>18)
#define SB2_RBUS1_TOSTAT_pcie0_tostat_shift                                          (17)
#define SB2_RBUS1_TOSTAT_pcie0_tostat_mask                                           (0x00020000)
#define SB2_RBUS1_TOSTAT_pcie0_tostat(data)                                          (0x00020000&((data)<<17))
#define SB2_RBUS1_TOSTAT_pcie0_tostat_src(data)                                      ((0x00020000&(data))>>17)
#define SB2_RBUS1_TOSTAT_get_pcie0_tostat(data)                                      ((0x00020000&(data))>>17)
#define SB2_RBUS1_TOSTAT_etn_tostat_shift                                            (16)
#define SB2_RBUS1_TOSTAT_etn_tostat_mask                                             (0x00010000)
#define SB2_RBUS1_TOSTAT_etn_tostat(data)                                            (0x00010000&((data)<<16))
#define SB2_RBUS1_TOSTAT_etn_tostat_src(data)                                        ((0x00010000&(data))>>16)
#define SB2_RBUS1_TOSTAT_get_etn_tostat(data)                                        ((0x00010000&(data))>>16)
#define SB2_RBUS1_TOSTAT_pcie1_tostat_auto_shift                                     (3)
#define SB2_RBUS1_TOSTAT_pcie1_tostat_auto_mask                                      (0x00000008)
#define SB2_RBUS1_TOSTAT_pcie1_tostat_auto(data)                                     (0x00000008&((data)<<3))
#define SB2_RBUS1_TOSTAT_pcie1_tostat_auto_src(data)                                 ((0x00000008&(data))>>3)
#define SB2_RBUS1_TOSTAT_get_pcie1_tostat_auto(data)                                 ((0x00000008&(data))>>3)
#define SB2_RBUS1_TOSTAT_sata_tostat_auto_shift                                      (2)
#define SB2_RBUS1_TOSTAT_sata_tostat_auto_mask                                       (0x00000004)
#define SB2_RBUS1_TOSTAT_sata_tostat_auto(data)                                      (0x00000004&((data)<<2))
#define SB2_RBUS1_TOSTAT_sata_tostat_auto_src(data)                                  ((0x00000004&(data))>>2)
#define SB2_RBUS1_TOSTAT_get_sata_tostat_auto(data)                                  ((0x00000004&(data))>>2)
#define SB2_RBUS1_TOSTAT_pcie0_tostat_auto_shift                                     (1)
#define SB2_RBUS1_TOSTAT_pcie0_tostat_auto_mask                                      (0x00000002)
#define SB2_RBUS1_TOSTAT_pcie0_tostat_auto(data)                                     (0x00000002&((data)<<1))
#define SB2_RBUS1_TOSTAT_pcie0_tostat_auto_src(data)                                 ((0x00000002&(data))>>1)
#define SB2_RBUS1_TOSTAT_get_pcie0_tostat_auto(data)                                 ((0x00000002&(data))>>1)
#define SB2_RBUS1_TOSTAT_etn_tostat_auto_shift                                       (0)
#define SB2_RBUS1_TOSTAT_etn_tostat_auto_mask                                        (0x00000001)
#define SB2_RBUS1_TOSTAT_etn_tostat_auto(data)                                       (0x00000001&((data)<<0))
#define SB2_RBUS1_TOSTAT_etn_tostat_auto_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_RBUS1_TOSTAT_get_etn_tostat_auto(data)                                   ((0x00000001&(data))>>0)


#define SB2_LEXRA_CTRL                                                               0x9801A070
#define SB2_LEXRA_CTRL_reg_addr                                                      "0xD801A070"
#define SB2_LEXRA_CTRL_reg                                                           0xD801A070
#define set_SB2_LEXRA_CTRL_reg(data)   (*((volatile unsigned int*) SB2_LEXRA_CTRL_reg)=data)
#define get_SB2_LEXRA_CTRL_reg   (*((volatile unsigned int*) SB2_LEXRA_CTRL_reg))
#define SB2_LEXRA_CTRL_inst_adr                                                      "0x001C"
#define SB2_LEXRA_CTRL_inst                                                          0x001C
#define SB2_LEXRA_CTRL_clk_gate_dis_shift                                            (1)
#define SB2_LEXRA_CTRL_clk_gate_dis_mask                                             (0x00000002)
#define SB2_LEXRA_CTRL_clk_gate_dis(data)                                            (0x00000002&((data)<<1))
#define SB2_LEXRA_CTRL_clk_gate_dis_src(data)                                        ((0x00000002&(data))>>1)
#define SB2_LEXRA_CTRL_get_clk_gate_dis(data)                                        ((0x00000002&(data))>>1)
#define SB2_LEXRA_CTRL_speed_up_shift                                                (0)
#define SB2_LEXRA_CTRL_speed_up_mask                                                 (0x00000001)
#define SB2_LEXRA_CTRL_speed_up(data)                                                (0x00000001&((data)<<0))
#define SB2_LEXRA_CTRL_speed_up_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_LEXRA_CTRL_get_speed_up(data)                                            ((0x00000001&(data))>>0)


#define SB2_CPU_INT                                                                  0x9801A104
#define SB2_CPU_INT_reg_addr                                                         "0xD801A104"
#define SB2_CPU_INT_reg                                                              0xD801A104
#define set_SB2_CPU_INT_reg(data)   (*((volatile unsigned int*) SB2_CPU_INT_reg)=data)
#define get_SB2_CPU_INT_reg   (*((volatile unsigned int*) SB2_CPU_INT_reg))
#define SB2_CPU_INT_inst_adr                                                         "0x0041"
#define SB2_CPU_INT_inst                                                             0x0041
#define SB2_CPU_INT_int_aswc_shift                                                   (11)
#define SB2_CPU_INT_int_aswc_mask                                                    (0x00000800)
#define SB2_CPU_INT_int_aswc(data)                                                   (0x00000800&((data)<<11))
#define SB2_CPU_INT_int_aswc_src(data)                                               ((0x00000800&(data))>>11)
#define SB2_CPU_INT_get_int_aswc(data)                                               ((0x00000800&(data))>>11)
#define SB2_CPU_INT_int_swca_shift                                                   (10)
#define SB2_CPU_INT_int_swca_mask                                                    (0x00000400)
#define SB2_CPU_INT_int_swca(data)                                                   (0x00000400&((data)<<10))
#define SB2_CPU_INT_int_swca_src(data)                                               ((0x00000400&(data))>>10)
#define SB2_CPU_INT_get_int_swca(data)                                               ((0x00000400&(data))>>10)
#define SB2_CPU_INT_int_as_shift                                                     (3)
#define SB2_CPU_INT_int_as_mask                                                      (0x00000008)
#define SB2_CPU_INT_int_as(data)                                                     (0x00000008&((data)<<3))
#define SB2_CPU_INT_int_as_src(data)                                                 ((0x00000008&(data))>>3)
#define SB2_CPU_INT_get_int_as(data)                                                 ((0x00000008&(data))>>3)
#define SB2_CPU_INT_int_sa_shift                                                     (1)
#define SB2_CPU_INT_int_sa_mask                                                      (0x00000002)
#define SB2_CPU_INT_int_sa(data)                                                     (0x00000002&((data)<<1))
#define SB2_CPU_INT_int_sa_src(data)                                                 ((0x00000002&(data))>>1)
#define SB2_CPU_INT_get_int_sa(data)                                                 ((0x00000002&(data))>>1)
#define SB2_CPU_INT_write_data_shift                                                 (0)
#define SB2_CPU_INT_write_data_mask                                                  (0x00000001)
#define SB2_CPU_INT_write_data(data)                                                 (0x00000001&((data)<<0))
#define SB2_CPU_INT_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define SB2_CPU_INT_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define SB2_CPU_INT_EN                                                               0x9801A108
#define SB2_CPU_INT_EN_reg_addr                                                      "0xD801A108"
#define SB2_CPU_INT_EN_reg                                                           0xD801A108
#define set_SB2_CPU_INT_EN_reg(data)   (*((volatile unsigned int*) SB2_CPU_INT_EN_reg)=data)
#define get_SB2_CPU_INT_EN_reg   (*((volatile unsigned int*) SB2_CPU_INT_EN_reg))
#define SB2_CPU_INT_EN_inst_adr                                                      "0x0042"
#define SB2_CPU_INT_EN_inst                                                          0x0042
#define SB2_CPU_INT_EN_int_aswc_en_shift                                             (11)
#define SB2_CPU_INT_EN_int_aswc_en_mask                                              (0x00000800)
#define SB2_CPU_INT_EN_int_aswc_en(data)                                             (0x00000800&((data)<<11))
#define SB2_CPU_INT_EN_int_aswc_en_src(data)                                         ((0x00000800&(data))>>11)
#define SB2_CPU_INT_EN_get_int_aswc_en(data)                                         ((0x00000800&(data))>>11)
#define SB2_CPU_INT_EN_int_swca_en_shift                                             (10)
#define SB2_CPU_INT_EN_int_swca_en_mask                                              (0x00000400)
#define SB2_CPU_INT_EN_int_swca_en(data)                                             (0x00000400&((data)<<10))
#define SB2_CPU_INT_EN_int_swca_en_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_CPU_INT_EN_get_int_swca_en(data)                                         ((0x00000400&(data))>>10)
#define SB2_CPU_INT_EN_int_as_en_shift                                               (3)
#define SB2_CPU_INT_EN_int_as_en_mask                                                (0x00000008)
#define SB2_CPU_INT_EN_int_as_en(data)                                               (0x00000008&((data)<<3))
#define SB2_CPU_INT_EN_int_as_en_src(data)                                           ((0x00000008&(data))>>3)
#define SB2_CPU_INT_EN_get_int_as_en(data)                                           ((0x00000008&(data))>>3)
#define SB2_CPU_INT_EN_int_sa_en_shift                                               (1)
#define SB2_CPU_INT_EN_int_sa_en_mask                                                (0x00000002)
#define SB2_CPU_INT_EN_int_sa_en(data)                                               (0x00000002&((data)<<1))
#define SB2_CPU_INT_EN_int_sa_en_src(data)                                           ((0x00000002&(data))>>1)
#define SB2_CPU_INT_EN_get_int_sa_en(data)                                           ((0x00000002&(data))>>1)
#define SB2_CPU_INT_EN_write_data_shift                                              (0)
#define SB2_CPU_INT_EN_write_data_mask                                               (0x00000001)
#define SB2_CPU_INT_EN_write_data(data)                                              (0x00000001&((data)<<0))
#define SB2_CPU_INT_EN_write_data_src(data)                                          ((0x00000001&(data))>>0)
#define SB2_CPU_INT_EN_get_write_data(data)                                          ((0x00000001&(data))>>0)


#define SB2_DREQ_MASK                                                                0x9801A138
#define SB2_DREQ_MASK_reg_addr                                                       "0xD801A138"
#define SB2_DREQ_MASK_reg                                                            0xD801A138
#define set_SB2_DREQ_MASK_reg(data)   (*((volatile unsigned int*) SB2_DREQ_MASK_reg)=data)
#define get_SB2_DREQ_MASK_reg   (*((volatile unsigned int*) SB2_DREQ_MASK_reg))
#define SB2_DREQ_MASK_inst_adr                                                       "0x004E"
#define SB2_DREQ_MASK_inst                                                           0x004E
#define SB2_DREQ_MASK_pending_shift                                                  (5)
#define SB2_DREQ_MASK_pending_mask                                                   (0x00000020)
#define SB2_DREQ_MASK_pending(data)                                                  (0x00000020&((data)<<5))
#define SB2_DREQ_MASK_pending_src(data)                                              ((0x00000020&(data))>>5)
#define SB2_DREQ_MASK_get_pending(data)                                              ((0x00000020&(data))>>5)
#define SB2_DREQ_MASK_mask_id_shift                                                  (0)
#define SB2_DREQ_MASK_mask_id_mask                                                   (0x00000007)
#define SB2_DREQ_MASK_mask_id(data)                                                  (0x00000007&((data)<<0))
#define SB2_DREQ_MASK_mask_id_src(data)                                              ((0x00000007&(data))>>0)
#define SB2_DREQ_MASK_get_mask_id(data)                                              ((0x00000007&(data))>>0)


#define SB2_CHIP_ID                                                                  0x9801A200
#define SB2_CHIP_ID_reg_addr                                                         "0xD801A200"
#define SB2_CHIP_ID_reg                                                              0xD801A200
#define set_SB2_CHIP_ID_reg(data)   (*((volatile unsigned int*) SB2_CHIP_ID_reg)=data)
#define get_SB2_CHIP_ID_reg   (*((volatile unsigned int*) SB2_CHIP_ID_reg))
#define SB2_CHIP_ID_inst_adr                                                         "0x0080"
#define SB2_CHIP_ID_inst                                                             0x0080
#define SB2_CHIP_ID_Chip_id_shift                                                    (0)
#define SB2_CHIP_ID_Chip_id_mask                                                     (0x0000FFFF)
#define SB2_CHIP_ID_Chip_id(data)                                                    (0x0000FFFF&((data)<<0))
#define SB2_CHIP_ID_Chip_id_src(data)                                                ((0x0000FFFF&(data))>>0)
#define SB2_CHIP_ID_get_Chip_id(data)                                                ((0x0000FFFF&(data))>>0)


#define SB2_CHIP_INFO                                                                0x9801A204
#define SB2_CHIP_INFO_reg_addr                                                       "0xD801A204"
#define SB2_CHIP_INFO_reg                                                            0xD801A204
#define set_SB2_CHIP_INFO_reg(data)   (*((volatile unsigned int*) SB2_CHIP_INFO_reg)=data)
#define get_SB2_CHIP_INFO_reg   (*((volatile unsigned int*) SB2_CHIP_INFO_reg))
#define SB2_CHIP_INFO_inst_adr                                                       "0x0081"
#define SB2_CHIP_INFO_inst                                                           0x0081
#define SB2_CHIP_INFO_Revise_id_shift                                                (16)
#define SB2_CHIP_INFO_Revise_id_mask                                                 (0xFFFF0000)
#define SB2_CHIP_INFO_Revise_id(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_CHIP_INFO_Revise_id_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_CHIP_INFO_get_Revise_id(data)                                            ((0xFFFF0000&(data))>>16)


#define SB2_ACPU_ROM_REMAP                                                           0x9801A300
#define SB2_ACPU_ROM_REMAP_reg_addr                                                  "0xD801A300"
#define SB2_ACPU_ROM_REMAP_reg                                                       0xD801A300
#define set_SB2_ACPU_ROM_REMAP_reg(data)   (*((volatile unsigned int*) SB2_ACPU_ROM_REMAP_reg)=data)
#define get_SB2_ACPU_ROM_REMAP_reg   (*((volatile unsigned int*) SB2_ACPU_ROM_REMAP_reg))
#define SB2_ACPU_ROM_REMAP_inst_adr                                                  "0x00C0"
#define SB2_ACPU_ROM_REMAP_inst                                                      0x00C0
#define SB2_ACPU_ROM_REMAP_rom_remap_shift                                           (12)
#define SB2_ACPU_ROM_REMAP_rom_remap_mask                                            (0xFFFFF000)
#define SB2_ACPU_ROM_REMAP_rom_remap(data)                                           (0xFFFFF000&((data)<<12))
#define SB2_ACPU_ROM_REMAP_rom_remap_src(data)                                       ((0xFFFFF000&(data))>>12)
#define SB2_ACPU_ROM_REMAP_get_rom_remap(data)                                       ((0xFFFFF000&(data))>>12)


#define SB2_ACPU_DELAY                                                               0x9801A304
#define SB2_ACPU_DELAY_reg_addr                                                      "0xD801A304"
#define SB2_ACPU_DELAY_reg                                                           0xD801A304
#define set_SB2_ACPU_DELAY_reg(data)   (*((volatile unsigned int*) SB2_ACPU_DELAY_reg)=data)
#define get_SB2_ACPU_DELAY_reg   (*((volatile unsigned int*) SB2_ACPU_DELAY_reg))
#define SB2_ACPU_DELAY_inst_adr                                                      "0x00C1"
#define SB2_ACPU_DELAY_inst                                                          0x00C1
#define SB2_ACPU_DELAY_gnt_wr_delay_shift                                            (28)
#define SB2_ACPU_DELAY_gnt_wr_delay_mask                                             (0xF0000000)
#define SB2_ACPU_DELAY_gnt_wr_delay(data)                                            (0xF0000000&((data)<<28))
#define SB2_ACPU_DELAY_gnt_wr_delay_src(data)                                        ((0xF0000000&(data))>>28)
#define SB2_ACPU_DELAY_get_gnt_wr_delay(data)                                        ((0xF0000000&(data))>>28)
#define SB2_ACPU_DELAY_acc_write_delay_shift                                         (24)
#define SB2_ACPU_DELAY_acc_write_delay_mask                                          (0x0F000000)
#define SB2_ACPU_DELAY_acc_write_delay(data)                                         (0x0F000000&((data)<<24))
#define SB2_ACPU_DELAY_acc_write_delay_src(data)                                     ((0x0F000000&(data))>>24)
#define SB2_ACPU_DELAY_get_acc_write_delay(data)                                     ((0x0F000000&(data))>>24)
#define SB2_ACPU_DELAY_did_com_shift                                                 (16)
#define SB2_ACPU_DELAY_did_com_mask                                                  (0x000F0000)
#define SB2_ACPU_DELAY_did_com(data)                                                 (0x000F0000&((data)<<16))
#define SB2_ACPU_DELAY_did_com_src(data)                                             ((0x000F0000&(data))>>16)
#define SB2_ACPU_DELAY_get_did_com(data)                                             ((0x000F0000&(data))>>16)
#define SB2_ACPU_DELAY_read_comm_shift                                               (8)
#define SB2_ACPU_DELAY_read_comm_mask                                                (0x00000F00)
#define SB2_ACPU_DELAY_read_comm(data)                                               (0x00000F00&((data)<<8))
#define SB2_ACPU_DELAY_read_comm_src(data)                                           ((0x00000F00&(data))>>8)
#define SB2_ACPU_DELAY_get_read_comm(data)                                           ((0x00000F00&(data))>>8)
#define SB2_ACPU_DELAY_addcmd_shift                                                  (0)
#define SB2_ACPU_DELAY_addcmd_mask                                                   (0x0000000F)
#define SB2_ACPU_DELAY_addcmd(data)                                                  (0x0000000F&((data)<<0))
#define SB2_ACPU_DELAY_addcmd_src(data)                                              ((0x0000000F&(data))>>0)
#define SB2_ACPU_DELAY_get_addcmd(data)                                              ((0x0000000F&(data))>>0)


#define SB2_RBUS_ICG1                                                                0x9801A308
#define SB2_RBUS_ICG1_reg_addr                                                       "0xD801A308"
#define SB2_RBUS_ICG1_reg                                                            0xD801A308
#define set_SB2_RBUS_ICG1_reg(data)   (*((volatile unsigned int*) SB2_RBUS_ICG1_reg)=data)
#define get_SB2_RBUS_ICG1_reg   (*((volatile unsigned int*) SB2_RBUS_ICG1_reg))
#define SB2_RBUS_ICG1_inst_adr                                                       "0x00C2"
#define SB2_RBUS_ICG1_inst                                                           0x00C2
#define SB2_RBUS_ICG1_cbustx_en_shift                                                (31)
#define SB2_RBUS_ICG1_cbustx_en_mask                                                 (0x80000000)
#define SB2_RBUS_ICG1_cbustx_en(data)                                                (0x80000000&((data)<<31))
#define SB2_RBUS_ICG1_cbustx_en_src(data)                                            ((0x80000000&(data))>>31)
#define SB2_RBUS_ICG1_get_cbustx_en(data)                                            ((0x80000000&(data))>>31)
#define SB2_RBUS_ICG1_cbusiso_en_shift                                               (30)
#define SB2_RBUS_ICG1_cbusiso_en_mask                                                (0x40000000)
#define SB2_RBUS_ICG1_cbusiso_en(data)                                               (0x40000000&((data)<<30))
#define SB2_RBUS_ICG1_cbusiso_en_src(data)                                           ((0x40000000&(data))>>30)
#define SB2_RBUS_ICG1_get_cbusiso_en(data)                                           ((0x40000000&(data))>>30)
#define SB2_RBUS_ICG1_isomis_en_shift                                                (29)
#define SB2_RBUS_ICG1_isomis_en_mask                                                 (0x20000000)
#define SB2_RBUS_ICG1_isomis_en(data)                                                (0x20000000&((data)<<29))
#define SB2_RBUS_ICG1_isomis_en_src(data)                                            ((0x20000000&(data))>>29)
#define SB2_RBUS_ICG1_get_isomis_en(data)                                            ((0x20000000&(data))>>29)
#define SB2_RBUS_ICG1_ae_en_shift                                                    (28)
#define SB2_RBUS_ICG1_ae_en_mask                                                     (0x10000000)
#define SB2_RBUS_ICG1_ae_en(data)                                                    (0x10000000&((data)<<28))
#define SB2_RBUS_ICG1_ae_en_src(data)                                                ((0x10000000&(data))>>28)
#define SB2_RBUS_ICG1_get_ae_en(data)                                                ((0x10000000&(data))>>28)
#define SB2_RBUS_ICG1_gpu_en_shift                                                   (27)
#define SB2_RBUS_ICG1_gpu_en_mask                                                    (0x08000000)
#define SB2_RBUS_ICG1_gpu_en(data)                                                   (0x08000000&((data)<<27))
#define SB2_RBUS_ICG1_gpu_en_src(data)                                               ((0x08000000&(data))>>27)
#define SB2_RBUS_ICG1_get_gpu_en(data)                                               ((0x08000000&(data))>>27)
#define SB2_RBUS_ICG1_mis_en_shift                                                   (26)
#define SB2_RBUS_ICG1_mis_en_mask                                                    (0x04000000)
#define SB2_RBUS_ICG1_mis_en(data)                                                   (0x04000000&((data)<<26))
#define SB2_RBUS_ICG1_mis_en_src(data)                                               ((0x04000000&(data))>>26)
#define SB2_RBUS_ICG1_get_mis_en(data)                                               ((0x04000000&(data))>>26)
#define SB2_RBUS_ICG1_rsa_en_shift                                                   (25)
#define SB2_RBUS_ICG1_rsa_en_mask                                                    (0x02000000)
#define SB2_RBUS_ICG1_rsa_en(data)                                                   (0x02000000&((data)<<25))
#define SB2_RBUS_ICG1_rsa_en_src(data)                                               ((0x02000000&(data))>>25)
#define SB2_RBUS_ICG1_get_rsa_en(data)                                               ((0x02000000&(data))>>25)
#define SB2_RBUS_ICG1_dcsb_en_shift                                                  (24)
#define SB2_RBUS_ICG1_dcsb_en_mask                                                   (0x01000000)
#define SB2_RBUS_ICG1_dcsb_en(data)                                                  (0x01000000&((data)<<24))
#define SB2_RBUS_ICG1_dcsb_en_src(data)                                              ((0x01000000&(data))>>24)
#define SB2_RBUS_ICG1_get_dcsb_en(data)                                              ((0x01000000&(data))>>24)
#define SB2_RBUS_ICG1_scw_en_shift                                                   (23)
#define SB2_RBUS_ICG1_scw_en_mask                                                    (0x00800000)
#define SB2_RBUS_ICG1_scw_en(data)                                                   (0x00800000&((data)<<23))
#define SB2_RBUS_ICG1_scw_en_src(data)                                               ((0x00800000&(data))>>23)
#define SB2_RBUS_ICG1_get_scw_en(data)                                               ((0x00800000&(data))>>23)
#define SB2_RBUS_ICG1_sbx_en_shift                                                   (22)
#define SB2_RBUS_ICG1_sbx_en_mask                                                    (0x00400000)
#define SB2_RBUS_ICG1_sbx_en(data)                                                   (0x00400000&((data)<<22))
#define SB2_RBUS_ICG1_sbx_en_src(data)                                               ((0x00400000&(data))>>22)
#define SB2_RBUS_ICG1_get_sbx_en(data)                                               ((0x00400000&(data))>>22)
#define SB2_RBUS_ICG1_sb2_en_shift                                                   (21)
#define SB2_RBUS_ICG1_sb2_en_mask                                                    (0x00200000)
#define SB2_RBUS_ICG1_sb2_en(data)                                                   (0x00200000&((data)<<21))
#define SB2_RBUS_ICG1_sb2_en_src(data)                                               ((0x00200000&(data))>>21)
#define SB2_RBUS_ICG1_get_sb2_en(data)                                               ((0x00200000&(data))>>21)
#define SB2_RBUS_ICG1_md_en_shift                                                    (20)
#define SB2_RBUS_ICG1_md_en_mask                                                     (0x00100000)
#define SB2_RBUS_ICG1_md_en(data)                                                    (0x00100000&((data)<<20))
#define SB2_RBUS_ICG1_md_en_src(data)                                                ((0x00100000&(data))>>20)
#define SB2_RBUS_ICG1_get_md_en(data)                                                ((0x00100000&(data))>>20)
#define SB2_RBUS_ICG1_jpeg_en_shift                                                  (19)
#define SB2_RBUS_ICG1_jpeg_en_mask                                                   (0x00080000)
#define SB2_RBUS_ICG1_jpeg_en(data)                                                  (0x00080000&((data)<<19))
#define SB2_RBUS_ICG1_jpeg_en_src(data)                                              ((0x00080000&(data))>>19)
#define SB2_RBUS_ICG1_get_jpeg_en(data)                                              ((0x00080000&(data))>>19)
#define SB2_RBUS_ICG1_nat_en_shift                                                   (18)
#define SB2_RBUS_ICG1_nat_en_mask                                                    (0x00040000)
#define SB2_RBUS_ICG1_nat_en(data)                                                   (0x00040000&((data)<<18))
#define SB2_RBUS_ICG1_nat_en_src(data)                                               ((0x00040000&(data))>>18)
#define SB2_RBUS_ICG1_get_nat_en(data)                                               ((0x00040000&(data))>>18)
#define SB2_RBUS_ICG1_usb3host_2_en_shift                                            (17)
#define SB2_RBUS_ICG1_usb3host_2_en_mask                                             (0x00020000)
#define SB2_RBUS_ICG1_usb3host_2_en(data)                                            (0x00020000&((data)<<17))
#define SB2_RBUS_ICG1_usb3host_2_en_src(data)                                        ((0x00020000&(data))>>17)
#define SB2_RBUS_ICG1_get_usb3host_2_en(data)                                        ((0x00020000&(data))>>17)
#define SB2_RBUS_ICG1_usb3drd_en_shift                                               (16)
#define SB2_RBUS_ICG1_usb3drd_en_mask                                                (0x00010000)
#define SB2_RBUS_ICG1_usb3drd_en(data)                                               (0x00010000&((data)<<16))
#define SB2_RBUS_ICG1_usb3drd_en_src(data)                                           ((0x00010000&(data))>>16)
#define SB2_RBUS_ICG1_get_usb3drd_en(data)                                           ((0x00010000&(data))>>16)
#define SB2_RBUS_ICG1_usb3host_en_shift                                              (15)
#define SB2_RBUS_ICG1_usb3host_en_mask                                               (0x00008000)
#define SB2_RBUS_ICG1_usb3host_en(data)                                              (0x00008000&((data)<<15))
#define SB2_RBUS_ICG1_usb3host_en_src(data)                                          ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG1_get_usb3host_en(data)                                          ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG1_usb2_en_shift                                                  (14)
#define SB2_RBUS_ICG1_usb2_en_mask                                                   (0x00004000)
#define SB2_RBUS_ICG1_usb2_en(data)                                                  (0x00004000&((data)<<14))
#define SB2_RBUS_ICG1_usb2_en_src(data)                                              ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG1_get_usb2_en(data)                                              ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG1_usb_en_shift                                                   (13)
#define SB2_RBUS_ICG1_usb_en_mask                                                    (0x00002000)
#define SB2_RBUS_ICG1_usb_en(data)                                                   (0x00002000&((data)<<13))
#define SB2_RBUS_ICG1_usb_en_src(data)                                               ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG1_get_usb_en(data)                                               ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG1_dbp4_en_shift                                                  (12)
#define SB2_RBUS_ICG1_dbp4_en_mask                                                   (0x00001000)
#define SB2_RBUS_ICG1_dbp4_en(data)                                                  (0x00001000&((data)<<12))
#define SB2_RBUS_ICG1_dbp4_en_src(data)                                              ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG1_get_dbp4_en(data)                                              ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG1_dbp_en_shift                                                   (11)
#define SB2_RBUS_ICG1_dbp_en_mask                                                    (0x00000800)
#define SB2_RBUS_ICG1_dbp_en(data)                                                   (0x00000800&((data)<<11))
#define SB2_RBUS_ICG1_dbp_en_src(data)                                               ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG1_get_dbp_en(data)                                               ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG1_efs_en_shift                                                   (10)
#define SB2_RBUS_ICG1_efs_en_mask                                                    (0x00000400)
#define SB2_RBUS_ICG1_efs_en(data)                                                   (0x00000400&((data)<<10))
#define SB2_RBUS_ICG1_efs_en_src(data)                                               ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG1_get_efs_en(data)                                               ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG1_etn_en_shift                                                   (9)
#define SB2_RBUS_ICG1_etn_en_mask                                                    (0x00000200)
#define SB2_RBUS_ICG1_etn_en(data)                                                   (0x00000200&((data)<<9))
#define SB2_RBUS_ICG1_etn_en_src(data)                                               ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG1_get_etn_en(data)                                               ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG1_pcie_en_shift                                                  (8)
#define SB2_RBUS_ICG1_pcie_en_mask                                                   (0x00000100)
#define SB2_RBUS_ICG1_pcie_en(data)                                                  (0x00000100&((data)<<8))
#define SB2_RBUS_ICG1_pcie_en_src(data)                                              ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG1_get_pcie_en(data)                                              ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG1_cr_en_shift                                                    (7)
#define SB2_RBUS_ICG1_cr_en_mask                                                     (0x00000080)
#define SB2_RBUS_ICG1_cr_en(data)                                                    (0x00000080&((data)<<7))
#define SB2_RBUS_ICG1_cr_en_src(data)                                                ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG1_get_cr_en(data)                                                ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG1_sdio_en_shift                                                  (6)
#define SB2_RBUS_ICG1_sdio_en_mask                                                   (0x00000040)
#define SB2_RBUS_ICG1_sdio_en(data)                                                  (0x00000040&((data)<<6))
#define SB2_RBUS_ICG1_sdio_en_src(data)                                              ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG1_get_sdio_en(data)                                              ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG1_emmc_en_shift                                                  (5)
#define SB2_RBUS_ICG1_emmc_en_mask                                                   (0x00000020)
#define SB2_RBUS_ICG1_emmc_en(data)                                                  (0x00000020&((data)<<5))
#define SB2_RBUS_ICG1_emmc_en_src(data)                                              ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG1_get_emmc_en(data)                                              ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG1_nfs_en_shift                                                   (4)
#define SB2_RBUS_ICG1_nfs_en_mask                                                    (0x00000010)
#define SB2_RBUS_ICG1_nfs_en(data)                                                   (0x00000010&((data)<<4))
#define SB2_RBUS_ICG1_nfs_en_src(data)                                               ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG1_get_nfs_en(data)                                               ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG1_nf_en_shift                                                    (3)
#define SB2_RBUS_ICG1_nf_en_mask                                                     (0x00000008)
#define SB2_RBUS_ICG1_nf_en(data)                                                    (0x00000008&((data)<<3))
#define SB2_RBUS_ICG1_nf_en_src(data)                                                ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG1_get_nf_en(data)                                                ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG1_sata_en_shift                                                  (2)
#define SB2_RBUS_ICG1_sata_en_mask                                                   (0x00000004)
#define SB2_RBUS_ICG1_sata_en(data)                                                  (0x00000004&((data)<<2))
#define SB2_RBUS_ICG1_sata_en_src(data)                                              ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG1_get_sata_en(data)                                              ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG1_tp_en_shift                                                    (1)
#define SB2_RBUS_ICG1_tp_en_mask                                                     (0x00000002)
#define SB2_RBUS_ICG1_tp_en(data)                                                    (0x00000002&((data)<<1))
#define SB2_RBUS_ICG1_tp_en_src(data)                                                ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG1_get_tp_en(data)                                                ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG1_cp_en_shift                                                    (0)
#define SB2_RBUS_ICG1_cp_en_mask                                                     (0x00000001)
#define SB2_RBUS_ICG1_cp_en(data)                                                    (0x00000001&((data)<<0))
#define SB2_RBUS_ICG1_cp_en_src(data)                                                ((0x00000001&(data))>>0)
#define SB2_RBUS_ICG1_get_cp_en(data)                                                ((0x00000001&(data))>>0)


#define SB2_RBUS_ICG2                                                                0x9801A30C
#define SB2_RBUS_ICG2_reg_addr                                                       "0xD801A30C"
#define SB2_RBUS_ICG2_reg                                                            0xD801A30C
#define set_SB2_RBUS_ICG2_reg(data)   (*((volatile unsigned int*) SB2_RBUS_ICG2_reg)=data)
#define get_SB2_RBUS_ICG2_reg   (*((volatile unsigned int*) SB2_RBUS_ICG2_reg))
#define SB2_RBUS_ICG2_inst_adr                                                       "0x00C3"
#define SB2_RBUS_ICG2_inst                                                           0x00C3
#define SB2_RBUS_ICG2_ve3_en_shift                                                   (15)
#define SB2_RBUS_ICG2_ve3_en_mask                                                    (0x00008000)
#define SB2_RBUS_ICG2_ve3_en(data)                                                   (0x00008000&((data)<<15))
#define SB2_RBUS_ICG2_ve3_en_src(data)                                               ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG2_get_ve3_en(data)                                               ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG2_ve2_en_shift                                                   (14)
#define SB2_RBUS_ICG2_ve2_en_mask                                                    (0x00004000)
#define SB2_RBUS_ICG2_ve2_en(data)                                                   (0x00004000&((data)<<14))
#define SB2_RBUS_ICG2_ve2_en_src(data)                                               ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG2_get_ve2_en(data)                                               ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG2_ve1_en_shift                                                   (13)
#define SB2_RBUS_ICG2_ve1_en_mask                                                    (0x00002000)
#define SB2_RBUS_ICG2_ve1_en(data)                                                   (0x00002000&((data)<<13))
#define SB2_RBUS_ICG2_ve1_en_src(data)                                               ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG2_get_ve1_en(data)                                               ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG2_lvds_en_shift                                                  (12)
#define SB2_RBUS_ICG2_lvds_en_mask                                                   (0x00001000)
#define SB2_RBUS_ICG2_lvds_en(data)                                                  (0x00001000&((data)<<12))
#define SB2_RBUS_ICG2_lvds_en_src(data)                                              ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG2_get_lvds_en(data)                                              ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG2_edp_en_shift                                                   (11)
#define SB2_RBUS_ICG2_edp_en_mask                                                    (0x00000800)
#define SB2_RBUS_ICG2_edp_en(data)                                                   (0x00000800&((data)<<11))
#define SB2_RBUS_ICG2_edp_en_src(data)                                               ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG2_get_edp_en(data)                                               ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG2_cbusrx_en_shift                                                (10)
#define SB2_RBUS_ICG2_cbusrx_en_mask                                                 (0x00000400)
#define SB2_RBUS_ICG2_cbusrx_en(data)                                                (0x00000400&((data)<<10))
#define SB2_RBUS_ICG2_cbusrx_en_src(data)                                            ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG2_get_cbusrx_en(data)                                            ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG2_hdmir_en_shift                                                 (9)
#define SB2_RBUS_ICG2_hdmir_en_mask                                                  (0x00000200)
#define SB2_RBUS_ICG2_hdmir_en(data)                                                 (0x00000200&((data)<<9))
#define SB2_RBUS_ICG2_hdmir_en_src(data)                                             ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG2_get_hdmir_en(data)                                             ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG2_hdmit_en_shift                                                 (8)
#define SB2_RBUS_ICG2_hdmit_en_mask                                                  (0x00000100)
#define SB2_RBUS_ICG2_hdmit_en(data)                                                 (0x00000100&((data)<<8))
#define SB2_RBUS_ICG2_hdmit_en_src(data)                                             ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG2_get_hdmit_en(data)                                             ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG2_se_en_shift                                                    (7)
#define SB2_RBUS_ICG2_se_en_mask                                                     (0x00000080)
#define SB2_RBUS_ICG2_se_en(data)                                                    (0x00000080&((data)<<7))
#define SB2_RBUS_ICG2_se_en_src(data)                                                ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG2_get_se_en(data)                                                ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG2_mipi_en_shift                                                  (6)
#define SB2_RBUS_ICG2_mipi_en_mask                                                   (0x00000040)
#define SB2_RBUS_ICG2_mipi_en(data)                                                  (0x00000040&((data)<<6))
#define SB2_RBUS_ICG2_mipi_en_src(data)                                              ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG2_get_mipi_en(data)                                              ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG2_dptmx_en_shift                                                 (5)
#define SB2_RBUS_ICG2_dptmx_en_mask                                                  (0x00000020)
#define SB2_RBUS_ICG2_dptmx_en(data)                                                 (0x00000020&((data)<<5))
#define SB2_RBUS_ICG2_dptmx_en_src(data)                                             ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG2_get_dptmx_en(data)                                             ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG2_tve_en_shift                                                   (4)
#define SB2_RBUS_ICG2_tve_en_mask                                                    (0x00000010)
#define SB2_RBUS_ICG2_tve_en(data)                                                   (0x00000010&((data)<<4))
#define SB2_RBUS_ICG2_tve_en_src(data)                                               ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG2_get_tve_en(data)                                               ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG2_voregsram_en_shift                                             (3)
#define SB2_RBUS_ICG2_voregsram_en_mask                                              (0x00000008)
#define SB2_RBUS_ICG2_voregsram_en(data)                                             (0x00000008&((data)<<3))
#define SB2_RBUS_ICG2_voregsram_en_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG2_get_voregsram_en(data)                                         ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG2_ao_en_shift                                                    (2)
#define SB2_RBUS_ICG2_ao_en_mask                                                     (0x00000004)
#define SB2_RBUS_ICG2_ao_en(data)                                                    (0x00000004&((data)<<2))
#define SB2_RBUS_ICG2_ao_en_src(data)                                                ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG2_get_ao_en(data)                                                ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG2_vo_en_shift                                                    (1)
#define SB2_RBUS_ICG2_vo_en_mask                                                     (0x00000002)
#define SB2_RBUS_ICG2_vo_en(data)                                                    (0x00000002&((data)<<1))
#define SB2_RBUS_ICG2_vo_en_src(data)                                                ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG2_get_vo_en(data)                                                ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG2_sys_en_shift                                                   (0)
#define SB2_RBUS_ICG2_sys_en_mask                                                    (0x00000001)
#define SB2_RBUS_ICG2_sys_en(data)                                                   (0x00000001&((data)<<0))
#define SB2_RBUS_ICG2_sys_en_src(data)                                               ((0x00000001&(data))>>0)
#define SB2_RBUS_ICG2_get_sys_en(data)                                               ((0x00000001&(data))>>0)


#define SB2_RBUS_ICG3                                                                0x9801A310
#define SB2_RBUS_ICG3_reg_addr                                                       "0xD801A310"
#define SB2_RBUS_ICG3_reg                                                            0xD801A310
#define set_SB2_RBUS_ICG3_reg(data)   (*((volatile unsigned int*) SB2_RBUS_ICG3_reg)=data)
#define get_SB2_RBUS_ICG3_reg   (*((volatile unsigned int*) SB2_RBUS_ICG3_reg))
#define SB2_RBUS_ICG3_inst_adr                                                       "0x00C4"
#define SB2_RBUS_ICG3_inst                                                           0x00C4
#define SB2_RBUS_ICG3_tmp11_shift                                                    (15)
#define SB2_RBUS_ICG3_tmp11_mask                                                     (0x00008000)
#define SB2_RBUS_ICG3_tmp11(data)                                                    (0x00008000&((data)<<15))
#define SB2_RBUS_ICG3_tmp11_src(data)                                                ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG3_get_tmp11(data)                                                ((0x00008000&(data))>>15)
#define SB2_RBUS_ICG3_tmp10_shift                                                    (14)
#define SB2_RBUS_ICG3_tmp10_mask                                                     (0x00004000)
#define SB2_RBUS_ICG3_tmp10(data)                                                    (0x00004000&((data)<<14))
#define SB2_RBUS_ICG3_tmp10_src(data)                                                ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG3_get_tmp10(data)                                                ((0x00004000&(data))>>14)
#define SB2_RBUS_ICG3_tmp9_shift                                                     (13)
#define SB2_RBUS_ICG3_tmp9_mask                                                      (0x00002000)
#define SB2_RBUS_ICG3_tmp9(data)                                                     (0x00002000&((data)<<13))
#define SB2_RBUS_ICG3_tmp9_src(data)                                                 ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG3_get_tmp9(data)                                                 ((0x00002000&(data))>>13)
#define SB2_RBUS_ICG3_tmp8_shift                                                     (12)
#define SB2_RBUS_ICG3_tmp8_mask                                                      (0x00001000)
#define SB2_RBUS_ICG3_tmp8(data)                                                     (0x00001000&((data)<<12))
#define SB2_RBUS_ICG3_tmp8_src(data)                                                 ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG3_get_tmp8(data)                                                 ((0x00001000&(data))>>12)
#define SB2_RBUS_ICG3_tmp7_shift                                                     (11)
#define SB2_RBUS_ICG3_tmp7_mask                                                      (0x00000800)
#define SB2_RBUS_ICG3_tmp7(data)                                                     (0x00000800&((data)<<11))
#define SB2_RBUS_ICG3_tmp7_src(data)                                                 ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG3_get_tmp7(data)                                                 ((0x00000800&(data))>>11)
#define SB2_RBUS_ICG3_tmp6_shift                                                     (10)
#define SB2_RBUS_ICG3_tmp6_mask                                                      (0x00000400)
#define SB2_RBUS_ICG3_tmp6(data)                                                     (0x00000400&((data)<<10))
#define SB2_RBUS_ICG3_tmp6_src(data)                                                 ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG3_get_tmp6(data)                                                 ((0x00000400&(data))>>10)
#define SB2_RBUS_ICG3_tmp5_shift                                                     (9)
#define SB2_RBUS_ICG3_tmp5_mask                                                      (0x00000200)
#define SB2_RBUS_ICG3_tmp5(data)                                                     (0x00000200&((data)<<9))
#define SB2_RBUS_ICG3_tmp5_src(data)                                                 ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG3_get_tmp5(data)                                                 ((0x00000200&(data))>>9)
#define SB2_RBUS_ICG3_tmp4_shift                                                     (8)
#define SB2_RBUS_ICG3_tmp4_mask                                                      (0x00000100)
#define SB2_RBUS_ICG3_tmp4(data)                                                     (0x00000100&((data)<<8))
#define SB2_RBUS_ICG3_tmp4_src(data)                                                 ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG3_get_tmp4(data)                                                 ((0x00000100&(data))>>8)
#define SB2_RBUS_ICG3_tmp3_shift                                                     (7)
#define SB2_RBUS_ICG3_tmp3_mask                                                      (0x00000080)
#define SB2_RBUS_ICG3_tmp3(data)                                                     (0x00000080&((data)<<7))
#define SB2_RBUS_ICG3_tmp3_src(data)                                                 ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG3_get_tmp3(data)                                                 ((0x00000080&(data))>>7)
#define SB2_RBUS_ICG3_tmp2_shift                                                     (6)
#define SB2_RBUS_ICG3_tmp2_mask                                                      (0x00000040)
#define SB2_RBUS_ICG3_tmp2(data)                                                     (0x00000040&((data)<<6))
#define SB2_RBUS_ICG3_tmp2_src(data)                                                 ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG3_get_tmp2(data)                                                 ((0x00000040&(data))>>6)
#define SB2_RBUS_ICG3_tmp1_shift                                                     (5)
#define SB2_RBUS_ICG3_tmp1_mask                                                      (0x00000020)
#define SB2_RBUS_ICG3_tmp1(data)                                                     (0x00000020&((data)<<5))
#define SB2_RBUS_ICG3_tmp1_src(data)                                                 ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG3_get_tmp1(data)                                                 ((0x00000020&(data))>>5)
#define SB2_RBUS_ICG3_tmp0_shift                                                     (4)
#define SB2_RBUS_ICG3_tmp0_mask                                                      (0x00000010)
#define SB2_RBUS_ICG3_tmp0(data)                                                     (0x00000010&((data)<<4))
#define SB2_RBUS_ICG3_tmp0_src(data)                                                 ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG3_get_tmp0(data)                                                 ((0x00000010&(data))>>4)
#define SB2_RBUS_ICG3_mon_en_shift                                                   (3)
#define SB2_RBUS_ICG3_mon_en_mask                                                    (0x00000008)
#define SB2_RBUS_ICG3_mon_en(data)                                                   (0x00000008&((data)<<3))
#define SB2_RBUS_ICG3_mon_en_src(data)                                               ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG3_get_mon_en(data)                                               ((0x00000008&(data))>>3)
#define SB2_RBUS_ICG3_dbus_en_shift                                                  (2)
#define SB2_RBUS_ICG3_dbus_en_mask                                                   (0x00000004)
#define SB2_RBUS_ICG3_dbus_en(data)                                                  (0x00000004&((data)<<2))
#define SB2_RBUS_ICG3_dbus_en_src(data)                                              ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG3_get_dbus_en(data)                                              ((0x00000004&(data))>>2)
#define SB2_RBUS_ICG3_rbus_en_shift                                                  (1)
#define SB2_RBUS_ICG3_rbus_en_mask                                                   (0x00000002)
#define SB2_RBUS_ICG3_rbus_en(data)                                                  (0x00000002&((data)<<1))
#define SB2_RBUS_ICG3_rbus_en_src(data)                                              ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG3_get_rbus_en(data)                                              ((0x00000002&(data))>>1)
#define SB2_RBUS_ICG3_spi_en_shift                                                   (0)
#define SB2_RBUS_ICG3_spi_en_mask                                                    (0x00000001)
#define SB2_RBUS_ICG3_spi_en(data)                                                   (0x00000001&((data)<<0))
#define SB2_RBUS_ICG3_spi_en_src(data)                                               ((0x00000001&(data))>>0)
#define SB2_RBUS_ICG3_get_spi_en(data)                                               ((0x00000001&(data))>>0)


#define SB2_HIF_CTRL1                                                                0x9801A314
#define SB2_HIF_CTRL1_reg_addr                                                       "0xD801A314"
#define SB2_HIF_CTRL1_reg                                                            0xD801A314
#define set_SB2_HIF_CTRL1_reg(data)   (*((volatile unsigned int*) SB2_HIF_CTRL1_reg)=data)
#define get_SB2_HIF_CTRL1_reg   (*((volatile unsigned int*) SB2_HIF_CTRL1_reg))
#define SB2_HIF_CTRL1_inst_adr                                                       "0x00C5"
#define SB2_HIF_CTRL1_inst                                                           0x00C5
#define SB2_HIF_CTRL1_hif_rdata_swap_shift                                           (1)
#define SB2_HIF_CTRL1_hif_rdata_swap_mask                                            (0x00000002)
#define SB2_HIF_CTRL1_hif_rdata_swap(data)                                           (0x00000002&((data)<<1))
#define SB2_HIF_CTRL1_hif_rdata_swap_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_HIF_CTRL1_get_hif_rdata_swap(data)                                       ((0x00000002&(data))>>1)
#define SB2_HIF_CTRL1_hif_wdata_swap_shift                                           (0)
#define SB2_HIF_CTRL1_hif_wdata_swap_mask                                            (0x00000001)
#define SB2_HIF_CTRL1_hif_wdata_swap(data)                                           (0x00000001&((data)<<0))
#define SB2_HIF_CTRL1_hif_wdata_swap_src(data)                                       ((0x00000001&(data))>>0)
#define SB2_HIF_CTRL1_get_hif_wdata_swap(data)                                       ((0x00000001&(data))>>0)


#define SB2_PC_CTRL                                                                  0x9801A400
#define SB2_PC_CTRL_reg_addr                                                         "0xD801A400"
#define SB2_PC_CTRL_reg                                                              0xD801A400
#define set_SB2_PC_CTRL_reg(data)   (*((volatile unsigned int*) SB2_PC_CTRL_reg)=data)
#define get_SB2_PC_CTRL_reg   (*((volatile unsigned int*) SB2_PC_CTRL_reg))
#define SB2_PC_CTRL_inst_adr                                                         "0x0000"
#define SB2_PC_CTRL_inst                                                             0x0000
#define SB2_PC_CTRL_write_en6_shift                                                  (11)
#define SB2_PC_CTRL_write_en6_mask                                                   (0x00000800)
#define SB2_PC_CTRL_write_en6(data)                                                  (0x00000800&((data)<<11))
#define SB2_PC_CTRL_write_en6_src(data)                                              ((0x00000800&(data))>>11)
#define SB2_PC_CTRL_get_write_en6(data)                                              ((0x00000800&(data))>>11)
#define SB2_PC_CTRL_acpu_rbus_go_shift                                               (10)
#define SB2_PC_CTRL_acpu_rbus_go_mask                                                (0x00000400)
#define SB2_PC_CTRL_acpu_rbus_go(data)                                               (0x00000400&((data)<<10))
#define SB2_PC_CTRL_acpu_rbus_go_src(data)                                           ((0x00000400&(data))>>10)
#define SB2_PC_CTRL_get_acpu_rbus_go(data)                                           ((0x00000400&(data))>>10)
#define SB2_PC_CTRL_write_en4_shift                                                  (7)
#define SB2_PC_CTRL_write_en4_mask                                                   (0x00000080)
#define SB2_PC_CTRL_write_en4(data)                                                  (0x00000080&((data)<<7))
#define SB2_PC_CTRL_write_en4_src(data)                                              ((0x00000080&(data))>>7)
#define SB2_PC_CTRL_get_write_en4(data)                                              ((0x00000080&(data))>>7)
#define SB2_PC_CTRL_scpu_rbus_go_shift                                               (6)
#define SB2_PC_CTRL_scpu_rbus_go_mask                                                (0x00000040)
#define SB2_PC_CTRL_scpu_rbus_go(data)                                               (0x00000040&((data)<<6))
#define SB2_PC_CTRL_scpu_rbus_go_src(data)                                           ((0x00000040&(data))>>6)
#define SB2_PC_CTRL_get_scpu_rbus_go(data)                                           ((0x00000040&(data))>>6)
#define SB2_PC_CTRL_write_en3_shift                                                  (5)
#define SB2_PC_CTRL_write_en3_mask                                                   (0x00000020)
#define SB2_PC_CTRL_write_en3(data)                                                  (0x00000020&((data)<<5))
#define SB2_PC_CTRL_write_en3_src(data)                                              ((0x00000020&(data))>>5)
#define SB2_PC_CTRL_get_write_en3(data)                                              ((0x00000020&(data))>>5)
#define SB2_PC_CTRL_acpu_dbus_go_shift                                               (4)
#define SB2_PC_CTRL_acpu_dbus_go_mask                                                (0x00000010)
#define SB2_PC_CTRL_acpu_dbus_go(data)                                               (0x00000010&((data)<<4))
#define SB2_PC_CTRL_acpu_dbus_go_src(data)                                           ((0x00000010&(data))>>4)
#define SB2_PC_CTRL_get_acpu_dbus_go(data)                                           ((0x00000010&(data))>>4)


#define SB2_ACPU_DACC                                                                0x9801A42C
#define SB2_ACPU_DACC_reg_addr                                                       "0xD801A42C"
#define SB2_ACPU_DACC_reg                                                            0xD801A42C
#define set_SB2_ACPU_DACC_reg(data)   (*((volatile unsigned int*) SB2_ACPU_DACC_reg)=data)
#define get_SB2_ACPU_DACC_reg   (*((volatile unsigned int*) SB2_ACPU_DACC_reg))
#define SB2_ACPU_DACC_inst_adr                                                       "0x000B"
#define SB2_ACPU_DACC_inst                                                           0x000B
#define SB2_ACPU_DACC_acpu_dbus_acc_shift                                            (0)
#define SB2_ACPU_DACC_acpu_dbus_acc_mask                                             (0xFFFFFFFF)
#define SB2_ACPU_DACC_acpu_dbus_acc(data)                                            (0xFFFFFFFF&((data)<<0))
#define SB2_ACPU_DACC_acpu_dbus_acc_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define SB2_ACPU_DACC_get_acpu_dbus_acc(data)                                        ((0xFFFFFFFF&(data))>>0)


#define SB2_ACPU_DREQ_NUM                                                            0x9801A430
#define SB2_ACPU_DREQ_NUM_reg_addr                                                   "0xD801A430"
#define SB2_ACPU_DREQ_NUM_reg                                                        0xD801A430
#define set_SB2_ACPU_DREQ_NUM_reg(data)   (*((volatile unsigned int*) SB2_ACPU_DREQ_NUM_reg)=data)
#define get_SB2_ACPU_DREQ_NUM_reg   (*((volatile unsigned int*) SB2_ACPU_DREQ_NUM_reg))
#define SB2_ACPU_DREQ_NUM_inst_adr                                                   "0x000C"
#define SB2_ACPU_DREQ_NUM_inst                                                       0x000C
#define SB2_ACPU_DREQ_NUM_acpu_dreq_num_shift                                        (0)
#define SB2_ACPU_DREQ_NUM_acpu_dreq_num_mask                                         (0x00FFFFFF)
#define SB2_ACPU_DREQ_NUM_acpu_dreq_num(data)                                        (0x00FFFFFF&((data)<<0))
#define SB2_ACPU_DREQ_NUM_acpu_dreq_num_src(data)                                    ((0x00FFFFFF&(data))>>0)
#define SB2_ACPU_DREQ_NUM_get_acpu_dreq_num(data)                                    ((0x00FFFFFF&(data))>>0)


#define SB2_ACPU_DREQ_MAX                                                            0x9801A434
#define SB2_ACPU_DREQ_MAX_reg_addr                                                   "0xD801A434"
#define SB2_ACPU_DREQ_MAX_reg                                                        0xD801A434
#define set_SB2_ACPU_DREQ_MAX_reg(data)   (*((volatile unsigned int*) SB2_ACPU_DREQ_MAX_reg)=data)
#define get_SB2_ACPU_DREQ_MAX_reg   (*((volatile unsigned int*) SB2_ACPU_DREQ_MAX_reg))
#define SB2_ACPU_DREQ_MAX_inst_adr                                                   "0x000D"
#define SB2_ACPU_DREQ_MAX_inst                                                       0x000D
#define SB2_ACPU_DREQ_MAX_acpu_dreq_max_shift                                        (0)
#define SB2_ACPU_DREQ_MAX_acpu_dreq_max_mask                                         (0x0000FFFF)
#define SB2_ACPU_DREQ_MAX_acpu_dreq_max(data)                                        (0x0000FFFF&((data)<<0))
#define SB2_ACPU_DREQ_MAX_acpu_dreq_max_src(data)                                    ((0x0000FFFF&(data))>>0)
#define SB2_ACPU_DREQ_MAX_get_acpu_dreq_max(data)                                    ((0x0000FFFF&(data))>>0)


#define SB2_ACPU_DREQ_ACK                                                            0x9801A438
#define SB2_ACPU_DREQ_ACK_reg_addr                                                   "0xD801A438"
#define SB2_ACPU_DREQ_ACK_reg                                                        0xD801A438
#define set_SB2_ACPU_DREQ_ACK_reg(data)   (*((volatile unsigned int*) SB2_ACPU_DREQ_ACK_reg)=data)
#define get_SB2_ACPU_DREQ_ACK_reg   (*((volatile unsigned int*) SB2_ACPU_DREQ_ACK_reg))
#define SB2_ACPU_DREQ_ACK_inst_adr                                                   "0x000E"
#define SB2_ACPU_DREQ_ACK_inst                                                       0x000E
#define SB2_ACPU_DREQ_ACK_acpu_dreq_ack_shift                                        (0)
#define SB2_ACPU_DREQ_ACK_acpu_dreq_ack_mask                                         (0x03FFFFFF)
#define SB2_ACPU_DREQ_ACK_acpu_dreq_ack(data)                                        (0x03FFFFFF&((data)<<0))
#define SB2_ACPU_DREQ_ACK_acpu_dreq_ack_src(data)                                    ((0x03FFFFFF&(data))>>0)
#define SB2_ACPU_DREQ_ACK_get_acpu_dreq_ack(data)                                    ((0x03FFFFFF&(data))>>0)


#define SB2_SCPU_RACC                                                                0x9801A440
#define SB2_SCPU_RACC_reg_addr                                                       "0xD801A440"
#define SB2_SCPU_RACC_reg                                                            0xD801A440
#define set_SB2_SCPU_RACC_reg(data)   (*((volatile unsigned int*) SB2_SCPU_RACC_reg)=data)
#define get_SB2_SCPU_RACC_reg   (*((volatile unsigned int*) SB2_SCPU_RACC_reg))
#define SB2_SCPU_RACC_inst_adr                                                       "0x0010"
#define SB2_SCPU_RACC_inst                                                           0x0010
#define SB2_SCPU_RACC_scpu_rbus_acc_shift                                            (0)
#define SB2_SCPU_RACC_scpu_rbus_acc_mask                                             (0xFFFFFFFF)
#define SB2_SCPU_RACC_scpu_rbus_acc(data)                                            (0xFFFFFFFF&((data)<<0))
#define SB2_SCPU_RACC_scpu_rbus_acc_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define SB2_SCPU_RACC_get_scpu_rbus_acc(data)                                        ((0xFFFFFFFF&(data))>>0)


#define SB2_SCPU_RREQ_RLT                                                            0x9801A444
#define SB2_SCPU_RREQ_RLT_reg_addr                                                   "0xD801A444"
#define SB2_SCPU_RREQ_RLT_reg                                                        0xD801A444
#define set_SB2_SCPU_RREQ_RLT_reg(data)   (*((volatile unsigned int*) SB2_SCPU_RREQ_RLT_reg)=data)
#define get_SB2_SCPU_RREQ_RLT_reg   (*((volatile unsigned int*) SB2_SCPU_RREQ_RLT_reg))
#define SB2_SCPU_RREQ_RLT_inst_adr                                                   "0x0011"
#define SB2_SCPU_RREQ_RLT_inst                                                       0x0011
#define SB2_SCPU_RREQ_RLT_scpu_rreq_max_shift                                        (24)
#define SB2_SCPU_RREQ_RLT_scpu_rreq_max_mask                                         (0xFF000000)
#define SB2_SCPU_RREQ_RLT_scpu_rreq_max(data)                                        (0xFF000000&((data)<<24))
#define SB2_SCPU_RREQ_RLT_scpu_rreq_max_src(data)                                    ((0xFF000000&(data))>>24)
#define SB2_SCPU_RREQ_RLT_get_scpu_rreq_max(data)                                    ((0xFF000000&(data))>>24)
#define SB2_SCPU_RREQ_RLT_scpu_rreq_num_shift                                        (0)
#define SB2_SCPU_RREQ_RLT_scpu_rreq_num_mask                                         (0x00FFFFFF)
#define SB2_SCPU_RREQ_RLT_scpu_rreq_num(data)                                        (0x00FFFFFF&((data)<<0))
#define SB2_SCPU_RREQ_RLT_scpu_rreq_num_src(data)                                    ((0x00FFFFFF&(data))>>0)
#define SB2_SCPU_RREQ_RLT_get_scpu_rreq_num(data)                                    ((0x00FFFFFF&(data))>>0)


#define SB2_ACPU_RACC                                                                0x9801A450
#define SB2_ACPU_RACC_reg_addr                                                       "0xD801A450"
#define SB2_ACPU_RACC_reg                                                            0xD801A450
#define set_SB2_ACPU_RACC_reg(data)   (*((volatile unsigned int*) SB2_ACPU_RACC_reg)=data)
#define get_SB2_ACPU_RACC_reg   (*((volatile unsigned int*) SB2_ACPU_RACC_reg))
#define SB2_ACPU_RACC_inst_adr                                                       "0x0014"
#define SB2_ACPU_RACC_inst                                                           0x0014
#define SB2_ACPU_RACC_acpu_rbus_acc_shift                                            (0)
#define SB2_ACPU_RACC_acpu_rbus_acc_mask                                             (0xFFFFFFFF)
#define SB2_ACPU_RACC_acpu_rbus_acc(data)                                            (0xFFFFFFFF&((data)<<0))
#define SB2_ACPU_RACC_acpu_rbus_acc_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define SB2_ACPU_RACC_get_acpu_rbus_acc(data)                                        ((0xFFFFFFFF&(data))>>0)


#define SB2_ACPU_RREQ_RLT                                                            0x9801A454
#define SB2_ACPU_RREQ_RLT_reg_addr                                                   "0xD801A454"
#define SB2_ACPU_RREQ_RLT_reg                                                        0xD801A454
#define set_SB2_ACPU_RREQ_RLT_reg(data)   (*((volatile unsigned int*) SB2_ACPU_RREQ_RLT_reg)=data)
#define get_SB2_ACPU_RREQ_RLT_reg   (*((volatile unsigned int*) SB2_ACPU_RREQ_RLT_reg))
#define SB2_ACPU_RREQ_RLT_inst_adr                                                   "0x0015"
#define SB2_ACPU_RREQ_RLT_inst                                                       0x0015
#define SB2_ACPU_RREQ_RLT_acpu_rreq_max_shift                                        (24)
#define SB2_ACPU_RREQ_RLT_acpu_rreq_max_mask                                         (0xFF000000)
#define SB2_ACPU_RREQ_RLT_acpu_rreq_max(data)                                        (0xFF000000&((data)<<24))
#define SB2_ACPU_RREQ_RLT_acpu_rreq_max_src(data)                                    ((0xFF000000&(data))>>24)
#define SB2_ACPU_RREQ_RLT_get_acpu_rreq_max(data)                                    ((0xFF000000&(data))>>24)
#define SB2_ACPU_RREQ_RLT_acpu_rreq_num_shift                                        (0)
#define SB2_ACPU_RREQ_RLT_acpu_rreq_num_mask                                         (0x00FFFFFF)
#define SB2_ACPU_RREQ_RLT_acpu_rreq_num(data)                                        (0x00FFFFFF&((data)<<0))
#define SB2_ACPU_RREQ_RLT_acpu_rreq_num_src(data)                                    ((0x00FFFFFF&(data))>>0)
#define SB2_ACPU_RREQ_RLT_get_acpu_rreq_num(data)                                    ((0x00FFFFFF&(data))>>0)


#define SB2_DBG_START_0                                                              0x9801A458
#define SB2_DBG_START_1                                                              0x9801A45C
#define SB2_DBG_START_2                                                              0x9801A460
#define SB2_DBG_START_3                                                              0x9801A464
#define SB2_DBG_START_4                                                              0x9801A468
#define SB2_DBG_START_5                                                              0x9801A46C
#define SB2_DBG_START_6                                                              0x9801A470
#define SB2_DBG_START_7                                                              0x9801A474
#define SB2_DBG_START_0_reg_addr                                                     "0xD801A458"
#define SB2_DBG_START_1_reg_addr                                                     "0xD801A45C"
#define SB2_DBG_START_2_reg_addr                                                     "0xD801A460"
#define SB2_DBG_START_3_reg_addr                                                     "0xD801A464"
#define SB2_DBG_START_4_reg_addr                                                     "0xD801A468"
#define SB2_DBG_START_5_reg_addr                                                     "0xD801A46C"
#define SB2_DBG_START_6_reg_addr                                                     "0xD801A470"
#define SB2_DBG_START_7_reg_addr                                                     "0xD801A474"
#define SB2_DBG_START_0_reg                                                          0xD801A458
#define SB2_DBG_START_1_reg                                                          0xD801A45C
#define SB2_DBG_START_2_reg                                                          0xD801A460
#define SB2_DBG_START_3_reg                                                          0xD801A464
#define SB2_DBG_START_4_reg                                                          0xD801A468
#define SB2_DBG_START_5_reg                                                          0xD801A46C
#define SB2_DBG_START_6_reg                                                          0xD801A470
#define SB2_DBG_START_7_reg                                                          0xD801A474
#define set_SB2_DBG_START_0_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_0_reg)=data)
#define set_SB2_DBG_START_1_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_1_reg)=data)
#define set_SB2_DBG_START_2_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_2_reg)=data)
#define set_SB2_DBG_START_3_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_3_reg)=data)
#define set_SB2_DBG_START_4_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_4_reg)=data)
#define set_SB2_DBG_START_5_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_5_reg)=data)
#define set_SB2_DBG_START_6_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_6_reg)=data)
#define set_SB2_DBG_START_7_reg(data)   (*((volatile unsigned int*) SB2_DBG_START_7_reg)=data)
#define get_SB2_DBG_START_0_reg   (*((volatile unsigned int*) SB2_DBG_START_0_reg))
#define get_SB2_DBG_START_1_reg   (*((volatile unsigned int*) SB2_DBG_START_1_reg))
#define get_SB2_DBG_START_2_reg   (*((volatile unsigned int*) SB2_DBG_START_2_reg))
#define get_SB2_DBG_START_3_reg   (*((volatile unsigned int*) SB2_DBG_START_3_reg))
#define get_SB2_DBG_START_4_reg   (*((volatile unsigned int*) SB2_DBG_START_4_reg))
#define get_SB2_DBG_START_5_reg   (*((volatile unsigned int*) SB2_DBG_START_5_reg))
#define get_SB2_DBG_START_6_reg   (*((volatile unsigned int*) SB2_DBG_START_6_reg))
#define get_SB2_DBG_START_7_reg   (*((volatile unsigned int*) SB2_DBG_START_7_reg))
#define SB2_DBG_START_0_inst_adr                                                     "0x0016"
#define SB2_DBG_START_1_inst_adr                                                     "0x0017"
#define SB2_DBG_START_2_inst_adr                                                     "0x0018"
#define SB2_DBG_START_3_inst_adr                                                     "0x0019"
#define SB2_DBG_START_4_inst_adr                                                     "0x001A"
#define SB2_DBG_START_5_inst_adr                                                     "0x001B"
#define SB2_DBG_START_6_inst_adr                                                     "0x001C"
#define SB2_DBG_START_7_inst_adr                                                     "0x001D"
#define SB2_DBG_START_0_inst                                                         0x0016
#define SB2_DBG_START_1_inst                                                         0x0017
#define SB2_DBG_START_2_inst                                                         0x0018
#define SB2_DBG_START_3_inst                                                         0x0019
#define SB2_DBG_START_4_inst                                                         0x001A
#define SB2_DBG_START_5_inst                                                         0x001B
#define SB2_DBG_START_6_inst                                                         0x001C
#define SB2_DBG_START_7_inst                                                         0x001D
#define SB2_DBG_START_Dbg_start_addr_shift                                           (0)
#define SB2_DBG_START_Dbg_start_addr_mask                                            (0xFFFFFFFF)
#define SB2_DBG_START_Dbg_start_addr(data)                                           (0xFFFFFFFF&((data)<<0))
#define SB2_DBG_START_Dbg_start_addr_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define SB2_DBG_START_get_Dbg_start_addr(data)                                       ((0xFFFFFFFF&(data))>>0)


#define SB2_DBG_END_0                                                                0x9801A478
#define SB2_DBG_END_1                                                                0x9801A47C
#define SB2_DBG_END_2                                                                0x9801A480
#define SB2_DBG_END_3                                                                0x9801A484
#define SB2_DBG_END_4                                                                0x9801A488
#define SB2_DBG_END_5                                                                0x9801A48C
#define SB2_DBG_END_6                                                                0x9801A490
#define SB2_DBG_END_7                                                                0x9801A494
#define SB2_DBG_END_0_reg_addr                                                       "0xD801A478"
#define SB2_DBG_END_1_reg_addr                                                       "0xD801A47C"
#define SB2_DBG_END_2_reg_addr                                                       "0xD801A480"
#define SB2_DBG_END_3_reg_addr                                                       "0xD801A484"
#define SB2_DBG_END_4_reg_addr                                                       "0xD801A488"
#define SB2_DBG_END_5_reg_addr                                                       "0xD801A48C"
#define SB2_DBG_END_6_reg_addr                                                       "0xD801A490"
#define SB2_DBG_END_7_reg_addr                                                       "0xD801A494"
#define SB2_DBG_END_0_reg                                                            0xD801A478
#define SB2_DBG_END_1_reg                                                            0xD801A47C
#define SB2_DBG_END_2_reg                                                            0xD801A480
#define SB2_DBG_END_3_reg                                                            0xD801A484
#define SB2_DBG_END_4_reg                                                            0xD801A488
#define SB2_DBG_END_5_reg                                                            0xD801A48C
#define SB2_DBG_END_6_reg                                                            0xD801A490
#define SB2_DBG_END_7_reg                                                            0xD801A494
#define set_SB2_DBG_END_0_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_0_reg)=data)
#define set_SB2_DBG_END_1_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_1_reg)=data)
#define set_SB2_DBG_END_2_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_2_reg)=data)
#define set_SB2_DBG_END_3_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_3_reg)=data)
#define set_SB2_DBG_END_4_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_4_reg)=data)
#define set_SB2_DBG_END_5_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_5_reg)=data)
#define set_SB2_DBG_END_6_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_6_reg)=data)
#define set_SB2_DBG_END_7_reg(data)   (*((volatile unsigned int*) SB2_DBG_END_7_reg)=data)
#define get_SB2_DBG_END_0_reg   (*((volatile unsigned int*) SB2_DBG_END_0_reg))
#define get_SB2_DBG_END_1_reg   (*((volatile unsigned int*) SB2_DBG_END_1_reg))
#define get_SB2_DBG_END_2_reg   (*((volatile unsigned int*) SB2_DBG_END_2_reg))
#define get_SB2_DBG_END_3_reg   (*((volatile unsigned int*) SB2_DBG_END_3_reg))
#define get_SB2_DBG_END_4_reg   (*((volatile unsigned int*) SB2_DBG_END_4_reg))
#define get_SB2_DBG_END_5_reg   (*((volatile unsigned int*) SB2_DBG_END_5_reg))
#define get_SB2_DBG_END_6_reg   (*((volatile unsigned int*) SB2_DBG_END_6_reg))
#define get_SB2_DBG_END_7_reg   (*((volatile unsigned int*) SB2_DBG_END_7_reg))
#define SB2_DBG_END_0_inst_adr                                                       "0x001E"
#define SB2_DBG_END_1_inst_adr                                                       "0x001F"
#define SB2_DBG_END_2_inst_adr                                                       "0x0020"
#define SB2_DBG_END_3_inst_adr                                                       "0x0021"
#define SB2_DBG_END_4_inst_adr                                                       "0x0022"
#define SB2_DBG_END_5_inst_adr                                                       "0x0023"
#define SB2_DBG_END_6_inst_adr                                                       "0x0024"
#define SB2_DBG_END_7_inst_adr                                                       "0x0025"
#define SB2_DBG_END_0_inst                                                           0x001E
#define SB2_DBG_END_1_inst                                                           0x001F
#define SB2_DBG_END_2_inst                                                           0x0020
#define SB2_DBG_END_3_inst                                                           0x0021
#define SB2_DBG_END_4_inst                                                           0x0022
#define SB2_DBG_END_5_inst                                                           0x0023
#define SB2_DBG_END_6_inst                                                           0x0024
#define SB2_DBG_END_7_inst                                                           0x0025
#define SB2_DBG_END_Dbg_end_addr_shift                                               (0)
#define SB2_DBG_END_Dbg_end_addr_mask                                                (0xFFFFFFFF)
#define SB2_DBG_END_Dbg_end_addr(data)                                               (0xFFFFFFFF&((data)<<0))
#define SB2_DBG_END_Dbg_end_addr_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SB2_DBG_END_get_Dbg_end_addr(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SB2_DBG_CTRL_0                                                               0x9801A498
#define SB2_DBG_CTRL_1                                                               0x9801A49C
#define SB2_DBG_CTRL_2                                                               0x9801A4A0
#define SB2_DBG_CTRL_3                                                               0x9801A4A4
#define SB2_DBG_CTRL_4                                                               0x9801A4A8
#define SB2_DBG_CTRL_5                                                               0x9801A4AC
#define SB2_DBG_CTRL_6                                                               0x9801A4B0
#define SB2_DBG_CTRL_7                                                               0x9801A4B4
#define SB2_DBG_CTRL_0_reg_addr                                                      "0xD801A498"
#define SB2_DBG_CTRL_1_reg_addr                                                      "0xD801A49C"
#define SB2_DBG_CTRL_2_reg_addr                                                      "0xD801A4A0"
#define SB2_DBG_CTRL_3_reg_addr                                                      "0xD801A4A4"
#define SB2_DBG_CTRL_4_reg_addr                                                      "0xD801A4A8"
#define SB2_DBG_CTRL_5_reg_addr                                                      "0xD801A4AC"
#define SB2_DBG_CTRL_6_reg_addr                                                      "0xD801A4B0"
#define SB2_DBG_CTRL_7_reg_addr                                                      "0xD801A4B4"
#define SB2_DBG_CTRL_0_reg                                                           0xD801A498
#define SB2_DBG_CTRL_1_reg                                                           0xD801A49C
#define SB2_DBG_CTRL_2_reg                                                           0xD801A4A0
#define SB2_DBG_CTRL_3_reg                                                           0xD801A4A4
#define SB2_DBG_CTRL_4_reg                                                           0xD801A4A8
#define SB2_DBG_CTRL_5_reg                                                           0xD801A4AC
#define SB2_DBG_CTRL_6_reg                                                           0xD801A4B0
#define SB2_DBG_CTRL_7_reg                                                           0xD801A4B4
#define set_SB2_DBG_CTRL_0_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_0_reg)=data)
#define set_SB2_DBG_CTRL_1_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_1_reg)=data)
#define set_SB2_DBG_CTRL_2_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_2_reg)=data)
#define set_SB2_DBG_CTRL_3_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_3_reg)=data)
#define set_SB2_DBG_CTRL_4_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_4_reg)=data)
#define set_SB2_DBG_CTRL_5_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_5_reg)=data)
#define set_SB2_DBG_CTRL_6_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_6_reg)=data)
#define set_SB2_DBG_CTRL_7_reg(data)   (*((volatile unsigned int*) SB2_DBG_CTRL_7_reg)=data)
#define get_SB2_DBG_CTRL_0_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_0_reg))
#define get_SB2_DBG_CTRL_1_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_1_reg))
#define get_SB2_DBG_CTRL_2_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_2_reg))
#define get_SB2_DBG_CTRL_3_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_3_reg))
#define get_SB2_DBG_CTRL_4_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_4_reg))
#define get_SB2_DBG_CTRL_5_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_5_reg))
#define get_SB2_DBG_CTRL_6_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_6_reg))
#define get_SB2_DBG_CTRL_7_reg   (*((volatile unsigned int*) SB2_DBG_CTRL_7_reg))
#define SB2_DBG_CTRL_0_inst_adr                                                      "0x0026"
#define SB2_DBG_CTRL_1_inst_adr                                                      "0x0027"
#define SB2_DBG_CTRL_2_inst_adr                                                      "0x0028"
#define SB2_DBG_CTRL_3_inst_adr                                                      "0x0029"
#define SB2_DBG_CTRL_4_inst_adr                                                      "0x002A"
#define SB2_DBG_CTRL_5_inst_adr                                                      "0x002B"
#define SB2_DBG_CTRL_6_inst_adr                                                      "0x002C"
#define SB2_DBG_CTRL_7_inst_adr                                                      "0x002D"
#define SB2_DBG_CTRL_0_inst                                                          0x0026
#define SB2_DBG_CTRL_1_inst                                                          0x0027
#define SB2_DBG_CTRL_2_inst                                                          0x0028
#define SB2_DBG_CTRL_3_inst                                                          0x0029
#define SB2_DBG_CTRL_4_inst                                                          0x002A
#define SB2_DBG_CTRL_5_inst                                                          0x002B
#define SB2_DBG_CTRL_6_inst                                                          0x002C
#define SB2_DBG_CTRL_7_inst                                                          0x002D
#define SB2_DBG_CTRL_write_en6_shift                                                 (13)
#define SB2_DBG_CTRL_write_en6_mask                                                  (0x00002000)
#define SB2_DBG_CTRL_write_en6(data)                                                 (0x00002000&((data)<<13))
#define SB2_DBG_CTRL_write_en6_src(data)                                             ((0x00002000&(data))>>13)
#define SB2_DBG_CTRL_get_write_en6(data)                                             ((0x00002000&(data))>>13)
#define SB2_DBG_CTRL_Dbg_acpu_chk_en_shift                                           (12)
#define SB2_DBG_CTRL_Dbg_acpu_chk_en_mask                                            (0x00001000)
#define SB2_DBG_CTRL_Dbg_acpu_chk_en(data)                                           (0x00001000&((data)<<12))
#define SB2_DBG_CTRL_Dbg_acpu_chk_en_src(data)                                       ((0x00001000&(data))>>12)
#define SB2_DBG_CTRL_get_Dbg_acpu_chk_en(data)                                       ((0x00001000&(data))>>12)
#define SB2_DBG_CTRL_write_en4_shift                                                 (9)
#define SB2_DBG_CTRL_write_en4_mask                                                  (0x00000200)
#define SB2_DBG_CTRL_write_en4(data)                                                 (0x00000200&((data)<<9))
#define SB2_DBG_CTRL_write_en4_src(data)                                             ((0x00000200&(data))>>9)
#define SB2_DBG_CTRL_get_write_en4(data)                                             ((0x00000200&(data))>>9)
#define SB2_DBG_CTRL_Dbg_scpu_chk_en_shift                                           (8)
#define SB2_DBG_CTRL_Dbg_scpu_chk_en_mask                                            (0x00000100)
#define SB2_DBG_CTRL_Dbg_scpu_chk_en(data)                                           (0x00000100&((data)<<8))
#define SB2_DBG_CTRL_Dbg_scpu_chk_en_src(data)                                       ((0x00000100&(data))>>8)
#define SB2_DBG_CTRL_get_Dbg_scpu_chk_en(data)                                       ((0x00000100&(data))>>8)
#define SB2_DBG_CTRL_write_en3_shift                                                 (7)
#define SB2_DBG_CTRL_write_en3_mask                                                  (0x00000080)
#define SB2_DBG_CTRL_write_en3(data)                                                 (0x00000080&((data)<<7))
#define SB2_DBG_CTRL_write_en3_src(data)                                             ((0x00000080&(data))>>7)
#define SB2_DBG_CTRL_get_write_en3(data)                                             ((0x00000080&(data))>>7)
#define SB2_DBG_CTRL_Dbg_wr_chk_shift                                                (5)
#define SB2_DBG_CTRL_Dbg_wr_chk_mask                                                 (0x00000060)
#define SB2_DBG_CTRL_Dbg_wr_chk(data)                                                (0x00000060&((data)<<5))
#define SB2_DBG_CTRL_Dbg_wr_chk_src(data)                                            ((0x00000060&(data))>>5)
#define SB2_DBG_CTRL_get_Dbg_wr_chk(data)                                            ((0x00000060&(data))>>5)
#define SB2_DBG_CTRL_write_en2_shift                                                 (4)
#define SB2_DBG_CTRL_write_en2_mask                                                  (0x00000010)
#define SB2_DBG_CTRL_write_en2(data)                                                 (0x00000010&((data)<<4))
#define SB2_DBG_CTRL_write_en2_src(data)                                             ((0x00000010&(data))>>4)
#define SB2_DBG_CTRL_get_write_en2(data)                                             ((0x00000010&(data))>>4)
#define SB2_DBG_CTRL_Dbg_id_chk_shift                                                (2)
#define SB2_DBG_CTRL_Dbg_id_chk_mask                                                 (0x0000000C)
#define SB2_DBG_CTRL_Dbg_id_chk(data)                                                (0x0000000C&((data)<<2))
#define SB2_DBG_CTRL_Dbg_id_chk_src(data)                                            ((0x0000000C&(data))>>2)
#define SB2_DBG_CTRL_get_Dbg_id_chk(data)                                            ((0x0000000C&(data))>>2)
#define SB2_DBG_CTRL_write_en1_shift                                                 (1)
#define SB2_DBG_CTRL_write_en1_mask                                                  (0x00000002)
#define SB2_DBG_CTRL_write_en1(data)                                                 (0x00000002&((data)<<1))
#define SB2_DBG_CTRL_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define SB2_DBG_CTRL_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define SB2_DBG_CTRL_Dbg_en_shift                                                    (0)
#define SB2_DBG_CTRL_Dbg_en_mask                                                     (0x00000001)
#define SB2_DBG_CTRL_Dbg_en(data)                                                    (0x00000001&((data)<<0))
#define SB2_DBG_CTRL_Dbg_en_src(data)                                                ((0x00000001&(data))>>0)
#define SB2_DBG_CTRL_get_Dbg_en(data)                                                ((0x00000001&(data))>>0)


#define SB2_DBG_ADDR_0                                                               0x9801A4B8
#define SB2_DBG_ADDR_1                                                               0x9801A4BC
#define SB2_DBG_ADDR_2                                                               0x9801A4C0
#define SB2_DBG_ADDR_0_reg_addr                                                      "0xD801A4B8"
#define SB2_DBG_ADDR_1_reg_addr                                                      "0xD801A4BC"
#define SB2_DBG_ADDR_2_reg_addr                                                      "0xD801A4C0"
#define SB2_DBG_ADDR_0_reg                                                           0xD801A4B8
#define SB2_DBG_ADDR_1_reg                                                           0xD801A4BC
#define SB2_DBG_ADDR_2_reg                                                           0xD801A4C0
#define set_SB2_DBG_ADDR_0_reg(data)   (*((volatile unsigned int*) SB2_DBG_ADDR_0_reg)=data)
#define set_SB2_DBG_ADDR_1_reg(data)   (*((volatile unsigned int*) SB2_DBG_ADDR_1_reg)=data)
#define set_SB2_DBG_ADDR_2_reg(data)   (*((volatile unsigned int*) SB2_DBG_ADDR_2_reg)=data)
#define get_SB2_DBG_ADDR_0_reg   (*((volatile unsigned int*) SB2_DBG_ADDR_0_reg))
#define get_SB2_DBG_ADDR_1_reg   (*((volatile unsigned int*) SB2_DBG_ADDR_1_reg))
#define get_SB2_DBG_ADDR_2_reg   (*((volatile unsigned int*) SB2_DBG_ADDR_2_reg))
#define SB2_DBG_ADDR_0_inst_adr                                                      "0x002E"
#define SB2_DBG_ADDR_1_inst_adr                                                      "0x002F"
#define SB2_DBG_ADDR_2_inst_adr                                                      "0x0030"
#define SB2_DBG_ADDR_0_inst                                                          0x002E
#define SB2_DBG_ADDR_1_inst                                                          0x002F
#define SB2_DBG_ADDR_2_inst                                                          0x0030
#define SB2_DBG_ADDR_dbg_addr_shift                                                  (0)
#define SB2_DBG_ADDR_dbg_addr_mask                                                   (0xFFFFFFFF)
#define SB2_DBG_ADDR_dbg_addr(data)                                                  (0xFFFFFFFF&((data)<<0))
#define SB2_DBG_ADDR_dbg_addr_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define SB2_DBG_ADDR_get_dbg_addr(data)                                              ((0xFFFFFFFF&(data))>>0)


#define SB2_DBG_ADDR1                                                                0x9801A4C8
#define SB2_DBG_ADDR1_reg_addr                                                       "0xD801A4C8"
#define SB2_DBG_ADDR1_reg                                                            0xD801A4C8
#define set_SB2_DBG_ADDR1_reg(data)   (*((volatile unsigned int*) SB2_DBG_ADDR1_reg)=data)
#define get_SB2_DBG_ADDR1_reg   (*((volatile unsigned int*) SB2_DBG_ADDR1_reg))
#define SB2_DBG_ADDR1_inst_adr                                                       "0x0032"
#define SB2_DBG_ADDR1_inst                                                           0x0032
#define SB2_DBG_ADDR1_acpu_dbg_write_shift                                           (5)
#define SB2_DBG_ADDR1_acpu_dbg_write_mask                                            (0x00000020)
#define SB2_DBG_ADDR1_acpu_dbg_write(data)                                           (0x00000020&((data)<<5))
#define SB2_DBG_ADDR1_acpu_dbg_write_src(data)                                       ((0x00000020&(data))>>5)
#define SB2_DBG_ADDR1_get_acpu_dbg_write(data)                                       ((0x00000020&(data))>>5)
#define SB2_DBG_ADDR1_acpu_dbg_dacc_shift                                            (4)
#define SB2_DBG_ADDR1_acpu_dbg_dacc_mask                                             (0x00000010)
#define SB2_DBG_ADDR1_acpu_dbg_dacc(data)                                            (0x00000010&((data)<<4))
#define SB2_DBG_ADDR1_acpu_dbg_dacc_src(data)                                        ((0x00000010&(data))>>4)
#define SB2_DBG_ADDR1_get_acpu_dbg_dacc(data)                                        ((0x00000010&(data))>>4)
#define SB2_DBG_ADDR1_scpu_dbg_write_shift                                           (3)
#define SB2_DBG_ADDR1_scpu_dbg_write_mask                                            (0x00000008)
#define SB2_DBG_ADDR1_scpu_dbg_write(data)                                           (0x00000008&((data)<<3))
#define SB2_DBG_ADDR1_scpu_dbg_write_src(data)                                       ((0x00000008&(data))>>3)
#define SB2_DBG_ADDR1_get_scpu_dbg_write(data)                                       ((0x00000008&(data))>>3)
#define SB2_DBG_ADDR1_scpu_dbg_dacc_shift                                            (2)
#define SB2_DBG_ADDR1_scpu_dbg_dacc_mask                                             (0x00000004)
#define SB2_DBG_ADDR1_scpu_dbg_dacc(data)                                            (0x00000004&((data)<<2))
#define SB2_DBG_ADDR1_scpu_dbg_dacc_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_DBG_ADDR1_get_scpu_dbg_dacc(data)                                        ((0x00000004&(data))>>2)


#define SB2_DBG_INT                                                                  0x9801A4E0
#define SB2_DBG_INT_reg_addr                                                         "0xD801A4E0"
#define SB2_DBG_INT_reg                                                              0xD801A4E0
#define set_SB2_DBG_INT_reg(data)   (*((volatile unsigned int*) SB2_DBG_INT_reg)=data)
#define get_SB2_DBG_INT_reg   (*((volatile unsigned int*) SB2_DBG_INT_reg))
#define SB2_DBG_INT_inst_adr                                                         "0x0038"
#define SB2_DBG_INT_inst                                                             0x0038
#define SB2_DBG_INT_acpu_int_shift                                                   (12)
#define SB2_DBG_INT_acpu_int_mask                                                    (0x00001000)
#define SB2_DBG_INT_acpu_int(data)                                                   (0x00001000&((data)<<12))
#define SB2_DBG_INT_acpu_int_src(data)                                               ((0x00001000&(data))>>12)
#define SB2_DBG_INT_get_acpu_int(data)                                               ((0x00001000&(data))>>12)
#define SB2_DBG_INT_scpu_int_shift                                                   (10)
#define SB2_DBG_INT_scpu_int_mask                                                    (0x00000400)
#define SB2_DBG_INT_scpu_int(data)                                                   (0x00000400&((data)<<10))
#define SB2_DBG_INT_scpu_int_src(data)                                               ((0x00000400&(data))>>10)
#define SB2_DBG_INT_get_scpu_int(data)                                               ((0x00000400&(data))>>10)
#define SB2_DBG_INT_acpu_int_en_shift                                                (9)
#define SB2_DBG_INT_acpu_int_en_mask                                                 (0x00000200)
#define SB2_DBG_INT_acpu_int_en(data)                                                (0x00000200&((data)<<9))
#define SB2_DBG_INT_acpu_int_en_src(data)                                            ((0x00000200&(data))>>9)
#define SB2_DBG_INT_get_acpu_int_en(data)                                            ((0x00000200&(data))>>9)
#define SB2_DBG_INT_scpu_int_en_shift                                                (7)
#define SB2_DBG_INT_scpu_int_en_mask                                                 (0x00000080)
#define SB2_DBG_INT_scpu_int_en(data)                                                (0x00000080&((data)<<7))
#define SB2_DBG_INT_scpu_int_en_src(data)                                            ((0x00000080&(data))>>7)
#define SB2_DBG_INT_get_scpu_int_en(data)                                            ((0x00000080&(data))>>7)
#define SB2_DBG_INT_acpu_neg_int_shift                                               (6)
#define SB2_DBG_INT_acpu_neg_int_mask                                                (0x00000040)
#define SB2_DBG_INT_acpu_neg_int(data)                                               (0x00000040&((data)<<6))
#define SB2_DBG_INT_acpu_neg_int_src(data)                                           ((0x00000040&(data))>>6)
#define SB2_DBG_INT_get_acpu_neg_int(data)                                           ((0x00000040&(data))>>6)
#define SB2_DBG_INT_scpu_neg_int_shift                                               (4)
#define SB2_DBG_INT_scpu_neg_int_mask                                                (0x00000010)
#define SB2_DBG_INT_scpu_neg_int(data)                                               (0x00000010&((data)<<4))
#define SB2_DBG_INT_scpu_neg_int_src(data)                                           ((0x00000010&(data))>>4)
#define SB2_DBG_INT_get_scpu_neg_int(data)                                           ((0x00000010&(data))>>4)
#define SB2_DBG_INT_acpu_neg_int_en_shift                                            (3)
#define SB2_DBG_INT_acpu_neg_int_en_mask                                             (0x00000008)
#define SB2_DBG_INT_acpu_neg_int_en(data)                                            (0x00000008&((data)<<3))
#define SB2_DBG_INT_acpu_neg_int_en_src(data)                                        ((0x00000008&(data))>>3)
#define SB2_DBG_INT_get_acpu_neg_int_en(data)                                        ((0x00000008&(data))>>3)
#define SB2_DBG_INT_scpu_neg_int_en_shift                                            (1)
#define SB2_DBG_INT_scpu_neg_int_en_mask                                             (0x00000002)
#define SB2_DBG_INT_scpu_neg_int_en(data)                                            (0x00000002&((data)<<1))
#define SB2_DBG_INT_scpu_neg_int_en_src(data)                                        ((0x00000002&(data))>>1)
#define SB2_DBG_INT_get_scpu_neg_int_en(data)                                        ((0x00000002&(data))>>1)
#define SB2_DBG_INT_write_data_shift                                                 (0)
#define SB2_DBG_INT_write_data_mask                                                  (0x00000001)
#define SB2_DBG_INT_write_data(data)                                                 (0x00000001&((data)<<0))
#define SB2_DBG_INT_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define SB2_DBG_INT_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define SB2_DBG_WDATA_0                                                              0x9801A4E4
#define SB2_DBG_WDATA_1                                                              0x9801A4E8
#define SB2_DBG_WDATA_0_reg_addr                                                     "0xD801A4E4"
#define SB2_DBG_WDATA_1_reg_addr                                                     "0xD801A4E8"
#define SB2_DBG_WDATA_0_reg                                                          0xD801A4E4
#define SB2_DBG_WDATA_1_reg                                                          0xD801A4E8
#define set_SB2_DBG_WDATA_0_reg(data)   (*((volatile unsigned int*) SB2_DBG_WDATA_0_reg)=data)
#define set_SB2_DBG_WDATA_1_reg(data)   (*((volatile unsigned int*) SB2_DBG_WDATA_1_reg)=data)
#define get_SB2_DBG_WDATA_0_reg   (*((volatile unsigned int*) SB2_DBG_WDATA_0_reg))
#define get_SB2_DBG_WDATA_1_reg   (*((volatile unsigned int*) SB2_DBG_WDATA_1_reg))
#define SB2_DBG_WDATA_0_inst_adr                                                     "0x0039"
#define SB2_DBG_WDATA_1_inst_adr                                                     "0x003A"
#define SB2_DBG_WDATA_0_inst                                                         0x0039
#define SB2_DBG_WDATA_1_inst                                                         0x003A
#define SB2_DBG_WDATA_dbg_wdata_shift                                                (0)
#define SB2_DBG_WDATA_dbg_wdata_mask                                                 (0xFFFFFFFF)
#define SB2_DBG_WDATA_dbg_wdata(data)                                                (0xFFFFFFFF&((data)<<0))
#define SB2_DBG_WDATA_dbg_wdata_src(data)                                            ((0xFFFFFFFF&(data))>>0)
#define SB2_DBG_WDATA_get_dbg_wdata(data)                                            ((0xFFFFFFFF&(data))>>0)


#define SB2_DUMMY_0                                                                  0x9801A600
#define SB2_DUMMY_1                                                                  0x9801A604
#define SB2_DUMMY_2                                                                  0x9801A608
#define SB2_DUMMY_3                                                                  0x9801A60C
#define SB2_DUMMY_0_reg_addr                                                         "0xD801A600"
#define SB2_DUMMY_1_reg_addr                                                         "0xD801A604"
#define SB2_DUMMY_2_reg_addr                                                         "0xD801A608"
#define SB2_DUMMY_3_reg_addr                                                         "0xD801A60C"
#define SB2_DUMMY_0_reg                                                              0xD801A600
#define SB2_DUMMY_1_reg                                                              0xD801A604
#define SB2_DUMMY_2_reg                                                              0xD801A608
#define SB2_DUMMY_3_reg                                                              0xD801A60C
#define set_SB2_DUMMY_0_reg(data)   (*((volatile unsigned int*) SB2_DUMMY_0_reg)=data)
#define set_SB2_DUMMY_1_reg(data)   (*((volatile unsigned int*) SB2_DUMMY_1_reg)=data)
#define set_SB2_DUMMY_2_reg(data)   (*((volatile unsigned int*) SB2_DUMMY_2_reg)=data)
#define set_SB2_DUMMY_3_reg(data)   (*((volatile unsigned int*) SB2_DUMMY_3_reg)=data)
#define get_SB2_DUMMY_0_reg   (*((volatile unsigned int*) SB2_DUMMY_0_reg))
#define get_SB2_DUMMY_1_reg   (*((volatile unsigned int*) SB2_DUMMY_1_reg))
#define get_SB2_DUMMY_2_reg   (*((volatile unsigned int*) SB2_DUMMY_2_reg))
#define get_SB2_DUMMY_3_reg   (*((volatile unsigned int*) SB2_DUMMY_3_reg))
#define SB2_DUMMY_0_inst_adr                                                         "0x0080"
#define SB2_DUMMY_1_inst_adr                                                         "0x0081"
#define SB2_DUMMY_2_inst_adr                                                         "0x0082"
#define SB2_DUMMY_3_inst_adr                                                         "0x0083"
#define SB2_DUMMY_0_inst                                                             0x0080
#define SB2_DUMMY_1_inst                                                             0x0081
#define SB2_DUMMY_2_inst                                                             0x0082
#define SB2_DUMMY_3_inst                                                             0x0083
#define SB2_DUMMY_data_shift                                                         (0)
#define SB2_DUMMY_data_mask                                                          (0xFFFFFFFF)
#define SB2_DUMMY_data(data)                                                         (0xFFFFFFFF&((data)<<0))
#define SB2_DUMMY_data_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define SB2_DUMMY_get_data(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define SB2_SHADOW_0                                                                 0x9801A610
#define SB2_SHADOW_1                                                                 0x9801A614
#define SB2_SHADOW_2                                                                 0x9801A618
#define SB2_SHADOW_3                                                                 0x9801A61C
#define SB2_SHADOW_0_reg_addr                                                        "0xD801A610"
#define SB2_SHADOW_1_reg_addr                                                        "0xD801A614"
#define SB2_SHADOW_2_reg_addr                                                        "0xD801A618"
#define SB2_SHADOW_3_reg_addr                                                        "0xD801A61C"
#define SB2_SHADOW_0_reg                                                             0xD801A610
#define SB2_SHADOW_1_reg                                                             0xD801A614
#define SB2_SHADOW_2_reg                                                             0xD801A618
#define SB2_SHADOW_3_reg                                                             0xD801A61C
#define set_SB2_SHADOW_0_reg(data)   (*((volatile unsigned int*) SB2_SHADOW_0_reg)=data)
#define set_SB2_SHADOW_1_reg(data)   (*((volatile unsigned int*) SB2_SHADOW_1_reg)=data)
#define set_SB2_SHADOW_2_reg(data)   (*((volatile unsigned int*) SB2_SHADOW_2_reg)=data)
#define set_SB2_SHADOW_3_reg(data)   (*((volatile unsigned int*) SB2_SHADOW_3_reg)=data)
#define get_SB2_SHADOW_0_reg   (*((volatile unsigned int*) SB2_SHADOW_0_reg))
#define get_SB2_SHADOW_1_reg   (*((volatile unsigned int*) SB2_SHADOW_1_reg))
#define get_SB2_SHADOW_2_reg   (*((volatile unsigned int*) SB2_SHADOW_2_reg))
#define get_SB2_SHADOW_3_reg   (*((volatile unsigned int*) SB2_SHADOW_3_reg))
#define SB2_SHADOW_0_inst_adr                                                        "0x0084"
#define SB2_SHADOW_1_inst_adr                                                        "0x0085"
#define SB2_SHADOW_2_inst_adr                                                        "0x0086"
#define SB2_SHADOW_3_inst_adr                                                        "0x0087"
#define SB2_SHADOW_0_inst                                                            0x0084
#define SB2_SHADOW_1_inst                                                            0x0085
#define SB2_SHADOW_2_inst                                                            0x0086
#define SB2_SHADOW_3_inst                                                            0x0087
#define SB2_SHADOW_data_shift                                                        (0)
#define SB2_SHADOW_data_mask                                                         (0xFFFFFFFF)
#define SB2_SHADOW_data(data)                                                        (0xFFFFFFFF&((data)<<0))
#define SB2_SHADOW_data_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define SB2_SHADOW_get_data(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define SB2_HD_SEM_NEW_0                                                             0x9801A620
#define SB2_HD_SEM_NEW_1                                                             0x9801A624
#define SB2_HD_SEM_NEW_2                                                             0x9801A628
#define SB2_HD_SEM_NEW_3                                                             0x9801A62C
#define SB2_HD_SEM_NEW_4                                                             0x9801A630
#define SB2_HD_SEM_NEW_5                                                             0x9801A634
#define SB2_HD_SEM_NEW_6                                                             0x9801A638
#define SB2_HD_SEM_NEW_7                                                             0x9801A63C
#define SB2_HD_SEM_NEW_0_reg_addr                                                    "0xD801A620"
#define SB2_HD_SEM_NEW_1_reg_addr                                                    "0xD801A624"
#define SB2_HD_SEM_NEW_2_reg_addr                                                    "0xD801A628"
#define SB2_HD_SEM_NEW_3_reg_addr                                                    "0xD801A62C"
#define SB2_HD_SEM_NEW_4_reg_addr                                                    "0xD801A630"
#define SB2_HD_SEM_NEW_5_reg_addr                                                    "0xD801A634"
#define SB2_HD_SEM_NEW_6_reg_addr                                                    "0xD801A638"
#define SB2_HD_SEM_NEW_7_reg_addr                                                    "0xD801A63C"
#define SB2_HD_SEM_NEW_0_reg                                                         0xD801A620
#define SB2_HD_SEM_NEW_1_reg                                                         0xD801A624
#define SB2_HD_SEM_NEW_2_reg                                                         0xD801A628
#define SB2_HD_SEM_NEW_3_reg                                                         0xD801A62C
#define SB2_HD_SEM_NEW_4_reg                                                         0xD801A630
#define SB2_HD_SEM_NEW_5_reg                                                         0xD801A634
#define SB2_HD_SEM_NEW_6_reg                                                         0xD801A638
#define SB2_HD_SEM_NEW_7_reg                                                         0xD801A63C
#define set_SB2_HD_SEM_NEW_0_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_0_reg)=data)
#define set_SB2_HD_SEM_NEW_1_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_1_reg)=data)
#define set_SB2_HD_SEM_NEW_2_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_2_reg)=data)
#define set_SB2_HD_SEM_NEW_3_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_3_reg)=data)
#define set_SB2_HD_SEM_NEW_4_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_4_reg)=data)
#define set_SB2_HD_SEM_NEW_5_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_5_reg)=data)
#define set_SB2_HD_SEM_NEW_6_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_6_reg)=data)
#define set_SB2_HD_SEM_NEW_7_reg(data)   (*((volatile unsigned int*) SB2_HD_SEM_NEW_7_reg)=data)
#define get_SB2_HD_SEM_NEW_0_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_0_reg))
#define get_SB2_HD_SEM_NEW_1_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_1_reg))
#define get_SB2_HD_SEM_NEW_2_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_2_reg))
#define get_SB2_HD_SEM_NEW_3_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_3_reg))
#define get_SB2_HD_SEM_NEW_4_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_4_reg))
#define get_SB2_HD_SEM_NEW_5_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_5_reg))
#define get_SB2_HD_SEM_NEW_6_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_6_reg))
#define get_SB2_HD_SEM_NEW_7_reg   (*((volatile unsigned int*) SB2_HD_SEM_NEW_7_reg))
#define SB2_HD_SEM_NEW_0_inst_adr                                                    "0x0088"
#define SB2_HD_SEM_NEW_1_inst_adr                                                    "0x0089"
#define SB2_HD_SEM_NEW_2_inst_adr                                                    "0x008A"
#define SB2_HD_SEM_NEW_3_inst_adr                                                    "0x008B"
#define SB2_HD_SEM_NEW_4_inst_adr                                                    "0x008C"
#define SB2_HD_SEM_NEW_5_inst_adr                                                    "0x008D"
#define SB2_HD_SEM_NEW_6_inst_adr                                                    "0x008E"
#define SB2_HD_SEM_NEW_7_inst_adr                                                    "0x008F"
#define SB2_HD_SEM_NEW_0_inst                                                        0x0088
#define SB2_HD_SEM_NEW_1_inst                                                        0x0089
#define SB2_HD_SEM_NEW_2_inst                                                        0x008A
#define SB2_HD_SEM_NEW_3_inst                                                        0x008B
#define SB2_HD_SEM_NEW_4_inst                                                        0x008C
#define SB2_HD_SEM_NEW_5_inst                                                        0x008D
#define SB2_HD_SEM_NEW_6_inst                                                        0x008E
#define SB2_HD_SEM_NEW_7_inst                                                        0x008F
#define SB2_HD_SEM_NEW_Semaphore_shift                                               (0)
#define SB2_HD_SEM_NEW_Semaphore_mask                                                (0x00000001)
#define SB2_HD_SEM_NEW_Semaphore(data)                                               (0x00000001&((data)<<0))
#define SB2_HD_SEM_NEW_Semaphore_src(data)                                           ((0x00000001&(data))>>0)
#define SB2_HD_SEM_NEW_get_Semaphore(data)                                           ((0x00000001&(data))>>0)


#define SB2_RBUS_INVA_ACC_CTRL                                                       0x9801A650
#define SB2_RBUS_INVA_ACC_CTRL_reg_addr                                              "0xD801A650"
#define SB2_RBUS_INVA_ACC_CTRL_reg                                                   0xD801A650
#define set_SB2_RBUS_INVA_ACC_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_CTRL_reg)=data)
#define get_SB2_RBUS_INVA_ACC_CTRL_reg   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_CTRL_reg))
#define SB2_RBUS_INVA_ACC_CTRL_inst_adr                                              "0x0094"
#define SB2_RBUS_INVA_ACC_CTRL_inst                                                  0x0094
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_shift                                 (2)
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_mask                                  (0x00000004)
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec2_en(data)                                 (0x00000004&((data)<<2))
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec2_en_src(data)                             ((0x00000004&(data))>>2)
#define SB2_RBUS_INVA_ACC_CTRL_get_inva_wr_sec2_en(data)                             ((0x00000004&(data))>>2)
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_shift                                 (0)
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_mask                                  (0x00000001)
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec1_en(data)                                 (0x00000001&((data)<<0))
#define SB2_RBUS_INVA_ACC_CTRL_inva_wr_sec1_en_src(data)                             ((0x00000001&(data))>>0)
#define SB2_RBUS_INVA_ACC_CTRL_get_inva_wr_sec1_en(data)                             ((0x00000001&(data))>>0)


#define SB2_RBUS_INVA_ACC_SEC1_START                                                 0x9801A654
#define SB2_RBUS_INVA_ACC_SEC1_START_reg_addr                                        "0xD801A654"
#define SB2_RBUS_INVA_ACC_SEC1_START_reg                                             0xD801A654
#define set_SB2_RBUS_INVA_ACC_SEC1_START_reg(data)   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC1_START_reg)=data)
#define get_SB2_RBUS_INVA_ACC_SEC1_START_reg   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC1_START_reg))
#define SB2_RBUS_INVA_ACC_SEC1_START_inst_adr                                        "0x0095"
#define SB2_RBUS_INVA_ACC_SEC1_START_inst                                            0x0095
#define SB2_RBUS_INVA_ACC_SEC1_START_sec1_start_shift                                (2)
#define SB2_RBUS_INVA_ACC_SEC1_START_sec1_start_mask                                 (0x003FFFFC)
#define SB2_RBUS_INVA_ACC_SEC1_START_sec1_start(data)                                (0x003FFFFC&((data)<<2))
#define SB2_RBUS_INVA_ACC_SEC1_START_sec1_start_src(data)                            ((0x003FFFFC&(data))>>2)
#define SB2_RBUS_INVA_ACC_SEC1_START_get_sec1_start(data)                            ((0x003FFFFC&(data))>>2)


#define SB2_RBUS_INVA_ACC_SEC1_END                                                   0x9801A658
#define SB2_RBUS_INVA_ACC_SEC1_END_reg_addr                                          "0xD801A658"
#define SB2_RBUS_INVA_ACC_SEC1_END_reg                                               0xD801A658
#define set_SB2_RBUS_INVA_ACC_SEC1_END_reg(data)   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC1_END_reg)=data)
#define get_SB2_RBUS_INVA_ACC_SEC1_END_reg   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC1_END_reg))
#define SB2_RBUS_INVA_ACC_SEC1_END_inst_adr                                          "0x0096"
#define SB2_RBUS_INVA_ACC_SEC1_END_inst                                              0x0096
#define SB2_RBUS_INVA_ACC_SEC1_END_sec1_end_shift                                    (2)
#define SB2_RBUS_INVA_ACC_SEC1_END_sec1_end_mask                                     (0x003FFFFC)
#define SB2_RBUS_INVA_ACC_SEC1_END_sec1_end(data)                                    (0x003FFFFC&((data)<<2))
#define SB2_RBUS_INVA_ACC_SEC1_END_sec1_end_src(data)                                ((0x003FFFFC&(data))>>2)
#define SB2_RBUS_INVA_ACC_SEC1_END_get_sec1_end(data)                                ((0x003FFFFC&(data))>>2)


#define SB2_RBUS_INVA_ACC_SEC2_START                                                 0x9801A65C
#define SB2_RBUS_INVA_ACC_SEC2_START_reg_addr                                        "0xD801A65C"
#define SB2_RBUS_INVA_ACC_SEC2_START_reg                                             0xD801A65C
#define set_SB2_RBUS_INVA_ACC_SEC2_START_reg(data)   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC2_START_reg)=data)
#define get_SB2_RBUS_INVA_ACC_SEC2_START_reg   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC2_START_reg))
#define SB2_RBUS_INVA_ACC_SEC2_START_inst_adr                                        "0x0097"
#define SB2_RBUS_INVA_ACC_SEC2_START_inst                                            0x0097
#define SB2_RBUS_INVA_ACC_SEC2_START_sec2_start_shift                                (2)
#define SB2_RBUS_INVA_ACC_SEC2_START_sec2_start_mask                                 (0x003FFFFC)
#define SB2_RBUS_INVA_ACC_SEC2_START_sec2_start(data)                                (0x003FFFFC&((data)<<2))
#define SB2_RBUS_INVA_ACC_SEC2_START_sec2_start_src(data)                            ((0x003FFFFC&(data))>>2)
#define SB2_RBUS_INVA_ACC_SEC2_START_get_sec2_start(data)                            ((0x003FFFFC&(data))>>2)


#define SB2_RBUS_INVA_ACC_SEC2_END                                                   0x9801A660
#define SB2_RBUS_INVA_ACC_SEC2_END_reg_addr                                          "0xD801A660"
#define SB2_RBUS_INVA_ACC_SEC2_END_reg                                               0xD801A660
#define set_SB2_RBUS_INVA_ACC_SEC2_END_reg(data)   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC2_END_reg)=data)
#define get_SB2_RBUS_INVA_ACC_SEC2_END_reg   (*((volatile unsigned int*) SB2_RBUS_INVA_ACC_SEC2_END_reg))
#define SB2_RBUS_INVA_ACC_SEC2_END_inst_adr                                          "0x0098"
#define SB2_RBUS_INVA_ACC_SEC2_END_inst                                              0x0098
#define SB2_RBUS_INVA_ACC_SEC2_END_sec2_end_shift                                    (2)
#define SB2_RBUS_INVA_ACC_SEC2_END_sec2_end_mask                                     (0x003FFFFC)
#define SB2_RBUS_INVA_ACC_SEC2_END_sec2_end(data)                                    (0x003FFFFC&((data)<<2))
#define SB2_RBUS_INVA_ACC_SEC2_END_sec2_end_src(data)                                ((0x003FFFFC&(data))>>2)
#define SB2_RBUS_INVA_ACC_SEC2_END_get_sec2_end(data)                                ((0x003FFFFC&(data))>>2)


#define SB2_RBUS_CMP_CTRL                                                            0x9801A664
#define SB2_RBUS_CMP_CTRL_reg_addr                                                   "0xD801A664"
#define SB2_RBUS_CMP_CTRL_reg                                                        0xD801A664
#define set_SB2_RBUS_CMP_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RBUS_CMP_CTRL_reg)=data)
#define get_SB2_RBUS_CMP_CTRL_reg   (*((volatile unsigned int*) SB2_RBUS_CMP_CTRL_reg))
#define SB2_RBUS_CMP_CTRL_inst_adr                                                   "0x0099"
#define SB2_RBUS_CMP_CTRL_inst                                                       0x0099
#define SB2_RBUS_CMP_CTRL_crc_cmp_latch_en_shift                                     (0)
#define SB2_RBUS_CMP_CTRL_crc_cmp_latch_en_mask                                      (0x00000001)
#define SB2_RBUS_CMP_CTRL_crc_cmp_latch_en(data)                                     (0x00000001&((data)<<0))
#define SB2_RBUS_CMP_CTRL_crc_cmp_latch_en_src(data)                                 ((0x00000001&(data))>>0)
#define SB2_RBUS_CMP_CTRL_get_crc_cmp_latch_en(data)                                 ((0x00000001&(data))>>0)


#define SB2_RBUS_CMP_DATA0                                                           0x9801A668
#define SB2_RBUS_CMP_DATA0_reg_addr                                                  "0xD801A668"
#define SB2_RBUS_CMP_DATA0_reg                                                       0xD801A668
#define set_SB2_RBUS_CMP_DATA0_reg(data)   (*((volatile unsigned int*) SB2_RBUS_CMP_DATA0_reg)=data)
#define get_SB2_RBUS_CMP_DATA0_reg   (*((volatile unsigned int*) SB2_RBUS_CMP_DATA0_reg))
#define SB2_RBUS_CMP_DATA0_inst_adr                                                  "0x009A"
#define SB2_RBUS_CMP_DATA0_inst                                                      0x009A
#define SB2_RBUS_CMP_DATA0_crc_cmp_expect0_shift                                     (0)
#define SB2_RBUS_CMP_DATA0_crc_cmp_expect0_mask                                      (0xFFFFFFFF)
#define SB2_RBUS_CMP_DATA0_crc_cmp_expect0(data)                                     (0xFFFFFFFF&((data)<<0))
#define SB2_RBUS_CMP_DATA0_crc_cmp_expect0_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SB2_RBUS_CMP_DATA0_get_crc_cmp_expect0(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SB2_RBUS_CMP_DATA1                                                           0x9801A66C
#define SB2_RBUS_CMP_DATA1_reg_addr                                                  "0xD801A66C"
#define SB2_RBUS_CMP_DATA1_reg                                                       0xD801A66C
#define set_SB2_RBUS_CMP_DATA1_reg(data)   (*((volatile unsigned int*) SB2_RBUS_CMP_DATA1_reg)=data)
#define get_SB2_RBUS_CMP_DATA1_reg   (*((volatile unsigned int*) SB2_RBUS_CMP_DATA1_reg))
#define SB2_RBUS_CMP_DATA1_inst_adr                                                  "0x009B"
#define SB2_RBUS_CMP_DATA1_inst                                                      0x009B
#define SB2_RBUS_CMP_DATA1_crc_cmp_expect1_shift                                     (0)
#define SB2_RBUS_CMP_DATA1_crc_cmp_expect1_mask                                      (0xFFFFFFFF)
#define SB2_RBUS_CMP_DATA1_crc_cmp_expect1(data)                                     (0xFFFFFFFF&((data)<<0))
#define SB2_RBUS_CMP_DATA1_crc_cmp_expect1_src(data)                                 ((0xFFFFFFFF&(data))>>0)
#define SB2_RBUS_CMP_DATA1_get_crc_cmp_expect1(data)                                 ((0xFFFFFFFF&(data))>>0)


#define SB2_RBUS_CMP_RESULT                                                          0x9801A670
#define SB2_RBUS_CMP_RESULT_reg_addr                                                 "0xD801A670"
#define SB2_RBUS_CMP_RESULT_reg                                                      0xD801A670
#define set_SB2_RBUS_CMP_RESULT_reg(data)   (*((volatile unsigned int*) SB2_RBUS_CMP_RESULT_reg)=data)
#define get_SB2_RBUS_CMP_RESULT_reg   (*((volatile unsigned int*) SB2_RBUS_CMP_RESULT_reg))
#define SB2_RBUS_CMP_RESULT_inst_adr                                                 "0x009C"
#define SB2_RBUS_CMP_RESULT_inst                                                     0x009C
#define SB2_RBUS_CMP_RESULT_crc_cmp_result0_shift                                    (1)
#define SB2_RBUS_CMP_RESULT_crc_cmp_result0_mask                                     (0x00000002)
#define SB2_RBUS_CMP_RESULT_crc_cmp_result0(data)                                    (0x00000002&((data)<<1))
#define SB2_RBUS_CMP_RESULT_crc_cmp_result0_src(data)                                ((0x00000002&(data))>>1)
#define SB2_RBUS_CMP_RESULT_get_crc_cmp_result0(data)                                ((0x00000002&(data))>>1)
#define SB2_RBUS_CMP_RESULT_crc_cmp_result1_shift                                    (0)
#define SB2_RBUS_CMP_RESULT_crc_cmp_result1_mask                                     (0x00000001)
#define SB2_RBUS_CMP_RESULT_crc_cmp_result1(data)                                    (0x00000001&((data)<<0))
#define SB2_RBUS_CMP_RESULT_crc_cmp_result1_src(data)                                ((0x00000001&(data))>>0)
#define SB2_RBUS_CMP_RESULT_get_crc_cmp_result1(data)                                ((0x00000001&(data))>>0)


#define SB2_BIST_CTRL                                                                0x9801A674
#define SB2_BIST_CTRL_reg_addr                                                       "0xD801A674"
#define SB2_BIST_CTRL_reg                                                            0xD801A674
#define set_SB2_BIST_CTRL_reg(data)   (*((volatile unsigned int*) SB2_BIST_CTRL_reg)=data)
#define get_SB2_BIST_CTRL_reg   (*((volatile unsigned int*) SB2_BIST_CTRL_reg))
#define SB2_BIST_CTRL_inst_adr                                                       "0x009D"
#define SB2_BIST_CTRL_inst                                                           0x009D
#define SB2_BIST_CTRL_sb2_bist_rstn_shift                                            (7)
#define SB2_BIST_CTRL_sb2_bist_rstn_mask                                             (0x00000080)
#define SB2_BIST_CTRL_sb2_bist_rstn(data)                                            (0x00000080&((data)<<7))
#define SB2_BIST_CTRL_sb2_bist_rstn_src(data)                                        ((0x00000080&(data))>>7)
#define SB2_BIST_CTRL_get_sb2_bist_rstn(data)                                        ((0x00000080&(data))>>7)
#define SB2_BIST_CTRL_sb2_bist_en_shift                                              (6)
#define SB2_BIST_CTRL_sb2_bist_en_mask                                               (0x00000040)
#define SB2_BIST_CTRL_sb2_bist_en(data)                                              (0x00000040&((data)<<6))
#define SB2_BIST_CTRL_sb2_bist_en_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_BIST_CTRL_get_sb2_bist_en(data)                                          ((0x00000040&(data))>>6)
#define SB2_BIST_CTRL_sb2_rom_ls_shift                                               (5)
#define SB2_BIST_CTRL_sb2_rom_ls_mask                                                (0x00000020)
#define SB2_BIST_CTRL_sb2_rom_ls(data)                                               (0x00000020&((data)<<5))
#define SB2_BIST_CTRL_sb2_rom_ls_src(data)                                           ((0x00000020&(data))>>5)
#define SB2_BIST_CTRL_get_sb2_rom_ls(data)                                           ((0x00000020&(data))>>5)
#define SB2_BIST_CTRL_sb2_rom_rme_shift                                              (4)
#define SB2_BIST_CTRL_sb2_rom_rme_mask                                               (0x00000010)
#define SB2_BIST_CTRL_sb2_rom_rme(data)                                              (0x00000010&((data)<<4))
#define SB2_BIST_CTRL_sb2_rom_rme_src(data)                                          ((0x00000010&(data))>>4)
#define SB2_BIST_CTRL_get_sb2_rom_rme(data)                                          ((0x00000010&(data))>>4)
#define SB2_BIST_CTRL_sb2_rom_rm_shift                                               (0)
#define SB2_BIST_CTRL_sb2_rom_rm_mask                                                (0x0000000F)
#define SB2_BIST_CTRL_sb2_rom_rm(data)                                               (0x0000000F&((data)<<0))
#define SB2_BIST_CTRL_sb2_rom_rm_src(data)                                           ((0x0000000F&(data))>>0)
#define SB2_BIST_CTRL_get_sb2_rom_rm(data)                                           ((0x0000000F&(data))>>0)


#define SB2_BIST_STATUS                                                              0x9801A678
#define SB2_BIST_STATUS_reg_addr                                                     "0xD801A678"
#define SB2_BIST_STATUS_reg                                                          0xD801A678
#define set_SB2_BIST_STATUS_reg(data)   (*((volatile unsigned int*) SB2_BIST_STATUS_reg)=data)
#define get_SB2_BIST_STATUS_reg   (*((volatile unsigned int*) SB2_BIST_STATUS_reg))
#define SB2_BIST_STATUS_inst_adr                                                     "0x009E"
#define SB2_BIST_STATUS_inst                                                         0x009E
#define SB2_BIST_STATUS_sb2_rom_bist_done_shift                                      (16)
#define SB2_BIST_STATUS_sb2_rom_bist_done_mask                                       (0x00010000)
#define SB2_BIST_STATUS_sb2_rom_bist_done(data)                                      (0x00010000&((data)<<16))
#define SB2_BIST_STATUS_sb2_rom_bist_done_src(data)                                  ((0x00010000&(data))>>16)
#define SB2_BIST_STATUS_get_sb2_rom_bist_done(data)                                  ((0x00010000&(data))>>16)


#define SB2_BIST_MISR_DATAOUT0                                                       0x9801A67C
#define SB2_BIST_MISR_DATAOUT0_reg_addr                                              "0xD801A67C"
#define SB2_BIST_MISR_DATAOUT0_reg                                                   0xD801A67C
#define set_SB2_BIST_MISR_DATAOUT0_reg(data)   (*((volatile unsigned int*) SB2_BIST_MISR_DATAOUT0_reg)=data)
#define get_SB2_BIST_MISR_DATAOUT0_reg   (*((volatile unsigned int*) SB2_BIST_MISR_DATAOUT0_reg))
#define SB2_BIST_MISR_DATAOUT0_inst_adr                                              "0x009F"
#define SB2_BIST_MISR_DATAOUT0_inst                                                  0x009F
#define SB2_BIST_MISR_DATAOUT0_sb2_misr_dataout_0_shift                              (0)
#define SB2_BIST_MISR_DATAOUT0_sb2_misr_dataout_0_mask                               (0xFFFFFFFF)
#define SB2_BIST_MISR_DATAOUT0_sb2_misr_dataout_0(data)                              (0xFFFFFFFF&((data)<<0))
#define SB2_BIST_MISR_DATAOUT0_sb2_misr_dataout_0_src(data)                          ((0xFFFFFFFF&(data))>>0)
#define SB2_BIST_MISR_DATAOUT0_get_sb2_misr_dataout_0(data)                          ((0xFFFFFFFF&(data))>>0)


#define SB2_BIST_MISR_DATAOUT1                                                       0x9801A680
#define SB2_BIST_MISR_DATAOUT1_reg_addr                                              "0xD801A680"
#define SB2_BIST_MISR_DATAOUT1_reg                                                   0xD801A680
#define set_SB2_BIST_MISR_DATAOUT1_reg(data)   (*((volatile unsigned int*) SB2_BIST_MISR_DATAOUT1_reg)=data)
#define get_SB2_BIST_MISR_DATAOUT1_reg   (*((volatile unsigned int*) SB2_BIST_MISR_DATAOUT1_reg))
#define SB2_BIST_MISR_DATAOUT1_inst_adr                                              "0x00A0"
#define SB2_BIST_MISR_DATAOUT1_inst                                                  0x00A0
#define SB2_BIST_MISR_DATAOUT1_sb2_misr_dataout_1_shift                              (0)
#define SB2_BIST_MISR_DATAOUT1_sb2_misr_dataout_1_mask                               (0xFFFFFFFF)
#define SB2_BIST_MISR_DATAOUT1_sb2_misr_dataout_1(data)                              (0xFFFFFFFF&((data)<<0))
#define SB2_BIST_MISR_DATAOUT1_sb2_misr_dataout_1_src(data)                          ((0xFFFFFFFF&(data))>>0)
#define SB2_BIST_MISR_DATAOUT1_get_sb2_misr_dataout_1(data)                          ((0xFFFFFFFF&(data))>>0)


#define SB2_SFC_OPCODE                                                               0x9801A800
#define SB2_SFC_OPCODE_reg_addr                                                      "0xD801A800"
#define SB2_SFC_OPCODE_reg                                                           0xD801A800
#define set_SB2_SFC_OPCODE_reg(data)   (*((volatile unsigned int*) SB2_SFC_OPCODE_reg)=data)
#define get_SB2_SFC_OPCODE_reg   (*((volatile unsigned int*) SB2_SFC_OPCODE_reg))
#define SB2_SFC_OPCODE_inst_adr                                                      "0x0000"
#define SB2_SFC_OPCODE_inst                                                          0x0000
#define SB2_SFC_OPCODE_dual_mode_shift                                               (9)
#define SB2_SFC_OPCODE_dual_mode_mask                                                (0x00000600)
#define SB2_SFC_OPCODE_dual_mode(data)                                               (0x00000600&((data)<<9))
#define SB2_SFC_OPCODE_dual_mode_src(data)                                           ((0x00000600&(data))>>9)
#define SB2_SFC_OPCODE_get_dual_mode(data)                                           ((0x00000600&(data))>>9)
#define SB2_SFC_OPCODE_fat_mode_shift                                                (8)
#define SB2_SFC_OPCODE_fat_mode_mask                                                 (0x00000100)
#define SB2_SFC_OPCODE_fat_mode(data)                                                (0x00000100&((data)<<8))
#define SB2_SFC_OPCODE_fat_mode_src(data)                                            ((0x00000100&(data))>>8)
#define SB2_SFC_OPCODE_get_fat_mode(data)                                            ((0x00000100&(data))>>8)
#define SB2_SFC_OPCODE_opc_shift                                                     (0)
#define SB2_SFC_OPCODE_opc_mask                                                      (0x000000FF)
#define SB2_SFC_OPCODE_opc(data)                                                     (0x000000FF&((data)<<0))
#define SB2_SFC_OPCODE_opc_src(data)                                                 ((0x000000FF&(data))>>0)
#define SB2_SFC_OPCODE_get_opc(data)                                                 ((0x000000FF&(data))>>0)


#define SB2_SFC_CTL                                                                  0x9801A804
#define SB2_SFC_CTL_reg_addr                                                         "0xD801A804"
#define SB2_SFC_CTL_reg                                                              0xD801A804
#define set_SB2_SFC_CTL_reg(data)   (*((volatile unsigned int*) SB2_SFC_CTL_reg)=data)
#define get_SB2_SFC_CTL_reg   (*((volatile unsigned int*) SB2_SFC_CTL_reg))
#define SB2_SFC_CTL_inst_adr                                                         "0x0001"
#define SB2_SFC_CTL_inst                                                             0x0001
#define SB2_SFC_CTL_dataen_shift                                                     (4)
#define SB2_SFC_CTL_dataen_mask                                                      (0x00000010)
#define SB2_SFC_CTL_dataen(data)                                                     (0x00000010&((data)<<4))
#define SB2_SFC_CTL_dataen_src(data)                                                 ((0x00000010&(data))>>4)
#define SB2_SFC_CTL_get_dataen(data)                                                 ((0x00000010&(data))>>4)
#define SB2_SFC_CTL_adren_shift                                                      (3)
#define SB2_SFC_CTL_adren_mask                                                       (0x00000008)
#define SB2_SFC_CTL_adren(data)                                                      (0x00000008&((data)<<3))
#define SB2_SFC_CTL_adren_src(data)                                                  ((0x00000008&(data))>>3)
#define SB2_SFC_CTL_get_adren(data)                                                  ((0x00000008&(data))>>3)
#define SB2_SFC_CTL_dmycnt_shift                                                     (0)
#define SB2_SFC_CTL_dmycnt_mask                                                      (0x00000007)
#define SB2_SFC_CTL_dmycnt(data)                                                     (0x00000007&((data)<<0))
#define SB2_SFC_CTL_dmycnt_src(data)                                                 ((0x00000007&(data))>>0)
#define SB2_SFC_CTL_get_dmycnt(data)                                                 ((0x00000007&(data))>>0)


#define SB2_SFC_SCK                                                                  0x9801A808
#define SB2_SFC_SCK_reg_addr                                                         "0xD801A808"
#define SB2_SFC_SCK_reg                                                              0xD801A808
#define set_SB2_SFC_SCK_reg(data)   (*((volatile unsigned int*) SB2_SFC_SCK_reg)=data)
#define get_SB2_SFC_SCK_reg   (*((volatile unsigned int*) SB2_SFC_SCK_reg))
#define SB2_SFC_SCK_inst_adr                                                         "0x0002"
#define SB2_SFC_SCK_inst                                                             0x0002
#define SB2_SFC_SCK_mode_shift                                                       (8)
#define SB2_SFC_SCK_mode_mask                                                        (0x00000100)
#define SB2_SFC_SCK_mode(data)                                                       (0x00000100&((data)<<8))
#define SB2_SFC_SCK_mode_src(data)                                                   ((0x00000100&(data))>>8)
#define SB2_SFC_SCK_get_mode(data)                                                   ((0x00000100&(data))>>8)
#define SB2_SFC_SCK_fdiv_shift                                                       (0)
#define SB2_SFC_SCK_fdiv_mask                                                        (0x000000FF)
#define SB2_SFC_SCK_fdiv(data)                                                       (0x000000FF&((data)<<0))
#define SB2_SFC_SCK_fdiv_src(data)                                                   ((0x000000FF&(data))>>0)
#define SB2_SFC_SCK_get_fdiv(data)                                                   ((0x000000FF&(data))>>0)


#define SB2_SFC_CE                                                                   0x9801A80C
#define SB2_SFC_CE_reg_addr                                                          "0xD801A80C"
#define SB2_SFC_CE_reg                                                               0xD801A80C
#define set_SB2_SFC_CE_reg(data)   (*((volatile unsigned int*) SB2_SFC_CE_reg)=data)
#define get_SB2_SFC_CE_reg   (*((volatile unsigned int*) SB2_SFC_CE_reg))
#define SB2_SFC_CE_inst_adr                                                          "0x0003"
#define SB2_SFC_CE_inst                                                              0x0003
#define SB2_SFC_CE_tdt_shift                                                         (16)
#define SB2_SFC_CE_tdt_mask                                                          (0xFFFF0000)
#define SB2_SFC_CE_tdt(data)                                                         (0xFFFF0000&((data)<<16))
#define SB2_SFC_CE_tdt_src(data)                                                     ((0xFFFF0000&(data))>>16)
#define SB2_SFC_CE_get_tdt(data)                                                     ((0xFFFF0000&(data))>>16)
#define SB2_SFC_CE_Phcnt_shift                                                       (8)
#define SB2_SFC_CE_Phcnt_mask                                                        (0x0000FF00)
#define SB2_SFC_CE_Phcnt(data)                                                       (0x0000FF00&((data)<<8))
#define SB2_SFC_CE_Phcnt_src(data)                                                   ((0x0000FF00&(data))>>8)
#define SB2_SFC_CE_get_Phcnt(data)                                                   ((0x0000FF00&(data))>>8)
#define SB2_SFC_CE_Plcnt_shift                                                       (0)
#define SB2_SFC_CE_Plcnt_mask                                                        (0x000000FF)
#define SB2_SFC_CE_Plcnt(data)                                                       (0x000000FF&((data)<<0))
#define SB2_SFC_CE_Plcnt_src(data)                                                   ((0x000000FF&(data))>>0)
#define SB2_SFC_CE_get_Plcnt(data)                                                   ((0x000000FF&(data))>>0)


#define SB2_SFC_WP                                                                   0x9801A810
#define SB2_SFC_WP_reg_addr                                                          "0xD801A810"
#define SB2_SFC_WP_reg                                                               0xD801A810
#define set_SB2_SFC_WP_reg(data)   (*((volatile unsigned int*) SB2_SFC_WP_reg)=data)
#define get_SB2_SFC_WP_reg   (*((volatile unsigned int*) SB2_SFC_WP_reg))
#define SB2_SFC_WP_inst_adr                                                          "0x0004"
#define SB2_SFC_WP_inst                                                              0x0004
#define SB2_SFC_WP_write_en5_shift                                                   (27)
#define SB2_SFC_WP_write_en5_mask                                                    (0x08000000)
#define SB2_SFC_WP_write_en5(data)                                                   (0x08000000&((data)<<27))
#define SB2_SFC_WP_write_en5_src(data)                                               ((0x08000000&(data))>>27)
#define SB2_SFC_WP_get_write_en5(data)                                               ((0x08000000&(data))>>27)
#define SB2_SFC_WP_rdy_shift                                                         (26)
#define SB2_SFC_WP_rdy_mask                                                          (0x04000000)
#define SB2_SFC_WP_rdy(data)                                                         (0x04000000&((data)<<26))
#define SB2_SFC_WP_rdy_src(data)                                                     ((0x04000000&(data))>>26)
#define SB2_SFC_WP_get_rdy(data)                                                     ((0x04000000&(data))>>26)
#define SB2_SFC_WP_write_en1_shift                                                   (1)
#define SB2_SFC_WP_write_en1_mask                                                    (0x00000002)
#define SB2_SFC_WP_write_en1(data)                                                   (0x00000002&((data)<<1))
#define SB2_SFC_WP_write_en1_src(data)                                               ((0x00000002&(data))>>1)
#define SB2_SFC_WP_get_write_en1(data)                                               ((0x00000002&(data))>>1)
#define SB2_SFC_WP_wp_n_shift                                                        (0)
#define SB2_SFC_WP_wp_n_mask                                                         (0x00000001)
#define SB2_SFC_WP_wp_n(data)                                                        (0x00000001&((data)<<0))
#define SB2_SFC_WP_wp_n_src(data)                                                    ((0x00000001&(data))>>0)
#define SB2_SFC_WP_get_wp_n(data)                                                    ((0x00000001&(data))>>0)


#define SB2_SFC_POS_LATCH                                                            0x9801A814
#define SB2_SFC_POS_LATCH_reg_addr                                                   "0xD801A814"
#define SB2_SFC_POS_LATCH_reg                                                        0xD801A814
#define set_SB2_SFC_POS_LATCH_reg(data)   (*((volatile unsigned int*) SB2_SFC_POS_LATCH_reg)=data)
#define get_SB2_SFC_POS_LATCH_reg   (*((volatile unsigned int*) SB2_SFC_POS_LATCH_reg))
#define SB2_SFC_POS_LATCH_inst_adr                                                   "0x0005"
#define SB2_SFC_POS_LATCH_inst                                                       0x0005
#define SB2_SFC_POS_LATCH_pos_latch_shift                                            (0)
#define SB2_SFC_POS_LATCH_pos_latch_mask                                             (0x00000001)
#define SB2_SFC_POS_LATCH_pos_latch(data)                                            (0x00000001&((data)<<0))
#define SB2_SFC_POS_LATCH_pos_latch_src(data)                                        ((0x00000001&(data))>>0)
#define SB2_SFC_POS_LATCH_get_pos_latch(data)                                        ((0x00000001&(data))>>0)


#define SB2_SFC_WAIT_WR                                                              0x9801A818
#define SB2_SFC_WAIT_WR_reg_addr                                                     "0xD801A818"
#define SB2_SFC_WAIT_WR_reg                                                          0xD801A818
#define set_SB2_SFC_WAIT_WR_reg(data)   (*((volatile unsigned int*) SB2_SFC_WAIT_WR_reg)=data)
#define get_SB2_SFC_WAIT_WR_reg   (*((volatile unsigned int*) SB2_SFC_WAIT_WR_reg))
#define SB2_SFC_WAIT_WR_inst_adr                                                     "0x0006"
#define SB2_SFC_WAIT_WR_inst                                                         0x0006
#define SB2_SFC_WAIT_WR_wt_prog_done_shift                                           (8)
#define SB2_SFC_WAIT_WR_wt_prog_done_mask                                            (0x00000100)
#define SB2_SFC_WAIT_WR_wt_prog_done(data)                                           (0x00000100&((data)<<8))
#define SB2_SFC_WAIT_WR_wt_prog_done_src(data)                                       ((0x00000100&(data))>>8)
#define SB2_SFC_WAIT_WR_get_wt_prog_done(data)                                       ((0x00000100&(data))>>8)
#define SB2_SFC_WAIT_WR_rdsr_op_shift                                                (0)
#define SB2_SFC_WAIT_WR_rdsr_op_mask                                                 (0x000000FF)
#define SB2_SFC_WAIT_WR_rdsr_op(data)                                                (0x000000FF&((data)<<0))
#define SB2_SFC_WAIT_WR_rdsr_op_src(data)                                            ((0x000000FF&(data))>>0)
#define SB2_SFC_WAIT_WR_get_rdsr_op(data)                                            ((0x000000FF&(data))>>0)


#define SB2_SFC_EN_WR                                                                0x9801A81C
#define SB2_SFC_EN_WR_reg_addr                                                       "0xD801A81C"
#define SB2_SFC_EN_WR_reg                                                            0xD801A81C
#define set_SB2_SFC_EN_WR_reg(data)   (*((volatile unsigned int*) SB2_SFC_EN_WR_reg)=data)
#define get_SB2_SFC_EN_WR_reg   (*((volatile unsigned int*) SB2_SFC_EN_WR_reg))
#define SB2_SFC_EN_WR_inst_adr                                                       "0x0007"
#define SB2_SFC_EN_WR_inst                                                           0x0007
#define SB2_SFC_EN_WR_wt_prog_en_shift                                               (8)
#define SB2_SFC_EN_WR_wt_prog_en_mask                                                (0x00000100)
#define SB2_SFC_EN_WR_wt_prog_en(data)                                               (0x00000100&((data)<<8))
#define SB2_SFC_EN_WR_wt_prog_en_src(data)                                           ((0x00000100&(data))>>8)
#define SB2_SFC_EN_WR_get_wt_prog_en(data)                                           ((0x00000100&(data))>>8)
#define SB2_SFC_EN_WR_wr_en_op_shift                                                 (0)
#define SB2_SFC_EN_WR_wr_en_op_mask                                                  (0x000000FF)
#define SB2_SFC_EN_WR_wr_en_op(data)                                                 (0x000000FF&((data)<<0))
#define SB2_SFC_EN_WR_wr_en_op_src(data)                                             ((0x000000FF&(data))>>0)
#define SB2_SFC_EN_WR_get_wr_en_op(data)                                             ((0x000000FF&(data))>>0)


#define SB2_SFC_FAST_RD                                                              0x9801A820
#define SB2_SFC_FAST_RD_reg_addr                                                     "0xD801A820"
#define SB2_SFC_FAST_RD_reg                                                          0xD801A820
#define set_SB2_SFC_FAST_RD_reg(data)   (*((volatile unsigned int*) SB2_SFC_FAST_RD_reg)=data)
#define get_SB2_SFC_FAST_RD_reg   (*((volatile unsigned int*) SB2_SFC_FAST_RD_reg))
#define SB2_SFC_FAST_RD_inst_adr                                                     "0x0008"
#define SB2_SFC_FAST_RD_inst                                                         0x0008
#define SB2_SFC_FAST_RD_sf_dclk_sel_shift                                            (4)
#define SB2_SFC_FAST_RD_sf_dclk_sel_mask                                             (0x00000010)
#define SB2_SFC_FAST_RD_sf_dclk_sel(data)                                            (0x00000010&((data)<<4))
#define SB2_SFC_FAST_RD_sf_dclk_sel_src(data)                                        ((0x00000010&(data))>>4)
#define SB2_SFC_FAST_RD_get_sf_dclk_sel(data)                                        ((0x00000010&(data))>>4)
#define SB2_SFC_FAST_RD_fifo_write_tap_shift                                         (1)
#define SB2_SFC_FAST_RD_fifo_write_tap_mask                                          (0x0000000E)
#define SB2_SFC_FAST_RD_fifo_write_tap(data)                                         (0x0000000E&((data)<<1))
#define SB2_SFC_FAST_RD_fifo_write_tap_src(data)                                     ((0x0000000E&(data))>>1)
#define SB2_SFC_FAST_RD_get_fifo_write_tap(data)                                     ((0x0000000E&(data))>>1)
#define SB2_SFC_FAST_RD_fast_read_en_shift                                           (0)
#define SB2_SFC_FAST_RD_fast_read_en_mask                                            (0x00000001)
#define SB2_SFC_FAST_RD_fast_read_en(data)                                           (0x00000001&((data)<<0))
#define SB2_SFC_FAST_RD_fast_read_en_src(data)                                       ((0x00000001&(data))>>0)
#define SB2_SFC_FAST_RD_get_fast_read_en(data)                                       ((0x00000001&(data))>>0)


#define SB2_SFC_SCK_TAP                                                              0x9801A824
#define SB2_SFC_SCK_TAP_reg_addr                                                     "0xD801A824"
#define SB2_SFC_SCK_TAP_reg                                                          0xD801A824
#define set_SB2_SFC_SCK_TAP_reg(data)   (*((volatile unsigned int*) SB2_SFC_SCK_TAP_reg)=data)
#define get_SB2_SFC_SCK_TAP_reg   (*((volatile unsigned int*) SB2_SFC_SCK_TAP_reg))
#define SB2_SFC_SCK_TAP_inst_adr                                                     "0x0009"
#define SB2_SFC_SCK_TAP_inst                                                         0x0009
#define SB2_SFC_SCK_TAP_delay_clk_tap_shift                                          (0)
#define SB2_SFC_SCK_TAP_delay_clk_tap_mask                                           (0xFFFFFFFF)
#define SB2_SFC_SCK_TAP_delay_clk_tap(data)                                          (0xFFFFFFFF&((data)<<0))
#define SB2_SFC_SCK_TAP_delay_clk_tap_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SB2_SFC_SCK_TAP_get_delay_clk_tap(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SB2_SFC_ADR_FOUR_BYTE_EN                                                     0x9801A828
#define SB2_SFC_ADR_FOUR_BYTE_EN_reg_addr                                            "0xD801A828"
#define SB2_SFC_ADR_FOUR_BYTE_EN_reg                                                 0xD801A828
#define set_SB2_SFC_ADR_FOUR_BYTE_EN_reg(data)   (*((volatile unsigned int*) SB2_SFC_ADR_FOUR_BYTE_EN_reg)=data)
#define get_SB2_SFC_ADR_FOUR_BYTE_EN_reg   (*((volatile unsigned int*) SB2_SFC_ADR_FOUR_BYTE_EN_reg))
#define SB2_SFC_ADR_FOUR_BYTE_EN_inst_adr                                            "0x000A"
#define SB2_SFC_ADR_FOUR_BYTE_EN_inst                                                0x000A
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_shift                        (0)
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_mask                         (0x00000001)
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en(data)                        (0x00000001&((data)<<0))
#define SB2_SFC_ADR_FOUR_BYTE_EN_SFC_OPCODE_adr4byte_en_src(data)                    ((0x00000001&(data))>>0)
#define SB2_SFC_ADR_FOUR_BYTE_EN_get_SFC_OPCODE_adr4byte_en(data)                    ((0x00000001&(data))>>0)


#define SB2_MUXPAD2                                                                  0x9801A908
#define SB2_MUXPAD2_reg_addr                                                         "0xD801A908"
#define SB2_MUXPAD2_reg                                                              0xD801A908
#define set_SB2_MUXPAD2_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD2_reg)=data)
#define get_SB2_MUXPAD2_reg   (*((volatile unsigned int*) SB2_MUXPAD2_reg))
#define SB2_MUXPAD2_inst_adr                                                         "0x0042"
#define SB2_MUXPAD2_inst                                                             0x0042
#define SB2_MUXPAD2_tp1_clk_shift                                                    (22)
#define SB2_MUXPAD2_tp1_clk_mask                                                     (0x00C00000)
#define SB2_MUXPAD2_tp1_clk(data)                                                    (0x00C00000&((data)<<22))
#define SB2_MUXPAD2_tp1_clk_src(data)                                                ((0x00C00000&(data))>>22)
#define SB2_MUXPAD2_get_tp1_clk(data)                                                ((0x00C00000&(data))>>22)
#define SB2_MUXPAD2_tp1_valid_shift                                                  (20)
#define SB2_MUXPAD2_tp1_valid_mask                                                   (0x00300000)
#define SB2_MUXPAD2_tp1_valid(data)                                                  (0x00300000&((data)<<20))
#define SB2_MUXPAD2_tp1_valid_src(data)                                              ((0x00300000&(data))>>20)
#define SB2_MUXPAD2_get_tp1_valid(data)                                              ((0x00300000&(data))>>20)
#define SB2_MUXPAD2_tp1_sync_shift                                                   (18)
#define SB2_MUXPAD2_tp1_sync_mask                                                    (0x000C0000)
#define SB2_MUXPAD2_tp1_sync(data)                                                   (0x000C0000&((data)<<18))
#define SB2_MUXPAD2_tp1_sync_src(data)                                               ((0x000C0000&(data))>>18)
#define SB2_MUXPAD2_get_tp1_sync(data)                                               ((0x000C0000&(data))>>18)
#define SB2_MUXPAD2_tp1_data_shift                                                   (16)
#define SB2_MUXPAD2_tp1_data_mask                                                    (0x00030000)
#define SB2_MUXPAD2_tp1_data(data)                                                   (0x00030000&((data)<<16))
#define SB2_MUXPAD2_tp1_data_src(data)                                               ((0x00030000&(data))>>16)
#define SB2_MUXPAD2_get_tp1_data(data)                                               ((0x00030000&(data))>>16)
#define SB2_MUXPAD2_tp0_clk_shift                                                    (9)
#define SB2_MUXPAD2_tp0_clk_mask                                                     (0x00000E00)
#define SB2_MUXPAD2_tp0_clk(data)                                                    (0x00000E00&((data)<<9))
#define SB2_MUXPAD2_tp0_clk_src(data)                                                ((0x00000E00&(data))>>9)
#define SB2_MUXPAD2_get_tp0_clk(data)                                                ((0x00000E00&(data))>>9)
#define SB2_MUXPAD2_tp0_valid_shift                                                  (6)
#define SB2_MUXPAD2_tp0_valid_mask                                                   (0x000001C0)
#define SB2_MUXPAD2_tp0_valid(data)                                                  (0x000001C0&((data)<<6))
#define SB2_MUXPAD2_tp0_valid_src(data)                                              ((0x000001C0&(data))>>6)
#define SB2_MUXPAD2_get_tp0_valid(data)                                              ((0x000001C0&(data))>>6)
#define SB2_MUXPAD2_tp0_sync_shift                                                   (3)
#define SB2_MUXPAD2_tp0_sync_mask                                                    (0x00000038)
#define SB2_MUXPAD2_tp0_sync(data)                                                   (0x00000038&((data)<<3))
#define SB2_MUXPAD2_tp0_sync_src(data)                                               ((0x00000038&(data))>>3)
#define SB2_MUXPAD2_get_tp0_sync(data)                                               ((0x00000038&(data))>>3)
#define SB2_MUXPAD2_tp0_data_shift                                                   (0)
#define SB2_MUXPAD2_tp0_data_mask                                                    (0x00000007)
#define SB2_MUXPAD2_tp0_data(data)                                                   (0x00000007&((data)<<0))
#define SB2_MUXPAD2_tp0_data_src(data)                                               ((0x00000007&(data))>>0)
#define SB2_MUXPAD2_get_tp0_data(data)                                               ((0x00000007&(data))>>0)


#define SB2_MUXPAD3                                                                  0x9801A90C
#define SB2_MUXPAD3_reg_addr                                                         "0xD801A90C"
#define SB2_MUXPAD3_reg                                                              0xD801A90C
#define set_SB2_MUXPAD3_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD3_reg)=data)
#define get_SB2_MUXPAD3_reg   (*((volatile unsigned int*) SB2_MUXPAD3_reg))
#define SB2_MUXPAD3_inst_adr                                                         "0x0043"
#define SB2_MUXPAD3_inst                                                             0x0043
#define SB2_MUXPAD3_sensor_cko_0_shift                                               (30)
#define SB2_MUXPAD3_sensor_cko_0_mask                                                (0xC0000000)
#define SB2_MUXPAD3_sensor_cko_0(data)                                               (0xC0000000&((data)<<30))
#define SB2_MUXPAD3_sensor_cko_0_src(data)                                           ((0xC0000000&(data))>>30)
#define SB2_MUXPAD3_get_sensor_cko_0(data)                                           ((0xC0000000&(data))>>30)
#define SB2_MUXPAD3_sensor_cko_1_shift                                               (28)
#define SB2_MUXPAD3_sensor_cko_1_mask                                                (0x30000000)
#define SB2_MUXPAD3_sensor_cko_1(data)                                               (0x30000000&((data)<<28))
#define SB2_MUXPAD3_sensor_cko_1_src(data)                                           ((0x30000000&(data))>>28)
#define SB2_MUXPAD3_get_sensor_cko_1(data)                                           ((0x30000000&(data))>>28)
#define SB2_MUXPAD3_sensor_rst_shift                                                 (26)
#define SB2_MUXPAD3_sensor_rst_mask                                                  (0x0C000000)
#define SB2_MUXPAD3_sensor_rst(data)                                                 (0x0C000000&((data)<<26))
#define SB2_MUXPAD3_sensor_rst_src(data)                                             ((0x0C000000&(data))>>26)
#define SB2_MUXPAD3_get_sensor_rst(data)                                             ((0x0C000000&(data))>>26)
#define SB2_MUXPAD3_sensor_stb_0_shift                                               (24)
#define SB2_MUXPAD3_sensor_stb_0_mask                                                (0x03000000)
#define SB2_MUXPAD3_sensor_stb_0(data)                                               (0x03000000&((data)<<24))
#define SB2_MUXPAD3_sensor_stb_0_src(data)                                           ((0x03000000&(data))>>24)
#define SB2_MUXPAD3_get_sensor_stb_0(data)                                           ((0x03000000&(data))>>24)
#define SB2_MUXPAD3_sensor_stb_1_shift                                               (22)
#define SB2_MUXPAD3_sensor_stb_1_mask                                                (0x00C00000)
#define SB2_MUXPAD3_sensor_stb_1(data)                                               (0x00C00000&((data)<<22))
#define SB2_MUXPAD3_sensor_stb_1_src(data)                                           ((0x00C00000&(data))>>22)
#define SB2_MUXPAD3_get_sensor_stb_1(data)                                           ((0x00C00000&(data))>>22)
#define SB2_MUXPAD3_ejtag_scpu_loc_shift                                             (20)
#define SB2_MUXPAD3_ejtag_scpu_loc_mask                                              (0x00300000)
#define SB2_MUXPAD3_ejtag_scpu_loc(data)                                             (0x00300000&((data)<<20))
#define SB2_MUXPAD3_ejtag_scpu_loc_src(data)                                         ((0x00300000&(data))>>20)
#define SB2_MUXPAD3_get_ejtag_scpu_loc(data)                                         ((0x00300000&(data))>>20)
#define SB2_MUXPAD3_hi_loc_shift                                                     (18)
#define SB2_MUXPAD3_hi_loc_mask                                                      (0x000C0000)
#define SB2_MUXPAD3_hi_loc(data)                                                     (0x000C0000&((data)<<18))
#define SB2_MUXPAD3_hi_loc_src(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD3_get_hi_loc(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD3_usb_id_shift                                                     (16)
#define SB2_MUXPAD3_usb_id_mask                                                      (0x00030000)
#define SB2_MUXPAD3_usb_id(data)                                                     (0x00030000&((data)<<16))
#define SB2_MUXPAD3_usb_id_src(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD3_get_usb_id(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD3_i2c_scl_5_shift                                                  (10)
#define SB2_MUXPAD3_i2c_scl_5_mask                                                   (0x00000C00)
#define SB2_MUXPAD3_i2c_scl_5(data)                                                  (0x00000C00&((data)<<10))
#define SB2_MUXPAD3_i2c_scl_5_src(data)                                              ((0x00000C00&(data))>>10)
#define SB2_MUXPAD3_get_i2c_scl_5(data)                                              ((0x00000C00&(data))>>10)
#define SB2_MUXPAD3_i2c_sda_5_shift                                                  (8)
#define SB2_MUXPAD3_i2c_sda_5_mask                                                   (0x00000300)
#define SB2_MUXPAD3_i2c_sda_5(data)                                                  (0x00000300&((data)<<8))
#define SB2_MUXPAD3_i2c_sda_5_src(data)                                              ((0x00000300&(data))>>8)
#define SB2_MUXPAD3_get_i2c_sda_5(data)                                              ((0x00000300&(data))>>8)
#define SB2_MUXPAD3_i2c_scl_4_shift                                                  (6)
#define SB2_MUXPAD3_i2c_scl_4_mask                                                   (0x000000C0)
#define SB2_MUXPAD3_i2c_scl_4(data)                                                  (0x000000C0&((data)<<6))
#define SB2_MUXPAD3_i2c_scl_4_src(data)                                              ((0x000000C0&(data))>>6)
#define SB2_MUXPAD3_get_i2c_scl_4(data)                                              ((0x000000C0&(data))>>6)
#define SB2_MUXPAD3_i2c_sda_4_shift                                                  (4)
#define SB2_MUXPAD3_i2c_sda_4_mask                                                   (0x00000030)
#define SB2_MUXPAD3_i2c_sda_4(data)                                                  (0x00000030&((data)<<4))
#define SB2_MUXPAD3_i2c_sda_4_src(data)                                              ((0x00000030&(data))>>4)
#define SB2_MUXPAD3_get_i2c_sda_4(data)                                              ((0x00000030&(data))>>4)


#define SB2_MUXPAD4                                                                  0x9801A910
#define SB2_MUXPAD4_reg_addr                                                         "0xD801A910"
#define SB2_MUXPAD4_reg                                                              0xD801A910
#define set_SB2_MUXPAD4_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD4_reg)=data)
#define get_SB2_MUXPAD4_reg   (*((volatile unsigned int*) SB2_MUXPAD4_reg))
#define SB2_MUXPAD4_inst_adr                                                         "0x0044"
#define SB2_MUXPAD4_inst                                                             0x0044
#define SB2_MUXPAD4_gpio_9_shift                                                     (22)
#define SB2_MUXPAD4_gpio_9_mask                                                      (0x00C00000)
#define SB2_MUXPAD4_gpio_9(data)                                                     (0x00C00000&((data)<<22))
#define SB2_MUXPAD4_gpio_9_src(data)                                                 ((0x00C00000&(data))>>22)
#define SB2_MUXPAD4_get_gpio_9(data)                                                 ((0x00C00000&(data))>>22)
#define SB2_MUXPAD4_gpio_8_shift                                                     (20)
#define SB2_MUXPAD4_gpio_8_mask                                                      (0x00300000)
#define SB2_MUXPAD4_gpio_8(data)                                                     (0x00300000&((data)<<20))
#define SB2_MUXPAD4_gpio_8_src(data)                                                 ((0x00300000&(data))>>20)
#define SB2_MUXPAD4_get_gpio_8(data)                                                 ((0x00300000&(data))>>20)
#define SB2_MUXPAD4_gpio_7_shift                                                     (18)
#define SB2_MUXPAD4_gpio_7_mask                                                      (0x000C0000)
#define SB2_MUXPAD4_gpio_7(data)                                                     (0x000C0000&((data)<<18))
#define SB2_MUXPAD4_gpio_7_src(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD4_get_gpio_7(data)                                                 ((0x000C0000&(data))>>18)
#define SB2_MUXPAD4_gpio_6_shift                                                     (16)
#define SB2_MUXPAD4_gpio_6_mask                                                      (0x00030000)
#define SB2_MUXPAD4_gpio_6(data)                                                     (0x00030000&((data)<<16))
#define SB2_MUXPAD4_gpio_6_src(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD4_get_gpio_6(data)                                                 ((0x00030000&(data))>>16)
#define SB2_MUXPAD4_gpio_5_shift                                                     (14)
#define SB2_MUXPAD4_gpio_5_mask                                                      (0x0000C000)
#define SB2_MUXPAD4_gpio_5(data)                                                     (0x0000C000&((data)<<14))
#define SB2_MUXPAD4_gpio_5_src(data)                                                 ((0x0000C000&(data))>>14)
#define SB2_MUXPAD4_get_gpio_5(data)                                                 ((0x0000C000&(data))>>14)
#define SB2_MUXPAD4_gpio_4_shift                                                     (12)
#define SB2_MUXPAD4_gpio_4_mask                                                      (0x00003000)
#define SB2_MUXPAD4_gpio_4(data)                                                     (0x00003000&((data)<<12))
#define SB2_MUXPAD4_gpio_4_src(data)                                                 ((0x00003000&(data))>>12)
#define SB2_MUXPAD4_get_gpio_4(data)                                                 ((0x00003000&(data))>>12)
#define SB2_MUXPAD4_gpio_3_shift                                                     (9)
#define SB2_MUXPAD4_gpio_3_mask                                                      (0x00000E00)
#define SB2_MUXPAD4_gpio_3(data)                                                     (0x00000E00&((data)<<9))
#define SB2_MUXPAD4_gpio_3_src(data)                                                 ((0x00000E00&(data))>>9)
#define SB2_MUXPAD4_get_gpio_3(data)                                                 ((0x00000E00&(data))>>9)
#define SB2_MUXPAD4_gpio_2_shift                                                     (6)
#define SB2_MUXPAD4_gpio_2_mask                                                      (0x000001C0)
#define SB2_MUXPAD4_gpio_2(data)                                                     (0x000001C0&((data)<<6))
#define SB2_MUXPAD4_gpio_2_src(data)                                                 ((0x000001C0&(data))>>6)
#define SB2_MUXPAD4_get_gpio_2(data)                                                 ((0x000001C0&(data))>>6)
#define SB2_MUXPAD4_gpio_1_shift                                                     (3)
#define SB2_MUXPAD4_gpio_1_mask                                                      (0x00000038)
#define SB2_MUXPAD4_gpio_1(data)                                                     (0x00000038&((data)<<3))
#define SB2_MUXPAD4_gpio_1_src(data)                                                 ((0x00000038&(data))>>3)
#define SB2_MUXPAD4_get_gpio_1(data)                                                 ((0x00000038&(data))>>3)
#define SB2_MUXPAD4_gpio_0_shift                                                     (0)
#define SB2_MUXPAD4_gpio_0_mask                                                      (0x00000007)
#define SB2_MUXPAD4_gpio_0(data)                                                     (0x00000007&((data)<<0))
#define SB2_MUXPAD4_gpio_0_src(data)                                                 ((0x00000007&(data))>>0)
#define SB2_MUXPAD4_get_gpio_0(data)                                                 ((0x00000007&(data))>>0)


#define SB2_MUXPAD5                                                                  0x9801A914
#define SB2_MUXPAD5_reg_addr                                                         "0xD801A914"
#define SB2_MUXPAD5_reg                                                              0xD801A914
#define set_SB2_MUXPAD5_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD5_reg)=data)
#define get_SB2_MUXPAD5_reg   (*((volatile unsigned int*) SB2_MUXPAD5_reg))
#define SB2_MUXPAD5_inst_adr                                                         "0x0045"
#define SB2_MUXPAD5_inst                                                             0x0045
#define SB2_MUXPAD5_tp1_loc_shift                                                    (8)
#define SB2_MUXPAD5_tp1_loc_mask                                                     (0x00000100)
#define SB2_MUXPAD5_tp1_loc(data)                                                    (0x00000100&((data)<<8))
#define SB2_MUXPAD5_tp1_loc_src(data)                                                ((0x00000100&(data))>>8)
#define SB2_MUXPAD5_get_tp1_loc(data)                                                ((0x00000100&(data))>>8)
#define SB2_MUXPAD5_tp0_loc_shift                                                    (7)
#define SB2_MUXPAD5_tp0_loc_mask                                                     (0x00000080)
#define SB2_MUXPAD5_tp0_loc(data)                                                    (0x00000080&((data)<<7))
#define SB2_MUXPAD5_tp0_loc_src(data)                                                ((0x00000080&(data))>>7)
#define SB2_MUXPAD5_get_tp0_loc(data)                                                ((0x00000080&(data))>>7)
#define SB2_MUXPAD5_debug_p2s_enable_shift                                           (6)
#define SB2_MUXPAD5_debug_p2s_enable_mask                                            (0x00000040)
#define SB2_MUXPAD5_debug_p2s_enable(data)                                           (0x00000040&((data)<<6))
#define SB2_MUXPAD5_debug_p2s_enable_src(data)                                       ((0x00000040&(data))>>6)
#define SB2_MUXPAD5_get_debug_p2s_enable(data)                                       ((0x00000040&(data))>>6)
#define SB2_MUXPAD5_ur1_loc_shift                                                    (4)
#define SB2_MUXPAD5_ur1_loc_mask                                                     (0x00000030)
#define SB2_MUXPAD5_ur1_loc(data)                                                    (0x00000030&((data)<<4))
#define SB2_MUXPAD5_ur1_loc_src(data)                                                ((0x00000030&(data))>>4)
#define SB2_MUXPAD5_get_ur1_loc(data)                                                ((0x00000030&(data))>>4)
#define SB2_MUXPAD5_ao_loc_shift                                                     (2)
#define SB2_MUXPAD5_ao_loc_mask                                                      (0x0000000C)
#define SB2_MUXPAD5_ao_loc(data)                                                     (0x0000000C&((data)<<2))
#define SB2_MUXPAD5_ao_loc_src(data)                                                 ((0x0000000C&(data))>>2)
#define SB2_MUXPAD5_get_ao_loc(data)                                                 ((0x0000000C&(data))>>2)
#define SB2_MUXPAD5_arm_trace_dbg_en_shift                                           (1)
#define SB2_MUXPAD5_arm_trace_dbg_en_mask                                            (0x00000002)
#define SB2_MUXPAD5_arm_trace_dbg_en(data)                                           (0x00000002&((data)<<1))
#define SB2_MUXPAD5_arm_trace_dbg_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_MUXPAD5_get_arm_trace_dbg_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_MUXPAD5_sf_en_shift                                                      (0)
#define SB2_MUXPAD5_sf_en_mask                                                       (0x00000001)
#define SB2_MUXPAD5_sf_en(data)                                                      (0x00000001&((data)<<0))
#define SB2_MUXPAD5_sf_en_src(data)                                                  ((0x00000001&(data))>>0)
#define SB2_MUXPAD5_get_sf_en(data)                                                  ((0x00000001&(data))>>0)


#define SB2_PFUNC_TP0                                                                0x9801A928
#define SB2_PFUNC_TP0_reg_addr                                                       "0xD801A928"
#define SB2_PFUNC_TP0_reg                                                            0xD801A928
#define set_SB2_PFUNC_TP0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_TP0_reg)=data)
#define get_SB2_PFUNC_TP0_reg   (*((volatile unsigned int*) SB2_PFUNC_TP0_reg))
#define SB2_PFUNC_TP0_inst_adr                                                       "0x004A"
#define SB2_PFUNC_TP0_inst                                                           0x004A
#define SB2_PFUNC_TP0_tp0_data_smt_shift                                             (15)
#define SB2_PFUNC_TP0_tp0_data_smt_mask                                              (0x00008000)
#define SB2_PFUNC_TP0_tp0_data_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_TP0_tp0_data_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP0_get_tp0_data_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP0_tp0_data_e2_shift                                              (14)
#define SB2_PFUNC_TP0_tp0_data_e2_mask                                               (0x00004000)
#define SB2_PFUNC_TP0_tp0_data_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_TP0_tp0_data_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP0_get_tp0_data_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP0_tp0_data_pud_en_shift                                          (13)
#define SB2_PFUNC_TP0_tp0_data_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_TP0_tp0_data_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_TP0_tp0_data_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP0_get_tp0_data_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP0_tp0_data_pud_sel_shift                                         (12)
#define SB2_PFUNC_TP0_tp0_data_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_TP0_tp0_data_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_TP0_tp0_data_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP0_get_tp0_data_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP0_tp0_valid_smt_shift                                            (11)
#define SB2_PFUNC_TP0_tp0_valid_smt_mask                                             (0x00000800)
#define SB2_PFUNC_TP0_tp0_valid_smt(data)                                            (0x00000800&((data)<<11))
#define SB2_PFUNC_TP0_tp0_valid_smt_src(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP0_get_tp0_valid_smt(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP0_tp0_valid_e2_shift                                             (10)
#define SB2_PFUNC_TP0_tp0_valid_e2_mask                                              (0x00000400)
#define SB2_PFUNC_TP0_tp0_valid_e2(data)                                             (0x00000400&((data)<<10))
#define SB2_PFUNC_TP0_tp0_valid_e2_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP0_get_tp0_valid_e2(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP0_tp0_valid_pud_en_shift                                         (9)
#define SB2_PFUNC_TP0_tp0_valid_pud_en_mask                                          (0x00000200)
#define SB2_PFUNC_TP0_tp0_valid_pud_en(data)                                         (0x00000200&((data)<<9))
#define SB2_PFUNC_TP0_tp0_valid_pud_en_src(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP0_get_tp0_valid_pud_en(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_shift                                        (8)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_mask                                         (0x00000100)
#define SB2_PFUNC_TP0_tp0_valid_pud_sel(data)                                        (0x00000100&((data)<<8))
#define SB2_PFUNC_TP0_tp0_valid_pud_sel_src(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP0_get_tp0_valid_pud_sel(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP0_tp0_sync_smt_shift                                             (7)
#define SB2_PFUNC_TP0_tp0_sync_smt_mask                                              (0x00000080)
#define SB2_PFUNC_TP0_tp0_sync_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_TP0_tp0_sync_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP0_get_tp0_sync_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP0_tp0_sync_e2_shift                                              (6)
#define SB2_PFUNC_TP0_tp0_sync_e2_mask                                               (0x00000040)
#define SB2_PFUNC_TP0_tp0_sync_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_TP0_tp0_sync_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP0_get_tp0_sync_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP0_tp0_sync_pud_en_shift                                          (5)
#define SB2_PFUNC_TP0_tp0_sync_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_TP0_tp0_sync_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_TP0_tp0_sync_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP0_get_tp0_sync_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_shift                                         (4)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_TP0_tp0_sync_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_TP0_tp0_sync_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP0_get_tp0_sync_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP0_tp0_clk_smt_shift                                              (3)
#define SB2_PFUNC_TP0_tp0_clk_smt_mask                                               (0x00000008)
#define SB2_PFUNC_TP0_tp0_clk_smt(data)                                              (0x00000008&((data)<<3))
#define SB2_PFUNC_TP0_tp0_clk_smt_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP0_get_tp0_clk_smt(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP0_tp0_clk_e2_shift                                               (2)
#define SB2_PFUNC_TP0_tp0_clk_e2_mask                                                (0x00000004)
#define SB2_PFUNC_TP0_tp0_clk_e2(data)                                               (0x00000004&((data)<<2))
#define SB2_PFUNC_TP0_tp0_clk_e2_src(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP0_get_tp0_clk_e2(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP0_tp0_clk_pud_en_shift                                           (1)
#define SB2_PFUNC_TP0_tp0_clk_pud_en_mask                                            (0x00000002)
#define SB2_PFUNC_TP0_tp0_clk_pud_en(data)                                           (0x00000002&((data)<<1))
#define SB2_PFUNC_TP0_tp0_clk_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP0_get_tp0_clk_pud_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_shift                                          (0)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_mask                                           (0x00000001)
#define SB2_PFUNC_TP0_tp0_clk_pud_sel(data)                                          (0x00000001&((data)<<0))
#define SB2_PFUNC_TP0_tp0_clk_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define SB2_PFUNC_TP0_get_tp0_clk_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define SB2_PFUNC_TP1                                                                0x9801A92C
#define SB2_PFUNC_TP1_reg_addr                                                       "0xD801A92C"
#define SB2_PFUNC_TP1_reg                                                            0xD801A92C
#define set_SB2_PFUNC_TP1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_TP1_reg)=data)
#define get_SB2_PFUNC_TP1_reg   (*((volatile unsigned int*) SB2_PFUNC_TP1_reg))
#define SB2_PFUNC_TP1_inst_adr                                                       "0x004B"
#define SB2_PFUNC_TP1_inst                                                           0x004B
#define SB2_PFUNC_TP1_tp1_data_smt_shift                                             (15)
#define SB2_PFUNC_TP1_tp1_data_smt_mask                                              (0x00008000)
#define SB2_PFUNC_TP1_tp1_data_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_TP1_tp1_data_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP1_get_tp1_data_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_TP1_tp1_data_e2_shift                                              (14)
#define SB2_PFUNC_TP1_tp1_data_e2_mask                                               (0x00004000)
#define SB2_PFUNC_TP1_tp1_data_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_TP1_tp1_data_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP1_get_tp1_data_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_TP1_tp1_data_pud_en_shift                                          (13)
#define SB2_PFUNC_TP1_tp1_data_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_TP1_tp1_data_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_TP1_tp1_data_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP1_get_tp1_data_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_TP1_tp1_data_pud_sel_shift                                         (12)
#define SB2_PFUNC_TP1_tp1_data_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_TP1_tp1_data_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_TP1_tp1_data_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP1_get_tp1_data_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_TP1_tp1_valid_smt_shift                                            (11)
#define SB2_PFUNC_TP1_tp1_valid_smt_mask                                             (0x00000800)
#define SB2_PFUNC_TP1_tp1_valid_smt(data)                                            (0x00000800&((data)<<11))
#define SB2_PFUNC_TP1_tp1_valid_smt_src(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP1_get_tp1_valid_smt(data)                                        ((0x00000800&(data))>>11)
#define SB2_PFUNC_TP1_tp1_valid_e2_shift                                             (10)
#define SB2_PFUNC_TP1_tp1_valid_e2_mask                                              (0x00000400)
#define SB2_PFUNC_TP1_tp1_valid_e2(data)                                             (0x00000400&((data)<<10))
#define SB2_PFUNC_TP1_tp1_valid_e2_src(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP1_get_tp1_valid_e2(data)                                         ((0x00000400&(data))>>10)
#define SB2_PFUNC_TP1_tp1_valid_pud_en_shift                                         (9)
#define SB2_PFUNC_TP1_tp1_valid_pud_en_mask                                          (0x00000200)
#define SB2_PFUNC_TP1_tp1_valid_pud_en(data)                                         (0x00000200&((data)<<9))
#define SB2_PFUNC_TP1_tp1_valid_pud_en_src(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP1_get_tp1_valid_pud_en(data)                                     ((0x00000200&(data))>>9)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_shift                                        (8)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_mask                                         (0x00000100)
#define SB2_PFUNC_TP1_tp1_valid_pud_sel(data)                                        (0x00000100&((data)<<8))
#define SB2_PFUNC_TP1_tp1_valid_pud_sel_src(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP1_get_tp1_valid_pud_sel(data)                                    ((0x00000100&(data))>>8)
#define SB2_PFUNC_TP1_tp1_sync_smt_shift                                             (7)
#define SB2_PFUNC_TP1_tp1_sync_smt_mask                                              (0x00000080)
#define SB2_PFUNC_TP1_tp1_sync_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_TP1_tp1_sync_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP1_get_tp1_sync_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_TP1_tp1_sync_e2_shift                                              (6)
#define SB2_PFUNC_TP1_tp1_sync_e2_mask                                               (0x00000040)
#define SB2_PFUNC_TP1_tp1_sync_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_TP1_tp1_sync_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP1_get_tp1_sync_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_TP1_tp1_sync_pud_en_shift                                          (5)
#define SB2_PFUNC_TP1_tp1_sync_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_TP1_tp1_sync_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_TP1_tp1_sync_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP1_get_tp1_sync_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_shift                                         (4)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_TP1_tp1_sync_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_TP1_tp1_sync_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP1_get_tp1_sync_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_TP1_tp1_clk_smt_shift                                              (3)
#define SB2_PFUNC_TP1_tp1_clk_smt_mask                                               (0x00000008)
#define SB2_PFUNC_TP1_tp1_clk_smt(data)                                              (0x00000008&((data)<<3))
#define SB2_PFUNC_TP1_tp1_clk_smt_src(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP1_get_tp1_clk_smt(data)                                          ((0x00000008&(data))>>3)
#define SB2_PFUNC_TP1_tp1_clk_e2_shift                                               (2)
#define SB2_PFUNC_TP1_tp1_clk_e2_mask                                                (0x00000004)
#define SB2_PFUNC_TP1_tp1_clk_e2(data)                                               (0x00000004&((data)<<2))
#define SB2_PFUNC_TP1_tp1_clk_e2_src(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP1_get_tp1_clk_e2(data)                                           ((0x00000004&(data))>>2)
#define SB2_PFUNC_TP1_tp1_clk_pud_en_shift                                           (1)
#define SB2_PFUNC_TP1_tp1_clk_pud_en_mask                                            (0x00000002)
#define SB2_PFUNC_TP1_tp1_clk_pud_en(data)                                           (0x00000002&((data)<<1))
#define SB2_PFUNC_TP1_tp1_clk_pud_en_src(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP1_get_tp1_clk_pud_en(data)                                       ((0x00000002&(data))>>1)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_shift                                          (0)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_mask                                           (0x00000001)
#define SB2_PFUNC_TP1_tp1_clk_pud_sel(data)                                          (0x00000001&((data)<<0))
#define SB2_PFUNC_TP1_tp1_clk_pud_sel_src(data)                                      ((0x00000001&(data))>>0)
#define SB2_PFUNC_TP1_get_tp1_clk_pud_sel(data)                                      ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC0                                                              0x9801A930
#define SB2_PFUNC_MISC0_reg_addr                                                     "0xD801A930"
#define SB2_PFUNC_MISC0_reg                                                          0xD801A930
#define set_SB2_PFUNC_MISC0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC0_reg)=data)
#define get_SB2_PFUNC_MISC0_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC0_reg))
#define SB2_PFUNC_MISC0_inst_adr                                                     "0x004C"
#define SB2_PFUNC_MISC0_inst                                                         0x004C
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_shift                                          (23)
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_mask                                           (0x00800000)
#define SB2_PFUNC_MISC0_i2c_scl_5_smt(data)                                          (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC0_i2c_scl_5_smt_src(data)                                      ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_smt(data)                                      ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_shift                                           (22)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_mask                                            (0x00400000)
#define SB2_PFUNC_MISC0_i2c_scl_5_e2(data)                                           (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC0_i2c_scl_5_e2_src(data)                                       ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_e2(data)                                       ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_shift                                       (21)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_mask                                        (0x00200000)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en(data)                                       (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_en_src(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_pud_en(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_shift                                      (20)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_mask                                       (0x00100000)
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel(data)                                      (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC0_i2c_scl_5_pud_sel_src(data)                                  ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC0_get_i2c_scl_5_pud_sel(data)                                  ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_shift                                          (19)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_mask                                           (0x00080000)
#define SB2_PFUNC_MISC0_i2c_sda_5_smt(data)                                          (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC0_i2c_sda_5_smt_src(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_smt(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_shift                                           (18)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_mask                                            (0x00040000)
#define SB2_PFUNC_MISC0_i2c_sda_5_e2(data)                                           (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC0_i2c_sda_5_e2_src(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_e2(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_shift                                       (17)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_mask                                        (0x00020000)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en(data)                                       (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_en_src(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_pud_en(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_shift                                      (16)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_mask                                       (0x00010000)
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel(data)                                      (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC0_i2c_sda_5_pud_sel_src(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC0_get_i2c_sda_5_pud_sel(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_shift                                          (15)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_mask                                           (0x00008000)
#define SB2_PFUNC_MISC0_i2c_scl_4_smt(data)                                          (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC0_i2c_scl_4_smt_src(data)                                      ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_smt(data)                                      ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_shift                                           (14)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_mask                                            (0x00004000)
#define SB2_PFUNC_MISC0_i2c_scl_4_e2(data)                                           (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC0_i2c_scl_4_e2_src(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_e2(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_shift                                       (13)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_mask                                        (0x00002000)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en(data)                                       (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_en_src(data)                                   ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_pud_en(data)                                   ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_shift                                      (12)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_mask                                       (0x00001000)
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel(data)                                      (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC0_i2c_scl_4_pud_sel_src(data)                                  ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC0_get_i2c_scl_4_pud_sel(data)                                  ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_shift                                          (11)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_mask                                           (0x00000800)
#define SB2_PFUNC_MISC0_i2c_sda_4_smt(data)                                          (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC0_i2c_sda_4_smt_src(data)                                      ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_smt(data)                                      ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_shift                                           (10)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_mask                                            (0x00000400)
#define SB2_PFUNC_MISC0_i2c_sda_4_e2(data)                                           (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC0_i2c_sda_4_e2_src(data)                                       ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_e2(data)                                       ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_shift                                       (9)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_mask                                        (0x00000200)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en(data)                                       (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_en_src(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_pud_en(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_shift                                      (8)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_mask                                       (0x00000100)
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel(data)                                      (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC0_i2c_sda_4_pud_sel_src(data)                                  ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC0_get_i2c_sda_4_pud_sel(data)                                  ((0x00000100&(data))>>8)


#define SB2_PFUNC_MISC1                                                              0x9801A934
#define SB2_PFUNC_MISC1_reg_addr                                                     "0xD801A934"
#define SB2_PFUNC_MISC1_reg                                                          0xD801A934
#define set_SB2_PFUNC_MISC1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC1_reg)=data)
#define get_SB2_PFUNC_MISC1_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC1_reg))
#define SB2_PFUNC_MISC1_inst_adr                                                     "0x004D"
#define SB2_PFUNC_MISC1_inst                                                         0x004D
#define SB2_PFUNC_MISC1_gpio_7_smt_shift                                             (31)
#define SB2_PFUNC_MISC1_gpio_7_smt_mask                                              (0x80000000)
#define SB2_PFUNC_MISC1_gpio_7_smt(data)                                             (0x80000000&((data)<<31))
#define SB2_PFUNC_MISC1_gpio_7_smt_src(data)                                         ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC1_get_gpio_7_smt(data)                                         ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC1_gpio_7_e2_shift                                              (30)
#define SB2_PFUNC_MISC1_gpio_7_e2_mask                                               (0x40000000)
#define SB2_PFUNC_MISC1_gpio_7_e2(data)                                              (0x40000000&((data)<<30))
#define SB2_PFUNC_MISC1_gpio_7_e2_src(data)                                          ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC1_get_gpio_7_e2(data)                                          ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC1_gpio_7_pud_en_shift                                          (29)
#define SB2_PFUNC_MISC1_gpio_7_pud_en_mask                                           (0x20000000)
#define SB2_PFUNC_MISC1_gpio_7_pud_en(data)                                          (0x20000000&((data)<<29))
#define SB2_PFUNC_MISC1_gpio_7_pud_en_src(data)                                      ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC1_get_gpio_7_pud_en(data)                                      ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_shift                                         (28)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_mask                                          (0x10000000)
#define SB2_PFUNC_MISC1_gpio_7_pud_sel(data)                                         (0x10000000&((data)<<28))
#define SB2_PFUNC_MISC1_gpio_7_pud_sel_src(data)                                     ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC1_get_gpio_7_pud_sel(data)                                     ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC1_gpio_6_smt_shift                                             (27)
#define SB2_PFUNC_MISC1_gpio_6_smt_mask                                              (0x08000000)
#define SB2_PFUNC_MISC1_gpio_6_smt(data)                                             (0x08000000&((data)<<27))
#define SB2_PFUNC_MISC1_gpio_6_smt_src(data)                                         ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC1_get_gpio_6_smt(data)                                         ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC1_gpio_6_e2_shift                                              (26)
#define SB2_PFUNC_MISC1_gpio_6_e2_mask                                               (0x04000000)
#define SB2_PFUNC_MISC1_gpio_6_e2(data)                                              (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC1_gpio_6_e2_src(data)                                          ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC1_get_gpio_6_e2(data)                                          ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC1_gpio_6_pud_en_shift                                          (25)
#define SB2_PFUNC_MISC1_gpio_6_pud_en_mask                                           (0x02000000)
#define SB2_PFUNC_MISC1_gpio_6_pud_en(data)                                          (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC1_gpio_6_pud_en_src(data)                                      ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC1_get_gpio_6_pud_en(data)                                      ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_shift                                         (24)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_mask                                          (0x01000000)
#define SB2_PFUNC_MISC1_gpio_6_pud_sel(data)                                         (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC1_gpio_6_pud_sel_src(data)                                     ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC1_get_gpio_6_pud_sel(data)                                     ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC1_gpio_5_smt_shift                                             (23)
#define SB2_PFUNC_MISC1_gpio_5_smt_mask                                              (0x00800000)
#define SB2_PFUNC_MISC1_gpio_5_smt(data)                                             (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC1_gpio_5_smt_src(data)                                         ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC1_get_gpio_5_smt(data)                                         ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC1_gpio_5_e2_shift                                              (22)
#define SB2_PFUNC_MISC1_gpio_5_e2_mask                                               (0x00400000)
#define SB2_PFUNC_MISC1_gpio_5_e2(data)                                              (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC1_gpio_5_e2_src(data)                                          ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC1_get_gpio_5_e2(data)                                          ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC1_gpio_5_pud_en_shift                                          (21)
#define SB2_PFUNC_MISC1_gpio_5_pud_en_mask                                           (0x00200000)
#define SB2_PFUNC_MISC1_gpio_5_pud_en(data)                                          (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC1_gpio_5_pud_en_src(data)                                      ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC1_get_gpio_5_pud_en(data)                                      ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_shift                                         (20)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_mask                                          (0x00100000)
#define SB2_PFUNC_MISC1_gpio_5_pud_sel(data)                                         (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC1_gpio_5_pud_sel_src(data)                                     ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC1_get_gpio_5_pud_sel(data)                                     ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC1_gpio_4_smt_shift                                             (19)
#define SB2_PFUNC_MISC1_gpio_4_smt_mask                                              (0x00080000)
#define SB2_PFUNC_MISC1_gpio_4_smt(data)                                             (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC1_gpio_4_smt_src(data)                                         ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC1_get_gpio_4_smt(data)                                         ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC1_gpio_4_e2_shift                                              (18)
#define SB2_PFUNC_MISC1_gpio_4_e2_mask                                               (0x00040000)
#define SB2_PFUNC_MISC1_gpio_4_e2(data)                                              (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC1_gpio_4_e2_src(data)                                          ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC1_get_gpio_4_e2(data)                                          ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC1_gpio_4_pud_en_shift                                          (17)
#define SB2_PFUNC_MISC1_gpio_4_pud_en_mask                                           (0x00020000)
#define SB2_PFUNC_MISC1_gpio_4_pud_en(data)                                          (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC1_gpio_4_pud_en_src(data)                                      ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC1_get_gpio_4_pud_en(data)                                      ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_shift                                         (16)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_mask                                          (0x00010000)
#define SB2_PFUNC_MISC1_gpio_4_pud_sel(data)                                         (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC1_gpio_4_pud_sel_src(data)                                     ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC1_get_gpio_4_pud_sel(data)                                     ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC1_gpio_3_smt_shift                                             (15)
#define SB2_PFUNC_MISC1_gpio_3_smt_mask                                              (0x00008000)
#define SB2_PFUNC_MISC1_gpio_3_smt(data)                                             (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC1_gpio_3_smt_src(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC1_get_gpio_3_smt(data)                                         ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC1_gpio_3_e2_shift                                              (14)
#define SB2_PFUNC_MISC1_gpio_3_e2_mask                                               (0x00004000)
#define SB2_PFUNC_MISC1_gpio_3_e2(data)                                              (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC1_gpio_3_e2_src(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC1_get_gpio_3_e2(data)                                          ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC1_gpio_3_pud_en_shift                                          (13)
#define SB2_PFUNC_MISC1_gpio_3_pud_en_mask                                           (0x00002000)
#define SB2_PFUNC_MISC1_gpio_3_pud_en(data)                                          (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC1_gpio_3_pud_en_src(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC1_get_gpio_3_pud_en(data)                                      ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_shift                                         (12)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_mask                                          (0x00001000)
#define SB2_PFUNC_MISC1_gpio_3_pud_sel(data)                                         (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC1_gpio_3_pud_sel_src(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC1_get_gpio_3_pud_sel(data)                                     ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC1_gpio_2_smt_shift                                             (11)
#define SB2_PFUNC_MISC1_gpio_2_smt_mask                                              (0x00000800)
#define SB2_PFUNC_MISC1_gpio_2_smt(data)                                             (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC1_gpio_2_smt_src(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC1_get_gpio_2_smt(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC1_gpio_2_e2_shift                                              (10)
#define SB2_PFUNC_MISC1_gpio_2_e2_mask                                               (0x00000400)
#define SB2_PFUNC_MISC1_gpio_2_e2(data)                                              (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC1_gpio_2_e2_src(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC1_get_gpio_2_e2(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC1_gpio_2_pud_en_shift                                          (9)
#define SB2_PFUNC_MISC1_gpio_2_pud_en_mask                                           (0x00000200)
#define SB2_PFUNC_MISC1_gpio_2_pud_en(data)                                          (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC1_gpio_2_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC1_get_gpio_2_pud_en(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_shift                                         (8)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_mask                                          (0x00000100)
#define SB2_PFUNC_MISC1_gpio_2_pud_sel(data)                                         (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC1_gpio_2_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC1_get_gpio_2_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC1_gpio_1_smt_shift                                             (7)
#define SB2_PFUNC_MISC1_gpio_1_smt_mask                                              (0x00000080)
#define SB2_PFUNC_MISC1_gpio_1_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC1_gpio_1_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC1_get_gpio_1_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC1_gpio_1_e2_shift                                              (6)
#define SB2_PFUNC_MISC1_gpio_1_e2_mask                                               (0x00000040)
#define SB2_PFUNC_MISC1_gpio_1_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC1_gpio_1_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC1_get_gpio_1_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC1_gpio_1_pud_en_shift                                          (5)
#define SB2_PFUNC_MISC1_gpio_1_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_MISC1_gpio_1_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC1_gpio_1_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC1_get_gpio_1_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_shift                                         (4)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_MISC1_gpio_1_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC1_gpio_1_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC1_get_gpio_1_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC1_gpio_0_smt_shift                                             (3)
#define SB2_PFUNC_MISC1_gpio_0_smt_mask                                              (0x00000008)
#define SB2_PFUNC_MISC1_gpio_0_smt(data)                                             (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC1_gpio_0_smt_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC1_get_gpio_0_smt(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC1_gpio_0_e2_shift                                              (2)
#define SB2_PFUNC_MISC1_gpio_0_e2_mask                                               (0x00000004)
#define SB2_PFUNC_MISC1_gpio_0_e2(data)                                              (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC1_gpio_0_e2_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC1_get_gpio_0_e2(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC1_gpio_0_pud_en_shift                                          (1)
#define SB2_PFUNC_MISC1_gpio_0_pud_en_mask                                           (0x00000002)
#define SB2_PFUNC_MISC1_gpio_0_pud_en(data)                                          (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC1_gpio_0_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC1_get_gpio_0_pud_en(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_shift                                         (0)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_mask                                          (0x00000001)
#define SB2_PFUNC_MISC1_gpio_0_pud_sel(data)                                         (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC1_gpio_0_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC1_get_gpio_0_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC2                                                              0x9801A938
#define SB2_PFUNC_MISC2_reg_addr                                                     "0xD801A938"
#define SB2_PFUNC_MISC2_reg                                                          0xD801A938
#define set_SB2_PFUNC_MISC2_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC2_reg)=data)
#define get_SB2_PFUNC_MISC2_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC2_reg))
#define SB2_PFUNC_MISC2_inst_adr                                                     "0x004E"
#define SB2_PFUNC_MISC2_inst                                                         0x004E
#define SB2_PFUNC_MISC2_sensor_cko1_smt_shift                                        (31)
#define SB2_PFUNC_MISC2_sensor_cko1_smt_mask                                         (0x80000000)
#define SB2_PFUNC_MISC2_sensor_cko1_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_MISC2_sensor_cko1_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC2_get_sensor_cko1_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_MISC2_sensor_cko1_e2_shift                                         (30)
#define SB2_PFUNC_MISC2_sensor_cko1_e2_mask                                          (0x40000000)
#define SB2_PFUNC_MISC2_sensor_cko1_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_MISC2_sensor_cko1_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC2_get_sensor_cko1_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_shift                                     (29)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_MISC2_sensor_cko1_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC2_get_sensor_cko1_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_shift                                    (28)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_MISC2_sensor_cko1_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC2_get_sensor_cko1_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_MISC2_sensor_cko0_smt_shift                                        (27)
#define SB2_PFUNC_MISC2_sensor_cko0_smt_mask                                         (0x08000000)
#define SB2_PFUNC_MISC2_sensor_cko0_smt(data)                                        (0x08000000&((data)<<27))
#define SB2_PFUNC_MISC2_sensor_cko0_smt_src(data)                                    ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC2_get_sensor_cko0_smt(data)                                    ((0x08000000&(data))>>27)
#define SB2_PFUNC_MISC2_sensor_cko0_e2_shift                                         (26)
#define SB2_PFUNC_MISC2_sensor_cko0_e2_mask                                          (0x04000000)
#define SB2_PFUNC_MISC2_sensor_cko0_e2(data)                                         (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC2_sensor_cko0_e2_src(data)                                     ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC2_get_sensor_cko0_e2(data)                                     ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_shift                                     (25)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_mask                                      (0x02000000)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en(data)                                     (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC2_sensor_cko0_pud_en_src(data)                                 ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC2_get_sensor_cko0_pud_en(data)                                 ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_shift                                    (24)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_mask                                     (0x01000000)
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel(data)                                    (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC2_sensor_cko0_pud_sel_src(data)                                ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC2_get_sensor_cko0_pud_sel(data)                                ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC2_sensor_rst_smt_shift                                         (23)
#define SB2_PFUNC_MISC2_sensor_rst_smt_mask                                          (0x00800000)
#define SB2_PFUNC_MISC2_sensor_rst_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC2_sensor_rst_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC2_get_sensor_rst_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC2_sensor_rst_e2_shift                                          (22)
#define SB2_PFUNC_MISC2_sensor_rst_e2_mask                                           (0x00400000)
#define SB2_PFUNC_MISC2_sensor_rst_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC2_sensor_rst_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC2_get_sensor_rst_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_shift                                      (21)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_MISC2_sensor_rst_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC2_sensor_rst_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC2_get_sensor_rst_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_shift                                     (20)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC2_sensor_rst_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC2_get_sensor_rst_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC2_sensor_stb1_smt_shift                                        (19)
#define SB2_PFUNC_MISC2_sensor_stb1_smt_mask                                         (0x00080000)
#define SB2_PFUNC_MISC2_sensor_stb1_smt(data)                                        (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC2_sensor_stb1_smt_src(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC2_get_sensor_stb1_smt(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC2_sensor_stb1_e2_shift                                         (18)
#define SB2_PFUNC_MISC2_sensor_stb1_e2_mask                                          (0x00040000)
#define SB2_PFUNC_MISC2_sensor_stb1_e2(data)                                         (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC2_sensor_stb1_e2_src(data)                                     ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC2_get_sensor_stb1_e2(data)                                     ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_shift                                     (17)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_mask                                      (0x00020000)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en(data)                                     (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC2_sensor_stb1_pud_en_src(data)                                 ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC2_get_sensor_stb1_pud_en(data)                                 ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_shift                                    (16)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_mask                                     (0x00010000)
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel(data)                                    (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC2_sensor_stb1_pud_sel_src(data)                                ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC2_get_sensor_stb1_pud_sel(data)                                ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC2_sensor_stb0_smt_shift                                        (15)
#define SB2_PFUNC_MISC2_sensor_stb0_smt_mask                                         (0x00008000)
#define SB2_PFUNC_MISC2_sensor_stb0_smt(data)                                        (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC2_sensor_stb0_smt_src(data)                                    ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC2_get_sensor_stb0_smt(data)                                    ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC2_sensor_stb0_e2_shift                                         (14)
#define SB2_PFUNC_MISC2_sensor_stb0_e2_mask                                          (0x00004000)
#define SB2_PFUNC_MISC2_sensor_stb0_e2(data)                                         (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC2_sensor_stb0_e2_src(data)                                     ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC2_get_sensor_stb0_e2(data)                                     ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_shift                                     (13)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_mask                                      (0x00002000)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en(data)                                     (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC2_sensor_stb0_pud_en_src(data)                                 ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC2_get_sensor_stb0_pud_en(data)                                 ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_shift                                    (12)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_mask                                     (0x00001000)
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel(data)                                    (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC2_sensor_stb0_pud_sel_src(data)                                ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC2_get_sensor_stb0_pud_sel(data)                                ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC2_usb_id_smt_shift                                             (11)
#define SB2_PFUNC_MISC2_usb_id_smt_mask                                              (0x00000800)
#define SB2_PFUNC_MISC2_usb_id_smt(data)                                             (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC2_usb_id_smt_src(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC2_get_usb_id_smt(data)                                         ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC2_usb_id_e2_shift                                              (10)
#define SB2_PFUNC_MISC2_usb_id_e2_mask                                               (0x00000400)
#define SB2_PFUNC_MISC2_usb_id_e2(data)                                              (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC2_usb_id_e2_src(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC2_get_usb_id_e2(data)                                          ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC2_usb_id_pud_en_shift                                          (9)
#define SB2_PFUNC_MISC2_usb_id_pud_en_mask                                           (0x00000200)
#define SB2_PFUNC_MISC2_usb_id_pud_en(data)                                          (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC2_usb_id_pud_en_src(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC2_get_usb_id_pud_en(data)                                      ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC2_usb_id_pud_sel_shift                                         (8)
#define SB2_PFUNC_MISC2_usb_id_pud_sel_mask                                          (0x00000100)
#define SB2_PFUNC_MISC2_usb_id_pud_sel(data)                                         (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC2_usb_id_pud_sel_src(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC2_get_usb_id_pud_sel(data)                                     ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC2_gpio_9_smt_shift                                             (7)
#define SB2_PFUNC_MISC2_gpio_9_smt_mask                                              (0x00000080)
#define SB2_PFUNC_MISC2_gpio_9_smt(data)                                             (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC2_gpio_9_smt_src(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC2_get_gpio_9_smt(data)                                         ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC2_gpio_9_e2_shift                                              (6)
#define SB2_PFUNC_MISC2_gpio_9_e2_mask                                               (0x00000040)
#define SB2_PFUNC_MISC2_gpio_9_e2(data)                                              (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC2_gpio_9_e2_src(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC2_get_gpio_9_e2(data)                                          ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC2_gpio_9_pud_en_shift                                          (5)
#define SB2_PFUNC_MISC2_gpio_9_pud_en_mask                                           (0x00000020)
#define SB2_PFUNC_MISC2_gpio_9_pud_en(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC2_gpio_9_pud_en_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC2_get_gpio_9_pud_en(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_shift                                         (4)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_mask                                          (0x00000010)
#define SB2_PFUNC_MISC2_gpio_9_pud_sel(data)                                         (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC2_gpio_9_pud_sel_src(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC2_get_gpio_9_pud_sel(data)                                     ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC2_gpio_8_smt_shift                                             (3)
#define SB2_PFUNC_MISC2_gpio_8_smt_mask                                              (0x00000008)
#define SB2_PFUNC_MISC2_gpio_8_smt(data)                                             (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC2_gpio_8_smt_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC2_get_gpio_8_smt(data)                                         ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC2_gpio_8_e2_shift                                              (2)
#define SB2_PFUNC_MISC2_gpio_8_e2_mask                                               (0x00000004)
#define SB2_PFUNC_MISC2_gpio_8_e2(data)                                              (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC2_gpio_8_e2_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC2_get_gpio_8_e2(data)                                          ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC2_gpio_8_pud_en_shift                                          (1)
#define SB2_PFUNC_MISC2_gpio_8_pud_en_mask                                           (0x00000002)
#define SB2_PFUNC_MISC2_gpio_8_pud_en(data)                                          (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC2_gpio_8_pud_en_src(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC2_get_gpio_8_pud_en(data)                                      ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_shift                                         (0)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_mask                                          (0x00000001)
#define SB2_PFUNC_MISC2_gpio_8_pud_sel(data)                                         (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC2_gpio_8_pud_sel_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC2_get_gpio_8_pud_sel(data)                                     ((0x00000001&(data))>>0)


#define SB2_PFUNC_MISC3                                                              0x9801A93C
#define SB2_PFUNC_MISC3_reg_addr                                                     "0xD801A93C"
#define SB2_PFUNC_MISC3_reg                                                          0xD801A93C
#define set_SB2_PFUNC_MISC3_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_MISC3_reg)=data)
#define get_SB2_PFUNC_MISC3_reg   (*((volatile unsigned int*) SB2_PFUNC_MISC3_reg))
#define SB2_PFUNC_MISC3_inst_adr                                                     "0x004F"
#define SB2_PFUNC_MISC3_inst                                                         0x004F
#define SB2_PFUNC_MISC3_boption4_smt_shift                                           (26)
#define SB2_PFUNC_MISC3_boption4_smt_mask                                            (0x04000000)
#define SB2_PFUNC_MISC3_boption4_smt(data)                                           (0x04000000&((data)<<26))
#define SB2_PFUNC_MISC3_boption4_smt_src(data)                                       ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC3_get_boption4_smt(data)                                       ((0x04000000&(data))>>26)
#define SB2_PFUNC_MISC3_boption4_pud_en_shift                                        (25)
#define SB2_PFUNC_MISC3_boption4_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_MISC3_boption4_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_MISC3_boption4_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC3_get_boption4_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_MISC3_boption4_pud_sel_shift                                       (24)
#define SB2_PFUNC_MISC3_boption4_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_MISC3_boption4_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_MISC3_boption4_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC3_get_boption4_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_MISC3_boption3_smt_shift                                           (23)
#define SB2_PFUNC_MISC3_boption3_smt_mask                                            (0x00800000)
#define SB2_PFUNC_MISC3_boption3_smt(data)                                           (0x00800000&((data)<<23))
#define SB2_PFUNC_MISC3_boption3_smt_src(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC3_get_boption3_smt(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_MISC3_boption3_pud_en_shift                                        (22)
#define SB2_PFUNC_MISC3_boption3_pud_en_mask                                         (0x00400000)
#define SB2_PFUNC_MISC3_boption3_pud_en(data)                                        (0x00400000&((data)<<22))
#define SB2_PFUNC_MISC3_boption3_pud_en_src(data)                                    ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC3_get_boption3_pud_en(data)                                    ((0x00400000&(data))>>22)
#define SB2_PFUNC_MISC3_boption3_pud_sel_shift                                       (21)
#define SB2_PFUNC_MISC3_boption3_pud_sel_mask                                        (0x00200000)
#define SB2_PFUNC_MISC3_boption3_pud_sel(data)                                       (0x00200000&((data)<<21))
#define SB2_PFUNC_MISC3_boption3_pud_sel_src(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC3_get_boption3_pud_sel(data)                                   ((0x00200000&(data))>>21)
#define SB2_PFUNC_MISC3_boption1_smt_shift                                           (20)
#define SB2_PFUNC_MISC3_boption1_smt_mask                                            (0x00100000)
#define SB2_PFUNC_MISC3_boption1_smt(data)                                           (0x00100000&((data)<<20))
#define SB2_PFUNC_MISC3_boption1_smt_src(data)                                       ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC3_get_boption1_smt(data)                                       ((0x00100000&(data))>>20)
#define SB2_PFUNC_MISC3_boption1_pud_en_shift                                        (19)
#define SB2_PFUNC_MISC3_boption1_pud_en_mask                                         (0x00080000)
#define SB2_PFUNC_MISC3_boption1_pud_en(data)                                        (0x00080000&((data)<<19))
#define SB2_PFUNC_MISC3_boption1_pud_en_src(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC3_get_boption1_pud_en(data)                                    ((0x00080000&(data))>>19)
#define SB2_PFUNC_MISC3_boption1_pud_sel_shift                                       (18)
#define SB2_PFUNC_MISC3_boption1_pud_sel_mask                                        (0x00040000)
#define SB2_PFUNC_MISC3_boption1_pud_sel(data)                                       (0x00040000&((data)<<18))
#define SB2_PFUNC_MISC3_boption1_pud_sel_src(data)                                   ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC3_get_boption1_pud_sel(data)                                   ((0x00040000&(data))>>18)
#define SB2_PFUNC_MISC3_boption0_smt_shift                                           (17)
#define SB2_PFUNC_MISC3_boption0_smt_mask                                            (0x00020000)
#define SB2_PFUNC_MISC3_boption0_smt(data)                                           (0x00020000&((data)<<17))
#define SB2_PFUNC_MISC3_boption0_smt_src(data)                                       ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC3_get_boption0_smt(data)                                       ((0x00020000&(data))>>17)
#define SB2_PFUNC_MISC3_boption0_pud_en_shift                                        (16)
#define SB2_PFUNC_MISC3_boption0_pud_en_mask                                         (0x00010000)
#define SB2_PFUNC_MISC3_boption0_pud_en(data)                                        (0x00010000&((data)<<16))
#define SB2_PFUNC_MISC3_boption0_pud_en_src(data)                                    ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC3_get_boption0_pud_en(data)                                    ((0x00010000&(data))>>16)
#define SB2_PFUNC_MISC3_boption0_pud_sel_shift                                       (15)
#define SB2_PFUNC_MISC3_boption0_pud_sel_mask                                        (0x00008000)
#define SB2_PFUNC_MISC3_boption0_pud_sel(data)                                       (0x00008000&((data)<<15))
#define SB2_PFUNC_MISC3_boption0_pud_sel_src(data)                                   ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC3_get_boption0_pud_sel(data)                                   ((0x00008000&(data))>>15)
#define SB2_PFUNC_MISC3_boption9_smt_shift                                           (14)
#define SB2_PFUNC_MISC3_boption9_smt_mask                                            (0x00004000)
#define SB2_PFUNC_MISC3_boption9_smt(data)                                           (0x00004000&((data)<<14))
#define SB2_PFUNC_MISC3_boption9_smt_src(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC3_get_boption9_smt(data)                                       ((0x00004000&(data))>>14)
#define SB2_PFUNC_MISC3_boption9_pud_en_shift                                        (13)
#define SB2_PFUNC_MISC3_boption9_pud_en_mask                                         (0x00002000)
#define SB2_PFUNC_MISC3_boption9_pud_en(data)                                        (0x00002000&((data)<<13))
#define SB2_PFUNC_MISC3_boption9_pud_en_src(data)                                    ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC3_get_boption9_pud_en(data)                                    ((0x00002000&(data))>>13)
#define SB2_PFUNC_MISC3_boption9_pud_sel_shift                                       (12)
#define SB2_PFUNC_MISC3_boption9_pud_sel_mask                                        (0x00001000)
#define SB2_PFUNC_MISC3_boption9_pud_sel(data)                                       (0x00001000&((data)<<12))
#define SB2_PFUNC_MISC3_boption9_pud_sel_src(data)                                   ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC3_get_boption9_pud_sel(data)                                   ((0x00001000&(data))>>12)
#define SB2_PFUNC_MISC3_boption8_smt_shift                                           (11)
#define SB2_PFUNC_MISC3_boption8_smt_mask                                            (0x00000800)
#define SB2_PFUNC_MISC3_boption8_smt(data)                                           (0x00000800&((data)<<11))
#define SB2_PFUNC_MISC3_boption8_smt_src(data)                                       ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC3_get_boption8_smt(data)                                       ((0x00000800&(data))>>11)
#define SB2_PFUNC_MISC3_boption8_pud_en_shift                                        (10)
#define SB2_PFUNC_MISC3_boption8_pud_en_mask                                         (0x00000400)
#define SB2_PFUNC_MISC3_boption8_pud_en(data)                                        (0x00000400&((data)<<10))
#define SB2_PFUNC_MISC3_boption8_pud_en_src(data)                                    ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC3_get_boption8_pud_en(data)                                    ((0x00000400&(data))>>10)
#define SB2_PFUNC_MISC3_boption8_pud_sel_shift                                       (9)
#define SB2_PFUNC_MISC3_boption8_pud_sel_mask                                        (0x00000200)
#define SB2_PFUNC_MISC3_boption8_pud_sel(data)                                       (0x00000200&((data)<<9))
#define SB2_PFUNC_MISC3_boption8_pud_sel_src(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC3_get_boption8_pud_sel(data)                                   ((0x00000200&(data))>>9)
#define SB2_PFUNC_MISC3_boption7_smt_shift                                           (8)
#define SB2_PFUNC_MISC3_boption7_smt_mask                                            (0x00000100)
#define SB2_PFUNC_MISC3_boption7_smt(data)                                           (0x00000100&((data)<<8))
#define SB2_PFUNC_MISC3_boption7_smt_src(data)                                       ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC3_get_boption7_smt(data)                                       ((0x00000100&(data))>>8)
#define SB2_PFUNC_MISC3_boption7_pud_en_shift                                        (7)
#define SB2_PFUNC_MISC3_boption7_pud_en_mask                                         (0x00000080)
#define SB2_PFUNC_MISC3_boption7_pud_en(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_MISC3_boption7_pud_en_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC3_get_boption7_pud_en(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_MISC3_boption7_pud_sel_shift                                       (6)
#define SB2_PFUNC_MISC3_boption7_pud_sel_mask                                        (0x00000040)
#define SB2_PFUNC_MISC3_boption7_pud_sel(data)                                       (0x00000040&((data)<<6))
#define SB2_PFUNC_MISC3_boption7_pud_sel_src(data)                                   ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC3_get_boption7_pud_sel(data)                                   ((0x00000040&(data))>>6)
#define SB2_PFUNC_MISC3_boption6_smt_shift                                           (5)
#define SB2_PFUNC_MISC3_boption6_smt_mask                                            (0x00000020)
#define SB2_PFUNC_MISC3_boption6_smt(data)                                           (0x00000020&((data)<<5))
#define SB2_PFUNC_MISC3_boption6_smt_src(data)                                       ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC3_get_boption6_smt(data)                                       ((0x00000020&(data))>>5)
#define SB2_PFUNC_MISC3_boption6_pud_en_shift                                        (4)
#define SB2_PFUNC_MISC3_boption6_pud_en_mask                                         (0x00000010)
#define SB2_PFUNC_MISC3_boption6_pud_en(data)                                        (0x00000010&((data)<<4))
#define SB2_PFUNC_MISC3_boption6_pud_en_src(data)                                    ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC3_get_boption6_pud_en(data)                                    ((0x00000010&(data))>>4)
#define SB2_PFUNC_MISC3_boption6_pud_sel_shift                                       (3)
#define SB2_PFUNC_MISC3_boption6_pud_sel_mask                                        (0x00000008)
#define SB2_PFUNC_MISC3_boption6_pud_sel(data)                                       (0x00000008&((data)<<3))
#define SB2_PFUNC_MISC3_boption6_pud_sel_src(data)                                   ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC3_get_boption6_pud_sel(data)                                   ((0x00000008&(data))>>3)
#define SB2_PFUNC_MISC3_boption5_smt_shift                                           (2)
#define SB2_PFUNC_MISC3_boption5_smt_mask                                            (0x00000004)
#define SB2_PFUNC_MISC3_boption5_smt(data)                                           (0x00000004&((data)<<2))
#define SB2_PFUNC_MISC3_boption5_smt_src(data)                                       ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC3_get_boption5_smt(data)                                       ((0x00000004&(data))>>2)
#define SB2_PFUNC_MISC3_boption5_pud_en_shift                                        (1)
#define SB2_PFUNC_MISC3_boption5_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_MISC3_boption5_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_MISC3_boption5_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC3_get_boption5_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_MISC3_boption5_pud_sel_shift                                       (0)
#define SB2_PFUNC_MISC3_boption5_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_MISC3_boption5_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_MISC3_boption5_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_MISC3_get_boption5_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define SB2_DEBUG                                                                    0x9801A954
#define SB2_DEBUG_reg_addr                                                           "0xD801A954"
#define SB2_DEBUG_reg                                                                0xD801A954
#define set_SB2_DEBUG_reg(data)   (*((volatile unsigned int*) SB2_DEBUG_reg)=data)
#define get_SB2_DEBUG_reg   (*((volatile unsigned int*) SB2_DEBUG_reg))
#define SB2_DEBUG_inst_adr                                                           "0x0055"
#define SB2_DEBUG_inst                                                               0x0055
#define SB2_DEBUG_main1_dbg_en_shift                                                 (31)
#define SB2_DEBUG_main1_dbg_en_mask                                                  (0x80000000)
#define SB2_DEBUG_main1_dbg_en(data)                                                 (0x80000000&((data)<<31))
#define SB2_DEBUG_main1_dbg_en_src(data)                                             ((0x80000000&(data))>>31)
#define SB2_DEBUG_get_main1_dbg_en(data)                                             ((0x80000000&(data))>>31)
#define SB2_DEBUG_main1_dbg_sel_shift                                                (24)
#define SB2_DEBUG_main1_dbg_sel_mask                                                 (0x0F000000)
#define SB2_DEBUG_main1_dbg_sel(data)                                                (0x0F000000&((data)<<24))
#define SB2_DEBUG_main1_dbg_sel_src(data)                                            ((0x0F000000&(data))>>24)
#define SB2_DEBUG_get_main1_dbg_sel(data)                                            ((0x0F000000&(data))>>24)
#define SB2_DEBUG_dbg_en_shift                                                       (14)
#define SB2_DEBUG_dbg_en_mask                                                        (0x00004000)
#define SB2_DEBUG_dbg_en(data)                                                       (0x00004000&((data)<<14))
#define SB2_DEBUG_dbg_en_src(data)                                                   ((0x00004000&(data))>>14)
#define SB2_DEBUG_get_dbg_en(data)                                                   ((0x00004000&(data))>>14)
#define SB2_DEBUG_dbg_loc_shift                                                      (12)
#define SB2_DEBUG_dbg_loc_mask                                                       (0x00003000)
#define SB2_DEBUG_dbg_loc(data)                                                      (0x00003000&((data)<<12))
#define SB2_DEBUG_dbg_loc_src(data)                                                  ((0x00003000&(data))>>12)
#define SB2_DEBUG_get_dbg_loc(data)                                                  ((0x00003000&(data))>>12)
#define SB2_DEBUG_dbg_sel0_shift                                                     (6)
#define SB2_DEBUG_dbg_sel0_mask                                                      (0x00000FC0)
#define SB2_DEBUG_dbg_sel0(data)                                                     (0x00000FC0&((data)<<6))
#define SB2_DEBUG_dbg_sel0_src(data)                                                 ((0x00000FC0&(data))>>6)
#define SB2_DEBUG_get_dbg_sel0(data)                                                 ((0x00000FC0&(data))>>6)
#define SB2_DEBUG_dbg_sel1_shift                                                     (0)
#define SB2_DEBUG_dbg_sel1_mask                                                      (0x0000003F)
#define SB2_DEBUG_dbg_sel1(data)                                                     (0x0000003F&((data)<<0))
#define SB2_DEBUG_dbg_sel1_src(data)                                                 ((0x0000003F&(data))>>0)
#define SB2_DEBUG_get_dbg_sel1(data)                                                 ((0x0000003F&(data))>>0)


#define SB2_MBIST                                                                    0x9801A958
#define SB2_MBIST_reg_addr                                                           "0xD801A958"
#define SB2_MBIST_reg                                                                0xD801A958
#define set_SB2_MBIST_reg(data)   (*((volatile unsigned int*) SB2_MBIST_reg)=data)
#define get_SB2_MBIST_reg   (*((volatile unsigned int*) SB2_MBIST_reg))
#define SB2_MBIST_inst_adr                                                           "0x0056"
#define SB2_MBIST_inst                                                               0x0056
#define SB2_MBIST_mbist_gpu_chip_top_st_shift                                        (28)
#define SB2_MBIST_mbist_gpu_chip_top_st_mask                                         (0x10000000)
#define SB2_MBIST_mbist_gpu_chip_top_st(data)                                        (0x10000000&((data)<<28))
#define SB2_MBIST_mbist_gpu_chip_top_st_src(data)                                    ((0x10000000&(data))>>28)
#define SB2_MBIST_get_mbist_gpu_chip_top_st(data)                                    ((0x10000000&(data))>>28)
#define SB2_MBIST_mbist_jpeg_st_shift                                                (27)
#define SB2_MBIST_mbist_jpeg_st_mask                                                 (0x08000000)
#define SB2_MBIST_mbist_jpeg_st(data)                                                (0x08000000&((data)<<27))
#define SB2_MBIST_mbist_jpeg_st_src(data)                                            ((0x08000000&(data))>>27)
#define SB2_MBIST_get_mbist_jpeg_st(data)                                            ((0x08000000&(data))>>27)
#define SB2_MBIST_mbist_ve1_st_shift                                                 (26)
#define SB2_MBIST_mbist_ve1_st_mask                                                  (0x04000000)
#define SB2_MBIST_mbist_ve1_st(data)                                                 (0x04000000&((data)<<26))
#define SB2_MBIST_mbist_ve1_st_src(data)                                             ((0x04000000&(data))>>26)
#define SB2_MBIST_get_mbist_ve1_st(data)                                             ((0x04000000&(data))>>26)
#define SB2_MBIST_mbist_ve2_st_shift                                                 (25)
#define SB2_MBIST_mbist_ve2_st_mask                                                  (0x02000000)
#define SB2_MBIST_mbist_ve2_st(data)                                                 (0x02000000&((data)<<25))
#define SB2_MBIST_mbist_ve2_st_src(data)                                             ((0x02000000&(data))>>25)
#define SB2_MBIST_get_mbist_ve2_st(data)                                             ((0x02000000&(data))>>25)
#define SB2_MBIST_mbist_ve3_st_shift                                                 (24)
#define SB2_MBIST_mbist_ve3_st_mask                                                  (0x01000000)
#define SB2_MBIST_mbist_ve3_st(data)                                                 (0x01000000&((data)<<24))
#define SB2_MBIST_mbist_ve3_st_src(data)                                             ((0x01000000&(data))>>24)
#define SB2_MBIST_get_mbist_ve3_st(data)                                             ((0x01000000&(data))>>24)
#define SB2_MBIST_mbist_rsa_st_shift                                                 (23)
#define SB2_MBIST_mbist_rsa_st_mask                                                  (0x00800000)
#define SB2_MBIST_mbist_rsa_st(data)                                                 (0x00800000&((data)<<23))
#define SB2_MBIST_mbist_rsa_st_src(data)                                             ((0x00800000&(data))>>23)
#define SB2_MBIST_get_mbist_rsa_st(data)                                             ((0x00800000&(data))>>23)
#define SB2_MBIST_mbist_sata_st_shift                                                (22)
#define SB2_MBIST_mbist_sata_st_mask                                                 (0x00400000)
#define SB2_MBIST_mbist_sata_st(data)                                                (0x00400000&((data)<<22))
#define SB2_MBIST_mbist_sata_st_src(data)                                            ((0x00400000&(data))>>22)
#define SB2_MBIST_get_mbist_sata_st(data)                                            ((0x00400000&(data))>>22)
#define SB2_MBIST_mbist_pcie0_st_shift                                               (21)
#define SB2_MBIST_mbist_pcie0_st_mask                                                (0x00200000)
#define SB2_MBIST_mbist_pcie0_st(data)                                               (0x00200000&((data)<<21))
#define SB2_MBIST_mbist_pcie0_st_src(data)                                           ((0x00200000&(data))>>21)
#define SB2_MBIST_get_mbist_pcie0_st(data)                                           ((0x00200000&(data))>>21)
#define SB2_MBIST_mbist_pcie1_st_shift                                               (20)
#define SB2_MBIST_mbist_pcie1_st_mask                                                (0x00100000)
#define SB2_MBIST_mbist_pcie1_st(data)                                               (0x00100000&((data)<<20))
#define SB2_MBIST_mbist_pcie1_st_src(data)                                           ((0x00100000&(data))>>20)
#define SB2_MBIST_get_mbist_pcie1_st(data)                                           ((0x00100000&(data))>>20)
#define SB2_MBIST_mbist_nat_st_shift                                                 (19)
#define SB2_MBIST_mbist_nat_st_mask                                                  (0x00080000)
#define SB2_MBIST_mbist_nat_st(data)                                                 (0x00080000&((data)<<19))
#define SB2_MBIST_mbist_nat_st_src(data)                                             ((0x00080000&(data))>>19)
#define SB2_MBIST_get_mbist_nat_st(data)                                             ((0x00080000&(data))>>19)
#define SB2_MBIST_mbist_mipi_st_shift                                                (18)
#define SB2_MBIST_mbist_mipi_st_mask                                                 (0x00040000)
#define SB2_MBIST_mbist_mipi_st(data)                                                (0x00040000&((data)<<18))
#define SB2_MBIST_mbist_mipi_st_src(data)                                            ((0x00040000&(data))>>18)
#define SB2_MBIST_get_mbist_mipi_st(data)                                            ((0x00040000&(data))>>18)
#define SB2_MBIST_mbist_usb_st_shift                                                 (17)
#define SB2_MBIST_mbist_usb_st_mask                                                  (0x00020000)
#define SB2_MBIST_mbist_usb_st(data)                                                 (0x00020000&((data)<<17))
#define SB2_MBIST_mbist_usb_st_src(data)                                             ((0x00020000&(data))>>17)
#define SB2_MBIST_get_mbist_usb_st(data)                                             ((0x00020000&(data))>>17)
#define SB2_MBIST_mbist_se_st_shift                                                  (16)
#define SB2_MBIST_mbist_se_st_mask                                                   (0x00010000)
#define SB2_MBIST_mbist_se_st(data)                                                  (0x00010000&((data)<<16))
#define SB2_MBIST_mbist_se_st_src(data)                                              ((0x00010000&(data))>>16)
#define SB2_MBIST_get_mbist_se_st(data)                                              ((0x00010000&(data))>>16)
#define SB2_MBIST_mbist_md_st_shift                                                  (15)
#define SB2_MBIST_mbist_md_st_mask                                                   (0x00008000)
#define SB2_MBIST_mbist_md_st(data)                                                  (0x00008000&((data)<<15))
#define SB2_MBIST_mbist_md_st_src(data)                                              ((0x00008000&(data))>>15)
#define SB2_MBIST_get_mbist_md_st(data)                                              ((0x00008000&(data))>>15)
#define SB2_MBIST_mbist_nf_st_shift                                                  (14)
#define SB2_MBIST_mbist_nf_st_mask                                                   (0x00004000)
#define SB2_MBIST_mbist_nf_st(data)                                                  (0x00004000&((data)<<14))
#define SB2_MBIST_mbist_nf_st_src(data)                                              ((0x00004000&(data))>>14)
#define SB2_MBIST_get_mbist_nf_st(data)                                              ((0x00004000&(data))>>14)
#define SB2_MBIST_mbist_cr_st_shift                                                  (13)
#define SB2_MBIST_mbist_cr_st_mask                                                   (0x00002000)
#define SB2_MBIST_mbist_cr_st(data)                                                  (0x00002000&((data)<<13))
#define SB2_MBIST_mbist_cr_st_src(data)                                              ((0x00002000&(data))>>13)
#define SB2_MBIST_get_mbist_cr_st(data)                                              ((0x00002000&(data))>>13)
#define SB2_MBIST_mbist_etn_st_shift                                                 (12)
#define SB2_MBIST_mbist_etn_st_mask                                                  (0x00001000)
#define SB2_MBIST_mbist_etn_st(data)                                                 (0x00001000&((data)<<12))
#define SB2_MBIST_mbist_etn_st_src(data)                                             ((0x00001000&(data))>>12)
#define SB2_MBIST_get_mbist_etn_st(data)                                             ((0x00001000&(data))>>12)
#define SB2_MBIST_mbist_dp_st_shift                                                  (11)
#define SB2_MBIST_mbist_dp_st_mask                                                   (0x00000800)
#define SB2_MBIST_mbist_dp_st(data)                                                  (0x00000800&((data)<<11))
#define SB2_MBIST_mbist_dp_st_src(data)                                              ((0x00000800&(data))>>11)
#define SB2_MBIST_get_mbist_dp_st(data)                                              ((0x00000800&(data))>>11)
#define SB2_MBIST_mbist_ae_st_shift                                                  (10)
#define SB2_MBIST_mbist_ae_st_mask                                                   (0x00000400)
#define SB2_MBIST_mbist_ae_st(data)                                                  (0x00000400&((data)<<10))
#define SB2_MBIST_mbist_ae_st_src(data)                                              ((0x00000400&(data))>>10)
#define SB2_MBIST_get_mbist_ae_st(data)                                              ((0x00000400&(data))>>10)
#define SB2_MBIST_mbist_acpu_st_shift                                                (9)
#define SB2_MBIST_mbist_acpu_st_mask                                                 (0x00000200)
#define SB2_MBIST_mbist_acpu_st(data)                                                (0x00000200&((data)<<9))
#define SB2_MBIST_mbist_acpu_st_src(data)                                            ((0x00000200&(data))>>9)
#define SB2_MBIST_get_mbist_acpu_st(data)                                            ((0x00000200&(data))>>9)
#define SB2_MBIST_mbist_gpu_st_shift                                                 (8)
#define SB2_MBIST_mbist_gpu_st_mask                                                  (0x00000100)
#define SB2_MBIST_mbist_gpu_st(data)                                                 (0x00000100&((data)<<8))
#define SB2_MBIST_mbist_gpu_st_src(data)                                             ((0x00000100&(data))>>8)
#define SB2_MBIST_get_mbist_gpu_st(data)                                             ((0x00000100&(data))>>8)
#define SB2_MBIST_mbist_tp_st_shift                                                  (7)
#define SB2_MBIST_mbist_tp_st_mask                                                   (0x00000080)
#define SB2_MBIST_mbist_tp_st(data)                                                  (0x00000080&((data)<<7))
#define SB2_MBIST_mbist_tp_st_src(data)                                              ((0x00000080&(data))>>7)
#define SB2_MBIST_get_mbist_tp_st(data)                                              ((0x00000080&(data))>>7)
#define SB2_MBIST_mbist_aio_st_shift                                                 (6)
#define SB2_MBIST_mbist_aio_st_mask                                                  (0x00000040)
#define SB2_MBIST_mbist_aio_st(data)                                                 (0x00000040&((data)<<6))
#define SB2_MBIST_mbist_aio_st_src(data)                                             ((0x00000040&(data))>>6)
#define SB2_MBIST_get_mbist_aio_st(data)                                             ((0x00000040&(data))>>6)
#define SB2_MBIST_mbist_pif_st_shift                                                 (5)
#define SB2_MBIST_mbist_pif_st_mask                                                  (0x00000020)
#define SB2_MBIST_mbist_pif_st(data)                                                 (0x00000020&((data)<<5))
#define SB2_MBIST_mbist_pif_st_src(data)                                             ((0x00000020&(data))>>5)
#define SB2_MBIST_get_mbist_pif_st(data)                                             ((0x00000020&(data))>>5)
#define SB2_MBIST_mbist_hdmi_st_shift                                                (4)
#define SB2_MBIST_mbist_hdmi_st_mask                                                 (0x00000010)
#define SB2_MBIST_mbist_hdmi_st(data)                                                (0x00000010&((data)<<4))
#define SB2_MBIST_mbist_hdmi_st_src(data)                                            ((0x00000010&(data))>>4)
#define SB2_MBIST_get_mbist_hdmi_st(data)                                            ((0x00000010&(data))>>4)
#define SB2_MBIST_mbist_vo_st_shift                                                  (3)
#define SB2_MBIST_mbist_vo_st_mask                                                   (0x00000008)
#define SB2_MBIST_mbist_vo_st(data)                                                  (0x00000008&((data)<<3))
#define SB2_MBIST_mbist_vo_st_src(data)                                              ((0x00000008&(data))>>3)
#define SB2_MBIST_get_mbist_vo_st(data)                                              ((0x00000008&(data))>>3)
#define SB2_MBIST_mbist_dc_phy_st_shift                                              (2)
#define SB2_MBIST_mbist_dc_phy_st_mask                                               (0x00000004)
#define SB2_MBIST_mbist_dc_phy_st(data)                                              (0x00000004&((data)<<2))
#define SB2_MBIST_mbist_dc_phy_st_src(data)                                          ((0x00000004&(data))>>2)
#define SB2_MBIST_get_mbist_dc_phy_st(data)                                          ((0x00000004&(data))>>2)
#define SB2_MBIST_mbist_dc_sys_st_shift                                              (1)
#define SB2_MBIST_mbist_dc_sys_st_mask                                               (0x00000002)
#define SB2_MBIST_mbist_dc_sys_st(data)                                              (0x00000002&((data)<<1))
#define SB2_MBIST_mbist_dc_sys_st_src(data)                                          ((0x00000002&(data))>>1)
#define SB2_MBIST_get_mbist_dc_sys_st(data)                                          ((0x00000002&(data))>>1)
#define SB2_MBIST_mbist_cp_st_shift                                                  (0)
#define SB2_MBIST_mbist_cp_st_mask                                                   (0x00000001)
#define SB2_MBIST_mbist_cp_st(data)                                                  (0x00000001&((data)<<0))
#define SB2_MBIST_mbist_cp_st_src(data)                                              ((0x00000001&(data))>>0)
#define SB2_MBIST_get_mbist_cp_st(data)                                              ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG0                                                                0x9801A960
#define SB2_PFUNC_RG0_reg_addr                                                       "0xD801A960"
#define SB2_PFUNC_RG0_reg                                                            0xD801A960
#define set_SB2_PFUNC_RG0_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG0_reg)=data)
#define get_SB2_PFUNC_RG0_reg   (*((volatile unsigned int*) SB2_PFUNC_RG0_reg))
#define SB2_PFUNC_RG0_inst_adr                                                       "0x0058"
#define SB2_PFUNC_RG0_inst                                                           0x0058
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_shift                                          (5)
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_mask                                           (0x00000020)
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_RG0_rgmii0_txd_3_sr_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG0_get_rgmii0_txd_3_sr(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_shift                                          (4)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_mask                                           (0x00000010)
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr(data)                                          (0x00000010&((data)<<4))
#define SB2_PFUNC_RG0_rgmii0_txd_2_sr_src(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG0_get_rgmii0_txd_2_sr(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_shift                                          (3)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_mask                                           (0x00000008)
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr(data)                                          (0x00000008&((data)<<3))
#define SB2_PFUNC_RG0_rgmii0_txd_1_sr_src(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG0_get_rgmii0_txd_1_sr(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_shift                                          (2)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_mask                                           (0x00000004)
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG0_rgmii0_txd_0_sr_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG0_get_rgmii0_txd_0_sr(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_shift                                         (1)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_mask                                          (0x00000002)
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr(data)                                         (0x00000002&((data)<<1))
#define SB2_PFUNC_RG0_rgmii0_tx_ctl_sr_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG0_get_rgmii0_tx_ctl_sr(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG0_rgmii0_txc_sr_shift                                            (0)
#define SB2_PFUNC_RG0_rgmii0_txc_sr_mask                                             (0x00000001)
#define SB2_PFUNC_RG0_rgmii0_txc_sr(data)                                            (0x00000001&((data)<<0))
#define SB2_PFUNC_RG0_rgmii0_txc_sr_src(data)                                        ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG0_get_rgmii0_txc_sr(data)                                        ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG1                                                                0x9801A964
#define SB2_PFUNC_RG1_reg_addr                                                       "0xD801A964"
#define SB2_PFUNC_RG1_reg                                                            0xD801A964
#define set_SB2_PFUNC_RG1_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG1_reg)=data)
#define get_SB2_PFUNC_RG1_reg   (*((volatile unsigned int*) SB2_PFUNC_RG1_reg))
#define SB2_PFUNC_RG1_inst_adr                                                       "0x0059"
#define SB2_PFUNC_RG1_inst                                                           0x0059
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_shift                                        (31)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_mask                                         (0x80000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_shift                                         (30)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_mask                                          (0x40000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_shift                                     (29)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_shift                                    (28)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_RG1_rgmii0_rx_ctl_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG1_get_rgmii0_rx_ctl_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_shift                                           (27)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_mask                                            (0x08000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_smt(data)                                           (0x08000000&((data)<<27))
#define SB2_PFUNC_RG1_rgmii0_rxc_smt_src(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_smt(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_shift                                            (26)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_mask                                             (0x04000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_e2(data)                                            (0x04000000&((data)<<26))
#define SB2_PFUNC_RG1_rgmii0_rxc_e2_src(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_e2(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_shift                                        (25)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_shift                                       (24)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_RG1_rgmii0_rxc_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG1_get_rgmii0_rxc_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_shift                                         (23)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_mask                                          (0x00800000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_RG1_rgmii0_txd_3_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_shift                                          (22)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_mask                                           (0x00400000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_RG1_rgmii0_txd_3_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_shift                                      (21)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_shift                                     (20)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_RG1_rgmii0_txd_3_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG1_get_rgmii0_txd_3_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_shift                                         (19)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_mask                                          (0x00080000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt(data)                                         (0x00080000&((data)<<19))
#define SB2_PFUNC_RG1_rgmii0_txd_2_smt_src(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_smt(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_shift                                          (18)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_mask                                           (0x00040000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2(data)                                          (0x00040000&((data)<<18))
#define SB2_PFUNC_RG1_rgmii0_txd_2_e2_src(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_e2(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_shift                                      (17)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_mask                                       (0x00020000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en(data)                                      (0x00020000&((data)<<17))
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_en_src(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_pud_en(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_shift                                     (16)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_mask                                      (0x00010000)
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel(data)                                     (0x00010000&((data)<<16))
#define SB2_PFUNC_RG1_rgmii0_txd_2_pud_sel_src(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG1_get_rgmii0_txd_2_pud_sel(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_shift                                         (15)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG1_rgmii0_txd_1_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_shift                                          (14)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG1_rgmii0_txd_1_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_shift                                      (13)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG1_rgmii0_txd_1_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG1_get_rgmii0_txd_1_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_shift                                         (11)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG1_rgmii0_txd_0_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_shift                                          (10)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG1_rgmii0_txd_0_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_shift                                      (9)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG1_rgmii0_txd_0_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG1_get_rgmii0_txd_0_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_shift                                        (7)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_mask                                         (0x00000080)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_smt_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_smt(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_shift                                         (6)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_mask                                          (0x00000040)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2(data)                                         (0x00000040&((data)<<6))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_e2_src(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_e2(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_shift                                     (5)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_mask                                      (0x00000020)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en(data)                                     (0x00000020&((data)<<5))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_en_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_pud_en(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_shift                                    (4)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_mask                                     (0x00000010)
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel(data)                                    (0x00000010&((data)<<4))
#define SB2_PFUNC_RG1_rgmii0_tx_ctl_pud_sel_src(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG1_get_rgmii0_tx_ctl_pud_sel(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG1_rgmii0_txc_smt_shift                                           (3)
#define SB2_PFUNC_RG1_rgmii0_txc_smt_mask                                            (0x00000008)
#define SB2_PFUNC_RG1_rgmii0_txc_smt(data)                                           (0x00000008&((data)<<3))
#define SB2_PFUNC_RG1_rgmii0_txc_smt_src(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG1_get_rgmii0_txc_smt(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG1_rgmii0_txc_e2_shift                                            (2)
#define SB2_PFUNC_RG1_rgmii0_txc_e2_mask                                             (0x00000004)
#define SB2_PFUNC_RG1_rgmii0_txc_e2(data)                                            (0x00000004&((data)<<2))
#define SB2_PFUNC_RG1_rgmii0_txc_e2_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG1_get_rgmii0_txc_e2(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_shift                                        (1)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_RG1_rgmii0_txc_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG1_get_rgmii0_txc_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_shift                                       (0)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_RG1_rgmii0_txc_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG1_get_rgmii0_txc_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG2                                                                0x9801A968
#define SB2_PFUNC_RG2_reg_addr                                                       "0xD801A968"
#define SB2_PFUNC_RG2_reg                                                            0xD801A968
#define set_SB2_PFUNC_RG2_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG2_reg)=data)
#define get_SB2_PFUNC_RG2_reg   (*((volatile unsigned int*) SB2_PFUNC_RG2_reg))
#define SB2_PFUNC_RG2_inst_adr                                                       "0x005A"
#define SB2_PFUNC_RG2_inst                                                           0x005A
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_shift                                        (31)
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_mask                                         (0x80000000)
#define SB2_PFUNC_RG2_rgmii0_bias_mode2(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG2_rgmii0_bias_mode2_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG2_get_rgmii0_bias_mode2(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG2_rgmii0_bias_mode_shift                                         (30)
#define SB2_PFUNC_RG2_rgmii0_bias_mode_mask                                          (0x40000000)
#define SB2_PFUNC_RG2_rgmii0_bias_mode(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG2_rgmii0_bias_mode_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG2_get_rgmii0_bias_mode(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG2_rgmii0_bias_dn_shift                                           (27)
#define SB2_PFUNC_RG2_rgmii0_bias_dn_mask                                            (0x38000000)
#define SB2_PFUNC_RG2_rgmii0_bias_dn(data)                                           (0x38000000&((data)<<27))
#define SB2_PFUNC_RG2_rgmii0_bias_dn_src(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG2_get_rgmii0_bias_dn(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG2_rgmii0_bias_dp_shift                                           (24)
#define SB2_PFUNC_RG2_rgmii0_bias_dp_mask                                            (0x07000000)
#define SB2_PFUNC_RG2_rgmii0_bias_dp(data)                                           (0x07000000&((data)<<24))
#define SB2_PFUNC_RG2_rgmii0_bias_dp_src(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG2_get_rgmii0_bias_dp(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_shift                                           (23)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_mask                                            (0x00800000)
#define SB2_PFUNC_RG2_rgmii0_mdc_smt(data)                                           (0x00800000&((data)<<23))
#define SB2_PFUNC_RG2_rgmii0_mdc_smt_src(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_smt(data)                                       ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_shift                                            (22)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_mask                                             (0x00400000)
#define SB2_PFUNC_RG2_rgmii0_mdc_e2(data)                                            (0x00400000&((data)<<22))
#define SB2_PFUNC_RG2_rgmii0_mdc_e2_src(data)                                        ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_e2(data)                                        ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_shift                                        (21)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_mask                                         (0x00200000)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en(data)                                        (0x00200000&((data)<<21))
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_en_src(data)                                    ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_pud_en(data)                                    ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_shift                                       (20)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_mask                                        (0x00100000)
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel(data)                                       (0x00100000&((data)<<20))
#define SB2_PFUNC_RG2_rgmii0_mdc_pud_sel_src(data)                                   ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG2_get_rgmii0_mdc_pud_sel(data)                                   ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_shift                                          (19)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_mask                                           (0x00080000)
#define SB2_PFUNC_RG2_rgmii0_mdio_smt(data)                                          (0x00080000&((data)<<19))
#define SB2_PFUNC_RG2_rgmii0_mdio_smt_src(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_smt(data)                                      ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_shift                                           (18)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_mask                                            (0x00040000)
#define SB2_PFUNC_RG2_rgmii0_mdio_e2(data)                                           (0x00040000&((data)<<18))
#define SB2_PFUNC_RG2_rgmii0_mdio_e2_src(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_e2(data)                                       ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_shift                                       (17)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_mask                                        (0x00020000)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en(data)                                       (0x00020000&((data)<<17))
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_en_src(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_pud_en(data)                                   ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_shift                                      (16)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_mask                                       (0x00010000)
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel(data)                                      (0x00010000&((data)<<16))
#define SB2_PFUNC_RG2_rgmii0_mdio_pud_sel_src(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG2_get_rgmii0_mdio_pud_sel(data)                                  ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_shift                                         (15)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_shift                                          (14)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_shift                                      (13)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG2_rgmii0_rxd_3_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_3_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_shift                                         (11)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_shift                                          (10)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_shift                                      (9)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG2_rgmii0_rxd_2_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_2_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_shift                                         (7)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_mask                                          (0x00000080)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt(data)                                         (0x00000080&((data)<<7))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_smt_src(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_smt(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_shift                                          (6)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_mask                                           (0x00000040)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2(data)                                          (0x00000040&((data)<<6))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_e2_src(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_e2(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_shift                                      (5)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_mask                                       (0x00000020)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en(data)                                      (0x00000020&((data)<<5))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_en_src(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_pud_en(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_shift                                     (4)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_mask                                      (0x00000010)
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel(data)                                     (0x00000010&((data)<<4))
#define SB2_PFUNC_RG2_rgmii0_rxd_1_pud_sel_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_1_pud_sel(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_shift                                         (3)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_mask                                          (0x00000008)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt(data)                                         (0x00000008&((data)<<3))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_smt_src(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_smt(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_shift                                          (2)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_mask                                           (0x00000004)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_e2_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_e2(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_shift                                      (1)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_mask                                       (0x00000002)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en(data)                                      (0x00000002&((data)<<1))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_en_src(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_pud_en(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_shift                                     (0)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_mask                                      (0x00000001)
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel(data)                                     (0x00000001&((data)<<0))
#define SB2_PFUNC_RG2_rgmii0_rxd_0_pud_sel_src(data)                                 ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG2_get_rgmii0_rxd_0_pud_sel(data)                                 ((0x00000001&(data))>>0)


#define SB2_MUXPAD_RG0                                                               0x9801A96C
#define SB2_MUXPAD_RG0_reg_addr                                                      "0xD801A96C"
#define SB2_MUXPAD_RG0_reg                                                           0xD801A96C
#define set_SB2_MUXPAD_RG0_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD_RG0_reg)=data)
#define get_SB2_MUXPAD_RG0_reg   (*((volatile unsigned int*) SB2_MUXPAD_RG0_reg))
#define SB2_MUXPAD_RG0_inst_adr                                                      "0x005B"
#define SB2_MUXPAD_RG0_inst                                                          0x005B
#define SB2_MUXPAD_RG0_rgmii0_mdc_shift                                              (26)
#define SB2_MUXPAD_RG0_rgmii0_mdc_mask                                               (0x0C000000)
#define SB2_MUXPAD_RG0_rgmii0_mdc(data)                                              (0x0C000000&((data)<<26))
#define SB2_MUXPAD_RG0_rgmii0_mdc_src(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG0_get_rgmii0_mdc(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG0_rgmii0_mdio_shift                                             (24)
#define SB2_MUXPAD_RG0_rgmii0_mdio_mask                                              (0x03000000)
#define SB2_MUXPAD_RG0_rgmii0_mdio(data)                                             (0x03000000&((data)<<24))
#define SB2_MUXPAD_RG0_rgmii0_mdio_src(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG0_get_rgmii0_mdio(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_shift                                            (22)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_mask                                             (0x00C00000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_3(data)                                            (0x00C00000&((data)<<22))
#define SB2_MUXPAD_RG0_rgmii0_rxd_3_src(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_3(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_shift                                            (20)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_mask                                             (0x00300000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_2(data)                                            (0x00300000&((data)<<20))
#define SB2_MUXPAD_RG0_rgmii0_rxd_2_src(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_2(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_shift                                            (18)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_mask                                             (0x000C0000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_1(data)                                            (0x000C0000&((data)<<18))
#define SB2_MUXPAD_RG0_rgmii0_rxd_1_src(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_1(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_shift                                            (16)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_mask                                             (0x00030000)
#define SB2_MUXPAD_RG0_rgmii0_rxd_0(data)                                            (0x00030000&((data)<<16))
#define SB2_MUXPAD_RG0_rgmii0_rxd_0_src(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG0_get_rgmii0_rxd_0(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_shift                                           (14)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_mask                                            (0x0000C000)
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl(data)                                           (0x0000C000&((data)<<14))
#define SB2_MUXPAD_RG0_rgmii0_rx_ctl_src(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG0_get_rgmii0_rx_ctl(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG0_rgmii0_rxc_shift                                              (12)
#define SB2_MUXPAD_RG0_rgmii0_rxc_mask                                               (0x00003000)
#define SB2_MUXPAD_RG0_rgmii0_rxc(data)                                              (0x00003000&((data)<<12))
#define SB2_MUXPAD_RG0_rgmii0_rxc_src(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG0_get_rgmii0_rxc(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG0_rgmii0_txd_3_shift                                            (10)
#define SB2_MUXPAD_RG0_rgmii0_txd_3_mask                                             (0x00000C00)
#define SB2_MUXPAD_RG0_rgmii0_txd_3(data)                                            (0x00000C00&((data)<<10))
#define SB2_MUXPAD_RG0_rgmii0_txd_3_src(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_3(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG0_rgmii0_txd_2_shift                                            (8)
#define SB2_MUXPAD_RG0_rgmii0_txd_2_mask                                             (0x00000300)
#define SB2_MUXPAD_RG0_rgmii0_txd_2(data)                                            (0x00000300&((data)<<8))
#define SB2_MUXPAD_RG0_rgmii0_txd_2_src(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_2(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG0_rgmii0_txd_1_shift                                            (6)
#define SB2_MUXPAD_RG0_rgmii0_txd_1_mask                                             (0x000000C0)
#define SB2_MUXPAD_RG0_rgmii0_txd_1(data)                                            (0x000000C0&((data)<<6))
#define SB2_MUXPAD_RG0_rgmii0_txd_1_src(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_1(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG0_rgmii0_txd_0_shift                                            (4)
#define SB2_MUXPAD_RG0_rgmii0_txd_0_mask                                             (0x00000030)
#define SB2_MUXPAD_RG0_rgmii0_txd_0(data)                                            (0x00000030&((data)<<4))
#define SB2_MUXPAD_RG0_rgmii0_txd_0_src(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG0_get_rgmii0_txd_0(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_shift                                           (2)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_mask                                            (0x0000000C)
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl(data)                                           (0x0000000C&((data)<<2))
#define SB2_MUXPAD_RG0_rgmii0_tx_ctl_src(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG0_get_rgmii0_tx_ctl(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG0_rgmii0_txc_shift                                              (0)
#define SB2_MUXPAD_RG0_rgmii0_txc_mask                                               (0x00000003)
#define SB2_MUXPAD_RG0_rgmii0_txc(data)                                              (0x00000003&((data)<<0))
#define SB2_MUXPAD_RG0_rgmii0_txc_src(data)                                          ((0x00000003&(data))>>0)
#define SB2_MUXPAD_RG0_get_rgmii0_txc(data)                                          ((0x00000003&(data))>>0)


#define SB2_PFUNC_RG3                                                                0x9801A970
#define SB2_PFUNC_RG3_reg_addr                                                       "0xD801A970"
#define SB2_PFUNC_RG3_reg                                                            0xD801A970
#define set_SB2_PFUNC_RG3_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG3_reg)=data)
#define get_SB2_PFUNC_RG3_reg   (*((volatile unsigned int*) SB2_PFUNC_RG3_reg))
#define SB2_PFUNC_RG3_inst_adr                                                       "0x005C"
#define SB2_PFUNC_RG3_inst                                                           0x005C
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_shift                                          (5)
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_mask                                           (0x00000020)
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr(data)                                          (0x00000020&((data)<<5))
#define SB2_PFUNC_RG3_rgmii1_txd_3_sr_src(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG3_get_rgmii1_txd_3_sr(data)                                      ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_shift                                          (4)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_mask                                           (0x00000010)
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr(data)                                          (0x00000010&((data)<<4))
#define SB2_PFUNC_RG3_rgmii1_txd_2_sr_src(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG3_get_rgmii1_txd_2_sr(data)                                      ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_shift                                          (3)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_mask                                           (0x00000008)
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr(data)                                          (0x00000008&((data)<<3))
#define SB2_PFUNC_RG3_rgmii1_txd_1_sr_src(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG3_get_rgmii1_txd_1_sr(data)                                      ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_shift                                          (2)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_mask                                           (0x00000004)
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG3_rgmii1_txd_0_sr_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG3_get_rgmii1_txd_0_sr(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_shift                                         (1)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_mask                                          (0x00000002)
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr(data)                                         (0x00000002&((data)<<1))
#define SB2_PFUNC_RG3_rgmii1_tx_ctl_sr_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG3_get_rgmii1_tx_ctl_sr(data)                                     ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG3_rgmii1_txc_sr_shift                                            (0)
#define SB2_PFUNC_RG3_rgmii1_txc_sr_mask                                             (0x00000001)
#define SB2_PFUNC_RG3_rgmii1_txc_sr(data)                                            (0x00000001&((data)<<0))
#define SB2_PFUNC_RG3_rgmii1_txc_sr_src(data)                                        ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG3_get_rgmii1_txc_sr(data)                                        ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG4                                                                0x9801A974
#define SB2_PFUNC_RG4_reg_addr                                                       "0xD801A974"
#define SB2_PFUNC_RG4_reg                                                            0xD801A974
#define set_SB2_PFUNC_RG4_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG4_reg)=data)
#define get_SB2_PFUNC_RG4_reg   (*((volatile unsigned int*) SB2_PFUNC_RG4_reg))
#define SB2_PFUNC_RG4_inst_adr                                                       "0x005D"
#define SB2_PFUNC_RG4_inst                                                           0x005D
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_shift                                        (31)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_mask                                         (0x80000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_smt_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_smt(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_shift                                         (30)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_mask                                          (0x40000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_e2_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_e2(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_shift                                     (29)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_mask                                      (0x20000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en(data)                                     (0x20000000&((data)<<29))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_en_src(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_pud_en(data)                                 ((0x20000000&(data))>>29)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_shift                                    (28)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_mask                                     (0x10000000)
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel(data)                                    (0x10000000&((data)<<28))
#define SB2_PFUNC_RG4_rgmii1_rx_ctl_pud_sel_src(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG4_get_rgmii1_rx_ctl_pud_sel(data)                                ((0x10000000&(data))>>28)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_shift                                           (27)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_mask                                            (0x08000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_smt(data)                                           (0x08000000&((data)<<27))
#define SB2_PFUNC_RG4_rgmii1_rxc_smt_src(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_smt(data)                                       ((0x08000000&(data))>>27)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_shift                                            (26)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_mask                                             (0x04000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_e2(data)                                            (0x04000000&((data)<<26))
#define SB2_PFUNC_RG4_rgmii1_rxc_e2_src(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_e2(data)                                        ((0x04000000&(data))>>26)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_shift                                        (25)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_mask                                         (0x02000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en(data)                                        (0x02000000&((data)<<25))
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_en_src(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_pud_en(data)                                    ((0x02000000&(data))>>25)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_shift                                       (24)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_mask                                        (0x01000000)
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel(data)                                       (0x01000000&((data)<<24))
#define SB2_PFUNC_RG4_rgmii1_rxc_pud_sel_src(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG4_get_rgmii1_rxc_pud_sel(data)                                   ((0x01000000&(data))>>24)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_shift                                         (23)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_mask                                          (0x00800000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt(data)                                         (0x00800000&((data)<<23))
#define SB2_PFUNC_RG4_rgmii1_txd_3_smt_src(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_smt(data)                                     ((0x00800000&(data))>>23)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_shift                                          (22)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_mask                                           (0x00400000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2(data)                                          (0x00400000&((data)<<22))
#define SB2_PFUNC_RG4_rgmii1_txd_3_e2_src(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_e2(data)                                      ((0x00400000&(data))>>22)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_shift                                      (21)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_mask                                       (0x00200000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en(data)                                      (0x00200000&((data)<<21))
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_en_src(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_pud_en(data)                                  ((0x00200000&(data))>>21)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_shift                                     (20)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_mask                                      (0x00100000)
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel(data)                                     (0x00100000&((data)<<20))
#define SB2_PFUNC_RG4_rgmii1_txd_3_pud_sel_src(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG4_get_rgmii1_txd_3_pud_sel(data)                                 ((0x00100000&(data))>>20)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_shift                                         (19)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_mask                                          (0x00080000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt(data)                                         (0x00080000&((data)<<19))
#define SB2_PFUNC_RG4_rgmii1_txd_2_smt_src(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_smt(data)                                     ((0x00080000&(data))>>19)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_shift                                          (18)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_mask                                           (0x00040000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2(data)                                          (0x00040000&((data)<<18))
#define SB2_PFUNC_RG4_rgmii1_txd_2_e2_src(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_e2(data)                                      ((0x00040000&(data))>>18)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_shift                                      (17)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_mask                                       (0x00020000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en(data)                                      (0x00020000&((data)<<17))
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_en_src(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_pud_en(data)                                  ((0x00020000&(data))>>17)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_shift                                     (16)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_mask                                      (0x00010000)
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel(data)                                     (0x00010000&((data)<<16))
#define SB2_PFUNC_RG4_rgmii1_txd_2_pud_sel_src(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG4_get_rgmii1_txd_2_pud_sel(data)                                 ((0x00010000&(data))>>16)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_shift                                         (15)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG4_rgmii1_txd_1_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_shift                                          (14)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG4_rgmii1_txd_1_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_shift                                      (13)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG4_rgmii1_txd_1_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG4_get_rgmii1_txd_1_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_shift                                         (11)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG4_rgmii1_txd_0_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_shift                                          (10)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG4_rgmii1_txd_0_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_shift                                      (9)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG4_rgmii1_txd_0_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG4_get_rgmii1_txd_0_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_shift                                        (7)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_mask                                         (0x00000080)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt(data)                                        (0x00000080&((data)<<7))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_smt_src(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_smt(data)                                    ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_shift                                         (6)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_mask                                          (0x00000040)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2(data)                                         (0x00000040&((data)<<6))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_e2_src(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_e2(data)                                     ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_shift                                     (5)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_mask                                      (0x00000020)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en(data)                                     (0x00000020&((data)<<5))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_en_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_pud_en(data)                                 ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_shift                                    (4)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_mask                                     (0x00000010)
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel(data)                                    (0x00000010&((data)<<4))
#define SB2_PFUNC_RG4_rgmii1_tx_ctl_pud_sel_src(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG4_get_rgmii1_tx_ctl_pud_sel(data)                                ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG4_rgmii1_txc_smt_shift                                           (3)
#define SB2_PFUNC_RG4_rgmii1_txc_smt_mask                                            (0x00000008)
#define SB2_PFUNC_RG4_rgmii1_txc_smt(data)                                           (0x00000008&((data)<<3))
#define SB2_PFUNC_RG4_rgmii1_txc_smt_src(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG4_get_rgmii1_txc_smt(data)                                       ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG4_rgmii1_txc_e2_shift                                            (2)
#define SB2_PFUNC_RG4_rgmii1_txc_e2_mask                                             (0x00000004)
#define SB2_PFUNC_RG4_rgmii1_txc_e2(data)                                            (0x00000004&((data)<<2))
#define SB2_PFUNC_RG4_rgmii1_txc_e2_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG4_get_rgmii1_txc_e2(data)                                        ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_shift                                        (1)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_mask                                         (0x00000002)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en(data)                                        (0x00000002&((data)<<1))
#define SB2_PFUNC_RG4_rgmii1_txc_pud_en_src(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG4_get_rgmii1_txc_pud_en(data)                                    ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_shift                                       (0)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_mask                                        (0x00000001)
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel(data)                                       (0x00000001&((data)<<0))
#define SB2_PFUNC_RG4_rgmii1_txc_pud_sel_src(data)                                   ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG4_get_rgmii1_txc_pud_sel(data)                                   ((0x00000001&(data))>>0)


#define SB2_PFUNC_RG5                                                                0x9801A978
#define SB2_PFUNC_RG5_reg_addr                                                       "0xD801A978"
#define SB2_PFUNC_RG5_reg                                                            0xD801A978
#define set_SB2_PFUNC_RG5_reg(data)   (*((volatile unsigned int*) SB2_PFUNC_RG5_reg)=data)
#define get_SB2_PFUNC_RG5_reg   (*((volatile unsigned int*) SB2_PFUNC_RG5_reg))
#define SB2_PFUNC_RG5_inst_adr                                                       "0x005E"
#define SB2_PFUNC_RG5_inst                                                           0x005E
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_shift                                        (31)
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_mask                                         (0x80000000)
#define SB2_PFUNC_RG5_rgmii1_bias_mode2(data)                                        (0x80000000&((data)<<31))
#define SB2_PFUNC_RG5_rgmii1_bias_mode2_src(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG5_get_rgmii1_bias_mode2(data)                                    ((0x80000000&(data))>>31)
#define SB2_PFUNC_RG5_rgmii1_bias_mode_shift                                         (30)
#define SB2_PFUNC_RG5_rgmii1_bias_mode_mask                                          (0x40000000)
#define SB2_PFUNC_RG5_rgmii1_bias_mode(data)                                         (0x40000000&((data)<<30))
#define SB2_PFUNC_RG5_rgmii1_bias_mode_src(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG5_get_rgmii1_bias_mode(data)                                     ((0x40000000&(data))>>30)
#define SB2_PFUNC_RG5_rgmii1_bias_dn_shift                                           (27)
#define SB2_PFUNC_RG5_rgmii1_bias_dn_mask                                            (0x38000000)
#define SB2_PFUNC_RG5_rgmii1_bias_dn(data)                                           (0x38000000&((data)<<27))
#define SB2_PFUNC_RG5_rgmii1_bias_dn_src(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG5_get_rgmii1_bias_dn(data)                                       ((0x38000000&(data))>>27)
#define SB2_PFUNC_RG5_rgmii1_bias_dp_shift                                           (24)
#define SB2_PFUNC_RG5_rgmii1_bias_dp_mask                                            (0x07000000)
#define SB2_PFUNC_RG5_rgmii1_bias_dp(data)                                           (0x07000000&((data)<<24))
#define SB2_PFUNC_RG5_rgmii1_bias_dp_src(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG5_get_rgmii1_bias_dp(data)                                       ((0x07000000&(data))>>24)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_shift                                         (15)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_mask                                          (0x00008000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt(data)                                         (0x00008000&((data)<<15))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_smt_src(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_smt(data)                                     ((0x00008000&(data))>>15)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_shift                                          (14)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_mask                                           (0x00004000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2(data)                                          (0x00004000&((data)<<14))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_e2_src(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_e2(data)                                      ((0x00004000&(data))>>14)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_shift                                      (13)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_mask                                       (0x00002000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en(data)                                      (0x00002000&((data)<<13))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_en_src(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_pud_en(data)                                  ((0x00002000&(data))>>13)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_shift                                     (12)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_mask                                      (0x00001000)
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel(data)                                     (0x00001000&((data)<<12))
#define SB2_PFUNC_RG5_rgmii1_rxd_3_pud_sel_src(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_3_pud_sel(data)                                 ((0x00001000&(data))>>12)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_shift                                         (11)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_mask                                          (0x00000800)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt(data)                                         (0x00000800&((data)<<11))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_smt_src(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_smt(data)                                     ((0x00000800&(data))>>11)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_shift                                          (10)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_mask                                           (0x00000400)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2(data)                                          (0x00000400&((data)<<10))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_e2_src(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_e2(data)                                      ((0x00000400&(data))>>10)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_shift                                      (9)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_mask                                       (0x00000200)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en(data)                                      (0x00000200&((data)<<9))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_en_src(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_pud_en(data)                                  ((0x00000200&(data))>>9)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_shift                                     (8)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_mask                                      (0x00000100)
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel(data)                                     (0x00000100&((data)<<8))
#define SB2_PFUNC_RG5_rgmii1_rxd_2_pud_sel_src(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_2_pud_sel(data)                                 ((0x00000100&(data))>>8)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_shift                                         (7)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_mask                                          (0x00000080)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt(data)                                         (0x00000080&((data)<<7))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_smt_src(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_smt(data)                                     ((0x00000080&(data))>>7)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_shift                                          (6)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_mask                                           (0x00000040)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2(data)                                          (0x00000040&((data)<<6))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_e2_src(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_e2(data)                                      ((0x00000040&(data))>>6)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_shift                                      (5)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_mask                                       (0x00000020)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en(data)                                      (0x00000020&((data)<<5))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_en_src(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_pud_en(data)                                  ((0x00000020&(data))>>5)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_shift                                     (4)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_mask                                      (0x00000010)
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel(data)                                     (0x00000010&((data)<<4))
#define SB2_PFUNC_RG5_rgmii1_rxd_1_pud_sel_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_1_pud_sel(data)                                 ((0x00000010&(data))>>4)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_shift                                         (3)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_mask                                          (0x00000008)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt(data)                                         (0x00000008&((data)<<3))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_smt_src(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_smt(data)                                     ((0x00000008&(data))>>3)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_shift                                          (2)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_mask                                           (0x00000004)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2(data)                                          (0x00000004&((data)<<2))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_e2_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_e2(data)                                      ((0x00000004&(data))>>2)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_shift                                      (1)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_mask                                       (0x00000002)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en(data)                                      (0x00000002&((data)<<1))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_en_src(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_pud_en(data)                                  ((0x00000002&(data))>>1)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_shift                                     (0)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_mask                                      (0x00000001)
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel(data)                                     (0x00000001&((data)<<0))
#define SB2_PFUNC_RG5_rgmii1_rxd_0_pud_sel_src(data)                                 ((0x00000001&(data))>>0)
#define SB2_PFUNC_RG5_get_rgmii1_rxd_0_pud_sel(data)                                 ((0x00000001&(data))>>0)


#define SB2_MUXPAD_RG1                                                               0x9801A97C
#define SB2_MUXPAD_RG1_reg_addr                                                      "0xD801A97C"
#define SB2_MUXPAD_RG1_reg                                                           0xD801A97C
#define set_SB2_MUXPAD_RG1_reg(data)   (*((volatile unsigned int*) SB2_MUXPAD_RG1_reg)=data)
#define get_SB2_MUXPAD_RG1_reg   (*((volatile unsigned int*) SB2_MUXPAD_RG1_reg))
#define SB2_MUXPAD_RG1_inst_adr                                                      "0x005F"
#define SB2_MUXPAD_RG1_inst                                                          0x005F
#define SB2_MUXPAD_RG1_rgmii1_mdc_shift                                              (26)
#define SB2_MUXPAD_RG1_rgmii1_mdc_mask                                               (0x0C000000)
#define SB2_MUXPAD_RG1_rgmii1_mdc(data)                                              (0x0C000000&((data)<<26))
#define SB2_MUXPAD_RG1_rgmii1_mdc_src(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG1_get_rgmii1_mdc(data)                                          ((0x0C000000&(data))>>26)
#define SB2_MUXPAD_RG1_rgmii1_mdio_shift                                             (24)
#define SB2_MUXPAD_RG1_rgmii1_mdio_mask                                              (0x03000000)
#define SB2_MUXPAD_RG1_rgmii1_mdio(data)                                             (0x03000000&((data)<<24))
#define SB2_MUXPAD_RG1_rgmii1_mdio_src(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG1_get_rgmii1_mdio(data)                                         ((0x03000000&(data))>>24)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_shift                                            (22)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_mask                                             (0x00C00000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_3(data)                                            (0x00C00000&((data)<<22))
#define SB2_MUXPAD_RG1_rgmii1_rxd_3_src(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_3(data)                                        ((0x00C00000&(data))>>22)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_shift                                            (20)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_mask                                             (0x00300000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_2(data)                                            (0x00300000&((data)<<20))
#define SB2_MUXPAD_RG1_rgmii1_rxd_2_src(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_2(data)                                        ((0x00300000&(data))>>20)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_shift                                            (18)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_mask                                             (0x000C0000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_1(data)                                            (0x000C0000&((data)<<18))
#define SB2_MUXPAD_RG1_rgmii1_rxd_1_src(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_1(data)                                        ((0x000C0000&(data))>>18)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_shift                                            (16)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_mask                                             (0x00030000)
#define SB2_MUXPAD_RG1_rgmii1_rxd_0(data)                                            (0x00030000&((data)<<16))
#define SB2_MUXPAD_RG1_rgmii1_rxd_0_src(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG1_get_rgmii1_rxd_0(data)                                        ((0x00030000&(data))>>16)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_shift                                           (14)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_mask                                            (0x0000C000)
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl(data)                                           (0x0000C000&((data)<<14))
#define SB2_MUXPAD_RG1_rgmii1_rx_ctl_src(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG1_get_rgmii1_rx_ctl(data)                                       ((0x0000C000&(data))>>14)
#define SB2_MUXPAD_RG1_rgmii1_rxc_shift                                              (12)
#define SB2_MUXPAD_RG1_rgmii1_rxc_mask                                               (0x00003000)
#define SB2_MUXPAD_RG1_rgmii1_rxc(data)                                              (0x00003000&((data)<<12))
#define SB2_MUXPAD_RG1_rgmii1_rxc_src(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG1_get_rgmii1_rxc(data)                                          ((0x00003000&(data))>>12)
#define SB2_MUXPAD_RG1_rgmii1_txd_3_shift                                            (10)
#define SB2_MUXPAD_RG1_rgmii1_txd_3_mask                                             (0x00000C00)
#define SB2_MUXPAD_RG1_rgmii1_txd_3(data)                                            (0x00000C00&((data)<<10))
#define SB2_MUXPAD_RG1_rgmii1_txd_3_src(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_3(data)                                        ((0x00000C00&(data))>>10)
#define SB2_MUXPAD_RG1_rgmii1_txd_2_shift                                            (8)
#define SB2_MUXPAD_RG1_rgmii1_txd_2_mask                                             (0x00000300)
#define SB2_MUXPAD_RG1_rgmii1_txd_2(data)                                            (0x00000300&((data)<<8))
#define SB2_MUXPAD_RG1_rgmii1_txd_2_src(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_2(data)                                        ((0x00000300&(data))>>8)
#define SB2_MUXPAD_RG1_rgmii1_txd_1_shift                                            (6)
#define SB2_MUXPAD_RG1_rgmii1_txd_1_mask                                             (0x000000C0)
#define SB2_MUXPAD_RG1_rgmii1_txd_1(data)                                            (0x000000C0&((data)<<6))
#define SB2_MUXPAD_RG1_rgmii1_txd_1_src(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_1(data)                                        ((0x000000C0&(data))>>6)
#define SB2_MUXPAD_RG1_rgmii1_txd_0_shift                                            (4)
#define SB2_MUXPAD_RG1_rgmii1_txd_0_mask                                             (0x00000030)
#define SB2_MUXPAD_RG1_rgmii1_txd_0(data)                                            (0x00000030&((data)<<4))
#define SB2_MUXPAD_RG1_rgmii1_txd_0_src(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG1_get_rgmii1_txd_0(data)                                        ((0x00000030&(data))>>4)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_shift                                           (2)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_mask                                            (0x0000000C)
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl(data)                                           (0x0000000C&((data)<<2))
#define SB2_MUXPAD_RG1_rgmii1_tx_ctl_src(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG1_get_rgmii1_tx_ctl(data)                                       ((0x0000000C&(data))>>2)
#define SB2_MUXPAD_RG1_rgmii1_txc_shift                                              (0)
#define SB2_MUXPAD_RG1_rgmii1_txc_mask                                               (0x00000003)
#define SB2_MUXPAD_RG1_rgmii1_txc(data)                                              (0x00000003&((data)<<0))
#define SB2_MUXPAD_RG1_rgmii1_txc_src(data)                                          ((0x00000003&(data))>>0)
#define SB2_MUXPAD_RG1_get_rgmii1_txc(data)                                          ((0x00000003&(data))>>0)


#define SB2_SATA_PHY_CTRL                                                            0x9801A980
#define SB2_SATA_PHY_CTRL_reg_addr                                                   "0xD801A980"
#define SB2_SATA_PHY_CTRL_reg                                                        0xD801A980
#define set_SB2_SATA_PHY_CTRL_reg(data)   (*((volatile unsigned int*) SB2_SATA_PHY_CTRL_reg)=data)
#define get_SB2_SATA_PHY_CTRL_reg   (*((volatile unsigned int*) SB2_SATA_PHY_CTRL_reg))
#define SB2_SATA_PHY_CTRL_inst_adr                                                   "0x0060"
#define SB2_SATA_PHY_CTRL_inst                                                       0x0060
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_shift                                       (8)
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_mask                                        (0x00000100)
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel(data)                                       (0x00000100&((data)<<8))
#define SB2_SATA_PHY_CTRL_sata_sgmii_sel_src(data)                                   ((0x00000100&(data))>>8)
#define SB2_SATA_PHY_CTRL_get_sata_sgmii_sel(data)                                   ((0x00000100&(data))>>8)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_shift                                 (7)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_mask                                  (0x00000080)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1(data)                                 (0x00000080&((data)<<7))
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_1_src(data)                             ((0x00000080&(data))>>7)
#define SB2_SATA_PHY_CTRL_get_isolate_sata_sgmii_1(data)                             ((0x00000080&(data))>>7)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_shift                                 (6)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_mask                                  (0x00000040)
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0(data)                                 (0x00000040&((data)<<6))
#define SB2_SATA_PHY_CTRL_isolate_sata_sgmii_0_src(data)                             ((0x00000040&(data))>>6)
#define SB2_SATA_PHY_CTRL_get_isolate_sata_sgmii_0(data)                             ((0x00000040&(data))>>6)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_shift                                     (5)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_mask                                      (0x00000020)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1(data)                                     (0x00000020&((data)<<5))
#define SB2_SATA_PHY_CTRL_sata_rx50_link_1_src(data)                                 ((0x00000020&(data))>>5)
#define SB2_SATA_PHY_CTRL_get_sata_rx50_link_1(data)                                 ((0x00000020&(data))>>5)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_shift                                     (4)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_mask                                      (0x00000010)
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0(data)                                     (0x00000010&((data)<<4))
#define SB2_SATA_PHY_CTRL_sata_rx50_link_0_src(data)                                 ((0x00000010&(data))>>4)
#define SB2_SATA_PHY_CTRL_get_sata_rx50_link_0(data)                                 ((0x00000010&(data))>>4)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_shift                                      (3)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_mask                                       (0x00000008)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1(data)                                      (0x00000008&((data)<<3))
#define SB2_SATA_PHY_CTRL_sata_mbias_en_1_src(data)                                  ((0x00000008&(data))>>3)
#define SB2_SATA_PHY_CTRL_get_sata_mbias_en_1(data)                                  ((0x00000008&(data))>>3)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_shift                                      (2)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_mask                                       (0x00000004)
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0(data)                                      (0x00000004&((data)<<2))
#define SB2_SATA_PHY_CTRL_sata_mbias_en_0_src(data)                                  ((0x00000004&(data))>>2)
#define SB2_SATA_PHY_CTRL_get_sata_mbias_en_0(data)                                  ((0x00000004&(data))>>2)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_shift                                         (1)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_mask                                          (0x00000002)
#define SB2_SATA_PHY_CTRL_sata_bg_en_1(data)                                         (0x00000002&((data)<<1))
#define SB2_SATA_PHY_CTRL_sata_bg_en_1_src(data)                                     ((0x00000002&(data))>>1)
#define SB2_SATA_PHY_CTRL_get_sata_bg_en_1(data)                                     ((0x00000002&(data))>>1)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_shift                                         (0)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_mask                                          (0x00000001)
#define SB2_SATA_PHY_CTRL_sata_bg_en_0(data)                                         (0x00000001&((data)<<0))
#define SB2_SATA_PHY_CTRL_sata_bg_en_0_src(data)                                     ((0x00000001&(data))>>0)
#define SB2_SATA_PHY_CTRL_get_sata_bg_en_0(data)                                     ((0x00000001&(data))>>0)


#define SB2_RNG_CTRL                                                                 0x9801AA00
#define SB2_RNG_CTRL_reg_addr                                                        "0xD801AA00"
#define SB2_RNG_CTRL_reg                                                             0xD801AA00
#define set_SB2_RNG_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_CTRL_reg)=data)
#define get_SB2_RNG_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_CTRL_reg))
#define SB2_RNG_CTRL_inst_adr                                                        "0x0080"
#define SB2_RNG_CTRL_inst                                                            0x0080
#define SB2_RNG_CTRL_lfsr_mode_shift                                                 (17)
#define SB2_RNG_CTRL_lfsr_mode_mask                                                  (0x00020000)
#define SB2_RNG_CTRL_lfsr_mode(data)                                                 (0x00020000&((data)<<17))
#define SB2_RNG_CTRL_lfsr_mode_src(data)                                             ((0x00020000&(data))>>17)
#define SB2_RNG_CTRL_get_lfsr_mode(data)                                             ((0x00020000&(data))>>17)
#define SB2_RNG_CTRL_lfsr_bypass_1_shift                                             (16)
#define SB2_RNG_CTRL_lfsr_bypass_1_mask                                              (0x00010000)
#define SB2_RNG_CTRL_lfsr_bypass_1(data)                                             (0x00010000&((data)<<16))
#define SB2_RNG_CTRL_lfsr_bypass_1_src(data)                                         ((0x00010000&(data))>>16)
#define SB2_RNG_CTRL_get_lfsr_bypass_1(data)                                         ((0x00010000&(data))>>16)
#define SB2_RNG_CTRL_dbg1_sel_shift                                                  (12)
#define SB2_RNG_CTRL_dbg1_sel_mask                                                   (0x0000F000)
#define SB2_RNG_CTRL_dbg1_sel(data)                                                  (0x0000F000&((data)<<12))
#define SB2_RNG_CTRL_dbg1_sel_src(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_CTRL_get_dbg1_sel(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_CTRL_dbg0_sel_shift                                                  (8)
#define SB2_RNG_CTRL_dbg0_sel_mask                                                   (0x00000F00)
#define SB2_RNG_CTRL_dbg0_sel(data)                                                  (0x00000F00&((data)<<8))
#define SB2_RNG_CTRL_dbg0_sel_src(data)                                              ((0x00000F00&(data))>>8)
#define SB2_RNG_CTRL_get_dbg0_sel(data)                                              ((0x00000F00&(data))>>8)
#define SB2_RNG_CTRL_corrector_imode_shift                                           (5)
#define SB2_RNG_CTRL_corrector_imode_mask                                            (0x00000020)
#define SB2_RNG_CTRL_corrector_imode(data)                                           (0x00000020&((data)<<5))
#define SB2_RNG_CTRL_corrector_imode_src(data)                                       ((0x00000020&(data))>>5)
#define SB2_RNG_CTRL_get_corrector_imode(data)                                       ((0x00000020&(data))>>5)
#define SB2_RNG_CTRL_rng_cali_srst_shift                                             (3)
#define SB2_RNG_CTRL_rng_cali_srst_mask                                              (0x00000008)
#define SB2_RNG_CTRL_rng_cali_srst(data)                                             (0x00000008&((data)<<3))
#define SB2_RNG_CTRL_rng_cali_srst_src(data)                                         ((0x00000008&(data))>>3)
#define SB2_RNG_CTRL_get_rng_cali_srst(data)                                         ((0x00000008&(data))>>3)
#define SB2_RNG_CTRL_corrector_bypass_shift                                          (2)
#define SB2_RNG_CTRL_corrector_bypass_mask                                           (0x00000004)
#define SB2_RNG_CTRL_corrector_bypass(data)                                          (0x00000004&((data)<<2))
#define SB2_RNG_CTRL_corrector_bypass_src(data)                                      ((0x00000004&(data))>>2)
#define SB2_RNG_CTRL_get_corrector_bypass(data)                                      ((0x00000004&(data))>>2)
#define SB2_RNG_CTRL_clk_hf_sel_shift                                                (1)
#define SB2_RNG_CTRL_clk_hf_sel_mask                                                 (0x00000002)
#define SB2_RNG_CTRL_clk_hf_sel(data)                                                (0x00000002&((data)<<1))
#define SB2_RNG_CTRL_clk_hf_sel_src(data)                                            ((0x00000002&(data))>>1)
#define SB2_RNG_CTRL_get_clk_hf_sel(data)                                            ((0x00000002&(data))>>1)
#define SB2_RNG_CTRL_rng_srst_shift                                                  (0)
#define SB2_RNG_CTRL_rng_srst_mask                                                   (0x00000001)
#define SB2_RNG_CTRL_rng_srst(data)                                                  (0x00000001&((data)<<0))
#define SB2_RNG_CTRL_rng_srst_src(data)                                              ((0x00000001&(data))>>0)
#define SB2_RNG_CTRL_get_rng_srst(data)                                              ((0x00000001&(data))>>0)


#define SB2_RNG_ANALOG                                                               0x9801AA14
#define SB2_RNG_ANALOG_reg_addr                                                      "0xD801AA14"
#define SB2_RNG_ANALOG_reg                                                           0xD801AA14
#define set_SB2_RNG_ANALOG_reg(data)   (*((volatile unsigned int*) SB2_RNG_ANALOG_reg)=data)
#define get_SB2_RNG_ANALOG_reg   (*((volatile unsigned int*) SB2_RNG_ANALOG_reg))
#define SB2_RNG_ANALOG_inst_adr                                                      "0x0085"
#define SB2_RNG_ANALOG_inst                                                          0x0085
#define SB2_RNG_ANALOG_rosc_d_shift                                                  (12)
#define SB2_RNG_ANALOG_rosc_d_mask                                                   (0x0000F000)
#define SB2_RNG_ANALOG_rosc_d(data)                                                  (0x0000F000&((data)<<12))
#define SB2_RNG_ANALOG_rosc_d_src(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_ANALOG_get_rosc_d(data)                                              ((0x0000F000&(data))>>12)
#define SB2_RNG_ANALOG_rosc_res_shift                                                (10)
#define SB2_RNG_ANALOG_rosc_res_mask                                                 (0x00000C00)
#define SB2_RNG_ANALOG_rosc_res(data)                                                (0x00000C00&((data)<<10))
#define SB2_RNG_ANALOG_rosc_res_src(data)                                            ((0x00000C00&(data))>>10)
#define SB2_RNG_ANALOG_get_rosc_res(data)                                            ((0x00000C00&(data))>>10)
#define SB2_RNG_ANALOG_rosc_div_shift                                                (8)
#define SB2_RNG_ANALOG_rosc_div_mask                                                 (0x00000300)
#define SB2_RNG_ANALOG_rosc_div(data)                                                (0x00000300&((data)<<8))
#define SB2_RNG_ANALOG_rosc_div_src(data)                                            ((0x00000300&(data))>>8)
#define SB2_RNG_ANALOG_get_rosc_div(data)                                            ((0x00000300&(data))>>8)
#define SB2_RNG_ANALOG_rosc_gain_shift                                               (6)
#define SB2_RNG_ANALOG_rosc_gain_mask                                                (0x000000C0)
#define SB2_RNG_ANALOG_rosc_gain(data)                                               (0x000000C0&((data)<<6))
#define SB2_RNG_ANALOG_rosc_gain_src(data)                                           ((0x000000C0&(data))>>6)
#define SB2_RNG_ANALOG_get_rosc_gain(data)                                           ((0x000000C0&(data))>>6)
#define SB2_RNG_ANALOG_rosc_fs_shift                                                 (4)
#define SB2_RNG_ANALOG_rosc_fs_mask                                                  (0x00000030)
#define SB2_RNG_ANALOG_rosc_fs(data)                                                 (0x00000030&((data)<<4))
#define SB2_RNG_ANALOG_rosc_fs_src(data)                                             ((0x00000030&(data))>>4)
#define SB2_RNG_ANALOG_get_rosc_fs(data)                                             ((0x00000030&(data))>>4)
#define SB2_RNG_ANALOG_rosc_test_shift                                               (1)
#define SB2_RNG_ANALOG_rosc_test_mask                                                (0x00000002)
#define SB2_RNG_ANALOG_rosc_test(data)                                               (0x00000002&((data)<<1))
#define SB2_RNG_ANALOG_rosc_test_src(data)                                           ((0x00000002&(data))>>1)
#define SB2_RNG_ANALOG_get_rosc_test(data)                                           ((0x00000002&(data))>>1)
#define SB2_RNG_ANALOG_rosc_pow_shift                                                (0)
#define SB2_RNG_ANALOG_rosc_pow_mask                                                 (0x00000001)
#define SB2_RNG_ANALOG_rosc_pow(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_ANALOG_rosc_pow_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_ANALOG_get_rosc_pow(data)                                            ((0x00000001&(data))>>0)


#define SB2_RNG_CALI_CHK                                                             0x9801AA18
#define SB2_RNG_CALI_CHK_reg_addr                                                    "0xD801AA18"
#define SB2_RNG_CALI_CHK_reg                                                         0xD801AA18
#define set_SB2_RNG_CALI_CHK_reg(data)   (*((volatile unsigned int*) SB2_RNG_CALI_CHK_reg)=data)
#define get_SB2_RNG_CALI_CHK_reg   (*((volatile unsigned int*) SB2_RNG_CALI_CHK_reg))
#define SB2_RNG_CALI_CHK_inst_adr                                                    "0x0086"
#define SB2_RNG_CALI_CHK_inst                                                        0x0086
#define SB2_RNG_CALI_CHK_prd_ub_shift                                                (16)
#define SB2_RNG_CALI_CHK_prd_ub_mask                                                 (0xFFFF0000)
#define SB2_RNG_CALI_CHK_prd_ub(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_CALI_CHK_prd_ub_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_CALI_CHK_get_prd_ub(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_CALI_CHK_prd_lb_shift                                                (0)
#define SB2_RNG_CALI_CHK_prd_lb_mask                                                 (0x0000FFFF)
#define SB2_RNG_CALI_CHK_prd_lb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_CALI_CHK_prd_lb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_CALI_CHK_get_prd_lb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_CALI_CTRL                                                            0x9801AA1C
#define SB2_RNG_CALI_CTRL_reg_addr                                                   "0xD801AA1C"
#define SB2_RNG_CALI_CTRL_reg                                                        0xD801AA1C
#define set_SB2_RNG_CALI_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_CALI_CTRL_reg)=data)
#define get_SB2_RNG_CALI_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_CALI_CTRL_reg))
#define SB2_RNG_CALI_CTRL_inst_adr                                                   "0x0087"
#define SB2_RNG_CALI_CTRL_inst                                                       0x0087
#define SB2_RNG_CALI_CTRL_shot_num_shift                                             (20)
#define SB2_RNG_CALI_CTRL_shot_num_mask                                              (0xFFF00000)
#define SB2_RNG_CALI_CTRL_shot_num(data)                                             (0xFFF00000&((data)<<20))
#define SB2_RNG_CALI_CTRL_shot_num_src(data)                                         ((0xFFF00000&(data))>>20)
#define SB2_RNG_CALI_CTRL_get_shot_num(data)                                         ((0xFFF00000&(data))>>20)
#define SB2_RNG_CALI_CTRL_cyc_num_shift                                              (17)
#define SB2_RNG_CALI_CTRL_cyc_num_mask                                               (0x000E0000)
#define SB2_RNG_CALI_CTRL_cyc_num(data)                                              (0x000E0000&((data)<<17))
#define SB2_RNG_CALI_CTRL_cyc_num_src(data)                                          ((0x000E0000&(data))>>17)
#define SB2_RNG_CALI_CTRL_get_cyc_num(data)                                          ((0x000E0000&(data))>>17)
#define SB2_RNG_CALI_CTRL_wait_num_shift                                             (12)
#define SB2_RNG_CALI_CTRL_wait_num_mask                                              (0x0001F000)
#define SB2_RNG_CALI_CTRL_wait_num(data)                                             (0x0001F000&((data)<<12))
#define SB2_RNG_CALI_CTRL_wait_num_src(data)                                         ((0x0001F000&(data))>>12)
#define SB2_RNG_CALI_CTRL_get_wait_num(data)                                         ((0x0001F000&(data))>>12)
#define SB2_RNG_CALI_CTRL_trig_num_shift                                             (4)
#define SB2_RNG_CALI_CTRL_trig_num_mask                                              (0x000001F0)
#define SB2_RNG_CALI_CTRL_trig_num(data)                                             (0x000001F0&((data)<<4))
#define SB2_RNG_CALI_CTRL_trig_num_src(data)                                         ((0x000001F0&(data))>>4)
#define SB2_RNG_CALI_CTRL_get_trig_num(data)                                         ((0x000001F0&(data))>>4)
#define SB2_RNG_CALI_CTRL_lock_shift                                                 (3)
#define SB2_RNG_CALI_CTRL_lock_mask                                                  (0x00000008)
#define SB2_RNG_CALI_CTRL_lock(data)                                                 (0x00000008&((data)<<3))
#define SB2_RNG_CALI_CTRL_lock_src(data)                                             ((0x00000008&(data))>>3)
#define SB2_RNG_CALI_CTRL_get_lock(data)                                             ((0x00000008&(data))>>3)
#define SB2_RNG_CALI_CTRL_shot_mode_shift                                            (2)
#define SB2_RNG_CALI_CTRL_shot_mode_mask                                             (0x00000004)
#define SB2_RNG_CALI_CTRL_shot_mode(data)                                            (0x00000004&((data)<<2))
#define SB2_RNG_CALI_CTRL_shot_mode_src(data)                                        ((0x00000004&(data))>>2)
#define SB2_RNG_CALI_CTRL_get_shot_mode(data)                                        ((0x00000004&(data))>>2)
#define SB2_RNG_CALI_CTRL_pol_shift                                                  (1)
#define SB2_RNG_CALI_CTRL_pol_mask                                                   (0x00000002)
#define SB2_RNG_CALI_CTRL_pol(data)                                                  (0x00000002&((data)<<1))
#define SB2_RNG_CALI_CTRL_pol_src(data)                                              ((0x00000002&(data))>>1)
#define SB2_RNG_CALI_CTRL_get_pol(data)                                              ((0x00000002&(data))>>1)
#define SB2_RNG_CALI_CTRL_hw_en_shift                                                (0)
#define SB2_RNG_CALI_CTRL_hw_en_mask                                                 (0x00000001)
#define SB2_RNG_CALI_CTRL_hw_en(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_CALI_CTRL_hw_en_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_CALI_CTRL_get_hw_en(data)                                            ((0x00000001&(data))>>0)


#define SB2_RNG_RETURN                                                               0x9801AA20
#define SB2_RNG_RETURN_reg_addr                                                      "0xD801AA20"
#define SB2_RNG_RETURN_reg                                                           0xD801AA20
#define set_SB2_RNG_RETURN_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN_reg)=data)
#define get_SB2_RNG_RETURN_reg   (*((volatile unsigned int*) SB2_RNG_RETURN_reg))
#define SB2_RNG_RETURN_inst_adr                                                      "0x0088"
#define SB2_RNG_RETURN_inst                                                          0x0088
#define SB2_RNG_RETURN_hw_d_shift                                                    (20)
#define SB2_RNG_RETURN_hw_d_mask                                                     (0x00F00000)
#define SB2_RNG_RETURN_hw_d(data)                                                    (0x00F00000&((data)<<20))
#define SB2_RNG_RETURN_hw_d_src(data)                                                ((0x00F00000&(data))>>20)
#define SB2_RNG_RETURN_get_hw_d(data)                                                ((0x00F00000&(data))>>20)
#define SB2_RNG_RETURN_rosc_lock_shift                                               (17)
#define SB2_RNG_RETURN_rosc_lock_mask                                                (0x00020000)
#define SB2_RNG_RETURN_rosc_lock(data)                                               (0x00020000&((data)<<17))
#define SB2_RNG_RETURN_rosc_lock_src(data)                                           ((0x00020000&(data))>>17)
#define SB2_RNG_RETURN_get_rosc_lock(data)                                           ((0x00020000&(data))>>17)
#define SB2_RNG_RETURN_cnt_ovflw_shift                                               (16)
#define SB2_RNG_RETURN_cnt_ovflw_mask                                                (0x00010000)
#define SB2_RNG_RETURN_cnt_ovflw(data)                                               (0x00010000&((data)<<16))
#define SB2_RNG_RETURN_cnt_ovflw_src(data)                                           ((0x00010000&(data))>>16)
#define SB2_RNG_RETURN_get_cnt_ovflw(data)                                           ((0x00010000&(data))>>16)
#define SB2_RNG_RETURN_cnt_shift                                                     (0)
#define SB2_RNG_RETURN_cnt_mask                                                      (0x0000FFFF)
#define SB2_RNG_RETURN_cnt(data)                                                     (0x0000FFFF&((data)<<0))
#define SB2_RNG_RETURN_cnt_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define SB2_RNG_RETURN_get_cnt(data)                                                 ((0x0000FFFF&(data))>>0)


#define SB2_RNG_LOCK_CHK                                                             0x9801AA24
#define SB2_RNG_LOCK_CHK_reg_addr                                                    "0xD801AA24"
#define SB2_RNG_LOCK_CHK_reg                                                         0xD801AA24
#define set_SB2_RNG_LOCK_CHK_reg(data)   (*((volatile unsigned int*) SB2_RNG_LOCK_CHK_reg)=data)
#define get_SB2_RNG_LOCK_CHK_reg   (*((volatile unsigned int*) SB2_RNG_LOCK_CHK_reg))
#define SB2_RNG_LOCK_CHK_inst_adr                                                    "0x0089"
#define SB2_RNG_LOCK_CHK_inst                                                        0x0089
#define SB2_RNG_LOCK_CHK_prd_ub_shift                                                (16)
#define SB2_RNG_LOCK_CHK_prd_ub_mask                                                 (0xFFFF0000)
#define SB2_RNG_LOCK_CHK_prd_ub(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_LOCK_CHK_prd_ub_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_LOCK_CHK_get_prd_ub(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_LOCK_CHK_prd_lb_shift                                                (0)
#define SB2_RNG_LOCK_CHK_prd_lb_mask                                                 (0x0000FFFF)
#define SB2_RNG_LOCK_CHK_prd_lb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_LOCK_CHK_prd_lb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_LOCK_CHK_get_prd_lb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_LOCK_CTRL                                                            0x9801AA28
#define SB2_RNG_LOCK_CTRL_reg_addr                                                   "0xD801AA28"
#define SB2_RNG_LOCK_CTRL_reg                                                        0xD801AA28
#define set_SB2_RNG_LOCK_CTRL_reg(data)   (*((volatile unsigned int*) SB2_RNG_LOCK_CTRL_reg)=data)
#define get_SB2_RNG_LOCK_CTRL_reg   (*((volatile unsigned int*) SB2_RNG_LOCK_CTRL_reg))
#define SB2_RNG_LOCK_CTRL_inst_adr                                                   "0x008A"
#define SB2_RNG_LOCK_CTRL_inst                                                       0x008A
#define SB2_RNG_LOCK_CTRL_exit_num_shift                                             (16)
#define SB2_RNG_LOCK_CTRL_exit_num_mask                                              (0x000F0000)
#define SB2_RNG_LOCK_CTRL_exit_num(data)                                             (0x000F0000&((data)<<16))
#define SB2_RNG_LOCK_CTRL_exit_num_src(data)                                         ((0x000F0000&(data))>>16)
#define SB2_RNG_LOCK_CTRL_get_exit_num(data)                                         ((0x000F0000&(data))>>16)
#define SB2_RNG_LOCK_CTRL_enter_num_shift                                            (0)
#define SB2_RNG_LOCK_CTRL_enter_num_mask                                             (0x0000000F)
#define SB2_RNG_LOCK_CTRL_enter_num(data)                                            (0x0000000F&((data)<<0))
#define SB2_RNG_LOCK_CTRL_enter_num_src(data)                                        ((0x0000000F&(data))>>0)
#define SB2_RNG_LOCK_CTRL_get_enter_num(data)                                        ((0x0000000F&(data))>>0)


#define SB2_RNG_RETURN3                                                              0x9801AA2C
#define SB2_RNG_RETURN3_reg_addr                                                     "0xD801AA2C"
#define SB2_RNG_RETURN3_reg                                                          0xD801AA2C
#define set_SB2_RNG_RETURN3_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN3_reg)=data)
#define get_SB2_RNG_RETURN3_reg   (*((volatile unsigned int*) SB2_RNG_RETURN3_reg))
#define SB2_RNG_RETURN3_inst_adr                                                     "0x008B"
#define SB2_RNG_RETURN3_inst                                                         0x008B
#define SB2_RNG_RETURN3_out_ready_shift                                              (0)
#define SB2_RNG_RETURN3_out_ready_mask                                               (0x00000001)
#define SB2_RNG_RETURN3_out_ready(data)                                              (0x00000001&((data)<<0))
#define SB2_RNG_RETURN3_out_ready_src(data)                                          ((0x00000001&(data))>>0)
#define SB2_RNG_RETURN3_get_out_ready(data)                                          ((0x00000001&(data))>>0)


#define SB2_RNG_RETURN4                                                              0x9801AA30
#define SB2_RNG_RETURN4_reg_addr                                                     "0xD801AA30"
#define SB2_RNG_RETURN4_reg                                                          0xD801AA30
#define set_SB2_RNG_RETURN4_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN4_reg)=data)
#define get_SB2_RNG_RETURN4_reg   (*((volatile unsigned int*) SB2_RNG_RETURN4_reg))
#define SB2_RNG_RETURN4_inst_adr                                                     "0x008C"
#define SB2_RNG_RETURN4_inst                                                         0x008C
#define SB2_RNG_RETURN4_valid_bit_num_shift                                          (0)
#define SB2_RNG_RETURN4_valid_bit_num_mask                                           (0xFFFFFFFF)
#define SB2_RNG_RETURN4_valid_bit_num(data)                                          (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RETURN4_valid_bit_num_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RETURN4_get_valid_bit_num(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_RETURN5                                                              0x9801AA34
#define SB2_RNG_RETURN5_reg_addr                                                     "0xD801AA34"
#define SB2_RNG_RETURN5_reg                                                          0xD801AA34
#define set_SB2_RNG_RETURN5_reg(data)   (*((volatile unsigned int*) SB2_RNG_RETURN5_reg)=data)
#define get_SB2_RNG_RETURN5_reg   (*((volatile unsigned int*) SB2_RNG_RETURN5_reg))
#define SB2_RNG_RETURN5_inst_adr                                                     "0x008D"
#define SB2_RNG_RETURN5_inst                                                         0x008D
#define SB2_RNG_RETURN5_drop_num_shift                                               (0)
#define SB2_RNG_RETURN5_drop_num_mask                                                (0xFFFFFFFF)
#define SB2_RNG_RETURN5_drop_num(data)                                               (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RETURN5_drop_num_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RETURN5_get_drop_num(data)                                           ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_RESULTR                                                              0x9801AA38
#define SB2_RNG_RESULTR_reg_addr                                                     "0xD801AA38"
#define SB2_RNG_RESULTR_reg                                                          0xD801AA38
#define set_SB2_RNG_RESULTR_reg(data)   (*((volatile unsigned int*) SB2_RNG_RESULTR_reg)=data)
#define get_SB2_RNG_RESULTR_reg   (*((volatile unsigned int*) SB2_RNG_RESULTR_reg))
#define SB2_RNG_RESULTR_inst_adr                                                     "0x008E"
#define SB2_RNG_RESULTR_inst                                                         0x008E
#define SB2_RNG_RESULTR_random_out_shift                                             (0)
#define SB2_RNG_RESULTR_random_out_mask                                              (0xFFFFFFFF)
#define SB2_RNG_RESULTR_random_out(data)                                             (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_RESULTR_random_out_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_RESULTR_get_random_out(data)                                         ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_LFSR_POLY_LSB                                                        0x9801AA3C
#define SB2_RNG_LFSR_POLY_LSB_reg_addr                                               "0xD801AA3C"
#define SB2_RNG_LFSR_POLY_LSB_reg                                                    0xD801AA3C
#define set_SB2_RNG_LFSR_POLY_LSB_reg(data)   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_LSB_reg)=data)
#define get_SB2_RNG_LFSR_POLY_LSB_reg   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_LSB_reg))
#define SB2_RNG_LFSR_POLY_LSB_inst_adr                                               "0x008F"
#define SB2_RNG_LFSR_POLY_LSB_inst                                                   0x008F
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_shift                                    (0)
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_mask                                     (0xFFFFFFFF)
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb(data)                                    (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_LFSR_POLY_LSB_lfsr_poly_lsb_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_LFSR_POLY_LSB_get_lfsr_poly_lsb(data)                                ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_LFSR_POLY_MSB                                                        0x9801AA40
#define SB2_RNG_LFSR_POLY_MSB_reg_addr                                               "0xD801AA40"
#define SB2_RNG_LFSR_POLY_MSB_reg                                                    0xD801AA40
#define set_SB2_RNG_LFSR_POLY_MSB_reg(data)   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_MSB_reg)=data)
#define get_SB2_RNG_LFSR_POLY_MSB_reg   (*((volatile unsigned int*) SB2_RNG_LFSR_POLY_MSB_reg))
#define SB2_RNG_LFSR_POLY_MSB_inst_adr                                               "0x0090"
#define SB2_RNG_LFSR_POLY_MSB_inst                                                   0x0090
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_shift                                    (0)
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_mask                                     (0xFFFFFFFF)
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb(data)                                    (0xFFFFFFFF&((data)<<0))
#define SB2_RNG_LFSR_POLY_MSB_lfsr_poly_msb_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define SB2_RNG_LFSR_POLY_MSB_get_lfsr_poly_msb(data)                                ((0xFFFFFFFF&(data))>>0)


#define SB2_RNG_DUMMY                                                                0x9801AA44
#define SB2_RNG_DUMMY_reg_addr                                                       "0xD801AA44"
#define SB2_RNG_DUMMY_reg                                                            0xD801AA44
#define set_SB2_RNG_DUMMY_reg(data)   (*((volatile unsigned int*) SB2_RNG_DUMMY_reg)=data)
#define get_SB2_RNG_DUMMY_reg   (*((volatile unsigned int*) SB2_RNG_DUMMY_reg))
#define SB2_RNG_DUMMY_inst_adr                                                       "0x0091"
#define SB2_RNG_DUMMY_inst                                                           0x0091
#define SB2_RNG_DUMMY_dummy_msb_shift                                                (16)
#define SB2_RNG_DUMMY_dummy_msb_mask                                                 (0xFFFF0000)
#define SB2_RNG_DUMMY_dummy_msb(data)                                                (0xFFFF0000&((data)<<16))
#define SB2_RNG_DUMMY_dummy_msb_src(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_DUMMY_get_dummy_msb(data)                                            ((0xFFFF0000&(data))>>16)
#define SB2_RNG_DUMMY_dummy_lsb_shift                                                (0)
#define SB2_RNG_DUMMY_dummy_lsb_mask                                                 (0x0000FFFF)
#define SB2_RNG_DUMMY_dummy_lsb(data)                                                (0x0000FFFF&((data)<<0))
#define SB2_RNG_DUMMY_dummy_lsb_src(data)                                            ((0x0000FFFF&(data))>>0)
#define SB2_RNG_DUMMY_get_dummy_lsb(data)                                            ((0x0000FFFF&(data))>>0)


#define SB2_RNG_POWER                                                                0x9801AA48
#define SB2_RNG_POWER_reg_addr                                                       "0xD801AA48"
#define SB2_RNG_POWER_reg                                                            0xD801AA48
#define set_SB2_RNG_POWER_reg(data)   (*((volatile unsigned int*) SB2_RNG_POWER_reg)=data)
#define get_SB2_RNG_POWER_reg   (*((volatile unsigned int*) SB2_RNG_POWER_reg))
#define SB2_RNG_POWER_inst_adr                                                       "0x0092"
#define SB2_RNG_POWER_inst                                                           0x0092
#define SB2_RNG_POWER_gating_en_shift                                                (0)
#define SB2_RNG_POWER_gating_en_mask                                                 (0x00000001)
#define SB2_RNG_POWER_gating_en(data)                                                (0x00000001&((data)<<0))
#define SB2_RNG_POWER_gating_en_src(data)                                            ((0x00000001&(data))>>0)
#define SB2_RNG_POWER_get_gating_en(data)                                            ((0x00000001&(data))>>0)


#endif
