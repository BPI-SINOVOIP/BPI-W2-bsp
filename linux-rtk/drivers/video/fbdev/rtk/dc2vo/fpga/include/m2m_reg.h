/**************************************************************
// Spec Version                  : 0.2
// Parser Version                : DVR_Parser_6.10(110913)
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/1/6 22:22:6
***************************************************************/


#ifndef _M2M_REG_H_INCLUDED_
#define _M2M_REG_H_INCLUDED_
#ifdef  _M2M_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     entry:3;
unsigned int     load:1;
}M2M_LOAD_KEY;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     encode:1;
unsigned int     entry:3;
unsigned int     go:1;
}M2M_CTRL;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     length:20;
}M2M_BC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error:1;
unsigned int     done:1;
}M2M_STATUS;

typedef struct 
{
unsigned int     data:32;
}M2M_IV;

typedef struct 
{
unsigned int     data:32;
}M2M_KEY;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     residue:2;
unsigned int     reserved_1:2;
unsigned int     bcm:2;
unsigned int     reserved_2:1;
unsigned int     mode:3;
unsigned int     reserved_3:6;
unsigned int     decrypt:1;
unsigned int     encrypt:1;
}M2M_KEY_CTRL;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     adr:31;
}M2M_M2M_SRC;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     adr:31;
}M2M_M2M_DST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error:1;
unsigned int     done:1;
}M2M_STATUS_EN;

#endif

#define M2M_LOAD_KEY                                                                 0x18015E00
#define M2M_LOAD_KEY_reg_addr                                                        "0xB8015E00"
#define M2M_LOAD_KEY_reg                                                             0xB8015E00
#define set_M2M_LOAD_KEY_reg(data)   (*((volatile unsigned int*) M2M_LOAD_KEY_reg)=data)
#define get_M2M_LOAD_KEY_reg   (*((volatile unsigned int*) M2M_LOAD_KEY_reg))
#define M2M_LOAD_KEY_inst_adr                                                        "0x0080"
#define M2M_LOAD_KEY_inst                                                            0x0080
#define M2M_LOAD_KEY_entry_shift                                                     (1)
#define M2M_LOAD_KEY_entry_mask                                                      (0x0000000E)
#define M2M_LOAD_KEY_entry(data)                                                     (0x0000000E&((data)<<1))
#define M2M_LOAD_KEY_entry_src(data)                                                 ((0x0000000E&(data))>>1)
#define M2M_LOAD_KEY_get_entry(data)                                                 ((0x0000000E&(data))>>1)
#define M2M_LOAD_KEY_load_shift                                                      (0)
#define M2M_LOAD_KEY_load_mask                                                       (0x00000001)
#define M2M_LOAD_KEY_load(data)                                                      (0x00000001&((data)<<0))
#define M2M_LOAD_KEY_load_src(data)                                                  ((0x00000001&(data))>>0)
#define M2M_LOAD_KEY_get_load(data)                                                  ((0x00000001&(data))>>0)


#define M2M_CTRL                                                                     0x18015E04
#define M2M_CTRL_reg_addr                                                            "0xB8015E04"
#define M2M_CTRL_reg                                                                 0xB8015E04
#define set_M2M_CTRL_reg(data)   (*((volatile unsigned int*) M2M_CTRL_reg)=data)
#define get_M2M_CTRL_reg   (*((volatile unsigned int*) M2M_CTRL_reg))
#define M2M_CTRL_inst_adr                                                            "0x0081"
#define M2M_CTRL_inst                                                                0x0081
#define M2M_CTRL_encode_shift                                                        (4)
#define M2M_CTRL_encode_mask                                                         (0x00000010)
#define M2M_CTRL_encode(data)                                                        (0x00000010&((data)<<4))
#define M2M_CTRL_encode_src(data)                                                    ((0x00000010&(data))>>4)
#define M2M_CTRL_get_encode(data)                                                    ((0x00000010&(data))>>4)
#define M2M_CTRL_entry_shift                                                         (1)
#define M2M_CTRL_entry_mask                                                          (0x0000000E)
#define M2M_CTRL_entry(data)                                                         (0x0000000E&((data)<<1))
#define M2M_CTRL_entry_src(data)                                                     ((0x0000000E&(data))>>1)
#define M2M_CTRL_get_entry(data)                                                     ((0x0000000E&(data))>>1)
#define M2M_CTRL_go_shift                                                            (0)
#define M2M_CTRL_go_mask                                                             (0x00000001)
#define M2M_CTRL_go(data)                                                            (0x00000001&((data)<<0))
#define M2M_CTRL_go_src(data)                                                        ((0x00000001&(data))>>0)
#define M2M_CTRL_get_go(data)                                                        ((0x00000001&(data))>>0)


