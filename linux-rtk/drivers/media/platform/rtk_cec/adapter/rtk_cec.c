/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>

#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <soc/realtek/rtk_chip.h>

#include <linux/of.h>
#include "../cec.h"
#include "rtk_cec.h"
#include "cec_rpc.h"

#ifdef CONFIG_ARCH_RTD129x
#define CONVERT_FOR_AVCPU(x)	((unsigned int)(x) | 0xA0000000)
#else
#define CONVERT_FOR_AVCPU(x)	(x)
#endif

#define CBUS_WRAPPER		(0)

#define CEC_INT_SCPU_EN		(0x1<<17)
#define CEC_INT_ACPU_EN		(0x1<<16)
#define CEC_PAD_EN		(0x1<<17)
#define CEC_PAD_EN_MODE		(0x1<<16)

//#define SELF_TEST		1

#define CEC_RSEL(x)				(x & 0x1F)
#define CEC_RPU_EN				(1<<5)
#define IRQ_BY_CEC_RECEIVE_SPECIAL_CMD(x)	((x&0x1)<<8)

#define AUDIO_ION_FLAG (ION_FLAG_NONCACHED | ION_FLAG_SCPUACC | ION_FLAG_ACPUACC)

static const struct of_device_id cec_ids[] __initconst = {
	{ .compatible = "Realtek,rtk-cec0", },
	{},
	{ .compatible = "Realtek,rtk-cec1", },
	{/*Sentinel*/},
};

static cec_device rtk_cec_controller[] = {
	{ .id = 0, .name = "cec0", },
	{ .id = 1, .name = "cec1", },
};

static const int cec_divider_table[] = {
	256000000, 255, 25,
	128000000, 200, 16,
};

#ifdef USE_ION_AUDIO_HEAP
extern struct ion_device *rtk_phoenix_ion_device;

struct ion_client *get_ion_client(const char *name)
{
	return ion_client_create(rtk_phoenix_ion_device, name);
}
#endif
static int clk_nb_func(struct notifier_block *nb,
			unsigned long action, void *data)
{
	struct rtk_cec *p_this = container_of(nb, struct rtk_cec, clk_nb);
	unsigned int i, reg, table_num;
	struct clk_notifier_data *d = data;

	if (action == 2)
		return 0;

	reg = read_reg32(p_this->reg_base + CEC_CR0);
	table_num = sizeof(cec_divider_table) / sizeof(int) / 3;
	for (i = 0; i < table_num; i++) {
		if (d->new_rate == cec_divider_table[i*3]) {
			reg &= ~0x00FFFF00;
			reg |= cec_divider_table[i*3+1] << 16
				| cec_divider_table[i*3+2]<<8;
		}
	}
	write_reg32(p_this->reg_base + CEC_CR0, reg);

	return 0;
}

int _read_cec_rx_fifo(void __iomem *reg, cm_buff *cmb)
{
	unsigned long rx_fifo_data[4];
	int len = read_reg32(reg + CEC_RXCR0) & 0x1F;
	int i;

	if (cmb_tailroom(cmb) >= len) {
		while (len) {
			unsigned char rx_len = len;

			if (rx_len > 16)
				rx_len = 16;

			for (i = 0; i < rx_len; i += 4)
				rx_fifo_data[i>>2] = __cpu_to_be32(
						read_reg32(reg + CEC_RXDR1 + i));

			memcpy(cmb->tail, (unsigned char *)rx_fifo_data, rx_len);
			cmb_put(cmb, rx_len);

			write_reg32(reg + CEC_TXDR0,
				RX_SUB_CNT | FIFO_CNT(rx_len));

			len -= rx_len;
		}
		return cmb->len;
	} else {
		pr_err("[cec] no more space to read data\n");
		return -ENOMEM;
	}
}

int _write_cec_tx_fifo(void __iomem *reg, cm_buff *cmb)
{
	int remain = 0x1F - (read_reg32(reg + CEC_TXCR0) & 0x1F);
	int i;
	int len = cmb->len;
	unsigned int tx_fifo_data[4];

	if (len > remain)
		len = remain;

	while (len) {
		unsigned char tx_len = len;

		if (tx_len > 16)
			tx_len = 16;

		memcpy(tx_fifo_data, cmb->data, tx_len);
		cmb_pull(cmb, tx_len);

		for (i = 0; i < tx_len; i += 4)
			write_reg32(reg + CEC_TXDR1 + i,
					__cpu_to_be32(tx_fifo_data[i>>2]));

		write_reg32(reg + CEC_TXDR0, TX_ADD_CNT | FIFO_CNT(tx_len));
		len -= tx_len;
	}

	return len;
}

static void rtk_cec_rx_reset(struct rtk_cec *p_this)
{
	write_reg32(p_this->reg_base + CEC_RXCR0, 0x4040);
	write_reg32(p_this->reg_base + CEC_RXCR0, 0x0);
	p_this->rcv.state = IDEL;
}
static void rtk_cec_tx_reset(struct rtk_cec *p_this)
{
	write_reg32(p_this->reg_base + CEC_TXCR0, 0x4040);
	write_reg32(p_this->reg_base + CEC_TXCR0, 0x0);
	p_this->xmit.state = IDEL;
}

void _cmb_cec_tx_complete(cm_buff *cmb)
{
	if (cmb == NULL) {
		pr_err("[cec] cmb free, wake fail\n");
		return;
	}

	if (cmb->flags & NONBLOCK) {
		kfree_cmb(cmb);
	} else {
		if (cmb->status == WAIT_XMIT)
			cmb->status = XMIT_ABORT;
		wake_up(&cmb->wq);
	}
}

