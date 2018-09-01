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


#ifndef _VMA_REG_H_INCLUDED_
#define _VMA_REG_H_INCLUDED_
#ifdef  _VMA_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     x:13;
unsigned int     y:14;
}VMA_DMAREG1A;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     cbcr_vmOffset:7;
unsigned int     mode:1;
unsigned int     right_offset:3;
unsigned int     left_offset:3;
unsigned int     reserved_1:1;
unsigned int     addr_idx:7;
unsigned int     post_inc_sel:1;
unsigned int     reserved_2:1;
unsigned int     post_inc:6;
}VMA_DMAREG2A;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     line_off:1;
unsigned int     reserved_1:1;
unsigned int     vmRowOffset:5;
unsigned int     reserved_2:3;
unsigned int     vm_addr:7;
unsigned int     H:6;
unsigned int     reserved_3:2;
unsigned int     W:4;
}VMA_DMAREG3A;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     Seq_VMEM_addr:13;
unsigned int     reserved_1:7;
unsigned int     Seq_xsfr_size:9;
}VMA_SDMACNTLA;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     seq_line_addr:31;
}VMA_SDMAADRA;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     write_enable3:1;
unsigned int     dmem_path:1;
unsigned int     write_enable2:1;
unsigned int     ldst_vmem_count:16;
unsigned int     write_enable1:1;
unsigned int     post_write_disable:1;
}VMA_DMACTLA;

#endif

