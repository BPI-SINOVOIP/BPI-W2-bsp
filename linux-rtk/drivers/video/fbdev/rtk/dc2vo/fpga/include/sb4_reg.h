/**************************************************************
// Spec Version                  : 0.1.2
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 1.0 2006.04.18
// Naming Rule                   : Module_Register_Name
// Firmware Header Generate Date : 2007/12/7
***************************************************************/


#ifndef _SB4_REG_H_INCLUDED_
#define _SB4_REG_H_INCLUDED_
#ifdef  _SB4_USE_STRUCT
typedef struct 
{
unsigned int     write_enable4:1;
unsigned int     dmy:18;
unsigned int     write_enable3:1;
unsigned int     wl:6;
unsigned int     write_enable2:1;
unsigned int     en_me2_mreq:1;
unsigned int     en_me1_mreq:1;
unsigned int     en_ve1b_mreq:1;
unsigned int     write_enable1:1;
unsigned int     rr:1;
}SB4_CTRL;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     ve2:6;
unsigned int     reserved_1:2;
unsigned int     ve1s:6;
unsigned int     reserved_2:2;
unsigned int     ve1b:6;
unsigned int     reserved_3:2;
unsigned int     se:6;
}SB4_PRIORITY1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     me2:6;
unsigned int     reserved_1:2;
unsigned int     me1:6;
}SB4_PRIORITY2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     status_id:6;
unsigned int     reserved_1:2;
unsigned int     mask_id:6;
}SB4_MASK;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_enable2:1;
unsigned int     pc2_go:1;
unsigned int     pc2_sel:6;
unsigned int     write_enable1:1;
unsigned int     pc1_go:1;
unsigned int     pc1_sel:6;
}SB4_PC_CTRL;

typedef struct 
{
unsigned int     tol:32;
}SB4_PC1_CYC;

typedef struct 
{
unsigned int     tol_cyc:32;
}SB4_PC1_ACK;

typedef struct 
{
unsigned int     req_lat:32;
}SB4_PC1_ACC;

typedef struct 
{
unsigned int     max_lat:16;
unsigned int     tol_num:16;
}SB4_PC1_REQ;

typedef struct 
{
unsigned int     tol:32;
}SB4_PC2_CYC;

typedef struct 
{
unsigned int     tol_cyc:32;
}SB4_PC2_ACK;

typedef struct 
{
unsigned int     req_lat:32;
}SB4_PC2_ACC;

typedef struct 
{
unsigned int     max_lat:16;
unsigned int     tol_num:16;
}SB4_PC2_REQ;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}SB4_DBG;

#endif

