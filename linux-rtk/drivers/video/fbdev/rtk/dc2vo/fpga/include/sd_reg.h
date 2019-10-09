/**************************************************************
// Spec Version                  : 0.8
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/31 14:4:24
***************************************************************/


#ifndef _SD_REG_H_INCLUDED_
#define _SD_REG_H_INCLUDED_
#ifdef  _SD_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     map_sel:1;
unsigned int     access_en:1;
unsigned int     mem_region:4;
}SD_SRAM_CTL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     dram_sa:28;
}SD_DMA_CTL1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dma_len:16;
}SD_DMA_CTL2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     dat64_sel:1;
unsigned int     rsp17_sel:1;
unsigned int     reserved_1:2;
unsigned int     ddr_wr:1;
unsigned int     dma_xfer:1;
}SD_DMA_CTL3;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     mcu_pp_sram_lp_ena:1;
unsigned int     sys_clk_gate_ena:1;
unsigned int     cp_clk_gate_ena:1;
unsigned int     dma_sram_lp_ena:1;
unsigned int     dma_sram_rdy_num:4;
}SD_SYS_LOW_PWR;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Int4:1;
unsigned int     reserved_1:1;
unsigned int     Int2:1;
unsigned int     Int1:1;
unsigned int     write_data:1;
}SD_SD_ISR;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     reserved_1:4;
unsigned int     Int4En:1;
unsigned int     reserved_2:1;
unsigned int     Int2En:1;
unsigned int     Int1En:1;
unsigned int     write_data:1;
}SD_SD_ISREN;

typedef struct 
{
unsigned int     dmy:32;
}SD_DUMMY_SYS;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_enable4:1;
unsigned int     cr_dbg_sel:2;
unsigned int     write_enable3:1;
unsigned int     sel1:3;
unsigned int     write_enable2:1;
unsigned int     sel0:3;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}SD_DBG;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     bist_cr_ppb_rme_1:1;
unsigned int     bist_cr_ppb_rm_1:4;
unsigned int     bist_cr_ppb_rme_0:1;
unsigned int     bist_cr_ppb_rm_0:4;
unsigned int     bist_clk_en:1;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
unsigned int     bist_rstn:1;
}SD_IP_BIST_CTL;

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
}SD_IP_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     cr_bist2_rme_1:1;
unsigned int     cr_bist2_rm_1:4;
unsigned int     cr_bist2_rme_0:1;
unsigned int     cr_bist2_rm_0:4;
unsigned int     cr_bist2_drf_test_resume:1;
unsigned int     cr_drf_bist2_mode:1;
unsigned int     cr_bist2_mode:1;
unsigned int     cr_bist2_rstn:1;
}SD_BIST_CTL;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     drf_bist2_fail_3:1;
unsigned int     drf_bist2_fail_2:1;
unsigned int     drf_bist2_fail_1:1;
unsigned int     drf_bist2_fail_0:1;
unsigned int     bist2_drf_start_pause:1;
unsigned int     drf_bist2_done:1;
unsigned int     reserved_1:11;
unsigned int     bist2_fail_3:1;
unsigned int     bist2_fail_2:1;
unsigned int     bist2_fail_1:1;
unsigned int     bist2_fail_0:1;
unsigned int     bist2_done:1;
}SD_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     asic_crc_dbgo_sel:8;
unsigned int     reserved_1:1;
unsigned int     crc_dbgo_sel:4;
unsigned int     ip_ea_flash:1;
unsigned int     crc_clk_disable_trig:1;
unsigned int     mcu_time_1_us:1;
}SD_IP_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     tune3318:1;
}SD_PAD_CTL;

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
}SD_CKGEN_CTL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     bist_dbus_buf_rme:1;
unsigned int     bist_dbus_buf_rm:4;
unsigned int     bist_clk_en:1;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
}SD_SDIO_BIST_CTL;

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
}SD_SDIO_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     bist_ring_buf_rme_0:1;
unsigned int     bist_ring_buf_rm_0:4;
unsigned int     bist_clk_en:1;
unsigned int     bist_drf_test_resume:1;
unsigned int     bist_drf_mode:1;
unsigned int     bist_en:1;
}SD_SDIO_IP_BIST_CTL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     bist_drf_start_pause:1;
unsigned int     bist_drf_fail:1;
unsigned int     bist_drf_done:1;
unsigned int     bist_fail:1;
unsigned int     bist_done:1;
}SD_SDIO_IP_BIST_STS;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     sensor_clk_en:1;
unsigned int     speed_en:1;
unsigned int     daya_in:20;
unsigned int     wire_sel:1;
unsigned int     ro_sel:3;
unsigned int     rstn:1;
}SD_SPEED_SENSOR_CTRL;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     count_out:20;
unsigned int     ready:1;
}SD_SPEED_SENSOR_OUT1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     dbgo:16;
unsigned int     wsort_go:1;
}SD_SPEED_SENSOR_OUT2;

#endif

#define SD_SRAM_CTL                                                                  0x18010400
#define SD_SRAM_CTL_reg_addr                                                         "0xB8010400"
#define SD_SRAM_CTL_reg                                                              0xB8010400
#define set_SD_SRAM_CTL_reg(data)   (*((volatile unsigned int*) SD_SRAM_CTL_reg)=data)
#define get_SD_SRAM_CTL_reg   (*((volatile unsigned int*) SD_SRAM_CTL_reg))
#define SD_SRAM_CTL_inst_adr                                                         "0x0000"
#define SD_SRAM_CTL_inst                                                             0x0000
#define SD_SRAM_CTL_map_sel_shift                                                    (5)
#define SD_SRAM_CTL_map_sel_mask                                                     (0x00000020)
#define SD_SRAM_CTL_map_sel(data)                                                    (0x00000020&((data)<<5))
#define SD_SRAM_CTL_map_sel_src(data)                                                ((0x00000020&(data))>>5)
#define SD_SRAM_CTL_get_map_sel(data)                                                ((0x00000020&(data))>>5)
#define SD_SRAM_CTL_access_en_shift                                                  (4)
#define SD_SRAM_CTL_access_en_mask                                                   (0x00000010)
#define SD_SRAM_CTL_access_en(data)                                                  (0x00000010&((data)<<4))
#define SD_SRAM_CTL_access_en_src(data)                                              ((0x00000010&(data))>>4)
#define SD_SRAM_CTL_get_access_en(data)                                              ((0x00000010&(data))>>4)
#define SD_SRAM_CTL_mem_region_shift                                                 (0)
#define SD_SRAM_CTL_mem_region_mask                                                  (0x0000000F)
#define SD_SRAM_CTL_mem_region(data)                                                 (0x0000000F&((data)<<0))
#define SD_SRAM_CTL_mem_region_src(data)                                             ((0x0000000F&(data))>>0)
#define SD_SRAM_CTL_get_mem_region(data)                                             ((0x0000000F&(data))>>0)


#define SD_DMA_CTL1                                                                  0x18010404
#define SD_DMA_CTL1_reg_addr                                                         "0xB8010404"
#define SD_DMA_CTL1_reg                                                              0xB8010404
#define set_SD_DMA_CTL1_reg(data)   (*((volatile unsigned int*) SD_DMA_CTL1_reg)=data)
#define get_SD_DMA_CTL1_reg   (*((volatile unsigned int*) SD_DMA_CTL1_reg))
#define SD_DMA_CTL1_inst_adr                                                         "0x0001"
#define SD_DMA_CTL1_inst                                                             0x0001
#define SD_DMA_CTL1_dram_sa_shift                                                    (0)
#define SD_DMA_CTL1_dram_sa_mask                                                     (0x0FFFFFFF)
#define SD_DMA_CTL1_dram_sa(data)                                                    (0x0FFFFFFF&((data)<<0))
#define SD_DMA_CTL1_dram_sa_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define SD_DMA_CTL1_get_dram_sa(data)                                                ((0x0FFFFFFF&(data))>>0)


#define SD_DMA_CTL2                                                                  0x18010408
#define SD_DMA_CTL2_reg_addr                                                         "0xB8010408"
#define SD_DMA_CTL2_reg                                                              0xB8010408
#define set_SD_DMA_CTL2_reg(data)   (*((volatile unsigned int*) SD_DMA_CTL2_reg)=data)
#define get_SD_DMA_CTL2_reg   (*((volatile unsigned int*) SD_DMA_CTL2_reg))
#define SD_DMA_CTL2_inst_adr                                                         "0x0002"
#define SD_DMA_CTL2_inst                                                             0x0002
#define SD_DMA_CTL2_dma_len_shift                                                    (0)
#define SD_DMA_CTL2_dma_len_mask                                                     (0x0000FFFF)
#define SD_DMA_CTL2_dma_len(data)                                                    (0x0000FFFF&((data)<<0))
#define SD_DMA_CTL2_dma_len_src(data)                                                ((0x0000FFFF&(data))>>0)
#define SD_DMA_CTL2_get_dma_len(data)                                                ((0x0000FFFF&(data))>>0)


