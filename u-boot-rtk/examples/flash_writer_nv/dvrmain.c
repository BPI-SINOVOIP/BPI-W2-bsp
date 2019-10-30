#ifdef FPGA
#include <stdio.h>
#include <stdlib.h>
#endif
#include "project_config_f.h"
#include "extern_param.h"
#include "shell_golinux.h"
#include "platform_iso.h"
#include "flashdev_n.h"
#include "flashdev_e.h"
#include "flashdev_s.h"
#include "otp.h"
#include "dvrboot_inc/mis_reg.h"
#include "dvrboot_inc/sys_reg.h"
#include "dvrboot_inc/util.h"
#include "dvrboot_inc/mcp.h"
#include "dvrboot_inc/string.h"
#include "uart.h"
#include "BootPartition_wrapper.h"
#include "iso_reg.h"

#define FLASH_MAGICNO_NOR_PARALLEL		0xBE
#define FLASH_MAGICNO_NAND				0xCE
#define FLASH_MAGICNO_NOR_SERIAL		0xDE
#define FLASH_MAGICNO_EMMC	 			0xEE

#define EXT_PARA_DDR_BASE				(0xA0A00000 - UBOOT_DDR_OFFSET)	// t_extern_param + logo + rescue base address on DDR
#define NAND_ENV_DDR_BASE				(0xA0040000 - UBOOT_DDR_OFFSET)	// modify by angus, original value is 0xa0010000

#define BOOTCODE_SIZE_ADDR				0XB801A60C
#define SIMULATION_DUMP_ADDR			(0xA3000000 - UBOOT_DDR_OFFSET)	// dump bootcode array to DDR
#define NAND_BOOT_BACKUP_COUNT			3								// number of backup bootcode in NAND flash

#define BOOTCODE_MAX_SIZE               0xC0000
#define SECURE_OS_MAX_SIZE              0xC0000
#define MAX_BOOTCODE_FW_SIZE            0x100000

extern unsigned char scpu_resetrom[];	//scpu rom data : 0x8810_0000~8812_B000
extern unsigned char scpu_resetrom_end;
extern unsigned char pcpu_resetrom[];	//pcpu rom data : 0x8812_B000~8812_F000
extern unsigned char pcpu_resetrom_end;
extern unsigned char acpu_resetrom[];	//acpu rom data : 0x8812_F000~8813_0000
extern unsigned char acpu_resetrom_end;
extern unsigned char eMMC_bootarray_fw_table[];
extern unsigned char eMMC_bootarray_fw_table_end;
extern unsigned char spi_bootarray_fw_table[];
extern unsigned char spi_bootarray_fw_table_end;

extern unsigned char nand_bootarray_fw_table_128KB[];
extern unsigned char nand_bootarray_fw_table_128KB_end;
extern unsigned char nand_bootarray_fw_table_256KB[];
extern unsigned char nand_bootarray_fw_table_256KB_end;

extern unsigned char nocs_certificate[];
extern unsigned char nocs_certificate_end;
extern unsigned char atf_certificate[];
extern unsigned char atf_certificate_end;
extern unsigned char pcpu_certificate[];
extern unsigned char pcpu_certificate_end;
extern unsigned char dte_fw_certificate[];
extern unsigned char dte_fw_certificate_end;
extern unsigned char afw_certificate[];
extern unsigned char afw_certificate_end;
extern unsigned char scs_params_area[];
extern unsigned char scs_params_area_end;
extern unsigned char rtk_params_area[];
extern unsigned char rtk_params_area_end;
extern unsigned char auxcode_area[];
extern unsigned char auxcode_area_end;
extern unsigned char dte_bootcode_area[];
extern unsigned char dte_bootcode_area_end;
extern unsigned char dte_bootcode_rtk_area[];
extern unsigned char dte_bootcode_rtk_area_end;

extern unsigned char secure_os[];
extern unsigned char secure_os_end;
extern unsigned char bl31[];
extern unsigned char bl31_end;
extern unsigned char pcpu_code_area[];
extern unsigned char pcpu_code_area_end;


extern unsigned int  pages_per_block;
extern unsigned int  blocks_per_flash;

extern unsigned int  mcp_dscpt_addr;

unsigned char  verify_after_write;
unsigned char  force_secure;
unsigned char  test_secure;
unsigned char  noreset;

PrintFuncPtr_t 			rtprintf=NULL;
Flush_Dcache_AllPtr_t 	rtflush_dcache_all=NULL;
Flush_CachePtr_t  		rtflush_cache=NULL;

unsigned int g_BlockSize;

/************************************************************************
 *
 ************************************************************************/
unsigned int align_to_boundary(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? size / block_size + 1 : size / block_size);
}

unsigned int align_to_boundary_length(unsigned int size, unsigned int block_size)
{
    return (size % block_size ? (size / block_size + 1)*block_size : (size / block_size)*block_size );
}

void set_spi_pin_mux(void)
{
#ifndef FPGA
	unsigned int chip_id = REG32(SB2_CHIP_ID);

	switch (chip_id) {
		case CHIP_ID_1395: // for bring up use, can be removed later
			//1395 set mux to spi
			REG32(ISO_muxpad5) &= 0xFFFFFF00;	//clear [7:0]
			//set sf_en=1
			REG32(ISO_muxpad6) |= 0x800;
			break;
		case CHIP_ID_161x:
		default:
			//1619 set mux to spi
			REG32(ISO_muxpad1) = 0x2db400;	//set [21:10]
			//set sf_en=1
			REG32(ISO_muxpad6) |= 0x800;
			break;
	}
#endif
}

void set_nand_pin_mux(void)
{
#ifndef FPGA
	unsigned int set_pad;
	unsigned int chip_id = REG32(SB2_CHIP_ID);

	switch (chip_id) {
		case CHIP_ID_1395: // for bring up use, can be removed later
			//1395 ISO_muxpad4
			//set mux to nf
			REG32(ISO_muxpad4) = 0x00555555;
			REG32(ISO_muxpad5) &= 0xFFFFFFC0;  //clear [5:0]
			REG32(ISO_muxpad5) |= 0x15;
			//set sf_en=0
			REG32(ISO_muxpad6) &= 0xFFFFF7FF;  //clear [11]
			break;
		case CHIP_ID_161x:
		default:
			//1619 m2tmx_muxpad0
			//set mux to nf
			set_pad = REG32(m2tmx_muxpad0);
			set_pad &= 0xE0000019;
			set_pad |= 0xAAAAAA2; //set [2:1], [28:5]
			REG32(m2tmx_muxpad0) = set_pad;
			//set sf_en=0
			set_pad = REG32(m2tmx_muxpad1);
			set_pad &= 0xFFFFFFF8;
			set_pad |= 0x1; //set [2:0]
			REG32(m2tmx_muxpad1) = set_pad;
			break;
	}
#endif
}

void set_emmc_freq()
{
	//1295
	REG32(SYS_PLL_EMMC2) = 0x031C0001;
	REG32(SYS_PLL_EMMC3) = 0x00AF0000;
	REG32(SYS_PLL_EMMC4) = 0x00000007;

	REG32(EMMC_CKGEN_CTL) = 0x2102;
	REG32(SYS_NF_CKSEL) = 0x5;
	sync();
}

void set_emmc_pin_mux(void)
{
#ifndef FPGA
	unsigned int chip_id = REG32(SB2_CHIP_ID);

	switch (chip_id) {
		case CHIP_ID_1395: // for bring up use, can be removed later
			//1395 ISO_muxpad4
			//set mux to emmc
			REG32(ISO_muxpad4) = 0x00aaaaaa;
			//set sf_en=1
			REG32(ISO_muxpad6) |= 0x800;
			break;
		case CHIP_ID_161x:
		default:
			//1619 m2tmx_muxpad0
			//set mux to emmc
			REG32(m2tmx_muxpad0) = 0x55555554;
			//set sf_en=1
			REG32(m2tmx_pfunc6) |= 0x800;
			break;
	}
#endif
}

/************************************************************************
 * get uboot domain function pointer to dvrmain domain function pointer
 ************************************************************************/
void rebuild_function_pointer_from_uboot_to_dvrmain( void )
{
    // get fun ptr of printf(...) from specified address
    #define DUMMY                               (*((unsigned int *)0x00020060))
    #define DUMMY2                              (*((unsigned int *)0x00020064))
    #define UBOOT_PRINTF_ADDRESS_TAG            (*((unsigned int *)0x00020068))
    #define UBOOT_PRINTF_ADDRESS                (*((unsigned int *)0x0002006C))
    #define UBOOT_FLUSH_DCACHE_ALL_ADDRESS_TAG  (*((unsigned int *)0x00020070))
    #define UBOOT_FLUSH_DCACHE_ALL_ADDRESS      (*((unsigned int *)0x00020074))
    #define UBOOT_FLUSH_CACHE_ADDRESS_TAG       (*((unsigned int *)0x00020078))
    #define UBOOT_FLUSH_CACHE_ADDRESS           (*((unsigned int *)0x0002007C))

    if( UBOOT_PRINTF_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        rtprintf = (PrintFuncPtr_t) (UBOOT_PRINTF_ADDRESS);
        rtprintf("\n\nHello World(%s %s), get printf ptr=%p\n\n", __DATE__, __TIME__, rtprintf);
    }
    else {
        rtprintf = NULL;
    }

    if( UBOOT_FLUSH_DCACHE_ALL_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        rtflush_dcache_all = (Flush_Dcache_AllPtr_t) (UBOOT_FLUSH_DCACHE_ALL_ADDRESS);
    }
    else {
        rtflush_dcache_all = NULL;
    }

    if( UBOOT_FLUSH_CACHE_ADDRESS_TAG == CODE_VAILD_MAGIC_NUMBER ) {
        if (UBOOT_FLUSH_CACHE_ADDRESS != UBOOT_PRINTF_ADDRESS) // prevent side effect
        {
            rtflush_cache = (Flush_CachePtr_t) (UBOOT_FLUSH_CACHE_ADDRESS);
        }
        else
        {
            rtflush_cache = NULL;
        }
    }
    else {
        rtflush_cache = NULL;
    }
}

