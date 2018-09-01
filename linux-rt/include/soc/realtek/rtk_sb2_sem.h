/*
 * rtk_sb2_sem.h - Realtek SB2 HW semaphore API
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_SB2_SEM_H
#define __SOC_REALTEK_SB2_SEM_H

struct sb2_sem;
struct sb2_sem *sb2_sem_get(unsigned int index);
int sb2_sem_try_lock(struct sb2_sem *sem, unsigned int flags);
void sb2_sem_lock(struct sb2_sem *sem, unsigned int flags);
void sb2_sem_unlock(struct sb2_sem *sem);
struct sb2_sem *sb2_sem_node_to_lock(struct device_node *np);

#define SB2_SEM_NO_WARNING         0x2
#define SB2_SEM_TIMEOUT_INFINITY   0x4

static inline struct sb2_sem *of_sb2_sem_get(const struct device_node *np,
	 int index)
{
	struct of_phandle_args args;
	int ret;

	ret = of_parse_phandle_with_fixed_args(np, "realtek,sb2-lock", 0,
		index, &args);
	if (ret)
		return ERR_PTR(ret);

	return sb2_sem_node_to_lock(args.np);
}

#endif
