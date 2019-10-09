// This file is generated using the spec version 2.0, firmware template version 1.39and DVR_Parser_0.46
#ifndef _SATA1_REG_H_INCLUDED_
#define _SATA1_REG_H_INCLUDED_

//#define  _SATA1_USE_STRUCT
#ifdef _SATA1_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data:16;
}sata1_CDR0;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata1_CDR1;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata1_CDR2;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata1_CDR3;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata1_CDR4;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    data_p:8;
    unsigned int    data:8;
}sata1_CDR5;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata1_CDR6;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata1_CDR7;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    data:8;
}sata1_CLR0;

typedef struct
{
    unsigned int    sstatus:32;
}sata1_SCR0;

typedef struct
{
    unsigned int    serror:32;
}sata1_SCR1;

typedef struct
{
    unsigned int    scontrol:32;
}sata1_SCR2;

typedef struct
{
    unsigned int    sactive:32;
}sata1_SCR3;

typedef struct
{
    unsigned int    snotification:32;
}sata1_SCR4;

typedef struct
{
    unsigned int    reserved_0:32;
}sata1_SCR5;

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
}sata1_DMACTRL;

typedef struct
{
    unsigned int    prd_ptr:30;
    unsigned int    reserved_0:2;
}sata1_PRDPTR;

typedef struct
{
    unsigned int    prd_pba:30;
    unsigned int    reserved_0:2;
}sata1_PRDEty0;

typedef struct
{
    unsigned int    eot:1;
    unsigned int    reserved_0:7;
    unsigned int    prd_bycnt:22;
    unsigned int    reserved_1:2;
}sata1_PRDEty1;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    intrq_en:1;
}sata1_enable;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    bridge_rlevel:4;
    unsigned int    bridge_wlevel:4;
    unsigned int    dma_flevel:4;
    unsigned int    reserved_1:5;
    unsigned int    cmd_swap:2;
    unsigned int    data_swap:1;
}sata1_DMAMisc;

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
}sata1_MDIOCtrl;

typedef struct
{
    unsigned int    crc:32;
}sata1_DMACrc;

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
}sata1_pinout;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    timeout_flg:1;
    unsigned int    reserved_1:11;
    unsigned int    timeout_en:1;
    unsigned int    timeout_cnt:16;
}sata1_timeout;

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
}sata1_dbg;
#endif

#define SATA1_CDR0                                                    0x18012C00
#define SATA1_CDR0_reg_addr                                           "0xB8012C00"
#define SATA1_CDR0_reg                                                0xB8012C00
#define SATA1_CDR0_inst_addr                                          "0x0300"
#define SATA1_CDR0_inst                                               0x0300
#define SATA1_CDR0_data_shift                                         (0)
#define SATA1_CDR0_data_mask                                          (0x0000FFFF)
#define SATA1_CDR0_data(data)                                         (0x0000FFFF&(data))
#define SATA1_CDR0_get_data(data)                                     (0x0000FFFF&(data))

