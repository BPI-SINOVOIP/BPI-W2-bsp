// This file is generated using the spec version 2.0, firmware template version 1.39and DVR_Parser_0.46
#ifndef _SATA0_REG_H_INCLUDED_
#define _SATA0_REG_H_INCLUDED_

//#define  _SATA0_USE_STRUCT
#ifdef _SATA0_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data:16;
}sata0_CDR0;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata0_CDR1;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata0_CDR2;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata0_CDR3;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata0_CDR4;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata0_CDR5;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata0_CDR6;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata0_CDR7;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata0_CLR0;

typedef struct
{
    unsigned int    sstatus:32;
}sata0_SCR0;

typedef struct
{
    unsigned int    serror:32;
}sata0_SCR1;

typedef struct
{
    unsigned int    scontrol:32;
}sata0_SCR2;

typedef struct
{
    unsigned int    sactive:32;
}sata0_SCR3;

typedef struct
{
    unsigned int    snotification:32;
}sata0_SCR4;

typedef struct
{
    unsigned int    reserved_0:32;
}sata0_SCR5;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    reg_mode:1;
    unsigned int    prd_num:8;
    unsigned int    reserved_1:1;
    unsigned int    cpen:1;
    unsigned int    srst:1;
    unsigned int    self_test:1;
    unsigned int    write:1;
    unsigned int    reserved_2:2;
    unsigned int    go:1;
}sata0_DMACTRL;

typedef struct
{
    unsigned int    prd_ptr:30;
    unsigned int    reserved_0:2;
}sata0_PRDPTR;

typedef struct
{
    unsigned int    prd_pba:30;
    unsigned int    reserved_0:2;
}sata0_PRDEty0;

typedef struct
{
    unsigned int    eot:1;
    unsigned int    reserved_0:7;
    unsigned int    prd_bycnt:22;
    unsigned int    reserved_1:2;
}sata0_PRDEty1;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    intrq_en:1;
}sata0_enable;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    bridge_rlevel:4;
    unsigned int    bridge_wlevel:4;
    unsigned int    dma_flevel:4;
    unsigned int    reserved_1:5;
    unsigned int    cmd_swap:2;
    unsigned int    data_swap:1;
}sata0_DMAMisc;

typedef struct
{
    unsigned int    data:16;
    unsigned int    phy_adr:3;
    unsigned int    reg_adr:5;
    unsigned int    reserved_0:1;
    unsigned int    mdio_st:2;
    unsigned int    mdio_rdy:1;
    unsigned int    mclk_rate:2;
    unsigned int    mdio_srst:1;
    unsigned int    mdio_rdwr:1;
}sata0_MDIOCtrl;

typedef struct
{
    unsigned int    crc:32;
}sata0_DMACrc;

typedef struct
{
    unsigned int    req_cnt:16;
    unsigned int    reserved_0:3;
    unsigned int    req_cnt_en:1;
    unsigned int    reserved_1:2;
    unsigned int    tx_data_vld:1;
    unsigned int    rx_enable:1;
    unsigned int    tx_enable:1;
    unsigned int    reset_n:1;
    unsigned int    slumber:1;
    unsigned int    partial:1;
    unsigned int    farafelb:1;
    unsigned int    nearafelb:1;
    unsigned int    spdsel:1;
    unsigned int    enable:1;
}sata0_pinout;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    timeout_flg:1;
    unsigned int    reserved_1:11;
    unsigned int    timeout_en:1;
    unsigned int    timeout_cnt:16;
}sata0_timeout;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable4:1;
    unsigned int    test_key:16;
    unsigned int    reserved_1:2;
    unsigned int    write_enable3:1;
    unsigned int    sel1:3;
    unsigned int    write_enable2:1;
    unsigned int    sel0:3;
    unsigned int    write_enable1:1;
    unsigned int    enable:1;
}sata0_dbg;
#endif

#define SATA0_CDR0                                                    0x18012B00
#define SATA0_CDR0_reg_addr                                           "0xB8012B00"
#define SATA0_CDR0_reg                                                0xB8012B00
#define SATA0_CDR0_inst_addr                                          "0x02C0"
#define SATA0_CDR0_inst                                               0x02C0
#define SATA0_CDR0_data_shift                                         (0)
#define SATA0_CDR0_data_mask                                          (0x0000FFFF)
#define SATA0_CDR0_data(data)                                         (0x0000FFFF&(data))
#define SATA0_CDR0_get_data(data)                                     (0x0000FFFF&(data))

