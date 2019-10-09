#include <project_config_f.h>
//#include <stdio.h>
#include <sysdefs.h>
//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>


#include "flashdev_n.h"
#include "flashdev_n_reg.h"
#include "dvrboot_inc/util.h"
#include "dvrboot_inc/io.h"
#include "cache.h"

#define PAGE_TMP_ADDR		0xa1200000 - UBOOT_DDR_OFFSET
#define SPARE_DMA_ADDR		0xa16fff00 - UBOOT_DDR_OFFSET
#define BLK_STATE_BASE		0xa1700000 - UBOOT_DDR_OFFSET

extern UINT8  verify_after_write;


UINT32 pages_per_block;
UINT32 blocks_per_flash;
UINT32 pages_per_chip;
UINT32 total_chip_num;

//-----------------------------------------//
static UINT32  fileflash_phys_start ;
static UINT32  fileflash_phys_end ;
static UINT8 *blk_state;			// bootcode block state array
static UINT32 blk_state_len;			// length of bootcode block state array
static UINT32 current_env_start;		// (latest) env param page address
static UINT8 env_version_no;			// (latest) env param version on

static BB_t *bbt;
static UINT32 BBT_LENGTH;
static UINT32 nand_bootcode_area_size;		// NAND bootcode area size
static const n_device_type *ptr_device;


static UINT32 force_2k=0;

//-----------------------------------------//
static void nf_read_id(UINT32 DDR_BASE, UINT8 size);
static INT8 nf_find_blk(n_device_type *device, UINT32 start_block, UINT32 search_depth, UINT32 offset);
static int set_block_state(UINT32 block_no, UINT8 state);
static int get_block_state(UINT32 block_no, UINT8 *state);
//static INT8 nf_read_to_table(n_device_type *device, UINT32 page_no, UINT32 length);
static INT8 nf_read_to_PP(n_device_type *device, UINT32 page_no);
static int nf_write(n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size);
static int nf_map_phys_page(n_device_type *device, UINT8 *chip_select, UINT32 *phys_page);
static int nf_map_page(n_device_type *device, UINT8 *chip_select, UINT32 *phys_page);
static int nf_write_phys_page( n_device_type *device, UINT8 chip_sel, UINT32 page_no, UINT8 *buf);
static int nf_read_phys_page( n_device_type *device, UINT8 chip_sel, UINT32 page_no, UINT8 *buf, UINT8 chk_all_one);
static int nf_erase_phys_block(n_device_type *device, UINT8 chip_sel, UINT32 page_addr);
static int nf_read_single_byte(n_device_type *device, UINT32 col_addr, UINT32 page_addr, UINT8 *data);
static int nf_read_phys_single_byte(n_device_type *device, UINT8 chip_sel, UINT32 col_addr, UINT32 page_addr, UINT8 *data);
static UINT8 nf_spare_ddr_enabled(void);
static UINT32 nf_get_auto_transfer_unit(UINT8 ecc_type);
static UINT8 nf_is_random_mode(void);
static void nf_enable_random_mode(void);
static void nf_disable_random_mode(void);
static void nf_set_random_read(n_device_type *device,unsigned int spare_col);
static void nf_set_random_write(n_device_type *device,unsigned int spare_col);
static UINT8 nf_set_spare(UINT32 spare, UINT32 offset);

// bad block related
static int bbt_exist(void *dev);
static int init_bbt(n_device_type *device);
static int get_remap_block(UINT32 *start_blk);
static int build_bbt(void *dev);
static int load_bbt(void *dev);
static UINT32 initial_bad_block_offset(n_device_type *device);
static int map_phys_block(n_device_type *device, UINT8 *chip_select, UINT32 *phys_block);

// NAND profile related
static int nand_profile_exist(const void *dev);
static int build_nand_profile(const void *dev, t_nand_profile *profile);
static int write_nand_profile_bak(const void *dev, t_nand_profile *profile);
static int write_nand_profile(const void *dev, t_nand_profile *profile);
static unsigned int accumulate_byte_value(const void *buf, unsigned int length);


static int test_rw(n_device_type *dev)
{
	int ret = 0;
	n_device_type device;
	unsigned char tmp[256];
	int i;
	
	for (i=0 ; i<256 ; i++)
		//tmp[i] = i%16;
		*((unsigned char *)PAGE_TMP_ADDR+i) = i%16;

	//copy_memory((UINT8 *)PAGE_TMP_ADDR, tmp, 256);
	set_memory((UINT8 *) (PAGE_TMP_ADDR + 256), 0xff, 2048 - 256);

	// write profile into page 0
	nf_set_spare(0x23, 0);
	if (nf_write(dev, 0x180, (UINT8 *)PAGE_TMP_ADDR, 2048)) {
		prints("write test failed\n");
		set_block_state(0, BLOCK_BAD);
	}

	nf_read_phys_page(dev, 0, 0x180, (UINT8 *)PAGE_TMP_ADDR, 0);
	nf_read_phys_page(dev, 0, 0x40180, (UINT8 *)PAGE_TMP_ADDR, 0);
	nf_read_phys_page(dev, 0, 0x80180, (UINT8 *)PAGE_TMP_ADDR, 0);
	nf_read_phys_page(dev, 0, 0xc0180, (UINT8 *)PAGE_TMP_ADDR, 0);

	return 0;

	device.id = 0;
	device.PageSize = 8192;
	device.BlockSize = 2048*1024;
	device.size = 2048;
	device.addr_mode_rw = ADDR_MODE_C16_R24;
	device.addr_mode_erase = ADDR_MODE_R24;
	device.num_chips = 1;
	device.initial_bb_pos = 0;
	device.t1 = 0;
	device.t2 = 0;
	device.t3 = 0;
	device.nf_div = 0;
	device.ecc_bit = ECC_24BIT;
	device.read_id_len = 0;
	device.id5 = 0;
	device.id6 = 0;

	REG32(REG_ECC_SEL) = ECC_24BIT;
	
	// init.
	//REG32(REG_RMZ_SEED_L) = 0x6e;
	//REG32(REG_RMZ_SEED_H) = 0xa3;
	REG32(REG_BLANK_CHK) = 1;
	REG32(REG_Chip_En) = 0x1e;

	// reset.
	REG32(REG_CMD1) = 0xff;
	REG32(REG_CTL) = 0x80;

	REG32(REG_RMZ_CTRL) = 0x1;
	nf_read_phys_page(&device, 0, 0, (UINT8 *)PAGE_TMP_ADDR, 0);

	return ret;
	/*
	// erase.
	nf_erase_phys_block(&device, 0, 0);

	// read.
	nf_read_phys_page(&device, 0, 0, (UINT8 *)PAGE_TMP_ADDR, 1);
	
	return ret;
	*/
}

static int nf_ctrler_ddr_setting()
{
	//////////////////////////////////////////////////////////
	// DIC recommend end
	//////////////////////////////////////////////////////////
	
	rtd_maskl(0xb800011c,0xFCFFFFFF,0x00000000);
	rtd_maskl(0xb800010c,0xFCFFFFFF,0x00000000);
	rtd_maskl(0xb800010c,0xFCFFFFFF,0x03000000);
	rtd_maskl(0xb800011c,0xFCFFFFFF,0x03000000);
	
	
	//DC_SYS setting
	rtd_outl(0xb8008004,0x024B0000);  // two-ddr
	//rtd_outl(0xb8008004,0x02420000);	// one-ddr
	
	//ZQ Calibration setting
	rtd_outl(0xb8008924,0x01000000); //Vref internal, DC1 ZQ PAD power down
	rtd_outl(0xb8003924,0x01000000); //Vref internal, DC2 ZQ PAD power down 										
	rtd_outl(0xb8008a14,0x00000000); // 						   
	mdelay(0x10); 										
	rtd_outl(0xb8008924,0x00000000); //Vref internal, ZQ PAD normal    
	rtd_outl(0xb8008928,0x7F063B76);	//OCD 34,ODT 60 for U40LP
	//rtd_outl(0xb8008928,0x7F085D3A); //OCD=40, ODT=60 for U55 
	//rtd_outl(0xb8008928,0x7F061E3C);	//OCD 40,ODT 60 for U40LP		  
	mdelay(0x10); 	   //delay							
	rtd_outl(0xb8008924,0x01000000); //Vref internal, ZQ PAD power down
	
	rtd_outl(0xb8008910,0x00000fff);	//PAD_OE_CTL PAD output enable;
	rtd_outl(0xb8008918,0x00000000);	//PAD_IDDQ0
	mdelay(0x1);		  //delay
	
	//OCD setting E2:1,NT:3,PT:5,PLSB:0 for DQ/DQS/CLK/CMD/ADDRESS
	//rtd_outl(0xb8008a34,0x36ED36ED); // DQ group 0~3
	//rtd_outl(0xb8008a38,0x0F6DBB6D); // DQS group 0~3
	//rtd_outl(0xb8008a3c,0x0F6DBB6D); // DQS# group 0~3
	//rtd_outl(0xb8008a40,0x000036ED); // CLK 
	//rtd_outl(0xb8008a44,0x000036ED); // CLK_1 
	//rtd_outl(0xb8008a10,0x00000489); // ADDR/CMD 0131 update from James 
	//rtd_outl(0xb8008a48,0x0000005D); // CMD_1 
	//rtd_outl(0xb8008920,0x0000005D); // ADDR_1 
	
	
	//Output delay chain
	rtd_outl(0xb8008930,0x24924924); //DQ9~0 //double buffer is?
	rtd_outl(0xb8008934,0x24924924); //DQ19~10
	rtd_outl(0xb8008938,0x24924924); //DQ29~20
	rtd_outl(0xb800893c,0x24924924); //DQS3~0, DM3~0, DQ31~30
	rtd_outl(0xb800890c,0x00000131); //set CLK output delay chain
	
	//Timing setting
	//1333 (SW)
	//rtd_outl(0xb8008800,0x00179712); //TMCTRL0: tRAS:25 / tCL:9 / tCWL:7 / tmCLRD:9
	//rtd_outl(0xb8008804,0x0408081C); //TMCTRL1: tRRD:6 / tRP:10 / tRCD:10 / tRC:34
	//rtd_outl(0xb8008808,0x0206050a); //TMCTRL2: TCCD:4 / tRTP:6 / tWTR:6 / tWR:12
	//rtd_outl(0xb800880c,0x1d013040); //TMCTRL3: tFAW: 31/ tREF: 19(3.84us) 9:1.92us / tmRFC:0x40=112ns
	//rtd_outl(0xb8008810,0x00000d03); //TMCTRL4: tAOND:2 / tAOFD:2 / tMMOD(Mode register Set Command cycle time):13 / tMMRD(MRS cmd to ODT update delay):5
	/////DRAM mode register
	//rtd_outl(0xb8008844,0x00040d51); //MOD_REG0, bit[15:0] for DDR3-1333MHz: CL9/BC4&BL8/WR12/AL0,40/60 
	//rtd_outl(0xb8008848,0x00000010); //MOD23_REG for DDR3:Rtt_WR: disable, CWL:7, ASR disable, dynamic ODT off.
	
	//////////////////////////////////////////////////////////
	// DIC recommend Start
	//////////////////////////////////////////////////////////
	//Timing setting
	//800 
	rtd_outl(0xb8008800,0x001c650C); //TMCTRL0: tRAS:0x1c((28+2)*2.5 = 75)(35ns) / #tCL:0x6(6nCK) / #tCWL:0x5(5nCK) / #tmCLRD:0x0C(12/2=6)(6nCK)
	rtd_outl(0xb8008804,0x060a0a22); //TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0xa((10+2)*2.5=30)(13.125ns) / tRCD:0xa((10+2)*2.5=30)(13.125ns) / tRC:0x22((34+6)*2.5 = 100)(48.75ns)
	rtd_outl(0xb8008808,0x02060508); //TMCTRL2: TCCD:4(2+2=4)(4nCK) / tRTP:6(6*2.5=15)(7.5ns) / tWTR:5((5+1)*2.5=15)(7.5ns) / tWR:0xa((8+2)*2.5=30)(15ns)
	rtd_outl(0xb800880c,0x2001707a); //TMCTRL3: tFAW: 32((32+2)*2.5=85)(45ns)/ tREF: 0x17((23+1)*128*2.5=7.68us)(3.9us/7.8us) / tmRFC:0x7a((122+11)*2.5=332.5)(160ns)
	rtd_outl(0xb8008810,0x03030d02); //TMCTRL4: tAOND:2((2+2)*2.5=10)(2ns) / tAOFD:2((2+2)*2.5=10)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK,15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	rtd_outl(0xb8008814,0x00200400); //TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	rtd_outl(0xb8008818,0x00240080); //TMCTRL6: dqs_lat_sel:0 / dqs_alt:0 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
	///DRAM mode register
	//rtd_outl(0xb8008844,0x00040b21); //MOD_REG0, bit[15:0] for DDR3-800MHz: #CL6(bit6,5,4,2)/BC4&BL8/#WR10/AL0,40/60
	rtd_outl(0xb8008844,0x00060b21); //MOD_REG0, bit[15:0] for DDR3-800MHz: #CL6(bit6,5,4,2)/BC4&BL8/#WR10/AL0,34/60  
	//rtd_outl(0xb8008844,0x00400b21); //MOD_REG0, bit[15:0] for DDR3-800MHz: #CL6(bit6,5,4,2)/BC4&BL8/#WR10/AL0,34/120
	//rtd_outl(0xb8008844,0x00420b21); //MOD_REG0, bit[15:0] for DDR3-800MHz: #CL6(bit6,5,4,2)/BC4&BL8/#WR10/AL0,34/40 
	
	rtd_outl(0xb8008848,0x00000000); //MOD23_REG for DDR3:Rtt_WR: disable, #CWL:5(bit6,5,4,2), ASR disable, dynamic ODT off.
	
	
	
	////1333 (PUPD2)
	//rtd_outl(0xb8008800,0x001c9712); //TMCTRL0: tRAS:0x1c((28+2)*1.5 = 45)(35ns) / #tCL:0x9(9nCK) / #tCWL:0x7(7nCK) / #tmCLRD:0x12(18/2=9)(9nCK)
	//rtd_outl(0xb8008804,0x060a0a22); //TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0xa((10+2)*1.5=18)(13.125ns) / tRCD:0xa((10+2)*1.5=18)(13.125ns) / tRC:0x22((34+6)*1.5 = 60)(48.75ns)
	//rtd_outl(0xb8008808,0x0206050a); //TMCTRL2: TCCD:4(2+2=4)(4nCK) / tRTP:6(6*1.5=9)(7.5ns) / tWTR:5((5+1)*1.5=9)(7.5ns) / tWR:0xa((10+2)*1.5=18)(15ns)
	//rtd_outl(0xb800880c,0x2001707a); //TMCTRL3: tFAW: 32((32+2)*1.5=51)(45ns)/ tREF: 0x17((23+1)*128*1.5=4608)(3.9us/7.8us) / tmRFC:0x7a((122+11)*1.5=199.5)(160ns)
	//rtd_outl(0xb8008810,0x03030d02); //TMCTRL4: tAOND:3((3+2)*1.5=7.5)(2ns) / tAOFD:3((3+2)*1.5=7.5)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK,15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	//rtd_outl(0xb8008814,0x00200400); //TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	//rtd_outl(0xb8008818,0x00240080); //TMCTRL6: dqs_lat_sel:0 / dqs_alt:0 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
	/////DRAM mode register
	//rtd_outl(0xb8008844,0x00000b51); //MOD_REG0, bit[15:0] for DDR3-1333MHz: #CL9/BC4&BL8/#WR10/AL0, 
	//rtd_outl(0xb8008848,0x00000010); //MOD23_REG for DDR3:Rtt_WR: disable, #CWL:7, ASR disable, dynamic ODT off.
	
	//1600 (PUPD2)
	//rtd_outl(0xb8008800,0x001cb816); //TMCTRL0: tRAS:0x1c((28+2)*1.25 = 37.5)(35ns) / #tCL:0xb(11nCK) / #tCWL:0x8(8nCK) / #tmCLRD:0x16(22/2=11)(11nCK)
	//rtd_outl(0xb8008804,0x060a0a22); //TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0xa((10+2)*1.25=15)(13.125ns) / tRCD:0xa((10+2)*1.25=15)(13.125ns) / tRC:0x22((34+6)*1.25 = 50)(48.75ns)
	//rtd_outl(0xb8008808,0x0206050a); //TMCTRL2: TCCD:4(2+2=4)(4nCK) / tRTP:6(6*1.25=7.5)(7.5ns) / tWTR:5((5+1)*1.25=7.5)(7.5ns) / tWR:0xa((10+2)*1.25=15)(15ns)
	//rtd_outl(0xb800880c,0x2001707a); //TMCTRL3: tFAW: 32((32+2)*1.25=42.5)(40ns)/ tREF: 0x17((23+1)*128*1.25=3840)(3.9us/7.8us) / tmRFC:0x7a((122+11)*1.25=166.25)(160ns)
	//rtd_outl(0xb8008810,0x03030d02); //TMCTRL4: tAOND:3((3+2)*1.25=6.25)(2ns) / tAOFD:3((3+2)*1.25=6.25)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK,15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	//rtd_outl(0xb8008814,0x00200400); //TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	//rtd_outl(0xb8008818,0x00240080); //TMCTRL6: dqs_lat_sel:0 / dqs_alt:0 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
	/////DRAM mode register
	//rtd_outl(0xb8008844,0x00060d71); //MOD_REG0, bit[15:0] for DDR3-1600MHz: #CL11/BC4&BL8/#WR12/AL0,34/60 
	//rtd_outl(0xb8008848,0x00000018); //MOD23_REG for DDR3:Rtt_WR: disable, #CWL:8, ASR disable, dynamic ODT off.
	//////////////////////////////////////////////////////////
	// DIC recommend end
	//////////////////////////////////////////////////////////
	
	rtd_outl(0xb8008820,0x000003ff); //ODT_CTRL
	rtd_outl(0xb800882c,0x00000000); //DC_MIS
	rtd_outl(0xb8008830,0x00000000); //DC_MISa	pre_dis,0, lbk_en,disable
	rtd_outl(0xb8008834,0x10000000); //DC_MISb	tmrc_sel,1: 0: tmrc,tmras+tmrp, 1: tmrc,tmrc (DRAM always let tRAS+tRP,tRC)
	rtd_outl(0xb8008954,0x00000011); //setting from DV , bit13:1(pupd2 on)
	
	rtd_outl(0xb8008880,0x00000618); //set inital read DQS to DQ phase to tap: 24
	rtd_outl(0xb8008838,0x07000000); //update all DQS RX delay chain
	rtd_outl(0xb8008908,0x000000F1); //5 taps for left and right, auto K enable
	
	//FIFO CTRL
	rtd_outl(0xb800884c,0x00000030);		//R/W/Q FIFO 
	//rtd_outl(0xb8008904,0x00002880);		//4T										 
	rtd_outl(0xb8008904,0x00000880);		//2T 
	rtd_outl(0xb800897c,0x00000001);		//Reset fifo.
	
	//use external REF 
	//rtd_outl(0xb8008924,0x03000000);
	
	//DQS OE MUX Select
	//rtd_outl(0xb8008c0c,0x00000000);		//select 0
	
	//Receiver_1st phase
	//rtd_outl(0xb8008880,0x08200820);
	//rtd_outl(0xb8008884,0x08200820);
	//rtd_outl(0xb8008888,0x08200820);
	//rtd_outl(0xb800888c,0x08200820);
	//rtd_outl(0xb8008890,0x08200820);
	//rtd_outl(0xb8008894,0x08200820);
	//rtd_outl(0xb800889c,0x08200820);
	//rtd_outl(0xb80088a0,0x08200820);
	//rtd_outl(0xb80088a4,0x08200820);
	//rtd_outl(0xb80088a8,0x08200820);
	//rtd_outl(0xb80088ac,0x08200820);
	//rtd_outl(0xb80088b0,0x08200820);
	//rtd_outl(0xb80088b4,0x08200820);
	//rtd_outl(0xb80088b8,0x08200820);
	//rtd_outl(0xb80088bc,0x08200820);
	//rtd_outl(0xb80088c0,0x08200820);
	//rtd_out1(0xb8008838,0x06000000);
	
	//fb_offset enable
	rtd_outl(0xb8008a4c,0x11115501);
	
	//DDR3 init 
	
	//////////////////////////////////////////////////////////
	// DIC recommend Start
	//////////////////////////////////////////////////////////
	rtd_outl(0xb8008940,0x00000001);  //gating par_stp, for MG
	//////////////////////////////////////////////////////////
	// DIC recommend end
	//////////////////////////////////////////////////////////
	
	rtd_outl(0xb8008840,0x00000003);  //DRAM init
	
	//////////////////////////////////////////////////////////
	// DIC recommend Start
	//////////////////////////////////////////////////////////
	rtd_outl(0xb8008940,0x00000003);  //un-gating par_stp, for MG
	//////////////////////////////////////////////////////////
	// DIC recommend end
	//////////////////////////////////////////////////////////
	
	mdelay(0x1);	  // Must wait 200us delay, don't remove it
	rtd_outl(0xb8008840,0x03000000);  //end 200us
	mdelay(0x1);	  // Must wait 500us delay, don't remove it
	rtd_outl(0xb8008840,0x0c000000);  //end 500us
	
	
	rtd_outl(0xb800897c,0x1);

}


