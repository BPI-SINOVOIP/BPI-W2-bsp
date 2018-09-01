/* rtk_dc_sys_dbg.c - DC system bus debug driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * Author: Chih-Feng Tai <james.tai@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include "rtk_dc_sys_dbg.h"

#define DVR_NAME "RTK_DCSYS_DBG"

#define MM_NUM 8

struct config_mt_info {
	u32 enable;
	u32 saddr;
	u32 eaddr;
	u32 module0;
	u32 module1;
	u32 module2;
	u32 module3;
	u32 int2cpu;
	u32 access_type;
	u32 mode;
};

struct config_ec_info {
	u32 err_cmd_en;
	u32 int2cpu;
};

struct ec_info {
	u32 dc_num;
	u32 warp_type_err;
	u32 read_last_err;
	u32 trap_case;
	u32 addr;
	u32 size;
	char *module;
};

static void ec_show_debug_info(struct ec_info ec)
{
	pr_info("[%s] EC Trapped module is %s 0x%x in dc_sys%d",
		DVR_NAME, ec.module, ec.addr, ec.dc_num);
	pr_info("burst length = %d byte\n", ec.size);

	switch (ec.trap_case) {
	case 0:
		pr_info("[%s] start address is not 16-byte alignment\n",
			DVR_NAME);
		break;
	case 1:
		pr_info("[%s] burst length is zero\n", DVR_NAME);
		break;
	case 2:
		pr_info("[%s] burst Length is not 16-byte alignment\n",
			DVR_NAME);
		break;
	case 3:
		pr_info("[%s] wrong wrap mode\n", DVR_NAME);
		break;
	default:
		pr_info("[%s] unknown case ...", DVR_NAME);
		break;
	}

	if (ec.read_last_err) {
		pr_info("[%s] Detect OCP read last different in dc_sys%d\n",
			DVR_NAME, ec.dc_num);
	} else if (ec.warp_type_err) {
		pr_info("[%s] Detect wrap CMD type mismatch in dc_sys%d\n",
			DVR_NAME, ec.dc_num);
	}
}

irqreturn_t isr_dcsys_dbg(int irq, void *pdev)
{
	struct ec_info ec0;
	struct ec_info ec1;
	u32 int_stat = 0;
	u32 dc_table = 0;
	u32 addcmd_hi = 0;
	u32 addcmd_lo0 = 0;
	u32 addcmd_lo1 = 0;
	u32 int_clear = 0;
	u32 offset = 0;
	u32 module_id0 = 0;
	u32 module_id1 = 0;
	u32 trap_dcsys0 = 0;
	u32 trap_dcsys1 = 0;
	u32 ec_int_stat = 0;
	u32 ec_addcmd_hi = 0;
	u32 ec_addcmd_lo0 = 0;
	u32 ec_addcmd_lo1 = 0;
	u32 size = 0;
	u32 addr = 0;
	u32 int1_flag = 0;
	u32 int2_flag = 0;
	u32 int3_flag = 0;
	u32 ec_int0_flag = 0;
	u32 ec_int1_flag = 0;
	int i = 0;
	int j = 0;
	char *module0 = NULL;
	char *module1 = NULL;

	/* Error command detection part */
	ec_int_stat = readl(DC_EC_CTRL);

	ec_int0_flag = (ec_int_stat >> EC_INT0_B20) & 0x1;
	ec_int1_flag = (ec_int_stat >> EC_INT1_B21) & 0x1;
	if (ec_int0_flag || ec_int1_flag) {
		trap_dcsys0 = (ec_int_stat >> EC_EVER_TRAP0_B22) & 0x1;
		trap_dcsys1 = (ec_int_stat >> EC_EVER_TRAP1_B23) & 0x1;

		ec_addcmd_hi = readl(DC_EC_ADDCMD_HI);
		ec_addcmd_lo0 = readl(DC_EC_ADDCMD_LO_0);
		ec_addcmd_lo1 = readl(DC_EC_ADDCMD_LO_1);

		for (j = 0 ; j < MODULE_NUM ; j++) {
			module_id0 = (ec_addcmd_hi & 0x3FFFF) >> 11;
			module_id1 = (ec_int_stat & 0x3FFFF) >> 11;
			if (module_table[j].id == module_id0)
				module0 = module_table[j].name;
			else if (module_table[j].id == module_id1)
				module1 = module_table[j].name;
		}

		if (trap_dcsys0) {
			ec0.trap_case = (ec_addcmd_hi >> CASE0_B20) & 0xF;
			ec0.read_last_err = (ec_addcmd_hi >> RD_ERR0_B28) & 0x1;
			ec0.warp_type_err =
				(ec_addcmd_hi >> WRAP_ERR0_B30) & 0x1;

			ec0.addr = (ec_addcmd_lo0 >> 2) * 8;
			ec0.size = (ec_addcmd_hi & 0x1FF) * 8;
			ec0.module = module0;
			ec0.dc_num = 0;

			ec_show_debug_info(ec0);

		} else if (trap_dcsys1) {
			ec1.trap_case = (ec_addcmd_hi >> CASE1_B24) & 0xF;
			ec1.read_last_err = (ec_addcmd_hi >> RD_ERR1_B29) & 0x1;
			ec1.warp_type_err =
				(ec_addcmd_hi >> WRAP_ERR1_B31) & 0x1;

			ec1.addr = (ec_addcmd_lo1 >> 2) * 8;
			ec1.size = (ec_int_stat & 0x1FF) * 8;
			ec1.module = module1;
			ec1.dc_num = 1;

			ec_show_debug_info(ec1);
		}

		ec_int_stat = readl(DC_EC_CTRL);
		ec_int_stat = ec_int_stat &
			~(EC_CTRL_EN(EC_INT0_B20) |
			EC_CTRL_EN(EC_INT1_B21) |
			EC_CTRL_EN(EC_EVER_TRAP0_B22) |
			EC_CTRL_EN(EC_EVER_TRAP1_B23));
		writel(ec_int_stat, DC_EC_CTRL);
	}

	/* Memory trash detection part */
	trap_dcsys0 = 0;
	trap_dcsys1 = 0;

	for (i = 0 ; i < MM_NUM ; i++) {
		offset = i * 4;
		int_stat = readl(DC_MT_MODE + offset);
		int1_flag = (int_stat & INT1_TRIG) >> INT1_B13;
		int2_flag = (int_stat & INT2_TRIG) >> INT2_B11;
		int3_flag = (int_stat & INT3_TRIG) >> INT3_B9;

		if (int1_flag == 1 || int2_flag == 1 || int3_flag == 1) {

			dc_table = readl(DC_MT_TABLE + offset);
			addcmd_hi = readl(DC_MT_ADDCMD_HI + offset);
			addcmd_lo0 = readl(DC_MT_ADDCMD_LO_0 + offset);
			addcmd_lo1 = readl(DC_MT_ADDCMD_LO_1 + offset);

			for (j = 0 ; j < MODULE_NUM ; j++) {
				module_id0 = (addcmd_hi >> MOD_ID0_B18) & 0x7F;
				module_id1 = (addcmd_hi >> MOD_ID1_B25) & 0x7F;
				if (module_table[j].id == module_id0)
					module0 = module_table[j].name;
				else if (module_table[j].id == module_id1)
					module1 = module_table[j].name;
			}

			trap_dcsys0 = (dc_table >> 30) & 1;
			trap_dcsys1 = (dc_table >> 31) & 1;

			if (trap_dcsys0 == 1) {
				size = (addcmd_hi & 0x3FF) * 8;
				addr = (addcmd_lo0 >> 2) * 8;
				pr_info("[%s] Trapped module is %s ",
					DVR_NAME, module0);
				pr_info("0x%x in dc_sys0\n",
					addr);
				pr_info("[%s] burst length = %d byte\n",
					DVR_NAME, size);
			} else if (trap_dcsys1 == 1) {
				size = ((addcmd_hi >> 9) & 0x3FF) * 8;
				addr = (addcmd_lo1 >> 2) * 8;
				pr_info("[%s] Trapped module is %s ",
					DVR_NAME, module1);
				pr_info("0x%x in dc_sys1\n",
					addr);
				pr_info("[%s] burst length = %d byte\n",
					DVR_NAME, size);
			}

			pr_info("\n");

			int_clear = WRITE_EN(W_EN1_B14) |
				WRITE_EN(W_EN2_B12) |
				WRITE_EN(W_EN3_B10);

			writel(int_clear, DC_MT_MODE + offset);
		}
	}

	return IRQ_HANDLED;
}

