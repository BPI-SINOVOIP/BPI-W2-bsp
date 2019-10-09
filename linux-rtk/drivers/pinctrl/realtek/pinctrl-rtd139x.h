/*
 * Realtek pin controller driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 */

#ifndef __PINCTRL_RTK139X_H
#define __PINCTRL_RTK139X_H

#include <linux/kernel.h>
#include <linux/pinctrl/pinctrl.h>

//#define RTK_PINCTRL_DEBUG
#ifdef RTK_PINCTRL_DEBUG
#define RTK_PINCTRL_DBG(fmt, ...) pr_info("[PINCTRL] " fmt "\n", ## __VA_ARGS__)
#else
#define RTK_PINCTRL_DBG(fmt, ...) do {} while (0)
#endif

#define RTK_PINCTRL_INF(fmt, ...) pr_info("[PINCTRL] " fmt "\n", ## __VA_ARGS__)
#define RTK_PINCTRL_ERR(fmt, ...) pr_err("[PINCTRL Error] " fmt "\n", ## __VA_ARGS__)

#define P_ISO_BASE			 0

#define RTK_PCONF_SCHM		2
#define RTK_PCONF_PULEN		1
#define RTK_PCONF_PULSEL	0
#define RTK_PCONF_CURR		-1


/* GPIO muxpad0*/
#define RTK_PINCTRL_PIN_gpio_0				PINCTRL_PIN(P_ISO_BASE + 0, "gpio_0")
#define RTK_PINCTRL_PIN_gpio_1				PINCTRL_PIN(P_ISO_BASE + 1, "gpio_1")
#define RTK_PINCTRL_PIN_gpio_2				PINCTRL_PIN(P_ISO_BASE + 2, "gpio_2")
#define RTK_PINCTRL_PIN_gpio_3				PINCTRL_PIN(P_ISO_BASE + 3, "gpio_3")
#define RTK_PINCTRL_PIN_gpio_4				PINCTRL_PIN(P_ISO_BASE + 4, "gpio_4")
#define RTK_PINCTRL_PIN_gpio_5				PINCTRL_PIN(P_ISO_BASE + 5, "gpio_5")
#define RTK_PINCTRL_PIN_gpio_6				PINCTRL_PIN(P_ISO_BASE + 6, "gpio_6")
#define RTK_PINCTRL_PIN_gpio_7				PINCTRL_PIN(P_ISO_BASE + 7, "gpio_7")
#define RTK_PINCTRL_PIN_gpio_8				PINCTRL_PIN(P_ISO_BASE + 8, "gpio_8")
#define RTK_PINCTRL_PIN_gpio_9				PINCTRL_PIN(P_ISO_BASE + 9, "gpio_9")
#define RTK_PINCTRL_PIN_gpio_10				PINCTRL_PIN(P_ISO_BASE + 10, "gpio_10")
#define RTK_PINCTRL_PIN_gpio_11				PINCTRL_PIN(P_ISO_BASE + 11, "gpio_11")

/* GPIO muxpad1*/
#define RTK_PINCTRL_PIN_gpio_12				PINCTRL_PIN(P_ISO_BASE + 12, "gpio_12")
#define RTK_PINCTRL_PIN_gpio_13				PINCTRL_PIN(P_ISO_BASE + 13, "gpio_13")
#define RTK_PINCTRL_PIN_gpio_14				PINCTRL_PIN(P_ISO_BASE + 14, "gpio_14")
#define RTK_PINCTRL_PIN_gpio_15				PINCTRL_PIN(P_ISO_BASE + 15, "gpio_15")
#define RTK_PINCTRL_PIN_gpio_16				PINCTRL_PIN(P_ISO_BASE + 16, "gpio_16")
#define RTK_PINCTRL_PIN_gpio_17				PINCTRL_PIN(P_ISO_BASE + 17, "gpio_17")
#define RTK_PINCTRL_PIN_gpio_18				PINCTRL_PIN(P_ISO_BASE + 18, "gpio_18")
#define RTK_PINCTRL_PIN_gpio_19				PINCTRL_PIN(P_ISO_BASE + 19, "gpio_19")
#define RTK_PINCTRL_PIN_gpio_20				PINCTRL_PIN(P_ISO_BASE + 20, "gpio_20")
#define RTK_PINCTRL_PIN_gpio_21				PINCTRL_PIN(P_ISO_BASE + 21, "gpio_21")
#define RTK_PINCTRL_PIN_gpio_22				PINCTRL_PIN(P_ISO_BASE + 22, "gpio_22")
#define RTK_PINCTRL_PIN_gpio_23				PINCTRL_PIN(P_ISO_BASE + 23, "gpio_23")
#define RTK_PINCTRL_PIN_usb_cc2				PINCTRL_PIN(P_ISO_BASE + 24, "usb_cc2")
#define RTK_PINCTRL_PIN_gpio_25				PINCTRL_PIN(P_ISO_BASE + 25, "gpio_25")
#define RTK_PINCTRL_PIN_gpio_26				PINCTRL_PIN(P_ISO_BASE + 26, "gpio_26")

