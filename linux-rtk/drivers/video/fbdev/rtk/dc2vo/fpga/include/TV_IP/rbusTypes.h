/**
 * @file RBus_types.h
 * RBus systemc program.
 *
 * @author Yu-Cheng Huang
 * @email timhuang@realtek.com.tw 
 * @date Wednesday June 21 2006
 * @version 1.1
 * @ingroup model_rbus
 *
 */

#ifndef _RBUS_TYPES_H_
#define _RBUS_TYPES_H_

// Data types
typedef unsigned long long RBus_UInt64;
typedef unsigned long RBus_UInt32;
typedef unsigned short RBus_UInt16;
typedef unsigned char RBus_UInt8;
typedef unsigned long ULONG;


#define SC_MODEL

#ifndef SC_MODEL
typedef unsigned char bool;
#define true     0x01
#define false    0x00
#define BIG_ENDIAN
#define VBIPPR_PG_ENABLE
#endif

#define RBUS_DEADCODE 0xDEADC0DE
#define RBUS_MAX_MASTER_NUM 2
#define RBUS_CO_SIM_FILE "rbus2rtl_reg.log"

enum VIDEO_MODE {
  VIDEO_NTSC = 0,
  VIDEO_PAL,
};

enum VTE_MODE {
  VTE_MODE_MICRONAS = 0,
  VTE_MODE_PHILIPS = 1,
};

#define BIG_ENDIA_SWAP(src,des) {des = ((src&0xFF)<<24) | ((src&0xFF00)<<8) | ((src&0xFF0000)>>8) | ((src&0xFF000000)>>24);};

#endif
