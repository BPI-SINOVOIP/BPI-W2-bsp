/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/24 15:23:28
***************************************************************/


#ifndef _GAMMA_REG_H_INCLUDED_
#define _GAMMA_REG_H_INCLUDED_
#ifdef  _GAMMA_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     GAMMA_AX_RW_Sel:2;
unsigned int     GAMMA_AX_Ch_Sel:2;
unsigned int     GAMMA_AX_Type_Sel:1;
}GAMMA_CTRL_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     GAMMA_FIFO_Empty:1;
unsigned int     GAMMA_FIFO_Full:1;
unsigned int     GAMMA_WR_Error:1;
}GAMMA_STATUS;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     GAMMA_R_En:1;
unsigned int     GAMMA_G_En:1;
unsigned int     GAMMA_B_En:1;
unsigned int     GAMMA_M_TAB_Sel:1;
unsigned int     Dummy:5;
}GAMMA_CTRL_2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     RME:1;
unsigned int     RM_3:1;
unsigned int     RM_2:1;
unsigned int     RM_1:1;
unsigned int     RM_0:1;
}BIST_RM;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     bist_fail2:1;
unsigned int     bist_fail1:1;
unsigned int     bist_fail0:1;
unsigned int     bist_done:1;
}BIST_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_start_pause:1;
unsigned int     reserved_1:12;
unsigned int     drf_fail2:1;
unsigned int     drf_fail1:1;
unsigned int     drf_fail0:1;
unsigned int     drf_done:1;
}DRF_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     drf_test_resume:1;
unsigned int     drf_bist_mode:1;
unsigned int     bist_mode:1;
}MBIST_CON;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     D_Stat_SrcSel:1;
unsigned int     reserved_1:4;
unsigned int     R_Low:10;
unsigned int     reserved_2:6;
unsigned int     R_High:10;
}DSTAT_CTRL_R;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     G_Low:10;
unsigned int     reserved_1:6;
unsigned int     G_High:10;
}DSTAT_CTRL_G;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     B_Low:10;
unsigned int     reserved_1:6;
unsigned int     B_High:10;
}DSTAT_CTRL_B;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     R_Cnt:21;
}DSTAT_O_R1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     R_Min:10;
unsigned int     reserved_1:6;
unsigned int     R_Max:10;
}DSTAT_O_R2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     G_Cnt:21;
}DSTAT_O_G1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     G_Min:10;
unsigned int     reserved_1:6;
unsigned int     G_Max:10;
}DSTAT_O_G2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     B_Cnt:21;
}DSTAT_O_B1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     B_Min:10;
unsigned int     reserved_1:6;
unsigned int     B_Max:10;
}DSTAT_O_B2;

#endif

#define GAMMA_CTRL_1                                                                 0x18009864
#define GAMMA_CTRL_1_reg_addr                                                        "0xB8009864"
#define GAMMA_CTRL_1_reg                                                             0xB8009864
#define set_GAMMA_CTRL_1_reg(data)   (*((volatile unsigned int*) GAMMA_CTRL_1_reg)=data)
#define get_GAMMA_CTRL_1_reg   (*((volatile unsigned int*) GAMMA_CTRL_1_reg))
#define GAMMA_CTRL_1_inst_adr                                                        "0x0019"
#define GAMMA_CTRL_1_inst                                                            0x0019
#define GAMMA_CTRL_1_GAMMA_AX_RW_Sel_shift                                           (3)
#define GAMMA_CTRL_1_GAMMA_AX_RW_Sel_mask                                            (0x00000018)
#define GAMMA_CTRL_1_GAMMA_AX_RW_Sel(data)                                           (0x00000018&((data)<<3))
#define GAMMA_CTRL_1_GAMMA_AX_RW_Sel_src(data)                                       ((0x00000018&(data))>>3)
#define GAMMA_CTRL_1_get_GAMMA_AX_RW_Sel(data)                                       ((0x00000018&(data))>>3)
#define GAMMA_CTRL_1_GAMMA_AX_Ch_Sel_shift                                           (1)
#define GAMMA_CTRL_1_GAMMA_AX_Ch_Sel_mask                                            (0x00000006)
#define GAMMA_CTRL_1_GAMMA_AX_Ch_Sel(data)                                           (0x00000006&((data)<<1))
#define GAMMA_CTRL_1_GAMMA_AX_Ch_Sel_src(data)                                       ((0x00000006&(data))>>1)
#define GAMMA_CTRL_1_get_GAMMA_AX_Ch_Sel(data)                                       ((0x00000006&(data))>>1)
#define GAMMA_CTRL_1_GAMMA_AX_Type_Sel_shift                                         (0)
#define GAMMA_CTRL_1_GAMMA_AX_Type_Sel_mask                                          (0x00000001)
#define GAMMA_CTRL_1_GAMMA_AX_Type_Sel(data)                                         (0x00000001&((data)<<0))
#define GAMMA_CTRL_1_GAMMA_AX_Type_Sel_src(data)                                     ((0x00000001&(data))>>0)
#define GAMMA_CTRL_1_get_GAMMA_AX_Type_Sel(data)                                     ((0x00000001&(data))>>0)


