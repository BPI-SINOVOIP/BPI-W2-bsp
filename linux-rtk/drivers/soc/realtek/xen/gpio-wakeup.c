#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/switch.h>
#include <linux/of.h>

#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>

#include <linux/sysfs.h>
#include <linux/completion.h>

#define DEV_NAME "GPIO_WAKEUP"

struct completion wu_completion;

bool gpio_wakeup_en[136];
bool gpio_wakeup_act[136];

struct class *wakeup_class;
int wu_gpio_num;
int gpio_irq_base;

static ssize_t gpio_wakeup_show(struct class *class,
		struct class_attribute *attr, char *buf)
{
	if (completion_done(&wu_completion))
		reinit_completion(&wu_completion);

	wait_for_completion_interruptible(&wu_completion);
	return sprintf(buf, "%d\n", wu_gpio_num);
}

static CLASS_ATTR(gpio_wakeup, 0444, gpio_wakeup_show, NULL);


static irqreturn_t gpio_wakeup_isr(int irq, void *data)
{
	int wakeup_value;
	int gpio_num = irq - gpio_irq_base;

	if(!gpio_wakeup_en[gpio_num])
		return IRQ_HANDLED;
	if (gpio_wakeup_act[gpio_num])
		wakeup_value = gpio_get_value(gpio_num) ? 0:1;
	else
		wakeup_value = gpio_get_value(gpio_num) ? 1:0;

	if(wakeup_value) {
		wu_gpio_num = gpio_num;
		complete_all(&wu_completion);
	}
	return IRQ_HANDLED;
}

static int rtk_gpio_wakeup_probe(struct platform_device *pdev)
{
	struct device_node *nd = NULL;
	struct device *gpio_dev;
	const u32 *prop_en;
	const u32 *prop_act;
	int ret = 0;
	int wu_gpio_en = 0;
	int wu_gpio_act = 0;
	int wu_gpio_list = 0;
	int en;
	int act;
	int i = 0;
	int wu_gpio;
	int wu_irq;

	gpio_dev = &pdev->dev;
	nd = pdev->dev.of_node;

	wakeup_class = class_create(THIS_MODULE, "wakeup");
	if (wakeup_class == NULL)
		pr_err("failed to create wakeup attribute!\n");
	ret = class_create_file(wakeup_class, &class_attr_gpio_wakeup);

	wu_gpio_list = of_gpio_named_count(nd, "wakeup-gpio-list");
	prop_en = of_get_property(nd, "wakeup-gpio-enable", &wu_gpio_en);
	prop_act = of_get_property(nd, "wakeup-gpio-activity", &wu_gpio_act);
	wu_gpio_en  /= sizeof(u32);
	wu_gpio_act /= sizeof(u32);

	pr_info("[%s] wakeup-gpio Cnt: en(%d) act(%d) list(%d)\n",
		DEV_NAME, wu_gpio_en, wu_gpio_act, wu_gpio_list);

	if (wu_gpio_en != 0 && (wu_gpio_en == wu_gpio_act)
		&& (wu_gpio_act == wu_gpio_list)) {

		for (i = 0 ; i < wu_gpio_list ; i++) {
			en  = of_read_number(prop_en, 1 + i);
			act = of_read_number(prop_act, 1 + i);
			wu_gpio = of_get_named_gpio(nd, "wakeup-gpio-list", i);

			if (!en) {
				pr_err("[%s] wakeup-gpio[%d] States is disable!",
					DEV_NAME, i);
				pr_err(" (en:%d act:%d gpio:%d)\n",
					en, act, wu_gpio);
				continue;
			}

			if (gpio_request(wu_gpio, nd->name)) {
				pr_err("[%s] wakeup-gpio[%d] Request failed!",
					DEV_NAME, i);
				pr_err(" (en:%d act:%d gpio:%d)\n",
					en, act, wu_gpio);
			} else {
				gpio_free(wu_gpio);
			}

			gpio_direction_input(wu_gpio);

			pr_info("[%s] wakeup-gpio[%d] Successful registration!",
				DEV_NAME, i);
			pr_info(" (en:%d act:%d gpio:%d)\n",
				en, act, wu_gpio);

			gpio_wakeup_en[wu_gpio] = en ? 1:0;
			gpio_wakeup_act[wu_gpio] = act ? 1:0;

			gpio_set_debounce(wu_gpio, 1000);
			wu_irq = gpio_to_irq(wu_gpio);

			if (!wu_irq)
				pr_err("Fail to get cvbs irq");
			else
				pr_debug("irq_num(%u)\n", wu_irq);

			irq_set_irq_type(wu_irq, IRQ_TYPE_EDGE_BOTH);
			ret = request_irq(wu_irq, gpio_wakeup_isr,
					IRQF_SHARED, "wakeup_gpio", gpio_dev);
			if (ret)
				pr_err("Cannot register IRQ %d", wu_irq);
		}
	}

	gpio_irq_base = gpio_to_irq(0);

	init_completion(&wu_completion);

	return ret;
}

static const struct of_device_id rtk_gpio_wakeup_table[] = {
	{.compatible = "realtek,gpio_wakeup",},
	{},
};


static struct platform_driver rtk_gpio_wakeup_driver = {
	.probe		= rtk_gpio_wakeup_probe,
	.driver		= {
		.name	= "gpio_wakeup",
		.of_match_table = of_match_ptr(rtk_gpio_wakeup_table),
		.owner	= THIS_MODULE,
	},
};


static int __init rtk_gpio_wakeup_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&rtk_gpio_wakeup_driver);
	if (ret != 0)
		goto err_register;

	return 0;
err_register:
	platform_driver_unregister(&rtk_gpio_wakeup_driver);

	return -EFAULT;
}

static void __exit rtk_gpio_wakeup_exit(void)
{

	class_remove_file(wakeup_class, &class_attr_gpio_wakeup);
	class_destroy(wakeup_class);
	platform_driver_unregister(&rtk_gpio_wakeup_driver);
}


module_init(rtk_gpio_wakeup_init);
module_exit(rtk_gpio_wakeup_exit);
MODULE_DESCRIPTION("Realtek GPIO wakeup driver");
MODULE_LICENSE("GPL v2");



