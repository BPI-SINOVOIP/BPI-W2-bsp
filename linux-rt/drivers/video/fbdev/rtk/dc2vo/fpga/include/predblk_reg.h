/**************************************************************
// Spec Version                  : 0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/6/22 11:40:33
***************************************************************/


#ifndef _PREDBLK_REG_H_INCLUDED_
#define _PREDBLK_REG_H_INCLUDED_
#ifdef  _PREDBLK_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     Nhmem_Flush:1;
unsigned int     RMEM_Rst:1;
unsigned int     Deblk_xsfer_mode:1;
unsigned int     Debug_mode:1;
unsigned int     fmo:1;
unsigned int     reserved_1:4;
unsigned int     Softrst_disable:1;
unsigned int     New_slice_row:1;
unsigned int     New_slice_mb_x:9;
unsigned int     Sw_neighbor_enable:1;
unsigned int     MbAddrA_available:1;
unsigned int     MbAddrB_available:1;
unsigned int     MbAddrC_available:1;
unsigned int     MbAddrD_available:1;
}PREDBLK_NEIGHBOR;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     ic_mix_fcm_enable:1;
unsigned int     CONDOVER:2;
unsigned int     Rnd_ctrl_ovt:1;
unsigned int     RND:1;
unsigned int     INTCOMP:1;
unsigned int     LUMSCALE0:6;
unsigned int     LUMSHIFT0:6;
}PREDBLK_VC1INTC1;

typedef struct 
{
unsigned int     Ic_pass0_of_fwd:4;
unsigned int     Ic_pass1_of_fwd:4;
unsigned int     Ic_pass0_sf_fwd:4;
unsigned int     Ic_pass1_sf_fwd:4;
unsigned int     Ic_pass0_of_bwd:4;
unsigned int     Ic_pass1_of_bwd:4;
unsigned int     Ic_pass0_sf_bwd:4;
unsigned int     Ic_pass1_sf_bwd:4;
}PREDBLK_VC1INTC2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     LUMSCALE1:6;
unsigned int     LUMSHIFT1:6;
unsigned int     LUMSCALE2:6;
unsigned int     LUMSHIFT2:6;
}PREDBLK_VC1INTC3;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     LUMSCALE3:6;
unsigned int     LUMSHIFT3:6;
unsigned int     LUMSCALE4:6;
unsigned int     LUMSHIFT4:6;
}PREDBLK_VC1INTC4;

typedef struct 
{
unsigned int     intra_flag:32;
}PREDBLK_NBINTRA0;

typedef struct 
{
unsigned int     intra_flag:32;
}PREDBLK_NBINTRA1;

typedef struct 
{
unsigned int     intra_flag:32;
}PREDBLK_NBINTRACH;

typedef struct 
{
unsigned int     Field_overflag_flag:32;
}PREDBLK_NBFIELDOV;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     Intra0:1;
unsigned int     Intra1:1;
unsigned int     IntraChroma:1;
unsigned int     IntraField:1;
}PREDBLK_NBEXTRA;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     WTBL_StartA:10;
}PREDBLK_WTBLSA;

typedef struct 
{
unsigned int     wt_flag:32;
}PREDBLK_WTFLAG;

typedef struct 
{
unsigned int     Wdone_enable:1;
unsigned int     Mem_eng_busy:1;
unsigned int     reserved_0:1;
unsigned int     seq_line_addr:29;
}PREDBLK_SDMAADR;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     Value:28;
}PREDBLK_INTR_THRESH;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     Reach_Thresh:1;
unsigned int     Count:28;
}PREDBLK_BUSY;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     BaseA0:7;
unsigned int     reserved_1:6;
unsigned int     BaseA1:7;
unsigned int     reserved_2:3;
}PREDBLK_BASEA;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     OffsetA:7;
unsigned int     reserved_1:3;
}PREDBLK_OFFSETA;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     StartA:7;
}PREDBLK_DEBPAR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     Rounding_Control:1;
unsigned int     Quarter_Sample:1;
}PREDBLK_MPEGCTL;

typedef struct 
{
unsigned int     Valid:1;
unsigned int     reserved_0:2;
unsigned int     Base_addr:26;
unsigned int     reserved_1:3;
}PREDBLK_RMEMDDR1;

typedef struct 
{
unsigned int     MBCnt_threshold:32;
}PREDBLK_RMEMDDR2;

typedef struct 
{
unsigned int     Valid:1;
unsigned int     reserved_0:17;
unsigned int     Start_Addr:7;
unsigned int     End_Addr:7;
}PREDBLK_RMEMCTL;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     URatio:15;
}PREDBLK_URATIO;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     VP6_1:1;
unsigned int     AutoSelectPMFlag:1;
unsigned int     BicubicFiltFlag:1;
unsigned int     Sample_var_thresh:10;
unsigned int     Max_vec_length:9;
unsigned int     Bicubic_filt_sel:4;
}PREDBLK_VP6CTRL;

typedef struct 
{
unsigned int     GenPulse:1;
unsigned int     PicCount:14;
unsigned int     MbAddrX:9;
unsigned int     MbAddrY:8;
}PREDBLK_DBUS;

typedef struct 
{
unsigned int     DbgCtrl:32;
}PREDBLK_DBUS2;

typedef struct 
{
unsigned int     DbgCtrl3:29;
unsigned int     DbgCtrl:3;
}PREDBLK_DBUS3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     SDMA2MSB:2;
unsigned int     RMEM2MSB:2;
}PREDBLK_DMAMSB;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     BaseAddr:12;
}PREDBLK_DMEMADR;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     DC_Quant:6;
unsigned int     reserved_1:7;
unsigned int     Div_Quant:17;
}PREDBLK_X8ILUQU;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     DC_Quant:7;
unsigned int     reserved_1:7;
unsigned int     Div_Quant:17;
}PREDBLK_X8ICHQU;

typedef struct 
{
unsigned int     TL:8;
unsigned int     TR:8;
unsigned int     BL:8;
unsigned int     BR:8;
}PREDBLK_X8ILFLT;

typedef struct 
{
unsigned int     TL:8;
unsigned int     TR:8;
unsigned int     BL:8;
unsigned int     BR:8;
}PREDBLK_X8ILFCR;

typedef struct 
{
unsigned int     TL:8;
unsigned int     TR:8;
unsigned int     BL:8;
unsigned int     BR:8;
}PREDBLK_X8ILFCC;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     BR:8;
}PREDBLK_X8ILFTP;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     Count:28;
}PREDBLK_DMEMOP;

typedef struct 
{
unsigned int     hw_enable:1;
unsigned int     reserved_0:30;
unsigned int     Pmem_idle:1;
}PREDBLK_SLICE_RESTART;

typedef struct 
{
unsigned int     sw_override:1;
unsigned int     reserved_0:8;
unsigned int     ddr_inb_rdadr:3;
unsigned int     ddr_out_rdadr:6;
unsigned int     inb_mbcnt:4;
unsigned int     out_mbcnt:4;
unsigned int     pmem_inb_mbptr:3;
unsigned int     pmem_out_mbptr:3;
}PREDBLK_SLICE_DBG0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     ddr_rng_rdptr:10;
unsigned int     ddr_rng_wrptr:10;
unsigned int     ddr_rng_size:10;
}PREDBLK_SLICE_DBG1;

#endif

#define PREDBLK_NEIGHBOR                                                             0x1800E800
#define PREDBLK_NEIGHBOR_reg_addr                                                    "0xB800E800"
#define PREDBLK_NEIGHBOR_reg                                                         0xB800E800
#define set_PREDBLK_NEIGHBOR_reg(data)   (*((volatile unsigned int*) PREDBLK_NEIGHBOR_reg)=data)
#define get_PREDBLK_NEIGHBOR_reg   (*((volatile unsigned int*) PREDBLK_NEIGHBOR_reg))
#define PREDBLK_NEIGHBOR_inst_adr                                                    "0x0000"
#define PREDBLK_NEIGHBOR_inst                                                        0x0000
#define PREDBLK_NEIGHBOR_Nhmem_Flush_shift                                           (24)
#define PREDBLK_NEIGHBOR_Nhmem_Flush_mask                                            (0x01000000)
#define PREDBLK_NEIGHBOR_Nhmem_Flush(data)                                           (0x01000000&((data)<<24))
#define PREDBLK_NEIGHBOR_Nhmem_Flush_src(data)                                       ((0x01000000&(data))>>24)
#define PREDBLK_NEIGHBOR_get_Nhmem_Flush(data)                                       ((0x01000000&(data))>>24)
#define PREDBLK_NEIGHBOR_RMEM_Rst_shift                                              (23)
#define PREDBLK_NEIGHBOR_RMEM_Rst_mask                                               (0x00800000)
#define PREDBLK_NEIGHBOR_RMEM_Rst(data)                                              (0x00800000&((data)<<23))
#define PREDBLK_NEIGHBOR_RMEM_Rst_src(data)                                          ((0x00800000&(data))>>23)
#define PREDBLK_NEIGHBOR_get_RMEM_Rst(data)                                          ((0x00800000&(data))>>23)
#define PREDBLK_NEIGHBOR_Deblk_xsfer_mode_shift                                      (22)
#define PREDBLK_NEIGHBOR_Deblk_xsfer_mode_mask                                       (0x00400000)
#define PREDBLK_NEIGHBOR_Deblk_xsfer_mode(data)                                      (0x00400000&((data)<<22))
#define PREDBLK_NEIGHBOR_Deblk_xsfer_mode_src(data)                                  ((0x00400000&(data))>>22)
#define PREDBLK_NEIGHBOR_get_Deblk_xsfer_mode(data)                                  ((0x00400000&(data))>>22)
#define PREDBLK_NEIGHBOR_Debug_mode_shift                                            (21)
#define PREDBLK_NEIGHBOR_Debug_mode_mask                                             (0x00200000)
#define PREDBLK_NEIGHBOR_Debug_mode(data)                                            (0x00200000&((data)<<21))
#define PREDBLK_NEIGHBOR_Debug_mode_src(data)                                        ((0x00200000&(data))>>21)
#define PREDBLK_NEIGHBOR_get_Debug_mode(data)                                        ((0x00200000&(data))>>21)
#define PREDBLK_NEIGHBOR_fmo_shift                                                   (20)
#define PREDBLK_NEIGHBOR_fmo_mask                                                    (0x00100000)
#define PREDBLK_NEIGHBOR_fmo(data)                                                   (0x00100000&((data)<<20))
#define PREDBLK_NEIGHBOR_fmo_src(data)                                               ((0x00100000&(data))>>20)
#define PREDBLK_NEIGHBOR_get_fmo(data)                                               ((0x00100000&(data))>>20)
#define PREDBLK_NEIGHBOR_Softrst_disable_shift                                       (15)
#define PREDBLK_NEIGHBOR_Softrst_disable_mask                                        (0x00008000)
#define PREDBLK_NEIGHBOR_Softrst_disable(data)                                       (0x00008000&((data)<<15))
#define PREDBLK_NEIGHBOR_Softrst_disable_src(data)                                   ((0x00008000&(data))>>15)
#define PREDBLK_NEIGHBOR_get_Softrst_disable(data)                                   ((0x00008000&(data))>>15)
#define PREDBLK_NEIGHBOR_New_slice_row_shift                                         (14)
#define PREDBLK_NEIGHBOR_New_slice_row_mask                                          (0x00004000)
#define PREDBLK_NEIGHBOR_New_slice_row(data)                                         (0x00004000&((data)<<14))
#define PREDBLK_NEIGHBOR_New_slice_row_src(data)                                     ((0x00004000&(data))>>14)
#define PREDBLK_NEIGHBOR_get_New_slice_row(data)                                     ((0x00004000&(data))>>14)
#define PREDBLK_NEIGHBOR_New_slice_mb_x_shift                                        (5)
#define PREDBLK_NEIGHBOR_New_slice_mb_x_mask                                         (0x00003FE0)
#define PREDBLK_NEIGHBOR_New_slice_mb_x(data)                                        (0x00003FE0&((data)<<5))
#define PREDBLK_NEIGHBOR_New_slice_mb_x_src(data)                                    ((0x00003FE0&(data))>>5)
#define PREDBLK_NEIGHBOR_get_New_slice_mb_x(data)                                    ((0x00003FE0&(data))>>5)
#define PREDBLK_NEIGHBOR_Sw_neighbor_enable_shift                                    (4)
#define PREDBLK_NEIGHBOR_Sw_neighbor_enable_mask                                     (0x00000010)
#define PREDBLK_NEIGHBOR_Sw_neighbor_enable(data)                                    (0x00000010&((data)<<4))
#define PREDBLK_NEIGHBOR_Sw_neighbor_enable_src(data)                                ((0x00000010&(data))>>4)
#define PREDBLK_NEIGHBOR_get_Sw_neighbor_enable(data)                                ((0x00000010&(data))>>4)
#define PREDBLK_NEIGHBOR_MbAddrA_available_shift                                     (3)
#define PREDBLK_NEIGHBOR_MbAddrA_available_mask                                      (0x00000008)
#define PREDBLK_NEIGHBOR_MbAddrA_available(data)                                     (0x00000008&((data)<<3))
#define PREDBLK_NEIGHBOR_MbAddrA_available_src(data)                                 ((0x00000008&(data))>>3)
#define PREDBLK_NEIGHBOR_get_MbAddrA_available(data)                                 ((0x00000008&(data))>>3)
#define PREDBLK_NEIGHBOR_MbAddrB_available_shift                                     (2)
#define PREDBLK_NEIGHBOR_MbAddrB_available_mask                                      (0x00000004)
#define PREDBLK_NEIGHBOR_MbAddrB_available(data)                                     (0x00000004&((data)<<2))
#define PREDBLK_NEIGHBOR_MbAddrB_available_src(data)                                 ((0x00000004&(data))>>2)
#define PREDBLK_NEIGHBOR_get_MbAddrB_available(data)                                 ((0x00000004&(data))>>2)
#define PREDBLK_NEIGHBOR_MbAddrC_available_shift                                     (1)
#define PREDBLK_NEIGHBOR_MbAddrC_available_mask                                      (0x00000002)
#define PREDBLK_NEIGHBOR_MbAddrC_available(data)                                     (0x00000002&((data)<<1))
#define PREDBLK_NEIGHBOR_MbAddrC_available_src(data)                                 ((0x00000002&(data))>>1)
#define PREDBLK_NEIGHBOR_get_MbAddrC_available(data)                                 ((0x00000002&(data))>>1)
#define PREDBLK_NEIGHBOR_MbAddrD_available_shift                                     (0)
#define PREDBLK_NEIGHBOR_MbAddrD_available_mask                                      (0x00000001)
#define PREDBLK_NEIGHBOR_MbAddrD_available(data)                                     (0x00000001&((data)<<0))
#define PREDBLK_NEIGHBOR_MbAddrD_available_src(data)                                 ((0x00000001&(data))>>0)
#define PREDBLK_NEIGHBOR_get_MbAddrD_available(data)                                 ((0x00000001&(data))>>0)