#define GAMMA_STATUS                                                                 0x18009868
#define GAMMA_STATUS_reg_addr                                                        "0xB8009868"
#define GAMMA_STATUS_reg                                                             0xB8009868
#define set_GAMMA_STATUS_reg(data)   (*((volatile unsigned int*) GAMMA_STATUS_reg)=data)
#define get_GAMMA_STATUS_reg   (*((volatile unsigned int*) GAMMA_STATUS_reg))
#define GAMMA_STATUS_inst_adr                                                        "0x001A"
#define GAMMA_STATUS_inst                                                            0x001A
#define GAMMA_STATUS_GAMMA_FIFO_Empty_shift                                          (2)
#define GAMMA_STATUS_GAMMA_FIFO_Empty_mask                                           (0x00000004)
#define GAMMA_STATUS_GAMMA_FIFO_Empty(data)                                          (0x00000004&((data)<<2))
#define GAMMA_STATUS_GAMMA_FIFO_Empty_src(data)                                      ((0x00000004&(data))>>2)
#define GAMMA_STATUS_get_GAMMA_FIFO_Empty(data)                                      ((0x00000004&(data))>>2)
#define GAMMA_STATUS_GAMMA_FIFO_Full_shift                                           (1)
#define GAMMA_STATUS_GAMMA_FIFO_Full_mask                                            (0x00000002)
#define GAMMA_STATUS_GAMMA_FIFO_Full(data)                                           (0x00000002&((data)<<1))
#define GAMMA_STATUS_GAMMA_FIFO_Full_src(data)                                       ((0x00000002&(data))>>1)
#define GAMMA_STATUS_get_GAMMA_FIFO_Full(data)                                       ((0x00000002&(data))>>1)
#define GAMMA_STATUS_GAMMA_WR_Error_shift                                            (0)
#define GAMMA_STATUS_GAMMA_WR_Error_mask                                             (0x00000001)
#define GAMMA_STATUS_GAMMA_WR_Error(data)                                            (0x00000001&((data)<<0))
#define GAMMA_STATUS_GAMMA_WR_Error_src(data)                                        ((0x00000001&(data))>>0)
#define GAMMA_STATUS_get_GAMMA_WR_Error(data)                                        ((0x00000001&(data))>>0)