static int nf_ctrler_crt_setting()
{
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);	
//	REG32(0xb8060050) = 0x00000001; //ST_BUS = 27 MHz
//	mdelay(1);
//	REG32(0xb8000200) = 0x00000001; //SCPU_clk=27 MHz
//	mdelay(1);
//	REG32(0xb8000204) = 0x00000001; //Main UART Clock Source Select = 27 MHz
//	mdelay(1);
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);	
//	REG32(0xB801a808) = 0xf;
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	
	//-------- PLL ACPU -------------------------------------------------
	
	REG32(0xb800040c) = 0x00000003;
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL BUS -------------------------------------------------
	REG32(0xb8000420) = 0x00350b52; //405MHz  
	REG32(0xb8000424) = 0x0001102b;
	REG32(0xb8000428) = 0x00000005;
	REG32(0xb8000428) = 0x00000007;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000428) = 0x00000003;
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL BUSH -------------------------------------------------
	REG32(0xb8000430) = 0x06d91b52;  //378MHz
	
	REG32(0xb8000434) = 0x0001102b;
	REG32(0xb8000438) = 0x00000005;
	REG32(0xb8000438) = 0x00000007;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000438) = 0x00000003;  // Div2
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL BUS2 -------------------------------------------------
	
	
	//-------- PLL SCPU -------------------------------------------------
	REG32(0xb8000400) = 0x00a62413; //900MHz
	REG32(0xb8000400) = 0x00000005;
	REG32(0xb8000400) = 0x00000007;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000404) = 0x00000003; 
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL VCPU -------------------------------------------------
	REG32(0xb8000410) = 0x00009613; //297MHz 
	REG32(0xb8000414) = 0x00000005;
	REG32(0xb8000414) = 0x00000007;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000414) = 0x00000003; 
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL DISP -------------------------------------------------
	REG32(0xb8000490) = 0x01f0142a; //297M 
	REG32(0xb8000494) = 0x0000000d; 
	REG32(0xb8000494) = 0x0152000f;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000494) = 0x01520003;
	REG32(0xb8000494) = 0x01520042; 
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- PLL DIF -------------------------------------------------
	REG32(0xb80004c0) = 0x00e5a000; //SYS 172.8MHz	ADC 28.8MHz
	REG32(0xb80004c4) = 0x00000001; 
	REG32(0xb80004c8) = 0x0000000e; 
	REG32(0xb80004c8) = 0x00000007; 
	
	//-------- PLL GPU -------------------------------------------------
	REG32(0xb8000450) = 0x00339693; //199.125MHz 
	REG32(0xb8000454) = 0x00000005;
	REG32(0xb8000454) = 0x00000007;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb8000454) = 0x00000003;
	
	//-------- PLL GPU_L2 -------------------------------------------------
	REG32(0xb8000458) = 0x00339693; //199.125MHz
	REG32(0xb800045c) = 0x00000005;
	REG32(0xb800045c) = 0x00000007;
	//ScalerTimer_DelayXms(1); 
	mdelay(1);
	REG32(0xb800045c) = 0x00000003;
	
	//-------- PLL VODMA -------------------------------------------------
	REG32(0xb8000464) = 0x00000005;
	REG32(0xb8000464) = 0x00000007;
	//ScalerTimer_DelayXms(1); 
	mdelay(1);
	REG32(0xb8000464) = 0x00000003; 
	
	//-------- PLL DDS -------------------------------------------------
	REG32(0xb8000478) = 0x02080005;
	REG32(0xb800047c) = 0x00000005;
	REG32(0xb800047c) = 0x00000007;
	//ScalerTimer_DelayXms(1); 
	mdelay(1);
	REG32(0xb800047c) = 0x00000003; 
	
	//-------- PLL 512FS -------------------------------------------------
	REG32(0xb80004b4) = 0x00000005;
	REG32(0xb80004b4) = 0x00000007;
	//ScalerTimer_DelayXms(1); 
	mdelay(1);
	REG32(0xb80004b4) = 0x00000003; 
	
	//-------- PLL AUD -------------------------------------------------
	REG32(0xb80004e4) = 0x0000000c; //196MHz 
	
	//-------- PLL 27X -------------------------------------------------
	REG32(0xb80004d0) = 0x02250012; //540MHz 
	REG32(0xb80004d4) = 0x00006500; 
	REG32(0xb80004dc) = 0x00000000; 
	REG32(0xb80004d8) = 0x00000007; 
	
	
	//-------- PLL VBY1 -------------------------------------------------
	REG32(0xb8000498) = 0x01f0142a; //297M 
	REG32(0xb800049c) = 0x0152000d; 
	REG32(0xb800049c) = 0x0152000f;
	//ScalerTimer_DelayXms(1);
	mdelay(1);
	REG32(0xb800049c) = 0x01520003;
	REG32(0xb800049c) = 0x01520042; 
	
	//-------- Module Clock & Reset --------------------------------------
	REG32(0xb8000104) = 0x02000000; 
	REG32(0xb800010c) = 0x02000000; 
	REG32(0xb8000114) = 0x02000000; 
	REG32(0xb800011c) = 0x02000000; 
	REG32(0xb8000100) = 0x0000008b; 
	
	//-------- ACPU clock source select to PLLACPU ------------------------
	REG32(0xb8000200) = 0x00000000; 
	//-------- BUS clock source select to PLLBUS ------------------------
	REG32(0xb8060050) = 0x00000000; 
	
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);		
	//-------- DDR clock source select to PLLDDR ------------------------
	
	REG32(0xb8000500) = 0x000000fc;
								  
	//500~ 600													   
	REG32(0xb8000504) = 0xfe09ba9a; 							   
	
	
	//Phase setting for 796 										   
	REG32(0xb8000508) = 0x0e081810; //phase control --> DQS0/1 change
	REG32(0xb800050c) = 0x2700180e; //phase control --> DQS2/3 change
	
	
	
	
	REG32(0xb8000514) = 0x02400000; //513MHz
	
	REG32(0xb8000518) = 0x030d00c0;
	 
	REG32(0xb8000500) = 0x000000fe; 
	REG32(0xb8000500) = 0x000000ff; 
	REG32(0xb8000500) = 0x00000003; 
	
	//DC2 setting-----------------------------------------
	
	REG32(0xb8000520) = 0x000000fc;
	
	//DDRPLL CLK
	//250 ~ 300
	REG32(0xb8000524) = 0xfe08b798;
	
	 
	REG32(0xb8000528) = 0x03081810; 
	REG32(0xb800052c) = 0x27001803;
	REG32(0xb8000534) = 0x01400000; //297MHz  
	
	REG32(0xb8000538) = 0x030d00c0;
	 
	REG32(0xb8000520) = 0x000000fe; 
	REG32(0xb8000520) = 0x000000ff; 
	REG32(0xb8000520) = 0x00000003; 
	
	//-------- Module Clock Enable --------------------------------------
	REG32(0xb8000110) = 0x00000331; 
	REG32(0xb8000114) = 0xffffffff; 
	REG32(0xb8000118) = 0xffffffff; 
	REG32(0xb800011c) = 0xffffffff; 
	REG32(0xb8000110) = 0x00000001; 
	REG32(0xb8000114) = 0x00000000; 
	REG32(0xb8000118) = 0x00000000; 
	REG32(0xb800011c) = 0x00000000; 
	REG32(0xb8000100) = 0xffffffff; 
	REG32(0xb8000104) = 0xffffffff; 
	REG32(0xb8000108) = 0xffffffff; 
	REG32(0xb800010c) = 0xffffffff; 
	REG32(0xb8060044) = 0xffffffff; 
	REG32(0xb8000114) = 0xffffffff; 
	REG32(0xb8000118) = 0xffffffff; 
	REG32(0xb800011c) = 0xffffffff; 
	 
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);	
	//rtd_inl(0xb8060040);	//0x00000000
	//rtd_inl(0xb8060030);	//0x000000ff 
	REG32(0xb8060030) = 0x0000007f; 
	REG32(0xb8060030) = 0x000000ff; 
	REG32(0xb8060040) = 0x000001ff;
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);	
	
	REG32(0xB8000910) = 0x0000000b; // ip sel crt = 0xb
	REG32(0xB8000854) = 0xE0000000; // dbg pin0
	REG32(0xB8000310) = 0x0003000b; // crt dbg enable
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__); 


}


//-----------------------------------------//

static int nf_ctrler_init()
{
	int count;

	/*******************************
	 * init NAND flash start
	 *******************************/
	//nf_ctrler_crt_setting();
	//nf_ctrler_ddr_setting();

	REG32(REG_Chip_En) = 0x1E;
	REG32(REG_T3) = 0x2;
	REG32(REG_T2) = 0x2;
	REG32(REG_T1) = 0x2;

	//REG32(REG_MultiChMod) = 0x20;
	REG32(REG_MultiChMod) = 0x0;
	REG32(REG_PP_RDY) = 0x0;
	
	REG32(REG_SPR_DDR_CTL) = 0x60000000 | (PHYS(SPARE_DMA_ADDR) >> 3);

	//REG32(REG_RMZ_SEED_L) = 0x6e;
	//REG32(REG_RMZ_SEED_H) = 0xa3;

	// reset nand.
	REG32(REG_CMD1) = 0xff;
	REG32(REG_CTL) = 0x80;
	sync();

	// check ready/busy pin of NAND flash
	while ((rtd_inl(REG_CTL)&0x40) == 0);

	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static UINT8 nf_get_spare(INT8 mem_region, UINT32 *spare, UINT32 offset)
{
	//modify by angus
	mem_region=4;

	if (nf_spare_ddr_enabled()) {
		REG32(REG_SPR_DDR_CTL) = 0x60000000 | (PHYS(SPARE_DMA_ADDR+offset) >> 3);
		*spare = rtd_inl(PHYS(SPARE_DMA_ADDR + offset));
		//*spare = rtd_inl(SPARE_DMA_ADDR);
	}
	else {
		// configure spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
		rtd_outl(REG_PP_RDY,0); // disable read_by_pp
		rtd_outl(REG_SRAM_CTL, 0x30 | mem_region); // enable direct access to PP #5

		*spare = rtd_inl(0xb8010000 + offset); // set spare area of first PP
		//REG32(0xb8010004) = spare[0]; // (only first 6 byte is user-defined)

		rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access
	}

	return 0;
}

static UINT8 nf_set_spare(UINT32 spare, UINT32 offset)
{
	UINT8 i, count, increment;
	
	if (nf_spare_ddr_enabled()) {
	
		REG32(REG_SPR_DDR_CTL) = 0x60000000 | (PHYS(SPARE_DMA_ADDR+offset) >> 3);
		//rtd_outl(SPARE_DMA_ADDR + offset, spare);
		//rtd_outl(SPARE_DMA_ADDR, spare);
	
		
		if (ptr_device->ecc_bit == ECC_24BIT)
			increment = 4;	// 4B for software
		else
			increment = 8;	// 6B for software (8B spacing)

		// spare/data: 6B/512B based
		count = ptr_device->PageSize / nf_get_auto_transfer_unit(ptr_device->ecc_bit);
		for (i = 0; i < count; i++) {
			// (only 6 byte is for software)
			//rtd_outl(SPARE_DMA_ADDR + i*increment, spare);
			rtd_outl(PHYS(SPARE_DMA_ADDR + i*increment), spare);
			//REG8(SPARE_DMA_ADDR + i*increment + 4) = 0xff;
			//REG8(SPARE_DMA_ADDR + i*increment + 5) = 0xff;
		}
		
	}
	else {
		// size of spare area
		switch (ptr_device->ecc_bit) {
			case ECC_16BIT:
			case ECC_24BIT:			// 128B/1KB (2B for software)
			case ECC_40BIT:
			case ECC_43BIT:
			case ECC_65BIT:
			case ECC_72BIT:
				increment = 0x80;
				break;
			case ECC_12BIT:			// 32B/512B (6B for software)
				increment = 0x20;
				break;
			case ECC_6BIT:			// 16B/512B (6B for software)
			default:
				increment = 0x10;
				break;
		}

		// configure spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
		rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
		rtd_outl(REG_SRAM_CTL, 0x30 | 0x4); // enable direct access to PP #5

		//rtd_outl(0xb8010000 + offset, spare); // set spare area of first PP
		
		for (i = 0; i < 0x80; i += increment) {
			rtd_outl(0xb8010000 + offset + i, spare); // set spare area of first PP
			// (only first 6 byte is user-defined)
			//REG8(0xb8010004 + i) = 0Xff;
			//REG8(0xb8010005 + i) = 0Xff;
		}
		
		rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access
	}

	return 0;
}

static int nf_read_page_nomap( n_device_type *device, UINT32 page_no, UINT8 *buf, UINT8 chk_all_one)
{
	UINT8 cs;

	if (nf_map_phys_page(device, &cs, &page_no))
		return -1;

	return nf_read_phys_page(device, cs, page_no, buf, chk_all_one);
}

static int nf_read_page( n_device_type *device, UINT32 page_no, UINT8 *buf, UINT8 chk_all_one)
{
	UINT8 cs;

	if (nf_map_phys_page(device, &cs, &page_no))
		return -1;

	return nf_read_phys_page(device, cs, page_no, buf, chk_all_one);
}

static int nf_read_phys_page( n_device_type *device, UINT8 chip_sel, UINT32 page_no, UINT8 *buf, UINT8 chk_all_one)
{
        UINT32 data_unit;
        UINT32 j;

        UINT32 isMLC =0;
        UINT32 retry_allone=0;

	//prints("\n nf_read_phys_page start \n");
	//print_hex(device);
	//prints("\n");
	//print_hex(chip_sel);
	//prints("\n");
	//print_hex(page_no);
	//prints("\n");
	//print_hex(buf);
	//prints("\n");


retry_all_one:

   
	if (chk_all_one) {
		nf_disable_random_mode();
		rtd_outl(REG_BLANK_CHK, 0x1);
		rtd_outl(REG_RMZ_CTRL, 0x0);
	}
	else {
		nf_enable_random_mode();
		rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check

		if (device->ecc_bit == ECC_6BIT || device->ecc_bit == ECC_12BIT) {		
			if (nf_is_random_mode())
				nf_set_random_read(device,0);
		}
		else {
                    isMLC=1;
                    prints("R_RMZ\n");
                for(j=0;j<6;j++){
                    REG32(REG_RMZ_OP) = j;
	            //REG32(REG_RMZ_SEED_L) = 0x6e;
	            //REG32(REG_RMZ_SEED_H) = 0xa3;

                    //REG32(REG_RMZ_SEED_L) = page_no & 0xff;
	            //REG32(REG_RMZ_SEED_H) = (page_no >> 8) & 0xff;

                    REG32(REG_RMZ_SEED_L) = (page_no>>(j * 0x10)) ;
	            REG32(REG_RMZ_SEED_H) = (page_no>>(j * 0x10 + 8));
                }
                REG32(REG_RMZ_OP) = 0x10;
            	            //REG32(REG_RMZ_SEED_L) = 0x6e;
	           // REG32(REG_RMZ_SEED_H) = 0xa3;
                        //REG32(REG_RMZ_OP) = 0x20;
			rtd_outl(REG_RMZ_CTRL, 0x1);
			nf_disable_random_mode();
		}
	}

        // determine read unit size
	data_unit = nf_get_auto_transfer_unit(device->ecc_bit);

	// Set chip select
	//rtd_outl(REG_Chip_En, NF_CHIP_SEL(chip_sel));

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1, 0x80 | ((data_unit >> 8) & 0x3f));	// transfer mode

	//Set page length at auto mode
	rtd_outl(REG_PAGE_LEN, device->PageSize / data_unit);	//Set page length (in unit)

	//Set PP
	rtd_outl(REG_PP_RDY, 0x80);	//NAND --> PP --> DRAM
	rtd_outl(REG_PP_CTL0, 0);
	rtd_outl(REG_PP_CTL1, 0);

	//Set command
	rtd_outl(REG_CMD1, 0x00);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  (page_no & 0xff));
	rtd_outl(REG_PAGE_ADR1,  (page_no >> 8 ) & 0xff);
	rtd_outl(REG_PAGE_ADR2, ((page_no >>16 ) & 0x1f) | (device->addr_mode_rw << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_no >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//Set ECC
	//rtd_outl(REG_MultiChMod, 0x20);
	rtd_outl(REG_MultiChMod, 0x0);
	rtd_outl(REG_ECC_STOP, 0x80);

	//Set DMA
	rtd_outl(REG_DMA_ADR, (((UINT32)buf) & 0x0fffffff) >> 3);	// 8 bytes unit, and must mask first 4 bits
	rtd_outl(REG_DMA_LEN, device->PageSize / 0x200);	// DMA transfer unit is 512 bytes
	rtd_outl(REG_DMA_CONF, 0x02|0x01);
	
	U_FLUSH_CACHE((unsigned long)buf, device->PageSize);
	U_FLUSH_CACHE(PHYS(SPARE_DMA_ADDR), 64);
	sync();
	
	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x80| 0x2);	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 ) {
		//prints("rtd_inl(REG_AUTO_TRIG)");
	};

	//Wait DMA done
	while( rtd_inl(REG_DMA_CONF) & 0x1 ){
		//prints("rtd_inl(REG_DMA_CONF)");
	};

	U_FLUSH_CACHE((unsigned long)buf, device->PageSize);
	U_FLUSH_CACHE(PHYS(SPARE_DMA_ADDR), 64);
	
	// return OK if all data bit is 1 (page is not written yet)
	if ((rtd_inl(REG_BLANK_CHK) & 0x8)==0) {
		prints("nf_read_phys_page all one \n");
		return (DATA_ALL_ONE);
	}

	// poll ECC state (err_not_clr)
	if (rtd_inl(REG_ECC_STATE) & 0x8) {

         if ((isMLC) && (retry_allone == 0)){
            retry_allone++;
            //prints("retry all one\n");
             chk_all_one=1;
            goto retry_all_one;
        }
		prints("read ECC error with page 0x");
		print_hex(page_no);
		prints("\n");
		return -1;
	}

	// Reset chip select
	//REG32(REG_Chip_En) = NF_CHIP_SEL(0);

	return 0;
}

