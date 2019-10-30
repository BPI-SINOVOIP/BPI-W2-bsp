/************************************************
 Comments in Big5:				
	���ɴy�z ��Flash Memory 
	�ʧ@�ɩһݪ��禡				
				
************************************************/
#ifndef __FLASHDEV_S_H__
#define __FLASHDEV_S_H__

#include "flash/flash_spi_list.h"
#include "include/project_config_f.h"

/************************************************************************
 *  Also update common/cmd_bootcode2.c
 ************************************************************************/
#define SPI_MAX_PARAM_SIZE				(0x800UL)
#define SPI_BOOTARRAY_FW_TABLE_SIZE		(1024)

#define SPI_BASE_ADDR					(0x88100000UL)
#define SPI_SCPU_RESETROM_SIZE			(0x2B000UL) //172KB
#define SPI_PCPU_RESETROM_SIZE			(0x4000UL) //16KB
#define SPI_ACPU_RESETROM_SIZE			(0x1000UL) //4KB

#define SPI_CODE_PART1_1					(SPI_BASE_ADDR)	//SCPU rom start
#define SPI_CODE_PART1_2					(SPI_BASE_ADDR+SPI_SCPU_RESETROM_SIZE) //PCPU rom start
#define SPI_CODE_PART1_3					(SPI_CODE_PART1_2+SPI_PCPU_RESETROM_SIZE) //ACPU rom start

#define SPI_CODE_PART2					(SPI_BASE_ADDR+(1UL<<19))
#define SPI_CODE_PART3					(SPI_BASE_ADDR+(1UL<<20)+(1UL<<19))

#define SPI_ENV_PARAM_ADDR              (SPI_CODE_PART1_3+SPI_ACPU_RESETROM_SIZE)

#define SPI_ERASE_SIZE_4KB				(0x00001000UL)
#define SPI_ERASE_SIZE_32KB				(0x00008000UL)
#define SPI_ERASE_SIZE_64KB				(0x00010000UL)
#define SPI_ERASE_SIZE_256KB			(0x00040000UL)

#define SPI_ERASE_SIZE_4KB_MINUS_1		(0x00001000UL-1UL)
#define SPI_ERASE_SIZE_32KB_MINUS_1		(0x00008000UL-1UL)
#define SPI_ERASE_SIZE_64KB_MINUS_1		(0x00010000UL-1UL)
#define SPI_ERASE_SIZE_256KB_MINUS_1	(0x00040000UL-1UL)

#define SPI_ERASE_SIZE_4KB_ALIGNMENT	(0xFFFFF000UL)
#define SPI_ERASE_SIZE_32KB_ALIGNMENT	(0xFFFF8000UL)
#define SPI_ERASE_SIZE_64KB_ALIGNMENT	(0xFFFF0000UL)
#define SPI_ERASE_SIZE_256KB_ALIGNMENT	(0xFFFC0000UL)

/************************************************************************
 *  Public function
 ************************************************************************/
int do_erase_s(void  *dev,
               unsigned int* dest,
               unsigned int   rem_size);

int do_write_s(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset);

int do_identify_s(void **dev);

int do_init_s(void *dev);

void do_exit_s(void *dev);

void spi_switch_read_mode(void);

void spi_hexdump( const char * str, unsigned int start_address, unsigned int length );

#ifdef CONFIG_VERIFY_SPI
void spi_verify_data( const char * str, unsigned int start_address,unsigned int data_address, unsigned int length );
#endif

#endif
