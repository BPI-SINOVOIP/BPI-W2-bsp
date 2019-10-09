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

//#define SPI_ENV_PARAM_ADDR              0x18200000
//#define SPI_ENV_PARAM_SIZE              0x00010000

#define FLASH_MAGICNO_NOR_PARALLEL		0xBE
#define FLASH_MAGICNO_NAND				0xCE
#define FLASH_MAGICNO_NOR_SERIAL		0xDE
#define FLASH_MAGICNO_EMMC	 			0xEE

#define EXT_PARA_DDR_BASE				(0xA0A00000 - UBOOT_DDR_OFFSET)	// t_extern_param + logo + rescue base address on DDR
#define NAND_ENV_DDR_BASE				(0xA0040000 - UBOOT_DDR_OFFSET)	// modify by angus, original value is 0xa0010000

#define BOOTCODE_SIZE_ADDR				0XB801A60C
#define SIMULATION_DUMP_ADDR			(0xA3000000 - UBOOT_DDR_OFFSET)	// dump hwsetting/bootcode related to DDR
#define NAND_BOOT_BACKUP_COUNT			3								// number of backup bootcode in NAND flash

#define HWSETTING_INFO_LEN				96	//not use anymore, for Romcode read size

#define RTD129x_CHIP_REVISION_A00       (0x00000000)
#define RTD129x_CHIP_REVISION_A01       (0x00010000)
#define RTD129x_CHIP_REVISION_B00       (0x00020000)

#define BOOTCODE_MAX_SIZE               0xC0000
#define FSBL_OS_MAX_SIZE                0xC0000

extern unsigned char resetrom[];		//rom data : 0x1FC0_0000 ~ 0x1FC0_1FFF
extern unsigned char resetrom_end;
extern unsigned char mips_resetrom[];		
extern unsigned char mips_resetrom_end;
extern unsigned char hwsetting[];
extern unsigned char hwsetting_end;
extern unsigned char hasharray[];
extern unsigned char hasharray_end;
extern unsigned char hasharray64[];
extern unsigned char hasharray64_end;
extern unsigned char signature[];
extern unsigned char signature_end;
extern unsigned char fsbl[];
extern unsigned char fsbl_end;
extern unsigned char fsbl_signature[];
extern unsigned char fsbl_signature_end;
extern unsigned char fsbl_vm[];
extern unsigned char fsbl_vm_end;
extern unsigned char fsbl_vm_signature[];
extern unsigned char fsbl_vm_signature_end;
extern unsigned char fsbl_os[];
extern unsigned char fsbl_os_end;
extern unsigned char fsbl_os_signature[];
extern unsigned char fsbl_os_signature_end;
extern unsigned char bl31[];
extern unsigned char bl31_end;
extern unsigned char bl31_signature[];
extern unsigned char bl31_signature_end;
extern unsigned char rsa_pub[];
extern unsigned char rsa_pub_end;
#if defined(Config_Secure_Improve_TRUE)
extern unsigned char Kpublic_fw[];
extern unsigned char Kpublic_fw_end;
extern unsigned char Kpublic_fw_signature[];
extern unsigned char Kpublic_fw_signature_end;
extern unsigned char Kpublic_tee[];
extern unsigned char Kpublic_tee_end;
extern unsigned char Kpublic_tee_signature[];
extern unsigned char Kpublic_tee_signature_end;
#endif
extern unsigned char bootcode2_boot_hasharray[];
extern unsigned char bootcode2_boot_hasharray_end;
extern unsigned char bootcode2_boot_signature[];
extern unsigned char bootcode2_boot_signature_end;
#ifdef MAGALLAN_PRJ
extern unsigned char bootcode3_boot_hasharray[];
extern unsigned char bootcode3_boot_hasharray_end;
extern unsigned char bootcode3_boot_signature[];
extern unsigned char bootcode3_boot_signature_end;
#endif
extern unsigned char ecbarray[];
extern unsigned char ecbarray_end;
extern unsigned char linux_rescue_hasharray[];
extern unsigned char linux_rescue_hasharray_end;
extern unsigned char linux_rescue_signature[];
extern unsigned char linux_rescue_signature_end;
extern unsigned char cbc_linux[];
extern unsigned char cbc_linux_end;
extern unsigned char hwsetting_sig_image[];
extern unsigned char hwsetting_sig_image_end;
extern unsigned char dcas_key_sig_image[];
extern unsigned char dcas_key_sig_image_end;
extern unsigned char logo[];
extern unsigned char logo_end;
extern unsigned char logo2[];
extern unsigned char logo2_end;
extern unsigned char logo3[];
extern unsigned char logo3_end;
extern unsigned char logo4[];
extern unsigned char logo4_end;
extern unsigned char logo5[];
extern unsigned char logo5_end;
extern unsigned char logo6[];
extern unsigned char logo6_end;
extern unsigned char logo7[];
extern unsigned char logo7_end;
extern unsigned char logo8[];
extern unsigned char logo8_end;

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
	//1395 set mux to spi
	REG32(ISO_muxpad5) &= 0xFFFFFF00;	//clear [7:0]
	//set sf_en=1
	REG32(ISO_muxpad6) |= 0x800;
#endif	
}

void set_nand_pin_mux(void)
{
#ifndef FPGA
	//1395 ISO_muxpad4
    //set mux to nf      
	REG32(ISO_muxpad4) = 0x00555555;
	REG32(ISO_muxpad5) &= 0xFFFFFFC0;  //clear [5:0]
	REG32(ISO_muxpad5) |= 0x15;
	//set sf_en=0
	REG32(ISO_muxpad6) &= 0xFFFFF7FF;  //clear [11]
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
	//1395 ISO_muxpad4
    //set mux to emmc      
	REG32(ISO_muxpad4) = 0x00aaaaaa;
	//set sf_en=1
	REG32(ISO_muxpad6) |= 0x800;
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
    unsigned char * spi_resetrom_addr;
    unsigned char * spi_mips_resetrom_addr;
    unsigned char * spi_hwsetting_addr;
    unsigned char * spi_param_addr;
    unsigned char * spi_param_addr2;
    unsigned char * spi_bootcode_addr;
    unsigned char * spi_rescue_addr;
    unsigned char * spi_rescue_sig_addr;
    // spi fsbl
    unsigned char * spi_fsbl_addr;
    unsigned char * spi_fsbl_sig_addr;
    // spi fsbl os
    unsigned char * spi_fsbl_os_addr;
    unsigned char * spi_fsbl_os_sig_addr;
    // spi bl31
    unsigned char * spi_bl31_addr;
    unsigned char * spi_bl31_sig_addr;
#if defined(Config_Secure_Improve_TRUE)
    unsigned char * spi_Kpublic_fw_addr;
    unsigned char * spi_Kpublic_fw_sig_addr;
    unsigned char * spi_Kpublic_tee_addr;
    unsigned char * spi_Kpublic_tee_sig_addr;
#endif
    unsigned char * spi_next_fw_start_addr;
    unsigned char * spi_rsa_pub_addr;
    unsigned char * spi_bootcode_sig_addr;
    unsigned char * spi_bootcode_addr2;
    unsigned char * spi_bootcode_addr3;
    unsigned char * spi_key_sig_addr;
    unsigned char * spi_key_sig_addr2;
    unsigned char * spi_key_sig_addr3;

    // for nand

    // for emmc

    // common
    unsigned char * logo_addr;
    unsigned char * logo2_addr;
    unsigned char * logo3_addr;
    unsigned char * logo4_addr;
    unsigned char * logo5_addr;
    unsigned char * logo6_addr;
    unsigned char * logo7_addr;
    unsigned char * logo8_addr;

    unsigned int  resetrom_size;
    unsigned int  mips_resetrom_size;
    unsigned int  hwsetting_size;
    unsigned int  hasharray_size;
    unsigned int  hasharray64_size;
	unsigned int  signature_size;
	unsigned int  bootcode2_boot_hasharray_size;
	unsigned int  bootcode2_boot_signature_size;
	unsigned int  bootcode3_boot_hasharray_size;
	unsigned int  bootcode3_boot_signature_size;
	unsigned int  linux_rescue_hasharray_size;
	unsigned int  linux_rescue_signature_size;
    unsigned int  hwsetting_sig_size;
    unsigned int  dcas_key_sig_size;
    unsigned int  logo_size;
    unsigned int  logo2_size;
    unsigned int  logo3_size;
    unsigned int  logo4_size;
    unsigned int  logo5_size;
    unsigned int  logo6_size;
    unsigned int  logo7_size;
    unsigned int  logo8_size;

    unsigned char * env_param_addr;
    unsigned char * linux_sec1_addr;
    unsigned char * linux_sec2_addr;
    unsigned int    linux_sec1_size;
    unsigned int    linux_sec2_size;

    unsigned char * programmed_img_base;
    unsigned char * programmed_img64_base;
    unsigned int    programmed_img_size;
    unsigned int    programmed_img64_size;

	unsigned char * programmed_img_sig_base;
	unsigned int	programmed_img_sig_size;
	unsigned char * programmed_linux_rescue_sig_base;
	unsigned int	programmed_linux_rescue_sig_size;

	unsigned char * programmed_fsbl_base;
	unsigned int	programmed_fsbl_size;
	unsigned char * programmed_fsbl_sig_base;
	unsigned int	programmed_fsbl_sig_size;

#if defined(Config_FSBL_VM_TRUE)
	unsigned char * programmed_fsbl_vm_base;
	unsigned int	programmed_fsbl_vm_size;
	unsigned char * programmed_fsbl_vm_sig_base;
	unsigned int	programmed_fsbl_vm_sig_size;
#endif
	
	unsigned char * programmed_fsbl_os_base;
	unsigned int	programmed_fsbl_os_size;
	unsigned char * programmed_fsbl_os_sig_base;
	unsigned int	programmed_fsbl_os_sig_size;
    unsigned char * programmed_bl31_base;
	unsigned int	programmed_bl31_size;
	unsigned char * programmed_bl31_sig_base;
	unsigned int	programmed_bl31_sig_size;
#if defined(Config_Secure_Improve_TRUE)
	unsigned char * programmed_Kpublic_fw_base;
	unsigned int	programmed_Kpublic_fw_size;
	unsigned char * programmed_Kpublic_fw_sig_base;
	unsigned int	programmed_Kpublic_fw_sig_size;
	unsigned char * programmed_Kpublic_tee_base;
	unsigned int	programmed_Kpublic_tee_size;
	unsigned char * programmed_Kpublic_tee_sig_base;
	unsigned int	programmed_Kpublic_tee_sig_size;
#endif
	unsigned char * programmed_rsa_pub_base;
	unsigned int	programmed_rsa_pub_size;
    
    unsigned char * bootcode2_boot_programmed_img_base;
    unsigned int    bootcode2_boot_programmed_img_size;
    
    unsigned char * bootcode3_boot_programmed_img_base;
    unsigned int    bootcode3_boot_programmed_img_size;    

    unsigned char * programmed_linux_rescue_img_base;
    unsigned int    programmed_linux_rescue_img_size;

    unsigned char   flash_type;
    unsigned char   flash_magicno;
    unsigned int    idx, i, j;
    unsigned int    temp, reg_addr;
    unsigned char * temp_ptr;
    unsigned int *  temp_ptr32;
	void * device;
    int res;
    int save_nand_env;

    unsigned int  block_size;
    unsigned int  total_block_cnt;

    t_extern_param param;
    t_extern_param *orignal_param;

#ifdef CR_MEMORY_DUMP
    UINT32 emmc_dump_addr = 0x03000000;
    UINT32 emmc_dump_ptr=0;
#endif
	// -------------------------------------------------------------------------
	// function declaration
	// -------------------------------------------------------------------------
    int (*do_erase)(void  *, unsigned int * , unsigned int);
    int (*do_write)(void *, unsigned char *, unsigned int *, unsigned int, unsigned int, const unsigned int);
    int (*do_identify)(void **);
    int (*do_init)(void *);
    int (*do_read)(void *, unsigned int *, unsigned char *, unsigned int, INT32);
    int (*do_hide_hwsetting)(void *, unsigned char *, unsigned int *, unsigned int, unsigned int, const unsigned int);
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
	resetrom_size  				  = (unsigned int )(&resetrom_end  			   - resetrom);
	mips_resetrom_size  		  = (unsigned int )(&mips_resetrom_end  	   - mips_resetrom);
    hwsetting_size 				  = (unsigned int )(&hwsetting_end 			   - hwsetting);	//hwsetting + signature for both secure/non-secure
    hasharray_size                = (unsigned int )(&hasharray_end 			   - hasharray);	//bootcode for secure/non-secure
    hasharray64_size                = (unsigned int )(&hasharray64_end 			   - hasharray64);	//bootcode for secure/non-secure
	signature_size                = (unsigned int )(&signature_end 			   - signature);	//bootcode signature for secure/non-secure
	bootcode2_boot_hasharray_size = (unsigned int )(&bootcode2_boot_hasharray_end 			   - bootcode2_boot_hasharray);
	bootcode2_boot_signature_size = (unsigned int )(&bootcode2_boot_signature_end 			   - bootcode2_boot_signature);
#ifdef MAGALLAN_PRJ
	bootcode3_boot_hasharray_size = (unsigned int )(&bootcode3_boot_hasharray_end 			   - bootcode3_boot_hasharray);
	bootcode3_boot_signature_size = (unsigned int )(&bootcode3_boot_signature_end 			   - bootcode3_boot_signature);
#endif
	linux_rescue_hasharray_size   = (unsigned int )(&linux_rescue_hasharray_end - linux_rescue_hasharray);
	linux_rescue_signature_size   = (unsigned int )(&linux_rescue_signature_end - linux_rescue_signature);
    hwsetting_sig_size 	          = (unsigned int )(&hwsetting_sig_image_end    - hwsetting_sig_image);
	dcas_key_sig_size 	          = (unsigned int )(&dcas_key_sig_image_end     - dcas_key_sig_image);
	logo_size      				  = (unsigned int )(&logo_end      			   - logo);
    logo2_size     				  = (unsigned int )(&logo2_end     			   - logo2);
    logo3_size     				  = (unsigned int )(&logo3_end     			   - logo3);
    logo4_size     				  = (unsigned int )(&logo4_end     			   - logo4);
    logo5_size     				  = (unsigned int )(&logo5_end     			   - logo5);
    logo6_size     				  = (unsigned int )(&logo6_end     			   - logo6);
    logo7_size     				  = (unsigned int )(&logo7_end     			   - logo7);
    logo8_size     				  = (unsigned int )(&logo8_end     			   - logo8);

    programmed_img_size 		  = hasharray_size;
	programmed_img_base           = hasharray;			//without signature
	programmed_img64_size 		  = hasharray64_size;
	programmed_img64_base           = hasharray64;			//without signature

	programmed_img_sig_base		  = signature;

    // fsbl
	programmed_fsbl_size          = (unsigned int )(&fsbl_end - fsbl);
    programmed_fsbl_base          = fsbl;

	// fsbl_vm
#if defined(Config_FSBL_VM_TRUE)	
	programmed_fsbl_vm_size          = (unsigned int )(&fsbl_vm_end - fsbl_vm);
    programmed_fsbl_vm_base          = fsbl_vm;
#endif	
    // tee os
	programmed_fsbl_os_size       = (unsigned int )(&fsbl_os_end - fsbl_os);
    programmed_fsbl_os_base       = fsbl_os;

    // bl31
    programmed_bl31_size       = (unsigned int )(&bl31_end - bl31);
    programmed_bl31_base       = bl31;
    
	programmed_rsa_pub_size   = (unsigned int )(&rsa_pub_end - rsa_pub);
    programmed_rsa_pub_base       = rsa_pub;
#if defined(Config_Secure_Improve_TRUE)
	programmed_Kpublic_fw_size   = (unsigned int )(&Kpublic_fw_end - Kpublic_fw);
    programmed_Kpublic_fw_base       = Kpublic_fw;
	programmed_Kpublic_fw_sig_size   = (unsigned int )(&Kpublic_fw_signature_end - Kpublic_fw_signature);
    programmed_Kpublic_fw_sig_base       = Kpublic_fw_signature;
	programmed_Kpublic_tee_size   = (unsigned int )(&Kpublic_tee_end - Kpublic_tee);
    programmed_Kpublic_tee_base       = Kpublic_tee;
	programmed_Kpublic_tee_sig_size   = (unsigned int )(&Kpublic_tee_signature_end - Kpublic_tee_signature);
    programmed_Kpublic_tee_sig_base       = Kpublic_tee_signature;
#endif
	if (signature_size>=sizeof(unsigned int))
		programmed_img_sig_size		  = signature_size;
	else
		programmed_img_sig_size = 0;

#ifdef ROMCODE_ON_SPI
    spi_resetrom_addr  			 = (unsigned char *)SPI_CODE_PART1; //assign arm romcode start address
    spi_mips_resetrom_addr  	 = (unsigned char *)SPI_CODE_PART11; //assign lexra romcode start address
    spi_param_addr 				 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE);
    spi_hwsetting_addr 			 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE + SPI_MAX_PARAM_SIZE); //assign hw setting start address, moidfy by angus, original value is 0xb8108000
