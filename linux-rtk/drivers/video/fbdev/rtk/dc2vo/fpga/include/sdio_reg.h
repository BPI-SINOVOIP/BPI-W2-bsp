/**************************************************************
// Spec Version                  : 0.7
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/23 16:58:21
***************************************************************/


#ifndef _SDIO_REG_H_INCLUDED_
#define _SDIO_REG_H_INCLUDED_
#ifdef  _SDIO_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     mcu_buf_access:2;
unsigned int     mcu_sel:1;
}SDIO_SRAM_CTL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     suspend_n:1;
}SDIO_IP_CTL;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_enable3:1;
unsigned int     sel1:3;
unsigned int     write_enable2:1;
unsigned int     sel0:3;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}SDIO_DBG_1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     dbus_dbg_sel:3;
}SDIO_DBG_2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     ip_dbg_sel:8;
}SDIO_DBG_3;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     Int4:1;
unsigned int     Int3:1;
unsigned int     Int2:1;
unsigned int     Int1:1;
unsigned int     write_data:1;
}SDIO_ISR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     Int1En:1;
unsigned int     write_data:1;
}SDIO_ISREN;

#endif

#define SDIO_SRAM_CTL                                                                0x18010A00
#define SDIO_SRAM_CTL_reg_addr                                                       "0xB8010A00"
#define SDIO_SRAM_CTL_reg                                                            0xB8010A00
#define set_SDIO_SRAM_CTL_reg(data)   (*((volatile unsigned int*) SDIO_SRAM_CTL_reg)=data)
#define get_SDIO_SRAM_CTL_reg   (*((volatile unsigned int*) SDIO_SRAM_CTL_reg))
#define SDIO_SRAM_CTL_inst_adr                                                       "0x0080"
#define SDIO_SRAM_CTL_inst                                                           0x0080
#define SDIO_SRAM_CTL_mcu_buf_access_shift                                           (1)
#define SDIO_SRAM_CTL_mcu_buf_access_mask                                            (0x00000006)
#define SDIO_SRAM_CTL_mcu_buf_access(data)                                           (0x00000006&((data)<<1))
#define SDIO_SRAM_CTL_mcu_buf_access_src(data)                                       ((0x00000006&(data))>>1)
#define SDIO_SRAM_CTL_get_mcu_buf_access(data)                                       ((0x00000006&(data))>>1)
#define SDIO_SRAM_CTL_mcu_sel_shift                                                  (0)
#define SDIO_SRAM_CTL_mcu_sel_mask                                                   (0x00000001)
#define SDIO_SRAM_CTL_mcu_sel(data)                                                  (0x00000001&((data)<<0))
#define SDIO_SRAM_CTL_mcu_sel_src(data)                                              ((0x00000001&(data))>>0)
#define SDIO_SRAM_CTL_get_mcu_sel(data)                                              ((0x00000001&(data))>>0)


#define SDIO_IP_CTL                                                                  0x18010A10
#define SDIO_IP_CTL_reg_addr                                                         "0xB8010A10"
#define SDIO_IP_CTL_reg                                                              0xB8010A10
#define set_SDIO_IP_CTL_reg(data)   (*((volatile unsigned int*) SDIO_IP_CTL_reg)=data)
#define get_SDIO_IP_CTL_reg   (*((volatile unsigned int*) SDIO_IP_CTL_reg))
#define SDIO_IP_CTL_inst_adr                                                         "0x0084"
#define SDIO_IP_CTL_inst                                                             0x0084
#define SDIO_IP_CTL_suspend_n_shift                                                  (0)
#define SDIO_IP_CTL_suspend_n_mask                                                   (0x00000001)
#define SDIO_IP_CTL_suspend_n(data)                                                  (0x00000001&((data)<<0))
#define SDIO_IP_CTL_suspend_n_src(data)                                              ((0x00000001&(data))>>0)
#define SDIO_IP_CTL_get_suspend_n(data)                                              ((0x00000001&(data))>>0)


