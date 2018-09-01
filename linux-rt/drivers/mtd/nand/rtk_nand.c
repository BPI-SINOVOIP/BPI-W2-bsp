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
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

#include <linux/dma-mapping.h>
#include "../mtdcore.h"

#include <linux/of.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>

#include <linux/clk.h>
#include <linux/reset.h>


//#include <asm/system_info.h>
//#define CP15DMB	asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))
#define CP15DMB	asm volatile ("DMB SY" : : : "memory")

#define BANNER  "Realtek NAND Flash Driver"
#define VERSION  "$Id: rtk_nand.c 2015-10-29 01:32:27Z aaron.lin $"
#define RTK_NAND_INTERRUPT	(0)
#define MTDSIZE	(sizeof (struct mtd_info) + sizeof (struct nand_chip))
#define MAX_PARTITIONS	16
#define BOOTCODE	16*1024*1024	//16MB
#define FACT_PARAM_SIZE 4*1024*1024 //4MB for TV factory parameter use.
#define DRIVER_NAME "rtkNF"
#define NF_INIT	(0)
#define NF_READ_TRIGGER 	(1)
#define NF_WRITE_TRIGGER 	(2)
#define NF_ERASE_TRIGGER 	(3)
#define NF_POLL_STATUS 	(4)
#define NF_WAKE_UP	(5)

#define NF_AUTO_IRQ_MASK	(0x08)
#define NF_DMA_IRQ_MASK		(0x10)
#define NF_POLL_IRQ_MASK	(0x80)
#define NF_XFER_IRQ_MASK	(0x04)
#define NF_IRQ_MASK	(NF_XFER_IRQ_MASK|NF_AUTO_IRQ_MASK|NF_DMA_IRQ_MASK|NF_POLL_IRQ_MASK)

#define NF_RESET_IRQ	REG_WRITE_U32(REG_NAND_ISREN,(0xff<<1|0x00));\
						REG_WRITE_U32(REG_NAND_ISR,(0xff<<1|0x00))

//#define NF_RESET_IRQ	NULL

#define NF_ENABLE_IRQ(mask)	REG_WRITE_U32(REG_NAND_ISREN,(mask|0x01))


static int g_nfFlag = NF_INIT ;

#define CLR_REG_NAND_ISR REG_WRITE_U32(REG_NAND_ISR,(0xFF<<1))

#define ISR_EN_READ (0x10)
#define ISR_EN_WRITE (0x08)

#ifdef CONFIG_MTD_NAND_RTK_HW_SEMAPHORE

#define HD_SEM_REG	(0xB801A63c)
#define DUMMY_REG	(0xB801A604)

extern void rtk_spin_lock(void);
extern void rtk_spin_unlock(void);

#endif

static int g_id_chain = 0;
static int g_enReadRetrial = 0;
static unsigned char regVal1=0;
static unsigned char regVal2=0;
static unsigned char regVal3=0;
static unsigned char regVal4=0;
static unsigned char nRun=0;
static unsigned char nInc=0;


static int read_retry_toshiba_cnt[]={0x00, 0x00, 0x04, 0x7c, 0x78, 0x74, 0x08};
static int read_retry_toshiba_cnt_new[8][5]={
        {0x00, 0x00, 0x00, 0x00, 0x00},
        {0x04, 0x04, 0x7c, 0x7e, 0x00},
        {0x00, 0x7c, 0x78, 0x78, 0x00},
        {0x7c, 0x76, 0x74, 0x72, 0x00},
        {0x08, 0x08, 0x00, 0x00, 0x00},
        {0x0b, 0x7e, 0x76, 0x74, 0x00},
        {0x10, 0x76, 0x72, 0x70, 0x00},
        {0x02, 0x7c, 0x7e, 0x70, 0x00}
};


static struct mtd_partition rtk_partitions[] = 
{
    {
        .name   = "bootcode",
        .size   = 0x940000,
        .offset = 0,
        .mask_flags = MTD_WRITEABLE
    },
    {
        .name   = "system",
        .size   = 0x20000000 - 0x940000,
        .offset = 0x940000
    }
};

char g_rtk_nandinfo_line[64];

int g_sw_WP_level = -1;

int g_isCheckEccStatus = 0;

void __iomem    *map_base = 0;
void __iomem    *muxpad0_base = 0;

static void rtk_xfer_GetParameter(void);
static void rtk_xfer_SetParameter(unsigned char val1,unsigned char val2,unsigned char val3,unsigned char val4);
static void rtk_set_feature_micron(int P1);

//static void rtk_SetVal( char val1, char val2, char val3, char val4);
static void rtk_SetReadRetrialMode(unsigned int run);
static int rtk_read_ecc_page_reTrial (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf);

extern int pcb_mgr_get_enum_info_byname(char *enum_name, unsigned long long *value);
//extern platform_info_t platform_info;

#if RTK_NAND_INTERRUPT
static wait_queue_head_t	g_irq_waitq;

//#define RTK_WAIT_EVENT wait_event_interruptible(g_host->irq_waitq,g_nfFlag==NF_WAKE_UP)
#define RTK_WAIT_EVENT wait_event_interruptible(g_irq_waitq,g_nfFlag==NF_WAKE_UP)

#define CHECK_IRQ(flag,reg,mask,value) ((g_nfFlag==flag)&&((REG_READ_U32(reg)&mask)==value))
#define CHECK_REG(reg,mask,value) (REG_READ_U32(reg)&mask==value)
//#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,(REG_READ_U32(reg)|mask)&0xfffffffe))
#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,mask))
#define NF_AUTO_TRIG_ISR	(0x08)
#define NF_DMA_ISR	(0x10)
#define NF_POLL_STATUS_ISR	(0x80)
#endif

#define RETRY_COUNT	(0x20)

#define rtd_inl(offset)     (*(volatile unsigned long *)(offset))
//#define rtd_outl(offset,val)    (*(volatile unsigned long *)(offset) = val); \
//                                asm ("sync")
#define rtd_outl(offset,val)    (*(volatile unsigned long *)(offset) = val);

#define rtd_maskl(offset, andMask, orMask) \
                rtd_outl(offset, ((rtd_inl(offset) & (andMask)) | (orMask))); 


//Add for GPIO Setting
//#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
static unsigned int g_regGPIODirBase = 0;
static unsigned int g_regGPIOOutBase = 0;
static struct rtk_nand_host *g_host;

static unsigned int g_NFWP_no = 0;
static unsigned int g_NFWP_index = 0;

static unsigned int g_NFWP_value_INV = 0;
static unsigned int g_NFWP_value_en = 0;
static unsigned int g_NFWP_value_dis = 0;
static int g_NFWP_pinType = 0;


#define NF_GPIO_OUT	(1)
#define NF_GPIO_IN	(0)
//#define NF_WP_ENABLE	(0)
//#define NF_WP_DISABLE	(1)

unsigned int g_BootcodeSize = 0;
unsigned int g_Factory_param_size = 0;
static int g_WP_en = 0;
unsigned int g_NF_pageSize = 0;
unsigned char g_isRandomize = 0;

#define NF_OOB_SIZE 512

const char *ptypes[] = {"cmdlinepart", NULL};

/* nand driver low-level functions */
static int rtk_read_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *buf);
static int rtk_read_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			u_char *data, u_char *oob_buf, u16 cp_mode, u_char *data_phy);
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *buf);
static int rtk_write_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data, const u_char *oob_buf, int isBBT,const u_char *data_phy);
static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page);

/* Global Variables */
struct mtd_info *rtk_mtd;
//static DECLARE_MUTEX (sem);


static int page_size, oob_size, ppb;
static int RBA_PERCENT = 5;
static char is_NF_CP_Enable_read = 0;
static char is_NF_CP_Enable_write = 0;

static unsigned int u32CP_mode = 0;
static unsigned int cpSel = 0;
static char u8regKey0[4];
static char u8regKey1[4];
static char u8regKey2[4];
static char u8regKey3[4];
static unsigned int *regKey0;
static unsigned int *regKey1;
static unsigned int *regKey2;
static unsigned int *regKey3;

static struct rw_semaphore rw_sem;
//DECLARE_MUTEX (sem_NF_CARDREADER);
//DEFINE_SEMAPHORE (sem_NF_CARDREADER);
//EXPORT_SYMBOL(sem_NF_CARDREADER);

#if RTK_ARD_ALGORITHM //Variable declartion
	#define TOTAL_BLK_NUM	8192
	const unsigned int g_RecBlkStart = 64;
	const unsigned int g_RecBlkEnd   = 7389;

	const unsigned int g_PorcWindowSize = 64;
	const unsigned int g_ReadCntThrshld = 0x200000;
	//const unsigned int g_ReadCntThrshld = 0x400000;

	const unsigned int g_MaxMinDist = 8192;
	const unsigned int g_DistInc = 1;

	const unsigned int g_WinTrigThrshld = 8192;
	static unsigned int g_WinTrigCnt = 0;

	static unsigned int g_RecArray[8192]={0};

	static unsigned int g_u32WinStart = 0;
	static unsigned int g_u32WinEnd = 0;

	int whichBlk= 0;
	int pagePerBlk = 0;

#endif
struct rtk_nand_host {
	struct mtd_info		    mtd;
	struct nand_chip	    nand;
	struct mtd_partition	*parts;
	struct device		    *dev;

	void    *spare0;
	void    *main_area0;
	void    *main_area1;

	void __iomem    *base;
	void __iomem    *regs;

	int	    status_request;
	struct clk  *clk;
	int	    clk_act;
	int	    irq;

	wait_queue_head_t	irq_waitq;

	uint8_t	    *data_buf;
	unsigned int    buf_start;
	int			    spare_len;
};

void syncPageRead(void)
{
    //CP15DMB;
    //REG32(0x1801a020) = 0x0;
    //REG_WRITE_U32(0x1801a020, 0x0);
    //CP15DMB;

    dmb(sy);
    //writel(0x0, sb2_base+0x20);
    //REG_WRITE_U32( sb2_base+0x20, 0x0);
    dmb(sy);
}

//------------------------------------------------------------------------------
void rtk_nand_hexdump( const char * str, unsigned char * pcBuf, unsigned int length )
{
	unsigned int i, j, rows, count;
	printk(KERN_ERR "======================================================\n");
	printk(KERN_ERR "%s(base=0x%08x)\n", str, (unsigned int)(pcBuf));
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		printk(KERN_ERR "%03x :", i<<4 );
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			printk(KERN_ERR " %02x",  *pcBuf );
			count++;
			pcBuf++;
		}
		printk(KERN_ERR "\n");
	}
}

//----------------------------------------------------------------------------
int getCPStatus(void)
{
	return is_NF_CP_Enable_read;
}
//----------------------------------------------------------------------------

void setCPfunc(int isEnable)
{
	if(isEnable)
		is_NF_CP_Enable_read = 1;
	else
		is_NF_CP_Enable_read = 0;
}


//----------------------------------------------------------------------------
void setAudioIOBit(int index, int value) {

	if (index > 3) return;
	rtd_maskl(0xb8000980, ~(1 << (index+ 12)), (value != 0) << (index+ 12));
}
//----------------------------------------------------------------------------

void setGPIOBit(unsigned int nGPIOBase, unsigned int nGPIOnum, unsigned int uBit)
{
        unsigned int whichReg = 0;
        unsigned int whichBit = 0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
        whichBit = nGPIOnum%32;
        //if(uBit)
                //REG_WRITE_U32(whichReg,SETBIT(REG_READ_U32(whichReg),whichBit));
        //else
                //REG_WRITE_U32(whichReg,CLEARBIT(REG_READ_U32(whichReg),whichBit));
}
//----------------------------------------------------------------------------
unsigned int getGPIOBit(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        unsigned int whichReg = 0;
        unsigned int whichBit = 0;
        unsigned int ret=0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
        whichBit = nGPIOnum%32;
        ret = REG_READ_U32(whichReg);
        ret>>=whichBit;
        ret&=(0x1);
        return ret;
}
//----------------------------------------------------------------------------

unsigned int getGPIORegVal(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        unsigned int whichReg = 0;
//        unsigned int whichBit = 0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
		//printk("\tgetRegister 0x%x\n",whichReg);
        return REG_READ_U32(whichReg);
}

 //----------------------------------------------------------------------------

 //----------------------------------------------------------------------------
 int is_jupiter_cpu(void)
 {
	 return 0;
 }
 //----------------------------------------------------------------------------
 int is_saturn_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_darwin_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 
 int is_macarthur_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_nike_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_venus_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_neptune_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_mars_cpu(void)
 {
	 return 0;
 }
 
 //----------------------------------------------------------------------------
 int is_macarthur2_cpu(void)
 {
	 return 1;
 }
 
 //----------------------------------------------------------------------------
 


