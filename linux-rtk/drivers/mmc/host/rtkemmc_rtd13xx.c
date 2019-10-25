/*
 * Realtek EMMC driver
 *
 * Authors:
 * Copyright (C) 2017 Realtek Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/mbus.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/mmc/host.h>
#include <asm/unaligned.h>

#include <linux/suspend.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>
#include <linux/workqueue.h>
#include <linux/completion.h>
#include "reg_iso.h"
#include "reg_sys.h"
#include "rtkemmc_rtd13xx.h"
#include "mmc_debug.h"
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <asm/cacheflush.h>
#include <linux/pm_runtime.h>

#include <linux/clk.h>
#include <linux/reset.h>

#ifdef CONFIG_REALTEK_PCBMGR
#include <mach/pcbMgr.h>
#ifdef CONFIG_REALTEK_GPIO
#include <mach/venus_gpio.h>
#define EMMC_SHOUTDOWN_PROTECT
#endif
#endif

#define DRIVER_NAME "EMMC"
#define BANNER      "Realtek eMMC Driver"
#define VERSION     "$Id: rtkemmc.c Hank 2019-1-7 19:00 $"

#define DMA_ALLOC_LENGTH     (0x80000)
#define DESC_ALLOC_LENGTH   (1024*1024)
unsigned int GLOBAL=0;
#define PHASE_INHERITED

#define FORCE_CHECK_CMD_AND_STS

#ifdef PHASE_INHERITED
static u32 VP0_saved = 0xFF, VP1_saved =0xFF;
#endif

#define DQS_INHERITED
#ifdef DQS_INHERITED
static u32 dqs_saved = 0xff;
#endif

#ifdef RTK_EMMC_HEALTH_REPORT
        int health_report_fd;
#endif

#define TIMEOUT_MS 3000
#define TIMEOUT_DMA 50
#define TIMEOUT_CMD 10000 //10 secs

#ifdef MMC_DBG
static unsigned sd_reg = 0;
#endif

//#define RTKEMMC_DEBUG

struct mmc_host * mmc_host_local = NULL;
static u32 rtk_emmc_bus_wid = 0;
static volatile int g_bResuming;
volatile int g_bTuning;
//static int bSendCmd0=0;
volatile unsigned int gCurrentBootMode=MODE_SDR;
volatile unsigned int gPreventRetry=0;
static volatile unsigned int  g_crinit=0;
static struct rw_semaphore cr_rw_sem;
//ip descriptor on ddr
unsigned int* gddr_descriptor=NULL;
static unsigned int* gddr_descriptor_org=NULL;

//internal emmc dma buffer on ddr
static unsigned char* gddr_dma=NULL;
static unsigned char* gddr_dma_org=NULL;

u32 rtkemmc_global_blksize;
u32 rtkemmc_global_bytecnt;
u32 rtkemmc_global_dbaddr;
int cmd_resend=0;
static u32 pddrive_nf_s0[5] = {0};
static u32 pddrive_nf_s1[5] = {0};
static u32 pddrive_nf_s2[5] = {0};
static u32 pddrive_nf_s3[5] = {0};

//#ifndef CONFIG_ARCH_RTD16xx
//#define SHA256
//#endif

#ifdef SHA256
int MCP_SHA256(unsigned char *p_in, unsigned char *p_out, unsigned long len, unsigned int iv[8]);
unsigned char *compare3=NULL;
unsigned char *compare4=NULL;
dma_addr_t          compare3_phy_addr;
dma_addr_t          compare4_phy_addr;
#else
unsigned char compare1[DMA_ALLOC_LENGTH];
unsigned char compare2[DMA_ALLOC_LENGTH];
#endif

struct reset_control *rstc_emmc;
struct clk * clk_en_emmc;
struct clk * clk_en_emmc_ip;

int rtkemmc_hs200_tuning(struct mmc_card *card);
int mmc_hs400_to_hs200(struct mmc_card *card);
int mmc_select_hs200(struct mmc_card *card);
int mmc_select_ddr50(struct mmc_card *card);
int rtkemmc_switch(struct mmc_card *card, u8 acc_mod, u8 index, u8 value, u8 cmd_set);
#ifdef RTKEMMC_DEBUG
static void rtkemmc_dump_registers(struct rtkemmc_host *emmc_port);
#endif
static void rtkemmc_request(struct mmc_host *host, struct mmc_request *mrq);
static int rtkemmc_get_ro(struct mmc_host *mmc);
static void rtkemmc_set_ios(struct mmc_host *host, struct mmc_ios *ios);

static void set_cmd_info(struct mmc_card *card,struct mmc_command * cmd,
struct sd_cmd_pkt * cmd_info,u32 opcode,u32 arg,u8 rsp_para);

static int rtkemmc_stop_transmission(struct mmc_card *card,int bIgnore);
static int rtkemmc_send_status(struct mmc_card *card, u32 *status, u8 * state,u8 divider,int bIgnore);
static int rtkemmc_wait_status(struct mmc_card *card,u8 state,u8 divider,int bIgnore);
int rtkemmc_send_cmd6(struct rtkemmc_host *emmc_port, u32 args,u16 * state);
static int rtkemmc_send_cmd13(struct rtkemmc_host *emmc_port, u16 * state);

static int mmc_Tuning_SDR50(struct rtkemmc_host *emmc_port);
static int mmc_Tuning_DDR50(struct rtkemmc_host *emmc_port,u32 mode);
static int mmc_Tuning_HS200(struct rtkemmc_host *emmc_port,u32 mode);
void set_RTK_initial_flag(int flag);
static int rtkemmc_execute_tuning(struct mmc_host *host, u32 opcode);
static int rtkemmc_prepare_hs400_tuning(struct mmc_host *host, struct mmc_ios *ios);
void phase(struct rtkemmc_host *emmc_port, u32 VP0, u32 VP1);
static void rtkemmc_chk_card_insert(struct rtkemmc_host *emmc_port);
static void rtkemmc_set_pin_mux(struct rtkemmc_host *emmc_port);
static u32 rtkemmc_chk_cmdcode(struct mmc_command* cmd);
static void rtkemmc_set_freq(struct rtkemmc_host *emmc_port, u32 freq, u32 div_ip);
void error_handling(struct rtkemmc_host *emmc_port);
static int SD_SendCMDGetRSP(struct sd_cmd_pkt * cmd_info,int bIgnore);
static int SD_SendCMDGetRSP_Cmd(struct sd_cmd_pkt *cmd_info,int bIgnore);
void rtkemmc_set_pad_driving(struct rtkemmc_host *emmc_port, u32 clk_drv, u32 cmd_drv, u32 data_drv, u32 ds_drv);
static int wait_done_timeout(struct rtkemmc_host *emmc_port, volatile u32 *addr, u32 mask, u32 value,const char *string);
static int SD_Stream_Cmd(u16 cmdcode,struct sd_cmd_pkt *cmd_info, unsigned int bIgnore);
static void rtkemmc_dqs_tuning(struct mmc_host *host);
int rtkemmc_select_timing(struct mmc_card *card);
void rtkemmc_select_card_type(struct mmc_card *card);
void down_speed_handling(struct rtkemmc_host *emmc_port);
u32 rtkemmc_swap_endian(u32 input);
DECLARE_COMPLETION(rtk_emmc_wait);
typedef void (*set_gpio_func_t)(u32 gpio_num,u8 dir,u8 level);


int suspend = 0;
int suspend_VP0=0xff, suspend_VP1=0xff;
int HS200_RX=0xff, HS200_TX=0xff;
int suspend_dqs=0x88;
bool hs400_to_hs200_flag=false;

static const struct mmc_host_ops rtkemmc_ops = {
	.request        = rtkemmc_request,
	.get_ro         = rtkemmc_get_ro,
	.set_ios        = rtkemmc_set_ios,
	.execute_tuning = rtkemmc_execute_tuning,
	.prepare_hs400_tuning = rtkemmc_prepare_hs400_tuning,
	.dqs_tuning = rtkemmc_dqs_tuning
};

static struct rtk_host_ops emmc_ops = {
	.func_irq       = NULL,
	.re_init_proc   = NULL,
	.card_det       = NULL,
	.card_power     = NULL,
        .chk_card_insert= rtkemmc_chk_card_insert,
        .set_crt_muxpad = rtkemmc_set_pin_mux,
        .set_clk        = NULL,
	.reset_card     = NULL,
	.reset_host     = NULL,
	.bus_speed_down = NULL,
	.get_cmdcode    = NULL,
	.get_r1_type    = NULL,
	.chk_cmdcode    = rtkemmc_chk_cmdcode,
	.chk_r1_type    = NULL,
	.backup_regs    = NULL,
	.restore_regs   = NULL,
};

void sync(struct rtkemmc_host *emmc_port)
{
	dmb(sy);
	writel(0x0, emmc_port->sb2_membase+0x20);
	dmb(sy);
}

//---------------------------------------------------------------------------------------------------------------------------
#ifdef CONFIG_RTK_ACPU_RELOAD
//this part is set for avcpu.c usage

static int rtkemmc_switch_user_partition(struct mmc_card *card)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	int err = 0;

	MMCPRINTF("\n");

	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	set_cmd_info(card,&cmd,&cmd_info, MMC_SWITCH, 0x03b30001, 6);

	err = SD_SendCMDGetRSP_Cmd(&cmd_info,0);

	if(err){
		mmcmsg3(KERN_WARNING "%s: MMC_SWITCH fail\n",DRIVER_NAME);
	}
	return err;
}
/* ========================================================
 * blk_addr    : eMMC read/write target address, block base.
 * data_size   : tarnsfer data size, block base.
 * buffer      : DMA address
 * rw_mode     : fast read or ast write
 ========================================================== */
#define FAST_READ   0x1278
#define FAST_WRITE  0x3478
static int mmc_fast_rw( unsigned int blk_addr, unsigned int data_size, unsigned char * buffer, unsigned int rw_mode )
{
	int err = 0;
	struct mmc_host * mmc = mmc_host_local;
	unsigned long flags;

	if(mmc){
		struct rtkemmc_host *emmc_port;
		struct mmc_card *card;
		struct mmc_request mrq = {0};
		struct mmc_command cmd = {0};
		struct mmc_data     data   = {0};
		struct scatterlist sg;

		emmc_port = mmc_priv(mmc);
		mmc_claim_host(mmc);
		spin_lock_irqsave(&emmc_port->lock,flags);

		card = mmc->card;
		if((emmc_port->rtflags & RTKCR_USER_PARTITION)==0){
			int try_loop = 3;
			do{
				err = 0;
				spin_unlock_irqrestore(&emmc_port->lock, flags);
				err = rtkemmc_switch_user_partition(card);
				spin_lock_irqsave(&emmc_port->lock,flags);

			}while(try_loop-- && err );

			if(err){
				spin_unlock_irqrestore(&emmc_port->lock, flags);
				mmc_release_host(mmc);
				goto ERR_OUT;
			}
			else
				emmc_port->rtflags |= RTKCR_USER_PARTITION;
		}

		if(data_size>1){
			if(rw_mode == FAST_WRITE)
				cmd.opcode = MMC_WRITE_MULTIPLE_BLOCK;
			else
				cmd.opcode = MMC_READ_MULTIPLE_BLOCK;
		}else{
			if(rw_mode == FAST_WRITE)
				cmd.opcode = MMC_WRITE_BLOCK;
			else
				cmd.opcode = MMC_READ_SINGLE_BLOCK;
		}

		cmd.arg = blk_addr;
		cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;

		if(data_size) {   //date info setting
			data.sg = &sg;
			data.sg_len = 1;
			data.blksz = 512;
			data.blocks = data_size;

			sg_init_one(data.sg, buffer, (data_size<<9));

			if(rw_mode == FAST_WRITE)
				data.flags = MMC_DATA_WRITE;
			else
				data.flags = MMC_DATA_READ;

			mmc_set_data_timeout(&data, card);
		}

		data.mrq = &mrq;
		cmd.mrq = &mrq;
		cmd.data = &data;
		cmd.retries =5;
CMD_RETRY:
		mrq.data = &data;
		mrq.cmd = &cmd;

		if(emmc_port->mrq){
			emmc_port->mrq = NULL;
		}

		cmd.error = 0;
		data.error = 0;
		spin_unlock_irqrestore(&emmc_port->lock, flags);
		mmc_wait_for_req(mmc, &mrq);
		spin_lock_irqsave(&emmc_port->lock,flags);
		err = cmd.error;
		if((err==0) && (rw_mode==FAST_WRITE))
		{
			spin_unlock_irqrestore(&emmc_port->lock, flags);
			err = rtkemmc_wait_status(mmc->card,STATE_TRAN,0,0);
			spin_lock_irqsave(&emmc_port->lock,flags);
		}
		if(err && cmd.retries){
			printk("%s(%u)last retry %d counter.\n", __func__,__LINE__,cmd.retries);
			cmd.retries--;
			goto CMD_RETRY;
		}
		spin_unlock_irqrestore(&emmc_port->lock, flags);
		mmc_release_host(mmc);
	}else{
		err = -ENODEV;
	}
ERR_OUT:
	if(err)
		printk("err=%d\n",err);

	return err;
}

#define MAX_XFER_BLK_A    0x100
#define MAX_XFER_BLK_B    0x400
static int mmc_fast_rw_loop(unsigned int blk_addr, unsigned int data_size, unsigned char * buffer, unsigned int rw_mode )
{
	int err = 0;

	unsigned int tmp_addr   = blk_addr;
	unsigned int tmp_size   = data_size;
	unsigned int org_size   = data_size;
	unsigned char * tmp_buf = buffer;
	unsigned int max_xfer_blk;
	do{
		// max 1M bytes read/write per transfer

		max_xfer_blk = MAX_XFER_BLK_B;

		if(data_size > max_xfer_blk){
			tmp_size = max_xfer_blk;
		}else{
			tmp_size = data_size;
		}

		err = mmc_fast_rw(tmp_addr,tmp_size,tmp_buf,rw_mode);

		if(err)
			break;

		if(data_size > max_xfer_blk){
			tmp_addr    += max_xfer_blk;
			data_size   -= max_xfer_blk;
			tmp_buf     += (max_xfer_blk<<9);
		}else{
			data_size = 0;
		}
	}while(data_size);

	if(err == 0)
		return org_size-data_size;
	else
		return err;
}

int mmc_fast_read(unsigned int blk_addr, unsigned int data_size, unsigned char * buffer )
{
	int err = 0;
	err = mmc_fast_rw_loop(blk_addr,data_size,buffer,FAST_READ);
	return err;
}
EXPORT_SYMBOL(mmc_fast_read);

int mmc_fast_write(unsigned int blk_addr, unsigned int data_size, unsigned char * buffer )
{
	int err = 0;
	if(blk_addr<0x20000){
		printk("target small then save area.\n");
		err = -1;
	}
	err = mmc_fast_rw_loop(blk_addr,data_size,buffer,FAST_WRITE);
	return err;
}
EXPORT_SYMBOL(mmc_fast_write);
#endif
//------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------command queue related function---------- -------------------------------------------
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ

int mmc_cmdq_halt(struct mmc_host *host, bool halt);
static int rtkemmc_cmdq_enable(struct mmc_host *mmc);
static int rtkemmc_cmdq_request(struct mmc_host *mmc, struct mmc_request *mrq);
static int rtkemmc_cmdq_alloc_tdl(struct cmdq_host *cq_host);
static void rtkemmc_cmdq_post_req(struct mmc_host *host, struct mmc_request *mrq, int err);
static void rtkemmc_cmdq_disable(struct mmc_host *mmc, bool soft);
static int rtkemmc_cmdq_halt(struct mmc_host *mmc, bool halt);
static void rtkemmc_cmdq_getrsp(struct mmc_host *host, struct mmc_request *mrq);

/*user should maintain a software table for cmdq to make sure the previous command task is complete.
  Slot 0~30 is for rw task, and this tag is assigned in block layer and they have already dealt with this issue,
  Therefore, eMMC driver does not need to protect slot 0~30. It only needs to protect slot 31 dcmd*/
volatile bool DCMD_complete=true;
volatile bool DCMD_wait_38=false;
volatile int DCMD_idx=0;

static const struct mmc_cmdq_host_ops cmdq_host_ops = {
	.enable = rtkemmc_cmdq_enable,
	.disable = rtkemmc_cmdq_disable,
	.request = rtkemmc_cmdq_request,
	.post_req = rtkemmc_cmdq_post_req,
	.halt = rtkemmc_cmdq_halt,
	.getrsp = rtkemmc_cmdq_getrsp,
};

#define DRV_NAME "rtkemmc-cmdq-host"

static void rtkemmc_cmdq_dumpregs(struct rtkemmc_host *emmc_port)
{
	struct mmc_host *mmc = emmc_port->mmc;

	pr_err(DRV_NAME ": ========== REGISTER DUMP (%s)==========\n",
		mmc_hostname(mmc));

	pr_err(DRV_NAME ": Queing config: 0x%08x | Queue Ctrl:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQCFG),
		readl(emmc_port->emmc_membase + EMMC_CQCTL));
	pr_err(DRV_NAME ": Int stat: 0x%08x      | Int enab:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQIS),
		readl(emmc_port->emmc_membase + EMMC_CQIS_STAT_EN));
	pr_err(DRV_NAME ": Int sig: 0x%08x       | Int Coal:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQIS_SIGNAL_EN),
		readl(emmc_port->emmc_membase + EMMC_CQIC));
	pr_err(DRV_NAME ": TDL base: 0x%08x\n", readl(emmc_port->emmc_membase + EMMC_CQTDLBA));
	pr_err(DRV_NAME ": Doorbell: 0x%08x      | Comp Notif:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQTDBR),
		readl(emmc_port->emmc_membase + EMMC_CQTCN));
	pr_err(DRV_NAME ": Dev queue: 0x%08x     | Dev Pend:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQDQS),
		readl(emmc_port->emmc_membase + EMMC_CQDPT));
	pr_err(DRV_NAME ": Task clr: 0x%08x      | Send stat 1:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQTCLR),
		readl(emmc_port->emmc_membase + EMMC_CQSSC1));
	pr_err(DRV_NAME ": Send stat 2: 0x%08x   | DCMD resp:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQSSC2),
		readl(emmc_port->emmc_membase + EMMC_CQCRDCT));
	pr_err(DRV_NAME ": Resp err mask: 0x%08x | Task err:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQRMEM),
		readl(emmc_port->emmc_membase + EMMC_CQTERRI));
	pr_err(DRV_NAME ": Resp idx 0x%08x       | Resp arg:  0x%08x\n",
		readl(emmc_port->emmc_membase + EMMC_CQCRI),
		readl(emmc_port->emmc_membase + EMMC_CQCRA));
	pr_err(DRV_NAME ": ===========================================\n");
}

static void rtkemmc_cmdq_getrsp(struct mmc_host *host, struct mmc_request *mrq)
{
	struct rtkemmc_host *emmc_port = mmc_priv(host);
	mrq->cmd->resp[0] = readl(emmc_port->emmc_membase+EMMC_CQCRDCT);
	//printk(KERN_ERR "%s: mrq->cmd->resp[0]=0x%x\n", __func__, mrq->cmd->resp[0]);
}

static void rtkemmc_cmdq_post_req(struct mmc_host *host, struct mmc_request *mrq, int err)
{
	struct mmc_data *data = mrq->data;

	if (data) {
		data->error = err;
		dma_unmap_sg(mmc_dev(host), data->sg, data->sg_len,
			     (data->flags & MMC_DATA_READ) ?
			     DMA_FROM_DEVICE : DMA_TO_DEVICE);
		if (err)
			data->bytes_xfered = 0;
		else
			data->bytes_xfered = blk_rq_bytes(mrq->req);
	}
}

int rtkemmc_cmdq_init(struct cmdq_host *cq_host, struct mmc_host *mmc, bool dma64)
{
	int err = 0;

	cq_host = kzalloc(sizeof(*cq_host), GFP_KERNEL);
	if (!cq_host) {
		printk(KERN_ERR "Allocate cq_host memory failed!!!\n");
		return -ENOMEM;
	}

	cq_host->dma64 = dma64;
	cq_host->mmc = mmc;
	cq_host->mmc->cmdq_private = cq_host;

#ifdef CONFIG_MMC_RTK_EMMC_PON
	cq_host->start_slot = 1;	//slot 0 is reserved for pon usage
#else
	cq_host->start_slot = 0;
#endif
	cq_host->num_slots = NUM_SLOTS;
	cq_host->dcmd_slot = DCMD_SLOT;

	mmc->cmdq_ops = &cmdq_host_ops;

	cq_host->mrq_slot = kzalloc(sizeof(cq_host->mrq_slot) *
					cq_host->num_slots, GFP_KERNEL);
	if (!cq_host->mrq_slot)
		return -ENOMEM;

	init_completion(&cq_host->halt_comp);
	return err;
}

static int rtkemmc_cmdq_halt(struct mmc_host *mmc, bool halt)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	struct rtkemmc_host *emmc_port = mmc_priv(mmc);
	u32 val = 0;

	if (halt) {
		rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_CQCTL) | EMMC_CQ_HALT, emmc_port->emmc_membase+EMMC_CQCTL);
		val = wait_for_completion_timeout(&cq_host->halt_comp, msecs_to_jiffies(HALT_TIMEOUT_MS));
		/* halt done: re-enable legacy interrupts */
		rtkemmc_writel(~EMMC_CQ_ALL_STAT_EN, emmc_port->emmc_membase+EMMC_CQIS_STAT_EN); //disable all cqe status interrupt bit
		rtkemmc_writel(~EMMC_CQ_ALL_SIGNAL_EN, emmc_port->emmc_membase+EMMC_CQIS_SIGNAL_EN);        //disable all cqe signal interrupt bit

		val = val ? 0 : -ETIMEDOUT;
	} else {
		rtkemmc_writel(EMMC_CQ_ALL_STAT_EN, emmc_port->emmc_membase+EMMC_CQIS_STAT_EN); //enable all cqe status interrupt bit
		rtkemmc_writel(EMMC_CQ_ALL_SIGNAL_EN, emmc_port->emmc_membase+EMMC_CQIS_SIGNAL_EN);        //enable all cqe signal interrupt bit
		rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_CQCTL) & (~EMMC_CQ_HALT), emmc_port->emmc_membase+EMMC_CQCTL);
	}

	return val;
}

static int rtkemmc_cmdq_enable(struct mmc_host *mmc)
{
	int err = 0;
	u32 cqcfg;
	struct cmdq_host *cq_host = mmc_cmdq_private(mmc);
	struct rtkemmc_host *emmc_port = mmc_priv(mmc);

	if (!cq_host || !mmc->card || !mmc_card_cmdq(mmc->card)) {
		printk(KERN_ERR "cq_host or mmc->card is null!!!\n");
		err = -EINVAL;
		goto out;
	}

	if (cq_host->enabled) {
		printk(KERN_ERR "cq_host->enabled flag 1, cqe has been already enabled!!!\n");
		goto out;
	}

	cqcfg = readl(emmc_port->emmc_membase+EMMC_CQCFG);
	if (cqcfg & EMMC_CQ_EN) {
		printk(KERN_ERR "%s: %s: cq_host is already enabled\n", mmc_hostname(mmc), __func__);
		WARN_ON(1);
		goto out;
	}

	if (!cq_host->desc_base || !cq_host->trans_desc_base) {
		//create the descriptor table, EMMC_CQTDLBA register will be filled out the descriptor address
		err = rtkemmc_cmdq_alloc_tdl(cq_host);
		if (err)
			goto out;
	}

	rtkemmc_writeb(EMMC_SW_RST_DAT, emmc_port->emmc_membase+EMMC_SW_RST_R);		//clear data path SW_RST_R.SW_RST_DAT = 1
	rtkemmc_writel(cq_host->desc_dma_base, emmc_port->emmc_membase+EMMC_CQTDLBA);		//0x980121a0, Set Task Descriptor List Base Address Register (CQTDLBA)
	rtkemmc_writew(0x200, emmc_port->emmc_membase+EMMC_BLOCKSIZE_R); //0x98012004,Set value corresponding to executed data byte length of one block to BLOCKSIZE_R
	rtkemmc_writew(((1<<EMMC_MULTI_BLK_SEL)|EMMC_BLOCK_COUNT_ENABLE|EMMC_DMA_ENABLE),emmc_port->emmc_membase+EMMC_XFER_MODE_R);	//0x9801200c
	rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xe7)|(EMMC_ADMA2_32<<EMMC_DMA_SEL),
			emmc_port->emmc_membase+EMMC_HOST_CTRL1_R);		//Set DMA_SEL to ADMA2 only mode in the HOST_CTRL1_R
	rtkemmc_writew(0, emmc_port->emmc_membase+EMMC_BLOCKCOUNT_R);
	rtkemmc_writel(0, emmc_port->emmc_membase+EMMC_SDMASA_R);	//Set SDMASA_R (while using 32 bits) to 0
	//Set CQIC register to enable interrupt coalescing and to configure its timeout and threshold parameters INTC_TOUT, INTC_TH, disable by default
	rtkemmc_writel(0, emmc_port->emmc_membase+EMMC_CQIC);
	rtkemmc_writel(0, emmc_port->emmc_membase+EMMC_CQIS);	//Set CQIS status interrupt register to 0
	rtkemmc_writel(EMMC_CQ_ALL_STAT_EN, emmc_port->emmc_membase+EMMC_CQIS_STAT_EN);	//enable all cqe status interrupt bit
	rtkemmc_writel(EMMC_CQ_ALL_SIGNAL_EN, emmc_port->emmc_membase+EMMC_CQIS_SIGNAL_EN);        //enable all cqe signal interrupt bit
	rtkemmc_writel(0x1000, emmc_port->emmc_membase+EMMC_CQSSC1);	//Set CQSSC1 register to configure device queue status fetch polling time and block count.
	rtkemmc_writel(0x1, emmc_port->emmc_membase+EMMC_CQSSC2);	//Set CQSSC2 to configure RCA
	rtkemmc_writel((cqcfg|EMMC_CQ_EN|EMMC_DCMD_EN), emmc_port->emmc_membase+EMMC_CQCFG);    //0x98012188, Set CQCFG register to configure DCMD_EN, TASK_DESC_SIZE and CQ_EN

	//cmdq interrupt mode
	rtkemmc_hold_int_dec();
	rtkemmc_en_cqe_int();

	isb();
	sync(emmc_port);

	cq_host->enabled = true;