#define SATA1_CDR1                                                    0x18012C04
#define SATA1_CDR1_reg_addr                                           "0xB8012C04"
#define SATA1_CDR1_reg                                                0xB8012C04
#define SATA1_CDR1_inst_addr                                          "0x0301"
#define SATA1_CDR1_inst                                               0x0301
#define SATA1_CDR1_data_p_shift                                       (8)
#define SATA1_CDR1_data_shift                                         (0)
#define SATA1_CDR1_data_p_mask                                        (0x0000FF00)
#define SATA1_CDR1_data_mask                                          (0x000000FF)
#define SATA1_CDR1_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA1_CDR1_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR1_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA1_CDR1_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR2                                                    0x18012C08
#define SATA1_CDR2_reg_addr                                           "0xB8012C08"
#define SATA1_CDR2_reg                                                0xB8012C08
#define SATA1_CDR2_inst_addr                                          "0x0302"
#define SATA1_CDR2_inst                                               0x0302
#define SATA1_CDR2_data_p_shift                                       (8)
#define SATA1_CDR2_data_shift                                         (0)
#define SATA1_CDR2_data_p_mask                                        (0x0000FF00)
#define SATA1_CDR2_data_mask                                          (0x000000FF)
#define SATA1_CDR2_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA1_CDR2_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR2_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA1_CDR2_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR3                                                    0x18012C0C
#define SATA1_CDR3_reg_addr                                           "0xB8012C0C"
#define SATA1_CDR3_reg                                                0xB8012C0C
#define SATA1_CDR3_inst_addr                                          "0x0303"
#define SATA1_CDR3_inst                                               0x0303
#define SATA1_CDR3_data_p_shift                                       (8)
#define SATA1_CDR3_data_shift                                         (0)
#define SATA1_CDR3_data_p_mask                                        (0x0000FF00)
#define SATA1_CDR3_data_mask                                          (0x000000FF)
#define SATA1_CDR3_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA1_CDR3_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR3_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA1_CDR3_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR4                                                    0x18012C10
#define SATA1_CDR4_reg_addr                                           "0xB8012C10"
#define SATA1_CDR4_reg                                                0xB8012C10
#define SATA1_CDR4_inst_addr                                          "0x0304"
#define SATA1_CDR4_inst                                               0x0304
#define SATA1_CDR4_data_p_shift                                       (8)
#define SATA1_CDR4_data_shift                                         (0)
#define SATA1_CDR4_data_p_mask                                        (0x0000FF00)
#define SATA1_CDR4_data_mask                                          (0x000000FF)
#define SATA1_CDR4_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA1_CDR4_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR4_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA1_CDR4_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR5                                                    0x18012C14
#define SATA1_CDR5_reg_addr                                           "0xB8012C14"
#define SATA1_CDR5_reg                                                0xB8012C14
#define SATA1_CDR5_inst_addr                                          "0x0305"
#define SATA1_CDR5_inst                                               0x0305
#define SATA1_CDR5_data_p_shift                                       (8)
#define SATA1_CDR5_data_shift                                         (0)
#define SATA1_CDR5_data_p_mask                                        (0x0000FF00)
#define SATA1_CDR5_data_mask                                          (0x000000FF)
#define SATA1_CDR5_data_p(data)                                       (0x0000FF00&((data)<<8))
#define SATA1_CDR5_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR5_get_data_p(data)                                   ((0x0000FF00&(data))>>8)
#define SATA1_CDR5_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR6                                                    0x18012C18
#define SATA1_CDR6_reg_addr                                           "0xB8012C18"
#define SATA1_CDR6_reg                                                0xB8012C18
#define SATA1_CDR6_inst_addr                                          "0x0306"
#define SATA1_CDR6_inst                                               0x0306
#define SATA1_CDR6_data_shift                                         (0)
#define SATA1_CDR6_data_mask                                          (0x000000FF)
#define SATA1_CDR6_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR6_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CDR7                                                    0x18012C1C
#define SATA1_CDR7_reg_addr                                           "0xB8012C1C"
#define SATA1_CDR7_reg                                                0xB8012C1C
#define SATA1_CDR7_inst_addr                                          "0x0307"
#define SATA1_CDR7_inst                                               0x0307
#define SATA1_CDR7_data_shift                                         (0)
#define SATA1_CDR7_data_mask                                          (0x000000FF)
#define SATA1_CDR7_data(data)                                         (0x000000FF&(data))
#define SATA1_CDR7_get_data(data)                                     (0x000000FF&(data))

#define SATA1_CLR0                                                    0x18012C20
#define SATA1_CLR0_reg_addr                                           "0xB8012C20"
#define SATA1_CLR0_reg                                                0xB8012C20
#define SATA1_CLR0_inst_addr                                          "0x0308"
#define SATA1_CLR0_inst                                               0x0308
#define SATA1_CLR0_data_shift                                         (0)
#define SATA1_CLR0_data_mask                                          (0x000000FF)
#define SATA1_CLR0_data(data)                                         (0x000000FF&(data))
#define SATA1_CLR0_get_data(data)                                     (0x000000FF&(data))