/* GPIO muxpad2*/
#define RTK_PINCTRL_PIN_gpio_27				PINCTRL_PIN(P_ISO_BASE + 27, "gpio_27")
#define RTK_PINCTRL_PIN_gpio_28				PINCTRL_PIN(P_ISO_BASE + 28, "gpio_28")
#define RTK_PINCTRL_PIN_gpio_29				PINCTRL_PIN(P_ISO_BASE + 29, "gpio_29")
#define RTK_PINCTRL_PIN_gpio_30				PINCTRL_PIN(P_ISO_BASE + 30, "gpio_30")
#define RTK_PINCTRL_PIN_gpio_31				PINCTRL_PIN(P_ISO_BASE + 31, "gpio_31")
#define RTK_PINCTRL_PIN_gpio_32				PINCTRL_PIN(P_ISO_BASE + 32, "gpio_32")
#define RTK_PINCTRL_PIN_gpio_33				PINCTRL_PIN(P_ISO_BASE + 33, "gpio_33")
#define RTK_PINCTRL_PIN_gpio_34				PINCTRL_PIN(P_ISO_BASE + 34, "gpio_34")
#define RTK_PINCTRL_PIN_gpio_35				PINCTRL_PIN(P_ISO_BASE + 35, "gpio_35")
#define RTK_PINCTRL_PIN_gpio_36				PINCTRL_PIN(P_ISO_BASE + 36, "gpio_36")
#define RTK_PINCTRL_PIN_gpio_37				PINCTRL_PIN(P_ISO_BASE + 37, "gpio_37")
#define RTK_PINCTRL_PIN_gpio_38				PINCTRL_PIN(P_ISO_BASE + 38, "gpio_38")

/* GPIO muxpad3*/
#define RTK_PINCTRL_PIN_gpio_39				PINCTRL_PIN(P_ISO_BASE + 39, "gpio_39")
#define RTK_PINCTRL_PIN_gpio_40				PINCTRL_PIN(P_ISO_BASE + 40, "gpio_40")
#define RTK_PINCTRL_PIN_gpio_41				PINCTRL_PIN(P_ISO_BASE + 41, "gpio_41")
#define RTK_PINCTRL_PIN_gpio_42				PINCTRL_PIN(P_ISO_BASE + 42, "gpio_42")
#define RTK_PINCTRL_PIN_gpio_43				PINCTRL_PIN(P_ISO_BASE + 43, "gpio_43")
#define RTK_PINCTRL_PIN_gpio_44				PINCTRL_PIN(P_ISO_BASE + 44, "gpio_44")
#define RTK_PINCTRL_PIN_gpio_45				PINCTRL_PIN(P_ISO_BASE + 45, "gpio_45")
#define RTK_PINCTRL_PIN_gpio_46				PINCTRL_PIN(P_ISO_BASE + 46, "gpio_46")
#define RTK_PINCTRL_PIN_gpio_47				PINCTRL_PIN(P_ISO_BASE + 47, "gpio_47")
#define RTK_PINCTRL_PIN_gpio_48				PINCTRL_PIN(P_ISO_BASE + 48, "gpio_48")
#define RTK_PINCTRL_PIN_gpio_49				PINCTRL_PIN(P_ISO_BASE + 49, "gpio_49")
#define RTK_PINCTRL_PIN_gpio_50				PINCTRL_PIN(P_ISO_BASE + 50, "gpio_50")

