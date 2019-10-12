/*
 * Realtek I2C driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */


#include <linux/kernel.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/arm-smccc.h>
#include <asm/irq.h>

#include "i2c-rtk-priv.h"

#ifdef CONFIG_I2C_RTK_SECURE_ACCESS
extern bool secure_dvfs_is_disabled(void);

static void swc_write(unsigned int address, unsigned int value)
{
	struct arm_smccc_res res;

	arm_smccc_smc(0x8400ff0a, value, 0, 0, 0, 0, 0, 0, &res);
//	ta_hdcp_lib_set_i2c_enable(value);
}

void SET_IC_ENABLE(struct rtk_i2c_handler *handler, int value)
{
	if (handler->id == 0 && !secure_dvfs_is_disabled())
		smc_write(handler->reg_map.IC_ENABLE, value);
	else
		wr_reg(handler->reg_map.IC_ENABLE, value);
}
#endif
/*
 * Func : rtk_i2c_init
 * Desc : init rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : 0
 */
int rtk_i2c_handler_init(struct rtk_i2c_handler *handler)
{
	RTK_DEBUG("%s\n", __func__);

#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
//	if (handler->id == 0)
//		ta_i2c_init();
#endif
#if 0
	if (handler->flags & RTK_I2C_IRQ_RDY)
		return 0;

	if (rtk_i2c_probe(handler) < 0)
		return -ENODEV;

	ret = request_irq(handler->irq, rtk_i2c_isr, SA_SHIRQ, "i2c",
		(void *) handler);
	if (ret < 0) {
		pr_err("FATAL: Request irq %d failed(ret=%d)\n",
			handler->irq, ret);
		return -ENODEV;
	}
#endif

	handler->flags = RTK_I2C_IRQ_RDY;
	handler->rx_fifo_depth =
		((GET_IC_COMP_PARAM_1(handler) >>  8) & 0xFF) + 1;
	handler->tx_fifo_depth =
		((GET_IC_COMP_PARAM_1(handler) >> 16) & 0xFF) + 1;
	init_waitqueue_head(&handler->wq);

	spin_lock_init(&handler->lock);

	return rtk_i2c_phy_init(handler);
}

/*
 * Func : rtk_i2c_uninit
 * Desc : uninit rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : 0
 */
int rtk_i2c_handler_uninit(struct rtk_i2c_handler *handler)
{
	RTK_DEBUG("%s\n", __func__);

	SET_IC_ENABLE(handler, 0);
	SET_IC_INTR_MASK(handler, 0);

	if ((handler->flags & RTK_I2C_IRQ_RDY)) {
		free_irq(handler->irq, handler);
		handler->flags = 0;
	}

	return 0;
}

/*
 * Func : rtk_i2c_phy_init
 * Desc : init rtk i2c phy
 * Parm : handler : handle of rtk i2c
 * Retn : 0
 */
int rtk_i2c_phy_init(struct rtk_i2c_handler *handler)
{
	RTK_DEBUG("%s\n", __func__);

	SET_IC_ENABLE(handler, 0);
	SET_IC_INTR_MASK(handler, 0); /* disable all interrupt*/
	SET_IC_CON(handler,
		IC_SLAVE_DISABLE | IC_RESTART_EN | SPEED_SS | IC_MASTER_MODE);
	SET_IC_TX_TL(handler, FIFO_THRESHOLD);
	SET_IC_RX_TL(handler, handler->rx_fifo_depth - FIFO_THRESHOLD);
	handler->set_spd(handler, handler->spd);

#ifdef DEV_DEBUG
	rtk_i2c_dump(handler);
#endif
	return 0;
}

/*
 * Func : rtk_i2c_set_spd
 * Desc : set speed of rtk i2c
 * Parm : handler:handle of rtk i2c
 *	KHz:operation speed of i2c
 * Retn : 0
 */
int rtk_i2c_set_spd(struct rtk_i2c_handler *handler, int KHz)
{
	unsigned int scl_time;
	unsigned int div_h;
	unsigned int div_l;
	unsigned long sda_del;
	unsigned int clk_time;

	RTK_DEBUG("%s\n", __func__);

#ifdef CONFIG_ARCH_RTD16xx
	if (handler->id == 0) {
		if (KHz < 10 || KHz > 3400) {
			pr_err("[I2C%d] warning, speed %d out of range,",
				handler->id, KHz);
			pr_err("speed should between 10 ~ 3400KHz\n");
			return -1;
		}
	} else {
		if (KHz < 10 || KHz > 800) {
			pr_err("[I2C%d] warning, speed %d out of range,",
				handler->id, KHz);
			pr_err("speed should between 10 ~ 800KHz\n");
			return -1;
		}
	}
#else
	if (KHz < 10 || KHz > 800) {
		pr_err("[I2C%d] warning, speed %d out of range,",
			handler->id, KHz);
		pr_err("speed should between 10 ~ 800KHz\n");
		return -1;
	}
#endif

	clk_time = 37; /*27MHZ*/

	scl_time = (1000000 / KHz) / 2; /* the time ns need for SCL high/low */
	if (scl_time % clk_time) {
		if ((scl_time % clk_time) > clk_time / 2)
			scl_time += (clk_time - (scl_time % clk_time));
		else
			scl_time -= (scl_time % clk_time);
	}

	/*
	 * 27MHz crystal generate one clock 37ns,
	 * 108MHz crystal generate one clock 9ns,
	 * for synopsys design ware ip v1.14a, SCL_LCNT need -1,
	 * SCL_HCNT need -8, 400KHz SCL Low required min 1.3 us
	 */

#ifdef CONFIG_ARCH_RTD16xx

	if (handler->id == 0) {
		if (KHz == 100){
			div_h = 524;
			div_l = 531;
		} else if (KHz == 400){
			div_h = 119;
			div_l = 126;
		} else if (KHz == 3400) {
			div_h = 7;
			div_l = 15;
		}
	} else {
		if (KHz < 400) {
			div_h = (scl_time / clk_time) - 8;
			div_l = (scl_time / clk_time) - 1;
		} else {
			div_h = 25;
			div_l = 32;
		}
	}

#else
	if (KHz < 400) {
		div_h = (scl_time / clk_time) - 8;
		div_l = (scl_time / clk_time) - 1;
	} else {
		div_h = 24;
		div_l = 34;
	}

	if (div_h >= 0xFFFF || div_h == 0 || div_l >= 0xFFFF || div_l == 0) {
		pr_err("[I2C%d] fatal, set speed failed : ", handler->id);
		pr_err("divider divider out of range.");
		pr_err("div_h = %d, div_l = %d\n", div_h, div_l);
		return -1;
	}

#endif

	RTK_DEBUG("[I2C%d] KHz = %d, div_h = %d, div_l = %d\n",
		handler->id, KHz, div_h, div_l);


	SET_IC_ENABLE(handler, 0);

	if (KHz <= 100) {
		SET_IC_CON(handler, (GET_IC_CON(handler) &
			(~IC_SPEED)) | SPEED_SS);
		SET_IC_SS_SCL_HCNT(handler, div_h);
		SET_IC_SS_SCL_LCNT(handler, div_l);
	} else if(KHz == 400) {
		SET_IC_CON(handler, (GET_IC_CON(handler) &
			(~IC_SPEED)) | SPEED_FS);
		SET_IC_FS_SCL_HCNT(handler, div_h);
		SET_IC_FS_SCL_LCNT(handler, div_l);
	} else if (KHz == 3400) {
		SET_IC_CON(handler, (GET_IC_CON(handler) &
			(~IC_SPEED)) | SPEED_HS);
		SET_IC_HS_SCL_HCNT(handler, div_h);
		SET_IC_HS_SCL_LCNT(handler, div_l);
	}

	handler->spd = KHz;
	/*Todo: Fix tick for 3.4MHz*/
	handler->tick = 1000 / KHz;

	/*Set SDA delay time */
	if (KHz == 3400) { /*disabled sda_del*/
		sda_del = 0x0;
	} else {
		sda_del = GET_IC_SDA_DEL(handler) & ~I2C_SDA_DEL_MASK;
		sda_del |= I2C_SDA_DEL_EN | I2C_SDA_DEL_SEL(SDA_DEL_518NS);
	}
	SET_IC_SDA_DEL(handler, sda_del);

	return 0;
}