out:
	return err;
}

static void rtkemmc_cmdq_disable(struct mmc_host *mmc, bool soft)
{
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	struct rtkemmc_host *emmc_port = mmc_priv(mmc);

        if (soft)
                rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_CQCFG) & ~(EMMC_CQ_EN), emmc_port->emmc_membase+EMMC_CQCFG);
        cq_host->enabled = false;
}

static int cmdq_dma_map(struct mmc_host *host, struct mmc_request *mrq)
{
	int sg_count;
	struct mmc_data *data = mrq->data;

	if (!data) {
		printk(KERN_ERR "%s: mmc_data = NULL!!!\n", __func__);
		return -EINVAL;
	}

	sg_count = dma_map_sg(mmc_dev(host), data->sg,
			      data->sg_len,
			      (data->flags & MMC_DATA_WRITE) ?
			      DMA_TO_DEVICE : DMA_FROM_DEVICE);
	if (!sg_count) {
		pr_err("%s: sg-len: %d\n", __func__, data->sg_len);
		return -ENOMEM;
	}

	return sg_count;
}

static inline u32 *get_desc(struct cmdq_host *cq_host, u8 tag)
{
	return cq_host->desc_base + (tag * cq_host->slot_sz / 4);
}

static inline u32 *get_link_desc(struct cmdq_host *cq_host, u8 tag)
{
	u32 *desc = get_desc(cq_host, tag);

	return desc + cq_host->task_desc_len/4;
}

static inline dma_addr_t get_trans_desc_dma(struct cmdq_host *cq_host, u8 tag)
{
	return cq_host->trans_desc_dma_base +
		(cq_host->mmc->max_segs * tag *
		 cq_host->trans_desc_len);
}

static inline u32 *get_trans_desc(struct cmdq_host *cq_host, u8 tag)

{
	return cq_host->trans_desc_base +
		(cq_host->trans_desc_len * cq_host->mmc->max_segs * tag / 4);
}

/* set the trans link structure value*/
static void setup_link_desc(struct cmdq_host *cq_host, u8 tag)
{
	u32 *link_temp;
	dma_addr_t trans_temp;

	link_temp = get_link_desc(cq_host, tag);
	trans_temp = get_trans_desc_dma(cq_host, tag);

	memset(link_temp, 0, cq_host->link_desc_len);

	if (tag == DCMD_SLOT) {
		link_temp[1] = rtkemmc_swap_endian(VALID(0) | ACT(0) | END(1));
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "%s: [DEBUG] link descriptor tag=%d, link[0]=0x%x, link[1]=0x%x\n", __func__, tag, link_temp[0], link_temp[1]);
#endif
		return;
	}
	//trans link [32:63] save the trans descriptor dma sddress
	link_temp[0] = rtkemmc_swap_endian(trans_temp);
	link_temp[1] = rtkemmc_swap_endian((VALID(1) | ACT(0x6) | END(0)));
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: [DEBUG] link descriptor tag=%d, link[0]=0x%x, link[1]=0x%x\n", __func__, tag, link_temp[0], link_temp[1]);
#endif
}
/**
 * The allocated descriptor table for task, link & transfer descritors
 * looks like:
 * |----------|
 * |task desc |  |->|----------|
 * |----------|  |  |trans desc|
 * |link desc-|->|  |----------|
 * |----------|          .
 *      .                .
 *  no. of slots      max-segs
 *      .           |----------|
 * |----------|
 * The idea here is to create the [task+trans] table and mark & point the
 * link desc to the transfer desc table on a per slot basis.
 */
static int rtkemmc_cmdq_alloc_tdl(struct cmdq_host *cq_host)
{
	size_t desc_size;
	size_t data_size;
	int i = 0;
	//in realtek, we only support 32 bit ADMA2
	cq_host->task_desc_len = 8;
	cq_host->trans_desc_len = 8;
	cq_host->link_desc_len = 8;

	/* total size of a slot: 1 task & 1 transfer (link) */
	cq_host->slot_sz = cq_host->task_desc_len + cq_host->link_desc_len;
	desc_size = cq_host->slot_sz * cq_host->num_slots;

	//dcmd does not need data buffer
	data_size = cq_host->trans_desc_len * cq_host->mmc->max_segs *
			(cq_host->num_slots - 1);
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: desc_size: %d data_sz: %d slot-sz: %d\n", __func__,
                (int)desc_size, (int)data_size, cq_host->slot_sz);
#endif
	/*
         * allocate a dma-mapped chunk of memory for the descriptors
         * allocate a dma-mapped chunk of memory for link descriptors
         * setup each link-desc memory offset per slot-number to
         * the descriptor table.
         */
	cq_host->desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
                                                 desc_size,
                                                 &cq_host->desc_dma_base,
                                                 GFP_KERNEL);
	cq_host->trans_desc_base = dmam_alloc_coherent(mmc_dev(cq_host->mmc),
                                              data_size,
                                              &cq_host->trans_desc_dma_base,
                                              GFP_KERNEL);
	if (!cq_host->desc_base || !cq_host->trans_desc_base)
		return -ENOMEM;
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "desc-base: 0x%p trans-base: 0x%p\n desc_dma 0x%llx trans_dma: 0x%llx\n",
		cq_host->desc_base, cq_host->trans_desc_base,
		(unsigned long long)cq_host->desc_dma_base,
		(unsigned long long) cq_host->trans_desc_dma_base);
#endif
	for (i=0 ; i < (cq_host->num_slots); i++)
		setup_link_desc(cq_host, i);

	return 0;
}

static void make_cmdq_dcmd_des(u32 *des_base, struct mmc_request *mrq)
{
	u8 resp_type;
	u8 timing;
	u32 tmp_val;

	if (!(mrq->cmd->flags & MMC_RSP_PRESENT)) {
		resp_type = 0x0;
		timing = 0x1;
	} else {
		if (mrq->cmd->flags & (MMC_RSP_BUSY|MMC_RSP_SPI_BUSY)) {
			resp_type = 0x3;
			timing = 0x0;
		} else {
			resp_type = 0x2;
			timing = 0x1;
		}
	}
	/*task[63:32], command argument */
	des_base[0] = rtkemmc_swap_endian(mrq->cmd->arg);
	/*task[31:0], resp type [24:23], cmd_idx[21:16] */
	tmp_val = (VALID(1) |
		   END(1) |
		   INT(1) |
		   QBAR(1) |
		   ACT(0x5) |
		   CMD_INDEX(mrq->cmd->opcode) |
		   CMD_TIMING(timing) | RESP_TYPE(resp_type));
	des_base[1] = rtkemmc_swap_endian(tmp_val);
	/* tran[63:32], all 0 */
	des_base[2] = 0;
	/* tran[31:0], end[1] =1  */
	des_base[3] = rtkemmc_swap_endian(3);	//end and valid bit
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: [DEBUG] DCMD TASK descriptor des_base[0]=0x%x, des_base[1]=0x%x, des_base[2]=0x%x, des_base[3]=0x%x\n",
				__func__, des_base[0], des_base[1],des_base[2],des_base[3]);
#endif
}

static void cmdq_set_tran_desc(u32 *desc,
                                 dma_addr_t addr, int len, bool end)
{
	u32 tmp_val= (VALID(1) |
                 END(end ? 1 : 0) |
                 INT(0) |
                 ACT(0x4) |
                 DAT_LENGTH(len));

	desc[0] = rtkemmc_swap_endian(addr);
	desc[1] = rtkemmc_swap_endian(tmp_val);
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: [DEBUG] trans descriptor desc[0]=0x%x, desc[1]=0x%x, end=%d, len=%d, dma_addr=0x%x\n", __func__, desc[0], desc[1], end, len, addr);
#endif
}

static int make_cmdq_rw_des(u32 *des_base, struct mmc_request *mrq, struct mmc_host *mmc, int tag)
{
	struct mmc_cmdq_req *cmdq_rq = mrq->cmdq_req;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	struct mmc_data *data = mrq->data;
	struct rtkemmc_host *emmc_port;
	emmc_port = mmc_priv(mmc);

	unsigned int blk_cnt = cmdq_rq->data.blocks;	//total block
	u32 blk_cnt2, remain_blk_cnt;
	int blk_addr = cmdq_rq->blk_addr;
	struct scatterlist *sg;
	u8 read=1;
	u32 *desc;
	int  dma_nents = 0;
	int  dma_leng = 0;
	int  dma_addr;
	int tmp_val;
	bool end = false;
	int i=0;
	u32 *link_temp;
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: blk_cnt=%d, blk_addr=%d\n", __func__, blk_cnt, blk_addr);
#endif

	if(mrq->cmdq_req->data.flags == MMC_DATA_READ) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "[DEBUG] %s: MMC_DATA_READ\n", __func__);
#endif
		read = 1;
	}
	else {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "[DEBUG] %s: MMC_DATA_WRITE\n", __func__);
#endif
		read = 0;
	}

	dma_nents = cmdq_dma_map(mrq->host, mrq);

	if (dma_nents < 0) {
		pr_err("%s: %s: unable to map sg lists, %d\n",
				mmc_hostname(mrq->host), __func__, dma_nents);
		return -1;
	}
	//fill out the transfer descriptor
	desc = get_trans_desc(cq_host, tag);
	memset(desc, 0, cq_host->trans_desc_len * cq_host->mmc->max_segs);

	for_each_sg(data->sg, sg, dma_nents, i) {
		dma_addr = sg_dma_address(sg);
		dma_leng = sg_dma_len(sg);
		remain_blk_cnt  = dma_leng >> 9;;

		while(remain_blk_cnt) {
			if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK)
				blk_cnt2 = EMMC_MAX_SCRIPT_BLK;
			else
				blk_cnt2 = remain_blk_cnt;

			if (((i+1) == dma_nents) && (remain_blk_cnt == blk_cnt2))
				end = true;

			cmdq_set_tran_desc(desc, dma_addr, (blk_cnt2<<9), end);

			dma_addr = dma_addr+(blk_cnt2<<9);
			remain_blk_cnt -= blk_cnt2;
			desc += (cq_host->trans_desc_len/4);

			isb();
			sync(emmc_port);
		}
	}
#ifdef RTKEMMC_DEBUG
        printk(KERN_INFO "%s: req: 0x%p tag: %d calc_trans_des: 0x%p sg-cnt: %d\n",
                __func__, mrq->req, tag, desc, dma_nents);
#endif
	//fill out the task descriptor
	/*task[63:32], block address */
	des_base[0] = rtkemmc_swap_endian(blk_addr);
	/*task[31:0], block count[31:16], task parameter[15:6], attribute[5:0] */
	tmp_val = VALID(1) |
		  END(1) |
		  INT(1) |
		  ACT(0x5) |
		  (read <<12) |
		  BLK_COUNT(blk_cnt);
	des_base[1] = rtkemmc_swap_endian(tmp_val);

	isb();
	sync(emmc_port);
	wmb();
	sync(emmc_port);
	/* tran[63:32], setting des2; Physical address to DMA to/from */
	//link descriptor part is set in setup_link_desc() function

	link_temp = get_link_desc(cq_host, tag);
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "%s: [DEBUG] task and link descriptor  tag=%d, des_base[0]=0x%x, des_base[1]=0x%x, link[0]=0x%x, link[1]=0x%x\n",
				__func__, tag, des_base[0], des_base[1], link_temp[0], link_temp[1]);
#endif
	return 1;
}

static void rtkemmc_cmdq_finish_data(struct mmc_host *mmc, unsigned int tag)
{
        struct mmc_request *mrq;
        struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
#ifdef RTKEMMC_DEBUG
	printk(KERN_INFO "[DEBUG] %s, tag=%d\n",__func__, tag);
#endif
        mrq = cq_host->mrq_slot[tag];
        mrq->done(mrq);
}

static int SD_Stream_cmdq_Cmd(struct mmc_host *mmc, struct mmc_request *mrq, u32 tag)
{
	int err = 0;
	struct rtkemmc_host *emmc_port;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);

#ifdef RTKEMMC_DEBUG
	printk(KERN_ERR "[DEBUG] %s, tag=%d\n", __func__, tag);
#endif
	emmc_port = mmc_priv(mmc);

	while(DCMD_wait_38 == true) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "%s: cmd 35 is fired and need to wait until cmd 38 is finished...\n", __func__);
#endif
		usleep_range(10, 30);
	}

	if((readl(emmc_port->emmc_membase+EMMC_CQTDBR)&(1<<tag))==0){
//		printk(KERN_ERR "queue status = 0x%x\n", readl(emmc_port->emmc_membase+EMMC_CQTDBR));
		int ret = make_cmdq_rw_des((u32*)cq_host->desc_base+tag*0x4, mrq, mmc, tag);
		if(ret < 0) {
			printk(KERN_ERR "make_cmdq_rw_des failed....\n");
			return ret;
		}
		cq_host->mrq_slot[tag] = mrq;
		rtkemmc_writel(1<<tag, emmc_port->emmc_membase+EMMC_CQTDBR);
#ifdef RTKEMMC_DEBUG
		printk(KERN_ERR "[DEBUG] cpuid=%d, rtkemmc write EMMC_CQTDBR bit %d, EMMC_CQTDBR=0x%x\n",
			raw_smp_processor_id(), tag, readl(emmc_port->emmc_membase+EMMC_CQTDBR));
#endif
	}
	else{
		printk("read/write slot %d is occupied\n", tag);
		err = RTK_FAIL;
	}
	return err;
}

static int SD_SendCMDGetRSP_cmdq_Cmd(struct mmc_host *mmc, struct mmc_request *mrq, u32 tag)
{
	int err = RTK_SUCC;
	struct rtkemmc_host *emmc_port;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	int i=0;

	emmc_port = mmc_priv(mmc);

	while((readl(emmc_port->emmc_membase+EMMC_CQTDBR)&(1<<DCMD_SLOT))!=0 || DCMD_complete==false) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "DCMD: wait previous dcmd complete, opcode=%d, arg=0x%x, wait %d times, DBR=0x%x\n",
			mrq->cmd->opcode, mrq->cmd->arg, ++i, readl(emmc_port->emmc_membase+EMMC_CQTDBR));
#endif
		usleep_range(10, 30);
		sync(emmc_port);
	}
	DCMD_complete = false;
	DCMD_idx =  mrq->cmd->opcode;   //this statement to check cmd 35 36 38 is uninterruptable

	if(DCMD_idx==MMC_ERASE_GROUP_START) {
		DCMD_wait_38 = true;	//in cmdq mode, cmd 35,36,38 must be continuous and cannot be separated by other cmdq command
#ifdef CONFIG_MMC_RTK_EMMC_PON
		//printk(KERN_INFO "DCMD: cmd is %d, occupy HW semaphore\n", DCMD_idx);
		while(1) {
			if(readl(emmc_port->emmc_membase+EMMC_HD_SEM)==1) break;
			else {
				printk(KERN_INFO "%s: Pon is occupying the semaphore, 0x98012030=0x%x, 0x98012032=0x%x\n",
					__func__, emmc_port->normal_interrupt, emmc_port->error_interrupt);
				usleep_range(10, 30);
			}
		}
#endif
	}

	if((readl(emmc_port->emmc_membase+EMMC_CQTDBR)&(1<<DCMD_SLOT))==0){
		make_cmdq_dcmd_des((u32*)cq_host->desc_base+DCMD_SLOT*4, mrq);
		cq_host->mrq_slot[DCMD_SLOT] = mrq;
		rtkemmc_writel(1<<DCMD_SLOT,emmc_port->emmc_membase+EMMC_CQTDBR);
#ifdef RTKEMMC_DEBUG
		printk(KERN_ERR "[DEBUG] %s, DCMD: mrq->cmd->opcode=%d, mrq->cmd->arg=%d, tag=%d DBR=0x%x\n",
			__func__, mrq->cmd->opcode, mrq->cmd->arg, tag, readl(emmc_port->emmc_membase+EMMC_CQTDBR));
#endif
	}
	else{
		printk(KERN_ERR "dcmd slot 31 is occupied\n");
		err = RTK_FAIL;
	}

	return err;
}

static int rtkemmc_cmdq_request(struct mmc_host *mmc, struct mmc_request *mrq)
{

	int err=-1;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(mmc);
	u32 tag = mrq->cmdq_req->tag + cq_host->start_slot;	//if we enable the pon, slot 0 is reserved for PON

	if (!cq_host->enabled) {
		pr_err("%s: CMDQ host not enabled yet !!!\n",
			mmc_hostname(mmc));
		err = -EINVAL;
		goto out;
	}

	if (mrq->cmdq_req->cmdq_req_flags & DCMD) {
		err = SD_SendCMDGetRSP_cmdq_Cmd(mmc, mrq, DCMD_SLOT);
	}
	else {
		err = SD_Stream_cmdq_Cmd(mmc, mrq, tag);
	}
out:
	return err;
}
#endif
//-------------------------------------------------------------------------------------------------------------------------------

static int rtkemmc_get_ro(struct mmc_host *mmc)
{
	return 0;
}

#ifdef CONFIG_MMC_RTK_EMMC_PON
void pon_initial(struct rtkemmc_host *emmc_port, u32 start_addr, u32 end_addr, u32 id, u32 cmdq)
{
	rtkemmc_writel(readl(emmc_port->crt_membase+0x68)|0x0c000000, emmc_port->crt_membase+0x68);     //release reset of spi2emmc
	rtkemmc_writel(0x0001B6DE, emmc_port->mux_mis_membase + 0x4); // pad mux, spi nand device
	rtkemmc_writel(start_addr, emmc_port->emmc_membase + 0x800); // block start address, 1b
	rtkemmc_writel(end_addr, emmc_port->emmc_membase + 0x804); // block end address
	rtkemmc_writel(0x0a000005, emmc_port->emmc_membase + 0x808); // blcok count and dma length
	rtkemmc_writel(id, emmc_port->emmc_membase + 0x810); // flash ID
	rtkemmc_writel(0x4|0x8|cmdq, emmc_port->emmc_membase + 0x80c);                              // data invert +cmdq enable
	gpio_direction_output(18, 1);
	gpio_direction_output(emmc_port->emmc_pon_gpio, 0);
}
#endif

void rtkemmc_dqs_delay_tap(struct rtkemmc_host *emmc_port, u32 dqs_dly)
{
	//this is a workaround for hank hs400 mode and will be fixed in A01
	u16 state=0;
	unsigned long timeout;
	bool expired = false;
	int err=0;

	rtkemmc_send_cmd6(emmc_port, 0x03b90301, &state);
	rtkemmc_writel(0x80|dqs_dly ,emmc_port->emmc_membase + EMMC_DQS_CTRL1);
	rtkemmc_send_cmd6(emmc_port, 0x03b91301, &state);

	timeout = jiffies + msecs_to_jiffies(3000) + 1;
	do {
		expired = time_after(jiffies, timeout);
		err = rtkemmc_send_cmd13(emmc_port, &state);
		if (expired &&
			(R1_CURRENT_STATE(state) == R1_STATE_PRG)) {
			printk(KERN_ERR "%s: Card stuck in programming state! %s\n",
				mmc_hostname(emmc_port->mmc), __func__);
			break;
		}
	}while(R1_CURRENT_STATE(state) == R1_STATE_PRG);
}

static int rtkemmc_prepare_hs400_tuning(struct mmc_host *host, struct mmc_ios *ios)
{
	struct rtkemmc_host *emmc_port;
        emmc_port = mmc_priv(host);
	printk(KERN_ERR "Prepare HS400 mode...\n");
	rtkemmc_writel(0x88 ,emmc_port->emmc_membase + EMMC_DQS_CTRL1);	//in hank A00, this setting will not take effect

	rtkemmc_writel(0x80|0x38, emmc_port->emmc_membase + EMMC_WCMD_CTRL);
	rtkemmc_writel(0x1, emmc_port->emmc_membase + EMMC_CMD_CTRL_SET);

	return 0;
}

static void set_cmd_info(struct mmc_card *card,struct mmc_command * cmd, struct sd_cmd_pkt * cmd_info,u32 opcode,u32 arg,u8 rsp_para)
{
	memset(cmd, 0, sizeof(struct mmc_command));
	memset(cmd_info, 0, sizeof(struct sd_cmd_pkt));

	cmd->opcode         = opcode;
	cmd->arg            = arg;
	cmd_info->cmd       = cmd;
	cmd_info->emmc_port    = mmc_priv(card->host);
	cmd_info->rsp_len   = rsp_para;
}