/*EMMC muxpad4*/
#define RTK_PINCTRL_PIN_emmc_rst_n			PINCTRL_PIN(P_ISO_BASE + 61, "emmc_rst_n")
#define RTK_PINCTRL_PIN_emmc_dd_sb			PINCTRL_PIN(P_ISO_BASE + 62, "emmc_dd_sb")
#define RTK_PINCTRL_PIN_emmc_clk			PINCTRL_PIN(P_ISO_BASE + 63, "emmc_clk")
#define RTK_PINCTRL_PIN_emmc_cmd			PINCTRL_PIN(P_ISO_BASE + 64, "emmc_cmd")
#define RTK_PINCTRL_PIN_emmc_data_0			PINCTRL_PIN(P_ISO_BASE + 65, "emmc_data_0")
#define RTK_PINCTRL_PIN_emmc_data_1			PINCTRL_PIN(P_ISO_BASE + 66, "emmc_data_1")
#define RTK_PINCTRL_PIN_emmc_data_2			PINCTRL_PIN(P_ISO_BASE + 67, "emmc_data_2")
#define RTK_PINCTRL_PIN_emmc_data_3			PINCTRL_PIN(P_ISO_BASE + 68, "emmc_data_3")
#define RTK_PINCTRL_PIN_emmc_data_4			PINCTRL_PIN(P_ISO_BASE + 69, "emmc_data_4")
#define RTK_PINCTRL_PIN_emmc_data_5			PINCTRL_PIN(P_ISO_BASE + 70, "emmc_data_5")
#define RTK_PINCTRL_PIN_emmc_data_6			PINCTRL_PIN(P_ISO_BASE + 71, "emmc_data_6")
#define RTK_PINCTRL_PIN_emmc_data_7			PINCTRL_PIN(P_ISO_BASE + 72, "emmc_data_7")

/*muxpad5*/
#define RTK_PINCTRL_PIN_spi_ce_n			PINCTRL_PIN(P_ISO_BASE + 57, "spi_ce_n")
#define RTK_PINCTRL_PIN_spi_sck				PINCTRL_PIN(P_ISO_BASE + 58, "spi_sck")
#define RTK_PINCTRL_PIN_spi_so				PINCTRL_PIN(P_ISO_BASE + 59, "spi_so")
#define RTK_PINCTRL_PIN_spi_si				PINCTRL_PIN(P_ISO_BASE + 60, "spi_si")
#define RTK_PINCTRL_PIN_usb_cc1				PINCTRL_PIN(P_ISO_BASE + 51, "usb_cc1")
#define RTK_PINCTRL_PIN_prob_0				PINCTRL_PIN(P_ISO_BASE + 52, "prob_0")
#define RTK_PINCTRL_PIN_prob_1				PINCTRL_PIN(P_ISO_BASE + 53, "prob_1")
#define RTK_PINCTRL_PIN_ir_rx				PINCTRL_PIN(P_ISO_BASE + 54, "ir_rx")
#define RTK_PINCTRL_PIN_ur0_rx				PINCTRL_PIN(P_ISO_BASE + 55, "ur0_rx")
#define RTK_PINCTRL_PIN_ur0_tx				PINCTRL_PIN(P_ISO_BASE + 56, "ur0_tx")

/*muxpad6*/
#define RTK_PINCTRL_PIN_ur2_loc				PINCTRL_PIN(P_ISO_BASE + 73, "ur2_loc")
#define RTK_PINCTRL_PIN_gspi_loc			PINCTRL_PIN(P_ISO_BASE + 74, "gspi_loc")
#define RTK_PINCTRL_PIN_sdio_loc			PINCTRL_PIN(P_ISO_BASE + 75, "sdio_loc")
#define RTK_PINCTRL_PIN_hi_loc				PINCTRL_PIN(P_ISO_BASE + 76, "hi_loc")
#define RTK_PINCTRL_PIN_hi_width			PINCTRL_PIN(P_ISO_BASE + 77, "hi_width")
#define RTK_PINCTRL_PIN_debug_p2s_enable		PINCTRL_PIN(P_ISO_BASE + 78, "debug_p2s_enable")
#define RTK_PINCTRL_PIN_sf_en				PINCTRL_PIN(P_ISO_BASE + 79, "sf_en")
#define RTK_PINCTRL_PIN_arm_trace_dbg_en		PINCTRL_PIN(P_ISO_BASE + 80, "arm_trace_dbg_en")
#define RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc0	PINCTRL_PIN(P_ISO_BASE + 81, "pwm_01_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc0	PINCTRL_PIN(P_ISO_BASE + 82, "pwm_23_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc1	PINCTRL_PIN(P_ISO_BASE + 83, "pwm_01_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc1	PINCTRL_PIN(P_ISO_BASE + 84, "pwm_23_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_ejtag_avcpu_loc			PINCTRL_PIN(P_ISO_BASE + 85, "ejtag_avcpu_loc")
#define RTK_PINCTRL_PIN_ejtag_scpu_loc			PINCTRL_PIN(P_ISO_BASE + 86, "ejtag_scpu_loc")


