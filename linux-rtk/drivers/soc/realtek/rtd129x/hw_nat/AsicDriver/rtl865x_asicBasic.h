/*
* Copyright c                  Realtek Semiconductor Corporation, 2009
* All rights reserved.
*
* Program : Switch table basic operation driver
* Abstract :
* Author : hyking (hyking_liu@realsil.com.cn)
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*/

#ifndef RTL865X_ASICBASIC_H
#define RTL865X_ASICBASIC_H

#define RTL8651_ASICTABLE_ENTRY_LENGTH (8 * sizeof(uint32))
#if defined(RTL865X_TEST) || defined(RTL865X_MODEL_USER) || defined(RTL865X_MODEL_KERNEL)
#define RTL8651_ASICTABLE_BASE_OF_ALL_TABLES pVirtualSWTable
#else
#if defined(CONFIG_RTD_1295_HWNAT)
#define RTL_ASIC_BASE_OF_ALL_TABLES HW_SWTBL_BASE
#define RTL_VIRT_BASE_OF_ALL_TABLES SW_SWTBL_BASE
#else //defined(CONFIG_RTD_1295_HWNAT)
#define RTL8651_ASICTABLE_BASE_OF_ALL_TABLES REAL_SWTBL_BASE
#endif //defined(CONFIG_RTD_1295_HWNAT)
#endif /* RTL865X_TEST */

#define DUMP_SWITCH	0x0001
#define HW_MCST			0x0002
#define HW_NAT			0x0004
#define HW_QOS			0x0008
#define HW_ACL			0x0010
#define ALL_NAT			0x0020

enum {
	TYPE_L2_SWITCH_TABLE = 0,
	TYPE_ARP_TABLE,
	TYPE_L3_ROUTING_TABLE,
	TYPE_MULTICAST_TABLE,
	TYPE_NETINTERFACE_TABLE,
	TYPE_EXT_INT_IP_TABLE,
	TYPE_VLAN_TABLE,
	TYPE_VLAN1_TABLE,
	TYPE_SERVER_PORT_TABLE,
	TYPE_L4_TCP_UDP_TABLE,
	TYPE_L4_ICMP_TABLE,      //10
	TYPE_PPPOE_TABLE,
	TYPE_ACL_RULE_TABLE,
	TYPE_NEXT_HOP_TABLE,
	TYPE_RATE_LIMIT_TABLE,
	TYPE_ALG_TABLE,
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	TYPE_DS_LITE_TABLE,	     //16
	TYPE_6RD_TABLE,          //17
	TYPE_L3_V6_ROUTING_TABLE,//18
	TYPE_NEXT_HOP_V6_TABLE,  //19
	TYPE_ARP_V6_TABLE,       //20
	TYPE_MULTICAST_V6_TABLE, //21
#endif
};

/*#define rtl8651_asicTableAccessAddrBase(type) (RTL8651_ASICTABLE_BASE_OF_ALL_TABLES + 0x10000 * (type)) */
#if defined(CONFIG_RTD_1295_HWNAT)
#define rtl8651_asicTableReadAddrBase(type) (RTL_VIRT_BASE_OF_ALL_TABLES + ((type)<<16) )
#else //defined(CONFIG_RTD_1295_HWNAT)
#define rtl8651_asicTableAccessAddrBase(type) (RTL8651_ASICTABLE_BASE_OF_ALL_TABLES + ((type)<<16) )
#endif //defined(CONFIG_RTD_1295_HWNAT)

#if defined(CONFIG_FPGA_V6_HWNAT)
#define rtl8651_asicTableWriteAddrBase(type) ((RTL_ASIC_BASE_OF_ALL_TABLES | 0x80000000) + ((type)<<16) )
#elif defined(CONFIG_RTD_1295_HWNAT)
#define rtl8651_asicTableWriteAddrBase(type) (RTL_ASIC_BASE_OF_ALL_TABLES + ((type)<<16) )
#endif //defined(CONFIG_FPGA_V6_HWNAT)


//extern int8 RtkHomeGatewayChipName[16];
//extern int32 RtkHomeGatewayChipNameID;
//extern int32 RtkHomeGatewayChipRevisionID;


int32 _rtl8651_addAsicEntry(uint32 tableType, uint32 eidx, void *entryContent_P);
int32 _rtl8651_forceAddAsicEntry(uint32 tableType, uint32 eidx, void *entryContent_P);
int32 _rtl8651_readAsicEntry(uint32 tableType, uint32 eidx, void *entryContent_P);
int32 _rtl8651_readAsicEntryStopTLU(uint32 tableType, uint32 eidx, void *entryContent_P);
int32 _rtl8651_delAsicEntry(uint32 tableType, uint32 startEidx, uint32 endEidx);

#endif
