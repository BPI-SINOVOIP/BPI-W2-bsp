/**************************************************************
// Spec Version                  : 0.7
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/17 20:54:5
***************************************************************/


#ifndef _EMMC_REG_H_INCLUDED_
#define _EMMC_REG_H_INCLUDED_
#ifdef  _EMMC_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     map_sel:1;
unsigned int     access_en:1;
unsigned int     mem_region:4;
}EMMC_SRAM_CTL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dram_sa:28;
}EMMC_DMA_CTL1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dma_len:16;
}EMMC_DMA_CTL2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     dat64_sel:1;
unsigned int     rsp17_sel:1;
unsigned int     reserved_1:2;
unsigned int     ddr_wr:1;
unsigned int     dma_xfer:1;
}EMMC_DMA_CTL3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mcu_pp_sram_lp_ena:1;
unsigned int     sys_clk_gate_ena:1;
unsigned int     cp_clk_gate_ena:1;
unsigned int     dma_sram_lp_ena:1;
unsigned int     dma_sram_rdy_num:4;
}EMMC_SYS_LOW_PWR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Int4:1;
unsigned int     reserved_1:1;
unsigned int     Int2:1;
unsigned int     Int1:1;
unsigned int     write_data:1;
}EMMC_SD_ISR;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     reserved_1:4;
unsigned int     Int4En:1;
unsigned int     reserved_2:1;
unsigned int     Int2En:1;
unsigned int     Int1En:1;
unsigned int     write_data:1;
}EMMC_SD_ISREN;

typedef struct 
{
unsigned int     dmy:32;
}EMMC_DUMMY_SYS;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_enable3:1;
unsigned int     sel1:3;
unsigned int     write_enable2:1;
unsigned int     sel0:3;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}EMMC_DBG;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     bist_cr_ppb_rme_1:1;
unsigned int     bist_cr_ppb_rm_1:4;
unsigned int     bist_cr_ppb_rme_0:1;
unsigned int     bist_cr_ppb_rm_0:4;
unsigned int     bist_clk_en:1;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
}EMMC_IP_BIST_CTL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     bist_drf_start_pause:1;
unsigned int     bist_drf_fail_1:1;
unsigned int     bist_drf_fail_0:1;
unsigned int     bist_drf_done:1;
unsigned int     bist_1_fail:1;
unsigned int     bist_0_fail:1;
unsigned int     bist_done:1;
}EMMC_IP_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     asic_crc_dbgo_sel:8;
unsigned int     reserved_1:1;
unsigned int     crc_dbgo_sel:4;
unsigned int     ip_ea_flash:1;
unsigned int     crc_clk_disable_trig:1;
unsigned int     mcu_time_1_us:1;
}EMMC_IP_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     tune3318:1;
}EMMC_PAD_CTL;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     sd30_sample_change:1;
unsigned int     sd30_push_change:1;
unsigned int     crc_clk_change:1;
unsigned int     reserved_1:2;
unsigned int     sd30_sample_clk_src:2;
unsigned int     reserved_2:2;
unsigned int     sd30_push_clk_src:2;
unsigned int     reserved_3:2;
unsigned int     crc_clk_src:2;
unsigned int     reserved_4:1;
unsigned int     clk_div:3;
}EMMC_CKGEN_CTL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     buf_full:1;
unsigned int     buf_sw:1;
unsigned int     cpu_mode:1;
}EMMC_CPU_ACC_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     EMMC_RST_n:1;
}EMMC_CARD_SIG;

#endif

#define EMMC_SRAM_CTL                                                                0x18012000
#define EMMC_SRAM_CTL_reg_addr                                                       "0xB8012000"
#define EMMC_SRAM_CTL_reg                                                            0xB8012000
#define set_EMMC_SRAM_CTL_reg(data)   (*((volatile unsigned int*) EMMC_SRAM_CTL_reg)=data)
#define get_EMMC_SRAM_CTL_reg   (*((volatile unsigned int*) EMMC_SRAM_CTL_reg))
#define EMMC_SRAM_CTL_inst_adr                                                       "0x0000"
#define EMMC_SRAM_CTL_inst                                                           0x0000
#define EMMC_SRAM_CTL_map_sel_shift                                                  (5)
#define EMMC_SRAM_CTL_map_sel_mask                                                   (0x00000020)
#define EMMC_SRAM_CTL_map_sel(data)                                                  (0x00000020&((data)<<5))
#define EMMC_SRAM_CTL_map_sel_src(data)                                              ((0x00000020&(data))>>5)
#define EMMC_SRAM_CTL_get_map_sel(data)                                              ((0x00000020&(data))>>5)
#define EMMC_SRAM_CTL_access_en_shift                                                (4)
#define EMMC_SRAM_CTL_access_en_mask                                                 (0x00000010)
#define EMMC_SRAM_CTL_access_en(data)                                                (0x00000010&((data)<<4))
#define EMMC_SRAM_CTL_access_en_src(data)                                            ((0x00000010&(data))>>4)
#define EMMC_SRAM_CTL_get_access_en(data)                                            ((0x00000010&(data))>>4)
#define EMMC_SRAM_CTL_mem_region_shift                                               (0)
#define EMMC_SRAM_CTL_mem_region_mask                                                (0x0000000F)
#define EMMC_SRAM_CTL_mem_region(data)                                               (0x0000000F&((data)<<0))
#define EMMC_SRAM_CTL_mem_region_src(data)                                           ((0x0000000F&(data))>>0)
#define EMMC_SRAM_CTL_get_mem_region(data)                                           ((0x0000000F&(data))>>0)


