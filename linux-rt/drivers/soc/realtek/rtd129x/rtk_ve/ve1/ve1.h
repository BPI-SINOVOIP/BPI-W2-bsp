/**
  ve1.c

  linux device driver for VPU.

 Copyright (C) 2006 - 2013  REALTEK INC.

  This library is free software; you can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the Free
  Software Foundation; either version 2.1 of the License, or (at your option)
  any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
  details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St, Fifth Floor, Boston, MA
  02110-1301  USA

*/

#ifndef __VPU_DRV_H__
#define __VPU_DRV_H__

#include <linux/fs.h>
#include <linux/types.h>

#define USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY

#define VDI_IOCTL_MAGIC 'V'
#define VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY _IO(VDI_IOCTL_MAGIC, 0)
#define VDI_IOCTL_FREE_PHYSICALMEMORY _IO(VDI_IOCTL_MAGIC, 1)
#define VDI_IOCTL_WAIT_INTERRUPT _IO(VDI_IOCTL_MAGIC, 2)
#define VDI_IOCTL_SET_CLOCK_GATE _IO(VDI_IOCTL_MAGIC, 3)
#define VDI_IOCTL_RESET _IO(VDI_IOCTL_MAGIC, 4)
#define VDI_IOCTL_GET_INSTANCE_POOL _IO(VDI_IOCTL_MAGIC, 5)
#define VDI_IOCTL_GET_COMMON_MEMORY _IO(VDI_IOCTL_MAGIC, 6)
#define VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO _IO(VDI_IOCTL_MAGIC, 8)
#define VDI_IOCTL_OPEN_INSTANCE _IO(VDI_IOCTL_MAGIC, 9)
#define VDI_IOCTL_CLOSE_INSTANCE _IO(VDI_IOCTL_MAGIC, 10)
#define VDI_IOCTL_GET_INSTANCE_NUM _IO(VDI_IOCTL_MAGIC, 11)
#define VDI_IOCTL_GET_REGISTER_INFO _IO(VDI_IOCTL_MAGIC, 12)

/* RTK ioctl */
#define VDI_IOCTL_SET_RTK_CLK_GATING _IO(VDI_IOCTL_MAGIC, 16)
#define VDI_IOCTL_SET_RTK_CLK_PLL _IO(VDI_IOCTL_MAGIC, 17)
#define VDI_IOCTL_GET_RTK_CLK_PLL _IO(VDI_IOCTL_MAGIC, 18)
#define VDI_IOCTL_GET_RTK_SUPPORT_TYPE _IO(VDI_IOCTL_MAGIC, 19)
#define VDI_IOCTL_GET_RTK_ASIC_REVISION _IO(VDI_IOCTL_MAGIC, 20)
#define VDI_IOCTL_SET_RTK_CLK_SELECT _IO(VDI_IOCTL_MAGIC, 21)
#define VDI_IOCTL_GET_RTK_CLK_SELECT _IO(VDI_IOCTL_MAGIC, 22)

#define VE_PLL_SYSH	0x000
#define VE_PLL_VE1	0x001
#define VE_PLL_VE2	0x010

typedef struct vpudrv_buffer_t {
	unsigned int size;
	unsigned long phys_addr;
	unsigned long base; /* kernel logical address in use kernel */
	unsigned long virt_addr; /* virtual user space address */
	unsigned int mem_type; /* RTK, for protect memory */
} vpudrv_buffer_t;

typedef struct vpu_bit_firmware_info_t {
	unsigned int size; /* size of this structure*/
	unsigned int core_idx;
	unsigned long reg_base_offset;
	unsigned short bit_code[512];
} vpu_bit_firmware_info_t;

typedef struct vpu_clock_info_t{
	unsigned int core_idx;
	unsigned int enable;
	unsigned int value;
} vpu_clock_info_t;

typedef struct vpudrv_inst_info_t {
	unsigned int core_idx;
	unsigned int inst_idx;
	int inst_open_count; /* for output only*/
} vpudrv_inst_info_t;

typedef struct vpudrv_intr_info_t {
	unsigned int core_idx;
	unsigned int timeout;
	int intr_reason;
} vpudrv_intr_info_t;
#endif
