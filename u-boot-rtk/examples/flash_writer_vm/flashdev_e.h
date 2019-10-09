#ifndef __FLASHDEV_E_H__
#define __FLASHDEV_E_H__

#include "rtkemmc.h"

/************************************************************************
 * 	EMMC bootarray data layout
 ************************************************************************/
#define EMMC_BLOCK_SIZE				(512UL)
#define EMMC_BLOCK_SIZE_SHIFT		(9)
#define EMMC_HW_SETTING_ADDR        0x00020000
#define EMMC_HW_SETTING_BLK			(EMMC_HW_SETTING_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 0x104

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
                const unsigned int boot_partition );

int do_read_e( void * dev,
               unsigned int * src,
               unsigned char * dest,
               unsigned int byte_length,
               unsigned int boot_partition );


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
