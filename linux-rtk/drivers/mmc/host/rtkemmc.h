/*
 *  Copyright (C) 2010 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RTKEMMC_H
#define __RTKEMMC_H

#include "reg_mmc.h"               
#include "mmc_debug.h"               

#define MAX_DESCRIPTOR_NUM    8
#define EMMC_MAX_SCRIPT_BLK   8   

//debug
//#define MMC_DBG
#ifdef MMC_DBG
#define MMCPRINTF(fmt, args...)   printk(fmt,## args)
#else
#define MMCPRINTF(fmt, args...)
#endif

/* cmd1 sector mode */
#define MMC_SECTOR_ADDR		0x40000000
/*
 * Clock rates
 */
#define RTKSD_CLOCKRATE_MAX	48000000
#define RTKSD_BASE_DIV_MAX	0x100

/*
 * pad driving
 * */
#define MMC_IOS_GET_PAD_DRV	0x1
#define MMC_IOS_SET_PAD_DRV	0x2
#define MMC_IOS_RESTORE_PAD_DRV	0x4
#define CLEAR_CR_CARD_STATUS(reg_addr)           \
	do {                                     \
		writel(0xffffffff, reg_addr);    \
	} while (0)

#define CLEAR_ALL_CR_CARD_STATUS(io_base)        \
do {                                \
	int i = 0;  \
	for(i=0; i<5; i++)  \
	CLEAR_CR_CARD_STATUS(io_base+20+ (i*4));  \
} while (0)

/* MMC configure2, for SD_CONFIGURE2, response type */
#define SD_R0                   (RESP_TYPE_NON|CRC7_CHK_DIS)
#define SD_R1                   (RESP_TYPE_6B)
#define SD_R1b                  (RESP_TYPE_6B|WAIT_BUSY_EN)
#define SD_R2                   (RESP_TYPE_17B)
#define SD_R3                   (RESP_TYPE_6B)
#define SD_R4                   (RESP_TYPE_6B)
#define SD_R5                   (RESP_TYPE_6B)
#define SD_R6                   (RESP_TYPE_6B)
#define SD_R7                   (RESP_TYPE_6B)
#define SD_R_NO                 (0xFF)

/* rtflags */
#define RTKCR_FCARD_DETECTED    (1<<0)      /* Card is detected */
#define RTKCR_FOPEN_LOG         (1<<1)      /* open command log */
#define RTKCR_USER_PARTITION    (1<<2)      /* card is working on normal partition */

#define RTKCR_FCARD_POWER       (1<<4)      /* Card is power on */
#define RTKCR_FHOST_POWER       (1<<5)      /* Host is power on */

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

#define EVENT_NON		    0x00
#define EVENT_INSER		    0x01
#define EVENT_REMOV		    0x02
#define EVENT_USER		    0x10

	u8                  reset_event;
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
#if defined(CONFIG_ARCH_RTD139x)
	volatile void __iomem   *iso_muxpad;
#elif defined(CONFIG_ARCH_RTD16xx)
	volatile void __iomem   *m2tmx;
#endif
	spinlock_t          lock;
	unsigned int        ns_per_clk;
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
#ifdef MONI_MEM_TRASH
	u8                  *cmp_buf;
	dma_addr_t          phy_addr;
#endif
	u32		test_count;
	u32		tmout;
	u32		rintsts; //2044
	u32 		mintsts; //2040
	u32		status;  //2048
	u32		idsts;	 //208c
	u32		dma_isr; //2424
	u32		int_stat;
	u32		idinten; //2090
	u32		intmask; //2024
	u8		rpmb_cmd; // it is rpmb cmd flag. When receiving CMD23, set to 1
	u8		tx_tuning; //flag  that tx tuning need to be performed
	u8		rx_tuning; //flag  that rx tuning need to be performed
	u8		dqs_tuning;
	u8		tx_user_defined;
	u8		rx_user_defined;
	u8		tx_reference_phase;
	u8		rx_reference_phase;
#define INT_STAT_CD		0x00000001	  //cmd done
#define INT_STAT_DTO		0x00000002	  //data trans over
#define INT_STAT_ACD		0x00000004    //r/w multiple blk
#define INT_STAT_DMA_DONE	0x00000008	  //rd dma done
#define INT_STAT_DATA_DONE	0x00000010 	  //wr data done
#define ClrINTState(host)      		    \
	do {                                \
		host->int_stat = 0x00000000;     \
	} while (0)