enum PMUX_BASE_TYPE {
	PMUX_BASE_SB2,
	PMUX_BASE_DISP,
	PMUX_BASE_CR,
	PMUX_BASE_ISO
};

struct rtk_pin_regmap {
	u8 pmux_base;
	u16 pmux_regoff;
	u16 pmux_regbit;
	u16 pmux_regbitmsk;
	u16 pcof_regoff;
	u16 pcof_regbit;
	u16 pcof_cur_strgh;/*0 : 2&4mA   1:4&8mA*/
};

struct rtk_pinmux_reg {
	u8 reg_base;
	u16 reg_offset;
};

#define PADDRI_4_8 1
#define PADDRI_2_4 0
#define PADDRI_UNSUPPORT 0xFFFF

#define PCOF_UNSUPPORT 0xFFFF
#define PMUX_UNSUPPORT 0xFFFF

static const struct rtk_pinmux_reg pinmux_reg_list[] = {
	/* muxpad*/
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x000},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x004},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x008},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x00c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x010},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x014},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x018},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x01c},
	/*ISO  pfunc*/
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x020},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x024},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x028},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x02c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x030},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x034},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x038},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x03c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x040},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x044},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x048},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x04c},
	/*emmc pfunc*/
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x050},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x054},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x058},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x05c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x060},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x064},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x068},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x06c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x070},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x074},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x078},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x07c},
};

static const struct rtk_pin_regmap pin_regmap[] = {
	/*GPIO*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 0, "gpio_0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 1, "gpio_1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 4, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 2, "gpio_2")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 7, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 3, "gpio_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 10, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 4, "gpio_4")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 13, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 5, "gpio_5")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 16, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 6, "gpio_6")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 19, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 7, "gpio_7")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 8, "gpio_8")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 23, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 9, "gpio_9")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 10, "gpio_10")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 11, "gpio_11")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 12, "gpio_12")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 13, "gpio_13")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 14, "gpio_14")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 15, "gpio_15")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 16, "gpio_16")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 17, "gpio_17")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 18, "gpio_18")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 19, "gpio_19")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 16, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 20, "gpio_20")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 19, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 21, "gpio_21")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 22, "gpio_22")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 23, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 23, "gpio_23")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 24, "usb_cc2")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 25, "gpio_25")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 26, "gpio_26")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 27, "gpio_27")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 28, "gpio_28")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 29, "gpio_29")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 9, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 30, "gpio_30")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 11, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 31, "gpio_31")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 13, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x034, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 32, "gpio_32")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 16, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x034, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 33, "gpio_33")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 19, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x034, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 34, "gpio_34")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x034, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 35, "gpio_35")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 23, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x038, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 36, "gpio_36")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 26, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x038, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 37, "gpio_37")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 29, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x03c, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 38, "gpio_38")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x03c, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 39, "gpio_39")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 3, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x040, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 40, "gpio_40")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 5, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x040, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 41, "gpio_41")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 7, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x044, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 42, "gpio_42")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 9, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x044, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 43, "gpio_43")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 11, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x048, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 44, "gpio_44")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 13, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x048, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 45, "gpio_45")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x04c, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 46, "gpio_46")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x04c, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 47, "gpio_47")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x04c, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 48, "gpio_48")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x04c, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 49, "gpio_49")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00c, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x04c, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 50, "gpio_50")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 51, "usb_cc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x070, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 52, "prob_0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x070, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 53, "prob_1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x070, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 54, "ir_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x070, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 55, "ur0_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x070, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 56, "ur0_tx")*/
	/*SPI*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x068, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 57, "spi_ce_n")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x068, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 58, "spi_sck")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x06c, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 59, "spi_so")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x014, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x06c, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 60, "spi_si")*/
	/*MMC*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x050, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 61, "emmc_rst_n")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x050, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 62, "emmc_dd_sb")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x054, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 63, "emmc_clk")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x054, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 64, "emmc_cmd")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x058, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 65, "emmc_data_0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x058, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 66, "emmc_data_1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x05c, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 67, "emmc_data_2")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x05c, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 68, "emmc_data_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x060, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 69, "emmc_data_4")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x060, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 70, "emmc_data_5")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x064, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 71, "emmc_data_6")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x064, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 72, "emmc_data_7")*/
	/*OTHERS*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 73, "ur2_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 74, "gspi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 75, "sdio_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 76, "hi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 77, "hi_width")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 10, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 78, "debug_p2s_enable")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 11, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 79, "sf_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 12, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 80, "arm_trace_dbg_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 13, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 81, "pwm_01_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 14, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 82, "pwm_23_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 15, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 83, "pwm_01_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 16, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 84, "pwm_23_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 17, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 85, "ejtag_avcpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x018, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 86, "ejtag_scpu_loc")*/
};


