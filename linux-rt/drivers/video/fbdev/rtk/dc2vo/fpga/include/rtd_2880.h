
/*=============================================================
 * Copyright C        Realtek Semiconductor Corporation, 2004 *
 * All rights reserved.                                       *
 *============================================================*/

/*======================= Description ========================*/
/**
 * @file
 *   This header file for RTD2880's registers define.
 * @Author Moya
 * @date 2003/05/07
 * @version { 1.0 }
 *
 */

/*======================= CVS Headers =========================
  $Header: /cvsroot/dtv/include/rtd_2880.h,v 1.46 2005/12/20 15:09:38 andy Exp $

  $Log: rtd_2880.h,v $
  Revision 1.46  2005/12/20 15:09:38  andy
  *: Enable ROS UART output for default setup

  Revision 1.45  2005/12/14 02:53:11  andy
  +: add UART disable for ROS platform

  Revision 1.44  2005/11/03 02:03:46  ray
  add error recovery function

  Revision 1.43  2005/10/28 09:33:45  ghyu
  +: Add AVCPUMBCR define.

  Revision 1.42  2005/10/26 06:55:00  frankcheng
  add pcmaia reset pin

  Revision 1.41  2005/10/26 06:53:41  frankcheng
  add pcmaia reset pin

  Revision 1.40  2005/10/25 06:59:51  ycchen
  +: add PC_HW_RESET1 and PC_HW_RESET2 definition

  Revision 1.39  2005/04/06 02:26:13  ghyu
  +: Remark definition of RTD2880_NEW.

  Revision 1.38  2005/03/23 01:53:55  andy
  *: restore MVD IRQ control field definition

  Revision 1.37  2005/03/22 14:07:15  andy
  *: update MVD IRQ

  Revision 1.36  2005/03/22 12:11:11  andy
  *: update for Dual OS & new HW Timer

  Revision 1.35  2005/03/17 01:12:21  temin
  +: Add IH-specific interrupt enable/pending bits

  Revision 1.34  2005/03/07 05:41:20  yoda
  +: add lcd control interface definition

  Revision 1.33  2005/01/19 06:47:04  andy
  +: support New HW timer, ROS run on system RISC

  Revision 1.32  2005/01/14 10:04:47  ghyu
  *: Redefine CCICR1 for new FPGA.

  Revision 1.31  2005/01/06 01:15:42  ghyu
  +: Add memory control registers.

  Revision 1.30  2005/01/03 06:54:59  yoda
  modify gpio definition

  Revision 1.29  2004/12/24 08:48:39  yoda
  *: for pwm definition

  Revision 1.28  2004/12/24 08:42:38  yoda
  *:add something

  Revision 1.27  2004/12/24 08:39:34  yoda
  +: add mux control definition

  Revision 1.26  2004/12/24 07:18:26  ghyu
  +: Add WDTEST_EN definition.

  Revision 1.25  2004/12/22 08:07:37  yoda
  *: modify gpio definition

  Revision 1.24  2004/12/13 02:45:01  timhuang
  +:  Dispaly engine interrupt control field definitions

  Revision 1.23  2004/12/08 11:57:46  ghyu
  +: Add _SYSTEM_RISC and _RTD2880_NEW for new FPGA board.

  Revision 1.22  2004/12/07 10:25:21  yoda
  *:resolve conflict

  Revision 1.21  2004/12/07 09:01:47  ghyu
  +: Resolve conflict.

  Revision 1.20  2004/12/07 08:52:12  ghyu
  +: Add PCMCIA register.

  Revision 1.16  2004/11/26 07:03:18  tzungder
  +add definitions for PLL

  Revision 1.15  2004/11/12 09:56:53  ghyu
  +: PCMCIA's definition.

  Revision 1.14  2004/11/10 03:25:37  ghyu
  +: PCMCIA declaration.

  Revision 1.13  2004/11/02 08:42:59  ghyu
  +: Slave definition.

  Revision 1.12  2004/10/27 03:20:01  tzungder
  refine rtd_types.h definitions and apply to all

  Revision 1.11  2004/10/26 05:17:48  ghyu
  +: I2C slave regiesters.

  Revision 1.10  2004/10/15 11:06:20  ghyu
  +: Add I2C slave registers define.

  Revision 1.9  2004/10/14 12:11:00  ghyu
  :+ Add definition for I2C module.

  Revision 1.8  2004/10/05 15:04:06  tzungder
  flash ROS and boot OK

  Revision 1.7  2004/08/27 09:04:59  yoda
  add pwm definition

  Revision 1.6  2004/08/20 02:16:07  yoda
  add gpio definition

  Revision 1.5  2004/08/16 05:19:59  ghyu
  *** empty log message ***

  Revision 1.4  2004/08/11 06:20:44  ghyu
  	Add definition for ICR.

  Revision 1.3  2004/08/09 04:24:53  tzungder
  add defines for NIC

  Revision 1.2  2004/08/06 05:05:43  ghyu
  	Add interrupt registration and release function.

  Revision 1.1  2004/08/05 08:29:05  ghyu
  	This file for RTD2880 register declare.

  Revision 1.1  2004/07/19 07:33:47  ghyu
  Boot loader draw up.

 *=============================================================*/

#ifndef _RTD2880_H

#define _RTD2880_H

//#define UART_DISABLE_FOR_ROS_PLATFORM		// Disable UART for GDB server -- hyc 2005-12-13
#ifdef CONFIG_UART_FOR_ROS
  #warning "WARNING: ROS NO UART SUPPORT!!"
#endif

#ifdef CONFIG_SYS_14500
#define CPU_CLOCK		(14500*1000)
#endif

#ifdef CONFIG_SYS_27000
#define CPU_CLOCK		(27000*1000)
#endif

#ifdef CONFIG_SYS_162000
#define CPU_CLOCK		(162000*1000)
#endif

#ifdef CONFIG_SYS_189000
#define CPU_CLOCK       (189000*1000)
#endif

#ifdef CONFIG_SYS_202000
#define CPU_CLOCK       (202000*1000)
#endif


#ifndef CPU_CLOCK
#define CPU_CLOCK		(27000*1000)
#endif


#define BIT(x)	(1 << (x))

#define UART0_BASE                          0xBD021000
#define UART1_BASE                          0xBD021100

#define rtd_inb(offset)		(*(volatile unsigned char *)( offset))
#define rtd_inw(offset)	(*(volatile unsigned short *)(offset))
#define rtd_inl(offset)		(*(volatile unsigned long *)(offset))

