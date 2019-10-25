/*
 * rtk_nand.c - nand driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/pm.h>
#include <asm/io.h>
#include <linux/init.h>
#include <linux/mtd/rtk_nand_reg.h>
#include <linux/mtd/rtk_nand.h>
#include <linux/bitops.h>
#include <mtd/mtd-abi.h>
#include <linux/jiffies.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/of.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/clk.h>
#include <linux/reset.h>
#include "../mtdcore.h"

#define BANNER			"Realtek NAND Flash Driver"
#define VERSION			"$Id: rtk_nand.c 2018-10-29 01:32:27Z aaron.lin $"
#define MTDSIZE			(sizeof (struct mtd_info) + sizeof (struct nand_chip))

#define RTKNAND_PROC_DIR_NAME           "rtknand"
#define RTKNAND_PROC_INFO_DIR_NAME      "rtknand/info"
#define RTKNAND_PROC_TEST_DIR_NAME	"rtknand/test"

extern struct proc_dir_entry proc_root;
static struct proc_dir_entry *rtknand_proc_dir = NULL;
#ifdef RTK_VERIFY
unsigned int r_test_flag = 0;
unsigned int w_test_flag = 0;
unsigned int w_wait_flag = 0;
unsigned int nomap_blk = 0;
#endif
static int g_id_chain = 0;
extern unsigned int g_eccbits;
extern dma_addr_t oobPhys_addr;

#ifdef RTK_TEST
static struct mtd_partition rtk_partitions[] =
{
    {
        .name   = "rtk_nand",
	.size   = 0x10000000,
	.offset = 0x0
    },
#if 0
    {
        .name   = "dtb",
        //.size   = 0x400000,
        .size   = 0x40000,
        .offset = 0x2000000
    },
    {
        .name   = "kernel",
        .size   = 0x1C00000,
        .offset = 0x2000000 + 0x400000
    },
    {
        .name   = "rootfs",
        .size   = 0x2000000,
        .offset = 0x2000000 + 0x2000000
    },
#endif
    {
        .name   = "yaffs",
        .size   = 0x2000000,
        .offset = 0x8000000
    },
    {
        .name   = "ubifs",
        .size   = 0x2000000,
        .offset = 0x8000000 + 4000000
    }
};
#endif

char g_rtk_nandinfo_line[64];

void __iomem    *map_base = 0;
void __iomem    *swc_base = 0;

const char *ptypes[] = {"cmdlinepart", NULL};

/* nand driver low-level functions */
//static int rtk_read_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *buf);
static int rtk_read_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			u_char *data, u_char *oob_buf, u16 cp_mode, dma_addr_t *data_phy);
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *buf);
static int rtk_write_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page, const u_char *data, const u_char *oob_buf, const dma_addr_t *data_phy);
static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page);
void rtk_nand_reset(void);
/* Global Variables */
struct mtd_info *rtk_mtd;

static int page_size, oob_size, ppb;
static int RBA_PERCENT = 5;

static struct rw_semaphore rw_sem;

struct rtk_nand_host {
	struct mtd_info		mtd;
	struct nand_chip	nand;
	struct mtd_partition	*parts;
	struct device		*dev;
	void    *spare0;
	void    *main_area0;
	void    *main_area1;
	void __iomem    *base;
	void __iomem    *regs;
	int	    status_request;
	struct clk  *clk;
	int	clk_act;
	int	irq;
	wait_queue_head_t	irq_waitq;
	uint8_t		*data_buf;
	unsigned int    buf_start;
	int		spare_len;
};

void syncPageRead(void)
{
	dmb(sy);
	dmb(sy);
}

int WAIT_DONE(void *addr, u64 mask, unsigned int value)
{
	unsigned int test = 0x0;

#ifdef RTK_VERIFY
	if(w_wait_flag == 1) {
		w_wait_flag = 0;
		printk(KERN_ERR "WAIT_DONE timeout, do nand reset.\n");
		return -WAIT_TIMEOUT;
	}
#endif

        while ( (REG_READ_U32((volatile unsigned int*)addr) & mask) != value ) {
                asm("nop");
                smp_wmb();
		test++;

		if (test == 0xFFFFFFFF) {
			printk(KERN_ERR "WAIT_DONE timeout, do nand reset.\n");
			return -WAIT_TIMEOUT;	
		}
        }
	
	return 0;
}

void rtk_nand_reset(void)
{
	int rc;

        //down_write(&rw_sem);

        // controller init.
        REG_WRITE_U32(REG_PD + map_base, 0x1E);
        REG_WRITE_U32(REG_TIME_PARA3 + map_base, 0x2);
        REG_WRITE_U32(REG_TIME_PARA2 + map_base, 0x5);
        REG_WRITE_U32(REG_TIME_PARA1 + map_base, 0x2);

        REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base, 0x0);
        REG_WRITE_U32(REG_READ_BY_PP+map_base, 0x0);

        // reset nand.
        REG_WRITE_U32(REG_ND_CMD+map_base, CMD_RESET);
        REG_WRITE_U32(REG_ND_CTL+map_base, 0x80);
        rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
        rc = WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);

        REG_WRITE_U32(REG_NF_LOW_PWR+map_base, REG_READ_U32(REG_NF_LOW_PWR+map_base)&~0x10);
        REG_WRITE_U32(REG_SPR_DDR_CTL+map_base, NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0));

	//up_write(&rw_sem);
}
EXPORT_SYMBOL(rtk_nand_reset);

