/*
 *
 * Realtek Low Speed ADC driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <common.h>
#include <asm/arch/rbus/iso_reg.h>
#if defined(CONFIG_RTD1395) || defined(CONFIG_RTD161x) || defined(CONFIG_RTD131x)
#include <asm/arch/rbus/iso_testmux_reg.h>
#endif
#include <asm/arch/io.h>
#include "rtk_lsadc.h"

#define LSADC_DEBUG 0

#if LSADC_DEBUG
#define DBG(format, ...) printf(format , ## __VA_ARGS__)
#else
#define DBG(format, ...)
#endif

#define LSADC_BASE_ADDR                                0x98007900
#define LSADC_PG_ADDR                                  0x9800034C

static int adc_to_mV_map[] = {
	   0,  100,  200,  200,  300,  300,  400,  400,  500,  500,
	 600,  600,  700,  700,  800,  800,  900,  900, 1000, 1000,
	1100, 1100, 1200, 1200, 1300, 1300, 1400, 1400, 1500, 1500,
	1600, 1600, 1700, 1700, 1800, 1800, 1900, 1900, 2000, 2000,
	2100, 2200, 2200, 2300, 2300, 2400, 2400, 2500, 2500, 2600,
	2600, 2600, 2700, 2800, 2800, 2900, 2900, 3000, 3000, 3100,
	3100, 3200, 3200, 3300
};

int rtk_lsadc0_pad0_mv_get(void)
{
	u32 value;

	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_PAD0_ADDR);
	value &= LSADC0_PAD_MASK_ADC_VAL;
	DBG("get LSADC0 pad0 adc value = %u (%d mV)\n",
		value, adc_to_mV_map[value]);
	return adc_to_mV_map[value];
}

int rtk_lsadc0_pad0_int_chk(void)
{
	u32 value;
	u32 pad0_int;

	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_STATUS_ADDR);
	pad0_int = value & LSADC_STATUS_MASK_PAD0_STATUS;
	DBG("LSADC0 pad0 status_reg = 0x%x, pad0_int = %d\n", value, pad0_int);
	if (pad0_int > 0) {
		value |= LSADC_STATUS_MASK_PAD0_STATUS;
		rtd_outl(LSADC_BASE_ADDR + LSADC0_STATUS_ADDR, value);
	}
	return pad0_int;
}

static void rtk_lsadc_clk_en(void)
{
	u32 value;

	#if defined(CONFIG_RTD1295)
#define CRT_DUMMY                                      0x98000450
#define CRT_DUMMY_clk_en_lsadc_shift                          (2)
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_B00) {
		/* Enable LSADC clock */
		value = rtd_inl(CRT_DUMMY);
		value |= 1 << CRT_DUMMY_clk_en_lsadc_shift;
		rtd_outl(CRT_DUMMY, value);
	}
	#elif defined(CONFIG_RTD1395)
#define CLOCK_ENABLE1                                  0x9800000C
#define CLOCK_ENABLE1_clk_en_lsadc_shift                     (16)
#define SOFT_RESET1                                    0x98000000
#define SOFT_RESET1_rstn_lsadc_shift                         (21)
	/* Enable LSADC clock */
	value = rtd_inl(CLOCK_ENABLE1);
	value |= 1 << CLOCK_ENABLE1_clk_en_lsadc_shift;
	rtd_outl(CLOCK_ENABLE1, value);

	/* Release LSADC reset */
	value = rtd_inl(SOFT_RESET1);
	value |= 1 << SOFT_RESET1_rstn_lsadc_shift;
	rtd_outl(SOFT_RESET1, value);
	#elif defined(CONFIG_RTD161x) || defined(CONFIG_RTD131x)
