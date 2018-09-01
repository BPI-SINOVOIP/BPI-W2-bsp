#ifndef __UART_H_
#define __UART_H_
//#include "typedef.h"
/************************************************************************
 *
 *  uart.h
 *
 *  UART function header for Phoenix internal ROM
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/

/************************************************************************
 *  Definitions
 ************************************************************************/
#define _2_LINE		//# without TDS, RDS pins

#define POLLSIZE 		0x200	// 512
#define HW_LIMIT_STOP	(POLLSIZE-64)  /* RTS OFF when 64 chars in buf */
#define HW_LIMIT_START	(POLLSIZE-32)  /* RTS  ON when 32 chars in buf */
#define SERIAL_MCR_DTR           0x01    /* Data Terminal Ready         */
#define SERIAL_MCR_RTS           0x02    /* Request To Send             */
#define SERIAL_LSR_DR            0x01    /* Character ready             */
#define SERIAL_LSR_OE            0x02    /* Overrun error               */
#define SERIAL_LSR_THRE          0x20    /* Transmit Holding empty      */
#define SERIAL_MSR_CTS           0x10    /* Clear to send               */	//# b218

#define ENABLE_UART_FUNC
#define UART_NEW_STYLE
#define UARTREG_BASE_ADDRESS 				UART0_REG_BASE
#define	UARTINFO_DATA_READY_MASK			0x01

#define	UARTINFO_TEMT_MASK					0x40
#define	UARTINFO_THRE_MASK					0x20
#define UARTINFO_TRANSMITTER_READY_MASK		(UARTINFO_TEMT_MASK | UARTINFO_THRE_MASK)


typedef union _UARTREG_RBR_THR_DLL
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_RBR_THR_DLL (0x1801_B200)
        UINT32  DLL: 8;             		//IO[7:0]: Divisor Latch LSB                                                                                            
        UINT32  Reserved: 24;               //IO[31:8]: Reserved 

    } Fields0;
    
    struct
    {       
                                            //Register: UART_RBR_THR_DLL (0x1801_B200)
        UINT32  RBD: 8;             		//IO[7:0]: Read: Receiver Buffer Data                                                                                            
        UINT32  Reserved: 24;               //IO[31:8]: Reserved 

    } Fields1;
    
    struct
    {       
                                            //Register: UART_RBR_THR_DLL (0x1801_B200)
        UINT32  THD: 8;             		//IO[7:0]: Write: Transmitter Holding Data                                                                                            
        UINT32  Reserved: 24;               //IO[31:8]: Reserved 

    } Fields2;
    
} UARTREG_RBR_THR_DLL;

typedef union _UARTREG_IER_DLM
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_IER_DLH (0x1801_B204)
        UINT32  DLM: 8;             		//IO[7:0]: Divisor Latch MSB                                                                                            
        UINT32  Reserved: 24;               //IO[31:8]: Reserved 
    } Fields0;
    
    struct
    {       
                                            //Register: UART_IER_DLM (0x1800_7804)        	
        UINT32  ERBI: 1;             		//IO[0]: Enable received data available interrupt 	
        UINT32  ETBEI: 1;             		//IO[1]: Enable transmitter holding register empty interrupt 	
        UINT32  ELSI: 1;             		//IO[2]: Enable receiver line status interrupt 	
        UINT32  EDSSI: 1;             		//IO[3]: Enable modem status register interrupt 
        UINT32  Reserved: 28;               //IO[31:4]: Reserved 
	} Fields1;
    
} UARTREG_IER_DLM;