#define PREDBLK_VC1INTC1                                                             0x1800E804
#define PREDBLK_VC1INTC1_reg_addr                                                    "0xB800E804"
#define PREDBLK_VC1INTC1_reg                                                         0xB800E804
#define set_PREDBLK_VC1INTC1_reg(data)   (*((volatile unsigned int*) PREDBLK_VC1INTC1_reg)=data)
#define get_PREDBLK_VC1INTC1_reg   (*((volatile unsigned int*) PREDBLK_VC1INTC1_reg))
#define PREDBLK_VC1INTC1_inst_adr                                                    "0x0001"
#define PREDBLK_VC1INTC1_inst                                                        0x0001
#define PREDBLK_VC1INTC1_ic_mix_fcm_enable_shift                                     (17)
#define PREDBLK_VC1INTC1_ic_mix_fcm_enable_mask                                      (0x00020000)
#define PREDBLK_VC1INTC1_ic_mix_fcm_enable(data)                                     (0x00020000&((data)<<17))
#define PREDBLK_VC1INTC1_ic_mix_fcm_enable_src(data)                                 ((0x00020000&(data))>>17)
#define PREDBLK_VC1INTC1_get_ic_mix_fcm_enable(data)                                 ((0x00020000&(data))>>17)
#define PREDBLK_VC1INTC1_CONDOVER_shift                                              (15)
#define PREDBLK_VC1INTC1_CONDOVER_mask                                               (0x00018000)
#define PREDBLK_VC1INTC1_CONDOVER(data)                                              (0x00018000&((data)<<15))
#define PREDBLK_VC1INTC1_CONDOVER_src(data)                                          ((0x00018000&(data))>>15)
#define PREDBLK_VC1INTC1_get_CONDOVER(data)                                          ((0x00018000&(data))>>15)
#define PREDBLK_VC1INTC1_Rnd_ctrl_ovt_shift                                          (14)
#define PREDBLK_VC1INTC1_Rnd_ctrl_ovt_mask                                           (0x00004000)
#define PREDBLK_VC1INTC1_Rnd_ctrl_ovt(data)                                          (0x00004000&((data)<<14))
#define PREDBLK_VC1INTC1_Rnd_ctrl_ovt_src(data)                                      ((0x00004000&(data))>>14)
#define PREDBLK_VC1INTC1_get_Rnd_ctrl_ovt(data)                                      ((0x00004000&(data))>>14)
#define PREDBLK_VC1INTC1_RND_shift                                                   (13)
#define PREDBLK_VC1INTC1_RND_mask                                                    (0x00002000)
#define PREDBLK_VC1INTC1_RND(data)                                                   (0x00002000&((data)<<13))
#define PREDBLK_VC1INTC1_RND_src(data)                                               ((0x00002000&(data))>>13)
#define PREDBLK_VC1INTC1_get_RND(data)                                               ((0x00002000&(data))>>13)
#define PREDBLK_VC1INTC1_INTCOMP_shift                                               (12)
#define PREDBLK_VC1INTC1_INTCOMP_mask                                                (0x00001000)
#define PREDBLK_VC1INTC1_INTCOMP(data)                                               (0x00001000&((data)<<12))
#define PREDBLK_VC1INTC1_INTCOMP_src(data)                                           ((0x00001000&(data))>>12)
#define PREDBLK_VC1INTC1_get_INTCOMP(data)                                           ((0x00001000&(data))>>12)
#define PREDBLK_VC1INTC1_LUMSCALE0_shift                                             (6)
#define PREDBLK_VC1INTC1_LUMSCALE0_mask                                              (0x00000FC0)
#define PREDBLK_VC1INTC1_LUMSCALE0(data)                                             (0x00000FC0&((data)<<6))
#define PREDBLK_VC1INTC1_LUMSCALE0_src(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC1_get_LUMSCALE0(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC1_LUMSHIFT0_shift                                             (0)
#define PREDBLK_VC1INTC1_LUMSHIFT0_mask                                              (0x0000003F)
#define PREDBLK_VC1INTC1_LUMSHIFT0(data)                                             (0x0000003F&((data)<<0))
#define PREDBLK_VC1INTC1_LUMSHIFT0_src(data)                                         ((0x0000003F&(data))>>0)
#define PREDBLK_VC1INTC1_get_LUMSHIFT0(data)                                         ((0x0000003F&(data))>>0)


#define PREDBLK_VC1INTC2                                                             0x1800E808
#define PREDBLK_VC1INTC2_reg_addr                                                    "0xB800E808"
#define PREDBLK_VC1INTC2_reg                                                         0xB800E808
#define set_PREDBLK_VC1INTC2_reg(data)   (*((volatile unsigned int*) PREDBLK_VC1INTC2_reg)=data)
#define get_PREDBLK_VC1INTC2_reg   (*((volatile unsigned int*) PREDBLK_VC1INTC2_reg))
#define PREDBLK_VC1INTC2_inst_adr                                                    "0x0002"
#define PREDBLK_VC1INTC2_inst                                                        0x0002
#define PREDBLK_VC1INTC2_Ic_pass0_of_fwd_shift                                       (28)
#define PREDBLK_VC1INTC2_Ic_pass0_of_fwd_mask                                        (0xF0000000)
#define PREDBLK_VC1INTC2_Ic_pass0_of_fwd(data)                                       (0xF0000000&((data)<<28))
#define PREDBLK_VC1INTC2_Ic_pass0_of_fwd_src(data)                                   ((0xF0000000&(data))>>28)
#define PREDBLK_VC1INTC2_get_Ic_pass0_of_fwd(data)                                   ((0xF0000000&(data))>>28)
#define PREDBLK_VC1INTC2_Ic_pass1_of_fwd_shift                                       (24)
#define PREDBLK_VC1INTC2_Ic_pass1_of_fwd_mask                                        (0x0F000000)
#define PREDBLK_VC1INTC2_Ic_pass1_of_fwd(data)                                       (0x0F000000&((data)<<24))
#define PREDBLK_VC1INTC2_Ic_pass1_of_fwd_src(data)                                   ((0x0F000000&(data))>>24)
#define PREDBLK_VC1INTC2_get_Ic_pass1_of_fwd(data)                                   ((0x0F000000&(data))>>24)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_fwd_shift                                       (20)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_fwd_mask                                        (0x00F00000)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_fwd(data)                                       (0x00F00000&((data)<<20))
#define PREDBLK_VC1INTC2_Ic_pass0_sf_fwd_src(data)                                   ((0x00F00000&(data))>>20)
#define PREDBLK_VC1INTC2_get_Ic_pass0_sf_fwd(data)                                   ((0x00F00000&(data))>>20)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_fwd_shift                                       (16)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_fwd_mask                                        (0x000F0000)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_fwd(data)                                       (0x000F0000&((data)<<16))
#define PREDBLK_VC1INTC2_Ic_pass1_sf_fwd_src(data)                                   ((0x000F0000&(data))>>16)
#define PREDBLK_VC1INTC2_get_Ic_pass1_sf_fwd(data)                                   ((0x000F0000&(data))>>16)
#define PREDBLK_VC1INTC2_Ic_pass0_of_bwd_shift                                       (12)
#define PREDBLK_VC1INTC2_Ic_pass0_of_bwd_mask                                        (0x0000F000)
#define PREDBLK_VC1INTC2_Ic_pass0_of_bwd(data)                                       (0x0000F000&((data)<<12))
#define PREDBLK_VC1INTC2_Ic_pass0_of_bwd_src(data)                                   ((0x0000F000&(data))>>12)
#define PREDBLK_VC1INTC2_get_Ic_pass0_of_bwd(data)                                   ((0x0000F000&(data))>>12)
#define PREDBLK_VC1INTC2_Ic_pass1_of_bwd_shift                                       (8)
#define PREDBLK_VC1INTC2_Ic_pass1_of_bwd_mask                                        (0x00000F00)
#define PREDBLK_VC1INTC2_Ic_pass1_of_bwd(data)                                       (0x00000F00&((data)<<8))
#define PREDBLK_VC1INTC2_Ic_pass1_of_bwd_src(data)                                   ((0x00000F00&(data))>>8)
#define PREDBLK_VC1INTC2_get_Ic_pass1_of_bwd(data)                                   ((0x00000F00&(data))>>8)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_bwd_shift                                       (4)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_bwd_mask                                        (0x000000F0)
#define PREDBLK_VC1INTC2_Ic_pass0_sf_bwd(data)                                       (0x000000F0&((data)<<4))
#define PREDBLK_VC1INTC2_Ic_pass0_sf_bwd_src(data)                                   ((0x000000F0&(data))>>4)
#define PREDBLK_VC1INTC2_get_Ic_pass0_sf_bwd(data)                                   ((0x000000F0&(data))>>4)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_bwd_shift                                       (0)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_bwd_mask                                        (0x0000000F)
#define PREDBLK_VC1INTC2_Ic_pass1_sf_bwd(data)                                       (0x0000000F&((data)<<0))
#define PREDBLK_VC1INTC2_Ic_pass1_sf_bwd_src(data)                                   ((0x0000000F&(data))>>0)
#define PREDBLK_VC1INTC2_get_Ic_pass1_sf_bwd(data)                                   ((0x0000000F&(data))>>0)


#define PREDBLK_VC1INTC3                                                             0x1800E80C
#define PREDBLK_VC1INTC3_reg_addr                                                    "0xB800E80C"
#define PREDBLK_VC1INTC3_reg                                                         0xB800E80C
#define set_PREDBLK_VC1INTC3_reg(data)   (*((volatile unsigned int*) PREDBLK_VC1INTC3_reg)=data)
#define get_PREDBLK_VC1INTC3_reg   (*((volatile unsigned int*) PREDBLK_VC1INTC3_reg))
#define PREDBLK_VC1INTC3_inst_adr                                                    "0x0003"
#define PREDBLK_VC1INTC3_inst                                                        0x0003
#define PREDBLK_VC1INTC3_LUMSCALE1_shift                                             (18)
#define PREDBLK_VC1INTC3_LUMSCALE1_mask                                              (0x00FC0000)
#define PREDBLK_VC1INTC3_LUMSCALE1(data)                                             (0x00FC0000&((data)<<18))
#define PREDBLK_VC1INTC3_LUMSCALE1_src(data)                                         ((0x00FC0000&(data))>>18)
#define PREDBLK_VC1INTC3_get_LUMSCALE1(data)                                         ((0x00FC0000&(data))>>18)
#define PREDBLK_VC1INTC3_LUMSHIFT1_shift                                             (12)
#define PREDBLK_VC1INTC3_LUMSHIFT1_mask                                              (0x0003F000)
#define PREDBLK_VC1INTC3_LUMSHIFT1(data)                                             (0x0003F000&((data)<<12))
#define PREDBLK_VC1INTC3_LUMSHIFT1_src(data)                                         ((0x0003F000&(data))>>12)
#define PREDBLK_VC1INTC3_get_LUMSHIFT1(data)                                         ((0x0003F000&(data))>>12)
#define PREDBLK_VC1INTC3_LUMSCALE2_shift                                             (6)
#define PREDBLK_VC1INTC3_LUMSCALE2_mask                                              (0x00000FC0)
#define PREDBLK_VC1INTC3_LUMSCALE2(data)                                             (0x00000FC0&((data)<<6))
#define PREDBLK_VC1INTC3_LUMSCALE2_src(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC3_get_LUMSCALE2(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC3_LUMSHIFT2_shift                                             (0)
#define PREDBLK_VC1INTC3_LUMSHIFT2_mask                                              (0x0000003F)
#define PREDBLK_VC1INTC3_LUMSHIFT2(data)                                             (0x0000003F&((data)<<0))
#define PREDBLK_VC1INTC3_LUMSHIFT2_src(data)                                         ((0x0000003F&(data))>>0)
#define PREDBLK_VC1INTC3_get_LUMSHIFT2(data)                                         ((0x0000003F&(data))>>0)


#define PREDBLK_VC1INTC4                                                             0x1800E810
#define PREDBLK_VC1INTC4_reg_addr                                                    "0xB800E810"
#define PREDBLK_VC1INTC4_reg                                                         0xB800E810
#define set_PREDBLK_VC1INTC4_reg(data)   (*((volatile unsigned int*) PREDBLK_VC1INTC4_reg)=data)
#define get_PREDBLK_VC1INTC4_reg   (*((volatile unsigned int*) PREDBLK_VC1INTC4_reg))
#define PREDBLK_VC1INTC4_inst_adr                                                    "0x0004"
#define PREDBLK_VC1INTC4_inst                                                        0x0004
#define PREDBLK_VC1INTC4_LUMSCALE3_shift                                             (18)
#define PREDBLK_VC1INTC4_LUMSCALE3_mask                                              (0x00FC0000)
#define PREDBLK_VC1INTC4_LUMSCALE3(data)                                             (0x00FC0000&((data)<<18))
#define PREDBLK_VC1INTC4_LUMSCALE3_src(data)                                         ((0x00FC0000&(data))>>18)
#define PREDBLK_VC1INTC4_get_LUMSCALE3(data)                                         ((0x00FC0000&(data))>>18)
#define PREDBLK_VC1INTC4_LUMSHIFT3_shift                                             (12)
#define PREDBLK_VC1INTC4_LUMSHIFT3_mask                                              (0x0003F000)
#define PREDBLK_VC1INTC4_LUMSHIFT3(data)                                             (0x0003F000&((data)<<12))
#define PREDBLK_VC1INTC4_LUMSHIFT3_src(data)                                         ((0x0003F000&(data))>>12)
#define PREDBLK_VC1INTC4_get_LUMSHIFT3(data)                                         ((0x0003F000&(data))>>12)
#define PREDBLK_VC1INTC4_LUMSCALE4_shift                                             (6)
#define PREDBLK_VC1INTC4_LUMSCALE4_mask                                              (0x00000FC0)
#define PREDBLK_VC1INTC4_LUMSCALE4(data)                                             (0x00000FC0&((data)<<6))
#define PREDBLK_VC1INTC4_LUMSCALE4_src(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC4_get_LUMSCALE4(data)                                         ((0x00000FC0&(data))>>6)
#define PREDBLK_VC1INTC4_LUMSHIFT4_shift                                             (0)
#define PREDBLK_VC1INTC4_LUMSHIFT4_mask                                              (0x0000003F)
#define PREDBLK_VC1INTC4_LUMSHIFT4(data)                                             (0x0000003F&((data)<<0))
#define PREDBLK_VC1INTC4_LUMSHIFT4_src(data)                                         ((0x0000003F&(data))>>0)
#define PREDBLK_VC1INTC4_get_LUMSHIFT4(data)                                         ((0x0000003F&(data))>>0)


