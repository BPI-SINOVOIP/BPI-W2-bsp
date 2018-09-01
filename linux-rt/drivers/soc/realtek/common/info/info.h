/*
 * info.h
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_REALTEK_INFO_H__
#define __SOC_REALTEK_INFO_H__

struct seq_file;

typedef	int (*info_dump_fn_t)(struct seq_file *s);

int info_dump_create_file(const char *name, info_dump_fn_t func);

#endif
