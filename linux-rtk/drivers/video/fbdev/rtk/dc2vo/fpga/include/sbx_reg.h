/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/8/12 12:49:48
***************************************************************/


#ifndef _SBX_REG_H_INCLUDED_
#define _SBX_REG_H_INCLUDED_
#ifdef  _SBX_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     tp:4;
unsigned int     reserved_1:4;
unsigned int     etn:4;
unsigned int     reserved_2:4;
unsigned int     etn2:4;
unsigned int     reserved_3:4;
unsigned int     sata:4;
}SB1_PRIORITY_1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     nf:4;
unsigned int     reserved_1:4;
unsigned int     usb:4;
unsigned int     reserved_2:4;
unsigned int     cp:4;
unsigned int     reserved_3:4;
unsigned int     cr:4;
}SB1_PRIORITY_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB1_CHANNEL_HIGH_PRIORITY;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB1_CHANNEL_REQ_MASK;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB1_CHANNEL_REQ_BUSY;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     allow_cmd_cnt:3;
}SB1_MISC_CTRL;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     md:4;
unsigned int     reserved_1:4;
unsigned int     reserved_2:4;
unsigned int     reserved_3:4;
unsigned int     ade:4;
unsigned int     reserved_4:4;
unsigned int     aee:4;
}SB3_PRIORITY_1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     me:4;
unsigned int     reserved_1:4;
unsigned int     hif:4;
unsigned int     reserved_2:4;
unsigned int     jpeg:4;
unsigned int     reserved_3:4;
unsigned int     ve:4;
}SB3_PRIORITY_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB3_CHANNEL_HIGH_PRIORITY;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB3_CHANNEL_REQ_MASK;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB3_CHANNEL_REQ_BUSY;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     allow_cmd_cnt:3;
}SB3_MISC_CTRL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     vi:4;
unsigned int     reserved_1:4;
unsigned int     aio:4;
}SB0_PRIORITY_1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB0_CHANNEL_REQ_MASK;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     index:8;
}SB0_CHANNEL_REQ_BUSY;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     allow_cmd_cnt:3;
}SB0_MISC_CTRL;

#endif

#define SB1_PRIORITY_1                                                               0x1801C000
#define SB1_PRIORITY_1_reg_addr                                                      "0xB801C000"
#define SB1_PRIORITY_1_reg                                                           0xB801C000
#define set_SB1_PRIORITY_1_reg(data)   (*((volatile unsigned int*) SB1_PRIORITY_1_reg)=data)
#define get_SB1_PRIORITY_1_reg   (*((volatile unsigned int*) SB1_PRIORITY_1_reg))
#define SB1_PRIORITY_1_inst_adr                                                      "0x0000"
#define SB1_PRIORITY_1_inst                                                          0x0000
#define SB1_PRIORITY_1_tp_shift                                                      (24)
#define SB1_PRIORITY_1_tp_mask                                                       (0x0F000000)
#define SB1_PRIORITY_1_tp(data)                                                      (0x0F000000&((data)<<24))
#define SB1_PRIORITY_1_tp_src(data)                                                  ((0x0F000000&(data))>>24)
#define SB1_PRIORITY_1_get_tp(data)                                                  ((0x0F000000&(data))>>24)
#define SB1_PRIORITY_1_etn_shift                                                     (16)
#define SB1_PRIORITY_1_etn_mask                                                      (0x000F0000)
#define SB1_PRIORITY_1_etn(data)                                                     (0x000F0000&((data)<<16))
#define SB1_PRIORITY_1_etn_src(data)                                                 ((0x000F0000&(data))>>16)
#define SB1_PRIORITY_1_get_etn(data)                                                 ((0x000F0000&(data))>>16)
#define SB1_PRIORITY_1_etn2_shift                                                    (8)
#define SB1_PRIORITY_1_etn2_mask                                                     (0x00000F00)
#define SB1_PRIORITY_1_etn2(data)                                                    (0x00000F00&((data)<<8))
#define SB1_PRIORITY_1_etn2_src(data)                                                ((0x00000F00&(data))>>8)
#define SB1_PRIORITY_1_get_etn2(data)                                                ((0x00000F00&(data))>>8)
#define SB1_PRIORITY_1_sata_shift                                                    (0)
#define SB1_PRIORITY_1_sata_mask                                                     (0x0000000F)
#define SB1_PRIORITY_1_sata(data)                                                    (0x0000000F&((data)<<0))
#define SB1_PRIORITY_1_sata_src(data)                                                ((0x0000000F&(data))>>0)
#define SB1_PRIORITY_1_get_sata(data)                                                ((0x0000000F&(data))>>0)


