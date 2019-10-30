/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * To match the U-Boot user interface on ARM platforms to the U-Boot
 * standard (as on PPC platforms), some messages with debug character
 * are removed from the default U-Boot build.
 *
 * Define DEBUG here if you want additional info as shown below
 * printed upon startup:
 *
 * U-Boot code: 00F00000 -> 00F3C774  BSS: -> 00FC3274
 * IRQ Stack: 00ebff7c
 * FIQ Stack: 00ebef7c
 */
#include <common.h>
#include <command.h>
#include <environment.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <version.h>
#include <net.h>
#include <serial.h>
#include <nand.h>
#include <onenand_uboot.h>
#include <mmc.h>
#include <scsi.h>
#include <status_led.h>
#include <libfdt.h>
#include <fdtdec.h>
#include <post.h>
#include <logbuff.h>
#include <asm/sections.h>
#include <rtkemmc_generic.h>

#include <asm/arch/platform_lib/board/pcb_mgr.h>
#include <asm/arch/extern_param.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/rtk_ipc_shm.h>
#include <asm/arch/system.h>
#include <asm/arch/ir.h>
#include <asm/arch/pwm.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/bootparam.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/misc_reg.h>
#include <asm/arch/md.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <logo_disp/logo_disp_api.h>
#include <watchdog.h>

#if defined(CONFIG_RTK_LSADC)
#include <asm/arch/lsadc.h>
#endif

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

ulong monitor_flash_len;

#ifdef BPI
#else
int bpi_boot=0; // 0: SD 1: eMMC
#endif

#ifdef CONFIG_HAS_DATAFLASH
extern int  AT91F_DataflashInit(void);
extern void dataflash_print_info(void);
#endif

#if defined(CONFIG_HARD_I2C) || \
	defined(CONFIG_SYS_I2C)
#include <i2c.h>
#endif

#ifdef CONFIG_RTK_EMMC_TRADITIONAL_MODE
#define RTK_eMMC_TRADITIONAL_MODE
#else
#define RTK_eMMC_FAST_MODE	//if users want to use mmc command, just undef RTK_eMMC_FAST_MODE
#endif

/************************************************************************
 *  External variables, check arch/arm/lib/sections.c for reasons
 ************************************************************************/

struct RTK119X_ipc_shm ipc_shm;
struct RTK119X_ipc_shm_ir ipc_ir;
BOOT_FLASH_T boot_flash_type;
/************************************************************************
 * Coloured LED functionality
 ************************************************************************
 * May be supplied by boards if desired
 */
__weak void coloured_LED_init(void) {}
__weak void red_led_on(void) {}
__weak void red_led_off(void) {}
__weak void green_led_on(void) {}
__weak void green_led_off(void) {}
__weak void yellow_led_on(void) {}
__weak void yellow_led_off(void) {}
__weak void blue_led_on(void) {}
__weak void blue_led_off(void) {}

extern int rtl8168_initialize(bd_t *bis);
extern void set_hdmi_off(void);
extern int sink_capability_handler(int set);
extern int dptx_sink_capability_handler(int set);

/*
 ************************************************************************
 * Init Utilities							*
 ************************************************************************
 * Some of this code should be moved into the core functions,
 * or dropped completely,
 * but let's get it working (again) first...
 */

#if defined(CONFIG_ARM_DCC) && !defined(CONFIG_BAUDRATE)
#define CONFIG_BAUDRATE 115200
#endif

static int init_baudrate(void)
{
	gd->baudrate = getenv_ulong("baudrate", 10, CONFIG_BAUDRATE);
	return 0;
}

static int display_banner(void)
{
	printf("\n\n%s\n\n", version_string);
	debug("U-Boot code: %08lX -> %08lX  BSS: -> %08lX\n",
	       (ulong)&_start,
	       (ulong)&__bss_start, (ulong)&__bss_end);
#ifdef CONFIG_MODEM_SUPPORT
	debug("Modem Support enabled\n");
#endif
#ifdef CONFIG_USE_IRQ
	debug("IRQ Stack: %08lx\n", IRQ_STACK_START);
	debug("FIQ Stack: %08lx\n", FIQ_STACK_START);
#endif

	return (0);
}

