/******************************************************************************
 * $Id: nand_base_rtk.c 317223 2010-06-01 07:38:49Z alexchang2131 $
 * drivers/mtd/nand/nand_base_rtk.c
 * Overview: Realtek MTD NAND Driver
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2008-06-10 Ken-Yu   create file
 *    #001 2008-09-10 Ken-Yu   add BBT and BB management
 *    #002 2008-09-28 Ken-Yu   change r/w from single to multiple pages
 *    #003 2008-10-09 Ken-Yu   support single nand with multiple dies
 *    #004 2008-10-23 Ken-Yu   support multiple nands
 *
 *******************************************************************************/
//#include <linux/delay.h>
//#include <linux/errno.h>
//#include <linux/sched.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
//#include <linux/interrupt.h>
//#include <linux/slab.h>
#include <asm/io.h>
#include <linux/bitops.h>
//#include <linux/parser.h>
// Ken-Yu
#include <mtd/mtd-abi.h>
//#include <linux/mtd/rtk_nand_reg.h>
#include <linux/mtd/rtk_nand.h>
//#include <asm/r4kcache.h>
//#include <asm/page.h>
//#include <linux/jiffies.h>
//#include <asm/mach-venus/platform.h>
//#include <asm/mach-rtk_dmp/platform.h>

#include <common.h>
#include <asm/arch/rbus/nand_reg.h>
#include <rtk_nand_list.h>
//#include <linux/bitops.h>
//#include <linux/string.h>
//#include <linux/kernel.h>
//#include <linux/proc_fs.h>


#ifdef CONFIG_NAND_MULTI_READ_FOR_CARDREADER
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(1)//add for fixing card reader share pin bug. alexchang 0831-2010
#else
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(0)//add for fixing card reader share pin bug. alexchang 0831-2010
#endif

#ifdef CONFIG_NAND_READ_SKIP_UPDATE_BBT
	#define NAND_READ_SKIP_UPDATE_BBT		(1)//add for fixing card reader share pin bug. alexchang 0901-2010
#else
	#define NAND_READ_SKIP_UPDATE_BBT		(0)//add for fixing card reader share pin bug. alexchang 0901-2010
#endif
//#ifdef CONFIG_NAND_BBT_NEW_MECHANISM
//	#define NAND_BBT_NEW_MECHANISM		(1)//add for fixing card reader share pin bug. alexchang 1026-2010
//	static struct semaphore nf_BBT_sem;
//#else
//	#define NAND_BBT_NEW_MECHANISM		(0)//add for fixing card reader share pin bug. alexchang 1026-2010
//#endif

//static DECLARE_MUTEX (sem_rd);
//static DECLARE_MUTEX (sem_wte);
//static DECLARE_MUTEX (sem_bbt);
//static struct semaphore sem_rd;
//static struct semaphore sem_wte;
//static struct semaphore sem_bbt;


struct mtd_info *g_rtk_mtd;
static unsigned char g_isSysSecure = 0;
extern unsigned char g_isRandomize;
extern char rtknand_info[128];
#define Nand_Block_Isbad_Slow_Version 0
#define MTD_SEM_RETRY_COUNT	(0x40)
#define NOTALIGNED(mtd, x) (x & (mtd->writesize-1)) != 0
#define NAND_CP_RW_DISABLE (0xFFFFFFFF)

