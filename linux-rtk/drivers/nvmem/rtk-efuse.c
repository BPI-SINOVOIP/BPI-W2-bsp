/*
 * rtk-efuse.c - Realtek eFuse driver
 *
 * Copyright (C) 2016-2018 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2018 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/nvmem-provider.h>
#include <linux/nvmem-consumer.h>
#include <soc/realtek/rtd129x_efuse.h>

#define BITMAP_CAST(_p) ((unsigned long *)(_p))

struct efuse_device {
	struct device *dev;
	struct list_head list;
	void *base;
	struct nvmem_device *nvmem;
};

static LIST_HEAD(efuse_device_list);
static struct kobject *efuse_kobj;

static int get_cell_nbits(struct device *dev, const char *name)
{
	struct device_node *np = dev->of_node;
	struct device_node *cell_np;
	int index = 0;
	u32 len;
	int ret;

	if (name)
		index = of_property_match_string(np, "nvmem-cell-names", name);

	cell_np = of_parse_phandle(np, "nvmem-cells", index);
	if (!cell_np)
		return -EINVAL;

	ret = of_property_read_u32_index(cell_np, "bits", 1, &len);
	if (ret)
		return ret;
	return len;
}

static size_t snprint_bit_lsb(char *buf, size_t size,
	const unsigned char *cell_data, size_t nbits)
{
	int i = 0, j = 0;

	if (size < (nbits + (nbits / 8)))
		return 0;

	for (i = 0; i < nbits; i++) {
		if (i != 0 &&  (i & 7) == 0)
			buf[j++] = ' ';
		buf[j++] =  (cell_data[i >> 3] & BIT(i & 7)) ? '1' : '0';
	}
	return j;
}

static ssize_t show_one_device_cell(char *buf, int len, struct device *dev,
	const char *name)
{
	struct nvmem_cell *cell;
	unsigned char *cell_data;
	size_t cell_data_size;
	int cell_nbits;

	len += snprintf(buf + len, PAGE_SIZE - len, "%-16s ", name);

	cell = nvmem_cell_get(dev, name);
	if (IS_ERR(cell)) {
		len += snprintf(buf + len, PAGE_SIZE - len, "%4s  %s",
			"", "(invalid cell-name)\n");
		return len;
	}
	cell_data = nvmem_cell_read(cell, &cell_data_size);
	nvmem_cell_put(cell);

	cell_nbits = get_cell_nbits(dev, name);
	if (cell_nbits < 0) {
		len += snprintf(buf + len, PAGE_SIZE - len, "%4s  %s",
			"", "(read error)");
		goto done;
	}

	len += snprintf(buf + len, PAGE_SIZE - len, "%4d  ", cell_nbits);

	if (bitmap_weight(BITMAP_CAST(cell_data), cell_nbits) == 0) {
		len += snprintf(buf + len, PAGE_SIZE - len, "(no data)");
		goto done;
	}

	/* show in bin format */
	len += snprintf(buf + len, PAGE_SIZE - len, "bin=<");
	len += snprint_bit_lsb(buf + len, PAGE_SIZE - len, cell_data, cell_nbits);
	len += snprintf(buf + len, PAGE_SIZE - len, ">");

	/* show in hex format */
	len += snprintf(buf + len, PAGE_SIZE - len, ", hex=%*pb",
		cell_nbits, BITMAP_CAST(cell_data));
done:
	len += snprintf(buf + len, PAGE_SIZE - len, "\n");
	kfree(cell_data);
	return len;
}

static ssize_t show_one_device(char *buf, int len, struct device *dev)
{
	struct property *prop;
	const char *name;

	len += snprintf(buf + len, PAGE_SIZE - len, "device: %s\n",
		dev_name(dev));
	len += snprintf(buf + len, PAGE_SIZE - len, "%-16s %4s  %s\n",
		"name", "len", "data");
	of_property_for_each_string(dev->of_node, "nvmem-cell-names",
		prop, name) {
		len = show_one_device_cell(buf, len, dev, name);
		if (len >= PAGE_SIZE)
			return PAGE_SIZE;
	}
	return len;
}

