/*
 * rtk_rstctl.h
 *
 * Copyright (c) 2018 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */
#ifndef __RTK_RSTCTL_H__
#define __RTK_RSTCTL_H__

#include <asm/arch/system.h>

#define REBOOT_ACTION_ADDR      (PLATFORM_REBOOT_ACTION_ADDR)
#define REBOOT_ACTION_MASK      (0xff)
#define REBOOT_MAGIC            0xaabbcc00
#define REBOOT_MAGIC_SHIFT      8
#define REBOOT_ACTION_VALID(v)  !((REBOOT_MAGIC ^ (v)) >> REBOOT_MAGIC_SHIFT)

typedef enum {
	RESET_ACTION_NO_ACTION = 0,
	RESET_ACTION_FASTBOOT,
	RESET_ACTION_RECOVERY,
	RESET_ACTION_GOLDEN,
	RESET_ACTION_RESCUE,
	RESET_ACTION_ABNORMAL = 0xff,
}RESET_ACTION;

#endif /* __RTK_RSTCTL_H__ */