#if RTK_ARD_ALGORITHM //function declartion
//----------------------------------------------------------------------------
void RTK_ARD_DumpProcWin(int nStartBlk, int nSize)
{
	int i=0;
	unsigned int nSysStartBlk = g_RecBlkStart;
	for(i=0;i<nSize;i++)
	{
		if(nStartBlk<=g_RecBlkEnd)
		{
			printk("[%u] %u \n",nStartBlk,g_RecArray[nStartBlk]);
			nStartBlk++;
		}
		else
		{
			printk("[%u] %u \n",nSysStartBlk,g_RecArray[nSysStartBlk]);
			nSysStartBlk++;
		}
	}
}
//----------------------------------------------------------------------------
void slideProcWindowPtr(void)
{
	int tmp=0;
	g_u32WinStart = g_u32WinEnd;
	if(((g_u32WinEnd+g_PorcWindowSize-1)>g_RecBlkEnd))//reverse
	{
		tmp =  g_RecBlkEnd - g_u32WinEnd+1;
		g_u32WinEnd = g_RecBlkStart + (g_PorcWindowSize - tmp)-1;
	}
	else
	{
		g_u32WinEnd+=(g_PorcWindowSize-1);
	}
}
//----------------------------------------------------------------------------
void resetBlock(int nBlkNo)
{
	static unsigned int tmpCnt = 0;
//Reser block....TBD...
////////////////////////////
	tmpCnt++;

printk("\n");
printk("\t[AT]Reset block [%u] : %u\n",nBlkNo,g_RecArray[nBlkNo]);
printk("\t[AT]Total reset %u blocks\n",tmpCnt);
	g_RecArray[nBlkNo]=0;

}
//----------------------------------------------------------------------------
void travelProcWindow(void)//When WinTrigCnt > WinTrigThrshld
{
	int maxVal[2];
	int minVal[2];
	int i=0;
	int idx=g_u32WinStart;

	if(g_RecArray[g_u32WinEnd] > g_RecArray[g_u32WinStart])
	{
		minVal[0]=g_u32WinStart;
		minVal[1]=g_RecArray[g_u32WinStart];
		maxVal[0]=g_u32WinEnd;
		maxVal[1]=g_RecArray[g_u32WinEnd];
	}
	else
	{
		maxVal[0]=g_u32WinStart;
		maxVal[1]=g_RecArray[g_u32WinStart];
		minVal[0]=g_u32WinEnd;
		minVal[1]=g_RecArray[g_u32WinEnd];
	}

	printk("++++Before Travel++++\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);
	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	for(i=0;i<g_PorcWindowSize;i++)
	{
		if(g_RecArray[idx]>=g_ReadCntThrshld)
			resetBlock(idx);
		if(idx<=g_RecBlkEnd)
		{
			if(g_RecArray[idx]<minVal[1])//Process minimun value
			{
				minVal[0]=idx;
				minVal[1]=g_RecArray[idx];
			}
			if(g_RecArray[idx]>maxVal[1])//Process maximun value
			{
				maxVal[0]=idx;
				maxVal[1]=g_RecArray[idx];
			}
			if(idx==g_RecBlkEnd)
				idx = g_RecBlkStart;
			else
				idx++;
		}

	}
	printk("----After Travel w/o Grouping ----\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);

	//Grouping
	g_RecArray[minVal[0]] += g_DistInc;
	if((maxVal[1]-minVal[1]) < g_MaxMinDist)
	{
		g_RecArray[maxVal[0]] += g_MaxMinDist;
	}

	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	slideProcWindowPtr();
	g_WinTrigCnt = 0; //Reset windows trigger count
}
#endif
//----------------------------------------------------------------------------

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
 char *rtkNF_parse_token(const char *parsed_string, const char *token)
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
				if(ret_str)
				{
					strncpy(ret_str, value_start, value_end-value_start);
					ret_str[value_end-value_start] = '\0';
				}
				return ret_str;
			} else {
				if(ret_str)
				{
					ret_str = kmalloc(1, GFP_KERNEL);
					strcpy(ret_str, "");
				}
				return ret_str;
			}
		}
	}

	return (char*)NULL;
}

//----------------------------------------------------------------------------
unsigned int rtkNF_getWPSettingval(void)
{
    unsigned char *param;
	unsigned int retWPval = 0 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"WP_PIN_EN");

    if(param)
		retWPval = simple_strtoul(param, (char**)&retWPval, 16);
	else
		retWPval = 0;
    return retWPval;
}
//----------------------------------------------------------------------------
unsigned char* rtkNF_getBootType(void)
{
    unsigned char *param;
	unsigned int retBootcodeSize = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"boot_flash");

     return param;
}
//----------------------------------------------------------------------------
unsigned int rtkNF_getBootcodeSize(void)
{
    unsigned char *param;
	unsigned int retBootcodeSize = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"nand_boot_size");

    if(param)
		retBootcodeSize = simple_strtoul(param, (char**)&retBootcodeSize, 16);
    return retBootcodeSize;
}
//----------------------------------------------------------------------------
unsigned int rtkNF_getFactParaSize(void)
{
    unsigned char *param;
	unsigned int retFactParaSize = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"factory_size");

    if(param)
		retFactParaSize = simple_strtoul(param, (char**)&retFactParaSize, 16);
    return retFactParaSize;
}

//----------------------------------------------------------------------------
unsigned int rtkNF_getRBAPercent(void)
{
    unsigned char *param;
	unsigned int retRbaPercent = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"rba_percent");

    if(param)
		retRbaPercent = simple_strtoul(param, (char**)&retRbaPercent, 16);
    return retRbaPercent;
}

//----------------------------------------------------------------------------
unsigned int rtkNF_getSW_WP_level(void)
{
    unsigned char *param;
	unsigned int retSWwplevel = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"sw_wp");

    if(param)
		retSWwplevel = simple_strtoul(param, (char**)&retSWwplevel, 16);
    return retSWwplevel;
}

//----------------------------------------------------------------------------


void WAIT_DONE(u64 addr, u64 mask, unsigned int value)
{
	while ( (REG_READ_U32(addr) & mask) != value )
	{
		asm("nop");
		smp_wmb();
	}
}
//----------------------------------------------------------------------------

void rtk_nand_reset(void)
{

    down_write(&rw_sem);
	REG_WRITE_U32( REG_ND_CMD+map_base,CMD_RESET );

	REG_WRITE_U32( REG_ND_CTL+map_base,0x80 );

	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);

    up_write(&rw_sem);
}
EXPORT_SYMBOL(rtk_nand_reset);

static void rtk_nand_resumeReg(void)
{

	
	//padlock(PAD_NAND);   // lock nand・s pad
	
	if(is_darwin_cpu())
	{
		printk("darwin resume detect...\n");
		//REG_WRITE_U32(0xb8000118,CLEARBIT(REG_READ_U32(0xb8000118),2));
		//REG_WRITE_U32(0xb8000108,CLEARBIT(REG_READ_U32(0xb8000108),2));
		//REG_WRITE_U32(0xb8000108,SETBIT(REG_READ_U32(0xb8000108),2));
		//REG_WRITE_U32(0xb8000118,SETBIT(REG_READ_U32(0xb8000118),2));
	}
	
	REG_WRITE_U32( 0xb801032c,0x01);	//Enable NAND/CardReader arbitrator
	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(0xb800000c)& (~0x00800000));
	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
		REG_WRITE_U32( REG_NF_CKSEL+map_base,0x04 );
	else if(is_saturn_cpu()||is_darwin_cpu())
		REG_WRITE_U32( (0xb8000038),0x02 );
	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(REG_CLOCK_ENABLE1)| (0x00800000));

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,0x7<<26);
	else
		REG_WRITE_U32(REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1) | NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0)); //set spare2ddr func. 4=>0.5k spe2ddr_ena at A000F000

	REG_WRITE_U32( REG_PD+map_base,~(0x1 << 0) );
	REG_WRITE_U32( REG_ND_CMD+map_base,CMD_RESET );

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
		REG_WRITE_U32( REG_ND_CTL+map_base,(0x80 | 0x00));
	else
		REG_WRITE_U32( REG_ND_CTL+map_base,(NF_ND_CTL_xfer(0x01) | NF_ND_CTL_tran_mode(0)) );

	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);

	REG_WRITE_U32( REG_TIME_PARA1+map_base,NF_TIME_PARA1_T1(0x1));
	REG_WRITE_U32( REG_TIME_PARA2+map_base,NF_TIME_PARA2_T2(0x1));
	REG_WRITE_U32( REG_TIME_PARA3+map_base,NF_TIME_PARA3_T3(0x1));

	if(!is_jupiter_cpu()||!is_saturn_cpu()||!is_darwin_cpu()||!is_macarthur_cpu()||!is_nike_cpu()||!is_macarthur2_cpu())
		REG_WRITE_U32( REG_DELAY_CTL+map_base,NF_DELAY_CTL_T_WHR_ADL(0x09) );

	REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(0x01));
	REG_WRITE_U32( REG_ECC_STOP+map_base,NF_ECC_STOP_ecc_n_stop(0x01));
	
	//padunlock(PAD_NAND);   // unlock nand・s pad
	

}
//----------------------------------------------------------------------------

/*
 * RTK NAND suspend:
 */
static void rtk_nand_suspend (struct mtd_info *mtd)
{
	printk(KERN_INFO "suspend - NF_LOW_PWR:0x%08x, NF_SWC_LOW_PWR:0x%08x\n",REG_READ_U32(REG_NF_LOW_PWR),REG_READ_U32(REG_NF_LOW_PWR));
	rtk_nand_reset();
}
//----------------------------------------------------------------------------
static void rtk_nand_resume (struct mtd_info *mtd)
{
	printk(KERN_INFO "resume 0 - NF_LOW_PWR:0x%08x, NF_SWC_LOW_PWR:0x%08x\n",REG_READ_U32(REG_NF_LOW_PWR),REG_READ_U32(REG_NF_LOW_PWR));
	REG_WRITE_U32(REG_NF_LOW_PWR+map_base, REG_READ_U32(REG_NF_LOW_PWR+map_base)&~0x10);
	REG_WRITE_U32(REG_NF_SWC_LOW_PWR+map_base, REG_READ_U32(REG_NF_SWC_LOW_PWR+map_base)&~0x10);
	printk(KERN_INFO "resume 1 - NF_LOW_PWR:0x%08x, NF_SWC_LOW_PWR:0x%08x\n",REG_READ_U32(REG_NF_LOW_PWR),REG_READ_U32(REG_NF_LOW_PWR));
}
//----------------------------------------------------------------------------
static void rtk_read_oob_from_SRAM(struct mtd_info *mtd, __u8 *r_oobbuf)
{
	unsigned int reg_oob, reg_num;
	int i;
	unsigned int sram_base_addr; 

	sram_base_addr = REG_NF_BASE_ADDR+map_base;
	
	//printk("mtd->ecctype 0x%x\n",mtd->ecctype);
//	if ( mtd->ecctype == MTD_ECC_NONE )
	//if ( mtd->ecctype == MTD_ECC_NONE ||(mtd->ecctype!=MTD_ECC_RTK_HW))
	if (1)
	{
		reg_num = sram_base_addr;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[0] = reg_oob & 0xff;
		r_oobbuf[1] = (reg_oob >> 8) & 0xff;
		r_oobbuf[2] = (reg_oob >> 16) & 0xff;
		r_oobbuf[3] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+4;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[4] = reg_oob & 0xff;

		reg_num = sram_base_addr+16;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[5] = reg_oob & 0xff;
		r_oobbuf[6] = (reg_oob >> 8) & 0xff;
		r_oobbuf[7] = (reg_oob >> 16) & 0xff;
		r_oobbuf[8] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+16*2;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[9] = reg_oob & 0xff;
		r_oobbuf[10] = (reg_oob >> 8) & 0xff;
		r_oobbuf[11] = (reg_oob >> 16) & 0xff;
		r_oobbuf[12] = (reg_oob >> 24) & 0xff;

		reg_num = sram_base_addr+16*3;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[13] = reg_oob & 0xff;
		r_oobbuf[14] = (reg_oob >> 8) & 0xff;
		r_oobbuf[15] = (reg_oob >> 16) & 0xff;
		r_oobbuf[16] = (reg_oob >> 24) & 0xff;

	}
	else
	{
		for ( i=0; i < 16; i++)
			{
				reg_num = sram_base_addr + i*4;
				reg_oob = REG_READ_U32(reg_num);
				r_oobbuf[i*4+0] = reg_oob & 0xff;
				r_oobbuf[i*4+1] = (reg_oob >> 8) & 0xff;
				r_oobbuf[i*4+2] = (reg_oob >> 16) & 0xff;
				r_oobbuf[i*4+3] = (reg_oob >> 24) & 0xff;
			}
	}
}

//----------------------------------------------------------------------------
static int rtk_nand_read_ecc_status(u_char id[6])
{
	int id_chain;
	int i;
	//padlock(PAD_NAND);   // lock nand・s pad
	
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0x06) );
	REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(0x01));

	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0x0));
	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));

	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(0x7A));

#ifdef XFER_MODE
	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(0x01));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
#endif
	REG_WRITE_U32(REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(0));
	REG_WRITE_U32(REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x07));


#ifdef XFER_MODE

	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(1));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
#else
    REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)| NF_AUTO_TRIG_auto_case(1));
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
#endif

	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(4));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);

	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_reset(1));

	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(1)|NF_SRAM_CTL_mem_region(0));
	
	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;
	for(i=0;i<3;i++)
	{
		if((id[i]&0xF)==0xF)
			return -1;
			
	}
	REG_WRITE_U32(REG_SRAM_CTL+map_base,0x0);	//# no omitted

	//padunlock(PAD_NAND);   // unlock nand・s pad
	return 0;
}

