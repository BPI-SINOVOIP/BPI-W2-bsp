/* Copyright 2013 Google Inc. All Rights Reserved. */

#ifndef _VE3DEC_H_
#define _VE3DEC_H_
#include <linux/ioctl.h>
#include <linux/types.h>

#undef PDEBUG
//#define HANTRODEC_DEBUG
#ifdef HANTRODEC_DEBUG
#  ifdef __KERNEL__
#    define PDEBUG(fmt, args...) pr_info(fmt, ## args)
#  else
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...)
#endif

#define HXDEC_MAX_CORES                 1

struct core_desc
{
    __u32 id; /* id of the core */
    unsigned long regs; /* pointer to user registers */
    __u32 size; /* size of register space */
};

/* Use 'k' as magic number */
#define HANTRODEC_IOC_MAGIC  'k'

/*
 * S means "Set" through a ptr,
 * T means "Tell" directly with the argument value
 * G means "Get": reply by setting through a pointer
 * Q means "Query": response is on the return value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */

#define HANTRODEC_HW_PERFORMANCE    _IO(HANTRODEC_IOC_MAGIC, 2)
#define HANTRODEC_IOCGHWOFFSET      _IOR(HANTRODEC_IOC_MAGIC,  3, unsigned long)
#define HANTRODEC_IOCGHWIOSIZE      _IOR(HANTRODEC_IOC_MAGIC,  4, unsigned int)

#define HANTRODEC_IOC_CLI           _IO(HANTRODEC_IOC_MAGIC,  5)
#define HANTRODEC_IOC_STI           _IO(HANTRODEC_IOC_MAGIC,  6)
#define HANTRODEC_IOC_MC_OFFSETS    _IOR(HANTRODEC_IOC_MAGIC, 7, unsigned long)
#define HANTRODEC_IOC_MC_CORES      _IOR(HANTRODEC_IOC_MAGIC, 8, unsigned int)


#define HANTRODEC_IOCS_DEC_PUSH_REG  _IOW(HANTRODEC_IOC_MAGIC, 9, struct core_desc)

#define HANTRODEC_IOCH_DEC_RESERVE   _IO(HANTRODEC_IOC_MAGIC, 11)
#define HANTRODEC_IOCT_DEC_RELEASE   _IO(HANTRODEC_IOC_MAGIC, 12)

#define HANTRODEC_IOCX_DEC_WAIT      _IOWR(HANTRODEC_IOC_MAGIC, 15, struct core_desc)

#define HANTRODEC_IOCS_DEC_PULL_REG  _IOWR(HANTRODEC_IOC_MAGIC, 17, struct core_desc)

#define HANTRODEC_IOCG_CORE_WAIT     _IOR(HANTRODEC_IOC_MAGIC, 19, int)

#define HANTRODEC_IOX_ASIC_ID        _IOWR(HANTRODEC_IOC_MAGIC, 20, __u32)

#define HANTRODEC_DEBUG_STATUS       _IO(HANTRODEC_IOC_MAGIC, 29)

/* RTK ioctl */
#define HANTRODEC_SET_CLOCK_ENABLE   _IO(HANTRODEC_IOC_MAGIC, 28)
#define HANTRODEC_RESET_CLK_GATING   _IO(HANTRODEC_IOC_MAGIC, 27)
#define HANTRODEC_NOTIFY_RELEASE     _IO(HANTRODEC_IOC_MAGIC, 26)
#define HANTRODEC_GET_ASIC_REVISION  _IOR(HANTRODEC_IOC_MAGIC, 25, unsigned int)
#define HANTRODEC_GET_ASIC_REG       _IOWR(HANTRODEC_IOC_MAGIC, 24, struct core_desc)
#define HANTRODEC_BONDINGOFFSET      _IOR(HANTRODEC_IOC_MAGIC,  23, unsigned long)
#define HANTRODEC_BONDINGIOSIZE      _IOR(HANTRODEC_IOC_MAGIC,  22, unsigned int)
#define HANTRODEC_GET_INSTANCE     _IO(HANTRODEC_IOC_MAGIC, 32)
#define HANTRODEC_IOC_MAXNR 35
#endif /* !_HANTRODEC_H_ */
