/**************************************************************
// Spec Version                  : 0.0.4
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/26 11:25:32
***************************************************************/


#ifndef _NF_SWC_REG_H_INCLUDED_
#define _NF_SWC_REG_H_INCLUDED_
#ifdef  _NF_SWC_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     page_addr0:8;
}NF_SWC_ND_PA0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     page_addr1:8;
}NF_SWC_ND_PA1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     addr_mode:3;
unsigned int     page_addr2:5;
}NF_SWC_ND_PA2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     col_addr0:8;
}NF_SWC_ND_CA0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cmd:8;
}NF_SWC_ND_CMD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dat:8;
}NF_SWC_ND_DAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     xfer:1;
unsigned int     ready_busy:1;
unsigned int     ecc_tran:1;
unsigned int     reserved_1:1;
unsigned int     ecc_enable:1;
unsigned int     tran_mode:3;
}NF_SWC_ND_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     blank_zero_num:5;
}NF_SWC_BLANK_ZERO_NUM;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cmd3:8;
}NF_SWC_CMD3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     page_addr3:3;
unsigned int     reserved_1:5;
}NF_SWC_ND_PA3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     bit_sel:3;
unsigned int     trig_poll:1;
}NF_SWC_POLL_FSTS;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     blank_zero_over:1;
unsigned int     read_ecc_xnor_ena:1;
unsigned int     blank_all_one:1;
unsigned int     blank_ena:1;
}NF_SWC_BLANK_CHK;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     ecc_not_clr:1;
unsigned int     ecc_err:1;
unsigned int     reserved_1:2;
}NF_SWC_ND_ECC;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     col_addr1:8;
}NF_SWC_ND_CA1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     length0:8;
}NF_SWC_DATA_TL0;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     access_mode:1;
unsigned int     reserved_1:1;
unsigned int     length1:6;
}NF_SWC_DATA_TL1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     eot_gen:1;
unsigned int     dma_max_pkt:1;
unsigned int     spec_pkt:1;
unsigned int     reserved_1:1;
}NF_SWC_DMA1_CTL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     pp_start_addr:3;
unsigned int     reserved_1:1;
unsigned int     pp_busy:1;
unsigned int     pp_reset:1;
unsigned int     pp_enable:1;
}NF_SWC_PP_CTL0;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     ecc_bch_72b_mode:3;
unsigned int     ecc_bch_12b_ena:1;
}NF_SWC_ECC_SEL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pp_start_addr:8;
}NF_SWC_PP_CTL1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     pd:5;
}NF_SWC_PD;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     pp_lp_mode:1;
unsigned int     pp_lp_ena:1;
unsigned int     ecc_clk_gate_ena:1;
unsigned int     ip_clk_gate_ena:1;
unsigned int     dma_clk_gate_ena:1;
unsigned int     pp_sram_rdy_num:3;
}NF_SWC_NF_LOW_PWR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dmy1:8;
}NF_SWC_DUMMY_NF1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dmy2:8;
}NF_SWC_DUMMY_NF2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dmy3:8;
}NF_SWC_DUMMY_NF3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Dmy4:8;
}NF_SWC_DUMMY_NF4;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     auto_trig:1;
unsigned int     addr_fbd:1;
unsigned int     pp_empty:1;
unsigned int     spec_auto_case:2;
unsigned int     auto_case:3;
}NF_SWC_AUTO_TRIG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecc_num:8;
}NF_SWC_RSECC_NUM;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rnd_cmd1:8;
}NF_SWC_RND_CMD1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rnd_cmd2:8;
}NF_SWC_RND_CMD2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     data_col_msb:8;
}NF_SWC_RND_DATASTR_COL_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     spr_col_msb:8;
}NF_SWC_RND_SPR_STR_COL_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     spr_col_lsb:8;
}NF_SWC_RND_SPR_STR_COL_L;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     rnd_rw_enable:1;
}NF_SWC_RND_RW_EN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     read_by_pp:1;
unsigned int     reserved_1:7;
}NF_SWC_READ_BY_PP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     max_ecc_num:8;
}NF_SWC_MAX_ECC_NUM;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     T3:8;
}NF_SWC_TIME_PARA3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     T2:8;
}NF_SWC_TIME_PARA2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     T1:8;
}NF_SWC_TIME_PARA1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rand_ready:1;
unsigned int     rand_en:1;
}NF_SWC_RMZ_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rand_seed_low:8;
}NF_SWC_RMZ_SEED_L;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     rand_seed_hi:7;
}NF_SWC_RMZ_SEED_H;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rand_seed_from_reg:1;
unsigned int     reserved_1:1;
unsigned int     rand_seed_num:3;
}NF_SWC_RMZ_SEED_NUM;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     pin_stop:1;
unsigned int     intlev_pin_ena:1;
unsigned int     pin_mux_ena:1;
}NF_SWC_PIN_MUX_STOP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     T_swait_busy:2;
unsigned int     T_WHR_ADL:6;
}NF_SWC_DELAY_CTL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecc_n_stop:1;
unsigned int     reserved_1:7;
}NF_SWC_ECC_STOP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecc_page:8;
}NF_SWC_ECC_PAGE;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     page_cnt:8;
}NF_SWC_PAGE_CNT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     page_len:8;
}NF_SWC_PAGE_LEN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     cmd2:8;
}NF_SWC_CMD2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ecc_pass:1;
unsigned int     ecc_no_check:1;
unsigned int     edo:1;
unsigned int     no_wait_busy:1;
unsigned int     wait_ready:2;
unsigned int     reserved_1:2;
}NF_SWC_MULTI_CHNL_MODE;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     map_sel:1;
unsigned int     access_en:1;
unsigned int     mem_region:4;
}NF_SWC_SRAM_CTL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dram_sa:28;
}NF_SWC_DMA_CTL1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dma_len:16;
}NF_SWC_DMA_CTL2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cp_first:1;
unsigned int     cp_enable:1;
unsigned int     ddr_wr:1;
unsigned int     dma_xfer:1;
}NF_SWC_DMA_CTL3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mcu_pp_sram_lp_ena:1;
unsigned int     sys_clk_gate_ena:1;
unsigned int     cp_clk_gate_ena:1;
unsigned int     dma_sram_lp_ena:1;
unsigned int     dma_sram_rdy_num:4;
}NF_SWC_SYS_LOW_PWR;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     Int8:1;
unsigned int     Int7:1;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     Int4:1;
unsigned int     Int3:1;
unsigned int     Int2:1;
unsigned int     Int1:1;
unsigned int     write_data:1;
}NF_SWC_NAND_ISR;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     Int8En:1;
unsigned int     Int7En:1;
unsigned int     reserved_1:1;
unsigned int     reserved_2:1;
unsigned int     Int4En:1;
unsigned int     Int3En:1;
unsigned int     Int2En:1;
unsigned int     Int1En:1;
unsigned int     write_data:1;
}NF_SWC_NAND_ISREN;

typedef struct 
{
unsigned int     dmy:32;
}NF_SWC_DUMMY_SYS;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_enable3:1;
unsigned int     sel1:3;
unsigned int     write_enable2:1;
unsigned int     sel0:3;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}NF_SWC_DBG;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     cr_nf_hw_pinmux_ena:1;
unsigned int     spare_ddr_ena:1;
unsigned int     per_2k_spr_ena:1;
unsigned int     spare_dram_sa:28;
}NF_SWC_SPR_DDR_CTL;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     cp_length:16;
unsigned int     reserved_1:9;
}NF_SWC_CP_LEN;

#endif

#define NF_SWC_ND_PA0                                                                0x1802F000
#define NF_SWC_ND_PA0_reg_addr                                                       "0xB802F000"
#define NF_SWC_ND_PA0_reg                                                            0xB802F000
#define set_NF_SWC_ND_PA0_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_PA0_reg)=data)
#define get_NF_SWC_ND_PA0_reg   (*((volatile unsigned int*) NF_SWC_ND_PA0_reg))
#define NF_SWC_ND_PA0_inst_adr                                                       "0x0000"
#define NF_SWC_ND_PA0_inst                                                           0x0000
#define NF_SWC_ND_PA0_page_addr0_shift                                               (0)
#define NF_SWC_ND_PA0_page_addr0_mask                                                (0x000000FF)
#define NF_SWC_ND_PA0_page_addr0(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_ND_PA0_page_addr0_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_ND_PA0_get_page_addr0(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_ND_PA1                                                                0x1802F004
#define NF_SWC_ND_PA1_reg_addr                                                       "0xB802F004"
#define NF_SWC_ND_PA1_reg                                                            0xB802F004
#define set_NF_SWC_ND_PA1_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_PA1_reg)=data)
#define get_NF_SWC_ND_PA1_reg   (*((volatile unsigned int*) NF_SWC_ND_PA1_reg))
#define NF_SWC_ND_PA1_inst_adr                                                       "0x0001"
#define NF_SWC_ND_PA1_inst                                                           0x0001
#define NF_SWC_ND_PA1_page_addr1_shift                                               (0)
#define NF_SWC_ND_PA1_page_addr1_mask                                                (0x000000FF)
#define NF_SWC_ND_PA1_page_addr1(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_ND_PA1_page_addr1_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_ND_PA1_get_page_addr1(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_ND_PA2                                                                0x1802F008
#define NF_SWC_ND_PA2_reg_addr                                                       "0xB802F008"
#define NF_SWC_ND_PA2_reg                                                            0xB802F008
#define set_NF_SWC_ND_PA2_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_PA2_reg)=data)
#define get_NF_SWC_ND_PA2_reg   (*((volatile unsigned int*) NF_SWC_ND_PA2_reg))
#define NF_SWC_ND_PA2_inst_adr                                                       "0x0002"
#define NF_SWC_ND_PA2_inst                                                           0x0002
#define NF_SWC_ND_PA2_addr_mode_shift                                                (5)
#define NF_SWC_ND_PA2_addr_mode_mask                                                 (0x000000E0)
#define NF_SWC_ND_PA2_addr_mode(data)                                                (0x000000E0&((data)<<5))
#define NF_SWC_ND_PA2_addr_mode_src(data)                                            ((0x000000E0&(data))>>5)
#define NF_SWC_ND_PA2_get_addr_mode(data)                                            ((0x000000E0&(data))>>5)
#define NF_SWC_ND_PA2_page_addr2_shift                                               (0)
#define NF_SWC_ND_PA2_page_addr2_mask                                                (0x0000001F)
#define NF_SWC_ND_PA2_page_addr2(data)                                               (0x0000001F&((data)<<0))
#define NF_SWC_ND_PA2_page_addr2_src(data)                                           ((0x0000001F&(data))>>0)
#define NF_SWC_ND_PA2_get_page_addr2(data)                                           ((0x0000001F&(data))>>0)


#define NF_SWC_ND_CA0                                                                0x1802F00C
#define NF_SWC_ND_CA0_reg_addr                                                       "0xB802F00C"
#define NF_SWC_ND_CA0_reg                                                            0xB802F00C
#define set_NF_SWC_ND_CA0_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_CA0_reg)=data)
#define get_NF_SWC_ND_CA0_reg   (*((volatile unsigned int*) NF_SWC_ND_CA0_reg))
#define NF_SWC_ND_CA0_inst_adr                                                       "0x0003"
#define NF_SWC_ND_CA0_inst                                                           0x0003
#define NF_SWC_ND_CA0_col_addr0_shift                                                (0)
#define NF_SWC_ND_CA0_col_addr0_mask                                                 (0x000000FF)
#define NF_SWC_ND_CA0_col_addr0(data)                                                (0x000000FF&((data)<<0))
#define NF_SWC_ND_CA0_col_addr0_src(data)                                            ((0x000000FF&(data))>>0)
#define NF_SWC_ND_CA0_get_col_addr0(data)                                            ((0x000000FF&(data))>>0)


#define NF_SWC_ND_CMD                                                                0x1802F010
#define NF_SWC_ND_CMD_reg_addr                                                       "0xB802F010"
#define NF_SWC_ND_CMD_reg                                                            0xB802F010
#define set_NF_SWC_ND_CMD_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_CMD_reg)=data)
#define get_NF_SWC_ND_CMD_reg   (*((volatile unsigned int*) NF_SWC_ND_CMD_reg))
#define NF_SWC_ND_CMD_inst_adr                                                       "0x0004"
#define NF_SWC_ND_CMD_inst                                                           0x0004
#define NF_SWC_ND_CMD_cmd_shift                                                      (0)
#define NF_SWC_ND_CMD_cmd_mask                                                       (0x000000FF)
#define NF_SWC_ND_CMD_cmd(data)                                                      (0x000000FF&((data)<<0))
#define NF_SWC_ND_CMD_cmd_src(data)                                                  ((0x000000FF&(data))>>0)
#define NF_SWC_ND_CMD_get_cmd(data)                                                  ((0x000000FF&(data))>>0)


#define NF_SWC_ND_DAT                                                                0x1802F014
#define NF_SWC_ND_DAT_reg_addr                                                       "0xB802F014"
#define NF_SWC_ND_DAT_reg                                                            0xB802F014
#define set_NF_SWC_ND_DAT_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_DAT_reg)=data)
#define get_NF_SWC_ND_DAT_reg   (*((volatile unsigned int*) NF_SWC_ND_DAT_reg))
#define NF_SWC_ND_DAT_inst_adr                                                       "0x0005"
#define NF_SWC_ND_DAT_inst                                                           0x0005
#define NF_SWC_ND_DAT_dat_shift                                                      (0)
#define NF_SWC_ND_DAT_dat_mask                                                       (0x000000FF)
#define NF_SWC_ND_DAT_dat(data)                                                      (0x000000FF&((data)<<0))
#define NF_SWC_ND_DAT_dat_src(data)                                                  ((0x000000FF&(data))>>0)
#define NF_SWC_ND_DAT_get_dat(data)                                                  ((0x000000FF&(data))>>0)


