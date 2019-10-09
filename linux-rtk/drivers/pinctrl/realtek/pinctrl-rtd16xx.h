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

#ifndef __PINCTRL_RTK16xx_H
#define __PINCTRL_RTK16xx_H

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
#define RTK_PCONF_PULEN		0
#define RTK_PCONF_PULSEL	1
#define RTK_PCONF_CURR		-1


/* ISO muxpad0*/
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
#define RTK_PINCTRL_PIN_gpio_12				PINCTRL_PIN(P_ISO_BASE + 12, "gpio_12")
#define RTK_PINCTRL_PIN_gpio_13				PINCTRL_PIN(P_ISO_BASE + 13, "gpio_13")
#define RTK_PINCTRL_PIN_gpio_14				PINCTRL_PIN(P_ISO_BASE + 14, "gpio_14")
#define RTK_PINCTRL_PIN_gpio_15				PINCTRL_PIN(P_ISO_BASE + 15, "gpio_15")
#define RTK_PINCTRL_PIN_gpio_16				PINCTRL_PIN(P_ISO_BASE + 16, "gpio_16")
#define RTK_PINCTRL_PIN_gpio_17				PINCTRL_PIN(P_ISO_BASE + 17, "gpio_17")

/* ISO muxpad1*/
#define RTK_PINCTRL_PIN_gpio_18				PINCTRL_PIN(P_ISO_BASE + 18, "gpio_18")
#define RTK_PINCTRL_PIN_gpio_19				PINCTRL_PIN(P_ISO_BASE + 19, "gpio_19")
#define RTK_PINCTRL_PIN_gpio_20				PINCTRL_PIN(P_ISO_BASE + 20, "gpio_20")
#define RTK_PINCTRL_PIN_gpio_21				PINCTRL_PIN(P_ISO_BASE + 21, "gpio_21")
#define RTK_PINCTRL_PIN_gpio_22				PINCTRL_PIN(P_ISO_BASE + 22, "gpio_22")
#define RTK_PINCTRL_PIN_gpio_23				PINCTRL_PIN(P_ISO_BASE + 23, "gpio_23")
#define RTK_PINCTRL_PIN_gpio_25				PINCTRL_PIN(P_ISO_BASE + 25, "gpio_25")
#define RTK_PINCTRL_PIN_gpio_26				PINCTRL_PIN(P_ISO_BASE + 26, "gpio_26")
#define RTK_PINCTRL_PIN_gpio_27				PINCTRL_PIN(P_ISO_BASE + 27, "gpio_27")
#define RTK_PINCTRL_PIN_gpio_28				PINCTRL_PIN(P_ISO_BASE + 28, "gpio_28")
#define RTK_PINCTRL_PIN_gpio_29				PINCTRL_PIN(P_ISO_BASE + 29, "gpio_29")
#define RTK_PINCTRL_PIN_gpio_30				PINCTRL_PIN(P_ISO_BASE + 30, "gpio_30")
#define RTK_PINCTRL_PIN_gpio_31				PINCTRL_PIN(P_ISO_BASE + 31, "gpio_31")
#define RTK_PINCTRL_PIN_gpio_34				PINCTRL_PIN(P_ISO_BASE + 34, "gpio_34")
#define RTK_PINCTRL_PIN_gpio_35				PINCTRL_PIN(P_ISO_BASE + 35, "gpio_35")


/* ISO muxpad2*/
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
#define RTK_PINCTRL_PIN_gpio_51				PINCTRL_PIN(P_ISO_BASE + 51, "gpio_51")

