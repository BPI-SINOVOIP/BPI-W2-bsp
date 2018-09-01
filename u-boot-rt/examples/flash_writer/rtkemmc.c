/*
 *  This is a driver for the eMMC controller found in Realtek Phoenix 1195
 *  SoCs.
 *
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#pragma GCC push_options
#pragma GCC optimize ("O2")
//#include "mmc.h"
#include "rtkemmc.h"
#include "dvrboot_inc/sys_reg.h"
#include "dvrboot_inc/util.h"
#include "cache.h"

#define __RTKEMMC_C__
//#define DEBUG


//unsigned char ext_csd[0x200];
//unsigned char dummy_buffer[0x220];


#define MAX_DESCRIPTOR_NUM    8
#define	EMMC_MAX_SCRIPT_BLK   8   

//emmc descriptor must be 8 byte aligned
unsigned int* rw_descriptor __attribute__ ((aligned(8))) =  0x00300000;
static unsigned char *alloc_ptr = 0x200000;
#define ROUND(a,b)		(((a) + (b) - 1) & ~((b) - 1))

static  u8* alloc_outside_buffer(unsigned int length){
	alloc_ptr += length;
	return alloc_ptr;
}

static  void MY_CLR_ALIGN_BUFFER(){
	alloc_ptr = 0x200000;
}

#define MY_ALLOC_CACHE_ALIGN_BUFFER(type, name, size)	type* name = alloc_outside_buffer(ROUND(size * sizeof(type), 64));
#define MY_ALLOC_ALIGN_BUFFER(type, name, size, align) type* name = alloc_outside_buffer(ROUND(size * sizeof(type), align));



unsigned char * dummy_512B;

#ifdef THIS_IS_FLASH_WRITE_U_ENV
static unsigned int rtkemmc_debug_msg;
static unsigned int rtkemmc_off_error_msg_in_init_flow;
static unsigned int sys_rsp17_addr;
static unsigned char* ptr_ext_csd;
static unsigned int sys_ext_csd_addr;
static UINT8 g_cmd[5]={0};
#else
unsigned int rtkemmc_debug_msg;
unsigned int rtkemmc_off_error_msg_in_init_flow;
#endif

#define ERR_EMMC_SEND_STATUS_RETRY_FAIL 0x60
#define ERR_EMMC_SEND_RW_CMD_RETRY_FAIL 0x61
#define ERR_EMMC_CMD3_FAIL          0x63    /* mmc cmd3 fail present initial process fail */
#define ERR_EMMC_CMD7_FAIL          0x64    /* mmc cmd4 fail present initial process fail */
#define EMMC_MAX_CMD_SEND_RETRY_CNT 20
#define EMMC_MAX_STOP_CMD_RETRY_CNT 10
#define ERR_EMMC_SRAM_DMA_TIME      0x51
static int bErrorRetry_1=0, bErrorRetry_2=0;
static int g_Indicator_RW=0;   //R : 0 , W : 1
/* mmc spec definition */
const unsigned int tran_exp[] = {
    10000, 100000, 1000000, 10000000,
    0,     0,      0,       0
};

const unsigned char tran_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