void print_reg_info(struct rtkemmc_host *emmc_port)
{
	printk(KERN_ERR "0x98012034 NORMAL INTERRUPT EN= 0x%x\n",readw(emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_EN_R));
	printk(KERN_ERR "0x98012036 ERROR INTERRUPT EN= 0x%x\n",readw(emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_EN_R));
	printk(KERN_ERR "0x98012038 NORMAL INTERRUPT SIGNAL EN= 0x%x\n",readw(emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R));
	printk(KERN_ERR "0x9801203a ERROR INTERRUPT SIGNAL EN = 0x%x\n",readw(emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R));
	printk(KERN_ERR "0x9801203e HOST CONTROL2 REG = 0x%x\n",readw(emmc_port->emmc_membase+EMMC_HOST_CTRL2_R));
	printk(KERN_ERR "0x98012024 PRESENT STATE REG = 0x%x\n",readl(emmc_port->emmc_membase+EMMC_PSTATE_REG));
	printk(KERN_ERR "0x98012028 HOST CONTROL1 REG= 0x%x\n",readb(emmc_port->emmc_membase+EMMC_HOST_CTRL1_R));
	printk(KERN_ERR "0x9801200c TRANSFER MODE REG = 0x%x\n",readw(emmc_port->emmc_membase+EMMC_XFER_MODE_R));
	printk(KERN_ERR "0x98012004 EMMC BLOCK SIZE = 0x%x\n",readw(emmc_port->emmc_membase+EMMC_BLOCKSIZE_R));
	printk(KERN_ERR "0x98012006 EMMC BLOCK COUNT = 0x%08x\n", readw(emmc_port->emmc_membase+EMMC_BLOCKCOUNT_R));
        printk(KERN_ERR "0x98012008 EMMC CMDARG = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_ARGUMENT_R));
}

void print_err_reg(u32 cmd_idx, u16 normal_interrupt, u16 error_interrupt)
{
	printk(KERN_ERR "=====================================================\n");
	printk(KERN_ERR "g_bTuning=%d cmd_idx 0x%08x, op_code (%d)\n",g_bTuning, cmd_idx, CMD_IDX_MASK(cmd_idx));
	printk(KERN_ERR "0x98012030 NORMAL INTERRUPT STAT = 0x%x\n", normal_interrupt);
	printk(KERN_ERR "0x98012032 ERROR INTERRUPT STAT = 0x%x\n", error_interrupt);
	if( error_interrupt & EMMC_VENDOR_ERR3 ) {           printk(KERN_ERR "bit 15: EMMC_VENDOR_ERR3\n");       }
	if( error_interrupt & EMMC_VENDOR_ERR2 ) {           printk(KERN_ERR "bit 14: EMMC_VENDOR_ERR2\n");  }
	if( error_interrupt & EMMC_VENDOR_ERR1 ) {       printk(KERN_ERR "bit 13: EMMC_VENDOR_ERR1\n");  }
	if( error_interrupt & EMMC_BOOT_ACK_ERR ) {           printk(KERN_ERR "bit 12: EMMC_BOOT_ACK_ERR\n");       }
	if( error_interrupt & EMMC_RESP_ERR ) {          printk(KERN_ERR "bit 11: EMMC_RESP_ERR\n");    }
	if( error_interrupt & EMMC_TUNING_ERR ) {           printk(KERN_ERR "bit 10: EMMC_TUNING_ERR\n");     }
	if( error_interrupt & EMMC_ADMA_ERR ) {      printk(KERN_ERR "bit  9: EMMC_ADMA_ERR\n"); }
	if( error_interrupt & EMMC_AUTO_CMD_ERR ) {       printk(KERN_ERR "bit  8: EMMC_AUTO_CMD_ERR\n");  }
	if( error_interrupt & EMMC_CUR_LMT_ERR ) {          printk(KERN_ERR "bit  7: EMMC_CUR_LMT_ERR\n");    }
	if( error_interrupt & EMMC_DATA_END_BIT_ERR ) {          printk(KERN_ERR "bit  6: EMMC_DATA_END_BIT_ERR\n");        }
	if( error_interrupt & EMMC_DATA_CRC_ERR ) {          printk(KERN_ERR "bit  5: EMMC_DATA_CRC_ERR\n");   }
	if( error_interrupt & EMMC_DATA_TOUT_ERR ) {          printk(KERN_ERR "bit  4: EMMC_DATA_TOUT_ERR\n");  }
	if( error_interrupt & EMMC_CMD_IDX_ERR ) {           printk(KERN_ERR "bit  3: EMMC_CMD_IDX_ERR\n");   }
	if( error_interrupt & EMMC_CMD_END_BIT_ERR ) {            printk(KERN_ERR "bit  2: EMMC_CMD_END_BIT_ERR\n");  }
	if( error_interrupt & EMMC_CMD_CRC_ERR ) {            printk(KERN_ERR "bit  1: EMMC_CMD_CRC_ERR\n");    }
	if( error_interrupt & EMMC_CMD_TOUT_ERR ) {           printk(KERN_ERR "bit  0: EMMC_CMD_TOUT_ERR\n");   }
	printk(KERN_ERR "=====================================================\n");
}

void print_ip_desc(struct rtkemmc_host *emmc_port)
{ 
	//unsigned int bytecnt = 0, desc_cnt = 0, i = 0;
	//unsigned int paddr_base = emmc_port->desc_paddr;

	printk(KERN_ERR "------------------------------>\n");
	printk(KERN_ERR "EMMC IP_DESC0 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC0));
	printk(KERN_ERR "EMMC IP_DESC1 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC1));
	printk(KERN_ERR "EMMC IP_DESC2 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC2));
	printk(KERN_ERR "EMMC IP_DESC3 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC3));

	printk(KERN_ERR "0x98012058 EMMC EMMC_ADMA_SA_LOW_R = 0x%08x\n------------------------------>\n", readl(emmc_port->emmc_membase+EMMC_ADMA_SA_LOW_R));
#if 0
	bytecnt = readl(emmc_port->emmc_membase+EMMC_BYTCNT);
	desc_cnt = bytecnt / 4096;

	for (i = 0 ; i < desc_cnt; i++){
		printk(KERN_INFO "=============== %u-th set of descriptor==============\n", i);
		printk(KERN_INFO "DESC0(0x%08x) = 0x%08x\n", paddr_base,  *(gddr_descriptor + 4*i));
		printk(KERN_INFO"DESC1(0x%08x) = 0x%08x\n", paddr_base + 16*i + 4, *(gddr_descriptor + 4*i + 1));
		printk(KERN_INFO "DESC2(0x%08x) = 0x%08x\n", paddr_base + 16*i + 8, *(gddr_descriptor + 4*i + 2));
		printk(KERN_INFO "DESC3(0x%08x) = 0x%08x\n", paddr_base + 16*i + 12, *(gddr_descriptor + 4*i + 3));
	}
	printk(KERN_INFO "=====================================================\n");
#endif
}

void mmc_host_reset(struct rtkemmc_host *emmc_port)
{

	MMCPRINTF("%s : \n", __func__);

        rtkemmc_writeb(0x07, emmc_port->emmc_membase + EMMC_SW_RST_R);      //9801202f, Software Reset Register
        isb();
        sync(emmc_port);

        rtkemmc_writeb(0x0e, emmc_port->emmc_membase + EMMC_TOUT_CTRL_R);      //9801202e, Timeout Control register
        isb();
        sync(emmc_port);

        rtkemmc_writew(0x200, emmc_port->emmc_membase + EMMC_BLOCKSIZE_R);      //98012004, block size = 512Byte
        isb();
        sync(emmc_port);
#if 0
        writew(0xe0b, emmc_port->emmc_membase + 0x2c);      //9801202c, clock control
        isb();
        sync(emmc_port);
#endif

	rtkemmc_writew(0xfeff, emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_EN_R);    //98012034, enable all Normal Interrupt Status register
        isb();
        sync(emmc_port);

        rtkemmc_writew(EMMC_ALL_ERR_STAT_EN, emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_EN_R); //98012036, enable all error Interrupt Status register
        isb();
        sync(emmc_port);

        rtkemmc_writew(0xfeff,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R); //98012038, enable all Normal SIGNAL Interrupt  register
        isb();
        sync(emmc_port);

        rtkemmc_writew(EMMC_ALL_ERR_SIGNAL_EN,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R);      //9801203a, enable all error SIGNAL Interrupt register
        isb();
        sync(emmc_port);

	MMCPRINTF("%s : \n", __func__);
}
static void rtkemmc_shutdown(struct platform_device *pdev)
{
	//struct device *dev = &pdev->dev;

	printk(KERN_ERR "[eMMC] Shutdown\n");
	pm_runtime_force_suspend(&pdev->dev);
}

#ifdef CONFIG_PM
static int rtkemmc_suspend(struct device *dev)
{
	int ret = 0;
	struct rtkemmc_host *emmc_port=NULL;
	struct mmc_host *mmc = NULL;
	suspend = 1;
	mmc = mmc_host_local;
	emmc_port = mmc_priv(mmc);
#if 1	//in hank A00 version
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x1, emmc_port->emmc_membase+EMMC_OTHER1);        //disable L4 gated
	isb();
	sync(emmc_port);
#endif
	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[%s] Enter %s Idle mode\n",DRIVER_NAME, __func__);
		//rtkemmc_backup_registers(emmc_port);
	}else{
		//For suspend mode
		printk(KERN_ERR "[%s] Enter %s Suspend mode\n",DRIVER_NAME, __func__);
	}

	ret = pm_runtime_force_suspend(dev);
	printk(KERN_ERR "[%s] Exit %s\n",DRIVER_NAME,__func__);
	return ret;
}

static int rtkemmc_resume(struct device *dev)
{
	int ret = 0;
	struct mmc_host *mmc = NULL;
	struct rtkemmc_host *emmc_port=NULL;
	struct mmc_host *host = NULL;

	mmc = mmc_host_local;
	emmc_port = mmc_priv(mmc);
	if (!emmc_port)
		BUG();
    
	host = emmc_port->mmc;
	host->card->host = mmc;
	g_bResuming=1;

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[%s] Enter %s Idle mode\n",DRIVER_NAME, __func__);
		//rtkemmc_restore_registers(emmc_port);
	}else{
		//For suspend mode
		printk(KERN_ERR "[%s] Enter %s Suspend mode\n",DRIVER_NAME, __func__);
	}

	if (!ret)
		ret = pm_runtime_force_resume(dev);

	rtkemmc_set_pin_mux(emmc_port);
	rtkemmc_chk_card_insert(emmc_port);
	sync(emmc_port);

	g_bResuming=0;
	init_completion(emmc_port->int_waiting);

#ifdef CONFIG_MMC_RTK_EMMC_PON  //we just write the fix value for fpga test, we will read the input from device tree after negotiate with android team later
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 1);
#else
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 0);      //currently, we disable command queue first, offset = 256x1024x1024/512/2048x512x5
#endif
#endif
	printk(KERN_ERR "[%s] Exit %s\n",DRIVER_NAME,__func__);

	return ret;
}

static const struct dev_pm_ops rtk_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(rtkemmc_suspend, rtkemmc_resume)
};
#endif

static int check_card_status(struct rtkemmc_host *emmc_port)
{
	u32 status=0;
	u8 state=0;

	rtkemmc_send_status(emmc_port->mmc->card, &status, &state, 0, 1);
#ifdef RTKEMMC_DEBUG
	if((status&0x80000000)==0x80000000)
		printk(KERN_INFO "ADDRESS OUT OF RANGE \n");
	if((status&0x40000000)==0x40000000)
		printk(KERN_INFO "ADDRESS MISALIGN \n");

	if((status&0x20000000)==0x20000000)
		printk(KERN_INFO "BLOCK LEN ERROR \n");

	if((status&0x10000000)==0x10000000)
		printk(KERN_INFO "ERASE SEQ ERROR \n");

	if((status&0x08000000)==0x08000000)
		printk(KERN_INFO "ERASE PARAM ERROR \n");

	if((status&0x04000000)==0x04000000)
		printk(KERN_INFO "WP VIOLATION \n");

	if((status&0x02000000)==0x02000000)
		printk(KERN_INFO "DEVICE IS LOCKED \n");

	if((status&0x01000000)==0x01000000)
		printk(KERN_INFO "LOCK/UNLOCK FAILED \n");

	if((status&0x00800000)==0x00800000)
		printk(KERN_INFO "COM CRC ERROR \n");

	if((status&0x00400000)==0x00400000)
		printk(KERN_INFO "ILLEGAL COMMAND \n");

	if((status&0x00200000)==0x00200000)
		printk(KERN_INFO "DEVICE ECC FAILED \n");

	if((status&0x00100000)==0x00100000)
		printk(KERN_INFO "CC ERROR \n");

	if((status&0x00080000)==0x00080000)
		printk(KERN_INFO "ERROR RELATED TO HOST COM \n");

	if((status&0x00010000)==0x00010000)
		printk(KERN_INFO "CID/CSD OVERWRITE ERROR \n");

	if((status&0x00008000)==0x00008000)
		printk(KERN_INFO "WP ERASE SKIP \n");

	if((status&0x00002000)==0x00002000)
		printk(KERN_INFO "ERASE RESET \n");

	if((status&0x00000100)==0x00000000)   //<-------------------------???????????????
		printk(KERN_INFO "NOT READY FOR DATA \n");

	if((status&0x00000080)==0x00000080)
		printk(KERN_INFO "SWTICH ERROR \n");

	if((status&0x00000040)==0x00000040)
		printk(KERN_INFO "EXCEPTION EVENT \n");

	if((status&0x00000020)==0x00000020)
		printk(KERN_INFO "APP CMD ENABLED \n");
#endif
	if(state == 4) {
#ifdef RTKEMMC_DEBUG
		printk("tran\n");
#endif
		return 0;
	}
	else if(state <=10) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "cur_state=%s\n",state_tlb[state]);
#endif
		return -1;
	}
	else {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "cur_state=reserved\n");
#endif
                return -1;
	}
}

void error_handling(struct rtkemmc_host *emmc_port)
{
	rtkemmc_writew(0, emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R);      //9801203a, enable all error SIGNAL Interrupt register
	isb();
	sync(emmc_port);

	if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
		(EMMC_AUTO_CMD_ERR|EMMC_CMD_IDX_ERR|EMMC_CMD_END_BIT_ERR|EMMC_CMD_CRC_ERR|EMMC_CMD_TOUT_ERR)) !=0){ //check cmd line
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "CMD Line error occurs \n");
#endif
		rtkemmc_writeb(0x2, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
		wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x2<<24), 0x0, __func__);	//wait for clear 0x2f bit 1
	}
	if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
		(EMMC_ADMA_ERR|EMMC_DATA_END_BIT_ERR|EMMC_DATA_CRC_ERR|EMMC_DATA_TOUT_ERR)) !=0){ //check data line
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "DAT Line error occurs \n");
#endif
		rtkemmc_writeb(0x4, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
		wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x4<<24), 0x0, __func__); //wait for clear 0x2f bit 2
	}

	//synchronous abort: stop host dma
	rtkemmc_writeb(0x1, emmc_port->emmc_membase + EMMC_BGAP_CTRL_R); //stop emmc transactions  <-------????????????????????????????
        wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R), 0x2, 0x2, __func__); //wait for xfer complete
        rtkemmc_writew(0x2, emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_R); //clear transfer complete status

	//synchronous abort: issue abort coomand
	rtkemmc_stop_transmission(emmc_port->mmc->card, 1);
        if(check_card_status(emmc_port)!=0){
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "Non-recoverable Error \n");
#endif
	}

	rtkemmc_writeb(0x6, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
        wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x6<<24), 0x0, __func__); //wait for clear 0x2f bit 1 & 2
        wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_PSTATE_REG), 0x3, 0x0, __func__); //wait for cmd and data lines are not in use
}

static int rtkemmc_send_cmd13(struct rtkemmc_host *emmc_port, u16 * state)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	int err=0;
	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	cmd.opcode         = MMC_SEND_STATUS;
	cmd.arg            = (1<<RCA_SHIFTER);
	cmd_info.cmd       = &cmd;
	cmd_info.emmc_port = emmc_port;
	cmd_info.rsp_len   = 6;

	gPreventRetry=1;
	err = SD_SendCMDGetRSP(&cmd_info,1);
	gPreventRetry=0;

	if(err ) {
		mmcmsg3(KERN_WARNING "%s: MMC_SEND_STATUS fail\n",DRIVER_NAME);
		if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
			(EMMC_AUTO_CMD_ERR|EMMC_CMD_IDX_ERR|EMMC_CMD_END_BIT_ERR|EMMC_CMD_CRC_ERR|EMMC_CMD_TOUT_ERR)) !=0){ //check cmd line
#ifdef RTKEMMC_DEBUG
			printk(KERN_INFO "CMD Line error occurs \n");
#endif
			rtkemmc_writeb(0x2, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x2<<24), 0x0, __func__); //wait for clear 0x2f bit 1
		}
		if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
			(EMMC_ADMA_ERR|EMMC_DATA_END_BIT_ERR|EMMC_DATA_CRC_ERR|EMMC_DATA_TOUT_ERR)) !=0){ //check data line
#ifdef RTKEMMC_DEBUG
			printk(KERN_INFO "DAT Line error occurs \n");
#endif
			rtkemmc_writeb(0x4, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x4<<24), 0x0, __func__); //wait for clear 0x2f bit 2
		}
	}
	else {
		u8 cur_state = R1_CURRENT_STATE(cmd.resp[0]);
		*state = cur_state;
		mmcmsg1("cur_state=%s\n",state_tlb[cur_state]);
	}

	return err;
}

int rtkemmc_send_cmd6(struct rtkemmc_host *emmc_port, u32 args, u16 * state)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	int err=0;
	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	cmd.opcode         = MMC_SWITCH;
	cmd.arg            = args;
	cmd.flags	   = MMC_CMD_AC|MMC_RSP_SPI_R1B | MMC_RSP_R1B;
	cmd_info.cmd       = &cmd;
	cmd_info.emmc_port = emmc_port;
	cmd_info.rsp_len   = 6;

	gPreventRetry=1;
	err = SD_SendCMDGetRSP(&cmd_info,1);
	gPreventRetry=0;

	if(err ) {
		printk(KERN_ERR "%s: send cmd6 fail\n",DRIVER_NAME);
		if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
			(EMMC_AUTO_CMD_ERR|EMMC_CMD_IDX_ERR|EMMC_CMD_END_BIT_ERR|EMMC_CMD_CRC_ERR|EMMC_CMD_TOUT_ERR)) !=0){ //check cmd line
#ifdef RTKEMMC_DEBUG
			printk(KERN_INFO "CMD Line error occurs \n");
#endif
			rtkemmc_writeb(0x2, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x2<<24), 0x0, __func__); //wait for clear 0x2f bit 1
		}
		if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
			(EMMC_ADMA_ERR|EMMC_DATA_END_BIT_ERR|EMMC_DATA_CRC_ERR|EMMC_DATA_TOUT_ERR)) !=0){ //check data line
#ifdef RTKEMMC_DEBUG
			printk(KERN_INFO "DAT Line error occurs \n");
#endif
			rtkemmc_writeb(0x4, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x4<<24), 0x0, __func__); //wait for clear 0x2f bit 2
		}
	}
	else {
		u8 cur_state = R1_CURRENT_STATE(cmd.resp[0]);
		*state = cur_state;
		mmcmsg1("cur_state=%s\n",state_tlb[cur_state]);
	}

	return err;
}

int rtkemmc_send_cmd18(struct rtkemmc_host *emmc_port, int size, unsigned long addr)
{
	int ret_err=0;
	struct sd_cmd_pkt cmd_info;
	//struct mmc_host *host = emmc_port->mmc;
	unsigned char *crd_tmp_buffer=NULL;
	struct mmc_data *data=NULL;
	struct mmc_command *cmd=NULL;
	int i=0;
	memset(&cmd_info, 0x00, sizeof(struct sd_cmd_pkt));

	crd_tmp_buffer = (unsigned char *)emmc_port->dma_paddr;
//	printk(KERN_ERR "crd_tmp_buffer=%p, emmc_port->dma_paddr=%p, gddr_dma_org=%p\n",crd_tmp_buffer,emmc_port->dma_paddr,gddr_dma_org);
	if (crd_tmp_buffer == NULL) {
		printk(KERN_ERR "%s,%s : crd_tmp_buffer == NULL\n",DRIVER_NAME,__func__);
		return -5;
	}

	for(i=0;i<(size/4);i++) {
		*(u32 *)(gddr_dma_org+(i*4)) = 0xdeadbeef;
		//isb();
		//sync(emmc_port);
	}
	wmb();

	if (cmd_info.cmd == NULL) {
		cmd  = (struct mmc_command*) kmalloc(sizeof(struct mmc_command),GFP_KERNEL);
		memset(cmd, 0x00, sizeof(struct mmc_command));
		cmd_info.cmd  = (struct mmc_command*) cmd;
	}
	cmd_info.emmc_port = emmc_port;
	cmd_info.cmd->arg = addr;
	cmd_info.cmd->opcode = MMC_READ_MULTIPLE_BLOCK;
	cmd_info.rsp_len         = 6;
	cmd_info.byte_count  = 0x200;
	cmd_info.block_count = size/cmd_info.byte_count;
	cmd_info.dma_buffer = crd_tmp_buffer;

	if (cmd_info.cmd->data == NULL) {
		data  = (struct mmc_data*) kmalloc(sizeof(struct mmc_data),GFP_KERNEL);
		memset(data, 0x00, sizeof(struct mmc_data));
		cmd_info.cmd->data = data;
		data->flags = MMC_DATA_READ;
	}
	else
		cmd_info.cmd->data->flags = MMC_DATA_READ;
	MMCPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), resp_type=0x%08x, host=0x%08x, card=0x%08x -------\n",
		__FILE__, __func__, __LINE__, cmd_info.cmd->opcode, cmd_info.cmd->opcode, cmd_info.cmd->flags, host, host->card);
	ret_err = SD_Stream_Cmd(EMMC_AUTOREAD1, &cmd_info, 1);
	if (ret_err) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "Tuning rx cmd 18 err and call error handling\n");
#endif
		error_handling(emmc_port);
        }

	if (cmd) {
		kfree(cmd);
		cmd_info.cmd = NULL;
		cmd=NULL;
	}
	if (data) {
		kfree(data);
		//cmd_info.cmd->data = NULL;
		data=NULL;
	}
	return ret_err;
}

int rtkemmc_send_cmd25(struct rtkemmc_host *emmc_port,int size, unsigned long addr, int data_src, int *hs400_data)
{
        int ret_err=0,i=0;
        struct sd_cmd_pkt cmd_info;
//        struct mmc_host *host = emmc_port->mmc;
        char *crd_tmp_buffer=NULL;
        struct mmc_data *data=NULL;
        struct mmc_command *cmd=NULL;
//      unsigned long flags=0;
        memset(&cmd_info, 0x00, sizeof(struct sd_cmd_pkt));

        crd_tmp_buffer = (unsigned char *) emmc_port->dma_paddr;
//	printk(KERN_ERR "crd_tmp_buffer=%p, emmc_port->dma_paddr=%p, gddr_dma_org=%p\n",crd_tmp_buffer,emmc_port->dma_paddr,gddr_dma_org);
        if (crd_tmp_buffer == NULL)
        {
                printk(KERN_ERR "%s,%s : crd_ext_csd == NULL\n",DRIVER_NAME,__func__);
                return -5;
        }

	if(data_src==0) {
		for(i=0;i<(size/4);i++)
		{
			if(GLOBAL==0x80000000) GLOBAL=0;
			else GLOBAL++;
			*(u32 *)(gddr_dma_org+(i*4)) = GLOBAL;
		}
	}
	else if(data_src==1) {
		for(i=0;i<(size/4);i++)
                {
                        if(GLOBAL==0x80000000) GLOBAL=0;
                        else GLOBAL++;
                        *(u32 *)(gddr_dma_org+(i*4)) = hs400_data[i];
                }
	}
	else printk(KERN_ERR "data_source flag should be 0 or 1\n");

        wmb();

        if (cmd_info.cmd == NULL)
        {
                cmd  = (struct mmc_command*) kmalloc(sizeof(struct mmc_command),GFP_KERNEL);
                memset(cmd, 0x00, sizeof(struct mmc_command));
                cmd_info.cmd  = (struct mmc_command*) cmd;
        }

        cmd_info.emmc_port = emmc_port;
        cmd_info.cmd->arg = addr;
        cmd_info.cmd->opcode = MMC_WRITE_MULTIPLE_BLOCK;
        cmd_info.rsp_len         = 6;
        cmd_info.byte_count  = 0x200;
        cmd_info.block_count = size/cmd_info.byte_count;
        cmd_info.dma_buffer = crd_tmp_buffer;

	if (cmd_info.cmd->data == NULL)
        {
                data  = (struct mmc_data*) kmalloc(sizeof(struct mmc_data),GFP_KERNEL);
                memset(data, 0x00, sizeof(struct mmc_data));
                cmd_info.cmd->data = data;
                data->flags = MMC_DATA_WRITE;
        }
        else
                cmd_info.cmd->data->flags = MMC_DATA_WRITE;

        MMCPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), resp_type=0x%08x, host=0x%08x, card=0x%08x , cmd=0x%08x, data=0x%08x-------\n",
                __FILE__, __func__, __LINE__, cmd_info.cmd->opcode, cmd_info.cmd->opcode, cmd_info.cmd->flags, host, host->card,cmd,data);
        ret_err = SD_Stream_Cmd(EMMC_AUTOWRITE1, &cmd_info, 1);
        if (ret_err)
        {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "Tuning rx cmd 25 err and call error handling\n");
#endif
		error_handling(emmc_port);
        }
        MMCPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), resp_type=0x%08x, host=0x%08x, card=0x%08x , cmd=0x%08x, data=0x%08x-------\n",
                __FILE__, __func__, __LINE__, cmd_info.cmd->opcode, cmd_info.cmd->opcode, cmd_info.cmd->flags, host, host->card,cmd,data);
#if 1
        if (cmd)
        {
                cmd_info.cmd = NULL;
                kfree(cmd);
                cmd=NULL;
        }
        if (data)
        {
                //cmd_info.cmd->data = NULL;
                kfree(data);
                data=NULL;
        }
#endif
        sync(emmc_port);
        return ret_err;
}

int rtkemmc_send_cmd21(struct rtkemmc_host *emmc_port, int size, unsigned long addr)
{
        int ret_err=0;
        struct sd_cmd_pkt cmd_info;
        //struct mmc_host *host = emmc_port->mmc;
        unsigned char *crd_tmp_buffer=NULL;
        struct mmc_data *data=NULL;
        struct mmc_command *cmd=NULL;
        int i=0;
        memset(&cmd_info, 0x00, sizeof(struct sd_cmd_pkt));

        crd_tmp_buffer = (unsigned char *)emmc_port->dma_paddr;
//      printk(KERN_ERR "crd_tmp_buffer=%p, emmc_port->dma_paddr=%p, gddr_dma_org=%p\n",crd_tmp_buffer,emmc_port->dma_paddr,gddr_dma_org);
        if (crd_tmp_buffer == NULL) {
                printk(KERN_ERR "%s,%s : crd_tmp_buffer == NULL\n",DRIVER_NAME,__func__);
                return -5;
        }

        for(i=0;i<(size/4);i++) {
                *(u32 *)(gddr_dma_org+(i*4)) = 0xdeadbeef;
                //isb();
                //sync(emmc_port);
        }
        wmb();

        if (cmd_info.cmd == NULL) {
                cmd  = (struct mmc_command*) kmalloc(sizeof(struct mmc_command),GFP_KERNEL);
                memset(cmd, 0x00, sizeof(struct mmc_command));
                cmd_info.cmd  = (struct mmc_command*) cmd;
        }
        cmd_info.emmc_port = emmc_port;
        cmd_info.cmd->arg = addr;
        cmd_info.cmd->opcode = MMC_SEND_TUNING_BLOCK_HS200;
        cmd_info.rsp_len         = 6;
        cmd_info.byte_count  = 0x80;
        cmd_info.block_count = 1;
        cmd_info.dma_buffer = crd_tmp_buffer;

        if (cmd_info.cmd->data == NULL) {
                data  = (struct mmc_data*) kmalloc(sizeof(struct mmc_data),GFP_KERNEL);
                memset(data, 0x00, sizeof(struct mmc_data));
                cmd_info.cmd->data = data;
                data->flags = MMC_DATA_READ;
        }
        else
                cmd_info.cmd->data->flags = MMC_DATA_READ;
        MMCPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), resp_type=0x%08x, host=0x%08x, card=0x%08x -------\n",
                __FILE__, __func__, __LINE__, cmd_info.cmd->opcode, cmd_info.cmd->opcode, cmd_info.cmd->flags, host, host->card);
        ret_err = SD_Stream_Cmd(EMMC_AUTOREAD1, &cmd_info, 1);
	if (ret_err) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "Tuning rx cmd 21 err and call error handling\n");
#endif
		error_handling(emmc_port);
        }

        if (cmd) {
                kfree(cmd);
                cmd_info.cmd = NULL;
                cmd=NULL;
        }
        if (data) {
                kfree(data);
                //cmd_info.cmd->data = NULL;
                data=NULL;
        }
        return ret_err;
}
int search_best(u32 window, u32 range)
{
        int i, j, k, max;
        int window_temp[32];
        int window_start[32];
        int window_end[32];
        int window_max=0;
        int window_best=0;
        int parse_end=1;

        for( i=0; i<0x20; i++ ) {
                window_temp[i]=0;
                window_start[i]=0;
                window_end[i]=-1;
        }
        j=1;
        i=0;
        k=0;
        max=0;
	while((i<(range-1)) && (k<(range-1))){
                parse_end=0;
                for( i=window_end[j-1]+1; i<range; i++ ){
                        if (((window>>i)&1)==1 ){
                                window_start[j]=i;
                                break;
                        }
                }
                if( i==range){
                        break;
                }
                for( k=window_start[j]+1; k<range; k++ ){
                        if(((window>>k)&1)==0){
                                window_end[j]=k-1;
                                parse_end=1;
                                break;
                        }
                }
                if(parse_end==0){
                        window_end[j]=range-1;
                }
                j++;
        }
        for(i=1; i<j; i++){
                window_temp[i]= window_end[i]-window_start[i]+1;
        }
        if((((window)&1)==1)&&(((window>>(range-1))&1)==1))
        {
                window_temp[1]=window_temp[1]+window_temp[j-1];
                window_start[1]=window_start[j-1];
        }
        for(i=1; i<j; i++){
                if(window_temp[i]>window_max){
                        window_max=window_temp[i];
                        max=i;
                }
        }
	if(window==0xffffffff){
                window_best=0x10;
        }
        else if((window==0xffff)&&(range==0x10)){
                window_best=0x8;
                }
        else if((((window&1)==1)&&(((window>>(range-1))&1)==1))&&(max==1)){
		window_best=(((window_start[max]+window_end[max]+range)/2)&(range-1));
        }
        else {
                window_best=((window_start[max]+window_end[max])/2)&0x1f;
        }
        return window_best;
}