#define SD_DMA_CTL3                                                                  0x1801040C
#define SD_DMA_CTL3_reg_addr                                                         "0xB801040C"
#define SD_DMA_CTL3_reg                                                              0xB801040C
#define set_SD_DMA_CTL3_reg(data)   (*((volatile unsigned int*) SD_DMA_CTL3_reg)=data)
#define get_SD_DMA_CTL3_reg   (*((volatile unsigned int*) SD_DMA_CTL3_reg))
#define SD_DMA_CTL3_inst_adr                                                         "0x0003"
#define SD_DMA_CTL3_inst                                                             0x0003
#define SD_DMA_CTL3_dat64_sel_shift                                                  (5)
#define SD_DMA_CTL3_dat64_sel_mask                                                   (0x00000020)
#define SD_DMA_CTL3_dat64_sel(data)                                                  (0x00000020&((data)<<5))
#define SD_DMA_CTL3_dat64_sel_src(data)                                              ((0x00000020&(data))>>5)
#define SD_DMA_CTL3_get_dat64_sel(data)                                              ((0x00000020&(data))>>5)
#define SD_DMA_CTL3_rsp17_sel_shift                                                  (4)
#define SD_DMA_CTL3_rsp17_sel_mask                                                   (0x00000010)
#define SD_DMA_CTL3_rsp17_sel(data)                                                  (0x00000010&((data)<<4))
#define SD_DMA_CTL3_rsp17_sel_src(data)                                              ((0x00000010&(data))>>4)
#define SD_DMA_CTL3_get_rsp17_sel(data)                                              ((0x00000010&(data))>>4)
#define SD_DMA_CTL3_ddr_wr_shift                                                     (1)
#define SD_DMA_CTL3_ddr_wr_mask                                                      (0x00000002)
#define SD_DMA_CTL3_ddr_wr(data)                                                     (0x00000002&((data)<<1))
#define SD_DMA_CTL3_ddr_wr_src(data)                                                 ((0x00000002&(data))>>1)
#define SD_DMA_CTL3_get_ddr_wr(data)                                                 ((0x00000002&(data))>>1)
#define SD_DMA_CTL3_dma_xfer_shift                                                   (0)
#define SD_DMA_CTL3_dma_xfer_mask                                                    (0x00000001)
#define SD_DMA_CTL3_dma_xfer(data)                                                   (0x00000001&((data)<<0))
#define SD_DMA_CTL3_dma_xfer_src(data)                                               ((0x00000001&(data))>>0)
#define SD_DMA_CTL3_get_dma_xfer(data)                                               ((0x00000001&(data))>>0)


#define SD_SYS_LOW_PWR                                                               0x18010410
#define SD_SYS_LOW_PWR_reg_addr                                                      "0xB8010410"
#define SD_SYS_LOW_PWR_reg                                                           0xB8010410
#define set_SD_SYS_LOW_PWR_reg(data)   (*((volatile unsigned int*) SD_SYS_LOW_PWR_reg)=data)
#define get_SD_SYS_LOW_PWR_reg   (*((volatile unsigned int*) SD_SYS_LOW_PWR_reg))
#define SD_SYS_LOW_PWR_inst_adr                                                      "0x0004"
#define SD_SYS_LOW_PWR_inst                                                          0x0004
#define SD_SYS_LOW_PWR_mcu_pp_sram_lp_ena_shift                                      (7)
#define SD_SYS_LOW_PWR_mcu_pp_sram_lp_ena_mask                                       (0x00000080)
#define SD_SYS_LOW_PWR_mcu_pp_sram_lp_ena(data)                                      (0x00000080&((data)<<7))
#define SD_SYS_LOW_PWR_mcu_pp_sram_lp_ena_src(data)                                  ((0x00000080&(data))>>7)
#define SD_SYS_LOW_PWR_get_mcu_pp_sram_lp_ena(data)                                  ((0x00000080&(data))>>7)
#define SD_SYS_LOW_PWR_sys_clk_gate_ena_shift                                        (6)
#define SD_SYS_LOW_PWR_sys_clk_gate_ena_mask                                         (0x00000040)
#define SD_SYS_LOW_PWR_sys_clk_gate_ena(data)                                        (0x00000040&((data)<<6))
#define SD_SYS_LOW_PWR_sys_clk_gate_ena_src(data)                                    ((0x00000040&(data))>>6)
#define SD_SYS_LOW_PWR_get_sys_clk_gate_ena(data)                                    ((0x00000040&(data))>>6)
#define SD_SYS_LOW_PWR_cp_clk_gate_ena_shift                                         (5)
#define SD_SYS_LOW_PWR_cp_clk_gate_ena_mask                                          (0x00000020)
#define SD_SYS_LOW_PWR_cp_clk_gate_ena(data)                                         (0x00000020&((data)<<5))
#define SD_SYS_LOW_PWR_cp_clk_gate_ena_src(data)                                     ((0x00000020&(data))>>5)
#define SD_SYS_LOW_PWR_get_cp_clk_gate_ena(data)                                     ((0x00000020&(data))>>5)
#define SD_SYS_LOW_PWR_dma_sram_lp_ena_shift                                         (4)
#define SD_SYS_LOW_PWR_dma_sram_lp_ena_mask                                          (0x00000010)
#define SD_SYS_LOW_PWR_dma_sram_lp_ena(data)                                         (0x00000010&((data)<<4))
#define SD_SYS_LOW_PWR_dma_sram_lp_ena_src(data)                                     ((0x00000010&(data))>>4)
#define SD_SYS_LOW_PWR_get_dma_sram_lp_ena(data)                                     ((0x00000010&(data))>>4)
#define SD_SYS_LOW_PWR_dma_sram_rdy_num_shift                                        (0)
#define SD_SYS_LOW_PWR_dma_sram_rdy_num_mask                                         (0x0000000F)
#define SD_SYS_LOW_PWR_dma_sram_rdy_num(data)                                        (0x0000000F&((data)<<0))
#define SD_SYS_LOW_PWR_dma_sram_rdy_num_src(data)                                    ((0x0000000F&(data))>>0)
#define SD_SYS_LOW_PWR_get_dma_sram_rdy_num(data)                                    ((0x0000000F&(data))>>0)