/**
 * Func : rtk_i2c_set_tar
 * Desc : set tar of rtk i2c
 * Parm : handler : handle of rtk i2c
 *	addr : address of sar
 *	mode : mode of sar
 * Retn : 0
 */
int rtk_i2c_set_tar(struct rtk_i2c_handler *handler, unsigned short addr,
	enum ADDR_MODE mode)
{
	RTK_DEBUG("%s\n", __func__);

	if (mode == ADDR_MODE_10BITS) {
		if (addr > ADDR_10BITS_MASK)
			return -EADDROVERRANGE;

		SET_IC_ENABLE(handler, 0);
		SET_IC_TAR(handler, addr & ADDR_10BITS_MASK);
		SET_IC_CON(handler, (GET_IC_CON(handler) &
			(~IC_10BITADDR_MASTER)) | IC_10BITADDR_MASTER);
	} else {
		if (addr > ADDR_7BITS_MASK)
			return -EADDROVERRANGE;

		SET_IC_ENABLE(handler, 0);
		SET_IC_TAR(handler, addr & ADDR_7BITS_MASK);
		SET_IC_CON(handler, GET_IC_CON(handler) &
			(~IC_10BITADDR_MASTER));
	}

	handler->tar = addr;
	handler->tar_mode = mode;

	return 0;
}

/*
 * Func : rtk_i2c_set_guard_interval
 * Desc : set guard_interval of rtk i2c
 * Parm : handler : handle of rtk i2c
 *		us : operation speed of i2c
 * Retn : 0
 */
int rtk_i2c_set_guard_interval(struct rtk_i2c_handler *handler,
	unsigned long us)
{
	RTK_DEBUG("%s\n", __func__);
	handler->guard_interval = us;
	return 0;
}

/*
 * Func : rtk_i2c_read
 * Desc : read data from sar
 * Parm : handler : handle of rtk i2c
 * Retn : 0 for success, others is failed
 */
int rtk_i2c_read(struct rtk_i2c_handler *handler,
	unsigned char *tx_buf, unsigned short tx_buf_len,
	unsigned char *rx_buf, unsigned short rx_buf_len)
{
	int retry = 2;
	unsigned int ret = 0;

	RTK_DEBUG("%s\n", __func__);

	while (retry > 0) {
		rtk_i2c_load_message(handler,
			tx_buf_len ? I2C_MASTER_RANDOM_READ : I2C_MASTER_READ,
			tx_buf, tx_buf_len,
			rx_buf, rx_buf_len, 0);

		ret = rtk_i2c_start_xfer(handler);
		if (ret != -ETIMEOUT)
			break;

		/*JAM_DEBUG("[I2C] read timeout detected, do retry\n");*/
		retry--;
	}

	return ret;
}

/*
 * Func : rtk_i2c_write
 * Desc : write data to sar
 * Parm : handler : handle of rtk i2c
 *	tx_buf : data to write
 *	tx_buf_len : number of bytes to write
 *	wait_stop  : wait for stop of not (extension)
 * Retn : 0 for success, others is failed
 */
int rtk_i2c_write(struct rtk_i2c_handler *handler, unsigned char *tx_buf,
	unsigned short tx_buf_len, unsigned char wait_stop)
{
	int retry = 2;
	unsigned int ret = 0;

	RTK_DEBUG("%s\n", __func__);

	while (retry > 0) {
		rtk_i2c_load_message(handler, I2C_MASTER_WRITE, tx_buf,
			tx_buf_len, NULL, 0, (wait_stop) ? 0 : I2C_NO_STOP);

		ret = rtk_i2c_start_xfer(handler);

		if (ret != -ETIMEOUT)
			break;

		retry--;
	}

	return ret;
}

/*
 * Func : rtk_i2c_load_message
 * Desc : load a i2c message (just add this message to the queue)
 * Parm : handler : handle of rtk i2c
 * Retn : 0 for success, others is failed
 */