void rtk_cec_tx_work(struct work_struct *work)
{
	struct rtk_cec *p_this =
		container_of(work, struct rtk_cec, xmit.work.work);
	struct rtk_cec_xmit *p_xmit = &p_this->xmit;
	void __iomem *reg = p_this->reg_base;
	unsigned char dest;
	unsigned long flags;

	spin_lock_irqsave(&p_this->lock, flags);

	if (p_xmit->state == XMIT) {
		if (!(read_reg32(reg + CEC_TXCR0) & TX_EN)) {
			if ((read_reg32(reg + CEC_TXCR0) & TX_EOM) == 0)
				p_xmit->cmb->status = XMIT_FAIL;
			else
				p_xmit->cmb->status = XMIT_OK;
			write_reg32(reg + CEC_TXCR0,
				read_reg32(reg + CEC_TXCR0));
			goto exit_xmit_state;
		}
		if (read_reg32(reg + CEC_TXCR0) & TX_INT) {
			if (p_xmit->cmb->len)
				_write_cec_tx_fifo(reg, p_xmit->cmb);
			if (p_xmit->cmb->len == 0)
				write_reg32(reg + CEC_TXCR0,
					read_reg32(reg + CEC_TXCR0) &
					~TX_CONTINUOUS);
			else
				write_reg32(reg + CEC_TXCR0,
					read_reg32(reg + CEC_TXCR0));
		}
		if (time_after(jiffies, p_xmit->timeout)) {
			write_reg32(reg + CEC_TXCR0, 0);
			p_xmit->cmb->status = XMIT_TIMEOUT;
			goto exit_xmit_state;
		} else {
			goto exit_workque;
		}
	} else if (p_xmit->state == IDEL) {
		goto cmdque_check;
	} else {
		goto exit_workque;
	}
exit_xmit_state:
	cancel_delayed_work(&p_xmit->work);
	_cmb_cec_tx_complete(p_xmit->cmb);
	p_xmit->cmb   = NULL;
	p_xmit->state = IDEL;

cmdque_check:
	if (p_xmit->enable) {
		p_xmit->cmb = cmb_dequeue(&p_this->tx_queue);
		if (!p_xmit->cmb)
			goto exit_workque;

		dest = (p_xmit->cmb->data[0] & 0xf);
		cmb_pull(p_xmit->cmb, 1);
		p_xmit->timeout = jiffies + TX_TIMEOUT;

		rtk_cec_tx_reset(p_this);
		_write_cec_tx_fifo(reg, p_xmit->cmb);

		if (p_xmit->cmb->len == 0)
			write_reg32(reg + CEC_TXCR0, TX_ADDR_EN |
					TX_ADDR(p_this->standby_logical_addr) |
					DEST_ADDR(dest) | TX_EN | TX_INT_EN);
		else
			write_reg32(reg + CEC_TXCR0,
					TX_ADDR(p_this->standby_logical_addr) |
					DEST_ADDR(dest) | TX_EN | TX_INT_EN |
					TX_CONTINUOUS);
		p_xmit->state = XMIT;
		schedule_delayed_work(&p_xmit->work, TX_TIMEOUT+1);
	}

exit_workque:
	spin_unlock_irqrestore(&p_this->lock, flags);
}

static void rtk_cec_tx_start(struct rtk_cec *p_this)
{
	unsigned long flags;

	spin_lock_irqsave(&p_this->lock, flags);

	if (!p_this->xmit.enable) {
		p_this->xmit.enable = 1;
		p_this->xmit.state  = IDEL;
		p_this->xmit.cmb    = NULL;

		INIT_DELAYED_WORK(&p_this->xmit.work, rtk_cec_tx_work);
		cmb_queue_head_init(&p_this->tx_queue);
	}

	spin_unlock_irqrestore(&p_this->lock, flags);
}

static void rtk_cec_tx_stop(struct rtk_cec *p_this)
{
	unsigned long flags;

	spin_lock_irqsave(&p_this->lock, flags);

	if (p_this->xmit.enable) {
		cancel_delayed_work(&p_this->xmit.work);
		rtk_cec_tx_reset(p_this);

		if (p_this->xmit.cmb)
			_cmb_cec_tx_complete(p_this->xmit.cmb);

/*		while((cmb = cmb_dequeue(&p_this->tx_queue)))
			_cmb_cec_tx_complete(cmb);*/

		p_this->xmit.enable = 0;
		p_this->xmit.state  = IDEL;
		p_this->xmit.cmb    = NULL;
	}

	spin_unlock_irqrestore(&p_this->lock, flags);
}

int rtk_cec_xmit_message(struct rtk_cec *p_this, cm_buff *cmb, unsigned long flags)
{
	struct device *dev = p_this->dev;
	int ret = 0;
	unsigned long flag;

	if (!p_this->xmit.enable)
		return -1;

	cmb->flags  = flags;
	cmb->status = WAIT_XMIT;

	cmb_queue_tail(&p_this->tx_queue, cmb);

	schedule_delayed_work(&p_this->xmit.work, 0);

	if (!(cmb->flags & NONBLOCK)) {
		wait_event_timeout(cmb->wq, cmb->status != WAIT_XMIT,
							TX_TIMEOUT + 50);

		switch (cmb->status) {
		case XMIT_OK:
			dev_info(dev, "xmit message success\n");
			break;
		case XMIT_ABORT:
			dev_info(dev, "xmit message abort\n");
			break;
		case XMIT_FAIL:
			dev_info(dev, "xmit message abort\n");
			break;
		default:
		case XMIT_TIMEOUT:
		case WAIT_XMIT:
			dev_info(dev, "xmit message timeout\n");
			break;
		}

		spin_lock_irqsave(&p_this->lock, flag);
		ret = (cmb->status == XMIT_OK) ? 0 : -1;
		kfree_cmb(cmb);
		spin_unlock_irqrestore(&p_this->lock, flag);
	}
	return ret;
}