#define SD_SD_ISR                                                                    0x18010424
#define SD_SD_ISR_reg_addr                                                           "0xB8010424"
#define SD_SD_ISR_reg                                                                0xB8010424
#define set_SD_SD_ISR_reg(data)   (*((volatile unsigned int*) SD_SD_ISR_reg)=data)
#define get_SD_SD_ISR_reg   (*((volatile unsigned int*) SD_SD_ISR_reg))
#define SD_SD_ISR_inst_adr                                                           "0x0009"
#define SD_SD_ISR_inst                                                               0x0009
#define SD_SD_ISR_Int4_shift                                                         (4)
#define SD_SD_ISR_Int4_mask                                                          (0x00000010)
#define SD_SD_ISR_Int4(data)                                                         (0x00000010&((data)<<4))
#define SD_SD_ISR_Int4_src(data)                                                     ((0x00000010&(data))>>4)
#define SD_SD_ISR_get_Int4(data)                                                     ((0x00000010&(data))>>4)
#define SD_SD_ISR_Int2_shift                                                         (2)
#define SD_SD_ISR_Int2_mask                                                          (0x00000004)
#define SD_SD_ISR_Int2(data)                                                         (0x00000004&((data)<<2))
#define SD_SD_ISR_Int2_src(data)                                                     ((0x00000004&(data))>>2)
#define SD_SD_ISR_get_Int2(data)                                                     ((0x00000004&(data))>>2)
#define SD_SD_ISR_Int1_shift                                                         (1)
#define SD_SD_ISR_Int1_mask                                                          (0x00000002)
#define SD_SD_ISR_Int1(data)                                                         (0x00000002&((data)<<1))
#define SD_SD_ISR_Int1_src(data)                                                     ((0x00000002&(data))>>1)
#define SD_SD_ISR_get_Int1(data)                                                     ((0x00000002&(data))>>1)
#define SD_SD_ISR_write_data_shift                                                   (0)
#define SD_SD_ISR_write_data_mask                                                    (0x00000001)
#define SD_SD_ISR_write_data(data)                                                   (0x00000001&((data)<<0))
#define SD_SD_ISR_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define SD_SD_ISR_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define SD_SD_ISREN                                                                  0x18010428
#define SD_SD_ISREN_reg_addr                                                         "0xB8010428"
#define SD_SD_ISREN_reg                                                              0xB8010428
#define set_SD_SD_ISREN_reg(data)   (*((volatile unsigned int*) SD_SD_ISREN_reg)=data)
#define get_SD_SD_ISREN_reg   (*((volatile unsigned int*) SD_SD_ISREN_reg))
#define SD_SD_ISREN_inst_adr                                                         "0x000A"
#define SD_SD_ISREN_inst                                                             0x000A
#define SD_SD_ISREN_Int4En_shift                                                     (4)
#define SD_SD_ISREN_Int4En_mask                                                      (0x00000010)
#define SD_SD_ISREN_Int4En(data)                                                     (0x00000010&((data)<<4))
#define SD_SD_ISREN_Int4En_src(data)                                                 ((0x00000010&(data))>>4)
#define SD_SD_ISREN_get_Int4En(data)                                                 ((0x00000010&(data))>>4)
#define SD_SD_ISREN_Int2En_shift                                                     (2)
#define SD_SD_ISREN_Int2En_mask                                                      (0x00000004)
#define SD_SD_ISREN_Int2En(data)                                                     (0x00000004&((data)<<2))
#define SD_SD_ISREN_Int2En_src(data)                                                 ((0x00000004&(data))>>2)
#define SD_SD_ISREN_get_Int2En(data)                                                 ((0x00000004&(data))>>2)
#define SD_SD_ISREN_Int1En_shift                                                     (1)
#define SD_SD_ISREN_Int1En_mask                                                      (0x00000002)
#define SD_SD_ISREN_Int1En(data)                                                     (0x00000002&((data)<<1))
#define SD_SD_ISREN_Int1En_src(data)                                                 ((0x00000002&(data))>>1)
#define SD_SD_ISREN_get_Int1En(data)                                                 ((0x00000002&(data))>>1)
#define SD_SD_ISREN_write_data_shift                                                 (0)
#define SD_SD_ISREN_write_data_mask                                                  (0x00000001)
#define SD_SD_ISREN_write_data(data)                                                 (0x00000001&((data)<<0))
#define SD_SD_ISREN_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define SD_SD_ISREN_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define SD_DUMMY_SYS                                                                 0x1801042C
#define SD_DUMMY_SYS_reg_addr                                                        "0xB801042C"
#define SD_DUMMY_SYS_reg                                                             0xB801042C
#define set_SD_DUMMY_SYS_reg(data)   (*((volatile unsigned int*) SD_DUMMY_SYS_reg)=data)
#define get_SD_DUMMY_SYS_reg   (*((volatile unsigned int*) SD_DUMMY_SYS_reg))
#define SD_DUMMY_SYS_inst_adr                                                        "0x000B"
#define SD_DUMMY_SYS_inst                                                            0x000B
#define SD_DUMMY_SYS_dmy_shift                                                       (0)
#define SD_DUMMY_SYS_dmy_mask                                                        (0xFFFFFFFF)
#define SD_DUMMY_SYS_dmy(data)                                                       (0xFFFFFFFF&((data)<<0))
#define SD_DUMMY_SYS_dmy_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define SD_DUMMY_SYS_get_dmy(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define SD_DBG                                                                       0x18010444
#define SD_DBG_reg_addr                                                              "0xB8010444"
#define SD_DBG_reg                                                                   0xB8010444
#define set_SD_DBG_reg(data)   (*((volatile unsigned int*) SD_DBG_reg)=data)
#define get_SD_DBG_reg   (*((volatile unsigned int*) SD_DBG_reg))
#define SD_DBG_inst_adr                                                              "0x0011"
#define SD_DBG_inst                                                                  0x0011
#define SD_DBG_write_enable4_shift                                                   (12)
#define SD_DBG_write_enable4_mask                                                    (0x00001000)
#define SD_DBG_write_enable4(data)                                                   (0x00001000&((data)<<12))
#define SD_DBG_write_enable4_src(data)                                               ((0x00001000&(data))>>12)
#define SD_DBG_get_write_enable4(data)                                               ((0x00001000&(data))>>12)
#define SD_DBG_cr_dbg_sel_shift                                                      (10)
#define SD_DBG_cr_dbg_sel_mask                                                       (0x00000C00)
#define SD_DBG_cr_dbg_sel(data)                                                      (0x00000C00&((data)<<10))
#define SD_DBG_cr_dbg_sel_src(data)                                                  ((0x00000C00&(data))>>10)
#define SD_DBG_get_cr_dbg_sel(data)                                                  ((0x00000C00&(data))>>10)
#define SD_DBG_write_enable3_shift                                                   (9)
#define SD_DBG_write_enable3_mask                                                    (0x00000200)
#define SD_DBG_write_enable3(data)                                                   (0x00000200&((data)<<9))
#define SD_DBG_write_enable3_src(data)                                               ((0x00000200&(data))>>9)
#define SD_DBG_get_write_enable3(data)                                               ((0x00000200&(data))>>9)
#define SD_DBG_sel1_shift                                                            (6)
#define SD_DBG_sel1_mask                                                             (0x000001C0)
#define SD_DBG_sel1(data)                                                            (0x000001C0&((data)<<6))
#define SD_DBG_sel1_src(data)                                                        ((0x000001C0&(data))>>6)
#define SD_DBG_get_sel1(data)                                                        ((0x000001C0&(data))>>6)
#define SD_DBG_write_enable2_shift                                                   (5)
#define SD_DBG_write_enable2_mask                                                    (0x00000020)
#define SD_DBG_write_enable2(data)                                                   (0x00000020&((data)<<5))
#define SD_DBG_write_enable2_src(data)                                               ((0x00000020&(data))>>5)
#define SD_DBG_get_write_enable2(data)                                               ((0x00000020&(data))>>5)
#define SD_DBG_sel0_shift                                                            (2)
#define SD_DBG_sel0_mask                                                             (0x0000001C)
#define SD_DBG_sel0(data)                                                            (0x0000001C&((data)<<2))
#define SD_DBG_sel0_src(data)                                                        ((0x0000001C&(data))>>2)
#define SD_DBG_get_sel0(data)                                                        ((0x0000001C&(data))>>2)
#define SD_DBG_write_enable1_shift                                                   (1)
#define SD_DBG_write_enable1_mask                                                    (0x00000002)
#define SD_DBG_write_enable1(data)                                                   (0x00000002&((data)<<1))
#define SD_DBG_write_enable1_src(data)                                               ((0x00000002&(data))>>1)
#define SD_DBG_get_write_enable1(data)                                               ((0x00000002&(data))>>1)
#define SD_DBG_enable_shift                                                          (0)
#define SD_DBG_enable_mask                                                           (0x00000001)
#define SD_DBG_enable(data)                                                          (0x00000001&((data)<<0))
#define SD_DBG_enable_src(data)                                                      ((0x00000001&(data))>>0)
#define SD_DBG_get_enable(data)                                                      ((0x00000001&(data))>>0)


#define SD_IP_BIST_CTL                                                               0x18010460
#define SD_IP_BIST_CTL_reg_addr                                                      "0xB8010460"
#define SD_IP_BIST_CTL_reg                                                           0xB8010460
#define set_SD_IP_BIST_CTL_reg(data)   (*((volatile unsigned int*) SD_IP_BIST_CTL_reg)=data)
#define get_SD_IP_BIST_CTL_reg   (*((volatile unsigned int*) SD_IP_BIST_CTL_reg))
#define SD_IP_BIST_CTL_inst_adr                                                      "0x0018"
#define SD_IP_BIST_CTL_inst                                                          0x0018
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_1_shift                                       (14)
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_1_mask                                        (0x00004000)
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_1(data)                                       (0x00004000&((data)<<14))
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_1_src(data)                                   ((0x00004000&(data))>>14)
#define SD_IP_BIST_CTL_get_bist_cr_ppb_rme_1(data)                                   ((0x00004000&(data))>>14)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_1_shift                                        (10)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_1_mask                                         (0x00003C00)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_1(data)                                        (0x00003C00&((data)<<10))
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_1_src(data)                                    ((0x00003C00&(data))>>10)
#define SD_IP_BIST_CTL_get_bist_cr_ppb_rm_1(data)                                    ((0x00003C00&(data))>>10)
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_0_shift                                       (9)
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_0_mask                                        (0x00000200)
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_0(data)                                       (0x00000200&((data)<<9))
#define SD_IP_BIST_CTL_bist_cr_ppb_rme_0_src(data)                                   ((0x00000200&(data))>>9)
#define SD_IP_BIST_CTL_get_bist_cr_ppb_rme_0(data)                                   ((0x00000200&(data))>>9)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_0_shift                                        (5)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_0_mask                                         (0x000001E0)
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_0(data)                                        (0x000001E0&((data)<<5))
#define SD_IP_BIST_CTL_bist_cr_ppb_rm_0_src(data)                                    ((0x000001E0&(data))>>5)
#define SD_IP_BIST_CTL_get_bist_cr_ppb_rm_0(data)                                    ((0x000001E0&(data))>>5)
#define SD_IP_BIST_CTL_bist_clk_en_shift                                             (4)
#define SD_IP_BIST_CTL_bist_clk_en_mask                                              (0x00000010)
#define SD_IP_BIST_CTL_bist_clk_en(data)                                             (0x00000010&((data)<<4))
#define SD_IP_BIST_CTL_bist_clk_en_src(data)                                         ((0x00000010&(data))>>4)
#define SD_IP_BIST_CTL_get_bist_clk_en(data)                                         ((0x00000010&(data))>>4)
#define SD_IP_BIST_CTL_bist_drf_test_resume_shift                                    (3)
#define SD_IP_BIST_CTL_bist_drf_test_resume_mask                                     (0x00000008)
#define SD_IP_BIST_CTL_bist_drf_test_resume(data)                                    (0x00000008&((data)<<3))
#define SD_IP_BIST_CTL_bist_drf_test_resume_src(data)                                ((0x00000008&(data))>>3)
#define SD_IP_BIST_CTL_get_bist_drf_test_resume(data)                                ((0x00000008&(data))>>3)
#define SD_IP_BIST_CTL_bist_drf_mode_shift                                           (2)
#define SD_IP_BIST_CTL_bist_drf_mode_mask                                            (0x00000004)
#define SD_IP_BIST_CTL_bist_drf_mode(data)                                           (0x00000004&((data)<<2))
#define SD_IP_BIST_CTL_bist_drf_mode_src(data)                                       ((0x00000004&(data))>>2)
#define SD_IP_BIST_CTL_get_bist_drf_mode(data)                                       ((0x00000004&(data))>>2)
#define SD_IP_BIST_CTL_bist_en_shift                                                 (1)
#define SD_IP_BIST_CTL_bist_en_mask                                                  (0x00000002)
#define SD_IP_BIST_CTL_bist_en(data)                                                 (0x00000002&((data)<<1))
#define SD_IP_BIST_CTL_bist_en_src(data)                                             ((0x00000002&(data))>>1)
#define SD_IP_BIST_CTL_get_bist_en(data)                                             ((0x00000002&(data))>>1)
#define SD_IP_BIST_CTL_bist_rstn_shift                                               (0)
#define SD_IP_BIST_CTL_bist_rstn_mask                                                (0x00000001)
#define SD_IP_BIST_CTL_bist_rstn(data)                                               (0x00000001&((data)<<0))
#define SD_IP_BIST_CTL_bist_rstn_src(data)                                           ((0x00000001&(data))>>0)
#define SD_IP_BIST_CTL_get_bist_rstn(data)                                           ((0x00000001&(data))>>0)