/* ISO muxpad3*/
#define RTK_PINCTRL_PIN_gpio_52				PINCTRL_PIN(P_ISO_BASE + 52, "gpio_52")
#define RTK_PINCTRL_PIN_ir_rx				PINCTRL_PIN(P_ISO_BASE + 53, "ir_rx")
#define RTK_PINCTRL_PIN_ur0_rx				PINCTRL_PIN(P_ISO_BASE + 54, "ur0_rx")
#define RTK_PINCTRL_PIN_ur0_tx				PINCTRL_PIN(P_ISO_BASE + 55, "ur0_tx")
#define RTK_PINCTRL_PIN_gpio_57				PINCTRL_PIN(P_ISO_BASE + 57, "gpio_57")
#define RTK_PINCTRL_PIN_gpio_58				PINCTRL_PIN(P_ISO_BASE + 58, "gpio_58")
#define RTK_PINCTRL_PIN_gpio_59				PINCTRL_PIN(P_ISO_BASE + 59, "gpio_59")
#define RTK_PINCTRL_PIN_gpio_60				PINCTRL_PIN(P_ISO_BASE + 60, "gpio_60")
#define RTK_PINCTRL_PIN_gpio_61				PINCTRL_PIN(P_ISO_BASE + 61, "gpio_61")
#define RTK_PINCTRL_PIN_gpio_62				PINCTRL_PIN(P_ISO_BASE + 62, "gpio_62")
#define RTK_PINCTRL_PIN_gpio_63				PINCTRL_PIN(P_ISO_BASE + 63, "gpio_63")
#define RTK_PINCTRL_PIN_gpio_64				PINCTRL_PIN(P_ISO_BASE + 64, "gpio_64")
#define RTK_PINCTRL_PIN_gpio_65				PINCTRL_PIN(P_ISO_BASE + 65, "gpio_65")
#define RTK_PINCTRL_PIN_gpio_66				PINCTRL_PIN(P_ISO_BASE + 66, "gpio_66")
#define RTK_PINCTRL_PIN_gpio_67				PINCTRL_PIN(P_ISO_BASE + 67, "gpio_67")
#define RTK_PINCTRL_PIN_gpio_68				PINCTRL_PIN(P_ISO_BASE + 68, "gpio_68")
#define RTK_PINCTRL_PIN_gpio_85				PINCTRL_PIN(P_ISO_BASE + 85, "gpio_85")

/* ISO muxpad4*/
#define RTK_PINCTRL_PIN_usb_cc1				PINCTRL_PIN(P_ISO_BASE + 56, "usb_cc1")
#define RTK_PINCTRL_PIN_usb_cc2				PINCTRL_PIN(P_ISO_BASE + 69, "usb_cc2")


/*ISO muxpad6*/
#define RTK_PINCTRL_PIN_ur2_loc				PINCTRL_PIN(P_ISO_BASE + 86, "ur2_loc")
#define RTK_PINCTRL_PIN_gspi_loc			PINCTRL_PIN(P_ISO_BASE + 87, "gspi_loc")
#define RTK_PINCTRL_PIN_sdio_loc			PINCTRL_PIN(P_ISO_BASE + 88, "sdio_loc")
#define RTK_PINCTRL_PIN_hi_loc				PINCTRL_PIN(P_ISO_BASE + 89, "hi_loc")
#define RTK_PINCTRL_PIN_hi_width			PINCTRL_PIN(P_ISO_BASE + 90, "hi_width")
#define RTK_PINCTRL_PIN_debug_p2s_enable		PINCTRL_PIN(P_ISO_BASE + 91, "debug_p2s_enable")
#define RTK_PINCTRL_PIN_sf_en				PINCTRL_PIN(P_ISO_BASE + 92, "sf_en")
#define RTK_PINCTRL_PIN_arm_trace_dbg_en		PINCTRL_PIN(P_ISO_BASE + 93, "arm_trace_dbg_en")
#define RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc0	PINCTRL_PIN(P_ISO_BASE + 94, "pwm_01_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc0	PINCTRL_PIN(P_ISO_BASE + 95, "pwm_23_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_pwm_01_open_drain_en_loc1	PINCTRL_PIN(P_ISO_BASE + 96, "pwm_01_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_pwm_23_open_drain_en_loc1	PINCTRL_PIN(P_ISO_BASE + 97, "pwm_23_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_ejtag_avcpu_loc			PINCTRL_PIN(P_ISO_BASE + 98, "ejtag_avcpu_loc")
#define RTK_PINCTRL_PIN_ejtag_scpu_loc			PINCTRL_PIN(P_ISO_BASE + 99, "ejtag_scpu_loc")
#define RTK_PINCTRL_PIN_i2c_tg				PINCTRL_PIN(P_ISO_BASE + 100, "i2c_tg")
#define RTK_PINCTRL_PIN_dmic_loc			PINCTRL_PIN(P_ISO_BASE + 101, "dmic_loc")

