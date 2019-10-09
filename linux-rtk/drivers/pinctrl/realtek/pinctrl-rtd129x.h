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


#ifndef __PINCTRL_RTK129X_H
#define __PINCTRL_RTK129X_H

#include <linux/kernel.h>
#include <linux/pinctrl/pinctrl.h>

//#define RTK_PINCTRL_DEBUG
#ifdef RTK_PINCTRL_DEBUG
#define RTK_PINCTRL_DBG(fmt, ....) pr_info("[PINCTRL] " fmt "\n", ## __VA_ARGS__)
#else
#define RTK_PINCTRL_DBG(fmt, ...) do {} while (0)
#endif

#define RTK_PINCTRL_INF(fmt, ...) pr_info("[PINCTRL] " fmt "\n", ## __VA_ARGS__)
#define RTK_PINCTRL_ERR(fmt, ...) pr_err("[PINCTRL Error] " fmt "\n", ## __VA_ARGS__)

#define P_MISC_BASE		0
#define P_MISC_BANK		101
#define P_ISO_BASE		(P_MISC_BASE+P_MISC_BANK)
#define P_ISO_BANK		35
#define P_OTHER_BASE		(P_ISO_BASE+P_ISO_BANK)


#define RTK_PCONF_SCHM		3
#define RTK_PCONF_CURR		2
#define RTK_PCONF_PULEN		1
#define RTK_PCONF_PULSEL	0


/*****   SB2 muxpad2   *****/
#define RTK_PINCTRL_PIN_SB2_tp0_data				PINCTRL_PIN(P_MISC_BASE + 21, "tp0_data")
#define RTK_PINCTRL_PIN_SB2_tp0_sync				PINCTRL_PIN(P_MISC_BASE + 24, "tp0_sync")
#define RTK_PINCTRL_PIN_SB2_tp0_valid				PINCTRL_PIN(P_MISC_BASE + 23, "tp0_valid")
#define RTK_PINCTRL_PIN_SB2_tp0_clk					PINCTRL_PIN(P_MISC_BASE + 22, "tp0_clk")
/*hole:9~11*/
#define RTK_PINCTRL_PIN_SB2_tp1_data				PINCTRL_PIN(P_MISC_BASE + 25, "tp1_data")
#define RTK_PINCTRL_PIN_SB2_tp1_sync				PINCTRL_PIN(P_MISC_BASE + 10, "tp1_sync")
#define RTK_PINCTRL_PIN_SB2_tp1_valid				PINCTRL_PIN(P_MISC_BASE + 27, "tp1_valid")
#define RTK_PINCTRL_PIN_SB2_tp1_clk					PINCTRL_PIN(P_MISC_BASE + 26, "tp1_clk")
/*hole:24~31*/

/*****	 SB2 muxpad3   *****/
/*hole:0~3*/
#define RTK_PINCTRL_PIN_SB2_i2c_sda_4				PINCTRL_PIN(P_MISC_BASE + 12, "i2c_sda_4")
#define RTK_PINCTRL_PIN_SB2_i2c_scl_4				PINCTRL_PIN(P_MISC_BASE + 11, "i2c_scl_4")
#define RTK_PINCTRL_PIN_SB2_i2c_sda_5				PINCTRL_PIN(P_MISC_BASE + 14, "i2c_sda_5")
#define RTK_PINCTRL_PIN_SB2_i2c_scl_5				PINCTRL_PIN(P_MISC_BASE + 13, "i2c_scl_5")
/*hole:12~15*/
#define RTK_PINCTRL_PIN_SB2_usb_id					PINCTRL_PIN(P_MISC_BASE + 15, "usb_id")
#define RTK_PINCTRL_PIN_SB2_hi_loc					PINCTRL_PIN(P_OTHER_BASE + 0, "hi_loc")
#define RTK_PINCTRL_PIN_SB2_ejtag_scpu_loc			PINCTRL_PIN(P_OTHER_BASE + 1, "ejtag_scpu_loc")
#define RTK_PINCTRL_PIN_SB2_sensor_stb_1			PINCTRL_PIN(P_MISC_BASE + 20, "sensor_stb_1")
#define RTK_PINCTRL_PIN_SB2_sensor_stb_0			PINCTRL_PIN(P_MISC_BASE + 19, "sensor_stb_0")
#define RTK_PINCTRL_PIN_SB2_sensor_rst				PINCTRL_PIN(P_MISC_BASE + 18, "sensor_rst")
#define RTK_PINCTRL_PIN_SB2_sensor_cko_1			PINCTRL_PIN(P_MISC_BASE + 17, "sensor_cko_1")
#define RTK_PINCTRL_PIN_SB2_sensor_cko_0			PINCTRL_PIN(P_MISC_BASE + 16, "sensor_cko_0")

/*****	 SB2 muxpad4   *****/
#define RTK_PINCTRL_PIN_SB2_gpio_0					PINCTRL_PIN(P_MISC_BASE + 0, "gpio_0")
#define RTK_PINCTRL_PIN_SB2_gpio_1					PINCTRL_PIN(P_MISC_BASE + 1, "gpio_1")
#define RTK_PINCTRL_PIN_SB2_gpio_2					PINCTRL_PIN(P_MISC_BASE + 2, "gpio_2")
#define RTK_PINCTRL_PIN_SB2_gpio_3					PINCTRL_PIN(P_MISC_BASE + 3, "gpio_3")
#define RTK_PINCTRL_PIN_SB2_gpio_4					PINCTRL_PIN(P_MISC_BASE + 4, "gpio_4")
#define RTK_PINCTRL_PIN_SB2_gpio_5					PINCTRL_PIN(P_MISC_BASE + 5, "gpio_5")
#define RTK_PINCTRL_PIN_SB2_gpio_6					PINCTRL_PIN(P_MISC_BASE + 6, "gpio_6")
#define RTK_PINCTRL_PIN_SB2_gpio_7					PINCTRL_PIN(P_MISC_BASE + 7, "gpio_7")
#define RTK_PINCTRL_PIN_SB2_gpio_8					PINCTRL_PIN(P_MISC_BASE + 8, "gpio_8")
#define RTK_PINCTRL_PIN_SB2_gpio_9					PINCTRL_PIN(P_MISC_BASE + 9, "gpio_9")
/*hole:24~31*/