#define PREDBLK_NBINTRA0_0                                                           0x1800E814
#define PREDBLK_NBINTRA0_1                                                           0x1800E818
#define PREDBLK_NBINTRA0_2                                                           0x1800E81C
#define PREDBLK_NBINTRA0_3                                                           0x1800E820
#define PREDBLK_NBINTRA0_4                                                           0x1800E824
#define PREDBLK_NBINTRA0_5                                                           0x1800E828
#define PREDBLK_NBINTRA0_6                                                           0x1800E82C
#define PREDBLK_NBINTRA0_7                                                           0x1800E830
#define PREDBLK_NBINTRA0_8                                                           0x1800E834
#define PREDBLK_NBINTRA0_9                                                           0x1800E838
#define PREDBLK_NBINTRA0_10                                                           0x1800E83C
#define PREDBLK_NBINTRA0_11                                                           0x1800E840
#define PREDBLK_NBINTRA0_12                                                           0x1800E844
#define PREDBLK_NBINTRA0_13                                                           0x1800E848
#define PREDBLK_NBINTRA0_14                                                           0x1800E84C
#define PREDBLK_NBINTRA0_15                                                           0x1800E850
#define PREDBLK_NBINTRA0_0_reg_addr                                                  "0xB800E814"
#define PREDBLK_NBINTRA0_1_reg_addr                                                  "0xB800E818"
#define PREDBLK_NBINTRA0_2_reg_addr                                                  "0xB800E81C"
#define PREDBLK_NBINTRA0_3_reg_addr                                                  "0xB800E820"
#define PREDBLK_NBINTRA0_4_reg_addr                                                  "0xB800E824"
#define PREDBLK_NBINTRA0_5_reg_addr                                                  "0xB800E828"
#define PREDBLK_NBINTRA0_6_reg_addr                                                  "0xB800E82C"
#define PREDBLK_NBINTRA0_7_reg_addr                                                  "0xB800E830"
#define PREDBLK_NBINTRA0_8_reg_addr                                                  "0xB800E834"
#define PREDBLK_NBINTRA0_9_reg_addr                                                  "0xB800E838"
#define PREDBLK_NBINTRA0_10_reg_addr                                                  "0xB800E83C"
#define PREDBLK_NBINTRA0_11_reg_addr                                                  "0xB800E840"
#define PREDBLK_NBINTRA0_12_reg_addr                                                  "0xB800E844"
#define PREDBLK_NBINTRA0_13_reg_addr                                                  "0xB800E848"
#define PREDBLK_NBINTRA0_14_reg_addr                                                  "0xB800E84C"
#define PREDBLK_NBINTRA0_15_reg_addr                                                  "0xB800E850"
#define PREDBLK_NBINTRA0_0_reg                                                       0xB800E814
#define PREDBLK_NBINTRA0_1_reg                                                       0xB800E818
#define PREDBLK_NBINTRA0_2_reg                                                       0xB800E81C
#define PREDBLK_NBINTRA0_3_reg                                                       0xB800E820
#define PREDBLK_NBINTRA0_4_reg                                                       0xB800E824
#define PREDBLK_NBINTRA0_5_reg                                                       0xB800E828
#define PREDBLK_NBINTRA0_6_reg                                                       0xB800E82C
#define PREDBLK_NBINTRA0_7_reg                                                       0xB800E830
#define PREDBLK_NBINTRA0_8_reg                                                       0xB800E834
#define PREDBLK_NBINTRA0_9_reg                                                       0xB800E838
#define PREDBLK_NBINTRA0_10_reg                                                       0xB800E83C
#define PREDBLK_NBINTRA0_11_reg                                                       0xB800E840
#define PREDBLK_NBINTRA0_12_reg                                                       0xB800E844
#define PREDBLK_NBINTRA0_13_reg                                                       0xB800E848
#define PREDBLK_NBINTRA0_14_reg                                                       0xB800E84C
#define PREDBLK_NBINTRA0_15_reg                                                       0xB800E850
#define set_PREDBLK_NBINTRA0_0_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_0_reg)=data)
#define set_PREDBLK_NBINTRA0_1_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_1_reg)=data)
#define set_PREDBLK_NBINTRA0_2_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_2_reg)=data)
#define set_PREDBLK_NBINTRA0_3_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_3_reg)=data)
#define set_PREDBLK_NBINTRA0_4_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_4_reg)=data)
#define set_PREDBLK_NBINTRA0_5_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_5_reg)=data)
#define set_PREDBLK_NBINTRA0_6_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_6_reg)=data)
#define set_PREDBLK_NBINTRA0_7_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_7_reg)=data)
#define set_PREDBLK_NBINTRA0_8_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_8_reg)=data)
#define set_PREDBLK_NBINTRA0_9_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_9_reg)=data)
#define set_PREDBLK_NBINTRA0_10_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_10_reg)=data)
#define set_PREDBLK_NBINTRA0_11_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_11_reg)=data)
#define set_PREDBLK_NBINTRA0_12_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_12_reg)=data)
#define set_PREDBLK_NBINTRA0_13_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_13_reg)=data)
#define set_PREDBLK_NBINTRA0_14_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_14_reg)=data)
#define set_PREDBLK_NBINTRA0_15_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA0_15_reg)=data)
#define get_PREDBLK_NBINTRA0_0_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_0_reg))
#define get_PREDBLK_NBINTRA0_1_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_1_reg))
#define get_PREDBLK_NBINTRA0_2_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_2_reg))
#define get_PREDBLK_NBINTRA0_3_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_3_reg))
#define get_PREDBLK_NBINTRA0_4_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_4_reg))
#define get_PREDBLK_NBINTRA0_5_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_5_reg))
#define get_PREDBLK_NBINTRA0_6_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_6_reg))
#define get_PREDBLK_NBINTRA0_7_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_7_reg))
#define get_PREDBLK_NBINTRA0_8_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_8_reg))
#define get_PREDBLK_NBINTRA0_9_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_9_reg))
#define get_PREDBLK_NBINTRA0_10_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_10_reg))
#define get_PREDBLK_NBINTRA0_11_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_11_reg))
#define get_PREDBLK_NBINTRA0_12_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_12_reg))
#define get_PREDBLK_NBINTRA0_13_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_13_reg))
#define get_PREDBLK_NBINTRA0_14_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_14_reg))
#define get_PREDBLK_NBINTRA0_15_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA0_15_reg))
#define PREDBLK_NBINTRA0_0_inst_adr                                                  "0x0005"
#define PREDBLK_NBINTRA0_1_inst_adr                                                  "0x0006"
#define PREDBLK_NBINTRA0_2_inst_adr                                                  "0x0007"
#define PREDBLK_NBINTRA0_3_inst_adr                                                  "0x0008"
#define PREDBLK_NBINTRA0_4_inst_adr                                                  "0x0009"
#define PREDBLK_NBINTRA0_5_inst_adr                                                  "0x000A"
#define PREDBLK_NBINTRA0_6_inst_adr                                                  "0x000B"
#define PREDBLK_NBINTRA0_7_inst_adr                                                  "0x000C"
#define PREDBLK_NBINTRA0_8_inst_adr                                                  "0x000D"
#define PREDBLK_NBINTRA0_9_inst_adr                                                  "0x000E"
#define PREDBLK_NBINTRA0_10_inst_adr                                                  "0x000F"
#define PREDBLK_NBINTRA0_11_inst_adr                                                  "0x0010"
#define PREDBLK_NBINTRA0_12_inst_adr                                                  "0x0011"
#define PREDBLK_NBINTRA0_13_inst_adr                                                  "0x0012"
#define PREDBLK_NBINTRA0_14_inst_adr                                                  "0x0013"
#define PREDBLK_NBINTRA0_15_inst_adr                                                  "0x0014"
#define PREDBLK_NBINTRA0_0_inst                                                      0x0005
#define PREDBLK_NBINTRA0_1_inst                                                      0x0006
#define PREDBLK_NBINTRA0_2_inst                                                      0x0007
#define PREDBLK_NBINTRA0_3_inst                                                      0x0008
#define PREDBLK_NBINTRA0_4_inst                                                      0x0009
#define PREDBLK_NBINTRA0_5_inst                                                      0x000A
#define PREDBLK_NBINTRA0_6_inst                                                      0x000B
#define PREDBLK_NBINTRA0_7_inst                                                      0x000C
#define PREDBLK_NBINTRA0_8_inst                                                      0x000D
#define PREDBLK_NBINTRA0_9_inst                                                      0x000E
#define PREDBLK_NBINTRA0_10_inst                                                      0x000F
#define PREDBLK_NBINTRA0_11_inst                                                      0x0010
#define PREDBLK_NBINTRA0_12_inst                                                      0x0011
#define PREDBLK_NBINTRA0_13_inst                                                      0x0012
#define PREDBLK_NBINTRA0_14_inst                                                      0x0013
#define PREDBLK_NBINTRA0_15_inst                                                      0x0014
#define PREDBLK_NBINTRA0_intra_flag_shift                                            (0)
#define PREDBLK_NBINTRA0_intra_flag_mask                                             (0xFFFFFFFF)
#define PREDBLK_NBINTRA0_intra_flag(data)                                            (0xFFFFFFFF&((data)<<0))
#define PREDBLK_NBINTRA0_intra_flag_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_NBINTRA0_get_intra_flag(data)                                        ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_NBINTRA1_0                                                           0x1800E854
#define PREDBLK_NBINTRA1_1                                                           0x1800E858
#define PREDBLK_NBINTRA1_2                                                           0x1800E85C
#define PREDBLK_NBINTRA1_3                                                           0x1800E860
#define PREDBLK_NBINTRA1_4                                                           0x1800E864
#define PREDBLK_NBINTRA1_5                                                           0x1800E868
#define PREDBLK_NBINTRA1_6                                                           0x1800E86C
#define PREDBLK_NBINTRA1_7                                                           0x1800E870
#define PREDBLK_NBINTRA1_8                                                           0x1800E874
#define PREDBLK_NBINTRA1_9                                                           0x1800E878
#define PREDBLK_NBINTRA1_10                                                           0x1800E87C
#define PREDBLK_NBINTRA1_11                                                           0x1800E880
#define PREDBLK_NBINTRA1_12                                                           0x1800E884
#define PREDBLK_NBINTRA1_13                                                           0x1800E888
#define PREDBLK_NBINTRA1_14                                                           0x1800E88C
#define PREDBLK_NBINTRA1_15                                                           0x1800E890
#define PREDBLK_NBINTRA1_0_reg_addr                                                  "0xB800E854"
#define PREDBLK_NBINTRA1_1_reg_addr                                                  "0xB800E858"
#define PREDBLK_NBINTRA1_2_reg_addr                                                  "0xB800E85C"
#define PREDBLK_NBINTRA1_3_reg_addr                                                  "0xB800E860"
#define PREDBLK_NBINTRA1_4_reg_addr                                                  "0xB800E864"
#define PREDBLK_NBINTRA1_5_reg_addr                                                  "0xB800E868"
#define PREDBLK_NBINTRA1_6_reg_addr                                                  "0xB800E86C"
#define PREDBLK_NBINTRA1_7_reg_addr                                                  "0xB800E870"
#define PREDBLK_NBINTRA1_8_reg_addr                                                  "0xB800E874"
#define PREDBLK_NBINTRA1_9_reg_addr                                                  "0xB800E878"
#define PREDBLK_NBINTRA1_10_reg_addr                                                  "0xB800E87C"
#define PREDBLK_NBINTRA1_11_reg_addr                                                  "0xB800E880"
#define PREDBLK_NBINTRA1_12_reg_addr                                                  "0xB800E884"
#define PREDBLK_NBINTRA1_13_reg_addr                                                  "0xB800E888"
#define PREDBLK_NBINTRA1_14_reg_addr                                                  "0xB800E88C"
#define PREDBLK_NBINTRA1_15_reg_addr                                                  "0xB800E890"
#define PREDBLK_NBINTRA1_0_reg                                                       0xB800E854
#define PREDBLK_NBINTRA1_1_reg                                                       0xB800E858
#define PREDBLK_NBINTRA1_2_reg                                                       0xB800E85C
#define PREDBLK_NBINTRA1_3_reg                                                       0xB800E860
#define PREDBLK_NBINTRA1_4_reg                                                       0xB800E864
#define PREDBLK_NBINTRA1_5_reg                                                       0xB800E868
#define PREDBLK_NBINTRA1_6_reg                                                       0xB800E86C
#define PREDBLK_NBINTRA1_7_reg                                                       0xB800E870
#define PREDBLK_NBINTRA1_8_reg                                                       0xB800E874
#define PREDBLK_NBINTRA1_9_reg                                                       0xB800E878
#define PREDBLK_NBINTRA1_10_reg                                                       0xB800E87C
#define PREDBLK_NBINTRA1_11_reg                                                       0xB800E880
#define PREDBLK_NBINTRA1_12_reg                                                       0xB800E884
#define PREDBLK_NBINTRA1_13_reg                                                       0xB800E888
#define PREDBLK_NBINTRA1_14_reg                                                       0xB800E88C
#define PREDBLK_NBINTRA1_15_reg                                                       0xB800E890
#define set_PREDBLK_NBINTRA1_0_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_0_reg)=data)
#define set_PREDBLK_NBINTRA1_1_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_1_reg)=data)
#define set_PREDBLK_NBINTRA1_2_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_2_reg)=data)
#define set_PREDBLK_NBINTRA1_3_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_3_reg)=data)
#define set_PREDBLK_NBINTRA1_4_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_4_reg)=data)
#define set_PREDBLK_NBINTRA1_5_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_5_reg)=data)
#define set_PREDBLK_NBINTRA1_6_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_6_reg)=data)
#define set_PREDBLK_NBINTRA1_7_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_7_reg)=data)
#define set_PREDBLK_NBINTRA1_8_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_8_reg)=data)
#define set_PREDBLK_NBINTRA1_9_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_9_reg)=data)
#define set_PREDBLK_NBINTRA1_10_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_10_reg)=data)
#define set_PREDBLK_NBINTRA1_11_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_11_reg)=data)
#define set_PREDBLK_NBINTRA1_12_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_12_reg)=data)
#define set_PREDBLK_NBINTRA1_13_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_13_reg)=data)
#define set_PREDBLK_NBINTRA1_14_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_14_reg)=data)
#define set_PREDBLK_NBINTRA1_15_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRA1_15_reg)=data)
#define get_PREDBLK_NBINTRA1_0_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_0_reg))
#define get_PREDBLK_NBINTRA1_1_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_1_reg))
#define get_PREDBLK_NBINTRA1_2_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_2_reg))
#define get_PREDBLK_NBINTRA1_3_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_3_reg))
#define get_PREDBLK_NBINTRA1_4_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_4_reg))
#define get_PREDBLK_NBINTRA1_5_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_5_reg))
#define get_PREDBLK_NBINTRA1_6_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_6_reg))
#define get_PREDBLK_NBINTRA1_7_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_7_reg))
#define get_PREDBLK_NBINTRA1_8_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_8_reg))
#define get_PREDBLK_NBINTRA1_9_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_9_reg))
#define get_PREDBLK_NBINTRA1_10_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_10_reg))
#define get_PREDBLK_NBINTRA1_11_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_11_reg))
#define get_PREDBLK_NBINTRA1_12_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_12_reg))
#define get_PREDBLK_NBINTRA1_13_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_13_reg))
#define get_PREDBLK_NBINTRA1_14_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_14_reg))
#define get_PREDBLK_NBINTRA1_15_reg   (*((volatile unsigned int*) PREDBLK_NBINTRA1_15_reg))
#define PREDBLK_NBINTRA1_0_inst_adr                                                  "0x0015"
#define PREDBLK_NBINTRA1_1_inst_adr                                                  "0x0016"
#define PREDBLK_NBINTRA1_2_inst_adr                                                  "0x0017"
#define PREDBLK_NBINTRA1_3_inst_adr                                                  "0x0018"
#define PREDBLK_NBINTRA1_4_inst_adr                                                  "0x0019"
#define PREDBLK_NBINTRA1_5_inst_adr                                                  "0x001A"
#define PREDBLK_NBINTRA1_6_inst_adr                                                  "0x001B"
#define PREDBLK_NBINTRA1_7_inst_adr                                                  "0x001C"
#define PREDBLK_NBINTRA1_8_inst_adr                                                  "0x001D"
#define PREDBLK_NBINTRA1_9_inst_adr                                                  "0x001E"
#define PREDBLK_NBINTRA1_10_inst_adr                                                  "0x001F"
#define PREDBLK_NBINTRA1_11_inst_adr                                                  "0x0020"
#define PREDBLK_NBINTRA1_12_inst_adr                                                  "0x0021"
#define PREDBLK_NBINTRA1_13_inst_adr                                                  "0x0022"
#define PREDBLK_NBINTRA1_14_inst_adr                                                  "0x0023"
#define PREDBLK_NBINTRA1_15_inst_adr                                                  "0x0024"
#define PREDBLK_NBINTRA1_0_inst                                                      0x0015
#define PREDBLK_NBINTRA1_1_inst                                                      0x0016
#define PREDBLK_NBINTRA1_2_inst                                                      0x0017
#define PREDBLK_NBINTRA1_3_inst                                                      0x0018
#define PREDBLK_NBINTRA1_4_inst                                                      0x0019
#define PREDBLK_NBINTRA1_5_inst                                                      0x001A
#define PREDBLK_NBINTRA1_6_inst                                                      0x001B
#define PREDBLK_NBINTRA1_7_inst                                                      0x001C
#define PREDBLK_NBINTRA1_8_inst                                                      0x001D
#define PREDBLK_NBINTRA1_9_inst                                                      0x001E
#define PREDBLK_NBINTRA1_10_inst                                                      0x001F
#define PREDBLK_NBINTRA1_11_inst                                                      0x0020
#define PREDBLK_NBINTRA1_12_inst                                                      0x0021
#define PREDBLK_NBINTRA1_13_inst                                                      0x0022
#define PREDBLK_NBINTRA1_14_inst                                                      0x0023
#define PREDBLK_NBINTRA1_15_inst                                                      0x0024
#define PREDBLK_NBINTRA1_intra_flag_shift                                            (0)
#define PREDBLK_NBINTRA1_intra_flag_mask                                             (0xFFFFFFFF)
#define PREDBLK_NBINTRA1_intra_flag(data)                                            (0xFFFFFFFF&((data)<<0))
#define PREDBLK_NBINTRA1_intra_flag_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_NBINTRA1_get_intra_flag(data)                                        ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_NBINTRACH_0                                                          0x1800E894
#define PREDBLK_NBINTRACH_1                                                          0x1800E898
#define PREDBLK_NBINTRACH_2                                                          0x1800E89C
#define PREDBLK_NBINTRACH_3                                                          0x1800E8A0
#define PREDBLK_NBINTRACH_4                                                          0x1800E8A4
#define PREDBLK_NBINTRACH_5                                                          0x1800E8A8
#define PREDBLK_NBINTRACH_6                                                          0x1800E8AC
#define PREDBLK_NBINTRACH_7                                                          0x1800E8B0
#define PREDBLK_NBINTRACH_8                                                          0x1800E8B4
#define PREDBLK_NBINTRACH_9                                                          0x1800E8B8
#define PREDBLK_NBINTRACH_10                                                          0x1800E8BC
#define PREDBLK_NBINTRACH_11                                                          0x1800E8C0
#define PREDBLK_NBINTRACH_12                                                          0x1800E8C4
#define PREDBLK_NBINTRACH_13                                                          0x1800E8C8
#define PREDBLK_NBINTRACH_14                                                          0x1800E8CC
#define PREDBLK_NBINTRACH_15                                                          0x1800E8D0
#define PREDBLK_NBINTRACH_0_reg_addr                                                 "0xB800E894"
#define PREDBLK_NBINTRACH_1_reg_addr                                                 "0xB800E898"
#define PREDBLK_NBINTRACH_2_reg_addr                                                 "0xB800E89C"
#define PREDBLK_NBINTRACH_3_reg_addr                                                 "0xB800E8A0"
#define PREDBLK_NBINTRACH_4_reg_addr                                                 "0xB800E8A4"
#define PREDBLK_NBINTRACH_5_reg_addr                                                 "0xB800E8A8"
#define PREDBLK_NBINTRACH_6_reg_addr                                                 "0xB800E8AC"
#define PREDBLK_NBINTRACH_7_reg_addr                                                 "0xB800E8B0"
#define PREDBLK_NBINTRACH_8_reg_addr                                                 "0xB800E8B4"
#define PREDBLK_NBINTRACH_9_reg_addr                                                 "0xB800E8B8"
#define PREDBLK_NBINTRACH_10_reg_addr                                                 "0xB800E8BC"
#define PREDBLK_NBINTRACH_11_reg_addr                                                 "0xB800E8C0"
#define PREDBLK_NBINTRACH_12_reg_addr                                                 "0xB800E8C4"
#define PREDBLK_NBINTRACH_13_reg_addr                                                 "0xB800E8C8"
#define PREDBLK_NBINTRACH_14_reg_addr                                                 "0xB800E8CC"
#define PREDBLK_NBINTRACH_15_reg_addr                                                 "0xB800E8D0"
#define PREDBLK_NBINTRACH_0_reg                                                      0xB800E894
#define PREDBLK_NBINTRACH_1_reg                                                      0xB800E898
#define PREDBLK_NBINTRACH_2_reg                                                      0xB800E89C
#define PREDBLK_NBINTRACH_3_reg                                                      0xB800E8A0
#define PREDBLK_NBINTRACH_4_reg                                                      0xB800E8A4
#define PREDBLK_NBINTRACH_5_reg                                                      0xB800E8A8
#define PREDBLK_NBINTRACH_6_reg                                                      0xB800E8AC
#define PREDBLK_NBINTRACH_7_reg                                                      0xB800E8B0
#define PREDBLK_NBINTRACH_8_reg                                                      0xB800E8B4
#define PREDBLK_NBINTRACH_9_reg                                                      0xB800E8B8
#define PREDBLK_NBINTRACH_10_reg                                                      0xB800E8BC
#define PREDBLK_NBINTRACH_11_reg                                                      0xB800E8C0
#define PREDBLK_NBINTRACH_12_reg                                                      0xB800E8C4
#define PREDBLK_NBINTRACH_13_reg                                                      0xB800E8C8
#define PREDBLK_NBINTRACH_14_reg                                                      0xB800E8CC
#define PREDBLK_NBINTRACH_15_reg                                                      0xB800E8D0
#define set_PREDBLK_NBINTRACH_0_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_0_reg)=data)
#define set_PREDBLK_NBINTRACH_1_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_1_reg)=data)
#define set_PREDBLK_NBINTRACH_2_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_2_reg)=data)
#define set_PREDBLK_NBINTRACH_3_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_3_reg)=data)
#define set_PREDBLK_NBINTRACH_4_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_4_reg)=data)
#define set_PREDBLK_NBINTRACH_5_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_5_reg)=data)
#define set_PREDBLK_NBINTRACH_6_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_6_reg)=data)
#define set_PREDBLK_NBINTRACH_7_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_7_reg)=data)
#define set_PREDBLK_NBINTRACH_8_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_8_reg)=data)
#define set_PREDBLK_NBINTRACH_9_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_9_reg)=data)
#define set_PREDBLK_NBINTRACH_10_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_10_reg)=data)
#define set_PREDBLK_NBINTRACH_11_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_11_reg)=data)
#define set_PREDBLK_NBINTRACH_12_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_12_reg)=data)
#define set_PREDBLK_NBINTRACH_13_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_13_reg)=data)
#define set_PREDBLK_NBINTRACH_14_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_14_reg)=data)
#define set_PREDBLK_NBINTRACH_15_reg(data)   (*((volatile unsigned int*) PREDBLK_NBINTRACH_15_reg)=data)
#define get_PREDBLK_NBINTRACH_0_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_0_reg))
#define get_PREDBLK_NBINTRACH_1_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_1_reg))
#define get_PREDBLK_NBINTRACH_2_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_2_reg))
#define get_PREDBLK_NBINTRACH_3_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_3_reg))
#define get_PREDBLK_NBINTRACH_4_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_4_reg))
#define get_PREDBLK_NBINTRACH_5_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_5_reg))
#define get_PREDBLK_NBINTRACH_6_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_6_reg))
#define get_PREDBLK_NBINTRACH_7_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_7_reg))
#define get_PREDBLK_NBINTRACH_8_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_8_reg))
#define get_PREDBLK_NBINTRACH_9_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_9_reg))
#define get_PREDBLK_NBINTRACH_10_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_10_reg))
#define get_PREDBLK_NBINTRACH_11_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_11_reg))
#define get_PREDBLK_NBINTRACH_12_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_12_reg))
#define get_PREDBLK_NBINTRACH_13_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_13_reg))
#define get_PREDBLK_NBINTRACH_14_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_14_reg))
#define get_PREDBLK_NBINTRACH_15_reg   (*((volatile unsigned int*) PREDBLK_NBINTRACH_15_reg))
#define PREDBLK_NBINTRACH_0_inst_adr                                                 "0x0025"
#define PREDBLK_NBINTRACH_1_inst_adr                                                 "0x0026"
#define PREDBLK_NBINTRACH_2_inst_adr                                                 "0x0027"
#define PREDBLK_NBINTRACH_3_inst_adr                                                 "0x0028"
#define PREDBLK_NBINTRACH_4_inst_adr                                                 "0x0029"
#define PREDBLK_NBINTRACH_5_inst_adr                                                 "0x002A"
#define PREDBLK_NBINTRACH_6_inst_adr                                                 "0x002B"
#define PREDBLK_NBINTRACH_7_inst_adr                                                 "0x002C"
#define PREDBLK_NBINTRACH_8_inst_adr                                                 "0x002D"
#define PREDBLK_NBINTRACH_9_inst_adr                                                 "0x002E"
#define PREDBLK_NBINTRACH_10_inst_adr                                                 "0x002F"
#define PREDBLK_NBINTRACH_11_inst_adr                                                 "0x0030"
#define PREDBLK_NBINTRACH_12_inst_adr                                                 "0x0031"
#define PREDBLK_NBINTRACH_13_inst_adr                                                 "0x0032"
#define PREDBLK_NBINTRACH_14_inst_adr                                                 "0x0033"
#define PREDBLK_NBINTRACH_15_inst_adr                                                 "0x0034"
#define PREDBLK_NBINTRACH_0_inst                                                     0x0025
#define PREDBLK_NBINTRACH_1_inst                                                     0x0026
#define PREDBLK_NBINTRACH_2_inst                                                     0x0027
#define PREDBLK_NBINTRACH_3_inst                                                     0x0028
#define PREDBLK_NBINTRACH_4_inst                                                     0x0029
#define PREDBLK_NBINTRACH_5_inst                                                     0x002A
#define PREDBLK_NBINTRACH_6_inst                                                     0x002B
#define PREDBLK_NBINTRACH_7_inst                                                     0x002C
#define PREDBLK_NBINTRACH_8_inst                                                     0x002D
#define PREDBLK_NBINTRACH_9_inst                                                     0x002E
#define PREDBLK_NBINTRACH_10_inst                                                     0x002F
#define PREDBLK_NBINTRACH_11_inst                                                     0x0030
#define PREDBLK_NBINTRACH_12_inst                                                     0x0031
#define PREDBLK_NBINTRACH_13_inst                                                     0x0032
#define PREDBLK_NBINTRACH_14_inst                                                     0x0033
#define PREDBLK_NBINTRACH_15_inst                                                     0x0034
#define PREDBLK_NBINTRACH_intra_flag_shift                                           (0)
#define PREDBLK_NBINTRACH_intra_flag_mask                                            (0xFFFFFFFF)
#define PREDBLK_NBINTRACH_intra_flag(data)                                           (0xFFFFFFFF&((data)<<0))
#define PREDBLK_NBINTRACH_intra_flag_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_NBINTRACH_get_intra_flag(data)                                       ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_NBFIELDOV_0                                                          0x1800E8D4
#define PREDBLK_NBFIELDOV_1                                                          0x1800E8D8
#define PREDBLK_NBFIELDOV_2                                                          0x1800E8DC
#define PREDBLK_NBFIELDOV_3                                                          0x1800E8E0
#define PREDBLK_NBFIELDOV_4                                                          0x1800E8E4
#define PREDBLK_NBFIELDOV_5                                                          0x1800E8E8
#define PREDBLK_NBFIELDOV_6                                                          0x1800E8EC
#define PREDBLK_NBFIELDOV_7                                                          0x1800E8F0
#define PREDBLK_NBFIELDOV_8                                                          0x1800E8F4
#define PREDBLK_NBFIELDOV_9                                                          0x1800E8F8
#define PREDBLK_NBFIELDOV_10                                                          0x1800E8FC
#define PREDBLK_NBFIELDOV_11                                                          0x1800E900
#define PREDBLK_NBFIELDOV_12                                                          0x1800E904
#define PREDBLK_NBFIELDOV_13                                                          0x1800E908
#define PREDBLK_NBFIELDOV_14                                                          0x1800E90C
#define PREDBLK_NBFIELDOV_15                                                          0x1800E910
#define PREDBLK_NBFIELDOV_0_reg_addr                                                 "0xB800E8D4"
#define PREDBLK_NBFIELDOV_1_reg_addr                                                 "0xB800E8D8"
#define PREDBLK_NBFIELDOV_2_reg_addr                                                 "0xB800E8DC"
#define PREDBLK_NBFIELDOV_3_reg_addr                                                 "0xB800E8E0"
#define PREDBLK_NBFIELDOV_4_reg_addr                                                 "0xB800E8E4"
#define PREDBLK_NBFIELDOV_5_reg_addr                                                 "0xB800E8E8"
#define PREDBLK_NBFIELDOV_6_reg_addr                                                 "0xB800E8EC"
#define PREDBLK_NBFIELDOV_7_reg_addr                                                 "0xB800E8F0"
#define PREDBLK_NBFIELDOV_8_reg_addr                                                 "0xB800E8F4"
#define PREDBLK_NBFIELDOV_9_reg_addr                                                 "0xB800E8F8"
#define PREDBLK_NBFIELDOV_10_reg_addr                                                 "0xB800E8FC"
#define PREDBLK_NBFIELDOV_11_reg_addr                                                 "0xB800E900"
#define PREDBLK_NBFIELDOV_12_reg_addr                                                 "0xB800E904"
#define PREDBLK_NBFIELDOV_13_reg_addr                                                 "0xB800E908"
#define PREDBLK_NBFIELDOV_14_reg_addr                                                 "0xB800E90C"
#define PREDBLK_NBFIELDOV_15_reg_addr                                                 "0xB800E910"
#define PREDBLK_NBFIELDOV_0_reg                                                      0xB800E8D4
#define PREDBLK_NBFIELDOV_1_reg                                                      0xB800E8D8
#define PREDBLK_NBFIELDOV_2_reg                                                      0xB800E8DC
#define PREDBLK_NBFIELDOV_3_reg                                                      0xB800E8E0
#define PREDBLK_NBFIELDOV_4_reg                                                      0xB800E8E4
#define PREDBLK_NBFIELDOV_5_reg                                                      0xB800E8E8
#define PREDBLK_NBFIELDOV_6_reg                                                      0xB800E8EC
#define PREDBLK_NBFIELDOV_7_reg                                                      0xB800E8F0
#define PREDBLK_NBFIELDOV_8_reg                                                      0xB800E8F4
#define PREDBLK_NBFIELDOV_9_reg                                                      0xB800E8F8
#define PREDBLK_NBFIELDOV_10_reg                                                      0xB800E8FC
#define PREDBLK_NBFIELDOV_11_reg                                                      0xB800E900
#define PREDBLK_NBFIELDOV_12_reg                                                      0xB800E904
#define PREDBLK_NBFIELDOV_13_reg                                                      0xB800E908
#define PREDBLK_NBFIELDOV_14_reg                                                      0xB800E90C
#define PREDBLK_NBFIELDOV_15_reg                                                      0xB800E910
#define set_PREDBLK_NBFIELDOV_0_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_0_reg)=data)
#define set_PREDBLK_NBFIELDOV_1_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_1_reg)=data)
#define set_PREDBLK_NBFIELDOV_2_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_2_reg)=data)
#define set_PREDBLK_NBFIELDOV_3_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_3_reg)=data)
#define set_PREDBLK_NBFIELDOV_4_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_4_reg)=data)
#define set_PREDBLK_NBFIELDOV_5_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_5_reg)=data)
#define set_PREDBLK_NBFIELDOV_6_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_6_reg)=data)
#define set_PREDBLK_NBFIELDOV_7_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_7_reg)=data)
#define set_PREDBLK_NBFIELDOV_8_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_8_reg)=data)
#define set_PREDBLK_NBFIELDOV_9_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_9_reg)=data)
#define set_PREDBLK_NBFIELDOV_10_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_10_reg)=data)
#define set_PREDBLK_NBFIELDOV_11_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_11_reg)=data)
#define set_PREDBLK_NBFIELDOV_12_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_12_reg)=data)
#define set_PREDBLK_NBFIELDOV_13_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_13_reg)=data)
#define set_PREDBLK_NBFIELDOV_14_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_14_reg)=data)
#define set_PREDBLK_NBFIELDOV_15_reg(data)   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_15_reg)=data)
#define get_PREDBLK_NBFIELDOV_0_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_0_reg))
#define get_PREDBLK_NBFIELDOV_1_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_1_reg))
#define get_PREDBLK_NBFIELDOV_2_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_2_reg))
#define get_PREDBLK_NBFIELDOV_3_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_3_reg))
#define get_PREDBLK_NBFIELDOV_4_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_4_reg))
#define get_PREDBLK_NBFIELDOV_5_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_5_reg))
#define get_PREDBLK_NBFIELDOV_6_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_6_reg))
#define get_PREDBLK_NBFIELDOV_7_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_7_reg))
#define get_PREDBLK_NBFIELDOV_8_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_8_reg))
#define get_PREDBLK_NBFIELDOV_9_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_9_reg))
#define get_PREDBLK_NBFIELDOV_10_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_10_reg))
#define get_PREDBLK_NBFIELDOV_11_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_11_reg))
#define get_PREDBLK_NBFIELDOV_12_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_12_reg))
#define get_PREDBLK_NBFIELDOV_13_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_13_reg))
#define get_PREDBLK_NBFIELDOV_14_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_14_reg))
#define get_PREDBLK_NBFIELDOV_15_reg   (*((volatile unsigned int*) PREDBLK_NBFIELDOV_15_reg))
#define PREDBLK_NBFIELDOV_0_inst_adr                                                 "0x0035"
#define PREDBLK_NBFIELDOV_1_inst_adr                                                 "0x0036"
#define PREDBLK_NBFIELDOV_2_inst_adr                                                 "0x0037"
#define PREDBLK_NBFIELDOV_3_inst_adr                                                 "0x0038"
#define PREDBLK_NBFIELDOV_4_inst_adr                                                 "0x0039"
#define PREDBLK_NBFIELDOV_5_inst_adr                                                 "0x003A"
#define PREDBLK_NBFIELDOV_6_inst_adr                                                 "0x003B"
#define PREDBLK_NBFIELDOV_7_inst_adr                                                 "0x003C"
#define PREDBLK_NBFIELDOV_8_inst_adr                                                 "0x003D"
#define PREDBLK_NBFIELDOV_9_inst_adr                                                 "0x003E"
#define PREDBLK_NBFIELDOV_10_inst_adr                                                 "0x003F"
#define PREDBLK_NBFIELDOV_11_inst_adr                                                 "0x0040"
#define PREDBLK_NBFIELDOV_12_inst_adr                                                 "0x0041"
#define PREDBLK_NBFIELDOV_13_inst_adr                                                 "0x0042"
#define PREDBLK_NBFIELDOV_14_inst_adr                                                 "0x0043"
#define PREDBLK_NBFIELDOV_15_inst_adr                                                 "0x0044"
#define PREDBLK_NBFIELDOV_0_inst                                                     0x0035
#define PREDBLK_NBFIELDOV_1_inst                                                     0x0036
#define PREDBLK_NBFIELDOV_2_inst                                                     0x0037
#define PREDBLK_NBFIELDOV_3_inst                                                     0x0038
#define PREDBLK_NBFIELDOV_4_inst                                                     0x0039
#define PREDBLK_NBFIELDOV_5_inst                                                     0x003A
#define PREDBLK_NBFIELDOV_6_inst                                                     0x003B
#define PREDBLK_NBFIELDOV_7_inst                                                     0x003C
#define PREDBLK_NBFIELDOV_8_inst                                                     0x003D
#define PREDBLK_NBFIELDOV_9_inst                                                     0x003E
#define PREDBLK_NBFIELDOV_10_inst                                                     0x003F
#define PREDBLK_NBFIELDOV_11_inst                                                     0x0040
#define PREDBLK_NBFIELDOV_12_inst                                                     0x0041
#define PREDBLK_NBFIELDOV_13_inst                                                     0x0042
#define PREDBLK_NBFIELDOV_14_inst                                                     0x0043
#define PREDBLK_NBFIELDOV_15_inst                                                     0x0044
#define PREDBLK_NBFIELDOV_Field_overflag_flag_shift                                  (0)
#define PREDBLK_NBFIELDOV_Field_overflag_flag_mask                                   (0xFFFFFFFF)
#define PREDBLK_NBFIELDOV_Field_overflag_flag(data)                                  (0xFFFFFFFF&((data)<<0))
#define PREDBLK_NBFIELDOV_Field_overflag_flag_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_NBFIELDOV_get_Field_overflag_flag(data)                              ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_NBEXTRA                                                              0x1800E914
#define PREDBLK_NBEXTRA_reg_addr                                                     "0xB800E914"
#define PREDBLK_NBEXTRA_reg                                                          0xB800E914
#define set_PREDBLK_NBEXTRA_reg(data)   (*((volatile unsigned int*) PREDBLK_NBEXTRA_reg)=data)
#define get_PREDBLK_NBEXTRA_reg   (*((volatile unsigned int*) PREDBLK_NBEXTRA_reg))
#define PREDBLK_NBEXTRA_inst_adr                                                     "0x0045"
#define PREDBLK_NBEXTRA_inst                                                         0x0045
#define PREDBLK_NBEXTRA_Intra0_shift                                                 (3)
#define PREDBLK_NBEXTRA_Intra0_mask                                                  (0x00000008)
#define PREDBLK_NBEXTRA_Intra0(data)                                                 (0x00000008&((data)<<3))
#define PREDBLK_NBEXTRA_Intra0_src(data)                                             ((0x00000008&(data))>>3)
#define PREDBLK_NBEXTRA_get_Intra0(data)                                             ((0x00000008&(data))>>3)
#define PREDBLK_NBEXTRA_Intra1_shift                                                 (2)
#define PREDBLK_NBEXTRA_Intra1_mask                                                  (0x00000004)
#define PREDBLK_NBEXTRA_Intra1(data)                                                 (0x00000004&((data)<<2))
#define PREDBLK_NBEXTRA_Intra1_src(data)                                             ((0x00000004&(data))>>2)
#define PREDBLK_NBEXTRA_get_Intra1(data)                                             ((0x00000004&(data))>>2)
#define PREDBLK_NBEXTRA_IntraChroma_shift                                            (1)
#define PREDBLK_NBEXTRA_IntraChroma_mask                                             (0x00000002)
#define PREDBLK_NBEXTRA_IntraChroma(data)                                            (0x00000002&((data)<<1))
#define PREDBLK_NBEXTRA_IntraChroma_src(data)                                        ((0x00000002&(data))>>1)
#define PREDBLK_NBEXTRA_get_IntraChroma(data)                                        ((0x00000002&(data))>>1)
#define PREDBLK_NBEXTRA_IntraField_shift                                             (0)
#define PREDBLK_NBEXTRA_IntraField_mask                                              (0x00000001)
#define PREDBLK_NBEXTRA_IntraField(data)                                             (0x00000001&((data)<<0))
#define PREDBLK_NBEXTRA_IntraField_src(data)                                         ((0x00000001&(data))>>0)
#define PREDBLK_NBEXTRA_get_IntraField(data)                                         ((0x00000001&(data))>>0)


