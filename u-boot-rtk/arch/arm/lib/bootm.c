/* Copyright (C) 2011
 * Corscience GmbH & Co. KG - Simon Schwarz <schwarz@corscience.de>
 *  - Added prep subcommand support
 *  - Reorganized source - modeled after powerpc version
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * Copyright (C) 2001  Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <libfdt.h>
#include <mapmem.h>
#include <fdt_support.h>
#include <asm/bootm.h>
#include <asm/secure.h>
#include <asm/arch/cpu.h>
#include <asm/io.h>
#include <linux/compiler.h>
#include <bootm.h>
#include <vxworks.h>
#include <asm/arch/fw_info.h>
#include <stdlib.h>

#ifdef CONFIG_ARMV7_NONSEC
#include <asm/armv7.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern BOOT_MODE boot_mode;
extern unsigned int Auto_AFW_MEM_START;

#ifdef CONFIG_RTD1295
#if defined(CONFIG_SYS_RTK_SPI_FLASH) || defined(CONFIG_SYS_RTK_SD_FLASH) || defined(CONFIG_SYS_NO_BL31)
	static int spi_boot_flow = 1;
#else
	static int spi_boot_flow = 0;
#endif
#endif

static struct tag *params;

static ulong get_sp(void)
{
	ulong ret;

	asm("mov %0, sp" : "=r"(ret) : );
	return ret;
}

#ifdef CONFIG_TARGET_RTD1295
static void (*bl31_entrypoint) (void* para1, void* para2) = (void*)BL31_ENTRY_ADDR;
#endif


void arch_lmb_reserve(struct lmb *lmb)
{
	ulong sp;

	/*
	 * Booting a (Linux) kernel image
	 *
	 * Allocate space for command line and board info - the
	 * address should be as high as possible within the reach of
	 * the kernel (see CONFIG_SYS_BOOTMAPSZ settings), but in unused
	 * memory, which means far enough below the current stack
	 * pointer.
	 */
	sp = get_sp();
	debug("## Current stack ends at 0x%08lx ", sp);

	/* adjust sp by 4K to be safe */
	sp -= 4096;
	lmb_reserve(lmb, sp,
		    gd->bd->bi_dram[0].start + gd->bd->bi_dram[0].size - sp);
}

/**
 * announce_and_cleanup() - Print message and prepare for kernel boot
 *
 * @fake: non-zero to do everything except actually boot
 */
static void announce_and_cleanup(int fake)
{
#ifdef CONFIG_TARGET_RTD1295
	if (get_rtd129x_cpu_revision() == RTD129x_CHIP_REVISION_A01 && !spi_boot_flow)
		printf("Jump to BL31 entrypoint\n");
	else{
		printf("\nStarting %s ...%s\n\n", (getenv("hyp_loadaddr") ? "Hypervisor" : "Kernel"), (fake ?
			"(fake run for tracing)" : ""));
	}
#else // !CONFIG_TARGET_RTD1295
	printf("\nStarting %s ...%s\n\n", (getenv("hyp_loadaddr") ? "Hypervisor" : "Kernel"), (fake ?
		"(fake run for tracing)" : ""));
#endif //CONFIG_TARGET_RTD1295

	bootstage_mark_name(BOOTSTAGE_ID_BOOTM_HANDOFF, "start_kernel");
#ifdef CONFIG_BOOTSTAGE_FDT
	bootstage_fdt_add_report();
#endif
#ifdef CONFIG_BOOTSTAGE_REPORT
	bootstage_report();
#endif

#ifdef CONFIG_USB_DEVICE
	udc_disconnect();
#endif
	cleanup_before_linux();
}

static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *)bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

static void setup_memory_tags(bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem32);

		params->u.mem.start = bd->bi_dram[i].start;
		params->u.mem.size = bd->bi_dram[i].size;

		params = tag_next (params);
	}
}

