/**************************************************************
// Spec Version                  : 1.0
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 16 bits
// Firmware Header Generate Date : 2012/1/9 11:6:38
***************************************************************/


#ifndef _ICAM_REG_H_INCLUDED_
#define _ICAM_REG_H_INCLUDED_
#ifdef  _ICAM_USE_STRUCT
typedef struct 
{
unsigned int     Data:32;
}ICAM_DATA;

typedef struct 
{
unsigned int     Restart:1;
unsigned int     reserved_0:17;
unsigned int     PID_Index:6;
unsigned int     Algorithm:3;
unsigned int     reserved_1:3;
unsigned int     OpCode:2;
}ICAM_COMMAND;

typedef struct 
{
unsigned int     Version:32;
}ICAM_VERSION;

typedef struct 
{
unsigned int     ID_H:32;
}ICAM_ID_H;

typedef struct 
{
unsigned int     ID_L:32;
}ICAM_ID_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Illegal_Transport_Stream_Write:1;
unsigned int     Illegal_Transport_Stream_Read:1;
unsigned int     Write_On_Busy:1;
unsigned int     Illegal_Sequence:1;
unsigned int     Illegal_Data:1;
unsigned int     Invalid_OTP:1;
unsigned int     Invalid_KTE:1;
unsigned int     UART:1;
}ICAM_INTERRUPT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Illegal_Transport_Stream_Write_Mask:1;
unsigned int     Illegal_Transport_Stream_Read_Mask:1;
unsigned int     Write_On_Busy_Mask:1;
unsigned int     Illegal_Sequence_Mask:1;
unsigned int     Illegal_Data_Mask:1;
unsigned int     Invalid_OTP_Mask:1;
unsigned int     Invalid_KTE_Mask:1;
unsigned int     reserved_1:1;
}ICAM_INTERRUPT_MASK;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     OTP_NDS_Mode:1;
unsigned int     Serialization_Fail:1;
unsigned int     Invalid_OTP:1;
unsigned int     Busy:1;
}ICAM_STATUS;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     KT_Status:20;
}ICAM_KT_STATUS_H;

typedef struct 
{
unsigned int     KT_Status:32;
}ICAM_KT_STATUS_L;

typedef struct 
{
unsigned int     iv:32;
}ICAM_AES_CBC_IV;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Data:8;
}ICAM_UART_DATA;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Control_Status:8;
}ICAM_UART_CTRL_STAT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Baud_Rate:8;
}ICAM_UART_BAUD_RATE_L;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Baud_Rate:8;
}ICAM_UART_BAUD_RATE_H;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Communication:8;
}ICAM_UART_COM;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Interrupt_Mask:8;
}ICAM_UART_INT;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Guard_Time:8;
}ICAM_UART_GUARD_TIME;

typedef struct 
{
unsigned int     SER_ID_H:32;
}ICAM_SER_ID_H;

typedef struct 
{
unsigned int     SER_ID_L:32;
}ICAM_SER_ID_L;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     OTP_NDS_Mode:1;
unsigned int     Serialization_Fail:1;
unsigned int     Invalid_OTP:1;
unsigned int     Busy:1;
}ICAM_SER_FLAG;

typedef struct 
{
unsigned int     SER_Base:32;
}ICAM_SER_BASE;

typedef struct 
{
unsigned int     SER_Result:32;
}ICAM_SER_RESULT;

#endif

#define ICAM_DATA_0                                                                  0x18020000
#define ICAM_DATA_1                                                                  0x18020004
#define ICAM_DATA_2                                                                  0x18020008
#define ICAM_DATA_3                                                                  0x1802000C
#define ICAM_DATA_0_reg_addr                                                         "0xB8020000"
#define ICAM_DATA_1_reg_addr                                                         "0xB8020004"
#define ICAM_DATA_2_reg_addr                                                         "0xB8020008"
#define ICAM_DATA_3_reg_addr                                                         "0xB802000C"
#define ICAM_DATA_0_reg                                                              0xB8020000
#define ICAM_DATA_1_reg                                                              0xB8020004
#define ICAM_DATA_2_reg                                                              0xB8020008
#define ICAM_DATA_3_reg                                                              0xB802000C
#define set_ICAM_DATA_0_reg(data)   (*((volatile unsigned int*) ICAM_DATA_0_reg)=data)
#define set_ICAM_DATA_1_reg(data)   (*((volatile unsigned int*) ICAM_DATA_1_reg)=data)
#define set_ICAM_DATA_2_reg(data)   (*((volatile unsigned int*) ICAM_DATA_2_reg)=data)
#define set_ICAM_DATA_3_reg(data)   (*((volatile unsigned int*) ICAM_DATA_3_reg)=data)
#define get_ICAM_DATA_0_reg   (*((volatile unsigned int*) ICAM_DATA_0_reg))
#define get_ICAM_DATA_1_reg   (*((volatile unsigned int*) ICAM_DATA_1_reg))
#define get_ICAM_DATA_2_reg   (*((volatile unsigned int*) ICAM_DATA_2_reg))
#define get_ICAM_DATA_3_reg   (*((volatile unsigned int*) ICAM_DATA_3_reg))
#define ICAM_DATA_0_inst_adr                                                         "0x0000"
#define ICAM_DATA_1_inst_adr                                                         "0x0001"
#define ICAM_DATA_2_inst_adr                                                         "0x0002"
#define ICAM_DATA_3_inst_adr                                                         "0x0003"
#define ICAM_DATA_0_inst                                                             0x0000
#define ICAM_DATA_1_inst                                                             0x0001
#define ICAM_DATA_2_inst                                                             0x0002
#define ICAM_DATA_3_inst                                                             0x0003
#define ICAM_DATA_Data_shift                                                         (0)
#define ICAM_DATA_Data_mask                                                          (0xFFFFFFFF)
#define ICAM_DATA_Data(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ICAM_DATA_Data_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ICAM_DATA_get_Data(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ICAM_COMMAND                                                                 0x18020010
#define ICAM_COMMAND_reg_addr                                                        "0xB8020010"
#define ICAM_COMMAND_reg                                                             0xB8020010
#define set_ICAM_COMMAND_reg(data)   (*((volatile unsigned int*) ICAM_COMMAND_reg)=data)
#define get_ICAM_COMMAND_reg   (*((volatile unsigned int*) ICAM_COMMAND_reg))
#define ICAM_COMMAND_inst_adr                                                        "0x0004"
#define ICAM_COMMAND_inst                                                            0x0004
#define ICAM_COMMAND_Restart_shift                                                   (31)
#define ICAM_COMMAND_Restart_mask                                                    (0x80000000)
#define ICAM_COMMAND_Restart(data)                                                   (0x80000000&((data)<<31))
#define ICAM_COMMAND_Restart_src(data)                                               ((0x80000000&(data))>>31)
#define ICAM_COMMAND_get_Restart(data)                                               ((0x80000000&(data))>>31)
#define ICAM_COMMAND_PID_Index_shift                                                 (8)
#define ICAM_COMMAND_PID_Index_mask                                                  (0x00003F00)
#define ICAM_COMMAND_PID_Index(data)                                                 (0x00003F00&((data)<<8))
#define ICAM_COMMAND_PID_Index_src(data)                                             ((0x00003F00&(data))>>8)
#define ICAM_COMMAND_get_PID_Index(data)                                             ((0x00003F00&(data))>>8)
#define ICAM_COMMAND_Algorithm_shift                                                 (5)
#define ICAM_COMMAND_Algorithm_mask                                                  (0x000000E0)
#define ICAM_COMMAND_Algorithm(data)                                                 (0x000000E0&((data)<<5))
#define ICAM_COMMAND_Algorithm_src(data)                                             ((0x000000E0&(data))>>5)
#define ICAM_COMMAND_get_Algorithm(data)                                             ((0x000000E0&(data))>>5)
#define ICAM_COMMAND_OpCode_shift                                                    (0)
#define ICAM_COMMAND_OpCode_mask                                                     (0x00000003)
#define ICAM_COMMAND_OpCode(data)                                                    (0x00000003&((data)<<0))
#define ICAM_COMMAND_OpCode_src(data)                                                ((0x00000003&(data))>>0)
#define ICAM_COMMAND_get_OpCode(data)                                                ((0x00000003&(data))>>0)


