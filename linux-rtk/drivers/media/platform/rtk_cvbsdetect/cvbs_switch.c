/*
 * cvbs_switch.c - RTK cvbs switch driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include "cvbs_switch.h"

int cvbs_rpc(unsigned int detected)
{
	struct VIDEO_RPC_PRIVATEINFO_PARAMETERS *rpc = NULL;
	struct ion_handle *handle = NULL;
	unsigned int RPC_ret;
	ion_phys_addr_t dat;
	size_t len;
	int ret = -1;
	unsigned long offset;

	handle = ion_alloc(cvbs_rpc_ion_client, 4096, 1024,
			RTK_PHOENIX_ION_HEAP_AUDIO_MASK,
			ION_FLAG_NONCACHED | ION_FLAG_SCPUACC
			| ION_FLAG_ACPUACC);
	if (IS_ERR(handle)) {
		cvbs_error("%s ion_alloc fail\n", __func__);
		goto exit;
	}
	if (ion_phys(cvbs_rpc_ion_client, handle, &dat, &len) != 0) {
		cvbs_error(KERN_ERR "%s ion_phys fail\n", __func__);
		goto exit;
	}
	rpc = ion_map_kernel(cvbs_rpc_ion_client, handle);

	offset = get_rpc_alignment_offset(
			sizeof(struct VIDEO_RPC_PRIVATEINFO_PARAMETERS));
	memset(rpc, 0, sizeof(struct VIDEO_RPC_PRIVATEINFO_PARAMETERS));

	rpc->type = htonl(ENUM_PRIVATEINFO_VIDEO_CVBS_POWER_OFF);
	rpc->privateInfo[0] = htonl(detected);

	if (send_rpc_command(RPC_AUDIO,
		ENUM_VIDEO_KERNEL_RPC_VOUT_VDAC_SET,
		CONVERT_FOR_AVCPU(dat),
		CONVERT_FOR_AVCPU(dat + offset),
		&RPC_ret)) {
		cvbs_error("[%s %d RPC fail]\n", __func__, __LINE__);
		goto exit;
	}
	ret = 0;

exit:
	if (handle != NULL) {
		ion_unmap_kernel(cvbs_rpc_ion_client, handle);
		ion_free(cvbs_rpc_ion_client, handle);
	}
	return ret;
}

ssize_t cvbs_switch_print_state(struct switch_dev *sdev, char *buf)
{
	cvbs_debug("cvbs_switch_print_state");
	return sprintf(buf, "%d", cvbs_det.state);
}

static void cvbs_switch_work_func(struct work_struct *work)
{
	int ret = 0;

	if (gpio_activity)
		cvbs_det.state = gpio_get_value(cvbs_det.gpio);
	else
		cvbs_det.state = !gpio_get_value(cvbs_det.gpio);

	if (cvbs_det.state == 0) { /*cvbs off*/
		switch_set_state(&cvbs_det.sdev, cvbs_det.state);
		ret = cvbs_rpc(1);
		gpio_set_value(cvbs_det.gpio_mute, 0);/*mute*/
		cvbs_info("cvbs unplugged");
	} else if (cvbs_det.state == 1) { /*cvbs on*/
		switch_set_state(&cvbs_det.sdev, cvbs_det.state);
		ret = cvbs_rpc(0);
		gpio_set_value(cvbs_det.gpio_mute, 1);/*unmute*/
		cvbs_info("cvbs plugged");
	}

	if (ret)
		cvbs_error("rpc failed\n");
}

static irqreturn_t cvbs_switch_isr(int irq, void *data)
{
	schedule_work(&cvbs_det.work);
	return IRQ_HANDLED;
}

