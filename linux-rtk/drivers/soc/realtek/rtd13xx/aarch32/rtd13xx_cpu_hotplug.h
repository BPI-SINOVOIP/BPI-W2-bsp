/*
 * rtd13xx_cpu_hotplug.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#ifndef RTD13xx_CPU_HOTPLUG_H_
#define RTD13xx_CPU_HOTPLUG_H_

#include <asm/virt.h>

void __cpu_do_lowpower(unsigned long secondary_entry_addr);

#endif /* RTD13xx_CPU_HOTPLUG_H_ */
