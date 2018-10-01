/*
 * Realtek 1295 common configuration settings
 *
 */

#ifndef __CONFIG_RTK_RTD1295_COMMON_H
#define __CONFIG_RTK_RTD1295_COMMON_H


/* Macros to convert string from number */
#ifndef __STR
#define __STR(x) #x
#endif
#ifndef STR
#define STR(x) __STR(x)
#endif

#define CONFIG_UBOOT_DEFAULT

/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_SKIP_LOWLEVEL_INIT	1

#undef CONFIG_USE_IRQ				/* no support for IRQs */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_REVISION_TAG		1

/*
 * Realtek IC type
 */
#define CONFIG_RTD1295     1

/*
 * NAS
 */
#ifdef CONFIG_NAS_ENABLE 
#define NAS_ENABLE			1	/* Enable NAS features */
//#define NAS_DUAL			1	/* Enable NAS dual boot on eMMC */
#endif

#ifdef NAS_ENABLE
#define CONFIG_PARTITION_UUIDS
#endif

/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
#define CONFIG_ENV_IS_IN_REMOTE
#define CONFIG_ENV_ADDR			0x10000000
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (256 << 10))

/*
 * Hardware drivers
 */

/*
 * serial port - NS16550 compatible
 */
#define V_NS16550_CLK				27000000

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK
#define CONFIG_SYS_NS16550_UART1_CLK    432000000 

#define UART1_BASE					0x9801B200
#define UART0_BASE					0x98007800
#define CONFIG_CONS_INDEX			1
#define CONFIG_SYS_NS16550_COM1     UART0_BASE
#define CONFIG_SYS_NS16550_COM2     UART1_BASE

#define CONFIG_BAUDRATE				115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3

/* Flash */
#define CONFIG_SYS_NO_FLASH	1

/*
 * Environment setup
 */

#define CONFIG_BOOTDELAY	3

#define CONFIG_ENV_OVERWRITE

/* BPI */
#define CONFIG_BOOTCOMMAND \
	"run boot_normal;" \
	"if test $? -ne 0; then "			\
		"run set_sdbootargs && gosd;"		\
	"fi;"						\
	"if test $? -ne 0; then "			\
		"run set_emmcbootargs && bootr; "	\
	"fi;"

#define CONFIG_KERNEL_LOADADDR	0x03000000
#define CONFIG_ROOTFS_LOADADDR	0x02200000
#define CONFIG_RESCUE_ROOTFS_LOADADDR 	0x02200000
#define CONFIG_LOGO_LOADADDR	0x02002000      //reserved ~2M
#define CONFIG_FDT_LOADADDR	0x02100000      //reserved 64K
#define CONFIG_BLUE_LOGO_LOADADDR 0x30000000
#if 0 /*def CONFIG_NAS_ENABLE*/
#define CONFIG_FW_LOADADDR	0x01b00000  //reserved 4M BPI kernel 4.4
#else
#define CONFIG_FW_LOADADDR	0x0f900000  //reserved 4M BPI kernel 4.9 / 4.1
#endif

#define CONFIG_EXTRA_ENV_SETTINGS                   \
    "bpiver=1\0" \
    "bpi=bananapi\0" \
    "board=bpi-w2\0" \
    "chip=RTD1296\0" \
    "service=linux\0" \
    "scriptaddr=0x1500000\0" \
    "device=sd\0" \
    "partition=0:1\0" \
    "kernel=uImage\0" \
    "root=/dev/mmcblk0p2\0" \
    "debug=7\0" \
    "bootenv=uEnv.txt\0" \
    "checksd=fatinfo ${device} 0:1\0" \
    "loadbootenv=fatload ${device} ${partition} ${scriptaddr} ${bpi}/${board}/${service}/${bootenv} || fatload ${device} ${partition} ${scriptaddr} ${bootenv}\0" \
    "boot_normal=if run checksd; then echo Boot from SD ; setenv partition 0:1; else echo Boot from eMMC ; mmc init 0 ; setenv partition 0:1 ; fi; if run loadbootenv; then echo Loaded environment from ${bootenv}; env import -t ${scriptaddr} ${filesize}; fi; run uenvcmd; fatload mmc 0:1 ${loadaddr} ${bpi}/${board}/${service}/${kernel}; bootr\0" \
    "bootmenu_delay=30\0" \
   "kernel_loadaddr=0x03000000\0"                  \
   "fdt_loadaddr=0x02100000\0"                  \
   "fdt_high=0xffffffffffffffff\0"                  \
   "rootfs_loadaddr=0x02200000\0"                   \
   "rescue_rootfs_loadaddr=0x02200000\0"                   \
   "audio_loadaddr="STR(CONFIG_FW_LOADADDR)"\0"                 \
   "blue_logo_loadaddr="STR(CONFIG_BLUE_LOGO_LOADADDR)"\0"      \
   "mtd_part=mtdparts=rtk_nand:\0"                  \
	"console_args=earlycon=uart8250,mmio32,0x98007800 fbcon=map:0 console=ttyS0,115200 loglevel=7\0" \
	"sdroot_args=board=bpi-w2 noinitrd rootwait root=/dev/mmcblk0p2 rw\0" \
	"set_sdbootargs=setenv bootargs ${console_args} ${sdroot_args}\0" \
	"emmcroot_args=root=/dev/mmcblk0p1 rootfstype=squashfs rootwait\0" \
	"set_emmcbootargs=setenv bootargs ${console_args} ${emmcroot_args}\0" \

