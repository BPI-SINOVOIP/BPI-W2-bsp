/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RTK_CEC_H__
#define __RTK_CEC_H__

#include <linux/wait.h>
#include <linux/timer.h>
#include <linux/clk.h>
#include <linux/reset.h>

#include "../cm_buff.h"

struct rtk_cec_xmit {
	unsigned char enable : 1;
	unsigned char state : 7;
	cm_buff *cmb;
	unsigned long timeout;
	struct delayed_work work;
};

struct rtk_cec_rcv {
	unsigned char enable : 1;
	unsigned char state : 7;
	cm_buff *cmb;
	wait_queue_head_t wq;
	struct delayed_work work;
};

struct rtk_cec {
	struct device *dev;
	struct {
		unsigned char init : 1;
		unsigned char enable : 1;
		unsigned char standby_mode : 1;
	} status;

	void __iomem *reg_base;
	void __iomem *iso_base;
	void __iomem *wrapper_reg;
	unsigned int irq_num;

	unsigned long  standby_config;
	unsigned char  standby_logical_addr;
	unsigned short standby_physical_addr;
	unsigned char  standby_cec_version;
	unsigned long  standby_vendor_id;
	unsigned short standby_rx_mask;
	unsigned char  standby_cec_wakeup_off;

	struct rtk_cec_xmit xmit;
	struct rtk_cec_rcv rcv;
	cm_buff_head tx_queue;
	cm_buff_head rx_queue;
	cm_buff_head rx_free_queue;
	spinlock_t lock;
	struct clk *clk;
	struct notifier_block clk_nb;
	struct reset_control *rstc;
	struct ion_client *rpc_ion_client;
	int chip_id;
};

#define RX_RING_LENGTH		16
#define TX_RING_LENGTH		16
#define TX_TIMEOUT		(HZ<<2)
#define SA_INTERRUPT		0
#define SA_SHIRQ		IRQF_SHARED


#define write_reg32(addr, val)	writel(val, (volatile unsigned int*)(addr))
#define read_reg32(addr)	readl((volatile unsigned int*)(addr))

#define FLD_GET(val, start, end)	(((val) & FLD_MASK(start, end)) >> (end))
#define FLD_MASK(start, end)		(((1 << (start - end + 1)) - 1) << (end))
#define SETBITS(base, offset, Mask)	write_reg32((base+offset), (read_reg32(base+offset) | Mask))
#define READBITS(value, Mask)		((value >> (Mask)) & 0x1)
#define CLEARBITS(base, offset, Mask)	write_reg32((base+offset), (read_reg32(base+offset) & ~(Mask)))
#define MASK_REG_32(base, offset, andMask, orMask)	write_reg32((base+offset), ((read_reg32(base+offset) & (andMask)) | (orMask)))

enum {
	IDEL,
	XMIT,
	RCV
};

enum {
	RCV_OK,
	RCV_FAIL,
};

#define CEC_MODE_OFF        0
#define CEC_MODE_ON         1
#define CEC_MODE_STANDBY    2

/* register define */
#define RTK_CEC_CR0				(0x00)
#define RTK_CEC_RTCR0				(0x04)
#define RTK_CEC_RXCR0				(0x08)
#define RTK_CEC_TXCR0				(0x0C)
#define RTK_CEC_TXDR0				(0x10)
#define RTK_CEC_TXDR1				(0x14)
#define RTK_CEC_TXDR2				(0x18)
#define RTK_CEC_TXDR3				(0x1C)
#define RTK_CEC_TXDR4				(0x20)
#define RTK_CEC_RXDR1				(0x24)
#define RTK_CEC_RXDR2				(0x28)
#define RTK_CEC_RXDR3				(0x2C)
#define RTK_CEC_RXDR4				(0x30)
#define RTK_CEC_RXTCR0				(0x34)
#define RTK_CEC_TXTCR0				(0x38)
#define RTK_CEC_TXTCR1				(0x3C)

