/*
 * DebugFS of Realtek DCSYS Performance Counter
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/slab.h>
#include <linux/debugfs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <soc/realtek/rtk_dc_sys_pc.h>
#include "rtk_dc_sys_pc.h"

struct dc_sel_conf {
	const char name[10];
	int val;
};

static struct dc_sel_conf prog_conf[] = {
#if defined(CONFIG_ARCH_RTD129x)
	{.name = "vo",    .val = DC_PC_PROG_ID_VO,},
	{.name = "aio",   .val = DC_PC_PROG_ID_AIO,},
	{.name = "cp",    .val = DC_PC_PROG_ID_CP,},
	{.name = "nat",   .val = DC_PC_PROG_ID_NAT,},
	{.name = "md",    .val = DC_PC_PROG_ID_MD,},
	{.name = "nat2",  .val = DC_PC_PROG_ID_NAT2,},
	{.name = "jpeg",  .val = DC_PC_PROG_ID_JPEG,},
	{.name = "tp",    .val = DC_PC_PROG_ID_TP,},
	{.name = "gpu",   .val = DC_PC_PROG_ID_GPU,},
	{.name = "scpu",  .val = DC_PC_PROG_ID_SCPU,},
	{.name = "acpu",  .val = DC_PC_PROG_ID_ACPU,},
	{.name = "usb",   .val = DC_PC_PROG_ID_USB,},
	{.name = "etn",   .val = DC_PC_PROG_ID_ETN,},
	{.name = "ve1",   .val = DC_PC_PROG_ID_VE1,},
	{.name = "ve2",   .val = DC_PC_PROG_ID_VE2,},
	{.name = "ve3",   .val = DC_PC_PROG_ID_VE3,},
	{.name = "se",    .val = DC_PC_PROG_ID_SE,},
	{.name = "cr",    .val = DC_PC_PROG_ID_CR,},
	{.name = "nf",    .val = DC_PC_PROG_ID_NF,},
	{.name = "mipi",  .val = DC_PC_PROG_ID_MIPI,},
	{.name = "sata",  .val = DC_PC_PROG_ID_SATA,},
	{.name = "pcie0", .val = DC_PC_PROG_ID_PCIE0,},
	{.name = "pcie1", .val = DC_PC_PROG_ID_PCIE1,},
#elif defined(CONFIG_ARCH_RTD139x)
	{.name = "vo",    .val = DC_PC_PROG_ID_VO,},
	{.name = "aio",   .val = DC_PC_PROG_ID_AIO,},
	{.name = "cp",    .val = DC_PC_PROG_ID_CP,},
	{.name = "md",    .val = DC_PC_PROG_ID_MD,},
	{.name = "jpeg",  .val = DC_PC_PROG_ID_JPEG,},
	{.name = "tp",    .val = DC_PC_PROG_ID_TP,},
	{.name = "gpu",   .val = DC_PC_PROG_ID_GPU,},
	{.name = "scpu",  .val = DC_PC_PROG_ID_SCPU,},
	{.name = "acpu",  .val = DC_PC_PROG_ID_ACPU,},
	{.name = "hif",   .val = DC_PC_PROG_ID_HIF,},
	{.name = "usb",   .val = DC_PC_PROG_ID_USB,},
	{.name = "sd",    .val = DC_PC_PROG_ID_SD,},
	{.name = "pcie",  .val = DC_PC_PROG_ID_PCIE,},
	{.name = "sdio",  .val = DC_PC_PROG_ID_SDIO,},
	{.name = "etn",   .val = DC_PC_PROG_ID_ETN,},
	{.name = "ve1",   .val = DC_PC_PROG_ID_VE1,},
	{.name = "ve2",   .val = DC_PC_PROG_ID_VE2,},
	{.name = "se",    .val = DC_PC_PROG_ID_SE,},
	{.name = "emmc",  .val = DC_PC_PROG_ID_EMMC,},
	{.name = "nf",    .val = DC_PC_PROG_ID_NF,},
	{.name = "dip",   .val = DC_PC_PROG_ID_DIP,},
	{.name = "hse",   .val = DC_PC_PROG_ID_HSE_REE,},
	{.name = "hse_tee", .val = DC_PC_PROG_ID_HSE_TEE,},
#endif
};

static struct dentry *root;
static struct dcsys_pc *pc;
static struct device *core_dev;

#define PTR_U32(_p) ((unsigned int)(unsigned long)(_p))
#define U32_PTR(_v) ((void *)(unsigned long)(_v))

static const char *sel_to_name(unsigned int sel)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(prog_conf); i++)
		if (prog_conf[i].val == sel)
			return prog_conf[i].name;

	return "undef";
}

static unsigned int name_to_sel(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(prog_conf); i++)
		if (!strcmp(name, prog_conf[i].name))
			return prog_conf[i].val;

	return 0;
}

static int dcsys_pc_summary_show(struct seq_file *s, void *data)
{
	struct dcsys_pc_core *core = dev_get_drvdata(core_dev);
	const char *pc_name = "none";
	int running = 0;
	int i;
	struct dcsys_pc_prog_data pd;
	struct dcsys_pc_global_data gd;

	seq_puts(s, "DCPC summary\n");
	seq_puts(s, "------------------------------------------------------------\n");

	running = core->owner != NULL;
	if (core->owner && core->owner->dev)
		pc_name = dev_name(core->owner->dev);

	seq_puts(s, "current status:\n");
	seq_printf(s, "owner: %s\n", pc_name);
	seq_printf(s, "state: %s\n", running ? "running" : "stopped");
	if (!running)
		seq_printf(s, "time interval in jiffies: %lld - %lld (%u ms)\n",
			core->start, core->stop,
			jiffies_to_msecs(core->stop - core->start));

	seq_puts(s, "------------------------------------------------------------\n");
	seq_puts(s, "1. total\n");
	seq_printf(s, "           dc  %10s %10s %10s\n", "MON", "ACK", "IDL");

	dcsys_pc_global_get_data(0, &gd);
	seq_printf(s, "            0: %10d %10d %10d\n",
		gd.mon, gd.ack, gd.idl);
	dcsys_pc_global_get_data(1, &gd);
	seq_printf(s, "            1: %10d %10d %10d\n",
		gd.mon, gd.ack, gd.idl);

	seq_puts(s, "------------------------------------------------------------\n");
	seq_puts(s, "2. sysh\n");
	seq_printf(s, "slot prog  dc  %10s %10s %10s %10s\n",
		"ACC_LAT", "MAX_LAT", "REQ", "ACK");

	for (i = 0; i <= 7; i++) {
		dcsys_pc_prog_get_data(i, &pd);
		seq_printf(s, "%4d %-5s %2d: %10u %10u %10u %10u\n", i,
			sel_to_name(pd.prog_sel), pd.dc_sel, pd.acc_lat,
			pd.max_lat, pd.req, pd.ack);
	}

	seq_puts(s, "------------------------------------------------------------\n");
	seq_puts(s, "* sys\n");
	seq_printf(s, "slot prog      %10s %10s %10s %10s\n",
		"ACC_LAT", "MAX_LAT", "REQ", "ACK");
	for (i = 8; i <= 10; i++) {
		dcsys_pc_prog_get_data(i, &pd);
		seq_printf(s, "%4d %-5s   : %10u %10u %10u %10u\n", i - 8,
			sel_to_name(pd.prog_sel), pd.acc_lat, pd.max_lat,
			pd.req, pd.ack);
	}

	return 0;
}

static int dcsys_pc_summary_open(struct inode *inode, struct file *file)
{
	return single_open(file, dcsys_pc_summary_show, inode->i_private);
}

static const struct file_operations dcsys_pc_summary_fops = {
	.owner   = THIS_MODULE,
	.open    = dcsys_pc_summary_open,
	.read    = seq_read,
	.release = single_release,
};

static int dcsys_pc_available_progs_show(struct seq_file *s, void *data)
{
	int i;
	const char *sp = "";

	for (i = 0; i < ARRAY_SIZE(prog_conf); i++) {
		if (!prog_conf[i].name[0])
			continue;
		seq_printf(s, "%s%s", sp, prog_conf[i].name);
		sp = " ";
	}
	seq_puts(s, "\n");

	return 0;
}

static int dcsys_pc_available_progs_open(struct inode *inode, struct file *file)
{
	return single_open(file, dcsys_pc_available_progs_show,
		inode->i_private);
}

static const struct file_operations dcsys_pc_available_progs_fops = {
	.owner   = THIS_MODULE,
	.open    = dcsys_pc_available_progs_open,
	.read    = seq_read,
	.release = single_release,
};

static int dcsys_pc_prog_sel_show(struct seq_file *s, void *data)
{
	unsigned int rf_id = PTR_U32(s->private);
	unsigned int val;

	dcsys_pc_get_regfield(rf_id, &val);
	seq_printf(s, "%s\n", sel_to_name(val));

	return 0;
}

static int dcsys_pc_prog_sel_open(struct inode *inode, struct file *file)
{
	return single_open(file, dcsys_pc_prog_sel_show, inode->i_private);
}

static ssize_t dcsys_pc_prog_sel_write(struct file *file,
	const char __user *user_buf, size_t count, loff_t *ppos)
{
	char buf[32];
	size_t buf_size;
	int val;
	unsigned int rf_id = PTR_U32(file->f_inode->i_private);
	int i;

	buf_size = min(count, (sizeof(buf)-1));
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;

	buf[buf_size] = '\0';

	for (i = 0; i < buf_size; i++) {
		if (!buf[i])
			break;
		if ('a' <= buf[i] && buf[i] <= 'z')
			continue;
		if ('0' <= buf[i] && buf[i] <= '9')
			continue;
		if (buf[i] == '-' || buf[i] == '_')
			continue;
		buf[i] = '\0';
		break;
	}

	val = name_to_sel(buf);
	dcsys_pc_set_regfield(rf_id, val);

	return count;
}

static const struct file_operations dcsys_pc_prog_sel_fops = {
	.owner   = THIS_MODULE,
	.open    = dcsys_pc_prog_sel_open,
	.read    = seq_read,
	.write   = dcsys_pc_prog_sel_write,
	.release = single_release,
};

static int dcsys_pc_prog_dc_sel_set(void *data, u64 val)
{
	unsigned int rf_id = PTR_U32(data);

	if (val != 0 && val != 1)
		return -EINVAL;

	dcsys_pc_set_regfield(rf_id, val);
	return 0;
}

static int dcsys_pc_prog_dc_sel_get(void *data, u64 *val)
{
	unsigned int rf_id = PTR_U32(data);
	unsigned int v;

	dcsys_pc_get_regfield(rf_id, &v);
	*val = v;
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(dcsys_pc_prog_dc_sel_fops, dcsys_pc_prog_dc_sel_get,
	dcsys_pc_prog_dc_sel_set, "%lld\n");

static int dcsys_pc_go_set(void *data, u64 val)
{
	if (val == 1)
		return dcsys_pc_start(pc);
	if (val == 0)
		return dcsys_pc_stop(pc);

	return -EINVAL;
}

DEFINE_SIMPLE_ATTRIBUTE(dcsys_pc_go_fops, NULL, dcsys_pc_go_set, "%lld\n");

static int dcsys_pc_lock_set(void *data, u64 val)
{
	int ret;

	if (val == 1) {
		dcsys_pc_set_owner(pc, DCSYS_PC_FORCE_SET);

		/* stop pc started by previous owner */
		ret = dcsys_pc_is_stopped(pc);
		if (ret != 1)
			dcsys_pc_stop(pc);
	}

	if (val == 0) {
		ret = dcsys_pc_is_owner(pc);
		if (ret != 1)
			return -EACCES;

		ret = dcsys_pc_is_stopped(pc);
		if (ret != 1)
			dcsys_pc_stop(pc);

		dcsys_pc_clear_owner(pc);
	}

	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(dcsys_pc_lock_fops, NULL, dcsys_pc_lock_set, "%lld\n");

