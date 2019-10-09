/**
 * snd-realtek-notify.c - Realtek alsa driver
 *
 * Copyright (C) 2017-2018 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <soc/realtek/kernel-rpc.h>
#include <sound/asound.h>
#include <rtk_rpc.h>
#include "snd-realtek.h"

extern struct ion_client *alsa_client;

static inline struct ion_client *__get_ion_client(void)
{
	return alsa_client;
}

enum {
	ENUM_DT_AI_EN = 0, /* this is used by acpu */
	ENUM_DT_AI_AIN, /* always set this bit if using AI */
	ENUM_DT_AI_ADC,
	ENUM_DT_AI_ANALOG_IN,
	ENUM_DT_AI_ADC_AMIC,
};

static const char *ai_names[] = {
	"", "",
	"adc", "analog-in", "adc-amic",
};

enum {
	ENUM_AI_I2S_STATUS = 0,
	ENUM_AI_I2S_PIN_SHARE_BIT, /* pin-share:1, pin-dependent:0 */
	ENUM_AI_I2S_AI_MASTER_BIT, /* AI-master:1, AI-slave:0 */
};

enum {
	ENUM_DT_AO_DAC    = 0,
	ENUM_DT_AO_I2S    = 1,
	ENUM_DT_AO_SPDIF  = 2,
	ENUM_DT_AO_HDMI   = 3,
	ENUM_DT_AO_GLOBAL = 4,
};

#define AN_MAX_DATA_SIZE 16

struct audio_notifier_data {
	AUDIO_ENUM_AIO_PRIVAETINFO info;
	u32 data[AN_MAX_DATA_SIZE];
	u32 size;
};

/* privateInfo for AI */
#define AN_AI_DEVICE_ON         0
#define AN_AI_DEVICE_I2S_CONF   1

/* privateInfo for AO */
#define AN_AO_SET_DEVICE_OFF            0
#define AN_AO_SET_I2S_CHANNEL           1
#define AN_AO_SET_I2S_MODE              2

/* selection of AN_AO_SET_I2S_CHANNEL */
enum {
	AN_AO_SET_I2S_2_CHANNEL       = 0,
	AN_AO_SET_I2S_8_CHANNEL       = 1,
};

/* selection of AN_AO_SET_I2S_MODE */
enum {
	AN_AO_SET_I2S_MODE_MASTER     = 0,
	AN_AO_SET_I2S_MODE_SLAVE      = 1,
};


static int __send_rpc(struct ion_client *client,
	AUDIO_ENUM_AIO_PRIVAETINFO info, unsigned int *data, int size)
{
	struct ion_handle *handle;
	ion_phys_addr_t phys;
	size_t len;
	AUDIO_RPC_AIO_PRIVATEINFO_PARAMETERS *arg;
	HRESULT RPC_ret;
	int off;
	int ret = -EINVAL;
	int i;

	if (!client)
		return -EINVAL;

	handle = ion_alloc(client, 4096, 1024,
		RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto exit;
	}

	ret = ion_phys(client, handle, &phys, &len);
	if (ret)
		goto exit;

	arg = ion_map_kernel(client, handle);
	memset(arg, 0, sizeof(*arg));

	arg->type = htonl(info);
	for (i = 0; i < size; i++)
		arg->argateInfo[i] = htonl(data[i]);
	off = get_rpc_alignment_offset(sizeof(*arg));

	if (send_rpc_command(RPC_AUDIO,
		ENUM_KERNEL_RPC_AIO_PRIVATEINFO,
		CONVERT_FOR_AVCPU(phys),
		CONVERT_FOR_AVCPU(phys + off),
		&RPC_ret)) {
		ret = -EINVAL;
		goto exit;
	}

	ret = RPC_ret != S_OK ? -EINVAL : 0;

exit:
	if (handle) {
		ion_unmap_kernel(client, handle);
		ion_free(client, handle);
	}
	return ret;
}

static bool audio_notifier_data_is_empty(struct audio_notifier_data *andata)
{
	int i;

	for (i = 0; i < andata->size; i++)
		if (andata->data[i] != 0)
			return false;
	return true;
}


