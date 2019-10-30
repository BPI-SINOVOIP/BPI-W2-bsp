/************************************************************************
 *
 *  uart_reg.h
 *
 *  Defines for Phoenix UART registers
 *
 ************************************************************************/

#ifndef UART_REG_H
#define UART_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
/* UART0 */                                   
#define UART0_REG_BASE	0x98007800  //see iso document"

#define U0RBR_THR_DLL	(UART0_REG_BASE + 0x0)
#define U0IER_DLH		(UART0_REG_BASE + 0x4)
#define U0IIR_FCR		(UART0_REG_BASE + 0x8)
#define U0LCR			(UART0_REG_BASE + 0xc)
#define U0MCR			(UART0_REG_BASE + 0x10)
#define U0LSR			(UART0_REG_BASE + 0x14)
#define U0MSR			(UART0_REG_BASE + 0x18)
#define U0SCR			(UART0_REG_BASE + 0x1c)
#define U0SRBR          (UART0_REG_BASE + 0x30)
#define U0FAR			(UART0_REG_BASE + 0x70)
#define U0TFR			(UART0_REG_BASE + 0x74)
#define U0RFW			(UART0_REG_BASE + 0x78)
#define U0USR			(UART0_REG_BASE + 0x7c)
#define U0TFL			(UART0_REG_BASE + 0x80)
#define U0RFL			(UART0_REG_BASE + 0x84)
#define U0SRR			(UART0_REG_BASE + 0x88)
#define U0SBCR			(UART0_REG_BASE + 0x90)
#define U0SDMAM			(UART0_REG_BASE + 0x94)
#define U0SFE			(UART0_REG_BASE + 0x98)
#define U0SRT			(UART0_REG_BASE + 0x9c)
#define U0STET			(UART0_REG_BASE + 0xa0)
#define U0HTX			(UART0_REG_BASE + 0xa4)
#define U0DMASA			(UART0_REG_BASE + 0xa8)
#define U0CPR			(UART0_REG_BASE + 0xf4)
#define U0UCV			(UART0_REG_BASE + 0xf8)
#define U0CTR			(UART0_REG_BASE + 0xfc)

/* uart1 */                                   
#define UART1_REG_BASE	0x1801B200	//see misc document

#define U1RBR_THR_DLL	(UART1_REG_BASE + 0x0)
#define U1IER_DLH		(UART1_REG_BASE + 0x4)
#define U1IIR_FCR		(UART1_REG_BASE + 0x8)
#define U1LCR			(UART1_REG_BASE + 0xc)
#define U1MCR			(UART1_REG_BASE + 0x10)
#define U1LSR			(UART1_REG_BASE + 0x14)
#define U1MSR			(UART1_REG_BASE + 0x18)
#define U1SCR			(UART1_REG_BASE + 0x1c)
#define U1SRBR          (UART1_REG_BASE + 0x30)
#define U1FAR			(UART1_REG_BASE + 0x70)
#define U1TFR			(UART1_REG_BASE + 0x74)
#define U1RFW			(UART1_REG_BASE + 0x78)
#define U1USR			(UART1_REG_BASE + 0x7c)
#define U1TFL			(UART1_REG_BASE + 0x80)
#define U1RFL			(UART1_REG_BASE + 0x84)
#define U1SRR			(UART1_REG_BASE + 0x88)
#define U1SBCR			(UART1_REG_BASE + 0x90)
#define U1SDMAM			(UART1_REG_BASE + 0x94)
#define U1SFE			(UART1_REG_BASE + 0x98)
#define U1SRT			(UART1_REG_BASE + 0x9c)
#define U1STET			(UART1_REG_BASE + 0xa0)
#define U1HTX			(UART1_REG_BASE + 0xa4)
#define U1DMASA			(UART1_REG_BASE + 0xa8)
#define U1CPR			(UART1_REG_BASE + 0xf4)
#define U1UCV			(UART1_REG_BASE + 0xf8)
#define U1CTR			(UART1_REG_BASE + 0xfc)


#endif /* #ifndef UART_REG_H */
