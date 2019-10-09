/************************************************
 Comments in Big5:				
	此檔描述 款Flash Memory 
	動作時所需的函式				
				
************************************************/
#ifndef __FLASHDEV_N_H__
#define __FLASHDEV_N_H__


#include "flash/flash_nand_list.h"
#include "flash/flash_nand_profile.h"


/* bad block table structure */
typedef struct  __attribute__ ((__packed__)){
    unsigned short BB_die;		// chip number where bad block reside in
    unsigned short bad_block;		// block no. marked as bad
    unsigned short RB_die;		// chip number where remapping block reside in
    unsigned short remap_block;		// remapping block no.
} BB_t;

/* block state */
#define BLOCK_BAD               0x00
#define BLOCK_HWSETTING         0X23
#define BLOCK_KEY_SIG		0x24
#define BLOCK_BOOTCODE          0x79
#define BLOCK_DATA              0x80
#define BLOCK_ENVPARAM_MAGICNO  0X81
#define BLOCK_FACTORY_SETTING   0X82
#define SECURE_FSBL_MAGIC_NUM   0x89        /* Identify secure boot loader in NAND flash spare area*/
#define SECURE_OS_MAGIC_NUM     0x90        /* Identify secure os loader in NAND flash spare area*/
#define BL31_MAGIC_NUM          0x91        /* Identify bl31 in NAND flash spare area*/
#define RSA_KEY_FW_MAGIC_NUM    0x92        /* Identify rsa key fw in NAND flash spare area*/
#define RSA_KEY_TEE_MAGIC_NUM   0x93        /* Identify rsa key tee in NAND flash spare area*/
#define BLOCK_OTHER_DATA	0xd0	// unknown data (user program into flash)
#define BLOCK_BBT		0xbb	// bad block table
#define BLOCK_CLEAN		0xff	// block is empty
#define BLOCK_UNDETERMINE	0x55	// block state is undetermined 
// (NOTE: BLOCK_UNDETERMINE is a fake state, all blocks in the flash SHALL NOT have this state or it will cause some problem)

#define DATA_ALL_ONE		1		// read one page and all bit is '1'
#define NULL		          ((void *)0)

#define NAND_BOOTCODE_AREA_12MB			0xc00000	// bootcode blocks in NAND flash (first 16MB)
#define NAND_BOOTCODE_AREA_30MB			0x1e00000
#define NAND_BOOTCODE_AREA_50MB			0x3200000
#define NAND_BOOTCODE_AREA_100MB			0x6400000
#define DEFAULT_NAND_BOOTCODE_SIZE		NAND_BOOTCODE_AREA_12MB

#define NAND_ENV_SIZE		0x10000		// size of env param + magic no 

/* bad block table related */
#define RBA_PERCENTAGE 		5		// percentage of blocks reserved for bad block remapping
#define BB_INIT 		0xFFFE		// initial bad_block value in bad block table
#define	RB_INIT			0xFFFD		// initial remap_block value in bad block table
#define BB_DIE_INIT		0xEEEE		// initial bad_block chip value in bad block table
#define RB_DIE_INIT		BB_DIE_INIT	// initial remap_block chip value in bad block table

/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_n(void  *dev,
               unsigned int* dest,
               unsigned int   rem_size);

int do_write_n(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset);
               
int do_read_n(void *dev,
               unsigned int*  start_blk,	
               unsigned char* dest,		
               unsigned int   rem_size,		
               unsigned int   signature);               
               

int do_identify_n(void **dev);

int do_init_n(void *dev);

void do_exit_n(void *dev);

int get_env_n(void *dev, unsigned char *buf);

int save_env_n(void *dev, unsigned char *buf);
void NF_dump_flash(n_device_type *device, unsigned int dst_addr, unsigned int src_page, unsigned int page_len);

#endif
