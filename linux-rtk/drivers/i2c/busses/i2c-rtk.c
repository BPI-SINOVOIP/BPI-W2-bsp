/*
 * Realtek I2C driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/completion.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <linux/pinctrl/consumer.h>
#include <linux/clkdev.h>
#include <linux/clk-provider.h>
#include <linux/clk.h>
#include <linux/reset.h>

#include "i2c-rtk-priv.h"

#include <linux/pinctrl/consumer.h>


#define RTK_MASTER_7BIT_ADDR  0x24
#define IsReadMsg(x) (x.flags & I2C_M_RD)
#define IsSameTarget(x, y) \
((x.addr == y.addr) && !((x.flags ^ y.flags) & (~I2C_M_RD)))

struct rtk_i2c_dev {
	struct device *dev;
	struct i2c_adapter adapter;
	struct clk *div_clk;
	void __iomem *base;
	unsigned int id;
	bool is_suspended;
	u32 bus_clk_rate;
	int cont_id;
	int irq;
	int is_dvc;
	struct rtk_i2c_reg_map reg_map;
	struct rtk_i2c_handler *handler;
};

void i2c_rtk_dump_msg(const struct i2c_msg *p_msg)
{
	RTK_DEBUG("%s\n", __func__);
	pr_info("msg->addr  = %02x\n", p_msg->addr);
	pr_info("msg->flags = %04x\n", p_msg->flags);
	pr_info("msg->len   = %d\n", p_msg->len);
	pr_info("msg->buf   = %p\n", p_msg->buf);
}

static u32 rtk_i2c_func(struct i2c_adapter *adap)
{
	u32 ret = I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		I2C_FUNC_10BIT_ADDR | I2C_FUNC_PROTOCOL_MANGLING;

	return ret;
}

static int  i2c_rtk_xfer(struct i2c_adapter *adap,
	struct i2c_msg msgs[], int num)
{
	struct rtk_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	struct rtk_i2c_handler *handler = i2c_dev->handler;
	int i = 0;
	int ret = 0;
	struct pinctrl *pctrl;
	struct pinctrl_state *pctrl_state;

	RTK_DEBUG("%s\n", __func__);

#ifdef CONFIG_ARCH_RTD16xx
	if (handler->id == 0) {
		pctrl = devm_pinctrl_get(i2c_dev->dev);
		pctrl_state = pinctrl_lookup_state(pctrl, "default");
		pinctrl_select_state(pctrl, pctrl_state);
	}
#endif

#ifdef EDID_4BLOCK_SUPPORT
	if (handler->id == 1 && num == 3) {
		if (msgs[0].addr == 0x30 && msgs[1].addr == 0x50) {
			ret = handler->read_edid_seg(handler, msgs[0].buf[0],
				msgs[1].buf[0], msgs[2].buf, msgs[2].len);

			if (ret < 0)
				goto err_occur;
			else
				return 3;
		}
	}
#endif

	for (i = 0; i < num; i++) {
		ret = handler->set_tar(handler, msgs[i].addr, ADDR_MODE_7BITS);
		if (ret < 0)
			goto err_occur;

		switch (msgs[i].flags & I2C_M_SPEED_MASK) {
		case I2C_M_FAST_SPEED:
			handler->set_spd(handler, 400);
			break;
		case I2C_M_HIGH_SPEED:
#ifdef CONFIG_ARCH_RTD16xx
			if (handler->id == 0) {
				pctrl_state = pinctrl_lookup_state(pctrl, "high_speed");
				pinctrl_select_state(pctrl, pctrl_state);
				handler->set_spd(handler, 3400);
			}
#else
			handler->set_spd(handler, 800);
#endif
			break;
		case I2C_M_LOW_SPEED:
			handler->set_spd(handler, 50);
			break;
		case I2C_M_LOW_SPEED_80:
			handler->set_spd(handler, 80);
			break;
		case I2C_M_LOW_SPEED_66:
			handler->set_spd(handler, 66);
			break;
		case I2C_M_LOW_SPEED_33:
			handler->set_spd(handler, 33);
			break;
		case I2C_M_LOW_SPEED_10:
			handler->set_spd(handler, 10);
			break;
		default:
		case I2C_M_NORMAL_SPEED:
			handler->set_spd(handler, 100);
			break;
		}

		handler->set_guard_interval(handler,
			(msgs[i].flags & I2C_M_NO_GUARD_TIME) ? 0 : 1000);

		if (IsReadMsg(msgs[i])) {
			ret = handler->read(handler, NULL, 0, msgs[i].buf,
				msgs[i].len);
		} else {
			if ((i < (num-1)) && IsReadMsg(msgs[i+1]) &&
				IsSameTarget(msgs[i], msgs[i+1])) {
				/* Random Read = Write + Read (same addr) */
				ret = handler->read(handler,
					msgs[i].buf, msgs[i].len,
					msgs[i+1].buf, msgs[i+1].len);
				i++;
			} else {
				/* Single Write */
				ret = handler->write(handler,
					msgs[i].buf, msgs[i].len,
					(i == (num-1)) ? WAIT_STOP : NON_STOP);
			}
		}

		if (ret < 0)
			goto err_occur;
	}

	return i;