#define PREDBLK_WTBLSA                                                               0x1800E918
#define PREDBLK_WTBLSA_reg_addr                                                      "0xB800E918"
#define PREDBLK_WTBLSA_reg                                                           0xB800E918
#define set_PREDBLK_WTBLSA_reg(data)   (*((volatile unsigned int*) PREDBLK_WTBLSA_reg)=data)
#define get_PREDBLK_WTBLSA_reg   (*((volatile unsigned int*) PREDBLK_WTBLSA_reg))
#define PREDBLK_WTBLSA_inst_adr                                                      "0x0046"
#define PREDBLK_WTBLSA_inst                                                          0x0046
#define PREDBLK_WTBLSA_WTBL_StartA_shift                                             (0)
#define PREDBLK_WTBLSA_WTBL_StartA_mask                                              (0x000003FF)
#define PREDBLK_WTBLSA_WTBL_StartA(data)                                             (0x000003FF&((data)<<0))
#define PREDBLK_WTBLSA_WTBL_StartA_src(data)                                         ((0x000003FF&(data))>>0)
#define PREDBLK_WTBLSA_get_WTBL_StartA(data)                                         ((0x000003FF&(data))>>0)


#define PREDBLK_WTFLAG_0                                                             0x1800E91C
#define PREDBLK_WTFLAG_1                                                             0x1800E920
#define PREDBLK_WTFLAG_2                                                             0x1800E924
#define PREDBLK_WTFLAG_3                                                             0x1800E928
#define PREDBLK_WTFLAG_0_reg_addr                                                    "0xB800E91C"
#define PREDBLK_WTFLAG_1_reg_addr                                                    "0xB800E920"
#define PREDBLK_WTFLAG_2_reg_addr                                                    "0xB800E924"
#define PREDBLK_WTFLAG_3_reg_addr                                                    "0xB800E928"
#define PREDBLK_WTFLAG_0_reg                                                         0xB800E91C
#define PREDBLK_WTFLAG_1_reg                                                         0xB800E920
#define PREDBLK_WTFLAG_2_reg                                                         0xB800E924
#define PREDBLK_WTFLAG_3_reg                                                         0xB800E928
#define set_PREDBLK_WTFLAG_0_reg(data)   (*((volatile unsigned int*) PREDBLK_WTFLAG_0_reg)=data)
#define set_PREDBLK_WTFLAG_1_reg(data)   (*((volatile unsigned int*) PREDBLK_WTFLAG_1_reg)=data)
#define set_PREDBLK_WTFLAG_2_reg(data)   (*((volatile unsigned int*) PREDBLK_WTFLAG_2_reg)=data)
#define set_PREDBLK_WTFLAG_3_reg(data)   (*((volatile unsigned int*) PREDBLK_WTFLAG_3_reg)=data)
#define get_PREDBLK_WTFLAG_0_reg   (*((volatile unsigned int*) PREDBLK_WTFLAG_0_reg))
#define get_PREDBLK_WTFLAG_1_reg   (*((volatile unsigned int*) PREDBLK_WTFLAG_1_reg))
#define get_PREDBLK_WTFLAG_2_reg   (*((volatile unsigned int*) PREDBLK_WTFLAG_2_reg))
#define get_PREDBLK_WTFLAG_3_reg   (*((volatile unsigned int*) PREDBLK_WTFLAG_3_reg))
#define PREDBLK_WTFLAG_0_inst_adr                                                    "0x0047"
#define PREDBLK_WTFLAG_1_inst_adr                                                    "0x0048"
#define PREDBLK_WTFLAG_2_inst_adr                                                    "0x0049"
#define PREDBLK_WTFLAG_3_inst_adr                                                    "0x004A"
#define PREDBLK_WTFLAG_0_inst                                                        0x0047
#define PREDBLK_WTFLAG_1_inst                                                        0x0048
#define PREDBLK_WTFLAG_2_inst                                                        0x0049
#define PREDBLK_WTFLAG_3_inst                                                        0x004A
#define PREDBLK_WTFLAG_wt_flag_shift                                                 (0)
#define PREDBLK_WTFLAG_wt_flag_mask                                                  (0xFFFFFFFF)
#define PREDBLK_WTFLAG_wt_flag(data)                                                 (0xFFFFFFFF&((data)<<0))
#define PREDBLK_WTFLAG_wt_flag_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_WTFLAG_get_wt_flag(data)                                             ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_SDMAADR                                                              0x1800E92C
#define PREDBLK_SDMAADR_reg_addr                                                     "0xB800E92C"
#define PREDBLK_SDMAADR_reg                                                          0xB800E92C
#define set_PREDBLK_SDMAADR_reg(data)   (*((volatile unsigned int*) PREDBLK_SDMAADR_reg)=data)
#define get_PREDBLK_SDMAADR_reg   (*((volatile unsigned int*) PREDBLK_SDMAADR_reg))
#define PREDBLK_SDMAADR_inst_adr                                                     "0x004B"
#define PREDBLK_SDMAADR_inst                                                         0x004B
#define PREDBLK_SDMAADR_Wdone_enable_shift                                           (31)
#define PREDBLK_SDMAADR_Wdone_enable_mask                                            (0x80000000)
#define PREDBLK_SDMAADR_Wdone_enable(data)                                           (0x80000000&((data)<<31))
#define PREDBLK_SDMAADR_Wdone_enable_src(data)                                       ((0x80000000&(data))>>31)
#define PREDBLK_SDMAADR_get_Wdone_enable(data)                                       ((0x80000000&(data))>>31)
#define PREDBLK_SDMAADR_Mem_eng_busy_shift                                           (30)
#define PREDBLK_SDMAADR_Mem_eng_busy_mask                                            (0x40000000)
#define PREDBLK_SDMAADR_Mem_eng_busy(data)                                           (0x40000000&((data)<<30))
#define PREDBLK_SDMAADR_Mem_eng_busy_src(data)                                       ((0x40000000&(data))>>30)
#define PREDBLK_SDMAADR_get_Mem_eng_busy(data)                                       ((0x40000000&(data))>>30)
#define PREDBLK_SDMAADR_seq_line_addr_shift                                          (0)
#define PREDBLK_SDMAADR_seq_line_addr_mask                                           (0x1FFFFFFF)
#define PREDBLK_SDMAADR_seq_line_addr(data)                                          (0x1FFFFFFF&((data)<<0))
#define PREDBLK_SDMAADR_seq_line_addr_src(data)                                      ((0x1FFFFFFF&(data))>>0)
#define PREDBLK_SDMAADR_get_seq_line_addr(data)                                      ((0x1FFFFFFF&(data))>>0)