#define NF_SWC_ND_CTL                                                                0x1802F018
#define NF_SWC_ND_CTL_reg_addr                                                       "0xB802F018"
#define NF_SWC_ND_CTL_reg                                                            0xB802F018
#define set_NF_SWC_ND_CTL_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_CTL_reg)=data)
#define get_NF_SWC_ND_CTL_reg   (*((volatile unsigned int*) NF_SWC_ND_CTL_reg))
#define NF_SWC_ND_CTL_inst_adr                                                       "0x0006"
#define NF_SWC_ND_CTL_inst                                                           0x0006
#define NF_SWC_ND_CTL_xfer_shift                                                     (7)
#define NF_SWC_ND_CTL_xfer_mask                                                      (0x00000080)
#define NF_SWC_ND_CTL_xfer(data)                                                     (0x00000080&((data)<<7))
#define NF_SWC_ND_CTL_xfer_src(data)                                                 ((0x00000080&(data))>>7)
#define NF_SWC_ND_CTL_get_xfer(data)                                                 ((0x00000080&(data))>>7)
#define NF_SWC_ND_CTL_ready_busy_shift                                               (6)
#define NF_SWC_ND_CTL_ready_busy_mask                                                (0x00000040)
#define NF_SWC_ND_CTL_ready_busy(data)                                               (0x00000040&((data)<<6))
#define NF_SWC_ND_CTL_ready_busy_src(data)                                           ((0x00000040&(data))>>6)
#define NF_SWC_ND_CTL_get_ready_busy(data)                                           ((0x00000040&(data))>>6)
#define NF_SWC_ND_CTL_ecc_tran_shift                                                 (5)
#define NF_SWC_ND_CTL_ecc_tran_mask                                                  (0x00000020)
#define NF_SWC_ND_CTL_ecc_tran(data)                                                 (0x00000020&((data)<<5))
#define NF_SWC_ND_CTL_ecc_tran_src(data)                                             ((0x00000020&(data))>>5)
#define NF_SWC_ND_CTL_get_ecc_tran(data)                                             ((0x00000020&(data))>>5)
#define NF_SWC_ND_CTL_ecc_enable_shift                                               (3)
#define NF_SWC_ND_CTL_ecc_enable_mask                                                (0x00000008)
#define NF_SWC_ND_CTL_ecc_enable(data)                                               (0x00000008&((data)<<3))
#define NF_SWC_ND_CTL_ecc_enable_src(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_ND_CTL_get_ecc_enable(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_ND_CTL_tran_mode_shift                                                (0)
#define NF_SWC_ND_CTL_tran_mode_mask                                                 (0x00000007)
#define NF_SWC_ND_CTL_tran_mode(data)                                                (0x00000007&((data)<<0))
#define NF_SWC_ND_CTL_tran_mode_src(data)                                            ((0x00000007&(data))>>0)
#define NF_SWC_ND_CTL_get_tran_mode(data)                                            ((0x00000007&(data))>>0)


#define NF_SWC_BLANK_ZERO_NUM                                                        0x1802F01C
#define NF_SWC_BLANK_ZERO_NUM_reg_addr                                               "0xB802F01C"
#define NF_SWC_BLANK_ZERO_NUM_reg                                                    0xB802F01C
#define set_NF_SWC_BLANK_ZERO_NUM_reg(data)   (*((volatile unsigned int*) NF_SWC_BLANK_ZERO_NUM_reg)=data)
#define get_NF_SWC_BLANK_ZERO_NUM_reg   (*((volatile unsigned int*) NF_SWC_BLANK_ZERO_NUM_reg))
#define NF_SWC_BLANK_ZERO_NUM_inst_adr                                               "0x0007"
#define NF_SWC_BLANK_ZERO_NUM_inst                                                   0x0007
#define NF_SWC_BLANK_ZERO_NUM_blank_zero_num_shift                                   (0)
#define NF_SWC_BLANK_ZERO_NUM_blank_zero_num_mask                                    (0x0000001F)
#define NF_SWC_BLANK_ZERO_NUM_blank_zero_num(data)                                   (0x0000001F&((data)<<0))
#define NF_SWC_BLANK_ZERO_NUM_blank_zero_num_src(data)                               ((0x0000001F&(data))>>0)
#define NF_SWC_BLANK_ZERO_NUM_get_blank_zero_num(data)                               ((0x0000001F&(data))>>0)


#define NF_SWC_CMD3                                                                  0x1802F028
#define NF_SWC_CMD3_reg_addr                                                         "0xB802F028"
#define NF_SWC_CMD3_reg                                                              0xB802F028
#define set_NF_SWC_CMD3_reg(data)   (*((volatile unsigned int*) NF_SWC_CMD3_reg)=data)
#define get_NF_SWC_CMD3_reg   (*((volatile unsigned int*) NF_SWC_CMD3_reg))
#define NF_SWC_CMD3_inst_adr                                                         "0x000A"
#define NF_SWC_CMD3_inst                                                             0x000A
#define NF_SWC_CMD3_cmd3_shift                                                       (0)
#define NF_SWC_CMD3_cmd3_mask                                                        (0x000000FF)
#define NF_SWC_CMD3_cmd3(data)                                                       (0x000000FF&((data)<<0))
#define NF_SWC_CMD3_cmd3_src(data)                                                   ((0x000000FF&(data))>>0)
#define NF_SWC_CMD3_get_cmd3(data)                                                   ((0x000000FF&(data))>>0)


#define NF_SWC_ND_PA3                                                                0x1802F02C
#define NF_SWC_ND_PA3_reg_addr                                                       "0xB802F02C"
#define NF_SWC_ND_PA3_reg                                                            0xB802F02C
#define set_NF_SWC_ND_PA3_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_PA3_reg)=data)
#define get_NF_SWC_ND_PA3_reg   (*((volatile unsigned int*) NF_SWC_ND_PA3_reg))
#define NF_SWC_ND_PA3_inst_adr                                                       "0x000B"
#define NF_SWC_ND_PA3_inst                                                           0x000B
#define NF_SWC_ND_PA3_page_addr3_shift                                               (5)
#define NF_SWC_ND_PA3_page_addr3_mask                                                (0x000000E0)
#define NF_SWC_ND_PA3_page_addr3(data)                                               (0x000000E0&((data)<<5))
#define NF_SWC_ND_PA3_page_addr3_src(data)                                           ((0x000000E0&(data))>>5)
#define NF_SWC_ND_PA3_get_page_addr3(data)                                           ((0x000000E0&(data))>>5)


#define NF_SWC_POLL_FSTS                                                             0x1802F030
#define NF_SWC_POLL_FSTS_reg_addr                                                    "0xB802F030"
#define NF_SWC_POLL_FSTS_reg                                                         0xB802F030
#define set_NF_SWC_POLL_FSTS_reg(data)   (*((volatile unsigned int*) NF_SWC_POLL_FSTS_reg)=data)
#define get_NF_SWC_POLL_FSTS_reg   (*((volatile unsigned int*) NF_SWC_POLL_FSTS_reg))
#define NF_SWC_POLL_FSTS_inst_adr                                                    "0x000C"
#define NF_SWC_POLL_FSTS_inst                                                        0x000C
#define NF_SWC_POLL_FSTS_bit_sel_shift                                               (1)
#define NF_SWC_POLL_FSTS_bit_sel_mask                                                (0x0000000E)
#define NF_SWC_POLL_FSTS_bit_sel(data)                                               (0x0000000E&((data)<<1))
#define NF_SWC_POLL_FSTS_bit_sel_src(data)                                           ((0x0000000E&(data))>>1)
#define NF_SWC_POLL_FSTS_get_bit_sel(data)                                           ((0x0000000E&(data))>>1)
#define NF_SWC_POLL_FSTS_trig_poll_shift                                             (0)
#define NF_SWC_POLL_FSTS_trig_poll_mask                                              (0x00000001)
#define NF_SWC_POLL_FSTS_trig_poll(data)                                             (0x00000001&((data)<<0))
#define NF_SWC_POLL_FSTS_trig_poll_src(data)                                         ((0x00000001&(data))>>0)
#define NF_SWC_POLL_FSTS_get_trig_poll(data)                                         ((0x00000001&(data))>>0)


#define NF_SWC_BLANK_CHK                                                             0x1802F034
#define NF_SWC_BLANK_CHK_reg_addr                                                    "0xB802F034"
#define NF_SWC_BLANK_CHK_reg                                                         0xB802F034
#define set_NF_SWC_BLANK_CHK_reg(data)   (*((volatile unsigned int*) NF_SWC_BLANK_CHK_reg)=data)
#define get_NF_SWC_BLANK_CHK_reg   (*((volatile unsigned int*) NF_SWC_BLANK_CHK_reg))
#define NF_SWC_BLANK_CHK_inst_adr                                                    "0x000D"
#define NF_SWC_BLANK_CHK_inst                                                        0x000D
#define NF_SWC_BLANK_CHK_blank_zero_over_shift                                       (3)
#define NF_SWC_BLANK_CHK_blank_zero_over_mask                                        (0x00000008)
#define NF_SWC_BLANK_CHK_blank_zero_over(data)                                       (0x00000008&((data)<<3))
#define NF_SWC_BLANK_CHK_blank_zero_over_src(data)                                   ((0x00000008&(data))>>3)
#define NF_SWC_BLANK_CHK_get_blank_zero_over(data)                                   ((0x00000008&(data))>>3)
#define NF_SWC_BLANK_CHK_read_ecc_xnor_ena_shift                                     (2)
#define NF_SWC_BLANK_CHK_read_ecc_xnor_ena_mask                                      (0x00000004)
#define NF_SWC_BLANK_CHK_read_ecc_xnor_ena(data)                                     (0x00000004&((data)<<2))
#define NF_SWC_BLANK_CHK_read_ecc_xnor_ena_src(data)                                 ((0x00000004&(data))>>2)
#define NF_SWC_BLANK_CHK_get_read_ecc_xnor_ena(data)                                 ((0x00000004&(data))>>2)
#define NF_SWC_BLANK_CHK_blank_all_one_shift                                         (1)
#define NF_SWC_BLANK_CHK_blank_all_one_mask                                          (0x00000002)
#define NF_SWC_BLANK_CHK_blank_all_one(data)                                         (0x00000002&((data)<<1))
#define NF_SWC_BLANK_CHK_blank_all_one_src(data)                                     ((0x00000002&(data))>>1)
#define NF_SWC_BLANK_CHK_get_blank_all_one(data)                                     ((0x00000002&(data))>>1)
#define NF_SWC_BLANK_CHK_blank_ena_shift                                             (0)
#define NF_SWC_BLANK_CHK_blank_ena_mask                                              (0x00000001)
#define NF_SWC_BLANK_CHK_blank_ena(data)                                             (0x00000001&((data)<<0))
#define NF_SWC_BLANK_CHK_blank_ena_src(data)                                         ((0x00000001&(data))>>0)
#define NF_SWC_BLANK_CHK_get_blank_ena(data)                                         ((0x00000001&(data))>>0)


#define NF_SWC_ND_ECC                                                                0x1802F038
#define NF_SWC_ND_ECC_reg_addr                                                       "0xB802F038"
#define NF_SWC_ND_ECC_reg                                                            0xB802F038
#define set_NF_SWC_ND_ECC_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_ECC_reg)=data)
#define get_NF_SWC_ND_ECC_reg   (*((volatile unsigned int*) NF_SWC_ND_ECC_reg))
#define NF_SWC_ND_ECC_inst_adr                                                       "0x000E"
#define NF_SWC_ND_ECC_inst                                                           0x000E
#define NF_SWC_ND_ECC_ecc_not_clr_shift                                              (3)
#define NF_SWC_ND_ECC_ecc_not_clr_mask                                               (0x00000008)
#define NF_SWC_ND_ECC_ecc_not_clr(data)                                              (0x00000008&((data)<<3))
#define NF_SWC_ND_ECC_ecc_not_clr_src(data)                                          ((0x00000008&(data))>>3)
#define NF_SWC_ND_ECC_get_ecc_not_clr(data)                                          ((0x00000008&(data))>>3)
#define NF_SWC_ND_ECC_ecc_err_shift                                                  (2)
#define NF_SWC_ND_ECC_ecc_err_mask                                                   (0x00000004)
#define NF_SWC_ND_ECC_ecc_err(data)                                                  (0x00000004&((data)<<2))
#define NF_SWC_ND_ECC_ecc_err_src(data)                                              ((0x00000004&(data))>>2)
#define NF_SWC_ND_ECC_get_ecc_err(data)                                              ((0x00000004&(data))>>2)


#define NF_SWC_ND_CA1                                                                0x1802F03C
#define NF_SWC_ND_CA1_reg_addr                                                       "0xB802F03C"
#define NF_SWC_ND_CA1_reg                                                            0xB802F03C
#define set_NF_SWC_ND_CA1_reg(data)   (*((volatile unsigned int*) NF_SWC_ND_CA1_reg)=data)
#define get_NF_SWC_ND_CA1_reg   (*((volatile unsigned int*) NF_SWC_ND_CA1_reg))
#define NF_SWC_ND_CA1_inst_adr                                                       "0x000F"
#define NF_SWC_ND_CA1_inst                                                           0x000F
#define NF_SWC_ND_CA1_col_addr1_shift                                                (0)
#define NF_SWC_ND_CA1_col_addr1_mask                                                 (0x000000FF)
#define NF_SWC_ND_CA1_col_addr1(data)                                                (0x000000FF&((data)<<0))
#define NF_SWC_ND_CA1_col_addr1_src(data)                                            ((0x000000FF&(data))>>0)
#define NF_SWC_ND_CA1_get_col_addr1(data)                                            ((0x000000FF&(data))>>0)


#define NF_SWC_DATA_TL0                                                              0x1802F100
#define NF_SWC_DATA_TL0_reg_addr                                                     "0xB802F100"
#define NF_SWC_DATA_TL0_reg                                                          0xB802F100
#define set_NF_SWC_DATA_TL0_reg(data)   (*((volatile unsigned int*) NF_SWC_DATA_TL0_reg)=data)
#define get_NF_SWC_DATA_TL0_reg   (*((volatile unsigned int*) NF_SWC_DATA_TL0_reg))
#define NF_SWC_DATA_TL0_inst_adr                                                     "0x0040"
#define NF_SWC_DATA_TL0_inst                                                         0x0040
#define NF_SWC_DATA_TL0_length0_shift                                                (0)
#define NF_SWC_DATA_TL0_length0_mask                                                 (0x000000FF)
#define NF_SWC_DATA_TL0_length0(data)                                                (0x000000FF&((data)<<0))
#define NF_SWC_DATA_TL0_length0_src(data)                                            ((0x000000FF&(data))>>0)
#define NF_SWC_DATA_TL0_get_length0(data)                                            ((0x000000FF&(data))>>0)


