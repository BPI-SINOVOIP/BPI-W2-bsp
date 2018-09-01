/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/4/11 19:55:7
***************************************************************/


#ifndef _SFDF_REG_H_INCLUDED_
#define _SFDF_REG_H_INCLUDED_
#ifdef  _SFDF_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     int_status:1;
}INTTERRUPT_STATUS;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     gamma_tab_index:10;
unsigned int     reserved_1:3;
unsigned int     gamma_tab_d0:5;
unsigned int     reserved_2:3;
unsigned int     gamma_tab_d1:5;
}GAMMA_PORT;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     d_stat_enable:1;
}DSTAT_CTRL_R;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     crc_start:1;
}CRC_CTRL_1;

#endif

#define INTTERRUPT_STATUS                                                            0x18009830
#define INTTERRUPT_STATUS_reg_addr                                                   "0xB8009830"
#define INTTERRUPT_STATUS_reg                                                        0xB8009830
#define set_INTTERRUPT_STATUS_reg(data)   (*((volatile unsigned int*) INTTERRUPT_STATUS_reg)=data)
#define get_INTTERRUPT_STATUS_reg   (*((volatile unsigned int*) INTTERRUPT_STATUS_reg))
#define INTTERRUPT_STATUS_inst_adr                                                   "0x000C"
#define INTTERRUPT_STATUS_inst                                                       0x000C
#define INTTERRUPT_STATUS_int_status_shift                                           (0)
#define INTTERRUPT_STATUS_int_status_mask                                            (0x00000001)
#define INTTERRUPT_STATUS_int_status(data)                                           (0x00000001&((data)<<0))
#define INTTERRUPT_STATUS_int_status_src(data)                                       ((0x00000001&(data))>>0)
#define INTTERRUPT_STATUS_get_int_status(data)                                       ((0x00000001&(data))>>0)


#define GAMMA_PORT                                                                   0x18009860
#define GAMMA_PORT_reg_addr                                                          "0xB8009860"
#define GAMMA_PORT_reg                                                               0xB8009860
#define set_GAMMA_PORT_reg(data)   (*((volatile unsigned int*) GAMMA_PORT_reg)=data)
#define get_GAMMA_PORT_reg   (*((volatile unsigned int*) GAMMA_PORT_reg))
#define GAMMA_PORT_inst_adr                                                          "0x0018"
#define GAMMA_PORT_inst                                                              0x0018
#define GAMMA_PORT_gamma_tab_index_shift                                             (16)
#define GAMMA_PORT_gamma_tab_index_mask                                              (0x03FF0000)
#define GAMMA_PORT_gamma_tab_index(data)                                             (0x03FF0000&((data)<<16))
#define GAMMA_PORT_gamma_tab_index_src(data)                                         ((0x03FF0000&(data))>>16)
#define GAMMA_PORT_get_gamma_tab_index(data)                                         ((0x03FF0000&(data))>>16)
#define GAMMA_PORT_gamma_tab_d0_shift                                                (8)
#define GAMMA_PORT_gamma_tab_d0_mask                                                 (0x00001F00)
#define GAMMA_PORT_gamma_tab_d0(data)                                                (0x00001F00&((data)<<8))
#define GAMMA_PORT_gamma_tab_d0_src(data)                                            ((0x00001F00&(data))>>8)
#define GAMMA_PORT_get_gamma_tab_d0(data)                                            ((0x00001F00&(data))>>8)
#define GAMMA_PORT_gamma_tab_d1_shift                                                (0)
#define GAMMA_PORT_gamma_tab_d1_mask                                                 (0x0000001F)
#define GAMMA_PORT_gamma_tab_d1(data)                                                (0x0000001F&((data)<<0))
#define GAMMA_PORT_gamma_tab_d1_src(data)                                            ((0x0000001F&(data))>>0)
#define GAMMA_PORT_get_gamma_tab_d1(data)                                            ((0x0000001F&(data))>>0)


#define DSTAT_CTRL_R                                                                 0x1800987c
#define DSTAT_CTRL_R_reg_addr                                                        "0xB800987C"
#define DSTAT_CTRL_R_reg                                                             0xB800987C
#define set_DSTAT_CTRL_R_reg(data)   (*((volatile unsigned int*) DSTAT_CTRL_R_reg)=data)
#define get_DSTAT_CTRL_R_reg   (*((volatile unsigned int*) DSTAT_CTRL_R_reg))
#define DSTAT_CTRL_R_inst_adr                                                        "0x001F"
#define DSTAT_CTRL_R_inst                                                            0x001F
#define DSTAT_CTRL_R_d_stat_enable_shift                                             (0)
#define DSTAT_CTRL_R_d_stat_enable_mask                                              (0x00000001)
#define DSTAT_CTRL_R_d_stat_enable(data)                                             (0x00000001&((data)<<0))
#define DSTAT_CTRL_R_d_stat_enable_src(data)                                         ((0x00000001&(data))>>0)
#define DSTAT_CTRL_R_get_d_stat_enable(data)                                         ((0x00000001&(data))>>0)


#define CRC_CTRL_1                                                                   0x180099e0
#define CRC_CTRL_1_reg_addr                                                          "0xB80099E0"
#define CRC_CTRL_1_reg                                                               0xB80099E0
#define set_CRC_CTRL_1_reg(data)   (*((volatile unsigned int*) CRC_CTRL_1_reg)=data)
#define get_CRC_CTRL_1_reg   (*((volatile unsigned int*) CRC_CTRL_1_reg))
#define CRC_CTRL_1_inst_adr                                                          "0x0078"
#define CRC_CTRL_1_inst                                                              0x0078
#define CRC_CTRL_1_crc_start_shift                                                   (0)
#define CRC_CTRL_1_crc_start_mask                                                    (0x00000001)
#define CRC_CTRL_1_crc_start(data)                                                   (0x00000001&((data)<<0))
#define CRC_CTRL_1_crc_start_src(data)                                               ((0x00000001&(data))>>0)
#define CRC_CTRL_1_get_crc_start(data)                                               ((0x00000001&(data))>>0)


#endif