#define EMMC_DMA_CTL1                                                                0x18012004
#define EMMC_DMA_CTL1_reg_addr                                                       "0xB8012004"
#define EMMC_DMA_CTL1_reg                                                            0xB8012004
#define set_EMMC_DMA_CTL1_reg(data)   (*((volatile unsigned int*) EMMC_DMA_CTL1_reg)=data)
#define get_EMMC_DMA_CTL1_reg   (*((volatile unsigned int*) EMMC_DMA_CTL1_reg))
#define EMMC_DMA_CTL1_inst_adr                                                       "0x0001"
#define EMMC_DMA_CTL1_inst                                                           0x0001
#define EMMC_DMA_CTL1_dram_sa_shift                                                  (0)
#define EMMC_DMA_CTL1_dram_sa_mask                                                   (0x0FFFFFFF)
#define EMMC_DMA_CTL1_dram_sa(data)                                                  (0x0FFFFFFF&((data)<<0))
#define EMMC_DMA_CTL1_dram_sa_src(data)                                              ((0x0FFFFFFF&(data))>>0)
#define EMMC_DMA_CTL1_get_dram_sa(data)                                              ((0x0FFFFFFF&(data))>>0)


#define EMMC_DMA_CTL2                                                                0x18012008
#define EMMC_DMA_CTL2_reg_addr                                                       "0xB8012008"
#define EMMC_DMA_CTL2_reg                                                            0xB8012008
#define set_EMMC_DMA_CTL2_reg(data)   (*((volatile unsigned int*) EMMC_DMA_CTL2_reg)=data)
#define get_EMMC_DMA_CTL2_reg   (*((volatile unsigned int*) EMMC_DMA_CTL2_reg))
#define EMMC_DMA_CTL2_inst_adr                                                       "0x0002"
#define EMMC_DMA_CTL2_inst                                                           0x0002
#define EMMC_DMA_CTL2_dma_len_shift                                                  (0)
#define EMMC_DMA_CTL2_dma_len_mask                                                   (0x0000FFFF)
#define EMMC_DMA_CTL2_dma_len(data)                                                  (0x0000FFFF&((data)<<0))
#define EMMC_DMA_CTL2_dma_len_src(data)                                              ((0x0000FFFF&(data))>>0)
#define EMMC_DMA_CTL2_get_dma_len(data)                                              ((0x0000FFFF&(data))>>0)


#define EMMC_DMA_CTL3                                                                0x1801200C
#define EMMC_DMA_CTL3_reg_addr                                                       "0xB801200C"
#define EMMC_DMA_CTL3_reg                                                            0xB801200C
#define set_EMMC_DMA_CTL3_reg(data)   (*((volatile unsigned int*) EMMC_DMA_CTL3_reg)=data)
#define get_EMMC_DMA_CTL3_reg   (*((volatile unsigned int*) EMMC_DMA_CTL3_reg))
#define EMMC_DMA_CTL3_inst_adr                                                       "0x0003"
#define EMMC_DMA_CTL3_inst                                                           0x0003
#define EMMC_DMA_CTL3_dat64_sel_shift                                                (5)
#define EMMC_DMA_CTL3_dat64_sel_mask                                                 (0x00000020)
#define EMMC_DMA_CTL3_dat64_sel(data)                                                (0x00000020&((data)<<5))
#define EMMC_DMA_CTL3_dat64_sel_src(data)                                            ((0x00000020&(data))>>5)
#define EMMC_DMA_CTL3_get_dat64_sel(data)                                            ((0x00000020&(data))>>5)
#define EMMC_DMA_CTL3_rsp17_sel_shift                                                (4)
#define EMMC_DMA_CTL3_rsp17_sel_mask                                                 (0x00000010)
#define EMMC_DMA_CTL3_rsp17_sel(data)                                                (0x00000010&((data)<<4))
#define EMMC_DMA_CTL3_rsp17_sel_src(data)                                            ((0x00000010&(data))>>4)
#define EMMC_DMA_CTL3_get_rsp17_sel(data)                                            ((0x00000010&(data))>>4)
#define EMMC_DMA_CTL3_ddr_wr_shift                                                   (1)
#define EMMC_DMA_CTL3_ddr_wr_mask                                                    (0x00000002)
#define EMMC_DMA_CTL3_ddr_wr(data)                                                   (0x00000002&((data)<<1))
#define EMMC_DMA_CTL3_ddr_wr_src(data)                                               ((0x00000002&(data))>>1)
#define EMMC_DMA_CTL3_get_ddr_wr(data)                                               ((0x00000002&(data))>>1)
#define EMMC_DMA_CTL3_dma_xfer_shift                                                 (0)
#define EMMC_DMA_CTL3_dma_xfer_mask                                                  (0x00000001)
#define EMMC_DMA_CTL3_dma_xfer(data)                                                 (0x00000001&((data)<<0))
#define EMMC_DMA_CTL3_dma_xfer_src(data)                                             ((0x00000001&(data))>>0)
#define EMMC_DMA_CTL3_get_dma_xfer(data)                                             ((0x00000001&(data))>>0)


