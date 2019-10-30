/*
 * Configuration settings for the Realtek 1395 qa board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1395_QA_SPI_BANANAPI_H
#define __CONFIG_RTK_RTD1395_QA_SPI_BANANAPI_H

/*
 * Include the common settings of RTD1395 platform.
 */
#include <configs/rtd1395_common.h>

//==========================================================
/* Flash type is SPI or NAND or eMMC*/
#define CONFIG_SYS_RTK_SPI_FLASH

#if defined(CONFIG_SYS_RTK_SPI_FLASH)
	/*   Flash writer setting:
	 *   The corresponding setting will be located at
	 *   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc
	 */
	#define CONFIG_FLASH_WRITER_SETTING				"1395_force_spi_bananapi"
	#define CONFIG_CHIP_ID							"rtd1395"
	#define CONFIG_CUSTOMER_ID						"demo"
	#define CONFIG_CHIP_TYPE						"0001"
	#define CONFIG_FLASH_TYPE						"RTK_FLASH_SPI"

	#define CONFIG_FACTORY_BASE						0x00200000
	#define CONFIG_FACTORY_SIZE						0x00020000

	#define CONFIG_DTS_BASE							0x000F0000
	#define CONFIG_DTS_SIZE							0x00010000
	#define CONFIG_AFW_ADDR							0x000C0000
	#define CONFIG_AFW_SIZE							0x00040000

	#define CONFIG_FW_TABLE_SIZE					0x8000

	#define CONFIG_RTKSPI
	#define CONFIG_CMD_RTKSPI

	#define CONFIG_CMD_GPT
	#define CONFIG_PARTITION_UUIDS
	#define CONFIG_CMD_RTKGPT
	#define CONFIG_CMD_RTKFDT

	/* ENV */
	#undef CONFIG_ENV_SIZE
	#define CONFIG_ENV_SIZE (8192)

	#undef CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
		#define CONFIG_ENV_IS_IN_FACTORY
	#endif
#endif

/* Boot Revision */
#define CONFIG_COMPANY_ID 		"0000"
#define CONFIG_BOARD_ID         "0705"
#define CONFIG_VERSION          "0000"
//==========================================================
/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#undef CONFIG_NR_DRAM_BANKS
#undef CONFIG_SYS_SDRAM_BASE
#undef CONFIG_SYS_RAM_DCU1_SIZE

#define ARM_ROMCODE_SIZE			(188*1024)
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x0
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000
/* #define CONFIG_FT_RESCUE */

#undef  V_NS16550_CLK
#define V_NS16550_CLK			27000000	//FIXME

/* Bootcode Feature: bootcmd: load bootcode from SD card */
#define CONFIG_LOADBOOTCODE_FROM_SD

/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"emmc.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB			"rescue.emmc.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.emmc.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */

#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_CMD_RTKRNG

/* MMC */
#ifdef CONFIG_RTK_MMC_DRIVER
	#define CONFIG_MMC
	#ifndef CONFIG_PARTITIONS
		#define CONFIG_PARTITIONS
	#endif
	#define CONFIG_DOS_PARTITION
	#define CONFIG_GENERIC_MMC
	#define CONFIG_RTK_MMC
	#define CONFIG_CMD_MMC
	#define USE_SIMPLIFY_READ_WRITE
	#define CONFIG_SHA256
#endif

/* SD */
#ifdef CONFIG_RTK_SD_DRIVER
	#define CONFIG_SD
	#define CONFIG_SD30
	#ifndef CONFIG_PARTITIONS
		#define CONFIG_PARTITIONS
	#endif
	#define CONFIG_DOS_PARTITION
	#define CONFIG_RTK_SD
	#define CONFIG_CMD_SD
	#define USE_SIMPLIFY_READ_WRITE
	#define CONFIG_SHA256
#endif

#define CONFIG_VERSION			"0000"

/* SD bootcode */
#define CONFIG_SD_BOOTCODE_BASE		0x00030000

/* SPI bootcode */
#undef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x00100000

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"gosdb"

#endif /* __CONFIG_RTK_RTD1395_QA_SPI_BANANAPI_H */

