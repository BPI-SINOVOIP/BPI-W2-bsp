/*
 * TI DaVinci GPIO Support
 *
 * Copyright (c) 2006 David Brownell
 * Copyright (c) 2007, MontaVista Software, Inc. <source@mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

//#ifndef	__RTK119X_RTK119X_GPIO_H
//#define	__RTK119X_RTK119X_GPIO_H

#include <linux/io.h>
#include <linux/spinlock.h>
#include <asm-generic/gpio.h>
//#include <mach/irqs.h>


//#define RTK_DEBUG
#ifdef RTK_DEBUG
#define RTK_debug(fmt, ...) printk(fmt, ##__VA_ARGS__)
#else
#define RTK_debug(fmt, ...)
#endif

#define GP_HIGH		1
#define GP_LOW		0
#define GP_DIROUT	1
#define GP_DIRIN	0

typedef enum {
    RTK119X_GPIO_DEBOUNCE_37ns = 0,
    RTK119X_GPIO_DEBOUNCE_1us,
    RTK119X_GPIO_DEBOUNCE_10us,
    RTK119X_GPIO_DEBOUNCE_100us,
    RTK119X_GPIO_DEBOUNCE_1ms,
    RTK119X_GPIO_DEBOUNCE_10ms,
    RTK119X_GPIO_DEBOUNCE_20ms,
    RTK119X_GPIO_DEBOUNCE_30ms,
}RTK119X_GPIO_DEBOUNCE;



struct rtk119x_gpio_groups {
	const char		*group_name;
	unsigned int		linux_irq_base;
	void __iomem		*irq_membase;
	unsigned int 		gpio_isr_deassert_offset;
	unsigned int 		gpio_isr_assert_offset;
	unsigned int 		reg_isr_off;
	unsigned int 		reg_umsk_isr_gpa_off;
	unsigned int 		reg_umsk_isr_gpda_off;
	void __iomem		*gpio_membase;
	unsigned int		mem_size;
	unsigned int 		reg_dir_off;
	unsigned int 		reg_dato_off;
	unsigned int 		reg_dati_off;
	unsigned int 		reg_ie_off;
	unsigned int 		reg_dp_off;
	unsigned int 		reg_deb_off;
//	int				bank_irq;
};

struct rtk119x_gpio_desc {
	const struct rtk119x_gpio_groups	*groups;
	int								ngroups;
};


/*
 * basic gpio routines
 *
 * board-specific init should be done by arch/.../.../board-XXX.c (maybe
 * initializing banks together) rather than boot loaders; kexec() won't
 * go through boot loaders.
 *
 * the gpio clock will be turned on when gpios are used, and you may also
 * need to pay attention to PINMUX registers to be sure those pins are
 * used as gpios, not with other peripherals.
 *
 * On-chip GPIOs are numbered 0..(RTK119X_N_GPIO-1).  For documentation,
 * and maybe for later updates, code may write GPIO(N).  These may be
 * all 1.8V signals, all 3.3V ones, or a mix of the two.  A given chip
 * may not support all the GPIOs in that range.
 *
 * GPIOs can also be on external chips, numbered after the ones built-in
 * to the DaVinci chip.  For now, they won't be usable as IRQ sources.
 */
//#define	GPIO(X)		(X)		/* 0 <= X <= (RTK119X_N_GPIO - 1) */

/* Convert GPIO signal to GPIO pin number */
//#define GPIO_TO_PIN(bank, gpio)	(16 * (bank) + (gpio))

struct rtk119x_gpio_controller {
	struct gpio_chip	chip;
	struct irq_chip	gp_irq_chip;
	int				bank_deassert_irq;
	int				bank_assert_irq;
	struct irq_domain *irq_mux_domain;
	spinlock_t		lock;
	unsigned int		gpio_isr_deassert_offset;
	unsigned int		gpio_isr_assert_offset;
	unsigned int		gpio_isr_deassert_enable_flag[10];
	unsigned int		gpio_isr_assert_enable_flag[10];
	unsigned int		linux_irq_base;
	void __iomem		*reg_isr;
	void __iomem		*regs_umsk_isr_gpa;
	void __iomem		*regs_umsk_isr_gpda;
	void __iomem 	*reg_dir;
	void __iomem 	*reg_dato;
	void __iomem		*reg_dati;
	void __iomem 	*reg_ie;
	void __iomem 	*reg_dp;
	void __iomem 	*reg_deb;

};


/* The __gpio_to_controller() and __gpio_mask() functions inline to constants
 * with constant parameters; or in outlined code they execute at runtime.
 *
 * You'd access the controller directly when reading or writing more than
 * one gpio value at a time, and to support wired logic where the value
 * being driven by the cpu need not match the value read back.
 *
 * These are NOT part of the cross-platform GPIO interface
 */
/*
static inline struct rtk119x_gpio_controller *
__gpio_to_controller(unsigned gpio)
{
	struct rtk119x_gpio_controller *ctlrs = rtk119x_soc_info.gpio_ctlrs;
	int index = gpio / 32;

	if (!ctlrs || index >= rtk119x_soc_info.gpio_ctlrs_num)
		return NULL;

	return ctlrs + index;
}

static inline u32 __gpio_mask(unsigned gpio)
{
	return 1 << (gpio % 32);
}
*/










//#endif	/* __RTK119X_RTK119X_GPIO_H */