#define GAMMA_CTRL_2                                                                 0x1800986c
#define GAMMA_CTRL_2_reg_addr                                                        "0xB800986C"
#define GAMMA_CTRL_2_reg                                                             0xB800986C
#define set_GAMMA_CTRL_2_reg(data)   (*((volatile unsigned int*) GAMMA_CTRL_2_reg)=data)
#define get_GAMMA_CTRL_2_reg   (*((volatile unsigned int*) GAMMA_CTRL_2_reg))
#define GAMMA_CTRL_2_inst_adr                                                        "0x001B"
#define GAMMA_CTRL_2_inst                                                            0x001B
#define GAMMA_CTRL_2_GAMMA_R_En_shift                                                (8)
#define GAMMA_CTRL_2_GAMMA_R_En_mask                                                 (0x00000100)
#define GAMMA_CTRL_2_GAMMA_R_En(data)                                                (0x00000100&((data)<<8))
#define GAMMA_CTRL_2_GAMMA_R_En_src(data)                                            ((0x00000100&(data))>>8)
#define GAMMA_CTRL_2_get_GAMMA_R_En(data)                                            ((0x00000100&(data))>>8)
#define GAMMA_CTRL_2_GAMMA_G_En_shift                                                (7)
#define GAMMA_CTRL_2_GAMMA_G_En_mask                                                 (0x00000080)
#define GAMMA_CTRL_2_GAMMA_G_En(data)                                                (0x00000080&((data)<<7))
#define GAMMA_CTRL_2_GAMMA_G_En_src(data)                                            ((0x00000080&(data))>>7)
#define GAMMA_CTRL_2_get_GAMMA_G_En(data)                                            ((0x00000080&(data))>>7)
#define GAMMA_CTRL_2_GAMMA_B_En_shift                                                (6)
#define GAMMA_CTRL_2_GAMMA_B_En_mask                                                 (0x00000040)
#define GAMMA_CTRL_2_GAMMA_B_En(data)                                                (0x00000040&((data)<<6))
#define GAMMA_CTRL_2_GAMMA_B_En_src(data)                                            ((0x00000040&(data))>>6)
#define GAMMA_CTRL_2_get_GAMMA_B_En(data)                                            ((0x00000040&(data))>>6)
#define GAMMA_CTRL_2_GAMMA_M_TAB_Sel_shift                                           (5)
#define GAMMA_CTRL_2_GAMMA_M_TAB_Sel_mask                                            (0x00000020)
#define GAMMA_CTRL_2_GAMMA_M_TAB_Sel(data)                                           (0x00000020&((data)<<5))
#define GAMMA_CTRL_2_GAMMA_M_TAB_Sel_src(data)                                       ((0x00000020&(data))>>5)
#define GAMMA_CTRL_2_get_GAMMA_M_TAB_Sel(data)                                       ((0x00000020&(data))>>5)
#define GAMMA_CTRL_2_Dummy_shift                                                     (0)
#define GAMMA_CTRL_2_Dummy_mask                                                      (0x0000001F)
#define GAMMA_CTRL_2_Dummy(data)                                                     (0x0000001F&((data)<<0))
#define GAMMA_CTRL_2_Dummy_src(data)                                                 ((0x0000001F&(data))>>0)
#define GAMMA_CTRL_2_get_Dummy(data)                                                 ((0x0000001F&(data))>>0)


#define BIST_RM                                                                      0x18009870
#define BIST_RM_reg_addr                                                             "0xB8009870"
#define BIST_RM_reg                                                                  0xB8009870
#define set_BIST_RM_reg(data)   (*((volatile unsigned int*) BIST_RM_reg)=data)
#define get_BIST_RM_reg   (*((volatile unsigned int*) BIST_RM_reg))
#define BIST_RM_inst_adr                                                             "0x001C"
#define BIST_RM_inst                                                                 0x001C
#define BIST_RM_RME_shift                                                            (4)
#define BIST_RM_RME_mask                                                             (0x00000010)
#define BIST_RM_RME(data)                                                            (0x00000010&((data)<<4))
#define BIST_RM_RME_src(data)                                                        ((0x00000010&(data))>>4)
#define BIST_RM_get_RME(data)                                                        ((0x00000010&(data))>>4)
#define BIST_RM_RM_3_shift                                                           (3)
#define BIST_RM_RM_3_mask                                                            (0x00000008)
#define BIST_RM_RM_3(data)                                                           (0x00000008&((data)<<3))
#define BIST_RM_RM_3_src(data)                                                       ((0x00000008&(data))>>3)
#define BIST_RM_get_RM_3(data)                                                       ((0x00000008&(data))>>3)
#define BIST_RM_RM_2_shift                                                           (2)
#define BIST_RM_RM_2_mask                                                            (0x00000004)
#define BIST_RM_RM_2(data)                                                           (0x00000004&((data)<<2))
#define BIST_RM_RM_2_src(data)                                                       ((0x00000004&(data))>>2)
#define BIST_RM_get_RM_2(data)                                                       ((0x00000004&(data))>>2)
#define BIST_RM_RM_1_shift                                                           (1)
#define BIST_RM_RM_1_mask                                                            (0x00000002)
#define BIST_RM_RM_1(data)                                                           (0x00000002&((data)<<1))
#define BIST_RM_RM_1_src(data)                                                       ((0x00000002&(data))>>1)
#define BIST_RM_get_RM_1(data)                                                       ((0x00000002&(data))>>1)
#define BIST_RM_RM_0_shift                                                           (0)
#define BIST_RM_RM_0_mask                                                            (0x00000001)
#define BIST_RM_RM_0(data)                                                           (0x00000001&((data)<<0))
#define BIST_RM_RM_0_src(data)                                                       ((0x00000001&(data))>>0)
#define BIST_RM_get_RM_0(data)                                                       ((0x00000001&(data))>>0)