static int nf_dump_phys_page( n_device_type *device, UINT8 chip_sel, UINT32 page_no, UINT32 page_col, UINT8 *buf, UINT8 chk_all_one)
{
    UINT32 data_unit;

	rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check
	rtd_outl(REG_RMZ_CTRL, 0x0);

    // determine read unit size
	data_unit = nf_get_auto_transfer_unit(device->ecc_bit);

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1, 0x80 | ((data_unit >> 8) & 0x3f));	// transfer mode

	//Set page length at auto mode
	rtd_outl(REG_PAGE_LEN, device->PageSize / data_unit);	//Set page length (in unit)

	//Set PP
	rtd_outl(REG_PP_RDY, 0x80);	//NAND --> PP --> DRAM
	rtd_outl(REG_PP_CTL0, 0);
	rtd_outl(REG_PP_CTL1, 0);

	//Set command
	rtd_outl(REG_CMD1, 0x00);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  (page_no & 0xff));
	rtd_outl(REG_PAGE_ADR1,  (page_no >> 8 ) & 0xff);
	rtd_outl(REG_PAGE_ADR2, ((page_no >>16 ) & 0x1f) | (device->addr_mode_rw << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_no >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, (page_col & 0xff));
	rtd_outl(REG_COL_ADR1, (page_col >> 8 ) & 0xff);

	//Set ECC
	//rtd_outl(REG_MultiChMod, 0x60);
	rtd_outl(REG_MultiChMod, 0x40);
	rtd_outl(REG_ECC_STOP, 0x80);

	//Set DMA
	rtd_outl(REG_DMA_ADR, (((UINT32)buf) & 0x0fffffff) >> 3);	// 8 bytes unit, and must mask first 4 bits
	rtd_outl(REG_DMA_LEN, device->PageSize / 0x200);	// DMA transfer unit is 512 bytes
	
	U_FLUSH_CACHE((unsigned long)buf, device->PageSize);
	U_FLUSH_CACHE(PHYS(SPARE_DMA_ADDR), 64);
	sync();

	rtd_outl(REG_DMA_CONF, 0x02|0x01);
	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x80| 0x2);	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 ) {
		//prints("rtd_inl(REG_AUTO_TRIG)");
	};

	//Wait DMA done
	while( rtd_inl(REG_DMA_CONF) & 0x1 ){
		//prints("rtd_inl(REG_DMA_CONF)");
	};

	U_FLUSH_CACHE((unsigned long)buf, device->PageSize);
	U_FLUSH_CACHE(PHYS(SPARE_DMA_ADDR), 64);
	
	// return OK if all data bit is 1 (page is not written yet)
	if ((rtd_inl(REG_BLANK_CHK) & 0x8)==0) {
		prints("nf_read_phys_page end \n");
		return (DATA_ALL_ONE);
	}

	// poll ECC state (err_not_clr)
	if (rtd_inl(REG_ECC_STATE) & 0x8) {
		prints("ECC error with page 0x");
		print_hex(page_no);
		prints("\n");
		return -1;
	}

	// Reset chip select
	//REG32(REG_Chip_En) = NF_CHIP_SEL(0);

	return 0;
}

static int nf_write_page( n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	UINT8 cs;

	if (nf_map_phys_page(device, &cs, &page_no))
		return -1;

	return nf_write_phys_page(device, cs, page_no, buf);
}

static int nf_write_phys_page( n_device_type *device, UINT8 chip_sel, UINT32 page_no, UINT8 *buf)
{
	UINT32 temp;
	UINT32 data_unit;
        UINT32 j;

	if (device->ecc_bit == ECC_6BIT || device->ecc_bit == ECC_12BIT) {		
		//if (nf_is_random_mode())
		nf_enable_random_mode();
			nf_set_random_write(device,0);

		rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check
	}
	else {
        prints("W_RMZ\n");
                for(j=0;j<6;j++){
                    REG32(REG_RMZ_OP) = j;
	            //REG32(REG_RMZ_SEED_L) = 0x6e;
	            //REG32(REG_RMZ_SEED_H) = 0xa3;

                    //REG32(REG_RMZ_SEED_L) = page_no & 0xff;
	            //REG32(REG_RMZ_SEED_H) = (page_no >> 8) & 0xff;

                    REG32(REG_RMZ_SEED_L) = (page_no>>(j * 0x10));
	            REG32(REG_RMZ_SEED_H) = (page_no>>(j * 0x10 + 8));
                }
                REG32(REG_RMZ_OP) = 0x10;
        
		rtd_outl(REG_RMZ_CTRL, 0x1);
		nf_disable_random_mode();
		rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check
	}	

	// determine read unit size
	data_unit = nf_get_auto_transfer_unit(device->ecc_bit);

	// Set chip select
	rtd_outl(REG_Chip_En, NF_CHIP_SEL(chip_sel));

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1, (data_unit >> 8) & 0x3f);	// transfer mode

	//Set page length at auto mode

    if(force_2k==1){
            rtd_outl(REG_PAGE_LEN, 0x800 / data_unit);	//Set page length (in unit)
    }else
	rtd_outl(REG_PAGE_LEN, device->PageSize / data_unit);	//Set page length (in unit)

	//Set PP
	rtd_outl(REG_PP_RDY, 0x0);	//NAND --> PP --> DRAM
	rtd_outl(REG_PP_CTL0, 0x0);
	rtd_outl(REG_PP_CTL1, 0);

	//Set table sram
	//rtd_outl(REG_TABLE_CTL, 0);

	//Set command
	rtd_outl(REG_CMD1, 0x80);
	rtd_outl(REG_CMD2, 0x10);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  page_no & 0xff);
	rtd_outl(REG_PAGE_ADR1,  page_no >> 8 );
	rtd_outl(REG_PAGE_ADR2, ((page_no >>16 ) & 0x1f) | (device->addr_mode_rw << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_no >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//Set ECC
	//rtd_outl(REG_MultiChMod, 0x20);
    rtd_outl(REG_MultiChMod, 0x0);
	rtd_outl(REG_ECC_STOP, 0x80);

	//Set DMA
	rtd_outl(REG_DMA_ADR, (((UINT32)buf) & 0x0fffffff) >> 3);	// 8 bytes unit

        if(force_2k==1){
            rtd_outl(REG_DMA_LEN, 0x800 / 0x200);	// DMA transfer unit is 512 bytes
    }else
	rtd_outl(REG_DMA_LEN, device->PageSize / 0x200);	// DMA transfer unit is 512 bytes
	
	
	U_FLUSH_CACHE((unsigned long)buf, device->PageSize);
	U_FLUSH_CACHE(PHYS(SPARE_DMA_ADDR), 64);
	sync();

	rtd_outl(REG_DMA_CONF, 0x01);
	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x80|(device->PageSize == 512 ? 0x0 : 0x1));	//0x1: write in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;

	//Wait DMA done
	while( rtd_inl(REG_DMA_CONF) & 0x1 );


	// execute command3 register and wait for executed completion
	rtd_outl(REG_POLL_STATUS, (0x6<<1) | 0x1);
	while ( rtd_inl(REG_POLL_STATUS) & 0x1)
		;
	
	temp = rtd_inl(REG_DATA) & 0x1;

	if (temp == 0) {
		/* show '.' in console */
		printf(".");
		return 0;
	}
	/* show '!' in console */
	printf("!(%x) ", page_no);
	return -1;
}

static int nf_erase_block_nomap(n_device_type *device, UINT32 block)
{
	UINT32 page_addr;
	UINT8 cs;

	page_addr = block * pages_per_block;

	if (nf_map_phys_page(device, &cs, &page_addr))
		return -1;

	return nf_erase_phys_block(device, cs, page_addr);
}

static int nf_erase_block(n_device_type *device, UINT32 block)
{
	UINT32 page_addr;
	UINT8 cs;

	page_addr = block * pages_per_block;

	if (nf_map_phys_page(device, &cs, &page_addr)) {
		prints("nf_erase_block -> nf_map_phys_page error!\n");
		return -1;
	}

	return nf_erase_phys_block(device, cs, page_addr);
}