#define VMA_DMAREG1A_0                                                               0x1800EE00
#define VMA_DMAREG1A_1                                                               0x1800EE04
#define VMA_DMAREG1A_2                                                               0x1800EE08
#define VMA_DMAREG1A_3                                                               0x1800EE0C
#define VMA_DMAREG1A_4                                                               0x1800EE10
#define VMA_DMAREG1A_5                                                               0x1800EE14
#define VMA_DMAREG1A_6                                                               0x1800EE18
#define VMA_DMAREG1A_7                                                               0x1800EE1C
#define VMA_DMAREG1A_0_reg_addr                                                      "0xB800EE00"
#define VMA_DMAREG1A_1_reg_addr                                                      "0xB800EE04"
#define VMA_DMAREG1A_2_reg_addr                                                      "0xB800EE08"
#define VMA_DMAREG1A_3_reg_addr                                                      "0xB800EE0C"
#define VMA_DMAREG1A_4_reg_addr                                                      "0xB800EE10"
#define VMA_DMAREG1A_5_reg_addr                                                      "0xB800EE14"
#define VMA_DMAREG1A_6_reg_addr                                                      "0xB800EE18"
#define VMA_DMAREG1A_7_reg_addr                                                      "0xB800EE1C"
#define VMA_DMAREG1A_0_reg                                                           0xB800EE00
#define VMA_DMAREG1A_1_reg                                                           0xB800EE04
#define VMA_DMAREG1A_2_reg                                                           0xB800EE08
#define VMA_DMAREG1A_3_reg                                                           0xB800EE0C
#define VMA_DMAREG1A_4_reg                                                           0xB800EE10
#define VMA_DMAREG1A_5_reg                                                           0xB800EE14
#define VMA_DMAREG1A_6_reg                                                           0xB800EE18
#define VMA_DMAREG1A_7_reg                                                           0xB800EE1C
#define set_VMA_DMAREG1A_0_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_0_reg)=data)
#define set_VMA_DMAREG1A_1_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_1_reg)=data)
#define set_VMA_DMAREG1A_2_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_2_reg)=data)
#define set_VMA_DMAREG1A_3_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_3_reg)=data)
#define set_VMA_DMAREG1A_4_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_4_reg)=data)
#define set_VMA_DMAREG1A_5_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_5_reg)=data)
#define set_VMA_DMAREG1A_6_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_6_reg)=data)
#define set_VMA_DMAREG1A_7_reg(data)   (*((volatile unsigned int*) VMA_DMAREG1A_7_reg)=data)
#define get_VMA_DMAREG1A_0_reg   (*((volatile unsigned int*) VMA_DMAREG1A_0_reg))
#define get_VMA_DMAREG1A_1_reg   (*((volatile unsigned int*) VMA_DMAREG1A_1_reg))
#define get_VMA_DMAREG1A_2_reg   (*((volatile unsigned int*) VMA_DMAREG1A_2_reg))
#define get_VMA_DMAREG1A_3_reg   (*((volatile unsigned int*) VMA_DMAREG1A_3_reg))
#define get_VMA_DMAREG1A_4_reg   (*((volatile unsigned int*) VMA_DMAREG1A_4_reg))
#define get_VMA_DMAREG1A_5_reg   (*((volatile unsigned int*) VMA_DMAREG1A_5_reg))
#define get_VMA_DMAREG1A_6_reg   (*((volatile unsigned int*) VMA_DMAREG1A_6_reg))
#define get_VMA_DMAREG1A_7_reg   (*((volatile unsigned int*) VMA_DMAREG1A_7_reg))
#define VMA_DMAREG1A_0_inst_adr                                                      "0x0080"
#define VMA_DMAREG1A_1_inst_adr                                                      "0x0081"
#define VMA_DMAREG1A_2_inst_adr                                                      "0x0082"
#define VMA_DMAREG1A_3_inst_adr                                                      "0x0083"
#define VMA_DMAREG1A_4_inst_adr                                                      "0x0084"
#define VMA_DMAREG1A_5_inst_adr                                                      "0x0085"
#define VMA_DMAREG1A_6_inst_adr                                                      "0x0086"
#define VMA_DMAREG1A_7_inst_adr                                                      "0x0087"
#define VMA_DMAREG1A_0_inst                                                          0x0080
#define VMA_DMAREG1A_1_inst                                                          0x0081
#define VMA_DMAREG1A_2_inst                                                          0x0082
#define VMA_DMAREG1A_3_inst                                                          0x0083
#define VMA_DMAREG1A_4_inst                                                          0x0084
#define VMA_DMAREG1A_5_inst                                                          0x0085
#define VMA_DMAREG1A_6_inst                                                          0x0086
#define VMA_DMAREG1A_7_inst                                                          0x0087
#define VMA_DMAREG1A_x_shift                                                         (14)
#define VMA_DMAREG1A_x_mask                                                          (0x07FFC000)
#define VMA_DMAREG1A_x(data)                                                         (0x07FFC000&((data)<<14))
#define VMA_DMAREG1A_x_src(data)                                                     ((0x07FFC000&(data))>>14)
#define VMA_DMAREG1A_get_x(data)                                                     ((0x07FFC000&(data))>>14)
#define VMA_DMAREG1A_y_shift                                                         (0)
#define VMA_DMAREG1A_y_mask                                                          (0x00003FFF)
#define VMA_DMAREG1A_y(data)                                                         (0x00003FFF&((data)<<0))
#define VMA_DMAREG1A_y_src(data)                                                     ((0x00003FFF&(data))>>0)
#define VMA_DMAREG1A_get_y(data)                                                     ((0x00003FFF&(data))>>0)