#define SD_IP_BIST_STS                                                               0x18010464
#define SD_IP_BIST_STS_reg_addr                                                      "0xB8010464"
#define SD_IP_BIST_STS_reg                                                           0xB8010464
#define set_SD_IP_BIST_STS_reg(data)   (*((volatile unsigned int*) SD_IP_BIST_STS_reg)=data)
#define get_SD_IP_BIST_STS_reg   (*((volatile unsigned int*) SD_IP_BIST_STS_reg))
#define SD_IP_BIST_STS_inst_adr                                                      "0x0019"
#define SD_IP_BIST_STS_inst                                                          0x0019
#define SD_IP_BIST_STS_bist_drf_start_pause_shift                                    (6)
#define SD_IP_BIST_STS_bist_drf_start_pause_mask                                     (0x00000040)
#define SD_IP_BIST_STS_bist_drf_start_pause(data)                                    (0x00000040&((data)<<6))
#define SD_IP_BIST_STS_bist_drf_start_pause_src(data)                                ((0x00000040&(data))>>6)
#define SD_IP_BIST_STS_get_bist_drf_start_pause(data)                                ((0x00000040&(data))>>6)
#define SD_IP_BIST_STS_bist_drf_fail_1_shift                                         (5)
#define SD_IP_BIST_STS_bist_drf_fail_1_mask                                          (0x00000020)
#define SD_IP_BIST_STS_bist_drf_fail_1(data)                                         (0x00000020&((data)<<5))
#define SD_IP_BIST_STS_bist_drf_fail_1_src(data)                                     ((0x00000020&(data))>>5)
#define SD_IP_BIST_STS_get_bist_drf_fail_1(data)                                     ((0x00000020&(data))>>5)
#define SD_IP_BIST_STS_bist_drf_fail_0_shift                                         (4)
#define SD_IP_BIST_STS_bist_drf_fail_0_mask                                          (0x00000010)
#define SD_IP_BIST_STS_bist_drf_fail_0(data)                                         (0x00000010&((data)<<4))
#define SD_IP_BIST_STS_bist_drf_fail_0_src(data)                                     ((0x00000010&(data))>>4)
#define SD_IP_BIST_STS_get_bist_drf_fail_0(data)                                     ((0x00000010&(data))>>4)
#define SD_IP_BIST_STS_bist_drf_done_shift                                           (3)
#define SD_IP_BIST_STS_bist_drf_done_mask                                            (0x00000008)
#define SD_IP_BIST_STS_bist_drf_done(data)                                           (0x00000008&((data)<<3))
#define SD_IP_BIST_STS_bist_drf_done_src(data)                                       ((0x00000008&(data))>>3)
#define SD_IP_BIST_STS_get_bist_drf_done(data)                                       ((0x00000008&(data))>>3)
#define SD_IP_BIST_STS_bist_1_fail_shift                                             (2)
#define SD_IP_BIST_STS_bist_1_fail_mask                                              (0x00000004)
#define SD_IP_BIST_STS_bist_1_fail(data)                                             (0x00000004&((data)<<2))
#define SD_IP_BIST_STS_bist_1_fail_src(data)                                         ((0x00000004&(data))>>2)
#define SD_IP_BIST_STS_get_bist_1_fail(data)                                         ((0x00000004&(data))>>2)
#define SD_IP_BIST_STS_bist_0_fail_shift                                             (1)
#define SD_IP_BIST_STS_bist_0_fail_mask                                              (0x00000002)
#define SD_IP_BIST_STS_bist_0_fail(data)                                             (0x00000002&((data)<<1))
#define SD_IP_BIST_STS_bist_0_fail_src(data)                                         ((0x00000002&(data))>>1)
#define SD_IP_BIST_STS_get_bist_0_fail(data)                                         ((0x00000002&(data))>>1)
#define SD_IP_BIST_STS_bist_done_shift                                               (0)
#define SD_IP_BIST_STS_bist_done_mask                                                (0x00000001)
#define SD_IP_BIST_STS_bist_done(data)                                               (0x00000001&((data)<<0))
#define SD_IP_BIST_STS_bist_done_src(data)                                           ((0x00000001&(data))>>0)
#define SD_IP_BIST_STS_get_bist_done(data)                                           ((0x00000001&(data))>>0)


#define SD_BIST_CTL                                                                  0x18010468
#define SD_BIST_CTL_reg_addr                                                         "0xB8010468"
#define SD_BIST_CTL_reg                                                              0xB8010468
#define set_SD_BIST_CTL_reg(data)   (*((volatile unsigned int*) SD_BIST_CTL_reg)=data)
#define get_SD_BIST_CTL_reg   (*((volatile unsigned int*) SD_BIST_CTL_reg))
#define SD_BIST_CTL_inst_adr                                                         "0x001A"
#define SD_BIST_CTL_inst                                                             0x001A
#define SD_BIST_CTL_cr_bist2_rme_1_shift                                             (13)
#define SD_BIST_CTL_cr_bist2_rme_1_mask                                              (0x00002000)
#define SD_BIST_CTL_cr_bist2_rme_1(data)                                             (0x00002000&((data)<<13))
#define SD_BIST_CTL_cr_bist2_rme_1_src(data)                                         ((0x00002000&(data))>>13)
#define SD_BIST_CTL_get_cr_bist2_rme_1(data)                                         ((0x00002000&(data))>>13)
#define SD_BIST_CTL_cr_bist2_rm_1_shift                                              (9)
#define SD_BIST_CTL_cr_bist2_rm_1_mask                                               (0x00001E00)
#define SD_BIST_CTL_cr_bist2_rm_1(data)                                              (0x00001E00&((data)<<9))
#define SD_BIST_CTL_cr_bist2_rm_1_src(data)                                          ((0x00001E00&(data))>>9)
#define SD_BIST_CTL_get_cr_bist2_rm_1(data)                                          ((0x00001E00&(data))>>9)
#define SD_BIST_CTL_cr_bist2_rme_0_shift                                             (8)
#define SD_BIST_CTL_cr_bist2_rme_0_mask                                              (0x00000100)
#define SD_BIST_CTL_cr_bist2_rme_0(data)                                             (0x00000100&((data)<<8))
#define SD_BIST_CTL_cr_bist2_rme_0_src(data)                                         ((0x00000100&(data))>>8)
#define SD_BIST_CTL_get_cr_bist2_rme_0(data)                                         ((0x00000100&(data))>>8)
#define SD_BIST_CTL_cr_bist2_rm_0_shift                                              (4)
#define SD_BIST_CTL_cr_bist2_rm_0_mask                                               (0x000000F0)
#define SD_BIST_CTL_cr_bist2_rm_0(data)                                              (0x000000F0&((data)<<4))
#define SD_BIST_CTL_cr_bist2_rm_0_src(data)                                          ((0x000000F0&(data))>>4)
#define SD_BIST_CTL_get_cr_bist2_rm_0(data)                                          ((0x000000F0&(data))>>4)
#define SD_BIST_CTL_cr_bist2_drf_test_resume_shift                                   (3)
#define SD_BIST_CTL_cr_bist2_drf_test_resume_mask                                    (0x00000008)
#define SD_BIST_CTL_cr_bist2_drf_test_resume(data)                                   (0x00000008&((data)<<3))
#define SD_BIST_CTL_cr_bist2_drf_test_resume_src(data)                               ((0x00000008&(data))>>3)
#define SD_BIST_CTL_get_cr_bist2_drf_test_resume(data)                               ((0x00000008&(data))>>3)
#define SD_BIST_CTL_cr_drf_bist2_mode_shift                                          (2)
#define SD_BIST_CTL_cr_drf_bist2_mode_mask                                           (0x00000004)
#define SD_BIST_CTL_cr_drf_bist2_mode(data)                                          (0x00000004&((data)<<2))
#define SD_BIST_CTL_cr_drf_bist2_mode_src(data)                                      ((0x00000004&(data))>>2)
#define SD_BIST_CTL_get_cr_drf_bist2_mode(data)                                      ((0x00000004&(data))>>2)
#define SD_BIST_CTL_cr_bist2_mode_shift                                              (1)
#define SD_BIST_CTL_cr_bist2_mode_mask                                               (0x00000002)
#define SD_BIST_CTL_cr_bist2_mode(data)                                              (0x00000002&((data)<<1))
#define SD_BIST_CTL_cr_bist2_mode_src(data)                                          ((0x00000002&(data))>>1)
#define SD_BIST_CTL_get_cr_bist2_mode(data)                                          ((0x00000002&(data))>>1)
#define SD_BIST_CTL_cr_bist2_rstn_shift                                              (0)
#define SD_BIST_CTL_cr_bist2_rstn_mask                                               (0x00000001)
#define SD_BIST_CTL_cr_bist2_rstn(data)                                              (0x00000001&((data)<<0))
#define SD_BIST_CTL_cr_bist2_rstn_src(data)                                          ((0x00000001&(data))>>0)
#define SD_BIST_CTL_get_cr_bist2_rstn(data)                                          ((0x00000001&(data))>>0)


