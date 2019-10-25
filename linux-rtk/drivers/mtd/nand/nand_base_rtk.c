/*
 * nand_base_rtk.c - nand driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <asm/io.h> 
#include <linux/bitops.h>
#include <linux/parser.h>
#include <linux/semaphore.h>
#include <mtd/mtd-abi.h>
#include <linux/mtd/rtk_nand_reg.h>
#include <linux/mtd/rtk_nand.h>
#include <linux/mtd/rtk_nand_list.h>
#include <asm/page.h>
#include <linux/jiffies.h>
#include <linux/dma-mapping.h>

static DECLARE_RWSEM(rw_sem_resume);
static DECLARE_RWSEM(rw_sem_suspend);
static DECLARE_RWSEM(rw_sem_rd);
static DECLARE_RWSEM(rw_sem_wte);
static DECLARE_RWSEM(rw_sem_wte_ecc);
static DECLARE_RWSEM(rw_sem_erase);
static DECLARE_RWSEM(rw_sem_bbt);
static DECLARE_RWSEM(rw_sem_markbad);
static DECLARE_RWSEM(rw_sem_panic_write);
static DECLARE_RWSEM(rw_sem_rd_oob);
static DECLARE_RWSEM(rw_sem_wte_oob);
static DEFINE_SEMAPHORE (sem_rd);
static DEFINE_SEMAPHORE (sem_wte);
static DEFINE_SEMAPHORE (sem_bbt);

#define MAX_NR_LENGTH 1024*1024*2
#define MAX_NW_LENGTH 1024*1024*2
static unsigned char *nwBuffer = NULL;
static unsigned char *nrBuffer = NULL;
dma_addr_t nrPhys_addr;
dma_addr_t oobPhys_addr;
dma_addr_t nwPhys_addr;
static unsigned char *tempBuffer = NULL;
dma_addr_t tempPhys_addr;
static int bEnterSuspend=0;

#define NOTALIGNED(mtd, x) (x & (mtd->writesize-1)) != 0
unsigned int g_eccbits = 0;
static struct mtd_info *g_rtk_mtd = NULL;

extern void __iomem *map_base;

#define check_end(mtd, addr, len)					\
do {									\
	if (mtd->size == 0) 						\
	{								\
		up_write(&rw_sem_erase);				\
		return -ENODEV;						\
	}								\
	else								\
	if ((addr + len) > mtd->size) {					\
		printk (						\
			"%s: attempt access past end of device\n",	\
			__FUNCTION__);					\
		up_write(&rw_sem_erase);				\
		return -EINVAL;						\
	}								\
} while(0)

#define check_block_align(mtd, addr)					\
do {									\
	if (addr & (mtd->erasesize - 1)) {				\
		printk (						\
			"%s: attempt access non-block-aligned data\n",	\
			__FUNCTION__);					\
		up_write(&rw_sem_erase);				\
		return -EINVAL;						\
	}								\
} while (0)

unsigned int g_mtd_BootcodeSize = 0;


/* RTK Nand Chip ID list */
static int rtd_get_set_nand_info(void);
extern char g_rtk_nandinfo_line[64];
static device_type_t g_nand_device;

/* NAND low-level MTD interface functions */
static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf);
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, unsigned char *buf, u_char *oob_buf, struct nand_oobinfo *oobsel, unsigned char *buf_phy);
static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf);
static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const unsigned char * buf, const u_char *oob_buf, struct nand_oobinfo *oobsel, const unsigned char *buf_phy);
static int nand_erase (struct mtd_info *mtd, struct erase_info *instr);
static void nand_sync (struct mtd_info *mtd);
static int nand_suspend (struct mtd_info *mtd);
static void nand_resume (struct mtd_info *mtd);
static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops);
static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops);
static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs);
//static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs);

int rtk_update_bbt (struct mtd_info *mtd, __u8 *data_buf, __u8 *oob_buf, BB_t *bbt);


/* Global Variables */
int RBA=0;
static int oob_size, ppb, isLastPage;
static int page_size = 0;

#ifdef RTK_VERIFY
extern unsigned int r_test_flag;
extern unsigned int w_test_flag;
extern unsigned int nomap_blk;
static void rtk_nand_read_page_check(struct mtd_info *mtd, unsigned int page)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i = 0;
	int rc;

        for(i = 0; i < ppb; i++) {
                rc = this->read_ecc_page (mtd, 0, page+i, tempBuffer, NULL, CP_NF_NONE, (dma_addr_t *) (&tempPhys_addr));
                if ( rc == 1 ) {
                        printk(KERN_ERR "page:[%d][%u] is blank\n", i, page+i);
                }
                else if (rc == 0) {
                        printk(KERN_ERR "read page:[%d][%u] ok\n", i, page+i);
                }
                else {
                        printk(KERN_ERR "read page:[%d][%u] fail\n", i, page+i);
                }
        }
	printk(KERN_ERR "\n");
}
#endif

static unsigned long long rtk_from_to_page(struct mtd_info *mtd, loff_t from)
{
        struct nand_chip *this = (struct nand_chip *) mtd->priv;

        return (int)(from >> this->page_shift);
}

#ifdef RTK_NAND_SHIFTABLE
static int rtk_in_shift_table(struct mtd_info *mtd, unsigned int blk)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	unsigned int i;

	for ( i=0; i<100; i++) {
                if ( this->sbt[i].chipnum != SB_INIT ) {
                        if(blk == this->sbt[i].block) {
                                return 1;
                        }
                }
        }

	return 0;
}

static unsigned int rtk_check_shift_table(struct mtd_info *mtd, unsigned int blk)
{
        struct nand_chip *this = (struct nand_chip *) mtd->priv;
        unsigned int i;
        unsigned int real_blk = blk;

shift_table_recheck:
        for ( i=0; i<100; i++) {
                if ( this->sbt[i].chipnum != SB_INIT ) {
			if(real_blk == this->sbt[i].block) {
				real_blk = blk + this->sbt[i].shift;
				break;
			}

                        if(real_blk < this->sbt[i].block) {
                                real_blk = blk + (this->sbt[i-1].shift);
                                break;
                        }
                }
        }

	if(rtk_in_shift_table(mtd, real_blk)) {
		goto shift_table_recheck;
	}

        return real_blk;
}
#endif

static unsigned int rtk_find_real_blk(struct mtd_info *mtd, unsigned int blk)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	unsigned int i = 0, match = 1, real_blk = blk;
#ifdef RTK_VERIFY
	if(real_blk == nomap_blk) {
		return real_blk;
	}
#endif
#ifdef RTK_NAND_SHIFTABLE
	real_blk = rtk_check_shift_table(mtd, real_blk);
#endif

	for ( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block != BB_INIT ){
			if ( blk == this->bbt[i].bad_block ){
				real_blk = this->bbt[i].remap_block;
				//NF_INFO_PRINT("need to do remap ...... [%d] to [%d][%d]\n", blk, real_blk, match);
				match++;
				blk = this->bbt[i].remap_block;
			}
		}
	}

	return real_blk;
}

#ifdef RTK_VERIFY
static void dump_data(const char *data, unsigned int len)
{
	int i;

	for (i = 0; i < (len/16); i++)
		printk(KERN_ERR "%.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n",
			*(data+(16*i)),*(data+1+(16*i)),*(data+2+(16*i)),*(data+3+(16*i)),*(data+4+(16*i)),*(data+5+(16*i)),*(data+6+(16*i)),*(data+7+(16*i)),
			*(data+8+(16*i)),*(data+9+(16*i)),*(data+10+(16*i)),*(data+11+(16*i)),*(data+12+(16*i)),*(data+13+(16*i)),*(data+14+(16*i)),*(data+15+(16*i))
	);
}
#endif