#define SB1_PRIORITY_2                                                               0x1801C004
#define SB1_PRIORITY_2_reg_addr                                                      "0xB801C004"
#define SB1_PRIORITY_2_reg                                                           0xB801C004
#define set_SB1_PRIORITY_2_reg(data)   (*((volatile unsigned int*) SB1_PRIORITY_2_reg)=data)
#define get_SB1_PRIORITY_2_reg   (*((volatile unsigned int*) SB1_PRIORITY_2_reg))
#define SB1_PRIORITY_2_inst_adr                                                      "0x0001"
#define SB1_PRIORITY_2_inst                                                          0x0001
#define SB1_PRIORITY_2_nf_shift                                                      (24)
#define SB1_PRIORITY_2_nf_mask                                                       (0x0F000000)
#define SB1_PRIORITY_2_nf(data)                                                      (0x0F000000&((data)<<24))
#define SB1_PRIORITY_2_nf_src(data)                                                  ((0x0F000000&(data))>>24)
#define SB1_PRIORITY_2_get_nf(data)                                                  ((0x0F000000&(data))>>24)
#define SB1_PRIORITY_2_usb_shift                                                     (16)
#define SB1_PRIORITY_2_usb_mask                                                      (0x000F0000)
#define SB1_PRIORITY_2_usb(data)                                                     (0x000F0000&((data)<<16))
#define SB1_PRIORITY_2_usb_src(data)                                                 ((0x000F0000&(data))>>16)
#define SB1_PRIORITY_2_get_usb(data)                                                 ((0x000F0000&(data))>>16)
#define SB1_PRIORITY_2_cp_shift                                                      (8)
#define SB1_PRIORITY_2_cp_mask                                                       (0x00000F00)
#define SB1_PRIORITY_2_cp(data)                                                      (0x00000F00&((data)<<8))
#define SB1_PRIORITY_2_cp_src(data)                                                  ((0x00000F00&(data))>>8)
#define SB1_PRIORITY_2_get_cp(data)                                                  ((0x00000F00&(data))>>8)
#define SB1_PRIORITY_2_cr_shift                                                      (0)
#define SB1_PRIORITY_2_cr_mask                                                       (0x0000000F)
#define SB1_PRIORITY_2_cr(data)                                                      (0x0000000F&((data)<<0))
#define SB1_PRIORITY_2_cr_src(data)                                                  ((0x0000000F&(data))>>0)
#define SB1_PRIORITY_2_get_cr(data)                                                  ((0x0000000F&(data))>>0)


#define SB1_CHANNEL_HIGH_PRIORITY                                                    0x1801C008
#define SB1_CHANNEL_HIGH_PRIORITY_reg_addr                                           "0xB801C008"
#define SB1_CHANNEL_HIGH_PRIORITY_reg                                                0xB801C008
#define set_SB1_CHANNEL_HIGH_PRIORITY_reg(data)   (*((volatile unsigned int*) SB1_CHANNEL_HIGH_PRIORITY_reg)=data)
#define get_SB1_CHANNEL_HIGH_PRIORITY_reg   (*((volatile unsigned int*) SB1_CHANNEL_HIGH_PRIORITY_reg))
#define SB1_CHANNEL_HIGH_PRIORITY_inst_adr                                           "0x0002"
#define SB1_CHANNEL_HIGH_PRIORITY_inst                                               0x0002
#define SB1_CHANNEL_HIGH_PRIORITY_index_shift                                        (0)
#define SB1_CHANNEL_HIGH_PRIORITY_index_mask                                         (0x000000FF)
#define SB1_CHANNEL_HIGH_PRIORITY_index(data)                                        (0x000000FF&((data)<<0))
#define SB1_CHANNEL_HIGH_PRIORITY_index_src(data)                                    ((0x000000FF&(data))>>0)
#define SB1_CHANNEL_HIGH_PRIORITY_get_index(data)                                    ((0x000000FF&(data))>>0)