void rtkemmc_hw_reset(void)
{
        struct mmc_host * mmc = mmc_host_local;
        struct rtkemmc_host *emmc_port;
        emmc_port = mmc_priv(mmc);
        if(emmc_port!=NULL) {
#if 0
		//hank emmc hw rest code
#endif
        }

}
EXPORT_SYMBOL(rtkemmc_hw_reset);

void rtkemmc_phase_tuning(struct rtkemmc_host *emmc_port,u32 mode,int flag)
{
	u32 TX_window=0;
        u32 RX_window=0;
	u32 TX1_window=0;
	int TX_best=0x0;
	int RX_best=0x0;
	int TX1_best=0x0;
        int i=0;
        u32 range=0;
        u16 state=0;

#if 0
        if (mode == MODE_HS400 || mode == MODE_DDR)
                range = 0x10;
        else
#endif
	range = 0x20;

	if(hs400_to_hs200_flag==true && (emmc_port->tx_tuning && emmc_port->rx_tuning)) {
		hs400_to_hs200_flag=false;
		phase(emmc_port, HS200_TX, HS200_RX);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

		sync(emmc_port);
                printk(KERN_ERR "down speed to hs200: restore tx & rx phase: TX=0x%x, RX=0x%x\n", HS200_TX, HS200_RX);
		return;
	}
	if(suspend == 1 && (emmc_port->tx_tuning || emmc_port->rx_tuning) && emmc_port->mmc->card->cid.manfid != 0x13)
	{
		if(emmc_port->tx_tuning==0 && emmc_port->rx_tuning==1) {
			phase(emmc_port, VP0_saved, suspend_VP1);
		}
		else if(emmc_port->tx_tuning==1 && emmc_port->rx_tuning==0)
		{
			phase(emmc_port, suspend_VP0, VP1_saved);
		}
		else {
			phase(emmc_port, suspend_VP0, suspend_VP1);
		}

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

		sync(emmc_port);
		printk(KERN_ERR "suspend/resume: restore tx & rx phase: TX=0x%x, RX=0x%x\n", suspend_VP0, suspend_VP1);
		if(mode == MODE_HS200) {
			suspend = 0;
		}
		return;
	}
#ifdef PHASE_INHERITED
	if (emmc_port->tx_tuning || emmc_port->rx_tuning){
                phase(emmc_port, (emmc_port->tx_tuning)?0xff:VP0_saved, (emmc_port->rx_tuning)?0xff:VP1_saved);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

                sync(emmc_port);
        }
        else {
                phase(emmc_port, VP0_saved, VP1_saved); //VP0, VP1 phase

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

                sync(emmc_port);
		printk(KERN_INFO "Inherit bootcode tuning phase: TX=0x%x, RX=0x%x\n", VP0_saved, VP1_saved);
                return;
        }
#else
	phase(emmc_port, 0, 0); //VP0, VP1 phase

	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

	mdelay(5);
        sync(emmc_port);
#endif

	if (emmc_port->tx_tuning) {
		if (mode == MODE_DDR && flag==1)
			printk(KERN_ERR "Start DDR50 TX Tuning:\n");
		else if (mode == MODE_HS400 && flag==1)
			printk(KERN_ERR "Start HS400 TX Tuning: \n");
		else if(flag==1)
			printk(KERN_ERR "Start HS200 TX Tuning:\n");
                for(i=0;i<range;i++) {
                        phase(emmc_port, i, 0xff);

			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
			udelay(1);
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

#ifdef DEBUG
                        printk("phase =0x%x \n", i);
#endif

                        if((rtkemmc_send_cmd13(emmc_port, &state)&0x01) != 0)
                                TX_window= TX_window&(~(1<<i));
                        else
                                TX_window= TX_window|((1<<i));
                }
		TX_best = search_best(TX_window, range);
		if(flag==1)printk(KERN_ERR "TX_WINDOW = 0x%08x TX_best=0x%x\n", TX_window, TX_best);
                phase(emmc_port, TX_best, 0xff);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
		suspend_VP0 = TX_best;
        }

	if (emmc_port->rx_tuning) {
		if (mode == MODE_DDR && flag==1)
			printk(KERN_ERR "Start DDR50 RX Tuning:\n");
		else if (mode == MODE_HS400 && flag==1)
			printk(KERN_ERR "Start HS400 RX Tuning:\n");
		else if(flag==1)
			printk(KERN_ERR "Start HS200 RX Tuning:\n ");

                for(i=0;i<range;i++) {
                        phase(emmc_port, 0xff, i);

			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
			udelay(1);
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

#ifdef DEBUG
                        printk("phase =0x%x \n", i);
#endif
			if (mode == MODE_HS200) {
				if(rtkemmc_send_cmd21(emmc_port, 128, 0x0) != 0)
					RX_window= RX_window&(~(1<<i));
				else
					RX_window= RX_window|((1<<i));
			}
			else {
				if(rtkemmc_send_cmd18(emmc_port, 1024, 0x100) != 0)
                                        RX_window= RX_window&(~(1<<i));
                                else
                                        RX_window= RX_window|((1<<i));
			}
                }
		RX_best = search_best(RX_window, range);
                if(flag==1)printk(KERN_ERR "RX_WINDOW = 0x%08x RX_best=0x%x\n", RX_window,RX_best);
                phase(emmc_port, 0xff, RX_best);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

		suspend_VP1 = RX_best;
        }

	if ((mode == MODE_HS400||mode == MODE_DDR) && emmc_port->tx_tuning) {
		TX1_window= TX_window;
		if(flag==1 && mode == MODE_HS400) printk(KERN_ERR "Start HS400 TX Tuning2:\n");
		else if(flag==1 && mode == MODE_DDR) printk(KERN_ERR "Start DDR50 TX Tuning2:\n");

                for(i=0;i<range;i++) {
			if(((TX_window>>i)&1)==1) {
				phase(emmc_port, i, 0xff);

				writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
				udelay(1);
				writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

#ifdef DEBUG
				printk("phase =0x%x \n", i);
#endif
				if(rtkemmc_send_cmd25(emmc_port, 1024,0xfe,0,NULL) != 0)
					TX1_window= TX1_window&(~(1<<i));
			}
		}
		TX1_best = search_best(TX1_window, range);
		if(flag==1)printk(KERN_ERR "TX1_WINDOW = 0x%08x TX1_best=0x%x\n", TX1_window,TX1_best);
                phase(emmc_port, TX1_best, 0xff);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

		suspend_VP0 = TX1_best;
        }
	sync(emmc_port);
}

static int mmc_Tuning_SDR50(struct rtkemmc_host *emmc_port)
{
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_SDR;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0x57, 0x1); //50Mhz

	if (pddrive_nf_s0[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s0[1], pddrive_nf_s0[2], pddrive_nf_s0[3], pddrive_nf_s0[4]);
	else {
		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);
	}
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xfffffffe, emmc_port->emmc_membase+EMMC_OTHER1);        //enable L4 gated after SDR50 finished

	sync(emmc_port);
	udelay(100);
	up_write(&cr_rw_sem);

#ifdef CONFIG_MMC_RTK_EMMC_PON  //we just write the fix value for fpga test, we will read the input from device tree after negotiate with android team later
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 1);
#else
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 0);      //currently, we disable command queue first, offset = 256x1024x1024/512/2048x512x5
#endif
#endif

	return 0;
}

static int mmc_Tuning_DDR50(struct rtkemmc_host *emmc_port, u32 mode)
{
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_DDR;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0x57, 0x1);  //50MMhz
	sync(emmc_port);
	udelay(100);
	if (pddrive_nf_s1[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s1[1], pddrive_nf_s1[2], pddrive_nf_s1[3], pddrive_nf_s1[4]);
        else {
		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);
	}
	if(emmc_port->tx_tuning && emmc_port->rx_tuning) {	//device tree set kernel tuning for DDR50
		rtkemmc_phase_tuning(emmc_port,mode,1);
		sync(emmc_port);
		mdelay(10);
	}
	else {
		phase(emmc_port, 0x8, 0x9);

		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

	}
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xfffffffe, emmc_port->emmc_membase+EMMC_OTHER1);        //enable L4 gated after DDR50 finished
	up_write(&cr_rw_sem);
#ifdef CONFIG_MMC_RTK_EMMC_PON  //we just write the fix value for fpga test, we will read the input from device tree after negotiate with android team later
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 1);
#else
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 0);      //currently, we disable command queue first, offset = 256x1024x1024/512/2048x512x5
#endif
#endif
	return 0;
}

static int mmc_Tuning_HS200(struct rtkemmc_host *emmc_port,u32 mode)
{
	MMCPRINTF("%s \n", __func__);

	down_write(&cr_rw_sem);
        if (!g_bResuming)
                gCurrentBootMode = MODE_HS200;
        MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0xa6, 0x0); //200Mhz

	if (pddrive_nf_s2[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s2[1], pddrive_nf_s2[2], pddrive_nf_s2[3], pddrive_nf_s2[4]);
	else {
		rtkemmc_set_pad_driving(emmc_port,0x4, 0x4, 0x4, 0x4);
	}

	rtkemmc_phase_tuning(emmc_port,mode,1);

	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xfffffffe, emmc_port->emmc_membase+EMMC_OTHER1);        //enable L4 gated after HS200 finished

	sync(emmc_port);
	mdelay(10);
	up_write(&cr_rw_sem);

	printk(KERN_ERR "HS200: final phase=0x%x\n", readl(emmc_port->crt_membase + SYS_PLL_EMMC1));

#ifdef CONFIG_MMC_RTK_EMMC_PON  //we just write the fix value for fpga test, we will read the input from device tree after negotiate with android team later
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 1);
#else
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 0);      //currently, we disable command queue first, offset = 256x1024x1024/512/2048x512x5
#endif
#endif
	return 0;
}

static int mmc_Tuning_HS400(struct rtkemmc_host *emmc_port,u32 mode)
{
        MMCPRINTF("%s \n", __func__);
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_HS400;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0xa6, 0x0); //200Mhz

	if (pddrive_nf_s3[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s3[1], pddrive_nf_s3[2], pddrive_nf_s3[3], pddrive_nf_s3[4]);
	else {
		rtkemmc_set_pad_driving(emmc_port,0x7, 0x2, 0x3, 0x0);
	}
	rtkemmc_phase_tuning(emmc_port,mode,1);

	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xfffffffe, emmc_port->emmc_membase+EMMC_OTHER1);        //enable L4 gated after HS400 finished

	sync(emmc_port);
	mdelay(10);
	up_write(&cr_rw_sem);
	printk(KERN_ERR "HS400 first stage: final phase=0x%x\n", readl(emmc_port->crt_membase + SYS_PLL_EMMC1));

	return 0;
}

static int rtkemmc_execute_tuning(struct mmc_host *host, u32 opcode)
{
	struct rtkemmc_host *emmc_port;
	struct sd_cmd_pkt cmd_info;
	MMCPRINTF("%s \n", __func__);

	emmc_port = mmc_priv(host);
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	cmd_info.emmc_port = emmc_port;

	if (host->card){
		printk(KERN_INFO "emmc card manid = 0x%08x\n", host->card->cid.manfid);
		if (host->card->cid.manfid == 0x13) //micron manfid
			emmc_port->rx_tuning = 1; //micron: force to turn on rx tuning
	}
	else
		printk(KERN_ERR "host->card is null! \n");

	MMCPRINTF("rtkemmc_execute_tuning : opcode=0x%08x, mode=0x%08x\n",opcode,host->mode);

	g_bTuning = 1;
	switch(host->mode)
	{
	case MODE_SDR:
		mmc_Tuning_SDR50(emmc_port);
		set_RTK_initial_flag(1);
		break;
	case MODE_DDR:
		mmc_Tuning_DDR50(emmc_port, host->mode);
		set_RTK_initial_flag(1);
		break;
	case MODE_HS200:
		mmc_Tuning_HS200(emmc_port,host->mode);
		set_RTK_initial_flag(1);
		break;
	case MODE_HS400:
		mmc_Tuning_HS400(emmc_port,host->mode);		//hs400 still have dqs tuning, so set flag as 1 after dqs tuning
		break;
	default:
		set_RTK_initial_flag(1);        //this flag is to use for sd card check for rcu stall
		break;
	}

	g_bTuning = 0;
	return 0;
}

static int rw_test_tuning(struct rtkemmc_host *emmc_port,unsigned long emmc_blk_addr)
{
	int i;
	rtkemmc_send_cmd25(emmc_port,DMA_ALLOC_LENGTH, emmc_blk_addr,0, NULL);
#ifdef SHA256
	MCP_SHA256((unsigned char *)emmc_port->dma_paddr, (unsigned char *)compare3_phy_addr, DMA_ALLOC_LENGTH, NULL);
#else
	memcpy(compare1, gddr_dma_org, DMA_ALLOC_LENGTH);
#endif
	rtkemmc_send_cmd18(emmc_port,DMA_ALLOC_LENGTH, emmc_blk_addr);
#ifdef SHA256
	MCP_SHA256((unsigned char *)emmc_port->dma_paddr, (unsigned char *)compare4_phy_addr, DMA_ALLOC_LENGTH, NULL);
#else
	memcpy(compare2, gddr_dma_org, DMA_ALLOC_LENGTH);
#endif

#ifdef SHA256
	for(i=0;i<32;i++) {
		if(compare3[i]!=compare4[i]) {
			return 1;
		}
	}
#else
	for(i=0;i<DMA_ALLOC_LENGTH;i++) {
		if(compare1[i]!=compare2[i]) {
			return 1;
		}
	}
#endif
	return 0;
}

static void rtkemmc_dqs_tuning(struct mmc_host *host)
{
	int i=0, j=0;
	struct rtkemmc_host *emmc_port;
	unsigned long emmc_real_size=0;
	unsigned long emmc_set_size=0;
	unsigned long dqs_tuning_blk_addr=0;
	int retry_count=0;
	unsigned int bitmap=0;
	unsigned int max=0;

	int hs400_data[128]={0};        //4 bytes header, 33aa, 4 bytes for TX, 4 bytes for RX, 4 bytes for dqs

        emmc_port = mmc_priv(host);
	mdelay(2);

	if(suspend == 1)
	{
		if(emmc_port->dqs_tuning == 1) {
			//writel(0x80 | suspend_dqs,emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
			rtkemmc_dqs_delay_tap(emmc_port, suspend_dqs);
		}
		else {
			//writel(0x80 | dqs_saved, emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
			rtkemmc_dqs_delay_tap(emmc_port, dqs_saved);
		}
                printk(KERN_ERR "suspend/resume: restore DQS=0x%x\n", readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
		suspend = 0;
		return;
	}

#ifdef DQS_INHERITED
        if(emmc_port->dqs_tuning == 0) {
		//writel(0x80 | dqs_saved, emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		rtkemmc_dqs_delay_tap(emmc_port, dqs_saved);
		printk(KERN_ERR "Inherit bootcode dqs: DQS=0x%x\n", readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
		printk(KERN_ERR "read/write test for inherit hs400 parameter...\n");
		if( rw_test_tuning(emmc_port, (emmc_port->emmc_tuning_addr/512))==0) {
			printk(KERN_ERR "read/write test success for hs400 parameter!!!\n");
			set_RTK_initial_flag(1);
			return;
		}
		else {
			emmc_port->dqs_tuning=1;
			emmc_port->tx_tuning = 1;
			emmc_port->rx_tuning = 1;
			printk(KERN_ERR "read/write test failed, retune the hs400...\n");
		}
	}
#endif

	down_write(&cr_rw_sem);
	g_bTuning = 1;

	if(emmc_port->emmc_tuning_addr==0) {	//using original MBR mode
		emmc_real_size = host->card->ext_csd.sectors;
		if(emmc_real_size > 0x2200000 )    //32gb
			emmc_set_size = 0x3900000;
		else if( (emmc_real_size > 0x1200000) && (emmc_real_size < 0x2200000) ) //16gb
			emmc_set_size = 0x1c80000;
		else if( (emmc_real_size > 0xb40000) && (emmc_real_size < 0x1200000) )  //8gb
			emmc_set_size = 0xe40000;
		else
			emmc_set_size = 0x720000;     //4gb

		if(emmc_real_size-emmc_set_size>0x800) {
			dqs_tuning_blk_addr = emmc_set_size;	//non-used emmc space
		}
		else {
			dqs_tuning_blk_addr = 0x26880;	//evaluated free space
		}
		printk(KERN_ERR "MBR mode: emmc_real_blk_size=0x%lx, emmc_set_blk_size=0x%lx, dqs_tuning_blk_addr=0x%lx\n",
				emmc_real_size,emmc_set_size,dqs_tuning_blk_addr);
	}
	else {	//using GPT partition mode for eMMC after android O
		dqs_tuning_blk_addr = emmc_port->emmc_tuning_addr / 512;	//convert from offset to block address
		printk(KERN_ERR "GPT mode: emmc_port->emmc_tuning_addr = 0x%lx, dqs_tuning_blk_addr = 0x%lx\n",
				emmc_port->emmc_tuning_addr, dqs_tuning_blk_addr);
	}

#ifdef SHA256
	printk(KERN_ERR "[EMMC] SHA256 is enabled for dqs comparison!!!\n");
	if(!compare3)
		compare3 = dma_alloc_coherent(emmc_port->dev, 32, &compare3_phy_addr ,GFP_KERNEL);
	if(!compare4)
		compare4 = dma_alloc_coherent(emmc_port->dev, 32, &compare4_phy_addr ,GFP_KERNEL);
#endif
retry:
	for(i=0; i<0x20; i++) {
		if(j>=5)			//must be more than 5 continuous tap sample point
			max = j;
		if(j==0 && max!=0)	//find the max tap length
			break;
#ifdef RTKEMMC_DEBUG
		printk(KERN_ERR "DQS windows tuning: i=0x%x\n",i<<1);
#endif
		//writel(0x80|(i<<1),emmc_port->emmc_membase + EMMC_DQS_CTRL1);
		rtkemmc_dqs_delay_tap(emmc_port, (i<<1));
		rtkemmc_phase_tuning(emmc_port,MODE_HS400,0);
		if( rw_test_tuning(emmc_port, dqs_tuning_blk_addr)==0) {
			j++;
			bitmap |= (1<<i);
		}
		else {
			j=0;
		}
	}
	if(max==0) {
		if((++retry_count)<5) {
                        printk(KERN_ERR "DQS_RETRY: dqs tap bitmap= 0x%x, retry: %d\n", bitmap, retry_count);
                        sync(emmc_port);
                        mdelay(10);
                        goto retry;
                }
                else {
                        printk(KERN_ERR RED_BOLD"Cannot find a proper dqs window..., dqs tap bitmap= 0x%x\n"RESET, bitmap);
                }

		//writel(0x88,emmc_port->emmc_membase + EMMC_DQS_CTRL1);
		rtkemmc_dqs_delay_tap(emmc_port, 0x8);
	}
	else {
		//writel(0x80|(readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1)-((max/2)*2)),emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		rtkemmc_dqs_delay_tap(emmc_port, (readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1)-((max/2)*2)));
		suspend_dqs = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
		printk(KERN_ERR "max sample point=%d, bitmap=0x%x, DQS=0x%x\n", max, bitmap, readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
		rtkemmc_phase_tuning(emmc_port,MODE_HS400,1);
		printk(KERN_ERR "HS400: final phase=0x%x\n", readl(emmc_port->crt_membase + SYS_PLL_EMMC1));
	}
#ifdef SHA256
	if(compare3)
		dma_free_coherent(emmc_port->dev, 32, compare3 , compare3_phy_addr);
	if(compare4)
		dma_free_coherent(emmc_port->dev, 32, compare4 , compare4_phy_addr);
#endif
        sync(emmc_port);
        mdelay(10);
	g_bTuning = 0;

	printk(KERN_ERR "save eMMC hs400 parameter to emmc dqs_tuning_blk_addr 0x%lx\n", emmc_port->emmc_tuning_addr);
	hs400_data[0] = 0x33aa;
	hs400_data[1] = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x000000f8) >> 3;
	hs400_data[2] = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x00001f00) >> 8;
	hs400_data[3] = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
	printk(KERN_ERR "hs400 parameter: hs400_TX[1]=0x%x, hs400_RX[2]=0x%x,hs400_dqs[3]=0x%x\n",hs400_data[1],hs400_data[2],hs400_data[3]);
	rtkemmc_send_cmd25(emmc_port, 512, emmc_port->emmc_tuning_addr/512-1024, 1, hs400_data);

	up_write(&cr_rw_sem);

#ifdef CONFIG_MMC_RTK_EMMC_PON  //we just write the fix value for fpga test, we will read the input from device tree after negotiate with android team later
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 1);
#else
	pon_initial(emmc_port, emmc_port->pon_addr, emmc_port->pon_addr+((256*2*1024)/4*5),0x00232223, 0);      //currently, we disable command queue first, offset = 256x1024x1024/512/2048x512x5
#endif
#endif
	set_RTK_initial_flag(1);        //this flag is to use for sd card check for rcu stall
}

static u32 rtkemmc_get_cmd_timeout(struct sd_cmd_pkt *cmd_info)
{
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;
	u16 block_count = cmd_info->block_count;
	u32 tmout = 0;

	MMCPRINTF("\n");

	if(cmd_info->cmd->data) {
		tmout = msecs_to_jiffies(200);

		if(block_count>0x100)
			tmout = tmout + 100 * msecs_to_jiffies(block_count);
    	}
	else
		tmout = msecs_to_jiffies(80);

#ifdef CONFIG_ANDROID
	tmout += msecs_to_jiffies(100);
#endif

	cmd_info->timeout = emmc_port->tmout = tmout;

	return 0;
}

static void rtkemmc_set_ios(struct mmc_host *host, struct mmc_ios *ios)
{
	struct rtkemmc_host *emmc_port;
	u32 cur_timing = 0;
	unsigned long flags;

	emmc_port = mmc_priv(host);

	MMCPRINTF(KERN_INFO "ios->bus_mode = %u\n",ios->bus_mode);
	MMCPRINTF(KERN_INFO "ios->clock = %u\n",ios->clock);
	MMCPRINTF(KERN_INFO "ios->bus_width = %u\n",ios->bus_width);
	MMCPRINTF(KERN_INFO "ios->timing = %u\n",ios->timing);
#ifdef CONFIG_MMC_RTK_EMMC_PON
	if(ios->bus_mode==MMC_BUSMODE_PUSHPULL && ios->bus_width == MMC_BUS_WIDTH_1 && ios->timing == MMC_TIMING_LEGACY) {
		return;
	}
#endif
	cur_timing = ios->timing;
	if (ios->clock == MMC_HIGH_52_MAX_DTR)
		cur_timing = MMC_TIMING_MMC_HS;

	MMCPRINTF(KERN_INFO "cur_timing = %u\n",cur_timing);

	if (!g_bResuming) {
		switch(cur_timing)
		{
		case MMC_TIMING_MMC_HS400:
			rtkemmc_set_freq(emmc_port,0xa6, 0x0);  //200MHZ
			isb();
			sync(emmc_port);
			rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xfb)|EMMC_HIGH_SPEED_EN,emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);
			rtkemmc_writew((readw(emmc_port->emmc_membase + EMMC_HOST_CTRL2_R)&0xfff8)|MODE_HS400 ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R); //enable HS400
			isb();
			sync(emmc_port);
			break;
		case MMC_TIMING_MMC_HS200:
			rtkemmc_set_freq(emmc_port,0xa6, 0x0);  //200MHZ
			rtkemmc_writew((readw(emmc_port->emmc_membase + EMMC_HOST_CTRL2_R)&0xfff8)|MODE_HS200 ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R);
			break;
		case MMC_TIMING_MMC_DDR52:
			rtkemmc_set_freq(emmc_port,0x57, 0x1);  //50MB
			rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xfb)|EMMC_HIGH_SPEED_EN,emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);
			rtkemmc_writew((readw(emmc_port->emmc_membase + EMMC_HOST_CTRL2_R)&0xfff8)|MODE_DDR ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R);
			break;
		case MMC_TIMING_MMC_HS:
			rtkemmc_set_freq(emmc_port,0x57, 0x1);  //50Mhz
			rtkemmc_writew((readw(emmc_port->emmc_membase + EMMC_HOST_CTRL2_R)&0xfff8)|MODE_SDR ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R);
			break;
		case MMC_TIMING_LEGACY:
			rtkemmc_set_freq(emmc_port,0x46, 0x80);  //80Mhz
			rtkemmc_writew((readw(emmc_port->emmc_membase + EMMC_HOST_CTRL2_R)&0xfff8)|MODE_LEGACY ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R);
			break;
		default:
			printk(KERN_INFO "%s: cur_timing = %u \n", __FILE__, cur_timing);
			break;
		}
	}

	if (ios->bus_width == MMC_BUS_WIDTH_8){
		spin_lock_irqsave(&emmc_port->lock,flags);
		rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xdf)|EMMC_BUS_WIDTH_8,emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);
		sync(emmc_port);
		spin_unlock_irqrestore(&emmc_port->lock, flags);

		printk(KERN_INFO "%s: set bus width 8, 0x98012028=%08x\n", DRIVER_NAME, readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R));

		if (cur_timing == MMC_TIMING_MMC_HS400) {
			rtkemmc_writel(0x88 ,emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap, this setting will not take effect in hank A00

			rtkemmc_writel(0x80|emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL0); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL1); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL2); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL3); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL4); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL5); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL6); //dqs dly tap
			rtkemmc_writel(emmc_port->dqs_dly_tape, emmc_port->emmc_membase+EMMC_RDQ_CTRL7); //dqs dly tap
			rtkemmc_writel(0xff00, emmc_port->emmc_membase+EMMC_DQ_CTRL_SET); //dqs dly tap

			isb();
			sync(emmc_port);
		}
	} else if (ios->bus_width == MMC_BUS_WIDTH_4){
		spin_lock_irqsave(&emmc_port->lock,flags);
                rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xdd)|EMMC_BUS_WIDTH_4,emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);
                sync(emmc_port);
                spin_unlock_irqrestore(&emmc_port->lock, flags);

                printk(KERN_INFO "%s: set bus width 4, 0x98012028=%08x\n", DRIVER_NAME, readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R));
	}
}

