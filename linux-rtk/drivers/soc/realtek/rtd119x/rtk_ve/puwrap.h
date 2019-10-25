

#ifndef __PU_DRV_H__
#define __PU_DRV_H__

#include <linux/fs.h>
#include <linux/types.h>


#define PDI_IOCTL_MAGIC  'V'

typedef struct pu_drv_context_t {
	struct fasync_struct *async_queue;
	unsigned long jpu_interrupt_reason;
	unsigned long vpu_interrupt_reason;
} pu_drv_context_t;

#endif