static void rtk_nand_read_id(struct mtd_info *mtd, u_char id[6])
{
	#define XFER_MODE
	int id_chain;
	printk("rtk_nand_read_id \n");
	//Set SRAM path and access mode
#ifdef XFER_MODE
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0x06));
	REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(0x01));

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0x0));

	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_READ_ID));
	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(0x01));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);

	//Set address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0);
	REG_WRITE_U32(REG_ND_PA1+map_base, 0);
	REG_WRITE_U32(REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x07));

	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(1));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	//Enable XFER mode
	REG_WRITE_U32(REG_ND_CTL+map_base,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(4));
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_reset(1));

	//Move data to DRAM from SRAM
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(1)|NF_SRAM_CTL_mem_region(0));

	id_chain = REG_READ_U32(REG_ND_PA0+map_base);
        g_id_chain = id_chain;
	printk("id_chain 1 = 0x%x \n", id_chain);
	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;

	//g_id_chain = id_chain;
	//if(id_chain==0xDA94D7AD)
	//{
	//	printk("Detect H27UBG8T2B and enable read-retrial mode...\n");
	//	g_enReadRetrial = 1;
	//	g_isRandomize = 1;
	//	printk("Enable Read-retrial mode...\n");
	//	printk("Enable Randomized mechanism\n");
	//}
	if(g_id_chain == 0x4b44642c)
	{
		printk("Detect MT29F64G08CBABA and enable read-retrial mode\n");
		g_enReadRetrial = 1;
	}else if(g_id_chain == 0x4b44442c)
	{
		printk("Detect MT29F32G08CBADA and enable read-retrial mode\n");
		g_enReadRetrial = 1;
	}else if(g_id_chain == 0x9384d798){
		printk("Detect TC58TEG5DCJT and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }else if(g_id_chain == 0x9384de98){
		printk("Detect TC58TEG6DCJT and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }else if(g_id_chain == 0x9394de98){
		printk("Detect TC58TEG6DDK and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }



	id_chain = REG_READ_U32(REG_ND_PA1+map_base);
	printk("id_chain 2 = 0x%x \n", id_chain);
	id[4] = id_chain & 0xff;
	id[5] = (id_chain >> 8) & 0xff;

	REG_WRITE_U32(REG_SRAM_CTL+map_base,0x0);	//# no omitted
#else
	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_reset(0x01));
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0x00));
	REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(0x01)|NF_DATA_TL1_length1(0x2));

	//Set page length at auto mode 
	REG_WRITE_U32(REG_PAGE_LEN+map_base, 0x1);
	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0x1));

	REG_WRITE_U32(REG_PP_CTL0+map_base,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_READ_ID));

	//Set address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0);
	REG_WRITE_U32(REG_ND_PA1+map_base, 0);
	REG_WRITE_U32(REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x07));
	
	//Set ECC	
	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base, NF_MULTI_CHNL_MODE_ecc_no_check(0) | NF_MULTI_CHNL_MODE_ecc_pass(0));	//Set HW no check ECC	
	REG_WRITE_U32(REG_ECC_STOP+map_base, NF_ECC_STOP_ecc_n_stop(0x1));	//Set ECC no stop
	//Set DMA	
	REG_WRITE_U32(REG_DMA_CTL1+map_base, id);	//Set DRAM start address
	REG_WRITE_U32(REG_DMA_CTL2+map_base, 0x1);	//Transfer length (Unit = 512B)	
	REG_WRITE_U32(REG_DMA_CTL3+map_base, NF_DMA_CTL3_ddr_wr(1) | NF_DMA_CTL3_dma_xfer(1));	//Set DMA direction and enable DMA transfer 
	//Enable Auto mode
	REG_WRITE_U32(REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)| NF_AUTO_TRIG_auto_case(0));
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
	//Enable Auto mode
	REG_WRITE_U32(REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(4));
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
	//Wait DMA done	
	WAIT_DONE(REG_DMA_CTL3+map_base, 0x01, 0x00);	
#endif
}
//----------------------------------------------------------------------------
#if 1
static void reverse_to_Tags(char *r_oobbuf, int eccBits)
{
	int k,j;

	if(is_jupiter_cpu())
	{
		for ( k=0; k<4; k++ )
				r_oobbuf[5+k] = r_oobbuf[8+k];

			memcpy(&r_oobbuf[9],&r_oobbuf[16],4);//add by alexchang for improve nand read 0225-2010
			memcpy(&r_oobbuf[13],&r_oobbuf[24],4);//add by alexchang for improve nand read 0225-2010
	}

	else
	{

		if(eccBits==0)
		{
	    for ( k=0; k<4; k++ )
			r_oobbuf[5+k] = r_oobbuf[8+k];

		memcpy(&r_oobbuf[9],&r_oobbuf[16],4);//add by alexchang for improve nand read 0225-2010
		memcpy(&r_oobbuf[13],&r_oobbuf[24],4);//add by alexchang for improve nand read 0225-2010
		}
		else if(eccBits==0x18)
		{
			for(k=0,j=1;k<28;k+=4,j++)
				memcpy(&r_oobbuf[1+k],&r_oobbuf[8*j],4);
		}
	}
}
#endif
//----------------------------------------------------------------------------
static int rtk_Process_Buf(unsigned char* oob_buf)
{
	int j=0,k=0;
	unsigned int reg_oob, reg_num;

	REG_WRITE_U32(REG_READ_BY_PP+map_base,0x00);
	REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x30 | 0x04);

	for ( j=0; j < 12; j++)
	{
		reg_num = map_base + j*4;
		reg_oob = REG_READ_U32(reg_num);
		oob_buf[j*4+0] = reg_oob & 0xff;
		oob_buf[j*4+1] = (reg_oob >> 8) & 0xff;
		if(j==11)
			break;
		oob_buf[j*4+2] = (reg_oob >> 16) & 0xff;
		oob_buf[j*4+3] = (reg_oob >> 24) & 0xff;
	}

	for ( j=16,k=0; j < 28; j++,k++)
	{
		reg_num = map_base + j*4;
		reg_oob = REG_READ_U32(reg_num);
		oob_buf[46+k*4+0] = reg_oob & 0xff;
		oob_buf[46+k*4+1] = (reg_oob >> 8) & 0xff;
		if(j==27)
			break;
		oob_buf[46+k*4+2] = (reg_oob >> 16) & 0xff;
		oob_buf[46+k*4+3] = (reg_oob >> 24) & 0xff;
	}

	REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x00);
	REG_WRITE_U32(REG_READ_BY_PP+map_base,0x80);
	return 0;
}
//----------------------------------------------------------------------------

static int rtk_read_regTrigger(int isCPdisable,int page_size,int triggerMode)
{
#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
	if(is_NF_CP_Enable_read&&(!isCPdisable))
	{
		REG_WRITE_U32(REG_CP_NF_KEY+map_base,*regKey0);
		REG_WRITE_U32((REG_CP_NF_KEY+map_base+0x4),*regKey1);
		REG_WRITE_U32((REG_CP_NF_KEY+map_base+0x8),*regKey2);
		REG_WRITE_U32((REG_CP_NF_KEY+map_base+0xc),*regKey3);

		REG_WRITE_U32(REG_CP_NF_SET+map_base,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN+map_base,NF_CP_LEN_cp_length(page_size));
		REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
	}
	else
		REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(triggerMode));

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
	WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
#endif
	if(is_NF_CP_Enable_read&&(!isCPdisable))//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET+map_base,0);
	}
	return 0;
}


//----------------------------------------------------------------------------
static int rtk_read_ecc_page_withLargeECC (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf)
{

	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;
	int r_unit = 2048;
	int i=0,cnt=0;
//	unsigned int reg_oob, reg_num;
	unsigned char *ptr_oob;
	unsigned int  *ptr_data;

	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;

	ptr_oob = kmalloc(128,GFP_KERNEL);
	ptr_data = kmalloc(2048,GFP_KERNEL);
//printk("ptr_oob 0x%x\n",ptr_oob);
//printk("ptr_data 0x%x\n",ptr_data);

	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;
	cnt = page_size/r_unit;
    if(page_size%r_unit)
    {
		printk("[%s]ERROR page_size not alignment...\n",__FUNCTION__);
		return -1;
    }

	page_size = 2048;

	REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1) );
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));

	if(this->ecc_select == 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
	}
	REG_WRITE_U32(REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(1));
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));
	REG_WRITE_U32(REG_PP_CTL0+map_base,0);

 	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
 		REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
	else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
		REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
	else
		REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_READ_C1));
	REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_READ_C2));
	REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_READ_C3));

	REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP+map_base,NF_ECC_STOP_ecc_n_stop(0x01));

	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));

	dram_sa = ( (uint32_t)data_buf >> 3);
	REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));

	if (ptr_oob)
		spare_dram_sa = ( (uint32_t)ptr_oob >> 3);
	else
		spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);

	if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
		REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,(0x7<<26) | (spare_dram_sa&0x3ffffff));
	else
		REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	//rtk_read_regTrigger(mtd->isCPdisable_R, page_size,auto_trigger_mode);

	rtk_Process_Buf(oob_buf);
	for(;i<cnt-1;i++)
	{
		data_buf+=2048;
		oob_buf+=92;
		dram_sa = ( (uint32_t)data_buf >> 3);

		if (ptr_oob)
				spare_dram_sa = ( (uint32_t)ptr_oob >> 3);
			else
				spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);

			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
				REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,(0x7<<26) | (spare_dram_sa&0x3ffffff));
			else
				REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
		REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
		//rtk_read_regTrigger(mtd->isCPdisable_R, page_size,0x04);
		rtk_Process_Buf(oob_buf);
	}

	if(ptr_oob)
	{
		kfree(ptr_oob);
		ptr_oob=NULL;
	}
	if(ptr_data)
	{
		kfree(ptr_data);
		ptr_data=NULL;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK+map_base)>>1) & 0x01;

	//mtd->nEccMaxValue = REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM));
	if (blank_all_one)
	{
		if(this->erase_page_flag)
			this->erase_page_flag[chip_section+section] =  (1<< index);
	}

	if (REG_READ_U32(REG_ND_ECC+map_base) & 0x0C){
		if(!this->erase_page_flag)
		{
			if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
				if ( chipnr == 0 && (page < (g_BootcodeSize/page_size)) )
				{
					return 0;
				}
				else
				{
					return -1;
				}
			}
		}
		else
		{
			if (this->erase_page_flag[chip_section+section] & (1<< index) ){
				;
			}else
			{
				if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
					if ( chipnr == 0 && (page < (g_BootcodeSize/page_size)) )
					{
						return 0;
					}
					else
					{
						return -1;
					}
				}
			}
		}
	}
#if RTK_ARD_ALGORITHM
	g_WinTrigCnt++;
	whichBlk = page / ppb;
	g_RecArray[whichBlk]++;
	if(g_WinTrigCnt > g_WinTrigThrshld)
		travelProcWindow();
#endif
	//mtd->isCPdisable_R = 0;
	return rc;
}


//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_terminate_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0xff));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_pre_condition_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0x5C));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0xC5));	//Set CMD2
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done


}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_ext_feature_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0x26));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0x5d));	//Set CMD2
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done


}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_feature_toshiba(int P1){

        int i = 0;

	printk("[%s] set slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0xf);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3+map_base,  NF_TIME_PARA3_T3(0x1));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2+map_base,  NF_TIME_PARA2_T2(0x1));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1+map_base,  NF_TIME_PARA1_T1(0x1));			//Set flash timming T1

    for(i=4;i<8;i++){
        printk("[%s] enter set REG_DATA_TL0 to 0x1, addr=0x%x\n", __FUNCTION__, i);
	//REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	//REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	//REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0x55));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

	//Set address, 
	REG_WRITE_U32(REG_ND_PA0+map_base, i);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2+map_base, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, P1);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_DATA_TL0+map_base, 0x1);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1+map_base, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL+map_base, 0xc0, 0x40);	//Wait xfer done
        }

        printk("[%s] close slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0x4);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3+map_base,  NF_TIME_PARA3_T3(0x0));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2+map_base,  NF_TIME_PARA2_T2(0x0));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1+map_base,  NF_TIME_PARA1_T1(0x0));			//Set flash timming T1
    
}	


//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_feature_toshiba_new(int P1){

        int i = 0;

	printk("[%s] set slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0xf);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3+map_base,  NF_TIME_PARA3_T3(0x1));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2+map_base,  NF_TIME_PARA2_T2(0x1));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1+map_base,  NF_TIME_PARA1_T1(0x1));			//Set flash timming T1

    for(i=4;i<9;i++){
        printk("[%s] enter set REG_DATA_TL0 to 0x1, addr=0x%x, data: 0x%x\n", __FUNCTION__, i,read_retry_toshiba_cnt_new[P1][i-4]);
	//REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	//REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	//REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0x55));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

	//Set address, 

        if(i==8)
            REG_WRITE_U32(REG_ND_PA0+map_base, 0x0d);	//Set PA[7:0]
        else
	    REG_WRITE_U32(REG_ND_PA0+map_base, i);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2+map_base, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, read_retry_toshiba_cnt_new[P1][i-4]);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_DATA_TL0+map_base, 0x1);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1+map_base, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL+map_base, 0xc0, 0x40);	//Wait xfer done
        }

        printk("[%s] close slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0x4);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3+map_base,  NF_TIME_PARA3_T3(0x0));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2+map_base,  NF_TIME_PARA2_T2(0x0));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1+map_base,  NF_TIME_PARA1_T1(0x0));			//Set flash timming T1

        if(P1==4){
        	printk("[%s] enter 4th retry send 0xb3 command\n", __FUNCTION__);

        	//Set command
        	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0xb3));	//Set CMD1
        	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
        	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done
        }
    
}	


//----------------------------------------------------------------------------
// add read-retry for Micron
void rtk_set_feature_micron(int P1){

	printk("[%s] enter \n", __FUNCTION__);
	
	REG_WRITE_U32(REG_DATA_TL0+map_base, 0x4);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1+map_base, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL1+map_base, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD+map_base, NF_ND_CMD_cmd(0xef));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done

	//Set address, 
	REG_WRITE_U32(REG_ND_PA0+map_base, 0x89);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2+map_base, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, P1);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL+map_base, 0xc0, 0x40);	//Wait xfer done
}	