#define SATA1_SCR0                                                    0x18012C24
#define SATA1_SCR0_reg_addr                                           "0xB8012C24"
#define SATA1_SCR0_reg                                                0xB8012C24
#define SATA1_SCR0_inst_addr                                          "0x0309"
#define SATA1_SCR0_inst                                               0x0309
#define SATA1_SCR0_sstatus_shift                                      (0)
#define SATA1_SCR0_sstatus_mask                                       (0xFFFFFFFF)
#define SATA1_SCR0_sstatus(data)                                      (0xFFFFFFFF&(data))
#define SATA1_SCR0_get_sstatus(data)                                  (0xFFFFFFFF&(data))

#define SATA1_SCR1                                                    0x18012C28
#define SATA1_SCR1_reg_addr                                           "0xB8012C28"
#define SATA1_SCR1_reg                                                0xB8012C28
#define SATA1_SCR1_inst_addr                                          "0x030A"
#define SATA1_SCR1_inst                                               0x030A
#define SATA1_SCR1_serror_shift                                       (0)
#define SATA1_SCR1_serror_mask                                        (0xFFFFFFFF)
#define SATA1_SCR1_serror(data)                                       (0xFFFFFFFF&(data))
#define SATA1_SCR1_get_serror(data)                                   (0xFFFFFFFF&(data))

#define SATA1_SCR2                                                    0x18012C2C
#define SATA1_SCR2_reg_addr                                           "0xB8012C2C"
#define SATA1_SCR2_reg                                                0xB8012C2C
#define SATA1_SCR2_inst_addr                                          "0x030B"
#define SATA1_SCR2_inst                                               0x030B
#define SATA1_SCR2_scontrol_shift                                     (0)
#define SATA1_SCR2_scontrol_mask                                      (0xFFFFFFFF)
#define SATA1_SCR2_scontrol(data)                                     (0xFFFFFFFF&(data))
#define SATA1_SCR2_get_scontrol(data)                                 (0xFFFFFFFF&(data))

#define SATA1_SCR3                                                    0x18012C30
#define SATA1_SCR3_reg_addr                                           "0xB8012C30"
#define SATA1_SCR3_reg                                                0xB8012C30
#define SATA1_SCR3_inst_addr                                          "0x030C"
#define SATA1_SCR3_inst                                               0x030C
#define SATA1_SCR3_sactive_shift                                      (0)
#define SATA1_SCR3_sactive_mask                                       (0xFFFFFFFF)
#define SATA1_SCR3_sactive(data)                                      (0xFFFFFFFF&(data))
#define SATA1_SCR3_get_sactive(data)                                  (0xFFFFFFFF&(data))

#define SATA1_SCR4                                                    0x18012C34
#define SATA1_SCR4_reg_addr                                           "0xB8012C34"
#define SATA1_SCR4_reg                                                0xB8012C34
#define SATA1_SCR4_inst_addr                                          "0x030D"
#define SATA1_SCR4_inst                                               0x030D
#define SATA1_SCR4_snotification_shift                                (0)
#define SATA1_SCR4_snotification_mask                                 (0xFFFFFFFF)
#define SATA1_SCR4_snotification(data)                                (0xFFFFFFFF&(data))
#define SATA1_SCR4_get_snotification(data)                            (0xFFFFFFFF&(data))

#define SATA1_SCR5                                                    0x18012C38
#define SATA1_SCR5_reg_addr                                           "0xB8012C38"
#define SATA1_SCR5_reg                                                0xB8012C38
#define SATA1_SCR5_inst_addr                                          "0x030E"
#define SATA1_SCR5_inst                                               0x030E