#define NF_SWC_DATA_TL1                                                              0x1802F104
#define NF_SWC_DATA_TL1_reg_addr                                                     "0xB802F104"
#define NF_SWC_DATA_TL1_reg                                                          0xB802F104
#define set_NF_SWC_DATA_TL1_reg(data)   (*((volatile unsigned int*) NF_SWC_DATA_TL1_reg)=data)
#define get_NF_SWC_DATA_TL1_reg   (*((volatile unsigned int*) NF_SWC_DATA_TL1_reg))
#define NF_SWC_DATA_TL1_inst_adr                                                     "0x0041"
#define NF_SWC_DATA_TL1_inst                                                         0x0041
#define NF_SWC_DATA_TL1_access_mode_shift                                            (7)
#define NF_SWC_DATA_TL1_access_mode_mask                                             (0x00000080)
#define NF_SWC_DATA_TL1_access_mode(data)                                            (0x00000080&((data)<<7))
#define NF_SWC_DATA_TL1_access_mode_src(data)                                        ((0x00000080&(data))>>7)
#define NF_SWC_DATA_TL1_get_access_mode(data)                                        ((0x00000080&(data))>>7)
#define NF_SWC_DATA_TL1_length1_shift                                                (0)
#define NF_SWC_DATA_TL1_length1_mask                                                 (0x0000003F)
#define NF_SWC_DATA_TL1_length1(data)                                                (0x0000003F&((data)<<0))
#define NF_SWC_DATA_TL1_length1_src(data)                                            ((0x0000003F&(data))>>0)
#define NF_SWC_DATA_TL1_get_length1(data)                                            ((0x0000003F&(data))>>0)


#define NF_SWC_DMA1_CTL                                                              0x1802F10C
#define NF_SWC_DMA1_CTL_reg_addr                                                     "0xB802F10C"
#define NF_SWC_DMA1_CTL_reg                                                          0xB802F10C
#define set_NF_SWC_DMA1_CTL_reg(data)   (*((volatile unsigned int*) NF_SWC_DMA1_CTL_reg)=data)
#define get_NF_SWC_DMA1_CTL_reg   (*((volatile unsigned int*) NF_SWC_DMA1_CTL_reg))
#define NF_SWC_DMA1_CTL_inst_adr                                                     "0x0043"
#define NF_SWC_DMA1_CTL_inst                                                         0x0043
#define NF_SWC_DMA1_CTL_eot_gen_shift                                                (3)
#define NF_SWC_DMA1_CTL_eot_gen_mask                                                 (0x00000008)
#define NF_SWC_DMA1_CTL_eot_gen(data)                                                (0x00000008&((data)<<3))
#define NF_SWC_DMA1_CTL_eot_gen_src(data)                                            ((0x00000008&(data))>>3)
#define NF_SWC_DMA1_CTL_get_eot_gen(data)                                            ((0x00000008&(data))>>3)
#define NF_SWC_DMA1_CTL_dma_max_pkt_shift                                            (2)
#define NF_SWC_DMA1_CTL_dma_max_pkt_mask                                             (0x00000004)
#define NF_SWC_DMA1_CTL_dma_max_pkt(data)                                            (0x00000004&((data)<<2))
#define NF_SWC_DMA1_CTL_dma_max_pkt_src(data)                                        ((0x00000004&(data))>>2)
#define NF_SWC_DMA1_CTL_get_dma_max_pkt(data)                                        ((0x00000004&(data))>>2)
#define NF_SWC_DMA1_CTL_spec_pkt_shift                                               (1)
#define NF_SWC_DMA1_CTL_spec_pkt_mask                                                (0x00000002)
#define NF_SWC_DMA1_CTL_spec_pkt(data)                                               (0x00000002&((data)<<1))
#define NF_SWC_DMA1_CTL_spec_pkt_src(data)                                           ((0x00000002&(data))>>1)
#define NF_SWC_DMA1_CTL_get_spec_pkt(data)                                           ((0x00000002&(data))>>1)


#define NF_SWC_PP_CTL0                                                               0x1802F110
#define NF_SWC_PP_CTL0_reg_addr                                                      "0xB802F110"
#define NF_SWC_PP_CTL0_reg                                                           0xB802F110
#define set_NF_SWC_PP_CTL0_reg(data)   (*((volatile unsigned int*) NF_SWC_PP_CTL0_reg)=data)
#define get_NF_SWC_PP_CTL0_reg   (*((volatile unsigned int*) NF_SWC_PP_CTL0_reg))
#define NF_SWC_PP_CTL0_inst_adr                                                      "0x0044"
#define NF_SWC_PP_CTL0_inst                                                          0x0044
#define NF_SWC_PP_CTL0_pp_start_addr_shift                                           (4)
#define NF_SWC_PP_CTL0_pp_start_addr_mask                                            (0x00000070)
#define NF_SWC_PP_CTL0_pp_start_addr(data)                                           (0x00000070&((data)<<4))
#define NF_SWC_PP_CTL0_pp_start_addr_src(data)                                       ((0x00000070&(data))>>4)
#define NF_SWC_PP_CTL0_get_pp_start_addr(data)                                       ((0x00000070&(data))>>4)
#define NF_SWC_PP_CTL0_pp_busy_shift                                                 (2)
#define NF_SWC_PP_CTL0_pp_busy_mask                                                  (0x00000004)
#define NF_SWC_PP_CTL0_pp_busy(data)                                                 (0x00000004&((data)<<2))
#define NF_SWC_PP_CTL0_pp_busy_src(data)                                             ((0x00000004&(data))>>2)
#define NF_SWC_PP_CTL0_get_pp_busy(data)                                             ((0x00000004&(data))>>2)
#define NF_SWC_PP_CTL0_pp_reset_shift                                                (1)
#define NF_SWC_PP_CTL0_pp_reset_mask                                                 (0x00000002)
#define NF_SWC_PP_CTL0_pp_reset(data)                                                (0x00000002&((data)<<1))
#define NF_SWC_PP_CTL0_pp_reset_src(data)                                            ((0x00000002&(data))>>1)
#define NF_SWC_PP_CTL0_get_pp_reset(data)                                            ((0x00000002&(data))>>1)
#define NF_SWC_PP_CTL0_pp_enable_shift                                               (0)
#define NF_SWC_PP_CTL0_pp_enable_mask                                                (0x00000001)
#define NF_SWC_PP_CTL0_pp_enable(data)                                               (0x00000001&((data)<<0))
#define NF_SWC_PP_CTL0_pp_enable_src(data)                                           ((0x00000001&(data))>>0)
#define NF_SWC_PP_CTL0_get_pp_enable(data)                                           ((0x00000001&(data))>>0)


#define NF_SWC_ECC_SEL                                                               0x1802F128
#define NF_SWC_ECC_SEL_reg_addr                                                      "0xB802F128"
#define NF_SWC_ECC_SEL_reg                                                           0xB802F128
#define set_NF_SWC_ECC_SEL_reg(data)   (*((volatile unsigned int*) NF_SWC_ECC_SEL_reg)=data)
#define get_NF_SWC_ECC_SEL_reg   (*((volatile unsigned int*) NF_SWC_ECC_SEL_reg))
#define NF_SWC_ECC_SEL_inst_adr                                                      "0x004A"
#define NF_SWC_ECC_SEL_inst                                                          0x004A
#define NF_SWC_ECC_SEL_ecc_bch_72b_mode_shift                                        (1)
#define NF_SWC_ECC_SEL_ecc_bch_72b_mode_mask                                         (0x0000000E)
#define NF_SWC_ECC_SEL_ecc_bch_72b_mode(data)                                        (0x0000000E&((data)<<1))
#define NF_SWC_ECC_SEL_ecc_bch_72b_mode_src(data)                                    ((0x0000000E&(data))>>1)
#define NF_SWC_ECC_SEL_get_ecc_bch_72b_mode(data)                                    ((0x0000000E&(data))>>1)
#define NF_SWC_ECC_SEL_ecc_bch_12b_ena_shift                                         (0)
#define NF_SWC_ECC_SEL_ecc_bch_12b_ena_mask                                          (0x00000001)
#define NF_SWC_ECC_SEL_ecc_bch_12b_ena(data)                                         (0x00000001&((data)<<0))
#define NF_SWC_ECC_SEL_ecc_bch_12b_ena_src(data)                                     ((0x00000001&(data))>>0)
#define NF_SWC_ECC_SEL_get_ecc_bch_12b_ena(data)                                     ((0x00000001&(data))>>0)


#define NF_SWC_PP_CTL1                                                               0x1802F12C
#define NF_SWC_PP_CTL1_reg_addr                                                      "0xB802F12C"
#define NF_SWC_PP_CTL1_reg                                                           0xB802F12C
#define set_NF_SWC_PP_CTL1_reg(data)   (*((volatile unsigned int*) NF_SWC_PP_CTL1_reg)=data)
#define get_NF_SWC_PP_CTL1_reg   (*((volatile unsigned int*) NF_SWC_PP_CTL1_reg))
#define NF_SWC_PP_CTL1_inst_adr                                                      "0x004B"
#define NF_SWC_PP_CTL1_inst                                                          0x004B
#define NF_SWC_PP_CTL1_pp_start_addr_shift                                           (0)
#define NF_SWC_PP_CTL1_pp_start_addr_mask                                            (0x000000FF)
#define NF_SWC_PP_CTL1_pp_start_addr(data)                                           (0x000000FF&((data)<<0))
#define NF_SWC_PP_CTL1_pp_start_addr_src(data)                                       ((0x000000FF&(data))>>0)
#define NF_SWC_PP_CTL1_get_pp_start_addr(data)                                       ((0x000000FF&(data))>>0)


#define NF_SWC_PD                                                                    0x1802F130
#define NF_SWC_PD_reg_addr                                                           "0xB802F130"
#define NF_SWC_PD_reg                                                                0xB802F130
#define set_NF_SWC_PD_reg(data)   (*((volatile unsigned int*) NF_SWC_PD_reg)=data)
#define get_NF_SWC_PD_reg   (*((volatile unsigned int*) NF_SWC_PD_reg))
#define NF_SWC_PD_inst_adr                                                           "0x004C"
#define NF_SWC_PD_inst                                                               0x004C
#define NF_SWC_PD_pd_shift                                                           (0)
#define NF_SWC_PD_pd_mask                                                            (0x0000001F)
#define NF_SWC_PD_pd(data)                                                           (0x0000001F&((data)<<0))
#define NF_SWC_PD_pd_src(data)                                                       ((0x0000001F&(data))>>0)
#define NF_SWC_PD_get_pd(data)                                                       ((0x0000001F&(data))>>0)


#define NF_SWC_NF_LOW_PWR                                                            0x1802F13C
#define NF_SWC_NF_LOW_PWR_reg_addr                                                   "0xB802F13C"
#define NF_SWC_NF_LOW_PWR_reg                                                        0xB802F13C
#define set_NF_SWC_NF_LOW_PWR_reg(data)   (*((volatile unsigned int*) NF_SWC_NF_LOW_PWR_reg)=data)
#define get_NF_SWC_NF_LOW_PWR_reg   (*((volatile unsigned int*) NF_SWC_NF_LOW_PWR_reg))
#define NF_SWC_NF_LOW_PWR_inst_adr                                                   "0x004F"
#define NF_SWC_NF_LOW_PWR_inst                                                       0x004F
#define NF_SWC_NF_LOW_PWR_pp_lp_mode_shift                                           (7)
#define NF_SWC_NF_LOW_PWR_pp_lp_mode_mask                                            (0x00000080)
#define NF_SWC_NF_LOW_PWR_pp_lp_mode(data)                                           (0x00000080&((data)<<7))
#define NF_SWC_NF_LOW_PWR_pp_lp_mode_src(data)                                       ((0x00000080&(data))>>7)
#define NF_SWC_NF_LOW_PWR_get_pp_lp_mode(data)                                       ((0x00000080&(data))>>7)
#define NF_SWC_NF_LOW_PWR_pp_lp_ena_shift                                            (6)
#define NF_SWC_NF_LOW_PWR_pp_lp_ena_mask                                             (0x00000040)
#define NF_SWC_NF_LOW_PWR_pp_lp_ena(data)                                            (0x00000040&((data)<<6))
#define NF_SWC_NF_LOW_PWR_pp_lp_ena_src(data)                                        ((0x00000040&(data))>>6)
#define NF_SWC_NF_LOW_PWR_get_pp_lp_ena(data)                                        ((0x00000040&(data))>>6)
#define NF_SWC_NF_LOW_PWR_ecc_clk_gate_ena_shift                                     (5)
#define NF_SWC_NF_LOW_PWR_ecc_clk_gate_ena_mask                                      (0x00000020)
#define NF_SWC_NF_LOW_PWR_ecc_clk_gate_ena(data)                                     (0x00000020&((data)<<5))
#define NF_SWC_NF_LOW_PWR_ecc_clk_gate_ena_src(data)                                 ((0x00000020&(data))>>5)
#define NF_SWC_NF_LOW_PWR_get_ecc_clk_gate_ena(data)                                 ((0x00000020&(data))>>5)
#define NF_SWC_NF_LOW_PWR_ip_clk_gate_ena_shift                                      (4)
#define NF_SWC_NF_LOW_PWR_ip_clk_gate_ena_mask                                       (0x00000010)
#define NF_SWC_NF_LOW_PWR_ip_clk_gate_ena(data)                                      (0x00000010&((data)<<4))
#define NF_SWC_NF_LOW_PWR_ip_clk_gate_ena_src(data)                                  ((0x00000010&(data))>>4)
#define NF_SWC_NF_LOW_PWR_get_ip_clk_gate_ena(data)                                  ((0x00000010&(data))>>4)
#define NF_SWC_NF_LOW_PWR_dma_clk_gate_ena_shift                                     (3)
#define NF_SWC_NF_LOW_PWR_dma_clk_gate_ena_mask                                      (0x00000008)
#define NF_SWC_NF_LOW_PWR_dma_clk_gate_ena(data)                                     (0x00000008&((data)<<3))
#define NF_SWC_NF_LOW_PWR_dma_clk_gate_ena_src(data)                                 ((0x00000008&(data))>>3)
#define NF_SWC_NF_LOW_PWR_get_dma_clk_gate_ena(data)                                 ((0x00000008&(data))>>3)
#define NF_SWC_NF_LOW_PWR_pp_sram_rdy_num_shift                                      (0)
#define NF_SWC_NF_LOW_PWR_pp_sram_rdy_num_mask                                       (0x00000007)
#define NF_SWC_NF_LOW_PWR_pp_sram_rdy_num(data)                                      (0x00000007&((data)<<0))
#define NF_SWC_NF_LOW_PWR_pp_sram_rdy_num_src(data)                                  ((0x00000007&(data))>>0)
#define NF_SWC_NF_LOW_PWR_get_pp_sram_rdy_num(data)                                  ((0x00000007&(data))>>0)