#define M2M_BC                                                                       0x18015E08
#define M2M_BC_reg_addr                                                              "0xB8015E08"
#define M2M_BC_reg                                                                   0xB8015E08
#define set_M2M_BC_reg(data)   (*((volatile unsigned int*) M2M_BC_reg)=data)
#define get_M2M_BC_reg   (*((volatile unsigned int*) M2M_BC_reg))
#define M2M_BC_inst_adr                                                              "0x0082"
#define M2M_BC_inst                                                                  0x0082
#define M2M_BC_length_shift                                                          (0)
#define M2M_BC_length_mask                                                           (0x000FFFFF)
#define M2M_BC_length(data)                                                          (0x000FFFFF&((data)<<0))
#define M2M_BC_length_src(data)                                                      ((0x000FFFFF&(data))>>0)
#define M2M_BC_get_length(data)                                                      ((0x000FFFFF&(data))>>0)


#define M2M_STATUS                                                                   0x18015E0C
#define M2M_STATUS_reg_addr                                                          "0xB8015E0C"
#define M2M_STATUS_reg                                                               0xB8015E0C
#define set_M2M_STATUS_reg(data)   (*((volatile unsigned int*) M2M_STATUS_reg)=data)
#define get_M2M_STATUS_reg   (*((volatile unsigned int*) M2M_STATUS_reg))
#define M2M_STATUS_inst_adr                                                          "0x0083"
#define M2M_STATUS_inst                                                              0x0083
#define M2M_STATUS_error_shift                                                       (1)
#define M2M_STATUS_error_mask                                                        (0x00000002)
#define M2M_STATUS_error(data)                                                       (0x00000002&((data)<<1))
#define M2M_STATUS_error_src(data)                                                   ((0x00000002&(data))>>1)
#define M2M_STATUS_get_error(data)                                                   ((0x00000002&(data))>>1)
#define M2M_STATUS_done_shift                                                        (0)
#define M2M_STATUS_done_mask                                                         (0x00000001)
#define M2M_STATUS_done(data)                                                        (0x00000001&((data)<<0))
#define M2M_STATUS_done_src(data)                                                    ((0x00000001&(data))>>0)
#define M2M_STATUS_get_done(data)                                                    ((0x00000001&(data))>>0)


#define M2M_IV_0                                                                     0x18015E10
#define M2M_IV_1                                                                     0x18015E14
#define M2M_IV_2                                                                     0x18015E18
#define M2M_IV_3                                                                     0x18015E1C
#define M2M_IV_0_reg_addr                                                            "0xB8015E10"
#define M2M_IV_1_reg_addr                                                            "0xB8015E14"
#define M2M_IV_2_reg_addr                                                            "0xB8015E18"
#define M2M_IV_3_reg_addr                                                            "0xB8015E1C"
#define M2M_IV_0_reg                                                                 0xB8015E10
#define M2M_IV_1_reg                                                                 0xB8015E14
#define M2M_IV_2_reg                                                                 0xB8015E18
#define M2M_IV_3_reg                                                                 0xB8015E1C
#define set_M2M_IV_0_reg(data)   (*((volatile unsigned int*) M2M_IV_0_reg)=data)
#define set_M2M_IV_1_reg(data)   (*((volatile unsigned int*) M2M_IV_1_reg)=data)
#define set_M2M_IV_2_reg(data)   (*((volatile unsigned int*) M2M_IV_2_reg)=data)
#define set_M2M_IV_3_reg(data)   (*((volatile unsigned int*) M2M_IV_3_reg)=data)
#define get_M2M_IV_0_reg   (*((volatile unsigned int*) M2M_IV_0_reg))
#define get_M2M_IV_1_reg   (*((volatile unsigned int*) M2M_IV_1_reg))
#define get_M2M_IV_2_reg   (*((volatile unsigned int*) M2M_IV_2_reg))
#define get_M2M_IV_3_reg   (*((volatile unsigned int*) M2M_IV_3_reg))
#define M2M_IV_0_inst_adr                                                            "0x0084"
#define M2M_IV_1_inst_adr                                                            "0x0085"
#define M2M_IV_2_inst_adr                                                            "0x0086"
#define M2M_IV_3_inst_adr                                                            "0x0087"
#define M2M_IV_0_inst                                                                0x0084
#define M2M_IV_1_inst                                                                0x0085
#define M2M_IV_2_inst                                                                0x0086
#define M2M_IV_3_inst                                                                0x0087
#define M2M_IV_data_shift                                                            (0)
#define M2M_IV_data_mask                                                             (0xFFFFFFFF)
#define M2M_IV_data(data)                                                            (0xFFFFFFFF&((data)<<0))
#define M2M_IV_data_src(data)                                                        ((0xFFFFFFFF&(data))>>0)
#define M2M_IV_get_data(data)                                                        ((0xFFFFFFFF&(data))>>0)