static int nf_erase_phys_block(n_device_type *device, UINT8 chip_sel, UINT32 page_addr)
{
	UINT32 temp;
	//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	
	// Set chip select
	//rtd_outl(REG_Chip_En, NF_CHIP_SEL(chip_sel));
	//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	//Set command
	rtd_outl(REG_CMD1, 0x60);		//Set CMD1
	rtd_outl(REG_CMD2, 0xd0);		//Set CMD2
	rtd_outl(REG_CMD3, 0x70);		//Set CMD3
	//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	//Set address
	//note. page_addr[5:0] is ignored to be truncated as block
	rtd_outl(REG_PAGE_ADR0,  page_addr & 0xff);
	rtd_outl(REG_PAGE_ADR1,  page_addr >> 8);
	rtd_outl(REG_PAGE_ADR2, ((page_addr >>16 ) & 0x1f) | (device->addr_mode_erase << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_addr >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	//Set ECC: Set HW no check ECC, no_wait_busy
	//rtd_outl(REG_MultiChMod, 0x1 << 5);
	//rtd_outl(REG_MultiChMod, 0x30);
	rtd_outl(REG_MultiChMod, 0x10);

	//Enable Auto mode: Set and enable auto mode
	// and wait until auto mode done
	rtd_outl(REG_AUTO_TRIG, 0x8a);
	while ( rtd_inl(REG_AUTO_TRIG) & 0x80)
		;
	
	// check ready/busy pin of NAND flash
	while ((rtd_inl(REG_CTL)&0x40) == 0);

	// execute command3 register and wait for executed completion
	//rtd_outl(REG_POLL_STATUS, (0x6<<1) | 0x1);
	rtd_outl(REG_POLL_STATUS, 0xd);
	while ( rtd_inl(REG_POLL_STATUS) & 0x1)
		;
	
	temp = rtd_inl(REG_DATA) & 0x1;

	if (temp == 0) {
		/* show '/' in console */
		printf("/(%x)", page_addr/pages_per_block);
		return 0;
	}
	/* show 'X' in console */
	printf("X(%x) ", page_addr);
	//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	
	prints("erase fail in page 0x");
	print_hex(page_addr);
	prints("\n");
	return -1;
}

/************************************************************************
 *
 *                          do_erase_n
 *  Description :
 *  -------------
 *  implement the flash erase
 *  (make sure there's enough blocks for do_write_n function)
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_erase_n(void *dev,               //flash device
               unsigned int* dest,     //start of block NO.
               unsigned int   rem_size) //request data length
{
	UINT32 signature;
	n_device_type *device = (n_device_type *)dev;

	UINT32 req_block_no, total_blocks, first_block;
	UINT32 current_block_no = *dest;
	int res;
	UINT8 state;

#ifdef ENABLE_NAND_DRIVER
	// calculate required number of blocks
	req_block_no = rem_size / device->BlockSize;
	if (rem_size % device->BlockSize)
		req_block_no++;

	total_blocks = req_block_no;
	first_block = *dest;

	while (req_block_no != 0)
	{
		// return failed if reach bootcode blocks boundary
		if (current_block_no > (blk_state_len - 1))
			return -1;

		res = get_block_state(current_block_no, &state);
		if (res)
		{
			// block state table has no record (out of range?)
			// try to read first page in block then check data
			// in spare area those load to PP
			res = nf_read_page( device, current_block_no * pages_per_block, (UINT8 *)PAGE_TMP_ADDR, 0);

			// read page failed (restart to find contiguous clean blocks)
			if (res == -1)
			{
				current_block_no++;
				req_block_no = total_blocks;
				first_block = current_block_no;	// re-init start block no
				continue;
			}

			nf_get_spare(0x2, &signature, 0);
			state = signature & 0xff;
		}

		// erase again, even if it's clean.
		// block is good
		//if (state == BLOCK_CLEAN)
		//{
		//	current_block_no++;
		//	req_block_no--;
		//	continue;
		//}

		// bad block (restart to find contiguous clean blocks)
		if((state == BLOCK_BAD) || (state == BLOCK_ENVPARAM_MAGICNO))
		{
			current_block_no++;
			req_block_no = total_blocks;
			first_block = current_block_no;	// re-init start block no
			continue;
		}
		else
		{
			// if erase current_block_no fail, mark this block as fail
			if (nf_erase_block(device, current_block_no) < 0)
			{
				// write 'BAD_BLOCK' signature to spare cell
				// (restart to find contiguous clean blocks)
				nf_set_spare(BLOCK_BAD, 0);
				nf_write_page( device, current_block_no * pages_per_block, (UINT8 *)PAGE_TMP_ADDR);

				set_block_state(current_block_no, BLOCK_BAD);
				current_block_no++;
				req_block_no = total_blocks;
				first_block = current_block_no;	// re-init start block no
				continue;
			}
			else
			{
				// block is good after erase
				set_block_state(current_block_no, BLOCK_CLEAN);
				current_block_no++;
				req_block_no--;
			}// end of erase block success
		}

	}// end of while (req_block_no != 0)
#endif

	// return start block available to write
	return first_block;

}





/**********************************************************************
** built by hcy for bad block handle
**
***********************************************************************/
static int nf_BB_handle( n_device_type *device, UINT32 current_block_no)
{
	UINT32 page_no;
	UINT8 cs;
	int i;
#ifdef ENABLE_NAND_DRIVER

	page_no = current_block_no * pages_per_block;
#if 0 /* we dont use bbt mapping anymore 20110610 */
	if (nf_map_page(device, &cs, &page_no))
	{
		prints("BB_handle: map_phys err \n");
		return -1;
	}
	/* there should be existed bbt */
	for (i = 0 ; i<BBT_LENGTH; i++)
	{
		if(bbt[i].bad_block == BB_INIT && bbt[i].remap_block !=RB_INIT)
		{
			bbt[i].BB_die = cs;
			bbt[i].bad_block = page_no/pages_per_block;

			printf("i =0x%x BB_die=0x%x ", i, bbt[i].BB_die);
		printf("bad_block=0x%x ", bbt[i].bad_block);
		printf("RB_die=0x%x ", bbt[i].RB_die);
		printf("remap_block=0x%x \n", bbt[i].remap_block);
			break;

		}
	}
	if (i == BBT_LENGTH) {
		prints("BB_handle:no free remap blk\n");
		return -1;
	}




	/* update BBT */
	write_bbt(device);
#endif /* we dont use bbt mapping anymore 20110610 */

	/* mark the block as BB */
	nf_set_spare(BLOCK_BAD, 0);
	nf_write_phys_page(device, cs, page_no, (UINT8 *)PAGE_TMP_ADDR);

#endif

	return 0;


}
/************************************************************************
 *
 *                          do_erase_map
 *  Description :
 *  -------------
 *  implement the flash erase with remapping feature
 *  (make sure there's enough blocks for do_write_map function)
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_erase_map(void *dev,               //flash device
               unsigned int* dest,     //start of block NO.
               unsigned int   rem_size) //request data length
{
	UINT32 signature;
	n_device_type *device = (n_device_type *)dev;

	UINT32 req_block_no, total_blocks, first_block;
	UINT32 current_block_no = *dest;
	int res;
	UINT8 state;

#ifdef ENABLE_NAND_DRIVER
	// calculate required number of blocks
	req_block_no = rem_size / device->BlockSize;
	if (rem_size % device->BlockSize)
		req_block_no++;

	total_blocks = req_block_no;
	first_block = *dest;

	while (req_block_no != 0)
	{
		// return failed if reach  blocks boundary
		if (current_block_no > (blk_state_len - 1))
			return -1;


		// if erase current_block_no fail, mark this block as fail
		if (nf_erase_block(device, current_block_no) < 0)
		{
			printf("do_erase_map :nf_erase_block err , BB handle \n");
			// write 'BAD_BLOCK' signature to spare cell
			nf_BB_handle( device, current_block_no);

			continue;
		}
		else
		{
			current_block_no++;
			req_block_no--;
		}// end of erase block success


	}// end of while (req_block_no != 0)
#endif
	// return start block available to write
	return first_block;

}

#ifdef DUMP_NAND_FLASH
UINT32 dst_data_addr = (0x03000000 - UBOOT_DDR_OFFSET), dst_spare_addr = (0x03200000 - UBOOT_DDR_OFFSET);
n_device_type *devicetype;

static UINT8 NF_read_to_PP_new(UINT32 col_addr, UINT32 page_addr)
{
	UINT8 addr_mode;
	UINT32 data_unit;

	// determine read unit size
	data_unit = nf_get_auto_transfer_unit(devicetype->ecc_bit);

	// Set chip select
	rtd_outl(REG_Chip_En, NF_CHIP_SEL(0));

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1,0x80 | ((data_unit >> 8) & 0x3f));	// transfer mode, 0x200 bytes

	//set page length at auto mode
	rtd_outl(REG_PAGE_LEN, devicetype->PageSize / data_unit);

	rtd_outl(REG_PP_RDY, 0x80);		// set read_by_pp
	rtd_outl(REG_PP_CTL0, 0x2);		// Reset PP
	rtd_outl(REG_PP_CTL1, 0);			// PP starting address at 0

	rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check

	//set command
	rtd_outl(REG_CMD1, 0);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  page_addr & 0xff);
	rtd_outl(REG_PAGE_ADR1,  page_addr >> 8 );
	addr_mode = devicetype->addr_mode_rw;
	rtd_outl(REG_PAGE_ADR2, ((page_addr >>16 ) & 0x1f) | (addr_mode << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_addr >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, col_addr & 0xff);
	rtd_outl(REG_COL_ADR1, col_addr >> 8);

	//ste ECC
	//rtd_outl(REG_MultiChMod, 0x20);
	rtd_outl(REG_MultiChMod, 0x0);
	rtd_outl(REG_ECC_STOP, 0x80);		// non-stop

	//no DMA (data remains in PP)
	rtd_outl(REG_DMA_CONF, 0);

	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x82);	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;

	if (rtd_inl(REG_BLANK_CHK) & 0x2)
		return 1;
	else
		// get ECC status
		return rtd_inl(REG_ECC_STATE);
}


static void NF_dump_flash_random(UINT32 dst_addr, UINT32 src_page, UINT32 page_len)
{
	UINT32 i, j;
	UINT32 cs, result;
	UINT32 page_addr;
	UINT32 dst_data_addr, dst_spare_addr;

	prints("dump nand flash from page No.");
	print_hex(src_page);
	prints(" to addr = 0x");
	print_hex(dst_addr);
	prints(" with page counts = 0x");
	print_hex(page_len);
	prints("\n");

	dst_data_addr = dst_addr;
	dst_spare_addr = dst_addr + devicetype->PageSize;
	for (i = 0; i < page_len; i++) {
		// map to physical page
		page_addr = src_page + i;
		if (nf_map_phys_page(devicetype, &cs, &page_addr)) {
			prints("nf_map_phys_page error\n");
			break;
		}

		// read each (512B+16B) within one page
		//for (j = 0; j < devicetype->PageSize / 512; j++) {
			// update col address
			nf_set_random_read(devicetype, 0);


			if (nf_map_phys_page(devicetype, &cs, &page_addr))
			{
				prints("nf_map_phys_page error\n");
				continue;
			}

			//result = NF_read_to_PP_new(j * 512, page_addr);
			nf_read_page(devicetype, page_addr, (UINT8 *)PAGE_TMP_ADDR, 0);
			//nf_get_spare(0x2, &temp, 0);
                        //prints("page_addr: \n");

			if (result & 0x8) {
				prints("col_addr: ");
				//print_hex(j * 512);
				prints(", page_addr: ");
				//print_hex(page_addr);
				prints(", read ecc error\n");
				return;
			}

#if 1
			// copy data bytes to destination
			//REG32(REG_PP_RDY) = 0; // disable read_by_pp
			//REG32(REG_SRAM_CTL) = 0x30; // enable direct access to PP or table SRAM
			copy_memory(dst_data_addr, PAGE_TMP_ADDR, devicetype->PageSize);
			//REG32(REG_SRAM_CTL) = 0x0; // disable direct access

#endif

			// copy spare bytes to destination
			rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
			rtd_outl(REG_SRAM_CTL, 0x34); // enable direct access to PP or table SRAM
			copy_memory(dst_spare_addr, REG_BASE_ADDR, 64);
			rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access
		//}

		// move to next destination
		j = (devicetype->PageSize / 512) * (512 + 16);
		dst_data_addr += j;
		dst_spare_addr += j;
	}

    prints("finish. ");
}

static UINT8 NF_read_to_PP_small(UINT32 page_addr, u32 ddr_addr, UINT32 spare_addr)
{
	UINT8 addr_mode, res = 0;
	UINT32 j;
	UINT32 buf;
	UINT32 data_unit = 512;

	buf = ddr_addr;


	if (devicetype == NULL)
		return (-1);




        // determine read unit size
	data_unit = nf_get_auto_transfer_unit(devicetype->ecc_bit);

	// Set chip select
	rtd_outl(REG_Chip_En, NF_CHIP_SEL(0));

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1, 0x80 | ((data_unit >> 8) & 0x3f));	// transfer mode

	//set page length at auto mode
	rtd_outl(REG_PAGE_LEN, devicetype->PageSize / data_unit);

	rtd_outl(REG_PP_RDY, 0x80);		// set read_by_pp
	//REG32(REG_PP_CTL0) = 0;			// enable PP
	rtd_outl(REG_PP_CTL1, 0);			// PP starting address at 0

	rtd_outl(REG_TABLE_CTL, 0);		// disable table SRAM

	rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check

	//set command
	rtd_outl(REG_CMD1, 0);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  page_addr & 0xff);
	rtd_outl(REG_PAGE_ADR1,  page_addr >> 8 );
	rtd_outl(REG_PAGE_ADR2, ((page_addr >>16 ) & 0x1f) | (devicetype->addr_mode_rw << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_addr >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//ste ECC
	//rtd_outl(REG_MultiChMod, 0x20);
    rtd_outl(REG_MultiChMod, 0x0);
	rtd_outl(REG_ECC_STOP,0x80);		// non-stop

	//no DMA (data remains in PP)
	rtd_outl(REG_DMA_CONF, 0);

	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x80 | 3);	//0x3: read in 512B page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;

	// check if all data bit is 1 (data is not written yet)
	if (rtd_inl(REG_BLANK_CHK) & 0x2)
		res = DATA_ALL_ONE;
	else
		res = rtd_inl(REG_ECC_STATE) & 0x8;	// get ECC result (ecc_not_clr)

	//Reset PP
	rtd_outl(REG_PP_CTL0, 0x2);


	// get 512B data
	rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
	rtd_outl(REG_SRAM_CTL, 0x10); // enable direct access to PP or table SRAM

	for (j = 0; j < 512; j += 4, buf += 4)
		rtd_outl(buf, rtd_inl(REG_BASE_ADDR + j));

	rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access

	// read spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
	rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
	rtd_outl(REG_SRAM_CTL, 0x14); // enable direct access to PP #3
	for (j = 0; j < 16; j+=4)
	{
		rtd_outl((spare_addr + j) , rtd_inl(0xb8010000 + j)); // set spare area of first PP
	}
	rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access

	return res;
}
/*
static UINT8 NF_read_to_PP_large(UINT32 page_addr, UINT32 ddr_addr, UINT32 spare_addr)
{
		UINT8 addr_mode, res = 0;
		UINT32 i, j;
		UINT32 counter, buf;
		UINT32 spare_idx;
		UINT32 data_unit;
		UINT8 second_pp_idx;

		// determine read unit size
		data_unit = nf_get_auto_transfer_unit(devicetype->ecc_bit);

		// determine second index of PP when read to PP
		second_pp_idx = (devicetype->ecc_bit == ECC_24BIT) ? 0x1 : 0x2;

		counter = devicetype->PageSize / 512;	// number of 1KB read of one page
		buf = ddr_addr;

		// Set chip select
		rtd_outl(REG_Chip_En, NF_CHIP_SEL(0));

		//Set data transfer count, data transfer count must be 0x200 at auto mode
		//Set SRAM path and access mode
		rtd_outl(REG_DATA_TL0, data_unit & 0xff);
		rtd_outl(REG_DATA_TL1, 0x80 | ((data_unit >> 8) & 0x3f)); // transfer mode, 0x200 bytes

		//set page length at auto mode
		rtd_outl(REG_PAGE_LEN, 1);

		rtd_outl(REG_PP_RDY, 0x80);		// set read_by_pp
		rtd_outl(REG_PP_CTL0, 0x2);		// Reset PP
		rtd_outl(REG_PP_CTL1, 0); 		// PP starting address at 0

		//REG32(REG_TABLE_CTL) = 0; 	// disable table SRAM

		rtd_outl(REG_BLANK_CHK, 0x1); 	// enable blank check

		//set command
		rtd_outl(REG_CMD1, 0);
		rtd_outl(REG_CMD2, 0x30);
		rtd_outl(REG_CMD3, 0x70);

		//Set address
		rtd_outl(REG_PAGE_ADR0,	page_addr & 0xff);
		rtd_outl(REG_PAGE_ADR1,	page_addr >> 8 );
		addr_mode = devicetype->addr_mode_rw);
		rtd_outl(REG_PAGE_ADR2, ((page_addr >>16 ) & 0x1f) | (addr_mode << 5);)
		rtd_outl(REG_PAGE_ADR3, ((page_addr >> 21) & 0x7) << 5);
		rtd_outl(REG_COL_ADR0, 0);
		rtd_outl(REG_COL_ADR1, 0);

		//ste ECC
		rtd_outl(REG_MultiChMod, 0x20);
		rtd_outl(REG_ECC_STOP,0x80); 	// non-stop

		//no DMA (data remains in PP)
		//REG32(REG_DMA_ADR) = DDR_BASE>>3; // 8 bytes unit
		//REG32(REG_DMA_LEN) = 1024 >> 9;		// 2*512 bytes
		rtd_outl(REG_DMA_CONF,0);

		//Enable Auto mode
		rtd_outl(REG_AUTO_TRIG, 0x82);	//0x2: read in 2K page size
		while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
			;

		if ((rtd_inl(REG_BLANK_CHK) & 0x2) != 1)	// not all data bit is 1
			// get ECC status
			res = (rtd_inl(REG_ECC_STATE) >> 3) & 0x8;

		// get first 1K data
	/*
		for (i = 0; i < 2; i++)
		{
			REG32(REG_READ_BY_PP) = 0; // disable read_by_pp
			REG32(REG_SRAM_CTL) = 0x30 | i; // enable direct access to PP or table SRAM

			for (j = 0; j < 512; j += 4, buf += 4)
				REG32(buf) = REG32(REG_BASE_ADDR + j);

			REG32(REG_SRAM_CTL) = 0x0; // disable direct access
		}
	*/
	/*
		{
			// get 512B data
			rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
			rtd_outl(REG_SRAM_CTL, 0x10); // enable direct access to PP or table SRAM

			for (j = 0; j < 512; j += 4, buf += 4)
				rtd_outl(buf, rtd_inl(REG_BASE_ADDR + j));

			rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access
		}

		counter--;

		// read spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
		rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
		rtd_outl(REG_SRAM_CTL, 0x14); // enable direct access to PP #3
		for (spare_idx = i = 0; i < 16; i+=4)
		{
			rtd_outl(spare_addr + spare_idx, rtd_inl(0xb8010000 + i)); // set spare area of first PP
			spare_idx+=4;
		}
		rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access

		// get other data
		while (counter)
		{
			//Reset PP
			rtd_outl(REG_PP_CTL0, 0x2);

			//re-enable PP to read
			rtd_outl(REG_PP_RDY, 0x80);

			rtd_outl(REG_BLANK_CHK, 0x1); 	// enable blank check

			//Enable Auto mode
			rtd_outl(REG_AUTO_TRIG, 0x80 | 0x4);	//0x4: use D read
			while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
				;

			if ((rtd_inl(REG_BLANK_CHK) & 0x2) != 1)	// not all data bit is 1
				// accumulate ECC status
				res += (rtd_inl(REG_ECC_STATE) >> 3) & 0x8;

			// get 1K data
	/*
			for (i = 0; i < 2; i++)
			{
				REG32(REG_READ_BY_PP) = 0; // disable read_by_pp
				REG32(REG_SRAM_CTL) = 0x30 | i; // enable direct access to PP or table SRAM

				for (j = 0; j < 512; j += 4, buf += 4)
					REG32(buf) = REG32(REG_BASE_ADDR + j);

				REG32(REG_SRAM_CTL) = 0x0; // disable direct access
			}
	*/
	/*
			{
				// get 512B data
				rtd_outl(REG_PP_RDY,0); // disable read_by_pp
				rtd_outl(REG_SRAM_CTL, 0x10); // enable direct access to PP or table SRAM

				for (j = 0; j < 512; j += 4, buf += 4)
					rtd_outl(buf,rtd_inl(REG_BASE_ADDR + j));

				rtd_outl(REG_SRAM_CTL,0x0); // disable direct access

			}

			// read spare area data in PP (16 byte: 6 byte for user-defined, 10 byte for ECC)
			rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
			rtd_outl(REG_SRAM_CTL, 0x14); // enable direct access to PP #3
			for (i = 0; i < 16; i+=4)
			{
				rtd_outl(spare_addr + spare_idx, rtd_inl(0xb8010000 + i)); // set spare area of first PP
				spare_idx+=4;
			}
			rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access

			counter--;
		}

		//Reset PP
		rtd_outl(REG_PP_CTL0, 0x2);

		// return OK if all data bit is 1 (page is not written yet)
		if (rtd_inl(REG_BLANK_CHK) & 0x2)
			return 0;

		// return ECC result
		return res;


}*/

static void NF_dump_flash_sequential(UINT32 dst_addr, UINT32 src_page, UINT32 page_len)
{
	prints("NF_dump_flash_sequential... \n");

	UINT32 i, j;
	UINT32 cs, result;
	UINT32 page_addr;
	UINT32 dst_data_addr;

	prints("dump nand flash from page No.");
	print_hex(src_page);
	prints(" to addr = 0x");
	print_hex(dst_addr);
	prints(" with page counts = 0x");
	print_hex(page_len);
	prints("\n");

	// set to 40 bit for reading spare data.
	REG32(REG_ECC_SEL) = ECC_40BIT;

	dst_data_addr = dst_addr;
	
	for (i = 0; i < page_len; i++) {
		// map to physical page
		page_addr = src_page + i;
		if (nf_map_phys_page(devicetype, &cs, &page_addr)) {
			prints("nf_map_phys_page error\n");
			break;
		}

		prints("read page 0x");
		print_hex(page_addr);
		prints("\n");

		// dump flash usage...
		for (j=0 ; j<9 ; j++) {
		//if(page_addr==1)
                    //continue;

			//result = nf_dump_phys_page(devicetype, cs, page_addr, j*(1024+72), (UINT8 *)PAGE_TMP_ADDR, 0);
			result = nf_dump_phys_page(devicetype, cs, page_addr, j*1024, (UINT8 *)PAGE_TMP_ADDR, 0);
                        //result =  nf_read_page(devicetype, page_addr, (UINT8 *)PAGE_TMP_ADDR, 0);
			if (result == -1) {
				prints("page:0x");
				print_hex(page_addr);
				prints(", col:0x");
				print_hex(j);
				prints(" read ecc error\n");
				return;
			}
			if ( j != 8 ) {

				//copy_memory(dst_data_addr, PAGE_TMP_ADDR, 8192);
				//dst_data_addr += 8192;
				
				copy_memory(dst_data_addr, PAGE_TMP_ADDR, 1024);
				dst_data_addr += 1024;
				/*
				rtd_outl(REG_PP_RDY, 0); // disable read_by_pp
				rtd_outl(REG_SRAM_CTL, 0x34); // enable direct access to PP or table SRAM
				copy_memory(dst_data_addr, REG_BASE_ADDR, 72);
				rtd_outl(REG_SRAM_CTL, 0x0); // disable direct access
				dst_data_addr += 72;
				*/
			}
			else {
				copy_memory(dst_data_addr, PAGE_TMP_ADDR, 392);
				dst_data_addr += 392;
				//copy_memory(dst_data_addr, PAGE_TMP_ADDR, 912);
				//dst_data_addr += 912;
			}
		}			
	}
}

void NF_dump_flash(n_device_type *device, UINT32 dst_addr, UINT32 src_page, UINT32 page_len)
{

	devicetype = device;
	if (nf_is_random_mode())
		NF_dump_flash_random(dst_addr, src_page, page_len);
	else
		NF_dump_flash_sequential(dst_addr, src_page, page_len);
}


#endif

/************************************************************************
 *
 *                          do_write
 *  Description :
 *  -------------
 *  implement the flash write
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_n(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int signature,
               const unsigned int page_offset)
{
	n_device_type *device = (n_device_type *)dev;
	int data_len = rem_size;
	UINT32 current_page;
	UINT8 * data_ptr = array_ptr;
	int ith;
	UINT32 end_blk;
	UINT32 page_counter = 0;	// ith page of the data
	UINT32 spare;
	UINT32 temp;
	UINT32 fail_counter = 0;
	UINT32 tmp_page_size;
#ifdef ENABLE_NAND_DRIVER

	if (device->ecc_bit > ECC_12BIT && signature == BLOCK_HWSETTING) {
		// since only 2k per page could be access without DMA, such that hwsetting should be 2k per page.
		tmp_page_size = 2048;
	}
	else {
		tmp_page_size = device->PageSize;
	}
	
	if (page_offset > (device->BlockSize / device->PageSize)) {
		printf("[%s] invalid page offset: %x\n", __FUNCTION__, page_offset);
		return -1;
	}

	prints("do_write_n: signature=0x");
	print_hex(signature);
	prints("\n");
	
	printf("signature=0x%x \n", signature);//cy test


/* all need do map  */
	//	return do_write_map(dev, array_ptr, dest, rem_size,signature);

	if (page_offset == 0) {
		//erase blocks we need to save data
		ith = do_erase_n(dev, dest, rem_size);

		if (ith == -1) {
			prints("erase fail.\n");
			return -1;	// no more blocks available
		}
	}
	else
		ith = *dest;	// skip erase blocks

	current_page = ((UINT32)ith) * pages_per_block + page_offset;
	
	//prints("set spare with REG32(REG_SPR_DDR_CTL) = ");
	//print_hex(REG32(REG_SPR_DDR_CTL));
	//prints("\n");

	// write data to nand flash pages
	while (data_len > 0)
	{
		// set signature to pp buffer and wait for writing to spare cell
		// (in the spare area first 2B is signature , following 2B are page_counter)

		// since spare data only got 2B, removing page_counter for useless.
		//spare = (signature & 0x0000ffff) | ((page_counter & 0xffff) << 16);
		//spare = signature & 0x0000ffff;
		spare = (signature & 0x000000ff) | (((page_counter/pages_per_block) & 0xff) << 8);
		nf_set_spare(spare, 0);

		if ( nf_write_page( device, current_page, data_ptr) < 0)
		{
			UINT32 current_block_no = current_page / pages_per_block;

			// erase whole block to write signature to spare cell
			nf_erase_block(device, current_block_no);

			//write 'BAD_BLOCK' signature to spare cell
			prints("write error, set BAD_BLOCK\n");
			nf_set_spare(BLOCK_BAD, 0);
			set_block_state(current_block_no, BLOCK_BAD);

			// perform writing
			nf_write_page( device, current_block_no * pages_per_block, (UINT8 *)PAGE_TMP_ADDR);

			if (page_offset != 0) {
				prints("page_offset != 0, return -1\n");
				return -1;	// just return failed (no retry)
			}

			// redo all operation from start
			ith = do_erase_n(dev, dest, rem_size);
			if (ith == -1) {
				prints("ith==-1, return -1\n");
				return -1;	// no more blocks available
			}

			data_len = rem_size;
			current_page = ((UINT32)ith) * pages_per_block;
			data_ptr = array_ptr;
			page_counter = 0;
			continue;
		}
		else
		{
			if (verify_after_write ) {
				// clear buffer
				set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, tmp_page_size);

				// read page again
				nf_read_page(device, current_page, (UINT8 *)PAGE_TMP_ADDR, 0);
				nf_get_spare(0x2, &temp, 0);

				//add by Angus for test read to SRAM mode
				#if 0
				if(temp != spare)
				{
					rtprintf("spare:0x%x verify fail with 0x%x\n", spare, temp);

					spare_tmp = REG32(REG_SPR_DDR_CTL);	// save original setting
					REG32(REG_SPR_DDR_CTL) = REG32(REG_SPR_DDR_CTL) & (~0x20000000);	// turn off spare to DDR

					nf_read_to_PP(device, current_page);
					
					//nf_read_to_PP_test(device, current_page);
					//NF_read_to_PP_large(device, cs, current_page, 0x84400000, 0x84200040);
					REG32(REG_PP_RDY) = 0; // disable read_by_pp
					REG32(REG_SRAM_CTL) = 0x30 | 4; // enable direct access to PP #0
					rtprintf("spare in sram = 0x%x \n", REG32(REG_PAGE_ADR0));
					REG32(REG_SRAM_CTL) = 0x0; // disable direct access

					REG32(REG_SPR_DDR_CTL) = spare_tmp;
				}
				#endif

				// verify data is the same
				if ((temp != spare) || compare_memory(data_ptr, (UINT8 *)PAGE_TMP_ADDR, tmp_page_size)) {
					prints("verify fail in spare: 0x");
					print_hex(spare);
					prints(", to temp = 0x");
					print_hex(temp);
					prints("\n");
					
					//xdump("[read]", PAGE_TMP_ADDR, device->PageSize);
					//ints("\n");
					
					//int_hex(spare);
					//ints("\n");
					//xdump("[data]", data_ptr, device->PageSize);
					
					if (page_offset != 0)
						return -1;	// just return failed (no retry)

					if (fail_counter > 3) {
						prints("verify failed\n");
						print_val((UINT32)data_ptr,4);
						prints("\n");
				                print_val(PAGE_TMP_ADDR,4);
						return -1;
					}

					fail_counter++;
					prints("f");
					// redo all operation from start
					ith = do_erase_n(dev, dest, rem_size);
					if (ith == -1)
						return -1;      // no more blocks available

					data_len = rem_size;
					current_page = ((UINT32)ith) * pages_per_block;
					data_ptr = array_ptr;
					page_counter = 0;
					continue;
				}
			}

			set_block_state(current_page / pages_per_block, signature);
			data_ptr += tmp_page_size;
			data_len -= tmp_page_size;
			// increment current_page if not finished
			if (data_len > 0)
				current_page ++;
		}

		page_counter++;
	}
/*
	// adjust first block available for env
	end_blk = current_page / pages_per_block;
	if (end_blk >= fileflash_phys_start )
		fileflash_phys_start = end_blk + 1;
*/
	*dest = ith;

#endif
	return current_page;
}
/************************************************************************
 *
 *                          do_write_map
 *  Description :
 *  -------------
 *  implement the flash write with remapping feature
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_map(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int signature)
{
	n_device_type *device = (n_device_type *)dev;
	int data_len = rem_size;
	UINT32 current_page;
	UINT8 * data_ptr = array_ptr;
	int ith;
	UINT32 end_blk;
	UINT32 page_counter = 0;	// ith page of the data
	UINT32 spare;
	UINT32 temp;
	UINT32 fail_counter = 0;
	int     i=0;
	UINT32 current_block_no;
#ifdef ENABLE_NAND_DRIVER
	//erase blocks we need to save data
	ith = do_erase_map(dev, dest, rem_size);

	if (ith == -1)
		return -1;	// no more blocks available

	current_page = ((UINT32)ith) * pages_per_block;
	current_block_no = current_page / pages_per_block;
	printf("current_page=0x%x current_block_no=0x%x \n", current_page, current_block_no);
	// write data to nand flash pages
	while (data_len > 0)
	{

		// set signature to pp buffer and wait for writing to spare cell
		// (in the spare area first 2B is signature , following 2B are page_counter)
		spare = (signature & 0x0000ffff) | ((page_counter & 0xffff) << 16);
		nf_set_spare(spare, 0);
		i++;

		if ( nf_write_page( device, current_page, data_ptr) < 0 /*|| i==2*/)
		{

			printf("test BB handle current_page=0x%x current_block_no=0x%x \n", current_page, current_block_no);
			// erase whole block to write signature to spare cell
			nf_erase_block(device, current_block_no);

			// write 'BAD_BLOCK' signature to spare cell
			nf_BB_handle( device, current_block_no);

			// redo all operation from start
			ith = do_erase_map(dev, dest, rem_size);
			if (ith == -1)
				return -1;	// no more blocks available

			data_len = rem_size;
			current_page = ((UINT32)ith) * pages_per_block;
			data_ptr = array_ptr;
			page_counter = 0;

			continue;
		}
		else
		{


			if (verify_after_write) {
				// perform writing
				set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, device->PageSize);

				// read page again
				nf_read_page(device, current_page, (UINT8 *)PAGE_TMP_ADDR, 0);
				nf_get_spare(0x2, &temp, 0);

				// verify data is the same
				if ((temp != spare) || compare_memory(data_ptr, (UINT8 *)PAGE_TMP_ADDR, device->PageSize)) {
					if (fail_counter > 3) {
						prints("verify failed\n");
						print_val((UINT32)data_ptr,4);
						prints("\n");
						print_val(PAGE_TMP_ADDR,4);
						return -1;
					}
					/* leave to deciding if need BB_handle



					*/
					fail_counter++;
					prints("f");

					// redo all operation from start
					ith = do_erase_map(dev, dest, rem_size);
					if (ith == -1)
						return -1;      // no more blocks available

					data_len = rem_size;
					current_page = ((UINT32)ith) * pages_per_block;
					data_ptr = array_ptr;
					page_counter = 0;

					continue;
				}
                        }

			set_block_state(current_page / pages_per_block, signature);
			data_ptr += device->PageSize;
			data_len -= device->PageSize;
			// increment current_page if not finished
			if (data_len > 0)
				current_page ++;
		}

		page_counter++;
	}

	*dest = ith;
