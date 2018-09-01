#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/of_regulator.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>
#include <linux/delay.h>
#include <linux/of_address.h>

static struct of_regulator_match rtkgpio_matches[] = {
	{ .name = "rtkgpio_regulator", .driver_data = NULL, },
};

int gpio0, gpio1, voltage;
static const unsigned int rtkgpio_dcdc_map[] = {
	0, 2, 3,
};

static int rtkgpio_list_voltage(struct regulator_dev *rdev, unsigned int sel)
{	
	if (!rdev->desc->volt_table) {
		BUG_ON(!rdev->desc->volt_table);
		return -EINVAL;
	}

	if (sel >= rdev->desc->n_voltages)
		return -EINVAL;

	return rdev->desc->volt_table[sel];
}
static int rtkgpio_get_voltage_sel(struct regulator_dev *rdev)
{
	return voltage;
}

static int rtkgpio_set_voltage_sel(struct regulator_dev *rdev, unsigned sel)
{
//	struct rtk_pmic_dev *pmic_dev = rdev_get_drvdata(rdev);
	unsigned char val;

	val = rtkgpio_dcdc_map[sel];
	gpio_set_value(gpio0, val&0x1);
	gpio_set_value(gpio1, (val&0x2)>>1);

	voltage = sel;	
	return 0;
}

static struct regulator_ops rtkgpio_regulator_ops = {
	.list_voltage = rtkgpio_list_voltage,
	.set_voltage_sel = rtkgpio_set_voltage_sel,
	.get_voltage_sel = rtkgpio_get_voltage_sel,
//	.enable = gmt_g2227_enable,
//	.disable = gmt_g2227_disable,
//	.is_enabled = regulator_is_enabled_regmap,
};

static const unsigned int rtkgpio_dcdc1_vtbl[] = {
	850000, 950000, 1050000,
};


static struct regulator_desc rtkgpio_regulator_desc[] = {
	{
		.name = "rtkgpio_regulator",
		.id = 0,
		.ops = &rtkgpio_regulator_ops,
		.n_voltages = ARRAY_SIZE(rtkgpio_dcdc1_vtbl),
		.volt_table = rtkgpio_dcdc1_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
//		.vsel_reg = 0x13,
//		.vsel_mask = 0xC0,
//		.enable_reg = 0x5,
//		.enable_mask = 1 << 7,
	},
};

static int rtkgpio_regulator_probe(struct platform_device *pdev)
{
	struct regulator_config cfg = { };
	struct of_regulator_match *match;
	struct regulator_dev *rdev;
	struct device *dev = &pdev->dev;

	gpio0 = of_get_gpio(dev->of_node, 0);
	gpio1 = of_get_gpio(dev->of_node, 1);

	if(gpio_request(gpio0, dev->of_node->name))
		printk(KERN_ERR "gpio_request gpio0 fail\n");

	if(gpio_request(gpio1, dev->of_node->name))
		printk(KERN_ERR "gpio_request gpio1 fail\n");

	voltage = 1;	//default 950000

	match = rtkgpio_matches;
	of_regulator_match(dev, dev->of_node, match, ARRAY_SIZE(rtkgpio_matches));
	
	cfg.dev = dev;
	cfg.init_data = match[0].init_data;
	cfg.driver_data = dev_get_drvdata(&pdev->dev);

	rdev = devm_regulator_register(dev, &rtkgpio_regulator_desc[0], &cfg);
	return 0;
}


static struct of_device_id rtkgpio_regulator_id[] = {
	{ .compatible = "rtkgpio-regulator" },
	{ /* Sentinel */ },
};
MODULE_DEVICE_TABLE(of, rtkgpio_regulator_id);

static struct platform_driver rtkgpio_regulator_driver = {
	.probe = rtkgpio_regulator_probe,
//	.remove = rtkgpio_regulator_remove,
	.driver		= {
		.name	= "rtkgpio-regulator",
		.of_match_table = rtkgpio_regulator_id,
	},
};

static int __init rtkgpio_regulator_init(void)
{
	return platform_driver_register(&rtkgpio_regulator_driver);
}
subsys_initcall(rtkgpio_regulator_init);

static void __exit rtkgpio_regulator_exit(void)
{
	platform_driver_unregister(&rtkgpio_regulator_driver);
}
module_exit(rtkgpio_regulator_exit);

/* Module information */
MODULE_AUTHOR("Simon Hsu");
MODULE_DESCRIPTION("RTK GPIO voltage and current regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk-gpio-regulator");
