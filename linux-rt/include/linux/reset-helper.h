/*
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _LINUX_RESET_HELPER_H_
#define _LINUX_RESET_HELPER_H_

#ifdef CONFIG_RESET_CONTROLLER

struct reset_control;

struct reset_control * rstc_get(const char * name);

int rstc_add(struct reset_control *rstc, const char * name);

#else

static inline struct reset_control * rstc_get(const char * name)
{
	WARN_ON(1);
	return NULL;
}


static inline int rstc_add(struct reset_control *rstc, const char * name)
{
	WARN_ON(1);
	return 0;
}

#endif

#endif /* _LINUX_RESET_HELPER_H_ */