#define ICAM_VERSION                                                                 0x18020014
#define ICAM_VERSION_reg_addr                                                        "0xB8020014"
#define ICAM_VERSION_reg                                                             0xB8020014
#define set_ICAM_VERSION_reg(data)   (*((volatile unsigned int*) ICAM_VERSION_reg)=data)
#define get_ICAM_VERSION_reg   (*((volatile unsigned int*) ICAM_VERSION_reg))
#define ICAM_VERSION_inst_adr                                                        "0x0005"
#define ICAM_VERSION_inst                                                            0x0005
#define ICAM_VERSION_Version_shift                                                   (0)
#define ICAM_VERSION_Version_mask                                                    (0xFFFFFFFF)
#define ICAM_VERSION_Version(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ICAM_VERSION_Version_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ICAM_VERSION_get_Version(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ICAM_ID_H                                                                    0x18020018
#define ICAM_ID_H_reg_addr                                                           "0xB8020018"
#define ICAM_ID_H_reg                                                                0xB8020018
#define set_ICAM_ID_H_reg(data)   (*((volatile unsigned int*) ICAM_ID_H_reg)=data)
#define get_ICAM_ID_H_reg   (*((volatile unsigned int*) ICAM_ID_H_reg))
#define ICAM_ID_H_inst_adr                                                           "0x0006"
#define ICAM_ID_H_inst                                                               0x0006
#define ICAM_ID_H_ID_H_shift                                                         (0)
#define ICAM_ID_H_ID_H_mask                                                          (0xFFFFFFFF)
#define ICAM_ID_H_ID_H(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ICAM_ID_H_ID_H_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ICAM_ID_H_get_ID_H(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ICAM_ID_L                                                                    0x1802001C
#define ICAM_ID_L_reg_addr                                                           "0xB802001C"
#define ICAM_ID_L_reg                                                                0xB802001C
#define set_ICAM_ID_L_reg(data)   (*((volatile unsigned int*) ICAM_ID_L_reg)=data)
#define get_ICAM_ID_L_reg   (*((volatile unsigned int*) ICAM_ID_L_reg))
#define ICAM_ID_L_inst_adr                                                           "0x0007"
#define ICAM_ID_L_inst                                                               0x0007
#define ICAM_ID_L_ID_L_shift                                                         (0)
#define ICAM_ID_L_ID_L_mask                                                          (0xFFFFFFFF)
#define ICAM_ID_L_ID_L(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ICAM_ID_L_ID_L_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ICAM_ID_L_get_ID_L(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ICAM_INTERRUPT                                                               0x18020020
#define ICAM_INTERRUPT_reg_addr                                                      "0xB8020020"
#define ICAM_INTERRUPT_reg                                                           0xB8020020
#define set_ICAM_INTERRUPT_reg(data)   (*((volatile unsigned int*) ICAM_INTERRUPT_reg)=data)
#define get_ICAM_INTERRUPT_reg   (*((volatile unsigned int*) ICAM_INTERRUPT_reg))
#define ICAM_INTERRUPT_inst_adr                                                      "0x0008"
#define ICAM_INTERRUPT_inst                                                          0x0008
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Write_shift                          (7)
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Write_mask                           (0x00000080)
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Write(data)                          (0x00000080&((data)<<7))
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Write_src(data)                      ((0x00000080&(data))>>7)
#define ICAM_INTERRUPT_get_Illegal_Transport_Stream_Write(data)                      ((0x00000080&(data))>>7)
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Read_shift                           (6)
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Read_mask                            (0x00000040)
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Read(data)                           (0x00000040&((data)<<6))
#define ICAM_INTERRUPT_Illegal_Transport_Stream_Read_src(data)                       ((0x00000040&(data))>>6)
#define ICAM_INTERRUPT_get_Illegal_Transport_Stream_Read(data)                       ((0x00000040&(data))>>6)
#define ICAM_INTERRUPT_Write_On_Busy_shift                                           (5)
#define ICAM_INTERRUPT_Write_On_Busy_mask                                            (0x00000020)
#define ICAM_INTERRUPT_Write_On_Busy(data)                                           (0x00000020&((data)<<5))
#define ICAM_INTERRUPT_Write_On_Busy_src(data)                                       ((0x00000020&(data))>>5)
#define ICAM_INTERRUPT_get_Write_On_Busy(data)                                       ((0x00000020&(data))>>5)
#define ICAM_INTERRUPT_Illegal_Sequence_shift                                        (4)
#define ICAM_INTERRUPT_Illegal_Sequence_mask                                         (0x00000010)
#define ICAM_INTERRUPT_Illegal_Sequence(data)                                        (0x00000010&((data)<<4))
#define ICAM_INTERRUPT_Illegal_Sequence_src(data)                                    ((0x00000010&(data))>>4)
#define ICAM_INTERRUPT_get_Illegal_Sequence(data)                                    ((0x00000010&(data))>>4)
#define ICAM_INTERRUPT_Illegal_Data_shift                                            (3)
#define ICAM_INTERRUPT_Illegal_Data_mask                                             (0x00000008)
#define ICAM_INTERRUPT_Illegal_Data(data)                                            (0x00000008&((data)<<3))
#define ICAM_INTERRUPT_Illegal_Data_src(data)                                        ((0x00000008&(data))>>3)
#define ICAM_INTERRUPT_get_Illegal_Data(data)                                        ((0x00000008&(data))>>3)
#define ICAM_INTERRUPT_Invalid_OTP_shift                                             (2)
#define ICAM_INTERRUPT_Invalid_OTP_mask                                              (0x00000004)
#define ICAM_INTERRUPT_Invalid_OTP(data)                                             (0x00000004&((data)<<2))
#define ICAM_INTERRUPT_Invalid_OTP_src(data)                                         ((0x00000004&(data))>>2)
#define ICAM_INTERRUPT_get_Invalid_OTP(data)                                         ((0x00000004&(data))>>2)
#define ICAM_INTERRUPT_Invalid_KTE_shift                                             (1)
#define ICAM_INTERRUPT_Invalid_KTE_mask                                              (0x00000002)
#define ICAM_INTERRUPT_Invalid_KTE(data)                                             (0x00000002&((data)<<1))
#define ICAM_INTERRUPT_Invalid_KTE_src(data)                                         ((0x00000002&(data))>>1)
#define ICAM_INTERRUPT_get_Invalid_KTE(data)                                         ((0x00000002&(data))>>1)
#define ICAM_INTERRUPT_UART_shift                                                    (0)
#define ICAM_INTERRUPT_UART_mask                                                     (0x00000001)
#define ICAM_INTERRUPT_UART(data)                                                    (0x00000001&((data)<<0))
#define ICAM_INTERRUPT_UART_src(data)                                                ((0x00000001&(data))>>0)
#define ICAM_INTERRUPT_get_UART(data)                                                ((0x00000001&(data))>>0)


#define ICAM_INTERRUPT_MASK                                                          0x18020024
#define ICAM_INTERRUPT_MASK_reg_addr                                                 "0xB8020024"
#define ICAM_INTERRUPT_MASK_reg                                                      0xB8020024
#define set_ICAM_INTERRUPT_MASK_reg(data)   (*((volatile unsigned int*) ICAM_INTERRUPT_MASK_reg)=data)
#define get_ICAM_INTERRUPT_MASK_reg   (*((volatile unsigned int*) ICAM_INTERRUPT_MASK_reg))
#define ICAM_INTERRUPT_MASK_inst_adr                                                 "0x0009"
#define ICAM_INTERRUPT_MASK_inst                                                     0x0009
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Write_Mask_shift                (7)
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Write_Mask_mask                 (0x00000080)
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Write_Mask(data)                (0x00000080&((data)<<7))
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Write_Mask_src(data)            ((0x00000080&(data))>>7)
#define ICAM_INTERRUPT_MASK_get_Illegal_Transport_Stream_Write_Mask(data)            ((0x00000080&(data))>>7)
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Read_Mask_shift                 (6)
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Read_Mask_mask                  (0x00000040)
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Read_Mask(data)                 (0x00000040&((data)<<6))
#define ICAM_INTERRUPT_MASK_Illegal_Transport_Stream_Read_Mask_src(data)             ((0x00000040&(data))>>6)
#define ICAM_INTERRUPT_MASK_get_Illegal_Transport_Stream_Read_Mask(data)             ((0x00000040&(data))>>6)
#define ICAM_INTERRUPT_MASK_Write_On_Busy_Mask_shift                                 (5)
#define ICAM_INTERRUPT_MASK_Write_On_Busy_Mask_mask                                  (0x00000020)
#define ICAM_INTERRUPT_MASK_Write_On_Busy_Mask(data)                                 (0x00000020&((data)<<5))
#define ICAM_INTERRUPT_MASK_Write_On_Busy_Mask_src(data)                             ((0x00000020&(data))>>5)
#define ICAM_INTERRUPT_MASK_get_Write_On_Busy_Mask(data)                             ((0x00000020&(data))>>5)
#define ICAM_INTERRUPT_MASK_Illegal_Sequence_Mask_shift                              (4)
#define ICAM_INTERRUPT_MASK_Illegal_Sequence_Mask_mask                               (0x00000010)
#define ICAM_INTERRUPT_MASK_Illegal_Sequence_Mask(data)                              (0x00000010&((data)<<4))
#define ICAM_INTERRUPT_MASK_Illegal_Sequence_Mask_src(data)                          ((0x00000010&(data))>>4)
#define ICAM_INTERRUPT_MASK_get_Illegal_Sequence_Mask(data)                          ((0x00000010&(data))>>4)
#define ICAM_INTERRUPT_MASK_Illegal_Data_Mask_shift                                  (3)
#define ICAM_INTERRUPT_MASK_Illegal_Data_Mask_mask                                   (0x00000008)
#define ICAM_INTERRUPT_MASK_Illegal_Data_Mask(data)                                  (0x00000008&((data)<<3))
#define ICAM_INTERRUPT_MASK_Illegal_Data_Mask_src(data)                              ((0x00000008&(data))>>3)
#define ICAM_INTERRUPT_MASK_get_Illegal_Data_Mask(data)                              ((0x00000008&(data))>>3)
#define ICAM_INTERRUPT_MASK_Invalid_OTP_Mask_shift                                   (2)
#define ICAM_INTERRUPT_MASK_Invalid_OTP_Mask_mask                                    (0x00000004)
#define ICAM_INTERRUPT_MASK_Invalid_OTP_Mask(data)                                   (0x00000004&((data)<<2))
#define ICAM_INTERRUPT_MASK_Invalid_OTP_Mask_src(data)                               ((0x00000004&(data))>>2)
#define ICAM_INTERRUPT_MASK_get_Invalid_OTP_Mask(data)                               ((0x00000004&(data))>>2)
#define ICAM_INTERRUPT_MASK_Invalid_KTE_Mask_shift                                   (1)
#define ICAM_INTERRUPT_MASK_Invalid_KTE_Mask_mask                                    (0x00000002)
#define ICAM_INTERRUPT_MASK_Invalid_KTE_Mask(data)                                   (0x00000002&((data)<<1))
#define ICAM_INTERRUPT_MASK_Invalid_KTE_Mask_src(data)                               ((0x00000002&(data))>>1)
#define ICAM_INTERRUPT_MASK_get_Invalid_KTE_Mask(data)                               ((0x00000002&(data))>>1)


#define ICAM_STATUS                                                                  0x18020028
#define ICAM_STATUS_reg_addr                                                         "0xB8020028"
#define ICAM_STATUS_reg                                                              0xB8020028
#define set_ICAM_STATUS_reg(data)   (*((volatile unsigned int*) ICAM_STATUS_reg)=data)
#define get_ICAM_STATUS_reg   (*((volatile unsigned int*) ICAM_STATUS_reg))
#define ICAM_STATUS_inst_adr                                                         "0x000A"
#define ICAM_STATUS_inst                                                             0x000A
#define ICAM_STATUS_OTP_NDS_Mode_shift                                               (3)
#define ICAM_STATUS_OTP_NDS_Mode_mask                                                (0x00000008)
#define ICAM_STATUS_OTP_NDS_Mode(data)                                               (0x00000008&((data)<<3))
#define ICAM_STATUS_OTP_NDS_Mode_src(data)                                           ((0x00000008&(data))>>3)
#define ICAM_STATUS_get_OTP_NDS_Mode(data)                                           ((0x00000008&(data))>>3)
#define ICAM_STATUS_Serialization_Fail_shift                                         (2)
#define ICAM_STATUS_Serialization_Fail_mask                                          (0x00000004)
#define ICAM_STATUS_Serialization_Fail(data)                                         (0x00000004&((data)<<2))
#define ICAM_STATUS_Serialization_Fail_src(data)                                     ((0x00000004&(data))>>2)
#define ICAM_STATUS_get_Serialization_Fail(data)                                     ((0x00000004&(data))>>2)
#define ICAM_STATUS_Invalid_OTP_shift                                                (1)
#define ICAM_STATUS_Invalid_OTP_mask                                                 (0x00000002)
#define ICAM_STATUS_Invalid_OTP(data)                                                (0x00000002&((data)<<1))
#define ICAM_STATUS_Invalid_OTP_src(data)                                            ((0x00000002&(data))>>1)
#define ICAM_STATUS_get_Invalid_OTP(data)                                            ((0x00000002&(data))>>1)
#define ICAM_STATUS_Busy_shift                                                       (0)
#define ICAM_STATUS_Busy_mask                                                        (0x00000001)
#define ICAM_STATUS_Busy(data)                                                       (0x00000001&((data)<<0))
#define ICAM_STATUS_Busy_src(data)                                                   ((0x00000001&(data))>>0)
#define ICAM_STATUS_get_Busy(data)                                                   ((0x00000001&(data))>>0)