#define EMMC_SYS_LOW_PWR                                                             0x18012010
#define EMMC_SYS_LOW_PWR_reg_addr                                                    "0xB8012010"
#define EMMC_SYS_LOW_PWR_reg                                                         0xB8012010
#define set_EMMC_SYS_LOW_PWR_reg(data)   (*((volatile unsigned int*) EMMC_SYS_LOW_PWR_reg)=data)
#define get_EMMC_SYS_LOW_PWR_reg   (*((volatile unsigned int*) EMMC_SYS_LOW_PWR_reg))
#define EMMC_SYS_LOW_PWR_inst_adr                                                    "0x0004"
#define EMMC_SYS_LOW_PWR_inst                                                        0x0004
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_shift                                    (7)
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_mask                                     (0x00000080)
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena(data)                                    (0x00000080&((data)<<7))
#define EMMC_SYS_LOW_PWR_mcu_pp_sram_lp_ena_src(data)                                ((0x00000080&(data))>>7)
#define EMMC_SYS_LOW_PWR_get_mcu_pp_sram_lp_ena(data)                                ((0x00000080&(data))>>7)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_shift                                      (6)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_mask                                       (0x00000040)
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena(data)                                      (0x00000040&((data)<<6))
#define EMMC_SYS_LOW_PWR_sys_clk_gate_ena_src(data)                                  ((0x00000040&(data))>>6)
#define EMMC_SYS_LOW_PWR_get_sys_clk_gate_ena(data)                                  ((0x00000040&(data))>>6)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_shift                                       (5)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_mask                                        (0x00000020)
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena(data)                                       (0x00000020&((data)<<5))
#define EMMC_SYS_LOW_PWR_cp_clk_gate_ena_src(data)                                   ((0x00000020&(data))>>5)
#define EMMC_SYS_LOW_PWR_get_cp_clk_gate_ena(data)                                   ((0x00000020&(data))>>5)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_shift                                       (4)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_mask                                        (0x00000010)
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena(data)                                       (0x00000010&((data)<<4))
#define EMMC_SYS_LOW_PWR_dma_sram_lp_ena_src(data)                                   ((0x00000010&(data))>>4)
#define EMMC_SYS_LOW_PWR_get_dma_sram_lp_ena(data)                                   ((0x00000010&(data))>>4)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_shift                                      (0)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_mask                                       (0x0000000F)
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num(data)                                      (0x0000000F&((data)<<0))
#define EMMC_SYS_LOW_PWR_dma_sram_rdy_num_src(data)                                  ((0x0000000F&(data))>>0)
#define EMMC_SYS_LOW_PWR_get_dma_sram_rdy_num(data)                                  ((0x0000000F&(data))>>0)


#define EMMC_SD_ISR                                                                  0x18012024
#define EMMC_SD_ISR_reg_addr                                                         "0xB8012024"
#define EMMC_SD_ISR_reg                                                              0xB8012024
#define set_EMMC_SD_ISR_reg(data)   (*((volatile unsigned int*) EMMC_SD_ISR_reg)=data)
#define get_EMMC_SD_ISR_reg   (*((volatile unsigned int*) EMMC_SD_ISR_reg))
#define EMMC_SD_ISR_inst_adr                                                         "0x0009"
#define EMMC_SD_ISR_inst                                                             0x0009
#define EMMC_SD_ISR_Int4_shift                                                       (4)
#define EMMC_SD_ISR_Int4_mask                                                        (0x00000010)
#define EMMC_SD_ISR_Int4(data)                                                       (0x00000010&((data)<<4))
#define EMMC_SD_ISR_Int4_src(data)                                                   ((0x00000010&(data))>>4)
#define EMMC_SD_ISR_get_Int4(data)                                                   ((0x00000010&(data))>>4)
#define EMMC_SD_ISR_Int2_shift                                                       (2)
#define EMMC_SD_ISR_Int2_mask                                                        (0x00000004)
#define EMMC_SD_ISR_Int2(data)                                                       (0x00000004&((data)<<2))
#define EMMC_SD_ISR_Int2_src(data)                                                   ((0x00000004&(data))>>2)
#define EMMC_SD_ISR_get_Int2(data)                                                   ((0x00000004&(data))>>2)
#define EMMC_SD_ISR_Int1_shift                                                       (1)
#define EMMC_SD_ISR_Int1_mask                                                        (0x00000002)
#define EMMC_SD_ISR_Int1(data)                                                       (0x00000002&((data)<<1))
#define EMMC_SD_ISR_Int1_src(data)                                                   ((0x00000002&(data))>>1)
#define EMMC_SD_ISR_get_Int1(data)                                                   ((0x00000002&(data))>>1)
#define EMMC_SD_ISR_write_data_shift                                                 (0)
#define EMMC_SD_ISR_write_data_mask                                                  (0x00000001)
#define EMMC_SD_ISR_write_data(data)                                                 (0x00000001&((data)<<0))
#define EMMC_SD_ISR_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define EMMC_SD_ISR_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define EMMC_SD_ISREN                                                                0x18012028
#define EMMC_SD_ISREN_reg_addr                                                       "0xB8012028"
#define EMMC_SD_ISREN_reg                                                            0xB8012028
#define set_EMMC_SD_ISREN_reg(data)   (*((volatile unsigned int*) EMMC_SD_ISREN_reg)=data)
#define get_EMMC_SD_ISREN_reg   (*((volatile unsigned int*) EMMC_SD_ISREN_reg))
#define EMMC_SD_ISREN_inst_adr                                                       "0x000A"
#define EMMC_SD_ISREN_inst                                                           0x000A
#define EMMC_SD_ISREN_Int4En_shift                                                   (4)
#define EMMC_SD_ISREN_Int4En_mask                                                    (0x00000010)
#define EMMC_SD_ISREN_Int4En(data)                                                   (0x00000010&((data)<<4))
#define EMMC_SD_ISREN_Int4En_src(data)                                               ((0x00000010&(data))>>4)
#define EMMC_SD_ISREN_get_Int4En(data)                                               ((0x00000010&(data))>>4)
#define EMMC_SD_ISREN_Int2En_shift                                                   (2)
#define EMMC_SD_ISREN_Int2En_mask                                                    (0x00000004)
#define EMMC_SD_ISREN_Int2En(data)                                                   (0x00000004&((data)<<2))
#define EMMC_SD_ISREN_Int2En_src(data)                                               ((0x00000004&(data))>>2)
#define EMMC_SD_ISREN_get_Int2En(data)                                               ((0x00000004&(data))>>2)
#define EMMC_SD_ISREN_Int1En_shift                                                   (1)
#define EMMC_SD_ISREN_Int1En_mask                                                    (0x00000002)
#define EMMC_SD_ISREN_Int1En(data)                                                   (0x00000002&((data)<<1))
#define EMMC_SD_ISREN_Int1En_src(data)                                               ((0x00000002&(data))>>1)
#define EMMC_SD_ISREN_get_Int1En(data)                                               ((0x00000002&(data))>>1)
#define EMMC_SD_ISREN_write_data_shift                                               (0)
#define EMMC_SD_ISREN_write_data_mask                                                (0x00000001)
#define EMMC_SD_ISREN_write_data(data)                                               (0x00000001&((data)<<0))
#define EMMC_SD_ISREN_write_data_src(data)                                           ((0x00000001&(data))>>0)
#define EMMC_SD_ISREN_get_write_data(data)                                           ((0x00000001&(data))>>0)


