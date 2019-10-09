/**************************************************************
// Spec Version                  : 0.0.7
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 1.0 2006.04.18
// Naming Rule                   : Module_Register_Name
// Firmware Header Generate Date : 2007/9/12
***************************************************************/


#ifndef _SDE_REG_H_INCLUDED_
#define _SDE_REG_H_INCLUDED_
#ifdef  _SDE_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     dmem_addr:14;
}SDE_DMEM_ADDR;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     ddr_addr:28;
}SDE_DDR_ADDR;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     length:14;
}SDE_DMA_LEN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     write_enable2:1;
unsigned int     stop:1;
unsigned int     write_enable1:1;
unsigned int     r_w:1;
unsigned int     go:1;
}SDE_DMA_CTRL;

typedef struct 
{
unsigned int     dmem_err:1;
unsigned int     reserved_0:21;
unsigned int     dma_done_7:1;
unsigned int     dma_done_6:1;
unsigned int     dma_done_5:1;
unsigned int     dma_done_4:1;
unsigned int     dma_done_3:1;
unsigned int     dma_done_2:1;
unsigned int     dma_done_1:1;
unsigned int     dma_done_0:1;
unsigned int     dma_all_done:1;
unsigned int     write_data:1;
}SDE_DMA_DONE;

typedef struct 
{
unsigned int     dmem_err_int_en:1;
unsigned int     reserved_0:21;
unsigned int     dma_done_7_en:1;
unsigned int     dma_done_6_en:1;
unsigned int     dma_done_5_en:1;
unsigned int     dma_done_4_en:1;
unsigned int     dma_done_3_en:1;
unsigned int     dma_done_2_en:1;
unsigned int     dma_done_1_en:1;
unsigned int     dma_done_0_en:1;
unsigned int     dma_all_done_en:1;
unsigned int     write_data:1;
}SDE_DMA_DONE_EN;

typedef struct 
{
unsigned int     data:32;
}SDE_DUMMY;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}SDE_DBG;

#endif

#define SDE_DMEM_ADDR_0                                                              0x18003000
#define SDE_DMEM_ADDR_1                                                              0x18003004
#define SDE_DMEM_ADDR_2                                                              0x18003008
#define SDE_DMEM_ADDR_3                                                              0x1800300C
#define SDE_DMEM_ADDR_4                                                              0x18003010
#define SDE_DMEM_ADDR_5                                                              0x18003014
#define SDE_DMEM_ADDR_6                                                              0x18003018
#define SDE_DMEM_ADDR_7                                                              0x1800301C
#define SDE_DMEM_ADDR_0_reg_addr                                                     "0xB8003000"
#define SDE_DMEM_ADDR_1_reg_addr                                                     "0xB8003004"
#define SDE_DMEM_ADDR_2_reg_addr                                                     "0xB8003008"
#define SDE_DMEM_ADDR_3_reg_addr                                                     "0xB800300C"
#define SDE_DMEM_ADDR_4_reg_addr                                                     "0xB8003010"
#define SDE_DMEM_ADDR_5_reg_addr                                                     "0xB8003014"
#define SDE_DMEM_ADDR_6_reg_addr                                                     "0xB8003018"
#define SDE_DMEM_ADDR_7_reg_addr                                                     "0xB800301C"
#define SDE_DMEM_ADDR_0_reg                                                          0xB8003000
#define SDE_DMEM_ADDR_1_reg                                                          0xB8003004
#define SDE_DMEM_ADDR_2_reg                                                          0xB8003008
#define SDE_DMEM_ADDR_3_reg                                                          0xB800300C
#define SDE_DMEM_ADDR_4_reg                                                          0xB8003010
#define SDE_DMEM_ADDR_5_reg                                                          0xB8003014
#define SDE_DMEM_ADDR_6_reg                                                          0xB8003018
#define SDE_DMEM_ADDR_7_reg                                                          0xB800301C
#define SDE_DMEM_ADDR_0_inst_adr                                                     "0x0000"
#define SDE_DMEM_ADDR_1_inst_adr                                                     "0x0001"
#define SDE_DMEM_ADDR_2_inst_adr                                                     "0x0002"
#define SDE_DMEM_ADDR_3_inst_adr                                                     "0x0003"
#define SDE_DMEM_ADDR_4_inst_adr                                                     "0x0004"
#define SDE_DMEM_ADDR_5_inst_adr                                                     "0x0005"
#define SDE_DMEM_ADDR_6_inst_adr                                                     "0x0006"
#define SDE_DMEM_ADDR_7_inst_adr                                                     "0x0007"
#define SDE_DMEM_ADDR_0_inst                                                         0x0000
#define SDE_DMEM_ADDR_1_inst                                                         0x0001
#define SDE_DMEM_ADDR_2_inst                                                         0x0002
#define SDE_DMEM_ADDR_3_inst                                                         0x0003
#define SDE_DMEM_ADDR_4_inst                                                         0x0004
#define SDE_DMEM_ADDR_5_inst                                                         0x0005
#define SDE_DMEM_ADDR_6_inst                                                         0x0006
#define SDE_DMEM_ADDR_7_inst                                                         0x0007
#define SDE_DMEM_ADDR_dmem_addr_shift                                                (0)
#define SDE_DMEM_ADDR_dmem_addr_mask                                                 (0x00003FFF)
#define SDE_DMEM_ADDR_dmem_addr(data)                                                (0x00003FFF&((data)<<0))
#define SDE_DMEM_ADDR_dmem_addr_src(data)                                            ((0x00003FFF&(data))>>0)