static int audio_notifier_notify(struct device *dev, struct audio_notifier_data *andata)
{
	int ret;
	struct ion_client *client = __get_ion_client();

	if (andata->size > AN_MAX_DATA_SIZE)
		return -E2BIG;

	if (audio_notifier_data_is_empty(andata)) {
		dev_dbg(dev, "no data to send\n");
		return 0;
	}

	ret = __send_rpc(client, andata->info, andata->data, andata->size);
	if (ret) {
		dev_err(dev, "failed to notify ACPU: %d\n", ret);
		return ret;
	}

	return 0;
}

/* second compatible of ai devices */
static const struct of_device_id rtk_ai_matches[] = {
	{.compatible = "alc5279",   .data = (void *)ENUM_DT_AI_ADC},
	{.compatible = "wm8782",    .data = (void *)ENUM_DT_AI_ADC},
	{.compatible = "adc",       .data = (void *)ENUM_DT_AI_ADC},
	{.compatible = "analog-in", .data = (void *)ENUM_DT_AI_ANALOG_IN},
	{.compatible = "adc-amic",  .data = (void *)ENUM_DT_AI_ADC_AMIC},
	{}
};

static int rtk_audio_notifier_ai_init(struct device *dev)
{
	struct device_node *np = dev->of_node;
	unsigned int val;
	const struct of_device_id *match;
	struct audio_notifier_data *andata;

	andata = devm_kzalloc(dev, sizeof(*andata), GFP_KERNEL);
	if (!andata)
		return -ENOMEM;

	andata->info = ENUM_PRIVATEINFO_AIO_AI_INTERFACE_SWITCH_CONTROL;
	andata->data[AN_AI_DEVICE_ON] = BIT(ENUM_DT_AI_AIN);
	andata->size = 2;

	match = of_match_node(rtk_ai_matches, np);
	if (!match)
		return -EINVAL;
	val = (unsigned long)(match->data);

	dev_info(dev, "device_type=%s(%d)\n", ai_names[val], val);
	andata->data[AN_AI_DEVICE_ON] |= BIT(val);

	if (of_property_match_string(np, "ai,type", "i2s") >= 0) {
		u32 conf = BIT(ENUM_AI_I2S_STATUS);

		if (of_find_property(np, "ai,i2s-pin-shared", NULL))
			conf |=	BIT(ENUM_AI_I2S_PIN_SHARE_BIT);
		if (of_find_property(np, "ai,i2s-master", NULL))
			conf |=	BIT(ENUM_AI_I2S_AI_MASTER_BIT);

		dev_info(dev, "i2s mode=%s, pin=%s\n",
			(conf & BIT(ENUM_AI_I2S_AI_MASTER_BIT)) ? "master" : "slave",
			(conf & BIT(ENUM_AI_I2S_PIN_SHARE_BIT)) ? "shared" : "independent");
		andata->data[AN_AI_DEVICE_I2S_CONF] = conf;
	}

	return audio_notifier_notify(dev, andata);
}

/* compatible of ao sub nodes */
static const struct of_device_id rtk_ao_matches[] = {
	{.compatible = "dac",    .data = (void *)ENUM_DT_AO_DAC},
	{.compatible = "i2s",    .data = (void *)ENUM_DT_AO_I2S},
	{.compatible = "spdif",  .data = (void *)ENUM_DT_AO_SPDIF},
	{.compatible = "hdmi",   .data = (void *)ENUM_DT_AO_HDMI},
	{.compatible = "global", .data = (void *)ENUM_DT_AO_GLOBAL},
	{}
};