#define M2M_KEY_0                                                                    0x18015E20
#define M2M_KEY_1                                                                    0x18015E24
#define M2M_KEY_2                                                                    0x18015E28
#define M2M_KEY_3                                                                    0x18015E2C
#define M2M_KEY_4                                                                    0x18015E30
#define M2M_KEY_5                                                                    0x18015E34
#define M2M_KEY_6                                                                    0x18015E38
#define M2M_KEY_7                                                                    0x18015E3C
#define M2M_KEY_8                                                                    0x18015E40
#define M2M_KEY_9                                                                    0x18015E44
#define M2M_KEY_10                                                                    0x18015E48
#define M2M_KEY_11                                                                    0x18015E4C
#define M2M_KEY_12                                                                    0x18015E50
#define M2M_KEY_13                                                                    0x18015E54
#define M2M_KEY_14                                                                    0x18015E58
#define M2M_KEY_15                                                                    0x18015E5C
#define M2M_KEY_16                                                                    0x18015E60
#define M2M_KEY_17                                                                    0x18015E64
#define M2M_KEY_18                                                                    0x18015E68
#define M2M_KEY_19                                                                    0x18015E6C
#define M2M_KEY_20                                                                    0x18015E70
#define M2M_KEY_21                                                                    0x18015E74
#define M2M_KEY_22                                                                    0x18015E78
#define M2M_KEY_23                                                                    0x18015E7C
#define M2M_KEY_24                                                                    0x18015E80
#define M2M_KEY_25                                                                    0x18015E84
#define M2M_KEY_26                                                                    0x18015E88
#define M2M_KEY_27                                                                    0x18015E8C
#define M2M_KEY_28                                                                    0x18015E90
#define M2M_KEY_29                                                                    0x18015E94
#define M2M_KEY_30                                                                    0x18015E98
#define M2M_KEY_31                                                                    0x18015E9C
#define M2M_KEY_0_reg_addr                                                           "0xB8015E20"
#define M2M_KEY_1_reg_addr                                                           "0xB8015E24"
#define M2M_KEY_2_reg_addr                                                           "0xB8015E28"
#define M2M_KEY_3_reg_addr                                                           "0xB8015E2C"
#define M2M_KEY_4_reg_addr                                                           "0xB8015E30"
#define M2M_KEY_5_reg_addr                                                           "0xB8015E34"
#define M2M_KEY_6_reg_addr                                                           "0xB8015E38"
#define M2M_KEY_7_reg_addr                                                           "0xB8015E3C"
#define M2M_KEY_8_reg_addr                                                           "0xB8015E40"
#define M2M_KEY_9_reg_addr                                                           "0xB8015E44"
#define M2M_KEY_10_reg_addr                                                           "0xB8015E48"
#define M2M_KEY_11_reg_addr                                                           "0xB8015E4C"
#define M2M_KEY_12_reg_addr                                                           "0xB8015E50"
#define M2M_KEY_13_reg_addr                                                           "0xB8015E54"
#define M2M_KEY_14_reg_addr                                                           "0xB8015E58"
#define M2M_KEY_15_reg_addr                                                           "0xB8015E5C"
#define M2M_KEY_16_reg_addr                                                           "0xB8015E60"
#define M2M_KEY_17_reg_addr                                                           "0xB8015E64"
#define M2M_KEY_18_reg_addr                                                           "0xB8015E68"
#define M2M_KEY_19_reg_addr                                                           "0xB8015E6C"
#define M2M_KEY_20_reg_addr                                                           "0xB8015E70"
#define M2M_KEY_21_reg_addr                                                           "0xB8015E74"
#define M2M_KEY_22_reg_addr                                                           "0xB8015E78"
#define M2M_KEY_23_reg_addr                                                           "0xB8015E7C"
#define M2M_KEY_24_reg_addr                                                           "0xB8015E80"
#define M2M_KEY_25_reg_addr                                                           "0xB8015E84"
#define M2M_KEY_26_reg_addr                                                           "0xB8015E88"
#define M2M_KEY_27_reg_addr                                                           "0xB8015E8C"
#define M2M_KEY_28_reg_addr                                                           "0xB8015E90"
#define M2M_KEY_29_reg_addr                                                           "0xB8015E94"
#define M2M_KEY_30_reg_addr                                                           "0xB8015E98"
#define M2M_KEY_31_reg_addr                                                           "0xB8015E9C"
#define M2M_KEY_0_reg                                                                0xB8015E20
#define M2M_KEY_1_reg                                                                0xB8015E24
#define M2M_KEY_2_reg                                                                0xB8015E28
#define M2M_KEY_3_reg                                                                0xB8015E2C
#define M2M_KEY_4_reg                                                                0xB8015E30
#define M2M_KEY_5_reg                                                                0xB8015E34
#define M2M_KEY_6_reg                                                                0xB8015E38
#define M2M_KEY_7_reg                                                                0xB8015E3C
#define M2M_KEY_8_reg                                                                0xB8015E40
#define M2M_KEY_9_reg                                                                0xB8015E44
#define M2M_KEY_10_reg                                                                0xB8015E48
#define M2M_KEY_11_reg                                                                0xB8015E4C
#define M2M_KEY_12_reg                                                                0xB8015E50
#define M2M_KEY_13_reg                                                                0xB8015E54
#define M2M_KEY_14_reg                                                                0xB8015E58
#define M2M_KEY_15_reg                                                                0xB8015E5C
#define M2M_KEY_16_reg                                                                0xB8015E60
#define M2M_KEY_17_reg                                                                0xB8015E64
#define M2M_KEY_18_reg                                                                0xB8015E68
#define M2M_KEY_19_reg                                                                0xB8015E6C
#define M2M_KEY_20_reg                                                                0xB8015E70
#define M2M_KEY_21_reg                                                                0xB8015E74
#define M2M_KEY_22_reg                                                                0xB8015E78
#define M2M_KEY_23_reg                                                                0xB8015E7C
#define M2M_KEY_24_reg                                                                0xB8015E80
#define M2M_KEY_25_reg                                                                0xB8015E84
#define M2M_KEY_26_reg                                                                0xB8015E88
#define M2M_KEY_27_reg                                                                0xB8015E8C
#define M2M_KEY_28_reg                                                                0xB8015E90
#define M2M_KEY_29_reg                                                                0xB8015E94
#define M2M_KEY_30_reg                                                                0xB8015E98
#define M2M_KEY_31_reg                                                                0xB8015E9C
#define set_M2M_KEY_0_reg(data)   (*((volatile unsigned int*) M2M_KEY_0_reg)=data)
#define set_M2M_KEY_1_reg(data)   (*((volatile unsigned int*) M2M_KEY_1_reg)=data)
#define set_M2M_KEY_2_reg(data)   (*((volatile unsigned int*) M2M_KEY_2_reg)=data)
#define set_M2M_KEY_3_reg(data)   (*((volatile unsigned int*) M2M_KEY_3_reg)=data)
#define set_M2M_KEY_4_reg(data)   (*((volatile unsigned int*) M2M_KEY_4_reg)=data)
#define set_M2M_KEY_5_reg(data)   (*((volatile unsigned int*) M2M_KEY_5_reg)=data)
#define set_M2M_KEY_6_reg(data)   (*((volatile unsigned int*) M2M_KEY_6_reg)=data)
#define set_M2M_KEY_7_reg(data)   (*((volatile unsigned int*) M2M_KEY_7_reg)=data)
#define set_M2M_KEY_8_reg(data)   (*((volatile unsigned int*) M2M_KEY_8_reg)=data)
#define set_M2M_KEY_9_reg(data)   (*((volatile unsigned int*) M2M_KEY_9_reg)=data)
#define set_M2M_KEY_10_reg(data)   (*((volatile unsigned int*) M2M_KEY_10_reg)=data)
#define set_M2M_KEY_11_reg(data)   (*((volatile unsigned int*) M2M_KEY_11_reg)=data)
#define set_M2M_KEY_12_reg(data)   (*((volatile unsigned int*) M2M_KEY_12_reg)=data)
#define set_M2M_KEY_13_reg(data)   (*((volatile unsigned int*) M2M_KEY_13_reg)=data)
#define set_M2M_KEY_14_reg(data)   (*((volatile unsigned int*) M2M_KEY_14_reg)=data)
#define set_M2M_KEY_15_reg(data)   (*((volatile unsigned int*) M2M_KEY_15_reg)=data)
#define set_M2M_KEY_16_reg(data)   (*((volatile unsigned int*) M2M_KEY_16_reg)=data)
#define set_M2M_KEY_17_reg(data)   (*((volatile unsigned int*) M2M_KEY_17_reg)=data)
#define set_M2M_KEY_18_reg(data)   (*((volatile unsigned int*) M2M_KEY_18_reg)=data)
#define set_M2M_KEY_19_reg(data)   (*((volatile unsigned int*) M2M_KEY_19_reg)=data)
#define set_M2M_KEY_20_reg(data)   (*((volatile unsigned int*) M2M_KEY_20_reg)=data)
#define set_M2M_KEY_21_reg(data)   (*((volatile unsigned int*) M2M_KEY_21_reg)=data)
#define set_M2M_KEY_22_reg(data)   (*((volatile unsigned int*) M2M_KEY_22_reg)=data)
#define set_M2M_KEY_23_reg(data)   (*((volatile unsigned int*) M2M_KEY_23_reg)=data)
#define set_M2M_KEY_24_reg(data)   (*((volatile unsigned int*) M2M_KEY_24_reg)=data)
#define set_M2M_KEY_25_reg(data)   (*((volatile unsigned int*) M2M_KEY_25_reg)=data)
#define set_M2M_KEY_26_reg(data)   (*((volatile unsigned int*) M2M_KEY_26_reg)=data)
#define set_M2M_KEY_27_reg(data)   (*((volatile unsigned int*) M2M_KEY_27_reg)=data)
#define set_M2M_KEY_28_reg(data)   (*((volatile unsigned int*) M2M_KEY_28_reg)=data)
#define set_M2M_KEY_29_reg(data)   (*((volatile unsigned int*) M2M_KEY_29_reg)=data)
#define set_M2M_KEY_30_reg(data)   (*((volatile unsigned int*) M2M_KEY_30_reg)=data)
#define set_M2M_KEY_31_reg(data)   (*((volatile unsigned int*) M2M_KEY_31_reg)=data)
#define get_M2M_KEY_0_reg   (*((volatile unsigned int*) M2M_KEY_0_reg))
#define get_M2M_KEY_1_reg   (*((volatile unsigned int*) M2M_KEY_1_reg))
#define get_M2M_KEY_2_reg   (*((volatile unsigned int*) M2M_KEY_2_reg))
#define get_M2M_KEY_3_reg   (*((volatile unsigned int*) M2M_KEY_3_reg))
#define get_M2M_KEY_4_reg   (*((volatile unsigned int*) M2M_KEY_4_reg))
#define get_M2M_KEY_5_reg   (*((volatile unsigned int*) M2M_KEY_5_reg))
#define get_M2M_KEY_6_reg   (*((volatile unsigned int*) M2M_KEY_6_reg))
#define get_M2M_KEY_7_reg   (*((volatile unsigned int*) M2M_KEY_7_reg))
#define get_M2M_KEY_8_reg   (*((volatile unsigned int*) M2M_KEY_8_reg))
#define get_M2M_KEY_9_reg   (*((volatile unsigned int*) M2M_KEY_9_reg))
#define get_M2M_KEY_10_reg   (*((volatile unsigned int*) M2M_KEY_10_reg))
#define get_M2M_KEY_11_reg   (*((volatile unsigned int*) M2M_KEY_11_reg))
#define get_M2M_KEY_12_reg   (*((volatile unsigned int*) M2M_KEY_12_reg))
#define get_M2M_KEY_13_reg   (*((volatile unsigned int*) M2M_KEY_13_reg))
#define get_M2M_KEY_14_reg   (*((volatile unsigned int*) M2M_KEY_14_reg))
#define get_M2M_KEY_15_reg   (*((volatile unsigned int*) M2M_KEY_15_reg))
#define get_M2M_KEY_16_reg   (*((volatile unsigned int*) M2M_KEY_16_reg))
#define get_M2M_KEY_17_reg   (*((volatile unsigned int*) M2M_KEY_17_reg))
#define get_M2M_KEY_18_reg   (*((volatile unsigned int*) M2M_KEY_18_reg))
#define get_M2M_KEY_19_reg   (*((volatile unsigned int*) M2M_KEY_19_reg))
#define get_M2M_KEY_20_reg   (*((volatile unsigned int*) M2M_KEY_20_reg))
#define get_M2M_KEY_21_reg   (*((volatile unsigned int*) M2M_KEY_21_reg))
#define get_M2M_KEY_22_reg   (*((volatile unsigned int*) M2M_KEY_22_reg))
#define get_M2M_KEY_23_reg   (*((volatile unsigned int*) M2M_KEY_23_reg))
#define get_M2M_KEY_24_reg   (*((volatile unsigned int*) M2M_KEY_24_reg))
#define get_M2M_KEY_25_reg   (*((volatile unsigned int*) M2M_KEY_25_reg))
#define get_M2M_KEY_26_reg   (*((volatile unsigned int*) M2M_KEY_26_reg))
#define get_M2M_KEY_27_reg   (*((volatile unsigned int*) M2M_KEY_27_reg))
#define get_M2M_KEY_28_reg   (*((volatile unsigned int*) M2M_KEY_28_reg))
#define get_M2M_KEY_29_reg   (*((volatile unsigned int*) M2M_KEY_29_reg))
#define get_M2M_KEY_30_reg   (*((volatile unsigned int*) M2M_KEY_30_reg))
#define get_M2M_KEY_31_reg   (*((volatile unsigned int*) M2M_KEY_31_reg))
#define M2M_KEY_0_inst_adr                                                           "0x0088"
#define M2M_KEY_1_inst_adr                                                           "0x0089"
#define M2M_KEY_2_inst_adr                                                           "0x008A"
#define M2M_KEY_3_inst_adr                                                           "0x008B"
#define M2M_KEY_4_inst_adr                                                           "0x008C"
#define M2M_KEY_5_inst_adr                                                           "0x008D"
#define M2M_KEY_6_inst_adr                                                           "0x008E"
#define M2M_KEY_7_inst_adr                                                           "0x008F"
#define M2M_KEY_8_inst_adr                                                           "0x0090"
#define M2M_KEY_9_inst_adr                                                           "0x0091"
#define M2M_KEY_10_inst_adr                                                           "0x0092"
#define M2M_KEY_11_inst_adr                                                           "0x0093"
#define M2M_KEY_12_inst_adr                                                           "0x0094"
#define M2M_KEY_13_inst_adr                                                           "0x0095"
#define M2M_KEY_14_inst_adr                                                           "0x0096"
#define M2M_KEY_15_inst_adr                                                           "0x0097"
#define M2M_KEY_16_inst_adr                                                           "0x0098"
#define M2M_KEY_17_inst_adr                                                           "0x0099"
#define M2M_KEY_18_inst_adr                                                           "0x009A"
#define M2M_KEY_19_inst_adr                                                           "0x009B"
#define M2M_KEY_20_inst_adr                                                           "0x009C"
#define M2M_KEY_21_inst_adr                                                           "0x009D"
#define M2M_KEY_22_inst_adr                                                           "0x009E"
#define M2M_KEY_23_inst_adr                                                           "0x009F"
#define M2M_KEY_24_inst_adr                                                           "0x00A0"
#define M2M_KEY_25_inst_adr                                                           "0x00A1"
#define M2M_KEY_26_inst_adr                                                           "0x00A2"
#define M2M_KEY_27_inst_adr                                                           "0x00A3"
#define M2M_KEY_28_inst_adr                                                           "0x00A4"
#define M2M_KEY_29_inst_adr                                                           "0x00A5"
#define M2M_KEY_30_inst_adr                                                           "0x00A6"
#define M2M_KEY_31_inst_adr                                                           "0x00A7"
#define M2M_KEY_0_inst                                                               0x0088
#define M2M_KEY_1_inst                                                               0x0089
#define M2M_KEY_2_inst                                                               0x008A
#define M2M_KEY_3_inst                                                               0x008B
#define M2M_KEY_4_inst                                                               0x008C
#define M2M_KEY_5_inst                                                               0x008D
#define M2M_KEY_6_inst                                                               0x008E
#define M2M_KEY_7_inst                                                               0x008F
#define M2M_KEY_8_inst                                                               0x0090
#define M2M_KEY_9_inst                                                               0x0091
#define M2M_KEY_10_inst                                                               0x0092
#define M2M_KEY_11_inst                                                               0x0093
#define M2M_KEY_12_inst                                                               0x0094
#define M2M_KEY_13_inst                                                               0x0095
#define M2M_KEY_14_inst                                                               0x0096
#define M2M_KEY_15_inst                                                               0x0097
#define M2M_KEY_16_inst                                                               0x0098
#define M2M_KEY_17_inst                                                               0x0099
#define M2M_KEY_18_inst                                                               0x009A
#define M2M_KEY_19_inst                                                               0x009B
#define M2M_KEY_20_inst                                                               0x009C
#define M2M_KEY_21_inst                                                               0x009D
#define M2M_KEY_22_inst                                                               0x009E
#define M2M_KEY_23_inst                                                               0x009F
#define M2M_KEY_24_inst                                                               0x00A0
#define M2M_KEY_25_inst                                                               0x00A1
#define M2M_KEY_26_inst                                                               0x00A2
#define M2M_KEY_27_inst                                                               0x00A3
#define M2M_KEY_28_inst                                                               0x00A4
#define M2M_KEY_29_inst                                                               0x00A5
#define M2M_KEY_30_inst                                                               0x00A6
#define M2M_KEY_31_inst                                                               0x00A7
#define M2M_KEY_data_shift                                                           (0)
#define M2M_KEY_data_mask                                                            (0xFFFFFFFF)
#define M2M_KEY_data(data)                                                           (0xFFFFFFFF&((data)<<0))
#define M2M_KEY_data_src(data)                                                       ((0xFFFFFFFF&(data))>>0)
#define M2M_KEY_get_data(data)                                                       ((0xFFFFFFFF&(data))>>0)