#define SDE_DDR_ADDR_0                                                               0x18003020
#define SDE_DDR_ADDR_1                                                               0x18003024
#define SDE_DDR_ADDR_2                                                               0x18003028
#define SDE_DDR_ADDR_3                                                               0x1800302C
#define SDE_DDR_ADDR_4                                                               0x18003030
#define SDE_DDR_ADDR_5                                                               0x18003034
#define SDE_DDR_ADDR_6                                                               0x18003038
#define SDE_DDR_ADDR_7                                                               0x1800303C
#define SDE_DDR_ADDR_0_reg_addr                                                      "0xB8003020"
#define SDE_DDR_ADDR_1_reg_addr                                                      "0xB8003024"
#define SDE_DDR_ADDR_2_reg_addr                                                      "0xB8003028"
#define SDE_DDR_ADDR_3_reg_addr                                                      "0xB800302C"
#define SDE_DDR_ADDR_4_reg_addr                                                      "0xB8003030"
#define SDE_DDR_ADDR_5_reg_addr                                                      "0xB8003034"
#define SDE_DDR_ADDR_6_reg_addr                                                      "0xB8003038"
#define SDE_DDR_ADDR_7_reg_addr                                                      "0xB800303C"
#define SDE_DDR_ADDR_0_reg                                                           0xB8003020
#define SDE_DDR_ADDR_1_reg                                                           0xB8003024
#define SDE_DDR_ADDR_2_reg                                                           0xB8003028
#define SDE_DDR_ADDR_3_reg                                                           0xB800302C
#define SDE_DDR_ADDR_4_reg                                                           0xB8003030
#define SDE_DDR_ADDR_5_reg                                                           0xB8003034
#define SDE_DDR_ADDR_6_reg                                                           0xB8003038
#define SDE_DDR_ADDR_7_reg                                                           0xB800303C
#define SDE_DDR_ADDR_0_inst_adr                                                      "0x0008"
#define SDE_DDR_ADDR_1_inst_adr                                                      "0x0009"
#define SDE_DDR_ADDR_2_inst_adr                                                      "0x000A"
#define SDE_DDR_ADDR_3_inst_adr                                                      "0x000B"
#define SDE_DDR_ADDR_4_inst_adr                                                      "0x000C"
#define SDE_DDR_ADDR_5_inst_adr                                                      "0x000D"
#define SDE_DDR_ADDR_6_inst_adr                                                      "0x000E"
#define SDE_DDR_ADDR_7_inst_adr                                                      "0x000F"
#define SDE_DDR_ADDR_0_inst                                                          0x0008
#define SDE_DDR_ADDR_1_inst                                                          0x0009
#define SDE_DDR_ADDR_2_inst                                                          0x000A
#define SDE_DDR_ADDR_3_inst                                                          0x000B
#define SDE_DDR_ADDR_4_inst                                                          0x000C
#define SDE_DDR_ADDR_5_inst                                                          0x000D
#define SDE_DDR_ADDR_6_inst                                                          0x000E
#define SDE_DDR_ADDR_7_inst                                                          0x000F
#define SDE_DDR_ADDR_ddr_addr_shift                                                  (0)
#define SDE_DDR_ADDR_ddr_addr_mask                                                   (0x0FFFFFFF)
#define SDE_DDR_ADDR_ddr_addr(data)                                                  (0x0FFFFFFF&((data)<<0))
#define SDE_DDR_ADDR_ddr_addr_src(data)                                              ((0x0FFFFFFF&(data))>>0)