//----------------------------------------------------------------------------
//Add read retrial mechanism
//static int nRun,regVal1,regVal2,regVal3,regVal4,nInc;
static void rtk_xfer_SetParameter(unsigned char val1,unsigned char val2,unsigned char val3,unsigned char val4)
{
#if RTK_NAND_INTERRUPT
    NF_RESET_IRQ;
    CLR_REG_NAND_ISR;
    g_nfFlag = NF_INIT;
#endif

	//rtk_xfer_GetParameter();
	REG_WRITE_U32(REG_DATA_TL0+map_base, 0x1);				//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1+map_base, NF_DATA_TL1_access_mode(1) | NF_DATA_TL1_sram_path(0) | NF_DATA_TL1_length1(0x0));				//Set data transfer count[13:8], SRAM path and access mode

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD+map_base, 0x36);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Transfer Reg#1 address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0xa7);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2+map_base, NF_ND_PA2_addr_mode(0x7) | NF_ND_PA2_page_addr2(0x0));				//Set address mode & PA[20:16]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP+map_base, NF_READ_BY_PP_read_by_pp(0));	//Data read to DRAM from NAND through PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, val1);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done
	//Transfer Reg#2 address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0xad);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, val2);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done


	//Transfer Reg#3 address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0xae);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, val3);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done


	//Transfer Reg#4 address
	REG_WRITE_U32(REG_ND_PA0+map_base, 0xaf);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));				//Set PP starting address[9:8], PP reset and PP enable
	//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0+map_base, val4);				//Set data
	REG_WRITE_U32(REG_SRAM_CTL+map_base,NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0+map_base, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD+map_base, 0x16);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL+map_base, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL+map_base, 0x80, 0x00);					//Wait xfer done
	//printk("Set and Get value...\n");
	//rtk_xfer_GetParameter();
//	printk("[%s]%d,%d,%d,%d\n",__FUNCTION__,val1,val2,val3,val4);
#if RTK_NAND_INTERRUPT
    NF_RESET_IRQ;
    CLR_REG_NAND_ISR;   
    g_nfFlag = NF_INIT;
#endif

}
//----------------------------------------------------------------------------
static void rtk_xfer_GetParameter(void)
{
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;
			g_nfFlag = NF_INIT;
#endif

#if 1 //Get parameter from DRAM

	//regVal1=(REG_READ_U32(0xb8007660)>>24)&0x000000ff ;
    //regVal2=(REG_READ_U32(0xb8007660)>>16)&0x000000ff ;
    //regVal3=(REG_READ_U32(0xb8007660)>>8)&0x000000ff ;
    //regVal4=REG_READ_U32(0xb8007660)&0x000000ff ;


#else

	REG_WRITE_U32(REG_DATA_TL0, 0x1);				//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(1) | NF_DATA_TL1_sram_path(0) | NF_DATA_TL1_length1(0x0));				//Set data transfer count[13:8], SRAM path and access mode

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//Data read to DRAM from NAND through PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));				//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL1, 0x0);				//Set PP starting assdress[7:0]
	//Set table sram
	//REG_WRITE_U32(NF_TABLE_CTL_reg, NF_TABLE_CTL_table_start_addr(0x0) | NF_TABLE_CTL_table_enable(0));				//Set table SRAM starting assdress ( 0 ~ A) and enable table SRAM

	//Transfer command
	REG_WRITE_U32(REG_ND_CMD, 0x37);				//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x0));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
//test hang

	//Transfer Reg#1 address
	REG_WRITE_U32(REG_ND_PA0, 0xa7);
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7) | NF_ND_PA2_page_addr2(0x0));	//Set reg#1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
//test ok
	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80,0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal1, REG_READ_U32(REG_ND_DAT));
//test err


	//Transfer Reg#2 address
	REG_WRITE_U32(REG_ND_PA0, 0xad);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal2, REG_READ_U32(REG_ND_DAT));

	//Transfer Reg#3 address
	REG_WRITE_U32(REG_ND_PA0, 0xae);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80,0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal3, REG_READ_U32(REG_ND_DAT));


	//Transfer Reg#4 address
	REG_WRITE_U32(REG_ND_PA0, 0xaf);				//Set PA[7:0]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x1));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done

	//Get data
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x2));				//Enable Xfer, eanble ECC and set transfer mode
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);					//Wait xfer done
	REG_WRITE_U32((unsigned long)&regVal4, REG_READ_U32(REG_ND_DAT));

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0)); 			//Set PP starting address[9:8], PP reset and PP enable
	#endif

//	printk("[%s]%d,%d,%d,%d\n",__FUNCTION__,regVal1,regVal2,regVal3,regVal4);
#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			CLR_REG_NAND_ISR;

			g_nfFlag = NF_INIT;
#endif

}
//----------------------------------------------------------------------------
#if 0
static void rtk_SetVal( char val1, char val2, char val3, char val4)
{
	rtk_xfer_GetParameter();
	regVal1+=val1;
	regVal2+=val2;
	regVal3+=val3;
	regVal4+=val4;
	rtk_xfer_SetParameter(regVal1,regVal2,regVal3,regVal4);
}
#endif
//----------------------------------------------------------------------------
static void rtk_SetReadRetrialMode(unsigned int run)
{

	if((regVal1==0)&&(regVal2==0)&&(regVal3==0)&&(regVal4==0))
		rtk_xfer_GetParameter();
	run%=7;

	if(run!=nRun)
		printk("\n\n$$run %d,[Run %d]\n",run,nRun);
	switch(run)
	{

	#if 1
		case 1:
			//rtk_SetVal(0x00,0x06,0x0A,0x06);
			rtk_xfer_SetParameter(regVal1,regVal2+0x06,regVal3+0x0A,regVal4+0x06);

		break;

		case 2:
			//rtk_SetVal(0xff,-0x03,-0x07,-0x08);
			rtk_xfer_SetParameter(0x00,regVal2-0x03,regVal3-0x07,regVal4-0x08);

		break;

		case 3:
			//rtk_SetVal(0xff,-0x06,-0x0D,-0x0F);
			rtk_xfer_SetParameter(0x00,regVal2-0x06,regVal3-0x0D,regVal4-0x0F);

		break;

		case 4:
			//rtk_SetVal(0xff,-0x09,-0x14,-0x17);
			rtk_xfer_SetParameter(0x00,regVal2-0x09,regVal3-0x14,regVal4-0x17);
		break;

		case 5:
			//rtk_SetVal(0xff,0xff,-0x1A,-0x1E);
			rtk_xfer_SetParameter(0x00,0x00,regVal3-0x1A,regVal4-0x1E);

		break;

		case 6:

			//rtk_SetVal(0xff,0xff,-0x20,-0x25);
			rtk_xfer_SetParameter(0x00,0x00,regVal3-0x20,regVal4-0x25);

		break;
#endif
		default:
			//rtk_xfer_SetParameter(regVal1,regVal2,regVal3,regVal4);
		break;
	}
}
//----------------------------------------------------------------------------
static int rtk_read_ecc_page_reTrial (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf)
{

	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;

	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);
	#if RTK_NAND_INTERRUPT
		NF_RESET_IRQ;
		NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
		g_nfFlag = NF_READ_TRIGGER;
#endif
	nInc=0;
	while(nInc<7)
	{


		rtk_SetReadRetrialMode(nInc+nRun);

		this = (struct nand_chip *) mtd->priv;
		page_size = mtd->writesize;
		oob_size = mtd->oobsize;
		ppb = mtd->erasesize/mtd->writesize;

		//if ( chipnr == 0 && page < (((g_BootcodeSize+g_Factory_param_size)/page_size)+ppb))
		//{
			//mtd->isCPdisable_R = 1;
			//mtd->isScramble=MTD_SCRAMBLE_DISABLE;
		//}
		//else
			//mtd->isScramble=1;

		//if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
		if(this->ecc_select==0x18||this->ecc_select==0x0c)
		{
			if(!oob_buf)
			{
				rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,this->g_oobbuf);
			}
			else
				rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,data_buf,oob_buf);
			if(rc==0)
			{
				nRun+=nInc;
				nRun%=7;
				return rc;
			}
			else
			{
				nInc++;
				rc=-1;
				continue;
			}
		}

;

		//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
		REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1) );
		REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));

		if(this->ecc_select == 0x18)
		{
			page_len = page_size >> 10;
			REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
		}
		else
		{
			page_len = page_size >> 9;
			REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		REG_WRITE_U32(REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

		REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0+map_base,0);

	 	if ( this->ecc_select == 0xc)//add by alexchang 0319-2010. setting for 12bits ecc.
	 		REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(1));
		else if( this->ecc_select == 0x18)//add by alexchang 0617-2011. setting for 24bits ecc.
			REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(1)|NF_ECC_SEL_ecc_bch_12b_ena(0));
		else
			REG_WRITE_U32(REG_ECC_SEL+map_base,NF_ECC_SEL_ecc_bch_24b_ena(0)|NF_ECC_SEL_ecc_bch_12b_ena(0));

		REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_READ_C1));
		REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_READ_C2));
		REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_READ_C3));

		REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page));
		REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8));
		REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
		REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>>21)&0x7));
		REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
		REG_WRITE_U32( REG_ECC_STOP+map_base,NF_ECC_STOP_ecc_n_stop(0x01));

		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));

		dram_sa = ( (uint32_t)data_buf >> 3);

		REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));

		if (oob_buf)
			spare_dram_sa = ( (uint32_t)oob_buf >> 3);
		else
			spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);

		if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
			REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,(0x7<<26) | (spare_dram_sa&0x3ffffff));
		else
			REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1)|NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));


#if RTK_NAND_INTERRUPT
		NF_RESET_IRQ;
		NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
		g_nfFlag = NF_READ_TRIGGER;
#endif
		//printk("Retry[%s]Ran 0x%x, scr 0x%x, flag 0x%x\n",__FUNCTION__,g_isRandomize,mtd->isScramble,mtd->isCPdisable_R);
		//printk("R blk:%u, page:%u\n",page/ppb,page%ppb);

		//if((g_isRandomize&&(!mtd->isCPdisable_R))||(mtd->isScramble!=MTD_SCRAMBLE_DISABLE))
		if((g_isRandomize))
		{
			//printk("Ran 0x%x\n",g_isRandomize);
			//printk("isCPdisable_R 0x%x\n",mtd->isCPdisable_R);
			//printk("isScramble 0x%x\n",mtd->isScramble);
	                //printk("page 0x%x\n",page);
			//printk("@");
			if(u32CP_mode==0)//CBC initial key setting.
			{
				REG_WRITE_U32( REG_CP_NF_INI_KEY+map_base,page);
			}
			REG_WRITE_U32(REG_CP_NF_KEY+map_base,0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+map_base+0x4),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+map_base+0x8),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+map_base+0xc),0x12345678);

			REG_WRITE_U32(REG_CP_NF_SET+map_base,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN+map_base,NF_CP_LEN_cp_length(page_size));
			#if 1
			dma_map_single(NULL, data_buf, page_size,  DMA_FROM_DEVICE);
			
			if ( oob_buf )
				dma_map_single(NULL, oob_buf, oob_size,  DMA_FROM_DEVICE);
			else
				dma_map_single(NULL, this->g_oobbuf, oob_size,  DMA_FROM_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			else
				RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
			#endif	
			REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{

			//if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
			if(is_NF_CP_Enable_read)
			{
				//printk("X");
				REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
				REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
				REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
				REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

				REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
				REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
				
				#if 1
				dma_map_single(NULL, data_buf, page_size,  DMA_FROM_DEVICE);
				
				if ( oob_buf )
					dma_map_single(NULL, oob_buf, oob_size,  DMA_FROM_DEVICE);
				else
					dma_map_single(NULL, oob_buf, this->g_oobbuf, DMA_FROM_DEVICE);
				#else
				RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
				if ( oob_buf )
					RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
				else
					RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
				#endif
				REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
			}
			else
			{//printk("/");
				
				#if 1
				dma_map_single(NULL, data_buf, page_size,  DMA_FROM_DEVICE);
				
				if ( oob_buf )
					dma_map_single(NULL, oob_buf, oob_size,  DMA_FROM_DEVICE);
				else
					dma_map_single(NULL, this->g_oobbuf, oob_size,  DMA_FROM_DEVICE);
				#else
				RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
				if ( oob_buf )
					RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
				else
					RTK_FLUSH_CACHE((unsigned long) this->g_oobbuf, oob_size);
				#endif
				REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
			}
		}

		REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
		RTK_WAIT_EVENT;
#else
		WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
		WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
#endif
	dma_unmap_single(NULL, virt_to_phys(data_buf), page_size, DMA_FROM_DEVICE);
	if ( oob_buf )
			dma_unmap_single(NULL, virt_to_phys(oob_buf), oob_size, DMA_FROM_DEVICE);
	else
			dma_unmap_single(NULL, virt_to_phys( this->g_oobbuf), oob_size,  DMA_FROM_DEVICE);
		//remove by Aaron==>if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
		//remove by Aaron==>{
			//remove by Aaron==>REG_WRITE_U32(REG_CP_NF_SET,0);
		//remove by Aaron==>}

		if(oob_buf)
		{
			if(this->ecc_select==0x18||this->ecc_select==0x0c)
				reverse_to_Tags(oob_buf,this->ecc_select);
			else
			{
				REG_WRITE_U32(REG_READ_BY_PP+map_base,0x00);
				if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
					REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x30 | 0x02);
				else
					REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x30 | 0x04);
				rtk_read_oob_from_SRAM(mtd, oob_buf);
				REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x00);
				REG_WRITE_U32(REG_READ_BY_PP+map_base,0x80);
			}
		}

		chip_section = (chipnr * this->page_num) >> 5;
		section = page >> 5;
		index = page & (32-1);
		blank_all_one = (REG_READ_U32(REG_BLANK_CHK+map_base)>>1) & 0x01;


		// add by alexchang 01-28-2011
		//mtd->nEccMaxValue = REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM));
		if (blank_all_one)
		{
			if(this->erase_page_flag)
			this->erase_page_flag[chip_section+section] =  (1<< index);
		}

		if (REG_READ_U32(REG_ND_ECC+map_base) & 0x0C){
					if(!this->erase_page_flag)
					{
						if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
							if ( chipnr == 0 && page < g_BootcodeSize/page_size )
							{
								nRun+=nInc;
								nRun%=7;
							    return 0;
							}
							else
							{
								//printk("0[%s]nInc %d,nRun %d\n",__FUNCTION__,nInc,nRun);
								nInc++;
								rc=-1;
								printk("!!!Read Fail page NO. 0x%x\n",page);
								continue;
							}
						}
					}
					else
					{
						if (this->erase_page_flag[chip_section+section] & (1<< index) ){
							;
						}else
						{
							if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
								if ( chipnr == 0 && page < g_BootcodeSize/page_size )
								{
									nRun+=nInc;
									nRun%=7;
									return 0;
								}
								else
								{
									//printk("1[%s]nInc %d,nRun %d\n",__FUNCTION__,nInc,nRun);
									nInc++;
									rc=-1;
									printk("!!!Read Fail page NO. 0x%x\n",page);
									continue;
								}
							}
						}
					}
				}