#else
    spi_resetrom_addr			 = NULL;
    spi_mips_resetrom_addr  	 = NULL; 
    spi_param_addr 				 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE);
    spi_hwsetting_addr 			 = (unsigned char *)(SPI_CODE_PART1 + SPI_RESETROM_SIZE + SPI_MIPS_RESETROM_SIZE + SPI_MAX_PARAM_SIZE); //assign hw setting start address, moidfy by angus, original value is 0xb8108000
#endif
	spi_bootcode_addr            = spi_hwsetting_addr + hwsetting_size;
	spi_bootcode_sig_addr        = spi_bootcode_addr + hasharray_size;
    spi_next_fw_start_addr       = spi_bootcode_sig_addr + signature_size;
#if defined(Config_FSBL_TRUE)
    // spi fsbl
    spi_fsbl_addr                = spi_next_fw_start_addr;
    spi_next_fw_start_addr       = spi_fsbl_addr + programmed_fsbl_size;
#endif
#if defined(Config_FSBL_OS_TRUE)
    // spi tee os
    spi_fsbl_os_addr             = spi_next_fw_start_addr;
    spi_next_fw_start_addr       = spi_fsbl_os_addr + programmed_fsbl_os_size;
#endif
#if defined(Config_FSBL_OS_TRUE)
    // spi bl31
    spi_bl31_addr                = spi_next_fw_start_addr;
    spi_next_fw_start_addr       = spi_bl31_addr + programmed_bl31_size;
#endif
#if defined(Config_Secure_Improve_TRUE)
	spi_Kpublic_fw_addr          = spi_next_fw_start_addr;
	spi_Kpublic_fw_sig_addr      = spi_Kpublic_fw_addr + programmed_Kpublic_fw_size;    
	spi_Kpublic_tee_addr         = spi_Kpublic_fw_sig_addr + programmed_Kpublic_fw_sig_size;
	spi_Kpublic_tee_sig_addr     = spi_Kpublic_tee_addr + programmed_Kpublic_tee_size;    
	spi_rescue_addr              = spi_Kpublic_tee_sig_addr + programmed_Kpublic_tee_sig_size;
#else
	spi_rescue_addr              = spi_next_fw_start_addr;
#endif

	spi_rsa_pub_addr             = SPI_CODE_PART1+0x80000;


	rtprintf("*** %s %d : resetrom_size                      = 0x%08x\n", __FUNCTION__, __LINE__, resetrom_size);
	rtprintf("*** %s %d : mips_resetrom_size                 = 0x%08x\n", __FUNCTION__, __LINE__, mips_resetrom_size);
	rtprintf("*** %s %d : hwsetting_size                     = 0x%08x\n", __FUNCTION__, __LINE__, hwsetting_size);
	rtprintf("*** %s %d : hwsetting_sig_size                 = 0x%08x\n", __FUNCTION__, __LINE__, hwsetting_sig_size);
	rtprintf("*** %s %d : hasharray_size                     = 0x%08x\n", __FUNCTION__, __LINE__, hasharray_size);
	rtprintf("*** %s %d : signature_size                     = 0x%08x\n", __FUNCTION__, __LINE__, signature_size);
	rtprintf("*** %s %d : programmed_img_base                = 0x%08x\n", __FUNCTION__, __LINE__, (unsigned int)programmed_img_base);
	rtprintf("*** %s %d : programmed_img_size                = 0x%08x\n", __FUNCTION__, __LINE__, programmed_img_size);
	rtprintf("*** %s %d : dcas_key_sig_size                  = 0x%08x\n", __FUNCTION__, __LINE__, dcas_key_sig_size);
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

#ifdef Board_CPU_RTD1295
    if (get_chip_rev_id() < RTD129x_CHIP_REVISION_B00)
    {
        prints("The chip id is not support, so system will reboot...\n");
        watchdog_reset();
        return -1;
    }
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
	    	do_hide_hwsetting = NULL;
	    	env_param_addr    = (unsigned char *)SPI_ENV_PARAM_ADDR;
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
	    	do_hide_hwsetting = do_hide_hwsetting_e;
	    	env_param_addr    = (unsigned char *)NAND_ENV_DDR_BASE;
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
	    	do_hide_hwsetting = NULL;
	    	env_param_addr    = (unsigned char *)NAND_ENV_DDR_BASE;
    		break;

    	default:
            #ifdef FOR_ICE_LOAD
            prints("unknown!\n");
            #endif
    		rtprintf("unknown!\n");
    		return -1;

    		break;
    }

    /***********************************************************************
     * update bootcode size of the HW setting table
     ***********************************************************************/
#ifdef MAGALLAN_PRJ
	if( check_secure_boot() != NDS_SECURE_BOOT ) {
		// find bootcode size field in HW setting table
		temp_ptr32 = (unsigned int *)hwsetting;
		res = 0;
		for( idx = 0; idx < ( hwsetting_size >> 2); idx += temp )
		{
			reg_addr = swap_endian( temp_ptr32[idx] );
			switch( reg_addr & 0x3 )
			{
				case 1:	 // poll operation: 3 word
				case 2:	 // mask operation: 3 word
					temp = 3;
					break;
				default: // write/nop operation: 2 word
					temp = 2;
					break;
			}

			if( reg_addr == BOOTCODE_SIZE_ADDR ) {
				// change to real bootcode size
				rtprintf("update hwsetting reg(0x%08x) with 0x%08x\n", reg_addr, *((unsigned int *)programmed_img_base));
				temp_ptr32[idx + 1] = *((unsigned int *)programmed_img_base);
				res = 1;
				break;
			}
		}
	}