#define SDE_DMA_LEN_0                                                                0x18003040
#define SDE_DMA_LEN_1                                                                0x18003044
#define SDE_DMA_LEN_2                                                                0x18003048
#define SDE_DMA_LEN_3                                                                0x1800304C
#define SDE_DMA_LEN_4                                                                0x18003050
#define SDE_DMA_LEN_5                                                                0x18003054
#define SDE_DMA_LEN_6                                                                0x18003058
#define SDE_DMA_LEN_7                                                                0x1800305C
#define SDE_DMA_LEN_0_reg_addr                                                       "0xB8003040"
#define SDE_DMA_LEN_1_reg_addr                                                       "0xB8003044"
#define SDE_DMA_LEN_2_reg_addr                                                       "0xB8003048"
#define SDE_DMA_LEN_3_reg_addr                                                       "0xB800304C"
#define SDE_DMA_LEN_4_reg_addr                                                       "0xB8003050"
#define SDE_DMA_LEN_5_reg_addr                                                       "0xB8003054"
#define SDE_DMA_LEN_6_reg_addr                                                       "0xB8003058"
#define SDE_DMA_LEN_7_reg_addr                                                       "0xB800305C"
#define SDE_DMA_LEN_0_reg                                                            0xB8003040
#define SDE_DMA_LEN_1_reg                                                            0xB8003044
#define SDE_DMA_LEN_2_reg                                                            0xB8003048
#define SDE_DMA_LEN_3_reg                                                            0xB800304C
#define SDE_DMA_LEN_4_reg                                                            0xB8003050
#define SDE_DMA_LEN_5_reg                                                            0xB8003054
#define SDE_DMA_LEN_6_reg                                                            0xB8003058
#define SDE_DMA_LEN_7_reg                                                            0xB800305C
#define SDE_DMA_LEN_0_inst_adr                                                       "0x0010"
#define SDE_DMA_LEN_1_inst_adr                                                       "0x0011"
#define SDE_DMA_LEN_2_inst_adr                                                       "0x0012"
#define SDE_DMA_LEN_3_inst_adr                                                       "0x0013"
#define SDE_DMA_LEN_4_inst_adr                                                       "0x0014"
#define SDE_DMA_LEN_5_inst_adr                                                       "0x0015"
#define SDE_DMA_LEN_6_inst_adr                                                       "0x0016"
#define SDE_DMA_LEN_7_inst_adr                                                       "0x0017"
#define SDE_DMA_LEN_0_inst                                                           0x0010
#define SDE_DMA_LEN_1_inst                                                           0x0011
#define SDE_DMA_LEN_2_inst                                                           0x0012
#define SDE_DMA_LEN_3_inst                                                           0x0013
#define SDE_DMA_LEN_4_inst                                                           0x0014
#define SDE_DMA_LEN_5_inst                                                           0x0015
#define SDE_DMA_LEN_6_inst                                                           0x0016
#define SDE_DMA_LEN_7_inst                                                           0x0017
#define SDE_DMA_LEN_length_shift                                                     (0)
#define SDE_DMA_LEN_length_mask                                                      (0x00003FFF)
#define SDE_DMA_LEN_length(data)                                                     (0x00003FFF&((data)<<0))
#define SDE_DMA_LEN_length_src(data)                                                 ((0x00003FFF&(data))>>0)