/*****	  SB2 muxpad5   *****/
#define RTK_PINCTRL_PIN_SB2_sf_en					PINCTRL_PIN(P_OTHER_BASE + 2, "sf_en")
#define RTK_PINCTRL_PIN_SB2_arm_trace_dbg_en		PINCTRL_PIN(P_OTHER_BASE + 3, "arm_trace_dbg_en")
/*hole:2~5*/
#define RTK_PINCTRL_PIN_SB2_debug_p2s_enable		PINCTRL_PIN(P_OTHER_BASE + 4, "debug_p2s_enable")
#define RTK_PINCTRL_PIN_SB2_tp0_loc					PINCTRL_PIN(P_OTHER_BASE + 5, "tp0_loc")
#define RTK_PINCTRL_PIN_SB2_tp1_loc					PINCTRL_PIN(P_OTHER_BASE + 6, "tp1_loc")
/*hole:9~31*/

/*****	  SB2 muxpad_reg0   *****/
#define RTK_PINCTRL_PIN_SB2_rgmii0_txc				PINCTRL_PIN(P_MISC_BASE + 28, "rgmii0_txc")
#define RTK_PINCTRL_PIN_SB2_rgmii0_tx_ctl			PINCTRL_PIN(P_MISC_BASE + 29, "rgmii0_tx_ctl")
#define RTK_PINCTRL_PIN_SB2_rgmii0_txd_0			PINCTRL_PIN(P_MISC_BASE + 30, "rgmii0_txd_0")
#define RTK_PINCTRL_PIN_SB2_rgmii0_txd_1			PINCTRL_PIN(P_MISC_BASE + 31, "rgmii0_txd_1")
#define RTK_PINCTRL_PIN_SB2_rgmii0_txd_2			PINCTRL_PIN(P_MISC_BASE + 32, "rgmii0_txd_2")
#define RTK_PINCTRL_PIN_SB2_rgmii0_txd_3			PINCTRL_PIN(P_MISC_BASE + 33, "rgmii0_txd_3")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rxc				PINCTRL_PIN(P_MISC_BASE + 34, "rgmii0_rxc")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rx_ctl			PINCTRL_PIN(P_MISC_BASE + 35, "rgmii0_rx_ctl")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rxd_0			PINCTRL_PIN(P_MISC_BASE + 36, "rgmii0_rxd_0")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rxd_1			PINCTRL_PIN(P_MISC_BASE + 37, "rgmii0_rxd_1")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rxd_2			PINCTRL_PIN(P_MISC_BASE + 38, "rgmii0_rxd_2")
#define RTK_PINCTRL_PIN_SB2_rgmii0_rxd_3			PINCTRL_PIN(P_MISC_BASE + 39, "rgmii0_rxd_3")
#define RTK_PINCTRL_PIN_SB2_rgmii0_mdio				PINCTRL_PIN(P_MISC_BASE + 40, "rgmii0_mdio")
#define RTK_PINCTRL_PIN_SB2_rgmii0_mdc				PINCTRL_PIN(P_MISC_BASE + 41, "rgmii0_mdc")
/*hole:28~31*/

/*****	  SB2 muxpad_reg1	*****/
#define RTK_PINCTRL_PIN_SB2_rgmii1_txc				PINCTRL_PIN(P_MISC_BASE + 42, "rgmii1_txc")
#define RTK_PINCTRL_PIN_SB2_rgmii1_tx_ctl			PINCTRL_PIN(P_MISC_BASE + 43, "rgmii1_tx_ctl")
#define RTK_PINCTRL_PIN_SB2_rgmii1_txd_0			PINCTRL_PIN(P_MISC_BASE + 44, "rgmii1_txd_0")
#define RTK_PINCTRL_PIN_SB2_rgmii1_txd_1			PINCTRL_PIN(P_MISC_BASE + 45, "rgmii1_txd_1")
#define RTK_PINCTRL_PIN_SB2_rgmii1_txd_2			PINCTRL_PIN(P_MISC_BASE + 46, "rgmii1_txd_2")
#define RTK_PINCTRL_PIN_SB2_rgmii1_txd_3			PINCTRL_PIN(P_MISC_BASE + 47, "rgmii1_txd_3")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rxc				PINCTRL_PIN(P_MISC_BASE + 48, "rgmii1_rxc")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rx_ctl			PINCTRL_PIN(P_MISC_BASE + 49, "rgmii1_rx_ctl")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rxd_0			PINCTRL_PIN(P_MISC_BASE + 50, "rgmii1_rxd_0")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rxd_1			PINCTRL_PIN(P_MISC_BASE + 51, "rgmii1_rxd_1")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rxd_2			PINCTRL_PIN(P_MISC_BASE + 52, "rgmii1_rxd_2")
#define RTK_PINCTRL_PIN_SB2_rgmii1_rxd_3			PINCTRL_PIN(P_MISC_BASE + 53, "rgmii1_rxd_3")
/*hole:28~31*/


