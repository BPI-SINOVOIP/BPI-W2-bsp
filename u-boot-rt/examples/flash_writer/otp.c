
/************************************************************************
 *
 *  otp.c
 *
 *  OTP routine for RTD299X internal ROM
 *
 *
 * Copyright (c) 2012 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/
#define __OTP_C__

/************************************************************************
 *  Include files
 ************************************************************************/
#include <sysdefs.h>
#include "otp.h"
#include "dvrboot_inc/mis_reg.h"
#include "dvrboot_inc/sys_reg.h"
#include "dvrboot_inc/util.h"
#include "dvrboot_inc/io.h"
#include "rtkemmc.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define OTP_REG_BASE    	 	0x18017000
#define OTP_BIT_SECUREBOOT		3494

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Public function prototypes
 ************************************************************************/

/************************************************************************
 *  Static function prototypes
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int get_boot_flash_type_from_gpio(void)
{
	int boottype=0;
	unsigned int gpiomux_val=0x00ff0300;
	unsigned int gpiodir_val=0x00407800;
	unsigned int nand_type;
	//extern nandecctype_t sys_nand_type;
	
	//1195
	//1. set pin mux for gpio 22/11/12/13/14
	REG32(SYS_muxpad0) &= ~gpiomux_val;
	//2. set gpio 22/11/12/13/14, dir=input
	REG32(MIS_GP0DIR) &= ~gpiodir_val;
	//3. get boot flash type
	if (REG32(MIS_GP0DATI)&(0x1<<22))
	{
		boottype = 0; //spi flashs
	}
	else if (((REG32(MIS_GP0DATI)&(0xf<<11))==0xf) && !(REG32(MIS_GP0DATI)&(0x1<<22)))
	{
		boottype = 1; //eMMC
	}
	else
	{
		boottype = 2; //nandflash	
	}

	switch(boottype) {
		case 0:
			return FLASH_TYPE_SPI;
		case 1:
			return FLASH_TYPE_EMMC;
		case 2:
			return FLASH_TYPE_NAND;
		default:	// should be impossible...
			return FLASH_TYPE_SPI;
	}

}


unsigned int OTP_JUDGE_BIT(UINT32 offset)
{
    UINT32 div_n=0, rem_n=0;
    UINT32 align_n=0, align_rem_n=0, real_n=0;

    rem_n = offset%8;
    div_n = offset/8;

    align_n = div_n & ~0x3;
    align_rem_n = div_n & 0x3;

    real_n = REG32(OTP_REG_BASE + align_n);
    return(((real_n >>(align_rem_n*8)) >> rem_n)&1);
}

unsigned char get_secure_type_from_efuse(void)
{
    if (OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT))
    {
        return RTK_SECURE_BOOT;
    }

	return NONE_SECURE_BOOT;
}

unsigned char check_secure_boot(void)
{
	#if defined(Config_Secure_Key_TRUE)
        //TODO : for real case
		#if 1
			return NONE_SECURE_BOOT;
		#else
			return get_secure_type_from_efuse();
		#endif
	#else
		return NONE_SECURE_BOOT;
	#endif		
}

const char * get_secure_type_name(void)
{
	unsigned char type;

	type = check_secure_boot();

	switch (type) {
		case NONE_SECURE_BOOT: // 0
			return "NONE_SECURE_BOOT";
		case NDS_SECURE_BOOT:  // 1
			return "NDS_SECURE_BOOT";
		case RTK_SECURE_BOOT:  // 2
			return "RTK_SECURE_BOOT";
		case DCAS_SECURE_BOOT: // 3
			return "DCAS_SECURE_BOOT";
		default:
			return "unknown";
	}

}