int rtk_i2c_load_message(struct rtk_i2c_handler *handler,
		unsigned char mode, unsigned char *tx_buf,
		unsigned short tx_buf_len, unsigned char *rx_buf,
		unsigned short rx_buf_len, unsigned char xfer_flags)
{
	unsigned long flags;

	RTK_DEBUG("%s\n", __func__);

	LOCK_RTK_I2C(&handler->lock, flags);

	memset(&handler->xfer, 0, sizeof(handler->xfer));

	handler->xfer.mode = mode;
	handler->xfer.flags = xfer_flags;
	handler->xfer.tx_buff = tx_buf;
	handler->xfer.tx_buff_len = tx_buf_len;
	handler->xfer.tx_len = 0;
	handler->xfer.rx_buff = rx_buf;
	handler->xfer.rx_buff_len = rx_buf_len;
	handler->xfer.rx_len = 0;
	handler->xfer.except_time =
		((tx_buf_len + rx_buf_len + 2) * 9 * handler->tick);

	if (rx_buf && rx_buf_len)
		memset(rx_buf, 0, rx_buf_len);

	//handler->xfer.gpio_xfer_state = G2C_ST_START;
	//handler->xfer.gpio_xfer_sub_state = 0;

	UNLOCK_RTK_I2C(&handler->lock, flags);

#ifdef DEV_DEBUG
	{
		int i;

		pr_info("%s xfer.mode = %x\n",
			__func__, handler->xfer.mode);
		pr_info("%s xfer.flags= 0x%x\n",
			__func__, handler->xfer.flags);

		if (handler->xfer.tx_buff_len) {
			for (i = 0; i < handler->xfer.tx_buff_len; i++) {
				pr_info("%s xfer.tx_buff= 0x%x\n",
					__func__, *handler->xfer.tx_buff);
				pr_info("%s xfer.tx_buff= 0x%x\n",
					__func__, handler->xfer.tx_buff[i]);
			}
		}

		pr_info("%s xfer.tx_buff_len= 0x%x\n",
			__func__, handler->xfer.tx_buff_len);
		pr_info("%s xfer.tx_len= 0x%x\n",
			__func__, handler->xfer.tx_len);

		if (handler->xfer.rx_buff_len) {
			for (i = 0; i < handler->xfer.rx_buff_len; i++) {
				pr_info("%s xfer.rx_buff= 0x%x\n",
					__func__, *handler->xfer.rx_buff);
				pr_info("%s xfer.rx_buff= 0x%x\n",
					__func__, handler->xfer.rx_buff[i]);
			}
		}

		pr_info("%s xfer.rx_buff_len= 0x%x\n",
			__func__, handler->xfer.rx_buff_len);
		pr_info("%s xfer.rx_len= 0x%x\n",
			__func__, handler->xfer.rx_len);
		pr_info("%s xfer.except_time= 0x%lx\n",
			__func__, handler->xfer.except_time);
	}
#endif

	return 0;
}

/*
 * Func : rtk_i2c_start_xfer
 * Desc : start xfer message
 * Parm : handler : handle of rtk i2c
 * Retn : 0 for success, others is failed
 */
int rtk_i2c_start_xfer(struct rtk_i2c_handler *handler)
{
	unsigned long flags;
	unsigned int ret;
	int mode = handler->xfer.mode;

	RTK_DEBUG("%s\n", __func__);

	LOG_EVENT(EVENT_START_XFER);

	LOCK_RTK_I2C(&handler->lock, flags);

	if ((GET_IC_CON(handler) & IC_SLAVE_DISABLE) == 0) {
		SET_IC_ENABLE(handler, 0);
		SET_IC_CON(handler, GET_IC_CON(handler) | IC_SLAVE_DISABLE);
	}

	switch (handler->xfer.mode) {
	case I2C_MASTER_WRITE:
		SET_IC_INTR_MASK(handler,
			TX_EMPTY_BIT | TX_ABRT_BIT | STOP_DET_BIT);
		break;
	case I2C_MASTER_READ:
	case I2C_MASTER_RANDOM_READ:
		if (GET_IC_RXFLR(handler)) {
			pr_info("WARNING, RX FIFO NOT EMPRY\n");

			while (GET_IC_RXFLR(handler))
				GET_IC_DATA_CMD(handler);
		}
		SET_IC_INTR_MASK(handler,
			RX_FULL_BIT | TX_EMPTY_BIT | TX_ABRT_BIT |
			STOP_DET_BIT);
		break;
	default:
		UNLOCK_RTK_I2C(&handler->lock, flags);
		LOG_EVENT(EVENT_STOP_XFER);
		return -EILLEGALMSG;
	}

	if (handler->reg_map.I2C_ISR_EN)
		wr_reg(handler->reg_map.I2C_ISR_EN,
			rd_reg(handler->reg_map.I2C_ISR_EN) |
			handler->reg_map.I2C_ISR_EN_MASK);

#ifdef MINIMUM_DELAY_EN
	UNLOCK_RTK_I2C(&handler->lock, flags);

	/* cfyeh found that delay 1/2 tick will cause long
	 * system booting time, so we revert the delay setting
	 * temporarily until we findout the root cause
	 */
	if (time_after(jiffies, handler->time_stamp)) {
		// udelay(handler->tick/2); /* wait 1/2 ticks */
		udelay(handler->guard_interval);
	}

	LOCK_RTK_I2C(&handler->lock, flags);
#endif

	SET_IC_ENABLE(handler, 1); /* Start Xfer */
	UNLOCK_RTK_I2C(&handler->lock, flags);

	/* less than 1 ms */
	if (handler->xfer.except_time < 1000) {
		/* extra 20 us for extra guard interval */
		udelay(handler->xfer.except_time + 20);
	}

	if (handler->xfer.mode != I2C_IDLE)
		wait_event_timeout(handler->wq,
			handler->xfer.mode == I2C_IDLE, 1 * HZ);

	LOCK_RTK_I2C(&handler->lock, flags);

	SET_IC_INTR_MASK(handler, 0);
	SET_IC_ENABLE(handler, 0);

	if (handler->xfer.mode != I2C_IDLE) {
		handler->xfer.ret  = -ETIMEOUT;

	} else if (handler->xfer.ret == -ECMDSPLIT) {
		pr_warn("WARNING,");
		switch (mode) {
		case I2C_MASTER_WRITE:
			pr_warn("Write Cmd Split, tx : %d/%d\n",
				handler->xfer.tx_len,
				handler->xfer.tx_buff_len);
			break;
		case I2C_MASTER_READ:
			pr_warn("Read Cmd Split, tx : %d/%d rx : %d/%d\n",
				handler->xfer.tx_len,
				handler->xfer.tx_buff_len,
				handler->xfer.rx_len,
				handler->xfer.rx_buff_len);
			break;
		case I2C_MASTER_RANDOM_READ:
			ret = handler->xfer.tx_buff_len +
				handler->xfer.rx_buff_len;
			pr_warn("Read Cmd Split, tx : %d/%d rx : %d/%d\n",
				handler->xfer.tx_len,
				ret,
				handler->xfer.rx_len,
				handler->xfer.rx_buff_len);
			break;
		default:
			break;
		}
	}

#ifdef MINIMUM_DELAY_EN
	handler->time_stamp = (unsigned long) jiffies;
#endif

	ret = handler->xfer.ret;

	UNLOCK_RTK_I2C(&handler->lock, flags);

#ifndef MINIMUM_DELAY_EN
	udelay(handler->guard_interval);
#endif

	LOG_EVENT(EVENT_STOP_XFER);

	if (handler->flags & RTK_I2C_SLAVE_ENABLE)
		handler->slave_mode_enable(handler, 1);

	return ret;
}