#define rtd_outb(offset,val)	(*(volatile unsigned char *)(offset) = val)
#define rtd_outw(offset,val)	(*(volatile unsigned short *)(offset) = val)
#define rtd_outl(offset,val)		(*(volatile unsigned long *)(offset) = val)

/// ****************************

//For Memory Controller
#if 0
#define MC_BASE			0xbd010004
#define MCMCR			(0x00 + MC_BASE) /*Memory Control Register*/
#define MCDTCRVB			(0x04 + MC_BASE) /*DDR-RAM Timing Control Register - Video Bank*/
#define MCDTCRSB			(0x08 + MC_BASE) /*DDR-RAM Timing Control Register - System Bank*/
#define MCDICR0VB		(0x0C + MC_BASE) /*DDR-RAM Internal Control Register0 - Video Bank*/
#define MCDICR1VB		(0x10 + MC_BASE) /*DDR-RAM Internal Control Register1 - Video Bank*/
#define MCDICR0SB		(0x14 + MC_BASE) /*DDR-RAM Internal Control Register0 - System Bank*/
#define MCDICR1SB		(0x18 + MC_BASE) /*DDR-RAM Internal Control Register1 - System Bank*/
#define MCRTCR			(0x1C + MC_BASE) /*ROM Timing Control Register*/
#define MCFSR				(0x20 + MC_BASE) /*Flash Status Register*/
#endif


#ifdef _RTD2880_NEW
#define VBMC_BASE	0xbd010000
#define MCMCRVB	(VBMC_BASE + 0x00)     // Memory Control Register - Video Bank
#define MCDTCRVB	(VBMC_BASE + 0x04)     // DDR-RAM Timing Control Register - Video Bank
#define MCDICR0VB	(VBMC_BASE + 0x08)     // DDR-RAM Internal Control Register 0 - Video Bank
#define MCDICR1VB 	(VBMC_BASE + 0x0c)     // DDR-RAM Internal Control Register 1 - Video Bank
#define MCVBACR1     	(VBMC_BASE + 0x10)     // Video Bus Arbitration Control Register 1
#define DLLCRVB     	(VBMC_BASE + 0x14)     // DLL Control Register - Video Bank
#define MCVBAMR1     (VBMC_BASE + 0x18)     // Video Bus Arbitration Monitor Register 1
#define MCVBAMR2     (VBMC_BASE + 0x1c)     // Video Bus Arbitration Monitor Register 2
#define MCVBCRCCR   (VBMC_BASE + 0x20)     // Video Bus CRC Control Register
#define MCVBCRCOR   (VBMC_BASE + 0x24)     // Video Bus CRC Output Register
#define MCVDMBCR    	(VBMC_BASE + 0x28)     // Video-DDR Controller Memory BIST Control Register
#define MCVDMBSR    	(VBMC_BASE + 0x2c)     // Video-DDR Controller Memory BIST Status Register
#define MCDBPRVB    	(VBMC_BASE + 0x30)     // DDR-RAM Best Phase Register - Video Bank

#define LBMC_BASE	0xbd010100
#define MCMCRSB      	(LBMC_BASE + 0x00)     // Memory Control Register - System Bank
#define MCDTCRSB     (LBMC_BASE + 0x04)     // DDR-RAM Timing Control Register - System Bank
#define MCDICR0SB    (LBMC_BASE + 0x08)     // DDR-RAM Internal Control Register 0 - System Bank
#define MCDICR1SB    (LBMC_BASE + 0x0c)     // DDR-RAM Internal Control Register 1 - System Bank
#define MCLBTCR        (LBMC_BASE + 0x10)     // Lexra Bus Timeout Control Register
#define MCLBTSR        (LBMC_BASE + 0x14)     // Lexra Bus Timeout Status Register
#define MCLBACR1      (LBMC_BASE + 0x18)     // Lexra Bus Arbitration Control Register 1
#define MCLBACR2   	(LBMC_BASE + 0x1c)     // Lexra Bus Arbitration Control Register 2
#define MCLBACR3      (LBMC_BASE + 0x20)     // Lexra Bus Arbitration Control Register 3
#define MCLBAMR1     (LBMC_BASE + 0x24)     // Lexra Bus Arbitration Monitor Register 1
#define MCLBAMR2     (LBMC_BASE + 0x28)     // Lexra Bus Arbitration Monitor Register 2
#define MCLBAMR3     (LBMC_BASE + 0x2c)     // Lexra Bus Arbitration Monitor Register 3
#define MCLBCRCCR   (LBMC_BASE + 0x30)     // Lexra Bus CRC Control Register
#define MCLBCRCOR   (LBMC_BASE + 0x34)     // Lexra Bus CRC Output Register
#define MCDBPRSB     (LBMC_BASE + 0x38)     // DDR-RAM Best Phase Register - System Bank
#define MCBBCR         (LBMC_BASE + 0x3c)     // Bus Bridge Control Register
#define MCBBMBCR     (LBMC_BASE + 0x40)     // Bus Bridge Memory BIST Control Register
#define MCBBMBSR     (LBMC_BASE + 0x44)     // Bus Bridge Memory BIST Status Register
#define DLLCRSB         (LBMC_BASE + 0x48)     // DLL Control Register - System Bank


// For Video Bus Arbitration Control Register 1 (SCIU_MCVBACR1)
/*#define VBMPCS		  ((UINT32)1 << 31)
#define VBMVDMPC 	24
#define VBDPMPC		16
#define VBLB2VBBMPC	8
#define VBDDRCMPC	0


// For Lexra Bus Arbitration Control Register (SCIU_MCLBACR)
#define LBMPCS		((UINT32)1 << 31)
#define LBMCPUMPC	24
#define LBAVCPUMPC	16
#define LBNANDMPC	8
#define LBAVDMAMPC	0
#define LBDPMPC		24
#define LBMVDMPC	16
#define LBTPMPC		8
#define LBAIMPC		0
#define LBPCIMPC	0*/


#endif

// For Video Bus Arbitration Control Register 1 (SCIU_MCVBACR1)
#define VBMPCS		  ((UINT32)1 << 31)
#define VBMVDMPC 	24
#define VBDPMPC		16
#define VBLB2VBBMPC	8
#define VBDDRCMPC	0


// For Lexra Bus Arbitration Control Register (SCIU_MCLBACR)
#define LBMPCS		((UINT32)1 << 31)
#define LBMCPUMPC	24
#define LBAVCPUMPC	16
#define LBNANDMPC	8
#define LBAVDMAMPC	0
#define LBDPMPC		24
#define LBMVDMPC	16
#define LBTPMPC		8
#define LBAIMPC		0
#define LBPCIMPC	0