#define ICAM_KT_STATUS_H                                                             0x1802002C
#define ICAM_KT_STATUS_H_reg_addr                                                    "0xB802002C"
#define ICAM_KT_STATUS_H_reg                                                         0xB802002C
#define set_ICAM_KT_STATUS_H_reg(data)   (*((volatile unsigned int*) ICAM_KT_STATUS_H_reg)=data)
#define get_ICAM_KT_STATUS_H_reg   (*((volatile unsigned int*) ICAM_KT_STATUS_H_reg))
#define ICAM_KT_STATUS_H_inst_adr                                                    "0x000B"
#define ICAM_KT_STATUS_H_inst                                                        0x000B
#define ICAM_KT_STATUS_H_KT_Status_shift                                             (0)
#define ICAM_KT_STATUS_H_KT_Status_mask                                              (0x000FFFFF)
#define ICAM_KT_STATUS_H_KT_Status(data)                                             (0x000FFFFF&((data)<<0))
#define ICAM_KT_STATUS_H_KT_Status_src(data)                                         ((0x000FFFFF&(data))>>0)
#define ICAM_KT_STATUS_H_get_KT_Status(data)                                         ((0x000FFFFF&(data))>>0)


#define ICAM_KT_STATUS_L                                                             0x18020030
#define ICAM_KT_STATUS_L_reg_addr                                                    "0xB8020030"
#define ICAM_KT_STATUS_L_reg                                                         0xB8020030
#define set_ICAM_KT_STATUS_L_reg(data)   (*((volatile unsigned int*) ICAM_KT_STATUS_L_reg)=data)
#define get_ICAM_KT_STATUS_L_reg   (*((volatile unsigned int*) ICAM_KT_STATUS_L_reg))
#define ICAM_KT_STATUS_L_inst_adr                                                    "0x000C"
#define ICAM_KT_STATUS_L_inst                                                        0x000C
#define ICAM_KT_STATUS_L_KT_Status_shift                                             (0)
#define ICAM_KT_STATUS_L_KT_Status_mask                                              (0xFFFFFFFF)
#define ICAM_KT_STATUS_L_KT_Status(data)                                             (0xFFFFFFFF&((data)<<0))
#define ICAM_KT_STATUS_L_KT_Status_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ICAM_KT_STATUS_L_get_KT_Status(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ICAM_AES_CBC_IV_0                                                            0x18020040
#define ICAM_AES_CBC_IV_1                                                            0x18020044
#define ICAM_AES_CBC_IV_2                                                            0x18020048
#define ICAM_AES_CBC_IV_3                                                            0x1802004C
#define ICAM_AES_CBC_IV_0_reg_addr                                                   "0xB8020040"
#define ICAM_AES_CBC_IV_1_reg_addr                                                   "0xB8020044"
#define ICAM_AES_CBC_IV_2_reg_addr                                                   "0xB8020048"
#define ICAM_AES_CBC_IV_3_reg_addr                                                   "0xB802004C"
#define ICAM_AES_CBC_IV_0_reg                                                        0xB8020040
#define ICAM_AES_CBC_IV_1_reg                                                        0xB8020044
#define ICAM_AES_CBC_IV_2_reg                                                        0xB8020048
#define ICAM_AES_CBC_IV_3_reg                                                        0xB802004C
#define set_ICAM_AES_CBC_IV_0_reg(data)   (*((volatile unsigned int*) ICAM_AES_CBC_IV_0_reg)=data)
#define set_ICAM_AES_CBC_IV_1_reg(data)   (*((volatile unsigned int*) ICAM_AES_CBC_IV_1_reg)=data)
#define set_ICAM_AES_CBC_IV_2_reg(data)   (*((volatile unsigned int*) ICAM_AES_CBC_IV_2_reg)=data)
#define set_ICAM_AES_CBC_IV_3_reg(data)   (*((volatile unsigned int*) ICAM_AES_CBC_IV_3_reg)=data)
#define get_ICAM_AES_CBC_IV_0_reg   (*((volatile unsigned int*) ICAM_AES_CBC_IV_0_reg))
#define get_ICAM_AES_CBC_IV_1_reg   (*((volatile unsigned int*) ICAM_AES_CBC_IV_1_reg))
#define get_ICAM_AES_CBC_IV_2_reg   (*((volatile unsigned int*) ICAM_AES_CBC_IV_2_reg))
#define get_ICAM_AES_CBC_IV_3_reg   (*((volatile unsigned int*) ICAM_AES_CBC_IV_3_reg))
#define ICAM_AES_CBC_IV_0_inst_adr                                                   "0x0010"
#define ICAM_AES_CBC_IV_1_inst_adr                                                   "0x0011"
#define ICAM_AES_CBC_IV_2_inst_adr                                                   "0x0012"
#define ICAM_AES_CBC_IV_3_inst_adr                                                   "0x0013"
#define ICAM_AES_CBC_IV_0_inst                                                       0x0010
#define ICAM_AES_CBC_IV_1_inst                                                       0x0011
#define ICAM_AES_CBC_IV_2_inst                                                       0x0012
#define ICAM_AES_CBC_IV_3_inst                                                       0x0013
#define ICAM_AES_CBC_IV_iv_shift                                                     (0)
#define ICAM_AES_CBC_IV_iv_mask                                                      (0xFFFFFFFF)
#define ICAM_AES_CBC_IV_iv(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ICAM_AES_CBC_IV_iv_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ICAM_AES_CBC_IV_get_iv(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ICAM_UART_DATA                                                               0x18020100
#define ICAM_UART_DATA_reg_addr                                                      "0xB8020100"
#define ICAM_UART_DATA_reg                                                           0xB8020100
#define set_ICAM_UART_DATA_reg(data)   (*((volatile unsigned int*) ICAM_UART_DATA_reg)=data)
#define get_ICAM_UART_DATA_reg   (*((volatile unsigned int*) ICAM_UART_DATA_reg))
#define ICAM_UART_DATA_inst_adr                                                      "0x0040"
#define ICAM_UART_DATA_inst                                                          0x0040
#define ICAM_UART_DATA_Data_shift                                                    (0)
#define ICAM_UART_DATA_Data_mask                                                     (0x000000FF)
#define ICAM_UART_DATA_Data(data)                                                    (0x000000FF&((data)<<0))
#define ICAM_UART_DATA_Data_src(data)                                                ((0x000000FF&(data))>>0)
#define ICAM_UART_DATA_get_Data(data)                                                ((0x000000FF&(data))>>0)


#define ICAM_UART_CTRL_STAT                                                          0x18020104
#define ICAM_UART_CTRL_STAT_reg_addr                                                 "0xB8020104"
#define ICAM_UART_CTRL_STAT_reg                                                      0xB8020104
#define set_ICAM_UART_CTRL_STAT_reg(data)   (*((volatile unsigned int*) ICAM_UART_CTRL_STAT_reg)=data)
#define get_ICAM_UART_CTRL_STAT_reg   (*((volatile unsigned int*) ICAM_UART_CTRL_STAT_reg))
#define ICAM_UART_CTRL_STAT_inst_adr                                                 "0x0041"
#define ICAM_UART_CTRL_STAT_inst                                                     0x0041
#define ICAM_UART_CTRL_STAT_Control_Status_shift                                     (0)
#define ICAM_UART_CTRL_STAT_Control_Status_mask                                      (0x000000FF)
#define ICAM_UART_CTRL_STAT_Control_Status(data)                                     (0x000000FF&((data)<<0))
#define ICAM_UART_CTRL_STAT_Control_Status_src(data)                                 ((0x000000FF&(data))>>0)
#define ICAM_UART_CTRL_STAT_get_Control_Status(data)                                 ((0x000000FF&(data))>>0)


#define ICAM_UART_BAUD_RATE_L                                                        0x18020108
#define ICAM_UART_BAUD_RATE_L_reg_addr                                               "0xB8020108"
#define ICAM_UART_BAUD_RATE_L_reg                                                    0xB8020108
#define set_ICAM_UART_BAUD_RATE_L_reg(data)   (*((volatile unsigned int*) ICAM_UART_BAUD_RATE_L_reg)=data)
#define get_ICAM_UART_BAUD_RATE_L_reg   (*((volatile unsigned int*) ICAM_UART_BAUD_RATE_L_reg))
#define ICAM_UART_BAUD_RATE_L_inst_adr                                               "0x0042"
#define ICAM_UART_BAUD_RATE_L_inst                                                   0x0042
#define ICAM_UART_BAUD_RATE_L_Baud_Rate_shift                                        (0)
#define ICAM_UART_BAUD_RATE_L_Baud_Rate_mask                                         (0x000000FF)
#define ICAM_UART_BAUD_RATE_L_Baud_Rate(data)                                        (0x000000FF&((data)<<0))
#define ICAM_UART_BAUD_RATE_L_Baud_Rate_src(data)                                    ((0x000000FF&(data))>>0)
#define ICAM_UART_BAUD_RATE_L_get_Baud_Rate(data)                                    ((0x000000FF&(data))>>0)


#define ICAM_UART_BAUD_RATE_H                                                        0x1802010C
#define ICAM_UART_BAUD_RATE_H_reg_addr                                               "0xB802010C"
#define ICAM_UART_BAUD_RATE_H_reg                                                    0xB802010C
#define set_ICAM_UART_BAUD_RATE_H_reg(data)   (*((volatile unsigned int*) ICAM_UART_BAUD_RATE_H_reg)=data)
#define get_ICAM_UART_BAUD_RATE_H_reg   (*((volatile unsigned int*) ICAM_UART_BAUD_RATE_H_reg))
#define ICAM_UART_BAUD_RATE_H_inst_adr                                               "0x0043"
#define ICAM_UART_BAUD_RATE_H_inst                                                   0x0043
#define ICAM_UART_BAUD_RATE_H_Baud_Rate_shift                                        (0)
#define ICAM_UART_BAUD_RATE_H_Baud_Rate_mask                                         (0x000000FF)
#define ICAM_UART_BAUD_RATE_H_Baud_Rate(data)                                        (0x000000FF&((data)<<0))
#define ICAM_UART_BAUD_RATE_H_Baud_Rate_src(data)                                    ((0x000000FF&(data))>>0)
#define ICAM_UART_BAUD_RATE_H_get_Baud_Rate(data)                                    ((0x000000FF&(data))>>0)