typedef union _UARTREG_IIR_FCR 
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_IIR_FCR (0x1801_B208)
        UINT32  IPND: 1;             		//IO[0]: Interrupt pending
											//		 - 0b = interrupt pending
        UINT32	IID: 3;						//IO[3:1]: IID
        									//		   - 000b: Modem Status Changed
											//		   - 001b: THR empty
											//		   - 010b: Received Data available
											//		   - 011b: Receiver Status
											//		   - 110b: Character Time Out
        UINT32	Reserved0: 2;				//IO[5:4]: Reserved
        UINT32	FIFO16: 2;					//IO[7:6]: FIFO16
											//		   - 00b = no FIFO
											//		   - 11b = 16-byte FIFO
        UINT32  Reserved1: 24;            	//IO[31:8]: Reserved 
    } Fields0;    
    
    struct
    {       
                                            //Register: UART_IIR_FCR (0x1801_B208)
        UINT32  EFIFO: 1;             		//IO[0]: Enable FIFO. 
        									//		 When this bit is set, enable the transmitter 
        									//		 and receiver FIFOs. Changing this bit clears 
        									//		 the FIFOs. 

        UINT32	RFRST: 1;					//IO[1]: Receiver FIFO reset. 
        									//		 Writes 1 to clear the receiver FIFO.                                    
        UINT32	TFRST: 1;					//IO[2]: Transmitter FIFO reset. 
        									//		 Writes 1 to clear the transmitter FIFO.                                    
        UINT32	DMAM: 1;					//IO[3]: DMA mode enable                                    
        UINT32	Reserved0: 2;				//IO[5:4]: Reserved                                   
        UINT32	RTRG: 2;					//IO[7:6]: Receiver trigger level
											//		   Trigger level: 14-byte
											//		   - 00b = 01 Bytes
											//		   - 01b = 04 Bytes
											//		   - 10b = 08 Bytes
											//		   - 11b = 14 Bytes                                    
        UINT32  Reserved1: 24;            	//IO[31:8]: Reserved                                     
    } Fields1;
    
} UARTREG_IIR_FCR;

typedef union _UARTREG_LCR 
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_LCR (0x1801_B20C)
        UINT32  WLS: 2;             		//IO[1:0]: Word length select
											//		   - 00b: 5 bits
											//		   - 01b: 6 bits
											//		   - 10b: 7 bits
											//		   - 11b: 8 bits
        UINT32	STP: 1;						//IO[2]: Number of stop bits
											//		 - 0b: 1 bit
											//		 - 1b: 2 bits
        UINT32	PEN: 1;						//IO[3]: Parity enable
        UINT32	EPS: 2;						//IO[5:4]: Even parity select
											//		   - 00b: odd parity
											//		   - 01b: even parity
											//		   - 10b: mark parity
											//		   - 11b: space parity
        UINT32	BRK: 1;						//IO[6]: Break control. 
											//		 Set this bit force TXD to the spacing (low) state.
											//		 Clear this bit to disable break condition.
        UINT32	DLAB: 1;					//IO[7]: Divisor latch access bit
        UINT32  Reserved: 24;            	//IO[31:8]: Reserved 
    } Fields;    
    
} UARTREG_LCR;

typedef union _UARTREG_MCR 
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_MCR (0x1801_B210)
        UINT32  DTR: 1;             		//IO[0]: Data terminal Ready. 
											//		 - 0b: Set DTR# high
											//		 - 1b: Set DTR# low
        UINT32	RTS: 1;						//IO[1]: Request to send
											//		 - 0b: Set RTS# high
											//		 - 1b: Set RTS# low
        UINT32	Reserved0: 2;				//IO[3:2]: Reserved
        UINT32  Reserved1: 27;            	//IO[31:5]: Reserved 
        UINT32	LOOP: 1;					//IO[4]: Loopback
    } Fields;    
    
} UARTREG_MCR;