/*
 * Func : rtk_i2c_get_tx_abort_reason
 * Desc : get reason of tx abort, this register will be clear when new
 *	message is loaded
 * Parm : handler : handle of rtk i2c
 * Retn : tx about source
 */
unsigned int rtk_i2c_get_tx_abort_reason(struct rtk_i2c_handler *handler)
{
	RTK_DEBUG("%s\n", __func__);
	return handler->xfer.tx_abort_source;
}


/*
 * Func : rtk_i2c_master_write
 * Desc : master write handler for rtk i2c
 * Parm : handler : handle of rtk i2c
 *		event  : INT event of rtk i2c
 * Retn : N/A
 */
void rtk_i2c_master_write(struct rtk_i2c_handler *handler, unsigned int event,
	unsigned int tx_abort_source)
{
#define TxComplete() (handler->xfer.tx_len >= handler->xfer.tx_buff_len)

	RTK_DEBUG("%s\n", __func__);

	while (!TxComplete() && NOT_TXFULL(handler)) {
		if (handler->xfer.tx_len == handler->xfer.tx_buff_len - 1) {
			SET_IC_DATA_CMD(handler,
				handler->xfer.tx_buff[handler->xfer.tx_len++] |
				(0x1 << 9));
		} else {
			SET_IC_DATA_CMD(handler,
				handler->xfer.tx_buff[handler->xfer.tx_len++]);
		}
	}

	if (TxComplete())
		SET_IC_INTR_MASK(handler,
			GET_IC_INTR_MASK(handler) & ~TX_EMPTY_BIT);

	if (event & TX_ABRT_BIT) {
		handler->tx_abort_flag = 1;
		handler->xfer.tx_abort_source = tx_abort_source;
	} else if (event & STOP_DET_BIT) {
		if (handler->tx_abort_flag != 1) {
			handler->xfer.ret =
				TxComplete() ? handler->xfer.tx_len : -ECMDSPLIT;
		} else {
			handler->tx_abort_flag = 0;
			handler->xfer.ret = -ETXABORT;
		}
	}

	if (handler->xfer.ret) {
		SET_IC_INTR_MASK(handler, 0);
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
		SET_IC_ENABLE(handler, 0);
#endif
		handler->xfer.mode = I2C_IDLE; /* change to idle state */
		wake_up(&handler->wq);
	}

#undef TxComplete
}

/*
 * Func : rtk_i2c_master_read
 * Desc : master read handler for rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : N/A
 */
void rtk_i2c_master_read(struct rtk_i2c_handler *handler, unsigned int event,
	unsigned int tx_abort_source)
{
#define TxComplete() (handler->xfer.tx_len >= handler->xfer.rx_buff_len)
#define RxComplete() (handler->xfer.rx_len >= handler->xfer.rx_buff_len)

	RTK_DEBUG("%s\n", __func__);

	/* TX Thread */
	while (!TxComplete() && NOT_TXFULL(handler)) {
		if (handler->xfer.tx_len ==
			((handler->xfer.rx_buff_len +
			handler->xfer.tx_buff_len) - 1)) {
			/* send stop command to rx fifo */
			SET_IC_DATA_CMD(handler, (READ_CMD | (0x1 << 9)));
		} else {
			/* send read command to rx fifo*/
			SET_IC_DATA_CMD(handler, READ_CMD);
		}

		handler->xfer.tx_len++;
		while (!RxComplete() && NOT_RXEMPTY(handler))
			handler->xfer.rx_buff[handler->xfer.rx_len++] =
				(unsigned char)(GET_IC_DATA_CMD(handler) &
				0xFF);
	}

	/* RX Thread */
	while (!RxComplete() && NOT_RXEMPTY(handler))
		handler->xfer.rx_buff[handler->xfer.rx_len++] =
			(unsigned char)(GET_IC_DATA_CMD(handler) & 0xFF);

	if (TxComplete())
		SET_IC_INTR_MASK(handler,
			GET_IC_INTR_MASK(handler) & ~TX_EMPTY_BIT);

	if (event & TX_ABRT_BIT) {
		handler->tx_abort_flag =1;
		handler->xfer.tx_abort_source = tx_abort_source;
	} else if ((event & STOP_DET_BIT) || RxComplete()) {
		SET_IC_INTR_MASK(handler,
			GET_IC_INTR_MASK(handler) & ~RX_FULL_BIT);
		if (handler->tx_abort_flag != 1) {
			handler->xfer.ret =
				RxComplete() ? handler->xfer.rx_len : -ECMDSPLIT;
		} else {
			handler->tx_abort_flag = 0;
			handler->xfer.ret = -ETXABORT;
		}
	}

	if (handler->xfer.ret  && (handler->xfer.ret!=-ETXABORT)) {
		SET_IC_INTR_MASK(handler, 0);
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
		SET_IC_ENABLE(handler, 0);
#endif
		handler->xfer.mode = I2C_IDLE; /* change to idle state */
		wake_up(&handler->wq);
	}

#undef TxComplete
#undef RxComplete
}

/*
 * Func : rtk_i2c_master_random_read
 * Desc : master random read handler for rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : N/A
 */