#define BIST_ST                                                                      0x18009874
#define BIST_ST_reg_addr                                                             "0xB8009874"
#define BIST_ST_reg                                                                  0xB8009874
#define set_BIST_ST_reg(data)   (*((volatile unsigned int*) BIST_ST_reg)=data)
#define get_BIST_ST_reg   (*((volatile unsigned int*) BIST_ST_reg))
#define BIST_ST_inst_adr                                                             "0x001D"
#define BIST_ST_inst                                                                 0x001D
#define BIST_ST_bist_fail2_shift                                                     (3)
#define BIST_ST_bist_fail2_mask                                                      (0x00000008)
#define BIST_ST_bist_fail2(data)                                                     (0x00000008&((data)<<3))
#define BIST_ST_bist_fail2_src(data)                                                 ((0x00000008&(data))>>3)
#define BIST_ST_get_bist_fail2(data)                                                 ((0x00000008&(data))>>3)
#define BIST_ST_bist_fail1_shift                                                     (2)
#define BIST_ST_bist_fail1_mask                                                      (0x00000004)
#define BIST_ST_bist_fail1(data)                                                     (0x00000004&((data)<<2))
#define BIST_ST_bist_fail1_src(data)                                                 ((0x00000004&(data))>>2)
#define BIST_ST_get_bist_fail1(data)                                                 ((0x00000004&(data))>>2)
#define BIST_ST_bist_fail0_shift                                                     (1)
#define BIST_ST_bist_fail0_mask                                                      (0x00000002)
#define BIST_ST_bist_fail0(data)                                                     (0x00000002&((data)<<1))
#define BIST_ST_bist_fail0_src(data)                                                 ((0x00000002&(data))>>1)
#define BIST_ST_get_bist_fail0(data)                                                 ((0x00000002&(data))>>1)
#define BIST_ST_bist_done_shift                                                      (0)
#define BIST_ST_bist_done_mask                                                       (0x00000001)
#define BIST_ST_bist_done(data)                                                      (0x00000001&((data)<<0))
#define BIST_ST_bist_done_src(data)                                                  ((0x00000001&(data))>>0)
#define BIST_ST_get_bist_done(data)                                                  ((0x00000001&(data))>>0)