/*
 * WARNING: this code looks "cleaner" than the PowerPC version, but
 * has the disadvantage that you either get nothing, or everything.
 * On PowerPC, you might see "DRAM: " before the system hangs - which
 * gives a simple yet clear indication which part of the
 * initialization if failing.
 */
static int display_dram_config(void)
{
	int i;

#ifdef DEBUG
	puts("RAM Configuration:\n");

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		printf("Bank #%d: %08lx ", i, gd->bd->bi_dram[i].start);
		print_size(gd->bd->bi_dram[i].size, "\n");
	}
#else
	ulong size = 0;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
		size += gd->bd->bi_dram[i].size;

	extern unsigned long get_accessible_ddr_size(int unit);
	puts("DRAM:  ");
	print_size(get_accessible_ddr_size(UNIT_BYTE), "\n");
#endif

	return (0);
}

#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SYS_I2C)
static int init_func_i2c(void)
{
	puts("I2C:   ");
#ifdef CONFIG_SYS_I2C
	i2c_init_all();
#else
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif
	puts("ready\n");
	return (0);
}
#endif

#if defined(CONFIG_CMD_PCI) || defined (CONFIG_PCI)
#include <pci.h>
static int arm_pci_init(void)
{
	pci_init();
	return 0;
}
#endif /* CONFIG_CMD_PCI || CONFIG_PCI */

/*
 * Breathe some life into the board...
 *
 * Initialize a serial port as console, and carry out some hardware
 * tests.
 *
 * The first part of initialization is running from Flash memory;
 * its main purpose is to initialize the RAM so that we
 * can relocate the monitor code to RAM.
 */

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependent #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t) (void);

__weak void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size =  gd->ram_size;
}

__weak int arch_cpu_init(void)
{
	return 0;
}

__weak int power_init_board(void)
{
	return 0;
}

	/* Record the board_init_f() bootstage (after arch_cpu_init()) */
static int mark_bootstage(void)
{
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_F, "board_init_f");

	return 0;
}

init_fnc_t *init_sequence[] = {
	arch_cpu_init,		/* basic arch cpu dependent setup */
	mark_bootstage,
#ifdef CONFIG_OF_CONTROL
	fdtdec_check_fdt,
#endif
#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,
#endif
	timer_init,			/* initialize timer */
#ifdef CONFIG_BOARD_POSTCLK_INIT
	board_postclk_init,
#endif
#ifdef CONFIG_FSL_ESDHC
	get_clocks,
#endif
	env_init,			/* initialize environment */
	init_baudrate,		/* initialze baudrate settings */
	serial_init,		/* serial communications setup */
	console_init_f,		/* stage 1 init of console */
	display_banner,		/* say that we are here */
	print_cpuinfo,		/* display cpu info (and speed) */
#if defined(CONFIG_DISPLAY_BOARDINFO)
	checkboard,			/* display board info */
#endif
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SYS_I2C)
	init_func_i2c,
#endif
	dram_init,			/* configure available RAM banks */
	NULL,
};

void board_init_f(ulong bootflag)
{
	bd_t *bd;
	init_fnc_t **init_fnc_ptr;
	gd_t *id;
	ulong addr, addr_sp;
#ifdef CONFIG_PRAM
	ulong reg;
#endif
	void *new_fdt = NULL;
	size_t fdt_size = 0;

	memset((void *)gd, 0, sizeof(gd_t));

	gd->mon_len = (ulong)&__bss_end - (ulong)_start;
#ifdef CONFIG_OF_EMBED
	/* Get a pointer to the FDT */
	gd->fdt_blob = __dtb_dt_begin;
#elif defined CONFIG_OF_SEPARATE
	/* FDT is at end of image */
	gd->fdt_blob = &_end;
#endif
	/* Allow the early environment to override the fdt address */
	gd->fdt_blob = (void *)getenv_ulong("fdtcontroladdr", 16,
						(uintptr_t)gd->fdt_blob);

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr) {
		if ((*init_fnc_ptr)() != 0) {
			hang ();
		}
	}