void rtkemmc_chk_param(u32 *pparam, u32 len, u8 *ptr)
{
	u32 value,i;
	mmcrtk("\n");

	*pparam = 0;
	for(i=0;i<len;i++){
		value = ptr[i] - '0';
		// KWarning: checked ok by alexkh@realtek.com
		if((value >= 0) && (value <=9))
		{
			*pparam+=value<<(4*(len-1-i));
			continue;
		}

		value = ptr[i] - 'a';
		// KWarning: checked ok by alexkh@realtek.com
		if((value >= 0) && (value <=5))
		{
			value+=10;
			*pparam+=value<<(4*(len-1-i));
			continue;
		}

		value = ptr[i] - 'A';
		// KWarning: checked ok by alexkh@realtek.com
		if((value >= 0) && (value <=5))
		{
			value+=10;
			*pparam+=value<<(4*(len-1-i));
			continue;
		}
	}
}

void rtk_op_complete(struct rtkemmc_host *emmc_port)
{
	struct completion *waiting = emmc_port->int_waiting;
	if (emmc_port->int_waiting) {
		MMCPRINTF("int wait complete 1\n");
		MMCPRINTF("rtk_op_complete: rtk wait complete addr = %08x\n", (unsigned int) emmc_port->int_waiting);
		//emmc_port->int_waiting = NULL;
		complete(waiting);
		MMCPRINTF("int wait complete 2\n");
	}
	else
		MMCPRINTF("int wait not complete\n");
}

static void rtkemmc_req_end_tasklet(unsigned long param)
{
	struct rtkemmc_host *emmc_port;
	struct mmc_request* mrq;
	unsigned long flags;
	MMCPRINTF("%s \n", __func__);

	emmc_port = (struct rtkemmc_host *)param;
	spin_lock_irqsave(&emmc_port->lock,flags);

	mrq = emmc_port->mrq;
	emmc_port->mrq = NULL;

	spin_unlock_irqrestore(&emmc_port->lock, flags);

	mmc_request_done(emmc_port->mmc, mrq);
}

static int rtkemmc_free_dma_buf(struct rtkemmc_host *emmc_port)
{
	if (gddr_descriptor_org)
		dma_free_coherent(emmc_port->dev, DESC_ALLOC_LENGTH, gddr_descriptor_org ,emmc_port->desc_paddr);
	MMCPRINTF("free rtk desc buf \n");

	if (gddr_dma_org)
		dma_free_coherent(emmc_port->dev, DMA_ALLOC_LENGTH, gddr_dma_org ,emmc_port->dma_paddr);
	MMCPRINTF("free rtk dma buf \n");

	return 1;
}

static int rtkemmc_allocate_dma_buf(struct rtkemmc_host *emmc_port, struct mmc_command *cmd)
{
	if (!gddr_descriptor)
		gddr_descriptor_org = gddr_descriptor = dma_alloc_coherent(emmc_port->dev, DESC_ALLOC_LENGTH, &emmc_port->desc_paddr ,GFP_KERNEL);

	if (!gddr_dma)
		gddr_dma_org = gddr_dma = dma_alloc_coherent(emmc_port->dev, DMA_ALLOC_LENGTH, &emmc_port->dma_paddr ,GFP_KERNEL);

	if(!gddr_dma || !gddr_descriptor){
		WARN_ON(1);
		cmd->error = -ENOMEM;
		return 0;
	}

	MMCPRINTF("allocate rtk dma buf : dma addr=0x%016llx, phy addr=0x%08x\n", gddr_dma, emmc_port->dma_paddr);
	MMCPRINTF("allocate rtk desc buf : desc addr=0x%016llx, phy addr=0x%08x\n", gddr_descriptor, emmc_port->desc_paddr);
	return 1;
}

static int wait_done_timeout(struct rtkemmc_host *emmc_port, volatile u32 *addr, u32 mask, u32 value, const char *string)
{
	int n = 0;
	while(1)
	{
		if (((*addr) &mask) == value){
			break;
                }

		if((readw(emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R) & 0x8000)!=0) {
			break;
		}

		if(n++ > 3000000) {
			printk(KERN_ERR "Timeout!!! cmd_opcode=%d, cmd_arg=%x, addr=%p, mask=%x, value=%x, emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R=%x \
					emmc_port->emmc_membase + EMMC_ERROR_INT_STA_R=%x, pre_func=%s\n",
				emmc_port->cmd_opcode, readl(emmc_port->emmc_membase+EMMC_ARGUMENT_R), addr, mask, value,
				readw(emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R), readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R),string);
			printk(KERN_ERR "RESP01=0x%x, RESP23=0x%x, RESP45=0x%x, RESP67=0x%x",
				readl(emmc_port->emmc_membase + EMMC_RESP01_R),
				readl(emmc_port->emmc_membase + EMMC_RESP23_R),
				readl(emmc_port->emmc_membase + EMMC_RESP45_R),
				readl(emmc_port->emmc_membase + EMMC_RESP67_R));
			print_err_reg(emmc_port->cmd_opcode, emmc_port->normal_interrupt, emmc_port->error_interrupt);
                        print_ip_desc(emmc_port);
                        print_reg_info(emmc_port);
			return -1;
		}
		udelay(1);
		sync(emmc_port);
	}
	return 0;
}

void rtkemmc_set_pad_driving(struct rtkemmc_host *emmc_port, u32 clk_drv, u32 cmd_drv, u32 data_drv, u32 ds_drv)
{
	rtkemmc_writel((readl(emmc_port->mux_mis_membase + EMMC_ISO_pfunc1)&0xff03f03f)|(clk_drv<<6)|(clk_drv<<9)|(cmd_drv<<18)|(cmd_drv<<21),
				emmc_port->mux_mis_membase + EMMC_ISO_pfunc1);
	rtkemmc_writel((readl(emmc_port->mux_mis_membase + EMMC_ISO_pfunc2)&0xff03f03f)|(data_drv<<6)|(data_drv<<9)|(data_drv<<18)|(data_drv<<21),
				emmc_port->mux_mis_membase + EMMC_ISO_pfunc2);
	rtkemmc_writel((readl(emmc_port->mux_mis_membase + EMMC_ISO_pfunc3)&0xff03f03f)|(data_drv<<6)|(data_drv<<9)|(data_drv<<18)|(data_drv<<21),
				emmc_port->mux_mis_membase + EMMC_ISO_pfunc3);
	rtkemmc_writel((readl(emmc_port->mux_mis_membase + EMMC_ISO_pfunc4)&0xff03f03f)|(data_drv<<6)|(data_drv<<9)|(data_drv<<18)|(data_drv<<21),
				emmc_port->mux_mis_membase + EMMC_ISO_pfunc4);
	rtkemmc_writel((readl(emmc_port->mux_mis_membase + EMMC_ISO_pfunc5)&0xff03f03f)|(data_drv<<6)|(data_drv<<9)|(data_drv<<18)|(data_drv<<21),
                                emmc_port->mux_mis_membase + EMMC_ISO_pfunc5);
	isb();
	sync(emmc_port);
}

void phase(struct rtkemmc_host *emmc_port, u32 VP0, u32 VP1)
{
	//phase selection
	if( (VP0==0xff) & (VP1==0xff)){
#ifdef DEBUG
		printk("phase VP0 and VP1 no change \n");
#endif
	}
	else if( (VP0!=0xff) & (VP1==0xff)) {
#ifdef DEBUG
		printk("phase VP0=%x, VP1 no change \n", VP0);
#endif
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000), emmc_port->emmc_membase + EMMC_CKGEN_CTL);    //change clock to 4MHz

		sync(emmc_port);
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd), emmc_port->crt_membase + SYS_PLL_EMMC1);     //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffff07)|(VP0<<3), emmc_port->crt_membase + SYS_PLL_EMMC1);    //vp0 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2), emmc_port->crt_membase + SYS_PLL_EMMC1);    //release reset pll
		sync(emmc_port);
		udelay(200);

		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff), emmc_port->emmc_membase + EMMC_CKGEN_CTL); //change clock to PLL
		sync(emmc_port);
	}
	else if( (VP0==0xff) & (VP1!=0xff)){
#ifdef DEBUG
		printk("phase VP0 no change, VP1=%x \n", VP1);
#endif
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000), emmc_port->emmc_membase + EMMC_CKGEN_CTL);    //change clock to 4MHz
		sync(emmc_port);

		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd), emmc_port->crt_membase + SYS_PLL_EMMC1);     //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffe0ff)|(VP1<<8), emmc_port->crt_membase + SYS_PLL_EMMC1);    //vp1 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2), emmc_port->crt_membase + SYS_PLL_EMMC1);    //release reset pll
		sync(emmc_port);
		udelay(200);

		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff),emmc_port->emmc_membase + EMMC_CKGEN_CTL);  //change clock to PLL
		sync(emmc_port);
	}
        else{
#ifdef DEBUG
		printk("phase VP0=%x, VP1=%x \n", VP0, VP1);
#endif
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000),emmc_port->emmc_membase + EMMC_CKGEN_CTL);     //change clock to 4MHz
		sync(emmc_port);

		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd),emmc_port->crt_membase + SYS_PLL_EMMC1);      //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffff07)|(VP0<<3),emmc_port->crt_membase + SYS_PLL_EMMC1);     //vp0 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffe0ff)|(VP1<<8),emmc_port->crt_membase + SYS_PLL_EMMC1);     //vp1 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2),emmc_port->crt_membase + SYS_PLL_EMMC1);     //release reset pll
		sync(emmc_port);
		udelay(200);

                rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff),emmc_port->emmc_membase + EMMC_CKGEN_CTL);  //change clock to PLL
		sync(emmc_port);
	}
#ifdef RTKEMMC_DEBUG
	printk(KERN_ERR "%s: phase adjust - EMMC_CKGEN_CTL=0x%08x, PLL_EMMC1=%08x, PLL_EMMC2=%08x, PLL_EMMC3=%08x, PLL_EMMC4=%08x\n",
		DRIVER_NAME,
		readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC4));
#endif
}

static void rtkemmc_set_freq(struct rtkemmc_host *emmc_port, u32 freq, u32 div_ip)
{
	u32 tmp_val=0;
	unsigned long flags;

	spin_lock_irqsave(&emmc_port->lock,flags);
#if 0
	clk_disable_unprepare(clk_en_emmc_ip);
	isb();
	sync(emmc_port);
#endif
	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC4) & 0x06);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC4);
	isb();
	sync(emmc_port);

	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC3) & 0xffff)|(freq<<16);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC3);
	isb();
	sync(emmc_port);

	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC4) | 0x01);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC4);
	isb();
	sync(emmc_port);
#if 0
	clk_prepare_enable(clk_en_emmc_ip);
	isb();
	sync(emmc_port);

	udelay(100);
        rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL) & 0xffff, emmc_port->emmc_membase+EMMC_CKGEN_CTL); //change to PLL
        sync(emmc_port);
#endif

	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_DUMMY_SYS)|0x00400000, emmc_port->emmc_membase+EMMC_DUMMY_SYS); //reset counter
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL)&0xfffffe00, emmc_port->emmc_membase+EMMC_CKGEN_CTL); //reset to the initial value
	if(div_ip!=0) {
		rtkemmc_writel((readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL)&0xfffff00|div_ip|0x100), emmc_port->emmc_membase+EMMC_CKGEN_CTL); //set the enable bit
	}
//	phase(emmc_port, 0, 0);

	rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd), emmc_port->crt_membase + SYS_PLL_EMMC1);     //reset pll
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_DUMMY_SYS)&0xffbfffff, emmc_port->emmc_membase+EMMC_DUMMY_SYS); //reset counter
	rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2), emmc_port->crt_membase + SYS_PLL_EMMC1);    //release reset pll

	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_PLL_STATUS), 0x1, 0x1, __func__);

	rtkemmc_writeb(0x06, emmc_port->emmc_membase + EMMC_SW_RST_R);      //9801202f, Software Reset Register

        sync(emmc_port);
	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), 0x6<<24, 0x0, __func__);

	printk(KERN_ERR "%s: emmc_port->emmc_membase+EMMC_CKGEN_CTL = 0x%x\n",__func__, readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL));
	spin_unlock_irqrestore(&emmc_port->lock, flags);

	printk(KERN_INFO "%s: div_ip=0x%08x, PLL_EMMC1=%08x, PLL_EMMC2=%08x, PLL_EMMC3=%08x, PLL_EMMC4=%08x\n",
		DRIVER_NAME,
		readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC4));
}

void rtkemmc_speed_up(void)
{
	struct mmc_host * mmc = mmc_host_local;
	struct rtkemmc_host *emmc_port;

	emmc_port = mmc_priv(mmc);

	rtkemmc_set_freq(emmc_port,0x46, 0x4);  //80Mhz
}
EXPORT_SYMBOL(rtkemmc_speed_up);

static u32 rtkemmc_chk_cmdcode(struct mmc_command* cmd)
{
	u32 cmdcode;

	if(cmd->opcode <= 56){
		cmdcode = (u32)rtk_sd_cmdcode[cmd->opcode];
		WARN_ON(cmd->data == NULL);
		if(cmd->data->flags & MMC_DATA_WRITE){
			if(cmd->opcode == 42)
				cmdcode = EMMC_NORMALWRITE;
			else if(cmd->opcode == 56)
				cmdcode = EMMC_AUTOWRITE2;
		}
	}else
		cmdcode = EMMC_CMD_UNKNOW;

	return cmdcode;
}

static void rtkemmc_set_pin_mux(struct rtkemmc_host *emmc_port)
{
	MMCPRINTF("rtkemmc_set_pin_mux \n");
	
	rtkemmc_writel((readl(emmc_port->mux_mis_membase)&0xff000000)|0x00aaaaaa, emmc_port->mux_mis_membase); //pad mux
	sync(emmc_port);
}

static void rtkemmc_timeout_timer(unsigned long data)
{
	struct rtkemmc_host *emmc_port;
	unsigned long flags;

	emmc_port = (struct rtkemmc_host *)data;
	printk(KERN_ERR "rtkemmc_timeout_timer fired ...\n");
	MMCPRINTF("%s - int_wait=%08x\n", __func__, emmc_port->int_waiting);
    
	spin_lock_irqsave(&emmc_port->lock,flags);
	//down_write(&cr_rw_sem);
	if(emmc_port->int_waiting)
	{
		MMCPRINTF("1. get sd trans \n");
		MMCPRINTF("========== C1 ==========\n");
		rtkemmc_hold_int_dec();
                rtkemmc_get_int_sta(&emmc_port->normal_interrupt, &emmc_port->error_interrupt);
		sync(emmc_port);
		MMCPRINTF("normal_interrupt =%08x, error_interrupt=0x%08x, int_waiting=%08x\n", emmc_port->normal_interrupt, emmc_port->error_interrupt, emmc_port->int_waiting);
	}
	else {
		WARN_ON(1);
	}

	if(emmc_port->int_waiting)
		rtk_op_complete(emmc_port);

	spin_unlock_irqrestore(&emmc_port->lock, flags);
	//up_write(&cr_rw_sem);
}

static irqreturn_t rtkemmc_irq(int irq, void *dev)
{
	struct rtkemmc_host *emmc_port = dev;
	int irq_handled = 0;

	rtkemmc_get_int_sta(&emmc_port->normal_interrupt, &emmc_port->error_interrupt);
	sync(emmc_port);

#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(emmc_port->mmc);
#endif

#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	if(cq_host->enabled==false)	//in command queue mode, this flag will be set after cmdq mode enable
		rtkemmc_hold_int_dec();
#else
	rtkemmc_hold_int_dec();
#endif

#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
	if(cq_host->enabled) {	//if we run the cmdq mode currently
		u32 status;
		unsigned long comp_status;
		unsigned long tag = 0;

		status = readl(emmc_port->emmc_membase+ EMMC_CQIS);

		if(emmc_port->normal_interrupt&0x8000) {
                                printk(KERN_ERR "%s: cmdq error case: cpuid=%d, normal_interrupt =%08x, error_interrupt=0x%08x, EMMC_CQIS=0x%x, EMMC_CQTCN=0x%x\n",
                                        __func__, raw_smp_processor_id(), emmc_port->normal_interrupt, emmc_port->error_interrupt, status, readl(emmc_port->emmc_membase+EMMC_CQTCN));
                                rtkemmc_cmdq_dumpregs(emmc_port);
                }

		if (status & EMMC_CQIS_TCC) {
			/* read QCTCN and complete the request */
			comp_status = readl(emmc_port->emmc_membase+EMMC_CQTCN);
#ifdef RTKEMMC_DEBUG
			printk(KERN_ERR "%s_cmdq: cpuid=%d, normal_interrupt =%08x, error_interrupt=0x%08x, EMMC_CQIS=0x%x, EMMC_CQTCN=0x%x\n",
				__func__, raw_smp_processor_id(), emmc_port->normal_interrupt, emmc_port->error_interrupt, status, comp_status);
#endif
			if (!comp_status)
				goto out;

			for_each_set_bit(tag, &comp_status, cq_host->num_slots) {
#ifdef CONFIG_MMC_RTK_EMMC_PON
				if(tag!=0) {
#endif
#ifdef RTKEMMC_DEBUG
					/* complete the corresponding mrq */
					printk(KERN_ERR "%s_cmdq: cpuid=%d, completing tag -> %lu\n", __func__, raw_smp_processor_id(), tag);
#endif

					rtkemmc_cmdq_finish_data(emmc_port->mmc, tag);

                                        if(tag==31 && DCMD_idx==MMC_ERASE) {
						DCMD_wait_38 = false;
#ifdef CONFIG_MMC_RTK_EMMC_PON
                                                //printk(KERN_INFO "DCMD cmd is %d, release the HW semaphore\n", DCMD_idx);
						rtkemmc_writel(0x0, emmc_port->emmc_membase+EMMC_HD_SEM);
#endif
                                        }
					if(tag==31) DCMD_complete = true;
#ifdef CONFIG_MMC_RTK_EMMC_PON
				}
#endif
			}
			rtkemmc_writel(comp_status, emmc_port->emmc_membase+EMMC_CQTCN);
			rtkemmc_writel(status, emmc_port->emmc_membase+ EMMC_CQIS);
			rtkemmc_clr_int_sta();	//clear 0x2030 status
		}

		if (status & EMMC_CQIS_RED) {
			/* task response has an error */
			printk(KERN_ERR "%s: RED error %d !!!\n", mmc_hostname(emmc_port->mmc), status);
			rtkemmc_writel(status, emmc_port->emmc_membase+ EMMC_CQIS);
			rtkemmc_clr_int_sta();  //clear 0x2030 status
			rtkemmc_cmdq_dumpregs(emmc_port);
		}

		if (status & EMMC_CQIS_HAC) {
#ifdef RTKEMMC_DEBUG
			printk(KERN_ERR "%s: halt irq case\n", __func__);
			printk(KERN_ERR "%s_cmdq: cpuid=%d, normal_interrupt =%08x, error_interrupt=0x%08x, EMMC_CQIS=0x%x\n",
                                __func__, raw_smp_processor_id(), emmc_port->normal_interrupt, emmc_port->error_interrupt, status);
#endif
			/* halt is completed, wakeup waiting thread */
			rtkemmc_writel(status, emmc_port->emmc_membase+ EMMC_CQIS);
			rtkemmc_clr_int_sta();  //clear 0x2030 status
			complete(&cq_host->halt_comp);
		}

out:
		return IRQ_HANDLED;
	}
#endif

#ifdef RTKEMMC_DEBUG
	printk(KERN_ERR "%s_legacy: cpuid=%d, cmd_idx=%d, normal_interrupt =%08x, error_interrupt=0x%08x\n",
			__func__, raw_smp_processor_id(), emmc_port->cmd_opcode, emmc_port->normal_interrupt, emmc_port->error_interrupt);
#endif

	if(emmc_port->int_waiting) {
		MMCPRINTF("int wait clear 1\n");
		del_timer(&emmc_port->timer);
		if (g_bResuming) //avoid to emit complete in rtkemmc_resume
			return IRQ_HANDLED;

		rtk_op_complete(emmc_port);
		MMCPRINTF("int wait clear 2\n");
	}else{
		MMCPRINTF("No int_waiting!!!\n");
	}

	irq_handled = 1;
	sync(emmc_port);

	if(irq_handled)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}

static void rtkemmc_chk_card_insert(struct rtkemmc_host *emmc_port)
{
	struct mmc_host *host=emmc_port->mmc;
	unsigned long flags;

	MMCPRINTF("%s : \n", __func__);

	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_DQS_CTRL1);    //98012498, this setting will not take effect in hank A00

#ifdef PHASE_INHERITED
        if (VP0_saved == 0xFF && VP1_saved == 0xFF){
                HS200_TX = VP0_saved = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x000000f8) >> 3;
                HS200_RX = VP1_saved = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x00001f00) >> 8;
        }

#endif
	if(emmc_port->tx_user_defined) {        //if we set user defined tx and rx value, then we won't use the bootcode reference value, always the first priority
                HS200_TX = VP0_saved = emmc_port->tx_reference_phase;
        }
        if(emmc_port->rx_user_defined) {
                HS200_RX = VP1_saved = emmc_port->rx_reference_phase;
        }

#ifdef DQS_INHERITED
	if (dqs_saved == 0xff)
		dqs_saved = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#endif
	rtkemmc_writel(3, emmc_port->crt_membase + SYS_PLL_EMMC1);      //980001f0

	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

	isb();
	sync(emmc_port);

	rtkemmc_writeb(0x07, emmc_port->emmc_membase + EMMC_SW_RST_R);      //9801202f, Software Reset Register
	isb();
	sync(emmc_port);
	
	rtkemmc_writeb(0x0e, emmc_port->emmc_membase + EMMC_TOUT_CTRL_R);      //9801202e, Timeout Control register 
        isb();
        sync(emmc_port);

	rtkemmc_writew(0x200, emmc_port->emmc_membase + EMMC_BLOCKSIZE_R);      //98012004, block size = 512Byte
        isb();
        sync(emmc_port);

	rtkemmc_writew(0x1008 ,emmc_port->emmc_membase + EMMC_HOST_CTRL2_R);
	isb();
	sync(emmc_port);

	rtkemmc_writew(0xfeff, emmc_port->emmc_membase+EMMC_NORMAL_INT_STAT_EN_R);	//98012034, enable all Normal Interrupt Status register
	isb();
	sync(emmc_port);

	rtkemmc_writew(EMMC_ALL_ERR_STAT_EN, emmc_port->emmc_membase+EMMC_ERROR_INT_STAT_EN_R);	//98012036, enable all error Interrupt Status register
	isb();
	sync(emmc_port);

	rtkemmc_writew(0xfeff,emmc_port->emmc_membase+EMMC_NORMAL_INT_SIGNAL_EN_R);	//98012038, enable all Normal SIGNAL Interrupt  register
	isb();
	sync(emmc_port);

	rtkemmc_writew(EMMC_ALL_ERR_SIGNAL_EN,emmc_port->emmc_membase+EMMC_ERROR_INT_SIGNAL_EN_R);	//9801203a, enable all error SIGNAL Interrupt register
	isb();
	sync(emmc_port);

	rtkemmc_writeb(0x0d, emmc_port->emmc_membase + EMMC_CTRL_R);      //9801202f, choose is card emmc bit
	isb();
	sync(emmc_port);

	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x1, emmc_port->emmc_membase+EMMC_OTHER1);        //disable L4 gated
	isb();
	sync(emmc_port);

	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_DUMMY_SYS)|(EMMC_CLK_O_ICG_EN|EMMC_CARD_STOP_ENABLE), emmc_port->emmc_membase+EMMC_DUMMY_SYS);	//enable eMMC command clock
	isb();
	sync(emmc_port);

	rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xe7)|(EMMC_ADMA2_32<<EMMC_DMA_SEL),
                        emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);   //ADMA2 32 bit select
	isb();
        sync(emmc_port);

	rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_MSHC_CTRL_R) & (~EMMC_CMD_CONFLICT_CHECK)), emmc_port->emmc_membase + EMMC_MSHC_CTRL_R);	//disable emmc cmd conflict checkout
	isb();
	sync(emmc_port);

	rtkemmc_writew(readw(emmc_port->emmc_membase + EMMC_CLK_CTRL_R)|0x1, emmc_port->emmc_membase + EMMC_CLK_CTRL_R);   //enable internal clock
	isb();
	sync(emmc_port);

	rtkemmc_writel(0x1, emmc_port->m2tmx_membase+EMMC_NAND_DMA_SEL);	// #sram_ctrl, 0 for nf, 1 for emmc
        isb();
        sync(emmc_port);

	spin_lock_irqsave(&emmc_port->lock,flags);	
	//initially set bus width 1
	rtkemmc_writeb((readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R)&0xdd)|EMMC_BUS_WIDTH_1,emmc_port->emmc_membase + EMMC_HOST_CTRL1_R);
	sync(emmc_port);
	spin_unlock_irqrestore(&emmc_port->lock, flags);

	printk(KERN_INFO "%s: set bus width 1, 0x98012028=%08x\n", DRIVER_NAME, readb(emmc_port->emmc_membase + EMMC_HOST_CTRL1_R));

	rtkemmc_set_pad_driving(emmc_port, 0x0, 0x0, 0x0, 0x0);

	
	//initially, we do not use pass tuning result from bootcode, so we need to reset the tx ,rx phase to 0 first, 
	//and then framework call rtkemmc_tuning will set the rx tx register
	//Now, we use the mechanism and hold this part for fear that user will use kernel tuning one day in the future
	//if we use tuning inherit, the phase will be set to 0 and restore the tx rx from bootcode
	phase(emmc_port, 0, 0); //VP0, VP1 phase

	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);

	rtkemmc_set_freq(emmc_port,0x46, 0x80);  //80Mhz / 256 ~= 300K

	sync(emmc_port);
	host->ops = &rtkemmc_ops;
	emmc_port->rtflags |= RTKCR_FCARD_DETECTED;
}

