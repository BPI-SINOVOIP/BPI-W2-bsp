/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __RTK_TRACE_H__
#define __RTK_TRACE_H__

/*
 * These numbers are used from the kernel command line and sysfs
 * to control filtering. Remove items from here with extreme caution.
 */
enum logk_event_type {
	LOGK_NONE = 0,
	LOGK_READL = 1,
	LOGK_WRITEL = 2,
	LOGK_LOGBUF = 3,
	LOGK_HOTPLUG = 4,
	LOGK_CTXID = 5,
	LOGK_TIMESTAMP = 6,
	LOGK_L2CPREAD = 7,
	LOGK_L2CPWRITE = 8,
	LOGK_IRQ = 9,
	LOGK_DIE = 10,
	LOGK_INITCALL = 11,
	LOGK_SOFTIRQ = 12,
	LOGK_HVC = 13,
};

#define LOGTYPE_NOPC 0x80

struct rtk_trace_platform_data {
	unsigned int size;
};

#if defined(CONFIG_RTK_TRACER)
int remove_vmap_info(void *va, int check_init);
int inject_vmap_info(void *va, unsigned long size , phys_addr_t pa, int check_init);

void rtk_trace_disable(void);

/*
 * returns 1 if data was logged, 0 otherwise
 */
int uncached_logk_pc(enum logk_event_type log_type, void *caller,
				void *data);

/*
 * returns 1 if data was logged, 0 otherwise
 */
int uncached_logk(enum logk_event_type log_type, void *data);

#define ETB_WAYPOINT  do { \
				BRANCH_TO_NEXT_ISTR; \
				nop(); \
				BRANCH_TO_NEXT_ISTR; \
				nop(); \
			} while (0)

#define BRANCH_TO_NEXT_ISTR  asm volatile("b .+4\n" : : : "memory")
/*
 * both the mb and the isb are needed to ensure enough waypoints for
 * etb tracing
 */
#define LOG_BARRIER	do { \
				mb(); \
				isb();\
			 } while (0)
#else /* !CONFIG_RTK_TRACER */
static inline int remove_vmap_info(void *va, int check_init) { return 0; }
static inline int inject_vmap_info(void *va, unsigned long size , phys_addr_t pa, int check_init) { return 0; }

static inline void rtk_trace_disable(void) { return; }

static inline int uncached_logk_pc(enum logk_event_type log_type,
					void *caller,
					void *data) { return 0; }

static inline int uncached_logk(enum logk_event_type log_type,
					void *data) { return 0; }

#define ETB_WAYPOINT
#define BRANCH_TO_NEXT_ISTR
/*
 * Due to a GCC bug, we need to have a nop here in order to prevent an extra
 * read from being generated after the write.
 */
#define LOG_BARRIER		nop()
#endif /* CONFIG_RTK_TRACER */

#endif /* __RTK_TRACE_H__ */