static int rtk_nand_suspend (struct device *dev)
{
        struct clk *clk = clk_get(dev, NULL);

        clk_disable_unprepare(clk);

	return 0;
}

static int rtk_nand_resume (struct device *dev)
{
        struct clk *clk = clk_get(dev, NULL);
	int rc;

	clk_prepare_enable(clk);

        // controller init.
        REG_WRITE_U32(REG_PD + map_base, 0x1E);
        REG_WRITE_U32(REG_TIME_PARA3 + map_base, 0x2);
        REG_WRITE_U32(REG_TIME_PARA2 + map_base, 0x5);
        REG_WRITE_U32(REG_TIME_PARA1 + map_base, 0x2);

        REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base, 0x0);
        REG_WRITE_U32(REG_READ_BY_PP+map_base, 0x0);

        // reset nand.
        REG_WRITE_U32(REG_ND_CMD+map_base, 0xff);
        REG_WRITE_U32(REG_ND_CTL+map_base, 0x80);

        rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
        rc = WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);

        REG_WRITE_U32(REG_NF_LOW_PWR+map_base, REG_READ_U32(REG_NF_LOW_PWR+map_base)&~0x10);

        REG_WRITE_U32(REG_SPR_DDR_CTL+map_base, NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0));

	return 0;
}

static void rtk_read_oob_from_SRAM(struct mtd_info *mtd, __u8 *oobbuf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
        unsigned int reg_oob;
        void __iomem *reg = NULL;
        int i;
	char r_oobbuf[256];
	int oobuse_size;

        REG_WRITE_U32(REG_READ_BY_PP+map_base,0x00);
        REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x30 | 0x04);

	memset(r_oobbuf, 0xFF, 256);
	memset(oobbuf, 0xFF, mtd->oobsize);

        reg = ioremap(0x98010000, 0x100);

	switch(this->ecc_select) {
                case 0x0:
                        oobuse_size = 6 + 10;
                        break;
                case 0x1:
                        oobuse_size = 6 + 20;
                        break;
                default:
                        oobuse_size = 6 + 10;
                        break;
        }

        for(i = 0; i<(mtd->oobsize/4); i++) {
                reg_oob = REG_READ_U32(reg+(i*4));

                r_oobbuf[i*4] = reg_oob & 0xff;
                r_oobbuf[(i*4)+1] = (reg_oob >> 8) & 0xff;
                r_oobbuf[(i*4)+2] = (reg_oob >> 16) & 0xff;
                r_oobbuf[(i*4)+3] = (reg_oob >> 24) & 0xff;
        }

	for(i = 0; i < 4; i++) {
		memcpy(oobbuf+(i*oobuse_size), r_oobbuf+(i*(mtd->oobsize/4)), oobuse_size);
	}

        REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x00);
        REG_WRITE_U32(REG_READ_BY_PP+map_base,0x80);

	return;
}

static void rtk_nand_read_id(struct mtd_info *mtd, u_char id[6])
{
	int id_chain;
	int rc;

	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0x06));
	REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(0x01));

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0x0));

	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_READ_ID));
	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(0x01));
	rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);

	//Set address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0);
	REG_WRITE_U32(REG_ND_PA1+map_base, 0);
	REG_WRITE_U32(REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x07));

	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(1));
	rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	//Enable XFER mode
	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(4));
	rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_reset(1));

	//Move data to DRAM from SRAM
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(1)|NF_SRAM_CTL_mem_region(0));

	id_chain = REG_READ_U32(REG_ND_PA0+map_base);
        g_id_chain = id_chain;
	NF_DEBUG_PRINT("id_chain 1 = 0x%x \n", id_chain);
	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;

	id_chain = REG_READ_U32(REG_ND_PA1+map_base);
	NF_DEBUG_PRINT("id_chain 2 = 0x%x \n", id_chain);
	id[4] = id_chain & 0xff;
	id[5] = (id_chain >> 8) & 0xff;

	REG_WRITE_U32(REG_SRAM_CTL+map_base,0x0);	//# no omitted
}