#define SetINTState(host, val)  	    \
	do {                                \
		host->int_stat |= val;     \
	} while (0)
#define GetINTState(host, val)  	    (host->int_stat & val)

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

struct ms_cmd_pkt {
	struct rtkemmc_host   *emmc_port;
	struct ms_command   *mscmd;
	struct mmc_data     *data;

	unsigned char       *dma_buffer;    //data transfer address
	u16                 cmdcode;        //rtk ms operation code
	u16                 trans_bytes;    //register transfer bytes
	u16                 block_count;    //data block transfer count
};

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

struct backupRegs {
#if defined(CONFIG_ARCH_RTD129x)
	u32			emmc_mux_pad0;
	u32			emmc_mux_pad1;
	u32			emmc_pfunc_nf1;
	u32			emmc_pfunc_cr;
	u32			emmc_pdrive_nf1;
	u32			emmc_pdrive_nf2;
	u32			emmc_pdrive_nf3;
	u32			emmc_pdrive_nf4;
//139x and 16xx does not need to restore the pad mux part, only 129x needs to take this action
/*
#elif defined(CONFIG_ARCH_RTD139x)
	u32                     iso_muxpad4;
	u32			Pfunc_emmc0;
	u32                     Pfunc_emmc1;
	u32                     Pfunc_emmc2;
	u32                     Pfunc_emmc3;
	u32                     Pfunc_emmc4;
	u32                     Pfunc_emmc5;
*/
#endif

#ifdef CONFIG_ARCH_RTD129x	//129x emmc reset will have impact on SD & SDIO
	u32			emmc_pdrive_cr0;
	u32			emmc_pdrive_cr1;
	u32			emmc_pdrive_sdio;
	u32			emmc_pdrive_sdio1;
#endif
	u32			emmc_ctype;
	u32			emmc_uhsreg;
	u32			emmc_ddr_reg;
	u32			emmc_card_thr_ctl;
	u32			emmc_clk_div;
	u32			emmc_ckgen_ctl;
	u32			emmc_dqs_ctrl1;
	u32			emmc_clken;
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	u32			emmc_drto_mask_ori;
	u32			emmc_other1;
#endif
};

/* *** Realtek CRT register &&& */
#define EMMC_CLKSEL_MASK        (0x07<<EMMC_CLKSEL_SHT)
#define SD_CLKSEL_MASK          (0x07<<SD_CLKSEL_SHT)
#define EMMC_CLOCK_SPEED_GAP    (0x03<<EMMC_CLKSEL_SHT)
#define SD_CLOCK_SPEED_GAP      (0x03<<SD_CLKSEL_SHT)


static const char *const clk_tlb_B[8] = {
	"12MHz",
	"16MHz",
	"20MHz",
	"25MHz",
	"33MHz",
	"49MHz"
};

/* Magellan_ISO_arch_spec.doc; PMM_Magellan_PinMux.doc */
// iso gpio pinmux map
static const u8 st_gpio_map[36] ={
	0x34,0x34,0x34,0x34,0x30,0x30,0x30,0x30,    //0:7
	0x2c,0x2c,0x2c,0x2c,0x28,0x28,0xff,0xff,    //8:15
	0xff,0xff,0xff,0xff,0xff,0x28,0x28,0x24,    //16:23
	0xff,0xff,0x24,0x24,0x24,0xff,0xff,0xff,    //24:31
	0xff,0xff,0xff,0x20                         //32:35
};

// iso gpio pinmux bit operation map
static const u8 st_gpio_bit_map[36] ={
	0x04,0x0C,0x14,0x1C,0x04,0x0C,0x14,0x1C,    //0:7
	0x04,0x0C,0x14,0x1C,0x04,0x0C,0xff,0xff,    //8:15
	0xff,0xff,0xff,0xff,0xff,0x14,0x1C,0x04,    //16:23
	0xff,0xff,0x0C,0x14,0x1C,0xff,0xff,0xff,    //24:31
	0xff,0xff,0xff,0x04                         //32:35
};

#define MAX_CMD_RETRY_COUNT 4
#define MAX_ISO_GPIO_CNT 35
#define MAX_MIS_GPIO_CNT 169

static const u8 mis_gpio_bit_map[4] ={
	0x1C,0x14,0x0C,0x04    //0:3
};

