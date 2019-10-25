/*
 * rtk_sb2.h - bus debug driver
 *
 * Copyright (c) 2019 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef __RTK_SB2_H_INCLUDED
#define __RTK_SB2_H_INCLUDED

#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/bitops.h>
#include <linux/arm-smccc.h>

/* register definitions */
#define SB2_HD_SEM                      (0x000)
#define SB2_INV_INTEN                   (0x004)
#define SB2_INV_INTSTAT                 (0x008)
#define SB2_INV_ADDR                    (0x00c)
#define SB2_DEBUG_REG                   (0x010)
#define SB2_CHIP_ID                     (0x200)
#define SB2_CHIP_INFO                   (0x204)

#define SB2_RBUS_ICG1                   (0x308)
#define SB2_RBUS_ICG2                   (0x30c)
#define SB2_RBUS_ICG3                   (0x310)

#define SB2_DBG_START_REG0              (0x458)
#define SB2_DBG_START_REG1              (0x45c)
#define SB2_DBG_START_REG2              (0x460)
#define SB2_DBG_START_REG3              (0x464)
#define SB2_DBG_START_REG4              (0x468)
#define SB2_DBG_START_REG5              (0x46c)
#define SB2_DBG_START_REG6              (0x470)
#define SB2_DBG_START_REG7              (0x474)

#define SB2_DBG_END_REG0                (0x478)
#define SB2_DBG_END_REG1                (0x47c)
#define SB2_DBG_END_REG2                (0x480)
#define SB2_DBG_END_REG3                (0x484)
#define SB2_DBG_END_REG4                (0x488)
#define SB2_DBG_END_REG5                (0x48c)
#define SB2_DBG_END_REG6                (0x490)
#define SB2_DBG_END_REG7                (0x494)

#define SB2_DBG_CTRL_REG0               (0x498)
#define SB2_DBG_CTRL_REG1               (0x49c)
#define SB2_DBG_CTRL_REG2               (0x4a0)
#define SB2_DBG_CTRL_REG3               (0x4a4)
#define SB2_DBG_CTRL_REG4               (0x4a8)
#define SB2_DBG_CTRL_REG5               (0x4ac)
#define SB2_DBG_CTRL_REG6               (0x4b0)
#define SB2_DBG_CTRL_REG7               (0x4b4)
#define SB2_DBG_ADDR_AUDIO              (0x4b8)
#define SB2_DBG_ADDR_PCPU               (0x4bc)
#define SB2_DBG_ADDR_SYSTEM             (0x4c0)
#define SB2_DBG_ADDR1                   (0x4c8)
#define SB2_DBG_INT                     (0x4E0)

#define SB2_HD_SEM_NEW_0                (0x620)
#define SB2_HD_SEM_NEW_1                (0x624)
#define SB2_HD_SEM_NEW_2                (0x628)
#define SB2_HD_SEM_NEW_3                (0x62c)
#define SB2_HD_SEM_NEW_4                (0x630)
#define SB2_HD_SEM_NEW_5                (0x634)
#define SB2_HD_SEM_NEW_6                (0x638)
#define SB2_HD_SEM_NEW_7                (0x63c)

/* SB2_INV_INTEN */
#define SWCIVAIRQ_EN                    BIT(6)
#define ACIVAIRQ_EN                     BIT(3)
#define PCIVAIRQ_EN                     BIT(2)
#define SCIVAIRQ_EN                     BIT(1)

/* SB2_INV_INTSTAT */
#define SWCIVA_INT                      BIT(4)
#define ACIVA_INT                       BIT(3)
#define PCIVA_INT                       BIT(2)
#define SCIVA_INT                       BIT(1)

#define WRITE_DATA_1                    1
#define WRITE_DATA_0                    0