/* Pass open firmware flat tree */
#define CONFIG_CMD_BOOTI
#define CONFIG_GZIP_DECOMPRESS_KERNEL_ADDR	0x0c000000	// GZIPED kernel decompress addr
#define CONFIG_GZIP_KERNEL_MAX_LEN		0x01400000	// Set MAX size to 20M after decompressed
/*
//#define CONFIG_ARMV8_SWITCH_TO_EL1
*/
#define CONFIG_OF_LIBFDT    		1
#define CONFIG_OF_STDOUT_VIA_ALIAS	1

/* Console */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

/*
// 1:cache disable   0:enable
*/
#if 0 
	#define CONFIG_SYS_ICACHE_OFF
	#define CONFIG_SYS_DCACHE_OFF
#else
	#define CONFIG_NONCACHE_ALLOCATION
	#define CONFIG_CMD_CACHE
#endif


/*
 * Miscellaneous configurable options
 */

#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER	/* use "hush" command parser */
#define CONFIG_HUSH_PARSER
#define CONFIG_SYS_CBSIZE		640

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		32

/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

/*
 * memtest setup
 */
#define CONFIG_SYS_MEMTEST_START	0x00000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + (32 << 20))

/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		0x03000000

/* Use General purpose timer 2 */
#define CONFIG_SYS_TIMER		0     //FPGA
#define CONFIG_SYS_HZ			1000

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
/*
//stack size is setup in linker script 1MB
*/
#ifdef CONFIG_USE_IRQ
	#define CONFIG_STACKSIZE_IRQ	(4 << 10)	/* IRQ stack */
	#define CONFIG_STACKSIZE_FIQ	(4 << 10)	/* FIQ stack */
#endif

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000		//512MB

/* GIC-400 setting */
#define CONFIG_GICV2
#define GICD_BASE			0xff011000      // FIXME, all these register should be reviewed
#define GICC_BASE			0xff012000      // FIXME, all these register should be reviewed



/*
//if the relocation is enabled, the address is used to be the stack at very beginning.
*/
#define CONFIG_SYS_INIT_SP_ADDR     0x00100000


/*
// 1:cache disable   0:enable
*/
#if 0
	#define CONFIG_SYS_ICACHE_OFF
	#define CONFIG_SYS_DCACHE_OFF
#else
	#define CONFIG_SYS_NONCACHED_MEMORY
	#define CONFIG_SYS_NONCACHED_START	0x20000000
	#define CONFIG_SYS_NONCACHED_SIZE	0x20000000
	#define CONFIG_CMD_CACHE
#endif

#define CONFIG_SYS_CACHELINE_SIZE	64

/*
 * rm include/autoconf.mk ---- prevent use old CONFIG_SYS_TEXT_BASE
 * make CONFIG_SYS_TEXT_BASE
 */
#ifndef CONFIG_SYS_TEXT_BASE
	#define CONFIG_SYS_TEXT_BASE		0x00020000
#endif

#define CONFIG_SYS_PROMPT       		"BPI-W2> "

/* Library support */
#define CONFIG_LZMA
#define CONFIG_LZO

#ifdef CONFIG_CMD_NET
	/* Eth Net */
	#define CONFIG_CMD_PING
/*
	//#define CONFIG_CMD_TFTPPUT
*/
	#define CONFIG_RTL8168
	#define CONFIG_TFTP_BLOCKSIZE		400

	/* Network setting */
	#define CONFIG_ETH_PRIME			r8168#0
	#define CONFIG_ETHADDR				00:10:20:30:40:50
	#define CONFIG_IPADDR				192.168.100.1
	#define CONFIG_GATEWAYIP			192.168.100.254
	#define CONFIG_SERVERIP				192.168.100.2
	#define CONFIG_NETMASK				255.255.255.0
#endif

/* BPI */
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_RUN
#define CONFIG_CMD_IMPORTENV
#define CONFIG_CMD_EXPORTENV
#define CONFIG_EFI_PARTITION
#define CONFIG_CMD_GPT
#define CONFIG_PARTITION_UUIDS
#define CONFIG_FS_EXT4
#define CONFIG_CMD_EXT4