#define MC_BASE      	0xBD010000
// For Flash
#define MCRTCR		(MC_BASE + 0x04)  // ROM Timing Control Register
#define MCFSR		(MC_BASE + 0x24) // Flash Status Register



#define AVCPUMBCR  	MC_BASE+0x1130
#define AVCPUMBSR  	MC_BASE+0x1134
#define AVCPUDMAMBCR  	MC_BASE+0x1150
#define AVCPUDMAMBSR  	MC_BASE+0x1154
// For BUS_MASTER

#ifndef _LINUX_CONFIG_H

#define UART_RBR    0x00    //Chuck add this for bootcode on 20060109
#define UART_THR	0x00
#define UART_DLL	0x00
#define UART_DLM	0x04
#define UART_FCR	0x08
#define UART_LCR	0x0C
#define UART_MCR	0x10
#define UART_LSR	0x14	//Chuck add this for bootcode on 20060109
#define UART_MSR	0x18
#define UART_SCR	0x1C

#endif

/* Global interrupt control registers */

#define GICR_BASE                           0xBD011000

#ifdef _SYSTEM_RISC
#define GICR                                (0x010 + GICR_BASE)       /* Global interrupt mask */
#define GISR                                (0x014 + GICR_BASE)       /* Global interrupt status */
#define IRR0R0                              (0x018 + GICR_BASE)       /* Interrupt routing 0 - RISC 0 */
#define IRR1R0                              (0x01C + GICR_BASE)       /* Interrupt routing 1 - RISC 0 */
#define GISR1                                (0x004 + GICR_BASE)       /* Global interrupt status */
#define CCICR1                              (0x020 + GICR_BASE)       /* CPU Communication Interrupt Control Register - RISC 0 */
#define CCICR0                              (0x024 + GICR_BASE)       /* CPU Communication Interrupt Control Register - RISC 1 */
#define CNL_UART 	UART0_BASE //tdl for dual CPU booting test
#define GDB_UART 	UART0_BASE
#else
#define GICR                                (0x000 + GICR_BASE)       /* Global interrupt mask */
#define GISR                                (0x004 + GICR_BASE)       /* Global interrupt status */
#define IRR0R0                              (0x008 + GICR_BASE)       /* Interrupt routing 0 - RISC 0 */
#define IRR1R0                              (0x00C + GICR_BASE)       /* Interrupt routing 1 - RISC 0 */
#define GISR1                                (0x014 + GICR_BASE)       /* Global interrupt status */
#define CCICR0                              (0x020 + GICR_BASE)       /* CPU Communication Interrupt Control Register - RISC 0 */
#define CCICR1                              (0x024 + GICR_BASE)       /* CPU Communication Interrupt Control Register - RISC 1 */
#define CNL_UART 	UART1_BASE //tdl for dual CPU booting test
#define GDB_UART 	UART1_BASE
#endif

#define IRR0R1                              (0x018 + GICR_BASE)       /* Interrupt routing 0 - RISC 1 */
#define IRR1R1                              (0x01C + GICR_BASE)       /* Interrupt routing 1 - RISC 1 */

#define ENRR0                               (0x028 + GICR_BASE)       /* RISC 0 Enable Register */
#define EXVORR0                             (0x02C + GICR_BASE)       /* RISC 0 Exception Vector Offset Register */

/* Global interrupt mask register field definitions
*/
#define TC01IE                              ((UINT32)1 << 31)       /* Timers/Counters 0 & 1 interrupt enable */
#define TC23IE                              (1 << 30)       /* Timers/Counters 2 & 3 interrupt enable */
#define UART0IE                             (1 << 29)       /* UART 0 interrupt enable */
#define UART1IE                             (1 << 28)       /* UART 1 interrupt enable */
#define I2C0IE                               (1 << 27)       /* I2C interrupt enable */
#define I2C1IE                               (1 << 26)       /* I2C interrupt enable */
#define I2C2IE                               (1 << 25)       /* I2C interrupt enable */
#define I2CSIE                               (1 << 24)       /* PWM interrupt enable */
#define SMC0IE                              (1 << 23)       /* Smartcard 0 interrupt enable */
#define SMC1IE                              (1 << 22)       /* Smartcard 1 interrupt enable */
#define GPIOAIE                             (1 << 21)       /* GPIO port A interrupt enable */
#define GPIOBIE                             (1 << 20)       /* GPIO port B interrupt enable */
#define GPIOCIE                             (1 << 19)       /* GPIO port C interrupt enable */
#define GPIODIE                             (1 << 18)       /* GPIO port D interrupt enable */
#define GPIOEIE                             (1 << 17)       /* GPIO port E interrupt enable */
#define GPIOFIE                             (1 << 16)       /* GPIO port F interrupt enable */
#define GPIOGIE                             (1 << 15)       /* GPIO port G interrupt enable */
#define GPIOHIE                             (1 << 14)       /* GPIO port H interrupt enable */
#define TPIE                                   (1 << 13)       /* Transport Parser interrupt enable */
#define MVDIE                                (1 << 12)       /* MVD interrupt enable */
#define AUDIOIE                             (1 << 11)       /* Audio interrupt enable */
#define DEIE                                   (1 << 10)       /* Display Engine interrupt enable */
#define TVEIE                                 (1 << 9)       /* TV encooder interrupt enable */
#define PCMIE                               	(1 << 8)       /* PCMCIA interrupt enable */
#define DMAIE                                (1 << 7)       /* DMA interrupt enable */
#define GEIE                                  	(1 << 6)       /* Graphic engine interrupt enable */
#define OSDIE                                	(1 << 5)       /* OSD interrupt enable */
#define ROMRRIE                           (1 << 4)       /* ROM read operation ready interrupt enable */
#define IRIE                               	(1 << 3)       /* IrDA interrupt enable */
#define LBCTMOIE                          (1 << 2)       /* Lexra Bus Timeout Interrupt Enable */
#define IRC1IE                            	(1 << 1)       /* IRC1 Interrupt Enable (Interrupt from RISC1) */
#define IHIE                  			(1 << 0)       /* IH Interrupt Enable */

/* Global interrupt status register field definitions */

