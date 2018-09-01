/*
 * Driver for keys on GPIO lines capable of generating interrupts.
 *
 * Copyright 2005 Phil Blundell
 * Copyright 2010, 2011 David Jander <david@protonic.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/spinlock.h>

struct gpio_button_data {
	const struct gpio_keys_button *button;
	struct input_dev *input;

	struct timer_list release_timer;
	unsigned int release_delay;	/* in msecs, for IRQ-only buttons */

	struct delayed_work work;
	unsigned int software_debounce;	/* in msecs, for GPIO-driven buttons */

	unsigned int irq;
	spinlock_t lock;
	bool disabled;
	bool key_pressed;
#if LEGACY_CMD
	unsigned int cmd_gpio[4]; 
#endif
};

struct gpio_keys_drvdata {
	const struct gpio_keys_platform_data *pdata;
	struct input_dev *input;
	struct mutex disable_lock;
	struct gpio_button_data data[0];
};

struct cmd_key {
        const u32 scancode;
        const u32 keycode;
	u32 rx;
	u32 repeat;
};

static struct cmd_key rtk_cmd_keys[] = {
#if LEGACY_CMD
        {0x00, KEY_VOICECOMMAND, 0, 0},                     
        {0x08, KEY_HOME, 0, 0},                     
        {0x09, KEY_VOLUMEUP, 0, 1},       
        {0x0A, KEY_VOLUMEDOWN, 0, 1},          
	{0x05, KEY_ESC, 0, 0},                   
        {0x0D, KEY_OK, 0, 0},                     
        {0x0E, KEY_PLAY, 0, 0},                                                        
        {0x0F, KEY_PAUSE, 0, 0},   
	{0x07, KEY_STOP, 0, 0}, 
	{0x0B, KEY_UP, 0, 0},                         
        {0x0C, KEY_DOWN, 0, 0},                     
        {0x03, KEY_RIGHT, 0, 0},                                                        
        {0x04, KEY_LEFT, 0, 0},   
	{0x06, KEY_ALEXA, 0, 0}, 
#else
        {0x00, KEY_SEARCH, 0, 0},
#endif
};

static int rtk_cmd_keys_count = ARRAY_SIZE(rtk_cmd_keys);
static u32 trigger_cmd = 0;


static ssize_t gpio_cmds_show_cmds(struct device *dev,                
                                     struct device_attribute *attr,     
                                     char *buf)                         
{                                                                       
                                                                        
        return sprintf(buf, "%d\n", trigger_cmd);              
                                            
}


static ssize_t gpio_cmds_store_cmds(struct device *dev,               
                                      struct device_attribute *attr,    
                                      const char *buf,                 
                                      size_t count)                    
{                                                                       
                           
	trigger_cmd = simple_strtol(buf, 0, 16);                                                                                  
       	return count;                                                   
}


static DEVICE_ATTR(cmds, 0644,
                   gpio_cmds_show_cmds,
                   gpio_cmds_store_cmds);

static struct attribute *gpio_cmds_attrs[] = {
        &dev_attr_cmds.attr,
        NULL,
};

static struct attribute_group gpio_cmds_attr_group = {
        .attrs = gpio_cmds_attrs,
};

