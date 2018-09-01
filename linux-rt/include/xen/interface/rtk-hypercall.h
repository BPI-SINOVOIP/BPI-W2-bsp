/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __XEN_PUBLIC_RTKHYPERCALL_H__
#define __XEN_PUBLIC_RTKHYPERCALL_H__

/****** RTK Hyp-Call Table ******/
/* 1 : XENRTK_domain_lock       */
/* 2 : XENRTK_domain_unlock     */
/* 3 : XENRTK_domain_lock_check */
/* 4 : XENRTK_getidletime       */
/********************************/

/*
 * Inter-Domain hypervisor lock.
 *
 */
typedef enum {
	GPIO_DOMLOCK = 0,
	HW_DOMLOCK,
	TEST_DOMLOCK,
	DOMLOCK_MAX, /* Place at end */
} RTK_DOMAIN_LOCK;

#define XENRTK_domain_lock		0
#define XENRTK_domain_unlock		1
#define XENRTK_domain_lock_check	2
struct xen_rtk_domain_lock {
	// In/Out-put
	unsigned int lock;
	unsigned int domid;
	RTK_DOMAIN_LOCK lock_type;
};
typedef struct xen_rtk_domain_lock xen_rtk_domain_lock_t;
DEFINE_GUEST_HANDLE_STRUCT(xen_rtk_domain_lock_t);


#define XENRTK_getidletime 3
struct xen_rtk_idletime {
    uint32_t cpumask;
    uint64_t idletime[4];
    uint64_t now;
};
typedef struct xen_rtk_idletime xen_rtk_idletime_t;
DEFINE_GUEST_HANDLE_STRUCT(xen_rtk_idletime_t);

#define XENRTK_cpu_load 4
struct xen_rtk_cpu_load {
	uint32_t max_load;
};
typedef struct xen_rtk_cpu_load xen_rtk_cpu_load_t;
DEFINE_GUEST_HANDLE_STRUCT(xen_rtk_cpu_load_t);

#endif //__XEN_PUBLIC_RTKHYPERCALL_H__
