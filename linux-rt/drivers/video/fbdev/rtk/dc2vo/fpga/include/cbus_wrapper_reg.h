/**************************************************************
// Spec Version                  : unknown
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/5/9 11:15:12
***************************************************************/


#ifndef _CBUS_WRAPPER_REG_H_INCLUDED_
#define _CBUS_WRAPPER_REG_H_INCLUDED_
#ifdef  _CBUS_WRAPPER_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     debug_sel:3;
unsigned int     int_scpu_en:1;
unsigned int     int_acpu_en:1;
unsigned int     reserved_1:3;
unsigned int     hdmirx_ddc_datain_detect:1;
unsigned int     hdmirx_ddc_sda_delay:4;
unsigned int     reserved_2:3;
unsigned int     cbusrx_ddc_datain_detect:1;
unsigned int     cbusrx_ddc_sda_delay:4;
}CBUS_WRAPPER_CONTROL;

#endif

#define CBUS_WRAPPER_CONTROL                                                         0x18037500
#define CBUS_WRAPPER_CONTROL_reg_addr                                                "0xB8037500"
#define CBUS_WRAPPER_CONTROL_reg                                                     0xB8037500
#define set_CBUS_WRAPPER_CONTROL_reg(data)   (*((volatile unsigned int*) CBUS_WRAPPER_CONTROL_reg)=data)
#define get_CBUS_WRAPPER_CONTROL_reg   (*((volatile unsigned int*) CBUS_WRAPPER_CONTROL_reg))
#define CBUS_WRAPPER_CONTROL_inst_adr                                                "0x0040"
#define CBUS_WRAPPER_CONTROL_inst                                                    0x0040
#define CBUS_WRAPPER_CONTROL_debug_sel_shift                                         (18)
#define CBUS_WRAPPER_CONTROL_debug_sel_mask                                          (0x001C0000)
#define CBUS_WRAPPER_CONTROL_debug_sel(data)                                         (0x001C0000&((data)<<18))
#define CBUS_WRAPPER_CONTROL_debug_sel_src(data)                                     ((0x001C0000&(data))>>18)
#define CBUS_WRAPPER_CONTROL_get_debug_sel(data)                                     ((0x001C0000&(data))>>18)
#define CBUS_WRAPPER_CONTROL_int_scpu_en_shift                                       (17)
#define CBUS_WRAPPER_CONTROL_int_scpu_en_mask                                        (0x00020000)
#define CBUS_WRAPPER_CONTROL_int_scpu_en(data)                                       (0x00020000&((data)<<17))
#define CBUS_WRAPPER_CONTROL_int_scpu_en_src(data)                                   ((0x00020000&(data))>>17)
#define CBUS_WRAPPER_CONTROL_get_int_scpu_en(data)                                   ((0x00020000&(data))>>17)
#define CBUS_WRAPPER_CONTROL_int_acpu_en_shift                                       (16)
#define CBUS_WRAPPER_CONTROL_int_acpu_en_mask                                        (0x00010000)
#define CBUS_WRAPPER_CONTROL_int_acpu_en(data)                                       (0x00010000&((data)<<16))
#define CBUS_WRAPPER_CONTROL_int_acpu_en_src(data)                                   ((0x00010000&(data))>>16)
#define CBUS_WRAPPER_CONTROL_get_int_acpu_en(data)                                   ((0x00010000&(data))>>16)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_datain_detect_shift                          (12)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_datain_detect_mask                           (0x00001000)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_datain_detect(data)                          (0x00001000&((data)<<12))
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_datain_detect_src(data)                      ((0x00001000&(data))>>12)
#define CBUS_WRAPPER_CONTROL_get_hdmirx_ddc_datain_detect(data)                      ((0x00001000&(data))>>12)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_sda_delay_shift                              (8)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_sda_delay_mask                               (0x00000F00)
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_sda_delay(data)                              (0x00000F00&((data)<<8))
#define CBUS_WRAPPER_CONTROL_hdmirx_ddc_sda_delay_src(data)                          ((0x00000F00&(data))>>8)
#define CBUS_WRAPPER_CONTROL_get_hdmirx_ddc_sda_delay(data)                          ((0x00000F00&(data))>>8)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_datain_detect_shift                          (4)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_datain_detect_mask                           (0x00000010)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_datain_detect(data)                          (0x00000010&((data)<<4))
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_datain_detect_src(data)                      ((0x00000010&(data))>>4)
#define CBUS_WRAPPER_CONTROL_get_cbusrx_ddc_datain_detect(data)                      ((0x00000010&(data))>>4)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_sda_delay_shift                              (0)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_sda_delay_mask                               (0x0000000F)
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_sda_delay(data)                              (0x0000000F&((data)<<0))
#define CBUS_WRAPPER_CONTROL_cbusrx_ddc_sda_delay_src(data)                          ((0x0000000F&(data))>>0)
#define CBUS_WRAPPER_CONTROL_get_cbusrx_ddc_sda_delay(data)                          ((0x0000000F&(data))>>0)


#endif