#define VMA_DMAREG2A_0                                                               0x1800EE20
#define VMA_DMAREG2A_1                                                               0x1800EE24
#define VMA_DMAREG2A_2                                                               0x1800EE28
#define VMA_DMAREG2A_3                                                               0x1800EE2C
#define VMA_DMAREG2A_4                                                               0x1800EE30
#define VMA_DMAREG2A_5                                                               0x1800EE34
#define VMA_DMAREG2A_6                                                               0x1800EE38
#define VMA_DMAREG2A_7                                                               0x1800EE3C
#define VMA_DMAREG2A_0_reg_addr                                                      "0xB800EE20"
#define VMA_DMAREG2A_1_reg_addr                                                      "0xB800EE24"
#define VMA_DMAREG2A_2_reg_addr                                                      "0xB800EE28"
#define VMA_DMAREG2A_3_reg_addr                                                      "0xB800EE2C"
#define VMA_DMAREG2A_4_reg_addr                                                      "0xB800EE30"
#define VMA_DMAREG2A_5_reg_addr                                                      "0xB800EE34"
#define VMA_DMAREG2A_6_reg_addr                                                      "0xB800EE38"
#define VMA_DMAREG2A_7_reg_addr                                                      "0xB800EE3C"
#define VMA_DMAREG2A_0_reg                                                           0xB800EE20
#define VMA_DMAREG2A_1_reg                                                           0xB800EE24
#define VMA_DMAREG2A_2_reg                                                           0xB800EE28
#define VMA_DMAREG2A_3_reg                                                           0xB800EE2C
#define VMA_DMAREG2A_4_reg                                                           0xB800EE30
#define VMA_DMAREG2A_5_reg                                                           0xB800EE34
#define VMA_DMAREG2A_6_reg                                                           0xB800EE38
#define VMA_DMAREG2A_7_reg                                                           0xB800EE3C
#define set_VMA_DMAREG2A_0_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_0_reg)=data)
#define set_VMA_DMAREG2A_1_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_1_reg)=data)
#define set_VMA_DMAREG2A_2_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_2_reg)=data)
#define set_VMA_DMAREG2A_3_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_3_reg)=data)
#define set_VMA_DMAREG2A_4_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_4_reg)=data)
#define set_VMA_DMAREG2A_5_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_5_reg)=data)
#define set_VMA_DMAREG2A_6_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_6_reg)=data)
#define set_VMA_DMAREG2A_7_reg(data)   (*((volatile unsigned int*) VMA_DMAREG2A_7_reg)=data)
#define get_VMA_DMAREG2A_0_reg   (*((volatile unsigned int*) VMA_DMAREG2A_0_reg))
#define get_VMA_DMAREG2A_1_reg   (*((volatile unsigned int*) VMA_DMAREG2A_1_reg))
#define get_VMA_DMAREG2A_2_reg   (*((volatile unsigned int*) VMA_DMAREG2A_2_reg))
#define get_VMA_DMAREG2A_3_reg   (*((volatile unsigned int*) VMA_DMAREG2A_3_reg))
#define get_VMA_DMAREG2A_4_reg   (*((volatile unsigned int*) VMA_DMAREG2A_4_reg))
#define get_VMA_DMAREG2A_5_reg   (*((volatile unsigned int*) VMA_DMAREG2A_5_reg))
#define get_VMA_DMAREG2A_6_reg   (*((volatile unsigned int*) VMA_DMAREG2A_6_reg))
#define get_VMA_DMAREG2A_7_reg   (*((volatile unsigned int*) VMA_DMAREG2A_7_reg))
#define VMA_DMAREG2A_0_inst_adr                                                      "0x0088"
#define VMA_DMAREG2A_1_inst_adr                                                      "0x0089"
#define VMA_DMAREG2A_2_inst_adr                                                      "0x008A"
#define VMA_DMAREG2A_3_inst_adr                                                      "0x008B"
#define VMA_DMAREG2A_4_inst_adr                                                      "0x008C"
#define VMA_DMAREG2A_5_inst_adr                                                      "0x008D"
#define VMA_DMAREG2A_6_inst_adr                                                      "0x008E"
#define VMA_DMAREG2A_7_inst_adr                                                      "0x008F"
#define VMA_DMAREG2A_0_inst                                                          0x0088
#define VMA_DMAREG2A_1_inst                                                          0x0089
#define VMA_DMAREG2A_2_inst                                                          0x008A
#define VMA_DMAREG2A_3_inst                                                          0x008B
#define VMA_DMAREG2A_4_inst                                                          0x008C
#define VMA_DMAREG2A_5_inst                                                          0x008D
#define VMA_DMAREG2A_6_inst                                                          0x008E
#define VMA_DMAREG2A_7_inst                                                          0x008F
#define VMA_DMAREG2A_cbcr_vmOffset_shift                                             (23)
#define VMA_DMAREG2A_cbcr_vmOffset_mask                                              (0x3F800000)
#define VMA_DMAREG2A_cbcr_vmOffset(data)                                             (0x3F800000&((data)<<23))
#define VMA_DMAREG2A_cbcr_vmOffset_src(data)                                         ((0x3F800000&(data))>>23)
#define VMA_DMAREG2A_get_cbcr_vmOffset(data)                                         ((0x3F800000&(data))>>23)
#define VMA_DMAREG2A_mode_shift                                                      (22)
#define VMA_DMAREG2A_mode_mask                                                       (0x00400000)
#define VMA_DMAREG2A_mode(data)                                                      (0x00400000&((data)<<22))
#define VMA_DMAREG2A_mode_src(data)                                                  ((0x00400000&(data))>>22)
#define VMA_DMAREG2A_get_mode(data)                                                  ((0x00400000&(data))>>22)
#define VMA_DMAREG2A_right_offset_shift                                              (19)
#define VMA_DMAREG2A_right_offset_mask                                               (0x00380000)
#define VMA_DMAREG2A_right_offset(data)                                              (0x00380000&((data)<<19))
#define VMA_DMAREG2A_right_offset_src(data)                                          ((0x00380000&(data))>>19)
#define VMA_DMAREG2A_get_right_offset(data)                                          ((0x00380000&(data))>>19)
#define VMA_DMAREG2A_left_offset_shift                                               (16)
#define VMA_DMAREG2A_left_offset_mask                                                (0x00070000)
#define VMA_DMAREG2A_left_offset(data)                                               (0x00070000&((data)<<16))
#define VMA_DMAREG2A_left_offset_src(data)                                           ((0x00070000&(data))>>16)
#define VMA_DMAREG2A_get_left_offset(data)                                           ((0x00070000&(data))>>16)
#define VMA_DMAREG2A_addr_idx_shift                                                  (8)
#define VMA_DMAREG2A_addr_idx_mask                                                   (0x00007F00)
#define VMA_DMAREG2A_addr_idx(data)                                                  (0x00007F00&((data)<<8))
#define VMA_DMAREG2A_addr_idx_src(data)                                              ((0x00007F00&(data))>>8)
#define VMA_DMAREG2A_get_addr_idx(data)                                              ((0x00007F00&(data))>>8)
#define VMA_DMAREG2A_post_inc_sel_shift                                              (7)
#define VMA_DMAREG2A_post_inc_sel_mask                                               (0x00000080)
#define VMA_DMAREG2A_post_inc_sel(data)                                              (0x00000080&((data)<<7))
#define VMA_DMAREG2A_post_inc_sel_src(data)                                          ((0x00000080&(data))>>7)
#define VMA_DMAREG2A_get_post_inc_sel(data)                                          ((0x00000080&(data))>>7)
#define VMA_DMAREG2A_post_inc_shift                                                  (0)
#define VMA_DMAREG2A_post_inc_mask                                                   (0x0000003F)
#define VMA_DMAREG2A_post_inc(data)                                                  (0x0000003F&((data)<<0))
#define VMA_DMAREG2A_post_inc_src(data)                                              ((0x0000003F&(data))>>0)
#define VMA_DMAREG2A_get_post_inc(data)                                              ((0x0000003F&(data))>>0)


