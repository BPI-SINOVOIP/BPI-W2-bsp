/*
 * Realtek CPU high-load booster
 *
 * Copyright (c) 2019, Realtek Semiconductor Corporation
 *
 * Author:
 *        Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#define pr_fmt(fmt) "rtk-cpu-hlb: " fmt
#include <linux/cpufreq.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/cpu.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/workqueue.h>

#define CPU_HLB_DEFAULT_BYPASS          (1)
#define CPU_HLB_DEFAULT_FREQ_THRESHOLD  (1300000)
#define CPU_HLB_DEFAULT_LOAD_THRESHOLD  (90)
#define CPU_HLB_DEFAULT_POLLING_TIME    (500)

struct rtk_cpu_hlb_data {
	struct device *dev;
	struct delayed_work dwork;
	struct notifier_block nb;

	/* sysfs */
	bool bypass;
	u32 polling_time;
	u32 load_th;
	u32 freq_th;

	u32 limit;
	u32 prev_limit;
	u64 prev_update_time[CONFIG_NR_CPUS];
	u64 prev_idle_time[CONFIG_NR_CPUS];
};

#define CPU_HLB_U32_DEVICE_ATTR(_m)                           \
static ssize_t _m ## _store(struct device *dev,               \
			    struct device_attribute *attr,    \
			    const char *buf,                  \
			    size_t count)                     \
{                                                             \
	struct rtk_cpu_hlb_data *data = dev_get_drvdata(dev); \
	int ret;                                              \
	u32 val;                                              \
\
	ret = kstrtou32(buf, 10, &val);                       \
	if (ret)                                              \
		return ret;                                   \
	if (val != data->_m) {                                \
		data->_m = val;                               \
		cpufreq_update_policy(0);                     \
	}                                                     \
	return count;                                         \
}                                                             \
static ssize_t _m ##_show(struct device *dev,                 \
			  struct device_attribute *attr,      \
			  char *buf)                          \
{                                                             \
	struct rtk_cpu_hlb_data *data = dev_get_drvdata(dev); \
\
	return snprintf(buf, PAGE_SIZE, "%u\n", data->_m);    \
}                                                             \
DEVICE_ATTR_RW(_m)

CPU_HLB_U32_DEVICE_ATTR(polling_time);
CPU_HLB_U32_DEVICE_ATTR(load_th);
CPU_HLB_U32_DEVICE_ATTR(freq_th);

static ssize_t bypass_show(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct rtk_cpu_hlb_data *data = dev_get_drvdata(dev);

	return snprintf(buf, PAGE_SIZE, "%s\n",
		data->bypass ? "true" : "false");
}
static ssize_t bypass_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf,
			      size_t count)
{
	struct rtk_cpu_hlb_data *data = dev_get_drvdata(dev);
	int ret;
	bool val;

	ret = kstrtobool(buf, &val);
	if (ret)
		return ret;

	if (val != data->bypass) {
		data->bypass = val;
		cpufreq_update_policy(0);
	}
	return count;
}
DEVICE_ATTR_RW(bypass);

static struct attribute *hlb_attrs[] = {
	&dev_attr_bypass.attr,
	&dev_attr_polling_time.attr,
	&dev_attr_load_th.attr,
	&dev_attr_freq_th.attr,
	NULL
};

static struct attribute_group hlb_attr_group = {
	.name = "hlb",
	.attrs = hlb_attrs,
};

static int
rtk_cpu_hlb_cb(struct notifier_block *nb, unsigned long action, void *p)
{
	struct rtk_cpu_hlb_data *data = container_of(nb,
		struct rtk_cpu_hlb_data, nb);
	struct cpufreq_policy *policy = p;

	if (data->bypass)
		return NOTIFY_DONE;

	if (action != CPUFREQ_ADJUST)
		return NOTIFY_DONE;

	if (data->limit == 1)
		cpufreq_verify_within_limits(policy, 0, data->freq_th);
	return NOTIFY_OK;
}