#define SATA1_DMACTRL                                                 0x18012CD0
#define SATA1_DMACTRL_reg_addr                                        "0xB8012CD0"
#define SATA1_DMACTRL_reg                                             0xB8012CD0
#define SATA1_DMACTRL_inst_addr                                       "0x0334"
#define SATA1_DMACTRL_inst                                            0x0334
#define SATA1_DMACTRL_reg_mode_shift                                  (16)
#define SATA1_DMACTRL_prd_num_shift                                   (8)
#define SATA1_DMACTRL_cpen_shift                                      (6)
#define SATA1_DMACTRL_srst_shift                                      (5)
#define SATA1_DMACTRL_self_test_shift                                 (4)
#define SATA1_DMACTRL_write_shift                                     (3)
#define SATA1_DMACTRL_go_shift                                        (0)
#define SATA1_DMACTRL_reg_mode_mask                                   (0x00010000)
#define SATA1_DMACTRL_prd_num_mask                                    (0x0000FF00)
#define SATA1_DMACTRL_cpen_mask                                       (0x00000040)
#define SATA1_DMACTRL_srst_mask                                       (0x00000020)
#define SATA1_DMACTRL_self_test_mask                                  (0x00000010)
#define SATA1_DMACTRL_write_mask                                      (0x00000008)
#define SATA1_DMACTRL_go_mask                                         (0x00000001)
#define SATA1_DMACTRL_reg_mode(data)                                  (0x00010000&((data)<<16))
#define SATA1_DMACTRL_prd_num(data)                                   (0x0000FF00&((data)<<8))
#define SATA1_DMACTRL_cpen(data)                                      (0x00000040&((data)<<6))
#define SATA1_DMACTRL_srst(data)                                      (0x00000020&((data)<<5))
#define SATA1_DMACTRL_self_test(data)                                 (0x00000010&((data)<<4))
#define SATA1_DMACTRL_write(data)                                     (0x00000008&((data)<<3))
#define SATA1_DMACTRL_go(data)                                        (0x00000001&(data))
#define SATA1_DMACTRL_get_reg_mode(data)                              ((0x00010000&(data))>>16)
#define SATA1_DMACTRL_get_prd_num(data)                               ((0x0000FF00&(data))>>8)
#define SATA1_DMACTRL_get_cpen(data)                                  ((0x00000040&(data))>>6)
#define SATA1_DMACTRL_get_srst(data)                                  ((0x00000020&(data))>>5)
#define SATA1_DMACTRL_get_self_test(data)                             ((0x00000010&(data))>>4)
#define SATA1_DMACTRL_get_write(data)                                 ((0x00000008&(data))>>3)
#define SATA1_DMACTRL_get_go(data)                                    (0x00000001&(data))

#define SATA1_PRDPTR                                                  0x18012CD4
#define SATA1_PRDPTR_reg_addr                                         "0xB8012CD4"
#define SATA1_PRDPTR_reg                                              0xB8012CD4
#define SATA1_PRDPTR_inst_addr                                        "0x0335"
#define SATA1_PRDPTR_inst                                             0x0335
#define SATA1_PRDPTR_prd_ptr_shift                                    (2)
#define SATA1_PRDPTR_prd_ptr_mask                                     (0xFFFFFFFC)
#define SATA1_PRDPTR_prd_ptr(data)                                    (0xFFFFFFFC&((data)<<2))
#define SATA1_PRDPTR_get_prd_ptr(data)                                ((0xFFFFFFFC&(data))>>2)

#define SATA1_PRDEty0                                                 0x18012CD8
#define SATA1_PRDEty0_reg_addr                                        "0xB8012CD8"
#define SATA1_PRDEty0_reg                                             0xB8012CD8
#define SATA1_PRDEty0_inst_addr                                       "0x0336"
#define SATA1_PRDEty0_inst                                            0x0336
#define SATA1_PRDEty0_prd_pba_shift                                   (2)
#define SATA1_PRDEty0_prd_pba_mask                                    (0xFFFFFFFC)
#define SATA1_PRDEty0_prd_pba(data)                                   (0xFFFFFFFC&((data)<<2))
#define SATA1_PRDEty0_get_prd_pba(data)                               ((0xFFFFFFFC&(data))>>2)