#define NF_SWC_DUMMY_NF1                                                             0x1802F158
#define NF_SWC_DUMMY_NF1_reg_addr                                                    "0xB802F158"
#define NF_SWC_DUMMY_NF1_reg                                                         0xB802F158
#define set_NF_SWC_DUMMY_NF1_reg(data)   (*((volatile unsigned int*) NF_SWC_DUMMY_NF1_reg)=data)
#define get_NF_SWC_DUMMY_NF1_reg   (*((volatile unsigned int*) NF_SWC_DUMMY_NF1_reg))
#define NF_SWC_DUMMY_NF1_inst_adr                                                    "0x0056"
#define NF_SWC_DUMMY_NF1_inst                                                        0x0056
#define NF_SWC_DUMMY_NF1_Dmy1_shift                                                  (0)
#define NF_SWC_DUMMY_NF1_Dmy1_mask                                                   (0x000000FF)
#define NF_SWC_DUMMY_NF1_Dmy1(data)                                                  (0x000000FF&((data)<<0))
#define NF_SWC_DUMMY_NF1_Dmy1_src(data)                                              ((0x000000FF&(data))>>0)
#define NF_SWC_DUMMY_NF1_get_Dmy1(data)                                              ((0x000000FF&(data))>>0)


#define NF_SWC_DUMMY_NF2                                                             0x1802F15C
#define NF_SWC_DUMMY_NF2_reg_addr                                                    "0xB802F15C"
#define NF_SWC_DUMMY_NF2_reg                                                         0xB802F15C
#define set_NF_SWC_DUMMY_NF2_reg(data)   (*((volatile unsigned int*) NF_SWC_DUMMY_NF2_reg)=data)
#define get_NF_SWC_DUMMY_NF2_reg   (*((volatile unsigned int*) NF_SWC_DUMMY_NF2_reg))
#define NF_SWC_DUMMY_NF2_inst_adr                                                    "0x0057"
#define NF_SWC_DUMMY_NF2_inst                                                        0x0057
#define NF_SWC_DUMMY_NF2_Dmy2_shift                                                  (0)
#define NF_SWC_DUMMY_NF2_Dmy2_mask                                                   (0x000000FF)
#define NF_SWC_DUMMY_NF2_Dmy2(data)                                                  (0x000000FF&((data)<<0))
#define NF_SWC_DUMMY_NF2_Dmy2_src(data)                                              ((0x000000FF&(data))>>0)
#define NF_SWC_DUMMY_NF2_get_Dmy2(data)                                              ((0x000000FF&(data))>>0)


#define NF_SWC_DUMMY_NF3                                                             0x1802F160
#define NF_SWC_DUMMY_NF3_reg_addr                                                    "0xB802F160"
#define NF_SWC_DUMMY_NF3_reg                                                         0xB802F160
#define set_NF_SWC_DUMMY_NF3_reg(data)   (*((volatile unsigned int*) NF_SWC_DUMMY_NF3_reg)=data)
#define get_NF_SWC_DUMMY_NF3_reg   (*((volatile unsigned int*) NF_SWC_DUMMY_NF3_reg))
#define NF_SWC_DUMMY_NF3_inst_adr                                                    "0x0058"
#define NF_SWC_DUMMY_NF3_inst                                                        0x0058
#define NF_SWC_DUMMY_NF3_Dmy3_shift                                                  (0)
#define NF_SWC_DUMMY_NF3_Dmy3_mask                                                   (0x000000FF)
#define NF_SWC_DUMMY_NF3_Dmy3(data)                                                  (0x000000FF&((data)<<0))
#define NF_SWC_DUMMY_NF3_Dmy3_src(data)                                              ((0x000000FF&(data))>>0)
#define NF_SWC_DUMMY_NF3_get_Dmy3(data)                                              ((0x000000FF&(data))>>0)


#define NF_SWC_DUMMY_NF4                                                             0x1802F164
#define NF_SWC_DUMMY_NF4_reg_addr                                                    "0xB802F164"
#define NF_SWC_DUMMY_NF4_reg                                                         0xB802F164
#define set_NF_SWC_DUMMY_NF4_reg(data)   (*((volatile unsigned int*) NF_SWC_DUMMY_NF4_reg)=data)
#define get_NF_SWC_DUMMY_NF4_reg   (*((volatile unsigned int*) NF_SWC_DUMMY_NF4_reg))
#define NF_SWC_DUMMY_NF4_inst_adr                                                    "0x0059"
#define NF_SWC_DUMMY_NF4_inst                                                        0x0059
#define NF_SWC_DUMMY_NF4_Dmy4_shift                                                  (0)
#define NF_SWC_DUMMY_NF4_Dmy4_mask                                                   (0x000000FF)
#define NF_SWC_DUMMY_NF4_Dmy4(data)                                                  (0x000000FF&((data)<<0))
#define NF_SWC_DUMMY_NF4_Dmy4_src(data)                                              ((0x000000FF&(data))>>0)
#define NF_SWC_DUMMY_NF4_get_Dmy4(data)                                              ((0x000000FF&(data))>>0)


#define NF_SWC_AUTO_TRIG                                                             0x1802F200
#define NF_SWC_AUTO_TRIG_reg_addr                                                    "0xB802F200"
#define NF_SWC_AUTO_TRIG_reg                                                         0xB802F200
#define set_NF_SWC_AUTO_TRIG_reg(data)   (*((volatile unsigned int*) NF_SWC_AUTO_TRIG_reg)=data)
#define get_NF_SWC_AUTO_TRIG_reg   (*((volatile unsigned int*) NF_SWC_AUTO_TRIG_reg))
#define NF_SWC_AUTO_TRIG_inst_adr                                                    "0x0080"
#define NF_SWC_AUTO_TRIG_inst                                                        0x0080
#define NF_SWC_AUTO_TRIG_auto_trig_shift                                             (7)
#define NF_SWC_AUTO_TRIG_auto_trig_mask                                              (0x00000080)
#define NF_SWC_AUTO_TRIG_auto_trig(data)                                             (0x00000080&((data)<<7))
#define NF_SWC_AUTO_TRIG_auto_trig_src(data)                                         ((0x00000080&(data))>>7)
#define NF_SWC_AUTO_TRIG_get_auto_trig(data)                                         ((0x00000080&(data))>>7)
#define NF_SWC_AUTO_TRIG_addr_fbd_shift                                              (6)
#define NF_SWC_AUTO_TRIG_addr_fbd_mask                                               (0x00000040)
#define NF_SWC_AUTO_TRIG_addr_fbd(data)                                              (0x00000040&((data)<<6))
#define NF_SWC_AUTO_TRIG_addr_fbd_src(data)                                          ((0x00000040&(data))>>6)
#define NF_SWC_AUTO_TRIG_get_addr_fbd(data)                                          ((0x00000040&(data))>>6)
#define NF_SWC_AUTO_TRIG_pp_empty_shift                                              (5)
#define NF_SWC_AUTO_TRIG_pp_empty_mask                                               (0x00000020)
#define NF_SWC_AUTO_TRIG_pp_empty(data)                                              (0x00000020&((data)<<5))
#define NF_SWC_AUTO_TRIG_pp_empty_src(data)                                          ((0x00000020&(data))>>5)
#define NF_SWC_AUTO_TRIG_get_pp_empty(data)                                          ((0x00000020&(data))>>5)
#define NF_SWC_AUTO_TRIG_spec_auto_case_shift                                        (3)
#define NF_SWC_AUTO_TRIG_spec_auto_case_mask                                         (0x00000018)
#define NF_SWC_AUTO_TRIG_spec_auto_case(data)                                        (0x00000018&((data)<<3))
#define NF_SWC_AUTO_TRIG_spec_auto_case_src(data)                                    ((0x00000018&(data))>>3)
#define NF_SWC_AUTO_TRIG_get_spec_auto_case(data)                                    ((0x00000018&(data))>>3)
#define NF_SWC_AUTO_TRIG_auto_case_shift                                             (0)
#define NF_SWC_AUTO_TRIG_auto_case_mask                                              (0x00000007)
#define NF_SWC_AUTO_TRIG_auto_case(data)                                             (0x00000007&((data)<<0))
#define NF_SWC_AUTO_TRIG_auto_case_src(data)                                         ((0x00000007&(data))>>0)
#define NF_SWC_AUTO_TRIG_get_auto_case(data)                                         ((0x00000007&(data))>>0)


#define NF_SWC_RSECC_NUM                                                             0x1802F204
#define NF_SWC_RSECC_NUM_reg_addr                                                    "0xB802F204"
#define NF_SWC_RSECC_NUM_reg                                                         0xB802F204
#define set_NF_SWC_RSECC_NUM_reg(data)   (*((volatile unsigned int*) NF_SWC_RSECC_NUM_reg)=data)
#define get_NF_SWC_RSECC_NUM_reg   (*((volatile unsigned int*) NF_SWC_RSECC_NUM_reg))
#define NF_SWC_RSECC_NUM_inst_adr                                                    "0x0081"
#define NF_SWC_RSECC_NUM_inst                                                        0x0081
#define NF_SWC_RSECC_NUM_ecc_num_shift                                               (0)
#define NF_SWC_RSECC_NUM_ecc_num_mask                                                (0x000000FF)
#define NF_SWC_RSECC_NUM_ecc_num(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_RSECC_NUM_ecc_num_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_RSECC_NUM_get_ecc_num(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_RND_CMD1                                                              0x1802F208
#define NF_SWC_RND_CMD1_reg_addr                                                     "0xB802F208"
#define NF_SWC_RND_CMD1_reg                                                          0xB802F208
#define set_NF_SWC_RND_CMD1_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_CMD1_reg)=data)
#define get_NF_SWC_RND_CMD1_reg   (*((volatile unsigned int*) NF_SWC_RND_CMD1_reg))
#define NF_SWC_RND_CMD1_inst_adr                                                     "0x0082"
#define NF_SWC_RND_CMD1_inst                                                         0x0082
#define NF_SWC_RND_CMD1_rnd_cmd1_shift                                               (0)
#define NF_SWC_RND_CMD1_rnd_cmd1_mask                                                (0x000000FF)
#define NF_SWC_RND_CMD1_rnd_cmd1(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_RND_CMD1_rnd_cmd1_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_RND_CMD1_get_rnd_cmd1(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_RND_CMD2                                                              0x1802F20C
#define NF_SWC_RND_CMD2_reg_addr                                                     "0xB802F20C"
#define NF_SWC_RND_CMD2_reg                                                          0xB802F20C
#define set_NF_SWC_RND_CMD2_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_CMD2_reg)=data)
#define get_NF_SWC_RND_CMD2_reg   (*((volatile unsigned int*) NF_SWC_RND_CMD2_reg))
#define NF_SWC_RND_CMD2_inst_adr                                                     "0x0083"
#define NF_SWC_RND_CMD2_inst                                                         0x0083
#define NF_SWC_RND_CMD2_rnd_cmd2_shift                                               (0)
#define NF_SWC_RND_CMD2_rnd_cmd2_mask                                                (0x000000FF)
#define NF_SWC_RND_CMD2_rnd_cmd2(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_RND_CMD2_rnd_cmd2_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_RND_CMD2_get_rnd_cmd2(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_RND_DATASTR_COL_H                                                     0x1802F210
#define NF_SWC_RND_DATASTR_COL_H_reg_addr                                            "0xB802F210"
#define NF_SWC_RND_DATASTR_COL_H_reg                                                 0xB802F210
#define set_NF_SWC_RND_DATASTR_COL_H_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_DATASTR_COL_H_reg)=data)
#define get_NF_SWC_RND_DATASTR_COL_H_reg   (*((volatile unsigned int*) NF_SWC_RND_DATASTR_COL_H_reg))
#define NF_SWC_RND_DATASTR_COL_H_inst_adr                                            "0x0084"
#define NF_SWC_RND_DATASTR_COL_H_inst                                                0x0084
#define NF_SWC_RND_DATASTR_COL_H_data_col_msb_shift                                  (0)
#define NF_SWC_RND_DATASTR_COL_H_data_col_msb_mask                                   (0x000000FF)
#define NF_SWC_RND_DATASTR_COL_H_data_col_msb(data)                                  (0x000000FF&((data)<<0))
#define NF_SWC_RND_DATASTR_COL_H_data_col_msb_src(data)                              ((0x000000FF&(data))>>0)
#define NF_SWC_RND_DATASTR_COL_H_get_data_col_msb(data)                              ((0x000000FF&(data))>>0)