/*****	  DISP muxpad0   *****/
#define RTK_PINCTRL_PIN_DISP_spdif					PINCTRL_PIN(P_MISC_BASE + 54, "spdif")
#define RTK_PINCTRL_PIN_DISP_dmic_clk				PINCTRL_PIN(P_MISC_BASE + 55, "dmic_clk")
#define RTK_PINCTRL_PIN_DISP_dmic_data				PINCTRL_PIN(P_MISC_BASE + 56, "dmic_data")
#define RTK_PINCTRL_PIN_DISP_ao_lrck				PINCTRL_PIN(P_MISC_BASE + 57, "ao_lrck")
#define RTK_PINCTRL_PIN_DISP_ao_bck					PINCTRL_PIN(P_MISC_BASE + 58, "ao_bck")
#define RTK_PINCTRL_PIN_DISP_aock					PINCTRL_PIN(P_MISC_BASE + 59, "aock")
#define RTK_PINCTRL_PIN_DISP_ao_sd_0				PINCTRL_PIN(P_MISC_BASE + 60, "ao_sd_0")
#define RTK_PINCTRL_PIN_DISP_ao_sd_1				PINCTRL_PIN(P_MISC_BASE + 61, "ao_sd_1")
#define RTK_PINCTRL_PIN_DISP_ao_sd_2				PINCTRL_PIN(P_MISC_BASE + 62, "ao_sd_2")
#define RTK_PINCTRL_PIN_DISP_ao_sd_3				PINCTRL_PIN(P_MISC_BASE + 63, "ao_sd_3")
#define RTK_PINCTRL_PIN_DISP_ai_loc					PINCTRL_PIN(P_OTHER_BASE + 7, "ai_loc")
/*hole:22~31*/


/*****	  CardReader muxpad0	  *****/
#define RTK_PINCTRL_PIN_CR_nf_dqs				PINCTRL_PIN(P_MISC_BASE + 77, "nf_dqs")
#define RTK_PINCTRL_PIN_CR_nf_rdy				PINCTRL_PIN(P_MISC_BASE + 68, "nf_rdy")
#define RTK_PINCTRL_PIN_CR_nf_rd_n				PINCTRL_PIN(P_MISC_BASE + 66, "nf_rd_n")
#define RTK_PINCTRL_PIN_CR_nf_wr_n				PINCTRL_PIN(P_MISC_BASE + 67, "nf_wr_n")
#define RTK_PINCTRL_PIN_CR_nf_ale				PINCTRL_PIN(P_MISC_BASE + 65, "nf_ale")
#define RTK_PINCTRL_PIN_CR_nf_cle				PINCTRL_PIN(P_MISC_BASE + 64, "nf_cle")
#define RTK_PINCTRL_PIN_CR_nf_ce_n_0				PINCTRL_PIN(P_MISC_BASE + 78, "nf_ce_n_0")
#define RTK_PINCTRL_PIN_CR_nf_ce_n_1				PINCTRL_PIN(P_MISC_BASE + 79, "nf_ce_n_1")
#define RTK_PINCTRL_PIN_CR_nf_dd_0				PINCTRL_PIN(P_MISC_BASE + 76, "nf_dd_0")
#define RTK_PINCTRL_PIN_CR_nf_dd_1				PINCTRL_PIN(P_MISC_BASE + 75, "nf_dd_1")
#define RTK_PINCTRL_PIN_CR_nf_dd_2				PINCTRL_PIN(P_MISC_BASE + 74, "nf_dd_2")
#define RTK_PINCTRL_PIN_CR_nf_dd_3				PINCTRL_PIN(P_MISC_BASE + 73, "nf_dd_3")
#define RTK_PINCTRL_PIN_CR_nf_dd_4				PINCTRL_PIN(P_MISC_BASE + 72, "nf_dd_4")
#define RTK_PINCTRL_PIN_CR_nf_dd_5				PINCTRL_PIN(P_MISC_BASE + 71, "nf_dd_5")
#define RTK_PINCTRL_PIN_CR_nf_dd_6				PINCTRL_PIN(P_MISC_BASE + 70, "nf_dd_6")
#define RTK_PINCTRL_PIN_CR_nf_dd_7				PINCTRL_PIN(P_MISC_BASE + 69, "nf_dd_7")


/*****	  CardReader muxpad1   *****/
#define RTK_PINCTRL_PIN_CR_sdio_cmd				PINCTRL_PIN(P_MISC_BASE + 89, "sdio_cmd")
#define RTK_PINCTRL_PIN_CR_sdio_clk				PINCTRL_PIN(P_MISC_BASE + 90, "sdio_clk")
#define RTK_PINCTRL_PIN_CR_sdio_data_0				PINCTRL_PIN(P_MISC_BASE + 91, "sdio_data_0")
#define RTK_PINCTRL_PIN_CR_sdio_data_1				PINCTRL_PIN(P_MISC_BASE + 92, "sdio_data_1")
#define RTK_PINCTRL_PIN_CR_sdio_data_2				PINCTRL_PIN(P_MISC_BASE + 93, "sdio_data_2")
#define RTK_PINCTRL_PIN_CR_sdio_data_3				PINCTRL_PIN(P_MISC_BASE + 94, "sdio_data_3")
#define RTK_PINCTRL_PIN_CR_emmc_dd_sb				PINCTRL_PIN(P_MISC_BASE + 80, "emmc_dd_sb")
/*hole:14~15*/
#define RTK_PINCTRL_PIN_CR_mmc_cmd				PINCTRL_PIN(P_MISC_BASE + 81, "mmc_cmd")
#define RTK_PINCTRL_PIN_CR_mmc_clk				PINCTRL_PIN(P_MISC_BASE + 82, "mmc_clk")
#define RTK_PINCTRL_PIN_CR_mmc_wp				PINCTRL_PIN(P_MISC_BASE + 83, "mmc_wp")
#define RTK_PINCTRL_PIN_CR_mmc_cd				PINCTRL_PIN(P_MISC_BASE + 84, "mmc_cd")
#define RTK_PINCTRL_PIN_CR_mmc_data_0				PINCTRL_PIN(P_MISC_BASE + 85, "mmc_data_0")
#define RTK_PINCTRL_PIN_CR_mmc_data_1				PINCTRL_PIN(P_MISC_BASE + 86, "mmc_data_1")
#define RTK_PINCTRL_PIN_CR_mmc_data_2				PINCTRL_PIN(P_MISC_BASE + 87, "mmc_data_2")
#define RTK_PINCTRL_PIN_CR_mmc_data_3				PINCTRL_PIN(P_MISC_BASE + 88, "mmc_data_3")