#define SATA1_PRDEty1                                                 0x18012CDC
#define SATA1_PRDEty1_reg_addr                                        "0xB8012CDC"
#define SATA1_PRDEty1_reg                                             0xB8012CDC
#define SATA1_PRDEty1_inst_addr                                       "0x0337"
#define SATA1_PRDEty1_inst                                            0x0337
#define SATA1_PRDEty1_eot_shift                                       (31)
#define SATA1_PRDEty1_prd_bycnt_shift                                 (2)
#define SATA1_PRDEty1_eot_mask                                        (0x80000000)
#define SATA1_PRDEty1_prd_bycnt_mask                                  (0x00FFFFFC)
#define SATA1_PRDEty1_eot(data)                                       (0x80000000&((data)<<31))
#define SATA1_PRDEty1_prd_bycnt(data)                                 (0x00FFFFFC&((data)<<2))
#define SATA1_PRDEty1_get_eot(data)                                   ((0x80000000&(data))>>31)
#define SATA1_PRDEty1_get_prd_bycnt(data)                             ((0x00FFFFFC&(data))>>2)

#define SATA1_enable                                                  0x18012CE0
#define SATA1_enable_reg_addr                                         "0xB8012CE0"
#define SATA1_enable_reg                                              0xB8012CE0
#define SATA1_enable_inst_addr                                        "0x0338"
#define SATA1_enable_inst                                             0x0338
#define SATA1_enable_intrq_en_shift                                   (0)
#define SATA1_enable_intrq_en_mask                                    (0x00000001)
#define SATA1_enable_intrq_en(data)                                   (0x00000001&(data))
#define SATA1_enable_get_intrq_en(data)                               (0x00000001&(data))

#define SATA1_DMAMisc                                                 0x18012CE4
#define SATA1_DMAMisc_reg_addr                                        "0xB8012CE4"
#define SATA1_DMAMisc_reg                                             0xB8012CE4
#define SATA1_DMAMisc_inst_addr                                       "0x0339"
#define SATA1_DMAMisc_inst                                            0x0339
#define SATA1_DMAMisc_bridge_rlevel_shift                             (16)
#define SATA1_DMAMisc_bridge_wlevel_shift                             (12)
#define SATA1_DMAMisc_dma_flevel_shift                                (8)
#define SATA1_DMAMisc_cmd_swap_shift                                  (1)
#define SATA1_DMAMisc_data_swap_shift                                 (0)
#define SATA1_DMAMisc_bridge_rlevel_mask                              (0x000F0000)
#define SATA1_DMAMisc_bridge_wlevel_mask                              (0x0000F000)
#define SATA1_DMAMisc_dma_flevel_mask                                 (0x00000F00)
#define SATA1_DMAMisc_cmd_swap_mask                                   (0x00000006)
#define SATA1_DMAMisc_data_swap_mask                                  (0x00000001)
#define SATA1_DMAMisc_bridge_rlevel(data)                             (0x000F0000&((data)<<16))
#define SATA1_DMAMisc_bridge_wlevel(data)                             (0x0000F000&((data)<<12))
#define SATA1_DMAMisc_dma_flevel(data)                                (0x00000F00&((data)<<8))
#define SATA1_DMAMisc_cmd_swap(data)                                  (0x00000006&((data)<<1))
#define SATA1_DMAMisc_data_swap(data)                                 (0x00000001&(data))
#define SATA1_DMAMisc_get_bridge_rlevel(data)                         ((0x000F0000&(data))>>16)
#define SATA1_DMAMisc_get_bridge_wlevel(data)                         ((0x0000F000&(data))>>12)
#define SATA1_DMAMisc_get_dma_flevel(data)                            ((0x00000F00&(data))>>8)
#define SATA1_DMAMisc_get_cmd_swap(data)                              ((0x00000006&(data))>>1)
#define SATA1_DMAMisc_get_data_swap(data)                             (0x00000001&(data))