#define DRF_ST                                                                       0x18009878
#define DRF_ST_reg_addr                                                              "0xB8009878"
#define DRF_ST_reg                                                                   0xB8009878
#define set_DRF_ST_reg(data)   (*((volatile unsigned int*) DRF_ST_reg)=data)
#define get_DRF_ST_reg   (*((volatile unsigned int*) DRF_ST_reg))
#define DRF_ST_inst_adr                                                              "0x001E"
#define DRF_ST_inst                                                                  0x001E
#define DRF_ST_drf_start_pause_shift                                                 (16)
#define DRF_ST_drf_start_pause_mask                                                  (0x00010000)
#define DRF_ST_drf_start_pause(data)                                                 (0x00010000&((data)<<16))
#define DRF_ST_drf_start_pause_src(data)                                             ((0x00010000&(data))>>16)
#define DRF_ST_get_drf_start_pause(data)                                             ((0x00010000&(data))>>16)
#define DRF_ST_drf_fail2_shift                                                       (3)
#define DRF_ST_drf_fail2_mask                                                        (0x00000008)
#define DRF_ST_drf_fail2(data)                                                       (0x00000008&((data)<<3))
#define DRF_ST_drf_fail2_src(data)                                                   ((0x00000008&(data))>>3)
#define DRF_ST_get_drf_fail2(data)                                                   ((0x00000008&(data))>>3)
#define DRF_ST_drf_fail1_shift                                                       (2)
#define DRF_ST_drf_fail1_mask                                                        (0x00000004)
#define DRF_ST_drf_fail1(data)                                                       (0x00000004&((data)<<2))
#define DRF_ST_drf_fail1_src(data)                                                   ((0x00000004&(data))>>2)
#define DRF_ST_get_drf_fail1(data)                                                   ((0x00000004&(data))>>2)
#define DRF_ST_drf_fail0_shift                                                       (1)
#define DRF_ST_drf_fail0_mask                                                        (0x00000002)
#define DRF_ST_drf_fail0(data)                                                       (0x00000002&((data)<<1))
#define DRF_ST_drf_fail0_src(data)                                                   ((0x00000002&(data))>>1)
#define DRF_ST_get_drf_fail0(data)                                                   ((0x00000002&(data))>>1)
#define DRF_ST_drf_done_shift                                                        (0)
#define DRF_ST_drf_done_mask                                                         (0x00000001)
#define DRF_ST_drf_done(data)                                                        (0x00000001&((data)<<0))
#define DRF_ST_drf_done_src(data)                                                    ((0x00000001&(data))>>0)
#define DRF_ST_get_drf_done(data)                                                    ((0x00000001&(data))>>0)


#define MBIST_CON                                                                    0x180098A4
#define MBIST_CON_reg_addr                                                           "0xB80098A4"
#define MBIST_CON_reg                                                                0xB80098A4
#define set_MBIST_CON_reg(data)   (*((volatile unsigned int*) MBIST_CON_reg)=data)
#define get_MBIST_CON_reg   (*((volatile unsigned int*) MBIST_CON_reg))
#define MBIST_CON_inst_adr                                                           "0x0029"
#define MBIST_CON_inst                                                               0x0029
#define MBIST_CON_drf_test_resume_shift                                              (2)
#define MBIST_CON_drf_test_resume_mask                                               (0x00000004)
#define MBIST_CON_drf_test_resume(data)                                              (0x00000004&((data)<<2))
#define MBIST_CON_drf_test_resume_src(data)                                          ((0x00000004&(data))>>2)
#define MBIST_CON_get_drf_test_resume(data)                                          ((0x00000004&(data))>>2)
#define MBIST_CON_drf_bist_mode_shift                                                (1)
#define MBIST_CON_drf_bist_mode_mask                                                 (0x00000002)
#define MBIST_CON_drf_bist_mode(data)                                                (0x00000002&((data)<<1))
#define MBIST_CON_drf_bist_mode_src(data)                                            ((0x00000002&(data))>>1)
#define MBIST_CON_get_drf_bist_mode(data)                                            ((0x00000002&(data))>>1)
#define MBIST_CON_bist_mode_shift                                                    (0)
#define MBIST_CON_bist_mode_mask                                                     (0x00000001)
#define MBIST_CON_bist_mode(data)                                                    (0x00000001&((data)<<0))
#define MBIST_CON_bist_mode_src(data)                                                ((0x00000001&(data))>>0)
#define MBIST_CON_get_bist_mode(data)                                                ((0x00000001&(data))>>0)