#define EMMC_DUMMY_SYS                                                               0x1801202C
#define EMMC_DUMMY_SYS_reg_addr                                                      "0xB801202C"
#define EMMC_DUMMY_SYS_reg                                                           0xB801202C
#define set_EMMC_DUMMY_SYS_reg(data)   (*((volatile unsigned int*) EMMC_DUMMY_SYS_reg)=data)
#define get_EMMC_DUMMY_SYS_reg   (*((volatile unsigned int*) EMMC_DUMMY_SYS_reg))
#define EMMC_DUMMY_SYS_inst_adr                                                      "0x000B"
#define EMMC_DUMMY_SYS_inst                                                          0x000B
#define EMMC_DUMMY_SYS_dmy_shift                                                     (0)
#define EMMC_DUMMY_SYS_dmy_mask                                                      (0xFFFFFFFF)
#define EMMC_DUMMY_SYS_dmy(data)                                                     (0xFFFFFFFF&((data)<<0))
#define EMMC_DUMMY_SYS_dmy_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define EMMC_DUMMY_SYS_get_dmy(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define EMMC_DBG                                                                     0x18012044
#define EMMC_DBG_reg_addr                                                            "0xB8012044"
#define EMMC_DBG_reg                                                                 0xB8012044
#define set_EMMC_DBG_reg(data)   (*((volatile unsigned int*) EMMC_DBG_reg)=data)
#define get_EMMC_DBG_reg   (*((volatile unsigned int*) EMMC_DBG_reg))
#define EMMC_DBG_inst_adr                                                            "0x0011"
#define EMMC_DBG_inst                                                                0x0011
#define EMMC_DBG_write_enable3_shift                                                 (9)
#define EMMC_DBG_write_enable3_mask                                                  (0x00000200)
#define EMMC_DBG_write_enable3(data)                                                 (0x00000200&((data)<<9))
#define EMMC_DBG_write_enable3_src(data)                                             ((0x00000200&(data))>>9)
#define EMMC_DBG_get_write_enable3(data)                                             ((0x00000200&(data))>>9)
#define EMMC_DBG_sel1_shift                                                          (6)
#define EMMC_DBG_sel1_mask                                                           (0x000001C0)
#define EMMC_DBG_sel1(data)                                                          (0x000001C0&((data)<<6))
#define EMMC_DBG_sel1_src(data)                                                      ((0x000001C0&(data))>>6)
#define EMMC_DBG_get_sel1(data)                                                      ((0x000001C0&(data))>>6)
#define EMMC_DBG_write_enable2_shift                                                 (5)
#define EMMC_DBG_write_enable2_mask                                                  (0x00000020)
#define EMMC_DBG_write_enable2(data)                                                 (0x00000020&((data)<<5))
#define EMMC_DBG_write_enable2_src(data)                                             ((0x00000020&(data))>>5)
#define EMMC_DBG_get_write_enable2(data)                                             ((0x00000020&(data))>>5)
#define EMMC_DBG_sel0_shift                                                          (2)
#define EMMC_DBG_sel0_mask                                                           (0x0000001C)
#define EMMC_DBG_sel0(data)                                                          (0x0000001C&((data)<<2))
#define EMMC_DBG_sel0_src(data)                                                      ((0x0000001C&(data))>>2)
#define EMMC_DBG_get_sel0(data)                                                      ((0x0000001C&(data))>>2)
#define EMMC_DBG_write_enable1_shift                                                 (1)
#define EMMC_DBG_write_enable1_mask                                                  (0x00000002)
#define EMMC_DBG_write_enable1(data)                                                 (0x00000002&((data)<<1))
#define EMMC_DBG_write_enable1_src(data)                                             ((0x00000002&(data))>>1)
#define EMMC_DBG_get_write_enable1(data)                                             ((0x00000002&(data))>>1)
#define EMMC_DBG_enable_shift                                                        (0)
#define EMMC_DBG_enable_mask                                                         (0x00000001)
#define EMMC_DBG_enable(data)                                                        (0x00000001&((data)<<0))
#define EMMC_DBG_enable_src(data)                                                    ((0x00000001&(data))>>0)
#define EMMC_DBG_get_enable(data)                                                    ((0x00000001&(data))>>0)