const unsigned int tacc_exp[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

const unsigned int tacc_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

const char *const state_tlb[9] = {
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
const char *const bit_tlb[4] = {
    "1bit",
    "4bits",
    "8bits",
    "unknow"
};

const char *const clk_tlb[8] = {
    "30MHz",
    "40MHz",
    "49MHz",
    "49MHz",
    "15MHz",
    "20MHz",
    "24MHz",
    "24MHz"
};

/************************************************************************
 *  global variable
 ************************************************************************/
unsigned cr_int_status_reg;
e_device_type emmc_card;


UINT32 check_error(){
	int i;
	UINT32 error;
	error = cr_readl(CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
#ifdef DEBUG
	prints("Emmc RINTSTS = 0x");
	print_hex(error);
	prints("\n");

	prints("Emmc STATUS = 0x");
	print_hex(cr_readl(CR_EMMC_STATUS));
	prints("\n");
#endif
	if ((error&CR_EMMC_EBE)==CR_EMMC_EBE)
	{
		prints("End bit error \n");
		return CR_EMMC_EBE;
	}
	else if ((error&CR_EMMC_SBE)==CR_EMMC_SBE)
	{
		prints("Start bit error \n");
		return CR_EMMC_SBE;
	}
	else if ((error&CR_EMMC_HLE)==CR_EMMC_HLE)
	{
		prints("Hardware locked write error \n");
		return CR_EMMC_HLE;
	}
	else if ((error&CR_EMMC_FRUN)==CR_EMMC_FRUN)
	{
		prints("FIFO underrun/overrun error \n");
		return CR_EMMC_FRUN;
	}
	else if ((error&CR_EMMC_HTO)==CR_EMMC_HTO)
	{
		prints("Data starvation by host timeout\n");
		return CR_EMMC_HTO;
	}
	else if ((error&CR_EMMC_DRTO)==CR_EMMC_DRTO)
	{
		prints("Data read timeout\n");
		return CR_EMMC_DRTO;
		}
	else if ((error&CR_EMMC_RTO)==CR_EMMC_RTO)
	{
		prints("Response timeout\n");
		return CR_EMMC_RTO;
	}
	else if ((error&CR_EMMC_DCRC)==CR_EMMC_DCRC)
	{
		prints("Data CRC error\n");
		return CR_EMMC_DCRC;
	}
	else if ((error&CR_EMMC_RCRC)==CR_EMMC_RCRC)
	{
		prints("Response CRC error\n");
		return CR_EMMC_RCRC;
	}
	else if ((error&CR_EMMC_RE)==CR_EMMC_RE)
	{
		prints("Response error\n");		
		return CR_EMMC_RE;
	}
	else 
	{
#ifdef DEBUG
		prints("No error \n");
#endif
		return 0;
	}	
	return 0;
	sync();
}

void reset_ip(){
	cr_writel(0x00000081, CR_EMMC_BMOD); //reset
	sync();	
}		


//rsp_con -  0: no rsp, 1: short rsp, 3: long rsp
int emmc_send_cmd_get_rsp(UINT32 cmd_idx, UINT32 sd_arg, UINT32 rsp_con, UINT32 crc){ 

	int ret_error = 0;
				
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS); 		// clear all interrupt status
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK); 		// enable all interrupts					
	CP15ISB;
	sync();
	cr_writel(sd_arg, CR_EMMC_CMDARG);	// cmd argument
	CP15ISB;
	sync();

#ifdef DEBUG
	prints("Emmc cmd = 0x");
	print_hex(cmd_idx);
	prints("\n");
#endif			
	cr_writel(0xa0000000|cmd_idx|(rsp_con<<6)|(crc<<8), CR_EMMC_CMD);	// cmd Register
	CP15ISB;
	sync();
	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); 	
	wait_done((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 	
	CP15ISB;
	sync();

#ifdef DEBUG
	prints("Emmc Resp0 = 0x");
	print_hex(cr_readl(CR_EMMC_RESP0));
	prints("\n");
	prints("Emmc Resp1 = 0x");
	print_hex(cr_readl(CR_EMMC_RESP1));
	prints("\n");
	prints("Emmc Resp2 = 0x");
	print_hex(cr_readl(CR_EMMC_RESP2));
	prints("\n");
	prints("Emmc Resp3 = 0x");
	print_hex(cr_readl(CR_EMMC_RESP3));
	prints("\n");
#endif	

	if ((ret_error = check_error())==0)
	{	
		return 0;
	}
	else 
	{
		reset_ip();
		return ret_error;
	}		
}	


int frequency(UINT32 fre, UINT32 div){
#ifndef FPGA
	cr_writel((cr_readl(SYS_PLL_EMMC3)&0xffff) | (fre << 16), SYS_PLL_EMMC3);
	CP15ISB;
	// ECO, if EMMC N/F code changed, toggle CR_EMMC_DUMMY_SYS bit 30
	cr_writel((~cr_readl(CR_EMMC_DUMMY_SYS)) & 0x40000000, CR_EMMC_DUMMY_SYS);
	CP15ISB;
	sync();
#endif
	wait_done((UINT32*)CR_EMMC_STATUS, 0x200, 0x0); 	 //card is not busy
	CP15ISB;
	sync();
	
	//disable clock
	cr_writel(0, CR_EMMC_CLKENA);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();

	//set divider
	cr_writel(div, CR_EMMC_CLKDIV);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();
	
	//enable clock
	cr_writel(0x10001, CR_EMMC_CLKENA);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();
	

	prints("switch frequency to 0x");
	print_hex(fre);
	prints("\n");

	prints("frequency divider is 0x");
	print_hex(div);
	prints("\n");
		
	
}
int kylin_cr_init(){
	int n = 0, ret_err = 0;
	
	//Intialize
	cr_writel(0x00000081, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x02000000, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_PWREN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	cr_writel(0xffffffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_CLKDIV);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CLKSRC);
	CP15ISB;
	sync();
	cr_writel(0x0001ffff, CR_EMMC_CLKENA);
	CP15ISB;
	sync();
	cr_writel(0xa0200000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	cr_writel(0xffffff40, CR_EMMC_TMOUT);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CTYPE);
	CP15ISB;
	sync();
	cr_writel(0x007f007f, CR_EMMC_FIFOTH);
	CP15ISB;
	sync();
	cr_writel(0x02000010, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x0000ffcf, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	//cr_writel(0x00600000, CR_EMMC_DBADDR);
	cr_writel(0x00000000, CR_EMMC_IDINTEN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_UHSREG);

	CP15ISB;
	sync();

	//Card identification
	frequency(0x46, 0x80); //devider = 2 * 128 = 256	

	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	
	ret_err = emmc_send_cmd_get_rsp(MMC_SEND_OP_COND, 0x40000080, 1, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp

	CP15ISB;
	sync();

	while ((cr_readl(CR_EMMC_RESP0)&0x80000000)!=0x80000000){
		if(n++ > 0x100)
		{
			prints("CMD1 ERROR! \n");
			return ret_err;      
	 	}   
		ret_err = emmc_send_cmd_get_rsp(MMC_SEND_OP_COND, 0x40000080, 1, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp		
		CP15ISB;
		sync();
	}
	emmc_send_cmd_get_rsp(MMC_ALL_SEND_CID, 0, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SET_RELATIVE_ADDR, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	//Data Transfer Mode
	frequency(0x46, 0x4); //80M / 8 = 10M
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_CSD, emmc_card.rca, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_CID, emmc_card.rca, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SELECT_CARD, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	prints("switch to SDR 8 bit\n");
	switch_bus(2);
	CP15ISB;
	sync();
	return 0;
}



int rtk_eMMC_init( void )
{
    unsigned int tmp;
	int ret_err;
	int retry_counter;

	
	MY_CLR_ALIGN_BUFFER();
	MY_ALLOC_CACHE_ALIGN_BUFFER(char, dummy_buffer, 0x220);

	ret_err = -1;
	retry_counter = 3;
	rtkemmc_debug_msg = 1;
	rtkemmc_off_error_msg_in_init_flow = 1;
    sys_rsp17_addr = 0x00010000;   //rsp dma addr : 17B
    sys_ext_csd_addr = 0x00180000; //ext csd dma addr : 512B
    ptr_ext_csd = (UINT8*)sys_ext_csd_addr;
    emmc_card.rca = 1<<16; 
    emmc_card.sector_addressing = 1;          

    if (GET_CHIP_REV() >= PHOENIX_REV_B)
    {
		printf("rtk_emmc : detect chip rev. >= B\n");
		REG32(SYS_PLL_EMMC1) = 0xe0003;     //LDO1.8V
		REG32(CR_EMMC_PAD_CTL) = 0;              //PAD to 1.8V
		mdelay(300);
    }
    #ifdef FOR_ICE_LOAD
    prints("\nemmc : PLL_EMMC1 = 0x");
    print_hex((unsigned int)REG32(SYS_PLL_EMMC1));
    #endif
    // work around for 8-byte alignment
    tmp = ((unsigned int)dummy_buffer)& 0xfffffff8;
    tmp += 0x00000008;
    dummy_512B = (unsigned char *)tmp; // 16-byte aligment

    #ifdef FOR_ICE_LOAD
    prints("\nemmc : dummy_buffer = 0x");
    print_hex((unsigned int)dummy_buffer);
    prints(", dummy_512B = 0x");
    print_hex((unsigned int)dummy_512B);
    prints("\n");
    #else
    UPRINTF("\nemmc:%s(%d) %s %s\n", __FUNCTION__, reset_only, __DATE__, __TIME__);
    mmcprintf("\nemmc:dummy_buffer=0x%08x, dummy_512B=0x%08x\n", (unsigned int)dummy_buffer, (unsigned int)dummy_512B);
    #endif

	CP15ISB;
	sync();
    
	while( retry_counter-- ) {

		ret_err = kylin_cr_init();

		if( ret_err ) {
            #ifdef FOR_ICE_LOAD
            prints("emmc: init fail(");
            print_hex(ret_err);
            prints(")\n");
            #else
			UPRINTF("\nemmc: init fail(%d)\n", ret_err);
            #endif
		}
		else {
			return ret_err;
		}
	}
	return ret_err;
}

void switch_bus(UINT8 WIDTH){
	emmc_send_cmd_get_rsp(MMC_SWITCH, 0x03b70000|(WIDTH<<8), 1, 1); //WIDTH - 0: SDR1b, 1: SDR4b, 2: SDR8b, 5: DDR4b, 6: DDR8b
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1);
	CP15ISB;
	if ((cr_readl(CR_EMMC_RESP0)&0x80)==0){
		prints("switch bus width to 0x");
		print_hex(WIDTH * 4);
		prints(" bits success\n");
		switch(WIDTH)
		{
			case 0:
				cr_writel(0x00000000, CR_EMMC_CTYPE); // 1bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 1:
				cr_writel(0x00000001, CR_EMMC_CTYPE); // 4bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 2:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 5:
				cr_writel(0x00000001, CR_EMMC_CTYPE); // 4bit
				cr_writel(0x00010001, CR_EMMC_UHSREG); //DDR mode, SW 1.8V
				break;
			case 6:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00010001, CR_EMMC_UHSREG); //DDR mode, SW 1.8V
				break;
			default:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
				break;			
		}
	}		
	else{
		prints("switch bus width to 0x");
		print_hex(WIDTH * 4);
		prints(" bits fail\n");
	}	
}
void switch_speed(UINT8 speed){
	int speed_modify=speed;
	if ((speed==0 )||(speed==1)){
		speed_modify=1;
	}
	CP15ISB;
	//speed - 0, backward compatible timing, 1: High speed, 2: HS200
	emmc_send_cmd_get_rsp(MMC_SWITCH, 0x03b90000|(speed_modify<<8), 1, 1);	
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1);
	CP15ISB;
	if ((cr_readl(CR_EMMC_RESP0)&0x80)==0){
		prints("switch speed to 0x");
		print_hex(speed);
		prints(" success\n");
	}	
	else{
		prints("switch speed to 0x");
		print_hex(speed);
		prints(" fail\n");
	}	
}

UINT32 IsAddressSRAM(UINT32 addr)
{
    if ((addr<0x80000000) || (addr > 0x80007FFF))
        //ddr address
        return 0;
    else
        //secureRam addr
        return 1;
}


void make_ip_des(unsigned char *dma_addr, UINT32 dma_length){
    
	UINT32* des_base = rw_descriptor;
	UINT32  blk_cnt;                                                                                                                               
	UINT32  blk_cnt2;                                                                 
	UINT32  remain_blk_cnt;                                                                                                                        
                                                             
	UINT32  tmp_val;         

	//__asm_flush_aarch32_dcache_all();

	//blk_cnt must be the multiple of 512(0x200)
	blk_cnt  = dma_length>>9;
  	remain_blk_cnt  = blk_cnt;                                                                                                                                                              
		                                                                                        
	while(remain_blk_cnt){                                                                                       
                                                                                     
		/* setting des0; transfer parameter  */                                         
		tmp_val = 0x80000000 | 0x2 | 0x10;                               
		                                                                                
		if(remain_blk_cnt == blk_cnt)                                                   
		        tmp_val |= 0x8;                                               
		                                                                                
		if(remain_blk_cnt <= EMMC_MAX_SCRIPT_BLK)                                       
		        tmp_val |= 0x4;                                               
		                                                                                
		des_base[0] = tmp_val;                                                         
		                                                                                
		/* setting des1; buffer size in byte */                                         
		if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK){                                       
		        blk_cnt2 = EMMC_MAX_SCRIPT_BLK;                                         
		}else{                                                                          
		        blk_cnt2 = remain_blk_cnt;                                              
		}                                                                               
		des_base[1] = (blk_cnt2<<9);                                                   
		                                                                                
		/* setting des2; Physical address to DMA to/from */                             
		des_base[2] = (dma_addr);                                                    
		                                                                                
		/* setting des3; next descrpter entry */                                        
		des_base[3] = ((unsigned int)(des_base+4));      

		CP15ISB;
	                                                                                                                                                             
		dma_addr = dma_addr+(blk_cnt2<<9);                                    
		remain_blk_cnt -= blk_cnt2;                                             
		des_base += 4;                                                         
			                                                                             
	}       
	//__asm_flush_aarch32_dcache_all();
} 

int emmc_read_write_ip(UINT32 cmd_idx, UINT32 blk_addr, unsigned char *dma_addr, UINT32 dma_length){
	UINT32 ret_error = 0;

	//descriptor and dma must be in DDR
	cr_writel(0, CR_EMMC_SWC_SEL);
	cr_writel(0, CR_EMMC_CP);	


	CP15ISB;
	sync();

	make_ip_des(dma_addr, dma_length);

	cr_writel(dma_length, CR_EMMC_BYTCNT);
	cr_writel(rw_descriptor, CR_EMMC_DBADDR);
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	cr_writel(blk_addr,CR_EMMC_CMDARG);		
	CP15ISB;
	sync();

#ifdef DEBUG	
	prints("Emmc cmd = 0x");
	print_hex(cmd_idx);
	prints("\n");	
#endif

	if((cmd_idx==MMC_READ_SINGLE_BLOCK)){           
		cr_writel(0xa0000340|cmd_idx,CR_EMMC_CMD);		         
	}
	else if(cmd_idx==MMC_READ_MULTIPLE_BLOCK){   
		cr_writel(0xa0001340|cmd_idx,CR_EMMC_CMD);
	}
	else if(cmd_idx==MMC_WRITE_BLOCK){   
		cr_writel(0xa0000740|cmd_idx,CR_EMMC_CMD);		         
	}
	else if(cmd_idx==MMC_WRITE_MULTIPLE_BLOCK){   
		cr_writel(0xa0001740|cmd_idx,CR_EMMC_CMD);	
	}
	else{
		prints("Illegal command \n");
	}
	CP15ISB;
	sync();

	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); //command done
	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x8, 0x8); //data transfer over

	CP15ISB;
	sync();

	if ((cmd_idx==MMC_READ_MULTIPLE_BLOCK) ||(cmd_idx==MMC_WRITE_MULTIPLE_BLOCK) ){
		wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4000, 0x4000); //auto command done (stop command done)
	}
	wait_done((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 
	CP15ISB;
	sync();
	if ((ret_error = check_error())!=0){
		return ret_error;
	}

	else{
		return 0;
	} 	
}

int rtk_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned char * buffer, unsigned int auto_sel_part )
{
	UINT32  EMMC_MAX_MULTI_BLK = EMMC_MAX_SCRIPT_BLK * MAX_DESCRIPTOR_NUM;
    int ret_err = 0;
	int i = 0;
    unsigned int total_blk_cnt;
    unsigned int cur_blk_addr;
    e_device_type * card = &emmc_card;
	
	UINT32  remain_blk_cnt;
	UINT32  cur_blk_cnt;

    total_blk_cnt = data_size>>9;
	
    if(data_size & 0x1ff) {
        total_blk_cnt+=1;
    }
	remain_blk_cnt = total_blk_cnt;
	cur_blk_addr = blk_addr;
	

	CP15ISB;
	sync();
		
	//if (total_blk_cont > 1){
		//single block write
#if 0
		for (i = 0; i < total_blk_cont; i++){
			ret_err = emmc_read_write_ip(MMC_WRITE_BLOCK, address + i, buffer + (0x80 * i), 0x200);
			CP15ISB;
			sync();
		}
#else

		while (remain_blk_cnt) {
			if (remain_blk_cnt > EMMC_MAX_MULTI_BLK)
				cur_blk_cnt = EMMC_MAX_MULTI_BLK;
			else
				cur_blk_cnt = remain_blk_cnt;

			remain_blk_cnt -= cur_blk_cnt;
			if (cur_blk_cnt > 1)
				ret_err = emmc_read_write_ip(MMC_WRITE_MULTIPLE_BLOCK, cur_blk_addr, buffer + ((cur_blk_addr - blk_addr) << 9), cur_blk_cnt << 9);
			else
				ret_err = emmc_read_write_ip(MMC_WRITE_BLOCK, cur_blk_addr, buffer + ((cur_blk_addr - blk_addr) << 9), cur_blk_cnt << 9);
			cur_blk_addr += cur_blk_cnt;
			if (ret_err ) return 0;

		}
#endif
	//}
	//else
	//	ret_err = emmc_read_write_ip(MMC_WRITE_BLOCK, address, buffer, total_blk_cont << 9);
	
    return !ret_err ?  total_blk_cnt : 0;
}

