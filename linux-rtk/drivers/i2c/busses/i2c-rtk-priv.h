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

#include <linux/i2c.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/atomic.h>

#include "i2c-rtk.h"
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
extern int ta_i2c_init(void);
extern void ta_hdcp_lib_set_i2c_enable(unsigned int  i2c_enable_value);
#endif

#define FIFO_THRESHOLD 4
#define ADDR_10BITS_MASK 0x3FF
#define ADDR_7BITS_MASK 0x7F

#ifdef CONFIG_ARCH_RTD119X
#define I2C_ID_MASK 0x7F

#elif defined(CONFIG_ARCH_RTD129x)
#define I2C_ID_MASK 0x3F

#elif defined(CONFIG_ARCH_RTD139x)

#define I2C_ID_MASK 0x23

#elif defined(CONFIG_ARCH_RTD16xx)

#define I2C_ID_MASK 0x3B

#elif defined(CONFIG_ARCH_RTD13xx)

#define I2C_ID_MASK 0x3B

#endif


/* DEFINE FLAG ENABLE */
#define MINIMUM_DELAY_EN
#define SPIN_LOCK_PROTECT_EN
#define EDID_4BLOCK_SUPPORT /* For HDMI TX CTS 7-1 */

/* DEBUG */
#ifdef DEV_DEBUG
#define RTK_DEBUG(fmt, ...) pr_info(fmt, ##__VA_ARGS__)
#else
#define RTK_DEBUG(fmt, ...)
#endif /* DEV_DEBUG */

/* LOG EVENT */
#ifdef I2C_PROFILEING_EN
#define LOG_EVENT(x) log_event(x)
#else
#define LOG_EVENT(x)
#endif /* LOG EVENT */

#define EVENT_START_XFER 4
#define EVENT_STOP_XFER 5
#define EVENT_ENTER_ISR 6
#define EVENT_EXIT_ISR 7
#define EVENT_EXIT_TIMEOUT 8

/* SPINLOCK */
#ifdef SPIN_LOCK_PROTECT_EN
#if defined(CONFIG_I2C_RTK_SECURE_ACCESS)
#define LOCK_RTK_I2C(a, b) spin_lock(a)
#define UNLOCK_RTK_I2C(a, b) spin_unlock(a)
#else
#define LOCK_RTK_I2C(a, b) spin_lock_irqsave(a, b)
#define UNLOCK_RTK_I2C(a, b) spin_unlock_irqrestore(a, b)
#endif
#else
#define LOCK_RTK_I2C(a, b) do {} while (0)
#define UNLOCK_RTK_I2C(a, b) do {} while (0)
#endif /* SPIN_LOCK_PROTECT_EN */