#define TC01IP                              ((UINT32)1 << 31)       /* Timers/Counters 0 & 1 interrupt pending */
#define TC23IP                              (1 << 30)       /* Timers/Counters 2 & 3 interrupt pending */
#define UART0IP                             (1 << 29)       /* UART 0 interrupt pending */
#define UART1IP                             (1 << 28)       /* UART 1 interrupt pending */
#define I2C0IP                               (1 << 27)       /* I2C interrupt pending */
#define I2C1IP                               (1 << 26)       /* I2C interrupt pending */
#define I2C2IP                               (1 << 25)       /* I2C interrupt pending */
#define I2CSIP                               (1 << 24)       /* PWM interrupt pending */
#define SMC0IP                              (1 << 23)       /* Smartcard 0 interrupt pending */
#define SMC1IP                              (1 << 22)       /* Smartcard 1 interrupt pending */
#define GPIOAIP                             (1 << 21)       /* GPIO port A interrupt pending */
#define GPIOBIP                             (1 << 20)       /* GPIO port B interrupt pending */
#define GPIOCIP                             (1 << 19)       /* GPIO port C interrupt pending */
#define GPIODIP                             (1 << 18)       /* GPIO port D interrupt pending */
#define GPIOEIP                             (1 << 17)       /* GPIO port E interrupt pending */
#define GPIOFIP                             (1 << 16)       /* GPIO port F interrupt pending */
#define GPIOGIP                             (1 << 15)       /* GPIO port G interrupt pending */
#define GPIOHIP                             (1 << 14)       /* GPIO port H interrupt pending */
#define TPIP                                	(1 << 13)       /* Transport Parser interrupt pending */
#define MVDIP                               	(1 << 12)       /* MVD interrupt pending */
#define AUDIOIP                           	(1 << 11)       /* Audio interrupt pending */
#define DEIP                                	(1 << 10)       /* Display Engine interrupt pending */
#define TVEIP                               	(1 << 9)       /* TV encooder interrupt pending */
#define PCMIP                               	(1 << 8)       /* PCMCIA interrupt pending */
#define DMAIP                                (1 << 7)       /* DMA interrupt pending */
#define GEIP                                 	(1 << 6)       /* Graphic engine interrupt pending */
#define OSDIP                                (1 << 5)       /* OSD interrupt pending */
#define ROMRRIP                           (1 << 4)       /* ROM read operation ready interrupt pending */
#define IRIP                               	(1 << 3)       /* IrDA interrupt pending */
#define LBCTMOIP                          (1 << 2)       /* Lexra Bus Timeout Interrupt pending */
#define IRC1IP                  (UINT32) (1 << 1)       /* IRC1 Interrupt pending (Interrupt from RISC1) */
#define IHIP                  			(1 << 0)       /* IH Interrupt pending */

/* Interrupt routing register 0 - RISC0 field definitions */
#define TCIE01IRS_OFFSET               30            /* Timers/Counters 0 & 1 interrupt Route Select Offset */
#define TCIE23IRS_OFFSET               28            /* Timers/Counters 2 & 3 interrupt Route Select Offset */
#define UART0IRS_OFFSET                26            /* UART 0 interrupt Route Select Offset */
#define UART1IRS_OFFSET                24            /* UART 1 interrupt Route Select Offset */
#define I2C0IRS_OFFSET                   22            /* I2C0 interrupt Route Select Offset */
#define I2C1IRS_OFFSET                   20            /* I2C1 interrupt Route Select Offset */
#define I2C2IRS_OFFSET                   18            /* I2C2 interrupt Route Select Offset */
#define I2CSIRS_OFFSET                  16            /* PWM interrupt Route Select Offset */
#define SMC0IRS_OFFSET                  14            /* Smartcard 0 interrupt Route Select Offset */
#define SMC1IRS_OFFSET                  12            /* Smartcard 1 interrupt Route Select Offset */
#define GPIOAIRS_OFFSET                 10            /* GPIO port A interrupt Route Select Offset */
#define GPIOBIRS_OFFSET                  8            /* GPIO port B interrupt Route Select Offset */
#define GPIOCIRS_OFFSET                  6            /* GPIO port C interrupt Route Select Offset */
#define GPIODIRS_OFFSET                  4            /* GPIO port D interrupt Route Select Offset */
#define GPIOEIRS_OFFSET                   2            /* GPIO port E interrupt Route Select Offset */
#define GPIOFIRS_OFFSET                    0            /* GPIO port F interrupt Route Select Offset */


/* Interrupt routing register 1 - RISC0 field definitions */
#define GPIOGIRS_OFFSET           	30            /* GPIO port G interrupt Route Select Offset */
#define GPIOHIRS_OFFSET             28            /* GPIO port H interrupt Route Select Offset */
#define TPIRS_OFFSET                  	26            /* Transport Parser interrupt Route Select Offset */
#define MVDIRS_OFFSET                	24            /* MVD interrupt Route Select Offset */
#define AUDIOIRS_OFFSET           	22            /* Audio interrupt Route Select Offset */
#define DEIRS_OFFSET                  	20            /* Display Engine interrupt Route Select Offset */
#define TVEIRS_OFFSET                	18            /* TV encooder interrupt Route Select Offset */
#define PCMIRS_OFFSET                	16            /* PCMCIA interrupt Route Select Offset */
#define DMAIRS_OFFSET            	14		  /* DMA interrupt pending */
#define GEIRS_OFFSET                  	12            /* Graphic engine interrupt pending */
#define OSDIRS_OFFSET                	10            /* OSD interrupt pending */
#define ROMRRIRS_OFFSET          	8		  /* ROM read operation ready interrupt pending */
#define IRIRS_OFFSET                  	6	         /* IrDA interrupt pending */
#define LBCTMOIRS_OFFSET        	4              /* Lexra Bus Timeout Interrupt pending */
//#define IRC1IRS_OFFSET               	2		   /* IRC1 Interrupt pending (Interrupt from RISC1) */
#define IHIRS_OFFSET               	0		   /* Interface handler Interrupt pending */

#define I2C_IRQ1(x)             I2C_IRQ##x
#define I2C_IRQ(x)               I2C_IRQ1(x)
#define I2C_IRQ3                 0
#define I2C_IRQ4                 1
#define I2C_IRQ8                 2
#define I2C_IRQ9                 3

#define I2CS_IRQ1(x)             I2CS_IRQ##x
#define I2CS_IRQ(x)               I2CS_IRQ1(x)
#define I2CS_IRQ4                 0
#define I2CS_IRQ5                 1
#define I2CS_IRQ10               2
#define I2CS_IRQ11               3

