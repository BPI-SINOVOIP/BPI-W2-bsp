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
#include <linux/workqueue.h>
#include <soc/realtek/rtk_chip.h>

#include "cvbs_rpc.h"


//#define CVBS_DEBUG

#define CVBS_SWITCH_NAME "cvbs_switch"
#define cvbs_error(format, ...)  \
	pr_err("[CVBS_SWITCH_ERR] " format "\n", ## __VA_ARGS__)
#define cvbs_info(format, ...)  \
	pr_info("[CVBS_SWITCH] " format "\n", ## __VA_ARGS__)
#ifdef CVBS_DEBUG
#define cvbs_debug(format, ...)  \
	pr_info("[CVBS_SWITCH_DEBUG] " format "\n", ## __VA_ARGS__)
#else
#define cvbs_debug(format, ...)
#endif

#ifdef CONFIG_ARCH_RTD129x
#define CONVERT_FOR_AVCPU(x)        ((unsigned int)(x) | 0xA0000000)
#else
#define CONVERT_FOR_AVCPU(x)        (x)
#endif

struct CVBS_DET {
	struct switch_dev sdev;
	struct device *dev;
	int gpio;
	int gpio_mute;
	unsigned int irq;
	int state;
	struct work_struct work;
} cvbs_det;

int gpio_activity;
struct ion_client *cvbs_rpc_ion_client;

extern struct ion_device *rtk_phoenix_ion_device;