static int rtkemmc_set_rspparam(struct rtkemmc_host *emmc_port, struct sd_cmd_pkt *cmd_info)
{
	switch(cmd_info->cmd->opcode)
	{
	case MMC_GO_IDLE_STATE:
		cmd_info->cmd_para = (EMMC_NO_RESP);
		cmd_info->rsp_len = 6;
		cmd_info->cmd->arg = 0x00000000;
		break;
	case MMC_SEND_OP_COND:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48);
		cmd_info->cmd->arg = MMC_SECTOR_ADDR|MMC_VDD_165_195;
		cmd_info->rsp_len = 6;
		break;
	case MMC_ALL_SEND_CID:
		cmd_info->cmd_para = (EMMC_RESP_LEN_136|EMMC_CMD_CHK_RESP_CRC);
		cmd_info->rsp_len = 17;
		cmd_info->cmd->arg = 0x00000000;
		break;
	case MMC_SET_RELATIVE_ADDR:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_CSD:
	case MMC_SEND_CID:
		cmd_info->cmd_para = (EMMC_RESP_LEN_136|EMMC_CMD_CHK_RESP_CRC);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 17;
		break;
	case MMC_SEND_EXT_CSD:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->cmd->arg = 0;
		cmd_info->rsp_len = 6;
		break;
	case MMC_SLEEP_AWAKE:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48B|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->rsp_len = 6;
		printk(KERN_INFO "%s : cmd5 arg=0x%08x\n",__func__,cmd_info->cmd->arg);
		break;
	case MMC_SELECT_CARD:
		printk(KERN_INFO "%s : cmd7 arg : 0x%08x\n",__func__,cmd_info->cmd->arg);
		if (cmd_info->cmd->flags == (MMC_RSP_NONE | MMC_CMD_AC)) {
			printk(KERN_INFO "%s : cmd7 with rsp none\n",__func__);
			cmd_info->cmd_para = (EMMC_NO_RESP);
		}
		else {
			printk(KERN_INFO "%s : cmd7 with rsp\n",__func__);
			cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		}
		cmd_info->rsp_len = 6;
		break;
	case MMC_SWITCH:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48B|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_STATUS:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 6;
		break;
	case MMC_STOP_TRANSMISSION:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|(EMMC_ABORT_CMD<<6));
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_TUNING_BLOCK_HS200:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->cmd->arg = 0;
		cmd_info->rsp_len = 6;
	case MMC_READ_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SET_BLOCK_COUNT:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->rsp_len = 6;
		break;
	case MMC_READ_SINGLE_BLOCK:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_BLOCK:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
		cmd_info->rsp_len = 6;
		break;
	case MMC_ERASE_GROUP_START:
	case MMC_ERASE_GROUP_END:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
                cmd_info->rsp_len = 6;
		break;
	case MMC_ERASE:
		cmd_info->cmd_para = (EMMC_RESP_LEN_48B|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE);
		cmd_info->rsp_len = 6;
		break;
	case MMC_GEN_CMD:
		if(cmd_info->cmd->arg & 0x1) {   //read single block
			cmd_info->cmd->arg = 0x1;
			cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
			cmd_info->rsp_len = 6;
			break;
		}
		else {      //write single block
			cmd_info->cmd->arg = 0x0;
			cmd_info->cmd_para = (EMMC_RESP_LEN_48|EMMC_CMD_CHK_RESP_CRC|EMMC_CMD_IDX_CHK_ENABLE|EMMC_DATA);
			cmd_info->rsp_len = 6;
			break;
		}
	default:
		printk("Realtek Unrecognized eMMC command!!!\n");
		cmd_info->cmd_para = 0;
		cmd_info->rsp_len = 6;
		break;
	}

	MMCPRINTF(KERN_INFO "%s : cmd=0x%02x rsp_len=0x%02x arg=0x%08x para=0x%08x\n","rtkemmc", cmd_info->cmd->opcode, cmd_info->rsp_len,cmd_info->cmd->arg,cmd_info->cmd_para);
	return 0;
}

static int rtkemmc_stop_transmission(struct mmc_card *card,int bIgnore)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	int err = 0;
	int bMalloc=0;
	struct mmc_host * mmc = mmc_host_local;

	MMCPRINTF("%s : \n", __func__);

	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));
	if (card == NULL) {
		bMalloc=1;
		card = (struct mmc_card*)kmalloc(sizeof(struct mmc_card),GFP_KERNEL);
		card->host = mmc;
	}
	set_cmd_info(card,&cmd,&cmd_info, MMC_STOP_TRANSMISSION, 0x00, 6);
	err = SD_SendCMDGetRSP_Cmd(&cmd_info,bIgnore);
	//printk(KERN_ERR "Tuning err handling cmd 12: EMMC_RINTSTS=0x%x,  EMMC_STATUS=0x%x\n",readl(emmc_port->emmc_membase + EMMC_RINTSTS),readl(emmc_port->emmc_membase + EMMC_STATUS));
	if (bMalloc) {
		kfree(card);
		card = NULL;
	}

	if(err)
		mmcmsg3(KERN_WARNING "%s: MMC_STOP_TRANSMISSION fail\n",DRIVER_NAME);

	return err;
}

static int rtkemmc_wait_status(struct mmc_card *card,u8 state,u8 divider,int bIgnore)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	unsigned long timeend;
	int err, bMalloc=0;
	struct mmc_host * mmc = mmc_host_local;

	MMCPRINTF("\n");
	timeend = jiffies + msecs_to_jiffies(100);    /* wait 100ms */

	if (card == NULL) {
		bMalloc=1;
		card = (struct mmc_card*)kmalloc(sizeof(struct mmc_card),GFP_KERNEL);
		card->host = mmc;
	}

	do {
		memset(&cmd, 0, sizeof(struct mmc_command));
		memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

		set_cmd_info(card,&cmd,&cmd_info, MMC_SEND_STATUS, (card->rca)<<RCA_SHIFTER, 6);
		err = SD_SendCMDGetRSP_Cmd(&cmd_info,bIgnore);

		if(err) {
			if (!bIgnore)
				printk(KERN_INFO "wait %s fail\n",state_tlb[state]);
			break;
		}
		else {
			u8 cur_state = R1_CURRENT_STATE(cmd.resp[0]);
			if (!bIgnore)
				MMCPRINTF(KERN_WARNING "resp[0]=0x%08x,cur_state=%s\n",cmd.resp[0],state_tlb[cur_state]);
			err = -1;
			if(cur_state == state) {
				if(cmd.resp[0] & R1_READY_FOR_DATA) {
					err = 0;
					break;
				}
			}
		}
	}while(time_before(jiffies, timeend));

	if (bMalloc) {
		kfree(card);
		card = NULL;
	}
	return err;
}
#if 0
void down_speed_handling(struct rtkemmc_host *emmc_port)
{
	struct mmc_host *mmc = emmc_port->mmc;
	if(gCurrentBootMode == MODE_HS200) {
		printk(KERN_ERR "down speed from HS200 to SDR50....\n");
		//downgrade to SDR50 mode
		mmc->caps &= ~(MMC_CAP_UHS_DDR50|MMC_CAP_1_8V_DDR);	//do not set emmc host capability as HS200
		mmc->caps2 &= ~(MMC_CAP2_HS200_1_8V_SDR);
		udelay(200);

		rtkemmc_stop_transmission(mmc->card, 1);
		wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x200, 0x0, __func__);          //card is not busy
		isb();
		sync(emmc_port);
		if (readl(emmc_port + EMMC_TBBCNT) == 1024) {
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_ISR), ISR_DMA_DONE_INT, ISR_DMA_DONE_INT, __func__);          //card is not busy
			isb();
			sync(emmc_port);
			rtkemmc_clr_int_sta();
		}

		card_stop(emmc_port);
		polling_to_tran_state(emmc_port,MMC_READ_MULTIPLE_BLOCK,1);//just pick up 1 command index for parameter

		if (!g_bResuming)
			gCurrentBootMode = MODE_SDR;

		rtkemmc_select_card_type(mmc->card);	//do not set the emmc card capability as HS200
		rtkemmc_select_timing(mmc->card);	//send cmd 6 again to inform the host SDR50 mode and set the correct bus speed mode

		rtkemmc_set_freq(emmc_port, 0x57, 0x1); //50Mhz

		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);

		rtkemmc_writel(3, emmc_port->crt_membase + SYS_PLL_EMMC1);      //980001f0
#if defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
		isb();
	
		sync(emmc_port);
		udelay(100);
	}
	else if(gCurrentBootMode == MODE_HS400) {
		//TBD
		printk(KERN_ERR "down speed from HS400 to HS200....\n");
		//downgrade to HS200 mode
		mmc->caps2 &= ~(MMC_CAP2_HS400_1_8V);
		if (!g_bResuming) {
			gCurrentBootMode = MODE_HS200;
		}
		emmc_port->tx_tuning = emmc_port->rx_tuning = 1;

		set_RTK_initial_flag(0);
		printk(KERN_ERR "stop the emmc ...\n");
		rtkemmc_stop_transmission(mmc->card, 1);
		wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x200, 0x0, __func__);          //card is not busy
		isb();
		sync(emmc_port);
		if (readl(emmc_port + EMMC_TBBCNT) == 1024) {
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_ISR), ISR_DMA_DONE_INT, ISR_DMA_DONE_INT, __func__);          //card is not busy
			isb();
			sync(emmc_port);
			rtkemmc_clr_int_sta();
		}

		card_stop(emmc_port);
		polling_to_tran_state(emmc_port,MMC_READ_MULTIPLE_BLOCK,1);//just pick up 1 command index for parameter
		//rtkemmc_backup_registers(emmc_port);
		//rtkemmc_hw_reset();
		//rtkemmc_restore_registers(emmc_port);
		rtkemmc_writel(0x00000000 ,emmc_port->emmc_membase + EMMC_DDR_REG);
		rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_UHSREG);
		rtkemmc_writel(0x80, emmc_port->emmc_membase + EMMC_DQS_CTRL1);
		printk(KERN_ERR "down speed: change emmc card capability to hs200...\n");
                rtkemmc_select_card_type(mmc->card);    //do not set the emmc card capability as HS200
		printk(KERN_ERR "down speed: hs400 to hs200...\n");
		mmc_hs400_to_hs200(mmc->card);
		printk(KERN_ERR "down speed: HS200 tuning...\n");
		hs400_to_hs200_flag=true;
		rtkemmc_hs200_tuning(mmc->card);
	}
}
#endif
static int rtkemmc_wait_opt_end(char* drv_name, struct rtkemmc_host *emmc_port,u8 cmdcode,u32 cmd_idx,u8 ignore_log)
{
	volatile int err = RTK_SUCC;
	volatile unsigned long timeend=0;
	unsigned long flags;
	u8 XFER_flag=0;
	u16 reg_blksize = 0;
	u16 reg_blkcount = 0;
	u16 reg_cmdidx = 0;
	u32 reg_argu = 0;

	unsigned long msec = TIMEOUT_MS;
	
	switch(CMD_IDX_MASK(cmd_idx)) {
		case MMC_READ_SINGLE_BLOCK:
		case MMC_READ_MULTIPLE_BLOCK:
		case MMC_WRITE_BLOCK:
		case MMC_WRITE_MULTIPLE_BLOCK:
		case MMC_SEND_EXT_CSD:
		case MMC_GEN_CMD:
		case MMC_SLEEP_AWAKE:
		case MMC_SWITCH:
		case MMC_ERASE:
		case MMC_SEND_TUNING_BLOCK_HS200:
#ifdef CONFIG_MMC_RTK_EMMC_CMDQ
		case MMC_CMDQ_TASK_MGMT:
#endif
			XFER_flag=1;
			break;
	}
	emmc_port->int_waiting = &rtk_emmc_wait;
	/* timeout timer fire */
	if (&emmc_port->timer) {
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
		MMCPRINTF("now = 0x%08x\n", jiffies);
		MMCPRINTF("timer started : ");
		timeend = jiffies + msecs_to_jiffies(msec)+emmc_port->tmout;
		MMCPRINTF("TO = 0x%08x\n", timeend);
		mod_timer(&emmc_port->timer, timeend );
#endif
	}

	if (emmc_port->int_waiting) {
		rtkemmc_hold_int_dec();
		rtkemmc_clr_int_sta();
		emmc_port->int_waiting = &rtk_emmc_wait;

		if (XFER_flag==1)
			rtkemmc_en_xfer_int();	//command with data, r1b case
		else
			rtkemmc_en_cd_int(); //command case

		if (CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK ){
			if (emmc_port->rpmb_cmd) {
				rtkemmc_writew(readw(emmc_port->emmc_membase + EMMC_XFER_MODE_R) & ~(1<<EMMC_AUTO_CMD_ENABLE), emmc_port->emmc_membase + EMMC_XFER_MODE_R);
			}//CMD25/18 following CMD13, never set CMD_SEND_AUTO_STOP
                }

		if(CMD_IDX_MASK(cmd_idx)==MMC_SEND_TUNING_BLOCK_HS200) {
			rtkemmc_writew(0x80, emmc_port->emmc_membase+EMMC_BLOCKSIZE_R);
		}
		else {
			rtkemmc_writew(0x200, emmc_port->emmc_membase+EMMC_BLOCKSIZE_R);
		}
		//cmd fire
		spin_lock_irqsave(&emmc_port->lock,flags);
		reg_blksize = readw(emmc_port->emmc_membase+EMMC_BLOCKSIZE_R);
		reg_blkcount = readw(emmc_port->emmc_membase+EMMC_BLOCKCOUNT_R);
		reg_argu = readl(emmc_port->emmc_membase+EMMC_ARGUMENT_R);
		rtkemmc_writew(cmd_idx,emmc_port->emmc_membase+EMMC_CMD_R);
		reg_cmdidx = readw(emmc_port->emmc_membase+EMMC_CMD_R);
		spin_unlock_irqrestore(&emmc_port->lock,flags);
		wait_for_completion(emmc_port->int_waiting);

		if(XFER_flag==1) {	//cmd with data
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R), 0x2, 0x2, __func__);
		}
		else{
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_NORMAL_INT_STAT_R), 0x1, 0x1, __func__);
		}
		if (emmc_port->normal_interrupt & EMMC_ERR_INTERRUPT) {
			if (!ignore_log) {
				if (CMD_IDX_MASK(cmd_idx)!=MMC_GO_IDLE_STATE) {
					printk(KERN_ERR "0x98012004 EMMC BLOCK SIZE = 0x%x\n",reg_blksize);
        				printk(KERN_ERR "0x98012006 EMMC BLOCK COUNT = 0x%08x\n", reg_blkcount);
        				printk(KERN_ERR "0x98012008 EMMC CMDARG = 0x%08x\n", reg_argu);
					printk(KERN_ERR "0x9801200e EMMC CMD REG = 0x%08x\n", reg_cmdidx);
					print_err_reg(cmd_idx, emmc_port->normal_interrupt, emmc_port->error_interrupt);
					print_ip_desc(emmc_port);
					print_reg_info(emmc_port);
					asm volatile("loop:");
					asm volatile("b loop");
				}
			}
			else{ //in tuning, only print rintsts
#ifdef RTKEMMC_DEBUG
				printk(KERN_ERR "Tuning error case!!!\n");
#endif
#if 0
				if (CMD_IDX_MASK(cmd_idx)!=MMC_GO_IDLE_STATE && (emmc_port->rintsts & (INT_STS_HTO | INT_STS_HLE | INT_STS_DRTO_BDS))) {
					printk(KERN_ERR "Tuning: HTO/HLE/DRTO - INT_STS_ERRORS, cmd_idx=0x%08x, rintsts=0x%08x, idsts=0x%08x, status=0x%08x\n",
						CMD_IDX_MASK(cmd_idx), emmc_port->rintsts, emmc_port->idsts, emmc_port->status);
				}
#endif
			}

			err = RTK_FAIL;
		}
	}
	return err;
}

u32 rtkemmc_swap_endian(u32 input)
{
        u32 output;
        output = (input & 0xff000000)>>24|
                 (input & 0x00ff0000)>>8|
                 (input & 0x0000ff00)<<8|
                 (input & 0x000000ff)<<24;
        return output;
}

#ifndef CONFIG_RTK_XEN_SUPPORT
static void make_sg_des(struct sd_cmd_pkt *cmd_info, u32 p_des_base, struct rtkemmc_host *emmc_port)
{
	u32  blk_cnt;
	u32  blk_cnt2;
	u32  remain_blk_cnt;
	u32  tmp_val;
	u32* des_base = gddr_descriptor ;
	u32  dir = 0;
	u32  dma_nents = 0;
	u32  dma_leng = 0;
	u32  dma_addr;
	u32  i;
	struct mmc_host *host = cmd_info->emmc_port->mmc;
	struct scatterlist *sg;

	MMCPRINTF("RTKEMMC: des_base = 0x%08x\n", des_base);

	if(cmd_info->data->flags & MMC_DATA_READ)
		dir = DMA_FROM_DEVICE;
	else
		dir = DMA_TO_DEVICE;

	dma_nents = dma_map_sg( mmc_dev(host), cmd_info->data->sg, cmd_info->data->sg_len,  dir);
	sg = cmd_info->data->sg;

	for(i=0; i<dma_nents; i++,sg++) {
		dma_leng = sg_dma_len(sg);
		blk_cnt  = dma_leng>>9;                         /*blk_cnt must be the multiple of 512(0x200)*/
		remain_blk_cnt  = blk_cnt;
		dma_addr = sg_dma_address(sg);

		while(remain_blk_cnt) {
			/* setting des1; buffer size in byte */
                	if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK)
                        	blk_cnt2 = EMMC_MAX_SCRIPT_BLK;
                	else
                        	blk_cnt2 = remain_blk_cnt;

			tmp_val = ((blk_cnt2&0x7f)<<25)|0x21;

			if((i==(dma_nents-1)) && (remain_blk_cnt == blk_cnt2))
				tmp_val |= 0x2;

			des_base[0] = rtkemmc_swap_endian(dma_addr);       /* setting des2; Physical address to DMA to/from */
			des_base[1] = rtkemmc_swap_endian(tmp_val);

			isb();
			sync(emmc_port);
#if 0
			printk(KERN_ERR "%s - remain cnt : 0x%08x, dma_addr=0x%08x, tmp_val=0x%08x, desc[0]=0x%08x, desc[1]=0x%08x\n",
				__func__, remain_blk_cnt, dma_addr, tmp_val, des_base[0],des_base[1]);
#endif
			dma_addr = dma_addr+(blk_cnt2<<9);
			remain_blk_cnt -= blk_cnt2;
			des_base += 2;
			isb();
			sync(emmc_port);
		}
	}

	//__flush_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
	//isb();
	wmb();
	sync(emmc_port);
}
#endif

static void make_ip_des(u32 dma_addr, u32 dma_length, u32 p_des_base, struct rtkemmc_host *emmc_port)
{
	u32  blk_cnt;
	u32  blk_cnt2;
	u32  remain_blk_cnt;
	u32  tmp_val;
	u32* des_base = gddr_descriptor ;

#if defined(CONFIG_CPU_V7)
	v7_flush_kern_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#else
	__flush_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#endif /* CONFIG_CPU_V7 */

	isb();
	sync(emmc_port);

	MMCPRINTF("RTKEMMC: des_base = 0x%08x\n", des_base);
	//blk_cnt must be the multiple of 512(0x200)
	if(dma_length<512) {
		blk_cnt = 1;
	}
	else{
		blk_cnt  = dma_length>>9;
	}
	remain_blk_cnt  = blk_cnt;

	isb();
	sync(emmc_port);

	while(remain_blk_cnt) {
		/* setting des1; buffer size in byte */
		if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK)
			blk_cnt2 = EMMC_MAX_SCRIPT_BLK;
		else
			blk_cnt2 = remain_blk_cnt;

		if(dma_length<512) tmp_val = ((dma_length)<<16)|0x21;
		else tmp_val = ((blk_cnt2&0x7f)<<25)|0x21;

		if(remain_blk_cnt == blk_cnt2)
			tmp_val |= 0x2;

		des_base[0] = rtkemmc_swap_endian(dma_addr);       /* setting des2; Physical address to DMA to/from */
		des_base[1] = rtkemmc_swap_endian(tmp_val);

		isb();
		sync(emmc_port);

		MMCPRINTF("%s - remain cnt : 0x%08x, desc[0]=0x%08x, desc[1]=0x%08x\n",
			__func__, remain_blk_cnt,des_base[0],des_base[1]);

		dma_addr = dma_addr+(blk_cnt2<<9);
		remain_blk_cnt -= blk_cnt2;
		des_base += 2;
		isb();
		sync(emmc_port);
	}

#if defined(CONFIG_CPU_V7)
	v7_flush_kern_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#else
	__flush_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#endif /* CONFIG_CPU_V7 */

	isb();
	sync(emmc_port);
}

static void rtkemmc_read_rsp(struct rtkemmc_host *emmc_port,u32 *rsp, int reg_count)
{
	MMCPRINTF("rsp addr=0x%p; rsp_count=%u\n", rsp, reg_count);
	if ( reg_count==6 ){
		rsp[0] = rsp[1] = 0;
		rsp[0] = readl(emmc_port->emmc_membase + EMMC_RESP01_R);
		MMCPRINTF(KERN_INFO "rsp[0]=0x%08x, rsp[1]=0x%08x\n",rsp[0],rsp[1]);
	}else if(reg_count==17){
		/*1. UNSTUFF_BITS uses the reverse order as: const int __off = 3 - ((start) / 32);
		  2. be32_to_cpu is called in mmc_send_csd as csd[i] = be32_to_cpu(csd_tmp[i]);*/
		//in hank eMMC IP, we neeed to rearrange  response in 17 bytes case because they save 8-135 bit instead of 0-127 bit
		u32 rsp_tmp[4]={0};
		rsp_tmp[3] = readl(emmc_port->emmc_membase + EMMC_RESP01_R);
		rsp_tmp[2] = readl(emmc_port->emmc_membase + EMMC_RESP23_R);
		rsp_tmp[1] = readl(emmc_port->emmc_membase + EMMC_RESP45_R);
		rsp_tmp[0] = readl(emmc_port->emmc_membase + EMMC_RESP67_R);
		rsp[3] = (rsp_tmp[3]&0x00ffffff)<<8;
		rsp[2] = ((rsp_tmp[2]&0x00ffffff)<<8) | ((rsp_tmp[3]&0xff000000)>>24);
		rsp[1] = ((rsp_tmp[1]&0x00ffffff)<<8) | ((rsp_tmp[2]&0xff000000)>>24); 
		rsp[0] = ((rsp_tmp[0]&0x00ffffff)<<8) | ((rsp_tmp[1]&0xff000000)>>24);
		MMCPRINTF(KERN_INFO "rsp[0]=0x%08x, rsp[1]=0x%08x, rsp[2]=0x%08x, rsp[3]=0x%08x\n",rsp[0],rsp[1],rsp[2],rsp[3]);
	}
	else
		MMCPRINTF("rsp[0]=0x%08x\n",rsp[0]);
}

static int rtkemmc_send_status(struct mmc_card *card, u32 *status, u8 *state,u8 divider,int bIgnore)
{
	struct mmc_command cmd;
	struct sd_cmd_pkt cmd_info;
	int err=0;
	int bMalloc=0;
	struct mmc_host * mmc = mmc_host_local;

	memset(&cmd, 0, sizeof(struct mmc_command));
	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	if (card == NULL) {
		bMalloc=1;
		card = (struct mmc_card*)kmalloc(sizeof(struct mmc_card),GFP_KERNEL);
		card->host = mmc;
	}

	set_cmd_info(card,&cmd,&cmd_info, MMC_SEND_STATUS, (card->rca)<<RCA_SHIFTER, 6);
    
	err = SD_SendCMDGetRSP(&cmd_info,bIgnore);

	if (bMalloc) {
		kfree(card);
		card = NULL;
	}

	if(err)
		mmcmsg3(KERN_WARNING "%s: MMC_SEND_STATUS fail\n",DRIVER_NAME);
	else {
		(*status) = cmd.resp[0];
		(*state) = R1_CURRENT_STATE(cmd.resp[0]);
		if (!bIgnore)
		printk(KERN_INFO "cur_state=%s\n",state_tlb[(*state)]);
	}

	return err;
}