#define SB1_CHANNEL_REQ_MASK                                                         0x1801C00C
#define SB1_CHANNEL_REQ_MASK_reg_addr                                                "0xB801C00C"
#define SB1_CHANNEL_REQ_MASK_reg                                                     0xB801C00C
#define set_SB1_CHANNEL_REQ_MASK_reg(data)   (*((volatile unsigned int*) SB1_CHANNEL_REQ_MASK_reg)=data)
#define get_SB1_CHANNEL_REQ_MASK_reg   (*((volatile unsigned int*) SB1_CHANNEL_REQ_MASK_reg))
#define SB1_CHANNEL_REQ_MASK_inst_adr                                                "0x0003"
#define SB1_CHANNEL_REQ_MASK_inst                                                    0x0003
#define SB1_CHANNEL_REQ_MASK_index_shift                                             (0)
#define SB1_CHANNEL_REQ_MASK_index_mask                                              (0x000000FF)
#define SB1_CHANNEL_REQ_MASK_index(data)                                             (0x000000FF&((data)<<0))
#define SB1_CHANNEL_REQ_MASK_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB1_CHANNEL_REQ_MASK_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB1_CHANNEL_REQ_BUSY                                                         0x1801C010
#define SB1_CHANNEL_REQ_BUSY_reg_addr                                                "0xB801C010"
#define SB1_CHANNEL_REQ_BUSY_reg                                                     0xB801C010
#define set_SB1_CHANNEL_REQ_BUSY_reg(data)   (*((volatile unsigned int*) SB1_CHANNEL_REQ_BUSY_reg)=data)
#define get_SB1_CHANNEL_REQ_BUSY_reg   (*((volatile unsigned int*) SB1_CHANNEL_REQ_BUSY_reg))
#define SB1_CHANNEL_REQ_BUSY_inst_adr                                                "0x0004"
#define SB1_CHANNEL_REQ_BUSY_inst                                                    0x0004
#define SB1_CHANNEL_REQ_BUSY_index_shift                                             (0)
#define SB1_CHANNEL_REQ_BUSY_index_mask                                              (0x000000FF)
#define SB1_CHANNEL_REQ_BUSY_index(data)                                             (0x000000FF&((data)<<0))
#define SB1_CHANNEL_REQ_BUSY_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB1_CHANNEL_REQ_BUSY_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB1_MISC_CTRL                                                                0x1801C014
#define SB1_MISC_CTRL_reg_addr                                                       "0xB801C014"
#define SB1_MISC_CTRL_reg                                                            0xB801C014
#define set_SB1_MISC_CTRL_reg(data)   (*((volatile unsigned int*) SB1_MISC_CTRL_reg)=data)
#define get_SB1_MISC_CTRL_reg   (*((volatile unsigned int*) SB1_MISC_CTRL_reg))
#define SB1_MISC_CTRL_inst_adr                                                       "0x0005"
#define SB1_MISC_CTRL_inst                                                           0x0005
#define SB1_MISC_CTRL_allow_cmd_cnt_shift                                            (0)
#define SB1_MISC_CTRL_allow_cmd_cnt_mask                                             (0x00000007)
#define SB1_MISC_CTRL_allow_cmd_cnt(data)                                            (0x00000007&((data)<<0))
#define SB1_MISC_CTRL_allow_cmd_cnt_src(data)                                        ((0x00000007&(data))>>0)
#define SB1_MISC_CTRL_get_allow_cmd_cnt(data)                                        ((0x00000007&(data))>>0)


#define SB3_PRIORITY_1                                                               0x1801C200
#define SB3_PRIORITY_1_reg_addr                                                      "0xB801C200"
#define SB3_PRIORITY_1_reg                                                           0xB801C200
#define set_SB3_PRIORITY_1_reg(data)   (*((volatile unsigned int*) SB3_PRIORITY_1_reg)=data)
#define get_SB3_PRIORITY_1_reg   (*((volatile unsigned int*) SB3_PRIORITY_1_reg))
#define SB3_PRIORITY_1_inst_adr                                                      "0x0080"
#define SB3_PRIORITY_1_inst                                                          0x0080
#define SB3_PRIORITY_1_md_shift                                                      (24)
#define SB3_PRIORITY_1_md_mask                                                       (0x0F000000)
#define SB3_PRIORITY_1_md(data)                                                      (0x0F000000&((data)<<24))
#define SB3_PRIORITY_1_md_src(data)                                                  ((0x0F000000&(data))>>24)
#define SB3_PRIORITY_1_get_md(data)                                                  ((0x0F000000&(data))>>24)
#define SB3_PRIORITY_1_ade_shift                                                     (8)
#define SB3_PRIORITY_1_ade_mask                                                      (0x00000F00)
#define SB3_PRIORITY_1_ade(data)                                                     (0x00000F00&((data)<<8))
#define SB3_PRIORITY_1_ade_src(data)                                                 ((0x00000F00&(data))>>8)
#define SB3_PRIORITY_1_get_ade(data)                                                 ((0x00000F00&(data))>>8)
#define SB3_PRIORITY_1_aee_shift                                                     (0)
#define SB3_PRIORITY_1_aee_mask                                                      (0x0000000F)
#define SB3_PRIORITY_1_aee(data)                                                     (0x0000000F&((data)<<0))
#define SB3_PRIORITY_1_aee_src(data)                                                 ((0x0000000F&(data))>>0)
#define SB3_PRIORITY_1_get_aee(data)                                                 ((0x0000000F&(data))>>0)