#define SATA1_MDIOCtrl                                                0x18012CE8
#define SATA1_MDIOCtrl_reg_addr                                       "0xB8012CE8"
#define SATA1_MDIOCtrl_reg                                            0xB8012CE8
#define SATA1_MDIOCtrl_inst_addr                                      "0x033A"
#define SATA1_MDIOCtrl_inst                                           0x033A
#define SATA1_MDIOCtrl_data_shift                                     (16)
#define SATA1_MDIOCtrl_phy_adr_shift                                  (13)
#define SATA1_MDIOCtrl_reg_adr_shift                                  (8)
#define SATA1_MDIOCtrl_mdio_st_shift                                  (5)
#define SATA1_MDIOCtrl_mdio_rdy_shift                                 (4)
#define SATA1_MDIOCtrl_mclk_rate_shift                                (2)
#define SATA1_MDIOCtrl_mdio_srst_shift                                (1)
#define SATA1_MDIOCtrl_mdio_rdwr_shift                                (0)
#define SATA1_MDIOCtrl_data_mask                                      (0xFFFF0000)
#define SATA1_MDIOCtrl_phy_adr_mask                                   (0x0000E000)
#define SATA1_MDIOCtrl_reg_adr_mask                                   (0x00001F00)
#define SATA1_MDIOCtrl_mdio_st_mask                                   (0x00000060)
#define SATA1_MDIOCtrl_mdio_rdy_mask                                  (0x00000010)
#define SATA1_MDIOCtrl_mclk_rate_mask                                 (0x0000000C)
#define SATA1_MDIOCtrl_mdio_srst_mask                                 (0x00000002)
#define SATA1_MDIOCtrl_mdio_rdwr_mask                                 (0x00000001)
#define SATA1_MDIOCtrl_data(data)                                     (0xFFFF0000&((data)<<16))
#define SATA1_MDIOCtrl_phy_adr(data)                                  (0x0000E000&((data)<<13))
#define SATA1_MDIOCtrl_reg_adr(data)                                  (0x00001F00&((data)<<8))
#define SATA1_MDIOCtrl_mdio_st(data)                                  (0x00000060&((data)<<5))
#define SATA1_MDIOCtrl_mdio_rdy(data)                                 (0x00000010&((data)<<4))
#define SATA1_MDIOCtrl_mclk_rate(data)                                (0x0000000C&((data)<<2))
#define SATA1_MDIOCtrl_mdio_srst(data)                                (0x00000002&((data)<<1))
#define SATA1_MDIOCtrl_mdio_rdwr(data)                                (0x00000001&(data))
#define SATA1_MDIOCtrl_get_data(data)                                 ((0xFFFF0000&(data))>>16)
#define SATA1_MDIOCtrl_get_phy_adr(data)                              ((0x0000E000&(data))>>13)
#define SATA1_MDIOCtrl_get_reg_adr(data)                              ((0x00001F00&(data))>>8)
#define SATA1_MDIOCtrl_get_mdio_st(data)                              ((0x00000060&(data))>>5)
#define SATA1_MDIOCtrl_get_mdio_rdy(data)                             ((0x00000010&(data))>>4)
#define SATA1_MDIOCtrl_get_mclk_rate(data)                            ((0x0000000C&(data))>>2)
#define SATA1_MDIOCtrl_get_mdio_srst(data)                            ((0x00000002&(data))>>1)
#define SATA1_MDIOCtrl_get_mdio_rdwr(data)                            (0x00000001&(data))

#define SATA1_DMACrc                                                  0x18012CEC
#define SATA1_DMACrc_reg_addr                                         "0xB8012CEC"
#define SATA1_DMACrc_reg                                              0xB8012CEC
#define SATA1_DMACrc_inst_addr                                        "0x033B"
#define SATA1_DMACrc_inst                                             0x033B
#define SATA1_DMACrc_crc_shift                                        (0)
#define SATA1_DMACrc_crc_mask                                         (0xFFFFFFFF)
#define SATA1_DMACrc_crc(data)                                        (0xFFFFFFFF&(data))
#define SATA1_DMACrc_get_crc(data)                                    (0xFFFFFFFF&(data))

