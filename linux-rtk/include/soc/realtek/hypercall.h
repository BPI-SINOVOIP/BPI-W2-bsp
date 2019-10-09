/*
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __SOC_RTK_HYPERCALL_H__
#define __SOC_RTK_HYPERCALL_H__

#include <xen/interface/rtk-hypercall.h>

#ifdef CONFIG_RTK_XEN_HYPERCALL
unsigned int rtk_xen_domain_lock(unsigned long timeout, RTK_DOMAIN_LOCK lock_type);
int rtk_xen_domain_unlock(unsigned int ticket, RTK_DOMAIN_LOCK lock_type);
#endif// CONFIG_RTK_XEN_HYPERCALL

#endif //__SOC_RTK_HYPERCALL_H__