#define RTK_GDI_CEC_COMPARE_OPCODE_01		(0x40)
#define RTK_GDI_CEC_SEND_OPCODE_01		(0x44)
#define RTK_GDI_CEC_SEND_OPERAND_NUMBER_01	(0x48)
#define RTK_GDI_CEC_OPERAND_01			(0x4C)
#define RTK_GDI_CEC_OPERAND_02			(0x50)
#define RTK_GDI_CEC_OPERAND_03			(0x54)
#define RTK_GDI_CEC_COMPARE_OPCODE_02		(0x58)
#define RTK_GDI_CEC_SEND_OPCODE_02		(0x5C)
#define RTK_GDI_CEC_SEND_OPERAND_NUMBER_02	(0x60)
#define RTK_GDI_CEC_OPERAND_04			(0x64)
#define RTK_GDI_CEC_OPERAND_05			(0x68)
#define RTK_GDI_CEC_OPERAND_06			(0x6C)
#define RTK_GDI_CEC_COMPARE_OPCODE_03		(0x70)
#define RTK_GDI_CEC_SEND_OPCODE_03		(0x74)
#define RTK_GDI_CEC_SEND_OPERAND_NUMBER_03	(0x78)
#define RTK_GDI_CEC_OPERAND_07			(0x7C)
#define RTK_GDI_CEC_OPERAND_08			(0x80)
#define RTK_GDI_CEC_OPERAND_09			(0x84)
#define RTK_GDI_CEC_COMPARE_OPCODE_04		(0x88)
#define RTK_GDI_CEC_SEND_OPCODE_04		(0x8C)
#define RTK_GDI_CEC_SEND_OPERAND_NUMBER_04	(0x90)
#define RTK_GDI_CEC_OPERAND_10			(0x94)
#define RTK_GDI_CEC_OPERAND_11			(0x98)
#define RTK_GDI_CEC_OPERAND_12			(0x9C)
#define RTK_GDI_CEC_COMPARE_OPCODE_05		(0xA0)
#define RTK_GDI_CEC_COMPARE_OPCODE_06		(0xA4)
#define RTK_GDI_CEC_COMPARE_OPCODE_07		(0xA8)
#define RTK_GDI_CEC_COMPARE_OPCODE_08		(0xAC)
#define RTK_GDI_CEC_COMPARE_OPCODE_09		(0xB0)
#define RTK_GDI_CEC_COMPARE_OPCODE_10		(0xB4)
#define RTK_GDI_CEC_COMPARE_OPCODE_11		(0xB8)
#define RTK_GDI_CEC_COMPARE_OPCODE_12		(0xBC)
#define RTK_GDI_CEC_COMPARE_OPCODE_13		(0xC0)
#define RTK_GDI_CEC_COMPARE_OPCODE_14		(0xC4)
#define RTK_GDI_CEC_COMPARE_OPCODE_15		(0xC8)
#define RTK_GDI_CEC_OPCODE_ENABLE		(0xCC)
#define RTK_GDI_POWER_SAVING_MODE		(0xD0)

#define RTK_CEC_SOFT_RESET			(0x88)
#define RTK_CEC_CLOCK_ENABLE			(0x8C)

#define CEC_CR0					RTK_CEC_CR0
#define CEC_RTCR0				RTK_CEC_RTCR0
#define CEC_RXCR0				RTK_CEC_RXCR0
#define CEC_TXCR0				RTK_CEC_TXCR0
#define CEC_TXDR0				RTK_CEC_TXDR0
#define CEC_TXDR1				RTK_CEC_TXDR1
#define CEC_TXDR2				RTK_CEC_TXDR2
#define CEC_TXDR3				RTK_CEC_TXDR3
#define CEC_TXDR4				RTK_CEC_TXDR4
#define CEC_RXDR1				RTK_CEC_RXDR1
#define CEC_RXDR2				RTK_CEC_RXDR2
#define CEC_RXDR3				RTK_CEC_RXDR3
#define CEC_RXDR4				RTK_CEC_RXDR4
#define CEC_RXTCR0				RTK_CEC_RXTCR0
#define CEC_TXTCR0				RTK_CEC_TXTCR0
#define CEC_TXTCR1				RTK_CEC_TXTCR1