#define M2M_KEY_CTRL_0                                                               0x18015EA0
#define M2M_KEY_CTRL_1                                                               0x18015EA4
#define M2M_KEY_CTRL_2                                                               0x18015EA8
#define M2M_KEY_CTRL_3                                                               0x18015EAC
#define M2M_KEY_CTRL_4                                                               0x18015EB0
#define M2M_KEY_CTRL_5                                                               0x18015EB4
#define M2M_KEY_CTRL_6                                                               0x18015EB8
#define M2M_KEY_CTRL_7                                                               0x18015EBC
#define M2M_KEY_CTRL_0_reg_addr                                                      "0xB8015EA0"
#define M2M_KEY_CTRL_1_reg_addr                                                      "0xB8015EA4"
#define M2M_KEY_CTRL_2_reg_addr                                                      "0xB8015EA8"
#define M2M_KEY_CTRL_3_reg_addr                                                      "0xB8015EAC"
#define M2M_KEY_CTRL_4_reg_addr                                                      "0xB8015EB0"
#define M2M_KEY_CTRL_5_reg_addr                                                      "0xB8015EB4"
#define M2M_KEY_CTRL_6_reg_addr                                                      "0xB8015EB8"
#define M2M_KEY_CTRL_7_reg_addr                                                      "0xB8015EBC"
#define M2M_KEY_CTRL_0_reg                                                           0xB8015EA0
#define M2M_KEY_CTRL_1_reg                                                           0xB8015EA4
#define M2M_KEY_CTRL_2_reg                                                           0xB8015EA8
#define M2M_KEY_CTRL_3_reg                                                           0xB8015EAC
#define M2M_KEY_CTRL_4_reg                                                           0xB8015EB0
#define M2M_KEY_CTRL_5_reg                                                           0xB8015EB4
#define M2M_KEY_CTRL_6_reg                                                           0xB8015EB8
#define M2M_KEY_CTRL_7_reg                                                           0xB8015EBC
#define set_M2M_KEY_CTRL_0_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_0_reg)=data)
#define set_M2M_KEY_CTRL_1_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_1_reg)=data)
#define set_M2M_KEY_CTRL_2_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_2_reg)=data)
#define set_M2M_KEY_CTRL_3_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_3_reg)=data)
#define set_M2M_KEY_CTRL_4_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_4_reg)=data)
#define set_M2M_KEY_CTRL_5_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_5_reg)=data)
#define set_M2M_KEY_CTRL_6_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_6_reg)=data)
#define set_M2M_KEY_CTRL_7_reg(data)   (*((volatile unsigned int*) M2M_KEY_CTRL_7_reg)=data)
#define get_M2M_KEY_CTRL_0_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_0_reg))
#define get_M2M_KEY_CTRL_1_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_1_reg))
#define get_M2M_KEY_CTRL_2_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_2_reg))
#define get_M2M_KEY_CTRL_3_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_3_reg))
#define get_M2M_KEY_CTRL_4_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_4_reg))
#define get_M2M_KEY_CTRL_5_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_5_reg))
#define get_M2M_KEY_CTRL_6_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_6_reg))
#define get_M2M_KEY_CTRL_7_reg   (*((volatile unsigned int*) M2M_KEY_CTRL_7_reg))
#define M2M_KEY_CTRL_0_inst_adr                                                      "0x00A8"
#define M2M_KEY_CTRL_1_inst_adr                                                      "0x00A9"
#define M2M_KEY_CTRL_2_inst_adr                                                      "0x00AA"
#define M2M_KEY_CTRL_3_inst_adr                                                      "0x00AB"
#define M2M_KEY_CTRL_4_inst_adr                                                      "0x00AC"
#define M2M_KEY_CTRL_5_inst_adr                                                      "0x00AD"
#define M2M_KEY_CTRL_6_inst_adr                                                      "0x00AE"
#define M2M_KEY_CTRL_7_inst_adr                                                      "0x00AF"
#define M2M_KEY_CTRL_0_inst                                                          0x00A8
#define M2M_KEY_CTRL_1_inst                                                          0x00A9
#define M2M_KEY_CTRL_2_inst                                                          0x00AA
#define M2M_KEY_CTRL_3_inst                                                          0x00AB
#define M2M_KEY_CTRL_4_inst                                                          0x00AC
#define M2M_KEY_CTRL_5_inst                                                          0x00AD
#define M2M_KEY_CTRL_6_inst                                                          0x00AE
#define M2M_KEY_CTRL_7_inst                                                          0x00AF
#define M2M_KEY_CTRL_residue_shift                                                   (16)
#define M2M_KEY_CTRL_residue_mask                                                    (0x00030000)
#define M2M_KEY_CTRL_residue(data)                                                   (0x00030000&((data)<<16))
#define M2M_KEY_CTRL_residue_src(data)                                               ((0x00030000&(data))>>16)
#define M2M_KEY_CTRL_get_residue(data)                                               ((0x00030000&(data))>>16)
#define M2M_KEY_CTRL_bcm_shift                                                       (12)
#define M2M_KEY_CTRL_bcm_mask                                                        (0x00003000)
#define M2M_KEY_CTRL_bcm(data)                                                       (0x00003000&((data)<<12))
#define M2M_KEY_CTRL_bcm_src(data)                                                   ((0x00003000&(data))>>12)
#define M2M_KEY_CTRL_get_bcm(data)                                                   ((0x00003000&(data))>>12)
#define M2M_KEY_CTRL_mode_shift                                                      (8)
#define M2M_KEY_CTRL_mode_mask                                                       (0x00000700)
#define M2M_KEY_CTRL_mode(data)                                                      (0x00000700&((data)<<8))
#define M2M_KEY_CTRL_mode_src(data)                                                  ((0x00000700&(data))>>8)
#define M2M_KEY_CTRL_get_mode(data)                                                  ((0x00000700&(data))>>8)
#define M2M_KEY_CTRL_decrypt_shift                                                   (1)
#define M2M_KEY_CTRL_decrypt_mask                                                    (0x00000002)
#define M2M_KEY_CTRL_decrypt(data)                                                   (0x00000002&((data)<<1))
#define M2M_KEY_CTRL_decrypt_src(data)                                               ((0x00000002&(data))>>1)
#define M2M_KEY_CTRL_get_decrypt(data)                                               ((0x00000002&(data))>>1)
#define M2M_KEY_CTRL_encrypt_shift                                                   (0)
#define M2M_KEY_CTRL_encrypt_mask                                                    (0x00000001)
#define M2M_KEY_CTRL_encrypt(data)                                                   (0x00000001&((data)<<0))
#define M2M_KEY_CTRL_encrypt_src(data)                                               ((0x00000001&(data))>>0)
#define M2M_KEY_CTRL_get_encrypt(data)                                               ((0x00000001&(data))>>0)