/*****	  CardReader muxpad2   *****/
#define RTK_PINCTRL_PIN_CR_sdio_loc				PINCTRL_PIN(P_OTHER_BASE + 8, "sdio_loc")
#define RTK_PINCTRL_PIN_CR_pcie_clkreq_0			PINCTRL_PIN(P_MISC_BASE + 95, "pcie_clkreq_0")
#define RTK_PINCTRL_PIN_CR_pcie_clkreq_1			PINCTRL_PIN(P_MISC_BASE + 96, "pcie_clkreq_1")
#define RTK_PINCTRL_PIN_CR_prob_0				PINCTRL_PIN(P_MISC_BASE + 97, "prob_0")
#define RTK_PINCTRL_PIN_CR_prob_1				PINCTRL_PIN(P_MISC_BASE + 98, "prob_1")
#define RTK_PINCTRL_PIN_CR_prob_2				PINCTRL_PIN(P_MISC_BASE + 99, "prob_2")
#define RTK_PINCTRL_PIN_CR_prob_3				PINCTRL_PIN(P_MISC_BASE + 100, "prob_3")
/*hole:14~31*/


/*****	  ISO muxpad0   *****/
#define RTK_PINCTRL_PIN_ISO_iso_gpio_4				PINCTRL_PIN(P_ISO_BASE + 4, "iso_gpio_4")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_5				PINCTRL_PIN(P_ISO_BASE + 5,	"iso_gpio_5")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_7				PINCTRL_PIN(P_ISO_BASE + 7,	"iso_gpio_7")
#define RTK_PINCTRL_PIN_ISO_ir_rx					PINCTRL_PIN(P_ISO_BASE + 8,	"ir_rx")
#define RTK_PINCTRL_PIN_ISO_ir_tx					PINCTRL_PIN(P_ISO_BASE + 9,	"ir_tx")
#define RTK_PINCTRL_PIN_ISO_ur0_rx					PINCTRL_PIN(P_ISO_BASE + 10, "ur0_rx")
#define RTK_PINCTRL_PIN_ISO_ur0_tx					PINCTRL_PIN(P_ISO_BASE + 11, "ur0_tx")
#define RTK_PINCTRL_PIN_ISO_ur1_rx					PINCTRL_PIN(P_ISO_BASE + 12, "ur1_rx")
#define RTK_PINCTRL_PIN_ISO_ur1_tx					PINCTRL_PIN(P_ISO_BASE + 13, "ur1_tx")
#define RTK_PINCTRL_PIN_ISO_ur1_cts_n				PINCTRL_PIN(P_ISO_BASE + 14, "ur1_cts_n")
#define RTK_PINCTRL_PIN_ISO_ur1_rts_n				PINCTRL_PIN(P_ISO_BASE + 15, "ur1_rts_n")
#define RTK_PINCTRL_PIN_ISO_i2c_scl_0				PINCTRL_PIN(P_ISO_BASE + 16, "i2c_scl_0")
#define RTK_PINCTRL_PIN_ISO_i2c_sda_0				PINCTRL_PIN(P_ISO_BASE + 17, "i2c_sda_0")
#define RTK_PINCTRL_PIN_ISO_etn_led_link			PINCTRL_PIN(P_ISO_BASE + 27, "etn_led_link")
#define RTK_PINCTRL_PIN_ISO_etn_led_rxtx			PINCTRL_PIN(P_ISO_BASE + 28, "etn_led_rxtx")


/*****	  ISO muxpad1	*****/
#define RTK_PINCTRL_PIN_ISO_i2c_scl_6				PINCTRL_PIN(P_ISO_BASE + 20, "i2c_scl_6")
#define RTK_PINCTRL_PIN_ISO_i2c_sda_6				PINCTRL_PIN(P_ISO_BASE + 26, "i2c_sda_6")
#define RTK_PINCTRL_PIN_ISO_hdmi_hpd				PINCTRL_PIN(P_ISO_BASE + 6,	"hdmi_hpd")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_2				PINCTRL_PIN(P_ISO_BASE + 2,	"iso_gpio_2")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_3				PINCTRL_PIN(P_ISO_BASE + 3,	"iso_gpio_3")
#define RTK_PINCTRL_PIN_ISO_i2c_scl_1				PINCTRL_PIN(P_ISO_BASE + 18, "i2c_scl_1")
#define RTK_PINCTRL_PIN_ISO_i2c_sda_1				PINCTRL_PIN(P_ISO_BASE + 19, "i2c_sda_1")
#define RTK_PINCTRL_PIN_ISO_nat_led_0				PINCTRL_PIN(P_ISO_BASE + 29, "nat_led_0")
#define RTK_PINCTRL_PIN_ISO_nat_led_1				PINCTRL_PIN(P_ISO_BASE + 30, "nat_led_1")
#define RTK_PINCTRL_PIN_ISO_nat_led_2				PINCTRL_PIN(P_ISO_BASE + 31, "nat_led_2")
#define RTK_PINCTRL_PIN_ISO_nat_led_3				PINCTRL_PIN(P_ISO_BASE + 32, "nat_led_3")
#define RTK_PINCTRL_PIN_ISO_pwm_23_open_drain_en_loc0					PINCTRL_PIN(P_OTHER_BASE + 9,	"pwm_23_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_ISO_pwm_01_open_drain_en_loc0					PINCTRL_PIN(P_OTHER_BASE + 10,	"pwm_01_open_drain_en_loc0")
#define RTK_PINCTRL_PIN_ISO_pwm_23_open_drain_en_loc1					PINCTRL_PIN(P_OTHER_BASE + 11,	"pwm_23_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_ISO_pwm_01_open_drain_en_loc1					PINCTRL_PIN(P_OTHER_BASE + 12,	"pwm_01_open_drain_en_loc1")
#define RTK_PINCTRL_PIN_ISO_ejtag_avcpu_loc			PINCTRL_PIN(P_OTHER_BASE + 13, "ejtag_avcpu_loc")
#define RTK_PINCTRL_PIN_ISO_ur2_loc					PINCTRL_PIN(P_OTHER_BASE + 14, "ur2_loc")