#define SATA1_pinout                                                  0x18012CF0
#define SATA1_pinout_reg_addr                                         "0xB8012CF0"
#define SATA1_pinout_reg                                              0xB8012CF0
#define SATA1_pinout_inst_addr                                        "0x033C"
#define SATA1_pinout_inst                                             0x033C
#define SATA1_pinout_req_cnt_shift                                    (16)
#define SATA1_pinout_req_cnt_en_shift                                 (12)
#define SATA1_pinout_tx_data_vld_shift                                (9)
#define SATA1_pinout_rx_enable_shift                                  (8)
#define SATA1_pinout_tx_enable_shift                                  (7)
#define SATA1_pinout_reset_n_shift                                    (6)
#define SATA1_pinout_slumber_shift                                    (5)
#define SATA1_pinout_partial_shift                                    (4)
#define SATA1_pinout_farafelb_shift                                   (3)
#define SATA1_pinout_nearafelb_shift                                  (2)
#define SATA1_pinout_spdsel_shift                                     (1)
#define SATA1_pinout_enable_shift                                     (0)
#define SATA1_pinout_req_cnt_mask                                     (0xFFFF0000)
#define SATA1_pinout_req_cnt_en_mask                                  (0x00001000)
#define SATA1_pinout_tx_data_vld_mask                                 (0x00000200)
#define SATA1_pinout_rx_enable_mask                                   (0x00000100)
#define SATA1_pinout_tx_enable_mask                                   (0x00000080)
#define SATA1_pinout_reset_n_mask                                     (0x00000040)
#define SATA1_pinout_slumber_mask                                     (0x00000020)
#define SATA1_pinout_partial_mask                                     (0x00000010)
#define SATA1_pinout_farafelb_mask                                    (0x00000008)
#define SATA1_pinout_nearafelb_mask                                   (0x00000004)
#define SATA1_pinout_spdsel_mask                                      (0x00000002)
#define SATA1_pinout_enable_mask                                      (0x00000001)
#define SATA1_pinout_req_cnt(data)                                    (0xFFFF0000&((data)<<16))
#define SATA1_pinout_req_cnt_en(data)                                 (0x00001000&((data)<<12))
#define SATA1_pinout_tx_data_vld(data)                                (0x00000200&((data)<<9))
#define SATA1_pinout_rx_enable(data)                                  (0x00000100&((data)<<8))
#define SATA1_pinout_tx_enable(data)                                  (0x00000080&((data)<<7))
#define SATA1_pinout_reset_n(data)                                    (0x00000040&((data)<<6))
#define SATA1_pinout_slumber(data)                                    (0x00000020&((data)<<5))
#define SATA1_pinout_partial(data)                                    (0x00000010&((data)<<4))
#define SATA1_pinout_farafelb(data)                                   (0x00000008&((data)<<3))
#define SATA1_pinout_nearafelb(data)                                  (0x00000004&((data)<<2))
#define SATA1_pinout_spdsel(data)                                     (0x00000002&((data)<<1))
#define SATA1_pinout_enable(data)                                     (0x00000001&(data))
#define SATA1_pinout_get_req_cnt(data)                                ((0xFFFF0000&(data))>>16)
#define SATA1_pinout_get_req_cnt_en(data)                             ((0x00001000&(data))>>12)
#define SATA1_pinout_get_tx_data_vld(data)                            ((0x00000200&(data))>>9)
#define SATA1_pinout_get_rx_enable(data)                              ((0x00000100&(data))>>8)
#define SATA1_pinout_get_tx_enable(data)                              ((0x00000080&(data))>>7)
#define SATA1_pinout_get_reset_n(data)                                ((0x00000040&(data))>>6)
#define SATA1_pinout_get_slumber(data)                                ((0x00000020&(data))>>5)
#define SATA1_pinout_get_partial(data)                                ((0x00000010&(data))>>4)
#define SATA1_pinout_get_farafelb(data)                               ((0x00000008&(data))>>3)
#define SATA1_pinout_get_nearafelb(data)                              ((0x00000004&(data))>>2)
#define SATA1_pinout_get_spdsel(data)                                 ((0x00000002&(data))>>1)
#define SATA1_pinout_get_enable(data)                                 (0x00000001&(data))

