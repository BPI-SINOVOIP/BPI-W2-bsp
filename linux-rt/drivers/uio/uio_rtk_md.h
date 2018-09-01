#ifndef __MD_DRIVER_H__
#define __MD_DRIVER_H__

#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/dma-mapping.h>

//#include "md_export.h"
//#include "debug.h"

#define MD_NUM_ENGINES			1 //3
#define MD_COMMAND_ENTRIES		4096
#define MD_CMDBUF_SIZE			(MD_COMMAND_ENTRIES * sizeof(uint32_t))

#define MAX_QUEUE_ENTRIES		32
#define BUF_OFFSET				12
#define BUF_SIZE				(4096*32 - BUF_OFFSET)

typedef struct md_engine {
	volatile uint64_t CmdBuf;           //kernel virtual start address of command queue
	volatile uint32_t CmdBase;          //physical start address of command queue
	volatile uint32_t CmdLimit;         //physical end address of command queue
	volatile uint32_t CmdWritePtr;      //physical address of write pointer
	volatile uint32_t BufSize;          //total size of command queue
} md_engine_t;

typedef struct md_hw {
	struct md_engine engine[MD_NUM_ENGINES];
} md_hw_t;

typedef struct md_resource {
	void __iomem		*base;
	int					irq;
} md_resource_t;

#endif // __MD_DRIVER_H__