#define SB3_PRIORITY_2                                                               0x1801C214
#define SB3_PRIORITY_2_reg_addr                                                      "0xB801C214"
#define SB3_PRIORITY_2_reg                                                           0xB801C214
#define set_SB3_PRIORITY_2_reg(data)   (*((volatile unsigned int*) SB3_PRIORITY_2_reg)=data)
#define get_SB3_PRIORITY_2_reg   (*((volatile unsigned int*) SB3_PRIORITY_2_reg))
#define SB3_PRIORITY_2_inst_adr                                                      "0x0085"
#define SB3_PRIORITY_2_inst                                                          0x0085
#define SB3_PRIORITY_2_me_shift                                                      (24)
#define SB3_PRIORITY_2_me_mask                                                       (0x0F000000)
#define SB3_PRIORITY_2_me(data)                                                      (0x0F000000&((data)<<24))
#define SB3_PRIORITY_2_me_src(data)                                                  ((0x0F000000&(data))>>24)
#define SB3_PRIORITY_2_get_me(data)                                                  ((0x0F000000&(data))>>24)
#define SB3_PRIORITY_2_hif_shift                                                     (16)
#define SB3_PRIORITY_2_hif_mask                                                      (0x000F0000)
#define SB3_PRIORITY_2_hif(data)                                                     (0x000F0000&((data)<<16))
#define SB3_PRIORITY_2_hif_src(data)                                                 ((0x000F0000&(data))>>16)
#define SB3_PRIORITY_2_get_hif(data)                                                 ((0x000F0000&(data))>>16)
#define SB3_PRIORITY_2_jpeg_shift                                                    (8)
#define SB3_PRIORITY_2_jpeg_mask                                                     (0x00000F00)
#define SB3_PRIORITY_2_jpeg(data)                                                    (0x00000F00&((data)<<8))
#define SB3_PRIORITY_2_jpeg_src(data)                                                ((0x00000F00&(data))>>8)
#define SB3_PRIORITY_2_get_jpeg(data)                                                ((0x00000F00&(data))>>8)
#define SB3_PRIORITY_2_ve_shift                                                      (0)
#define SB3_PRIORITY_2_ve_mask                                                       (0x0000000F)
#define SB3_PRIORITY_2_ve(data)                                                      (0x0000000F&((data)<<0))
#define SB3_PRIORITY_2_ve_src(data)                                                  ((0x0000000F&(data))>>0)
#define SB3_PRIORITY_2_get_ve(data)                                                  ((0x0000000F&(data))>>0)


#define SB3_CHANNEL_HIGH_PRIORITY                                                    0x1801C218
#define SB3_CHANNEL_HIGH_PRIORITY_reg_addr                                           "0xB801C218"
#define SB3_CHANNEL_HIGH_PRIORITY_reg                                                0xB801C218
#define set_SB3_CHANNEL_HIGH_PRIORITY_reg(data)   (*((volatile unsigned int*) SB3_CHANNEL_HIGH_PRIORITY_reg)=data)
#define get_SB3_CHANNEL_HIGH_PRIORITY_reg   (*((volatile unsigned int*) SB3_CHANNEL_HIGH_PRIORITY_reg))
#define SB3_CHANNEL_HIGH_PRIORITY_inst_adr                                           "0x0086"
#define SB3_CHANNEL_HIGH_PRIORITY_inst                                               0x0086
#define SB3_CHANNEL_HIGH_PRIORITY_index_shift                                        (0)
#define SB3_CHANNEL_HIGH_PRIORITY_index_mask                                         (0x000000FF)
#define SB3_CHANNEL_HIGH_PRIORITY_index(data)                                        (0x000000FF&((data)<<0))
#define SB3_CHANNEL_HIGH_PRIORITY_index_src(data)                                    ((0x000000FF&(data))>>0)
#define SB3_CHANNEL_HIGH_PRIORITY_get_index(data)                                    ((0x000000FF&(data))>>0)