static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page)
{
	struct nand_chip *this = NULL;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;
	this = (struct nand_chip *) mtd->priv;

	down_write(&rw_sem);

	if ( page & (ppb-1) ){
		NF_ERR_PRINT("%s: page %d is not block alignment !!\n", __FUNCTION__, page);
		up_write(&rw_sem);
		return -1;
	}

	REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_no_wait_busy(1)|NF_MULTI_CHNL_MODE_edo(1));


	REG_WRITE_U32( REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_BLK_ERASE_C1) );
	REG_WRITE_U32( REG_CMD2+map_base,NF_CMD2_cmd2(CMD_BLK_ERASE_C2) );
	REG_WRITE_U32( REG_CMD3+map_base,NF_CMD3_cmd3(CMD_BLK_ERASE_C3) );

	REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x04)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>> 21)&0x7) );

	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)|NF_AUTO_TRIG_auto_case(2) );
	if(WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
		up_write(&rw_sem);
		return -WAIT_TIMEOUT;
	}

	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	if(WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
		up_write(&rw_sem);
		return -WAIT_TIMEOUT;
	}
	if(WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
		up_write(&rw_sem);
		return -WAIT_TIMEOUT;
	}

	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ){
		up_write(&rw_sem);
		NF_ERR_PRINT("[%s] erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
		return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
#if 0
	if(this->erase_page_flag)
		memset ( (__u32 *)(this->erase_page_flag)+ chip_section + section, 0xff, ppb>>3);
#endif
	up_write(&rw_sem);
	
	return 0;
}

static int rtk_read_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf, u16 cp_mode, dma_addr_t *data_phy)
{
	struct nand_chip *this = NULL;
	int dram_sa, dma_len;
	int page_len;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	uint8_t	bChkAllOne = 0;
    	volatile unsigned int data;
    	unsigned int eccNum = 0;

	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;

	syncPageRead();

	down_write(&rw_sem);

	if(((uintptr_t)data_buf&0x7)!=0) {
		NF_DEBUG_PRINT("[%s]data_buf must 8 byte alignmemt!!\n", __FUNCTION__);
		BUG();
	}

	while (1) 
	{
		if(this->ecc_select >= 0x18)
		{
			if (bChkAllOne) {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 0);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(1));
			}
			else {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 1);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			}
			
			page_len = page_size >> 10;
			REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(1024));
			REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
		}
		else
		{
			// set random read
			REG_WRITE_U32(REG_RND_EN+map_base, 1);
			REG_WRITE_U32(REG_RND_CMD1+map_base, 0x5);
			REG_WRITE_U32(REG_RND_CMD2+map_base, 0xe0);
			REG_WRITE_U32(REG_RND_DATA_STR_COL_H+map_base, 0);	// data start address MSB (always 0)
			REG_WRITE_U32(REG_RND_SPR_STR_COL_H+map_base, page_size >> 8);	// spare start address MSB
			REG_WRITE_U32(REG_RND_SPR_STR_COL_L+map_base, page_size & 0xff);	// spare start address LSB
			
			page_len = page_size >> 9;
			REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(512));
			REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		REG_WRITE_U32(REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

		//Set PP
		REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0+map_base,0);

		// enable blank check
		REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1) );

		if(cp_mode == CP_NF_AES_ECB_128 || cp_mode==CP_NF_AES_CBC_128) {
			REG_WRITE_U32(CP_NF_INI_KEY_0+map_base,0x0);
			REG_WRITE_U32(CP_NF_INI_KEY_1+map_base,0x0);
			REG_WRITE_U32(CP_NF_INI_KEY_2+map_base,0x0);
			REG_WRITE_U32(CP_NF_INI_KEY_3+map_base,0x0);

			REG_WRITE_U32(CP_NF_KEY_0+map_base,0x8746bca3);
			REG_WRITE_U32(CP_NF_KEY_1+map_base,0xcdef89ab);
			REG_WRITE_U32(CP_NF_KEY_2+map_base,0x54369923);
			REG_WRITE_U32(CP_NF_KEY_3+map_base,0xcdefbcab);

			// set CP register.
			if(cp_mode == CP_NF_AES_ECB_128)
				REG_WRITE_U32(CP_NF_SET+map_base, 0x200);	// sel=0, cw_entry=0, bcm=1, aes_mode=0. Its ECB mode.
			else
				REG_WRITE_U32(CP_NF_SET+map_base, 0x0);		// sel=0, cw_entry=0, bcm=0, aes_mode=0. Its CBC mode.

			REG_WRITE_U32(REG_CP_LEN+map_base, (page_size / 0x200) << 9);	// integer multiple of dma_len.

		}

		//Set command
		REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_READ_C1));
		REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_READ_C2));
		REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_READ_C3));
		
		//Set address
		REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0( 0xff&page ));
        
		REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1( 0xff&(page>>8) ));
		REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2( 0x1f&(page>>16) ));
		REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3( 0x7&(page>>21) ));

		REG_WRITE_U32(REG_ND_CA0+map_base, 0);
		REG_WRITE_U32(REG_ND_CA1+map_base, 0);

		//Set ECC
		REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
		REG_WRITE_U32( REG_ECC_STOP+map_base,NF_ECC_STOP_ecc_n_stop(0x01));

		REG_WRITE_U32(REG_ECC_SEL+map_base, this->ecc_select);

		dram_sa = ( (uintptr_t)data_phy >> 3);
		REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));

		if(cp_mode == CP_NF_AES_ECB_128||cp_mode==CP_NF_AES_CBC_128){
			REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(1)|NF_DMA_CTL3_cp_first(1)|NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
		}else{
			REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
		}

		smp_wmb();
	
		syncPageRead();

		//Enable Auto mode
		REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

		if(WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0)) {
			NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
			up_write(&rw_sem);
			return -WAIT_TIMEOUT;
		}

		if(WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0)) {
			NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
                        up_write(&rw_sem);
                        return -WAIT_TIMEOUT;
		}

		if(1) {
			data = (REG_READ_U32(REG_SPR_DDR_CTL+map_base) & 0x1fffffff) << 3;	// physical address
			NF_DEBUG_PRINT("data==> 0x%x\n",data);
			NF_DEBUG_PRINT("oob_buf[0]==> 0x%x, page=0x%x\n",this->g_oobbuf[0],page);    
		}

		if(oob_buf) {
			rtk_read_oob_from_SRAM(mtd, oob_buf);
		}

		// return OK if all data bit is 1 (page is not written yet)
		if ((REG_READ_U32(REG_BLANK_CHK+map_base) & 0x8)==0){
			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return 1;
		}
		else if (REG_READ_U32(REG_ND_ECC+map_base) & 0x8) {
			NF_DEBUG_PRINT("[DBG][%s] page(0x%x) ecc error,  REG_BLANK_CHK reg: 0x%x\n", __FUNCTION__, page, REG_READ_U32(REG_BLANK_CHK+map_base));
			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return -1;	// ECC not correctable
		}
		else {
            		//NF_DEBUG_PRINT("PK test page:%u  [0x%x]\n", page, REG_READ_U32(REG_ND_ECC+map_base));
            		if (REG_READ_U32(REG_ND_ECC+map_base) & 0x04){
                		eccNum = REG_READ_U32(REG_RSECC_NUM+map_base) & 0xff;
                		NF_DEBUG_PRINT("[NAND_DBG][%s]:%d, ecc_num:%d, page:%u\n", __FUNCTION__,__LINE__, eccNum, page);
                		if(eccNum > (g_eccbits - 2) ) {
                    			NF_ERR_PRINT("[NAND_DBG][%s]:%d, ecc_num:%d, page:%u\n", __FUNCTION__,__LINE__, eccNum, page);
                    			REG_WRITE_U32(REG_BLANK_CHK+map_base, NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
                    			up_write(&rw_sem);
                    			return -2;
                		}
            		}

			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return 0;
		}
	}
}

