/*
 *  Copyright (C) 2010 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RTKEMMC_H
#define __RTKEMMC_H

#include "reg_mmc_rtd13xx.h"               
#include "mmc_debug.h"               

#define EMMC_MAX_SCRIPT_BLK   128

//debug
//#define MMC_DBG
#ifdef MMC_DBG
#define MMCPRINTF(fmt, args...)   printk(fmt,## args)
#else
#define MMCPRINTF(fmt, args...)
#endif

/* cmd1 sector mode */
#define MMC_SECTOR_ADDR		0x40000000


/* rtflags */
#define RTKCR_FCARD_DETECTED    (1<<0)      /* Card is detected */
#define RTKCR_FOPEN_LOG         (1<<1)      /* open command log */
#define RTKCR_USER_PARTITION    (1<<2)      /* card is working on normal partition */


#define RED_BOLD "\033[31;1m"
#define BLU_BOLD "\033[34;1m"
#define YEL_BOLD "\033[33;1m"
#define GRN_BOLD "\033[32;1m"
#define CYAN_BOLD_ITALIC "\033[36;1;3m"
#define RESET "\033[0;m"

struct rtkemmc_host {
	struct mmc_host     *mmc;           /* MMC structure */
	u32                 rtflags;        /* Driver states */
	u8                  ins_event;
	u8                  cmd_opcode;

	struct mmc_request  *mrq;            /* Current request */
	u8                  wp;
	struct rtk_host_ops *ops;
	struct semaphore	sem;
	struct semaphore	sem_op_end;

	volatile void __iomem	*emmc_membase;
	volatile void __iomem	*crt_membase;
	volatile void __iomem	*sb2_membase;	
	volatile void __iomem	*misc_membase;
	volatile void __iomem   *sb2_debug_membase;
	volatile void __iomem   *mux_mis_membase;
	volatile void __iomem   *iso_blk_membase;
	volatile void __iomem   *m2tmx_membase;
	
	spinlock_t          lock;
	struct delayed_work cmd_work;
	struct tasklet_struct req_end_tasklet;

	struct timer_list   timer;
	struct timer_list   plug_timer;
	struct completion   *int_waiting;
	struct device       *dev;
	struct resource     *res;
	int                 irq;
	u8                  *tmp_buf;
	dma_addr_t          tmp_buf_phy_addr;
	dma_addr_t          dma_paddr;
	dma_addr_t          desc_paddr;
	u32		test_count;
	u32		tmout;
	u16		normal_interrupt; //2030
	u16		error_interrupt;  //2032
	u8		rpmb_cmd; // it is rpmb cmd flag. When receiving CMD23, set to 1
	u8		tx_tuning; //flag  that tx tuning need to be performed
	u8		rx_tuning; //flag  that rx tuning need to be performed
	u8		dqs_tuning;
	u8		tx_user_defined;
	u8		rx_user_defined;
	u8		tx_reference_phase;
	u8		rx_reference_phase;
	u32		dqs_dly_tape;
	unsigned long	emmc_tuning_addr;
#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	struct cmdq_host *cq_host;
#endif
#if defined(CONFIG_MMC_RTK_EMMC_PON)
	unsigned long pon_addr;
	u32 emmc_pon_gpio;
#endif
};

struct rtk_host_ops {
	irqreturn_t (*func_irq)(int irq, void *dev);
	int (*re_init_proc)(struct mmc_card *card);
	int (*card_det)(struct rtkemmc_host *emmc_port);
	void (*card_power)(struct rtkemmc_host *emmc_port,u8 status);
	void (*chk_card_insert)(struct rtkemmc_host *rtkhost);
	void (*set_crt_muxpad)(struct rtkemmc_host *rtkhost);
	void (*set_clk)(struct rtkemmc_host *rtkhost,u32 mmc_clk);
	void (*reset_card)(struct rtkemmc_host *rtkhost);
	void (*reset_host)(struct rtkemmc_host *rtkhost);
	void (*bus_speed_down)(struct rtkemmc_host *emmc_port);
	u32 (*get_cmdcode)(u32 opcode );
	u32 (*get_r1_type)(u32 opcode );
	u32 (*chk_cmdcode)(struct mmc_command* cmd);
	u32 (*chk_r1_type)(struct mmc_command* cmd);
	void (*backup_regs)(struct rtkemmc_host *emmc_port);
	void (*restore_regs)(struct rtkemmc_host *emmc_port);
};