static int rtk_audio_notifier_ao_init(struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct device_node *child;
	unsigned int mask = BIT(ENUM_DT_AO_DAC) |
		BIT(ENUM_DT_AO_SPDIF) |
		BIT(ENUM_DT_AO_I2S) |
		BIT(ENUM_DT_AO_HDMI) |
		BIT(ENUM_DT_AO_GLOBAL);
	struct audio_notifier_data *andata;

	andata = devm_kzalloc(dev, sizeof(*andata), GFP_KERNEL);
	if (!andata)
		return -ENOMEM;

	andata->info = ENUM_PRIVATEINFO_AIO_AO_INTERFACE_SWITCH_CONTROL;
	andata->size = 3;

	for_each_child_of_node(np, child) {
		const struct of_device_id *match;
		u32 val;

		match = of_match_node(rtk_ao_matches, child);
		if (!match)
			continue;

		if (!of_device_is_available(child))
			continue;

		/* parse config for ao-i2s */
		if (!strcmp(match->compatible, "i2s")) {
			int val = 0;
			int ch = AN_AO_SET_I2S_2_CHANNEL;
			int mo = AN_AO_SET_I2S_MODE_MASTER;

			/* i2s channgel */
			if (of_property_read_u32(child, "channel", &val))
				val = 0;
			if (val == 8)
				ch = AN_AO_SET_I2S_8_CHANNEL;

			/* i2s mode */
			if (of_find_property(child, "slave-mode", NULL))
				mo = AN_AO_SET_I2S_MODE_SLAVE;

			dev_info(dev, "i2s: mode=%s, channel=%d\n",
				mo ? "slave" : "master", ch ? 8 : 2);
			andata->data[AN_AO_SET_I2S_CHANNEL] = ch;
			andata->data[AN_AO_SET_I2S_MODE]    = mo;
		}

		val = (u64)(uintptr_t)(match->data);
		mask &= ~BIT(val);
		dev_dbg(dev, "update mask to 0x%08x from dt node %s\n", mask,
			child->name);
	}

	andata->data[AN_AO_SET_DEVICE_OFF] = mask;
	if (mask & BIT(ENUM_DT_AO_DAC))
		dev_info(dev, "disabling adc\n");
	if (mask & BIT(ENUM_DT_AO_SPDIF))
		dev_info(dev, "disabling spdif\n");
	if (mask & BIT(ENUM_DT_AO_I2S))
		dev_info(dev, "disabling i2s\n");
	if (mask & BIT(ENUM_DT_AO_HDMI))
		dev_info(dev, "disabling hdmi\n");
	if (mask & BIT(ENUM_DT_AO_GLOBAL))
		dev_info(dev, "disabling global\n");
	return audio_notifier_notify(dev, andata);
}

static const struct of_device_id rtk_audio_dev_ids[] = {
	{
		.compatible = "realtek,audio-in",
		.data = rtk_audio_notifier_ai_init,
	},
	{
		.compatible = "realtek,audio-out",
		.data = rtk_audio_notifier_ao_init,
	},
	{}
};

static void rtk_audio_notifier_of_get_gpios(struct device *dev)
{
	struct device_node *np = dev->of_node;
	int num;
	int i;

	num = of_gpio_count(np);
	for (i = 0; i < num; i++) {
		int gpio = of_get_gpio(np, i);

		if (gpio < 0) {
			dev_err(dev, "failed to get gpio[%d]\n", i);
			continue;
		}

		if (!gpio_is_valid(gpio)) {
			dev_err(dev, "invalid gpio num %d\n", gpio);
			continue;
		}

		if (gpio_request(gpio, dev_name(dev))) {
			dev_err(dev, "failed to request gpio %d\n", gpio);
			continue;
		}

		dev_info(dev, "request gpio%d\n", gpio);
	}
}

static int rtk_audio_notifier_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *match;
	int (*init_func)(struct device *dev);

	dev_info(&pdev->dev, "%s\n", __func__);

	match = of_match_node(rtk_audio_dev_ids, dev->of_node);
	if (!match)
		return -EFAULT;

	rtk_audio_notifier_of_get_gpios(dev);

	init_func = match->data;
	return init_func ? init_func(dev) : -EINVAL;
}

static struct platform_driver rtk_audio_notifier_drv = {
	.driver = {
		.name   = "audio-notifier",
		.of_match_table = rtk_audio_dev_ids,
	},
	.probe = rtk_audio_notifier_probe,
};

static int __init rtk_audio_notifier_init(void)
{
	return platform_driver_register(&rtk_audio_notifier_drv);
}
late_initcall(rtk_audio_notifier_init);