#define DSTAT_CTRL_R                                                                 0x18009880
#define DSTAT_CTRL_R_reg_addr                                                        "0xB8009880"
#define DSTAT_CTRL_R_reg                                                             0xB8009880
#define set_DSTAT_CTRL_R_reg(data)   (*((volatile unsigned int*) DSTAT_CTRL_R_reg)=data)
#define get_DSTAT_CTRL_R_reg   (*((volatile unsigned int*) DSTAT_CTRL_R_reg))
#define DSTAT_CTRL_R_inst_adr                                                        "0x0020"
#define DSTAT_CTRL_R_inst                                                            0x0020
#define DSTAT_CTRL_R_D_Stat_SrcSel_shift                                             (30)
#define DSTAT_CTRL_R_D_Stat_SrcSel_mask                                              (0x40000000)
#define DSTAT_CTRL_R_D_Stat_SrcSel(data)                                             (0x40000000&((data)<<30))
#define DSTAT_CTRL_R_D_Stat_SrcSel_src(data)                                         ((0x40000000&(data))>>30)
#define DSTAT_CTRL_R_get_D_Stat_SrcSel(data)                                         ((0x40000000&(data))>>30)
#define DSTAT_CTRL_R_R_Low_shift                                                     (16)
#define DSTAT_CTRL_R_R_Low_mask                                                      (0x03FF0000)
#define DSTAT_CTRL_R_R_Low(data)                                                     (0x03FF0000&((data)<<16))
#define DSTAT_CTRL_R_R_Low_src(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_R_get_R_Low(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_R_R_High_shift                                                    (0)
#define DSTAT_CTRL_R_R_High_mask                                                     (0x000003FF)
#define DSTAT_CTRL_R_R_High(data)                                                    (0x000003FF&((data)<<0))
#define DSTAT_CTRL_R_R_High_src(data)                                                ((0x000003FF&(data))>>0)
#define DSTAT_CTRL_R_get_R_High(data)                                                ((0x000003FF&(data))>>0)


#define DSTAT_CTRL_G                                                                 0x18009884
#define DSTAT_CTRL_G_reg_addr                                                        "0xB8009884"
#define DSTAT_CTRL_G_reg                                                             0xB8009884
#define set_DSTAT_CTRL_G_reg(data)   (*((volatile unsigned int*) DSTAT_CTRL_G_reg)=data)
#define get_DSTAT_CTRL_G_reg   (*((volatile unsigned int*) DSTAT_CTRL_G_reg))
#define DSTAT_CTRL_G_inst_adr                                                        "0x0021"
#define DSTAT_CTRL_G_inst                                                            0x0021
#define DSTAT_CTRL_G_G_Low_shift                                                     (16)
#define DSTAT_CTRL_G_G_Low_mask                                                      (0x03FF0000)
#define DSTAT_CTRL_G_G_Low(data)                                                     (0x03FF0000&((data)<<16))
#define DSTAT_CTRL_G_G_Low_src(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_G_get_G_Low(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_G_G_High_shift                                                    (0)
#define DSTAT_CTRL_G_G_High_mask                                                     (0x000003FF)
#define DSTAT_CTRL_G_G_High(data)                                                    (0x000003FF&((data)<<0))
#define DSTAT_CTRL_G_G_High_src(data)                                                ((0x000003FF&(data))>>0)
#define DSTAT_CTRL_G_get_G_High(data)                                                ((0x000003FF&(data))>>0)


#define DSTAT_CTRL_B                                                                 0x18009888
#define DSTAT_CTRL_B_reg_addr                                                        "0xB8009888"
#define DSTAT_CTRL_B_reg                                                             0xB8009888
#define set_DSTAT_CTRL_B_reg(data)   (*((volatile unsigned int*) DSTAT_CTRL_B_reg)=data)
#define get_DSTAT_CTRL_B_reg   (*((volatile unsigned int*) DSTAT_CTRL_B_reg))
#define DSTAT_CTRL_B_inst_adr                                                        "0x0022"
#define DSTAT_CTRL_B_inst                                                            0x0022
#define DSTAT_CTRL_B_B_Low_shift                                                     (16)
#define DSTAT_CTRL_B_B_Low_mask                                                      (0x03FF0000)
#define DSTAT_CTRL_B_B_Low(data)                                                     (0x03FF0000&((data)<<16))
#define DSTAT_CTRL_B_B_Low_src(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_B_get_B_Low(data)                                                 ((0x03FF0000&(data))>>16)
#define DSTAT_CTRL_B_B_High_shift                                                    (0)
#define DSTAT_CTRL_B_B_High_mask                                                     (0x000003FF)
#define DSTAT_CTRL_B_B_High(data)                                                    (0x000003FF&((data)<<0))
#define DSTAT_CTRL_B_B_High_src(data)                                                ((0x000003FF&(data))>>0)
#define DSTAT_CTRL_B_get_B_High(data)                                                ((0x000003FF&(data))>>0)