#define check_end(mtd, addr, len)					\
do {									\
	if (mtd->size == 0) 						\
		return -ENODEV;						\
	else								\
	if ((addr + len) > mtd->size) {					\
		printk (				\
			"%s: attempt access past end of device\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while(0)

#define check_page_align(mtd, addr)					\
do {									\
	if (addr & (mtd->writesize - 1)) {				\
		printk (				\
			"%s: attempt access non-page-aligned data\n",	\
			__FUNCTION__);					\
		printk (				\
			"%s: mtd->writesize = 0x%x\n",			\
			__FUNCTION__,mtd->writesize);			\
		return -EINVAL;						\
	}								\
} while (0)

#define check_block_align(mtd, addr)					\
do {									\
	if (addr & (mtd->erasesize - 1)) {				\
		printk (				\
			"%s: attempt access non-block-aligned data\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

#define check_len_align(mtd,len)					\
do {									\
	if (len & (512 - 1)) {          	 			\
		printk (				\
               	      "%s: attempt access non-512bytes-aligned mem\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

//static DECLARE_MUTEX (mtd_sem);
extern char *rtkNF_parse_token(const char *parsed_string, const char *token);
extern unsigned int rtkNF_getBootcodeSize(void);
extern unsigned int rtkNF_getFactParaSize(void);
extern int is_jupiter_cpu(void);
extern int is_saturn_cpu(void);
extern int is_darwin_cpu(void);
extern int is_macarthur_cpu(void);
extern int is_nike_cpu(void);
extern int is_venus_cpu(void);
extern int is_neptune_cpu(void);
extern int is_mars_cpu(void);
#ifdef NAS_ENABLE
extern int rtk_plat_get_fw_desc_table_start(void);
#endif

unsigned int g_mtd_BootcodeSize = 0;
static void dump_BBT(struct mtd_info *mtd);
static unsigned int rtk_find_real_blk(struct mtd_info *mtd, unsigned int blk);

#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
/*
	parse_token can parse a string and extract the value of designated token.
		parsed_string: The string to be parsed.
		token: the name of the token
		return value: If return value is NULL, it means that the token is not found.
			If return value is "non zero", it means that the token is found, and return value will be a string that contains the value of that token.
			If the token doesn't have a value, return value will be a string that contains empty string ("\0").
			If return value is "non zero", "BE SURE" TO free it after you donot need it.

		Exp:
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A0");
				=> value=NULL
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A1");
				=> value points to a string of "\0"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A2");
				=> value points to a string of "222"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A3");
				=> value points to a string of "333 333"
*/
static char *NF_parse_token(const char *parsed_string, const char *token)
{
	const char *ptr = parsed_string;
	const char *start, *end, *value_start, *value_end;
	char *ret_str;

	while(1) {
		value_start = value_end = 0;
		for(;*ptr == ' ' || *ptr == '\t'; ptr++)	;
		if(*ptr == '\0')	break;
		start = ptr;
		for(;*ptr != ' ' && *ptr != '\t' && *ptr != '=' && *ptr != '\0'; ptr++) ;
		end = ptr;
		if(*ptr == '=') {
			ptr++;
			if(*ptr == '"') {
				ptr++;
				value_start = ptr;
				for(; *ptr != '"' && *ptr != '\0'; ptr++)	;
				if(*ptr != '"' || (*(ptr+1) != '\0' && *(ptr+1) != ' ' && *(ptr+1) != '\t')) {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			} else {
				value_start = ptr;
				for(;*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '"'; ptr++) ;
				if(*ptr == '"') {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			}
			value_end = ptr;
		}

		if(!strncmp(token, start, end-start)) {
			if(value_start) {
				ret_str = kmalloc(value_end-value_start+1, GFP_KERNEL);
				strncpy(ret_str, value_start, value_end-value_start);
				ret_str[value_end-value_start] = '\0';
				return ret_str;
			} else {
				ret_str = kmalloc(1, GFP_KERNEL);
				strcpy(ret_str, "");
				return ret_str;
			}
		}
	}

	return (char*)NULL;
}
#endif

#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
u32 NF_rtk_power_gpio=0;
u32 NF_rtk_power_bits=0;
void NF_rtkcr_card_power(u8 status)
{
    void __iomem *mmio = (void __iomem *) NF_rtk_power_gpio;
    if(status==0){ //power on
        printk("Card Power on\n");
        writel(readl(mmio) & ~(1<<NF_rtk_power_bits),mmio);
    }else{          //power off
        printk("Card Power off\n");
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio);
    }
}
void NF_rtkcr_chk_param(u32 *pparam, u32 len, u8 *ptr)
{
    unsigned int value,i;
    for(i=0;i<len;i++){
        value = ptr[i] - '0';
        if((value >= 0) && (value <=9))
        {
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'a';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'A';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
    }
}
int NF_rtkcr_get_gpio(void)
{
    unsigned char *cr_param;
    void __iomem *mmio;
//    cr_param=(char *)NF_parse_token(platform_info.system_parameters,"cr_pw");
    if(cr_param){
        NF_rtkcr_chk_param(&NF_rtk_power_gpio,4,cr_param);
        NF_rtkcr_chk_param(&NF_rtk_power_bits,2,cr_param+5);

        mmio = (void __iomem *) (NF_rtk_power_gpio+0xb8010000);
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio); //enable GPIO output

        if((NF_rtk_power_gpio & 0xf00) ==0x100){
            NF_rtk_power_gpio+=0xb8010010;
        }else if((NF_rtk_power_gpio & 0xf00) ==0xd00){
            NF_rtk_power_gpio+=0xb8010004;
        }else{
            printk(KERN_ERR "wrong GPIO of card's power.\n");
            return -1;
        }
        printk("power_gpio = 0x%x\n",NF_rtk_power_gpio);
        printk("power_bits = %d\n",NF_rtk_power_bits);
        return 0;
    }
    printk(KERN_ERR "Can't find GPIO of card's power.\n");
    return -1;

}

#endif

int check_buffer_all_one(char* buf, int len) {
	int i = 0;
	int ret = 1;
	
	for (i=0 ; i<len ; i++) 
	{
		if ( *(buf+i) != 0xff ) {
			ret = 0;
			break;
		}
	}
	
	return ret;
}

/* NAND low-level MTD interface functions */
static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf);
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf,
			struct mtd_oob_ops *ops);
static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf);
static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char * buf,
			struct mtd_oob_ops *ops);
static int nand_erase (struct mtd_info *mtd, struct erase_info *instr);
static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt);
static void nand_sync (struct mtd_info *mtd);
static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops);
//static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *oob_buf);

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops);

/* YAFFS2 */

static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs);
static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs);

/////////////////////////////////////////
static int rtk_update_bbt (struct mtd_info *mtd, struct mtd_oob_ops *ops, BB_t *bbt);



/* Global Variables */
#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
int g_sbt_count = 0;
#endif
int RBA=0;
static int oob_size, ppb, isLastPage;
static int ppb_shift;
static int page_size = 0;
//CMYu:, 20090415
//extern platform_info_t platform_info;
char *mp_erase_nand;
int mp_erase_flag = 0;
//CMYu:, 20090512
char *mp_time_para;
int mp_time_para_value = 0;
char *nf_clock;
int nf_clock_value = 0;
//CMYu:, 20090720
char *mcp;

//===========================================================================
#if 0
static void NF_CKSEL(char *PartNum, unsigned int value)
{
	REG_WRITE_U32( 0xb800000c,REG_READ_U32(0xb800000c)& (~0x00800000));
	REG_WRITE_U32( 0xb8000034,value);
	REG_WRITE_U32(0xb800000c,REG_READ_U32(0xb800000c)| (0x00800000));
	printk("[%s] %s is set to nf clock: 0x%x\n", __FUNCTION__, PartNum, value);
}
#endif
//------------------------------------------------------------------------------------------------
static unsigned int rtk_page_to_block(__u32 page)
{
        return page/ppb;
}

int rtk_update_bbt_to_flash(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;

	int rc = 0;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter=0;

	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}

	memset( temp_BBT, 0xff, mem_page_num*page_size);
	this->select_chip(mtd, 0);
	if ( this->erase_block(mtd, 0, 64) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, 64 >> ppb_shift);
		rc =  -1;
		goto EXIT;
	}

	if ( this->erase_block(mtd, 0, 128) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, 128 >> ppb_shift);
		rc =  -1;
		goto EXIT;
	}

	this->ops.oobbuf[0] = BBT_TAG;

	memcpy( temp_BBT, this->bbt, sizeof(BB_t)*RBA );
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, 64+page_counter, temp_BBT+(page_counter*page_size), &this->ops, 1) ) {
				//printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
				//	page ==0?0:1, 64+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, 128+page_counter, temp_BBT+(page_counter*page_size), &this->ops, 1) ) {
				//printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
				//	page ==0?0:1, 128+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}
EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	
	return rc;
}

static int rtk_update_BBT(struct mtd_info *mtd, __u32 blk)
{
        struct nand_chip *this = mtd->priv;
        unsigned int i, flag = 1;

        for ( i=0; i<RBA; i++){
		if (this->bbt[i].bad_block == blk) {
			return -2;
		}

                if (this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT)
                {
                        flag = 0;
                        this->bbt[i].BB_die = 0;
                        this->bbt[i].bad_block = blk;
                        this->bbt[i].RB_die = 0;
                        break;
                }
        }

        if(flag == 1) {
		printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
                return -1;
        }

        dump_BBT(mtd);

        if (rtk_update_bbt_to_flash(mtd)){
                printk("[%s] rtk_update_bbt_to_flash() fails.\n", __FUNCTION__);
                return -1;
        }
        printk("[%s] rtk_update_bbt() successfully.\n", __FUNCTION__);

        return 0;
}

static int cmp_mem(unsigned char* data, unsigned char* data_enc,int len)                                                                                                                      {
        unsigned int i;
        int check_data = 0;

        for (i=0; i<len; i++){
                if(data[i] != data_enc[i]){
                        check_data = 1;
                        break;
                }
        }

        printk("check...%d\n", check_data);

        return check_data;
}

static int rtk_backup_block(struct mtd_info *mtd, __u32 blk)
{
        struct nand_chip *this = mtd->priv;
        __u32 backup_block = rtk_find_real_blk(mtd, blk);
        unsigned int start_page = blk * ppb;
        unsigned int backup_start_page = backup_block * ppb;
        unsigned int i;
        u_char *cmp_data = NULL;
        u_char *buffer = NULL;

	buffer = kmalloc(page_size, GFP_KERNEL);	
        cmp_data = kmalloc(page_size, GFP_KERNEL);

        printk("Start to Backup block from %u to %u\n", blk, backup_block);

        for(i = 0; i < ppb; i++) {
                memset(buffer, 0x00, page_size);

		this->read_ecc_page (mtd, this->active_chip, start_page+i, buffer, NULL, CP_NF_NONE,0,0);
		this->write_ecc_page(mtd, 0, backup_start_page+i, buffer, NULL, 0); 

                memcpy(cmp_data, buffer, page_size);
                memset(buffer, 0x00, page_size);

		this->read_ecc_page (mtd, this->active_chip, backup_start_page+i, buffer, NULL, CP_NF_NONE, 0, 0);

                if(cmp_mem(buffer, cmp_data, page_size)) {
                        printk("check fail.\n");
                } else {
                        printk("check OK.\n");
                }
        }

        //this->g_oobbuf[0] = 0x00;
        this->erase_block(mtd,this->active_chip,  start_page);
        //rc = this->read_ecc_page (mtd, this->active_chip, start_page, buffer, this->g_oobbuf, CP_NF_NONE, phys_addr);
        //rc = this->read_ecc_page (mtd, this->active_chip, start_page+1, buffer, this->g_oobbuf, CP_NF_NONE, phys_addr);

        kfree(buffer);
        kfree(cmp_data);

        return 1;
}

