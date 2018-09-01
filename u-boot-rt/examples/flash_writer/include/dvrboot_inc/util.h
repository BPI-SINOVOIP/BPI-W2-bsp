#ifndef __UTIL_H__
#define __UTIL_H__

#include <project_config_f.h>
#include <platform_iso.h>
#include <sysdefs.h>
#include "sys_reg.h"
#include "../../cache.h"

#define FOR_ICE_LOAD                        //for ice load
#define UBOOT_DDR_OFFSET		0xa0000000	//for RTD299X
//#define UBOOT_DDR_OFFSET		0x20000000	//for pandaboard

#ifdef FOR_ICE_LOAD
#define rtprintf(format,args...)
#endif

//#define DUMP_NAND_FLASH
//#define DUMP_SPI_FLASH
//#define DUMP_EMMC_FLASH
#define ENABLE_NAND_DRIVER
//#define ERASE_WHOLE_NAND_BEFORE_WRITIE
//#define FAKE_EMMC_API
//#define FAKE_SPI_API
//#define ROMCODE_ON_SPI //config by .inc

#define NONE_SECURE_BOOT	0
#define NDS_SECURE_BOOT		1
#define RTK_SECURE_BOOT		2
#define DCAS_SECURE_BOOT	3

//#define FLASH_TYPE_NOR_PARALLEL		0x0
#define FLASH_TYPE_NAND		   	0x0
#define FLASH_TYPE_SPI   		0x1
#define FLASH_TYPE_EMMC         0x2

#define REG8( addr )		  (*(volatile UINT8 *) (addr))
#define REG16( addr )		  (*(volatile UINT16 *)(addr))
#define REG32( addr )		  (*(volatile UINT32 *)(addr))
#define REG64( addr )		  (*(volatile UINT64 *)(addr))

#define CPU_TO_BE32( value ) ( (                ((UINT32)value)  << 24) |   \
                               ((0x0000FF00UL & ((UINT32)value)) <<  8) |   \
                               ((0x00FF0000UL & ((UINT32)value)) >>  8) |   \
                               (                ((UINT32)value)  >> 24)   )
#define BE32_TO_CPU( value ) CPU_TO_BE32( value )

/*
typedef unsigned char		UINT8;
typedef signed char			INT8;
typedef unsigned short		UINT16;
typedef signed short		INT16;
typedef unsigned int		UINT32;
typedef signed int			INT32;
typedef unsigned long long	UINT64;
typedef signed long long	INT64;
typedef UINT8				bool;
*/

#define KUSEG_MSK		  0x80000000
#define KSEG_MSK		  0xE0000000
#define KUSEGBASE		  0x00000000
#define KSEG0BASE		  0x80000000
#define KSEG1BASE		  0xA0000000
#define KSSEGBASE		  0xC0000000
#define KSEG3BASE		  0xE0000000

#define KSEG0(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG0BASE)
#define KSEG1(addr)     (((UINT32)(addr) & ~KSEG_MSK)  | KSEG1BASE)
#define KSSEG(addr)	(((UINT32)(addr) & ~KSEG_MSK)  | KSSEGBASE)
#define KSEG3(addr)	(((UINT32)(addr) & ~KSEG_MSK)  | KSEG3BASE)
#define KUSEG(addr)	(((UINT32)(addr) & ~KUSEG_MSK) | KUSEGBASE)
#define PHYS(addr) 	((UINT32)(addr)  & ~KSEG_MSK)

#define PARAMETER_TMP_ADDR					(0xA2400000 - UBOOT_DDR_OFFSET)
#define DATA_TMP_ADDR						(0xA2600000 - UBOOT_DDR_OFFSET)
#define MAX_MALLOC_SIZE						(16<<20) // 16MB
#define MALLOC_BASE						(0xA8000000 - UBOOT_DDR_OFFSET)
#define REF_MALLOC_BASE						(0xA9000000 - UBOOT_DDR_OFFSET)
#define MALLOC_BASE2						(0xAA000000 - UBOOT_DDR_OFFSET)
#define REF_MALLOC_BASE2					(0xAB000000 - UBOOT_DDR_OFFSET)

#define CODE_VAILD_MAGIC_NUMBER 0xF9E8D7C6

typedef int (*PrintFuncPtr_t)(const char *fmt, ...);
typedef void (*Flush_Dcache_AllPtr_t)(void);
typedef void (*Flush_CachePtr_t)(unsigned long start, unsigned long size);

extern PrintFuncPtr_t rtprintf;
extern Flush_Dcache_AllPtr_t rtflush_dcache_all;
extern Flush_CachePtr_t rtflush_cache;

#ifdef FOR_ICE_LOAD
#define U_FLUSH_CACHE(start, size)	\
	if( 1 ) {			\
		v7_maint_dcache_all(ARMV7_DCACHE_CLEAN_INVAL_ALL);	\
		sync();			\
	}
#else
#define U_FLUSH_CACHE(start, size)	\
	if( rtflush_cache ) {			\
		rtflush_cache(start, size);	\
	}
#endif

#define printf(fmt, args...)

#define ENABLE_UART_FUNC
//#define ENABLE_PRINTF

#ifdef ENABLE_PRINTF
#define print_uart printf
#endif

//sb2
#define PHOENIX_REV_A   0x0000
#define PHOENIX_REV_B   0x0001
#define IS_CHIP_REV_B() ((REG32(SB2_CHIP_INFO)>>16) == PHOENIX_REV_B)
#define GET_CHIP_REV() (REG32(SB2_CHIP_INFO)>>16)

/************************************************************************
 *  Public function
 ************************************************************************/
void sync(void);
void init_uart(void);
void wait_done(volatile UINT32 *addr, UINT32 mask, UINT32 value);



#ifdef ENABLE_UART_FUNC
void print_uart(char *message);
#endif
void print_val(UINT32 val, UINT32 len);

void set_memory(void *dst, UINT8 value, UINT32 size);
void copy_memory(void *dest, void *src, UINT32 size);
void spi_copy_memory(void *dest, void *src, UINT32 size);
int compare_memory(void *s1, void *s2, UINT32 size);
int compare_str(const char *s1, const char *s2);
void sys_dcache_flush_all(void);
void put_char(char ch);
unsigned int hexstr2int(char *s);
void *simple_malloc(unsigned int n_bytes);
void hexdump(const char *str, const void *buf, unsigned int length);
extern void * memset(void * s,int c,size_t count);
//extern int printf(const char* fmt, ...);

#endif