#define PREDBLK_INTR_THRESH                                                          0x1800E930
#define PREDBLK_INTR_THRESH_reg_addr                                                 "0xB800E930"
#define PREDBLK_INTR_THRESH_reg                                                      0xB800E930
#define set_PREDBLK_INTR_THRESH_reg(data)   (*((volatile unsigned int*) PREDBLK_INTR_THRESH_reg)=data)
#define get_PREDBLK_INTR_THRESH_reg   (*((volatile unsigned int*) PREDBLK_INTR_THRESH_reg))
#define PREDBLK_INTR_THRESH_inst_adr                                                 "0x004C"
#define PREDBLK_INTR_THRESH_inst                                                     0x004C
#define PREDBLK_INTR_THRESH_Value_shift                                              (0)
#define PREDBLK_INTR_THRESH_Value_mask                                               (0x0FFFFFFF)
#define PREDBLK_INTR_THRESH_Value(data)                                              (0x0FFFFFFF&((data)<<0))
#define PREDBLK_INTR_THRESH_Value_src(data)                                          ((0x0FFFFFFF&(data))>>0)
#define PREDBLK_INTR_THRESH_get_Value(data)                                          ((0x0FFFFFFF&(data))>>0)


#define PREDBLK_BUSY                                                                 0x1800E934
#define PREDBLK_BUSY_reg_addr                                                        "0xB800E934"
#define PREDBLK_BUSY_reg                                                             0xB800E934
#define set_PREDBLK_BUSY_reg(data)   (*((volatile unsigned int*) PREDBLK_BUSY_reg)=data)
#define get_PREDBLK_BUSY_reg   (*((volatile unsigned int*) PREDBLK_BUSY_reg))
#define PREDBLK_BUSY_inst_adr                                                        "0x004D"
#define PREDBLK_BUSY_inst                                                            0x004D
#define PREDBLK_BUSY_Reach_Thresh_shift                                              (28)
#define PREDBLK_BUSY_Reach_Thresh_mask                                               (0x10000000)
#define PREDBLK_BUSY_Reach_Thresh(data)                                              (0x10000000&((data)<<28))
#define PREDBLK_BUSY_Reach_Thresh_src(data)                                          ((0x10000000&(data))>>28)
#define PREDBLK_BUSY_get_Reach_Thresh(data)                                          ((0x10000000&(data))>>28)
#define PREDBLK_BUSY_Count_shift                                                     (0)
#define PREDBLK_BUSY_Count_mask                                                      (0x0FFFFFFF)
#define PREDBLK_BUSY_Count(data)                                                     (0x0FFFFFFF&((data)<<0))
#define PREDBLK_BUSY_Count_src(data)                                                 ((0x0FFFFFFF&(data))>>0)
#define PREDBLK_BUSY_get_Count(data)                                                 ((0x0FFFFFFF&(data))>>0)