typedef union _UARTREG_LSR
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_LSR (0x1801_B214)
        UINT32  DR: 1;             			//IO[0]: Data ready. 
											//		 - Character mode: data ready in RBR
											//		 - FIFO mode: receiver FIFO is not empty

        UINT32	OE: 1;						//IO[1]: Overrun error. 
        									//		 An overrun occurs when the receiver FIFO is 
        									//		 full and the next character is completely received 
        									//		 in the receiver shift register. An OE is indicated. 
        									//		 The character in the shift register will be overwritten
        UINT32	PE: 1;						//IO[2]: Parity error
        UINT32	FE: 1;						//IO[3]: Framing error
        UINT32	BI: 1;						//IO[4]: Break interrupt indicator
        UINT32	THRE: 1;					//IO[5]: Transmitter holding register empty.
											//		 - Character mode: THR is empty.
											//		 - FIFO mode: transmitter FIFO is empty
        UINT32	TEMT: 1;					//IO[6]: Transmitter empty
											//		 - Character mode: both THR and TSR are empty.
											//		 - FIFO mode: both transmitter FIFO and TSR are empty
        UINT32	RFE: 1;						//IO[7]: Errors in receiver FIFO. 
        									//		 At least one parity, framing and break error in the FIFO.
        UINT32  Reserved: 24;            	//IO[31:8]: Reserved 
    } Fields;    
    
} UARTREG_LSR;

typedef union _UARTREG_MSR
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_MSR (0x1801_B218)
        
        UINT32  DCTS: 1;             		//IO[0]: Delta clear to send. 
        									//		 CTS# signal transits.
        UINT32	Reserved0: 3;				//IO[3:1]: Reserved
        UINT32	CTS: 1;						//IO[4]: Clear to send.
											//		 - 0b: CTS# detected high
											//		 - 1b: CTS# detected low
        UINT32	DSR: 1;						//IO[5]: DSR
        									//		 - In loopback mode, returns the bit 0 of MCR
											//		 - In normal mode, returns 1.
        UINT32	RI: 1;						//IO[6]: RI
        									//		 - In loopback mode, returns the bit 3 of MCR.
        									//		 - In normal mode, returns 0.
        UINT32	DCD: 1;						//IO[7]: DCD
        									//		 - In loopback mode, returns the bit 2 of MCR.
        									//		 - In normal mode, returns 1.
        UINT32  Reserved1: 24;            	//IO[31:8]: Reserved 

    } Fields;    
    
} UARTREG_MSR;

typedef union _UARTREG_SCR
{
    UINT32  Value;
    struct
    {       
                                            //Register: UART_SCR (0x1801_B21C)
        UINT32	SCR: 8;						//IO[7:0]: Scratch Register
        UINT32  Reserved: 24;            	//IO[31:8]: Reserved         
    } Fields;    
    
} UARTREG_SCR;

//=================================================================================================
typedef struct _UARTREG
{
	UARTREG_RBR_THR_DLL		UartRbrTheDll;	//0x1800_7800: UART_RBR_THR_DLL
	UARTREG_IER_DLM			UartIerDlm;    	//0x1800_7804: UART_IER_DLM    
	UARTREG_IIR_FCR			UartIirFcr;    	//0x1800_7808: UART_IIR_FCR    
	UARTREG_LCR				UartLcr;       	//0x1800_780C: UART_LCR        
	UARTREG_MCR				UartMcr;       	//0x1800_7810: UART_MCR        
	UARTREG_LSR				UartLsr;       	//0x1800_7814: UART_LSR        
	UARTREG_MSR				UartMsr;       	//0x1800_7818: UART_MSR        
	UARTREG_SCR				UartScr;       	//0x1800_781C: UART_SCR        
	
} UARTREG;

//=================================================================================================


/************************************************************************
 *  Function prototypes
 ************************************************************************/
void init_uart(void);
void set_recovery_uart(void);
void rollback_recovery_uart(void);

void set_focus_uart(int currentUartPort);
int serial_read(unsigned char *ch);
void prints(const char *ch);
void print_val(unsigned int val, unsigned int len);
void print_hex(unsigned int value);
#ifdef ENABLE_UART1_DEBUG
void serial_write_uart1(unsigned char  *p_param);
void prints_uart1(const char *ch);
void print_val_uart1(unsigned int val, unsigned int len);
#endif
//int read_byte(char *ch);
int read_word(int *word, int bEcho);
#ifdef ROM_DEBUG
void hexdump(const char *str, const void *buf, unsigned int length);
#endif

#endif