#define SB2_DBG_MONITOR_DATA            (BIT(4)|BIT(2))
#define SB2_DBG_MONITOR_INST            (BIT(4)|BIT(3))
#define SB2_DBG_MONITOR_READ            (BIT(7)|BIT(5))
#define SB2_DBG_MONITOR_WRITE           (BIT(7)|BIT(6))

/* SB2_DBG_INT */
#define SB2_ACPU_INT                    BIT(12)
#define SB2_PCPU_INT                    BIT(11)
#define SB2_SCPU_INT                    BIT(10)
#define SB2_ACPU_INT_EN                 BIT(9)
#define SB2_PCPU_INT_EN                 BIT(8)
#define SB2_SCPU_INT_EN                 BIT(7)
#define SB2_ACPU_NEG_INT                BIT(6)
#define SB2_PCPU_NEG_INT                BIT(5)
#define SB2_SCPU_NEG_INT                BIT(4)
#define SB2_ACPU_NEG_INT_EN             BIT(3)
#define SB2_PCPU_NEG_INT_EN             BIT(2)
#define SB2_SCPU_NEG_INT_EN             BIT(1)

/* SB2_DBG_CTRL_REG */
#define SET_DBG_ACPU_CHK_EN             (3 << 12)
#define CLR_DBG_ACPU_CHK_EN             (2 << 12)
#define SET_DBG_SCPU_CHK_EN             (3 << 8)
#define CLR_DBG_SCPU_CHK_EN             (2 << 8)
#define SET_DBG_EN                      (3 << 0)
#define CLR_DBG_EN                      (2 << 0)


struct device;
struct device_node;

struct sb2_data {
	void *base;
	phys_addr_t phy;
	int offset;
	int irq;
};


#ifdef CONFIG_RTK_SB2_SECURITY_DEBG
#define SB2_USE_SMCCALL                (1)

#if defined(CONFIG_ARCH_RTD16xx) || defined(CONFIG_ARCH_RTD13xx)
#define SB2_SWCIO_RCMD                  0x8400fffe
#define SB2_SWCIO_WCMD                  0x8400ffff
#elif defined(CONFIG_ARCH_RTD139x)
#define SB2_SWCIO_RCMD                  0x8400ff06
#define SB2_SWCIO_WCMD                  0x8400ff07
#else
#error "invalid sb2 smccall cmd"
#endif

#endif /* CONFIG_RTK_SB2_SECURITY_DEBG */

#ifndef SB2_USE_SMCCALL
#define SB2_USE_SMCCALL                 (0)
#endif

static inline int of_sb2_data_init(struct device_node *np,
				   struct sb2_data *data,
				   int index)
{
	int ret;
	struct resource res;

	ret = of_address_to_resource(np, index, &res);
	if (ret)
		return ret;

	data->base = ioremap(res.start, resource_size(&res));
	if (!data->base)
		return -ENOMEM;

	data->phy    = res.start & ~0xfff;
	data->offset = res.start & 0xfff;
	return 0;
}

static inline void sb2_data_fini(struct sb2_data *data)
{
	iounmap(data->base);
}

static inline u32 sb2_read(struct sb2_data *data,
			   u32 offset)
{
	u32 val;

#ifdef CONFIG_RTK_SB2_SECURITY_DEBG
	struct arm_smccc_res res;

	arm_smccc_smc(SB2_SWCIO_RCMD, (u32)data->phy | (offset + data->offset), 0, 0, 0, 0, 0, 0, &res);
	val = res.a0;
#else
	val = readl(data->base + offset);
#endif
	return val;
}

static inline void sb2_write(struct sb2_data *data,
			     u32 offset,
			     u32 val)
{
#ifdef CONFIG_RTK_SB2_SECURITY_DEBG
	struct arm_smccc_res res;

	arm_smccc_smc(SB2_SWCIO_WCMD, (u32)data->phy | (offset + data->offset), val, 0, 0, 0, 0, 0, &res);
#else
	writel(val, data->base + offset);
#endif
}

#endif /* __RTK_SB2_H_INCLUDED */