err_occur:

	switch (ret) {
	case -ECMDSPLIT:
		pr_info("[I2C%d] Xfer fail - MSG SPLIT (%d/%d)\n",
			handler->id, i, num);
		break;
	case -ETXABORT:
		pr_info("[I2C%d] Xfer fail - TXABORT (%d/%d), Reason=%04x\n",
			handler->id, i, num,
			handler->get_tx_abort_reason(handler));
		break;
	case -ETIMEOUT:
		pr_info("[I2C%d] Xfer fail - TIMEOUT (%d/%d)\n",
			handler->id, i, num);
		break;
	case -EILLEGALMSG:
		pr_info("[I2C%d] Xfer fail - ILLEGAL MSG (%d/%d)\n",
			handler->id, i, num);
		break;
	case -EADDROVERRANGE:
		pr_info("[I2C%d] Xfer fail - ADDRESS OUT OF RANGE (%d/%d)\n",
			handler->id, i, num);
		break;
	default:
		pr_info("[I2C%d] Xfer fail - Unkonwn Return Value (%d/%d)\n",
			handler->id, i, num);
		break;
	}

	i2c_rtk_dump_msg(&msgs[i]);

	ret = -EACCES;
	return ret;
}

static const struct i2c_algorithm rtk_i2c_algo = {
	.master_xfer = i2c_rtk_xfer,
	.functionality = rtk_i2c_func,
};

static int  rtk_i2c_init(struct rtk_i2c_dev *i2c_dev)
{
	i2c_dev->handler = create_rtk_i2c_handle(
		i2c_dev->id, RTK_MASTER_7BIT_ADDR,
		ADDR_MODE_7BITS, SPD_MODE_SS, i2c_dev->irq,
		(unsigned long)i2c_dev->base);

	if (i2c_dev->handler == NULL)
		pr_info("[I2C%d] handler is NULL, FAIL!!!!\n", i2c_dev->id);

	return i2c_dev->handler->init(i2c_dev->handler);
}