/*MISC muxpad0*/
#define RTK_PINCTRL_PIN_demod_agc			PINCTRL_PIN(P_ISO_BASE + 24, "demod_agc")
#define RTK_PINCTRL_PIN_emmc_rst			PINCTRL_PIN(P_ISO_BASE + 102, "emmc_rst")
#define RTK_PINCTRL_PIN_emmc_dd_sb			PINCTRL_PIN(P_ISO_BASE + 103, "emmc_dd_sb")
#define RTK_PINCTRL_PIN_emmc_clk			PINCTRL_PIN(P_ISO_BASE + 104, "emmc_clk")
#define RTK_PINCTRL_PIN_emmc_cmd			PINCTRL_PIN(P_ISO_BASE + 105, "emmc_cmd")
#define RTK_PINCTRL_PIN_emmc_data_0			PINCTRL_PIN(P_ISO_BASE + 106, "emmc_data_0")
#define RTK_PINCTRL_PIN_emmc_data_1			PINCTRL_PIN(P_ISO_BASE + 107, "emmc_data_1")
#define RTK_PINCTRL_PIN_emmc_data_2			PINCTRL_PIN(P_ISO_BASE + 108, "emmc_data_2")
#define RTK_PINCTRL_PIN_emmc_data_3			PINCTRL_PIN(P_ISO_BASE + 109, "emmc_data_3")
#define RTK_PINCTRL_PIN_emmc_data_4			PINCTRL_PIN(P_ISO_BASE + 110, "emmc_data_4")
#define RTK_PINCTRL_PIN_emmc_data_5			PINCTRL_PIN(P_ISO_BASE + 111, "emmc_data_5")
#define RTK_PINCTRL_PIN_emmc_data_6			PINCTRL_PIN(P_ISO_BASE + 112, "emmc_data_6")
#define RTK_PINCTRL_PIN_emmc_data_7			PINCTRL_PIN(P_ISO_BASE + 113, "emmc_data_7")
#define RTK_PINCTRL_PIN_hif_data_0			PINCTRL_PIN(P_ISO_BASE + 81, "hif_data_0")
#define RTK_PINCTRL_PIN_hif_rdy				PINCTRL_PIN(P_ISO_BASE + 82, "hif_rdy")
#define RTK_PINCTRL_PIN_hif_clk				PINCTRL_PIN(P_ISO_BASE + 83, "hif_clk")

/*MISC muxpad1*/
#define RTK_PINCTRL_PIN_hif_en				PINCTRL_PIN(P_ISO_BASE + 84, "hif_en")
#define RTK_PINCTRL_PIN_sd3_cmd				PINCTRL_PIN(P_ISO_BASE + 32, "sd3_cmd")
#define RTK_PINCTRL_PIN_sd3_clk				PINCTRL_PIN(P_ISO_BASE + 33, "sd3_clk")
#define RTK_PINCTRL_PIN_sd3_data_0			PINCTRL_PIN(P_ISO_BASE + 36, "sd3_data_0")
#define RTK_PINCTRL_PIN_sd3_data_1			PINCTRL_PIN(P_ISO_BASE + 37, "sd3_data_1")
#define RTK_PINCTRL_PIN_sd3_data_2			PINCTRL_PIN(P_ISO_BASE + 38, "sd3_data_2")
#define RTK_PINCTRL_PIN_sd3_data_3			PINCTRL_PIN(P_ISO_BASE + 39, "sd3_data_3")
#define RTK_PINCTRL_PIN_tp_sync				PINCTRL_PIN(P_ISO_BASE + 70, "tp_sync")
#define RTK_PINCTRL_PIN_tp_valid			PINCTRL_PIN(P_ISO_BASE + 71, "tp_valid")
#define RTK_PINCTRL_PIN_tp_clk				PINCTRL_PIN(P_ISO_BASE + 72, "tp_clk")
#define RTK_PINCTRL_PIN_tp_data_0			PINCTRL_PIN(P_ISO_BASE + 73, "tp_data_0")