void rtk_i2c_master_random_read(struct rtk_i2c_handler *handler,
	unsigned int event, unsigned int tx_abort_source)
{
/* it should add the same number of read command to tx fifo */
#define TxComplete() \
(handler->xfer.tx_len >= \
(handler->xfer.rx_buff_len + handler->xfer.tx_buff_len))
#define RxComplete() (handler->xfer.rx_len >=  handler->xfer.rx_buff_len)

	RTK_DEBUG("%s\n", __func__);

	/* TX Thread  */
	while (!TxComplete() && NOT_TXFULL(handler)) {
		if (handler->xfer.tx_len < handler->xfer.tx_buff_len) {
			SET_IC_DATA_CMD(handler,
				handler->xfer.tx_buff[handler->xfer.tx_len]);
		} else {
			if ((handler->xfer.tx_len == handler->xfer.tx_buff_len)
				&& (handler->xfer.tx_len ==
				((handler->xfer.rx_buff_len +
				handler->xfer.tx_buff_len) - 1))) {
				/* send Restart command and STOP to rx fifo :
				 * first also last read cmd
				 */
				SET_IC_DATA_CMD(handler,
					(READ_CMD | (0x3 << 9)));
			} else if ((handler->xfer.tx_len ==
					(handler->xfer.tx_buff_len)) &&
					(!(handler->xfer.tx_len ==
					((handler->xfer.rx_buff_len +
					handler->xfer.tx_buff_len) - 1)))) {
				/* send restart command to rx fifo :
				 * first but not last read cmd
				 */
				SET_IC_DATA_CMD(handler,
					(READ_CMD | (0x1 << 10)));
			} else if ((!(handler->xfer.tx_len ==
					(handler->xfer.tx_buff_len))) &&
					(handler->xfer.tx_len ==
					((handler->xfer.rx_buff_len +
					handler->xfer.tx_buff_len) - 1))) {
				/* send stop command to rx fifo :
				 * not first but last read cmd
				 */
				SET_IC_DATA_CMD(handler,
					(READ_CMD | (0x1 << 9)));
			} else {
				/* send read command to rx fifo :
				 * not first also not last read cmd
				 */
				SET_IC_DATA_CMD(handler, READ_CMD);
			}
		}

		handler->xfer.tx_len++;

		/* RX Thread,
		 * incase rxfifo overflow and the datas are droped
		 */
		while (!RxComplete() && NOT_RXEMPTY(handler)) {
			RTK_DEBUG("%s handler->xfer.rx_len =%d\n",
				__func__, handler->xfer.rx_len);
			handler->xfer.rx_buff[handler->xfer.rx_len++] =
				(unsigned char)(GET_IC_DATA_CMD(handler) &
				0xFF);
		}
	}

	/* RX Thread */
	while (!RxComplete() && NOT_RXEMPTY(handler))
		handler->xfer.rx_buff[handler->xfer.rx_len++] =
			(unsigned char)(GET_IC_DATA_CMD(handler) & 0xFF);

	if (TxComplete())
		SET_IC_INTR_MASK(handler,
			GET_IC_INTR_MASK(handler) & ~TX_EMPTY_BIT);

	if (event & TX_ABRT_BIT) {
		handler->tx_abort_flag =1;
		handler->xfer.tx_abort_source = tx_abort_source;
	} else if ((event & STOP_DET_BIT) || RxComplete()) {
		SET_IC_INTR_MASK(handler,
			GET_IC_INTR_MASK(handler) & ~RX_FULL_BIT);
		if (handler->tx_abort_flag != 1) {
			handler->xfer.ret =
				RxComplete() ? handler->xfer.rx_len : -ECMDSPLIT;
		} else {
			handler->tx_abort_flag = 0;
			handler->xfer.ret = -ETXABORT;
		}
	}

	if (handler->xfer.ret) {
		SET_IC_INTR_MASK(handler, 0);
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
		SET_IC_ENABLE(handler, 0);
#endif
		handler->xfer.mode = I2C_IDLE; /* change to idle state */
		wake_up(&handler->wq);
	}

#undef TxComplete
#undef RxComplete
}

#ifdef EDID_4BLOCK_SUPPORT

/*
 * Func : rtk_i2c_read_edid_seg
 * Desc : read edid seg
 * Parm : Block 0~1: Seg 0
 *	Block 2: Seg 1, Offset 0
 *	Block 3: Seg 1, Offset 128
 * Retn : 0 for success, others is failed
 */
int rtk_i2c_read_edid_seg(struct rtk_i2c_handler *handler,
	unsigned char seg, /* Segment Pointer */
	unsigned char offset, /* Word Offset */
	unsigned char *rx_buff, unsigned short rx_buf_len)
{
#define RxComplete() (rx_len >= rx_buf_len)
#define TxComplete() (tx_len >= rx_buf_len)

	int rx_len = 0;
	int tx_len = 0;
	int cnt = 0;

	RTK_DEBUG("%s seg=0x%x offset=0x%02x len(%u)\n",
		__func__, seg, offset, rx_buf_len);

	rtk_i2c_set_tar(handler, 0x30, ADDR_MODE_7BITS);
	CLR_IC_INTR(handler);
	SET_IC_ENABLE(handler, 1);

	while (GET_IC_STATUS(handler) & (ST_ACTIVITY_BIT == 0)) {
		if (cnt++ < 5)
			udelay(50);
		else
			return -ETIMEOUT;

		RTK_DEBUG("%s IC_STATUS = 0x%x\n",
			__func__, GET_IC_STATUS(handler));
	}

	SET_IC_DATA_CMD(handler, seg); /* Segment Pointer */
	udelay(50);
	CLR_IC_INTR(handler);
	SET_IC_ENABLE(handler, 0);

	rtk_i2c_set_tar(handler, 0x50, ADDR_MODE_7BITS);
	CLR_IC_INTR(handler);
	SET_IC_ENABLE(handler, 1);
	cnt = 0;

	while (GET_IC_STATUS(handler) & (ST_ACTIVITY_BIT == 0)) {
		if (cnt++ < 5)
			udelay(50);
		else
			return -ETIMEOUT;
	}

	SET_IC_DATA_CMD(handler, offset|(0x1<<10)); /* Restart, Word Offset */
	udelay(100);

	RTK_DEBUG("%s IC_STATUS= 0x%x\n", __func__, GET_IC_STATUS(handler));

	while (!TxComplete() && NOT_TXFULL(handler)) {

		if (tx_len == rx_buf_len - 1)
			/* Read, Stop */
			SET_IC_DATA_CMD(handler, (0x1 << 8) | (0x1 << 9));
		else
			/* Read */
			SET_IC_DATA_CMD(handler, (0x1 << 8));

		tx_len++;
		udelay(100);
		while (NOT_RXEMPTY(handler)) {
			rx_buff[rx_len] =
				(unsigned char)(GET_IC_DATA_CMD(handler) &
				0xFF);
			udelay(50);
			rx_len++;
		}
	}

	while (!RxComplete() && NOT_RXEMPTY(handler)) {
		rx_buff[rx_len] =
			(unsigned char)(GET_IC_DATA_CMD(handler) & 0xFF);
		rx_len++;
		udelay(50);
	}

	CLR_IC_INTR(handler);
	SET_IC_ENABLE(handler, 0);

	return 0;
}
#endif