static void rtk_cpu_hlb_load_worker(struct work_struct *work)
{
	int cpu = cpumask_first(cpu_online_mask);
	struct rtk_cpu_hlb_data *data = container_of(work,
		struct rtk_cpu_hlb_data, dwork.work);
	u32 max_load = 0;
	struct cpufreq_policy *policy;
	u32 j;

	if (data->bypass)
		goto done;

	policy = cpufreq_cpu_get(cpu);
	if (!policy) {
		dev_err(data->dev, "can't get cpu policy, worker stop\n");
		return;
	}
	for_each_cpu(j, policy->cpus) {
		u64 update, idle;
		u32 d_update, d_idle;
		u32 load;

		idle = get_cpu_idle_time(j, &update, 0);

		d_idle = idle - data->prev_idle_time[j];
		data->prev_idle_time[j] = idle;
		d_update = update - data->prev_update_time[j];
		data->prev_update_time[j] = update;

		load = 100 * (d_update - d_idle) / d_update;
		if (load > max_load)
			max_load = load;
	}
	cpufreq_cpu_put(policy);

	dev_dbg(data->dev, "max_load=%u\n", max_load);
	data->prev_limit = data->limit;
	data->limit = max_load <= data->load_th;
	if (data->prev_limit != data->limit)
		cpufreq_update_policy(cpu);
done:
	queue_delayed_work(system_freezable_wq, &data->dwork,
		msecs_to_jiffies(data->polling_time));
}

static int rtk_cpu_hlb_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rtk_cpu_hlb_data *data;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->dev = dev;
	data->bypass       = CPU_HLB_DEFAULT_BYPASS;
	data->polling_time = CPU_HLB_DEFAULT_POLLING_TIME;
	data->load_th      = CPU_HLB_DEFAULT_LOAD_THRESHOLD;
	data->freq_th      = CPU_HLB_DEFAULT_FREQ_THRESHOLD;

	ret = sysfs_create_group(&dev->kobj, &hlb_attr_group);
	if (ret) {
		dev_err(dev, "sysfs_create_group() returns %d\n", ret);
		return ret;
	}

	data->nb.notifier_call = rtk_cpu_hlb_cb;
	cpufreq_register_notifier(&data->nb, CPUFREQ_POLICY_NOTIFIER);

	INIT_DELAYED_WORK(&data->dwork, rtk_cpu_hlb_load_worker);
	rtk_cpu_hlb_load_worker(&data->dwork.work);

	platform_set_drvdata(pdev, data);
	dev_info(dev, "bypass=%d, polling-ms=%u, load_th=%u, freq_th=%u\n",
		data->bypass, data->polling_time, data->load_th, data->freq_th);
	dev_info(dev, "initialized\n");
	return 0;

}

static int rtk_cpu_hlb_remove(struct platform_device *pdev)
{
	struct rtk_cpu_hlb_data *data = platform_get_drvdata(pdev);
	struct device *dev = &pdev->dev;

	cancel_delayed_work(&data->dwork);
	cpufreq_unregister_notifier(&data->nb, CPUFREQ_POLICY_NOTIFIER);
	sysfs_remove_group(&dev->kobj, &hlb_attr_group);
	dev_info(dev, "removed\n");
	return 0;
}


static struct platform_driver rtk_cpu_hlb_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "rtk-cpu-hlb",
	},
	.probe = rtk_cpu_hlb_probe,
	.remove = rtk_cpu_hlb_remove,
};

static struct platform_device *rtk_cpu_hlb_pdev;

static int __init rtk_cpu_hlb_init(void)
{
	int ret;

	ret = platform_driver_register(&rtk_cpu_hlb_driver);
	if (ret) {
		pr_err("failed to register platform driver: %d\n", ret);
		return ret;
	}

	rtk_cpu_hlb_pdev = platform_device_register_simple("rtk-cpu-hlb",
							   PLATFORM_DEVID_NONE,
							   NULL, 0);
	if (IS_ERR(rtk_cpu_hlb_pdev)) {
		ret = PTR_ERR(rtk_cpu_hlb_pdev);
		pr_err("failed to register platform driver: %d\n", ret);
		platform_driver_unregister(&rtk_cpu_hlb_driver);
		return ret;
	}
	return 0;
}
module_init(rtk_cpu_hlb_init);

static void __exit rtk_cpu_hlb_exit(void)
{
	platform_device_unregister(rtk_cpu_hlb_pdev);
	platform_driver_unregister(&rtk_cpu_hlb_driver);
}
module_exit(rtk_cpu_hlb_exit);
