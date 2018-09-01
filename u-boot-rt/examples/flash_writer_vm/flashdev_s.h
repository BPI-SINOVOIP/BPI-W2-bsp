/************************************************
 Comments in Big5:				
	此檔描述 款Flash Memory 
	動作時所需的函式				
				
************************************************/
#ifndef __FLASHDEV_S_H__
#define __FLASHDEV_S_H__

#include "flash/flash_spi_list.h"
#include "include/project_config_f.h"

/************************************************************************
 *  Also update common/cmd_bootcode2.c
 ************************************************************************/
#define SPI_MAX_PARAM_SIZE				(0x800UL)
#define SPI_MIPS_RESETROM_SIZE				(0x1000UL)

#if defined(Board_CPU_RTD1395)
#define SPI_BASE_ADDR					(0x88100000UL)
#define SPI_RESETROM_SIZE				(0x2F000UL) //188KB
#elif defined(Board_CPU_RTD1295) 
#define SPI_BASE_ADDR					(0x88100000UL)
#define SPI_RESETROM_SIZE				(0x1F000UL)
#elif defined(Board_CPU_RTD1195) 
#define SPI_BASE_ADDR					(0x18100000UL)
#define SPI_RESETROM_SIZE				(0xA800UL)
#elif defined(Board_CPU_RTD1192) 
#define SPI_BASE_ADDR					(0x88100000UL)
#define SPI_RESETROM_SIZE				(0xF000UL)
#else
#define SPI_BASE_ADDR					(0x18100000UL)
#define SPI_RESETROM_SIZE				(0xA800UL)
#endif
#define SPI_CODE_PART1					(SPI_BASE_ADDR)
#define SPI_CODE_PART11					(SPI_BASE_ADDR+SPI_RESETROM_SIZE)
#define SPI_CODE_PART2					(SPI_BASE_ADDR+(1UL<<19))
#define SPI_CODE_PART3					(SPI_BASE_ADDR+(1UL<<20)+(1UL<<19))

#define SPI_ENV_PARAM_SIZE              (0x00010000UL) // 64KB
#define SPI_ENV_PARAM_ADDR              (SPI_CODE_PART11+SPI_MIPS_RESETROM_SIZE)

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
