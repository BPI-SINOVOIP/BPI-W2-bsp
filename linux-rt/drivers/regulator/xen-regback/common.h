/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __XEN_REGBACK_COMMON_H__
#define __XEN_REGBACK_COMMON_H__

int xen_regif_xenbus_init(void);

struct device;

#define VREG_MAX_REGULATOR_SIZE 10

void vreg_reset(void);
int vreg_regulator_get(struct device *dev, const char *name);
void vreg_regulator_put(int id);
int vreg_regulator_set_volt(int id, int vsel);
int vreg_regulator_get_volt(int id);
int vreg_regulator_count_voltages(int id);
int vreg_regulator_list_voltage(int id, int sel);
int vreg_regulator_get_constraints(int id, int csel);


#endif /* __XEN_REGBACK_COMMON_H__ */