int rtk_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned char * buffer, unsigned int auto_sel_part )
{
	UINT32  EMMC_MAX_MULTI_BLK = EMMC_MAX_SCRIPT_BLK * MAX_DESCRIPTOR_NUM;
    int ret_err = 0;
	int i = 0;
    unsigned int total_blk_cnt;
    unsigned int cur_blk_addr;
    e_device_type * card = &emmc_card;
	
	UINT32  remain_blk_cnt;
	UINT32  cur_blk_cnt;

    total_blk_cnt = data_size>>9;
	
    if(data_size & 0x1ff) {
        total_blk_cnt+=1;
    }
	remain_blk_cnt = total_blk_cnt;
	cur_blk_addr = blk_addr;
	

	CP15ISB;
	sync();
	
	//if (total_blk_cont > 1){
		//single block write
#if 0
		for (i = 0; i < total_blk_cont; i++){
			ret_err = emmc_read_write_ip(MMC_WRITE_BLOCK, address + i, buffer + (0x80 * i), 0x200);
			CP15ISB;
			sync();
		}
#else
		while (remain_blk_cnt) {
			if (remain_blk_cnt > EMMC_MAX_MULTI_BLK)
				cur_blk_cnt = EMMC_MAX_MULTI_BLK;
			else
				cur_blk_cnt = remain_blk_cnt;

			remain_blk_cnt -= cur_blk_cnt;
			if (cur_blk_cnt > 1)
				ret_err = emmc_read_write_ip(MMC_READ_MULTIPLE_BLOCK, cur_blk_addr, buffer + ((cur_blk_addr - blk_addr) << 9), cur_blk_cnt << 9);
			else
				ret_err = emmc_read_write_ip(MMC_READ_SINGLE_BLOCK, cur_blk_addr, buffer + ((cur_blk_addr - blk_addr) << 9), cur_blk_cnt << 9);
			cur_blk_addr += cur_blk_cnt;
			if (ret_err ) return 0;

		}

#endif
	//}
	//else
	//	ret_err = emmc_read_write_ip(MMC_WRITE_BLOCK, address, buffer, total_blk_cont << 9);
	
    return !ret_err ?  total_blk_cnt : 0;
}	


int emmc_switch_partition(unsigned int part_num){
	/*switch to partition,we should check response by MMC_SEND_STATUS	
	 * MMC_SWITCH_MODE_WRITE_BYTE <<24 |	 
	 *EXT_CSD_PART_CONF<<16 |
	 * part_num << 8 |	
	 * 1 <<0	
	 */
	 emmc_send_cmd_get_rsp(MMC_SWITCH, 				
	 			          ((MMC_SWITCH_MODE_WRITE_BYTE<<24)|(EXT_CSD_PART_CONF<<16) | ((part_num & PART_ACCESS_MASK)<<8)|(1<<0)) ,					
	 			           1,				
	 			           1);
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS,emmc_card.rca,1,1);

	CP15ISB;

	if( (cr_readl(CR_EMMC_RESP0) & SWITCH_ERROR) ==1){
		prints("switch fail\n");
		return 1;
	}
	else if( (cr_readl(CR_EMMC_RESP0) & SWITCH_ERROR) ==0){ 
		prints("switch success\n");
		return 0;
	}
	else{
		prints("can't get response\n");
		return 1;
	}
}





#pragma GCC pop_options