#endif
    /***********************************************************************
     * calculate images start address
     ***********************************************************************/
	logo_addr  = 0x0;
	logo2_addr = 0x0;
	logo3_addr = 0x0;
	logo4_addr = 0x0;
	logo5_addr = 0x0;
	logo6_addr = 0x0;
	logo7_addr = 0x0;
	logo8_addr = 0x0;
    linux_sec1_addr = 0;
    linux_sec1_size = 0;
    linux_sec2_addr = 0;
    linux_sec2_size = 0;
    if( (flash_magicno == FLASH_MAGICNO_NAND) || (flash_magicno == FLASH_MAGICNO_EMMC) )
    {
    	// data will be copied to DDR when NAND oreMMC,
    	// so we need to fill with corresponding DRAM address
    	temp = EXT_PARA_DDR_BASE + sizeof(param);
    	rtprintf(" EXT_PARA_DDR_BASE = 0x%08x\n", EXT_PARA_DDR_BASE);
    	rtprintf(" sizeof(param)     = 0x%08x\n", sizeof(param));
    	rtprintf(" temp              = 0x%08x\n", temp);

    	logo_addr  = (unsigned char *)temp;		temp += logo_size;
		logo2_addr = (unsigned char *)temp;		temp += logo2_size;
		logo3_addr = (unsigned char *)temp;		temp += logo3_size;
		logo4_addr = (unsigned char *)temp;		temp += logo4_size;
		logo5_addr = (unsigned char *)temp;		temp += logo5_size;
		logo6_addr = (unsigned char *)temp;		temp += logo6_size;
		logo7_addr = (unsigned char *)temp;		temp += logo7_size;
		logo8_addr = (unsigned char *)temp;		temp += logo8_size;

		linux_sec1_addr = (unsigned char *)temp;
		linux_sec1_size = programmed_linux_rescue_img_size;
        linux_sec2_addr = 0;
        linux_sec2_size = 0;

    	rtprintf(" logo_addr  = 0x%08x\n", logo_addr);
    	rtprintf(" logo2_addr = 0x%08x\n", logo2_addr);
    	rtprintf(" logo3_addr = 0x%08x\n", logo3_addr);
    	rtprintf(" logo4_addr = 0x%08x\n", logo4_addr);
    	rtprintf(" logo5_addr = 0x%08x\n", logo5_addr);
    	rtprintf(" logo6_addr = 0x%08x\n", logo6_addr);
    	rtprintf(" logo7_addr = 0x%08x\n", logo7_addr);
    	rtprintf(" logo8_addr = 0x%08x\n", logo8_addr);

    	rtprintf(" linux_sec1_addr = 0x%08x\n", linux_sec1_addr);
    	rtprintf(" linux_sec1_size = 0x%08x\n", linux_sec1_size);
    }
    else if (flash_magicno == FLASH_MAGICNO_NOR_SERIAL)	// NOR flash case
    {
	    res = check_secure_boot();
	    if( res == DCAS_SECURE_BOOT ) {
	    	temp = ((programmed_img_size + hwsetting_size + dcas_key_sig_size ) / block_size )+ 1;
	    }
		else {
        	temp = ((programmed_img_size + hwsetting_size) / block_size )+ 1;
		}
        total_block_cnt -= temp;
        temp_ptr = (unsigned char *)(spi_hwsetting_addr + (temp * block_size));

        rtprintf(" spi_resetrom_addr  = 0x%08x\n", spi_resetrom_addr);
        rtprintf(" spi_mips_resetrom_addr  = 0x%08x\n", spi_mips_resetrom_addr);
        rtprintf(" spi_param_addr     = 0x%08x\n", spi_param_addr);
        rtprintf(" spi_hwsetting_addr = 0x%08x\n", spi_hwsetting_addr);
        rtprintf(" spi_bootcode_addr  = 0x%08x\n", spi_bootcode_addr);
        rtprintf(" spi_key_sig_addr   = 0x%08x\n", spi_key_sig_addr);
        rtprintf(" logo_addr          = 0x%08x\n", logo_addr);
    	rtprintf(" logo2_addr         = 0x%08x\n", logo2_addr);
    	rtprintf(" logo3_addr         = 0x%08x\n", logo3_addr);
    	rtprintf(" logo4_addr         = 0x%08x\n", logo4_addr);
    	rtprintf(" logo5_addr         = 0x%08x\n", logo5_addr);
    	rtprintf(" logo6_addr         = 0x%08x\n", logo6_addr);
    	rtprintf(" logo7_addr         = 0x%08x\n", logo7_addr);
    	rtprintf(" logo8_addr         = 0x%08x\n", logo8_addr);
    	rtprintf(" linux_sec1_addr    = 0x%08x\n", linux_sec1_addr);
    	rtprintf(" linux_sec1_size    = 0x%08x\n", linux_sec1_size);
    }
    else
    {
    	rtprintf("unknown flash_magicno\n");
    	return -66;
    }
    /***********************************************************************
     * assign value to param object
     ***********************************************************************/
    param.secure_mode        	= check_secure_boot();
    param.flash_type 		 	= flash_magicno;
    param.region     		 	= 0;

	param.mac_hi     		 	= Param_MAC_hi;
	param.mac_lo     		 	= Param_MAC_lo;

    param.array_img_saddr        = 0;
    param.array_img_size         = 0;
    param.secure_mode            = check_secure_boot();
    param.rescue_img_size        = programmed_linux_rescue_img_size;
    param.rescue_img_addr        = 0;
    param.rescue_img_part0_saddr = linux_sec1_addr;
    param.rescue_img_part0_len   = linux_sec1_size;
    param.rescue_img_part1_saddr = linux_sec2_addr;
    param.rescue_img_part1_len   = linux_sec2_size;

	//clear logo value if logo2, logo3 ,logo4 was not used
	param.logo_img_saddr         = 0;
	param.logo2_img_saddr        = 0;
	param.logo3_img_saddr        = 0;
	param.logo4_img_saddr        = 0;
	param.logo5_img_saddr        = 0;
	param.logo6_img_saddr        = 0;
	param.logo7_img_saddr        = 0;
	param.logo8_img_saddr        = 0;

	param.logo_img_len           = 0;
	param.logo2_img_len          = 0;
	param.logo3_img_len          = 0;
	param.logo4_img_len          = 0;
	param.logo5_img_len          = 0;
	param.logo6_img_len          = 0;
	param.logo7_img_len          = 0;
	param.logo8_img_len          = 0;

	param.logo_type              = 0;
	param.logo2_type             = 0;
	param.logo3_type             = 0;
	param.logo4_type             = 0;
	param.logo5_type             = 0;
	param.logo6_type             = 0;
	param.logo7_type             = 0;
	param.logo8_type             = 0;

	param.logo_offset     		 = 0;
	param.logo2_offset    		 = 0;
	param.logo3_offset    		 = 0;
	param.logo4_offset    		 = 0;
	param.logo5_offset    		 = 0;
	param.logo6_offset    		 = 0;
	param.logo7_offset    		 = 0;
	param.logo8_offset    		 = 0;

	param.logo_reg_5370   		 = 0;
	param.logo2_reg_5370  		 = 0;
	param.logo3_reg_5370  		 = 0;
	param.logo4_reg_5370  		 = 0;
	param.logo5_reg_5370  		 = 0;
	param.logo6_reg_5370  		 = 0;
	param.logo7_reg_5370  		 = 0;
	param.logo8_reg_5370  		 = 0;

	param.logo_reg_5374   		 = 0;
	param.logo2_reg_5374  		 = 0;
	param.logo3_reg_5374  		 = 0;
	param.logo4_reg_5374  		 = 0;
	param.logo5_reg_5374  		 = 0;
	param.logo6_reg_5374  		 = 0;
	param.logo7_reg_5374  		 = 0;
	param.logo8_reg_5374  		 = 0;

	param.logo_reg_5378   		 = 0;
	param.logo2_reg_5378  		 = 0;
	param.logo3_reg_5378  		 = 0;
	param.logo4_reg_5378  		 = 0;
	param.logo5_reg_5378  		 = 0;
	param.logo6_reg_5378  		 = 0;
	param.logo7_reg_5378  		 = 0;
	param.logo8_reg_5378  		 = 0;

	param.logo_reg_537c   		 = 0;
	param.logo2_reg_537c  		 = 0;
	param.logo3_reg_537c  		 = 0;
	param.logo4_reg_537c  		 = 0;
	param.logo5_reg_537c  		 = 0;
	param.logo6_reg_537c  		 = 0;
	param.logo7_reg_537c  		 = 0;
	param.logo8_reg_537c  		 = 0;

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

	#if defined(Logo_Source_FLASH)
	    param.logo_img_saddr = logo_addr;
	    param.logo_img_len   = logo_size;
		#if defined(Logo_Type_NTSC)
		    param.logo_type   = 0;
		#elif defined(Logo_Type_PAL)
		    param.logo_type   = 1;
		#elif defined(Logo_Type_1080p50)
		    param.logo_type   = 2;
		#elif defined(Logo_Type_1080p60)
		    param.logo_type   = 3;
		#endif
	    param.logo_offset   = Logo_Offset;
	    param.logo_reg_5370 = Logo_Reg5370;
	    param.logo_reg_5374 = Logo_Reg5374;
	    param.logo_reg_5378 = Logo_Reg5378;
	    param.logo_reg_537c = Logo_Reg537c;
	#endif

	#if defined(Logo2_Source_FLASH)
	    param.logo2_img_saddr = logo2_addr;
	    param.logo2_img_len   = logo2_size;
		#if defined(Logo2_Type_NTSC)
			param.logo2_type   = 0;
		#elif defined(Logo2_Type_PAL)
			param.logo2_type   = 1;
		#elif defined(Logo2_Type_1080p50)
			param.logo2_type   = 2;
		#elif defined(Logo2_Type_1080p60)
			param.logo2_type   = 3;
		#endif
	    param.logo2_offset   = Logo2_Offset;
	    param.logo2_reg_5370 = Logo2_Reg5370;
	    param.logo2_reg_5374 = Logo2_Reg5374;
	    param.logo2_reg_5378 = Logo2_Reg5378;
	    param.logo2_reg_537c = Logo2_Reg537c;
	#endif

	#if defined(Logo3_Source_FLASH)
		param.logo3_img_saddr = logo3_addr;
		param.logo3_img_len   = logo3_size  ;
		#if defined(Logo3_Type_NTSC)
			param.logo3_type   = 0  ;
		#elif defined(Logo3_Type_PAL)
			param.logo3_type   = 1  ;
		#elif defined(Logo3_Type_1080p50)
			param.logo3_type   = 2;
		#elif defined(Logo3_Type_1080p60)
			param.logo3_type   = 3;
		#endif
		param.logo3_offset   = Logo3_Offset;
		param.logo3_reg_5370 = Logo3_Reg5370;
		param.logo3_reg_5374 = Logo3_Reg5374;
		param.logo3_reg_5378 = Logo3_Reg5378;
		param.logo3_reg_537c = Logo3_Reg537c;
	#endif

	#if defined(Logo4_Source_FLASH)
		param.logo4_img_saddr = logo4_addr;
		param.logo4_img_len   = logo4_size  ;
		#if defined(Logo4_Type_NTSC)
			param.logo4_type   = 0  ;
		#elif defined(Logo4_Type_PAL)
			param.logo4_type   = 1  ;
		#elif defined(Logo4_Type_1080p50)
			param.logo4_type   = 2;
		#elif defined(Logo4_Type_1080p60)
			param.logo4_type   = 3;
		#endif
		param.logo4_offset   = Logo4_Offset;
		param.logo4_reg_5370 = Logo4_Reg5370;
		param.logo4_reg_5374 = Logo4_Reg5374;
		param.logo4_reg_5378 = Logo4_Reg5378;
		param.logo4_reg_537c = Logo4_Reg537c;
	#endif

	#if defined(Logo5_Source_FLASH)
		param.logo5_img_saddr = logo5_addr;
		param.logo5_img_len   = logo5_size  ;
		#if defined(Logo5_Type_NTSC)
			param.logo5_type   = 0  ;
		#elif defined(Logo5_Type_PAL)
			param.logo5_type   = 1  ;
		#elif defined(Logo5_Type_1080p50)
			param.logo5_type   = 2;
		#elif defined(Logo5_Type_1080p60)
			param.logo5_type   = 3;
		#endif
		param.logo5_offset   = Logo5_Offset;
		param.logo5_reg_5370 = Logo5_Reg5370;
		param.logo5_reg_5374 = Logo5_Reg5374;
		param.logo5_reg_5378 = Logo5_Reg5378;
		param.logo5_reg_537c = Logo5_Reg537c;
	#endif

	#if defined(Logo6_Source_FLASH)
		param.logo6_img_saddr = logo6_addr;
		param.logo6_img_len   = logo6_size  ;
		#if defined(Logo6_Type_NTSC)
			param.logo6_type   = 0  ;
		#elif defined(Logo6_Type_PAL)
			param.logo6_type   = 1  ;
		#elif defined(Logo6_Type_1080p50)
			param.logo6_type   = 2;
		#elif defined(Logo6_Type_1080p60)
			param.logo6_type   = 3;
		#endif
		param.logo6_offset   = Logo6_Offset;
		param.logo6_reg_5370 = Logo6_Reg5370;
		param.logo6_reg_5374 = Logo6_Reg5374;
		param.logo6_reg_5378 = Logo6_Reg5378;
		param.logo6_reg_537c = Logo6_Reg537c;
	#endif

	#if defined(Logo7_Source_FLASH)
		param.logo7_img_saddr = logo7_addr;
		param.logo7_img_len   = logo7_size  ;
		#if defined(Logo7_Type_NTSC)
			param.logo7_type   = 0  ;
		#elif defined(Logo7_Type_PAL)
			param.logo7_type   = 1  ;
		#elif defined(Logo7_Type_1080p50)
			param.logo7_type   = 2;
		#elif defined(Logo7_Type_1080p60)
			param.logo7_type   = 3;
		#endif
		param.logo7_offset   = Logo7_Offset;
		param.logo7_reg_5370 = Logo7_Reg5370;
		param.logo7_reg_5374 = Logo7_Reg5374;
		param.logo7_reg_5378 = Logo7_Reg5378;
		param.logo7_reg_537c = Logo7_Reg537c;
	#endif

	#if defined(Logo8_Source_FLASH)
		param.logo8_img_saddr = logo8_addr;
		param.logo8_img_len   = logo8_size  ;
		#if defined(Logo8_Type_NTSC)
			param.logo8_type   = 0  ;
		#elif defined(Logo8_Type_PAL)
			param.logo8_type   = 1  ;
		#elif defined(Logo8_Type_1080p50)
			param.logo8_type   = 2;
		#elif defined(Logo8_Type_1080p60)
			param.logo8_type   = 3;
		#endif
		param.logo8_offset   = Logo8_Offset;
		param.logo8_reg_5370 = Logo8_Reg5370;
		param.logo8_reg_5374 = Logo8_Reg5374;
		param.logo8_reg_5378 = Logo8_Reg5378;
		param.logo8_reg_537c = Logo8_Reg537c;
	#endif
    param.env_param_saddr = env_param_addr;
    param.data_start_blk = 0;

	#if defined(Config_HDMI_Key1) && defined(Config_HDMI_Key2) && defined(Config_HDMI_Key3) && \
		defined(Config_HDMI_Key4) && defined(Config_HDMI_Key5) && defined(Config_HDMI_Key6)
		{
			// use defined HDMI key
			idx = 0;
			temp_ptr = Config_HDMI_Key1;
			for (i = 0; (i < sizeof(param.hdmi_key1)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key1[i] = temp_ptr[i];

			temp_ptr = Config_HDMI_Key2;
			for (i = 0; (i < sizeof(param.hdmi_key2)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key2[i] = temp_ptr[i];

			temp_ptr = Config_HDMI_Key3;
			for (i = 0; (i < sizeof(param.hdmi_key3)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key3[i] = temp_ptr[i];

			temp_ptr = Config_HDMI_Key4;
			for (i = 0; (i < sizeof(param.hdmi_key4)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key4[i] = temp_ptr[i];

			temp_ptr = Config_HDMI_Key5;
			for (i = 0; (i < sizeof(param.hdmi_key5)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key5[i] = temp_ptr[i];

			temp_ptr = Config_HDMI_Key6;
			for (i = 0; (i < sizeof(param.hdmi_key6)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.hdmi_key6[i] = temp_ptr[i];

			// make sure key length is correct (omit string terminating symbol '\0')
			if ( idx != (sizeof(param.hdmi_key1)-1+sizeof(param.hdmi_key2)-1+sizeof(param.hdmi_key3)-1+sizeof(param.hdmi_key4)-1+sizeof(param.hdmi_key5)-1+sizeof(param.hdmi_key6)-1) )
			{
				rtprintf("HDMI key length incorrect!\n");
				return -200;
			}
		}
	#endif

	#if defined(custom_value)
		{
			idx = 0;
			temp_ptr = custom_value;
			for (i = 0; (i < sizeof(param.custom_field)-1) && (temp_ptr[i] != '\0'); i++, idx++)
				param.custom_field[i] = temp_ptr[i];
		}
	#endif

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

		res = check_secure_boot();
		if(res == NONE_SECURE_BOOT) {
		    #ifdef FOR_ICE_LOAD
		    prints("*********** NONE_SECURE_BOOT ***********\n");
		    #endif
		    rtprintf("*********** NONE_SECURE_BOOT ***********\n");
		}
		else if(res == RTK_SECURE_BOOT) {
		    #ifdef FOR_ICE_LOAD
		    prints("*********** RTK_SECURE_BOOT ***********\n");
		    #endif
		    rtprintf("*********** RTK_SECURE_BOOT ***********\n");
		}

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
			//fsbl block is at block 0x0E
			NF_dump_flash(device, 0x03000000, 0, 0x440);
			//NF_dump_flash(device, 0x03002000, 0x180, 0x2);
			//NF_dump_flash(device, 0x03004000, 0x40180, 0x2);
			//NF_dump_flash(device, 0x03006000, 0x80180, 0x2);
			//NF_dump_flash(device, 0x03000000, 0, 0x197F);
			//NF_dump_flash(device, 0x03000000, 0, 0xa1e);
			//NF_dump_flash(device, 0x03000000, 0, 0x500);

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

program_main_copy_of_hwsetting:
	    /******************************
	     * start to program hwsetting
	     ******************************/
		copy_memory((unsigned char *)DATA_TMP_ADDR, hwsetting, hwsetting_size);

		// align to page size boundary
		temp = hwsetting_size % pagesize;

		if (temp)
			set_memory((unsigned char *)(DATA_TMP_ADDR + hwsetting_size), 0xff, pagesize - temp);

        // at most (backup_number + 1) copies of hwsetting in flash
	    supposed_block = current_block + (backup_number + 1);

	    // main copy of hwsetting data
	    #ifdef FOR_ICE_LOAD
		prints("\n");
		prints("Write Main Hwsetting in Block No. 0x");
		print_hex(current_block);
		prints(", Size: 0x");
		print_hex(hwsetting_size);
		prints(", Tag: 0x");
		print_hex(BLOCK_HWSETTING);
		prints("\n");
		#endif
			
	    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, hwsetting_size, BLOCK_HWSETTING, 0);

	    if (end_page == -1)
	    {
            #ifdef FOR_ICE_LOAD
            prints("main copy of hwsetting error!!\n");
            #endif
	    	rtprintf("main copy of hwsetting error!!\n");
	    	return -101;
	    }

	    // calculate next block start page
	    current_block = (end_page / pages_per_block) + 1;

	    // backup copy of hwsetting data
	    res = check_secure_boot();
	    for (i = 0, idx = 0; i < backup_number; i++)
	    {
program_backup_copy_of_hwsetting:
    	    // cannot write beyond supposed blocks
            if (current_block > supposed_block) {
                #ifdef FOR_ICE_LOAD
                prints("hwsetting full\n");
                #endif
            	rtprintf("hwsetting full");
            	break;
            }

            if ((res == NDS_SECURE_BOOT) || (res == DCAS_SECURE_BOOT)) {
            	// refill hwsetting into buffer
				copy_memory((unsigned char *)DATA_TMP_ADDR, hwsetting, hwsetting_size);
				// align to page size boundary
				temp = hwsetting_size % pagesize;
				if (temp) {
					set_memory((unsigned char *)(DATA_TMP_ADDR + hwsetting_size), 0xff, pagesize - temp);
				}
		    }

			#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Write Backup Hwsetting in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(hwsetting_size);
			prints(", Tag: 0x");
			print_hex(BLOCK_HWSETTING);
			prints("\n");
			#endif

		    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, hwsetting_size, BLOCK_HWSETTING, 0);

		    if (end_page == -1) {
                #ifdef FOR_ICE_LOAD
                prints("backup copy of hwsetting error!!\n");
                #endif
		    	rtprintf("backup copy of hwsetting error!!\n");
		    	return -102;
		    }

		    // calculate next block start page
		    current_block = (end_page / pages_per_block) + 1;
		}

#ifdef DUMP_NAND_FLASH
		//NF_dump_flash(device, gdst_data_addr, 0xc0, 0x40);
#endif
	    /******************************
	     * start to program bootcode
	     ******************************/
    	copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_img_base, programmed_img_size);
		if (programmed_img_sig_size>0)
    		copy_memory((unsigned char *)DATA_TMP_ADDR+programmed_img_size, programmed_img_sig_base, programmed_img_sig_size);

		// align to page size boundary
    	temp = (programmed_img_size+programmed_img_sig_size) % pagesize;
    	if (temp) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + programmed_img_size+programmed_img_sig_size), 0xff, pagesize - temp);
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
		print_hex(programmed_img_size+programmed_img_sig_size);
		prints(", Tag: 0x");
		print_hex(BLOCK_BOOTCODE);
		prints("\n");
		#endif

		end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_img_size+programmed_img_sig_size, BLOCK_BOOTCODE, 0);

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
			print_hex(programmed_img_size+programmed_img_sig_size);
			prints(", Tag: 0x");
			print_hex(BLOCK_BOOTCODE);
			prints("\n");
			#endif

		    end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, programmed_img_size+programmed_img_sig_size, BLOCK_BOOTCODE, 0);

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
		 * start to program FSBL
		 ******************************/
		if(programmed_fsbl_size > 0) {
		
            unsigned int program_len=0,rescue_blk=0;
            
            //1. copy fsbl to buffer
            program_len = programmed_fsbl_size;
            copy_memory(DATA_TMP_ADDR, programmed_fsbl_base, programmed_fsbl_size);
	
			// align to page size boundary
			temp = program_len % pagesize;
			if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
			}
			
			// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of fsbl in flash
			temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
			supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

			// main copy of fsbl
			#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Main Fsbl in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(program_len);
			prints(", Tag: 0x");
			print_hex(SECURE_FSBL_MAGIC_NUM);
			prints("\n");
			#endif
			
			end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, SECURE_FSBL_MAGIC_NUM, 0);

			if (end_page == -1) {
	    		#ifdef FOR_ICE_LOAD
					prints("main copy of fsbl error!!\n");
	    		#endif
					rtprintf("main copy of fsbl error!!\n");
				return -103;
			}
			// calculate next block start page
			current_block = (end_page / pages_per_block) + 1;

			// backup copy of fsbl
			for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
			{
				// cannot write beyond supposed blocks
				if (current_block > supposed_block) {
	        		#ifdef FOR_ICE_LOAD
						prints("fsbl full\n");
	        		#endif
						rtprintf("fsbl full");
					break;
				}

				#ifdef FOR_ICE_LOAD
				prints("\n");
				prints("Wrtie Backup Fsbl in Block No. 0x");
				print_hex(current_block);
				prints(", Size: 0x");
				print_hex(program_len);
				prints(", Tag: 0x");
				print_hex(SECURE_FSBL_MAGIC_NUM);
				prints("\n");
				#endif

				end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, SECURE_FSBL_MAGIC_NUM, 0);

				if (end_page == -1) {
	        		#ifdef FOR_ICE_LOAD
						prints("backup of fsbl error!!\n");
	        		#endif
						rtprintf("backup of fsbl error!!\n");
					return -104;
				}
				// calculate next block start page
				current_block = (end_page / pages_per_block) + 1;
			}
		}

		/******************************
	       * start to program FSBL OS
	       ******************************/
	    if (programmed_fsbl_os_size > 0) {
            unsigned int fsbl_blk=0,program_len=0;
            
            //1. copy fsbl_os to buffer
            program_len = programmed_fsbl_os_size;
            copy_memory(DATA_TMP_ADDR, programmed_fsbl_os_base, programmed_fsbl_os_size);
          
			// align to page size boundary
	    	temp = program_len % pagesize;
	    	if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
	    	}

			// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
	        //temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
            temp = FSBL_OS_MAX_SIZE / blocksize;
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
	            prints("main copy of fsbl os error!!\n");
	            #endif
	    		rtprintf("main copy of fsbl os error!!\n");
	    		return -103;
	    	}

			// calculate next block start page
			//current_block = (end_page / pages_per_block) + 1;
			current_block = current_block + (FSBL_OS_MAX_SIZE / blocksize);

			// backup copy of bootcode
			for (i = 0; i < NAND_BOOT_BACKUP_COUNT; i++)
			{
	    	    // cannot write beyond supposed blocks
	            if (current_block > supposed_block) {
	                #ifdef FOR_ICE_LOAD
	                prints("fsbl os full\n");
	                #endif
	            	rtprintf("fsbl os full");
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
	                prints("backup of fsbl os error!!\n");
	                #endif
			    	rtprintf("backup of fsbl os error!!\n");
			    	return -104;
			    }
			    // calculate next block start page
			    //current_block = (end_page / pages_per_block) + 1;
                current_block = current_block + (FSBL_OS_MAX_SIZE / blocksize);
			}
		}


        /******************************
	       * start to program BL31
	       ******************************/
	    if (programmed_bl31_size > 0) {
            unsigned int bl31_blk=0,program_len=0;
            
            //1. copy bl31 to buffer
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
	            prints("main copy of fsbl os error!!\n");
	            #endif
	    		rtprintf("main copy of fsbl os error!!\n");
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

#if defined(Config_Secure_Improve_TRUE)
		/******************************
	       * start to program Kpublic_fw & Kpublic_fw_signature
	       ******************************/
	    if(( programmed_Kpublic_fw_size > 0 )&&( programmed_Kpublic_fw_sig_size > 0 )) {
            unsigned int program_len=0;
            
            //1. copy Kpublic_fw+Kpublic_fw_sig to buffer
            program_len = programmed_Kpublic_fw_size+programmed_Kpublic_fw_sig_size;
            copy_memory(DATA_TMP_ADDR, programmed_Kpublic_fw_base, programmed_Kpublic_fw_size);
            copy_memory(DATA_TMP_ADDR+programmed_Kpublic_fw_size, programmed_Kpublic_fw_sig_base, programmed_Kpublic_fw_sig_size);

			// align to page size boundary
	    	temp = program_len % pagesize;
	    	if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
	    	}

			// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
	        temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
	    	supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

			// main copy of Kpublic_fw
	    	#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Main Kpublic_fw in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(program_len);
			prints(", Tag: 0x");
			print_hex(RSA_KEY_FW_MAGIC_NUM);
			prints("\n");
			#endif
			
	    	end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, RSA_KEY_FW_MAGIC_NUM, 0);

	    	if (end_page == -1) {
	            #ifdef FOR_ICE_LOAD
	            prints("main copy of Kpublic_fw error!!\n");
	            #endif
	    		rtprintf("main copy of Kpublic_fw error!!\n");
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
	                prints("Kpublic_fw full\n");
	                #endif
	            	rtprintf("Kpublic_fw full");
	            	break;
	            }

				#ifdef FOR_ICE_LOAD
				prints("\n");
				prints("Wrtie Main Kpublic_fw in Block No. 0x");
				print_hex(current_block);
				prints(", Size: 0x");
				print_hex(program_len);
				prints(", Tag: 0x");
				print_hex(RSA_KEY_FW_MAGIC_NUM);
				prints("\n");
				#endif

				end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, RSA_KEY_FW_MAGIC_NUM, 0);

			    if (end_page == -1) {
	                #ifdef FOR_ICE_LOAD
	                prints("backup of Kpublic_fw error!!\n");
	                #endif
			    	rtprintf("backup of Kpublic_fw error!!\n");
			    	return -104;
			    }
			    // calculate next block start page
			    current_block = (end_page / pages_per_block) + 1;
			}
		}

		/******************************
	       * start to program Kpublic_tee & Kpublic_tee_signature
	       ******************************/
	    if(( programmed_Kpublic_tee_size > 0 )&&( programmed_Kpublic_tee_sig_size > 0 )) {
            unsigned int program_len=0;
            
            //1. copy Kpublic_tee / Kpublic_tee_sig to buffer
            program_len = programmed_Kpublic_tee_size+programmed_Kpublic_tee_sig_size;
            copy_memory(DATA_TMP_ADDR, programmed_Kpublic_tee_base, programmed_Kpublic_tee_size);
            copy_memory(DATA_TMP_ADDR+programmed_Kpublic_tee_size, programmed_Kpublic_tee_sig_base, programmed_Kpublic_tee_sig_size);

			// align to page size boundary
	    	temp = program_len % pagesize;
	    	if (temp) {
				set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, pagesize - temp);
	    	}

		// at most (NAND_BOOT_BACKUP_COUNT + 1) copies of bootcode in flash
	        temp = program_len / blocksize + (program_len % blocksize ? 1 : 0);
	    	supposed_block = current_block + temp * (NAND_BOOT_BACKUP_COUNT + 1);

			// main copy of Kpublic_tee
	    	#ifdef FOR_ICE_LOAD
			prints("\n");
			prints("Wrtie Main Kpublic_tee in Block No. 0x");
			print_hex(current_block);
			prints(", Size: 0x");
			print_hex(program_len);
			prints(", Tag: 0x");
			print_hex(RSA_KEY_TEE_MAGIC_NUM);
			prints("\n");
			#endif
			
	    	end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, RSA_KEY_TEE_MAGIC_NUM, 0);

	    	if (end_page == -1) {
	            #ifdef FOR_ICE_LOAD
	            prints("main copy of Kpublic_tee error!!\n");
	            #endif
	    		rtprintf("main copy of Kpublic_tee error!!\n");
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
	                prints("Kpublic_tee full\n");
	                #endif
	            	rtprintf("Kpublic_tee full");
	            	break;
	            }

				#ifdef FOR_ICE_LOAD
				prints("\n");
				prints("Wrtie Backup Kpublic_tee in Block No. 0x");
				print_hex(current_block);
				prints(", Size: 0x");
				print_hex(program_len);
				prints(", Tag: 0x");
				print_hex(RSA_KEY_TEE_MAGIC_NUM);
				prints("\n");
				#endif

				end_page = (*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &current_block, program_len, RSA_KEY_TEE_MAGIC_NUM, 0);

			    if (end_page == -1) {
	                #ifdef FOR_ICE_LOAD
	                prints("backup of Kpublic_tee error!!\n");
	                #endif
			    	rtprintf("backup of Kpublic_tee error!!\n");
			    	return -104;
			    }
			    // calculate next block start page
			    current_block = (end_page / pages_per_block) + 1;
			}
		}
