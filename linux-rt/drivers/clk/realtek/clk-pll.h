/*
 * clk-pll.h - pll clock with regmap
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __CLK_REALTEK_CLK_PLL_H
#define __CLK_REALTEK_CLK_PLL_H

#include "common.h"

/**
 * struct freq_table - clock frequency table
 *
 * @val:  register valute
 * @mask: mask to apply value to register
 * @rate: frequency
 */
struct freq_table {
	unsigned int val;
	unsigned int mask;
	unsigned long rate;
};

#define FREQ_TABLE_END { .rate = 0 }
#define IS_FREQ_TABLE_END(_f) ((_f)->rate == 0)

/**
 * struct div_table - clock divisor table
 *
 * @rate: rate for divisor selection. When target rate is greater-equal than
 *     the rate, using the divisor.
 * @div:  divisor
 * @val:  register value
 */
struct div_table {
	unsigned long rate;
	unsigned int div;
	unsigned int val;
};

#define DIV_TABLE_END   { .rate = 0 }
#define IS_DIV_TABLE_END(_d) ((_d)->rate == 0)

/**
 * struct clk_pll - pll clock with regmap. Using a frequency table to lookup
 * for frequency.
 *
 * @base:       handle for common, hw and register access interface
 * @pll_offset: offset of register to set pll rate
 * @freq_table: frequency table
 * @ssc_offset: offset of ssc register
 * @rdy_offset: offset for checking the pll is stable
 * @lock:       register lock
 * @flags:      clk_pll flags
 * @status:     clk_pll status
 *
 * Flags:
 * CLK_PLL_REGMAP_BYPASS  - (deprecated) always use direct register access.
 *     Sometime the register access is insecure.
 * CLK_PLL_LSM_STEP_HIGH  - faster pll rate adjustment
 * CLK_PLL_DIV_WORKAROUND - (kylin) workaround for clk_pll_div
 *
 * Status:
 * CLK_PLL_PREPARED - indicate the pll is prepared
 */
struct clk_pll {
	struct clk_reg base;

	const struct freq_table *freq_tbl;
	int pll_offset;
	int pow_offset;
#if defined(CONFIG_COMMON_CLK_RTD129X) || defined(CONFIG_COMMON_CLK_RTD139X) \
	|| defined(CONFIG_COMMON_CLK_RTD16XX)
	int ssc_offset;
	int rdy_offset;
#endif
	spinlock_t *lock;

	unsigned int flags;
	unsigned int status;
};

#define to_clk_pll(_hw) container_of(to_clk_reg(_hw), struct clk_pll, base)
#define __clk_pll_hw(_ptr)  __clk_reg_hw(&(_ptr)->base)

/* clk_pll flags */
#define CLK_PLL_REGMAP_BYPASS          BIT(0)
#define CLK_PLL_LSM_STEP_HIGH          BIT(1)
#define CLK_PLL_DIV_WORKAROUND         BIT(2)

/* clk_pll status */
#define CLK_PLL_PREPARED               BIT(0)

/* clk_pll helper macros & functions */
#define SSC_VALID(_pll) CLK_OFFSET_IS_VALID((_pll)->ssc_offset)
#define RDY_VALID(_pll) CLK_OFFSET_IS_VALID((_pll)->rdy_offset)
#define POW_VALID(_pll) CLK_OFFSET_IS_VALID((_pll)->pow_offset)

static inline unsigned long clk_pll_lock(struct clk_pll *pll)
{
	unsigned long flags = 0;

	if (pll->lock)
		spin_lock_irqsave(pll->lock, flags);
	return flags;
}

static inline void clk_pll_unlock(struct clk_pll *pll, unsigned long flags)
{
	if (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);
}

/**
 * struct clk_pll_div - pll clock externion with divisor
 *
 * @clkp:       pll clock
 * @div_offset: offset of divsor register
 * @div_shift:  shift of divsor bit field
 * @div_width:  width of divsor bit field
 * @div_tbl:    divsor table
 * @lock        divsor register lock
 */
struct clk_pll_div {
	struct clk_pll clkp;
	int div_offset;
	int div_shift;
	int div_width;
	const struct div_table *div_tbl;
	spinlock_t *lock;
};

#define to_clk_pll_div(_hw) \
	container_of(to_clk_pll(_hw), struct clk_pll_div, clkp)
#define __clk_pll_div_hw(_ptr) __clk_pll_hw(&(_ptr)->clkp)

/* clk_pll_div helper functions */
static inline unsigned long clk_pll_div_lock(struct clk_pll_div *plld)
{
	unsigned long flags = 0;

	if (plld->lock)
		spin_lock_irqsave(plld->lock, flags);
	return flags;
}

static inline void clk_pll_div_unlock(struct clk_pll_div *plld,
	unsigned long flags)
{
	if (plld->lock)
		spin_unlock_irqrestore(plld->lock, flags);
}

static inline void hw_set_div_val(struct clk_pll_div *plld, unsigned int val)
{
	unsigned int m = (BIT(plld->div_width) - 1) << plld->div_shift;
	unsigned int s = plld->div_shift;

	clk_reg_update(&plld->clkp.base, plld->div_offset, m, val << s);
}

