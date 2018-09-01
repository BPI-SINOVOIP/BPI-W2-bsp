/**
 * io.h - DesignWare USB3 DRD IO Header
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __DRIVERS_USB_DWC3_IO_H
#define __DRIVERS_USB_DWC3_IO_H

#include <linux/io.h>
#include "trace.h"
#include "debug.h"
#include "core.h"

#ifdef CONFIG_USB_PATCH_ON_RTK
/* Add global lock for emmc issue*/
#include <soc/realtek/rtd129x_lockapi.h>
#endif

static inline u32 dwc3_readl(void __iomem *base, u32 offset)
{
	u32 value;

#ifdef CONFIG_USB_PATCH_ON_RTK
	/* Add global lock for emmc issue*/
	unsigned long flags;
	rtk_lockapi_lock(flags, __FUNCTION__);
#endif

	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	value = readl(base + offset - DWC3_GLOBALS_REGS_START);

#ifdef CONFIG_USB_PATCH_ON_RTK
	/* Add global lock for emmc issue*/
	rtk_lockapi_unlock(flags,__FUNCTION__);
#endif

	/*
	 * When tracing we want to make it easy to find the correct address on
	 * documentation, so we revert it back to the proper addresses, the
	 * same way they are described on SNPS documentation
	 */
	dwc3_trace(trace_dwc3_readl, "addr %p value %08x",
			base - DWC3_GLOBALS_REGS_START + offset, value);

	return value;
}

static inline void dwc3_writel(void __iomem *base, u32 offset, u32 value)
{
#ifdef CONFIG_USB_PATCH_ON_RTK
	unsigned long flags;
	rtk_lockapi_lock(flags, __FUNCTION__);
#endif

	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	writel(value, base + offset - DWC3_GLOBALS_REGS_START);

#ifdef CONFIG_USB_PATCH_ON_RTK
	rtk_lockapi_unlock(flags,__FUNCTION__);
#endif

	/*
	 * When tracing we want to make it easy to find the correct address on
	 * documentation, so we revert it back to the proper addresses, the
	 * same way they are described on SNPS documentation
	 */
	dwc3_trace(trace_dwc3_writel, "addr %p value %08x",
			base - DWC3_GLOBALS_REGS_START + offset, value);
}

#endif /* __DRIVERS_USB_DWC3_IO_H */