/*****	  ISO muxpad2	*****/
#define RTK_PINCTRL_PIN_ISO_iso_gpio_21					PINCTRL_PIN(P_ISO_BASE + 21, "iso_gpio_21")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_22					PINCTRL_PIN(P_ISO_BASE + 22, "iso_gpio_22")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_23					PINCTRL_PIN(P_ISO_BASE + 23, "iso_gpio_23")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_24					PINCTRL_PIN(P_ISO_BASE + 24, "iso_gpio_24")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_25					PINCTRL_PIN(P_ISO_BASE + 25, "iso_gpio_25")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_33					PINCTRL_PIN(P_ISO_BASE + 33, "iso_gpio_33")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_34					PINCTRL_PIN(P_ISO_BASE + 34, "iso_gpio_34")
/*hole:14*/
#define RTK_PINCTRL_PIN_ISO_i2c_tg_enable				PINCTRL_PIN(P_OTHER_BASE + 15,	"i2c_tg_enable")


/*****	  No muxpad GPIO	*****/
#define RTK_PINCTRL_PIN_ISO_iso_gpio_0				PINCTRL_PIN(P_ISO_BASE + 0, "iso_gpio_0")
#define RTK_PINCTRL_PIN_ISO_iso_gpio_1				PINCTRL_PIN(P_ISO_BASE + 1, "iso_gpio_1")


enum PMUX_BASE_TYPE {
	PMUX_BASE_SB2,
	PMUX_BASE_DISP,
	PMUX_BASE_CR,
	PMUX_BASE_ISO
};

struct rtk_pin_regmap {
	u8	pmux_base;
	u16 pmux_regoff;
	u16 pmux_regbit;
	u16 pmux_regbitmsk;
	u16 pcof_regoff;
	u16 pcof_regbit;
	u16 pcof_cur_strgh;//0 : 2&4mA   1:4&8mA
};

struct rtk_pinmux_reg {
	u8	reg_base;
	u16 reg_offset;
};

#define PADDRI_4_8 1
#define PADDRI_2_4 0
#define PADDRI_UNSUPPORT 0xFFFF

#define PCOF_UNSUPPORT 0xFFFF
#define PMUX_UNSUPPORT 0xFFFF

static const struct rtk_pinmux_reg pinmux_reg_list[] = {
	/* ----- SB2 muxpad ----- */
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x908},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x90c},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x910},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x914},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x96c},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x97c},
	/* ----- SB2 pfunc ----- */
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x928},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x92c},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x930},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x934},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x938},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x93c},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x964},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x968},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x974},
	{.reg_base = PMUX_BASE_SB2, .reg_offset = 0x978},
	/* ----- disp muxpad ----- */
	{.reg_base = PMUX_BASE_DISP, .reg_offset = 0x008},
	/* ----- disp pfunc ----- */
	{.reg_base = PMUX_BASE_DISP, .reg_offset = 0x000},
	{.reg_base = PMUX_BASE_DISP, .reg_offset = 0x004},
	/* ----- CardReader muxpad ----- */
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x600},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x604},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x61c},
	/* ----- CardReader pfunc ----- */
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x608},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x60c},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x610},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x614},
	{.reg_base = PMUX_BASE_CR, .reg_offset = 0x618},
	/* ----- ISO muxpad ----- */
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x310},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x314},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x31c},
	/* ----- ISO pfunc ----- */
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x300},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x304},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x308},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x30c},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x318},
	{.reg_base = PMUX_BASE_ISO, .reg_offset = 0x320},
};