#define TIMER01_IRQ1(x)        	TIMER01_IRQ##x
#define TIMER01_IRQ(x)        		TIMER01_IRQ1(x)
#define TIMER01_IRQ3                 0
#define TIMER01_IRQ4                 1
#define TIMER01_IRQ8                 2
#define TIMER01_IRQ9                 3

#define PCM_IRQ1(x)      		PCM_IRQ##x
#define PCM_IRQ(x)        		PCM_IRQ1(x)
#define PCM_IRQ6			0
#define PCM_IRQ7			1
#define PCM_IRQ12			2
#define PCM_IRQ13			3

#define LBTO_IRQ1(x)      		LBTO_IRQ##x
#define LBTO_IRQ(x)        		LBTO_IRQ1(x)
#define LBTO_IRQ6			0
#define LBTO_IRQ7			1
#define LBTO_IRQ14			2
#define LBTO_IRQ15			3

#define UART01_IRQ1(x)        		UART01_IRQ##x
#define UART01_IRQ(x)        		UART01_IRQ1(x)
#define UART01_IRQ3			0
#define UART01_IRQ4			1
#define UART01_IRQ8			2
#define UART01_IRQ9			3

/* Dispaly engine interrupt control field definitions
 * */
#define DE_IRQ(x)                               DE_##x
#define DE_IRQ4                                 (0)
#define DE_IRQ5                                 (1)
#define DE_IRQ12                                (2)
#define DE_IRQ13                                (3)

#define IH_IRQ(x)                               IH_##x
#define IH_IRQ6                                 (0)
#define IH_IRQ7                                 (1)
#define IH_IRQ14                                (2)
#define IH_IRQ15                                (3)

#define MVD_IRQ(x)                              MVD_##x
#define MVD_IRQ4                                (0)
#define MVD_IRQ5                                (1)
#define MVD_IRQ10                               (2)
#define MVD_IRQ11                               (3)

// For I2C interface
#define G_I2CBASE            0xBD022000
#define I2CCR                   (0x000 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMCR0                 (0x020 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSTR0                (0x024 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSR0                 (0x028 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMFR0                 (0x02c + G_I2CBASE)       /* I2C Clock Register */
#define I2CMCR1                 (0x040 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSTR1                (0x044 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSR1                 (0x048 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMFR1                 (0x04c + G_I2CBASE)       /* I2C Clock Register */
#define I2CMCR2                 (0x060 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSTR2                (0x064 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMSR2                 (0x068 + G_I2CBASE)       /* I2C Clock Register */
#define I2CMFR2                 (0x06c + G_I2CBASE)       /* I2C Clock Register */
#define I2CSRR                  (0x080 + G_I2CBASE)       /* I2C Clock Register */
#define I2CSCR                  (0x084 + G_I2CBASE)       /* I2C Clock Register */
#define I2CSSAR                 (0x088 + G_I2CBASE)       /* I2C Clock Register */
#define I2CSDFR                 (0x08c + G_I2CBASE)       /* I2C Clock Register */

#define I2CS_ID_OFFSET		7
#define I2CS_RESET			(1<<2)
#define I2CS_RCDRIE			(1<<1)
#define I2CS_WCDRIE			(1<<0)
#define I2CS_RCDRIF			(1<<1)
#define I2CS_WCDRIF			(1<<0)
#define I2CS_CDIB			(1<<7)
#define I2CS_CT_WRITE             (1 << 6)
#define I2CS_CT_READ             (0 << 6)
#define I2CS_RL_OFF           	2


#define I2C_RESET                     (UINT32) (1<<31)       /* Transaction complete pending bit */
#define I2C_TEIF                        (1<<2)       /* Transaction error pending bit */
#define I2C_RCIF                        (1<<1)       /* Receive complete pending bit */
#define I2C_TCIF                        (1<<0)       /* Transaction complete pending bit */
#define I2CSCR_OFFS                0x1             /* I2C slave regisger offset */
#define I2CSSAR_OFFS                0x2             /* I2C slave regisger offset */
#define I2CSDFR_OFFS                0x3             /* I2C slave regisger offset */


// For PCMCIA interface

#ifndef _RTD2880_NEW
#define GICR_PCBASE                         0xBD010300
#else
#define GICR_PCBASE                         0xBD010700
#endif

#define PC_PCFR  	(0x000 + GICR_PCBASE)
#define PC_PCR   	(0x004 + GICR_PCBASE)
#define PC_PSR   		(0x008 + GICR_PCBASE)
#define PC_PAMTCR   	(0x00c + GICR_PCBASE)
#define PC_PIMTCR   	(0x010 + GICR_PCBASE)
#define PC_PMATCR   	(0x014 + GICR_PCBASE)

#define PC_PSRESET  	((UINT32)1 << 31)  //!< PCMCIA software reset
#define PC_CS2 	  	(1 << 30)  //!< PCMCIA chip select 2 enable
#define PC_CS3 	  	(1 << 29)  //!< PCMCIA chip select 3 enable
#define PC_CS5 	  	(1 << 28)  //!< PCMCIA chip select 5 enable
#define PC_CS6	  	(1 << 27)  //!< PCMCIA chip select 6 enable

//Chuck add this definition on 20051025
#define PC_HW_RESET1	(1 << 26)	//!< PCMCIA card 1 reset
#define PC_HW_RESET2	(1 << 25)	//!< PCMCIA card 2 reset

#define PC_CT_READ 		(0 << 24)  //!< PCMCIA read command tyep
#define PC_CT_WRITE 	(1 << 24)  //!< PCMCIA write command tyep
#define PC_AT_IO_DRFR	0xfefe 	  //!< Access type as IO access & waiting DRFR interrupt
#define PC_AT_IO 		(0 << 23)  //!< Access type as IO access
#define PC_AT_ATTR 		(1 << 23)  //!< Access type as Attribute memory
#define PC_PA_OFFSET		8	  //!< PCMCIA address's offset

#define PC_PRES1	(1 << 9)	  //!< PCMCIA card 1 present bit
#define PC_PRES2	(1 << 8)	  //!< PCMCIA card 2 present bit
#define PC_PII1		(1 << 7)	  //!< PCMCIA card 1 IRQ1# interrupt
#define PC_PCII1		(1 << 6)	  //!< PCMCIA card 1 insert interrupt
#define PC_PCRI1	(1 << 5)	  //!< PCMCIA card 1 remove interrupt
#define PC_PII2		(1 << 4)	  //!< PCMCIA card 2 IRQ2# interrupt
#define PC_PCII2		(1 << 3)	  //!< PCMCIA card 2 insert interrupt
#define PC_PCRI2	(1 << 2)	  //!< PCMCIA card 2 remove interrupt
#define PC_AFI		(1 << 1)	  //!< PCMCIA address fault interrupt
#define PC_APFI		(1 << 0)	  //!< PCMCIA address pending flag interrupt