#define NF_SWC_RND_SPR_STR_COL_H                                                     0x1802F214
#define NF_SWC_RND_SPR_STR_COL_H_reg_addr                                            "0xB802F214"
#define NF_SWC_RND_SPR_STR_COL_H_reg                                                 0xB802F214
#define set_NF_SWC_RND_SPR_STR_COL_H_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_SPR_STR_COL_H_reg)=data)
#define get_NF_SWC_RND_SPR_STR_COL_H_reg   (*((volatile unsigned int*) NF_SWC_RND_SPR_STR_COL_H_reg))
#define NF_SWC_RND_SPR_STR_COL_H_inst_adr                                            "0x0085"
#define NF_SWC_RND_SPR_STR_COL_H_inst                                                0x0085
#define NF_SWC_RND_SPR_STR_COL_H_spr_col_msb_shift                                   (0)
#define NF_SWC_RND_SPR_STR_COL_H_spr_col_msb_mask                                    (0x000000FF)
#define NF_SWC_RND_SPR_STR_COL_H_spr_col_msb(data)                                   (0x000000FF&((data)<<0))
#define NF_SWC_RND_SPR_STR_COL_H_spr_col_msb_src(data)                               ((0x000000FF&(data))>>0)
#define NF_SWC_RND_SPR_STR_COL_H_get_spr_col_msb(data)                               ((0x000000FF&(data))>>0)


#define NF_SWC_RND_SPR_STR_COL_L                                                     0x1802F218
#define NF_SWC_RND_SPR_STR_COL_L_reg_addr                                            "0xB802F218"
#define NF_SWC_RND_SPR_STR_COL_L_reg                                                 0xB802F218
#define set_NF_SWC_RND_SPR_STR_COL_L_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_SPR_STR_COL_L_reg)=data)
#define get_NF_SWC_RND_SPR_STR_COL_L_reg   (*((volatile unsigned int*) NF_SWC_RND_SPR_STR_COL_L_reg))
#define NF_SWC_RND_SPR_STR_COL_L_inst_adr                                            "0x0086"
#define NF_SWC_RND_SPR_STR_COL_L_inst                                                0x0086
#define NF_SWC_RND_SPR_STR_COL_L_spr_col_lsb_shift                                   (0)
#define NF_SWC_RND_SPR_STR_COL_L_spr_col_lsb_mask                                    (0x000000FF)
#define NF_SWC_RND_SPR_STR_COL_L_spr_col_lsb(data)                                   (0x000000FF&((data)<<0))
#define NF_SWC_RND_SPR_STR_COL_L_spr_col_lsb_src(data)                               ((0x000000FF&(data))>>0)
#define NF_SWC_RND_SPR_STR_COL_L_get_spr_col_lsb(data)                               ((0x000000FF&(data))>>0)


#define NF_SWC_RND_RW_EN                                                             0x1802F21C
#define NF_SWC_RND_RW_EN_reg_addr                                                    "0xB802F21C"
#define NF_SWC_RND_RW_EN_reg                                                         0xB802F21C
#define set_NF_SWC_RND_RW_EN_reg(data)   (*((volatile unsigned int*) NF_SWC_RND_RW_EN_reg)=data)
#define get_NF_SWC_RND_RW_EN_reg   (*((volatile unsigned int*) NF_SWC_RND_RW_EN_reg))
#define NF_SWC_RND_RW_EN_inst_adr                                                    "0x0087"
#define NF_SWC_RND_RW_EN_inst                                                        0x0087
#define NF_SWC_RND_RW_EN_rnd_rw_enable_shift                                         (0)
#define NF_SWC_RND_RW_EN_rnd_rw_enable_mask                                          (0x00000001)
#define NF_SWC_RND_RW_EN_rnd_rw_enable(data)                                         (0x00000001&((data)<<0))
#define NF_SWC_RND_RW_EN_rnd_rw_enable_src(data)                                     ((0x00000001&(data))>>0)
#define NF_SWC_RND_RW_EN_get_rnd_rw_enable(data)                                     ((0x00000001&(data))>>0)


#define NF_SWC_READ_BY_PP                                                            0x1802F228
#define NF_SWC_READ_BY_PP_reg_addr                                                   "0xB802F228"
#define NF_SWC_READ_BY_PP_reg                                                        0xB802F228
#define set_NF_SWC_READ_BY_PP_reg(data)   (*((volatile unsigned int*) NF_SWC_READ_BY_PP_reg)=data)
#define get_NF_SWC_READ_BY_PP_reg   (*((volatile unsigned int*) NF_SWC_READ_BY_PP_reg))
#define NF_SWC_READ_BY_PP_inst_adr                                                   "0x008A"
#define NF_SWC_READ_BY_PP_inst                                                       0x008A
#define NF_SWC_READ_BY_PP_read_by_pp_shift                                           (7)
#define NF_SWC_READ_BY_PP_read_by_pp_mask                                            (0x00000080)
#define NF_SWC_READ_BY_PP_read_by_pp(data)                                           (0x00000080&((data)<<7))
#define NF_SWC_READ_BY_PP_read_by_pp_src(data)                                       ((0x00000080&(data))>>7)
#define NF_SWC_READ_BY_PP_get_read_by_pp(data)                                       ((0x00000080&(data))>>7)


#define NF_SWC_MAX_ECC_NUM                                                           0x1802F22C
#define NF_SWC_MAX_ECC_NUM_reg_addr                                                  "0xB802F22C"
#define NF_SWC_MAX_ECC_NUM_reg                                                       0xB802F22C
#define set_NF_SWC_MAX_ECC_NUM_reg(data)   (*((volatile unsigned int*) NF_SWC_MAX_ECC_NUM_reg)=data)
#define get_NF_SWC_MAX_ECC_NUM_reg   (*((volatile unsigned int*) NF_SWC_MAX_ECC_NUM_reg))
#define NF_SWC_MAX_ECC_NUM_inst_adr                                                  "0x008B"
#define NF_SWC_MAX_ECC_NUM_inst                                                      0x008B
#define NF_SWC_MAX_ECC_NUM_max_ecc_num_shift                                         (0)
#define NF_SWC_MAX_ECC_NUM_max_ecc_num_mask                                          (0x000000FF)
#define NF_SWC_MAX_ECC_NUM_max_ecc_num(data)                                         (0x000000FF&((data)<<0))
#define NF_SWC_MAX_ECC_NUM_max_ecc_num_src(data)                                     ((0x000000FF&(data))>>0)
#define NF_SWC_MAX_ECC_NUM_get_max_ecc_num(data)                                     ((0x000000FF&(data))>>0)


#define NF_SWC_TIME_PARA3                                                            0x1802F234
#define NF_SWC_TIME_PARA3_reg_addr                                                   "0xB802F234"
#define NF_SWC_TIME_PARA3_reg                                                        0xB802F234
#define set_NF_SWC_TIME_PARA3_reg(data)   (*((volatile unsigned int*) NF_SWC_TIME_PARA3_reg)=data)
#define get_NF_SWC_TIME_PARA3_reg   (*((volatile unsigned int*) NF_SWC_TIME_PARA3_reg))
#define NF_SWC_TIME_PARA3_inst_adr                                                   "0x008D"
#define NF_SWC_TIME_PARA3_inst                                                       0x008D
#define NF_SWC_TIME_PARA3_T3_shift                                                   (0)
#define NF_SWC_TIME_PARA3_T3_mask                                                    (0x000000FF)
#define NF_SWC_TIME_PARA3_T3(data)                                                   (0x000000FF&((data)<<0))
#define NF_SWC_TIME_PARA3_T3_src(data)                                               ((0x000000FF&(data))>>0)
#define NF_SWC_TIME_PARA3_get_T3(data)                                               ((0x000000FF&(data))>>0)


#define NF_SWC_TIME_PARA2                                                            0x1802F238
#define NF_SWC_TIME_PARA2_reg_addr                                                   "0xB802F238"
#define NF_SWC_TIME_PARA2_reg                                                        0xB802F238
#define set_NF_SWC_TIME_PARA2_reg(data)   (*((volatile unsigned int*) NF_SWC_TIME_PARA2_reg)=data)
#define get_NF_SWC_TIME_PARA2_reg   (*((volatile unsigned int*) NF_SWC_TIME_PARA2_reg))
#define NF_SWC_TIME_PARA2_inst_adr                                                   "0x008E"
#define NF_SWC_TIME_PARA2_inst                                                       0x008E
#define NF_SWC_TIME_PARA2_T2_shift                                                   (0)
#define NF_SWC_TIME_PARA2_T2_mask                                                    (0x000000FF)
#define NF_SWC_TIME_PARA2_T2(data)                                                   (0x000000FF&((data)<<0))
#define NF_SWC_TIME_PARA2_T2_src(data)                                               ((0x000000FF&(data))>>0)
#define NF_SWC_TIME_PARA2_get_T2(data)                                               ((0x000000FF&(data))>>0)


#define NF_SWC_TIME_PARA1                                                            0x1802F23C
#define NF_SWC_TIME_PARA1_reg_addr                                                   "0xB802F23C"
#define NF_SWC_TIME_PARA1_reg                                                        0xB802F23C
#define set_NF_SWC_TIME_PARA1_reg(data)   (*((volatile unsigned int*) NF_SWC_TIME_PARA1_reg)=data)
#define get_NF_SWC_TIME_PARA1_reg   (*((volatile unsigned int*) NF_SWC_TIME_PARA1_reg))
#define NF_SWC_TIME_PARA1_inst_adr                                                   "0x008F"
#define NF_SWC_TIME_PARA1_inst                                                       0x008F
#define NF_SWC_TIME_PARA1_T1_shift                                                   (0)
#define NF_SWC_TIME_PARA1_T1_mask                                                    (0x000000FF)
#define NF_SWC_TIME_PARA1_T1(data)                                                   (0x000000FF&((data)<<0))
#define NF_SWC_TIME_PARA1_T1_src(data)                                               ((0x000000FF&(data))>>0)
#define NF_SWC_TIME_PARA1_get_T1(data)                                               ((0x000000FF&(data))>>0)


#define NF_SWC_RMZ_CTRL                                                              0x1802F240
#define NF_SWC_RMZ_CTRL_reg_addr                                                     "0xB802F240"
#define NF_SWC_RMZ_CTRL_reg                                                          0xB802F240
#define set_NF_SWC_RMZ_CTRL_reg(data)   (*((volatile unsigned int*) NF_SWC_RMZ_CTRL_reg)=data)
#define get_NF_SWC_RMZ_CTRL_reg   (*((volatile unsigned int*) NF_SWC_RMZ_CTRL_reg))
#define NF_SWC_RMZ_CTRL_inst_adr                                                     "0x0090"
#define NF_SWC_RMZ_CTRL_inst                                                         0x0090
#define NF_SWC_RMZ_CTRL_rand_ready_shift                                             (1)
#define NF_SWC_RMZ_CTRL_rand_ready_mask                                              (0x00000002)
#define NF_SWC_RMZ_CTRL_rand_ready(data)                                             (0x00000002&((data)<<1))
#define NF_SWC_RMZ_CTRL_rand_ready_src(data)                                         ((0x00000002&(data))>>1)
#define NF_SWC_RMZ_CTRL_get_rand_ready(data)                                         ((0x00000002&(data))>>1)
#define NF_SWC_RMZ_CTRL_rand_en_shift                                                (0)
#define NF_SWC_RMZ_CTRL_rand_en_mask                                                 (0x00000001)
#define NF_SWC_RMZ_CTRL_rand_en(data)                                                (0x00000001&((data)<<0))
#define NF_SWC_RMZ_CTRL_rand_en_src(data)                                            ((0x00000001&(data))>>0)
#define NF_SWC_RMZ_CTRL_get_rand_en(data)                                            ((0x00000001&(data))>>0)


#define NF_SWC_RMZ_SEED_L                                                            0x1802F244
#define NF_SWC_RMZ_SEED_L_reg_addr                                                   "0xB802F244"
#define NF_SWC_RMZ_SEED_L_reg                                                        0xB802F244
#define set_NF_SWC_RMZ_SEED_L_reg(data)   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_L_reg)=data)
#define get_NF_SWC_RMZ_SEED_L_reg   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_L_reg))
#define NF_SWC_RMZ_SEED_L_inst_adr                                                   "0x0091"
#define NF_SWC_RMZ_SEED_L_inst                                                       0x0091
#define NF_SWC_RMZ_SEED_L_rand_seed_low_shift                                        (0)
#define NF_SWC_RMZ_SEED_L_rand_seed_low_mask                                         (0x000000FF)
#define NF_SWC_RMZ_SEED_L_rand_seed_low(data)                                        (0x000000FF&((data)<<0))
#define NF_SWC_RMZ_SEED_L_rand_seed_low_src(data)                                    ((0x000000FF&(data))>>0)
#define NF_SWC_RMZ_SEED_L_get_rand_seed_low(data)                                    ((0x000000FF&(data))>>0)


#define NF_SWC_RMZ_SEED_H                                                            0x1802F248
#define NF_SWC_RMZ_SEED_H_reg_addr                                                   "0xB802F248"
#define NF_SWC_RMZ_SEED_H_reg                                                        0xB802F248
#define set_NF_SWC_RMZ_SEED_H_reg(data)   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_H_reg)=data)
#define get_NF_SWC_RMZ_SEED_H_reg   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_H_reg))
#define NF_SWC_RMZ_SEED_H_inst_adr                                                   "0x0092"
#define NF_SWC_RMZ_SEED_H_inst                                                       0x0092
#define NF_SWC_RMZ_SEED_H_rand_seed_hi_shift                                         (0)
#define NF_SWC_RMZ_SEED_H_rand_seed_hi_mask                                          (0x0000007F)
#define NF_SWC_RMZ_SEED_H_rand_seed_hi(data)                                         (0x0000007F&((data)<<0))
#define NF_SWC_RMZ_SEED_H_rand_seed_hi_src(data)                                     ((0x0000007F&(data))>>0)
#define NF_SWC_RMZ_SEED_H_get_rand_seed_hi(data)                                     ((0x0000007F&(data))>>0)