#if RTK_ARD_ALGORITHM
		whichBlk = page / ppb;
		g_RecArray[whichBlk]++;
		if(g_WinTrigCnt > g_WinTrigThrshld)
			travelProcWindow();
#endif
		//mtd->isCPdisable_R = 0;
		rc=0;
		break;

	}
	//printk("return rc %d\n",rc);
	nRun+=nInc;
	nRun%=7;

	return rc;
}


//----------------------------------------------------------------------------


static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page)
{
	struct nand_chip *this = NULL;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int retryCnt = RETRY_COUNT;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;
//printk("erasesize 0x%x,writesize 0x%x\n",mtd->erasesize,mtd->writesize);
//printk("AT[%s]:show chipnr %d\n",__FUNCTION__,chipnr);
	//padlock(PAD_NAND);   // lock nand・s pad
	
	down_write(&rw_sem);
	//while (down_interruptible (&sem_NF_CARDREADER)) {
		//printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
	//	if(retryCnt<=0)
	//	{
	//		retryCnt = RETRY_COUNT;
	//		printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
			
			//padunlock(PAD_NAND);   // unlock nand・s pad
			
	//		return -ERESTARTSYS;
	//	}
	//	retryCnt--;
	//}
	this = (struct nand_chip *) mtd->priv;
//	printk("AT[%s]:page %d, ppb %d, mtd->erasesize %u, mtd->writesize %u\n",__FUNCTION__,page,ppb,mtd->erasesize,mtd->writesize);
	if ( page & (ppb-1) ){
		printk("%s: page %d is not block alignment !!\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -1;
	}

	//if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())//Disable NF_WP pin (Write Protect Pin)
	//{
	//	if(g_WP_en)
	//	{
	//		switch(g_NFWP_pinType)
	//		{
	//			case PCB_PIN_TYPE_AUDIO:
	//				setAudioIOBit(g_NFWP_no, g_NFWP_value_dis);
	//			break;
	//			case PCB_PIN_TYPE_GPIO:
	//			default:
	//				setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
	//				setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_dis);//Set Value
	//			break;
	//		}
     //       REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3));
      //      REG_WRITE_U32( REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(0x07)|NF_POLL_FSTS_trig_poll(1));
	//		WAIT_DONE(REG_POLL_FSTS,0x1,0);
	//	}
	//}

#if RTK_NAND_INTERRUPT
	g_nfFlag = NF_ERASE_TRIGGER;
	NF_RESET_IRQ;
#endif

	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	//REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_no_wait_busy(1)|NF_MULTI_CHNL_MODE_edo(1));
	REG_WRITE_U32( REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_no_wait_busy(1)|NF_MULTI_CHNL_MODE_edo(1));


	REG_WRITE_U32( REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_BLK_ERASE_C1) );
	REG_WRITE_U32( REG_CMD2+map_base,NF_CMD2_cmd2(CMD_BLK_ERASE_C2) );
	REG_WRITE_U32( REG_CMD3+map_base,NF_CMD3_cmd3(CMD_BLK_ERASE_C3) );

	REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(0x04)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>> 21)&0x7) );

	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)|NF_AUTO_TRIG_auto_case(2) );
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_ERASE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_IRQ_MASK);
#else
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	//REG_WRITE_U32(REG_POLL_FSTS+map_base,0xd );
	WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0);
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);//add by alexchang 0416-2010
#endif

	//if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())//Enable NF_WP pin (Write Protect Pin)
	//{
	//	if(g_WP_en)
	//	{
	//		switch(g_NFWP_pinType)
	//		{
	//			case PCB_PIN_TYPE_AUDIO:
	//				setAudioIOBit(g_NFWP_no, g_NFWP_value_en);
	//			break;
	//			case PCB_PIN_TYPE_GPIO:
	//			default:
	//				setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
	//				setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_en);//Set Value
	//			break;
	//		}
	//	}
	//}

	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		printk("[%s] QQ erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
		if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size ){
            printk("[%s] return 0 %d\n", __FUNCTION__, page/ppb);
			return 0;
            }else{
            printk("[%s] return -1 %d\n", __FUNCTION__, page/ppb);
			return -1;
            }
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	if(this->erase_page_flag)
		memset ( (__u32 *)(this->erase_page_flag)+ chip_section + section, 0xff, ppb>>3);
	//printk("[AT]Erase block : %u  \n",page/ppb);
	//up (&sem_NF_CARDREADER);
	up_write(&rw_sem);
	//padunlock(PAD_NAND);   // unlock nand・s pad
#if RTK_ARD_ALGORITHM
	g_RecArray[page/ppb]=0;
//	printk("[AT]Erase block : %u  \n",page/ppb);
#endif

	
	return 0;
}
//----------------------------------------------------------------------------
unsigned char *malloc_aligned(size_t size,int alignment)
{
   unsigned char *ptr = kmalloc(size + alignment-1,GFP_KERNEL);
   if (!ptr) return NULL;
   ptr = (unsigned char *)(((unsigned int)(ptr) + alignment-1) & ~alignment);
   return ptr;
}
//----------------------------------------------------------------------------

static int rtk_read_oob (struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *oob_buf)
{	
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one=0;
	int page_len;
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	uint8_t auto_trigger_mode = 2;
	uint8_t addr_mode = 1;
	uint8_t	bChkAllOne = 0;
	
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;
	//padlock(PAD_NAND);   // lock nand・s pad
	printk("[%s]line: %d\n",__FUNCTION__,__LINE__);

	down_write(&rw_sem);
	//while (down_interruptible (&sem_NF_CARDREADER)) {
		//printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
	//	if(retryCnt<=0)
	//	{
	//		retryCnt = RETRY_COUNT;
	//		printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
			//padunlock(PAD_NAND);   // unlock nand・s pad
	//		return -ERESTARTSYS;
	//	}
	//	retryCnt--;
	//}
	//if(g_enReadRetrial)
	//{
	//	if(!oob_buf)
	//	{
	//		rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,this->g_oobbuf);
	//	}
	//	else
	//		rc = rtk_read_ecc_page_reTrial(mtd,chipnr,page,this->g_databuf,oob_buf);
	//	up(&sem_NF_CARDREADER);
	//	//padunlock(PAD_NAND);   // unlock nand・s pad
	//	return rc;
	//}

	if ( len>oob_size || !oob_buf ){
		printk("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -1;
	}
	//if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
		//mtd->isCPdisable_R = 1;
	#if 1
	//dma_map_single(NULL,this->g_databuf, page_size,  DMA_FROM_DEVICE);
	//if ( oob_buf )
		//dma_map_single(NULL,oob_buf, oob_size,  DMA_FROM_DEVICE);
	#else
	RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
	if ( oob_buf )
		RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
	#endif
	//if((mtd->ecctype==MTD_ECC_RTK_HW)&&(this->ecc_select==0x18||this->ecc_select==0x0c))
	//if(this->ecc_select==0x18||this->ecc_select==0x0c)
	//{
	//	rc = rtk_read_ecc_page_withLargeECC(mtd,chipnr,page,this->g_databuf,oob_buf);
	//	up(&sem_NF_CARDREADER);
	//	//padunlock(PAD_NAND);   // unlock nand・s pad
	//	return rc;
	//}
	while (1)
	{
		REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));
		if(this->ecc_select >= 0x18)
		{
			if (bChkAllOne) {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 0);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_read_ecc_xnor_ena(1));
			}
			else {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 1);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_read_ecc_xnor_ena(0));
			}
			page_len = page_size >> 10;
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
			REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		
		REG_WRITE_U32(REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

		//Set PP
		REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0+map_base,0);

		// enable blank check
		REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1) );

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

		switch(this->ecc_select) {
			case 6:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
				break;
			case 12:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x1);
				break;
			case 16:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0xe);
				break;
			case 24:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0xa);
				break;
			case 40:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x2);
				break;
			case 43:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x4);
				break;
			case 65:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x6);
				break;
			case 72:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x8);
				break;
			default:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
				break;
		}

		dram_sa = ( (uint32_t)this->g_databuf >> 3);
		REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));
		REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));

		spare_dram_sa = ( (uint32_t)oob_buf >> 3);
		REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(0)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

		#if RTK_NAND_INTERRUPT
			NF_RESET_IRQ;
			NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
			g_nfFlag = NF_READ_TRIGGER;
		#endif

		REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
		WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
		
		#if RTK_NAND_INTERRUPT
			RTK_WAIT_EVENT;
		#else
			WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
			WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
		#endif
		
		//dma_unmap_single(NULL, virt_to_phys(this->g_databuf), page_size, DMA_FROM_DEVICE);
		//if ( oob_buf )
			//dma_unmap_single(NULL, virt_to_phys(oob_buf), oob_size, DMA_FROM_DEVICE);

		if(oob_buf)	{
			//REG_WRITE_U32(REG_READ_BY_PP+map_base,0x00);
			//REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x30 | 0x04);
			//rtk_read_oob_from_SRAM(mtd, oob_buf);
			//REG_WRITE_U32(REG_SRAM_CTL+map_base, 0x00);
			//REG_WRITE_U32(REG_READ_BY_PP+map_base,0x80);
		}
		
		// return OK if all data bit is 1 (page is not written yet)
		if (REG_READ_U32(REG_BLANK_CHK+map_base) & 0x2){
			//printk("[%s] page(0x%x) data all one\n", __FUNCTION__, page);
			//up (&sem_NF_CARDREADER);
			up_write(&rw_sem);
			return 0;
		}
		else if (REG_READ_U32(REG_ND_ECC+map_base) & 0x8) {
			if (!bChkAllOne && this->ecc_select>=0x18) {
				bChkAllOne = 1;
				continue;
			}
			printk("[%s] page(0x%x) ecc error\n", __FUNCTION__, page);
			//up (&sem_NF_CARDREADER);
			up_write(&rw_sem);
			return -1;	// ECC not correctable
		}
		else {
			//printk("[%s] page(0x%x) oob= 0x%x\n", __FUNCTION__, page, *oob_buf);
			//up (&sem_NF_CARDREADER);
			up_write(&rw_sem);
			return 0;
		}
	}
#if 0	
#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
	g_nfFlag = NF_READ_TRIGGER;
#endif
	if(g_isRandomize&&(!mtd->isCPdisable_R))
	{
		if(u32CP_mode==0)//CBC initial key setting.
        {
                REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
        }
		REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
		REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);

		REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
		REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
		
		#if 1
		dma_map_single(NULL, this->g_databuf, page_size,  DMA_FROM_DEVICE);
		if ( oob_buf )
			dma_map_single(NULL, oob_buf, oob_size,  DMA_FROM_DEVICE);
		#else
		RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
		if ( oob_buf )
			RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
		#endif
		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));

	}
	else
	{
		if(is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))
		{
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);

			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			
			#if 1
			dma_map_single(NULL, this->g_databuf, page_size,  DMA_FROM_DEVICE);
			if ( oob_buf )
				dma_map_single(NULL,oob_buf, oob_size,  DMA_FROM_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0x1)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			#if 1
			dma_map_single(NULL,this->g_databuf, page_size,  DMA_FROM_DEVICE);
			if ( oob_buf )
				dma_map_single(NULL,oob_buf, oob_size,  DMA_FROM_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
		}
	}
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
	//WAIT_DONE(REG_AUTO_TRIG,0x80,0);

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
#endif
	dma_unmap_single(NULL, virt_to_phys(this->g_databuf), page_size, DMA_FROM_DEVICE);
	if ( oob_buf )
		dma_unmap_single(NULL, virt_to_phys(oob_buf), oob_size, DMA_FROM_DEVICE);

	if((is_NF_CP_Enable_read&&(!mtd->isCPdisable_R))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}

	if(oob_buf)
	{
		if(this->ecc_select==0x18||this->ecc_select==0xc||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
			reverse_to_Tags(oob_buf,this->ecc_select);
		else
		{
			if( ! is_jupiter_cpu() )
			{
				REG_WRITE_U32(REG_READ_BY_PP,0x00);
				if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x02);
				else
					REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
				rtk_read_oob_from_SRAM(mtd, oob_buf);
				REG_WRITE_U32(REG_SRAM_CTL, 0x00);
				REG_WRITE_U32(REG_READ_BY_PP,0x80);
			}
			if(is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
				reverse_to_Tags(oob_buf,this->ecc_select);
		}
	}
//oobReadCnt++;
//printk("\t oob read cnt %u\n",oobReadCnt);
	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	blank_all_one = (REG_READ_U32(REG_BLANK_CHK+map_base)>>1) & 0x01;
	if (blank_all_one)
	{
		if(this->erase_page_flag)
		this->erase_page_flag[chip_section+section] =  (1<< index);
	}

	if (REG_READ_U32(REG_ND_ECC+map_base) & 0x0C){
				if(!this->erase_page_flag)
				{
					if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
						if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
						{
							up (&sem_NF_CARDREADER);
							//padunlock(PAD_NAND);   // unlock nand・s pad
							return 0;
						}
						else
						{
							up (&sem_NF_CARDREADER);
							//padunlock(PAD_NAND);   // unlock nand・s pad
							printk("[%s]blk %d, page %d fail\n",__FUNCTION__,page/ppb,page%ppb);
							return -1;
						}
					}
				}
				else
				{
					if (this->erase_page_flag[chip_section+section] & (1<< index) ){
						;
					}else
					{
						if (REG_READ_U32(REG_ND_ECC+map_base) & 0x08){
							if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
							{
								up (&sem_NF_CARDREADER);
								//padunlock(PAD_NAND);   // unlock nand・s pad
								return 0;
							}
							else
							{
								up (&sem_NF_CARDREADER);
								printk("[%s]blk %d, page %d fail\n",__FUNCTION__,page/ppb,page%ppb);
								//padunlock(PAD_NAND);   // unlock nand・s pad
								return -1;
							}
						}
					}
				}
			}