/*
 * Func : rtk_i2c_isr
 * Desc : isr of rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : 0
 */
irqreturn_t rtk_i2c_isr(int this_irq, void *dev_id)
{
	struct rtk_i2c_handler *handler = (struct rtk_i2c_handler *) dev_id;
	unsigned long flags;
	unsigned int event = 0;
	unsigned int tx_abrt_source = 0;
	unsigned int tmp;

	RTK_DEBUG("%s\n", __func__);

#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
	LOCK_RTK_I2C(&handler->lock, flags);
#endif

	/* interrupt belongs to I2C */
	if (!(GET_I2C_ISR(handler) & handler->reg_map.I2C_INT)) {
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
		UNLOCK_RTK_I2C(&handler->lock, flags);
#endif
		return IRQ_NONE;
	}

	LOG_EVENT(EVENT_ENTER_ISR);

	event = GET_IC_INTR_STAT(handler);
	tx_abrt_source = GET_IC_TX_ABRT_SOURCE(handler);

	CLR_IC_INTR(handler); /* clear interrupts of i2c_x */

	if ((GET_IC_CON(handler) & IC_SLAVE_DISABLE) == 0) {
		while (NOT_RXEMPTY(handler) &&
			(handler->slave_rx_len <
			sizeof(handler->slave_rx_buffer))) {
			handler->slave_rx_buffer[handler->slave_rx_len++] =
				(unsigned char)(GET_IC_DATA_CMD(handler) &
				0xFF);
		}

		if ((event & STOP_DET_BIT) && handler->slave_rx_len) {
			if (handler->slave_ops.handle_command)
				handler->slave_ops.handle_command(
						handler->slave_id,
						handler->slave_rx_buffer,
						handler->slave_rx_len);

			handler->slave_rx_len = 0; /* flush buffer */
		}

		if (event & RD_REQ_BIT) {
			if (handler->slave_ops.read_data) {
				tmp = handler->slave_id;
				SET_IC_DATA_CMD(handler,
					handler->slave_ops.read_data(tmp));
			} else
				SET_IC_DATA_CMD(handler, 0xFF);
		}
	} else {
		switch (handler->xfer.mode) {
		case I2C_MASTER_WRITE:
			rtk_i2c_master_write(handler, event, tx_abrt_source);
			break;

		case I2C_MASTER_READ:
			rtk_i2c_master_read(handler, event, tx_abrt_source);
			break;

		case I2C_MASTER_RANDOM_READ:
			rtk_i2c_master_random_read(handler, event,
						tx_abrt_source);
			break;

		default:
			pr_info("Unexcepted Interrupt\n");
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
			SET_IC_ENABLE(handler, 0);
#endif
		}
	}

	/* clear I2C Interrupt Flag */
	SET_I2C_ISR(handler, handler->reg_map.I2C_INT);
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#else
	UNLOCK_RTK_I2C(&handler->lock, flags);
#endif
	return IRQ_HANDLED;
}

/*
 * Func : rtk_i2c_set_sar
 * Desc : set sar of rtk i2c
 * Parm : handler : handle of rtk i2c
 *	addr : address of sar
 *	mode : mode of sar
 * Retn : 0
 */
int rtk_i2c_set_sar(struct rtk_i2c_handler *handler,
	unsigned short addr, enum ADDR_MODE mode)
{
	RTK_DEBUG("%s\n", __func__);

	if (mode == ADDR_MODE_10BITS) {
		SET_IC_ENABLE(handler, 0);
		SET_IC_SAR(handler, handler->sar & ADDR_10BITS_MASK);
		SET_IC_CON(handler, GET_IC_CON(handler) | IC_10BITADDR_SLAVE);
	} else {
		SET_IC_ENABLE(handler, 0);
		SET_IC_SAR(handler, handler->sar & ADDR_7BITS_MASK);
		SET_IC_CON(handler, GET_IC_CON(handler) &
			(~IC_10BITADDR_SLAVE));
	}

	handler->sar = addr;
	handler->sar_mode = mode;

	return 0;
}

/*
 * Func : rtk_i2c_slave_mode_enable
 * Desc : enable/disable i2c slave mode
 * Parm : handler : handle of rtk i2c
 *	on : enable /disable
 * Retn : 0
 */
int rtk_i2c_slave_mode_enable(struct rtk_i2c_handler *handler,
	unsigned char on)
{
	unsigned long flags;

	RTK_DEBUG("%s\n", __func__);

	LOCK_RTK_I2C(&handler->lock, flags);

	if (on) {
		pr_info("[I2C%d] i2c slave enabled, sar=%x\n",
				handler->id, GET_IC_SAR(handler));
		SET_IC_ENABLE(handler, 0);
		handler->set_sar(handler, handler->sar, handler->sar_mode);
		SET_IC_CON(handler, GET_IC_CON(handler) & ~(IC_SLAVE_DISABLE));
		SET_IC_INTR_MASK(handler, START_DET_BIT |
				STOP_DET_BIT | RD_REQ_BIT | RX_FULL_BIT);
		if (handler->reg_map.I2C_ISR_EN)
			wr_reg(handler->reg_map.I2C_ISR_EN,
				rd_reg(handler->reg_map.I2C_ISR_EN) |
				handler->reg_map.I2C_ISR_EN_MASK);
		SET_IC_ENABLE(handler, 1);
		handler->flags |= RTK_I2C_SLAVE_ENABLE;
	} else {
		pr_info("[I2C%d] i2c slave disabled\n", handler->id);
		SET_IC_ENABLE(handler, 0);
		SET_IC_CON(handler, GET_IC_CON(handler) | IC_SLAVE_DISABLE);
		SET_IC_INTR_MASK(handler, 0);
		handler->flags &= ~RTK_I2C_SLAVE_ENABLE;
	}

	UNLOCK_RTK_I2C(&handler->lock, flags);

	return 0;
}