static void gpio_keys_gpio_report_event(struct gpio_button_data *bdata)
{
	const struct gpio_keys_button *button = bdata->button;
	struct input_dev *input = bdata->input;
	unsigned int type = button->type ?: EV_KEY;
	int state = (gpio_get_value_cansleep(button->gpio) ? 1 : 0) ^ button->active_low;
	u32 map_data = 0;
	int i, j;

#if LEGACY_CMD
	for (i =0 ; i < 4; i++) {

		if(gpio_request(bdata->cmd_gpio[i], "cmd"))  {       //request gpio
        		pr_err("%s ERROR Request cmd_gpio[%d] fail\n",__func__, i);
			return;
		}
        	else if (bdata->cmd_gpio[i]!= -1) {
			gpio_direction_input(bdata->cmd_gpio[i]);
			pr_debug("gpio_direction_input(bdata->cmd_gpio[%d]) = %d \n", i, gpio_get_value(bdata->cmd_gpio[i]));

			map_data |= (gpio_get_value(bdata->cmd_gpio[i]) << i);	
			
			gpio_free(bdata->cmd_gpio[i]);
		}
	}
	for (i = 0; i < rtk_cmd_keys_count; i++) {

                if (map_data == rtk_cmd_keys[i].scancode) {

			pr_err("[getscancode] found! keycode=%d scancode=0x%x !\n", rtk_cmd_keys[i].keycode, rtk_cmd_keys[i].scancode);

			if ( i == 0) {
				trigger_cmd = 1;
				return ;					
			}
			trigger_cmd = 0;
	
			rtk_cmd_keys[i].rx++;

			j = rtk_cmd_keys[i].repeat + 1;
			while ( j--) {
				input_report_key(input, rtk_cmd_keys[i].keycode, 1);
             			input_event(input, EV_SYN, SYN_REPORT, rtk_cmd_keys[i].rx);
				
				input_report_key(input, rtk_cmd_keys[i].keycode, 0);
				input_event(input, EV_SYN, SYN_REPORT, rtk_cmd_keys[i].rx);
				if (j)
					msleep(500);
			}
                        return ;
                }
        }
#else
        i = 0;
        pr_err("[getscancode] found! keycode=%d scancode=0x%x !\n", rtk_cmd_keys[i].keycode, rtk_cmd_keys[i].scancode);
        input_report_key(input, rtk_cmd_keys[i].keycode, 1);
        input_event(input, EV_SYN, SYN_REPORT, rtk_cmd_keys[i].rx);

        input_report_key(input, rtk_cmd_keys[i].keycode, 0);
        input_event(input, EV_SYN, SYN_REPORT, rtk_cmd_keys[i].rx);
        trigger_cmd = 1;
#endif

}

static void gpio_keys_gpio_work_func(struct work_struct *work)
{
	struct gpio_button_data *bdata =
		container_of(work, struct gpio_button_data, work.work);

	gpio_keys_gpio_report_event(bdata);

	if (bdata->button->wakeup)
		pm_relax(bdata->input->dev.parent);
}

static irqreturn_t gpio_keys_gpio_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;

	BUG_ON(irq != bdata->irq);

	if (bdata->button->wakeup)
		pm_stay_awake(bdata->input->dev.parent);

	mod_delayed_work(system_wq,
			 &bdata->work,
			 msecs_to_jiffies(bdata->software_debounce));

	return IRQ_HANDLED;
}

static void gpio_keys_irq_timer(unsigned long _data)
{
	struct gpio_button_data *bdata = (struct gpio_button_data *)_data;
	struct input_dev *input = bdata->input;
	unsigned long flags;

	spin_lock_irqsave(&bdata->lock, flags);
	if (bdata->key_pressed) {
		input_event(input, EV_KEY, bdata->button->code, 0);
		input_sync(input);
		bdata->key_pressed = false;
	}
	spin_unlock_irqrestore(&bdata->lock, flags);
}

static irqreturn_t gpio_keys_irq_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;
	const struct gpio_keys_button *button = bdata->button;
	struct input_dev *input = bdata->input;
	unsigned long flags;

	BUG_ON(irq != bdata->irq);

	spin_lock_irqsave(&bdata->lock, flags);

	if (!bdata->key_pressed) {
		if (bdata->button->wakeup)
			pm_wakeup_event(bdata->input->dev.parent, 0);

		input_event(input, EV_KEY, button->code, 1);
		input_sync(input);

		if (!bdata->release_delay) {
			input_event(input, EV_KEY, button->code, 0);
			input_sync(input);
			goto out;
		}

		bdata->key_pressed = true;
	}

	if (bdata->release_delay)
		mod_timer(&bdata->release_timer,
			jiffies + msecs_to_jiffies(bdata->release_delay));
out:
	spin_unlock_irqrestore(&bdata->lock, flags);
	return IRQ_HANDLED;
}

static void gpio_keys_quiesce_key(void *data)
{
	struct gpio_button_data *bdata = data;

	if (gpio_is_valid(bdata->button->gpio))
		cancel_delayed_work_sync(&bdata->work);
	else
		del_timer_sync(&bdata->release_timer);
}

