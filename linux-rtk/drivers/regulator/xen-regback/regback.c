/*
 * regback.c - xen regulator backend driver
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "regif-be: " fmt

#include <linux/regulator/consumer.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/driver.h>
#include <linux/list.h>
#include <xen/xen.h>
#include "regif.h"
#include "common.h"
#include "../internal.h"

struct vreg_info {
	int id;
	struct regulator *regulator;
	char name[REGIF_NAME_LENGTH];
};

static int vreg_list_count = 0;
static struct vreg_info vreg_list[VREG_MAX_REGULATOR_SIZE];
#define vreg_to_regulator(_id)  (vreg_list[(_id)].regulator)

void vreg_reset(void)
{
	int i;
	vreg_list_count = 0;
	for (i = 0; i < VREG_MAX_REGULATOR_SIZE; i++) {
		vreg_list[i].id = 0;
		vreg_list[i].regulator = NULL;
		vreg_list[i].name[0] = 0;
	}
}

int vreg_regulator_get(struct device *dev, const char *name)
{
	struct regulator *regulator;
	int i;

	/* list is full */
	if (vreg_list_count >= VREG_MAX_REGULATOR_SIZE) {
		WARN_ON(1);
		return -ENOSPC;
	}

	/* find an existing resource */
	for (i = 0; i < vreg_list_count; i++)
		if (strcmp(name, vreg_list[i].name) == 0 &&
			vreg_list[i].regulator != NULL)
			return i;

	/* if not existed, try to get */
	regulator = devm_regulator_get(dev, name);
	if (IS_ERR_OR_NULL(regulator))
		return -EINVAL;

	/* add to the list */
	i = vreg_list_count;
	vreg_list[i].id = i;
	vreg_list[i].regulator = regulator;
	strncpy(vreg_list[i].name, name, REGIF_NAME_LENGTH);
	vreg_list_count ++;

	return vreg_list[i].id;
}

void vreg_regulator_put(int id)
{
	struct regulator *regulator = vreg_to_regulator(id);
	regulator_put(regulator);
	vreg_list[id].regulator = NULL;
}

int vreg_regulator_set_volt(int id, int vsel)
{
	struct regulator *regulator = vreg_to_regulator(id);
	int ret;

	ret = regulator_list_voltage(regulator, vsel);
	return regulator_set_voltage(regulator, ret, ret);
}

int vreg_regulator_get_volt(int id)
{
	struct regulator *regulator = vreg_to_regulator(id);
	return regulator_get_voltage(regulator);
}

int vreg_regulator_count_voltages(int id)
{
	struct regulator *regulator = vreg_to_regulator(id);
	return regulator_count_voltages(regulator);
}

int vreg_regulator_list_voltage(int id, int sel)
{
	struct regulator *regulator = vreg_to_regulator(id);
	return regulator_list_voltage(regulator, sel);
}

int vreg_regulator_get_constraints(int id, int csel)
{
	struct regulator *regulator = vreg_to_regulator(id);
	int ret = -1;
	switch (csel) {
	case VREG_CONSTRAINTS_MAX_VOLT:
		ret = regulator->rdev->constraints->max_uV;
		break;
	case VREG_CONSTRAINTS_MIN_VOLT:
		ret = regulator->rdev->constraints->min_uV;
		break;
	case VREG_CONSTRAINTS_BOOT_ON:
		ret = regulator_is_enabled(regulator);
		break;
	case VREG_CONSTRAINTS_ALWAYS_ON:
		ret = regulator->rdev->constraints->always_on;
		break;
	case VREG_CONSTRAINTS_VALID_OPS:
		ret = regulator->rdev->constraints->valid_ops_mask;
		break;
	}
	return ret;
}

static int __init xen_regif_init(void)
{
	if (!xen_domain())
		return -ENODEV;

	/* only exists in dom0 */
	if (!xen_initial_domain())
		return -ENODEV;

	return xen_regif_xenbus_init();
}
late_initcall(xen_regif_init);

