/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Defines of the Venus cpu's specific address-MAP, registers, etc.
 *
 * Copyright (C) 2010 by Chien-An Lin <colin@realtek.com.tw>
 */
#ifndef _MACH_VENUS_H
#define _MACH_VENUS_H

//#include <asm/addrspace.h>


/*
 * Yamon Prom print address.
 */
#define YAMON_PROM_PRINT_ADDR		0x1fc00504

//#define VENUS_RESET_ADDR		0xbfc00000

//#define VENUS_IO_PORT_BASE		0xb8000000
#define VENUS_ISO_IO_PORT_BASE		0xFE000000
#define VENUS_MISC_IO_PORT_BASE		0xFE000000
//#define VENUS_0_SYS_DEBUG		0xB80000AC


/*
 * Venus USB registers.
 */
#define VENUS_USB_BASE			0x13000
//Ehci Capability Registers
#define VENUS_USB_EHCI_USBBASE		VENUS_USB_BASE
#define VENUS_USB_EHCI_HCCAPBASE	(VENUS_USB_EHCI_USBBASE+0x00)
#define VENUS_USB_EHCI_HCSPARAMS	(VENUS_USB_EHCI_USBBASE+0x04)
#define VENUS_USB_EHCI_HCCPARAMS	(VENUS_USB_EHCI_USBBASE+0x08)
//Ehci Operational Registers
#define VENUS_USB_EHCI_USBOPBASE	(VENUS_USB_EHCI_USBBASE+0x10)
#define VENUS_USB_EHCI_USBCMD		(VENUS_USB_EHCI_USBOPBASE+0x00)
#define VENUS_USB_EHCI_USBSTS		(VENUS_USB_EHCI_USBOPBASE+0x04)
#define VENUS_USB_EHCI_USBINTR		(VENUS_USB_EHCI_USBOPBASE+0x08)
#define VENUS_USB_EHCI_FRINDEX		(VENUS_USB_EHCI_USBOPBASE+0x0c)
#define VENUS_USB_EHCI_CTRLDSSEGMENT	(VENUS_USB_EHCI_USBOPBASE+0x10)
#define VENUS_USB_EHCI_PERIODICLISTBASE	(VENUS_USB_EHCI_USBOPBASE+0x14)
#define VENUS_USB_EHCI_ASYNCLISTADDR	(VENUS_USB_EHCI_USBOPBASE+0x18)
#define VENUS_USB_EHCI_CONFIGFLAG	(VENUS_USB_EHCI_USBOPBASE+0x40)
#define VENUS_USB_EHCI_PORTSC_0		(VENUS_USB_EHCI_USBOPBASE+0x44)
//Synopsys-Specific Registers
#define VENUS_USB_EHCI_INSNREG00	(VENUS_USB_EHCI_USBOPBASE+0x80)
#define VENUS_USB_EHCI_INSNREG01	(VENUS_USB_EHCI_USBOPBASE+0x84)
#define VENUS_USB_EHCI_INSNREG02	(VENUS_USB_EHCI_USBOPBASE+0x88)
#define VENUS_USB_EHCI_INSNREG03	(VENUS_USB_EHCI_USBOPBASE+0x8c)
#define VENUS_USB_EHCI_INSNREG04	(VENUS_USB_EHCI_USBOPBASE+0x90)
#define VENUS_USB_EHCI_INSNREG05	(VENUS_USB_EHCI_USBOPBASE+0x94)
//Ohci Registers
#define VENUS_USB_OHCI_USBBASE		(VENUS_USB_BASE+0x400)
#define VENUS_USB_OHCI_REVISION		(VENUS_USB_OHCI_USBBASE+0x00)
#define VENUS_USB_OHCI_CONTROL		(VENUS_USB_OHCI_USBBASE+0x04)
#define VENUS_USB_OHCI_COMMAND_STATUS	(VENUS_USB_OHCI_USBBASE+0x08)
#define VENUS_USB_OHCI_INTERRUPT_STATUS	(VENUS_USB_OHCI_USBBASE+0x0c)
#define VENUS_USB_OHCI_INTERRUPT_ENABLE	(VENUS_USB_OHCI_USBBASE+0x10)
#define VENUS_USB_OHCI_INTERRUPT_DISABLE	(VENUS_USB_OHCI_USBBASE+0x14)
#define VENUS_USB_OHCI_HCCA		(VENUS_USB_OHCI_USBBASE+0x18)
#define VENUS_USB_OHCI_PERIOD_CURRENTED	(VENUS_USB_OHCI_USBBASE+0x1c)
#define VENUS_USB_OHCI_CONTROL_HEADED	(VENUS_USB_OHCI_USBBASE+0x20)
#define VENUS_USB_OHCI_CONTROL_CURRENTED	(VENUS_USB_OHCI_USBBASE+0x24)
#define VENUS_USB_OHCI_BULK_HEADED	(VENUS_USB_OHCI_USBBASE+0x28)
#define VENUS_USB_OHCI_BULK_CURRENTED	(VENUS_USB_OHCI_USBBASE+0x2c)
#define VENUS_USB_OHCI_DONE_HEAD	(VENUS_USB_OHCI_USBBASE+0x30)
#define VENUS_USB_OHCI_FM_INTERVAL	(VENUS_USB_OHCI_USBBASE+0x34)
#define VENUS_USB_OHCI_FM_REMAINING	(VENUS_USB_OHCI_USBBASE+0x38)
#define VENUS_USB_OHCI_FM_NUMBER	(VENUS_USB_OHCI_USBBASE+0x3c)
#define VENUS_USB_OHCI_PERIODIC_START	(VENUS_USB_OHCI_USBBASE+0x40)
#define VENUS_USB_OHCI_LS_THRESHOLD	(VENUS_USB_OHCI_USBBASE+0x44)
#define VENUS_USB_OHCI_RH_DESC_A	(VENUS_USB_OHCI_USBBASE+0x48)
#define VENUS_USB_OHCI_RH_DESC_B	(VENUS_USB_OHCI_USBBASE+0x4c)
#define VENUS_USB_OHCI_RH_STATUS	(VENUS_USB_OHCI_USBBASE+0x50)
#define VENUS_USB_OHCI_PORT_STATUS_1	(VENUS_USB_OHCI_USBBASE+0x54)