struct RTK_desc_function {
	const char	*name;
	u8		muxval;
};

struct RTK_desc_pin {
	struct pinctrl_pin_desc		pin;
	struct RTK_desc_function	*functions;
};

struct RTK_pinctrl_desc {
	const struct RTK_desc_pin	*pins;
	int				npins;
	struct pinctrl_gpio_range	*ranges;
	int				nranges;
};

struct RTK_pinctrl_function {
	const char	*name;
	const char	**groups;
	unsigned int	ngroups;
};

struct RTK_pinctrl_group {
	const char	*name;
	unsigned long	config;
	unsigned int	pin;
};

struct RTK_pinctrl {
/*
 *	void __iomem			*sb2_membase;
 *	void __iomem			*disp_membase;
 *	void __iomem			*cr_membase;
 *	void __iomem			*iso_membase;
 *	struct gpio_chip		*chip;
 */
	void __iomem			*iso_membase;
	struct RTK_pinctrl_desc	*desc;
	struct device			*dev;
	struct RTK_pinctrl_function	*functions;
	unsigned int			nfunctions;
	struct RTK_pinctrl_group	*groups;
	unsigned int			ngroups;
	struct pinctrl_dev		*pctl_dev;
};

#define RTK_PIN(_pin, ...)					\
	{							\
		.pin = _pin,					\
		.functions = (struct RTK_desc_function[]){	\
			__VA_ARGS__, { } },			\
	}

#define RTK_FUNCTION(_val, _name)				\
	{							\
		.name = _name,					\
		.muxval = _val,					\
	}


