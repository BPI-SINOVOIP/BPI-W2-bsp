/*
 * Configuration settings for the Realtek 1619 QA board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD161X_QA_RTK_EMMC_H
#define __CONFIG_RTK_RTD161X_QA_RTK_EMMC_H

/*
 * Include the common settings of RTD1619 platform.
 */
#include <configs/rtd161x_common.h>

/* ========================================================== */
/* Flash type is SPI or NAND or eMMC*/
#define CONFIG_SYS_RTK_EMMC_FLASH

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)
	/* Flash writer setting:
	*   The corresponding setting will be located at
	*   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc*/
	#define CONFIG_FLASH_WRITER_SETTING            "161x_force_emmc_rtk_non_tee"
	#define CONFIG_CHIP_ID            			   "rtd161x"
	#define CONFIG_CUSTOMER_ID            		   "demo" 
	#define CONFIG_CHIP_TYPE            		   "0001"

	#define CONFIG_SYS_NON_TEE	
	#define CONFIG_BOOTCODE_LOAD_AVFW
	/* Factory start address and size in eMMC */
	#define EMMC_BOOTCODE_AREA_SIZE		(0x620000)	//0x300000(3MB)*2+ 0x20000(0x100*512B)
	#define SCS_UNCHECK_AREA_SIZE		(0x1000)	//Reserve 4K size for melon
	#define CONFIG_FACTORY_START		EMMC_BOOTCODE_AREA_SIZE + SCS_UNCHECK_AREA_SIZE	/* For eMMC */
	#define CONFIG_FACTORY_SIZE			0x400000	/* For eMMC */
	#define CONFIG_FW_TABLE_SIZE		0x8000		/* For eMMC */

	#ifndef CONFIG_SYS_PANEL_PARAMETER
		#define CONFIG_SYS_PANEL_PARAMETER
	#endif

	/* MMC */
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

	/* ENV */
	#undef	CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
		#define CONFIG_ENV_IS_IN_FACTORY
		/* #define CONFIG_SYS_FACTORY_READ_ONLY */
	#endif

	#ifdef CONFIG_RESCUE_FROM_USB
		#undef CONFIG_RESCUE_FROM_USB_VMLINUX
		#undef CONFIG_RESCUE_FROM_USB_DTB
		#undef CONFIG_RESCUE_FROM_USB_ROOTFS
		#define CONFIG_RESCUE_FROM_USB_VMLINUX			"emmc.uImage"
		#define CONFIG_RESCUE_FROM_USB_DTB				"rescue.emmc.dtb"
		#define CONFIG_RESCUE_FROM_USB_ROOTFS			"rescue.root.emmc.cpio.gz_pad.img"
	#endif /* CONFIG_RESCUE_FROM_USB */

	/* KERNELARGS */
#ifndef CONFIG_KERNELARGS
	#define CONFIG_KERNELARGS	"init=/etc/init root=/dev/mmcblk0p1 rootfstype=squashfs rootwait loglevel=8"
#endif
#endif


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
#define V_NS16550_CLK			27000000

/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"emmc.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB		"rescue.emmc.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.emmc.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */

#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

/* The definition for RTK tee boot flow */
#define RTK_FLOW

/* Non-Cache area setting */
#undef CONFIG_SYS_NONCACHED_START
#undef CONFIG_SYS_NONCACHED_SIZE
#define CONFIG_SYS_NONCACHED_START	0x20000000
#define CONFIG_SYS_NONCACHED_SIZE	0x20000000

/* #undef CONFIG_SYS_FACTORY */

/* PWM */
//#define CONFIG_CMD_RTKPWM
//#define CONFIG_RTK_PWM
#ifdef CONFIG_RTK_PWM
#define CONFIG_CMD_PWM
//#define PWM_0_PIN_0
//#define PWM_0_PIN_1
//#define PWM_1_PIN_0
//#define PWM_1_PIN_1
//#define PWM_2_PIN_0
//#define PWM_2_PIN_1
//#define PWM_3_PIN_0
//#define PWM_3_PIN_1
#define PWM_OPEN_DRAIN_EN 0
#endif /* CONFIG_RTK_PWM */
#endif /* __CONFIG_RTK_RTD161X_QA_RTK_EMMC_H */

