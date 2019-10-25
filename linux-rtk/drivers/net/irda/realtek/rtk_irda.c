/*
 *  rtk_irda.c - RTK irda driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/input.h>
#include <linux/kfifo.h>
#include <linux/cdev.h>
#include <linux/freezer.h>
#include <linux/uaccess.h>
#include <linux/poll.h>

#include <linux/cdev.h>
#include <linux/clk.h>
#include <linux/reset.h>

#include "rtk_irda.h"
#include "irda_sw_decoder.h"

#include <soc/realtek/rtk_chip.h>
#include <soc/realtek/memory.h>
#include <soc/realtek/rtk_ipc_shm.h>

#ifdef CONFIG_RTK_XEN_SUPPORT
#include <xen/xen.h>
#endif

#define IRDA_CDEV_MAJOR			234
#define IRDA_CDEV_MINOR			50

#define IRDA_RXFIFO			128
#define IRDA_TXFIFO			16

#define FIFO_DEPTH			16
#define RTK_MK5_CUSTOMER_CODE		0x7F80

#if defined(CONFIG_ARCH_RTD16xx) || defined(CONFIG_ARCH_RTD13xx)
extern struct ipc_shm_irda pcpu_data_irda;
#endif

enum {
	irda_rx = 0,
	irda_tx,
};

enum {
	software = 0,
	hardware,
};

enum {
	NORMAL = 0,
	RC6,
	COMCAST,
	DIRECTTV,
	SWDEC,
};

enum {
	SINGLE_WORD_IF = 0,
	DOUBLE_WORD_IF = 1,
};

struct irda_protocol_info {
	char name[16];
	unsigned int burst_len;
	unsigned int modulation_len;
	unsigned int zero_len;
	unsigned int one_len;
	unsigned int repeat_len;
	unsigned int silence_len;

	unsigned int hw_decoder;
	const struct swdec_ops *swdec;
};

static const struct irda_protocol_info protocol[] = {
	{ "NEC", 9000, 560, 560, 1690, 2250, 4500, 0x5df, NULL },
	{ "SONY", 2400, 600, 600, 1200, 0, 2500, 0xdd3, NULL },
	{ "RC5", 0, 889, 889, 889, 0, 0, 0x70c, NULL },
	{ "RC6_16", 2666, 444, 444, 444, 0, 889, 0x715, NULL },
	{ "RC6_32", 2666, 444, 444, 444, 0, 889, 0xa50720, &rc6_swdec_ops },
	{ "SHARP", 0, 320, 680, 1680, 0, 0, 0x58e, NULL },
	{ "DIRECTTV", 0, 0, 0, 0, 0, 0, 0x040007cf, NULL },
	{ "COMCAST", 0, 0, 0, 0, 0, 0, 0x0800071f, &xmp_swdec_ops },
	{ "XMP", 0, 0, 0, 0, 0, 0, 0x0800071f, &xmp_swdec_ops },
	{ "RAW", 0, 0, 0, 0, 0, 0, 0, NULL },
};

struct irda_keymap {
	unsigned int scancode;
	unsigned int keycode;
};

struct irda_key_table {
	int size;
	unsigned int cust_code;
	unsigned int scancode_msk;
	unsigned int custcode_msk;
	struct irda_keymap *keys;
};

static struct irda_keymap rtk_mk5_tv_keys[] = {
	{0x18, KEY_POWER},
	{0x5A, KEY_SELECT},
	{0x58, KEY_CYCLEWINDOWS},
	{0x1A, KEY_TV},
	{0x14, KEY_HOME},
	{0x56, KEY_OPTION},
	{0x54, KEY_INFO},
	{0x19, KEY_REPLY},
	{0x57, KEY_BACK},
	{0x55, KEY_PLAY},
	{0x17, KEY_STOP},
	{0x15, KEY_ZOOM},
	{0x4F, KEY_REWIND},
	{0x4D, KEY_UP},
	{0x16, KEY_FASTFORWARD},
	{0x0C, KEY_LEFT},
	{0x4C, KEY_OK},
	{0x0E, KEY_RIGHT},
	{0x08, KEY_PREVIOUS},
	{0x48, KEY_DOWN},
	{0x09, KEY_NEXT},
	{0x4B, KEY_VOLUMEDOWN},
	{0x49, KEY_VOLUMEUP},
	{0x0B, KEY_TOUCHPAD_OFF},
	{0x0A, KEY_TOUCHPAD_ON},
	{0xEEEE, REL_X},
	{0xEEEE, REL_Y},
	{0xFFFF, BTN_LEFT},
};

static struct irda_key_table rtk_mk5_tv_key_table = {
	.keys = rtk_mk5_tv_keys,
	.size = ARRAY_SIZE(rtk_mk5_tv_keys),
	.cust_code = RTK_MK5_CUSTOMER_CODE,
	.scancode_msk = 0x00FF0000,
	.custcode_msk = 0xFFFF,
};

struct irda_protocol_desc {
	const struct swdec_ops *swdec;
	struct irda_key_table *keytable;

	unsigned int mode;
	unsigned int protocol;
	unsigned int index;
	unsigned int sample_rate;
	unsigned int accuracy;
	unsigned int dpir;
	unsigned int repeat_time;

	unsigned int lastRecvMs;
	unsigned int lastdata;
	unsigned int debounce;

	unsigned int multi_remote;
	unsigned int wakeup_key;
};

struct irda_chrdev {
	struct device *dev;
	struct cdev cdev;
	struct class *class;

	unsigned char *rxbuf;
	unsigned char *txbuf;
	struct kfifo rxfifo;
	struct kfifo txfifo;

	wait_queue_head_t rx_wait;

	unsigned int fifosize;
};

struct rtk_irda_dev {
	struct device *dev;
	struct irda_chrdev chrdev;

	void __iomem *reg;
	struct clk *clk;
	struct reset_control *rstc;

	struct irda_protocol_desc *rx_desc;
	struct irda_protocol_desc *tx_desc;

	struct timer_list key_timer;
	struct timer_list wakeup_timer;
	spinlock_t splock;

	struct input_dev *input;
	atomic_t report_cnt;

	enum rtd_chip_id chip_id;
	enum rtd_chip_revision chip_revision;

	unsigned int rx_cnt;
	unsigned int tx_cnt;
	unsigned int irq;
	unsigned int driver_mode;
	unsigned int keycode;
	unsigned int input_disable;
	bool isKeyTimerCreate;
};

static void irda_input_report(struct rtk_irda_dev *irda_dev)
{
	struct input_dev *input = irda_dev->input;
	unsigned int keycode = irda_dev->keycode;

	if (irda_dev->input_disable == true)
		return;

	atomic_inc(&irda_dev->report_cnt);
	input_report_key(input, keycode, 1);
	input_sync(input);
}

static void irda_input_report_end(struct rtk_irda_dev *irda_dev)
{
	struct input_dev *input = irda_dev->input;
	unsigned int keycode = irda_dev->keycode;

	if (irda_dev->input_disable == true)
		return;

	if (atomic_read(&irda_dev->report_cnt) != 1)
		dev_err(irda_dev->dev, "report key not in pairs");

	atomic_set(&irda_dev->report_cnt, 0);
	input_report_key(input, keycode, 0);
	input_sync(input);
}

static void irda_wakeup_timer(unsigned long data)
{
	struct rtk_irda_dev *irda_dev = (struct rtk_irda_dev *)data;
	unsigned long lock_flags;

	spin_lock_irqsave(&irda_dev->splock, lock_flags);

	irda_dev->keycode = KEY_STOP;
	irda_input_report(irda_dev);
	irda_input_report_end(irda_dev);

	spin_unlock_irqrestore(&irda_dev->splock, lock_flags);
}

static void irda_key_timer(unsigned long data)
{
	struct rtk_irda_dev *irda_dev = (struct rtk_irda_dev *)data;
	unsigned long lock_flags;

	spin_lock_irqsave(&irda_dev->splock, lock_flags);
	if (irda_dev->isKeyTimerCreate) {
		irda_dev->isKeyTimerCreate = false;
		irda_input_report_end(irda_dev);
	}
	spin_unlock_irqrestore(&irda_dev->splock, lock_flags);
}

static void irda_set_keybit(struct rtk_irda_dev *irda_dev, unsigned long *addr)
{
	struct irda_protocol_desc *desc = irda_dev->rx_desc;
	struct irda_key_table *table;
	int i, j, k;

	for (i = 0; i < irda_dev->rx_cnt; i++) {
		for (j = 0; j < (desc + i)->multi_remote; j++) {
			table = (desc + i)->keytable + j;
			for (k = 0; k < table->size; k++) {
				if (table->keys[k].scancode == 0xEEEE)
					continue;
				set_bit(table->keys[k].keycode, addr);
			}
		}
	}
}

static void irda_set_relbit(struct rtk_irda_dev *irda_dev, unsigned long *addr)
{
	struct irda_protocol_desc *desc = irda_dev->rx_desc;
	struct irda_key_table *table;
	int i, j, k;

	for (i = 0; i < irda_dev->rx_cnt; i++) {
		for (j = 0; j < (desc + i)->multi_remote; j++) {
			table = (desc + i)->keytable + j;
			for (k = 0; k < table->size; k++) {
				if (table->keys[k].scancode != 0xEEEE)
					continue;
				set_bit(table->keys[k].keycode, addr);
			}
		}
	}
}

static int irda_input_init(struct rtk_irda_dev *irda_dev)
{
	struct input_dev *input;
	int result;

	input = input_allocate_device();
	if (!input)
		return -ENOMEM;

	irda_dev->input = input;
	atomic_set(&irda_dev->report_cnt, 0);

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT(EV_REL);
	input->name = "venus_IR_input";
	input->phys = "venus/input0";
	input->setkeycode = NULL;
	input->getkeycode = NULL;

	irda_set_keybit(irda_dev, input->keybit);
	irda_set_relbit(irda_dev, input->relbit);

	result = input_register_device(input);
	if (result) {
		input_free_device(input);
		return -1;
	}

	return 0;
}

static void rtk_irda_rx_init(struct rtk_irda_dev *irda_dev,
		struct irda_protocol_desc *desc, void __iomem *reg)
{
	unsigned int val;
	unsigned int mode, idx;
	unsigned int burst, mod, one, zero, repeat, sil, sr, accur, dpir;

	if (desc->mode == hardware) {
		if (!strcmp(protocol[desc->index].name, "DIRECTTV"))
			mode = DIRECTTV;
		else if (!strcmp(protocol[desc->index].name, "COMCAST"))
			mode = COMCAST;
		else if (!strcmp(protocol[desc->index].name, "RC6_16") ||
				!strcmp(protocol[desc->index].name, "RC6_32"))
			mode = RC6;
		else
			mode = NORMAL;
		desc->protocol = mode;
	} else {
		mode = SWDEC;
		if (!strcmp(protocol[desc->index].name, "RC6_16") ||
			!strcmp(protocol[desc->index].name, "RC6_32"))
			desc->protocol = RC6;
		else
			desc->protocol = mode;
	}

	idx = desc->index;
	sr = desc->sample_rate;
	accur = desc->accuracy;
	dpir = desc->dpir;

	switch (mode) {
	case NORMAL:
	case RC6:
		writel((sr * 27 - 1), reg + IR_SF_OFF);

		burst = protocol[idx].burst_len	* accur / 400 / sr;
		mod = protocol[idx].modulation_len * accur / 100 / sr;
		zero = protocol[idx].zero_len * accur / 100 / sr;
		one = protocol[idx].one_len * accur / 100 / sr;
		repeat = protocol[idx].repeat_len * accur / 400 / sr;
		sil = protocol[idx].silence_len * accur / 400 / sr;

		val = (burst & 0xff) << 24 | (mod & 0xff) << 16 |
			(zero & 0xff) << 8 | (one & 0xff);
		writel(val, reg + IR_PSR_OFF);
		val = 1 << 16 | (repeat & 0xff) << 8 | (sil & 0xff);
		writel(val, reg + IR_PER_OFF);

		if (mode == RC6)
			writel(0x123, reg + IR_CTRL_RC6_OFF);

		if (irda_dev->chip_id == CHIP_ID_RTD1619)
			writel(protocol[idx].hw_decoder
					| IR_REPEAT_EN, reg + IR_CR_OFF);
		else
			writel(protocol[idx].hw_decoder, reg + IR_CR_OFF);
		writel(dpir * 1000 / sr, reg + IR_DPIR_OFF);
		break;
	case DIRECTTV:
		writel(0x64, reg + IR_SF_OFF);
		writel(0xbb000000, reg + IR_PSR_OFF);
		writel(0x1004b, reg + IR_PER_OFF);
		writel(0x00fa007d, reg + IRDIRECTV_TIMING1);
		writel(0x01f40177, reg + IRDIRECTV_TIMING2);
		writel(protocol[idx].hw_decoder, reg + IR_CR_OFF);
		break;
	case COMCAST:
		writel(0x1a, reg + IR_SF_OFF);
		writel(0x10001, reg + IR_PER_OFF);
		writel(0x2ee0, reg + IR_DPIR_OFF);
		writel(0x11d89385, reg + IRCOMCAST_TIMING);
		writel(protocol[idx].hw_decoder, reg + IR_CR_OFF);
		break;
	case SWDEC:
		writel(sr * 27, reg + IR_SF_OFF);
		writel(0x03138850, reg + IR_RAW_CTRL_OFF);
		writel(0x7300, reg + IR_CR_OFF);
		desc->swdec->init();
		break;
	default:
		break;
	}
}

static void rtk_irda_tx_init(struct irda_protocol_desc *desc,
				void __iomem *reg)
{
	writel(0x00000400, reg + IRTX_CFG_OFF);
	writel(0x13AB0, reg + IRTX_PWM_SETTING_OFF);
	if (!strcmp(protocol[desc->index].name, "NEC")) {
		writel(0x3B0D, reg + IRTX_TIM_OFF);
		writel(0x80000710, reg + IRTX_CFG_OFF);
		writel(0xf04, reg + IRTX_INT_EN_OFF);
	} else if (!strcmp(protocol[desc->index].name, "RAW")) {
		writel((desc->sample_rate * 27) - 1, reg + IRTX_TIM_OFF);
		writel(0x80000510, reg + IRTX_CFG_OFF);
		writel(0xf06, reg + IRTX_INT_EN_OFF);
	}
	writel(0x80000000, reg + IRTX_FIFO_ST_OFF);
	writel(0x00000000, reg + IRTX_FIFO_ST_OFF);
}

static void rtk_irda_init(struct rtk_irda_dev *irda_dev)
{
	void __iomem *reg = irda_dev->reg;
	struct irda_protocol_desc *desc;
	int i;

	writel(IRCR_RESET, reg + IR_CR_OFF);

	for (i = 0; i < irda_dev->rx_cnt; i++) {
		desc = irda_dev->rx_desc + i;
		rtk_irda_rx_init(irda_dev, desc, reg);
	}

	for (i = 0; i < irda_dev->tx_cnt; i++) {
		desc = irda_dev->tx_desc + i;
		rtk_irda_tx_init(desc, reg);
	}
}

static int rxdata_transcode(struct irda_protocol_desc *desc, unsigned int data)
{
	struct irda_key_table *table;
	unsigned int scancode, keycode;
	int shift;
	int i, j;

	for (j = 0; j < desc->multi_remote; j++) {
		table = desc->keytable + j;

		for (shift = 0; shift < 32; shift++)
			if ((1 << shift) & table->custcode_msk)
				break;
		if (((data & table->custcode_msk) >> shift) != table->cust_code)
			continue;

		for (shift = 0; shift < 32; shift++)
			if ((1 << shift) & table->scancode_msk)
				break;

		scancode = (data & table->scancode_msk) >> shift;
		for (i = 0; i < table->size; i++) {
			if (scancode == table->keys[i].scancode) {
				keycode = table->keys[i].keycode;
				return keycode;
			}
		}
	}

	return -1;
}

static int txdata_transcode(struct irda_protocol_desc *desc, unsigned int data)
{
	struct irda_key_table *table;
	unsigned int scancode;
	int i;

	table = desc->keytable;
	for (i = 0; i < table->size; i++) {
		if (data == table->keys[i].keycode) {
			scancode = table->keys[i].scancode;
			return scancode;
		}
	}
	return -1;
}

static int irda_nec_send(struct rtk_irda_dev *irda_dev,
			struct irda_protocol_desc *desc, unsigned int scancode)
{
	void __iomem *reg = irda_dev->reg;
	unsigned char burst[3], addr[6], cmd[6], cmdend;
	unsigned short necaddr, neccmd;
	unsigned int custcode, val;
	int offset;
	int i;

	custcode = desc->keytable->cust_code;

	necaddr = (unsigned short)(custcode & 0x0000ffff);
	neccmd = (unsigned short)((~(scancode & 0x000000ff)) << 8 |
						(scancode & 0x000000ff));

	memset(addr, 0 , sizeof(addr));
	memset(cmd, 0 , sizeof(cmd));

	burst[2] = burst[1] = 0xff;
	burst[0] = 0x0;
	cmdend = 0x80;

	offset = 8 * sizeof(addr) - 1;
	for (i=0; i<(8 * sizeof(necaddr)); i++) {
		if (offset < 0) {
			pr_err("IRTX: offset error\n");
			return -1;
		} else if (necaddr & (0x1 << i)) {
			__set_bit(offset, (unsigned long *)addr);
			offset = offset - 4;
		} else {
			__set_bit(offset, (unsigned long *)addr);
			offset = offset - 2;
		}
	}

	offset = 8 * sizeof(cmd) - 1;
	for (i=0; i<(8*sizeof(neccmd)); i++) {
		if (offset < 0) {
			pr_err("IRTX: offset error\n");
			return -1;
		} else if (neccmd & (0x1 << i)){
			__set_bit(offset, (unsigned long *)cmd);
			offset = offset - 4;
		} else {
			__set_bit(offset, (unsigned long *)cmd);
			offset = offset - 2;
		}
	}
	val = ((burst[2]<<24) | (burst[1]<<16) |(burst[0]<<8) | addr[5]);
	writel(val, reg + IRTX_FIFO_OFF);

	val = ((addr[4]<<24) | (addr[3]<<16) | (addr[2]<<8) | addr[1]);
	writel(val, reg + IRTX_FIFO_OFF);

	val = ((addr[0]<<24) | (cmd[5]<<16) | (cmd[4]<<8) | cmd[3] );
	writel(val, reg + IRTX_FIFO_OFF);

	val = ((cmd[2]<<24) | (cmd[1]<<16) | (cmd[0]<<8) | cmdend );
	writel(val, reg + IRTX_FIFO_OFF);

	return 0;
}

static void irda_key_handle(struct rtk_irda_dev *irda_dev,
			struct irda_protocol_desc *desc, int code, int repeat)
{
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	int time;
	int keycode;

	time = jiffies_to_msecs(jiffies) - desc->lastRecvMs;
	if (desc->debounce > 0 && time < desc->debounce)
		return;

	if (desc->protocol == RC6) {
		code = ~(code) & 0x1fffff;
		if ((desc->lastdata & 0xffff) == (code & 0xffff))
			repeat = 1;
		desc->lastdata = code;
	}
	dev_info(irda_dev->dev, "scancode = 0x%x\n", code);

	kfifo_in(&chrdev->rxfifo, &code, sizeof(unsigned int));
	if (irda_dev->driver_mode == DOUBLE_WORD_IF)
		kfifo_in(&chrdev->rxfifo, (unsigned char *)&repeat,
						sizeof(unsigned int));
	wake_up_interruptible(&chrdev->rx_wait);
	desc->lastRecvMs = jiffies_to_msecs(jiffies);

	keycode = rxdata_transcode(desc, code);
	if (keycode < 0)
		return;

	if (desc->mode == software)
		if (time < desc->repeat_time && irda_dev->keycode == keycode)
			repeat = 1;

	if (repeat == 1 && (irda_dev->isKeyTimerCreate == true ||
		time > desc->repeat_time))
		return;

	if (irda_dev->isKeyTimerCreate) {
		irda_dev->isKeyTimerCreate = false;
		irda_input_report_end(irda_dev);
	}
	irda_dev->keycode = keycode;
	irda_dev->isKeyTimerCreate = true;
	irda_input_report(irda_dev);

	dev_info(irda_dev->dev, "keycode = 0x%x\n", keycode);
}

static irqreturn_t rtk_irda_isr(int irq, void *dev_id)
{
	struct rtk_irda_dev *irda_dev = (struct rtk_irda_dev *)dev_id;
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	struct irda_protocol_desc *desc;
	void __iomem *reg = irda_dev->reg;
	unsigned int val;
	unsigned int data;
	unsigned int fifoval[IRDA_RXFIFO], fifolv = 0;
	int keycode;
	int repeat = 0;
	int i;

	val = readl(reg + IR_SR_OFF);

	desc = irda_dev->rx_desc;
	if (val & IR_DVF) {
		if (val & IR_REPEAT)
			repeat = 1;
		writel((IR_DVF | IR_REPEAT), reg + IR_SR_OFF);
		data = readl(reg + IR_RP_OFF);
		for (i = 0; i < irda_dev->rx_cnt; i++)
			if (desc[i].mode == hardware)
				break;
		if (i != irda_dev->rx_cnt)
			irda_key_handle(irda_dev, desc + i, data, repeat);
		mod_timer(&irda_dev->key_timer,
			jiffies + msecs_to_jiffies(desc->repeat_time));
	}
	if (val & (IR_RAWDOV | IR_RAWDVF)) {
		writel((val & (~0xf)), reg + IR_SR_OFF);
		fifolv = readl(reg + IR_RAW_WL_OFF) & 0x3f;
		for (i = 0; i < fifolv; i++)
			fifoval[i] = readl(reg + IR_RAW_FF_OFF);
		for (i = 0; i < irda_dev->rx_cnt; i++) {
			if (desc[i].mode == hardware)
				continue;
			if (desc[i].swdec->decoder) {
				keycode = desc[i].swdec->decoder(
							fifoval, fifolv);
				if (keycode < 0)
					continue;
			} else {
				kfifo_in(&chrdev->rxfifo, fifoval, fifolv * 4);
				continue;
			}
			irda_key_handle(irda_dev, desc + i, keycode, repeat);
			mod_timer(&irda_dev->key_timer,
				jiffies + msecs_to_jiffies(desc->repeat_time));
		}
	}

	desc = irda_dev->tx_desc;
	val = readl(reg + IRTX_INT_ST_OFF);

	if (!strcmp(protocol[desc->index].name, "RAW")) {
	
	}
	if (val & 0x4) {
		val = readl(reg + IRTX_CFG_OFF);
		writel(val & ~0x1, reg + IRTX_CFG_OFF);

		writel(0x80000000, reg + IRTX_FIFO_ST_OFF);	//irtx fifo reset
		writel(0x00000000, reg + IRTX_FIFO_ST_OFF);	//irtx fifo normal
	}

	return IRQ_HANDLED;
}

static int get_irda_protocol_index(const char *name, int mode, int irmode)
{
	int cnt;
	int index;

	cnt = ARRAY_SIZE(protocol);
	for (index = 0; index < cnt; index++)
		if (!strcmp(name, protocol[index].name))
			break;
	if (index == cnt)
		return -1;

	switch (irmode) {
	case irda_rx:
		if (mode == software) {
			if (!protocol[index].swdec)
				return -1;
		} else {
			if (!protocol[index].hw_decoder)
				return -1;
		}
		break;

	case irda_tx:
		break;
	default:
		break;
	}

	return index;
}

ssize_t irda_show_keytable(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);
	struct irda_protocol_desc *desc = irda_dev->rx_desc;

//	if(desc->keytable == NULL)
//		return sprintf(buf, "key table is not exist!\n");
	return sprintf(buf, "table size=%d\n", desc->keytable->size);
}

ssize_t irda_store_keytable(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);
	struct irda_protocol_desc *desc = irda_dev->rx_desc;
	struct irda_key_table *keytbl = desc->keytable;
	struct irda_keymap *key;
	struct file *fp;
	struct kstat stat;
	char filename[64] = {0};
	char *buffer;
	char *token, *vtoken, *cur;
	unsigned int keymap_size = 0;
	mm_segment_t old_fs = get_fs();
	unsigned int idx = 0;

	if (!buf || count < 1) {
		dev_err(dev, "%s - buffer is null!\n", __func__);
		return count;
	}
	sscanf(buf, "%s", filename);

	set_fs(KERNEL_DS);
	if (vfs_stat(filename, &stat) < 0) {
		dev_err(dev, "%s - file fail!\n", __func__);
		set_fs(old_fs);
		return count;
	}
	set_fs(old_fs);

	fp = filp_open(filename, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		dev_err(dev, "%s - can't open file!\n", __func__);
		return count;
	}

	buffer = devm_kzalloc(dev, stat.size, GFP_KERNEL);
	if (!buffer)
		goto kzalloc_fail;

	cur = buffer;
	if (kernel_read(fp, 0, buffer, stat.size) < 0)
		goto get_file_fail;

	filp_close(fp, 0);

	while ((token = strsep(&cur, "\n"))) {
		vtoken = strsep(&token, "=");
		if (strcmp(vtoken, "cust-code") == 0) {
			if (!sscanf(token, "0x%X", &(keytbl->cust_code)))
				goto format_err;
		} else if (strcmp(vtoken, "scancode-msk") == 0) {
			if (!sscanf(token, "0x%08X", &(keytbl->scancode_msk)))
				goto format_err;
		} else if (strcmp(vtoken, "custcode-msk") == 0) {
			if (!sscanf(token, "0x%08X", &(keytbl->custcode_msk)))
				goto format_err;
		} else if (strcmp(vtoken, "keymap-size") == 0) {
			if (!sscanf(token, "%d", &keymap_size))
				goto format_err;
		} else if (strcmp(vtoken, "keymap-tbl") == 0) {
			if (keymap_size < 1) {
				dev_err(dev, "%s - keysize error\n", __func__);
				return count;
			}
			key = devm_kzalloc(dev, keymap_size, GFP_KERNEL);
			if (!key)
				return count;

			devm_kfree(dev, keytbl->keys);
			keytbl->keys = key;
			keytbl->size = keymap_size;

			while ((token = strsep(&cur, "\n")) &&
						(idx < keymap_size)) {
				vtoken = strsep(&token, "=");
				if (strlen(vtoken) > 1) {
					if (!sscanf(vtoken, "0x%X", &(key[idx].scancode)))
						goto format_err;
					if (!sscanf(token, "%d", &(key[idx].keycode)))
						goto format_err;
					idx++;
				}
			}
			break;
		}
		continue;
format_err:
		dev_err(dev, "%s - replace table format error\n", __func__);
	}
	return count;

get_file_fail:
	dev_err(dev, "%s - read file fail\n", __func__);
	devm_kfree(dev, buffer);
kzalloc_fail:
	filp_close(fp, 0);
	return count;
}

ssize_t irda_input_ctrl_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);

	return sprintf(buf, "=> %d\n", irda_dev->input_disable);
}

ssize_t irda_input_ctrl_store(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);

	sscanf(buf, "%d", &irda_dev->input_disable);
	return count;
}

static DEVICE_ATTR(replace_table, S_IRUGO | S_IWUSR,
		irda_show_keytable, irda_store_keytable);
static DEVICE_ATTR(input_disable, S_IRUGO | S_IWUSR, irda_input_ctrl_show,
		irda_input_ctrl_store);

static struct attribute *irda_dev_attrs[] = {
	&dev_attr_replace_table.attr,
	&dev_attr_input_disable.attr,
	NULL,
};

static struct attribute_group irda_attr_group = {
	.attrs = irda_dev_attrs,
};

int rtk_irda_open(struct inode *inode, struct file *filp)
{
	struct rtk_irda_dev *irda_dev;
	struct irda_chrdev *chrdev;

	chrdev = container_of(inode->i_cdev, struct irda_chrdev, cdev);
	irda_dev = container_of(chrdev, struct rtk_irda_dev, chrdev);
	filp->private_data = irda_dev;

	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		if (irda_dev->tx_cnt == 0)
			return -1;
		kfifo_reset(&chrdev->txfifo);
	}
	if ((filp->f_flags & O_ACCMODE) == O_RDONLY) {
		if (irda_dev->rx_cnt == 0)
			return -1;
		kfifo_reset(&chrdev->rxfifo);
	}
	return 0;
}

ssize_t rtk_irda_read(struct file *filp, char __user *buf,
			size_t count, loff_t *f_pos)
{
	struct rtk_irda_dev *irda_dev = filp->private_data;
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	int rCnt = count;
	int len;

restart:
	if (wait_event_interruptible
		(chrdev->rx_wait, kfifo_len(&chrdev->rxfifo) > 0)) {
		if (try_to_freeze())
			goto restart;
	}

	if (kfifo_len(&chrdev->rxfifo) < count)
		rCnt = kfifo_len(&chrdev->rxfifo);

	len = kfifo_out(&chrdev->rxfifo, chrdev->rxbuf, rCnt);
	if (!len)
		return -EFAULT;
	rCnt = len;
	if (copy_to_user(buf, chrdev->rxbuf, len)) {
		dev_err(irda_dev->dev, "copy fail\n");
		return -EFAULT;
	}

	return rCnt;
}

ssize_t rtk_irda_write(struct file *filp, const char __user *buf,
			size_t count, loff_t *f_pos)
{
	struct rtk_irda_dev *irda_dev = filp->private_data;
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	struct irda_protocol_desc *desc;
	void __iomem *reg = irda_dev->reg;
	unsigned int val;
	int wCnt;
	int keycode, scancode;
	int i;

	desc = irda_dev->tx_desc;

	wCnt = kfifo_avail(&chrdev->txfifo);
	if (count < wCnt)
		wCnt = count;
	if (copy_from_user(chrdev->txbuf, buf, wCnt)) {
		dev_err(irda_dev->dev, "copy from user error\n");
		return -EFAULT;
	}

	if (!strcmp(protocol[desc->index].name, "RAW")) {
		val = readl(reg + IRTX_CFG_OFF);
		if (val & 0x1) {
			kfifo_in(&chrdev->txfifo, chrdev->txbuf, wCnt);
			return wCnt;
		}
		if(wCnt <= FIFO_DEPTH * 4) {
			for(i=0; i<(wCnt/4); i++)
				writel( *((int *)(chrdev->txbuf) + i), reg + IRTX_FIFO_OFF);
			writel(0x80000511, reg + IRTX_CFG_OFF);
		} else {
			for(i=0; i<FIFO_DEPTH; i++)
				writel( *((int *)(chrdev->txbuf) + i), reg + IRTX_FIFO_OFF);
			writel(0x80000511, reg + IRTX_CFG_OFF);
			kfifo_in(&chrdev->txfifo, chrdev->txbuf + FIFO_DEPTH * 4, wCnt - FIFO_DEPTH * 4);
		}
	} else {
		sscanf(chrdev->txbuf, "%d", &keycode);
		if (desc == NULL)
			return -1;

		scancode = txdata_transcode(desc, keycode);
		if (scancode >= 0) {
			irda_nec_send(irda_dev, desc, scancode);
			val = readl(reg + IRTX_CFG_OFF);
			writel(val | 0x1, reg + IRTX_CFG_OFF);
		}
	}
	return wCnt;
}

unsigned int rtk_irda_poll(struct file *filp, poll_table *wait)
{
	struct rtk_irda_dev *irda_dev = filp->private_data;
	struct irda_chrdev *chrdev = &irda_dev->chrdev;

	poll_wait(filp, &chrdev->rx_wait, wait);

	if (kfifo_len(&chrdev->rxfifo) > 0)
		return POLLIN | POLLRDNORM;
	else
		return 0;
}

long rtk_irda_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct rtk_irda_dev *irda_dev = filp->private_data;
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	void __iomem *reg = irda_dev->reg;
	int ret = 0;
	int i;

	switch (cmd) {
	case VENUS_IR_IOC_SET_IRPSR:
		writel(arg, reg + IR_PSR_OFF);
		break;
	case VENUS_IR_IOC_SET_IRPER:
		writel(arg, reg + IR_PER_OFF);
		break;
	case VENUS_IR_IOC_SET_IRSF:
		writel(arg, reg + IR_SF_OFF);
		break;
	case VENUS_IR_IOC_SET_IRCR:
		writel(arg, reg + IR_CR_OFF);
		break;
	case VENUS_IR_IOC_SET_IRIOTCDP:
		writel(arg, reg + IR_DPIR_OFF);
		break;
	case VENUS_IR_IOC_SET_PROTOCOL:
	case VENUS_IR_IOC_SET_FIRST_REPEAT_DELAY:
	case VENUS_IRTX_IOC_SET_TX_TABLE:
		dev_err(irda_dev->dev, "ioctl not support now\n");
		break;
	case VENUS_IR_IOC_FLUSH_IRRP:
		kfifo_reset(&chrdev->rxfifo);
		break;
	case VENUS_IR_IOC_SET_DEBOUNCE:
		for (i = 0; i < irda_dev->rx_cnt; i++)
			irda_dev->rx_desc[i].debounce = (unsigned int)arg;
		break;
	case VENUS_IR_IOC_SET_DRIVER_MODE:
		if ((unsigned int)arg >= 2) {
			ret = -EFAULT;
		} else {
			kfifo_reset(&chrdev->rxfifo);
			irda_dev->driver_mode = (unsigned int)arg;
		}
		break;
	default:
		ret = -ENOIOCTLCMD;
		break;
	}
	return ret;
}
#ifdef CONFIG_64BIT
long rtk_irda_compat_ioctl(struct file *filp, unsigned int cmd,
			unsigned long arg)
{
	long (*ioctl)(struct file*, unsigned int, unsigned long);

	if (!filp->f_op->unlocked_ioctl)
		return -ENOTTY;

	ioctl = filp->f_op->unlocked_ioctl;

	switch (cmd) {
	case VENUS_IR_IOC_SET_IRPSR:
	case VENUS_IR_IOC_SET_IRPER:
	case VENUS_IR_IOC_SET_IRSF:
	case VENUS_IR_IOC_SET_IRCR:
	case VENUS_IR_IOC_SET_IRIOTCDP:
	case VENUS_IR_IOC_SET_PROTOCOL:
	case VENUS_IR_IOC_FLUSH_IRRP:
	case VENUS_IR_IOC_SET_DEBOUNCE:
	case VENUS_IR_IOC_SET_FIRST_REPEAT_DELAY:
	case VENUS_IR_IOC_SET_DRIVER_MODE:
	case VENUS_IRTX_IOC_SET_TX_TABLE:
	case VENUS_IRRX_RAW_STOP:
		return ioctl(filp, cmd, (unsigned long)compat_ptr(arg));
	default:
		return -EFAULT;
	}
}
#endif
static const struct file_operations rtk_irda_fops = {
	.owner = THIS_MODULE,
	.open = rtk_irda_open,
	.read = rtk_irda_read,
	.write = rtk_irda_write,
	.poll = rtk_irda_poll,
	.unlocked_ioctl = rtk_irda_ioctl,
#ifdef CONFIG_64BIT 
	.compat_ioctl = rtk_irda_compat_ioctl,
#endif
};

static int create_irda_chrdev(struct rtk_irda_dev *irda_dev)
{
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	struct device *dev = irda_dev->dev;
	struct device_node *np = irda_dev->dev->of_node;
	struct class *class;
	dev_t dev_no;

	if (of_property_read_u32(np, "fifo-size", &chrdev->fifosize))
		chrdev->fifosize = 128;
	if (irda_dev->rx_cnt) {
		if (kfifo_alloc(&chrdev->rxfifo, chrdev->fifosize, GFP_KERNEL))
			goto chrdev_malloc_fail;
		chrdev->rxbuf = devm_kzalloc(dev, chrdev->fifosize, GFP_KERNEL);
		if (!chrdev->rxbuf)
			goto chrdev_malloc_fail;
	}
	if (irda_dev->tx_cnt) {
		if (kfifo_alloc(&chrdev->txfifo, chrdev->fifosize, GFP_KERNEL))
			goto chrdev_malloc_fail;
		chrdev->txbuf = devm_kzalloc(dev, chrdev->fifosize, GFP_KERNEL);
		if (!chrdev->txbuf)
			goto chrdev_malloc_fail;
	}

	dev_no = MKDEV(IRDA_CDEV_MAJOR, IRDA_CDEV_MINOR);
	if (register_chrdev_region(dev_no, 1, "rtk_irda_cdev"))
		goto chrdev_malloc_fail;

	cdev_init(&chrdev->cdev, &rtk_irda_fops);
	chrdev->cdev.ops = &rtk_irda_fops;
	if (cdev_add(&chrdev->cdev, dev_no, 1))
		goto cdev_add_fail;

	class = class_create(THIS_MODULE, "rtk_irda_class");
	chrdev->dev = device_create(class, NULL, dev_no, &chrdev->cdev, "venus_ir");
	chrdev->class = class;

	init_waitqueue_head(&chrdev->rx_wait);
	return 0;
cdev_add_fail:
	unregister_chrdev_region(dev_no, 1);
chrdev_malloc_fail:
	if (&chrdev->rxfifo)
		kfifo_free(&chrdev->rxfifo);
	if (&chrdev->txfifo)
		kfifo_free(&chrdev->txfifo);
	return -1;
}

static int get_desc_from_dtb(struct device *dev,
				struct irda_protocol_desc *desc,
				int mode)
{
	struct device_node *node = dev->of_node;
	struct device_node *np;
	struct irda_key_table *table;
	struct irda_keymap *keys;
	const unsigned int *pkey;
	const char *str;
	char name[32];
	int cnt = 0;
	int tmp;
	int i, j;

	for_each_child_of_node(node, np) {
		if (mode == irda_rx) {
			if (of_property_read_string(np, "irrx-protocol", &str))
				continue;
		} else {
			if (of_property_read_string(np, "irtx-protocol", &str))
				continue;
		}
		if (of_property_read_u32(np, "transcode-mode", &desc->mode))
			desc->mode = 1;

		if (of_property_read_u32(np, "sample-rate", &desc->sample_rate))
			desc->sample_rate = 20;

		if (of_property_read_u32(np, "reg-ir-dpir", &desc->dpir))
			desc->dpir = 50;

		if (of_property_read_u32(np, "debounce", &desc->debounce))
			desc->debounce = 0;

		if (of_property_read_u32(np, "accuracy", &desc->accuracy))
			desc->accuracy = 70;

		if (of_property_read_u32(np, "repeat-time", &desc->repeat_time))
			desc->repeat_time = 250;

		if (of_property_read_u32(np, "wakeup-key", &desc->wakeup_key))
			desc->wakeup_key = 116;

		dev_err(dev, "wakeup key = %d\n", desc->wakeup_key);
		desc->index = get_irda_protocol_index(str, desc->mode, mode);
		if (desc->index < 0)
			continue;

		if (desc->mode == software)
			desc->swdec = protocol[desc->index].swdec;

		// start get key table
		if (of_property_read_u32(np, "multi-remote", &desc->multi_remote))
			desc->multi_remote = 1;

		table = devm_kzalloc(dev, sizeof(*table) * desc->multi_remote,
				GFP_KERNEL);
		if (!table)
			continue;
		desc->keytable = table;

		pkey = of_get_property(np, "keymap-tbl", &tmp);
		if (!pkey) {
			dev_err(dev, "can't find key table, use default\n");
			memcpy(table, &rtk_mk5_tv_key_table,
						sizeof(rtk_mk5_tv_key_table));
			goto get_next_keytable;
		}
		table->keys = devm_kzalloc(dev, tmp, GFP_KERNEL);
		table->size = tmp / (2 * sizeof(unsigned int));
		keys = table->keys;
		for (i = 0; i < table->size; i++) {
			keys[i].scancode = of_read_number(pkey, 1 + (i * 2));
			keys[i].keycode = of_read_number(pkey, 2 + (i * 2));
		}
		if (of_property_read_u32(np, "cust-code", &table->cust_code))
			table->cust_code = RTK_MK5_CUSTOMER_CODE;
		if (of_property_read_u32(np, "scancode-msk", &table->scancode_msk))
			table->scancode_msk = 0x00FF0000;
		if (of_property_read_u32(np, "custcode-msk", &table->custcode_msk))
			table->custcode_msk = 0xFFFF;

get_next_keytable:
		for (i=1; i<desc->multi_remote; i++) {
			sprintf(name, "cust-code%d", i);
			if (of_property_read_u32(np, name, &table[i].cust_code))
				table[i].cust_code = table->cust_code;
			sprintf(name, "scancode-msk%d", i);
			if (of_property_read_u32(np, name, &table[i].scancode_msk))
				table[i].scancode_msk = table->scancode_msk;
			sprintf(name, "custcode-msk%d", i);
			if (of_property_read_u32(np, name, &table[i].custcode_msk))
				table[i].custcode_msk = table->custcode_msk;

			sprintf(name, "keymap-tbl%d", i);
			pkey = of_get_property(np, name, &tmp);
			if (!pkey) {
				table[i].keys = table->keys;
				table[i].size = table->size;
				continue;
			}

			table[i].keys = devm_kzalloc(dev, tmp, GFP_KERNEL);
			table[i].size = tmp / (2 * sizeof(unsigned int));
			keys = table[i].keys;
			for (j = 0; j < table[i].size; j++) {
				keys[j].scancode = of_read_number(pkey, 1 + (j * 2));
				keys[j].keycode = of_read_number(pkey, 2 + (j * 2));
			}
		}
		cnt++;
		desc++;
	}
	return cnt;
}

#ifdef CONFIG_PM
static int irda_set_wakeup_keys(struct rtk_irda_dev *irda_dev,
				struct ipc_shm_irda *p_table)
{
	struct irda_protocol_desc *desc;
	struct irda_key_table *table;
	int i, j, k;
	int cnt = 0;

	for (i = 0; i < irda_dev->rx_cnt; i++) {
		desc = irda_dev->rx_desc + i;
		for (j = 0; j < desc->multi_remote; j++) {
			table = desc->keytable + j;
			p_table->key_tbl[cnt].protocol = htonl(0);
			p_table->key_tbl[cnt].scancode_mask = htonl(table->scancode_msk);
			p_table->key_tbl[cnt].cus_mask = htonl(table->custcode_msk);
			p_table->key_tbl[cnt].cus_code = htonl(table->cust_code);

			for (k = 0; k < table->size; k++) {
				if (desc->wakeup_key == table->keys[k].keycode) {
					p_table->key_tbl[cnt].wakeup_scancode =
							htonl(table->keys[k].scancode);
					break;
				}
			}
			cnt ++;
		}
	}
	p_table->dev_count = htonl(cnt);
	p_table->ipc_shm_ir_magic = htonl(0x49525641);

	return 0;
}
#endif

int rtk_irda_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_irda_dev *irda_dev;
	struct irda_protocol_desc *desc;
#ifdef CONFIG_PM
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
	struct ipc_shm_irda __iomem *ir_ipc;
	unsigned int phy_ir_ipc;
#endif
	int ret;

	/* malloc memory for irda device */
	irda_dev = devm_kzalloc(dev, sizeof(*irda_dev), GFP_KERNEL);
	if (!irda_dev)
		goto mem_alloc_fail;

	irda_dev->dev = dev;
	dev->driver_data = irda_dev;

	irda_dev->chip_id = get_rtd_chip_id();
	irda_dev->chip_revision = get_rtd_chip_revision();

	spin_lock_init(&irda_dev->splock);

	/* Read parameter from DTB */
	irda_dev->reg = of_iomap(dev->of_node, 1);
	if (!irda_dev->reg)
		goto read_dtb_fail;

	irda_dev->clk = clk_get(dev, NULL);
	irda_dev->rstc = reset_control_get(dev, NULL);
	if (!irda_dev->clk || !irda_dev->rstc)
		goto read_dtb_fail;

	irda_dev->irq = irq_of_parse_and_map(dev->of_node, 0);

	ret = of_get_child_count(dev->of_node);
	if (!ret)
		goto read_dtb_fail;
	desc = devm_kzalloc(dev, sizeof(*desc) * ret, GFP_KERNEL);
	if (!desc)
		goto mem_alloc_fail;

	irda_dev->rx_desc = desc;
	irda_dev->rx_cnt = get_desc_from_dtb(dev, irda_dev->rx_desc, irda_rx);

	irda_dev->tx_desc = desc + irda_dev->rx_cnt;
	irda_dev->tx_cnt = get_desc_from_dtb(dev, irda_dev->tx_desc, irda_tx);

	if (irda_dev->rx_cnt == 0 && irda_dev->tx_cnt == 0)
		goto read_dtb_fail;

	/* create character device for irda module */
	ret = create_irda_chrdev(irda_dev);
	if (ret)
		dev_err(dev, "create irda character device fail\n");

	irda_input_init(irda_dev);

	ret = sysfs_create_group(&pdev->dev.kobj, &irda_attr_group);
	if (ret)
		dev_err(dev, "create irda sysfs fail\n");

	setup_timer(&irda_dev->key_timer, irda_key_timer, (unsigned long)irda_dev);
	setup_timer(&irda_dev->wakeup_timer, irda_wakeup_timer, (unsigned long)irda_dev);
	irda_dev->key_timer.expires = jiffies + msecs_to_jiffies(70);

	/* Start realtek irda initial */
	reset_control_deassert(irda_dev->rstc);
	clk_prepare_enable(irda_dev->clk);

	rtk_irda_init(irda_dev);

	if (request_irq(irda_dev->irq, rtk_irda_isr, IRQF_SHARED,
			"RTK_IRDA", irda_dev)) {
		dev_err(dev, "cannot register IRQ\n");
		goto read_dtb_fail;
	}