static const struct rtk_pin_regmap pin_regmap[] = {
	/* ----- SB2 muxpad ----- */
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x934, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 0, "gpio_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x934, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 1, "gpio_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x934, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 2, "gpio_2")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x934, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 3, "gpio_3")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x934, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 4, "gpio_4")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x934, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 5, "gpio_5")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x934, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 6, "gpio_6")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x934, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 7, "gpio_7")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 8, "gpio_8")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x910, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 9, "gpio_9")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x92c, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 10, "tp1_sync")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x930, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 11, "i2c_scl_4")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x930, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 12, "i2c_sda_4")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x930, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 13, "i2c_scl_5")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x930, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 14, "i2c_sda_5")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 15, "usb_id")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 30, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 16, "sensor_cko_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 17, "sensor_cko_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 18, "sensor_rst")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 19, "sensor_stb_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x938, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 20, "sensor_stb_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x928, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 21, "tp0_data")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x928, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 22, "tp0_clk")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x928, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 23, "tp0_valid")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x928, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 24, "tp0_sync")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x92c, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 25, "tp1_data")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x92c, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 26, "tp1_clk")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x908, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x92c, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 27, "tp1_valid")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 28, "rgmii0_txc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 29, "rgmii0_tx_ctl")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 30, "rgmii0_txd_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 31, "rgmii0_txd_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 32, "rgmii0_txd_2")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 33, "rgmii0_txd_3")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 34, "rgmii0_rxc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x964, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 35, "rgmii0_rx_ctl")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 36, "rgmii0_rxd_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 37, "rgmii0_rxd_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 38, "rgmii0_rxd_2")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 39, "rgmii0_rxd_3")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 40, "rgmii0_mdio")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x96c, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x968, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 41, "rgmii0_mdc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 42, "rgmii1_txc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 43, "rgmii1_tx_ctl")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 44, "rgmii1_txd_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 45, "rgmii1_txd_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 46, "rgmii1_txd_2")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 47, "rgmii1_txd_3")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 48, "rgmii1_rxc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x974, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 49, "rgmii1_rx_ctl")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x978, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 50, "rgmii1_rxd_0")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x978, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 51, "rgmii1_rxd_1")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x978, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 52, "rgmii1_rxd_2")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x97c, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x978, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 53, "rgmii1_rxd_3")
	/* ----- disp muxpad ----- */
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x000, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 54, "spdif")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x000, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 55, "dmic_clk")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x000, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 56, "dmic_data")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 57, "ao_lrck")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 58, "ao_bck")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 59, "aock")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 60, "ao_sd_0")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 61, "ao_sd_1")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 62, "ao_sd_2")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x004, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 63, "ao_sd_3")
	/* ----- CardReader muxpad ----- */
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 64, "nf_cle")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 65, "nf_ale")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 66, "nf_rd_n")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 67, "nf_wr_n")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 68, "nf_rdy")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 30, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 69, "nf_dd_7")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 70, "nf_dd_6")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 71, "nf_dd_5")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 72, "nf_dd_4")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 73, "nf_dd_3")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 74, "nf_dd_2")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 75, "nf_dd_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x60c, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 76, "nf_dd_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 77, "nf_dqs")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 78, "nf_ce_n_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x600, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x608, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 79, "nf_ce_n_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 80, "emmc_dd_sb")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 81, "mmc_cmd")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 82, "mmc_clk")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 83, "mmc_wp")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 84, "mmc_cd")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 85, "mmc_data_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 86, "mmc_data_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 87, "mmc_data_2")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 30, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x610, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 88, "mmc_data_3")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 89, "sdio_cmd")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 90, "sdio_clk")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 91, "sdio_data_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 92, "sdio_data_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 93, "sdio_data_2")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x604, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x614, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 94, "sdio_data_3")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 95, "pcie_clkreq_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 96, "pcie_clkreq_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 97, "prob_0")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 98, "prob_1")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 99, "prob_2")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x618, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 100, "prob_3")
	/* ----- ISO muxpad ----- */
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = PMUX_UNSUPPORT,	.pmux_regbit = 0, .pmux_regbitmsk = 0x0,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 0, "iso_gpio_0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = PMUX_UNSUPPORT,	.pmux_regbit = 0, .pmux_regbitmsk = 0x0,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 1, "iso_gpio_1)
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x300, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 2,	"iso_gpio_2")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x300, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 3,	"iso_gpio_3")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 4,	"iso_gpio_4")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 5,	"iso_gpio_5")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x30c, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 6,	"hdmi_hpd")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 7,	"iso_gpio_7")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 8,	"ir_rx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x308, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 9,	"ir_tx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 10, "ur0_rx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 11, "ur0_tx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 12, "ur1_rx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 13, "ur1_tx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 14, "ur1_cts_n")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 15, "ur1_rts_n")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 16, "i2c_scl_0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x300, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 17, "i2c_sda_0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x308, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 18, "i2c_scl_1")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 14, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x308, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 19, "i2c_sda_1")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x308, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 20, "i2c_scl_6")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x318, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 21, "iso_gpio_21")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x318, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 22, "iso_gpio_22")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x318, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 23, "iso_gpio_23")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x318, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 24, "iso_gpio_24")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x318, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 25, "iso_gpio_25")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x308, .pcof_regbit = 12, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 26, "i2c_sda_6")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 27, "etn_led_link")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x310, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x304, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 28, "etn_led_rxtx")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 16, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x30c, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 29, "nat_led_0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x30c, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 30, "nat_led_1")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x30c, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 31, "nat_led_2")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x30c, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 32, "nat_led_3")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x320, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 33, "iso_gpio_33")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 12, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x320, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 34, "iso_gpio_34")
	/* Other, not gpio*/
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c,	.pmux_regbit = 18, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 0, "hi_loc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x90c,	.pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 1, "ejtag_scpu_loc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x914,	.pmux_regbit = 0, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 2, "sf_en")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x914,	.pmux_regbit = 1, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 3, "arm_trace_dbg_en")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x914,	.pmux_regbit = 6, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 4, "debug_p2s_enable")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x914,	.pmux_regbit = 7, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 5, "tp0_loc")
	{.pmux_base = PMUX_BASE_SB2,	.pmux_regoff = 0x914,	.pmux_regbit = 8, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 6, "tp1_loc")
	{.pmux_base = PMUX_BASE_DISP, .pmux_regoff = 0x008,	.pmux_regbit = 20, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 7, "ai_loc")
	{.pmux_base = PMUX_BASE_CR,	.pmux_regoff = 0x61c,	.pmux_regbit = 0, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 8, "sdio_loc")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 24, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 9, "pwm_23_open_drain_en_loc0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 25, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 10, "pwm_01_open_drain_en_loc0")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 26, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 11, "pwm_23_open_drain_en_loc1")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 27, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 12, "pwm_01_open_drain_en_loc1")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 13, "ejtag_avcpu_loc")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x314, .pmux_regbit = 30, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 14, "ur2_loc")
	{.pmux_base = PMUX_BASE_ISO,	.pmux_regoff = 0x31c, .pmux_regbit = 15, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_OTHER_BASE + 15, "i2c_tg_enable")
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
	void __iomem			*sb2_membase;
	void __iomem			*disp_membase;
	void __iomem			*cr_membase;
	void __iomem			*iso_membase;