static int rtk_badblock_handle(struct mtd_info *mtd, __u32 page, uint32_t backup)
{
        __u32 block = rtk_page_to_block(page);
	int rc;

	rc = rtk_update_BBT(mtd, block);
        if(rc == -1) {
                printk("[%s] rtk_update_BBT fail.\n", __FUNCTION__);
                return -1;
        }
	else if (rc == -2) {
		printk("[%s] block %u is exist.\n", __FUNCTION__, block);
	}

        if(backup) {
                /* Backup all block */
                if(rtk_backup_block(mtd, block) == -1) {
                        printk("[%s] rtk_backup_all_block fail.\n", __FUNCTION__);
                        return -1;
                }
        }

        return 1;
}

static unsigned long long rtk_from_to_page(struct mtd_info *mtd, loff_t from)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;

	return (int)(from >> this->page_shift);
}

#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
static int rtk_in_shift_table(struct mtd_info *mtd, unsigned int blk)
{
        struct nand_chip *this = (struct nand_chip *) mtd->priv;
        unsigned int i;

        for ( i=0; i<STBCOUNT; i++) {
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
	for ( i=0; i<STBCOUNT; i++) {
		if ( this->sbt[i].chipnum != SB_INIT ) {
			if(blk == this->sbt[i].block) {
                                real_blk = blk + this->sbt[i].shift;
                                break;
                        }

			if(blk < this->sbt[i].block) {
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

//static unsigned int rtk_find_real_blk(struct mtd_info *mtd, unsigned int blk, int *chipnr_remap)
static unsigned int rtk_find_real_blk(struct mtd_info *mtd, unsigned int blk)
{
    struct nand_chip *this = (struct nand_chip *) mtd->priv;
    unsigned int i;
    unsigned int real_blk = blk;
    unsigned int match = 1;

#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
    real_blk = rtk_check_shift_table(mtd, real_blk);
#endif
    for ( i=0; i<RBA; i++){
        if ( this->bbt[i].bad_block != BB_INIT ){
            if ( blk == this->bbt[i].bad_block ){
                real_blk = this->bbt[i].remap_block;
		match++;
                blk = this->bbt[i].remap_block;
            }
        }
    }

    return real_blk;
}

static int  check_BBT(struct mtd_info *mtd, unsigned int blk)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	printk("[%s]..\n", __FUNCTION__);
	int i;
	//int BBs=0;

	for ( i=0; i<RBA; i++)
	{
		if ( this->bbt[i].bad_block == blk )
		{
			printk("blk 0x%x exist\n",blk);
			return -1;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------------------
#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
static void dump_SBT(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	g_sbt_count = 0;

	printk("[%s] Nand SBT Content\n", __FUNCTION__);

	for ( i=0; i<STBCOUNT; i++){
			if ( i==0 && this->sbt[i].chipnum == SB_INIT ) {
			printk("Congratulation!! No shift block in this nand.\n");
			break;
		}

		if ( this->sbt[i].block != SB_INIT ){
			printk("[%d] (%u, %u, %u)\n", i, this->sbt[i].chipnum, this->sbt[i].block, this->sbt[i].shift);
			g_sbt_count++;
		}
	}

	g_sbt_count = g_sbt_count - 1;
}
#endif

static void dump_BBT(struct mtd_info *mtd)
{

	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	int BBs=0;
	printk("[%s] Nand BBT Content\n", __FUNCTION__);
	for ( i=0; i<RBA; i++){
		if ( i==0 && this->bbt[i].BB_die == BB_DIE_INIT && this->bbt[i].bad_block == BB_INIT ){
			printk("Congratulation!! No BBs in this Nand.\n");
			break;
		}
		if ( this->bbt[i].bad_block != BB_INIT ){
			printk("[%d] (%d, %u, %d, %u)\n", i, this->bbt[i].BB_die, this->bbt[i].bad_block,
				this->bbt[i].RB_die, this->bbt[i].remap_block);
			BBs++;
		}
	}
	this->BBs = BBs;
}
#if 0//NAND_BBT_NEW_MECHANISM
int rtk_GetRemapBlk(struct mtd_info *mtd, int chipnr_remap, int block )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	for ( i=0; i<RBA; i++){
	if ( this->bbt[i].bad_block != BB_INIT ){
		if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
			retBlk = this->bbt[i].remap_block;
			if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
				this->active_chip = chipnr_remap = this->bbt[i].RB_die;
				this->select_chip(mtd, chipnr_remap);
			}
		}
	}else
		break;
	}
	return retBlk;
}
//-------------------------------------------------------------------------------------------------
int rtk_BadBlkRemapping(struct mtd_info *mtd, int chipnr, int chipnr_remap, int badblock, int* err_chipnr_remap  )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	while (down_interruptible (&nf_BBT_sem)) {
		printk("%s : Retry\n",__FUNCTION__);
		//return -ERESTARTSYS;
	}
	for( i=0; i<RBA; i++){
		if(this->bbt[i].bad_block==badblock)
		{
			up(&nf_BBT_sem);
			return -1;
		}
	}
	for( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
			if ( chipnr != chipnr_remap)
				this->bbt[i].BB_die = chipnr_remap;
			else
				this->bbt[i].BB_die = chipnr;
			this->bbt[i].bad_block = badblock;
			if(err_chipnr_remap)
				*err_chipnr_remap = this->bbt[i].RB_die;
			retBlk = this->bbt[i].remap_block;
			break;
		}
	}
	up(&nf_BBT_sem);
	if ( retBlk == -1 ){
		printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
		return -1;
	}
	dump_BBT(mtd);
	return retBlk;
}
#endif


/*static void reverse_to_Yaffs2Tags(__u8 *r_oobbuf)
{
	int k;
	int cpBits=0;
	if(page_size==2048)
		cpBits=16;
	else
		cpBits=32;
	for ( k=0; k<cpBits; k++ ){
//	for ( k=0; k<oob_size; k++ ){
		r_oobbuf[k]  = r_oobbuf[1+k];
	}
}*/

#ifndef CONFIG_MTD_NAND_RTK_SHIFTABLE
 static int rtk_block_isbad(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block;
	unsigned char block_status_p1;
#if Nand_Block_Isbad_Slow_Version
	unsigned char block_status_p2;
#endif

	//unsigned char buf[oob_size] __attribute__((__aligned__(4)));

	this->active_chip=chipnr=0;
	page = ofs >> this->page_shift;
	block = page >> ppb_shift;
	
	if ( isLastPage ){
		page = block*ppb + (ppb-1);
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->ops.oobbuf[0];
#if Nand_Block_Isbad_Slow_Version
		page = block*ppb + (ppb-2);
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p2 = this->ops.oobbuf[0];
		//debug_nand("[1]block_status_p1=0x%x, block_status_p2=0x%x\n", block_status_p1, block_status_p2);
#endif
	}else{
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->ops.oobbuf[0];
#if Nand_Block_Isbad_Slow_Version
		if ( this->read_oob (mtd, chipnr, page+1, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page+1=%d failed\n", __FUNCTION__, page+1);
			return 1;
		}
		block_status_p2 = this->ops.oobbuf[0];
		//debug_nand("[2]block_status_p1=0x%x, block_status_p2=0x%x\n", block_status_p1, block_status_p2);
#endif
	}
	
#if Nand_Block_Isbad_Slow_Version
	if ( (block_status_p1 != 0xff) && (block_status_p2 != 0xff) ){
#else
	if ( block_status_p1 != 0xff){
#endif
		printk ("WARNING: Die %d: block=%d is bad, block_status_p1=0x%x\n", chipnr, block, block_status_p1);
		return -1;
	}

	return 0;
}
#endif

static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs)
{
	return 0;
}


static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	int i;
	int rc = 0;
	unsigned char buf[oob_size] __attribute__((__aligned__(4)));
	int chipnr, chipnr_remap;

	page = ofs >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = (int)(ofs >> this->chip_shift);
	page_offset = page & (ppb-1);
	block = page >> ppb_shift;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

	for ( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block != BB_INIT ){
			if ( chipnr == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
				block = this->bbt[i].remap_block;
				if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
					this->active_chip = chipnr_remap = this->bbt[i].RB_die;
					this->select_chip(mtd, chipnr_remap);
				}
			}
		}else
			break;
	}
	page = block*ppb + page_offset;

	buf[0]=0x00;
	rc = this->write_oob (mtd, this->active_chip, page, oob_size, buf);
	if (rc) {
			//DEBUG (MTD_DEBUG_LEVEL0, "%s: write_oob failed\n", __FUNCTION__);
			return -1;
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------
//add by alexchang 0928-2010

//----------------------------------------------------------------------------------------------------
/*
static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen,
			u_char *oob_buf)
{
	struct nand_chip *this = mtd->priv;
	unsigned int page, realpage;
	int oob_len = 0, thislen;
	int rc=0;
	int old_page, page_offset, block;
	int chipnr, chipnr_remap;
	int i;

	if ((from + len) > mtd->size) {
		printk ("nand_read_oob: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}


	if (NOTALIGNED (mtd, from)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n", __func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	block = page >> ppb_shift;
	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);


	if ( retlen )
		*retlen = 0;
	thislen = oob_size;

	while (oob_len < len) {
		if (thislen > (len - oob_len))
			thislen = (len - oob_len);

		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		page = block*ppb + page_offset;

		rc = this->read_oob (mtd, this->active_chip, page, thislen, &oob_buf[oob_len]);
		if (rc < 0) {
			if (rc == -1){
				printk ("%s: read_oob: Un-correctable HW ECC\n", __FUNCTION__);
				if(check_BBT(mtd,page >> ppb_shift)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page >> ppb_shift;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->ops.oobbuf[0] = 0x00;
				if ( isLastPage ){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
				printk("rtk_read_oob: Un-correctable HW ECC Error at page=%d\n", page);
			}else{
				printk ("%s: rtk_read_oob: semphore failed\n", __FUNCTION__);
				return -1;
			}
		}

		oob_len += thislen;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( oob_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){
		if ( oob_len == len )
			*retlen = oob_len;
		else{
			printk("[%s] error: oob_len %d != len %zu\n", __FUNCTION__, oob_len, len);
			return -1;
		}
	}

	return 0;
}
*/


static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf)
{
	int rc=0;

	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);

	//printk("[%s] mtd->writesize =%u\n", __FUNCTION__, mtd->writesize);
	rc = nand_read_ecc (mtd, from, len, retlen, buf, NULL);
	if(g_isSysSecure||g_isRandomize)
        {
		//printk("[%s] done \n",__FUNCTION__);
		//mtd->isScramble= 0;

	}

	return rc;
}