#ifdef CONFIG_OF_CONTROL
	/* For now, put this check after the console is ready */
	if (fdtdec_prepare_fdt()) {
		panic("** CONFIG_OF_CONTROL defined but no FDT - please see "
			"doc/README.fdt-control");
	}
#endif

	debug("monitor len: %08lX\n", gd->mon_len);
	/*
	 * Ram is setup, size stored in gd !!
	 */
	debug("ramsize: %08lX\n", gd->ram_size);
#if defined(CONFIG_SYS_MEM_TOP_HIDE)
	/*
	 * Subtract specified amount of memory to hide so that it won't
	 * get "touched" at all by U-Boot. By fixing up gd->ram_size
	 * the Linux kernel should now get passed the now "corrected"
	 * memory size and won't touch it either. This should work
	 * for arch/ppc and arch/powerpc. Only Linux board ports in
	 * arch/powerpc with bootwrapper support, that recalculate the
	 * memory size from the SDRAM controller setup will have to
	 * get fixed.
	 */
	gd->ram_size -= CONFIG_SYS_MEM_TOP_HIDE;
#endif

	addr = CONFIG_SYS_SDRAM_BASE + get_effective_memsize();

#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
	/* reserve kernel log buffer */
	addr -= (LOGBUFF_RESERVE);
	debug("Reserving %dk for kernel logbuffer at %08lx\n", LOGBUFF_LEN,
		addr);
#endif
#endif

#ifdef CONFIG_PRAM
	/*
	 * reserve protected RAM
	 */
	reg = getenv_ulong("pram", 10, CONFIG_PRAM);
	addr -= (reg << 10);		/* size is in kB */
	debug("Reserving %ldk for protected RAM at %08lx\n", reg, addr);
#endif /* CONFIG_PRAM */

#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	/* reserve TLB table */
	gd->arch.tlb_size = PGTABLE_SIZE;
	addr -= gd->arch.tlb_size;

	/* round down to next 64 kB limit */
	addr &= ~(0x10000 - 1);

	gd->arch.tlb_addr = addr;
	debug("TLB table from %08lx to %08lx\n", addr, addr + gd->arch.tlb_size);
#endif

	/* round down to next 4 kB limit */
	addr &= ~(4096 - 1);
	debug("Top of RAM usable for U-Boot at: %08lx\n", addr);

#ifdef CONFIG_LCD
#ifdef CONFIG_FB_ADDR
	gd->fb_base = CONFIG_FB_ADDR;
#else
	/* reserve memory for LCD display (always full pages) */
	addr = lcd_setmem(addr);
	gd->fb_base = addr;
#endif /* CONFIG_FB_ADDR */
#endif /* CONFIG_LCD */

	/*
	 * reserve memory for U-Boot code, data & bss
	 * round down to next 4 kB limit
	 */
	addr -= gd->mon_len;
	addr &= ~(4096 - 1);

	debug("Reserving %ldk for U-Boot at: %08lx\n", gd->mon_len >> 10, addr);

#ifndef CONFIG_SPL_BUILD
	/*
	 * reserve memory for malloc() arena
	 */
	addr_sp = addr - TOTAL_MALLOC_LEN;
	debug("Reserving %dk for malloc() at: %08lx\n",
			TOTAL_MALLOC_LEN >> 10, addr_sp);
	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof (bd_t);
	bd = (bd_t *) addr_sp;
	gd->bd = bd;
	debug("Reserving %zu Bytes for Board Info at: %08lx\n",
			sizeof (bd_t), addr_sp);

#ifdef CONFIG_MACH_TYPE
	gd->bd->bi_arch_number = CONFIG_MACH_TYPE; /* board id for Linux */