static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *oob_buf)
{
        struct nand_chip *this = (struct nand_chip *) mtd->priv;
        int rc = 0;
        uint8_t auto_trigger_mode = 1;
        uint8_t addr_mode = 1;
        unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
        unsigned char oob_1stB;
        unsigned int chip_section = 0;
        unsigned int section =0;
        unsigned int index =0;

        memset(this->g_databuf, 0xff, page_size);

        page_size = mtd->writesize;
        oob_size = mtd->oobsize;
        ppb = mtd->erasesize/mtd->writesize;

        down_write(&rw_sem);

	if ( len > oob_size || !oob_buf ){
		NF_ERR_PRINT("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
                up_write(&rw_sem);
                return -1;
        }
	
	REG_WRITE_U32(REG_SRAM_CTL+map_base,0x00);
        REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));
        if(this->ecc_select >= 0x18) {
                page_len = page_size >> 10;
                REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(4));
        } else {
                page_len = page_size >> 9;
                REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(2));
        }

	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0));
        REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));
        REG_WRITE_U32(REG_PP_CTL0+map_base,0);

        REG_WRITE_U32( REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

        REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
        REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
        REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

        REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page));
        REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8));
        REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
        REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>>21)&0x7));
        REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));

        REG_WRITE_U32(REG_ECC_SEL+map_base, this->ecc_select);

	dram_sa = ((uintptr_t)this->g_databuf >> 3);
        REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
        dma_len = page_size >> 9;
        REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));
        REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));

        spare_dram_sa = ((uintptr_t)oob_buf >> 3);
        REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
        WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
        REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
        WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0);
        WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);

	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ) {
		NF_ERR_PRINT("[%s] write oob is not completed at page %d\n", __FUNCTION__, page);
                up_write(&rw_sem);
                return -1;
        }

	printk(KERN_ERR "[%s] write oob OK at page %d\n", __FUNCTION__, page);

        up_write(&rw_sem);

        return rc;
}

