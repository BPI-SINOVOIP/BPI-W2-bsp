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

/****************************************************************************************
 * Modifications									*
 * 1. In rtkemmc_probe, we use iomap to get device tree resource			*
 * 2. In rtkemmc_probe, we use lockapi to protect the DBG_PORT part			*
 * 3. Change the sg map and unmap in correct code section for reading easier		*
 * 4. Remove shutdown_protection definition						*
 * 5. Merge rtkemmc_ops.c to rtkemmc.c							*
 * 6. Add EMMC HS400 mode								*
 * 7. Add emmc down speed error handling once the HS200 tuning failed			*
 * 8. emmc info will be save under /sys/devices/platform/98012000.emmc/emmc_info	*
 * 9. mmc_fast_rw is for ACPU's usage							*
 * 10.Add 139x support									*
 ****************************************************************************************/
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
#include "reg_mmc.h"
#include "reg_iso.h"
#include "reg_sys.h"
#include "rtkemmc.h"
#include "mmc_debug.h"
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <asm/cacheflush.h>
#include <linux/pm_runtime.h>
//#include <soc/realtek/rtd129x_cpu.h>
#include <soc/realtek/rtk_cpu.h>
#include <soc/realtek/rtd129x_lockapi.h>

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
#define VERSION     "$Id: rtkemmc.c Kylin 2017-03-12 18:00 $"

#define DMA_ALLOC_LENGTH     (0x80000)
#define DESC_ALLOC_LENGTH   (1024*1024)
unsigned int GLOBAL=0;
//#define EMMC_PARAM_TEST
//#define DBG_PORT
//#define EMMC_DEBUG
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

#define UNSTUFF_BITS(resp,start,size)                                   \
	({                                                              \
		const int __size = size;                                \
		const u32 __mask = (__size < 32 ? 1 << __size : 0) - 1; \
		const int __off = 3 - ((start) / 32);                   \
		const int __shft = (start) & 31;                        \
		u32 __res;                                              \
                                                                        \
		__res = resp[__off] >> __shft;                          \
		if (__size + __shft > 32)                               \
			__res |= resp[__off-1] << ((32 - __shft) % 32); \
		__res & __mask;                                         \
	})

struct mmc_host * mmc_host_local = NULL;
static u32 rtk_emmc_bus_wid = 0;
static volatile struct backupRegs gRegTbl;
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

#ifndef CONFIG_ARCH_RTD16xx
#define SHA256
#endif

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
#ifdef CONFIG_ARCH_RTD129x
struct clk * clk_cr;
#endif

#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
#define MASK_DRTO 1
#endif

int rtkemmc_hs200_tuning(struct mmc_card *card);
int mmc_hs400_to_hs200(struct mmc_card *card);
int mmc_select_hs200(struct mmc_card *card);
int mmc_select_ddr50(struct mmc_card *card);
int rtkemmc_switch(struct mmc_card *card, u8 acc_mod, u8 index, u8 value, u8 cmd_set);
#ifdef EMMC_DEBUG
static void rtkemmc_dump_registers(struct rtkemmc_host *emmc_port);
#endif
static void rtkemmc_request(struct mmc_host *host, struct mmc_request *mrq);
static int rtkemmc_get_ro(struct mmc_host *mmc);
static void rtkemmc_set_ios(struct mmc_host *host, struct mmc_ios *ios);

static void set_cmd_info(struct mmc_card *card,struct mmc_command * cmd,
struct sd_cmd_pkt * cmd_info,u32 opcode,u32 arg,u8 rsp_para);

static int rtkemmc_stop_transmission(struct mmc_card *card,int bIgnore);
static int rtkemmc_send_status(struct mmc_card *card,u8 * state,u8 divider,int bIgnore);
static int rtkemmc_wait_status(struct mmc_card *card,u8 state,u8 divider,int bIgnore);

static void rtkemmc_set_wrapper_div(struct rtkemmc_host *emmc_port,u8 level);
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
static void rtkemmc_backup_registers(struct rtkemmc_host *emmc_port);
static void rtkemmc_restore_registers(struct rtkemmc_host *emmc_port);
static void rtkemmc_set_ip_div(struct rtkemmc_host *emmc_port,u32 set_div);
static void rtkemmc_set_freq(struct rtkemmc_host *emmc_port, u32 freq);
int error_handling(struct rtkemmc_host *emmc_port, unsigned int cmd_idx, unsigned int bIgnore);
int polling_to_tran_state(struct rtkemmc_host *emmc_port,int cmd_idx,int bIgnore);
static int SD_SendCMDGetRSP(struct sd_cmd_pkt * cmd_info,int bIgnore);
static int SD_SendCMDGetRSP_Cmd(struct sd_cmd_pkt *cmd_info,int bIgnore);
void rtkemmc_set_pad_driving(struct rtkemmc_host *emmc_port, u32 clk_drv, u32 cmd_drv, u32 data_drv, u32 ds_drv);
static int wait_done_timeout(struct rtkemmc_host *emmc_port, volatile u32 *addr, u32 mask, u32 value,const char *string);
static void rtkemmc_set_bits(struct rtkemmc_host *emmc_port,u32 set_bit);
static int SD_Stream_Cmd(u16 cmdcode,struct sd_cmd_pkt *cmd_info, unsigned int bIgnore);
static void rtkemmc_dqs_tuning(struct mmc_host *host);
int rtkemmc_select_timing(struct mmc_card *card);
void rtkemmc_select_card_type(struct mmc_card *card);
void down_speed_handling(struct rtkemmc_host *emmc_port);

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
	.backup_regs    = rtkemmc_backup_registers,
	.restore_regs   = rtkemmc_restore_registers,
};


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
void sync(struct rtkemmc_host *emmc_port)
{
	dmb(sy);
    	writel(0x0, emmc_port->sb2_membase+0x20);
    	dmb(sy);
}

static int rtkemmc_get_ro(struct mmc_host *mmc)
{
	return 0;
}

static int rtkemmc_prepare_hs400_tuning(struct mmc_host *host, struct mmc_ios *ios)
{
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	struct rtkemmc_host *emmc_port;
        emmc_port = mmc_priv(host);
	printk(KERN_ERR "Prepare HS400 mode...\n");
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_prepare_hs400_tuning"));
#endif
	rtkemmc_writel(0x88 ,emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("rtkemmc_prepare_hs400_tuning"));
#endif
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

void print_reg_sts(u32 cmd_idx, u32 rintsts)
{
	printk(KERN_ERR "=====================================================\n");
	printk(KERN_ERR "g_bTuning=%d cmd_idx 0x%08x, op_code 0x%02x(%d)\n",g_bTuning, cmd_idx, CMD_IDX_MASK(cmd_idx), CMD_IDX_MASK(cmd_idx));
	if( rintsts & INT_STS_EBE ) {           printk(KERN_ERR "bit 15: Enb bit error(R), No CRC(W)\n");       }
	if( rintsts & INT_STS_ACD ) {           printk(KERN_ERR "bit 14: Auto commanddone\n");  }
	if( rintsts & INT_STS_SBE_BCI ) {       printk(KERN_ERR "bit 13: Start Bit Error, Busy Clear Int.\n");  }
	if( rintsts & INT_STS_HLE ) {           printk(KERN_ERR "bit 12: Hardware locked write error\n");       }
	if( rintsts & INT_STS_FRUN ) {          printk(KERN_ERR "bit 11: FIFIL underrun/overrun\n");    }
	if( rintsts & INT_STS_HTO ) {           printk(KERN_ERR "bit 10: Data startvation by host timeout(HTO)\n");     }
	if( rintsts & INT_STS_DRTO_BDS ) {      printk(KERN_ERR "bit  9: Data read timeout\n"); }
	if( rintsts & INT_STS_RTO_BAR ) {       printk(KERN_ERR "bit  8: Response timeout\n");  }
	if( rintsts & INT_STS_DCRC ) {          printk(KERN_ERR "bit  7: Data CRC error\n");    }
	if( rintsts & INT_STS_RCRC ) {          printk(KERN_ERR "bit  6: Response CRC error\n");        }
	if( rintsts & INT_STS_RXDR ) {          printk(KERN_ERR "bit  5: Receive FIFO data request(RXDT)\n");   }
	if( rintsts & INT_STS_TXDR ) {          printk(KERN_ERR "bit  4: Transmit FIFO data request(TXDR)\n");  }
	if( rintsts & INT_STS_DTO ) {           printk(KERN_ERR "bit  3: Data Transfer over(DTO)\n");   }
	if( rintsts & INT_STS_CD ) {            printk(KERN_ERR "bit  2: Command done(CD)\n");  }
	if( rintsts & INT_STS_RE ) {            printk(KERN_ERR "bit  1: Response error\n");    }
	if( rintsts & INT_STS_CRD ) {           printk(KERN_ERR "bit  0: Card detect(CD)\n");   }
	printk(KERN_ERR "=====================================================\n");
}

void print_ip_desc(struct rtkemmc_host *emmc_port)
{ 
	unsigned int bytecnt = 0, desc_cnt = 0, i = 0;
	unsigned int paddr_base = emmc_port->desc_paddr;

	printk(KERN_ERR "------------------------------>\n");
	printk(KERN_ERR "EMMC IP_DESC0 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC0));
	printk(KERN_ERR "EMMC IP_DESC1 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC1));
	printk(KERN_ERR "EMMC IP_DESC2 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC2));
	printk(KERN_ERR "EMMC IP_DESC3 = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_IP_DESC3));

	printk(KERN_ERR "EMMC BYTCNT = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_BYTCNT));
	printk(KERN_ERR "EMMC CMDARG = 0x%08x\n", readl(emmc_port->emmc_membase+EMMC_CMDARG));
	printk(KERN_ERR "EMMC DBADDR = 0x%08x\n------------------------------>\n", readl(emmc_port->emmc_membase+EMMC_DBADDR));

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
}

void mmc_host_reset(struct rtkemmc_host *emmc_port)
{
//	unsigned long flags2;

	MMCPRINTF("%s : \n", __func__);
	//rtk_lockapi_lock2(flags2, _at_("mmc_host_reset"));
	rtkemmc_writel(0x00000081, emmc_port->emmc_membase + EMMC_BMOD);
	isb();
	sync(emmc_port);
	//rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_CTRL);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000000, emmc_port->emmc_membase + EMMC_CTRL);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_PWREN);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffce, emmc_port->emmc_membase + EMMC_INTMASK);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0xffffffff, emmc_port->emmc_membase + EMMC_RINTSTS);
	isb();
	sync(emmc_port);
	//rtkemmc_writel(0x00000010, emmc_port->emmc_membase + EMMC_CTRL);
	isb();
	sync(emmc_port);

	rtkemmc_writel(0x00000080, emmc_port->emmc_membase + EMMC_CLKDIV);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_CLKSRC);
	isb();
	sync(emmc_port);
	//rtkemmc_writel(0x0001ffff, emmc_port->emmc_membase + EMMC_CLKENA);
	rtkemmc_writel(0x00010001, emmc_port->emmc_membase + EMMC_CLKENA);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0xa0200000, emmc_port->emmc_membase + EMMC_CMD);
	isb();
	sync(emmc_port);

	MMCPRINTF(KERN_INFO "1 EMMC_TMOUT = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_TMOUT));
	rtkemmc_writel(0xffffff40, (volatile void*)(emmc_port->emmc_membase + EMMC_TMOUT));
	isb();
	sync(emmc_port);
	MMCPRINTF(KERN_INFO "2 EMMC_TMOUT = 0x%08x \n",  (volatile void*)readl(emmc_port->emmc_membase + EMMC_TMOUT));

	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_CTYPE);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0001007f, emmc_port->emmc_membase + EMMC_FIFOTH);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000010, emmc_port->emmc_membase + EMMC_CTRL);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000080, emmc_port->emmc_membase + EMMC_BMOD);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffce, emmc_port->emmc_membase + EMMC_INTMASK);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00600000, emmc_port->emmc_membase + EMMC_DBADDR);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_IDINTEN);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffff, emmc_port->emmc_membase + EMMC_RINTSTS);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_UHSREG);
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000001, emmc_port->emmc_membase + EMMC_CARD_THR_CTL);	//boot code 0x01000001
	isb();
	sync(emmc_port);
	//rtk_lockapi_unlock2(flags2, _at_("mmc_host_reset"));

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
	printk(KERN_ERR "[%s] Exit %s\n",DRIVER_NAME,__func__);

	return ret;
}

static const struct dev_pm_ops rtk_dev_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(rtkemmc_suspend, rtkemmc_resume)
};
#endif

void card_stop(struct rtkemmc_host *emmc_port)
{
#ifdef CONFIG_ARCH_RTD129x
        unsigned long flags2;
	volatile u32 reg;
#endif
#ifdef EMMC_DEBUG
        printk(KERN_ERR "card_stop - start\n");
#endif
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_lock2(flags2, _at_("card_stop2"));
#endif
        rtkemmc_backup_registers(emmc_port);
	reset_control_assert(rstc_emmc);
        sync(emmc_port);

	clk_disable_unprepare(clk_en_emmc);
	clk_disable_unprepare(clk_en_emmc_ip);
	sync(emmc_port);

#ifdef CONFIG_ARCH_RTD129x
	//kylin A01 and HS400 mode need to reset this dummy register
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 &&
		(get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_B00 || (emmc_port->mmc->caps2 & MMC_CAP2_HS400_1_8V)==MMC_CAP2_HS400_1_8V)) {
                reg = readl(emmc_port->crt_membase + SYS_DUMMY);
                isb();
                sync(emmc_port);
                rtkemmc_writel(reg&0xfffffffd, emmc_port->crt_membase + SYS_DUMMY);
                isb();
                sync(emmc_port);
        }
#else
	//1395 HS400 mode TBD
#endif

	reset_control_deassert(rstc_emmc);
        sync(emmc_port);

	clk_prepare_enable(clk_en_emmc);
        clk_prepare_enable(clk_en_emmc_ip);
        sync(emmc_port);

#ifdef CONFIG_ARCH_RTD129x
	//kylin A01 and HS400 mode need to reset this dummy register
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 &&
		(get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_B00 || (emmc_port->mmc->caps2 & MMC_CAP2_HS400_1_8V)==MMC_CAP2_HS400_1_8V)) {
                reg = readl(emmc_port->crt_membase + SYS_DUMMY);
                isb();
                sync(emmc_port);
                rtkemmc_writel(reg | 0x00000002, emmc_port->crt_membase + SYS_DUMMY);
                isb();
                sync(emmc_port);
        }
#else
	//1395 HS400 mode TBD
#endif

#ifdef CONFIG_ARCH_RTD129x
	//1395 does not need to toggle this register
        if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
                rtkemmc_writel( readl(emmc_port->emmc_membase + EMMC_DUMMY_SYS) ^ 0x40000000, emmc_port->emmc_membase + EMMC_DUMMY_SYS);
                isb();
                sync(emmc_port);
                udelay(200);
        }
#endif

#if defined(CONFIG_ARCH_RTD129x)
	rtkemmc_writel(gRegTbl.emmc_mux_pad0, emmc_port->emmc_membase + EMMC_muxpad0);
        rtkemmc_writel(gRegTbl.emmc_mux_pad1, emmc_port->emmc_membase + EMMC_muxpad1);
        rtkemmc_writel(gRegTbl.emmc_pfunc_nf1, emmc_port->emmc_membase + EMMC_PFUNC_NF1);
        rtkemmc_writel(gRegTbl.emmc_pfunc_cr, emmc_port->emmc_membase + EMMC_PFUNC_CR);
        rtkemmc_writel(gRegTbl.emmc_pdrive_nf1, emmc_port->emmc_membase + EMMC_PDRIVE_NF1);
        rtkemmc_writel(gRegTbl.emmc_pdrive_nf2, emmc_port->emmc_membase + EMMC_PDRIVE_NF2);
        rtkemmc_writel(gRegTbl.emmc_pdrive_nf3, emmc_port->emmc_membase + EMMC_PDRIVE_NF3);
        rtkemmc_writel(gRegTbl.emmc_pdrive_nf4, emmc_port->emmc_membase + EMMC_PDRIVE_NF4);
/*	//139x and 16xx does not need to restore the pad mux part, only 129x needs to take this action
#elif defined(CONFIG_ARCH_RTD139x)
	rtkemmc_writel(gRegTbl.iso_muxpad4,emmc_port->iso_muxpad + ISO_muxpad4);
	rtkemmc_writel(gRegTbl.Pfunc_emmc0,emmc_port->iso_muxpad + pfunc_emmc0);
	rtkemmc_writel(gRegTbl.Pfunc_emmc1,emmc_port->iso_muxpad + pfunc_emmc1);
	rtkemmc_writel(gRegTbl.Pfunc_emmc2,emmc_port->iso_muxpad + pfunc_emmc2);
	rtkemmc_writel(gRegTbl.Pfunc_emmc3,emmc_port->iso_muxpad + pfunc_emmc3);
	rtkemmc_writel(gRegTbl.Pfunc_emmc4,emmc_port->iso_muxpad + pfunc_emmc4);
	rtkemmc_writel(gRegTbl.Pfunc_emmc5,emmc_port->iso_muxpad + pfunc_emmc5);
*/
#endif

#ifdef CONFIG_ARCH_RTD129x
        rtkemmc_writel(gRegTbl.emmc_pdrive_cr0, emmc_port->emmc_membase + EMMC_PDRIVE_CR0);
        rtkemmc_writel(gRegTbl.emmc_pdrive_cr1, emmc_port->emmc_membase + EMMC_PDRIVE_CR1);
        rtkemmc_writel(gRegTbl.emmc_pdrive_sdio, emmc_port->emmc_membase + EMMC_PDRIVE_SDIO);
        rtkemmc_writel(gRegTbl.emmc_pdrive_sdio1, emmc_port->emmc_membase + EMMC_PDRIVE_SDIO1);
#endif
        rtkemmc_writel(gRegTbl.emmc_ckgen_ctl, emmc_port->emmc_membase + EMMC_CKGEN_CTL);
        isb();
        sync(emmc_port);
	mmc_host_reset(emmc_port);

        rtkemmc_writel(gRegTbl.emmc_ctype, emmc_port->emmc_membase + EMMC_CTYPE);
        rtkemmc_writel(gRegTbl.emmc_uhsreg, emmc_port->emmc_membase + EMMC_UHSREG);
        rtkemmc_writel(gRegTbl.emmc_ddr_reg, emmc_port->emmc_membase + EMMC_DDR_REG);
        rtkemmc_writel(gRegTbl.emmc_card_thr_ctl, emmc_port->emmc_membase + EMMC_CARD_THR_CTL);
	if(gCurrentBootMode == MODE_HS400) {
		rtkemmc_writel(gRegTbl.emmc_dqs_ctrl1 | 0x80, emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#if defined(CONFIG_ARCH_RTD139x)
		rtkemmc_writel(0x94, emmc_port->emmc_membase+0x530); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x534); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x538); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x53c); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x540); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x544); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x548 ); //dqs dly tap
		rtkemmc_writel(0x14, emmc_port->emmc_membase+0x54c); //dqs dly tap
		rtkemmc_writel(0xff00, emmc_port->emmc_membase+0x50c); //dqs dly tap
		rtkemmc_writel(0x94, emmc_port->emmc_membase+0x558);
		rtkemmc_writel(0x2, emmc_port->emmc_membase+0x550);