#define SB4_CTRL                                                                     0x1801C600
#define SB4_CTRL_reg_addr                                                            "0xB801C600"
#define SB4_CTRL_reg                                                                 0xB801C600
#define SB4_CTRL_inst_adr                                                            "0x0080"
#define SB4_CTRL_inst                                                                0x0080
#define SB4_CTRL_write_enable4_shift                                                 (31)
#define SB4_CTRL_write_enable4_mask                                                  (0x80000000)
#define SB4_CTRL_write_enable4(data)                                                 (0x80000000&((data)<<31))
#define SB4_CTRL_write_enable4_src(data)                                             ((0x80000000&(data))>>31)
#define SB4_CTRL_dmy_shift                                                           (13)
#define SB4_CTRL_dmy_mask                                                            (0x7FFFE000)
#define SB4_CTRL_dmy(data)                                                           (0x7FFFE000&((data)<<13))
#define SB4_CTRL_dmy_src(data)                                                       ((0x7FFFE000&(data))>>13)
#define SB4_CTRL_write_enable3_shift                                                 (12)
#define SB4_CTRL_write_enable3_mask                                                  (0x00001000)
#define SB4_CTRL_write_enable3(data)                                                 (0x00001000&((data)<<12))
#define SB4_CTRL_write_enable3_src(data)                                             ((0x00001000&(data))>>12)
#define SB4_CTRL_wl_shift                                                            (6)
#define SB4_CTRL_wl_mask                                                             (0x00000FC0)
#define SB4_CTRL_wl(data)                                                            (0x00000FC0&((data)<<6))
#define SB4_CTRL_wl_src(data)                                                        ((0x00000FC0&(data))>>6)
#define SB4_CTRL_write_enable2_shift                                                 (5)
#define SB4_CTRL_write_enable2_mask                                                  (0x00000020)
#define SB4_CTRL_write_enable2(data)                                                 (0x00000020&((data)<<5))
#define SB4_CTRL_write_enable2_src(data)                                             ((0x00000020&(data))>>5)
#define SB4_CTRL_en_me2_mreq_shift                                                   (4)
#define SB4_CTRL_en_me2_mreq_mask                                                    (0x00000010)
#define SB4_CTRL_en_me2_mreq(data)                                                   (0x00000010&((data)<<4))
#define SB4_CTRL_en_me2_mreq_src(data)                                               ((0x00000010&(data))>>4)
#define SB4_CTRL_en_me1_mreq_shift                                                   (3)
#define SB4_CTRL_en_me1_mreq_mask                                                    (0x00000008)
#define SB4_CTRL_en_me1_mreq(data)                                                   (0x00000008&((data)<<3))
#define SB4_CTRL_en_me1_mreq_src(data)                                               ((0x00000008&(data))>>3)
#define SB4_CTRL_en_ve1b_mreq_shift                                                  (2)
#define SB4_CTRL_en_ve1b_mreq_mask                                                   (0x00000004)
#define SB4_CTRL_en_ve1b_mreq(data)                                                  (0x00000004&((data)<<2))
#define SB4_CTRL_en_ve1b_mreq_src(data)                                              ((0x00000004&(data))>>2)
#define SB4_CTRL_write_enable1_shift                                                 (1)
#define SB4_CTRL_write_enable1_mask                                                  (0x00000002)
#define SB4_CTRL_write_enable1(data)                                                 (0x00000002&((data)<<1))
#define SB4_CTRL_write_enable1_src(data)                                             ((0x00000002&(data))>>1)
#define SB4_CTRL_rr_shift                                                            (0)
#define SB4_CTRL_rr_mask                                                             (0x00000001)
#define SB4_CTRL_rr(data)                                                            (0x00000001&((data)<<0))
#define SB4_CTRL_rr_src(data)                                                        ((0x00000001&(data))>>0)


#define SB4_PRIORITY1                                                                0x1801C604
#define SB4_PRIORITY1_reg_addr                                                       "0xB801C604"
#define SB4_PRIORITY1_reg                                                            0xB801C604
#define SB4_PRIORITY1_inst_adr                                                       "0x0081"
#define SB4_PRIORITY1_inst                                                           0x0081
#define SB4_PRIORITY1_ve2_shift                                                      (24)
#define SB4_PRIORITY1_ve2_mask                                                       (0x3F000000)
#define SB4_PRIORITY1_ve2(data)                                                      (0x3F000000&((data)<<24))
#define SB4_PRIORITY1_ve2_src(data)                                                  ((0x3F000000&(data))>>24)
#define SB4_PRIORITY1_ve1s_shift                                                     (16)
#define SB4_PRIORITY1_ve1s_mask                                                      (0x003F0000)
#define SB4_PRIORITY1_ve1s(data)                                                     (0x003F0000&((data)<<16))
#define SB4_PRIORITY1_ve1s_src(data)                                                 ((0x003F0000&(data))>>16)
#define SB4_PRIORITY1_ve1b_shift                                                     (8)
#define SB4_PRIORITY1_ve1b_mask                                                      (0x00003F00)
#define SB4_PRIORITY1_ve1b(data)                                                     (0x00003F00&((data)<<8))
#define SB4_PRIORITY1_ve1b_src(data)                                                 ((0x00003F00&(data))>>8)
#define SB4_PRIORITY1_se_shift                                                       (0)
#define SB4_PRIORITY1_se_mask                                                        (0x0000003F)
#define SB4_PRIORITY1_se(data)                                                       (0x0000003F&((data)<<0))
#define SB4_PRIORITY1_se_src(data)                                                   ((0x0000003F&(data))>>0)