// For General Purpose Timer/Counter

#ifndef _RTD2880_NEW
#define GICR_TCBASE                         0xBD012000
#else
#define GICR_TCBASE                         0xBD010400
#endif

/* Timer/Counter data register field definitions
*/
#define TCD_OFFSET                          8

/* Timer control registers
*/
#define TC0DATA                             (0x000 + GICR_TCBASE)       /* Timer/Counter 0 data */
#define TC0CNT                              (0x004 + GICR_TCBASE)       /* Timer/Counter 0 count */
#define TC1DATA                             (0x008 + GICR_TCBASE)       /* Timer/Counter 1 data */
#define TC1CNT                              (0x00C + GICR_TCBASE)       /* Timer/Counter 1 count */
#define TC2DATA                             (0x010 + GICR_TCBASE)       /* Timer/Counter 2 data */
#define TC2CNT                              (0x014 + GICR_TCBASE)       /* Timer/Counter 2 count */
#define TC3DATA                             (0x018 + GICR_TCBASE)       /* Timer/Counter 3 data */
#define TC3CNT                              (0x01C + GICR_TCBASE)       /* Timer/Counter 3 count */


#define TCCNR01                             (0x040 + GICR_TCBASE)       /* Timer/Counter control - Timer 0 & 1 */
#define TCCNR23                             (0x044 + GICR_TCBASE)       /* Timer/Counter control - Timer 2 & 3 */
#define TCICR01                             (0x050 + GICR_TCBASE)       /* Timer/Counter intertupt - Timer 0 & 1 */
#define TCICR23                             (0x054 + GICR_TCBASE)       /* Timer/Counter intertupt - Timer 2 & 3 */
#define TCCDBR01                            (0x060 + GICR_TCBASE)       /* Clock division base - Timer 0 & 1 */
#define TCCDBR23                            (0x064 + GICR_TCBASE)       /* Clock division base - Timer 2 & 3 */
#define TCWCR                               (0x70 + GICR_TCBASE)       /* Watchdog timer control */
#define TCWTR                            (0x074 + GICR_TCBASE)       /* Watchdog Trigger  Register */
#define TCWMR                              (0x78 + GICR_TCBASE)       /* Watchdog timer control */

#ifndef _RTD2880_NEW

#else
#define TCWDMR                              (0x078 + GICR_TCBASE)       /* Watchdog Monitor Register */
#endif

#define TC4DATA                             (0x020 + GICR_TCBASE)       /* Timer/Counter 0 data */
#define TC4CNT                              (0x024 + GICR_TCBASE)       /* Timer/Counter 0 count */
#define TC5DATA                             (0x028 + GICR_TCBASE)       /* Timer/Counter 1 data */
#define TC5CNT                              (0x02C + GICR_TCBASE)       /* Timer/Counter 1 count */
#define TC6DATA                             (0x030 + GICR_TCBASE)       /* Timer/Counter 2 data */
#define TC6CNT                              (0x034 + GICR_TCBASE)       /* Timer/Counter 2 count */
#define TC7DATA                             (0x038 + GICR_TCBASE)       /* Timer/Counter 3 data */
#define TC7CNT                              (0x03C + GICR_TCBASE)       /* Timer/Counter 3 count */

#define TCCNR45                             (0x048 + GICR_TCBASE)       /* Timer/Counter control - Timer 0 & 1 */
#define TCCNR67                             (0x04c + GICR_TCBASE)       /* Timer/Counter control - Timer 2 & 3 */
#define TCICR45                             (0x058 + GICR_TCBASE)       /* Timer/Counter intertupt - Timer 0 & 1 */
#define TCICR67                             (0x05c + GICR_TCBASE)       /* Timer/Counter intertupt - Timer 2 & 3 */
#define TCCDBR45                            (0x068 + GICR_TCBASE)       /* Clock division base - Timer 0 & 1 */
#define TCCDBR67                            (0x06c + GICR_TCBASE)       /* Clock division base - Timer 2 & 3 */


/* Timer/Counter control register field defintions
*/
#define TC0EN                               ((UINT32)1 << 31)       /* Timer/Counter 0 enable */
#define TC0MODE_COUNTER                     0               /* Timer/Counter 0 counter mode */
#define TC0MODE_TIMER                       (1 << 30)       /* Timer/Counter 0 timer mode */
#define TC1EN                               (1 << 29)       /* Timer/Counter 1 enable */
#define TC1MODE_COUNTER                     0               /* Timer/Counter 1 counter mode */
#define TC1MODE_TIMER                       (1 << 28)       /* Timer/Counter 1 timer mode */
#define TC2EN                               ((UINT32)1 << 31)       /* Timer/Counter 2 enable */
#define TC2MODE_COUNTER                     0               /* Timer/Counter 2 counter mode */
#define TC2MODE_TIMER                       (1 << 30)       /* Timer/Counter 2 timer mode */
#define TC3EN                               (1 << 29)       /* Timer/Counter 3 enable */
#define TC3MODE_COUNTER                     0               /* Timer/Counter 3 counter mode */
#define TC3MODE_TIMER                       (1 << 28)       /* Timer/Counter 3 timer mode */
/* Timer/Counter interrupt register field definitions
*/
#define TC0IE                               ((UINT32)1 << 31)       /* Timer/Counter 0 interrupt enable */
#define TC1IE                               (1 << 30)       /* Timer/Counter 1 interrupt enable */
#define TC0IP                               (1 << 29)       /* Timer/Counter 0 interrupt pending */
#define TC1IP                               (1 << 28)       /* Timer/Counter 1 interrupt pending */
#define TC2IE                               ((UINT32)1 << 31)       /* Timer/Counter 2 interrupt enable */
#define TC3IE                               (1 << 30)       /* Timer/Counter 3 interrupt enable */
#define TC2IP                               (1 << 29)       /* Timer/Counter 2 interrupt pending */
#define TC3IP                               (1 << 28)       /* Timer/Counter 3 interrupt pending */
/* Clock division base register field definitions
*/
#define DIVF01_OFFSET                       16
#define DIVF23_OFFSET                       16
/* Watchdog control register field definitions
*/
#define OVSEL_15                            0               /* Overflow select count 2^15 */
#define OVSEL_16                            (1 << 29)       /* Overflow select count 2^16 */
#define OVSEL_17                            (2 << 29)       /* Overflow select count 2^17 */
#define OVSEL_18                            (3 << 29)       /* Overflow select count 2^18 */
#define OVSEL_19                            (4 << 29)       /* Overflow select count 2^19 */
#define OVSEL_20                            (5 << 29)       /* Overflow select count 2^20 */
#define OVSEL_21                            (6 << 29)       /* Overflow select count 2^21 */
#define OVSEL_22                            (7 << 29)       /* Overflow select count 2^22 */
#define WDTEST_EN 	                     ( 1 << 28)      /* Watchdog stop test mode enable bit */
#define WDSTOP_PATTERN                      0xA5            /* Watchdog stop pattern */
#define WDTE_OFFSET                         0               /* Watchdog enable */
#define WDC_OFFSET                          25              /* Indicate whether watchdog ever occurs */
#define WDTCLR_PATTERN                      0xFF<<WDC_OFFSET/* Watchdog clear pattern */