#define SATA0_CDR1                                                    0x18012B04
#define SATA0_CDR1_reg_addr                                           "0xB8012B04"
#define SATA0_CDR1_reg                                                0xB8012B04
#define SATA0_CDR1_inst_addr                                          "0x02C1"
#define SATA0_CDR1_inst                                               0x02C1
#define SATA0_CDR1_data_p_shift                                       (8)
#define SATA0_CDR1_data_shift                                         (0)
#define SATA0_CDR1_data_p_mask                                        (0x0000FF00)
#define SATA0_CDR1_data_mask                                          (0x000000FF)
#define SATA0_CDR1_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA0_CDR1_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR1_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA0_CDR1_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR2                                                    0x18012B08
#define SATA0_CDR2_reg_addr                                           "0xB8012B08"
#define SATA0_CDR2_reg                                                0xB8012B08
#define SATA0_CDR2_inst_addr                                          "0x02C2"
#define SATA0_CDR2_inst                                               0x02C2
#define SATA0_CDR2_data_p_shift                                       (8)
#define SATA0_CDR2_data_shift                                         (0)
#define SATA0_CDR2_data_p_mask                                        (0x0000FF00)
#define SATA0_CDR2_data_mask                                          (0x000000FF)
#define SATA0_CDR2_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA0_CDR2_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR2_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA0_CDR2_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR3                                                    0x18012B0C
#define SATA0_CDR3_reg_addr                                           "0xB8012B0C"
#define SATA0_CDR3_reg                                                0xB8012B0C
#define SATA0_CDR3_inst_addr                                          "0x02C3"
#define SATA0_CDR3_inst                                               0x02C3
#define SATA0_CDR3_data_p_shift                                       (8)
#define SATA0_CDR3_data_shift                                         (0)
#define SATA0_CDR3_data_p_mask                                        (0x0000FF00)
#define SATA0_CDR3_data_mask                                          (0x000000FF)
#define SATA0_CDR3_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA0_CDR3_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR3_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA0_CDR3_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR4                                                    0x18012B10
#define SATA0_CDR4_reg_addr                                           "0xB8012B10"
#define SATA0_CDR4_reg                                                0xB8012B10
#define SATA0_CDR4_inst_addr                                          "0x02C4"
#define SATA0_CDR4_inst                                               0x02C4
#define SATA0_CDR4_data_p_shift                                       (8)
#define SATA0_CDR4_data_shift                                         (0)
#define SATA0_CDR4_data_p_mask                                        (0x0000FF00)
#define SATA0_CDR4_data_mask                                          (0x000000FF)
#define SATA0_CDR4_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA0_CDR4_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR4_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA0_CDR4_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR5                                                    0x18012B14
#define SATA0_CDR5_reg_addr                                           "0xB8012B14"
#define SATA0_CDR5_reg                                                0xB8012B14
#define SATA0_CDR5_inst_addr                                          "0x02C5"
#define SATA0_CDR5_inst                                               0x02C5
#define SATA0_CDR5_data_p_shift                                       (8)
#define SATA0_CDR5_data_shift                                         (0)
#define SATA0_CDR5_data_p_mask                                        (0x0000FF00)
#define SATA0_CDR5_data_mask                                          (0x000000FF)
#define SATA0_CDR5_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA0_CDR5_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR5_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA0_CDR5_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR6                                                    0x18012B18
#define SATA0_CDR6_reg_addr                                           "0xB8012B18"
#define SATA0_CDR6_reg                                                0xB8012B18
#define SATA0_CDR6_inst_addr                                          "0x02C6"
#define SATA0_CDR6_inst                                               0x02C6
#define SATA0_CDR6_data_shift                                         (0)
#define SATA0_CDR6_data_mask                                          (0x000000FF)
#define SATA0_CDR6_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR6_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CDR7                                                    0x18012B1C
#define SATA0_CDR7_reg_addr                                           "0xB8012B1C"
#define SATA0_CDR7_reg                                                0xB8012B1C
#define SATA0_CDR7_inst_addr                                          "0x02C7"
#define SATA0_CDR7_inst                                               0x02C7
#define SATA0_CDR7_data_shift                                         (0)
#define SATA0_CDR7_data_mask                                          (0x000000FF)
#define SATA0_CDR7_data(data)                                         (0x000000FF&(data))
#define SATA0_CDR7_get_data(data)                                     (0x000000FF&(data))