#endif
	return current_page;
}

/************************************************************************
 *
 *                          do_identify_n
 *  Description :
 *  -------------
 *  implement the identyfy flash type
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_identify_n(void **dev)
{
	UINT32 chipid = 0;
	UINT32 idx, i;
	UINT64 die_size;
	UINT8 id5, id6;
	UINT32 BlockSize;

	int retry = 0;

	prints("do_identify_n start... \n");
	
#ifdef ENABLE_NAND_DRIVER
	blocks_per_flash = total_chip_num = 0;
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	if (nf_ctrler_init()) {
//rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
		prints("nf_ctrler_init failed\n");
		return -1;
	}
#if 0
	REG32(0xb80008C8) = 0x00000030;

	REG32(0xb8000800) = 0xF0F00000;
	REG32(0xb8000804) = 0x00F00000;
	REG32(0xb8000808) = 0x00F00000;
	REG32(0xb800080C) = 0x00F0F0F0;
	REG32(0xb8000810) = 0xF00000F0;
	REG32(0xb8000814) = 0xF00000F0;
	REG32(0xb8000818) = 0x0000F0F0;
	
	REG32(0xb8000214) = 0x100;
	
	REG32(0xb8010130) = 0x1E; 
	REG32(0xb8010234) = 0x1;   
	REG32(0xb8010238) = 0x1;
	   
	REG32(0xb801023c) = 0x1;  
	REG32(0xb801027c) = 0x20; 
	REG32(0xb8010228) = 0x00; 
#endif
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	for (i = die_size = 0 ; i < NF_CHIP_SEL_NUM; i++)
	{
		// reset chip id
		chipid = 0;
		id5 = id6 = 0;

		// switch each chip select
		REG32(REG_Chip_En) = NF_CHIP_SEL(i);

		/***************************************
		 * get maker ID and device ID from flash
		 * to DDR
		 ***************************************/
		//modify by angus
		//nf_read_id(PAGE_TMP_ADDR, 6);
		// read 3 times for timing issue.
		nf_read_id(PAGE_TMP_ADDR, 8);
		nf_read_id(PAGE_TMP_ADDR, 8);
		nf_read_id(PAGE_TMP_ADDR, 8);

		//get maker id and device id from DDR
		chipid = rtd_inl(PAGE_TMP_ADDR);

		prints("chipid = 0x");
		print_hex(chipid);
		prints("\n");

		if (chipid != 0) {
			//modify by angus
			//printf("[%x %x]\n", chipid, REG8(PAGE_TMP_ADDR+4));
			printf("[%x %x]\n", chipid, rtd_inl(PAGE_TMP_ADDR+7));
		}
		else {
			if (!retry) {
				retry = 1;
				i --;
			}
			else {
				retry = 0;
			}
			continue;
		}
		/***************************************
		 * compare maker id and device ID with
		 * IDs in nand flash table
		 ***************************************/
		for (idx = 0; idx < DEV_SIZE_N; idx++)
		{
			/* find the match flash brand */
			if (n_device[idx].read_id_len == 2)
			{
				if ((chipid & 0xffff) != n_device[idx].id)
					continue;
			}
			else if (n_device[idx].read_id_len == 4)
			{
				if (chipid != n_device[idx].id)
					continue;
			}
			else if (n_device[idx].read_id_len == 5)
			{
				//modify by angus
				//id5 = REG8(PAGE_TMP_ADDR + 4);
				id5 = rtd_inb(PAGE_TMP_ADDR + 4);

#if 1
				if ((chipid != n_device[idx].id) || (id5 != n_device[idx].id5))
					continue;

#endif
			}
			else if (n_device[idx].read_id_len == 6)
			{
				//modify by angus
				//id5 = REG8(PAGE_TMP_ADDR + 4);
				//id6 = REG8(PAGE_TMP_ADDR + 5);
				id5 = rtd_inb(PAGE_TMP_ADDR + 4);
				id6 = rtd_inb(PAGE_TMP_ADDR + 5);
				prints("chipid: ");
				print_hex(chipid);
				prints("\n");
				print_hex(id5);
				prints("\n");
				print_hex(id6);
				prints("\n");
				
				if ((chipid != n_device[idx].id) ||
					(id5 != n_device[idx].id5) ||
					(id6 != n_device[idx].id6))
						continue;
			}
			else	// unknown length ??
				continue;


			*dev = (void *)&n_device[idx];
			ptr_device = &n_device[idx];

			// calculate block number per flash and page size per block
			pages_per_block  = n_device[idx].BlockSize / n_device[idx].PageSize;
			die_size = n_device[idx].size / n_device[idx].num_chips;
			pages_per_chip = die_size / n_device[idx].PageSize;
			total_chip_num++;
			blocks_per_flash += die_size / n_device[idx].BlockSize;

			// set ECC bit level
			((n_device_type *)(*dev))->ecc_bit = n_device[idx].ecc_bit;
			
			prints("pages_per_block = ");
			print_hex(pages_per_block);
			prints("\n");
			
			prints("blocks_per_flash = ");
			print_hex(blocks_per_flash);
			prints("\n");

			prints("ecc bit = ");
			print_hex(((n_device_type *)(*dev))->ecc_bit);
			prints("\n");
			break;
		}

                if (idx == DEV_SIZE_N) { // not found
            //modify by angus
			//printf("[%x %x]\n", chipid, REG8(PAGE_TMP_ADDR+4));
			printf("[%x %x]\n", chipid, rtd_inb(PAGE_TMP_ADDR+4));
		}
	}
rtprintf("%s %s %d, chipid=0x%08x\n", __FILE__, __FUNCTION__, __LINE__, chipid);
	// cannot find any matched ID
	if (total_chip_num == 0)
	{
rtprintf("%s %s %d, total_chip_num=%d\n", __FILE__, __FUNCTION__, __LINE__, total_chip_num);
		*dev = 0;
		return -1;
	}

	// chip select
	REG32(REG_Chip_En) = NF_CHIP_SEL(0);
	
	BlockSize = ((n_device_type *)(*dev))->BlockSize;
rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	// set bootcode area size according to different block size
	if (BlockSize <= 0x40000)		// < 256KB
	{
		//nand_bootcode_area_size = NAND_BOOTCODE_AREA_12MB;
		nand_bootcode_area_size = 14*BlockSize; // BBT+HWset+FSBL
		nand_bootcode_area_size += NAND_BOOTCODE_768KB;
#ifdef Config_FSBL_OS_TRUE
		nand_bootcode_area_size += NAND_BOOTCODE_768KB;
#endif
#ifdef Config_BL31_TRUE
		nand_bootcode_area_size += 4*BlockSize;
		nand_bootcode_area_size += 8*BlockSize; // RSA FW+RSA TEE
#endif
	}
	else if (BlockSize <= 0x100000)	// 512KB/1MB
		nand_bootcode_area_size = NAND_BOOTCODE_AREA_30MB;
	else if (BlockSize == 0x200000)	// 2MB
		nand_bootcode_area_size = NAND_BOOTCODE_AREA_50MB;
	else if (BlockSize == 0x400000)	// 2MB
		nand_bootcode_area_size = NAND_BOOTCODE_AREA_100MB;
	else{	// undefined block size??
	        prints("undefined block size ");
                print_hex(BlockSize);
                prints("\n ");
		return -1;
        }

	// set ECC bit level
	//((n_device_type *)(*dev))->ecc_bit = ECC_6BIT; // set to 6 bit ecc.
	REG32(REG_ECC_SEL) = ((n_device_type *)(*dev))->ecc_bit;

	// set random access mode
//#ifdef FPGA_BOOT_NAND_RANDOM_ACCESS_MODE
	if (((n_device_type *)(*dev))->ecc_bit == ECC_6BIT || ((n_device_type *)(*dev))->ecc_bit == ECC_12BIT) {
		prints("enable NF random access mode\n");
		nf_enable_random_mode();
	}
	else {
		prints("disable NF random access mode\n");
		nf_disable_random_mode();
	}
//#endif

#endif
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	prints("do_identify_n end... \n");
	if (((n_device_type *)(*dev))->ecc_bit > 0x1)
	{
		prints("do_identify_n NOT support MLC!!!!!!!!!!!! \n");
		return -1;
	}
	return 0;
}

/************************************************************************
 *
 *                          do_init_n
 *  Description :
 *  -------------
 *  implement the following NAND flash init job:
 *	1. setup block state table for bootcode area
 *	2. erase old bootcode blocks
 *	3. determine block range for env param
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_init_n(void *dev)
{
	n_device_type *device = (n_device_type *)dev;
	UINT32 i, temp, temp2, idx;
	INT32 res;
	UINT8 state;
	//UINT32 len;
	prints("do_init_n start\n");

	disable_dcache();
	
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#ifdef ENABLE_NAND_DRIVER
	t_nand_profile *profile;
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	// init block state table

	#ifdef ERASE_WHOLE_NAND_BEFORE_WRITIE
		// erase all.
		for (i=0 ; i<blocks_per_flash ; i++)
			nf_erase_block(device, i);
	#endif
	
	//blk_state_len = nand_bootcode_area_size / device->BlockSize;	// only bootcode blocks
	blk_state_len = blocks_per_flash;
	//for (i = 0; i < blk_state_len; i++)
	for (i = 0; i < blocks_per_flash; i++)
		rtd_outb((BLK_STATE_BASE + i) , BLOCK_UNDETERMINE);
	blk_state = (UINT8 *)BLK_STATE_BASE;

	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	/* fill all blocks state table */
	// search with non-exist magic no (this guarantees we can visit to the end of the bootcode blocks)
	//res = nf_find_blk(device, 0, blk_state_len, 0, BLOCK_UNDETERMINE, &temp);
        //res = nf_find_blk(device, 0, blk_state_len, 0);
	//rtprintf("0x81000000 0x%x \n", rtd_inl(0x81000000) );
	
//	if(rtd_inl(0x81000000) == 0x23) {
if(0) {
		rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	/* erase blocks */ //cy test I will modified
	for (i = 0; i < blk_state_len; i++)
	{
		rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

				if (nf_erase_block_nomap(device, i)) {
					prints("nf_erase_block err , BB handle \n");


					set_block_state(i, BLOCK_BAD);
				}
				else
				{
					// check read ok after erase
					//res = nf_read_to_table(device, i * pages_per_block, 2048);
					res = nf_read_page_nomap(device, i * pages_per_block, (UINT8 *)PAGE_TMP_ADDR, 1);
					if (res == DATA_ALL_ONE)
						set_block_state(i,  BLOCK_CLEAN );
					else {


						set_block_state(i, BLOCK_BAD);
					}

				}

	}
	//check_build_bbt(device);

}
else {
	/* after we create the block state table , we check if bbt exists or not */
	//check_build_bbt(device);
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	
	prints("before erase old bootcode related blocks \n");
	/* erase old bootcode related blocks */ //cy test I will modified
	for (i = 0; i < /*blk_state_len*/ nand_bootcode_area_size / device->BlockSize; i++)
	{
		get_block_state(i, &state);
		switch (state)
		{
			// block is ready to write
			case BLOCK_CLEAN:
			// reserve env block & user data only
			case BLOCK_ENVPARAM_MAGICNO:
			// reserve user programed data
			case BLOCK_OTHER_DATA:
			// skip bad block table (they are in block 0 & 1, should not happen here)
			case BLOCK_BBT:
			// dont erase factory setting data
			case BLOCK_FACTORY_SETTING:
				break;

			// erase old bootcode

			case BLOCK_HWSETTING:


			case BLOCK_BOOTCODE:
			case BLOCK_DATA:
			// erase again to make sure it's really a bad block
			case BLOCK_BAD:
			// erase unknown type of block
			default:
				if (nf_erase_block(device, i)) {
					prints("nf_erase_block err , BB handle \n");
					// write 'BAD_BLOCK' signature to spare cell
					nf_BB_handle( device, i);

					set_block_state(i, BLOCK_BAD);
				}
				else
				{
					// check read ok after erase
					prints("check block No.");
					print_hex(i);
					prints(" , ok after erase with state");
					print_hex(state);
					prints("\n");
					
					//res = nf_read_to_table(device, i * pages_per_block, 2048);
					res = nf_read_page(device, i * pages_per_block, (UINT8 *)PAGE_TMP_ADDR, 1);
					
					if (res == DATA_ALL_ONE) {
						prints("ok, set block to clean \n");
						set_block_state(i,  BLOCK_CLEAN );
					}
					else {

						prints("nf_read_page err , BB handle \n");
						// write 'BAD_BLOCK' signature to spare cell
						nf_BB_handle( device, i);


						set_block_state(i, BLOCK_BAD);
					}

				}
		}
	}

	prints("after erase old bootcode related blocks \n");
}

	// reset current env start page address
	env_version_no = 0;
	current_env_start = temp = temp2 = fileflash_phys_end = fileflash_phys_start = -1;
	for (idx = 3, i = 0; idx < nand_bootcode_area_size / device->BlockSize; idx++)
	{
		if (get_block_state(idx, &state))
			continue;	// block out of range

		// find first env block
		if ((fileflash_phys_start == -1)
			&& (state == BLOCK_ENVPARAM_MAGICNO))
		{
		    fileflash_phys_start = idx;
		}

		// find last env block
		if (state == BLOCK_ENVPARAM_MAGICNO)
		{
		    fileflash_phys_end = idx;
		}


		// find first unused block
		if ((temp == -1) && (state == BLOCK_CLEAN))
		{
		    temp = idx;
		}

		// find last unused block
		if (blk_state[idx] == BLOCK_CLEAN)
		{
		    temp2 = idx;
		}
	}

	// locate first block available for env
	if (temp < fileflash_phys_start)
		fileflash_phys_start = temp;

	// extend block available for env (maximum is last block of bootcode area)
	if (fileflash_phys_end == -1)
	{
		if (temp2 != -1)
			fileflash_phys_end = temp2;
		else
			prints("no space for env\n");
	}
	else
	{
		if ((temp2 != -1) && (fileflash_phys_end < temp2))
			fileflash_phys_end = temp2;
	}