static int rtk_write_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page, const u_char *data_buf, const  u_char *oob_buf, const dma_addr_t *data_phy)
{	
	//unsigned int ppb = mtd->erasesize/mtd->writesize;
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;
	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	//unsigned char oob_1stB,oob_2ndB=0;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;

        syncPageRead();

	down_write(&rw_sem);

        if(((uintptr_t)data_buf&0x7)!=0)
        {
                NF_ERR_PRINT("[%s]data_buf must 8 byte alignmemt!!\n",__FUNCTION__);
                BUG();
        }

        if(((uintptr_t)oob_buf&0x7)!=0)
        {
                NF_ERR_PRINT("[%s]oob_buf must 8 byte alignmemt!!\n",__FUNCTION__);
                BUG();
        }

#if 0
	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG >> 8;
	else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Factory_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;
	else
		oob_1stB = 0xFF;

	if (oob_buf) {
		if ((*(unsigned char*)(((unsigned char*)oob_buf)+2) == 0xbe) && (*(unsigned char*)(((unsigned char*)oob_buf)+3) == 0xef)) {
			oob_1stB = *(unsigned char*)(((unsigned char*)oob_buf)+0);
			oob_2ndB = *(unsigned char*)(((unsigned char*)oob_buf)+1);
		}
	}

	this->g_oobbuf[0x0] = oob_1stB;
	this->g_oobbuf[0x10] = oob_1stB;
	this->g_oobbuf[0x20] = oob_1stB;
	this->g_oobbuf[0x30] = oob_1stB;

    	this->g_oobbuf[0x8] = oob_1stB;
	this->g_oobbuf[0x18] = oob_1stB;
	this->g_oobbuf[0x28] = oob_1stB;
	this->g_oobbuf[0x38] = oob_1stB;

	if(oob_size > 0x40){       //MLC oob size > 64 bytes
		this->g_oobbuf[0x40] = oob_1stB;
		this->g_oobbuf[0x50] = oob_1stB;
		this->g_oobbuf[0x60] = oob_1stB;
		this->g_oobbuf[0x70] = oob_1stB;

		this->g_oobbuf[0x48] = oob_1stB;
		this->g_oobbuf[0x58] = oob_1stB;
		this->g_oobbuf[0x68] = oob_1stB;
		this->g_oobbuf[0x78] = oob_1stB;
	}

	if (oob_buf) {
		if ((*(unsigned char*)(((unsigned char*)oob_buf)+2) == 0xbe) && (*(unsigned char*)(((unsigned char*)oob_buf)+3) == 0xef)) {  
			this->g_oobbuf[0x1] = oob_2ndB;
			this->g_oobbuf[0x11] = oob_2ndB;
			this->g_oobbuf[0x21] = oob_2ndB;
			this->g_oobbuf[0x31] = oob_2ndB;
		}
	}
#endif

	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));
 	if(this->ecc_select >= 0x18)
	{
		// enable randomizer
		REG_WRITE_U32(REG_RMZ_CTRL+map_base, 1);
                REG_WRITE_U32(REG_RMZ_SEED_H+map_base, ((page+1) & 0xff00)>>8);
                REG_WRITE_U32(REG_RMZ_SEED_L+map_base, (page+1) & 0xff);
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(4));
	}
	else
	{
		// set random write
		REG_WRITE_U32(REG_RND_EN+map_base, 1);
		REG_WRITE_U32(REG_RND_CMD1+map_base, 0x85);
		REG_WRITE_U32(REG_RND_DATA_STR_COL_H+map_base, 0);	// data start address MSB (always 0)
		REG_WRITE_U32(REG_RND_SPR_STR_COL_H+map_base, page_size >> 8);	// spare start address MSB
		REG_WRITE_U32(REG_RND_SPR_STR_COL_L+map_base, page_size & 0xff);	// spare start address LSB
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32( REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0+map_base,0);//add by alexchang 0208-2010

	//Set command
 	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	//Set address
	REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_ND_CA0+map_base, 0);
	REG_WRITE_U32(REG_ND_CA1+map_base, 0);

	//Set ECC
	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP+map_base,NF_ECC_STOP_ecc_n_stop(0x01));

	REG_WRITE_U32(REG_ECC_SEL+map_base, this->ecc_select);

	dram_sa = ( (uintptr_t)data_phy >> 3);
	REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));

	spare_dram_sa = ( (uintptr_t)oobPhys_addr >> 3);
	REG_WRITE_U32(REG_SPR_DDR_CTL+map_base,0x60000000|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(1));
    
	syncPageRead();

	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
	smp_wmb();

	if(WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
                up_write(&rw_sem);
                return -WAIT_TIMEOUT;
	}
	if(WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
                up_write(&rw_sem);
                return -WAIT_TIMEOUT;
	}
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	if(WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0)) {
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
                up_write(&rw_sem);
                return -WAIT_TIMEOUT;
	}
	if(WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40)) {//add by alexchang 0416-2010
		NF_ERR_PRINT("[%s] WAIT_DONE timeout. (%d)\n", __FUNCTION__, __LINE__);
                up_write(&rw_sem);
                return -WAIT_TIMEOUT;
	}

	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ){
		up_write(&rw_sem);
		NF_ERR_PRINT("[%s] write is not completed at page %d\n", __FUNCTION__, page);
		return -1;
	}
#if 0	
	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);

	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
#endif
	up_write(&rw_sem);
	
	return rc;
}

static int rtk_mtd_add_partitions(struct mtd_info *mtd, struct mtd_partitions *parts)
{
        const struct mtd_partition *real_parts = parts->parts;
        int nbparts = parts->nr_parts;
        int ret;

	NF_DEBUG_PRINT("%s, nbparts:[%d]\n", __FUNCTION__, nbparts);

        if (nbparts > 0) {
                ret = add_mtd_partitions(mtd, real_parts, nbparts);
		NF_DEBUG_PRINT("%s, ret:[%d]\n", __FUNCTION__, ret);
                return ret;
        }

        return 0;
}