#define SATA0_CLR0                                                    0x18012B20
#define SATA0_CLR0_reg_addr                                           "0xB8012B20"
#define SATA0_CLR0_reg                                                0xB8012B20
#define SATA0_CLR0_inst_addr                                          "0x02C8"
#define SATA0_CLR0_inst                                               0x02C8
#define SATA0_CLR0_data_shift                                         (0)
#define SATA0_CLR0_data_mask                                          (0x000000FF)
#define SATA0_CLR0_data(data)                                         (0x000000FF&(data))
#define SATA0_CLR0_get_data(data)                                     (0x000000FF&(data))

#define SATA0_SCR0                                                    0x18012B24
#define SATA0_SCR0_reg_addr                                           "0xB8012B24"
#define SATA0_SCR0_reg                                                0xB8012B24
#define SATA0_SCR0_inst_addr                                          "0x02C9"
#define SATA0_SCR0_inst                                               0x02C9
#define SATA0_SCR0_sstatus_shift                                      (0)
#define SATA0_SCR0_sstatus_mask                                       (0xFFFFFFFF)
#define SATA0_SCR0_sstatus(data)                                      (0xFFFFFFFF&(data))
#define SATA0_SCR0_get_sstatus(data)                                  (0xFFFFFFFF&(data))

#define SATA0_SCR1                                                    0x18012B28
#define SATA0_SCR1_reg_addr                                           "0xB8012B28"
#define SATA0_SCR1_reg                                                0xB8012B28
#define SATA0_SCR1_inst_addr                                          "0x02CA"
#define SATA0_SCR1_inst                                               0x02CA
#define SATA0_SCR1_serror_shift                                       (0)
#define SATA0_SCR1_serror_mask                                        (0xFFFFFFFF)
#define SATA0_SCR1_serror(data)                                       (0xFFFFFFFF&(data))
#define SATA0_SCR1_get_serror(data)                                   (0xFFFFFFFF&(data))

#define SATA0_SCR2                                                    0x18012B2C
#define SATA0_SCR2_reg_addr                                           "0xB8012B2C"
#define SATA0_SCR2_reg                                                0xB8012B2C
#define SATA0_SCR2_inst_addr                                          "0x02CB"
#define SATA0_SCR2_inst                                               0x02CB
#define SATA0_SCR2_scontrol_shift                                     (0)
#define SATA0_SCR2_scontrol_mask                                      (0xFFFFFFFF)
#define SATA0_SCR2_scontrol(data)                                     (0xFFFFFFFF&(data))
#define SATA0_SCR2_get_scontrol(data)                                 (0xFFFFFFFF&(data))

#define SATA0_SCR3                                                    0x18012B30
#define SATA0_SCR3_reg_addr                                           "0xB8012B30"
#define SATA0_SCR3_reg                                                0xB8012B30
#define SATA0_SCR3_inst_addr                                          "0x02CC"
#define SATA0_SCR3_inst                                               0x02CC
#define SATA0_SCR3_sactive_shift                                      (0)
#define SATA0_SCR3_sactive_mask                                       (0xFFFFFFFF)
#define SATA0_SCR3_sactive(data)                                      (0xFFFFFFFF&(data))
#define SATA0_SCR3_get_sactive(data)                                  (0xFFFFFFFF&(data))

#define SATA0_SCR4                                                    0x18012B34
#define SATA0_SCR4_reg_addr                                           "0xB8012B34"
#define SATA0_SCR4_reg                                                0xB8012B34
#define SATA0_SCR4_inst_addr                                          "0x02CD"
#define SATA0_SCR4_inst                                               0x02CD
#define SATA0_SCR4_snotification_shift                                (0)
#define SATA0_SCR4_snotification_mask                                 (0xFFFFFFFF)
#define SATA0_SCR4_snotification(data)                                (0xFFFFFFFF&(data))
#define SATA0_SCR4_get_snotification(data)                            (0xFFFFFFFF&(data))