#define SDE_DMA_CTRL_0                                                               0x18003060
#define SDE_DMA_CTRL_1                                                               0x18003064
#define SDE_DMA_CTRL_2                                                               0x18003068
#define SDE_DMA_CTRL_3                                                               0x1800306C
#define SDE_DMA_CTRL_4                                                               0x18003070
#define SDE_DMA_CTRL_5                                                               0x18003074
#define SDE_DMA_CTRL_6                                                               0x18003078
#define SDE_DMA_CTRL_7                                                               0x1800307C
#define SDE_DMA_CTRL_0_reg_addr                                                      "0xB8003060"
#define SDE_DMA_CTRL_1_reg_addr                                                      "0xB8003064"
#define SDE_DMA_CTRL_2_reg_addr                                                      "0xB8003068"
#define SDE_DMA_CTRL_3_reg_addr                                                      "0xB800306C"
#define SDE_DMA_CTRL_4_reg_addr                                                      "0xB8003070"
#define SDE_DMA_CTRL_5_reg_addr                                                      "0xB8003074"
#define SDE_DMA_CTRL_6_reg_addr                                                      "0xB8003078"
#define SDE_DMA_CTRL_7_reg_addr                                                      "0xB800307C"
#define SDE_DMA_CTRL_0_reg                                                           0xB8003060
#define SDE_DMA_CTRL_1_reg                                                           0xB8003064
#define SDE_DMA_CTRL_2_reg                                                           0xB8003068
#define SDE_DMA_CTRL_3_reg                                                           0xB800306C
#define SDE_DMA_CTRL_4_reg                                                           0xB8003070
#define SDE_DMA_CTRL_5_reg                                                           0xB8003074
#define SDE_DMA_CTRL_6_reg                                                           0xB8003078
#define SDE_DMA_CTRL_7_reg                                                           0xB800307C
#define SDE_DMA_CTRL_0_inst_adr                                                      "0x0018"
#define SDE_DMA_CTRL_1_inst_adr                                                      "0x0019"
#define SDE_DMA_CTRL_2_inst_adr                                                      "0x001A"
#define SDE_DMA_CTRL_3_inst_adr                                                      "0x001B"
#define SDE_DMA_CTRL_4_inst_adr                                                      "0x001C"
#define SDE_DMA_CTRL_5_inst_adr                                                      "0x001D"
#define SDE_DMA_CTRL_6_inst_adr                                                      "0x001E"
#define SDE_DMA_CTRL_7_inst_adr                                                      "0x001F"
#define SDE_DMA_CTRL_0_inst                                                          0x0018
#define SDE_DMA_CTRL_1_inst                                                          0x0019
#define SDE_DMA_CTRL_2_inst                                                          0x001A
#define SDE_DMA_CTRL_3_inst                                                          0x001B
#define SDE_DMA_CTRL_4_inst                                                          0x001C
#define SDE_DMA_CTRL_5_inst                                                          0x001D
#define SDE_DMA_CTRL_6_inst                                                          0x001E
#define SDE_DMA_CTRL_7_inst                                                          0x001F
#define SDE_DMA_CTRL_write_enable2_shift                                             (4)
#define SDE_DMA_CTRL_write_enable2_mask                                              (0x00000010)
#define SDE_DMA_CTRL_write_enable2(data)                                             (0x00000010&((data)<<4))
#define SDE_DMA_CTRL_write_enable2_src(data)                                         ((0x00000010&(data))>>4)
#define SDE_DMA_CTRL_stop_shift                                                      (3)
#define SDE_DMA_CTRL_stop_mask                                                       (0x00000008)
#define SDE_DMA_CTRL_stop(data)                                                      (0x00000008&((data)<<3))
#define SDE_DMA_CTRL_stop_src(data)                                                  ((0x00000008&(data))>>3)
#define SDE_DMA_CTRL_write_enable1_shift                                             (2)
#define SDE_DMA_CTRL_write_enable1_mask                                              (0x00000004)
#define SDE_DMA_CTRL_write_enable1(data)                                             (0x00000004&((data)<<2))
#define SDE_DMA_CTRL_write_enable1_src(data)                                         ((0x00000004&(data))>>2)
#define SDE_DMA_CTRL_r_w_shift                                                       (1)
#define SDE_DMA_CTRL_r_w_mask                                                        (0x00000002)
#define SDE_DMA_CTRL_r_w(data)                                                       (0x00000002&((data)<<1))
#define SDE_DMA_CTRL_r_w_src(data)                                                   ((0x00000002&(data))>>1)
#define SDE_DMA_CTRL_go_shift                                                        (0)
#define SDE_DMA_CTRL_go_mask                                                         (0x00000001)
#define SDE_DMA_CTRL_go(data)                                                        (0x00000001&((data)<<0))
#define SDE_DMA_CTRL_go_src(data)                                                    ((0x00000001&(data))>>0)