#define SDIO_DBG_1                                                                   0x18010A20
#define SDIO_DBG_1_reg_addr                                                          "0xB8010A20"
#define SDIO_DBG_1_reg                                                               0xB8010A20
#define set_SDIO_DBG_1_reg(data)   (*((volatile unsigned int*) SDIO_DBG_1_reg)=data)
#define get_SDIO_DBG_1_reg   (*((volatile unsigned int*) SDIO_DBG_1_reg))
#define SDIO_DBG_1_inst_adr                                                          "0x0088"
#define SDIO_DBG_1_inst                                                              0x0088
#define SDIO_DBG_1_write_enable3_shift                                               (9)
#define SDIO_DBG_1_write_enable3_mask                                                (0x00000200)
#define SDIO_DBG_1_write_enable3(data)                                               (0x00000200&((data)<<9))
#define SDIO_DBG_1_write_enable3_src(data)                                           ((0x00000200&(data))>>9)
#define SDIO_DBG_1_get_write_enable3(data)                                           ((0x00000200&(data))>>9)
#define SDIO_DBG_1_sel1_shift                                                        (6)
#define SDIO_DBG_1_sel1_mask                                                         (0x000001C0)
#define SDIO_DBG_1_sel1(data)                                                        (0x000001C0&((data)<<6))
#define SDIO_DBG_1_sel1_src(data)                                                    ((0x000001C0&(data))>>6)
#define SDIO_DBG_1_get_sel1(data)                                                    ((0x000001C0&(data))>>6)
#define SDIO_DBG_1_write_enable2_shift                                               (5)
#define SDIO_DBG_1_write_enable2_mask                                                (0x00000020)
#define SDIO_DBG_1_write_enable2(data)                                               (0x00000020&((data)<<5))
#define SDIO_DBG_1_write_enable2_src(data)                                           ((0x00000020&(data))>>5)
#define SDIO_DBG_1_get_write_enable2(data)                                           ((0x00000020&(data))>>5)
#define SDIO_DBG_1_sel0_shift                                                        (2)
#define SDIO_DBG_1_sel0_mask                                                         (0x0000001C)
#define SDIO_DBG_1_sel0(data)                                                        (0x0000001C&((data)<<2))
#define SDIO_DBG_1_sel0_src(data)                                                    ((0x0000001C&(data))>>2)
#define SDIO_DBG_1_get_sel0(data)                                                    ((0x0000001C&(data))>>2)
#define SDIO_DBG_1_write_enable1_shift                                               (1)
#define SDIO_DBG_1_write_enable1_mask                                                (0x00000002)
#define SDIO_DBG_1_write_enable1(data)                                               (0x00000002&((data)<<1))
#define SDIO_DBG_1_write_enable1_src(data)                                           ((0x00000002&(data))>>1)
#define SDIO_DBG_1_get_write_enable1(data)                                           ((0x00000002&(data))>>1)
#define SDIO_DBG_1_enable_shift                                                      (0)
#define SDIO_DBG_1_enable_mask                                                       (0x00000001)
#define SDIO_DBG_1_enable(data)                                                      (0x00000001&((data)<<0))
#define SDIO_DBG_1_enable_src(data)                                                  ((0x00000001&(data))>>0)
#define SDIO_DBG_1_get_enable(data)                                                  ((0x00000001&(data))>>0)


#define SDIO_DBG_2                                                                   0x18010A24
#define SDIO_DBG_2_reg_addr                                                          "0xB8010A24"
#define SDIO_DBG_2_reg                                                               0xB8010A24
#define set_SDIO_DBG_2_reg(data)   (*((volatile unsigned int*) SDIO_DBG_2_reg)=data)
#define get_SDIO_DBG_2_reg   (*((volatile unsigned int*) SDIO_DBG_2_reg))
#define SDIO_DBG_2_inst_adr                                                          "0x0089"
#define SDIO_DBG_2_inst                                                              0x0089
#define SDIO_DBG_2_dbus_dbg_sel_shift                                                (0)
#define SDIO_DBG_2_dbus_dbg_sel_mask                                                 (0x00000007)
#define SDIO_DBG_2_dbus_dbg_sel(data)                                                (0x00000007&((data)<<0))
#define SDIO_DBG_2_dbus_dbg_sel_src(data)                                            ((0x00000007&(data))>>0)
#define SDIO_DBG_2_get_dbus_dbg_sel(data)                                            ((0x00000007&(data))>>0)