#define VMA_DMAREG3A_0                                                               0x1800EE40
#define VMA_DMAREG3A_1                                                               0x1800EE44
#define VMA_DMAREG3A_2                                                               0x1800EE48
#define VMA_DMAREG3A_3                                                               0x1800EE4C
#define VMA_DMAREG3A_4                                                               0x1800EE50
#define VMA_DMAREG3A_5                                                               0x1800EE54
#define VMA_DMAREG3A_6                                                               0x1800EE58
#define VMA_DMAREG3A_7                                                               0x1800EE5C
#define VMA_DMAREG3A_0_reg_addr                                                      "0xB800EE40"
#define VMA_DMAREG3A_1_reg_addr                                                      "0xB800EE44"
#define VMA_DMAREG3A_2_reg_addr                                                      "0xB800EE48"
#define VMA_DMAREG3A_3_reg_addr                                                      "0xB800EE4C"
#define VMA_DMAREG3A_4_reg_addr                                                      "0xB800EE50"
#define VMA_DMAREG3A_5_reg_addr                                                      "0xB800EE54"
#define VMA_DMAREG3A_6_reg_addr                                                      "0xB800EE58"
#define VMA_DMAREG3A_7_reg_addr                                                      "0xB800EE5C"
#define VMA_DMAREG3A_0_reg                                                           0xB800EE40
#define VMA_DMAREG3A_1_reg                                                           0xB800EE44
#define VMA_DMAREG3A_2_reg                                                           0xB800EE48
#define VMA_DMAREG3A_3_reg                                                           0xB800EE4C
#define VMA_DMAREG3A_4_reg                                                           0xB800EE50
#define VMA_DMAREG3A_5_reg                                                           0xB800EE54
#define VMA_DMAREG3A_6_reg                                                           0xB800EE58
#define VMA_DMAREG3A_7_reg                                                           0xB800EE5C
#define set_VMA_DMAREG3A_0_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_0_reg)=data)
#define set_VMA_DMAREG3A_1_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_1_reg)=data)
#define set_VMA_DMAREG3A_2_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_2_reg)=data)
#define set_VMA_DMAREG3A_3_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_3_reg)=data)
#define set_VMA_DMAREG3A_4_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_4_reg)=data)
#define set_VMA_DMAREG3A_5_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_5_reg)=data)
#define set_VMA_DMAREG3A_6_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_6_reg)=data)
#define set_VMA_DMAREG3A_7_reg(data)   (*((volatile unsigned int*) VMA_DMAREG3A_7_reg)=data)
#define get_VMA_DMAREG3A_0_reg   (*((volatile unsigned int*) VMA_DMAREG3A_0_reg))
#define get_VMA_DMAREG3A_1_reg   (*((volatile unsigned int*) VMA_DMAREG3A_1_reg))
#define get_VMA_DMAREG3A_2_reg   (*((volatile unsigned int*) VMA_DMAREG3A_2_reg))
#define get_VMA_DMAREG3A_3_reg   (*((volatile unsigned int*) VMA_DMAREG3A_3_reg))
#define get_VMA_DMAREG3A_4_reg   (*((volatile unsigned int*) VMA_DMAREG3A_4_reg))
#define get_VMA_DMAREG3A_5_reg   (*((volatile unsigned int*) VMA_DMAREG3A_5_reg))
#define get_VMA_DMAREG3A_6_reg   (*((volatile unsigned int*) VMA_DMAREG3A_6_reg))
#define get_VMA_DMAREG3A_7_reg   (*((volatile unsigned int*) VMA_DMAREG3A_7_reg))
#define VMA_DMAREG3A_0_inst_adr                                                      "0x0090"
#define VMA_DMAREG3A_1_inst_adr                                                      "0x0091"
#define VMA_DMAREG3A_2_inst_adr                                                      "0x0092"
#define VMA_DMAREG3A_3_inst_adr                                                      "0x0093"
#define VMA_DMAREG3A_4_inst_adr                                                      "0x0094"
#define VMA_DMAREG3A_5_inst_adr                                                      "0x0095"
#define VMA_DMAREG3A_6_inst_adr                                                      "0x0096"
#define VMA_DMAREG3A_7_inst_adr                                                      "0x0097"
#define VMA_DMAREG3A_0_inst                                                          0x0090
#define VMA_DMAREG3A_1_inst                                                          0x0091
#define VMA_DMAREG3A_2_inst                                                          0x0092
#define VMA_DMAREG3A_3_inst                                                          0x0093
#define VMA_DMAREG3A_4_inst                                                          0x0094
#define VMA_DMAREG3A_5_inst                                                          0x0095
#define VMA_DMAREG3A_6_inst                                                          0x0096
#define VMA_DMAREG3A_7_inst                                                          0x0097
#define VMA_DMAREG3A_line_off_shift                                                  (28)
#define VMA_DMAREG3A_line_off_mask                                                   (0x10000000)
#define VMA_DMAREG3A_line_off(data)                                                  (0x10000000&((data)<<28))
#define VMA_DMAREG3A_line_off_src(data)                                              ((0x10000000&(data))>>28)
#define VMA_DMAREG3A_get_line_off(data)                                              ((0x10000000&(data))>>28)
#define VMA_DMAREG3A_vmRowOffset_shift                                               (22)
#define VMA_DMAREG3A_vmRowOffset_mask                                                (0x07C00000)
#define VMA_DMAREG3A_vmRowOffset(data)                                               (0x07C00000&((data)<<22))
#define VMA_DMAREG3A_vmRowOffset_src(data)                                           ((0x07C00000&(data))>>22)
#define VMA_DMAREG3A_get_vmRowOffset(data)                                           ((0x07C00000&(data))>>22)
#define VMA_DMAREG3A_vm_addr_shift                                                   (12)
#define VMA_DMAREG3A_vm_addr_mask                                                    (0x0007F000)
#define VMA_DMAREG3A_vm_addr(data)                                                   (0x0007F000&((data)<<12))
#define VMA_DMAREG3A_vm_addr_src(data)                                               ((0x0007F000&(data))>>12)
#define VMA_DMAREG3A_get_vm_addr(data)                                               ((0x0007F000&(data))>>12)
#define VMA_DMAREG3A_H_shift                                                         (6)
#define VMA_DMAREG3A_H_mask                                                          (0x00000FC0)
#define VMA_DMAREG3A_H(data)                                                         (0x00000FC0&((data)<<6))
#define VMA_DMAREG3A_H_src(data)                                                     ((0x00000FC0&(data))>>6)
#define VMA_DMAREG3A_get_H(data)                                                     ((0x00000FC0&(data))>>6)
#define VMA_DMAREG3A_W_shift                                                         (0)
#define VMA_DMAREG3A_W_mask                                                          (0x0000000F)
#define VMA_DMAREG3A_W(data)                                                         (0x0000000F&((data)<<0))
#define VMA_DMAREG3A_W_src(data)                                                     ((0x0000000F&(data))>>0)
#define VMA_DMAREG3A_get_W(data)                                                     ((0x0000000F&(data))>>0)