#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
struct cmdq_host {
	const struct cmdq_host_ops *ops;
	struct mmc_host *mmc;

	/* 64 bit DMA */
	bool dma64;

	int num_slots;
	int start_slot;
	u32 dcmd_slot;

	//u32 caps;
#define CMDQ_TASK_DESC_SZ_128 0x1

	//u32 quirks;
#define CMDQ_QUIRK_SHORT_TXFR_DESC_SZ 0x1
#define CMDQ_QUIRK_NO_DCMD      0x2

	bool enabled;
	bool halted;
	bool init_done;

	u32 *desc_base;

	/* total descriptor size */
	u8 slot_sz;


	/* 64/128 bit depends on CQCFG */
	u8 task_desc_len;

	/* 64 bit on 32-bit arch, 128 bit on 64-bit */
	u8 link_desc_len;

	u32 *trans_desc_base;
	/* same length as transfer descriptor */
	u8 trans_desc_len;

	dma_addr_t desc_dma_base;
	dma_addr_t trans_desc_dma_base;

	struct completion halt_comp;
	struct mmc_request **mrq_slot;
	void *private;
};
#endif

struct sd_cmd_pkt {
	struct mmc_host     *mmc;       /* MMC structure */
	struct rtkemmc_host   *emmc_port;
	struct mmc_command  *cmd;    /* cmd->opcode; cmd->arg; cmd->resp; cmd->data */
	struct mmc_data     *data;
	unsigned char       *dma_buffer;
	u16                 byte_count;
	u16                 block_count;

	u32                 flags;
	u32			cmd_para;
	u8                  rsp_len;
	u32                 timeout;
};

#define MAX_CMD_RETRY_COUNT 4

#define RCA_SHIFTER             16

/* move from c file *** */
#define BYTE_CNT            0x200

#define RTK_FAIL            0x3  /* DMA error & cmd parser error */
#define RTK_RMOV            0x2  /* card removed */
#define RTK_TOUT            0x1  /* time out include DMA finish & cmd parser finish */
#define RTK_SUCC            0x0
#define CR_TRANSFER_FAIL    0x4

/* send status event */
#define STATE_IDLE          0
#define STATE_READY         1
#define STATE_IDENT         2
#define STATE_STBY          3
#define STATE_TRAN          4
#define STATE_DATA          5
#define STATE_RCV           6
#define STATE_PRG           7
#define STATE_DIS           8

#define rtkemmc_get_int_sta(normal_interrupt, error_interrupt)	\
	do {	\
		*(u16 *)normal_interrupt = readw(emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_R);   \
		*(u16 *)error_interrupt = readw(emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_R);   \
            } while (0)

//clear status register, we always keep the card interrupt, card insertion, removal status because the eMMC is unremovable
#define rtkemmc_clr_int_sta()                                                                              \
	do {                                                                                                \
		rtkemmc_writew(readw(emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_R)&0xffff, emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_R); \
		rtkemmc_writew(readw(emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_R)&0xfeff, emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_R); \
	} while(0)

//mask all emmc interrupts
#define rtkemmc_hold_int_dec()    \
	do {      \
                writew(0x0,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R); \
                writew(0x0,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R); \
	} while(0)

//for cmdq, we do not need cmd and xfer done, only cqe event
#define rtkemmc_en_cqe_int()  \
	do { \
		writew(0xfefc,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R); \
		writew(EMMC_ALL_ERR_SIGNAL_EN,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R); \
	} while(0)