#endif

	prints("do_init_n end\n");
	return 0;
}
/************************************************************************
 *
 *                          write_bbt
 *  Description :
 *  -------------
 *  write BBT
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void write_bbt(void *dev)
{
	UINT32 idx, len, bbt_size;
	int res;
	n_device_type *device = (n_device_type *)dev;
	// prepare memory space for bad block table (aligned to page boundary)
#ifdef ENABLE_NAND_DRIVER
	bbt_size = sizeof(BB_t) * BBT_LENGTH;
	len = bbt_size / device->PageSize;
	if (bbt_size & (device->PageSize - 1))
		len++;

	if (len >= pages_per_block)
	{
		prints("bbt exceed one block\n");
		return;
	}

	len *= device->PageSize;
	set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, len);
	copy_memory((UINT8 *)PAGE_TMP_ADDR, bbt, bbt_size);

	// write bad block table into block 0 & 1
	nf_set_spare(BLOCK_BBT, 0);
	for (idx = 1; idx < 3; idx++)
	{
		res = nf_erase_block(device, idx);
		if (res == 0)
		{
		 	if (nf_write(device, idx * pages_per_block, (UINT8 *)PAGE_TMP_ADDR, len))
				prints("write bbt failed\n");
			else
				set_block_state(idx, BLOCK_BBT);
		}
		else
		{
			prints("erase bbt failed\n");
			set_block_state(idx, BLOCK_BAD);
		}
	}
#endif
}
/************************************************************************
 *
 *                          check_build_bbt
 *  Description :
 *  -------------
 *  check & build BBT
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void check_build_bbt(void *dev)
{
	INT32 res;
	UINT32 idx;
	UINT32 ini_bb_offset;
	n_device_type *device = (n_device_type *)dev;
	//UINT32 spare;
	UINT8 status;

#ifdef ENABLE_NAND_DRIVER
	if (bbt_exist(dev) == 0 )
	{
		prints("build bbt...");

		// reserve 5% blocks
		BBT_LENGTH = blocks_per_flash * RBA_PERCENTAGE / 100;
#if 0
		// scan untill end of flash
		//nf_find_blk(device, nand_bootcode_area_size / device->BlockSize, 0xffffffff, initial_bad_block_offset(device));
		ini_bb_offset = initial_bad_block_offset(device);
		for (res = 0, idx = nand_bootcode_area_size / device->BlockSize; idx < blocks_per_flash; idx++)
		{


			// read initial block status
			// (1st byte in the physical spare area, not controller's spare area)
			// e.g. 2KB page -> 1st spare byte at column address 2048
			//      4KB page -> 1st spare byte at column address 4096
			res = nf_read_single_byte(device, device->PageSize, (idx * pages_per_block + ini_bb_offset), &status);

			if (status != BLOCK_CLEAN)
				status = (nf_erase_block(device, idx) == 0 ? BLOCK_CLEAN : BLOCK_BAD);

			// save block state
			set_block_state(idx, status);
		}

#endif
		if (init_bbt(dev))
		{
			prints("init_bbt failed\n");
			return;
		}

		build_bbt(dev);

		write_bbt(dev);

		prints("build bbt...finished");
	}
	else {
		prints("load bbt...");
		load_bbt(dev);
	}
#endif
}


/************************************************************************
 *
 *                          do_exit_n
 *  Description :
 *  -------------
 *  implement the exit flash writing operation
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void do_exit_n(void *dev)
{
#ifdef ENABLE_NAND_DRIVER
	n_device_type *device = (n_device_type *)dev;
	t_nand_profile profile;
	int res;

	prints("do_exit_n\n");

	memset(&profile, 0, sizeof(t_nand_profile));
	
	prints("build profile... on memory 0x");
	print_hex(&profile);
	prints(", length = 0x");
	print_hex(sizeof(t_nand_profile));
	prints("\n");

        if ((device->ecc_bit == ECC_6BIT || device->ecc_bit == ECC_12BIT)&& device->PageSize==0x1000){
            force_2k=1;
        }

	build_nand_profile(device, &profile);
	hexdump("[do_exit_n]", &profile, sizeof(t_nand_profile));
	res = write_nand_profile(device, &profile);
	if (res == -1)
		return;
	else{
                prints("write backup profile.\n");
                res = write_nand_profile_bak(device, &profile);

                if (res == -1)
		    return;
        
		prints("done\n");
        }

#endif
}

/************************************************************************
 *
 *                          nf_read_id
 *  Description :
 *  -------------
 *  get NAND flash ID
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'DDR_BASE',       	IN,    READ ID result address
 *  'size',	  	IN,    number of bytes
 *
 *
 *  Return values :
 *  ---------------
 *
 *
 *
 ************************************************************************/
static void nf_read_id(UINT32 DDR_BASE, UINT8 size)
{
	UINT8 i;
#if 1
	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0,size & 0xff);
	rtd_outl(REG_DATA_TL1,0x80);	// transfer mode

	//Set PP
	rtd_outl(REG_PP_RDY, 0);		// NOt through PP
	rtd_outl(REG_PP_CTL0,0x01);
	rtd_outl(REG_PP_CTL1,0);

	//Set command
	rtd_outl(REG_CMD1,0x90);
	//if( !trans_code(TRANS_CMD) )	while(1);
	rtd_outl(REG_CTL,0x80);
	while (rtd_inl(REG_CTL) & 0x80)
		;

	//Set address
	rtd_outl(REG_PAGE_ADR0, 0);
	rtd_outl(REG_PAGE_ADR1, 0);
	rtd_outl(REG_PAGE_ADR2, 0x7<<5);
	//if( !trans_code(TRANS_ADDR) )	while(1);
	rtd_outl(REG_CTL, 0x81);
	while (rtd_inl(REG_CTL) & 0x80)
		;

	//Enable MultiByteRead XFER mode
	//if( !trans_code(TRANS_MBR) )	while(1);
	rtd_outl(REG_CTL, 0x84);
	while (rtd_inl(REG_CTL) & 0x80)
		;

	//Reset PP
	rtd_outl(REG_PP_CTL0, 0x2);

	//Move data to DRAM from SRAM
	rtd_outl(REG_SRAM_CTL, 0x30);//modify by angus, set to 0x30, original value is 0x10
	for ( i = 0 ; i < size ; i++){
		//temp = DDR_BASE * 8 + i * 4;
		rtd_outb((DDR_BASE+i), rtd_inb(REG_PAGE_ADR0 + i));	//5 bytes value : EC D3 10 A6 64
	}
	rtd_outl(REG_SRAM_CTL, 0x00);	//# no omitted
#else
	rtd_outl(REG_PP_CTL0, 0x02);
	rtd_outl(REG_DATA_TL0, 0);
	rtd_outl(REG_DATA_TL1, 0x82);	// auto mode

	//Set page length at auto mode
	rtd_outl(REG_PAGE_LEN, 1);

	//Set PP
	rtd_outl(REG_PP_RDY, 0x80);		// NOt through PP
	rtd_outl(REG_PP_CTL0,0x01);
	rtd_outl(REG_PP_CTL1,0);

	//Set command
	rtd_outl(REG_CMD1,0x90);
	rtd_outl(REG_CMD2,0);
	rtd_outl(REG_CMD3,0);

	//Set address
	rtd_outl(REG_PAGE_ADR0, 0);
	rtd_outl(REG_PAGE_ADR1, 0);
	rtd_outl(REG_PAGE_ADR2, 0x7<<5);
	rtd_outl(REG_PAGE_ADR3, 0);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//set ECC
	REG32(REG_MultiChMod) = 0xc0;
	REG32(REG_ECC_STOP) = 0x80;		// non-stop

	//Set DMA
	rtd_outl(REG_DMA_ADR, DDR_BASE);	// 8 bytes unit, and must mask first 4 bits
	rtd_outl(REG_DMA_LEN, 1);	// DMA transfer unit is 512 bytes
	rtd_outl(REG_DMA_CONF, 0x02|0x01);
	
	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x88);	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;

	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x84);	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;
	
	//Wait DMA done
	while( rtd_inl(REG_DMA_CONF) & 0x1 ){
		//prints("rtd_inl(REG_DMA_CONF)");
	};
	
#endif
}


/************************************************************************
 *
 *                          nf_read_to_table
 *  Description :
 *  -------------
 *  read one page from NAND flash into table SRAM
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'device',       	IN,    variable of type, n_device_type.
 *  'page_no',  	IN,    page address
 *  'length',  		IN,    read data area size (multiple of 512B and cannot exceed one page)
 *
 *
 *  Return values :
 *  ---------------
 *
 *  "0"                  : means read page success (ECC is ok)
 *  "-1"                 : means device is NULL
 *  "DATA_ALL_ONE" = 0x1 : means all bits in the page is 1 (including spare area)
 *  "8"                  : means ECC is uncorrectable
 *
 *
 ************************************************************************/
/*
static INT8 nf_read_to_table(n_device_type *device, UINT32 page_no, UINT32 length)
{
	UINT8 cs;
	//int res = 0;

	if (device == NULL)
		return (-1);

	// data length must be multiple of 512B and cannot exceed one page
	if ((length & 0x1ff) || (length > device->PageSize))
		return (-1);

	if (nf_map_phys_page(device, &cs, &page_no))
		return -1;

	// Set chip select
	REG32(REG_Chip_En) = NF_CHIP_SEL(cs);

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	REG32(REG_DATA_TL0) = 0;
	REG32(REG_DATA_TL1) = 0xc2;

	//set page length at auto mode (512B unit)
	REG32(REG_PAGE_LEN) = length >> 9;

	REG32(REG_PP_RDY) = 0;			// no read_by_pp
	REG32(REG_PP_CTL0) = 0;			// disable PP
	REG32(REG_TABLE_CTL) = 0x1;		// enable table SRAM

	REG32(REG_BLANK_CHK) = 0x1;		// enable blank check

	//set command
	REG32(REG_CMD1) = 0;
	REG32(REG_CMD2) = 0x30;
	REG32(REG_CMD3) = 0x70;

	//Set address
	REG32(REG_PAGE_ADR0) =  page_no & 0xff;
	REG32(REG_PAGE_ADR1) =  page_no >> 8 ;
	REG32(REG_PAGE_ADR2) = ((page_no >>16 ) & 0x1f) | (device->addr_mode_rw << 5);
	REG32(REG_PAGE_ADR3) = ((page_no >> 21) & 0x7) << 5;
	REG32(REG_COL_ADR0)  = 0;
	REG32(REG_COL_ADR1)  = 0;

	//ste ECC
	REG32(REG_MultiChMod) = 0;
	REG32(REG_ECC_STOP) = 0x80;		// non-stop

	//Enable Auto mode
	REG32(REG_AUTO_TRIG) = 0x80 | (device->PageSize == 512 ? 0x3 : 0x2);	//0x2: read in 2K page size
	while( REG32(REG_AUTO_TRIG) & 0x80 )
		;

	// return OK if all data bit is 1 (page is not written yet)
	if (REG32(REG_BLANK_CHK) & 0x2)
		return (DATA_ALL_ONE);

	// return ECC result
	return (REG32(REG_ECC_STATE) & 0x8);	// ecc_not_clr
}
*/

/************************************************************************
 *
 *                          nf_read_to_PP
 *  Description :
 *  -------------
 *  read the 1st 1024B of page data from NAND flash into PP buffer
 *  (after remapping)
 *  (primary for get spare area byte)
 *
 *  Parameters :
 *  ------------
 *
 *  'device',       	IN,    variable of type, n_device_type.
 *  'page_no',  	IN,    page address
 *
 *
 *  Return values :
 *  ---------------
 *
 *  "0"                  : means read page success (ECC is ok)
 *  "-1"                 : means device is NULL
 *  "DATA_ALL_ONE" = 0x1 : means all bits in the page is 1 (including spare area)
 *  "8"                  : means ECC is uncorrectable
 *
 *
 ************************************************************************/
static INT8 nf_read_to_PP(n_device_type *device, UINT32 page_no)
{
	UINT8 cs;
	INT8 res = 0;
        UINT32 data_unit;

	if (device == NULL)
		return (-1);

	if (nf_map_phys_page(device, &cs, &page_no))
		return -1;

	if (device->ecc_bit == ECC_6BIT || device->ecc_bit == ECC_12BIT) {		
		//if (nf_is_random_mode())
		nf_enable_random_mode();
			nf_set_random_read(device,0);

		rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check
	}
	else {
		rtd_outl(REG_RMZ_CTRL, 0x1);
		nf_disable_random_mode();
		rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check
	}

    // determine read unit size
	data_unit = nf_get_auto_transfer_unit(device->ecc_bit);

	prints("data_unit = 0x");
	print_hex(data_unit);
	prints("\n");

    	prints("page_no = 0x");
	print_hex(page_no);
	prints("\n");

	// Set chip select
	//rtd_outl(REG_Chip_En , NF_CHIP_SEL(cs));

	//Set data transfer count, data transfer count must be 0x200 at auto mode
	//Set SRAM path and access mode
	rtd_outl(REG_DATA_TL0, data_unit & 0xff);
	rtd_outl(REG_DATA_TL1, 0x80 | ((data_unit >> 8) & 0x3f));	// transfer mode

	//set page length at auto mode
	rtd_outl(REG_PAGE_LEN, 1024 / data_unit);

	rtd_outl(REG_PP_RDY, 0x80);		// set read_by_pp
	//REG32(REG_PP_CTL0) = 0;			// enable PP
	rtd_outl(REG_PP_CTL1, 0);			// PP starting address at 0

	rtd_outl(REG_TABLE_CTL, 0);		// disable table SRAM

	//rtd_outl(REG_BLANK_CHK, 0x1);		// enable blank check

	//set command
	rtd_outl(REG_CMD1, 0);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0,  page_no & 0xff);
	rtd_outl(REG_PAGE_ADR1,  page_no >> 8 );
	rtd_outl(REG_PAGE_ADR2, ((page_no >>16 ) & 0x1f) | (device->addr_mode_rw << 5));
	rtd_outl(REG_PAGE_ADR3, ((page_no >> 21) & 0x7) << 5);
	rtd_outl(REG_COL_ADR0, 0);
	rtd_outl(REG_COL_ADR1, 0);

	//ste ECC
	//rtd_outl(REG_MultiChMod, 0x20);
	rtd_outl(REG_MultiChMod, 0x0);
	rtd_outl(REG_ECC_STOP, 0x80);		// non-stop

	//no DMA (data remains in PP)
	rtd_outl(REG_DMA_CONF, 0);

	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG, 0x80 | (device->PageSize == 512 ? 0x3 : 0x2));	//0x2: read in 2K page size
	while( rtd_inl(REG_AUTO_TRIG) & 0x80 )
		;

	// check if all data bit is 1 (data is not written yet)
	if (rtd_inl(REG_BLANK_CHK) & 0x2)
		res = DATA_ALL_ONE;
	else
		res = rtd_inl(REG_ECC_STATE) & 0x8;	// get ECC result (ecc_not_clr)

	//Reset PP
	rtd_outl(REG_PP_CTL0, 0x2);

	return res;
}



/************************************************************************
 *
 *                          FLASH_NAND_search_latest_env
 *  Description :
 *  -------------
 *  Search latest env param data
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'device',   IN,    variable of type, n_device_type.
 *  'start',    IN,    start block no
 *  'end',   	IN,    end block no
 *  'latest',  	INOUT, latest env param start page address
 *
 *
 *  Return values :
 *  ---------------
 *
 * 'OK' = 0x00:                         System FLASH OK
 *
 ************************************************************************/
static int nf_search_latest_env(n_device_type *device, UINT32 start, UINT32 end, UINT32 *latest)
{
	UINT32 page_start, page_end, increment;
	UINT32 i, spare;
	UINT8 res, version, lowest, highest;
	UINT8 wrap_version;	// version no (wrap case)
	UINT32 wrap_latest;	// latest env address (wrap case)

	if (device == NULL)
		return (-1);

	// env param size is 64KB
	increment = NAND_ENV_SIZE / device->PageSize;

	// start == -1 means search from the first block (skip block 0 because it's used by YAFFS)
	page_start = (start == -1 ? 1 : start) * pages_per_block;

	// end == -1 means search to the end of the bootcode blocks
	page_end = (end == -1 ? blk_state_len : end) * pages_per_block;

	// search to the last page of the block
	page_end += pages_per_block;

	version = highest = wrap_latest = wrap_version = 0;
	lowest = 255;
	for (i = page_start; i < page_end; i += increment)
	{
		res = nf_read_page(device, i, (UINT8 *)PAGE_TMP_ADDR, 0);

		// skip empty page
		if (res == DATA_ALL_ONE)
			continue;

		nf_get_spare(0x2, &spare, 0);

		// check 1st byte of spare area identifies env param
		if ((spare & 0xff) != BLOCK_ENVPARAM_MAGICNO)
			continue;

		// get 2nd byte of the spare area
		res = (spare >> 8) & 0xff;
		if (res >= version)
		{
			version = res;
			*latest = i;
		}

		// update lowest & highest version no
		if (res < lowest)
			lowest = res;
		if (res > highest)
			highest = res;

		// update possible wraped latest no
		// (number of env in flash is expected to be smaller than 128)
		/*
			why 128?
			if BlockSize=256K, env=64K
			=> one block contains at most 4 versions
			=> thus we support at most 128/4=32 blocks for storing env

			=> if BlockSize=128K, we can support up to 64 blocks !!
		*/
		if ((res >= wrap_version) && (res < 128))
		{
			wrap_version = res;
			wrap_latest = i;
		}
	}

	// check wrap condition (when version 0 and 255 both exists)
	if ((lowest == 0) && (highest == 255))
	{
		// version no 255 is not latest, use warped ones instead
		version = wrap_version;
		*latest = wrap_latest;
	}

	// update env param version no
	env_version_no = version;

	return 0;
}