/* RTK I2C API */
#define wr_reg(x, y) writel(y, (unsigned int *)x)
#define rd_reg(x) readl((unsigned int *)x)
#define SET_I2C_ISR(adp, x) wr_reg(adp->reg_map.I2C_ISR, x)
#define GET_I2C_ISR(adp) rd_reg(adp->reg_map.I2C_ISR)
#ifndef CONFIG_I2C_RTK_SECURE_ACCESS
#define SET_IC_ENABLE(adp, x) wr_reg(adp->reg_map.IC_ENABLE, x)
#endif
#define GET_IC_ENABLE(adp) rd_reg(adp->reg_map.IC_ENABLE)
#define SET_IC_CON(adp, x) wr_reg(adp->reg_map.IC_CON, x)
#define GET_IC_CON(adp) rd_reg(adp->reg_map.IC_CON)
#define SET_IC_SAR(adp, x) wr_reg(adp->reg_map.IC_SAR, x)
#define GET_IC_SAR(adp) rd_reg(adp->reg_map.IC_SAR)
#define SET_IC_TAR(adp, x) wr_reg(adp->reg_map.IC_TAR, x)
#define GET_IC_TAR(adp) rd_reg(adp->reg_map.IC_TAR)
#define SET_IC_DATA_CMD(adp, x) wr_reg(adp->reg_map.IC_DATA_CMD, x)
#define GET_IC_DATA_CMD(adp) rd_reg(adp->reg_map.IC_DATA_CMD)
#define SET_IC_SS_SCL_HCNT(adp, x) wr_reg(adp->reg_map.IC_SS_SCL_HCNT, x)
#define SET_IC_SS_SCL_LCNT(adp, x) wr_reg(adp->reg_map.IC_SS_SCL_LCNT, x)
#define SET_IC_FS_SCL_HCNT(adp, x) wr_reg(adp->reg_map.IC_FS_SCL_HCNT, x)
#define SET_IC_FS_SCL_LCNT(adp, x) wr_reg(adp->reg_map.IC_FS_SCL_LCNT, x)
#define SET_IC_HS_SCL_HCNT(adp, x) wr_reg(adp->reg_map.IC_HS_SCL_HCNT, x)
#define SET_IC_HS_SCL_LCNT(adp, x) wr_reg(adp->reg_map.IC_HS_SCL_LCNT, x)
#define GET_IC_STATUS(adp) rd_reg(adp->reg_map.IC_STATUS)
#define SET_IC_INTR_MASK(adp, x) wr_reg(adp->reg_map.IC_INTR_MASK, x)
#define GET_IC_INTR_MASK(adp) rd_reg(adp->reg_map.IC_INTR_MASK)
#define GET_IC_INTR_STAT(adp) rd_reg(adp->reg_map.IC_INTR_STAT)
#define GET_IC_RAW_INTR_STAT(adp) rd_reg(adp->reg_map.IC_RAW_INTR_STAT)
#define CLR_IC_INTR(adp) rd_reg(adp->reg_map.IC_CLR_INTR)
#define CLR_IC_RX_UNDER(adp) rd_reg(adp->reg_map.IC_CLR_RX_UNDER)
#define CLR_IC_TX_OVER(adp) rd_reg(adp->reg_map.IC_CLR_TX_OVER)
#define CLR_IC_RD_REQ(adp) rd_reg(adp->reg_map.IC_CLR_RD_REQ)
#define CLR_IC_RX_DONE(adp) rd_reg(adp->reg_map.IC_CLR_RX_DONE)
#define CLR_IC_ACTIVITY(adp) rd_reg(adp->reg_map.IC_CLR_ACTIVITY)
#define CLR_IC_GEN_CALL(adp) rd_reg(adp->reg_map.IC_CLR_GEN_CALL)
#define CLR_IC_TX_ABRT(adp) rd_reg(adp->reg_map.IC_CLR_TX_ABRT)
#define CLR_IC_STOP_DET(adp) rd_reg(adp->reg_map.IC_CLR_STOP_DET)
#define GET_IC_COMP_PARAM_1(adp) rd_reg(adp->reg_map.IC_COMP_PARAM_1)
#define GET_IC_TXFLR(adp) rd_reg(adp->reg_map.IC_TXFLR)
#define GET_IC_RXFLR(adp) rd_reg(adp->reg_map.IC_RXFLR)
#define GET_IC_RX_TL(adp) rd_reg(adp->reg_map.IC_RX_TL)
#define GET_IC_TX_TL(adp) rd_reg(adp->reg_map.IC_TX_TL)
#define GET_IC_SDA_DEL(adp) rd_reg(adp->reg_map.IC_SDA_DEL)
#define SET_IC_RX_TL(adp, x) wr_reg(adp->reg_map.IC_RX_TL, x)
#define SET_IC_TX_TL(adp, x) wr_reg(adp->reg_map.IC_TX_TL, x)
#define SET_IC_SDA_DEL(adp, x) wr_reg(adp->reg_map.IC_SDA_DEL, x)
#define GET_IC_TX_ABRT_SOURCE(adp) rd_reg(adp->reg_map.IC_TX_ABRT_SOURCE)
#define NOT_TXFULL(adp) (GET_IC_STATUS(adp) & ST_TFNF_BIT)
#define NOT_RXEMPTY(adp) (GET_IC_STATUS(adp) & ST_RFNE_BIT)