#define SD_BIST_STS                                                                  0x1801046C
#define SD_BIST_STS_reg_addr                                                         "0xB801046C"
#define SD_BIST_STS_reg                                                              0xB801046C
#define set_SD_BIST_STS_reg(data)   (*((volatile unsigned int*) SD_BIST_STS_reg)=data)
#define get_SD_BIST_STS_reg   (*((volatile unsigned int*) SD_BIST_STS_reg))
#define SD_BIST_STS_inst_adr                                                         "0x001B"
#define SD_BIST_STS_inst                                                             0x001B
#define SD_BIST_STS_drf_bist2_fail_3_shift                                           (21)
#define SD_BIST_STS_drf_bist2_fail_3_mask                                            (0x00200000)
#define SD_BIST_STS_drf_bist2_fail_3(data)                                           (0x00200000&((data)<<21))
#define SD_BIST_STS_drf_bist2_fail_3_src(data)                                       ((0x00200000&(data))>>21)
#define SD_BIST_STS_get_drf_bist2_fail_3(data)                                       ((0x00200000&(data))>>21)
#define SD_BIST_STS_drf_bist2_fail_2_shift                                           (20)
#define SD_BIST_STS_drf_bist2_fail_2_mask                                            (0x00100000)
#define SD_BIST_STS_drf_bist2_fail_2(data)                                           (0x00100000&((data)<<20))
#define SD_BIST_STS_drf_bist2_fail_2_src(data)                                       ((0x00100000&(data))>>20)
#define SD_BIST_STS_get_drf_bist2_fail_2(data)                                       ((0x00100000&(data))>>20)
#define SD_BIST_STS_drf_bist2_fail_1_shift                                           (19)
#define SD_BIST_STS_drf_bist2_fail_1_mask                                            (0x00080000)
#define SD_BIST_STS_drf_bist2_fail_1(data)                                           (0x00080000&((data)<<19))
#define SD_BIST_STS_drf_bist2_fail_1_src(data)                                       ((0x00080000&(data))>>19)
#define SD_BIST_STS_get_drf_bist2_fail_1(data)                                       ((0x00080000&(data))>>19)
#define SD_BIST_STS_drf_bist2_fail_0_shift                                           (18)
#define SD_BIST_STS_drf_bist2_fail_0_mask                                            (0x00040000)
#define SD_BIST_STS_drf_bist2_fail_0(data)                                           (0x00040000&((data)<<18))
#define SD_BIST_STS_drf_bist2_fail_0_src(data)                                       ((0x00040000&(data))>>18)
#define SD_BIST_STS_get_drf_bist2_fail_0(data)                                       ((0x00040000&(data))>>18)
#define SD_BIST_STS_bist2_drf_start_pause_shift                                      (17)
#define SD_BIST_STS_bist2_drf_start_pause_mask                                       (0x00020000)
#define SD_BIST_STS_bist2_drf_start_pause(data)                                      (0x00020000&((data)<<17))
#define SD_BIST_STS_bist2_drf_start_pause_src(data)                                  ((0x00020000&(data))>>17)
#define SD_BIST_STS_get_bist2_drf_start_pause(data)                                  ((0x00020000&(data))>>17)
#define SD_BIST_STS_drf_bist2_done_shift                                             (16)
#define SD_BIST_STS_drf_bist2_done_mask                                              (0x00010000)
#define SD_BIST_STS_drf_bist2_done(data)                                             (0x00010000&((data)<<16))
#define SD_BIST_STS_drf_bist2_done_src(data)                                         ((0x00010000&(data))>>16)
#define SD_BIST_STS_get_drf_bist2_done(data)                                         ((0x00010000&(data))>>16)
#define SD_BIST_STS_bist2_fail_3_shift                                               (4)
#define SD_BIST_STS_bist2_fail_3_mask                                                (0x00000010)
#define SD_BIST_STS_bist2_fail_3(data)                                               (0x00000010&((data)<<4))
#define SD_BIST_STS_bist2_fail_3_src(data)                                           ((0x00000010&(data))>>4)
#define SD_BIST_STS_get_bist2_fail_3(data)                                           ((0x00000010&(data))>>4)
#define SD_BIST_STS_bist2_fail_2_shift                                               (3)
#define SD_BIST_STS_bist2_fail_2_mask                                                (0x00000008)
#define SD_BIST_STS_bist2_fail_2(data)                                               (0x00000008&((data)<<3))
#define SD_BIST_STS_bist2_fail_2_src(data)                                           ((0x00000008&(data))>>3)
#define SD_BIST_STS_get_bist2_fail_2(data)                                           ((0x00000008&(data))>>3)
#define SD_BIST_STS_bist2_fail_1_shift                                               (2)
#define SD_BIST_STS_bist2_fail_1_mask                                                (0x00000004)
#define SD_BIST_STS_bist2_fail_1(data)                                               (0x00000004&((data)<<2))
#define SD_BIST_STS_bist2_fail_1_src(data)                                           ((0x00000004&(data))>>2)
#define SD_BIST_STS_get_bist2_fail_1(data)                                           ((0x00000004&(data))>>2)
#define SD_BIST_STS_bist2_fail_0_shift                                               (1)
#define SD_BIST_STS_bist2_fail_0_mask                                                (0x00000002)
#define SD_BIST_STS_bist2_fail_0(data)                                               (0x00000002&((data)<<1))
#define SD_BIST_STS_bist2_fail_0_src(data)                                           ((0x00000002&(data))>>1)
#define SD_BIST_STS_get_bist2_fail_0(data)                                           ((0x00000002&(data))>>1)
#define SD_BIST_STS_bist2_done_shift                                                 (0)
#define SD_BIST_STS_bist2_done_mask                                                  (0x00000001)
#define SD_BIST_STS_bist2_done(data)                                                 (0x00000001&((data)<<0))
#define SD_BIST_STS_bist2_done_src(data)                                             ((0x00000001&(data))>>0)
#define SD_BIST_STS_get_bist2_done(data)                                             ((0x00000001&(data))>>0)


#define SD_IP_CTL                                                                    0x18010470
#define SD_IP_CTL_reg_addr                                                           "0xB8010470"
#define SD_IP_CTL_reg                                                                0xB8010470
#define set_SD_IP_CTL_reg(data)   (*((volatile unsigned int*) SD_IP_CTL_reg)=data)
#define get_SD_IP_CTL_reg   (*((volatile unsigned int*) SD_IP_CTL_reg))
#define SD_IP_CTL_inst_adr                                                           "0x001C"
#define SD_IP_CTL_inst                                                               0x001C
#define SD_IP_CTL_asic_crc_dbgo_sel_shift                                            (8)
#define SD_IP_CTL_asic_crc_dbgo_sel_mask                                             (0x0000FF00)
#define SD_IP_CTL_asic_crc_dbgo_sel(data)                                            (0x0000FF00&((data)<<8))
#define SD_IP_CTL_asic_crc_dbgo_sel_src(data)                                        ((0x0000FF00&(data))>>8)
#define SD_IP_CTL_get_asic_crc_dbgo_sel(data)                                        ((0x0000FF00&(data))>>8)
#define SD_IP_CTL_crc_dbgo_sel_shift                                                 (3)
#define SD_IP_CTL_crc_dbgo_sel_mask                                                  (0x00000078)
#define SD_IP_CTL_crc_dbgo_sel(data)                                                 (0x00000078&((data)<<3))
#define SD_IP_CTL_crc_dbgo_sel_src(data)                                             ((0x00000078&(data))>>3)
#define SD_IP_CTL_get_crc_dbgo_sel(data)                                             ((0x00000078&(data))>>3)
#define SD_IP_CTL_ip_ea_flash_shift                                                  (2)
#define SD_IP_CTL_ip_ea_flash_mask                                                   (0x00000004)
#define SD_IP_CTL_ip_ea_flash(data)                                                  (0x00000004&((data)<<2))
#define SD_IP_CTL_ip_ea_flash_src(data)                                              ((0x00000004&(data))>>2)
#define SD_IP_CTL_get_ip_ea_flash(data)                                              ((0x00000004&(data))>>2)
#define SD_IP_CTL_crc_clk_disable_trig_shift                                         (1)
#define SD_IP_CTL_crc_clk_disable_trig_mask                                          (0x00000002)
#define SD_IP_CTL_crc_clk_disable_trig(data)                                         (0x00000002&((data)<<1))
#define SD_IP_CTL_crc_clk_disable_trig_src(data)                                     ((0x00000002&(data))>>1)
#define SD_IP_CTL_get_crc_clk_disable_trig(data)                                     ((0x00000002&(data))>>1)
#define SD_IP_CTL_mcu_time_1_us_shift                                                (0)
#define SD_IP_CTL_mcu_time_1_us_mask                                                 (0x00000001)
#define SD_IP_CTL_mcu_time_1_us(data)                                                (0x00000001&((data)<<0))
#define SD_IP_CTL_mcu_time_1_us_src(data)                                            ((0x00000001&(data))>>0)
#define SD_IP_CTL_get_mcu_time_1_us(data)                                            ((0x00000001&(data))>>0)


#define SD_PAD_CTL                                                                   0x18010474
#define SD_PAD_CTL_reg_addr                                                          "0xB8010474"
#define SD_PAD_CTL_reg                                                               0xB8010474
#define set_SD_PAD_CTL_reg(data)   (*((volatile unsigned int*) SD_PAD_CTL_reg)=data)
#define get_SD_PAD_CTL_reg   (*((volatile unsigned int*) SD_PAD_CTL_reg))
#define SD_PAD_CTL_inst_adr                                                          "0x001D"
#define SD_PAD_CTL_inst                                                              0x001D
#define SD_PAD_CTL_tune3318_shift                                                    (0)
#define SD_PAD_CTL_tune3318_mask                                                     (0x00000001)
#define SD_PAD_CTL_tune3318(data)                                                    (0x00000001&((data)<<0))
#define SD_PAD_CTL_tune3318_src(data)                                                ((0x00000001&(data))>>0)
#define SD_PAD_CTL_get_tune3318(data)                                                ((0x00000001&(data))>>0)