#define VMA_SDMACNTLA                                                                0x1800EE80
#define VMA_SDMACNTLA_reg_addr                                                       "0xB800EE80"
#define VMA_SDMACNTLA_reg                                                            0xB800EE80
#define set_VMA_SDMACNTLA_reg(data)   (*((volatile unsigned int*) VMA_SDMACNTLA_reg)=data)
#define get_VMA_SDMACNTLA_reg   (*((volatile unsigned int*) VMA_SDMACNTLA_reg))
#define VMA_SDMACNTLA_inst_adr                                                       "0x00A0"
#define VMA_SDMACNTLA_inst                                                           0x00A0
#define VMA_SDMACNTLA_Seq_VMEM_addr_shift                                            (16)
#define VMA_SDMACNTLA_Seq_VMEM_addr_mask                                             (0x1FFF0000)
#define VMA_SDMACNTLA_Seq_VMEM_addr(data)                                            (0x1FFF0000&((data)<<16))
#define VMA_SDMACNTLA_Seq_VMEM_addr_src(data)                                        ((0x1FFF0000&(data))>>16)
#define VMA_SDMACNTLA_get_Seq_VMEM_addr(data)                                        ((0x1FFF0000&(data))>>16)
#define VMA_SDMACNTLA_Seq_xsfr_size_shift                                            (0)
#define VMA_SDMACNTLA_Seq_xsfr_size_mask                                             (0x000001FF)
#define VMA_SDMACNTLA_Seq_xsfr_size(data)                                            (0x000001FF&((data)<<0))
#define VMA_SDMACNTLA_Seq_xsfr_size_src(data)                                        ((0x000001FF&(data))>>0)
#define VMA_SDMACNTLA_get_Seq_xsfr_size(data)                                        ((0x000001FF&(data))>>0)