#define EMMC_IP_BIST_CTL                                                             0x18012060
#define EMMC_IP_BIST_CTL_reg_addr                                                    "0xB8012060"
#define EMMC_IP_BIST_CTL_reg                                                         0xB8012060
#define set_EMMC_IP_BIST_CTL_reg(data)   (*((volatile unsigned int*) EMMC_IP_BIST_CTL_reg)=data)
#define get_EMMC_IP_BIST_CTL_reg   (*((volatile unsigned int*) EMMC_IP_BIST_CTL_reg))
#define EMMC_IP_BIST_CTL_inst_adr                                                    "0x0018"
#define EMMC_IP_BIST_CTL_inst                                                        0x0018
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_1_shift                                     (13)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_1_mask                                      (0x00002000)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_1(data)                                     (0x00002000&((data)<<13))
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_1_src(data)                                 ((0x00002000&(data))>>13)
#define EMMC_IP_BIST_CTL_get_bist_cr_ppb_rme_1(data)                                 ((0x00002000&(data))>>13)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_1_shift                                      (9)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_1_mask                                       (0x00001E00)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_1(data)                                      (0x00001E00&((data)<<9))
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_1_src(data)                                  ((0x00001E00&(data))>>9)
#define EMMC_IP_BIST_CTL_get_bist_cr_ppb_rm_1(data)                                  ((0x00001E00&(data))>>9)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_0_shift                                     (8)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_0_mask                                      (0x00000100)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_0(data)                                     (0x00000100&((data)<<8))
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rme_0_src(data)                                 ((0x00000100&(data))>>8)
#define EMMC_IP_BIST_CTL_get_bist_cr_ppb_rme_0(data)                                 ((0x00000100&(data))>>8)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_0_shift                                      (4)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_0_mask                                       (0x000000F0)
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_0(data)                                      (0x000000F0&((data)<<4))
#define EMMC_IP_BIST_CTL_bist_cr_ppb_rm_0_src(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_IP_BIST_CTL_get_bist_cr_ppb_rm_0(data)                                  ((0x000000F0&(data))>>4)
#define EMMC_IP_BIST_CTL_bist_clk_en_shift                                           (3)
#define EMMC_IP_BIST_CTL_bist_clk_en_mask                                            (0x00000008)
#define EMMC_IP_BIST_CTL_bist_clk_en(data)                                           (0x00000008&((data)<<3))
#define EMMC_IP_BIST_CTL_bist_clk_en_src(data)                                       ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_CTL_get_bist_clk_en(data)                                       ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_shift                                  (2)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_mask                                   (0x00000004)
#define EMMC_IP_BIST_CTL_bist_drf_test_resume(data)                                  (0x00000004&((data)<<2))
#define EMMC_IP_BIST_CTL_bist_drf_test_resume_src(data)                              ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_CTL_get_bist_drf_test_resume(data)                              ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_CTL_bist_drf_mode_shift                                         (1)
#define EMMC_IP_BIST_CTL_bist_drf_mode_mask                                          (0x00000002)
#define EMMC_IP_BIST_CTL_bist_drf_mode(data)                                         (0x00000002&((data)<<1))
#define EMMC_IP_BIST_CTL_bist_drf_mode_src(data)                                     ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_CTL_get_bist_drf_mode(data)                                     ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_CTL_bist_en_shift                                               (0)
#define EMMC_IP_BIST_CTL_bist_en_mask                                                (0x00000001)
#define EMMC_IP_BIST_CTL_bist_en(data)                                               (0x00000001&((data)<<0))
#define EMMC_IP_BIST_CTL_bist_en_src(data)                                           ((0x00000001&(data))>>0)
#define EMMC_IP_BIST_CTL_get_bist_en(data)                                           ((0x00000001&(data))>>0)