#define SB4_PRIORITY2                                                                0x1801C608
#define SB4_PRIORITY2_reg_addr                                                       "0xB801C608"
#define SB4_PRIORITY2_reg                                                            0xB801C608
#define SB4_PRIORITY2_inst_adr                                                       "0x0082"
#define SB4_PRIORITY2_inst                                                           0x0082
#define SB4_PRIORITY2_me2_shift                                                      (8)
#define SB4_PRIORITY2_me2_mask                                                       (0x00003F00)
#define SB4_PRIORITY2_me2(data)                                                      (0x00003F00&((data)<<8))
#define SB4_PRIORITY2_me2_src(data)                                                  ((0x00003F00&(data))>>8)
#define SB4_PRIORITY2_me1_shift                                                      (0)
#define SB4_PRIORITY2_me1_mask                                                       (0x0000003F)
#define SB4_PRIORITY2_me1(data)                                                      (0x0000003F&((data)<<0))
#define SB4_PRIORITY2_me1_src(data)                                                  ((0x0000003F&(data))>>0)


#define SB4_MASK                                                                     0x1801C60C
#define SB4_MASK_reg_addr                                                            "0xB801C60C"
#define SB4_MASK_reg                                                                 0xB801C60C
#define SB4_MASK_inst_adr                                                            "0x0083"
#define SB4_MASK_inst                                                                0x0083
#define SB4_MASK_status_id_shift                                                     (8)
#define SB4_MASK_status_id_mask                                                      (0x00003F00)
#define SB4_MASK_status_id(data)                                                     (0x00003F00&((data)<<8))
#define SB4_MASK_status_id_src(data)                                                 ((0x00003F00&(data))>>8)
#define SB4_MASK_mask_id_shift                                                       (0)
#define SB4_MASK_mask_id_mask                                                        (0x0000003F)
#define SB4_MASK_mask_id(data)                                                       (0x0000003F&((data)<<0))
#define SB4_MASK_mask_id_src(data)                                                   ((0x0000003F&(data))>>0)


#define SB4_PC_CTRL                                                                  0x1801C610
#define SB4_PC_CTRL_reg_addr                                                         "0xB801C610"
#define SB4_PC_CTRL_reg                                                              0xB801C610
#define SB4_PC_CTRL_inst_adr                                                         "0x0084"
#define SB4_PC_CTRL_inst                                                             0x0084
#define SB4_PC_CTRL_write_enable2_shift                                              (15)
#define SB4_PC_CTRL_write_enable2_mask                                               (0x00008000)
#define SB4_PC_CTRL_write_enable2(data)                                              (0x00008000&((data)<<15))
#define SB4_PC_CTRL_write_enable2_src(data)                                          ((0x00008000&(data))>>15)
#define SB4_PC_CTRL_pc2_go_shift                                                     (14)
#define SB4_PC_CTRL_pc2_go_mask                                                      (0x00004000)
#define SB4_PC_CTRL_pc2_go(data)                                                     (0x00004000&((data)<<14))
#define SB4_PC_CTRL_pc2_go_src(data)                                                 ((0x00004000&(data))>>14)
#define SB4_PC_CTRL_pc2_sel_shift                                                    (8)
#define SB4_PC_CTRL_pc2_sel_mask                                                     (0x00003F00)
#define SB4_PC_CTRL_pc2_sel(data)                                                    (0x00003F00&((data)<<8))
#define SB4_PC_CTRL_pc2_sel_src(data)                                                ((0x00003F00&(data))>>8)
#define SB4_PC_CTRL_write_enable1_shift                                              (7)
#define SB4_PC_CTRL_write_enable1_mask                                               (0x00000080)
#define SB4_PC_CTRL_write_enable1(data)                                              (0x00000080&((data)<<7))
#define SB4_PC_CTRL_write_enable1_src(data)                                          ((0x00000080&(data))>>7)
#define SB4_PC_CTRL_pc1_go_shift                                                     (6)
#define SB4_PC_CTRL_pc1_go_mask                                                      (0x00000040)
#define SB4_PC_CTRL_pc1_go(data)                                                     (0x00000040&((data)<<6))
#define SB4_PC_CTRL_pc1_go_src(data)                                                 ((0x00000040&(data))>>6)
#define SB4_PC_CTRL_pc1_sel_shift                                                    (0)
#define SB4_PC_CTRL_pc1_sel_mask                                                     (0x0000003F)
#define SB4_PC_CTRL_pc1_sel(data)                                                    (0x0000003F&((data)<<0))
#define SB4_PC_CTRL_pc1_sel_src(data)                                                ((0x0000003F&(data))>>0)


