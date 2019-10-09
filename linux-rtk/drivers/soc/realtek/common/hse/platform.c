#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include "hse.h"

static const struct hse_engine_group groups[] = {
	{ 0x3, "SWC" },
	{ 0xc, "NWC" },
};

static struct hse_desc desc = {
	.num_groups = ARRAY_SIZE(groups),
	.groups = groups,
};

static int hse_hw_init(struct hse_device *hdev)
{
	hse_write(hdev, HSE_REG_BYPASS, 1);
	return 0;
}

static int hse_runtime_suspend(struct device *dev)
{
	struct hse_device *hdev = dev_get_drvdata(dev);
	int i;

	dev_dbg(dev, "%s\n", __func__);
	for (i = 0; i < HSE_MAX_ENGINES; i++)
		hse_engine_suspend(hdev->engs[i]);
	clk_disable_unprepare(hdev->clk);

	return 0;
}

static int hse_runtime_resume(struct device *dev)
{
	struct hse_device *hdev = dev_get_drvdata(dev);
	int i;

	dev_dbg(dev, "%s\n", __func__);
	clk_prepare_enable(hdev->clk);
	for (i = 0; i < HSE_MAX_ENGINES; i++)
		hse_engine_resume(hdev->engs[i]);

	return 0;
}

static const struct dev_pm_ops hse_pm_ops = {
	.runtime_suspend = hse_runtime_suspend,
	.runtime_resume  = hse_runtime_resume,
};

static irqreturn_t hse_interrupt(int irq, void *dev_id)
{
	struct hse_device *hdev = dev_id;
	int i;
	int mask = 0;

	for (i = 0; i < HSE_MAX_IRQS; i++)
		if (irq == hdev->irqs[i]) {
			mask = hdev->desc->groups[i].engine_mask;
			break;
		}
	BUG_ON(mask == 0);

	for (i = 0 ; i < HSE_MAX_ENGINES; i++) {
		if (!hdev->engs[i])
			continue;
		if (!(BIT(i) & mask))
			continue;
		dev_dbg(hdev->dev, "irq:%d fire to engine%d\n", irq, i);
		hse_engine_check_ints(hdev->engs[i]);
	}
	return IRQ_HANDLED;
}

static int of_parse_engine_mask(struct device_node *np, int *mask)
{
	*mask = 0;
	if (of_find_property(np, "engine-0-enabled", NULL))
		*mask |= 0x1;
	if (of_find_property(np, "engine-1-enabled", NULL))
		*mask |= 0x2;
	if (of_find_property(np, "engine-2-enabled", NULL))
		*mask |= 0x4;
	if (of_find_property(np, "engine-3-enabled", NULL))
		*mask |= 0x8;

	return *mask == 0 ? -EINVAL : 0;
}

static int hse_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct hse_device *hdev;
	struct resource res;
	int ret;
	int i;
	int requested_irq_num = 0;

	dev_info(dev, "%s\n", __func__);

	hdev = devm_kzalloc(dev, sizeof(*hdev), GFP_KERNEL);
	if (!hdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, hdev);
	hdev->dev = dev;
	hdev->desc = &desc;

	ret = of_address_to_resource(np, 0, &res);
	if (ret) {
		dev_err(dev, "of_address_to_resource() returns %d\n", ret);
		return -ENODEV;
	}

	hdev->base = devm_ioremap(dev, res.start, resource_size(&res));
	if (!hdev->base)
		return -ENOMEM;

	hdev->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(hdev->clk)) {
		ret = PTR_ERR(hdev->clk);
		dev_err(dev, "clk_get() returns %d\n", ret);
		return ret;
	}

	hdev->rstc = devm_reset_control_get(dev, NULL);
	if (IS_ERR(hdev->rstc)) {
		ret = PTR_ERR(hdev->rstc);
		dev_err(dev, "reset_control_get() returns %d\n", ret);
		return ret;
	}

	ret = of_parse_engine_mask(np, &hdev->engine_mask);
	if (ret) {
		dev_err(dev, "no engine enabled\n");
		return -ENODEV;
	}
	dev_dbg(dev, "engine_mask=%x\n", hdev->engine_mask);

	for (i = 0; i < desc.num_groups; i++) {
		const struct hse_engine_group *group = &desc.groups[i];
		int irq;

		if (!(group->engine_mask & hdev->engine_mask))
			continue;

		irq = platform_get_irq_byname(pdev, group->irq_name);
		if (irq < 0) {
			dev_err(dev, "group%d: platform_get_irq_byname() of '%s' returns %d\n",
				i, group->irq_name, ret);
			return ret;
		}

		ret = devm_request_irq(dev, irq, hse_interrupt,	IRQF_SHARED,
			dev_name(dev), hdev);
		if (ret) {
			dev_err(dev, "group%d: request_irq() returns %d\n",
				i, ret);
			return ret;
		}

		dev_dbg(dev, "group%d: irq=%d\n", i, irq);
		hdev->irqs[i] = irq;
		requested_irq_num ++;
	}

	if (!requested_irq_num) {
		dev_err(dev, "requested_irq_num is 0\n");
		return -EINVAL;
	}

	hdev->mdev.minor  = MISC_DYNAMIC_MINOR;
	hdev->mdev.name   = "hse";
	hdev->mdev.fops   = &hse_fops;
	hdev->mdev.parent = NULL;
	ret = misc_register(&hdev->mdev);
	if (ret) {
		dev_err(dev, "misc_register() returns %d\n", ret);
		return ret;
	}

	reset_control_deassert(hdev->rstc);

	pm_runtime_set_suspended(dev);
	pm_runtime_enable(dev);

	pm_runtime_get_sync(dev);
	hse_hw_init(hdev);
	for (i = 0; i < HSE_MAX_ENGINES; i++) {
		if (!(hdev->engine_mask & BIT(i)))
			continue;

		ret = hse_engine_init(hdev, i);
		WARN(ret, "engine%d: hse_engine_init() returns %d\n",
			i, ret);
	}
	pm_runtime_put_sync(dev);

	hse_self_test(hdev);
	return 0;
}

static int hse_remove(struct platform_device *pdev)
{
	struct hse_device *hdev = platform_get_drvdata(pdev);

	pm_runtime_disable(hdev->dev);
	reset_control_assert(hdev->rstc);
	return 0;
}

static const struct of_device_id hse_ids[] = {
	{ .compatible = "realtek,highspeed-streaming-engine" },
	{}
};

static struct platform_driver hse_driver = {
	.probe  = hse_probe,
	.remove = hse_remove,
	.driver = {
		.name           = "rtk-hse",
		.owner          = THIS_MODULE,
		.of_match_table = hse_ids,
		.pm             = &hse_pm_ops,
	},
};
module_platform_driver(hse_driver);