#elif defined(CONFIG_ARCH_RTD16xx)
		rtkemmc_writel(0x80, emmc_port->emmc_membase+0x530); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x534); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x538); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x53c); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x540); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x544); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x548 ); //dqs dly tap
		rtkemmc_writel(0x0, emmc_port->emmc_membase+0x54c); //dqs dly tap
		rtkemmc_writel(0xff00, emmc_port->emmc_membase+0x50c); //dqs dly tap
		rtkemmc_writel(0x80, emmc_port->emmc_membase+0x558);
		rtkemmc_writel(0x2, emmc_port->emmc_membase+0x550);
#endif
	}
	else {
		rtkemmc_writel(gRegTbl.emmc_dqs_ctrl1, emmc_port->emmc_membase + EMMC_DQS_CTRL1);
	}
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
        writel(gRegTbl.emmc_drto_mask_ori, emmc_port->emmc_membase + EMMC_DUMMY_SYS);	//emmc timeout mechanism enable/disable
	writel(gRegTbl.emmc_other1, emmc_port->emmc_membase + EMMC_OTHER1);	//emmc L4 gated setting restored
#endif
        isb();
        sync(emmc_port);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_CLKENA); // 0x10, clk enable, disable clock
        isb();
        sync(emmc_port);

        rtkemmc_writel(0xa0202000, emmc_port->emmc_membase + EMMC_CMD); // 0x10, clk enable, disable clock
        isb();
        sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_unlock2(flags2, _at_("card_stop"));
#endif
	// 0x2c, wait for CIU to take the command
        wait_done_timeout(emmc_port, emmc_port->emmc_membase + EMMC_CMD, 0x80000000, 0, __func__);

#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_lock2(flags2, _at_("card_stop"));
#endif
        rtkemmc_writel(gRegTbl.emmc_clk_div, emmc_port->emmc_membase + EMMC_CLKDIV);
        isb();
        sync(emmc_port);

        rtkemmc_writel(0xa0202000, emmc_port->emmc_membase + EMMC_CMD);  // 0x2c = start_cmd, upd_clk_reg_only, wait_prvdata_complete
        isb();
        sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_unlock2(flags2, _at_("card_stop"));
#endif
	wait_done_timeout(emmc_port, emmc_port->emmc_membase + EMMC_CMD, 0x80000000,0, __func__);
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_lock2(flags2, _at_("card_stop"));
#endif
        rtkemmc_writel(0x10001, emmc_port->emmc_membase + EMMC_CLKENA); // 0x10, clk enable, disable clock
        isb();
        sync(emmc_port);

        rtkemmc_writel(0xa0202000, emmc_port->emmc_membase + EMMC_CMD);  // 0x2c = start_cmd, upd_clk_reg_only, wait_prvdata_complete
        isb();
        sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_unlock2(flags2, _at_("card_stop"));
#endif
        // 0x2c, wait for CIU to take the command
        wait_done_timeout(emmc_port, emmc_port->emmc_membase + EMMC_CMD, 0x80000000,0, __func__);
#ifdef EMMC_DEBUG
        printk(KERN_ERR "card_stop - end\n");
#if defined(CONFIG_ARCH_RTD129x)
        rtk_lockapi_lock2(flags2, _at_("card_stop"));
        printk (KERN_ERR "muxpad1- 0x%08x\n", readl(emmc_port->emmc_membase + EMMC_muxpad1));
        rtk_lockapi_unlock2(flags2, _at_("card_stop"));
#elif defined(CONFIG_ARCH_RTD139x)
	printk (KERN_ERR "muxpad4- 0x%08x\n", readl(emmc_port->iso_muxpad + ISO_muxpad4));
#elif defined(CONFIG_ARCH_RTD16xx)
	printk (KERN_ERR "m2tmx_muxpad0- 0x%08x\n", readl(emmc_port->m2tmx + m2tmx_muxpad0));
#endif
#endif
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

	if(err)
		mmcmsg3(KERN_WARNING "%s: MMC_SEND_STATUS fail\n",DRIVER_NAME);
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
	struct mmc_host *host = emmc_port->mmc;
	unsigned char *crd_tmp_buffer=NULL;
	struct mmc_data *data=NULL;
	struct mmc_command *cmd=NULL;
	int i=0;
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
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
#ifdef CONFIG_ARCH_RTD139x
	if(get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01) {
		if(readl(emmc_port->emmc_membase + EMMC_BYTCNT) == readl(emmc_port->emmc_membase + EMMC_TBBCNT))
			writel(0x2,emmc_port->emmc_membase+EMMC_ISR);
	}
	else {
		if (readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT)
			writel(0x2,emmc_port->emmc_membase+EMMC_ISR);
	}
#else
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_send_cmd18"));
#endif
	if (readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT)
		writel(0x2,emmc_port->emmc_membase+EMMC_ISR);
#ifdef CONFIG_ARCH_RTD129x
        rtk_lockapi_unlock2(flags2, _at_("rtkemmc_send_cmd18"));
#endif
#endif
	if (ret_err) {
#ifdef EMMC_DEBUG
		printk(KERN_ERR "Tuning rx cmd 18 err: size=%d, EMMC_RINTSTS=0x%x, EMMC_STATUS=0x%x\n", size, readl(emmc_port->emmc_membase + EMMC_RINTSTS),readl(emmc_port->emmc_membase + EMMC_STATUS));
#endif
		udelay(200);
		if((readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0x4000)==0)
			rtkemmc_stop_transmission(host->card, 1);
		card_stop(emmc_port);
		polling_to_tran_state(emmc_port,MMC_READ_MULTIPLE_BLOCK,1);
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

int rtkemmc_send_cmd25(struct rtkemmc_host *emmc_port,int size, unsigned long addr)
{
        int ret_err=0,i=0;
        struct sd_cmd_pkt cmd_info;
        struct mmc_host *host = emmc_port->mmc;
        char *crd_tmp_buffer=NULL;
        struct mmc_data *data=NULL;
        struct mmc_command *cmd=NULL;
//      unsigned long flags=0;
//	unsigned long flags2;
        memset(&cmd_info, 0x00, sizeof(struct sd_cmd_pkt));

        crd_tmp_buffer = (unsigned char *) emmc_port->dma_paddr;
//	printk(KERN_ERR "crd_tmp_buffer=%p, emmc_port->dma_paddr=%p, gddr_dma_org=%p\n",crd_tmp_buffer,emmc_port->dma_paddr,gddr_dma_org);
        if (crd_tmp_buffer == NULL)
        {
                printk(KERN_ERR "%s,%s : crd_ext_csd == NULL\n",DRIVER_NAME,__func__);
                return -5;
        }

        for(i=0;i<(size/4);i++)
        {
		if(GLOBAL==0x80000000) GLOBAL=0;
		else GLOBAL++;
		*(u32 *)(gddr_dma_org+(i*4)) = GLOBAL;
        }
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
#ifdef EMMC_DEBUG
		printk(KERN_ERR "Tuning tx cmd 25 err: size=%d, EMMC_RINTSTS=0x%x, EMMC_STATUS=0x%x\n",size, readl(emmc_port->emmc_membase + EMMC_RINTSTS),readl(emmc_port->emmc_membase + EMMC_STATUS));
#endif
		wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x2f0, 0x0, __func__);          //card is not busy
		if((readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0x4000)==0)
			rtkemmc_stop_transmission(host->card, 1);
		card_stop(emmc_port);
                polling_to_tran_state(emmc_port,MMC_WRITE_MULTIPLE_BLOCK,1);
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
                u32 reg_val=0;
#if defined(CONFIG_ARCH_RTD129x)
                printk(KERN_ERR "muxpad0=0x%x, before emmc do hw reset...\n",readl(emmc_port->emmc_membase + EMMC_muxpad0));
                reg_val = readl(emmc_port->emmc_membase + EMMC_muxpad0);
                reg_val &= ~0xFFFF0C3C;
                reg_val |= 0xaaaa0828;
                rtkemmc_writel(reg_val, emmc_port->emmc_membase+EMMC_muxpad0);
                mdelay(1);
                printk(KERN_ERR "muxpad0=0x%x, emmc do really hw reset...\n",readl(emmc_port->emmc_membase + EMMC_muxpad0));
#elif defined(CONFIG_ARCH_RTD139x)
		printk(KERN_ERR "isopad4=0x%x, before emmc do hw reset...\n",readl(emmc_port->iso_muxpad + ISO_muxpad4));
		reg_val = readl(emmc_port->iso_muxpad + ISO_muxpad4);
		reg_val &= ~0x3;
		reg_val |= 0x2;
		rtkemmc_writel(reg_val, emmc_port->iso_muxpad + ISO_muxpad4);
		mdelay(1);
		printk(KERN_ERR "isopad4=0x%x, emmc do really hw reset...\n",readl(emmc_port->iso_muxpad + ISO_muxpad4));
#elif defined(CONFIG_ARCH_RTD16xx)
		printk(KERN_ERR "m2tmx_muxpad0=0x%x, before emmc do hw reset...\n",readl(emmc_port->m2tmx + m2tmx_muxpad0));
		reg_val = readl(emmc_port->m2tmx + m2tmx_muxpad0);
		reg_val &= 0xfe000001;  //bit 1 - bit 24 set 0x10 0x10 0x10...0x10
		reg_val |= 0x01555554;
		rtkemmc_writel(reg_val, emmc_port->m2tmx + m2tmx_muxpad0);
		mdelay(1);
		printk(KERN_ERR "m2tmx_muxpad0=0x%x, after emmc do hw reset...\n",readl(emmc_port->m2tmx + m2tmx_muxpad0));
#endif
                writel(0x0, emmc_port->emmc_membase+0x78);
                mdelay(1);
                writel(0x1, emmc_port->emmc_membase+0x78);
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

        if (mode == MODE_HS400 || mode == MODE_DDR)
                range = 0x10;
        else
                range = 0x20;

	if(hs400_to_hs200_flag==true && (emmc_port->tx_tuning && emmc_port->rx_tuning)) {
		hs400_to_hs200_flag=false;
		phase(emmc_port, HS200_TX, HS200_RX);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
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
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
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
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
                sync(emmc_port);
        }
        else {
                phase(emmc_port, VP0_saved, VP1_saved); //VP0, VP1 phase
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
                sync(emmc_port);
		printk(KERN_INFO "Inherit bootcode tuning phase: TX=0x%x, RX=0x%x\n", VP0_saved, VP1_saved);
                return;
        }
#else
	phase(emmc_port, 0, 0); //VP0, VP1 phase
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
	mdelay(5);
        sync(emmc_port);
#endif
/*	if(emmc_port->tx_tuning || emmc_port->rx_tuning)
                card_stop(emmc_port);*/

	if (emmc_port->tx_tuning) {
		if (mode == MODE_DDR && flag==1)
			printk(KERN_ERR "Start DDR50 TX Tuning:\n");
		else if (mode == MODE_HS400 && flag==1)
			printk(KERN_ERR "Start HS400 TX Tuning: \n");
		else if(flag==1)
			printk(KERN_ERR "Start HS200 TX Tuning:\n");
                for(i=0;i<range;i++) {
                        phase(emmc_port, i, 0xff);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
			udelay(1);
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
#ifdef DEBUG
                        printk("phase =0x%x \n", i);
#endif

                        if(rtkemmc_send_cmd13(emmc_port, &state) != 0)
                                TX_window= TX_window&(~(1<<i));
                        else
                                TX_window= TX_window|((1<<i));
                }
		TX_best = search_best(TX_window, range);
		if(flag==1)printk(KERN_ERR "TX_WINDOW = 0x%08x TX_best=0x%x\n", TX_window, TX_best);
                phase(emmc_port, TX_best, 0xff);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
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
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
			udelay(1);
			writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
#ifdef DEBUG
                        printk("phase =0x%x \n", i);
#endif
                        if(rtkemmc_send_cmd18(emmc_port, 1024, 0x100) != 0)
                                RX_window= RX_window&(~(1<<i));
                        else
                                RX_window= RX_window|((1<<i));
                }
		RX_best = search_best(RX_window, range);
                if(flag==1)printk(KERN_ERR "RX_WINDOW = 0x%08x RX_best=0x%x\n", RX_window,RX_best);
                phase(emmc_port, 0xff, RX_best);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
		suspend_VP1 = RX_best;
        }
	if (emmc_port->tx_tuning) {
		TX1_window= TX_window;
		if (mode == MODE_DDR && flag==1)
			printk(KERN_ERR "Start DDR50 TX Tuning2:\n");
		else if (mode == MODE_HS400 && flag==1)
			printk(KERN_ERR "Start HS400 TX Tuning2:\n");
		else if(flag==1)
			printk(KERN_ERR "Start HS200 TX Tuning2:\n");
                for(i=0;i<range;i++) {
			if(((TX_window>>i)&1)==1) {
				phase(emmc_port, i, 0xff);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
				writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
				udelay(1);
				writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
#ifdef DEBUG
				printk("phase =0x%x \n", i);
#endif
				if(rtkemmc_send_cmd25(emmc_port, 1024,0xfe) != 0)
					TX1_window= TX1_window&(~(1<<i));
			}
		}
		TX1_best = search_best(TX1_window, range);
		if(flag==1)printk(KERN_ERR "TX1_WINDOW = 0x%08x TX1_best=0x%x\n", TX1_window,TX1_best);
                phase(emmc_port, TX1_best, 0xff);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
		suspend_VP0 = TX1_best;
        }
	sync(emmc_port);
/*	if(emmc_port->tx_tuning || emmc_port->rx_tuning) {
                card_stop(emmc_port);
		polling_to_tran_state(emmc_port,MMC_WRITE_MULTIPLE_BLOCK,1);
	}*/
}

static int mmc_Tuning_SDR50(struct rtkemmc_host *emmc_port)
{
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_SDR;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0x57); //100Mhz
	rtkemmc_set_ip_div(emmc_port, EMMC_CLOCK_DIV_2); // 100MHZ/2 = 50MHZ

	if (pddrive_nf_s0[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s0[1], pddrive_nf_s0[2], pddrive_nf_s0[3], pddrive_nf_s0[4]);
	else {
#ifdef CONFIG_ARCH_RTD129x
		rtkemmc_set_pad_driving(emmc_port,0x33, 0x33, 0x33, 0x33);
#else
		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);
#endif
	}
	sync(emmc_port);
	udelay(100);
	up_write(&cr_rw_sem);

	return 0;
}

static int mmc_Tuning_DDR50(struct rtkemmc_host *emmc_port, u32 mode)
{
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_DDR;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0x2a);  //100MMhz
	rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_NON);
	sync(emmc_port);
	udelay(100);
	if (pddrive_nf_s1[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s1[1], pddrive_nf_s1[2], pddrive_nf_s1[3], pddrive_nf_s1[4]);
        else {
#ifdef CONFIG_ARCH_RTD129x
		rtkemmc_set_pad_driving(emmc_port,0x33, 0x33, 0x33, 0x33);
#else
		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);
#endif
	}
	if(emmc_port->tx_tuning && emmc_port->rx_tuning) {	//device tree set kernel tuning for DDR50
		rtkemmc_phase_tuning(emmc_port,mode,1);
		sync(emmc_port);
		mdelay(10);
	}
	else {
		phase(emmc_port, 0x8, 0x9);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
		udelay(1);
		writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
	}
	up_write(&cr_rw_sem);

	return 0;
}

static int mmc_Tuning_HS200(struct rtkemmc_host *emmc_port,u32 mode)
{
	MMCPRINTF("%s \n", __func__);

	down_write(&cr_rw_sem);
        if (!g_bResuming)
                gCurrentBootMode = MODE_HS200;
        MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);

	rtkemmc_set_freq(emmc_port, 0xa6); //200Mhz
	rtkemmc_set_ip_div(emmc_port, EMMC_CLOCK_DIV_NON); // 200MHZ/1 = 200MHZ
#ifdef EMMC_PARAM_TEST
	if (readl(emmc_port->misc_membase + MISC_DUMMY2) != 0xffffffff){
		clk_drv = (readl(emmc_port->misc_membase + MISC_DUMMY2) & 0xff000000) >> 24;
		cmd_drv = (readl(emmc_port->misc_membase + MISC_DUMMY2) & 0x00ff0000) >> 16;
		data_drv = (readl(emmc_port->misc_membase + MISC_DUMMY2) & 0x0000ff00) >> 8;
		ds_drv = (readl(emmc_port->misc_membase + MISC_DUMMY2) & 0x000000ff);
		printk(KERN_ERR RED_BOLD"clk_drv = 0x%02x, cmd_drv = 0x%02x, data_drv = 0x%02x, ds_drv = 0x%02x"RESET, clk_drv, cmd_drv, data_drv, ds_drv);
		rtkemmc_set_pad_driving(emmc_port,clk_drv, cmd_drv, data_drv, ds_drv);
	}
	else {
#endif
		if (pddrive_nf_s2[0] != 0 )
			rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s2[1], pddrive_nf_s2[2], pddrive_nf_s2[3], pddrive_nf_s2[4]);
		else {
#ifdef CONFIG_ARCH_RTD129x
			rtkemmc_set_pad_driving(emmc_port,0xbb, 0xbb, 0xbb, 0xbb);
#else
			rtkemmc_set_pad_driving(emmc_port,0x4, 0x4, 0x4, 0x4);
#endif
		}
#ifdef EMMC_PARAM_TEST
	}
#endif

	rtkemmc_phase_tuning(emmc_port,mode,1);
	sync(emmc_port);
	mdelay(10);
	up_write(&cr_rw_sem);
	printk(KERN_ERR "HS200: final phase=0x%x\n", readl(emmc_port->crt_membase + SYS_PLL_EMMC1));

	return 0;
}