static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	//int chipnr_remap;
	u_char *data_buf = NULL;
	unsigned long long real_page = 0;
	unsigned long long page = 0;
	unsigned long long page_offset = 0;
	unsigned int block = 0;
	unsigned int real_block = 0;
	loff_t new_from = from;

	data_buf = (ops->datbuf)?(ops->datbuf):this->ops.datbuf;

	from += ops->ooboffs;
	ops->oobretlen = 0;

	page = rtk_from_to_page(mtd, new_from);
	page_offset = page & (ppb-1);
	block = page >> ppb_shift;

	real_block = rtk_find_real_blk(mtd, block);
	real_page = (real_block * ppb) + page_offset;

	rc = this->read_ecc_page(mtd, this->active_chip, real_page, data_buf, ops, CP_NF_NONE,0,0);

	ops->oobretlen = oob_size;

	up_write(&rw_sem_rd);

	return rc;

}
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = mtd->priv;
	unsigned long long  page, realpage,page_ppb;
	int data_len;
	int rc = 0;
	unsigned int old_page, page_offset, block, real_block, original_page_offset, original_block;
	int chipnr, chipnr_remap;
	//int i;
	unsigned int max_bitflips = 0;

	//int from_tmp = from;
	debug("[%s] from:0x%08llx, len:0x%08zx, buf:%p \n", __func__, from, len, buf);

	if ((from + len) > mtd->size) {
		printk ("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	//printk("[%s] NOTALIGNED (mtd, from) 0x%x, NOTALIGNED(mtd, len)0x%x\n",__FUNCTION__,NOTALIGNED (mtd, from),NOTALIGNED(mtd, len));

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n",__func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = original_page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = original_block = (unsigned int)page_ppb;
	debug("\t\tReady to READ blk:%u, page:%u, len:%zu, page_size:%d, oob_size:%d\n",block,page_offset,len,page_size,oob_size);

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = 0;
	if(ops)
		ops->oobretlen = 0;

read_after_backup:
	while (data_len < len) {
		real_block = rtk_find_real_blk(mtd, block);
		page = real_block*ppb + page_offset;
		rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, CP_NF_NONE,0,0);
		if (rc < 0) {
			 if(rtk_badblock_handle(mtd, page, 1)) {
                                printk("Finish backup bad block. read after backup.......\n");
                                data_len = 0;
                                page_offset = original_page_offset;
                                block = original_block;
                                //msleep(100);
                                goto read_after_backup;
                        } else {
                                printk("backup bad block fail.\n");
                                return -1;
                        }
		}
		else
			max_bitflips = max_t(unsigned int, max_bitflips, rc);
		data_len += page_size;

		if(ops)//add by alexchang 0524-2010
			ops->oobretlen += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
				printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
				return -1;
		}
	}
	if(rc < 0)
		return rc;

	return max_bitflips;
}


static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	int rc = 0;
	rc = (nand_write_ecc (mtd, to, len, retlen, buf, NULL));

	return rc;
}

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)//for 2.6.34 YAFFS-->mtd
{
	struct nand_chip *this = mtd->priv;
	int rc = 0;
	u_char *data_buf = NULL;

	data_buf = (ops->datbuf)?(ops->datbuf):this->ops.datbuf;

	rc =  nand_write_ecc (mtd, to, ops->len, &ops->retlen, data_buf, ops);
	ops->oobretlen = ops->ooblen;
	ops->retlen = ops->len;

	return rc;
}

static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
			const u_char * buf, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = mtd->priv;
	unsigned long long page, realpage,page_ppb, original_block, original_page_offset;
	int data_len, oob_len;
	int rc;
	unsigned int old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap; //err_chipnr = 0, err_chipnr_remap = 1;
	//int backup_offset;
	//int block_remap=0x12345678;
	if ((to + len) > mtd->size) {
		printk ("nand_write_ecc: Attempt write beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	if (NOTALIGNED (mtd, to) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to write not page aligned data\n", __func__);
		return -EINVAL;
	}
//printk("[%s] to 0x%llx\n",__FUNCTION__,to);
	realpage = (unsigned long long)(to >> this->page_shift);
