/*
 * Realtek DCSYS Performance Counter Driver & APIs
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "dcsys: " fmt

#include <linux/clk.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include <soc/realtek/rtk_dc_sys_pc.h>
#include "rtk_dc_sys_pc.h"

struct dcsys_pc_regfield {
	int offset;
	int lsb;
	int msb;
};

#define DCPC_RF(_off, _lsb, _msb) {.offset = _off, .lsb = _lsb, .msb = _msb,}

static struct dcsys_pc_core *core;

static struct dcsys_pc_regfield _reg[] = {
	[PC_SYSH_PROG0_SEL] = DCPC_RF(0x50, 0, 6),
	[PC_SYSH_PROG0_DC_SEL] = DCPC_RF(0x50, 7, 7),
	[PC_SYSH_PROG1_SEL] = DCPC_RF(0x50, 8, 14),
	[PC_SYSH_PROG1_DC_SEL] = DCPC_RF(0x50, 15, 15),
	[PC_SYSH_PROG2_SEL] = DCPC_RF(0x50, 16, 22),
	[PC_SYSH_PROG2_DC_SEL] = DCPC_RF(0x50, 23, 23),
	[PC_SYSH_PROG3_SEL] = DCPC_RF(0x500, 0, 6),
	[PC_SYSH_PROG3_DC_SEL] = DCPC_RF(0x500, 7, 7),
	[PC_SYSH_PROG4_SEL] = DCPC_RF(0x500, 8, 14),
	[PC_SYSH_PROG4_DC_SEL] = DCPC_RF(0x500, 15, 15),
	[PC_SYSH_PROG5_SEL] = DCPC_RF(0x500, 16, 22),
	[PC_SYSH_PROG5_DC_SEL] = DCPC_RF(0x500, 23, 23),
	[PC_SYSH_PROG6_SEL] = DCPC_RF(0x504, 0, 6),
	[PC_SYSH_PROG6_DC_SEL] = DCPC_RF(0x504, 7, 7),
	[PC_SYSH_PROG7_SEL] = DCPC_RF(0x504, 8, 14),
	[PC_SYSH_PROG7_DC_SEL] = DCPC_RF(0x504, 15, 15),
	[PC_SYS_PROG0_SEL] = DCPC_RF(0x54, 0, 6),
	[PC_SYS_PROG1_SEL] = DCPC_RF(0x54, 8, 14),
	[PC_SYS_PROG2_SEL] = DCPC_RF(0x54, 16, 22),
};

int dcsys_pc_set_regfield(int rf_id, unsigned int val)
{
	struct dcsys_pc_regfield *drf;
	unsigned int s, m, v;

	if (rf_id > PC_SYS_PROG2_SEL)
		return -EINVAL;

	drf = &_reg[rf_id];

	s = drf->lsb;
	m = BIT(drf->msb - drf->lsb + 1) - 1;
	m <<= s;

	v = readl(core->base + drf->offset);
	v &= ~m;
	v |= (val << s) & m;
	writel(v, core->base + drf->offset);

	return 0;
}

int dcsys_pc_get_regfield(int rf_id, unsigned int *val)
{
	struct dcsys_pc_regfield *drf;
	unsigned int s, m, v;

	if (rf_id > PC_SYS_PROG2_SEL)
		return -EINVAL;

	drf = &_reg[rf_id];

	s = drf->lsb;
	m = BIT(drf->msb - drf->lsb + 1) - 1;
	m <<= s;

	v = readl(core->base + drf->offset);
	v &= m;

	*val = v >> s;

	return 0;
}

struct dcsys_pc_desc {
	int prog_sel;
	int dc_sel;
	unsigned int acc_lat;
	unsigned int max_lat;
	unsigned int req;
	unsigned int ack;
};

#define DEFINE_SYSH_DESC(_id) \
{ \
	.prog_sel = PC_SYSH_PROG ## _id ## _SEL,  \
	.dc_sel   = PC_SYSH_PROG ## _id ## _DC_SEL, \
	.acc_lat  = DC_PC_SYSH_PROG_ ## _id ## _ACC_LAT, \
	.max_lat  = DC_PC_SYSH_PROG_ ## _id ## _MAX_LAT, \
	.req      = DC_PC_SYSH_PROG_ ## _id ## _REQ_NUM, \
	.ack      = DC_PC_SYSH_PROG_ ## _id ## _ACK_NUM, \
}

#define DEFINE_SYS_DESC(_id) \
{ \
	.prog_sel = PC_SYS_PROG ## _id ## _SEL,  \
	.dc_sel   = -1, \
	.acc_lat  = DC_PC_SYS_PROG_ ## _id ## _ACC_LAT, \
	.max_lat  = DC_PC_SYS_PROG_ ## _id ## _MAX_LAT, \
	.req      = DC_PC_SYS_PROG_ ## _id ## _REQ_NUM, \
	.ack      = DC_PC_SYS_PROG_ ## _id ## _ACK_NUM, \
}

static const struct dcsys_pc_desc desc[] = {
	DEFINE_SYSH_DESC(0),
	DEFINE_SYSH_DESC(1),
	DEFINE_SYSH_DESC(2),
	DEFINE_SYSH_DESC(3),
	DEFINE_SYSH_DESC(4),
	DEFINE_SYSH_DESC(5),
	DEFINE_SYSH_DESC(6),
	DEFINE_SYSH_DESC(7),
	DEFINE_SYS_DESC(0),
	DEFINE_SYS_DESC(1),
	DEFINE_SYS_DESC(2),
};

int dcsys_pc_get_reg(int offset, unsigned int *val)
{
	*val = readl(core->base + offset);
	return 0;
}

int dcsys_pc_prog_configure(int idx, int prog, int dc_sel)
{
	if (!core)
		return -ENODEV;

	dcsys_pc_set_regfield(desc[idx].prog_sel, prog);
	if (desc[idx].dc_sel != -1)
		dcsys_pc_set_regfield(desc[idx].dc_sel, dc_sel);
	return 0;
}

int dcsys_pc_prog_get_data(int idx, struct dcsys_pc_prog_data *data)
{
	if (!core)
		return -ENODEV;

	dcsys_pc_get_regfield(desc[idx].prog_sel, &data->prog_sel);
	if (desc[idx].dc_sel != -1)
		dcsys_pc_get_regfield(desc[idx].dc_sel, &data->dc_sel);

	data->acc_lat = readl(core->base + desc[idx].acc_lat);
	data->max_lat = readl(core->base + desc[idx].acc_lat);
	data->req = readl(core->base + desc[idx].req);
	data->ack = readl(core->base + desc[idx].ack);

	return 0;
}

int dcsys_pc_global_get_data(int sys, struct dcsys_pc_global_data *data)
{
	void *base;

	if (!core)
		return -ENODEV;

	base = core->base + (sys ? 0x40 : 0x34);
	data->mon = readl(base + 0);
	data->ack = readl(base + 4);
	data->idl = readl(base + 8);

	return 0;
}

struct dcsys_pc *dcsys_pc_simple_get(struct device *dev)
{
	struct dcsys_pc *pc = NULL;

	if (!core)
		goto done;

	pc = kzalloc(sizeof(*pc), GFP_KERNEL);
	if (!pc)
		goto done;

	list_add(&pc->list, &core->list);
	pc->dev = dev;

done:
	return pc;
}

void dcsys_pc_put(struct dcsys_pc *pc)
{
	if (!pc)
		return;

	list_del(&pc->list);
	kfree(pc);
}

int dcsys_pc_register_notifier(struct notifier_block *nb)
{
	if (!core)
		return -ENODEV;

	return srcu_notifier_chain_register(&core->notifier_list, nb);
}

int dcsys_pc_unregister_notifier(struct notifier_block *nb)
{
	if (!core)
		return -ENODEV;

	return srcu_notifier_chain_unregister(&core->notifier_list, nb);
}

static void dcsys_pc_notify(unsigned int state)
{
	srcu_notifier_call_chain(&core->notifier_list, state, NULL);
}

int dcsys_pc_set_owner(struct dcsys_pc *pc, unsigned int flags)
{
	if (!pc)
		return -ENODEV;

	if (!(flags & DCSYS_PC_FORCE_SET) && core->owner != NULL) {
		pr_debug("%s: %s is owner\n", __func__, dev_name(pc->dev));
		return -EBUSY;
	}

	mutex_lock(&core->lock);
	core->owner = pc;
	mutex_unlock(&core->lock);

	writel(0, core->base + DC_PC_CTRL);
	core->stop = get_jiffies_64();
	core->start_cnt = 0;

	dcsys_pc_notify(DCSYS_PC_OWNER_SET);

	return 0;
}

int dcsys_pc_clear_owner(struct dcsys_pc *pc)
{
	if (!pc)
		return -ENODEV;

	if (core->owner != pc)
		return -EACCES;

	mutex_lock(&core->lock);
	core->owner = NULL;
	mutex_unlock(&core->lock);

	dcsys_pc_notify(DCSYS_PC_OWNER_CLEAR);

	return 0;
}

int dcsys_pc_is_owner(struct dcsys_pc *pc)
{
	bool ret;

	if (!pc)
		return -ENODEV;

	mutex_lock(&core->lock);
	ret = core->owner == pc;
	mutex_unlock(&core->lock);

	return ret;
}

int dcsys_pc_is_stopped(struct dcsys_pc *pc)
{
	unsigned int val;

	if (!pc)
		return -ENODEV;

	val = readl(core->base + DC_PC_CTRL);

	return val == 0;
}

int dcsys_pc_start(struct dcsys_pc *pc)
{
	if (!pc)
		return -ENODEV;

	if (core->owner != pc)
		return -EACCES;

	writel(0, core->base + DC_PC_CTRL);
	core->start = get_jiffies_64();
	core->start_cnt++;
	writel(1, core->base + DC_PC_CTRL);

	return 0;
}

static  int dcsys_pc_is_corrupted(struct dcsys_pc *pc)
{
	unsigned long time;
	unsigned long freq;
	unsigned long dcsys_pc_time;
	unsigned long t;
	unsigned long dt;

	if (!pc)
		return -ENODEV;

	if (!core->ref)
		return -EINVAL;

	time = jiffies_to_msecs(core->stop - core->start);
	if (time >= 9000)
		return -E2BIG;

	dcsys_pc_time = readl(core->base + DC_PC_TOTA_MON_NUM_0);
	freq = clk_get_rate(core->ref);

	t = freq * time / 1000;
	dt = t / 10;
	if ((t + dt) > dcsys_pc_time && dcsys_pc_time > (t - dt))
		return 0;
	return 1;
}

int dcsys_pc_stop(struct dcsys_pc *pc)
{
	if (!pc)
		return -ENODEV;

	if (core->owner != pc)
		return -EPERM;

	writel(0, core->base + DC_PC_CTRL);
	core->stop = get_jiffies_64();

	if (core->start_cnt >= 2 && dcsys_pc_is_corrupted(pc) == 1) {
		pr_err("%s: dcsys_pc is corrupted in %lld round\n",
			dev_name(core->owner->dev), core->start_cnt);
		core->owner = NULL;
	}

	return 0;
}

static int dcsys_pc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int ret;

	dev_info(dev, "[DCSYS] %s\n", __func__);

	core = kzalloc(sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->base = of_iomap(np, 0);
	if (!core->base) {
		ret = -ENOMEM;
		goto free_mem;
	}

	core->ref = clk_get(dev, "ref");
	if (IS_ERR(core->ref)) {
		core->ref = NULL;
		dev_warn(dev, "failed to get ref clk, disable corrupt checking\n");
	}

	INIT_LIST_HEAD(&core->list);
	mutex_init(&core->lock);
	srcu_init_notifier_head(&core->notifier_list);

	platform_set_drvdata(pdev, core);

	dcsys_pc_debugfs_init(dev);

	return 0;

free_mem:
	kfree(core);
	core = NULL;

	return ret;
}

static const struct of_device_id dcsys_pc_match[] = {
	{.compatible = "realtek,dcsys-pc"},
	{}
};

static struct platform_driver dcsys_pc_driver = {
	.probe = dcsys_pc_probe,
	.driver = {
		.name   = "rtk-dcsys:pc",
		.of_match_table = dcsys_pc_match,
	},
};

static int __init dcsys_pc_init(void)
{
	return platform_driver_register(&dcsys_pc_driver);
}
arch_initcall(dcsys_pc_init);

