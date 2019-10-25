

#ifndef __PU_DRV_H__
#define __PU_DRV_H__

#include <linux/fs.h>
#include <linux/types.h>
#include <linux/reset.h>

#define PDI_IOCTL_MAGIC  'V'

#define PLL_CLK_715 (0x10D336)
#define PLL_CLK_702 (0x10C186)
#define PLL_CLK_675 (0x10C176)
#define PLL_CLK_648 (0x10C166)
#define PLL_CLK_594 (0x10C146)
#define PLL_CLK_567 (0x10C136)
#define PLL_CLK_337 (0x12C176)
#define PLL_CLK_297 (0x12C146)

#define UNUSED_PARAMETER(p) (void)(p)

#define MISC_JPU_MINOR 107
#define MISC_MEM_MINOR 108
#define MISC_VE3_MINOR 109
#define MISC_VE1_MINOR 110

typedef struct pu_drv_context_t {
	struct fasync_struct *async_queue;
	unsigned long jpu_interrupt_reason;
	unsigned long vpu_interrupt_reason;
} pu_drv_context_t;

#ifdef CONFIG_RTK_RESERVE_MEMORY
int pu_alloc_dma_buffer(unsigned int size, unsigned long *phys_addr, unsigned long *base, unsigned int mem_type);
void pu_free_dma_buffer(unsigned long base, unsigned long phys_addr);
int pu_mmap_dma_buffer(struct vm_area_struct *vm);
unsigned long pu_mmap_kernel_buffer(unsigned long phys_addr, unsigned int size);
void pu_unmap_kernel_buffer(unsigned long base, unsigned long phys_addr);
#endif
void pu_pll_setting(unsigned long offset, unsigned int value, unsigned int bOverwrite, unsigned int bEnable);

#endif
