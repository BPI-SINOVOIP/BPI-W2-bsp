/*
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __SOC_REALTEK_DEVFREQ_GOVERNOR_DATA_H_INCLUDED
#define __SOC_REALTEK_DEVFREQ_GOVERNOR_DATA_H_INCLUDED

struct devfreq_ltl_data {
	int th_cap;
	int th_cap_short;
	int th_cap_long;

	/* private data */
	int prev_cap;
	int weighted_cap_long;
	int weighted_cap_short;
	struct notifier_block nb;
};



#endif