#define SATA0_SCR5                                                    0x18012B38
#define SATA0_SCR5_reg_addr                                           "0xB8012B38"
#define SATA0_SCR5_reg                                                0xB8012B38
#define SATA0_SCR5_inst_addr                                          "0x02CE"
#define SATA0_SCR5_inst                                               0x02CE

#define SATA0_DMACTRL                                                 0x18012BD0
#define SATA0_DMACTRL_reg_addr                                        "0xB8012BD0"
#define SATA0_DMACTRL_reg                                             0xB8012BD0
#define SATA0_DMACTRL_inst_addr                                       "0x02F4"
#define SATA0_DMACTRL_inst                                            0x02F4
#define SATA0_DMACTRL_reg_mode_shift                                  (16)
#define SATA0_DMACTRL_prd_num_shift                                   (8)
#define SATA0_DMACTRL_cpen_shift                                      (6)
#define SATA0_DMACTRL_srst_shift                                      (5)
#define SATA0_DMACTRL_self_test_shift                                 (4)
#define SATA0_DMACTRL_write_shift                                     (3)
#define SATA0_DMACTRL_go_shift                                        (0)
#define SATA0_DMACTRL_reg_mode_mask                                   (0x00010000)
#define SATA0_DMACTRL_prd_num_mask                                    (0x0000FF00)
#define SATA0_DMACTRL_cpen_mask                                       (0x00000040)
#define SATA0_DMACTRL_srst_mask                                       (0x00000020)
#define SATA0_DMACTRL_self_test_mask                                  (0x00000010)
#define SATA0_DMACTRL_write_mask                                      (0x00000008)
#define SATA0_DMACTRL_go_mask                                         (0x00000001)
#define SATA0_DMACTRL_reg_mode(data)                                  (0x00010000&((data)<<16))
#define SATA0_DMACTRL_prd_num(data)                                   (0x0000FF00&((data)<<8))
#define SATA0_DMACTRL_cpen(data)                                      (0x00000040&((data)<<6))
#define SATA0_DMACTRL_srst(data)                                      (0x00000020&((data)<<5))
#define SATA0_DMACTRL_self_test(data)                                 (0x00000010&((data)<<4))
#define SATA0_DMACTRL_write(data)                                     (0x00000008&((data)<<3))
#define SATA0_DMACTRL_go(data)                                        (0x00000001&(data))
#define SATA0_DMACTRL_get_reg_mode(data)                              ((0x00010000&(data))>>16)
#define SATA0_DMACTRL_get_prd_num(data)                               ((0x0000FF00&(data))>>8)
#define SATA0_DMACTRL_get_cpen(data)                                  ((0x00000040&(data))>>6)
#define SATA0_DMACTRL_get_srst(data)                                  ((0x00000020&(data))>>5)
#define SATA0_DMACTRL_get_self_test(data)                             ((0x00000010&(data))>>4)
#define SATA0_DMACTRL_get_write(data)                                 ((0x00000008&(data))>>3)
#define SATA0_DMACTRL_get_go(data)                                    (0x00000001&(data))

#define SATA0_PRDPTR                                                  0x18012BD4
#define SATA0_PRDPTR_reg_addr                                         "0xB8012BD4"
#define SATA0_PRDPTR_reg                                              0xB8012BD4
#define SATA0_PRDPTR_inst_addr                                        "0x02F5"
#define SATA0_PRDPTR_inst                                             0x02F5
#define SATA0_PRDPTR_prd_ptr_shift                                    (2)
#define SATA0_PRDPTR_prd_ptr_mask                                     (0xFFFFFFFC)
#define SATA0_PRDPTR_prd_ptr(data)                                    (0xFFFFFFFC&((data)<<2))
#define SATA0_PRDPTR_get_prd_ptr(data)                                ((0xFFFFFFFC&(data))>>2)