#define ICAM_UART_COM                                                                0x18020110
#define ICAM_UART_COM_reg_addr                                                       "0xB8020110"
#define ICAM_UART_COM_reg                                                            0xB8020110
#define set_ICAM_UART_COM_reg(data)   (*((volatile unsigned int*) ICAM_UART_COM_reg)=data)
#define get_ICAM_UART_COM_reg   (*((volatile unsigned int*) ICAM_UART_COM_reg))
#define ICAM_UART_COM_inst_adr                                                       "0x0044"
#define ICAM_UART_COM_inst                                                           0x0044
#define ICAM_UART_COM_Communication_shift                                            (0)
#define ICAM_UART_COM_Communication_mask                                             (0x000000FF)
#define ICAM_UART_COM_Communication(data)                                            (0x000000FF&((data)<<0))
#define ICAM_UART_COM_Communication_src(data)                                        ((0x000000FF&(data))>>0)
#define ICAM_UART_COM_get_Communication(data)                                        ((0x000000FF&(data))>>0)


#define ICAM_UART_INT                                                                0x18020114
#define ICAM_UART_INT_reg_addr                                                       "0xB8020114"
#define ICAM_UART_INT_reg                                                            0xB8020114
#define set_ICAM_UART_INT_reg(data)   (*((volatile unsigned int*) ICAM_UART_INT_reg)=data)
#define get_ICAM_UART_INT_reg   (*((volatile unsigned int*) ICAM_UART_INT_reg))
#define ICAM_UART_INT_inst_adr                                                       "0x0045"
#define ICAM_UART_INT_inst                                                           0x0045
#define ICAM_UART_INT_Interrupt_Mask_shift                                           (0)
#define ICAM_UART_INT_Interrupt_Mask_mask                                            (0x000000FF)
#define ICAM_UART_INT_Interrupt_Mask(data)                                           (0x000000FF&((data)<<0))
#define ICAM_UART_INT_Interrupt_Mask_src(data)                                       ((0x000000FF&(data))>>0)
#define ICAM_UART_INT_get_Interrupt_Mask(data)                                       ((0x000000FF&(data))>>0)


#define ICAM_UART_GUARD_TIME                                                         0x18020118
#define ICAM_UART_GUARD_TIME_reg_addr                                                "0xB8020118"
#define ICAM_UART_GUARD_TIME_reg                                                     0xB8020118
#define set_ICAM_UART_GUARD_TIME_reg(data)   (*((volatile unsigned int*) ICAM_UART_GUARD_TIME_reg)=data)
#define get_ICAM_UART_GUARD_TIME_reg   (*((volatile unsigned int*) ICAM_UART_GUARD_TIME_reg))
#define ICAM_UART_GUARD_TIME_inst_adr                                                "0x0046"
#define ICAM_UART_GUARD_TIME_inst                                                    0x0046
#define ICAM_UART_GUARD_TIME_Guard_Time_shift                                        (0)
#define ICAM_UART_GUARD_TIME_Guard_Time_mask                                         (0x000000FF)
#define ICAM_UART_GUARD_TIME_Guard_Time(data)                                        (0x000000FF&((data)<<0))
#define ICAM_UART_GUARD_TIME_Guard_Time_src(data)                                    ((0x000000FF&(data))>>0)
#define ICAM_UART_GUARD_TIME_get_Guard_Time(data)                                    ((0x000000FF&(data))>>0)


#define ICAM_SER_ID_H                                                                0x18021100
#define ICAM_SER_ID_H_reg_addr                                                       "0xB8021100"
#define ICAM_SER_ID_H_reg                                                            0xB8021100
#define set_ICAM_SER_ID_H_reg(data)   (*((volatile unsigned int*) ICAM_SER_ID_H_reg)=data)
#define get_ICAM_SER_ID_H_reg   (*((volatile unsigned int*) ICAM_SER_ID_H_reg))
#define ICAM_SER_ID_H_inst_adr                                                       "0x0440"
#define ICAM_SER_ID_H_inst                                                           0x0440
#define ICAM_SER_ID_H_SER_ID_H_shift                                                 (0)
#define ICAM_SER_ID_H_SER_ID_H_mask                                                  (0xFFFFFFFF)
#define ICAM_SER_ID_H_SER_ID_H(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ICAM_SER_ID_H_SER_ID_H_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ICAM_SER_ID_H_get_SER_ID_H(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ICAM_SER_ID_L                                                                0x18021104
#define ICAM_SER_ID_L_reg_addr                                                       "0xB8021104"
#define ICAM_SER_ID_L_reg                                                            0xB8021104
#define set_ICAM_SER_ID_L_reg(data)   (*((volatile unsigned int*) ICAM_SER_ID_L_reg)=data)
#define get_ICAM_SER_ID_L_reg   (*((volatile unsigned int*) ICAM_SER_ID_L_reg))
#define ICAM_SER_ID_L_inst_adr                                                       "0x0441"
#define ICAM_SER_ID_L_inst                                                           0x0441
#define ICAM_SER_ID_L_SER_ID_L_shift                                                 (0)
#define ICAM_SER_ID_L_SER_ID_L_mask                                                  (0xFFFFFFFF)
#define ICAM_SER_ID_L_SER_ID_L(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ICAM_SER_ID_L_SER_ID_L_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ICAM_SER_ID_L_get_SER_ID_L(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ICAM_SER_FLAG                                                                0x18021108
#define ICAM_SER_FLAG_reg_addr                                                       "0xB8021108"
#define ICAM_SER_FLAG_reg                                                            0xB8021108
#define set_ICAM_SER_FLAG_reg(data)   (*((volatile unsigned int*) ICAM_SER_FLAG_reg)=data)
#define get_ICAM_SER_FLAG_reg   (*((volatile unsigned int*) ICAM_SER_FLAG_reg))
#define ICAM_SER_FLAG_inst_adr                                                       "0x0442"
#define ICAM_SER_FLAG_inst                                                           0x0442
#define ICAM_SER_FLAG_OTP_NDS_Mode_shift                                             (3)
#define ICAM_SER_FLAG_OTP_NDS_Mode_mask                                              (0x00000008)
#define ICAM_SER_FLAG_OTP_NDS_Mode(data)                                             (0x00000008&((data)<<3))
#define ICAM_SER_FLAG_OTP_NDS_Mode_src(data)                                         ((0x00000008&(data))>>3)
#define ICAM_SER_FLAG_get_OTP_NDS_Mode(data)                                         ((0x00000008&(data))>>3)
#define ICAM_SER_FLAG_Serialization_Fail_shift                                       (2)
#define ICAM_SER_FLAG_Serialization_Fail_mask                                        (0x00000004)
#define ICAM_SER_FLAG_Serialization_Fail(data)                                       (0x00000004&((data)<<2))
#define ICAM_SER_FLAG_Serialization_Fail_src(data)                                   ((0x00000004&(data))>>2)
#define ICAM_SER_FLAG_get_Serialization_Fail(data)                                   ((0x00000004&(data))>>2)
#define ICAM_SER_FLAG_Invalid_OTP_shift                                              (1)
#define ICAM_SER_FLAG_Invalid_OTP_mask                                               (0x00000002)
#define ICAM_SER_FLAG_Invalid_OTP(data)                                              (0x00000002&((data)<<1))
#define ICAM_SER_FLAG_Invalid_OTP_src(data)                                          ((0x00000002&(data))>>1)
#define ICAM_SER_FLAG_get_Invalid_OTP(data)                                          ((0x00000002&(data))>>1)
#define ICAM_SER_FLAG_Busy_shift                                                     (0)
#define ICAM_SER_FLAG_Busy_mask                                                      (0x00000001)
#define ICAM_SER_FLAG_Busy(data)                                                     (0x00000001&((data)<<0))
#define ICAM_SER_FLAG_Busy_src(data)                                                 ((0x00000001&(data))>>0)
#define ICAM_SER_FLAG_get_Busy(data)                                                 ((0x00000001&(data))>>0)