// USB Host Registers
#define VENUS_USB_HOST_BASE		(VENUS_USB_BASE+0x800)
#define VENUS_USB_HOST_WRAPPER		(VENUS_USB_HOST_BASE+0x00)
#define VENUS_USB_HOST_VSTATUS		(VENUS_USB_HOST_BASE+0x04)
#define VENUS_USB_HOST_USBIP_INPUT	(VENUS_USB_HOST_BASE+0x08)
#define VENUS_USB_HOST_RESET_UTMI	(VENUS_USB_HOST_BASE+0x0c)
#define VENUS_USB_HOST_SELF_LOOP_BACK	(VENUS_USB_HOST_BASE+0x10)


/* Define for Venus Ethernet MAC. */
#define VENUS_ETH_BASE			0xb8016000
#define VENUS_ETH_CR			((volatile unsigned char *)(VENUS_ETH_BASE + 0x3B))
#define VENUS_ETH_IMR			((volatile unsigned short *)(VENUS_ETH_BASE + 0x3C))
#define VENUS_ETH_RCR			((volatile unsigned int *)(VENUS_ETH_BASE + 0x44))
#define VENUS_ETH_MIIAR			((volatile unsigned int *)(VENUS_ETH_BASE + 0x5C))
/*
 * Venus Ethernet Phy registers.
 */
#define VENUS_ETN_MII_AR		0x1605C


/*
 * Venus TV encoder registers.
 */
#define VENUS_TVE_VIDEO_DAC_CTRL0	0x180D0
#define VENUS_TVE_VIDEO_DAC_CTRL1	0x180D4


/*
 * Venus TV decoder registers.
 */
#define VENUS_TVD_VIDEO_ADC_DIGITAL_CTRL0	0x190FC


/*
 * Venus SB2 registers.
 */
#define VENUS_SB2_HD_SEM		0x1A000
#define VENUS_SB2_INV_INTEN		0x1A004
#define VENUS_SB2_INV_INTSTAT		0x1A008
#define VENUS_SB2_INV_ADDR		0x1A00C

#define VENUS_SB2_CHIP_ID		0x1A200
#define VENUS_SB2_CHIP_INFO		0x1A204


/*
 * Software Debug registers
 */
#define SB2_DGB_START_REG0		0x1A458
#define SB2_DGB_START_REG1		0x1A45c
#define SB2_DGB_START_REG2		0x1A460
#define SB2_DGB_START_REG3		0x1A464
#define SB2_DGB_START_REG4		0x1A468
#define SB2_DGB_START_REG5		0x1A46c
#define SB2_DGB_START_REG6		0x1A470
#define SB2_DGB_START_REG7		0x1A474

#define SB2_DGB_END_REG0		0x1A478
#define SB2_DGB_END_REG1		0x1A47c
#define SB2_DGB_END_REG2		0x1A480
#define SB2_DGB_END_REG3		0x1A484
#define SB2_DGB_END_REG4		0x1A488
#define SB2_DGB_END_REG5		0x1A48c
#define SB2_DGB_END_REG6		0x1A490
#define SB2_DGB_END_REG7		0x1A494