static void setup_commandline_tag(bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

static void setup_initrd_tag(bd_t *bd, ulong initrd_start, ulong initrd_end)
{
	/* an ATAG_INITRD node tells the kernel where the compressed
	 * ramdisk can be found. ATAG_RDIMG is a better name, actually.
	 */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size (tag_initrd);

	params->u.initrd.start = initrd_start;
	params->u.initrd.size = initrd_end - initrd_start;

	params = tag_next (params);
}

static void setup_serial_tag(struct tag **tmp)
{
	struct tag *params = *tmp;
	struct tag_serialnr serialnr;

	get_board_serial(&serialnr);
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = serialnr.low;
	params->u.serialnr.high= serialnr.high;
	params = tag_next (params);
	*tmp = params;
}

static void setup_revision_tag(struct tag **in_params)
{
	u32 rev = 0;

	rev = get_board_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}

static void setup_end_tag(bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

__weak void setup_board_tags(struct tag **in_params) {}

#ifdef CONFIG_ARM64
static void do_nonsec_virt_switch(void)
{
#ifdef CONFIG_ARMV8_MULTIENTRY
	smp_kick_all_cpus();
#endif
	dcache_disable();	/* flush cache before swtiching to EL2 */
#ifdef CONFIG_TARGET_RTD1295
	if (get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_A01 || spi_boot_flow)
#endif //CONFIG_TARGET_RTD1295
		armv8_switch_to_el2();

#ifdef CONFIG_ARMV8_SWITCH_TO_EL1
	armv8_switch_to_el1();
#endif
}
#endif

#ifdef CONFIG_SYS_RTK_NAND_FLASH
/**********************************************************
 * Append the information of partition to bootargs.
 **********************************************************/
extern char rtknand_info[128];
int rtk_plat_boot_prep_partition(void)
{
#if defined(CONFIG_RTD1295) && defined(NAS_ENABLE)
	if(boot_mode == BOOT_RESCUE_MODE)
		return 0;

	char *kernelargs= NULL;
	char *tmp_cmdline = NULL;
	char *mtd_part = NULL;

	kernelargs= getenv("kernelargs")?:"";
	mtd_part = getenv("mtd_part")?:"";

	tmp_cmdline = (char *)malloc(strlen(kernelargs)+strlen(mtd_part)+strlen(rtknand_info)+3);
	if (!tmp_cmdline) {
		printf("%s: Malloc failed\n", __func__);
	}
	else {
		sprintf(tmp_cmdline, "%s %s %s", kernelargs, mtd_part, rtknand_info);
		setenv("kernelargs", tmp_cmdline);
		free(tmp_cmdline);
	}
	debug("%s\n",getenv("kernelargs"));
#else
	char *commandline = NULL;
	char *tmp_cmdline = NULL;
	char *mtd_part = NULL;
#ifdef CONFIG_CUSTOMIZE_NEMO
	commandline = getenv("bootargs")?:"dev=1 earlycon=uart8250,mmio32,0x98007800 console=ttyS0,115200 loglevel=4 ubi.mtd=1 rootfstype=ubifs rw root=ubi0_0";
#else
	commandline = getenv("bootargs")?:"";
#endif
	mtd_part = getenv("mtd_part")?:"";

	tmp_cmdline = (char *)malloc(strlen(commandline)+strlen(mtd_part)+strlen(rtknand_info)+3);
	if (!tmp_cmdline) {
                printf("%s: Malloc failed\n", __func__);
        }
        else {
                sprintf(tmp_cmdline, "%s %s %s ", commandline, mtd_part, rtknand_info);
                setenv("bootargs", tmp_cmdline);
                free(tmp_cmdline);
        }
        debug("%s\n",getenv("bootargs"));
#endif

	return 0;
}
#endif

#if defined(NAS_ENABLE)

/*****************************************************************************
 * This function is a template code for creating customized boot arguments.
 * It provides room for customers to append programmable arguments.
 * For example, the path of boot device might be
 * "/dev/mmcblk0p0" or "/dev/mmcblk0p1", depending on circumstances.
 * This can be done as follows:
 *
 * if (case_boot_part_zero)
 *     part_num=0;
 * else
 *     part_num=1;
 * sprintf( custom_boot_args, "root=%s%d", device_path, part_num );
 * 
 * where the variable "device_path" is "/dev/mmcblk0p" and 
 * "part_num" is the boot partition index.
 *****************************************************************************/
int set_custom_boot_args(char custom_boot_args[]) 
{
	return 0;
}

extern uint initrd_size;
/*****************************************************************************
 * Overwrite kernelargs in rescue mode & appending customized boot arguments
 *****************************************************************************/
int rtk_plat_boot_prep_kernelargs(void)
{
	char *kernelargs = getenv("kernelargs");
	char *temp_args = NULL;
	char custom_boot_args[256]={0};
	char empty_str[1]={0};

	// clear kernelargs variable for rescue mode
	if (boot_mode == BOOT_RESCUE_MODE) {
		kernelargs = empty_str;
		setenv("kernelargs", kernelargs);
	}
	if (!kernelargs)
	    return 0;
	
	set_custom_boot_args(custom_boot_args);
	if(strlen(custom_boot_args) == 0) {
		debug("No custom boot flag.\n");
	}
	else {
		// Need 2 extra bytes for space and null character.
		temp_args = malloc(strlen(kernelargs) + strlen(custom_boot_args) + 2);
		if(!temp_args) {
			printf("%s: Malloc failed\n", __func__);
		}
		else {
			sprintf(temp_args, "%s %s", kernelargs, custom_boot_args);
			setenv("kernelargs", temp_args);
			free(temp_args);
		}
	}
	debug("%s\n",getenv("kernelargs"));

	return 0;
}
#endif

/* Subcommand: PREP */
static void boot_prep_linux(bootm_headers_t *images)
{
	char *commandline = getenv("bootargs");

	if (IMAGE_ENABLE_OF_LIBFDT && images->ft_len) {
#ifdef CONFIG_OF_LIBFDT
		debug("using: FDT\n");
		if (image_setup_linux(images)) {
			printf("FDT creation failed! hanging...");
			hang();
		}
#endif
	} else if (BOOTM_ENABLE_TAGS) {
		debug("using: ATAGS\n");
		setup_start_tag(gd->bd);
		if (BOOTM_ENABLE_SERIAL_TAG)
			setup_serial_tag(&params);
		if (BOOTM_ENABLE_CMDLINE_TAG)
			setup_commandline_tag(gd->bd, commandline);
		if (BOOTM_ENABLE_REVISION_TAG)
			setup_revision_tag(&params);
		if (BOOTM_ENABLE_MEMORY_TAGS)
			setup_memory_tags(gd->bd);
		if (BOOTM_ENABLE_INITRD_TAG) {
			if (images->rd_start && images->rd_end) {
				setup_initrd_tag(gd->bd, images->rd_start,
						 images->rd_end);
			}
		}
		setup_board_tags(&params);
		setup_end_tag(gd->bd);
	} else {
		printf("FDT and ATAGS support not compiled in - hanging\n");
		hang();
	}
}

#ifdef CONFIG_ARMV7_NONSEC
bool armv7_boot_nonsec(void)
{
	char *s = getenv("bootm_boot_mode");
#ifdef CONFIG_ARMV7_BOOT_SEC_DEFAULT
	bool nonsec = false;
#else
	bool nonsec = true;
#endif

	if (s && !strcmp(s, "sec"))
		nonsec = false;

	if (s && !strcmp(s, "nonsec"))
		nonsec = true;

	return nonsec;
}
#endif

#ifdef CONFIG_ACPU_LOGBUF_ENABLE
static int reserve_acpu_logbuf(void *blob)
{
	int i;
	uint64_t addr, size;
	uint64_t r_start, r_end;
	uint64_t alog_start, alog_end;
	int total;

	/* First, check if memory region had alreay been reserved */
	alog_start = CONFIG_ACPU_LOGBUF_ADDR;
	alog_end = CONFIG_ACPU_LOGBUF_ADDR + CONFIG_ACPU_LOGBUF_SIZE;
	total = fdt_num_mem_rsv(blob);

	for (i = 0; i < total; i++) {
		fdt_get_mem_rsv(blob, i, &addr, &size);
		r_start = addr;
		r_end = addr + size;
		if (alog_end <= r_start || alog_start >= r_end)
			continue;
		printf("## ERROR, ACPU logbuf region already used\n");
		debug("## rsvmem: 0x%08llx-0x%08llx, alog:0x%08llx-0x%08llx\n",
			r_start, r_end, alog_start, alog_end);
		return -1;
	}

	fdt_add_mem_rsv(blob, CONFIG_ACPU_LOGBUF_ADDR, CONFIG_ACPU_LOGBUF_SIZE);

	return 0;
}
#else /* !CONFIG_ACPU_LOGBUF_ENABLE */
static inline int reserve_acpu_logbuf(void *blob) {return 0;}
#endif /* CONFIG_ACPU_LOGBUF_ENABLE */

/* Subcommand: GO */
static void boot_jump_linux(bootm_headers_t *images, int flag)
{
	int err;

#ifdef CONFIG_RTK_SLAVE_CPU_BOOT
	bootup_slave_cpu();
#endif

#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
	char *fdt_addr_str = NULL;
	void *fdt_addr;

	if ((fdt_addr_str = getenv("fdt_loadaddr")) == NULL) {
		fdt_addr_str = (char*) CONFIG_FDT_LOADADDR;
	}
	fdt_addr = (void*) simple_strtoul(fdt_addr_str, NULL, 16);

	if (fdt_addr) {
		if (fdt_rsv_mem_for_ion_exist(fdt_addr) >= 0) {
#endif
	if(!Auto_AFW_MEM_START)
		Auto_AFW_MEM_START = AFW_MEM_START_ADDR;
	 /* If AFW load failed, using default address of AFW. */

	err = fdt_add_mem_rsv(images->ft_addr, Auto_AFW_MEM_START, AFW_MEM_SIZE);
	if (err < 0)
		printf("## WARNING %s Add AFW_MEMRSV: %s\n", __func__, fdt_strerror(err));
#if defined(NAS_ENABLE) && defined(CONFIG_RTD161x)
		}
	}
#endif

/* Bootcode is part of suspend/resume flow of Kylin, this mem region has to be reserved */
#ifdef CONFIG_RTD1295
	err = fdt_add_mem_rsv(images->ft_addr, UBOOT_MEM_START_ADDR, UBOOT_MEM_SIZE);
	if (err < 0)
		printf("## WARNING %s Add UBOOT_MEMRSV: %s\n", __func__, fdt_strerror(err));
#endif

#ifndef CONFIG_SYS_NON_TEE
	err = fdt_add_mem_rsv(images->ft_addr, TEE_MEM_START_ADDR, TEE_MEM_SIZE);
	if (err < 0)
		printf("## WARNING %s Add TEE_MEMRSV: %s\n", __func__, fdt_strerror(err));
#endif
	if (reserve_acpu_logbuf(images->ft_addr))
		return;
#ifdef CONFIG_ARM64
	void (*kernel_entry)(void *fdt_addr, void *res0, void *res1,
			void *res2);
	int fake = (flag & BOOTM_STATE_OS_FAKE_GO);
	kernel_entry = (void (*)(void *fdt_addr, void *res0, void *res1,
				void *res2))images->ep;
	debug("## Transferring control to Linux (at address %lx)...\n",
		(ulong) kernel_entry);
	bootstage_mark(BOOTSTAGE_ID_RUN_OS);

	announce_and_cleanup(fake);

	if (!fake) {
		do_nonsec_virt_switch();
#ifdef CONFIG_TARGET_RTD1295
		//Just A01 need to go this flow, because A00 dosen't have the security and 
		//the security of B00 is done before EL2 which not need bl31 again. 
		if (get_rtd129x_cpu_revision() == RTD129x_CHIP_REVISION_A01 && !spi_boot_flow) {
			bl31_entrypoint(kernel_entry, images->ft_addr);
		} else {
			kernel_entry(images->ft_addr, NULL, NULL, NULL);
		}
#else // !CONFIG_TARGET_RTD1295
#ifdef CONFIG_RTK_ARM32
		armv8_switch_to_el1_aarch(0, (u64)gd->bd->bi_arch_number,
		    (u64)images->ft_addr, 0,
		    (u64)images->ep,
		    ES_TO_AARCH32);
#endif
		kernel_entry(images->ft_addr, NULL, NULL, NULL);
#endif // CONFIG_TARGET_RTD1295
	}
#else
	unsigned long machid = gd->bd->bi_arch_number;
	char *s;
	void (*kernel_entry)(int zero, int arch, uint params);
	unsigned long r2;
	int fake = (flag & BOOTM_STATE_OS_FAKE_GO);

	kernel_entry = (void (*)(int, int, uint))images->ep;

	s = getenv("machid");
	if (s) {
		strict_strtoul(s, 16, &machid);
		printf("Using machid 0x%lx from environment\n", machid);
	}

	debug("## Transferring control to Linux (at address %08lx)" \
		"...\n", (ulong) kernel_entry);
	bootstage_mark(BOOTSTAGE_ID_RUN_OS);
	announce_and_cleanup(fake);

	if (IMAGE_ENABLE_OF_LIBFDT && images->ft_len)
		r2 = (unsigned long)images->ft_addr;
	else
		r2 = gd->bd->bi_boot_params;

	if (!fake) {
#ifdef CONFIG_ARMV7_NONSEC
		if (armv7_boot_nonsec()) {
			armv7_init_nonsec();
			secure_ram_addr(_do_nonsec_entry)(kernel_entry,
							  0, machid, r2);
		} else
#endif
			kernel_entry(0, machid, r2);
	}
#endif
}

/* Main Entry point for arm bootm implementation
 *
 * Modeled after the powerpc implementation
 * DIFFERENCE: Instead of calling prep and go at the end
 * they are called if subcommand is equal 0.
 */
int do_bootm_linux(int flag, int argc, char * const argv[],
		   bootm_headers_t *images)
{
	/* No need for those on ARM */
	if (flag & BOOTM_STATE_OS_BD_T || flag & BOOTM_STATE_OS_CMDLINE)
		return -1;

	if (flag & BOOTM_STATE_OS_PREP) {
		boot_prep_linux(images);
		return 0;
	}

	if (flag & (BOOTM_STATE_OS_GO | BOOTM_STATE_OS_FAKE_GO)) {
		boot_jump_linux(images, flag);
		return 0;
	}

	boot_prep_linux(images);
	boot_jump_linux(images, flag);
	return 0;
}

#ifdef CONFIG_CMD_BOOTZ

struct zimage_header {
	uint32_t	code[9];
	uint32_t	zi_magic;
	uint32_t	zi_start;
	uint32_t	zi_end;
};

#define	LINUX_ARM_ZIMAGE_MAGIC	0x016f2818

int bootz_setup(ulong image, ulong *start, ulong *end)
{
	struct zimage_header *zi;

	zi = (struct zimage_header *)map_sysmem(image, 0);
	if (zi->zi_magic != LINUX_ARM_ZIMAGE_MAGIC) {
		puts("Bad Linux ARM zImage magic!\n");
		return 1;
	}

	*start = zi->zi_start;
	*end = zi->zi_end;

	printf("Kernel image @ %#08lx [ %#08lx - %#08lx ]\n", image, *start,
	      *end);

	return 0;
}

#endif	/* CONFIG_CMD_BOOTZ */

#if defined(CONFIG_BOOTM_VXWORKS)
void boot_prep_vxworks(bootm_headers_t *images)
{
#if defined(CONFIG_OF_LIBFDT)
	int off;

	if (images->ft_addr) {
		off = fdt_path_offset(images->ft_addr, "/memory");
		if (off < 0) {
			if (arch_fixup_fdt(images->ft_addr))
				puts("## WARNING: fixup memory failed!\n");
		}
	}
#endif
	cleanup_before_linux();
}
void boot_jump_vxworks(bootm_headers_t *images)
{
	/* ARM VxWorks requires device tree physical address to be passed */
	((void (*)(void *))images->ep)(images->ft_addr);
}
#endif
