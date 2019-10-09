/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : DVR_Parser_6.8(110516)
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2011/12/14 10:3:38
***************************************************************/


#ifndef _CAM_EMM_REG_H_INCLUDED_
#define _CAM_EMM_REG_H_INCLUDED_
#ifdef  _CAM_EMM_USE_STRUCT
typedef struct 
{
unsigned int     msb_03:8;
unsigned int     msb_02:8;
unsigned int     lsb_01:8;
unsigned int     lsb_00:8;
}CAM_EMM_TID_MODE;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID1;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID2;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID3;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID1;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID2;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID3;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     emm_en:1;
unsigned int     tid_en:1;
unsigned int     reserved_1:1;
unsigned int     pid:13;
}CAM_EMM_PID;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tid_msb:4;
unsigned int     dmy:4;
}CAM_EMM_TID;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     emm:8;
}CAM_EMM_CA_INT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     int_sts:8;
}CAM_EMM_INT_STAT;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID4;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID5;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID6;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID7;

typedef struct 
{
unsigned int     data:32;
}CAM_EMM_DATA_ID8;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID4;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID5;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID6;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID7;

typedef struct 
{
unsigned int     mask:32;
}CAM_EMM_MASK_ID8;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     num_lbl:16;
}CAM_EMM_CTRL_ID;

typedef struct 
{
unsigned int     pkt_data:32;
}CAM_EMM_EMM_BUF;

#endif

#define CAM_EMM_TID_MODE                                                             0x18011000
#define CAM_EMM_TID_MODE_reg_addr                                                    "0xB8011000"
#define CAM_EMM_TID_MODE_reg                                                         0xB8011000
#define set_CAM_EMM_TID_MODE_reg(data)   (*((volatile unsigned int*) CAM_EMM_TID_MODE_reg)=data)
#define get_CAM_EMM_TID_MODE_reg   (*((volatile unsigned int*) CAM_EMM_TID_MODE_reg))
#define CAM_EMM_TID_MODE_inst_adr                                                    "0x0000"
#define CAM_EMM_TID_MODE_inst                                                        0x0000
#define CAM_EMM_TID_MODE_msb_03_shift                                                (24)
#define CAM_EMM_TID_MODE_msb_03_mask                                                 (0xFF000000)
#define CAM_EMM_TID_MODE_msb_03(data)                                                (0xFF000000&((data)<<24))
#define CAM_EMM_TID_MODE_msb_03_src(data)                                            ((0xFF000000&(data))>>24)
#define CAM_EMM_TID_MODE_get_msb_03(data)                                            ((0xFF000000&(data))>>24)
#define CAM_EMM_TID_MODE_msb_02_shift                                                (16)
#define CAM_EMM_TID_MODE_msb_02_mask                                                 (0x00FF0000)
#define CAM_EMM_TID_MODE_msb_02(data)                                                (0x00FF0000&((data)<<16))
#define CAM_EMM_TID_MODE_msb_02_src(data)                                            ((0x00FF0000&(data))>>16)
#define CAM_EMM_TID_MODE_get_msb_02(data)                                            ((0x00FF0000&(data))>>16)
#define CAM_EMM_TID_MODE_lsb_01_shift                                                (8)
#define CAM_EMM_TID_MODE_lsb_01_mask                                                 (0x0000FF00)
#define CAM_EMM_TID_MODE_lsb_01(data)                                                (0x0000FF00&((data)<<8))
#define CAM_EMM_TID_MODE_lsb_01_src(data)                                            ((0x0000FF00&(data))>>8)
#define CAM_EMM_TID_MODE_get_lsb_01(data)                                            ((0x0000FF00&(data))>>8)
#define CAM_EMM_TID_MODE_lsb_00_shift                                                (0)
#define CAM_EMM_TID_MODE_lsb_00_mask                                                 (0x000000FF)
#define CAM_EMM_TID_MODE_lsb_00(data)                                                (0x000000FF&((data)<<0))
#define CAM_EMM_TID_MODE_lsb_00_src(data)                                            ((0x000000FF&(data))>>0)
#define CAM_EMM_TID_MODE_get_lsb_00(data)                                            ((0x000000FF&(data))>>0)


#define CAM_EMM_DATA_ID1                                                             0x18011004
#define CAM_EMM_DATA_ID1_reg_addr                                                    "0xB8011004"
#define CAM_EMM_DATA_ID1_reg                                                         0xB8011004
#define set_CAM_EMM_DATA_ID1_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID1_reg)=data)
#define get_CAM_EMM_DATA_ID1_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID1_reg))
#define CAM_EMM_DATA_ID1_inst_adr                                                    "0x0001"
#define CAM_EMM_DATA_ID1_inst                                                        0x0001
#define CAM_EMM_DATA_ID1_data_shift                                                  (0)
#define CAM_EMM_DATA_ID1_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID1_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID1_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID1_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID2                                                             0x18011008
#define CAM_EMM_DATA_ID2_reg_addr                                                    "0xB8011008"
#define CAM_EMM_DATA_ID2_reg                                                         0xB8011008
#define set_CAM_EMM_DATA_ID2_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID2_reg)=data)
#define get_CAM_EMM_DATA_ID2_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID2_reg))
#define CAM_EMM_DATA_ID2_inst_adr                                                    "0x0002"
#define CAM_EMM_DATA_ID2_inst                                                        0x0002
#define CAM_EMM_DATA_ID2_data_shift                                                  (0)
#define CAM_EMM_DATA_ID2_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID2_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID2_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID2_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID3                                                             0x1801100C
#define CAM_EMM_DATA_ID3_reg_addr                                                    "0xB801100C"
#define CAM_EMM_DATA_ID3_reg                                                         0xB801100C
#define set_CAM_EMM_DATA_ID3_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID3_reg)=data)
#define get_CAM_EMM_DATA_ID3_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID3_reg))
#define CAM_EMM_DATA_ID3_inst_adr                                                    "0x0003"
#define CAM_EMM_DATA_ID3_inst                                                        0x0003
#define CAM_EMM_DATA_ID3_data_shift                                                  (0)
#define CAM_EMM_DATA_ID3_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID3_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID3_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID3_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID1                                                             0x18011014
#define CAM_EMM_MASK_ID1_reg_addr                                                    "0xB8011014"
#define CAM_EMM_MASK_ID1_reg                                                         0xB8011014
#define set_CAM_EMM_MASK_ID1_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID1_reg)=data)
#define get_CAM_EMM_MASK_ID1_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID1_reg))
#define CAM_EMM_MASK_ID1_inst_adr                                                    "0x0005"
#define CAM_EMM_MASK_ID1_inst                                                        0x0005
#define CAM_EMM_MASK_ID1_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID1_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID1_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID1_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID1_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID2                                                             0x18011018
#define CAM_EMM_MASK_ID2_reg_addr                                                    "0xB8011018"
#define CAM_EMM_MASK_ID2_reg                                                         0xB8011018
#define set_CAM_EMM_MASK_ID2_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID2_reg)=data)
#define get_CAM_EMM_MASK_ID2_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID2_reg))
#define CAM_EMM_MASK_ID2_inst_adr                                                    "0x0006"
#define CAM_EMM_MASK_ID2_inst                                                        0x0006
#define CAM_EMM_MASK_ID2_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID2_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID2_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID2_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID2_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID3                                                             0x1801101C
#define CAM_EMM_MASK_ID3_reg_addr                                                    "0xB801101C"
#define CAM_EMM_MASK_ID3_reg                                                         0xB801101C
#define set_CAM_EMM_MASK_ID3_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID3_reg)=data)
#define get_CAM_EMM_MASK_ID3_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID3_reg))
#define CAM_EMM_MASK_ID3_inst_adr                                                    "0x0007"
#define CAM_EMM_MASK_ID3_inst                                                        0x0007
#define CAM_EMM_MASK_ID3_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID3_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID3_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID3_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID3_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_PID                                                                  0x18011020
#define CAM_EMM_PID_reg_addr                                                         "0xB8011020"
#define CAM_EMM_PID_reg                                                              0xB8011020
#define set_CAM_EMM_PID_reg(data)   (*((volatile unsigned int*) CAM_EMM_PID_reg)=data)
#define get_CAM_EMM_PID_reg   (*((volatile unsigned int*) CAM_EMM_PID_reg))
#define CAM_EMM_PID_inst_adr                                                         "0x0008"
#define CAM_EMM_PID_inst                                                             0x0008
#define CAM_EMM_PID_emm_en_shift                                                     (15)
#define CAM_EMM_PID_emm_en_mask                                                      (0x00008000)
#define CAM_EMM_PID_emm_en(data)                                                     (0x00008000&((data)<<15))
#define CAM_EMM_PID_emm_en_src(data)                                                 ((0x00008000&(data))>>15)
#define CAM_EMM_PID_get_emm_en(data)                                                 ((0x00008000&(data))>>15)
#define CAM_EMM_PID_tid_en_shift                                                     (14)
#define CAM_EMM_PID_tid_en_mask                                                      (0x00004000)
#define CAM_EMM_PID_tid_en(data)                                                     (0x00004000&((data)<<14))
#define CAM_EMM_PID_tid_en_src(data)                                                 ((0x00004000&(data))>>14)
#define CAM_EMM_PID_get_tid_en(data)                                                 ((0x00004000&(data))>>14)
#define CAM_EMM_PID_pid_shift                                                        (0)
#define CAM_EMM_PID_pid_mask                                                         (0x00001FFF)
#define CAM_EMM_PID_pid(data)                                                        (0x00001FFF&((data)<<0))
#define CAM_EMM_PID_pid_src(data)                                                    ((0x00001FFF&(data))>>0)
#define CAM_EMM_PID_get_pid(data)                                                    ((0x00001FFF&(data))>>0)


#define CAM_EMM_TID                                                                  0x18011024
#define CAM_EMM_TID_reg_addr                                                         "0xB8011024"
#define CAM_EMM_TID_reg                                                              0xB8011024
#define set_CAM_EMM_TID_reg(data)   (*((volatile unsigned int*) CAM_EMM_TID_reg)=data)
#define get_CAM_EMM_TID_reg   (*((volatile unsigned int*) CAM_EMM_TID_reg))
#define CAM_EMM_TID_inst_adr                                                         "0x0009"
#define CAM_EMM_TID_inst                                                             0x0009
#define CAM_EMM_TID_tid_msb_shift                                                    (4)
#define CAM_EMM_TID_tid_msb_mask                                                     (0x000000F0)
#define CAM_EMM_TID_tid_msb(data)                                                    (0x000000F0&((data)<<4))
#define CAM_EMM_TID_tid_msb_src(data)                                                ((0x000000F0&(data))>>4)
#define CAM_EMM_TID_get_tid_msb(data)                                                ((0x000000F0&(data))>>4)
#define CAM_EMM_TID_dmy_shift                                                        (0)
#define CAM_EMM_TID_dmy_mask                                                         (0x0000000F)
#define CAM_EMM_TID_dmy(data)                                                        (0x0000000F&((data)<<0))
#define CAM_EMM_TID_dmy_src(data)                                                    ((0x0000000F&(data))>>0)
#define CAM_EMM_TID_get_dmy(data)                                                    ((0x0000000F&(data))>>0)


#define CAM_EMM_CA_INT                                                               0x18011030
#define CAM_EMM_CA_INT_reg_addr                                                      "0xB8011030"
#define CAM_EMM_CA_INT_reg                                                           0xB8011030
#define set_CAM_EMM_CA_INT_reg(data)   (*((volatile unsigned int*) CAM_EMM_CA_INT_reg)=data)
#define get_CAM_EMM_CA_INT_reg   (*((volatile unsigned int*) CAM_EMM_CA_INT_reg))
#define CAM_EMM_CA_INT_inst_adr                                                      "0x000C"
#define CAM_EMM_CA_INT_inst                                                          0x000C
#define CAM_EMM_CA_INT_emm_shift                                                     (0)
#define CAM_EMM_CA_INT_emm_mask                                                      (0x000000FF)
#define CAM_EMM_CA_INT_emm(data)                                                     (0x000000FF&((data)<<0))
#define CAM_EMM_CA_INT_emm_src(data)                                                 ((0x000000FF&(data))>>0)
#define CAM_EMM_CA_INT_get_emm(data)                                                 ((0x000000FF&(data))>>0)


#define CAM_EMM_INT_STAT                                                             0x18011034
#define CAM_EMM_INT_STAT_reg_addr                                                    "0xB8011034"
#define CAM_EMM_INT_STAT_reg                                                         0xB8011034
#define set_CAM_EMM_INT_STAT_reg(data)   (*((volatile unsigned int*) CAM_EMM_INT_STAT_reg)=data)
#define get_CAM_EMM_INT_STAT_reg   (*((volatile unsigned int*) CAM_EMM_INT_STAT_reg))
#define CAM_EMM_INT_STAT_inst_adr                                                    "0x000D"
#define CAM_EMM_INT_STAT_inst                                                        0x000D
#define CAM_EMM_INT_STAT_int_sts_shift                                               (0)
#define CAM_EMM_INT_STAT_int_sts_mask                                                (0x000000FF)
#define CAM_EMM_INT_STAT_int_sts(data)                                               (0x000000FF&((data)<<0))
#define CAM_EMM_INT_STAT_int_sts_src(data)                                           ((0x000000FF&(data))>>0)
#define CAM_EMM_INT_STAT_get_int_sts(data)                                           ((0x000000FF&(data))>>0)


#define CAM_EMM_DATA_ID4                                                             0x18011070
#define CAM_EMM_DATA_ID4_reg_addr                                                    "0xB8011070"
#define CAM_EMM_DATA_ID4_reg                                                         0xB8011070
#define set_CAM_EMM_DATA_ID4_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID4_reg)=data)
#define get_CAM_EMM_DATA_ID4_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID4_reg))
#define CAM_EMM_DATA_ID4_inst_adr                                                    "0x001C"
#define CAM_EMM_DATA_ID4_inst                                                        0x001C
#define CAM_EMM_DATA_ID4_data_shift                                                  (0)
#define CAM_EMM_DATA_ID4_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID4_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID4_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID4_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID5                                                             0x18011074
#define CAM_EMM_DATA_ID5_reg_addr                                                    "0xB8011074"
#define CAM_EMM_DATA_ID5_reg                                                         0xB8011074
#define set_CAM_EMM_DATA_ID5_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID5_reg)=data)
#define get_CAM_EMM_DATA_ID5_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID5_reg))
#define CAM_EMM_DATA_ID5_inst_adr                                                    "0x001D"
#define CAM_EMM_DATA_ID5_inst                                                        0x001D
#define CAM_EMM_DATA_ID5_data_shift                                                  (0)
#define CAM_EMM_DATA_ID5_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID5_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID5_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID5_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID6                                                             0x18011078
#define CAM_EMM_DATA_ID6_reg_addr                                                    "0xB8011078"
#define CAM_EMM_DATA_ID6_reg                                                         0xB8011078
#define set_CAM_EMM_DATA_ID6_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID6_reg)=data)
#define get_CAM_EMM_DATA_ID6_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID6_reg))
#define CAM_EMM_DATA_ID6_inst_adr                                                    "0x001E"
#define CAM_EMM_DATA_ID6_inst                                                        0x001E
#define CAM_EMM_DATA_ID6_data_shift                                                  (0)
#define CAM_EMM_DATA_ID6_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID6_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID6_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID6_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID7                                                             0x1801107C
#define CAM_EMM_DATA_ID7_reg_addr                                                    "0xB801107C"
#define CAM_EMM_DATA_ID7_reg                                                         0xB801107C
#define set_CAM_EMM_DATA_ID7_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID7_reg)=data)
#define get_CAM_EMM_DATA_ID7_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID7_reg))
#define CAM_EMM_DATA_ID7_inst_adr                                                    "0x001F"
#define CAM_EMM_DATA_ID7_inst                                                        0x001F
#define CAM_EMM_DATA_ID7_data_shift                                                  (0)
#define CAM_EMM_DATA_ID7_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID7_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID7_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID7_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_DATA_ID8                                                             0x18011080
#define CAM_EMM_DATA_ID8_reg_addr                                                    "0xB8011080"
#define CAM_EMM_DATA_ID8_reg                                                         0xB8011080
#define set_CAM_EMM_DATA_ID8_reg(data)   (*((volatile unsigned int*) CAM_EMM_DATA_ID8_reg)=data)
#define get_CAM_EMM_DATA_ID8_reg   (*((volatile unsigned int*) CAM_EMM_DATA_ID8_reg))
#define CAM_EMM_DATA_ID8_inst_adr                                                    "0x0020"
#define CAM_EMM_DATA_ID8_inst                                                        0x0020
#define CAM_EMM_DATA_ID8_data_shift                                                  (0)
#define CAM_EMM_DATA_ID8_data_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_DATA_ID8_data(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_DATA_ID8_data_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_DATA_ID8_get_data(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID4                                                             0x18011084
#define CAM_EMM_MASK_ID4_reg_addr                                                    "0xB8011084"
#define CAM_EMM_MASK_ID4_reg                                                         0xB8011084
#define set_CAM_EMM_MASK_ID4_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID4_reg)=data)
#define get_CAM_EMM_MASK_ID4_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID4_reg))
#define CAM_EMM_MASK_ID4_inst_adr                                                    "0x0021"
#define CAM_EMM_MASK_ID4_inst                                                        0x0021
#define CAM_EMM_MASK_ID4_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID4_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID4_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID4_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID4_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID5                                                             0x18011088
#define CAM_EMM_MASK_ID5_reg_addr                                                    "0xB8011088"
#define CAM_EMM_MASK_ID5_reg                                                         0xB8011088
#define set_CAM_EMM_MASK_ID5_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID5_reg)=data)
#define get_CAM_EMM_MASK_ID5_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID5_reg))
#define CAM_EMM_MASK_ID5_inst_adr                                                    "0x0022"
#define CAM_EMM_MASK_ID5_inst                                                        0x0022
#define CAM_EMM_MASK_ID5_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID5_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID5_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID5_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID5_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID6                                                             0x1801108C
#define CAM_EMM_MASK_ID6_reg_addr                                                    "0xB801108C"
#define CAM_EMM_MASK_ID6_reg                                                         0xB801108C
#define set_CAM_EMM_MASK_ID6_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID6_reg)=data)
#define get_CAM_EMM_MASK_ID6_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID6_reg))
#define CAM_EMM_MASK_ID6_inst_adr                                                    "0x0023"
#define CAM_EMM_MASK_ID6_inst                                                        0x0023
#define CAM_EMM_MASK_ID6_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID6_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID6_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID6_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID6_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID7                                                             0x18011090
#define CAM_EMM_MASK_ID7_reg_addr                                                    "0xB8011090"
#define CAM_EMM_MASK_ID7_reg                                                         0xB8011090
#define set_CAM_EMM_MASK_ID7_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID7_reg)=data)
#define get_CAM_EMM_MASK_ID7_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID7_reg))
#define CAM_EMM_MASK_ID7_inst_adr                                                    "0x0024"
#define CAM_EMM_MASK_ID7_inst                                                        0x0024
#define CAM_EMM_MASK_ID7_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID7_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID7_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID7_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID7_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_MASK_ID8                                                             0x18011094
#define CAM_EMM_MASK_ID8_reg_addr                                                    "0xB8011094"
#define CAM_EMM_MASK_ID8_reg                                                         0xB8011094
#define set_CAM_EMM_MASK_ID8_reg(data)   (*((volatile unsigned int*) CAM_EMM_MASK_ID8_reg)=data)
#define get_CAM_EMM_MASK_ID8_reg   (*((volatile unsigned int*) CAM_EMM_MASK_ID8_reg))
#define CAM_EMM_MASK_ID8_inst_adr                                                    "0x0025"
#define CAM_EMM_MASK_ID8_inst                                                        0x0025
#define CAM_EMM_MASK_ID8_mask_shift                                                  (0)
#define CAM_EMM_MASK_ID8_mask_mask                                                   (0xFFFFFFFF)
#define CAM_EMM_MASK_ID8_mask(data)                                                  (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_MASK_ID8_mask_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_MASK_ID8_get_mask(data)                                              ((0xFFFFFFFF&(data))>>0)


#define CAM_EMM_CTRL_ID                                                              0x18011098
#define CAM_EMM_CTRL_ID_reg_addr                                                     "0xB8011098"
#define CAM_EMM_CTRL_ID_reg                                                          0xB8011098
#define set_CAM_EMM_CTRL_ID_reg(data)   (*((volatile unsigned int*) CAM_EMM_CTRL_ID_reg)=data)
#define get_CAM_EMM_CTRL_ID_reg   (*((volatile unsigned int*) CAM_EMM_CTRL_ID_reg))
#define CAM_EMM_CTRL_ID_inst_adr                                                     "0x0026"
#define CAM_EMM_CTRL_ID_inst                                                         0x0026
#define CAM_EMM_CTRL_ID_num_lbl_shift                                                (0)
#define CAM_EMM_CTRL_ID_num_lbl_mask                                                 (0x0000FFFF)
#define CAM_EMM_CTRL_ID_num_lbl(data)                                                (0x0000FFFF&((data)<<0))
#define CAM_EMM_CTRL_ID_num_lbl_src(data)                                            ((0x0000FFFF&(data))>>0)
#define CAM_EMM_CTRL_ID_get_num_lbl(data)                                            ((0x0000FFFF&(data))>>0)


#define CAM_EMM_EMM_BUF_0                                                            0x18011600
#define CAM_EMM_EMM_BUF_1                                                            0x18011604
#define CAM_EMM_EMM_BUF_2                                                            0x18011608
#define CAM_EMM_EMM_BUF_3                                                            0x1801160C
#define CAM_EMM_EMM_BUF_4                                                            0x18011610
#define CAM_EMM_EMM_BUF_5                                                            0x18011614
#define CAM_EMM_EMM_BUF_6                                                            0x18011618
#define CAM_EMM_EMM_BUF_7                                                            0x1801161C
#define CAM_EMM_EMM_BUF_8                                                            0x18011620
#define CAM_EMM_EMM_BUF_9                                                            0x18011624
#define CAM_EMM_EMM_BUF_10                                                            0x18011628
#define CAM_EMM_EMM_BUF_11                                                            0x1801162C
#define CAM_EMM_EMM_BUF_12                                                            0x18011630
#define CAM_EMM_EMM_BUF_13                                                            0x18011634
#define CAM_EMM_EMM_BUF_14                                                            0x18011638
#define CAM_EMM_EMM_BUF_15                                                            0x1801163C
#define CAM_EMM_EMM_BUF_16                                                            0x18011640
#define CAM_EMM_EMM_BUF_17                                                            0x18011644
#define CAM_EMM_EMM_BUF_18                                                            0x18011648
#define CAM_EMM_EMM_BUF_19                                                            0x1801164C
#define CAM_EMM_EMM_BUF_20                                                            0x18011650
#define CAM_EMM_EMM_BUF_21                                                            0x18011654
#define CAM_EMM_EMM_BUF_22                                                            0x18011658
#define CAM_EMM_EMM_BUF_23                                                            0x1801165C
#define CAM_EMM_EMM_BUF_24                                                            0x18011660
#define CAM_EMM_EMM_BUF_25                                                            0x18011664
#define CAM_EMM_EMM_BUF_26                                                            0x18011668
#define CAM_EMM_EMM_BUF_27                                                            0x1801166C
#define CAM_EMM_EMM_BUF_28                                                            0x18011670
#define CAM_EMM_EMM_BUF_29                                                            0x18011674
#define CAM_EMM_EMM_BUF_30                                                            0x18011678
#define CAM_EMM_EMM_BUF_31                                                            0x1801167C
#define CAM_EMM_EMM_BUF_32                                                            0x18011680
#define CAM_EMM_EMM_BUF_33                                                            0x18011684
#define CAM_EMM_EMM_BUF_34                                                            0x18011688
#define CAM_EMM_EMM_BUF_35                                                            0x1801168C
#define CAM_EMM_EMM_BUF_36                                                            0x18011690
#define CAM_EMM_EMM_BUF_37                                                            0x18011694
#define CAM_EMM_EMM_BUF_38                                                            0x18011698
#define CAM_EMM_EMM_BUF_39                                                            0x1801169C
#define CAM_EMM_EMM_BUF_40                                                            0x180116A0
#define CAM_EMM_EMM_BUF_41                                                            0x180116A4
#define CAM_EMM_EMM_BUF_42                                                            0x180116A8
#define CAM_EMM_EMM_BUF_43                                                            0x180116AC
#define CAM_EMM_EMM_BUF_44                                                            0x180116B0
#define CAM_EMM_EMM_BUF_45                                                            0x180116B4
#define CAM_EMM_EMM_BUF_46                                                            0x180116B8
#define CAM_EMM_EMM_BUF_47                                                            0x180116BC
#define CAM_EMM_EMM_BUF_48                                                            0x180116C0
#define CAM_EMM_EMM_BUF_49                                                            0x180116C4
#define CAM_EMM_EMM_BUF_50                                                            0x180116C8
#define CAM_EMM_EMM_BUF_51                                                            0x180116CC
#define CAM_EMM_EMM_BUF_52                                                            0x180116D0
#define CAM_EMM_EMM_BUF_53                                                            0x180116D4
#define CAM_EMM_EMM_BUF_54                                                            0x180116D8
#define CAM_EMM_EMM_BUF_55                                                            0x180116DC
#define CAM_EMM_EMM_BUF_56                                                            0x180116E0
#define CAM_EMM_EMM_BUF_57                                                            0x180116E4
#define CAM_EMM_EMM_BUF_58                                                            0x180116E8
#define CAM_EMM_EMM_BUF_59                                                            0x180116EC
#define CAM_EMM_EMM_BUF_60                                                            0x180116F0
#define CAM_EMM_EMM_BUF_61                                                            0x180116F4
#define CAM_EMM_EMM_BUF_62                                                            0x180116F8
#define CAM_EMM_EMM_BUF_63                                                            0x180116FC
#define CAM_EMM_EMM_BUF_64                                                            0x18011700
#define CAM_EMM_EMM_BUF_65                                                            0x18011704
#define CAM_EMM_EMM_BUF_66                                                            0x18011708
#define CAM_EMM_EMM_BUF_67                                                            0x1801170C
#define CAM_EMM_EMM_BUF_68                                                            0x18011710
#define CAM_EMM_EMM_BUF_69                                                            0x18011714
#define CAM_EMM_EMM_BUF_70                                                            0x18011718
#define CAM_EMM_EMM_BUF_71                                                            0x1801171C
#define CAM_EMM_EMM_BUF_72                                                            0x18011720
#define CAM_EMM_EMM_BUF_73                                                            0x18011724
#define CAM_EMM_EMM_BUF_74                                                            0x18011728
#define CAM_EMM_EMM_BUF_75                                                            0x1801172C
#define CAM_EMM_EMM_BUF_76                                                            0x18011730
#define CAM_EMM_EMM_BUF_77                                                            0x18011734
#define CAM_EMM_EMM_BUF_78                                                            0x18011738
#define CAM_EMM_EMM_BUF_79                                                            0x1801173C
#define CAM_EMM_EMM_BUF_80                                                            0x18011740
#define CAM_EMM_EMM_BUF_81                                                            0x18011744
#define CAM_EMM_EMM_BUF_82                                                            0x18011748
#define CAM_EMM_EMM_BUF_83                                                            0x1801174C
#define CAM_EMM_EMM_BUF_84                                                            0x18011750
#define CAM_EMM_EMM_BUF_85                                                            0x18011754
#define CAM_EMM_EMM_BUF_86                                                            0x18011758
#define CAM_EMM_EMM_BUF_87                                                            0x1801175C
#define CAM_EMM_EMM_BUF_88                                                            0x18011760
#define CAM_EMM_EMM_BUF_89                                                            0x18011764
#define CAM_EMM_EMM_BUF_90                                                            0x18011768
#define CAM_EMM_EMM_BUF_91                                                            0x1801176C
#define CAM_EMM_EMM_BUF_92                                                            0x18011770
#define CAM_EMM_EMM_BUF_93                                                            0x18011774
#define CAM_EMM_EMM_BUF_94                                                            0x18011778
#define CAM_EMM_EMM_BUF_95                                                            0x1801177C
#define CAM_EMM_EMM_BUF_96                                                            0x18011780
#define CAM_EMM_EMM_BUF_97                                                            0x18011784
#define CAM_EMM_EMM_BUF_98                                                            0x18011788
#define CAM_EMM_EMM_BUF_99                                                            0x1801178C
#define CAM_EMM_EMM_BUF_100                                                            0x18011790
#define CAM_EMM_EMM_BUF_101                                                            0x18011794
#define CAM_EMM_EMM_BUF_102                                                            0x18011798
#define CAM_EMM_EMM_BUF_103                                                            0x1801179C
#define CAM_EMM_EMM_BUF_104                                                            0x180117A0
#define CAM_EMM_EMM_BUF_105                                                            0x180117A4
#define CAM_EMM_EMM_BUF_106                                                            0x180117A8
#define CAM_EMM_EMM_BUF_107                                                            0x180117AC
#define CAM_EMM_EMM_BUF_108                                                            0x180117B0
#define CAM_EMM_EMM_BUF_109                                                            0x180117B4
#define CAM_EMM_EMM_BUF_110                                                            0x180117B8
#define CAM_EMM_EMM_BUF_111                                                            0x180117BC
#define CAM_EMM_EMM_BUF_112                                                            0x180117C0
#define CAM_EMM_EMM_BUF_113                                                            0x180117C4
#define CAM_EMM_EMM_BUF_114                                                            0x180117C8
#define CAM_EMM_EMM_BUF_115                                                            0x180117CC
#define CAM_EMM_EMM_BUF_116                                                            0x180117D0
#define CAM_EMM_EMM_BUF_117                                                            0x180117D4
#define CAM_EMM_EMM_BUF_118                                                            0x180117D8
#define CAM_EMM_EMM_BUF_119                                                            0x180117DC
#define CAM_EMM_EMM_BUF_120                                                            0x180117E0
#define CAM_EMM_EMM_BUF_121                                                            0x180117E4
#define CAM_EMM_EMM_BUF_122                                                            0x180117E8
#define CAM_EMM_EMM_BUF_123                                                            0x180117EC
#define CAM_EMM_EMM_BUF_124                                                            0x180117F0
#define CAM_EMM_EMM_BUF_125                                                            0x180117F4
#define CAM_EMM_EMM_BUF_126                                                            0x180117F8
#define CAM_EMM_EMM_BUF_127                                                            0x180117FC
#define CAM_EMM_EMM_BUF_128                                                            0x18011800
#define CAM_EMM_EMM_BUF_129                                                            0x18011804
#define CAM_EMM_EMM_BUF_130                                                            0x18011808
#define CAM_EMM_EMM_BUF_131                                                            0x1801180C
#define CAM_EMM_EMM_BUF_132                                                            0x18011810
#define CAM_EMM_EMM_BUF_133                                                            0x18011814
#define CAM_EMM_EMM_BUF_134                                                            0x18011818
#define CAM_EMM_EMM_BUF_135                                                            0x1801181C
#define CAM_EMM_EMM_BUF_136                                                            0x18011820
#define CAM_EMM_EMM_BUF_137                                                            0x18011824
#define CAM_EMM_EMM_BUF_138                                                            0x18011828
#define CAM_EMM_EMM_BUF_139                                                            0x1801182C
#define CAM_EMM_EMM_BUF_140                                                            0x18011830
#define CAM_EMM_EMM_BUF_141                                                            0x18011834
#define CAM_EMM_EMM_BUF_142                                                            0x18011838
#define CAM_EMM_EMM_BUF_143                                                            0x1801183C
#define CAM_EMM_EMM_BUF_144                                                            0x18011840
#define CAM_EMM_EMM_BUF_145                                                            0x18011844
#define CAM_EMM_EMM_BUF_146                                                            0x18011848
#define CAM_EMM_EMM_BUF_147                                                            0x1801184C
#define CAM_EMM_EMM_BUF_148                                                            0x18011850
#define CAM_EMM_EMM_BUF_149                                                            0x18011854
#define CAM_EMM_EMM_BUF_150                                                            0x18011858
#define CAM_EMM_EMM_BUF_151                                                            0x1801185C
#define CAM_EMM_EMM_BUF_152                                                            0x18011860
#define CAM_EMM_EMM_BUF_153                                                            0x18011864
#define CAM_EMM_EMM_BUF_154                                                            0x18011868
#define CAM_EMM_EMM_BUF_155                                                            0x1801186C
#define CAM_EMM_EMM_BUF_156                                                            0x18011870
#define CAM_EMM_EMM_BUF_157                                                            0x18011874
#define CAM_EMM_EMM_BUF_158                                                            0x18011878
#define CAM_EMM_EMM_BUF_159                                                            0x1801187C
#define CAM_EMM_EMM_BUF_160                                                            0x18011880
#define CAM_EMM_EMM_BUF_161                                                            0x18011884
#define CAM_EMM_EMM_BUF_162                                                            0x18011888
#define CAM_EMM_EMM_BUF_163                                                            0x1801188C
#define CAM_EMM_EMM_BUF_164                                                            0x18011890
#define CAM_EMM_EMM_BUF_165                                                            0x18011894
#define CAM_EMM_EMM_BUF_166                                                            0x18011898
#define CAM_EMM_EMM_BUF_167                                                            0x1801189C
#define CAM_EMM_EMM_BUF_168                                                            0x180118A0
#define CAM_EMM_EMM_BUF_169                                                            0x180118A4
#define CAM_EMM_EMM_BUF_170                                                            0x180118A8
#define CAM_EMM_EMM_BUF_171                                                            0x180118AC
#define CAM_EMM_EMM_BUF_172                                                            0x180118B0
#define CAM_EMM_EMM_BUF_173                                                            0x180118B4
#define CAM_EMM_EMM_BUF_174                                                            0x180118B8
#define CAM_EMM_EMM_BUF_175                                                            0x180118BC
#define CAM_EMM_EMM_BUF_176                                                            0x180118C0
#define CAM_EMM_EMM_BUF_177                                                            0x180118C4
#define CAM_EMM_EMM_BUF_178                                                            0x180118C8
#define CAM_EMM_EMM_BUF_179                                                            0x180118CC
#define CAM_EMM_EMM_BUF_180                                                            0x180118D0
#define CAM_EMM_EMM_BUF_181                                                            0x180118D4
#define CAM_EMM_EMM_BUF_182                                                            0x180118D8
#define CAM_EMM_EMM_BUF_183                                                            0x180118DC
#define CAM_EMM_EMM_BUF_184                                                            0x180118E0
#define CAM_EMM_EMM_BUF_185                                                            0x180118E4
#define CAM_EMM_EMM_BUF_186                                                            0x180118E8
#define CAM_EMM_EMM_BUF_187                                                            0x180118EC
#define CAM_EMM_EMM_BUF_188                                                            0x180118F0
#define CAM_EMM_EMM_BUF_189                                                            0x180118F4
#define CAM_EMM_EMM_BUF_190                                                            0x180118F8
#define CAM_EMM_EMM_BUF_191                                                            0x180118FC
#define CAM_EMM_EMM_BUF_192                                                            0x18011900
#define CAM_EMM_EMM_BUF_193                                                            0x18011904
#define CAM_EMM_EMM_BUF_194                                                            0x18011908
#define CAM_EMM_EMM_BUF_195                                                            0x1801190C
#define CAM_EMM_EMM_BUF_196                                                            0x18011910
#define CAM_EMM_EMM_BUF_197                                                            0x18011914
#define CAM_EMM_EMM_BUF_198                                                            0x18011918
#define CAM_EMM_EMM_BUF_199                                                            0x1801191C
#define CAM_EMM_EMM_BUF_200                                                            0x18011920
#define CAM_EMM_EMM_BUF_201                                                            0x18011924
#define CAM_EMM_EMM_BUF_202                                                            0x18011928
#define CAM_EMM_EMM_BUF_203                                                            0x1801192C
#define CAM_EMM_EMM_BUF_204                                                            0x18011930
#define CAM_EMM_EMM_BUF_205                                                            0x18011934
#define CAM_EMM_EMM_BUF_206                                                            0x18011938
#define CAM_EMM_EMM_BUF_207                                                            0x1801193C
#define CAM_EMM_EMM_BUF_208                                                            0x18011940
#define CAM_EMM_EMM_BUF_209                                                            0x18011944
#define CAM_EMM_EMM_BUF_210                                                            0x18011948
#define CAM_EMM_EMM_BUF_211                                                            0x1801194C
#define CAM_EMM_EMM_BUF_212                                                            0x18011950
#define CAM_EMM_EMM_BUF_213                                                            0x18011954
#define CAM_EMM_EMM_BUF_214                                                            0x18011958
#define CAM_EMM_EMM_BUF_215                                                            0x1801195C
#define CAM_EMM_EMM_BUF_216                                                            0x18011960
#define CAM_EMM_EMM_BUF_217                                                            0x18011964
#define CAM_EMM_EMM_BUF_218                                                            0x18011968
#define CAM_EMM_EMM_BUF_219                                                            0x1801196C
#define CAM_EMM_EMM_BUF_220                                                            0x18011970
#define CAM_EMM_EMM_BUF_221                                                            0x18011974
#define CAM_EMM_EMM_BUF_222                                                            0x18011978
#define CAM_EMM_EMM_BUF_223                                                            0x1801197C
#define CAM_EMM_EMM_BUF_224                                                            0x18011980
#define CAM_EMM_EMM_BUF_225                                                            0x18011984
#define CAM_EMM_EMM_BUF_226                                                            0x18011988
#define CAM_EMM_EMM_BUF_227                                                            0x1801198C
#define CAM_EMM_EMM_BUF_228                                                            0x18011990
#define CAM_EMM_EMM_BUF_229                                                            0x18011994
#define CAM_EMM_EMM_BUF_230                                                            0x18011998
#define CAM_EMM_EMM_BUF_231                                                            0x1801199C
#define CAM_EMM_EMM_BUF_232                                                            0x180119A0
#define CAM_EMM_EMM_BUF_233                                                            0x180119A4
#define CAM_EMM_EMM_BUF_234                                                            0x180119A8
#define CAM_EMM_EMM_BUF_235                                                            0x180119AC
#define CAM_EMM_EMM_BUF_236                                                            0x180119B0
#define CAM_EMM_EMM_BUF_237                                                            0x180119B4
#define CAM_EMM_EMM_BUF_238                                                            0x180119B8
#define CAM_EMM_EMM_BUF_239                                                            0x180119BC
#define CAM_EMM_EMM_BUF_240                                                            0x180119C0
#define CAM_EMM_EMM_BUF_241                                                            0x180119C4
#define CAM_EMM_EMM_BUF_242                                                            0x180119C8
#define CAM_EMM_EMM_BUF_243                                                            0x180119CC
#define CAM_EMM_EMM_BUF_244                                                            0x180119D0
#define CAM_EMM_EMM_BUF_245                                                            0x180119D4
#define CAM_EMM_EMM_BUF_246                                                            0x180119D8
#define CAM_EMM_EMM_BUF_247                                                            0x180119DC
#define CAM_EMM_EMM_BUF_248                                                            0x180119E0
#define CAM_EMM_EMM_BUF_249                                                            0x180119E4
#define CAM_EMM_EMM_BUF_250                                                            0x180119E8
#define CAM_EMM_EMM_BUF_251                                                            0x180119EC
#define CAM_EMM_EMM_BUF_252                                                            0x180119F0
#define CAM_EMM_EMM_BUF_253                                                            0x180119F4
#define CAM_EMM_EMM_BUF_254                                                            0x180119F8
#define CAM_EMM_EMM_BUF_255                                                            0x180119FC
#define CAM_EMM_EMM_BUF_256                                                            0x18011A00
#define CAM_EMM_EMM_BUF_257                                                            0x18011A04
#define CAM_EMM_EMM_BUF_258                                                            0x18011A08
#define CAM_EMM_EMM_BUF_259                                                            0x18011A0C
#define CAM_EMM_EMM_BUF_260                                                            0x18011A10
#define CAM_EMM_EMM_BUF_261                                                            0x18011A14
#define CAM_EMM_EMM_BUF_262                                                            0x18011A18
#define CAM_EMM_EMM_BUF_263                                                            0x18011A1C
#define CAM_EMM_EMM_BUF_264                                                            0x18011A20
#define CAM_EMM_EMM_BUF_265                                                            0x18011A24
#define CAM_EMM_EMM_BUF_266                                                            0x18011A28
#define CAM_EMM_EMM_BUF_267                                                            0x18011A2C
#define CAM_EMM_EMM_BUF_268                                                            0x18011A30
#define CAM_EMM_EMM_BUF_269                                                            0x18011A34
#define CAM_EMM_EMM_BUF_270                                                            0x18011A38
#define CAM_EMM_EMM_BUF_271                                                            0x18011A3C
#define CAM_EMM_EMM_BUF_272                                                            0x18011A40
#define CAM_EMM_EMM_BUF_273                                                            0x18011A44
#define CAM_EMM_EMM_BUF_274                                                            0x18011A48
#define CAM_EMM_EMM_BUF_275                                                            0x18011A4C
#define CAM_EMM_EMM_BUF_276                                                            0x18011A50
#define CAM_EMM_EMM_BUF_277                                                            0x18011A54
#define CAM_EMM_EMM_BUF_278                                                            0x18011A58
#define CAM_EMM_EMM_BUF_279                                                            0x18011A5C
#define CAM_EMM_EMM_BUF_280                                                            0x18011A60
#define CAM_EMM_EMM_BUF_281                                                            0x18011A64
#define CAM_EMM_EMM_BUF_282                                                            0x18011A68
#define CAM_EMM_EMM_BUF_283                                                            0x18011A6C
#define CAM_EMM_EMM_BUF_284                                                            0x18011A70
#define CAM_EMM_EMM_BUF_285                                                            0x18011A74
#define CAM_EMM_EMM_BUF_286                                                            0x18011A78
#define CAM_EMM_EMM_BUF_287                                                            0x18011A7C
#define CAM_EMM_EMM_BUF_288                                                            0x18011A80
#define CAM_EMM_EMM_BUF_289                                                            0x18011A84
#define CAM_EMM_EMM_BUF_290                                                            0x18011A88
#define CAM_EMM_EMM_BUF_291                                                            0x18011A8C
#define CAM_EMM_EMM_BUF_292                                                            0x18011A90
#define CAM_EMM_EMM_BUF_293                                                            0x18011A94
#define CAM_EMM_EMM_BUF_294                                                            0x18011A98
#define CAM_EMM_EMM_BUF_295                                                            0x18011A9C
#define CAM_EMM_EMM_BUF_296                                                            0x18011AA0
#define CAM_EMM_EMM_BUF_297                                                            0x18011AA4
#define CAM_EMM_EMM_BUF_298                                                            0x18011AA8
#define CAM_EMM_EMM_BUF_299                                                            0x18011AAC
#define CAM_EMM_EMM_BUF_300                                                            0x18011AB0
#define CAM_EMM_EMM_BUF_301                                                            0x18011AB4
#define CAM_EMM_EMM_BUF_302                                                            0x18011AB8
#define CAM_EMM_EMM_BUF_303                                                            0x18011ABC
#define CAM_EMM_EMM_BUF_304                                                            0x18011AC0
#define CAM_EMM_EMM_BUF_305                                                            0x18011AC4
#define CAM_EMM_EMM_BUF_306                                                            0x18011AC8
#define CAM_EMM_EMM_BUF_307                                                            0x18011ACC
#define CAM_EMM_EMM_BUF_308                                                            0x18011AD0
#define CAM_EMM_EMM_BUF_309                                                            0x18011AD4
#define CAM_EMM_EMM_BUF_310                                                            0x18011AD8
#define CAM_EMM_EMM_BUF_311                                                            0x18011ADC
#define CAM_EMM_EMM_BUF_312                                                            0x18011AE0
#define CAM_EMM_EMM_BUF_313                                                            0x18011AE4
#define CAM_EMM_EMM_BUF_314                                                            0x18011AE8
#define CAM_EMM_EMM_BUF_315                                                            0x18011AEC
#define CAM_EMM_EMM_BUF_316                                                            0x18011AF0
#define CAM_EMM_EMM_BUF_317                                                            0x18011AF4
#define CAM_EMM_EMM_BUF_318                                                            0x18011AF8
#define CAM_EMM_EMM_BUF_319                                                            0x18011AFC
#define CAM_EMM_EMM_BUF_320                                                            0x18011B00
#define CAM_EMM_EMM_BUF_321                                                            0x18011B04
#define CAM_EMM_EMM_BUF_322                                                            0x18011B08
#define CAM_EMM_EMM_BUF_323                                                            0x18011B0C
#define CAM_EMM_EMM_BUF_324                                                            0x18011B10
#define CAM_EMM_EMM_BUF_325                                                            0x18011B14
#define CAM_EMM_EMM_BUF_326                                                            0x18011B18
#define CAM_EMM_EMM_BUF_327                                                            0x18011B1C
#define CAM_EMM_EMM_BUF_328                                                            0x18011B20
#define CAM_EMM_EMM_BUF_329                                                            0x18011B24
#define CAM_EMM_EMM_BUF_330                                                            0x18011B28
#define CAM_EMM_EMM_BUF_331                                                            0x18011B2C
#define CAM_EMM_EMM_BUF_332                                                            0x18011B30
#define CAM_EMM_EMM_BUF_333                                                            0x18011B34
#define CAM_EMM_EMM_BUF_334                                                            0x18011B38
#define CAM_EMM_EMM_BUF_335                                                            0x18011B3C
#define CAM_EMM_EMM_BUF_336                                                            0x18011B40
#define CAM_EMM_EMM_BUF_337                                                            0x18011B44
#define CAM_EMM_EMM_BUF_338                                                            0x18011B48
#define CAM_EMM_EMM_BUF_339                                                            0x18011B4C
#define CAM_EMM_EMM_BUF_340                                                            0x18011B50
#define CAM_EMM_EMM_BUF_341                                                            0x18011B54
#define CAM_EMM_EMM_BUF_342                                                            0x18011B58
#define CAM_EMM_EMM_BUF_343                                                            0x18011B5C
#define CAM_EMM_EMM_BUF_344                                                            0x18011B60
#define CAM_EMM_EMM_BUF_345                                                            0x18011B64
#define CAM_EMM_EMM_BUF_346                                                            0x18011B68
#define CAM_EMM_EMM_BUF_347                                                            0x18011B6C
#define CAM_EMM_EMM_BUF_348                                                            0x18011B70
#define CAM_EMM_EMM_BUF_349                                                            0x18011B74
#define CAM_EMM_EMM_BUF_350                                                            0x18011B78
#define CAM_EMM_EMM_BUF_351                                                            0x18011B7C
#define CAM_EMM_EMM_BUF_352                                                            0x18011B80
#define CAM_EMM_EMM_BUF_353                                                            0x18011B84
#define CAM_EMM_EMM_BUF_354                                                            0x18011B88
#define CAM_EMM_EMM_BUF_355                                                            0x18011B8C
#define CAM_EMM_EMM_BUF_356                                                            0x18011B90
#define CAM_EMM_EMM_BUF_357                                                            0x18011B94
#define CAM_EMM_EMM_BUF_358                                                            0x18011B98
#define CAM_EMM_EMM_BUF_359                                                            0x18011B9C
#define CAM_EMM_EMM_BUF_360                                                            0x18011BA0
#define CAM_EMM_EMM_BUF_361                                                            0x18011BA4
#define CAM_EMM_EMM_BUF_362                                                            0x18011BA8
#define CAM_EMM_EMM_BUF_363                                                            0x18011BAC
#define CAM_EMM_EMM_BUF_364                                                            0x18011BB0
#define CAM_EMM_EMM_BUF_365                                                            0x18011BB4
#define CAM_EMM_EMM_BUF_366                                                            0x18011BB8
#define CAM_EMM_EMM_BUF_367                                                            0x18011BBC
#define CAM_EMM_EMM_BUF_368                                                            0x18011BC0
#define CAM_EMM_EMM_BUF_369                                                            0x18011BC4
#define CAM_EMM_EMM_BUF_370                                                            0x18011BC8
#define CAM_EMM_EMM_BUF_371                                                            0x18011BCC
#define CAM_EMM_EMM_BUF_372                                                            0x18011BD0
#define CAM_EMM_EMM_BUF_373                                                            0x18011BD4
#define CAM_EMM_EMM_BUF_374                                                            0x18011BD8
#define CAM_EMM_EMM_BUF_375                                                            0x18011BDC
#define CAM_EMM_EMM_BUF_376                                                            0x18011BE0
#define CAM_EMM_EMM_BUF_377                                                            0x18011BE4
#define CAM_EMM_EMM_BUF_378                                                            0x18011BE8
#define CAM_EMM_EMM_BUF_379                                                            0x18011BEC
#define CAM_EMM_EMM_BUF_380                                                            0x18011BF0
#define CAM_EMM_EMM_BUF_381                                                            0x18011BF4
#define CAM_EMM_EMM_BUF_382                                                            0x18011BF8
#define CAM_EMM_EMM_BUF_383                                                            0x18011BFC
#define CAM_EMM_EMM_BUF_384                                                            0x18011C00
#define CAM_EMM_EMM_BUF_385                                                            0x18011C04
#define CAM_EMM_EMM_BUF_386                                                            0x18011C08
#define CAM_EMM_EMM_BUF_387                                                            0x18011C0C
#define CAM_EMM_EMM_BUF_388                                                            0x18011C10
#define CAM_EMM_EMM_BUF_389                                                            0x18011C14
#define CAM_EMM_EMM_BUF_390                                                            0x18011C18
#define CAM_EMM_EMM_BUF_391                                                            0x18011C1C
#define CAM_EMM_EMM_BUF_392                                                            0x18011C20
#define CAM_EMM_EMM_BUF_393                                                            0x18011C24
#define CAM_EMM_EMM_BUF_394                                                            0x18011C28
#define CAM_EMM_EMM_BUF_395                                                            0x18011C2C
#define CAM_EMM_EMM_BUF_396                                                            0x18011C30
#define CAM_EMM_EMM_BUF_397                                                            0x18011C34
#define CAM_EMM_EMM_BUF_398                                                            0x18011C38
#define CAM_EMM_EMM_BUF_399                                                            0x18011C3C
#define CAM_EMM_EMM_BUF_400                                                            0x18011C40
#define CAM_EMM_EMM_BUF_401                                                            0x18011C44
#define CAM_EMM_EMM_BUF_402                                                            0x18011C48
#define CAM_EMM_EMM_BUF_403                                                            0x18011C4C
#define CAM_EMM_EMM_BUF_404                                                            0x18011C50
#define CAM_EMM_EMM_BUF_405                                                            0x18011C54
#define CAM_EMM_EMM_BUF_406                                                            0x18011C58
#define CAM_EMM_EMM_BUF_407                                                            0x18011C5C
#define CAM_EMM_EMM_BUF_408                                                            0x18011C60
#define CAM_EMM_EMM_BUF_409                                                            0x18011C64
#define CAM_EMM_EMM_BUF_410                                                            0x18011C68
#define CAM_EMM_EMM_BUF_411                                                            0x18011C6C
#define CAM_EMM_EMM_BUF_412                                                            0x18011C70
#define CAM_EMM_EMM_BUF_413                                                            0x18011C74
#define CAM_EMM_EMM_BUF_414                                                            0x18011C78
#define CAM_EMM_EMM_BUF_415                                                            0x18011C7C
#define CAM_EMM_EMM_BUF_416                                                            0x18011C80
#define CAM_EMM_EMM_BUF_417                                                            0x18011C84
#define CAM_EMM_EMM_BUF_418                                                            0x18011C88
#define CAM_EMM_EMM_BUF_419                                                            0x18011C8C
#define CAM_EMM_EMM_BUF_420                                                            0x18011C90
#define CAM_EMM_EMM_BUF_421                                                            0x18011C94
#define CAM_EMM_EMM_BUF_422                                                            0x18011C98
#define CAM_EMM_EMM_BUF_423                                                            0x18011C9C
#define CAM_EMM_EMM_BUF_424                                                            0x18011CA0
#define CAM_EMM_EMM_BUF_425                                                            0x18011CA4
#define CAM_EMM_EMM_BUF_426                                                            0x18011CA8
#define CAM_EMM_EMM_BUF_427                                                            0x18011CAC
#define CAM_EMM_EMM_BUF_428                                                            0x18011CB0
#define CAM_EMM_EMM_BUF_429                                                            0x18011CB4
#define CAM_EMM_EMM_BUF_430                                                            0x18011CB8
#define CAM_EMM_EMM_BUF_431                                                            0x18011CBC
#define CAM_EMM_EMM_BUF_432                                                            0x18011CC0
#define CAM_EMM_EMM_BUF_433                                                            0x18011CC4
#define CAM_EMM_EMM_BUF_434                                                            0x18011CC8
#define CAM_EMM_EMM_BUF_435                                                            0x18011CCC
#define CAM_EMM_EMM_BUF_436                                                            0x18011CD0
#define CAM_EMM_EMM_BUF_437                                                            0x18011CD4
#define CAM_EMM_EMM_BUF_438                                                            0x18011CD8
#define CAM_EMM_EMM_BUF_439                                                            0x18011CDC
#define CAM_EMM_EMM_BUF_440                                                            0x18011CE0
#define CAM_EMM_EMM_BUF_441                                                            0x18011CE4
#define CAM_EMM_EMM_BUF_442                                                            0x18011CE8
#define CAM_EMM_EMM_BUF_443                                                            0x18011CEC
#define CAM_EMM_EMM_BUF_444                                                            0x18011CF0
#define CAM_EMM_EMM_BUF_445                                                            0x18011CF4
#define CAM_EMM_EMM_BUF_446                                                            0x18011CF8
#define CAM_EMM_EMM_BUF_447                                                            0x18011CFC
#define CAM_EMM_EMM_BUF_448                                                            0x18011D00
#define CAM_EMM_EMM_BUF_449                                                            0x18011D04
#define CAM_EMM_EMM_BUF_450                                                            0x18011D08
#define CAM_EMM_EMM_BUF_451                                                            0x18011D0C
#define CAM_EMM_EMM_BUF_452                                                            0x18011D10
#define CAM_EMM_EMM_BUF_453                                                            0x18011D14
#define CAM_EMM_EMM_BUF_454                                                            0x18011D18
#define CAM_EMM_EMM_BUF_455                                                            0x18011D1C
#define CAM_EMM_EMM_BUF_456                                                            0x18011D20
#define CAM_EMM_EMM_BUF_457                                                            0x18011D24
#define CAM_EMM_EMM_BUF_458                                                            0x18011D28
#define CAM_EMM_EMM_BUF_459                                                            0x18011D2C
#define CAM_EMM_EMM_BUF_460                                                            0x18011D30
#define CAM_EMM_EMM_BUF_461                                                            0x18011D34
#define CAM_EMM_EMM_BUF_462                                                            0x18011D38
#define CAM_EMM_EMM_BUF_463                                                            0x18011D3C
#define CAM_EMM_EMM_BUF_464                                                            0x18011D40
#define CAM_EMM_EMM_BUF_465                                                            0x18011D44
#define CAM_EMM_EMM_BUF_466                                                            0x18011D48
#define CAM_EMM_EMM_BUF_467                                                            0x18011D4C
#define CAM_EMM_EMM_BUF_468                                                            0x18011D50
#define CAM_EMM_EMM_BUF_469                                                            0x18011D54
#define CAM_EMM_EMM_BUF_470                                                            0x18011D58
#define CAM_EMM_EMM_BUF_471                                                            0x18011D5C
#define CAM_EMM_EMM_BUF_472                                                            0x18011D60
#define CAM_EMM_EMM_BUF_473                                                            0x18011D64
#define CAM_EMM_EMM_BUF_474                                                            0x18011D68
#define CAM_EMM_EMM_BUF_475                                                            0x18011D6C
#define CAM_EMM_EMM_BUF_476                                                            0x18011D70
#define CAM_EMM_EMM_BUF_477                                                            0x18011D74
#define CAM_EMM_EMM_BUF_478                                                            0x18011D78
#define CAM_EMM_EMM_BUF_479                                                            0x18011D7C
#define CAM_EMM_EMM_BUF_480                                                            0x18011D80
#define CAM_EMM_EMM_BUF_481                                                            0x18011D84
#define CAM_EMM_EMM_BUF_482                                                            0x18011D88
#define CAM_EMM_EMM_BUF_483                                                            0x18011D8C
#define CAM_EMM_EMM_BUF_484                                                            0x18011D90
#define CAM_EMM_EMM_BUF_485                                                            0x18011D94
#define CAM_EMM_EMM_BUF_486                                                            0x18011D98
#define CAM_EMM_EMM_BUF_487                                                            0x18011D9C
#define CAM_EMM_EMM_BUF_488                                                            0x18011DA0
#define CAM_EMM_EMM_BUF_489                                                            0x18011DA4
#define CAM_EMM_EMM_BUF_490                                                            0x18011DA8
#define CAM_EMM_EMM_BUF_491                                                            0x18011DAC
#define CAM_EMM_EMM_BUF_492                                                            0x18011DB0
#define CAM_EMM_EMM_BUF_493                                                            0x18011DB4
#define CAM_EMM_EMM_BUF_494                                                            0x18011DB8
#define CAM_EMM_EMM_BUF_495                                                            0x18011DBC
#define CAM_EMM_EMM_BUF_496                                                            0x18011DC0
#define CAM_EMM_EMM_BUF_497                                                            0x18011DC4
#define CAM_EMM_EMM_BUF_498                                                            0x18011DC8
#define CAM_EMM_EMM_BUF_499                                                            0x18011DCC
#define CAM_EMM_EMM_BUF_500                                                            0x18011DD0
#define CAM_EMM_EMM_BUF_501                                                            0x18011DD4
#define CAM_EMM_EMM_BUF_502                                                            0x18011DD8
#define CAM_EMM_EMM_BUF_503                                                            0x18011DDC
#define CAM_EMM_EMM_BUF_504                                                            0x18011DE0
#define CAM_EMM_EMM_BUF_505                                                            0x18011DE4
#define CAM_EMM_EMM_BUF_506                                                            0x18011DE8
#define CAM_EMM_EMM_BUF_507                                                            0x18011DEC
#define CAM_EMM_EMM_BUF_508                                                            0x18011DF0
#define CAM_EMM_EMM_BUF_509                                                            0x18011DF4
#define CAM_EMM_EMM_BUF_510                                                            0x18011DF8
#define CAM_EMM_EMM_BUF_511                                                            0x18011DFC
#define CAM_EMM_EMM_BUF_512                                                            0x18011E00
#define CAM_EMM_EMM_BUF_513                                                            0x18011E04
#define CAM_EMM_EMM_BUF_514                                                            0x18011E08
#define CAM_EMM_EMM_BUF_515                                                            0x18011E0C
#define CAM_EMM_EMM_BUF_516                                                            0x18011E10
#define CAM_EMM_EMM_BUF_517                                                            0x18011E14
#define CAM_EMM_EMM_BUF_518                                                            0x18011E18
#define CAM_EMM_EMM_BUF_519                                                            0x18011E1C
#define CAM_EMM_EMM_BUF_520                                                            0x18011E20
#define CAM_EMM_EMM_BUF_521                                                            0x18011E24
#define CAM_EMM_EMM_BUF_522                                                            0x18011E28
#define CAM_EMM_EMM_BUF_523                                                            0x18011E2C
#define CAM_EMM_EMM_BUF_524                                                            0x18011E30
#define CAM_EMM_EMM_BUF_525                                                            0x18011E34
#define CAM_EMM_EMM_BUF_526                                                            0x18011E38
#define CAM_EMM_EMM_BUF_527                                                            0x18011E3C
#define CAM_EMM_EMM_BUF_528                                                            0x18011E40
#define CAM_EMM_EMM_BUF_529                                                            0x18011E44
#define CAM_EMM_EMM_BUF_530                                                            0x18011E48
#define CAM_EMM_EMM_BUF_531                                                            0x18011E4C
#define CAM_EMM_EMM_BUF_532                                                            0x18011E50
#define CAM_EMM_EMM_BUF_533                                                            0x18011E54
#define CAM_EMM_EMM_BUF_534                                                            0x18011E58
#define CAM_EMM_EMM_BUF_535                                                            0x18011E5C
#define CAM_EMM_EMM_BUF_536                                                            0x18011E60
#define CAM_EMM_EMM_BUF_537                                                            0x18011E64
#define CAM_EMM_EMM_BUF_538                                                            0x18011E68
#define CAM_EMM_EMM_BUF_539                                                            0x18011E6C
#define CAM_EMM_EMM_BUF_540                                                            0x18011E70
#define CAM_EMM_EMM_BUF_541                                                            0x18011E74
#define CAM_EMM_EMM_BUF_542                                                            0x18011E78
#define CAM_EMM_EMM_BUF_543                                                            0x18011E7C
#define CAM_EMM_EMM_BUF_544                                                            0x18011E80
#define CAM_EMM_EMM_BUF_545                                                            0x18011E84
#define CAM_EMM_EMM_BUF_546                                                            0x18011E88
#define CAM_EMM_EMM_BUF_547                                                            0x18011E8C
#define CAM_EMM_EMM_BUF_548                                                            0x18011E90
#define CAM_EMM_EMM_BUF_549                                                            0x18011E94
#define CAM_EMM_EMM_BUF_550                                                            0x18011E98
#define CAM_EMM_EMM_BUF_551                                                            0x18011E9C
#define CAM_EMM_EMM_BUF_552                                                            0x18011EA0
#define CAM_EMM_EMM_BUF_553                                                            0x18011EA4
#define CAM_EMM_EMM_BUF_554                                                            0x18011EA8
#define CAM_EMM_EMM_BUF_555                                                            0x18011EAC
#define CAM_EMM_EMM_BUF_556                                                            0x18011EB0
#define CAM_EMM_EMM_BUF_557                                                            0x18011EB4
#define CAM_EMM_EMM_BUF_558                                                            0x18011EB8
#define CAM_EMM_EMM_BUF_559                                                            0x18011EBC
#define CAM_EMM_EMM_BUF_560                                                            0x18011EC0
#define CAM_EMM_EMM_BUF_561                                                            0x18011EC4
#define CAM_EMM_EMM_BUF_562                                                            0x18011EC8
#define CAM_EMM_EMM_BUF_563                                                            0x18011ECC
#define CAM_EMM_EMM_BUF_564                                                            0x18011ED0
#define CAM_EMM_EMM_BUF_565                                                            0x18011ED4
#define CAM_EMM_EMM_BUF_566                                                            0x18011ED8
#define CAM_EMM_EMM_BUF_567                                                            0x18011EDC
#define CAM_EMM_EMM_BUF_568                                                            0x18011EE0
#define CAM_EMM_EMM_BUF_569                                                            0x18011EE4
#define CAM_EMM_EMM_BUF_570                                                            0x18011EE8
#define CAM_EMM_EMM_BUF_571                                                            0x18011EEC
#define CAM_EMM_EMM_BUF_572                                                            0x18011EF0
#define CAM_EMM_EMM_BUF_573                                                            0x18011EF4
#define CAM_EMM_EMM_BUF_574                                                            0x18011EF8
#define CAM_EMM_EMM_BUF_575                                                            0x18011EFC
#define CAM_EMM_EMM_BUF_576                                                            0x18011F00
#define CAM_EMM_EMM_BUF_577                                                            0x18011F04
#define CAM_EMM_EMM_BUF_578                                                            0x18011F08
#define CAM_EMM_EMM_BUF_579                                                            0x18011F0C
#define CAM_EMM_EMM_BUF_580                                                            0x18011F10
#define CAM_EMM_EMM_BUF_581                                                            0x18011F14
#define CAM_EMM_EMM_BUF_582                                                            0x18011F18
#define CAM_EMM_EMM_BUF_583                                                            0x18011F1C
#define CAM_EMM_EMM_BUF_584                                                            0x18011F20
#define CAM_EMM_EMM_BUF_585                                                            0x18011F24
#define CAM_EMM_EMM_BUF_586                                                            0x18011F28
#define CAM_EMM_EMM_BUF_587                                                            0x18011F2C
#define CAM_EMM_EMM_BUF_588                                                            0x18011F30
#define CAM_EMM_EMM_BUF_589                                                            0x18011F34
#define CAM_EMM_EMM_BUF_590                                                            0x18011F38
#define CAM_EMM_EMM_BUF_591                                                            0x18011F3C
#define CAM_EMM_EMM_BUF_592                                                            0x18011F40
#define CAM_EMM_EMM_BUF_593                                                            0x18011F44
#define CAM_EMM_EMM_BUF_594                                                            0x18011F48
#define CAM_EMM_EMM_BUF_595                                                            0x18011F4C
#define CAM_EMM_EMM_BUF_596                                                            0x18011F50
#define CAM_EMM_EMM_BUF_597                                                            0x18011F54
#define CAM_EMM_EMM_BUF_598                                                            0x18011F58
#define CAM_EMM_EMM_BUF_599                                                            0x18011F5C
#define CAM_EMM_EMM_BUF_600                                                            0x18011F60
#define CAM_EMM_EMM_BUF_601                                                            0x18011F64
#define CAM_EMM_EMM_BUF_602                                                            0x18011F68
#define CAM_EMM_EMM_BUF_603                                                            0x18011F6C
#define CAM_EMM_EMM_BUF_604                                                            0x18011F70
#define CAM_EMM_EMM_BUF_605                                                            0x18011F74
#define CAM_EMM_EMM_BUF_606                                                            0x18011F78
#define CAM_EMM_EMM_BUF_607                                                            0x18011F7C
#define CAM_EMM_EMM_BUF_608                                                            0x18011F80
#define CAM_EMM_EMM_BUF_609                                                            0x18011F84
#define CAM_EMM_EMM_BUF_610                                                            0x18011F88
#define CAM_EMM_EMM_BUF_611                                                            0x18011F8C
#define CAM_EMM_EMM_BUF_612                                                            0x18011F90
#define CAM_EMM_EMM_BUF_613                                                            0x18011F94
#define CAM_EMM_EMM_BUF_614                                                            0x18011F98
#define CAM_EMM_EMM_BUF_615                                                            0x18011F9C
#define CAM_EMM_EMM_BUF_616                                                            0x18011FA0
#define CAM_EMM_EMM_BUF_617                                                            0x18011FA4
#define CAM_EMM_EMM_BUF_618                                                            0x18011FA8
#define CAM_EMM_EMM_BUF_619                                                            0x18011FAC
#define CAM_EMM_EMM_BUF_620                                                            0x18011FB0
#define CAM_EMM_EMM_BUF_621                                                            0x18011FB4
#define CAM_EMM_EMM_BUF_622                                                            0x18011FB8
#define CAM_EMM_EMM_BUF_623                                                            0x18011FBC
#define CAM_EMM_EMM_BUF_624                                                            0x18011FC0
#define CAM_EMM_EMM_BUF_625                                                            0x18011FC4
#define CAM_EMM_EMM_BUF_626                                                            0x18011FC8
#define CAM_EMM_EMM_BUF_627                                                            0x18011FCC
#define CAM_EMM_EMM_BUF_628                                                            0x18011FD0
#define CAM_EMM_EMM_BUF_629                                                            0x18011FD4
#define CAM_EMM_EMM_BUF_630                                                            0x18011FD8
#define CAM_EMM_EMM_BUF_631                                                            0x18011FDC
#define CAM_EMM_EMM_BUF_632                                                            0x18011FE0
#define CAM_EMM_EMM_BUF_633                                                            0x18011FE4
#define CAM_EMM_EMM_BUF_634                                                            0x18011FE8
#define CAM_EMM_EMM_BUF_635                                                            0x18011FEC
#define CAM_EMM_EMM_BUF_636                                                            0x18011FF0
#define CAM_EMM_EMM_BUF_637                                                            0x18011FF4
#define CAM_EMM_EMM_BUF_638                                                            0x18011FF8
#define CAM_EMM_EMM_BUF_639                                                            0x18011FFC
#define CAM_EMM_EMM_BUF_0_reg_addr                                                   "0xB8011600"
#define CAM_EMM_EMM_BUF_1_reg_addr                                                   "0xB8011604"
#define CAM_EMM_EMM_BUF_2_reg_addr                                                   "0xB8011608"
#define CAM_EMM_EMM_BUF_3_reg_addr                                                   "0xB801160C"
#define CAM_EMM_EMM_BUF_4_reg_addr                                                   "0xB8011610"
#define CAM_EMM_EMM_BUF_5_reg_addr                                                   "0xB8011614"
#define CAM_EMM_EMM_BUF_6_reg_addr                                                   "0xB8011618"
#define CAM_EMM_EMM_BUF_7_reg_addr                                                   "0xB801161C"
#define CAM_EMM_EMM_BUF_8_reg_addr                                                   "0xB8011620"
#define CAM_EMM_EMM_BUF_9_reg_addr                                                   "0xB8011624"
#define CAM_EMM_EMM_BUF_10_reg_addr                                                   "0xB8011628"
#define CAM_EMM_EMM_BUF_11_reg_addr                                                   "0xB801162C"
#define CAM_EMM_EMM_BUF_12_reg_addr                                                   "0xB8011630"
#define CAM_EMM_EMM_BUF_13_reg_addr                                                   "0xB8011634"
#define CAM_EMM_EMM_BUF_14_reg_addr                                                   "0xB8011638"
#define CAM_EMM_EMM_BUF_15_reg_addr                                                   "0xB801163C"
#define CAM_EMM_EMM_BUF_16_reg_addr                                                   "0xB8011640"
#define CAM_EMM_EMM_BUF_17_reg_addr                                                   "0xB8011644"
#define CAM_EMM_EMM_BUF_18_reg_addr                                                   "0xB8011648"
#define CAM_EMM_EMM_BUF_19_reg_addr                                                   "0xB801164C"
#define CAM_EMM_EMM_BUF_20_reg_addr                                                   "0xB8011650"
#define CAM_EMM_EMM_BUF_21_reg_addr                                                   "0xB8011654"
#define CAM_EMM_EMM_BUF_22_reg_addr                                                   "0xB8011658"
#define CAM_EMM_EMM_BUF_23_reg_addr                                                   "0xB801165C"
#define CAM_EMM_EMM_BUF_24_reg_addr                                                   "0xB8011660"
#define CAM_EMM_EMM_BUF_25_reg_addr                                                   "0xB8011664"
#define CAM_EMM_EMM_BUF_26_reg_addr                                                   "0xB8011668"
#define CAM_EMM_EMM_BUF_27_reg_addr                                                   "0xB801166C"
#define CAM_EMM_EMM_BUF_28_reg_addr                                                   "0xB8011670"
#define CAM_EMM_EMM_BUF_29_reg_addr                                                   "0xB8011674"
#define CAM_EMM_EMM_BUF_30_reg_addr                                                   "0xB8011678"
#define CAM_EMM_EMM_BUF_31_reg_addr                                                   "0xB801167C"
#define CAM_EMM_EMM_BUF_32_reg_addr                                                   "0xB8011680"
#define CAM_EMM_EMM_BUF_33_reg_addr                                                   "0xB8011684"
#define CAM_EMM_EMM_BUF_34_reg_addr                                                   "0xB8011688"
#define CAM_EMM_EMM_BUF_35_reg_addr                                                   "0xB801168C"
#define CAM_EMM_EMM_BUF_36_reg_addr                                                   "0xB8011690"
#define CAM_EMM_EMM_BUF_37_reg_addr                                                   "0xB8011694"
#define CAM_EMM_EMM_BUF_38_reg_addr                                                   "0xB8011698"
#define CAM_EMM_EMM_BUF_39_reg_addr                                                   "0xB801169C"
#define CAM_EMM_EMM_BUF_40_reg_addr                                                   "0xB80116A0"
#define CAM_EMM_EMM_BUF_41_reg_addr                                                   "0xB80116A4"
#define CAM_EMM_EMM_BUF_42_reg_addr                                                   "0xB80116A8"
#define CAM_EMM_EMM_BUF_43_reg_addr                                                   "0xB80116AC"
#define CAM_EMM_EMM_BUF_44_reg_addr                                                   "0xB80116B0"
#define CAM_EMM_EMM_BUF_45_reg_addr                                                   "0xB80116B4"
#define CAM_EMM_EMM_BUF_46_reg_addr                                                   "0xB80116B8"
#define CAM_EMM_EMM_BUF_47_reg_addr                                                   "0xB80116BC"
#define CAM_EMM_EMM_BUF_48_reg_addr                                                   "0xB80116C0"
#define CAM_EMM_EMM_BUF_49_reg_addr                                                   "0xB80116C4"
#define CAM_EMM_EMM_BUF_50_reg_addr                                                   "0xB80116C8"
#define CAM_EMM_EMM_BUF_51_reg_addr                                                   "0xB80116CC"
#define CAM_EMM_EMM_BUF_52_reg_addr                                                   "0xB80116D0"
#define CAM_EMM_EMM_BUF_53_reg_addr                                                   "0xB80116D4"
#define CAM_EMM_EMM_BUF_54_reg_addr                                                   "0xB80116D8"
#define CAM_EMM_EMM_BUF_55_reg_addr                                                   "0xB80116DC"
#define CAM_EMM_EMM_BUF_56_reg_addr                                                   "0xB80116E0"
#define CAM_EMM_EMM_BUF_57_reg_addr                                                   "0xB80116E4"
#define CAM_EMM_EMM_BUF_58_reg_addr                                                   "0xB80116E8"
#define CAM_EMM_EMM_BUF_59_reg_addr                                                   "0xB80116EC"
#define CAM_EMM_EMM_BUF_60_reg_addr                                                   "0xB80116F0"
#define CAM_EMM_EMM_BUF_61_reg_addr                                                   "0xB80116F4"
#define CAM_EMM_EMM_BUF_62_reg_addr                                                   "0xB80116F8"
#define CAM_EMM_EMM_BUF_63_reg_addr                                                   "0xB80116FC"
#define CAM_EMM_EMM_BUF_64_reg_addr                                                   "0xB8011700"
#define CAM_EMM_EMM_BUF_65_reg_addr                                                   "0xB8011704"
#define CAM_EMM_EMM_BUF_66_reg_addr                                                   "0xB8011708"
#define CAM_EMM_EMM_BUF_67_reg_addr                                                   "0xB801170C"
#define CAM_EMM_EMM_BUF_68_reg_addr                                                   "0xB8011710"
#define CAM_EMM_EMM_BUF_69_reg_addr                                                   "0xB8011714"
#define CAM_EMM_EMM_BUF_70_reg_addr                                                   "0xB8011718"
#define CAM_EMM_EMM_BUF_71_reg_addr                                                   "0xB801171C"
#define CAM_EMM_EMM_BUF_72_reg_addr                                                   "0xB8011720"
#define CAM_EMM_EMM_BUF_73_reg_addr                                                   "0xB8011724"
#define CAM_EMM_EMM_BUF_74_reg_addr                                                   "0xB8011728"
#define CAM_EMM_EMM_BUF_75_reg_addr                                                   "0xB801172C"
#define CAM_EMM_EMM_BUF_76_reg_addr                                                   "0xB8011730"
#define CAM_EMM_EMM_BUF_77_reg_addr                                                   "0xB8011734"
#define CAM_EMM_EMM_BUF_78_reg_addr                                                   "0xB8011738"
#define CAM_EMM_EMM_BUF_79_reg_addr                                                   "0xB801173C"
#define CAM_EMM_EMM_BUF_80_reg_addr                                                   "0xB8011740"
#define CAM_EMM_EMM_BUF_81_reg_addr                                                   "0xB8011744"
#define CAM_EMM_EMM_BUF_82_reg_addr                                                   "0xB8011748"
#define CAM_EMM_EMM_BUF_83_reg_addr                                                   "0xB801174C"
#define CAM_EMM_EMM_BUF_84_reg_addr                                                   "0xB8011750"
#define CAM_EMM_EMM_BUF_85_reg_addr                                                   "0xB8011754"
#define CAM_EMM_EMM_BUF_86_reg_addr                                                   "0xB8011758"
#define CAM_EMM_EMM_BUF_87_reg_addr                                                   "0xB801175C"
#define CAM_EMM_EMM_BUF_88_reg_addr                                                   "0xB8011760"
#define CAM_EMM_EMM_BUF_89_reg_addr                                                   "0xB8011764"
#define CAM_EMM_EMM_BUF_90_reg_addr                                                   "0xB8011768"
#define CAM_EMM_EMM_BUF_91_reg_addr                                                   "0xB801176C"
#define CAM_EMM_EMM_BUF_92_reg_addr                                                   "0xB8011770"
#define CAM_EMM_EMM_BUF_93_reg_addr                                                   "0xB8011774"
#define CAM_EMM_EMM_BUF_94_reg_addr                                                   "0xB8011778"
#define CAM_EMM_EMM_BUF_95_reg_addr                                                   "0xB801177C"
#define CAM_EMM_EMM_BUF_96_reg_addr                                                   "0xB8011780"
#define CAM_EMM_EMM_BUF_97_reg_addr                                                   "0xB8011784"
#define CAM_EMM_EMM_BUF_98_reg_addr                                                   "0xB8011788"
#define CAM_EMM_EMM_BUF_99_reg_addr                                                   "0xB801178C"
#define CAM_EMM_EMM_BUF_100_reg_addr                                                   "0xB8011790"
#define CAM_EMM_EMM_BUF_101_reg_addr                                                   "0xB8011794"
#define CAM_EMM_EMM_BUF_102_reg_addr                                                   "0xB8011798"
#define CAM_EMM_EMM_BUF_103_reg_addr                                                   "0xB801179C"
#define CAM_EMM_EMM_BUF_104_reg_addr                                                   "0xB80117A0"
#define CAM_EMM_EMM_BUF_105_reg_addr                                                   "0xB80117A4"
#define CAM_EMM_EMM_BUF_106_reg_addr                                                   "0xB80117A8"
#define CAM_EMM_EMM_BUF_107_reg_addr                                                   "0xB80117AC"
#define CAM_EMM_EMM_BUF_108_reg_addr                                                   "0xB80117B0"
#define CAM_EMM_EMM_BUF_109_reg_addr                                                   "0xB80117B4"
#define CAM_EMM_EMM_BUF_110_reg_addr                                                   "0xB80117B8"
#define CAM_EMM_EMM_BUF_111_reg_addr                                                   "0xB80117BC"
#define CAM_EMM_EMM_BUF_112_reg_addr                                                   "0xB80117C0"
#define CAM_EMM_EMM_BUF_113_reg_addr                                                   "0xB80117C4"
#define CAM_EMM_EMM_BUF_114_reg_addr                                                   "0xB80117C8"
#define CAM_EMM_EMM_BUF_115_reg_addr                                                   "0xB80117CC"
#define CAM_EMM_EMM_BUF_116_reg_addr                                                   "0xB80117D0"
#define CAM_EMM_EMM_BUF_117_reg_addr                                                   "0xB80117D4"
#define CAM_EMM_EMM_BUF_118_reg_addr                                                   "0xB80117D8"
#define CAM_EMM_EMM_BUF_119_reg_addr                                                   "0xB80117DC"
#define CAM_EMM_EMM_BUF_120_reg_addr                                                   "0xB80117E0"
#define CAM_EMM_EMM_BUF_121_reg_addr                                                   "0xB80117E4"
#define CAM_EMM_EMM_BUF_122_reg_addr                                                   "0xB80117E8"
#define CAM_EMM_EMM_BUF_123_reg_addr                                                   "0xB80117EC"
#define CAM_EMM_EMM_BUF_124_reg_addr                                                   "0xB80117F0"
#define CAM_EMM_EMM_BUF_125_reg_addr                                                   "0xB80117F4"
#define CAM_EMM_EMM_BUF_126_reg_addr                                                   "0xB80117F8"
#define CAM_EMM_EMM_BUF_127_reg_addr                                                   "0xB80117FC"
#define CAM_EMM_EMM_BUF_128_reg_addr                                                   "0xB8011800"
#define CAM_EMM_EMM_BUF_129_reg_addr                                                   "0xB8011804"
#define CAM_EMM_EMM_BUF_130_reg_addr                                                   "0xB8011808"
#define CAM_EMM_EMM_BUF_131_reg_addr                                                   "0xB801180C"
#define CAM_EMM_EMM_BUF_132_reg_addr                                                   "0xB8011810"
#define CAM_EMM_EMM_BUF_133_reg_addr                                                   "0xB8011814"
#define CAM_EMM_EMM_BUF_134_reg_addr                                                   "0xB8011818"
#define CAM_EMM_EMM_BUF_135_reg_addr                                                   "0xB801181C"
#define CAM_EMM_EMM_BUF_136_reg_addr                                                   "0xB8011820"
#define CAM_EMM_EMM_BUF_137_reg_addr                                                   "0xB8011824"
#define CAM_EMM_EMM_BUF_138_reg_addr                                                   "0xB8011828"
#define CAM_EMM_EMM_BUF_139_reg_addr                                                   "0xB801182C"
#define CAM_EMM_EMM_BUF_140_reg_addr                                                   "0xB8011830"
#define CAM_EMM_EMM_BUF_141_reg_addr                                                   "0xB8011834"
#define CAM_EMM_EMM_BUF_142_reg_addr                                                   "0xB8011838"
#define CAM_EMM_EMM_BUF_143_reg_addr                                                   "0xB801183C"
#define CAM_EMM_EMM_BUF_144_reg_addr                                                   "0xB8011840"
#define CAM_EMM_EMM_BUF_145_reg_addr                                                   "0xB8011844"
#define CAM_EMM_EMM_BUF_146_reg_addr                                                   "0xB8011848"
#define CAM_EMM_EMM_BUF_147_reg_addr                                                   "0xB801184C"
#define CAM_EMM_EMM_BUF_148_reg_addr                                                   "0xB8011850"
#define CAM_EMM_EMM_BUF_149_reg_addr                                                   "0xB8011854"
#define CAM_EMM_EMM_BUF_150_reg_addr                                                   "0xB8011858"
#define CAM_EMM_EMM_BUF_151_reg_addr                                                   "0xB801185C"
#define CAM_EMM_EMM_BUF_152_reg_addr                                                   "0xB8011860"
#define CAM_EMM_EMM_BUF_153_reg_addr                                                   "0xB8011864"
#define CAM_EMM_EMM_BUF_154_reg_addr                                                   "0xB8011868"
#define CAM_EMM_EMM_BUF_155_reg_addr                                                   "0xB801186C"
#define CAM_EMM_EMM_BUF_156_reg_addr                                                   "0xB8011870"
#define CAM_EMM_EMM_BUF_157_reg_addr                                                   "0xB8011874"
#define CAM_EMM_EMM_BUF_158_reg_addr                                                   "0xB8011878"
#define CAM_EMM_EMM_BUF_159_reg_addr                                                   "0xB801187C"
#define CAM_EMM_EMM_BUF_160_reg_addr                                                   "0xB8011880"
#define CAM_EMM_EMM_BUF_161_reg_addr                                                   "0xB8011884"
#define CAM_EMM_EMM_BUF_162_reg_addr                                                   "0xB8011888"
#define CAM_EMM_EMM_BUF_163_reg_addr                                                   "0xB801188C"
#define CAM_EMM_EMM_BUF_164_reg_addr                                                   "0xB8011890"
#define CAM_EMM_EMM_BUF_165_reg_addr                                                   "0xB8011894"
#define CAM_EMM_EMM_BUF_166_reg_addr                                                   "0xB8011898"
#define CAM_EMM_EMM_BUF_167_reg_addr                                                   "0xB801189C"
#define CAM_EMM_EMM_BUF_168_reg_addr                                                   "0xB80118A0"
#define CAM_EMM_EMM_BUF_169_reg_addr                                                   "0xB80118A4"
#define CAM_EMM_EMM_BUF_170_reg_addr                                                   "0xB80118A8"
#define CAM_EMM_EMM_BUF_171_reg_addr                                                   "0xB80118AC"
#define CAM_EMM_EMM_BUF_172_reg_addr                                                   "0xB80118B0"
#define CAM_EMM_EMM_BUF_173_reg_addr                                                   "0xB80118B4"
#define CAM_EMM_EMM_BUF_174_reg_addr                                                   "0xB80118B8"
#define CAM_EMM_EMM_BUF_175_reg_addr                                                   "0xB80118BC"
#define CAM_EMM_EMM_BUF_176_reg_addr                                                   "0xB80118C0"
#define CAM_EMM_EMM_BUF_177_reg_addr                                                   "0xB80118C4"
#define CAM_EMM_EMM_BUF_178_reg_addr                                                   "0xB80118C8"
#define CAM_EMM_EMM_BUF_179_reg_addr                                                   "0xB80118CC"
#define CAM_EMM_EMM_BUF_180_reg_addr                                                   "0xB80118D0"
#define CAM_EMM_EMM_BUF_181_reg_addr                                                   "0xB80118D4"
#define CAM_EMM_EMM_BUF_182_reg_addr                                                   "0xB80118D8"
#define CAM_EMM_EMM_BUF_183_reg_addr                                                   "0xB80118DC"
#define CAM_EMM_EMM_BUF_184_reg_addr                                                   "0xB80118E0"
#define CAM_EMM_EMM_BUF_185_reg_addr                                                   "0xB80118E4"
#define CAM_EMM_EMM_BUF_186_reg_addr                                                   "0xB80118E8"
#define CAM_EMM_EMM_BUF_187_reg_addr                                                   "0xB80118EC"
#define CAM_EMM_EMM_BUF_188_reg_addr                                                   "0xB80118F0"
#define CAM_EMM_EMM_BUF_189_reg_addr                                                   "0xB80118F4"
#define CAM_EMM_EMM_BUF_190_reg_addr                                                   "0xB80118F8"
#define CAM_EMM_EMM_BUF_191_reg_addr                                                   "0xB80118FC"
#define CAM_EMM_EMM_BUF_192_reg_addr                                                   "0xB8011900"
#define CAM_EMM_EMM_BUF_193_reg_addr                                                   "0xB8011904"
#define CAM_EMM_EMM_BUF_194_reg_addr                                                   "0xB8011908"
#define CAM_EMM_EMM_BUF_195_reg_addr                                                   "0xB801190C"
#define CAM_EMM_EMM_BUF_196_reg_addr                                                   "0xB8011910"
#define CAM_EMM_EMM_BUF_197_reg_addr                                                   "0xB8011914"
#define CAM_EMM_EMM_BUF_198_reg_addr                                                   "0xB8011918"
#define CAM_EMM_EMM_BUF_199_reg_addr                                                   "0xB801191C"
#define CAM_EMM_EMM_BUF_200_reg_addr                                                   "0xB8011920"
#define CAM_EMM_EMM_BUF_201_reg_addr                                                   "0xB8011924"
#define CAM_EMM_EMM_BUF_202_reg_addr                                                   "0xB8011928"
#define CAM_EMM_EMM_BUF_203_reg_addr                                                   "0xB801192C"
#define CAM_EMM_EMM_BUF_204_reg_addr                                                   "0xB8011930"
#define CAM_EMM_EMM_BUF_205_reg_addr                                                   "0xB8011934"
#define CAM_EMM_EMM_BUF_206_reg_addr                                                   "0xB8011938"
#define CAM_EMM_EMM_BUF_207_reg_addr                                                   "0xB801193C"
#define CAM_EMM_EMM_BUF_208_reg_addr                                                   "0xB8011940"
#define CAM_EMM_EMM_BUF_209_reg_addr                                                   "0xB8011944"
#define CAM_EMM_EMM_BUF_210_reg_addr                                                   "0xB8011948"
#define CAM_EMM_EMM_BUF_211_reg_addr                                                   "0xB801194C"
#define CAM_EMM_EMM_BUF_212_reg_addr                                                   "0xB8011950"
#define CAM_EMM_EMM_BUF_213_reg_addr                                                   "0xB8011954"
#define CAM_EMM_EMM_BUF_214_reg_addr                                                   "0xB8011958"
#define CAM_EMM_EMM_BUF_215_reg_addr                                                   "0xB801195C"
#define CAM_EMM_EMM_BUF_216_reg_addr                                                   "0xB8011960"
#define CAM_EMM_EMM_BUF_217_reg_addr                                                   "0xB8011964"
#define CAM_EMM_EMM_BUF_218_reg_addr                                                   "0xB8011968"
#define CAM_EMM_EMM_BUF_219_reg_addr                                                   "0xB801196C"
#define CAM_EMM_EMM_BUF_220_reg_addr                                                   "0xB8011970"
#define CAM_EMM_EMM_BUF_221_reg_addr                                                   "0xB8011974"
#define CAM_EMM_EMM_BUF_222_reg_addr                                                   "0xB8011978"
#define CAM_EMM_EMM_BUF_223_reg_addr                                                   "0xB801197C"
#define CAM_EMM_EMM_BUF_224_reg_addr                                                   "0xB8011980"
#define CAM_EMM_EMM_BUF_225_reg_addr                                                   "0xB8011984"
#define CAM_EMM_EMM_BUF_226_reg_addr                                                   "0xB8011988"
#define CAM_EMM_EMM_BUF_227_reg_addr                                                   "0xB801198C"
#define CAM_EMM_EMM_BUF_228_reg_addr                                                   "0xB8011990"
#define CAM_EMM_EMM_BUF_229_reg_addr                                                   "0xB8011994"
#define CAM_EMM_EMM_BUF_230_reg_addr                                                   "0xB8011998"
#define CAM_EMM_EMM_BUF_231_reg_addr                                                   "0xB801199C"
#define CAM_EMM_EMM_BUF_232_reg_addr                                                   "0xB80119A0"
#define CAM_EMM_EMM_BUF_233_reg_addr                                                   "0xB80119A4"
#define CAM_EMM_EMM_BUF_234_reg_addr                                                   "0xB80119A8"
#define CAM_EMM_EMM_BUF_235_reg_addr                                                   "0xB80119AC"
#define CAM_EMM_EMM_BUF_236_reg_addr                                                   "0xB80119B0"
#define CAM_EMM_EMM_BUF_237_reg_addr                                                   "0xB80119B4"
#define CAM_EMM_EMM_BUF_238_reg_addr                                                   "0xB80119B8"
#define CAM_EMM_EMM_BUF_239_reg_addr                                                   "0xB80119BC"
#define CAM_EMM_EMM_BUF_240_reg_addr                                                   "0xB80119C0"
#define CAM_EMM_EMM_BUF_241_reg_addr                                                   "0xB80119C4"
#define CAM_EMM_EMM_BUF_242_reg_addr                                                   "0xB80119C8"
#define CAM_EMM_EMM_BUF_243_reg_addr                                                   "0xB80119CC"
#define CAM_EMM_EMM_BUF_244_reg_addr                                                   "0xB80119D0"
#define CAM_EMM_EMM_BUF_245_reg_addr                                                   "0xB80119D4"
#define CAM_EMM_EMM_BUF_246_reg_addr                                                   "0xB80119D8"
#define CAM_EMM_EMM_BUF_247_reg_addr                                                   "0xB80119DC"
#define CAM_EMM_EMM_BUF_248_reg_addr                                                   "0xB80119E0"
#define CAM_EMM_EMM_BUF_249_reg_addr                                                   "0xB80119E4"
#define CAM_EMM_EMM_BUF_250_reg_addr                                                   "0xB80119E8"
#define CAM_EMM_EMM_BUF_251_reg_addr                                                   "0xB80119EC"
#define CAM_EMM_EMM_BUF_252_reg_addr                                                   "0xB80119F0"
#define CAM_EMM_EMM_BUF_253_reg_addr                                                   "0xB80119F4"
#define CAM_EMM_EMM_BUF_254_reg_addr                                                   "0xB80119F8"
#define CAM_EMM_EMM_BUF_255_reg_addr                                                   "0xB80119FC"
#define CAM_EMM_EMM_BUF_256_reg_addr                                                   "0xB8011A00"
#define CAM_EMM_EMM_BUF_257_reg_addr                                                   "0xB8011A04"
#define CAM_EMM_EMM_BUF_258_reg_addr                                                   "0xB8011A08"
#define CAM_EMM_EMM_BUF_259_reg_addr                                                   "0xB8011A0C"
#define CAM_EMM_EMM_BUF_260_reg_addr                                                   "0xB8011A10"
#define CAM_EMM_EMM_BUF_261_reg_addr                                                   "0xB8011A14"
#define CAM_EMM_EMM_BUF_262_reg_addr                                                   "0xB8011A18"
#define CAM_EMM_EMM_BUF_263_reg_addr                                                   "0xB8011A1C"
#define CAM_EMM_EMM_BUF_264_reg_addr                                                   "0xB8011A20"
#define CAM_EMM_EMM_BUF_265_reg_addr                                                   "0xB8011A24"
#define CAM_EMM_EMM_BUF_266_reg_addr                                                   "0xB8011A28"
#define CAM_EMM_EMM_BUF_267_reg_addr                                                   "0xB8011A2C"
#define CAM_EMM_EMM_BUF_268_reg_addr                                                   "0xB8011A30"
#define CAM_EMM_EMM_BUF_269_reg_addr                                                   "0xB8011A34"
#define CAM_EMM_EMM_BUF_270_reg_addr                                                   "0xB8011A38"
#define CAM_EMM_EMM_BUF_271_reg_addr                                                   "0xB8011A3C"
#define CAM_EMM_EMM_BUF_272_reg_addr                                                   "0xB8011A40"
#define CAM_EMM_EMM_BUF_273_reg_addr                                                   "0xB8011A44"
#define CAM_EMM_EMM_BUF_274_reg_addr                                                   "0xB8011A48"
#define CAM_EMM_EMM_BUF_275_reg_addr                                                   "0xB8011A4C"
#define CAM_EMM_EMM_BUF_276_reg_addr                                                   "0xB8011A50"
#define CAM_EMM_EMM_BUF_277_reg_addr                                                   "0xB8011A54"
#define CAM_EMM_EMM_BUF_278_reg_addr                                                   "0xB8011A58"
#define CAM_EMM_EMM_BUF_279_reg_addr                                                   "0xB8011A5C"
#define CAM_EMM_EMM_BUF_280_reg_addr                                                   "0xB8011A60"
#define CAM_EMM_EMM_BUF_281_reg_addr                                                   "0xB8011A64"
#define CAM_EMM_EMM_BUF_282_reg_addr                                                   "0xB8011A68"
#define CAM_EMM_EMM_BUF_283_reg_addr                                                   "0xB8011A6C"
#define CAM_EMM_EMM_BUF_284_reg_addr                                                   "0xB8011A70"
#define CAM_EMM_EMM_BUF_285_reg_addr                                                   "0xB8011A74"
#define CAM_EMM_EMM_BUF_286_reg_addr                                                   "0xB8011A78"
#define CAM_EMM_EMM_BUF_287_reg_addr                                                   "0xB8011A7C"
#define CAM_EMM_EMM_BUF_288_reg_addr                                                   "0xB8011A80"
#define CAM_EMM_EMM_BUF_289_reg_addr                                                   "0xB8011A84"
#define CAM_EMM_EMM_BUF_290_reg_addr                                                   "0xB8011A88"
#define CAM_EMM_EMM_BUF_291_reg_addr                                                   "0xB8011A8C"
#define CAM_EMM_EMM_BUF_292_reg_addr                                                   "0xB8011A90"
#define CAM_EMM_EMM_BUF_293_reg_addr                                                   "0xB8011A94"
#define CAM_EMM_EMM_BUF_294_reg_addr                                                   "0xB8011A98"
#define CAM_EMM_EMM_BUF_295_reg_addr                                                   "0xB8011A9C"
#define CAM_EMM_EMM_BUF_296_reg_addr                                                   "0xB8011AA0"
#define CAM_EMM_EMM_BUF_297_reg_addr                                                   "0xB8011AA4"
#define CAM_EMM_EMM_BUF_298_reg_addr                                                   "0xB8011AA8"
#define CAM_EMM_EMM_BUF_299_reg_addr                                                   "0xB8011AAC"
#define CAM_EMM_EMM_BUF_300_reg_addr                                                   "0xB8011AB0"
#define CAM_EMM_EMM_BUF_301_reg_addr                                                   "0xB8011AB4"
#define CAM_EMM_EMM_BUF_302_reg_addr                                                   "0xB8011AB8"
#define CAM_EMM_EMM_BUF_303_reg_addr                                                   "0xB8011ABC"
#define CAM_EMM_EMM_BUF_304_reg_addr                                                   "0xB8011AC0"
#define CAM_EMM_EMM_BUF_305_reg_addr                                                   "0xB8011AC4"
#define CAM_EMM_EMM_BUF_306_reg_addr                                                   "0xB8011AC8"
#define CAM_EMM_EMM_BUF_307_reg_addr                                                   "0xB8011ACC"
#define CAM_EMM_EMM_BUF_308_reg_addr                                                   "0xB8011AD0"
#define CAM_EMM_EMM_BUF_309_reg_addr                                                   "0xB8011AD4"
#define CAM_EMM_EMM_BUF_310_reg_addr                                                   "0xB8011AD8"
#define CAM_EMM_EMM_BUF_311_reg_addr                                                   "0xB8011ADC"
#define CAM_EMM_EMM_BUF_312_reg_addr                                                   "0xB8011AE0"
#define CAM_EMM_EMM_BUF_313_reg_addr                                                   "0xB8011AE4"
#define CAM_EMM_EMM_BUF_314_reg_addr                                                   "0xB8011AE8"
#define CAM_EMM_EMM_BUF_315_reg_addr                                                   "0xB8011AEC"
#define CAM_EMM_EMM_BUF_316_reg_addr                                                   "0xB8011AF0"
#define CAM_EMM_EMM_BUF_317_reg_addr                                                   "0xB8011AF4"
#define CAM_EMM_EMM_BUF_318_reg_addr                                                   "0xB8011AF8"
#define CAM_EMM_EMM_BUF_319_reg_addr                                                   "0xB8011AFC"
#define CAM_EMM_EMM_BUF_320_reg_addr                                                   "0xB8011B00"
#define CAM_EMM_EMM_BUF_321_reg_addr                                                   "0xB8011B04"
#define CAM_EMM_EMM_BUF_322_reg_addr                                                   "0xB8011B08"
#define CAM_EMM_EMM_BUF_323_reg_addr                                                   "0xB8011B0C"
#define CAM_EMM_EMM_BUF_324_reg_addr                                                   "0xB8011B10"
#define CAM_EMM_EMM_BUF_325_reg_addr                                                   "0xB8011B14"
#define CAM_EMM_EMM_BUF_326_reg_addr                                                   "0xB8011B18"
#define CAM_EMM_EMM_BUF_327_reg_addr                                                   "0xB8011B1C"
#define CAM_EMM_EMM_BUF_328_reg_addr                                                   "0xB8011B20"
#define CAM_EMM_EMM_BUF_329_reg_addr                                                   "0xB8011B24"
#define CAM_EMM_EMM_BUF_330_reg_addr                                                   "0xB8011B28"
#define CAM_EMM_EMM_BUF_331_reg_addr                                                   "0xB8011B2C"
#define CAM_EMM_EMM_BUF_332_reg_addr                                                   "0xB8011B30"
#define CAM_EMM_EMM_BUF_333_reg_addr                                                   "0xB8011B34"
#define CAM_EMM_EMM_BUF_334_reg_addr                                                   "0xB8011B38"
#define CAM_EMM_EMM_BUF_335_reg_addr                                                   "0xB8011B3C"
#define CAM_EMM_EMM_BUF_336_reg_addr                                                   "0xB8011B40"
#define CAM_EMM_EMM_BUF_337_reg_addr                                                   "0xB8011B44"
#define CAM_EMM_EMM_BUF_338_reg_addr                                                   "0xB8011B48"
#define CAM_EMM_EMM_BUF_339_reg_addr                                                   "0xB8011B4C"
#define CAM_EMM_EMM_BUF_340_reg_addr                                                   "0xB8011B50"
#define CAM_EMM_EMM_BUF_341_reg_addr                                                   "0xB8011B54"
#define CAM_EMM_EMM_BUF_342_reg_addr                                                   "0xB8011B58"
#define CAM_EMM_EMM_BUF_343_reg_addr                                                   "0xB8011B5C"
#define CAM_EMM_EMM_BUF_344_reg_addr                                                   "0xB8011B60"
#define CAM_EMM_EMM_BUF_345_reg_addr                                                   "0xB8011B64"
#define CAM_EMM_EMM_BUF_346_reg_addr                                                   "0xB8011B68"
#define CAM_EMM_EMM_BUF_347_reg_addr                                                   "0xB8011B6C"
#define CAM_EMM_EMM_BUF_348_reg_addr                                                   "0xB8011B70"
#define CAM_EMM_EMM_BUF_349_reg_addr                                                   "0xB8011B74"
#define CAM_EMM_EMM_BUF_350_reg_addr                                                   "0xB8011B78"
#define CAM_EMM_EMM_BUF_351_reg_addr                                                   "0xB8011B7C"
#define CAM_EMM_EMM_BUF_352_reg_addr                                                   "0xB8011B80"
#define CAM_EMM_EMM_BUF_353_reg_addr                                                   "0xB8011B84"
#define CAM_EMM_EMM_BUF_354_reg_addr                                                   "0xB8011B88"
#define CAM_EMM_EMM_BUF_355_reg_addr                                                   "0xB8011B8C"
#define CAM_EMM_EMM_BUF_356_reg_addr                                                   "0xB8011B90"
#define CAM_EMM_EMM_BUF_357_reg_addr                                                   "0xB8011B94"
#define CAM_EMM_EMM_BUF_358_reg_addr                                                   "0xB8011B98"
#define CAM_EMM_EMM_BUF_359_reg_addr                                                   "0xB8011B9C"
#define CAM_EMM_EMM_BUF_360_reg_addr                                                   "0xB8011BA0"
#define CAM_EMM_EMM_BUF_361_reg_addr                                                   "0xB8011BA4"
#define CAM_EMM_EMM_BUF_362_reg_addr                                                   "0xB8011BA8"
#define CAM_EMM_EMM_BUF_363_reg_addr                                                   "0xB8011BAC"
#define CAM_EMM_EMM_BUF_364_reg_addr                                                   "0xB8011BB0"
#define CAM_EMM_EMM_BUF_365_reg_addr                                                   "0xB8011BB4"
#define CAM_EMM_EMM_BUF_366_reg_addr                                                   "0xB8011BB8"
#define CAM_EMM_EMM_BUF_367_reg_addr                                                   "0xB8011BBC"
#define CAM_EMM_EMM_BUF_368_reg_addr                                                   "0xB8011BC0"
#define CAM_EMM_EMM_BUF_369_reg_addr                                                   "0xB8011BC4"
#define CAM_EMM_EMM_BUF_370_reg_addr                                                   "0xB8011BC8"
#define CAM_EMM_EMM_BUF_371_reg_addr                                                   "0xB8011BCC"
#define CAM_EMM_EMM_BUF_372_reg_addr                                                   "0xB8011BD0"
#define CAM_EMM_EMM_BUF_373_reg_addr                                                   "0xB8011BD4"
#define CAM_EMM_EMM_BUF_374_reg_addr                                                   "0xB8011BD8"
#define CAM_EMM_EMM_BUF_375_reg_addr                                                   "0xB8011BDC"
#define CAM_EMM_EMM_BUF_376_reg_addr                                                   "0xB8011BE0"
#define CAM_EMM_EMM_BUF_377_reg_addr                                                   "0xB8011BE4"
#define CAM_EMM_EMM_BUF_378_reg_addr                                                   "0xB8011BE8"
#define CAM_EMM_EMM_BUF_379_reg_addr                                                   "0xB8011BEC"
#define CAM_EMM_EMM_BUF_380_reg_addr                                                   "0xB8011BF0"
#define CAM_EMM_EMM_BUF_381_reg_addr                                                   "0xB8011BF4"
#define CAM_EMM_EMM_BUF_382_reg_addr                                                   "0xB8011BF8"
#define CAM_EMM_EMM_BUF_383_reg_addr                                                   "0xB8011BFC"
#define CAM_EMM_EMM_BUF_384_reg_addr                                                   "0xB8011C00"
#define CAM_EMM_EMM_BUF_385_reg_addr                                                   "0xB8011C04"
#define CAM_EMM_EMM_BUF_386_reg_addr                                                   "0xB8011C08"
#define CAM_EMM_EMM_BUF_387_reg_addr                                                   "0xB8011C0C"
#define CAM_EMM_EMM_BUF_388_reg_addr                                                   "0xB8011C10"
#define CAM_EMM_EMM_BUF_389_reg_addr                                                   "0xB8011C14"
#define CAM_EMM_EMM_BUF_390_reg_addr                                                   "0xB8011C18"
#define CAM_EMM_EMM_BUF_391_reg_addr                                                   "0xB8011C1C"
#define CAM_EMM_EMM_BUF_392_reg_addr                                                   "0xB8011C20"
#define CAM_EMM_EMM_BUF_393_reg_addr                                                   "0xB8011C24"
#define CAM_EMM_EMM_BUF_394_reg_addr                                                   "0xB8011C28"
#define CAM_EMM_EMM_BUF_395_reg_addr                                                   "0xB8011C2C"
#define CAM_EMM_EMM_BUF_396_reg_addr                                                   "0xB8011C30"
#define CAM_EMM_EMM_BUF_397_reg_addr                                                   "0xB8011C34"
#define CAM_EMM_EMM_BUF_398_reg_addr                                                   "0xB8011C38"
#define CAM_EMM_EMM_BUF_399_reg_addr                                                   "0xB8011C3C"
#define CAM_EMM_EMM_BUF_400_reg_addr                                                   "0xB8011C40"
#define CAM_EMM_EMM_BUF_401_reg_addr                                                   "0xB8011C44"
#define CAM_EMM_EMM_BUF_402_reg_addr                                                   "0xB8011C48"
#define CAM_EMM_EMM_BUF_403_reg_addr                                                   "0xB8011C4C"
#define CAM_EMM_EMM_BUF_404_reg_addr                                                   "0xB8011C50"
#define CAM_EMM_EMM_BUF_405_reg_addr                                                   "0xB8011C54"
#define CAM_EMM_EMM_BUF_406_reg_addr                                                   "0xB8011C58"
#define CAM_EMM_EMM_BUF_407_reg_addr                                                   "0xB8011C5C"
#define CAM_EMM_EMM_BUF_408_reg_addr                                                   "0xB8011C60"
#define CAM_EMM_EMM_BUF_409_reg_addr                                                   "0xB8011C64"
#define CAM_EMM_EMM_BUF_410_reg_addr                                                   "0xB8011C68"
#define CAM_EMM_EMM_BUF_411_reg_addr                                                   "0xB8011C6C"
#define CAM_EMM_EMM_BUF_412_reg_addr                                                   "0xB8011C70"
#define CAM_EMM_EMM_BUF_413_reg_addr                                                   "0xB8011C74"
#define CAM_EMM_EMM_BUF_414_reg_addr                                                   "0xB8011C78"
#define CAM_EMM_EMM_BUF_415_reg_addr                                                   "0xB8011C7C"
#define CAM_EMM_EMM_BUF_416_reg_addr                                                   "0xB8011C80"
#define CAM_EMM_EMM_BUF_417_reg_addr                                                   "0xB8011C84"
#define CAM_EMM_EMM_BUF_418_reg_addr                                                   "0xB8011C88"
#define CAM_EMM_EMM_BUF_419_reg_addr                                                   "0xB8011C8C"
#define CAM_EMM_EMM_BUF_420_reg_addr                                                   "0xB8011C90"
#define CAM_EMM_EMM_BUF_421_reg_addr                                                   "0xB8011C94"
#define CAM_EMM_EMM_BUF_422_reg_addr                                                   "0xB8011C98"
#define CAM_EMM_EMM_BUF_423_reg_addr                                                   "0xB8011C9C"
#define CAM_EMM_EMM_BUF_424_reg_addr                                                   "0xB8011CA0"
#define CAM_EMM_EMM_BUF_425_reg_addr                                                   "0xB8011CA4"
#define CAM_EMM_EMM_BUF_426_reg_addr                                                   "0xB8011CA8"
#define CAM_EMM_EMM_BUF_427_reg_addr                                                   "0xB8011CAC"
#define CAM_EMM_EMM_BUF_428_reg_addr                                                   "0xB8011CB0"
#define CAM_EMM_EMM_BUF_429_reg_addr                                                   "0xB8011CB4"
#define CAM_EMM_EMM_BUF_430_reg_addr                                                   "0xB8011CB8"
#define CAM_EMM_EMM_BUF_431_reg_addr                                                   "0xB8011CBC"
#define CAM_EMM_EMM_BUF_432_reg_addr                                                   "0xB8011CC0"
#define CAM_EMM_EMM_BUF_433_reg_addr                                                   "0xB8011CC4"
#define CAM_EMM_EMM_BUF_434_reg_addr                                                   "0xB8011CC8"
#define CAM_EMM_EMM_BUF_435_reg_addr                                                   "0xB8011CCC"
#define CAM_EMM_EMM_BUF_436_reg_addr                                                   "0xB8011CD0"
#define CAM_EMM_EMM_BUF_437_reg_addr                                                   "0xB8011CD4"
#define CAM_EMM_EMM_BUF_438_reg_addr                                                   "0xB8011CD8"
#define CAM_EMM_EMM_BUF_439_reg_addr                                                   "0xB8011CDC"
#define CAM_EMM_EMM_BUF_440_reg_addr                                                   "0xB8011CE0"
#define CAM_EMM_EMM_BUF_441_reg_addr                                                   "0xB8011CE4"
#define CAM_EMM_EMM_BUF_442_reg_addr                                                   "0xB8011CE8"
#define CAM_EMM_EMM_BUF_443_reg_addr                                                   "0xB8011CEC"
#define CAM_EMM_EMM_BUF_444_reg_addr                                                   "0xB8011CF0"
#define CAM_EMM_EMM_BUF_445_reg_addr                                                   "0xB8011CF4"
#define CAM_EMM_EMM_BUF_446_reg_addr                                                   "0xB8011CF8"
#define CAM_EMM_EMM_BUF_447_reg_addr                                                   "0xB8011CFC"
#define CAM_EMM_EMM_BUF_448_reg_addr                                                   "0xB8011D00"
#define CAM_EMM_EMM_BUF_449_reg_addr                                                   "0xB8011D04"
#define CAM_EMM_EMM_BUF_450_reg_addr                                                   "0xB8011D08"
#define CAM_EMM_EMM_BUF_451_reg_addr                                                   "0xB8011D0C"
#define CAM_EMM_EMM_BUF_452_reg_addr                                                   "0xB8011D10"
#define CAM_EMM_EMM_BUF_453_reg_addr                                                   "0xB8011D14"
#define CAM_EMM_EMM_BUF_454_reg_addr                                                   "0xB8011D18"
#define CAM_EMM_EMM_BUF_455_reg_addr                                                   "0xB8011D1C"
#define CAM_EMM_EMM_BUF_456_reg_addr                                                   "0xB8011D20"
#define CAM_EMM_EMM_BUF_457_reg_addr                                                   "0xB8011D24"
#define CAM_EMM_EMM_BUF_458_reg_addr                                                   "0xB8011D28"
#define CAM_EMM_EMM_BUF_459_reg_addr                                                   "0xB8011D2C"
#define CAM_EMM_EMM_BUF_460_reg_addr                                                   "0xB8011D30"
#define CAM_EMM_EMM_BUF_461_reg_addr                                                   "0xB8011D34"
#define CAM_EMM_EMM_BUF_462_reg_addr                                                   "0xB8011D38"
#define CAM_EMM_EMM_BUF_463_reg_addr                                                   "0xB8011D3C"
#define CAM_EMM_EMM_BUF_464_reg_addr                                                   "0xB8011D40"
#define CAM_EMM_EMM_BUF_465_reg_addr                                                   "0xB8011D44"
#define CAM_EMM_EMM_BUF_466_reg_addr                                                   "0xB8011D48"
#define CAM_EMM_EMM_BUF_467_reg_addr                                                   "0xB8011D4C"
#define CAM_EMM_EMM_BUF_468_reg_addr                                                   "0xB8011D50"
#define CAM_EMM_EMM_BUF_469_reg_addr                                                   "0xB8011D54"
#define CAM_EMM_EMM_BUF_470_reg_addr                                                   "0xB8011D58"
#define CAM_EMM_EMM_BUF_471_reg_addr                                                   "0xB8011D5C"
#define CAM_EMM_EMM_BUF_472_reg_addr                                                   "0xB8011D60"
#define CAM_EMM_EMM_BUF_473_reg_addr                                                   "0xB8011D64"
#define CAM_EMM_EMM_BUF_474_reg_addr                                                   "0xB8011D68"
#define CAM_EMM_EMM_BUF_475_reg_addr                                                   "0xB8011D6C"
#define CAM_EMM_EMM_BUF_476_reg_addr                                                   "0xB8011D70"
#define CAM_EMM_EMM_BUF_477_reg_addr                                                   "0xB8011D74"
#define CAM_EMM_EMM_BUF_478_reg_addr                                                   "0xB8011D78"
#define CAM_EMM_EMM_BUF_479_reg_addr                                                   "0xB8011D7C"
#define CAM_EMM_EMM_BUF_480_reg_addr                                                   "0xB8011D80"
#define CAM_EMM_EMM_BUF_481_reg_addr                                                   "0xB8011D84"
#define CAM_EMM_EMM_BUF_482_reg_addr                                                   "0xB8011D88"
#define CAM_EMM_EMM_BUF_483_reg_addr                                                   "0xB8011D8C"
#define CAM_EMM_EMM_BUF_484_reg_addr                                                   "0xB8011D90"
#define CAM_EMM_EMM_BUF_485_reg_addr                                                   "0xB8011D94"
#define CAM_EMM_EMM_BUF_486_reg_addr                                                   "0xB8011D98"
#define CAM_EMM_EMM_BUF_487_reg_addr                                                   "0xB8011D9C"
#define CAM_EMM_EMM_BUF_488_reg_addr                                                   "0xB8011DA0"
#define CAM_EMM_EMM_BUF_489_reg_addr                                                   "0xB8011DA4"
#define CAM_EMM_EMM_BUF_490_reg_addr                                                   "0xB8011DA8"
#define CAM_EMM_EMM_BUF_491_reg_addr                                                   "0xB8011DAC"
#define CAM_EMM_EMM_BUF_492_reg_addr                                                   "0xB8011DB0"
#define CAM_EMM_EMM_BUF_493_reg_addr                                                   "0xB8011DB4"
#define CAM_EMM_EMM_BUF_494_reg_addr                                                   "0xB8011DB8"
#define CAM_EMM_EMM_BUF_495_reg_addr                                                   "0xB8011DBC"
#define CAM_EMM_EMM_BUF_496_reg_addr                                                   "0xB8011DC0"
#define CAM_EMM_EMM_BUF_497_reg_addr                                                   "0xB8011DC4"
#define CAM_EMM_EMM_BUF_498_reg_addr                                                   "0xB8011DC8"
#define CAM_EMM_EMM_BUF_499_reg_addr                                                   "0xB8011DCC"
#define CAM_EMM_EMM_BUF_500_reg_addr                                                   "0xB8011DD0"
#define CAM_EMM_EMM_BUF_501_reg_addr                                                   "0xB8011DD4"
#define CAM_EMM_EMM_BUF_502_reg_addr                                                   "0xB8011DD8"
#define CAM_EMM_EMM_BUF_503_reg_addr                                                   "0xB8011DDC"
#define CAM_EMM_EMM_BUF_504_reg_addr                                                   "0xB8011DE0"
#define CAM_EMM_EMM_BUF_505_reg_addr                                                   "0xB8011DE4"
#define CAM_EMM_EMM_BUF_506_reg_addr                                                   "0xB8011DE8"
#define CAM_EMM_EMM_BUF_507_reg_addr                                                   "0xB8011DEC"
#define CAM_EMM_EMM_BUF_508_reg_addr                                                   "0xB8011DF0"
#define CAM_EMM_EMM_BUF_509_reg_addr                                                   "0xB8011DF4"
#define CAM_EMM_EMM_BUF_510_reg_addr                                                   "0xB8011DF8"
#define CAM_EMM_EMM_BUF_511_reg_addr                                                   "0xB8011DFC"
#define CAM_EMM_EMM_BUF_512_reg_addr                                                   "0xB8011E00"
#define CAM_EMM_EMM_BUF_513_reg_addr                                                   "0xB8011E04"
#define CAM_EMM_EMM_BUF_514_reg_addr                                                   "0xB8011E08"
#define CAM_EMM_EMM_BUF_515_reg_addr                                                   "0xB8011E0C"
#define CAM_EMM_EMM_BUF_516_reg_addr                                                   "0xB8011E10"
#define CAM_EMM_EMM_BUF_517_reg_addr                                                   "0xB8011E14"
#define CAM_EMM_EMM_BUF_518_reg_addr                                                   "0xB8011E18"
#define CAM_EMM_EMM_BUF_519_reg_addr                                                   "0xB8011E1C"
#define CAM_EMM_EMM_BUF_520_reg_addr                                                   "0xB8011E20"
#define CAM_EMM_EMM_BUF_521_reg_addr                                                   "0xB8011E24"
#define CAM_EMM_EMM_BUF_522_reg_addr                                                   "0xB8011E28"
#define CAM_EMM_EMM_BUF_523_reg_addr                                                   "0xB8011E2C"
#define CAM_EMM_EMM_BUF_524_reg_addr                                                   "0xB8011E30"
#define CAM_EMM_EMM_BUF_525_reg_addr                                                   "0xB8011E34"
#define CAM_EMM_EMM_BUF_526_reg_addr                                                   "0xB8011E38"
#define CAM_EMM_EMM_BUF_527_reg_addr                                                   "0xB8011E3C"
#define CAM_EMM_EMM_BUF_528_reg_addr                                                   "0xB8011E40"
#define CAM_EMM_EMM_BUF_529_reg_addr                                                   "0xB8011E44"
#define CAM_EMM_EMM_BUF_530_reg_addr                                                   "0xB8011E48"
#define CAM_EMM_EMM_BUF_531_reg_addr                                                   "0xB8011E4C"
#define CAM_EMM_EMM_BUF_532_reg_addr                                                   "0xB8011E50"
#define CAM_EMM_EMM_BUF_533_reg_addr                                                   "0xB8011E54"
#define CAM_EMM_EMM_BUF_534_reg_addr                                                   "0xB8011E58"
#define CAM_EMM_EMM_BUF_535_reg_addr                                                   "0xB8011E5C"
#define CAM_EMM_EMM_BUF_536_reg_addr                                                   "0xB8011E60"
#define CAM_EMM_EMM_BUF_537_reg_addr                                                   "0xB8011E64"
#define CAM_EMM_EMM_BUF_538_reg_addr                                                   "0xB8011E68"
#define CAM_EMM_EMM_BUF_539_reg_addr                                                   "0xB8011E6C"
#define CAM_EMM_EMM_BUF_540_reg_addr                                                   "0xB8011E70"
#define CAM_EMM_EMM_BUF_541_reg_addr                                                   "0xB8011E74"
#define CAM_EMM_EMM_BUF_542_reg_addr                                                   "0xB8011E78"
#define CAM_EMM_EMM_BUF_543_reg_addr                                                   "0xB8011E7C"
#define CAM_EMM_EMM_BUF_544_reg_addr                                                   "0xB8011E80"
#define CAM_EMM_EMM_BUF_545_reg_addr                                                   "0xB8011E84"
#define CAM_EMM_EMM_BUF_546_reg_addr                                                   "0xB8011E88"
#define CAM_EMM_EMM_BUF_547_reg_addr                                                   "0xB8011E8C"
#define CAM_EMM_EMM_BUF_548_reg_addr                                                   "0xB8011E90"
#define CAM_EMM_EMM_BUF_549_reg_addr                                                   "0xB8011E94"
#define CAM_EMM_EMM_BUF_550_reg_addr                                                   "0xB8011E98"
#define CAM_EMM_EMM_BUF_551_reg_addr                                                   "0xB8011E9C"
#define CAM_EMM_EMM_BUF_552_reg_addr                                                   "0xB8011EA0"
#define CAM_EMM_EMM_BUF_553_reg_addr                                                   "0xB8011EA4"
#define CAM_EMM_EMM_BUF_554_reg_addr                                                   "0xB8011EA8"
#define CAM_EMM_EMM_BUF_555_reg_addr                                                   "0xB8011EAC"
#define CAM_EMM_EMM_BUF_556_reg_addr                                                   "0xB8011EB0"
#define CAM_EMM_EMM_BUF_557_reg_addr                                                   "0xB8011EB4"
#define CAM_EMM_EMM_BUF_558_reg_addr                                                   "0xB8011EB8"
#define CAM_EMM_EMM_BUF_559_reg_addr                                                   "0xB8011EBC"
#define CAM_EMM_EMM_BUF_560_reg_addr                                                   "0xB8011EC0"
#define CAM_EMM_EMM_BUF_561_reg_addr                                                   "0xB8011EC4"
#define CAM_EMM_EMM_BUF_562_reg_addr                                                   "0xB8011EC8"
#define CAM_EMM_EMM_BUF_563_reg_addr                                                   "0xB8011ECC"
#define CAM_EMM_EMM_BUF_564_reg_addr                                                   "0xB8011ED0"
#define CAM_EMM_EMM_BUF_565_reg_addr                                                   "0xB8011ED4"
#define CAM_EMM_EMM_BUF_566_reg_addr                                                   "0xB8011ED8"
#define CAM_EMM_EMM_BUF_567_reg_addr                                                   "0xB8011EDC"
#define CAM_EMM_EMM_BUF_568_reg_addr                                                   "0xB8011EE0"
#define CAM_EMM_EMM_BUF_569_reg_addr                                                   "0xB8011EE4"
#define CAM_EMM_EMM_BUF_570_reg_addr                                                   "0xB8011EE8"
#define CAM_EMM_EMM_BUF_571_reg_addr                                                   "0xB8011EEC"
#define CAM_EMM_EMM_BUF_572_reg_addr                                                   "0xB8011EF0"
#define CAM_EMM_EMM_BUF_573_reg_addr                                                   "0xB8011EF4"
#define CAM_EMM_EMM_BUF_574_reg_addr                                                   "0xB8011EF8"
#define CAM_EMM_EMM_BUF_575_reg_addr                                                   "0xB8011EFC"
#define CAM_EMM_EMM_BUF_576_reg_addr                                                   "0xB8011F00"
#define CAM_EMM_EMM_BUF_577_reg_addr                                                   "0xB8011F04"
#define CAM_EMM_EMM_BUF_578_reg_addr                                                   "0xB8011F08"
#define CAM_EMM_EMM_BUF_579_reg_addr                                                   "0xB8011F0C"
#define CAM_EMM_EMM_BUF_580_reg_addr                                                   "0xB8011F10"
#define CAM_EMM_EMM_BUF_581_reg_addr                                                   "0xB8011F14"
#define CAM_EMM_EMM_BUF_582_reg_addr                                                   "0xB8011F18"
#define CAM_EMM_EMM_BUF_583_reg_addr                                                   "0xB8011F1C"
#define CAM_EMM_EMM_BUF_584_reg_addr                                                   "0xB8011F20"
#define CAM_EMM_EMM_BUF_585_reg_addr                                                   "0xB8011F24"
#define CAM_EMM_EMM_BUF_586_reg_addr                                                   "0xB8011F28"
#define CAM_EMM_EMM_BUF_587_reg_addr                                                   "0xB8011F2C"
#define CAM_EMM_EMM_BUF_588_reg_addr                                                   "0xB8011F30"
#define CAM_EMM_EMM_BUF_589_reg_addr                                                   "0xB8011F34"
#define CAM_EMM_EMM_BUF_590_reg_addr                                                   "0xB8011F38"
#define CAM_EMM_EMM_BUF_591_reg_addr                                                   "0xB8011F3C"
#define CAM_EMM_EMM_BUF_592_reg_addr                                                   "0xB8011F40"
#define CAM_EMM_EMM_BUF_593_reg_addr                                                   "0xB8011F44"
#define CAM_EMM_EMM_BUF_594_reg_addr                                                   "0xB8011F48"
#define CAM_EMM_EMM_BUF_595_reg_addr                                                   "0xB8011F4C"
#define CAM_EMM_EMM_BUF_596_reg_addr                                                   "0xB8011F50"
#define CAM_EMM_EMM_BUF_597_reg_addr                                                   "0xB8011F54"
#define CAM_EMM_EMM_BUF_598_reg_addr                                                   "0xB8011F58"
#define CAM_EMM_EMM_BUF_599_reg_addr                                                   "0xB8011F5C"
#define CAM_EMM_EMM_BUF_600_reg_addr                                                   "0xB8011F60"
#define CAM_EMM_EMM_BUF_601_reg_addr                                                   "0xB8011F64"
#define CAM_EMM_EMM_BUF_602_reg_addr                                                   "0xB8011F68"
#define CAM_EMM_EMM_BUF_603_reg_addr                                                   "0xB8011F6C"
#define CAM_EMM_EMM_BUF_604_reg_addr                                                   "0xB8011F70"
#define CAM_EMM_EMM_BUF_605_reg_addr                                                   "0xB8011F74"
#define CAM_EMM_EMM_BUF_606_reg_addr                                                   "0xB8011F78"
#define CAM_EMM_EMM_BUF_607_reg_addr                                                   "0xB8011F7C"
#define CAM_EMM_EMM_BUF_608_reg_addr                                                   "0xB8011F80"
#define CAM_EMM_EMM_BUF_609_reg_addr                                                   "0xB8011F84"
#define CAM_EMM_EMM_BUF_610_reg_addr                                                   "0xB8011F88"
#define CAM_EMM_EMM_BUF_611_reg_addr                                                   "0xB8011F8C"
#define CAM_EMM_EMM_BUF_612_reg_addr                                                   "0xB8011F90"
#define CAM_EMM_EMM_BUF_613_reg_addr                                                   "0xB8011F94"
#define CAM_EMM_EMM_BUF_614_reg_addr                                                   "0xB8011F98"
#define CAM_EMM_EMM_BUF_615_reg_addr                                                   "0xB8011F9C"
#define CAM_EMM_EMM_BUF_616_reg_addr                                                   "0xB8011FA0"
#define CAM_EMM_EMM_BUF_617_reg_addr                                                   "0xB8011FA4"
#define CAM_EMM_EMM_BUF_618_reg_addr                                                   "0xB8011FA8"
#define CAM_EMM_EMM_BUF_619_reg_addr                                                   "0xB8011FAC"
#define CAM_EMM_EMM_BUF_620_reg_addr                                                   "0xB8011FB0"
#define CAM_EMM_EMM_BUF_621_reg_addr                                                   "0xB8011FB4"
#define CAM_EMM_EMM_BUF_622_reg_addr                                                   "0xB8011FB8"
#define CAM_EMM_EMM_BUF_623_reg_addr                                                   "0xB8011FBC"
#define CAM_EMM_EMM_BUF_624_reg_addr                                                   "0xB8011FC0"
#define CAM_EMM_EMM_BUF_625_reg_addr                                                   "0xB8011FC4"
#define CAM_EMM_EMM_BUF_626_reg_addr                                                   "0xB8011FC8"
#define CAM_EMM_EMM_BUF_627_reg_addr                                                   "0xB8011FCC"
#define CAM_EMM_EMM_BUF_628_reg_addr                                                   "0xB8011FD0"
#define CAM_EMM_EMM_BUF_629_reg_addr                                                   "0xB8011FD4"
#define CAM_EMM_EMM_BUF_630_reg_addr                                                   "0xB8011FD8"
#define CAM_EMM_EMM_BUF_631_reg_addr                                                   "0xB8011FDC"
#define CAM_EMM_EMM_BUF_632_reg_addr                                                   "0xB8011FE0"
#define CAM_EMM_EMM_BUF_633_reg_addr                                                   "0xB8011FE4"
#define CAM_EMM_EMM_BUF_634_reg_addr                                                   "0xB8011FE8"
#define CAM_EMM_EMM_BUF_635_reg_addr                                                   "0xB8011FEC"
#define CAM_EMM_EMM_BUF_636_reg_addr                                                   "0xB8011FF0"
#define CAM_EMM_EMM_BUF_637_reg_addr                                                   "0xB8011FF4"
#define CAM_EMM_EMM_BUF_638_reg_addr                                                   "0xB8011FF8"
#define CAM_EMM_EMM_BUF_639_reg_addr                                                   "0xB8011FFC"
#define CAM_EMM_EMM_BUF_0_reg                                                        0xB8011600
#define CAM_EMM_EMM_BUF_1_reg                                                        0xB8011604
#define CAM_EMM_EMM_BUF_2_reg                                                        0xB8011608
#define CAM_EMM_EMM_BUF_3_reg                                                        0xB801160C
#define CAM_EMM_EMM_BUF_4_reg                                                        0xB8011610
#define CAM_EMM_EMM_BUF_5_reg                                                        0xB8011614
#define CAM_EMM_EMM_BUF_6_reg                                                        0xB8011618
#define CAM_EMM_EMM_BUF_7_reg                                                        0xB801161C
#define CAM_EMM_EMM_BUF_8_reg                                                        0xB8011620
#define CAM_EMM_EMM_BUF_9_reg                                                        0xB8011624
#define CAM_EMM_EMM_BUF_10_reg                                                        0xB8011628
#define CAM_EMM_EMM_BUF_11_reg                                                        0xB801162C
#define CAM_EMM_EMM_BUF_12_reg                                                        0xB8011630
#define CAM_EMM_EMM_BUF_13_reg                                                        0xB8011634
#define CAM_EMM_EMM_BUF_14_reg                                                        0xB8011638
#define CAM_EMM_EMM_BUF_15_reg                                                        0xB801163C
#define CAM_EMM_EMM_BUF_16_reg                                                        0xB8011640
#define CAM_EMM_EMM_BUF_17_reg                                                        0xB8011644
#define CAM_EMM_EMM_BUF_18_reg                                                        0xB8011648
#define CAM_EMM_EMM_BUF_19_reg                                                        0xB801164C
#define CAM_EMM_EMM_BUF_20_reg                                                        0xB8011650
#define CAM_EMM_EMM_BUF_21_reg                                                        0xB8011654
#define CAM_EMM_EMM_BUF_22_reg                                                        0xB8011658
#define CAM_EMM_EMM_BUF_23_reg                                                        0xB801165C
#define CAM_EMM_EMM_BUF_24_reg                                                        0xB8011660
#define CAM_EMM_EMM_BUF_25_reg                                                        0xB8011664
#define CAM_EMM_EMM_BUF_26_reg                                                        0xB8011668
#define CAM_EMM_EMM_BUF_27_reg                                                        0xB801166C
#define CAM_EMM_EMM_BUF_28_reg                                                        0xB8011670
#define CAM_EMM_EMM_BUF_29_reg                                                        0xB8011674
#define CAM_EMM_EMM_BUF_30_reg                                                        0xB8011678
#define CAM_EMM_EMM_BUF_31_reg                                                        0xB801167C
#define CAM_EMM_EMM_BUF_32_reg                                                        0xB8011680
#define CAM_EMM_EMM_BUF_33_reg                                                        0xB8011684
#define CAM_EMM_EMM_BUF_34_reg                                                        0xB8011688
#define CAM_EMM_EMM_BUF_35_reg                                                        0xB801168C
#define CAM_EMM_EMM_BUF_36_reg                                                        0xB8011690
#define CAM_EMM_EMM_BUF_37_reg                                                        0xB8011694
#define CAM_EMM_EMM_BUF_38_reg                                                        0xB8011698
#define CAM_EMM_EMM_BUF_39_reg                                                        0xB801169C
#define CAM_EMM_EMM_BUF_40_reg                                                        0xB80116A0
#define CAM_EMM_EMM_BUF_41_reg                                                        0xB80116A4
#define CAM_EMM_EMM_BUF_42_reg                                                        0xB80116A8
#define CAM_EMM_EMM_BUF_43_reg                                                        0xB80116AC
#define CAM_EMM_EMM_BUF_44_reg                                                        0xB80116B0
#define CAM_EMM_EMM_BUF_45_reg                                                        0xB80116B4
#define CAM_EMM_EMM_BUF_46_reg                                                        0xB80116B8
#define CAM_EMM_EMM_BUF_47_reg                                                        0xB80116BC
#define CAM_EMM_EMM_BUF_48_reg                                                        0xB80116C0
#define CAM_EMM_EMM_BUF_49_reg                                                        0xB80116C4
#define CAM_EMM_EMM_BUF_50_reg                                                        0xB80116C8
#define CAM_EMM_EMM_BUF_51_reg                                                        0xB80116CC
#define CAM_EMM_EMM_BUF_52_reg                                                        0xB80116D0
#define CAM_EMM_EMM_BUF_53_reg                                                        0xB80116D4
#define CAM_EMM_EMM_BUF_54_reg                                                        0xB80116D8
#define CAM_EMM_EMM_BUF_55_reg                                                        0xB80116DC
#define CAM_EMM_EMM_BUF_56_reg                                                        0xB80116E0
#define CAM_EMM_EMM_BUF_57_reg                                                        0xB80116E4
#define CAM_EMM_EMM_BUF_58_reg                                                        0xB80116E8
#define CAM_EMM_EMM_BUF_59_reg                                                        0xB80116EC
#define CAM_EMM_EMM_BUF_60_reg                                                        0xB80116F0
#define CAM_EMM_EMM_BUF_61_reg                                                        0xB80116F4
#define CAM_EMM_EMM_BUF_62_reg                                                        0xB80116F8
#define CAM_EMM_EMM_BUF_63_reg                                                        0xB80116FC
#define CAM_EMM_EMM_BUF_64_reg                                                        0xB8011700
#define CAM_EMM_EMM_BUF_65_reg                                                        0xB8011704
#define CAM_EMM_EMM_BUF_66_reg                                                        0xB8011708
#define CAM_EMM_EMM_BUF_67_reg                                                        0xB801170C
#define CAM_EMM_EMM_BUF_68_reg                                                        0xB8011710
#define CAM_EMM_EMM_BUF_69_reg                                                        0xB8011714
#define CAM_EMM_EMM_BUF_70_reg                                                        0xB8011718
#define CAM_EMM_EMM_BUF_71_reg                                                        0xB801171C
#define CAM_EMM_EMM_BUF_72_reg                                                        0xB8011720
#define CAM_EMM_EMM_BUF_73_reg                                                        0xB8011724
#define CAM_EMM_EMM_BUF_74_reg                                                        0xB8011728
#define CAM_EMM_EMM_BUF_75_reg                                                        0xB801172C
#define CAM_EMM_EMM_BUF_76_reg                                                        0xB8011730
#define CAM_EMM_EMM_BUF_77_reg                                                        0xB8011734
#define CAM_EMM_EMM_BUF_78_reg                                                        0xB8011738
#define CAM_EMM_EMM_BUF_79_reg                                                        0xB801173C
#define CAM_EMM_EMM_BUF_80_reg                                                        0xB8011740
#define CAM_EMM_EMM_BUF_81_reg                                                        0xB8011744
#define CAM_EMM_EMM_BUF_82_reg                                                        0xB8011748
#define CAM_EMM_EMM_BUF_83_reg                                                        0xB801174C
#define CAM_EMM_EMM_BUF_84_reg                                                        0xB8011750
#define CAM_EMM_EMM_BUF_85_reg                                                        0xB8011754
#define CAM_EMM_EMM_BUF_86_reg                                                        0xB8011758
#define CAM_EMM_EMM_BUF_87_reg                                                        0xB801175C
#define CAM_EMM_EMM_BUF_88_reg                                                        0xB8011760
#define CAM_EMM_EMM_BUF_89_reg                                                        0xB8011764
#define CAM_EMM_EMM_BUF_90_reg                                                        0xB8011768
#define CAM_EMM_EMM_BUF_91_reg                                                        0xB801176C
#define CAM_EMM_EMM_BUF_92_reg                                                        0xB8011770
#define CAM_EMM_EMM_BUF_93_reg                                                        0xB8011774
#define CAM_EMM_EMM_BUF_94_reg                                                        0xB8011778
#define CAM_EMM_EMM_BUF_95_reg                                                        0xB801177C
#define CAM_EMM_EMM_BUF_96_reg                                                        0xB8011780
#define CAM_EMM_EMM_BUF_97_reg                                                        0xB8011784
#define CAM_EMM_EMM_BUF_98_reg                                                        0xB8011788
#define CAM_EMM_EMM_BUF_99_reg                                                        0xB801178C
#define CAM_EMM_EMM_BUF_100_reg                                                        0xB8011790
#define CAM_EMM_EMM_BUF_101_reg                                                        0xB8011794
#define CAM_EMM_EMM_BUF_102_reg                                                        0xB8011798
#define CAM_EMM_EMM_BUF_103_reg                                                        0xB801179C
#define CAM_EMM_EMM_BUF_104_reg                                                        0xB80117A0
#define CAM_EMM_EMM_BUF_105_reg                                                        0xB80117A4
#define CAM_EMM_EMM_BUF_106_reg                                                        0xB80117A8
#define CAM_EMM_EMM_BUF_107_reg                                                        0xB80117AC
#define CAM_EMM_EMM_BUF_108_reg                                                        0xB80117B0
#define CAM_EMM_EMM_BUF_109_reg                                                        0xB80117B4
#define CAM_EMM_EMM_BUF_110_reg                                                        0xB80117B8
#define CAM_EMM_EMM_BUF_111_reg                                                        0xB80117BC
#define CAM_EMM_EMM_BUF_112_reg                                                        0xB80117C0
#define CAM_EMM_EMM_BUF_113_reg                                                        0xB80117C4
#define CAM_EMM_EMM_BUF_114_reg                                                        0xB80117C8
#define CAM_EMM_EMM_BUF_115_reg                                                        0xB80117CC
#define CAM_EMM_EMM_BUF_116_reg                                                        0xB80117D0
#define CAM_EMM_EMM_BUF_117_reg                                                        0xB80117D4
#define CAM_EMM_EMM_BUF_118_reg                                                        0xB80117D8
#define CAM_EMM_EMM_BUF_119_reg                                                        0xB80117DC
#define CAM_EMM_EMM_BUF_120_reg                                                        0xB80117E0
#define CAM_EMM_EMM_BUF_121_reg                                                        0xB80117E4
#define CAM_EMM_EMM_BUF_122_reg                                                        0xB80117E8
#define CAM_EMM_EMM_BUF_123_reg                                                        0xB80117EC
#define CAM_EMM_EMM_BUF_124_reg                                                        0xB80117F0
#define CAM_EMM_EMM_BUF_125_reg                                                        0xB80117F4
#define CAM_EMM_EMM_BUF_126_reg                                                        0xB80117F8
#define CAM_EMM_EMM_BUF_127_reg                                                        0xB80117FC
#define CAM_EMM_EMM_BUF_128_reg                                                        0xB8011800
#define CAM_EMM_EMM_BUF_129_reg                                                        0xB8011804
#define CAM_EMM_EMM_BUF_130_reg                                                        0xB8011808
#define CAM_EMM_EMM_BUF_131_reg                                                        0xB801180C
#define CAM_EMM_EMM_BUF_132_reg                                                        0xB8011810
#define CAM_EMM_EMM_BUF_133_reg                                                        0xB8011814
#define CAM_EMM_EMM_BUF_134_reg                                                        0xB8011818
#define CAM_EMM_EMM_BUF_135_reg                                                        0xB801181C
#define CAM_EMM_EMM_BUF_136_reg                                                        0xB8011820
#define CAM_EMM_EMM_BUF_137_reg                                                        0xB8011824
#define CAM_EMM_EMM_BUF_138_reg                                                        0xB8011828
#define CAM_EMM_EMM_BUF_139_reg                                                        0xB801182C
#define CAM_EMM_EMM_BUF_140_reg                                                        0xB8011830
#define CAM_EMM_EMM_BUF_141_reg                                                        0xB8011834
#define CAM_EMM_EMM_BUF_142_reg                                                        0xB8011838
#define CAM_EMM_EMM_BUF_143_reg                                                        0xB801183C
#define CAM_EMM_EMM_BUF_144_reg                                                        0xB8011840
#define CAM_EMM_EMM_BUF_145_reg                                                        0xB8011844
#define CAM_EMM_EMM_BUF_146_reg                                                        0xB8011848
#define CAM_EMM_EMM_BUF_147_reg                                                        0xB801184C
#define CAM_EMM_EMM_BUF_148_reg                                                        0xB8011850
#define CAM_EMM_EMM_BUF_149_reg                                                        0xB8011854
#define CAM_EMM_EMM_BUF_150_reg                                                        0xB8011858
#define CAM_EMM_EMM_BUF_151_reg                                                        0xB801185C
#define CAM_EMM_EMM_BUF_152_reg                                                        0xB8011860
#define CAM_EMM_EMM_BUF_153_reg                                                        0xB8011864
#define CAM_EMM_EMM_BUF_154_reg                                                        0xB8011868
#define CAM_EMM_EMM_BUF_155_reg                                                        0xB801186C
#define CAM_EMM_EMM_BUF_156_reg                                                        0xB8011870
#define CAM_EMM_EMM_BUF_157_reg                                                        0xB8011874
#define CAM_EMM_EMM_BUF_158_reg                                                        0xB8011878
#define CAM_EMM_EMM_BUF_159_reg                                                        0xB801187C
#define CAM_EMM_EMM_BUF_160_reg                                                        0xB8011880
#define CAM_EMM_EMM_BUF_161_reg                                                        0xB8011884
#define CAM_EMM_EMM_BUF_162_reg                                                        0xB8011888
#define CAM_EMM_EMM_BUF_163_reg                                                        0xB801188C
#define CAM_EMM_EMM_BUF_164_reg                                                        0xB8011890
#define CAM_EMM_EMM_BUF_165_reg                                                        0xB8011894
#define CAM_EMM_EMM_BUF_166_reg                                                        0xB8011898
#define CAM_EMM_EMM_BUF_167_reg                                                        0xB801189C
#define CAM_EMM_EMM_BUF_168_reg                                                        0xB80118A0
#define CAM_EMM_EMM_BUF_169_reg                                                        0xB80118A4
#define CAM_EMM_EMM_BUF_170_reg                                                        0xB80118A8
#define CAM_EMM_EMM_BUF_171_reg                                                        0xB80118AC
#define CAM_EMM_EMM_BUF_172_reg                                                        0xB80118B0
#define CAM_EMM_EMM_BUF_173_reg                                                        0xB80118B4
#define CAM_EMM_EMM_BUF_174_reg                                                        0xB80118B8
#define CAM_EMM_EMM_BUF_175_reg                                                        0xB80118BC
#define CAM_EMM_EMM_BUF_176_reg                                                        0xB80118C0
#define CAM_EMM_EMM_BUF_177_reg                                                        0xB80118C4
#define CAM_EMM_EMM_BUF_178_reg                                                        0xB80118C8
#define CAM_EMM_EMM_BUF_179_reg                                                        0xB80118CC
#define CAM_EMM_EMM_BUF_180_reg                                                        0xB80118D0
#define CAM_EMM_EMM_BUF_181_reg                                                        0xB80118D4
#define CAM_EMM_EMM_BUF_182_reg                                                        0xB80118D8
#define CAM_EMM_EMM_BUF_183_reg                                                        0xB80118DC
#define CAM_EMM_EMM_BUF_184_reg                                                        0xB80118E0
#define CAM_EMM_EMM_BUF_185_reg                                                        0xB80118E4
#define CAM_EMM_EMM_BUF_186_reg                                                        0xB80118E8
#define CAM_EMM_EMM_BUF_187_reg                                                        0xB80118EC
#define CAM_EMM_EMM_BUF_188_reg                                                        0xB80118F0
#define CAM_EMM_EMM_BUF_189_reg                                                        0xB80118F4
#define CAM_EMM_EMM_BUF_190_reg                                                        0xB80118F8
#define CAM_EMM_EMM_BUF_191_reg                                                        0xB80118FC
#define CAM_EMM_EMM_BUF_192_reg                                                        0xB8011900
#define CAM_EMM_EMM_BUF_193_reg                                                        0xB8011904
#define CAM_EMM_EMM_BUF_194_reg                                                        0xB8011908
#define CAM_EMM_EMM_BUF_195_reg                                                        0xB801190C
#define CAM_EMM_EMM_BUF_196_reg                                                        0xB8011910
#define CAM_EMM_EMM_BUF_197_reg                                                        0xB8011914
#define CAM_EMM_EMM_BUF_198_reg                                                        0xB8011918
#define CAM_EMM_EMM_BUF_199_reg                                                        0xB801191C
#define CAM_EMM_EMM_BUF_200_reg                                                        0xB8011920
#define CAM_EMM_EMM_BUF_201_reg                                                        0xB8011924
#define CAM_EMM_EMM_BUF_202_reg                                                        0xB8011928
#define CAM_EMM_EMM_BUF_203_reg                                                        0xB801192C
#define CAM_EMM_EMM_BUF_204_reg                                                        0xB8011930
#define CAM_EMM_EMM_BUF_205_reg                                                        0xB8011934
#define CAM_EMM_EMM_BUF_206_reg                                                        0xB8011938
#define CAM_EMM_EMM_BUF_207_reg                                                        0xB801193C
#define CAM_EMM_EMM_BUF_208_reg                                                        0xB8011940
#define CAM_EMM_EMM_BUF_209_reg                                                        0xB8011944
#define CAM_EMM_EMM_BUF_210_reg                                                        0xB8011948
#define CAM_EMM_EMM_BUF_211_reg                                                        0xB801194C
#define CAM_EMM_EMM_BUF_212_reg                                                        0xB8011950
#define CAM_EMM_EMM_BUF_213_reg                                                        0xB8011954
#define CAM_EMM_EMM_BUF_214_reg                                                        0xB8011958
#define CAM_EMM_EMM_BUF_215_reg                                                        0xB801195C
#define CAM_EMM_EMM_BUF_216_reg                                                        0xB8011960
#define CAM_EMM_EMM_BUF_217_reg                                                        0xB8011964
#define CAM_EMM_EMM_BUF_218_reg                                                        0xB8011968
#define CAM_EMM_EMM_BUF_219_reg                                                        0xB801196C
#define CAM_EMM_EMM_BUF_220_reg                                                        0xB8011970
#define CAM_EMM_EMM_BUF_221_reg                                                        0xB8011974
#define CAM_EMM_EMM_BUF_222_reg                                                        0xB8011978
#define CAM_EMM_EMM_BUF_223_reg                                                        0xB801197C
#define CAM_EMM_EMM_BUF_224_reg                                                        0xB8011980
#define CAM_EMM_EMM_BUF_225_reg                                                        0xB8011984
#define CAM_EMM_EMM_BUF_226_reg                                                        0xB8011988
#define CAM_EMM_EMM_BUF_227_reg                                                        0xB801198C
#define CAM_EMM_EMM_BUF_228_reg                                                        0xB8011990
#define CAM_EMM_EMM_BUF_229_reg                                                        0xB8011994
#define CAM_EMM_EMM_BUF_230_reg                                                        0xB8011998
#define CAM_EMM_EMM_BUF_231_reg                                                        0xB801199C
#define CAM_EMM_EMM_BUF_232_reg                                                        0xB80119A0
#define CAM_EMM_EMM_BUF_233_reg                                                        0xB80119A4
#define CAM_EMM_EMM_BUF_234_reg                                                        0xB80119A8
#define CAM_EMM_EMM_BUF_235_reg                                                        0xB80119AC
#define CAM_EMM_EMM_BUF_236_reg                                                        0xB80119B0
#define CAM_EMM_EMM_BUF_237_reg                                                        0xB80119B4
#define CAM_EMM_EMM_BUF_238_reg                                                        0xB80119B8
#define CAM_EMM_EMM_BUF_239_reg                                                        0xB80119BC
#define CAM_EMM_EMM_BUF_240_reg                                                        0xB80119C0
#define CAM_EMM_EMM_BUF_241_reg                                                        0xB80119C4
#define CAM_EMM_EMM_BUF_242_reg                                                        0xB80119C8
#define CAM_EMM_EMM_BUF_243_reg                                                        0xB80119CC
#define CAM_EMM_EMM_BUF_244_reg                                                        0xB80119D0
#define CAM_EMM_EMM_BUF_245_reg                                                        0xB80119D4
#define CAM_EMM_EMM_BUF_246_reg                                                        0xB80119D8
#define CAM_EMM_EMM_BUF_247_reg                                                        0xB80119DC
#define CAM_EMM_EMM_BUF_248_reg                                                        0xB80119E0
#define CAM_EMM_EMM_BUF_249_reg                                                        0xB80119E4
#define CAM_EMM_EMM_BUF_250_reg                                                        0xB80119E8
#define CAM_EMM_EMM_BUF_251_reg                                                        0xB80119EC
#define CAM_EMM_EMM_BUF_252_reg                                                        0xB80119F0
#define CAM_EMM_EMM_BUF_253_reg                                                        0xB80119F4
#define CAM_EMM_EMM_BUF_254_reg                                                        0xB80119F8
#define CAM_EMM_EMM_BUF_255_reg                                                        0xB80119FC
#define CAM_EMM_EMM_BUF_256_reg                                                        0xB8011A00
#define CAM_EMM_EMM_BUF_257_reg                                                        0xB8011A04
#define CAM_EMM_EMM_BUF_258_reg                                                        0xB8011A08
#define CAM_EMM_EMM_BUF_259_reg                                                        0xB8011A0C
#define CAM_EMM_EMM_BUF_260_reg                                                        0xB8011A10
#define CAM_EMM_EMM_BUF_261_reg                                                        0xB8011A14
#define CAM_EMM_EMM_BUF_262_reg                                                        0xB8011A18
#define CAM_EMM_EMM_BUF_263_reg                                                        0xB8011A1C
#define CAM_EMM_EMM_BUF_264_reg                                                        0xB8011A20
#define CAM_EMM_EMM_BUF_265_reg                                                        0xB8011A24
#define CAM_EMM_EMM_BUF_266_reg                                                        0xB8011A28
#define CAM_EMM_EMM_BUF_267_reg                                                        0xB8011A2C
#define CAM_EMM_EMM_BUF_268_reg                                                        0xB8011A30
#define CAM_EMM_EMM_BUF_269_reg                                                        0xB8011A34
#define CAM_EMM_EMM_BUF_270_reg                                                        0xB8011A38
#define CAM_EMM_EMM_BUF_271_reg                                                        0xB8011A3C
#define CAM_EMM_EMM_BUF_272_reg                                                        0xB8011A40
#define CAM_EMM_EMM_BUF_273_reg                                                        0xB8011A44
#define CAM_EMM_EMM_BUF_274_reg                                                        0xB8011A48
#define CAM_EMM_EMM_BUF_275_reg                                                        0xB8011A4C
#define CAM_EMM_EMM_BUF_276_reg                                                        0xB8011A50
#define CAM_EMM_EMM_BUF_277_reg                                                        0xB8011A54
#define CAM_EMM_EMM_BUF_278_reg                                                        0xB8011A58
#define CAM_EMM_EMM_BUF_279_reg                                                        0xB8011A5C
#define CAM_EMM_EMM_BUF_280_reg                                                        0xB8011A60
#define CAM_EMM_EMM_BUF_281_reg                                                        0xB8011A64
#define CAM_EMM_EMM_BUF_282_reg                                                        0xB8011A68
#define CAM_EMM_EMM_BUF_283_reg                                                        0xB8011A6C
#define CAM_EMM_EMM_BUF_284_reg                                                        0xB8011A70
#define CAM_EMM_EMM_BUF_285_reg                                                        0xB8011A74
#define CAM_EMM_EMM_BUF_286_reg                                                        0xB8011A78
#define CAM_EMM_EMM_BUF_287_reg                                                        0xB8011A7C
#define CAM_EMM_EMM_BUF_288_reg                                                        0xB8011A80
#define CAM_EMM_EMM_BUF_289_reg                                                        0xB8011A84
#define CAM_EMM_EMM_BUF_290_reg                                                        0xB8011A88
#define CAM_EMM_EMM_BUF_291_reg                                                        0xB8011A8C
#define CAM_EMM_EMM_BUF_292_reg                                                        0xB8011A90
#define CAM_EMM_EMM_BUF_293_reg                                                        0xB8011A94
#define CAM_EMM_EMM_BUF_294_reg                                                        0xB8011A98
#define CAM_EMM_EMM_BUF_295_reg                                                        0xB8011A9C
#define CAM_EMM_EMM_BUF_296_reg                                                        0xB8011AA0
#define CAM_EMM_EMM_BUF_297_reg                                                        0xB8011AA4
#define CAM_EMM_EMM_BUF_298_reg                                                        0xB8011AA8
#define CAM_EMM_EMM_BUF_299_reg                                                        0xB8011AAC
#define CAM_EMM_EMM_BUF_300_reg                                                        0xB8011AB0
#define CAM_EMM_EMM_BUF_301_reg                                                        0xB8011AB4
#define CAM_EMM_EMM_BUF_302_reg                                                        0xB8011AB8
#define CAM_EMM_EMM_BUF_303_reg                                                        0xB8011ABC
#define CAM_EMM_EMM_BUF_304_reg                                                        0xB8011AC0
#define CAM_EMM_EMM_BUF_305_reg                                                        0xB8011AC4
#define CAM_EMM_EMM_BUF_306_reg                                                        0xB8011AC8
#define CAM_EMM_EMM_BUF_307_reg                                                        0xB8011ACC
#define CAM_EMM_EMM_BUF_308_reg                                                        0xB8011AD0
#define CAM_EMM_EMM_BUF_309_reg                                                        0xB8011AD4
#define CAM_EMM_EMM_BUF_310_reg                                                        0xB8011AD8
#define CAM_EMM_EMM_BUF_311_reg                                                        0xB8011ADC
#define CAM_EMM_EMM_BUF_312_reg                                                        0xB8011AE0
#define CAM_EMM_EMM_BUF_313_reg                                                        0xB8011AE4
#define CAM_EMM_EMM_BUF_314_reg                                                        0xB8011AE8
#define CAM_EMM_EMM_BUF_315_reg                                                        0xB8011AEC
#define CAM_EMM_EMM_BUF_316_reg                                                        0xB8011AF0
#define CAM_EMM_EMM_BUF_317_reg                                                        0xB8011AF4
#define CAM_EMM_EMM_BUF_318_reg                                                        0xB8011AF8
#define CAM_EMM_EMM_BUF_319_reg                                                        0xB8011AFC
#define CAM_EMM_EMM_BUF_320_reg                                                        0xB8011B00
#define CAM_EMM_EMM_BUF_321_reg                                                        0xB8011B04
#define CAM_EMM_EMM_BUF_322_reg                                                        0xB8011B08
#define CAM_EMM_EMM_BUF_323_reg                                                        0xB8011B0C
#define CAM_EMM_EMM_BUF_324_reg                                                        0xB8011B10
#define CAM_EMM_EMM_BUF_325_reg                                                        0xB8011B14
#define CAM_EMM_EMM_BUF_326_reg                                                        0xB8011B18
#define CAM_EMM_EMM_BUF_327_reg                                                        0xB8011B1C
#define CAM_EMM_EMM_BUF_328_reg                                                        0xB8011B20
#define CAM_EMM_EMM_BUF_329_reg                                                        0xB8011B24
#define CAM_EMM_EMM_BUF_330_reg                                                        0xB8011B28
#define CAM_EMM_EMM_BUF_331_reg                                                        0xB8011B2C
#define CAM_EMM_EMM_BUF_332_reg                                                        0xB8011B30
#define CAM_EMM_EMM_BUF_333_reg                                                        0xB8011B34
#define CAM_EMM_EMM_BUF_334_reg                                                        0xB8011B38
#define CAM_EMM_EMM_BUF_335_reg                                                        0xB8011B3C
#define CAM_EMM_EMM_BUF_336_reg                                                        0xB8011B40
#define CAM_EMM_EMM_BUF_337_reg                                                        0xB8011B44
#define CAM_EMM_EMM_BUF_338_reg                                                        0xB8011B48
#define CAM_EMM_EMM_BUF_339_reg                                                        0xB8011B4C
#define CAM_EMM_EMM_BUF_340_reg                                                        0xB8011B50
#define CAM_EMM_EMM_BUF_341_reg                                                        0xB8011B54
#define CAM_EMM_EMM_BUF_342_reg                                                        0xB8011B58
#define CAM_EMM_EMM_BUF_343_reg                                                        0xB8011B5C
#define CAM_EMM_EMM_BUF_344_reg                                                        0xB8011B60
#define CAM_EMM_EMM_BUF_345_reg                                                        0xB8011B64
#define CAM_EMM_EMM_BUF_346_reg                                                        0xB8011B68
#define CAM_EMM_EMM_BUF_347_reg                                                        0xB8011B6C
#define CAM_EMM_EMM_BUF_348_reg                                                        0xB8011B70
#define CAM_EMM_EMM_BUF_349_reg                                                        0xB8011B74
#define CAM_EMM_EMM_BUF_350_reg                                                        0xB8011B78
#define CAM_EMM_EMM_BUF_351_reg                                                        0xB8011B7C
#define CAM_EMM_EMM_BUF_352_reg                                                        0xB8011B80
#define CAM_EMM_EMM_BUF_353_reg                                                        0xB8011B84
#define CAM_EMM_EMM_BUF_354_reg                                                        0xB8011B88
#define CAM_EMM_EMM_BUF_355_reg                                                        0xB8011B8C
#define CAM_EMM_EMM_BUF_356_reg                                                        0xB8011B90
#define CAM_EMM_EMM_BUF_357_reg                                                        0xB8011B94
#define CAM_EMM_EMM_BUF_358_reg                                                        0xB8011B98
#define CAM_EMM_EMM_BUF_359_reg                                                        0xB8011B9C
#define CAM_EMM_EMM_BUF_360_reg                                                        0xB8011BA0
#define CAM_EMM_EMM_BUF_361_reg                                                        0xB8011BA4
#define CAM_EMM_EMM_BUF_362_reg                                                        0xB8011BA8
#define CAM_EMM_EMM_BUF_363_reg                                                        0xB8011BAC
#define CAM_EMM_EMM_BUF_364_reg                                                        0xB8011BB0
#define CAM_EMM_EMM_BUF_365_reg                                                        0xB8011BB4
#define CAM_EMM_EMM_BUF_366_reg                                                        0xB8011BB8
#define CAM_EMM_EMM_BUF_367_reg                                                        0xB8011BBC
#define CAM_EMM_EMM_BUF_368_reg                                                        0xB8011BC0
#define CAM_EMM_EMM_BUF_369_reg                                                        0xB8011BC4
#define CAM_EMM_EMM_BUF_370_reg                                                        0xB8011BC8
#define CAM_EMM_EMM_BUF_371_reg                                                        0xB8011BCC
#define CAM_EMM_EMM_BUF_372_reg                                                        0xB8011BD0
#define CAM_EMM_EMM_BUF_373_reg                                                        0xB8011BD4
#define CAM_EMM_EMM_BUF_374_reg                                                        0xB8011BD8
#define CAM_EMM_EMM_BUF_375_reg                                                        0xB8011BDC
#define CAM_EMM_EMM_BUF_376_reg                                                        0xB8011BE0
#define CAM_EMM_EMM_BUF_377_reg                                                        0xB8011BE4
#define CAM_EMM_EMM_BUF_378_reg                                                        0xB8011BE8
#define CAM_EMM_EMM_BUF_379_reg                                                        0xB8011BEC
#define CAM_EMM_EMM_BUF_380_reg                                                        0xB8011BF0
#define CAM_EMM_EMM_BUF_381_reg                                                        0xB8011BF4
#define CAM_EMM_EMM_BUF_382_reg                                                        0xB8011BF8
#define CAM_EMM_EMM_BUF_383_reg                                                        0xB8011BFC
#define CAM_EMM_EMM_BUF_384_reg                                                        0xB8011C00
#define CAM_EMM_EMM_BUF_385_reg                                                        0xB8011C04
#define CAM_EMM_EMM_BUF_386_reg                                                        0xB8011C08
#define CAM_EMM_EMM_BUF_387_reg                                                        0xB8011C0C
#define CAM_EMM_EMM_BUF_388_reg                                                        0xB8011C10
#define CAM_EMM_EMM_BUF_389_reg                                                        0xB8011C14
#define CAM_EMM_EMM_BUF_390_reg                                                        0xB8011C18
#define CAM_EMM_EMM_BUF_391_reg                                                        0xB8011C1C
#define CAM_EMM_EMM_BUF_392_reg                                                        0xB8011C20
#define CAM_EMM_EMM_BUF_393_reg                                                        0xB8011C24
#define CAM_EMM_EMM_BUF_394_reg                                                        0xB8011C28
#define CAM_EMM_EMM_BUF_395_reg                                                        0xB8011C2C
#define CAM_EMM_EMM_BUF_396_reg                                                        0xB8011C30
#define CAM_EMM_EMM_BUF_397_reg                                                        0xB8011C34
#define CAM_EMM_EMM_BUF_398_reg                                                        0xB8011C38
#define CAM_EMM_EMM_BUF_399_reg                                                        0xB8011C3C
#define CAM_EMM_EMM_BUF_400_reg                                                        0xB8011C40
#define CAM_EMM_EMM_BUF_401_reg                                                        0xB8011C44
#define CAM_EMM_EMM_BUF_402_reg                                                        0xB8011C48
#define CAM_EMM_EMM_BUF_403_reg                                                        0xB8011C4C
#define CAM_EMM_EMM_BUF_404_reg                                                        0xB8011C50
#define CAM_EMM_EMM_BUF_405_reg                                                        0xB8011C54
#define CAM_EMM_EMM_BUF_406_reg                                                        0xB8011C58
#define CAM_EMM_EMM_BUF_407_reg                                                        0xB8011C5C
#define CAM_EMM_EMM_BUF_408_reg                                                        0xB8011C60
#define CAM_EMM_EMM_BUF_409_reg                                                        0xB8011C64
#define CAM_EMM_EMM_BUF_410_reg                                                        0xB8011C68
#define CAM_EMM_EMM_BUF_411_reg                                                        0xB8011C6C
#define CAM_EMM_EMM_BUF_412_reg                                                        0xB8011C70
#define CAM_EMM_EMM_BUF_413_reg                                                        0xB8011C74
#define CAM_EMM_EMM_BUF_414_reg                                                        0xB8011C78
#define CAM_EMM_EMM_BUF_415_reg                                                        0xB8011C7C
#define CAM_EMM_EMM_BUF_416_reg                                                        0xB8011C80
#define CAM_EMM_EMM_BUF_417_reg                                                        0xB8011C84
#define CAM_EMM_EMM_BUF_418_reg                                                        0xB8011C88
#define CAM_EMM_EMM_BUF_419_reg                                                        0xB8011C8C
#define CAM_EMM_EMM_BUF_420_reg                                                        0xB8011C90
#define CAM_EMM_EMM_BUF_421_reg                                                        0xB8011C94
#define CAM_EMM_EMM_BUF_422_reg                                                        0xB8011C98
#define CAM_EMM_EMM_BUF_423_reg                                                        0xB8011C9C
#define CAM_EMM_EMM_BUF_424_reg                                                        0xB8011CA0
#define CAM_EMM_EMM_BUF_425_reg                                                        0xB8011CA4
#define CAM_EMM_EMM_BUF_426_reg                                                        0xB8011CA8
#define CAM_EMM_EMM_BUF_427_reg                                                        0xB8011CAC
#define CAM_EMM_EMM_BUF_428_reg                                                        0xB8011CB0
#define CAM_EMM_EMM_BUF_429_reg                                                        0xB8011CB4
#define CAM_EMM_EMM_BUF_430_reg                                                        0xB8011CB8
#define CAM_EMM_EMM_BUF_431_reg                                                        0xB8011CBC
#define CAM_EMM_EMM_BUF_432_reg                                                        0xB8011CC0
#define CAM_EMM_EMM_BUF_433_reg                                                        0xB8011CC4
#define CAM_EMM_EMM_BUF_434_reg                                                        0xB8011CC8
#define CAM_EMM_EMM_BUF_435_reg                                                        0xB8011CCC
#define CAM_EMM_EMM_BUF_436_reg                                                        0xB8011CD0
#define CAM_EMM_EMM_BUF_437_reg                                                        0xB8011CD4
#define CAM_EMM_EMM_BUF_438_reg                                                        0xB8011CD8
#define CAM_EMM_EMM_BUF_439_reg                                                        0xB8011CDC
#define CAM_EMM_EMM_BUF_440_reg                                                        0xB8011CE0
#define CAM_EMM_EMM_BUF_441_reg                                                        0xB8011CE4
#define CAM_EMM_EMM_BUF_442_reg                                                        0xB8011CE8
#define CAM_EMM_EMM_BUF_443_reg                                                        0xB8011CEC
#define CAM_EMM_EMM_BUF_444_reg                                                        0xB8011CF0
#define CAM_EMM_EMM_BUF_445_reg                                                        0xB8011CF4
#define CAM_EMM_EMM_BUF_446_reg                                                        0xB8011CF8
#define CAM_EMM_EMM_BUF_447_reg                                                        0xB8011CFC
#define CAM_EMM_EMM_BUF_448_reg                                                        0xB8011D00
#define CAM_EMM_EMM_BUF_449_reg                                                        0xB8011D04
#define CAM_EMM_EMM_BUF_450_reg                                                        0xB8011D08
#define CAM_EMM_EMM_BUF_451_reg                                                        0xB8011D0C
#define CAM_EMM_EMM_BUF_452_reg                                                        0xB8011D10
#define CAM_EMM_EMM_BUF_453_reg                                                        0xB8011D14
#define CAM_EMM_EMM_BUF_454_reg                                                        0xB8011D18
#define CAM_EMM_EMM_BUF_455_reg                                                        0xB8011D1C
#define CAM_EMM_EMM_BUF_456_reg                                                        0xB8011D20
#define CAM_EMM_EMM_BUF_457_reg                                                        0xB8011D24
#define CAM_EMM_EMM_BUF_458_reg                                                        0xB8011D28
#define CAM_EMM_EMM_BUF_459_reg                                                        0xB8011D2C
#define CAM_EMM_EMM_BUF_460_reg                                                        0xB8011D30
#define CAM_EMM_EMM_BUF_461_reg                                                        0xB8011D34
#define CAM_EMM_EMM_BUF_462_reg                                                        0xB8011D38
#define CAM_EMM_EMM_BUF_463_reg                                                        0xB8011D3C
#define CAM_EMM_EMM_BUF_464_reg                                                        0xB8011D40
#define CAM_EMM_EMM_BUF_465_reg                                                        0xB8011D44
#define CAM_EMM_EMM_BUF_466_reg                                                        0xB8011D48
#define CAM_EMM_EMM_BUF_467_reg                                                        0xB8011D4C
#define CAM_EMM_EMM_BUF_468_reg                                                        0xB8011D50
#define CAM_EMM_EMM_BUF_469_reg                                                        0xB8011D54
#define CAM_EMM_EMM_BUF_470_reg                                                        0xB8011D58
#define CAM_EMM_EMM_BUF_471_reg                                                        0xB8011D5C
#define CAM_EMM_EMM_BUF_472_reg                                                        0xB8011D60
#define CAM_EMM_EMM_BUF_473_reg                                                        0xB8011D64
#define CAM_EMM_EMM_BUF_474_reg                                                        0xB8011D68
#define CAM_EMM_EMM_BUF_475_reg                                                        0xB8011D6C
#define CAM_EMM_EMM_BUF_476_reg                                                        0xB8011D70
#define CAM_EMM_EMM_BUF_477_reg                                                        0xB8011D74
#define CAM_EMM_EMM_BUF_478_reg                                                        0xB8011D78
#define CAM_EMM_EMM_BUF_479_reg                                                        0xB8011D7C
#define CAM_EMM_EMM_BUF_480_reg                                                        0xB8011D80
#define CAM_EMM_EMM_BUF_481_reg                                                        0xB8011D84
#define CAM_EMM_EMM_BUF_482_reg                                                        0xB8011D88
#define CAM_EMM_EMM_BUF_483_reg                                                        0xB8011D8C
#define CAM_EMM_EMM_BUF_484_reg                                                        0xB8011D90
#define CAM_EMM_EMM_BUF_485_reg                                                        0xB8011D94
#define CAM_EMM_EMM_BUF_486_reg                                                        0xB8011D98
#define CAM_EMM_EMM_BUF_487_reg                                                        0xB8011D9C
#define CAM_EMM_EMM_BUF_488_reg                                                        0xB8011DA0
#define CAM_EMM_EMM_BUF_489_reg                                                        0xB8011DA4
#define CAM_EMM_EMM_BUF_490_reg                                                        0xB8011DA8
#define CAM_EMM_EMM_BUF_491_reg                                                        0xB8011DAC
#define CAM_EMM_EMM_BUF_492_reg                                                        0xB8011DB0
#define CAM_EMM_EMM_BUF_493_reg                                                        0xB8011DB4
#define CAM_EMM_EMM_BUF_494_reg                                                        0xB8011DB8
#define CAM_EMM_EMM_BUF_495_reg                                                        0xB8011DBC
#define CAM_EMM_EMM_BUF_496_reg                                                        0xB8011DC0
#define CAM_EMM_EMM_BUF_497_reg                                                        0xB8011DC4
#define CAM_EMM_EMM_BUF_498_reg                                                        0xB8011DC8
#define CAM_EMM_EMM_BUF_499_reg                                                        0xB8011DCC
#define CAM_EMM_EMM_BUF_500_reg                                                        0xB8011DD0
#define CAM_EMM_EMM_BUF_501_reg                                                        0xB8011DD4
#define CAM_EMM_EMM_BUF_502_reg                                                        0xB8011DD8
#define CAM_EMM_EMM_BUF_503_reg                                                        0xB8011DDC
#define CAM_EMM_EMM_BUF_504_reg                                                        0xB8011DE0
#define CAM_EMM_EMM_BUF_505_reg                                                        0xB8011DE4
#define CAM_EMM_EMM_BUF_506_reg                                                        0xB8011DE8
#define CAM_EMM_EMM_BUF_507_reg                                                        0xB8011DEC
#define CAM_EMM_EMM_BUF_508_reg                                                        0xB8011DF0
#define CAM_EMM_EMM_BUF_509_reg                                                        0xB8011DF4
#define CAM_EMM_EMM_BUF_510_reg                                                        0xB8011DF8
#define CAM_EMM_EMM_BUF_511_reg                                                        0xB8011DFC
#define CAM_EMM_EMM_BUF_512_reg                                                        0xB8011E00
#define CAM_EMM_EMM_BUF_513_reg                                                        0xB8011E04
#define CAM_EMM_EMM_BUF_514_reg                                                        0xB8011E08
#define CAM_EMM_EMM_BUF_515_reg                                                        0xB8011E0C
#define CAM_EMM_EMM_BUF_516_reg                                                        0xB8011E10
#define CAM_EMM_EMM_BUF_517_reg                                                        0xB8011E14
#define CAM_EMM_EMM_BUF_518_reg                                                        0xB8011E18
#define CAM_EMM_EMM_BUF_519_reg                                                        0xB8011E1C
#define CAM_EMM_EMM_BUF_520_reg                                                        0xB8011E20
#define CAM_EMM_EMM_BUF_521_reg                                                        0xB8011E24
#define CAM_EMM_EMM_BUF_522_reg                                                        0xB8011E28
#define CAM_EMM_EMM_BUF_523_reg                                                        0xB8011E2C
#define CAM_EMM_EMM_BUF_524_reg                                                        0xB8011E30
#define CAM_EMM_EMM_BUF_525_reg                                                        0xB8011E34
#define CAM_EMM_EMM_BUF_526_reg                                                        0xB8011E38
#define CAM_EMM_EMM_BUF_527_reg                                                        0xB8011E3C
#define CAM_EMM_EMM_BUF_528_reg                                                        0xB8011E40
#define CAM_EMM_EMM_BUF_529_reg                                                        0xB8011E44
#define CAM_EMM_EMM_BUF_530_reg                                                        0xB8011E48
#define CAM_EMM_EMM_BUF_531_reg                                                        0xB8011E4C
#define CAM_EMM_EMM_BUF_532_reg                                                        0xB8011E50
#define CAM_EMM_EMM_BUF_533_reg                                                        0xB8011E54
#define CAM_EMM_EMM_BUF_534_reg                                                        0xB8011E58
#define CAM_EMM_EMM_BUF_535_reg                                                        0xB8011E5C
#define CAM_EMM_EMM_BUF_536_reg                                                        0xB8011E60
#define CAM_EMM_EMM_BUF_537_reg                                                        0xB8011E64
#define CAM_EMM_EMM_BUF_538_reg                                                        0xB8011E68
#define CAM_EMM_EMM_BUF_539_reg                                                        0xB8011E6C
#define CAM_EMM_EMM_BUF_540_reg                                                        0xB8011E70
#define CAM_EMM_EMM_BUF_541_reg                                                        0xB8011E74
#define CAM_EMM_EMM_BUF_542_reg                                                        0xB8011E78
#define CAM_EMM_EMM_BUF_543_reg                                                        0xB8011E7C
#define CAM_EMM_EMM_BUF_544_reg                                                        0xB8011E80
#define CAM_EMM_EMM_BUF_545_reg                                                        0xB8011E84
#define CAM_EMM_EMM_BUF_546_reg                                                        0xB8011E88
#define CAM_EMM_EMM_BUF_547_reg                                                        0xB8011E8C
#define CAM_EMM_EMM_BUF_548_reg                                                        0xB8011E90
#define CAM_EMM_EMM_BUF_549_reg                                                        0xB8011E94
#define CAM_EMM_EMM_BUF_550_reg                                                        0xB8011E98
#define CAM_EMM_EMM_BUF_551_reg                                                        0xB8011E9C
#define CAM_EMM_EMM_BUF_552_reg                                                        0xB8011EA0
#define CAM_EMM_EMM_BUF_553_reg                                                        0xB8011EA4
#define CAM_EMM_EMM_BUF_554_reg                                                        0xB8011EA8
#define CAM_EMM_EMM_BUF_555_reg                                                        0xB8011EAC
#define CAM_EMM_EMM_BUF_556_reg                                                        0xB8011EB0
#define CAM_EMM_EMM_BUF_557_reg                                                        0xB8011EB4
#define CAM_EMM_EMM_BUF_558_reg                                                        0xB8011EB8
#define CAM_EMM_EMM_BUF_559_reg                                                        0xB8011EBC
#define CAM_EMM_EMM_BUF_560_reg                                                        0xB8011EC0
#define CAM_EMM_EMM_BUF_561_reg                                                        0xB8011EC4
#define CAM_EMM_EMM_BUF_562_reg                                                        0xB8011EC8
#define CAM_EMM_EMM_BUF_563_reg                                                        0xB8011ECC
#define CAM_EMM_EMM_BUF_564_reg                                                        0xB8011ED0
#define CAM_EMM_EMM_BUF_565_reg                                                        0xB8011ED4
#define CAM_EMM_EMM_BUF_566_reg                                                        0xB8011ED8
#define CAM_EMM_EMM_BUF_567_reg                                                        0xB8011EDC
#define CAM_EMM_EMM_BUF_568_reg                                                        0xB8011EE0
#define CAM_EMM_EMM_BUF_569_reg                                                        0xB8011EE4
#define CAM_EMM_EMM_BUF_570_reg                                                        0xB8011EE8
#define CAM_EMM_EMM_BUF_571_reg                                                        0xB8011EEC
#define CAM_EMM_EMM_BUF_572_reg                                                        0xB8011EF0
#define CAM_EMM_EMM_BUF_573_reg                                                        0xB8011EF4
#define CAM_EMM_EMM_BUF_574_reg                                                        0xB8011EF8
#define CAM_EMM_EMM_BUF_575_reg                                                        0xB8011EFC
#define CAM_EMM_EMM_BUF_576_reg                                                        0xB8011F00
#define CAM_EMM_EMM_BUF_577_reg                                                        0xB8011F04
#define CAM_EMM_EMM_BUF_578_reg                                                        0xB8011F08
#define CAM_EMM_EMM_BUF_579_reg                                                        0xB8011F0C
#define CAM_EMM_EMM_BUF_580_reg                                                        0xB8011F10
#define CAM_EMM_EMM_BUF_581_reg                                                        0xB8011F14
#define CAM_EMM_EMM_BUF_582_reg                                                        0xB8011F18
#define CAM_EMM_EMM_BUF_583_reg                                                        0xB8011F1C
#define CAM_EMM_EMM_BUF_584_reg                                                        0xB8011F20
#define CAM_EMM_EMM_BUF_585_reg                                                        0xB8011F24
#define CAM_EMM_EMM_BUF_586_reg                                                        0xB8011F28
#define CAM_EMM_EMM_BUF_587_reg                                                        0xB8011F2C
#define CAM_EMM_EMM_BUF_588_reg                                                        0xB8011F30
#define CAM_EMM_EMM_BUF_589_reg                                                        0xB8011F34
#define CAM_EMM_EMM_BUF_590_reg                                                        0xB8011F38
#define CAM_EMM_EMM_BUF_591_reg                                                        0xB8011F3C
#define CAM_EMM_EMM_BUF_592_reg                                                        0xB8011F40
#define CAM_EMM_EMM_BUF_593_reg                                                        0xB8011F44
#define CAM_EMM_EMM_BUF_594_reg                                                        0xB8011F48
#define CAM_EMM_EMM_BUF_595_reg                                                        0xB8011F4C
#define CAM_EMM_EMM_BUF_596_reg                                                        0xB8011F50
#define CAM_EMM_EMM_BUF_597_reg                                                        0xB8011F54
#define CAM_EMM_EMM_BUF_598_reg                                                        0xB8011F58
#define CAM_EMM_EMM_BUF_599_reg                                                        0xB8011F5C
#define CAM_EMM_EMM_BUF_600_reg                                                        0xB8011F60
#define CAM_EMM_EMM_BUF_601_reg                                                        0xB8011F64
#define CAM_EMM_EMM_BUF_602_reg                                                        0xB8011F68
#define CAM_EMM_EMM_BUF_603_reg                                                        0xB8011F6C
#define CAM_EMM_EMM_BUF_604_reg                                                        0xB8011F70
#define CAM_EMM_EMM_BUF_605_reg                                                        0xB8011F74
#define CAM_EMM_EMM_BUF_606_reg                                                        0xB8011F78
#define CAM_EMM_EMM_BUF_607_reg                                                        0xB8011F7C
#define CAM_EMM_EMM_BUF_608_reg                                                        0xB8011F80
#define CAM_EMM_EMM_BUF_609_reg                                                        0xB8011F84
#define CAM_EMM_EMM_BUF_610_reg                                                        0xB8011F88
#define CAM_EMM_EMM_BUF_611_reg                                                        0xB8011F8C
#define CAM_EMM_EMM_BUF_612_reg                                                        0xB8011F90
#define CAM_EMM_EMM_BUF_613_reg                                                        0xB8011F94
#define CAM_EMM_EMM_BUF_614_reg                                                        0xB8011F98
#define CAM_EMM_EMM_BUF_615_reg                                                        0xB8011F9C
#define CAM_EMM_EMM_BUF_616_reg                                                        0xB8011FA0
#define CAM_EMM_EMM_BUF_617_reg                                                        0xB8011FA4
#define CAM_EMM_EMM_BUF_618_reg                                                        0xB8011FA8
#define CAM_EMM_EMM_BUF_619_reg                                                        0xB8011FAC
#define CAM_EMM_EMM_BUF_620_reg                                                        0xB8011FB0
#define CAM_EMM_EMM_BUF_621_reg                                                        0xB8011FB4
#define CAM_EMM_EMM_BUF_622_reg                                                        0xB8011FB8
#define CAM_EMM_EMM_BUF_623_reg                                                        0xB8011FBC
#define CAM_EMM_EMM_BUF_624_reg                                                        0xB8011FC0
#define CAM_EMM_EMM_BUF_625_reg                                                        0xB8011FC4
#define CAM_EMM_EMM_BUF_626_reg                                                        0xB8011FC8
#define CAM_EMM_EMM_BUF_627_reg                                                        0xB8011FCC
#define CAM_EMM_EMM_BUF_628_reg                                                        0xB8011FD0
#define CAM_EMM_EMM_BUF_629_reg                                                        0xB8011FD4
#define CAM_EMM_EMM_BUF_630_reg                                                        0xB8011FD8
#define CAM_EMM_EMM_BUF_631_reg                                                        0xB8011FDC
#define CAM_EMM_EMM_BUF_632_reg                                                        0xB8011FE0
#define CAM_EMM_EMM_BUF_633_reg                                                        0xB8011FE4
#define CAM_EMM_EMM_BUF_634_reg                                                        0xB8011FE8
#define CAM_EMM_EMM_BUF_635_reg                                                        0xB8011FEC
#define CAM_EMM_EMM_BUF_636_reg                                                        0xB8011FF0
#define CAM_EMM_EMM_BUF_637_reg                                                        0xB8011FF4
#define CAM_EMM_EMM_BUF_638_reg                                                        0xB8011FF8
#define CAM_EMM_EMM_BUF_639_reg                                                        0xB8011FFC
#define set_CAM_EMM_EMM_BUF_0_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_0_reg)=data)
#define set_CAM_EMM_EMM_BUF_1_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_1_reg)=data)
#define set_CAM_EMM_EMM_BUF_2_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_2_reg)=data)
#define set_CAM_EMM_EMM_BUF_3_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_3_reg)=data)
#define set_CAM_EMM_EMM_BUF_4_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_4_reg)=data)
#define set_CAM_EMM_EMM_BUF_5_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_5_reg)=data)
#define set_CAM_EMM_EMM_BUF_6_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_6_reg)=data)
#define set_CAM_EMM_EMM_BUF_7_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_7_reg)=data)
#define set_CAM_EMM_EMM_BUF_8_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_8_reg)=data)
#define set_CAM_EMM_EMM_BUF_9_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_9_reg)=data)
#define set_CAM_EMM_EMM_BUF_10_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_10_reg)=data)
#define set_CAM_EMM_EMM_BUF_11_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_11_reg)=data)
#define set_CAM_EMM_EMM_BUF_12_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_12_reg)=data)
#define set_CAM_EMM_EMM_BUF_13_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_13_reg)=data)
#define set_CAM_EMM_EMM_BUF_14_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_14_reg)=data)
#define set_CAM_EMM_EMM_BUF_15_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_15_reg)=data)
#define set_CAM_EMM_EMM_BUF_16_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_16_reg)=data)
#define set_CAM_EMM_EMM_BUF_17_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_17_reg)=data)
#define set_CAM_EMM_EMM_BUF_18_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_18_reg)=data)
#define set_CAM_EMM_EMM_BUF_19_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_19_reg)=data)
#define set_CAM_EMM_EMM_BUF_20_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_20_reg)=data)
#define set_CAM_EMM_EMM_BUF_21_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_21_reg)=data)
#define set_CAM_EMM_EMM_BUF_22_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_22_reg)=data)
#define set_CAM_EMM_EMM_BUF_23_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_23_reg)=data)
#define set_CAM_EMM_EMM_BUF_24_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_24_reg)=data)
#define set_CAM_EMM_EMM_BUF_25_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_25_reg)=data)
#define set_CAM_EMM_EMM_BUF_26_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_26_reg)=data)
#define set_CAM_EMM_EMM_BUF_27_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_27_reg)=data)
#define set_CAM_EMM_EMM_BUF_28_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_28_reg)=data)
#define set_CAM_EMM_EMM_BUF_29_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_29_reg)=data)
#define set_CAM_EMM_EMM_BUF_30_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_30_reg)=data)
#define set_CAM_EMM_EMM_BUF_31_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_31_reg)=data)
#define set_CAM_EMM_EMM_BUF_32_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_32_reg)=data)
#define set_CAM_EMM_EMM_BUF_33_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_33_reg)=data)
#define set_CAM_EMM_EMM_BUF_34_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_34_reg)=data)
#define set_CAM_EMM_EMM_BUF_35_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_35_reg)=data)
#define set_CAM_EMM_EMM_BUF_36_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_36_reg)=data)
#define set_CAM_EMM_EMM_BUF_37_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_37_reg)=data)
#define set_CAM_EMM_EMM_BUF_38_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_38_reg)=data)
#define set_CAM_EMM_EMM_BUF_39_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_39_reg)=data)
#define set_CAM_EMM_EMM_BUF_40_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_40_reg)=data)
#define set_CAM_EMM_EMM_BUF_41_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_41_reg)=data)
#define set_CAM_EMM_EMM_BUF_42_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_42_reg)=data)
#define set_CAM_EMM_EMM_BUF_43_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_43_reg)=data)
#define set_CAM_EMM_EMM_BUF_44_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_44_reg)=data)
#define set_CAM_EMM_EMM_BUF_45_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_45_reg)=data)
#define set_CAM_EMM_EMM_BUF_46_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_46_reg)=data)
#define set_CAM_EMM_EMM_BUF_47_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_47_reg)=data)
#define set_CAM_EMM_EMM_BUF_48_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_48_reg)=data)
#define set_CAM_EMM_EMM_BUF_49_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_49_reg)=data)
#define set_CAM_EMM_EMM_BUF_50_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_50_reg)=data)
#define set_CAM_EMM_EMM_BUF_51_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_51_reg)=data)
#define set_CAM_EMM_EMM_BUF_52_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_52_reg)=data)
#define set_CAM_EMM_EMM_BUF_53_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_53_reg)=data)
#define set_CAM_EMM_EMM_BUF_54_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_54_reg)=data)
#define set_CAM_EMM_EMM_BUF_55_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_55_reg)=data)
#define set_CAM_EMM_EMM_BUF_56_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_56_reg)=data)
#define set_CAM_EMM_EMM_BUF_57_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_57_reg)=data)
#define set_CAM_EMM_EMM_BUF_58_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_58_reg)=data)
#define set_CAM_EMM_EMM_BUF_59_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_59_reg)=data)
#define set_CAM_EMM_EMM_BUF_60_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_60_reg)=data)
#define set_CAM_EMM_EMM_BUF_61_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_61_reg)=data)
#define set_CAM_EMM_EMM_BUF_62_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_62_reg)=data)
#define set_CAM_EMM_EMM_BUF_63_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_63_reg)=data)
#define set_CAM_EMM_EMM_BUF_64_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_64_reg)=data)
#define set_CAM_EMM_EMM_BUF_65_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_65_reg)=data)
#define set_CAM_EMM_EMM_BUF_66_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_66_reg)=data)
#define set_CAM_EMM_EMM_BUF_67_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_67_reg)=data)
#define set_CAM_EMM_EMM_BUF_68_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_68_reg)=data)
#define set_CAM_EMM_EMM_BUF_69_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_69_reg)=data)
#define set_CAM_EMM_EMM_BUF_70_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_70_reg)=data)
#define set_CAM_EMM_EMM_BUF_71_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_71_reg)=data)
#define set_CAM_EMM_EMM_BUF_72_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_72_reg)=data)
#define set_CAM_EMM_EMM_BUF_73_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_73_reg)=data)
#define set_CAM_EMM_EMM_BUF_74_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_74_reg)=data)
#define set_CAM_EMM_EMM_BUF_75_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_75_reg)=data)
#define set_CAM_EMM_EMM_BUF_76_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_76_reg)=data)
#define set_CAM_EMM_EMM_BUF_77_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_77_reg)=data)
#define set_CAM_EMM_EMM_BUF_78_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_78_reg)=data)
#define set_CAM_EMM_EMM_BUF_79_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_79_reg)=data)
#define set_CAM_EMM_EMM_BUF_80_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_80_reg)=data)
#define set_CAM_EMM_EMM_BUF_81_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_81_reg)=data)
#define set_CAM_EMM_EMM_BUF_82_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_82_reg)=data)
#define set_CAM_EMM_EMM_BUF_83_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_83_reg)=data)
#define set_CAM_EMM_EMM_BUF_84_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_84_reg)=data)
#define set_CAM_EMM_EMM_BUF_85_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_85_reg)=data)
#define set_CAM_EMM_EMM_BUF_86_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_86_reg)=data)
#define set_CAM_EMM_EMM_BUF_87_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_87_reg)=data)
#define set_CAM_EMM_EMM_BUF_88_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_88_reg)=data)
#define set_CAM_EMM_EMM_BUF_89_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_89_reg)=data)
#define set_CAM_EMM_EMM_BUF_90_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_90_reg)=data)
#define set_CAM_EMM_EMM_BUF_91_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_91_reg)=data)
#define set_CAM_EMM_EMM_BUF_92_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_92_reg)=data)
#define set_CAM_EMM_EMM_BUF_93_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_93_reg)=data)
#define set_CAM_EMM_EMM_BUF_94_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_94_reg)=data)
#define set_CAM_EMM_EMM_BUF_95_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_95_reg)=data)
#define set_CAM_EMM_EMM_BUF_96_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_96_reg)=data)
#define set_CAM_EMM_EMM_BUF_97_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_97_reg)=data)
#define set_CAM_EMM_EMM_BUF_98_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_98_reg)=data)
#define set_CAM_EMM_EMM_BUF_99_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_99_reg)=data)
#define set_CAM_EMM_EMM_BUF_100_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_100_reg)=data)
#define set_CAM_EMM_EMM_BUF_101_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_101_reg)=data)
#define set_CAM_EMM_EMM_BUF_102_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_102_reg)=data)
#define set_CAM_EMM_EMM_BUF_103_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_103_reg)=data)
#define set_CAM_EMM_EMM_BUF_104_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_104_reg)=data)
#define set_CAM_EMM_EMM_BUF_105_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_105_reg)=data)
#define set_CAM_EMM_EMM_BUF_106_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_106_reg)=data)
#define set_CAM_EMM_EMM_BUF_107_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_107_reg)=data)
#define set_CAM_EMM_EMM_BUF_108_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_108_reg)=data)
#define set_CAM_EMM_EMM_BUF_109_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_109_reg)=data)
#define set_CAM_EMM_EMM_BUF_110_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_110_reg)=data)
#define set_CAM_EMM_EMM_BUF_111_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_111_reg)=data)
#define set_CAM_EMM_EMM_BUF_112_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_112_reg)=data)
#define set_CAM_EMM_EMM_BUF_113_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_113_reg)=data)
#define set_CAM_EMM_EMM_BUF_114_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_114_reg)=data)
#define set_CAM_EMM_EMM_BUF_115_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_115_reg)=data)
#define set_CAM_EMM_EMM_BUF_116_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_116_reg)=data)
#define set_CAM_EMM_EMM_BUF_117_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_117_reg)=data)
#define set_CAM_EMM_EMM_BUF_118_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_118_reg)=data)
#define set_CAM_EMM_EMM_BUF_119_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_119_reg)=data)
#define set_CAM_EMM_EMM_BUF_120_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_120_reg)=data)
#define set_CAM_EMM_EMM_BUF_121_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_121_reg)=data)
#define set_CAM_EMM_EMM_BUF_122_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_122_reg)=data)
#define set_CAM_EMM_EMM_BUF_123_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_123_reg)=data)
#define set_CAM_EMM_EMM_BUF_124_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_124_reg)=data)
#define set_CAM_EMM_EMM_BUF_125_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_125_reg)=data)
#define set_CAM_EMM_EMM_BUF_126_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_126_reg)=data)
#define set_CAM_EMM_EMM_BUF_127_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_127_reg)=data)
#define set_CAM_EMM_EMM_BUF_128_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_128_reg)=data)
#define set_CAM_EMM_EMM_BUF_129_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_129_reg)=data)
#define set_CAM_EMM_EMM_BUF_130_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_130_reg)=data)
#define set_CAM_EMM_EMM_BUF_131_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_131_reg)=data)
#define set_CAM_EMM_EMM_BUF_132_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_132_reg)=data)
#define set_CAM_EMM_EMM_BUF_133_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_133_reg)=data)
#define set_CAM_EMM_EMM_BUF_134_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_134_reg)=data)
#define set_CAM_EMM_EMM_BUF_135_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_135_reg)=data)
#define set_CAM_EMM_EMM_BUF_136_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_136_reg)=data)
#define set_CAM_EMM_EMM_BUF_137_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_137_reg)=data)
#define set_CAM_EMM_EMM_BUF_138_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_138_reg)=data)
#define set_CAM_EMM_EMM_BUF_139_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_139_reg)=data)
#define set_CAM_EMM_EMM_BUF_140_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_140_reg)=data)
#define set_CAM_EMM_EMM_BUF_141_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_141_reg)=data)
#define set_CAM_EMM_EMM_BUF_142_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_142_reg)=data)
#define set_CAM_EMM_EMM_BUF_143_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_143_reg)=data)
#define set_CAM_EMM_EMM_BUF_144_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_144_reg)=data)
#define set_CAM_EMM_EMM_BUF_145_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_145_reg)=data)
#define set_CAM_EMM_EMM_BUF_146_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_146_reg)=data)
#define set_CAM_EMM_EMM_BUF_147_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_147_reg)=data)
#define set_CAM_EMM_EMM_BUF_148_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_148_reg)=data)
#define set_CAM_EMM_EMM_BUF_149_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_149_reg)=data)
#define set_CAM_EMM_EMM_BUF_150_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_150_reg)=data)
#define set_CAM_EMM_EMM_BUF_151_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_151_reg)=data)
#define set_CAM_EMM_EMM_BUF_152_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_152_reg)=data)
#define set_CAM_EMM_EMM_BUF_153_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_153_reg)=data)
#define set_CAM_EMM_EMM_BUF_154_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_154_reg)=data)
#define set_CAM_EMM_EMM_BUF_155_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_155_reg)=data)
#define set_CAM_EMM_EMM_BUF_156_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_156_reg)=data)
#define set_CAM_EMM_EMM_BUF_157_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_157_reg)=data)
#define set_CAM_EMM_EMM_BUF_158_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_158_reg)=data)
#define set_CAM_EMM_EMM_BUF_159_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_159_reg)=data)
#define set_CAM_EMM_EMM_BUF_160_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_160_reg)=data)
#define set_CAM_EMM_EMM_BUF_161_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_161_reg)=data)
#define set_CAM_EMM_EMM_BUF_162_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_162_reg)=data)
#define set_CAM_EMM_EMM_BUF_163_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_163_reg)=data)
#define set_CAM_EMM_EMM_BUF_164_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_164_reg)=data)
#define set_CAM_EMM_EMM_BUF_165_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_165_reg)=data)
#define set_CAM_EMM_EMM_BUF_166_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_166_reg)=data)
#define set_CAM_EMM_EMM_BUF_167_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_167_reg)=data)
#define set_CAM_EMM_EMM_BUF_168_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_168_reg)=data)
#define set_CAM_EMM_EMM_BUF_169_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_169_reg)=data)
#define set_CAM_EMM_EMM_BUF_170_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_170_reg)=data)
#define set_CAM_EMM_EMM_BUF_171_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_171_reg)=data)
#define set_CAM_EMM_EMM_BUF_172_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_172_reg)=data)
#define set_CAM_EMM_EMM_BUF_173_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_173_reg)=data)
#define set_CAM_EMM_EMM_BUF_174_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_174_reg)=data)
#define set_CAM_EMM_EMM_BUF_175_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_175_reg)=data)
#define set_CAM_EMM_EMM_BUF_176_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_176_reg)=data)
#define set_CAM_EMM_EMM_BUF_177_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_177_reg)=data)
#define set_CAM_EMM_EMM_BUF_178_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_178_reg)=data)
#define set_CAM_EMM_EMM_BUF_179_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_179_reg)=data)
#define set_CAM_EMM_EMM_BUF_180_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_180_reg)=data)
#define set_CAM_EMM_EMM_BUF_181_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_181_reg)=data)
#define set_CAM_EMM_EMM_BUF_182_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_182_reg)=data)
#define set_CAM_EMM_EMM_BUF_183_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_183_reg)=data)
#define set_CAM_EMM_EMM_BUF_184_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_184_reg)=data)
#define set_CAM_EMM_EMM_BUF_185_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_185_reg)=data)
#define set_CAM_EMM_EMM_BUF_186_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_186_reg)=data)
#define set_CAM_EMM_EMM_BUF_187_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_187_reg)=data)
#define set_CAM_EMM_EMM_BUF_188_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_188_reg)=data)
#define set_CAM_EMM_EMM_BUF_189_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_189_reg)=data)
#define set_CAM_EMM_EMM_BUF_190_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_190_reg)=data)
#define set_CAM_EMM_EMM_BUF_191_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_191_reg)=data)
#define set_CAM_EMM_EMM_BUF_192_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_192_reg)=data)
#define set_CAM_EMM_EMM_BUF_193_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_193_reg)=data)
#define set_CAM_EMM_EMM_BUF_194_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_194_reg)=data)
#define set_CAM_EMM_EMM_BUF_195_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_195_reg)=data)
#define set_CAM_EMM_EMM_BUF_196_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_196_reg)=data)
#define set_CAM_EMM_EMM_BUF_197_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_197_reg)=data)
#define set_CAM_EMM_EMM_BUF_198_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_198_reg)=data)
#define set_CAM_EMM_EMM_BUF_199_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_199_reg)=data)
#define set_CAM_EMM_EMM_BUF_200_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_200_reg)=data)
#define set_CAM_EMM_EMM_BUF_201_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_201_reg)=data)
#define set_CAM_EMM_EMM_BUF_202_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_202_reg)=data)
#define set_CAM_EMM_EMM_BUF_203_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_203_reg)=data)
#define set_CAM_EMM_EMM_BUF_204_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_204_reg)=data)
#define set_CAM_EMM_EMM_BUF_205_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_205_reg)=data)
#define set_CAM_EMM_EMM_BUF_206_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_206_reg)=data)
#define set_CAM_EMM_EMM_BUF_207_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_207_reg)=data)
#define set_CAM_EMM_EMM_BUF_208_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_208_reg)=data)
#define set_CAM_EMM_EMM_BUF_209_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_209_reg)=data)
#define set_CAM_EMM_EMM_BUF_210_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_210_reg)=data)
#define set_CAM_EMM_EMM_BUF_211_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_211_reg)=data)
#define set_CAM_EMM_EMM_BUF_212_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_212_reg)=data)
#define set_CAM_EMM_EMM_BUF_213_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_213_reg)=data)
#define set_CAM_EMM_EMM_BUF_214_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_214_reg)=data)
#define set_CAM_EMM_EMM_BUF_215_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_215_reg)=data)
#define set_CAM_EMM_EMM_BUF_216_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_216_reg)=data)
#define set_CAM_EMM_EMM_BUF_217_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_217_reg)=data)
#define set_CAM_EMM_EMM_BUF_218_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_218_reg)=data)
#define set_CAM_EMM_EMM_BUF_219_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_219_reg)=data)
#define set_CAM_EMM_EMM_BUF_220_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_220_reg)=data)
#define set_CAM_EMM_EMM_BUF_221_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_221_reg)=data)
#define set_CAM_EMM_EMM_BUF_222_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_222_reg)=data)
#define set_CAM_EMM_EMM_BUF_223_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_223_reg)=data)
#define set_CAM_EMM_EMM_BUF_224_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_224_reg)=data)
#define set_CAM_EMM_EMM_BUF_225_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_225_reg)=data)
#define set_CAM_EMM_EMM_BUF_226_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_226_reg)=data)
#define set_CAM_EMM_EMM_BUF_227_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_227_reg)=data)
#define set_CAM_EMM_EMM_BUF_228_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_228_reg)=data)
#define set_CAM_EMM_EMM_BUF_229_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_229_reg)=data)
#define set_CAM_EMM_EMM_BUF_230_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_230_reg)=data)
#define set_CAM_EMM_EMM_BUF_231_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_231_reg)=data)
#define set_CAM_EMM_EMM_BUF_232_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_232_reg)=data)
#define set_CAM_EMM_EMM_BUF_233_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_233_reg)=data)
#define set_CAM_EMM_EMM_BUF_234_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_234_reg)=data)
#define set_CAM_EMM_EMM_BUF_235_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_235_reg)=data)
#define set_CAM_EMM_EMM_BUF_236_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_236_reg)=data)
#define set_CAM_EMM_EMM_BUF_237_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_237_reg)=data)
#define set_CAM_EMM_EMM_BUF_238_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_238_reg)=data)
#define set_CAM_EMM_EMM_BUF_239_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_239_reg)=data)
#define set_CAM_EMM_EMM_BUF_240_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_240_reg)=data)
#define set_CAM_EMM_EMM_BUF_241_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_241_reg)=data)
#define set_CAM_EMM_EMM_BUF_242_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_242_reg)=data)
#define set_CAM_EMM_EMM_BUF_243_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_243_reg)=data)
#define set_CAM_EMM_EMM_BUF_244_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_244_reg)=data)
#define set_CAM_EMM_EMM_BUF_245_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_245_reg)=data)
#define set_CAM_EMM_EMM_BUF_246_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_246_reg)=data)
#define set_CAM_EMM_EMM_BUF_247_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_247_reg)=data)
#define set_CAM_EMM_EMM_BUF_248_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_248_reg)=data)
#define set_CAM_EMM_EMM_BUF_249_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_249_reg)=data)
#define set_CAM_EMM_EMM_BUF_250_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_250_reg)=data)
#define set_CAM_EMM_EMM_BUF_251_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_251_reg)=data)
#define set_CAM_EMM_EMM_BUF_252_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_252_reg)=data)
#define set_CAM_EMM_EMM_BUF_253_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_253_reg)=data)
#define set_CAM_EMM_EMM_BUF_254_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_254_reg)=data)
#define set_CAM_EMM_EMM_BUF_255_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_255_reg)=data)
#define set_CAM_EMM_EMM_BUF_256_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_256_reg)=data)
#define set_CAM_EMM_EMM_BUF_257_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_257_reg)=data)
#define set_CAM_EMM_EMM_BUF_258_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_258_reg)=data)
#define set_CAM_EMM_EMM_BUF_259_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_259_reg)=data)
#define set_CAM_EMM_EMM_BUF_260_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_260_reg)=data)
#define set_CAM_EMM_EMM_BUF_261_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_261_reg)=data)
#define set_CAM_EMM_EMM_BUF_262_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_262_reg)=data)
#define set_CAM_EMM_EMM_BUF_263_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_263_reg)=data)
#define set_CAM_EMM_EMM_BUF_264_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_264_reg)=data)
#define set_CAM_EMM_EMM_BUF_265_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_265_reg)=data)
#define set_CAM_EMM_EMM_BUF_266_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_266_reg)=data)
#define set_CAM_EMM_EMM_BUF_267_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_267_reg)=data)
#define set_CAM_EMM_EMM_BUF_268_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_268_reg)=data)
#define set_CAM_EMM_EMM_BUF_269_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_269_reg)=data)
#define set_CAM_EMM_EMM_BUF_270_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_270_reg)=data)
#define set_CAM_EMM_EMM_BUF_271_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_271_reg)=data)
#define set_CAM_EMM_EMM_BUF_272_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_272_reg)=data)
#define set_CAM_EMM_EMM_BUF_273_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_273_reg)=data)
#define set_CAM_EMM_EMM_BUF_274_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_274_reg)=data)
#define set_CAM_EMM_EMM_BUF_275_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_275_reg)=data)
#define set_CAM_EMM_EMM_BUF_276_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_276_reg)=data)
#define set_CAM_EMM_EMM_BUF_277_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_277_reg)=data)
#define set_CAM_EMM_EMM_BUF_278_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_278_reg)=data)
#define set_CAM_EMM_EMM_BUF_279_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_279_reg)=data)
#define set_CAM_EMM_EMM_BUF_280_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_280_reg)=data)
#define set_CAM_EMM_EMM_BUF_281_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_281_reg)=data)
#define set_CAM_EMM_EMM_BUF_282_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_282_reg)=data)
#define set_CAM_EMM_EMM_BUF_283_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_283_reg)=data)
#define set_CAM_EMM_EMM_BUF_284_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_284_reg)=data)
#define set_CAM_EMM_EMM_BUF_285_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_285_reg)=data)
#define set_CAM_EMM_EMM_BUF_286_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_286_reg)=data)
#define set_CAM_EMM_EMM_BUF_287_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_287_reg)=data)
#define set_CAM_EMM_EMM_BUF_288_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_288_reg)=data)
#define set_CAM_EMM_EMM_BUF_289_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_289_reg)=data)
#define set_CAM_EMM_EMM_BUF_290_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_290_reg)=data)
#define set_CAM_EMM_EMM_BUF_291_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_291_reg)=data)
#define set_CAM_EMM_EMM_BUF_292_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_292_reg)=data)
#define set_CAM_EMM_EMM_BUF_293_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_293_reg)=data)
#define set_CAM_EMM_EMM_BUF_294_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_294_reg)=data)
#define set_CAM_EMM_EMM_BUF_295_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_295_reg)=data)
#define set_CAM_EMM_EMM_BUF_296_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_296_reg)=data)
#define set_CAM_EMM_EMM_BUF_297_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_297_reg)=data)
#define set_CAM_EMM_EMM_BUF_298_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_298_reg)=data)
#define set_CAM_EMM_EMM_BUF_299_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_299_reg)=data)
#define set_CAM_EMM_EMM_BUF_300_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_300_reg)=data)
#define set_CAM_EMM_EMM_BUF_301_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_301_reg)=data)
#define set_CAM_EMM_EMM_BUF_302_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_302_reg)=data)
#define set_CAM_EMM_EMM_BUF_303_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_303_reg)=data)
#define set_CAM_EMM_EMM_BUF_304_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_304_reg)=data)
#define set_CAM_EMM_EMM_BUF_305_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_305_reg)=data)
#define set_CAM_EMM_EMM_BUF_306_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_306_reg)=data)
#define set_CAM_EMM_EMM_BUF_307_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_307_reg)=data)
#define set_CAM_EMM_EMM_BUF_308_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_308_reg)=data)
#define set_CAM_EMM_EMM_BUF_309_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_309_reg)=data)
#define set_CAM_EMM_EMM_BUF_310_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_310_reg)=data)
#define set_CAM_EMM_EMM_BUF_311_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_311_reg)=data)
#define set_CAM_EMM_EMM_BUF_312_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_312_reg)=data)
#define set_CAM_EMM_EMM_BUF_313_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_313_reg)=data)
#define set_CAM_EMM_EMM_BUF_314_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_314_reg)=data)
#define set_CAM_EMM_EMM_BUF_315_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_315_reg)=data)
#define set_CAM_EMM_EMM_BUF_316_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_316_reg)=data)
#define set_CAM_EMM_EMM_BUF_317_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_317_reg)=data)
#define set_CAM_EMM_EMM_BUF_318_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_318_reg)=data)
#define set_CAM_EMM_EMM_BUF_319_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_319_reg)=data)
#define set_CAM_EMM_EMM_BUF_320_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_320_reg)=data)
#define set_CAM_EMM_EMM_BUF_321_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_321_reg)=data)
#define set_CAM_EMM_EMM_BUF_322_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_322_reg)=data)
#define set_CAM_EMM_EMM_BUF_323_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_323_reg)=data)
#define set_CAM_EMM_EMM_BUF_324_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_324_reg)=data)
#define set_CAM_EMM_EMM_BUF_325_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_325_reg)=data)
#define set_CAM_EMM_EMM_BUF_326_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_326_reg)=data)
#define set_CAM_EMM_EMM_BUF_327_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_327_reg)=data)
#define set_CAM_EMM_EMM_BUF_328_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_328_reg)=data)
#define set_CAM_EMM_EMM_BUF_329_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_329_reg)=data)
#define set_CAM_EMM_EMM_BUF_330_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_330_reg)=data)
#define set_CAM_EMM_EMM_BUF_331_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_331_reg)=data)
#define set_CAM_EMM_EMM_BUF_332_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_332_reg)=data)
#define set_CAM_EMM_EMM_BUF_333_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_333_reg)=data)
#define set_CAM_EMM_EMM_BUF_334_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_334_reg)=data)
#define set_CAM_EMM_EMM_BUF_335_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_335_reg)=data)
#define set_CAM_EMM_EMM_BUF_336_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_336_reg)=data)
#define set_CAM_EMM_EMM_BUF_337_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_337_reg)=data)
#define set_CAM_EMM_EMM_BUF_338_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_338_reg)=data)
#define set_CAM_EMM_EMM_BUF_339_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_339_reg)=data)
#define set_CAM_EMM_EMM_BUF_340_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_340_reg)=data)
#define set_CAM_EMM_EMM_BUF_341_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_341_reg)=data)
#define set_CAM_EMM_EMM_BUF_342_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_342_reg)=data)
#define set_CAM_EMM_EMM_BUF_343_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_343_reg)=data)
#define set_CAM_EMM_EMM_BUF_344_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_344_reg)=data)
#define set_CAM_EMM_EMM_BUF_345_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_345_reg)=data)
#define set_CAM_EMM_EMM_BUF_346_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_346_reg)=data)
#define set_CAM_EMM_EMM_BUF_347_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_347_reg)=data)
#define set_CAM_EMM_EMM_BUF_348_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_348_reg)=data)
#define set_CAM_EMM_EMM_BUF_349_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_349_reg)=data)
#define set_CAM_EMM_EMM_BUF_350_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_350_reg)=data)
#define set_CAM_EMM_EMM_BUF_351_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_351_reg)=data)
#define set_CAM_EMM_EMM_BUF_352_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_352_reg)=data)
#define set_CAM_EMM_EMM_BUF_353_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_353_reg)=data)
#define set_CAM_EMM_EMM_BUF_354_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_354_reg)=data)
#define set_CAM_EMM_EMM_BUF_355_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_355_reg)=data)
#define set_CAM_EMM_EMM_BUF_356_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_356_reg)=data)
#define set_CAM_EMM_EMM_BUF_357_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_357_reg)=data)
#define set_CAM_EMM_EMM_BUF_358_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_358_reg)=data)
#define set_CAM_EMM_EMM_BUF_359_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_359_reg)=data)
#define set_CAM_EMM_EMM_BUF_360_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_360_reg)=data)
#define set_CAM_EMM_EMM_BUF_361_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_361_reg)=data)
#define set_CAM_EMM_EMM_BUF_362_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_362_reg)=data)
#define set_CAM_EMM_EMM_BUF_363_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_363_reg)=data)
#define set_CAM_EMM_EMM_BUF_364_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_364_reg)=data)
#define set_CAM_EMM_EMM_BUF_365_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_365_reg)=data)
#define set_CAM_EMM_EMM_BUF_366_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_366_reg)=data)
#define set_CAM_EMM_EMM_BUF_367_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_367_reg)=data)
#define set_CAM_EMM_EMM_BUF_368_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_368_reg)=data)
#define set_CAM_EMM_EMM_BUF_369_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_369_reg)=data)
#define set_CAM_EMM_EMM_BUF_370_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_370_reg)=data)
#define set_CAM_EMM_EMM_BUF_371_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_371_reg)=data)
#define set_CAM_EMM_EMM_BUF_372_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_372_reg)=data)
#define set_CAM_EMM_EMM_BUF_373_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_373_reg)=data)
#define set_CAM_EMM_EMM_BUF_374_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_374_reg)=data)
#define set_CAM_EMM_EMM_BUF_375_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_375_reg)=data)
#define set_CAM_EMM_EMM_BUF_376_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_376_reg)=data)
#define set_CAM_EMM_EMM_BUF_377_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_377_reg)=data)
#define set_CAM_EMM_EMM_BUF_378_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_378_reg)=data)
#define set_CAM_EMM_EMM_BUF_379_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_379_reg)=data)
#define set_CAM_EMM_EMM_BUF_380_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_380_reg)=data)
#define set_CAM_EMM_EMM_BUF_381_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_381_reg)=data)
#define set_CAM_EMM_EMM_BUF_382_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_382_reg)=data)
#define set_CAM_EMM_EMM_BUF_383_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_383_reg)=data)
#define set_CAM_EMM_EMM_BUF_384_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_384_reg)=data)
#define set_CAM_EMM_EMM_BUF_385_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_385_reg)=data)
#define set_CAM_EMM_EMM_BUF_386_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_386_reg)=data)
#define set_CAM_EMM_EMM_BUF_387_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_387_reg)=data)
#define set_CAM_EMM_EMM_BUF_388_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_388_reg)=data)
#define set_CAM_EMM_EMM_BUF_389_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_389_reg)=data)
#define set_CAM_EMM_EMM_BUF_390_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_390_reg)=data)
#define set_CAM_EMM_EMM_BUF_391_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_391_reg)=data)
#define set_CAM_EMM_EMM_BUF_392_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_392_reg)=data)
#define set_CAM_EMM_EMM_BUF_393_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_393_reg)=data)
#define set_CAM_EMM_EMM_BUF_394_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_394_reg)=data)
#define set_CAM_EMM_EMM_BUF_395_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_395_reg)=data)
#define set_CAM_EMM_EMM_BUF_396_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_396_reg)=data)
#define set_CAM_EMM_EMM_BUF_397_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_397_reg)=data)
#define set_CAM_EMM_EMM_BUF_398_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_398_reg)=data)
#define set_CAM_EMM_EMM_BUF_399_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_399_reg)=data)
#define set_CAM_EMM_EMM_BUF_400_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_400_reg)=data)
#define set_CAM_EMM_EMM_BUF_401_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_401_reg)=data)
#define set_CAM_EMM_EMM_BUF_402_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_402_reg)=data)
#define set_CAM_EMM_EMM_BUF_403_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_403_reg)=data)
#define set_CAM_EMM_EMM_BUF_404_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_404_reg)=data)
#define set_CAM_EMM_EMM_BUF_405_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_405_reg)=data)
#define set_CAM_EMM_EMM_BUF_406_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_406_reg)=data)
#define set_CAM_EMM_EMM_BUF_407_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_407_reg)=data)
#define set_CAM_EMM_EMM_BUF_408_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_408_reg)=data)
#define set_CAM_EMM_EMM_BUF_409_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_409_reg)=data)
#define set_CAM_EMM_EMM_BUF_410_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_410_reg)=data)
#define set_CAM_EMM_EMM_BUF_411_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_411_reg)=data)
#define set_CAM_EMM_EMM_BUF_412_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_412_reg)=data)
#define set_CAM_EMM_EMM_BUF_413_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_413_reg)=data)
#define set_CAM_EMM_EMM_BUF_414_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_414_reg)=data)
#define set_CAM_EMM_EMM_BUF_415_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_415_reg)=data)
#define set_CAM_EMM_EMM_BUF_416_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_416_reg)=data)
#define set_CAM_EMM_EMM_BUF_417_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_417_reg)=data)
#define set_CAM_EMM_EMM_BUF_418_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_418_reg)=data)
#define set_CAM_EMM_EMM_BUF_419_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_419_reg)=data)
#define set_CAM_EMM_EMM_BUF_420_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_420_reg)=data)
#define set_CAM_EMM_EMM_BUF_421_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_421_reg)=data)
#define set_CAM_EMM_EMM_BUF_422_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_422_reg)=data)
#define set_CAM_EMM_EMM_BUF_423_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_423_reg)=data)
#define set_CAM_EMM_EMM_BUF_424_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_424_reg)=data)
#define set_CAM_EMM_EMM_BUF_425_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_425_reg)=data)
#define set_CAM_EMM_EMM_BUF_426_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_426_reg)=data)
#define set_CAM_EMM_EMM_BUF_427_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_427_reg)=data)
#define set_CAM_EMM_EMM_BUF_428_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_428_reg)=data)
#define set_CAM_EMM_EMM_BUF_429_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_429_reg)=data)
#define set_CAM_EMM_EMM_BUF_430_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_430_reg)=data)
#define set_CAM_EMM_EMM_BUF_431_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_431_reg)=data)
#define set_CAM_EMM_EMM_BUF_432_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_432_reg)=data)
#define set_CAM_EMM_EMM_BUF_433_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_433_reg)=data)
#define set_CAM_EMM_EMM_BUF_434_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_434_reg)=data)
#define set_CAM_EMM_EMM_BUF_435_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_435_reg)=data)
#define set_CAM_EMM_EMM_BUF_436_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_436_reg)=data)
#define set_CAM_EMM_EMM_BUF_437_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_437_reg)=data)
#define set_CAM_EMM_EMM_BUF_438_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_438_reg)=data)
#define set_CAM_EMM_EMM_BUF_439_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_439_reg)=data)
#define set_CAM_EMM_EMM_BUF_440_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_440_reg)=data)
#define set_CAM_EMM_EMM_BUF_441_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_441_reg)=data)
#define set_CAM_EMM_EMM_BUF_442_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_442_reg)=data)
#define set_CAM_EMM_EMM_BUF_443_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_443_reg)=data)
#define set_CAM_EMM_EMM_BUF_444_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_444_reg)=data)
#define set_CAM_EMM_EMM_BUF_445_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_445_reg)=data)
#define set_CAM_EMM_EMM_BUF_446_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_446_reg)=data)
#define set_CAM_EMM_EMM_BUF_447_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_447_reg)=data)
#define set_CAM_EMM_EMM_BUF_448_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_448_reg)=data)
#define set_CAM_EMM_EMM_BUF_449_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_449_reg)=data)
#define set_CAM_EMM_EMM_BUF_450_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_450_reg)=data)
#define set_CAM_EMM_EMM_BUF_451_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_451_reg)=data)
#define set_CAM_EMM_EMM_BUF_452_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_452_reg)=data)
#define set_CAM_EMM_EMM_BUF_453_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_453_reg)=data)
#define set_CAM_EMM_EMM_BUF_454_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_454_reg)=data)
#define set_CAM_EMM_EMM_BUF_455_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_455_reg)=data)
#define set_CAM_EMM_EMM_BUF_456_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_456_reg)=data)
#define set_CAM_EMM_EMM_BUF_457_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_457_reg)=data)
#define set_CAM_EMM_EMM_BUF_458_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_458_reg)=data)
#define set_CAM_EMM_EMM_BUF_459_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_459_reg)=data)
#define set_CAM_EMM_EMM_BUF_460_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_460_reg)=data)
#define set_CAM_EMM_EMM_BUF_461_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_461_reg)=data)
#define set_CAM_EMM_EMM_BUF_462_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_462_reg)=data)
#define set_CAM_EMM_EMM_BUF_463_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_463_reg)=data)
#define set_CAM_EMM_EMM_BUF_464_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_464_reg)=data)
#define set_CAM_EMM_EMM_BUF_465_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_465_reg)=data)
#define set_CAM_EMM_EMM_BUF_466_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_466_reg)=data)
#define set_CAM_EMM_EMM_BUF_467_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_467_reg)=data)
#define set_CAM_EMM_EMM_BUF_468_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_468_reg)=data)
#define set_CAM_EMM_EMM_BUF_469_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_469_reg)=data)
#define set_CAM_EMM_EMM_BUF_470_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_470_reg)=data)
#define set_CAM_EMM_EMM_BUF_471_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_471_reg)=data)
#define set_CAM_EMM_EMM_BUF_472_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_472_reg)=data)
#define set_CAM_EMM_EMM_BUF_473_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_473_reg)=data)
#define set_CAM_EMM_EMM_BUF_474_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_474_reg)=data)
#define set_CAM_EMM_EMM_BUF_475_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_475_reg)=data)
#define set_CAM_EMM_EMM_BUF_476_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_476_reg)=data)
#define set_CAM_EMM_EMM_BUF_477_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_477_reg)=data)
#define set_CAM_EMM_EMM_BUF_478_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_478_reg)=data)
#define set_CAM_EMM_EMM_BUF_479_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_479_reg)=data)
#define set_CAM_EMM_EMM_BUF_480_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_480_reg)=data)
#define set_CAM_EMM_EMM_BUF_481_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_481_reg)=data)
#define set_CAM_EMM_EMM_BUF_482_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_482_reg)=data)
#define set_CAM_EMM_EMM_BUF_483_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_483_reg)=data)
#define set_CAM_EMM_EMM_BUF_484_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_484_reg)=data)
#define set_CAM_EMM_EMM_BUF_485_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_485_reg)=data)
#define set_CAM_EMM_EMM_BUF_486_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_486_reg)=data)
#define set_CAM_EMM_EMM_BUF_487_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_487_reg)=data)
#define set_CAM_EMM_EMM_BUF_488_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_488_reg)=data)
#define set_CAM_EMM_EMM_BUF_489_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_489_reg)=data)
#define set_CAM_EMM_EMM_BUF_490_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_490_reg)=data)
#define set_CAM_EMM_EMM_BUF_491_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_491_reg)=data)
#define set_CAM_EMM_EMM_BUF_492_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_492_reg)=data)
#define set_CAM_EMM_EMM_BUF_493_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_493_reg)=data)
#define set_CAM_EMM_EMM_BUF_494_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_494_reg)=data)
#define set_CAM_EMM_EMM_BUF_495_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_495_reg)=data)
#define set_CAM_EMM_EMM_BUF_496_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_496_reg)=data)
#define set_CAM_EMM_EMM_BUF_497_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_497_reg)=data)
#define set_CAM_EMM_EMM_BUF_498_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_498_reg)=data)
#define set_CAM_EMM_EMM_BUF_499_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_499_reg)=data)
#define set_CAM_EMM_EMM_BUF_500_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_500_reg)=data)
#define set_CAM_EMM_EMM_BUF_501_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_501_reg)=data)
#define set_CAM_EMM_EMM_BUF_502_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_502_reg)=data)
#define set_CAM_EMM_EMM_BUF_503_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_503_reg)=data)
#define set_CAM_EMM_EMM_BUF_504_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_504_reg)=data)
#define set_CAM_EMM_EMM_BUF_505_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_505_reg)=data)
#define set_CAM_EMM_EMM_BUF_506_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_506_reg)=data)
#define set_CAM_EMM_EMM_BUF_507_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_507_reg)=data)
#define set_CAM_EMM_EMM_BUF_508_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_508_reg)=data)
#define set_CAM_EMM_EMM_BUF_509_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_509_reg)=data)
#define set_CAM_EMM_EMM_BUF_510_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_510_reg)=data)
#define set_CAM_EMM_EMM_BUF_511_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_511_reg)=data)
#define set_CAM_EMM_EMM_BUF_512_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_512_reg)=data)
#define set_CAM_EMM_EMM_BUF_513_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_513_reg)=data)
#define set_CAM_EMM_EMM_BUF_514_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_514_reg)=data)
#define set_CAM_EMM_EMM_BUF_515_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_515_reg)=data)
#define set_CAM_EMM_EMM_BUF_516_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_516_reg)=data)
#define set_CAM_EMM_EMM_BUF_517_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_517_reg)=data)
#define set_CAM_EMM_EMM_BUF_518_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_518_reg)=data)
#define set_CAM_EMM_EMM_BUF_519_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_519_reg)=data)
#define set_CAM_EMM_EMM_BUF_520_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_520_reg)=data)
#define set_CAM_EMM_EMM_BUF_521_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_521_reg)=data)
#define set_CAM_EMM_EMM_BUF_522_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_522_reg)=data)
#define set_CAM_EMM_EMM_BUF_523_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_523_reg)=data)
#define set_CAM_EMM_EMM_BUF_524_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_524_reg)=data)
#define set_CAM_EMM_EMM_BUF_525_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_525_reg)=data)
#define set_CAM_EMM_EMM_BUF_526_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_526_reg)=data)
#define set_CAM_EMM_EMM_BUF_527_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_527_reg)=data)
#define set_CAM_EMM_EMM_BUF_528_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_528_reg)=data)
#define set_CAM_EMM_EMM_BUF_529_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_529_reg)=data)
#define set_CAM_EMM_EMM_BUF_530_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_530_reg)=data)
#define set_CAM_EMM_EMM_BUF_531_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_531_reg)=data)
#define set_CAM_EMM_EMM_BUF_532_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_532_reg)=data)
#define set_CAM_EMM_EMM_BUF_533_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_533_reg)=data)
#define set_CAM_EMM_EMM_BUF_534_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_534_reg)=data)
#define set_CAM_EMM_EMM_BUF_535_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_535_reg)=data)
#define set_CAM_EMM_EMM_BUF_536_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_536_reg)=data)
#define set_CAM_EMM_EMM_BUF_537_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_537_reg)=data)
#define set_CAM_EMM_EMM_BUF_538_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_538_reg)=data)
#define set_CAM_EMM_EMM_BUF_539_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_539_reg)=data)
#define set_CAM_EMM_EMM_BUF_540_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_540_reg)=data)
#define set_CAM_EMM_EMM_BUF_541_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_541_reg)=data)
#define set_CAM_EMM_EMM_BUF_542_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_542_reg)=data)
#define set_CAM_EMM_EMM_BUF_543_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_543_reg)=data)
#define set_CAM_EMM_EMM_BUF_544_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_544_reg)=data)
#define set_CAM_EMM_EMM_BUF_545_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_545_reg)=data)
#define set_CAM_EMM_EMM_BUF_546_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_546_reg)=data)
#define set_CAM_EMM_EMM_BUF_547_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_547_reg)=data)
#define set_CAM_EMM_EMM_BUF_548_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_548_reg)=data)
#define set_CAM_EMM_EMM_BUF_549_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_549_reg)=data)
#define set_CAM_EMM_EMM_BUF_550_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_550_reg)=data)
#define set_CAM_EMM_EMM_BUF_551_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_551_reg)=data)
#define set_CAM_EMM_EMM_BUF_552_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_552_reg)=data)
#define set_CAM_EMM_EMM_BUF_553_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_553_reg)=data)
#define set_CAM_EMM_EMM_BUF_554_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_554_reg)=data)
#define set_CAM_EMM_EMM_BUF_555_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_555_reg)=data)
#define set_CAM_EMM_EMM_BUF_556_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_556_reg)=data)
#define set_CAM_EMM_EMM_BUF_557_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_557_reg)=data)
#define set_CAM_EMM_EMM_BUF_558_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_558_reg)=data)
#define set_CAM_EMM_EMM_BUF_559_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_559_reg)=data)
#define set_CAM_EMM_EMM_BUF_560_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_560_reg)=data)
#define set_CAM_EMM_EMM_BUF_561_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_561_reg)=data)
#define set_CAM_EMM_EMM_BUF_562_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_562_reg)=data)
#define set_CAM_EMM_EMM_BUF_563_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_563_reg)=data)
#define set_CAM_EMM_EMM_BUF_564_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_564_reg)=data)
#define set_CAM_EMM_EMM_BUF_565_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_565_reg)=data)
#define set_CAM_EMM_EMM_BUF_566_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_566_reg)=data)
#define set_CAM_EMM_EMM_BUF_567_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_567_reg)=data)
#define set_CAM_EMM_EMM_BUF_568_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_568_reg)=data)
#define set_CAM_EMM_EMM_BUF_569_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_569_reg)=data)
#define set_CAM_EMM_EMM_BUF_570_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_570_reg)=data)
#define set_CAM_EMM_EMM_BUF_571_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_571_reg)=data)
#define set_CAM_EMM_EMM_BUF_572_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_572_reg)=data)
#define set_CAM_EMM_EMM_BUF_573_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_573_reg)=data)
#define set_CAM_EMM_EMM_BUF_574_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_574_reg)=data)
#define set_CAM_EMM_EMM_BUF_575_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_575_reg)=data)
#define set_CAM_EMM_EMM_BUF_576_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_576_reg)=data)
#define set_CAM_EMM_EMM_BUF_577_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_577_reg)=data)
#define set_CAM_EMM_EMM_BUF_578_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_578_reg)=data)
#define set_CAM_EMM_EMM_BUF_579_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_579_reg)=data)
#define set_CAM_EMM_EMM_BUF_580_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_580_reg)=data)
#define set_CAM_EMM_EMM_BUF_581_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_581_reg)=data)
#define set_CAM_EMM_EMM_BUF_582_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_582_reg)=data)
#define set_CAM_EMM_EMM_BUF_583_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_583_reg)=data)
#define set_CAM_EMM_EMM_BUF_584_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_584_reg)=data)
#define set_CAM_EMM_EMM_BUF_585_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_585_reg)=data)
#define set_CAM_EMM_EMM_BUF_586_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_586_reg)=data)
#define set_CAM_EMM_EMM_BUF_587_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_587_reg)=data)
#define set_CAM_EMM_EMM_BUF_588_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_588_reg)=data)
#define set_CAM_EMM_EMM_BUF_589_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_589_reg)=data)
#define set_CAM_EMM_EMM_BUF_590_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_590_reg)=data)
#define set_CAM_EMM_EMM_BUF_591_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_591_reg)=data)
#define set_CAM_EMM_EMM_BUF_592_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_592_reg)=data)
#define set_CAM_EMM_EMM_BUF_593_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_593_reg)=data)
#define set_CAM_EMM_EMM_BUF_594_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_594_reg)=data)
#define set_CAM_EMM_EMM_BUF_595_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_595_reg)=data)
#define set_CAM_EMM_EMM_BUF_596_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_596_reg)=data)
#define set_CAM_EMM_EMM_BUF_597_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_597_reg)=data)
#define set_CAM_EMM_EMM_BUF_598_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_598_reg)=data)
#define set_CAM_EMM_EMM_BUF_599_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_599_reg)=data)
#define set_CAM_EMM_EMM_BUF_600_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_600_reg)=data)
#define set_CAM_EMM_EMM_BUF_601_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_601_reg)=data)
#define set_CAM_EMM_EMM_BUF_602_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_602_reg)=data)
#define set_CAM_EMM_EMM_BUF_603_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_603_reg)=data)
#define set_CAM_EMM_EMM_BUF_604_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_604_reg)=data)
#define set_CAM_EMM_EMM_BUF_605_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_605_reg)=data)
#define set_CAM_EMM_EMM_BUF_606_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_606_reg)=data)
#define set_CAM_EMM_EMM_BUF_607_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_607_reg)=data)
#define set_CAM_EMM_EMM_BUF_608_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_608_reg)=data)
#define set_CAM_EMM_EMM_BUF_609_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_609_reg)=data)
#define set_CAM_EMM_EMM_BUF_610_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_610_reg)=data)
#define set_CAM_EMM_EMM_BUF_611_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_611_reg)=data)
#define set_CAM_EMM_EMM_BUF_612_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_612_reg)=data)
#define set_CAM_EMM_EMM_BUF_613_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_613_reg)=data)
#define set_CAM_EMM_EMM_BUF_614_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_614_reg)=data)
#define set_CAM_EMM_EMM_BUF_615_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_615_reg)=data)
#define set_CAM_EMM_EMM_BUF_616_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_616_reg)=data)
#define set_CAM_EMM_EMM_BUF_617_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_617_reg)=data)
#define set_CAM_EMM_EMM_BUF_618_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_618_reg)=data)
#define set_CAM_EMM_EMM_BUF_619_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_619_reg)=data)
#define set_CAM_EMM_EMM_BUF_620_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_620_reg)=data)
#define set_CAM_EMM_EMM_BUF_621_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_621_reg)=data)
#define set_CAM_EMM_EMM_BUF_622_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_622_reg)=data)
#define set_CAM_EMM_EMM_BUF_623_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_623_reg)=data)
#define set_CAM_EMM_EMM_BUF_624_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_624_reg)=data)
#define set_CAM_EMM_EMM_BUF_625_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_625_reg)=data)
#define set_CAM_EMM_EMM_BUF_626_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_626_reg)=data)
#define set_CAM_EMM_EMM_BUF_627_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_627_reg)=data)
#define set_CAM_EMM_EMM_BUF_628_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_628_reg)=data)
#define set_CAM_EMM_EMM_BUF_629_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_629_reg)=data)
#define set_CAM_EMM_EMM_BUF_630_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_630_reg)=data)
#define set_CAM_EMM_EMM_BUF_631_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_631_reg)=data)
#define set_CAM_EMM_EMM_BUF_632_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_632_reg)=data)
#define set_CAM_EMM_EMM_BUF_633_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_633_reg)=data)
#define set_CAM_EMM_EMM_BUF_634_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_634_reg)=data)
#define set_CAM_EMM_EMM_BUF_635_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_635_reg)=data)
#define set_CAM_EMM_EMM_BUF_636_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_636_reg)=data)
#define set_CAM_EMM_EMM_BUF_637_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_637_reg)=data)
#define set_CAM_EMM_EMM_BUF_638_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_638_reg)=data)
#define set_CAM_EMM_EMM_BUF_639_reg(data)   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_639_reg)=data)
#define get_CAM_EMM_EMM_BUF_0_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_0_reg))
#define get_CAM_EMM_EMM_BUF_1_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_1_reg))
#define get_CAM_EMM_EMM_BUF_2_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_2_reg))
#define get_CAM_EMM_EMM_BUF_3_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_3_reg))
#define get_CAM_EMM_EMM_BUF_4_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_4_reg))
#define get_CAM_EMM_EMM_BUF_5_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_5_reg))
#define get_CAM_EMM_EMM_BUF_6_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_6_reg))
#define get_CAM_EMM_EMM_BUF_7_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_7_reg))
#define get_CAM_EMM_EMM_BUF_8_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_8_reg))
#define get_CAM_EMM_EMM_BUF_9_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_9_reg))
#define get_CAM_EMM_EMM_BUF_10_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_10_reg))
#define get_CAM_EMM_EMM_BUF_11_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_11_reg))
#define get_CAM_EMM_EMM_BUF_12_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_12_reg))
#define get_CAM_EMM_EMM_BUF_13_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_13_reg))
#define get_CAM_EMM_EMM_BUF_14_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_14_reg))
#define get_CAM_EMM_EMM_BUF_15_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_15_reg))
#define get_CAM_EMM_EMM_BUF_16_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_16_reg))
#define get_CAM_EMM_EMM_BUF_17_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_17_reg))
#define get_CAM_EMM_EMM_BUF_18_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_18_reg))
#define get_CAM_EMM_EMM_BUF_19_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_19_reg))
#define get_CAM_EMM_EMM_BUF_20_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_20_reg))
#define get_CAM_EMM_EMM_BUF_21_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_21_reg))
#define get_CAM_EMM_EMM_BUF_22_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_22_reg))
#define get_CAM_EMM_EMM_BUF_23_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_23_reg))
#define get_CAM_EMM_EMM_BUF_24_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_24_reg))
#define get_CAM_EMM_EMM_BUF_25_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_25_reg))
#define get_CAM_EMM_EMM_BUF_26_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_26_reg))
#define get_CAM_EMM_EMM_BUF_27_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_27_reg))
#define get_CAM_EMM_EMM_BUF_28_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_28_reg))
#define get_CAM_EMM_EMM_BUF_29_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_29_reg))
#define get_CAM_EMM_EMM_BUF_30_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_30_reg))
#define get_CAM_EMM_EMM_BUF_31_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_31_reg))
#define get_CAM_EMM_EMM_BUF_32_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_32_reg))
#define get_CAM_EMM_EMM_BUF_33_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_33_reg))
#define get_CAM_EMM_EMM_BUF_34_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_34_reg))
#define get_CAM_EMM_EMM_BUF_35_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_35_reg))
#define get_CAM_EMM_EMM_BUF_36_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_36_reg))
#define get_CAM_EMM_EMM_BUF_37_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_37_reg))
#define get_CAM_EMM_EMM_BUF_38_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_38_reg))
#define get_CAM_EMM_EMM_BUF_39_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_39_reg))
#define get_CAM_EMM_EMM_BUF_40_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_40_reg))
#define get_CAM_EMM_EMM_BUF_41_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_41_reg))
#define get_CAM_EMM_EMM_BUF_42_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_42_reg))
#define get_CAM_EMM_EMM_BUF_43_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_43_reg))
#define get_CAM_EMM_EMM_BUF_44_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_44_reg))
#define get_CAM_EMM_EMM_BUF_45_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_45_reg))
#define get_CAM_EMM_EMM_BUF_46_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_46_reg))
#define get_CAM_EMM_EMM_BUF_47_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_47_reg))
#define get_CAM_EMM_EMM_BUF_48_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_48_reg))
#define get_CAM_EMM_EMM_BUF_49_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_49_reg))
#define get_CAM_EMM_EMM_BUF_50_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_50_reg))
#define get_CAM_EMM_EMM_BUF_51_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_51_reg))
#define get_CAM_EMM_EMM_BUF_52_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_52_reg))
#define get_CAM_EMM_EMM_BUF_53_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_53_reg))
#define get_CAM_EMM_EMM_BUF_54_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_54_reg))
#define get_CAM_EMM_EMM_BUF_55_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_55_reg))
#define get_CAM_EMM_EMM_BUF_56_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_56_reg))
#define get_CAM_EMM_EMM_BUF_57_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_57_reg))
#define get_CAM_EMM_EMM_BUF_58_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_58_reg))
#define get_CAM_EMM_EMM_BUF_59_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_59_reg))
#define get_CAM_EMM_EMM_BUF_60_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_60_reg))
#define get_CAM_EMM_EMM_BUF_61_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_61_reg))
#define get_CAM_EMM_EMM_BUF_62_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_62_reg))
#define get_CAM_EMM_EMM_BUF_63_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_63_reg))
#define get_CAM_EMM_EMM_BUF_64_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_64_reg))
#define get_CAM_EMM_EMM_BUF_65_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_65_reg))
#define get_CAM_EMM_EMM_BUF_66_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_66_reg))
#define get_CAM_EMM_EMM_BUF_67_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_67_reg))
#define get_CAM_EMM_EMM_BUF_68_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_68_reg))
#define get_CAM_EMM_EMM_BUF_69_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_69_reg))
#define get_CAM_EMM_EMM_BUF_70_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_70_reg))
#define get_CAM_EMM_EMM_BUF_71_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_71_reg))
#define get_CAM_EMM_EMM_BUF_72_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_72_reg))
#define get_CAM_EMM_EMM_BUF_73_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_73_reg))
#define get_CAM_EMM_EMM_BUF_74_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_74_reg))
#define get_CAM_EMM_EMM_BUF_75_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_75_reg))
#define get_CAM_EMM_EMM_BUF_76_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_76_reg))
#define get_CAM_EMM_EMM_BUF_77_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_77_reg))
#define get_CAM_EMM_EMM_BUF_78_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_78_reg))
#define get_CAM_EMM_EMM_BUF_79_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_79_reg))
#define get_CAM_EMM_EMM_BUF_80_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_80_reg))
#define get_CAM_EMM_EMM_BUF_81_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_81_reg))
#define get_CAM_EMM_EMM_BUF_82_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_82_reg))
#define get_CAM_EMM_EMM_BUF_83_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_83_reg))
#define get_CAM_EMM_EMM_BUF_84_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_84_reg))
#define get_CAM_EMM_EMM_BUF_85_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_85_reg))
#define get_CAM_EMM_EMM_BUF_86_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_86_reg))
#define get_CAM_EMM_EMM_BUF_87_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_87_reg))
#define get_CAM_EMM_EMM_BUF_88_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_88_reg))
#define get_CAM_EMM_EMM_BUF_89_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_89_reg))
#define get_CAM_EMM_EMM_BUF_90_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_90_reg))
#define get_CAM_EMM_EMM_BUF_91_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_91_reg))
#define get_CAM_EMM_EMM_BUF_92_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_92_reg))
#define get_CAM_EMM_EMM_BUF_93_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_93_reg))
#define get_CAM_EMM_EMM_BUF_94_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_94_reg))
#define get_CAM_EMM_EMM_BUF_95_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_95_reg))
#define get_CAM_EMM_EMM_BUF_96_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_96_reg))
#define get_CAM_EMM_EMM_BUF_97_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_97_reg))
#define get_CAM_EMM_EMM_BUF_98_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_98_reg))
#define get_CAM_EMM_EMM_BUF_99_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_99_reg))
#define get_CAM_EMM_EMM_BUF_100_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_100_reg))
#define get_CAM_EMM_EMM_BUF_101_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_101_reg))
#define get_CAM_EMM_EMM_BUF_102_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_102_reg))
#define get_CAM_EMM_EMM_BUF_103_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_103_reg))
#define get_CAM_EMM_EMM_BUF_104_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_104_reg))
#define get_CAM_EMM_EMM_BUF_105_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_105_reg))
#define get_CAM_EMM_EMM_BUF_106_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_106_reg))
#define get_CAM_EMM_EMM_BUF_107_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_107_reg))
#define get_CAM_EMM_EMM_BUF_108_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_108_reg))
#define get_CAM_EMM_EMM_BUF_109_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_109_reg))
#define get_CAM_EMM_EMM_BUF_110_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_110_reg))
#define get_CAM_EMM_EMM_BUF_111_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_111_reg))
#define get_CAM_EMM_EMM_BUF_112_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_112_reg))
#define get_CAM_EMM_EMM_BUF_113_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_113_reg))
#define get_CAM_EMM_EMM_BUF_114_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_114_reg))
#define get_CAM_EMM_EMM_BUF_115_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_115_reg))
#define get_CAM_EMM_EMM_BUF_116_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_116_reg))
#define get_CAM_EMM_EMM_BUF_117_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_117_reg))
#define get_CAM_EMM_EMM_BUF_118_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_118_reg))
#define get_CAM_EMM_EMM_BUF_119_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_119_reg))
#define get_CAM_EMM_EMM_BUF_120_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_120_reg))
#define get_CAM_EMM_EMM_BUF_121_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_121_reg))
#define get_CAM_EMM_EMM_BUF_122_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_122_reg))
#define get_CAM_EMM_EMM_BUF_123_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_123_reg))
#define get_CAM_EMM_EMM_BUF_124_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_124_reg))
#define get_CAM_EMM_EMM_BUF_125_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_125_reg))
#define get_CAM_EMM_EMM_BUF_126_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_126_reg))
#define get_CAM_EMM_EMM_BUF_127_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_127_reg))
#define get_CAM_EMM_EMM_BUF_128_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_128_reg))
#define get_CAM_EMM_EMM_BUF_129_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_129_reg))
#define get_CAM_EMM_EMM_BUF_130_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_130_reg))
#define get_CAM_EMM_EMM_BUF_131_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_131_reg))
#define get_CAM_EMM_EMM_BUF_132_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_132_reg))
#define get_CAM_EMM_EMM_BUF_133_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_133_reg))
#define get_CAM_EMM_EMM_BUF_134_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_134_reg))
#define get_CAM_EMM_EMM_BUF_135_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_135_reg))
#define get_CAM_EMM_EMM_BUF_136_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_136_reg))
#define get_CAM_EMM_EMM_BUF_137_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_137_reg))
#define get_CAM_EMM_EMM_BUF_138_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_138_reg))
#define get_CAM_EMM_EMM_BUF_139_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_139_reg))
#define get_CAM_EMM_EMM_BUF_140_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_140_reg))
#define get_CAM_EMM_EMM_BUF_141_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_141_reg))
#define get_CAM_EMM_EMM_BUF_142_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_142_reg))
#define get_CAM_EMM_EMM_BUF_143_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_143_reg))
#define get_CAM_EMM_EMM_BUF_144_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_144_reg))
#define get_CAM_EMM_EMM_BUF_145_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_145_reg))
#define get_CAM_EMM_EMM_BUF_146_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_146_reg))
#define get_CAM_EMM_EMM_BUF_147_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_147_reg))
#define get_CAM_EMM_EMM_BUF_148_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_148_reg))
#define get_CAM_EMM_EMM_BUF_149_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_149_reg))
#define get_CAM_EMM_EMM_BUF_150_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_150_reg))
#define get_CAM_EMM_EMM_BUF_151_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_151_reg))
#define get_CAM_EMM_EMM_BUF_152_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_152_reg))
#define get_CAM_EMM_EMM_BUF_153_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_153_reg))
#define get_CAM_EMM_EMM_BUF_154_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_154_reg))
#define get_CAM_EMM_EMM_BUF_155_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_155_reg))
#define get_CAM_EMM_EMM_BUF_156_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_156_reg))
#define get_CAM_EMM_EMM_BUF_157_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_157_reg))
#define get_CAM_EMM_EMM_BUF_158_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_158_reg))
#define get_CAM_EMM_EMM_BUF_159_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_159_reg))
#define get_CAM_EMM_EMM_BUF_160_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_160_reg))
#define get_CAM_EMM_EMM_BUF_161_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_161_reg))
#define get_CAM_EMM_EMM_BUF_162_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_162_reg))
#define get_CAM_EMM_EMM_BUF_163_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_163_reg))
#define get_CAM_EMM_EMM_BUF_164_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_164_reg))
#define get_CAM_EMM_EMM_BUF_165_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_165_reg))
#define get_CAM_EMM_EMM_BUF_166_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_166_reg))
#define get_CAM_EMM_EMM_BUF_167_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_167_reg))
#define get_CAM_EMM_EMM_BUF_168_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_168_reg))
#define get_CAM_EMM_EMM_BUF_169_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_169_reg))
#define get_CAM_EMM_EMM_BUF_170_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_170_reg))
#define get_CAM_EMM_EMM_BUF_171_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_171_reg))
#define get_CAM_EMM_EMM_BUF_172_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_172_reg))
#define get_CAM_EMM_EMM_BUF_173_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_173_reg))
#define get_CAM_EMM_EMM_BUF_174_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_174_reg))
#define get_CAM_EMM_EMM_BUF_175_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_175_reg))
#define get_CAM_EMM_EMM_BUF_176_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_176_reg))
#define get_CAM_EMM_EMM_BUF_177_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_177_reg))
#define get_CAM_EMM_EMM_BUF_178_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_178_reg))
#define get_CAM_EMM_EMM_BUF_179_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_179_reg))
#define get_CAM_EMM_EMM_BUF_180_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_180_reg))
#define get_CAM_EMM_EMM_BUF_181_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_181_reg))
#define get_CAM_EMM_EMM_BUF_182_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_182_reg))
#define get_CAM_EMM_EMM_BUF_183_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_183_reg))
#define get_CAM_EMM_EMM_BUF_184_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_184_reg))
#define get_CAM_EMM_EMM_BUF_185_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_185_reg))
#define get_CAM_EMM_EMM_BUF_186_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_186_reg))
#define get_CAM_EMM_EMM_BUF_187_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_187_reg))
#define get_CAM_EMM_EMM_BUF_188_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_188_reg))
#define get_CAM_EMM_EMM_BUF_189_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_189_reg))
#define get_CAM_EMM_EMM_BUF_190_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_190_reg))
#define get_CAM_EMM_EMM_BUF_191_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_191_reg))
#define get_CAM_EMM_EMM_BUF_192_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_192_reg))
#define get_CAM_EMM_EMM_BUF_193_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_193_reg))
#define get_CAM_EMM_EMM_BUF_194_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_194_reg))
#define get_CAM_EMM_EMM_BUF_195_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_195_reg))
#define get_CAM_EMM_EMM_BUF_196_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_196_reg))
#define get_CAM_EMM_EMM_BUF_197_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_197_reg))
#define get_CAM_EMM_EMM_BUF_198_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_198_reg))
#define get_CAM_EMM_EMM_BUF_199_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_199_reg))
#define get_CAM_EMM_EMM_BUF_200_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_200_reg))
#define get_CAM_EMM_EMM_BUF_201_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_201_reg))
#define get_CAM_EMM_EMM_BUF_202_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_202_reg))
#define get_CAM_EMM_EMM_BUF_203_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_203_reg))
#define get_CAM_EMM_EMM_BUF_204_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_204_reg))
#define get_CAM_EMM_EMM_BUF_205_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_205_reg))
#define get_CAM_EMM_EMM_BUF_206_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_206_reg))
#define get_CAM_EMM_EMM_BUF_207_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_207_reg))
#define get_CAM_EMM_EMM_BUF_208_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_208_reg))
#define get_CAM_EMM_EMM_BUF_209_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_209_reg))
#define get_CAM_EMM_EMM_BUF_210_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_210_reg))
#define get_CAM_EMM_EMM_BUF_211_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_211_reg))
#define get_CAM_EMM_EMM_BUF_212_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_212_reg))
#define get_CAM_EMM_EMM_BUF_213_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_213_reg))
#define get_CAM_EMM_EMM_BUF_214_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_214_reg))
#define get_CAM_EMM_EMM_BUF_215_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_215_reg))
#define get_CAM_EMM_EMM_BUF_216_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_216_reg))
#define get_CAM_EMM_EMM_BUF_217_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_217_reg))
#define get_CAM_EMM_EMM_BUF_218_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_218_reg))
#define get_CAM_EMM_EMM_BUF_219_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_219_reg))
#define get_CAM_EMM_EMM_BUF_220_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_220_reg))
#define get_CAM_EMM_EMM_BUF_221_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_221_reg))
#define get_CAM_EMM_EMM_BUF_222_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_222_reg))
#define get_CAM_EMM_EMM_BUF_223_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_223_reg))
#define get_CAM_EMM_EMM_BUF_224_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_224_reg))
#define get_CAM_EMM_EMM_BUF_225_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_225_reg))
#define get_CAM_EMM_EMM_BUF_226_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_226_reg))
#define get_CAM_EMM_EMM_BUF_227_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_227_reg))
#define get_CAM_EMM_EMM_BUF_228_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_228_reg))
#define get_CAM_EMM_EMM_BUF_229_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_229_reg))
#define get_CAM_EMM_EMM_BUF_230_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_230_reg))
#define get_CAM_EMM_EMM_BUF_231_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_231_reg))
#define get_CAM_EMM_EMM_BUF_232_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_232_reg))
#define get_CAM_EMM_EMM_BUF_233_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_233_reg))
#define get_CAM_EMM_EMM_BUF_234_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_234_reg))
#define get_CAM_EMM_EMM_BUF_235_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_235_reg))
#define get_CAM_EMM_EMM_BUF_236_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_236_reg))
#define get_CAM_EMM_EMM_BUF_237_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_237_reg))
#define get_CAM_EMM_EMM_BUF_238_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_238_reg))
#define get_CAM_EMM_EMM_BUF_239_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_239_reg))
#define get_CAM_EMM_EMM_BUF_240_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_240_reg))
#define get_CAM_EMM_EMM_BUF_241_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_241_reg))
#define get_CAM_EMM_EMM_BUF_242_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_242_reg))
#define get_CAM_EMM_EMM_BUF_243_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_243_reg))
#define get_CAM_EMM_EMM_BUF_244_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_244_reg))
#define get_CAM_EMM_EMM_BUF_245_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_245_reg))
#define get_CAM_EMM_EMM_BUF_246_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_246_reg))
#define get_CAM_EMM_EMM_BUF_247_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_247_reg))
#define get_CAM_EMM_EMM_BUF_248_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_248_reg))
#define get_CAM_EMM_EMM_BUF_249_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_249_reg))
#define get_CAM_EMM_EMM_BUF_250_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_250_reg))
#define get_CAM_EMM_EMM_BUF_251_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_251_reg))
#define get_CAM_EMM_EMM_BUF_252_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_252_reg))
#define get_CAM_EMM_EMM_BUF_253_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_253_reg))
#define get_CAM_EMM_EMM_BUF_254_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_254_reg))
#define get_CAM_EMM_EMM_BUF_255_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_255_reg))
#define get_CAM_EMM_EMM_BUF_256_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_256_reg))
#define get_CAM_EMM_EMM_BUF_257_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_257_reg))
#define get_CAM_EMM_EMM_BUF_258_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_258_reg))
#define get_CAM_EMM_EMM_BUF_259_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_259_reg))
#define get_CAM_EMM_EMM_BUF_260_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_260_reg))
#define get_CAM_EMM_EMM_BUF_261_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_261_reg))
#define get_CAM_EMM_EMM_BUF_262_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_262_reg))
#define get_CAM_EMM_EMM_BUF_263_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_263_reg))
#define get_CAM_EMM_EMM_BUF_264_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_264_reg))
#define get_CAM_EMM_EMM_BUF_265_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_265_reg))
#define get_CAM_EMM_EMM_BUF_266_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_266_reg))
#define get_CAM_EMM_EMM_BUF_267_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_267_reg))
#define get_CAM_EMM_EMM_BUF_268_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_268_reg))
#define get_CAM_EMM_EMM_BUF_269_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_269_reg))
#define get_CAM_EMM_EMM_BUF_270_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_270_reg))
#define get_CAM_EMM_EMM_BUF_271_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_271_reg))
#define get_CAM_EMM_EMM_BUF_272_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_272_reg))
#define get_CAM_EMM_EMM_BUF_273_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_273_reg))
#define get_CAM_EMM_EMM_BUF_274_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_274_reg))
#define get_CAM_EMM_EMM_BUF_275_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_275_reg))
#define get_CAM_EMM_EMM_BUF_276_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_276_reg))
#define get_CAM_EMM_EMM_BUF_277_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_277_reg))
#define get_CAM_EMM_EMM_BUF_278_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_278_reg))
#define get_CAM_EMM_EMM_BUF_279_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_279_reg))
#define get_CAM_EMM_EMM_BUF_280_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_280_reg))
#define get_CAM_EMM_EMM_BUF_281_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_281_reg))
#define get_CAM_EMM_EMM_BUF_282_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_282_reg))
#define get_CAM_EMM_EMM_BUF_283_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_283_reg))
#define get_CAM_EMM_EMM_BUF_284_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_284_reg))
#define get_CAM_EMM_EMM_BUF_285_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_285_reg))
#define get_CAM_EMM_EMM_BUF_286_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_286_reg))
#define get_CAM_EMM_EMM_BUF_287_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_287_reg))
#define get_CAM_EMM_EMM_BUF_288_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_288_reg))
#define get_CAM_EMM_EMM_BUF_289_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_289_reg))
#define get_CAM_EMM_EMM_BUF_290_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_290_reg))
#define get_CAM_EMM_EMM_BUF_291_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_291_reg))
#define get_CAM_EMM_EMM_BUF_292_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_292_reg))
#define get_CAM_EMM_EMM_BUF_293_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_293_reg))
#define get_CAM_EMM_EMM_BUF_294_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_294_reg))
#define get_CAM_EMM_EMM_BUF_295_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_295_reg))
#define get_CAM_EMM_EMM_BUF_296_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_296_reg))
#define get_CAM_EMM_EMM_BUF_297_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_297_reg))
#define get_CAM_EMM_EMM_BUF_298_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_298_reg))
#define get_CAM_EMM_EMM_BUF_299_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_299_reg))
#define get_CAM_EMM_EMM_BUF_300_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_300_reg))
#define get_CAM_EMM_EMM_BUF_301_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_301_reg))
#define get_CAM_EMM_EMM_BUF_302_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_302_reg))
#define get_CAM_EMM_EMM_BUF_303_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_303_reg))
#define get_CAM_EMM_EMM_BUF_304_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_304_reg))
#define get_CAM_EMM_EMM_BUF_305_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_305_reg))
#define get_CAM_EMM_EMM_BUF_306_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_306_reg))
#define get_CAM_EMM_EMM_BUF_307_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_307_reg))
#define get_CAM_EMM_EMM_BUF_308_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_308_reg))
#define get_CAM_EMM_EMM_BUF_309_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_309_reg))
#define get_CAM_EMM_EMM_BUF_310_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_310_reg))
#define get_CAM_EMM_EMM_BUF_311_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_311_reg))
#define get_CAM_EMM_EMM_BUF_312_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_312_reg))
#define get_CAM_EMM_EMM_BUF_313_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_313_reg))
#define get_CAM_EMM_EMM_BUF_314_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_314_reg))
#define get_CAM_EMM_EMM_BUF_315_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_315_reg))
#define get_CAM_EMM_EMM_BUF_316_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_316_reg))
#define get_CAM_EMM_EMM_BUF_317_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_317_reg))
#define get_CAM_EMM_EMM_BUF_318_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_318_reg))
#define get_CAM_EMM_EMM_BUF_319_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_319_reg))
#define get_CAM_EMM_EMM_BUF_320_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_320_reg))
#define get_CAM_EMM_EMM_BUF_321_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_321_reg))
#define get_CAM_EMM_EMM_BUF_322_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_322_reg))
#define get_CAM_EMM_EMM_BUF_323_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_323_reg))
#define get_CAM_EMM_EMM_BUF_324_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_324_reg))
#define get_CAM_EMM_EMM_BUF_325_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_325_reg))
#define get_CAM_EMM_EMM_BUF_326_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_326_reg))
#define get_CAM_EMM_EMM_BUF_327_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_327_reg))
#define get_CAM_EMM_EMM_BUF_328_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_328_reg))
#define get_CAM_EMM_EMM_BUF_329_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_329_reg))
#define get_CAM_EMM_EMM_BUF_330_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_330_reg))
#define get_CAM_EMM_EMM_BUF_331_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_331_reg))
#define get_CAM_EMM_EMM_BUF_332_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_332_reg))
#define get_CAM_EMM_EMM_BUF_333_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_333_reg))
#define get_CAM_EMM_EMM_BUF_334_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_334_reg))
#define get_CAM_EMM_EMM_BUF_335_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_335_reg))
#define get_CAM_EMM_EMM_BUF_336_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_336_reg))
#define get_CAM_EMM_EMM_BUF_337_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_337_reg))
#define get_CAM_EMM_EMM_BUF_338_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_338_reg))
#define get_CAM_EMM_EMM_BUF_339_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_339_reg))
#define get_CAM_EMM_EMM_BUF_340_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_340_reg))
#define get_CAM_EMM_EMM_BUF_341_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_341_reg))
#define get_CAM_EMM_EMM_BUF_342_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_342_reg))
#define get_CAM_EMM_EMM_BUF_343_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_343_reg))
#define get_CAM_EMM_EMM_BUF_344_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_344_reg))
#define get_CAM_EMM_EMM_BUF_345_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_345_reg))
#define get_CAM_EMM_EMM_BUF_346_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_346_reg))
#define get_CAM_EMM_EMM_BUF_347_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_347_reg))
#define get_CAM_EMM_EMM_BUF_348_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_348_reg))
#define get_CAM_EMM_EMM_BUF_349_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_349_reg))
#define get_CAM_EMM_EMM_BUF_350_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_350_reg))
#define get_CAM_EMM_EMM_BUF_351_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_351_reg))
#define get_CAM_EMM_EMM_BUF_352_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_352_reg))
#define get_CAM_EMM_EMM_BUF_353_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_353_reg))
#define get_CAM_EMM_EMM_BUF_354_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_354_reg))
#define get_CAM_EMM_EMM_BUF_355_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_355_reg))
#define get_CAM_EMM_EMM_BUF_356_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_356_reg))
#define get_CAM_EMM_EMM_BUF_357_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_357_reg))
#define get_CAM_EMM_EMM_BUF_358_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_358_reg))
#define get_CAM_EMM_EMM_BUF_359_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_359_reg))
#define get_CAM_EMM_EMM_BUF_360_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_360_reg))
#define get_CAM_EMM_EMM_BUF_361_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_361_reg))
#define get_CAM_EMM_EMM_BUF_362_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_362_reg))
#define get_CAM_EMM_EMM_BUF_363_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_363_reg))
#define get_CAM_EMM_EMM_BUF_364_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_364_reg))
#define get_CAM_EMM_EMM_BUF_365_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_365_reg))
#define get_CAM_EMM_EMM_BUF_366_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_366_reg))
#define get_CAM_EMM_EMM_BUF_367_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_367_reg))
#define get_CAM_EMM_EMM_BUF_368_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_368_reg))
#define get_CAM_EMM_EMM_BUF_369_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_369_reg))
#define get_CAM_EMM_EMM_BUF_370_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_370_reg))
#define get_CAM_EMM_EMM_BUF_371_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_371_reg))
#define get_CAM_EMM_EMM_BUF_372_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_372_reg))
#define get_CAM_EMM_EMM_BUF_373_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_373_reg))
#define get_CAM_EMM_EMM_BUF_374_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_374_reg))
#define get_CAM_EMM_EMM_BUF_375_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_375_reg))
#define get_CAM_EMM_EMM_BUF_376_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_376_reg))
#define get_CAM_EMM_EMM_BUF_377_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_377_reg))
#define get_CAM_EMM_EMM_BUF_378_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_378_reg))
#define get_CAM_EMM_EMM_BUF_379_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_379_reg))
#define get_CAM_EMM_EMM_BUF_380_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_380_reg))
#define get_CAM_EMM_EMM_BUF_381_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_381_reg))
#define get_CAM_EMM_EMM_BUF_382_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_382_reg))
#define get_CAM_EMM_EMM_BUF_383_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_383_reg))
#define get_CAM_EMM_EMM_BUF_384_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_384_reg))
#define get_CAM_EMM_EMM_BUF_385_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_385_reg))
#define get_CAM_EMM_EMM_BUF_386_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_386_reg))
#define get_CAM_EMM_EMM_BUF_387_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_387_reg))
#define get_CAM_EMM_EMM_BUF_388_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_388_reg))
#define get_CAM_EMM_EMM_BUF_389_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_389_reg))
#define get_CAM_EMM_EMM_BUF_390_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_390_reg))
#define get_CAM_EMM_EMM_BUF_391_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_391_reg))
#define get_CAM_EMM_EMM_BUF_392_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_392_reg))
#define get_CAM_EMM_EMM_BUF_393_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_393_reg))
#define get_CAM_EMM_EMM_BUF_394_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_394_reg))
#define get_CAM_EMM_EMM_BUF_395_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_395_reg))
#define get_CAM_EMM_EMM_BUF_396_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_396_reg))
#define get_CAM_EMM_EMM_BUF_397_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_397_reg))
#define get_CAM_EMM_EMM_BUF_398_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_398_reg))
#define get_CAM_EMM_EMM_BUF_399_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_399_reg))
#define get_CAM_EMM_EMM_BUF_400_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_400_reg))
#define get_CAM_EMM_EMM_BUF_401_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_401_reg))
#define get_CAM_EMM_EMM_BUF_402_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_402_reg))
#define get_CAM_EMM_EMM_BUF_403_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_403_reg))
#define get_CAM_EMM_EMM_BUF_404_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_404_reg))
#define get_CAM_EMM_EMM_BUF_405_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_405_reg))
#define get_CAM_EMM_EMM_BUF_406_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_406_reg))
#define get_CAM_EMM_EMM_BUF_407_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_407_reg))
#define get_CAM_EMM_EMM_BUF_408_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_408_reg))
#define get_CAM_EMM_EMM_BUF_409_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_409_reg))
#define get_CAM_EMM_EMM_BUF_410_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_410_reg))
#define get_CAM_EMM_EMM_BUF_411_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_411_reg))
#define get_CAM_EMM_EMM_BUF_412_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_412_reg))
#define get_CAM_EMM_EMM_BUF_413_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_413_reg))
#define get_CAM_EMM_EMM_BUF_414_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_414_reg))
#define get_CAM_EMM_EMM_BUF_415_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_415_reg))
#define get_CAM_EMM_EMM_BUF_416_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_416_reg))
#define get_CAM_EMM_EMM_BUF_417_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_417_reg))
#define get_CAM_EMM_EMM_BUF_418_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_418_reg))
#define get_CAM_EMM_EMM_BUF_419_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_419_reg))
#define get_CAM_EMM_EMM_BUF_420_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_420_reg))
#define get_CAM_EMM_EMM_BUF_421_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_421_reg))
#define get_CAM_EMM_EMM_BUF_422_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_422_reg))
#define get_CAM_EMM_EMM_BUF_423_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_423_reg))
#define get_CAM_EMM_EMM_BUF_424_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_424_reg))
#define get_CAM_EMM_EMM_BUF_425_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_425_reg))
#define get_CAM_EMM_EMM_BUF_426_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_426_reg))
#define get_CAM_EMM_EMM_BUF_427_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_427_reg))
#define get_CAM_EMM_EMM_BUF_428_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_428_reg))
#define get_CAM_EMM_EMM_BUF_429_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_429_reg))
#define get_CAM_EMM_EMM_BUF_430_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_430_reg))
#define get_CAM_EMM_EMM_BUF_431_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_431_reg))
#define get_CAM_EMM_EMM_BUF_432_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_432_reg))
#define get_CAM_EMM_EMM_BUF_433_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_433_reg))
#define get_CAM_EMM_EMM_BUF_434_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_434_reg))
#define get_CAM_EMM_EMM_BUF_435_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_435_reg))
#define get_CAM_EMM_EMM_BUF_436_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_436_reg))
#define get_CAM_EMM_EMM_BUF_437_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_437_reg))
#define get_CAM_EMM_EMM_BUF_438_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_438_reg))
#define get_CAM_EMM_EMM_BUF_439_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_439_reg))
#define get_CAM_EMM_EMM_BUF_440_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_440_reg))
#define get_CAM_EMM_EMM_BUF_441_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_441_reg))
#define get_CAM_EMM_EMM_BUF_442_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_442_reg))
#define get_CAM_EMM_EMM_BUF_443_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_443_reg))
#define get_CAM_EMM_EMM_BUF_444_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_444_reg))
#define get_CAM_EMM_EMM_BUF_445_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_445_reg))
#define get_CAM_EMM_EMM_BUF_446_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_446_reg))
#define get_CAM_EMM_EMM_BUF_447_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_447_reg))
#define get_CAM_EMM_EMM_BUF_448_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_448_reg))
#define get_CAM_EMM_EMM_BUF_449_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_449_reg))
#define get_CAM_EMM_EMM_BUF_450_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_450_reg))
#define get_CAM_EMM_EMM_BUF_451_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_451_reg))
#define get_CAM_EMM_EMM_BUF_452_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_452_reg))
#define get_CAM_EMM_EMM_BUF_453_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_453_reg))
#define get_CAM_EMM_EMM_BUF_454_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_454_reg))
#define get_CAM_EMM_EMM_BUF_455_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_455_reg))
#define get_CAM_EMM_EMM_BUF_456_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_456_reg))
#define get_CAM_EMM_EMM_BUF_457_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_457_reg))
#define get_CAM_EMM_EMM_BUF_458_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_458_reg))
#define get_CAM_EMM_EMM_BUF_459_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_459_reg))
#define get_CAM_EMM_EMM_BUF_460_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_460_reg))
#define get_CAM_EMM_EMM_BUF_461_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_461_reg))
#define get_CAM_EMM_EMM_BUF_462_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_462_reg))
#define get_CAM_EMM_EMM_BUF_463_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_463_reg))
#define get_CAM_EMM_EMM_BUF_464_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_464_reg))
#define get_CAM_EMM_EMM_BUF_465_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_465_reg))
#define get_CAM_EMM_EMM_BUF_466_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_466_reg))
#define get_CAM_EMM_EMM_BUF_467_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_467_reg))
#define get_CAM_EMM_EMM_BUF_468_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_468_reg))
#define get_CAM_EMM_EMM_BUF_469_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_469_reg))
#define get_CAM_EMM_EMM_BUF_470_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_470_reg))
#define get_CAM_EMM_EMM_BUF_471_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_471_reg))
#define get_CAM_EMM_EMM_BUF_472_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_472_reg))
#define get_CAM_EMM_EMM_BUF_473_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_473_reg))
#define get_CAM_EMM_EMM_BUF_474_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_474_reg))
#define get_CAM_EMM_EMM_BUF_475_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_475_reg))
#define get_CAM_EMM_EMM_BUF_476_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_476_reg))
#define get_CAM_EMM_EMM_BUF_477_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_477_reg))
#define get_CAM_EMM_EMM_BUF_478_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_478_reg))
#define get_CAM_EMM_EMM_BUF_479_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_479_reg))
#define get_CAM_EMM_EMM_BUF_480_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_480_reg))
#define get_CAM_EMM_EMM_BUF_481_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_481_reg))
#define get_CAM_EMM_EMM_BUF_482_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_482_reg))
#define get_CAM_EMM_EMM_BUF_483_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_483_reg))
#define get_CAM_EMM_EMM_BUF_484_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_484_reg))
#define get_CAM_EMM_EMM_BUF_485_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_485_reg))
#define get_CAM_EMM_EMM_BUF_486_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_486_reg))
#define get_CAM_EMM_EMM_BUF_487_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_487_reg))
#define get_CAM_EMM_EMM_BUF_488_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_488_reg))
#define get_CAM_EMM_EMM_BUF_489_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_489_reg))
#define get_CAM_EMM_EMM_BUF_490_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_490_reg))
#define get_CAM_EMM_EMM_BUF_491_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_491_reg))
#define get_CAM_EMM_EMM_BUF_492_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_492_reg))
#define get_CAM_EMM_EMM_BUF_493_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_493_reg))
#define get_CAM_EMM_EMM_BUF_494_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_494_reg))
#define get_CAM_EMM_EMM_BUF_495_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_495_reg))
#define get_CAM_EMM_EMM_BUF_496_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_496_reg))
#define get_CAM_EMM_EMM_BUF_497_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_497_reg))
#define get_CAM_EMM_EMM_BUF_498_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_498_reg))
#define get_CAM_EMM_EMM_BUF_499_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_499_reg))
#define get_CAM_EMM_EMM_BUF_500_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_500_reg))
#define get_CAM_EMM_EMM_BUF_501_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_501_reg))
#define get_CAM_EMM_EMM_BUF_502_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_502_reg))
#define get_CAM_EMM_EMM_BUF_503_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_503_reg))
#define get_CAM_EMM_EMM_BUF_504_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_504_reg))
#define get_CAM_EMM_EMM_BUF_505_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_505_reg))
#define get_CAM_EMM_EMM_BUF_506_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_506_reg))
#define get_CAM_EMM_EMM_BUF_507_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_507_reg))
#define get_CAM_EMM_EMM_BUF_508_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_508_reg))
#define get_CAM_EMM_EMM_BUF_509_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_509_reg))
#define get_CAM_EMM_EMM_BUF_510_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_510_reg))
#define get_CAM_EMM_EMM_BUF_511_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_511_reg))
#define get_CAM_EMM_EMM_BUF_512_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_512_reg))
#define get_CAM_EMM_EMM_BUF_513_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_513_reg))
#define get_CAM_EMM_EMM_BUF_514_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_514_reg))
#define get_CAM_EMM_EMM_BUF_515_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_515_reg))
#define get_CAM_EMM_EMM_BUF_516_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_516_reg))
#define get_CAM_EMM_EMM_BUF_517_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_517_reg))
#define get_CAM_EMM_EMM_BUF_518_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_518_reg))
#define get_CAM_EMM_EMM_BUF_519_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_519_reg))
#define get_CAM_EMM_EMM_BUF_520_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_520_reg))
#define get_CAM_EMM_EMM_BUF_521_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_521_reg))
#define get_CAM_EMM_EMM_BUF_522_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_522_reg))
#define get_CAM_EMM_EMM_BUF_523_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_523_reg))
#define get_CAM_EMM_EMM_BUF_524_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_524_reg))
#define get_CAM_EMM_EMM_BUF_525_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_525_reg))
#define get_CAM_EMM_EMM_BUF_526_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_526_reg))
#define get_CAM_EMM_EMM_BUF_527_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_527_reg))
#define get_CAM_EMM_EMM_BUF_528_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_528_reg))
#define get_CAM_EMM_EMM_BUF_529_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_529_reg))
#define get_CAM_EMM_EMM_BUF_530_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_530_reg))
#define get_CAM_EMM_EMM_BUF_531_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_531_reg))
#define get_CAM_EMM_EMM_BUF_532_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_532_reg))
#define get_CAM_EMM_EMM_BUF_533_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_533_reg))
#define get_CAM_EMM_EMM_BUF_534_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_534_reg))
#define get_CAM_EMM_EMM_BUF_535_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_535_reg))
#define get_CAM_EMM_EMM_BUF_536_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_536_reg))
#define get_CAM_EMM_EMM_BUF_537_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_537_reg))
#define get_CAM_EMM_EMM_BUF_538_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_538_reg))
#define get_CAM_EMM_EMM_BUF_539_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_539_reg))
#define get_CAM_EMM_EMM_BUF_540_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_540_reg))
#define get_CAM_EMM_EMM_BUF_541_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_541_reg))
#define get_CAM_EMM_EMM_BUF_542_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_542_reg))
#define get_CAM_EMM_EMM_BUF_543_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_543_reg))
#define get_CAM_EMM_EMM_BUF_544_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_544_reg))
#define get_CAM_EMM_EMM_BUF_545_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_545_reg))
#define get_CAM_EMM_EMM_BUF_546_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_546_reg))
#define get_CAM_EMM_EMM_BUF_547_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_547_reg))
#define get_CAM_EMM_EMM_BUF_548_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_548_reg))
#define get_CAM_EMM_EMM_BUF_549_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_549_reg))
#define get_CAM_EMM_EMM_BUF_550_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_550_reg))
#define get_CAM_EMM_EMM_BUF_551_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_551_reg))
#define get_CAM_EMM_EMM_BUF_552_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_552_reg))
#define get_CAM_EMM_EMM_BUF_553_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_553_reg))
#define get_CAM_EMM_EMM_BUF_554_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_554_reg))
#define get_CAM_EMM_EMM_BUF_555_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_555_reg))
#define get_CAM_EMM_EMM_BUF_556_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_556_reg))
#define get_CAM_EMM_EMM_BUF_557_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_557_reg))
#define get_CAM_EMM_EMM_BUF_558_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_558_reg))
#define get_CAM_EMM_EMM_BUF_559_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_559_reg))
#define get_CAM_EMM_EMM_BUF_560_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_560_reg))
#define get_CAM_EMM_EMM_BUF_561_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_561_reg))
#define get_CAM_EMM_EMM_BUF_562_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_562_reg))
#define get_CAM_EMM_EMM_BUF_563_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_563_reg))
#define get_CAM_EMM_EMM_BUF_564_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_564_reg))
#define get_CAM_EMM_EMM_BUF_565_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_565_reg))
#define get_CAM_EMM_EMM_BUF_566_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_566_reg))
#define get_CAM_EMM_EMM_BUF_567_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_567_reg))
#define get_CAM_EMM_EMM_BUF_568_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_568_reg))
#define get_CAM_EMM_EMM_BUF_569_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_569_reg))
#define get_CAM_EMM_EMM_BUF_570_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_570_reg))
#define get_CAM_EMM_EMM_BUF_571_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_571_reg))
#define get_CAM_EMM_EMM_BUF_572_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_572_reg))
#define get_CAM_EMM_EMM_BUF_573_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_573_reg))
#define get_CAM_EMM_EMM_BUF_574_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_574_reg))
#define get_CAM_EMM_EMM_BUF_575_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_575_reg))
#define get_CAM_EMM_EMM_BUF_576_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_576_reg))
#define get_CAM_EMM_EMM_BUF_577_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_577_reg))
#define get_CAM_EMM_EMM_BUF_578_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_578_reg))
#define get_CAM_EMM_EMM_BUF_579_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_579_reg))
#define get_CAM_EMM_EMM_BUF_580_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_580_reg))
#define get_CAM_EMM_EMM_BUF_581_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_581_reg))
#define get_CAM_EMM_EMM_BUF_582_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_582_reg))
#define get_CAM_EMM_EMM_BUF_583_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_583_reg))
#define get_CAM_EMM_EMM_BUF_584_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_584_reg))
#define get_CAM_EMM_EMM_BUF_585_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_585_reg))
#define get_CAM_EMM_EMM_BUF_586_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_586_reg))
#define get_CAM_EMM_EMM_BUF_587_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_587_reg))
#define get_CAM_EMM_EMM_BUF_588_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_588_reg))
#define get_CAM_EMM_EMM_BUF_589_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_589_reg))
#define get_CAM_EMM_EMM_BUF_590_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_590_reg))
#define get_CAM_EMM_EMM_BUF_591_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_591_reg))
#define get_CAM_EMM_EMM_BUF_592_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_592_reg))
#define get_CAM_EMM_EMM_BUF_593_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_593_reg))
#define get_CAM_EMM_EMM_BUF_594_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_594_reg))
#define get_CAM_EMM_EMM_BUF_595_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_595_reg))
#define get_CAM_EMM_EMM_BUF_596_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_596_reg))
#define get_CAM_EMM_EMM_BUF_597_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_597_reg))
#define get_CAM_EMM_EMM_BUF_598_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_598_reg))
#define get_CAM_EMM_EMM_BUF_599_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_599_reg))
#define get_CAM_EMM_EMM_BUF_600_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_600_reg))
#define get_CAM_EMM_EMM_BUF_601_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_601_reg))
#define get_CAM_EMM_EMM_BUF_602_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_602_reg))
#define get_CAM_EMM_EMM_BUF_603_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_603_reg))
#define get_CAM_EMM_EMM_BUF_604_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_604_reg))
#define get_CAM_EMM_EMM_BUF_605_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_605_reg))
#define get_CAM_EMM_EMM_BUF_606_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_606_reg))
#define get_CAM_EMM_EMM_BUF_607_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_607_reg))
#define get_CAM_EMM_EMM_BUF_608_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_608_reg))
#define get_CAM_EMM_EMM_BUF_609_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_609_reg))
#define get_CAM_EMM_EMM_BUF_610_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_610_reg))
#define get_CAM_EMM_EMM_BUF_611_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_611_reg))
#define get_CAM_EMM_EMM_BUF_612_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_612_reg))
#define get_CAM_EMM_EMM_BUF_613_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_613_reg))
#define get_CAM_EMM_EMM_BUF_614_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_614_reg))
#define get_CAM_EMM_EMM_BUF_615_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_615_reg))
#define get_CAM_EMM_EMM_BUF_616_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_616_reg))
#define get_CAM_EMM_EMM_BUF_617_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_617_reg))
#define get_CAM_EMM_EMM_BUF_618_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_618_reg))
#define get_CAM_EMM_EMM_BUF_619_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_619_reg))
#define get_CAM_EMM_EMM_BUF_620_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_620_reg))
#define get_CAM_EMM_EMM_BUF_621_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_621_reg))
#define get_CAM_EMM_EMM_BUF_622_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_622_reg))
#define get_CAM_EMM_EMM_BUF_623_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_623_reg))
#define get_CAM_EMM_EMM_BUF_624_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_624_reg))
#define get_CAM_EMM_EMM_BUF_625_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_625_reg))
#define get_CAM_EMM_EMM_BUF_626_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_626_reg))
#define get_CAM_EMM_EMM_BUF_627_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_627_reg))
#define get_CAM_EMM_EMM_BUF_628_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_628_reg))
#define get_CAM_EMM_EMM_BUF_629_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_629_reg))
#define get_CAM_EMM_EMM_BUF_630_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_630_reg))
#define get_CAM_EMM_EMM_BUF_631_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_631_reg))
#define get_CAM_EMM_EMM_BUF_632_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_632_reg))
#define get_CAM_EMM_EMM_BUF_633_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_633_reg))
#define get_CAM_EMM_EMM_BUF_634_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_634_reg))
#define get_CAM_EMM_EMM_BUF_635_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_635_reg))
#define get_CAM_EMM_EMM_BUF_636_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_636_reg))
#define get_CAM_EMM_EMM_BUF_637_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_637_reg))
#define get_CAM_EMM_EMM_BUF_638_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_638_reg))
#define get_CAM_EMM_EMM_BUF_639_reg   (*((volatile unsigned int*) CAM_EMM_EMM_BUF_639_reg))
#define CAM_EMM_EMM_BUF_0_inst_adr                                                   "0x0080"
#define CAM_EMM_EMM_BUF_1_inst_adr                                                   "0x0081"
#define CAM_EMM_EMM_BUF_2_inst_adr                                                   "0x0082"
#define CAM_EMM_EMM_BUF_3_inst_adr                                                   "0x0083"
#define CAM_EMM_EMM_BUF_4_inst_adr                                                   "0x0084"
#define CAM_EMM_EMM_BUF_5_inst_adr                                                   "0x0085"
#define CAM_EMM_EMM_BUF_6_inst_adr                                                   "0x0086"
#define CAM_EMM_EMM_BUF_7_inst_adr                                                   "0x0087"
#define CAM_EMM_EMM_BUF_8_inst_adr                                                   "0x0088"
#define CAM_EMM_EMM_BUF_9_inst_adr                                                   "0x0089"
#define CAM_EMM_EMM_BUF_10_inst_adr                                                   "0x008A"
#define CAM_EMM_EMM_BUF_11_inst_adr                                                   "0x008B"
#define CAM_EMM_EMM_BUF_12_inst_adr                                                   "0x008C"
#define CAM_EMM_EMM_BUF_13_inst_adr                                                   "0x008D"
#define CAM_EMM_EMM_BUF_14_inst_adr                                                   "0x008E"
#define CAM_EMM_EMM_BUF_15_inst_adr                                                   "0x008F"
#define CAM_EMM_EMM_BUF_16_inst_adr                                                   "0x0090"
#define CAM_EMM_EMM_BUF_17_inst_adr                                                   "0x0091"
#define CAM_EMM_EMM_BUF_18_inst_adr                                                   "0x0092"
#define CAM_EMM_EMM_BUF_19_inst_adr                                                   "0x0093"
#define CAM_EMM_EMM_BUF_20_inst_adr                                                   "0x0094"
#define CAM_EMM_EMM_BUF_21_inst_adr                                                   "0x0095"
#define CAM_EMM_EMM_BUF_22_inst_adr                                                   "0x0096"
#define CAM_EMM_EMM_BUF_23_inst_adr                                                   "0x0097"
#define CAM_EMM_EMM_BUF_24_inst_adr                                                   "0x0098"
#define CAM_EMM_EMM_BUF_25_inst_adr                                                   "0x0099"
#define CAM_EMM_EMM_BUF_26_inst_adr                                                   "0x009A"
#define CAM_EMM_EMM_BUF_27_inst_adr                                                   "0x009B"
#define CAM_EMM_EMM_BUF_28_inst_adr                                                   "0x009C"
#define CAM_EMM_EMM_BUF_29_inst_adr                                                   "0x009D"
#define CAM_EMM_EMM_BUF_30_inst_adr                                                   "0x009E"
#define CAM_EMM_EMM_BUF_31_inst_adr                                                   "0x009F"
#define CAM_EMM_EMM_BUF_32_inst_adr                                                   "0x00A0"
#define CAM_EMM_EMM_BUF_33_inst_adr                                                   "0x00A1"
#define CAM_EMM_EMM_BUF_34_inst_adr                                                   "0x00A2"
#define CAM_EMM_EMM_BUF_35_inst_adr                                                   "0x00A3"
#define CAM_EMM_EMM_BUF_36_inst_adr                                                   "0x00A4"
#define CAM_EMM_EMM_BUF_37_inst_adr                                                   "0x00A5"
#define CAM_EMM_EMM_BUF_38_inst_adr                                                   "0x00A6"
#define CAM_EMM_EMM_BUF_39_inst_adr                                                   "0x00A7"
#define CAM_EMM_EMM_BUF_40_inst_adr                                                   "0x00A8"
#define CAM_EMM_EMM_BUF_41_inst_adr                                                   "0x00A9"
#define CAM_EMM_EMM_BUF_42_inst_adr                                                   "0x00AA"
#define CAM_EMM_EMM_BUF_43_inst_adr                                                   "0x00AB"
#define CAM_EMM_EMM_BUF_44_inst_adr                                                   "0x00AC"
#define CAM_EMM_EMM_BUF_45_inst_adr                                                   "0x00AD"
#define CAM_EMM_EMM_BUF_46_inst_adr                                                   "0x00AE"
#define CAM_EMM_EMM_BUF_47_inst_adr                                                   "0x00AF"
#define CAM_EMM_EMM_BUF_48_inst_adr                                                   "0x00B0"
#define CAM_EMM_EMM_BUF_49_inst_adr                                                   "0x00B1"
#define CAM_EMM_EMM_BUF_50_inst_adr                                                   "0x00B2"
#define CAM_EMM_EMM_BUF_51_inst_adr                                                   "0x00B3"
#define CAM_EMM_EMM_BUF_52_inst_adr                                                   "0x00B4"
#define CAM_EMM_EMM_BUF_53_inst_adr                                                   "0x00B5"
#define CAM_EMM_EMM_BUF_54_inst_adr                                                   "0x00B6"
#define CAM_EMM_EMM_BUF_55_inst_adr                                                   "0x00B7"
#define CAM_EMM_EMM_BUF_56_inst_adr                                                   "0x00B8"
#define CAM_EMM_EMM_BUF_57_inst_adr                                                   "0x00B9"
#define CAM_EMM_EMM_BUF_58_inst_adr                                                   "0x00BA"
#define CAM_EMM_EMM_BUF_59_inst_adr                                                   "0x00BB"
#define CAM_EMM_EMM_BUF_60_inst_adr                                                   "0x00BC"
#define CAM_EMM_EMM_BUF_61_inst_adr                                                   "0x00BD"
#define CAM_EMM_EMM_BUF_62_inst_adr                                                   "0x00BE"
#define CAM_EMM_EMM_BUF_63_inst_adr                                                   "0x00BF"
#define CAM_EMM_EMM_BUF_64_inst_adr                                                   "0x00C0"
#define CAM_EMM_EMM_BUF_65_inst_adr                                                   "0x00C1"
#define CAM_EMM_EMM_BUF_66_inst_adr                                                   "0x00C2"
#define CAM_EMM_EMM_BUF_67_inst_adr                                                   "0x00C3"
#define CAM_EMM_EMM_BUF_68_inst_adr                                                   "0x00C4"
#define CAM_EMM_EMM_BUF_69_inst_adr                                                   "0x00C5"
#define CAM_EMM_EMM_BUF_70_inst_adr                                                   "0x00C6"
#define CAM_EMM_EMM_BUF_71_inst_adr                                                   "0x00C7"
#define CAM_EMM_EMM_BUF_72_inst_adr                                                   "0x00C8"
#define CAM_EMM_EMM_BUF_73_inst_adr                                                   "0x00C9"
#define CAM_EMM_EMM_BUF_74_inst_adr                                                   "0x00CA"
#define CAM_EMM_EMM_BUF_75_inst_adr                                                   "0x00CB"
#define CAM_EMM_EMM_BUF_76_inst_adr                                                   "0x00CC"
#define CAM_EMM_EMM_BUF_77_inst_adr                                                   "0x00CD"
#define CAM_EMM_EMM_BUF_78_inst_adr                                                   "0x00CE"
#define CAM_EMM_EMM_BUF_79_inst_adr                                                   "0x00CF"
#define CAM_EMM_EMM_BUF_80_inst_adr                                                   "0x00D0"
#define CAM_EMM_EMM_BUF_81_inst_adr                                                   "0x00D1"
#define CAM_EMM_EMM_BUF_82_inst_adr                                                   "0x00D2"
#define CAM_EMM_EMM_BUF_83_inst_adr                                                   "0x00D3"
#define CAM_EMM_EMM_BUF_84_inst_adr                                                   "0x00D4"
#define CAM_EMM_EMM_BUF_85_inst_adr                                                   "0x00D5"
#define CAM_EMM_EMM_BUF_86_inst_adr                                                   "0x00D6"
#define CAM_EMM_EMM_BUF_87_inst_adr                                                   "0x00D7"
#define CAM_EMM_EMM_BUF_88_inst_adr                                                   "0x00D8"
#define CAM_EMM_EMM_BUF_89_inst_adr                                                   "0x00D9"
#define CAM_EMM_EMM_BUF_90_inst_adr                                                   "0x00DA"
#define CAM_EMM_EMM_BUF_91_inst_adr                                                   "0x00DB"
#define CAM_EMM_EMM_BUF_92_inst_adr                                                   "0x00DC"
#define CAM_EMM_EMM_BUF_93_inst_adr                                                   "0x00DD"
#define CAM_EMM_EMM_BUF_94_inst_adr                                                   "0x00DE"
#define CAM_EMM_EMM_BUF_95_inst_adr                                                   "0x00DF"
#define CAM_EMM_EMM_BUF_96_inst_adr                                                   "0x00E0"
#define CAM_EMM_EMM_BUF_97_inst_adr                                                   "0x00E1"
#define CAM_EMM_EMM_BUF_98_inst_adr                                                   "0x00E2"
#define CAM_EMM_EMM_BUF_99_inst_adr                                                   "0x00E3"
#define CAM_EMM_EMM_BUF_100_inst_adr                                                   "0x00E4"
#define CAM_EMM_EMM_BUF_101_inst_adr                                                   "0x00E5"
#define CAM_EMM_EMM_BUF_102_inst_adr                                                   "0x00E6"
#define CAM_EMM_EMM_BUF_103_inst_adr                                                   "0x00E7"
#define CAM_EMM_EMM_BUF_104_inst_adr                                                   "0x00E8"
#define CAM_EMM_EMM_BUF_105_inst_adr                                                   "0x00E9"
#define CAM_EMM_EMM_BUF_106_inst_adr                                                   "0x00EA"
#define CAM_EMM_EMM_BUF_107_inst_adr                                                   "0x00EB"
#define CAM_EMM_EMM_BUF_108_inst_adr                                                   "0x00EC"
#define CAM_EMM_EMM_BUF_109_inst_adr                                                   "0x00ED"
#define CAM_EMM_EMM_BUF_110_inst_adr                                                   "0x00EE"
#define CAM_EMM_EMM_BUF_111_inst_adr                                                   "0x00EF"
#define CAM_EMM_EMM_BUF_112_inst_adr                                                   "0x00F0"
#define CAM_EMM_EMM_BUF_113_inst_adr                                                   "0x00F1"
#define CAM_EMM_EMM_BUF_114_inst_adr                                                   "0x00F2"
#define CAM_EMM_EMM_BUF_115_inst_adr                                                   "0x00F3"
#define CAM_EMM_EMM_BUF_116_inst_adr                                                   "0x00F4"
#define CAM_EMM_EMM_BUF_117_inst_adr                                                   "0x00F5"
#define CAM_EMM_EMM_BUF_118_inst_adr                                                   "0x00F6"
#define CAM_EMM_EMM_BUF_119_inst_adr                                                   "0x00F7"
#define CAM_EMM_EMM_BUF_120_inst_adr                                                   "0x00F8"
#define CAM_EMM_EMM_BUF_121_inst_adr                                                   "0x00F9"
#define CAM_EMM_EMM_BUF_122_inst_adr                                                   "0x00FA"
#define CAM_EMM_EMM_BUF_123_inst_adr                                                   "0x00FB"
#define CAM_EMM_EMM_BUF_124_inst_adr                                                   "0x00FC"
#define CAM_EMM_EMM_BUF_125_inst_adr                                                   "0x00FD"
#define CAM_EMM_EMM_BUF_126_inst_adr                                                   "0x00FE"
#define CAM_EMM_EMM_BUF_127_inst_adr                                                   "0x00FF"
#define CAM_EMM_EMM_BUF_128_inst_adr                                                   "0x0100"
#define CAM_EMM_EMM_BUF_129_inst_adr                                                   "0x0101"
#define CAM_EMM_EMM_BUF_130_inst_adr                                                   "0x0102"
#define CAM_EMM_EMM_BUF_131_inst_adr                                                   "0x0103"
#define CAM_EMM_EMM_BUF_132_inst_adr                                                   "0x0104"
#define CAM_EMM_EMM_BUF_133_inst_adr                                                   "0x0105"
#define CAM_EMM_EMM_BUF_134_inst_adr                                                   "0x0106"
#define CAM_EMM_EMM_BUF_135_inst_adr                                                   "0x0107"
#define CAM_EMM_EMM_BUF_136_inst_adr                                                   "0x0108"
#define CAM_EMM_EMM_BUF_137_inst_adr                                                   "0x0109"
#define CAM_EMM_EMM_BUF_138_inst_adr                                                   "0x010A"
#define CAM_EMM_EMM_BUF_139_inst_adr                                                   "0x010B"
#define CAM_EMM_EMM_BUF_140_inst_adr                                                   "0x010C"
#define CAM_EMM_EMM_BUF_141_inst_adr                                                   "0x010D"
#define CAM_EMM_EMM_BUF_142_inst_adr                                                   "0x010E"
#define CAM_EMM_EMM_BUF_143_inst_adr                                                   "0x010F"
#define CAM_EMM_EMM_BUF_144_inst_adr                                                   "0x0110"
#define CAM_EMM_EMM_BUF_145_inst_adr                                                   "0x0111"
#define CAM_EMM_EMM_BUF_146_inst_adr                                                   "0x0112"
#define CAM_EMM_EMM_BUF_147_inst_adr                                                   "0x0113"
#define CAM_EMM_EMM_BUF_148_inst_adr                                                   "0x0114"
#define CAM_EMM_EMM_BUF_149_inst_adr                                                   "0x0115"
#define CAM_EMM_EMM_BUF_150_inst_adr                                                   "0x0116"
#define CAM_EMM_EMM_BUF_151_inst_adr                                                   "0x0117"
#define CAM_EMM_EMM_BUF_152_inst_adr                                                   "0x0118"
#define CAM_EMM_EMM_BUF_153_inst_adr                                                   "0x0119"
#define CAM_EMM_EMM_BUF_154_inst_adr                                                   "0x011A"
#define CAM_EMM_EMM_BUF_155_inst_adr                                                   "0x011B"
#define CAM_EMM_EMM_BUF_156_inst_adr                                                   "0x011C"
#define CAM_EMM_EMM_BUF_157_inst_adr                                                   "0x011D"
#define CAM_EMM_EMM_BUF_158_inst_adr                                                   "0x011E"
#define CAM_EMM_EMM_BUF_159_inst_adr                                                   "0x011F"
#define CAM_EMM_EMM_BUF_160_inst_adr                                                   "0x0120"
#define CAM_EMM_EMM_BUF_161_inst_adr                                                   "0x0121"
#define CAM_EMM_EMM_BUF_162_inst_adr                                                   "0x0122"
#define CAM_EMM_EMM_BUF_163_inst_adr                                                   "0x0123"
#define CAM_EMM_EMM_BUF_164_inst_adr                                                   "0x0124"
#define CAM_EMM_EMM_BUF_165_inst_adr                                                   "0x0125"
#define CAM_EMM_EMM_BUF_166_inst_adr                                                   "0x0126"
#define CAM_EMM_EMM_BUF_167_inst_adr                                                   "0x0127"
#define CAM_EMM_EMM_BUF_168_inst_adr                                                   "0x0128"
#define CAM_EMM_EMM_BUF_169_inst_adr                                                   "0x0129"
#define CAM_EMM_EMM_BUF_170_inst_adr                                                   "0x012A"
#define CAM_EMM_EMM_BUF_171_inst_adr                                                   "0x012B"
#define CAM_EMM_EMM_BUF_172_inst_adr                                                   "0x012C"
#define CAM_EMM_EMM_BUF_173_inst_adr                                                   "0x012D"
#define CAM_EMM_EMM_BUF_174_inst_adr                                                   "0x012E"
#define CAM_EMM_EMM_BUF_175_inst_adr                                                   "0x012F"
#define CAM_EMM_EMM_BUF_176_inst_adr                                                   "0x0130"
#define CAM_EMM_EMM_BUF_177_inst_adr                                                   "0x0131"
#define CAM_EMM_EMM_BUF_178_inst_adr                                                   "0x0132"
#define CAM_EMM_EMM_BUF_179_inst_adr                                                   "0x0133"
#define CAM_EMM_EMM_BUF_180_inst_adr                                                   "0x0134"
#define CAM_EMM_EMM_BUF_181_inst_adr                                                   "0x0135"
#define CAM_EMM_EMM_BUF_182_inst_adr                                                   "0x0136"
#define CAM_EMM_EMM_BUF_183_inst_adr                                                   "0x0137"
#define CAM_EMM_EMM_BUF_184_inst_adr                                                   "0x0138"
#define CAM_EMM_EMM_BUF_185_inst_adr                                                   "0x0139"
#define CAM_EMM_EMM_BUF_186_inst_adr                                                   "0x013A"
#define CAM_EMM_EMM_BUF_187_inst_adr                                                   "0x013B"
#define CAM_EMM_EMM_BUF_188_inst_adr                                                   "0x013C"
#define CAM_EMM_EMM_BUF_189_inst_adr                                                   "0x013D"
#define CAM_EMM_EMM_BUF_190_inst_adr                                                   "0x013E"
#define CAM_EMM_EMM_BUF_191_inst_adr                                                   "0x013F"
#define CAM_EMM_EMM_BUF_192_inst_adr                                                   "0x0140"
#define CAM_EMM_EMM_BUF_193_inst_adr                                                   "0x0141"
#define CAM_EMM_EMM_BUF_194_inst_adr                                                   "0x0142"
#define CAM_EMM_EMM_BUF_195_inst_adr                                                   "0x0143"
#define CAM_EMM_EMM_BUF_196_inst_adr                                                   "0x0144"
#define CAM_EMM_EMM_BUF_197_inst_adr                                                   "0x0145"
#define CAM_EMM_EMM_BUF_198_inst_adr                                                   "0x0146"
#define CAM_EMM_EMM_BUF_199_inst_adr                                                   "0x0147"
#define CAM_EMM_EMM_BUF_200_inst_adr                                                   "0x0148"
#define CAM_EMM_EMM_BUF_201_inst_adr                                                   "0x0149"
#define CAM_EMM_EMM_BUF_202_inst_adr                                                   "0x014A"
#define CAM_EMM_EMM_BUF_203_inst_adr                                                   "0x014B"
#define CAM_EMM_EMM_BUF_204_inst_adr                                                   "0x014C"
#define CAM_EMM_EMM_BUF_205_inst_adr                                                   "0x014D"
#define CAM_EMM_EMM_BUF_206_inst_adr                                                   "0x014E"
#define CAM_EMM_EMM_BUF_207_inst_adr                                                   "0x014F"
#define CAM_EMM_EMM_BUF_208_inst_adr                                                   "0x0150"
#define CAM_EMM_EMM_BUF_209_inst_adr                                                   "0x0151"
#define CAM_EMM_EMM_BUF_210_inst_adr                                                   "0x0152"
#define CAM_EMM_EMM_BUF_211_inst_adr                                                   "0x0153"
#define CAM_EMM_EMM_BUF_212_inst_adr                                                   "0x0154"
#define CAM_EMM_EMM_BUF_213_inst_adr                                                   "0x0155"
#define CAM_EMM_EMM_BUF_214_inst_adr                                                   "0x0156"
#define CAM_EMM_EMM_BUF_215_inst_adr                                                   "0x0157"
#define CAM_EMM_EMM_BUF_216_inst_adr                                                   "0x0158"
#define CAM_EMM_EMM_BUF_217_inst_adr                                                   "0x0159"
#define CAM_EMM_EMM_BUF_218_inst_adr                                                   "0x015A"
#define CAM_EMM_EMM_BUF_219_inst_adr                                                   "0x015B"
#define CAM_EMM_EMM_BUF_220_inst_adr                                                   "0x015C"
#define CAM_EMM_EMM_BUF_221_inst_adr                                                   "0x015D"
#define CAM_EMM_EMM_BUF_222_inst_adr                                                   "0x015E"
#define CAM_EMM_EMM_BUF_223_inst_adr                                                   "0x015F"
#define CAM_EMM_EMM_BUF_224_inst_adr                                                   "0x0160"
#define CAM_EMM_EMM_BUF_225_inst_adr                                                   "0x0161"
#define CAM_EMM_EMM_BUF_226_inst_adr                                                   "0x0162"
#define CAM_EMM_EMM_BUF_227_inst_adr                                                   "0x0163"
#define CAM_EMM_EMM_BUF_228_inst_adr                                                   "0x0164"
#define CAM_EMM_EMM_BUF_229_inst_adr                                                   "0x0165"
#define CAM_EMM_EMM_BUF_230_inst_adr                                                   "0x0166"
#define CAM_EMM_EMM_BUF_231_inst_adr                                                   "0x0167"
#define CAM_EMM_EMM_BUF_232_inst_adr                                                   "0x0168"
#define CAM_EMM_EMM_BUF_233_inst_adr                                                   "0x0169"
#define CAM_EMM_EMM_BUF_234_inst_adr                                                   "0x016A"
#define CAM_EMM_EMM_BUF_235_inst_adr                                                   "0x016B"
#define CAM_EMM_EMM_BUF_236_inst_adr                                                   "0x016C"
#define CAM_EMM_EMM_BUF_237_inst_adr                                                   "0x016D"
#define CAM_EMM_EMM_BUF_238_inst_adr                                                   "0x016E"
#define CAM_EMM_EMM_BUF_239_inst_adr                                                   "0x016F"
#define CAM_EMM_EMM_BUF_240_inst_adr                                                   "0x0170"
#define CAM_EMM_EMM_BUF_241_inst_adr                                                   "0x0171"
#define CAM_EMM_EMM_BUF_242_inst_adr                                                   "0x0172"
#define CAM_EMM_EMM_BUF_243_inst_adr                                                   "0x0173"
#define CAM_EMM_EMM_BUF_244_inst_adr                                                   "0x0174"
#define CAM_EMM_EMM_BUF_245_inst_adr                                                   "0x0175"
#define CAM_EMM_EMM_BUF_246_inst_adr                                                   "0x0176"
#define CAM_EMM_EMM_BUF_247_inst_adr                                                   "0x0177"
#define CAM_EMM_EMM_BUF_248_inst_adr                                                   "0x0178"
#define CAM_EMM_EMM_BUF_249_inst_adr                                                   "0x0179"
#define CAM_EMM_EMM_BUF_250_inst_adr                                                   "0x017A"
#define CAM_EMM_EMM_BUF_251_inst_adr                                                   "0x017B"
#define CAM_EMM_EMM_BUF_252_inst_adr                                                   "0x017C"
#define CAM_EMM_EMM_BUF_253_inst_adr                                                   "0x017D"
#define CAM_EMM_EMM_BUF_254_inst_adr                                                   "0x017E"
#define CAM_EMM_EMM_BUF_255_inst_adr                                                   "0x017F"
#define CAM_EMM_EMM_BUF_256_inst_adr                                                   "0x0180"
#define CAM_EMM_EMM_BUF_257_inst_adr                                                   "0x0181"
#define CAM_EMM_EMM_BUF_258_inst_adr                                                   "0x0182"
#define CAM_EMM_EMM_BUF_259_inst_adr                                                   "0x0183"
#define CAM_EMM_EMM_BUF_260_inst_adr                                                   "0x0184"
#define CAM_EMM_EMM_BUF_261_inst_adr                                                   "0x0185"
#define CAM_EMM_EMM_BUF_262_inst_adr                                                   "0x0186"
#define CAM_EMM_EMM_BUF_263_inst_adr                                                   "0x0187"
#define CAM_EMM_EMM_BUF_264_inst_adr                                                   "0x0188"
#define CAM_EMM_EMM_BUF_265_inst_adr                                                   "0x0189"
#define CAM_EMM_EMM_BUF_266_inst_adr                                                   "0x018A"
#define CAM_EMM_EMM_BUF_267_inst_adr                                                   "0x018B"
#define CAM_EMM_EMM_BUF_268_inst_adr                                                   "0x018C"
#define CAM_EMM_EMM_BUF_269_inst_adr                                                   "0x018D"
#define CAM_EMM_EMM_BUF_270_inst_adr                                                   "0x018E"
#define CAM_EMM_EMM_BUF_271_inst_adr                                                   "0x018F"
#define CAM_EMM_EMM_BUF_272_inst_adr                                                   "0x0190"
#define CAM_EMM_EMM_BUF_273_inst_adr                                                   "0x0191"
#define CAM_EMM_EMM_BUF_274_inst_adr                                                   "0x0192"
#define CAM_EMM_EMM_BUF_275_inst_adr                                                   "0x0193"
#define CAM_EMM_EMM_BUF_276_inst_adr                                                   "0x0194"
#define CAM_EMM_EMM_BUF_277_inst_adr                                                   "0x0195"
#define CAM_EMM_EMM_BUF_278_inst_adr                                                   "0x0196"
#define CAM_EMM_EMM_BUF_279_inst_adr                                                   "0x0197"
#define CAM_EMM_EMM_BUF_280_inst_adr                                                   "0x0198"
#define CAM_EMM_EMM_BUF_281_inst_adr                                                   "0x0199"
#define CAM_EMM_EMM_BUF_282_inst_adr                                                   "0x019A"
#define CAM_EMM_EMM_BUF_283_inst_adr                                                   "0x019B"
#define CAM_EMM_EMM_BUF_284_inst_adr                                                   "0x019C"
#define CAM_EMM_EMM_BUF_285_inst_adr                                                   "0x019D"
#define CAM_EMM_EMM_BUF_286_inst_adr                                                   "0x019E"
#define CAM_EMM_EMM_BUF_287_inst_adr                                                   "0x019F"
#define CAM_EMM_EMM_BUF_288_inst_adr                                                   "0x01A0"
#define CAM_EMM_EMM_BUF_289_inst_adr                                                   "0x01A1"
#define CAM_EMM_EMM_BUF_290_inst_adr                                                   "0x01A2"
#define CAM_EMM_EMM_BUF_291_inst_adr                                                   "0x01A3"
#define CAM_EMM_EMM_BUF_292_inst_adr                                                   "0x01A4"
#define CAM_EMM_EMM_BUF_293_inst_adr                                                   "0x01A5"
#define CAM_EMM_EMM_BUF_294_inst_adr                                                   "0x01A6"
#define CAM_EMM_EMM_BUF_295_inst_adr                                                   "0x01A7"
#define CAM_EMM_EMM_BUF_296_inst_adr                                                   "0x01A8"
#define CAM_EMM_EMM_BUF_297_inst_adr                                                   "0x01A9"
#define CAM_EMM_EMM_BUF_298_inst_adr                                                   "0x01AA"
#define CAM_EMM_EMM_BUF_299_inst_adr                                                   "0x01AB"
#define CAM_EMM_EMM_BUF_300_inst_adr                                                   "0x01AC"
#define CAM_EMM_EMM_BUF_301_inst_adr                                                   "0x01AD"
#define CAM_EMM_EMM_BUF_302_inst_adr                                                   "0x01AE"
#define CAM_EMM_EMM_BUF_303_inst_adr                                                   "0x01AF"
#define CAM_EMM_EMM_BUF_304_inst_adr                                                   "0x01B0"
#define CAM_EMM_EMM_BUF_305_inst_adr                                                   "0x01B1"
#define CAM_EMM_EMM_BUF_306_inst_adr                                                   "0x01B2"
#define CAM_EMM_EMM_BUF_307_inst_adr                                                   "0x01B3"
#define CAM_EMM_EMM_BUF_308_inst_adr                                                   "0x01B4"
#define CAM_EMM_EMM_BUF_309_inst_adr                                                   "0x01B5"
#define CAM_EMM_EMM_BUF_310_inst_adr                                                   "0x01B6"
#define CAM_EMM_EMM_BUF_311_inst_adr                                                   "0x01B7"
#define CAM_EMM_EMM_BUF_312_inst_adr                                                   "0x01B8"
#define CAM_EMM_EMM_BUF_313_inst_adr                                                   "0x01B9"
#define CAM_EMM_EMM_BUF_314_inst_adr                                                   "0x01BA"
#define CAM_EMM_EMM_BUF_315_inst_adr                                                   "0x01BB"
#define CAM_EMM_EMM_BUF_316_inst_adr                                                   "0x01BC"
#define CAM_EMM_EMM_BUF_317_inst_adr                                                   "0x01BD"
#define CAM_EMM_EMM_BUF_318_inst_adr                                                   "0x01BE"
#define CAM_EMM_EMM_BUF_319_inst_adr                                                   "0x01BF"
#define CAM_EMM_EMM_BUF_320_inst_adr                                                   "0x01C0"
#define CAM_EMM_EMM_BUF_321_inst_adr                                                   "0x01C1"
#define CAM_EMM_EMM_BUF_322_inst_adr                                                   "0x01C2"
#define CAM_EMM_EMM_BUF_323_inst_adr                                                   "0x01C3"
#define CAM_EMM_EMM_BUF_324_inst_adr                                                   "0x01C4"
#define CAM_EMM_EMM_BUF_325_inst_adr                                                   "0x01C5"
#define CAM_EMM_EMM_BUF_326_inst_adr                                                   "0x01C6"
#define CAM_EMM_EMM_BUF_327_inst_adr                                                   "0x01C7"
#define CAM_EMM_EMM_BUF_328_inst_adr                                                   "0x01C8"
#define CAM_EMM_EMM_BUF_329_inst_adr                                                   "0x01C9"
#define CAM_EMM_EMM_BUF_330_inst_adr                                                   "0x01CA"
#define CAM_EMM_EMM_BUF_331_inst_adr                                                   "0x01CB"
#define CAM_EMM_EMM_BUF_332_inst_adr                                                   "0x01CC"
#define CAM_EMM_EMM_BUF_333_inst_adr                                                   "0x01CD"
#define CAM_EMM_EMM_BUF_334_inst_adr                                                   "0x01CE"
#define CAM_EMM_EMM_BUF_335_inst_adr                                                   "0x01CF"
#define CAM_EMM_EMM_BUF_336_inst_adr                                                   "0x01D0"
#define CAM_EMM_EMM_BUF_337_inst_adr                                                   "0x01D1"
#define CAM_EMM_EMM_BUF_338_inst_adr                                                   "0x01D2"
#define CAM_EMM_EMM_BUF_339_inst_adr                                                   "0x01D3"
#define CAM_EMM_EMM_BUF_340_inst_adr                                                   "0x01D4"
#define CAM_EMM_EMM_BUF_341_inst_adr                                                   "0x01D5"
#define CAM_EMM_EMM_BUF_342_inst_adr                                                   "0x01D6"
#define CAM_EMM_EMM_BUF_343_inst_adr                                                   "0x01D7"
#define CAM_EMM_EMM_BUF_344_inst_adr                                                   "0x01D8"
#define CAM_EMM_EMM_BUF_345_inst_adr                                                   "0x01D9"
#define CAM_EMM_EMM_BUF_346_inst_adr                                                   "0x01DA"
#define CAM_EMM_EMM_BUF_347_inst_adr                                                   "0x01DB"
#define CAM_EMM_EMM_BUF_348_inst_adr                                                   "0x01DC"
#define CAM_EMM_EMM_BUF_349_inst_adr                                                   "0x01DD"
#define CAM_EMM_EMM_BUF_350_inst_adr                                                   "0x01DE"
#define CAM_EMM_EMM_BUF_351_inst_adr                                                   "0x01DF"
#define CAM_EMM_EMM_BUF_352_inst_adr                                                   "0x01E0"
#define CAM_EMM_EMM_BUF_353_inst_adr                                                   "0x01E1"
#define CAM_EMM_EMM_BUF_354_inst_adr                                                   "0x01E2"
#define CAM_EMM_EMM_BUF_355_inst_adr                                                   "0x01E3"
#define CAM_EMM_EMM_BUF_356_inst_adr                                                   "0x01E4"
#define CAM_EMM_EMM_BUF_357_inst_adr                                                   "0x01E5"
#define CAM_EMM_EMM_BUF_358_inst_adr                                                   "0x01E6"
#define CAM_EMM_EMM_BUF_359_inst_adr                                                   "0x01E7"
#define CAM_EMM_EMM_BUF_360_inst_adr                                                   "0x01E8"
#define CAM_EMM_EMM_BUF_361_inst_adr                                                   "0x01E9"
#define CAM_EMM_EMM_BUF_362_inst_adr                                                   "0x01EA"
#define CAM_EMM_EMM_BUF_363_inst_adr                                                   "0x01EB"
#define CAM_EMM_EMM_BUF_364_inst_adr                                                   "0x01EC"
#define CAM_EMM_EMM_BUF_365_inst_adr                                                   "0x01ED"
#define CAM_EMM_EMM_BUF_366_inst_adr                                                   "0x01EE"
#define CAM_EMM_EMM_BUF_367_inst_adr                                                   "0x01EF"
#define CAM_EMM_EMM_BUF_368_inst_adr                                                   "0x01F0"
#define CAM_EMM_EMM_BUF_369_inst_adr                                                   "0x01F1"
#define CAM_EMM_EMM_BUF_370_inst_adr                                                   "0x01F2"
#define CAM_EMM_EMM_BUF_371_inst_adr                                                   "0x01F3"
#define CAM_EMM_EMM_BUF_372_inst_adr                                                   "0x01F4"
#define CAM_EMM_EMM_BUF_373_inst_adr                                                   "0x01F5"
#define CAM_EMM_EMM_BUF_374_inst_adr                                                   "0x01F6"
#define CAM_EMM_EMM_BUF_375_inst_adr                                                   "0x01F7"
#define CAM_EMM_EMM_BUF_376_inst_adr                                                   "0x01F8"
#define CAM_EMM_EMM_BUF_377_inst_adr                                                   "0x01F9"
#define CAM_EMM_EMM_BUF_378_inst_adr                                                   "0x01FA"
#define CAM_EMM_EMM_BUF_379_inst_adr                                                   "0x01FB"
#define CAM_EMM_EMM_BUF_380_inst_adr                                                   "0x01FC"
#define CAM_EMM_EMM_BUF_381_inst_adr                                                   "0x01FD"
#define CAM_EMM_EMM_BUF_382_inst_adr                                                   "0x01FE"
#define CAM_EMM_EMM_BUF_383_inst_adr                                                   "0x01FF"
#define CAM_EMM_EMM_BUF_384_inst_adr                                                   "0x0200"
#define CAM_EMM_EMM_BUF_385_inst_adr                                                   "0x0201"
#define CAM_EMM_EMM_BUF_386_inst_adr                                                   "0x0202"
#define CAM_EMM_EMM_BUF_387_inst_adr                                                   "0x0203"
#define CAM_EMM_EMM_BUF_388_inst_adr                                                   "0x0204"
#define CAM_EMM_EMM_BUF_389_inst_adr                                                   "0x0205"
#define CAM_EMM_EMM_BUF_390_inst_adr                                                   "0x0206"
#define CAM_EMM_EMM_BUF_391_inst_adr                                                   "0x0207"
#define CAM_EMM_EMM_BUF_392_inst_adr                                                   "0x0208"
#define CAM_EMM_EMM_BUF_393_inst_adr                                                   "0x0209"
#define CAM_EMM_EMM_BUF_394_inst_adr                                                   "0x020A"
#define CAM_EMM_EMM_BUF_395_inst_adr                                                   "0x020B"
#define CAM_EMM_EMM_BUF_396_inst_adr                                                   "0x020C"
#define CAM_EMM_EMM_BUF_397_inst_adr                                                   "0x020D"
#define CAM_EMM_EMM_BUF_398_inst_adr                                                   "0x020E"
#define CAM_EMM_EMM_BUF_399_inst_adr                                                   "0x020F"
#define CAM_EMM_EMM_BUF_400_inst_adr                                                   "0x0210"
#define CAM_EMM_EMM_BUF_401_inst_adr                                                   "0x0211"
#define CAM_EMM_EMM_BUF_402_inst_adr                                                   "0x0212"
#define CAM_EMM_EMM_BUF_403_inst_adr                                                   "0x0213"
#define CAM_EMM_EMM_BUF_404_inst_adr                                                   "0x0214"
#define CAM_EMM_EMM_BUF_405_inst_adr                                                   "0x0215"
#define CAM_EMM_EMM_BUF_406_inst_adr                                                   "0x0216"
#define CAM_EMM_EMM_BUF_407_inst_adr                                                   "0x0217"
#define CAM_EMM_EMM_BUF_408_inst_adr                                                   "0x0218"
#define CAM_EMM_EMM_BUF_409_inst_adr                                                   "0x0219"
#define CAM_EMM_EMM_BUF_410_inst_adr                                                   "0x021A"
#define CAM_EMM_EMM_BUF_411_inst_adr                                                   "0x021B"
#define CAM_EMM_EMM_BUF_412_inst_adr                                                   "0x021C"
#define CAM_EMM_EMM_BUF_413_inst_adr                                                   "0x021D"
#define CAM_EMM_EMM_BUF_414_inst_adr                                                   "0x021E"
#define CAM_EMM_EMM_BUF_415_inst_adr                                                   "0x021F"
#define CAM_EMM_EMM_BUF_416_inst_adr                                                   "0x0220"
#define CAM_EMM_EMM_BUF_417_inst_adr                                                   "0x0221"
#define CAM_EMM_EMM_BUF_418_inst_adr                                                   "0x0222"
#define CAM_EMM_EMM_BUF_419_inst_adr                                                   "0x0223"
#define CAM_EMM_EMM_BUF_420_inst_adr                                                   "0x0224"
#define CAM_EMM_EMM_BUF_421_inst_adr                                                   "0x0225"
#define CAM_EMM_EMM_BUF_422_inst_adr                                                   "0x0226"
#define CAM_EMM_EMM_BUF_423_inst_adr                                                   "0x0227"
#define CAM_EMM_EMM_BUF_424_inst_adr                                                   "0x0228"
#define CAM_EMM_EMM_BUF_425_inst_adr                                                   "0x0229"
#define CAM_EMM_EMM_BUF_426_inst_adr                                                   "0x022A"
#define CAM_EMM_EMM_BUF_427_inst_adr                                                   "0x022B"
#define CAM_EMM_EMM_BUF_428_inst_adr                                                   "0x022C"
#define CAM_EMM_EMM_BUF_429_inst_adr                                                   "0x022D"
#define CAM_EMM_EMM_BUF_430_inst_adr                                                   "0x022E"
#define CAM_EMM_EMM_BUF_431_inst_adr                                                   "0x022F"
#define CAM_EMM_EMM_BUF_432_inst_adr                                                   "0x0230"
#define CAM_EMM_EMM_BUF_433_inst_adr                                                   "0x0231"
#define CAM_EMM_EMM_BUF_434_inst_adr                                                   "0x0232"
#define CAM_EMM_EMM_BUF_435_inst_adr                                                   "0x0233"
#define CAM_EMM_EMM_BUF_436_inst_adr                                                   "0x0234"
#define CAM_EMM_EMM_BUF_437_inst_adr                                                   "0x0235"
#define CAM_EMM_EMM_BUF_438_inst_adr                                                   "0x0236"
#define CAM_EMM_EMM_BUF_439_inst_adr                                                   "0x0237"
#define CAM_EMM_EMM_BUF_440_inst_adr                                                   "0x0238"
#define CAM_EMM_EMM_BUF_441_inst_adr                                                   "0x0239"
#define CAM_EMM_EMM_BUF_442_inst_adr                                                   "0x023A"
#define CAM_EMM_EMM_BUF_443_inst_adr                                                   "0x023B"
#define CAM_EMM_EMM_BUF_444_inst_adr                                                   "0x023C"
#define CAM_EMM_EMM_BUF_445_inst_adr                                                   "0x023D"
#define CAM_EMM_EMM_BUF_446_inst_adr                                                   "0x023E"
#define CAM_EMM_EMM_BUF_447_inst_adr                                                   "0x023F"
#define CAM_EMM_EMM_BUF_448_inst_adr                                                   "0x0240"
#define CAM_EMM_EMM_BUF_449_inst_adr                                                   "0x0241"
#define CAM_EMM_EMM_BUF_450_inst_adr                                                   "0x0242"
#define CAM_EMM_EMM_BUF_451_inst_adr                                                   "0x0243"
#define CAM_EMM_EMM_BUF_452_inst_adr                                                   "0x0244"
#define CAM_EMM_EMM_BUF_453_inst_adr                                                   "0x0245"
#define CAM_EMM_EMM_BUF_454_inst_adr                                                   "0x0246"
#define CAM_EMM_EMM_BUF_455_inst_adr                                                   "0x0247"
#define CAM_EMM_EMM_BUF_456_inst_adr                                                   "0x0248"
#define CAM_EMM_EMM_BUF_457_inst_adr                                                   "0x0249"
#define CAM_EMM_EMM_BUF_458_inst_adr                                                   "0x024A"
#define CAM_EMM_EMM_BUF_459_inst_adr                                                   "0x024B"
#define CAM_EMM_EMM_BUF_460_inst_adr                                                   "0x024C"
#define CAM_EMM_EMM_BUF_461_inst_adr                                                   "0x024D"
#define CAM_EMM_EMM_BUF_462_inst_adr                                                   "0x024E"
#define CAM_EMM_EMM_BUF_463_inst_adr                                                   "0x024F"
#define CAM_EMM_EMM_BUF_464_inst_adr                                                   "0x0250"
#define CAM_EMM_EMM_BUF_465_inst_adr                                                   "0x0251"
#define CAM_EMM_EMM_BUF_466_inst_adr                                                   "0x0252"
#define CAM_EMM_EMM_BUF_467_inst_adr                                                   "0x0253"
#define CAM_EMM_EMM_BUF_468_inst_adr                                                   "0x0254"
#define CAM_EMM_EMM_BUF_469_inst_adr                                                   "0x0255"
#define CAM_EMM_EMM_BUF_470_inst_adr                                                   "0x0256"
#define CAM_EMM_EMM_BUF_471_inst_adr                                                   "0x0257"
#define CAM_EMM_EMM_BUF_472_inst_adr                                                   "0x0258"
#define CAM_EMM_EMM_BUF_473_inst_adr                                                   "0x0259"
#define CAM_EMM_EMM_BUF_474_inst_adr                                                   "0x025A"
#define CAM_EMM_EMM_BUF_475_inst_adr                                                   "0x025B"
#define CAM_EMM_EMM_BUF_476_inst_adr                                                   "0x025C"
#define CAM_EMM_EMM_BUF_477_inst_adr                                                   "0x025D"
#define CAM_EMM_EMM_BUF_478_inst_adr                                                   "0x025E"
#define CAM_EMM_EMM_BUF_479_inst_adr                                                   "0x025F"
#define CAM_EMM_EMM_BUF_480_inst_adr                                                   "0x0260"
#define CAM_EMM_EMM_BUF_481_inst_adr                                                   "0x0261"
#define CAM_EMM_EMM_BUF_482_inst_adr                                                   "0x0262"
#define CAM_EMM_EMM_BUF_483_inst_adr                                                   "0x0263"
#define CAM_EMM_EMM_BUF_484_inst_adr                                                   "0x0264"
#define CAM_EMM_EMM_BUF_485_inst_adr                                                   "0x0265"
#define CAM_EMM_EMM_BUF_486_inst_adr                                                   "0x0266"
#define CAM_EMM_EMM_BUF_487_inst_adr                                                   "0x0267"
#define CAM_EMM_EMM_BUF_488_inst_adr                                                   "0x0268"
#define CAM_EMM_EMM_BUF_489_inst_adr                                                   "0x0269"
#define CAM_EMM_EMM_BUF_490_inst_adr                                                   "0x026A"
#define CAM_EMM_EMM_BUF_491_inst_adr                                                   "0x026B"
#define CAM_EMM_EMM_BUF_492_inst_adr                                                   "0x026C"
#define CAM_EMM_EMM_BUF_493_inst_adr                                                   "0x026D"
#define CAM_EMM_EMM_BUF_494_inst_adr                                                   "0x026E"
#define CAM_EMM_EMM_BUF_495_inst_adr                                                   "0x026F"
#define CAM_EMM_EMM_BUF_496_inst_adr                                                   "0x0270"
#define CAM_EMM_EMM_BUF_497_inst_adr                                                   "0x0271"
#define CAM_EMM_EMM_BUF_498_inst_adr                                                   "0x0272"
#define CAM_EMM_EMM_BUF_499_inst_adr                                                   "0x0273"
#define CAM_EMM_EMM_BUF_500_inst_adr                                                   "0x0274"
#define CAM_EMM_EMM_BUF_501_inst_adr                                                   "0x0275"
#define CAM_EMM_EMM_BUF_502_inst_adr                                                   "0x0276"
#define CAM_EMM_EMM_BUF_503_inst_adr                                                   "0x0277"
#define CAM_EMM_EMM_BUF_504_inst_adr                                                   "0x0278"
#define CAM_EMM_EMM_BUF_505_inst_adr                                                   "0x0279"
#define CAM_EMM_EMM_BUF_506_inst_adr                                                   "0x027A"
#define CAM_EMM_EMM_BUF_507_inst_adr                                                   "0x027B"
#define CAM_EMM_EMM_BUF_508_inst_adr                                                   "0x027C"
#define CAM_EMM_EMM_BUF_509_inst_adr                                                   "0x027D"
#define CAM_EMM_EMM_BUF_510_inst_adr                                                   "0x027E"
#define CAM_EMM_EMM_BUF_511_inst_adr                                                   "0x027F"
#define CAM_EMM_EMM_BUF_512_inst_adr                                                   "0x0280"
#define CAM_EMM_EMM_BUF_513_inst_adr                                                   "0x0281"
#define CAM_EMM_EMM_BUF_514_inst_adr                                                   "0x0282"
#define CAM_EMM_EMM_BUF_515_inst_adr                                                   "0x0283"
#define CAM_EMM_EMM_BUF_516_inst_adr                                                   "0x0284"
#define CAM_EMM_EMM_BUF_517_inst_adr                                                   "0x0285"
#define CAM_EMM_EMM_BUF_518_inst_adr                                                   "0x0286"
#define CAM_EMM_EMM_BUF_519_inst_adr                                                   "0x0287"
#define CAM_EMM_EMM_BUF_520_inst_adr                                                   "0x0288"
#define CAM_EMM_EMM_BUF_521_inst_adr                                                   "0x0289"
#define CAM_EMM_EMM_BUF_522_inst_adr                                                   "0x028A"
#define CAM_EMM_EMM_BUF_523_inst_adr                                                   "0x028B"
#define CAM_EMM_EMM_BUF_524_inst_adr                                                   "0x028C"
#define CAM_EMM_EMM_BUF_525_inst_adr                                                   "0x028D"
#define CAM_EMM_EMM_BUF_526_inst_adr                                                   "0x028E"
#define CAM_EMM_EMM_BUF_527_inst_adr                                                   "0x028F"
#define CAM_EMM_EMM_BUF_528_inst_adr                                                   "0x0290"
#define CAM_EMM_EMM_BUF_529_inst_adr                                                   "0x0291"
#define CAM_EMM_EMM_BUF_530_inst_adr                                                   "0x0292"
#define CAM_EMM_EMM_BUF_531_inst_adr                                                   "0x0293"
#define CAM_EMM_EMM_BUF_532_inst_adr                                                   "0x0294"
#define CAM_EMM_EMM_BUF_533_inst_adr                                                   "0x0295"
#define CAM_EMM_EMM_BUF_534_inst_adr                                                   "0x0296"
#define CAM_EMM_EMM_BUF_535_inst_adr                                                   "0x0297"
#define CAM_EMM_EMM_BUF_536_inst_adr                                                   "0x0298"
#define CAM_EMM_EMM_BUF_537_inst_adr                                                   "0x0299"
#define CAM_EMM_EMM_BUF_538_inst_adr                                                   "0x029A"
#define CAM_EMM_EMM_BUF_539_inst_adr                                                   "0x029B"
#define CAM_EMM_EMM_BUF_540_inst_adr                                                   "0x029C"
#define CAM_EMM_EMM_BUF_541_inst_adr                                                   "0x029D"
#define CAM_EMM_EMM_BUF_542_inst_adr                                                   "0x029E"
#define CAM_EMM_EMM_BUF_543_inst_adr                                                   "0x029F"
#define CAM_EMM_EMM_BUF_544_inst_adr                                                   "0x02A0"
#define CAM_EMM_EMM_BUF_545_inst_adr                                                   "0x02A1"
#define CAM_EMM_EMM_BUF_546_inst_adr                                                   "0x02A2"
#define CAM_EMM_EMM_BUF_547_inst_adr                                                   "0x02A3"
#define CAM_EMM_EMM_BUF_548_inst_adr                                                   "0x02A4"
#define CAM_EMM_EMM_BUF_549_inst_adr                                                   "0x02A5"
#define CAM_EMM_EMM_BUF_550_inst_adr                                                   "0x02A6"
#define CAM_EMM_EMM_BUF_551_inst_adr                                                   "0x02A7"
#define CAM_EMM_EMM_BUF_552_inst_adr                                                   "0x02A8"
#define CAM_EMM_EMM_BUF_553_inst_adr                                                   "0x02A9"
#define CAM_EMM_EMM_BUF_554_inst_adr                                                   "0x02AA"
#define CAM_EMM_EMM_BUF_555_inst_adr                                                   "0x02AB"
#define CAM_EMM_EMM_BUF_556_inst_adr                                                   "0x02AC"
#define CAM_EMM_EMM_BUF_557_inst_adr                                                   "0x02AD"
#define CAM_EMM_EMM_BUF_558_inst_adr                                                   "0x02AE"
#define CAM_EMM_EMM_BUF_559_inst_adr                                                   "0x02AF"
#define CAM_EMM_EMM_BUF_560_inst_adr                                                   "0x02B0"
#define CAM_EMM_EMM_BUF_561_inst_adr                                                   "0x02B1"
#define CAM_EMM_EMM_BUF_562_inst_adr                                                   "0x02B2"
#define CAM_EMM_EMM_BUF_563_inst_adr                                                   "0x02B3"
#define CAM_EMM_EMM_BUF_564_inst_adr                                                   "0x02B4"
#define CAM_EMM_EMM_BUF_565_inst_adr                                                   "0x02B5"
#define CAM_EMM_EMM_BUF_566_inst_adr                                                   "0x02B6"
#define CAM_EMM_EMM_BUF_567_inst_adr                                                   "0x02B7"
#define CAM_EMM_EMM_BUF_568_inst_adr                                                   "0x02B8"
#define CAM_EMM_EMM_BUF_569_inst_adr                                                   "0x02B9"
#define CAM_EMM_EMM_BUF_570_inst_adr                                                   "0x02BA"
#define CAM_EMM_EMM_BUF_571_inst_adr                                                   "0x02BB"
#define CAM_EMM_EMM_BUF_572_inst_adr                                                   "0x02BC"
#define CAM_EMM_EMM_BUF_573_inst_adr                                                   "0x02BD"
#define CAM_EMM_EMM_BUF_574_inst_adr                                                   "0x02BE"
#define CAM_EMM_EMM_BUF_575_inst_adr                                                   "0x02BF"
#define CAM_EMM_EMM_BUF_576_inst_adr                                                   "0x02C0"
#define CAM_EMM_EMM_BUF_577_inst_adr                                                   "0x02C1"
#define CAM_EMM_EMM_BUF_578_inst_adr                                                   "0x02C2"
#define CAM_EMM_EMM_BUF_579_inst_adr                                                   "0x02C3"
#define CAM_EMM_EMM_BUF_580_inst_adr                                                   "0x02C4"
#define CAM_EMM_EMM_BUF_581_inst_adr                                                   "0x02C5"
#define CAM_EMM_EMM_BUF_582_inst_adr                                                   "0x02C6"
#define CAM_EMM_EMM_BUF_583_inst_adr                                                   "0x02C7"
#define CAM_EMM_EMM_BUF_584_inst_adr                                                   "0x02C8"
#define CAM_EMM_EMM_BUF_585_inst_adr                                                   "0x02C9"
#define CAM_EMM_EMM_BUF_586_inst_adr                                                   "0x02CA"
#define CAM_EMM_EMM_BUF_587_inst_adr                                                   "0x02CB"
#define CAM_EMM_EMM_BUF_588_inst_adr                                                   "0x02CC"
#define CAM_EMM_EMM_BUF_589_inst_adr                                                   "0x02CD"
#define CAM_EMM_EMM_BUF_590_inst_adr                                                   "0x02CE"
#define CAM_EMM_EMM_BUF_591_inst_adr                                                   "0x02CF"
#define CAM_EMM_EMM_BUF_592_inst_adr                                                   "0x02D0"
#define CAM_EMM_EMM_BUF_593_inst_adr                                                   "0x02D1"
#define CAM_EMM_EMM_BUF_594_inst_adr                                                   "0x02D2"
#define CAM_EMM_EMM_BUF_595_inst_adr                                                   "0x02D3"
#define CAM_EMM_EMM_BUF_596_inst_adr                                                   "0x02D4"
#define CAM_EMM_EMM_BUF_597_inst_adr                                                   "0x02D5"
#define CAM_EMM_EMM_BUF_598_inst_adr                                                   "0x02D6"
#define CAM_EMM_EMM_BUF_599_inst_adr                                                   "0x02D7"
#define CAM_EMM_EMM_BUF_600_inst_adr                                                   "0x02D8"
#define CAM_EMM_EMM_BUF_601_inst_adr                                                   "0x02D9"
#define CAM_EMM_EMM_BUF_602_inst_adr                                                   "0x02DA"
#define CAM_EMM_EMM_BUF_603_inst_adr                                                   "0x02DB"
#define CAM_EMM_EMM_BUF_604_inst_adr                                                   "0x02DC"
#define CAM_EMM_EMM_BUF_605_inst_adr                                                   "0x02DD"
#define CAM_EMM_EMM_BUF_606_inst_adr                                                   "0x02DE"
#define CAM_EMM_EMM_BUF_607_inst_adr                                                   "0x02DF"
#define CAM_EMM_EMM_BUF_608_inst_adr                                                   "0x02E0"
#define CAM_EMM_EMM_BUF_609_inst_adr                                                   "0x02E1"
#define CAM_EMM_EMM_BUF_610_inst_adr                                                   "0x02E2"
#define CAM_EMM_EMM_BUF_611_inst_adr                                                   "0x02E3"
#define CAM_EMM_EMM_BUF_612_inst_adr                                                   "0x02E4"
#define CAM_EMM_EMM_BUF_613_inst_adr                                                   "0x02E5"
#define CAM_EMM_EMM_BUF_614_inst_adr                                                   "0x02E6"
#define CAM_EMM_EMM_BUF_615_inst_adr                                                   "0x02E7"
#define CAM_EMM_EMM_BUF_616_inst_adr                                                   "0x02E8"
#define CAM_EMM_EMM_BUF_617_inst_adr                                                   "0x02E9"
#define CAM_EMM_EMM_BUF_618_inst_adr                                                   "0x02EA"
#define CAM_EMM_EMM_BUF_619_inst_adr                                                   "0x02EB"
#define CAM_EMM_EMM_BUF_620_inst_adr                                                   "0x02EC"
#define CAM_EMM_EMM_BUF_621_inst_adr                                                   "0x02ED"
#define CAM_EMM_EMM_BUF_622_inst_adr                                                   "0x02EE"
#define CAM_EMM_EMM_BUF_623_inst_adr                                                   "0x02EF"
#define CAM_EMM_EMM_BUF_624_inst_adr                                                   "0x02F0"
#define CAM_EMM_EMM_BUF_625_inst_adr                                                   "0x02F1"
#define CAM_EMM_EMM_BUF_626_inst_adr                                                   "0x02F2"
#define CAM_EMM_EMM_BUF_627_inst_adr                                                   "0x02F3"
#define CAM_EMM_EMM_BUF_628_inst_adr                                                   "0x02F4"
#define CAM_EMM_EMM_BUF_629_inst_adr                                                   "0x02F5"
#define CAM_EMM_EMM_BUF_630_inst_adr                                                   "0x02F6"
#define CAM_EMM_EMM_BUF_631_inst_adr                                                   "0x02F7"
#define CAM_EMM_EMM_BUF_632_inst_adr                                                   "0x02F8"
#define CAM_EMM_EMM_BUF_633_inst_adr                                                   "0x02F9"
#define CAM_EMM_EMM_BUF_634_inst_adr                                                   "0x02FA"
#define CAM_EMM_EMM_BUF_635_inst_adr                                                   "0x02FB"
#define CAM_EMM_EMM_BUF_636_inst_adr                                                   "0x02FC"
#define CAM_EMM_EMM_BUF_637_inst_adr                                                   "0x02FD"
#define CAM_EMM_EMM_BUF_638_inst_adr                                                   "0x02FE"
#define CAM_EMM_EMM_BUF_639_inst_adr                                                   "0x02FF"
#define CAM_EMM_EMM_BUF_0_inst                                                       0x0080
#define CAM_EMM_EMM_BUF_1_inst                                                       0x0081
#define CAM_EMM_EMM_BUF_2_inst                                                       0x0082
#define CAM_EMM_EMM_BUF_3_inst                                                       0x0083
#define CAM_EMM_EMM_BUF_4_inst                                                       0x0084
#define CAM_EMM_EMM_BUF_5_inst                                                       0x0085
#define CAM_EMM_EMM_BUF_6_inst                                                       0x0086
#define CAM_EMM_EMM_BUF_7_inst                                                       0x0087
#define CAM_EMM_EMM_BUF_8_inst                                                       0x0088
#define CAM_EMM_EMM_BUF_9_inst                                                       0x0089
#define CAM_EMM_EMM_BUF_10_inst                                                       0x008A
#define CAM_EMM_EMM_BUF_11_inst                                                       0x008B
#define CAM_EMM_EMM_BUF_12_inst                                                       0x008C
#define CAM_EMM_EMM_BUF_13_inst                                                       0x008D
#define CAM_EMM_EMM_BUF_14_inst                                                       0x008E
#define CAM_EMM_EMM_BUF_15_inst                                                       0x008F
#define CAM_EMM_EMM_BUF_16_inst                                                       0x0090
#define CAM_EMM_EMM_BUF_17_inst                                                       0x0091
#define CAM_EMM_EMM_BUF_18_inst                                                       0x0092
#define CAM_EMM_EMM_BUF_19_inst                                                       0x0093
#define CAM_EMM_EMM_BUF_20_inst                                                       0x0094
#define CAM_EMM_EMM_BUF_21_inst                                                       0x0095
#define CAM_EMM_EMM_BUF_22_inst                                                       0x0096
#define CAM_EMM_EMM_BUF_23_inst                                                       0x0097
#define CAM_EMM_EMM_BUF_24_inst                                                       0x0098
#define CAM_EMM_EMM_BUF_25_inst                                                       0x0099
#define CAM_EMM_EMM_BUF_26_inst                                                       0x009A
#define CAM_EMM_EMM_BUF_27_inst                                                       0x009B
#define CAM_EMM_EMM_BUF_28_inst                                                       0x009C
#define CAM_EMM_EMM_BUF_29_inst                                                       0x009D
#define CAM_EMM_EMM_BUF_30_inst                                                       0x009E
#define CAM_EMM_EMM_BUF_31_inst                                                       0x009F
#define CAM_EMM_EMM_BUF_32_inst                                                       0x00A0
#define CAM_EMM_EMM_BUF_33_inst                                                       0x00A1
#define CAM_EMM_EMM_BUF_34_inst                                                       0x00A2
#define CAM_EMM_EMM_BUF_35_inst                                                       0x00A3
#define CAM_EMM_EMM_BUF_36_inst                                                       0x00A4
#define CAM_EMM_EMM_BUF_37_inst                                                       0x00A5
#define CAM_EMM_EMM_BUF_38_inst                                                       0x00A6
#define CAM_EMM_EMM_BUF_39_inst                                                       0x00A7
#define CAM_EMM_EMM_BUF_40_inst                                                       0x00A8
#define CAM_EMM_EMM_BUF_41_inst                                                       0x00A9
#define CAM_EMM_EMM_BUF_42_inst                                                       0x00AA
#define CAM_EMM_EMM_BUF_43_inst                                                       0x00AB
#define CAM_EMM_EMM_BUF_44_inst                                                       0x00AC
#define CAM_EMM_EMM_BUF_45_inst                                                       0x00AD
#define CAM_EMM_EMM_BUF_46_inst                                                       0x00AE
#define CAM_EMM_EMM_BUF_47_inst                                                       0x00AF
#define CAM_EMM_EMM_BUF_48_inst                                                       0x00B0
#define CAM_EMM_EMM_BUF_49_inst                                                       0x00B1
#define CAM_EMM_EMM_BUF_50_inst                                                       0x00B2
#define CAM_EMM_EMM_BUF_51_inst                                                       0x00B3
#define CAM_EMM_EMM_BUF_52_inst                                                       0x00B4
#define CAM_EMM_EMM_BUF_53_inst                                                       0x00B5
#define CAM_EMM_EMM_BUF_54_inst                                                       0x00B6
#define CAM_EMM_EMM_BUF_55_inst                                                       0x00B7
#define CAM_EMM_EMM_BUF_56_inst                                                       0x00B8
#define CAM_EMM_EMM_BUF_57_inst                                                       0x00B9
#define CAM_EMM_EMM_BUF_58_inst                                                       0x00BA
#define CAM_EMM_EMM_BUF_59_inst                                                       0x00BB
#define CAM_EMM_EMM_BUF_60_inst                                                       0x00BC
#define CAM_EMM_EMM_BUF_61_inst                                                       0x00BD
#define CAM_EMM_EMM_BUF_62_inst                                                       0x00BE
#define CAM_EMM_EMM_BUF_63_inst                                                       0x00BF
#define CAM_EMM_EMM_BUF_64_inst                                                       0x00C0
#define CAM_EMM_EMM_BUF_65_inst                                                       0x00C1
#define CAM_EMM_EMM_BUF_66_inst                                                       0x00C2
#define CAM_EMM_EMM_BUF_67_inst                                                       0x00C3
#define CAM_EMM_EMM_BUF_68_inst                                                       0x00C4
#define CAM_EMM_EMM_BUF_69_inst                                                       0x00C5
#define CAM_EMM_EMM_BUF_70_inst                                                       0x00C6
#define CAM_EMM_EMM_BUF_71_inst                                                       0x00C7
#define CAM_EMM_EMM_BUF_72_inst                                                       0x00C8
#define CAM_EMM_EMM_BUF_73_inst                                                       0x00C9
#define CAM_EMM_EMM_BUF_74_inst                                                       0x00CA
#define CAM_EMM_EMM_BUF_75_inst                                                       0x00CB
#define CAM_EMM_EMM_BUF_76_inst                                                       0x00CC
#define CAM_EMM_EMM_BUF_77_inst                                                       0x00CD
#define CAM_EMM_EMM_BUF_78_inst                                                       0x00CE
#define CAM_EMM_EMM_BUF_79_inst                                                       0x00CF
#define CAM_EMM_EMM_BUF_80_inst                                                       0x00D0
#define CAM_EMM_EMM_BUF_81_inst                                                       0x00D1
#define CAM_EMM_EMM_BUF_82_inst                                                       0x00D2
#define CAM_EMM_EMM_BUF_83_inst                                                       0x00D3
#define CAM_EMM_EMM_BUF_84_inst                                                       0x00D4
#define CAM_EMM_EMM_BUF_85_inst                                                       0x00D5
#define CAM_EMM_EMM_BUF_86_inst                                                       0x00D6
#define CAM_EMM_EMM_BUF_87_inst                                                       0x00D7
#define CAM_EMM_EMM_BUF_88_inst                                                       0x00D8
#define CAM_EMM_EMM_BUF_89_inst                                                       0x00D9
#define CAM_EMM_EMM_BUF_90_inst                                                       0x00DA
#define CAM_EMM_EMM_BUF_91_inst                                                       0x00DB
#define CAM_EMM_EMM_BUF_92_inst                                                       0x00DC
#define CAM_EMM_EMM_BUF_93_inst                                                       0x00DD
#define CAM_EMM_EMM_BUF_94_inst                                                       0x00DE
#define CAM_EMM_EMM_BUF_95_inst                                                       0x00DF
#define CAM_EMM_EMM_BUF_96_inst                                                       0x00E0
#define CAM_EMM_EMM_BUF_97_inst                                                       0x00E1
#define CAM_EMM_EMM_BUF_98_inst                                                       0x00E2
#define CAM_EMM_EMM_BUF_99_inst                                                       0x00E3
#define CAM_EMM_EMM_BUF_100_inst                                                       0x00E4
#define CAM_EMM_EMM_BUF_101_inst                                                       0x00E5
#define CAM_EMM_EMM_BUF_102_inst                                                       0x00E6
#define CAM_EMM_EMM_BUF_103_inst                                                       0x00E7
#define CAM_EMM_EMM_BUF_104_inst                                                       0x00E8
#define CAM_EMM_EMM_BUF_105_inst                                                       0x00E9
#define CAM_EMM_EMM_BUF_106_inst                                                       0x00EA
#define CAM_EMM_EMM_BUF_107_inst                                                       0x00EB
#define CAM_EMM_EMM_BUF_108_inst                                                       0x00EC
#define CAM_EMM_EMM_BUF_109_inst                                                       0x00ED
#define CAM_EMM_EMM_BUF_110_inst                                                       0x00EE
#define CAM_EMM_EMM_BUF_111_inst                                                       0x00EF
#define CAM_EMM_EMM_BUF_112_inst                                                       0x00F0
#define CAM_EMM_EMM_BUF_113_inst                                                       0x00F1
#define CAM_EMM_EMM_BUF_114_inst                                                       0x00F2
#define CAM_EMM_EMM_BUF_115_inst                                                       0x00F3
#define CAM_EMM_EMM_BUF_116_inst                                                       0x00F4
#define CAM_EMM_EMM_BUF_117_inst                                                       0x00F5
#define CAM_EMM_EMM_BUF_118_inst                                                       0x00F6
#define CAM_EMM_EMM_BUF_119_inst                                                       0x00F7
#define CAM_EMM_EMM_BUF_120_inst                                                       0x00F8
#define CAM_EMM_EMM_BUF_121_inst                                                       0x00F9
#define CAM_EMM_EMM_BUF_122_inst                                                       0x00FA
#define CAM_EMM_EMM_BUF_123_inst                                                       0x00FB
#define CAM_EMM_EMM_BUF_124_inst                                                       0x00FC
#define CAM_EMM_EMM_BUF_125_inst                                                       0x00FD
#define CAM_EMM_EMM_BUF_126_inst                                                       0x00FE
#define CAM_EMM_EMM_BUF_127_inst                                                       0x00FF
#define CAM_EMM_EMM_BUF_128_inst                                                       0x0100
#define CAM_EMM_EMM_BUF_129_inst                                                       0x0101
#define CAM_EMM_EMM_BUF_130_inst                                                       0x0102
#define CAM_EMM_EMM_BUF_131_inst                                                       0x0103
#define CAM_EMM_EMM_BUF_132_inst                                                       0x0104
#define CAM_EMM_EMM_BUF_133_inst                                                       0x0105
#define CAM_EMM_EMM_BUF_134_inst                                                       0x0106
#define CAM_EMM_EMM_BUF_135_inst                                                       0x0107
#define CAM_EMM_EMM_BUF_136_inst                                                       0x0108
#define CAM_EMM_EMM_BUF_137_inst                                                       0x0109
#define CAM_EMM_EMM_BUF_138_inst                                                       0x010A
#define CAM_EMM_EMM_BUF_139_inst                                                       0x010B
#define CAM_EMM_EMM_BUF_140_inst                                                       0x010C
#define CAM_EMM_EMM_BUF_141_inst                                                       0x010D
#define CAM_EMM_EMM_BUF_142_inst                                                       0x010E
#define CAM_EMM_EMM_BUF_143_inst                                                       0x010F
#define CAM_EMM_EMM_BUF_144_inst                                                       0x0110
#define CAM_EMM_EMM_BUF_145_inst                                                       0x0111
#define CAM_EMM_EMM_BUF_146_inst                                                       0x0112
#define CAM_EMM_EMM_BUF_147_inst                                                       0x0113
#define CAM_EMM_EMM_BUF_148_inst                                                       0x0114
#define CAM_EMM_EMM_BUF_149_inst                                                       0x0115
#define CAM_EMM_EMM_BUF_150_inst                                                       0x0116
#define CAM_EMM_EMM_BUF_151_inst                                                       0x0117
#define CAM_EMM_EMM_BUF_152_inst                                                       0x0118
#define CAM_EMM_EMM_BUF_153_inst                                                       0x0119
#define CAM_EMM_EMM_BUF_154_inst                                                       0x011A
#define CAM_EMM_EMM_BUF_155_inst                                                       0x011B
#define CAM_EMM_EMM_BUF_156_inst                                                       0x011C
#define CAM_EMM_EMM_BUF_157_inst                                                       0x011D
#define CAM_EMM_EMM_BUF_158_inst                                                       0x011E
#define CAM_EMM_EMM_BUF_159_inst                                                       0x011F
#define CAM_EMM_EMM_BUF_160_inst                                                       0x0120
#define CAM_EMM_EMM_BUF_161_inst                                                       0x0121
#define CAM_EMM_EMM_BUF_162_inst                                                       0x0122
#define CAM_EMM_EMM_BUF_163_inst                                                       0x0123
#define CAM_EMM_EMM_BUF_164_inst                                                       0x0124
#define CAM_EMM_EMM_BUF_165_inst                                                       0x0125
#define CAM_EMM_EMM_BUF_166_inst                                                       0x0126
#define CAM_EMM_EMM_BUF_167_inst                                                       0x0127
#define CAM_EMM_EMM_BUF_168_inst                                                       0x0128
#define CAM_EMM_EMM_BUF_169_inst                                                       0x0129
#define CAM_EMM_EMM_BUF_170_inst                                                       0x012A
#define CAM_EMM_EMM_BUF_171_inst                                                       0x012B
#define CAM_EMM_EMM_BUF_172_inst                                                       0x012C
#define CAM_EMM_EMM_BUF_173_inst                                                       0x012D
#define CAM_EMM_EMM_BUF_174_inst                                                       0x012E
#define CAM_EMM_EMM_BUF_175_inst                                                       0x012F
#define CAM_EMM_EMM_BUF_176_inst                                                       0x0130
#define CAM_EMM_EMM_BUF_177_inst                                                       0x0131
#define CAM_EMM_EMM_BUF_178_inst                                                       0x0132
#define CAM_EMM_EMM_BUF_179_inst                                                       0x0133
#define CAM_EMM_EMM_BUF_180_inst                                                       0x0134
#define CAM_EMM_EMM_BUF_181_inst                                                       0x0135
#define CAM_EMM_EMM_BUF_182_inst                                                       0x0136
#define CAM_EMM_EMM_BUF_183_inst                                                       0x0137
#define CAM_EMM_EMM_BUF_184_inst                                                       0x0138
#define CAM_EMM_EMM_BUF_185_inst                                                       0x0139
#define CAM_EMM_EMM_BUF_186_inst                                                       0x013A
#define CAM_EMM_EMM_BUF_187_inst                                                       0x013B
#define CAM_EMM_EMM_BUF_188_inst                                                       0x013C
#define CAM_EMM_EMM_BUF_189_inst                                                       0x013D
#define CAM_EMM_EMM_BUF_190_inst                                                       0x013E
#define CAM_EMM_EMM_BUF_191_inst                                                       0x013F
#define CAM_EMM_EMM_BUF_192_inst                                                       0x0140
#define CAM_EMM_EMM_BUF_193_inst                                                       0x0141
#define CAM_EMM_EMM_BUF_194_inst                                                       0x0142
#define CAM_EMM_EMM_BUF_195_inst                                                       0x0143
#define CAM_EMM_EMM_BUF_196_inst                                                       0x0144
#define CAM_EMM_EMM_BUF_197_inst                                                       0x0145
#define CAM_EMM_EMM_BUF_198_inst                                                       0x0146
#define CAM_EMM_EMM_BUF_199_inst                                                       0x0147
#define CAM_EMM_EMM_BUF_200_inst                                                       0x0148
#define CAM_EMM_EMM_BUF_201_inst                                                       0x0149
#define CAM_EMM_EMM_BUF_202_inst                                                       0x014A
#define CAM_EMM_EMM_BUF_203_inst                                                       0x014B
#define CAM_EMM_EMM_BUF_204_inst                                                       0x014C
#define CAM_EMM_EMM_BUF_205_inst                                                       0x014D
#define CAM_EMM_EMM_BUF_206_inst                                                       0x014E
#define CAM_EMM_EMM_BUF_207_inst                                                       0x014F
#define CAM_EMM_EMM_BUF_208_inst                                                       0x0150
#define CAM_EMM_EMM_BUF_209_inst                                                       0x0151
#define CAM_EMM_EMM_BUF_210_inst                                                       0x0152
#define CAM_EMM_EMM_BUF_211_inst                                                       0x0153
#define CAM_EMM_EMM_BUF_212_inst                                                       0x0154
#define CAM_EMM_EMM_BUF_213_inst                                                       0x0155
#define CAM_EMM_EMM_BUF_214_inst                                                       0x0156
#define CAM_EMM_EMM_BUF_215_inst                                                       0x0157
#define CAM_EMM_EMM_BUF_216_inst                                                       0x0158
#define CAM_EMM_EMM_BUF_217_inst                                                       0x0159
#define CAM_EMM_EMM_BUF_218_inst                                                       0x015A
#define CAM_EMM_EMM_BUF_219_inst                                                       0x015B
#define CAM_EMM_EMM_BUF_220_inst                                                       0x015C
#define CAM_EMM_EMM_BUF_221_inst                                                       0x015D
#define CAM_EMM_EMM_BUF_222_inst                                                       0x015E
#define CAM_EMM_EMM_BUF_223_inst                                                       0x015F
#define CAM_EMM_EMM_BUF_224_inst                                                       0x0160
#define CAM_EMM_EMM_BUF_225_inst                                                       0x0161
#define CAM_EMM_EMM_BUF_226_inst                                                       0x0162
#define CAM_EMM_EMM_BUF_227_inst                                                       0x0163
#define CAM_EMM_EMM_BUF_228_inst                                                       0x0164
#define CAM_EMM_EMM_BUF_229_inst                                                       0x0165
#define CAM_EMM_EMM_BUF_230_inst                                                       0x0166
#define CAM_EMM_EMM_BUF_231_inst                                                       0x0167
#define CAM_EMM_EMM_BUF_232_inst                                                       0x0168
#define CAM_EMM_EMM_BUF_233_inst                                                       0x0169
#define CAM_EMM_EMM_BUF_234_inst                                                       0x016A
#define CAM_EMM_EMM_BUF_235_inst                                                       0x016B
#define CAM_EMM_EMM_BUF_236_inst                                                       0x016C
#define CAM_EMM_EMM_BUF_237_inst                                                       0x016D
#define CAM_EMM_EMM_BUF_238_inst                                                       0x016E
#define CAM_EMM_EMM_BUF_239_inst                                                       0x016F
#define CAM_EMM_EMM_BUF_240_inst                                                       0x0170
#define CAM_EMM_EMM_BUF_241_inst                                                       0x0171
#define CAM_EMM_EMM_BUF_242_inst                                                       0x0172
#define CAM_EMM_EMM_BUF_243_inst                                                       0x0173
#define CAM_EMM_EMM_BUF_244_inst                                                       0x0174
#define CAM_EMM_EMM_BUF_245_inst                                                       0x0175
#define CAM_EMM_EMM_BUF_246_inst                                                       0x0176
#define CAM_EMM_EMM_BUF_247_inst                                                       0x0177
#define CAM_EMM_EMM_BUF_248_inst                                                       0x0178
#define CAM_EMM_EMM_BUF_249_inst                                                       0x0179
#define CAM_EMM_EMM_BUF_250_inst                                                       0x017A
#define CAM_EMM_EMM_BUF_251_inst                                                       0x017B
#define CAM_EMM_EMM_BUF_252_inst                                                       0x017C
#define CAM_EMM_EMM_BUF_253_inst                                                       0x017D
#define CAM_EMM_EMM_BUF_254_inst                                                       0x017E
#define CAM_EMM_EMM_BUF_255_inst                                                       0x017F
#define CAM_EMM_EMM_BUF_256_inst                                                       0x0180
#define CAM_EMM_EMM_BUF_257_inst                                                       0x0181
#define CAM_EMM_EMM_BUF_258_inst                                                       0x0182
#define CAM_EMM_EMM_BUF_259_inst                                                       0x0183
#define CAM_EMM_EMM_BUF_260_inst                                                       0x0184
#define CAM_EMM_EMM_BUF_261_inst                                                       0x0185
#define CAM_EMM_EMM_BUF_262_inst                                                       0x0186
#define CAM_EMM_EMM_BUF_263_inst                                                       0x0187
#define CAM_EMM_EMM_BUF_264_inst                                                       0x0188
#define CAM_EMM_EMM_BUF_265_inst                                                       0x0189
#define CAM_EMM_EMM_BUF_266_inst                                                       0x018A
#define CAM_EMM_EMM_BUF_267_inst                                                       0x018B
#define CAM_EMM_EMM_BUF_268_inst                                                       0x018C
#define CAM_EMM_EMM_BUF_269_inst                                                       0x018D
#define CAM_EMM_EMM_BUF_270_inst                                                       0x018E
#define CAM_EMM_EMM_BUF_271_inst                                                       0x018F
#define CAM_EMM_EMM_BUF_272_inst                                                       0x0190
#define CAM_EMM_EMM_BUF_273_inst                                                       0x0191
#define CAM_EMM_EMM_BUF_274_inst                                                       0x0192
#define CAM_EMM_EMM_BUF_275_inst                                                       0x0193
#define CAM_EMM_EMM_BUF_276_inst                                                       0x0194
#define CAM_EMM_EMM_BUF_277_inst                                                       0x0195
#define CAM_EMM_EMM_BUF_278_inst                                                       0x0196
#define CAM_EMM_EMM_BUF_279_inst                                                       0x0197
#define CAM_EMM_EMM_BUF_280_inst                                                       0x0198
#define CAM_EMM_EMM_BUF_281_inst                                                       0x0199
#define CAM_EMM_EMM_BUF_282_inst                                                       0x019A
#define CAM_EMM_EMM_BUF_283_inst                                                       0x019B
#define CAM_EMM_EMM_BUF_284_inst                                                       0x019C
#define CAM_EMM_EMM_BUF_285_inst                                                       0x019D
#define CAM_EMM_EMM_BUF_286_inst                                                       0x019E
#define CAM_EMM_EMM_BUF_287_inst                                                       0x019F
#define CAM_EMM_EMM_BUF_288_inst                                                       0x01A0
#define CAM_EMM_EMM_BUF_289_inst                                                       0x01A1
#define CAM_EMM_EMM_BUF_290_inst                                                       0x01A2
#define CAM_EMM_EMM_BUF_291_inst                                                       0x01A3
#define CAM_EMM_EMM_BUF_292_inst                                                       0x01A4
#define CAM_EMM_EMM_BUF_293_inst                                                       0x01A5
#define CAM_EMM_EMM_BUF_294_inst                                                       0x01A6
#define CAM_EMM_EMM_BUF_295_inst                                                       0x01A7
#define CAM_EMM_EMM_BUF_296_inst                                                       0x01A8
#define CAM_EMM_EMM_BUF_297_inst                                                       0x01A9
#define CAM_EMM_EMM_BUF_298_inst                                                       0x01AA
#define CAM_EMM_EMM_BUF_299_inst                                                       0x01AB
#define CAM_EMM_EMM_BUF_300_inst                                                       0x01AC
#define CAM_EMM_EMM_BUF_301_inst                                                       0x01AD
#define CAM_EMM_EMM_BUF_302_inst                                                       0x01AE
#define CAM_EMM_EMM_BUF_303_inst                                                       0x01AF
#define CAM_EMM_EMM_BUF_304_inst                                                       0x01B0
#define CAM_EMM_EMM_BUF_305_inst                                                       0x01B1
#define CAM_EMM_EMM_BUF_306_inst                                                       0x01B2
#define CAM_EMM_EMM_BUF_307_inst                                                       0x01B3
#define CAM_EMM_EMM_BUF_308_inst                                                       0x01B4
#define CAM_EMM_EMM_BUF_309_inst                                                       0x01B5
#define CAM_EMM_EMM_BUF_310_inst                                                       0x01B6
#define CAM_EMM_EMM_BUF_311_inst                                                       0x01B7
#define CAM_EMM_EMM_BUF_312_inst                                                       0x01B8
#define CAM_EMM_EMM_BUF_313_inst                                                       0x01B9
#define CAM_EMM_EMM_BUF_314_inst                                                       0x01BA
#define CAM_EMM_EMM_BUF_315_inst                                                       0x01BB
#define CAM_EMM_EMM_BUF_316_inst                                                       0x01BC
#define CAM_EMM_EMM_BUF_317_inst                                                       0x01BD
#define CAM_EMM_EMM_BUF_318_inst                                                       0x01BE
#define CAM_EMM_EMM_BUF_319_inst                                                       0x01BF
#define CAM_EMM_EMM_BUF_320_inst                                                       0x01C0
#define CAM_EMM_EMM_BUF_321_inst                                                       0x01C1
#define CAM_EMM_EMM_BUF_322_inst                                                       0x01C2
#define CAM_EMM_EMM_BUF_323_inst                                                       0x01C3
#define CAM_EMM_EMM_BUF_324_inst                                                       0x01C4
#define CAM_EMM_EMM_BUF_325_inst                                                       0x01C5
#define CAM_EMM_EMM_BUF_326_inst                                                       0x01C6
#define CAM_EMM_EMM_BUF_327_inst                                                       0x01C7
#define CAM_EMM_EMM_BUF_328_inst                                                       0x01C8
#define CAM_EMM_EMM_BUF_329_inst                                                       0x01C9
#define CAM_EMM_EMM_BUF_330_inst                                                       0x01CA
#define CAM_EMM_EMM_BUF_331_inst                                                       0x01CB
#define CAM_EMM_EMM_BUF_332_inst                                                       0x01CC
#define CAM_EMM_EMM_BUF_333_inst                                                       0x01CD
#define CAM_EMM_EMM_BUF_334_inst                                                       0x01CE
#define CAM_EMM_EMM_BUF_335_inst                                                       0x01CF
#define CAM_EMM_EMM_BUF_336_inst                                                       0x01D0
#define CAM_EMM_EMM_BUF_337_inst                                                       0x01D1
#define CAM_EMM_EMM_BUF_338_inst                                                       0x01D2
#define CAM_EMM_EMM_BUF_339_inst                                                       0x01D3
#define CAM_EMM_EMM_BUF_340_inst                                                       0x01D4
#define CAM_EMM_EMM_BUF_341_inst                                                       0x01D5
#define CAM_EMM_EMM_BUF_342_inst                                                       0x01D6
#define CAM_EMM_EMM_BUF_343_inst                                                       0x01D7
#define CAM_EMM_EMM_BUF_344_inst                                                       0x01D8
#define CAM_EMM_EMM_BUF_345_inst                                                       0x01D9
#define CAM_EMM_EMM_BUF_346_inst                                                       0x01DA
#define CAM_EMM_EMM_BUF_347_inst                                                       0x01DB
#define CAM_EMM_EMM_BUF_348_inst                                                       0x01DC
#define CAM_EMM_EMM_BUF_349_inst                                                       0x01DD
#define CAM_EMM_EMM_BUF_350_inst                                                       0x01DE
#define CAM_EMM_EMM_BUF_351_inst                                                       0x01DF
#define CAM_EMM_EMM_BUF_352_inst                                                       0x01E0
#define CAM_EMM_EMM_BUF_353_inst                                                       0x01E1
#define CAM_EMM_EMM_BUF_354_inst                                                       0x01E2
#define CAM_EMM_EMM_BUF_355_inst                                                       0x01E3
#define CAM_EMM_EMM_BUF_356_inst                                                       0x01E4
#define CAM_EMM_EMM_BUF_357_inst                                                       0x01E5
#define CAM_EMM_EMM_BUF_358_inst                                                       0x01E6
#define CAM_EMM_EMM_BUF_359_inst                                                       0x01E7
#define CAM_EMM_EMM_BUF_360_inst                                                       0x01E8
#define CAM_EMM_EMM_BUF_361_inst                                                       0x01E9
#define CAM_EMM_EMM_BUF_362_inst                                                       0x01EA
#define CAM_EMM_EMM_BUF_363_inst                                                       0x01EB
#define CAM_EMM_EMM_BUF_364_inst                                                       0x01EC
#define CAM_EMM_EMM_BUF_365_inst                                                       0x01ED
#define CAM_EMM_EMM_BUF_366_inst                                                       0x01EE
#define CAM_EMM_EMM_BUF_367_inst                                                       0x01EF
#define CAM_EMM_EMM_BUF_368_inst                                                       0x01F0
#define CAM_EMM_EMM_BUF_369_inst                                                       0x01F1
#define CAM_EMM_EMM_BUF_370_inst                                                       0x01F2
#define CAM_EMM_EMM_BUF_371_inst                                                       0x01F3
#define CAM_EMM_EMM_BUF_372_inst                                                       0x01F4
#define CAM_EMM_EMM_BUF_373_inst                                                       0x01F5
#define CAM_EMM_EMM_BUF_374_inst                                                       0x01F6
#define CAM_EMM_EMM_BUF_375_inst                                                       0x01F7
#define CAM_EMM_EMM_BUF_376_inst                                                       0x01F8
#define CAM_EMM_EMM_BUF_377_inst                                                       0x01F9
#define CAM_EMM_EMM_BUF_378_inst                                                       0x01FA
#define CAM_EMM_EMM_BUF_379_inst                                                       0x01FB
#define CAM_EMM_EMM_BUF_380_inst                                                       0x01FC
#define CAM_EMM_EMM_BUF_381_inst                                                       0x01FD
#define CAM_EMM_EMM_BUF_382_inst                                                       0x01FE
#define CAM_EMM_EMM_BUF_383_inst                                                       0x01FF
#define CAM_EMM_EMM_BUF_384_inst                                                       0x0200
#define CAM_EMM_EMM_BUF_385_inst                                                       0x0201
#define CAM_EMM_EMM_BUF_386_inst                                                       0x0202
#define CAM_EMM_EMM_BUF_387_inst                                                       0x0203
#define CAM_EMM_EMM_BUF_388_inst                                                       0x0204
#define CAM_EMM_EMM_BUF_389_inst                                                       0x0205
#define CAM_EMM_EMM_BUF_390_inst                                                       0x0206
#define CAM_EMM_EMM_BUF_391_inst                                                       0x0207
#define CAM_EMM_EMM_BUF_392_inst                                                       0x0208
#define CAM_EMM_EMM_BUF_393_inst                                                       0x0209
#define CAM_EMM_EMM_BUF_394_inst                                                       0x020A
#define CAM_EMM_EMM_BUF_395_inst                                                       0x020B
#define CAM_EMM_EMM_BUF_396_inst                                                       0x020C
#define CAM_EMM_EMM_BUF_397_inst                                                       0x020D
#define CAM_EMM_EMM_BUF_398_inst                                                       0x020E
#define CAM_EMM_EMM_BUF_399_inst                                                       0x020F
#define CAM_EMM_EMM_BUF_400_inst                                                       0x0210
#define CAM_EMM_EMM_BUF_401_inst                                                       0x0211
#define CAM_EMM_EMM_BUF_402_inst                                                       0x0212
#define CAM_EMM_EMM_BUF_403_inst                                                       0x0213
#define CAM_EMM_EMM_BUF_404_inst                                                       0x0214
#define CAM_EMM_EMM_BUF_405_inst                                                       0x0215
#define CAM_EMM_EMM_BUF_406_inst                                                       0x0216
#define CAM_EMM_EMM_BUF_407_inst                                                       0x0217
#define CAM_EMM_EMM_BUF_408_inst                                                       0x0218
#define CAM_EMM_EMM_BUF_409_inst                                                       0x0219
#define CAM_EMM_EMM_BUF_410_inst                                                       0x021A
#define CAM_EMM_EMM_BUF_411_inst                                                       0x021B
#define CAM_EMM_EMM_BUF_412_inst                                                       0x021C
#define CAM_EMM_EMM_BUF_413_inst                                                       0x021D
#define CAM_EMM_EMM_BUF_414_inst                                                       0x021E
#define CAM_EMM_EMM_BUF_415_inst                                                       0x021F
#define CAM_EMM_EMM_BUF_416_inst                                                       0x0220
#define CAM_EMM_EMM_BUF_417_inst                                                       0x0221
#define CAM_EMM_EMM_BUF_418_inst                                                       0x0222
#define CAM_EMM_EMM_BUF_419_inst                                                       0x0223
#define CAM_EMM_EMM_BUF_420_inst                                                       0x0224
#define CAM_EMM_EMM_BUF_421_inst                                                       0x0225
#define CAM_EMM_EMM_BUF_422_inst                                                       0x0226
#define CAM_EMM_EMM_BUF_423_inst                                                       0x0227
#define CAM_EMM_EMM_BUF_424_inst                                                       0x0228
#define CAM_EMM_EMM_BUF_425_inst                                                       0x0229
#define CAM_EMM_EMM_BUF_426_inst                                                       0x022A
#define CAM_EMM_EMM_BUF_427_inst                                                       0x022B
#define CAM_EMM_EMM_BUF_428_inst                                                       0x022C
#define CAM_EMM_EMM_BUF_429_inst                                                       0x022D
#define CAM_EMM_EMM_BUF_430_inst                                                       0x022E
#define CAM_EMM_EMM_BUF_431_inst                                                       0x022F
#define CAM_EMM_EMM_BUF_432_inst                                                       0x0230
#define CAM_EMM_EMM_BUF_433_inst                                                       0x0231
#define CAM_EMM_EMM_BUF_434_inst                                                       0x0232
#define CAM_EMM_EMM_BUF_435_inst                                                       0x0233
#define CAM_EMM_EMM_BUF_436_inst                                                       0x0234
#define CAM_EMM_EMM_BUF_437_inst                                                       0x0235
#define CAM_EMM_EMM_BUF_438_inst                                                       0x0236
#define CAM_EMM_EMM_BUF_439_inst                                                       0x0237
#define CAM_EMM_EMM_BUF_440_inst                                                       0x0238
#define CAM_EMM_EMM_BUF_441_inst                                                       0x0239
#define CAM_EMM_EMM_BUF_442_inst                                                       0x023A
#define CAM_EMM_EMM_BUF_443_inst                                                       0x023B
#define CAM_EMM_EMM_BUF_444_inst                                                       0x023C
#define CAM_EMM_EMM_BUF_445_inst                                                       0x023D
#define CAM_EMM_EMM_BUF_446_inst                                                       0x023E
#define CAM_EMM_EMM_BUF_447_inst                                                       0x023F
#define CAM_EMM_EMM_BUF_448_inst                                                       0x0240
#define CAM_EMM_EMM_BUF_449_inst                                                       0x0241
#define CAM_EMM_EMM_BUF_450_inst                                                       0x0242
#define CAM_EMM_EMM_BUF_451_inst                                                       0x0243
#define CAM_EMM_EMM_BUF_452_inst                                                       0x0244
#define CAM_EMM_EMM_BUF_453_inst                                                       0x0245
#define CAM_EMM_EMM_BUF_454_inst                                                       0x0246
#define CAM_EMM_EMM_BUF_455_inst                                                       0x0247
#define CAM_EMM_EMM_BUF_456_inst                                                       0x0248
#define CAM_EMM_EMM_BUF_457_inst                                                       0x0249
#define CAM_EMM_EMM_BUF_458_inst                                                       0x024A
#define CAM_EMM_EMM_BUF_459_inst                                                       0x024B
#define CAM_EMM_EMM_BUF_460_inst                                                       0x024C
#define CAM_EMM_EMM_BUF_461_inst                                                       0x024D
#define CAM_EMM_EMM_BUF_462_inst                                                       0x024E
#define CAM_EMM_EMM_BUF_463_inst                                                       0x024F
#define CAM_EMM_EMM_BUF_464_inst                                                       0x0250
#define CAM_EMM_EMM_BUF_465_inst                                                       0x0251
#define CAM_EMM_EMM_BUF_466_inst                                                       0x0252
#define CAM_EMM_EMM_BUF_467_inst                                                       0x0253
#define CAM_EMM_EMM_BUF_468_inst                                                       0x0254
#define CAM_EMM_EMM_BUF_469_inst                                                       0x0255
#define CAM_EMM_EMM_BUF_470_inst                                                       0x0256
#define CAM_EMM_EMM_BUF_471_inst                                                       0x0257
#define CAM_EMM_EMM_BUF_472_inst                                                       0x0258
#define CAM_EMM_EMM_BUF_473_inst                                                       0x0259
#define CAM_EMM_EMM_BUF_474_inst                                                       0x025A
#define CAM_EMM_EMM_BUF_475_inst                                                       0x025B
#define CAM_EMM_EMM_BUF_476_inst                                                       0x025C
#define CAM_EMM_EMM_BUF_477_inst                                                       0x025D
#define CAM_EMM_EMM_BUF_478_inst                                                       0x025E
#define CAM_EMM_EMM_BUF_479_inst                                                       0x025F
#define CAM_EMM_EMM_BUF_480_inst                                                       0x0260
#define CAM_EMM_EMM_BUF_481_inst                                                       0x0261
#define CAM_EMM_EMM_BUF_482_inst                                                       0x0262
#define CAM_EMM_EMM_BUF_483_inst                                                       0x0263
#define CAM_EMM_EMM_BUF_484_inst                                                       0x0264
#define CAM_EMM_EMM_BUF_485_inst                                                       0x0265
#define CAM_EMM_EMM_BUF_486_inst                                                       0x0266
#define CAM_EMM_EMM_BUF_487_inst                                                       0x0267
#define CAM_EMM_EMM_BUF_488_inst                                                       0x0268
#define CAM_EMM_EMM_BUF_489_inst                                                       0x0269
#define CAM_EMM_EMM_BUF_490_inst                                                       0x026A
#define CAM_EMM_EMM_BUF_491_inst                                                       0x026B
#define CAM_EMM_EMM_BUF_492_inst                                                       0x026C
#define CAM_EMM_EMM_BUF_493_inst                                                       0x026D
#define CAM_EMM_EMM_BUF_494_inst                                                       0x026E
#define CAM_EMM_EMM_BUF_495_inst                                                       0x026F
#define CAM_EMM_EMM_BUF_496_inst                                                       0x0270
#define CAM_EMM_EMM_BUF_497_inst                                                       0x0271
#define CAM_EMM_EMM_BUF_498_inst                                                       0x0272
#define CAM_EMM_EMM_BUF_499_inst                                                       0x0273
#define CAM_EMM_EMM_BUF_500_inst                                                       0x0274
#define CAM_EMM_EMM_BUF_501_inst                                                       0x0275
#define CAM_EMM_EMM_BUF_502_inst                                                       0x0276
#define CAM_EMM_EMM_BUF_503_inst                                                       0x0277
#define CAM_EMM_EMM_BUF_504_inst                                                       0x0278
#define CAM_EMM_EMM_BUF_505_inst                                                       0x0279
#define CAM_EMM_EMM_BUF_506_inst                                                       0x027A
#define CAM_EMM_EMM_BUF_507_inst                                                       0x027B
#define CAM_EMM_EMM_BUF_508_inst                                                       0x027C
#define CAM_EMM_EMM_BUF_509_inst                                                       0x027D
#define CAM_EMM_EMM_BUF_510_inst                                                       0x027E
#define CAM_EMM_EMM_BUF_511_inst                                                       0x027F
#define CAM_EMM_EMM_BUF_512_inst                                                       0x0280
#define CAM_EMM_EMM_BUF_513_inst                                                       0x0281
#define CAM_EMM_EMM_BUF_514_inst                                                       0x0282
#define CAM_EMM_EMM_BUF_515_inst                                                       0x0283
#define CAM_EMM_EMM_BUF_516_inst                                                       0x0284
#define CAM_EMM_EMM_BUF_517_inst                                                       0x0285
#define CAM_EMM_EMM_BUF_518_inst                                                       0x0286
#define CAM_EMM_EMM_BUF_519_inst                                                       0x0287
#define CAM_EMM_EMM_BUF_520_inst                                                       0x0288
#define CAM_EMM_EMM_BUF_521_inst                                                       0x0289
#define CAM_EMM_EMM_BUF_522_inst                                                       0x028A
#define CAM_EMM_EMM_BUF_523_inst                                                       0x028B
#define CAM_EMM_EMM_BUF_524_inst                                                       0x028C
#define CAM_EMM_EMM_BUF_525_inst                                                       0x028D
#define CAM_EMM_EMM_BUF_526_inst                                                       0x028E
#define CAM_EMM_EMM_BUF_527_inst                                                       0x028F
#define CAM_EMM_EMM_BUF_528_inst                                                       0x0290
#define CAM_EMM_EMM_BUF_529_inst                                                       0x0291
#define CAM_EMM_EMM_BUF_530_inst                                                       0x0292
#define CAM_EMM_EMM_BUF_531_inst                                                       0x0293
#define CAM_EMM_EMM_BUF_532_inst                                                       0x0294
#define CAM_EMM_EMM_BUF_533_inst                                                       0x0295
#define CAM_EMM_EMM_BUF_534_inst                                                       0x0296
#define CAM_EMM_EMM_BUF_535_inst                                                       0x0297
#define CAM_EMM_EMM_BUF_536_inst                                                       0x0298
#define CAM_EMM_EMM_BUF_537_inst                                                       0x0299
#define CAM_EMM_EMM_BUF_538_inst                                                       0x029A
#define CAM_EMM_EMM_BUF_539_inst                                                       0x029B
#define CAM_EMM_EMM_BUF_540_inst                                                       0x029C
#define CAM_EMM_EMM_BUF_541_inst                                                       0x029D
#define CAM_EMM_EMM_BUF_542_inst                                                       0x029E
#define CAM_EMM_EMM_BUF_543_inst                                                       0x029F
#define CAM_EMM_EMM_BUF_544_inst                                                       0x02A0
#define CAM_EMM_EMM_BUF_545_inst                                                       0x02A1
#define CAM_EMM_EMM_BUF_546_inst                                                       0x02A2
#define CAM_EMM_EMM_BUF_547_inst                                                       0x02A3
#define CAM_EMM_EMM_BUF_548_inst                                                       0x02A4
#define CAM_EMM_EMM_BUF_549_inst                                                       0x02A5
#define CAM_EMM_EMM_BUF_550_inst                                                       0x02A6
#define CAM_EMM_EMM_BUF_551_inst                                                       0x02A7
#define CAM_EMM_EMM_BUF_552_inst                                                       0x02A8
#define CAM_EMM_EMM_BUF_553_inst                                                       0x02A9
#define CAM_EMM_EMM_BUF_554_inst                                                       0x02AA
#define CAM_EMM_EMM_BUF_555_inst                                                       0x02AB
#define CAM_EMM_EMM_BUF_556_inst                                                       0x02AC
#define CAM_EMM_EMM_BUF_557_inst                                                       0x02AD
#define CAM_EMM_EMM_BUF_558_inst                                                       0x02AE
#define CAM_EMM_EMM_BUF_559_inst                                                       0x02AF
#define CAM_EMM_EMM_BUF_560_inst                                                       0x02B0
#define CAM_EMM_EMM_BUF_561_inst                                                       0x02B1
#define CAM_EMM_EMM_BUF_562_inst                                                       0x02B2
#define CAM_EMM_EMM_BUF_563_inst                                                       0x02B3
#define CAM_EMM_EMM_BUF_564_inst                                                       0x02B4
#define CAM_EMM_EMM_BUF_565_inst                                                       0x02B5
#define CAM_EMM_EMM_BUF_566_inst                                                       0x02B6
#define CAM_EMM_EMM_BUF_567_inst                                                       0x02B7
#define CAM_EMM_EMM_BUF_568_inst                                                       0x02B8
#define CAM_EMM_EMM_BUF_569_inst                                                       0x02B9
#define CAM_EMM_EMM_BUF_570_inst                                                       0x02BA
#define CAM_EMM_EMM_BUF_571_inst                                                       0x02BB
#define CAM_EMM_EMM_BUF_572_inst                                                       0x02BC
#define CAM_EMM_EMM_BUF_573_inst                                                       0x02BD
#define CAM_EMM_EMM_BUF_574_inst                                                       0x02BE
#define CAM_EMM_EMM_BUF_575_inst                                                       0x02BF
#define CAM_EMM_EMM_BUF_576_inst                                                       0x02C0
#define CAM_EMM_EMM_BUF_577_inst                                                       0x02C1
#define CAM_EMM_EMM_BUF_578_inst                                                       0x02C2
#define CAM_EMM_EMM_BUF_579_inst                                                       0x02C3
#define CAM_EMM_EMM_BUF_580_inst                                                       0x02C4
#define CAM_EMM_EMM_BUF_581_inst                                                       0x02C5
#define CAM_EMM_EMM_BUF_582_inst                                                       0x02C6
#define CAM_EMM_EMM_BUF_583_inst                                                       0x02C7
#define CAM_EMM_EMM_BUF_584_inst                                                       0x02C8
#define CAM_EMM_EMM_BUF_585_inst                                                       0x02C9
#define CAM_EMM_EMM_BUF_586_inst                                                       0x02CA
#define CAM_EMM_EMM_BUF_587_inst                                                       0x02CB
#define CAM_EMM_EMM_BUF_588_inst                                                       0x02CC
#define CAM_EMM_EMM_BUF_589_inst                                                       0x02CD
#define CAM_EMM_EMM_BUF_590_inst                                                       0x02CE
#define CAM_EMM_EMM_BUF_591_inst                                                       0x02CF
#define CAM_EMM_EMM_BUF_592_inst                                                       0x02D0
#define CAM_EMM_EMM_BUF_593_inst                                                       0x02D1
#define CAM_EMM_EMM_BUF_594_inst                                                       0x02D2
#define CAM_EMM_EMM_BUF_595_inst                                                       0x02D3
#define CAM_EMM_EMM_BUF_596_inst                                                       0x02D4
#define CAM_EMM_EMM_BUF_597_inst                                                       0x02D5
#define CAM_EMM_EMM_BUF_598_inst                                                       0x02D6
#define CAM_EMM_EMM_BUF_599_inst                                                       0x02D7
#define CAM_EMM_EMM_BUF_600_inst                                                       0x02D8
#define CAM_EMM_EMM_BUF_601_inst                                                       0x02D9
#define CAM_EMM_EMM_BUF_602_inst                                                       0x02DA
#define CAM_EMM_EMM_BUF_603_inst                                                       0x02DB
#define CAM_EMM_EMM_BUF_604_inst                                                       0x02DC
#define CAM_EMM_EMM_BUF_605_inst                                                       0x02DD
#define CAM_EMM_EMM_BUF_606_inst                                                       0x02DE
#define CAM_EMM_EMM_BUF_607_inst                                                       0x02DF
#define CAM_EMM_EMM_BUF_608_inst                                                       0x02E0
#define CAM_EMM_EMM_BUF_609_inst                                                       0x02E1
#define CAM_EMM_EMM_BUF_610_inst                                                       0x02E2
#define CAM_EMM_EMM_BUF_611_inst                                                       0x02E3
#define CAM_EMM_EMM_BUF_612_inst                                                       0x02E4
#define CAM_EMM_EMM_BUF_613_inst                                                       0x02E5
#define CAM_EMM_EMM_BUF_614_inst                                                       0x02E6
#define CAM_EMM_EMM_BUF_615_inst                                                       0x02E7
#define CAM_EMM_EMM_BUF_616_inst                                                       0x02E8
#define CAM_EMM_EMM_BUF_617_inst                                                       0x02E9
#define CAM_EMM_EMM_BUF_618_inst                                                       0x02EA
#define CAM_EMM_EMM_BUF_619_inst                                                       0x02EB
#define CAM_EMM_EMM_BUF_620_inst                                                       0x02EC
#define CAM_EMM_EMM_BUF_621_inst                                                       0x02ED
#define CAM_EMM_EMM_BUF_622_inst                                                       0x02EE
#define CAM_EMM_EMM_BUF_623_inst                                                       0x02EF
#define CAM_EMM_EMM_BUF_624_inst                                                       0x02F0
#define CAM_EMM_EMM_BUF_625_inst                                                       0x02F1
#define CAM_EMM_EMM_BUF_626_inst                                                       0x02F2
#define CAM_EMM_EMM_BUF_627_inst                                                       0x02F3
#define CAM_EMM_EMM_BUF_628_inst                                                       0x02F4
#define CAM_EMM_EMM_BUF_629_inst                                                       0x02F5
#define CAM_EMM_EMM_BUF_630_inst                                                       0x02F6
#define CAM_EMM_EMM_BUF_631_inst                                                       0x02F7
#define CAM_EMM_EMM_BUF_632_inst                                                       0x02F8
#define CAM_EMM_EMM_BUF_633_inst                                                       0x02F9
#define CAM_EMM_EMM_BUF_634_inst                                                       0x02FA
#define CAM_EMM_EMM_BUF_635_inst                                                       0x02FB
#define CAM_EMM_EMM_BUF_636_inst                                                       0x02FC
#define CAM_EMM_EMM_BUF_637_inst                                                       0x02FD
#define CAM_EMM_EMM_BUF_638_inst                                                       0x02FE
#define CAM_EMM_EMM_BUF_639_inst                                                       0x02FF
#define CAM_EMM_EMM_BUF_pkt_data_shift                                               (0)
#define CAM_EMM_EMM_BUF_pkt_data_mask                                                (0xFFFFFFFF)
#define CAM_EMM_EMM_BUF_pkt_data(data)                                               (0xFFFFFFFF&((data)<<0))
#define CAM_EMM_EMM_BUF_pkt_data_src(data)                                           ((0xFFFFFFFF&(data))>>0)
#define CAM_EMM_EMM_BUF_get_pkt_data(data)                                           ((0xFFFFFFFF&(data))>>0)


#endif