static int dcsys_dbg_init(struct platform_device *pdev)
{
	struct device_node *np;
	struct config_mt_info *mt_config;
	struct config_ec_info *ec_config;
	int dcsys_irq = 0;
	int size = 0;
	int i = 0;
	u32 offset = 0;
	u32 tmp = 0;
	u32 **mt;
	u32 *ec;
	char buf[15];
	int ret;

	if (WARN_ON(!(pdev->dev.of_node))) {
		pr_err("[%s] Error: No node\n", DVR_NAME);
		return -ENODEV;
	}

	np = pdev->dev.of_node;

	DCSYS_BASE = of_iomap(np, 0);

	dcsys_irq = irq_of_parse_and_map(np, 0);
	if (!dcsys_irq) {
		pr_err("[%s] irq parse fail\n", DVR_NAME);
		return -ENXIO;
	}

	snprintf(buf, sizeof(buf), "err_cmd_detect");
	size = of_property_count_u32_elems(pdev->dev.of_node, buf);
	ec = kmalloc_array(size, sizeof(u32), GFP_KERNEL);
	of_property_read_u32_array(pdev->dev.of_node, buf, ec, size);
	ec_config = (struct config_ec_info *)ec;

	ret = request_irq(dcsys_irq,
		isr_dcsys_dbg,
		IRQF_SHARED,
		"dcsys_dbg",
		pdev);
	if (ret != 0) {
		pr_err("[%s] irq request fail\n", DVR_NAME);
		return -ENXIO;
	}

	if (ec_config->err_cmd_en) {
		tmp = tmp |
			EC_CTRL_EN(EC_SWAP_EN_B25) |
			EC_CTRL_EN(EC_DETECT_EN_B24) |
			EC_CTRL_EN(OVER_DCSYS0_B18) |
			EC_CTRL_EN(OVER_DCSYS1_B19) |
			EC_CPU_TYPE(ec_config->int2cpu) |
			EC_CTRL_EN(EC_INT_EN_B26);

		writel(tmp, DC_EC_CTRL);

		pr_info("[%s] DC_EC_CTRL(0x%x) = %x\n",
			DVR_NAME,
			0x98008300,
			tmp);
	}

	mt = kmalloc_array(MM_NUM, sizeof(u32*), GFP_KERNEL);
	size = 0;
	for (i = 0 ; i < MM_NUM ; i++) {
		offset = i * 4;
		snprintf(buf, sizeof(buf), "mt_%d", i);

		size = of_property_count_u32_elems(pdev->dev.of_node, buf);
		mt[i] = kmalloc_array(size, sizeof(u32), GFP_KERNEL);
		of_property_read_u32_array(pdev->dev.of_node, buf, mt[i], size);

		mt_config = (struct config_mt_info *) mt[i];

		if (mt_config->enable != 1)
			continue;

		writel(SADDR(mt_config->saddr), DC_MT_SADDR + offset);
		writel(EADDR(mt_config->eaddr), DC_MT_EADDR + offset);

		tmp = mt_config->module0 |
			mt_config->module1 << 7 |
			mt_config->module2 << 14|
			mt_config->module3 << 21;
		writel(tmp, DC_MT_TABLE + offset);

		tmp = WRITE_EN(W_EN_B2) |
			TRASH_MODE(mt_config->mode) |
			WRITE_EN(W_EN0_B23) |
			ACCESS_TYPE(mt_config->access_type, ACCESS_T0_B21) |
			ACCESS_TYPE(mt_config->access_type, ACCESS_T1_B19) |
			ACCESS_TYPE(mt_config->access_type, ACCESS_T2_B17) |
			ACCESS_TYPE(mt_config->access_type, ACCESS_T3_B15) |
			WRITE_EN(W_EN4_B8) |
			INIT_EN(INT3_EN_B3) |
			INIT_EN(INT2_EN_B4) |
			INIT_EN(INT1_EN_B5) |
			CPU_TYPE(mt_config->int2cpu);

		writel(tmp, DC_MT_MODE + offset);

		pr_info("[%s] DC_MT_MODE(0x%x) = %x\n",
			DVR_NAME,
			0x98008240 + offset,
			tmp);
	}

	for (i = 0 ; i < MM_NUM ; i++)
		kfree(mt[i]);

	kfree(mt);
	kfree(ec);

	pr_info("[%s] initialized\n", DVR_NAME);

	return 0;
}

