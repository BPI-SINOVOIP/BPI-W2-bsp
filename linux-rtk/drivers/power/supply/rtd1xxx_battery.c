/*
 * Battery driver for RTD1xxx
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

struct power_supply *battery;

static int rtd1xxx_bat_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	int ret = 0;

	switch (psp) {
 	case POWER_SUPPLY_PROP_PRESENT:

		val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:

		val->intval = 100;
		break;
	case POWER_SUPPLY_PROP_STATUS:

		val->intval = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case POWER_SUPPLY_PROP_HEALTH:

		val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:

		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CHARGE_COUNTER:

		val->intval = 22;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:

		val->intval = 0;
		break;
	default:
		pr_err("%s %d \n", __func__, __LINE__);

		ret = -ENODEV;
		break;
	}
	return ret;
}
static enum power_supply_property rtd1xxx_battery_props[] = {

	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_TECHNOLOGY,
    POWER_SUPPLY_PROP_CHARGE_COUNTER,
    POWER_SUPPLY_PROP_CURRENT_NOW,
};

static const struct power_supply_desc battery_desc = {
	.name		= "rtd1xxx-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= rtd1xxx_battery_props,
	.num_properties	= ARRAY_SIZE(rtd1xxx_battery_props),
	.get_property	= rtd1xxx_bat_get_prop,
};


static struct platform_device *pdev;


static int __init rtd1xxx_battery_init(void)
{
	int ret = 0;
	pdev = platform_device_register_simple("rtd1xxx-battery",
                                                   0, NULL, 0);
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		pr_err("%s platform_device_register_simple \n", __func__);
		goto out;
	}

	battery = power_supply_register(&pdev->dev, &battery_desc, NULL);
	if (IS_ERR(battery)) {
		ret = PTR_ERR(battery);
		pr_err("%s power_supply_register err \n", __func__);
		battery = NULL;
		goto out;
	}

out:
	return ret;
}

static void rtd1xxx_battery_exit(void)
{
	power_supply_unregister(battery);
	platform_device_unregister(pdev);
}


module_init(rtd1xxx_battery_init);
module_exit(rtd1xxx_battery_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Battery power supply driver for RTD1xxx ");
MODULE_ALIAS("platform:rtd1xxx-battery");