#define CARD_SWITCHCLOCK_25MHZ_B    (0x00UL)    //(0x05)
#define CARD_SWITCHCLOCK_33MHZ_B    (0x01UL)    //(0x06)
#define CARD_SWITCHCLOCK_40MHZ_B    (0x02UL)    //(0x00)
#define CARD_SWITCHCLOCK_50MHZ_B    (0x03UL)    //(0x01)
#define CARD_SWITCHCLOCK_66MHZ_B    (0x04UL)    //(0x02)
#define CARD_SWITCHCLOCK_98MH_B     (0x05UL)    //(0x03)
#define CLOCK_SPEED_GAP          CARD_SWITCHCLOCK_50MHZ_B
#define LOW_SPEED_LMT               CARD_SWITCHCLOCK_33MHZ_B

static const u32 map_clk_to_reg[6] = {0x05,0x06,0x00,0x01,0x02,0x03};

static const u32 map_reg_to_clk[8] = {0x02,0x03,0x04,0x05,0xFF,0x00,0x01,0xFF};

#define CARD_SWITCHCLOCK_60MHZ  (0x00UL)      //(0x00<<12)
#define CARD_SWITCHCLOCK_80MHZ  (0x01UL)      //(0x01<<12)
#define CARD_SWITCHCLOCK_98MHZ  (0x02UL)      //(0x02<<12)
#define CARD_SWITCHCLOCK_98MHZS (0x03UL)      //(0x03<<12)
#define CARD_SWITCHCLOCK_30MHZ  (0x04UL)      //(0x04<<12)
#define CARD_SWITCHCLOCK_40MHZ  (0x05UL)      //(0x05<<12)
#define CARD_SWITCHCLOCK_49MHZ  (0x06UL)      //(0x06<<12)
#define CARD_SWITCHCLOCK_49MHZS (0x07UL)      //(0x07<<12)

/* CRT_SYS_CLKSEL setting bit &&& */

/* CRT_SYS_SRST2 setting bit *** */
#define RSTN_CR (0x01<<23)      //for eMMC
/* CRT_SYS_SRST2 setting bit &&& */

/* CRT_SYS_SRST3 setting bit *** */
#define RSTN_SD (0x01<<16)      //for card reader
/* CRT_SYS_SRST3 setting bit &&& */


/* CRT_SYS_CLKEN2 setting bit *** */
#define CLKEN_CR (0x01<<23)      //for eMMC
/* CRT_SYS_CLKEN2 setting bit &&& */

/* CRT_SYS_CLKEN3 setting bit *** */
#define CLKEN_SD (0x01<<16)      //for card reader
/* CRT_SYS_CLKEN3 setting bit &&& */

#define CR_PINMUX_CR_MASK       0xFFFFC000

#define MUX_SD_DAT2             (0x01<<26)
#define MUX_MS_CLK              (0x02<<26)
#define MUX_SD_DAT1             (0x01<<24)
#define MUX_MS_BS               (0x02<<24)
#define MUX_SD_DT               (0x01<<20)
#define MUX_OTP_ATE_FAIL        (0x02<<20)
#define MUX_SD_WP               (0x01<<18)
#define MUX_MS_DT               (0x02<<18)
#define MUX_SD_CLK              (0x01<<16)
#define MUX_MS_DAT0             (0x02<<16)
#define MUX_SD_CMD              (0x01<<14)
#define MUX_MS_DAT2             (0x02<<14)

#define MUX_PAD5_DEFAULT         0x15554000

#define CR_PMUX_CMD_MASK        ~(0x03<<14)  //mask 15,14
#define CR_PMUX_CLK_MASK        ~(0x03<<16)  //mask 16,17
#define CR_PMUX_MOD_MASK        ~(0x0f<<18)  //mask 18,19,20,21
//#define DETECT_MODE             MUX_MS_DT|MUX_SD_DT
#define DETECT_MODE             MUX_SD_DT

#define MUX_PAD5_SD_MODE        0x15554000

#define RCA_SHIFTER             16
#define NORMAL_READ_BUF_SIZE    512      //no matter FPGA & QA

#define SD_CARD_WP              (1<<5)
//#define MS_CARD_EXIST           (1<<3)
#define SD_CARD_EXIST           (1<<2)

/*======================================================== */