#define SB2_DGB_CTRL_REG0		0x1A498
#define SB2_DGB_CTRL_REG1		0x1A49c
#define SB2_DGB_CTRL_REG2		0x1A4a0
#define SB2_DGB_CTRL_REG3		0x1A4a4
#define SB2_DGB_CTRL_REG4		0x1A4a8
#define SB2_DGB_CTRL_REG5		0x1A4ac
#define SB2_DGB_CTRL_REG6		0x1A4b0
#define SB2_DGB_CTRL_REG7		0x1A4b4

#define SB2_DGB_ADDR_ADUIO		0x1A4b8
#define SB2_DGB_ADDR_VIDEO		0x1A4bc
#define SB2_DGB_ADDR_SYSTEM		0x1A4c0

#define SB2_DGB_INT			0x1A4e0


/*
 * Venus MISC registers.
 */

#define VENUS_ISO_ISR			0x7000


#define VENUS_MIS_PSELH			0x1B000
#define VENUS_MIS_PSELL			0x1B004
#define VENUS_MIS_UMSK_ISR		0x1B008
#define VENUS_MIS_ISR			0x1B00C
#define VENUS_MIS_UMSK_ISR_GP0A		0x1B010
#define VENUS_MIS_UMSK_ISR_GP0DA	0x1B014
#define VENUS_MIS_UMSK_ISR_KPADAH	0x1B018
#define VENUS_MIS_UMSK_ISR_KPADAL	0x1B01C
#define VENUS_MIS_UMSK_ISR_KPADDAH	0x1B020
#define VENUS_MIS_UMSK_ISR_KPADDAL	0x1B024
#define VENUS_MIS_UMSK_ISR_SW		0x1B028
#define VENUS_MIS_DBG			0x1B02C
#define VENUS_MIS_DUMMY			0x1B030
#define VENUS_MIS_PSEL2			0x1B034
#define VENUS_MIS_UMSK_ISR_GP1A		0x1B038
#define VENUS_MIS_UMSK_ISR_GP1DA	0x1B03C


/*
 * Venus GPIO registers.
 */
#define VENUS_MIS_GP0DIR		0x1B100
#define VENUS_MIS_GP1DIR		0x1B104
#define VENUS_MIS_GP0DATO		0x1B108
#define VENUS_MIS_GP1DATO		0x1B10C
#define VENUS_MIS_GP0DATI		0x1B110
#define VENUS_MIS_GP1DATI		0x1B114
#define VENUS_MIS_GP0IE			0x1B118
#define VENUS_MIS_GP1IE			0x1B11C
#define VENUS_MIS_GP0DP			0x1B120
#define VENUS_MIS_GP1DP			0x1B124
#define VENUS_MIS_GPDEB			0x1B128



/*
 * Venus UART registers. jjdarwin
 */

#if  defined(CONFIG_REALTEK_MACARTHUR)
 
#define VENUS_MIS_U1RBR_THR_DLL         0x1B100
#define VENUS_MIS_U1IER_DLH             0x1B104
#define VENUS_MIS_U1IIR_FCR             0x1B108
#define VENUS_MIS_U1LCR                 0x1B10C
#define VENUS_MIS_U1MCR                 0x1B110
#define VENUS_MIS_U1LSR                 0x1B114
#define VENUS_MIS_U1MSR                 0x1B118
#define VENUS_MIS_U1SCR                 0x1B11C
 
#define VENUS_MIS_U0RBR_THR_DLL         0x61300
#define VENUS_MIS_U0IER_DLH                 0x61304
#define VENUS_MIS_U0IIR_FCR                  0x61308
#define VENUS_MIS_U0LCR                         0x6130C
#define VENUS_MIS_U0MCR                        0x61310
#define VENUS_MIS_U0LSR                         0x61314
#define VENUS_MIS_U0MSR                        0x61318
#define VENUS_MIS_U0SCR                         0x6131C

#define VENUS_MIS_U3RBR_THR_DLL         0x1B300
#define VENUS_MIS_U3IER_DLH             0x1B304
#define VENUS_MIS_U3IIR_FCR             0x1B308
#define VENUS_MIS_U3LCR                 0x1B30C
#define VENUS_MIS_U3MCR                 0x1B310
#define VENUS_MIS_U3LSR                 0x1B314
#define VENUS_MIS_U3MSR                 0x1B318
#define VENUS_MIS_U3SCR                 0x1B31C
#define VENUS_MIS_U3SRBR                0x1B330
#define VENUS_MIS_U3FAR                 0x1B370
#define VENUS_MIS_U3TFR                 0x1B374
#define VENUS_MIS_U3RFW                 0x1B378
#define VENUS_MIS_U3USR                 0x1B37C
#define VENUS_MIS_U3TFL                 0x1B380
#define VENUS_MIS_U3RFL                 0x1B384
#define VENUS_MIS_U3SRR                 0x1B388
#define VENUS_MIS_U3SBCR                0x1B390
#define VENUS_MIS_U3SDMAM               0x1B394
#define VENUS_MIS_U3SFE                 0x1B398
#define VENUS_MIS_U3SRT                 0x1B39C
#define VENUS_MIS_U3STET                0x1B3A0
#define VENUS_MIS_U3HTX                 0x1B3A4
#define VENUS_MIS_U3DMASA               0x1B3A8
#define VENUS_MIS_U3CPR                 0x1B3F4
#define VENUS_MIS_U3UCV                 0x1B3F8
#define VENUS_MIS_U3CTR                 0x1B3FC