static int mmc_Tuning_HS400(struct rtkemmc_host *emmc_port,u32 mode)
{
        MMCPRINTF("%s \n", __func__);
	down_write(&cr_rw_sem);
	if (!g_bResuming)
		gCurrentBootMode = MODE_HS400;
	MMCPRINTF("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);
	rtkemmc_set_freq(emmc_port, 0x70); //200Mhz
	rtkemmc_set_ip_div(emmc_port, EMMC_CLOCK_DIV_NON); // 200MHZ/1 = 200MHZ

	if (pddrive_nf_s3[0] != 0 )
		rtkemmc_set_pad_driving(emmc_port, pddrive_nf_s3[1], pddrive_nf_s3[2], pddrive_nf_s3[3], pddrive_nf_s3[4]);
	else {
#ifdef CONFIG_ARCH_RTD129x
		rtkemmc_set_pad_driving(emmc_port,0xff, 0x99, 0xaa, 0x33);
#else
		rtkemmc_set_pad_driving(emmc_port,0x7, 0x2, 0x3, 0x0);
#endif
	}
	rtkemmc_phase_tuning(emmc_port,mode,1);
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
	rtkemmc_set_wrapper_div(emmc_port, 0);

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
	rtkemmc_send_cmd25(emmc_port,DMA_ALLOC_LENGTH, emmc_blk_addr);
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
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	unsigned int bitmap=0;
	unsigned int max=0;

        emmc_port = mmc_priv(host);
	mdelay(2);

	if(suspend == 1)
	{
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		if(emmc_port->dqs_tuning == 1) {
                	writel(0x80 | suspend_dqs,emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		}
		else {
			writel(0x80 | dqs_saved, emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		}
                printk(KERN_ERR "suspend/resume: restore DQS=0x%x\n", readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
#ifdef CONFIG_ARCH_RTD129x
                rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		suspend = 0;
		return;
	}

#ifdef DQS_INHERITED
        if(emmc_port->dqs_tuning == 0) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		writel(0x80 | dqs_saved, emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		printk(KERN_ERR "Inherit bootcode dqs: DQS=0x%x\n", readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		set_RTK_initial_flag(1);
		return;
	}
#endif
	down_write(&cr_rw_sem);
	g_bTuning = 1;

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
	printk(KERN_ERR "emmc_real_blk_size=0x%lx, emmc_set_blk_size=0x%lx, dqs_tuning_blk_addr=0x%lx\n",emmc_real_size,emmc_set_size,dqs_tuning_blk_addr);

#ifdef SHA256
	printk(KERN_ERR "[EMMC] SHA256 is enabled for dqs comparison!!!\n");
	if(!compare3)
		compare3 = dma_alloc_coherent(emmc_port->dev, 32, &compare3_phy_addr ,GFP_KERNEL);
	if(!compare4)
		compare4 = dma_alloc_coherent(emmc_port->dev, 32, &compare4_phy_addr ,GFP_KERNEL);
#endif
	for(i=0; i<0x20; i++) {
		if(j>=5)			//must be more than 5 continuous tap sample point
			max = j;
		if(j==0 && max!=0)	//find the max tap length
			break;
#ifdef EMMC_DEBUG
		printk(KERN_ERR "DQS windows tuning: i=0x%x\n",i<<1);
#endif
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		writel(0x80|(i<<1),emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
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
		printk(KERN_ERR "Cannot find a proper dqs window...\n");
		printk(KERN_ERR "dqs tap bitmap= 0x%x\n", bitmap);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		writel(0x88,emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
	}
	else {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
		writel(0x80|(readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1)-((max/2)*2)),emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
		suspend_dqs = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
		printk(KERN_ERR "max sample point=%d, bitmap=0x%x, DQS=0x%x\n", max, bitmap, readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
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
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
	printk(KERN_ERR "rtkemmc_dqs_tuning finished!!! EMMC_UHSREG=%x\n",readl(emmc_port->emmc_membase + EMMC_UHSREG));
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dqs_tuning"));
#endif
	up_write(&cr_rw_sem);

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
			tmout = tmout + msecs_to_jiffies(block_count>>1);
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
	u32 busmode=0;
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	u32 cur_timing = 0;

	emmc_port = mmc_priv(host);

	MMCPRINTF(KERN_INFO "ios->bus_mode = %u\n",ios->bus_mode);
	MMCPRINTF(KERN_INFO "ios->clock = %u\n",ios->clock);
	MMCPRINTF(KERN_INFO "ios->bus_width = %u\n",ios->bus_width);
	MMCPRINTF(KERN_INFO "ios->timing = %u\n",ios->timing);
	//down_write(&cr_rw_sem);
	cur_timing = ios->timing;
	if (ios->clock == MMC_HIGH_52_MAX_DTR)
		cur_timing = MMC_TIMING_MMC_HS;

	MMCPRINTF(KERN_INFO "cur_timing = %u\n",cur_timing);

	if (!g_bResuming) {
		switch(cur_timing)
		{
		case MMC_TIMING_MMC_HS400:
			rtkemmc_set_freq(emmc_port,0x70);  //200MHZ
			rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_NON);
			isb();
			sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ios"));
#endif
			rtkemmc_writel(0x80000000 ,emmc_port->emmc_membase + EMMC_DDR_REG); //enable HS400
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ios"));
#endif
			isb();
			sync(emmc_port);
			printk(KERN_INFO "%s - enable HS400, DDR_REG:0x%08x\n",__func__,readl(emmc_port->emmc_membase + EMMC_DDR_REG));
			break;
		case MMC_TIMING_MMC_HS200:
			rtkemmc_set_freq(emmc_port,0xa6);  //200MHZ
			rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_NON);
			break;
		case MMC_TIMING_MMC_DDR52:
			rtkemmc_set_freq(emmc_port,0x2a);  //100MB
			rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_NON); //100MHZ/2 = 50MHZ
			break;
		case MMC_TIMING_MMC_HS:
			rtkemmc_set_freq(emmc_port,0x57);  //100Mhz
			rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_2); //100MHZ/2 = 50MHZ
			break;
		case MMC_TIMING_LEGACY:
			rtkemmc_set_freq(emmc_port,0x46);  //80Mhz
			rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_256);
			break;
		default:
			printk(KERN_INFO "%s: cur_timing = %u \n", __FILE__, cur_timing);
			break;
		}
	}

	if (ios->bus_width == MMC_BUS_WIDTH_8){
		printk(KERN_INFO "set bus width 8\n");
		rtkemmc_set_bits(emmc_port,BUS_WIDTH_8);
		busmode = BUS_WIDTH_8;
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ios"));
#endif
		if (cur_timing == MMC_TIMING_MMC_HS400) {
			rtkemmc_writel(0x00010001, emmc_port->emmc_membase + EMMC_UHSREG); //DDR
			isb();
			sync(emmc_port);
			rtkemmc_writel(0x88 ,emmc_port->emmc_membase + EMMC_DQS_CTRL1); //dqs dly tap
#if defined(CONFIG_ARCH_RTD139x)
			rtkemmc_writel(0x94, emmc_port->emmc_membase+0x530); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x534); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x538); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x53c); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x540); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x544); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x548 ); //dqs dly tap
			rtkemmc_writel(0x14, emmc_port->emmc_membase+0x54c); //dqs dly tap
			rtkemmc_writel(0xff00, emmc_port->emmc_membase+0x50c); //dqs dly tap
			rtkemmc_writel(0x94, emmc_port->emmc_membase+0x558);
			rtkemmc_writel(0x2, emmc_port->emmc_membase+0x550);
#elif defined(CONFIG_ARCH_RTD16xx)
			rtkemmc_writel(0x80, emmc_port->emmc_membase+0x530); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x534); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x538); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x53c); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x540); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x544); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x548 ); //dqs dly tap
			rtkemmc_writel(0x0, emmc_port->emmc_membase+0x54c); //dqs dly tap
			rtkemmc_writel(0xff00, emmc_port->emmc_membase+0x50c); //dqs dly tap
			rtkemmc_writel(0x80, emmc_port->emmc_membase+0x558);
			rtkemmc_writel(0x2, emmc_port->emmc_membase+0x550);
#endif
			isb();
			sync(emmc_port);
			
			//rtkemmc_dump_registers(emmc_port);
			sync(emmc_port);
		}
		else if(cur_timing == MMC_TIMING_MMC_DDR52) {
			rtkemmc_writel(0x00010001, emmc_port->emmc_membase + EMMC_UHSREG); //DDR
			isb();
			sync(emmc_port);
		}
		else{
			rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_UHSREG); //non-DDR, such as SDR / HS200
		}
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ios"));
#endif
	} else if (ios->bus_width == MMC_BUS_WIDTH_4){
		printk(KERN_INFO "set bus width 4\n");
		rtkemmc_set_bits(emmc_port,BUS_WIDTH_4);
		busmode = BUS_WIDTH_4;
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

#ifdef EMMC_DEBUG
static void rtkemmc_dump_registers(struct rtkemmc_host *emmc_port)
{
	printk(KERN_INFO "%s : \n", __func__);
//	unsigned long flags2;

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_dump_registers"));
#if defined(CONFIG_ARCH_RTD129x)
	printk(KERN_ERR "EMMC_muxpad0 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_muxpad0));
	printk(KERN_ERR "EMMC_muxpad1 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_muxpad1));
	printk(KERN_ERR "EMMC_PFUNC_NF1 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PFUNC_NF1));
	printk(KERN_ERR "EMMC_PFUNC_CR  = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PFUNC_CR));
	printk(KERN_ERR "EMMC_PDRIVE_NF1 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF1));
	printk(KERN_ERR "EMMC_PDRIVE_NF2 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF2));
	printk(KERN_ERR "EMMC_PDRIVE_NF3 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF3));
#elif defined(CONFIG_ARCH_RTD139x)
	printk(KERN_INFO "ISO_muxpad4 = 0x%08x \n", readl(emmc_port->iso_muxpad + ISO_muxpad4));
	printk(KERN_INFO "pfunc_emmc0 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc0));
	printk(KERN_INFO "pfunc_emmc1 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc1));
	printk(KERN_INFO "pfunc_emmc2 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc2));
	printk(KERN_INFO "pfunc_emmc3 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc3));
	printk(KERN_INFO "pfunc_emmc4 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc4));
	printk(KERN_INFO "pfunc_emmc5 = 0x%08x \n", readl(emmc_port->iso_muxpad + pfunc_emmc5));
#elif defined(CONFIG_ARCH_RTD16xx)
	printk(KERN_INFO "m2tmx_muxpad0 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_muxpad0));
	printk(KERN_INFO "m2tmx_pfunc4 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_pfunc4));
	printk(KERN_INFO "m2tmx_pfunc5 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_pfunc5));
	printk(KERN_INFO "m2tmx_pfunc6 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_pfunc6));
	printk(KERN_INFO "m2tmx_pfunc7 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_pfunc7));
	printk(KERN_INFO "m2tmx_pfunc8 = 0x%08x \n", readl(emmc_port->m2tmx + m2tmx_pfunc8));
#endif
	printk(KERN_INFO "EMMC_CTYPE = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CTYPE));
	printk(KERN_INFO "EMMC_UHSREG = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_UHSREG));
	printk(KERN_INFO "EMMC_DDR_REG = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_DDR_REG));
	printk(KERN_INFO "EMMC_CARD_THR_CTL = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CARD_THR_CTL));
	printk(KERN_INFO "EMMC_CLKDIV = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CLKDIV));
	printk(KERN_INFO "EMMC_CKGEN_CTL = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL));
	printk(KERN_INFO "EMMC_DQS_CTLR1 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1));
	printk(KERN_INFO "EMMC_PAD_CTL = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PAD_CTL));
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
        printk(KERN_INFO "EMMC_DUMMY_SYS = 0x%08x\n", readl(emmc_port->emmc_membase + EMMC_DUMMY_SYS));
#endif

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_dump_registers"));
	isb();
	sync(emmc_port);
}
#endif

static void rtkemmc_restore_registers(struct rtkemmc_host *emmc_port)
{
//	unsigned long flags2;

        //rtk_lockapi_lock2(flags2, _at_("rtkemmc_restore_registers"));
#if defined(CONFIG_ARCH_RTD129x)
	rtkemmc_writel(gRegTbl.emmc_mux_pad0, emmc_port->emmc_membase + EMMC_muxpad0);
	rtkemmc_writel(gRegTbl.emmc_mux_pad1, emmc_port->emmc_membase + EMMC_muxpad1);
	rtkemmc_writel(gRegTbl.emmc_pfunc_nf1, emmc_port->emmc_membase + EMMC_PFUNC_NF1);
	rtkemmc_writel(gRegTbl.emmc_pfunc_cr, emmc_port->emmc_membase + EMMC_PFUNC_CR);
	rtkemmc_writel(gRegTbl.emmc_pdrive_nf1, emmc_port->emmc_membase + EMMC_PDRIVE_NF1);
	rtkemmc_writel(gRegTbl.emmc_pdrive_nf2, emmc_port->emmc_membase + EMMC_PDRIVE_NF2);
	rtkemmc_writel(gRegTbl.emmc_pdrive_nf3, emmc_port->emmc_membase + EMMC_PDRIVE_NF3);
	rtkemmc_writel(gRegTbl.emmc_pdrive_nf4, emmc_port->emmc_membase + EMMC_PDRIVE_NF4);
/*this part for 139x and 16xx only for debugging,
  129x & 16xx does not need to do this, onlt 129x needs to take this action*/
/*
#elif defined(CONFIG_ARCH_RTD139x)
	rtkemmc_writel(gRegTbl.iso_muxpad4,emmc_port->iso_muxpad + ISO_muxpad4);
	rtkemmc_writel(gRegTbl.Pfunc_emmc0,emmc_port->iso_muxpad + pfunc_emmc0);
	rtkemmc_writel(gRegTbl.Pfunc_emmc1,emmc_port->iso_muxpad + pfunc_emmc1);
	rtkemmc_writel(gRegTbl.Pfunc_emmc2,emmc_port->iso_muxpad + pfunc_emmc2);
	rtkemmc_writel(gRegTbl.Pfunc_emmc3,emmc_port->iso_muxpad + pfunc_emmc3);
	rtkemmc_writel(gRegTbl.Pfunc_emmc4,emmc_port->iso_muxpad + pfunc_emmc4);
	rtkemmc_writel(gRegTbl.Pfunc_emmc5,emmc_port->iso_muxpad + pfunc_emmc5);
*/
#endif

#ifdef CONFIG_ARCH_RTD129x
	rtkemmc_writel(gRegTbl.emmc_pdrive_cr0, emmc_port->emmc_membase + EMMC_PDRIVE_CR0);
        rtkemmc_writel(gRegTbl.emmc_pdrive_cr1, emmc_port->emmc_membase + EMMC_PDRIVE_CR1);
        rtkemmc_writel(gRegTbl.emmc_pdrive_sdio, emmc_port->emmc_membase + EMMC_PDRIVE_SDIO);
        rtkemmc_writel(gRegTbl.emmc_pdrive_sdio1, emmc_port->emmc_membase + EMMC_PDRIVE_SDIO1);
#endif
	rtkemmc_writel(gRegTbl.emmc_ctype, emmc_port->emmc_membase + EMMC_CTYPE);
	rtkemmc_writel(gRegTbl.emmc_uhsreg, emmc_port->emmc_membase + EMMC_UHSREG);
	rtkemmc_writel(gRegTbl.emmc_ddr_reg, emmc_port->emmc_membase + EMMC_DDR_REG);
	rtkemmc_writel(gRegTbl.emmc_card_thr_ctl, emmc_port->emmc_membase + EMMC_CARD_THR_CTL);
	rtkemmc_writel(gRegTbl.emmc_clk_div, emmc_port->emmc_membase + EMMC_CLKDIV);
	rtkemmc_writel(gRegTbl.emmc_ckgen_ctl, emmc_port->emmc_membase + EMMC_CKGEN_CTL);
	if(gCurrentBootMode == MODE_HS400) {
		rtkemmc_writel(gRegTbl.emmc_dqs_ctrl1 | 0x80, emmc_port->emmc_membase + EMMC_DQS_CTRL1);
	}
	else {
		rtkemmc_writel(gRegTbl.emmc_dqs_ctrl1, emmc_port->emmc_membase + EMMC_DQS_CTRL1);
	}
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	rtkemmc_writel(gRegTbl.emmc_drto_mask_ori,emmc_port->emmc_membase + EMMC_DUMMY_SYS);
#endif
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_restore_registers"));
	isb();
	sync(emmc_port);
#ifdef EMMC_DEBUG
	rtkemmc_dump_registers(emmc_port);
#endif
}

static void rtkemmc_backup_registers(struct rtkemmc_host *emmc_port)
{
//	unsigned long flags2;

        //rtk_lockapi_lock2(flags2, _at_("rtkemmc_backup_registers"));
#if defined(CONFIG_ARCH_RTD129x)
	gRegTbl.emmc_mux_pad0 = readl(emmc_port->emmc_membase + EMMC_muxpad0);
	gRegTbl.emmc_mux_pad1 = readl(emmc_port->emmc_membase + EMMC_muxpad1);
	gRegTbl.emmc_pfunc_nf1 = readl(emmc_port->emmc_membase + EMMC_PFUNC_NF1);
	gRegTbl.emmc_pfunc_cr = readl(emmc_port->emmc_membase + EMMC_PFUNC_CR);
	gRegTbl.emmc_pdrive_nf1 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF1);
	gRegTbl.emmc_pdrive_nf2 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF2);
	gRegTbl.emmc_pdrive_nf3 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF3);
	gRegTbl.emmc_pdrive_nf4 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF4);

/*this part for 139x and 16xx only for debugging,
  129x & 16xx does not need to do this, onlt 129x needs to take this action*/
/*
#elif defined(CONFIG_ARCH_RTD139x)
	gRegTbl.iso_muxpad4 = readl(emmc_port->iso_muxpad + ISO_muxpad4);
	gRegTbl.Pfunc_emmc0 = readl(emmc_port->iso_muxpad + pfunc_emmc0);
	gRegTbl.Pfunc_emmc1 = readl(emmc_port->iso_muxpad + pfunc_emmc1);
	gRegTbl.Pfunc_emmc2 = readl(emmc_port->iso_muxpad + pfunc_emmc2);
	gRegTbl.Pfunc_emmc3 = readl(emmc_port->iso_muxpad + pfunc_emmc3);
	gRegTbl.Pfunc_emmc4 = readl(emmc_port->iso_muxpad + pfunc_emmc4);
	gRegTbl.Pfunc_emmc5 = readl(emmc_port->iso_muxpad + pfunc_emmc5);
*/
#endif

#ifdef CONFIG_ARCH_RTD129x
	gRegTbl.emmc_pdrive_cr0 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_CR0);
	gRegTbl.emmc_pdrive_cr1 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_CR1);
	gRegTbl.emmc_pdrive_sdio = readl(emmc_port->emmc_membase + EMMC_PDRIVE_SDIO);
	gRegTbl.emmc_pdrive_sdio1 = readl(emmc_port->emmc_membase + EMMC_PDRIVE_SDIO1);
#endif
	gRegTbl.emmc_ctype = readl(emmc_port->emmc_membase + EMMC_CTYPE);
	gRegTbl.emmc_uhsreg = readl(emmc_port->emmc_membase + EMMC_UHSREG);
	gRegTbl.emmc_ddr_reg = readl(emmc_port->emmc_membase + EMMC_DDR_REG);
	gRegTbl.emmc_card_thr_ctl = readl(emmc_port->emmc_membase + EMMC_CARD_THR_CTL);
	gRegTbl.emmc_clk_div = readl(emmc_port->emmc_membase + EMMC_CLKDIV);
	gRegTbl.emmc_ckgen_ctl = readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL);
	gRegTbl.emmc_dqs_ctrl1 = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	gRegTbl.emmc_drto_mask_ori = readl(emmc_port->emmc_membase + EMMC_DUMMY_SYS);
	gRegTbl.emmc_other1 = readl(emmc_port->emmc_membase + EMMC_OTHER1);
#endif
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_backup_registers"));
	isb();
	sync(emmc_port);
#ifdef EMMC_DEBUG
	rtkemmc_dump_registers(emmc_port);
#endif
}

static int wait_done_timeout(struct rtkemmc_host *emmc_port, volatile u32 *addr, u32 mask, u32 value, const char *string)
{
	int n = 0;
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	while(1)
	{
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("wait_done_timeout"));
#endif
		if (((*addr) &mask) == value){
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("wait_done_timeout"));
#endif
			break;
                }
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("wait_done_timeout"));
#endif
		if(n++ > 3000000) {
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("wait_done_timeout"));
#endif
			printk(KERN_ERR "Timeout!!! cmd_opcode=%d, cmd_arg=%x, addr=%p, mask=%x, value=%x, emmc_port->emmc_membase + EMMC_STATUS=%x, pre_func=%s\n"
				,emmc_port->cmd_opcode, readl(emmc_port->emmc_membase+EMMC_CMDARG), addr, mask, value, readl(emmc_port->emmc_membase + EMMC_STATUS), string);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("wait_done_timeout"));
#endif
			return -1;
		}
		udelay(1);
		sync(emmc_port);
	}
	return 0;
}

static void rtkemmc_set_bits(struct rtkemmc_host *emmc_port,u32 set_bit)
{
	unsigned long flags;
//	unsigned long flags2;

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_bits"));	//spin lock only assures that one process cannot be interruptted by IRQ on one cpu, we still need to use lock_api
								//to fix A01 IP bug 

	spin_lock_irqsave(&emmc_port->lock,flags);
	rtkemmc_writel(set_bit,emmc_port->emmc_membase + EMMC_CTYPE);
	sync(emmc_port);
	spin_unlock_irqrestore(&emmc_port->lock, flags);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_bits"));

        wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x200, 0x0, __func__);          //card is not busy
    	sync(emmc_port);

    	printk(KERN_INFO "%s: set to 0x%08x, EMMC_CTYPE=%08x\n", DRIVER_NAME, set_bit, readl(emmc_port->emmc_membase + EMMC_CTYPE));
}

void rtkemmc_set_pad_driving(struct rtkemmc_host *emmc_port, u32 clk_drv, u32 cmd_drv, u32 data_drv, u32 ds_drv)
{
//	unsigned long flags2;
#ifdef CONFIG_ARCH_RTD139x
	u32 tmp = 0;
#endif

#if defined(CONFIG_ARCH_RTD129x)
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_pad_driving"));

	rtkemmc_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), emmc_port->emmc_membase + EMMC_PDRIVE_NF1); //d0~d3
	rtkemmc_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), emmc_port->emmc_membase + EMMC_PDRIVE_NF2); //d4~d7
	rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_PDRIVE_NF3)&(0x00ff00ff))|(clk_drv<<8)|(cmd_drv<<24), emmc_port->emmc_membase + EMMC_PDRIVE_NF3); //d4~d7
	rtkemmc_writel(ds_drv, emmc_port->emmc_membase + EMMC_PDRIVE_NF4); //data strobe

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_pad_driving"));
#elif defined(CONFIG_ARCH_RTD139x)
	//data 0 - 7
	tmp = (readl(emmc_port->iso_muxpad + pfunc_emmc2)&0xffe07e07)|(data_drv<<3)|(data_drv<<6)|(data_drv<<15)|(data_drv<<18);
	rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc2);
        rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc3);
	rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc4);
	rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc5);

	tmp = (readl(emmc_port->iso_muxpad + pfunc_emmc1)&0xffe07e07)|(clk_drv<<3)|(clk_drv<<6)|(cmd_drv<<15)|(cmd_drv<<18);	//clk and cmd
	rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc1);

	tmp = (readl(emmc_port->iso_muxpad + pfunc_emmc0)&0xffe07fff)|(ds_drv<<15)|(ds_drv<<18);	//data strobe
	rtkemmc_writel(tmp, emmc_port->iso_muxpad + pfunc_emmc0);
#elif defined(CONFIG_ARCH_RTD16xx)
	rtkemmc_writel((readl(emmc_port->m2tmx + m2tmx_pfunc4)&0xf03fffff)|(clk_drv<<22)|(clk_drv<<25),emmc_port->m2tmx + m2tmx_pfunc4);
	rtkemmc_writel((readl(emmc_port->m2tmx + m2tmx_pfunc5)&0x07e07f03)|(cmd_drv<<2)|(cmd_drv<<5)|(data_drv<<15)|(data_drv<<18)|(data_drv<<27)|((data_drv&0x3)<<30),
				emmc_port->m2tmx + m2tmx_pfunc5);
	rtkemmc_writel((readl(emmc_port->m2tmx + m2tmx_pfunc6)&0x7e07e07e)|(data_drv>>2)|(data_drv<<7)|(data_drv<<10)|(data_drv<<19)|(data_drv<<22)|((data_drv&0x1)<<31),
				emmc_port->m2tmx + m2tmx_pfunc6);
	rtkemmc_writel((readl(emmc_port->m2tmx + m2tmx_pfunc7)&0xe07e07e0)|(data_drv>>1)|(data_drv<<2)|(data_drv<<11)|(data_drv<<14)|(data_drv<<23)|(data_drv<<26),
				emmc_port->m2tmx + m2tmx_pfunc7);
	rtkemmc_writel((readl(emmc_port->m2tmx + m2tmx_pfunc8)&0xfffffe07)|(data_drv<<3)|(data_drv<<6),emmc_port->m2tmx + m2tmx_pfunc8);
#endif
	isb();
	sync(emmc_port);
}

//wrapper clk divider
//clk_div       [2..0]
//000: div1
//001: div2
//010: div4
//011: div8

static void rtkemmc_set_wrapper_div(struct rtkemmc_host *emmc_port,u8 level)
{

	unsigned long flags;
//	unsigned long flags2;

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_wrapper_div"));

	spin_lock_irqsave(&emmc_port->lock,flags);

	switch(level)
    	{
	case 0:
		rtkemmc_writel(0x2100,emmc_port->emmc_membase + EMMC_CKGEN_CTL);
		break;
	case 1:
		rtkemmc_writel(0x2010,emmc_port->emmc_membase + EMMC_CKGEN_CTL);
		break;
	case 2:
		rtkemmc_writel(0x2102,emmc_port->emmc_membase + EMMC_CKGEN_CTL);
		break;
	case 3:
		rtkemmc_writel(0x2103,emmc_port->emmc_membase + EMMC_CKGEN_CTL);
		break;
	}
	
	isb();
	sync(emmc_port);
	printk(KERN_INFO "%s: set_wrapper_div to 0x%08x\n", DRIVER_NAME, readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL));
	
	spin_unlock_irqrestore(&emmc_port->lock, flags);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_wrapper_div"));
}