unsigned int get_chip_rev_id()
{
    return REG32(SB2_CHIP_INFO);
}
/************************************************************************
 *
 *  dvrmain
 *  Description :
 *  -------------
 *  main function of flash writer
 *  attention:
 *  1. since 0xbfc0_0000 ~ 0xbfc0_1fff occupied by ROM code,
 *     space from 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash can not be utilized.
 *     In order to write data to the space, we shift writing address space from
 *     0xbed0_0000 ~ 0xbfcf_ffff to 0xbdd0_0000 ~ 0xbecf_ffff. So that we can
 *     access to space 0xbfc0_0000 ~ 0xbfc0_1fff in NOR flash.
 *  2. we left 0xbecf_f000 ~ 0xbecf_ffff for ext_param.
 *  3. ext_param is located from 0xbecf_f800.
 *
 *  Parameters :
 *  Return values :
 *
 ************************************************************************/
int dvrmain	( int argc, char * const argv[] )
{
    // spi used
    unsigned char * spi_scpu_resetrom_addr;
	unsigned char * spi_pcpu_resetrom_addr;
    unsigned char * spi_acpu_resetrom_addr;
	unsigned char * spi_bootarray_fw_table_addr;
    unsigned char * spi_param_addr;

    unsigned char * spi_next_fw_start_addr;

    unsigned int  scpu_resetrom_size;
	unsigned int  pcpu_resetrom_size;
    unsigned int  acpu_resetrom_size;
	unsigned int  bootarray_fw_table_size;

            unsigned int  programmed_fw_bootarray_fw_table_nand_128KB_size;
            unsigned int  programmed_fw_bootarray_fw_table_nand_256KB_size;
            unsigned char * programmed_fw_table_base_128KB;
            unsigned char * programmed_fw_table_base_256KB;

	unsigned int  nocs_certificate_size;
	unsigned int  atf_certificate_size;
	unsigned int  pcpu_certificate_size;
	unsigned int  dte_fw_certificate_size;
	unsigned int  afw_certificate_size;
	unsigned int  scs_params_area_size;
	unsigned int  scs_area_size;
	unsigned int  cert_area_size;
	unsigned int  rtk_params_area_size;
	unsigned int  auxcode_area_size;
	unsigned int  dte_bootcode_area_size;
    unsigned char * env_param_addr;

	//DTE_Bootcode_RTK (LK or Uboot64)
    unsigned int    dte_bootcode_rtk_area_size;

	unsigned char * programmed_secure_os_base;
	unsigned int	programmed_secure_os_size;

    unsigned char * programmed_bl31_base;
	unsigned int	programmed_bl31_size;

	//PCPU Code Area
	unsigned char * programmed_pcpu_code_base;
	unsigned int	programmed_pcpu_code_size;

    unsigned char   flash_type;
    unsigned char   flash_magicno;
    unsigned int    idx, i, j;
    unsigned int    temp, reg_addr;
	void * device;
    int res;
    int save_nand_env;

    unsigned int  block_size;
    unsigned int  total_block_cnt;

    t_extern_param param;
    t_extern_param *orignal_param;

	// -------------------------------------------------------------------------
	// function declaration
	// -------------------------------------------------------------------------
    int (*do_erase)(void  *, unsigned int * , unsigned int);
    int (*do_write)(void *, unsigned char *, unsigned int *, unsigned int, unsigned int, const unsigned int);
    int (*do_identify)(void **);
    int (*do_init)(void *);
    int (*do_read)(void *, unsigned int *, unsigned char *, unsigned int, INT32);
    void (*do_exit)(void *dev);

    // -------------------------------------------------------------------------
	// copy uboot domain fun pointer to dvrmoan domain
	// -------------------------------------------------------------------------
	#ifndef FOR_ICE_LOAD
	rebuild_function_pointer_from_uboot_to_dvrmain();
    #else
	// make a copy here to avoid flush function pointer being invalid.
	rebuild_function_pointer_from_uboot_to_dvrmain();
    init_uart();
    set_focus_uart(0); //default : uart0
	#endif

	// -------------------------------------------------------------------------
	// initial global variable
	// -------------------------------------------------------------------------
	block_size = 0x00001000;													// block size == 4096 bytes
	total_block_cnt = 0x00100000 / block_size;									// 256 blocks for 1MB ( 0xbec0_0000~0xbecf_ffff )
	mcp_dscpt_addr = 0;

	// -------------------------------------------------------------------------
	// initial local variable
	// -------------------------------------------------------------------------
	// sort by address value
	scpu_resetrom_size  		  = (unsigned int )(&scpu_resetrom_end  	   - scpu_resetrom);
	pcpu_resetrom_size  		  = (unsigned int )(&pcpu_resetrom_end  	   - pcpu_resetrom);
	acpu_resetrom_size  		  = (unsigned int )(&acpu_resetrom_end  	   - acpu_resetrom);

	nocs_certificate_size = (unsigned int )(&nocs_certificate_end  - nocs_certificate);
	atf_certificate_size = (unsigned int )(&atf_certificate_end  - atf_certificate);
	pcpu_certificate_size = (unsigned int )(&pcpu_certificate_end  - pcpu_certificate);
	dte_fw_certificate_size = (unsigned int )(&dte_fw_certificate_end  - dte_fw_certificate);
	afw_certificate_size = (unsigned int )(&afw_certificate_end  - afw_certificate);
	if (nocs_certificate_size != 1024){
		prints("Error: nocs_certificate_size != 1KB \n");
		return -1;
	}
	if (atf_certificate_size != 1024){
		prints("Error: atf_certificate_size != 1KB \n");
		return -1;
	}
	if (pcpu_certificate_size != 1024){
		prints("Error: pcpu_certificate_size != 1KB \n");
		return -1;
	}
	if (dte_fw_certificate_size != 1024){
		prints("Error: dte_fw_certificate_size != 1KB \n");
		return -1;
	}
	if (afw_certificate_size != 1024){
		prints("Error: afw_certificate_size != 1KB \n");
		return -1;
	}

	scs_params_area_size = (unsigned int )(&scs_params_area_end  - scs_params_area);
	rtk_params_area_size = (unsigned int )(&rtk_params_area_end  - rtk_params_area);
	auxcode_area_size = (unsigned int )(&auxcode_area_end  - auxcode_area);
	dte_bootcode_area_size = (unsigned int )(&dte_bootcode_area_end  - dte_bootcode_area);
	dte_bootcode_rtk_area_size = (unsigned int )(&dte_bootcode_rtk_area_end - dte_bootcode_rtk_area);

    // tee os
	programmed_secure_os_size       = (unsigned int )(&secure_os_end - secure_os);
    programmed_secure_os_base       = secure_os;

    // bl31
    programmed_bl31_size       = (unsigned int )(&bl31_end - bl31);
    programmed_bl31_base       = bl31;

	// pcpu code
	programmed_pcpu_code_size	   = (unsigned int )(&pcpu_code_area_end - pcpu_code_area);
	programmed_pcpu_code_base	   = pcpu_code_area;

    spi_scpu_resetrom_addr  	 = (unsigned char *)SPI_CODE_PART1_1; //assign scpu romcode start address
    spi_pcpu_resetrom_addr  	 = (unsigned char *)SPI_CODE_PART1_2; //assign pcpu romcode start address
    spi_acpu_resetrom_addr  	 = (unsigned char *)SPI_CODE_PART1_3; //assign acpu romcode start address
    spi_param_addr 				 = (unsigned char *)(SPI_ENV_PARAM_ADDR);
	spi_bootarray_fw_table_addr	 = (unsigned char *)(SPI_ENV_PARAM_ADDR + SPI_MAX_PARAM_SIZE);  //0x8813_0000 + 0x800
    spi_next_fw_start_addr       = (unsigned char *)(SPI_ENV_PARAM_ADDR + SPI_MAX_PARAM_SIZE + SPI_BOOTARRAY_FW_TABLE_SIZE);//0x8813_0000 + 0x800 + 0x400

    /* reserve one block in 0xbecf_f000 ~ 0xbecf_ffff for ext_param */
    total_block_cnt = total_block_cnt - 1;

    /***********************************************************************
     * determine flash type and program flow
     * 0 for nand flash		FLASH_TYPE_NAND
     * 1 for spi nor		FLASH_TYPE_SPI
     * 2 for eMMC		FLASH_TYPE_EMMC
     ***********************************************************************/
    verify_after_write = 0;
    force_secure = 0;
    test_secure = 0;
    noreset = 0;

#if defined(FPGA_BOOT_NAND) || defined(RTK_FLASH_NAND)
    flash_type = FLASH_TYPE_NAND;
    verify_after_write = 1;
#elif defined(FPGA_BOOT_EMMC) || defined(RTK_FLASH_EMMC)
    flash_type = FLASH_TYPE_EMMC;
    verify_after_write = 1;
#else
    flash_type = FLASH_TYPE_SPI;
#endif

    rtprintf("flash_type: ");
    #ifdef FOR_ICE_LOAD
    prints("flash_type: ");
    #endif
    switch( flash_type )
    {
    	case FLASH_TYPE_SPI:
            #ifdef FOR_ICE_LOAD
            prints("SPI\n");
            #endif
	    	rtprintf("SPI\n");
	    	flash_magicno     = FLASH_MAGICNO_NOR_SERIAL;
	    	do_erase          = do_erase_s;
	    	do_write          = do_write_s;
	    	do_identify       = do_identify_s;
	    	do_init           = do_init_s;
	    	do_exit           = do_exit_s;
	    	do_read           = NULL;
	    	env_param_addr    = (unsigned char *)SPI_ENV_PARAM_ADDR;
			bootarray_fw_table_size 	  = (unsigned int )(&spi_bootarray_fw_table_end    - spi_bootarray_fw_table);
    		break;

    	case FLASH_TYPE_EMMC:
            #ifdef FOR_ICE_LOAD
            prints("eMMC\n");
            #endif
	    	rtprintf("eMMC\n");
	    	flash_magicno     = FLASH_MAGICNO_EMMC;
	    	do_erase          = do_erase_e;
	    	do_write          = do_write_e;
	    	do_identify       = do_identify_e;
	    	do_init           = do_init_e;
	    	do_exit           = do_exit_e;
	    	do_read           = do_read_e;
	    	env_param_addr    = (unsigned char *)NAND_ENV_DDR_BASE;
			bootarray_fw_table_size 	  = (unsigned int )(&eMMC_bootarray_fw_table_end    - eMMC_bootarray_fw_table);
    		break;

    	case FLASH_TYPE_NAND:
            #ifdef FOR_ICE_LOAD
            prints("nand\n");
            #endif
			rtprintf("nand\n");
	    	flash_magicno     = FLASH_MAGICNO_NAND;
	    	do_erase          = do_erase_n;
	    	do_write          = do_write_n;
	    	do_identify       = do_identify_n;
	    	do_init           = do_init_n;
	    	do_exit           = do_exit_n;
	    	do_read           = NULL;
	    	env_param_addr    = (unsigned char *)NAND_ENV_DDR_BASE;
			if ((&nand_bootarray_fw_table_128KB_end - nand_bootarray_fw_table_128KB) != 1024){
				prints("Error: nand bootarray_fw_table_size for page size 128KB is not equal to 1KB !! \n");
				return -1;
			}
			if ((&nand_bootarray_fw_table_256KB_end - nand_bootarray_fw_table_256KB) != 1024){
				prints("Error: nand bootarray_fw_table_size for page size 256KB is not equal to 1KB !! \n");
				return -1;
			}
                                programmed_fw_bootarray_fw_table_nand_128KB_size 	  = (unsigned int )(&nand_bootarray_fw_table_128KB_end - nand_bootarray_fw_table_128KB);
                                programmed_fw_bootarray_fw_table_nand_256KB_size 	  = (unsigned int )(&nand_bootarray_fw_table_256KB_end - nand_bootarray_fw_table_256KB);

                                programmed_fw_table_base_128KB = nand_bootarray_fw_table_128KB;
                                programmed_fw_table_base_256KB = nand_bootarray_fw_table_256KB;

			bootarray_fw_table_size 	  = programmed_fw_bootarray_fw_table_nand_128KB_size;
    		break;

    	default:
            #ifdef FOR_ICE_LOAD
            prints("unknown!\n");
            #endif
    		rtprintf("unknown!\n");
    		return -1;

    		break;
    }

	if (bootarray_fw_table_size != 1024){
		prints("Error: bootarray_fw_table_size is not equal to 1KB !! \n");
		return -1;
	}

    /***********************************************************************
     * assign value to param object
     ***********************************************************************/
    param.flash_type 		 	= flash_magicno;
    param.region     		 	= 0;

	param.mac_hi     		 	= Param_MAC_hi;
	param.mac_lo     		 	= Param_MAC_lo;

    param.array_img_saddr        = 0;
    param.array_img_size         = 0;
	// clear hdmi key
	for (i = 0; i < sizeof(param.hdmi_key1); i++)
		param.hdmi_key1[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key2); i++)
		param.hdmi_key2[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key3); i++)
		param.hdmi_key3[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key4); i++)
		param.hdmi_key4[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key5); i++)
		param.hdmi_key5[i] = 0;
	for (i = 0; i < sizeof(param.hdmi_key6); i++)
		param.hdmi_key6[i] = 0;

	set_memory(param.custom_field, 0, sizeof(param.custom_field));

    param.env_param_saddr = env_param_addr;
    param.data_start_blk = 0;

    //dump 'Begin' string to RS232 to notify uset that flash write start to program
	#ifdef FOR_ICE_LOAD
    prints("begin: \n");
    #endif
    rtprintf("Begin:");

	if( flash_magicno == FLASH_MAGICNO_NAND )
	{
		unsigned int current_block = 0;
		unsigned int end_page;
		unsigned int buf_start = DATA_TMP_ADDR;
		unsigned int data_lentgh;
		unsigned int pagesize, blocksize, pagePerBlock;
		unsigned int supposed_block;
		unsigned int backup_number;

		// we leave block empty: 0 for nand profile, 1, 2 (for BBT use), 3, 4 for GBT , 5 reversed
		current_block+=6;
	    /***********************************************************************
	     * identyfy flash type
	     ***********************************************************************/
	    set_nand_pin_mux();

		#ifdef FOR_ICE_LOAD
		prints("Identify...\n");
		#endif

		if ((*do_identify)(&device) < 0)
		{
            #ifdef FOR_ICE_LOAD
            prints("error identify flash!!\n");
            #endif
			rtprintf("error identify flash!!\n");
			return -2;
		}

		#ifdef DUMP_NAND_FLASH
			prints("NF_dump_flash finish \n");
			NF_dump_flash(device, 0x03000000, 0, 0x1E00);
			//NF_dump_flash(device, 0x03000000, 0x500, 0x51e);
			prints("NF_dump_flash finish 2. and wait..\n");
                        while(1){
                                //wait ice connect and dump DDR
                        }
			return -2;
		#endif

		// determine number of backup according to flash type...
		switch (((n_device_type *)device)->ecc_bit)
		{
			case ECC_24BIT:
				backup_number = 3;	// total (2+1) hwsetting/bootcode/rescue
				break;
			case ECC_12BIT:
				backup_number = 3;	// total (4+1) hwsetting/bootcode/rescue
				break;
			case ECC_6BIT:
			default:
				backup_number = 3;	// total (7+1) hwsetting/bootcode/rescue
				break;
		}


		// init (setup block state table and erase old bootcode blocks)
		#ifdef FOR_ICE_LOAD
		prints("Init...\n");
		#endif
		if (do_init(device))
		{
            #ifdef FOR_ICE_LOAD
            prints("do_init_n falied\n");
            #endif
			rtprintf("do_init_n falied\n");
			return -2;
		}

		pagesize = ((n_device_type *)device)->PageSize;
		blocksize = ((n_device_type *)device)->BlockSize;

		g_BlockSize=blocksize;
		pagePerBlock = blocksize / pagesize;

	    /******************************
	     * copy parameters in flash to DDR
	     ******************************/
     	// reset memory
    	//for (idx = 0; idx < NAND_ENV_SIZE; idx+=4)
    	//	REG32(PARAMETER_TMP_ADDR + idx) = 0xffffffff;
     	set_memory((unsigned char *)PARAMETER_TMP_ADDR, 0xff, NAND_ENV_SIZE);
		res = get_env_n(device, (unsigned char *)PARAMETER_TMP_ADDR);
		save_nand_env = (res == 0 ? 1 : 0);

/*=============================for thor nand dvrmain start==============================================================*/
        /******************************
            * start to program bootcode_tw_table
        ******************************/
        if(blocksize == 0x20000){
            copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_fw_table_base_128KB, programmed_fw_bootarray_fw_table_nand_128KB_size);
            bootarray_fw_table_size = programmed_fw_bootarray_fw_table_nand_128KB_size;
        }else if(blocksize == 0x40000){
            copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_fw_table_base_256KB, programmed_fw_bootarray_fw_table_nand_256KB_size);
            bootarray_fw_table_size = programmed_fw_bootarray_fw_table_nand_256KB_size;
        }
        // align to page size boundary
        temp = (bootarray_fw_table_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + bootarray_fw_table_size), 0xff, pagesize - temp);
        }
        current_block = NF_BOOTCODE_START_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of bootcode_tw_table
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie Main bootcode_tw_table in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(bootarray_fw_table_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, bootarray_fw_table_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of bootcode_tw_table error!!\n");
        #endif
            rtprintf("main copy of bootcode_tw_table error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of bootcode_tw_table
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup bootcode_tw_table in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(bootarray_fw_table_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, bootarray_fw_table_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of bootcode_tw_table error!!\n");
                #endif
                    rtprintf("backup of bootcode_tw_table error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program SCS_area = NOCS Certificate + SCS_Params_Area
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, nocs_certificate, nocs_certificate_size);
        copy_memory((unsigned char *)DATA_TMP_ADDR+nocs_certificate_size, scs_params_area, scs_params_area_size);
        scs_area_size = nocs_certificate_size + scs_params_area_size;
        // align to page size boundary
        temp = (scs_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + scs_area_size), 0xff, pagesize - temp);
        }
        current_block = NF_SCS_AREA_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of SCS Area
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie SCS Area in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(scs_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, scs_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of SCS Area error!!\n");
        #endif
            rtprintf("main copy of SCS Area error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of SCS Area
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup SCS Area in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(scs_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, scs_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of SCS Area error!!\n");
                #endif
                    rtprintf("backup of SCS Area error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }
        /******************************
            * start to program Auxcode_area
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, auxcode_area, auxcode_area_size);
        // align to page size boundary
        temp = (auxcode_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + auxcode_area_size), 0xff, pagesize - temp);
        }
        current_block = NF_AUXCODE_AREA_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of auxcode
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie auxcode in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(auxcode_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, auxcode_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of auxcode error!!\n");
        #endif
            rtprintf("main copy of auxcode error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of auxcode
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup auxcode in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(dte_bootcode_rtk_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, auxcode_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of auxcode error!!\n");
                #endif
                    rtprintf("backup of auxcode error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program dte_bootcode_area
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, dte_bootcode_area, dte_bootcode_area_size);

        // align to page size boundary
        temp = (dte_bootcode_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + dte_bootcode_area_size), 0xff, pagesize - temp);
        }
        current_block = NF_DTE_BOOTCODE_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of dte_bootcode_area
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie dte_bootcode in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(dte_bootcode_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of dte_bootcode_area error!!\n");
        #endif
            rtprintf("main copy of dte_bootcode_area error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of dte_bootcode_area
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup dte_bootcode in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(dte_bootcode_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of dte_bootcode_area error!!\n");
                #endif
                    rtprintf("backup of dte_bootcode_area error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program Cert_area = PCPU Certificate + ATF Cert + AFW Cert + DTE FW Cert
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, atf_certificate, atf_certificate_size);
        copy_memory((unsigned char *)DATA_TMP_ADDR+atf_certificate_size, pcpu_certificate, pcpu_certificate_size);
        copy_memory((unsigned char *)DATA_TMP_ADDR+atf_certificate_size+pcpu_certificate_size, afw_certificate, afw_certificate_size);
        copy_memory((unsigned char *)DATA_TMP_ADDR+atf_certificate_size+pcpu_certificate_size+afw_certificate_size, dte_fw_certificate, dte_fw_certificate_size);
        cert_area_size = pcpu_certificate_size + atf_certificate_size + afw_certificate_size + dte_fw_certificate_size;
        // align to page size boundary
        temp = (cert_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + cert_area_size), 0xff, pagesize - temp);
        }
        current_block = NF_CERT_AREA_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of cert_area
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie cert_area in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(cert_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, cert_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of cert_area error!!\n");
        #endif
            rtprintf("main copy of cert_area error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of cert_area
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup cert_area in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(cert_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, cert_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of cert_area error!!\n");
                #endif
                    rtprintf("backup of cert_area error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program rtk_params_area
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, rtk_params_area, rtk_params_area_size);

        // align to page size boundary
        temp = (rtk_params_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + rtk_params_area_size), 0xff, pagesize - temp);
        }
        current_block = NF_RTK_PARAMS_AREA_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of rtk_params_area
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie rtk_params_area in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(rtk_params_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, rtk_params_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of rtk_params_area error!!\n");
        #endif
            rtprintf("main copy of rtk_params_area error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of rtk_params_area
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup rtk_params_area in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(rtk_params_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, rtk_params_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of rtk_params_area error!!\n");
                #endif
                    rtprintf("backup of rtk_params_area error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program bl31
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_bl31_base, programmed_bl31_size);

        // align to page size boundary
        temp = (programmed_bl31_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + programmed_bl31_size), 0xff, pagesize - temp);
        }
        current_block = NF_BL31_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of bl31
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie bl31 in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(programmed_bl31_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_bl31_size, BL31_MAGIC_NUM, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of bl31 error!!\n");
        #endif
            rtprintf("main copy of bl31 error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of bl31
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup bl31 in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(programmed_bl31_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_bl31_size, BL31_MAGIC_NUM, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of bl31 error!!\n");
                #endif
                    rtprintf("backup of bl31 error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program tee_os
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_secure_os_base, programmed_secure_os_size);

        // align to page size boundary
        temp = (programmed_secure_os_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + programmed_secure_os_size), 0xff, pagesize - temp);
        }
        current_block = NF_TEEOS_BLOCK;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of secure_os
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie secure_os in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(programmed_secure_os_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_secure_os_size, SECURE_OS_MAGIC_NUM, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of secure_os error!!\n");
        #endif
            rtprintf("main copy of secure_os error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of secure_os
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup secure_os in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(programmed_secure_os_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_secure_os_size, SECURE_OS_MAGIC_NUM, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of secure_os error!!\n");
                #endif
                    rtprintf("backup of secure_os error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

        /******************************
            * start to program dte_bootcode_rtk
        ******************************/
        copy_memory((unsigned char *)DATA_TMP_ADDR, dte_bootcode_rtk_area, dte_bootcode_rtk_area_size);

        // align to page size boundary
        temp = (dte_bootcode_rtk_area_size) % pagesize;
        if (temp) {
                set_memory((unsigned char *)(DATA_TMP_ADDR + dte_bootcode_rtk_area_size), 0xff, pagesize - temp);
        }
        current_block=NF_TEEOS_BLOCK + TEE_OS_BLOCK_CNT;

        temp = (BOOTCODE_MAX_SIZE) / blocksize;
        supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

        // main copy of bootcode
        #ifdef FOR_ICE_LOAD
            prints("\n");
            prints("Wrtie dte_bootcode_rtk_area in Block No. 0x");
            print_hex(current_block);
            prints(", Size: 0x");
            print_hex(dte_bootcode_rtk_area_size);
            prints(", Tag: 0x");
            print_hex(BLOCK_BOOTCODE);
            prints("\n");
        #endif

        end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_rtk_area_size, BLOCK_BOOTCODE, 0);

        if (end_page == -1) {
        #ifdef FOR_ICE_LOAD
            prints("main copy of dte_bootcode_rtk error!!\n");
        #endif
            rtprintf("main copy of dte_bootcode_rtk error!!\n");
            return -103;
        }
        current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;

        // backup copy of dte_bootcode_rtk
        for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
        {
                #ifdef FOR_ICE_LOAD
                prints("\n");
                prints("Wrtie Backup dte_bootcode_rtk_area in Block No. 0x");
                print_hex(current_block);
                prints(", Size: 0x");
                print_hex(dte_bootcode_rtk_area_size);
                prints(", Tag: 0x");
                print_hex(BLOCK_BOOTCODE);
                prints("\n");
                #endif

                end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_rtk_area_size, BLOCK_BOOTCODE, 0);

                if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                    prints("backup of dte_bootcode_rtk error!!\n");
                #endif
                    rtprintf("backup of dte_bootcode_rtk error!!\n");
                    return -104;
                }
                current_block = current_block + NF_BOOTCODE_BLOCK_AMOUNT;
            }

/*===================================thor nand dvrmain end====================================================================*/
#if 0
	     /******************************
	     * start to program bootcode
	     ******************************/
    	copy_memory((unsigned char *)DATA_TMP_ADDR, dte_bootcode_rtk_area, dte_bootcode_rtk_area_size);

		// align to page size boundary
    	temp = (dte_bootcode_rtk_area_size) % pagesize;
    	if (temp) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + dte_bootcode_rtk_area_size), 0xff, pagesize - temp);
    	}

        // at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
        //temp = (programmed_img_size+programmed_img_sig_size) / blocksize + ((programmed_img_size+programmed_img_sig_size) % blocksize ? 1 : 0);
        temp = (BOOTCODE_MAX_SIZE) / blocksize;
    	supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

    	// main copy of bootcode
    	#ifdef FOR_ICE_LOAD
		prints("\n");
		prints("Wrtie Main Bootcode in Block No. 0x");
		print_hex(current_block);
		prints(", Size: 0x");
		print_hex(dte_bootcode_rtk_area_size);
		prints(", Tag: 0x");
		print_hex(BLOCK_BOOTCODE);
		prints("\n");
		#endif

		end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_rtk_area_size, BLOCK_BOOTCODE, 0);

    	if (end_page == -1) {
            #ifdef FOR_ICE_LOAD
            prints("main copy of bootcode error!!\n");
            #endif
    		rtprintf("main copy of bootcode error!!\n");
    		return -103;
    	}
    	// calculate next block start page
		//current_block = (end_page / pages_per_block) + 1;
		current_block = current_block + (BOOTCODE_MAX_SIZE / blocksize);

		// backup copy of bootcode
		for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
		{
    	    // cannot write beyond supposed blocks
            if (current_block > supposed_block) {
                #ifdef FOR_ICE_LOAD
                prints("bootcode full\n");
                #endif
            	rtprintf("bootcode full");
            	break;
            }

			#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Backup Bootcode in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(dte_bootcode_rtk_area_size);
			prints(", Tag: 0x");
			print_hex(BLOCK_BOOTCODE);
			prints("\n");
			#endif

		    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, dte_bootcode_rtk_area_size, BLOCK_BOOTCODE, 0);

		    if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                prints("backup of bootcode error!!\n");
                #endif
		    	rtprintf("backup of bootcode error!!\n");
		    	return -104;
		    }

			// calculate next block start page
			//current_block = (end_page / pages_per_block) + 1;
			current_block = current_block + (BOOTCODE_MAX_SIZE / blocksize);
		}