#define NF_SWC_RMZ_SEED_NUM                                                          0x1802F24c
#define NF_SWC_RMZ_SEED_NUM_reg_addr                                                 "0xB802F24c"
#define NF_SWC_RMZ_SEED_NUM_reg                                                      0xB802F24c
#define set_NF_SWC_RMZ_SEED_NUM_reg(data)   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_NUM_reg)=data)
#define get_NF_SWC_RMZ_SEED_NUM_reg   (*((volatile unsigned int*) NF_SWC_RMZ_SEED_NUM_reg))
#define NF_SWC_RMZ_SEED_NUM_inst_adr                                                 "0x0093"
#define NF_SWC_RMZ_SEED_NUM_inst                                                     0x0093
#define NF_SWC_RMZ_SEED_NUM_rand_seed_from_reg_shift                                 (4)
#define NF_SWC_RMZ_SEED_NUM_rand_seed_from_reg_mask                                  (0x00000010)
#define NF_SWC_RMZ_SEED_NUM_rand_seed_from_reg(data)                                 (0x00000010&((data)<<4))
#define NF_SWC_RMZ_SEED_NUM_rand_seed_from_reg_src(data)                             ((0x00000010&(data))>>4)
#define NF_SWC_RMZ_SEED_NUM_get_rand_seed_from_reg(data)                             ((0x00000010&(data))>>4)
#define NF_SWC_RMZ_SEED_NUM_rand_seed_num_shift                                      (0)
#define NF_SWC_RMZ_SEED_NUM_rand_seed_num_mask                                       (0x00000007)
#define NF_SWC_RMZ_SEED_NUM_rand_seed_num(data)                                      (0x00000007&((data)<<0))
#define NF_SWC_RMZ_SEED_NUM_rand_seed_num_src(data)                                  ((0x00000007&(data))>>0)
#define NF_SWC_RMZ_SEED_NUM_get_rand_seed_num(data)                                  ((0x00000007&(data))>>0)


#define NF_SWC_PIN_MUX_STOP                                                          0x1802F25C
#define NF_SWC_PIN_MUX_STOP_reg_addr                                                 "0xB802F25C"
#define NF_SWC_PIN_MUX_STOP_reg                                                      0xB802F25C
#define set_NF_SWC_PIN_MUX_STOP_reg(data)   (*((volatile unsigned int*) NF_SWC_PIN_MUX_STOP_reg)=data)
#define get_NF_SWC_PIN_MUX_STOP_reg   (*((volatile unsigned int*) NF_SWC_PIN_MUX_STOP_reg))
#define NF_SWC_PIN_MUX_STOP_inst_adr                                                 "0x0097"
#define NF_SWC_PIN_MUX_STOP_inst                                                     0x0097
#define NF_SWC_PIN_MUX_STOP_pin_stop_shift                                           (2)
#define NF_SWC_PIN_MUX_STOP_pin_stop_mask                                            (0x00000004)
#define NF_SWC_PIN_MUX_STOP_pin_stop(data)                                           (0x00000004&((data)<<2))
#define NF_SWC_PIN_MUX_STOP_pin_stop_src(data)                                       ((0x00000004&(data))>>2)
#define NF_SWC_PIN_MUX_STOP_get_pin_stop(data)                                       ((0x00000004&(data))>>2)
#define NF_SWC_PIN_MUX_STOP_intlev_pin_ena_shift                                     (1)
#define NF_SWC_PIN_MUX_STOP_intlev_pin_ena_mask                                      (0x00000002)
#define NF_SWC_PIN_MUX_STOP_intlev_pin_ena(data)                                     (0x00000002&((data)<<1))
#define NF_SWC_PIN_MUX_STOP_intlev_pin_ena_src(data)                                 ((0x00000002&(data))>>1)
#define NF_SWC_PIN_MUX_STOP_get_intlev_pin_ena(data)                                 ((0x00000002&(data))>>1)
#define NF_SWC_PIN_MUX_STOP_pin_mux_ena_shift                                        (0)
#define NF_SWC_PIN_MUX_STOP_pin_mux_ena_mask                                         (0x00000001)
#define NF_SWC_PIN_MUX_STOP_pin_mux_ena(data)                                        (0x00000001&((data)<<0))
#define NF_SWC_PIN_MUX_STOP_pin_mux_ena_src(data)                                    ((0x00000001&(data))>>0)
#define NF_SWC_PIN_MUX_STOP_get_pin_mux_ena(data)                                    ((0x00000001&(data))>>0)


#define NF_SWC_DELAY_CTL                                                             0x1802F260
#define NF_SWC_DELAY_CTL_reg_addr                                                    "0xB802F260"
#define NF_SWC_DELAY_CTL_reg                                                         0xB802F260
#define set_NF_SWC_DELAY_CTL_reg(data)   (*((volatile unsigned int*) NF_SWC_DELAY_CTL_reg)=data)
#define get_NF_SWC_DELAY_CTL_reg   (*((volatile unsigned int*) NF_SWC_DELAY_CTL_reg))
#define NF_SWC_DELAY_CTL_inst_adr                                                    "0x0098"
#define NF_SWC_DELAY_CTL_inst                                                        0x0098
#define NF_SWC_DELAY_CTL_T_swait_busy_shift                                          (6)
#define NF_SWC_DELAY_CTL_T_swait_busy_mask                                           (0x000000C0)
#define NF_SWC_DELAY_CTL_T_swait_busy(data)                                          (0x000000C0&((data)<<6))
#define NF_SWC_DELAY_CTL_T_swait_busy_src(data)                                      ((0x000000C0&(data))>>6)
#define NF_SWC_DELAY_CTL_get_T_swait_busy(data)                                      ((0x000000C0&(data))>>6)
#define NF_SWC_DELAY_CTL_T_WHR_ADL_shift                                             (0)
#define NF_SWC_DELAY_CTL_T_WHR_ADL_mask                                              (0x0000003F)
#define NF_SWC_DELAY_CTL_T_WHR_ADL(data)                                             (0x0000003F&((data)<<0))
#define NF_SWC_DELAY_CTL_T_WHR_ADL_src(data)                                         ((0x0000003F&(data))>>0)
#define NF_SWC_DELAY_CTL_get_T_WHR_ADL(data)                                         ((0x0000003F&(data))>>0)


#define NF_SWC_ECC_STOP                                                              0x1802F264
#define NF_SWC_ECC_STOP_reg_addr                                                     "0xB802F264"
#define NF_SWC_ECC_STOP_reg                                                          0xB802F264
#define set_NF_SWC_ECC_STOP_reg(data)   (*((volatile unsigned int*) NF_SWC_ECC_STOP_reg)=data)
#define get_NF_SWC_ECC_STOP_reg   (*((volatile unsigned int*) NF_SWC_ECC_STOP_reg))
#define NF_SWC_ECC_STOP_inst_adr                                                     "0x0099"
#define NF_SWC_ECC_STOP_inst                                                         0x0099
#define NF_SWC_ECC_STOP_ecc_n_stop_shift                                             (7)
#define NF_SWC_ECC_STOP_ecc_n_stop_mask                                              (0x00000080)
#define NF_SWC_ECC_STOP_ecc_n_stop(data)                                             (0x00000080&((data)<<7))
#define NF_SWC_ECC_STOP_ecc_n_stop_src(data)                                         ((0x00000080&(data))>>7)
#define NF_SWC_ECC_STOP_get_ecc_n_stop(data)                                         ((0x00000080&(data))>>7)


#define NF_SWC_ECC_PAGE                                                              0x1802F268
#define NF_SWC_ECC_PAGE_reg_addr                                                     "0xB802F268"
#define NF_SWC_ECC_PAGE_reg                                                          0xB802F268
#define set_NF_SWC_ECC_PAGE_reg(data)   (*((volatile unsigned int*) NF_SWC_ECC_PAGE_reg)=data)
#define get_NF_SWC_ECC_PAGE_reg   (*((volatile unsigned int*) NF_SWC_ECC_PAGE_reg))
#define NF_SWC_ECC_PAGE_inst_adr                                                     "0x009A"
#define NF_SWC_ECC_PAGE_inst                                                         0x009A
#define NF_SWC_ECC_PAGE_ecc_page_shift                                               (0)
#define NF_SWC_ECC_PAGE_ecc_page_mask                                                (0x000000FF)
#define NF_SWC_ECC_PAGE_ecc_page(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_ECC_PAGE_ecc_page_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_ECC_PAGE_get_ecc_page(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_PAGE_CNT                                                              0x1802F26C
#define NF_SWC_PAGE_CNT_reg_addr                                                     "0xB802F26C"
#define NF_SWC_PAGE_CNT_reg                                                          0xB802F26C
#define set_NF_SWC_PAGE_CNT_reg(data)   (*((volatile unsigned int*) NF_SWC_PAGE_CNT_reg)=data)
#define get_NF_SWC_PAGE_CNT_reg   (*((volatile unsigned int*) NF_SWC_PAGE_CNT_reg))
#define NF_SWC_PAGE_CNT_inst_adr                                                     "0x009B"
#define NF_SWC_PAGE_CNT_inst                                                         0x009B
#define NF_SWC_PAGE_CNT_page_cnt_shift                                               (0)
#define NF_SWC_PAGE_CNT_page_cnt_mask                                                (0x000000FF)
#define NF_SWC_PAGE_CNT_page_cnt(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_PAGE_CNT_page_cnt_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_PAGE_CNT_get_page_cnt(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_PAGE_LEN                                                              0x1802F270
#define NF_SWC_PAGE_LEN_reg_addr                                                     "0xB802F270"
#define NF_SWC_PAGE_LEN_reg                                                          0xB802F270
#define set_NF_SWC_PAGE_LEN_reg(data)   (*((volatile unsigned int*) NF_SWC_PAGE_LEN_reg)=data)
#define get_NF_SWC_PAGE_LEN_reg   (*((volatile unsigned int*) NF_SWC_PAGE_LEN_reg))
#define NF_SWC_PAGE_LEN_inst_adr                                                     "0x009C"
#define NF_SWC_PAGE_LEN_inst                                                         0x009C
#define NF_SWC_PAGE_LEN_page_len_shift                                               (0)
#define NF_SWC_PAGE_LEN_page_len_mask                                                (0x000000FF)
#define NF_SWC_PAGE_LEN_page_len(data)                                               (0x000000FF&((data)<<0))
#define NF_SWC_PAGE_LEN_page_len_src(data)                                           ((0x000000FF&(data))>>0)
#define NF_SWC_PAGE_LEN_get_page_len(data)                                           ((0x000000FF&(data))>>0)


#define NF_SWC_CMD2                                                                  0x1802F274
#define NF_SWC_CMD2_reg_addr                                                         "0xB802F274"
#define NF_SWC_CMD2_reg                                                              0xB802F274
#define set_NF_SWC_CMD2_reg(data)   (*((volatile unsigned int*) NF_SWC_CMD2_reg)=data)
#define get_NF_SWC_CMD2_reg   (*((volatile unsigned int*) NF_SWC_CMD2_reg))
#define NF_SWC_CMD2_inst_adr                                                         "0x009D"
#define NF_SWC_CMD2_inst                                                             0x009D
#define NF_SWC_CMD2_cmd2_shift                                                       (0)
#define NF_SWC_CMD2_cmd2_mask                                                        (0x000000FF)
#define NF_SWC_CMD2_cmd2(data)                                                       (0x000000FF&((data)<<0))
#define NF_SWC_CMD2_cmd2_src(data)                                                   ((0x000000FF&(data))>>0)
#define NF_SWC_CMD2_get_cmd2(data)                                                   ((0x000000FF&(data))>>0)


#define NF_SWC_MULTI_CHNL_MODE                                                       0x1802F27C
#define NF_SWC_MULTI_CHNL_MODE_reg_addr                                              "0xB802F27C"
#define NF_SWC_MULTI_CHNL_MODE_reg                                                   0xB802F27C
#define set_NF_SWC_MULTI_CHNL_MODE_reg(data)   (*((volatile unsigned int*) NF_SWC_MULTI_CHNL_MODE_reg)=data)
#define get_NF_SWC_MULTI_CHNL_MODE_reg   (*((volatile unsigned int*) NF_SWC_MULTI_CHNL_MODE_reg))
#define NF_SWC_MULTI_CHNL_MODE_inst_adr                                              "0x009F"
#define NF_SWC_MULTI_CHNL_MODE_inst                                                  0x009F
#define NF_SWC_MULTI_CHNL_MODE_ecc_pass_shift                                        (7)
#define NF_SWC_MULTI_CHNL_MODE_ecc_pass_mask                                         (0x00000080)
#define NF_SWC_MULTI_CHNL_MODE_ecc_pass(data)                                        (0x00000080&((data)<<7))
#define NF_SWC_MULTI_CHNL_MODE_ecc_pass_src(data)                                    ((0x00000080&(data))>>7)
#define NF_SWC_MULTI_CHNL_MODE_get_ecc_pass(data)                                    ((0x00000080&(data))>>7)
#define NF_SWC_MULTI_CHNL_MODE_ecc_no_check_shift                                    (6)
#define NF_SWC_MULTI_CHNL_MODE_ecc_no_check_mask                                     (0x00000040)
#define NF_SWC_MULTI_CHNL_MODE_ecc_no_check(data)                                    (0x00000040&((data)<<6))
#define NF_SWC_MULTI_CHNL_MODE_ecc_no_check_src(data)                                ((0x00000040&(data))>>6)
#define NF_SWC_MULTI_CHNL_MODE_get_ecc_no_check(data)                                ((0x00000040&(data))>>6)
#define NF_SWC_MULTI_CHNL_MODE_edo_shift                                             (5)
#define NF_SWC_MULTI_CHNL_MODE_edo_mask                                              (0x00000020)
#define NF_SWC_MULTI_CHNL_MODE_edo(data)                                             (0x00000020&((data)<<5))
#define NF_SWC_MULTI_CHNL_MODE_edo_src(data)                                         ((0x00000020&(data))>>5)
#define NF_SWC_MULTI_CHNL_MODE_get_edo(data)                                         ((0x00000020&(data))>>5)
#define NF_SWC_MULTI_CHNL_MODE_no_wait_busy_shift                                    (4)
#define NF_SWC_MULTI_CHNL_MODE_no_wait_busy_mask                                     (0x00000010)
#define NF_SWC_MULTI_CHNL_MODE_no_wait_busy(data)                                    (0x00000010&((data)<<4))
#define NF_SWC_MULTI_CHNL_MODE_no_wait_busy_src(data)                                ((0x00000010&(data))>>4)
#define NF_SWC_MULTI_CHNL_MODE_get_no_wait_busy(data)                                ((0x00000010&(data))>>4)
#define NF_SWC_MULTI_CHNL_MODE_wait_ready_shift                                      (2)
#define NF_SWC_MULTI_CHNL_MODE_wait_ready_mask                                       (0x0000000C)
#define NF_SWC_MULTI_CHNL_MODE_wait_ready(data)                                      (0x0000000C&((data)<<2))
#define NF_SWC_MULTI_CHNL_MODE_wait_ready_src(data)                                  ((0x0000000C&(data))>>2)
#define NF_SWC_MULTI_CHNL_MODE_get_wait_ready(data)                                  ((0x0000000C&(data))>>2)