#endif

	addr_sp -= sizeof (gd_t);
	id = (gd_t *) addr_sp;
	debug("Reserving %zu Bytes for Global Data at: %08lx\n",
			sizeof (gd_t), addr_sp);

#if defined(CONFIG_OF_SEPARATE) && defined(CONFIG_OF_CONTROL)
	/*
	 * If the device tree is sitting immediate above our image then we
	 * must relocate it. If it is embedded in the data section, then it
	 * will be relocated with other data.
	 */
	if (gd->fdt_blob) {
		fdt_size = ALIGN(fdt_totalsize(gd->fdt_blob) + 0x1000, 32);

		addr_sp -= fdt_size;
		new_fdt = (void *)addr_sp;
		debug("Reserving %zu Bytes for FDT at: %08lx\n",
		      fdt_size, addr_sp);
	}
#endif

#ifndef CONFIG_ARM64
	/* setup stackpointer for exeptions */
	gd->irq_sp = addr_sp;
#ifdef CONFIG_USE_IRQ
	addr_sp -= (CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ);
	debug("Reserving %zu Bytes for IRQ stack at: %08lx\n",
		CONFIG_STACKSIZE_IRQ+CONFIG_STACKSIZE_FIQ, addr_sp);
#endif
	/* leave 3 words for abort-stack    */
	addr_sp -= 12;

	/* 8-byte alignment for ABI compliance */
	addr_sp &= ~0x07;
#else	/* CONFIG_ARM64 */
	/* 16-byte alignment for ABI compliance */
	addr_sp &= ~0x0f;
#endif	/* CONFIG_ARM64 */
#else
	addr_sp += 128;	/* leave 32 words for abort-stack   */
	gd->irq_sp = addr_sp;
#endif

	debug("New Stack Pointer is: %08lx\n", addr_sp);

#ifdef CONFIG_POST
	post_bootmode_init();
	post_run(NULL, POST_ROM | post_bootmode_get(0));
#endif

	/* Ram ist board specific, so move it to board code ... */
	dram_init_banksize();
	display_dram_config();	/* and display it */
#if defined(CONFIG_NO_RELOCATION) && defined(CONFIG_ARM64)
	gd->relocaddr = (ulong)&_start;
	gd->start_addr_sp = CONFIG_SYS_INIT_SP_ADDR;
	gd->reloc_off = 0;
	debug("gd:relocaddr0x%lx, start_addr_sp:0x%lx, reloc_off:0x%lx, id:0x%p\n",
		gd->relocaddr, gd->start_addr_sp, gd->reloc_off, id);
	debug("Don't do relocation!\n");
#elif defined(CONFIG_NO_RELOCATION) /* ARMv7A part */
	gd->relocaddr = (ulong)&_start;
	gd->start_addr_sp = CONFIG_SYS_INIT_SP_ADDR;
	gd->reloc_off = 0;

	id = (void*)CONFIG_SYS_INIT_SP_ADDR;
	gd->bd = (void*)(CONFIG_SYS_INIT_SP_ADDR + sizeof(gd_t));
	memcpy(gd->bd, bd, sizeof(bd_t));
	debug("gd->bd:0x%p relocaddr0x%lx, start_addr_sp:0x%lx, reloc_off:0x%lx, id:0x%p\n",
		gd->bd, gd->relocaddr, gd->start_addr_sp, gd->reloc_off, id);
	debug("Don't do relocation!\n");
#else
	gd->relocaddr = addr;
	gd->start_addr_sp = addr_sp;
	gd->reloc_off = addr - (ulong)&_start;
	debug("relocation Offset is: %08lx\n", gd->reloc_off);
#endif //CONFIG_NO_RELOCATION
	if (new_fdt) {
		memcpy(new_fdt, gd->fdt_blob, fdt_size);
		gd->fdt_blob = new_fdt;
	}
	memcpy(id, (void *)gd, sizeof(gd_t));
}