#define SATA0_PRDEty0                                                 0x18012BD8
#define SATA0_PRDEty0_reg_addr                                        "0xB8012BD8"
#define SATA0_PRDEty0_reg                                             0xB8012BD8
#define SATA0_PRDEty0_inst_addr                                       "0x02F6"
#define SATA0_PRDEty0_inst                                            0x02F6
#define SATA0_PRDEty0_prd_pba_shift                                   (2)
#define SATA0_PRDEty0_prd_pba_mask                                    (0xFFFFFFFC)
#define SATA0_PRDEty0_prd_pba(data)                                   (0xFFFFFFFC&((data)<<2))
#define SATA0_PRDEty0_get_prd_pba(data)                               ((0xFFFFFFFC&(data))>>2)

#define SATA0_PRDEty1                                                 0x18012BDC
#define SATA0_PRDEty1_reg_addr                                        "0xB8012BDC"
#define SATA0_PRDEty1_reg                                             0xB8012BDC
#define SATA0_PRDEty1_inst_addr                                       "0x02F7"
#define SATA0_PRDEty1_inst                                            0x02F7
#define SATA0_PRDEty1_eot_shift                                       (31)
#define SATA0_PRDEty1_prd_bycnt_shift                                 (2)
#define SATA0_PRDEty1_eot_mask                                        (0x80000000)
#define SATA0_PRDEty1_prd_bycnt_mask                                  (0x00FFFFFC)
#define SATA0_PRDEty1_eot(data)                                       (0x80000000&((data)<<31))
#define SATA0_PRDEty1_prd_bycnt(data)                                 (0x00FFFFFC&((data)<<2))
#define SATA0_PRDEty1_get_eot(data)                                   ((0x80000000&(data))>>31)
#define SATA0_PRDEty1_get_prd_bycnt(data)                             ((0x00FFFFFC&(data))>>2)

#define SATA0_enable                                                  0x18012BE0
#define SATA0_enable_reg_addr                                         "0xB8012BE0"
#define SATA0_enable_reg                                              0xB8012BE0
#define SATA0_enable_inst_addr                                        "0x02F8"
#define SATA0_enable_inst                                             0x02F8
#define SATA0_enable_intrq_en_shift                                   (0)
#define SATA0_enable_intrq_en_mask                                    (0x00000001)
#define SATA0_enable_intrq_en(data)                                   (0x00000001&(data))
#define SATA0_enable_get_intrq_en(data)                               (0x00000001&(data))

#define SATA0_DMAMisc                                                 0x18012BE4
#define SATA0_DMAMisc_reg_addr                                        "0xB8012BE4"
#define SATA0_DMAMisc_reg                                             0xB8012BE4
#define SATA0_DMAMisc_inst_addr                                       "0x02F9"
#define SATA0_DMAMisc_inst                                            0x02F9
#define SATA0_DMAMisc_bridge_rlevel_shift                             (16)
#define SATA0_DMAMisc_bridge_wlevel_shift                             (12)
#define SATA0_DMAMisc_dma_flevel_shift                                (8)
#define SATA0_DMAMisc_cmd_swap_shift                                  (1)
#define SATA0_DMAMisc_data_swap_shift                                 (0)
#define SATA0_DMAMisc_bridge_rlevel_mask                              (0x000F0000)
#define SATA0_DMAMisc_bridge_wlevel_mask                              (0x0000F000)
#define SATA0_DMAMisc_dma_flevel_mask                                 (0x00000F00)
#define SATA0_DMAMisc_cmd_swap_mask                                   (0x00000006)
#define SATA0_DMAMisc_data_swap_mask                                  (0x00000001)
#define SATA0_DMAMisc_bridge_rlevel(data)                             (0x000F0000&((data)<<16))
#define SATA0_DMAMisc_bridge_wlevel(data)                             (0x0000F000&((data)<<12))
#define SATA0_DMAMisc_dma_flevel(data)                                (0x00000F00&((data)<<8))
#define SATA0_DMAMisc_cmd_swap(data)                                  (0x00000006&((data)<<1))
#define SATA0_DMAMisc_data_swap(data)                                 (0x00000001&(data))
#define SATA0_DMAMisc_get_bridge_rlevel(data)                         ((0x000F0000&(data))>>16)
#define SATA0_DMAMisc_get_bridge_wlevel(data)                         ((0x0000F000&(data))>>12)
#define SATA0_DMAMisc_get_dma_flevel(data)                            ((0x00000F00&(data))>>8)
#define SATA0_DMAMisc_get_cmd_swap(data)                              ((0x00000006&(data))>>1)
#define SATA0_DMAMisc_get_data_swap(data)                             (0x00000001&(data))

