/* Copyright 2012 Google Inc. All Rights Reserved. */

#ifndef MEMALLOC_H
#define MEMALLOC_H

#include <linux/ioctl.h>

#undef PDEBUG
//#define MEMALLOC_DEBUG
#ifdef MEMALLOC_DEBUG
#ifdef __KERNEL__
#define PDEBUG(fmt, args...) printk(KERN_INFO "memalloc: " fmt, ##args)
#else
#define PDEBUG(fmt, args...) fprintf(stderr, fmt, ##args)
#endif
#else
#define PDEBUG(fmt, args...)
#endif

typedef struct {
    unsigned bus_address;
    unsigned size;
    unsigned translation_offset;
    unsigned mem_type;
} MemallocParams;

#define MEMALLOC_IOC_MAGIC 'k'

#define MEMALLOC_IOCXGETBUFFER _IOWR(MEMALLOC_IOC_MAGIC, 1, MemallocParams)
#define MEMALLOC_IOCSFREEBUFFER _IOW(MEMALLOC_IOC_MAGIC, 2, unsigned long)

#define MEMALLOC_IOCHARDRESET _IO(MEMALLOC_IOC_MAGIC, 15) /* debugging tool */
#define MEMALLOC_IOC_MAXNR 15

#endif /* MEMALLOC_H */