#define CLOCK_ENABLE1                                  0x98000050
#define CLOCK_ENABLE1_clk_en_lsadc_shift                     (28)
#define SOFT_RESET1                                    0x98000000
#define SOFT_RESET1_rstn_lsadc_shift                         (26)
	/* Enable LSADC clock */
	value = rtd_inl(CLOCK_ENABLE1);
	value |= 1 << CLOCK_ENABLE1_clk_en_lsadc_shift;
	rtd_outl(CLOCK_ENABLE1, value);

	/* Release LSADC reset */
	value = rtd_inl(SOFT_RESET1);
	value |= 1 << SOFT_RESET1_rstn_lsadc_shift;
	rtd_outl(SOFT_RESET1, value);
	#endif /* CONFIG_RTD1295 | CONFIG_RTD1395 | CONFIG_RTD161x | CONFIG_RTD131x */
}

int rtk_lsadc_init(void)
{
	u32 value;

	rtk_lsadc_clk_en();

	/* init clock gating */
	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_POWER_ADDR);
	value &= ~(LSADC0_CLK_GATING_EN | LSADC1_CLK_GATING_EN);
	#if RTK_LSADC_CLK_GATING_EN
	value |= LSADC0_CLK_GATING_EN;
	#endif
	rtd_outl(LSADC_BASE_ADDR + LSADC0_POWER_ADDR, value);
	DBG("write lsadc0_power_reg = 0x%08x\n", value);

	/* init ananlog_ctrl value to 0x00000001 */
	rtd_outl(LSADC_BASE_ADDR + LSADC0_ANALOG_CTRL_ADDR, LSADC_ANALOG_CTRL_VALUE);
	DBG("write analog_ctrl_reg = 0x%08x\n", LSADC_ANALOG_CTRL_VALUE);
	mdelay(100);

	/* init LSADC0 pad0 */
	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_PAD0_ADDR);
	value &= ~(LSADC_PAD_MASK_ACTIVE | LSADC_PAD_MASK_THRESHOLD | \
		LSADC_PAD_MASK_SW | LSADC_PAD_MASK_CTRL | LSADC0_PAD_MASK_ADC_VAL);
	#if RTK_LSADC_ACTIVE
	value |= LSADC_PAD_MASK_ACTIVE;
	#endif
	#if RTK_LSADC_SW_IDX
	value |= LSADC_PAD_MASK_SW;
	#endif
	#if RTK_LSADC_CTRL_MODE
	value |= LSADC_PAD_MASK_CTRL;
	#endif
	value |= (RTK_LSADC_VOLTAGE_THRESHOLD << 16);
	rtd_outl(LSADC_BASE_ADDR + LSADC0_PAD0_ADDR, value);
	DBG("write pad0_reg = 0x%08x\n", value);

	/* init LSADC0 ctrl */
	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_CTRL_ADDR);
	value &= ~(LSADC0_CTRL_DEBOUNCE_MASK);
	value |= LSADC_CTRL_MASK_ENABLE | LSADC_CTRL_MASK_SEL_WAIT;
	value |= RTK_LSADC_DEBOUNCE_CNT;
	rtd_outl(LSADC_BASE_ADDR + LSADC0_CTRL_ADDR, value);
	DBG("write ctrl_reg = 0x%08x\n", value);

	/* init LSADC0 status */
	value = rtd_inl(LSADC_BASE_ADDR + LSADC0_STATUS_ADDR);
	value |= LSADC_STATUS_MASK_IRQ_EN;
	rtd_outl(LSADC_BASE_ADDR + LSADC0_STATUS_ADDR, value);
	DBG("write status_reg = 0x%x\n", value);
	
	DBG("LSADC0 result: ctrl_reg = 0x%08x, status_reg = 0x%08x, pad0_reg = 0x%08x\n",
		rtd_inl(LSADC_BASE_ADDR + LSADC0_CTRL_ADDR),
		rtd_inl(LSADC_BASE_ADDR + LSADC0_STATUS_ADDR),
		rtd_inl(LSADC_BASE_ADDR + LSADC0_PAD0_ADDR));

	/* init CRT LSADC PG */
	rtd_outl(LSADC_PG_ADDR, CRT_LSADC_PG_VALUE);
	DBG("write lsadc_pg_reg = 0x%08x\n", CRT_LSADC_PG_VALUE);

	return 0;
}