static inline unsigned int hw_get_div_val(struct clk_pll_div *plld)
{
	unsigned int m = (BIT(plld->div_width) - 1) << plld->div_shift;
	unsigned int s = plld->div_shift;

	return (clk_reg_read(&plld->clkp.base, plld->div_offset) & m) >> s;
}

extern const struct clk_ops clk_pll_ops;
extern const struct clk_ops clk_pll_div_ops;
int clk_pll_init(struct clk_hw *hw);

#ifdef CONFIG_COMMON_CLK_RTD119X

static inline void __hw_set_pow(struct clk_pll *pll, int on)
{
	if (!POW_VALID(pll))
		return;

	/* use clk_reg_update instead of clk_reg_write, since output
	 * divisor (factor o) of pll_bus and pll_dcsb is placed in pow
	 * register
	 */
	if (on) {
		 clk_reg_update(&pll->base, pll->pow_offset, 0x7, 0x3);
		 udelay(200);
	} else {
		 clk_reg_update(&pll->base, pll->pow_offset, 0x7, 0x4);
	}
}

static inline int __hw_is_pow(struct clk_pll *pll)
{
	unsigned int val;

	if (!POW_VALID(pll))
		return -EINVAL;

	val = clk_reg_read(&pll->base, pll->pow_offset);
	return !!(val && 0x1);
}

static inline int __hw_is_oc(struct clk_pll *pll)
{
	unsigned int val;

	if (POW_VALID(pll))
		return -EINVAL;

	val = clk_reg_read(&pll->base, pll->pll_offset);
	return !!(val & 0x1);
}

static inline int __hw_set_rate_prepare(struct clk_pll *pll)
{
	return 0;
}

static inline int __hw_set_rate_done(struct clk_pll *pll)
{
	/* only MNO-type pll has pow reg */
	if (POW_VALID(pll))
		goto mno_type;

	/* SCPU_PLL */
	/* toggle oc_en */
	clk_reg_update(&pll->base, pll->pll_offset + 0x4, 0x1, 0x0);
	clk_reg_update(&pll->base, pll->pll_offset + 0x4, 0x1, 0x1);

	return  0;
mno_type:
	/* MNO-type */

	return 0;
}

#elif defined(CONFIG_COMMON_CLK_RTD129X) || defined(CONFIG_COMMON_CLK_RTD139X) \
	|| defined(CONFIG_COMMON_CLK_RTD16XX)

/*
 * There are 2 types of clk pll in RTD-129X/139X/16XX
 *
 * type NF:
 *  w/ pow:   pll_ddsa, pll_ddsb, pll_gpu
 *  w/o pow:  pll_scpu, pll_bus, pll_dcsb(bus_h)
 * type MNO:
 *  w/ pow:   pll_ve1, pll_ve2
 *
 */
static inline void __hw_set_pow(struct clk_pll *pll, int on)
{
	if (!POW_VALID(pll))
		return;

	if (on) {
		 clk_reg_write(&pll->base, pll->pow_offset, 3);
		 udelay(200);
	} else {
		 clk_reg_write(&pll->base, pll->pow_offset, 4);
	}
}

static inline int __hw_is_pow(struct clk_pll *pll)
{
	unsigned int val;

	if (!POW_VALID(pll))
		return -EINVAL;

	val = clk_reg_read(&pll->base, pll->pow_offset);
	return !!(val && 0x1);
}

static inline int __hw_is_oc(struct clk_pll *pll)
{
	unsigned int val;

	if (!SSC_VALID(pll))
		return -EINVAL;

	val = clk_reg_read(&pll->base, pll->ssc_offset);
	return !!(val & 0x1);
}

static inline int __hw_set_rate_prepare(struct clk_pll *pll)
{
	if (!SSC_VALID(pll))
		return -EINVAL;

	/* clear oc_en */
	clk_reg_update(&pll->base, pll->ssc_offset, 0x7, 0x4);

	return 0;
}

static inline int __hw_set_rate_done(struct clk_pll *pll)
{
	int retry = 2000000;

	/* ssc register is only valid for NF-type PLL */
	if (!SSC_VALID(pll))
		goto mno_done;

	/* for NF-type PLLs */

	/* set oc_en */
	clk_reg_update(&pll->base, pll->ssc_offset, 0x7, 0x5);

	/* wait oc_done == 1 */
	if (!RDY_VALID(pll))
		return -EPERM;
	while (--retry > 0)
		if (clk_reg_read(&pll->base, pll->rdy_offset) & BIT(20))
			return 0;

	return -ETIME;

	/* for MNO-type PLLs */
mno_done:
#if 0
	/*
	 * FIXME: just add flag CLK_SET_RATE_GATE to mno-type pll, to make sure
	 * the rate is set in correct flow for the consumer
	 */
	clk_reg_update(&pll->base, pll->pow_offset, 0x4, 0x0);
	udelay(100);
	clk_reg_update(&pll->base, pll->pow_offset, 0x4, 0x4);
#endif
	return 0;
}

#endif

#endif /* __CLK_REALTEK_CLK_PLL_H */