static int rtk_nand_profile (void)
{
	int maxchips = 4;
	int pnum = 0;
	struct mtd_partitions mtd_parts;
	struct nand_chip *this = (struct nand_chip *)rtk_mtd->priv;
	int rc = 0;

	memset(&mtd_parts, 0, sizeof(mtd_parts));

	this->RBA_PERCENT = RBA_PERCENT;

	if (rtk_nand_scan (rtk_mtd, maxchips) < 0 || rtk_mtd->size == 0){
		NF_ERR_PRINT("%s: Error, cannot do nand_scan(on-board)\n", __FUNCTION__);
		return -ENODEV;
	}

	if ( !(rtk_mtd->writesize&(0x200-1)) )
		REG_WRITE_U32( REG_PAGE_LEN+map_base,rtk_mtd->writesize >> 9);
	else{
		NF_ERR_PRINT("Error: pagesize is not 512B Multiple");
		return -1;
	}
#ifdef RTK_TEST
	rc = mtd_device_register(rtk_mtd, rtk_partitions, ARRAY_SIZE(rtk_partitions));
#else

#ifdef CONFIG_MTD_CMDLINE_PARTS
	rc = parse_mtd_partitions (rtk_mtd, ptypes, &mtd_parts, 0);
	pnum = mtd_parts.nr_parts;
#else
	rc = mtd_device_parse_register(rtk_mtd, ptypes, 0, &mtd_parts, 0);
	NF_INFO_PRINT("[%s] mtd_device_parse_register rc = 0x%x\n", __FUNCTION__, rc);
#endif

    	NF_INFO_PRINT("[%s] add mtd partition. pnum:[%d]\n", __FUNCTION__, pnum);

	if (pnum <= 0) {
		NF_INFO_PRINT("RTK: using the whole nand as a partitoin\n");
		if(add_mtd_device(rtk_mtd)) {
			NF_ERR_PRINT("RTK: Failed to register new nand device\n");
			return -EAGAIN;
		}
	}else{
		NF_INFO_PRINT("RTK: using dynamic nand partition\n");
		if(rtk_mtd_add_partitions(rtk_mtd, &mtd_parts)) {
			NF_INFO_PRINT("%s: Error, cannot add %s device\n", __FUNCTION__, rtk_mtd->name);
			rtk_mtd->size = 0;
			return -EAGAIN;
		}

		mtd_part_parser_cleanup(&mtd_parts);
	}
#endif
	return 0;
}

static void display_version (void)
{
	const __u8 *revision;
	const __u8 *date;
	char *running = (__u8 *)VERSION;
	strsep(&running, " ");
	strsep(&running, " ");
	revision = strsep(&running, " ");
	date = strsep(&running, " ");
	printk(BANNER " Rev:%s (%s)\n", revision, date);
}

#define CTL_ENABLE  1
#define CTL_DISABLE 0

static int rtk_nand_clk_reset_ctrl(struct device *dev, int enable)
{
	struct reset_control *reset = reset_control_get(dev, NULL);
	struct clk *clk = clk_get(dev, NULL);

	if(enable == CTL_ENABLE){
		reset_control_deassert(reset);
        	clk_prepare_enable(clk);
    	}else{
        	clk_disable_unprepare(clk);
    	}

    	clk_put(clk);
    	reset_control_put(reset);

	return 0;
}

static void rtk_nand_gating(void)
{
	REG_WRITE_U32(0x168+map_base, REG_READ_U32(0x168+map_base) | (0x1));
	REG_WRITE_U32(0x168+map_base, REG_READ_U32(0x168+map_base) | (0x1 << 1));

	REG_WRITE_U32(0x314+map_base, REG_READ_U32(0x314+map_base) | (0x1));
	REG_WRITE_U32(0x314+map_base, REG_READ_U32(0x314+map_base) | (0x1 << 1));

	//REG_WRITE_U32(0xf168+map_base, REG_READ_U32(0xf168+map_base) | (0x1));
	//REG_WRITE_U32(0xf168+map_base, REG_READ_U32(0xf168+map_base) | (0x1 << 1));

	//REG_WRITE_U32(0xf314+map_base, REG_READ_U32(0xf314+map_base) | (0x1));
	//REG_WRITE_U32(0xf314+map_base, REG_READ_U32(0xf314+map_base) | (0x1 << 1));

	REG_WRITE_U32(0x13c+map_base, REG_READ_U32(0x13c+map_base) | (0x1 << 3));
	REG_WRITE_U32(0x13c+map_base, REG_READ_U32(0x13c+map_base) | (0x1 << 4));

	REG_WRITE_U32(0x310+map_base, REG_READ_U32(0x310+map_base) | (0x1 << 5));
	REG_WRITE_U32(0x310+map_base, REG_READ_U32(0x310+map_base) | (0x1 << 6));

	//REG_WRITE_U32(0xf13c+map_base, REG_READ_U32(0xf13c+map_base) | (0x1 << 3));
	//REG_WRITE_U32(0xf13c+map_base, REG_READ_U32(0xf13c+map_base) | (0x1 << 4));

	//REG_WRITE_U32(0xf310+map_base, REG_READ_U32(0xf310+map_base) | (0x1 << 5));
	//REG_WRITE_U32(0xf310+map_base, REG_READ_U32(0xf310+map_base) | (0x1 << 6));

	REG_WRITE_U32(0x318+map_base, REG_READ_U32(0x318+map_base) | (0x1));

}

