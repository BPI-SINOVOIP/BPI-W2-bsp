#ifndef __SE_DRIVER_H__
#define __SE_DRIVER_H__

#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/dma-mapping.h>

//#include "se_export.h"
//#include "debug.h"

#ifdef CONFIG_ARCH_RTD129x
#  define SE_NUM_ENGINES       2
#elif defined(CONFIG_ARCH_RTD139x)
#  define SE_NUM_ENGINES       1
#elif defined(CONFIG_ARCH_RTD16xx)
#  define SE_NUM_ENGINES       1
#else
#  error "unknown platform"
#endif

#define SE_COMMAND_ENTRIES		4096
#define SE_CMDBUF_SIZE			(SE_COMMAND_ENTRIES * sizeof(uint32_t))

#define MAX_QUEUE_ENTRIES		32
#define BUF_OFFSET				12
#define BUF_SIZE				(4096*32 - BUF_OFFSET)

typedef struct se_engine {
	volatile uint64_t CmdBuf;           //kernel virtual start address of command queue
	volatile uint32_t CmdBase;          //physical start address of command queue
	volatile uint32_t CmdLimit;         //physical end address of command queue
	volatile uint32_t CmdWritePtr;      //physical address of write pointer
	volatile uint32_t BufSize;          //total size of command queue
} se_engine_t;

typedef struct se_hw {
	struct se_engine engine[SE_NUM_ENGINES];
} se_hw_t;

typedef struct se_resource {
	void __iomem		*base;
	int					irq;
} se_resource_t;

#endif // __SE_DRIVER_H__