#if !defined(CONFIG_SYS_NO_FLASH)
static char *failed = "*** failed ***\n";
#endif

/*
 * Tell if it's OK to load the environment early in boot.
 *
 * If CONFIG_OF_CONFIG is defined, we'll check with the FDT to see
 * if this is OK (defaulting to saying it's not OK).
 *
 * NOTE: Loading the environment early can be a bad idea if security is
 *       important, since no verification is done on the environment.
 *
 * @return 0 if environment should not be loaded, !=0 if it is ok to load
 */
static int should_load_env(void)
{
#ifdef CONFIG_OF_CONTROL
	return fdtdec_get_config_int(gd->fdt_blob, "load-environment", 1);
#elif defined CONFIG_DELAY_ENVIRONMENT
	return 0;
#else
	return 1;
#endif
}

#if defined(CONFIG_DISPLAY_BOARDINFO_LATE) && defined(CONFIG_OF_CONTROL)
static void display_fdt_model(const void *blob)
{
	const char *model;

	model = (char *)fdt_getprop(blob, 0, "model", NULL);
	printf("Model: %s\n", model ? model : "<unknown>");
}
#endif


void set_shared_memory_for_communication_with_ACPU(void)
{
	unsigned svn_number = 0, svn_len = 0, i=0, mul_base = 1;
	char *start_ptr = NULL, *end_ptr = NULL;

	memset(&ipc_shm,0x0,sizeof(ipc_shm));
	memset(&ipc_ir,0x0,sizeof(ipc_ir));
	
	// fill the UART register base address for A/V CPU.
	ipc_shm.sys_assign_serial = SWAPEND32(CONFIG_SYS_NS16550_COM1 | 0xc0000000);
	// VIDEO FORMAT PTR ADDRESS
	ipc_shm.pov_boot_vd_std_ptr = SWAPEND32(VO_RESOLUTION);
	// u-boot version MAGIC pass to FW 'svn\0'
	ipc_shm.u_boot_version_magic = SWAPEND32(0x73766e00);
	// u-boot SVN number pass to FW
	if((start_ptr = strstr(U_BOOT_VERSION, "-svn"))) {
		start_ptr +=4;
		if((end_ptr = strchr(start_ptr, ' ')))
			svn_len = end_ptr - start_ptr;
		else
			svn_len = strlen(start_ptr);
		
		for(i = 0 ; i < svn_len ; i++) {
			svn_number += (start_ptr[svn_len-i-1] - '0') * mul_base;
			mul_base *= 10;
		}
	} else {
		svn_number = 0;
	}
	ipc_shm.u_boot_version_info = SWAPEND32(svn_number);
#ifdef CONFIG_ACPU_LOGBUF_ENABLE
	struct acpu_syslog_struct *alog_p = (struct acpu_syslog_struct*)&ipc_shm.printk_buffer[0];
	alog_p->log_buf_addr = CONFIG_ACPU_LOGBUF_ADDR;
	alog_p->log_buf_len = CONFIG_ACPU_LOGBUF_SIZE;
	debug("%s: ACPU logbuf addr:0x%08x, size:0x%08x\n",
		__func__, CONFIG_ACPU_LOGBUF_ADDR, CONFIG_ACPU_LOGBUF_SIZE);
#endif /* CONFIG_ACPU_LOGBUF_ENABLE */
}

/************************************************************************
 *
 * This is the next part if the initialization sequence: we are now
 * running from RAM and have a "normal" C environment, i. e. global
 * data can be written, BSS has been cleared, the stack size in not
 * that critical any more, etc.
 *
 ************************************************************************
 */