//used for data, r1b case, we mask cmd done interrupt
#define rtkemmc_en_xfer_int()  \
	do {  \
                writew(0xfefe,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R); \
                writew(EMMC_ALL_ERR_SIGNAL_EN,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R); \
	} while(0)

//used for none-stream case (cmd w/wo/ resp)
#define rtkemmc_en_cd_int()  \
	do {    \
                writew(0xfefd,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R); \
                writew(EMMC_ALL_ERR_SIGNAL_EN,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R); \
	} while(0)	

#define rtkemmc_writel(val, addr) \
	do {    \
		sync(emmc_port);					\
		writel(val, addr);					\
	} while(0)

#define rtkemmc_writew(val, addr) \
	do {    \
		sync(emmc_port);                                        \
		writew(val, addr);					\
	} while(0)

#define rtkemmc_writeb(val, addr) \
	do {    \
		sync(emmc_port);                                        \
		writeb(val, addr);					\
	} while(0)

static const char *const state_tlb[11] = {
	"STATE_IDLE",
	"STATE_READY",
	"STATE_IDENT",
	"STATE_STBY",
	"STATE_TRAN",
	"STATE_DATA",
	"STATE_RCV",
	"STATE_PRG",
	"STATE_DIS",
	"STATE_BTST",
	"STATE_SLEEP"
};

/* Only ADTC type cmd use */
static const unsigned char rtk_sd_cmdcode[64] = {
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //0~3
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_NORMALREAD, EMMC_CMD_UNKNOW, //4~7
	EMMC_NORMALREAD, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_AUTOREAD1 , //8~11
	EMMC_CMD_UNKNOW, EMMC_NORMALREAD, EMMC_NORMALREAD, EMMC_CMD_UNKNOW, //12~15
	EMMC_CMD_UNKNOW, EMMC_AUTOREAD2 , EMMC_AUTOREAD1 , EMMC_NORMALWRITE , //16~19
	EMMC_AUTOWRITE1, EMMC_TUNING    , EMMC_NORMALREAD, EMMC_CMD_UNKNOW , //20~23
	EMMC_AUTOWRITE2, EMMC_AUTOWRITE1, EMMC_NORMALWRITE, EMMC_NORMALWRITE, //24~27
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_NORMALREAD, EMMC_NORMALREAD , //28~31
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //32~35
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //36~39
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_NORMALREAD, EMMC_CMD_UNKNOW, //40~43
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //44~47
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_NORMALREAD, //48~51
	EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //52~55
	EMMC_AUTOREAD2, EMMC_CMD_UNKNOW , EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW, //56~59
	EMMC_AUTOWRITE2, EMMC_NORMALREAD, EMMC_CMD_UNKNOW, EMMC_CMD_UNKNOW   //60~63 
};

/* remove from c file &&& */

/* rtk function definition */

/* rtk function definition */
void error_handling(struct rtkemmc_host *emmc_port);
int rtkemmc_send_cmd25(struct rtkemmc_host *emmc_port,int,unsigned long, int,int*);
int rtkemmc_send_cmd18(struct rtkemmc_host *emmc_port,int,unsigned long);
int rtkemmc_send_cmd24(struct rtkemmc_host *emmc_port);
int rtkemmc_send_cmd17(struct rtkemmc_host *emmc_port);


//int rtkemmc_send_cmd8(struct rtkemmc_host *emmc_port,unsigned int bIgnore);
int rtkemmc_send_cmd8(struct rtkemmc_host *emmc_port, unsigned int bIgnore);
int polling_to_tran_state(struct rtkemmc_host *emmc_port,int cmd_idx, int bIgnore);
void host_card_stop(struct rtkemmc_host *emmc_port);
void host_card_stop2(struct rtkemmc_host *emmc_port);
int rtkemmc_switch(struct mmc_card *card, u8 acc_mod, u8 index, u8 value, u8 cmd_set);
#endif
