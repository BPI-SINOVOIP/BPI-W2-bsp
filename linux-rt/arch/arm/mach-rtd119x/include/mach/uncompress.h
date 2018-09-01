/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * Serial port stubs for kernel decompress status messages
 */

#include <linux/types.h>
#include <linux/serial_reg.h>

#include <asm/memory.h>
#include <asm/mach-types.h>


#define SYSTEM_CONSOLE		0
#define UART_CLOCK		27000000
#define DEFAULT_BAUNDRATE	115200

volatile u8 *uart_base;
int uart_shift;

static void putc(int c)
{
    if (!uart_base)
        return;

    while (!(uart_base[UART_LSR << uart_shift] & UART_LSR_THRE))
        barrier();

    uart_base[UART_TX << uart_shift] = c;
}

static inline void flush(void)
{
}

static int uart_setBaudrate(u32 baudrate)
{
    u8 tmp_LCR;
    u32 divisor;

    switch (baudrate) {
    case 9600:
    case 19200:
    case 38400:
    case 57600:
    case 115200:
    case 230400:
    case 460800:
    case 921600:
        break;
    default:
        return -1;
    }

    /* Enable access to the divisor latches by setting DLAB in LCR. */
    tmp_LCR = uart_base[UART_LCR << uart_shift];

    /* Set divisor latches. */
    uart_base[UART_LCR << uart_shift] = tmp_LCR | 0x80;
    divisor = ((UART_CLOCK + 8 * baudrate)/16 /baudrate );

    uart_base[UART_DLL << uart_shift] = divisor & 0xff;
    uart_base[UART_DLM << uart_shift] = ((divisor & 0xff00 ) >> 8);

    /* Restore line control register */
    uart_base[UART_LCR << uart_shift] = tmp_LCR;

    return 0;
}

#define U1RBR_THR_DLL		0x1801B200

static inline void __arch_decomp_setup(unsigned long arch_id)
{
    /*
     * Initialize the port based on the machine ID from the bootloader.
     * Note that we're using macros here instead of switch statement
     * as machine_is functions are optimized out for the boards that
     * are not selected.
     */
    do {
        switch(SYSTEM_CONSOLE)
        {
        case 0:
            uart_base = (u8 *)U1RBR_THR_DLL;
            break;
        default:
        case 1:
            uart_base = (u8 *)U1RBR_THR_DLL;
            break;
#if 0
        case 2:
            uart_base = (u8 *)U2RBR_THR_DLL;
            break;
        case 3:
            uart_base = (u8 *)U3RBR_THR_DLL;
            break;
#endif
        }

        uart_shift = 2;

        uart_base[UART_LCR << uart_shift] = 0x3;

        uart_setBaudrate(DEFAULT_BAUNDRATE);

        // Reset Tx/Rx FIFO
        uart_base[UART_FCR << uart_shift] = 0x6;
        // Enable FIFO
        uart_base[UART_FCR << uart_shift] = 0x1;
        uart_base[UART_MCR << uart_shift] = 0x0;
    } while (0);
}

#define arch_decomp_setup()	__arch_decomp_setup(arch_id)

/*
 * nothing to do
 */
#define arch_decomp_wdog()
