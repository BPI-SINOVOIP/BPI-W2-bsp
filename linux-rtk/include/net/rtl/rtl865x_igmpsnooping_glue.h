/*
* Copyright c                  Realsil Semiconductor Corporation, 2006
* All rights reserved.
*
* Program :  IGMP glue file
* Abstract :
* Author :qinjunjie
* Email:qinjunjie1980@hotmail.com
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
*/

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef SUCCESS
#define SUCCESS 	0
#endif

#ifndef FAILED
#define FAILED -1
#endif

#if 0
#ifndef _RTL_TYPES_H
typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char uint8;
typedef char int8;
#endif
#else
#include "rtl_types.h"
#endif

#ifndef RTL_MULTICAST_SNOOPING_GLUE
#define RTL_MULTICAST_SNOOPING_GLUE

#define swapl32(x)\
	((((x) & 0xff000000U) >> 24) | \
	(((x) & 0x00ff0000U) >>  8) | \
	(((x) & 0x0000ff00U) <<  8) | \
	(((x) & 0x000000ffU) << 24))
#define swaps16(x)        \
	((((x) & 0xff00) >> 8) | \
	(((x) & 0x00ff) << 8))

#ifdef _LITTLE_ENDIAN

#ifndef ntohs
#define ntohs(x)   (swaps16(x))
#endif

#ifndef ntohl
#define ntohl(x)   (swapl32(x))
#endif

#ifndef htons
#define htons(x)   (swaps16(x))
#endif

#ifndef htonl
#define htonl(x)   (swapl32(x))
#endif

#else

#ifndef ntohs
#define ntohs(x)	(x)
#endif

#ifndef ntohl
#define ntohl(x)	(x)
#endif

#ifndef htons
#define htons(x)	(x)
#endif

#ifndef htonl
#define htonl(x)	(x)
#endif

#endif

#ifdef __KERNEL__
#define rtl_gluePrintf printk
#else
#define rtl_gluePrintf printf
#endif

void *rtl_glueMalloc(uint32 NBYTES);
void rtl_glueFree(void *memblock);

void rtl_glueMutexLock(void);
void rtl_glueMutexUnlock(void);


#ifdef CONFIG_SMP
#include <linux/spinlock.h>
extern int lock_owner_igmp;
extern spinlock_t lock_igmp;
extern int lock_owner_igmp_concurrent;
extern spinlock_t lock_igmp_concurrent;

#ifdef CONFIG_PREEMPT
#define SMP_LOCK_IGMP(__x__)    \
	do { \
		get_cpu(); \
		if (lock_owner_igmp != smp_processor_id()) { \
			lock_owner_igmp = smp_processor_id(); \
			put_cpu(); \
			spin_lock_irqsave(&lock_igmp, (__x__)); \
		} else {\
			lock_owner_igmp = smp_processor_id();\
			put_cpu(); \
			rtlglue_printf("[%s %s %d] recursion detection in IGMP\n", __FILE__, __FUNCTION__, __LINE__); \
		} \
	} while (0)
#else
#define SMP_LOCK_IGMP(__x__)	\
	do { \
		if (lock_owner_igmp != smp_processor_id()) \
			spin_lock_irqsave(&lock_igmp, (__x__)); \
		else \
			rtlglue_printf("[%s %s %d] recursion detection in IGMP\n", __FILE__, __FUNCTION__, __LINE__); \
		lock_owner_igmp = smp_processor_id();\
	} while (0)
#endif

#define SMP_UNLOCK_IGMP(__x__) \
	do { \
		lock_owner_igmp = -1; \
		spin_unlock_irqrestore(&lock_igmp, (__x__)); \
	} while (0)

#define SMP_LOCK_IGMP_CONCURRENT(__x__)			spin_lock_irqsave(&lock_igmp_concurrent, (__x__))
#define SMP_UNLOCK_IGMP_CONCURRENT(__x__) 		spin_unlock_irqrestore(&lock_igmp_concurrent, (__x__))

#else
#define SMP_LOCK_IGMP(__x__)
#define SMP_UNLOCK_IGMP(__x__)
#endif

#endif