#define PREDBLK_BASEA                                                                0x1800E938
#define PREDBLK_BASEA_reg_addr                                                       "0xB800E938"
#define PREDBLK_BASEA_reg                                                            0xB800E938
#define set_PREDBLK_BASEA_reg(data)   (*((volatile unsigned int*) PREDBLK_BASEA_reg)=data)
#define get_PREDBLK_BASEA_reg   (*((volatile unsigned int*) PREDBLK_BASEA_reg))
#define PREDBLK_BASEA_inst_adr                                                       "0x004E"
#define PREDBLK_BASEA_inst                                                           0x004E
#define PREDBLK_BASEA_BaseA0_shift                                                   (16)
#define PREDBLK_BASEA_BaseA0_mask                                                    (0x007F0000)
#define PREDBLK_BASEA_BaseA0(data)                                                   (0x007F0000&((data)<<16))
#define PREDBLK_BASEA_BaseA0_src(data)                                               ((0x007F0000&(data))>>16)
#define PREDBLK_BASEA_get_BaseA0(data)                                               ((0x007F0000&(data))>>16)
#define PREDBLK_BASEA_BaseA1_shift                                                   (3)
#define PREDBLK_BASEA_BaseA1_mask                                                    (0x000003F8)
#define PREDBLK_BASEA_BaseA1(data)                                                   (0x000003F8&((data)<<3))
#define PREDBLK_BASEA_BaseA1_src(data)                                               ((0x000003F8&(data))>>3)
#define PREDBLK_BASEA_get_BaseA1(data)                                               ((0x000003F8&(data))>>3)


#define PREDBLK_OFFSETA_0                                                            0x1800E93C
#define PREDBLK_OFFSETA_1                                                            0x1800E940
#define PREDBLK_OFFSETA_2                                                            0x1800E944
#define PREDBLK_OFFSETA_0_reg_addr                                                   "0xB800E93C"
#define PREDBLK_OFFSETA_1_reg_addr                                                   "0xB800E940"
#define PREDBLK_OFFSETA_2_reg_addr                                                   "0xB800E944"
#define PREDBLK_OFFSETA_0_reg                                                        0xB800E93C
#define PREDBLK_OFFSETA_1_reg                                                        0xB800E940
#define PREDBLK_OFFSETA_2_reg                                                        0xB800E944
#define set_PREDBLK_OFFSETA_0_reg(data)   (*((volatile unsigned int*) PREDBLK_OFFSETA_0_reg)=data)
#define set_PREDBLK_OFFSETA_1_reg(data)   (*((volatile unsigned int*) PREDBLK_OFFSETA_1_reg)=data)
#define set_PREDBLK_OFFSETA_2_reg(data)   (*((volatile unsigned int*) PREDBLK_OFFSETA_2_reg)=data)
#define get_PREDBLK_OFFSETA_0_reg   (*((volatile unsigned int*) PREDBLK_OFFSETA_0_reg))
#define get_PREDBLK_OFFSETA_1_reg   (*((volatile unsigned int*) PREDBLK_OFFSETA_1_reg))
#define get_PREDBLK_OFFSETA_2_reg   (*((volatile unsigned int*) PREDBLK_OFFSETA_2_reg))
#define PREDBLK_OFFSETA_0_inst_adr                                                   "0x004F"
#define PREDBLK_OFFSETA_1_inst_adr                                                   "0x0050"
#define PREDBLK_OFFSETA_2_inst_adr                                                   "0x0051"
#define PREDBLK_OFFSETA_0_inst                                                       0x004F
#define PREDBLK_OFFSETA_1_inst                                                       0x0050
#define PREDBLK_OFFSETA_2_inst                                                       0x0051
#define PREDBLK_OFFSETA_OffsetA_shift                                                (3)
#define PREDBLK_OFFSETA_OffsetA_mask                                                 (0x000003F8)
#define PREDBLK_OFFSETA_OffsetA(data)                                                (0x000003F8&((data)<<3))
#define PREDBLK_OFFSETA_OffsetA_src(data)                                            ((0x000003F8&(data))>>3)
#define PREDBLK_OFFSETA_get_OffsetA(data)                                            ((0x000003F8&(data))>>3)


#define PREDBLK_DEBPAR                                                               0x1800E948
#define PREDBLK_DEBPAR_reg_addr                                                      "0xB800E948"
#define PREDBLK_DEBPAR_reg                                                           0xB800E948
#define set_PREDBLK_DEBPAR_reg(data)   (*((volatile unsigned int*) PREDBLK_DEBPAR_reg)=data)
#define get_PREDBLK_DEBPAR_reg   (*((volatile unsigned int*) PREDBLK_DEBPAR_reg))
#define PREDBLK_DEBPAR_inst_adr                                                      "0x0052"
#define PREDBLK_DEBPAR_inst                                                          0x0052
#define PREDBLK_DEBPAR_StartA_shift                                                  (0)
#define PREDBLK_DEBPAR_StartA_mask                                                   (0x0000007F)
#define PREDBLK_DEBPAR_StartA(data)                                                  (0x0000007F&((data)<<0))
#define PREDBLK_DEBPAR_StartA_src(data)                                              ((0x0000007F&(data))>>0)
#define PREDBLK_DEBPAR_get_StartA(data)                                              ((0x0000007F&(data))>>0)


#define PREDBLK_MPEGCTL                                                              0x1800E94C
#define PREDBLK_MPEGCTL_reg_addr                                                     "0xB800E94C"
#define PREDBLK_MPEGCTL_reg                                                          0xB800E94C
#define set_PREDBLK_MPEGCTL_reg(data)   (*((volatile unsigned int*) PREDBLK_MPEGCTL_reg)=data)
#define get_PREDBLK_MPEGCTL_reg   (*((volatile unsigned int*) PREDBLK_MPEGCTL_reg))
#define PREDBLK_MPEGCTL_inst_adr                                                     "0x0053"
#define PREDBLK_MPEGCTL_inst                                                         0x0053
#define PREDBLK_MPEGCTL_Rounding_Control_shift                                       (1)
#define PREDBLK_MPEGCTL_Rounding_Control_mask                                        (0x00000002)
#define PREDBLK_MPEGCTL_Rounding_Control(data)                                       (0x00000002&((data)<<1))
#define PREDBLK_MPEGCTL_Rounding_Control_src(data)                                   ((0x00000002&(data))>>1)
#define PREDBLK_MPEGCTL_get_Rounding_Control(data)                                   ((0x00000002&(data))>>1)
#define PREDBLK_MPEGCTL_Quarter_Sample_shift                                         (0)
#define PREDBLK_MPEGCTL_Quarter_Sample_mask                                          (0x00000001)
#define PREDBLK_MPEGCTL_Quarter_Sample(data)                                         (0x00000001&((data)<<0))
#define PREDBLK_MPEGCTL_Quarter_Sample_src(data)                                     ((0x00000001&(data))>>0)
#define PREDBLK_MPEGCTL_get_Quarter_Sample(data)                                     ((0x00000001&(data))>>0)


#define PREDBLK_RMEMDDR1                                                             0x1800E950
#define PREDBLK_RMEMDDR1_reg_addr                                                    "0xB800E950"
#define PREDBLK_RMEMDDR1_reg                                                         0xB800E950
#define set_PREDBLK_RMEMDDR1_reg(data)   (*((volatile unsigned int*) PREDBLK_RMEMDDR1_reg)=data)
#define get_PREDBLK_RMEMDDR1_reg   (*((volatile unsigned int*) PREDBLK_RMEMDDR1_reg))
#define PREDBLK_RMEMDDR1_inst_adr                                                    "0x0054"
#define PREDBLK_RMEMDDR1_inst                                                        0x0054
#define PREDBLK_RMEMDDR1_Valid_shift                                                 (31)
#define PREDBLK_RMEMDDR1_Valid_mask                                                  (0x80000000)
#define PREDBLK_RMEMDDR1_Valid(data)                                                 (0x80000000&((data)<<31))
#define PREDBLK_RMEMDDR1_Valid_src(data)                                             ((0x80000000&(data))>>31)
#define PREDBLK_RMEMDDR1_get_Valid(data)                                             ((0x80000000&(data))>>31)
#define PREDBLK_RMEMDDR1_Base_addr_shift                                             (3)
#define PREDBLK_RMEMDDR1_Base_addr_mask                                              (0x1FFFFFF8)
#define PREDBLK_RMEMDDR1_Base_addr(data)                                             (0x1FFFFFF8&((data)<<3))
#define PREDBLK_RMEMDDR1_Base_addr_src(data)                                         ((0x1FFFFFF8&(data))>>3)
#define PREDBLK_RMEMDDR1_get_Base_addr(data)                                         ((0x1FFFFFF8&(data))>>3)


#define PREDBLK_RMEMDDR2                                                             0x1800E954
#define PREDBLK_RMEMDDR2_reg_addr                                                    "0xB800E954"
#define PREDBLK_RMEMDDR2_reg                                                         0xB800E954
#define set_PREDBLK_RMEMDDR2_reg(data)   (*((volatile unsigned int*) PREDBLK_RMEMDDR2_reg)=data)
#define get_PREDBLK_RMEMDDR2_reg   (*((volatile unsigned int*) PREDBLK_RMEMDDR2_reg))
#define PREDBLK_RMEMDDR2_inst_adr                                                    "0x0055"
#define PREDBLK_RMEMDDR2_inst                                                        0x0055
#define PREDBLK_RMEMDDR2_MBCnt_threshold_shift                                       (0)
#define PREDBLK_RMEMDDR2_MBCnt_threshold_mask                                        (0xFFFFFFFF)
#define PREDBLK_RMEMDDR2_MBCnt_threshold(data)                                       (0xFFFFFFFF&((data)<<0))
#define PREDBLK_RMEMDDR2_MBCnt_threshold_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_RMEMDDR2_get_MBCnt_threshold(data)                                   ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_RMEMCTL                                                              0x1800E958
#define PREDBLK_RMEMCTL_reg_addr                                                     "0xB800E958"
#define PREDBLK_RMEMCTL_reg                                                          0xB800E958
#define set_PREDBLK_RMEMCTL_reg(data)   (*((volatile unsigned int*) PREDBLK_RMEMCTL_reg)=data)
#define get_PREDBLK_RMEMCTL_reg   (*((volatile unsigned int*) PREDBLK_RMEMCTL_reg))
#define PREDBLK_RMEMCTL_inst_adr                                                     "0x0056"
#define PREDBLK_RMEMCTL_inst                                                         0x0056
#define PREDBLK_RMEMCTL_Valid_shift                                                  (31)
#define PREDBLK_RMEMCTL_Valid_mask                                                   (0x80000000)
#define PREDBLK_RMEMCTL_Valid(data)                                                  (0x80000000&((data)<<31))
#define PREDBLK_RMEMCTL_Valid_src(data)                                              ((0x80000000&(data))>>31)
#define PREDBLK_RMEMCTL_get_Valid(data)                                              ((0x80000000&(data))>>31)
#define PREDBLK_RMEMCTL_Start_Addr_shift                                             (7)
#define PREDBLK_RMEMCTL_Start_Addr_mask                                              (0x00003F80)
#define PREDBLK_RMEMCTL_Start_Addr(data)                                             (0x00003F80&((data)<<7))
#define PREDBLK_RMEMCTL_Start_Addr_src(data)                                         ((0x00003F80&(data))>>7)
#define PREDBLK_RMEMCTL_get_Start_Addr(data)                                         ((0x00003F80&(data))>>7)
#define PREDBLK_RMEMCTL_End_Addr_shift                                               (0)
#define PREDBLK_RMEMCTL_End_Addr_mask                                                (0x0000007F)
#define PREDBLK_RMEMCTL_End_Addr(data)                                               (0x0000007F&((data)<<0))
#define PREDBLK_RMEMCTL_End_Addr_src(data)                                           ((0x0000007F&(data))>>0)
#define PREDBLK_RMEMCTL_get_End_Addr(data)                                           ((0x0000007F&(data))>>0)


#define PREDBLK_URATIO_0                                                             0x1800E95C
#define PREDBLK_URATIO_1                                                             0x1800E960
#define PREDBLK_URATIO_0_reg_addr                                                    "0xB800E95C"
#define PREDBLK_URATIO_1_reg_addr                                                    "0xB800E960"
#define PREDBLK_URATIO_0_reg                                                         0xB800E95C
#define PREDBLK_URATIO_1_reg                                                         0xB800E960
#define set_PREDBLK_URATIO_0_reg(data)   (*((volatile unsigned int*) PREDBLK_URATIO_0_reg)=data)
#define set_PREDBLK_URATIO_1_reg(data)   (*((volatile unsigned int*) PREDBLK_URATIO_1_reg)=data)
#define get_PREDBLK_URATIO_0_reg   (*((volatile unsigned int*) PREDBLK_URATIO_0_reg))
#define get_PREDBLK_URATIO_1_reg   (*((volatile unsigned int*) PREDBLK_URATIO_1_reg))
#define PREDBLK_URATIO_0_inst_adr                                                    "0x0057"
#define PREDBLK_URATIO_1_inst_adr                                                    "0x0058"
#define PREDBLK_URATIO_0_inst                                                        0x0057
#define PREDBLK_URATIO_1_inst                                                        0x0058
#define PREDBLK_URATIO_URatio_shift                                                  (0)
#define PREDBLK_URATIO_URatio_mask                                                   (0x00007FFF)
#define PREDBLK_URATIO_URatio(data)                                                  (0x00007FFF&((data)<<0))
#define PREDBLK_URATIO_URatio_src(data)                                              ((0x00007FFF&(data))>>0)
#define PREDBLK_URATIO_get_URatio(data)                                              ((0x00007FFF&(data))>>0)