/************************************************************************
 *
 *                          nf_search_next_env
 *  Description :
 *  -------------
 *  Search next writable address for env param data
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'device',	IN,	variable of type, n_device_type.
 *  'page_no',  INOUT,	page address of next writable address
 *
 *
 *  Return values :
 *  ---------------
 *
 *  '-1': device is NULL or cannot found writable address
 *
 ************************************************************************/
static int nf_search_next_env(n_device_type *device, UINT32 *page_no)
{
	INT8 res;
	UINT32 current_env_end, page_cnt;
	UINT32 current_blk, next_blk;
	UINT8 state;

	if ((device == NULL) || (page_no == NULL))
		return (-1);

	// check if latest env exist
	if (current_env_start == -1)
	{
		// no env found in flash
		//return (-1);

		// no current env, start from fileflash_phys_start
		for (next_blk = fileflash_phys_start; next_blk <= fileflash_phys_end; next_blk++)
		{
			if (get_block_state(next_blk, &state))
				continue;

			switch (state)
			{
				case BLOCK_CLEAN:
					*page_no =  next_blk * pages_per_block;
					return (0);

				case BLOCK_ENVPARAM_MAGICNO:
					res = nf_erase_block(device, next_blk);
					if (res == 0)
					{
						*page_no = next_blk * pages_per_block;
						return (0);
					}
					else	// erase failed, mark as bad block
						set_block_state(next_blk, BLOCK_BAD);
					break;

				default:
					break;
			}
		}

		// cannot find any available block
		return (-1);
	}

	/* find next writable 64KB area */
	page_cnt = NAND_ENV_SIZE / device->PageSize;
	current_env_end = current_env_start + page_cnt - 1;
	current_blk = current_env_end / pages_per_block;
	//printf("current_env_end:%x, current_blk:%x\n", current_env_end, current_blk);

	// check if current env block has space
	if ( current_blk == ((current_env_end + page_cnt) / pages_per_block) )
	{
		// current env & next env in the same block
		*page_no = current_env_start + page_cnt;
		return (0);
	}
	else
	{
		// current env & next env not in the same block
		next_blk = (current_blk >= fileflash_phys_end ? fileflash_phys_start : current_blk + 1);
		while (next_blk != current_blk)
		{
			// try to find next available block
			res = get_block_state(next_blk, &state);
			if (res == 0)
			{
				switch (blk_state[next_blk])
				{
					// skip bad block
					case BLOCK_BAD:
					// skip bootcode related block
					case BLOCK_HWSETTING:
					case BLOCK_BOOTCODE:
					case BLOCK_DATA:
						break;

					case BLOCK_CLEAN:
						*page_no = next_blk * pages_per_block;
						return (0);

					case BLOCK_ENVPARAM_MAGICNO:
					//case BLOCK_OTHER_DATA:
						res = nf_erase_block(device, next_blk);
						if (res == 0)
						{
							*page_no = next_blk * pages_per_block;
							return (0);
						}
						else	// erase failed, mark as bad block
							set_block_state(next_blk, BLOCK_BAD);
						break;

					default:
						break;
				}
			}
			// end of bootcode blocks, wrap to fileflsh start
			if (next_blk >= fileflash_phys_end)
				next_blk = fileflash_phys_start;
			else
				next_blk++;
		}
		return (-1);
	}

}



/************************************************************************
 *
 *                          nf_read
 *  Description :
 *  -------------
 *  read NAND flash
 *
 *  Parameters :
 *  ------------
 *  'device',       	IN,    variable of type, n_device_type.
 *  'start_page',  	IN,    start page address to read
 *  'buf', 	        IN,    pointer for buffer of data to read
 *  'size',       	IN,    number of bytes to read
 *
 *  Return values :
 *  ---------------
 *  '-1': device is NULL or read beyond flash or read failed
 *
 ************************************************************************/
static int nf_read(n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size)
{
	UINT32 stop_page;
	INT32 res;

	// validate arguments (size should be aligned to page size boundary)
	if ( (device == NULL) || (buf == NULL)
		|| (start_page > pages_per_block * blocks_per_flash)
		|| (size & (device->PageSize - 1))
		|| (size == 0) )
		return (-1);

	// do not allow read past end of flash
	stop_page = start_page + size / device->PageSize;
	if (stop_page > pages_per_block * blocks_per_flash)
		return (-1);

	while (start_page < stop_page)
	{
		res = nf_read_page(device, start_page, buf, 0);
		switch (res)
		{
			case DATA_ALL_ONE:	// page is clean
			case 0:
				break;

			default:
				return (-1);
                                break;
		}

		buf += device->PageSize;
		start_page++;
	}
	return 0;
}


/************************************************************************
 *
 *                          nf_write
 *  Description :
 *  -------------
 *  write data into NAND flash
 *
 *  Parameters :
 *  ------------
 *  'device',       	IN,    variable of type, n_device_type.
 *  'start_page',  	IN,    start page address to write
 *  'buf', 	        IN,    pointer for buffer of data to be written
 *  'size',       	IN,    number of bytes to write
 *
 *  Return values :
 *  ---------------
 *  '-1': device is NULL or write beyond flash or write failed
 *
 ************************************************************************/
static int nf_write(n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size)
{
	UINT32 stop_page;
	INT32 res;

	// validate arguments (size should be aligned to page size boundary)
	if ( (device == NULL) || (buf == NULL)
		|| (start_page > pages_per_block * blocks_per_flash)
		|| (size & (device->PageSize - 1))
		|| (size == 0) )
		return (-1);

	// do not allow write past end of flash
	stop_page = start_page + size / device->PageSize;
	if (stop_page > pages_per_block * blocks_per_flash)
		return (-1);

	while (start_page < stop_page)
	{
	prints("start_page = 0x");
	print_hex(start_page);
	prints("\n");
    
		res = nf_write_page(device, start_page, buf);
		if (res)
			return (-1);
		buf += device->PageSize;
		start_page++;
	}
	return 0;
}



/************************************************************************
 *
 *                          nf_find_blk
 *  Description :
 *  -------------
 *  scan NAND flash to get block state
 *
 *  Parameters :
 *  ------------
 *  'device',       	IN,    variable of type, n_device_type.
 *  'start_block',  	IN,    start block to search
 *  'search_depth', 	IN,    maximum number of blocks to search
 *  'offset',       	IN,    page offset in the block
 *
 *  Return values :
 *  ---------------
 *  '-1': device is NULL or start_block beyond flash or not found
 *
 ************************************************************************/