void rtk_cec_standby_message_handler(struct rtk_cec *p_this,
				unsigned char init,
				unsigned char dest,
				unsigned char opcode,
				unsigned char *param,
				unsigned char len)
{
	cm_buff *cmb = NULL;
	unsigned char dev_type_map[15] = {
		CEC_DEVICE_TV,
		CEC_DEVICE_RECORDING_DEVICE,
		CEC_DEVICE_RECORDING_DEVICE,
		CEC_DEVICE_TUNER,
		CEC_DEVICE_PLAYBACK_DEVICE,
		CEC_DEVICE_AUDIO_SYSTEM,
		CEC_DEVICE_TUNER,
		CEC_DEVICE_TUNER,
		CEC_DEVICE_PLAYBACK_DEVICE,
		CEC_DEVICE_RECORDING_DEVICE,
		CEC_DEVICE_TUNER,
		CEC_DEVICE_PLAYBACK_DEVICE,
		CEC_DEVICE_RESERVED,
		CEC_DEVICE_RESERVED,
		CEC_DEVICE_TV
	};

	switch (opcode) {
	case CEC_MSG_GIVE_DEVICE_POWER_STATUS:
		if ((p_this->standby_config & STANBY_RESPONSE_GIVE_POWER_STATUS)
			&& len == 0 && init != 0xF) {
#ifdef CEC_OPCODE_COMPARE_ENABLE
			if (PWR_STS_COMP_EN())
				break;
#endif
			cmb = alloc_cmb(3);
			if (cmb) {
				cmb->data[0] = (dest<<4) | init;
				cmb->data[1] = CEC_MSG_REPORT_POWER_STATUS;
				cmb->data[2] = CEC_POWER_STATUS_STANDBY;
				cmb_put(cmb, 3);
			}
		}
		break;
	case CEC_MSG_GIVE_PHYSICAL_ADDRESS:
		if ((p_this->standby_config & STANBY_WAKEUP_BY_SET_STREAM_PATH)
			&& len == 0 && dest != 0xF) {

#ifdef CEC_OPCODE_COMPARE_ENABLE
			if (PHY_ADDR_COMP_EN())
				break;
#endif
			cmb = alloc_cmb(5);
			if (cmb) {
				cmb->data[0] = (dest<<4) | 0xF;
				cmb->data[1] = CEC_MSG_REPORT_PHYSICAL_ADDRESS;
				cmb->data[2] = (p_this->standby_physical_addr >> 8) & 0xFF;
				cmb->data[3] = (p_this->standby_physical_addr) & 0xFF;
				cmb->data[4] = dev_type_map[dest];
				cmb_put(cmb, 5);
			}
		}
		break;
	case CEC_MSG_STANDBY:
		break;

	default:
		if (init != 0xF && dest != 0xF) {
			cmb = alloc_cmb(4);
			if (cmb) {
				cmb->data[0] = (dest<<4) | init;
				cmb->data[1] = CEC_MSG_FEATURE_ABORT;
				cmb->data[2] = opcode;
				cmb->data[3] = CEC_ABORT_NOT_IN_CORECT_MODE;
				cmb_put(cmb, 4);
			}
		}
	}
	if (cmb)
		rtk_cec_xmit_message(p_this, cmb, NONBLOCK);
}