/*MISC muxpad2*/
#define RTK_PINCTRL_PIN_tp_data_1			PINCTRL_PIN(P_ISO_BASE + 74, "tp_data_1")
#define RTK_PINCTRL_PIN_tp_data_2			PINCTRL_PIN(P_ISO_BASE + 75, "tp_data_2")
#define RTK_PINCTRL_PIN_tp_data_3			PINCTRL_PIN(P_ISO_BASE + 76, "tp_data_3")
#define RTK_PINCTRL_PIN_tp_data_4			PINCTRL_PIN(P_ISO_BASE + 77, "tp_data_4")
#define RTK_PINCTRL_PIN_tp_data_5			PINCTRL_PIN(P_ISO_BASE + 78, "tp_data_5")
#define RTK_PINCTRL_PIN_tp_data_6			PINCTRL_PIN(P_ISO_BASE + 79, "tp_data_6")
#define RTK_PINCTRL_PIN_tp_data_7			PINCTRL_PIN(P_ISO_BASE + 80, "tp_data_7")



enum PMUX_BASE_TYPE {
	PMUX_BASE_ISO,
	PMUX_BASE_MISC
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
#define PMUX_UNSUPPORT 0xFF

static const struct rtk_pinmux_reg pinmux_reg_list[] = {
	/*ISO muxpad*/
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x000},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x004},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x008},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x00c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x010},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x048},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x04C},
	/*ISO  pfunc*/
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x014},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x018},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x01C},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x020},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x024},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x028},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x02C},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x030},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x034},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x038},
	/*MISC muxpad*/
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x000},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x004},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x008},
	/*MISC  pfunc*/
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x00C},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x010},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x014},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x018},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x01C},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x020},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x024},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x028},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x02C},
	{.reg_base = PMUX_BASE_MISC, .reg_offset = 0x030},
};