static const struct RTK_desc_pin rtk_pins[] = {
	/*GPIO*/
	RTK_PIN(RTK_PINCTRL_PIN_gpio_0,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_1,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "standby_dbg"),
		RTK_FUNCTION(0x2, "ao"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "standby_dbg"),
		RTK_FUNCTION(0x2, "ao"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "ao"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "ao"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x7, "ai")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_7,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_8,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "tp0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_9,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "tp0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_10,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "tp0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_11,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "tp0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_12,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c0"),
		RTK_FUNCTION(0x2, "pwm0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_13,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c0"),
		RTK_FUNCTION(0x2, "pwm1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_14,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "etn_led"),
		RTK_FUNCTION(0x2, "pwm2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_15,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "etn_led"),
		RTK_FUNCTION(0x2, "pwm3")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_16,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_17,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_18,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc0"),
		RTK_FUNCTION(0x3, "sc_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_19,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc0"),
		RTK_FUNCTION(0x3, "sc_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_20,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc0"),
		RTK_FUNCTION(0x3, "sc_loc0"),
		RTK_FUNCTION(0x4, "pwm0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_21,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_22,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_23,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm3")),
	RTK_PIN(RTK_PINCTRL_PIN_usb_cc2,
		RTK_FUNCTION(0x0, "usb_cc2"),
		RTK_FUNCTION(0x1, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_25,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "gspi_loc1"),
		RTK_FUNCTION(0x2, "uart2_loc1"),
		RTK_FUNCTION(0x3, "rtc")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_26,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "gspi_loc1"),
		RTK_FUNCTION(0x2, "uart2_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_27,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "gspi_loc1"),
		RTK_FUNCTION(0x2, "uart2_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_28,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "gspi_loc1"),
		RTK_FUNCTION(0x2, "uart2_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_29,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "gphy"),
		RTK_FUNCTION(0x4, "extphy")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_30,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_31,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc0"),
		RTK_FUNCTION(0x3, "sc_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_32,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_33,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_34,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_35,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_36,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc1"),
		RTK_FUNCTION(0x5, "tp1"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_37,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc1"),
		RTK_FUNCTION(0x5, "tp1"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_38,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x5, "tp1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_39,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "mmc"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc1"),
		RTK_FUNCTION(0x5, "tp1"),
		RTK_FUNCTION(0x6, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_40,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_41,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_42,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_43,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_44,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_45,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_46,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie"),
		RTK_FUNCTION(0x3, "gphy"),
		RTK_FUNCTION(0x4, "extphy")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_47,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "dc_fan_sensor")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_48,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "prob_2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_49,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "prob_3")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_50,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif"),
		RTK_FUNCTION(0x2, "test_loop_dis")),
	RTK_PIN(RTK_PINCTRL_PIN_usb_cc1,
		RTK_FUNCTION(0x0, "usb_cc1"),
		RTK_FUNCTION(0x1, "gpio")), /*gpio51*/
	RTK_PIN(RTK_PINCTRL_PIN_prob_0,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio52*/
		RTK_FUNCTION(0x1, "prob_0"),
		RTK_FUNCTION(0x2, "p2s")),
	RTK_PIN(RTK_PINCTRL_PIN_prob_1,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio53*/
		RTK_FUNCTION(0x1, "prob_1"),
		RTK_FUNCTION(0x2, "p2s")),
	RTK_PIN(RTK_PINCTRL_PIN_ir_rx,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio54*/
		RTK_FUNCTION(0x1, "ir_rx"),
		RTK_FUNCTION(0x2, "standby_dbg")),
	RTK_PIN(RTK_PINCTRL_PIN_ur0_rx,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio55*/
		RTK_FUNCTION(0x1, "uart0")),
	RTK_PIN(RTK_PINCTRL_PIN_ur0_tx,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio56*/
		RTK_FUNCTION(0x1, "uart0")),
	/*SPI*/
	RTK_PIN(RTK_PINCTRL_PIN_spi_ce_n,
		RTK_FUNCTION(0x0, "spi"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "i2c5")),
	RTK_PIN(RTK_PINCTRL_PIN_spi_sck,
		RTK_FUNCTION(0x0, "spi"),
		RTK_FUNCTION(0x1, "nand")),
	RTK_PIN(RTK_PINCTRL_PIN_spi_so,
		RTK_FUNCTION(0x0, "spi"),
		RTK_FUNCTION(0x1, "nand")),
	RTK_PIN(RTK_PINCTRL_PIN_spi_si,
		RTK_FUNCTION(0x0, "spi"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "i2c5")),
	/*MMC*/
	RTK_PIN(RTK_PINCTRL_PIN_emmc_rst_n,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_dd_sb,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_clk,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_cmd,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_0,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_1,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_2,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_3,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_4,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_5,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_6,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_7,
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	/*OTHERS*/
	RTK_PIN(RTK_PINCTRL_PIN_ur2_loc,
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "uart2_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gspi_loc,
		RTK_FUNCTION(0x1, "gspi_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_sdio_loc,
		RTK_FUNCTION(0x1, "sdio_loc0"),
		RTK_FUNCTION(0x2, "sdio_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_hi_loc,
		RTK_FUNCTION(0x0, "hi_loc_disable"),
		RTK_FUNCTION(0x1, "hi_loc0"),
		RTK_FUNCTION(0x2, "hi_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_hi_width,
		RTK_FUNCTION(0x0, "hi_width_disable"),
		RTK_FUNCTION(0x1, "hi_width_1bit"),
		RTK_FUNCTION(0x2, "hi_width_8bit"),
		RTK_FUNCTION(0x3, "hi_width_16bit")),
	RTK_PIN(RTK_PINCTRL_PIN_debug_p2s_enable,
		RTK_FUNCTION(0x0, "p2s_disable"),
		RTK_FUNCTION(0x1, "p2s_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_sf_en,
		RTK_FUNCTION(0x0, "sf_disable"),
		RTK_FUNCTION(0x1, "sf_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_arm_trace_dbg_en,
		RTK_FUNCTION(0x0, "arm_trace_debug_disable"),
		RTK_FUNCTION(0x1, "arm_trace_debug_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc0,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc0,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc1,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc1,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_ejtag_avcpu_loc,
		RTK_FUNCTION(0x1, "acpu_ejtag_loc0"),
		RTK_FUNCTION(0x2, "acpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_ejtag_scpu_loc,
		RTK_FUNCTION(0x1, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc1")),
};

void gpio_pinctrl_control(struct gpio_chip *gc, int gpio, int direction, int value);

#endif /* __PINCTRL_RTK139X_H */