static int rtk_read_proc_nandinfo(struct seq_file *m, void *v) 
{
	struct nand_chip *this = (struct nand_chip *) rtk_mtd->priv;
	int i;

	seq_printf(m, "nand_size:%u\n", (uint32_t)this->device_size);
	seq_printf(m, "chip_size:%u\n", (uint32_t)this->chipsize);
	seq_printf(m, "block_size:%u\n", rtk_mtd->erasesize);
	seq_printf(m, "page_size:%u\n", rtk_mtd->writesize);
	seq_printf(m, "oob_size:%u\n", rtk_mtd->oobsize);
	seq_printf(m, "ppb:%u\n", rtk_mtd->erasesize/rtk_mtd->writesize);
	seq_printf(m, "RBA:%u\n", this->RBA);
	seq_printf(m, "BBs:%u\n", this->BBs);
	seq_printf(m, "ecc bits:%u\n", g_eccbits);
	seq_printf(m, "\n");
#ifdef RTK_NAND_SHIFTABLE
        seq_printf(m, "Shift block table:\n");
	for ( i=0; i<STBCOUNT; i++){
                if ( i==0 && this->sbt[i].chipnum == SB_INIT){
                        seq_printf(m, "Congratulation!! No shift block in this Nand.\n");
                        break;
                }

                if ( this->sbt[i].block != SB_INIT ){
                        seq_printf(m, "[%d] (%d, %d, %d)\n", i, this->sbt[i].chipnum, this->sbt[i].block, this->sbt[i].shift);
                }
        }
        seq_printf(m, "\n");
#endif
        seq_printf(m, "Bad block table:\n");
	for ( i=0; i<this->RBA; i++){
                if ( i==0 && this->bbt[i].BB_die == BB_DIE_INIT && this->bbt[i].bad_block == BB_INIT ){
                        seq_printf(m, "Congratulation!! No bad block in this Nand.\n");
                        break;
                }

                if ( this->bbt[i].bad_block != BB_INIT ){
                        seq_printf(m, "[%d] (%d, %u(0x%x), %d, %u(0x%x))\n",
                                        i,
                                        this->bbt[i].BB_die,
                                        this->bbt[i].bad_block, this->bbt[i].bad_block * 131072,
                                        this->bbt[i].RB_die,
                                        this->bbt[i].remap_block, this->bbt[i].remap_block * 131072);
                }
        }
        seq_printf(m, "\n");

	return 0;
}

static int rtk_nand_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, rtk_read_proc_nandinfo, NULL);
}