#ifdef RTK_NAND_SHIFTABLE
static void dump_SBT(struct mtd_info *mtd)
{
        struct nand_chip *this = (struct nand_chip *) mtd->priv;
        int i;

        printk("[%s] Nand SBT Content\n", __FUNCTION__);

        for ( i=0; i<100; i++){
                        if ( i==0 && this->sbt[i].chipnum == SB_INIT ) {
			NF_INFO_PRINT("Congratulation!! No shift block in this nand.\n");
                        break;
                }

                if ( this->sbt[i].block != SB_INIT ){
                        NF_INFO_PRINT("[%d] (%u, %u, %u)\n", i, this->sbt[i].chipnum, this->sbt[i].block, this->sbt[i].shift);
                }
        }
}
#endif

static void dump_BBT(struct mtd_info *mtd)
{
	
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	int BBs=0;

	NF_INFO_PRINT("[%s] Nand BBT Content\n", __FUNCTION__);

	for ( i=0; i<RBA; i++){
		if ( i==0 && this->bbt[i].BB_die == BB_DIE_INIT && this->bbt[i].bad_block == BB_INIT ){
			NF_INFO_PRINT("Congratulation!! No BBs in this Nand.\n");
			break;
		}
		if ( this->bbt[i].bad_block != BB_INIT ){
			NF_INFO_PRINT("[%d] (%d, %u, %d, %u)\n", i, this->bbt[i].BB_die, this->bbt[i].bad_block, 
				this->bbt[i].RB_die, this->bbt[i].remap_block);
			BBs++;
		}
	}
	this->BBs = BBs;
}

static unsigned int rtk_page_to_block(__u32 page)
{
        return page/ppb;
}

int rtk_update_bbt_to_flash(struct mtd_info *mtd)
{
	int rc = 0;
	struct nand_chip *this = mtd->priv;
	unsigned char active_chip = this->active_chip;
	u_char *temp_BBT = NULL;
	BB_t *bbt = this->bbt;
	u_char *new_buf = NULL;

	new_buf = tempBuffer;
	if(new_buf == NULL){
		NF_ERR_PRINT("bbtBuffer error......\n");
		return -ENOMEM;
	}

	this->select_chip(mtd, 0);
	this->g_oobbuf[0] = (BBT_TAG >> 8);	
		
	if (sizeof(BB_t)*RBA <= page_size) {
		memcpy( new_buf, bbt, sizeof(BB_t)*RBA );
	}else{
		temp_BBT = kmalloc( 2 * page_size, GFP_KERNEL );
		if ( !(temp_BBT) ){
			NF_ERR_PRINT("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
			return -ENOMEM;
		}
		memset(temp_BBT, 0xff, 2*page_size);
		memcpy(temp_BBT, bbt, sizeof(BB_t)*RBA );
		memcpy(new_buf, temp_BBT, page_size);
	}
		
	if (this->erase_block(mtd, 0, 64) ){
		NF_ERR_PRINT("[%s]error: erase block 1 failure\n", __FUNCTION__);
	}

	if ( this->write_ecc_page(mtd, 0, 64, new_buf, this->g_oobbuf, (dma_addr_t *)tempPhys_addr) ){
		NF_ERR_PRINT("[%s]update BBT B1 page 64 failure\n", __FUNCTION__);
	}else{
		if ( sizeof(BB_t)*RBA > page_size ) {
			memset(new_buf, 0xff, page_size);
			memcpy(new_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, 65, new_buf, this->g_oobbuf, (dma_addr_t *)tempPhys_addr) ) {
				NF_ERR_PRINT("[%s]update BBT B1 page 1 failure\n", __FUNCTION__);
			}
			memcpy(new_buf, temp_BBT, page_size);
		}	
	}
	
	if ( this->erase_block(mtd, 0, 128) ){
		NF_ERR_PRINT("[%s]error: erase block 1 failure\n", __FUNCTION__);
		return -1;
	}

	if ( this->write_ecc_page(mtd, 0, 128, new_buf, this->g_oobbuf, (dma_addr_t *)tempPhys_addr) ){
		NF_ERR_PRINT("[%s]update BBT B2 failure\n", __FUNCTION__);
		return -1;
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(new_buf, 0xff, page_size);
			memcpy(new_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, 129, new_buf, this->g_oobbuf, (dma_addr_t *)tempPhys_addr) ){
				NF_ERR_PRINT("[%s]error: erase block 2 failure\n", __FUNCTION__);
				return -1;
			}
		}		
	}
	
	this->select_chip(mtd, active_chip);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}

static int rtk_update_BBT(struct mtd_info *mtd, __u32 blk)
{
	struct nand_chip *this = mtd->priv;
        unsigned int i, flag = 1;

        down_write(&rw_sem_bbt);
        for ( i=0; i<RBA; i++){
                if (this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT)
                {
                        flag = 0;
                        this->bbt[i].BB_die = 0;
                        this->bbt[i].bad_block = blk;
                        this->bbt[i].RB_die = 0;
                        break;
                }
        }
        up_write(&rw_sem_bbt);

        if(flag == 1) {
                NF_ERR_PRINT("[%s] RBA do not have free remap block\n", __FUNCTION__);
                return -1;
        }

        dump_BBT(mtd);

        if (rtk_update_bbt_to_flash(mtd)){
                NF_ERR_PRINT("[%s] rtk_update_bbt_to_flash() fails.\n", __FUNCTION__);
                return -1;
        }
        NF_INFO_PRINT("[%s] rtk_update_bbt() successfully.\n", __FUNCTION__);

        return 0;
}

static int cmp_mem(unsigned char* data, unsigned char* data_enc,int len)
{
        unsigned int i;
        int check_data = 0;

        for (i=0; i<len; i++){
                if(data[i] != data_enc[i]){
                        check_data = 1;
                        break;
                }
        }

        NF_DEBUG_PRINT("check...%d\n", check_data);

        return check_data;
}

static int rtk_backup_block(struct mtd_info *mtd, __u32 blk)
{
	struct nand_chip *this = mtd->priv;
        __u32 backup_block = rtk_find_real_blk(mtd, blk);
        unsigned int start_page = blk * ppb;
        unsigned int backup_start_page = backup_block * ppb;
        unsigned int i;
        char *cmp_data = NULL;
	int retry_count = 0;
	int rc;

        cmp_data = kmalloc(page_size, GFP_KERNEL);

        NF_INFO_PRINT("Start to Backup block from %u to %u\n", blk, backup_block);

backup_retry:
	if (this->erase_block(mtd, 0, backup_start_page)) {
		NF_ERR_PRINT("[%s]error: erase block %u failure\n", __FUNCTION__, backup_start_page);
        }
#ifdef RTK_VERIFY
        rtk_nand_read_page_check(mtd, start_page);
#endif
        for(i = 0; i < ppb; i++) {
		memset(tempBuffer, 0x0, page_size);

		rc = this->read_ecc_page (mtd, this->active_chip, start_page+i, tempBuffer, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)tempPhys_addr);
		if(rc == 1) {
			continue;
		}
		rc = this->write_ecc_page(mtd, this->active_chip, backup_start_page+i, tempBuffer, this->g_oobbuf, (dma_addr_t *)tempPhys_addr);

                memcpy(cmp_data, tempBuffer, page_size);
                memset(tempBuffer, 0x0, page_size);
		
		rc = this->read_ecc_page (mtd, this->active_chip, backup_start_page+i, tempBuffer, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)tempPhys_addr);

                if(cmp_mem(tempBuffer, cmp_data, page_size)) {
                        NF_ERR_PRINT("check fail, goto backup_retry.\n");
			if ( retry_count < 3 ) {
				retry_count++;
				goto backup_retry;
			}
                } else {
                        NF_INFO_PRINT("check OK.\n");
                }
        }