static void rtkemmc_set_ip_div(struct rtkemmc_host *emmc_port,u32 set_div)
{
	unsigned long flags;
//	unsigned long flags2;

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ip_div"));

	u32 cur_div = readl(emmc_port->emmc_membase+EMMC_CLKDIV);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ip_div"));

	if (cur_div == set_div){
		printk(KERN_INFO "%s, set_ip_div = cur_div(0x%08x), ignored. \n", DRIVER_NAME, cur_div);
		return;
	}

	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x200, 0x0, __func__);
	
	spin_lock_irqsave(&emmc_port->lock,flags);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ip_div"));
	//disable clock
	rtkemmc_writel(0, emmc_port->emmc_membase+EMMC_CLKENA);
	isb();

	//EMMC Cmd
	rtkemmc_writel(0xa0202000, emmc_port->emmc_membase+EMMC_CMD);
	isb();
	sync(emmc_port);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ip_div"));

	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase+EMMC_CMD), 0x80000000, 0x0, __func__);
	sync(emmc_port);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ip_div"));
	//set divider
	rtkemmc_writel(set_div, emmc_port->emmc_membase+EMMC_CLKDIV);
	isb();
	sync(emmc_port);

	while (readl(emmc_port->emmc_membase + EMMC_CLKDIV) != set_div){
		printk(KERN_ERR RED_BOLD"Fail to write  EMMC_CLKDIV! EMMC_CLKDIV = 0x%08x\n"RESET, readl(emmc_port->emmc_membase+EMMC_CLKDIV));
		rtkemmc_writel(set_div, emmc_port->emmc_membase+EMMC_CLKDIV);
		sync(emmc_port);
	}

	//EMMC Cmd
	rtkemmc_writel(0xa0202000, emmc_port->emmc_membase+EMMC_CMD);
	isb();
	sync(emmc_port);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ip_div"));

	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase+EMMC_CMD), 0x80000000, 0x0, __func__);
	isb();
	sync(emmc_port);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ip_div"));

	//enable clock
	rtkemmc_writel(0x10001, emmc_port->emmc_membase+EMMC_CLKENA);
	isb();
	sync(emmc_port);

	//EMMC Cmd
	rtkemmc_writel(0xa0202000, emmc_port->emmc_membase+EMMC_CMD);
	isb();
	sync(emmc_port);

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ip_div"));

	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase+EMMC_CMD), 0x80000000, 0x0, __func__);
	isb();

	spin_unlock_irqrestore(&emmc_port->lock, flags);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_ip_div"));
	printk(KERN_INFO "%s: set div to 0x%02x, EMMC_CLKDIV=%08x\n", DRIVER_NAME, set_div, readl(emmc_port->emmc_membase + EMMC_CLKDIV));
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_ip_div"));
}

void phase(struct rtkemmc_host *emmc_port, u32 VP0, u32 VP1)
{
//	unsigned long flags2;

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
		//rtk_lockapi_lock2(flags2, _at_("phase"));
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000), emmc_port->emmc_membase + EMMC_CKGEN_CTL);    //change clock to 4MHz
		//rtk_lockapi_unlock2(flags2, _at_("phase"));

		sync(emmc_port);
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd), emmc_port->crt_membase + SYS_PLL_EMMC1);     //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffff07)|(VP0<<3), emmc_port->crt_membase + SYS_PLL_EMMC1);    //vp0 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2), emmc_port->crt_membase + SYS_PLL_EMMC1);    //release reset pll
		sync(emmc_port);
		udelay(200);

		//rtk_lockapi_lock2(flags2, _at_("phase"));
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff), emmc_port->emmc_membase + EMMC_CKGEN_CTL); //change clock to PLL
		//rtk_lockapi_unlock2(flags2, _at_("phase"));
		sync(emmc_port);
	}
	else if( (VP0==0xff) & (VP1!=0xff)){
#ifdef DEBUG
		printk("phase VP0 no change, VP1=%x \n", VP1);
#endif
		//rtk_lockapi_lock2(flags2, _at_("phase"));
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000), emmc_port->emmc_membase + EMMC_CKGEN_CTL);    //change clock to 4MHz
		//rtk_lockapi_unlock2(flags2, _at_("phase"));
		sync(emmc_port);

		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd), emmc_port->crt_membase + SYS_PLL_EMMC1);     //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffe0ff)|(VP1<<8), emmc_port->crt_membase + SYS_PLL_EMMC1);    //vp1 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2), emmc_port->crt_membase + SYS_PLL_EMMC1);    //release reset pll
		sync(emmc_port);
		udelay(200);

		//rtk_lockapi_lock2(flags2, _at_("phase"));
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff),emmc_port->emmc_membase + EMMC_CKGEN_CTL);  //change clock to PLL
		//rtk_lockapi_unlock2(flags2, _at_("phase"));
		sync(emmc_port);
	}
        else{
#ifdef DEBUG
		printk("phase VP0=%x, VP1=%x \n", VP0, VP1);
#endif
		//rtk_lockapi_lock2(flags2, _at_("phase"));
		rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)|0x70000),emmc_port->emmc_membase + EMMC_CKGEN_CTL);     //change clock to 4MHz
		//rtk_lockapi_unlock2(flags2, _at_("phase"));
		sync(emmc_port);

		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xfffffffd),emmc_port->crt_membase + SYS_PLL_EMMC1);      //reset pll
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffff07)|(VP0<<3),emmc_port->crt_membase + SYS_PLL_EMMC1);     //vp0 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)&0xffffe0ff)|(VP1<<8),emmc_port->crt_membase + SYS_PLL_EMMC1);     //vp1 phase:0x0~0x1f
		rtkemmc_writel((readl(emmc_port->crt_membase + SYS_PLL_EMMC1)|0x2),emmc_port->crt_membase + SYS_PLL_EMMC1);     //release reset pll
		sync(emmc_port);
		udelay(200);

		//rtk_lockapi_lock2(flags2, _at_("phase"));
                rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL)&0xfff8ffff),emmc_port->emmc_membase + EMMC_CKGEN_CTL);  //change clock to PLL
		//rtk_lockapi_unlock2(flags2, _at_("phase"));
		sync(emmc_port);
	}
#ifdef EMMC_DEBUG
	//rtk_lockapi_lock2(flags2, _at_("phase"));
	printk(KERN_ERR "%s: phase adjust - EMMC_CKGEN_CTL=0x%08x, PLL_EMMC1=%08x, PLL_EMMC2=%08x, PLL_EMMC3=%08x, PLL_EMMC4=%08x\n",
		DRIVER_NAME,
		readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC4));
	//rtk_lockapi_unlock2(flags2, _at_("phase"));
#endif
}

static void rtkemmc_set_freq(struct rtkemmc_host *emmc_port, u32 freq)
{
	u32 tmp_val=0;
	unsigned long flags;
//	unsigned long flags2;

	spin_lock_irqsave(&emmc_port->lock,flags);
	wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_STATUS), 0x200, 0x0, __func__);          //card is not busy
	isb();
	sync(emmc_port);

	//disable clk_en_emmc_ip, using common clk framework`
	//tmp_val = (readl(emmc_port->crt_membase + SYS_CLOCK_ENABLE1) & 0xefffffff);
	//rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_CLOCK_ENABLE1);

	clk_disable_unprepare(clk_en_emmc_ip);
	isb();
	sync(emmc_port);

	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC4) & 0x06);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC4);
	isb();
	sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
	if (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01 ) {
		rtkemmc_writel(1, emmc_port->crt_membase + SYS_GROUP1_CK_SEL);
		isb();
		sync(emmc_port);
	}
#endif
	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC3) & 0xffff)|(freq<<16);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC3);
	isb();
	sync(emmc_port);

	tmp_val = (readl(emmc_port->crt_membase + SYS_PLL_EMMC4) | 0x01);
	rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_PLL_EMMC4);
	isb();
	sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
	if (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01 ) {
		rtkemmc_writel(0, emmc_port->crt_membase + SYS_GROUP1_CK_SEL);
		isb();
		sync(emmc_port);
	}
#endif
#ifdef CONFIG_ARCH_RTD129x	//1395 does not need to toggle this register
	// [A01] ECO, If EMMC N/F code changed, toggle CR_EMMC_DUMMY_SYS bit 30
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
		//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_freq"));
		rtkemmc_writel(readl(emmc_port->emmc_membase + EMMC_DUMMY_SYS) ^ 0x40000000, emmc_port->emmc_membase + EMMC_DUMMY_SYS);
		//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_freq"));
		isb();
		sync(emmc_port);
	}

	udelay(400); //delay 200us to wait PLL stable
	isb();
	sync(emmc_port);
#endif
	//enable clk_en_emmc_ip
	//tmp_val = (readl(emmc_port->crt_membase + SYS_CLOCK_ENABLE1) | 0x10000000);
	//rtkemmc_writel(tmp_val, emmc_port->crt_membase + SYS_CLOCK_ENABLE1);

	clk_prepare_enable(clk_en_emmc_ip);
	isb();
	sync(emmc_port);

	spin_unlock_irqrestore(&emmc_port->lock, flags);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_freq"));
	printk(KERN_INFO "%s: set_freq to 0x%02x, EMMC_CKGEN_CTL=0x%08x, PLL_EMMC1=%08x, PLL_EMMC2=%08x, PLL_EMMC3=%08x, PLL_EMMC4=%08x\n",
		DRIVER_NAME,
		freq, readl(emmc_port->emmc_membase + EMMC_CKGEN_CTL),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
		readl(emmc_port->crt_membase + SYS_PLL_EMMC4));
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_freq"));
}

void rtkemmc_speed_up(void)
{
	struct mmc_host * mmc = mmc_host_local;
	struct rtkemmc_host *emmc_port;

	emmc_port = mmc_priv(mmc);

	rtkemmc_set_freq(emmc_port,0x46);  //80Mhz
	rtkemmc_set_ip_div(emmc_port,EMMC_CLOCK_DIV_8);
}
EXPORT_SYMBOL(rtkemmc_speed_up);