#endif	
	//mtd->isCPdisable_R = 0;
	//up (&sem_NF_CARDREADER);
	up_write(&rw_sem);
	//padunlock(PAD_NAND);   // unlock nand・s pad
	
	return rc;
}
//----------------------------------------------------------------------------
static int rtk_read_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf, u16 cp_mode, u_char *data_phy)
{
    //NF_DEBUG_PRINT("rtk_read_ecc_page chipnr:[%d] page:[%d]\n", chipnr, page);
//static unsigned int eccReadCnt = 0;
	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int blank_all_one = 0;
	int page_len;
	uint8_t eccStatus[6];
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	uint8_t	bChkAllOne = 0;
	int ret;
	uint8_t read_retry_cnt = 0;
	uint8_t max_read_retry_cnt = 0;
	int j=0;
    	volatile unsigned int data;
    	unsigned int eccNum = 0;
    	extern dma_addr_t nrPhys_addr;
    	extern dma_addr_t oobPhys_addr;

	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;

    syncPageRead();

	down_write(&rw_sem);

    if(((uint32_t)data_buf&0x7)!=0) {
        NF_DEBUG_PRINT("[%s]data_buf must 8 byte alignmemt!!\n", __FUNCTION__);
        BUG();
    }

	while (1) 
	{
		//REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(512));
		if(this->ecc_select >= 0x18)
		{
			if (bChkAllOne) {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 0);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(1));
                //printk("[DBG]ecc error, set xnor and blank to 1, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
			}
			else {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL+map_base, 1);
				REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
                // printk("[DBG]set xnor to 0, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
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

        if(cp_mode == CP_NF_AES_ECB_128 || cp_mode==CP_NF_AES_CBC_128){
			//REG_WRITE_U32(CP_NF_INI_KEY_0,0x8746bca3);
			//REG_WRITE_U32(CP_NF_INI_KEY_1,0xcdef89ab);
			//REG_WRITE_U32(CP_NF_INI_KEY_2,0x54369923);
			//REG_WRITE_U32(CP_NF_INI_KEY_3,0xcdefbcab);

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
                REG_WRITE_U32(CP_NF_SET+map_base, 0x200);				// sel=0, cw_entry=0, bcm=1, aes_mode=0. Its ECB mode.
            else
                REG_WRITE_U32(CP_NF_SET+map_base, 0x0);				// sel=0, cw_entry=0, bcm=0, aes_mode=0. Its CBC mode.

            REG_WRITE_U32(REG_CP_LEN+map_base, (page_size / 0x200) << 9);		// integer multiple of dma_len.

            //syncPageRead();
            //printk("[DBG]set cp mode...............REG_READ_U32(REG_CP_LEN): 0x%x\n", REG_READ_U32(REG_CP_LEN));
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

		switch(this->ecc_select) {
			case 6:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
				break;
			case 12:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x1);
				break;
			case 16:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0xe);
				break;
			case 24:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0xa);
				break;
			case 40:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x2);
				break;
			case 43:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x4);
				break;
			case 65:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x6);
				break;
			case 72:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x8);
				break;
			default:
				REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
				break;
		}

        spare_dram_sa = ( (uint32_t)oobPhys_addr >> 3);
		REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,0x60000000 |NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

        dram_sa = ( (uint32_t)data_phy >> 3);
		REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));

        if(cp_mode == CP_NF_AES_ECB_128||cp_mode==CP_NF_AES_CBC_128){
            REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_cp_enable(1)|NF_DMA_CTL3_cp_first(1)|NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
        }else{
            REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
        }

		smp_wmb();
	
#if RTK_NAND_INTERRUPT
        NF_RESET_IRQ;
        NF_ENABLE_IRQ(NF_DMA_IRQ_MASK);
        g_nfFlag = NF_READ_TRIGGER;
#endif
        syncPageRead();

		//Enable Auto mode
		REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
		RTK_WAIT_EVENT;
#else
		WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
		WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
#endif

		if(1) {
            data = (REG_READ_U32(REG_SPR_DDR_CTL+map_base) & 0x1fffffff) << 3;	// physical address
            NF_DEBUG_PRINT("data==> 0x%x\n",data);
            NF_DEBUG_PRINT("oob_buf[0]==> 0x%x, page=0x%x\n",this->g_oobbuf[0],page);    
		}

		// return OK if all data bit is 1 (page is not written yet)
		if ((REG_READ_U32(REG_BLANK_CHK+map_base) & 0x8)==0){
			//NF_DEBUG_PRINT("data all one, page:%u \n", page);
			//up (&sem_NF_CARDREADER);
			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return 1;
		}
		else if (REG_READ_U32(REG_ND_ECC+map_base) & 0x8) {
			NF_DEBUG_PRINT("[DBG][%s] page(0x%x) ecc error,  REG_BLANK_CHK reg: 0x%x\n", __FUNCTION__, page, REG_READ_U32(REG_BLANK_CHK+map_base));
			//up (&sem_NF_CARDREADER);
			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return -1;	// ECC not correctable
		}
		else {
            		//NF_DEBUG_PRINT("PK test page:%u  [0x%x]\n", page, REG_READ_U32(REG_ND_ECC+map_base));
            		if (REG_READ_U32(REG_ND_ECC+map_base) & 0x04){
                		eccNum = REG_READ_U32(REG_RSECC_NUM+map_base) & 0xff;
                		NF_DEBUG_PRINT("[NAND_DBG][%s]:%d, ecc_num:%d, page:%u\n", __FUNCTION__,__LINE__, eccNum, page);
                		if(eccNum > 4){
                    			NF_ERR_PRINT("[NAND_DBG][%s]:%d, ecc_num:%d, page:%u\n", __FUNCTION__,__LINE__, eccNum, page);
                    			REG_WRITE_U32(REG_BLANK_CHK+map_base, NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
                    			up_write(&rw_sem);
                    			return -2;
                		}
            		}

			//up (&sem_NF_CARDREADER);
			REG_WRITE_U32(REG_BLANK_CHK+map_base,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			up_write(&rw_sem);
			return 0;
		}
	}
}

//----------------------------------------------------------------------------
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *oob_buf)
{	
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;
	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	unsigned char oob_1stB;
	unsigned int chip_section = 0;
	unsigned int section =0;
	unsigned int index =0;
	unsigned int retryCnt = RETRY_COUNT;
	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	memset(this->g_databuf, 0xff, page_size);

	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;
	//padlock(PAD_NAND);   // lock nand・s pad
	printk("[%s]line: %d\n",__FUNCTION__,__LINE__);

	down_write(&rw_sem);
	//while (down_interruptible (&sem_NF_CARDREADER)) {
		//printk("%s : Retry [Address: 0x%x]\n",__FUNCTION__,page);
	//		if(retryCnt<=0)
	//		{
	//			retryCnt = RETRY_COUNT;
	//			printk("%s : Retry fail [ADDR 0x%x]\n",__FUNCTION__,page);
				//padunlock(PAD_NAND);   // unlock nand・s pad
	//			return -ERESTARTSYS;
	//		}
	//		retryCnt--;
	//}
	if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size ){
		printk("[%s] You have no permission to write this page %d\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -2;
	}

	if ( len>oob_size || !oob_buf ){
		printk("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -1;
	}
#if 0
	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_dis);
				break;
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_dis);//Set Value
				break;
			}
            REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3));
            REG_WRITE_U32( REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(0x07)|NF_POLL_FSTS_trig_poll(1));
            WAIT_DONE(REG_POLL_FSTS,0x1,0);
		}
	}
#endif	
	#if 1
		dma_map_single(&mtd->dev,this->g_databuf, page_size, DMA_TO_DEVICE);
		if ( oob_buf ) 
		    dma_map_single(&mtd->dev,oob_buf, oob_size, DMA_TO_DEVICE);
#else
	RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
	if ( oob_buf ) 
		RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
#endif
	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Factory_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;
	else
		oob_1stB = 0xFF;
//end of alexchang 0208-2010
	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32(REG_SRAM_CTL+map_base,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));
 	if(this->ecc_select >= 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1+map_base,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32(REG_READ_BY_PP+map_base,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1+map_base,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0+map_base,0);//add by alexchang 0208-2010

	REG_WRITE_U32( REG_PAGE_LEN+map_base,NF_PAGE_LEN_page_len(page_len));

 	REG_WRITE_U32(REG_ND_CMD+map_base,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2+map_base,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3+map_base,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	REG_WRITE_U32( REG_ND_PA0+map_base,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1+map_base,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2+map_base,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3+map_base,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010

	switch(this->ecc_select) {
		case 6:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
			break;
		case 12:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x1);
			break;
		case 16:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0xe);
			break;
		case 24:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0xa);
			break;
		case 40:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x2);
			break;
		case 43:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x4);
			break;
		case 65:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x6);
			break;
		case 72:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x8);
			break;
		default:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
			break;
	}

	dram_sa = ( (uint32_t)this->g_databuf >> 3);
	REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));	
	REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));

	spare_dram_sa = ( (uint32_t)oob_buf >> 3);
	REG_WRITE_U32( REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_AUTO_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
#endif
#if 0
	if(g_isRandomize&&(!mtd->isCPdisable_W))
	{
		if(mtd->isScramble!=MTD_SCRAMBLE_DISABLE)
		{
			//printk("&");
			if(u32CP_mode==0)//CBC initial key setting.
			{
					REG_WRITE_U32( REG_CP_NF_INI_KEY,page);
			}
			REG_WRITE_U32(REG_CP_NF_KEY,0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),0x12345678);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),0x12345678);


			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			//add by alexchang 0208-2010
			
			#if 1
			dma_map_single(NULL,this->g_databuf, page_size, DMA_TO_DEVICE);
			if ( oob_buf )
			dma_map_single(NULL, oob_buf, oob_size, DMA_TO_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{
			//printk("%");
			#if 1
			dma_map_single(NULL,this->g_databuf, page_size, DMA_TO_DEVICE);
			if ( oob_buf )
			dma_map_single(NULL,oob_buf, oob_size, DMA_TO_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}
	else
	{
		if(is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))
		{//printk("#");
			REG_WRITE_U32(REG_CP_NF_KEY,*regKey0);
			REG_WRITE_U32((REG_CP_NF_KEY+0x4),*regKey1);
			REG_WRITE_U32((REG_CP_NF_KEY+0x8),*regKey2);
			REG_WRITE_U32((REG_CP_NF_KEY+0xc),*regKey3);


			REG_WRITE_U32(REG_CP_NF_SET,u32CP_mode|cpSel);
			REG_WRITE_U32(REG_CP_LEN,NF_CP_LEN_cp_length(page_size));
			//add by alexchang 0208-2010
			#if 1
			dma_map_single(NULL,this->g_databuf, page_size, DMA_TO_DEVICE);
			if ( oob_buf )
			dma_map_single(NULL,oob_buf, oob_size, DMA_TO_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0x1)|NF_DMA_CTL3_cp_first(0x1)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
		else
		{//printk("@");
			//add by alexchang 0208-2010
			#if 1
			dma_map_single(NULL,this->g_databuf, page_size, DMA_TO_DEVICE);
			if ( oob_buf )
			dma_map_single(NULL,oob_buf, oob_size, DMA_TO_DEVICE);
			#else
			RTK_FLUSH_CACHE((unsigned long) this->g_databuf, page_size);
			if ( oob_buf )
				RTK_FLUSH_CACHE((unsigned long) oob_buf, oob_size);
			#endif
			REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(0)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(0x1));
		}
	}
#endif
	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
	WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0);
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);//add by alexchang 0416-2010
#endif

			dma_unmap_single(NULL, virt_to_phys(this->g_databuf), page_size, DMA_TO_DEVICE);
			if ( oob_buf )
			dma_unmap_single(NULL, virt_to_phys(oob_buf), oob_size, DMA_TO_DEVICE);
#if 0
	if(is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())//Enable NF_WP pin (Write Protect Pin)
	{
		if(g_WP_en)
		{
			switch(g_NFWP_pinType)
			{
				case PCB_PIN_TYPE_AUDIO:
					setAudioIOBit(g_NFWP_no, g_NFWP_value_en);
				break;
				case PCB_PIN_TYPE_GPIO:
				default:
					setGPIOBit(g_regGPIODirBase,g_NFWP_no,NF_GPIO_OUT);//Set Driection
					setGPIOBit(g_regGPIOOutBase,g_NFWP_no,g_NFWP_value_en);//Set Value
				break;
			}
		}
	}

	if((is_NF_CP_Enable_write&&(!mtd->isCPdisable_W))||g_isRandomize)//Clear register
	{
		REG_WRITE_U32(REG_CP_NF_SET,0);
	}