/* TRUCT DEFINE */
enum SPD_MODE {
	SPD_MODE_LS = 33,
	SPD_MODE_SS = 100,
	SPD_MODE_FS = 400,
	SPD_MODE_HS = 1000
};

enum ADDR_MODE {
	ADDR_MODE_7BITS   = 7,
	ADDR_MODE_10BITS  = 10
};

enum {
	ECMDSPLIT = 40, /* stop detected during transfer*/
	ETXABORT = 41,
	ETIMEOUT = 42,
	EILLEGALMSG = 43, /* illegal message*/
	EADDROVERRANGE = 44, /* invalid Address*/
};

enum {
	NON_STOP = 0, /* stop detected during transfer */
	WAIT_STOP = 1,
};

struct rtk_i2c_xfer {
	unsigned char mode;
	#define I2C_IDLE 0
	#define I2C_MASTER_READ 1
	#define I2C_MASTER_WRITE 2
	#define I2C_MASTER_RANDOM_READ 3

	/* don't issue stop command, (for gpio xfer only) */
	#define I2C_NO_STOP 0x01

	unsigned char flags;
	unsigned char *tx_buff;
	unsigned short tx_buff_len;
	unsigned short tx_len;
	unsigned char *rx_buff;
	unsigned short rx_buff_len;
	unsigned short rx_len;
	unsigned long except_time;
	unsigned long timeout;
	int ret; /* 0 : on going, > 0 : success, < 0 : err */
	unsigned int tx_abort_source; /* for gpio mode */
};

struct rtk_i2c_slave_ops {
	int (*handle_command)(int id, unsigned char *cmd, unsigned char len);
	unsigned char (*read_data)(int id); /* read data form i2c slave */
};

struct rtk_i2c_reg_map {
	unsigned long I2C_ISR_EN;
	unsigned long I2C_ISR_EN_MASK;
	unsigned long I2C_ISR;
	unsigned long I2C_INT;
	unsigned long IC_CON;
	unsigned long IC_TAR;
	unsigned long IC_SAR;
	unsigned long IC_HS_MADDR;
	unsigned long IC_DATA_CMD;
	unsigned long IC_SS_SCL_HCNT;
	unsigned long IC_SS_SCL_LCNT;
	unsigned long IC_FS_SCL_HCNT;
	unsigned long IC_FS_SCL_LCNT;
	unsigned long IC_HS_SCL_HCNT;
	unsigned long IC_HS_SCL_LCNT;
	unsigned long IC_INTR_STAT;
	unsigned long IC_INTR_MASK;
	unsigned long IC_RAW_INTR_STAT;
	unsigned long IC_RX_TL;
	unsigned long IC_TX_TL;
	unsigned long IC_CLR_INTR;
	unsigned long IC_CLR_RX_UNDER;
	unsigned long IC_CLR_RX_OVER;
	unsigned long IC_CLR_TX_OVER;
	unsigned long IC_CLR_RD_REQ;
	unsigned long IC_CLR_TX_ABRT;
	unsigned long IC_CLR_RX_DONE;
	unsigned long IC_CLR_ACTIVITY;
	unsigned long IC_CLR_STOP_DET;
	unsigned long IC_CLR_START_DET;
	unsigned long IC_CLR_GEN_CALL;
	unsigned long IC_ENABLE;
	unsigned long IC_STATUS;
	unsigned long IC_TXFLR;
	unsigned long IC_RXFLR;
	unsigned long IC_SDA_HOLD;
	unsigned long IC_TX_ABRT_SOURCE;
	unsigned long IC_SLV_DATA_NACK_ONLY;
	unsigned long IC_DMA_CR;
	unsigned long IC_DMA_TDLR;
	unsigned long IC_DMA_RDLR;
	unsigned long IC_SDA_SETUP;
	unsigned long IC_ACK_GENERAL_CALL;
	unsigned long IC_ENABLE_STATUS;
	unsigned long IC_COMP_PARAM_1;
	unsigned long IC_COMP_VERSION;
	unsigned long IC_COMP_TYPE;
	unsigned long IC_SDA_DEL;
};