#define PREDBLK_VP6CTRL                                                              0x1800E964
#define PREDBLK_VP6CTRL_reg_addr                                                     "0xB800E964"
#define PREDBLK_VP6CTRL_reg                                                          0xB800E964
#define set_PREDBLK_VP6CTRL_reg(data)   (*((volatile unsigned int*) PREDBLK_VP6CTRL_reg)=data)
#define get_PREDBLK_VP6CTRL_reg   (*((volatile unsigned int*) PREDBLK_VP6CTRL_reg))
#define PREDBLK_VP6CTRL_inst_adr                                                     "0x0059"
#define PREDBLK_VP6CTRL_inst                                                         0x0059
#define PREDBLK_VP6CTRL_VP6_1_shift                                                  (25)
#define PREDBLK_VP6CTRL_VP6_1_mask                                                   (0x02000000)
#define PREDBLK_VP6CTRL_VP6_1(data)                                                  (0x02000000&((data)<<25))
#define PREDBLK_VP6CTRL_VP6_1_src(data)                                              ((0x02000000&(data))>>25)
#define PREDBLK_VP6CTRL_get_VP6_1(data)                                              ((0x02000000&(data))>>25)
#define PREDBLK_VP6CTRL_AutoSelectPMFlag_shift                                       (24)
#define PREDBLK_VP6CTRL_AutoSelectPMFlag_mask                                        (0x01000000)
#define PREDBLK_VP6CTRL_AutoSelectPMFlag(data)                                       (0x01000000&((data)<<24))
#define PREDBLK_VP6CTRL_AutoSelectPMFlag_src(data)                                   ((0x01000000&(data))>>24)
#define PREDBLK_VP6CTRL_get_AutoSelectPMFlag(data)                                   ((0x01000000&(data))>>24)
#define PREDBLK_VP6CTRL_BicubicFiltFlag_shift                                        (23)
#define PREDBLK_VP6CTRL_BicubicFiltFlag_mask                                         (0x00800000)
#define PREDBLK_VP6CTRL_BicubicFiltFlag(data)                                        (0x00800000&((data)<<23))
#define PREDBLK_VP6CTRL_BicubicFiltFlag_src(data)                                    ((0x00800000&(data))>>23)
#define PREDBLK_VP6CTRL_get_BicubicFiltFlag(data)                                    ((0x00800000&(data))>>23)
#define PREDBLK_VP6CTRL_Sample_var_thresh_shift                                      (13)
#define PREDBLK_VP6CTRL_Sample_var_thresh_mask                                       (0x007FE000)
#define PREDBLK_VP6CTRL_Sample_var_thresh(data)                                      (0x007FE000&((data)<<13))
#define PREDBLK_VP6CTRL_Sample_var_thresh_src(data)                                  ((0x007FE000&(data))>>13)
#define PREDBLK_VP6CTRL_get_Sample_var_thresh(data)                                  ((0x007FE000&(data))>>13)
#define PREDBLK_VP6CTRL_Max_vec_length_shift                                         (4)
#define PREDBLK_VP6CTRL_Max_vec_length_mask                                          (0x00001FF0)
#define PREDBLK_VP6CTRL_Max_vec_length(data)                                         (0x00001FF0&((data)<<4))
#define PREDBLK_VP6CTRL_Max_vec_length_src(data)                                     ((0x00001FF0&(data))>>4)
#define PREDBLK_VP6CTRL_get_Max_vec_length(data)                                     ((0x00001FF0&(data))>>4)
#define PREDBLK_VP6CTRL_Bicubic_filt_sel_shift                                       (0)
#define PREDBLK_VP6CTRL_Bicubic_filt_sel_mask                                        (0x0000000F)
#define PREDBLK_VP6CTRL_Bicubic_filt_sel(data)                                       (0x0000000F&((data)<<0))
#define PREDBLK_VP6CTRL_Bicubic_filt_sel_src(data)                                   ((0x0000000F&(data))>>0)
#define PREDBLK_VP6CTRL_get_Bicubic_filt_sel(data)                                   ((0x0000000F&(data))>>0)


#define PREDBLK_DBUS                                                                 0x1800E968
#define PREDBLK_DBUS_reg_addr                                                        "0xB800E968"
#define PREDBLK_DBUS_reg                                                             0xB800E968
#define set_PREDBLK_DBUS_reg(data)   (*((volatile unsigned int*) PREDBLK_DBUS_reg)=data)
#define get_PREDBLK_DBUS_reg   (*((volatile unsigned int*) PREDBLK_DBUS_reg))
#define PREDBLK_DBUS_inst_adr                                                        "0x005A"
#define PREDBLK_DBUS_inst                                                            0x005A
#define PREDBLK_DBUS_GenPulse_shift                                                  (31)
#define PREDBLK_DBUS_GenPulse_mask                                                   (0x80000000)
#define PREDBLK_DBUS_GenPulse(data)                                                  (0x80000000&((data)<<31))
#define PREDBLK_DBUS_GenPulse_src(data)                                              ((0x80000000&(data))>>31)
#define PREDBLK_DBUS_get_GenPulse(data)                                              ((0x80000000&(data))>>31)
#define PREDBLK_DBUS_PicCount_shift                                                  (17)
#define PREDBLK_DBUS_PicCount_mask                                                   (0x7FFE0000)
#define PREDBLK_DBUS_PicCount(data)                                                  (0x7FFE0000&((data)<<17))
#define PREDBLK_DBUS_PicCount_src(data)                                              ((0x7FFE0000&(data))>>17)
#define PREDBLK_DBUS_get_PicCount(data)                                              ((0x7FFE0000&(data))>>17)
#define PREDBLK_DBUS_MbAddrX_shift                                                   (8)
#define PREDBLK_DBUS_MbAddrX_mask                                                    (0x0001FF00)
#define PREDBLK_DBUS_MbAddrX(data)                                                   (0x0001FF00&((data)<<8))
#define PREDBLK_DBUS_MbAddrX_src(data)                                               ((0x0001FF00&(data))>>8)
#define PREDBLK_DBUS_get_MbAddrX(data)                                               ((0x0001FF00&(data))>>8)
#define PREDBLK_DBUS_MbAddrY_shift                                                   (0)
#define PREDBLK_DBUS_MbAddrY_mask                                                    (0x000000FF)
#define PREDBLK_DBUS_MbAddrY(data)                                                   (0x000000FF&((data)<<0))
#define PREDBLK_DBUS_MbAddrY_src(data)                                               ((0x000000FF&(data))>>0)
#define PREDBLK_DBUS_get_MbAddrY(data)                                               ((0x000000FF&(data))>>0)


#define PREDBLK_DBUS2                                                                0x1800E96C
#define PREDBLK_DBUS2_reg_addr                                                       "0xB800E96C"
#define PREDBLK_DBUS2_reg                                                            0xB800E96C
#define set_PREDBLK_DBUS2_reg(data)   (*((volatile unsigned int*) PREDBLK_DBUS2_reg)=data)
#define get_PREDBLK_DBUS2_reg   (*((volatile unsigned int*) PREDBLK_DBUS2_reg))
#define PREDBLK_DBUS2_inst_adr                                                       "0x005B"
#define PREDBLK_DBUS2_inst                                                           0x005B
#define PREDBLK_DBUS2_DbgCtrl_shift                                                  (0)
#define PREDBLK_DBUS2_DbgCtrl_mask                                                   (0xFFFFFFFF)
#define PREDBLK_DBUS2_DbgCtrl(data)                                                  (0xFFFFFFFF&((data)<<0))
#define PREDBLK_DBUS2_DbgCtrl_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define PREDBLK_DBUS2_get_DbgCtrl(data)                                              ((0xFFFFFFFF&(data))>>0)


#define PREDBLK_DBUS3                                                                0x1800E9A8
#define PREDBLK_DBUS3_reg_addr                                                       "0xB800E9A8"
#define PREDBLK_DBUS3_reg                                                            0xB800E9A8
#define set_PREDBLK_DBUS3_reg(data)   (*((volatile unsigned int*) PREDBLK_DBUS3_reg)=data)
#define get_PREDBLK_DBUS3_reg   (*((volatile unsigned int*) PREDBLK_DBUS3_reg))
#define PREDBLK_DBUS3_inst_adr                                                       "0x006A"
#define PREDBLK_DBUS3_inst                                                           0x006A
#define PREDBLK_DBUS3_DbgCtrl3_shift                                                 (3)
#define PREDBLK_DBUS3_DbgCtrl3_mask                                                  (0xFFFFFFF8)
#define PREDBLK_DBUS3_DbgCtrl3(data)                                                 (0xFFFFFFF8&((data)<<3))
#define PREDBLK_DBUS3_DbgCtrl3_src(data)                                             ((0xFFFFFFF8&(data))>>3)
#define PREDBLK_DBUS3_get_DbgCtrl3(data)                                             ((0xFFFFFFF8&(data))>>3)
#define PREDBLK_DBUS3_DbgCtrl_shift                                                  (0)
#define PREDBLK_DBUS3_DbgCtrl_mask                                                   (0x00000007)
#define PREDBLK_DBUS3_DbgCtrl(data)                                                  (0x00000007&((data)<<0))
#define PREDBLK_DBUS3_DbgCtrl_src(data)                                              ((0x00000007&(data))>>0)
#define PREDBLK_DBUS3_get_DbgCtrl(data)                                              ((0x00000007&(data))>>0)


#define PREDBLK_DMAMSB                                                               0x1800E970
#define PREDBLK_DMAMSB_reg_addr                                                      "0xB800E970"
#define PREDBLK_DMAMSB_reg                                                           0xB800E970
#define set_PREDBLK_DMAMSB_reg(data)   (*((volatile unsigned int*) PREDBLK_DMAMSB_reg)=data)
#define get_PREDBLK_DMAMSB_reg   (*((volatile unsigned int*) PREDBLK_DMAMSB_reg))
#define PREDBLK_DMAMSB_inst_adr                                                      "0x005C"
#define PREDBLK_DMAMSB_inst                                                          0x005C
#define PREDBLK_DMAMSB_SDMA2MSB_shift                                                (2)
#define PREDBLK_DMAMSB_SDMA2MSB_mask                                                 (0x0000000C)
#define PREDBLK_DMAMSB_SDMA2MSB(data)                                                (0x0000000C&((data)<<2))
#define PREDBLK_DMAMSB_SDMA2MSB_src(data)                                            ((0x0000000C&(data))>>2)
#define PREDBLK_DMAMSB_get_SDMA2MSB(data)                                            ((0x0000000C&(data))>>2)
#define PREDBLK_DMAMSB_RMEM2MSB_shift                                                (0)
#define PREDBLK_DMAMSB_RMEM2MSB_mask                                                 (0x00000003)
#define PREDBLK_DMAMSB_RMEM2MSB(data)                                                (0x00000003&((data)<<0))
#define PREDBLK_DMAMSB_RMEM2MSB_src(data)                                            ((0x00000003&(data))>>0)
#define PREDBLK_DMAMSB_get_RMEM2MSB(data)                                            ((0x00000003&(data))>>0)


#define PREDBLK_DMEMADR                                                              0x1800E974
#define PREDBLK_DMEMADR_reg_addr                                                     "0xB800E974"
#define PREDBLK_DMEMADR_reg                                                          0xB800E974
#define set_PREDBLK_DMEMADR_reg(data)   (*((volatile unsigned int*) PREDBLK_DMEMADR_reg)=data)
#define get_PREDBLK_DMEMADR_reg   (*((volatile unsigned int*) PREDBLK_DMEMADR_reg))
#define PREDBLK_DMEMADR_inst_adr                                                     "0x005D"
#define PREDBLK_DMEMADR_inst                                                         0x005D
#define PREDBLK_DMEMADR_BaseAddr_shift                                               (0)
#define PREDBLK_DMEMADR_BaseAddr_mask                                                (0x00000FFF)
#define PREDBLK_DMEMADR_BaseAddr(data)                                               (0x00000FFF&((data)<<0))
#define PREDBLK_DMEMADR_BaseAddr_src(data)                                           ((0x00000FFF&(data))>>0)
#define PREDBLK_DMEMADR_get_BaseAddr(data)                                           ((0x00000FFF&(data))>>0)


#define PREDBLK_X8ILUQU                                                              0x1800E978
#define PREDBLK_X8ILUQU_reg_addr                                                     "0xB800E978"
#define PREDBLK_X8ILUQU_reg                                                          0xB800E978
#define set_PREDBLK_X8ILUQU_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ILUQU_reg)=data)
#define get_PREDBLK_X8ILUQU_reg   (*((volatile unsigned int*) PREDBLK_X8ILUQU_reg))
#define PREDBLK_X8ILUQU_inst_adr                                                     "0x005E"
#define PREDBLK_X8ILUQU_inst                                                         0x005E
#define PREDBLK_X8ILUQU_DC_Quant_shift                                               (24)
#define PREDBLK_X8ILUQU_DC_Quant_mask                                                (0x3F000000)
#define PREDBLK_X8ILUQU_DC_Quant(data)                                               (0x3F000000&((data)<<24))
#define PREDBLK_X8ILUQU_DC_Quant_src(data)                                           ((0x3F000000&(data))>>24)
#define PREDBLK_X8ILUQU_get_DC_Quant(data)                                           ((0x3F000000&(data))>>24)
#define PREDBLK_X8ILUQU_Div_Quant_shift                                              (0)
#define PREDBLK_X8ILUQU_Div_Quant_mask                                               (0x0001FFFF)
#define PREDBLK_X8ILUQU_Div_Quant(data)                                              (0x0001FFFF&((data)<<0))
#define PREDBLK_X8ILUQU_Div_Quant_src(data)                                          ((0x0001FFFF&(data))>>0)
#define PREDBLK_X8ILUQU_get_Div_Quant(data)                                          ((0x0001FFFF&(data))>>0)


#define PREDBLK_X8ICHQU                                                              0x1800E97C
#define PREDBLK_X8ICHQU_reg_addr                                                     "0xB800E97C"
#define PREDBLK_X8ICHQU_reg                                                          0xB800E97C
#define set_PREDBLK_X8ICHQU_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ICHQU_reg)=data)
#define get_PREDBLK_X8ICHQU_reg   (*((volatile unsigned int*) PREDBLK_X8ICHQU_reg))
#define PREDBLK_X8ICHQU_inst_adr                                                     "0x005F"
#define PREDBLK_X8ICHQU_inst                                                         0x005F
#define PREDBLK_X8ICHQU_DC_Quant_shift                                               (24)
#define PREDBLK_X8ICHQU_DC_Quant_mask                                                (0x7F000000)
#define PREDBLK_X8ICHQU_DC_Quant(data)                                               (0x7F000000&((data)<<24))
#define PREDBLK_X8ICHQU_DC_Quant_src(data)                                           ((0x7F000000&(data))>>24)
#define PREDBLK_X8ICHQU_get_DC_Quant(data)                                           ((0x7F000000&(data))>>24)
#define PREDBLK_X8ICHQU_Div_Quant_shift                                              (0)
#define PREDBLK_X8ICHQU_Div_Quant_mask                                               (0x0001FFFF)
#define PREDBLK_X8ICHQU_Div_Quant(data)                                              (0x0001FFFF&((data)<<0))
#define PREDBLK_X8ICHQU_Div_Quant_src(data)                                          ((0x0001FFFF&(data))>>0)
#define PREDBLK_X8ICHQU_get_Div_Quant(data)                                          ((0x0001FFFF&(data))>>0)


#define PREDBLK_X8ILFLT                                                              0x1800E980
#define PREDBLK_X8ILFLT_reg_addr                                                     "0xB800E980"
#define PREDBLK_X8ILFLT_reg                                                          0xB800E980
#define set_PREDBLK_X8ILFLT_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ILFLT_reg)=data)
#define get_PREDBLK_X8ILFLT_reg   (*((volatile unsigned int*) PREDBLK_X8ILFLT_reg))
#define PREDBLK_X8ILFLT_inst_adr                                                     "0x0060"
#define PREDBLK_X8ILFLT_inst                                                         0x0060
#define PREDBLK_X8ILFLT_TL_shift                                                     (24)
#define PREDBLK_X8ILFLT_TL_mask                                                      (0xFF000000)
#define PREDBLK_X8ILFLT_TL(data)                                                     (0xFF000000&((data)<<24))
#define PREDBLK_X8ILFLT_TL_src(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFLT_get_TL(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFLT_TR_shift                                                     (16)
#define PREDBLK_X8ILFLT_TR_mask                                                      (0x00FF0000)
#define PREDBLK_X8ILFLT_TR(data)                                                     (0x00FF0000&((data)<<16))
#define PREDBLK_X8ILFLT_TR_src(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFLT_get_TR(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFLT_BL_shift                                                     (8)
#define PREDBLK_X8ILFLT_BL_mask                                                      (0x0000FF00)
#define PREDBLK_X8ILFLT_BL(data)                                                     (0x0000FF00&((data)<<8))
#define PREDBLK_X8ILFLT_BL_src(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFLT_get_BL(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFLT_BR_shift                                                     (0)
#define PREDBLK_X8ILFLT_BR_mask                                                      (0x000000FF)
#define PREDBLK_X8ILFLT_BR(data)                                                     (0x000000FF&((data)<<0))
#define PREDBLK_X8ILFLT_BR_src(data)                                                 ((0x000000FF&(data))>>0)
#define PREDBLK_X8ILFLT_get_BR(data)                                                 ((0x000000FF&(data))>>0)


