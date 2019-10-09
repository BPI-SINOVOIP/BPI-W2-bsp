/**************************************************************
// Spec Version                  : 0.0.2
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/4/10 16:22:10
***************************************************************/


#ifndef _SB3_REG_H_INCLUDED_
#define _SB3_REG_H_INCLUDED_
#ifdef  _SB3_USE_STRUCT
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
unsigned int     vde:4;
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

#endif

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
#define SB3_PRIORITY_2_vde_shift                                                     (8)
#define SB3_PRIORITY_2_vde_mask                                                      (0x00000F00)
#define SB3_PRIORITY_2_vde(data)                                                     (0x00000F00&((data)<<8))
#define SB3_PRIORITY_2_vde_src(data)                                                 ((0x00000F00&(data))>>8)
#define SB3_PRIORITY_2_get_vde(data)                                                 ((0x00000F00&(data))>>8)
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


#endif