#ifdef CONFIG_PM
	ir_ipc = (void __iomem *)(IPC_SHM_VIRT + sizeof(*ipc));
	phy_ir_ipc = RPC_COMM_PHYS + 0xC4 + sizeof(*ipc);

#if defined(CONFIG_ARCH_RTD16xx) || defined(CONFIG_ARCH_RTD13xx)
	irda_set_wakeup_keys(irda_dev, &pcpu_data_irda);
#else
	irda_set_wakeup_keys(irda_dev, ir_ipc);
#endif
	writel(cpu_to_be32(phy_ir_ipc), &(ipc->ir_extended_tbl_pt));
#endif
	return 0;

read_dtb_fail:
	dev_err(dev, "%s read dtb fail\n", __func__);
	return -1;

mem_alloc_fail:
	dev_err(dev, "%s mem alloc fail\n", __func__);
	return -ENOMEM;
}

int rtk_irda_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);
	struct irda_chrdev *chrdev = &irda_dev->chrdev;
	dev_t dev_no;

	del_timer_sync(&irda_dev->wakeup_timer);

	writel(0x80000000, irda_dev->reg + IR_CR_OFF);

	free_irq(irda_dev->irq, rtk_irda_isr);

	dev_no = MKDEV(IRDA_CDEV_MAJOR, IRDA_CDEV_MINOR);
	device_destroy(chrdev->class, dev_no);
	class_destroy(chrdev->class);
	cdev_del(&chrdev->cdev);

	return 0;
}