/* USB Setting */
#define CONFIG_CMD_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_RTKMKFAT
/*
//#define CONFIG_PARTITIONS
*/
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 5
/*
//#define CONFIG_DM_USB
*/

/*Total USB quantity*/
#define CONFIG_USB_MAX_CONTROLLER_COUNT 4

/* define 1295 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#define USB_PORT0_GPIO_TYPE "ISOGPIO"
#define USB_PORT0_GPIO_NUM 1
#define USB_PORT0_TYPE_C_RD_GPIO_TYPE "ISOGPIO"
#define USB_PORT0_TYPE_C_RD_GPIO_NUM 34
/* Port 1, xhci u2 host */
#define USB_PORT1_GPIO_TYPE "GPIO"
#define USB_PORT1_GPIO_NUM  19
/* Port 2, ehci u2 host */
#define USB_PORT2_GPIO_TYPE "GPIO"
#define USB_PORT2_GPIO_NUM  19
/* Port 3, xhci u3 host only for 1296 */
#define USB_PORT3_GPIO_TYPE "NO_DEFINE"
#define USB_PORT3_GPIO_NUM 0

/*
// for none define GPIO
*/
/* define 1296 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#define RTD1296_USB_PORT0_GPIO_TYPE "ISOGPIO"
#define RTD1296_USB_PORT0_GPIO_NUM 1
#define RTD1296_USB_PORT0_TYPE_C_RD_GPIO_TYPE "ISOGPIO"
#define RTD1296_USB_PORT0_TYPE_C_RD_GPIO_NUM 34
/* Port 1, xhci u2 host */
#define RTD1296_USB_PORT1_GPIO_TYPE "ISOGPIO"
#define RTD1296_USB_PORT1_GPIO_NUM 31
/* Port 2, ehci u2 host */
#define RTD1296_USB_PORT2_GPIO_TYPE "ISOGPIO"
#define RTD1296_USB_PORT2_GPIO_NUM  31
/* Port 3, xhci u3 host only for 1296 */
#define RTD1296_USB_PORT3_GPIO_TYPE "ISOGPIO"
#define RTD1296_USB_PORT3_GPIO_NUM 32

/* Fastboot */
#define CONFIG_G_DNL_VENDOR_NUM      0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM   0x4e40
#define CONFIG_G_DNL_MANUFACTURER   "Realtek"

/*
//#define CONFIG_ANDROID_BOOT_IMAGE
*/
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_USB_FASTBOOT_BUF_ADDR   0x28000000//CONFIG_SYS_LOAD_ADDR
#define CONFIG_USB_FASTBOOT_BUF_SIZE   0x6400000 //100MB
#define FASTBOOT_FW_IMG_UPDATE_ADDR    0x30000000
#define FASTBOOT_FW_IMG_UPDATE_MAX_SIZE 0x6400000 //100MB
#define FASTBOOT_SPARSE_IMAGE_ADDR     0x36400000
#define FASTBOOT_SPARSE_IMAGE_MAX_SIZE  0x6400000 //100MB
#define FASTBOOT_TAR_BUFFER_ADDR       0x3C800000
#define FASTBOOT_TAR_BUFFER_SIZE         0x400000 //4MB

/* Factory */
#define CONFIG_SYS_FACTORY
#define PANEL_CONFIG_FROM_FACTORY_PANEL_BIN

/* GPIO */
#define CONFIG_REALTEK_GPIO
#define CONFIG_INSTALL_GPIO_NUM    		8
#define CONFIG_HDMITx_HPD_IGPIO_NUM		6

/* I2C */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_REALTEK_I2C
#define CONFIG_SYS_I2C_SPEED		100


/* Auto detect sink*/
#define CONFIG_SYS_AUTO_DETECT
#define CONFIG_HDMITX_MODE				 1 // 0:Always OFF, 1: Always ON, 2: Auto
/* drivers/logo_disp/rtk_rpc.h */
#ifdef BPI
#define CONFIG_DEFAULT_TV_SYSTEM    	25 //1080P_60
#else
#define CONFIG_DEFAULT_TV_SYSTEM    	13 //720P_60
#endif

/* If partition table */
#ifndef CONFIG_PARTITIONS
	#define CONFIG_PARTITIONS
	#define CONFIG_DOS_PARTITION
#endif

/* EEPROM */
#define CONFIG_CMD_EEPROM
#define CONFIG_SYS_I2C_EEPROM_BUS 5
#define CONFIG_SYS_I2C_FRAM
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS 7

/* enable key burn fnction */
/*
//#define CONFIG_CMD_KEY_BURNING
*/

/********* RTK CONFIGS ************/
#define CONFIG_BSP_REALTEK
#define CONFIG_NO_RELOCATION
#define CONFIG_HEAP_ADDR	0x07880000

#define CONFIG_MISC_INIT_R
#endif /* __CONFIG_RTK_RTD1295_COMMON_H */

