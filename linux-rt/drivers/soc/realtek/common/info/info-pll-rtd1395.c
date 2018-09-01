/*
 * Dump information of RTD139X/161X PLL
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/seq_file.h>
#include "info.h"

#define DIV_SEL(_v, _h, _l) \
	(((_v) >> (_l)) & (BIT((_h) - (_l) + 1) - 1))

#define PLL_SHIFT  13
#define PLL_MASK   (BIT(29 - 13 + 1) - 1)
#define RETRY_MAX  30000

static int pll_get_freq(unsigned int addr, unsigned int *freq)
{
	int ret = 0;
	void *reg = ioremap(addr, 0x4);
	int retry = RETRY_MAX;

	writel(0x0, reg);
	writel(0x1, reg);
	writel(0x3, reg);

	while (--retry && (readl(reg) & BIT(30)) == 0)
		;

	if (!retry)
		ret = -EINVAL;
	else
		*freq = ((readl(reg) >> PLL_SHIFT) & PLL_MASK) / 10;

	writel(0x0, reg);
	iounmap(reg);

	return ret;
}

static int pll_scpu_get_freq(unsigned int addr, unsigned int *freq)
{
	int ret = 0;
	void *reg = ioremap(addr, 0xC);
	int retry = RETRY_MAX;

	writel(readl(reg) & ~0x30000, reg);
	writel(readl(reg) | 0x20000, reg);
	writel(readl(reg) | 0x30000, reg);

	while (--retry && (readl(reg+8) & BIT(0)) == 0)
		;

	if (!retry)
		ret = -EINVAL;
	else
		*freq = ((readl(reg + 8) >> 1) & PLL_MASK) / 10;

	writel(readl(reg) & ~0x30000, reg);
	iounmap(reg);

	return ret;
}

static void pll_show_one(struct seq_file *s, const char *name, unsigned int addr)
{
	unsigned int freq;

	seq_printf(s, "  %-10s ", name);

	if ((addr == 0x9801D700 && pll_scpu_get_freq(addr, &freq)) ||
		(addr != 0x9801D700 && pll_get_freq(addr, &freq)))
		seq_puts(s, "unavailable\n");
	else
		seq_printf(s, "%4d MHz\n", freq);
}

static int pll_div(int val)
{
	if (val & BIT(1))
		return (val & BIT(0)) ? 4 : 2;
	return 1;
}

static int pll_scpu_div(int val)
{
#ifdef CONFIG_ARCH_RTD139x
	if (val & BIT(7)) {
		val = (val & ~BIT(7)) >> 2;
		switch (val) {
		case 5: case 6: case 7: case 8: case 10: case 13:
			return val;
		default:
			return 3;
		}
	} else if (val & BIT(1)) {
		return (val & BIT(0)) ? 4 : 2;
	}
	return 1;
#elif defined(CONFIG_ARCH_RTD16xx)
	if (val & 0x80)
		return (val & ~0x80) >> 2;
	return 1;
#else
	return -1;
#endif
}

static int pll_acpu_div(int val)
{
	return 1 << (ffs(~val) - 1);
}

static unsigned int get_div(void)
{
	void *reg = ioremap(0x98000030, 0x4);
	unsigned int div = readl(reg);

	iounmap(reg);
	return div;
}

static int pll_show(struct seq_file *s)
{
	unsigned int raw = get_div();
	unsigned int sel;

	seq_puts(s, "PLL FREQ\n");
	pll_show_one(s, "PLL_SCPU",  0x9801D700);
	pll_show_one(s, "PLL_BUS",   0x98000424);
	pll_show_one(s, "PLL_DCSB",  0x98000428);
	pll_show_one(s, "PLL_ACPU",  0x9800042C);
	pll_show_one(s, "PLL_DDSA",  0x98000430);
#ifdef CONFIG_ARCH_RTD139x
	pll_show_one(s, "PLL_DDSB",  0x98000434);
#endif
	pll_show_one(s, "PLL_GPU",   0x98000438);
	pll_show_one(s, "PLL_VCPU",  0x9800043C);
	pll_show_one(s, "PLL_VCPU2", 0x98000440);

	seq_puts(s, "PLL DIV SEL/VAL\n");
	sel = DIV_SEL(raw, 16, 6);
	seq_printf(s, "  SCPU SEL = 0x%02x VAL = %2d\n", sel, pll_scpu_div(sel));
	sel = DIV_SEL(raw, 1, 0);
	seq_printf(s, "  BUS  SEL = 0x%02x VAL = %2d\n", sel, pll_div(sel));
	sel = DIV_SEL(raw, 3, 2);
	seq_printf(s, "  DCSB SEL = 0x%02x VAL = %2d\n", sel, pll_div(sel));
	sel = DIV_SEL(raw, 26, 22);
	seq_printf(s, "  ACPU SEL = 0x%02x VAL = %2d\n", sel, pll_acpu_div(sel));

	return 0;
}

static int pll_init(void)
{
	info_dump_create_file("pll", pll_show);
	return 0;
}
late_initcall(pll_init);

