/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 */

#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H

//#define NR_IRQS			256  // sync as hardware gic configuration
#ifndef CONFIG_MACH_RTK1192
#define NR_IRQS			320  // sync as hardware gic configuration
#else
#define NR_IRQS         360
#endif

#define IRQ_WDOG_NMI	32
#define IRQ_RTC			33
#define IRQ_TIMER		34
#define IRQ_CPU2CPU		35	// ACPU/VCPU/VCPU2 to SCPU
#define IRQ_DCSYS		36	// DCSYS-PHY, DCSYS/TVSB/SB2 to SCPU
#define IRQ_L2CACHE		37
#define IRQ_IMDOMAIN	38	// VODMA1/VODMA2/DCC/APLL/I/M-DOMAIN
#define IRQ_DDOMAIN		39	// DCT/UZ/OSD
#define IRQ_AXI			40
#define IRQ_VDEC		41
#define IRQ_VBI			42
#define IRQ_SE			43
#define IRQ_MCP			44
#define IRQ_MD			45
#define IRQ_GPU			46
#define IRQ_IFDEMOD		47
#define IRQ_NF			49	// NF/EMMC
#define IRQ_CR			74
#define IRQ_CRSD		76
#define IRQ_MISC		51	// GPIO/I2C/UART/SC/PCMCIA/EFUSE
#define IRQ_ETH			52	// ETH/GETH
#define IRQ_USB			53
#define IRQ_TP			54
#define IRQ_HDMI		55
#define IRQ_SDIO		56
#define IRQ_CEC			57	// CEC/CBUS/MISC_ISO_ON/MISC_ISO_OFF/SYNCP
#define IRQ_SB2			68
#define IRQ_VE			83

#endif
