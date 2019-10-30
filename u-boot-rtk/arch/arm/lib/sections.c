/*
 * Copyright 2013 Albert ARIBAUD <albert.u.boot@aribaud.net>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/**
 * These two symbols are declared in a C file so that the linker
 * uses R_ARM_RELATIVE relocation, rather than the R_ARM_ABS32 one
 * it would use if the symbols were defined in the linker file.
 * Using only R_ARM_RELATIVE relocation ensures that references to
 * the symbols are correct after as well as before relocation.
 *
 * We need a 0-byte-size type for these symbols, and the compiler
 * does not allow defining objects of C type 'void'. Using an empty
 * struct is allowed by the compiler, but causes gcc versions 4.4 and
 * below to complain about aliasing. Therefore we use the next best
 * thing: zero-sized arrays, which are both 0-byte-size and exempt from
 * aliasing warnings.
 */
#include <common.h>

char __bss_start[0] __attribute__((section(".__bss_start")));
char __bss_end[0] __attribute__((section(".__bss_end")));
char __image_copy_start[0] __attribute__((section(".__image_copy_start")));
char __image_copy_end[0] __attribute__((section(".__image_copy_end")));
char __rel_dyn_start[0] __attribute__((section(".__rel_dyn_start")));
char __rel_dyn_end[0] __attribute__((section(".__rel_dyn_end")));
char __secure_start[0] __attribute__((section(".__secure_start")));
char __secure_end[0] __attribute__((section(".__secure_end")));
char _end[0] __attribute__((section(".__end")));

#ifdef CONFIG_BSP_REALTEK
char _f_exc_redirect_img[0] __attribute__((section(".__redirect_img_start")));
char _e_exc_redirect_img[0] __attribute__((section(".__redirect_img_end")));
char _f_exc_dispatch_img[0] __attribute__((section(".__dispatch_img_start")));
char _e_exc_dispatch_img[0] __attribute__((section(".__dispatch_img_end")));
char _f_a_entry_img[0] __attribute__((section(".__a_entry_img_start")));
char _e_a_entry_img[0] __attribute__((section(".__a_entry_img_end")));
char _f_v_entry_img[0] __attribute__((section(".__v_entry_img_start")));
char _e_v_entry_img[0] __attribute__((section(".__v_entry_img_end")));
char _f_isrvideo_img[0] __attribute__((section(".__isrvideo_img_start")));
char _e_isrvideo_img[0] __attribute__((section(".__isrvideo_img_end")));
char _f_rosbootvector_img[0] __attribute__((section(".__rosbootvector_img_start")));
char _e_rosbootvector_img[0] __attribute__((section(".__rosbootvector_img_end")));
#endif