#define SATA0_MDIOCtrl                                                0x18012BE8
#define SATA0_MDIOCtrl_reg_addr                                       "0xB8012BE8"
#define SATA0_MDIOCtrl_reg                                            0xB8012BE8
#define SATA0_MDIOCtrl_inst_addr                                      "0x02FA"
#define SATA0_MDIOCtrl_inst                                           0x02FA
#define SATA0_MDIOCtrl_data_shift                                     (16)
#define SATA0_MDIOCtrl_phy_adr_shift                                  (13)
#define SATA0_MDIOCtrl_reg_adr_shift                                  (8)
#define SATA0_MDIOCtrl_mdio_st_shift                                  (5)
#define SATA0_MDIOCtrl_mdio_rdy_shift                                 (4)
#define SATA0_MDIOCtrl_mclk_rate_shift                                (2)
#define SATA0_MDIOCtrl_mdio_srst_shift                                (1)
#define SATA0_MDIOCtrl_mdio_rdwr_shift                                (0)
#define SATA0_MDIOCtrl_data_mask                                      (0xFFFF0000)
#define SATA0_MDIOCtrl_phy_adr_mask                                   (0x0000E000)
#define SATA0_MDIOCtrl_reg_adr_mask                                   (0x00001F00)
#define SATA0_MDIOCtrl_mdio_st_mask                                   (0x00000060)
#define SATA0_MDIOCtrl_mdio_rdy_mask                                  (0x00000010)
#define SATA0_MDIOCtrl_mclk_rate_mask                                 (0x0000000C)
#define SATA0_MDIOCtrl_mdio_srst_mask                                 (0x00000002)
#define SATA0_MDIOCtrl_mdio_rdwr_mask                                 (0x00000001)
#define SATA0_MDIOCtrl_data(data)                                     (0xFFFF0000&((data)<<16))
#define SATA0_MDIOCtrl_phy_adr(data)                                  (0x0000E000&((data)<<13))
#define SATA0_MDIOCtrl_reg_adr(data)                                  (0x00001F00&((data)<<8))
#define SATA0_MDIOCtrl_mdio_st(data)                                  (0x00000060&((data)<<5))
#define SATA0_MDIOCtrl_mdio_rdy(data)                                 (0x00000010&((data)<<4))
#define SATA0_MDIOCtrl_mclk_rate(data)                                (0x0000000C&((data)<<2))
#define SATA0_MDIOCtrl_mdio_srst(data)                                (0x00000002&((data)<<1))
#define SATA0_MDIOCtrl_mdio_rdwr(data)                                (0x00000001&(data))
#define SATA0_MDIOCtrl_get_data(data)                                 ((0xFFFF0000&(data))>>16)
#define SATA0_MDIOCtrl_get_phy_adr(data)                              ((0x0000E000&(data))>>13)
#define SATA0_MDIOCtrl_get_reg_adr(data)                              ((0x00001F00&(data))>>8)
#define SATA0_MDIOCtrl_get_mdio_st(data)                              ((0x00000060&(data))>>5)
#define SATA0_MDIOCtrl_get_mdio_rdy(data)                             ((0x00000010&(data))>>4)
#define SATA0_MDIOCtrl_get_mclk_rate(data)                            ((0x0000000C&(data))>>2)
#define SATA0_MDIOCtrl_get_mdio_srst(data)                            ((0x00000002&(data))>>1)
#define SATA0_MDIOCtrl_get_mdio_rdwr(data)                            (0x00000001&(data))

#define SATA0_DMACrc                                                  0x18012BEC
#define SATA0_DMACrc_reg_addr                                         "0xB8012BEC"
#define SATA0_DMACrc_reg                                              0xB8012BEC
#define SATA0_DMACrc_inst_addr                                        "0x02FB"
#define SATA0_DMACrc_inst                                             0x02FB
#define SATA0_DMACrc_crc_shift                                        (0)
#define SATA0_DMACrc_crc_mask                                         (0xFFFFFFFF)
#define SATA0_DMACrc_crc(data)                                        (0xFFFFFFFF&(data))
#define SATA0_DMACrc_get_crc(data)                                    (0xFFFFFFFF&(data))