void rtk_cec_rx_work(struct work_struct *work)
{
	struct rtk_cec *p_this =
			container_of(work, struct rtk_cec, rcv.work.work);
	struct rtk_cec_rcv *p_rcv = &p_this->rcv;
	struct device *dev = p_this->dev;
	void __iomem *reg = p_this->reg_base;
	unsigned long flags;
	unsigned long rx_event = read_reg32(p_this->reg_base + CEC_RXCR0);

	spin_lock_irqsave(&p_this->lock, flags);

	if (!p_rcv->enable) {
		if (p_rcv->state == RCV) {
			dev_info(dev, "%s force stop\n", __func__);
			write_reg32(p_this->reg_base + CEC_RXCR0, 0);
			kfree_cmb(p_rcv->cmb);
			p_rcv->cmb   = NULL;
			p_rcv->state = IDEL;
		}
		rtk_cec_rx_reset(p_this);
		goto exit_workque;
	}

	if (p_rcv->state != RCV)
		goto exit_rcv_state;

#ifdef CEC_OPCODE_COMPARE_ENABLE
	if ((rx_event & RX_EN) && (!IS_OPCODE_COMP_EN())) {
#else
	if (rx_event & RX_EN) {
#endif
		if (rx_event & RX_INT) {
			if (_read_cec_rx_fifo(reg, p_rcv->cmb) < 0) {
				write_reg32(reg + CEC_RXCR0, 0);
				p_rcv->state = IDEL;
			}
			write_reg32(reg + CEC_RXCR0, RX_INT);
		}
		goto exit_rcv_state;
	}

	if ((rx_event & RX_EOM) && _read_cec_rx_fifo(reg, p_rcv->cmb)) {
		if (rx_event & BROADCAST_ADDR)
			*cmb_push(p_rcv->cmb, 1) =
			((rx_event & INIT_ADDR_MASK)>>INIT_ADDR_SHIFT)<<4 |
			0xF;
		else
			*cmb_push(p_rcv->cmb, 1) =
			((rx_event & INIT_ADDR_MASK)>>INIT_ADDR_SHIFT)<<4 |
			(read_reg32(reg + CEC_CR0) & LOGICAL_ADDR_MASK)>>LOGICAL_ADDR_SHIFT;
	}
	if (p_this->status.standby_mode) {
		rtk_cec_standby_message_handler(
					p_this,
					p_rcv->cmb->data[0] >> 4,
					p_rcv->cmb->data[0] & 0xF,
					p_rcv->cmb->data[1],
					&p_rcv->cmb->data[2],
					p_rcv->cmb->len - 2);
	} else {
		cmb_queue_tail(&p_this->rx_queue, p_rcv->cmb);
		p_rcv->cmb = NULL;
		wake_up_interruptible(&p_this->rcv.wq);
	}
	p_rcv->state = IDEL;

exit_rcv_state:
	if (p_rcv->state != IDEL)
		goto exit_workque;

	if (!p_rcv->cmb) {
		if (cmb_queue_len(&p_this->rx_free_queue))
			p_rcv->cmb = cmb_dequeue(&p_this->rx_free_queue);
		else
			p_rcv->cmb = cmb_dequeue(&p_this->rx_queue);

		if (p_rcv->cmb == NULL)
			goto exit_workque;
	}
	cmb_purge(p_rcv->cmb);
	cmb_reserve(p_rcv->cmb, 1);

	rtk_cec_rx_reset(p_this);
	write_reg32(reg + CEC_RXCR0, RX_EN | RX_INT_EN);
	p_rcv->state = RCV;

exit_workque:
	spin_unlock_irqrestore(&p_this->lock, flags);
}

static void rtk_cec_rx_start(struct rtk_cec *p_this)
{
	unsigned long flags;

	spin_lock_irqsave(&p_this->lock, flags);

	if (!p_this->rcv.enable) {
		p_this->rcv.enable = 1;
		p_this->rcv.state  = IDEL;
		p_this->rcv.cmb    = NULL;

		INIT_DELAYED_WORK(&p_this->rcv.work, rtk_cec_rx_work);

		schedule_delayed_work(&p_this->rcv.work, 0);
	}

	spin_unlock_irqrestore(&p_this->lock, flags);
}

static void rtk_cec_rx_stop(struct rtk_cec *p_this)
{
	cm_buff *cmb;
	unsigned long flags;

	spin_lock_irqsave(&p_this->lock, flags);

	if (p_this->rcv.enable) {
		rtk_cec_rx_reset(p_this);

		if (p_this->rcv.cmb) {
			cmb_purge(p_this->rcv.cmb);
			cmb_reserve(p_this->rcv.cmb, 1);
			cmb_queue_tail(&p_this->rx_free_queue, p_this->rcv.cmb);
		}

		while ((cmb = cmb_dequeue(&p_this->rx_queue))) {
			cmb_purge(cmb);
			cmb_reserve(cmb, 1);
			cmb_queue_tail(&p_this->rx_free_queue, cmb);
		}
		p_this->rcv.enable = 0;
		p_this->rcv.state  = IDEL;
		p_this->rcv.cmb    = NULL;

		wake_up_interruptible(&p_this->rcv.wq);
	}
	spin_unlock_irqrestore(&p_this->lock, flags);
}

static irqreturn_t rtk_cec_isr(int this_irq, void *dev_id)
{
	struct rtk_cec *p_this;
	int i, dev_num;
	irqreturn_t ret = IRQ_NONE;

	dev_num = ARRAY_SIZE(rtk_cec_controller);
	for (i = 0; i < dev_num; i++) {
		if (cec_device_pthis[i] != 0) {
			p_this = (struct rtk_cec *)cec_device_pthis[i];

			if (read_reg32(p_this->reg_base + CEC_TXCR0) & TX_INT) {
				rtk_cec_tx_work(&p_this->xmit.work.work);
				ret = IRQ_HANDLED;
			}

			if (read_reg32(p_this->reg_base + CEC_RXCR0) & RX_INT) {
				rtk_cec_rx_work(&p_this->rcv.work.work);
				ret = IRQ_HANDLED;
			}
		}
	}
	return ret;
}

int rtk_cec_init(struct rtk_cec *p_this)
{
	cm_buff *cmb = NULL;
	void __iomem *reg = p_this->reg_base;
	void __iomem *wrapper = p_this->wrapper_reg;
	int i;

	if (p_this->status.init)
		return 0;
	rtk_cec_rx_reset(p_this);
	rtk_cec_tx_reset(p_this);

	write_reg32(reg + CEC_TXTCR1, TX_DATA_LOW(0x1A) |
					TX_DATA_01(0x23) |
					TX_DATA_HIGH(0x22));
	write_reg32(reg + CEC_TXTCR0, TX_START_LOW(0x93) | TX_START_HIGH(0x20));
	write_reg32(reg + CEC_RXTCR0, RX_START_LOW(0x8C) |
					RX_START_PERIOD(0xC1) |
					RX_DATA_SAMPLE(0x2A) |
					RX_DATA_PERIOD(0x52));
	if(p_this->chip_id == CHIP_ID_RTD1295 ||
		p_this->chip_id == CHIP_ID_RTD1296) {
		write_reg32(reg + CEC_CR0, CEC_MODE(1) |
					LOGICAL_ADDR(0x4) |
					TIMER_DIV(25) |
					PRE_DIV(255) |
					UNREG_ACK_EN);
	} else {
		write_reg32(reg + CEC_CR0, CEC_MODE(1) |
					LOGICAL_ADDR(0x4) |
					TIMER_DIV(20) |
					PRE_DIV(33) |
					UNREG_ACK_EN);
	}
	write_reg32(reg + CEC_RTCR0, CEC_PAD_EN | CEC_PAD_EN_MODE | RETRY_NO(2));
	write_reg32(reg + CEC_RXCR0, RX_EN | RX_INT_EN);
#ifdef CEC_OPCODE_COMPARE_ENABLE
	write_reg32(reg + GDI_CEC_OPCODE_ENABLE, 0);
#endif
	spin_lock_init(&p_this->lock);

	p_this->xmit.state      = IDEL;
	p_this->xmit.cmb        = NULL;
	p_this->xmit.timeout    = 0;

	p_this->rcv.state       = IDEL;
	p_this->rcv.cmb         = NULL;
	init_waitqueue_head(&p_this->rcv.wq);

	cmb_queue_head_init(&p_this->tx_queue);
	cmb_queue_head_init(&p_this->rx_queue);
	cmb_queue_head_init(&p_this->rx_free_queue);

	for (i = 0; i < RX_RING_LENGTH; i++) {
		cmb = alloc_cmb(RX_BUFFER_SIZE);
		if (cmb)
			cmb_queue_tail(&p_this->rx_free_queue, cmb);
	}

	if (request_irq(p_this->irq_num, rtk_cec_isr,
			IRQF_SHARED, "RTK CEC", p_this) < 0) {
		return -EIO;
	}
	if (wrapper != NULL)
		write_reg32(wrapper + CBUS_WRAPPER,
				read_reg32(wrapper + CBUS_WRAPPER) |
				CEC_INT_SCPU_EN |
				CEC_INT_ACPU_EN);
	write_reg32(reg + GDI_POWER_SAVING_MODE,
			IRQ_BY_CEC_RECEIVE_SPECIAL_CMD(1) |
			CEC_RPU_EN | CEC_RSEL(0x17));
	p_this->status.init = 1;

	return 0;
}

int rtk_cec_RPC_TOAGENT_PrivateInfo(struct rtk_cec *p_this, char *str,
							unsigned long para)
{
#ifdef USE_ION_AUDIO_HEAP
	struct AUDIO_RPC_PRIVATEINFO_PARAMETERS *rpc = NULL;
	struct device *dev = p_this->dev;
	struct ion_handle *handle = NULL;
	struct ion_client *client = p_this->rpc_ion_client;
	unsigned int RPC_ret;
	ion_phys_addr_t dat = {0};
	size_t len;
	int ret = -1;
	unsigned long offset;

	handle = ion_alloc(client, 4096, 1024,
				RTK_PHOENIX_ION_HEAP_AUDIO_MASK,
				AUDIO_ION_FLAG);
	if (IS_ERR(handle)) {
		dev_err(dev, "%s ion_alloc fail\n", __func__);
		goto exit;
	}
	if (ion_phys(client, handle, &dat, &len) != 0) {
		dev_err(dev, "%s ion_phys fail\n", __func__);
		goto exit;
	}
	rpc = ion_map_kernel(client, handle);
	if (!rpc)
		goto exit;

	offset = get_rpc_alignment_offset(sizeof(*rpc));
	memset(rpc, 0, sizeof(*rpc));

	rpc->type = htonl(ENUM_PRIVATEINFO_AUDIO_SET_CEC_PARAMETERS);
	rpc->privateInfo[0] = htonl(p_this->standby_config);
	rpc->privateInfo[1] = htonl(p_this->standby_logical_addr);
	rpc->privateInfo[2] = htonl(p_this->standby_physical_addr);
	rpc->privateInfo[3] = htonl(p_this->standby_cec_version);
	rpc->privateInfo[4] = htonl(p_this->standby_vendor_id);
	rpc->privateInfo[5] = htonl(p_this->standby_rx_mask);
	rpc->privateInfo[6] = htonl(p_this->standby_cec_wakeup_off);

	if (send_rpc_command(RPC_AUDIO,
		ENUM_KERNEL_RPC_PRIVATEINFO,
		CONVERT_FOR_AVCPU(dat),
		CONVERT_FOR_AVCPU(dat + offset),
		&RPC_ret)) {
		dev_err(dev, "%s RPC fail\n", __func__);
		goto exit;
	}
	ret = 0;
exit:
	if (handle != NULL) {
		ion_unmap_kernel(client, handle);
		ion_free(client, handle);
	}
	return ret;
#endif
	return 0;
}

int rtk_cec_set_mode(struct rtk_cec *p_this, unsigned char mode)
{
	struct device *dev = p_this->dev;
	void __iomem *reg = p_this->reg_base;

	switch (mode) {
	case CEC_MODE_OFF:
		dev_info(dev, "mode : OFF\n");
		write_reg32(reg + CEC_CR0,
				(read_reg32(reg + CEC_CR0) &
				~CTRL_MASK1) |
				CEC_MODE(0) |
				LOGICAL_ADDR(0xF));
		p_this->status.enable = 0;
		p_this->status.standby_mode = 0;
		rtk_cec_rx_stop(p_this);
		rtk_cec_tx_stop(p_this);
		break;

	case CEC_MODE_ON:
		dev_info(dev, "mode : ON\n");
		write_reg32(reg + CEC_CR0,
				(read_reg32(reg + CEC_CR0) & ~CTRL_MASK1) |
				CEC_MODE(1));
		write_reg32(reg + CEC_RXCR0, RX_EN | RX_INT_EN);
#ifdef CEC_OPCODE_COMPARE_ENABLE
		write_reg32(reg + GDI_CEC_OPCODE_ENABLE, 0);
#endif
		rtk_cec_rx_start(p_this);
		rtk_cec_tx_start(p_this);
		p_this->status.enable = 1;
		p_this->status.standby_mode = 0;
		break;

	case CEC_MODE_STANDBY:
		dev_info(dev, "mode : standby (la=%x)\n",
				p_this->standby_logical_addr);
		write_reg32(reg + CEC_CR0,
				(read_reg32(reg + CEC_CR0) & ~CTRL_MASK1) |
				CEC_MODE(1) |
				LOGICAL_ADDR(p_this->standby_logical_addr));
		rtk_cec_rx_start(p_this);
		rtk_cec_tx_start(p_this);
		p_this->status.enable = 1;
		p_this->status.standby_mode = 1;
		break;
	}
	return 0;
}

int rtk_cec_enable(struct rtk_cec *p_this, unsigned char on_off)
{
	if (on_off) {
		rtk_cec_set_mode(p_this, CEC_MODE_ON);
	} else {
		if (p_this->standby_config == 0 ||
				p_this->standby_logical_addr >= 0xF ||
				p_this->standby_physical_addr == 0xFFFF)
			rtk_cec_set_mode(p_this, CEC_MODE_OFF);
		else
			rtk_cec_set_mode(p_this, CEC_MODE_STANDBY);
	}
	return 0;
}

int rtk_cec_set_rx_mask(struct rtk_cec *p_this, unsigned short rx_mask)
{
	struct device *dev = p_this->dev;
	void __iomem *reg = p_this->reg_base;
	unsigned char log_addr = 0xf;
	int i;

	for (i = 0; i < 16; i++) {
		if (TEST_BIT(rx_mask, i)) {
			log_addr = i;
			break;
		}
	}

	if (rx_mask & ~(BIT_MASK(15) | BIT_MASK(log_addr))) {
		dev_info(dev,
			"multi addr specified %04x, only address %x are valid\n"
			, rx_mask, log_addr);
	}

	write_reg32(reg + CEC_CR0, (read_reg32(reg + CEC_CR0) &
			~LOGICAL_ADDR_MASK) | LOGICAL_ADDR(log_addr));

	if (log_addr != 0xF) {
		p_this->standby_logical_addr = log_addr;
		rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "logical address",
						p_this->standby_logical_addr);
	}
	return 0;
}