#define SB3_CHANNEL_REQ_MASK                                                         0x1801C208
#define SB3_CHANNEL_REQ_MASK_reg_addr                                                "0xB801C208"
#define SB3_CHANNEL_REQ_MASK_reg                                                     0xB801C208
#define set_SB3_CHANNEL_REQ_MASK_reg(data)   (*((volatile unsigned int*) SB3_CHANNEL_REQ_MASK_reg)=data)
#define get_SB3_CHANNEL_REQ_MASK_reg   (*((volatile unsigned int*) SB3_CHANNEL_REQ_MASK_reg))
#define SB3_CHANNEL_REQ_MASK_inst_adr                                                "0x0082"
#define SB3_CHANNEL_REQ_MASK_inst                                                    0x0082
#define SB3_CHANNEL_REQ_MASK_index_shift                                             (0)
#define SB3_CHANNEL_REQ_MASK_index_mask                                              (0x000000FF)
#define SB3_CHANNEL_REQ_MASK_index(data)                                             (0x000000FF&((data)<<0))
#define SB3_CHANNEL_REQ_MASK_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB3_CHANNEL_REQ_MASK_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB3_CHANNEL_REQ_BUSY                                                         0x1801C20C
#define SB3_CHANNEL_REQ_BUSY_reg_addr                                                "0xB801C20C"
#define SB3_CHANNEL_REQ_BUSY_reg                                                     0xB801C20C
#define set_SB3_CHANNEL_REQ_BUSY_reg(data)   (*((volatile unsigned int*) SB3_CHANNEL_REQ_BUSY_reg)=data)
#define get_SB3_CHANNEL_REQ_BUSY_reg   (*((volatile unsigned int*) SB3_CHANNEL_REQ_BUSY_reg))
#define SB3_CHANNEL_REQ_BUSY_inst_adr                                                "0x0083"
#define SB3_CHANNEL_REQ_BUSY_inst                                                    0x0083
#define SB3_CHANNEL_REQ_BUSY_index_shift                                             (0)
#define SB3_CHANNEL_REQ_BUSY_index_mask                                              (0x000000FF)
#define SB3_CHANNEL_REQ_BUSY_index(data)                                             (0x000000FF&((data)<<0))
#define SB3_CHANNEL_REQ_BUSY_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB3_CHANNEL_REQ_BUSY_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB3_MISC_CTRL                                                                0x1801C210
#define SB3_MISC_CTRL_reg_addr                                                       "0xB801C210"
#define SB3_MISC_CTRL_reg                                                            0xB801C210
#define set_SB3_MISC_CTRL_reg(data)   (*((volatile unsigned int*) SB3_MISC_CTRL_reg)=data)
#define get_SB3_MISC_CTRL_reg   (*((volatile unsigned int*) SB3_MISC_CTRL_reg))
#define SB3_MISC_CTRL_inst_adr                                                       "0x0084"
#define SB3_MISC_CTRL_inst                                                           0x0084
#define SB3_MISC_CTRL_allow_cmd_cnt_shift                                            (0)
#define SB3_MISC_CTRL_allow_cmd_cnt_mask                                             (0x00000007)
#define SB3_MISC_CTRL_allow_cmd_cnt(data)                                            (0x00000007&((data)<<0))
#define SB3_MISC_CTRL_allow_cmd_cnt_src(data)                                        ((0x00000007&(data))>>0)
#define SB3_MISC_CTRL_get_allow_cmd_cnt(data)                                        ((0x00000007&(data))>>0)