#define EMMC_IP_BIST_STS                                                             0x18012064
#define EMMC_IP_BIST_STS_reg_addr                                                    "0xB8012064"
#define EMMC_IP_BIST_STS_reg                                                         0xB8012064
#define set_EMMC_IP_BIST_STS_reg(data)   (*((volatile unsigned int*) EMMC_IP_BIST_STS_reg)=data)
#define get_EMMC_IP_BIST_STS_reg   (*((volatile unsigned int*) EMMC_IP_BIST_STS_reg))
#define EMMC_IP_BIST_STS_inst_adr                                                    "0x0019"
#define EMMC_IP_BIST_STS_inst                                                        0x0019
#define EMMC_IP_BIST_STS_bist_drf_start_pause_shift                                  (6)
#define EMMC_IP_BIST_STS_bist_drf_start_pause_mask                                   (0x00000040)
#define EMMC_IP_BIST_STS_bist_drf_start_pause(data)                                  (0x00000040&((data)<<6))
#define EMMC_IP_BIST_STS_bist_drf_start_pause_src(data)                              ((0x00000040&(data))>>6)
#define EMMC_IP_BIST_STS_get_bist_drf_start_pause(data)                              ((0x00000040&(data))>>6)
#define EMMC_IP_BIST_STS_bist_drf_fail_1_shift                                       (5)
#define EMMC_IP_BIST_STS_bist_drf_fail_1_mask                                        (0x00000020)
#define EMMC_IP_BIST_STS_bist_drf_fail_1(data)                                       (0x00000020&((data)<<5))
#define EMMC_IP_BIST_STS_bist_drf_fail_1_src(data)                                   ((0x00000020&(data))>>5)
#define EMMC_IP_BIST_STS_get_bist_drf_fail_1(data)                                   ((0x00000020&(data))>>5)
#define EMMC_IP_BIST_STS_bist_drf_fail_0_shift                                       (4)
#define EMMC_IP_BIST_STS_bist_drf_fail_0_mask                                        (0x00000010)
#define EMMC_IP_BIST_STS_bist_drf_fail_0(data)                                       (0x00000010&((data)<<4))
#define EMMC_IP_BIST_STS_bist_drf_fail_0_src(data)                                   ((0x00000010&(data))>>4)
#define EMMC_IP_BIST_STS_get_bist_drf_fail_0(data)                                   ((0x00000010&(data))>>4)
#define EMMC_IP_BIST_STS_bist_drf_done_shift                                         (3)
#define EMMC_IP_BIST_STS_bist_drf_done_mask                                          (0x00000008)
#define EMMC_IP_BIST_STS_bist_drf_done(data)                                         (0x00000008&((data)<<3))
#define EMMC_IP_BIST_STS_bist_drf_done_src(data)                                     ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_STS_get_bist_drf_done(data)                                     ((0x00000008&(data))>>3)
#define EMMC_IP_BIST_STS_bist_1_fail_shift                                           (2)
#define EMMC_IP_BIST_STS_bist_1_fail_mask                                            (0x00000004)
#define EMMC_IP_BIST_STS_bist_1_fail(data)                                           (0x00000004&((data)<<2))
#define EMMC_IP_BIST_STS_bist_1_fail_src(data)                                       ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_STS_get_bist_1_fail(data)                                       ((0x00000004&(data))>>2)
#define EMMC_IP_BIST_STS_bist_0_fail_shift                                           (1)
#define EMMC_IP_BIST_STS_bist_0_fail_mask                                            (0x00000002)
#define EMMC_IP_BIST_STS_bist_0_fail(data)                                           (0x00000002&((data)<<1))
#define EMMC_IP_BIST_STS_bist_0_fail_src(data)                                       ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_STS_get_bist_0_fail(data)                                       ((0x00000002&(data))>>1)
#define EMMC_IP_BIST_STS_bist_done_shift                                             (0)
#define EMMC_IP_BIST_STS_bist_done_mask                                              (0x00000001)
#define EMMC_IP_BIST_STS_bist_done(data)                                             (0x00000001&((data)<<0))
#define EMMC_IP_BIST_STS_bist_done_src(data)                                         ((0x00000001&(data))>>0)
#define EMMC_IP_BIST_STS_get_bist_done(data)                                         ((0x00000001&(data))>>0)