//	printk("realpage 0x%llx, to 0x%llx\n",realpage,to);
	this->active_chip = chipnr = chipnr_remap = (int)(to >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
//	printk("pagemask 0x%llx\n",this->pagemask);
	page_offset = original_page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = original_block = (unsigned int)page_ppb;
//printk("READY write to block 0x%x",block);
    //printk("Ready to write blk:%u, page:%u, len:%u, page_size:%d, oob_size:%d\n",page/ppb,page%ppb,len,page_size,oob_size);
	//CMYu, 20091030

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = oob_len = 0;

write_after_backup:
	while ( data_len < len) {
		real_block = rtk_find_real_blk(mtd, block);
		page = real_block*ppb + page_offset;
		rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, 0);
		if (rc < 0) {
			printk("%s: write_ecc_page:  write blk:%u, page:%u failed\n", __FUNCTION__,(__u32)page/ppb,(__u32)page%ppb);
                        if(rtk_badblock_handle(mtd, page, 1)) {
                                printk("Finish backup bad block. write after backup.......\n");
                                data_len = 0;
                                page_offset = original_page_offset;
                                block = original_block;
                                //msleep(100);
                                goto write_after_backup;
                        } else {
                                printk("backup bad block fail.\n");
                                return -1;
                        }
#if 0
				printk("[%s] Start to Backup old_page from %d to %d\n", __FUNCTION__, block*ppb, block*ppb+backup_offset-1);

				for ( i=0; i<backup_offset; i++){
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr;
						this->select_chip(mtd, err_chipnr);
					}
					this->read_ecc_page(mtd, this->active_chip, (page/ppb)*ppb+i, this->ops.datbuf, this->ops.oobbuf);
					if ( this->ops.oobbuf )
						reverse_to_Yaffs2Tags(this->ops.oobbuf);
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr_remap;
						this->select_chip(mtd, err_chipnr_remap);
					}
					this->write_ecc_page(mtd, this->active_chip, block_remap*ppb+i, this->ops.datbuf, this->ops.oobbuf, 0);
				}
				this->write_ecc_page (mtd, this->active_chip, block_remap*ppb+backup_offset, &buf[data_len], &oob_buf[oob_len], 0);
				printk("[%s] write failure page = %d to %d\n", __FUNCTION__, page, block_remap*ppb+backup_offset);
#endif
			//}else{
			//	printk ("%s: write_ecc_page:  rc=%d\n", __FUNCTION__, rc);
			//	return -1;
			//}
		}
		//else
			//printk("Confirm to write blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;
		oob_len += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){

		if ( data_len == len )
			*retlen = data_len;
		else{
			printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
			return -1;
		}
	}
	return 0;
}


static int nand_erase (struct mtd_info *mtd, struct erase_info *instr)
{

	return nand_erase_nand (mtd, instr, 0);
}


static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	u_int64_t addr = instr->addr;
	u_int64_t len = instr->len;
	int old_page, page, chipnr, chipnr_remap;
	int block, real_block;
	u_int64_t elen = 0;
	int rc = 0;
	int realpage; //chipnr_remap, block_remap=0x12345678;

	check_end (mtd, addr, len);
	check_block_align (mtd, addr);

	 instr->fail_addr = 0xffffffff;

	realpage = addr >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = addr >> this->chip_shift;
	old_page= page = realpage & this->pagemask;
	block = page >> ppb_shift;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

	instr->state = MTD_ERASING;

	while (elen < len) {
		//int i;
		//real_block = rtk_find_real_blk(mtd, block);
		real_block = block;
		page = real_block*ppb;
		rc = this->erase_block (mtd, this->active_chip, page);
		if (rc) {
			printk ("%s: block erase failed at page address=%llu\n", __FUNCTION__, addr);
                        instr->fail_addr = (page << this->page_shift);
                        rtk_badblock_handle(mtd, page, 0);
		}
		//else
			//printk("confirm to Erase blk %u  succeed!!\n",page/ppb);

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

		block = old_page >> ppb_shift;
	}
	instr->state = MTD_ERASE_DONE;

	return rc;
}


static void nand_sync (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->state = RTK_FL_READY;
}


static void nand_select_chip(struct mtd_info *mtd, int chip)
{
	switch(chip) {
		case -1:
			REG_WRITE_U32(REG_PD,0xff);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			REG_WRITE_U32(REG_PD, ~(1 << chip));
			break;
		default:
			REG_WRITE_U32(REG_PD, ~(1 << 0));
	}
}

#ifndef CONFIG_MTD_NAND_RTK_SHIFTABLE
static int scan_last_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page = 0;
	uint64_t addr;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	//int table_index=0;
	//int remap_block[RBA];
	//int remap_count = 0;
	int i, j;
	int numchips = this->numchips;
	uint64_t chip_size = this->chipsize;
	int rc = 0;
	__u8 *block_status = NULL;
	int start_block = 0;

	g_mtd_BootcodeSize = rtkNF_getBootcodeSize();
	if(g_mtd_BootcodeSize == -1)
	{
		//g_mtd_BootcodeSize = rtk_plat_get_fw_desc_table_start();
		//if (g_mtd_BootcodeSize <= 0)
		g_mtd_BootcodeSize = 0x940000;
	}
	if ( numchips>1 ){
		start_page = 0x00000000;
		printk("multi-chip is not supported yet!!\n");
		return -1;
	}else{
		//start_page = 0x01000000;
		start_page = g_mtd_BootcodeSize;
	}

	printk("[%s] numchips(%x), start_page(%x), ppb(%x)\n", __FUNCTION__, numchips, start_page, ppb);
	// skip the first 0x3e blocks.
	//start_page = block_size * 0x3e;//for fsbl, tee...

	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);

	block_status = kmalloc( block_num, GFP_KERNEL );
	if ( !block_status ){
		printk("%s: Error, no enough memory for block_status\n",__FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (__u32 *)block_status, 0, block_num );

        start_block = (start_page >> this->page_shift) >> ppb_shift;
	printk("chip_size(%llu), block_size(%d), this->phys_erase_shift(%d) RBA:[%d]\n", chip_size, block_size, this->phys_erase_shift, RBA);
	for( addr=start_page; addr<chip_size; addr+=block_size ){
		if ( rtk_block_isbad(mtd, numchips-1, addr) ){
			int bb = addr >> this->phys_erase_shift;
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
			this->bbt[j].BB_die	 = numchips-1;
			this->bbt[j].bad_block	 = i;
			this->bbt[j].RB_die	 = numchips-1;
			j++;
		}
	}
#if 0
	for ( i=0; i<RBA; i++){
		if ( block_status[(block_num-1)-i] == 0x00){
			remap_block[remap_count] = (block_num-1)-i;
			remap_count++;
		}
	}

	if (remap_count<RBA+1){
		for (j=remap_count+1; j<RBA+1; j++)
			remap_block[j-1] = RB_INIT;
	}

	for ( i=0; i<(block_num-RBA); i++){
		if (table_index >= RBA) {
			printk("BB number exceeds RBA. \n");
			break;
		}
		if (block_status[i] == 0xff){
			this->bbt[table_index].bad_block = i;
			this->bbt[table_index].BB_die = numchips-1;
			this->bbt[table_index].remap_block = remap_block[table_index];
			this->bbt[table_index].RB_die = numchips-1;
			table_index++;
		}
	}

	for( i=table_index; table_index<RBA; table_index++){
		this->bbt[table_index].bad_block = BB_INIT;
		this->bbt[table_index].BB_die = BB_DIE_INIT;
		this->bbt[table_index].remap_block = remap_block[table_index];
		this->bbt[table_index].RB_die = numchips-1;
	}
#endif
	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

EXIT:

	if (block_status) {
		kfree(block_status);
	}

	return rc;
}
#endif