#define GDI_CEC_COMPARE_OPCODE_01		RTK_GDI_CEC_COMPARE_OPCODE_01
#define GDI_CEC_SEND_OPCODE_01			RTK_GDI_CEC_SEND_OPCODE_01
#define GDI_CEC_SEND_OPERAND_NUMBER_01		RTK_GDI_CEC_SEND_OPERAND_NUMBER_01
#define GDI_CEC_OPERAND_01			RTK_GDI_CEC_OPERAND_01
#define GDI_CEC_OPERAND_02			RTK_GDI_CEC_OPERAND_02
#define GDI_CEC_OPERAND_03			RTK_GDI_CEC_OPERAND_03
#define GDI_CEC_COMPARE_OPCODE_02		RTK_GDI_CEC_COMPARE_OPCODE_02
#define GDI_CEC_SEND_OPCODE_02			RTK_GDI_CEC_SEND_OPCODE_02
#define GDI_CEC_SEND_OPERAND_NUMBER_02		RTK_GDI_CEC_SEND_OPERAND_NUMBER_02
#define GDI_CEC_OPERAND_04			RTK_GDI_CEC_OPERAND_04
#define GDI_CEC_OPERAND_05			RTK_GDI_CEC_OPERAND_05
#define GDI_CEC_OPERAND_06			RTK_GDI_CEC_OPERAND_06
#define GDI_CEC_COMPARE_OPCODE_03		RTK_GDI_CEC_COMPARE_OPCODE_03
#define GDI_CEC_SEND_OPCODE_03			RTK_GDI_CEC_SEND_OPCODE_03
#define GDI_CEC_SEND_OPERAND_NUMBER_03		RTK_GDI_CEC_SEND_OPERAND_NUMBER_03
#define GDI_CEC_OPERAND_07			RTK_GDI_CEC_OPERAND_07
#define GDI_CEC_OPERAND_08			RTK_GDI_CEC_OPERAND_08
#define GDI_CEC_OPERAND_09			RTK_GDI_CEC_OPERAND_09
#define GDI_CEC_COMPARE_OPCODE_04		RTK_GDI_CEC_COMPARE_OPCODE_04
#define GDI_CEC_SEND_OPCODE_04			RTK_GDI_CEC_SEND_OPCODE_04
#define GDI_CEC_SEND_OPERAND_NUMBER_04		RTK_GDI_CEC_SEND_OPERAND_NUMBER_04
#define GDI_CEC_OPERAND_10			RTK_GDI_CEC_OPERAND_10
#define GDI_CEC_OPERAND_11			RTK_GDI_CEC_OPERAND_11
#define GDI_CEC_OPERAND_12			RTK_GDI_CEC_OPERAND_12
#define GDI_CEC_COMPARE_OPCODE_05		RTK_GDI_CEC_COMPARE_OPCODE_05
#define GDI_CEC_COMPARE_OPCODE_06		RTK_GDI_CEC_COMPARE_OPCODE_06
#define GDI_CEC_COMPARE_OPCODE_07		RTK_GDI_CEC_COMPARE_OPCODE_07
#define GDI_CEC_COMPARE_OPCODE_08		RTK_GDI_CEC_COMPARE_OPCODE_08
#define GDI_CEC_COMPARE_OPCODE_09		RTK_GDI_CEC_COMPARE_OPCODE_09
#define GDI_CEC_COMPARE_OPCODE_10		RTK_GDI_CEC_COMPARE_OPCODE_10
#define GDI_CEC_COMPARE_OPCODE_11		RTK_GDI_CEC_COMPARE_OPCODE_11
#define GDI_CEC_COMPARE_OPCODE_12		RTK_GDI_CEC_COMPARE_OPCODE_12
#define GDI_CEC_COMPARE_OPCODE_13		RTK_GDI_CEC_COMPARE_OPCODE_13
#define GDI_CEC_COMPARE_OPCODE_14		RTK_GDI_CEC_COMPARE_OPCODE_14
#define GDI_CEC_COMPARE_OPCODE_15		RTK_GDI_CEC_COMPARE_OPCODE_15
#define GDI_CEC_OPCODE_ENABLE			RTK_GDI_CEC_OPCODE_ENABLE
#define GDI_POWER_SAVING_MODE			RTK_GDI_POWER_SAVING_MODE