#if 1
	for( i=0; i<6; i++) {
		this->g_oobbuf[i] = 0x00;
	}

	rc = this->write_ecc_page (mtd, this->active_chip, start_page, tempBuffer, this->g_oobbuf, (dma_addr_t *)tempPhys_addr);
#endif
	if(cmp_data)
		kfree(cmp_data);
#ifdef RTK_VERIFY
	rtk_nand_read_page_check(mtd, backup_start_page);
#endif
        return 1;
}

static int rtk_badblock_handle(struct mtd_info *mtd, __u32 page, uint32_t backup)
{
        __u32 block = rtk_page_to_block(page);

        if(rtk_update_BBT(mtd, block) == -1) {
                NF_ERR_PRINT("[%s] rtk_update_BBT fail.\n", __FUNCTION__);
                return -1;
        }

	if(backup) {
		/* Backup all block */
		if(rtk_backup_block(mtd, block) == -1) {
			NF_ERR_PRINT("[%s] rtk_backup_all_block fail.\n", __FUNCTION__);
			return -1;
		}
	}

        return 1;
}

#ifdef RTK_VERIFY
static void rtk_nand_read_block_check(struct mtd_info *mtd, unsigned int page)
{
	__u32 block = rtk_page_to_block(page);
	__u32 real_block = rtk_find_real_blk(mtd, block);
        unsigned int start_page = real_block * ppb;

	rtk_nand_read_page_check(mtd, start_page);

	return;
}
#endif

static int rtk_block_isbad(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	unsigned char block_status_p1;
	unsigned char block_status_p1_org;

	this->active_chip=chipnr=0;		
	page = ofs >> this->page_shift;
	block_status_p1_org= this->g_oobbuf[0];
	page_offset = page & (ppb-1);
	block = page/ppb;

	if ( isLastPage ) {
		page = block*ppb + (ppb-1);	
	}	

	if ( this->read_ecc_page(mtd, this->active_chip, ppb, this->g_databuf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&oobPhys_addr) ) {
		NF_ERR_PRINT("%s: read_oob page=%d failed\n", __FUNCTION__, page);
		return 1;
	}
	block_status_p1 = this->g_oobbuf[0];

	if ( block_status_p1 != 0xff){
		NF_ERR_PRINT("WARNING: Die %d: block=%d is bad, block_status_p1=0x%x\n", chipnr, block, block_status_p1);
		return -1;
	}
	
	return 0;
}

static int nand_read(struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf)
{
	int rc=0;
	size_t new_len = 0;
	u_char *new_buf = NULL;
	loff_t new_from = from;
	loff_t is_over_page;
	struct nand_chip *this = mtd->priv;

	down_write(&rw_sem_rd);

	if(len <= 0){
		*retlen = 0;
		NF_ERR_PRINT("%s:%d read non-positive len=%zu\n", __func__, __LINE__, len);
		up_write(&rw_sem_rd);
		return 0;
	}
    	
	if(nrBuffer == NULL){
		nrBuffer = (unsigned char *)dma_alloc_coherent(&mtd->dev, MAX_NR_LENGTH, (dma_addr_t *) (&nrPhys_addr), GFP_KERNEL);
		NF_DEBUG_PRINT("%s:%d allocate from dma_alloc_coherent, nrBuffer=0x%.8x, nrPhys_addr=0x%.8x\n", __func__, __LINE__, nrBuffer, nrPhys_addr);
	}
	
	if (NOTALIGNED(mtd, from)) {
		new_from = from & this->page_idx_mask;
	}

	is_over_page = (from+len-1) & this->page_idx_mask;
	if ((is_over_page-new_from) > ((len-1)&this->page_idx_mask))
		is_over_page = 1;
	else
		is_over_page = 0;

    	new_len = (((len-1)>>this->page_shift)+1+is_over_page)<<this->page_shift;
	new_buf = nrBuffer;

	if (new_buf) {
		rc = nand_read_ecc(mtd, new_from, new_len, retlen, new_buf, NULL, NULL, (unsigned char *)nrPhys_addr);

		if (rc == 0) {
			*retlen = len;
			memcpy(buf, new_buf+(from-new_from), len);
		}
		else {
			*retlen = 0;
		}

		if (new_len > MAX_NR_LENGTH) {
			kfree(new_buf);
		}
	}
    	
	up_write(&rw_sem_rd);

	return rc;
}                          

static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
        int rc = 0;
        unsigned int page = 0, real_page = 0;
        unsigned int page_offset = 0;
        unsigned int block = 0;
        unsigned int real_block = 0;
        loff_t new_from = from;

	from += ops->ooboffs;

	if(ops->datbuf != NULL && ops->len != 0) {
		ops->retlen = 0;
		nand_read(mtd, from, ops->len, &ops->retlen, ops->datbuf);
	}

	down_write(&rw_sem_rd);

	if(ops->oobbuf != NULL && ops->ooblen != 0) {
		ops->oobretlen = 0;

		if (NOTALIGNED(mtd, from)) {
			new_from = from & this->page_idx_mask;
		}

		page = rtk_from_to_page(mtd, new_from);
		page_offset =  page % ppb;
		block = page/ppb;

		real_block = rtk_find_real_blk(mtd, block);

		real_page = (real_block * ppb) + page_offset;

		rc = this->read_ecc_page(mtd, this->active_chip, real_page, this->g_databuf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&nrPhys_addr);

		memcpy(ops->oobbuf, this->g_oobbuf, mtd->oobsize);

		ops->oobretlen = mtd->oobsize;
	}

	up_write(&rw_sem_rd);

	return rc;
}