#define SB4_PC1_CYC                                                                  0x1801C614
#define SB4_PC1_CYC_reg_addr                                                         "0xB801C614"
#define SB4_PC1_CYC_reg                                                              0xB801C614
#define SB4_PC1_CYC_inst_adr                                                         "0x0085"
#define SB4_PC1_CYC_inst                                                             0x0085
#define SB4_PC1_CYC_tol_shift                                                        (0)
#define SB4_PC1_CYC_tol_mask                                                         (0xFFFFFFFF)
#define SB4_PC1_CYC_tol(data)                                                        (0xFFFFFFFF&((data)<<0))
#define SB4_PC1_CYC_tol_src(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define SB4_PC1_ACK                                                                  0x1801C618
#define SB4_PC1_ACK_reg_addr                                                         "0xB801C618"
#define SB4_PC1_ACK_reg                                                              0xB801C618
#define SB4_PC1_ACK_inst_adr                                                         "0x0086"
#define SB4_PC1_ACK_inst                                                             0x0086
#define SB4_PC1_ACK_tol_cyc_shift                                                    (0)
#define SB4_PC1_ACK_tol_cyc_mask                                                     (0xFFFFFFFF)
#define SB4_PC1_ACK_tol_cyc(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SB4_PC1_ACK_tol_cyc_src(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SB4_PC1_ACC                                                                  0x1801C61C
#define SB4_PC1_ACC_reg_addr                                                         "0xB801C61C"
#define SB4_PC1_ACC_reg                                                              0xB801C61C
#define SB4_PC1_ACC_inst_adr                                                         "0x0087"
#define SB4_PC1_ACC_inst                                                             0x0087
#define SB4_PC1_ACC_req_lat_shift                                                    (0)
#define SB4_PC1_ACC_req_lat_mask                                                     (0xFFFFFFFF)
#define SB4_PC1_ACC_req_lat(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SB4_PC1_ACC_req_lat_src(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SB4_PC1_REQ                                                                  0x1801C620
#define SB4_PC1_REQ_reg_addr                                                         "0xB801C620"
#define SB4_PC1_REQ_reg                                                              0xB801C620
#define SB4_PC1_REQ_inst_adr                                                         "0x0088"
#define SB4_PC1_REQ_inst                                                             0x0088
#define SB4_PC1_REQ_max_lat_shift                                                    (16)
#define SB4_PC1_REQ_max_lat_mask                                                     (0xFFFF0000)
#define SB4_PC1_REQ_max_lat(data)                                                    (0xFFFF0000&((data)<<16))
#define SB4_PC1_REQ_max_lat_src(data)                                                ((0xFFFF0000&(data))>>16)
#define SB4_PC1_REQ_tol_num_shift                                                    (0)
#define SB4_PC1_REQ_tol_num_mask                                                     (0x0000FFFF)
#define SB4_PC1_REQ_tol_num(data)                                                    (0x0000FFFF&((data)<<0))
#define SB4_PC1_REQ_tol_num_src(data)                                                ((0x0000FFFF&(data))>>0)