int rtk_cec_set_physical_addr(struct rtk_cec *p_this, unsigned short phy_addr)
{
	dev_info(p_this->dev, "physcial address = %04x\n", phy_addr);

	if (phy_addr != 0xffff)
		p_this->standby_physical_addr = phy_addr;

	rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "physical addr",
					(unsigned long)phy_addr);
	return 0;
}

int rtk_cec_get_physical_addr(struct rtk_cec *p_this)
{
	return p_this->standby_physical_addr;
}

int rtk_cec_set_cec_version(struct rtk_cec *p_this, unsigned char version)
{
	p_this->standby_cec_version = version;
	rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "cec version",
					(unsigned long)version);
	return 0;
}

int rtk_cec_set_device_vendor_id(struct rtk_cec *p_this, unsigned long vendor_id)
{
	p_this->standby_vendor_id = vendor_id;
	rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "vendor id", vendor_id);
	return 0;
}

int rtk_cec_set_stanby_mode(struct rtk_cec *p_this, unsigned long mode)
{
	p_this->standby_config = mode;
	rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "standy mode", mode);
	return 0;
}

int rtk_cec_set_retry_num(struct rtk_cec *p_this, unsigned long	num)
{
	void __iomem *reg = p_this->reg_base;

	write_reg32(reg + CEC_RTCR0, ((read_reg32(reg + CEC_RTCR0) &
					~RETRY_NO_MASK) | RETRY_NO(num)));
	return 0;
}