#endif

#if  defined(CONFIG_REALTEK_DARWIN) 
 
#define VENUS_MIS_U0RBR_THR_DLL         0x1B100
#define VENUS_MIS_U0IER_DLH             0x1B104
#define VENUS_MIS_U0IIR_FCR             0x1B108
#define VENUS_MIS_U0LCR                 0x1B10C
#define VENUS_MIS_U0MCR                 0x1B110
#define VENUS_MIS_U0LSR                 0x1B114
#define VENUS_MIS_U0MSR                 0x1B118
#define VENUS_MIS_U0SCR                 0x1B11C
 
#define VENUS_MIS_U1RBR_THR_DLL         0x61300
#define VENUS_MIS_U1IER_DLH                 0x61304
#define VENUS_MIS_U1IIR_FCR                  0x61308
#define VENUS_MIS_U1LCR                         0x6130C
#define VENUS_MIS_U1MCR                        0x61310
#define VENUS_MIS_U1LSR                         0x61314
#define VENUS_MIS_U1MSR                        0x61318
#define VENUS_MIS_U1SCR                         0x6131C
 
#endif

#if  defined(CONFIG_REALTEK_SATURN)

#define VENUS_MIS_U0RBR_THR_DLL		0x7800
#define VENUS_MIS_U0IER_DLH		0x7804
#define VENUS_MIS_U0IIR_FCR		0x7808
#define VENUS_MIS_U0LCR			0x780C
#define VENUS_MIS_U0MCR			0x7810
#define VENUS_MIS_U0LSR			0x7814
#define VENUS_MIS_U0MSR			0x7818
#define VENUS_MIS_U0SCR			0x781C

#define VENUS_MIS_U1RBR_THR_DLL		0x1BC00
#define VENUS_MIS_U1IER_DLH		0x1BC04
#define VENUS_MIS_U1IIR_FCR		0x1BC08
#define VENUS_MIS_U1LCR			0x1BC0C
#define VENUS_MIS_U1MCR			0x1BC10
#define VENUS_MIS_U1LSR			0x1BC14
#define VENUS_MIS_U1MSR			0x1BC18
#define VENUS_MIS_U1SCR			0x1BC1C

#endif

#if  defined(CONFIG_REALTEK_NIKE)

#define VENUS_MIS_U0RBR_THR_DLL		0x7800
#define VENUS_MIS_U0IER_DLH		0x7804
#define VENUS_MIS_U0IIR_FCR		0x7808
#define VENUS_MIS_U0LCR			0x780C
#define VENUS_MIS_U0MCR			0x7810
#define VENUS_MIS_U0LSR			0x7814
#define VENUS_MIS_U0MSR			0x7818
#define VENUS_MIS_U0SCR			0x781C

#define VENUS_MIS_U1RBR_THR_DLL		0x7900
#define VENUS_MIS_U1IER_DLH		0x7904
#define VENUS_MIS_U1IIR_FCR		0x7908
#define VENUS_MIS_U1LCR			0x790C
#define VENUS_MIS_U1MCR			0x7910
#define VENUS_MIS_U1LSR			0x7914
#define VENUS_MIS_U1MSR			0x7918
#define VENUS_MIS_U1SCR			0x791C

#endif

// for Chip before Saturn
#ifndef VENUS_MIS_U0RBR_THR_DLL
#define VENUS_MIS_U0RBR_THR_DLL         0x1B200
#define VENUS_MIS_U0IER_DLH             0x1B204
#define VENUS_MIS_U0IIR_FCR             0x1B208
#define VENUS_MIS_U0LCR                 0x1B20C
#define VENUS_MIS_U0MCR                 0x1B210
#define VENUS_MIS_U0LSR                 0x1B214
#define VENUS_MIS_U0MSR                 0x1B218
#define VENUS_MIS_U0SCR                 0x1B21C
 