static int gpio_keys_setup_key(struct platform_device *pdev,
				struct input_dev *input,
				struct gpio_button_data *bdata,
				const struct gpio_keys_button *button)
{
	const char *desc = button->desc ? button->desc : "gpio_cmds";
	struct device *dev = &pdev->dev;
	irq_handler_t isr;
	unsigned long irqflags;
	int irq;
	int error;
	struct device_node *node;
	unsigned int ldo_gpio;
	int i;

	node = dev->of_node;
	if (!node)
		return -ENODEV;

	bdata->input = input;
	bdata->button = button;
	spin_lock_init(&bdata->lock);

	if (gpio_is_valid(button->gpio)) {
		//if(gpio_request(button->gpio, "gpio_cmds")) {        //request gpio
                //	dev_err(dev, "%s ERROR Request ldo gpio fail\n",__func__);
		//	return -EINVAL;
		//}
		//gpio_direction_input(button->gpio);


		error = devm_gpio_request_one(&pdev->dev, button->gpio,
					      GPIOF_IN, desc);
		if (error < 0) {
			dev_err(dev, "Failed to request GPIO %d, error %d\n",
				button->gpio, error);
			return error;
		}

		if (button->debounce_interval) {
			error = gpio_set_debounce(button->gpio,
					button->debounce_interval * 1000);
			/* use timer if gpiolib doesn't provide debounce */
			if (error < 0)
				bdata->software_debounce =
						button->debounce_interval;
		}

		if (button->irq) {
			bdata->irq = button->irq;
			dev_err(dev, "[irq] = %d \n", bdata->irq);

		} else {
			irq = gpio_to_irq(button->gpio);
			if (irq < 0) {
				error = irq;
				dev_err(dev,
					"Unable to get irq number for GPIO %d, error %d\n",
					button->gpio, error);
				return error;
			}
			bdata->irq = irq;
			dev_err(dev, "(irq) = %d \n", bdata->irq);
		}

		
#if LEGACY_CMD	
		bdata->cmd_gpio[0] = of_get_named_gpio(node, "5679_gpio2", 0);
                if (!gpio_is_valid(bdata->cmd_gpio[0])) {
			dev_err(dev, "Found cmd without 5679_gpio2 \n");
                        return -EINVAL;
			
		}
	
		bdata->cmd_gpio[1] = of_get_named_gpio(node, "5679_gpio3", 0);
                if (!gpio_is_valid(bdata->cmd_gpio[1])) {
			dev_err(dev, "Found cmd without 5679_gpio3 \n");
                        return -EINVAL;
			
		}

		bdata->cmd_gpio[2] = of_get_named_gpio(node, "5679_gpio12", 0);
                if (!gpio_is_valid(bdata->cmd_gpio[2])) {
			dev_err(dev, "Found cmd without 5679_gpio12 \n");
                        return -EINVAL;
			
		}
	
		bdata->cmd_gpio[3] = of_get_named_gpio(node, "5679_gpio13", 0);
                if (!gpio_is_valid(bdata->cmd_gpio[3])) {
			dev_err(dev, "Found cmd without 5679_gpio13 \n");
                        return -EINVAL;
			
		}

		ldo_gpio = of_get_named_gpio(node, "5679_ldo", 0);
                if (gpio_is_valid(ldo_gpio)) {

			if(gpio_request(ldo_gpio, "ldo"))         //request gpio
                        	dev_err(dev, "%s ERROR Request ldo gpio fail\n",__func__);
                        else if (ldo_gpio != -1) {
                        	if (gpio_direction_output(ldo_gpio, 0))
                                	dev_err(dev, "%s ERROR ldo gpio ouput 0 fail \n", __func__);;
				mdelay(100);                     // may be too long ?
				if (gpio_direction_output(ldo_gpio, 1))
                                	dev_err(dev, "%s ERROR ldo gpio ouput 0 fail \n", __func__);;

                                gpio_free(ldo_gpio);

                        }

                }
#endif
				
		INIT_DELAYED_WORK(&bdata->work, gpio_keys_gpio_work_func);

		isr = gpio_keys_gpio_isr;
		irqflags = IRQF_TRIGGER_RISING /*| IRQF_TRIGGER_FALLING*/;

	} else {
		if (!button->irq) {
			dev_err(dev, "No IRQ specified\n");
			return -EINVAL;
		}
		bdata->irq = button->irq;

		if (button->type && button->type != EV_KEY) {
			dev_err(dev, "Only EV_KEY allowed for IRQ buttons.\n");
			return -EINVAL;
		}

		bdata->release_delay = button->debounce_interval;
		setup_timer(&bdata->release_timer,
			    gpio_keys_irq_timer, (unsigned long)bdata);

		isr = gpio_keys_irq_isr;
		irqflags = 0;
	}

	for (i = 0; i < rtk_cmd_keys_count; i++) 
		input_set_capability(input, EV_KEY, rtk_cmd_keys[i].keycode);

	/*
	 * Install custom action to cancel release timer and
	 * workqueue item.
	 */
	error = devm_add_action(&pdev->dev, gpio_keys_quiesce_key, bdata);
	if (error) {
		dev_err(&pdev->dev,
			"failed to register quiesce action, error: %d\n",
			error);
		return error;
	}

	/*
	 * If platform has specified that the button can be disabled,
	 * we don't want it to share the interrupt line.
	 */
	if (!button->can_disable)
		irqflags |= IRQF_SHARED;

	error = devm_request_any_context_irq(&pdev->dev, bdata->irq,
					     isr, irqflags, desc, bdata);
	if (error < 0) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			bdata->irq, error);
		return error;
	}

	return 0;
}

