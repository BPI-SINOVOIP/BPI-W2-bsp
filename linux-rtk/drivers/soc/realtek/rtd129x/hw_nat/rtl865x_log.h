/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef	RTL865X_LOG_H
#define	RTL865X_LOG_H

#if defined(CONFIG_RTL_LOG_DEBUG)

	#if defined(LOG_ERROR)
	#undef LOG_ERROR
	#define LOG_ERROR(fmt, args...) do{ \
		if(RTL_LogTypeMask.ERROR&&RTL_LogModuleMask.NIC&&LOG_LIMIT)scrlog_printk("NIC-ERROR:"fmt, ## args); \
			}while(0)
	#endif

	#if defined(LOG_MEM_ERROR)
	#undef LOG_MEM_ERROR
	#define LOG_MEM_ERROR(fmt, args...) do{ \
		if(RTL_LogTypeMask.ERROR&&RTL_LogErrorMask.MEM&&RTL_LogModuleMask.NIC&&LOG_LIMIT)scrlog_printk("NIC-MEM-ERROR:"fmt, ## args); \
			}while(0)
	#endif

	#if defined(LOG_SKB_ERROR)
	#undef LOG_SKB_ERROR
	#define LOG_SKB_ERROR(fmt, args...) do{ \
		if(RTL_LogTypeMask.ERROR&&RTL_LogErrorMask.SKB&&RTL_LogModuleMask.NIC&&LOG_LIMIT)scrlog_printk("NIC-SKB-ERROR:"fmt, ## args); \
			}while(0)
	#endif

	#if defined(LOG_WARN)
	#undef LOG_WARN
	#define LOG_WARN(fmt, args...) do{ \
		if(RTL_LogTypeMask.WARN&&RTL_LogModuleMask.NIC&&LOG_LIMIT)scrlog_printk("NIC-WARN:"fmt, ## args); \
			}while(0)
	#endif

	#if defined(LOG_INFO)
	#undef LOG_INFO
	#define LOG_INFO(fmt, args...) do{ \
		if(RTL_LogTypeMask.INFO&&RTL_LogModuleMask.NIC&&LOG_LIMIT)scrlog_printk("NIC-INFO:"fmt, ## args); \
			}while(0)
	#endif

#endif

#endif
