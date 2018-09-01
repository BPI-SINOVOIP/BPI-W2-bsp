/*
 * rdbg.c - Realtek Register Debug
 *
 * Copyright (C) 2017, Realtek Semiconductor Corporation
 * Copyright (C) 2017, Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "[RDBG] " fmt

#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

#define RDBG_MAX_INFO 20

struct rdbg_info {
	unsigned long paddr;
	void *vaddr;
	unsigned int value;
	unsigned int diff;
};

static DEFINE_SPINLOCK(lock);
static int icnt;
static struct rdbg_info infos[RDBG_MAX_INFO];

struct rdbg_info *rdbg_create_info(unsigned long paddr)
{
	unsigned long flags;
	struct rdbg_info *info = NULL;
	void *vaddr;
	int idx;

	if (WARN_ON(icnt > RDBG_MAX_INFO))
		return NULL;

	vaddr = ioremap(paddr, 0x4);
	if (!vaddr)
		return NULL;

	spin_lock_irqsave(&lock, flags);

	info = &infos[icnt];
	info->paddr = paddr;
	info->vaddr = vaddr;
	info->diff = 0;
	info->value = readl(info->vaddr);
	idx = icnt++;

	spin_unlock_irqrestore(&lock, flags);

	pr_err("%s: create map %d: 0x%lx -> %p\n", __func__,
		idx, paddr, vaddr);

	return info;
}

struct rdbg_info *rdbg_phy2info(unsigned long paddr)
{
	int i;

	for (i = 0; i < icnt; i++)
		if (infos[i].paddr == paddr)
			return &infos[i];
	return NULL;
}


void rdbg_update_ref(struct rdbg_info *info, unsigned int update_val, const char *caller)
{
	unsigned int val;
	unsigned int diff;
	unsigned long flags;

	if (!info)
		return;

	val = readl(info->vaddr);
	diff = val ^ info->value;
	diff &= ~update_val;

	spin_lock_irqsave(&lock, flags);
	info->diff = diff;
	info->value = val;
	spin_unlock_irqrestore(&lock, flags);;

	if (diff)
		pr_err("%s: untracked change detected: paddr=%08lx val=%08x delta=%08x caller=%s\n",
			__func__, info->paddr, val, diff, caller);
}