#define EMMC_IP_CTL                                                                  0x18012070
#define EMMC_IP_CTL_reg_addr                                                         "0xB8012070"
#define EMMC_IP_CTL_reg                                                              0xB8012070
#define set_EMMC_IP_CTL_reg(data)   (*((volatile unsigned int*) EMMC_IP_CTL_reg)=data)
#define get_EMMC_IP_CTL_reg   (*((volatile unsigned int*) EMMC_IP_CTL_reg))
#define EMMC_IP_CTL_inst_adr                                                         "0x001C"
#define EMMC_IP_CTL_inst                                                             0x001C
#define EMMC_IP_CTL_asic_crc_dbgo_sel_shift                                          (8)
#define EMMC_IP_CTL_asic_crc_dbgo_sel_mask                                           (0x0000FF00)
#define EMMC_IP_CTL_asic_crc_dbgo_sel(data)                                          (0x0000FF00&((data)<<8))
#define EMMC_IP_CTL_asic_crc_dbgo_sel_src(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_IP_CTL_get_asic_crc_dbgo_sel(data)                                      ((0x0000FF00&(data))>>8)
#define EMMC_IP_CTL_crc_dbgo_sel_shift                                               (3)
#define EMMC_IP_CTL_crc_dbgo_sel_mask                                                (0x00000078)
#define EMMC_IP_CTL_crc_dbgo_sel(data)                                               (0x00000078&((data)<<3))
#define EMMC_IP_CTL_crc_dbgo_sel_src(data)                                           ((0x00000078&(data))>>3)
#define EMMC_IP_CTL_get_crc_dbgo_sel(data)                                           ((0x00000078&(data))>>3)
#define EMMC_IP_CTL_ip_ea_flash_shift                                                (2)
#define EMMC_IP_CTL_ip_ea_flash_mask                                                 (0x00000004)
#define EMMC_IP_CTL_ip_ea_flash(data)                                                (0x00000004&((data)<<2))
#define EMMC_IP_CTL_ip_ea_flash_src(data)                                            ((0x00000004&(data))>>2)
#define EMMC_IP_CTL_get_ip_ea_flash(data)                                            ((0x00000004&(data))>>2)
#define EMMC_IP_CTL_crc_clk_disable_trig_shift                                       (1)
#define EMMC_IP_CTL_crc_clk_disable_trig_mask                                        (0x00000002)
#define EMMC_IP_CTL_crc_clk_disable_trig(data)                                       (0x00000002&((data)<<1))
#define EMMC_IP_CTL_crc_clk_disable_trig_src(data)                                   ((0x00000002&(data))>>1)
#define EMMC_IP_CTL_get_crc_clk_disable_trig(data)                                   ((0x00000002&(data))>>1)
#define EMMC_IP_CTL_mcu_time_1_us_shift                                              (0)
#define EMMC_IP_CTL_mcu_time_1_us_mask                                               (0x00000001)
#define EMMC_IP_CTL_mcu_time_1_us(data)                                              (0x00000001&((data)<<0))
#define EMMC_IP_CTL_mcu_time_1_us_src(data)                                          ((0x00000001&(data))>>0)
#define EMMC_IP_CTL_get_mcu_time_1_us(data)                                          ((0x00000001&(data))>>0)


#define EMMC_PAD_CTL                                                                 0x18012074
#define EMMC_PAD_CTL_reg_addr                                                        "0xB8012074"
#define EMMC_PAD_CTL_reg                                                             0xB8012074
#define set_EMMC_PAD_CTL_reg(data)   (*((volatile unsigned int*) EMMC_PAD_CTL_reg)=data)
#define get_EMMC_PAD_CTL_reg   (*((volatile unsigned int*) EMMC_PAD_CTL_reg))
#define EMMC_PAD_CTL_inst_adr                                                        "0x001D"
#define EMMC_PAD_CTL_inst                                                            0x001D
#define EMMC_PAD_CTL_tune3318_shift                                                  (0)
#define EMMC_PAD_CTL_tune3318_mask                                                   (0x00000001)
#define EMMC_PAD_CTL_tune3318(data)                                                  (0x00000001&((data)<<0))
#define EMMC_PAD_CTL_tune3318_src(data)                                              ((0x00000001&(data))>>0)
#define EMMC_PAD_CTL_get_tune3318(data)                                              ((0x00000001&(data))>>0)


#define EMMC_CKGEN_CTL                                                               0x18012078
#define EMMC_CKGEN_CTL_reg_addr                                                      "0xB8012078"
#define EMMC_CKGEN_CTL_reg                                                           0xB8012078
#define set_EMMC_CKGEN_CTL_reg(data)   (*((volatile unsigned int*) EMMC_CKGEN_CTL_reg)=data)
#define get_EMMC_CKGEN_CTL_reg   (*((volatile unsigned int*) EMMC_CKGEN_CTL_reg))
#define EMMC_CKGEN_CTL_inst_adr                                                      "0x001E"
#define EMMC_CKGEN_CTL_inst                                                          0x001E
#define EMMC_CKGEN_CTL_sd30_sample_change_shift                                      (18)
#define EMMC_CKGEN_CTL_sd30_sample_change_mask                                       (0x00040000)
#define EMMC_CKGEN_CTL_sd30_sample_change(data)                                      (0x00040000&((data)<<18))
#define EMMC_CKGEN_CTL_sd30_sample_change_src(data)                                  ((0x00040000&(data))>>18)
#define EMMC_CKGEN_CTL_get_sd30_sample_change(data)                                  ((0x00040000&(data))>>18)
#define EMMC_CKGEN_CTL_sd30_push_change_shift                                        (17)
#define EMMC_CKGEN_CTL_sd30_push_change_mask                                         (0x00020000)
#define EMMC_CKGEN_CTL_sd30_push_change(data)                                        (0x00020000&((data)<<17))
#define EMMC_CKGEN_CTL_sd30_push_change_src(data)                                    ((0x00020000&(data))>>17)
#define EMMC_CKGEN_CTL_get_sd30_push_change(data)                                    ((0x00020000&(data))>>17)
#define EMMC_CKGEN_CTL_crc_clk_change_shift                                          (16)
#define EMMC_CKGEN_CTL_crc_clk_change_mask                                           (0x00010000)
#define EMMC_CKGEN_CTL_crc_clk_change(data)                                          (0x00010000&((data)<<16))
#define EMMC_CKGEN_CTL_crc_clk_change_src(data)                                      ((0x00010000&(data))>>16)
#define EMMC_CKGEN_CTL_get_crc_clk_change(data)                                      ((0x00010000&(data))>>16)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_shift                                     (12)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_mask                                      (0x00003000)
#define EMMC_CKGEN_CTL_sd30_sample_clk_src(data)                                     (0x00003000&((data)<<12))
#define EMMC_CKGEN_CTL_sd30_sample_clk_src_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_CKGEN_CTL_get_sd30_sample_clk_src(data)                                 ((0x00003000&(data))>>12)
#define EMMC_CKGEN_CTL_sd30_push_clk_src_shift                                       (8)
#define EMMC_CKGEN_CTL_sd30_push_clk_src_mask                                        (0x00000300)
#define EMMC_CKGEN_CTL_sd30_push_clk_src(data)                                       (0x00000300&((data)<<8))
#define EMMC_CKGEN_CTL_sd30_push_clk_src_src(data)                                   ((0x00000300&(data))>>8)
#define EMMC_CKGEN_CTL_get_sd30_push_clk_src(data)                                   ((0x00000300&(data))>>8)
#define EMMC_CKGEN_CTL_crc_clk_src_shift                                             (4)
#define EMMC_CKGEN_CTL_crc_clk_src_mask                                              (0x00000030)
#define EMMC_CKGEN_CTL_crc_clk_src(data)                                             (0x00000030&((data)<<4))
#define EMMC_CKGEN_CTL_crc_clk_src_src(data)                                         ((0x00000030&(data))>>4)
#define EMMC_CKGEN_CTL_get_crc_clk_src(data)                                         ((0x00000030&(data))>>4)
#define EMMC_CKGEN_CTL_clk_div_shift                                                 (0)
#define EMMC_CKGEN_CTL_clk_div_mask                                                  (0x00000007)
#define EMMC_CKGEN_CTL_clk_div(data)                                                 (0x00000007&((data)<<0))
#define EMMC_CKGEN_CTL_clk_div_src(data)                                             ((0x00000007&(data))>>0)
#define EMMC_CKGEN_CTL_get_clk_div(data)                                             ((0x00000007&(data))>>0)