#define NF_SWC_SRAM_CTL                                                              0x1802F300
#define NF_SWC_SRAM_CTL_reg_addr                                                     "0xB802F300"
#define NF_SWC_SRAM_CTL_reg                                                          0xB802F300
#define set_NF_SWC_SRAM_CTL_reg(data)   (*((volatile unsigned int*) NF_SWC_SRAM_CTL_reg)=data)
#define get_NF_SWC_SRAM_CTL_reg   (*((volatile unsigned int*) NF_SWC_SRAM_CTL_reg))
#define NF_SWC_SRAM_CTL_inst_adr                                                     "0x00C0"
#define NF_SWC_SRAM_CTL_inst                                                         0x00C0
#define NF_SWC_SRAM_CTL_map_sel_shift                                                (5)
#define NF_SWC_SRAM_CTL_map_sel_mask                                                 (0x00000020)
#define NF_SWC_SRAM_CTL_map_sel(data)                                                (0x00000020&((data)<<5))
#define NF_SWC_SRAM_CTL_map_sel_src(data)                                            ((0x00000020&(data))>>5)
#define NF_SWC_SRAM_CTL_get_map_sel(data)                                            ((0x00000020&(data))>>5)
#define NF_SWC_SRAM_CTL_access_en_shift                                              (4)
#define NF_SWC_SRAM_CTL_access_en_mask                                               (0x00000010)
#define NF_SWC_SRAM_CTL_access_en(data)                                              (0x00000010&((data)<<4))
#define NF_SWC_SRAM_CTL_access_en_src(data)                                          ((0x00000010&(data))>>4)
#define NF_SWC_SRAM_CTL_get_access_en(data)                                          ((0x00000010&(data))>>4)
#define NF_SWC_SRAM_CTL_mem_region_shift                                             (0)
#define NF_SWC_SRAM_CTL_mem_region_mask                                              (0x0000000F)
#define NF_SWC_SRAM_CTL_mem_region(data)                                             (0x0000000F&((data)<<0))
#define NF_SWC_SRAM_CTL_mem_region_src(data)                                         ((0x0000000F&(data))>>0)
#define NF_SWC_SRAM_CTL_get_mem_region(data)                                         ((0x0000000F&(data))>>0)


#define NF_SWC_DMA_CTL1                                                              0x1802F304
#define NF_SWC_DMA_CTL1_reg_addr                                                     "0xB802F304"
#define NF_SWC_DMA_CTL1_reg                                                          0xB802F304
#define set_NF_SWC_DMA_CTL1_reg(data)   (*((volatile unsigned int*) NF_SWC_DMA_CTL1_reg)=data)
#define get_NF_SWC_DMA_CTL1_reg   (*((volatile unsigned int*) NF_SWC_DMA_CTL1_reg))
#define NF_SWC_DMA_CTL1_inst_adr                                                     "0x00C1"
#define NF_SWC_DMA_CTL1_inst                                                         0x00C1
#define NF_SWC_DMA_CTL1_dram_sa_shift                                                (0)
#define NF_SWC_DMA_CTL1_dram_sa_mask                                                 (0x0FFFFFFF)
#define NF_SWC_DMA_CTL1_dram_sa(data)                                                (0x0FFFFFFF&((data)<<0))
#define NF_SWC_DMA_CTL1_dram_sa_src(data)                                            ((0x0FFFFFFF&(data))>>0)
#define NF_SWC_DMA_CTL1_get_dram_sa(data)                                            ((0x0FFFFFFF&(data))>>0)


#define NF_SWC_DMA_CTL2                                                              0x1802F308
#define NF_SWC_DMA_CTL2_reg_addr                                                     "0xB802F308"
#define NF_SWC_DMA_CTL2_reg                                                          0xB802F308
#define set_NF_SWC_DMA_CTL2_reg(data)   (*((volatile unsigned int*) NF_SWC_DMA_CTL2_reg)=data)
#define get_NF_SWC_DMA_CTL2_reg   (*((volatile unsigned int*) NF_SWC_DMA_CTL2_reg))
#define NF_SWC_DMA_CTL2_inst_adr                                                     "0x00C2"
#define NF_SWC_DMA_CTL2_inst                                                         0x00C2
#define NF_SWC_DMA_CTL2_dma_len_shift                                                (0)
#define NF_SWC_DMA_CTL2_dma_len_mask                                                 (0x0000FFFF)
#define NF_SWC_DMA_CTL2_dma_len(data)                                                (0x0000FFFF&((data)<<0))
#define NF_SWC_DMA_CTL2_dma_len_src(data)                                            ((0x0000FFFF&(data))>>0)
#define NF_SWC_DMA_CTL2_get_dma_len(data)                                            ((0x0000FFFF&(data))>>0)


#define NF_SWC_DMA_CTL3                                                              0x1802F30C
#define NF_SWC_DMA_CTL3_reg_addr                                                     "0xB802F30C"
#define NF_SWC_DMA_CTL3_reg                                                          0xB802F30C
#define set_NF_SWC_DMA_CTL3_reg(data)   (*((volatile unsigned int*) NF_SWC_DMA_CTL3_reg)=data)
#define get_NF_SWC_DMA_CTL3_reg   (*((volatile unsigned int*) NF_SWC_DMA_CTL3_reg))
#define NF_SWC_DMA_CTL3_inst_adr                                                     "0x00C3"
#define NF_SWC_DMA_CTL3_inst                                                         0x00C3
#define NF_SWC_DMA_CTL3_cp_first_shift                                               (3)
#define NF_SWC_DMA_CTL3_cp_first_mask                                                (0x00000008)
#define NF_SWC_DMA_CTL3_cp_first(data)                                               (0x00000008&((data)<<3))
#define NF_SWC_DMA_CTL3_cp_first_src(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_DMA_CTL3_get_cp_first(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_DMA_CTL3_cp_enable_shift                                              (2)
#define NF_SWC_DMA_CTL3_cp_enable_mask                                               (0x00000004)
#define NF_SWC_DMA_CTL3_cp_enable(data)                                              (0x00000004&((data)<<2))
#define NF_SWC_DMA_CTL3_cp_enable_src(data)                                          ((0x00000004&(data))>>2)
#define NF_SWC_DMA_CTL3_get_cp_enable(data)                                          ((0x00000004&(data))>>2)
#define NF_SWC_DMA_CTL3_ddr_wr_shift                                                 (1)
#define NF_SWC_DMA_CTL3_ddr_wr_mask                                                  (0x00000002)
#define NF_SWC_DMA_CTL3_ddr_wr(data)                                                 (0x00000002&((data)<<1))
#define NF_SWC_DMA_CTL3_ddr_wr_src(data)                                             ((0x00000002&(data))>>1)
#define NF_SWC_DMA_CTL3_get_ddr_wr(data)                                             ((0x00000002&(data))>>1)
#define NF_SWC_DMA_CTL3_dma_xfer_shift                                               (0)
#define NF_SWC_DMA_CTL3_dma_xfer_mask                                                (0x00000001)
#define NF_SWC_DMA_CTL3_dma_xfer(data)                                               (0x00000001&((data)<<0))
#define NF_SWC_DMA_CTL3_dma_xfer_src(data)                                           ((0x00000001&(data))>>0)
#define NF_SWC_DMA_CTL3_get_dma_xfer(data)                                           ((0x00000001&(data))>>0)


#define NF_SWC_SYS_LOW_PWR                                                           0x1802F310
#define NF_SWC_SYS_LOW_PWR_reg_addr                                                  "0xB802F310"
#define NF_SWC_SYS_LOW_PWR_reg                                                       0xB802F310
#define set_NF_SWC_SYS_LOW_PWR_reg(data)   (*((volatile unsigned int*) NF_SWC_SYS_LOW_PWR_reg)=data)
#define get_NF_SWC_SYS_LOW_PWR_reg   (*((volatile unsigned int*) NF_SWC_SYS_LOW_PWR_reg))
#define NF_SWC_SYS_LOW_PWR_inst_adr                                                  "0x00C4"
#define NF_SWC_SYS_LOW_PWR_inst                                                      0x00C4
#define NF_SWC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_shift                                  (7)
#define NF_SWC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_mask                                   (0x00000080)
#define NF_SWC_SYS_LOW_PWR_mcu_pp_sram_lp_ena(data)                                  (0x00000080&((data)<<7))
#define NF_SWC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_src(data)                              ((0x00000080&(data))>>7)
#define NF_SWC_SYS_LOW_PWR_get_mcu_pp_sram_lp_ena(data)                              ((0x00000080&(data))>>7)
#define NF_SWC_SYS_LOW_PWR_sys_clk_gate_ena_shift                                    (6)
#define NF_SWC_SYS_LOW_PWR_sys_clk_gate_ena_mask                                     (0x00000040)
#define NF_SWC_SYS_LOW_PWR_sys_clk_gate_ena(data)                                    (0x00000040&((data)<<6))
#define NF_SWC_SYS_LOW_PWR_sys_clk_gate_ena_src(data)                                ((0x00000040&(data))>>6)
#define NF_SWC_SYS_LOW_PWR_get_sys_clk_gate_ena(data)                                ((0x00000040&(data))>>6)
#define NF_SWC_SYS_LOW_PWR_cp_clk_gate_ena_shift                                     (5)
#define NF_SWC_SYS_LOW_PWR_cp_clk_gate_ena_mask                                      (0x00000020)
#define NF_SWC_SYS_LOW_PWR_cp_clk_gate_ena(data)                                     (0x00000020&((data)<<5))
#define NF_SWC_SYS_LOW_PWR_cp_clk_gate_ena_src(data)                                 ((0x00000020&(data))>>5)
#define NF_SWC_SYS_LOW_PWR_get_cp_clk_gate_ena(data)                                 ((0x00000020&(data))>>5)
#define NF_SWC_SYS_LOW_PWR_dma_sram_lp_ena_shift                                     (4)
#define NF_SWC_SYS_LOW_PWR_dma_sram_lp_ena_mask                                      (0x00000010)
#define NF_SWC_SYS_LOW_PWR_dma_sram_lp_ena(data)                                     (0x00000010&((data)<<4))
#define NF_SWC_SYS_LOW_PWR_dma_sram_lp_ena_src(data)                                 ((0x00000010&(data))>>4)
#define NF_SWC_SYS_LOW_PWR_get_dma_sram_lp_ena(data)                                 ((0x00000010&(data))>>4)
#define NF_SWC_SYS_LOW_PWR_dma_sram_rdy_num_shift                                    (0)
#define NF_SWC_SYS_LOW_PWR_dma_sram_rdy_num_mask                                     (0x0000000F)
#define NF_SWC_SYS_LOW_PWR_dma_sram_rdy_num(data)                                    (0x0000000F&((data)<<0))
#define NF_SWC_SYS_LOW_PWR_dma_sram_rdy_num_src(data)                                ((0x0000000F&(data))>>0)
#define NF_SWC_SYS_LOW_PWR_get_dma_sram_rdy_num(data)                                ((0x0000000F&(data))>>0)


#define NF_SWC_NAND_ISR                                                              0x1802F324
#define NF_SWC_NAND_ISR_reg_addr                                                     "0xB802F324"
#define NF_SWC_NAND_ISR_reg                                                          0xB802F324
#define set_NF_SWC_NAND_ISR_reg(data)   (*((volatile unsigned int*) NF_SWC_NAND_ISR_reg)=data)
#define get_NF_SWC_NAND_ISR_reg   (*((volatile unsigned int*) NF_SWC_NAND_ISR_reg))
#define NF_SWC_NAND_ISR_inst_adr                                                     "0x00C9"
#define NF_SWC_NAND_ISR_inst                                                         0x00C9
#define NF_SWC_NAND_ISR_Int8_shift                                                   (8)
#define NF_SWC_NAND_ISR_Int8_mask                                                    (0x00000100)
#define NF_SWC_NAND_ISR_Int8(data)                                                   (0x00000100&((data)<<8))
#define NF_SWC_NAND_ISR_Int8_src(data)                                               ((0x00000100&(data))>>8)
#define NF_SWC_NAND_ISR_get_Int8(data)                                               ((0x00000100&(data))>>8)
#define NF_SWC_NAND_ISR_Int7_shift                                                   (7)
#define NF_SWC_NAND_ISR_Int7_mask                                                    (0x00000080)
#define NF_SWC_NAND_ISR_Int7(data)                                                   (0x00000080&((data)<<7))
#define NF_SWC_NAND_ISR_Int7_src(data)                                               ((0x00000080&(data))>>7)
#define NF_SWC_NAND_ISR_get_Int7(data)                                               ((0x00000080&(data))>>7)
#define NF_SWC_NAND_ISR_Int4_shift                                                   (4)
#define NF_SWC_NAND_ISR_Int4_mask                                                    (0x00000010)
#define NF_SWC_NAND_ISR_Int4(data)                                                   (0x00000010&((data)<<4))
#define NF_SWC_NAND_ISR_Int4_src(data)                                               ((0x00000010&(data))>>4)
#define NF_SWC_NAND_ISR_get_Int4(data)                                               ((0x00000010&(data))>>4)
#define NF_SWC_NAND_ISR_Int3_shift                                                   (3)
#define NF_SWC_NAND_ISR_Int3_mask                                                    (0x00000008)
#define NF_SWC_NAND_ISR_Int3(data)                                                   (0x00000008&((data)<<3))
#define NF_SWC_NAND_ISR_Int3_src(data)                                               ((0x00000008&(data))>>3)
#define NF_SWC_NAND_ISR_get_Int3(data)                                               ((0x00000008&(data))>>3)
#define NF_SWC_NAND_ISR_Int2_shift                                                   (2)
#define NF_SWC_NAND_ISR_Int2_mask                                                    (0x00000004)
#define NF_SWC_NAND_ISR_Int2(data)                                                   (0x00000004&((data)<<2))
#define NF_SWC_NAND_ISR_Int2_src(data)                                               ((0x00000004&(data))>>2)
#define NF_SWC_NAND_ISR_get_Int2(data)                                               ((0x00000004&(data))>>2)
#define NF_SWC_NAND_ISR_Int1_shift                                                   (1)
#define NF_SWC_NAND_ISR_Int1_mask                                                    (0x00000002)
#define NF_SWC_NAND_ISR_Int1(data)                                                   (0x00000002&((data)<<1))
#define NF_SWC_NAND_ISR_Int1_src(data)                                               ((0x00000002&(data))>>1)
#define NF_SWC_NAND_ISR_get_Int1(data)                                               ((0x00000002&(data))>>1)
#define NF_SWC_NAND_ISR_write_data_shift                                             (0)
#define NF_SWC_NAND_ISR_write_data_mask                                              (0x00000001)
#define NF_SWC_NAND_ISR_write_data(data)                                             (0x00000001&((data)<<0))
#define NF_SWC_NAND_ISR_write_data_src(data)                                         ((0x00000001&(data))>>0)
#define NF_SWC_NAND_ISR_get_write_data(data)                                         ((0x00000001&(data))>>0)


