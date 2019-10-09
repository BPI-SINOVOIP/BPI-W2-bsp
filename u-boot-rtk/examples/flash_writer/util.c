//#include <stdio.h>
//#include <string.h>
//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>
#include "sysdefs.h"
#include "dvrboot_inc/util.h"
#include "uart.h"
#include "uart_reg.h"
#include "iso_reg.h"
#include "dvrboot_inc/mis_reg.h"
#include "rtkemmc.h"

/************************************************************************
 *  Definitions for print to UART0
*************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
UINT8 sys_l2cache_enabled = 0;	// do not use it
#ifdef UART_NEW_STYLE
volatile        UARTREG         *UartReg = (UARTREG *) UARTREG_BASE_ADDRESS;
#endif

/************************************************************************
 *  Static variables
 ************************************************************************/
static void serial_write(UINT8  *p_param);

//extern void flush_dcache_all(void);

/************************************************************************
 *
 *                          sync
 *  Description :
 *  -------------
 *  
 *  
 *
 *  Parameters :
 *  ------------
 *
 *
 *
 *  Return values :
 *  ---------------
 *
 *  
 *
 *
 ************************************************************************/
void sync(void)
{
    CP15DMB;
    REG32(0x9801a020) = 0x0;
    CP15DMB;
}

void wait_done(volatile UINT32 *addr, UINT32 mask, UINT32 value){
	int n = 0;
	while (((*addr) &mask) != value)
	{
		if(n++ > 3000)
		{
			prints("Time out \n");
			return;      
	 	}   
		mdelay(1);
	}
}


void init_uart(void)
{
        unsigned int reg_val;
        unsigned int urMuxPad_val = 0x00555000;

        //1195, set ur0,ur1 pin mux, pin : 12~23
        reg_val = REG32(ISO_muxpad0) & ~(0x00fff000);
        REG32(ISO_muxpad0) = reg_val | urMuxPad_val;

#ifdef ENABLE_UART_FUNC
        // init uart0
        REG32(U0LCR) = 0x90;
#ifdef FPGA
        //REG32(U0RBR_THR_DLL) = 0x1b;  // 115200 baud (for FPGA 50MHz) 50*1000*1000/115200/16
        REG32(U0RBR_THR_DLL) = 0x12;    // 115200 baud (for FPGA 33MHz) 33*1000*1000/115200/16
#else
        REG32(U0RBR_THR_DLL) = 0xe;             // 115200 baud (for ASIC 27MHz)
#endif
        REG32(U0IER_DLH) = 0;
        REG32(U0LCR) = 0x3;                             // 8-N-1
        REG32(U0IIR_FCR) = 0xb7;
        REG32(U0IER_DLH) = 0;

#if 0
        //init uart1
        REG32(U1LCR) = 0x90;
#ifdef FPGA
        REG32(U1RBR_THR_DLL) = 0x12;    // 115200 baud (for FPGA 33MHz) 33*1000*1000/115200/16
#else
        REG32(U1RBR_THR_DLL) = 0xf;             // 115200 baud (for ASIC 27MHz)
#endif
        REG32(U1IER_DLH) = 0;
        REG32(U1LCR) = 0x3;                     // 8-N-1
        REG32(U1IIR_FCR) = 0xb7;
        REG32(U1IER_DLH) = 0;
#endif
#endif

}

void set_focus_uart(int currentUartPort)
{
        UartReg = (currentUartPort == 0) ? (UARTREG *)UART0_REG_BASE : (UARTREG *)UART1_REG_BASE;
}

void serial_write(unsigned char  *p_param)
{
        while((UartReg->UartLsr.Value & UARTINFO_TRANSMITTER_READY_MASK) != UARTINFO_TRANSMITTER_READY_MASK);

        UartReg->UartRbrTheDll.Value = *p_param;
}

void prints(const char *ch)
{
#ifdef ENABLE_UART_FUNC

        unsigned char ch8;
        unsigned char tmpBuf[2048]={0};

        memset(tmpBuf, 0x00, 2048);


        while (*ch != '\0') {
                ch8 = *ch;
                if (*ch++ == '\n') {
                        ch8 = 0x0d;
                        serial_write((UINT8 *)&ch8);
                        ch8 = 0x0a;
                }
                serial_write((UINT8 *) &ch8);
        }
#endif
}

void print_val(UINT32 val, UINT32 len)
{
#ifdef ENABLE_UART_FUNC
        unsigned char ch;

        len--;
        do {
                ch = (val >> (len << 2)) & 0xf;
                ch += (ch < 0xa ? 0x30 : 0x37);
                serial_write(&ch);
        } while(len--);
#endif
}