#define EMMC_CPU_ACC_CTRL                                                            0x18012080
#define EMMC_CPU_ACC_CTRL_reg_addr                                                   "0xB8012080"
#define EMMC_CPU_ACC_CTRL_reg                                                        0xB8012080
#define set_EMMC_CPU_ACC_CTRL_reg(data)   (*((volatile unsigned int*) EMMC_CPU_ACC_CTRL_reg)=data)
#define get_EMMC_CPU_ACC_CTRL_reg   (*((volatile unsigned int*) EMMC_CPU_ACC_CTRL_reg))
#define EMMC_CPU_ACC_CTRL_inst_adr                                                   "0x0020"
#define EMMC_CPU_ACC_CTRL_inst                                                       0x0020
#define EMMC_CPU_ACC_CTRL_buf_full_shift                                             (2)
#define EMMC_CPU_ACC_CTRL_buf_full_mask                                              (0x00000004)
#define EMMC_CPU_ACC_CTRL_buf_full(data)                                             (0x00000004&((data)<<2))
#define EMMC_CPU_ACC_CTRL_buf_full_src(data)                                         ((0x00000004&(data))>>2)
#define EMMC_CPU_ACC_CTRL_get_buf_full(data)                                         ((0x00000004&(data))>>2)
#define EMMC_CPU_ACC_CTRL_buf_sw_shift                                               (1)
#define EMMC_CPU_ACC_CTRL_buf_sw_mask                                                (0x00000002)
#define EMMC_CPU_ACC_CTRL_buf_sw(data)                                               (0x00000002&((data)<<1))
#define EMMC_CPU_ACC_CTRL_buf_sw_src(data)                                           ((0x00000002&(data))>>1)
#define EMMC_CPU_ACC_CTRL_get_buf_sw(data)                                           ((0x00000002&(data))>>1)
#define EMMC_CPU_ACC_CTRL_cpu_mode_shift                                             (0)
#define EMMC_CPU_ACC_CTRL_cpu_mode_mask                                              (0x00000001)
#define EMMC_CPU_ACC_CTRL_cpu_mode(data)                                             (0x00000001&((data)<<0))
#define EMMC_CPU_ACC_CTRL_cpu_mode_src(data)                                         ((0x00000001&(data))>>0)
#define EMMC_CPU_ACC_CTRL_get_cpu_mode(data)                                         ((0x00000001&(data))>>0)


#define EMMC_CARD_SIG                                                                 0x18012084
#define EMMC_CARD_SIG_reg_addr                                                        "0xB8012084"
#define EMMC_CARD_SIG_reg                                                             0xB8012084
#define set_EMMC_CARD_SIG_reg(data)   (*((volatile unsigned int*) EMMC_CARD_SIG_reg)=data)
#define get_EMMC_CARD_SIG_reg   (*((volatile unsigned int*) EMMC_CARD_SIG_reg))
#define EMMC_CARD_SIG_inst_adr                                                        "0x0021"
#define EMMC_CARD_SIG_inst                                                            0x0021
#define EMMC_CARD_SIG_EMMC_RST_n_shift                                                (0)
#define EMMC_CARD_SIG_EMMC_RST_n_mask                                                 (0x00000001)
#define EMMC_CARD_SIG_EMMC_RST_n(data)                                                (0x00000001&((data)<<0))
#define EMMC_CARD_SIG_EMMC_RST_n_src(data)                                            ((0x00000001&(data))>>0)
#define EMMC_CARD_SIG_get_EMMC_RST_n(data)                                            ((0x00000001&(data))>>0)


#endif
