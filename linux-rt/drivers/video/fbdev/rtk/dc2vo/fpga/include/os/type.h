#ifndef __FPGA_OS_TYPE_H__
#define __FPGA_OS_TYPE_H__
#include <rbus/reg.h>


#define RTK_VIRT_ADDR_MAP(addr) (RBUS_BASE_VIRT + ((unsigned int)addr - RBUS_BASE_PHYS))

#define WRITE_REG_INT32U(addr,val)  *(volatile unsigned int *) RTK_VIRT_ADDR_MAP(addr) = (unsigned int)(val)
#define READ_REG_INT32U(addr)       *(volatile unsigned int *) RTK_VIRT_ADDR_MAP(addr)

#define INT8U unsigned short int
#define INT32U unsigned int


#endif