static u32 rtkemmc_chk_cmdcode(struct mmc_command* cmd)
{
	u32 cmdcode;

	if(cmd->opcode < 56){
		cmdcode = (u32)rtk_sd_cmdcode[cmd->opcode][0];
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
	u32 reg_val=0;
//	unsigned long flags2;

	MMCPRINTF("rtkemmc_set_pin_mux \n");

	//1295 muxpad0 is in card reader
	//set default i/f to emmc
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_set_pin_mux"));
#if defined(CONFIG_ARCH_RTD129x)
	reg_val = readl(emmc_port->emmc_membase + EMMC_muxpad0);
	reg_val &= ~0xFFFF0C3C;
	//reg_val |= 0xaaaa0828;    //comment by Jim
	reg_val |= 0xaaaa0824;  //2017/1/17 modified by Jim, change pin mux to NAND flash instead of emmc rstn
        
	rtkemmc_writel(reg_val, emmc_port->emmc_membase+EMMC_muxpad0);
	sync(emmc_port);
	rtkemmc_writel((readl(emmc_port->emmc_membase + EMMC_muxpad1)&0xffffcfff)|0x2000, emmc_port->emmc_membase + EMMC_muxpad1); //kylin data strobe pad mux
	sync(emmc_port);
#elif defined(CONFIG_ARCH_RTD139x)
	reg_val = readl(emmc_port->iso_muxpad + ISO_muxpad4);
        reg_val &= ~0x3;
        reg_val |= 0x1;

        rtkemmc_writel(reg_val, emmc_port->iso_muxpad + ISO_muxpad4);
#elif defined(CONFIG_ARCH_RTD16xx)
	reg_val = readl(emmc_port->m2tmx + m2tmx_muxpad0);
	reg_val &= 0xfe000001;	//bit 1 - bit 24 set 0x10 0x10 0x10...0x10
	reg_val |= 0x01555554;
	rtkemmc_writel(reg_val, emmc_port->m2tmx + m2tmx_muxpad0);
#endif

#ifdef CONFIG_ARCH_RTD129x
	//emmc :pfunc_nf1
	rtkemmc_writel(0x33333333, emmc_port->emmc_membase+EMMC_PFUNC_NF1);
	sync(emmc_port);
	printk(KERN_INFO "rtkemmc_set_pin_mux: EMMC_PFUNC_NF1 = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_PFUNC_NF1));
#endif
	rtkemmc_writel(0, emmc_port->emmc_membase+EMMC_PAD_CTL); //PAD to 1.8v
	sync(emmc_port);
	
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_set_pin_mux"));
}

static void rtkemmc_timeout_timer(unsigned long data)
{
	struct rtkemmc_host *emmc_port;
	unsigned long flags;
//	unsigned long flags2;

	emmc_port = (struct rtkemmc_host *)data;
	MMCPRINTF("rtkemmc_timeout_timer fired ...\n");
	MMCPRINTF("%s - int_wait=%08x\n", __func__, emmc_port->int_waiting);
    
	spin_lock_irqsave(&emmc_port->lock,flags);
	//down_write(&cr_rw_sem);
#ifdef ENABLE_EMMC_INT_MODE
	if(emmc_port->int_waiting)
#else
	if (1)
#endif
	{
		MMCPRINTF("1. get sd trans \n");
#ifdef ENABLE_EMMC_INT_MODE
		MMCPRINTF("========== C1 ==========\n");
		rtkemmc_hold_int_dec();
                rtkemmc_get_int_sta(&emmc_port->rintsts, &emmc_port->mintsts, &emmc_port->dma_isr);
		rtkemmc_get_sta(&emmc_port->status, &emmc_port->idsts);
		rtkemmc_get_mask(&emmc_port->idinten, &emmc_port->intmask);
		sync(emmc_port);
#endif

		MMCPRINTF("rintsts =%08x, mintsts=0x%08x, int_waiting=%08x\n", emmc_port->rintsts, emmc_port->mintsts, emmc_port->int_waiting);
		MMCPRINTF("status=0x%08x idsts=0x%8x\n",emmc_port->status ,emmc_port->idsts);
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
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_irq"));
#endif
	rtkemmc_get_int_sta(&emmc_port->rintsts, &emmc_port->mintsts, &emmc_port->dma_isr);
	rtkemmc_get_sta(&emmc_port->status, &emmc_port->idsts);
	rtkemmc_get_mask(&emmc_port->idinten, &emmc_port->intmask);
	sync(emmc_port);

	MMCPRINTF("rintsts =%08x, mintsts=0x%08x, int_waiting=%08x\n", emmc_port->rintsts, emmc_port->mintsts, emmc_port->int_waiting);
	MMCPRINTF("intmask =%08x, isr=0x%08x\n", readl(emmc_port->emmc_membase+EMMC_INTMASK), emmc_port->dma_isr);
    
	rtkemmc_hold_int_dec();
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("rtkemmc_irq"));
#endif
	MMCPRINTF("we get int end \n");

#ifdef  SHOW_INT_STATUS
	printk("status=0x%08x idsts=0x%8x\n",emmc_port->status,emmc_port->idsts);
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
//	unsigned long flags2;

	MMCPRINTF("%s : \n", __func__);

	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_chk_card_insert"));

	rtkemmc_writel(0x00000000 ,emmc_port->emmc_membase + EMMC_DDR_REG); //restore to default   //9801210c
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_DQS_CTRL1);    //98012498

	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_chk_card_insert"));

#ifdef PHASE_INHERITED
        if (VP0_saved == 0xFF && VP1_saved == 0xFF){
                HS200_TX = VP0_saved = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x000000f8) >> 3;
                HS200_RX = VP1_saved = (readl(emmc_port->crt_membase + SYS_PLL_EMMC1) & 0x00001f00) >> 8;
		if(emmc_port->tx_user_defined) {	//if we set user defined tx and rx value, then we won't use the bootcode reference value
			HS200_TX = VP0_saved = emmc_port->tx_reference_phase;
		}
		if(emmc_port->rx_user_defined) {
			HS200_RX = VP1_saved = emmc_port->rx_reference_phase;
		}
        }
#endif

#ifdef DQS_INHERITED
	if (dqs_saved == 0xff)
		dqs_saved = readl(emmc_port->emmc_membase + EMMC_DQS_CTRL1);
#endif
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_chk_card_insert"));
	rtkemmc_writel(3, emmc_port->crt_membase + SYS_PLL_EMMC1);      //980001f0
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000081, emmc_port->emmc_membase + EMMC_BMOD);    //98012080  //enable the emmc dma and do dma software reset
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000000, emmc_port->emmc_membase + EMMC_CTRL);        //98012000      //if we use DMA, bit 25 has to be set
	isb();
	sync(emmc_port);

	rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_PWREN);       //98012004      //we only have one emmc, so we just set bit 0 to 1 to power on
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffce, emmc_port->emmc_membase + EMMC_INTMASK);     //98012024      //in emmc IP, it can be used as SD, MMC,SDIO,emmc, but in realtek usage, we only use emmc,
                                                                                                //so, we disable SDIO mask, but it does not matter for use to set o or 1 because they do not
                                                                                                //use these data pin, lower 16 bit is for emmc usage, we enable it
	isb();
	sync(emmc_port);
	rtkemmc_writel(0xffffffff, emmc_port->emmc_membase + EMMC_RINTSTS);     //98012044      //clear SDIO interrupt status bit, lower 16 bit is for emmc interrupt check, initial
                                                                                                //value is 0
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000080, emmc_port->emmc_membase + EMMC_CLKDIV);      //98012008      //in emmc IP, we have 4 clock divider, in realtek chipset, we only use the first divider,
                                                                                                //and we set the divider is 2*128=256, so initial clock rate is 80MHz/256
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_CLKSRC);      //9801200c      //choose the clock divider source, as previosly said, we only use divider 0
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0001ffff, emmc_port->emmc_membase + EMMC_CLKENA);      //98012010      //higher 16 bit is for low power control, do not send clock if no command, we only have
                                                                                                //one emmc, so we set bit 16 as 1m and ffff can only be set to 1 instead of ffff
	isb();
	sync(emmc_port);
	rtkemmc_writel(0xa0200000, emmc_port->emmc_membase + EMMC_CMD);         //9801202c      //bit 31 is for two purposes, one is for send command, set this bit to fire a command,
                                                                                                //the other is to update the clock register when we modify the clock related register
                                                                                                //including clock divider, clock enable, for this usage, we must set bit 21, as for bit 29,
                                                                                                //we decide if we need  tx ,rx normal clock or use the same clock, in realtek case, we use
                                                                                                //different clock, so set it as 1
	isb();
	sync(emmc_port);
	MMCPRINTF(KERN_INFO "1 EMMC_TMOUT = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_TMOUT));   //98012014
	rtkemmc_writel(0xffffff40, (volatile void*)(emmc_port->emmc_membase + EMMC_TMOUT));
	isb();
	sync(emmc_port);
	MMCPRINTF(KERN_INFO "2 EMMC_TMOUT = 0x%08x \n",  (volatile void*)readl(emmc_port->emmc_membase + EMMC_TMOUT));

	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_CTYPE);       //98012018      //initially, we set bus width as 1 for card 0 (emmc)
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0001007f, emmc_port->emmc_membase + EMMC_FIFOTH); // original: 0x0007f007f //9801204c, set the tx, rx threshold to decide whether we have to read/write data to/from
                                                                                                        //FIFO
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000010, emmc_port->emmc_membase + EMMC_CTRL);        //98012000      //bit 4 is global interrupt enable, we have to set this bit to 1 and then
                                                                                                //98012024 and 98012044 is meaningful, otherwise, nonsense
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000080, emmc_port->emmc_membase + EMMC_BMOD);        //98012080      //no need for this write becasue reset the bit 0 will be reset to 0
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffce, emmc_port->emmc_membase + EMMC_INTMASK);     //98012024      //FIFO interrupt has some issues, so we disable this two bits
	isb();
	sync(emmc_port);
	//rtkemmc_writel(0x00600000, emmc_port->emmc_membase + EMMC_DBADDR);
	rtkemmc_writel(0x00000000, emmc_port->emmc_membase + EMMC_IDINTEN);     //98012090      //we do not use abnormal interrupt, so disable all
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x0000ffff, emmc_port->emmc_membase + EMMC_RINTSTS);     //98012044      //do not need this one
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x00000001, emmc_port->emmc_membase + EMMC_UHSREG);      //98012074      //in emmc, they always use 1.8V, differenct from SD card, they do not need to switch voltage
	isb();
	sync(emmc_port);
	rtkemmc_writel(0x02000001, emmc_port->emmc_membase + EMMC_CARD_THR_CTL);        //98012100      //FIFO size is 128, once the FIFO size is greater than 128 bytes, we can read/write
                                                                                                        //but in this case, we only set bit 0 as 1, we only set read threshold
	isb();
	sync(emmc_port);

#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xa, emmc_port->emmc_membase+EMMC_OTHER1);    //Enable eMMC L4 gated
	if(MASK_DRTO)	//enable/disable timeout mechanism
		writel(readl(emmc_port->emmc_membase + EMMC_DUMMY_SYS) | 0x1, emmc_port->emmc_membase + EMMC_DUMMY_SYS);
#endif


	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_chk_card_insert"));
#ifdef EMMC_LA_DEBUG_GPIO
	//gpio 100 pin mux
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_chk_card_insert"));
#ifdef CONFIG_ARCH_RTD129x
	reg = readl(emmc_port->emmc_membase + EMMC_muxpad2);            //9801261c
	reg &= (~0x00003000);
	rtkemmc_writel(reg, emmc_port->emmc_membase + EMMC_muxpad2);
#endif
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_chk_card_insert"));
	//gpio 100 dir
	reg = readl(emmc_port->misc_membase + MISC_GP3DIR);             //9801B10c
	reg |= (0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DIR);

	//gpio 100  pull  high
	reg = readl(emmc_port->misc_membase + MISC_GP3DATO);            //9801B11c
	reg |= (0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
	isb();
	sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_chk_card_insert"));

	//gpio 90 pin mux
	reg = readl(emmc_port->emmc_membase + EMMC_muxpad1);            //98012604
	reg &= (~0x0000000c);
	rtkemmc_writel(reg, emmc_port->emmc_membase + EMMC_muxpad1);
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_chk_card_insert"));
#endif
	//gpio 90 dir
	reg = readl(emmc_port->misc_membase + MISC_GP2DIR);             //9801B108
	reg |= (0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DIR);

	//gpio 90  pull  high
	reg = readl(emmc_port->misc_membase + MISC_GP2DATO);            //9801B118
	reg |= (0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
	isb();
	sync(emmc_port);
#endif
	rtkemmc_set_bits(emmc_port,BUS_WIDTH_1);                    //initially, set the bus width as 1

#ifdef CONFIG_ARCH_RTD129x
	rtkemmc_set_pad_driving(emmc_port, 0x33, 0x33, 0x33, 0x33);
#else
	rtkemmc_set_pad_driving(emmc_port, 0x0, 0x0, 0x0, 0x0);
#endif

	rtkemmc_set_wrapper_div(emmc_port, 0);                      //in emmc, they have two clock divider, ip and wrapperm in SD case, they only have wrapper clock divider
         	                                                    //because emmc IP clock divider can set clock precisely, we do not need to use wrapper clock divider

	rtkemmc_set_ip_div(emmc_port, EMMC_CLOCK_DIV_256);
	
	//initially, we do not use pass tuning result from bootcode, so we need to reset the tx ,rx phase to 0 first, 
	//and then framework call rtkemmc_tuning will set the rx tx register
	//Now, we use the mechanism and hold this part for fear that user will use kernel tuning one day in the future
	//if we use tuning inherit, the phase will be set to 0 and restore the tx rx from bootcode
	phase(emmc_port, 0, 0); //VP0, VP1 phase
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)&0xffffffff7,emmc_port->emmc_membase+EMMC_OTHER1);
	udelay(1);
	writel(readl(emmc_port->emmc_membase+EMMC_OTHER1)|0x8,emmc_port->emmc_membase+EMMC_OTHER1);
#endif
	rtkemmc_set_freq(emmc_port,0x46);  //80Mhz / 256 ~= 300K

	sync(emmc_port);
	host->ops = &rtkemmc_ops;
	emmc_port->rtflags |= RTKCR_FCARD_DETECTED;
#ifdef EMMC_DEBUG
	rtkemmc_dump_registers(emmc_port);
#endif
}

static int rtkemmc_set_rspparam(struct rtkemmc_host *emmc_port, struct sd_cmd_pkt *cmd_info)
{
	switch(cmd_info->cmd->opcode)
	{
	case MMC_GO_IDLE_STATE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG);
		cmd_info->rsp_len = 6;
		cmd_info->cmd->arg = 0x00000000;
		break;
	case MMC_SEND_OP_COND:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_RSP_EXP);
		cmd_info->cmd->arg = MMC_SECTOR_ADDR|MMC_VDD_165_195;
		cmd_info->rsp_len = 6;
		break;
	case MMC_ALL_SEND_CID:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		cmd_info->rsp_len = 17;
		cmd_info->cmd->arg = 0x00000000;
		break;
	case MMC_SET_RELATIVE_ADDR:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_CSD:
	case MMC_SEND_CID:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 17;
		break;
	case MMC_SEND_EXT_CSD:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->arg = 0;
		cmd_info->rsp_len = 6;
		break;
	case MMC_SLEEP_AWAKE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		printk(KERN_INFO "%s : cmd5 arg=0x%08x\n",__func__,cmd_info->cmd->arg);
		break;
	case MMC_SELECT_CARD:
		printk(KERN_INFO "%s : cmd7 arg : 0x%08x\n",__func__,cmd_info->cmd->arg);
		if (cmd_info->cmd->flags == (MMC_RSP_NONE | MMC_CMD_AC)) {
			printk(KERN_INFO "%s : cmd7 with rsp none\n",__func__);
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC);
		}
		else {
			printk(KERN_INFO "%s : cmd7 with rsp\n",__func__);
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		}
		cmd_info->rsp_len = 6;
		break;
	case MMC_SWITCH:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_STATUS:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->arg = (1<<RCA_SHIFTER);
		cmd_info->rsp_len = 6;
		break;
	case MMC_STOP_TRANSMISSION:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_READ_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_SEND_AUTO_STOP|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP|CMD_WAIT_PRV_DATA_COMPLETE);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SET_BLOCK_COUNT:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_SEND_AUTO_STOP|CMD_RD_WR|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_READ_SINGLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP|CMD_WAIT_PRV_DATA_COMPLETE);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_RD_WR|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_ERASE_GROUP_START:
	case MMC_ERASE_GROUP_END:
	case MMC_ERASE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_GEN_CMD:
		if(cmd_info->cmd->arg & 0x1) {   //read single block
			cmd_info->cmd->arg = 0x1;
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP|CMD_WAIT_PRV_DATA_COMPLETE);
			cmd_info->rsp_len = 6;
			break;
		}
		else {      //write single block
			cmd_info->cmd->arg = 0x0;
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_RD_WR|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
			cmd_info->rsp_len = 6;
			break;
		}
	default:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG);
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

void down_speed_handling(struct rtkemmc_host *emmc_port)
{
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
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
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("down_speed_HS200"));
#endif
		if (readl(emmc_port + EMMC_TBBCNT) == 1024) {
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("down_speed_HS200"));
#endif
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_ISR), ISR_DMA_DONE_INT, ISR_DMA_DONE_INT, __func__);          //card is not busy
			isb();
			sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("down_speed_HS200"));
#endif
			rtkemmc_clr_int_sta();
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("down_speed_HS200"));
#endif
		}
#ifdef CONFIG_ARCH_RTD129x
		else
			rtk_lockapi_unlock2(flags2, _at_("down_speed_HS200"));
#endif

		card_stop(emmc_port);
		polling_to_tran_state(emmc_port,MMC_READ_MULTIPLE_BLOCK,1);//just pick up 1 command index for parameter

		if (!g_bResuming)
			gCurrentBootMode = MODE_SDR;

		rtkemmc_select_card_type(mmc->card);	//do not set the emmc card capability as HS200
		rtkemmc_select_timing(mmc->card);	//send cmd 6 again to inform the host SDR50 mode and set the correct bus speed mode

		rtkemmc_set_freq(emmc_port, 0x57); //100Mhz
		rtkemmc_set_ip_div(emmc_port, EMMC_CLOCK_DIV_2); // 100MHZ/2 = 50MHZ

#ifdef CONFIG_ARCH_RTD129x
		rtkemmc_set_pad_driving(emmc_port,0x33, 0x33, 0x33, 0x33);
#else
		rtkemmc_set_pad_driving(emmc_port,0x0, 0x0, 0x0, 0x0);
#endif
		rtkemmc_writel(3, emmc_port->crt_membase + SYS_PLL_EMMC1);      //980001f0
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
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
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("down_speed_handling"));
#endif
		if (readl(emmc_port + EMMC_TBBCNT) == 1024) {
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("down_speed_handling"));
#endif
			wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_ISR), ISR_DMA_DONE_INT, ISR_DMA_DONE_INT, __func__);          //card is not busy
			isb();
			sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("down_speed_handling"));
#endif
			rtkemmc_clr_int_sta();
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("down_speed_handling"));
#endif
		}
		else {
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("down_speed_handling"));
#endif
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