#define VENUS_MIS_U1RBR_THR_DLL         0x1B220
#define VENUS_MIS_U1IER_DLH             0x1B224
#define VENUS_MIS_U1IIR_FCR             0x1B228
#define VENUS_MIS_U1LCR                 0x1B22C
#define VENUS_MIS_U1MCR                 0x1B230
#define VENUS_MIS_U1LSR                 0x1B234
#define VENUS_MIS_U1MSR                 0x1B238
#define VENUS_MIS_U1SCR                 0x1B23C

#endif


#define VENUS_UART0_CLK			27000000
#define VENUS_UART1_CLK			432000000

/*
 * Venus IrDA registers.
 */
#define VENUS_MIS_IR_PSR		0x1B400
#define VENUS_MIS_IR_PRE		0x1B404
#define VENUS_MIS_IR_SF			0x1B408
#define VENUS_MIS_IR_DPIR		0x1B40C
#define VENUS_MIS_IR_CR			0x1B410
#define VENUS_MIS_IR_RP			0x1B414
#define VENUS_MIS_IR_SR			0x1B418


/*
 * Venus external timer registers.jjdarwin
 */
#if  defined(CONFIG_REALTEK_DARWIN) || defined(CONFIG_REALTEK_MACARTHUR)
#define VENUS_MIS_TC0TVR		0x1B600
#define VENUS_MIS_TC1TVR		0x1B604
#define VENUS_MIS_TC2TVR		0x1B608//0x1B618//0x1B608 use TC6
#define VENUS_MIS_TC6TVR		0x1B618
#define VENUS_MIS_TC0CVR		0x1B620
#define VENUS_MIS_TC1CVR		0x1B624
#define VENUS_MIS_TC2CVR		0x1B628//0x1B638//0x1B628 use TC6
#define VENUS_MIS_TC6CVR		0x1B638
#define VENUS_MIS_TC0CR			0x1B640
#define VENUS_MIS_TC1CR			0x1B644
#define VENUS_MIS_TC2CR			0x1B648//0x1B658//0x1B648 use TC6
#define VENUS_MIS_TC6CR			0x1B658
#define VENUS_MIS_TC0ICR		0x1B660
#define VENUS_MIS_TC1ICR		0x1B664
#define VENUS_MIS_TC2ICR		0x1B668//0x1B678//0x1B668 use TC6
#define VENUS_MIS_TC6ICR		0x1B678
#define VENUS_MIS_TCWCR			0x1BB00
#define VENUS_MIS_TCWTR			0x1BB04
#define VENUS_MIS_TCWOV			0x1BB0C
#define VENUS_MIS_CLK27M_CLK90K_CNT	0x1B688
#define VENUS_MIS_CLK90K_TM_LO		0x1B690
#define VENUS_MIS_CLK90K_TM_HI		0x1B694

#else

#define VENUS_MIS_TC0TVR                0x1B500
#define VENUS_MIS_TC1TVR                0x1B504
#define VENUS_MIS_TC2TVR                0x1B508
#define VENUS_MIS_TC0CVR                0x1B50C
#define VENUS_MIS_TC1CVR                0x1B510
#define VENUS_MIS_TC2CVR                0x1B514
#define VENUS_MIS_TC0CR                 0x1B518
#define VENUS_MIS_TC1CR                 0x1B51C
#define VENUS_MIS_TC2CR                 0x1B520
#define VENUS_MIS_TC0ICR                0x1B524
#define VENUS_MIS_TC1ICR                0x1B528
#define VENUS_MIS_TC2ICR                0x1B52C
#if  defined(CONFIG_REALTEK_SATURN) || defined(CONFIG_REALTEK_NIKE)
#define VENUS_MIS_TCWCR                 0x1B5B0
#define VENUS_MIS_TCWTR                 0x1B5B4
#define VENUS_MIS_TCWOV                 0x1B5BC
#else
#define VENUS_MIS_TCWCR                 0x1B530
#define VENUS_MIS_TCWTR                 0x1B534
#endif
#define VENUS_MIS_CLK27M_CLK90K_CNT     0x1B538
#define VENUS_MIS_CLK90K_TM_LO          0x1B53C
#define VENUS_MIS_CLK90K_TM_HI          0x1B540

#endif



/*
 * Venus RTC registers.
 */
#define VENUS_MIS_RTCSEC		0x1B600
#define VENUS_MIS_RTCMIN		0x1B604
#define VENUS_MIS_RTCHR			0x1B608
#define VENUS_MIS_RTCDATE1		0x1B60C
#define VENUS_MIS_RTCDATE2		0x1B610
#define VENUS_MIS_ALMMIN		0x1B614
#define VENUS_MIS_ALMHR			0x1B618
#define VENUS_MIS_ALMDATE1		0x1B61C
#define VENUS_MIS_ALMDATE2		0x1B620
#define VENUS_MIS_RTCSTOP		0x1B624
#define VENUS_MIS_RTCACR		0x1B628
#define VENUS_MIS_RTCEN			0x1B62C
#define VENUS_MIS_RTCCR			0x1B630