static int SD_SendCMDGetRSP_Cmd(struct sd_cmd_pkt *cmd_info,int bIgnore)
{
	volatile u8 cmd_idx              = cmd_info->cmd->opcode;
	u32 *rsp                = (u32 *)&cmd_info->cmd->resp;
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;
	struct mmc_host *host = emmc_port->mmc;
	int err;//, retry_count=0;
	u8 state = 0;
	u32 status = 0;
	int cmd1_retry_cnt = 3000;
	MMCPRINTF("%s \n", __func__);

//	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_PSTATE_REG), 0x3, 0x0, __func__);

	rtkemmc_set_rspparam(emmc_port,cmd_info);   //for 1295
	if(rsp == NULL)
		BUG_ON(1);

	if ((g_crinit == 0)&&(cmd_idx > MMC_SET_RELATIVE_ADDR)) {
		printk("%s : ignore cmd:0x%02x since we're still in emmc init stage\n",DRIVER_NAME,cmd_idx);
		return CR_TRANSFER_FAIL;
	}
RET_CMD:
	rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_ARGUMENT_R);
	isb();
	sync(emmc_port);

	emmc_port->cmd_opcode = cmd_idx;

	if (cmd_idx == MMC_SET_BLOCK_COUNT)
		emmc_port->rpmb_cmd = 1;
	else
		emmc_port->rpmb_cmd = 0;
	err = rtkemmc_wait_opt_end(DRIVER_NAME,emmc_port,EMMC_SENDCMDGETRSP,((cmd_idx<<8)|cmd_info->cmd_para),bIgnore);
	if(err == RTK_SUCC){
		sync(emmc_port);
		rtkemmc_read_rsp(emmc_port,rsp, cmd_info->rsp_len);
		sync(emmc_port);
#if 0
		printk(KERN_INFO "%s: rsp[0]=0x%x, rsp[1]=0x%x, rsp[2]=0x%x, rsp[3]=0x%x\n",__func__, rsp[0], rsp[1], rsp[2], rsp[3]);
#endif
		//luis, TBC
		while ((cmd_idx == MMC_SEND_OP_COND) && ((rsp[0]&0x80000000) != 0x80000000) && cmd1_retry_cnt--) {
			sync(emmc_port);
			mdelay(1);
			goto RET_CMD;
		}

		//CMD1 timeout case
		if ((cmd_idx == MMC_SEND_OP_COND) && ((rsp[0]&0x80000000) != 0x80000000)){
			printk(KERN_ERR RED_BOLD"eMMC CMD1 timeout error !!\n"RESET);
			BUG();
		}

		if (cmd_idx == MMC_SET_RELATIVE_ADDR) {
			g_crinit = 1;
			MMCPRINTF("emmc init done ...\n");
		}

		//get cmd7 status
		if ((cmd_info->cmd->flags == (MMC_RSP_NONE | MMC_CMD_AC))&&(cmd_idx==MMC_SELECT_CARD)) {
			printk(KERN_INFO "get status =>\n");
			rtkemmc_send_status(host->card,&status, &state,0,0);
		}

	}
	else {
#if 0
		if (gCurrentBootMode > MODE_SDR && cmd_idx > MMC_SEND_OP_COND)
			return err;
		if (cmd_idx == MMC_SEND_STATUS) //prevent dead lock looping
			return err;
#else
		if(!bIgnore) {
			printk(KERN_ERR "SD_SendCMDGetRSP_Cmd error...\n");
			if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
				(EMMC_AUTO_CMD_ERR|EMMC_CMD_IDX_ERR|EMMC_CMD_END_BIT_ERR|EMMC_CMD_CRC_ERR|EMMC_CMD_TOUT_ERR))!=0){ //check cmd line
#ifdef RTKEMMC_DEBUG
				printk(KERN_INFO "CMD Line error occurs \n");
#endif
				rtkemmc_writeb(0x2, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
				wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x2<<24), 0x0, __func__); //wait for clear 0x2f bit 1
			}
			if((readw(emmc_port->emmc_membase + EMMC_ERROR_INT_STAT_R)&
				(EMMC_ADMA_ERR|EMMC_DATA_END_BIT_ERR|EMMC_DATA_CRC_ERR|EMMC_DATA_TOUT_ERR)) !=0){ //check data line
#ifdef RTKEMMC_DEBUG
				printk(KERN_INFO "DAT Line error occurs \n");
#endif
				rtkemmc_writeb(0x4, emmc_port->emmc_membase + EMMC_SW_RST_R); //Perform a software reset
				wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + 0x2c), (0x4<<24), 0x0, __func__); //wait for clear 0x2f bit 2
			}
		}
#endif
	}
	return err;
}

static int SD_Stream_Cmd(u16 cmdcode,struct sd_cmd_pkt *cmd_info, unsigned int bIgnore)
{
	u8 cmd_idx              = cmd_info->cmd->opcode;
	u32 *rsp                = (u32 *)&cmd_info->cmd->resp;
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;
	u16 block_count         = cmd_info->block_count;
	int err;
	u8 *data              = cmd_info->dma_buffer;
//	u32 retry_count=0;

	int read_flag=1;
	int mul_blk_flag=0;
	int auto_stop_flag=0;

	MMCPRINTF("%s \n", __func__);

	if(rsp == NULL)
		BUG_ON(1);
//	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_PSTATE_REG), 0x3, 0x0,__func__);
#ifdef TEST_POWER_RESCYCLE
	cmd_info->emmc_port->test_count++;
	mmcspec("test_count=%d\n",cmd_info->emmc_port->test_count);
#endif

	if ((g_crinit == 0)&&(cmd_idx > MMC_SET_RELATIVE_ADDR)) {
		printk("%s : ignore cmd:0x%02x since we're still in emmc init stage\n",DRIVER_NAME,cmd_idx);
		return CR_TRANSFER_FAIL;
	}

	rtkemmc_set_rspparam(emmc_port,cmd_info);   //for 119x

	/*************************************************************************/
	rtkemmc_writel(readl(emmc_port->iso_blk_membase + EMMC_SWC_SEL)|0x10, emmc_port->iso_blk_membase + EMMC_SWC_SEL);
	rtkemmc_writel(readl(emmc_port->iso_blk_membase + EMMC_SWC_SEL1)&0xffffffef, emmc_port->iso_blk_membase + EMMC_SWC_SEL1);
	rtkemmc_writel(readl(emmc_port->iso_blk_membase + EMMC_SWC_SEL2)|0x10, emmc_port->iso_blk_membase + EMMC_SWC_SEL2);
	rtkemmc_writel(readl(emmc_port->iso_blk_membase + EMMC_SWC_SEL3)&0xffffffef, emmc_port->iso_blk_membase + EMMC_SWC_SEL3);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_CP);
	/*************************************************************************/
#ifndef CONFIG_RTK_XEN_SUPPORT
	if (cmd_info->data)
		make_sg_des(cmd_info, emmc_port->desc_paddr, emmc_port);
	else if (data) {
		if(cmd_idx==MMC_SEND_TUNING_BLOCK_HS200) make_ip_des(data, 0x80, emmc_port->desc_paddr, emmc_port);
		else make_ip_des(data, block_count<<9, emmc_port->desc_paddr, emmc_port);
	}
	else
		BUG_ON(1);
#else
	if(cmd_idx==MMC_SEND_TUNING_BLOCK_HS200) make_ip_des(data, 0x80, emmc_port->desc_paddr, emmc_port);
	else make_ip_des(data, block_count<<9, emmc_port->desc_paddr, emmc_port);
#endif
//STR_CMD_RET:
	rtkemmc_writew(block_count, emmc_port->emmc_membase + EMMC_BLOCKCOUNT_R);
	rtkemmc_writel(emmc_port->desc_paddr, emmc_port->emmc_membase + EMMC_ADMA_SA_LOW_R);

	rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_ARGUMENT_R);

	if(cmd_idx==MMC_WRITE_BLOCK || cmd_idx==MMC_WRITE_MULTIPLE_BLOCK || cmd_idx==MMC_LOCK_UNLOCK
		||cmd_idx==47 || cmd_idx==49 || (cmd_idx==MMC_GEN_CMD && cmd_info->cmd->arg==0))
		read_flag=0;

	if(cmd_idx==MMC_WRITE_MULTIPLE_BLOCK || cmd_idx==MMC_READ_MULTIPLE_BLOCK) {
		mul_blk_flag=1;
		auto_stop_flag=1;
	}

	rtkemmc_writew((mul_blk_flag<<EMMC_MULTI_BLK_SEL)|
		       (read_flag<<EMMC_DATA_XFER_DIR)|
		       (auto_stop_flag<<EMMC_AUTO_CMD_ENABLE)|
		        EMMC_BLOCK_COUNT_ENABLE|
			EMMC_DMA_ENABLE,
			emmc_port->emmc_membase + EMMC_XFER_MODE_R);
	isb();
	sync(emmc_port);

#if 0
	//workaround, if fail to write EMMC_CMDARG, re-write
	while(readl(emmc_port->emmc_membase + EMMC_ARGUMENT_R) != cmd_info->cmd->arg) {
		printk(KERN_ERR RED_BOLD"SD_Stream_Cmd: Fail to write EMMC_CMDARG ! \n"RESET);
		printk(KERN_ERR "cmd_info->opcode = 0x%08x \n", cmd_info->cmd->opcode );
		printk(KERN_ERR "cmd_info->cmd->arg = 0x%08x \n", cmd_info->cmd->arg );
		printk(KERN_ERR "EMMC_CMDARG = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_ARGUMENT_R));
		rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_ARGUMENT_R);
		isb();
		sync(emmc_port);
	}
#endif
	emmc_port->cmd_opcode = cmd_idx;

	rtkemmc_get_cmd_timeout(cmd_info);
	isb();
	sync(emmc_port);
	err = rtkemmc_wait_opt_end(DRIVER_NAME,emmc_port,cmdcode,((cmd_idx<<8)|cmd_info->cmd_para),bIgnore);
	isb();
	sync(emmc_port);

	if(err == RTK_SUCC) {
		if((cmdcode == EMMC_AUTOREAD1) || (cmdcode == EMMC_AUTOWRITE1))
			MMCPRINTF("AUTO READ/WRITE 1 skip response~\n");
		else {
			rtkemmc_read_rsp(emmc_port,rsp, cmd_info->rsp_len);
#if 0
			printk(KERN_INFO "%s: rsp[0]=0x%x, rsp[1]=0x%x, rsp[2]=0x%x, rsp[3]=0x%x\n",__func__, rsp[0], rsp[1], rsp[2], rsp[3]);
#endif
		}
	}
	else {
#if 0
		if(cmd_resend==1) //down speed handling
			return RTK_SUCC;
#else
		if(!bIgnore) {
			printk(KERN_ERR "SD_Stream_Cmd error...\n");
			error_handling(emmc_port);
		}
#endif
	}
	return err;
}

static int SD_SendCMDGetRSP(struct sd_cmd_pkt * cmd_info,int bIgnore)
{
	int rc;

	MMCPRINTF("\n");

	rc = SD_SendCMDGetRSP_Cmd(cmd_info,bIgnore);
	return rc;
}

#ifndef CONFIG_RTK_XEN_SUPPORT
static int SD_Stream(struct sd_cmd_pkt *cmd_info)
{
	int err=0;
	u32 dma_leng = 0;
	u32 old_arg;
	u16 cmdcode = 0;
	u32 dir = 0;

	struct mmc_host *host = cmd_info->emmc_port->mmc;
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;

	MMCPRINTF("%s \n", __func__);

	rtkemmc_set_rspparam(emmc_port,cmd_info);
	if(cmd_info->data->flags & MMC_DATA_READ){
		dir = DMA_FROM_DEVICE;
	}else{
		dir = DMA_TO_DEVICE;
	}

	cmd_info->data->bytes_xfered=0;
	//dma_nents = dma_map_sg( mmc_dev(host), cmd_info->data->sg, cmd_info->data->sg_len,  dir);
	//sg = cmd_info->data->sg;

#ifdef SHOW_MMC_PRD
	printk("sg_len:%u\n",cmd_info->data->sg_len);
	printk("sg:0x%p; dma_nents:%u\n",sg,dma_nents);
#endif
	old_arg=cmd_info->cmd->arg;

	//for(i=0; i<dma_nents; i++,sg++)
		//dma_leng += sg_dma_len(sg);

	//printk("%s dma_leng=0x%x \n", __func__, dma_leng);      //hcy test
	//printk("%s cmd_info->data->blksz  =0x%x \n", __func__,    cmd_info->data->blksz );
	//printk("%s cmd_info->data->blocks =0x%x \n", __func__,    cmd_info->data->blocks);
	//printk("%s cmd_info->data->blksz * cmd_info->data->blocks =0x%x \n", __func__,    cmd_info->data->blksz * cmd_info->data->blocks);
	dma_leng = cmd_info->data->blksz * cmd_info->data->blocks;
#ifdef RTK_EMMC_HEALTH_REPORT
	//if(host->remainder == 0) printk(KERN_INFO "cmd_info->data->blksz = %d\n", cmd_info->data->blksz);
	//1G = 1024 x 1024 x 1024 bytes, so emmc size is from ext_csd,
	if((cmd_info->cmd->opcode==24 || cmd_info->cmd->opcode==25) && host->card!=NULL) {
		host->remainder += cmd_info->data->blocks;
		if(host->remainder/host->card->ext_csd.sectors > 0) {
			host->wr_emmc_size_cnt += (host->remainder/host->card->ext_csd.sectors);
			host->remainder = host->remainder % host->card->ext_csd.sectors;
		}
	}
	if(host->wr_emmc_size_cnt > 3000) printk(KERN_ERR "EMMC write count is larger than 3000 times of emmc size!!!\n");
#endif

#ifdef SHOW_MMC_PRD
	printk("dma_addr:0x%x; dma_leng:0x%x\n",dma_addr,dma_leng);
	mmcinfo("host=%p\n",host);
	if(host->card){
		mmcinfo("card=%p\n",host->card);
		if(mmc_card_blockaddr(host->card))
			printk("arg:0x%x blk\n",cmd_info->cmd->arg);
		else
			printk("arg:0x%x byte\n",cmd_info->cmd->arg);
	}
#endif

	cmd_info->byte_count = BYTE_CNT;     //rtk HW limite, one trigger 512 byte pass.
	cmd_info->block_count =  cmd_info->data->blocks; //blk_cnt;
	cmdcode = emmc_port->ops->chk_cmdcode(cmd_info->cmd);

	err = SD_Stream_Cmd(cmdcode,cmd_info,0);

	if(err == 0) {
		if(host->card){
			if( (cmd_info->cmd->opcode == 25) && (cmdcode == EMMC_AUTOWRITE2)) {
				int stop_err;

				stop_err = rtkemmc_stop_transmission(host->card,0);
				if(stop_err) {
					MMCPRINTF("rtkemmc_stop_transmission fail\n");
					goto ERR_HANDLE;
				}
			}
		}

		if(host->card && mmc_card_blockaddr(host->card))
			cmd_info->cmd->arg += cmd_info->block_count;
		else
			cmd_info->cmd->arg += dma_leng;

		cmd_info->data->bytes_xfered += dma_leng;
	}
	else {
ERR_HANDLE:
#if 0
		//TBD
		if(rtkemmc_err_handle(cmdcode,cmd_info)){
			if(cmd_info->cmd->opcode == 18 || cmd_info->cmd->opcode == 25) {
				if(host->card){
					int stop_err;
					stop_err = rtkemmc_stop_transmission(host->card,0);
					if(stop_err)
						MMCPRINTF("rtkemmc_stop_transmission fail\n");

					rtkemmc_wait_status(host->card,STATE_TRAN,0,0);
				}
			}
			else
				mmcmsg3(KERN_INFO "%s: error recover fail 4\n", DRIVER_NAME);
		}
#else
		printk(KERN_ERR "SD_Stream error...\n");
#endif
	}

	if(err)
		cmd_info->cmd->arg = old_arg;


	dma_unmap_sg( mmc_dev(host), cmd_info->data->sg, cmd_info->data->sg_len, dir);
	return err;
}
#else
static void duplicate_pkt(struct sd_cmd_pkt* sour,struct sd_cmd_pkt* dist)
{
	dist->emmc_port      = sour->emmc_port;
	dist->cmd         = sour->cmd;
	dist->data        = sour->data;

	dist->dma_buffer  = sour->dma_buffer;
	dist->byte_count  = sour->byte_count;
	dist->block_count = sour->block_count;

	dist->flags       = sour->flags;
	dist->rsp_len     = sour->rsp_len;
	dist->timeout     = sour->timeout;
}

static int SD_Stream(struct sd_cmd_pkt *cmd_info)
{
	int err=0;
	u32 i;
	struct scatterlist *sg;
	u32 dir = 0;
	u32 dma_nents = 0;
	u32 dma_leng;
	u32 dma_addr;
	u32 dma_addr_sys = 0;
	u32 old_arg;
	u8 one_blk=0;
	u8 f_in_dma = 0;
	u16 cmdcode = 0;
	unsigned long flags;

	struct mmc_host *host = cmd_info->emmc_port->mmc;
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;

	rtkemmc_set_rspparam(emmc_port, cmd_info);   //for 119x

	if(cmd_info->data->flags & MMC_DATA_READ){
		dir = DMA_FROM_DEVICE;
	}else{
		dir = DMA_TO_DEVICE;
	}

	cmd_info->data->bytes_xfered=0;
	dma_nents = dma_map_sg( mmc_dev(host), cmd_info->data->sg, cmd_info->data->sg_len,  dir);
	sg = cmd_info->data->sg;

	old_arg=cmd_info->cmd->arg;

	for(i=0; i<dma_nents; i++,sg++){
		dma_leng = sg_dma_len(sg);

		if(dma_leng & 0x1ff){
			dma_addr_sys = sg_dma_address(sg);

			if(emmc_port->tmp_buf){    //use tmp buffer
				f_in_dma = 1;
				dma_addr = emmc_port->tmp_buf_phy_addr;
			}else{                  //use default buffer
				dma_addr = dma_addr_sys;
			}
		}else{
			dma_addr = sg_dma_address(sg);
		}

		if(one_blk){    /* occur at write case only */
			u8 i;
			u32 blk_cnt;
			struct sd_cmd_pkt tmp_pkt;

			blk_cnt = dma_leng/BYTE_CNT;
			if(blk_cnt == 0){
				WARN_ON(1);
				blk_cnt = 1;
			}
			duplicate_pkt(cmd_info,&tmp_pkt);

			tmp_pkt.byte_count  = BYTE_CNT;
			tmp_pkt.block_count = 1;
			tmp_pkt.dma_buffer  = (unsigned char *)dma_addr;

			if(tmp_pkt.cmd->opcode == 25){
				tmp_pkt.cmd->opcode = 24;
			}

			if(tmp_pkt.cmd->opcode == 18){
				tmp_pkt.cmd->opcode = 17;
			}

			cmdcode = emmc_port->ops->chk_cmdcode(tmp_pkt.cmd);
			for(i=0;i<blk_cnt;i++){
				err = SD_Stream_Cmd(cmdcode,&tmp_pkt,0);

				if(err == 0){
					if(host->card && mmc_card_blockaddr(host->card))
						tmp_pkt.cmd->arg += 1;
					else
						tmp_pkt.cmd->arg += BYTE_CNT;

					tmp_pkt.dma_buffer += BYTE_CNT;
					tmp_pkt.data->bytes_xfered += BYTE_CNT;
				}else{
					//TBD
					mmcmsg3(KERN_INFO "%s: unknown fail 2\n", DRIVER_NAME);
					break;
				}
			}
		}
		else {
			u32 blk_cnt;
			cmd_info->byte_count = BYTE_CNT;     //rtk HW limite, one trigger 512 byte pass.
			blk_cnt = dma_leng/BYTE_CNT;

			if(blk_cnt == 0 && dma_leng){
				blk_cnt = 1;
			}

			cmd_info->block_count = blk_cnt;
			cmd_info->dma_buffer = (unsigned char *)dma_addr;

			cmdcode = emmc_port->ops->chk_cmdcode(cmd_info->cmd);
			err = SD_Stream_Cmd(cmdcode,cmd_info,0);

			if(err == 0){
				if(host->card){
					if( (cmd_info->cmd->opcode == 25) && (cmdcode == EMMC_AUTOWRITE2) ) {
						int stop_err;

						stop_err = rtkemmc_stop_transmission(host->card,0);
						if(stop_err){
							MMCPRINTF("rtkemmc_stop_transmission fail\n");
							goto ERR_HANDLE;
						}
					}
				}

				if(host->card && mmc_card_blockaddr(host->card))
					cmd_info->cmd->arg += cmd_info->block_count;
				else
					cmd_info->cmd->arg += dma_leng;

				cmd_info->data->bytes_xfered += dma_leng;
			}else{
ERR_HANDLE:
#if 0
				if(rtkemmc_err_handle(cmdcode,cmd_info)){
					if(cmd_info->cmd->opcode == 18 || cmd_info->cmd->opcode == 25) {
						if(host->card){
							int stop_err;
							stop_err = rtkemmc_stop_transmission(host->card,0);
							if(stop_err){
								MMCPRINTF("rtkemmc_stop_transmission fail\n");
								//goto ERR_HANDLE;
							}
							rtkemmc_wait_status(host->card,STATE_TRAN,0,0);
						}
					}else{
						mmcmsg3(KERN_INFO "%s: error recover fail 4\n", DRIVER_NAME);
					}
				}
#else
				printk(KERN_ERR "SD Stream error!!!\n");
#endif
			}
		}
		if(err){
			cmd_info->cmd->arg = old_arg;
			break;
		}

		if(f_in_dma){
			u32 i;
			u8 * ptr1 = phys_to_virt(dma_addr_sys);
			u8 * ptr2 = phys_to_virt(dma_addr);
			f_in_dma = 0;
			for(i=0; i<dma_leng;i++)
				*ptr1 = *ptr2;
		}
	}

	dma_unmap_sg( mmc_dev(host), cmd_info->data->sg, cmd_info->data->sg_len,  dir);

	return err;
}
#endif

static void rtkemmc_send_command(struct rtkemmc_host *emmc_port, struct mmc_command *cmd)
{
	int rc = 0;
	struct sd_cmd_pkt cmd_info;
	MMCPRINTF("%s \n", __func__);

	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	if ( !emmc_port || !cmd ){
		printk(KERN_ERR "%s: emmc_port or cmd is null\n",DRIVER_NAME);
		return ;
	}

	cmd_info.cmd    = cmd;
	cmd_info.emmc_port = emmc_port;
	if (cmd->data) {
		cmd_info.data = cmd->data;
		if(cmd->data->flags == MMC_DATA_READ){
			MMCPRINTF("%s MMC_DATA_READ\n", __func__);	/* do nothing */
		}else if(cmd->data->flags == MMC_DATA_WRITE){
			MMCPRINTF("%s MMC_DATA_WRITE\n", __func__);
			if(emmc_port->wp ==1){
				printk(KERN_WARNING "%s: card is locked!", DRIVER_NAME);
				rc = -1;
				cmd->retries = 0;
				goto err_out;
			}
		}else{
			printk(KERN_ERR "error: cmd->data->flags=%d\n", cmd->data->flags);
			cmd->error = -MMC_BLK_CMD_ERR;
			cmd->retries = 0;
			goto err_out;
		}
		if (g_bTuning)
			MMCPRINTF("................[%s:HS200] still tuning.............. \n",DRIVER_NAME);
		rc = SD_Stream(&cmd_info);
	}
	else {
		if (g_bTuning)
			MMCPRINTF("................[%s:HS200] still tuning.............. \n",DRIVER_NAME);
		rc = SD_SendCMDGetRSP(&cmd_info,0);
	}

	if(cmd->opcode == MMC_SWITCH){
		if((cmd->arg & 0xffff00ff) == 0x03b30001) {
			if((cmd->arg & 0x0000ff00)==0)
				emmc_port->rtflags |= RTKCR_USER_PARTITION;
			else
				emmc_port->rtflags &= ~RTKCR_USER_PARTITION;
		}
	}
	MMCPRINTF("%s: cmd->opcode=0x%02x finish !!\n",__func__,cmd->opcode);
err_out:

	if (rc){
		if(rc == -RTK_RMOV)
			cmd->retries = 0;
		cmd->error = -MMC_BLK_CMD_ERR;
	}
	rtkemmc_req_end_tasklet((unsigned long)emmc_port);
}

static void rtkemmc_request(struct mmc_host *host, struct mmc_request *mrq)
{
	struct rtkemmc_host *emmc_port;
	struct mmc_command *cmd;
#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	int cmdq_disable=0;
	struct cmdq_host *cq_host = (struct cmdq_host *)mmc_cmdq_private(host);
	int retry=0;
#endif
	MMCPRINTF("%s \n", __func__);
	emmc_port = mmc_priv(host);
	BUG_ON(emmc_port->mrq != NULL);

#if defined(CONFIG_MMC_RTK_EMMC_PON)
	if(mrq->cmd->opcode!=MMC_ERASE && mrq->cmd->opcode!=MMC_ERASE_GROUP_END) {    //cmd 36, 38 we do not need to occupy the semaphore
		while(1) {
			if(readl(emmc_port->emmc_membase+EMMC_HD_SEM)==1) break;
			else {
				printk(KERN_INFO "%s: Pon is occupying the semaphore, 0x98012030=0x%x, 0x98012032=0x%x\n",
					__func__, emmc_port->normal_interrupt, emmc_port->error_interrupt);
				usleep_range(10, 30);
			}
		}
	}
#endif

#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	if(cq_host->enabled==true) {
#ifdef RTKEMMC_DEBUG
		printk(KERN_INFO "currently is under cqe mode and back to normal mode for the time being, mrq->cmd->opcode=%d...\n", mrq->cmd->opcode);
#endif
		mmc_cmdq_halt(host, true);

		while(readl(emmc_port->emmc_membase+EMMC_CQTDBR)!=0 && (++retry)<=100) {
			printk(KERN_INFO "wait until DBR register 0, current DBR= 0x%x\n", readl(emmc_port->emmc_membase+EMMC_CQTDBR));
		}
		if(retry>100) printk(KERN_ERR "register DBR=0x%x before disabling cmdq!!!\n", readl(emmc_port->emmc_membase+EMMC_CQTDBR));

		rtkemmc_cmdq_disable(host, true);
		cmdq_disable=1;
	}
