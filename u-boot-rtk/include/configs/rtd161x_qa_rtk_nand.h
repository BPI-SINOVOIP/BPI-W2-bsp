/*
 * Configuration settings for the Realtek 1619 qa board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD161x_QA_RTK_NAND_H
#define __CONFIG_RTK_RTD161x_QA_RTK_NAND_H

/*
 * Include the common settings of RTD1619 platform.
 */
#include <configs/rtd161x_common.h>

/* Flash type is NAND*/
#define CONFIG_SYS_RTK_NAND_FLASH

#if defined(CONFIG_SYS_RTK_NAND_FLASH)
	/* Flash writer setting:
	*   The corresponding setting will be located at
	*   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc*/
	#define CONFIG_FLASH_WRITER_SETTING            "161x_force_nand_rtk"
	#define CONFIG_CHIP_ID            			   "rtd161x"
	#define CONFIG_CUSTOMER_ID            		   "demo" 
	#define CONFIG_CHIP_TYPE            		   "0001"
	#define CONFIG_FLASH_TYPE					   "RTK_FLASH_NAND"

	/* Factory*/
	#define CONFIG_NAND_BLOCK_SIZE		0x20000		/* SLC block: 128KB */
	#define CONFIG_FACTORY_SIZE     	0x400000	/* 4MB */
	
	#define CONFIG_MTD_DEVICE
	#define CONFIG_MTD_PARTITIONS
	#define CONFIG_MTD_NAND_RTK_1395
	#define CONFIG_SYS_MAX_NAND_DEVICE	1
	#define CONFIG_SYS_NAND_BASE  	  	0x00000000
	
	/* ENV */
	#undef CONFIG_ENV_SIZE
	#define CONFIG_ENV_SIZE (8192)

	#undef  CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
	#define CONFIG_ENV_IS_IN_FACTORY
	/* #define CONFIG_SYS_FACTORY_READ_ONLY */
	#endif
	
	#ifdef CONFIG_RESCUE_FROM_USB
		#undef CONFIG_RESCUE_FROM_USB_VMLINUX
		#undef CONFIG_RESCUE_FROM_USB_DTB
		#undef CONFIG_RESCUE_FROM_USB_ROOTFS
		#define CONFIG_RESCUE_FROM_USB_VMLINUX			"nand.uImage"
		#define CONFIG_RESCUE_FROM_USB_DTB				"rescue.nand.dtb"
		#define CONFIG_RESCUE_FROM_USB_ROOTFS			"rescue.root.nand.cpio.gz_pad.img"
	#endif /* CONFIG_RESCUE_FROM_USB */
	
	/* KERNELARGS */
#ifndef CONFIG_KERNELARGS
	//FIX ME, use correct NAND bootargs, here we just avoid compiling error
	#define CONFIG_KERNELARGS	"init=/etc/init root=/dev/mmcblk0p1 rootfstype=squashfs rootwait loglevel=8"
#endif
#endif

/* Boot Revision */
#define CONFIG_COMPANY_ID 		"0000"
#define CONFIG_BOARD_ID         "0705"
#define CONFIG_VERSION          "0000"

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#undef CONFIG_NR_DRAM_BANKS
#undef CONFIG_SYS_SDRAM_BASE
#undef CONFIG_SYS_RAM_DCU1_SIZE

#define ARM_ROMCODE_SIZE		(188*1024)
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x0
#define CONFIG_SYS_RAM_DCU1_SIZE	0x40000000	// FIXME
/* #define CONFIG_FT_RESCUE */

#undef V_NS16550_CLK
#define V_NS16550_CLK			27000000	//FIXME

/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"nand.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB		"rescue.nand.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.nand.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */

/*The partition format and file system of ext4*/
#define CONFIG_EFI_PARTITION
#define CONFIG_CMD_GPT
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_EXT4

#ifdef CONFIG_ACPU_LOGBUF_ENABLE
#define CONFIG_ACPU_LOGBUF_ADDR		0x0FE00000
#define CONFIG_ACPU_LOGBUF_SIZE		0x00002000
#endif

#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

#undef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x00030000

#endif /* __CONFIG_RTK_RTD161x_QA_RTK_NAND_H */

