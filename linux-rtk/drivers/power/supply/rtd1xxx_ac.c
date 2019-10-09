/*
 * AC driver for RTD1xxx
 *
 * Copyright (c) 
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>

struct power_supply *ac;

static int rtd1xxx_ac_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:

		val->intval = 1;
		break;	
	default:
		pr_err("%s %d \n", __func__, __LINE__);

		ret = -ENODEV;
		break;
	}
	return ret;
}
static enum power_supply_property rtd1xxx_ac_props[] = {

	POWER_SUPPLY_PROP_ONLINE,
};

static const struct power_supply_desc ac_desc = {
	.name		= "rtd1xxx-ac",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= rtd1xxx_ac_props,
	.num_properties	= ARRAY_SIZE(rtd1xxx_ac_props),
	.get_property	= rtd1xxx_ac_get_prop,
};


static struct platform_device *pdev;


static int __init rtd1xxx_ac_init(void)
{
	int ret = 0;
	pdev = platform_device_register_simple("rtd1xxx-ac",
                                                   0, NULL, 0);
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		pr_err("%s platform_device_register_simple \n", __func__);
		goto out;
	}

	ac = power_supply_register(&pdev->dev, &ac_desc, NULL);
	if (IS_ERR(ac)) {
		ret = PTR_ERR(ac);
		pr_err("%s power_supply_register err \n", __func__);
		ac = NULL;
		goto out;
	}

out:
	return ret;
}

static void rtd1xxx_ac_exit(void)
{
	power_supply_unregister(ac);
	platform_device_unregister(pdev);
}


module_init(rtd1xxx_ac_init);
module_exit(rtd1xxx_ac_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("AC power supply driver for RTD1xxx ");
MODULE_ALIAS("platform:rtd1xxx-ac");