#endif

#if 0
	if(mrq->cmd->opcode==MMC_SEND_EXT_CSD)
	{
		//====we add the following program becasue we need to read HS400 parameter in specific emmc block in SDR50 mode if exists====
		//hs400 mode case, we need to eliminate the tuning process, so we read the dqs, phase data from offset that bootcode provided
		if((host->caps2 & MMC_CAP2_HS400_1_8V) && emmc_port->dqs_tuning==1 && emmc_port->emmc_tuning_addr!=0)    //bootcode doesn't do the hs400 tuning
		{
			int hs400_data[128]={0};        //4 bytes header, 33aa, 4 bytes for TX, 4 bytes for RX, 4 bytes for dqs
			rtkemmc_send_cmd18(emmc_port, 512, emmc_port->emmc_tuning_addr/512-1024);       //we put the hs400 parameter data after emmc hs400 1024 tuning patterns
			memcpy(hs400_data, gddr_dma_org, 512);

			printk(KERN_ERR "before cmd8, read dqs_data from emmc first for later usage: hs400_header=0x%x, hs400_TX=0x%x, hs400_RX=0x%x, hs400_dqs=0x%x\n",
				hs400_data[0], hs400_data[1], hs400_data[2], hs400_data[3]);

			if(hs400_data[0]==0x33aa) {     //inherit from emmc saved data instead of bootcode
				emmc_port->dqs_tuning=0;
				emmc_port->tx_tuning = 0;
				emmc_port->rx_tuning = 0;

				HS200_TX = VP0_saved = hs400_data[1];
				HS200_RX = VP1_saved = hs400_data[2];
				dqs_saved = hs400_data[3];

				if(emmc_port->tx_user_defined) {        //if we set user defined tx and rx value, then we won't use the bootcode reference value, always the first priority
					printk(KERN_ERR "tx_user_defined has been set, we still use user define value for usage\n");
					HS200_TX = VP0_saved = emmc_port->tx_reference_phase;
				}
				if(emmc_port->rx_user_defined) {
					printk(KERN_ERR "rx_user_defined has been set, we still use user define value for usage\n");
					HS200_RX = VP1_saved = emmc_port->rx_reference_phase;
				}
			}
		}
	}
#endif
	down_write(&cr_rw_sem);
	cmd = mrq->cmd;
	emmc_port->mrq = mrq;

	if (!(emmc_port->rtflags & RTKCR_FCARD_DETECTED)){
		cmd->error = -MMC_BLK_NOMEDIUM;
		cmd->retries = 0;
		goto done;
	}

#if defined(CONFIG_MMC_RTK_EMMC_PON)
        if(mrq->cmd->opcode==MMC_SLEEP_AWAKE || (mrq->cmd->opcode==MMC_SELECT_CARD && mrq->cmd->arg==0x0)) {
		goto done;
	}
#endif
	if ( emmc_port && cmd ){
		rtkemmc_allocate_dma_buf(emmc_port, cmd);
		rtkemmc_send_command(emmc_port, cmd);
	}else{
done:
		rtkemmc_req_end_tasklet((unsigned long)emmc_port);
	}
	up_write(&cr_rw_sem);
#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	if(cq_host->enabled==false && cmdq_disable==1) {
		rtkemmc_cmdq_enable(host);
		mmc_cmdq_halt(host, false);
        }
#endif

#if defined(CONFIG_MMC_RTK_EMMC_PON)
	if(mrq->cmd->opcode!=MMC_ERASE_GROUP_START && mrq->cmd->opcode!=MMC_ERASE_GROUP_END)  //cmd 35, 36 not release the semaphore
		rtkemmc_writel(0x0, emmc_port->emmc_membase+EMMC_HD_SEM);
#endif

#if 0
	if(cmd_resend==1) {
		cmd_resend=0;
		down_speed_handling(emmc_port);
	}
#endif
}

static ssize_t emmc_info_dev_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mmc_host * host = dev_get_drvdata(dev);
	struct rtkemmc_host *emmc_port = mmc_priv(host);

	printk(KERN_INFO "%s(%u)\n",__func__,__LINE__);

	return sprintf(buf, "EMMC SYS_PLL_EMMC1=0x%08x SYS_PLL_EMMC2=0x%08x \nSYS_PLL_EMMC3=0x%08x SYS_PLL_EMMC4=0x%08x HOST_CONTROL2_REG=0x%08x\n \
				PRESENT_STATE_REG=0x%08x  HOST CONTROL1 REG=0x%08x TRANSFER_MODE_REG=0x%08x \n EMMC_CKGEN_CTL=0x%08x EMMC_DQS_CTRL1=0x%08x \n",
				readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC4),
				readw(emmc_port->emmc_membase+EMMC_HOST_CTRL2_R),
				readl(emmc_port->emmc_membase+EMMC_PSTATE_REG),
				readb(emmc_port->emmc_membase+EMMC_HOST_CTRL1_R),
				readw(emmc_port->emmc_membase+EMMC_XFER_MODE_R),
				readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL),
				readl(emmc_port->emmc_membase+EMMC_DQS_CTRL1));

}

static ssize_t emmc_info_dev_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	printk(KERN_ERR "%s(%u)Nothing to do\n",__func__,__LINE__);

	/* return value must be equare or big then "count" to finish this attribute */
	return count;
}
DEVICE_ATTR(emmc_info, S_IRUGO | S_IWUSR,
		emmc_info_dev_show,emmc_info_dev_store);

static int rtkemmc_probe(struct platform_device *pdev)
{
	struct mmc_host *mmc = NULL;
	struct rtkemmc_host *emmc_port = NULL;
	int ret = 0, irq = 0;
	int att_err;
	const u32 *prop;
	int size,speed_step=0;
	struct device_node *emmc_node = NULL;
	int i;
	int counter=0;
	emmc_node = pdev->dev.of_node;

	if (!emmc_node)
		printk(KERN_ERR "%s : No emmc of_node found\n",DRIVER_NAME);
	else
		printk(KERN_ERR "%s : emmc of_node found\n",DRIVER_NAME);

	mmc = mmc_alloc_host(sizeof(struct rtkemmc_host), &pdev->dev);

	if (!mmc) {
		ret = -ENOMEM;
		goto out;
	}

	mmc_host_local = mmc;

	emmc_port = mmc_priv(mmc);
	memset(emmc_port, 0, sizeof(struct rtkemmc_host));
	emmc_port->mmc = mmc;
	emmc_port->dev = &pdev->dev;
	emmc_port->ops = &emmc_ops;

	sema_init(&emmc_port->sem,1);
	sema_init(&emmc_port->sem_op_end,1);

	//att_err = device_create_file(&pdev->dev, &dev_attr_cr_send_cmd0);
	//att_err = device_create_file(&pdev->dev, &dev_attr_cr_fast_RW);
	//att_err = device_create_file(&pdev->dev, &dev_attr_em_open_log);
	att_err = device_create_file(&pdev->dev, &dev_attr_emmc_info);

	irq = irq_of_parse_and_map(emmc_node, 0);
	if (irq <= 0) {
                printk(KERN_ERR "%s : fail to parse of irq.\n",DRIVER_NAME);
                return -ENXIO;
	}
	MMCPRINTF(KERN_INFO "%s : IRQ = 0x%08x\n",DRIVER_NAME, irq);

	emmc_port->emmc_membase = of_iomap(emmc_node, 0);
	emmc_port->crt_membase = of_iomap(emmc_node, 1);
	emmc_port->sb2_membase = of_iomap(emmc_node, 2);
	emmc_port->mux_mis_membase = of_iomap(emmc_node, 3);
	emmc_port->iso_blk_membase = of_iomap(emmc_node, 4);
	emmc_port->m2tmx_membase = of_iomap(emmc_node, 5);

#if defined(CONFIG_MMC_RTK_EMMC_PON)
	emmc_port->emmc_pon_gpio = of_get_gpio_flags(emmc_node, 0, NULL);
	if (gpio_is_valid(emmc_port->emmc_pon_gpio)) {
		ret = gpio_request(emmc_port->emmc_pon_gpio, "emmc_pon_gpio");
		if (ret < 0)
			printk(KERN_ERR "%s: can't request gpio %d\n", __func__, emmc_port->emmc_pon_gpio);
	} else {
		printk(KERN_ERR "%s: gpio %d is not valid\n", __func__, emmc_port->emmc_pon_gpio);
	}
#endif
	prop = of_get_property(pdev->dev.of_node, "speed-step", &size);
	if (prop) {
		speed_step = of_read_number(prop, 1);
		printk(KERN_INFO "[%s] get speed-step : %d \n",__func__,speed_step);
	} else {
		printk(KERN_ERR "[%s] get speed-step error !!\n",__func__);
	}
	prop = of_get_property(pdev->dev.of_node, "pddrive_nf_s0", &size);
	if (prop) {
		if (size)
			counter = size / sizeof(u32);

		for (i=0; i<counter; i+=1) {
			pddrive_nf_s0[i]= of_read_number(prop, 1 + i);
			/* KERN_ERR to let be happy */
			if(speed_step==0) printk(KERN_ERR "[%s] get driving s0 : 0x%x\n",__func__,pddrive_nf_s0[i]);
		}
	} else {
		printk(KERN_INFO "[%s] no driving nf_s0 warning !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "pddrive_nf_s1", &size);
	if (prop) {
		if (size)
			counter = size / sizeof(u32);

		for (i=0; i<counter; i+=1) {
			pddrive_nf_s1[i]= of_read_number(prop, 1 + i);
			/* KERN_ERR to let be happy */
			if(speed_step==1) printk(KERN_ERR "[%s] get driving s1 : 0x%x\n",__func__,pddrive_nf_s1[i]);
		}
	} else {
		printk(KERN_INFO "[%s] no driving nf_s1 warning !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "pddrive_nf_s2", &size);
	if (prop) {
		if (size)
			counter = size / sizeof(u32);

		for (i=0; i<counter; i+=1) {
			pddrive_nf_s2[i]= of_read_number(prop, 1 + i);
			/* KERN_ERR to let be happy */
			if(speed_step==2) printk(KERN_ERR "[%s] get driving s2 : 0x%x\n",__func__,pddrive_nf_s2[i]);
		}
	} else {
		printk(KERN_INFO "[%s] no driving nf_s2 warning !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "pddrive_nf_s3", &size);
        if (prop) {
                if (size)
                        counter = size / sizeof(u32);

                for (i=0; i<counter; i+=1) {
                        pddrive_nf_s3[i]= of_read_number(prop, 1 + i);
                        /* KERN_ERR to let be happy */
                        if(speed_step==3) printk(KERN_ERR "[%s] get driving s3 : 0x%x\n",__func__,pddrive_nf_s3[i]);
                }
        } else {
                printk(KERN_INFO "[%s] no driving nf_s3 warning !! \n",__func__);
        }

	prop = of_get_property(pdev->dev.of_node, "phase_tuning", &size);
	if (prop) {
		emmc_port->tx_tuning = of_read_number(prop, 1);
		emmc_port->rx_tuning = of_read_number(prop, 2);
		printk(KERN_ERR "[%s] get tx tuning switch : %u\n",__func__, emmc_port->tx_tuning);
		printk(KERN_ERR "[%s] get rx tuning switch : %u\n",__func__, emmc_port->rx_tuning);
	} else {
		emmc_port->tx_tuning = 1;	//if we do not get this node in device tree, we should tune phase by kernel
		emmc_port->rx_tuning = 1;
		printk(KERN_INFO "[%s] no phase_tuning switch node !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "dqs_tuning", &size);
	if (prop) {
		emmc_port->dqs_tuning = of_read_number(prop, 1);
		printk(KERN_ERR "[%s] get dqs tuning switch : %u\n",__func__, emmc_port->dqs_tuning);
	} else {
		emmc_port->dqs_tuning = 1;	//if we do not get this node, we should tune dqs value by kernel
		printk(KERN_INFO "[%s] no dqs_tuning switch node !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "reference_phase", &size);
	if (prop) {
		emmc_port->tx_user_defined = of_read_number(prop, 1);
		emmc_port->tx_reference_phase = of_read_number(prop, 2);
		emmc_port->rx_user_defined = of_read_number(prop, 3);
		emmc_port->rx_reference_phase = of_read_number(prop, 4);
		if(emmc_port->tx_user_defined) printk(KERN_ERR "[%s] get User defined tx reference phase: %u\n",__func__, emmc_port->tx_reference_phase);
		if(emmc_port->rx_user_defined) printk(KERN_ERR "[%s] get User defined rx reference phase: %u\n",__func__, emmc_port->rx_reference_phase);
	} else {
		emmc_port->tx_user_defined = 0;
		emmc_port->tx_reference_phase = 0x0;
		emmc_port->rx_user_defined = 0;
		emmc_port->rx_reference_phase = 0x0;
		printk(KERN_INFO "[%s] no tx & rx reference phase switch node !! \n",__func__);
	}

	prop = of_get_property(pdev->dev.of_node, "dqs_dly_tape", &size);
        if (prop) {
                emmc_port->dqs_dly_tape = of_read_number(prop, 1);
                printk(KERN_ERR "[%s] get dqs_dly_tape : %u\n",__func__, emmc_port->dqs_dly_tape);
        } else {
                emmc_port->dqs_dly_tape = 0x0;      //use 0x0 as default
                printk(KERN_INFO "[%s] no dqs_dly_tape switch node, use default 0x0 !! \n",__func__);
        }

	prop = of_get_property(pdev->dev.of_node, "emmc_tuning_addr", &size);
	if (prop) {
		emmc_port->emmc_tuning_addr = of_read_number(prop, 1);
		printk(KERN_ERR "[%s] GPT format: emmc tuning offset start from 0x%lx\n",__func__, emmc_port->emmc_tuning_addr);
	} else {
		emmc_port->emmc_tuning_addr = 0;      //if we do not get this node, we assume that the system uses MBR mode before Android O
		printk(KERN_INFO "[%s] No emmc tuning offset node, using MBR format !! \n",__func__);
	}
#if defined(CONFIG_MMC_RTK_EMMC_PON)
	prop = of_get_property(pdev->dev.of_node, "pon_addr", &size);
	if (prop) {
		emmc_port->pon_addr = of_read_number(prop, 1);
		emmc_port->pon_addr = emmc_port->pon_addr / 0x200;
		printk(KERN_ERR "[%s] pon address starts from 0x%lx\n",__func__, emmc_port->pon_addr);
	} else {
		emmc_port->pon_addr = 0;      //if we do not get this node, we assume that the system uses MBR mode before Android O
		printk(KERN_INFO "[%s] No pon address node, emmc_port->pon_addr = 0 !! \n",__func__);
	}
#endif

#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	rtkemmc_cmdq_init(emmc_port->cq_host, mmc, 0);  //allocate cq_host and realtek always uses ADMA 32 bit address
#endif
	rstc_emmc = devm_reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(rstc_emmc)) {
		printk(KERN_WARNING "%s: reset_control_get() returns %ld\n", __func__,
			PTR_ERR(rstc_emmc));
		rstc_emmc = NULL;
	}

	clk_en_emmc = devm_clk_get(&pdev->dev, "emmc");
	if (IS_ERR(clk_en_emmc)) {
		printk(KERN_WARNING "%s: clk_get() returns %ld\n", __func__,
			PTR_ERR(clk_en_emmc));
		clk_en_emmc = NULL;
	}
	clk_en_emmc_ip = devm_clk_get(&pdev->dev, "emmc_ip");
	if (IS_ERR(clk_en_emmc_ip)) {
		printk(KERN_WARNING "%s: clk_get() returns %ld\n", __func__,
			PTR_ERR(clk_en_emmc_ip));
		clk_en_emmc_ip = NULL;
	}
	clk_prepare_enable(clk_en_emmc);
	clk_prepare_enable(clk_en_emmc_ip);

	rtkemmc_writel(readl(emmc_port->crt_membase+0x454)|0x1, emmc_port->crt_membase+0x454);

	mmc->ocr_avail = MMC_VDD_30_31 
			| MMC_VDD_31_32
			| MMC_VDD_32_33
			| MMC_VDD_33_34
			| MMC_VDD_165_195;

	mmc->caps = MMC_CAP_4_BIT_DATA
		| MMC_CAP_8_BIT_DATA
		| MMC_CAP_SD_HIGHSPEED
		| MMC_CAP_MMC_HIGHSPEED
		| MMC_CAP_NONREMOVABLE
		| MMC_CAP_1_8V_DDR
		| MMC_CAP_UHS_DDR50
		| MMC_CAP_CMD23
		| MMC_CAP_ERASE;

	mmc->caps2 = (MMC_CAP2_NO_SDIO | MMC_CAP2_NO_SD);
	switch(speed_step)
	{
	case 0: //sdr50
		mmc->caps &= ~(MMC_CAP_UHS_DDR50|MMC_CAP_1_8V_DDR);
		mmc->caps2 &= ~(MMC_CAP2_HS200_1_8V_SDR);
		break;
	case 1: //ddr50
		mmc->caps2 &= ~(MMC_CAP2_HS200_1_8V_SDR);
		break;
	case 2: //hs200
		mmc->caps2 |= MMC_CAP2_HS200_1_8V_SDR;
		break;
	case 3: //hs400
		mmc->caps2 |= (MMC_CAP2_HS200_1_8V_SDR|MMC_CAP2_HS400_1_8V);
		break;
	}

	if(rtk_emmc_bus_wid == 4 || rtk_emmc_bus_wid == 5)
		mmc->caps &= ~MMC_CAP_8_BIT_DATA;

#if defined(CONFIG_MMC_RTK_EMMC_CMDQ)
	mmc->caps2 |= MMC_CAP2_CMD_QUEUE;
#endif
	mmc->caps2 |= MMC_CAP2_HC_ERASE_SZ;
	mmc->f_min = 300000;        //300K
	mmc->f_max = 400000000; //400M
#ifdef CONFIG_RTK_XEN_SUPPORT
	mmc->max_segs = 1;
#else
	mmc->max_segs = 256;	//the max number of nodes in the scatterlist
#endif
	mmc->max_blk_size   = 512;
#ifdef CONFIG_RTK_XEN_SUPPORT
	mmc->max_blk_count  = 0x400; //0x400;
#else
	mmc->max_blk_count  = 0x800;
#endif
	mmc->max_seg_size   = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_req_size   = mmc->max_blk_size * mmc->max_blk_count;

	spin_lock_init(&emmc_port->lock);
	init_rwsem(&cr_rw_sem);
	tasklet_init(&emmc_port->req_end_tasklet, rtkemmc_req_end_tasklet, (unsigned long)emmc_port);

	//Force enable dbg log
#ifdef MMC_DBG
	emmc_port->rtflags |= RTKCR_FOPEN_LOG;
#endif

	if(rtk_emmc_bus_wid == 9 || rtk_emmc_bus_wid == 5)
		emmc_port->rtflags |= RTKCR_FOPEN_LOG;

	if (!emmc_port->emmc_membase) {
		printk(KERN_INFO "---- Realtek EMMC Controller Driver probe fail - nomem ----\n\n");
		ret = -ENOMEM;
		goto out;
	}

	rtkemmc_hold_int_dec();       /* hold status interrupt */
	rtkemmc_clr_int_sta();
	ret = request_irq(irq, rtkemmc_irq, IRQF_SHARED, DRIVER_NAME, emmc_port);   //rtkemmc_interrupt
	if (ret) {
		printk(KERN_ERR "%s: cannot assign irq %d\n", DRIVER_NAME, irq);
		goto out;
	} else
		emmc_port->irq = irq;

	setup_timer(&emmc_port->timer, rtkemmc_timeout_timer, (unsigned long)emmc_port);
	emmc_port->ops->set_crt_muxpad(emmc_port);

	if (emmc_port->ops->reset_card)
		emmc_port->ops->reset_card(emmc_port);

	emmc_port->ops->chk_card_insert(emmc_port);

	platform_set_drvdata(pdev, mmc);
	
	ret = mmc_add_host(mmc);
	if (ret)
		goto out;

	sync(emmc_port);
	gCurrentBootMode = MODE_SDR;
	g_crinit=0;
	gPreventRetry=0;
	g_bResuming=0;
	g_bTuning=0;

#ifdef RTK_EMMC_HEALTH_REPORT
	mmc->wr_emmc_size_cnt = 0;
	mmc->remainder = 0;
#endif
	printk(KERN_NOTICE "%s: %s driver initialized\n",
	mmc_hostname(mmc), DRIVER_NAME);
	return 0;

out:
	if (emmc_port) {
		if (emmc_port->irq)
			free_irq(emmc_port->irq, emmc_port);

		if (emmc_port->emmc_membase)
			iounmap(emmc_port->emmc_membase);
		if (emmc_port->crt_membase)
			iounmap(emmc_port->crt_membase);
	}

	if (mmc)
		mmc_free_host(mmc);

	return ret;
}

static int __exit rtkemmc_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);
	MMCPRINTF("\n");

	//device_remove_file(&pdev->dev, &dev_attr_cr_send_cmd0);
	//device_remove_file(&pdev->dev, &dev_attr_cr_fast_RW);
	//device_remove_file(&pdev->dev, &dev_attr_em_open_log);
	device_remove_file(&pdev->dev, &dev_attr_emmc_info);

#ifdef CONFIG_MMC_RTKEMMC_HK_ATTR
	device_remove_file(&pdev->dev, &dev_attr_emmc_hacking);
#endif

	if (mmc) {
		struct rtkemmc_host *emmc_port = mmc_priv(mmc);
		flush_scheduled_work();
		rtkemmc_free_dma_buf(emmc_port);
		mmc_remove_host(mmc);
		if(!mmc){
			printk("eMMC host have removed.\n");
			mmc_host_local = NULL;
        	}
		free_irq(emmc_port->irq, emmc_port);

		del_timer_sync(&emmc_port->timer);
		iounmap(emmc_port->emmc_membase);
		iounmap(emmc_port->crt_membase);
		iounmap(emmc_port->sb2_membase);
		iounmap(emmc_port->mux_mis_membase);
                iounmap(emmc_port->iso_blk_membase);
                iounmap(emmc_port->m2tmx_membase);
#if defined(CONFIG_MMC_RTK_EMMC_PON)
		gpio_free(emmc_port->emmc_pon_gpio);
#endif
		release_resource(emmc_port->res);
		mmc_free_host(mmc);
	}
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static const struct of_device_id rtkemmc_ids[] = {
        { .compatible = "Realtek,rtk13xx-emmc" },
        { /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, rtkemmc_ids);

/**************************************************/
/* driver / device attache area                   */
/**************************************************/
static struct platform_driver rtkemmc_driver = {
	.probe      = rtkemmc_probe,
	.remove     = __exit_p(rtkemmc_remove),
	.driver     =
	{
		.name   = "rtkemmc",
		.owner  = THIS_MODULE,
		.of_match_table = of_match_ptr(rtkemmc_ids),
#ifdef CONFIG_PM
		.pm     = &rtk_dev_pm_ops
#endif
	},
	.shutdown   = rtkemmc_shutdown,
};
#if 0
static void rtkemmc_display_version (void)
{
	const __u8 *revision;
	const __u8 *date;
	const __u8 *time;
	char *running = (__u8 *)VERSION;

	strsep(&running, " ");
	strsep(&running, " ");
	revision = strsep(&running, " ");
	date = strsep(&running, " ");
	time = strsep(&running, " ");
	printk(BANNER " Rev:%s (%s %s)\n", revision, date, time);

#ifdef CONFIG_MMC_BLOCK_BOUNCE
	printk("%s: CONFIG_MMC_BLOCK_BOUNCE enable\n",DRIVER_NAME);
#else
	printk("%s: CONFIG_MMC_BLOCK_BOUNCE disable\n",DRIVER_NAME);
#endif

#ifdef CONFIG_SMP
	printk("%s: ##### CONFIG_SMP alert!! #####\n",DRIVER_NAME);
#else
	printk("%s: ##### CONFIG_SMP disable!! #####\n",DRIVER_NAME);
#endif
}
#endif
static int rtkemmc_set_bus_width(char * buf){
	/*
	get eMMC bus width setting by bootcode parameter, like below
	bootargs=console=ttyS0,115200 earlyprintk emmc_bus=8
	the keyword is "emmc_bus"
	the getted parameter is hex.
        example:
        emmc_bus=8
	*/

	rtkemmc_chk_param(&rtk_emmc_bus_wid,1,buf+1);
	printk("%s: setting bus width is %u-bit\n", DRIVER_NAME,rtk_emmc_bus_wid);
	return 0;
}
module_platform_driver(rtkemmc_driver);

MODULE_AUTHOR("Jim Tsai");
MODULE_DESCRIPTION("Realtek EMMC Host Controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtkemmc");

__setup("emmc_bus",rtkemmc_set_bus_width);