static int rtkemmc_wait_opt_end(char* drv_name, struct rtkemmc_host *emmc_port,u8 cmdcode,u32 cmd_idx,u8 ignore_log)
{
	volatile int err = RTK_SUCC;
	volatile unsigned long timeend=0;
	unsigned long flags;
	int loop_threshold=0;
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	u32 reg = 0;
	u32 reg_blksize = 0;
	u32 reg_bytecount = 0;
	u32 reg_cmdidx = 0;
	u32 reg_argu = 0;
	u32 i = 0;

	unsigned long msec = TIMEOUT_MS;
	unsigned long dma_msec = 0;

	switch(CMD_IDX_MASK(cmd_idx)) {
		case MMC_READ_SINGLE_BLOCK:
		case MMC_READ_MULTIPLE_BLOCK:
		case MMC_WRITE_BLOCK:
		case MMC_WRITE_MULTIPLE_BLOCK:
		case MMC_SEND_EXT_CSD:
			dma_msec=TIMEOUT_DMA;
			break;
	}
	MMCPRINTF("%s - data_to=%u, dma_to=0x%08x\n","rtkemmc",TIMEOUT_MS,dma_msec);
	//err = rtk_int_enable_and_waitfor(emmc_port,cmdcode,cmd_idx,TIMEOUT_MS,dma_to,ignore_log);
#ifndef ENABLE_EMMC_INT_MODE
	emmc_port->int_waiting = NULL;
#else
	emmc_port->int_waiting = &rtk_emmc_wait;
	MMCPRINTF("%s : msec = %u \n", __func__, msec);
	MMCPRINTF("%s : emmc_port->tmout = %u \n", __func__, emmc_port->tmout);
	MMCPRINTF("rtk wait complete addr = %08x\n", (unsigned int) emmc_port->int_waiting);
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
#endif

#ifdef ENABLE_EMMC_INT_MODE
	if(emmc_port->rtflags & RTKCR_FOPEN_LOG){
		//rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
		printk(KERN_ERR "cmd_idx:%08x ------------------------------>\n",cmd_idx);
		printk(KERN_ERR "rtkemmc - before cmd fired\n\trintsts : 0x%08x mintsts : 0x%08x, status : 0x%08x, idsts : 0x%08x\n\tcmd=0x%08x, cmd_arg=0x%08x\n",
			readl(emmc_port->emmc_membase+EMMC_RINTSTS),readl(emmc_port->emmc_membase+EMMC_MINTSTS),readl(emmc_port->emmc_membase+EMMC_STATUS),
			readl(emmc_port->emmc_membase+EMMC_IDSTS),cmd_idx,readl(emmc_port->emmc_membase+EMMC_CMDARG));
		printk(KERN_ERR "\tbmod : 0x%08x ctrl : 0x%08x, pwren : 0x%08x, intmask : 0x%08x\n\tclkdiv : 0x%08x, clksrc : 0x%08x, clkena : 0x%08x, cmd : 0x%08x\n",
			readl(emmc_port->emmc_membase+EMMC_BMOD),readl(emmc_port->emmc_membase+EMMC_CTRL),readl(emmc_port->emmc_membase+EMMC_PWREN),
			readl(emmc_port->emmc_membase+EMMC_INTMASK),readl(emmc_port->emmc_membase+EMMC_CLKDIV),readl(emmc_port->emmc_membase+EMMC_CLKSRC),
			readl(emmc_port->emmc_membase+EMMC_CLKENA),readl(emmc_port->emmc_membase+EMMC_CMD));
		printk(KERN_ERR "\ttmout : 0x%08x ctype : 0x%08x, fifoth : 0x%08x, idinten : 0x%08x\n\tuhsreg : 0x%08x\n",
			readl(emmc_port->emmc_membase+EMMC_TMOUT),readl(emmc_port->emmc_membase+EMMC_CTYPE),readl(emmc_port->emmc_membase+EMMC_FIFOTH),
			readl(emmc_port->emmc_membase+EMMC_IDINTEN),readl(emmc_port->emmc_membase+EMMC_UHSREG));
		printk(KERN_ERR "------------------------------>\n");
		//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
	}

	if (emmc_port->int_waiting) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
		rtkemmc_hold_int_dec();
		//gpio 100 pull low
#ifdef EMMC_LA_DEBUG_GPIO
		reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
		reg &= (~0x00000010);
		rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
		isb();
		sync(emmc_port);
#endif
		rtkemmc_clr_int_sta();
		ClrINTState(emmc_port);
		emmc_port->int_waiting = &rtk_emmc_wait;

#ifdef EMMC_LA_DEBUG_GPIO
		reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
		reg |= (0x00000010);
		rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
		isb();
		sync(emmc_port);
#endif

		if (CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_WRITE_BLOCK )
			rtkemmc_en_wr_int();//wr case
		else if (CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_READ_SINGLE_BLOCK
			|| CMD_IDX_MASK(cmd_idx)==MMC_SEND_EXT_CSD)//rd case
			rtkemmc_en_rd_int();
                /*else if (CMD_IDX_MASK(cmd_idx)==MMC_SWITCH)
                        rtkemmc_en_cd6_int();*/
		else
			rtkemmc_en_cd_int(); //command case

		//EMMC_CMD bit 31 must be zero, do not need to be protected for emmc register because it is panic funciton
		BUG_ON(readl(emmc_port->emmc_membase+EMMC_CMD) & CMD_START_CMD);

		if (g_bTuning == 0){
#ifdef EMMC_LA_DEBUG_GPIO
			//gpio 90  pull  low
			reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
			reg &= ~(0x04000000);
			rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
			isb();
			sync(emmc_port);
#endif
			//rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
			while (readl(emmc_port->emmc_membase+EMMC_RINTSTS) & (0xfffe)){
				printk(KERN_ERR RED_BOLD "Fail to clear EMMC_RINTSTS! EMMC_RINTSTS = 0x%08x, CMDIDX = %d \n"RESET, 
					readl(emmc_port->emmc_membase+EMMC_RINTSTS), CMD_IDX_MASK(cmd_idx));
				rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0x0000fffe, emmc_port->emmc_membase+EMMC_RINTSTS);
			}
			//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#ifdef EMMC_LA_DEBUG_GPIO
                        //gpio 90  pull  high
			reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
			reg |= (0x04000000);
			rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
			isb();
			sync(emmc_port);
#endif
		}
		if (g_bTuning == 1) {		//in Tuning process, clear the error bit before cmd fire for fear that cmd 12,13 error because the previous cmd 18,25 tuning error bit
			rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0xb7c2, emmc_port->emmc_membase+EMMC_RINTSTS);
			loop_threshold = 0;
			while (readl(emmc_port->emmc_membase+EMMC_RINTSTS) & (0xb7c2)){
				++loop_threshold;
				if(loop_threshold > 5) {
					printk(KERN_ERR RED_BOLD "Tuning: Fail to clear EMMC_RINTSTS! EMMC_RINTSTS = 0x%08x, CMDIDX = %d \n"RESET,
						readl(emmc_port->emmc_membase+EMMC_RINTSTS), CMD_IDX_MASK(cmd_idx));
				}
				sync(emmc_port);
				rtkemmc_writel(readl(emmc_port->emmc_membase+EMMC_RINTSTS)&0xb7c2, emmc_port->emmc_membase+EMMC_RINTSTS);
                        }
		}

		if (CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK ){
			if (emmc_port->rpmb_cmd)
				cmd_idx &= (~CMD_SEND_AUTO_STOP); //CMD25/18 following CMD13, never set CMD_SEND_AUTO_STOP(bit 12)
                }

		//cmd fire
		//rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
		spin_lock_irqsave(&emmc_port->lock,flags);
		reg_blksize = readl(emmc_port->emmc_membase+EMMC_BLKSIZE);
		reg_bytecount = readl(emmc_port->emmc_membase+EMMC_BYTCNT);
		reg_argu = readl(emmc_port->emmc_membase+EMMC_CMDARG);
		rtkemmc_writel(cmd_idx,emmc_port->emmc_membase+EMMC_CMD);
		reg_cmdidx = readl(emmc_port->emmc_membase+EMMC_CMD);
		spin_unlock_irqrestore(&emmc_port->lock,flags);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
		wait_for_completion(emmc_port->int_waiting);

		if (emmc_port->rintsts & INT_STS_ERRORS) {
			/*if (CMD_IDX_MASK(cmd_idx)==MMC_SWITCH && (emmc_port->rintsts & INT_STS_ERRORS2) == 0) {
				goto chk_status;
			}*/
			if (!ignore_log) {
				if (CMD_IDX_MASK(cmd_idx)!=MMC_GO_IDLE_STATE) {
					printk(KERN_ERR "rtkemmc - INT_STS_ERRORS, cmd_idx=0x%08x, rintsts=0x%08x, idsts=0x%08x, status=0x%08x\n", 
						cmd_idx, emmc_port->rintsts, emmc_port->idsts, emmc_port->status);
					printk(KERN_ERR "rtkemmc - read cmd_idx = 0x%08x\n", reg_cmdidx);
					printk(KERN_ERR "rtkemmc - read reg_argu = 0x%08x\n", reg_argu);
					printk(KERN_ERR "rtkemmc - read byte count = 0x%08x\n", reg_bytecount);
					printk(KERN_ERR "rtkemmc - read blk size = 0x%08x\n", reg_blksize);
					printk(KERN_ERR "rtkemmc - read rtkemmc_global_blksize = 0x%08x\n", rtkemmc_global_blksize);
					printk(KERN_ERR "rtkemmc - read rtkemmc_global_bytecnt = 0x%08x\n", rtkemmc_global_bytecnt);
					printk(KERN_ERR "rtkemmc - read rtkemmc_global_dbaddr = 0x%08x\n", rtkemmc_global_dbaddr);
					print_reg_sts(cmd_idx,emmc_port->rintsts);
					print_ip_desc(emmc_port);

					if((emmc_port->rintsts & INT_STS_DCRC) && (CMD_IDX_MASK(cmd_idx)==18 || CMD_IDX_MASK(cmd_idx)==25) )
						cmd_resend=1;
					else if((emmc_port->rintsts & INT_STS_RTO_BAR) && CMD_IDX_MASK(cmd_idx)==6)
						cmd_resend=1;
				}
			}
			else{ //in tuning, only print rintsts
				if (CMD_IDX_MASK(cmd_idx)!=MMC_GO_IDLE_STATE && (emmc_port->rintsts & (INT_STS_HTO | INT_STS_HLE | INT_STS_DRTO_BDS))) {
					printk(KERN_ERR "Tuning: HTO/HLE/DRTO - INT_STS_ERRORS, cmd_idx=0x%08x, rintsts=0x%08x, idsts=0x%08x, status=0x%08x\n",
						CMD_IDX_MASK(cmd_idx), emmc_port->rintsts, emmc_port->idsts, emmc_port->status);
				}
			}

			err = RTK_FAIL;

			// in HS200 tuning, skip status busy check with emmc error
			if (g_bTuning && (CMD_IDX_MASK(cmd_idx)==MMC_STOP_TRANSMISSION || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK)) {
			//	printk(KERN_ERR "opt_end: Tuning cmd18 error and goto bit31 check\n");
				goto chk_cmd_bit31;
			}
			else
				goto chk_status;
		}
		//polling ACD for multiple r/w
		
		if (CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK ) {
			//for rpmb rw cmd, don't need to polling ACD
			if (emmc_port->rpmb_cmd)
				emmc_port->rpmb_cmd = 0;
			else {
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
				timeend = jiffies + msecs_to_jiffies(msec);
				MMCPRINTF("[%s:%d] Start polling ACD........\n", __FILE__, __LINE__);
				while(time_before(jiffies, timeend))
#else
				MMCPRINTF("[%s:%d] Start polling ACD........\n", __FILE__, __LINE__);
				while(1)
#endif
				{
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					reg = readl(emmc_port->emmc_membase+EMMC_RINTSTS);
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif

					if (reg & INT_STS_ERRORS){
						err = RTK_FAIL;
						if (g_bTuning && (CMD_IDX_MASK(cmd_idx)==MMC_STOP_TRANSMISSION || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK))
							goto chk_cmd_bit31;
						else
							goto chk_status;
					}

					if ( reg & (INT_STS_ACD)) {
						err = RTK_SUCC;
#ifdef CONFIG_ARCH_RTD129x
						if (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01 ) {
							for (i = 0; i < 100000; i++)
								asm volatile("nop" : : : );
						}
#endif
						i=0;
						while (1) {
#ifdef CONFIG_ARCH_RTD129x
							rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
							reg = readl(emmc_port->emmc_membase+EMMC_STATUS);
							asm volatile("nop" : : : );
#ifdef CONFIG_ARCH_RTD129x
							rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
							if( ( (reg & STS_RSP_IDX_MASK)>>STS_RSP_IDX ) == MMC_STOP_TRANSMISSION )
								break;
							if ( i == 0 ) {
#ifdef CONFIG_ARCH_RTD129x
								rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
								printk(KERN_ERR RED_BOLD"[%s:%d] wait STOP after ACD fail ........\n"RESET, __FILE__, __LINE__);
								printk(KERN_ERR RED_BOLD"rtkemmc - \n\trintsts : 0x%08x mintsts : 0x%08x, status : 0x%08x, \
									idsts : 0x%08x\n\tcmd=0x%08x, cmd_arg=0x%08x\n"RESET, 
									readl(emmc_port->emmc_membase+EMMC_RINTSTS),
									readl(emmc_port->emmc_membase+EMMC_MINTSTS),
									readl(emmc_port->emmc_membase+EMMC_STATUS),
									readl(emmc_port->emmc_membase+EMMC_IDSTS),
									cmd_idx,
									readl(emmc_port->emmc_membase+EMMC_CMDARG));
#ifdef CONFIG_ARCH_RTD129x
								rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
							}
							if (i++ > 0x100000) {
#ifdef CONFIG_ARCH_RTD129x
								rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
								printk(KERN_ERR RED_BOLD"[%s:%d] polling STOP after ACD fail ........\n"RESET, __FILE__, __LINE__);
								printk(KERN_ERR RED_BOLD"rtkemmc - \n\trintsts : 0x%08x mintsts : 0x%08x, status : 0x%08x,	\
									idsts : 0x%08x\n\tcmd=0x%08x, cmd_arg=0x%08x\n"RESET,
									readl(emmc_port->emmc_membase+EMMC_RINTSTS),
									readl(emmc_port->emmc_membase+EMMC_MINTSTS),
									readl(emmc_port->emmc_membase+EMMC_STATUS),
									readl(emmc_port->emmc_membase+EMMC_IDSTS),
									cmd_idx,
									readl(emmc_port->emmc_membase+EMMC_CMDARG));
#ifdef CONFIG_ARCH_RTD129x
								rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
								break;
							}
							usleep_range(10, 30);
						}
						break;
					}
					usleep_range(10, 30);
				}

				MMCPRINTF("[%s:%d] End polling ACD........\n", __FILE__, __LINE__);
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
#ifdef CONFIG_ARCH_RTD129x
				rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
				if (!(readl(emmc_port->emmc_membase+EMMC_RINTSTS) & INT_STS_ACD) && time_after_eq(jiffies, timeend)) {
					if (!ignore_log)
						printk(KERN_ERR "[%s:%d] ACD Timeout!!!........, cmd_idx=%d, EMMC_RINTSTS=0x%x\n", __FILE__, __LINE__, CMD_IDX_MASK(cmd_idx), readl(emmc_port->emmc_membase+EMMC_RINTSTS));
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					err = RTK_TOUT;
					goto chk_status;
				}
#ifdef CONFIG_ARCH_RTD129x
				else rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#endif
			}
		}
		//polling dma_done_int is not reliable when transaction > 4KB, i.e, more than one set of descriptor,
		//because dma_done_int raised when one descriptor finished.
		if (dma_msec > 0) {
			if ((CMD_IDX_MASK(cmd_idx)==MMC_READ_SINGLE_BLOCK)||(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK)||(CMD_IDX_MASK(cmd_idx)==MMC_SEND_EXT_CSD)) {
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
				timeend = jiffies + msecs_to_jiffies(dma_msec);
#ifdef CONFIG_ARCH_RTD139x
				if(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK && (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01))	//139x cmd18 has bug, we polling the dma length instead of dma done
					MMCPRINTF("[%s:%d] Start polling DMA_LENGTH........\n", __FILE__, __LINE__);
				else
					MMCPRINTF("[%s:%d] Start polling DMA_DONE........\n", __FILE__, __LINE__);
#else
				MMCPRINTF("[%s:%d] Start polling DMA_DONE........\n", __FILE__, __LINE__);
#endif
				while(time_before(jiffies, timeend))
#else
#ifdef CONFIG_ARCH_RTD139x
				if(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK && (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01))      //139x cmd18 has bug, we polling the dma length instead of dma done
                                        MMCPRINTF("[%s:%d] Start polling DMA_LENGTH........\n", __FILE__, __LINE__);
                                else
                                        MMCPRINTF("[%s:%d] Start polling DMA_DONE........\n", __FILE__, __LINE__);
#else
				MMCPRINTF("[%s:%d] Start polling DMA_DONE........\n", __FILE__, __LINE__);
#endif
				while(1)
#endif
				{
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					reg = readl(emmc_port->emmc_membase+EMMC_RINTSTS);
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					if (reg & INT_STS_ERRORS){
						err = RTK_FAIL;
						if (g_bTuning && (CMD_IDX_MASK(cmd_idx)==MMC_STOP_TRANSMISSION || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK))
							goto chk_cmd_bit31;
						else
							goto chk_status;
					}
#ifdef CONFIG_ARCH_RTD139x
					if(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK && (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01)) {
						if(readl(emmc_port->emmc_membase + EMMC_BYTCNT) == readl(emmc_port->emmc_membase + EMMC_TBBCNT)) {
							rtkemmc_writel(ISR_DMA_DONE_INT, emmc_port->emmc_membase+EMMC_ISR);
							usleep_range(50,100);
							err = RTK_SUCC;
							MMCPRINTF("RTKEMMC - rd done, rintsts : 0x%08x, isr : 0x%08x, idsts : 0x%08x\n",
							readl(emmc_port->emmc_membase+EMMC_RINTSTS), readl(emmc_port->emmc_membase+EMMC_ISR), readl(emmc_port->emmc_membase+EMMC_IDSTS));
							break;
						}
					}
					else {
						if (readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT) {
							//printk(KERN_ERR "POLLING DMA_DONE \n");
							//clear dma_done_int
							rtkemmc_writel(ISR_DMA_DONE_INT, emmc_port->emmc_membase+EMMC_ISR);
							err = RTK_SUCC;
							MMCPRINTF("RTKEMMC - rd done, rintsts : 0x%08x, isr : 0x%08x, idsts : 0x%08x\n",
							readl(emmc_port->emmc_membase+EMMC_RINTSTS), readl(emmc_port->emmc_membase+EMMC_ISR), readl(emmc_port->emmc_membase+EMMC_IDSTS));
							break;
						}
					}
#else
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					if (readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT) {
						//printk(KERN_ERR "POLLING DMA_DONE \n");
						//clear dma_done_int
						rtkemmc_writel(ISR_DMA_DONE_INT, emmc_port->emmc_membase+EMMC_ISR);
						err = RTK_SUCC;
						MMCPRINTF("RTKEMMC - rd done, rintsts : 0x%08x, isr : 0x%08x, idsts : 0x%08x\n", 
							readl(emmc_port->emmc_membase+EMMC_RINTSTS), readl(emmc_port->emmc_membase+EMMC_ISR), readl(emmc_port->emmc_membase+EMMC_IDSTS));
#ifdef CONFIG_ARCH_RTD129x
						rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
						break;
					}
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#endif
					MMCPRINTF("ISR = 0x%08x \n", readl(emmc_port->emmc_membase+EMMC_ISR));
					usleep_range(10, 30);
				}
#ifdef CONFIG_ARCH_RTD139x
				if(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK && (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01))
					MMCPRINTF("[%s:%d] End polling DMA_LENGTH........\n", __FILE__, __LINE__);
				else
					MMCPRINTF("[%s:%d] End polling DMA_DONE........\n", __FILE__, __LINE__);
#else
				MMCPRINTF("[%s:%d] End polling DMA_DONE........\n", __FILE__, __LINE__);
#endif
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
#ifdef CONFIG_ARCH_RTD139x
				if(CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK && (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01)) {
					if (readl(emmc_port->emmc_membase + EMMC_BYTCNT)!=readl(emmc_port->emmc_membase + EMMC_TBBCNT) && time_after_eq(jiffies, timeend)) {
						printk(KERN_ERR "[%s:%d] DMA_DONE length is unequal expected read bytes = %x, real read bytes = %x !!!........\n"
							, __FILE__, __LINE__,readl(emmc_port->emmc_membase + EMMC_BYTCNT),readl(emmc_port->emmc_membase + EMMC_TBBCNT));
						err = RTK_TOUT;
						goto chk_status;
					}
				}
				else {
					if ((readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT) && time_after_eq(jiffies, timeend)) {
						printk(KERN_ERR "[%s:%d] cmd_idx=%d, EMMC_ISR=0x%x, DMA_DONE Timeout !!!........\n", __FILE__, __LINE__, CMD_IDX_MASK(cmd_idx), readl(emmc_port->emmc_membase+EMMC_ISR));
						err = RTK_TOUT;
						goto chk_status;
					}

				}
#else
#ifdef CONFIG_ARCH_RTD129x
				rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
				if ((readl(emmc_port->emmc_membase+EMMC_ISR) & ISR_DMA_DONE_INT) && time_after_eq(jiffies, timeend)) {
					printk(KERN_ERR "[%s:%d] cmd_idx=%d, EMMC_ISR=0x%x, DMA_DONE Timeout !!!........\n", __FILE__, __LINE__, CMD_IDX_MASK(cmd_idx), readl(emmc_port->emmc_membase+EMMC_ISR));
#ifdef CONFIG_ARCH_RTD129x
					rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
					err = RTK_TOUT;
					goto chk_status;
				}
#ifdef CONFIG_ARCH_RTD129x
				else rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#endif
#endif
			}
		}
chk_status: //check status busy
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
		timeend = jiffies + msecs_to_jiffies(msec);
		//pr_err("[%s:%d] Start polling STATUS BUSY........\n", __FILE__, __LINE__);
		while(time_before(jiffies, timeend))