/*
 * Func : rtk_i2c_register_slave_ops
 * Desc : register slave mode ops
 * Parm : handler : handle of rtk i2c
 *		ops : slave mode ops
 * Retn : 0
 */
int rtk_i2c_register_slave_ops(struct rtk_i2c_handler *handler,
	struct rtk_i2c_slave_ops *ops, unsigned long id)
{
	unsigned long flags;

	RTK_DEBUG("%s\n", __func__);

	LOCK_RTK_I2C(&handler->lock, flags);

	if (ops == NULL) {
		handler->slave_ops.handle_command = NULL;
		handler->slave_ops.read_data = NULL;
		handler->slave_id = 0;
		rtk_i2c_slave_mode_enable(handler, 0);
	} else {
		handler->slave_ops.handle_command = ops->handle_command;
		handler->slave_ops.read_data = ops->read_data;
		handler->slave_id = id;
	}

	UNLOCK_RTK_I2C(&handler->lock, flags);
	return 0;
}

/*
 * Func : rtk_i2c_dump
 * Desc : dump staus of rtk i2c
 * Parm : handler : handle of rtk i2c
 * Retn : 0 for success
 */
int rtk_i2c_dump(struct rtk_i2c_handler *handler)
{
	RTK_DEBUG("%s\n", __func__);
	pr_info("=========================\n");
	pr_info("= VER : %s\n", VERSION);
	pr_info("=========================\n");
	pr_info("= PHY : %d\n", handler->id);
	//pr_info("= PORT: %ld\n", current_port_id(handler));
	pr_info("= MODEL: %s\n", handler->model_name);
	pr_info("= SPD : %d\n", handler->spd);
	pr_info("= SAR : 0x%03x (%d bits)\n",
			handler->sar, handler->sar_mode);
	pr_info("= TX FIFO DEPTH : %d\n", handler->tx_fifo_depth);
	pr_info("= RX FIFO DEPTH : %d\n", handler->rx_fifo_depth);
	pr_info("= FIFO THRESHOLD: %d\n", FIFO_THRESHOLD);
	pr_info("=========================\n");
	return 0;
}

/*
 * Func : rtk_i2c_setup_reg_base
 * Desc : setup register of rtk i2c
 * Parm : N/A
 * Retn : reg_map of rtk i2c
 */
struct rtk_i2c_reg_map rtk_i2c_setup_reg_base(unsigned int id,
	unsigned long base)
{
	struct rtk_i2c_reg_map reg_map;

	switch (id) {
	case 0:
		reg_map.I2C_ISR = (base & ~0xFFF);
		reg_map.I2C_INT = ISO_ISR_I2C0;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | ISO_I2C0_SDA_DEL;
		break;
	case 1:
#ifdef CONFIG_ARCH_RTD119X
		reg_map.I2C_ISR = (base & ~0xFFF) | 0x000C;
		reg_map.I2C_INT = MISC_ISR_I2C1;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | MISC_I2C1_SDA_DEL;
#else
		reg_map.I2C_ISR = (base & ~0xFFF);
		reg_map.I2C_INT = ISO_ISR_I2C1;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | ISO_I2C1_SDA_DEL;
#endif
		break;
	case 2:
		reg_map.I2C_ISR = (base & ~0xFFF) | 0x000C;
		reg_map.I2C_INT = MIS_ISR_I2C2;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | MIS_I2C2_SDA_DEL;
		break;
	case 3:
		reg_map.I2C_ISR = (base & ~0xFFF) | 0x000C;
		reg_map.I2C_INT = MIS_ISR_I2C3;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | MIS_I2C3_SDA_DEL;
		break;
	case 4:
		reg_map.I2C_ISR = (base & ~0xFFF) | 0x000C;
		reg_map.I2C_INT = MIS_ISR_I2C4;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | MIS_I2C4_SDA_DEL;
		break;
	case 5:
		reg_map.I2C_ISR = (base & ~0xFFF) | 0x000C;
		reg_map.I2C_INT = MIS_ISR_I2C5;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | MIS_I2C5_SDA_DEL;
		break;
	case 6:
		reg_map.I2C_ISR = (base & ~0xFFF);
		reg_map.I2C_INT = ISO_ISR_I2C6;
		reg_map.IC_SDA_DEL = (base & ~0xFFF) | ISO_I2C6_SDA_DEL;
		break;
	default:
		break;
	}

	reg_map.I2C_ISR_EN = 0;
	reg_map.I2C_ISR_EN_MASK = 0;
	reg_map.IC_CON = base | I2C_CON;
	reg_map.IC_TAR = base | I2C_TAR;
	reg_map.IC_SAR = base | I2C_SAR;
	reg_map.IC_HS_MADDR = base | I2C_HS_MADDR;
	reg_map.IC_DATA_CMD = base | I2C_DATA_CMD;

	reg_map.IC_FS_SCL_HCNT = base | I2C_FS_SCL_HCNT;
	reg_map.IC_FS_SCL_LCNT = base | I2C_FS_SCL_LCNT;
	reg_map.IC_SS_SCL_HCNT = base | I2C_SS_SCL_HCNT;
	reg_map.IC_SS_SCL_LCNT = base | I2C_SS_SCL_LCNT;
#ifdef CONFIG_ARCH_RTD16xx
	if (id == 0) {
		reg_map.IC_HS_SCL_HCNT = base | I2C_HS_SCL_HCNT;
		reg_map.IC_HS_SCL_LCNT = base | I2C_HS_SCL_LCNT;
	}
#endif
	reg_map.IC_INTR_STAT = base | I2C_INTR_STAT;
	reg_map.IC_INTR_MASK = base | I2C_INTR_MASK;
	reg_map.IC_RAW_INTR_STAT = base | I2C_RAW_INTR_STAT;
	reg_map.IC_RX_TL = base | I2C_RX_TL;
	reg_map.IC_TX_TL = base | I2C_TX_TL;

	reg_map.IC_CLR_INTR = base | I2C_CLR_INTR;
	reg_map.IC_CLR_RX_UNDER = base | I2C_CLR_RX_UNDER;
	reg_map.IC_CLR_RX_OVER = base | I2C_CLR_RX_OVER;
	reg_map.IC_CLR_TX_OVER = base | I2C_CLR_TX_OVER;
	reg_map.IC_CLR_RD_REQ = base | I2C_CLR_RD_REQ;
	reg_map.IC_CLR_TX_ABRT = base | I2C_CLR_TX_ABRT;
	reg_map.IC_CLR_RX_DONE = base | I2C_CLR_RX_DONE;
	reg_map.IC_CLR_ACTIVITY = base | I2C_CLR_ACTIVITY;
	reg_map.IC_CLR_STOP_DET = base | I2C_CLR_STOP_DET;
	reg_map.IC_CLR_START_DET = base | I2C_CLR_START_DET;
	reg_map.IC_CLR_GEN_CALL = base | I2C_CLR_GEN_CALL;

	reg_map.IC_ENABLE = base | I2C_ENABLE;
	reg_map.IC_STATUS = base | I2C_STATUS;
	reg_map.IC_TXFLR = base | I2C_TXFLR;
	reg_map.IC_RXFLR = base | I2C_RXFLR;
	reg_map.IC_SDA_HOLD = base | I2C_SDA_HOLD;
	reg_map.IC_TX_ABRT_SOURCE = base | I2C_TX_ABRT_SOURCE;
	reg_map.IC_SLV_DATA_NACK_ONLY = base | I2C_SLV_DATA_NACK_ONLY;
	reg_map.IC_DMA_CR = base | I2C_DMA_CR;
	reg_map.IC_DMA_TDLR = base | I2C_DMA_TDLR;
	reg_map.IC_DMA_RDLR = base | I2C_DMA_RDLR;
	reg_map.IC_SDA_SETUP = base | I2C_SDA_SETUP;
	reg_map.IC_ACK_GENERAL_CALL = base | I2C_ACK_GENERAL_CALL;
	reg_map.IC_ENABLE_STATUS = base | I2C_ENABLE_STATUS;
	reg_map.IC_COMP_PARAM_1 = base | I2C_COMP_PARAM_1;
	reg_map.IC_COMP_VERSION = base | I2C_COMP_VERSION;
	reg_map.IC_COMP_TYPE = base | I2C_COMP_TYPE;
	return reg_map;
}