#define NF_SWC_NAND_ISREN                                                            0x1802F328
#define NF_SWC_NAND_ISREN_reg_addr                                                   "0xB802F328"
#define NF_SWC_NAND_ISREN_reg                                                        0xB802F328
#define set_NF_SWC_NAND_ISREN_reg(data)   (*((volatile unsigned int*) NF_SWC_NAND_ISREN_reg)=data)
#define get_NF_SWC_NAND_ISREN_reg   (*((volatile unsigned int*) NF_SWC_NAND_ISREN_reg))
#define NF_SWC_NAND_ISREN_inst_adr                                                   "0x00CA"
#define NF_SWC_NAND_ISREN_inst                                                       0x00CA
#define NF_SWC_NAND_ISREN_Int8En_shift                                               (8)
#define NF_SWC_NAND_ISREN_Int8En_mask                                                (0x00000100)
#define NF_SWC_NAND_ISREN_Int8En(data)                                               (0x00000100&((data)<<8))
#define NF_SWC_NAND_ISREN_Int8En_src(data)                                           ((0x00000100&(data))>>8)
#define NF_SWC_NAND_ISREN_get_Int8En(data)                                           ((0x00000100&(data))>>8)
#define NF_SWC_NAND_ISREN_Int7En_shift                                               (7)
#define NF_SWC_NAND_ISREN_Int7En_mask                                                (0x00000080)
#define NF_SWC_NAND_ISREN_Int7En(data)                                               (0x00000080&((data)<<7))
#define NF_SWC_NAND_ISREN_Int7En_src(data)                                           ((0x00000080&(data))>>7)
#define NF_SWC_NAND_ISREN_get_Int7En(data)                                           ((0x00000080&(data))>>7)
#define NF_SWC_NAND_ISREN_Int4En_shift                                               (4)
#define NF_SWC_NAND_ISREN_Int4En_mask                                                (0x00000010)
#define NF_SWC_NAND_ISREN_Int4En(data)                                               (0x00000010&((data)<<4))
#define NF_SWC_NAND_ISREN_Int4En_src(data)                                           ((0x00000010&(data))>>4)
#define NF_SWC_NAND_ISREN_get_Int4En(data)                                           ((0x00000010&(data))>>4)
#define NF_SWC_NAND_ISREN_Int3En_shift                                               (3)
#define NF_SWC_NAND_ISREN_Int3En_mask                                                (0x00000008)
#define NF_SWC_NAND_ISREN_Int3En(data)                                               (0x00000008&((data)<<3))
#define NF_SWC_NAND_ISREN_Int3En_src(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_NAND_ISREN_get_Int3En(data)                                           ((0x00000008&(data))>>3)
#define NF_SWC_NAND_ISREN_Int2En_shift                                               (2)
#define NF_SWC_NAND_ISREN_Int2En_mask                                                (0x00000004)
#define NF_SWC_NAND_ISREN_Int2En(data)                                               (0x00000004&((data)<<2))
#define NF_SWC_NAND_ISREN_Int2En_src(data)                                           ((0x00000004&(data))>>2)
#define NF_SWC_NAND_ISREN_get_Int2En(data)                                           ((0x00000004&(data))>>2)
#define NF_SWC_NAND_ISREN_Int1En_shift                                               (1)
#define NF_SWC_NAND_ISREN_Int1En_mask                                                (0x00000002)
#define NF_SWC_NAND_ISREN_Int1En(data)                                               (0x00000002&((data)<<1))
#define NF_SWC_NAND_ISREN_Int1En_src(data)                                           ((0x00000002&(data))>>1)
#define NF_SWC_NAND_ISREN_get_Int1En(data)                                           ((0x00000002&(data))>>1)
#define NF_SWC_NAND_ISREN_write_data_shift                                           (0)
#define NF_SWC_NAND_ISREN_write_data_mask                                            (0x00000001)
#define NF_SWC_NAND_ISREN_write_data(data)                                           (0x00000001&((data)<<0))
#define NF_SWC_NAND_ISREN_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define NF_SWC_NAND_ISREN_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define NF_SWC_DUMMY_SYS                                                             0x1802F32C
#define NF_SWC_DUMMY_SYS_reg_addr                                                    "0xB802F32C"
#define NF_SWC_DUMMY_SYS_reg                                                         0xB802F32C
#define set_NF_SWC_DUMMY_SYS_reg(data)   (*((volatile unsigned int*) NF_SWC_DUMMY_SYS_reg)=data)
#define get_NF_SWC_DUMMY_SYS_reg   (*((volatile unsigned int*) NF_SWC_DUMMY_SYS_reg))
#define NF_SWC_DUMMY_SYS_inst_adr                                                    "0x00CB"
#define NF_SWC_DUMMY_SYS_inst                                                        0x00CB
#define NF_SWC_DUMMY_SYS_dmy_shift                                                   (0)
#define NF_SWC_DUMMY_SYS_dmy_mask                                                    (0xFFFFFFFF)
#define NF_SWC_DUMMY_SYS_dmy(data)                                                   (0xFFFFFFFF&((data)<<0))
#define NF_SWC_DUMMY_SYS_dmy_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define NF_SWC_DUMMY_SYS_get_dmy(data)                                               ((0xFFFFFFFF&(data))>>0)


#define NF_SWC_DBG                                                                   0x1802F344
#define NF_SWC_DBG_reg_addr                                                          "0xB802F344"
#define NF_SWC_DBG_reg                                                               0xB802F344
#define set_NF_SWC_DBG_reg(data)   (*((volatile unsigned int*) NF_SWC_DBG_reg)=data)
#define get_NF_SWC_DBG_reg   (*((volatile unsigned int*) NF_SWC_DBG_reg))
#define NF_SWC_DBG_inst_adr                                                          "0x00D1"
#define NF_SWC_DBG_inst                                                              0x00D1
#define NF_SWC_DBG_write_enable3_shift                                               (9)
#define NF_SWC_DBG_write_enable3_mask                                                (0x00000200)
#define NF_SWC_DBG_write_enable3(data)                                               (0x00000200&((data)<<9))
#define NF_SWC_DBG_write_enable3_src(data)                                           ((0x00000200&(data))>>9)
#define NF_SWC_DBG_get_write_enable3(data)                                           ((0x00000200&(data))>>9)
#define NF_SWC_DBG_sel1_shift                                                        (6)
#define NF_SWC_DBG_sel1_mask                                                         (0x000001C0)
#define NF_SWC_DBG_sel1(data)                                                        (0x000001C0&((data)<<6))
#define NF_SWC_DBG_sel1_src(data)                                                    ((0x000001C0&(data))>>6)
#define NF_SWC_DBG_get_sel1(data)                                                    ((0x000001C0&(data))>>6)
#define NF_SWC_DBG_write_enable2_shift                                               (5)
#define NF_SWC_DBG_write_enable2_mask                                                (0x00000020)
#define NF_SWC_DBG_write_enable2(data)                                               (0x00000020&((data)<<5))
#define NF_SWC_DBG_write_enable2_src(data)                                           ((0x00000020&(data))>>5)
#define NF_SWC_DBG_get_write_enable2(data)                                           ((0x00000020&(data))>>5)
#define NF_SWC_DBG_sel0_shift                                                        (2)
#define NF_SWC_DBG_sel0_mask                                                         (0x0000001C)
#define NF_SWC_DBG_sel0(data)                                                        (0x0000001C&((data)<<2))
#define NF_SWC_DBG_sel0_src(data)                                                    ((0x0000001C&(data))>>2)
#define NF_SWC_DBG_get_sel0(data)                                                    ((0x0000001C&(data))>>2)
#define NF_SWC_DBG_write_enable1_shift                                               (1)
#define NF_SWC_DBG_write_enable1_mask                                                (0x00000002)
#define NF_SWC_DBG_write_enable1(data)                                               (0x00000002&((data)<<1))
#define NF_SWC_DBG_write_enable1_src(data)                                           ((0x00000002&(data))>>1)
#define NF_SWC_DBG_get_write_enable1(data)                                           ((0x00000002&(data))>>1)
#define NF_SWC_DBG_enable_shift                                                      (0)
#define NF_SWC_DBG_enable_mask                                                       (0x00000001)
#define NF_SWC_DBG_enable(data)                                                      (0x00000001&((data)<<0))
#define NF_SWC_DBG_enable_src(data)                                                  ((0x00000001&(data))>>0)
#define NF_SWC_DBG_get_enable(data)                                                  ((0x00000001&(data))>>0)


#define NF_SWC_SPR_DDR_CTL                                                           0x1802F348
#define NF_SWC_SPR_DDR_CTL_reg_addr                                                  "0xB802F348"
#define NF_SWC_SPR_DDR_CTL_reg                                                       0xB802F348
#define set_NF_SWC_SPR_DDR_CTL_reg(data)   (*((volatile unsigned int*) NF_SWC_SPR_DDR_CTL_reg)=data)
#define get_NF_SWC_SPR_DDR_CTL_reg   (*((volatile unsigned int*) NF_SWC_SPR_DDR_CTL_reg))
#define NF_SWC_SPR_DDR_CTL_inst_adr                                                  "0x00D2"
#define NF_SWC_SPR_DDR_CTL_inst                                                      0x00D2
#define NF_SWC_SPR_DDR_CTL_cr_nf_hw_pinmux_ena_shift                                 (30)
#define NF_SWC_SPR_DDR_CTL_cr_nf_hw_pinmux_ena_mask                                  (0x40000000)
#define NF_SWC_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(data)                                 (0x40000000&((data)<<30))
#define NF_SWC_SPR_DDR_CTL_cr_nf_hw_pinmux_ena_src(data)                             ((0x40000000&(data))>>30)
#define NF_SWC_SPR_DDR_CTL_get_cr_nf_hw_pinmux_ena(data)                             ((0x40000000&(data))>>30)
#define NF_SWC_SPR_DDR_CTL_spare_ddr_ena_shift                                       (29)
#define NF_SWC_SPR_DDR_CTL_spare_ddr_ena_mask                                        (0x20000000)
#define NF_SWC_SPR_DDR_CTL_spare_ddr_ena(data)                                       (0x20000000&((data)<<29))
#define NF_SWC_SPR_DDR_CTL_spare_ddr_ena_src(data)                                   ((0x20000000&(data))>>29)
#define NF_SWC_SPR_DDR_CTL_get_spare_ddr_ena(data)                                   ((0x20000000&(data))>>29)
#define NF_SWC_SPR_DDR_CTL_per_2k_spr_ena_shift                                      (28)
#define NF_SWC_SPR_DDR_CTL_per_2k_spr_ena_mask                                       (0x10000000)
#define NF_SWC_SPR_DDR_CTL_per_2k_spr_ena(data)                                      (0x10000000&((data)<<28))
#define NF_SWC_SPR_DDR_CTL_per_2k_spr_ena_src(data)                                  ((0x10000000&(data))>>28)
#define NF_SWC_SPR_DDR_CTL_get_per_2k_spr_ena(data)                                  ((0x10000000&(data))>>28)
#define NF_SWC_SPR_DDR_CTL_spare_dram_sa_shift                                       (0)
#define NF_SWC_SPR_DDR_CTL_spare_dram_sa_mask                                        (0x0FFFFFFF)
#define NF_SWC_SPR_DDR_CTL_spare_dram_sa(data)                                       (0x0FFFFFFF&((data)<<0))
#define NF_SWC_SPR_DDR_CTL_spare_dram_sa_src(data)                                   ((0x0FFFFFFF&(data))>>0)
#define NF_SWC_SPR_DDR_CTL_get_spare_dram_sa(data)                                   ((0x0FFFFFFF&(data))>>0)


#define NF_SWC_CP_LEN                                                                0x1802F34C
#define NF_SWC_CP_LEN_reg_addr                                                       "0xB802F34C"
#define NF_SWC_CP_LEN_reg                                                            0xB802F34C
#define set_NF_SWC_CP_LEN_reg(data)   (*((volatile unsigned int*) NF_SWC_CP_LEN_reg)=data)
#define get_NF_SWC_CP_LEN_reg   (*((volatile unsigned int*) NF_SWC_CP_LEN_reg))
#define NF_SWC_CP_LEN_inst_adr                                                       "0x00D3"
#define NF_SWC_CP_LEN_inst                                                           0x00D3
#define NF_SWC_CP_LEN_cp_length_shift                                                (9)
#define NF_SWC_CP_LEN_cp_length_mask                                                 (0x01FFFE00)
#define NF_SWC_CP_LEN_cp_length(data)                                                (0x01FFFE00&((data)<<9))
#define NF_SWC_CP_LEN_cp_length_src(data)                                            ((0x01FFFE00&(data))>>9)
#define NF_SWC_CP_LEN_get_cp_length(data)                                            ((0x01FFFE00&(data))>>9)


#endif