/* move from c file *** */
#define BYTE_CNT            0x200
#define RTK_NORMAL_SPEED    0x00
#define RTK_HIGH_SPEED      0x01
#define RTK_1_BITS          0x00
#define RTK_4_BITS          0x10
#define RTK_BITS_MASK       0x30
#define RTK_SPEED_MASK      0x01
#define RTK_PHASE_MASK      0x06

#define R_W_CMD             2   //read/write command
#define INN_CMD             1   //command work chip inside
#define UIN_CMD             0   //no interrupt rtk command

#define RTK_FAIL            3  /* DMA error & cmd parser error */
#define RTK_RMOV            2  /* card removed */
#define RTK_TOUT            1  /* time out include DMA finish & cmd parser finish */
#define RTK_SUCC            0

#define CR_TRANS_OK         0x0
#define CR_TRANSFER_TO      0x1
#define CR_BUF_FULL_TO      0x2
#define CR_DMA_FAIL         0x3
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

#define GPIO_HI             0x78
#define GPIO_LO             0x87

#define LVL_HI             0x01
#define LVL_LO             0x00

#define POW_CHECK 0
#define POW_FORCE 1

#define rtkemmc_get_int_sta(rintsts, mintsts, isr)	\
	do {	\
		*(u32 *)rintsts = readl(emmc_port->emmc_membase+EMMC_RINTSTS);   \
		*(u32 *)mintsts = readl(emmc_port->emmc_membase+EMMC_MINTSTS); \
		*(u32 *)isr = readl(emmc_port->emmc_membase+EMMC_ISR); \
            } while (0)

#define rtkemmc_get_sta(status,idsts)       \
	do {	\
		*(u32 *)status = readl(emmc_port->emmc_membase+EMMC_STATUS);     \
		*(u32 *)idsts  = readl(emmc_port->emmc_membase+EMMC_IDSTS);     \
	} while (0)

#define rtkemmc_get_mask(idinten,intmask)       \
	do {	\
		*(u32 *)idinten = readl(emmc_port->emmc_membase+EMMC_IDINTEN);	   \
		*(u32 *)intmask  = readl(emmc_port->emmc_membase+EMMC_INTMASK); 	\
	} while (0)

#define rtkemmc_clr_int_sta()                                                                              \
	do {                                                                                                \
		writel(ISR_DMA_DONE_INT, emmc_port->emmc_membase+EMMC_ISR); \
		writel(readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0x0000fffe, emmc_port->emmc_membase+EMMC_RINTSTS); \
	} while(0)

//mask all emmc interrupts
#define rtkemmc_hold_int_dec()    \
	do {      \
		writel((ISR_WRITE_DATA|ISR_DMA_INT_MASK|ISR_DESC_INT_MASK|ISR_IP_INT_MASK), emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)&0xffff0000), emmc_port->emmc_membase+EMMC_INTMASK); \
	} while(0)

//unmask all emmc interrupt			
#define rtkemmc_en_int()  \
	do { \
		writel(ISR_DMA_INT_MASK|ISR_DESC_INT_MASK|ISR_IP_INT_MASK, emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)|0x0000fffe), emmc_port->emmc_membase+EMMC_INTMASK); \
	} while(0)

//used for wr case
#define rtkemmc_en_wr_int()  \
	do {  \
		writel(ISR_IP_INT_MASK, emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)|INT_STS_ERRORS|INT_STS_DTO), emmc_port->emmc_membase+EMMC_INTMASK); \
	} while(0)

//used for rd case
#define rtkemmc_en_rd_int()  \
	do { \
		writel(ISR_IP_INT_MASK, emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)|INT_STS_ERRORS|INT_STS_DTO), emmc_port->emmc_membase+EMMC_INTMASK); \
            } while(0)

//used for none-stream case (cmd w/wo/ resp)
#define rtkemmc_en_cd_int()  \
	do {    \
		writel(ISR_IP_INT_MASK, emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)|INT_STS_ERRORS|INT_STS_CD), emmc_port->emmc_membase+EMMC_INTMASK); \
	} while(0)	

//used for cm6 case (cmd w/wo/ resp), ignore Response timeout(INT_STS_RTO_BAR)
#define rtkemmc_en_cd6_int()  \
	do {    \
		writel(ISR_IP_INT_MASK, emmc_port->emmc_membase+EMMC_ISR); \
		writel((readl(emmc_port->emmc_membase+EMMC_INTMASK)|INT_STS_ERRORS2|INT_STS_CD), emmc_port->emmc_membase+EMMC_INTMASK); \
	} while(0)			