/*
 * Venus VFD registers.
 */
#define VENUS_MIS_VFD_CTL		0x1B700
#define VENUS_MIS_VFD_WRCTL		0x1B704
#define VENUS_MIS_VFDO			0x1B708
#define VENUS_MIS_VFD_ARDCTL 		0x1B70C
#define VENUS_MIS_VFD_KPADLIE		0x1B710
#define VENUS_MIS_VFD_KPADHIE		0x1B714
#define VENUS_MIS_VFD_SWIE		0x1B718
#define VENUS_MIS_VFD_ARDKPADL		0x1B71C
#define VENUS_MIS_VFD_ARDKPADH		0x1B720
#define VENUS_MIS_VFD_ARDSW		0x1B724


/*
 * Defines for the Venus interrupt controller.
 */
#define VENUS_INT_BASE			2
#define VENUS_INT_USB			(VENUS_INT_BASE+0)
#define VENUS_INT_ETH			(VENUS_INT_BASE+0)

#define VENUS_INT_CP			(VENUS_INT_BASE+1)

#define VENUS_INT_1394			(VENUS_INT_BASE+2)
#define VENUS_INT_ATA			(VENUS_INT_BASE+2)
#define VENUS_INT_NAND			(VENUS_INT_BASE+2)

#define VENUS_INT_AUDIO_RISC		(VENUS_INT_BASE+3)
#define VENUS_INT_VIDEO_RISC		(VENUS_INT_BASE+3)
#define VENUS_INT_SB2			(VENUS_INT_BASE+3)
#define VENUS_INT_SE			(VENUS_INT_BASE+3)
#define VENUS_INT_PERFORMANCE_COUNTER	(VENUS_INT_BASE+3)	// 24K has this; 4KEC doesn't

#define VENUS_INT_EXTERNAL_TIMER	(VENUS_INT_BASE+4)//1)//4) //jjdarwin

#define VENUS_INT_TIMER			(VENUS_INT_BASE+5)
#define VENUS_INT_RTC			(VENUS_INT_BASE+5)