#define SDIO_DBG_3                                                                   0x18010A28
#define SDIO_DBG_3_reg_addr                                                          "0xB8010A28"
#define SDIO_DBG_3_reg                                                               0xB8010A28
#define set_SDIO_DBG_3_reg(data)   (*((volatile unsigned int*) SDIO_DBG_3_reg)=data)
#define get_SDIO_DBG_3_reg   (*((volatile unsigned int*) SDIO_DBG_3_reg))
#define SDIO_DBG_3_inst_adr                                                          "0x008A"
#define SDIO_DBG_3_inst                                                              0x008A
#define SDIO_DBG_3_ip_dbg_sel_shift                                                  (0)
#define SDIO_DBG_3_ip_dbg_sel_mask                                                   (0x000000FF)
#define SDIO_DBG_3_ip_dbg_sel(data)                                                  (0x000000FF&((data)<<0))
#define SDIO_DBG_3_ip_dbg_sel_src(data)                                              ((0x000000FF&(data))>>0)
#define SDIO_DBG_3_get_ip_dbg_sel(data)                                              ((0x000000FF&(data))>>0)


#define SDIO_ISR                                                                     0x18010A30
#define SDIO_ISR_reg_addr                                                            "0xB8010A30"
#define SDIO_ISR_reg                                                                 0xB8010A30
#define set_SDIO_ISR_reg(data)   (*((volatile unsigned int*) SDIO_ISR_reg)=data)
#define get_SDIO_ISR_reg   (*((volatile unsigned int*) SDIO_ISR_reg))
#define SDIO_ISR_inst_adr                                                            "0x008C"
#define SDIO_ISR_inst                                                                0x008C
#define SDIO_ISR_Int4_shift                                                          (4)
#define SDIO_ISR_Int4_mask                                                           (0x00000010)
#define SDIO_ISR_Int4(data)                                                          (0x00000010&((data)<<4))
#define SDIO_ISR_Int4_src(data)                                                      ((0x00000010&(data))>>4)
#define SDIO_ISR_get_Int4(data)                                                      ((0x00000010&(data))>>4)
#define SDIO_ISR_Int3_shift                                                          (3)
#define SDIO_ISR_Int3_mask                                                           (0x00000008)
#define SDIO_ISR_Int3(data)                                                          (0x00000008&((data)<<3))
#define SDIO_ISR_Int3_src(data)                                                      ((0x00000008&(data))>>3)
#define SDIO_ISR_get_Int3(data)                                                      ((0x00000008&(data))>>3)
#define SDIO_ISR_Int2_shift                                                          (2)
#define SDIO_ISR_Int2_mask                                                           (0x00000004)
#define SDIO_ISR_Int2(data)                                                          (0x00000004&((data)<<2))
#define SDIO_ISR_Int2_src(data)                                                      ((0x00000004&(data))>>2)
#define SDIO_ISR_get_Int2(data)                                                      ((0x00000004&(data))>>2)
#define SDIO_ISR_Int1_shift                                                          (1)
#define SDIO_ISR_Int1_mask                                                           (0x00000002)
#define SDIO_ISR_Int1(data)                                                          (0x00000002&((data)<<1))
#define SDIO_ISR_Int1_src(data)                                                      ((0x00000002&(data))>>1)
#define SDIO_ISR_get_Int1(data)                                                      ((0x00000002&(data))>>1)
#define SDIO_ISR_write_data_shift                                                    (0)
#define SDIO_ISR_write_data_mask                                                     (0x00000001)
#define SDIO_ISR_write_data(data)                                                    (0x00000001&((data)<<0))
#define SDIO_ISR_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define SDIO_ISR_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define SDIO_ISREN                                                                   0x18010A34
#define SDIO_ISREN_reg_addr                                                          "0xB8010A34"
#define SDIO_ISREN_reg                                                               0xB8010A34
#define set_SDIO_ISREN_reg(data)   (*((volatile unsigned int*) SDIO_ISREN_reg)=data)
#define get_SDIO_ISREN_reg   (*((volatile unsigned int*) SDIO_ISREN_reg))
#define SDIO_ISREN_inst_adr                                                          "0x008D"
#define SDIO_ISREN_inst                                                              0x008D
#define SDIO_ISREN_Int1En_shift                                                      (1)
#define SDIO_ISREN_Int1En_mask                                                       (0x00000002)
#define SDIO_ISREN_Int1En(data)                                                      (0x00000002&((data)<<1))
#define SDIO_ISREN_Int1En_src(data)                                                  ((0x00000002&(data))>>1)
#define SDIO_ISREN_get_Int1En(data)                                                  ((0x00000002&(data))>>1)
#define SDIO_ISREN_write_data_shift                                                  (0)
#define SDIO_ISREN_write_data_mask                                                   (0x00000001)
#define SDIO_ISREN_write_data(data)                                                  (0x00000001&((data)<<0))
#define SDIO_ISREN_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define SDIO_ISREN_get_write_data(data)                                              ((0x00000001&(data))>>0)


#endif