void print_hex(unsigned int value)
{
#ifdef ENABLE_UART_FUNC
        print_val(value, 8);
#endif
}

#ifdef ENABLE_UART_FUNC
#define print_uart prints
#endif

//dummy function
void sys_dcache_flush_all(void)
{
	//rtflush_dcache_all();
    return;
}  

void put_char(char ch)
{
#ifdef ENABLE_UART_FUNC

	serial_write(&ch);
#endif
}

unsigned int hexstr2int(char *s)
{
	return (unsigned int) strtoul (s, (char **) 0, 16);
}

void *simple_malloc(unsigned int n_bytes)
{
	static unsigned int alloc_current = MALLOC_BASE;
	static unsigned int alloc_count = 0;
	void *p;

	if ((alloc_count + n_bytes) > MAX_MALLOC_SIZE) {
		// exceed limit
		return NULL;
	}

	p = (void *)(alloc_current);
	// always aligned to word boundary
	if (n_bytes & 0x3)
		n_bytes = (n_bytes & ((unsigned int)~0x3)) + 0x4;

	alloc_current += n_bytes;
	alloc_count += n_bytes;
	return p;
}

int is_hex_digit(char c)
{
	if ((c >= '0') && (c <='9'))
		return 0;
	else if ((c >= 'A') && (c <= 'F'))
		return 0;
	else if ((c >= 'a') && (c <= 'f'))
		return 0;
	else
		return -1;
}

void hexdump(const char *str, const void *buf, unsigned int length)
{
	unsigned int i;
	char *ptr = (char *)buf;
	
	if ((buf == NULL) || (length == 0)) {
		prints("NULL\n");
		return;
	}

	prints(str == NULL ? __FUNCTION__ : str);
	prints(" (0x");
	print_hex((UINT32)buf);
	prints(")\n");

	for (i = 0; i < length; i++) {
		print_val((unsigned int)(ptr[i]), 2);

		if ((i & 0xf) == 0xf)
			prints("\n");
		else
			prints(" ");
	}
	prints("\n");
}

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void * memset(void * s,int c,size_t count)
{
	unsigned long *sl = (unsigned long *) s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if ( ((ulong)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}

void set_memory(void *dst, UINT8 value, UINT32 size)
{
	UINT32 i;	
	for (i=0; i<size; i++)
		REG8(((UINT32)dst) + i) = value;
}

void copy_memory(void *dst, void *src, UINT32 size)
{
	UINT32 i;	
	for (i=0; i<size; i++)
		rtd_outb((((UINT32)dst) + i) , rtd_inb(((UINT32)src) + i));
}


int compare_memory(void *s1, void *s2, UINT32 size)
{
	UINT32 i;
	char *p1, *p2;
	
	p1 = (char *)s1;
	p2 = (char *)s2;
	for (i = 0; i < size; i++)
	{
		if (p1[i] != p2[i])
			return (int)p1[i] - (int)p2[i];
	}
	
	return 0;
}

int compare_str(const char *s1, const char *s2)
{
	UINT32 i = 0;

	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (int)s1[i] - (int)s2[i];
		i++;
	}
	
	return 0;
}

int swap_endian(UINT32 input)
{
	UINT32 output;

	output = (input & 0xff000000)>>24|
			 (input & 0x00ff0000)>>8|
			 (input & 0x0000ff00)<<8|
			 (input & 0x000000ff)<<24;
	
	return output;
}

void watchdog_reset(void)
{	
	REG32(MIS_TCWCR) = 0xa5;	// disable watchdog
	REG32(MIS_TCWTR) = 0x1;		// clear watchdog counter

	// set overflow count
	REG32(MIS_TCWOV) = 0x0;

	REG32(MIS_TCWCR) = 0;		// enable watchdog
}

/************************************************************************
 *

Uboot is a stand-alone application; raise() is an OS call on Linux that
raises a signal (in this case SIGFPE, with the subcode of
division-by-zero).

What you need here is a suitable definition of __div0 for your division
function (__div0 is called if the user attempts to divide by zero).  In
most bare-metal apps like uboot, you simply need a definition of __div0
that returns 0 rather than throwing an exception.

The implementation of __div0 that comes with the arm-none-eabi build of
the tools should do that.  Perhaps you should use that version of the
compiler for building uboot, not the arm-none-linux-gnueabi version.
*
*
************************************************************************/
void __div0 (void)
{
}

