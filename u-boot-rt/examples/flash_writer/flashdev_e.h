#ifndef __FLASHDEV_E_H__
#define __FLASHDEV_E_H__

#include "rtkemmc.h"

/************************************************************************
 * 	EMMC data layout
 ************************************************************************/
//#define EMMC_EXT_PARAM_BLK_ADDR	(EMMC_EXT_PARAM_ADDR>>9)		
#define EMMC_BLOCK_SIZE				(512UL)
#define EMMC_BLOCK_SIZE_SHIFT		(9)
#define EMMC_EXT_PARAM_ADDR			0x0000F800
#define EMMC_EXT_PARAM_BLK_ADDR		(EMMC_EXT_PARAM_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 0x7C
#define EMMC_EXT_PARAM_BYTE_SIZE	0x00000800	
#define	EMMC_KEY_SIG_ADDR			0x00020000
#define EMMC_KEY_SIG_BLK_ADDR		(EMMC_KEY_SIG_ADDR>>EMMC_BLOCK_SIZE_SHIFT)		// 0x100
#define EMMC_KEY_SIG_BYTE_SIZE		0x00000800
#define EMMC_HW_SETTING_ADDR        (EMMC_KEY_SIG_ADDR)
#define EMMC_HW_SETTING_BLK			(EMMC_HW_SETTING_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 0x104
#define EMMC_RESCURE_LOGO_ADDR		0x00100000										// offset 1MB
#define EMMC_RESCURE_LOGO_BLK_ADDR  (EMMC_RESCURE_LOGO_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 2048th block

/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_e( void  * dev,
                unsigned int * dest,
                unsigned int byte_length );

int do_write_e( void * dev,
                unsigned char * array_ptr,
                unsigned int * dest,
                unsigned int byte_length,
                unsigned int signature,
                const unsigned int page_offset );

int do_read_e( void * dev,
               unsigned int * src,
               unsigned char * dest,
               unsigned int byte_length,
               unsigned int signature );


int do_identify_e( void ** dev );

int do_init_e( void * dev );

void do_exit_e( void * dev );

int do_hide_hwsetting_e( void * dev,
				unsigned char * array_ptr,
                unsigned int * block_no,
                unsigned int byte_length,
                unsigned int signature,
                const unsigned int page_offset);

#endif  /* #define __FLASHDEV_E_H__ */

/* end of file */