static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, unsigned char *buf, unsigned char *oob_buf, struct nand_oobinfo *oobsel, unsigned char *buf_phy)
{
	struct nand_chip *this = mtd->priv;
	__u32 page, realpage;
	__u64 page_ppb;
	int data_len, oob_len;
	int rc;
	__u32 old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap;

	if ((from + len) > mtd->size) {
		NF_ERR_PRINT("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		NF_ERR_PRINT("nand_read_ecc: Attempt to read not page aligned data\n");
        	*retlen = 0;
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;

	this->active_chip = chipnr = chipnr_remap = 0;		
	
	this->select_chip(mtd, chipnr);
	
	if ( retlen )
		*retlen = 0;
	
	data_len = oob_len = 0;

	while (data_len < len) {
read_after_backup:
        	real_block = rtk_find_real_blk(mtd, block);
		page = real_block*ppb + page_offset;  
        
		rc = this->read_ecc_page(mtd, this->active_chip, page, &buf[data_len], NULL, CP_NF_NONE, (dma_addr_t *)&buf_phy[data_len]);
#ifdef RTK_VERIFY
                if( r_test_flag == 1 ) {
                        NF_ERR_PRINT("test_flag is 1, block %u is going to be bad block.\n", real_block);
                        r_test_flag = 0;
                        rc = -2;
                }
#endif
		if (rc < 0) {
            		if (rc == -1){
				rc = -1;
                		NF_ERR_PRINT("rtk_read_ecc_page: Un-correctable HW ECC Error at page=%u block:[%u] real_block:[%u]\n", page, block, real_block);
            		}
			else if (rc == -2){
				NF_ERR_PRINT("read_ecc_page: rc:%d read ppb:%u, page:%u failed\n", rc, ppb, page);
				NF_ERR_PRINT("Prepare to to backup\n");
				if(rtk_badblock_handle(mtd, page, 1)) {
					NF_ERR_PRINT("Finish backup bad block. read after backup.......\n");
					msleep(100);
					goto read_after_backup;
				} else {
					NF_ERR_PRINT("backup bad block fail.\n");
					return -1;
				}
			} else if ( rc == -WAIT_TIMEOUT ) {
				NF_ERR_PRINT("WAIT_LOOP timeout, read after nand reset\n");
				msleep(100);
				goto read_after_backup;
			}else{
				NF_ERR_PRINT("%s: read_ecc_page:  semphore failed\n", __FUNCTION__);
				return -1;
			}
		}

		data_len += page_size;

		if(oob_buf)
			oob_len += oob_size;
		
		old_page++;
		page_offset = old_page & (ppb-1);
		block = old_page/ppb;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
			NF_ERR_PRINT("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
			return -1;
		}	
	}

	return 0;
}

static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	int rc = 0;
	u_char *new_buf = NULL;

	down_write(&rw_sem_wte);

	if (bEnterSuspend){
		NF_ERR_PRINT("[%s] - prevent cmd execute while in suspend stage\n",__func__);
		up_write(&rw_sem_wte);
		return 0;
	}

	if (nwBuffer == NULL){
		nwBuffer = (unsigned char *)dma_alloc_coherent(&mtd->dev, MAX_NW_LENGTH, (dma_addr_t *) (&nwPhys_addr), GFP_DMA | GFP_KERNEL);
	}

	new_buf = nwBuffer;
	
	if (new_buf) {
		memcpy(new_buf, buf, len);

		rc = nand_write_ecc (mtd, to, len, retlen, new_buf, NULL, NULL, (unsigned char *)nwPhys_addr);
		if (len > MAX_NW_LENGTH)
		{
			kfree(new_buf);
		}
	}

	up_write(&rw_sem_wte);

	return rc;
}

static int nand_write_ext (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = mtd->priv;
	int rc = 0;
	u_char *new_buf = NULL;

	if (bEnterSuspend){
		NF_ERR_PRINT("[%s] - prevent cmd execute while in suspend stage\n",__func__);
		return 0;
	}

	if (nwBuffer == NULL){
		nwBuffer = (unsigned char *)dma_alloc_coherent(&mtd->dev, MAX_NW_LENGTH, (dma_addr_t *) (&nwPhys_addr), GFP_DMA | GFP_KERNEL);
	}

	new_buf = nwBuffer;
	
	if (new_buf) {
		if(ops->datbuf != NULL && ops->len != 0) {
			memcpy(new_buf, ops->datbuf, ops->len);
		}

		if(ops->oobbuf != NULL && ops->ooblen != 0) {
			memcpy(this->g_oobbuf, ops->oobbuf, ops->ooblen);
		}

		if(ops->datbuf != NULL && ops->oobbuf != NULL) {
			rc = nand_write_ecc (mtd, to, ops->len, &ops->retlen, new_buf, this->g_oobbuf, NULL, (unsigned char *)nwPhys_addr);
		} else if(ops->datbuf != NULL && ops->oobbuf == NULL) {
			rc = nand_write_ecc (mtd, to, ops->len, &ops->retlen, new_buf, NULL, NULL, (unsigned char *)nwPhys_addr);
		} else if(ops->datbuf == NULL && ops->oobbuf != NULL) {
			rc = nand_write_ecc (mtd, to, ops->len, &ops->retlen, NULL, this->g_oobbuf, NULL, (unsigned char *)nwPhys_addr);
		}

		if(rc == 0) {
			ops->oobretlen = ops->ooblen;
		} else {
			NF_ERR_PRINT("nand_write_ext() FAIL\n");
			ops->oobretlen = 0;
		}
	}

	return rc;
}

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)//for 2.6.34 YAFFS-->mtd
{
	struct nand_chip *this = mtd->priv;
	int rc = 0;
        u_char *new_buf = NULL;

	down_write(&rw_sem_wte_oob);

	rc = nand_write_ext(mtd, to, ops);

	up_write(&rw_sem_wte_oob);

	return rc;
}                          

static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, 
			const u_char * buf, const u_char *oob_buf, struct nand_oobinfo *oobsel, const u_char * buf_phy)
{
	struct nand_chip *this = mtd->priv;
	__u32 page, realpage;
	__u64 page_ppb;
	int data_len, oob_len;
	int rc = 0;
	unsigned int old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap;

	if (bEnterSuspend){
		NF_ERR_PRINT("[%s] - prevent cmd execute while in suspend stage\n",__func__);
		return 0;
	}

	if ((to + len) > mtd->size) {
		NF_ERR_PRINT("nand_write_ecc: Attempt write beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}

	if (NOTALIGNED (mtd, to) || NOTALIGNED(mtd, len)) {
		NF_ERR_PRINT("nand_write_ecc: Attempt to write not page aligned data mtd size: %x\n", mtd->writesize-1);
		*retlen = 0;
		return -EINVAL;
	}

	realpage = (unsigned int)(to >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(to >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;

	NF_DEBUG_PRINT("[NAND_DBG][%s] READY write to block 0x%u, page 0x%u",__FUNCTION__, block, page);

	this->active_chip = chipnr = chipnr_remap = 0;

	this->select_chip(mtd, chipnr);
	
	if ( retlen )
		*retlen = 0;
	
	data_len = oob_len = 0;

	while ( data_len < len) {
write_after_backup:
		down_write (&rw_sem_bbt);
		real_block = rtk_find_real_blk(mtd, block);
		up_write (&rw_sem_bbt);
        
		page = real_block*ppb + page_offset;

		NF_DEBUG_PRINT("Confirm to write blk:[%u] real_block:[%d], page:[%u]\n",(__u32)page/ppb, real_block, (__u32)page%ppb);
#ifdef RTK_VERIFY
		if( w_test_flag == 1 ) {
			NF_ERR_PRINT("test_flag is 1, block %u is going to be bad block.\n", real_block);
                        rc = -1;
		} else {
#endif
		if (buf && oob_buf) {
			rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], &oob_buf[oob_len], (dma_addr_t *)&buf_phy[data_len]);
		} else if (buf && !oob_buf) {
			rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], NULL, (dma_addr_t *)&buf_phy[data_len]);
		} else if (!buf && oob_buf) {
			rc = this->write_oob (mtd, this->active_chip, page, oob_size, &oob_buf[oob_len]);
		} else {
			rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], NULL, (dma_addr_t *)&buf_phy[data_len]);
		}
#ifdef RTK_VERIFY
		}

		if (w_test_flag == 2) {
                        w_test_flag = 0;
                        NF_ERR_PRINT("Dump page [%u][%u] after backup. page_offset:[%d]\n", page, real_block, page_offset);
                        rtk_nand_read_block_check(mtd, page);
                        dump_data(&buf[data_len], page_size);
		}