#define SDE_DMA_DONE                                                                 0x18003080
#define SDE_DMA_DONE_reg_addr                                                        "0xB8003080"
#define SDE_DMA_DONE_reg                                                             0xB8003080
#define SDE_DMA_DONE_inst_adr                                                        "0x0020"
#define SDE_DMA_DONE_inst                                                            0x0020
#define SDE_DMA_DONE_dmem_err_shift                                                  (31)
#define SDE_DMA_DONE_dmem_err_mask                                                   (0x80000000)
#define SDE_DMA_DONE_dmem_err(data)                                                  (0x80000000&((data)<<31))
#define SDE_DMA_DONE_dmem_err_src(data)                                              ((0x80000000&(data))>>31)
#define SDE_DMA_DONE_dma_done_7_shift                                                (9)
#define SDE_DMA_DONE_dma_done_7_mask                                                 (0x00000200)
#define SDE_DMA_DONE_dma_done_7(data)                                                (0x00000200&((data)<<9))
#define SDE_DMA_DONE_dma_done_7_src(data)                                            ((0x00000200&(data))>>9)
#define SDE_DMA_DONE_dma_done_6_shift                                                (8)
#define SDE_DMA_DONE_dma_done_6_mask                                                 (0x00000100)
#define SDE_DMA_DONE_dma_done_6(data)                                                (0x00000100&((data)<<8))
#define SDE_DMA_DONE_dma_done_6_src(data)                                            ((0x00000100&(data))>>8)
#define SDE_DMA_DONE_dma_done_5_shift                                                (7)
#define SDE_DMA_DONE_dma_done_5_mask                                                 (0x00000080)
#define SDE_DMA_DONE_dma_done_5(data)                                                (0x00000080&((data)<<7))
#define SDE_DMA_DONE_dma_done_5_src(data)                                            ((0x00000080&(data))>>7)
#define SDE_DMA_DONE_dma_done_4_shift                                                (6)
#define SDE_DMA_DONE_dma_done_4_mask                                                 (0x00000040)
#define SDE_DMA_DONE_dma_done_4(data)                                                (0x00000040&((data)<<6))
#define SDE_DMA_DONE_dma_done_4_src(data)                                            ((0x00000040&(data))>>6)
#define SDE_DMA_DONE_dma_done_3_shift                                                (5)
#define SDE_DMA_DONE_dma_done_3_mask                                                 (0x00000020)
#define SDE_DMA_DONE_dma_done_3(data)                                                (0x00000020&((data)<<5))
#define SDE_DMA_DONE_dma_done_3_src(data)                                            ((0x00000020&(data))>>5)
#define SDE_DMA_DONE_dma_done_2_shift                                                (4)
#define SDE_DMA_DONE_dma_done_2_mask                                                 (0x00000010)
#define SDE_DMA_DONE_dma_done_2(data)                                                (0x00000010&((data)<<4))
#define SDE_DMA_DONE_dma_done_2_src(data)                                            ((0x00000010&(data))>>4)
#define SDE_DMA_DONE_dma_done_1_shift                                                (3)
#define SDE_DMA_DONE_dma_done_1_mask                                                 (0x00000008)
#define SDE_DMA_DONE_dma_done_1(data)                                                (0x00000008&((data)<<3))
#define SDE_DMA_DONE_dma_done_1_src(data)                                            ((0x00000008&(data))>>3)
#define SDE_DMA_DONE_dma_done_0_shift                                                (2)
#define SDE_DMA_DONE_dma_done_0_mask                                                 (0x00000004)
#define SDE_DMA_DONE_dma_done_0(data)                                                (0x00000004&((data)<<2))
#define SDE_DMA_DONE_dma_done_0_src(data)                                            ((0x00000004&(data))>>2)
#define SDE_DMA_DONE_dma_all_done_shift                                              (1)
#define SDE_DMA_DONE_dma_all_done_mask                                               (0x00000002)
#define SDE_DMA_DONE_dma_all_done(data)                                              (0x00000002&((data)<<1))
#define SDE_DMA_DONE_dma_all_done_src(data)                                          ((0x00000002&(data))>>1)
#define SDE_DMA_DONE_write_data_shift                                                (0)
#define SDE_DMA_DONE_write_data_mask                                                 (0x00000001)
#define SDE_DMA_DONE_write_data(data)                                                (0x00000001&((data)<<0))
#define SDE_DMA_DONE_write_data_src(data)                                            ((0x00000001&(data))>>0)


