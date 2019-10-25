/*
 * rtk_mmio.c - Realtek Regmap-MMIO API.
 *              This file is based on drivers/mfd/syscon.c.
 *
 * Copyright (C) 2017,2019 Realtek Semiconductor Corporation
 *
 * Author:
 *      Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/slab.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/list.h>
#include <linux/regmap.h>
#include <linux/io.h>
#include <soc/realtek/rtk_sb2_sem.h>
#include <soc/realtek/rtk_regmap.h>
#include <soc/realtek/rtk_mmio.h>

struct regmap_sb2_lock_data {
	struct sb2_sem *sb2lock;
	spinlock_t spinlock;
	unsigned long flags;
};

static void regmap_sb2_lock(void *data)
__acquires(&data->spinlock)
{
	unsigned long flags;
	struct regmap_sb2_lock_data *lock = data;

	spin_lock_irqsave(&lock->spinlock, flags);
	lock->flags = flags;
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
	const char *name;
	struct regmap_config *cfg;
};

#define __addr(_m) ((unsigned long)((_m)->res.start))
#define mmio_err(_m, _fmt, ...) \
	pr_err("rtk-mmio %lx.%s: " _fmt, __addr(_m), (_m)->name, ##__VA_ARGS__)
#define mmio_warn(_m, _fmt, ...) \
	pr_warn("rtk-mmio %lx.%s: " _fmt, __addr(_m), (_m)->name, ##__VA_ARGS__)
#define mmio_info(_m, _fmt, ...) \
	pr_info("rtk-mmio %lx.%s: " _fmt, __addr(_m), (_m)->name, ##__VA_ARGS__)

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
	struct rtk_regmap_config *conf = NULL;

	if (!of_device_is_compatible(np, "realtek,mmio")) {
		pr_err("%s: not realtek,mmio\n", np->name);
		return ERR_PTR(-EINVAL);
	}

	mmio = kzalloc(sizeof(*mmio), GFP_KERNEL);
	if (!mmio)
		return ERR_PTR(-ENOMEM);
	mmio->name = np->name;

	ret = of_address_to_resource(np, 0, &mmio->res);
	if (ret) {
		mmio_err(mmio, "failed to get resource: %d\n", ret);
		goto free_mem;
	}

	reg = ioremap(mmio->res.start, resource_size(&mmio->res));
	if (!reg) {
		mmio_err(mmio, "failed to ioremap\n");
		ret = -ENOMEM;
		goto free_mem;
	}

	/* secure regster accese */
	conf = rtk_mmio_match_config_by_addr(mmio->res.start);
	if (conf) {
		mmio_info(mmio, "use secure config\n");
		mmio->cfg = &conf->config;
		mmio->cfg->max_register = resource_size(&mmio->res) - 1;
	} else {
		mmio->cfg = &cfg;
		mmio->cfg->name = np->name;
		mmio->cfg->max_register = resource_size(&mmio->res) - 1;
	}

	/* hwsemaphore */
	sb2lock = of_sb2_sem_get(np, 0);
	if (IS_ERR(sb2lock)) {
		mmio_info(mmio, "failed to get hw semaphore: %ld\n",
			PTR_ERR(sb2lock));
		sb2lock = NULL;
	}
	if (sb2lock) {
		mmio_info(mmio, "use hw semaphore\n");

		lock = kzalloc(sizeof(*lock), GFP_KERNEL);
		if (!lock) {
			ret = -ENOMEM;
			mmio_err(mmio, "failed to alloc lock data\n");
			goto free_mem;
		}
		spin_lock_init(&lock->spinlock);
		lock->sb2lock = sb2lock;

		mmio->cfg->lock_arg = lock;
		mmio->cfg->lock = regmap_sb2_lock;
		mmio->cfg->unlock = regmap_sb2_unlock;
	}


	if (conf)
		regmap = rtk_regmap_init_secure_mmio(NULL, reg, conf);
	else
		regmap = regmap_init_mmio(NULL, reg, mmio->cfg);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		mmio_err(mmio, "failed to init regmap: %d\n", ret);
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

