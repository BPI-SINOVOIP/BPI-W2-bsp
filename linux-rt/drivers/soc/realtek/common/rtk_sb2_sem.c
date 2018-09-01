/*
 * rtk_sb2_sem.c - Realtek SB2 HW semaphore API
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/idr.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <soc/realtek/rtk_sb2_sem.h>


#define SB2_SEM_TRYLOCK_MAX 1024
#define SB2_SEM_RETRY_MAX 10

struct sb2_sem {
	int id;
	struct list_head list;
	struct device_node *np;
	void __iomem *reg;
};

int sb2_sem_try_lock(struct sb2_sem *sem, unsigned int flags)
{
	unsigned int val;

	if (IS_ERR_OR_NULL(sem))
		return -EINVAL;

	val = readl(sem->reg);
	return val;

}

void sb2_sem_lock(struct sb2_sem *sem, unsigned int flags)
{
	int i;
	unsigned int val;
	int cnt  = 0;

	if (IS_ERR_OR_NULL(sem))
		return;

retry:
	for (i = 0; i < SB2_SEM_TRYLOCK_MAX; i++) {
		val = sb2_sem_try_lock(sem, flags);
		if (val)
			return;
	}

	if (flags & SB2_SEM_TIMEOUT_INFINITY)
		goto retry;

	if (!(flags & SB2_SEM_NO_WARNING))
		pr_warn("sb2-sem: trylock fail\n");
	cnt++;
	if (cnt < SB2_SEM_RETRY_MAX)
		goto retry;

	if (!(flags & SB2_SEM_NO_WARNING))
		pr_warn("sb2-sem: ignore lock\n");
}

void sb2_sem_unlock(struct sb2_sem *sem)
{
	if (IS_ERR_OR_NULL(sem))
		return;

	writel(0, sem->reg);
}

static LIST_HEAD(sb2_list);
static DEFINE_SPINLOCK(sb2_list_lock);

struct sb2_sem *sb2_sem_get(unsigned int index)
{
	struct sb2_sem *sb2 = ERR_PTR(-EINVAL), *p;

	spin_lock(&sb2_list_lock);
	list_for_each_entry(p, &sb2_list, list)
		if (!index--) {
			sb2 = p;
			break;
		}
	spin_unlock(&sb2_list_lock);

	return sb2;
}
static struct sb2_sem *create_sb2_sem(struct device_node *np)
{
	struct sb2_sem *sb2;

	sb2 = kzalloc(sizeof(*sb2), GFP_KERNEL);
	if (!sb2)
		return ERR_PTR(-ENOMEM);

	sb2->np = np;
	sb2->reg = of_iomap(np, 0);

	spin_lock(&sb2_list_lock);
	list_add_tail(&sb2->list, &sb2_list);
	spin_unlock(&sb2_list_lock);

	return sb2;
}

struct sb2_sem *sb2_sem_node_to_lock(struct device_node *np)
{
	struct sb2_sem *sb2 = NULL, *p;

	spin_lock(&sb2_list_lock);
	list_for_each_entry(p, &sb2_list, list)
		if (p->np == np) {
			sb2 = p;
			break;
		}
	spin_unlock(&sb2_list_lock);

	if (!sb2)
		sb2 = create_sb2_sem(np);

	return sb2;
}

static __init int init_sb2_sem(void)
{
	struct device_node *np;

	for_each_compatible_node(np, NULL, "realtek,sb2-sem") {
		sb2_sem_node_to_lock(np);
	}
	return 0;
}
early_initcall(init_sb2_sem);

struct sb2_sem_priv {
	int id;
	struct sb2_sem *sem;
	struct miscdevice mdev;
};

static DEFINE_IDR(num_idr);

static int sb2_sem_open(struct inode *inode, struct file *filp)
{
	struct sb2_sem_priv *priv = container_of(filp->private_data,
		struct sb2_sem_priv, mdev);
	struct device *dev = priv->mdev.this_device;
	int ret;

	dev_dbg(dev, "%s\n", __func__);

	ret = sb2_sem_try_lock(priv->sem, 0);

	dev_dbg(dev, "%s: returns %d\n", __func__, ret);

	return ret ? 0 : -EAGAIN;
}

static int sb2_sem_release(struct inode *inode, struct file *filp)
{
	struct sb2_sem_priv *priv = container_of(filp->private_data,
		struct sb2_sem_priv, mdev);
	struct device *dev = priv->mdev.this_device;

	dev_dbg(dev, "%s\n", __func__);

	sb2_sem_unlock(priv->sem);

	return 0;
}

static const struct file_operations sb2_sem_fops = {
	.owner = THIS_MODULE,
	.open = sb2_sem_open,
	.release = sb2_sem_release,
};

#define DEV_NAME_LENGTH 20

static int sb2_sem_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct sb2_sem *sem;
	struct sb2_sem_priv *priv;
	int id;
	int ret;
	char name[DEV_NAME_LENGTH];

	dev_info(&pdev->dev, "[SB2-SEM] %s\n", __func__);

	sem = sb2_sem_node_to_lock(np);
	if (IS_ERR(sem))
		return PTR_ERR(sem);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	id = of_alias_get_id(np, "hwsem");
	if (id >= 0)
		ret = idr_alloc(&num_idr, priv, id, id + 1, GFP_KERNEL);
	else
		ret = idr_alloc(&num_idr, priv, 0, 0, GFP_KERNEL);

	dev_dbg(&pdev->dev, "%s: alias = %d, idr = %d\n", __func__, id, ret);

	if (ret < 0)
		goto free_priv;

	snprintf(name, DEV_NAME_LENGTH, "hwsem%d", ret);

	priv->id = ret;
	priv->sem = sem;
	priv->mdev.minor  = MISC_DYNAMIC_MINOR;
	priv->mdev.name   = kstrdup(name, GFP_KERNEL);
	priv->mdev.fops   = &sb2_sem_fops;
	priv->mdev.parent = NULL;

	ret = misc_register(&priv->mdev);
	if (ret) {
		dev_err(&pdev->dev, "%s: failed to misc_register %s: %d\n",
			__func__, priv->mdev.name, ret);
		goto free_idr;
	}

	return 0;
free_idr:
	kfree(priv->mdev.name);
	idr_remove(&num_idr, priv->id);
free_priv:
	kfree(priv);

	return ret;
}

static const struct of_device_id sb2_sem_ids[] = {
	 { .compatible = "realtek,sb2-sem-dev" },
	 {}
};


static struct platform_driver sb2_sem_drv = {
	.driver = {
		.name = "rtk-sb2-sem",
		.owner = THIS_MODULE,
		.of_match_table = sb2_sem_ids,
	},
	.probe = sb2_sem_probe,
};

static int __init sb2_sem_drv_init(void)
{
	return platform_driver_register(&sb2_sem_drv);
}
device_initcall(sb2_sem_drv_init);