#define ICAM_SER_BASE_0                                                              0x18021280
#define ICAM_SER_BASE_1                                                              0x18021284
#define ICAM_SER_BASE_2                                                              0x18021288
#define ICAM_SER_BASE_3                                                              0x1802128C
#define ICAM_SER_BASE_4                                                              0x18021290
#define ICAM_SER_BASE_5                                                              0x18021294
#define ICAM_SER_BASE_6                                                              0x18021298
#define ICAM_SER_BASE_7                                                              0x1802129C
#define ICAM_SER_BASE_8                                                              0x180212A0
#define ICAM_SER_BASE_9                                                              0x180212A4
#define ICAM_SER_BASE_10                                                              0x180212A8
#define ICAM_SER_BASE_11                                                              0x180212AC
#define ICAM_SER_BASE_12                                                              0x180212B0
#define ICAM_SER_BASE_13                                                              0x180212B4
#define ICAM_SER_BASE_14                                                              0x180212B8
#define ICAM_SER_BASE_15                                                              0x180212BC
#define ICAM_SER_BASE_16                                                              0x180212C0
#define ICAM_SER_BASE_17                                                              0x180212C4
#define ICAM_SER_BASE_18                                                              0x180212C8
#define ICAM_SER_BASE_19                                                              0x180212CC
#define ICAM_SER_BASE_20                                                              0x180212D0
#define ICAM_SER_BASE_21                                                              0x180212D4
#define ICAM_SER_BASE_22                                                              0x180212D8
#define ICAM_SER_BASE_23                                                              0x180212DC
#define ICAM_SER_BASE_24                                                              0x180212E0
#define ICAM_SER_BASE_25                                                              0x180212E4
#define ICAM_SER_BASE_26                                                              0x180212E8
#define ICAM_SER_BASE_27                                                              0x180212EC
#define ICAM_SER_BASE_28                                                              0x180212F0
#define ICAM_SER_BASE_29                                                              0x180212F4
#define ICAM_SER_BASE_30                                                              0x180212F8
#define ICAM_SER_BASE_31                                                              0x180212FC
#define ICAM_SER_BASE_32                                                              0x18021300
#define ICAM_SER_BASE_33                                                              0x18021304
#define ICAM_SER_BASE_34                                                              0x18021308
#define ICAM_SER_BASE_35                                                              0x1802130C
#define ICAM_SER_BASE_36                                                              0x18021310
#define ICAM_SER_BASE_37                                                              0x18021314
#define ICAM_SER_BASE_38                                                              0x18021318
#define ICAM_SER_BASE_39                                                              0x1802131C
#define ICAM_SER_BASE_40                                                              0x18021320
#define ICAM_SER_BASE_41                                                              0x18021324
#define ICAM_SER_BASE_42                                                              0x18021328
#define ICAM_SER_BASE_43                                                              0x1802132C
#define ICAM_SER_BASE_44                                                              0x18021330
#define ICAM_SER_BASE_45                                                              0x18021334
#define ICAM_SER_BASE_46                                                              0x18021338
#define ICAM_SER_BASE_47                                                              0x1802133C
#define ICAM_SER_BASE_0_reg_addr                                                     "0xB8021280"
#define ICAM_SER_BASE_1_reg_addr                                                     "0xB8021284"
#define ICAM_SER_BASE_2_reg_addr                                                     "0xB8021288"
#define ICAM_SER_BASE_3_reg_addr                                                     "0xB802128C"
#define ICAM_SER_BASE_4_reg_addr                                                     "0xB8021290"
#define ICAM_SER_BASE_5_reg_addr                                                     "0xB8021294"
#define ICAM_SER_BASE_6_reg_addr                                                     "0xB8021298"
#define ICAM_SER_BASE_7_reg_addr                                                     "0xB802129C"
#define ICAM_SER_BASE_8_reg_addr                                                     "0xB80212A0"
#define ICAM_SER_BASE_9_reg_addr                                                     "0xB80212A4"
#define ICAM_SER_BASE_10_reg_addr                                                     "0xB80212A8"
#define ICAM_SER_BASE_11_reg_addr                                                     "0xB80212AC"
#define ICAM_SER_BASE_12_reg_addr                                                     "0xB80212B0"
#define ICAM_SER_BASE_13_reg_addr                                                     "0xB80212B4"
#define ICAM_SER_BASE_14_reg_addr                                                     "0xB80212B8"
#define ICAM_SER_BASE_15_reg_addr                                                     "0xB80212BC"
#define ICAM_SER_BASE_16_reg_addr                                                     "0xB80212C0"
#define ICAM_SER_BASE_17_reg_addr                                                     "0xB80212C4"
#define ICAM_SER_BASE_18_reg_addr                                                     "0xB80212C8"
#define ICAM_SER_BASE_19_reg_addr                                                     "0xB80212CC"
#define ICAM_SER_BASE_20_reg_addr                                                     "0xB80212D0"
#define ICAM_SER_BASE_21_reg_addr                                                     "0xB80212D4"
#define ICAM_SER_BASE_22_reg_addr                                                     "0xB80212D8"
#define ICAM_SER_BASE_23_reg_addr                                                     "0xB80212DC"
#define ICAM_SER_BASE_24_reg_addr                                                     "0xB80212E0"
#define ICAM_SER_BASE_25_reg_addr                                                     "0xB80212E4"
#define ICAM_SER_BASE_26_reg_addr                                                     "0xB80212E8"
#define ICAM_SER_BASE_27_reg_addr                                                     "0xB80212EC"
#define ICAM_SER_BASE_28_reg_addr                                                     "0xB80212F0"
#define ICAM_SER_BASE_29_reg_addr                                                     "0xB80212F4"
#define ICAM_SER_BASE_30_reg_addr                                                     "0xB80212F8"
#define ICAM_SER_BASE_31_reg_addr                                                     "0xB80212FC"
#define ICAM_SER_BASE_32_reg_addr                                                     "0xB8021300"
#define ICAM_SER_BASE_33_reg_addr                                                     "0xB8021304"
#define ICAM_SER_BASE_34_reg_addr                                                     "0xB8021308"
#define ICAM_SER_BASE_35_reg_addr                                                     "0xB802130C"
#define ICAM_SER_BASE_36_reg_addr                                                     "0xB8021310"
#define ICAM_SER_BASE_37_reg_addr                                                     "0xB8021314"
#define ICAM_SER_BASE_38_reg_addr                                                     "0xB8021318"
#define ICAM_SER_BASE_39_reg_addr                                                     "0xB802131C"
#define ICAM_SER_BASE_40_reg_addr                                                     "0xB8021320"
#define ICAM_SER_BASE_41_reg_addr                                                     "0xB8021324"
#define ICAM_SER_BASE_42_reg_addr                                                     "0xB8021328"
#define ICAM_SER_BASE_43_reg_addr                                                     "0xB802132C"
#define ICAM_SER_BASE_44_reg_addr                                                     "0xB8021330"
#define ICAM_SER_BASE_45_reg_addr                                                     "0xB8021334"
#define ICAM_SER_BASE_46_reg_addr                                                     "0xB8021338"
#define ICAM_SER_BASE_47_reg_addr                                                     "0xB802133C"
#define ICAM_SER_BASE_0_reg                                                          0xB8021280
#define ICAM_SER_BASE_1_reg                                                          0xB8021284
#define ICAM_SER_BASE_2_reg                                                          0xB8021288
#define ICAM_SER_BASE_3_reg                                                          0xB802128C
#define ICAM_SER_BASE_4_reg                                                          0xB8021290
#define ICAM_SER_BASE_5_reg                                                          0xB8021294
#define ICAM_SER_BASE_6_reg                                                          0xB8021298
#define ICAM_SER_BASE_7_reg                                                          0xB802129C
#define ICAM_SER_BASE_8_reg                                                          0xB80212A0
#define ICAM_SER_BASE_9_reg                                                          0xB80212A4
#define ICAM_SER_BASE_10_reg                                                          0xB80212A8
#define ICAM_SER_BASE_11_reg                                                          0xB80212AC
#define ICAM_SER_BASE_12_reg                                                          0xB80212B0
#define ICAM_SER_BASE_13_reg                                                          0xB80212B4
#define ICAM_SER_BASE_14_reg                                                          0xB80212B8
#define ICAM_SER_BASE_15_reg                                                          0xB80212BC
#define ICAM_SER_BASE_16_reg                                                          0xB80212C0
#define ICAM_SER_BASE_17_reg                                                          0xB80212C4
#define ICAM_SER_BASE_18_reg                                                          0xB80212C8
#define ICAM_SER_BASE_19_reg                                                          0xB80212CC
#define ICAM_SER_BASE_20_reg                                                          0xB80212D0
#define ICAM_SER_BASE_21_reg                                                          0xB80212D4
#define ICAM_SER_BASE_22_reg                                                          0xB80212D8
#define ICAM_SER_BASE_23_reg                                                          0xB80212DC
#define ICAM_SER_BASE_24_reg                                                          0xB80212E0
#define ICAM_SER_BASE_25_reg                                                          0xB80212E4
#define ICAM_SER_BASE_26_reg                                                          0xB80212E8
#define ICAM_SER_BASE_27_reg                                                          0xB80212EC
#define ICAM_SER_BASE_28_reg                                                          0xB80212F0
#define ICAM_SER_BASE_29_reg                                                          0xB80212F4
#define ICAM_SER_BASE_30_reg                                                          0xB80212F8
#define ICAM_SER_BASE_31_reg                                                          0xB80212FC
#define ICAM_SER_BASE_32_reg                                                          0xB8021300
#define ICAM_SER_BASE_33_reg                                                          0xB8021304
#define ICAM_SER_BASE_34_reg                                                          0xB8021308
#define ICAM_SER_BASE_35_reg                                                          0xB802130C
#define ICAM_SER_BASE_36_reg                                                          0xB8021310
#define ICAM_SER_BASE_37_reg                                                          0xB8021314
#define ICAM_SER_BASE_38_reg                                                          0xB8021318
#define ICAM_SER_BASE_39_reg                                                          0xB802131C
#define ICAM_SER_BASE_40_reg                                                          0xB8021320
#define ICAM_SER_BASE_41_reg                                                          0xB8021324
#define ICAM_SER_BASE_42_reg                                                          0xB8021328
#define ICAM_SER_BASE_43_reg                                                          0xB802132C
#define ICAM_SER_BASE_44_reg                                                          0xB8021330
#define ICAM_SER_BASE_45_reg                                                          0xB8021334
#define ICAM_SER_BASE_46_reg                                                          0xB8021338
#define ICAM_SER_BASE_47_reg                                                          0xB802133C
#define set_ICAM_SER_BASE_0_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_0_reg)=data)
#define set_ICAM_SER_BASE_1_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_1_reg)=data)
#define set_ICAM_SER_BASE_2_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_2_reg)=data)
#define set_ICAM_SER_BASE_3_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_3_reg)=data)
#define set_ICAM_SER_BASE_4_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_4_reg)=data)
#define set_ICAM_SER_BASE_5_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_5_reg)=data)
#define set_ICAM_SER_BASE_6_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_6_reg)=data)
#define set_ICAM_SER_BASE_7_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_7_reg)=data)
#define set_ICAM_SER_BASE_8_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_8_reg)=data)
#define set_ICAM_SER_BASE_9_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_9_reg)=data)
#define set_ICAM_SER_BASE_10_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_10_reg)=data)
#define set_ICAM_SER_BASE_11_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_11_reg)=data)
#define set_ICAM_SER_BASE_12_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_12_reg)=data)
#define set_ICAM_SER_BASE_13_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_13_reg)=data)
#define set_ICAM_SER_BASE_14_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_14_reg)=data)
#define set_ICAM_SER_BASE_15_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_15_reg)=data)
#define set_ICAM_SER_BASE_16_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_16_reg)=data)
#define set_ICAM_SER_BASE_17_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_17_reg)=data)
#define set_ICAM_SER_BASE_18_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_18_reg)=data)
#define set_ICAM_SER_BASE_19_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_19_reg)=data)
#define set_ICAM_SER_BASE_20_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_20_reg)=data)
#define set_ICAM_SER_BASE_21_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_21_reg)=data)
#define set_ICAM_SER_BASE_22_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_22_reg)=data)
#define set_ICAM_SER_BASE_23_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_23_reg)=data)
#define set_ICAM_SER_BASE_24_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_24_reg)=data)
#define set_ICAM_SER_BASE_25_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_25_reg)=data)
#define set_ICAM_SER_BASE_26_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_26_reg)=data)
#define set_ICAM_SER_BASE_27_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_27_reg)=data)
#define set_ICAM_SER_BASE_28_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_28_reg)=data)
#define set_ICAM_SER_BASE_29_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_29_reg)=data)
#define set_ICAM_SER_BASE_30_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_30_reg)=data)
#define set_ICAM_SER_BASE_31_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_31_reg)=data)
#define set_ICAM_SER_BASE_32_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_32_reg)=data)
#define set_ICAM_SER_BASE_33_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_33_reg)=data)
#define set_ICAM_SER_BASE_34_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_34_reg)=data)
#define set_ICAM_SER_BASE_35_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_35_reg)=data)
#define set_ICAM_SER_BASE_36_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_36_reg)=data)
#define set_ICAM_SER_BASE_37_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_37_reg)=data)
#define set_ICAM_SER_BASE_38_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_38_reg)=data)
#define set_ICAM_SER_BASE_39_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_39_reg)=data)
#define set_ICAM_SER_BASE_40_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_40_reg)=data)
#define set_ICAM_SER_BASE_41_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_41_reg)=data)
#define set_ICAM_SER_BASE_42_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_42_reg)=data)
#define set_ICAM_SER_BASE_43_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_43_reg)=data)
#define set_ICAM_SER_BASE_44_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_44_reg)=data)
#define set_ICAM_SER_BASE_45_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_45_reg)=data)
#define set_ICAM_SER_BASE_46_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_46_reg)=data)
#define set_ICAM_SER_BASE_47_reg(data)   (*((volatile unsigned int*) ICAM_SER_BASE_47_reg)=data)
#define get_ICAM_SER_BASE_0_reg   (*((volatile unsigned int*) ICAM_SER_BASE_0_reg))
#define get_ICAM_SER_BASE_1_reg   (*((volatile unsigned int*) ICAM_SER_BASE_1_reg))
#define get_ICAM_SER_BASE_2_reg   (*((volatile unsigned int*) ICAM_SER_BASE_2_reg))
#define get_ICAM_SER_BASE_3_reg   (*((volatile unsigned int*) ICAM_SER_BASE_3_reg))
#define get_ICAM_SER_BASE_4_reg   (*((volatile unsigned int*) ICAM_SER_BASE_4_reg))
#define get_ICAM_SER_BASE_5_reg   (*((volatile unsigned int*) ICAM_SER_BASE_5_reg))
#define get_ICAM_SER_BASE_6_reg   (*((volatile unsigned int*) ICAM_SER_BASE_6_reg))
#define get_ICAM_SER_BASE_7_reg   (*((volatile unsigned int*) ICAM_SER_BASE_7_reg))
#define get_ICAM_SER_BASE_8_reg   (*((volatile unsigned int*) ICAM_SER_BASE_8_reg))
#define get_ICAM_SER_BASE_9_reg   (*((volatile unsigned int*) ICAM_SER_BASE_9_reg))
#define get_ICAM_SER_BASE_10_reg   (*((volatile unsigned int*) ICAM_SER_BASE_10_reg))
#define get_ICAM_SER_BASE_11_reg   (*((volatile unsigned int*) ICAM_SER_BASE_11_reg))
#define get_ICAM_SER_BASE_12_reg   (*((volatile unsigned int*) ICAM_SER_BASE_12_reg))
#define get_ICAM_SER_BASE_13_reg   (*((volatile unsigned int*) ICAM_SER_BASE_13_reg))
#define get_ICAM_SER_BASE_14_reg   (*((volatile unsigned int*) ICAM_SER_BASE_14_reg))
#define get_ICAM_SER_BASE_15_reg   (*((volatile unsigned int*) ICAM_SER_BASE_15_reg))
#define get_ICAM_SER_BASE_16_reg   (*((volatile unsigned int*) ICAM_SER_BASE_16_reg))
#define get_ICAM_SER_BASE_17_reg   (*((volatile unsigned int*) ICAM_SER_BASE_17_reg))
#define get_ICAM_SER_BASE_18_reg   (*((volatile unsigned int*) ICAM_SER_BASE_18_reg))
#define get_ICAM_SER_BASE_19_reg   (*((volatile unsigned int*) ICAM_SER_BASE_19_reg))
#define get_ICAM_SER_BASE_20_reg   (*((volatile unsigned int*) ICAM_SER_BASE_20_reg))
#define get_ICAM_SER_BASE_21_reg   (*((volatile unsigned int*) ICAM_SER_BASE_21_reg))
#define get_ICAM_SER_BASE_22_reg   (*((volatile unsigned int*) ICAM_SER_BASE_22_reg))
#define get_ICAM_SER_BASE_23_reg   (*((volatile unsigned int*) ICAM_SER_BASE_23_reg))
#define get_ICAM_SER_BASE_24_reg   (*((volatile unsigned int*) ICAM_SER_BASE_24_reg))
#define get_ICAM_SER_BASE_25_reg   (*((volatile unsigned int*) ICAM_SER_BASE_25_reg))
#define get_ICAM_SER_BASE_26_reg   (*((volatile unsigned int*) ICAM_SER_BASE_26_reg))
#define get_ICAM_SER_BASE_27_reg   (*((volatile unsigned int*) ICAM_SER_BASE_27_reg))
#define get_ICAM_SER_BASE_28_reg   (*((volatile unsigned int*) ICAM_SER_BASE_28_reg))
#define get_ICAM_SER_BASE_29_reg   (*((volatile unsigned int*) ICAM_SER_BASE_29_reg))
#define get_ICAM_SER_BASE_30_reg   (*((volatile unsigned int*) ICAM_SER_BASE_30_reg))
#define get_ICAM_SER_BASE_31_reg   (*((volatile unsigned int*) ICAM_SER_BASE_31_reg))
#define get_ICAM_SER_BASE_32_reg   (*((volatile unsigned int*) ICAM_SER_BASE_32_reg))
#define get_ICAM_SER_BASE_33_reg   (*((volatile unsigned int*) ICAM_SER_BASE_33_reg))
#define get_ICAM_SER_BASE_34_reg   (*((volatile unsigned int*) ICAM_SER_BASE_34_reg))
#define get_ICAM_SER_BASE_35_reg   (*((volatile unsigned int*) ICAM_SER_BASE_35_reg))
#define get_ICAM_SER_BASE_36_reg   (*((volatile unsigned int*) ICAM_SER_BASE_36_reg))
#define get_ICAM_SER_BASE_37_reg   (*((volatile unsigned int*) ICAM_SER_BASE_37_reg))
#define get_ICAM_SER_BASE_38_reg   (*((volatile unsigned int*) ICAM_SER_BASE_38_reg))
#define get_ICAM_SER_BASE_39_reg   (*((volatile unsigned int*) ICAM_SER_BASE_39_reg))
#define get_ICAM_SER_BASE_40_reg   (*((volatile unsigned int*) ICAM_SER_BASE_40_reg))
#define get_ICAM_SER_BASE_41_reg   (*((volatile unsigned int*) ICAM_SER_BASE_41_reg))
#define get_ICAM_SER_BASE_42_reg   (*((volatile unsigned int*) ICAM_SER_BASE_42_reg))
#define get_ICAM_SER_BASE_43_reg   (*((volatile unsigned int*) ICAM_SER_BASE_43_reg))
#define get_ICAM_SER_BASE_44_reg   (*((volatile unsigned int*) ICAM_SER_BASE_44_reg))
#define get_ICAM_SER_BASE_45_reg   (*((volatile unsigned int*) ICAM_SER_BASE_45_reg))
#define get_ICAM_SER_BASE_46_reg   (*((volatile unsigned int*) ICAM_SER_BASE_46_reg))
#define get_ICAM_SER_BASE_47_reg   (*((volatile unsigned int*) ICAM_SER_BASE_47_reg))
#define ICAM_SER_BASE_0_inst_adr                                                     "0x04A0"
#define ICAM_SER_BASE_1_inst_adr                                                     "0x04A1"
#define ICAM_SER_BASE_2_inst_adr                                                     "0x04A2"
#define ICAM_SER_BASE_3_inst_adr                                                     "0x04A3"
#define ICAM_SER_BASE_4_inst_adr                                                     "0x04A4"
#define ICAM_SER_BASE_5_inst_adr                                                     "0x04A5"
#define ICAM_SER_BASE_6_inst_adr                                                     "0x04A6"
#define ICAM_SER_BASE_7_inst_adr                                                     "0x04A7"
#define ICAM_SER_BASE_8_inst_adr                                                     "0x04A8"
#define ICAM_SER_BASE_9_inst_adr                                                     "0x04A9"
#define ICAM_SER_BASE_10_inst_adr                                                     "0x04AA"
#define ICAM_SER_BASE_11_inst_adr                                                     "0x04AB"
#define ICAM_SER_BASE_12_inst_adr                                                     "0x04AC"
#define ICAM_SER_BASE_13_inst_adr                                                     "0x04AD"
#define ICAM_SER_BASE_14_inst_adr                                                     "0x04AE"
#define ICAM_SER_BASE_15_inst_adr                                                     "0x04AF"
#define ICAM_SER_BASE_16_inst_adr                                                     "0x04B0"
#define ICAM_SER_BASE_17_inst_adr                                                     "0x04B1"
#define ICAM_SER_BASE_18_inst_adr                                                     "0x04B2"
#define ICAM_SER_BASE_19_inst_adr                                                     "0x04B3"
#define ICAM_SER_BASE_20_inst_adr                                                     "0x04B4"
#define ICAM_SER_BASE_21_inst_adr                                                     "0x04B5"
#define ICAM_SER_BASE_22_inst_adr                                                     "0x04B6"
#define ICAM_SER_BASE_23_inst_adr                                                     "0x04B7"
#define ICAM_SER_BASE_24_inst_adr                                                     "0x04B8"
#define ICAM_SER_BASE_25_inst_adr                                                     "0x04B9"
#define ICAM_SER_BASE_26_inst_adr                                                     "0x04BA"
#define ICAM_SER_BASE_27_inst_adr                                                     "0x04BB"
#define ICAM_SER_BASE_28_inst_adr                                                     "0x04BC"
#define ICAM_SER_BASE_29_inst_adr                                                     "0x04BD"
#define ICAM_SER_BASE_30_inst_adr                                                     "0x04BE"
#define ICAM_SER_BASE_31_inst_adr                                                     "0x04BF"
#define ICAM_SER_BASE_32_inst_adr                                                     "0x04C0"
#define ICAM_SER_BASE_33_inst_adr                                                     "0x04C1"
#define ICAM_SER_BASE_34_inst_adr                                                     "0x04C2"
#define ICAM_SER_BASE_35_inst_adr                                                     "0x04C3"
#define ICAM_SER_BASE_36_inst_adr                                                     "0x04C4"
#define ICAM_SER_BASE_37_inst_adr                                                     "0x04C5"
#define ICAM_SER_BASE_38_inst_adr                                                     "0x04C6"
#define ICAM_SER_BASE_39_inst_adr                                                     "0x04C7"
#define ICAM_SER_BASE_40_inst_adr                                                     "0x04C8"
#define ICAM_SER_BASE_41_inst_adr                                                     "0x04C9"
#define ICAM_SER_BASE_42_inst_adr                                                     "0x04CA"
#define ICAM_SER_BASE_43_inst_adr                                                     "0x04CB"
#define ICAM_SER_BASE_44_inst_adr                                                     "0x04CC"
#define ICAM_SER_BASE_45_inst_adr                                                     "0x04CD"
#define ICAM_SER_BASE_46_inst_adr                                                     "0x04CE"
#define ICAM_SER_BASE_47_inst_adr                                                     "0x04CF"
#define ICAM_SER_BASE_0_inst                                                         0x04A0
#define ICAM_SER_BASE_1_inst                                                         0x04A1
#define ICAM_SER_BASE_2_inst                                                         0x04A2
#define ICAM_SER_BASE_3_inst                                                         0x04A3
#define ICAM_SER_BASE_4_inst                                                         0x04A4
#define ICAM_SER_BASE_5_inst                                                         0x04A5
#define ICAM_SER_BASE_6_inst                                                         0x04A6
#define ICAM_SER_BASE_7_inst                                                         0x04A7
#define ICAM_SER_BASE_8_inst                                                         0x04A8
#define ICAM_SER_BASE_9_inst                                                         0x04A9
#define ICAM_SER_BASE_10_inst                                                         0x04AA
#define ICAM_SER_BASE_11_inst                                                         0x04AB
#define ICAM_SER_BASE_12_inst                                                         0x04AC
#define ICAM_SER_BASE_13_inst                                                         0x04AD
#define ICAM_SER_BASE_14_inst                                                         0x04AE
#define ICAM_SER_BASE_15_inst                                                         0x04AF
#define ICAM_SER_BASE_16_inst                                                         0x04B0
#define ICAM_SER_BASE_17_inst                                                         0x04B1
#define ICAM_SER_BASE_18_inst                                                         0x04B2
#define ICAM_SER_BASE_19_inst                                                         0x04B3
#define ICAM_SER_BASE_20_inst                                                         0x04B4
#define ICAM_SER_BASE_21_inst                                                         0x04B5
#define ICAM_SER_BASE_22_inst                                                         0x04B6
#define ICAM_SER_BASE_23_inst                                                         0x04B7
#define ICAM_SER_BASE_24_inst                                                         0x04B8
#define ICAM_SER_BASE_25_inst                                                         0x04B9
#define ICAM_SER_BASE_26_inst                                                         0x04BA
#define ICAM_SER_BASE_27_inst                                                         0x04BB
#define ICAM_SER_BASE_28_inst                                                         0x04BC
#define ICAM_SER_BASE_29_inst                                                         0x04BD
#define ICAM_SER_BASE_30_inst                                                         0x04BE
#define ICAM_SER_BASE_31_inst                                                         0x04BF
#define ICAM_SER_BASE_32_inst                                                         0x04C0
#define ICAM_SER_BASE_33_inst                                                         0x04C1
#define ICAM_SER_BASE_34_inst                                                         0x04C2
#define ICAM_SER_BASE_35_inst                                                         0x04C3
#define ICAM_SER_BASE_36_inst                                                         0x04C4
#define ICAM_SER_BASE_37_inst                                                         0x04C5
#define ICAM_SER_BASE_38_inst                                                         0x04C6
#define ICAM_SER_BASE_39_inst                                                         0x04C7
#define ICAM_SER_BASE_40_inst                                                         0x04C8
#define ICAM_SER_BASE_41_inst                                                         0x04C9
#define ICAM_SER_BASE_42_inst                                                         0x04CA
#define ICAM_SER_BASE_43_inst                                                         0x04CB
#define ICAM_SER_BASE_44_inst                                                         0x04CC
#define ICAM_SER_BASE_45_inst                                                         0x04CD
#define ICAM_SER_BASE_46_inst                                                         0x04CE
#define ICAM_SER_BASE_47_inst                                                         0x04CF
#define ICAM_SER_BASE_SER_Base_shift                                                 (0)
#define ICAM_SER_BASE_SER_Base_mask                                                  (0xFFFFFFFF)
#define ICAM_SER_BASE_SER_Base(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ICAM_SER_BASE_SER_Base_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ICAM_SER_BASE_get_SER_Base(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ICAM_SER_RESULT_0                                                            0x18021340
#define ICAM_SER_RESULT_1                                                            0x18021344
#define ICAM_SER_RESULT_2                                                            0x18021348
#define ICAM_SER_RESULT_3                                                            0x1802134C
#define ICAM_SER_RESULT_4                                                            0x18021350
#define ICAM_SER_RESULT_5                                                            0x18021354
#define ICAM_SER_RESULT_6                                                            0x18021358
#define ICAM_SER_RESULT_7                                                            0x1802135C
#define ICAM_SER_RESULT_8                                                            0x18021360
#define ICAM_SER_RESULT_9                                                            0x18021364
#define ICAM_SER_RESULT_10                                                            0x18021368
#define ICAM_SER_RESULT_11                                                            0x1802136C
#define ICAM_SER_RESULT_12                                                            0x18021370
#define ICAM_SER_RESULT_13                                                            0x18021374
#define ICAM_SER_RESULT_14                                                            0x18021378
#define ICAM_SER_RESULT_15                                                            0x1802137C
#define ICAM_SER_RESULT_16                                                            0x18021380
#define ICAM_SER_RESULT_17                                                            0x18021384
#define ICAM_SER_RESULT_18                                                            0x18021388
#define ICAM_SER_RESULT_19                                                            0x1802138C
#define ICAM_SER_RESULT_20                                                            0x18021390
#define ICAM_SER_RESULT_21                                                            0x18021394
#define ICAM_SER_RESULT_22                                                            0x18021398
#define ICAM_SER_RESULT_23                                                            0x1802139C
#define ICAM_SER_RESULT_24                                                            0x180213A0
#define ICAM_SER_RESULT_25                                                            0x180213A4
#define ICAM_SER_RESULT_26                                                            0x180213A8
#define ICAM_SER_RESULT_27                                                            0x180213AC
#define ICAM_SER_RESULT_28                                                            0x180213B0
#define ICAM_SER_RESULT_29                                                            0x180213B4
#define ICAM_SER_RESULT_30                                                            0x180213B8
#define ICAM_SER_RESULT_31                                                            0x180213BC
#define ICAM_SER_RESULT_0_reg_addr                                                   "0xB8021340"
#define ICAM_SER_RESULT_1_reg_addr                                                   "0xB8021344"
#define ICAM_SER_RESULT_2_reg_addr                                                   "0xB8021348"
#define ICAM_SER_RESULT_3_reg_addr                                                   "0xB802134C"
#define ICAM_SER_RESULT_4_reg_addr                                                   "0xB8021350"
#define ICAM_SER_RESULT_5_reg_addr                                                   "0xB8021354"
#define ICAM_SER_RESULT_6_reg_addr                                                   "0xB8021358"
#define ICAM_SER_RESULT_7_reg_addr                                                   "0xB802135C"
#define ICAM_SER_RESULT_8_reg_addr                                                   "0xB8021360"
#define ICAM_SER_RESULT_9_reg_addr                                                   "0xB8021364"
#define ICAM_SER_RESULT_10_reg_addr                                                   "0xB8021368"
#define ICAM_SER_RESULT_11_reg_addr                                                   "0xB802136C"
#define ICAM_SER_RESULT_12_reg_addr                                                   "0xB8021370"
#define ICAM_SER_RESULT_13_reg_addr                                                   "0xB8021374"
#define ICAM_SER_RESULT_14_reg_addr                                                   "0xB8021378"
#define ICAM_SER_RESULT_15_reg_addr                                                   "0xB802137C"
#define ICAM_SER_RESULT_16_reg_addr                                                   "0xB8021380"
#define ICAM_SER_RESULT_17_reg_addr                                                   "0xB8021384"
#define ICAM_SER_RESULT_18_reg_addr                                                   "0xB8021388"
#define ICAM_SER_RESULT_19_reg_addr                                                   "0xB802138C"
#define ICAM_SER_RESULT_20_reg_addr                                                   "0xB8021390"
#define ICAM_SER_RESULT_21_reg_addr                                                   "0xB8021394"
#define ICAM_SER_RESULT_22_reg_addr                                                   "0xB8021398"
#define ICAM_SER_RESULT_23_reg_addr                                                   "0xB802139C"
#define ICAM_SER_RESULT_24_reg_addr                                                   "0xB80213A0"
#define ICAM_SER_RESULT_25_reg_addr                                                   "0xB80213A4"
#define ICAM_SER_RESULT_26_reg_addr                                                   "0xB80213A8"
#define ICAM_SER_RESULT_27_reg_addr                                                   "0xB80213AC"
#define ICAM_SER_RESULT_28_reg_addr                                                   "0xB80213B0"
#define ICAM_SER_RESULT_29_reg_addr                                                   "0xB80213B4"
#define ICAM_SER_RESULT_30_reg_addr                                                   "0xB80213B8"
#define ICAM_SER_RESULT_31_reg_addr                                                   "0xB80213BC"
#define ICAM_SER_RESULT_0_reg                                                        0xB8021340
#define ICAM_SER_RESULT_1_reg                                                        0xB8021344
#define ICAM_SER_RESULT_2_reg                                                        0xB8021348
#define ICAM_SER_RESULT_3_reg                                                        0xB802134C
#define ICAM_SER_RESULT_4_reg                                                        0xB8021350
#define ICAM_SER_RESULT_5_reg                                                        0xB8021354
#define ICAM_SER_RESULT_6_reg                                                        0xB8021358
#define ICAM_SER_RESULT_7_reg                                                        0xB802135C
#define ICAM_SER_RESULT_8_reg                                                        0xB8021360
#define ICAM_SER_RESULT_9_reg                                                        0xB8021364
#define ICAM_SER_RESULT_10_reg                                                        0xB8021368
#define ICAM_SER_RESULT_11_reg                                                        0xB802136C
#define ICAM_SER_RESULT_12_reg                                                        0xB8021370
#define ICAM_SER_RESULT_13_reg                                                        0xB8021374
#define ICAM_SER_RESULT_14_reg                                                        0xB8021378
#define ICAM_SER_RESULT_15_reg                                                        0xB802137C
#define ICAM_SER_RESULT_16_reg                                                        0xB8021380
#define ICAM_SER_RESULT_17_reg                                                        0xB8021384
#define ICAM_SER_RESULT_18_reg                                                        0xB8021388
#define ICAM_SER_RESULT_19_reg                                                        0xB802138C
#define ICAM_SER_RESULT_20_reg                                                        0xB8021390
#define ICAM_SER_RESULT_21_reg                                                        0xB8021394
#define ICAM_SER_RESULT_22_reg                                                        0xB8021398
#define ICAM_SER_RESULT_23_reg                                                        0xB802139C
#define ICAM_SER_RESULT_24_reg                                                        0xB80213A0
#define ICAM_SER_RESULT_25_reg                                                        0xB80213A4
#define ICAM_SER_RESULT_26_reg                                                        0xB80213A8
#define ICAM_SER_RESULT_27_reg                                                        0xB80213AC
#define ICAM_SER_RESULT_28_reg                                                        0xB80213B0
#define ICAM_SER_RESULT_29_reg                                                        0xB80213B4
#define ICAM_SER_RESULT_30_reg                                                        0xB80213B8
#define ICAM_SER_RESULT_31_reg                                                        0xB80213BC
#define set_ICAM_SER_RESULT_0_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_0_reg)=data)
#define set_ICAM_SER_RESULT_1_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_1_reg)=data)
#define set_ICAM_SER_RESULT_2_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_2_reg)=data)
#define set_ICAM_SER_RESULT_3_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_3_reg)=data)
#define set_ICAM_SER_RESULT_4_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_4_reg)=data)
#define set_ICAM_SER_RESULT_5_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_5_reg)=data)
#define set_ICAM_SER_RESULT_6_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_6_reg)=data)
#define set_ICAM_SER_RESULT_7_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_7_reg)=data)
#define set_ICAM_SER_RESULT_8_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_8_reg)=data)
#define set_ICAM_SER_RESULT_9_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_9_reg)=data)
#define set_ICAM_SER_RESULT_10_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_10_reg)=data)
#define set_ICAM_SER_RESULT_11_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_11_reg)=data)
#define set_ICAM_SER_RESULT_12_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_12_reg)=data)
#define set_ICAM_SER_RESULT_13_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_13_reg)=data)
#define set_ICAM_SER_RESULT_14_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_14_reg)=data)
#define set_ICAM_SER_RESULT_15_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_15_reg)=data)
#define set_ICAM_SER_RESULT_16_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_16_reg)=data)
#define set_ICAM_SER_RESULT_17_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_17_reg)=data)
#define set_ICAM_SER_RESULT_18_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_18_reg)=data)
#define set_ICAM_SER_RESULT_19_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_19_reg)=data)
#define set_ICAM_SER_RESULT_20_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_20_reg)=data)
#define set_ICAM_SER_RESULT_21_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_21_reg)=data)
#define set_ICAM_SER_RESULT_22_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_22_reg)=data)
#define set_ICAM_SER_RESULT_23_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_23_reg)=data)
#define set_ICAM_SER_RESULT_24_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_24_reg)=data)
#define set_ICAM_SER_RESULT_25_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_25_reg)=data)
#define set_ICAM_SER_RESULT_26_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_26_reg)=data)
#define set_ICAM_SER_RESULT_27_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_27_reg)=data)
#define set_ICAM_SER_RESULT_28_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_28_reg)=data)
#define set_ICAM_SER_RESULT_29_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_29_reg)=data)
#define set_ICAM_SER_RESULT_30_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_30_reg)=data)
#define set_ICAM_SER_RESULT_31_reg(data)   (*((volatile unsigned int*) ICAM_SER_RESULT_31_reg)=data)
#define get_ICAM_SER_RESULT_0_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_0_reg))
#define get_ICAM_SER_RESULT_1_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_1_reg))
#define get_ICAM_SER_RESULT_2_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_2_reg))
#define get_ICAM_SER_RESULT_3_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_3_reg))
#define get_ICAM_SER_RESULT_4_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_4_reg))
#define get_ICAM_SER_RESULT_5_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_5_reg))
#define get_ICAM_SER_RESULT_6_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_6_reg))
#define get_ICAM_SER_RESULT_7_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_7_reg))
#define get_ICAM_SER_RESULT_8_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_8_reg))
#define get_ICAM_SER_RESULT_9_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_9_reg))
#define get_ICAM_SER_RESULT_10_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_10_reg))
#define get_ICAM_SER_RESULT_11_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_11_reg))
#define get_ICAM_SER_RESULT_12_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_12_reg))
#define get_ICAM_SER_RESULT_13_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_13_reg))
#define get_ICAM_SER_RESULT_14_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_14_reg))
#define get_ICAM_SER_RESULT_15_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_15_reg))
#define get_ICAM_SER_RESULT_16_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_16_reg))
#define get_ICAM_SER_RESULT_17_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_17_reg))
#define get_ICAM_SER_RESULT_18_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_18_reg))
#define get_ICAM_SER_RESULT_19_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_19_reg))
#define get_ICAM_SER_RESULT_20_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_20_reg))
#define get_ICAM_SER_RESULT_21_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_21_reg))
#define get_ICAM_SER_RESULT_22_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_22_reg))
#define get_ICAM_SER_RESULT_23_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_23_reg))
#define get_ICAM_SER_RESULT_24_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_24_reg))
#define get_ICAM_SER_RESULT_25_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_25_reg))
#define get_ICAM_SER_RESULT_26_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_26_reg))
#define get_ICAM_SER_RESULT_27_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_27_reg))
#define get_ICAM_SER_RESULT_28_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_28_reg))
#define get_ICAM_SER_RESULT_29_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_29_reg))
#define get_ICAM_SER_RESULT_30_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_30_reg))
#define get_ICAM_SER_RESULT_31_reg   (*((volatile unsigned int*) ICAM_SER_RESULT_31_reg))
#define ICAM_SER_RESULT_0_inst_adr                                                   "0x04D0"
#define ICAM_SER_RESULT_1_inst_adr                                                   "0x04D1"
#define ICAM_SER_RESULT_2_inst_adr                                                   "0x04D2"
#define ICAM_SER_RESULT_3_inst_adr                                                   "0x04D3"
#define ICAM_SER_RESULT_4_inst_adr                                                   "0x04D4"
#define ICAM_SER_RESULT_5_inst_adr                                                   "0x04D5"
#define ICAM_SER_RESULT_6_inst_adr                                                   "0x04D6"
#define ICAM_SER_RESULT_7_inst_adr                                                   "0x04D7"
#define ICAM_SER_RESULT_8_inst_adr                                                   "0x04D8"
#define ICAM_SER_RESULT_9_inst_adr                                                   "0x04D9"
#define ICAM_SER_RESULT_10_inst_adr                                                   "0x04DA"
#define ICAM_SER_RESULT_11_inst_adr                                                   "0x04DB"
#define ICAM_SER_RESULT_12_inst_adr                                                   "0x04DC"
#define ICAM_SER_RESULT_13_inst_adr                                                   "0x04DD"
#define ICAM_SER_RESULT_14_inst_adr                                                   "0x04DE"
#define ICAM_SER_RESULT_15_inst_adr                                                   "0x04DF"
#define ICAM_SER_RESULT_16_inst_adr                                                   "0x04E0"
#define ICAM_SER_RESULT_17_inst_adr                                                   "0x04E1"
#define ICAM_SER_RESULT_18_inst_adr                                                   "0x04E2"
#define ICAM_SER_RESULT_19_inst_adr                                                   "0x04E3"
#define ICAM_SER_RESULT_20_inst_adr                                                   "0x04E4"
#define ICAM_SER_RESULT_21_inst_adr                                                   "0x04E5"
#define ICAM_SER_RESULT_22_inst_adr                                                   "0x04E6"
#define ICAM_SER_RESULT_23_inst_adr                                                   "0x04E7"
#define ICAM_SER_RESULT_24_inst_adr                                                   "0x04E8"
#define ICAM_SER_RESULT_25_inst_adr                                                   "0x04E9"
#define ICAM_SER_RESULT_26_inst_adr                                                   "0x04EA"
#define ICAM_SER_RESULT_27_inst_adr                                                   "0x04EB"
#define ICAM_SER_RESULT_28_inst_adr                                                   "0x04EC"
#define ICAM_SER_RESULT_29_inst_adr                                                   "0x04ED"
#define ICAM_SER_RESULT_30_inst_adr                                                   "0x04EE"
#define ICAM_SER_RESULT_31_inst_adr                                                   "0x04EF"
#define ICAM_SER_RESULT_0_inst                                                       0x04D0
#define ICAM_SER_RESULT_1_inst                                                       0x04D1
#define ICAM_SER_RESULT_2_inst                                                       0x04D2
#define ICAM_SER_RESULT_3_inst                                                       0x04D3
#define ICAM_SER_RESULT_4_inst                                                       0x04D4
#define ICAM_SER_RESULT_5_inst                                                       0x04D5
#define ICAM_SER_RESULT_6_inst                                                       0x04D6
#define ICAM_SER_RESULT_7_inst                                                       0x04D7
#define ICAM_SER_RESULT_8_inst                                                       0x04D8
#define ICAM_SER_RESULT_9_inst                                                       0x04D9
#define ICAM_SER_RESULT_10_inst                                                       0x04DA
#define ICAM_SER_RESULT_11_inst                                                       0x04DB
#define ICAM_SER_RESULT_12_inst                                                       0x04DC
#define ICAM_SER_RESULT_13_inst                                                       0x04DD
#define ICAM_SER_RESULT_14_inst                                                       0x04DE
#define ICAM_SER_RESULT_15_inst                                                       0x04DF
#define ICAM_SER_RESULT_16_inst                                                       0x04E0
#define ICAM_SER_RESULT_17_inst                                                       0x04E1
#define ICAM_SER_RESULT_18_inst                                                       0x04E2
#define ICAM_SER_RESULT_19_inst                                                       0x04E3
#define ICAM_SER_RESULT_20_inst                                                       0x04E4
#define ICAM_SER_RESULT_21_inst                                                       0x04E5
#define ICAM_SER_RESULT_22_inst                                                       0x04E6
#define ICAM_SER_RESULT_23_inst                                                       0x04E7
#define ICAM_SER_RESULT_24_inst                                                       0x04E8
#define ICAM_SER_RESULT_25_inst                                                       0x04E9
#define ICAM_SER_RESULT_26_inst                                                       0x04EA
#define ICAM_SER_RESULT_27_inst                                                       0x04EB
#define ICAM_SER_RESULT_28_inst                                                       0x04EC
#define ICAM_SER_RESULT_29_inst                                                       0x04ED
#define ICAM_SER_RESULT_30_inst                                                       0x04EE
#define ICAM_SER_RESULT_31_inst                                                       0x04EF
#define ICAM_SER_RESULT_SER_Result_shift                                             (0)
#define ICAM_SER_RESULT_SER_Result_mask                                              (0xFFFFFFFF)
#define ICAM_SER_RESULT_SER_Result(data)                                             (0xFFFFFFFF&((data)<<0))
#define ICAM_SER_RESULT_SER_Result_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ICAM_SER_RESULT_get_SER_Result(data)                                         ((0xFFFFFFFF&(data))>>0)


#endif