#if 0
static int scan_other_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page;
	uint64_t addr;
	int block_size = 1 << this->phys_erase_shift;
	int j, k;
	int numchips = this->numchips;
	uint64_t chip_size = this->chipsize;

	g_mtd_BootcodeSize = rtkNF_getBootcodeSize();
	if(g_mtd_BootcodeSize == -1)
	{
		if(is_darwin_cpu()||is_saturn_cpu()||is_nike_cpu())
			g_mtd_BootcodeSize = 12*1024*1024;
		else
			g_mtd_BootcodeSize = 16*1024*1024;
	}
	for( k=0; k<numchips-1; k++ ){
		this->active_chip = k;
		this->select_chip(mtd, k);
		if( k==0 ){
			// start_page = g_mtd_BootcodeSize;
			// skip the first 0x12 blocks.
			//start_page = ppb * 0x12;
			printk("[%s] skip the first 0x3e blocks !!\n", __FUNCTION__);
			start_page = ppb * 0x3e;
		}else{
			start_page = 0x00000000;
		}

		for( addr=start_page; addr<chip_size; addr+=block_size ){
			if ( rtk_block_isbad(mtd, k, addr) ){
				for( j=0; j<RBA; j++){
					if ( this->bbt[j].bad_block == BB_INIT && this->bbt[j].remap_block != RB_INIT){
						this->bbt[j].bad_block = addr >> this->phys_erase_shift;
						this->bbt[j].BB_die = k;
						this->bbt[j].RB_die = numchips-1;
						break;
					}
				}
			}
		}
	}

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

	return 0;
}
#endif

static int rtk_create_bbt(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter=0;
	
	if(page==ppb)
		printk("[%s] nand driver creates B1 !!\n", __FUNCTION__);
	else if(page==(ppb<<1))
		printk("[%s] nand driver creates B2 !!\n", __FUNCTION__);
	else {
		printk("[%s] abort creating BB on page %x !!\n", __FUNCTION__, page);
		return -1;
	}
#ifndef CONFIG_MTD_NAND_RTK_SHIFTABLE
	if ( scan_last_die_BB(mtd) ){
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}
#else
	int i;
	for ( i = 0 ; i < RBA; i++) {
                this->bbt[i].bad_block = BB_INIT;
                this->bbt[i].BB_die = BB_DIE_INIT;
		this->bbt[i].remap_block = (this->block_num-1) - i;
                this->bbt[i].RB_die = BB_DIE_INIT;
        }
#endif
	if ( this->numchips >1 ){
		//if ( scan_other_die_BB(mtd) ){
			printk("[%s] scan_last_die() error !!\n", __FUNCTION__);
			return -1;
		//}
	}

	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	this->select_chip(mtd, 0);
	if ( this->erase_block(mtd, 0, page) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, page >> ppb_shift);
		rc =  -1;
		goto EXIT;
	}
	this->ops.oobbuf[0] = BBT_TAG;

	memcpy( temp_BBT, this->bbt, sizeof(BB_t)*RBA );
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, page+page_counter, temp_BBT+page_counter*page_size,
			&this->ops, 1) ){
				printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
					page ==0?0:1, page+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	
	return rc;
}


static int rtk_update_bbt (struct mtd_info *mtd, struct mtd_oob_ops *ops, BB_t *bbt)
{
	int rc = 0;
	struct nand_chip *this = mtd->priv;
	unsigned char active_chip = this->active_chip;
	u8 *temp_BBT = 0;
	__u8 *data_buf = ops->datbuf;
	__u8 *oob_buf = ops->oobbuf;

	oob_buf[0] = BBT_TAG;

	this->select_chip(mtd, 0);

	if ( sizeof(BB_t)*RBA <= page_size){
		memcpy( data_buf, bbt, sizeof(BB_t)*RBA );
	}else{
		temp_BBT = kmalloc( 2*page_size, GFP_KERNEL );
		if ( !(temp_BBT) ){
			printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
			return -ENOMEM;
		}
		memset(temp_BBT, 0xff, 2*page_size);
		memcpy(temp_BBT, bbt, sizeof(BB_t)*RBA );
		memcpy(data_buf, temp_BBT, page_size);
	}

	if ( this->erase_block(mtd, 0, ppb) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
	}

	if ( this->write_ecc_page(mtd, 0, ppb, data_buf, ops, 1) ){
		printk("[%s]update BBT B1 page 0 failure\n", __FUNCTION__);
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, ppb+1, data_buf, ops, 1) ){
				printk("[%s]update BBT B1 page 1 failure\n", __FUNCTION__);
			}
			memcpy(data_buf, temp_BBT, page_size);//add by alexchang 0906-2010
		}
	}
	//-----------------------------------------------------------------------
	if ( this->erase_block(mtd, 0, ppb<<1) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
		return -1;
	}

	if ( this->write_ecc_page(mtd, 0, ppb<<1, data_buf, ops, 1) ){
		printk("[%s]update BBT B2 failure\n", __FUNCTION__);
		return -1;
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, 2*ppb+1, data_buf, ops, 1) ){
				printk("[%s]error: erase block 2 failure\n", __FUNCTION__);
				return -1;
			}
		}
	}

	this->select_chip(mtd, active_chip);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}

#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
static int rtk_nand_get_shift_table(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 issbt_t1, issbt_t2;
	u8 *temp_SBT = 0;
	u8 mem_page_num, page_counter = 0;

	RTK_FLUSH_CACHE((unsigned long) this->sbt, sizeof(SB_t)*100);
	mem_page_num = (sizeof(SB_t)*STBCOUNT + page_size-1) / page_size;
	temp_SBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );

	 if ( !temp_SBT ){
                printk("%s: Error, no enough memory for temp_SBT\n",__FUNCTION__);
                return -ENOMEM;
        }
        memset(temp_SBT, 0xff, mem_page_num*page_size);

	rc = this->read_ecc_page(mtd, 0, ppb*4, this->ops.datbuf, &this->ops, CP_NF_NONE, 0, 0);
	issbt_t1 = this->ops.oobbuf[0];
        if ( !rc ){
		if ( issbt_t1 == SBT_TAG ){
			printk("[%s] Get shift table 1, loads it !!\n", __FUNCTION__);
			memcpy( temp_SBT, this->ops.datbuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, (ppb*4)+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE, 0, 0) ) {
					printk("[%s] load shift table 1 error!!\n", __FUNCTION__);
					kfree(temp_SBT);
					return 0;
				}
				memcpy( temp_SBT+page_counter*page_size, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->sbt, temp_SBT, sizeof(SB_t)*100);
		}
		else{
			printk("[%s] read shift table 1 fail, try to read table 2.\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ppb*5, this->ops.datbuf, &this->ops, CP_NF_NONE, 0, 0);
			issbt_t2 = this->ops.oobbuf[0];
			if ( !rc ){
				if ( issbt_t2 == SBT_TAG ){
					printk("[%s] Get shift table 2, loads it !!\n", __FUNCTION__);
					memcpy( temp_SBT, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, (ppb*5)+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE, 0, 0) ){
							printk("[%s] load shift table 2 error!!\n", __FUNCTION__);
							kfree(temp_SBT);
							return 0;
						}
						memcpy( temp_SBT+page_counter*page_size, this->ops.datbuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->sbt, temp_SBT, sizeof(SB_t)*100 );
				}else{
					printk("[%s] read SBT 2 tags fails\n", __FUNCTION__);
					return 0;
				}
			}else{
				printk("[%s] read SBT 2 with HW ECC fail.\n", __FUNCTION__);
				return 0;
			}
		}
	}else{
		printk("[%s] read SBT 1 with HW ECC error, try to load SBT 2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ppb*5, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
		issbt_t2 = this->ops.oobbuf[0];
		if ( !rc ){
			if ( issbt_t2 == SBT_TAG ){
				printk("[%s] Get shift table 2, loads it !!\n", __FUNCTION__);
				memcpy( temp_SBT, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, (ppb*5)+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE, 0, 0) ){
						printk("[%s] load shift table 2 error!!\n", __FUNCTION__);
						kfree(temp_SBT);
						return 0;
					}
					memcpy( temp_SBT+page_counter*page_size, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->sbt, temp_SBT, sizeof(SB_t)*100 );
			}else{
				printk("[%s] read SBT 2 tags fails\n", __FUNCTION__);
				return 0;
			}
		}else{
			printk("[%s] read SBT 1 and 2 with HW ECC fails\n", __FUNCTION__);
			kfree(temp_SBT);
			return 0;
		}
	}

	dump_SBT(mtd);

	if (temp_SBT)
		kfree(temp_SBT);

	return rc;
}
#endif