#define SDE_DMA_DONE_EN                                                              0x18003084
#define SDE_DMA_DONE_EN_reg_addr                                                     "0xB8003084"
#define SDE_DMA_DONE_EN_reg                                                          0xB8003084
#define SDE_DMA_DONE_EN_inst_adr                                                     "0x0021"
#define SDE_DMA_DONE_EN_inst                                                         0x0021
#define SDE_DMA_DONE_EN_dmem_err_int_en_shift                                        (31)
#define SDE_DMA_DONE_EN_dmem_err_int_en_mask                                         (0x80000000)
#define SDE_DMA_DONE_EN_dmem_err_int_en(data)                                        (0x80000000&((data)<<31))
#define SDE_DMA_DONE_EN_dmem_err_int_en_src(data)                                    ((0x80000000&(data))>>31)
#define SDE_DMA_DONE_EN_dma_done_7_en_shift                                          (9)
#define SDE_DMA_DONE_EN_dma_done_7_en_mask                                           (0x00000200)
#define SDE_DMA_DONE_EN_dma_done_7_en(data)                                          (0x00000200&((data)<<9))
#define SDE_DMA_DONE_EN_dma_done_7_en_src(data)                                      ((0x00000200&(data))>>9)
#define SDE_DMA_DONE_EN_dma_done_6_en_shift                                          (8)
#define SDE_DMA_DONE_EN_dma_done_6_en_mask                                           (0x00000100)
#define SDE_DMA_DONE_EN_dma_done_6_en(data)                                          (0x00000100&((data)<<8))
#define SDE_DMA_DONE_EN_dma_done_6_en_src(data)                                      ((0x00000100&(data))>>8)
#define SDE_DMA_DONE_EN_dma_done_5_en_shift                                          (7)
#define SDE_DMA_DONE_EN_dma_done_5_en_mask                                           (0x00000080)
#define SDE_DMA_DONE_EN_dma_done_5_en(data)                                          (0x00000080&((data)<<7))
#define SDE_DMA_DONE_EN_dma_done_5_en_src(data)                                      ((0x00000080&(data))>>7)
#define SDE_DMA_DONE_EN_dma_done_4_en_shift                                          (6)
#define SDE_DMA_DONE_EN_dma_done_4_en_mask                                           (0x00000040)
#define SDE_DMA_DONE_EN_dma_done_4_en(data)                                          (0x00000040&((data)<<6))
#define SDE_DMA_DONE_EN_dma_done_4_en_src(data)                                      ((0x00000040&(data))>>6)
#define SDE_DMA_DONE_EN_dma_done_3_en_shift                                          (5)
#define SDE_DMA_DONE_EN_dma_done_3_en_mask                                           (0x00000020)
#define SDE_DMA_DONE_EN_dma_done_3_en(data)                                          (0x00000020&((data)<<5))
#define SDE_DMA_DONE_EN_dma_done_3_en_src(data)                                      ((0x00000020&(data))>>5)
#define SDE_DMA_DONE_EN_dma_done_2_en_shift                                          (4)
#define SDE_DMA_DONE_EN_dma_done_2_en_mask                                           (0x00000010)
#define SDE_DMA_DONE_EN_dma_done_2_en(data)                                          (0x00000010&((data)<<4))
#define SDE_DMA_DONE_EN_dma_done_2_en_src(data)                                      ((0x00000010&(data))>>4)
#define SDE_DMA_DONE_EN_dma_done_1_en_shift                                          (3)
#define SDE_DMA_DONE_EN_dma_done_1_en_mask                                           (0x00000008)
#define SDE_DMA_DONE_EN_dma_done_1_en(data)                                          (0x00000008&((data)<<3))
#define SDE_DMA_DONE_EN_dma_done_1_en_src(data)                                      ((0x00000008&(data))>>3)
#define SDE_DMA_DONE_EN_dma_done_0_en_shift                                          (2)
#define SDE_DMA_DONE_EN_dma_done_0_en_mask                                           (0x00000004)
#define SDE_DMA_DONE_EN_dma_done_0_en(data)                                          (0x00000004&((data)<<2))
#define SDE_DMA_DONE_EN_dma_done_0_en_src(data)                                      ((0x00000004&(data))>>2)
#define SDE_DMA_DONE_EN_dma_all_done_en_shift                                        (1)
#define SDE_DMA_DONE_EN_dma_all_done_en_mask                                         (0x00000002)
#define SDE_DMA_DONE_EN_dma_all_done_en(data)                                        (0x00000002&((data)<<1))
#define SDE_DMA_DONE_EN_dma_all_done_en_src(data)                                    ((0x00000002&(data))>>1)
#define SDE_DMA_DONE_EN_write_data_shift                                             (0)
#define SDE_DMA_DONE_EN_write_data_mask                                              (0x00000001)
#define SDE_DMA_DONE_EN_write_data(data)                                             (0x00000001&((data)<<0))
#define SDE_DMA_DONE_EN_write_data_src(data)                                         ((0x00000001&(data))>>0)