/* Match table for of_platform binding */
static const struct of_device_id rtk_i2c_of_match[] = {
	{ .compatible = "realtek,rtk-i2c", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_i2c_of_match);

static int rtk_i2c_probe(struct platform_device *pdev)
{
	struct rtk_i2c_dev *i2c_dev;
	struct clk *div_clk = NULL;
	void __iomem *base;
	int irq;
	u32 i2c_id;
	int ret = 0;

	base = of_iomap(pdev->dev.of_node, 0);
	if (!base) {
		pr_err("i2c no mmio space\n");
		return -EINVAL;
	}

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq < 0) {
		pr_err("i2c no irq\n");
		return -EINVAL;
	}

	if (of_property_read_u32(pdev->dev.of_node, "i2c-num", &i2c_id)) {
		pr_err("Get I2C ID fail\n");
		return -EINVAL;
	}

	div_clk = of_clk_get(pdev->dev.of_node, 0);
	if (IS_ERR_OR_NULL(div_clk)) {
		pr_warn("Failed to get clk from DT: %ld\n", PTR_ERR(div_clk));
		div_clk = NULL;
	}
	clk_prepare_enable(div_clk);
	ret = device_reset(&pdev->dev);
	if (ret)
		pr_warn("Failed to device reset: %d\n", ret);

	i2c_dev = devm_kzalloc(&pdev->dev, sizeof(*i2c_dev), GFP_KERNEL);
	i2c_dev->base = base;
	i2c_dev->div_clk = div_clk;
	i2c_dev->adapter.algo = &rtk_i2c_algo;
	i2c_dev->irq = irq;
	i2c_dev->cont_id = pdev->id;
	i2c_dev->id = i2c_id;
	i2c_dev->dev = &pdev->dev;

	ret = of_property_read_u32(i2c_dev->dev->of_node, "clock-frequency",
		&i2c_dev->bus_clk_rate);
	if (ret)
		i2c_dev->bus_clk_rate = 100000; /* default clock rate */

	if (pdev->dev.of_node) {
		const struct of_device_id *match;

		match = of_match_device(rtk_i2c_of_match, &pdev->dev);
	}

	platform_set_drvdata(pdev, i2c_dev);

	ret = rtk_i2c_init(i2c_dev);

	if (ret) {
		dev_err(&pdev->dev, "Failed to initialize i2c controller");
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, i2c_dev->irq, rtk_i2c_isr,
		IRQF_SHARED, dev_name(&pdev->dev),
		(void *)i2c_dev->handler);

	i2c_set_adapdata(&i2c_dev->adapter, i2c_dev);
	i2c_dev->adapter.owner = THIS_MODULE;
	i2c_dev->adapter.class = I2C_CLASS_HWMON;
	strlcpy(i2c_dev->adapter.name, "Realtek I2C adapter",
		sizeof(i2c_dev->adapter.name));
	i2c_dev->adapter.dev.parent = &pdev->dev;
	i2c_dev->adapter.nr = pdev->id;
	i2c_dev->adapter.dev.of_node = pdev->dev.of_node;

	ret = i2c_add_numbered_adapter(&i2c_dev->adapter);

	if (ret) {
		dev_err(&pdev->dev, "Failed to add I2C adapter\n");
		return ret;
	}
	return 0;
}

static int rtk_i2c_remove(struct platform_device *pdev)
{
	struct rtk_i2c_dev *i2c_dev = platform_get_drvdata(pdev);

	i2c_del_adapter(&i2c_dev->adapter);
	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int rtk_i2c_suspend(struct device *dev)
{
	struct rtk_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	pr_info("[I2C] Enter %s\n", __func__);

	i2c_lock_adapter(&i2c_dev->adapter);
	i2c_dev->is_suspended = true;
	clk_disable_unprepare(i2c_dev->div_clk);
	i2c_unlock_adapter(&i2c_dev->adapter);

	pr_info("[I2C] Exit %s\n", __func__);
	return 0;
}

static int rtk_i2c_resume(struct device *dev)
{
	struct rtk_i2c_dev *i2c_dev = dev_get_drvdata(dev);
	int ret;

	pr_info("[I2C] Enter %s\n", __func__);

	i2c_lock_adapter(&i2c_dev->adapter);

	clk_prepare_enable(i2c_dev->div_clk);

	ret = rtk_i2c_init(i2c_dev);

	if (ret) {
		i2c_unlock_adapter(&i2c_dev->adapter);
		return ret;
	}

	i2c_dev->is_suspended = false;

	i2c_unlock_adapter(&i2c_dev->adapter);

	pr_info("[I2C] Exit %s\n", __func__);
	return 0;
}

static const struct dev_pm_ops rtk_i2c_pm_ops = {
	.suspend_noirq = rtk_i2c_suspend,
	.resume_noirq = rtk_i2c_resume,
};

#define RTK_I2C_PM_OPS (&rtk_i2c_pm_ops)
#else
#define RTK_I2C_PM_OPS NULL
#endif /* CONFIG_PM_SLEEP */

static struct platform_driver rtk_i2c_driver = {
	.probe = rtk_i2c_probe,
	.remove = rtk_i2c_remove,
	.driver = {
		.name = "rtk_i2c",
		.owner = THIS_MODULE,
		.pm = RTK_I2C_PM_OPS,
		.of_match_table = of_match_ptr(rtk_i2c_of_match),
	},
};

/* I2C may be needed to bring up other drivers */
static int __init rtk_i2c_init_driver(void)
{
	return platform_driver_register(&rtk_i2c_driver);
}
//subsys_initcall(rtk_i2c_init_driver);
rootfs_initcall(rtk_i2c_init_driver);

static void __exit rtk_i2c_exit_driver(void)
{
	platform_driver_unregister(&rtk_i2c_driver);
}
module_exit(rtk_i2c_exit_driver);

MODULE_AUTHOR("James Tai <james.tai@realtek.com>");
MODULE_DESCRIPTION("Realtek I2C bus adapter");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk_i2c");