void board_init_r(gd_t *id, ulong dest_addr)
{
	ulong malloc_start;
#if !defined(CONFIG_SYS_NO_FLASH)
	ulong flash_size;
#endif


#ifdef CONFIG_REALTEK_WATCHDOG
	WATCHDOG_KICK();
	puts("Watchdog: Enabled\n");
#else
	puts("Watchdog: Disabled\n");
#endif

	gd = id;

	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */
	bootstage_mark_name(BOOTSTAGE_ID_START_UBOOT_R, "board_init_r");

	monitor_flash_len = (ulong)&__rel_dyn_end - (ulong)_start;

	/* Enable caches */
	enable_caches();
#ifdef CONFIG_SYS_NONCACHED_MEMORY
	noncached_init();
#endif

	debug("monitor flash len: %08lX\n", monitor_flash_len);
	/*
	 * TODO: printing of the clock inforamtion of the board is now
	 * implemented as part of bdinfo command. Currently only support for
	 * davinci SOC's is added. Remove this check once all the board
	 * implement this.
	 */
#ifdef CONFIG_CLOCKS
	set_cpu_clk_info(); /* Setup clock information */
#endif
	serial_initialize();

	debug("Now running in RAM - U-Boot at: %08lx\n", dest_addr);

#ifdef CONFIG_LOGBUFFER
	logbuff_init_ptrs();
#endif
#ifdef CONFIG_POST
	post_output_backlog();
#endif

#ifndef CONFIG_NO_RELOCATION
	/* The Malloc area is immediately below the monitor copy in DRAM */
	malloc_start = dest_addr - TOTAL_MALLOC_LEN;
#else
	/* RTK disable Relocation */
	malloc_start = CONFIG_HEAP_ADDR;
#endif //CONFIG_NO_RELOCATION
	mem_malloc_init (malloc_start, TOTAL_MALLOC_LEN);
	//mem_malloc_noncache_init(UBOOT_NONCACHE_MEMORY_ADDR, (1 << 20));


//**************************************************************************
/*
 *********************************************************
 * Realtek Patch:
 *	Copy several mips codes from .data section
 *	to specific ddr region for A/V CPU use.
 *********************************************************
 */
#ifdef CONFIG_BSP_REALTEK
{
#ifndef CONFIG_POWER_DOWN_MD
	unsigned char *a,*b;

	// copy .exc_redirect (MIPS exception redirect)
	a = (unsigned char *)_e_exc_redirect_img;
	b = (unsigned char *)_f_exc_redirect_img;
	md_memcpy((unsigned char *)MIPS_EXC_REDIRECT_CODE_ADDR, b, a-b);

	// copy .exc_dispatch (MIPS exception dispatch)
	a = (unsigned char *)_e_exc_dispatch_img;
	b = (unsigned char *)_f_exc_dispatch_img;
	md_memcpy((unsigned char *)MIPS_EXC_DISPATCH_CODE_ADDR, b, a-b);

	// copy .isrvideoimg (video cpu isr handler)
	a = (unsigned char *)_e_isrvideo_img;
	b = (unsigned char *)_f_isrvideo_img;
	md_memcpy((unsigned char *)MIPS_ISR_VIDEO_IMG_ADDR, b, a-b);

	// copy .rosbootvectorimg (MIPS vector interrupt)
	a = (unsigned char *)_e_rosbootvector_img;
	b = (unsigned char *)_f_rosbootvector_img;
	md_memcpy((unsigned char *)MIPS_ROS_BOOT_VECTOR_IMG_ADDR, b, a-b);

	// copy .a_entry (ACPU bootcode)
	a = (unsigned char *)_e_a_entry_img;
	b = (unsigned char *)_f_a_entry_img;
	md_memcpy((unsigned char *)MIPS_A_ENTRY_CODE_ADDR, b, a-b);

	// fill the ACPU jump address.
	// After ACPU got HW semaphore in rom code, it will check this register.
	rtd_outl(ACPU_JUMP_ADDR_reg,SWAPEND32( MIPS_A_ENTRY_CODE_ADDR | MIPS_KSEG1BASE));
	rtd_outl(ISO_RESERVED_USE_3,MIPS_A_ENTRY_CODE_ADDR | MIPS_KSEG1BASE);
#endif

	set_shared_memory_for_communication_with_ACPU();
}
#endif	/* CONFIG_BSP_REALTEK */
//**************************************************************************

	power_init_board();

#if !defined(CONFIG_SYS_NO_FLASH)
	puts("Flash: ");

	flash_size = flash_init();
	if (flash_size > 0) {
# ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size(flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		if (getenv_yesno("flashchecksum") == 1) {
			printf("  CRC: %08X", crc32(0,
				(const unsigned char *) CONFIG_SYS_FLASH_BASE,
				flash_size));
		}
		putc('\n');
# else	/* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size(flash_size, "\n");
# endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts(failed);
		hang();
	}