#define REG_CLOCK_ENABLE1				(0xb800000c)
#define REG_MUXPAD7							(0xb800036c)
#define REG_NF_CKSEL						(0xb8000034)
#define REG_DDR_BASE_ADDR				(0x80000000)
#define REG_NF_BASE_ADDR				(0xb8010000)
#define REG_ND_PA0							( REG_NF_BASE_ADDR + 0 ) 		//Page address 0 [7:0]
#define	REG_ND_PA1							( REG_NF_BASE_ADDR + 0x4 )		//Page address 1 [15:8]
#define	REG_ND_PA2							( REG_NF_BASE_ADDR + 0x8 )		//Page address 2 [20:16]
#define	REG_ND_CA0				  		( REG_NF_BASE_ADDR + 0xc )		//Column address 0 [7:0]
#define	REG_ND_CMD							( REG_NF_BASE_ADDR + 0x10 )		//Command [7:0]
#define	REG_ND_DAT							( REG_NF_BASE_ADDR + 0x14 )		//NAND Data[7:0](Status_0)
#define	REG_ND_CTL							( REG_NF_BASE_ADDR + 0x18 )		//NAND control register
#define	REG_CMD3								( REG_NF_BASE_ADDR + 0x28 )		//CMD3 is the third command that would be transfer out by auto mode case 0/1/2
#define	REG_ND_PA3							( REG_NF_BASE_ADDR + 0x2c )		//Page address 3 [23:21]
#define REG_POLL_FSTS						( REG_NF_BASE_ADDR + 0x30 )		//Polling nand flash status
#define REG_BLANK_CHK						( REG_NF_BASE_ADDR + 0x34 )		//Enable blank check function
#define REG_ND_ECC							( REG_NF_BASE_ADDR + 0x38 )		//Indicate ECC status
#define	REG_ND_CA1							( REG_NF_BASE_ADDR + 0x3c )		//Column address [15:8]
#define	REG_DATA_TL0						( REG_NF_BASE_ADDR + 0x100 )	//Data transfer count [7:0]...
#define	REG_DATA_TL1						( REG_NF_BASE_ADDR + 0x104 )	//Data transfer count [13:8]...
#define REG_DMA1_CTL						( REG_NF_BASE_ADDR + 0x10c )	//DMA1 control register
#define REG_PP_CTL0							( REG_NF_BASE_ADDR + 0x110 )	//Ping-Pong buffer control register
#define REG_ECC_SEL							( REG_NF_BASE_ADDR + 0x128 )
#define REG_PP_CTL1							( REG_NF_BASE_ADDR + 0x12c )	//PP starting address [7:0], this filedspecifies the starting address of the Ping-Pong buffer to put the data
#define	REG_PD									( REG_NF_BASE_ADDR + 0x130 )	//PDx. Flash Chip Enable Output
#define REG_DUMMY_NF1						( REG_NF_BASE_ADDR + 0x158 )	//NF clock dummy bit
#define REG_DUMMY_NF2						( REG_NF_BASE_ADDR + 0x15c )	//NF clock dummy bit
#define REG_DUMMY_NF3						( REG_NF_BASE_ADDR + 0x160 )	//NF clock dummy bit
#define REG_DUMMY_NF4						( REG_NF_BASE_ADDR + 0x164 )	//NF clock dummy bit
#define REG_AUTO_TRIG						( REG_NF_BASE_ADDR + 0x200 )	//Auto trigger register control
#define REG_RSECC_NUM						( REG_NF_BASE_ADDR + 0x204 )	//ECC_NUM RS ECC error symbol count.
#define REG_READ_BY_PP					( REG_NF_BASE_ADDR + 0x228 )	//Setting data read to DRAM from NAND through by PP or not
#define REG_MAX_ECC_NUM					( REG_NF_BASE_ADDR + 0x22c )	//Auto mode(Mode 000) read status 
#define REG_TIME_PARA3					( REG_NF_BASE_ADDR + 0x234 )	//NAND flash AC timming setting
#define REG_TIME_PARA2					( REG_NF_BASE_ADDR + 0x238 )	//NAND flash AC timming setting
#define REG_TIME_PARA1					( REG_NF_BASE_ADDR + 0x23c )	//NAND flash AC timming setting
#define REG_PIN_MUX_STOP				( REG_NF_BASE_ADDR + 0x25c )	//Enable Pin_Mux_Stop function
#define REG_DELAY_CTL						( REG_NF_BASE_ADDR + 0x260 )    //Flash timing delay clock number control
#define	REG_ECC_STOP						( REG_NF_BASE_ADDR + 0x264 )	//Data read from NAND to SRAM don't stop transfer when ECC error occurs 
#define	REG_ECC_PAGE						( REG_NF_BASE_ADDR + 0x268 )	//Used in data reading from NAND flash to TBRAM, and ECC_N_STOP was set.
#define	REG_PAGE_CNT						( REG_NF_BASE_ADDR + 0x26c )	//Data page count that had been transferred.
#define	REG_PAGE_LEN						( REG_NF_BASE_ADDR + 0x270 )	//Set the data length would be transferred by auto mode.
#define	REG_CMD2								( REG_NF_BASE_ADDR + 0x274 )	//This is the secone command that would be transfer out by auto mode case 0/1/2.
#define	REG_MULTI_CHNL_MODE			( REG_NF_BASE_ADDR + 0x27c )	//Multi-channel control register
#define REG_SRAM_CTL						( REG_NF_BASE_ADDR + 0x300 )	//SRAM control register
#define	REG_DMA_CTL1						( REG_NF_BASE_ADDR + 0x304 )	//DRAM start address for DMA transfer.
#define	REG_DMA_CTL2						( REG_NF_BASE_ADDR + 0x308 )    //Transfer length for DMA transfer between DMA buffer and DDR.(512B Unit)
#define	REG_DMA_CTL3						( REG_NF_BASE_ADDR + 0x30c )	//Set to control data transfer between DRAM and DMA buffer.
#define	REG_NAND_ISR						( REG_NF_BASE_ADDR + 0x324 )	//NAND ISR status register
#define	REG_NAND_ISREN					( REG_NF_BASE_ADDR + 0x328 )	//NAND ISR enable register
#define	REG_DUMMY_SYS						( REG_NF_BASE_ADDR + 0x32c )	//Dummy
#define	REG_DBG									( REG_NF_BASE_ADDR + 0x344 )	
#define	REG_SPR_DDR_CTL					( REG_NF_BASE_ADDR + 0x348 )	
#define	REG_CP_LEN							( REG_NF_BASE_ADDR + 0x34C )	



/*
 * Defines for the CP.
 */