#define SDE_DUMMY                                                                    0x18003090
#define SDE_DUMMY_reg_addr                                                           "0xB8003090"
#define SDE_DUMMY_reg                                                                0xB8003090
#define SDE_DUMMY_inst_adr                                                           "0x0024"
#define SDE_DUMMY_inst                                                               0x0024
#define SDE_DUMMY_data_shift                                                         (0)
#define SDE_DUMMY_data_mask                                                          (0xFFFFFFFF)
#define SDE_DUMMY_data(data)                                                         (0xFFFFFFFF&((data)<<0))
#define SDE_DUMMY_data_src(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define SDE_DBG                                                                      0x180030A0
#define SDE_DBG_reg_addr                                                             "0xB80030A0"
#define SDE_DBG_reg                                                                  0xB80030A0
#define SDE_DBG_inst_adr                                                             "0x0028"
#define SDE_DBG_inst                                                                 0x0028
#define SDE_DBG_write_enable3_shift                                                  (13)
#define SDE_DBG_write_enable3_mask                                                   (0x00002000)
#define SDE_DBG_write_enable3(data)                                                  (0x00002000&((data)<<13))
#define SDE_DBG_write_enable3_src(data)                                              ((0x00002000&(data))>>13)
#define SDE_DBG_sel1_shift                                                           (8)
#define SDE_DBG_sel1_mask                                                            (0x00001F00)
#define SDE_DBG_sel1(data)                                                           (0x00001F00&((data)<<8))
#define SDE_DBG_sel1_src(data)                                                       ((0x00001F00&(data))>>8)
#define SDE_DBG_write_enable2_shift                                                  (7)
#define SDE_DBG_write_enable2_mask                                                   (0x00000080)
#define SDE_DBG_write_enable2(data)                                                  (0x00000080&((data)<<7))
#define SDE_DBG_write_enable2_src(data)                                              ((0x00000080&(data))>>7)
#define SDE_DBG_sel0_shift                                                           (2)
#define SDE_DBG_sel0_mask                                                            (0x0000007C)
#define SDE_DBG_sel0(data)                                                           (0x0000007C&((data)<<2))
#define SDE_DBG_sel0_src(data)                                                       ((0x0000007C&(data))>>2)
#define SDE_DBG_write_enable1_shift                                                  (1)
#define SDE_DBG_write_enable1_mask                                                   (0x00000002)
#define SDE_DBG_write_enable1(data)                                                  (0x00000002&((data)<<1))
#define SDE_DBG_write_enable1_src(data)                                              ((0x00000002&(data))>>1)
#define SDE_DBG_enable_shift                                                         (0)
#define SDE_DBG_enable_mask                                                          (0x00000001)
#define SDE_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define SDE_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)


#endif