static int rtk_nand_scan_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 isbbt_b1, isbbt_b2;
	u8 *temp_BBT=0;
	u8 mem_page_num, page_counter=0;

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	
	rc = this->read_ecc_page(mtd, 0, ppb, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
	//printk("read_ecc_page rc = %x , oob = 0x%x\n", rc, this->ops.oobbuf[0]);

	isbbt_b1 = this->ops.oobbuf[0];
	if ( !rc ){
		if ( isbbt_b1 == BBT_TAG ){
			printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
			memcpy( temp_BBT, this->ops.datbuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
					printk("[%s] load bbt B1 error!!\n", __FUNCTION__);
					kfree(temp_BBT);
					return -1;
				}
				memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
		}
		else{
			printk("[%s] read BBT B1 tags fails, try to load BBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ppb<<1, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
			printk("read_ecc_page rc = %x , oob = 0x%x\n", rc, this->ops.oobbuf[0]);
			isbbt_b2 = this->ops.oobbuf[0];
			if ( !rc ){
				if ( isbbt_b2 == BBT_TAG ){
					printk("[%s] have created bbt B2, just loads it !!\n", __FUNCTION__);
					memcpy( temp_BBT, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
							printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
							kfree(temp_BBT);
							return -1;
						}
						memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
				}else{
					printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B1 and B2\n", __FUNCTION__);
					rtk_create_bbt(mtd, ppb);
					rtk_create_bbt(mtd, ppb<<1);
				}
			}else{
				printk("[%s] read BBT B2 with HW ECC fails, nand driver will creat BBT B1\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb);
			}
		}
	}else{
		printk("[%s] read BBT B1 with HW ECC error, try to load BBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ppb<<1, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
		isbbt_b2 = this->ops.oobbuf[0];
		if ( !rc ){
			if ( isbbt_b2 == BBT_TAG ){
				printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
				memcpy( temp_BBT, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
						printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
						kfree(temp_BBT);
						return -1;
					}
					memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
			}else{
				printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb<<1);
			}
		}else{
			printk("[%s] read BBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
			kfree(temp_BBT);
			return -1;
		}
	}

	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
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
	uint64_t chip_size=0;
	unsigned int num_chips_probe = 1;
	uint64_t result = 0;
	uint64_t div_res = 0;
	unsigned int num_coding_blk = 0;
	unsigned int list_num = 0;

	g_rtk_mtd = mtd;

	if ( !this->select_chip )
		this->select_chip = nand_select_chip;
	if ( !this->scan_bbt )
		this->scan_bbt = rtk_nand_scan_bbt;

	this->active_chip = 0;
	this->select_chip(mtd, 0);
#if 0
	if(platform_info.secure_boot)
		g_isSysSecure = 1;
#endif
//printk("nand_base_rtk version:0824-2011\n");
        //if(is_macarthur_cpu())
        //{
        //        if((REG_READ_U32(0xb8060008)&0x01)!=1)
        //       {
        //                printk("[%s]Doesn't support NAND boot for macathur\n",__FUNCTION__);
        //                return -1;
        //        }
        //}
	mtd->name = "rtk_nand";
#if		NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
	NF_rtkcr_get_gpio();
	printk("(V)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#else
	printk("(X)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#endif

#if NAND_READ_SKIP_UPDATE_BBT
		printk("(V)NAND_READ_SKIP_UPDATE_BBT\n");
#else
		printk("(X)NAND_READ_SKIP_UPDATE_BBT\n");
#endif

	while (1) {
		// read 3 times for timing issue.
		this->read_id(mtd, id);
		this->read_id(mtd, id);
		this->read_id(mtd, id);

		this->maker_code = maker_code = id[0];
		this->device_code = device_code = id[1];
		//nand_type_id = maker_code<<24 | device_code<<16 | id[2]<<8 | id[3];
		nand_type_id = id[3]<<24 | id[2]<<16 | device_code<<8 | maker_code;
		B5th = id[4];
		B6th = id[5];

		printk("[Phoenix]READ ID:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",id[0],id[1],id[2],id[3],id[4],id[5]);

		i=1;

		if (i > 1){
			num_chips_probe = i;
			printk(KERN_INFO "NAND Flash Controller detects %d dies\n", num_chips_probe);
		}

		list_num = sizeof(n_device)/sizeof(n_device_type);

		for (i = 0; i < list_num; i++) {
			if ( n_device[i].id == nand_type_id &&
				((n_device[i].id5==0xff)?1:(n_device[i].id5==B5th))&&
				((n_device[i].id6==0xff)?1:(n_device[i].id6==B6th))){
				REG_WRITE_U32( REG_TIME_PARA1,n_device[i].t1);
				REG_WRITE_U32( REG_TIME_PARA2,n_device[i].t2);
				REG_WRITE_U32( REG_TIME_PARA3,n_device[i].t3);

				if ( nand_type_id != HY27UT084G2M ){
					REG_WRITE_U32( REG_MULTI_CHNL_MODE,0x20);
				}

				printk("One %s chip on board with index(%d)\n", n_device[i].string, i);
						
				device_size = n_device[i].size;
				chip_size = n_device[i].size;
				page_size = n_device[i].PageSize;
				block_size = n_device[i].BlockSize;
				oob_size = 64;
				num_chips = 1;
				isLastPage = 0;;
				rtk_lookup_table_flag = 1;
						
				REG_WRITE_U32( REG_TIME_PARA1,n_device[i].t1);
				REG_WRITE_U32( REG_TIME_PARA2,n_device[i].t2);
				REG_WRITE_U32( REG_TIME_PARA3,n_device[i].t3);

				printk("index(%d) nand part=%s, id=0x%x, device_size=0x%x, page_size=0x%x, block_size=0x%x, oob_size=0x%x, num_chips=0x%x, isLastPage=0x%x, ecc_sel=0x%x \n",
							i,
							n_device[i].string,
							n_device[i].id,
							device_size,
							page_size,
							block_size,
							oob_size,
							num_chips,
							isLastPage,
							n_device[i].ecc_bit);
						
				break;
			}
		}

		if ( !rtk_lookup_table_flag ){
			printk("Warning: Lookup Table do not have this nand flash !!\n");
			printk ("%s: Manufacture ID=0x%02x, Chip ID=0x%02x, "
					"3thID=0x%02x, 4thID=0x%02x, 5thID=0x%02x, 6thID=0x%02x\n",
					mtd->name, id[0], id[1], id[2], id[3], id[4], id[5]);
			return -1;
		}

		/* prepare nand info for linux kernel */
		sprintf(rtknand_info, "nandinfo=id:%x,ds:%llu,ps:%d,bs:%d,t1:%d,t2:%d,t3:%d,eb:%d", n_device[i].id, n_device[i].size, n_device[i].PageSize, n_device[i].BlockSize, n_device[i].t1, n_device[i].t2, n_device[i].t3, n_device[i].ecc_bit);

		/* attributes setup */
		this->page_shift = generic_ffs(page_size)-1;
		//this->page_idx_mask = ~((1L << this->page_shift) -1);
		this->phys_erase_shift = generic_ffs(block_size)-1;
		this->oob_shift = generic_ffs(oob_size)-1;
		ppb = this->ppb = block_size >> this->page_shift;
		ppb_shift = this->phys_erase_shift - this->page_shift;

		if (chip_size){
			this->block_num = chip_size >> this->phys_erase_shift;
			this->page_num = chip_size >> this->page_shift;
			this->chipsize = chip_size;
			this->device_size = device_size;
			this->chip_shift =  generic_ffs(this->chipsize )-1;
		}

		//printk("[%s] block_num(0x%x), phys_erase_shift(0x%x)\n", __FUNCTION__, this->block_num, this->phys_erase_shift);

		this->pagemask = (this->chipsize >> this->page_shift) - 1;

		mtd->oobsize = this->oob_size = oob_size;

		mtd->writesize = page_size;//add by alexchang 0923-2010
		mtd->erasesize = block_size;
		mtd->writebufsize = page_size;

		mtd->erasesize_shift = this->phys_erase_shift;
		mtd->writesize_shift = this->page_shift;

		this->ecc_select = n_device[i].ecc_bit;//add by alexchang 0617-2011.
		//this->eccmode = MTD_ECC_RTK_HW;

		// Default to 6 bit BCH ECC if ecc_select = 0
		//if(!this->ecc_select) this->ecc_select = 0x6;

		mtd->ecc_strength = 512;

		if(this->ecc_select>=0x10){
			/* 1KB coding block */
			num_coding_blk = mtd->writesize >> 10;
		}
		else{
			/* 512B coding block */
			num_coding_blk = mtd->writesize >> 9;
		}
		/* Need to consider the ECC error in each mini page? */
		mtd->bitflip_threshold = max(mtd->ecc_strength, 4u) >> 2;

		mtd->ecc_strength *= num_coding_blk;

		break;

	}

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
	
//	RBA = this->RBA = (mtd->size/block_size) * this->RBA_PERCENT/100;
	//if(mtd->u32RBApercentage)
		//mtd->u32RBApercentage = this->RBA_PERCENT;
	//printk("[%s],mtd->u32RBApercentage %d%\n",__FUNCTION__,mtd->u32RBApercentage);
	this->bbt = kmalloc( sizeof(BB_t)*RBA, GFP_KERNEL );

	if ( !this->bbt ){
		printk("%s: Error, no enough memory for BBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->bbt, 0,  sizeof(BB_t)*RBA);

	this->ops.datbuf = kmalloc( page_size, GFP_KERNEL );
	if ( !this->ops.datbuf ){
		printk("%s: Error, no enough memory for g_databuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->ops.datbuf, 0xff, page_size);

	this->ops.oobbuf = kmalloc( oob_size, GFP_KERNEL );
	if ( !this->ops.oobbuf ){
		printk("%s: Error, no enough memory for g_oobbuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->ops.oobbuf, 0xff, oob_size);

	mtd->type			= MTD_NANDFLASH;
	mtd->flags			= MTD_CAP_NANDFLASH;
	mtd->_erase			= nand_erase;
	//mtd->_point			= NULL;
	//mtd->_unpoint		= NULL;
	mtd->_read			= nand_read;
	mtd->_write			= nand_write;
	//mtd->read_ecc		= nand_read_ecc;
	//mtd->write_ecc		= nand_write_ecc;
	mtd->_read_oob		= nand_read_oob;
	mtd->_write_oob	= 	nand_write_oob;
	//mtd->_readv			= NULL;
	//mtd->writev			= NULL;
	//mtd->_readv_ecc	= NULL;
	//mtd->_writev_ecc	= NULL;
	mtd->_sync			= nand_sync;
	mtd->_lock				= NULL;
	mtd->_unlock			= NULL;
	//mtd->owner			= THIS_MODULE;

	mtd->_block_isbad			= nand_block_isbad;
	mtd->_block_markbad	= nand_block_markbad;

	/* Ken: 20090210 */
	//mtd->reload_bbt = rtk_nand_scan_bbt;


#ifdef CONFIG_MTD_NAND_RTK_SHIFTABLE
	if(rtk_nand_get_shift_table(mtd) < 0) 
		return -1;

	RBA = RBA - g_sbt_count - 1;
#endif
	return this->scan_bbt (mtd);
}


/* on the fly */
int nand_read_ecc_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf, struct mtd_oob_ops *ops,u16 cp_mode)
{	
	struct nand_chip *this = mtd->priv;
	unsigned long long  page, realpage,page_ppb;
	int data_len;
	int rc;
	unsigned int old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap;
	int i;


	//printk("[%s] from:0x%x, len:0x%x, buf:0x%x \n", __FUNCTION__, from, len, buf);	
	
	if ((from + len) > mtd->size) {
		printk ("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	//printk("[%s] NOTALIGNED (mtd, from) 0x%x, NOTALIGNED(mtd, len)0x%x\n",__FUNCTION__,NOTALIGNED (mtd, from),NOTALIGNED(mtd, len));

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n", __func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
	//printk("\t\tReady to READ blk:%u, page:%u, len:%u, page_size:%d, oob_size:%d\n",page/ppb,page%ppb,len,page_size,oob_size);

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = 0;

	while (data_len < len) {
		real_block = rtk_find_real_blk(mtd, block);
		page = real_block*ppb + page_offset;
		if(data_len==0)			
            rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, cp_mode,1,len);
        else
			rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, cp_mode,0,0);
		
		if (rc < 0) {
			
			if (rc == -1){
				printk ("%s: read_ecc_page: Un-correctable HW ECC\n", __FUNCTION__);
				//continue;

				//update BBT
				if(check_BBT(mtd,page_ppb)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page_ppb;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->ops.oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
				printk("rtk_read_ecc_page: Un-correctable HW ECC Error at page=%llx\n", page);
			}else{
				printk ("%s: read_ecc_page:  semphore failed\n", __FUNCTION__);
				return -1;
			}
		}
		//else
			//printk("\t\tConfirm to READ blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;

		if(ops)
			ops->oobretlen = oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page/ppb;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
				printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
				return -1;
		}
	}
	//printk("[%s]OK\n",__FUNCTION__);
	//rtk_hexdump("buf: ", buf, *retlen);
	
	return 0;
}

int nand_read_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf, u16 cp_mode)
{
	int rc=0;
	unsigned int tmp_len;

	tmp_len = len;

	rc = nand_read_ecc_on_the_fly (mtd, from, len, retlen, buf, NULL,cp_mode);

	if(*retlen == len)
		*retlen=tmp_len;
		
	return rc;
}

void rtk_rebuild_bbt(void)
{
	printk("rtk_rebuild_bbt() ..... \n");
	rtk_create_bbt(g_rtk_mtd, 64);
        rtk_create_bbt(g_rtk_mtd, 128);

	dump_BBT(g_rtk_mtd);
}

void rtk_dump_bbt(void)
{
	printk("rtk_dump_bbt() ..... \n");

	dump_BBT(g_rtk_mtd);
}