#define VMA_SDMAADRA                                                                 0x1800EE84
#define VMA_SDMAADRA_reg_addr                                                        "0xB800EE84"
#define VMA_SDMAADRA_reg                                                             0xB800EE84
#define set_VMA_SDMAADRA_reg(data)   (*((volatile unsigned int*) VMA_SDMAADRA_reg)=data)
#define get_VMA_SDMAADRA_reg   (*((volatile unsigned int*) VMA_SDMAADRA_reg))
#define VMA_SDMAADRA_inst_adr                                                        "0x00A1"
#define VMA_SDMAADRA_inst                                                            0x00A1
#define VMA_SDMAADRA_seq_line_addr_shift                                             (0)
#define VMA_SDMAADRA_seq_line_addr_mask                                              (0x7FFFFFFF)
#define VMA_SDMAADRA_seq_line_addr(data)                                             (0x7FFFFFFF&((data)<<0))
#define VMA_SDMAADRA_seq_line_addr_src(data)                                         ((0x7FFFFFFF&(data))>>0)
#define VMA_SDMAADRA_get_seq_line_addr(data)                                         ((0x7FFFFFFF&(data))>>0)


#define VMA_DMACTLA                                                                  0x1800EE88
#define VMA_DMACTLA_reg_addr                                                         "0xB800EE88"
#define VMA_DMACTLA_reg                                                              0xB800EE88
#define set_VMA_DMACTLA_reg(data)   (*((volatile unsigned int*) VMA_DMACTLA_reg)=data)
#define get_VMA_DMACTLA_reg   (*((volatile unsigned int*) VMA_DMACTLA_reg))
#define VMA_DMACTLA_inst_adr                                                         "0x00A2"
#define VMA_DMACTLA_inst                                                             0x00A2
#define VMA_DMACTLA_write_enable3_shift                                              (20)
#define VMA_DMACTLA_write_enable3_mask                                               (0x00100000)
#define VMA_DMACTLA_write_enable3(data)                                              (0x00100000&((data)<<20))
#define VMA_DMACTLA_write_enable3_src(data)                                          ((0x00100000&(data))>>20)
#define VMA_DMACTLA_get_write_enable3(data)                                          ((0x00100000&(data))>>20)
#define VMA_DMACTLA_dmem_path_shift                                                  (19)
#define VMA_DMACTLA_dmem_path_mask                                                   (0x00080000)
#define VMA_DMACTLA_dmem_path(data)                                                  (0x00080000&((data)<<19))
#define VMA_DMACTLA_dmem_path_src(data)                                              ((0x00080000&(data))>>19)
#define VMA_DMACTLA_get_dmem_path(data)                                              ((0x00080000&(data))>>19)
#define VMA_DMACTLA_write_enable2_shift                                              (18)
#define VMA_DMACTLA_write_enable2_mask                                               (0x00040000)
#define VMA_DMACTLA_write_enable2(data)                                              (0x00040000&((data)<<18))
#define VMA_DMACTLA_write_enable2_src(data)                                          ((0x00040000&(data))>>18)
#define VMA_DMACTLA_get_write_enable2(data)                                          ((0x00040000&(data))>>18)
#define VMA_DMACTLA_ldst_vmem_count_shift                                            (2)
#define VMA_DMACTLA_ldst_vmem_count_mask                                             (0x0003FFFC)
#define VMA_DMACTLA_ldst_vmem_count(data)                                            (0x0003FFFC&((data)<<2))
#define VMA_DMACTLA_ldst_vmem_count_src(data)                                        ((0x0003FFFC&(data))>>2)
#define VMA_DMACTLA_get_ldst_vmem_count(data)                                        ((0x0003FFFC&(data))>>2)
#define VMA_DMACTLA_write_enable1_shift                                              (1)
#define VMA_DMACTLA_write_enable1_mask                                               (0x00000002)
#define VMA_DMACTLA_write_enable1(data)                                              (0x00000002&((data)<<1))
#define VMA_DMACTLA_write_enable1_src(data)                                          ((0x00000002&(data))>>1)
#define VMA_DMACTLA_get_write_enable1(data)                                          ((0x00000002&(data))>>1)
#define VMA_DMACTLA_post_write_disable_shift                                         (0)
#define VMA_DMACTLA_post_write_disable_mask                                          (0x00000001)
#define VMA_DMACTLA_post_write_disable(data)                                         (0x00000001&((data)<<0))
#define VMA_DMACTLA_post_write_disable_src(data)                                     ((0x00000001&(data))>>0)
#define VMA_DMACTLA_get_post_write_disable(data)                                     ((0x00000001&(data))>>0)


#endif