static void gpio_keys_report_state(struct gpio_keys_drvdata *ddata)
{
	struct input_dev *input = ddata->input;
	int i;

	for (i = 0; i < ddata->pdata->nbuttons; i++) {
		struct gpio_button_data *bdata = &ddata->data[i];
		if (gpio_is_valid(bdata->button->gpio))
			gpio_keys_gpio_report_event(bdata);
	}
	input_sync(input);
}

static int gpio_keys_open(struct input_dev *input)
{
	struct gpio_keys_drvdata *ddata = input_get_drvdata(input);
	const struct gpio_keys_platform_data *pdata = ddata->pdata;
	int error;

	if (pdata->enable) {
		error = pdata->enable(input->dev.parent);
		if (error)
			return error;
	}

	/* Report current state of buttons that are connected to GPIOs */
	//gpio_keys_report_state(ddata);

	return 0;
}

static void gpio_keys_close(struct input_dev *input)
{
	struct gpio_keys_drvdata *ddata = input_get_drvdata(input);
	const struct gpio_keys_platform_data *pdata = ddata->pdata;

	if (pdata->disable)
		pdata->disable(input->dev.parent);
}

/*
 * Handlers for alternative sources of platform_data
 */

#ifdef CONFIG_OF
/*
 * Translate OpenFirmware node properties into platform_data
 */
static struct gpio_keys_platform_data *
gpio_keys_get_devtree_pdata(struct device *dev)
{
	struct device_node *node, *pp;
	struct gpio_keys_platform_data *pdata;
	struct gpio_keys_button *button;
	int error;
	int nbuttons;
	int i;

	node = dev->of_node;
	if (!node)
		return ERR_PTR(-ENODEV);

	nbuttons = of_get_child_count(node);
	if (nbuttons == 0)
		return ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev,
			     sizeof(*pdata) + nbuttons * sizeof(*button),
			     GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	pdata->buttons = (struct gpio_keys_button *)(pdata + 1);
	pdata->nbuttons = nbuttons;

	pdata->rep = !!of_get_property(node, "autorepeat", NULL);

	i = 0;
	for_each_child_of_node(node, pp) {
		enum of_gpio_flags flags;

		button = &pdata->buttons[i++];

		button->gpio = of_get_gpio_flags(pp, 0, &flags);
		if (button->gpio < 0) {
			error = button->gpio;
			if (error != -ENOENT) {
				if (error != -EPROBE_DEFER)
					dev_err(dev,
						"Failed to get gpio flags, error: %d\n",
						error);
				return ERR_PTR(error);
			}
		} else {
			button->active_low = flags & OF_GPIO_ACTIVE_LOW;
		}

		button->irq = irq_of_parse_and_map(pp, 0);

		if (!gpio_is_valid(button->gpio) && !button->irq) {
			dev_err(dev, "Found button without gpios or irqs\n");
			return ERR_PTR(-EINVAL);
		}


		button->wakeup = !!of_get_property(pp, "gpio-key,wakeup", NULL);

		button->can_disable = !!of_get_property(pp, "linux,can-disable", NULL);

		if (of_property_read_u32(pp, "debounce-interval",
					 &button->debounce_interval))
			button->debounce_interval = 5;
	}

	if (pdata->nbuttons == 0)
		return ERR_PTR(-EINVAL);


	return pdata;
}

static const struct of_device_id gpio_cmds_of_match[] = {
	{ .compatible = "gpio-cmds", },
	{ },
};
MODULE_DEVICE_TABLE(of, gpio_cmds_of_match);

#else

static inline struct gpio_keys_platform_data *
gpio_keys_get_devtree_pdata(struct device *dev)
{
	return ERR_PTR(-ENODEV);
}

#endif