#define M2M_M2M_SRC                                                                  0x18015EC0
#define M2M_M2M_SRC_reg_addr                                                         "0xB8015EC0"
#define M2M_M2M_SRC_reg                                                              0xB8015EC0
#define set_M2M_M2M_SRC_reg(data)   (*((volatile unsigned int*) M2M_M2M_SRC_reg)=data)
#define get_M2M_M2M_SRC_reg   (*((volatile unsigned int*) M2M_M2M_SRC_reg))
#define M2M_M2M_SRC_inst_adr                                                         "0x00B0"
#define M2M_M2M_SRC_inst                                                             0x00B0
#define M2M_M2M_SRC_adr_shift                                                        (0)
#define M2M_M2M_SRC_adr_mask                                                         (0x7FFFFFFF)
#define M2M_M2M_SRC_adr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define M2M_M2M_SRC_adr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define M2M_M2M_SRC_get_adr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define M2M_M2M_DST                                                                  0x18015EC4
#define M2M_M2M_DST_reg_addr                                                         "0xB8015EC4"
#define M2M_M2M_DST_reg                                                              0xB8015EC4
#define set_M2M_M2M_DST_reg(data)   (*((volatile unsigned int*) M2M_M2M_DST_reg)=data)
#define get_M2M_M2M_DST_reg   (*((volatile unsigned int*) M2M_M2M_DST_reg))
#define M2M_M2M_DST_inst_adr                                                         "0x00B1"
#define M2M_M2M_DST_inst                                                             0x00B1
#define M2M_M2M_DST_adr_shift                                                        (0)
#define M2M_M2M_DST_adr_mask                                                         (0x7FFFFFFF)
#define M2M_M2M_DST_adr(data)                                                        (0x7FFFFFFF&((data)<<0))
#define M2M_M2M_DST_adr_src(data)                                                    ((0x7FFFFFFF&(data))>>0)
#define M2M_M2M_DST_get_adr(data)                                                    ((0x7FFFFFFF&(data))>>0)


