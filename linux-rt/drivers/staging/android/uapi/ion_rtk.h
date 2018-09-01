/*
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_RTK_PHOENIX_ION_H
#define _LINUX_RTK_PHOENIX_ION_H

#include <linux/types.h>
#include <linux/cma.h>

//#include "ion.h"
//#include "../ion/ion.h"
/**
 * struct rtk_phoenix_ion_tiler_alloc_data - metadata passed from userspace for allocations
 * @w:		width of the allocation
 * @h:		height of the allocation
 * @fmt:	format of the data (8, 16, 32bit or page)
 * @flags:	flags passed to heap
 * @stride:	stride of the allocation, returned to caller from kernel
 * @handle:	pointer that will be populated with a cookie to use to refer
 *		to this allocation
 *
 * Provided by userspace as an argument to the ioctl
 */

#ifdef __KERNEL__
struct ion_heap *   ion_get_client_heap_by_mask(struct ion_client *client, unsigned int heap_id_mask);
long                rtk_phoenix_ion_ioctl(struct ion_client *client, unsigned int cmd, unsigned long arg);
#endif /* __KERNEL__ */

/* additional heaps used only on rtk_phoenix */
enum {
	RTK_PHOENIX_ION_HEAP_TYPE_TILER = ION_HEAP_TYPE_CUSTOM + 1,
	RTK_PHOENIX_ION_HEAP_TYPE_MEDIA,
	RTK_PHOENIX_ION_HEAP_TYPE_AUDIO,
	RTK_PHOENIX_ION_HEAP_TYPE_SECURE,
};

#define RTK_PHOENIX_ION_HEAP_TILER_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_TILER)
#define RTK_PHOENIX_ION_HEAP_MEDIA_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_MEDIA)
#define RTK_PHOENIX_ION_HEAP_AUDIO_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_AUDIO)
#define RTK_PHOENIX_ION_HEAP_SECURE_MASK (1 << RTK_PHOENIX_ION_HEAP_TYPE_SECURE)

struct RTK_ION_IOC_GET_MEMORY_INFO_S {
	unsigned int heapMask; /* request  : Select the heap to be queried */
	unsigned int flags; /* request  : Set the conditions to query, 0 is to query all the conditions */
	unsigned int usedSize; /* response */
	unsigned int freeSize; /* response */
};

struct RTK_ION_IOC_SYNC_RANE {
	ion_user_handle_t handle;
	unsigned long long phyAddr;
	unsigned int len;
};

struct RTK_ION_IOC_PHY_INFO {
	ion_user_handle_t handle;
	unsigned long long addr;
	unsigned long long len;
};

#define RTK_ION_IOC_MAGIC 'R'
#define RTK_PHOENIX_ION_TILER_ALLOC (0x0)
#define RTK_PHOENIX_ION_GET_LAST_ALLOC_ADDR (0x1)
#define RTK_ION_IOC_INVALIDATE (0x10)
#define RTK_ION_IOC_FLUSH (0x11)
#define RTK_ION_IOC_GET_MEMORY_INFO _IOWR(RTK_ION_IOC_MAGIC, 0x12, struct RTK_ION_IOC_GET_MEMORY_INFO_S)
#define RTK_ION_IOC_INVALIDATE_RANGE (0x13)
#define RTK_ION_IOC_FLUSH_RANGE (0x14)
#define RTK_ION_IOC_GET_PHYINFO (0x15)

/**
 * These should match the defines in the tiler driver
 */
enum {
	TILER_PIXEL_FMT_MIN = 0,
	TILER_PIXEL_FMT_8BIT = 0,
	TILER_PIXEL_FMT_16BIT = 1,
	TILER_PIXEL_FMT_32BIT = 2,
	TILER_PIXEL_FMT_PAGE = 3,
	TILER_PIXEL_FMT_MAX = 3
};

/**
 * List of heaps in the system
 */
enum {
	RTK_PHOENIX_ION_HEAP_LARGE_SURFACES,
	RTK_PHOENIX_ION_HEAP_TILER,
	RTK_PHOENIX_ION_HEAP_SECURE_INPUT,
	RTK_PHOENIX_ION_HEAP_NONSECURE_TILER,
};

#endif /* _LINUX_RTK_PHOENIX_ION_H */