#define DSTAT_O_R1                                                                   0x1800988c
#define DSTAT_O_R1_reg_addr                                                          "0xB800988C"
#define DSTAT_O_R1_reg                                                               0xB800988C
#define set_DSTAT_O_R1_reg(data)   (*((volatile unsigned int*) DSTAT_O_R1_reg)=data)
#define get_DSTAT_O_R1_reg   (*((volatile unsigned int*) DSTAT_O_R1_reg))
#define DSTAT_O_R1_inst_adr                                                          "0x0023"
#define DSTAT_O_R1_inst                                                              0x0023
#define DSTAT_O_R1_R_Cnt_shift                                                       (0)
#define DSTAT_O_R1_R_Cnt_mask                                                        (0x001FFFFF)
#define DSTAT_O_R1_R_Cnt(data)                                                       (0x001FFFFF&((data)<<0))
#define DSTAT_O_R1_R_Cnt_src(data)                                                   ((0x001FFFFF&(data))>>0)
#define DSTAT_O_R1_get_R_Cnt(data)                                                   ((0x001FFFFF&(data))>>0)


#define DSTAT_O_R2                                                                   0x18009890
#define DSTAT_O_R2_reg_addr                                                          "0xB8009890"
#define DSTAT_O_R2_reg                                                               0xB8009890
#define set_DSTAT_O_R2_reg(data)   (*((volatile unsigned int*) DSTAT_O_R2_reg)=data)
#define get_DSTAT_O_R2_reg   (*((volatile unsigned int*) DSTAT_O_R2_reg))
#define DSTAT_O_R2_inst_adr                                                          "0x0024"
#define DSTAT_O_R2_inst                                                              0x0024
#define DSTAT_O_R2_R_Min_shift                                                       (16)
#define DSTAT_O_R2_R_Min_mask                                                        (0x03FF0000)
#define DSTAT_O_R2_R_Min(data)                                                       (0x03FF0000&((data)<<16))
#define DSTAT_O_R2_R_Min_src(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_R2_get_R_Min(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_R2_R_Max_shift                                                       (0)
#define DSTAT_O_R2_R_Max_mask                                                        (0x000003FF)
#define DSTAT_O_R2_R_Max(data)                                                       (0x000003FF&((data)<<0))
#define DSTAT_O_R2_R_Max_src(data)                                                   ((0x000003FF&(data))>>0)
#define DSTAT_O_R2_get_R_Max(data)                                                   ((0x000003FF&(data))>>0)


#define DSTAT_O_G1                                                                   0x18009894
#define DSTAT_O_G1_reg_addr                                                          "0xB8009894"
#define DSTAT_O_G1_reg                                                               0xB8009894
#define set_DSTAT_O_G1_reg(data)   (*((volatile unsigned int*) DSTAT_O_G1_reg)=data)
#define get_DSTAT_O_G1_reg   (*((volatile unsigned int*) DSTAT_O_G1_reg))
#define DSTAT_O_G1_inst_adr                                                          "0x0025"
#define DSTAT_O_G1_inst                                                              0x0025
#define DSTAT_O_G1_G_Cnt_shift                                                       (0)
#define DSTAT_O_G1_G_Cnt_mask                                                        (0x001FFFFF)
#define DSTAT_O_G1_G_Cnt(data)                                                       (0x001FFFFF&((data)<<0))
#define DSTAT_O_G1_G_Cnt_src(data)                                                   ((0x001FFFFF&(data))>>0)
#define DSTAT_O_G1_get_G_Cnt(data)                                                   ((0x001FFFFF&(data))>>0)