#define M2M_STATUS_EN                                                                0x18015EC8
#define M2M_STATUS_EN_reg_addr                                                       "0xB8015EC8"
#define M2M_STATUS_EN_reg                                                            0xB8015EC8
#define set_M2M_STATUS_EN_reg(data)   (*((volatile unsigned int*) M2M_STATUS_EN_reg)=data)
#define get_M2M_STATUS_EN_reg   (*((volatile unsigned int*) M2M_STATUS_EN_reg))
#define M2M_STATUS_EN_inst_adr                                                       "0x00B2"
#define M2M_STATUS_EN_inst                                                           0x00B2
#define M2M_STATUS_EN_error_shift                                                    (1)
#define M2M_STATUS_EN_error_mask                                                     (0x00000002)
#define M2M_STATUS_EN_error(data)                                                    (0x00000002&((data)<<1))
#define M2M_STATUS_EN_error_src(data)                                                ((0x00000002&(data))>>1)
#define M2M_STATUS_EN_get_error(data)                                                ((0x00000002&(data))>>1)
#define M2M_STATUS_EN_done_shift                                                     (0)
#define M2M_STATUS_EN_done_mask                                                      (0x00000001)
#define M2M_STATUS_EN_done(data)                                                     (0x00000001&((data)<<0))
#define M2M_STATUS_EN_done_src(data)                                                 ((0x00000001&(data))>>0)
#define M2M_STATUS_EN_get_done(data)                                                 ((0x00000001&(data))>>0)


#endif