#define SATA0_pinout                                                  0x18012BF0
#define SATA0_pinout_reg_addr                                         "0xB8012BF0"
#define SATA0_pinout_reg                                              0xB8012BF0
#define SATA0_pinout_inst_addr                                        "0x02FC"
#define SATA0_pinout_inst                                             0x02FC
#define SATA0_pinout_req_cnt_shift                                    (16)
#define SATA0_pinout_req_cnt_en_shift                                 (12)
#define SATA0_pinout_tx_data_vld_shift                                (9)
#define SATA0_pinout_rx_enable_shift                                  (8)
#define SATA0_pinout_tx_enable_shift                                  (7)
#define SATA0_pinout_reset_n_shift                                    (6)
#define SATA0_pinout_slumber_shift                                    (5)
#define SATA0_pinout_partial_shift                                    (4)
#define SATA0_pinout_farafelb_shift                                   (3)
#define SATA0_pinout_nearafelb_shift                                  (2)
#define SATA0_pinout_spdsel_shift                                     (1)
#define SATA0_pinout_enable_shift                                     (0)
#define SATA0_pinout_req_cnt_mask                                     (0xFFFF0000)
#define SATA0_pinout_req_cnt_en_mask                                  (0x00001000)
#define SATA0_pinout_tx_data_vld_mask                                 (0x00000200)
#define SATA0_pinout_rx_enable_mask                                   (0x00000100)
#define SATA0_pinout_tx_enable_mask                                   (0x00000080)
#define SATA0_pinout_reset_n_mask                                     (0x00000040)
#define SATA0_pinout_slumber_mask                                     (0x00000020)
#define SATA0_pinout_partial_mask                                     (0x00000010)
#define SATA0_pinout_farafelb_mask                                    (0x00000008)
#define SATA0_pinout_nearafelb_mask                                   (0x00000004)
#define SATA0_pinout_spdsel_mask                                      (0x00000002)
#define SATA0_pinout_enable_mask                                      (0x00000001)
#define SATA0_pinout_req_cnt(data)                                    (0xFFFF0000&((data)<<16))
#define SATA0_pinout_req_cnt_en(data)                                 (0x00001000&((data)<<12))
#define SATA0_pinout_tx_data_vld(data)                                (0x00000200&((data)<<9))
#define SATA0_pinout_rx_enable(data)                                  (0x00000100&((data)<<8))
#define SATA0_pinout_tx_enable(data)                                  (0x00000080&((data)<<7))
#define SATA0_pinout_reset_n(data)                                    (0x00000040&((data)<<6))
#define SATA0_pinout_slumber(data)                                    (0x00000020&((data)<<5))
#define SATA0_pinout_partial(data)                                    (0x00000010&((data)<<4))
#define SATA0_pinout_farafelb(data)                                   (0x00000008&((data)<<3))
#define SATA0_pinout_nearafelb(data)                                  (0x00000004&((data)<<2))
#define SATA0_pinout_spdsel(data)                                     (0x00000002&((data)<<1))
#define SATA0_pinout_enable(data)                                     (0x00000001&(data))
#define SATA0_pinout_get_req_cnt(data)                                ((0xFFFF0000&(data))>>16)
#define SATA0_pinout_get_req_cnt_en(data)                             ((0x00001000&(data))>>12)
#define SATA0_pinout_get_tx_data_vld(data)                            ((0x00000200&(data))>>9)
#define SATA0_pinout_get_rx_enable(data)                              ((0x00000100&(data))>>8)
#define SATA0_pinout_get_tx_enable(data)                              ((0x00000080&(data))>>7)
#define SATA0_pinout_get_reset_n(data)                                ((0x00000040&(data))>>6)
#define SATA0_pinout_get_slumber(data)                                ((0x00000020&(data))>>5)
#define SATA0_pinout_get_partial(data)                                ((0x00000010&(data))>>4)
#define SATA0_pinout_get_farafelb(data)                               ((0x00000008&(data))>>3)
#define SATA0_pinout_get_nearafelb(data)                              ((0x00000004&(data))>>2)
#define SATA0_pinout_get_spdsel(data)                                 ((0x00000002&(data))>>1)
#define SATA0_pinout_get_enable(data)                                 (0x00000001&(data))