static int gpio_cmds_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct gpio_keys_platform_data *pdata = dev_get_platdata(dev);
	struct gpio_keys_drvdata *ddata;
	struct input_dev *input;
	size_t size;
	int i, error;
	int wakeup = 0;

	if (!pdata) {
		pdata = gpio_keys_get_devtree_pdata(dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}

	size = sizeof(struct gpio_keys_drvdata) +
			pdata->nbuttons * sizeof(struct gpio_button_data);
	ddata = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!ddata) {
		dev_err(dev, "failed to allocate state\n");
		return -ENOMEM;
	}

	input = devm_input_allocate_device(dev);
	if (!input) {
		dev_err(dev, "failed to allocate input device\n");
		return -ENOMEM;
	}

	ddata->pdata = pdata;
	ddata->input = input;
	mutex_init(&ddata->disable_lock);

	platform_set_drvdata(pdev, ddata);
	input_set_drvdata(input, ddata);

	input->name = pdata->name ? : pdev->name;
	input->phys = "gpio-cmds/input0";
	input->dev.parent = &pdev->dev;
	input->open = gpio_keys_open;
	input->close = gpio_keys_close;

	input->id.bustype = BUS_HOST;
	input->id.vendor = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	/* Enable auto repeat feature of Linux input subsystem */
	if (pdata->rep)
		__set_bit(EV_REP, input->evbit);

	for (i = 0; i < pdata->nbuttons; i++) {
		const struct gpio_keys_button *button = &pdata->buttons[i];
		struct gpio_button_data *bdata = &ddata->data[i];

		error = gpio_keys_setup_key(pdev, input, bdata, button);
		if (error)
			return error;

		if (button->wakeup)
			wakeup = 1;
	}

	error = sysfs_create_group(&pdev->dev.kobj, &gpio_cmds_attr_group);
        if (error) {
                dev_err(dev, "Unable to export cmds, error: %d\n",
                        error);
                return error;
        }


	error = input_register_device(input);
	if (error) {
		dev_err(dev, "Unable to register input device, error: %d\n",
			error);
		goto err_remove_group;
	}

	device_init_wakeup(&pdev->dev, wakeup);

	return 0;

err_remove_group:
	return error;
}

static int gpio_cmds_remove(struct platform_device *pdev)
{

	device_init_wakeup(&pdev->dev, 0);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int gpio_cmds_suspend(struct device *dev)
{
	struct gpio_keys_drvdata *ddata = dev_get_drvdata(dev);
	struct input_dev *input = ddata->input;
	int i;

	if (device_may_wakeup(dev)) {
		for (i = 0; i < ddata->pdata->nbuttons; i++) {
			struct gpio_button_data *bdata = &ddata->data[i];
			if (bdata->button->wakeup)
				enable_irq_wake(bdata->irq);
		}
	} else {
		mutex_lock(&input->mutex);
		if (input->users)
			gpio_keys_close(input);
		mutex_unlock(&input->mutex);
	}

	return 0;
}

static int gpio_cmds_resume(struct device *dev)
{
	struct gpio_keys_drvdata *ddata = dev_get_drvdata(dev);
	struct input_dev *input = ddata->input;
	int error = 0;
	int i;

	if (device_may_wakeup(dev)) {
		for (i = 0; i < ddata->pdata->nbuttons; i++) {
			struct gpio_button_data *bdata = &ddata->data[i];
			if (bdata->button->wakeup)
				disable_irq_wake(bdata->irq);
		}
	} else {
		mutex_lock(&input->mutex);
		if (input->users)
			error = gpio_keys_open(input);
		mutex_unlock(&input->mutex);
	}

	if (error)
		return error;

	//gpio_keys_report_state(ddata);
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(gpio_cmds_pm_ops, gpio_cmds_suspend, gpio_cmds_resume);

static struct platform_driver gpio_cmds_device_driver = {
	.probe		= gpio_cmds_probe,
	.remove		= gpio_cmds_remove,
	.driver		= {
		.name	= "gpio-cmds",
		.pm	= &gpio_cmds_pm_ops,
		.of_match_table = of_match_ptr(gpio_cmds_of_match),
	}
};

static int __init gpio_cmds_init(void)
{
	return platform_driver_register(&gpio_cmds_device_driver);
}

static void __exit gpio_cmds_exit(void)
{
	platform_driver_unregister(&gpio_cmds_device_driver);
}

late_initcall(gpio_cmds_init);
module_exit(gpio_cmds_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Command driver for GPIOs");
MODULE_ALIAS("platform:gpio-cmds");