static ssize_t summary_show(struct kobject *kobj, struct kobj_attribute *attr,
	char *buf)
{
	struct efuse_device *pos;
	int len = 0;

	list_for_each_entry(pos, &efuse_device_list, list) {
		len = show_one_device(buf, len, pos->dev);
		if (len >= PAGE_SIZE)
			return PAGE_SIZE;
	}
	return len;
}

static struct kobj_attribute summary_attr = __ATTR_RO(summary);

static __init int sysfs_create(void)
{
	int ret = 0;

	efuse_kobj = kobject_create_and_add("efuse", kernel_kobj);
	if (!efuse_kobj) {
		pr_warn("rtk-efuse: cannot create kobject\n");
		return -ENOMEM;
	}

	ret = sysfs_create_file(efuse_kobj, &summary_attr.attr);
	if (ret) {
		pr_warn("rtk-efuse: cannot create sysfs group. err:%d\n", ret);
		goto error;
	}
	return 0;

error:
	if (efuse_kobj)
		kobject_del(efuse_kobj);
	return ret;
}
static __exit void sysfs_destroy(void)
{
	sysfs_remove_file(efuse_kobj, &summary_attr.attr);
	kobject_del(efuse_kobj);
}

static int rtk_efuse_read(void *priv, unsigned int offset, void *val,
	size_t bytes)
{
	struct efuse_device *edev = priv;
	void __iomem *base = edev->base;
	unsigned char *valp = val;
	int size = bytes;
	int i;


	for (i = 0; i < size; i++) {
		valp[i] = readb(base + offset  + i);
		dev_dbg(edev->dev, "addr=%03x, val=%02x\n", offset+i, valp[i]);
	}
	return 0;
}

static struct nvmem_config config = {
	.name = "rtk-efuse",
	.stride = 1,
	.word_size = 4,
	.reg_read = rtk_efuse_read,
	.owner = THIS_MODULE,
};

static int rtk_efuse_probe(struct platform_device *pdev)
{
	struct efuse_device *edev;
	struct device *dev = &pdev->dev;
	struct resource *res;

	dev_info(dev, "%s\n", __func__);

	edev = devm_kzalloc(dev, sizeof(*edev), GFP_KERNEL);
	if (!edev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	edev->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(edev->base))
		return PTR_ERR(edev->base);
	edev->dev = dev;

	config.priv = edev;
	config.dev  = dev;
	config.size = resource_size(res);
	edev->nvmem = nvmem_register(&config);
	if (IS_ERR(edev->nvmem))
		return PTR_ERR(edev->nvmem);
	list_add(&edev->list, &efuse_device_list);
	platform_set_drvdata(pdev, edev);

	return 0;
}

static int rtk_efuse_remove(struct platform_device *pdev)
{
	struct efuse_device *edev = platform_get_drvdata(pdev);

	list_del(&edev->list);
	platform_set_drvdata(pdev, NULL);
	nvmem_unregister(edev->nvmem);

	return 0;
}

static const struct of_device_id rtk_efuse_of_match[] = {
	{.compatible = "realtek,efuse",},
	{},
};

static struct platform_driver rtk_efuse_drv = {
	.probe = rtk_efuse_probe,
	.remove = rtk_efuse_remove,
	.driver = {
		.name = "rtk-efuse",
		.owner = THIS_MODULE,
		.of_match_table = rtk_efuse_of_match,
	},
};

static __init int rtk_efuse_init(void)
{
	sysfs_create();
	return platform_driver_register(&rtk_efuse_drv);
}
subsys_initcall(rtk_efuse_init);

MODULE_DESCRIPTION("Realtek eFuse driver");
MODULE_ALIAS("platform:rtk-efuse");
MODULE_LICENSE("GPL");
