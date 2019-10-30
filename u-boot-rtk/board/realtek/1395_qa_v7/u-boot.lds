/*
 * Copyright (c) 2004-2008 Texas Instruments
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x00000000;

	. = ALIGN(4);
	.text :
	{
		*(.__image_copy_start)
		*(.vectors)
		CPUDIR/start.o (.text*)
		*(.text*)
	}

	. = ALIGN(4);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(4);
	.data : {
		*(.data*)
	}

	. = ALIGN(4);

	. = .;

	. = ALIGN(4);
	.u_boot_list : {
		KEEP(*(SORT(.u_boot_list*)));
	}

	/********* Insert A/V CPU related image start *********/
	. = ALIGN(8);

	.redirect_img_start : {
		KEEP(*(.__redirect_img_start));
	}

	.redirect_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.exc_redirect))
		. = ALIGN(8);
	}

	. = .;

	.redirect_img_end : {
		KEEP(*(.__redirect_img_end));
	}


	.dispatch_img_start : {
		KEEP(*(.__dispatch_img_start));
	}

	.dispatch_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.exc_dispatch))
		. = ALIGN(8);
	}

	. = .;

	.dispatch_img_end : {
		KEEP(*(.__dispatch_img_end));
	}

	.a_entry_img_start : {
		KEEP(*(.__a_entry_img_start));
	}

	.a_entry_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.a_entry))
		. = ALIGN(8);
	}

	. = .;

	.a_entry_img_end : {
		KEEP(*(.__a_entry_img_end));
	}

	.v_entry_img_start : {
		KEEP(*(.__v_entry_img_start));
	}

	.v_entry_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.v_entry))
		. = ALIGN(8);
	}

	. = .;

	.v_entry_img_end : {
		KEEP(*(.__v_entry_img_end));
	}

	.isrvideo_img_start : {
		KEEP(*(.__isrvideo_img_start));
	}

	.isrvideo_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.isrvideoimg))
		. = ALIGN(8);
	}

	. = .;

	.isrvideo_img_end : {
		KEEP(*(.__isrvideo_img_end));
	}

	.rosbootvector_img_start : {
		KEEP(*(.__rosbootvector_img_start));
	}

	.rosbootvector_img : {
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.rosbootvectorimg))
		. = ALIGN(8);
	}

	. = .;

	.rosbootvector_img_end : {
		KEEP(*(.__rosbootvector_img_end));
	}
	/********* Insert A/V CPU related image end *********/

	. = ALIGN(4);

	.image_copy_end :
	{
		*(.__image_copy_end)
	}

	.rel_dyn_start :
	{
		*(.__rel_dyn_start)
	}

	.rel.dyn : {
		*(.rel*)
	}

	.rel_dyn_end :
	{
		*(.__rel_dyn_end)
	}

	.end :
	{
		*(.__end)
	}

	_image_binary_end = .;

	/*
	 * Deprecated: this MMU section is used by pxa at present but
	 * should not be used by new boards/CPUs.
	 */
	. = ALIGN(4096);
	.mmutable : {
		*(.mmutable)
	}

/*
 * Compiler-generated __bss_start and __bss_end, see arch/arm/lib/bss.c
 * __bss_base and __bss_limit are for linker only (overlay ordering)
 */

	.bss_start __rel_dyn_start (OVERLAY) : {
		KEEP(*(.__bss_start));
		__bss_base = .;
	}

	.bss __bss_base (OVERLAY) : {
		*(.bss*)
		 . = ALIGN(4);
		 __bss_limit = .;
	}

	.bss_end __bss_limit (OVERLAY) : {
		KEEP(*(.__bss_end));
	}

	.dynsym _image_binary_end : { *(.dynsym) }
	.dynbss : { *(.dynbss) }
	.dynstr : { *(.dynstr*) }
	.dynamic : { *(.dynamic*) }
	.plt : { *(.plt*) }
	.interp : { *(.interp*) }
	.gnu.hash : { *(.gnu.hash) }
	.gnu : { *(.gnu*) }
	.ARM.exidx : { *(.ARM.exidx*) }
	.gnu.linkonce.armexidx : { *(.gnu.linkonce.armexidx.*) }
}
