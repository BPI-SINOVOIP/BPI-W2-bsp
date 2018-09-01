/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cpu.h>
#include <xen/xen.h>
#include <xen/interface/rtk-hypercall.h>
#include <asm/xen/hypercall.h>
#include <asm/xen/interface.h>

#define DUMMY_TICKET	(~0)	// ticket wouldn't reach this value since it's u16

unsigned int rtk_xen_domain_lock(unsigned long timeout, RTK_DOMAIN_LOCK lock_type) {
	struct xen_rtk_domain_lock lock_param;
	unsigned int ticket;
	unsigned long base_time = sched_clock() / NSEC_PER_MSEC;
	unsigned long current_time;
	int rc = 0;

	if (!xen_domain())
		return DUMMY_TICKET;

	lock_param.lock_type = lock_type;

	rc = HYPERVISOR_rtk_hypercall_op(XENRTK_domain_lock, &lock_param);
	if(rc) {
		pr_err("%s, get ticket FAIL!!\n", __func__);
		goto err;
	}

	ticket = lock_param.lock;

	while (1) {
		lock_param.lock_type = lock_type;
		lock_param.lock = ticket;
		rc = HYPERVISOR_rtk_hypercall_op(XENRTK_domain_lock_check, &lock_param);

		/* LOCK HOLD */
		if (!rc)
			return ticket;

		current_time = sched_clock() / NSEC_PER_MSEC;
		if (current_time - base_time > timeout) {
			pr_err("%s, timeout with ticket:%x, lock:%x held by dom:%u\n",
				__func__, ticket, lock_param.lock, lock_param.domid);
			goto err;
		}
	}
err:
	BUG();
	return rc;
}

int rtk_xen_domain_unlock(unsigned int ticket, RTK_DOMAIN_LOCK lock_type) {
	struct xen_rtk_domain_lock lock_param;
	int rc = 0;

	if (ticket == DUMMY_TICKET)
		return 0;

	lock_param.lock = ticket;
	lock_param.lock_type = lock_type;
	rc =  HYPERVISOR_rtk_hypercall_op(XENRTK_domain_unlock, &lock_param);

	if (rc != 0) {
		pr_warn("DEBUG UNLOCK FAIL!!\n");
		BUG();
	}

	return rc;
}

