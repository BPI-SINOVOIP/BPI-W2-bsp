#ifndef __FLASHDEV_E_H__
#define __FLASHDEV_E_H__

#include "rtkemmc.h"

/************************************************************************
 * 	EMMC bootarray data layout
 ************************************************************************/
#define EMMC_BLOCK_SIZE				(512UL)
#define EMMC_BLOCK_SIZE_SHIFT		(9)
#define EMMC_BOOTARRAY_FW_TABLE_ADDR        0x00020000
#define EMMC_BOOTARRAY_FW_TABLE_BLK			(EMMC_BOOTARRAY_FW_TABLE_ADDR>>EMMC_BLOCK_SIZE_SHIFT)	// 0x100
#define BACKUP_EMMC_UDA_BLK_OFFSET			(0x1800) //offset 3MB

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


#endif  /* #define __FLASHDEV_E_H__ */

/* end of file */