#ifdef DUMP_NAND_FLASH
		//NF_dump_flash(device, gdst_data_addr, 0x1c0, 0x40);
#endif

		param.data_start_blk = current_block;

		/******************************
	       * start to program SECURE OS
	       ******************************/
	    if(programmed_secure_os_size > 0) {
            unsigned int fsbl_blk=0,program_len=0;

            //1. copy secure_os+secure_os_sig to buffer
            program_len = programmed_secure_os_size;
            copy_memory(DATA_TMP_ADDR, programmed_secure_os_base, programmed_secure_os_size);

			// align to page size boundary
	    	temp = program_len % pagesize;
	    	if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
	    	}

			// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
	        //temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
            temp = SECURE_OS_MAX_SIZE / blocksize;
	    	supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

			// main copy of bootcode
	    	#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Main TEE OS in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(program_len);
			prints(", Tag: 0x");
			print_hex(SECURE_OS_MAGIC_NUM);
			prints("\n");
			#endif

	    	end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, SECURE_OS_MAGIC_NUM, 0);

	    	if (end_page == -1) {
	            #ifdef FOR_ICE_LOAD
	            prints("main copy of secure os error!!\n");
	            #endif
	    		rtprintf("main copy of secure os error!!\n");
	    		return -103;
	    	}

			// calculate next block start page
			//current_block = (end_page / pages_per_block) + 1;
			current_block = current_block + (SECURE_OS_MAX_SIZE / blocksize);

			// backup copy of bootcode
			for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
			{
	    	    // cannot write beyond supposed blocks
	            if (current_block > supposed_block) {
	                #ifdef FOR_ICE_LOAD
	                prints("secure os full\n");
	                #endif
	            	rtprintf("secure os full");
	            	break;
	            }

				#ifdef FOR_ICE_LOAD
				prints("\n");
				prints("Wrtie Backup TEE OS in Block No. 0x");
				print_hex(current_block);
				prints(", Size: 0x");
				print_hex(program_len);
				prints(", Tag: 0x");
				print_hex(SECURE_OS_MAGIC_NUM);
				prints("\n");
				#endif

				end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, SECURE_OS_MAGIC_NUM, 0);

			    if (end_page == -1) {
	                #ifdef FOR_ICE_LOAD
	                prints("backup of secure os error!!\n");
	                #endif
			    	rtprintf("backup of secure os error!!\n");
			    	return -104;
			    }
			    // calculate next block start page
			    //current_block = (end_page / pages_per_block) + 1;
                current_block = current_block + (SECURE_OS_MAX_SIZE / blocksize);
			}

		}


        /******************************
	       * start to program BL31
	       ******************************/
	    if(programmed_bl31_size > 0 ) {
            unsigned int bl31_blk=0,program_len=0;

            //1. copy bl31+bl31_sig to buffer
            program_len = programmed_bl31_size;
            copy_memory(DATA_TMP_ADDR, programmed_bl31_base, programmed_bl31_size);

			// align to page size boundary
	    	temp = program_len % pagesize;
	    	if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
	    	}

			// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
	        temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
	    	supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

			// main copy of bootcode
			#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Main BL31 in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(program_len);
			prints(", Tag: 0x");
			print_hex(BL31_MAGIC_NUM);
			prints("\n");
			#endif

	    	end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, BL31_MAGIC_NUM, 0);

	    	if (end_page == -1) {
	            #ifdef FOR_ICE_LOAD
	            prints("main copy of secure os error!!\n");
	            #endif
	    		rtprintf("main copy of secure os error!!\n");
	    		return -103;
	    	}

	    	// calculate next block start page
	    	current_block = (end_page / pages_per_block) + 1;

			// backup copy of bootcode
			for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
			{
	    	    // cannot write beyond supposed blocks
	            if (current_block > supposed_block) {
	                #ifdef FOR_ICE_LOAD
	                prints("bl31 full\n");
	                #endif
	            	rtprintf("bl31 full");
	            	break;
	            }

				#ifdef FOR_ICE_LOAD
				prints("\n");
				prints("Wrtie Backup BL31 in Block No. 0x");
				print_hex(current_block);
				prints(", Size: 0x");
				print_hex(program_len);
				prints(", Tag: 0x");
				print_hex(BL31_MAGIC_NUM);
				prints("\n");
				#endif

				end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, BL31_MAGIC_NUM, 0);

			    if (end_page == -1) {
	                #ifdef FOR_ICE_LOAD
	                prints("backup of bl31 error!!\n");
	                #endif
			    	rtprintf("backup of bl31 error!!\n");
			    	return -104;
			    }
			    // calculate next block start page
			    current_block = (end_page / pages_per_block) + 1;
			}

		}

		param.data_start_blk = current_block;


	    /***********************************************************************
	     * copy each data section to DDR for copy all to flash
	     ***********************************************************************/
		// copy ext_param structure data to DDR
		for (idx = 0; idx < sizeof(param); idx+=4) {
			REG32((unsigned int)(buf_start + idx)) = REG32((unsigned int)(((unsigned char *)&param) + idx));
		}
		// shift data pointer of DDR
		buf_start +=idx;
		data_lentgh = buf_start - DATA_TMP_ADDR;

		// align to page size boundary
		temp = data_lentgh % pagesize;
		if (temp) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + data_lentgh), 0xff, pagesize - temp);
		}

	    /***********************************************************************
	     * start to program data(rescue and logo1,2,..)
	     ***********************************************************************/
		// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
		temp = data_lentgh / blocksize + (data_lentgh % blocksize ? 1 : 0);
	    supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

		// main copy of data
		#ifdef FOR_ICE_LOAD
		prints("\n");
		prints("Wrtie Main Data in Block No. 0x");
		print_hex(current_block);
		prints(", Size: 0x");
		print_hex(data_lentgh);
		prints(", Tag: 0x");
		print_hex(BLOCK_DATA);
		prints("\n");
		#endif
	    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, data_lentgh, BLOCK_DATA, 0);

	    if (end_page == -1) {
            #ifdef FOR_ICE_LOAD
            prints("main copy of rescue+logo error!!\n");
            #endif
	    	rtprintf("main copy of rescue+logo error!!\n");
	    	return -105;
	    }
	    // calculate next block start page
	    current_block = (end_page / pages_per_block) + 1;

		// backup copy of data
		for (i = 0; i < backup_number; i++) {
    	    // cannot write beyond supposed blocks
            if (current_block > supposed_block)
            {
                #ifdef FOR_ICE_LOAD
                prints("rescue+logo full\n");
                #endif
            	rtprintf("rescue+logo full");
            	break;
            }

			#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Backup Data in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(data_lentgh);
			prints(", Tag: 0x");
			print_hex(BLOCK_DATA);
			prints("\n");
			#endif

		    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, data_lentgh, BLOCK_DATA, 0);

		    if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                prints("backup copy of rescue+logo error!!\n");
                #endif
		    	rtprintf("backup copy of rescue+logo error!!\n");
		    	return -106;
		    }
		    // calculate next block start page
		    current_block = (end_page / pages_per_block) + 1;
		}
