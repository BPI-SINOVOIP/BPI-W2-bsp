/* drivers/media/platform/rtk-cec/rtk_cec.h
 *
 * Realtek HDMI CEC driver
 *
 * Copyright (c) 2019 Realtek Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _RTK_CEC_H_
#define _RTK_CEC_H_ __FILE__

#include <linux/clk.h>
#include <linux/reset.h>

/* CEC register define */
#define CEC_CR0		(0x00)
#define CEC_RTCR0	(0x04)
#define CEC_RXCR0	(0x08)
#define CEC_TXCR0	(0x0C)
#define CEC_TXDR0	(0x10)
#define CEC_TXDR1	(0x14)
#define CEC_TXDR2	(0x18)
#define CEC_TXDR3	(0x1C)
#define CEC_TXDR4	(0x20)
#define CEC_RXDR1	(0x24)
#define CEC_RXDR2	(0x28)
#define CEC_RXDR3	(0x2C)
#define CEC_RXDR4	(0x30)
#define CEC_RXTCR0	(0x34)
#define CEC_TXTCR0	(0x38)
#define CEC_TXTCR1	(0x3C)
#define CEC_PWR_SAVE	(0xD0)

/* For CEC_CR0 */
#define CEC_MODE_SHIFT		(30)
#define PRE_DIV_SHIFT		(8)
#define TIMER_DIV_SHIFT		(16)
#define LOG_ADDR_SHIFT		(24)
#define PRE_DIV_MASK		(0xFF << PRE_DIV_SHIFT)
#define TIMER_DIV_MASK		(0xFF << TIMER_DIV_SHIFT)
#define LOG_ADDR_MASK		(0xF << LOG_ADDR_SHIFT)
#define PAD_DATA_MASK		(0x1F)
#define UNREG_ACK_EN		BIT(7)

/* For CEC_RTCR0 */
#define PAD_EN_SHIFT		(17)
#define PAD_EN_MODE_SHIFT	(16)
#define RETRY_NUM_MASK		(0xF)

/* For CEC_RXCR0 */
#define RX_INT_CLEAR		BIT(6)
#define RX_INT			BIT(6)
#define RX_EOM			BIT(7)
#define RX_INT_EN		BIT(12)
#define RX_RESET		BIT(14)
#define RX_EN			BIT(15)

/* For CEC_TXCR0 */
#define TX_INT_CLEAR		BIT(6)
#define TX_INT			BIT(6)
#define TX_EOM			BIT(7)
#define TX_INT_EN		BIT(12)
#define TX_RESET		BIT(14)
#define TX_EN			BIT(15)
#define TX_ADDR_EN		BIT(20)
#define TX_DEST_ADDR_SHIFT	(8)
#define TX_LOG_ADDR_SHIFT	(16)
#define TX_FIFO_CNT		(0x1F)

/* For CEC_TXDR0 */
#define SUB_CNT			BIT(5)
#define ADD_CNT			BIT(6)

/* For CEC_RXTCR0 */
#define RXSTART_LOW_SHIFT	(24)
#define RXSTART_PERIOD_SHIFT	(16)
#define RXDATA_SAMPLE_SHIFT	(8)

/* For CEC_TXTCR0 */
#define TXSTART_LOW_SHIFT	(8)

/* For CEC_TXTCR1 */
#define TXDATA_LOW_SHIFT	(16)
#define TXDATA_01_SHIFT		(8)

/* For CEC_PWR_SAVE */
#define RPU_MASK		(0x1F)
#define RPU_EN			BIT(5)
#define SPECIAL_CMD_IRQ_EN	BIT(8)

/* CEC wrapper register define */
#define WRAPPER_CTRL		(0x00)

#define INT_ACPU_SHIFT		(16)
#define INT_SCPU_SHIFT		(17)
#define CLOCK_SEL_SHIFT		(26)

enum cec_state {
	STATE_IDLE,
	STATE_BUSY,
	STATE_DONE,
	STATE_NACK,
	STATE_ERROR
};

struct rtk_cec_dev {
	struct cec_adapter	*adap;
	struct cec_msg		msg;
	struct device		*dev;

	struct clk		*clk_cbus_osc;
	struct clk		*clk_cbus_sys;
	struct clk		*clk_cbus_tx;
	struct reset_control	*rstc_cbus;
	struct reset_control	*rstc_cbus_tx;

	void __iomem		*reg;
	void __iomem		*wrapper;
	int			irq;

	enum cec_state		rx;
	enum cec_state		tx;
	unsigned char		log_addr;
};

#endif /* _RTK_CEC_H_ */