static const struct file_operations info_proc_fops = {
	.owner = THIS_MODULE,
	.open = rtk_nand_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#ifdef RTK_VERIFY
static int test_read(struct seq_file *s, void *v)
{
	seq_printf(s, "EX.\n");
	seq_printf(s, "echo read > /proc/rtknand/test  --->  simulate read page ecc error.\n");
	seq_printf(s, "echo write > /proc/rtknand/test  --->  simulate write page ecc error.\n");
	seq_printf(s, "echo \"nomap 1234\" > /proc/rtknand/test  --->  set 1234 block as no map block.\n");
	seq_printf(s, "\n");
        seq_printf(s, "r_test_flag :[%u]\n", r_test_flag);
        seq_printf(s, "w_test_flag :[%u]\n", w_test_flag);
        seq_printf(s, "nomap_blk   :[%u]\n", nomap_blk);
	seq_printf(s, "\n");

        return 0;
}

static int test_proc_open(struct inode *inode, struct file *file)
{
        return (single_open(file, test_read, NULL));
}

extern void write_oob_test(void);
static int test_write(struct file *filp, const char *buff, unsigned long len, void *data)
{
        char tmpbuf[64] = {0};
        unsigned int num = 0;

        if (buff && !copy_from_user(tmpbuf, buff, len)) {
                tmpbuf[len - 1] = '\0';

		if(strstr(tmpbuf, "nomap") != NULL) {
			num = sscanf(tmpbuf,"nomap %u", &nomap_blk);
			printk(KERN_ERR "nomap block:[%u]\n", nomap_blk);
		}
		else if(strstr(tmpbuf, "read") != NULL) {
			r_test_flag = 1;
		}
		else if(strstr(tmpbuf, "write") != NULL) {
			w_test_flag = 1;
		}
		else if(strstr(tmpbuf, "timeout") != NULL) {
			w_wait_flag = 1;
		}
        }

        return len;
}

static ssize_t test_proc_write(struct file *file, const char __user *userbuf, size_t count, loff_t *off)
{
        return test_write(file, userbuf, count, off);
}

static struct file_operations test_proc_fops = {
        .open = test_proc_open,
        .write = test_proc_write,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};
#endif

static void rtknand_proc_init(void)
{
        rtknand_proc_dir = proc_mkdir(RTKNAND_PROC_DIR_NAME, &proc_root);
        if (rtknand_proc_dir) {
                proc_create_data("info", 0, rtknand_proc_dir, &info_proc_fops, NULL);
#ifdef RTK_VERIFY
                proc_create_data("test", 0, rtknand_proc_dir, &test_proc_fops, NULL);
#endif
        }
}

static int rtk_nand_probe(struct platform_device *pdev)
{
	int rc = 0;
	struct nand_chip *this = NULL;
	struct device_node *rtk129x_nand_node;
	rtk129x_nand_node = pdev->dev.of_node;

	init_rwsem(&rw_sem);

	map_base = of_iomap(rtk129x_nand_node, 0);
	swc_base = of_iomap(rtk129x_nand_node, 1);

    	rtk_nand_clk_reset_ctrl(&pdev->dev, CTL_ENABLE);

	rtk_nand_gating();

	// controller init.
	REG_WRITE_U32(REG_PD + map_base, 0x1E);
    	REG_WRITE_U32(REG_TIME_PARA3 + map_base, 0x2);
	REG_WRITE_U32(REG_TIME_PARA2 + map_base, 0x5);
	REG_WRITE_U32(REG_TIME_PARA1 + map_base, 0x2);

	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base, 0x0);
	REG_WRITE_U32(REG_READ_BY_PP+map_base, 0x0);
	
	// reset nand.
	REG_WRITE_U32(REG_ND_CMD+map_base, 0xff);
	REG_WRITE_U32(REG_ND_CTL+map_base, 0x80);

	rc = WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	rc = WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);
	NF_DEBUG_PRINT("nand ready. \n");

	REG_WRITE_U32(REG_NF_LOW_PWR+map_base, REG_READ_U32(REG_NF_LOW_PWR+map_base)&~0x10);
	display_version();

	REG_WRITE_U32(REG_SPR_DDR_CTL+map_base, NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0)); //set spare2ddr func. 4=>0.5k spe2ddr_ena at A000F000
	rtk_mtd = kmalloc (MTDSIZE, GFP_KERNEL);
	if ( !rtk_mtd ){
		NF_ERR_PRINT("%s: Error, no enough memory for rtk_mtd\n", __FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (char *)rtk_mtd, 0, MTDSIZE);
	rtk_mtd->priv = this = (struct nand_chip *)(rtk_mtd+1);

	this->read_id		= rtk_nand_read_id;
	this->read_ecc_page 	= rtk_read_ecc_page;
	this->read_oob 		= NULL; //rtk_read_oob;
	this->write_ecc_page	= rtk_write_ecc_page;
	this->write_oob		= rtk_write_oob;
	this->erase_block 	= rtk_erase_block;
	//this->suspend		= rtk_nand_suspend;
	//this->resume		= rtk_nand_resume;
	this->sync		= NULL;

	if( rtk_nand_profile() < 0 ){
		rc = -1;
		goto EXIT;
	}

	page_size = rtk_mtd->writesize;
	oob_size = rtk_mtd->oobsize;
	ppb = (rtk_mtd->erasesize)/(rtk_mtd->writesize);

	rtknand_proc_init();
EXIT:
	if (rc < 0) {
		if (rtk_mtd) {
#if 0
			if (this->erase_page_flag) {
				unsigned int flag_size =  (this->numchips * this->page_num) >> 3;
				unsigned int mempage_order = get_order(flag_size);
				free_pages((unsigned long)this->erase_page_flag, mempage_order);
			}
#endif
			kfree(rtk_mtd);
		}
	} else {
		NF_INIT_PRINT("Realtek Nand Flash Driver is successfully installing.\n");
	}

	return rc;
}

static int rtk_nand_remove(struct platform_device *dev)
{
	struct nand_chip *this = NULL;

	if (rtk_mtd){
		//del_mtd_partitions (rtk_mtd);
		this = (struct nand_chip *)rtk_mtd->priv;
		if (this->g_databuf)
			kfree(this->g_databuf);
		if(this->g_oobbuf)
			kfree(this->g_oobbuf);
#if 0
		if (this->erase_page_flag){
			unsigned int flag_size =  (this->numchips * this->page_num) >> 3;
			unsigned int mempage_order = get_order(flag_size);
			free_pages((unsigned long)this->erase_page_flag, mempage_order);
		}
#endif
		kfree(rtk_mtd);

	}

	return 0;
}

static struct of_device_id rtk129x_nand_ids[] = {
	{ .compatible = "Realtek,rtk1395-nand" },
	{ .compatible = "Realtek,rtk1295-nand" },
	{ .compatible = "Realtek,rtk1195-nand" },
	{ /* Sentinel */ },
};

static const struct dev_pm_ops rtk_nand_dev_pm_ops = {
        SET_SYSTEM_SLEEP_PM_OPS(rtk_nand_suspend, rtk_nand_resume)
};

static struct platform_driver rtk_nand_driver = {
	.probe      = rtk_nand_probe,
	.remove     = rtk_nand_remove,
	.driver     = {
		.name = "rtk_nand_driver",
		.owner = THIS_MODULE,
		.of_match_table = rtk129x_nand_ids,
		.pm     = &rtk_nand_dev_pm_ops,
	},
};

module_platform_driver(rtk_nand_driver);

static int __init rtk_nand_info_setup(char *line)
{
	strlcpy(g_rtk_nandinfo_line, line, sizeof(g_rtk_nandinfo_line));

	return 1;
}
__setup("nandinfo=", rtk_nand_info_setup);

MODULE_AUTHOR("AlexChang <alexchang2131@realtek.com>");
MODULE_DESCRIPTION("Realtek NAND Flash Controller Driver");