void dcsys_pc_debugfs_init(struct device *dev)
{
	pc = dcsys_pc_simple_get(dev);
	core_dev = dev;
	root = debugfs_create_dir("dcsys_pc", NULL);

#define CREATE_FILE(_name) \
	debugfs_create_file("dcsys_pc_" #_name, 0644, root, NULL, \
		&dcsys_pc_ ## _name ## _fops)
	CREATE_FILE(summary);
	CREATE_FILE(available_progs);
	CREATE_FILE(go);
	CREATE_FILE(lock);

#define CREATE_SYSH_FILES(_id) \
do { \
	debugfs_create_file("dcsys_pc_sysh_prog" #_id  "_sel", 0644, \
		root, U32_PTR(PC_SYSH_PROG ## _id ## _SEL), \
		&dcsys_pc_prog_sel_fops); \
	debugfs_create_file("dcsys_pc_sysh_prog" #_id  "_dc_sel", 0644, \
		root, U32_PTR(PC_SYSH_PROG ## _id ## _DC_SEL), \
		&dcsys_pc_prog_dc_sel_fops); \
} while (0)

	CREATE_SYSH_FILES(0);
	CREATE_SYSH_FILES(1);
	CREATE_SYSH_FILES(2);
	CREATE_SYSH_FILES(3);
	CREATE_SYSH_FILES(4);
	CREATE_SYSH_FILES(5);
	CREATE_SYSH_FILES(6);
	CREATE_SYSH_FILES(7);

#undef CREATE_SYSH_FILES

	debugfs_create_file("dcsys_pc_sys_prog0_sel", 0644, root,
		U32_PTR(PC_SYS_PROG0_SEL), &dcsys_pc_prog_sel_fops);
	debugfs_create_file("dcsys_pc_sys_prog1_sel", 0644, root,
		U32_PTR(PC_SYS_PROG1_SEL), &dcsys_pc_prog_sel_fops);
	debugfs_create_file("dcsys_pc_sys_prog2_sel", 0644, root,
		U32_PTR(PC_SYS_PROG2_SEL), &dcsys_pc_prog_sel_fops);
}