#else
		//pr_err("[%s:%d] Start polling STATUS BUSY........\n", __FILE__, __LINE__);
		while(1)
#endif
		{
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			if ((readl(emmc_port->emmc_membase+EMMC_STATUS) & STS_DATA_BUSY)== 0) {
				SetINTState(emmc_port, INT_STAT_DATA_DONE);
#ifdef CONFIG_ARCH_RTD129x
				rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
				break;
			}
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			usleep_range(500, 1000);
		}

#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
		if ((readl(emmc_port->emmc_membase+EMMC_STATUS) & STS_DATA_BUSY) && time_after_eq(jiffies, timeend)) {
			printk(KERN_ERR "[%s:%d] STS_DATA_BUSY Timeout !!!........, cmd_idx=%d, EMMC_STATUS=%x EMMC_RINTSTS=%x, cmd.arg=%x\n", __FILE__, __LINE__,CMD_IDX_MASK(cmd_idx), readl(emmc_port->emmc_membase+EMMC_STATUS),readl(emmc_port->emmc_membase+EMMC_RINTSTS),readl(emmc_port->emmc_membase+EMMC_CMDARG));
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			err = RTK_TOUT;
		}
#ifdef CONFIG_ARCH_RTD129x
		else rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#endif

chk_cmd_bit31:
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
		MMCPRINTF("RTKEMMC - done: rintsts : 0x%08x, isr : 0x%08x, idsts : 0x%08x\n", emmc_port->rintsts, emmc_port->dma_isr, readl(emmc_port->emmc_membase+EMMC_IDSTS));
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
		timeend = jiffies + msecs_to_jiffies(TIMEOUT_CMD); //timeout 10 secs
		while(time_before(jiffies, timeend))
#else
		while(1)
#endif
		{
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			reg = readl(emmc_port->emmc_membase+EMMC_CMD);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			if( (reg & CMD_START_CMD) == 0)
				break;

			usleep_range(10, 30);
		}
#ifndef CONFIG_MMC_RTKEMMC_JIFFY_NOT_WORK_ON_1_LAYER_FPGA
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
		if ((readl(emmc_port->emmc_membase+EMMC_CMD)&CMD_START_CMD) && time_after_eq(jiffies, timeend)) {
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			printk(KERN_ERR "cmd_idx=%d, EMMC_CMD bit31 can't recover to 0 \n", CMD_IDX_MASK(cmd_idx));
			BUG();
		}
#ifdef CONFIG_ARCH_RTD129x
		else rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
#endif
		//cmd 13 for tx tuning
		if (g_bTuning && err != RTK_SUCC && CMD_IDX_MASK(cmd_idx)== MMC_SEND_STATUS){
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_lock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			reg = readl(emmc_port->emmc_membase+EMMC_RINTSTS);
#ifdef CONFIG_ARCH_RTD129x
			rtk_lockapi_unlock2(flags2, _at_("rtkemmc_wait_opt_end"));
#endif
			if (!(reg & 0x8180)) //only 0x8180 is the real error for tx tuning
				err = RTK_SUCC;
		}
                return err;
        }
	err = RTK_FAIL;
	return err;
#endif
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
			tmp_val = 0x80000000 | 0x2 | 0x10;              /* setting des0; transfer parameter  */
			if(i==0 && remain_blk_cnt == blk_cnt )
				tmp_val |= 0x8;

			if(i==dma_nents-1 && remain_blk_cnt <= EMMC_MAX_SCRIPT_BLK)
				tmp_val |= 0x4;

			des_base[0] = tmp_val;
			 /* setting des1; buffer size in byte */
			if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK)
				blk_cnt2 = EMMC_MAX_SCRIPT_BLK;
			else
				blk_cnt2 = remain_blk_cnt;

			des_base[1] = (blk_cnt2<<9);
			des_base[2] = (dma_addr);               /* setting des2; Physical address to DMA to/from */
			des_base[3] = p_des_base + 16;                  /* setting des3; next descrpter entry */

			MMCPRINTF("%s - remain cnt : 0x%08x, desc[0]=0x%08x, desc[1]=0x%08x, desc[2]=0x%08x, desc[3]=0x%08x\n",
				__func__, remain_blk_cnt,des_base[0],des_base[1],des_base[2],des_base[3]);

			dma_addr = dma_addr+(blk_cnt2<<9);
			remain_blk_cnt -= blk_cnt2;
			des_base += 4;
			p_des_base += 16;  // 4 * 4
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

#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#else
	__flush_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#endif /* CONFIG_ARCH_MULTI_V7 */

	isb();
	sync(emmc_port);

	MMCPRINTF("RTKEMMC: des_base = 0x%08x\n", des_base);
	//blk_cnt must be the multiple of 512(0x200)
	blk_cnt  = dma_length>>9;
	remain_blk_cnt  = blk_cnt;

	isb();
	sync(emmc_port);

	while(remain_blk_cnt) {
		/* setting des0; transfer parameter  */
		tmp_val = 0x80000000 | 0x2 | 0x10;

		if(remain_blk_cnt == blk_cnt)
			tmp_val |= 0x8;

		if(remain_blk_cnt <= EMMC_MAX_SCRIPT_BLK)
			tmp_val |= 0x4;

		des_base[0] = tmp_val;

		/* setting des1; buffer size in byte */
		if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK)
			blk_cnt2 = EMMC_MAX_SCRIPT_BLK;
		else
			blk_cnt2 = remain_blk_cnt;

		des_base[1] = (blk_cnt2<<9);
		des_base[2] = (dma_addr);	/* setting des2; Physical address to DMA to/from */
		des_base[3] = p_des_base + 16;	/* setting des3; next descrpter entry */

		isb();
		sync(emmc_port);

		MMCPRINTF("%s - remain cnt : 0x%08x, desc[0]=0x%08x, desc[1]=0x%08x, desc[2]=0x%08x, desc[3]=0x%08x\n",
			__func__, remain_blk_cnt,des_base[0],des_base[1],des_base[2],des_base[3]);

		dma_addr = dma_addr+(blk_cnt2<<9);
		remain_blk_cnt -= blk_cnt2;
		des_base += 4;
		p_des_base += 16;  // 4 * 4
		isb();
		sync(emmc_port);
	}

#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#else
	__flush_dcache_area(gddr_descriptor, DESC_ALLOC_LENGTH);
#endif /* CONFIG_ARCH_MULTI_V7 */

	isb();
	sync(emmc_port);
}

static void rtkemmc_read_rsp(struct rtkemmc_host *emmc_port,u32 *rsp, int reg_count)
{
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	MMCPRINTF("rsp addr=0x%p; rsp_count=%u\n", rsp, reg_count);
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_read_rsp"));
#endif
	if ( reg_count==6 ){
		rsp[0] = rsp[1] = 0;
		rsp[0] = readl(emmc_port->emmc_membase + EMMC_RESP0);
		MMCPRINTF(KERN_INFO "rsp[0]=0x%08x, rsp[1]=0x%08x\n",rsp[0],rsp[1]);
	}else if(reg_count==17){
		/*1. UNSTUFF_BITS uses the reverse order as: const int __off = 3 - ((start) / 32);
		  2. be32_to_cpu is called in mmc_send_csd as csd[i] = be32_to_cpu(csd_tmp[i]);*/

		rsp[3] = readl(emmc_port->emmc_membase + EMMC_RESP0);
		rsp[2] = readl(emmc_port->emmc_membase + EMMC_RESP1);
		rsp[1] = readl(emmc_port->emmc_membase + EMMC_RESP2);
		rsp[0] = readl(emmc_port->emmc_membase + EMMC_RESP3);
		MMCPRINTF(KERN_INFO "rsp[0]=0x%08x, rsp[1]=0x%08x, rsp[2]=0x%08x, rsp[3]=0x%08x\n",rsp[0],rsp[1],rsp[2],rsp[3]);
	}
	else
		MMCPRINTF("rsp[0]=0x%08x\n",rsp[0]);
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("rtkemmc_read_rsp"));
#endif
}

static int rtkemmc_send_status(struct mmc_card *card,u8 * state,u8 divider,int bIgnore)
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
		u8 cur_state = R1_CURRENT_STATE(cmd.resp[0]);
		*state = cur_state;
		if (!bIgnore)
		printk(KERN_INFO "cur_state=%s\n",state_tlb[cur_state]);
	}

	return err;
}

static int SD_SendCMDGetRSP_Cmd(struct sd_cmd_pkt *cmd_info,int bIgnore)
{
	volatile u8 cmd_idx              = cmd_info->cmd->opcode;
	u32 *rsp                = (u32 *)&cmd_info->cmd->resp;
	struct rtkemmc_host *emmc_port = cmd_info->emmc_port;
	struct mmc_host *host = emmc_port->mmc;
	int err, retry_count=0;
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	u8 state = 0;
	int cmd1_retry_cnt = 3000;
	MMCPRINTF("%s \n", __func__);

	rtkemmc_set_rspparam(emmc_port,cmd_info);   //for 1295
	if(rsp == NULL)
		BUG_ON(1);

	if ((g_crinit == 0)&&(cmd_idx > MMC_SET_RELATIVE_ADDR)) {
		printk("%s : ignore cmd:0x%02x since we're still in emmc init stage\n",DRIVER_NAME,cmd_idx);
		return CR_TRANSFER_FAIL;
	}

RET_CMD:
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("SD_SendCMDGetRSP_Cmd"));
#endif
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
//	rtkemmc_writel(1, emmc_port->emmc_membase + EMMC_SWC_SEL);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL1);
	rtkemmc_writel(1, emmc_port->emmc_membase + EMMC_SWC_SEL2);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL3);
#else
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL);
#endif
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_CP);
	//gpio 100 pull low
#ifdef EMMC_LA_DEBUG_GPIO
	reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
	reg &= (~0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
	isb();
	sync(emmc_port);
#endif

	rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_CMDARG);
	isb();
	sync(emmc_port);
	//gpio 100 pull high
#ifdef EMMC_LA_DEBUG_GPIO
	reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
	reg |= (0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
	isb();
	sync(emmc_port);
#endif

#ifdef EMMC_LA_DEBUG_GPIO
	//gpio 90  pull  low
	reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
	reg &= ~(0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
	isb();
	sync(emmc_port);
#endif

	//workaround, if fail to write EMMC_CMDARG, re-write
	while(readl(emmc_port->emmc_membase + EMMC_CMDARG) != cmd_info->cmd->arg) {
		printk(KERN_ERR RED_BOLD"SD_SendCMDGetRSP_Cmd: Fail to write EMMC_CMDARG ! \n"RESET);
		printk(KERN_ERR "cmd_info->opcode = 0x%08x \n", cmd_info->cmd->opcode );
		printk(KERN_ERR "cmd_info->cmd->arg = 0x%08x \n", cmd_info->cmd->arg );
		printk(KERN_ERR "EMMC_CMDARG = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CMDARG));
		//BUG();
		rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_CMDARG);
		isb();
		sync(emmc_port);
	}
#ifdef EMMC_LA_DEBUG_GPIO
	//gpio 90  pull  high
	reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
	reg |= (0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
	isb();
	sync(emmc_port);
#endif
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("SD_SendCMDGetRSP_Cmd"));
#endif

	if (cmd_idx == MMC_SET_BLOCK_COUNT)
		emmc_port->rpmb_cmd = 1;
	else
		emmc_port->rpmb_cmd = 0;
	err = rtkemmc_wait_opt_end(DRIVER_NAME,emmc_port,EMMC_SENDCMDGETRSP,(cmd_idx|cmd_info->cmd_para),bIgnore);
	if(err == RTK_SUCC){
		sync(emmc_port);
		rtkemmc_read_rsp(emmc_port,rsp, cmd_info->rsp_len);
		sync(emmc_port);
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
			rtkemmc_send_status(host->card,&state,0,0);
		}
	}
	else {
		if (!bIgnore)
			printk(KERN_WARNING "%s: %s cmd trans fail, err=%d, ignore=%d, gPreventRetry=%d, gCurrentBootMode=%d, cmd_idx=%d\n",
				DRIVER_NAME,__func__, err, bIgnore,gPreventRetry,gCurrentBootMode,cmd_idx);
		MMCPRINTF("%s: %s gCurrentBootMode =%d\n", DRIVER_NAME, __func__, gCurrentBootMode);

		if (gPreventRetry) {
			printk(KERN_WARNING "[LY]error when card in uninit state, err=%d\n",err);
			return err;
		}
		if (gCurrentBootMode > MODE_SDR && cmd_idx > MMC_SEND_OP_COND)
			return err;
		if (cmd_idx == MMC_SEND_STATUS) //prevent dead lock looping
			return err;
		if (retry_count++ < MAX_CMD_RETRY_COUNT) {
			printk(KERN_ERR RED_BOLD"cmd %d retry %d ---->\n"RESET,cmd_idx,retry_count);
			err = error_handling(emmc_port,cmd_idx,bIgnore);
			goto RET_CMD;
		}
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
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	u32 retry_count=0;
	MMCPRINTF("%s \n", __func__);

	if(rsp == NULL)
		BUG_ON(1);

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
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("SD_Stream_Cmd"));
#endif
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
//	rtkemmc_writel(1, emmc_port->emmc_membase + EMMC_SWC_SEL);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL1);
	rtkemmc_writel(1, emmc_port->emmc_membase + EMMC_SWC_SEL2);
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL3);
#else
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_SWC_SEL);
#endif
	rtkemmc_writel(0, emmc_port->emmc_membase + EMMC_CP);
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("SD_Stream_Cmd"));
#endif
	/*************************************************************************/
#ifndef CONFIG_RTK_XEN_SUPPORT
	if (cmd_info->data)
		make_sg_des(cmd_info, emmc_port->desc_paddr, emmc_port);
	else if (data)
		make_ip_des(data, block_count<<9, emmc_port->desc_paddr, emmc_port);
	else
		BUG_ON(1);
#else
	make_ip_des(data, block_count<<9, emmc_port->desc_paddr, emmc_port);
#endif
STR_CMD_RET:
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("SD_Stream_Cmd"));
#endif
	rtkemmc_writel(block_count<<9, emmc_port->emmc_membase + EMMC_BYTCNT);
	rtkemmc_writel(emmc_port->desc_paddr, emmc_port->emmc_membase + EMMC_DBADDR);
	rtkemmc_global_blksize = readl(emmc_port->emmc_membase + EMMC_BLKSIZE);
	rtkemmc_global_bytecnt = readl(emmc_port->emmc_membase + EMMC_BYTCNT);
	rtkemmc_global_dbaddr = readl(emmc_port->emmc_membase + EMMC_DBADDR);
	MMCPRINTF("%s EMMC_BYTCNT=0x%x  \n", __func__, rtkemmc_global_bytecnt);
	//gpio 100 pull low
#ifdef EMMC_LA_DEBUG_GPIO
	reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
	reg &= (~0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
	isb();
	sync(emmc_port);
#endif

	rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_CMDARG);
	isb();
	sync(emmc_port);

	//gpio 100 pull high
#ifdef EMMC_LA_DEBUG_GPIO
	reg = readl(emmc_port->misc_membase + MISC_GP3DATO);
	reg |= (0x00000010);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP3DATO);
	isb();
	sync(emmc_port);
#endif

#ifdef EMMC_LA_DEBUG_GPIO
	//gpio 90  pull  low
	reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
	reg &= ~(0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
	isb();
	sync(emmc_port);
#endif

	//workaround, if fail to write EMMC_CMDARG, re-write
	while(readl(emmc_port->emmc_membase + EMMC_CMDARG) != cmd_info->cmd->arg) {
		printk(KERN_ERR RED_BOLD"SD_Stream_Cmd: Fail to write EMMC_CMDARG ! \n"RESET);
		printk(KERN_ERR "cmd_info->opcode = 0x%08x \n", cmd_info->cmd->opcode );
		printk(KERN_ERR "cmd_info->cmd->arg = 0x%08x \n", cmd_info->cmd->arg );
		printk(KERN_ERR "EMMC_CMDARG = 0x%08x \n", readl(emmc_port->emmc_membase + EMMC_CMDARG));
		rtkemmc_writel(cmd_info->cmd->arg, emmc_port->emmc_membase + EMMC_CMDARG);
		isb();
		sync(emmc_port);
	}

	//gpio 90  pull  high
#ifdef EMMC_LA_DEBUG_GPIO
	reg = readl(emmc_port->misc_membase + MISC_GP2DATO);
	reg |= (0x04000000);
	rtkemmc_writel(reg, emmc_port->misc_membase + MISC_GP2DATO);
	isb();
	sync(emmc_port);
#endif

	emmc_port->cmd_opcode = cmd_idx;
	MMCPRINTF(KERN_INFO "%s - cmdidx:0x%02x, byte_cnt:0x%08x, cmd_arg:0x%08x \n", __func__,
		cmd_idx, readl(emmc_port->emmc_membase + EMMC_BYTCNT), readl(emmc_port->emmc_membase + EMMC_CMDARG));

	rtkemmc_get_cmd_timeout(cmd_info);
	isb();
	sync(emmc_port);
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("SD_Stream_Cmd"));
#endif
	err = rtkemmc_wait_opt_end(DRIVER_NAME,emmc_port,cmdcode,(cmd_idx|cmd_info->cmd_para),bIgnore);
	//wait_done_timeout(emmc_port, (u32*)(emmc_port->emmc_membase + EMMC_CMD), 0x80000000, 0x0);
	isb();
	sync(emmc_port);

	if(err == RTK_SUCC) {
		if((cmdcode == EMMC_AUTOREAD1) || (cmdcode == EMMC_AUTOWRITE1))
			MMCPRINTF("AUTO READ/WRITE 1 skip response~\n");
		else {
			rtkemmc_read_rsp(emmc_port,rsp, cmd_info->rsp_len);
			MMCPRINTF("---stream cmd done---\n");
		}
	}
	else {
		if(cmd_resend==1) //down speed handling
			return RTK_SUCC;

		MMCPRINTF("strm cmd_idx=%d,ret_err=%d,bIgnore=%d\n",cmd_idx ,err,bIgnore);
		mmcmsg3(KERN_WARNING "%s: %s fail\n",DRIVER_NAME,__func__);
		if (bIgnore)
			return err;

		if (retry_count++ < MAX_CMD_RETRY_COUNT) {
			err = error_handling(emmc_port,cmd_idx,bIgnore);
			goto STR_CMD_RET;
		}
	}
	return err;
}

int polling_to_tran_state(struct rtkemmc_host *emmc_port, int cmd_idx, int bIgnore)
{
	int err=1, retry_cnt=5;
	u8 ret_state=0;
	struct mmc_host *host = emmc_port->mmc;

	MMCPRINTF("%s : \n", __func__);
	sync(emmc_port);
	while(retry_cnt-- && err)
        	err = rtkemmc_send_status(host->card,&ret_state,0,bIgnore);

	sync(emmc_port);

	if ((err)||(ret_state != STATE_TRAN)) {
#ifdef EMMC_DEBUG
		printk("--- cmd13 fail or ret_state not tran : 0x%08x---\n", ret_state);
#endif
//		if ((cmd_idx != MMC_READ_SINGLE_BLOCK)&&(cmd_idx != MMC_WRITE_BLOCK))
		rtkemmc_stop_transmission(host->card,1);
		err = rtkemmc_wait_status(host->card,STATE_TRAN,0,bIgnore);
	}
	sync(emmc_port);
	return err;
}