#define SB0_PRIORITY_1                                                               0x1801C400
#define SB0_PRIORITY_1_reg_addr                                                      "0xB801C400"
#define SB0_PRIORITY_1_reg                                                           0xB801C400
#define set_SB0_PRIORITY_1_reg(data)   (*((volatile unsigned int*) SB0_PRIORITY_1_reg)=data)
#define get_SB0_PRIORITY_1_reg   (*((volatile unsigned int*) SB0_PRIORITY_1_reg))
#define SB0_PRIORITY_1_inst_adr                                                      "0x0000"
#define SB0_PRIORITY_1_inst                                                          0x0000
#define SB0_PRIORITY_1_vi_shift                                                      (8)
#define SB0_PRIORITY_1_vi_mask                                                       (0x00000F00)
#define SB0_PRIORITY_1_vi(data)                                                      (0x00000F00&((data)<<8))
#define SB0_PRIORITY_1_vi_src(data)                                                  ((0x00000F00&(data))>>8)
#define SB0_PRIORITY_1_get_vi(data)                                                  ((0x00000F00&(data))>>8)
#define SB0_PRIORITY_1_aio_shift                                                     (0)
#define SB0_PRIORITY_1_aio_mask                                                      (0x0000000F)
#define SB0_PRIORITY_1_aio(data)                                                     (0x0000000F&((data)<<0))
#define SB0_PRIORITY_1_aio_src(data)                                                 ((0x0000000F&(data))>>0)
#define SB0_PRIORITY_1_get_aio(data)                                                 ((0x0000000F&(data))>>0)


#define SB0_CHANNEL_REQ_MASK                                                         0x1801C408
#define SB0_CHANNEL_REQ_MASK_reg_addr                                                "0xB801C408"
#define SB0_CHANNEL_REQ_MASK_reg                                                     0xB801C408
#define set_SB0_CHANNEL_REQ_MASK_reg(data)   (*((volatile unsigned int*) SB0_CHANNEL_REQ_MASK_reg)=data)
#define get_SB0_CHANNEL_REQ_MASK_reg   (*((volatile unsigned int*) SB0_CHANNEL_REQ_MASK_reg))
#define SB0_CHANNEL_REQ_MASK_inst_adr                                                "0x0002"
#define SB0_CHANNEL_REQ_MASK_inst                                                    0x0002
#define SB0_CHANNEL_REQ_MASK_index_shift                                             (0)
#define SB0_CHANNEL_REQ_MASK_index_mask                                              (0x000000FF)
#define SB0_CHANNEL_REQ_MASK_index(data)                                             (0x000000FF&((data)<<0))
#define SB0_CHANNEL_REQ_MASK_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB0_CHANNEL_REQ_MASK_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB0_CHANNEL_REQ_BUSY                                                         0x1801C40C
#define SB0_CHANNEL_REQ_BUSY_reg_addr                                                "0xB801C40C"
#define SB0_CHANNEL_REQ_BUSY_reg                                                     0xB801C40C
#define set_SB0_CHANNEL_REQ_BUSY_reg(data)   (*((volatile unsigned int*) SB0_CHANNEL_REQ_BUSY_reg)=data)
#define get_SB0_CHANNEL_REQ_BUSY_reg   (*((volatile unsigned int*) SB0_CHANNEL_REQ_BUSY_reg))
#define SB0_CHANNEL_REQ_BUSY_inst_adr                                                "0x0003"
#define SB0_CHANNEL_REQ_BUSY_inst                                                    0x0003
#define SB0_CHANNEL_REQ_BUSY_index_shift                                             (0)
#define SB0_CHANNEL_REQ_BUSY_index_mask                                              (0x000000FF)
#define SB0_CHANNEL_REQ_BUSY_index(data)                                             (0x000000FF&((data)<<0))
#define SB0_CHANNEL_REQ_BUSY_index_src(data)                                         ((0x000000FF&(data))>>0)
#define SB0_CHANNEL_REQ_BUSY_get_index(data)                                         ((0x000000FF&(data))>>0)


#define SB0_MISC_CTRL                                                                0x1801C410
#define SB0_MISC_CTRL_reg_addr                                                       "0xB801C410"
#define SB0_MISC_CTRL_reg                                                            0xB801C410
#define set_SB0_MISC_CTRL_reg(data)   (*((volatile unsigned int*) SB0_MISC_CTRL_reg)=data)
#define get_SB0_MISC_CTRL_reg   (*((volatile unsigned int*) SB0_MISC_CTRL_reg))
#define SB0_MISC_CTRL_inst_adr                                                       "0x0004"
#define SB0_MISC_CTRL_inst                                                           0x0004
#define SB0_MISC_CTRL_allow_cmd_cnt_shift                                            (0)
#define SB0_MISC_CTRL_allow_cmd_cnt_mask                                             (0x00000007)
#define SB0_MISC_CTRL_allow_cmd_cnt(data)                                            (0x00000007&((data)<<0))
#define SB0_MISC_CTRL_allow_cmd_cnt_src(data)                                        ((0x00000007&(data))>>0)
#define SB0_MISC_CTRL_get_allow_cmd_cnt(data)                                        ((0x00000007&(data))>>0)


#endif