#define SATA0_timeout                                                 0x18012BF4
#define SATA0_timeout_reg_addr                                        "0xB8012BF4"
#define SATA0_timeout_reg                                             0xB8012BF4
#define SATA0_timeout_inst_addr                                       "0x02FD"
#define SATA0_timeout_inst                                            0x02FD
#define SATA0_timeout_timeout_flg_shift                               (28)
#define SATA0_timeout_timeout_en_shift                                (16)
#define SATA0_timeout_timeout_cnt_shift                               (0)
#define SATA0_timeout_timeout_flg_mask                                (0x10000000)
#define SATA0_timeout_timeout_en_mask                                 (0x00010000)
#define SATA0_timeout_timeout_cnt_mask                                (0x0000FFFF)
#define SATA0_timeout_timeout_flg(data)                               (0x10000000&((data)<<28))
#define SATA0_timeout_timeout_en(data)                                (0x00010000&((data)<<16))
#define SATA0_timeout_timeout_cnt(data)                               (0x0000FFFF&(data))
#define SATA0_timeout_get_timeout_flg(data)                           ((0x10000000&(data))>>28)
#define SATA0_timeout_get_timeout_en(data)                            ((0x00010000&(data))>>16)
#define SATA0_timeout_get_timeout_cnt(data)                           (0x0000FFFF&(data))

#define SATA0_dbg                                                     0x18012BF8
#define SATA0_dbg_reg_addr                                            "0xB8012BF8"
#define SATA0_dbg_reg                                                 0xB8012BF8
#define SATA0_dbg_inst_addr                                           "0x02FE"
#define SATA0_dbg_inst                                                0x02FE
#define SATA0_dbg_write_enable4_shift                                 (28)
#define SATA0_dbg_test_key_shift                                      (12)
#define SATA0_dbg_write_enable3_shift                                 (9)
#define SATA0_dbg_sel1_shift                                          (6)
#define SATA0_dbg_write_enable2_shift                                 (5)
#define SATA0_dbg_sel0_shift                                          (2)
#define SATA0_dbg_write_enable1_shift                                 (1)
#define SATA0_dbg_enable_shift                                        (0)
#define SATA0_dbg_write_enable4_mask                                  (0x10000000)
#define SATA0_dbg_test_key_mask                                       (0x0FFFF000)
#define SATA0_dbg_write_enable3_mask                                  (0x00000200)
#define SATA0_dbg_sel1_mask                                           (0x000001C0)
#define SATA0_dbg_write_enable2_mask                                  (0x00000020)
#define SATA0_dbg_sel0_mask                                           (0x0000001C)
#define SATA0_dbg_write_enable1_mask                                  (0x00000002)
#define SATA0_dbg_enable_mask                                         (0x00000001)
#define SATA0_dbg_write_enable4(data)                                 (0x10000000&((data)<<28))
#define SATA0_dbg_test_key(data)                                      (0x0FFFF000&((data)<<12))
#define SATA0_dbg_write_enable3(data)                                 (0x00000200&((data)<<9))
#define SATA0_dbg_sel1(data)                                          (0x000001C0&((data)<<6))
#define SATA0_dbg_write_enable2(data)                                 (0x00000020&((data)<<5))
#define SATA0_dbg_sel0(data)                                          (0x0000001C&((data)<<2))
#define SATA0_dbg_write_enable1(data)                                 (0x00000002&((data)<<1))
#define SATA0_dbg_enable(data)                                        (0x00000001&(data))
#define SATA0_dbg_get_write_enable4(data)                             ((0x10000000&(data))>>28)
#define SATA0_dbg_get_test_key(data)                                  ((0x0FFFF000&(data))>>12)
#define SATA0_dbg_get_write_enable3(data)                             ((0x00000200&(data))>>9)
#define SATA0_dbg_get_sel1(data)                                      ((0x000001C0&(data))>>6)
#define SATA0_dbg_get_write_enable2(data)                             ((0x00000020&(data))>>5)
#define SATA0_dbg_get_sel0(data)                                      ((0x0000001C&(data))>>2)
#define SATA0_dbg_get_write_enable1(data)                             ((0x00000002&(data))>>1)
#define SATA0_dbg_get_enable(data)                                    (0x00000001&(data))
#endif