static cm_buff *rtk_cec_read_message(struct rtk_cec *p_this, unsigned char flags)
{
	while (!(flags & NONBLOCK) && p_this->status.enable &&
				!cmb_queue_len(&p_this->rx_queue)) {
		wait_event_interruptible(p_this->rcv.wq, !p_this->status.enable
					|| cmb_queue_len(&p_this->rx_queue));
	}
	if (p_this->status.enable) {
		cm_buff *cmb = cmb_dequeue(&p_this->rx_queue);

		if (cmb) {
			cm_buff *cmb1 = alloc_cmb(RX_BUFFER_SIZE);
			if (cmb1)
				cmb_queue_tail(&p_this->rx_free_queue, cmb1);
			else
				dev_err(p_this->dev, "alloc_cmb fail\n");
			dev_info(p_this->dev, "got msg %p\n", cmb);
			return cmb;
		}
	}

	return NULL;
}

void rtk_cec_uninit(struct rtk_cec *p_this)
{
	struct device *dev = p_this->dev;
	void __iomem *reg = p_this->reg_base;

	dev_info(dev, "%s\n", __func__);

	free_irq(p_this->irq_num, p_this);
	write_reg32(reg + CEC_CR0, read_reg32(reg + CEC_CR0) & ~CEC_MODE_MASK);
	write_reg32(reg + CEC_RXCR0, 0);
	write_reg32(reg + CEC_TXCR0, 0);
	rtk_cec_enable(p_this, 0);
	p_this->status.init = 0;
}