#define SD_CKGEN_CTL                                                                 0x18010478
#define SD_CKGEN_CTL_reg_addr                                                        "0xB8010478"
#define SD_CKGEN_CTL_reg                                                             0xB8010478
#define set_SD_CKGEN_CTL_reg(data)   (*((volatile unsigned int*) SD_CKGEN_CTL_reg)=data)
#define get_SD_CKGEN_CTL_reg   (*((volatile unsigned int*) SD_CKGEN_CTL_reg))
#define SD_CKGEN_CTL_inst_adr                                                        "0x001E"
#define SD_CKGEN_CTL_inst                                                            0x001E
#define SD_CKGEN_CTL_sd30_sample_change_shift                                        (18)
#define SD_CKGEN_CTL_sd30_sample_change_mask                                         (0x00040000)
#define SD_CKGEN_CTL_sd30_sample_change(data)                                        (0x00040000&((data)<<18))
#define SD_CKGEN_CTL_sd30_sample_change_src(data)                                    ((0x00040000&(data))>>18)
#define SD_CKGEN_CTL_get_sd30_sample_change(data)                                    ((0x00040000&(data))>>18)
#define SD_CKGEN_CTL_sd30_push_change_shift                                          (17)
#define SD_CKGEN_CTL_sd30_push_change_mask                                           (0x00020000)
#define SD_CKGEN_CTL_sd30_push_change(data)                                          (0x00020000&((data)<<17))
#define SD_CKGEN_CTL_sd30_push_change_src(data)                                      ((0x00020000&(data))>>17)
#define SD_CKGEN_CTL_get_sd30_push_change(data)                                      ((0x00020000&(data))>>17)
#define SD_CKGEN_CTL_crc_clk_change_shift                                            (16)
#define SD_CKGEN_CTL_crc_clk_change_mask                                             (0x00010000)
#define SD_CKGEN_CTL_crc_clk_change(data)                                            (0x00010000&((data)<<16))
#define SD_CKGEN_CTL_crc_clk_change_src(data)                                        ((0x00010000&(data))>>16)
#define SD_CKGEN_CTL_get_crc_clk_change(data)                                        ((0x00010000&(data))>>16)
#define SD_CKGEN_CTL_sd30_sample_clk_src_shift                                       (12)
#define SD_CKGEN_CTL_sd30_sample_clk_src_mask                                        (0x00003000)
#define SD_CKGEN_CTL_sd30_sample_clk_src(data)                                       (0x00003000&((data)<<12))
#define SD_CKGEN_CTL_sd30_sample_clk_src_src(data)                                   ((0x00003000&(data))>>12)
#define SD_CKGEN_CTL_get_sd30_sample_clk_src(data)                                   ((0x00003000&(data))>>12)
#define SD_CKGEN_CTL_sd30_push_clk_src_shift                                         (8)
#define SD_CKGEN_CTL_sd30_push_clk_src_mask                                          (0x00000300)
#define SD_CKGEN_CTL_sd30_push_clk_src(data)                                         (0x00000300&((data)<<8))
#define SD_CKGEN_CTL_sd30_push_clk_src_src(data)                                     ((0x00000300&(data))>>8)
#define SD_CKGEN_CTL_get_sd30_push_clk_src(data)                                     ((0x00000300&(data))>>8)
#define SD_CKGEN_CTL_crc_clk_src_shift                                               (4)
#define SD_CKGEN_CTL_crc_clk_src_mask                                                (0x00000030)
#define SD_CKGEN_CTL_crc_clk_src(data)                                               (0x00000030&((data)<<4))
#define SD_CKGEN_CTL_crc_clk_src_src(data)                                           ((0x00000030&(data))>>4)
#define SD_CKGEN_CTL_get_crc_clk_src(data)                                           ((0x00000030&(data))>>4)
#define SD_CKGEN_CTL_clk_div_shift                                                   (0)
#define SD_CKGEN_CTL_clk_div_mask                                                    (0x00000007)
#define SD_CKGEN_CTL_clk_div(data)                                                   (0x00000007&((data)<<0))
#define SD_CKGEN_CTL_clk_div_src(data)                                               ((0x00000007&(data))>>0)
#define SD_CKGEN_CTL_get_clk_div(data)                                               ((0x00000007&(data))>>0)


#define SD_SDIO_BIST_CTL                                                             0x18010480
#define SD_SDIO_BIST_CTL_reg_addr                                                    "0xB8010480"
#define SD_SDIO_BIST_CTL_reg                                                         0xB8010480
#define set_SD_SDIO_BIST_CTL_reg(data)   (*((volatile unsigned int*) SD_SDIO_BIST_CTL_reg)=data)
#define get_SD_SDIO_BIST_CTL_reg   (*((volatile unsigned int*) SD_SDIO_BIST_CTL_reg))
#define SD_SDIO_BIST_CTL_inst_adr                                                    "0x0020"
#define SD_SDIO_BIST_CTL_inst                                                        0x0020
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rme_shift                                     (8)
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rme_mask                                      (0x00000100)
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rme(data)                                     (0x00000100&((data)<<8))
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rme_src(data)                                 ((0x00000100&(data))>>8)
#define SD_SDIO_BIST_CTL_get_bist_dbus_buf_rme(data)                                 ((0x00000100&(data))>>8)
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rm_shift                                      (4)
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rm_mask                                       (0x000000F0)
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rm(data)                                      (0x000000F0&((data)<<4))
#define SD_SDIO_BIST_CTL_bist_dbus_buf_rm_src(data)                                  ((0x000000F0&(data))>>4)
#define SD_SDIO_BIST_CTL_get_bist_dbus_buf_rm(data)                                  ((0x000000F0&(data))>>4)
#define SD_SDIO_BIST_CTL_bist_clk_en_shift                                           (3)
#define SD_SDIO_BIST_CTL_bist_clk_en_mask                                            (0x00000008)
#define SD_SDIO_BIST_CTL_bist_clk_en(data)                                           (0x00000008&((data)<<3))
#define SD_SDIO_BIST_CTL_bist_clk_en_src(data)                                       ((0x00000008&(data))>>3)
#define SD_SDIO_BIST_CTL_get_bist_clk_en(data)                                       ((0x00000008&(data))>>3)
#define SD_SDIO_BIST_CTL_bist_drf_test_resume_shift                                  (2)
#define SD_SDIO_BIST_CTL_bist_drf_test_resume_mask                                   (0x00000004)
#define SD_SDIO_BIST_CTL_bist_drf_test_resume(data)                                  (0x00000004&((data)<<2))
#define SD_SDIO_BIST_CTL_bist_drf_test_resume_src(data)                              ((0x00000004&(data))>>2)
#define SD_SDIO_BIST_CTL_get_bist_drf_test_resume(data)                              ((0x00000004&(data))>>2)
#define SD_SDIO_BIST_CTL_bist_drf_mode_shift                                         (1)
#define SD_SDIO_BIST_CTL_bist_drf_mode_mask                                          (0x00000002)
#define SD_SDIO_BIST_CTL_bist_drf_mode(data)                                         (0x00000002&((data)<<1))
#define SD_SDIO_BIST_CTL_bist_drf_mode_src(data)                                     ((0x00000002&(data))>>1)
#define SD_SDIO_BIST_CTL_get_bist_drf_mode(data)                                     ((0x00000002&(data))>>1)
#define SD_SDIO_BIST_CTL_bist_en_shift                                               (0)
#define SD_SDIO_BIST_CTL_bist_en_mask                                                (0x00000001)
#define SD_SDIO_BIST_CTL_bist_en(data)                                               (0x00000001&((data)<<0))
#define SD_SDIO_BIST_CTL_bist_en_src(data)                                           ((0x00000001&(data))>>0)
#define SD_SDIO_BIST_CTL_get_bist_en(data)                                           ((0x00000001&(data))>>0)