#define  rtkemmc_mdelay(x)  \
	set_current_state(TASK_INTERRUPTIBLE); \
	schedule_timeout(msecs_to_jiffies(x))

#define rtkemmc_writel(val, addr) \
	sync(emmc_port);					\
	writel(val, addr);					
		
#define INT_BLOCK_R_GAP 0x200
#define INT_BLOCK_W_GAP 5

static const char *const state_tlb[9] = {
	"STATE_IDLE",
	"STATE_READY",
	"STATE_IDENT",
	"STATE_STBY",
	"STATE_TRAN",
	"STATE_DATA",
	"STATE_RCV",
	"STATE_PRG",
	"STATE_DIS"
};

static const char *const bit_tlb[4] = {
	"1bit",
	"4bits",
	"8bits",
	"unknow"
};

static const char *const clk_tlb[8] = {
	"30MHz",
	"40MHz",
	"49MHz",
	"49MHz",
	"15MHz",
	"20MHz",
	"24MHz",
	"24MHz"
};

static const u32 const clk_2_hz[8] = {
	10000000,
	12000000,
	15000000,
	20000000,
	24000000,
	30000000,
	40000000,
	48000000
};

/* data read cmd */
static const u8 const opcode_r_type[16] = {
    0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0
};

/* data write cmd */
static const u8 const opcode_w_type[16] = {
    1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0
};

/* data xfer cmd */
static const u8 const opcode_d_type[16] = {
    1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0
};

static const char *const cmdcode_tlb[16] = {
	"N_W",      /* 0 */
	"AW3",      /* 1 */
	"AW4",      /* 2 */
	"UNK",      /* 3 */
	"UNK",      /* 4 */
	"AR3",      /* 5 */
	"AR4",      /* 6 */
	"UNK",      /* 7 */
	"SGR",      /* 8 */
	"AW1",      /* 9 */
	"AW2",      /* 10 */
	"UNK",      /* 11 */
	"N_R",      /* 12 */
	"AR1",      /* 13 */
	"AR2",      /* 14 */
	"UNK",      /* 15 */
};

#define card_sta_err_mask ((1<<31)|(1<<30)|(1<<29)|(1<<28)|(1<<27)|(1<<26)|(1<<24)|(1<<23)|(1<<22)|(1<<21)|(1<<20)|(1<<19)|(1<<18)|(1<<17)|(1<<16)|(1<<15)|(1<<13)|(1<<7))

/* Only ADTC type cmd use */
static const unsigned char rtk_sd_cmdcode[64][2] = {
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //0~3
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //4~7
	{EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_AUTOREAD1  ,SD_R1 }, //8~11
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //12~15
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_AUTOREAD2  ,SD_R1 }, {EMMC_AUTOREAD1  ,SD_R1 }, {EMMC_NORMALWRITE,SD_R1 }, //16~19
	{EMMC_AUTOWRITE1 ,SD_R1 }, {EMMC_TUNING     ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //20~23
	{EMMC_AUTOWRITE2 ,SD_R1 }, {EMMC_AUTOWRITE1 ,SD_R1 }, {EMMC_NORMALWRITE,SD_R1 }, {EMMC_NORMALWRITE,SD_R1 }, //24~27
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_NORMALREAD ,SD_R1 }, //28~31
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //32~35
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //36~39
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //40~43
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //44~47
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_NORMALREAD ,SD_R1 }, //48~51
	{EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //52~55
	{EMMC_AUTOREAD2  ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }, //56~59
	{EMMC_AUTOWRITE2 ,SD_R1 }, {EMMC_NORMALREAD ,SD_R1 }, {EMMC_CMD_UNKNOW ,SD_R0 }, {EMMC_CMD_UNKNOW ,SD_R0 }  //60~63 
};

/* remove from c file &&& */

/* rtk function definition */
#define ENABLE_EMMC_INT_MODE
//#define EMMC_LA_DEBUG_GPIO

/* rtk function definition */
int error_handling(struct rtkemmc_host *emmc_port, unsigned int cmd_idx, unsigned int bIgnore);
int rtkemmc_send_cmd25(struct rtkemmc_host *emmc_port,int,unsigned long);
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