#endif

	    /******************************
	     * copy parameters in DDR to flash
	     ******************************/
	     if( save_nand_env ) {
                    rtprintf("save env");
	     	res = save_env_n(device, (unsigned char *)PARAMETER_TMP_ADDR);
	     	 if (res) {
                #ifdef FOR_ICE_LOAD
                prints("save env failed\n");
                #endif
	     	 	rtprintf("save env failed");
	     	}
	     }

 		prints("\nExit...\n");
	    /* Reset Command */
	    (*do_exit)(device);

		#ifdef DUMP_NAND_FLASH
			//NF_dump_flash(device, 0x03000000, 0, 0x197F);
			//NF_dump_flash(device, 0x03000000, 0, 0x177F);
			//NF_dump_flash(device, 0x03000000, 0, 0xa1e);
		#endif
	}
	else if ( flash_magicno == FLASH_MAGICNO_NOR_SERIAL)
	{
	    /***********************************************************************
	     * copy parameters in flash to DDR
	     ***********************************************************************/
	    for (idx = 0; idx < SPI_MAX_PARAM_SIZE; idx +=4) {
			rtd_outl( (PARAMETER_TMP_ADDR + idx) ,rtd_inl((unsigned int)(SPI_ENV_PARAM_ADDR + idx))); //copy to ddr : 0x02400000 , len: 0x10000
		}

	    /***********************************************************************
	     * set pin mux
	     ***********************************************************************/
	    set_spi_pin_mux();
	    if ((*do_identify)(&device) < 0) {
	    	rtprintf("error identify flash!!\n");
            #ifdef FOR_ICE_LOAD
            prints("error identify flash!!\n");
            #endif
	    	return -2;
	    }
	    #ifdef FOR_ICE_LOAD
        prints("init\n");
        #endif

	    (*do_init)(device);

		//erase first 832KB or 1MB for bootcode fw size
		#ifdef FOR_ICE_LOAD
        prints("spi : erase 0x");
        print_hex(MAX_BOOTCODE_FW_SIZE);
        prints(" bytes from 0x");
        print_hex(SPI_CODE_PART1_1);
        prints("\n");
        #endif
        rtprintf("spi : erase 0x%x bytes from 0x%08x\n", MAX_BOOTCODE_FW_SIZE, SPI_CODE_PART1_1);
        if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART1_1, MAX_BOOTCODE_FW_SIZE) !=0 ) {
            return -3;
        }

