

#ifndef __VPU_DRV_H__
#define __VPU_DRV_H__

#include <linux/fs.h>
#include <linux/types.h>


#define VDI_IOCTL_MAGIC  'V'
#define VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY	_IO(VDI_IOCTL_MAGIC, 0)
#define VDI_IOCTL_FREE_PHYSICALMEMORY		_IO(VDI_IOCTL_MAGIC, 1)
#define VDI_IOCTL_WAIT_INTERRUPT			_IO(VDI_IOCTL_MAGIC, 2)
#define VDI_IOCTL_SET_CLOCK_GATE			_IO(VDI_IOCTL_MAGIC, 3)
#define VDI_IOCTL_RESET						_IO(VDI_IOCTL_MAGIC, 4)
#define VDI_IOCTL_GET_INSTANCE_POOL			_IO(VDI_IOCTL_MAGIC, 5)
#define VDI_IOCTL_GET_COMMON_MEMORY			_IO(VDI_IOCTL_MAGIC, 6)
#define VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO _IO(VDI_IOCTL_MAGIC, 8)
#define VDI_IOCTL_OPEN_INSTANCE				_IO(VDI_IOCTL_MAGIC, 9)
#define VDI_IOCTL_CLOSE_INSTANCE			_IO(VDI_IOCTL_MAGIC, 10)
#define VDI_IOCTL_GET_INSTANCE_NUM			_IO(VDI_IOCTL_MAGIC, 11)
#define VDI_IOCTL_ENABLE_INTERRUPT			_IO(VDI_IOCTL_MAGIC, 12)
#define VDI_IOCTL_SET_CLOCK					_IO(VDI_IOCTL_MAGIC, 13)
#define VDI_IOCTL_GET_CLOCK					_IO(VDI_IOCTL_MAGIC, 14)
#define VDI_IOCTL_SET_CLOCK_ENABLE			_IO(VDI_IOCTL_MAGIC, 15)
#define VDI_IOCTL_SET_CLOCK_DISABLE			_IO(VDI_IOCTL_MAGIC, 16)
#define VDI_IOCTL_GET_SUPPORT_TYPE			_IO(VDI_IOCTL_MAGIC, 17)
#define VDI_IOCTL_FOURK_INFO				_IO(VDI_IOCTL_MAGIC, 18)
#define VDI_IOCTL_SLEEP						_IO(VDI_IOCTL_MAGIC, 19)
#define VDI_IOCTL_WAKEUP					_IO(VDI_IOCTL_MAGIC, 20)

typedef enum {
	FOURK_SET_PENDING,	/* 0 */
	FOURK_GET_PENDING,
	FOURK_SET_INSTANCE_TYPE,
	FOURK_GET_INSTANCE_NUM,
    FOURK_GET_INSTIDX,
} FOURK_CODE;
	

typedef struct vpudrv_buffer_t {
	unsigned int size;
	unsigned long long phys_addr;
	unsigned long base;							/* kernel logical address in use kernel */
	unsigned long virt_addr;				/* virtual user space address */
} vpudrv_buffer_t;

typedef struct vpu_bit_firmware_info_t {
	unsigned int size;						// size of this structure
	unsigned int core_idx;
	unsigned long reg_base_offset;
	unsigned short bit_code[512];
} vpu_bit_firmware_info_t;

typedef struct vpu_clock_info_t{
	unsigned int value;
} vpu_clock_info_t;

typedef struct vpudrv_inst_info_t {
	unsigned int core_idx;
	unsigned int inst_idx;
	int inst_open_count;	// for output only
} vpudrv_inst_info_t;

typedef struct vpudrv_intr_info_t {
	unsigned int timeout;
	int intr_reason;
} vpudrv_intr_info_t;

typedef struct vpudrv_fourk_info_t {
	unsigned int core_idx;
	unsigned int inst_idx;
	FOURK_CODE setvalue;
	int value;
} vpudrv_fourk_info_t;

#endif