static int rtk_cvbs_switch_probe(struct platform_device *pdev)
{
	int ret = 0, mode;

	if (get_rtd_chip_revision() == RTD_CHIP_A01) {
		return -1;
	}
	cvbs_det.sdev.name = CVBS_SWITCH_NAME;
	cvbs_det.sdev.print_state = cvbs_switch_print_state;
	cvbs_det.dev = &pdev->dev;
	cvbs_rpc_ion_client = ion_client_create(rtk_phoenix_ion_device,
						"CVBS_SWITCH");

	ret = switch_dev_register(&cvbs_det.sdev);
	if (ret < 0)
		cvbs_error("err_register_switch");


	if (of_property_read_u32(pdev->dev.of_node, "detect-mode", &mode)) {
		cvbs_error("Get detect-mode failed\n");
		cvbs_error("cvbs use GPIO21 to detect\n");
	}

	if (mode)
		if (of_property_read_u32(pdev->dev.of_node,
				"gpio-activity", &gpio_activity))
			cvbs_error("Get gpio-activity failed\n");

	cvbs_det.gpio = of_get_gpio_flags(pdev->dev.of_node, 0, NULL);
	ret = gpio_request(cvbs_det.gpio, "cvbs_gpio");
	if (ret < 0)
		cvbs_error("%s: can't request gpio %d\n",
				__func__, cvbs_det.gpio);

	gpio_set_debounce(cvbs_det.gpio, 30*1000);

	cvbs_det.gpio_mute = of_get_named_gpio(pdev->dev.of_node, "gpio_mute", 0);
	ret = gpio_request(cvbs_det.gpio_mute, "cvbs_gpio_mute");
	if (ret < 0)
		cvbs_error("%s: can't request gpio %d\n",
				__func__, cvbs_det.gpio_mute);

	INIT_WORK(&cvbs_det.work, cvbs_switch_work_func);
	schedule_work(&cvbs_det.work);

	cvbs_det.irq = gpio_to_irq(cvbs_det.gpio);

	if (!cvbs_det.irq)
		cvbs_error("Fail to get cvbs irq");
	else
		cvbs_debug("irq_num(%u)\n", cvbs_det.irq);

	irq_set_irq_type(cvbs_det.irq, IRQ_TYPE_EDGE_BOTH);
	ret = request_irq(cvbs_det.irq, cvbs_switch_isr,
		IRQF_SHARED, "cvbs_switch", cvbs_det.dev);
	if (ret)
		cvbs_error("Cannot register IRQ %d", cvbs_det.irq);

	return ret;
}


static int rtk_cvbs_switch_suspend(struct platform_device *pdev, pm_message_t state)
{
	disable_irq(cvbs_det.irq);
	free_irq(cvbs_det.irq, cvbs_det.dev);
	/* Cancel work and wait for it to finish */
	cancel_work_sync(&cvbs_det.work);

	return 0;
}

static int rtk_cvbs_switch_resume(struct platform_device *pdev)
{
	int ret;

	schedule_work(&cvbs_det.work);
	gpio_set_debounce(cvbs_det.gpio, 30*1000);
	irq_set_irq_type(cvbs_det.irq, IRQ_TYPE_EDGE_BOTH);
	ret = request_irq(cvbs_det.irq, cvbs_switch_isr,
		IRQF_SHARED, "cvbs_switch", cvbs_det.dev);
	if (ret)
		cvbs_error("Cannot register IRQ %d", cvbs_det.irq);

	return 0;
}


static int rtk_cvbs_switch_remove(struct platform_device *pdev)
{

	disable_irq(cvbs_det.irq);
	free_irq(cvbs_det.irq, cvbs_det.dev);
	gpio_free(cvbs_det.gpio);
	gpio_free(cvbs_det.gpio_mute);
	/* Cancel work and wait for it to finish */
	cancel_work_sync(&cvbs_det.work);
	switch_dev_unregister(&cvbs_det.sdev);

	return 0;
}


static const struct of_device_id rtk_cvbs_match_table[] = {
	{.compatible = "realtek,rtd1395-cvbs-switch",},
	{},
};


static struct platform_driver rtk_cvbs_switch_driver = {
	.probe		= rtk_cvbs_switch_probe,
	.driver		= {
		.name	= "switch-cvbs",
		.of_match_table = of_match_ptr(rtk_cvbs_match_table),
		.owner	= THIS_MODULE,
	},
	.suspend	= rtk_cvbs_switch_suspend,
	.resume		= rtk_cvbs_switch_resume,
	.remove		= rtk_cvbs_switch_remove,
};

static int __init rtk_cvbs_switch_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&rtk_cvbs_switch_driver);
	if (ret != 0)
		goto err_register;

	return 0;
err_register:
	platform_driver_unregister(&rtk_cvbs_switch_driver);

	return -EFAULT;
}

static void __exit rtk_cvbs_switch_exit(void)
{
	platform_driver_unregister(&rtk_cvbs_switch_driver);

}

module_init(rtk_cvbs_switch_init);
module_exit(rtk_cvbs_switch_exit);
MODULE_DESCRIPTION("Realtek CVBS Switch driver");
MODULE_LICENSE("GPL v2");