#endif

#if defined(CONFIG_RTKSPI) && defined(CONFIG_CMD_RTKSPI)
	extern void rtkspi_init(void);
	rtkspi_init();		/* SPI initial */
#endif

#if defined(CONFIG_CMD_NAND)
	puts("NAND:  ");
	nand_init();		/* go init the NAND */
#endif

#if defined(CONFIG_CMD_ONENAND)
	onenand_init();
#endif

#ifdef CONFIG_RTK_MMC
	puts("MMC:   ");
#ifdef RTK_eMMC_FAST_MODE
	printf("Initialize eMMC in fast flow\n");
	if(rtk_eMMC_init() < 0) {
		printf("[ERR] bringup mmc failed.\n");
	}
#else /* RTK_eMMC_TRADITIONAL_MODE */
	printf("Initialize eMMC in traditional mmc flow.\n");
	mmc_initialize(gd->bd);
	if(bringup_mmc_driver() < 0) {
		printf("[ERR] bringup mmc failed\n");
		bpi_boot=0; // 0: SD 1: eMMC
	}
#endif
#endif

#ifdef CONFIG_RTK_SD
	puts("SD:\n");
	sd_initialize(gd->bd);
#ifdef CONFIG_SYS_RTK_SD_FLASH
	extern int sd_card_init(void);
	if( sd_card_init() != 0 ) {
		puts("SD: initialize card failed\n");
		bpi_boot=1; // 0: SD 1: eMMC
	}
#endif /* CONFIG_SYS_RTK_SD_FLASH */
#endif /* CONFIG_RTK_SD */

//****************************************************************
#ifdef CONFIG_BSP_REALTEK
	pcb_get_boot_flash_type();
#ifdef CONFIG_SYS_FACTORY
	puts("Factory: ");
	factory_init();
	get_bootparam();
#ifdef CONFIG_SYS_FACTORY_READ_ONLY
	puts("Factory RO: ");
	factory_ro_init();
#endif
#endif
#endif /* CONFIG_BSP_REALTEK */
//****************************************************************

	/* Doing board init after flash and factory_init */
	board_init();

#ifdef CONFIG_CMD_SCSI
	puts("SCSI:  ");
	scsi_init();
#endif

#ifdef CONFIG_HAS_DATAFLASH
	AT91F_DataflashInit();
	dataflash_print_info();
#endif

	/* initialize environment */
	if (should_load_env())
		env_relocate();
	else
		set_default_env(NULL);

#ifdef BPI
#else
	if(bpi_boot) {
		setenv("device", "mmc");
		setenv("sdmmc_on", "0"); // disable rtk_sdmmc
	}
	else {
		setenv("sdmmc_on", "1");
	}
#endif
#if defined(CONFIG_CMD_PCI) || defined(CONFIG_PCI)
	arm_pci_init();
#endif

	stdio_init();	/* get the devices list going. */

	jumptable_init();

#if defined(CONFIG_API)
	/* Initialize API */
	api_init();
#endif

	console_init_r();	/* fully init console as a device */

#ifdef CONFIG_DISPLAY_BOARDINFO_LATE
# ifdef CONFIG_OF_CONTROL
	/* Put this here so it appears on the LCD, now it is ready */
	display_fdt_model(gd->fdt_blob);
# else
	checkboard();
# endif
#endif

