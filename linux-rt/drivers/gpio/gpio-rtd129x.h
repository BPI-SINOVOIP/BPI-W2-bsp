/*
 * Realtek GPIO driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */


#ifndef _RTK_GPIO_H_
#define _RTK_GPIO_H_

#include <linux/io.h>
#include <linux/spinlock.h>
#include <asm-generic/gpio.h>


//#define RTK_GPIO_DEBUG
#ifdef RTK_GPIO_DEBUG
#define RTK_GPIO_DBG(fmt, ...) pr_info("[GPIO DBG] " fmt "\n", ## __VA_ARGS__)
#else
#define RTK_GPIO_DBG(fmt, ...)
#endif

#define RTK_GPIO_INF(fmt, ...) pr_info("[GPIO] " fmt "\n", ## __VA_ARGS__)
#define RTK_GPIO_ERR(fmt, ...) pr_err("[GPIO Error] " fmt "\n", ## __VA_ARGS__)

#define GP_HIGH		1
#define GP_LOW		0
#define GP_DIROUT	1
#define GP_DIRIN	0

/*RTK_GPIO_DEBOUNCE*/
enum {
	RTK_GPIO_DEBOUNCE_37ns = 0,
	RTK_GPIO_DEBOUNCE_1us,
	RTK_GPIO_DEBOUNCE_10us,
	RTK_GPIO_DEBOUNCE_100us,
	RTK_GPIO_DEBOUNCE_1ms,
	RTK_GPIO_DEBOUNCE_10ms,
	RTK_GPIO_DEBOUNCE_20ms,
	RTK_GPIO_DEBOUNCE_30ms,
};

#define GPIO_REG_ARRAY_SIZE	 4

#define UNKNOW_OFFSET	0xFFFF

/*GP_REG_TYPE*/
enum {
	GP_REG_UMSK_ISR_GPA = 0,
	GP_REG_UMSK_ISR_GPDA,
	GP_REG_DIR,
	GP_REG_DATO,
	GP_REG_DATI,
	GP_REG_IE,
	GP_REG_DP
};


struct rtk_gpio_groups {
	const char	*group_name;
	u32	group_index;
	u32	linux_irq_base;
	void __iomem	*irq_membase;
	u32	gpio_isr_deassert_int;
	u32	gpio_isr_assert_int;
	u32	reg_isr_off;
	u32	reg_umsk_isr_gpa_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_umsk_isr_gpda_off[GPIO_REG_ARRAY_SIZE];
	void __iomem	*gpio_membase;
	u32	mem_size;
	u32	reg_dir_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_dato_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_dati_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_ie_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_dp_off[GPIO_REG_ARRAY_SIZE];
	u32	reg_deb_off;
};


struct rtk_gpio_controller {
	struct gpio_chip	chip;
	struct irq_chip	gp_irq_chip;
	unsigned int	bank_deassert_irq;
	unsigned int	bank_assert_irq;
	struct irq_domain *irq_mux_domain;
	spinlock_t		lock;
	u32		gpio_isr_deassert_int;
	u32		gpio_isr_assert_int;
	u64		gpio_isr_deassert_enable_flag[GPIO_REG_ARRAY_SIZE];
	u64		gpio_isr_assert_enable_flag[GPIO_REG_ARRAY_SIZE];
	u32		linux_irq_base;
	u32 group_index;
	void __iomem	*reg_isr;
	void __iomem	*irq_regs_base;
	void __iomem	*gpio_regs_base;
	void __iomem	*reg_deb;
};

#endif //_RTK_GPIO_H_
