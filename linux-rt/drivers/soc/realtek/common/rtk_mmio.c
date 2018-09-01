/*
 * rtk_mmio.c - Realtek Regmap-MMIO API. This file is based on
 * drivers/mfd/syscon.c. SB2 HW can be supported if the relative API
 * is existed.
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/list.h>
#include <linux/regmap.h>
#include <linux/io.h>
#include <linux/device.h>
#include <soc/realtek/rtk_sb2_sem.h>

struct regmap_sb2_lock_data {
	struct sb2_sem *sb2lock;
	spinlock_t spinlock;
	unsigned long flags;
};

static void regmap_sb2_lock(void *data)
__acquires(&data->spinlock)
{
	struct regmap_sb2_lock_data *lock = data;

	spin_lock_irqsave(&lock->spinlock, lock->flags);
	sb2_sem_lock(lock->sb2lock, SB2_SEM_NO_WARNING);
}

static void regmap_sb2_unlock(void *data)
__releases(&data->spinlock)
{
	struct regmap_sb2_lock_data *lock = data;

	sb2_sem_unlock(lock->sb2lock);
	spin_unlock_irqrestore(&lock->spinlock, lock->flags);
}

struct rtk_mmio {
	struct list_head list;
	struct regmap *regmap;
	struct device_node *np;
	struct resource res;
};


static struct regmap_config common_config = {
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
};

static LIST_HEAD(mmio_list);
static DEFINE_SPINLOCK(mmio_list_lock);

static struct rtk_mmio *create_rtk_mmio(struct device_node *np)
{
	struct rtk_mmio *mmio;
	struct regmap *regmap;
	struct regmap_config cfg = common_config;
	void __iomem *reg;
	struct sb2_sem *sb2lock = NULL;
	struct regmap_sb2_lock_data *lock = NULL;
	int ret;

	if (!of_device_is_compatible(np, "realtek,mmio"))
		return ERR_PTR(-EINVAL);

	mmio = kzalloc(sizeof(*mmio), GFP_KERNEL);
	if (!mmio)
		return ERR_PTR(-ENOMEM);

	ret = of_address_to_resource(np, 0, &mmio->res);
	if (ret)
		goto free_mem;

	reg = ioremap(mmio->res.start, resource_size(&mmio->res));

	sb2lock = of_sb2_sem_get(np, 0);
	if (IS_ERR(sb2lock)) {
		pr_warn("%s: failed to get sb2_sem: %ld\n",
			np->name, PTR_ERR(sb2lock));
		sb2lock = NULL;
	}

	cfg.name = np->name;
	cfg.max_register = resource_size(&mmio->res) - 1;
	if (sb2lock) {
		pr_info("%s: use sb2_sem\n", np->name);

		lock = kzalloc(sizeof(*lock), GFP_KERNEL);
		if (!lock) {
			ret = -ENOMEM;
			goto free_mem;
		}
		spin_lock_init(&lock->spinlock);
		lock->sb2lock = sb2lock;

		cfg.lock_arg = lock;
		cfg.lock = regmap_sb2_lock;
		cfg.unlock = regmap_sb2_unlock;
	}

	regmap = regmap_init_mmio(NULL, reg, &cfg);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		pr_err("%s: failed to init regmap: %d\n", np->name, ret);
		goto free_mem;
	}

	mmio->np = np;
	mmio->regmap = regmap;

	spin_lock(&mmio_list_lock);
	list_add_tail(&mmio->list, &mmio_list);
	spin_unlock(&mmio_list_lock);

	return mmio;

free_mem:
	kfree(lock);
	kfree(mmio);
	return ERR_PTR(ret);
}

struct regmap *rtk_mmio_node_to_regmap(struct device_node *np)
{
	struct rtk_mmio *mmio = NULL, *p;

	spin_lock(&mmio_list_lock);
	list_for_each_entry(p, &mmio_list, list)
		if (p->np == np) {
			mmio = p;
			break;
		}
	spin_unlock(&mmio_list_lock);

	if (!mmio)
		mmio = create_rtk_mmio(np);

	if (IS_ERR(mmio))
		return ERR_CAST(mmio);

	return mmio->regmap;
}