/*GPIO control registers definition
*/
#define GPIO_BASE           0xbd020000

//#ifndef _RTD2880_NEW
#define GPIO_C_CR		(GPIO_BASE)			/*Port C Configuration Register*/
#define GPIO_C_IMR		(GPIO_BASE+0x004)	/*Port C Interrupt Mask Register*/
#define GPIO_D_CR		(GPIO_BASE+0x008)	/*Port D Configuration Register*/
#define GPIO_D_IMR		(GPIO_BASE+0x00c)	/*Port D Interrupt Mask Register*/
#define GPIO_E_CR		(GPIO_BASE+0x010)	/*Port E Configuration Register*/
#define GPIO_E_IMR		(GPIO_BASE+0x014)	/*Port E Interrupt Mask Register*/
#define GPIO_F_CR		(GPIO_BASE+0x018)	/*Port F Configuration Register*/
#define GPIO_F_IMR		(GPIO_BASE+0x01c)	/*Port F Interrupt Mask Register*/
#define GPIO_G_CR		(GPIO_BASE+0x020)	/*Port G Configuration Register*/
#define GPIO_G_IMR		(GPIO_BASE+0x024)	/*Port G Interrupt Mask Register*/
#define GPIO_H_CR		(GPIO_BASE+0x028)	/*Port H Configuration Register*/
#define GPIO_H_IMR		(GPIO_BASE+0x02c)	/*Port H Interrupt Mask Register*/
#define GPIO_I_CR		(GPIO_BASE+0x030)	/*Port I Configuration Register*/
#define GPIO_I_IMR		(GPIO_BASE+0x034)	/*Port I Interrupt Mask Register*/
#define GPIO_J_CR		(GPIO_BASE+0x038)	/*Port J Configuration Register*/
#define GPIO_J_IMR		(GPIO_BASE+0x03c)	/*Port J Interrupt Mask Register*/
#define GPIO_K_CR		(GPIO_BASE+0x040)	/*Port K Configuration Register*/
#define GPIO_K_IMR		(GPIO_BASE+0x044)	/*Port K Interrupt Mask Register*/
#define GPIO_L_CR		(GPIO_BASE+0x048)	/*Port L Configuration Register*/
#define GPIO_L_IMR		(GPIO_BASE+0x04c)	/*Port L Interrupt Mask Register*/
#define GPIO_ER 			(GPIO_BASE+0x050)	/*GPIO Extension Register*/
//#endif
#define MUX_CTL_1	0xbd011110
#define MUX_CTL_2	0xbd011114
#define MUX_CTL_3	0xbd011118

/*PWM control register definition
*/
#define PWM_BASE	0xbd025000
#define PWM_C_CBR		(PWM_BASE)			/* Port C PWM clock base register */
#define PWM_C_CDR		(PWM_BASE+0x04)	/* Port C PWM clock duty register */
#define PWM_E_CBR		(PWM_BASE+0x08)			/* Port E PWM clock base register */
#define PWM_E_CDR		(PWM_BASE+0x0c)	/* Port E PWM clock duty register */
#define PWM_ER		(PWM_BASE+0x10)	/* PWM extension register */

//For Nor flash
#define NOR_REG_BASE               0xbd010500
#define MCMCRNF            		   (NOR_REG_BASE + 0x00)
#define MCRTCRNF           		   (NOR_REG_BASE + 0x04)
#define MCNFSR            		   (NOR_REG_BASE + 0x08)
#define MCB1MMSASR       		   (NOR_REG_BASE + 0x0c)
#define MCEBMMSAR       		   (NOR_REG_BASE + 0x10)

//For NAND flash

#ifndef _RTD2880_NEW
#define NAND_BASE               0xbd010100
#else
#define NAND_BASE               0xbd010600
#endif

#define NAND_ACR                (NAND_BASE)                     //NAND Flash Access Control Register
#define NAND_TCR                (NAND_BASE+0x04)        //NAND Flash Timing Control Register
#define NAND_ATCR               (NAND_BASE+0x08)        //NAND Flash Access Timing Control Register
#define NAND_RWDLR              (NAND_BASE+0x0c)        //NAND Flash R/W Data Length Register
#define NAND_DAIDR             (NAND_BASE+0x10) //NAND Flash Data Address IN DDR Register
#define NAND_SDAIDR     (NAND_BASE+0x14)     //NAND Flash Spare Address IN DDR Register
#define NAND_CR                 (NAND_BASE+0x18)        //NAND Flash Command Register
#define NAND_CBCR               (NAND_BASE+0x1c)        //NAND Flash Copy Back Command Register
#define NAND_CAR                (NAND_BASE+0x20)        //NAND Flash Column Address Register
#define NAND_RAR                (NAND_BASE+0x24)        //NAND Flash Row Address Register
#define NAND_DCAR               (NAND_BASE+0x28)        //NAND Flash Destination Column Address Register
#define NAND_DRAR               (NAND_BASE+0x2c)        //NAND Flash Destination Row Address Register
#define NAND_ICR                (NAND_BASE+0x30)        //NAND Flash Interrupt Control Register
#define NAND_SR                 (NAND_BASE+0x34)        //NAND Flash Status Register
#define NAND_SDR                (NAND_BASE+0x38)        //NAND Flash ID/Flash Status Data Register