static int dcsys_dbg_exit(struct platform_device *pdev)
{
	struct device_node *np;
	int sb2_irq;

	pr_info("[%s] Exit\n", DVR_NAME);

	np = pdev->dev.of_node;
	sb2_irq = irq_of_parse_and_map(np, 0);

	free_irq(sb2_irq, NULL);

	return 0;
}

int dcsys_dbg_suspend(struct device *dev)
{
	pr_info("[%s] Enter\n", DVR_NAME);

	pr_info("[%s] Exit\n", DVR_NAME);

	return 0;
}

int dcsys_dbg_resume(struct device *dev)
{
	pr_info("[%s] Resume enter\n", DVR_NAME);

	pr_info("[%s] Resume exit\n", DVR_NAME);

	return 0;
}

static const struct dev_pm_ops dcsys_pm_ops = {
	.suspend_noirq = dcsys_dbg_suspend,
	.resume_noirq = dcsys_dbg_resume,
};

static const struct of_device_id rtk_dcsys_match[] = {
	{.compatible = "realtek,rtk-dcsys-debug"},
	{},
};

static struct platform_driver rtk_dcsys_driver = {
	.probe = dcsys_dbg_init,
	.remove = dcsys_dbg_exit,
	.driver = {
		.name = DVR_NAME,
		.owner = THIS_MODULE,
		.pm = &dcsys_pm_ops,
		.of_match_table = of_match_ptr(rtk_dcsys_match),
	},
};

static void __exit rtk_dcsys_exit(void)
{
	platform_driver_unregister(&rtk_dcsys_driver);
}
module_exit(rtk_dcsys_exit);

static int __init rtk_dcsys_init(void)
{
	return platform_driver_register(&rtk_dcsys_driver);
}
arch_initcall(rtk_dcsys_init);

MODULE_DESCRIPTION("Realtek DC system bus debug driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:RTK-DCSYS-DBG");