#endif
	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		printk("[%s] write oob is not completed at page %d\n", __FUNCTION__, page);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);
	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	//mtd->isCPdisable_W = 0;
	//printk("[AT]WO block : %u ,page : %d  \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);
	up_write(&rw_sem);
	//padunlock(PAD_NAND);   // unlock nand・s pad
//int k= 0;
//for(k=0;k<32;k++)
//printk("[WO][%u,%u][%d]0x%x\n",page/ppb,page%ppb,k,oob_buf[k]);
//printk("----------------------------\n");
	
	return rc;
}

//----------------------------------------------------------------------------
//char bbbbb[4096];

static int rtk_write_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data_buf, const  u_char *oob_buf, int isBBT,const u_char *data_phy)
{	
	unsigned int ppb = mtd->erasesize/mtd->writesize;
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;

	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	unsigned char oob_1stB,oob_2ndB=0;

	unsigned char nf_oob_buf[oob_size];
	unsigned int chip_section = 0;
	unsigned int section = 0;
	unsigned int index = 0;
	unsigned int retryCnt = RETRY_COUNT;
	//padlock(PAD_NAND);   // lock nand・s pad
        extern dma_addr_t nwPhys_addr;
        extern dma_addr_t oobPhys_addr;
	//printk("00[%s]Ran 0x%x, scr 0x%x, flag 0x%x\n",__FUNCTION__,g_isRandomize,mtd->isScramble,mtd->isCPdisable_W);
        int j=0;
        syncPageRead();

	down_write(&rw_sem);

        if(((uint32_t)data_buf&0x7)!=0)
        {
                printk("[%s]data_buf must 8 byte alignmemt!!\n",__FUNCTION__);
                BUG();
        }
        if(((uint32_t)oob_buf&0x7)!=0)
        {
                printk("[%s]oob_buf must 8 byte alignmemt!!\n",__FUNCTION__);
                BUG();
        }
#if 1
	//dma_map_single(NULL,data_buf, page_size, DMA_TO_DEVICE);
	//if (oob_buf) {
		//dma_map_single(NULL,oob_buf, oob_size, DMA_TO_DEVICE);
	//}
#else
RTK_FLUSH_CACHE((unsigned long) data_buf, page_size);
#endif

	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Factory_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;
	else
		oob_1stB = 0xFF;

	if (oob_buf)
	{
		pr_debug("[LY] write customer oob : 0x%02x 0x%02x 0x%02x 0x%02x\n", *(unsigned char*)(((unsigned char*)oob_buf)+0), *(unsigned char*)(((unsigned char*)oob_buf)+1), *(unsigned char*)(((unsigned char*)oob_buf)+2), *(unsigned char*)(((unsigned char*)oob_buf)+3));

		if ((*(unsigned char*)(((unsigned char*)oob_buf)+2) == 0xbe) && (*(unsigned char*)(((unsigned char*)oob_buf)+3) == 0xef))
		{
			oob_1stB = *(unsigned char*)(((unsigned char*)oob_buf)+0);
			oob_2ndB = *(unsigned char*)(((unsigned char*)oob_buf)+1);
			pr_debug("[LY] write oob data 1 : 0x%02x 0x%02x\n", oob_1stB, oob_2ndB);
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

	if (oob_buf)
	{
	  if ((*(unsigned char*)(((unsigned char*)oob_buf)+2) == 0xbe) && (*(unsigned char*)(((unsigned char*)oob_buf)+3) == 0xef))
	  {  
		pr_debug("[LY] write oob data 2 : 0x%02x 0x%02x\n", oob_1stB, oob_2ndB);
		this->g_oobbuf[0x1] = oob_2ndB;
		this->g_oobbuf[0x11] = oob_2ndB;
		this->g_oobbuf[0x21] = oob_2ndB;
		this->g_oobbuf[0x31] = oob_2ndB;
	  }
	}
#if 1
//dma_map_single(NULL,this->g_oobbuf, oob_size, DMA_TO_DEVICE);
#else
	RTK_FLUSH_CACHE((unsigned long) nf_oob_buf, oob_size);	
#endif
	
	//REG_WRITE_U32(REG_SRAM_CTL,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0+map_base,NF_DATA_TL0_length0(0));
 	if(this->ecc_select >= 0x18)
	{
		// enable randomizer
		REG_WRITE_U32(REG_RMZ_CTRL+map_base, 1);

	//REG32(REG_RMZ_SEED_L) = 0x6e;
	//REG32(REG_RMZ_SEED_H) = 0xa3;

                REG_WRITE_U32(REG_RMZ_SEED_H+map_base, ((page+1) & 0xff00)>>8);
                REG_WRITE_U32(REG_RMZ_SEED_L+map_base, (page+1) & 0xff);

                //printk("page: 0x%x, H+1: 0x%x, L+1: 0x%x\n", page,((page+1) & 0xff00)>>8, (page+1) & 0xff );
    
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

	switch(this->ecc_select) {
		case 6:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
			break;
		case 12:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x1);
			break;
		case 16:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0xe);
			break;
		case 24:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0xa);
			break;
		case 40:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x2);
			break;
		case 43:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x4);
			break;
		case 65:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x6);
			break;
		case 72:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x8);
			break;
		default:
			REG_WRITE_U32(REG_ECC_SEL+map_base, 0x0);
			break;
	}

	//dram_sa = ( (uint32_t)nwPhys_addr >> 3);
	dram_sa = ( (uint32_t)data_phy >> 3);
	REG_WRITE_U32(REG_DMA_CTL1+map_base,NF_DMA_CTL1_dram_sa(dram_sa));
	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2+map_base,NF_DMA_CTL2_dma_len(dma_len));	
	//REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(1));
	
	//if (oob_buf)
	//	spare_dram_sa = ( (uint32_t)nf_oob_buf >> 3);
	//else
		//spare_dram_sa = ( (uint32_t)this->g_oobbuf >> 3);
		spare_dram_sa = ( (uint32_t)oobPhys_addr >> 3);
	//REG_WRITE_U32(REG_SPR_DDR_CTL+map_base,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_SPR_DDR_CTL+map_base,0x60000000|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_DMA_CTL3+map_base,NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(1));
    
#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_AUTO_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
#endif

        syncPageRead();

	REG_WRITE_U32( REG_AUTO_TRIG+map_base,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
	smp_wmb();

#if RTK_NAND_INTERRUPT
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_WRITE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
#else
	WAIT_DONE(REG_AUTO_TRIG+map_base,0x80,0);
	WAIT_DONE(REG_DMA_CTL3+map_base,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS+map_base,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS+map_base,0x01,0x0);
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);//add by alexchang 0416-2010
#endif

               // for(j=0;j<100;j++){
                   // printk("[%s]line: %d, data_buf[%d]: 0x%x\n",__FUNCTION__,__LINE__,j,data_buf[j]);
                   // }
               // for(j=0;j<64;j++){
                    //printk("[%s]line: %d, this->g_oobbuf[%d]: 0x%x\n",__FUNCTION__,__LINE__,j,(uint32_t)this->g_oobbuf[j]);
                   // }
//dma_unmap_single(NULL, virt_to_phys(data_buf), page_size, DMA_TO_DEVICE);
//if (oob_buf) {
	//dma_unmap_single(NULL, virt_to_phys(oob_buf), oob_size, DMA_TO_DEVICE);
//}
//dma_unmap_single(NULL, virt_to_phys(nf_oob_buf), oob_size, DMA_TO_DEVICE);

	if ( REG_READ_U32(REG_ND_DAT+map_base) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		up_write(&rw_sem);
		printk("[%s] write is not completed at page %d\n", __FUNCTION__, page);
		//padunlock(PAD_NAND);   // unlock nand・s pad
		return -1;
	}

	chip_section = (chipnr * this->page_num) >> 5;
	section = page >> 5;
	index = page & (32-1);

	if (this->erase_page_flag)
		this->erase_page_flag[chip_section+section] &= ~(1 << index);
	//mtd->isCPdisable_W = 0;
	//printk("[AT]W block : %u , page: %u \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);
	up_write(&rw_sem);
	//padunlock(PAD_NAND);   // unlock nand・s pad
printk("[%s] write is completed at page %d\n", __FUNCTION__, page);
	
	return rc;
}

static int rtk_mtd_add_partitions(struct mtd_info *mtd, struct mtd_partitions *parts)
{
        const struct mtd_partition *real_parts = parts->parts;
        int nbparts = parts->nr_parts;
        int ret;

	NF_INIT_PRINT("%s, nbparts:[%d]\n", __FUNCTION__, nbparts);

        if (nbparts > 0) {
                ret = add_mtd_partitions(mtd, real_parts, nbparts);
		NF_INIT_PRINT("%s, ret:[%d]\n", __FUNCTION__, ret);
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
	int retRba=0;
	int rc = 0;

	memset(&mtd_parts, 0, sizeof(mtd_parts));
#if 0
#ifdef CONFIG_MTD_NAND_RTK_RBA_PERCENT
	this->RBA_PERCENT = CONFIG_MTD_NAND_RTK_RBA_PERCENT;
	printk("[Customize]RBA percentage: %d%\n",this->RBA_PERCENT);

#else
	this->RBA_PERCENT = RBA_PERCENT;
	printk("[Default]RBA percentage: %d'%'\n",this->RBA_PERCENT);
#endif
#else

#if 0
    retRba = rtkNF_getRBAPercent();
	if(retRba == -1)
	{
		//rtk_mtd->u32RBApercentage = 
        this->RBA_PERCENT = RBA_PERCENT;
		printk(KERN_INFO "[**Default**]RBA percentage: %d%\n",this->RBA_PERCENT);
	}
	else
	{
		//rtk_mtd->u32RBApercentage = this->RBA_PERCENT = retRba;
		printk(KERN_INFO "[**Customize**]RBA percentage: %d%\n",this->RBA_PERCENT);
	}
#endif
	this->RBA_PERCENT = RBA_PERCENT;
	NF_INIT_PRINT("[**Default**]RBA percentage: %d%\n",this->RBA_PERCENT);
#endif

	g_sw_WP_level = rtkNF_getSW_WP_level();
	if(g_sw_WP_level == -1) {
		NF_INIT_PRINT("Disable software write protect!\n");
	}
	else {
		NF_INIT_PRINT("Enable software write protect!\n");
	}

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

#ifdef CONFIG_MTD_CMDLINE_PARTS
	rc = parse_mtd_partitions (rtk_mtd, ptypes, &mtd_parts, 0);
	pnum = mtd_parts.nr_parts;
#else
	rc = mtd_device_parse_register(rtk_mtd, ptypes, 0, &mtd_parts, 0);
	NF_INIT_PRINT("[%s] mtd_device_parse_register rc = 0x%x\n", __FUNCTION__, rc);
#endif

#if 0
    if (add_mtd_partitions(rtk_mtd, rtk_partitions, ARRAY_SIZE(rtk_partitions))) {
        return -EIO;
    }
#endif
    	NF_INIT_PRINT("[%s] add mtd partition. pnum:[%d]\n", __FUNCTION__, pnum);

	if (pnum <= 0) {
		NF_INIT_PRINT("RTK: using the whole nand as a partitoin\n");
		if(add_mtd_device(rtk_mtd)) {
			NF_ERR_PRINT("RTK: Failed to register new nand device\n");
			return -EAGAIN;
		}
	}else{
		NF_INIT_PRINT("RTK: using dynamic nand partition\n");
		if(rtk_mtd_add_partitions(rtk_mtd, &mtd_parts)) {
			NF_ERR_PRINT("%s: Error, cannot add %s device\n", __FUNCTION__, rtk_mtd->name);
			rtk_mtd->size = 0;
			return -EAGAIN;
		}
	}

	mtd_part_parser_cleanup(&mtd_parts);

	return 0;
}

static int rtk_read_proc_nandinfo(struct seq_file *m, void *v) 
{
    struct nand_chip *this = (struct nand_chip *) rtk_mtd->priv;

	seq_printf(m, "nand_size:%llu\n", (uint64_t)this->device_size);
	seq_printf(m, "chip_size:%llu\n", (uint64_t)this->chipsize);
	seq_printf(m, "block_size:%u\n", rtk_mtd->erasesize);
	seq_printf(m, "page_size:%u\n", rtk_mtd->writesize);
	seq_printf(m, "oob_size:%u\n", rtk_mtd->oobsize);
	seq_printf(m, "ppb:%u\n", rtk_mtd->erasesize/rtk_mtd->writesize);
	seq_printf(m, "RBA:%u\n", this->RBA);
	seq_printf(m, "BBs:%u\n", this->BBs);

    return 0;
}

//----------------------------------------------------------------------------
#if 0
int rtk_read_proc_nandinfo(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
	struct nand_chip *this = (struct nand_chip *) rtk_mtd->priv;
	int wlen = 0;
	//wlen += sprintf(buf+wlen,"nand_PartNum:%s\n", rtk_mtd->PartNum);
	wlen += sprintf(buf+wlen,"nand_size:%llu\n", (uint64_t)this->device_size);
	wlen += sprintf(buf+wlen,"chip_size:%llu\n", (uint64_t)this->chipsize);
	wlen += sprintf(buf+wlen,"block_size:%u\n", rtk_mtd->erasesize);
	wlen += sprintf(buf+wlen,"page_size:%u\n", rtk_mtd->writesize);
	wlen += sprintf(buf+wlen,"oob_size:%u\n", rtk_mtd->oobsize);
	wlen += sprintf(buf+wlen,"ppb:%u\n", rtk_mtd->erasesize/rtk_mtd->writesize);
	wlen += sprintf(buf+wlen,"RBA:%u\n", this->RBA);
	wlen += sprintf(buf+wlen,"BBs:%u\n", this->BBs);
	return wlen;
}
#endif
//----------------------------------------------------------------------------
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
	//strcpy(&media_type[0], "nand");
}
//----------------------------------------------------------------------------
#if 0//!RTK_CP_DISABLE
static int rtk_set_CP_KEY(struct CP_key_info *cp_keyInfo)
{
	#if 0
	REG_WRITE_U32(cp_keyInfo->CP_INI_KEY_0,CP_NF_INI_KEY_0_reg);
	REG_WRITE_U32(cp_keyInfo->CP_INI_KEY_1,CP_NF_INI_KEY_1_reg);
	REG_WRITE_U32(cp_keyInfo->CP_INI_KEY_2,CP_NF_INI_KEY_2_reg);
	REG_WRITE_U32(cp_keyInfo->CP_INI_KEY_3,CP_NF_INI_KEY_3_reg);
	REG_WRITE_U32(cp_keyInfo->CP_KEY_0,CP_NF_KEY_0_reg);
	REG_WRITE_U32(cp_keyInfo->CP_KEY_1,CP_NF_KEY_1_reg);
	REG_WRITE_U32(cp_keyInfo->CP_KEY_2,CP_NF_KEY_2_reg);
	REG_WRITE_U32(cp_keyInfo->CP_KEY_3,CP_NF_KEY_3_reg);
	#endif
	return 0;
}
#endif
#if 1
void endian_swap(unsigned int* x)
{
	*x = (*x>>24) |((*x<<8) & 0x00FF0000) |((*x>>8) & 0x0000FF00) |(*x<<24);
}
#endif
//----------------------------------------------------------------------------
static struct platform_driver rtkNF_device = {
    .driver     = {
        .name   = DRIVER_NAME,
        .owner  = THIS_MODULE,
    },
    .remove     = __exit_p(rtk_nand_exit),
    .suspend    = rtk_nand_suspend,
    .resume     = rtk_nand_resume,
    .suspend    = NULL,
    .resume     = NULL,
};
//----------------------------------------------------------------------------
#if RTK_NAND_INTERRUPT
static irqreturn_t rtknf_irq(int irq, void *dev)
{
	//printk("++++f:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
	//Read isr handler
	//printk("&g_irq_waitq 0x%x\n",&g_irq_waitq);
	if(CHECK_IRQ(NF_READ_TRIGGER,REG_NAND_ISR,NF_DMA_ISR,NF_DMA_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_DMA_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);

		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_READ_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		return IRQ_HANDLED;
	}

	//Write isr handler
	if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_POLL_STATUS_ISR,NF_POLL_STATUS_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_POLL_STATUS_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_DMA_ISR,NF_DMA_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_DMA_ISR);
		return IRQ_HANDLED;
	}

	//Erase isr handler
	if(CHECK_IRQ(NF_ERASE_TRIGGER,REG_NAND_ISR,NF_POLL_STATUS_ISR,NF_POLL_STATUS_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_POLL_STATUS_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_ERASE_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		return IRQ_HANDLED;
	}

	if((REG_READ_U32(REG_NAND_ISR+map_base)&NF_IRQ_MASK))
	{
		if((g_nfFlag==NF_ERASE_TRIGGER)||(g_nfFlag==NF_READ_TRIGGER)||(g_nfFlag==NF_READ_TRIGGER)||(g_nfFlag=NF_WAKE_UP))
		{
			//printk("+++++f:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
			CLR_REG_NAND_ISR;
			return IRQ_HANDLED;
		}
	}
	//printk("xxxxxf:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
	 return IRQ_NONE;
}