static const struct rtk_pin_regmap pin_regmap[] = {
	/*GPIO*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 0, "gpio_0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 1, "gpio_1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  2, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 2, "gpio_2")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  5, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 3, "gpio_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  8, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 4, "gpio_4")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 11, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 5, "gpio_5")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 14, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 6, "gpio_6")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 17, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 7, "gpio_7")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 18, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 8, "gpio_8")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 19, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 9, "gpio_9")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 20, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 10, "gpio_10")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 21, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 11, "gpio_11")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 12, "gpio_12")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 13, "gpio_13")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 14, "gpio_14")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 15, "gpio_15")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 30, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 16, "gpio_16")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 31, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 17, "gpio_17")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 18, "gpio_18")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 19, "gpio_19")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 20, "gpio_20")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 21, "gpio_21")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 22, "gpio_22")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 23, "gpio_23")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x00C, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 24, "demod_agc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 10, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 25, "gpio_25")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 13, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 26, "gpio_26")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 16, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 27, "gpio_27")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 19, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 28, "gpio_28")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 22, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 29, "gpio_29")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 25, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x020, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 30, "gpio_30")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 26, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x020, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 31, "gpio_31")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 32, "sd3_cmd")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 33, "sd3_clk")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 34, "gpio_34")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 35, "gpio_35")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 36, "sd3_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x010, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 37, "sd3_data_1")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 15, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x010, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 38, "sd3_data_2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 17, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 39, "sd3_data_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 40, "gpio_40")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 41, "gpio_41")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 26, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 42, "gpio_42")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 43, "gpio_43")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 44, "gpio_44")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 45, "gpio_45")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x02C, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 46, "gpio_46")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 47, "gpio_47")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 23, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x02C, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 48, "gpio_48")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 24, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x02C, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 49, "gpio_49")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 50, "gpio_50")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 27, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x02C, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 51, "gpio_51")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 52, "gpio_52")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  3, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 3, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 53, "ir_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  5, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x030, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 54, "ur0_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  6, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x030, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 55, "ur0_tx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 56, "usb_cc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  7, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 57, "gpio_57")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 58, "gpio_58")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 59, "gpio_59")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 60, "gpio_60")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 31, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 61, "gpio_61")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 21, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x034, .pcof_regbit = 3, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 62, "gpio_62")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 24, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 63, "gpio_63")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 25, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 64, "gpio_64")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x034, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 65, "gpio_65")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 28, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 66, "gpio_66")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 29, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 67, "gpio_67")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 30, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 68, "gpio_68")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 69, "usb_cc2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 20, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 70, "tp_sync")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 23, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 71, "tp_valid")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 26, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 72, "tp_clk")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x014, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 73, "tp_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 74, "tp_data_1")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 75, "tp_data_2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 76, "tp_data_3")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 77, "tp_data_4")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 78, "tp_data_5")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 79, "tp_data_6")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 80, "tp_data_7")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 81, "hif_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 82, "hif_rdy")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 83, "hif_clk")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 84, "hif_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 31, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x038, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_4_8}, /*(P_ISO_BASE + 85, "gpio_85")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  0, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 86, "ur2_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  2, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 87, "gspi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  4, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 88, "sdio_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  6, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 89, "hi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  8, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 90, "hi_width")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 10, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 91, "debug_p2s_enable")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 11, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 92, "sf_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 12, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 93, "arm_trace_dbg_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 13, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 94, "pwm_01_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 14, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 95, "pwm_23_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 15, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 96, "pwm_01_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 16, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 97, "pwm_23_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 17, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 98, "ejtag_avcpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 99, "ejtag_scpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 23, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 100, "ejtag_scpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 101, "i2c_tg")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  1, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 102, "emmc_rst")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  3, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 103, "emmc_dd_sb")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  5, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 104, "emmc_clk")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  7, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 105, "emmc_cmd")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  9, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 106, "emmc_data_0")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 11, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 107, "emmc_data_1")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 13, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 108, "emmc_data_2")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 15, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 109, "emmc_data_3")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 17, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 110, "emmc_data_4")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 19, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 111, "emmc_data_5")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 112, "emmc_data_6")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 23, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 113, "emmc_data_7")*/
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
	void __iomem			*misc_membase;
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
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "standby_dbg"),
		RTK_FUNCTION(0x3, "gspi_loc0"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc0"),
		RTK_FUNCTION(0x7, "vfd")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "standby_dbg"),
		RTK_FUNCTION(0x3, "gspi_loc0"),
		RTK_FUNCTION(0x4, "scan_debug"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc0"),
		RTK_FUNCTION(0x7, "vfd")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x3, "gspi_loc0"),
		RTK_FUNCTION(0x4, "scan_debug"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc0"),
		RTK_FUNCTION(0x7, "vfd")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "i2c5"),
		RTK_FUNCTION(0x3, "gspi_loc0"),
		RTK_FUNCTION(0x4, "scan_debug"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "i2c5"),
		RTK_FUNCTION(0x4, "scan_debug"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_7,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_8,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_9,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_10,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_11,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
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
		RTK_FUNCTION(0x1, "i2c2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_19,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_20,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_21,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif"),
		RTK_FUNCTION(0x2, "pwm1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_22,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm2")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_23,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "pwm3")),
	RTK_PIN(RTK_PINCTRL_PIN_demod_agc,
		RTK_FUNCTION(0x0, "gpio"),/*gpio24*/
		RTK_FUNCTION(0x1, "qam_agc_if")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_25,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc1"),
		RTK_FUNCTION(0x2, "rtc_dig"),
		RTK_FUNCTION(0x3, "gspi_loc1"),
		RTK_FUNCTION(0x4, "rtc_ana"),
		RTK_FUNCTION(0x5, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_26,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc1"),
		RTK_FUNCTION(0x3, "gspi_loc1"),
		RTK_FUNCTION(0x5, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_27,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc1"),
		RTK_FUNCTION(0x3, "gspi_loc1"),
		RTK_FUNCTION(0x5, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_28,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_loc1"),
		RTK_FUNCTION(0x3, "gspi_loc1"),
		RTK_FUNCTION(0x5, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_29,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "gphy"),
		RTK_FUNCTION(0x4, "extphy")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_30,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_31,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_cmd,
		RTK_FUNCTION(0x0, "gpio"),/*gpio32*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x4, "sc1"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_clk,
		RTK_FUNCTION(0x0, "gpio"),/*gpio33*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x4, "sc1"),
		RTK_FUNCTION(0x5, "scpu_main2"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_34,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "i2c3")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_35,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "i2c3")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_data_0,
		RTK_FUNCTION(0x0, "gpio"),/*gpio36*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x4, "sc1"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_data_1,
		RTK_FUNCTION(0x0, "gpio"),/*gpio37*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x4, "sc1"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_data_2,
		RTK_FUNCTION(0x0, "gpio"),/*gpio38*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_sd3_data_3,
		RTK_FUNCTION(0x0, "gpio"),/*gpio39*/
		RTK_FUNCTION(0x1, "sd"),
		RTK_FUNCTION(0x2, "sdio_loc0"),
		RTK_FUNCTION(0x5, "scpu_ejtag_loc1"),
		RTK_FUNCTION(0x6, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_40,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x4, "tdm_ai_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_41,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x4, "tdm_ai_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_42,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x4, "tdm_ai_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_43,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x4, "tdm_ai_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_44,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_45,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "sdio_loc1"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_46,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie0"),
		RTK_FUNCTION(0x3, "gphy"),
		RTK_FUNCTION(0x4, "extphy")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_47,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ir_tx"),
		RTK_FUNCTION(0x2, "dc_fan_sensor")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_48,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_49,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_50,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif"),
		RTK_FUNCTION(0x2, "test_loop_dis")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_51,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test_loc0"),
		RTK_FUNCTION(0x2, "debug_p2s"),
		RTK_FUNCTION(0x3, "etn_led"),
		RTK_FUNCTION(0x4, "scan_debug")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_52,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test_loc0"),
		RTK_FUNCTION(0x2, "debug_p2s"),
		RTK_FUNCTION(0x4, "scan_debug")),
	RTK_PIN(RTK_PINCTRL_PIN_ir_rx,
		RTK_FUNCTION(0x0, "gpio"),/*gpio53*/
		RTK_FUNCTION(0x1, "ir_rx"),
		RTK_FUNCTION(0x2, "standby_dbg")),
	RTK_PIN(RTK_PINCTRL_PIN_ur0_rx,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio54*/
		RTK_FUNCTION(0x1, "uart0")),
	RTK_PIN(RTK_PINCTRL_PIN_ur0_tx,
		RTK_FUNCTION(0x0, "gpio"),  /*gpio55*/
		RTK_FUNCTION(0x1, "uart0")),
	RTK_PIN(RTK_PINCTRL_PIN_usb_cc1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "usb_cc1")), /*gpio56*/
	RTK_PIN(RTK_PINCTRL_PIN_gpio_57,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc1"),
		RTK_FUNCTION(0x5, "ai_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_58,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_59,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x4, "sc0"),
		RTK_FUNCTION(0x5, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_60,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x4, "sc0"),
		RTK_FUNCTION(0x5, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_61,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x4, "sc0"),
		RTK_FUNCTION(0x5, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_62,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x4, "sc0"),
		RTK_FUNCTION(0x5, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_63,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_64,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_65,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie1"),
		RTK_FUNCTION(0x2, "hdd_pwr")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_66,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie1")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_67,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_68,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif")),
	RTK_PIN(RTK_PINCTRL_PIN_usb_cc2,
		RTK_FUNCTION(0x0, "gpio"),/*gpio69*/
		RTK_FUNCTION(0x1, "usb_cc2")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_sync,
		RTK_FUNCTION(0x0, "gpio"),/*gpio70*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tdm_ai_loc0"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x6, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_valid,
		RTK_FUNCTION(0x0, "gpio"),/*gpio71*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tdm_ai_loc0"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x4, "scan_debug"),
		RTK_FUNCTION(0x6, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_clk,
		RTK_FUNCTION(0x0, "gpio"),/*gpio72*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tdm_ai_loc0"),
		RTK_FUNCTION(0x3, "dmic_loc0"),
		RTK_FUNCTION(0x6, "ai_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_0,
		RTK_FUNCTION(0x0, "gpio"),/*gpio73*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tdm_ai_loc0"),
		RTK_FUNCTION(0x3, "dmic_loc0")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_1,
		RTK_FUNCTION(0x0, "gpio"),/*gpio74*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tp1"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_2,
		RTK_FUNCTION(0x0, "gpio"),/*gpio75*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tp1"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_3,
		RTK_FUNCTION(0x0, "gpio"),/*gpio76*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tp1"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_4,
		RTK_FUNCTION(0x0, "gpio"),/*gpio77*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x2, "tp1"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_5,
		RTK_FUNCTION(0x0, "gpio"),/*gpio78*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_6,
		RTK_FUNCTION(0x0, "gpio"),/*gpio79*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x6, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_tp_data_7,
		RTK_FUNCTION(0x0, "gpio"),/*gpio80*/
		RTK_FUNCTION(0x1, "tp0"),
		RTK_FUNCTION(0x3, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_hif_data_0,
		RTK_FUNCTION(0x0, "gpio"),/*gpio81*/
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "hi")),
	RTK_PIN(RTK_PINCTRL_PIN_hif_rdy,
		RTK_FUNCTION(0x0, "gpio"),/*gpio82*/
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "hi")),
	RTK_PIN(RTK_PINCTRL_PIN_hif_clk,
		RTK_FUNCTION(0x0, "gpio"),/*gpio83*/
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "i2c4")),
	RTK_PIN(RTK_PINCTRL_PIN_hif_en,
		RTK_FUNCTION(0x0, "gpio"),/*gpio84*/
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "hi"),
		RTK_FUNCTION(0x3, "i2c4"),
		RTK_FUNCTION(0x4, "edp")),
	RTK_PIN(RTK_PINCTRL_PIN_gpio_85,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif")),

	/*OTHERS*/
	RTK_PIN(RTK_PINCTRL_PIN_ur2_loc,
		RTK_FUNCTION(0x0, "uart2_disable"),
		RTK_FUNCTION(0x1, "uart2_loc0"),
		RTK_FUNCTION(0x2, "uart2_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_gspi_loc,
		RTK_FUNCTION(0x0, "gspi_disable"),
		RTK_FUNCTION(0x1, "gspi_loc0"),
		RTK_FUNCTION(0x2, "gspi_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_sdio_loc,
		RTK_FUNCTION(0x0, "sdio_disable"),
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
		RTK_FUNCTION(0x1, "debug_p2s")),
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
		RTK_FUNCTION(0x1, "lx_ejtag_loc0"),
		RTK_FUNCTION(0x2, "lx_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_ejtag_scpu_loc,
		RTK_FUNCTION(0x1, "scpu_ejtag_disable"),
		RTK_FUNCTION(0x1, "scpu_ejtag_loc0"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_i2c_tg,
		RTK_FUNCTION(0x1, "i2c_tg_disable"),
		RTK_FUNCTION(0x2, "i2c_tg_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_dmic_loc,
		RTK_FUNCTION(0x1, "dmic_loc0"),
		RTK_FUNCTION(0x2, "dmic_loc1")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_rst,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_dd_sb,
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_clk,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_cmd,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_0,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_1,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_2,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_3,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_4,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_5,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_6,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_emmc_data_7,
		RTK_FUNCTION(0x1, "nf"),
		RTK_FUNCTION(0x2, "emmc")),

};

void gpio_pinctrl_control(struct gpio_chip *gc, int gpio, int direction, int value);

#endif /* __PINCTRL_RTK16xx_H */
