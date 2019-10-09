/*
 * Pheonix SCPU wrapper SRAM control
 *
 * Copyright (C) 2018 Realtek Semiconductor Corporation
 * Copyright (C) 2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/cpufreq.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>

#define SRAM_RME      0x480
#define SRAM_RM       0x484
#define L2_SRAM_RME   0x48c
#define L2_SRAM_RM    0x490

struct scpu_sramctl_data {
	struct device *dev;
	void *base;
	struct notifier_block volt_trans_nb;
	struct notifier_block freq_trans_nb;
	int cpu;
	int new_freq;
	int old_volt;
};

static void scpu_sramctl_rm_init(struct scpu_sramctl_data *sscd)
{
	dev_dbg(sscd->dev, "%s\n", __func__);
	writel(0x01111111, sscd->base + SRAM_RM);
	writel(0x00000011, sscd->base + L2_SRAM_RM);
}

static void scpu_sramctl_rm_enable(struct scpu_sramctl_data *sscd)
{
	dev_dbg(sscd->dev, "%s\n", __func__);
	writel(0x0000007f, sscd->base + SRAM_RME);
	writel(0x00000003, sscd->base + L2_SRAM_RME);
}

static void scpu_sramctl_rm_diable(struct scpu_sramctl_data *sscd)
{
	dev_dbg(sscd->dev, "%s\n", __func__);
	writel(0x00000000, sscd->base + SRAM_RME);
	writel(0x00000000, sscd->base + L2_SRAM_RME);
}

/*
 *  using cpufreq/regulator to record freq/volt change
 *
 *  event order:
 *    CPUFREQ_PRECHANGE
 *    REGULATOR_EVENT_PRE_VOLTAGE_CHANGE
 *    CPUFREQ_POSTCHANGE
 */

static int scpu_sramctl_freq_notifier(struct notifier_block *nb,
	unsigned long action, void *data)
{
	struct scpu_sramctl_data *sscd = container_of(nb,
		struct scpu_sramctl_data, freq_trans_nb);
	struct cpufreq_freqs *freqs = data;
	int new_freq;
	int old_volt;

	switch (action) {
	case CPUFREQ_PRECHANGE:
		sscd->new_freq = freqs->new;

		/* save the cpu id, to prevent multiple postchange */
		sscd->cpu = freqs->cpu;
		break;

	case CPUFREQ_POSTCHANGE:
		if (freqs->cpu != sscd->cpu)
			return NOTIFY_DONE;

		new_freq = freqs->new;
		old_volt = sscd->old_volt;

		/* clear saved voltage */
		sscd->old_volt = 0;

		dev_dbg(sscd->dev, "%s: cpu%d: new_freq=%d, old_volt=%d\n",
			__func__, freqs->cpu, new_freq, old_volt);
		if (new_freq > 450000 && old_volt == 900000)
			scpu_sramctl_rm_diable(sscd);
		break;

	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}

static int scpu_sramctl_volt_notifier(struct notifier_block *nb,
	unsigned long action, void *data)
{
	struct scpu_sramctl_data *sscd = container_of(nb,
		struct scpu_sramctl_data, volt_trans_nb);
	struct pre_voltage_change_data *vdata = data;
	int new_freq;
	int new_volt;

	if (action != REGULATOR_EVENT_PRE_VOLTAGE_CHANGE)
		return NOTIFY_DONE;

	sscd->old_volt = vdata->old_uV;

	new_freq = sscd->new_freq;
	new_volt = vdata->min_uV;
	dev_dbg(sscd->dev, "%s: new_freq=%d, new_volt=%d\n",
		__func__, new_freq, new_volt);
	if (new_freq < 450000 && new_volt == 900000)
		scpu_sramctl_rm_enable(sscd);

	return NOTIFY_OK;
}

static struct scpu_sramctl_data *sscdp;

int scpu_sramctl_init(struct device *dev)
{
	struct scpu_sramctl_data *sscd;
	struct regulator *supply;
	int ret;

	BUG_ON(sscdp != NULL);
	sscd = kzalloc(sizeof(*sscd), GFP_KERNEL);
	if (!sscd)
		return -ENOMEM;

	sscd->dev = dev;
	sscd->volt_trans_nb.notifier_call = scpu_sramctl_volt_notifier;
	sscd->freq_trans_nb.notifier_call = scpu_sramctl_freq_notifier;
	sscd->base = of_iomap(dev->of_node, 0);
	if (!sscd->base) {
		ret = -ENOMEM;
		goto free_sscd;
	}

	supply = regulator_get_optional(dev, "cpu");
	if (IS_ERR(supply)) {
		ret = PTR_ERR(supply);
		goto unmap;
	}
	regulator_register_notifier(supply, &sscd->volt_trans_nb);
	regulator_put(supply);

	cpufreq_register_notifier(&sscd->freq_trans_nb,
		CPUFREQ_TRANSITION_NOTIFIER);

	sscdp = sscd;
	scpu_sramctl_rm_init(sscd);
	return 0;
unmap:
	iounmap(sscd->base);
free_sscd:
	kfree(sscd);

	return ret;
}

int scpu_sramctl_fini(struct device *dev)
{
	struct scpu_sramctl_data *sscd = sscdp;
	struct regulator *supply;

	if (!sscd)
		return -EINVAL;
	cpufreq_unregister_notifier(&sscd->freq_trans_nb,
		CPUFREQ_TRANSITION_NOTIFIER);
	supply = regulator_get_optional(dev, "cpu");
	regulator_unregister_notifier(supply, &sscd->volt_trans_nb);
	regulator_put(supply);
	iounmap(sscd->base);
	kfree(sscd);
	sscdp = NULL;
	return 0;
}

static int scpu_sramctl_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s\n", __func__);
	return scpu_sramctl_init(&pdev->dev);
}

static struct of_device_id scpu_sramctl_ids[] = {
	{ .compatible = "realtek,scpu-sramctl" },
	{}
};

static struct platform_driver scpu_sramctl_driver = {
	.probe  = scpu_sramctl_probe,
	.driver = {
		.name   = "rtd119x-scpu-sramctl",
		.of_match_table = scpu_sramctl_ids,
	},
};
module_platform_driver(scpu_sramctl_driver);