#define SD_SDIO_BIST_STS                                                             0x18010484
#define SD_SDIO_BIST_STS_reg_addr                                                    "0xB8010484"
#define SD_SDIO_BIST_STS_reg                                                         0xB8010484
#define set_SD_SDIO_BIST_STS_reg(data)   (*((volatile unsigned int*) SD_SDIO_BIST_STS_reg)=data)
#define get_SD_SDIO_BIST_STS_reg   (*((volatile unsigned int*) SD_SDIO_BIST_STS_reg))
#define SD_SDIO_BIST_STS_inst_adr                                                    "0x0021"
#define SD_SDIO_BIST_STS_inst                                                        0x0021
#define SD_SDIO_BIST_STS_bist_drf_start_pause_shift                                  (6)
#define SD_SDIO_BIST_STS_bist_drf_start_pause_mask                                   (0x00000040)
#define SD_SDIO_BIST_STS_bist_drf_start_pause(data)                                  (0x00000040&((data)<<6))
#define SD_SDIO_BIST_STS_bist_drf_start_pause_src(data)                              ((0x00000040&(data))>>6)
#define SD_SDIO_BIST_STS_get_bist_drf_start_pause(data)                              ((0x00000040&(data))>>6)
#define SD_SDIO_BIST_STS_bist_drf_fail_1_shift                                       (5)
#define SD_SDIO_BIST_STS_bist_drf_fail_1_mask                                        (0x00000020)
#define SD_SDIO_BIST_STS_bist_drf_fail_1(data)                                       (0x00000020&((data)<<5))
#define SD_SDIO_BIST_STS_bist_drf_fail_1_src(data)                                   ((0x00000020&(data))>>5)
#define SD_SDIO_BIST_STS_get_bist_drf_fail_1(data)                                   ((0x00000020&(data))>>5)
#define SD_SDIO_BIST_STS_bist_drf_fail_0_shift                                       (4)
#define SD_SDIO_BIST_STS_bist_drf_fail_0_mask                                        (0x00000010)
#define SD_SDIO_BIST_STS_bist_drf_fail_0(data)                                       (0x00000010&((data)<<4))
#define SD_SDIO_BIST_STS_bist_drf_fail_0_src(data)                                   ((0x00000010&(data))>>4)
#define SD_SDIO_BIST_STS_get_bist_drf_fail_0(data)                                   ((0x00000010&(data))>>4)
#define SD_SDIO_BIST_STS_bist_drf_done_shift                                         (3)
#define SD_SDIO_BIST_STS_bist_drf_done_mask                                          (0x00000008)
#define SD_SDIO_BIST_STS_bist_drf_done(data)                                         (0x00000008&((data)<<3))
#define SD_SDIO_BIST_STS_bist_drf_done_src(data)                                     ((0x00000008&(data))>>3)
#define SD_SDIO_BIST_STS_get_bist_drf_done(data)                                     ((0x00000008&(data))>>3)
#define SD_SDIO_BIST_STS_bist_1_fail_shift                                           (2)
#define SD_SDIO_BIST_STS_bist_1_fail_mask                                            (0x00000004)
#define SD_SDIO_BIST_STS_bist_1_fail(data)                                           (0x00000004&((data)<<2))
#define SD_SDIO_BIST_STS_bist_1_fail_src(data)                                       ((0x00000004&(data))>>2)
#define SD_SDIO_BIST_STS_get_bist_1_fail(data)                                       ((0x00000004&(data))>>2)
#define SD_SDIO_BIST_STS_bist_0_fail_shift                                           (1)
#define SD_SDIO_BIST_STS_bist_0_fail_mask                                            (0x00000002)
#define SD_SDIO_BIST_STS_bist_0_fail(data)                                           (0x00000002&((data)<<1))
#define SD_SDIO_BIST_STS_bist_0_fail_src(data)                                       ((0x00000002&(data))>>1)
#define SD_SDIO_BIST_STS_get_bist_0_fail(data)                                       ((0x00000002&(data))>>1)
#define SD_SDIO_BIST_STS_bist_done_shift                                             (0)
#define SD_SDIO_BIST_STS_bist_done_mask                                              (0x00000001)
#define SD_SDIO_BIST_STS_bist_done(data)                                             (0x00000001&((data)<<0))
#define SD_SDIO_BIST_STS_bist_done_src(data)                                         ((0x00000001&(data))>>0)
#define SD_SDIO_BIST_STS_get_bist_done(data)                                         ((0x00000001&(data))>>0)


#define SD_SDIO_IP_BIST_CTL                                                          0x18010488
#define SD_SDIO_IP_BIST_CTL_reg_addr                                                 "0xB8010488"
#define SD_SDIO_IP_BIST_CTL_reg                                                      0xB8010488
#define set_SD_SDIO_IP_BIST_CTL_reg(data)   (*((volatile unsigned int*) SD_SDIO_IP_BIST_CTL_reg)=data)
#define get_SD_SDIO_IP_BIST_CTL_reg   (*((volatile unsigned int*) SD_SDIO_IP_BIST_CTL_reg))
#define SD_SDIO_IP_BIST_CTL_inst_adr                                                 "0x0022"
#define SD_SDIO_IP_BIST_CTL_inst                                                     0x0022
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rme_0_shift                                (8)
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rme_0_mask                                 (0x00000100)
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rme_0(data)                                (0x00000100&((data)<<8))
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rme_0_src(data)                            ((0x00000100&(data))>>8)
#define SD_SDIO_IP_BIST_CTL_get_bist_ring_buf_rme_0(data)                            ((0x00000100&(data))>>8)
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rm_0_shift                                 (4)
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rm_0_mask                                  (0x000000F0)
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rm_0(data)                                 (0x000000F0&((data)<<4))
#define SD_SDIO_IP_BIST_CTL_bist_ring_buf_rm_0_src(data)                             ((0x000000F0&(data))>>4)
#define SD_SDIO_IP_BIST_CTL_get_bist_ring_buf_rm_0(data)                             ((0x000000F0&(data))>>4)
#define SD_SDIO_IP_BIST_CTL_bist_clk_en_shift                                        (3)
#define SD_SDIO_IP_BIST_CTL_bist_clk_en_mask                                         (0x00000008)
#define SD_SDIO_IP_BIST_CTL_bist_clk_en(data)                                        (0x00000008&((data)<<3))
#define SD_SDIO_IP_BIST_CTL_bist_clk_en_src(data)                                    ((0x00000008&(data))>>3)
#define SD_SDIO_IP_BIST_CTL_get_bist_clk_en(data)                                    ((0x00000008&(data))>>3)
#define SD_SDIO_IP_BIST_CTL_bist_drf_test_resume_shift                               (2)
#define SD_SDIO_IP_BIST_CTL_bist_drf_test_resume_mask                                (0x00000004)
#define SD_SDIO_IP_BIST_CTL_bist_drf_test_resume(data)                               (0x00000004&((data)<<2))
#define SD_SDIO_IP_BIST_CTL_bist_drf_test_resume_src(data)                           ((0x00000004&(data))>>2)
#define SD_SDIO_IP_BIST_CTL_get_bist_drf_test_resume(data)                           ((0x00000004&(data))>>2)
#define SD_SDIO_IP_BIST_CTL_bist_drf_mode_shift                                      (1)
#define SD_SDIO_IP_BIST_CTL_bist_drf_mode_mask                                       (0x00000002)
#define SD_SDIO_IP_BIST_CTL_bist_drf_mode(data)                                      (0x00000002&((data)<<1))
#define SD_SDIO_IP_BIST_CTL_bist_drf_mode_src(data)                                  ((0x00000002&(data))>>1)
#define SD_SDIO_IP_BIST_CTL_get_bist_drf_mode(data)                                  ((0x00000002&(data))>>1)
#define SD_SDIO_IP_BIST_CTL_bist_en_shift                                            (0)
#define SD_SDIO_IP_BIST_CTL_bist_en_mask                                             (0x00000001)
#define SD_SDIO_IP_BIST_CTL_bist_en(data)                                            (0x00000001&((data)<<0))
#define SD_SDIO_IP_BIST_CTL_bist_en_src(data)                                        ((0x00000001&(data))>>0)
#define SD_SDIO_IP_BIST_CTL_get_bist_en(data)                                        ((0x00000001&(data))>>0)


#define SD_SDIO_IP_BIST_STS                                                          0x1801048C
#define SD_SDIO_IP_BIST_STS_reg_addr                                                 "0xB801048C"
#define SD_SDIO_IP_BIST_STS_reg                                                      0xB801048C
#define set_SD_SDIO_IP_BIST_STS_reg(data)   (*((volatile unsigned int*) SD_SDIO_IP_BIST_STS_reg)=data)
#define get_SD_SDIO_IP_BIST_STS_reg   (*((volatile unsigned int*) SD_SDIO_IP_BIST_STS_reg))
#define SD_SDIO_IP_BIST_STS_inst_adr                                                 "0x0023"
#define SD_SDIO_IP_BIST_STS_inst                                                     0x0023
#define SD_SDIO_IP_BIST_STS_bist_drf_start_pause_shift                               (4)
#define SD_SDIO_IP_BIST_STS_bist_drf_start_pause_mask                                (0x00000010)
#define SD_SDIO_IP_BIST_STS_bist_drf_start_pause(data)                               (0x00000010&((data)<<4))
#define SD_SDIO_IP_BIST_STS_bist_drf_start_pause_src(data)                           ((0x00000010&(data))>>4)
#define SD_SDIO_IP_BIST_STS_get_bist_drf_start_pause(data)                           ((0x00000010&(data))>>4)
#define SD_SDIO_IP_BIST_STS_bist_drf_fail_shift                                      (3)
#define SD_SDIO_IP_BIST_STS_bist_drf_fail_mask                                       (0x00000008)
#define SD_SDIO_IP_BIST_STS_bist_drf_fail(data)                                      (0x00000008&((data)<<3))
#define SD_SDIO_IP_BIST_STS_bist_drf_fail_src(data)                                  ((0x00000008&(data))>>3)
#define SD_SDIO_IP_BIST_STS_get_bist_drf_fail(data)                                  ((0x00000008&(data))>>3)
#define SD_SDIO_IP_BIST_STS_bist_drf_done_shift                                      (2)
#define SD_SDIO_IP_BIST_STS_bist_drf_done_mask                                       (0x00000004)
#define SD_SDIO_IP_BIST_STS_bist_drf_done(data)                                      (0x00000004&((data)<<2))
#define SD_SDIO_IP_BIST_STS_bist_drf_done_src(data)                                  ((0x00000004&(data))>>2)
#define SD_SDIO_IP_BIST_STS_get_bist_drf_done(data)                                  ((0x00000004&(data))>>2)
#define SD_SDIO_IP_BIST_STS_bist_fail_shift                                          (1)
#define SD_SDIO_IP_BIST_STS_bist_fail_mask                                           (0x00000002)
#define SD_SDIO_IP_BIST_STS_bist_fail(data)                                          (0x00000002&((data)<<1))
#define SD_SDIO_IP_BIST_STS_bist_fail_src(data)                                      ((0x00000002&(data))>>1)
#define SD_SDIO_IP_BIST_STS_get_bist_fail(data)                                      ((0x00000002&(data))>>1)
#define SD_SDIO_IP_BIST_STS_bist_done_shift                                          (0)
#define SD_SDIO_IP_BIST_STS_bist_done_mask                                           (0x00000001)
#define SD_SDIO_IP_BIST_STS_bist_done(data)                                          (0x00000001&((data)<<0))
#define SD_SDIO_IP_BIST_STS_bist_done_src(data)                                      ((0x00000001&(data))>>0)
#define SD_SDIO_IP_BIST_STS_get_bist_done(data)                                      ((0x00000001&(data))>>0)