#define PREDBLK_X8ILFCR                                                              0x1800E984
#define PREDBLK_X8ILFCR_reg_addr                                                     "0xB800E984"
#define PREDBLK_X8ILFCR_reg                                                          0xB800E984
#define set_PREDBLK_X8ILFCR_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ILFCR_reg)=data)
#define get_PREDBLK_X8ILFCR_reg   (*((volatile unsigned int*) PREDBLK_X8ILFCR_reg))
#define PREDBLK_X8ILFCR_inst_adr                                                     "0x0061"
#define PREDBLK_X8ILFCR_inst                                                         0x0061
#define PREDBLK_X8ILFCR_TL_shift                                                     (24)
#define PREDBLK_X8ILFCR_TL_mask                                                      (0xFF000000)
#define PREDBLK_X8ILFCR_TL(data)                                                     (0xFF000000&((data)<<24))
#define PREDBLK_X8ILFCR_TL_src(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFCR_get_TL(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFCR_TR_shift                                                     (16)
#define PREDBLK_X8ILFCR_TR_mask                                                      (0x00FF0000)
#define PREDBLK_X8ILFCR_TR(data)                                                     (0x00FF0000&((data)<<16))
#define PREDBLK_X8ILFCR_TR_src(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFCR_get_TR(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFCR_BL_shift                                                     (8)
#define PREDBLK_X8ILFCR_BL_mask                                                      (0x0000FF00)
#define PREDBLK_X8ILFCR_BL(data)                                                     (0x0000FF00&((data)<<8))
#define PREDBLK_X8ILFCR_BL_src(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFCR_get_BL(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFCR_BR_shift                                                     (0)
#define PREDBLK_X8ILFCR_BR_mask                                                      (0x000000FF)
#define PREDBLK_X8ILFCR_BR(data)                                                     (0x000000FF&((data)<<0))
#define PREDBLK_X8ILFCR_BR_src(data)                                                 ((0x000000FF&(data))>>0)
#define PREDBLK_X8ILFCR_get_BR(data)                                                 ((0x000000FF&(data))>>0)


#define PREDBLK_X8ILFCC                                                              0x1800E988
#define PREDBLK_X8ILFCC_reg_addr                                                     "0xB800E988"
#define PREDBLK_X8ILFCC_reg                                                          0xB800E988
#define set_PREDBLK_X8ILFCC_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ILFCC_reg)=data)
#define get_PREDBLK_X8ILFCC_reg   (*((volatile unsigned int*) PREDBLK_X8ILFCC_reg))
#define PREDBLK_X8ILFCC_inst_adr                                                     "0x0062"
#define PREDBLK_X8ILFCC_inst                                                         0x0062
#define PREDBLK_X8ILFCC_TL_shift                                                     (24)
#define PREDBLK_X8ILFCC_TL_mask                                                      (0xFF000000)
#define PREDBLK_X8ILFCC_TL(data)                                                     (0xFF000000&((data)<<24))
#define PREDBLK_X8ILFCC_TL_src(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFCC_get_TL(data)                                                 ((0xFF000000&(data))>>24)
#define PREDBLK_X8ILFCC_TR_shift                                                     (16)
#define PREDBLK_X8ILFCC_TR_mask                                                      (0x00FF0000)
#define PREDBLK_X8ILFCC_TR(data)                                                     (0x00FF0000&((data)<<16))
#define PREDBLK_X8ILFCC_TR_src(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFCC_get_TR(data)                                                 ((0x00FF0000&(data))>>16)
#define PREDBLK_X8ILFCC_BL_shift                                                     (8)
#define PREDBLK_X8ILFCC_BL_mask                                                      (0x0000FF00)
#define PREDBLK_X8ILFCC_BL(data)                                                     (0x0000FF00&((data)<<8))
#define PREDBLK_X8ILFCC_BL_src(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFCC_get_BL(data)                                                 ((0x0000FF00&(data))>>8)
#define PREDBLK_X8ILFCC_BR_shift                                                     (0)
#define PREDBLK_X8ILFCC_BR_mask                                                      (0x000000FF)
#define PREDBLK_X8ILFCC_BR(data)                                                     (0x000000FF&((data)<<0))
#define PREDBLK_X8ILFCC_BR_src(data)                                                 ((0x000000FF&(data))>>0)
#define PREDBLK_X8ILFCC_get_BR(data)                                                 ((0x000000FF&(data))>>0)


#define PREDBLK_X8ILFTP                                                              0x1800E98C
#define PREDBLK_X8ILFTP_reg_addr                                                     "0xB800E98C"
#define PREDBLK_X8ILFTP_reg                                                          0xB800E98C
#define set_PREDBLK_X8ILFTP_reg(data)   (*((volatile unsigned int*) PREDBLK_X8ILFTP_reg)=data)
#define get_PREDBLK_X8ILFTP_reg   (*((volatile unsigned int*) PREDBLK_X8ILFTP_reg))
#define PREDBLK_X8ILFTP_inst_adr                                                     "0x0063"
#define PREDBLK_X8ILFTP_inst                                                         0x0063
#define PREDBLK_X8ILFTP_BR_shift                                                     (0)
#define PREDBLK_X8ILFTP_BR_mask                                                      (0x000000FF)
#define PREDBLK_X8ILFTP_BR(data)                                                     (0x000000FF&((data)<<0))
#define PREDBLK_X8ILFTP_BR_src(data)                                                 ((0x000000FF&(data))>>0)
#define PREDBLK_X8ILFTP_get_BR(data)                                                 ((0x000000FF&(data))>>0)


#define PREDBLK_DMEMOP                                                               0x1800E990
#define PREDBLK_DMEMOP_reg_addr                                                      "0xB800E990"
#define PREDBLK_DMEMOP_reg                                                           0xB800E990
#define set_PREDBLK_DMEMOP_reg(data)   (*((volatile unsigned int*) PREDBLK_DMEMOP_reg)=data)
#define get_PREDBLK_DMEMOP_reg   (*((volatile unsigned int*) PREDBLK_DMEMOP_reg))
#define PREDBLK_DMEMOP_inst_adr                                                      "0x0064"
#define PREDBLK_DMEMOP_inst                                                          0x0064
#define PREDBLK_DMEMOP_Count_shift                                                   (0)
#define PREDBLK_DMEMOP_Count_mask                                                    (0x0FFFFFFF)
#define PREDBLK_DMEMOP_Count(data)                                                   (0x0FFFFFFF&((data)<<0))
#define PREDBLK_DMEMOP_Count_src(data)                                               ((0x0FFFFFFF&(data))>>0)
#define PREDBLK_DMEMOP_get_Count(data)                                               ((0x0FFFFFFF&(data))>>0)


#define PREDBLK_SLICE_RESTART                                                        0x1800E994
#define PREDBLK_SLICE_RESTART_reg_addr                                               "0xB800E994"
#define PREDBLK_SLICE_RESTART_reg                                                    0xB800E994
#define set_PREDBLK_SLICE_RESTART_reg(data)   (*((volatile unsigned int*) PREDBLK_SLICE_RESTART_reg)=data)
#define get_PREDBLK_SLICE_RESTART_reg   (*((volatile unsigned int*) PREDBLK_SLICE_RESTART_reg))
#define PREDBLK_SLICE_RESTART_inst_adr                                               "0x0065"
#define PREDBLK_SLICE_RESTART_inst                                                   0x0065
#define PREDBLK_SLICE_RESTART_hw_enable_shift                                        (31)
#define PREDBLK_SLICE_RESTART_hw_enable_mask                                         (0x80000000)
#define PREDBLK_SLICE_RESTART_hw_enable(data)                                        (0x80000000&((data)<<31))
#define PREDBLK_SLICE_RESTART_hw_enable_src(data)                                    ((0x80000000&(data))>>31)
#define PREDBLK_SLICE_RESTART_get_hw_enable(data)                                    ((0x80000000&(data))>>31)
#define PREDBLK_SLICE_RESTART_Pmem_idle_shift                                        (0)
#define PREDBLK_SLICE_RESTART_Pmem_idle_mask                                         (0x00000001)
#define PREDBLK_SLICE_RESTART_Pmem_idle(data)                                        (0x00000001&((data)<<0))
#define PREDBLK_SLICE_RESTART_Pmem_idle_src(data)                                    ((0x00000001&(data))>>0)
#define PREDBLK_SLICE_RESTART_get_Pmem_idle(data)                                    ((0x00000001&(data))>>0)


#define PREDBLK_SLICE_DBG0                                                           0x1800E998
#define PREDBLK_SLICE_DBG0_reg_addr                                                  "0xB800E998"
#define PREDBLK_SLICE_DBG0_reg                                                       0xB800E998
#define set_PREDBLK_SLICE_DBG0_reg(data)   (*((volatile unsigned int*) PREDBLK_SLICE_DBG0_reg)=data)
#define get_PREDBLK_SLICE_DBG0_reg   (*((volatile unsigned int*) PREDBLK_SLICE_DBG0_reg))
#define PREDBLK_SLICE_DBG0_inst_adr                                                  "0x0066"
#define PREDBLK_SLICE_DBG0_inst                                                      0x0066
#define PREDBLK_SLICE_DBG0_sw_override_shift                                         (31)
#define PREDBLK_SLICE_DBG0_sw_override_mask                                          (0x80000000)
#define PREDBLK_SLICE_DBG0_sw_override(data)                                         (0x80000000&((data)<<31))
#define PREDBLK_SLICE_DBG0_sw_override_src(data)                                     ((0x80000000&(data))>>31)
#define PREDBLK_SLICE_DBG0_get_sw_override(data)                                     ((0x80000000&(data))>>31)
#define PREDBLK_SLICE_DBG0_ddr_inb_rdadr_shift                                       (20)
#define PREDBLK_SLICE_DBG0_ddr_inb_rdadr_mask                                        (0x00700000)
#define PREDBLK_SLICE_DBG0_ddr_inb_rdadr(data)                                       (0x00700000&((data)<<20))
#define PREDBLK_SLICE_DBG0_ddr_inb_rdadr_src(data)                                   ((0x00700000&(data))>>20)
#define PREDBLK_SLICE_DBG0_get_ddr_inb_rdadr(data)                                   ((0x00700000&(data))>>20)
#define PREDBLK_SLICE_DBG0_ddr_out_rdadr_shift                                       (14)
#define PREDBLK_SLICE_DBG0_ddr_out_rdadr_mask                                        (0x000FC000)
#define PREDBLK_SLICE_DBG0_ddr_out_rdadr(data)                                       (0x000FC000&((data)<<14))
#define PREDBLK_SLICE_DBG0_ddr_out_rdadr_src(data)                                   ((0x000FC000&(data))>>14)
#define PREDBLK_SLICE_DBG0_get_ddr_out_rdadr(data)                                   ((0x000FC000&(data))>>14)
#define PREDBLK_SLICE_DBG0_inb_mbcnt_shift                                           (10)
#define PREDBLK_SLICE_DBG0_inb_mbcnt_mask                                            (0x00003C00)
#define PREDBLK_SLICE_DBG0_inb_mbcnt(data)                                           (0x00003C00&((data)<<10))
#define PREDBLK_SLICE_DBG0_inb_mbcnt_src(data)                                       ((0x00003C00&(data))>>10)
#define PREDBLK_SLICE_DBG0_get_inb_mbcnt(data)                                       ((0x00003C00&(data))>>10)
#define PREDBLK_SLICE_DBG0_out_mbcnt_shift                                           (6)
#define PREDBLK_SLICE_DBG0_out_mbcnt_mask                                            (0x000003C0)
#define PREDBLK_SLICE_DBG0_out_mbcnt(data)                                           (0x000003C0&((data)<<6))
#define PREDBLK_SLICE_DBG0_out_mbcnt_src(data)                                       ((0x000003C0&(data))>>6)
#define PREDBLK_SLICE_DBG0_get_out_mbcnt(data)                                       ((0x000003C0&(data))>>6)
#define PREDBLK_SLICE_DBG0_pmem_inb_mbptr_shift                                      (3)
#define PREDBLK_SLICE_DBG0_pmem_inb_mbptr_mask                                       (0x00000038)
#define PREDBLK_SLICE_DBG0_pmem_inb_mbptr(data)                                      (0x00000038&((data)<<3))
#define PREDBLK_SLICE_DBG0_pmem_inb_mbptr_src(data)                                  ((0x00000038&(data))>>3)
#define PREDBLK_SLICE_DBG0_get_pmem_inb_mbptr(data)                                  ((0x00000038&(data))>>3)
#define PREDBLK_SLICE_DBG0_pmem_out_mbptr_shift                                      (0)
#define PREDBLK_SLICE_DBG0_pmem_out_mbptr_mask                                       (0x00000007)
#define PREDBLK_SLICE_DBG0_pmem_out_mbptr(data)                                      (0x00000007&((data)<<0))
#define PREDBLK_SLICE_DBG0_pmem_out_mbptr_src(data)                                  ((0x00000007&(data))>>0)
#define PREDBLK_SLICE_DBG0_get_pmem_out_mbptr(data)                                  ((0x00000007&(data))>>0)


#define PREDBLK_SLICE_DBG1                                                           0x1800E99C
#define PREDBLK_SLICE_DBG1_reg_addr                                                  "0xB800E99C"
#define PREDBLK_SLICE_DBG1_reg                                                       0xB800E99C
#define set_PREDBLK_SLICE_DBG1_reg(data)   (*((volatile unsigned int*) PREDBLK_SLICE_DBG1_reg)=data)
#define get_PREDBLK_SLICE_DBG1_reg   (*((volatile unsigned int*) PREDBLK_SLICE_DBG1_reg))
#define PREDBLK_SLICE_DBG1_inst_adr                                                  "0x0067"
#define PREDBLK_SLICE_DBG1_inst                                                      0x0067
#define PREDBLK_SLICE_DBG1_ddr_rng_rdptr_shift                                       (20)
#define PREDBLK_SLICE_DBG1_ddr_rng_rdptr_mask                                        (0x3FF00000)
#define PREDBLK_SLICE_DBG1_ddr_rng_rdptr(data)                                       (0x3FF00000&((data)<<20))
#define PREDBLK_SLICE_DBG1_ddr_rng_rdptr_src(data)                                   ((0x3FF00000&(data))>>20)
#define PREDBLK_SLICE_DBG1_get_ddr_rng_rdptr(data)                                   ((0x3FF00000&(data))>>20)
#define PREDBLK_SLICE_DBG1_ddr_rng_wrptr_shift                                       (10)
#define PREDBLK_SLICE_DBG1_ddr_rng_wrptr_mask                                        (0x000FFC00)
#define PREDBLK_SLICE_DBG1_ddr_rng_wrptr(data)                                       (0x000FFC00&((data)<<10))
#define PREDBLK_SLICE_DBG1_ddr_rng_wrptr_src(data)                                   ((0x000FFC00&(data))>>10)
#define PREDBLK_SLICE_DBG1_get_ddr_rng_wrptr(data)                                   ((0x000FFC00&(data))>>10)
#define PREDBLK_SLICE_DBG1_ddr_rng_size_shift                                        (0)
#define PREDBLK_SLICE_DBG1_ddr_rng_size_mask                                         (0x000003FF)
#define PREDBLK_SLICE_DBG1_ddr_rng_size(data)                                        (0x000003FF&((data)<<0))
#define PREDBLK_SLICE_DBG1_ddr_rng_size_src(data)                                    ((0x000003FF&(data))>>0)
#define PREDBLK_SLICE_DBG1_get_ddr_rng_size(data)                                    ((0x000003FF&(data))>>0)


#endif