//----------------------------------------------------------------------------
static int __init rtkNF_probe(struct platform_device *pdev)
{
	struct resource *r;
	int nf_irq,ret;
	/* Allocate memory for MTD device structure and private data */
	g_host = kzalloc(sizeof(struct rtk_nand_host), GFP_KERNEL);
	if (!g_host)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	//init_waitqueue_head(&g_host->irq_waitq);
	init_waitqueue_head(&g_irq_waitq);




	nf_irq = platform_get_irq(pdev, 0);
	ret = request_irq(nf_irq, rtknf_irq, IRQF_SHARED, DRIVER_NAME, g_host);   //rtkcr_interrupt
    if (ret)
    {
        printk(KERN_ERR "%s: cannot assign irq %d\n", DRIVER_NAME, nf_irq);
		return -1;
    }
	return 0;

}
#endif

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
}

static int rtk_nand_proc_open(struct inode *inode, struct  file *file) {
	return single_open(file, rtk_read_proc_nandinfo, NULL);
}

static const struct file_operations rtk_nand_proc_fops = {
	.owner = THIS_MODULE,
	.open = rtk_nand_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int rtk_nand_probe(struct platform_device *pdev)
{
	int rc = 0;
	struct nand_chip *this=NULL;
	bool default_state = true;
	struct device_node *rtk129x_nand_node;
	rtk129x_nand_node = pdev->dev.of_node;

	init_rwsem(&rw_sem);

	map_base = of_iomap(rtk129x_nand_node, 0);

    	rtk_nand_clk_reset_ctrl(&pdev->dev, CTL_ENABLE);

	// controller init.
	REG_WRITE_U32(REG_PD + map_base, 0x1E);
    	REG_WRITE_U32(REG_TIME_PARA3 + map_base, 0x2);
	REG_WRITE_U32(REG_TIME_PARA2 + map_base, 0x5);
	REG_WRITE_U32(REG_TIME_PARA1 + map_base, 0x2);

	//REG_WRITE_U32(REG_MULTI_CHNL_MODE, 0x20);
	REG_WRITE_U32(REG_MULTI_CHNL_MODE+map_base, 0x0);
	REG_WRITE_U32(REG_READ_BY_PP+map_base, 0x0);
	
	//REG32(REG_SPR_DDR_CTL) = 0x30000000 | (PHYS(SPARE_DMA_ADDR) >> 3);

	//REG32(REG_RMZ_SEED_L) = 0x6e;
	//REG32(REG_RMZ_SEED_H) = 0xa3;

        //REG_WRITE_U32(0x1801013c, REG_READ_U32(0x1801013c) & 0xffffffef);

	// reset nand.
	REG_WRITE_U32(REG_ND_CMD+map_base, 0xff);
	REG_WRITE_U32(REG_ND_CTL+map_base, 0x80);

	//printk("\n\n");
	//printk("0x1800011c = 0x%x \n", REG_READ_U32(0x1800011c));
	//printk("0x18000128 = 0x%x \n", REG_READ_U32(0x18000128));
	//printk("0x18000124 = 0x%x \n", REG_READ_U32(0x18000124));
	
	//printk("SYS_muxpad0:0x%x = 0x%x \n", SYS_muxpad0, REG_READ_U32(SYS_muxpad0));
	//printk("REG_PD:0x%x = 0x%x \n", REG_PD, REG_READ_U32(REG_PD));
	
	NF_INIT_PRINT("trigger... \n");
	WAIT_DONE(REG_ND_CTL+map_base,0x80,0);
	NF_INIT_PRINT("trigger xfer.\n");
	WAIT_DONE(REG_ND_CTL+map_base,0x40,0x40);
	NF_INIT_PRINT("nand ready. \n");

	//************************board_nand_init
	//printk(KERN_INFO "read_value32:0x%08x\n",read_value32);
    
	NF_DEBUG_PRINT("NF_LOW_PWR:0x%08x, map_base:0x%08x\n",REG_READ_U32(REG_NF_LOW_PWR+map_base),map_base);
#if 1
	REG_WRITE_U32(REG_NF_LOW_PWR+map_base, REG_READ_U32(REG_NF_LOW_PWR+map_base)&~0x10);
	//REG_WRITE_U32(REG_NF_SWC_LOW_PWR, REG_READ_U32(REG_NF_SWC_LOW_PWR)&~0x10);
	NF_DEBUG_PRINT("NF_LOW_PWR:0x%08x, NF_SWC_LOW_PWR:0x%08x\n",REG_READ_U32(REG_NF_LOW_PWR+map_base),REG_READ_U32(REG_NF_LOW_PWR+map_base));

	display_version();

	NF_DEBUG_PRINT("(X)Enable interrupt mechanism of NAND driver.\n");

	g_BootcodeSize = rtkNF_getBootcodeSize();
	g_Factory_param_size = rtkNF_getFactParaSize();

	g_BootcodeSize = 0;
	g_Factory_param_size = 0;

	//nRun = nInc = 0;
	NF_DEBUG_PRINT("Get parameter from register...\n");
	NF_DEBUG_PRINT("[%s]Bootcode size 0x%x\n",__FUNCTION__,g_BootcodeSize);
	NF_DEBUG_PRINT("[%s]Factory parameter size 0x%x\n",__FUNCTION__,g_Factory_param_size);

	
	NF_INIT_PRINT("[%s]Disable NFCP...\n", __FUNCTION__);
	is_NF_CP_Enable_write = is_NF_CP_Enable_read = 0;
#if 0
	// set pinmux to nand.
	//REG_WRITE_U32(SYS_muxpad0, 0x55555554);

	//REG_WRITE_U32( 0xb801032c,0x01);	//Enable NAND/CardReader arbitrator
	REG_WRITE_U32( REG_CLOCK_ENABLE1+clk_base,REG_READ_U32(REG_CLOCK_ENABLE1+clk_base)& (~0x00800000));
	
	//if (is_jupiter_cpu())
	//	REG_WRITE_U32( REG_NF_CKSEL,0x02 );
	//else if(is_saturn_cpu()||is_darwin_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
	//	REG_WRITE_U32( (0xb8000038),0x02 );
	REG_WRITE_U32( REG_NF_CKSEL+clk_base,0x04 );
	REG_WRITE_U32( REG_CLOCK_ENABLE1+clk_base,REG_READ_U32(REG_CLOCK_ENABLE1+clk_base)| (0x00800000));
 #endif
	//if ( is_jupiter_cpu()||is_macarthur_cpu()||is_nike_cpu()||is_macarthur2_cpu())
	//	REG_WRITE_U32( REG_SPR_DDR_CTL,0x7<<26);
	//else
	//	REG_WRITE_U32(REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(1) | NF_SPR_DDR_CTL_spare_ddr_ena(1) | NF_SPR_DDR_CTL_per_2k_spr_ena(1)| NF_SPR_DDR_CTL_spare_dram_sa(0)); //set spare2ddr func. 4=>0.5k spe2ddr_ena at A000F000
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
	this->read_oob 		= rtk_read_oob;
	this->write_ecc_page	= rtk_write_ecc_page;
	this->write_oob		= rtk_write_oob;
	this->erase_block 	= rtk_erase_block;
	this->suspend		= rtk_nand_suspend;
	this->resume		= rtk_nand_resume;
	this->sync		= NULL;

	if( rtk_nand_profile() < 0 ){
		rc = -1;
		goto EXIT;
	}
#if 0
	if(g_isRandomize)
	{
		printk("[%s]Randomized enabled \n ",__FUNCTION__);
		cpSel = 0;//0:register, 1:CW, 2:E-Fuse
		u32CP_mode = 0x0;//0 for CBC mode, 0x200 for ECB mode
	}
#endif
	g_NF_pageSize = page_size = rtk_mtd->writesize;
	oob_size = rtk_mtd->oobsize;
	ppb = (rtk_mtd->erasesize)/(rtk_mtd->writesize);

	NF_INIT_PRINT("[%s]Ecc bit select %u\n",__FUNCTION__,this->ecc_select);

	proc_create("nandinfo", 0, NULL, &rtk_nand_proc_fops);

EXIT:
	if (rc < 0) {
		if (rtk_mtd){
			//del_mtd_partitions (rtk_mtd);
			if (this->g_databuf)
				kfree(this->g_databuf);
			if(this->g_oobbuf)
				kfree(this->g_oobbuf);
			if (this->erase_page_flag){
				unsigned int flag_size =  (this->numchips * this->page_num) >> 3;
				unsigned int mempage_order = get_order(flag_size);
				free_pages((unsigned long)this->erase_page_flag, mempage_order);
			}
			kfree(rtk_mtd);
		}
		//remove_proc_entry("nandinfo", NULL);
	}else{
		printk(KERN_ERR "Realtek Nand Flash Driver is successfully installing.\n");
	}

#endif
	return rc;
}

static int rtk_nand_remove(struct platform_device *dev)
{
	struct nand_chip *this = NULL;
	free_irq(g_host->irq, g_host);

	if (rtk_mtd){
		//del_mtd_partitions (rtk_mtd);
		this = (struct nand_chip *)rtk_mtd->priv;
		if (this->g_databuf)
			kfree(this->g_databuf);
		if(this->g_oobbuf)
			kfree(this->g_oobbuf);
		if (this->erase_page_flag){
			unsigned int flag_size =  (this->numchips * this->page_num) >> 3;
			unsigned int mempage_order = get_order(flag_size);
			free_pages((unsigned long)this->erase_page_flag, mempage_order);
		}
		kfree(rtk_mtd);

	}

	return 0;
}

static struct of_device_id rtk129x_nand_ids[] = {
	{ .compatible = "Realtek,rtk1295-nand" },
	{ /* Sentinel */ },
};

static struct platform_driver rtk_nand_driver = {
	.probe      = rtk_nand_probe,
	.remove     = rtk_nand_remove,
	.suspend    = rtk_nand_suspend,
	.resume     = rtk_nand_resume,
	.driver     = {
		.name = "rtk_nand_driver",
		.owner = THIS_MODULE,
		.of_match_table = rtk129x_nand_ids,
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
