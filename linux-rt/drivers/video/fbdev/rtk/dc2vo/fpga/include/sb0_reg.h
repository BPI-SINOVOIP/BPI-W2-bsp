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


#ifndef _SBX_REG_H_INCLUDED_
#define _SBX_REG_H_INCLUDED_
#ifdef  _SBX_USE_STRUCT
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
