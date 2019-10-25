/* drivers/media/platform/rtk-cec/rtk_cec.c
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

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/pm_runtime.h>
#include <media/cec.h>

#include "rtk_cec.h"

#define CEC_NAME	"rtk-cec"

#define XTAL_CLK		27000000
#define PRE_DIV_TARGET		800000
#define TIMER_DIV_TARGET	40000
#define RPU_SELECT		0x17

#define TX_FIFO_NUM		4

static void rtk_cec_rx_reset(struct rtk_cec_dev *cec)
{
	writel(RX_INT_CLEAR | RX_RESET, cec->reg + CEC_RXCR0);
	writel(0, cec->reg + CEC_RXCR0);
}

static void rtk_cec_tx_reset(struct rtk_cec_dev *cec)
{
	writel(TX_INT_CLEAR | TX_RESET, cec->reg + CEC_TXCR0);
	writel(0, cec->reg + CEC_TXCR0);
}

static void rtk_cec_set_divider(struct rtk_cec_dev *cec)
{
	unsigned int reg;
	unsigned short pre_div, timer_div;

	reg = readl(cec->wrapper + WRAPPER_CTRL);
	reg &= ~(1 << CLOCK_SEL_SHIFT);
	writel(reg, cec->wrapper + WRAPPER_CTRL);

	pre_div = XTAL_CLK / PRE_DIV_TARGET;
	timer_div = PRE_DIV_TARGET / TIMER_DIV_TARGET;

	reg = readl(cec->reg + CEC_CR0);
	reg &= ~(PRE_DIV_MASK | TIMER_DIV_MASK);
	reg |= (pre_div << PRE_DIV_SHIFT) | (timer_div << TIMER_DIV_SHIFT);
	writel(reg, cec->reg + CEC_CR0);
}

static void rtk_cec_set_retries(struct rtk_cec_dev *cec, unsigned char retries)
{
	unsigned int reg;

	reg = readl(cec->reg + CEC_RTCR0);
	reg &= ~RETRY_NUM_MASK;
	reg |= retries;
	writel(reg, cec->reg + CEC_RTCR0);
}

static void rtk_cec_enable(struct rtk_cec_dev *cec)
{
	unsigned int reg;

	reg = (1 << PAD_EN_SHIFT) | (1 << PAD_EN_MODE_SHIFT);
	writel(reg, cec->reg + CEC_RTCR0);

	rtk_cec_set_retries(cec, 2);

	reg = (0x1A << TXDATA_LOW_SHIFT) | (0x23 << TXDATA_01_SHIFT) | 0x22;
	writel(reg, cec->reg + CEC_TXTCR1);

	reg = (0x93 << TXSTART_LOW_SHIFT) | 0x20;
	writel(reg, cec->reg + CEC_TXTCR0);

	reg = (0x8c << RXSTART_LOW_SHIFT) | (0xc1 << RXSTART_PERIOD_SHIFT) |
				(0x2a << RXDATA_SAMPLE_SHIFT) | 0x52;
	writel(reg, cec->reg + CEC_RXTCR0);

	reg = readl(cec->reg + CEC_CR0);
	reg |= (1 << CEC_MODE_SHIFT) | UNREG_ACK_EN;
	reg &= ~(PAD_DATA_MASK);
	writel(reg, cec->reg + CEC_CR0);

	reg = SPECIAL_CMD_IRQ_EN | RPU_EN | RPU_SELECT;
	writel(reg, cec->reg + CEC_PWR_SAVE);

	reg = readl(cec->wrapper + WRAPPER_CTRL);
	reg |= (1 << INT_ACPU_SHIFT) | (1 << INT_SCPU_SHIFT);
	writel(reg, cec->wrapper + WRAPPER_CTRL);
}

static void rtk_cec_disable(struct rtk_cec_dev *cec)
{
	unsigned int reg;

	reg = readl(cec->reg + CEC_CR0);
	reg &= ~(1 << CEC_MODE_SHIFT);
	writel(reg, cec->reg + CEC_CR0);
}

static void rtk_cec_rx_enable(struct rtk_cec_dev *cec)
{
	writel(RX_EN | RX_INT_EN, cec->reg + CEC_RXCR0);
}

static void rtk_cec_get_rx_buf(struct rtk_cec_dev *cec,
			       unsigned int size, unsigned char *buf)
{
	unsigned int rxfifo[4];
	int i;

	for (i = 0; i < size; i += 4)
		rxfifo[i >> 2] = __cpu_to_be32(readl(cec->reg + CEC_RXDR1 + i));

	memcpy(buf, (unsigned char *)rxfifo, size);

	writel(SUB_CNT | size, cec->reg + CEC_TXDR0);
}

static int rtk_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct rtk_cec_dev *cec = adap->priv;

	dev_dbg(cec->dev, "%s start, %d\n", __func__, enable);
	if (enable) {
		rtk_cec_rx_reset(cec);
		rtk_cec_tx_reset(cec);

		rtk_cec_set_divider(cec);
		rtk_cec_enable(cec);
		rtk_cec_rx_enable(cec);
	} else {
		rtk_cec_rx_reset(cec);
		rtk_cec_tx_reset(cec);

		rtk_cec_disable(cec);
	}
	return 0;
}

static int rtk_cec_adap_log_addr(struct cec_adapter *adap, u8 addr)
{
	struct rtk_cec_dev *cec = adap->priv;
	unsigned int reg;

	dev_dbg(cec->dev, "%s addr = 0x%x\n", __func__, addr);
	reg = readl(cec->reg + CEC_CR0);
	reg &= ~(LOG_ADDR_MASK);
	reg |= (addr & 0xf) << LOG_ADDR_SHIFT;
	writel(reg, cec->reg + CEC_CR0);

	cec->log_addr = addr;

	return 0;
}

static int rtk_cec_adap_transmit(struct cec_adapter *adap, u8 attempts,
				 u32 signal_free_time, struct cec_msg *msg)
{
	struct rtk_cec_dev *cec = adap->priv;
	unsigned int txfifo[TX_FIFO_NUM];
	unsigned int reg;
	int remain;
	int i;
	int len;

	len = msg->len - 1;

	remain = TX_FIFO_CNT - (readl(cec->reg + CEC_TXCR0) & TX_FIFO_CNT);

	if (msg->len > remain) {
		dev_err(cec->dev, "tx fifo not enougth");
		return -1;
	}

	rtk_cec_set_retries(cec, attempts);

	rtk_cec_tx_reset(cec);

	memcpy(txfifo, (msg->msg + 1), len);
	for (i = 0; i < len; i += 4)
		writel(__cpu_to_be32(txfifo[i >> 2]), cec->reg + CEC_TXDR1 + i);

	writel(ADD_CNT | len, cec->reg + CEC_TXDR0);

	reg = TX_ADDR_EN | (cec->log_addr << TX_LOG_ADDR_SHIFT)
		| ((msg->msg[0] & 0xf) << TX_DEST_ADDR_SHIFT)
		| TX_EN | TX_INT_EN;
	writel(reg, cec->reg + CEC_TXCR0);

	return 0;
}

static irqreturn_t rtk_cec_irq_handler(int irq, void *priv)
{
	struct rtk_cec_dev *cec = priv;
	unsigned int reg;

	dev_dbg(cec->dev, "irq received\n");

	reg = readl(cec->reg + CEC_TXCR0);
	if (reg & TX_INT) {
		if (reg & TX_EOM) {
			cec->tx = STATE_DONE;
		} else {
			dev_dbg(cec->dev, "tx transfer error\n");
			cec->tx = STATE_ERROR;
		}
		writel(reg, cec->reg + CEC_TXCR0);
	}

	reg = readl(cec->reg + CEC_RXCR0);
	if (reg & RX_INT) {
		if (reg & RX_EN) {
			dev_dbg(cec->dev, "over rx msg fifo\n");
			cec->rx = STATE_ERROR;
		} else if (reg & RX_EOM) {
			reg = readl(cec->reg + CEC_RXCR0);
			cec->msg.len = reg & 0x1F;
			cec->msg.rx_status = CEC_RX_STATUS_OK;
			rtk_cec_get_rx_buf(cec, cec->msg.len, cec->msg.msg);
			cec->rx = STATE_DONE;
		}
		rtk_cec_rx_reset(cec);
		rtk_cec_rx_enable(cec);
	}
	return IRQ_WAKE_THREAD;
}

static irqreturn_t rtk_cec_irq_handler_thread(int irq, void *priv)
{
	struct rtk_cec_dev *cec = priv;

	switch (cec->tx) {
	case STATE_DONE:
		cec_transmit_done(cec->adap, CEC_TX_STATUS_OK, 0, 0, 0, 0);
		cec->tx = STATE_IDLE;
		break;
	case STATE_ERROR:
		cec_transmit_done(cec->adap, CEC_TX_STATUS_MAX_RETRIES |
				CEC_TX_STATUS_ERROR, 0, 0, 0, 1);
		cec->tx = STATE_IDLE;
		break;
	case STATE_IDLE:
		break;
	default:
		dev_err(cec->dev, "can't handle this tx state\n");
		break;
	}

	switch (cec->rx) {
	case STATE_DONE:
		cec_received_msg(cec->adap, &cec->msg);
		cec->rx = STATE_IDLE;
		break;
	default:
		break;
	}

	return IRQ_HANDLED;
}

static const struct cec_adap_ops rtk_cec_adap_ops = {
	.adap_enable = rtk_cec_adap_enable,
	.adap_log_addr = rtk_cec_adap_log_addr,
	.adap_transmit = rtk_cec_adap_transmit,
};

static int rtk_cec_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct rtk_cec_dev *cec;
	int ret;

	cec = devm_kzalloc(&pdev->dev, sizeof(*cec), GFP_KERNEL);
	if (!cec)
		return -ENOMEM;

	cec->dev = dev;

	cec->irq = platform_get_irq(pdev, 0);
	if (cec->irq < 0)
		return cec->irq;

	ret = devm_request_threaded_irq(dev, cec->irq, rtk_cec_irq_handler,
					rtk_cec_irq_handler_thread, 0,
					pdev->name, cec);
	if (ret)
		return ret;

	cec->clk_cbus_osc = devm_clk_get(dev, "cbus_osc");
	if (IS_ERR(cec->clk_cbus_osc))
		return PTR_ERR(cec->clk_cbus_osc);

	cec->clk_cbus_sys = devm_clk_get(dev, "cbus_sys");
	if (IS_ERR(cec->clk_cbus_sys))
		return PTR_ERR(cec->clk_cbus_sys);

	cec->clk_cbus_tx = devm_clk_get(dev, "cbustx_sys");
	if (IS_ERR(cec->clk_cbus_tx))
		return PTR_ERR(cec->clk_cbus_tx);

	cec->rstc_cbus = devm_reset_control_get_shared(dev, "cbus");
	if (IS_ERR(cec->rstc_cbus))
		return PTR_ERR(cec->rstc_cbus);

	cec->rstc_cbus_tx = devm_reset_control_get_shared(dev, "cbustx");
	if (IS_ERR(cec->rstc_cbus_tx))
		return PTR_ERR(cec->rstc_cbus_tx);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	cec->reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(cec->reg))
		return PTR_ERR(cec->reg);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	cec->wrapper = devm_ioremap_resource(dev, res);
	if (IS_ERR(cec->wrapper))
		return PTR_ERR(cec->wrapper);

	cec->adap = cec_allocate_adapter(&rtk_cec_adap_ops, cec, CEC_NAME,
		CEC_CAP_PHYS_ADDR | CEC_CAP_LOG_ADDRS | CEC_CAP_TRANSMIT |
		CEC_CAP_PASSTHROUGH | CEC_CAP_RC,
		1, &pdev->dev);
	ret = PTR_ERR_OR_ZERO(cec->adap);
	if (ret)
		return ret;

	ret = cec_register_adapter(cec->adap);
	if (ret)
		goto err_delete_adapter;

	platform_set_drvdata(pdev, cec);

	clk_prepare_enable(cec->clk_cbus_osc);
	clk_prepare_enable(cec->clk_cbus_sys);
	clk_prepare_enable(cec->clk_cbus_tx);

	reset_control_deassert(cec->rstc_cbus);
	reset_control_deassert(cec->rstc_cbus_tx);

	return 0;

err_delete_adapter:
	cec_delete_adapter(cec->adap);
	return ret;
}

static int rtk_cec_remove(struct platform_device *pdev)
{
	struct rtk_cec_dev *cec = platform_get_drvdata(pdev);

	cec_unregister_adapter(cec->adap);
	pm_runtime_disable(&pdev->dev);
	return 0;
}

static const struct of_device_id rtk_cec_match[] = {
	{
		.compatible	= "Realtek,rtk-cec",
	},
	{},
};
MODULE_DEVICE_TABLE(of, rtk_cec_match);

static struct platform_driver rtk_cec_pdrv = {
	.probe	= rtk_cec_probe,
	.remove	= rtk_cec_remove,
	.driver	= {
		.name		= CEC_NAME,
		.of_match_table	= rtk_cec_match,
	},
};
module_platform_driver(rtk_cec_pdrv);

MODULE_AUTHOR("Simon HSU <simon_hsu@realtek.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek HDMI CEC driver");