//	struct gpio_chip		*chip;
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
	/*****   Pin 0~4   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x3, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_gpio"),
		RTK_FUNCTION(0x3, "gspi")),
	/*****   Pin 5~9   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_gpio"),
		RTK_FUNCTION(0x3, "gspi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_gpio"),
		RTK_FUNCTION(0x3, "gspi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_7,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_gpio"),
		RTK_FUNCTION(0x3, "gspi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_8,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_gpio_9,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "dc_fan_sensor")),
	/*****   Pin 10~14   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp1_sync,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp1_loc_tp1"),
		RTK_FUNCTION(0x2, "tp1_loc_tp0"),
		RTK_FUNCTION(0x3, "i2c2")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_i2c_scl_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c4")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_i2c_sda_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c4")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_i2c_scl_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c5"),
		RTK_FUNCTION(0x3, "nand")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_i2c_sda_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c5"),
		RTK_FUNCTION(0x3, "nand")),
	/*****   Pin 15~19   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_usb_id,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "test_loop_dis")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sensor_cko_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sensor_cko_output")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sensor_cko_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sensor_cko_output"),
		RTK_FUNCTION(0x3, "usb_clock_output")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sensor_rst,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sensor_stb_0,
		RTK_FUNCTION(0x0, "gpio")),
	/*****   Pin 20~24   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sensor_stb_1,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp0_data,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp0_loc_tp0"),
		RTK_FUNCTION(0x2, "tp0_loc_tp1"),
		RTK_FUNCTION(0x3, "AI")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp0_clk,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp0_loc_tp0"),
		RTK_FUNCTION(0x2, "tp0_loc_tp1"),
		RTK_FUNCTION(0x3, "AI")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp0_valid,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp0_loc_tp0"),
		RTK_FUNCTION(0x2, "tp0_loc_tp1"),
		RTK_FUNCTION(0x3, "AI")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp0_sync,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp0_loc_tp0"),
		RTK_FUNCTION(0x2, "tp0_loc_tp1"),
		RTK_FUNCTION(0x3, "AI")),
	/*****   Pin 25~29   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp1_data,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp1_loc_tp1"),
		RTK_FUNCTION(0x2, "tp1_loc_tp0"),
		RTK_FUNCTION(0x3, "i2c3")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp1_clk,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp1_loc_tp1"),
		RTK_FUNCTION(0x2, "tp1_loc_tp0"),
		RTK_FUNCTION(0x3, "i2c2")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp1_valid,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "tp1_loc_tp1"),
		RTK_FUNCTION(0x2, "tp1_loc_tp0"),
		RTK_FUNCTION(0x3, "i2c3")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_txc,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_tx_ctl,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	/*****   Pin 30~34   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_txd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp0_loc_rgmii0_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_txd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp0_loc_rgmii0_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_txd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp0_loc_rgmii0_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_txd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp0_loc_rgmii0_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rxc,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	/*****   Pin 35~39   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rx_ctl,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rxd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp1_loc_rgmii0_rx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rxd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp1_loc_rgmii0_rx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rxd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp1_loc_rgmii0_rx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_rxd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "tp1_loc_rgmii0_rx")),
	/*****   Pin 40~44   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_mdio,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "eth_gpy")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii0_mdc,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii"),
		RTK_FUNCTION(0x2, "eth_gpy")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_txc,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_tx_ctl,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_txd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	/*****   Pin 45~49   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_txd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_txd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_txd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rxc,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rx_ctl,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	/*****   Pin 50~54   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rxd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rxd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rxd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_rgmii1_rxd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rgmii")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_spdif,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spdif_out")),
	/*****   Pin 55~59   *****/
	RTK_PIN(RTK_PINCTRL_PIN_DISP_dmic_clk,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "dmic"),
		RTK_FUNCTION(0x2, "ai")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_dmic_data,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "dmic"),
		RTK_FUNCTION(0x2, "ai")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_lrck,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_bck,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_aock,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao")),
	/*****   Pin 60~64   *****/
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_sd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_sd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_sd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao"),
		RTK_FUNCTION(0x2, "ai")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ao_sd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ao"),
		RTK_FUNCTION(0x2, "ai")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_cle,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "hif")),
	/*****   Pin 65~69   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_ale,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x3, "hif")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_rd_n,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "avcpu_ej")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_wr_n,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x3, "hif")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_rdy,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "avcpu_ej")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_7,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "avcpu_ej")),
	/*****   Pin 70~74   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "avcpu_ej")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "avcpu_ej")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc"),
		RTK_FUNCTION(0x3, "hif")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	/*****   Pin 75~79   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dd_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_dqs,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_ce_n_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_nf_ce_n_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nand")),
	/*****   Pin 80~84   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_emmc_dd_sb,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "emmc")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_cmd,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio"),
		RTK_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_clk,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio"),
		RTK_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_wp,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_cd,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card")),
	/*****   Pin 85~89   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_data_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio"),
		RTK_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_data_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_data_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_mmc_data_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card"),
		RTK_FUNCTION(0x2, "sdio"),
		RTK_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_cmd,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio")),
	/*****   Pin 90~94   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_clk,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sd_card")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_data_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_data_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_data_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_data_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "sdio")),
	/*****   Pin 95~99   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_pcie_clkreq_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_pcie_clkreq_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pcie")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_prob_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test"),
		RTK_FUNCTION(0x2, "p2s")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_prob_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test"),
		RTK_FUNCTION(0x2, "p2s")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_prob_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test")),
	/*****   Pin 100~104   *****/
	RTK_PIN(RTK_PINCTRL_PIN_CR_prob_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pll_test")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_0,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_1,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "standby_dbg"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc_iso"),
		RTK_FUNCTION(0x4, "uart2_0")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "standby_dbg"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc_iso"),
		RTK_FUNCTION(0x4, "uart2_0")),
	/*****   Pin 105~109   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_4,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc_iso")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_5,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart2_0"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc_iso")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_hdmi_hpd,
		RTK_FUNCTION(0x0, "gpio")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_7,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "edp_hpd"),
		RTK_FUNCTION(0x3, "acpu_ejtag_loc_iso")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ir_rx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ir_rx"),
		RTK_FUNCTION(0x2, "standby_dbg")),
	/*****   Pin 110~114   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ir_tx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "ir_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur0_rx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart0")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur0_tx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart0")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur1_rx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur1_tx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	/*****   Pin 115~119   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur1_cts_n,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur1_rts_n,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "uart1")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_scl_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c0")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_sda_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c0")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_scl_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c1")),
	/*****   Pin 120~124   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_sda_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c1")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_scl_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c6")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_21,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pwm")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_22,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pwm")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_23,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pwm"),
		RTK_FUNCTION(0x2, "uart2_1")),
	/*****   Pin 125~129   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_24,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "pwm"),
		RTK_FUNCTION(0x2, "uart2_1")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_25,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "rtc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_sda_6,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "i2c6")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_etn_led_link,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "etn_led"),
		RTK_FUNCTION(0x2, "pwm")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_etn_led_rxtx,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "etn_led"),
		RTK_FUNCTION(0x2, "pwm")),
	/*****   Pin 130~134   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_nat_led_0,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nat_led"),
		RTK_FUNCTION(0x2, "pwm"),
		RTK_FUNCTION(0x3, "sc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_nat_led_1,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nat_led"),
		RTK_FUNCTION(0x2, "pwm"),
		RTK_FUNCTION(0x3, "sc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_nat_led_2,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nat_led"),
		RTK_FUNCTION(0x3, "sc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_nat_led_3,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "nat_led"),
		RTK_FUNCTION(0x3, "sc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_33,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "uart2_1")),
	/*****   Pin 135   *****/
	RTK_PIN(RTK_PINCTRL_PIN_ISO_iso_gpio_34,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x2, "uart2_1")),
	/*****   Pin 136~   *****/
	RTK_PIN(RTK_PINCTRL_PIN_SB2_hi_loc,
		RTK_FUNCTION(0x1, "hi_loc_misc"),
		RTK_FUNCTION(0x2, "hi_loc_nf")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_ejtag_scpu_loc,
		RTK_FUNCTION(0x1, "scpu_ejtag_loc_gpio"),
		RTK_FUNCTION(0x2, "scpu_ejtag_loc_cr")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_sf_en,
		RTK_FUNCTION(0x0, "gpio"),
		RTK_FUNCTION(0x1, "spi")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_arm_trace_dbg_en,
		RTK_FUNCTION(0x0, "arm_trace_disable"),
		RTK_FUNCTION(0x1, "arm_trace_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_debug_p2s_enable,
		RTK_FUNCTION(0x0, "p2s_disable"),
		RTK_FUNCTION(0x1, "p2s_enable")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp0_loc,
		RTK_FUNCTION(0x0, "tp0_loc_tp0"),
		RTK_FUNCTION(0x0, "tp0_loc_tp1"),
		RTK_FUNCTION(0x1, "tp0_loc_rgmii0_tx")),
	RTK_PIN(RTK_PINCTRL_PIN_SB2_tp1_loc,
		RTK_FUNCTION(0x0, "tp1_loc_tp1"),
		RTK_FUNCTION(0x0, "tp1_loc_tp0"),
		RTK_FUNCTION(0x1, "tp1_loc_rgmii0_rx")),
	RTK_PIN(RTK_PINCTRL_PIN_DISP_ai_loc,
		RTK_FUNCTION(0x1, "ai_loc_main"),
		RTK_FUNCTION(0x2, "ai_loc_disp")),
	RTK_PIN(RTK_PINCTRL_PIN_CR_sdio_loc,
		RTK_FUNCTION(0x1, "sdio_loc_sdio"),
		RTK_FUNCTION(0x2, "sdio_loc_mmc")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_pwm_23_open_drain_en_loc0,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_pwm_01_open_drain_en_loc0,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_pwm_23_open_drain_en_loc1,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_pwm_01_open_drain_en_loc1,
		RTK_FUNCTION(0x0, "pwm_normal"),
		RTK_FUNCTION(0x1, "pwm_open_drain")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ejtag_avcpu_loc,
		RTK_FUNCTION(0x1, "acpu_ejtag_loc_iso"),
		RTK_FUNCTION(0x2, "acpu_ejtag_loc_nf")),
	RTK_PIN(RTK_PINCTRL_PIN_ISO_ur2_loc,
		RTK_FUNCTION(0x1, "uart2_0"),//iso_2_3_4_5
		RTK_FUNCTION(0x2, "uart2_1")),//iso_23_24_33_34
	RTK_PIN(RTK_PINCTRL_PIN_ISO_i2c_tg_enable,
		RTK_FUNCTION(0x0, "i2c_tg_enable"),
		RTK_FUNCTION(0x1, "i2c_tg_disable")),
};

#endif /* __PINCTRL_RTK129X_H */