int error_handling(struct rtkemmc_host *emmc_port, unsigned int cmd_idx, unsigned int bIgnore)
{
	int err=0;

	printk(KERN_INFO "%s : cmd_idx=0x%02x, gCurrentBootMode=0x%02x\n", __func__, cmd_idx, gCurrentBootMode);

	card_stop(emmc_port);

	if (cmd_idx > MMC_SET_RELATIVE_ADDR)
		polling_to_tran_state(emmc_port,cmd_idx,bIgnore);

	printk(KERN_INFO "%s : cmd_idx=0x%02x, gCurrentBootMode=0x%02x\n", __func__,cmd_idx,gCurrentBootMode);
	if (bIgnore)
		return 0;
	return err;
}

static int rtkemmc_err_handle(u16 cmdcode,struct sd_cmd_pkt *cmd_info)
{
	struct mmc_host *host = cmd_info->emmc_port->mmc;
	u8 state = 0;
	int err = 0;

	MMCPRINTF("(%s:%d) : cmd=0x%02x\n", __func__,__LINE__,cmdcode);

	if(host->card) {
		if(cmdcode == EMMC_AUTOWRITE2) {
			if( cmd_info->cmd->opcode == 18 || cmd_info->cmd->opcode == 25 ) {
				int stop_loop = 5;

				while(stop_loop--) {
					err = rtkemmc_stop_transmission(host->card,0);
					if(err) {
						//mdelay(1);
						rtkemmc_send_status(host->card,&state,0,0);
						if(state == STATE_TRAN)
							break;
					}
					else
						break;
				}
			}
		}
		MMCPRINTF("(%s:%d) - cmd=0x%/02x, before polling TRAN state\n", __func__,__LINE__,cmdcode);
		err = rtkemmc_wait_status(host->card,STATE_TRAN,0,0);
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
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
	unsigned int reg_val;
	unsigned long tmout;
	unsigned long curr_jiffies;
	int istimeout;
	int read_reg_yet;
	MMCPRINTF("%s \n", __func__);

	memset(&cmd_info, 0, sizeof(struct sd_cmd_pkt));

	if ( !emmc_port || !cmd ){
		printk(KERN_ERR "%s: emmc_port or cmd is null\n",DRIVER_NAME);
		return ;
	}

	cmd_info.cmd    = cmd;
	cmd_info.emmc_port = emmc_port;
#ifdef FORCE_CHECK_CMD_AND_STS
	// ChiYun's comment
	// wait_done((UINT32 *)0x9801202c, 0x80000000, 0);      //cmd done
	// wait_done((UINT32 *)0x98012048, 0x000006f0, 0);      //idle
	istimeout = 1;
	read_reg_yet = 0;
	reg_val = 0xdeadbeef;
	curr_jiffies = tmout = jiffies + msecs_to_jiffies(1000);
	// time_before(jiffies, tmout) = time_after(tmout, jiffies) = ((jiffies - tmout) < 0)
	while( time_before(jiffies, tmout) ) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_send_command"));
#endif
		reg_val = readl(emmc_port->emmc_membase + EMMC_CMD);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_send_command"));
#endif
		read_reg_yet = 1;
		if( !(reg_val & 0x80000000UL) ) {
			istimeout = 0;
			break;
		}
	}
	curr_jiffies = jiffies;
	if( istimeout ) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_send_command"));
#endif
		reg_val = readl(emmc_port->emmc_membase + EMMC_CMD);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_send_command"));
#endif
		printk(KERN_ERR "****** tmout 0x%lx, curr_jiffies 0x%lx, jiffies 0x%lx\n", tmout, curr_jiffies, jiffies);
		printk(KERN_ERR "****** check 0x9801202c timeout!!!! (reg val 0x%08x@base_0x%p)(%d)\n", reg_val, emmc_port->emmc_membase, read_reg_yet);
		printk(KERN_ERR "****** read  0x9801202c again!!!!!! (reg val 0x%08x@base_0x%p)\n", reg_val, emmc_port->emmc_membase);
	}

	istimeout = 1;
	read_reg_yet = 0;
	reg_val = 0xbeefdead;
	curr_jiffies = tmout = jiffies + msecs_to_jiffies(1000);
	while(time_before(jiffies, tmout)) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_send_command"));
#endif
		reg_val = readl(emmc_port->emmc_membase + EMMC_STATUS);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_send_command"));
#endif
		read_reg_yet = 1;
		if( !(reg_val & 0x000006f0UL) ) {
			istimeout = 0;
			break;
		}
	}
	curr_jiffies = jiffies;
	if( istimeout ) {
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_lock2(flags2, _at_("rtkemmc_send_command"));
#endif
		reg_val = readl(emmc_port->emmc_membase + EMMC_STATUS);
#ifdef CONFIG_ARCH_RTD129x
		rtk_lockapi_unlock2(flags2, _at_("rtkemmc_send_command"));
#endif
		printk(KERN_ERR "****** tmout 0x%lx, curr_jiffies 0x%lx, jiffies 0x%lx\n", tmout, curr_jiffies, jiffies);
		printk(KERN_ERR "****** check 0x98012048 timeout!!!! (reg val 0x%08x@base_0x%p)(%d)\n", reg_val, emmc_port->emmc_membase, read_reg_yet);
		printk(KERN_ERR "****** read  0x98012048 again!!!!!! (reg val 0x%08x@base_0x%p)\n", reg_val, emmc_port->emmc_membase);
	}
#endif // FORCE_CHECK_CMD_AND_STS
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
#ifdef USE_TMP_BUF
	unsigned char *tmp_buf=NULL;
#endif
	MMCPRINTF("%s \n", __func__);
	emmc_port = mmc_priv(host);
	BUG_ON(emmc_port->mrq != NULL);

	down_write(&cr_rw_sem);
	cmd = mrq->cmd;
	emmc_port->mrq = mrq;

	if (!(emmc_port->rtflags & RTKCR_FCARD_DETECTED)){
		cmd->error = -MMC_BLK_NOMEDIUM;
		cmd->retries = 0;
		goto done;
	}
	/*
	* the "tmp_buf" should used be for sg_init_one() in blksz small than 512 byte case.
	* because RTK DMA HW issue,the samllest DMA size is 512 byte
	*/
#ifdef USE_TMP_BUF
	if (cmd->data) {
		if(cmd->data->blksz < 512){
			WARN_ON(1);
			printk("blksz=%d\n",cmd->data->blksz);
			tmp_buf = dma_alloc_coherent(emmc_port->dev, 512, &emmc_port->tmp_buf_phy_addr, GFP_KERNEL);

			if(!tmp_buf){
				WARN_ON(1);
				cmd->error = -ENOMEM;
				goto done;
			}
			memset(tmp_buf,0,512);
			emmc_port->tmp_buf = tmp_buf;
		}else
			emmc_port->tmp_buf = NULL;
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
	if(cmd_resend==1) {
		cmd_resend=0;
		down_speed_handling(emmc_port);
	}
}

static ssize_t emmc_info_dev_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct mmc_host * host = dev_get_drvdata(dev);
	struct rtkemmc_host *emmc_port = mmc_priv(host);

	printk(KERN_INFO "%s(%u)\n",__func__,__LINE__);
#if defined(CONFIG_ARCH_RTD129x)
	return sprintf(buf, "EMMC_STATUS=0x%08x SYS_PLL_EMMC1=0x%08x SYS_PLL_EMMC2=0x%08x \nSYS_PLL_EMMC3=0x%08x SYS_PLL_EMMC4=0x%08x EMMC_RINTSTS=0x%08x\nEMMC_IDSTS=0x%08x muxpad0=0x%08x muxpad1=0x%08x \nEMMC_PFUNC_NF1=0x%08x EMMC_PDRIVE_NF1=0x%08x EMMC_PDRIVE_NF2=0x%08x \nEMMC_PDRIVE_NF3=0x%08x EMMC_CTYPE=0x%08x EMMC_UHSREG=0x%08x \n EMMC_DDR_REG=0x%08x EMMC_CARD_THR_CTL=0x%08x EMMC_CLKDIV=0x%08x\nEMMC_CKGEN_CTL=0x%08x EMMC_DQS_CTRL1=0x%08x \n",
				readl(emmc_port->emmc_membase+EMMC_STATUS),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC4),
				readl(emmc_port->emmc_membase+EMMC_RINTSTS),
				readl(emmc_port->emmc_membase+EMMC_IDSTS),
				readl(emmc_port->emmc_membase+EMMC_muxpad0),
				readl(emmc_port->emmc_membase+EMMC_muxpad1),
				readl(emmc_port->emmc_membase+EMMC_PFUNC_NF1),
				readl(emmc_port->emmc_membase+EMMC_PDRIVE_NF1),
				readl(emmc_port->emmc_membase+EMMC_PDRIVE_NF2),
				readl(emmc_port->emmc_membase+EMMC_PDRIVE_NF3),
				readl(emmc_port->emmc_membase+EMMC_CTYPE),
				readl(emmc_port->emmc_membase+EMMC_UHSREG),
				readl(emmc_port->emmc_membase+EMMC_DDR_REG),
				readl(emmc_port->emmc_membase+EMMC_CARD_THR_CTL),
				readl(emmc_port->emmc_membase+EMMC_CLKDIV),
				readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL),
				readl(emmc_port->emmc_membase+EMMC_DQS_CTRL1));
#elif defined(CONFIG_ARCH_RTD139x)
	return sprintf(buf, "EMMC_STATUS=0x%08x SYS_PLL_EMMC1=0x%08x SYS_PLL_EMMC2=0x%08x \nSYS_PLL_EMMC3=0x%08x SYS_PLL_EMMC4=0x%08x EMMC_RINTSTS=0x%08x\nEMMC_IDSTS=0x%08x muxpad4=0x%08x\nPfunc_emmc0=0x%08x Pfunc_emmc1=0x%08x Pfunc_emmc2=0x%08x \nPfunc_emmc3=0x%08x Pfunc_emmc4=0x%08x Pfunc_emmc5=0x%08x EMMC_CTYPE=0x%08x EMMC_UHSREG=0x%08x \n EMMC_DDR_REG=0x%08x EMMC_CARD_THR_CTL=0x%08x EMMC_CLKDIV=0x%08x\nEMMC_CKGEN_CTL=0x%08x EMMC_DQS_CTRL1=0x%08x \n",
                                readl(emmc_port->emmc_membase+EMMC_STATUS),
                                readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
                                readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
                                readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
                                readl(emmc_port->crt_membase + SYS_PLL_EMMC4),
                                readl(emmc_port->emmc_membase+EMMC_RINTSTS),
                                readl(emmc_port->emmc_membase+EMMC_IDSTS),
                                readl(emmc_port->iso_muxpad+ISO_muxpad4),
				readl(emmc_port->iso_muxpad + pfunc_emmc0),
				readl(emmc_port->iso_muxpad + pfunc_emmc1),
				readl(emmc_port->iso_muxpad + pfunc_emmc2),
				readl(emmc_port->iso_muxpad + pfunc_emmc3),
				readl(emmc_port->iso_muxpad + pfunc_emmc4),
				readl(emmc_port->iso_muxpad + pfunc_emmc5),
                                readl(emmc_port->emmc_membase+EMMC_CTYPE),
                                readl(emmc_port->emmc_membase+EMMC_UHSREG),
                                readl(emmc_port->emmc_membase+EMMC_DDR_REG),
                                readl(emmc_port->emmc_membase+EMMC_CARD_THR_CTL),
                                readl(emmc_port->emmc_membase+EMMC_CLKDIV),
                                readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL),
                                readl(emmc_port->emmc_membase+EMMC_DQS_CTRL1));
#elif defined(CONFIG_ARCH_RTD16xx)
	return sprintf(buf, "EMMC_STATUS=0x%08x SYS_PLL_EMMC1=0x%08x SYS_PLL_EMMC2=0x%08x \nSYS_PLL_EMMC3=0x%08x SYS_PLL_EMMC4=0x%08x EMMC_RINTSTS=0x%08x\nEMMC_IDSTS=0x%08x m2tmx_muxpad0=0x%08x\nm2tmx_pfunc4=0x%08x m2tmx_pfunc5=0x%08x m2tmx_pfunc6=0x%08x \nm2tmx_pfunc7=0x%08x m2tmx_pfunc8=0x%08x EMMC_CTYPE=0x%08x EMMC_UHSREG=0x%08x \n EMMC_DDR_REG=0x%08x EMMC_CARD_THR_CTL=0x%08x EMMC_CLKDIV=0x%08x\nEMMC_CKGEN_CTL=0x%08x EMMC_DQS_CTRL1=0x%08x \n",
				readl(emmc_port->emmc_membase+EMMC_STATUS),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC1),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC2),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC3),
				readl(emmc_port->crt_membase + SYS_PLL_EMMC4),
				readl(emmc_port->emmc_membase+EMMC_RINTSTS),
				readl(emmc_port->emmc_membase+EMMC_IDSTS),
				readl(emmc_port->m2tmx + m2tmx_muxpad0),
				readl(emmc_port->m2tmx + m2tmx_pfunc4),
				readl(emmc_port->m2tmx + m2tmx_pfunc5),
				readl(emmc_port->m2tmx + m2tmx_pfunc6),
				readl(emmc_port->m2tmx + m2tmx_pfunc7),
				readl(emmc_port->m2tmx + m2tmx_pfunc8),
				readl(emmc_port->emmc_membase+EMMC_CTYPE),
				readl(emmc_port->emmc_membase+EMMC_UHSREG),
				readl(emmc_port->emmc_membase+EMMC_DDR_REG),
				readl(emmc_port->emmc_membase+EMMC_CARD_THR_CTL),
				readl(emmc_port->emmc_membase+EMMC_CLKDIV),
				readl(emmc_port->emmc_membase+EMMC_CKGEN_CTL),
				readl(emmc_port->emmc_membase+EMMC_DQS_CTRL1));
#endif
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
#ifdef CONFIG_ARCH_RTD129x
	unsigned long flags2;
#endif
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

#if defined(EMMC_LA_DEBUG_GPIO) || defined(EMMC_PARAM_TEST)
	emmc_port->misc_membase = of_iomap(emmc_node, 3);
#endif

#ifdef DBG_PORT
	emmc_port->sb2_debug_membase = of_iomap(emmc_node, 4);
	//rtk_lockapi_lock2(flags2, _at_("rtkemmc_probe"));
        rtkemmc_writel(0x5, emmc_port->emmc_membase + EMMC_MAIN2_DBG);
        rtkemmc_writel(0x7208,emmc_port->sb2_debug_membase);
        rtkemmc_writel(0x2db7, emmc_port->emmc_membase + EMMC_DBG);
	//rtk_lockapi_unlock2(flags2, _at_("rtkemmc_probe"));
        isb();
        sync(emmc_port);
#endif

#if defined(CONFIG_ARCH_RTD139x)
	emmc_port->iso_muxpad = of_iomap(emmc_node, 5);
#elif defined(CONFIG_ARCH_RTD16xx)
	emmc_port->m2tmx = of_iomap(emmc_node, 5);
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

	rstc_emmc = devm_reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(rstc_emmc)) {
		printk(KERN_WARNING "%s: reset_control_get() returns %ld\n", __func__,
			PTR_ERR(rstc_emmc));
		rstc_emmc = NULL;
	}
	clk_en_emmc = devm_clk_get(&pdev->dev, "clk_en_emmc");
	if (IS_ERR(clk_en_emmc)) {
		printk(KERN_WARNING "%s: clk_get() returns %ld\n", __func__,
			PTR_ERR(clk_en_emmc));
		clk_en_emmc = NULL;
	}
	clk_en_emmc_ip = devm_clk_get(&pdev->dev, "clk_en_emmc_ip");
	if (IS_ERR(clk_en_emmc_ip)) {
		printk(KERN_WARNING "%s: clk_get() returns %ld\n", __func__,
			PTR_ERR(clk_en_emmc_ip));
		clk_en_emmc_ip = NULL;
	}
#ifdef CONFIG_ARCH_RTD129x
	//1295 uses the same DMA bus bwtween SD, SDIO, and EMMC, we still need to open this clk if no SD card and SDIO driver, 1395 will separare the DMA bus
	clk_cr = devm_clk_get(&pdev->dev, "clk_en_cr");
	if (IS_ERR(clk_cr)) {
		printk(KERN_WARNING "%s: clk_get() returns %ld\n", __func__,
			PTR_ERR(clk_cr));
		clk_cr = NULL;
	}
#endif
	clk_prepare_enable(clk_en_emmc);
	clk_prepare_enable(clk_en_emmc_ip);
#ifdef CONFIG_ARCH_RTD129x
	clk_prepare_enable(clk_cr);
#endif

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
#if defined(CONFIG_ARCH_RTD139x) || defined(CONFIG_ARCH_RTD16xx)
		| MMC_CAP_1_8V_DDR
		| MMC_CAP_UHS_DDR50
#endif
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

	mmc->caps2 |= MMC_CAP2_HC_ERASE_SZ;
	mmc->f_min = 300000;        //300K
	mmc->f_max = 400000000; //400M
#ifdef CONFIG_RTK_XEN_SUPPORT
	mmc->max_segs = 1;
#else
	mmc->max_segs = 256;
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

#ifdef ENABLE_EMMC_INT_MODE
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_lock2(flags2, _at_("rtkemmc_probe"));
#endif
	rtkemmc_hold_int_dec();       /* hold status interrupt */
	rtkemmc_clr_int_sta();
#ifdef CONFIG_ARCH_RTD129x
	rtk_lockapi_unlock2(flags2, _at_("rtkemmc_probe"));
#endif
	ret = request_irq(irq, rtkemmc_irq, IRQF_SHARED, DRIVER_NAME, emmc_port);   //rtkemmc_interrupt
	if (ret) {
		printk(KERN_ERR "%s: cannot assign irq %d\n", DRIVER_NAME, irq);
		goto out;
	} else
		emmc_port->irq = irq;

	setup_timer(&emmc_port->timer, rtkemmc_timeout_timer, (unsigned long)emmc_port);
#endif
	emmc_port->ops->set_crt_muxpad(emmc_port);
	
	if (emmc_port->ops->reset_card)
		emmc_port->ops->reset_card(emmc_port);

	emmc_port->ops->chk_card_insert(emmc_port);

	platform_set_drvdata(pdev, mmc);
	
	ret = mmc_add_host(mmc);
	if (ret)
		goto out;

	sync(emmc_port);
	memset((struct backupRegs*)&gRegTbl, 0x00, sizeof(struct backupRegs));
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
#if defined(EMMC_LA_DEBUG_GPIO) || defined(EMMC_PARAM_TEST)
		iounmap(emmc_port->misc_membase);
#endif
#ifdef DBG_PORT
		iounmap(emmc_port->sb2_debug_membase);
#endif
		release_resource(emmc_port->res);
		mmc_free_host(mmc);
	}
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static const struct of_device_id rtkemmc_ids[] = {
        { .compatible = "Realtek,rtk1295-emmc" },
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