#endif
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

		// copy logo data to DDR
		if (logo_size > 0) {
			for (idx = 0; idx < logo_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo2 data to DDR
		if ( logo2_size > 0) {
			for (idx = 0; idx < logo2_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo2 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo3 data to DDR
		if ( logo3_size > 0) {
			for (idx = 0; idx < logo3_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo3 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo4 data to DDR
		if ( logo4_size > 0) {
			for (idx = 0; idx < logo4_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo4 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo5 data to DDR
		if ( logo5_size > 0) {
			for (idx = 0; idx < logo5_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo5 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo6 data to DDR
		if ( logo6_size > 0) {
			for (idx = 0; idx < logo6_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo6 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo7 data to DDR
		if ( logo7_size > 0) {
			for (idx = 0; idx < logo7_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo7 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

		// copy logo8 data to DDR
		if ( logo8_size > 0) {
			for (idx = 0; idx < logo8_size; idx+=4)
				REG32(buf_start + idx) = REG32(logo8 + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}
		// copy rescue data to DDR
		if ( linux_rescue_hasharray_size > 0) {
			for (idx = 0; idx < linux_rescue_hasharray_size; idx+=4)
				REG32(buf_start + idx) = REG32(linux_rescue_hasharray + idx);
			// shift data pointer of DDR
			buf_start +=idx;
		}

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


	    /******************************
	     * copy parameters in DDR to flash
	     ******************************/
	     if( save_nand_env ) {
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
	     * free SPI control to ACPU
	     ***********************************************************************/
	    #ifdef MAGALLAN_PRJ
	    rtprintf("\nRelease HW semaphore....");
	    *((volatile unsigned int *)0x000000E0) = 0;
		rtd_outl(0xB801A000, 0x0);
		rtprintf("Done\n");
	    #endif
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

		//erase first 832KB or 1MB
#if 1
	#ifdef CONFIG_DTB_IN_SPI_NOR
        #ifdef FOR_ICE_LOAD
        	prints("spi : erase 832KB from 0x");
        	print_hex(SPI_CODE_PART1);
        	prints("\n");
        #endif
		rtprintf("spi : erase 832KB from 0x%08x\n", SPI_CODE_PART1);
	    if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART1, 0x000D0000) !=0 ) {
			return -3;
		}
	#else
		#ifdef FOR_ICE_LOAD
        prints("spi : erase 0x");
        print_hex(((s_device_type *)device)->size);
        prints(" bytes from 0x");
        print_hex(SPI_CODE_PART1);
        prints("\n");
        #endif
        rtprintf("spi : erase 0x%x bytes from 0x%08x\n", ((s_device_type *)device)->size, SPI_CODE_PART1);
        if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART1, ((s_device_type *)device)->size) !=0 ) {
            return -3;
        }
	#endif
#else
		#ifdef FOR_ICE_LOAD
        	prints("spi : erase 1MB from 0x");
        	print_hex(SPI_CODE_PART1);
        	prints("\n");
        #endif
        rtprintf("spi : erase 1MB from 0x%08x\n", SPI_CODE_PART1);
	    if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART1, 0x00100000) !=0 ) {
			return -3;
		}
#endif
#if 0 // dump flash
		spi_switch_read_mode();
		spi_hexdump("spi data", SPI_CODE_PART1, 512);
#endif

#ifdef ROMCODE_ON_SPI
		//arm
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write arm romcode, start=0x");
        print_hex(spi_resetrom_addr);
        prints(", len=0x");
        print_hex(resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write arm romcode, start=0x%08x, len=0x%08x\n", spi_resetrom_addr, resetrom_size);
	    if ((*do_write)(device, resetrom, (unsigned int *)spi_resetrom_addr, resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
		//lexra
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write lexra romcode, start=0x");
        print_hex(spi_mips_resetrom_addr);
        prints(", len=0x");
        print_hex(mips_resetrom_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write lexra romcode, start=0x%08x, len=0x%08x\n", spi_mips_resetrom_addr, mips_resetrom_size);
	    if ((*do_write)(device, mips_resetrom, (unsigned int *)spi_mips_resetrom_addr, mips_resetrom_size, 0, 0)!= 0 ) {
	        return -4;
		}
#endif
		//for secure / non-secure
		//hwsetting
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write hw setting&signature, start=0x");
        print_hex(spi_hwsetting_addr);
        prints(", len=0x");
        print_hex(hwsetting_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write hw setting&signature, start=0x%08x, len=0x%08x\n", spi_hwsetting_addr, hwsetting_size);
	    if ((*do_write)(device, hwsetting, (unsigned int *)spi_hwsetting_addr, hwsetting_size, 0, 0)!= 0 ) {
	        return -5;
	    }
		//bootcode
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write bootcode, start=0x");
        print_hex(spi_bootcode_addr);
        prints(", len=0x");
        print_hex(programmed_img_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write bootcode, start=0x%08x, len=0x%08x\n", spi_bootcode_addr, programmed_img_size);
	    if ((*do_write)(device, programmed_img_base, (unsigned int *)spi_bootcode_addr, programmed_img_size, 0, 0)!= 0 ) {
	        return -6;
	    }
		//bootcode signature
	    if (programmed_img_sig_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write bootcode signature, start=0x");
            print_hex(spi_bootcode_sig_addr);
            prints(", len=0x");
            print_hex(programmed_img_sig_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write bootcode signature, start=0x%08x, len=0x%08x\n", spi_bootcode_sig_addr, programmed_img_sig_size);
	    	if ((*do_write)(device, programmed_img_sig_base, (unsigned int *)spi_bootcode_sig_addr, programmed_img_sig_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
#if defined(Config_FSBL_TRUE)        
        //fsbl
	    if (programmed_fsbl_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write fsbl, start=0x");
            print_hex(spi_fsbl_addr);
            prints(", len=0x");
            print_hex(programmed_fsbl_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write fsbl, start=0x%08x, len=0x%08x\n", spi_fsbl_addr, programmed_fsbl_size);
	    	if ((*do_write)(device, programmed_fsbl_base, (unsigned int *)spi_fsbl_addr, programmed_fsbl_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    } 
#endif
#if defined(Config_FSBL_OS_TRUE)
        //fsbl os
	    if (programmed_fsbl_os_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write fsbl_os, start=0x");
            print_hex(spi_fsbl_os_addr);
            prints(", len=0x");
            print_hex(programmed_fsbl_os_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write fsbl_os, start=0x%08x, len=0x%08x\n", spi_fsbl_os_addr, programmed_fsbl_os_size);
	    	if ((*do_write)(device, programmed_fsbl_os_base, (unsigned int *)spi_fsbl_os_addr, programmed_fsbl_os_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
#endif
#if defined(Config_BL31_TRUE)
        //bl31
	    if (programmed_bl31_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write bl31, start=0x");
            print_hex(spi_bl31_addr);
            prints(", len=0x");
            print_hex(programmed_bl31_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write bl31, start=0x%08x, len=0x%08x\n", spi_bl31_addr, programmed_bl31_size);
	    	if ((*do_write)(device, programmed_bl31_base, (unsigned int *)spi_bl31_addr, programmed_bl31_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
#endif
#if defined(Config_Secure_Improve_TRUE)
        //Kpublic_fw
	    if (programmed_Kpublic_fw_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write Kpublic_fw, start=0x");
            print_hex(spi_Kpublic_fw_addr);
            prints(", len=0x");
            print_hex(programmed_Kpublic_fw_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write Kpublic_fw, start=0x%08x, len=0x%08x\n", spi_Kpublic_fw_addr, programmed_Kpublic_fw_size);
	    	if ((*do_write)(device, programmed_Kpublic_fw_base, (unsigned int *)spi_Kpublic_fw_addr, programmed_Kpublic_fw_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
        //Kpublic_fw sig
	    if (programmed_Kpublic_fw_sig_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write Kpublic_fw sig, start=0x");
            print_hex(spi_Kpublic_fw_sig_addr);
            prints(", len=0x");
            print_hex(programmed_Kpublic_fw_sig_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write Kpublic_fw sig, start=0x%08x, len=0x%08x\n", spi_Kpublic_fw_sig_addr, programmed_Kpublic_fw_sig_size);
	    	if ((*do_write)(device, programmed_Kpublic_fw_sig_base, (unsigned int *)spi_Kpublic_fw_sig_addr, programmed_Kpublic_fw_sig_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
        //Kpublic_tee
	    if (programmed_Kpublic_tee_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write Kpublic_tee, start=0x");
            print_hex(spi_Kpublic_tee_addr);
            prints(", len=0x");
            print_hex(programmed_Kpublic_tee_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write Kpublic_tee, start=0x%08x, len=0x%08x\n", spi_Kpublic_tee_addr, programmed_Kpublic_tee_size);
	    	if ((*do_write)(device, programmed_Kpublic_tee_base, (unsigned int *)spi_Kpublic_tee_addr, programmed_Kpublic_tee_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
        //Kpublic_tee sig
	    if (programmed_Kpublic_tee_sig_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write Kpublic_tee sig, start=0x");
            print_hex(spi_Kpublic_tee_sig_addr);
            prints(", len=0x");
            print_hex(programmed_Kpublic_tee_sig_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write Kpublic_tee sig, start=0x%08x, len=0x%08x\n", spi_Kpublic_tee_sig_addr, programmed_Kpublic_tee_sig_size);
	    	if ((*do_write)(device, programmed_Kpublic_tee_sig_base, (unsigned int *)spi_Kpublic_tee_sig_addr, programmed_Kpublic_tee_sig_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
#endif
        //rescue kernel 
#if 0
        #ifdef FOR_ICE_LOAD
        prints("\nspi : write rescue, start=0x");
        print_hex(spi_rescue_addr);
        prints(", len=0x");
        print_hex(programmed_linux_rescue_img_size);
        prints("\n");
        #endif
	    rtprintf("\nspi : write rescue, start=0x%08x, len=0x%08x\n", spi_rescue_addr, programmed_linux_rescue_img_size);
	    if ((*do_write)(device, programmed_linux_rescue_img_base, (unsigned int *)spi_rescue_addr, programmed_linux_rescue_img_size, 0, 0)!= 0 ) {
	        return -6;
	    }
		//rescue signature
	    if (programmed_linux_rescue_sig_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write rescue signature, start=0x");
            print_hex(spi_rescue_addr);
            prints(", len=0x");
            print_hex(programmed_linux_rescue_sig_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write rescue signature, start=0x%08x, len=0x%08x\n", spi_rescue_addr, programmed_linux_rescue_sig_size);
	    	if ((*do_write)(device, programmed_linux_rescue_sig_base, (unsigned int *)spi_rescue_sig_addr, programmed_linux_rescue_sig_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
#endif 
        //rsa_pub
	    if (programmed_rsa_pub_size > 0)
	    {
            #ifdef FOR_ICE_LOAD
            prints("\nspi : write rsa_pub, start=0x");
            print_hex(spi_rsa_pub_addr);
            prints(", len=0x");
            print_hex(programmed_rsa_pub_size);
            prints("\n");
            #endif
	    	rtprintf("\nspi : write rsa_pub, start=0x%08x, len=0x%08x\n", spi_rsa_pub_addr, programmed_rsa_pub_size);
	    	if ((*do_write)(device, programmed_rsa_pub_base, (unsigned int *)spi_rsa_pub_addr, programmed_rsa_pub_size, 0, 0)!= 0 ) {
	        	return -6;
	    	}
	    }
	    /***********************************************************************
	        * prepare for hwsetting signature or DCAS key1
	        ***********************************************************************/
#ifdef MAGALLEN_PRJ
	    res = check_secure_boot();
	    if( (res == NDS_SECURE_BOOT) || (res == DCAS_SECURE_BOOT) ) {
	    	if (res == NDS_SECURE_BOOT) {
	    		rtprintf("\nspi : write NDS key signature, start=0x%08x, len=0x%08x\n", spi_key_sig_addr, hwsetting_sig_size);
	    		if ((*do_write)(device, hwsetting_sig_image, (unsigned int *)spi_key_sig_addr, hwsetting_sig_size, 0, 0)!= 0 ) {
	        		return -15;
	        	}
	    	}
	    	else { // res == DCAS_SECURE_BOOT
	    		rtprintf("\nspi : write DCAS key signature, start=0x%08x, len=0x%08x\n", spi_key_sig_addr, dcas_key_sig_size);
	    		if ((*do_write)(device, dcas_key_sig_image, (unsigned int *)spi_key_sig_addr, dcas_key_sig_size, 0, 0)!= 0 ) {
	        		return -15;
	        	}
	    	}
	    }

#if 0	    
	    if( bootcode2_boot_programmed_img_size || bootcode3_boot_programmed_img_size ) {
	    	rtprintf("\nspi : erase 1MB from 0x%08x\n", SPI_CODE_PART2);
		    if ((*do_erase)(device, (unsigned int *)SPI_CODE_PART2, 0x00100000) !=0 ) {
				return -3;
			}
	    }
#endif
#endif
	    if( bootcode2_boot_programmed_img_size ) {
	    	// write bootcode2		
			#ifdef FOR_ICE_LOAD
        		prints("\nspi : write bootcode2, start=0x");
        		print_hex(spi_bootcode_addr2);
        		prints(", len=0x");
        		print_hex(bootcode2_boot_programmed_img_size);
        		prints(", src=0x");
        		print_hex(bootcode2_boot_programmed_img_base);
        		prints("\n");
        	#endif
			rtprintf("\nspi : write bootcode2, start=0x%08x, len=0x%08x\n", spi_bootcode_addr2, bootcode2_boot_programmed_img_size);
#ifdef CONFIG_DTB_IN_SPI_NOR
		    if( bootcode2_boot_programmed_img_size > (320<<10) ) {
				prints("\nspi : bootcode2 size is too large, bootcode2 not program");
				return -5;
	    	}
#else
			if( bootcode2_boot_programmed_img_size > (384<<10) ) {
				prints("\nspi : bootcode2 size is too large, bootcode2 not program");
				return -5;
	    	}
#endif
			if ((*do_write)(device, bootcode2_boot_programmed_img_base, (unsigned int *)spi_bootcode_addr2, bootcode2_boot_programmed_img_size, 0, 0)!= 0 ) {
		        return -6;
		    }
   		}
	    
	    // write parameter in bootcode1
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
		unsigned int block_no;
        unsigned int block_no_64;
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
		set_emmc_freq();
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
		res = check_secure_boot();
        if (res == NONE_SECURE_BOOT)
        {
            #ifdef FOR_ICE_LOAD
			prints("**********for NON_SECURE_BOOT\n");
            #endif
            rtprintf("**********for NON_SECURE_BOOT\n");
	    }
        else if (res == RTK_SECURE_BOOT)
        {
            #ifdef FOR_ICE_LOAD
			prints("**********for RTK_SECURE_BOOT\n");
            #endif
            rtprintf("**********for RTK_SECURE_BOOT\n");
        }       

		/***********************************************************************
		 * start to program hwsetting
		 ***********************************************************************/
        #ifdef FOR_ICE_LOAD
		prints("*******************************************\n");
        #endif
    	rtprintf("*******************************************\n");
    	copy_memory((unsigned char *)DATA_TMP_ADDR, hwsetting, hwsetting_size);
		// align to block size boundary
		temp = hwsetting_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + hwsetting_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}

		// hwsetting data
		//block_no += align_to_boundary(0x800, EMMC_BLOCK_SIZE);
		block_no = EMMC_HW_SETTING_BLK;
#ifndef BOOT1_RESCUE		
        #ifdef FOR_ICE_LOAD
		prints("hwsetting: block 0x");
        print_hex(block_no);
		prints(", size 0x");
        print_hex(hwsetting_size);
        prints("\n");
        #endif
		rtprintf("hwsetting: block 0x%x, size 0x%x\n", block_no, hwsetting_size);

		// overwrite hw setting ( clear old setting )
		#if 0
		res = do_hide_hwsetting( device, NULL, &block_no, 512, 0xFEFFFFFF, 0);
        #ifdef FOR_ICE_LOAD
		prints("hwsetting: res=");
        print_hex(res);
        prints("\n");
        #endif
		rtprintf("hwsetting: res=%d\n", res);
        #endif
  
		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, hwsetting_size, 0, 0)) {
            #ifdef FOR_ICE_LOAD
    		prints("do_write falied\n");
            #endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
            #ifdef FOR_ICE_LOAD
    		prints("read hwsetting back: block 0x");
            print_hex(block_no);
    		prints(", size 0x");
            print_hex(hwsetting_size);
            prints("\n");
            #endif
			rtprintf("read hwsetting back: block 0x%x, size 0x%x\n", block_no, hwsetting_size);
			if ((*do_read)(device, &block_no, read_buf, hwsetting_size, 0)) {
                #ifdef FOR_ICE_LOAD
        		prints("do_read check falied\n");
                #endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, hwsetting_size)) {
                #ifdef FOR_ICE_LOAD
        		prints("verify hwsetting falied\n");
                #endif
				rtprintf("verify hwsetting falied\n");
				return -6;
			}
            #ifdef CR_MEMORY_DUMP
            copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(hwsetting_size, EMMC_BLOCK_SIZE));
            emmc_dump_ptr += align_to_boundary_length(hwsetting_size, EMMC_BLOCK_SIZE);
            #endif
		}

/* =======================================
 *        BOOT1 partition for RESCUE
 * =========================================
 */
#else 
		#ifdef FOR_ICE_LOAD
		prints("hwsetting: block 0x");
        print_hex(boot_part_dest_block);
		prints(", size 0x");
        print_hex(hwsetting_size);
        prints("\n");
        #endif
		//write from boot1 block 0
		if (BootPartOps.write( device, (unsigned char *)DATA_TMP_ADDR, boot_part_dest_block, hwsetting_size)) {
            #ifdef FOR_ICE_LOAD
    		prints("do_write boot1 hwsetting falied\n");
            #endif
			rtprintf("do_write boot1 hwsetting falied\n");
			return -4;
		}

		if(verify_after_write){
			if( EXIT_FAILURE == BootPartOps.verify_data(device,(unsigned char *)DATA_TMP_ADDR,boot_part_dest_block,hwsetting_size)){
				prints("verify boot1 hwsetting fail\n");
				return -6;
			}else{
				prints("verify  boot1 hwsetting   OK\n");
			}
		}

		boot_part_dest_block += align_to_boundary(hwsetting_size, EMMC_BLOCK_SIZE);

#endif
/* =================================================== */	

		

		/***********************************************************************
		 * start to program bootcode
		 ***********************************************************************/
        #ifdef FOR_ICE_LOAD
        prints("*******************************************\n");
        #endif
	    rtprintf("*******************************************\n");
	    copy_memory((unsigned char *)DATA_TMP_ADDR, programmed_img_base, programmed_img_size);
	    if (programmed_img_sig_size > 0)
		{
			copy_memory((unsigned char *)DATA_TMP_ADDR+programmed_img_size, programmed_img_sig_base, programmed_img_sig_size);
			programmed_img_size += programmed_img_sig_size;
		}
		// align to block size boundary
		temp = programmed_img_size % EMMC_BLOCK_SIZE;
		if( temp ) {
			set_memory((unsigned char *)(DATA_TMP_ADDR + programmed_img_size), 0xFF, EMMC_BLOCK_SIZE - temp);
		}

		// bootcode
		block_no += align_to_boundary(hwsetting_size, EMMC_BLOCK_SIZE);  //for uda
#ifndef BOOT1_RESCUE 	
        #ifdef FOR_ICE_LOAD
    	prints("write bootcode: block 0x");
        print_hex(block_no);
    	prints(", size 0x");
        print_hex(programmed_img_size);
        prints("\n");
        #endif
		rtprintf("write bootcode: block 0x%x, size 0x%x\n", block_no, programmed_img_size);

		if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, programmed_img_size, 0, 0)) {
            #ifdef FOR_ICE_LOAD
        	prints("do_write falied\n");
            #endif
			rtprintf("do_write falied\n");
			return -4;
		}

		if (verify_after_write) {
            #ifdef FOR_ICE_LOAD
        	prints("read back bootcode: block 0x");
            print_hex(block_no);
        	prints(", size 0x");
            print_hex(programmed_img_size);
            prints("\n");
            #endif
			rtprintf("read back bootcode: block 0x%x, size 0x%x\n", block_no, programmed_img_size);
			if ((*do_read)(device, &block_no, read_buf, programmed_img_size, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_read check falied\n");
                #endif
				rtprintf("do_read check falied\n");
				return -5;
			}
			if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, programmed_img_size)) {
                #ifdef FOR_ICE_LOAD
            	prints("verify bootcode falied\n");
                #endif
				rtprintf("verify bootcode falied\n");
				return -6;
			}
            #ifdef CR_MEMORY_DUMP
            copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(programmed_img_size, EMMC_BLOCK_SIZE));
            emmc_dump_ptr += align_to_boundary_length(programmed_img_size, EMMC_BLOCK_SIZE);
            #endif
           
		}

/* =======================================
 *		  BOOT1 RESCUE
 * =========================================
 */
#else
	#ifdef FOR_ICE_LOAD
	prints("write bootcode: block 0x");
    print_hex(boot_part_dest_block);
	prints(", size 0x");
    print_hex(programmed_img_size);
    prints("\n");
    #endif
		
	if(EXIT_FAILURE == BootPartOps.write(device,(unsigned char *)DATA_TMP_ADDR,boot_part_dest_block,programmed_img_size)){
		prints("do_write failed\n");
		return -4;
	}
	if(verify_after_write){
		if( EXIT_FAILURE == BootPartOps.verify_data(device,(unsigned char *)DATA_TMP_ADDR,boot_part_dest_block,programmed_img_size)){
			prints("verify BOOT1 bootcode  fail\n");
			return -6;
		}else{
			prints("verify BOOT1 bootcode  OK\n");
		}
	}
	boot_part_dest_block += align_to_boundary(programmed_img_size, EMMC_BLOCK_SIZE);
#endif
/* ========================================= */

		/***********************************************************************
		 * start to fsbl
		 ***********************************************************************/
		if (programmed_fsbl_size != 0) {            
            //1. copy fsbl to buffer
            unsigned int program_len = programmed_fsbl_size;
            copy_memory(DATA_TMP_ADDR, programmed_fsbl_base, programmed_fsbl_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
			rtprintf("*******************************************\n");

			block_no += align_to_boundary(programmed_img_size, EMMC_BLOCK_SIZE);	
#ifndef BOOT1_RESCUE			
            #ifdef FOR_ICE_LOAD
        	prints("write fsbl: block 0x");
            print_hex(block_no);
        	prints(", fsbl size 0x");
            print_hex(programmed_fsbl_size);
            prints("\n");
            #endif
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(fsbl): block 0x");
                print_hex(block_no);
            	prints(", fsbl size 0x");
                print_hex(programmed_fsbl_size);
                prints("\n");
                #endif
				rtprintf("read back data(fsbl): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify fsbl data falied\n");
                    #endif
					rtprintf("verify fsbl data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
                param.fsbl_addr = block_no;
			}
/* =======================================
 *		  BOOT1 RESCUE
 * =========================================
 */
#else
			#ifdef FOR_ICE_LOAD
        	prints("write fsbl: block 0x");
            print_hex(boot_part_dest_block);
        	prints(", fsbl size 0x");
            print_hex(programmed_fsbl_size);
            prints("\n");
            #endif
			
			if(EXIT_FAILURE == BootPartOps.write(device,(unsigned char *)DATA_TMP_ADDR,boot_part_dest_block,program_len)){
				prints("do_write BOOT1 fsbl failed\n");
				return -4;
			}
			if(verify_after_write){
				if( EXIT_FAILURE == BootPartOps.verify_data(device,(unsigned char *)DATA_TMP_ADDR,boot_part_dest_block,program_len)){
					prints("verify BOOT1 fsbl fail\n");
					return -6;
				}else{
					prints("verify BOOT1 fsbl OK\n");
				}
			}
#ifdef FOR_ICE_LOAD
		    prints("Finish\n");
#endif
		    while(1);
#endif			
		} 
		
		/***********************************************************************
		 * start to fsbl_os
		 ***********************************************************************/
		if(programmed_fsbl_os_size != 0) {
            unsigned int fsbl_blk=0, fsbl_len=0, program_len=0;
            
            //1. copy fsbl_os to buffer
            fsbl_len = programmed_fsbl_size;
            program_len = programmed_fsbl_os_size;
            copy_memory(DATA_TMP_ADDR, programmed_fsbl_os_base, programmed_fsbl_os_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
			rtprintf("*******************************************\n");
            //get fsbl_os write block no. behind fsbl
	        block_no += align_to_boundary(fsbl_len, EMMC_BLOCK_SIZE);
            param.fsbl_os_addr = block_no;
            #ifdef FOR_ICE_LOAD
        	prints("write fsbl_os: block 0x");
            print_hex(block_no);
        	prints(", fsbl_os size 0x");
            print_hex(programmed_fsbl_os_size);
            prints("\n");
            #endif
			rtprintf("write fsbl_os : block 0x%x, size 0x%x\n", block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(fsbl_os): block 0x");
                print_hex(block_no);
            	prints(", fsbl_os size 0x");
                print_hex(programmed_fsbl_os_size);
                prints("\n");
                #endif
				rtprintf("read back data(fsbl_os): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify fsbl_os data falied\n");
                    #endif
					rtprintf("verify fsbl_os data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
			}


/* ============================================== */
			
}   

        /***********************************************************************
		 * start to bl31
		 ***********************************************************************/
		if(programmed_bl31_size != 0) {
            unsigned int fsbl_os_blk=0, fsbl_os_len=0, program_len=0;
            
            //1. copy bl31 to buffer
            fsbl_os_len = programmed_fsbl_os_size;
            program_len = programmed_bl31_size;
            copy_memory(DATA_TMP_ADDR, programmed_bl31_base, programmed_bl31_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
			rtprintf("*******************************************\n");
			
			block_no += align_to_boundary(fsbl_os_len, EMMC_BLOCK_SIZE);
			
			param.bl31_addr = block_no;
            #ifdef FOR_ICE_LOAD
        	prints("write bl31: block 0x");
            print_hex(block_no);
        	prints(", bl31 size 0x");
            print_hex(programmed_bl31_size);
            prints("\n");
            #endif
			rtprintf("write bl31 : block 0x%x, size 0x%x\n", block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(bl31): block 0x");
                print_hex(block_no);
            	prints(", bl31 size 0x");
                print_hex(programmed_bl31_size);
                prints("\n");
                #endif
				rtprintf("read back data(bl31): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify bl31 data falied\n");
                    #endif
					rtprintf("verify bl31 data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
			}


/* ===================================  */

} 

#if defined(Config_Secure_Improve_TRUE)
		/***********************************************************************
		 * start to Kpublic_fw / Kpublic_fw_sig data
		 ***********************************************************************/
		if(( programmed_Kpublic_fw_size != 0 )&&( programmed_Kpublic_fw_sig_size != 0 )) {
            unsigned int bl31_len=0, program_len=0;
            
            //1. copy Kpublic_fw + Kpublic_fw_sig to buffer
            bl31_len = programmed_bl31_size+programmed_bl31_sig_size;
            program_len = programmed_Kpublic_fw_size+programmed_Kpublic_fw_sig_size;
            copy_memory(DATA_TMP_ADDR, programmed_Kpublic_fw_base, programmed_Kpublic_fw_size);
            copy_memory(DATA_TMP_ADDR+programmed_Kpublic_fw_size, programmed_Kpublic_fw_sig_base, programmed_Kpublic_fw_sig_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
			rtprintf("*******************************************\n");
            //get Kpublic_fw write block no. behind bl31
	        block_no += align_to_boundary(bl31_len, EMMC_BLOCK_SIZE);
            param.Kpublic_fw_addr = block_no;
            #ifdef FOR_ICE_LOAD
        	prints("write Kpublic_fw,Kpublic_fw_sig: block 0x");
            print_hex(block_no);
        	prints(", Kpublic_fw size 0x");
            print_hex(programmed_Kpublic_fw_size);
            prints(", Kpublic_fw_sig_size 0x");
            print_hex(programmed_Kpublic_fw_sig_size);
            prints("\n");
            #endif
			rtprintf("write Kpublic_fw/Kpublic_fw_sig : block 0x%x, size 0x%x\n", block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(Kpublic_fw/Kpublic_fw_sig): block 0x");
                print_hex(block_no);
            	prints(", Kpublic_fw size 0x");
                print_hex(programmed_Kpublic_fw_size);
                prints(", Kpublic_fw_sig_size 0x");
                print_hex(programmed_Kpublic_fw_sig_size);
                prints("\n");
                #endif
				rtprintf("read back data(Kpublic_fw/Kpublic_fw_sig): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify Kpublic_fw/Kpublic_fw_sig data falied\n");
                    #endif
					rtprintf("verify Kpublic_fw/Kpublic_fw_sig data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
			}
		}   
		/***********************************************************************
		 * start to Kpublic_tee / Kpublic_tee_sig data
		 ***********************************************************************/
		if(( programmed_Kpublic_tee_size != 0 )&&( programmed_Kpublic_tee_sig_size != 0 )) {
            unsigned int Kpublic_fw_len=0, program_len=0;
            
            //1. copy Kpublic_tee + Kpublic_tee_sig to buffer
            Kpublic_fw_len = programmed_Kpublic_fw_size+programmed_Kpublic_fw_sig_size;
            program_len = programmed_Kpublic_tee_size+programmed_Kpublic_tee_sig_size;
            copy_memory(DATA_TMP_ADDR, programmed_Kpublic_tee_base, programmed_Kpublic_tee_size);
            copy_memory(DATA_TMP_ADDR+programmed_Kpublic_tee_size, programmed_Kpublic_tee_sig_base, programmed_Kpublic_tee_sig_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
			rtprintf("*******************************************\n");
            //get Kpublic_tee write block no. behind rescue kernel
	    	block_no += align_to_boundary(Kpublic_fw_len, EMMC_BLOCK_SIZE);
            param.Kpublic_tee_addr = block_no;
            #ifdef FOR_ICE_LOAD
        	prints("write Kpublic_tee,Kpublic_tee_sig: block 0x");
            print_hex(block_no);
        	prints(", Kpublic_tee size 0x");
            print_hex(programmed_Kpublic_tee_size);
            prints(", Kpublic_tee_sig_size 0x");
            print_hex(programmed_Kpublic_tee_sig_size);
            prints("\n");
            #endif
			rtprintf("write Kpublic_tee/Kpublic_tee_sig : block 0x%x, size 0x%x\n", block_no, program_len);
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -4;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(Kpublic_tee/Kpublic_tee_sig): block 0x");
                print_hex(block_no);
            	prints(", Kpublic_tee size 0x");
                print_hex(programmed_Kpublic_tee_size);
                prints(", Kpublic_tee_sig_size 0x");
                print_hex(programmed_Kpublic_tee_sig_size);
                prints("\n");
                #endif
				rtprintf("read back data(Kpublic_tee/Kpublic_tee_sig): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify Kpublic_tee/Kpublic_tee_sig data falied\n");
                    #endif
					rtprintf("verify Kpublic_tee/Kpublic_tee_sig data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
			}
			
		}
#endif

#if defined(Config_FSBL_VM_TRUE)
		/***********************************************************************
		 * start to fsb_vml / fsbl_vm_sig data
		 ***********************************************************************/	
		if(programmed_fsbl_vm_size != 0) {            
            //1. copy fsbl_vm + fsbl_vm_sig to buffer
            unsigned int program_len = programmed_fsbl_vm_size;
            copy_memory(DATA_TMP_ADDR, programmed_fsbl_vm_base, programmed_fsbl_vm_size);
            
    		// align to page size boundary
    		temp = program_len % EMMC_BLOCK_SIZE;
    		if( temp ) {
    			set_memory((unsigned char *)(DATA_TMP_ADDR + program_len), 0xff, EMMC_BLOCK_SIZE - temp);
    		}
            //2. program
            #ifdef FOR_ICE_LOAD
            prints("*******************************************\n");
            #endif
#if defined(Config_Secure_Improve_TRUE)
			unsigned int Kpublic_tee_len = programmed_Kpublic_tee_size+programmed_Kpublic_tee_sig_size;
			block_no += align_to_boundary(Kpublic_tee_len, EMMC_BLOCK_SIZE);
#else
			unsigned int bl31_len = programmed_bl31_size;
			block_no += align_to_boundary(bl31_len, EMMC_BLOCK_SIZE);
#endif
			#ifdef FOR_ICE_LOAD
        	prints("write fsbl_vm: block 0x");
            print_hex(block_no);
        	prints(", fsbl_vm size 0x");
            print_hex(programmed_fsbl_size);
            prints("\n");
            #endif
			if ((*do_write)( device, (unsigned char *)DATA_TMP_ADDR, &block_no, program_len, 0, 0)) {
                #ifdef FOR_ICE_LOAD
            	prints("do_write falied\n");
                #endif
				rtprintf("do_write falied\n");
				return -6;
			}

			if (verify_after_write) {
                #ifdef FOR_ICE_LOAD
            	prints("read back data(fsbl_vm): block 0x");
                print_hex(block_no);
            	prints(", fsbl_vm size 0x");
                print_hex(programmed_fsbl_vm_size);
                prints("\n");
                #endif
				rtprintf("read back data(fsbl_vm): block 0x%x, size 0x%x\n", block_no, program_len);
				if ((*do_read)(device, &block_no, read_buf, program_len, 0)) {
                    #ifdef FOR_ICE_LOAD
                	prints("do_read check falied\n");
                    #endif
					rtprintf("do_read check falied\n");
					return -5;
				}
				if (compare_memory((unsigned char *)DATA_TMP_ADDR, read_buf, program_len)) {
                    #ifdef FOR_ICE_LOAD
                	prints("verify fsbl_vm data falied\n");
                    #endif
					rtprintf("verify fsbl_vm data falied\n");
					return -6;
				}
                #ifdef CR_MEMORY_DUMP
                copy_memory((unsigned char *)emmc_dump_addr+emmc_dump_ptr, read_buf, align_to_boundary_length(program_len, EMMC_BLOCK_SIZE));
                emmc_dump_ptr += align_to_boundary_length(program_len, EMMC_BLOCK_SIZE);
                #endif
                param.fsbl_vm_addr = block_no;
			}
		}
#endif
	}

    //dump 'Finish' string to RS232
    #ifdef FOR_ICE_LOAD
    prints("Finish\n");
    #endif
    #ifdef CR_MEMORY_DUMP
    prints("Total dump 0x");
    print_hex(emmc_dump_ptr);
    prints(" at 0x");
    print_hex(emmc_dump_addr);
    prints("\n");

    while(1);
    #endif
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