#define SD_SPEED_SENSOR_CTRL_0                                                       0x18010490
#define SD_SPEED_SENSOR_CTRL_1                                                       0x18010494
#define SD_SPEED_SENSOR_CTRL_0_reg_addr                                              "0xB8010490"
#define SD_SPEED_SENSOR_CTRL_1_reg_addr                                              "0xB8010494"
#define SD_SPEED_SENSOR_CTRL_0_reg                                                   0xB8010490
#define SD_SPEED_SENSOR_CTRL_1_reg                                                   0xB8010494
#define set_SD_SPEED_SENSOR_CTRL_0_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_CTRL_0_reg)=data)
#define set_SD_SPEED_SENSOR_CTRL_1_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_CTRL_1_reg)=data)
#define get_SD_SPEED_SENSOR_CTRL_0_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_CTRL_0_reg))
#define get_SD_SPEED_SENSOR_CTRL_1_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_CTRL_1_reg))
#define SD_SPEED_SENSOR_CTRL_0_inst_adr                                              "0x0024"
#define SD_SPEED_SENSOR_CTRL_1_inst_adr                                              "0x0025"
#define SD_SPEED_SENSOR_CTRL_0_inst                                                  0x0024
#define SD_SPEED_SENSOR_CTRL_1_inst                                                  0x0025
#define SD_SPEED_SENSOR_CTRL_sensor_clk_en_shift                                     (26)
#define SD_SPEED_SENSOR_CTRL_sensor_clk_en_mask                                      (0x04000000)
#define SD_SPEED_SENSOR_CTRL_sensor_clk_en(data)                                     (0x04000000&((data)<<26))
#define SD_SPEED_SENSOR_CTRL_sensor_clk_en_src(data)                                 ((0x04000000&(data))>>26)
#define SD_SPEED_SENSOR_CTRL_get_sensor_clk_en(data)                                 ((0x04000000&(data))>>26)
#define SD_SPEED_SENSOR_CTRL_speed_en_shift                                          (25)
#define SD_SPEED_SENSOR_CTRL_speed_en_mask                                           (0x02000000)
#define SD_SPEED_SENSOR_CTRL_speed_en(data)                                          (0x02000000&((data)<<25))
#define SD_SPEED_SENSOR_CTRL_speed_en_src(data)                                      ((0x02000000&(data))>>25)
#define SD_SPEED_SENSOR_CTRL_get_speed_en(data)                                      ((0x02000000&(data))>>25)
#define SD_SPEED_SENSOR_CTRL_daya_in_shift                                           (5)
#define SD_SPEED_SENSOR_CTRL_daya_in_mask                                            (0x01FFFFE0)
#define SD_SPEED_SENSOR_CTRL_daya_in(data)                                           (0x01FFFFE0&((data)<<5))
#define SD_SPEED_SENSOR_CTRL_daya_in_src(data)                                       ((0x01FFFFE0&(data))>>5)
#define SD_SPEED_SENSOR_CTRL_get_daya_in(data)                                       ((0x01FFFFE0&(data))>>5)
#define SD_SPEED_SENSOR_CTRL_wire_sel_shift                                          (4)
#define SD_SPEED_SENSOR_CTRL_wire_sel_mask                                           (0x00000010)
#define SD_SPEED_SENSOR_CTRL_wire_sel(data)                                          (0x00000010&((data)<<4))
#define SD_SPEED_SENSOR_CTRL_wire_sel_src(data)                                      ((0x00000010&(data))>>4)
#define SD_SPEED_SENSOR_CTRL_get_wire_sel(data)                                      ((0x00000010&(data))>>4)
#define SD_SPEED_SENSOR_CTRL_ro_sel_shift                                            (1)
#define SD_SPEED_SENSOR_CTRL_ro_sel_mask                                             (0x0000000E)
#define SD_SPEED_SENSOR_CTRL_ro_sel(data)                                            (0x0000000E&((data)<<1))
#define SD_SPEED_SENSOR_CTRL_ro_sel_src(data)                                        ((0x0000000E&(data))>>1)
#define SD_SPEED_SENSOR_CTRL_get_ro_sel(data)                                        ((0x0000000E&(data))>>1)
#define SD_SPEED_SENSOR_CTRL_rstn_shift                                              (0)
#define SD_SPEED_SENSOR_CTRL_rstn_mask                                               (0x00000001)
#define SD_SPEED_SENSOR_CTRL_rstn(data)                                              (0x00000001&((data)<<0))
#define SD_SPEED_SENSOR_CTRL_rstn_src(data)                                          ((0x00000001&(data))>>0)
#define SD_SPEED_SENSOR_CTRL_get_rstn(data)                                          ((0x00000001&(data))>>0)


#define SD_SPEED_SENSOR_OUT1_0                                                       0x1801049C
#define SD_SPEED_SENSOR_OUT1_1                                                       0x180104A0
#define SD_SPEED_SENSOR_OUT1_0_reg_addr                                              "0xB801049C"
#define SD_SPEED_SENSOR_OUT1_1_reg_addr                                              "0xB80104A0"
#define SD_SPEED_SENSOR_OUT1_0_reg                                                   0xB801049C
#define SD_SPEED_SENSOR_OUT1_1_reg                                                   0xB80104A0
#define set_SD_SPEED_SENSOR_OUT1_0_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT1_0_reg)=data)
#define set_SD_SPEED_SENSOR_OUT1_1_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT1_1_reg)=data)
#define get_SD_SPEED_SENSOR_OUT1_0_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT1_0_reg))
#define get_SD_SPEED_SENSOR_OUT1_1_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT1_1_reg))
#define SD_SPEED_SENSOR_OUT1_0_inst_adr                                              "0x0027"
#define SD_SPEED_SENSOR_OUT1_1_inst_adr                                              "0x0028"
#define SD_SPEED_SENSOR_OUT1_0_inst                                                  0x0027
#define SD_SPEED_SENSOR_OUT1_1_inst                                                  0x0028
#define SD_SPEED_SENSOR_OUT1_count_out_shift                                         (1)
#define SD_SPEED_SENSOR_OUT1_count_out_mask                                          (0x001FFFFE)
#define SD_SPEED_SENSOR_OUT1_count_out(data)                                         (0x001FFFFE&((data)<<1))
#define SD_SPEED_SENSOR_OUT1_count_out_src(data)                                     ((0x001FFFFE&(data))>>1)
#define SD_SPEED_SENSOR_OUT1_get_count_out(data)                                     ((0x001FFFFE&(data))>>1)
#define SD_SPEED_SENSOR_OUT1_ready_shift                                             (0)
#define SD_SPEED_SENSOR_OUT1_ready_mask                                              (0x00000001)
#define SD_SPEED_SENSOR_OUT1_ready(data)                                             (0x00000001&((data)<<0))
#define SD_SPEED_SENSOR_OUT1_ready_src(data)                                         ((0x00000001&(data))>>0)
#define SD_SPEED_SENSOR_OUT1_get_ready(data)                                         ((0x00000001&(data))>>0)


#define SD_SPEED_SENSOR_OUT2_0                                                       0x180104A4
#define SD_SPEED_SENSOR_OUT2_1                                                       0x180104A8
#define SD_SPEED_SENSOR_OUT2_0_reg_addr                                              "0xB80104A4"
#define SD_SPEED_SENSOR_OUT2_1_reg_addr                                              "0xB80104A8"
#define SD_SPEED_SENSOR_OUT2_0_reg                                                   0xB80104A4
#define SD_SPEED_SENSOR_OUT2_1_reg                                                   0xB80104A8
#define set_SD_SPEED_SENSOR_OUT2_0_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT2_0_reg)=data)
#define set_SD_SPEED_SENSOR_OUT2_1_reg(data)   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT2_1_reg)=data)
#define get_SD_SPEED_SENSOR_OUT2_0_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT2_0_reg))
#define get_SD_SPEED_SENSOR_OUT2_1_reg   (*((volatile unsigned int*) SD_SPEED_SENSOR_OUT2_1_reg))
#define SD_SPEED_SENSOR_OUT2_0_inst_adr                                              "0x0029"
#define SD_SPEED_SENSOR_OUT2_1_inst_adr                                              "0x002A"
#define SD_SPEED_SENSOR_OUT2_0_inst                                                  0x0029
#define SD_SPEED_SENSOR_OUT2_1_inst                                                  0x002A
#define SD_SPEED_SENSOR_OUT2_dbgo_shift                                              (1)
#define SD_SPEED_SENSOR_OUT2_dbgo_mask                                               (0x0001FFFE)
#define SD_SPEED_SENSOR_OUT2_dbgo(data)                                              (0x0001FFFE&((data)<<1))
#define SD_SPEED_SENSOR_OUT2_dbgo_src(data)                                          ((0x0001FFFE&(data))>>1)
#define SD_SPEED_SENSOR_OUT2_get_dbgo(data)                                          ((0x0001FFFE&(data))>>1)
#define SD_SPEED_SENSOR_OUT2_wsort_go_shift                                          (0)
#define SD_SPEED_SENSOR_OUT2_wsort_go_mask                                           (0x00000001)
#define SD_SPEED_SENSOR_OUT2_wsort_go(data)                                          (0x00000001&((data)<<0))
#define SD_SPEED_SENSOR_OUT2_wsort_go_src(data)                                      ((0x00000001&(data))>>0)
#define SD_SPEED_SENSOR_OUT2_get_wsort_go(data)                                      ((0x00000001&(data))>>0)


#endif