static INT8 nf_find_blk(n_device_type *device, UINT32 start_block, UINT32 search_depth, UINT32 offset)
{
	UINT32 blk, limit, page_no;
	UINT32 spare;
	INT8 res;
	//UINT8 state;
	UINT32 spr_ddr_ctrl;
	prints("nf_find_blk \n");
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	// validate arguments
	if ((device == NULL) || (start_block >= blocks_per_flash) || (offset >= pages_per_block))
		return (-1);

	// determine search limit
	if (search_depth == 0)
		limit = nand_bootcode_area_size / device->BlockSize;	// only bootcode blocks
	else if (search_depth >= blocks_per_flash)
		limit = blocks_per_flash;	// search to end of flash
	else
	{
		limit = start_block + search_depth;

		// cannot search beyond flash (max is last block of flash)
		if (limit >= blocks_per_flash)
			limit = blocks_per_flash;
	}

	if (nf_spare_ddr_enabled()) {
		spr_ddr_ctrl = rtd_inl(REG_SPR_DDR_CTL);	// save original setting
		rtd_outl(REG_SPR_DDR_CTL, rtd_inl(REG_SPR_DDR_CTL) & (~0x40000000));	// turn off spare to DDR
	}
	else
		spr_ddr_ctrl = 0;

	for (blk = start_block, page_no = (blk * pages_per_block + offset);
		blk < limit ;
		blk++, page_no += pages_per_block)
	{
		// read first page of the block to table sram
		res = nf_read_page(device, page_no, (UINT8 *)PAGE_TMP_ADDR, 0);
		//res = nf_read_to_PP(device, page_no);

		switch (res)
		{
			case DATA_ALL_ONE:
				set_block_state(blk, BLOCK_CLEAN);
				continue;

			case 0:		// read to table success
				nf_get_spare(0x2, &spare, 0);
				prints("blk = ");
				print_hex(blk);
				prints(" , page_no = ");
				print_hex(page_no);
				prints(" , spare = ");
				print_hex(spare);
				prints("\n");
				spare &= 0xff;
				break;

			default:	// read to table has error
				set_block_state(blk, BLOCK_BAD);
				continue;	// next block
		}

		// NOTE: BLOCK_UNDETERMINE is a fake state,
		// all blocks in the flash "SHALL NOT" have this state or it will cause some problem!!
		if (spare == BLOCK_UNDETERMINE)
			continue;	// should not happen

		/*
		// check if block is beyond the range of block state table
		res = get_block_state(blk, &state);
		if (res)
			continue;
		*/

		// update with new magic no. in spare area
		set_block_state(blk, (UINT8)(spare & 0xff));
	}

//	{
//		UINT8 state;
//		for (blk = 0; blk < blk_state_len; blk++)
//		{

//			get_block_state(blk, &state);
//			printf("blk=0x%x, state=0x%x \n", blk, state);
//		}
//	}


	if (spr_ddr_ctrl != 0)
		rtd_outl(REG_SPR_DDR_CTL, spr_ddr_ctrl);	// restore to original setting
	rtprintf("\n%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

	return (0);
}

/************************************************************************
 *
 *                          set_block_state
 *  Description :
 *  -------------
 *  get block state
 *
 *  Parameters :
 *  ------------
 *  'block_no',	IN,	block no.
 *  'state',	IN,	specified block state
 *
 *  Return values :
 *  ---------------
 *  '-1': block_no is out of range
 *
 ************************************************************************/
static int set_block_state(UINT32 block_no, UINT8 state)
{
/*
	if (block_no >= blk_state_len)
		return (-1);

	blk_state[block_no] = state;
	return (0);
*/
	blk_state[block_no] = state;
	return (block_no < blk_state_len ? 0 : -1);
}


/************************************************************************
 *
 *                          get_block_state
 *  Description :
 *  -------------
 *  get block state
 *
 *  Parameters :
 *  ------------
 *  'block_no',	IN,	block no.
 *  'state',	INOUT,	specified block state
 *
 *  Return values :
 *  ---------------
 *  '-1': block_no is out of range
 *
 ************************************************************************/
static int get_block_state(UINT32 block_no, UINT8 *state)
{
/*
	if (block_no >= blk_state_len)
		return (-1);

	*state = blk_state[block_no];
	return 0;
*/
	*state = blk_state[block_no];
	return (block_no < blk_state_len ? 0 : -1);
}


/************************************************************************
 *
 *                          get_env_n
 *  Description :
 *  -------------
 *  get env param from flash to DRAM
 *
 *  Parameters :
 *  ------------
 *  'device',	IN,	variable of type, n_device_type.
 *  'buf',	IN,	env data pointer
 *
 *  Return values :
 *  ---------------
 *  '-1': means device or buf is NULL, or no env found, or copy env to DRAM failed
 *
 ************************************************************************/
int get_env_n(void *dev, UINT8 *buf)
{
#ifdef ENABLE_NAND_DRIVER
	INT32 res;
	n_device_type *device = (n_device_type *)dev;

	if ((device == NULL) || (buf == NULL))
		return (-1);

        // search latest env data from fileflash_phys_start
       	nf_search_latest_env(device, fileflash_phys_start, fileflash_phys_end, &current_env_start);
	if (current_env_start == -1)
        	return (-1);	// no env found

    // copy latest env data to DDR
    res = nf_read(device, current_env_start, buf, NAND_ENV_SIZE);
   	return (res);
#else
	return (-1);
#endif
}


/************************************************************************
 *
 *                          save_env_n
 *  Description :
 *  -------------
 *  save env param from DRAM to flash
 *
 *  Parameters :
 *  ------------
 *  'device',	IN,	variable of type, n_device_type.
 *  'buf',	IN,	env data pointer
 *
 *  Return values :
 *  ---------------
 *  '-1': means device or buf is NULL, or no env found, or find next writable page address failed
 *
 ************************************************************************/
int save_env_n(void *dev, UINT8 *buf)
{
	n_device_type *device = (n_device_type *)dev;
	UINT32 start_page, spare;
	UINT8 block_state;
	int rc;
#ifdef ENABLE_NAND_DRIVER
	if ((device == NULL) || (buf == NULL))
		return (-1);

	// skip save env param if latest one is not overwritten by bootcode blocks
	block_state = BLOCK_UNDETERMINE;
	rc = get_block_state(current_env_start / pages_per_block, &block_state);
	if (rc != 0)
		return rc;

	if (block_state == BLOCK_ENVPARAM_MAGICNO)
		return 0;
	else
		current_env_start = -1;		// current env page does not exist

	// find next writable page address
	rc = nf_search_next_env(dev, &start_page);
	if (rc != 0)
		return rc;

	// if this is the first time to write env param, start with version 0
	spare = (env_version_no == 0 ? 0 : env_version_no + 1);
	spare = (spare << 8) | BLOCK_ENVPARAM_MAGICNO;
	nf_set_spare(spare, 0);
	rc = nf_write(device, start_page, buf, NAND_ENV_SIZE);
//	printf("start_page:%x, env_version_no: %x\n", start_page, (current_env_start == -1 ? 0 : env_version_no + 1));
	if (rc == 0)
	{
		// write env param success
		current_env_start = start_page;	// update env param page address
		env_version_no++;		// increment env param version no

		// update block state array
		if (set_block_state(start_page / pages_per_block, BLOCK_ENVPARAM_MAGICNO))
			return (-1);
	}

#endif	

return rc;

}


static int bbt_exist(void *dev)
{
	INT32 res;
	UINT8 state = 0;
	n_device_type *device = (n_device_type *)dev;

	// first check block 1
	get_block_state(1, &state);
	switch (state)
	{
		case BLOCK_CLEAN:	// block 1 is empty
			return (0);

		case BLOCK_BBT:		// block 2 has bad block table
			return (1);

		case BLOCK_BAD:
		default:
			res = nf_erase_block(device, 1);
			if (res == 0)
				return (0);
			else
				prints("block 1 failed\n");
			break;
	}

	// block 1 failed, check block 2 instead
	get_block_state(2, &state);
	switch (state)
	{
		case BLOCK_CLEAN:	// block 2 is empty
			return (0);

		case BLOCK_BBT:		// block 2 has bad block table
			return (1);

		case BLOCK_BAD:
		default:
			res = nf_erase_block(device, 2);
			if (res == 0)
				return (0);
			else
				prints("block 2 failed\n");
			break;
	}

	return (-1);
}

static int init_bbt(n_device_type *device)
{
	UINT32 i, remap_idx;
	UINT32 bbt_limit;
	UINT8 cs;
	UINT32 phys_offset;

	// specify bad block table space
	bbt = (BB_t *)(BLK_STATE_BASE + blocks_per_flash);

	// reset bad block table with initial value
	for (i = 0 ; i < BBT_LENGTH; i++)
	{
		bbt[i].BB_die = BB_DIE_INIT;
		bbt[i].bad_block = BB_INIT;
		bbt[i].RB_die = RB_DIE_INIT;
		bbt[i].remap_block = RB_INIT;
	}

	// fill the remap block field
	remap_idx = blocks_per_flash - 1;
	bbt_limit = remap_idx - BBT_LENGTH;
	for (i = 0; i < BBT_LENGTH; i++)
	{
		if (get_remap_block(&remap_idx)) {
			printf("get_remap_block err \n");
			return (-1);		// cannot find remap block anymore
		}

		// remapping block no. is limited to the last "BBT_LENGTH" blocks of flash
		if (remap_idx < bbt_limit)
			break;

		// calculate physical block offset and chip select
		phys_offset = remap_idx;
		if (map_phys_block(device, &cs, &phys_offset)) {
			printf("map_phys_block \n");
			return (-1);
		}

		bbt[i].RB_die = cs;
		bbt[i].remap_block = phys_offset;
		remap_idx--;
	}

	return 0;
}


static int get_remap_block(UINT32 *start_blk)
{
	UINT8 state;
	UINT32 ith;

	if (start_blk == NULL)
		return (-1);



	// cannot remap beyond flash
	if (*start_blk >= blocks_per_flash) {

		return (-1);
	}

	// search backward , >=2 bbt blocks , I think
	for (ith = *start_blk; ith >= 2 ; ith--)
	{
		get_block_state(ith, &state);

		// found replaceable block
		if (state == BLOCK_CLEAN)
		{
			*start_blk = ith;
			return (0);
		}
	}

	return (-1);
}

static int build_bbt(void *dev)
{
	//int res;
	UINT32 i, bbt_i;
	UINT32 phys_offset;
	UINT8 state, cs;
	n_device_type *device = (n_device_type *)dev;

	// check for bad block
	for (i = nand_bootcode_area_size / device->BlockSize, bbt_i = 0;
		(i < blocks_per_flash) && (bbt_i < BBT_LENGTH); // stop when bad block table is full
		i++)
	{
		get_block_state(i, &state);
		if (state == BLOCK_BAD)
		{
			// check remapping block is valid
			if (bbt[bbt_i].remap_block == RB_INIT)
				break;			// reach the end of valid table entry

			// calculate physical block offset and chip select
			phys_offset = i;
			if (map_phys_block(device, &cs, &phys_offset))
				return (-1);

			// register into bad block table
			bbt[bbt_i].BB_die = cs;
			bbt[bbt_i].bad_block = phys_offset;
			bbt_i++;
		}
	}

	return (0);
}


static int load_bbt(void *dev)
{
	UINT8 state;
	n_device_type *device = (n_device_type *)dev;
	UINT32 i, bbt_size;

	for (i = 1; i < 3; i++)
	{
		get_block_state(i, &state);
		if (state == BLOCK_BBT)
			break;
	}

	// bad block table not found (something wrong with building bad block table)
	// or cannot get bad block table (cause read ECC failed)
	if (i == 3)
	{
		BBT_LENGTH = 0;
		bbt = NULL;
		return (-1);
	}
	// specify bad block table space
	bbt = (BB_t *)(BLK_STATE_BASE + blocks_per_flash);

	BBT_LENGTH = blocks_per_flash * RBA_PERCENTAGE / 100;
	bbt_size = sizeof(BB_t) * BBT_LENGTH;

	// read bad block table to DRAM
	if (nf_read( device, i * pages_per_block, (UINT8 *)bbt, ((bbt_size / device->PageSize) + 1) * device->PageSize ))
	{
		return (-1);
	}


	for (i = 0 ; i<BBT_LENGTH; i++)
	{

		printf("BB_die=0x%x ", bbt[i].BB_die);
		printf("bad_block=0x%x ", bbt[i].bad_block);
		printf("RB_die=0x%x ", bbt[i].RB_die);
		printf("remap_block=0x%x \n", bbt[i].remap_block);

	}
	return (0);



}
static UINT32 initial_bad_block_offset(n_device_type *device)
{

	// initial bad block mark is in first page of the block
	if (device->initial_bb_pos == INITIAL_BB_POS_FIRST)
		return 0;
	// initial bad block mark is in last page of the block
	else if (device->initial_bb_pos == INITIAL_BB_POS_LAST)
		return (pages_per_block - 1);
	// should not happen
	else
		return -1;
}



/************************************************************************
 *
 *                          remapped_bbt
 *  Description :
 *  -------------
 *  remap bad block
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'chip_sel',  	INOUT,    chip select value
 *  'block_no',		INOUT,    bad/remap block no.
 *
 *
 *  Return values :
 *  ---------------
 *
 *
 *
 ************************************************************************/
static void remapped_bbt(UINT8 *chip_sel, UINT32 *block_no)
{
	UINT32 i;
	UINT8 cs;
	UINT32 blk;

	// no remapping info (remain original chip_select & block_no)
	if (bbt == NULL) {
		printf("bbt null !\n");
		return;
	}

	cs = *chip_sel;
	blk = *block_no;
	for (i = 0; i < BBT_LENGTH; i++)
	{
#if 0
		printf("cs=0x%x, blk=0x%x \n", cs, blk);
		printf("i=0x%x, BB_die=0x%x ", i, bbt[i].BB_die);
		printf("bad_block=0x%x ", bbt[i].bad_block);
		printf("RB_die=0x%x ", bbt[i].RB_die);
		printf("remap_block=0x%x \n", bbt[i].remap_block);
#endif
		// check if bad block entry is valid
		if (bbt[i].BB_die == BB_DIE_INIT) {

			break;
		}

		// update remapping block if found (may have recursive mapping)
		if ((bbt[i].BB_die == cs) && (bbt[i].bad_block == blk))
		{
			cs = bbt[i].RB_die;
			blk = bbt[i].remap_block;
			printf(" 0x%x remap to (%x, 0x%x)\n",bbt[i].bad_block,   cs, blk);
			continue;
		}
	}
	// return final remapping result
	*chip_sel = cs;
	*block_no = blk;

	return;
}
static int nf_map_phys_page(n_device_type *device, UINT8 *chip_select, UINT32 *phys_page)
{
	UINT8 i;

	// do not need to calculate page offset in single chip case
	if (total_chip_num == 1)
	{
		*chip_select = 0;
		return 0;
	}

	for (i = 0; i < total_chip_num; i++)
	{
		if (*phys_page < pages_per_chip)
		{
			*chip_select = i;
			return 0;
		}

		*phys_page -= pages_per_chip;
	}

	return -1;

}


/* calculate the chip_select # & the page offset on it  after remapping*/

static int nf_map_page(n_device_type *device, UINT8 *chip_select, UINT32 *phys_page)
{
	UINT8 i;
	UINT32 block_offset, page_offset;
	UINT32 temp;


	if (total_chip_num == 1)
	{
		*chip_select = 0;	// only one possible chip select
		block_offset = *phys_page / pages_per_block;
		page_offset = *phys_page % pages_per_block;
	}
	else
	{
		*chip_select = *phys_page / pages_per_chip;
		temp = *phys_page % pages_per_chip;
		block_offset = temp / pages_per_block;
		page_offset = temp % pages_per_block;
	}

	// remap bad block

	remapped_bbt(chip_select, &block_offset);
	// calculate physical pages address
	*phys_page = block_offset * pages_per_block + page_offset;

	return 0;

}

static int map_phys_block(n_device_type *device, UINT8 *chip_select, UINT32 *phys_block)
{
	UINT32 blocks_per_chip;
	UINT8 i;

	// do not need to calculate block offset in single chip case
	if (total_chip_num == 1)
	{
		*chip_select = 0;
		return 0;
	}

	blocks_per_chip = pages_per_chip / pages_per_block;

	for (i = 0; i < total_chip_num; i++)
	{
		if (*phys_block < blocks_per_chip)
		{
			*chip_select = i;
			return 0;
		}

		*phys_block -= blocks_per_chip;
	}

	return -1;
}


static int nf_read_single_byte(n_device_type *device, UINT32 col_addr, UINT32 page_addr, UINT8 *data)
{
	UINT8 cs;

	if (nf_map_phys_page(device, &cs, &page_addr))
		return -1;

	return nf_read_phys_single_byte(device, cs, col_addr, page_addr, data);
}

static int nf_read_phys_single_byte(n_device_type *device, UINT8 chip_sel, UINT32 col_addr, UINT32 page_addr, UINT8 *data)
{
	// Set chip select
	rtd_outl(REG_Chip_En, NF_CHIP_SEL(chip_sel));

	//Set not using PP
	rtd_outl(REG_PP_RDY, 0x0);
	rtd_outl(REG_PP_CTL0, 0x0);
	//REG32(REG_PP_CTL1) = 0;

	//Set table sram
	rtd_outl(REG_TABLE_CTL, 0);

	//Set command
	rtd_outl(REG_CMD1, 0x0);
	rtd_outl(REG_CMD2, 0x30);
	rtd_outl(REG_CMD3, 0x70);

	//Set address
	rtd_outl(REG_PAGE_ADR0, page_addr & 0xff);
	rtd_outl(REG_PAGE_ADR1, page_addr >> 8);
	rtd_outl(REG_PAGE_ADR2, (device->addr_mode_rw << 5) | ((page_addr >> 16) & 0x1f));
	rtd_outl(REG_PAGE_ADR3, ((page_addr >> 21)&0x7) << 5);
	rtd_outl(REG_COL_ADR0, col_addr & 0xff);
	rtd_outl(REG_COL_ADR1, col_addr >> 8);

	//Set ECC
	//rtd_outl(REG_MultiChMod, 0x20);		// no EDO
	rtd_outl(REG_MultiChMod, 0x00);		// no EDO
	rtd_outl(REG_ECC_STOP,0x80);

	//Enable Auto mode
	rtd_outl(REG_AUTO_TRIG,0x80| (0x1 << 3) | 0x2);	// only CMD/Address cycle of read 2K
	while( rtd_inl(REG_AUTO_TRIG)&0x80 );

	// check ready/busy pin of NAND flash
	while ((rtd_inl(REG_CTL)&0x40) == 0);

	// read single byte data in transfer mode
	rtd_outl(REG_CTL, 0x80 | 0x2);
	while( rtd_inl(REG_CTL)&0x80 );

	*data = rtd_inl(REG_DATA) & 0xff;
	return 0;
}

static UINT8 nf_spare_ddr_enabled(void)
{
        return ((rtd_inl(REG_SPR_DDR_CTL) >> 30) & 0x1);
}

static UINT32 nf_get_auto_transfer_unit(UINT8 ecc_type)
{
	if ((ecc_type == ECC_6BIT) || (ecc_type == ECC_12BIT))
		return 512;
	else
		return 1024;
}
/************************************************************************
 *
 *                          do_read_n
 *  Description :
 *  -------------
 *  implement the flash read
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_read_n(void *dev,
               unsigned int*  start_blk,	// start of block NO.
               unsigned char* dest,		// dest memory address
               unsigned int   rem_size,		// request data length
               unsigned int   signature)
{
	n_device_type *device = (n_device_type *)dev;
	UINT32 i, page_len, tmp;
	UINT8 state;

#ifdef ENABLE_NAND_DRIVER
	// search block state table
	if ((signature) && (*start_blk < blk_state_len))
	{
		for (i = *start_blk; i < blk_state_len; i++)
		{
			tmp = 0;
			get_block_state(i, &state);
			if (state == BLOCK_BAD) {
				UINT32 page_no;
				UINT32 cs;
				INT8 res;
				UINT32 spr_ddr_ctrl;

				//printf("meet bad block \n");//cy test
				if (nf_spare_ddr_enabled()) {
					spr_ddr_ctrl = rtd_inl(REG_SPR_DDR_CTL);	// save original setting
					rtd_outl(REG_SPR_DDR_CTL, ~0x40000000);	// turn off spare to DDR
				}
				else
					spr_ddr_ctrl = 0;

				page_no = i*pages_per_block;

				res = nf_read_to_PP(device, page_no);
				if (!res)
				{
					nf_get_spare(0x2, &tmp, 0);
					state = tmp && 0xff;
					//printf("new block state=0x%x \n",state);
				}
				if (spr_ddr_ctrl != 0)
					rtd_outl(REG_SPR_DDR_CTL, spr_ddr_ctrl);	// restore to original setting

			}

			if (state == signature)
			{
				*start_blk = i;
				break;
			}
		}

		if (i == blk_state_len)
			return -1;		// not found
	}

	// align data length to page boundary
	page_len = rem_size / device->PageSize;
	if (rem_size % device->PageSize)
		page_len++;

	return nf_read(device, (*start_blk * pages_per_block), dest,
					(page_len * device->PageSize));

#endif
}
static int nand_profile_exist(const void *dev)
{
	UINT8 state = 0;
	int res;
	unsigned int checksum;
	t_nand_profile *profile;
	n_device_type *device = (n_device_type *)dev;

	// first check block state
	get_block_state(0, &state);
	if (state != BLOCK_OTHER_DATA) {
		printf("[%x] profile not exist\n", state);
		return 0;
	}

	// then try to read profile
	res = nf_read_page(device, 0, (UINT8 *)PAGE_TMP_ADDR, 0);
	if (res == -1) {
		printf("read profile error\n");
		return 0;
	}

	// check profile identifier
	profile = (t_nand_profile *)PAGE_TMP_ADDR;
	res = compare_memory(profile->identifier, NAND_PROFILE_IDENTIFIER,
		strlen(NAND_PROFILE_IDENTIFIER));
	if (res) {
		char *ptr;

		printf("wrong profile identifier:\n\t");
		for (res = 0; res < sizeof(profile->identifier); res++)
			printf("%2x ", profile->identifier[res]);
		printf("\n\t");
		ptr = NAND_PROFILE_IDENTIFIER;
		for (res = 0; res < strlen(NAND_PROFILE_IDENTIFIER); res++)
			printf("%2x ", ptr[res]);
		return 0;
	}

	checksum = accumulate_byte_value(profile, 128);
	if (checksum != *((unsigned int *)profile->checksum)) {
		printf("profile checksum not match (%x <> %x)\n",
			checksum, *((unsigned int *)profile->checksum));
		return 0;
	}

	return 1;
}

static int build_nand_profile(const void *dev, t_nand_profile *profile)
{
	unsigned int tmp, checksum;
	n_device_type *device = (n_device_type *)dev;

	if ((dev == NULL) || (profile == NULL)) {
		return -1;
	}

	// build NAND profile
	copy_memory(profile->identifier, NAND_PROFILE_IDENTIFIER, sizeof(NAND_PROFILE_IDENTIFIER));
	profile->revision = 0x2;

	for (tmp = 0; tmp < 4; tmp++)
		profile->manufacturer_id[tmp] = (device->id >> (tmp * 8)) & 0xff;

	if (device->read_id_len > 4) {
		profile->manufacturer_id[tmp] = device->id5;
		tmp++;

		if (device->read_id_len > 5)
			profile->manufacturer_id[tmp] = device->id6;
	}

	if (strlen(device->string) < (sizeof(profile->flash_name) - 1))
		tmp = strlen(device->string);
	else
		tmp = sizeof(profile->flash_name) - 1;

	copy_memory(profile->flash_name, device->string, tmp);

	profile->number_of_bbt = 2;
	profile->bbt_start_block = 0x1;
	profile->bbt_end_block = 0x2;
	profile->number_of_rsv_block = blocks_per_flash * RBA_PERCENTAGE / 100;
	profile->rsv_start_block = blocks_per_flash - profile->number_of_rsv_block;
	profile->rsv_end_block = blocks_per_flash - 1;
	profile->data_per_page = device->PageSize;

	switch (device->ecc_bit) {
		case ECC_6BIT:
			tmp = 16 * (device->PageSize / 512);
			break;
		case ECC_12BIT:
			tmp = 32 * (device->PageSize / 512);
			break;
		case ECC_16BIT:
		case ECC_24BIT:
		case ECC_40BIT:
		case ECC_43BIT:
		case ECC_65BIT:
		case ECC_72BIT:
			tmp = 128 * (device->PageSize / 1024);
			break;
		default:	// unknown type
			return -1;
	}

	profile->oob_per_page = tmp;
	profile->page_per_block = pages_per_block;
	profile->block_per_die = blocks_per_flash;
	profile->ecc_bit = device->ecc_bit;
	profile->param_t1 = device->t1;
	profile->param_t2 = device->t2;
	profile->param_t3 = device->t3;
	profile->address_mode = device->addr_mode_rw;
	
	checksum = accumulate_byte_value(profile, 128);
	//modify by angus, rtd299x doesn't endian invert
	//for (tmp = 0; tmp < 4; tmp++)
		//profile->checksum[tmp] = (checksum >> (tmp * 8)) & 0xff;
	*(unsigned int *)profile->checksum = checksum;

	return 0;
}

static int write_nand_profile(const void *dev, t_nand_profile *profile)
{
	UINT8 state = 0;
	n_device_type *device = (n_device_type *)dev;

	if ((dev == NULL) || (profile == NULL) )
		return -1;

	if (sizeof(t_nand_profile) > device->PageSize) {
		printf("NAND profile exceed one page\n");
		return -2;
	}

	copy_memory((UINT8 *)PAGE_TMP_ADDR, profile, sizeof(t_nand_profile));
	set_memory((UINT8 *) (PAGE_TMP_ADDR + sizeof(t_nand_profile)), 0xff, device->PageSize - sizeof(t_nand_profile));

	get_block_state(0, &state);
	if (state != BLOCK_CLEAN) {
		// erase block 0
		if (nf_erase_block(device, 0)) {
			printf("erase block 0 error\n");
			return -3;
		}
	}

	// write profile into page 0
	nf_set_spare(BLOCK_OTHER_DATA, 0);
	if (nf_write(device, 0, (UINT8 *)PAGE_TMP_ADDR, device->PageSize)) {
		prints("write NAND profile failed\n");
		set_block_state(0, BLOCK_BAD);
		return -4;
	}
	else
		set_block_state(0, BLOCK_BBT);

	return 0;
}

static int write_nand_profile_bak(const void *dev, t_nand_profile *profile)
{
	UINT8 state = 0;
        UINT32 pageNum = 0;
	n_device_type *device = (n_device_type *)dev;

	if ((dev == NULL) || (profile == NULL) )
		return -1;

	if (sizeof(t_nand_profile) > device->PageSize) {
		printf("NAND profile exceed one page\n");
		return -2;
	}

	copy_memory((UINT8 *)PAGE_TMP_ADDR, profile, sizeof(t_nand_profile));
	set_memory((UINT8 *) (PAGE_TMP_ADDR + sizeof(t_nand_profile)), 0xff, device->PageSize - sizeof(t_nand_profile));

	get_block_state(3, &state);
	if (state != BLOCK_CLEAN) {
		// erase block 0
		if (nf_erase_block(device, 3)) {
			printf("erase block 3 error\n");
			return -3;
		}
	}

	// write profile into page 0
	nf_set_spare(BLOCK_OTHER_DATA, 0);

    if (device->ecc_bit == ECC_6BIT || device->ecc_bit == ECC_12BIT) {	
            prints("SLC\n");
            pageNum = 64 * 3;
    }else{
            prints("MLC\n");
            pageNum = 256 * 3;
    }

	if (nf_write(device, pageNum, (UINT8 *)PAGE_TMP_ADDR, device->PageSize)) {
		prints("write NAND profile failed\n");
		set_block_state(3, BLOCK_BAD);
		return -4;
	}
	else
		set_block_state(3, BLOCK_BBT);

	return 0;
}

static unsigned int accumulate_byte_value(const void *buf, unsigned int length)
{
	unsigned int i, res;
	unsigned char *ptr = (unsigned char *)buf;

	if ((buf == NULL) || (length == 0))
		return 0;

	for (i = res = 0; i < length; i++)
		res += ptr[i];

	return res;
}

static UINT8 nf_is_random_mode(void)
{
	return rtd_inl(REG_RND_EN) & 0x1;
}

static void nf_enable_random_mode(void)
{
	//REG32(REG_RND_EN) |= 0x1;
	rtd_outl(REG_RND_EN,rtd_inl(REG_RND_EN) | 0x1);
}

static void nf_disable_random_mode(void)
{
	//REG32(REG_RND_EN) &= ~0x1;
	rtd_outl(REG_RND_EN,rtd_inl(REG_RND_EN) & (~0x1));
}

static void nf_set_random_read(n_device_type *device,unsigned int spare_col)
{
	rtd_outl(REG_RND_CMD1, 0x5);
	rtd_outl(REG_RND_CMD2, 0xe0);
	rtd_outl(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
	rtd_outl(REG_RND_SPR_STR_COL_H, (spare_col+ device->PageSize) >> 8);	// spare start address MSB
	rtd_outl(REG_RND_SPR_STR_COL_L, (spare_col+ device->PageSize) & 0xff);	// spare start address LSB
}

static void nf_set_random_write(n_device_type *device,unsigned int spare_col)
{
	rtd_outl(REG_RND_CMD1, 0x85);
	rtd_outl(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)

        if(force_2k==1){
            prints("force 2K.\n");
                rtd_outl(REG_RND_SPR_STR_COL_H, (spare_col+ 0x800) >> 8);	// spare start address MSB
	        rtd_outl(REG_RND_SPR_STR_COL_L, (spare_col+ 0x800) & 0xff);	// spare start address LSB
        }else{
    
	rtd_outl(REG_RND_SPR_STR_COL_H, (spare_col+ device->PageSize) >> 8);	// spare start address MSB
	rtd_outl(REG_RND_SPR_STR_COL_L, (spare_col+ device->PageSize) & 0xff);	// spare start address LSB
            }
}