int rtk_cec_suspend(struct rtk_cec *p_this)
{
	struct device *dev = p_this->dev;
	void __iomem *reg = p_this->reg_base;
	void __iomem *wrapper = p_this->wrapper_reg;

	if (!p_this->status.enable) {
		dev_info(dev, "function is disable\n");
		p_this->standby_cec_wakeup_off = 1;
		rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "wakeup off",
					p_this->standby_cec_wakeup_off);
		return 0;
	}

	p_this->standby_cec_wakeup_off = 0;
	rtk_cec_RPC_TOAGENT_PrivateInfo(p_this, "wakeup off",
					p_this->standby_cec_wakeup_off);

	dev_info(dev, "rtk cec suspended (la=%x, pa=%04x, standby_mode=%ld)",
			p_this->standby_logical_addr,
			p_this->standby_physical_addr,
			p_this->standby_config);

	rtk_cec_set_mode(p_this, CEC_MODE_OFF);

	disable_irq(p_this->irq_num);

	if (p_this->standby_config && p_this->standby_logical_addr < 0xF &&
				p_this->standby_physical_addr != 0xFFFF) {
		p_this->status.enable = 1;
		p_this->status.standby_mode = 1;

		write_reg32(reg + CEC_CR0,
			(read_reg32(reg + CEC_CR0) & ~(LOGICAL_ADDR(0xF))) |
			CEC_MODE(1) |
			LOGICAL_ADDR(p_this->standby_logical_addr));
		write_reg32(reg + CEC_RXCR0,  RX_RST);
		write_reg32(reg + CEC_RXCR0,  0);
		write_reg32(reg + CEC_TXCR0,  TX_RST);
		write_reg32(reg + CEC_TXCR0,  0);

		write_reg32(reg + CEC_RXCR0,  RX_EN | RX_INT_EN | RX_INT);
		write_reg32(reg + GDI_POWER_SAVING_MODE,
				IRQ_BY_CEC_RECEIVE_SPECIAL_CMD(1) |
				CEC_RPU_EN | CEC_RSEL(0x17));
		if (wrapper != NULL)
			write_reg32(wrapper + CBUS_WRAPPER,
				(read_reg32(wrapper + CBUS_WRAPPER) & ~CEC_INT_SCPU_EN));
		dev_info(dev, "standby enabled");
	}
	return 0;
}

int rtk_cec_resume(struct rtk_cec *p_this)
{
	void __iomem *reg = p_this->reg_base;
	void __iomem *wrapper = p_this->wrapper_reg;
	unsigned int val;

	/* clear tx interrupt */
	val = read_reg32(reg + CEC_TXCR0);
	if (val & TX_INT)
		write_reg32(reg + CEC_TXCR0, val);

	write_reg32(reg + CEC_TXTCR1, TX_DATA_LOW(0x1A) |
					TX_DATA_01(0x23) |
					TX_DATA_HIGH(0x22));
	write_reg32(reg + CEC_TXTCR0, TX_START_LOW(0x93) | TX_START_HIGH(0x20));
	write_reg32(reg + CEC_RXTCR0, RX_START_LOW(0x8C) |
					RX_START_PERIOD(0xC1) |
					RX_DATA_SAMPLE(0x2A) |
					RX_DATA_PERIOD(0x52));
	if(p_this->chip_id == CHIP_ID_RTD1295 ||
		p_this->chip_id == CHIP_ID_RTD1296) {
		write_reg32(reg + CEC_CR0, CEC_MODE(1) |
					LOGICAL_ADDR(0x4) |
					TIMER_DIV(25) |
					PRE_DIV(255) |
					UNREG_ACK_EN);
	} else {
		write_reg32(reg + CEC_CR0, CEC_MODE(1) |
					LOGICAL_ADDR(0x4) |
					TIMER_DIV(20) |
					PRE_DIV(33) |
					UNREG_ACK_EN);
	}
	write_reg32(reg + CEC_RTCR0, CEC_PAD_EN | CEC_PAD_EN_MODE | RETRY_NO(2));
	write_reg32(reg + CEC_RXCR0, RX_EN | RX_INT_EN);

	rtk_cec_rx_reset(p_this);
	rtk_cec_tx_reset(p_this);

	if (p_this->standby_config && p_this->standby_logical_addr < 0xF &&
					p_this->standby_physical_addr != 0xFFFF)
		rtk_cec_set_mode(p_this, CEC_MODE_ON);
	else
		rtk_cec_set_mode(p_this, CEC_MODE_OFF);

	if (p_this->status.enable)
		enable_irq(p_this->irq_num);
	if (wrapper != NULL)
		write_reg32(wrapper + CBUS_WRAPPER,
				read_reg32(wrapper + CBUS_WRAPPER) |
				CEC_INT_SCPU_EN |
				CEC_INT_ACPU_EN);
	return 0;
}