#define REG_CP_BASE_ADDR				(0xb8015000)
#define REG_MCP_CTRL					(REG_CP_BASE_ADDR+0x100)
#define REG_MCP_STATUS					(REG_CP_BASE_ADDR+0x104)
#define REG_MCP_EN						(REG_CP_BASE_ADDR+0x108)
#define REG_MCP_CTRL1					(REG_CP_BASE_ADDR+0x198)
#define REG_MCP_BASE					(REG_CP_BASE_ADDR+0x10C)
#define REG_MCP_LIMIT					(REG_CP_BASE_ADDR+0x110)
#define REG_MCP_RDPTR					(REG_CP_BASE_ADDR+0x114)
#define REG_MCP_WRPTR					(REG_CP_BASE_ADDR+0x118)
#define REG_MCP_DES_COUNT				(REG_CP_BASE_ADDR+0x134)
#define REG_MCP_DES_COMPARE				(REG_CP_BASE_ADDR+0x138)
#define REG_MCP_DES_INI_KEY				(REG_CP_BASE_ADDR+0x11C)
#define REG_MCP_AES_INI_KEY				(REG_CP_BASE_ADDR+0x124)
#define REG_MCP_MULTI2_SYS_KEY			(REG_CP_BASE_ADDR+0x178)
#define REG_OTP_LOAD					(REG_CP_BASE_ADDR+0x19C)
#define REG_K_MCP_CTRL					(REG_CP_BASE_ADDR+0x900)
#define REG_K_MCP_STATUS				(REG_CP_BASE_ADDR+0x904)
#define REG_K_MCP_EN					(REG_CP_BASE_ADDR+0x908)
#define REG_K_MCP_CTRL1					(REG_CP_BASE_ADDR+0x998)
#define REG_K_MCP_BASE					(REG_CP_BASE_ADDR+0x90C)
#define REG_K_MCP_LIMIT					(REG_CP_BASE_ADDR+0x910)
#define REG_K_MCP_RDPTR					(REG_CP_BASE_ADDR+0x914)
#define REG_K_MCP_WRPTR					(REG_CP_BASE_ADDR+0x918)
#define REG_K_MCP_DES_COUNT				(REG_CP_BASE_ADDR+0x934)
#define REG_K_MCP_DES_COMPARE			(REG_CP_BASE_ADDR+0x938)
#define REG_K_MCP_DES_INI_KEY			(REG_CP_BASE_ADDR+0x91C)
#define REG_K_MCP_AES_INI_KEY			(REG_CP_BASE_ADDR+0x924)
#define REG_K_MCP_MULTI2_SYS_KEY		(REG_CP_BASE_ADDR+0x978)
#define REG_CP_REG_KEY					(REG_CP_BASE_ADDR+0x034)
#define REG_CP_REG_DATAIN				(REG_CP_BASE_ADDR+0x044)	
#define REG_CP_REG_DATAOUT				(REG_CP_BASE_ADDR+0x054)
#define REG_CP_REG_IV					(REG_CP_BASE_ADDR+0x064)
#define REG_CP_REG_SET					(REG_CP_BASE_ADDR+0x074)
#define REG_CP_REG_SET1					(REG_CP_BASE_ADDR+0x078)
#define REG_CP_REG_SET2					(REG_CP_BASE_ADDR+0x07C)
#define REG_TP_KEY_INFO					(0xB8014058)
#define REG_TP_KEY_CTRL					(0xB8014060)
#define REG_CP_SCTCH					(REG_CP_BASE_ADDR+0x080)
#define REG_CP_NF_KEY					(REG_CP_BASE_ADDR+0x084)
#define REG_CP_NF_INI_KEY				(REG_CP_BASE_ADDR+0x094)
#define REG_CP_NF_SET					(REG_CP_BASE_ADDR+0x0A4)
#define REG_CP_MD_KEY					(REG_CP_BASE_ADDR+0x0A8)
#define REG_CP_MD_INI_KEY				(REG_CP_BASE_ADDR+0x0B8)
#define REG_CP_MD_SET					(REG_CP_BASE_ADDR+0x0C8)
#define REG_K_CP_REG_KEY				(REG_CP_BASE_ADDR+0x834)
#define REG_K_CP_REG_DATAIN				(REG_CP_BASE_ADDR+0x844)
#define REG_K_CP_REG_DATAOUT			(REG_CP_BASE_ADDR+0x854)
#define REG_K_CP_REG_IV					(REG_CP_BASE_ADDR+0x864)
#define REG_K_CP_REG_SET				(REG_CP_BASE_ADDR+0x874)
#define REG_K_CP_REG_SET1				(REG_CP_BASE_ADDR+0x878)
#define REG_K_CP_REG_SET2				(REG_CP_BASE_ADDR+0x87C)
#define REG_CP_DBG						(REG_CP_BASE_ADDR+0x0CC)
#define REG_MCP_ST						(REG_CP_BASE_ADDR+0x1A0)

#define __sleep __attribute__ ((__section__ (".sleep.text")))
#define __sleepdata __attribute__ ((__section__ (".sleep.data")))

#endif /* !(_MACH_VENUS_H) */