struct rtk_i2c_handler {
#define RTK_I2C_IRQ_RDY 0x01
#define RTK_I2C_SLAVE_ENABLE 0x80
	unsigned int flags;
	atomic_t ref_cnt;
	char *model_name;
	unsigned int irq;
	unsigned char id;
	unsigned int spd;
	unsigned int tick;
	unsigned int guard_interval;
	unsigned short sar;
	unsigned short tar;
	unsigned char rx_fifo_depth;
	unsigned char tx_fifo_depth;
	unsigned long time_stamp;
	unsigned char slave_rx_buffer[64];
	unsigned int slave_rx_len;
	unsigned long slave_id;
	unsigned int tx_abort_flag;
	enum ADDR_MODE tar_mode;
	enum ADDR_MODE sar_mode;
	struct rtk_i2c_reg_map reg_map;
	struct rtk_i2c_xfer xfer;
	struct rtk_i2c_slave_ops slave_ops;
	wait_queue_head_t wq;
	spinlock_t lock;
	int (*init)(struct rtk_i2c_handler *handler);
	int (*uninit)(struct rtk_i2c_handler *handler);
	int (*set_spd)(struct rtk_i2c_handler *handler, int KHz);
	int (*set_guard_interval)(struct rtk_i2c_handler *handler,
		unsigned long us);
	int (*set_tar)(struct rtk_i2c_handler *handler, unsigned short addr,
		enum ADDR_MODE mode);
	int (*read)(struct rtk_i2c_handler *handler, unsigned char *tx_buf,
		unsigned short tx_buf_len, unsigned char *rx_buff,
		unsigned short rx_buf_len);
	int (*write)(struct rtk_i2c_handler *handler, unsigned char *tx_buf,
		unsigned short tx_buf_len, unsigned char wait_stop);
#if 0
	int (*gpio_read)(struct rtk_i2c_handler *handler,
		unsigned char *tx_buf, unsigned short tx_buf_len,
		unsigned char *rx_buff, unsigned short rx_buf_len);
	int (*gpio_write)(struct rtk_i2c_handler *handler,
		unsigned char *tx_buf, unsigned short tx_buf_len,
		unsigned char wait_stop);
#endif
	int (*dump)(struct rtk_i2c_handler *handler); /* for debug*/
#if 0
	int (*suspend)(struct rtk_i2c_handler *handler);
	int (*resume)(struct rtk_i2c_handler *handler);
#endif
	unsigned int (*get_tx_abort_reason)(struct rtk_i2c_handler *handler);
	int (*set_sar)(struct rtk_i2c_handler *handler,
		unsigned short, enum ADDR_MODE mode);
	int (*register_slave_ops)(struct rtk_i2c_handler *handler,
		struct rtk_i2c_slave_ops *ops, unsigned long id);
	int (*slave_mode_enable)(struct rtk_i2c_handler *handler,
		unsigned char on);
#ifdef EDID_4BLOCK_SUPPORT
	int (*read_edid_seg)(struct rtk_i2c_handler *handler,
		unsigned char seg, unsigned char offset,
		unsigned char *rx_buff, unsigned short rx_buf_len);
#endif /* EDID_4BLOCK_SUPPORT */

};

/* FUNCTION PROTOTYPE */
struct rtk_i2c_handler  *create_rtk_i2c_handle(unsigned int id,
	unsigned short sar, enum ADDR_MODE sar_mode, enum SPD_MODE spd,
	unsigned int irq, unsigned long base);

int rtk_i2c_phy_init(struct rtk_i2c_handler *handler);

int rtk_i2c_load_message(struct rtk_i2c_handler *handler, unsigned char mode,
	unsigned char *tx_buf, unsigned short tx_buf_len,
	unsigned char *rx_buf, unsigned short rx_buf_len,
	unsigned char xfer_flags);

int rtk_i2c_start_xfer(struct rtk_i2c_handler *handler);
unsigned int rtk_i2c_get_tx_abort_reason(struct rtk_i2c_handler *handler);
irqreturn_t rtk_i2c_isr(int this_irq, void *dev_id);
