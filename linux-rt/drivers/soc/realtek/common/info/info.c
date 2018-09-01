/*
 * info.c - Simple API for dump information in DEBUGFS
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
#include "info.h"

static struct dentry *info_dump_root;

struct info_dump {
	info_dump_fn_t func;
};

static int info_dump_show(struct seq_file *s, void *data)
{
	struct info_dump *info = s->private;

	return info->func(s);
}

static int info_dump_open(struct inode *inode, struct file *file)
{
	return single_open(file, info_dump_show, inode->i_private);
}

static const struct file_operations info_dump_fops = {
	.owner   = THIS_MODULE,
	.open    = info_dump_open,
	.read    = seq_read,
	.release = single_release,
};

static int __init info_dump_init(void)
{
	info_dump_root = debugfs_create_dir("info", NULL);
	return 0;
}
arch_initcall(info_dump_init);

int info_dump_create_file(const char *name, info_dump_fn_t func)
{
	struct info_dump *info;
	struct dentry *d;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->func = func;

	d = debugfs_create_file(name, 0644, info_dump_root, info,
		&info_dump_fops);
	if (!d) {
		kfree(info);
		return -ENOMEM;
	}

	return 0;
}