#define LCD_PARAL_BASE	0xbd010a00			   // lcd parallel interface controller base
#define LCD_PARAL_ALE	(LCD_PARAL_BASE)	   // lcd parallel interface address latch control
#define LCD_PARAL_WR	(LCD_PARAL_BASE+0x04) // lcd parallel interface write control
#define LCD_PARAL_RD	(LCD_PARAL_BASE+0x08) //lcd parallel interface read control
#define LCD_PARAL_CON0	(LCD_PARAL_BASE+0x0c) //lcd parallel interface control register 0
#define LCD_PARAL_CON1	(LCD_PARAL_BASE+0x10) //lcd parallel interface control register 1
#define LCD_PARAL_SR	(LCD_PARAL_BASE+0x14) //lcd parallel interface status register


#ifndef _RTD2880_NEW
#define ICENRR0               0xbd011030     /* Enable Register - RISC0*/
#define ICEXVORR0          0xbd011034     /* Exception Vector Offset Register - RISC0 */
#else
#define ICENRR0               0xbd011028     /* Enable Register - RISC0*/
#define ICEXVORR0          0xbd01102c     /* Exception Vector Offset Register - RISC0 */
#endif

#define FLASH_MAP_BEGIN		0xbf000000
#define FLASH_MAP_END		0xc0000000
#define FLASH_BASE 			0xbfc00000

//For PLL Controller
#define PLL_BASE				0xbd011200
#define PLL_CPUCR			(0x00 + PLL_BASE) /*PLL_CPU Control Register*/
#define PLL_DDSCR			(0x04 + PLL_BASE) /*PLL_DDS Control Register*/
#define PLL_DDSCR2			(0x08 + PLL_BASE) /*PLL_DDS Control Register2*/
#define PLL_DDSCR3			(0x0C + PLL_BASE) /*PLL_DDS Control Register3*/
#define PLL_DDSSR			(0x10 + PLL_BASE) /*PLL_DDS Status Register*/
#define PLL_DDSSR2			(0x14 + PLL_BASE) /*PLL_DDS Status Register2*/
#define PLL_BUSCR			(0x18 + PLL_BASE) /*PLL_BUS Control Register*/
#define PLL_BUSCR2			(0x1C + PLL_BASE) /*PLL_BUS Control Register2*/
#define PLL_BUSCR3 			(0x20 + PLL_BASE) /*PLL_BUS Control Register3*/
#define PLL_DISPCR			(0x24 + PLL_BASE) /*PLL_DISP Control Register*/
#define PLL_DISPCR2			(0x28 + PLL_BASE) /*PLL_DISP Control Register2*/
#define PLL_OTHERCR			(0x2C + PLL_BASE) /*PLL_OTHER Control Register*/

#define SCIU_CDCR			(0x60 + PLL_BASE) /* Clock Domain control Register */
// For NIC
#define NIC_CNR1	0x000
#define NIC_ID		0x000
#define NIC_MAR		0x008
#define NIC_TSAD		0x014
#define NIC_RSAD	0x018
#define NIC_IMTR		0x01C
#define NIC_CR		0x03b
#define NIC_IMR		0x03c
#define NIC_ISR		0x03e
#define NIC_MSR		0x058
#define NIC_TMF0	0x028
#define NIC_TMF1	0x02C
#define NIC_TMF2	0x030
#define NIC_TMF3	0x034
#define NIC_MII		0x05C
#define NIC_CNR2	0x03C
#define NIC_TCR		0x040
#define NIC_RCR		0x044
#define NIC_MPC		0x080
#define NIC_TXCOL	0x084
#define NIC_RXERR	0x088
#define NIC_BIST		0x08C

#define MII_W		0x80000000
#define MII_R		0x00000000
#define MII_PHY_ADDR	0x01

#define PHY_REG0	0x00
#define PHY_LOOPBACK 0x4000
#define PHY_100M	0x2000
#define PHY_10M		0x0000
#define PHY_AUTONEO 0x1000
#define PHY_F_DUP	0x0100
#define PHY_H_DUP	0x0000


#define	TxFDP1		0x1300
#define	TxCDO1		0x1304
#define	RxFDP		0x13F0
#define	RxCDO		0x13F4
#define RxRingSize	0x13f6
#define EthrntRxCPU_Des_Num	0x1430
#define Rx_Pse_Des_Thres		0x1432
#define	IO_CMD		0x1434

#define TX_EN		BIT(2)
#define RX_EN		BIT(3)

#define DEFAULT_CONSOLE            CNL_UART

#define Def_UARTBaudRate 115200
#define Fast_UARTBaudRate 115200
#define BAUDRATE_DEF (CPU_CLOCK / Def_UARTBaudRate / 16) - 1
//#define Timer_Tick CPU_CLOCK /Fast_UARTBaudRate * 8
//#define Timer_Tick 27000*1000 /Fast_UARTBaudRate * 8

#define Timer_Tick CPU_CLOCK / (Fast_UARTBaudRate / 8)
#define Timer_Data  (Fast_UARTBaudRate / 8 /10)
//#define Timer_Tick 27000* 8

#define TICK_10MS_FREQ    100 /* 100 Hz */
#define TICK_5MS_FREQ      200 /* 200 Hz */
#define ROS_TICK_FREQ  	TICK_5MS_FREQ


///////////////////////////////////////////////////////
//
// Memory Mapping Area (Linux, IP, ROS)
//
///////////////////////////////////////////////////////

#define MMA_LINUX_START 0x0
#define MMA_LINUX_SIZE (7 << 20)

#define MMA_TP0_START 0x700000
//#define MMA_TP0_SIZE (3 << 20)
#define MMA_TP0_SIZE (7*512*1024)

#define MMA_TP1_START 0x1000000
#define MMA_TP1_SIZE (3 << 20)

#define MMA_GDE_START 0x1300000
#define MMA_GDE_SIZE (8 << 20)

#define MMA_DISP_MVD_SHARED_START (0xa1cffc00)   ///< KSEG1 virtual addr
#define MMA_DISP_MVD_SHARED_0	MMA_DISP_MVD_SHARED_START
#define MMA_DISP_MVD_SHARED_1	(0x100+MMA_DISP_MVD_SHARED_0)
#define MMA_DISP_MVD_SHARED_SIZE (1 << 10)

#define MMA_AI_FIFO_START 0x1d00000
#define MMA_AI_FIFO_SIZE (672 << 10)

#define MMA_ROS_START 0x1e00000
#define MMA_ROS_SIZE (2 << 20)

#define MMA_MVD_BUFFER_START 0x2600000
#define MMA_MVD_BUFFER_SIZE (17 << 20)

#endif
