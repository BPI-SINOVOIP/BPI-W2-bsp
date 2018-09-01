/**
 * Copyright (c) 2015-2016 Realtek. All rights reserved.
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License ("GPL")
 * version 2, as published by the Free Software Foundation.
 */

#include <linux/hw_random.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/delay.h>

#define MAX_1MS_TO_CNT          1000

#define TRNG_REG_BASE           0

#if defined(CONFIG_ARCH_RTD129x)

#define RNG_CALI_CHK            (TRNG_REG_BASE + 0x18)
#define RNG_ANA                 (TRNG_REG_BASE + 0x14)
#define RNG_CALI_RETURN         (TRNG_REG_BASE + 0x20)
#define RNG_LOCK_CHK            (TRNG_REG_BASE + 0x24)
#define RNG_RETURN3             (TRNG_REG_BASE + 0x2c)
#define RNG_RETURN4             (TRNG_REG_BASE + 0x30)
#define RNG_RESULTR             (TRNG_REG_BASE + 0x38)
#define RNG_DUMMY               (TRNG_REG_BASE + 0x44)

#elif defined(CONFIG_ARCH_RTD139x)

#define RNG_CTRL		(TRNG_REG_BASE + 0x00)
#define RNG_CALI_CHK            (TRNG_REG_BASE + 0x08)
#define RNG_ANA                 (TRNG_REG_BASE + 0x04)
#define RNG_CALI_RETURN         (TRNG_REG_BASE + 0x10)
#define RNG_LOCK_CHK            (TRNG_REG_BASE + 0x14)
#define RNG_RETURN3             (TRNG_REG_BASE + 0x1c)
#define RNG_RETURN4             (TRNG_REG_BASE + 0x20)
#define RNG_RESULTR             (TRNG_REG_BASE + 0x28)
#define RNG_DUMMY               (TRNG_REG_BASE + 0x34)
#define RNG_ST              	(TRNG_REG_BASE + 0x3c)

#elif defined(CONFIG_ARCH_RTD16xx)

#define RNG_CTRL		(TRNG_REG_BASE + 0x00)
#define RNG_CALI_CHK            (TRNG_REG_BASE + 0x08)
#define RNG_ANALOG              (TRNG_REG_BASE + 0x04)
#define RNG_CALI_CTRL           (TRNG_REG_BASE + 0x0c)
#define RNG_CALI_RETURN0        (TRNG_REG_BASE + 0x10)
#define RNG_LOCK_CHK            (TRNG_REG_BASE + 0x14)
#define RNG_RETURN0             (TRNG_REG_BASE + 0x1c)
#define RNG_RETURN1             (TRNG_REG_BASE + 0x20)
#define RNG_RETURN2             (TRNG_REG_BASE + 0x24)
#define RNG_RESULTR             (TRNG_REG_BASE + 0x28)
#define RNG_DUMMY               (TRNG_REG_BASE + 0x34)
#define RNG_ST              	(TRNG_REG_BASE + 0x3c)

/* RTD16xx changes this RNG_RETURN3 as 0 */
#define RNG_RETURN3		RNG_RETURN0            
#endif 

static int rtd_rng_read(struct hwrng *rng, void *buf, size_t max,
                               bool wait)
{
        void __iomem *rng_base = (void __iomem *)rng->priv;
        unsigned int tocnt=0;

        while (!(__raw_readl(rng_base + RNG_RETURN3) & 0x1)) {
                if (!wait || tocnt++ > MAX_1MS_TO_CNT){
			pr_err("**************************%s timeout******************** \n", __func__);
                        return 0;
		}
                cpu_relax();
        }
        *(u32 *)buf = __raw_readl(rng_base + RNG_RESULTR);
        return sizeof(u32);
}

static int rtd_rng_init(struct hwrng *rng)
{
        void __iomem *rng_base = (void __iomem *)rng->priv;
        pr_info("%s %d\n", __func__, __LINE__);

#if defined(CONFIG_ARCH_RTD129x)
        __raw_writel(0xd8000220, rng_base + RNG_CALI_CHK);
        __raw_writel(0xd8000220, rng_base + RNG_LOCK_CHK);
        __raw_writel(0x00008891, rng_base + RNG_ANA);
#elif defined(CONFIG_ARCH_RTD139x)
	__raw_writel(0x00001000, rng_base + RNG_CTRL);
	__raw_writel(0x24a524a4, rng_base + RNG_CALI_CHK);
        __raw_writel(0x300021c0, rng_base + RNG_LOCK_CHK);
        __raw_writel(0x00008b91, rng_base + RNG_ANA);
	__raw_writel(0x00014062, rng_base + RNG_ST);
#elif defined(CONFIG_ARCH_RTD16xx)
	__raw_writel(0x00008000, rng_base + RNG_CTRL);
	__raw_writel(0x010c1041, rng_base + RNG_CALI_CTRL);
	__raw_writel(0x24a524a4, rng_base + RNG_CALI_CHK);
        __raw_writel(0x300021c0, rng_base + RNG_LOCK_CHK);
        __raw_writel(0x00008b91, rng_base + RNG_ANALOG); 
#endif
	msleep(2);
        return 0;
}

static struct hwrng rtd_rng_ops = {
        .name   = "rtd",
        .init   = rtd_rng_init,
        .read   = rtd_rng_read,
	.quality = 1000,
};

static int rtd_rng_probe(struct platform_device *pdev)
{
        struct device *dev = &pdev->dev;
        struct device_node *np = dev->of_node;
        void __iomem *rng_base;
        int err;

        /* map peripheral */
        rng_base = of_iomap(np, 0);
        if (!rng_base) {
                dev_err(dev, "failed to remap rng regs");
                return -ENODEV;
        }
        rtd_rng_ops.priv = (unsigned long)rng_base;



        /* register driver */
	err = hwrng_register(&rtd_rng_ops);
        if (err) {
                dev_err(dev, "hwrng registration failed\n");
                iounmap(rng_base);
                rtd_rng_ops.priv = (unsigned long)0;
        } else
                dev_info(dev, "hwrng registered\n");

        return err;
}

static int rtd_rng_remove(struct platform_device *pdev)
{
        void __iomem *rng_base = (void __iomem *)rtd_rng_ops.priv;


        /* unregister driver */
        hwrng_unregister(&rtd_rng_ops);
        iounmap(rng_base);

        return 0;
}
#ifdef CONFIG_PM
static int rtd_rng_suspend(struct device *dev)
{
        return 0;
}

static int rtd_rng_resume(struct device *dev)
{
        if (rtd_rng_ops.priv)
                rtd_rng_init(&rtd_rng_ops);
        return 0;
}

static const struct dev_pm_ops rtd_rng_pm_ops = {
        .suspend        = rtd_rng_suspend,
        .resume         = rtd_rng_resume,
};
#endif /* CONFIG_PM */

static const struct of_device_id rtd_rng_of_match[] = {
        { .compatible = "Realtek,rtk-rng", },
        {},
};
MODULE_DEVICE_TABLE(of, rtd_rng_of_match);

static struct platform_driver rtd_rng_driver = {
        .driver         = {
                .name = "rtd-rng",
                .of_match_table = rtd_rng_of_match,
#ifdef CONFIG_PM
                .pm             = &rtd_rng_pm_ops,
#endif /* CONFIG_PM */
        },
        .probe          = rtd_rng_probe,
        .remove         = rtd_rng_remove,
};
module_platform_driver(rtd_rng_driver);

MODULE_AUTHOR("Cy Huang");
MODULE_DESCRIPTION("RTD1295/1395 Random Number Generator (RNG) driver");
MODULE_LICENSE("GPL v2");