#if 0 // dump flash
		spi_switch_read_mode();
		spi_hexdump("spi data", SPI_CODE_PART1, 512);
#endif

#ifdef ROMCODE_ON_SPI
		//scpu
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write scpu romcode, start=0x");
        print_hex(spi_scpu_resetrom_addr);
        prints(", len=0x");
        print_hex(scpu_resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write scpu romcode, start=0x%08x, len=0x%08x\n", spi_scpu_resetrom_addr, scpu_resetrom_size);
	    if ((*do_write)(device, scpu_resetrom, (unsigned int *)spi_scpu_resetrom_addr, scpu_resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
		//pcpu
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write pcpu romcode, start=0x");
        print_hex(spi_pcpu_resetrom_addr);
        prints(", len=0x");
        print_hex(pcpu_resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write pcpu romcode, start=0x%08x, len=0x%08x\n", spi_pcpu_resetrom_addr, pcpu_resetrom_size);
	    if ((*do_write)(device, pcpu_resetrom, (unsigned int *)spi_pcpu_resetrom_addr, pcpu_resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
		//acpu
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write acpu romcode, start=0x");
        print_hex(spi_acpu_resetrom_addr);
        prints(", len=0x");
        print_hex(acpu_resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write acpu romcode, start=0x%08x, len=0x%08x\n", spi_acpu_resetrom_addr, acpu_resetrom_size);
	    if ((*do_write)(device, acpu_resetrom, (unsigned int *)spi_acpu_resetrom_addr, acpu_resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
	#ifdef ROMCODE_ON_SPI_ONLY
	goto finish;
	#endif
#endif // ROMCODE_ON_SPI

		//for secure / non-secure
		//bootarray_fw_table
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write bootarray_fw_table&signature, start=0x");
        print_hex(spi_bootarray_fw_table_addr);
        prints(", len=0x");
        print_hex(bootarray_fw_table_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write bootarray_fw_table&signature, start=0x%08x, len=0x%08x\n", spi_bootarray_fw_table_addr, bootarray_fw_table_size);
	    if ((*do_write)(device, spi_bootarray_fw_table, (unsigned int *)spi_bootarray_fw_table_addr, bootarray_fw_table_size, 0, 0)!= 0 ) {
	        return -5;
	    }

		//nocs_certificate
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write nocs_certificate, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(nocs_certificate_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write nocs_certificate, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, nocs_certificate_size);
	    if ((*do_write)(device, nocs_certificate, (unsigned int *)spi_next_fw_start_addr, nocs_certificate_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += nocs_certificate_size;

		//atf_certificate
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write atf_certificate, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(atf_certificate_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write atf_certificate, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, atf_certificate_size);
	    if ((*do_write)(device, atf_certificate, (unsigned int *)spi_next_fw_start_addr, atf_certificate_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += atf_certificate_size;

		//pcpu_certificate
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write pcpu_certificate, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(pcpu_certificate_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write pcpu_certificate, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, pcpu_certificate_size);
	    if ((*do_write)(device, pcpu_certificate, (unsigned int *)spi_next_fw_start_addr, pcpu_certificate_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += pcpu_certificate_size;

		//dte_fw_certificate
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write dte_fw_certificate, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(dte_fw_certificate_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write dte_fw_certificate, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, dte_fw_certificate_size);
	    if ((*do_write)(device, dte_fw_certificate, (unsigned int *)spi_next_fw_start_addr, dte_fw_certificate_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += dte_fw_certificate_size;

		//afw_certificate
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write afw_certificate, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(afw_certificate_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write afw_certificate, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, afw_certificate_size);
	    if ((*do_write)(device, afw_certificate, (unsigned int *)spi_next_fw_start_addr, afw_certificate_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += afw_certificate_size;

		//scs_params_area
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write scs_params_area, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(scs_params_area_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write scs_params_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, scs_params_area_size);
	    if ((*do_write)(device, scs_params_area, (unsigned int *)spi_next_fw_start_addr, scs_params_area_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += scs_params_area_size;

		//rtk_params_area
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write rtk_params_area, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(rtk_params_area_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write rtk_params_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, rtk_params_area_size);
	    if ((*do_write)(device, rtk_params_area, (unsigned int *)spi_next_fw_start_addr, rtk_params_area_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += rtk_params_area_size;

		//auxcode_area
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write auxcode_area, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(auxcode_area_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write auxcode_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, auxcode_area_size);
	    if ((*do_write)(device, auxcode_area, (unsigned int *)spi_next_fw_start_addr, auxcode_area_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += auxcode_area_size;


		//dte_bootcode_area
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write dte_bootcode_area, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(dte_bootcode_area_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write dte_bootcode_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, dte_bootcode_area_size);
	    if ((*do_write)(device, dte_bootcode_area, (unsigned int *)spi_next_fw_start_addr, dte_bootcode_area_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		spi_next_fw_start_addr += dte_bootcode_area_size;

		//pcpu code area
	    if (programmed_pcpu_code_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write pcpu_code_area, start=0x");
            print_hex(spi_next_fw_start_addr);
            prints(", len=0x");
            print_hex(programmed_pcpu_code_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write pcpu_code_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, programmed_pcpu_code_size);
	    	if ((*do_write)(device, programmed_pcpu_code_base, (unsigned int *)spi_next_fw_start_addr, programmed_pcpu_code_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
		spi_next_fw_start_addr += programmed_pcpu_code_size;

#if defined(Config_BL31_TRUE)
		//bl31
		if (programmed_bl31_size > 0)
		{
#ifdef FOR_ICE_LOAD
			prints("\nspi : write bl31_area, start=0x");
			print_hex(spi_next_fw_start_addr);
			prints(", len=0x");
			print_hex(programmed_bl31_size);
			prints("\n");
#endif
			rtprintf("\nspi : write bl31_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, programmed_bl31_size);
			if ((*do_write)(device, programmed_bl31_base, (unsigned int *)spi_next_fw_start_addr, programmed_bl31_size, 0, 0)!= 0 ) {
				return -6;
			}
		}
		spi_next_fw_start_addr += programmed_bl31_size;

#endif


#if defined(Config_SECURE_OS_TRUE)
        //fsbl os
	    if (programmed_secure_os_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write secure_os_area, start=0x");
            print_hex(spi_next_fw_start_addr);
            prints(", len=0x");
            print_hex(programmed_secure_os_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write secure_os_area, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, programmed_secure_os_size);
	    	if ((*do_write)(device, programmed_secure_os_base, (unsigned int *)spi_next_fw_start_addr, programmed_secure_os_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
		spi_next_fw_start_addr += programmed_secure_os_size;

#endif

		//dte_bootcode_rtk
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write dte_bootcode_rtk&signature, start=0x");
        print_hex(spi_next_fw_start_addr);
        prints(", len=0x");
        print_hex(dte_bootcode_rtk_area_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write dte_bootcode_rtk&signature, start=0x%08x, len=0x%08x\n", spi_next_fw_start_addr, dte_bootcode_rtk_area_size);
	    if ((*do_write)(device, dte_bootcode_rtk_area, (unsigned int *)spi_next_fw_start_addr, dte_bootcode_rtk_area_size, 0, 0)!= 0 ) {
	        return -6;
	    }

		/************* parameter is  fixed spi address *******************/

	    // write parameter in bootcode
	    #ifdef FOR_ICE_LOAD
        prints("\nspi : write parameter, start=0x");
        print_hex(spi_param_addr);
        prints(", len=0x");
        print_hex(sizeof(t_extern_param));
        prints("\n");
        #endif
	    rtprintf("\nspi : write parameter, start=0x%08x, len=0x%08x\n", spi_param_addr, sizeof(t_extern_param));
	    if ((*do_write)(device, (unsigned char *)&param, (unsigned int *)spi_param_addr, sizeof(t_extern_param), 0, 0)!= 0 ) {
	        return -14;
	    }

#if 0 // dump flash
		spi_switch_read_mode();
		spi_hexdump("spi data", spi_param_addr, 64);
		spi_hexdump("spi data", spi_bootcode_addr2, 64);
		spi_hexdump("spi data", spi_bootcode_addr3, 64);
#endif

	    #ifdef FOR_ICE_LOAD
        prints("exit\n");
        #endif
	    /* Reset Command */
	    (*do_exit)(device);

	}
	else if ( flash_magicno == FLASH_MAGICNO_EMMC)
	{
		unsigned char * read_buf;
		unsigned int uda_block_no;
		unsigned int backup_uda_block_no;
        unsigned int boot_block_no;
		unsigned int buf_start;
		unsigned int data_length;
		unsigned int boot_part_dest_block=0;

		block_size = EMMC_BLOCK_SIZE;
		data_length = 0;

		t_BootPart_obj BootPartOps;
		InitBootPartitionOpes(flash_type,&BootPartOps);

		/***********************************************************************
		 * set pin mux
		 ***********************************************************************/
#ifndef FPGA
		set_emmc_pin_mux();
		//set_emmc_freq();
#endif
		if ((*do_identify)(&device) < 0) {
            #ifdef FOR_ICE_LOAD
			prints("error identify flash!!\n");
            #endif
			rtprintf("error identify flash!!\n");
			return -2;
		}

		if ((*do_init)(device)) {
            #ifdef FOR_ICE_LOAD
			prints("do_init falied\n");
            #endif
			rtprintf("do_init falied\n");
			return -2;
		}

		read_buf = REF_MALLOC_BASE;
		rtprintf("set read_buf = 0x%08x\n", (unsigned int)read_buf);

        #ifdef FOR_ICE_LOAD
		prints("*******************************************\n");
        #endif
    	rtprintf("*******************************************\n");

		/***********************************************************************
		 * start to program bootarray fw table
		 ***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, eMMC_bootarray_fw_table, bootarray_fw_table_size);
		uda_block_no = EMMC_BOOTARRAY_FW_TABLE_BLK;

        #ifdef FOR_ICE_LOAD
		prints("bootarray_fw_table: UDA block 0x");
        print_hex(uda_block_no);
		prints(", size 0x");
        print_hex(bootarray_fw_table_size);
        prints("\n");
        #endif
		rtprintf("bootarray_fw_table: UDA block 0x%x, size 0x%x\n", uda_block_no, bootarray_fw_table_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, bootarray_fw_table_size, 0, MMC_PART_UDA)) {
            #ifdef FOR_ICE_LOAD
    		prints("do_write falied\n");
            #endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
    		prints("read bootarray_fw_table back: UDA block 0x");
            print_hex(uda_block_no);
    		prints(", size 0x");
            print_hex(bootarray_fw_table_size);
            prints("\n");
#endif
			rtprintf("read bootarray_fw_table back: UDA block 0x%x, size 0x%x\n", uda_block_no, bootarray_fw_table_size);
			if ((*do_read)(device, &uda_block_no, read_buf, bootarray_fw_table_size, MMC_PART_UDA)) {
                #ifdef FOR_ICE_LOAD
        		prints("do_read check falied\n");
                #endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, bootarray_fw_table_size)) {
                #ifdef FOR_ICE_LOAD
        		prints("verify bootarray_fw_table falied\n");
                #endif
				rtprintf("verify bootarray_fw_table falied\n");
				return -6;
			}
		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, bootarray_fw_table_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(bootarray_fw_table_size, EMMC_BLOCK_SIZE);  //for uda


		/***********************************************************************
		 * start to program NOCS Certificate
		 ***********************************************************************/
		boot_block_no = 0;
		copy_memory((unsigned char *)DATA_TMP_ADDR, nocs_certificate, nocs_certificate_size);
		for (i = 0; i <= 1; i++){
#ifdef FOR_ICE_LOAD
			if (i == 0)
				prints("NOCS Certificate: boot1 block 0x");
			else
				prints("NOCS Certificate: boot2 block 0x");
	        print_hex(boot_block_no);
			prints(", size 0x");
	        print_hex(nocs_certificate_size);
	        prints("\n");
#endif
			rtprintf("NOCS Certificate: boot block 0x%x, size 0x%x\n", boot_block_no, nocs_certificate_size);

			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &boot_block_no, nocs_certificate_size, 0, MMC_PART_BOOT_1+i)) {
	            #ifdef FOR_ICE_LOAD
	    		prints("do_write falied\n");
	            #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
#ifdef FOR_ICE_LOAD
				if (i == 0)
	    			prints("read NOCS Certificate back: boot1 block 0x");
				else
					prints("read NOCS Certificate back: boot2 block 0x");
	            print_hex(boot_block_no);
	    		prints(", size 0x");
	            print_hex(nocs_certificate_size);
	            prints("\n");
#endif
				rtprintf("read NOCS Certificate back: boot block 0x%x, size 0x%x\n", boot_block_no, nocs_certificate_size);
				if ((*do_read)(device, &boot_block_no, read_buf, nocs_certificate_size, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
	        		prints("do_read check falied\n");
#endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, nocs_certificate_size)) {
	                #ifdef FOR_ICE_LOAD
	        		prints("verify NOCS Certificate falied\n");
	                #endif
					rtprintf("verify NOCS Certificate falied\n");
					return -6;
				}
			}
		}


		boot_block_no += align_to_boundary(nocs_certificate_size, EMMC_BLOCK_SIZE);  //for boot partition


		/***********************************************************************
			 * start to program SCS_Params_Area
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, scs_params_area, scs_params_area_size);
		// clear copy_memory region to align emmc block size
		temp = scs_params_area_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + scs_params_area_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}
		for (i = 0; i <= 1; i++){
#ifdef FOR_ICE_LOAD
			if(i == 0)
				prints("SCS_Params_Area: boot1 block 0x");
			else
				prints("SCS_Params_Area: boot2 block 0x");
			print_hex(boot_block_no);
			prints(", size 0x");
			print_hex(scs_params_area_size);
			prints("\n");
#endif
			rtprintf("SCS_Params_Area: block 0x%x, size 0x%x\n", boot_block_no, scs_params_area_size);

			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &boot_block_no, scs_params_area_size, 0, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
				prints("do_write falied\n");
#endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
#ifdef FOR_ICE_LOAD
				if(i == 0)
					prints("read SCS_Params_Area back: boot1 block 0x");
				else
					prints("read SCS_Params_Area back: boot2 block 0x");
				print_hex(boot_block_no);
				prints(", size 0x");
				print_hex(scs_params_area_size);
				prints("\n");
#endif
				rtprintf("read SCS_Params_Area back: boot block 0x%x, size 0x%x\n", boot_block_no, scs_params_area_size);
				if ((*do_read)(device, &boot_block_no, read_buf, scs_params_area_size, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
					prints("do_read check falied\n");
#endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, scs_params_area_size)) {
#ifdef FOR_ICE_LOAD
					prints("verify SCS_Params_Area falied\n");
#endif
					rtprintf("verify SCS_Params_Area falied\n");
					return -6;
				}
			}
		}
		boot_block_no += align_to_boundary(scs_params_area_size, EMMC_BLOCK_SIZE);  //for boot partition

		/***********************************************************************
		 * start to program Auxcode_Area
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, auxcode_area, auxcode_area_size);
		// clear copy_memory region to align emmc block size
		temp = auxcode_area_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + auxcode_area_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}
		for (i = 0; i<=1; i++){
#ifdef FOR_ICE_LOAD
			if (i == 0)
				prints("Auxcode_Area: boot1 block 0x");
			else
				prints("Auxcode_Area: boot2 block 0x");
			print_hex(boot_block_no);
			prints(", size 0x");
			print_hex(auxcode_area_size);
			prints("\n");
#endif
			rtprintf("Auxcode_Area: block 0x%x, size 0x%x\n", boot_block_no, auxcode_area_size);

			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &boot_block_no, auxcode_area_size, 0, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
				prints("do_write falied\n");
#endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
#ifdef FOR_ICE_LOAD
				if(i == 0)
					prints("read Auxcode_Area back: boot1 block 0x");
				else
					prints("read Auxcode_Area back: boot2 block 0x");
				print_hex(boot_block_no);
				prints(", size 0x");
				print_hex(auxcode_area_size);
				prints("\n");
#endif
				rtprintf("read Auxcode_Area back: boot block 0x%x, size 0x%x\n", boot_block_no, auxcode_area_size);
				if ((*do_read)(device, &boot_block_no, read_buf, auxcode_area_size, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
					prints("do_read check falied\n");
#endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, auxcode_area_size)) {
#ifdef FOR_ICE_LOAD
					prints("verify Auxcode_Area falied\n");
#endif
					rtprintf("verify Auxcode_Area falied\n");
					return -6;
				}

			}
		}
		boot_block_no += align_to_boundary(auxcode_area_size, EMMC_BLOCK_SIZE);  //for boot partition

		/***********************************************************************
		 * start to program DTE_Bootcode_Area
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, dte_bootcode_area, dte_bootcode_area_size);
		// clear copy_memory region to align emmc block size
		temp = dte_bootcode_area_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + dte_bootcode_area_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}
		for (i = 0; i<=1; i++){
#ifdef FOR_ICE_LOAD
			if (i == 0)
				prints("DTE_Bootcode_Area: boot1 block 0x");
			else
				prints("DTE_Bootcode_Area: boot2 block 0x");
			print_hex(boot_block_no);
			prints(", size 0x");
			print_hex(dte_bootcode_area_size);
			prints("\n");
#endif
			rtprintf("DTE_Bootcode_Area: boot block 0x%x, size 0x%x\n", boot_block_no, dte_bootcode_area_size);

			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &boot_block_no, dte_bootcode_area_size, 0, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
				prints("do_write falied\n");
#endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
#ifdef FOR_ICE_LOAD
				if (i == 0)
					prints("read DTE_Bootcode_Area back: boot1 block 0x");
				else
					prints("read DTE_Bootcode_Area back: boot2 block 0x");
				print_hex(boot_block_no);
				prints(", size 0x");
				print_hex(dte_bootcode_area_size);
				prints("\n");
#endif
				rtprintf("read DTE_Bootcode_Area back: block 0x%x, size 0x%x\n", boot_block_no, dte_bootcode_area_size);
				if ((*do_read)(device, &boot_block_no, read_buf, dte_bootcode_area_size, MMC_PART_BOOT_1+i)) {
#ifdef FOR_ICE_LOAD
					prints("do_read check falied\n");
#endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, dte_bootcode_area_size)) {
#ifdef FOR_ICE_LOAD
					prints("verify DTE_Bootcode_Area falied\n");
#endif
					rtprintf("verify DTE_Bootcode_Area falied\n");
					return -6;
				}
			}
		}
		boot_block_no += align_to_boundary(dte_bootcode_area_size, EMMC_BLOCK_SIZE);  //for uda

		/***********************************************************************
		 * start to program ATF Certificate
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, atf_certificate, atf_certificate_size);
#ifdef FOR_ICE_LOAD
		prints("ATF Certificate: uda block 0x");
		print_hex(uda_block_no);
		prints(", size 0x");
		print_hex(atf_certificate_size);
		prints("\n");
#endif
		rtprintf("ATF Certificate: uda block 0x%x, size 0x%x\n", uda_block_no, atf_certificate_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, atf_certificate_size, 0, MMC_PART_UDA)) {
    #ifdef FOR_ICE_LOAD
			prints("do_write falied\n");
    #endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
			prints("read ATF Certificate back: uda block 0x");
			print_hex(uda_block_no);
			prints(", size 0x");
			print_hex(atf_certificate_size);
			prints("\n");
#endif
			rtprintf("read ATF Certificate back: uda block 0x%x, size 0x%x\n", uda_block_no, atf_certificate_size);
			if ((*do_read)(device, &uda_block_no, read_buf, atf_certificate_size, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
				prints("do_read check falied\n");
#endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, atf_certificate_size)) {
        #ifdef FOR_ICE_LOAD
				prints("verify ATF Certificate falied\n");
        #endif
				rtprintf("verify ATF Certificate falied\n");
				return -6;
			}

		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, atf_certificate_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(atf_certificate_size, EMMC_BLOCK_SIZE);  //for uda


		/***********************************************************************
		 * start to program PCPU Certificate
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, pcpu_certificate, pcpu_certificate_size);
#ifdef FOR_ICE_LOAD
		prints("PCPU Certificate: uda block 0x");
		print_hex(uda_block_no);
		prints(", size 0x");
		print_hex(pcpu_certificate_size);
		prints("\n");
#endif
		rtprintf("PCPU Certificate: uda block 0x%x, size 0x%x\n", uda_block_no, pcpu_certificate_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, pcpu_certificate_size, 0, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
			prints("do_write falied\n");
#endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
			prints("read PCPU Certificate back: uda block 0x");
			print_hex(uda_block_no);
			prints(", size 0x");
			print_hex(pcpu_certificate_size);
			prints("\n");
#endif
			rtprintf("read PCPU Certificate back: uda block 0x%x, size 0x%x\n", uda_block_no, pcpu_certificate_size);
			if ((*do_read)(device, &uda_block_no, read_buf, pcpu_certificate_size, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
				prints("do_read check falied\n");
#endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, pcpu_certificate_size)) {
#ifdef FOR_ICE_LOAD
				prints("verify PCPU Certificate falied\n");
#endif
				rtprintf("verify PCPU Certificate falied\n");
				return -6;
			}
		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, pcpu_certificate_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(pcpu_certificate_size, EMMC_BLOCK_SIZE);  //for uda


		/***********************************************************************
		 * start to program DTE FW_Certificate
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, dte_fw_certificate, dte_fw_certificate_size);
#ifdef FOR_ICE_LOAD
		prints("DTE_FW Certificate: uda block 0x");
		print_hex(uda_block_no);
		prints(", size 0x");
		print_hex(dte_fw_certificate_size);
		prints("\n");
#endif
		rtprintf("DTE_FW Certificate: uda block 0x%x, size 0x%x\n", uda_block_no, dte_fw_certificate_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, dte_fw_certificate_size, 0, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
			prints("do_write falied\n");
#endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
			prints("read DTE_FW Certificate back: uda block 0x");
			print_hex(uda_block_no);
			prints(", size 0x");
			print_hex(dte_fw_certificate_size);
			prints("\n");
#endif
			rtprintf("read DTE_FW Certificate back: uda block 0x%x, size 0x%x\n", uda_block_no, dte_fw_certificate_size);
			if ((*do_read)(device, &uda_block_no, read_buf, dte_fw_certificate_size, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
				prints("do_read check falied\n");
#endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, dte_fw_certificate_size)) {
#ifdef FOR_ICE_LOAD
				prints("verify DTE_FW Certificate falied\n");
#endif
				rtprintf("verify DTE_FW Certificate falied\n");
				return -6;
			}
		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, dte_fw_certificate_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(dte_fw_certificate_size, EMMC_BLOCK_SIZE);	//for uda

		/***********************************************************************
		 * start to program AFW_Certificate
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, afw_certificate, afw_certificate_size);
#ifdef FOR_ICE_LOAD
		prints("AFW Certificate: uda block 0x");
		print_hex(uda_block_no);
		prints(", size 0x");
		print_hex(afw_certificate_size);
		prints("\n");
#endif
		rtprintf("AFW Certificate: uda block 0x%x, size 0x%x\n", uda_block_no, afw_certificate_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, afw_certificate_size, 0, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
			prints("do_write falied\n");
#endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
			prints("read AFW Certificate back: uda block 0x");
			print_hex(uda_block_no);
			prints(", size 0x");
			print_hex(afw_certificate_size);
			prints("\n");
#endif
			rtprintf("read AFW Certificate back: uda block 0x%x, size 0x%x\n", uda_block_no, afw_certificate_size);
			if ((*do_read)(device, &uda_block_no, read_buf, afw_certificate_size, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
				prints("do_read check falied\n");
#endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, afw_certificate_size)) {
#ifdef FOR_ICE_LOAD
				prints("verify AFW Certificate falied\n");
#endif
				rtprintf("verify AFW Certificate falied\n");
				return -6;
			}
		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, afw_certificate_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(afw_certificate_size, EMMC_BLOCK_SIZE);	//for uda


		/***********************************************************************
		 * start to program RTK_Params_Area
		***********************************************************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, rtk_params_area, rtk_params_area_size);
		// clear copy_memory region to align emmc block size
		temp = rtk_params_area_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + rtk_params_area_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}
#ifdef FOR_ICE_LOAD
		prints("RTK_Params_Area: uda block 0x");
		print_hex(uda_block_no);
		prints(", size 0x");
		print_hex(rtk_params_area_size);
		prints("\n");
#endif
		rtprintf("RTK_Params_Area: uda block 0x%x, size 0x%x\n", uda_block_no, rtk_params_area_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, rtk_params_area_size, 0, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
			prints("do_write falied\n");
#endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
#ifdef FOR_ICE_LOAD
			prints("read RTK_Params_Area back: uda block 0x");
			print_hex(uda_block_no);
			prints(", size 0x");
			print_hex(rtk_params_area_size);
			prints("\n");
#endif
			rtprintf("read RTK_Params_Area back: uda block 0x%x, size 0x%x\n", uda_block_no, rtk_params_area_size);
			if ((*do_read)(device, &uda_block_no, read_buf, rtk_params_area_size, MMC_PART_UDA)) {
#ifdef FOR_ICE_LOAD
				prints("do_read check falied\n");
#endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, rtk_params_area_size)) {
#ifdef FOR_ICE_LOAD
				prints("verify RTK_Params_Area falied\n");
#endif
				rtprintf("verify RTK_Params_Area falied\n");
				return -6;
			}

		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, rtk_params_area_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(rtk_params_area_size, EMMC_BLOCK_SIZE);  //for uda

		
		/***********************************************************************
		* start to program PCPU Code Area
		***********************************************************************/
		if(programmed_pcpu_code_size != 0 ) {
			unsigned int program_len=0;
			program_len = programmed_pcpu_code_size;
			copy_memory(DATA_TMP_ADDR, programmed_pcpu_code_base, programmed_pcpu_code_size);
	
			// clear copy_memory region to align emmc block size
			temp = program_len % EMMC_BLOCK_SIZE;
			if( temp ) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
			}
			//2. program
	#ifdef FOR_ICE_LOAD
			prints("write pcpu_code area: uda block 0x");
			print_hex(uda_block_no);
			prints(", pcpu_code area size 0x");
			print_hex(programmed_pcpu_code_size);
			prints("\n");
	#endif
			rtprintf("write pcpu_code area : block 0x%x, size 0x%x\n", uda_block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, program_len, 0, MMC_PART_UDA)) {
		#ifdef FOR_ICE_LOAD
				prints("do_write falied\n");
		#endif
				rtprintf("do_write falied\n");
				return -4;
			}
	
			if (verify_after_write) {
		#ifdef FOR_ICE_LOAD
				prints("read back data(pcpu_code area): uda block 0x");
				print_hex(uda_block_no);
				prints(", pcpu_code area size 0x");
				print_hex(programmed_pcpu_code_size);
				prints("\n");
		#endif
				rtprintf("read back data(pcpu_code): block 0x%x, size 0x%x\n", uda_block_no, program_len);
				if ((*do_read)(device, &uda_block_no, read_buf, program_len, MMC_PART_UDA)) {
			#ifdef FOR_ICE_LOAD
					prints("do_read check falied\n");
			#endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
			#ifdef FOR_ICE_LOAD
					prints("verify pcpu_code area data falied\n");
			#endif
					rtprintf("verify pcpu_code area data falied\n");
					return -6;
				}
			}
			backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
			prints("write uda backup at blk 0x");
			print_hex(backup_uda_block_no);
			prints(".\n");
			(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, program_len, 0, MMC_PART_UDA);
			uda_block_no += align_to_boundary(programmed_pcpu_code_size, EMMC_BLOCK_SIZE);
		}

		/***********************************************************************
		* start to bl31 / bl31_sig data
		***********************************************************************/
		if( programmed_bl31_size != 0 ) {
			unsigned int program_len=0;
			program_len = programmed_bl31_size;
			copy_memory(DATA_TMP_ADDR, programmed_bl31_base, programmed_bl31_size);

			// clear copy_memory region to align emmc block size
			temp = program_len % EMMC_BLOCK_SIZE;
			if( temp ) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
			}
			//2. program

			param.bl31_addr = uda_block_no;
#ifdef FOR_ICE_LOAD
			prints("write bl31_area: uda block 0x");
			print_hex(uda_block_no);
			prints(", bl31_area size 0x");
			print_hex(programmed_bl31_size);
			prints("\n");
#endif
			rtprintf("write bl31_area: block 0x%x, size 0x%x\n", uda_block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, program_len, 0, MMC_PART_UDA)) {
	    #ifdef FOR_ICE_LOAD
				prints("do_write falied\n");
	    #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
	    #ifdef FOR_ICE_LOAD
				prints("read back data(bl31_area): uda block 0x");
				print_hex(uda_block_no);
				prints(", bl31_area size 0x");
				print_hex(programmed_bl31_size);
				prints("\n");
	    #endif
				rtprintf("read back data(bl31_area): block 0x%x, size 0x%x\n", uda_block_no, program_len);
				if ((*do_read)(device, &uda_block_no, read_buf, program_len, MMC_PART_UDA)) {
	        #ifdef FOR_ICE_LOAD
					prints("do_read check falied\n");
	        #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
	        #ifdef FOR_ICE_LOAD
					prints("verify bl31_area data falied\n");
	        #endif
					rtprintf("verify bl31_area data falied\n");
					return -6;
				}
			}
			backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
			prints("write uda backup at blk 0x");
			print_hex(backup_uda_block_no);
			prints(".\n");
			(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, program_len, 0, MMC_PART_UDA);
			uda_block_no += align_to_boundary(programmed_bl31_size, EMMC_BLOCK_SIZE);  //for uda
		}


		/***********************************************************************
		 * start to secure_os / secure_os_sig data
		 ***********************************************************************/
		if(programmed_secure_os_size != 0 ) {
            unsigned int program_len=0;
            program_len = programmed_secure_os_size;
            copy_memory(DATA_TMP_ADDR, programmed_secure_os_base, programmed_secure_os_size);

    		// clear copy_memory region to align emmc block size
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            param.secure_os_addr = uda_block_no;
            #ifdef FOR_ICE_LOAD
        	prints("write secure_os area: uda block 0x");
            print_hex(uda_block_no);
        	prints(", secure_os area size 0x");
            print_hex(programmed_secure_os_size);
            prints("\n");
            #endif
			rtprintf("write secure_os area : block 0x%x, size 0x%x\n", uda_block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, program_len, 0, MMC_PART_UDA)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(secure_os area): uda block 0x");
                print_hex(uda_block_no);
            	prints(", secure_os area size 0x");
                print_hex(programmed_secure_os_size);
                prints("\n");
                #endif
				rtprintf("read back data(secure_os): block 0x%x, size 0x%x\n", uda_block_no, program_len);
				if ((*do_read)(device, &uda_block_no, read_buf, program_len, MMC_PART_UDA)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify secure_os area data falied\n");
                    #endif
					rtprintf("verify secure_os area data falied\n");
					return -6;
				}
			}
			backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
			prints("write uda backup at blk 0x");
			print_hex(backup_uda_block_no);
			prints(".\n");
			(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, program_len, 0, MMC_PART_UDA);
			uda_block_no += align_to_boundary(programmed_secure_os_size, EMMC_BLOCK_SIZE);
		}

		/***********************************************************************
		 * start to program dte_bootcode_rtk_area
		 ***********************************************************************/
        #ifdef FOR_ICE_LOAD
        prints("*******************************************\n");
        #endif
	    rtprintf("*******************************************\n");
	    copy_memory((unsigned char *)DATA_TMP_ADDR, dte_bootcode_rtk_area, dte_bootcode_rtk_area_size);

		// clear copy_memory region to align dte_bootcode_rtk_area_size block size
		temp = dte_bootcode_rtk_area_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + dte_bootcode_rtk_area_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}

        #ifdef FOR_ICE_LOAD
    	prints("write dte_bootcode_rtk: uda block 0x");
        print_hex(uda_block_no);
    	prints(", size 0x");
        print_hex(dte_bootcode_rtk_area_size);
        prints("\n");
        #endif
		rtprintf("write dte_bootcode_rtk: block 0x%x, size 0x%x\n", uda_block_no, dte_bootcode_rtk_area_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &uda_block_no, dte_bootcode_rtk_area_size, 0, MMC_PART_UDA)) {
            #ifdef FOR_ICE_LOAD
        	prints("do_write falied\n");
            #endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
            #ifdef FOR_ICE_LOAD
        	prints("read back dte_bootcode_rtk: uda block 0x");
            print_hex(uda_block_no);
        	prints(", size 0x");
            print_hex(dte_bootcode_rtk_area_size);
            prints("\n");
            #endif
			rtprintf("read back dte_ootcode_rtk: uda block 0x%x, size 0x%x\n", uda_block_no, dte_bootcode_rtk_area_size);
			if ((*do_read)(device, &uda_block_no, read_buf, dte_bootcode_rtk_area_size, MMC_PART_UDA)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_read check falied\n");
                #endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, dte_bootcode_rtk_area_size)) {
                #ifdef FOR_ICE_LOAD
            	prints("verify dte_bootcode_rtk falied\n");
                #endif
				rtprintf("verify dte_bootcode_rtk falied\n");
				return -6;
			}
		}
		backup_uda_block_no = uda_block_no + BACKUP_EMMC_UDA_BLK_OFFSET;
		prints("write uda backup at blk 0x");
		print_hex(backup_uda_block_no);
		prints(".\n");
		(*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &backup_uda_block_no, dte_bootcode_rtk_area_size, 0, MMC_PART_UDA);
		uda_block_no += align_to_boundary(dte_bootcode_rtk_area_size, EMMC_BLOCK_SIZE);
	}

finish:
    //dump 'Finish' string to RS232
    #ifdef FOR_ICE_LOAD
    prints("Finish\n");
    #endif

    while(1);

    rtprintf("Finish\n");
	#ifndef FPGA
	    if (noreset == 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("reset...\n");
            #endif
	        rtprintf("reset...\n");
            watchdog_reset();
    }
	#endif

	#ifdef FOR_ICE_LOAD
    prints("end\n");
    #endif
    return 0;
}