static unsigned char rtk_i2c_flags;
static struct rtk_i2c_handler *rtk_i2c_phy_handle[I2C_PHY_CNT] = {NULL};

/*
 * Func : create_rtk_i2c_handle
 * Desc : create handle of rtk i2c
 * Parm : N/A
 * Retn : handle of rtk i2c
 */
struct rtk_i2c_handler *create_rtk_i2c_handle(
	unsigned int id,
	unsigned short sar,
	enum ADDR_MODE sar_mode,
	unsigned int spd,
	unsigned int irq,
	unsigned long base)
{
	struct rtk_i2c_handler *hHandle;

	RTK_DEBUG("%s\n", __func__);

	if (!(BIT(id) & I2C_ID_MASK))
		return NULL;

	if (((rtk_i2c_flags>>id) & 0x01))
		return rtk_i2c_phy_handle[id];

	hHandle = kmalloc(sizeof(struct rtk_i2c_handler), GFP_KERNEL);

	if (hHandle != NULL) {
		memset(hHandle, 0, sizeof(struct rtk_i2c_handler));
		hHandle->flags = 0;
		hHandle->id = id;
		hHandle->irq = irq;
		hHandle->sar = sar;
		hHandle->sar_mode = sar_mode;
		hHandle->spd = spd;
		hHandle->guard_interval = 1000;
		hHandle->tx_abort_flag = 0;
		hHandle->init = rtk_i2c_handler_init;
		hHandle->uninit = rtk_i2c_handler_uninit;
		hHandle->set_spd = rtk_i2c_set_spd;
		hHandle->set_guard_interval = rtk_i2c_set_guard_interval;
		hHandle->set_tar = rtk_i2c_set_tar;
		hHandle->reg_map = rtk_i2c_setup_reg_base(id, base);
		hHandle->read = rtk_i2c_read;
		hHandle->write = rtk_i2c_write;
		hHandle->get_tx_abort_reason = rtk_i2c_get_tx_abort_reason;
		hHandle->dump = rtk_i2c_dump;
		hHandle->set_sar = rtk_i2c_set_sar;
		hHandle->slave_mode_enable = rtk_i2c_slave_mode_enable;
		hHandle->register_slave_ops = rtk_i2c_register_slave_ops;
		/* GPIO */
		//hHandle->set_port = rtk_i2c_set_port;
		//hHandle->gpio_read = rtk_g2c_read;
		//hHandle->gpio_write = rtk_g2c_write;
#ifdef EDID_4BLOCK_SUPPORT
		hHandle->read_edid_seg = rtk_i2c_read_edid_seg;
#endif
		atomic_set(&hHandle->ref_cnt, 1);
		memset(&hHandle->xfer, 0, sizeof(struct rtk_i2c_xfer));
		rtk_i2c_phy_handle[id] = hHandle;
		rtk_i2c_flags |= (0x01 << id);
	}

	return hHandle;
}
EXPORT_SYMBOL(create_rtk_i2c_handle);

/*
 * Func : destroy_rtk_i2c_handle
 * Desc : destroy handle of rtk i2c
 * Parm : N/A
 * Retn : N/A
 */
void destroy_rtk_i2c_handle(struct rtk_i2c_handler *hHandle)
{
	RTK_DEBUG("%s\n", __func__);

	if (hHandle == NULL)
		return;

	if (atomic_dec_return(&hHandle->ref_cnt) > 0) {
		pr_info("[I2C] destroy I2C%d successed, reference cnt=%d\n",
			hHandle->id, atomic_read(&hHandle->ref_cnt));
		return;
	}

	pr_info("[I2C] destroy rtk i2c%d handle\n", hHandle->id);
	hHandle->uninit(hHandle);
	rtk_i2c_flags &= ~(0x01 << hHandle->id);
	rtk_i2c_phy_handle[hHandle->id] = NULL;
	kfree(hHandle);
}
EXPORT_SYMBOL(destroy_rtk_i2c_handle);