/* CR0 */
#define LOGICAL_ADDR_SHIFT		24
#define CEC_MODE(x)			((x & 0x3)<<30)
#define TEST_MODE_PAD_EN		(0x1<<28)
#define LOGICAL_ADDR(x)			((x & 0xF)<<LOGICAL_ADDR_SHIFT)
#define TIMER_DIV(x)			((x & 0xFF)<<16)
#define PRE_DIV(x)			((x & 0xFF)<<8)
#define UNREG_ACK_EN			(1<<7)
#define CDC_ARBITRATION_EN		(0x1<<5)
#define TEST_MODE_DATA(x)		(x & 0x1F)

#define CEC_MODE_MASK			(CEC_MODE(3))
#define LOGICAL_ADDR_MASK		(LOGICAL_ADDR(0xF))
#define CTRL_MASK1			(CEC_MODE_MASK | LOGICAL_ADDR_MASK)

/* RTCR0 */
#define CEC_PAD_IN			(0x1<<31)
#define CLEAR_CEC_INT			(0x1<<11)
#define WT_CNT(x)			((x & 0x3F)<<5)
#define LATTEST				(0x1<<4)
#define RETRY_NO_MASK			(0x0F)
#define RETRY_NO(x)			(x & 0xF)

/* RXCR0 */
#define INIT_ADDR_SHIFT			(8)
#define BROADCAST_ADDR			(0x1<<31)
#define STB_ADDR_SEL			(0x1<<20)
#define STB_INIT_ADDR(x)		((x & 0xF)<<16)
#define RX_EN				(0x1<<15)
#define RX_RST				(0x1<<14)
#define RX_CONTINUOUS			(0x1<<13)
#define RX_INT_EN			(0x1<<12)
#define INIT_ADDR(x)			((x & 0xF)<<INIT_ADDR_SHIFT)
#define RX_EOM				(0x1<<7)
#define RX_INT				(0x1<<6)
#define RX_FIFO_OV			(0x1<<5)
#define RX_FIFO_CNT(x)			(x & 0x1F)

#define INIT_ADDR_MASK			INIT_ADDR(0xF)

/* TXCR0 */
#define TX_ADDR_EN			(0x1<<20)
#define TX_ADDR(x)			((x & 0xF)<<16)
#define TX_EN				(0x1<<15)
#define TX_RST				(0x1<<14)
#define TX_CONTINUOUS			(0x1<<13)
#define TX_INT_EN			(0x1<<12)
#define DEST_ADDR(x)			((x & 0xF)<<8)
#define TX_EOM				(0x1<<7)
#define TX_INT				(0x1<<6)
#define TX_FIFO_UD			(0x1<<5)
#define TX_FIFO_CNT(x)			(x & 0x1F)

/* TXDR0 */
#define TX_ADD_CNT			(0x1<<6)
#define RX_SUB_CNT			(0x1<<5)
#define FIFO_CNT(x)			(x & 0x1F)

/* RXTCR0 */
#define RX_START_LOW(x)			((x & 0xFF)<<24)
#define RX_START_PERIOD(x)		((x & 0xFF)<<16)
#define RX_DATA_SAMPLE(x)		((x & 0xFF)<<8)
#define RX_DATA_PERIOD(x)		(x & 0xFF)

/* TXCR0 */
#define TX_START_LOW(x)			((x & 0xFF)<<8)
#define TX_START_HIGH(x)		((x & 0xFF))

#define TX_DATA_LOW(x)			((x & 0xFF)<<16)
#define TX_DATA_01(x)			((x & 0xFF)<<8)
#define TX_DATA_HIGH(x)			((x & 0xFF))

#endif /*__RTK_CEC_H_ */