static int ops_probe(cec_device *dev)
{
	struct device_node __maybe_unused *cec_node;
	struct rtk_cec *m_cec;
	struct clk *clk;
	struct reset_control *rstc;

	m_cec = kzalloc(sizeof(*m_cec), GFP_KERNEL);
	cec_node = of_find_matching_node(NULL, &cec_ids[dev->id*2]);
	if (!cec_node)
		goto cec_probe_fail;
	if (!of_device_is_available(cec_node))
		goto cec_probe_fail;

	m_cec->dev = &dev->dev;
	cec_device_en[dev->id] = 1;
	cec_device_pthis[dev->id] = 0;

#ifdef USE_ION_AUDIO_HEAP
	m_cec->rpc_ion_client = ion_client_create(
					rtk_phoenix_ion_device, "CECDriver");
#else
	m_cec->rpc_ion_client = NULL;
#endif
	m_cec->reg_base = of_iomap(cec_node, 0);
	m_cec->iso_base = of_iomap(cec_node, 1);
	m_cec->wrapper_reg = of_iomap(cec_node, 2);

	m_cec->chip_id = get_rtd_chip_id();
	if (m_cec->chip_id == CHIP_ID_RTD1295 ||
		m_cec->chip_id == CHIP_ID_RTD1296) {
		clk = of_clk_get_by_name(cec_node, "sys");
		m_cec->clk_nb.notifier_call = clk_nb_func;
		clk_notifier_register(clk, &m_cec->clk_nb);
	}

	if (m_cec->wrapper_reg == NULL && m_cec->chip_id != CHIP_ID_RTD1195)
		goto cec_probe_fail;

	clk = of_clk_get_by_name(cec_node, "cbus_osc");
	if (!IS_ERR(clk))
		clk_prepare_enable(clk);
	clk = of_clk_get_by_name(cec_node, "cbus_sys");
	if (!IS_ERR(clk))
		clk_prepare_enable(clk);

	rstc = of_reset_control_get(cec_node, "cbus");
	if (!IS_ERR(rstc))
		reset_control_deassert(rstc);

	if (dev->id == 0) {
		m_cec->clk = of_clk_get_by_name(cec_node, "cbustx_sys");
		m_cec->rstc = of_reset_control_get(cec_node, "cbustx");
	} else {
		m_cec->clk = of_clk_get_by_name(cec_node, "cbusrx_sys");
		m_cec->rstc = of_reset_control_get(cec_node, "cbusrx");
	}
	if (!IS_ERR(m_cec->rstc))
		reset_control_deassert(m_cec->rstc);
	if (!IS_ERR(m_cec->clk))
		clk_prepare_enable(m_cec->clk);

	m_cec->irq_num = irq_of_parse_and_map(cec_node, 0);
	if (!m_cec->irq_num)
		goto cec_probe_fail;

	if (rtk_cec_init(m_cec) == 0) {
		cec_set_drvdata(dev, m_cec);
		cec_device_pthis[dev->id] = (int *)m_cec;
	}
#if defined(SELF_TEST) && SELF_TEST
	pr_info("%s self test start\n", __func__);
	rtk_cec_enable(m_cec, 1);
	rtk_cec_set_rx_mask(m_cec, 0x8010);
#endif
	dev_info(&dev->dev, "probe success\n");
	return 0;

cec_probe_fail:
	dev_err(&dev->dev, "probe fail\n");
	kfree(m_cec);
	return -1;
}

static void ops_remove(cec_device *dev)
{
	rtk_cec_uninit((struct rtk_cec *)cec_get_drvdata(dev));
}

static int ops_enable(cec_device *dev, unsigned char on_off)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	dev_info(p_this->dev, "%s : %02x\n", __func__, on_off);
	if ((on_off & 0xf0) == 0) {
		if (on_off & 0x0f) {
			p_this->standby_config = STANBY_RESPONSE_GIVE_POWER_STATUS
					| STANBY_RESPONSE_GET_CEC_VERISON;
			p_this->standby_logical_addr	= 0x0;
			p_this->standby_physical_addr	= 0x0000;
		} else {
			p_this->standby_config		= 0;
			p_this->standby_logical_addr	= 0xF;
			p_this->standby_physical_addr	= 0xFFFF;
		}
	}
	return rtk_cec_enable(p_this, (on_off & 0x0f));
}

static int ops_set_rx_mask(cec_device *dev, unsigned short rx_mask)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_rx_mask(p_this, rx_mask);
}

static int ops_set_physical_addr(cec_device *dev, unsigned short phy_addr)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_physical_addr(p_this, phy_addr);
}

static int ops_get_physical_addr(cec_device *dev)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_get_physical_addr(p_this);
}

static int ops_set_cev_version(cec_device *dev, unsigned char version)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_cec_version(p_this, version);
}

static int ops_set_device_vendor_id(cec_device *dev, unsigned long vendor_id)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_device_vendor_id(p_this, vendor_id);
}

static int ops_xmit(cec_device *dev, cm_buff *cmb, unsigned long flags)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_xmit_message(p_this, cmb, flags);
}

static cm_buff *ops_read(cec_device *dev, unsigned long flags)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_read_message(p_this, flags);
}

static int ops_set_stanby_mode(cec_device *dev, unsigned long flags)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_stanby_mode(p_this, flags);
}

static int ops_set_retry_num(cec_device *dev, unsigned long num)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_set_retry_num(p_this, num);
}

static int ops_suspend(cec_device *dev)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_suspend(p_this);
}

static int ops_resume(cec_device *dev)
{
	struct rtk_cec *p_this = cec_get_drvdata(dev);

	return rtk_cec_resume(p_this);
}

static cec_driver rtk_cec_driver = {
	.name			= "cec",
	.probe			= ops_probe,
	.remove			= ops_remove,
	.suspend		= ops_suspend,
	.resume			= ops_resume,
	.enable			= ops_enable,
	.xmit			= ops_xmit,
	.read			= ops_read,
	.set_rx_mask		= ops_set_rx_mask,
	.set_physical_addr	= ops_set_physical_addr,
	.set_cec_version	= ops_set_cev_version,
	.set_device_vendor_id	= ops_set_device_vendor_id,
	.set_stanby_mode	= ops_set_stanby_mode,
	.set_retry_num		= ops_set_retry_num,
	.get_physical_addr	= ops_get_physical_addr,
};

static int __init rtk_cec_module_init(void)
{
	int i, dev_num;

	if (register_cec_driver(&rtk_cec_driver) != 0)
		return -EFAULT;

	dev_num = ARRAY_SIZE(rtk_cec_controller);
	if (dev_num > 0) {
		for (i = 0; i < dev_num; i++)
			register_cec_device(&rtk_cec_controller[i]);
	}
	return 0;
}

static void __exit rtk_cec_module_exit(void)
{
	unregister_cec_driver(&rtk_cec_driver);
}

module_init(rtk_cec_module_init);
module_exit(rtk_cec_module_exit);