#define DSTAT_O_G2                                                                   0x18009898
#define DSTAT_O_G2_reg_addr                                                          "0xB8009898"
#define DSTAT_O_G2_reg                                                               0xB8009898
#define set_DSTAT_O_G2_reg(data)   (*((volatile unsigned int*) DSTAT_O_G2_reg)=data)
#define get_DSTAT_O_G2_reg   (*((volatile unsigned int*) DSTAT_O_G2_reg))
#define DSTAT_O_G2_inst_adr                                                          "0x0026"
#define DSTAT_O_G2_inst                                                              0x0026
#define DSTAT_O_G2_G_Min_shift                                                       (16)
#define DSTAT_O_G2_G_Min_mask                                                        (0x03FF0000)
#define DSTAT_O_G2_G_Min(data)                                                       (0x03FF0000&((data)<<16))
#define DSTAT_O_G2_G_Min_src(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_G2_get_G_Min(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_G2_G_Max_shift                                                       (0)
#define DSTAT_O_G2_G_Max_mask                                                        (0x000003FF)
#define DSTAT_O_G2_G_Max(data)                                                       (0x000003FF&((data)<<0))
#define DSTAT_O_G2_G_Max_src(data)                                                   ((0x000003FF&(data))>>0)
#define DSTAT_O_G2_get_G_Max(data)                                                   ((0x000003FF&(data))>>0)


#define DSTAT_O_B1                                                                   0x1800989c
#define DSTAT_O_B1_reg_addr                                                          "0xB800989C"
#define DSTAT_O_B1_reg                                                               0xB800989C
#define set_DSTAT_O_B1_reg(data)   (*((volatile unsigned int*) DSTAT_O_B1_reg)=data)
#define get_DSTAT_O_B1_reg   (*((volatile unsigned int*) DSTAT_O_B1_reg))
#define DSTAT_O_B1_inst_adr                                                          "0x0027"
#define DSTAT_O_B1_inst                                                              0x0027
#define DSTAT_O_B1_B_Cnt_shift                                                       (0)
#define DSTAT_O_B1_B_Cnt_mask                                                        (0x001FFFFF)
#define DSTAT_O_B1_B_Cnt(data)                                                       (0x001FFFFF&((data)<<0))
#define DSTAT_O_B1_B_Cnt_src(data)                                                   ((0x001FFFFF&(data))>>0)
#define DSTAT_O_B1_get_B_Cnt(data)                                                   ((0x001FFFFF&(data))>>0)


#define DSTAT_O_B2                                                                   0x180098a0
#define DSTAT_O_B2_reg_addr                                                          "0xB80098A0"
#define DSTAT_O_B2_reg                                                               0xB80098A0
#define set_DSTAT_O_B2_reg(data)   (*((volatile unsigned int*) DSTAT_O_B2_reg)=data)
#define get_DSTAT_O_B2_reg   (*((volatile unsigned int*) DSTAT_O_B2_reg))
#define DSTAT_O_B2_inst_adr                                                          "0x0028"
#define DSTAT_O_B2_inst                                                              0x0028
#define DSTAT_O_B2_B_Min_shift                                                       (16)
#define DSTAT_O_B2_B_Min_mask                                                        (0x03FF0000)
#define DSTAT_O_B2_B_Min(data)                                                       (0x03FF0000&((data)<<16))
#define DSTAT_O_B2_B_Min_src(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_B2_get_B_Min(data)                                                   ((0x03FF0000&(data))>>16)
#define DSTAT_O_B2_B_Max_shift                                                       (0)
#define DSTAT_O_B2_B_Max_mask                                                        (0x000003FF)
#define DSTAT_O_B2_B_Max(data)                                                       (0x000003FF&((data)<<0))
#define DSTAT_O_B2_B_Max_src(data)                                                   ((0x000003FF&(data))>>0)
#define DSTAT_O_B2_get_B_Max(data)                                                   ((0x000003FF&(data))>>0)


#endif