#ifdef CONFIG_CUSTOMIZE_NEMO
	/* Turn on HDMITX 5V */
	setISOGPIO(52, 1);
#endif

#ifdef CONFIG_HDMITX_MODE
	if(CONFIG_HDMITX_MODE==0)//HDMI TX always off
		set_hdmi_off();
	else
		sink_capability_handler(1);
#endif
#ifdef CONFIG_DPTX_MODE
	if(CONFIG_DPTX_MODE==1)
		dptx_sink_capability_handler(1);
#endif

#if defined(CONFIG_ARCH_MISC_INIT)
	/* miscellaneous arch dependent initialisations */
	arch_misc_init();
#endif
#if defined(CONFIG_MISC_INIT_R)
	/* miscellaneous platform dependent initialisations */
	misc_init_r();
#endif

	 /* set up exceptions */
	interrupt_init();
	/* enable exceptions */
	enable_interrupts();

	/* Initialize from environment */
	load_addr = getenv_ulong("loadaddr", 16, load_addr);

#if defined(CONFIG_BOARD_WD_MONARCH)||defined(CONFIG_BOARD_WD_PELICAN)
#if defined(CONFIG_RTK_PWM)
    /**
       @WD_Changes_begin
       Enable the LED at 50% at the beginning of uboot
     **/
    rtk_pwm_init();
    // enable the LED at the earlier boot
    pwm_set_duty_rate(SYS_LED_PWM_PORT_NUM, 50);
    pwm_enable(SYS_LED_PWM_PORT_NUM, 1);
#ifdef CONFIG_BOARD_WD_PELICAN
    // for pelican, turn on the FAN
    //pwm_set_duty_rate(FAN_PWM_PORT_NUM, 100);  // set the FAN speed to 100%
    pwm_set_duty_rate(FAN_PWM_PORT_NUM, 20);  // set the FAN speed to 100%
    pwm_enable(FAN_PWM_PORT_NUM, 1);
#endif /* CONFIG_BOARD_WD_PELICAN */
#endif /* CONFIG_RTK_PWM */
#endif /* CONFIG_BOARD_WD_MONARCH */ /* CONFIG_BOARD_WD_PELICAN */

#if defined(CONFIG_RTK_LSADC)
    rtk_lsadc_init();
#endif /* CONFIG_RTK_LSADC */

#ifdef CONFIG_BOARD_LATE_INIT
	board_late_init();
#endif

#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif


#ifndef CONFIG_POWER_DOWN_ETN
#if defined(CONFIG_CMD_NET)
	puts("Net:   ");
#ifdef CONFIG_BSP_REALTEK
	rtl8168_initialize(gd->bd);
#else
	eth_initialize(gd->bd);
#endif
#if defined(CONFIG_RESET_PHY_R)
	debug("Reset Ethernet PHY\n");
	reset_phy();
#endif
#endif //CONFIG_CMD_NET
#endif //CONFIG_POWER_DOWN_ETN



#ifdef CONFIG_POST
	post_run(NULL, POST_RAM | post_bootmode_get(0));
#endif

#if defined(CONFIG_PRAM) || defined(CONFIG_LOGBUFFER)
	/*
	 * Export available size of memory for Linux,
	 * taking into account the protected RAM at top of memory
	 */
	{
		ulong pram = 0;
		uchar memsz[32];

#ifdef CONFIG_PRAM
		pram = getenv_ulong("pram", 10, CONFIG_PRAM);
#endif
#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
		/* Also take the logbuffer into account (pram is in kB) */
		pram += (LOGBUFF_LEN + LOGBUFF_OVERHEAD) / 1024;
#endif
#endif
		sprintf((char *)memsz, "%ldk", (gd->ram_size / 1024) - pram);
		setenv("mem", (char *)memsz);
	}
#endif

	/* main_loop() can return to retry autoboot, if so just run it again. */
	for (;;) {
		main_loop();
	}

	/* NOTREACHED - no way out of command loop except booting */
}