#ifdef CONFIG_PM
static int rtk_irda_suspend(struct device *dev)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);
	void __iomem *reg = irda_dev->reg;
	unsigned int regValue;

	dev_info(dev, "Enter %s\n", __func__);

	while (readl(reg + IR_SR_OFF) & 0x1) {
		writel(0x00000003, reg + IR_SR_OFF); /* clear IRDVF */
		regValue = readl(reg + IR_RP_OFF); /* read IRRP */
	}
	regValue = readl(reg + IR_CR_OFF);
	regValue = regValue & ~(0x400);
	writel(regValue, reg + IR_CR_OFF);

	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static void rtk_irda_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	rtk_irda_suspend(dev);

	return;
}

static int rtk_irda_resume(struct device *dev)
{
	struct rtk_irda_dev *irda_dev = dev_get_drvdata(dev);
	void __iomem *reg = irda_dev->reg;
	unsigned int regValue;

	dev_info(dev, "Enter %s\n", __func__);

	while (readl(reg + IR_SR_OFF) & 0x1) {
		writel(0x00000003, reg + IR_SR_OFF); /* clear IRDVF */
		regValue = readl(reg + IR_RP_OFF); /* read IRRP */
	}
	rtk_irda_init(irda_dev);

	regValue = readl(reg + IR_CR_OFF);
	regValue = regValue | 0x400;
	writel(regValue, reg + IR_CR_OFF);

	mod_timer(&irda_dev->wakeup_timer, (jiffies + (msecs_to_jiffies(1000))));

	dev_info(dev, "Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_irda_pm_ops = {
	.suspend = rtk_irda_suspend,
	.resume = rtk_irda_resume,
};

#else

static const struct dev_pm_ops rtk_irda_pm_ops = {};

#endif

static const struct of_device_id rtk_irda_ids[] = {
	{ .compatible = "Realtek,rtk-irda" },
	{ /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, rtk_irda_ids);

static struct platform_driver rtk_irda_driver = {
	.driver = {
		.name = "rtk-irda",
		.owner = THIS_MODULE,
		.of_match_table = rtk_irda_ids,
#ifdef CONFIG_PM
		.pm = &rtk_irda_pm_ops,
#endif /* CONFIG_PM */
	},
	.probe = rtk_irda_probe,
	.remove = rtk_irda_remove,
#ifdef CONFIG_PM
	.shutdown = rtk_irda_shutdown,
#endif /* CONFIG_PM */
};

module_platform_driver(rtk_irda_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("REALTEK Corporation");
MODULE_ALIAS("platform:irda");