#define SB4_PC2_CYC                                                                  0x1801C624
#define SB4_PC2_CYC_reg_addr                                                         "0xB801C624"
#define SB4_PC2_CYC_reg                                                              0xB801C624
#define SB4_PC2_CYC_inst_adr                                                         "0x0089"
#define SB4_PC2_CYC_inst                                                             0x0089
#define SB4_PC2_CYC_tol_shift                                                        (0)
#define SB4_PC2_CYC_tol_mask                                                         (0xFFFFFFFF)
#define SB4_PC2_CYC_tol(data)                                                        (0xFFFFFFFF&((data)<<0))
#define SB4_PC2_CYC_tol_src(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define SB4_PC2_ACK                                                                  0x1801C628
#define SB4_PC2_ACK_reg_addr                                                         "0xB801C628"
#define SB4_PC2_ACK_reg                                                              0xB801C628
#define SB4_PC2_ACK_inst_adr                                                         "0x008A"
#define SB4_PC2_ACK_inst                                                             0x008A
#define SB4_PC2_ACK_tol_cyc_shift                                                    (0)
#define SB4_PC2_ACK_tol_cyc_mask                                                     (0xFFFFFFFF)
#define SB4_PC2_ACK_tol_cyc(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SB4_PC2_ACK_tol_cyc_src(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SB4_PC2_ACC                                                                  0x1801C62C
#define SB4_PC2_ACC_reg_addr                                                         "0xB801C62C"
#define SB4_PC2_ACC_reg                                                              0xB801C62C
#define SB4_PC2_ACC_inst_adr                                                         "0x008B"
#define SB4_PC2_ACC_inst                                                             0x008B
#define SB4_PC2_ACC_req_lat_shift                                                    (0)
#define SB4_PC2_ACC_req_lat_mask                                                     (0xFFFFFFFF)
#define SB4_PC2_ACC_req_lat(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SB4_PC2_ACC_req_lat_src(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SB4_PC2_REQ                                                                  0x1801C630
#define SB4_PC2_REQ_reg_addr                                                         "0xB801C630"
#define SB4_PC2_REQ_reg                                                              0xB801C630
#define SB4_PC2_REQ_inst_adr                                                         "0x008C"
#define SB4_PC2_REQ_inst                                                             0x008C
#define SB4_PC2_REQ_max_lat_shift                                                    (16)
#define SB4_PC2_REQ_max_lat_mask                                                     (0xFFFF0000)
#define SB4_PC2_REQ_max_lat(data)                                                    (0xFFFF0000&((data)<<16))
#define SB4_PC2_REQ_max_lat_src(data)                                                ((0xFFFF0000&(data))>>16)
#define SB4_PC2_REQ_tol_num_shift                                                    (0)
#define SB4_PC2_REQ_tol_num_mask                                                     (0x0000FFFF)
#define SB4_PC2_REQ_tol_num(data)                                                    (0x0000FFFF&((data)<<0))
#define SB4_PC2_REQ_tol_num_src(data)                                                ((0x0000FFFF&(data))>>0)


#define SB4_DBG                                                                      0x1801C634
#define SB4_DBG_reg_addr                                                             "0xB801C634"
#define SB4_DBG_reg                                                                  0xB801C634
#define SB4_DBG_inst_adr                                                             "0x008D"
#define SB4_DBG_inst                                                                 0x008D
#define SB4_DBG_write_enable3_shift                                                  (13)
#define SB4_DBG_write_enable3_mask                                                   (0x00002000)
#define SB4_DBG_write_enable3(data)                                                  (0x00002000&((data)<<13))
#define SB4_DBG_write_enable3_src(data)                                              ((0x00002000&(data))>>13)
#define SB4_DBG_sel1_shift                                                           (8)
#define SB4_DBG_sel1_mask                                                            (0x00001F00)
#define SB4_DBG_sel1(data)                                                           (0x00001F00&((data)<<8))
#define SB4_DBG_sel1_src(data)                                                       ((0x00001F00&(data))>>8)
#define SB4_DBG_write_enable2_shift                                                  (7)
#define SB4_DBG_write_enable2_mask                                                   (0x00000080)
#define SB4_DBG_write_enable2(data)                                                  (0x00000080&((data)<<7))
#define SB4_DBG_write_enable2_src(data)                                              ((0x00000080&(data))>>7)
#define SB4_DBG_sel0_shift                                                           (2)
#define SB4_DBG_sel0_mask                                                            (0x0000007C)
#define SB4_DBG_sel0(data)                                                           (0x0000007C&((data)<<2))
#define SB4_DBG_sel0_src(data)                                                       ((0x0000007C&(data))>>2)
#define SB4_DBG_write_enable1_shift                                                  (1)
#define SB4_DBG_write_enable1_mask                                                   (0x00000002)
#define SB4_DBG_write_enable1(data)                                                  (0x00000002&((data)<<1))
#define SB4_DBG_write_enable1_src(data)                                              ((0x00000002&(data))>>1)
#define SB4_DBG_enable_shift                                                         (0)
#define SB4_DBG_enable_mask                                                          (0x00000001)
#define SB4_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define SB4_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)


#endif