#endif
		if (rc < 0) {
			if (rc == -WAIT_TIMEOUT) {
				NF_ERR_PRINT("WAIT_LOOP timeout, write after nand reset.\n");
                                msleep(100);
                                goto write_after_backup;	
			}
			else {
				NF_ERR_PRINT("%s: write_ecc_page:  write blk:%u, page_offset:[%u]\n", __FUNCTION__, (__u32)page/ppb, page_offset);
				if(rtk_badblock_handle(mtd, page, 1)) {
					NF_ERR_PRINT("Finish backup bad block, re-write ...\n");
#ifdef RTK_VERIFY
					w_test_flag = 2;
#endif
					msleep(100);
					goto write_after_backup;
				} else {
					NF_ERR_PRINT("backup bad block fail.\n");
					return -1;
				}
			}	
		}

		data_len += page_size;
		oob_len += oob_size;		
		old_page++;
		page_offset = old_page & (ppb-1);
		block = old_page/ppb;
	}

	if ( retlen ){
		
		if ( data_len == len )
			*retlen = data_len;
		else{
			NF_ERR_PRINT("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
			return -1;
		}	
	}

	return 0;
}

static int nand_erase (struct mtd_info *mtd, struct erase_info *instr)
{
	return nand_erase_nand (mtd, instr, 0);
}

int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	u_int32_t addr = instr->addr;
	u_int32_t len = instr->len;
	int page, chipnr;
	int old_page, block, real_block;
	u_int32_t elen = 0;
	int rc = 0;
	int realpage, chipnr_remap;
	down_write(&rw_sem_erase);

	if (bEnterSuspend)
	{
		NF_ERR_PRINT("[%s] - prevent cmd execute while in suspend stage\n",__func__);
		up_write(&rw_sem_erase);
		return 0;
	}

	check_end (mtd, addr, len);
	check_block_align (mtd, addr);

	instr->fail_addr = 0xffffffff;

	realpage =  addr >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = addr >> this->chip_shift;
	old_page = page = realpage & this->pagemask;
	block = page/ppb;

	this->active_chip=chipnr=chipnr_remap=0;		
	this->select_chip(mtd, chipnr);
	
	instr->state = MTD_ERASING;
	while (elen < len) {
erase_after_reset:
		down_write (&rw_sem_bbt);
		real_block = rtk_find_real_blk(mtd, block);
		up_write (&rw_sem_bbt);
		
		page = real_block*ppb;
		NF_DEBUG_PRINT("confirm to Erase blk[%u][%d] this->active_chip:[%d]\n", page/ppb, real_block, this->active_chip);
		rc = this->erase_block (mtd, this->active_chip, page);
			
		if (rc) {
			if (rc == -WAIT_TIMEOUT) {
                                NF_ERR_PRINT("WAIT_LOOP timeout, erase after nand reset.\n");
                                msleep(100);
                                goto erase_after_reset;
                        }
			else {
				NF_ERR_PRINT("%s: block erase failed at page address=%u\n", __FUNCTION__, addr);
				instr->fail_addr = (page << this->page_shift);
				rtk_badblock_handle(mtd, page, 0);
			}
		}
		
		if ( chipnr != chipnr_remap )
			this->select_chip(mtd, chipnr);
			
		elen += mtd->erasesize;

		old_page += ppb;
		
		if ( elen<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}

		block = old_page/ppb;
	}
	instr->state = MTD_ERASE_DONE;

	if (!rc)
                mtd_erase_callback(instr);

	up_write(&rw_sem_erase);

	return rc;
}


static void nand_sync (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->state = FL_READY;
}


static int nand_suspend (struct mtd_info *mtd)
{
	down_write(&rw_sem_suspend);
	bEnterSuspend = 1;
	up_write(&rw_sem_suspend);
	return 0;
}


static void nand_resume (struct mtd_info *mtd)
{
	down_write(&rw_sem_resume);
	bEnterSuspend = 0;
	up_write(&rw_sem_resume);
}

static void nand_select_chip(struct mtd_info *mtd, int chip)
{
	switch(chip) {
		case -1:
			REG_WRITE_U32(REG_PD+map_base,0xff);
			break;			
		case 0:
		case 1:
		case 2:
		case 3:
			REG_WRITE_U32(REG_PD+map_base, ~(1 << chip));
			break;
		default:
			REG_WRITE_U32(REG_PD+map_base, ~(1 << 0));
	}
}


static int scan_last_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page = 0, start_block = 0;
	uint32_t addr;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	int i, j;
	int numchips = this->numchips;
	uint32_t chip_size = this->chipsize;
	int rc = 0;
	int bb = 0;
	__u8 *block_status = NULL;
	
	NF_ERR_PRINT("scan_last_die_BB()\n");

	start_page = 0x00000000;
	
	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);
	
	block_status = kmalloc( block_num, GFP_KERNEL );	
	if ( !block_status ){
		NF_ERR_PRINT("%s: Error, no enough memory for block_status\n",__FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (__u32 *)block_status, 0, block_num );

	start_block = (start_page >> this->page_shift) >> (this->phys_erase_shift - this->page_shift);	
	for( addr=start_page; addr<chip_size; addr+=block_size ){
		if ( rtk_block_isbad(mtd, numchips-1, addr) ){
			bb = addr >> this->phys_erase_shift;
			block_status[bb] = 0xff;
		}
	}

        for ( i = 0 ; i < RBA; i++) {
                this->bbt[i].bad_block = BB_INIT;
                this->bbt[i].BB_die = BB_DIE_INIT;
                this->bbt[i].remap_block = (block_num-1) - i;
                this->bbt[i].RB_die = BB_DIE_INIT;
        }

        j = 0;
        for ( i = start_block; i < block_num; i++ ) {
                if(block_status[i] == 0xff) {
                        this->bbt[j].BB_die      = numchips-1;
                        this->bbt[j].bad_block   = i;
                        this->bbt[j].RB_die      = numchips-1;
                        j++;
                }
        }

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	
EXIT:
	if (block_status)
		kfree(block_status);	
				
	return 0;
}

