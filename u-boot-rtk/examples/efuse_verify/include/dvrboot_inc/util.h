#ifndef __UTIL_H__
#define __UTIL_H__

#include "sysdefs.h"
#include "dvrboot_inc/io.h"
extern int printf(const char *fmt, ...);

#define UBOOT_DDR_OFFSET		0xa0000000	//for RTD299X
//#define UBOOT_DDR_OFFSET		0x20000000	//for pandaboard

#ifdef __ARM_ARCH_8A__
#define CP15ISB asm volatile ("ISB SY" : : : "memory")
#define CP15DSB asm volatile ("DSB SY" : : : "memory")
#define CP15DMB asm volatile ("DMB SY" : : : "memory")
#else
#define CP15ISB asm volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define CP15DSB asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define CP15DMB asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))
#endif

#define isb() __asm__ __volatile__ ("" : : : "memory")
#define nop() __asm__ __volatile__("mov\tr0,r0\t@ nop\n\t")

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

#define MAX_MALLOC_SIZE		16*1024*1024
#define MALLOC_BASE		(0xa4000000 - UBOOT_DDR_OFFSET)	//modify by angus, orininal value is 0xa6000000
#define	UARTINFO_TEMT_MASK					0x40
#define	UARTINFO_THRE_MASK					0x20
#define UARTINFO_TRANSMITTER_READY_MASK		(UARTINFO_TEMT_MASK | UARTINFO_THRE_MASK)

/* UART0 */
#if 1
#define  UART0_REG_BASE		0xb8062300  //see "RTD299X_ISO_MIS_OFF_arch_spec.doc"
#else
#define  UART0_REG_BASE		0xB801B100  //see "RTD299X_ISO_MIS_OFF_arch_spec.doc"
#endif
#define U0RBR_THR_DLL		(UART0_REG_BASE + 0x0)
#define U0IER_DLH		(UART0_REG_BASE + 0x4)
#define U0IIR_FCR		(UART0_REG_BASE + 0x8)
#define U0LCR			(UART0_REG_BASE + 0xc)
#define U0MCR			(UART0_REG_BASE + 0x10)
#define U0LSR			(UART0_REG_BASE + 0x14)
#define U0MSR			(UART0_REG_BASE + 0x18)
#define U0SCR			(UART0_REG_BASE + 0x1c)

#define U0FAR			(UART0_REG_BASE + 0x70)
#define U0TFR			(UART0_REG_BASE + 0x74)
#define U0RFW			(UART0_REG_BASE + 0x78)
#define U0USR			(UART0_REG_BASE + 0x7c)
#define U0TFL			(UART0_REG_BASE + 0x80)
#define U0RFL			(UART0_REG_BASE + 0x84)
#define U0SRR			(UART0_REG_BASE + 0x88)
#define U0SBCR			(UART0_REG_BASE + 0x8c)
#define U0BCR			(UART0_REG_BASE + 0x90)
#define U0SDMAM			(UART0_REG_BASE + 0x94)
#define U0SFE			(UART0_REG_BASE + 0x98)
#define U0SRT			(UART0_REG_BASE + 0x9c)
#define U0STET			(UART0_REG_BASE + 0xa0)
#define U0HTX			(UART0_REG_BASE + 0xa4)
#define U0DMASA			(UART0_REG_BASE + 0xa8)
#define U0CPR			(UART0_REG_BASE + 0xf4)
#define U0UCV			(UART0_REG_BASE + 0xf8)
#define U0CTR			(UART0_REG_BASE + 0xfc)
//end by angus

#define CODE_VAILD_MAGIC_NUMBER 0xF9E8D7C6

typedef int (*PrintFuncPtr_t)(const char *fmt, ...);
typedef void (*Flush_Dcache_AllPtr_t)(void);

extern PrintFuncPtr_t rtprintf;
extern Flush_Dcache_AllPtr_t rtflush_dcache_all;

//#define printf(fmt, args...)

#define ENABLE_UART_FUNC
//#define ENABLE_PRINTF

#ifdef ENABLE_PRINTF
#define print_uart printf
#endif
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
int IsHexStr(char *s);
void *simple_malloc(unsigned int n_bytes);
void hexdump(const char *str, const void *buf, unsigned int length);
extern void * memset(void * s,int c,size_t count);
//extern int printf(const char* fmt, ...);

#define MAX_RETRY_CNT   5
#define __align__ __attribute__((aligned (8)))
//#define DEBUG_PRT

typedef enum {
        ENUM_TYPE_UNKNOWN,
        ENUM_TYPE_AES_KEY,
        ENUM_TYPE_AES_SEED,
        ENUM_TYPE_AES_DEC_KEY,
        ENUM_TYPE_AES_DEC_SEED,
	ENUM_TYPE_B00_KEY_OBFUSE,
	ENUM_TYPE_B00_KEY_DEOBFUSE
    } otp_method_enum_t;

#endif