#define SATA1_timeout                                                 0x18012CF4
#define SATA1_timeout_reg_addr                                        "0xB8012CF4"
#define SATA1_timeout_reg                                             0xB8012CF4
#define SATA1_timeout_inst_addr                                       "0x033D"
#define SATA1_timeout_inst                                            0x033D
#define SATA1_timeout_timeout_flg_shift                               (28)
#define SATA1_timeout_timeout_en_shift                                (16)
#define SATA1_timeout_timeout_cnt_shift                               (0)
#define SATA1_timeout_timeout_flg_mask                                (0x10000000)
#define SATA1_timeout_timeout_en_mask                                 (0x00010000)
#define SATA1_timeout_timeout_cnt_mask                                (0x0000FFFF)
#define SATA1_timeout_timeout_flg(data)                               (0x10000000&((data)<<28))
#define SATA1_timeout_timeout_en(data)                                (0x00010000&((data)<<16))
#define SATA1_timeout_timeout_cnt(data)                               (0x0000FFFF&(data))
#define SATA1_timeout_get_timeout_flg(data)                           ((0x10000000&(data))>>28)
#define SATA1_timeout_get_timeout_en(data)                            ((0x00010000&(data))>>16)
#define SATA1_timeout_get_timeout_cnt(data)                           (0x0000FFFF&(data))

#define SATA1_dbg                                                     0x18012CF8
#define SATA1_dbg_reg_addr                                            "0xB8012CF8"
#define SATA1_dbg_reg                                                 0xB8012CF8
#define SATA1_dbg_inst_addr                                           "0x033E"
#define SATA1_dbg_inst                                                0x033E
#define SATA1_dbg_write_enable4_shift                                 (28)
#define SATA1_dbg_test_key_shift                                      (12)
#define SATA1_dbg_write_enable3_shift                                 (9)
#define SATA1_dbg_sel1_shift                                          (6)
#define SATA1_dbg_write_enable2_shift                                 (5)
#define SATA1_dbg_sel0_shift                                          (2)
#define SATA1_dbg_write_enable1_shift                                 (1)
#define SATA1_dbg_enable_shift                                        (0)
#define SATA1_dbg_write_enable4_mask                                  (0x10000000)
#define SATA1_dbg_test_key_mask                                       (0x0FFFF000)
#define SATA1_dbg_write_enable3_mask                                  (0x00000200)
#define SATA1_dbg_sel1_mask                                           (0x000001C0)
#define SATA1_dbg_write_enable2_mask                                  (0x00000020)
#define SATA1_dbg_sel0_mask                                           (0x0000001C)
#define SATA1_dbg_write_enable1_mask                                  (0x00000002)
#define SATA1_dbg_enable_mask                                         (0x00000001)
#define SATA1_dbg_write_enable4(data)                                 (0x10000000&((data)<<28))
#define SATA1_dbg_test_key(data)                                      (0x0FFFF000&((data)<<12))
#define SATA1_dbg_write_enable3(data)                                 (0x00000200&((data)<<9))
#define SATA1_dbg_sel1(data)                                          (0x000001C0&((data)<<6))
#define SATA1_dbg_write_enable2(data)                                 (0x00000020&((data)<<5))
#define SATA1_dbg_sel0(data)                                          (0x0000001C&((data)<<2))
#define SATA1_dbg_write_enable1(data)                                 (0x00000002&((data)<<1))
#define SATA1_dbg_enable(data)                                        (0x00000001&(data))
#define SATA1_dbg_get_write_enable4(data)                             ((0x10000000&(data))>>28)
#define SATA1_dbg_get_test_key(data)                                  ((0x0FFFF000&(data))>>12)
#define SATA1_dbg_get_write_enable3(data)                             ((0x00000200&(data))>>9)
#define SATA1_dbg_get_sel1(data)                                      ((0x000001C0&(data))>>6)
#define SATA1_dbg_get_write_enable2(data)                             ((0x00000020&(data))>>5)
#define SATA1_dbg_get_sel0(data)                                      ((0x0000001C&(data))>>2)
#define SATA1_dbg_get_write_enable1(data)                             ((0x00000002&(data))>>1)
#define SATA1_dbg_get_enable(data)                                    (0x00000001&(data))
#endif