static int rtk_create_bbt(struct mtd_info *mtd, int page)
{
	int rc = 0;
	
	if(page == 64)
		NF_INFO_PRINT("[%s] nand driver creates B1 !!\n", __FUNCTION__);
	else if(page == 128)
		NF_INFO_PRINT("[%s] nand driver creates B2 !!\n", __FUNCTION__);
	else {
		NF_ERR_PRINT("[%s] abort creating BB on page %x !!\n", __FUNCTION__, page);
		return -1;
	}

	if ( scan_last_die_BB(mtd) ){
		NF_ERR_PRINT("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1; 
	}

	dump_BBT(mtd);

	if (rtk_update_bbt_to_flash(mtd)){
                NF_ERR_PRINT("[%s] rtk_update_bbt_to_flash() fails.\n", __FUNCTION__);
                return -1;
        }
        NF_INFO_PRINT("[%s] rtk_update_bbt() successfully.\n", __FUNCTION__);
	
	return rc;		
}

#ifdef RTK_VERIFY
void write_oob_test(void)
{
	struct nand_chip *this = (struct nand_chip *)g_rtk_mtd->priv;
	int i;
	
	for (i=0; i<64; i++) {
		this->g_oobbuf[i] = (0x1 + i);
	}
	this->g_oobbuf[5] = 0xFF;

	memset(nwBuffer, 0xFF, page_size);
	sprintf(nwBuffer, "%s", "AABBCCDDEEFF");

	if (this->erase_block(g_rtk_mtd, 0, 64*3) ){
                NF_ERR_PRINT("[%s]error: erase block 1 failure\n", __FUNCTION__);
        }

        if ( this->write_ecc_page(g_rtk_mtd, 0, 64*3, nwBuffer, this->g_oobbuf, (dma_addr_t *)nwPhys_addr) ) {
                NF_ERR_PRINT("[%s] write_oob_test error. \n", __FUNCTION__);
	}
}
#endif

#ifdef RTK_NAND_SHIFTABLE
static int rtk_nand_get_shift_table(struct mtd_info *mtd, unsigned char *buf_phy)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 issbt_b1, issbt_b2;
	u8 *temp_SBT=0;
	u8 mem_page_num;
	u_char *new_buf = NULL;

	RTK_FLUSH_CACHE((unsigned long) this->sbt, sizeof(SB_t)*100);
	mem_page_num = (sizeof(SB_t)*100 + page_size-1 )/page_size;

	temp_SBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_SBT ){
		NF_ERR_PRINT("%s: Error, no enough memory for temp_SBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_SBT, 0xff, mem_page_num*page_size);

	new_buf = nrBuffer;

	rc = this->read_ecc_page(mtd, this->active_chip, ppb*4, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
	issbt_b1 = this->g_oobbuf[0];
	NF_DEBUG_PRINT("[%s] issbt_b1:[%x] SBT_TAG:[%x] SBT_TAG >> 8 [%x]\n", __FUNCTION__, issbt_b1, SBT_TAG, SBT_TAG >> 8);
	if ( !rc ) {
		if ( issbt_b1 == (SBT_TAG >> 8) ){
			NF_INFO_PRINT("[%s] Get sbt B1, loads it !!\n", __FUNCTION__);
			memcpy( temp_SBT, new_buf, page_size );
			memcpy( this->sbt, temp_SBT, sizeof(SB_t)*100 );
		}
		else{
			NF_INFO_PRINT("[%s] read SBT B1 tags fails, try to load SBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, this->active_chip, ppb*5, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
			issbt_b2 = this->g_oobbuf[0];	
			NF_INFO_PRINT("[%s] issbt_b2:[%x]!!\n", __FUNCTION__, issbt_b2);
			if ( !rc ){
				if ( issbt_b2 == (SBT_TAG >> 8) ){
					NF_INFO_PRINT("[%s] Get sbt B2, loads it !!\n", __FUNCTION__);
					memcpy( temp_SBT, new_buf, page_size );
					memcpy( this->sbt, temp_SBT, sizeof(SB_t)*100 );
				}else{
					NF_INFO_PRINT("[%s] read SBT2 fail\n", __FUNCTION__);
				}
			}else{
				NF_INFO_PRINT("[%s] read SBT2 fail.\n", __FUNCTION__);
			}
		}
	}else{
		NF_INFO_PRINT("[%s] read SBT B1 with HW ECC error, try to load SBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, this->active_chip, ppb*5, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
		issbt_b2 = this->g_oobbuf[0];	
		if ( !rc ){
			if ( issbt_b2 == (SBT_TAG >> 8) ){
				NF_INFO_PRINT("[%s] Get sbt B2, loads it !!\n", __FUNCTION__);
				memcpy( temp_SBT, new_buf, page_size );
				memcpy( this->bbt, temp_SBT, sizeof(SB_t)*100 );
			}else{
				NF_INFO_PRINT("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
			}
		}else{
			NF_INFO_PRINT("[%s] read SBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
		}
	}

	if(!rc) {
		dump_SBT(mtd);
	}

	if (temp_SBT)
		kfree(temp_SBT);
	
	return rc;
}
#endif

static int rtk_nand_scan_bbt(struct mtd_info *mtd, unsigned char *buf_phy)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 isbbt_b1, isbbt_b2;
	u8 *temp_BBT=0;
	u8 mem_page_num;
	u_char *new_buf = NULL;

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
    
	NF_DEBUG_PRINT("[%s]:[%s] ppb:[%d] mem_page_num:[%d]\n", __FILE__, __func__, ppb, mem_page_num);

	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		NF_ERR_PRINT("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);

	new_buf = nrBuffer;

	rc = this->read_ecc_page(mtd, this->active_chip, 64, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
	isbbt_b1 = this->g_oobbuf[0];
	NF_DEBUG_PRINT("[%s] isbbt_b1:[%x] BBT_TAG:[%x] BBT_TAG >> 8 [%x]\n", __FUNCTION__, isbbt_b1, BBT_TAG, BBT_TAG >> 8);
	if ( !rc ){
		if ( isbbt_b1 == (BBT_TAG >> 8) ){
			NF_INFO_PRINT("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
			memcpy( temp_BBT, new_buf, page_size );
			memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
		}
		else{
			NF_INFO_PRINT("[%s] read BBT B1 tags fails, try to load BBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, this->active_chip, 128, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
			isbbt_b2 = this->g_oobbuf[0];	
			NF_INFO_PRINT("[%s] isbbt_b2:[%x]!!\n", __FUNCTION__, isbbt_b2);
			if ( !rc ){
				if ( isbbt_b2 == (BBT_TAG >> 8) ){
					NF_INFO_PRINT("[%s] have created bbt B2, just loads it !!\n", __FUNCTION__);
					memcpy( temp_BBT, new_buf, page_size );
					memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
				}else{
					NF_INFO_PRINT("[%s] read BBT B2 tags fails, nand driver will creat BBT B1 and B2\n", __FUNCTION__);
					rtk_create_bbt(mtd, 64);
					rtk_create_bbt(mtd, 128);
				}
			}else{
				NF_INFO_PRINT("[%s] read BBT B2 with HW ECC fails, nand driver will creat BBT B1\n", __FUNCTION__);
				rtk_create_bbt(mtd, 64);
			}
		}
	}else{
		NF_INFO_PRINT("[%s] read BBT B1 with HW ECC error, try to load BBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, this->active_chip, 128, new_buf, this->g_oobbuf, CP_NF_NONE, (dma_addr_t *)&buf_phy[0]);
		isbbt_b2 = this->g_oobbuf[0];	
		if ( !rc ){
			if ( isbbt_b2 == (BBT_TAG >> 8) ){
				NF_INFO_PRINT("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
				memcpy( temp_BBT, new_buf, page_size );
				memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
			}else{
				NF_INFO_PRINT("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
				rtk_create_bbt(mtd, 128);
			}
		}else{
			NF_INFO_PRINT("[%s] read BBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
			kfree(temp_BBT);
			return -1;
		}
	}

	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);
	
	return rc;
}

static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs)
{
        return 0;
}

static int nand_block_markbad (struct mtd_info *mtd, loff_t to)
{
        struct nand_chip *this = mtd->priv;
        unsigned int page = rtk_from_to_page(mtd, to);

	printk(KERN_ERR "nand_block_markbad(), This function should not be called. page:[%d] block:[%d]\n", page ,page/ppb);

        return 0;
}

static void rtd_set_nand_info(char *item)
{
	int ret = 0;
	char *s = NULL;
	unsigned int temp = 0;

	if( (s = strstr(item, "ds:")) != NULL ){
		ret = kstrtoull(s+3, 10, &g_nand_device.size);
		g_nand_device.chipsize = g_nand_device.size;
	}
	else if( (s = strstr(item, "ps:")) != NULL ){
		ret = kstrtouint(s+3, 10, &g_nand_device.PageSize);
	}
	else if( (s = strstr(item, "bs:")) != NULL ){
		ret = kstrtouint(s+3, 10, &g_nand_device.BlockSize);
	}
	else if( (s = strstr(item, "t1:")) != NULL ){
		ret = kstrtouint(s+3, 10, &temp);
		g_nand_device.T1 = (unsigned char)temp;
	}
	else if( (s = strstr(item, "t2:")) != NULL ){
		ret = kstrtouint(s+3, 10, &temp);
		g_nand_device.T2 = (unsigned char)temp;
	}
	else if( (s = strstr(item, "t3:")) != NULL ){
		ret = kstrtouint(s+3, 10, &temp);
		g_nand_device.T3 = (unsigned char)temp;
	}
	else if( (s = strstr(item, "eb:")) != NULL ){
		ret = kstrtouint(s+3, 10, &temp);
		g_nand_device.eccSelect = (unsigned short)temp;
	}
}

static int rtd_get_set_nand_info()
{
	const char * const delim = ",";
	char *sepstr = g_rtk_nandinfo_line;
	char *substr = NULL;

	if(strlen(g_rtk_nandinfo_line) == 0) {
		NF_INIT_PRINT("No nand info got from lk!!!!\n");
		return -1;
	}

	memset(&g_nand_device, 0x0, sizeof(device_type_t));

	NF_INIT_PRINT("g_rtk_nandinfo_line:[%s]\n", sepstr);

	substr = strsep(&sepstr, delim);

	do{
		rtd_set_nand_info(substr);

		substr = strsep(&sepstr, delim);
	}while(substr);

	g_nand_device.num_chips = 1;
	g_nand_device.isLastPage = 0;

	if(g_nand_device.eccSelect == 0x1)
		g_nand_device.OobSize = 128;
	else
		g_nand_device.OobSize = 64;

	NF_INFO_PRINT("total flash size:[%llu]\n", g_nand_device.size);
	NF_INFO_PRINT("chip size:[%llu]\n", g_nand_device.chipsize);
	NF_INFO_PRINT("page size:[%d]\n", g_nand_device.PageSize);
	NF_INFO_PRINT("block size:[%d]\n", g_nand_device.BlockSize);
	NF_INFO_PRINT("oob size:[%d]\n", g_nand_device.OobSize);
	NF_INFO_PRINT("t1:[%d]\n", g_nand_device.T1);
	NF_INFO_PRINT("t2:[%d]\n", g_nand_device.T2);
	NF_INFO_PRINT("t3:[%d]\n", g_nand_device.T3);
	NF_INFO_PRINT("ecc select:[%d]\n", g_nand_device.eccSelect);

	return 1;
}

int rtk_nand_scan(struct mtd_info *mtd, int maxchips)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned char id[6];
	unsigned int device_size=0;
	unsigned int i;
	unsigned int nand_type_id ;
	int rtk_lookup_table_flag=0;
	unsigned char maker_code;	
	unsigned char device_code; 
	unsigned char B5th;
	unsigned char B6th;
	unsigned int block_size;
	unsigned int num_chips = 1;
	uint32_t chip_size=0;
	unsigned int num_chips_probe = 1;
	uint64_t result = 0;
	uint64_t div_res = 0;
	unsigned int flag_size, mempage_order;

	g_rtk_mtd = mtd;
	
	if ( !this->select_chip )
		this->select_chip = nand_select_chip;
	if ( !this->scan_bbt )
		this->scan_bbt = rtk_nand_scan_bbt;

	this->active_chip = 0;
	this->select_chip(mtd, 0);

	NF_INFO_PRINT("nand_base_rtk version:0815-2018\n");

	mtd->name = "rtk_nand";

	if(rtd_get_set_nand_info() > 0)
	{
		NF_INFO_PRINT("Get nand info from bootcode successfully.\n");
		
		REG_WRITE_U32( REG_TIME_PARA1+map_base, g_nand_device.T1);
		REG_WRITE_U32( REG_TIME_PARA2+map_base, g_nand_device.T2);
		REG_WRITE_U32( REG_TIME_PARA3+map_base, g_nand_device.T3);

		device_size = g_nand_device.size;
		chip_size   = g_nand_device.chipsize;
		page_size   = g_nand_device.PageSize;
		block_size  = g_nand_device.BlockSize;
		oob_size    = g_nand_device.OobSize;
		num_chips   = g_nand_device.num_chips;
		isLastPage  = g_nand_device.isLastPage;

		REG_WRITE_U32( REG_TIME_PARA1+map_base, g_nand_device.T1);
		REG_WRITE_U32( REG_TIME_PARA2+map_base, g_nand_device.T2);
		REG_WRITE_U32( REG_TIME_PARA3+map_base, g_nand_device.T3);

		this->page_shift = __ffs(page_size); 
		this->page_idx_mask = ~((1L << this->page_shift) -1);
		this->phys_erase_shift = __ffs(block_size);
		this->oob_shift = __ffs(oob_size);
		ppb = this->ppb = block_size >> this->page_shift;

		if (chip_size){
			this->block_num = chip_size >> this->phys_erase_shift;
			this->page_num = chip_size >> this->page_shift;
			this->chipsize = chip_size;
			this->device_size = device_size;
			this->chip_shift =  __ffs(this->chipsize );
		}

		this->pagemask = (this->chipsize >> this->page_shift) - 1;

		mtd->oobsize = this->oob_size = oob_size;

		mtd->writesize = page_size;
		mtd->erasesize = block_size;
		mtd->writebufsize = page_size;

		mtd->erasesize_shift = this->phys_erase_shift;
		mtd->writesize_shift = this->page_shift;

		this->ecc_select = g_nand_device.eccSelect;
	}
	else 
	{
		while (1) {
			this->read_id(mtd, id);

			this->maker_code = maker_code = id[0];
			this->device_code = device_code = id[1];
			nand_type_id = maker_code<<24 | device_code<<16 | id[2]<<8 | id[3];
			B5th = id[4];
			B6th = id[5];

			NF_INFO_PRINT("READ ID:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",id[0],id[1],id[2],id[3],id[4],id[5]);		

			NF_INFO_PRINT("NAND Flash Controller detects %d dies\n", num_chips_probe);

			for (i = 0; nand_device[i].name; i++){

				if ( nand_device[i].id==nand_type_id && 
						((nand_device[i].CycleID5th==0xff)?1:(nand_device[i].CycleID5th==B5th))&&
						((nand_device[i].CycleID6th==0xff)?1:(nand_device[i].CycleID6th==B6th))) {
					REG_WRITE_U32( REG_TIME_PARA1+map_base,nand_device[i].T1);
					REG_WRITE_U32( REG_TIME_PARA2+map_base,nand_device[i].T2);
					REG_WRITE_U32( REG_TIME_PARA3+map_base,nand_device[i].T3);
					if ( nand_type_id != HY27UT084G2M ){
						REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,0x20);
					}
					if (nand_device[i].size == num_chips_probe * nand_device[i].chipsize){
						if ( num_chips_probe == nand_device[i].num_chips ){
							NF_INFO_PRINT("One %s chip has %d die(s) on board\n", 
									nand_device[i].name, nand_device[i].num_chips);
							//mtd->PartNum = nand_device[i].name;
							device_size = nand_device[i].size;
							chip_size = nand_device[i].chipsize;
							page_size = nand_device[i].PageSize;
							block_size = nand_device[i].BlockSize;
							oob_size = nand_device[i].OobSize;
							num_chips = nand_device[i].num_chips;
							isLastPage = nand_device[i].isLastPage;
							rtk_lookup_table_flag = 1;
							REG_WRITE_U32( REG_TIME_PARA1+map_base,nand_device[i].T1);
							REG_WRITE_U32( REG_TIME_PARA2+map_base,nand_device[i].T2);
							REG_WRITE_U32( REG_TIME_PARA3+map_base,nand_device[i].T3);
							NF_INFO_PRINT("index(%d) nand part=%s, id=0x%x, device_size=%llu, page_size=0x%x, block_size=0x%x, oob_size=0x%x, num_chips=0x%x, isLastPage=0x%x, ecc_sel=0x%x \n",
									i,
									nand_device[i].name,
									nand_device[i].id,
									nand_device[i].size,
									page_size,
									block_size,
									oob_size,
									num_chips,
									isLastPage,
									nand_device[i].eccSelect);
							break;
						}				
					}else{
						if ( !strcmp(nand_device[i].name, "HY27UF084G2M" ) )
							continue;
						else{	
							NF_INFO_PRINT("We have %d the same %s chips on board\n", 
									num_chips_probe/nand_device[i].num_chips, nand_device[i].name);
							//mtd->PartNum = nand_device[i].name;
							device_size = nand_device[i].size;
							chip_size = nand_device[i].chipsize;	
							page_size = nand_device[i].PageSize;
							block_size = nand_device[i].BlockSize;
							oob_size = nand_device[i].OobSize;
							num_chips = nand_device[i].num_chips;
							isLastPage = nand_device[i].isLastPage;
							rtk_lookup_table_flag = 1;
							NF_INFO_PRINT("nand part=%s, id=%x, device_size=%llu, chip_size=%llu, num_chips=%d, isLastPage=%d, eccBits=%d\n", 
									nand_device[i].name, nand_device[i].id, nand_device[i].size, nand_device[i].chipsize, 
									nand_device[i].num_chips, nand_device[i].isLastPage, nand_device[i].eccSelect);
							break;
						}
					}
				}
			}

			if ( !rtk_lookup_table_flag ){
				NF_ERR_PRINT("Warning: Lookup Table do not have this nand flash !!\n");
				NF_ERR_PRINT("%s: Manufacture ID=0x%02x, Chip ID=0x%02x, "
						"3thID=0x%02x, 4thID=0x%02x, 5thID=0x%02x, 6thID=0x%02x\n",
						mtd->name, id[0], id[1], id[2], id[3], id[4], id[5]);
				return -1;
			}

			this->page_shift = __ffs(page_size); 
			this->page_idx_mask = ~((1L << this->page_shift) -1);
			this->phys_erase_shift = __ffs(block_size);
			this->oob_shift = __ffs(oob_size);
			ppb = this->ppb = block_size >> this->page_shift;

			if (chip_size){
				this->block_num = chip_size >> this->phys_erase_shift;
				this->page_num = chip_size >> this->page_shift;
				this->chipsize = chip_size;
				this->device_size = device_size;
				this->chip_shift =  __ffs(this->chipsize );
			}

			this->pagemask = (this->chipsize >> this->page_shift) - 1;

			mtd->oobsize = this->oob_size = oob_size;

			mtd->writesize = page_size;//add by alexchang 0923-2010
			mtd->erasesize = block_size;
			mtd->writebufsize = page_size;

			mtd->erasesize_shift = this->phys_erase_shift;
			mtd->writesize_shift = this->page_shift;

			this->ecc_select = nand_device[i].eccSelect;//add by alexchang 0617-2011.

			break;
		}
	}

	switch(this->ecc_select) {
		case 0x0:
			g_eccbits = 6;
                        break;
                case 0x1:
			g_eccbits = 12;
                        break;
                case 0xe:
			g_eccbits = 16;
                        break;
                case 0xa:
			g_eccbits = 24;
                        break;
                case 0x2:
			g_eccbits = 40;
                        break;
                case 0x4:
			g_eccbits = 43;
                        break;
                case 0x6:
			g_eccbits = 65;
                        break;
                case 0x8:
			g_eccbits = 72;
                        break;
                default:
			g_eccbits = 6;
                        break;
        }

	 if(g_eccbits >= 0x18)
		mtd->ecc_strength = 1024;
        else
		mtd->ecc_strength = 512;

	this->select_chip(mtd, 0);
			
	if ( num_chips != num_chips_probe )
		this->numchips = num_chips_probe;
	else
		this->numchips = num_chips;
	div_res = mtd->size = this->numchips * this->chipsize;

	do_div(div_res,block_size);
	result = div_res;
	result*=this->RBA_PERCENT;
	do_div(result,100);
	RBA = this->RBA = result;


	RBA = this->RBA = ((unsigned int)mtd->size/block_size) * this->RBA_PERCENT/100;

	mtd->dev.coherent_dma_mask = 0xffffffff;

	this->bbt = kmalloc( sizeof(BB_t)*RBA, GFP_KERNEL );
	if ( !this->bbt ){
		NF_ERR_PRINT("%s: Error, no enough memory for BBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->bbt, 0,  sizeof(BB_t)*RBA);

#ifdef RTK_NAND_SHIFTABLE
	this->sbt = kmalloc( sizeof(SB_t)*100, GFP_KERNEL );
	if ( !this->sbt ){
		NF_ERR_PRINT("%s: Error, no enough memory for SBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->sbt, 0,  sizeof(SB_t)*100);
#endif

	nrBuffer = (unsigned char *)dma_alloc_coherent(&mtd->dev, MAX_NR_LENGTH, (dma_addr_t *) (&nrPhys_addr), GFP_DMA | GFP_KERNEL);
	if ( !nrBuffer ) {
		NF_ERR_PRINT("%s: Error, no enough memory for nrBuffer\n",__FUNCTION__);
		return -ENOMEM;	
        }
	memset(nrBuffer, 0xff, MAX_NR_LENGTH);

	this->g_oobbuf = (unsigned char  *)dma_alloc_coherent(&mtd->dev, oob_size*256, (dma_addr_t *) (&oobPhys_addr), GFP_KERNEL | GFP_DMA);
	if ( !this->g_oobbuf ){
		NF_ERR_PRINT("%s: Error, no enough memory for g_oobbuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->g_oobbuf, 0xff, oob_size);

	tempBuffer = (unsigned char  *)dma_alloc_coherent(&mtd->dev, 2048*4, (dma_addr_t *) (&tempPhys_addr), GFP_KERNEL | GFP_DMA);
	if ( !tempBuffer ){
                NF_ERR_PRINT("%s: Error, no enough memory for tempBuffer\n",__FUNCTION__);
                return -ENOMEM;
        }
        memset(tempBuffer, 0xff, 2048*4);

	flag_size =  (this->numchips * this->page_num) >> 3;
	mempage_order = get_order(flag_size);
#if 0	
	this->erase_page_flag = (void *)__get_free_pages(GFP_KERNEL, mempage_order);	
	if ( !this->erase_page_flag ){
		NF_ERR_PRINT("%s: Error, no enough memory for erase_page_flag\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset ( (__u32 *)this->erase_page_flag, 0, flag_size);
#endif
	mtd->type		= MTD_NANDFLASH;
	mtd->flags		= MTD_CAP_NANDFLASH;
	mtd->_erase		= nand_erase;
	mtd->_point		= NULL;
	mtd->_unpoint		= NULL;
	mtd->_read		= nand_read;
	mtd->_write		= nand_write;
	mtd->_read_oob		= nand_read_oob;
	mtd->_write_oob		= nand_write_oob;
	mtd->_sync		= nand_sync;
	mtd->_lock		= NULL;
	mtd->_unlock		= NULL;
	mtd->_suspend		= nand_suspend;
	mtd->_resume		= nand_resume;
	mtd->owner		= THIS_MODULE;
	mtd->_block_isbad	= nand_block_isbad;
	mtd->_block_markbad	= nand_block_markbad;
	mtd->_panic_write	= NULL; //panic_nand_write;
	mtd->owner = THIS_MODULE;

#ifdef RTK_NAND_SHIFTABLE
	if(rtk_nand_get_shift_table(mtd, (unsigned char *)nrPhys_addr) < 0) {
                return -1;
	}
#endif

	return this->scan_bbt(mtd, (unsigned char *)nrPhys_addr);
}
