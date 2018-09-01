/*
 * Allwinner A1X SoCs pinctrl driver.
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@free-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __PINCTRL_RTK119X_H
#define __PINCTRL_RTK119X_H

#include <linux/kernel.h>

#define P_SB2_BASE	0
#define P_ISO_BASE	115


//#define RTK_DEBUG
#ifdef RTK_DEBUG
#define RTK_debug(fmt, ...) printk(fmt, ##__VA_ARGS__)
#else
#define RTK_debug(fmt, ...) do {} while(0)
#endif

/**********************************************************************************
* sb2_muxpad0
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_nf_dqs					PINCTRL_PIN(P_SB2_BASE + 110,  	"nf_dqs")
#define RTK_PINCTRL_PIN_SB2_nf_rdy					PINCTRL_PIN(P_SB2_BASE + 17,  	"nf_rdy")
#define RTK_PINCTRL_PIN_SB2_nf_rd_n					PINCTRL_PIN(P_SB2_BASE + 18, 	"nf_rd_n")
#define RTK_PINCTRL_PIN_SB2_nf_wr_n					PINCTRL_PIN(P_SB2_BASE + 19,  	"nf_wr_n")
#define RTK_PINCTRL_PIN_SB2_nf_ale					PINCTRL_PIN(P_SB2_BASE + 20,  	"nf_ale")
#define RTK_PINCTRL_PIN_SB2_nf_cle					PINCTRL_PIN(P_SB2_BASE + 21,  	"nf_cle")
#define RTK_PINCTRL_PIN_SB2_nf_ce_n_0 				PINCTRL_PIN(P_SB2_BASE + 22,  	"nf_ce_n_0")
#define RTK_PINCTRL_PIN_SB2_nf_ce_n_1 				PINCTRL_PIN(P_SB2_BASE + 23,  	"nf_ce_n_1")
#define RTK_PINCTRL_PIN_SB2_nf_dd_0					PINCTRL_PIN(P_SB2_BASE + 9,  	"nf_dd_0")
#define RTK_PINCTRL_PIN_SB2_nf_dd_1					PINCTRL_PIN(P_SB2_BASE + 10,  	"nf_dd_1")
#define RTK_PINCTRL_PIN_SB2_nf_dd_2					PINCTRL_PIN(P_SB2_BASE + 11,  	"nf_dd_2")
#define RTK_PINCTRL_PIN_SB2_nf_dd_3					PINCTRL_PIN(P_SB2_BASE + 12,  	"nf_dd_3")
#define RTK_PINCTRL_PIN_SB2_nf_dd_4 				PINCTRL_PIN(P_SB2_BASE + 13,  	"nf_dd_4")
#define RTK_PINCTRL_PIN_SB2_nf_dd_5					PINCTRL_PIN(P_SB2_BASE + 14,  	"nf_dd_5")
#define RTK_PINCTRL_PIN_SB2_nf_dd_6					PINCTRL_PIN(P_SB2_BASE + 15,  	"nf_dd_6")
#define RTK_PINCTRL_PIN_SB2_nf_dd_7					PINCTRL_PIN(P_SB2_BASE + 16,  	"nf_dd_7")


/**********************************************************************************
* sb2_muxpad1
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_sdio_cmd				PINCTRL_PIN(P_SB2_BASE + 37,  	"sdio_cmd")
#define RTK_PINCTRL_PIN_SB2_sdio_clk				PINCTRL_PIN(P_SB2_BASE + 32,  	"sdio_clk")
#define RTK_PINCTRL_PIN_SB2_sdio_data_0				PINCTRL_PIN(P_SB2_BASE + 33,  	"sdio_data_0")
#define RTK_PINCTRL_PIN_SB2_sdio_data_1 			PINCTRL_PIN(P_SB2_BASE + 34,  	"sdio_data_1")
#define RTK_PINCTRL_PIN_SB2_sdio_data_2 			PINCTRL_PIN(P_SB2_BASE + 35,  	"sdio_data_2")
#define RTK_PINCTRL_PIN_SB2_sdio_data_3 			PINCTRL_PIN(P_SB2_BASE + 36,  	"sdio_data_3")
//Rvd:12~15
#define RTK_PINCTRL_PIN_SB2_mmc_cmd 				PINCTRL_PIN(P_SB2_BASE + 29,  	"mmc_cmd")
#define RTK_PINCTRL_PIN_SB2_mmc_clk 				PINCTRL_PIN(P_SB2_BASE + 28,  	"mmc_clk")
#define RTK_PINCTRL_PIN_SB2_mmc_wp 					PINCTRL_PIN(P_SB2_BASE + 30,  	"mmc_wp")
#define RTK_PINCTRL_PIN_SB2_mmc_cd 					PINCTRL_PIN(P_SB2_BASE + 31,  	"mmc_cd")
#define RTK_PINCTRL_PIN_SB2_mmc_data_0 				PINCTRL_PIN(P_SB2_BASE + 24,  	"mmc_data_0")
#define RTK_PINCTRL_PIN_SB2_mmc_data_1 				PINCTRL_PIN(P_SB2_BASE + 25,  	"mmc_data_1")
#define RTK_PINCTRL_PIN_SB2_mmc_data_2 				PINCTRL_PIN(P_SB2_BASE + 26,  	"mmc_data_2")
#define RTK_PINCTRL_PIN_SB2_mmc_data_3 				PINCTRL_PIN(P_SB2_BASE + 27,  	"mmc_data_3")


/**********************************************************************************
* sb2_muxpad2
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_tp0_data 				PINCTRL_PIN(P_SB2_BASE + 44,  	"tp0_data")
#define RTK_PINCTRL_PIN_SB2_tp0_sync 				PINCTRL_PIN(P_SB2_BASE + 47,  	"tp0_sync")
#define RTK_PINCTRL_PIN_SB2_tp0_valid 				PINCTRL_PIN(P_SB2_BASE + 46,  	"tp0_valid")
#define RTK_PINCTRL_PIN_SB2_tp0_clk 				PINCTRL_PIN(P_SB2_BASE + 45,  	"tp0_clk")
//Rvd:12~15
#define RTK_PINCTRL_PIN_SB2_tp1_data 				PINCTRL_PIN(P_SB2_BASE + 40,  	"tp1_data")
#define RTK_PINCTRL_PIN_SB2_tp1_sync 				PINCTRL_PIN(P_SB2_BASE + 43,  	"tp1_sync")
#define RTK_PINCTRL_PIN_SB2_tp1_valid 				PINCTRL_PIN(P_SB2_BASE + 42,  	"tp1_valid")
#define RTK_PINCTRL_PIN_SB2_tp1_clk 				PINCTRL_PIN(P_SB2_BASE + 41,  	"tp1_clk")
//Rvd:24~31


/**********************************************************************************
* sb2_muxpad3
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_i2c_sda_1				PINCTRL_PIN(P_SB2_BASE + 52,  	"i2c_sda_1")
#define RTK_PINCTRL_PIN_SB2_i2c_scl_1 				PINCTRL_PIN(P_SB2_BASE + 51,  	"i2c_scl_1")
#define RTK_PINCTRL_PIN_SB2_i2c_sda_4				PINCTRL_PIN(P_SB2_BASE + 54,  	"i2c_sda_4")
#define RTK_PINCTRL_PIN_SB2_i2c_scl_4 				PINCTRL_PIN(P_SB2_BASE + 53,  	"i2c_scl_4")
#define RTK_PINCTRL_PIN_SB2_i2c_sda_5				PINCTRL_PIN(P_SB2_BASE + 39,  	"i2c_sda_5")
#define RTK_PINCTRL_PIN_SB2_i2c_scl_5 				PINCTRL_PIN(P_SB2_BASE + 38,  	"i2c_scl_5")
#define RTK_PINCTRL_PIN_SB2_spdif 					PINCTRL_PIN(P_SB2_BASE + 50,  	"spdif")
#define RTK_PINCTRL_PIN_SB2_hdmi_hpd				PINCTRL_PIN(P_SB2_BASE + 49,  	"hdmi_hpd")
#define RTK_PINCTRL_PIN_SB2_usb_id					PINCTRL_PIN(P_SB2_BASE + 48,  	"usb_id")
#define RTK_PINCTRL_PIN_SB2_hi_loc					PINCTRL_PIN(P_SB2_BASE + 103,  	"hi_loc")
#define RTK_PINCTRL_PIN_SB2_ejtag_scpu_loc			PINCTRL_PIN(P_SB2_BASE + 104,  	"ejtag_scpu_loc")
#define RTK_PINCTRL_PIN_SB2_sensor_stb_1			PINCTRL_PIN(P_SB2_BASE + 59,  	"sensor_stb_1")
#define RTK_PINCTRL_PIN_SB2_sensor_stb_0 			PINCTRL_PIN(P_SB2_BASE + 58,  	"sensor_stb_0")
#define RTK_PINCTRL_PIN_SB2_sensor_rst				PINCTRL_PIN(P_SB2_BASE + 57,  	"sensor_rst")
#define RTK_PINCTRL_PIN_SB2_sensor_cko_1			PINCTRL_PIN(P_SB2_BASE + 56,  	"sensor_cko_1")
#define RTK_PINCTRL_PIN_SB2_sensor_cko_0			PINCTRL_PIN(P_SB2_BASE + 55,  	"sensor_cko_0")


/**********************************************************************************
* sb2_muxpad4
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_gpio_0					PINCTRL_PIN(P_SB2_BASE + 0,  	"gpio_0")
#define RTK_PINCTRL_PIN_SB2_gpio_1					PINCTRL_PIN(P_SB2_BASE + 1,  	"gpio_1")
#define RTK_PINCTRL_PIN_SB2_gpio_2					PINCTRL_PIN(P_SB2_BASE + 2,  	"gpio_2")
#define RTK_PINCTRL_PIN_SB2_gpio_3					PINCTRL_PIN(P_SB2_BASE + 3,  	"gpio_3")
#define RTK_PINCTRL_PIN_SB2_gpio_4					PINCTRL_PIN(P_SB2_BASE + 4,  	"gpio_4")
#define RTK_PINCTRL_PIN_SB2_gpio_5					PINCTRL_PIN(P_SB2_BASE + 5,  	"gpio_5")
#define RTK_PINCTRL_PIN_SB2_gpio_6					PINCTRL_PIN(P_SB2_BASE + 6,  	"gpio_6")
#define RTK_PINCTRL_PIN_SB2_gpio_7					PINCTRL_PIN(P_SB2_BASE + 7,  	"gpio_7")
#define RTK_PINCTRL_PIN_SB2_gpio_8					PINCTRL_PIN(P_SB2_BASE + 8,  	"gpio_8")
//Rvd:22~31


/**********************************************************************************
* sb2_muxpad5
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_sf_en					PINCTRL_PIN(P_SB2_BASE + 105,  	"sf_en")
#define RTK_PINCTRL_PIN_SB2_arm_trace_dbg_en		PINCTRL_PIN(P_SB2_BASE + 106,  	"arm_trace_dbg_en")
#define RTK_PINCTRL_PIN_SB2_ao_loc					PINCTRL_PIN(P_SB2_BASE + 107,  	"ao_loc")
#define RTK_PINCTRL_PIN_SB2_sdio_loc				PINCTRL_PIN(P_SB2_BASE + 108,  	"sdio_loc")
#define RTK_PINCTRL_PIN_SB2_ur1_loc					PINCTRL_PIN(P_SB2_BASE + 109,  	"ur1_loc")
//Rvd:8~31


/**********************************************************************************
* sb2_muxpad6
**********************************************************************************/
#define RTK_PINCTRL_PIN_SB2_sdio_data_4				PINCTRL_PIN(P_SB2_BASE + 111,  	"sdio_data_4")
#define RTK_PINCTRL_PIN_SB2_sdio_data_5				PINCTRL_PIN(P_SB2_BASE + 112,  	"sdio_data_5")
#define RTK_PINCTRL_PIN_SB2_sdio_data_6				PINCTRL_PIN(P_SB2_BASE + 113,  	"sdio_data_6")
#define RTK_PINCTRL_PIN_SB2_sdio_data_7				PINCTRL_PIN(P_SB2_BASE + 114,  	"sdio_data_7")
//Rvd:8~31



/**********************************************************************************
* iso_muxpad0
**********************************************************************************/
#define RTK_PINCTRL_PIN_PISO_vfd_d					PINCTRL_PIN(P_ISO_BASE + 6, 	"vfd_d")
#define RTK_PINCTRL_PIN_PISO_vfd_clk 				PINCTRL_PIN(P_ISO_BASE + 5,  	"vfd_clk")
#define RTK_PINCTRL_PIN_PISO_vfd_cs_n 				PINCTRL_PIN(P_ISO_BASE + 4, 	"vfd_cs_n")
#define RTK_PINCTRL_PIN_PISO_ir_rx 					PINCTRL_PIN(P_ISO_BASE + 7,  	"ir_rx")
#define RTK_PINCTRL_PIN_PISO_ir_tx					PINCTRL_PIN(P_ISO_BASE + 8, 	"ir_tx")
//Rvd:10~11
#define RTK_PINCTRL_PIN_PISO_ur1_rx 				PINCTRL_PIN(P_ISO_BASE + 11,  	"ur1_rx")
#define RTK_PINCTRL_PIN_PISO_ur1_tx 				PINCTRL_PIN(P_ISO_BASE + 12,  	"ur1_tx")
#define RTK_PINCTRL_PIN_PISO_ur1_rts_n				PINCTRL_PIN(P_ISO_BASE + 14,  	"ur1_rts_n")
#define RTK_PINCTRL_PIN_PISO_ur1_cts_n				PINCTRL_PIN(P_ISO_BASE + 13,  	"ur1_cts_n")
#define RTK_PINCTRL_PIN_PISO_ur0_rx 				PINCTRL_PIN(P_ISO_BASE + 9,  	"ur0_rx")
#define RTK_PINCTRL_PIN_PISO_ur0_tx 				PINCTRL_PIN(P_ISO_BASE + 10,  	"ur0_tx")
#define RTK_PINCTRL_PIN_PISO_i2c_scl_0 				PINCTRL_PIN(P_ISO_BASE + 15,  	"i2c_scl_0")
#define RTK_PINCTRL_PIN_PISO_i2c_sda_0				PINCTRL_PIN(P_ISO_BASE + 16,  	"i2c_sda_0")
#define RTK_PINCTRL_PIN_PISO_etn_led_link 			PINCTRL_PIN(P_ISO_BASE + 17,  	"etn_led_link")
#define RTK_PINCTRL_PIN_PISO_etn_led_rxtx 			PINCTRL_PIN(P_ISO_BASE + 18,  	"etn_led_rxtx")


/**********************************************************************************
* iso_muxpad1
**********************************************************************************/
#define RTK_PINCTRL_PIN_PISO_i2c_scl_6				PINCTRL_PIN(P_ISO_BASE + 19,  	"i2c_scl_6")
#define RTK_PINCTRL_PIN_PISO_i2c_sda_6 				PINCTRL_PIN(P_ISO_BASE + 20,  	"i2c_sda_6")
//Rvd:4~5
#define RTK_PINCTRL_PIN_PISO_iso_gpio_2				PINCTRL_PIN(P_ISO_BASE + 2,		"iso_gpio_2")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_3				PINCTRL_PIN(P_ISO_BASE + 3,		"iso_gpio_3")
//Rvd:12~23
#define RTK_PINCTRL_PIN_PISO_pwm_23_open_drain_switch	PINCTRL_PIN(P_ISO_BASE + 40,"pwm_23_open_drain_switch")
#define RTK_PINCTRL_PIN_PISO_pwm_01_open_drain_switch	PINCTRL_PIN(P_ISO_BASE + 41,"pwm_01_open_drain_switch")
//Rvd:26~27
#define RTK_PINCTRL_PIN_PISO_ejtag_avcpu_loc		PINCTRL_PIN(P_ISO_BASE + 42,	"ejtag_avcpu_loc")
#define RTK_PINCTRL_PIN_PISO_ai_loc					PINCTRL_PIN(P_ISO_BASE + 43,	"ai_loc")


/**********************************************************************************
* iso_muxpad2
**********************************************************************************/
#define RTK_PINCTRL_PIN_PISO_rgmii_txc				PINCTRL_PIN(P_ISO_BASE + 39,	"rgmii_txc")
#define RTK_PINCTRL_PIN_PISO_rgmii_tx_ctl			PINCTRL_PIN(P_ISO_BASE + 26,	"rgmii_tx_ctl")
#define RTK_PINCTRL_PIN_PISO_rgmii_txd_0			PINCTRL_PIN(P_ISO_BASE + 27,	"rgmii_txd_0")
#define RTK_PINCTRL_PIN_PISO_rgmii_txd_1			PINCTRL_PIN(P_ISO_BASE + 28,	"rgmii_txd_1")
#define RTK_PINCTRL_PIN_PISO_rgmii_txd_2			PINCTRL_PIN(P_ISO_BASE + 29,	"rgmii_txd_2")
#define RTK_PINCTRL_PIN_PISO_rgmii_txd_3			PINCTRL_PIN(P_ISO_BASE + 30,	"rgmii_txd_3")
#define RTK_PINCTRL_PIN_PISO_rgmii_rxc				PINCTRL_PIN(P_ISO_BASE + 31,	"rgmii_rxc")
#define RTK_PINCTRL_PIN_PISO_rgmii_rx_ctl			PINCTRL_PIN(P_ISO_BASE + 32,	"rgmii_rx_ctl")
#define RTK_PINCTRL_PIN_PISO_rgmii_rxd_0			PINCTRL_PIN(P_ISO_BASE + 33,	"rgmii_rxd_0")
#define RTK_PINCTRL_PIN_PISO_rgmii_rxd_1			PINCTRL_PIN(P_ISO_BASE + 34,	"rgmii_rxd_1")
#define RTK_PINCTRL_PIN_PISO_rgmii_rxd_2			PINCTRL_PIN(P_ISO_BASE + 35,	"rgmii_rxd_2")
#define RTK_PINCTRL_PIN_PISO_rgmii_rxd_3			PINCTRL_PIN(P_ISO_BASE + 36,	"rgmii_rxd_3")
#define RTK_PINCTRL_PIN_PISO_rgmii_mdio				PINCTRL_PIN(P_ISO_BASE + 37,	"rgmii_mdio")
#define RTK_PINCTRL_PIN_PISO_rgmii_mdc				PINCTRL_PIN(P_ISO_BASE + 38,	"rgmii_mdc")
//Rvd:28~31


/**********************************************************************************
* iso_muxpad3
**********************************************************************************/
#define RTK_PINCTRL_PIN_PISO_iso_gpio_21 				PINCTRL_PIN(P_ISO_BASE + 21,	"iso_gpio_21")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_22 				PINCTRL_PIN(P_ISO_BASE + 22,	"iso_gpio_22")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_23 				PINCTRL_PIN(P_ISO_BASE + 23,	"iso_gpio_23")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_24 				PINCTRL_PIN(P_ISO_BASE + 24,	"iso_gpio_24")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_25 				PINCTRL_PIN(P_ISO_BASE + 25,	"iso_gpio_25")
//Rvd:10~31


#define RTK_PINCTRL_PIN_SB2_gpio_60					PINCTRL_PIN(P_SB2_BASE + 60, 	"gpio_60")
#define RTK_PINCTRL_PIN_SB2_gpio_61 				PINCTRL_PIN(P_SB2_BASE + 61,	"gpio_61")
#define RTK_PINCTRL_PIN_SB2_gpio_62 				PINCTRL_PIN(P_SB2_BASE + 62,	"gpio_62")
#define RTK_PINCTRL_PIN_SB2_gpio_63 				PINCTRL_PIN(P_SB2_BASE + 63,	"gpio_63")
#define RTK_PINCTRL_PIN_SB2_gpio_64 				PINCTRL_PIN(P_SB2_BASE + 64,	"gpio_64")
#define RTK_PINCTRL_PIN_SB2_gpio_65 				PINCTRL_PIN(P_SB2_BASE + 65,	"gpio_65")
#define RTK_PINCTRL_PIN_SB2_gpio_66 				PINCTRL_PIN(P_SB2_BASE + 66,	"gpio_66")
#define RTK_PINCTRL_PIN_SB2_gpio_67 				PINCTRL_PIN(P_SB2_BASE + 67,	"gpio_67")
#define RTK_PINCTRL_PIN_SB2_gpio_68 				PINCTRL_PIN(P_SB2_BASE + 68,	"gpio_68")
#define RTK_PINCTRL_PIN_SB2_gpio_69 				PINCTRL_PIN(P_SB2_BASE + 69,	"gpio_69")
#define RTK_PINCTRL_PIN_SB2_gpio_70 				PINCTRL_PIN(P_SB2_BASE + 70,	"gpio_70")
#define RTK_PINCTRL_PIN_SB2_gpio_71 				PINCTRL_PIN(P_SB2_BASE + 71,	"gpio_71")
#define RTK_PINCTRL_PIN_SB2_gpio_72 				PINCTRL_PIN(P_SB2_BASE + 72,	"gpio_72")
#define RTK_PINCTRL_PIN_SB2_gpio_73 				PINCTRL_PIN(P_SB2_BASE + 73,	"gpio_73")
#define RTK_PINCTRL_PIN_SB2_gpio_74 				PINCTRL_PIN(P_SB2_BASE + 74,	"gpio_74")
#define RTK_PINCTRL_PIN_SB2_gpio_75 				PINCTRL_PIN(P_SB2_BASE + 75,	"gpio_75")
#define RTK_PINCTRL_PIN_SB2_gpio_76 				PINCTRL_PIN(P_SB2_BASE + 76,	"gpio_76")
#define RTK_PINCTRL_PIN_SB2_gpio_77 				PINCTRL_PIN(P_SB2_BASE + 77,	"gpio_77")
#define RTK_PINCTRL_PIN_SB2_gpio_78 				PINCTRL_PIN(P_SB2_BASE + 78,	"gpio_78")
#define RTK_PINCTRL_PIN_SB2_gpio_79 				PINCTRL_PIN(P_SB2_BASE + 79,	"gpio_79")
#define RTK_PINCTRL_PIN_SB2_gpio_80 				PINCTRL_PIN(P_SB2_BASE + 80,	"gpio_80")
#define RTK_PINCTRL_PIN_SB2_gpio_81 				PINCTRL_PIN(P_SB2_BASE + 81,	"gpio_81")
#define RTK_PINCTRL_PIN_SB2_gpio_82 				PINCTRL_PIN(P_SB2_BASE + 82,	"gpio_82")
#define RTK_PINCTRL_PIN_SB2_gpio_83 				PINCTRL_PIN(P_SB2_BASE + 83,	"gpio_83")
#define RTK_PINCTRL_PIN_SB2_gpio_84 				PINCTRL_PIN(P_SB2_BASE + 84,	"gpio_84")
#define RTK_PINCTRL_PIN_SB2_gpio_85 				PINCTRL_PIN(P_SB2_BASE + 85,	"gpio_85")
#define RTK_PINCTRL_PIN_SB2_gpio_86 				PINCTRL_PIN(P_SB2_BASE + 86,	"gpio_86")
#define RTK_PINCTRL_PIN_SB2_gpio_87 				PINCTRL_PIN(P_SB2_BASE + 87,	"gpio_87")
#define RTK_PINCTRL_PIN_SB2_gpio_88 				PINCTRL_PIN(P_SB2_BASE + 88,	"gpio_88")
#define RTK_PINCTRL_PIN_SB2_gpio_89 				PINCTRL_PIN(P_SB2_BASE + 89,	"gpio_89")
#define RTK_PINCTRL_PIN_SB2_gpio_90 				PINCTRL_PIN(P_SB2_BASE + 90,	"gpio_90")
#define RTK_PINCTRL_PIN_SB2_gpio_91 				PINCTRL_PIN(P_SB2_BASE + 91,	"gpio_91")
#define RTK_PINCTRL_PIN_SB2_gpio_92 				PINCTRL_PIN(P_SB2_BASE + 92,	"gpio_92")
#define RTK_PINCTRL_PIN_SB2_gpio_93 				PINCTRL_PIN(P_SB2_BASE + 93,	"gpio_93")
#define RTK_PINCTRL_PIN_SB2_gpio_94 				PINCTRL_PIN(P_SB2_BASE + 94,	"gpio_94")
#define RTK_PINCTRL_PIN_SB2_gpio_95 				PINCTRL_PIN(P_SB2_BASE + 95,	"gpio_95")
#define RTK_PINCTRL_PIN_SB2_gpio_96 				PINCTRL_PIN(P_SB2_BASE + 96,	"gpio_96")
#define RTK_PINCTRL_PIN_SB2_gpio_97 				PINCTRL_PIN(P_SB2_BASE + 97,	"gpio_97")
#define RTK_PINCTRL_PIN_SB2_gpio_98 				PINCTRL_PIN(P_SB2_BASE + 98,	"gpio_98")
#define RTK_PINCTRL_PIN_SB2_gpio_99 				PINCTRL_PIN(P_SB2_BASE + 99,	"gpio_99")
#define RTK_PINCTRL_PIN_SB2_gpio_100 				PINCTRL_PIN(P_SB2_BASE + 100,	"gpio_100")
#define RTK_PINCTRL_PIN_SB2_gpio_101 				PINCTRL_PIN(P_SB2_BASE + 101,	"gpio_101")
#define RTK_PINCTRL_PIN_SB2_gpio_102				PINCTRL_PIN(P_SB2_BASE + 102,	"gpio_102")

#define RTK_PINCTRL_PIN_PISO_iso_gpio_0					PINCTRL_PIN(P_ISO_BASE + 0, 	"iso_gpio0")
#define RTK_PINCTRL_PIN_PISO_iso_gpio_1					PINCTRL_PIN(P_ISO_BASE + 1, 	"iso_gpio1")


struct rtk119x_pin_regmap{
	u16 pmux_regoff;
	u16 pmux_regbit;
	u16 pmux_regbitmsk;
	u16 pcof_regoff;
	u16 pcof_regbit;
	u16 pcof_cur_strgh;//0 : 2&4mA   1:4&8mA
};

#define PADDRI_4_8 1
#define PADDRI_2_4 0
#define PADDRI_UNSUPPORT 0xFFFF

#define PCOF_UNSUPPORT 0xFFFF
#define PMUX_UNSUPPORT 0xFFFF //GPIO[60]~GPIO[102]

static const struct rtk119x_pin_regmap pin_regmap[] = {
	////////////////////////////sb2_muxpad////////////////////////////
	{.pmux_regoff=0x910,	.pmux_regbit= 0, .pmux_regbitmsk=0x7,	.pcof_regoff=0x938, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 0,	"gpio_0")
	{.pmux_regoff=0x910,	.pmux_regbit= 3, .pmux_regbitmsk=0x7,	.pcof_regoff=0x938, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 1,	"gpio_1")
	{.pmux_regoff=0x910,	.pmux_regbit= 6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x938, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 2,	"gpio_2")
	{.pmux_regoff=0x910,	.pmux_regbit= 9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x938, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 3,	"gpio_3")
	{.pmux_regoff=0x910,	.pmux_regbit=12, .pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 4,	"gpio_4")
	{.pmux_regoff=0x910,	.pmux_regbit=14, .pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 5,	"gpio_5")
	{.pmux_regoff=0x910,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 6,	"gpio_6")
	{.pmux_regoff=0x910,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 7,	"gpio_7")
	{.pmux_regoff=0x910,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 8,	"gpio_8")
	{.pmux_regoff=0x900,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 9,	"nf_dd_0")
	{.pmux_regoff=0x900,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 10,	"nf_dd_1")
	{.pmux_regoff=0x900,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 11,	"nf_dd_2")
	{.pmux_regoff=0x900,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 12, 	"nf_dd_3")
	{.pmux_regoff=0x900,	.pmux_regbit=24, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 13, 	"nf_dd_4")
	{.pmux_regoff=0x900,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 14, 	"nf_dd_5")
	{.pmux_regoff=0x900,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 15, 	"nf_dd_6")
	{.pmux_regoff=0x900,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=0x91C, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 16, 	"nf_dd_7")
	{.pmux_regoff=0x900,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 17, 	"nf_rdy")
	{.pmux_regoff=0x900,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 18, 	"nf_rd_n")
	{.pmux_regoff=0x900,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 19, 	"nf_wr_n")
	{.pmux_regoff=0x900,	.pmux_regbit= 8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 20,	"nf_ale")
	{.pmux_regoff=0x900,	.pmux_regbit=10, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 21, 	"nf_cle")
	{.pmux_regoff=0x900,	.pmux_regbit=12, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 22,	"nf_ce_n_0")
	{.pmux_regoff=0x900,	.pmux_regbit=14, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 23, 	"nf_ce_n_1")
	{.pmux_regoff=0x904,	.pmux_regbit=24, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 24, 	"mmc_data_0")
	{.pmux_regoff=0x904,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 25, 	"mmc_data_1")
	{.pmux_regoff=0x904,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 26, 	"mmc_data_2")
	{.pmux_regoff=0x904,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 27, 	"mmc_data_3")
	{.pmux_regoff=0x904,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 28,	"mmc_clk")
	{.pmux_regoff=0x904,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 29,	"mmc_cmd")
	{.pmux_regoff=0x904,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 30,	"mmc_wp")
	{.pmux_regoff=0x904,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x920, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 31, 	"mmc_cd")
	{.pmux_regoff=0x904,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 32,	"sdio_clk")
	{.pmux_regoff=0x904,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 33, 	"sdio_data_0")
	{.pmux_regoff=0x904,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 34, 	"sdio_data_1")
	{.pmux_regoff=0x904,	.pmux_regbit= 8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 35, 	"sdio_data_2")
	{.pmux_regoff=0x904,	.pmux_regbit=10, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 36, 	"sdio_data_3")
	{.pmux_regoff=0x904,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 37,	"sdio_cmd")
	{.pmux_regoff=0x90C,	.pmux_regbit=10, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 38, 	"i2c_scl_5")
	{.pmux_regoff=0x90C,	.pmux_regbit= 8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x924, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 39, 	"i2c_sda_5")
	{.pmux_regoff=0x908,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x92C, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 40, 	"tp1_data")
	{.pmux_regoff=0x908,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x92C, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 41,	"tp1_clk")
	{.pmux_regoff=0x908,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x92C, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 42,	"tp1_valid")
	{.pmux_regoff=0x908,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x92C, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 43,	"tp1_sync")
	{.pmux_regoff=0x908,	.pmux_regbit= 0, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 44, 	"tp0_data")
	{.pmux_regoff=0x908,	.pmux_regbit= 9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 45,	"tp0_clk")
	{.pmux_regoff=0x908,	.pmux_regbit= 6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 46,	"tp0_valid")
	{.pmux_regoff=0x908,	.pmux_regbit= 3, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 47,	"tp0_sync")
	{.pmux_regoff=0x90C,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 48,	"usb_id")
	{.pmux_regoff=0x90C,	.pmux_regbit=14, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 49,	"hdmi_hpd")
	{.pmux_regoff=0x90C,	.pmux_regbit=12, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 50,	"spdif")		//NO SMT
	{.pmux_regoff=0x90C,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 51,	"i2c_scl_1")
	{.pmux_regoff=0x90C,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 52,	"i2c_sda_1")
	{.pmux_regoff=0x90C,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 53, 	"i2c_scl_4")
	{.pmux_regoff=0x90C,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_4_8}, //(P_SB2_BASE + 54,	"i2c_sda_4")
	{.pmux_regoff=0x90C,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 55, 	"sensor_cko_0")
	{.pmux_regoff=0x90C,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 56, 	"sensor_cko_1")
	{.pmux_regoff=0x90C,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 57, 	"sensor_rst")
	{.pmux_regoff=0x90C,	.pmux_regbit=24, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 58, 	"sensor_stb_0")
	{.pmux_regoff=0x90C,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x93C, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_SB2_BASE + 59, 	"sensor_stb_1")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 60, 	"gpio_60")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 61, 	"gpio_61")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 62, 	"gpio_62")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 63, 	"gpio_63")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 64, 	"gpio_64")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 65, 	"gpio_65")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 66, 	"gpio_66")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 67, 	"gpio_67")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 68, 	"gpio_68")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 69, 	"gpio_69")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 70, 	"gpio_70")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 71, 	"gpio_71")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 72, 	"gpio_72")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 73, 	"gpio_73")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 74, 	"gpio_74")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 75, 	"gpio_75")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 76, 	"gpio_76")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 77, 	"gpio_77")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 78, 	"gpio_78")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 79, 	"gpio_79")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 80, 	"gpio_80")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 81, 	"gpio_81")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 82, 	"gpio_82")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 83, 	"gpio_83")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 84, 	"gpio_84")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 85, 	"gpio_85")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 86, 	"gpio_86")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 87, 	"gpio_87")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 88, 	"gpio_88")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 89, 	"gpio_89")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 90, 	"gpio_90")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 91, 	"gpio_91")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 92, 	"gpio_92")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 93, 	"gpio_93")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 94, 	"gpio_94")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 95, 	"gpio_95")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 96, 	"gpio_96")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 97, 	"gpio_97")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 98, 	"gpio_98")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 99, 	"gpio_99")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 100, 	"gpio_100")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 101, 	"gpio_101")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 102, 	"gpio_102")
	{.pmux_regoff=0x90C,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 103, 	"hi_loc")
	{.pmux_regoff=0x90C,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 104, 	"ejtag_scpu_loc")
	{.pmux_regoff=0x914,	.pmux_regbit= 0, .pmux_regbitmsk=0x1,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 105, 	"sf_en")
	{.pmux_regoff=0x914,	.pmux_regbit= 1, .pmux_regbitmsk=0x1,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 106, 	"arm_trace_dbg_en")
	{.pmux_regoff=0x914,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 107, 	"ao_loc")
	{.pmux_regoff=0x914,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 108,	"sdio_loc")
	{.pmux_regoff=0x914,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_SB2_BASE + 109,	"ur1_loc")
	{.pmux_regoff=0x900,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x918, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 110,	"nf_dqs")
	{.pmux_regoff=0x944,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x948, .pcof_regbit= 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 111,	"sdio_data_4")
	{.pmux_regoff=0x944,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x948, .pcof_regbit= 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 112,	"sdio_data_5")
	{.pmux_regoff=0x944,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x948, .pcof_regbit= 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 113,	"sdio_data_6")
	{.pmux_regoff=0x944,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x948, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_SB2_BASE + 114,	"sdio_data_7")

	////////////////////////////iso_muxpad////////////////////////////
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0x0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 0,	"iso_gpio_0")
	{.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0x0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 1,	"iso_gpio_1)
	{.pmux_regoff=0x314,	.pmux_regbit= 6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x300, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 2,	"iso_gpio_2")
	{.pmux_regoff=0x314,	.pmux_regbit= 9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x300, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 3,	"iso_gpio_3")
	{.pmux_regoff=0x310,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 4,	"vfd_cs_n")
	{.pmux_regoff=0x310,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 5,	"vfd_clk")
	{.pmux_regoff=0x310,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 6,	"vfd_d")
	{.pmux_regoff=0x310,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 7,	"ir_rx")
	{.pmux_regoff=0x310,	.pmux_regbit= 8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 8,	"ir_tx")
	{.pmux_regoff=0x310,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 9,	"ur0_rx")
	{.pmux_regoff=0x310,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 10, 	"ur0_tx")
	{.pmux_regoff=0x310,	.pmux_regbit=12, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 11,	"ur1_rx")
	{.pmux_regoff=0x310,	.pmux_regbit=14, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 12,	"ur1_tx")
	{.pmux_regoff=0x310,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 13, 	"ur1_cts_n")
	{.pmux_regoff=0x310,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 14,	"ur1_rts_n")
	{.pmux_regoff=0x310,	.pmux_regbit=24, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 15, 	"i2c_scl_0")
	{.pmux_regoff=0x310,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 16, 	"i2c_sda_0")
	{.pmux_regoff=0x310,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 17, 	"etn_led_link")
	{.pmux_regoff=0x310,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 18, 	"etn_led_rxtx")
	{.pmux_regoff=0x314,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 19, 	"i2c_scl_6")
	{.pmux_regoff=0x314,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 20, 	"i2c_sda_6")
	{.pmux_regoff=0x328,	.pmux_regbit=24, .pmux_regbitmsk=0x1,	.pcof_regoff=0x318, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 21, 	"iso_gpio_21")
	{.pmux_regoff=0x328,	.pmux_regbit=25, .pmux_regbitmsk=0x1,	.pcof_regoff=0x318, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 22, 	"iso_gpio_22")
	{.pmux_regoff=0x328,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 23, 	"iso_gpio_23")
	{.pmux_regoff=0x328,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 24, 	"iso_gpio_24")
	{.pmux_regoff=0x328,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 25, 	"iso_gpio_25")
	{.pmux_regoff=0x324,	.pmux_regbit= 2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 26, 	"rgmii_tx_ctl")
	{.pmux_regoff=0x324,	.pmux_regbit= 4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 27, 	"rgmii_txd_0")
	{.pmux_regoff=0x324,	.pmux_regbit= 6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 28, 	"rgmii_txd_1")
	{.pmux_regoff=0x324,	.pmux_regbit= 8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 29, 	"rgmii_txd_2")
	{.pmux_regoff=0x324,	.pmux_regbit=10, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 30, 	"rgmii_txd_3")
	{.pmux_regoff=0x324,	.pmux_regbit=12, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=24, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 31, 	"rgmii_rxc")
	{.pmux_regoff=0x324,	.pmux_regbit=14, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=28, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 32, 	"rgmii_rx_ctl")
	{.pmux_regoff=0x324,	.pmux_regbit=16, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 33, 	"rgmii_rxd_0")
	{.pmux_regoff=0x324,	.pmux_regbit=18, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 34, 	"rgmii_rxd_1")
	{.pmux_regoff=0x324,	.pmux_regbit=20, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 35, 	"rgmii_rxd_2")
	{.pmux_regoff=0x324,	.pmux_regbit=22, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=12, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 36, 	"rgmii_rxd_3")
	{.pmux_regoff=0x324,	.pmux_regbit=24, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=16, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 37, 	"rgmii_mdio")
	{.pmux_regoff=0x324,	.pmux_regbit=26, .pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=20, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 38, 	"rgmii_mdc")
	{.pmux_regoff=0x324,	.pmux_regbit= 0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x31C, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 39, 	"rgmii_txc")
	{.pmux_regoff=0x314,	.pmux_regbit=24, .pmux_regbitmsk=0x1,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_ISO_BASE + 40, 	"pwm_23_open_drain_switch")
	{.pmux_regoff=0x314,	.pmux_regbit=25, .pmux_regbitmsk=0x1,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_ISO_BASE + 41, 	"pwm_01_open_drain_switch")
	{.pmux_regoff=0x314,	.pmux_regbit=28, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_ISO_BASE + 42, 	"ejtag_avcpu_loc")
	{.pmux_regoff=0x314,	.pmux_regbit=30, .pmux_regbitmsk=0x3,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0}, //(P_ISO_BASE + 43, 	"ai_loc")

};

#define RTK119X_PCONF_SCHM 3
#define RTK119X_PCONF_CURR 2
#define RTK119X_PCONF_PULEN 1
#define RTK119X_PCONF_PULSEL 0

/*

#define RTK119X_PIN_NAME_MAX_LEN	5

#define BANK_MEM_SIZE		0x24
#define MUX_REGS_OFFSET	0x0
#define DATA_REGS_OFFSET	0x10
#define DLEVEL_REGS_OFFSET	0x14
#define PULL_REGS_OFFSET	0x1c
*/

#define PINS_OF_CRTBANK				115
#define MUX_PINS_PER_REG			16
#define MUX_PINS_NUMBER_MASK		0xffff0000
#define MUX_PINS_NUMBER_MASK_OFF	16
#define MUX_REG_BITNUM_MASK			0x0000ff00
#define MUX_REG_BITNUM_MASK_OFF		8
#define MUX_REG_BITOFF_MASK			0x000000ff




/*
#define MUX_PINS_BITS		4
#define MUX_PINS_MASK		0x0f
#define DATA_PINS_PER_REG	32
#define DATA_PINS_BITS		1
#define DATA_PINS_MASK		0x01
#define DLEVEL_PINS_PER_REG	16
#define DLEVEL_PINS_BITS	2
#define DLEVEL_PINS_MASK	0x03
#define PULL_PINS_PER_REG	16
#define PULL_PINS_BITS		2
#define PULL_PINS_MASK		0x03
*/
struct RTK119X_desc_function {
	const char	*name;
	u8		muxval;
};

struct RTK119X_desc_pin {
	struct pinctrl_pin_desc		pin;
	struct RTK119X_desc_function	*functions;
};

struct RTK119X_pinctrl_desc {
	const struct RTK119X_desc_pin	*pins;
	int				npins;
	struct pinctrl_gpio_range	*ranges;
	int				nranges;
};

struct RTK119X_pinctrl_function {
	const char	*name;
	const char	**groups;
	unsigned	ngroups;
};

struct RTK119X_pinctrl_group {
	const char	*name;
	unsigned long	config;
	unsigned	pin;
};

struct RTK119X_pinctrl {
	void __iomem			*crt_membase;
	void __iomem			*iso_membase;
//	struct gpio_chip		*chip;
	struct RTK119X_pinctrl_desc	*desc;
	struct device			*dev;
	struct RTK119X_pinctrl_function	*functions;
	unsigned			nfunctions;
	struct RTK119X_pinctrl_group	*groups;
	unsigned			ngroups;
	struct pinctrl_dev		*pctl_dev;
};

#define RTK119X_PIN(_pin, ...)					\
	{							\
		.pin = _pin,					\
		.functions = (struct RTK119X_desc_function[]){	\
			__VA_ARGS__, { } },			\
	}

#define RTK119X_FUNCTION(_val, _name)				\
	{							\
		.name = _name,					\
		.muxval = _val,					\
	}

static const struct RTK119X_desc_pin rtk119x_pins[] = {
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_0,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "uart1_loc_misc"),
		RTK119X_FUNCTION(0x3, "hif_loc_misc"),
		RTK119X_FUNCTION(0x4, "gspi")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_1,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "uart1_loc_misc"),
		RTK119X_FUNCTION(0x3, "hif_loc_misc"),
		RTK119X_FUNCTION(0x4, "gspi")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_2,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "uart1_loc_misc"),
		RTK119X_FUNCTION(0x3, "hif_loc_misc"),
		RTK119X_FUNCTION(0x4, "gspi")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_3,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "uart1_loc_misc"),
		RTK119X_FUNCTION(0x3, "hif_loc_misc"),
		RTK119X_FUNCTION(0x4, "gspi")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_4,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_misc"),
		RTK119X_FUNCTION(0x3, "ao_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_5,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_misc"),
		RTK119X_FUNCTION(0x3, "ao_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_6,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_misc"),
		RTK119X_FUNCTION(0x3, "ao_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_7,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_misc"),
		RTK119X_FUNCTION(0x3, "ao_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_8,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_4,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "hif_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_5,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_6,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dd_7,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_rdy,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_rd_n,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_wr_n,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "hif_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_ale,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "hif_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_cle,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "hif_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_ce_n_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_ce_n_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_data_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_data_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_data_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_data_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_clk,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_cmd,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x2, "sdio"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_wp,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_cr")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_mmc_cd,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "mmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_clk,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_cmd,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_scl_5,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c5"),
		RTK119X_FUNCTION(0x3, "nand")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_sda_5,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c5"),
		RTK119X_FUNCTION(0x3, "nand")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp1_data,
		RTK119X_FUNCTION(0x0, "tp1"),
		RTK119X_FUNCTION(0x1, "tp0"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "i2c3")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp1_clk,
		RTK119X_FUNCTION(0x0, "tp1"),
		RTK119X_FUNCTION(0x1, "tp0"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "i2c2")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp1_valid,
		RTK119X_FUNCTION(0x0, "tp1"),
		RTK119X_FUNCTION(0x1, "tp0"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "i2c3")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp1_sync,
		RTK119X_FUNCTION(0x0, "tp1"),
		RTK119X_FUNCTION(0x1, "tp0"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "i2c2")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp0_data,
		RTK119X_FUNCTION(0x0, "tp0"),
		RTK119X_FUNCTION(0x1, "tp1"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "ao_loc_tp"),
		RTK119X_FUNCTION(0x4, "ttl")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp0_clk,
		RTK119X_FUNCTION(0x0, "tp0"),
		RTK119X_FUNCTION(0x1, "tp1"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "ao_loc_tp"),
		RTK119X_FUNCTION(0x4, "ttl")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp0_valid,
		RTK119X_FUNCTION(0x0, "tp0"),
		RTK119X_FUNCTION(0x1, "tp1"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "ao_loc_tp"),
		RTK119X_FUNCTION(0x4, "ttl")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_tp0_sync,
		RTK119X_FUNCTION(0x0, "tp0"),
		RTK119X_FUNCTION(0x1, "tp1"),
		RTK119X_FUNCTION(0x2, "gpio"),
		RTK119X_FUNCTION(0x3, "ao_loc_tp"),
		RTK119X_FUNCTION(0x4, "ttl")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_usb_id,
		RTK119X_FUNCTION(0x1, "gpio"),
		RTK119X_FUNCTION(0x2, "cpu_loop")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_hdmi_hpd,
		RTK119X_FUNCTION(0x1, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_spdif,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "spdif")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_scl_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c1")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_sda_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c1")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_scl_4,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c4"),
		RTK119X_FUNCTION(0x2, "uart2")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_i2c_sda_4,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c4"),
		RTK119X_FUNCTION(0x2, "uart2")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sensor_cko_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sensor"),
		RTK119X_FUNCTION(0x2, "uart2")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sensor_cko_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sensor"),
		RTK119X_FUNCTION(0x2, "uart2"),
		RTK119X_FUNCTION(0x3, "usb")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sensor_rst,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sensor_stb_0,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sensor_stb_1,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_60,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_61,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_62,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_63,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_64,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_65,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_66,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_67,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_68,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_69,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_70,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_71,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_72,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_73,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_74,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_75,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_76,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_77,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_78,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_79,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_80,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_81,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_82,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_83,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_84,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_85,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_86,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_87,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_88,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_89,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_90,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_91,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_92,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_93,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_94,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_95,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_96,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_97,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_98,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_99,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_100,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_101,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_gpio_102,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_hi_loc,
		RTK119X_FUNCTION(0x1, "hif_loc_misc"),
		RTK119X_FUNCTION(0x2, "hif_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_ejtag_scpu_loc,
		RTK119X_FUNCTION(0x1, "scpu_ejtag_loc_misc"),
		RTK119X_FUNCTION(0x2, "scpu_ejtag_loc_cr"),
		RTK119X_FUNCTION(0x3, "scpu_ejtag_loc_scpu")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sf_en,
		RTK119X_FUNCTION(0x0, "uart1_loc_misc"),
		RTK119X_FUNCTION(0x0, "hif_loc_misc"),
		RTK119X_FUNCTION(0x0, "gspi"),
		RTK119X_FUNCTION(0x1, "spi")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_arm_trace_dbg_en,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand"),
		RTK119X_FUNCTION(0x2, "emmc"),
		RTK119X_FUNCTION(0x3, "jtag")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_ao_loc,
		RTK119X_FUNCTION(0x1, "ao_loc_tp"),
		RTK119X_FUNCTION(0x2, "ao_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_loc,
		RTK119X_FUNCTION(0x1, "sdio_from_sdio"),
		RTK119X_FUNCTION(0x2, "sdio_from_mmc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_ur1_loc,
		RTK119X_FUNCTION(0x1, "uart1_loc_iso"),
		RTK119X_FUNCTION(0x2, "uart1_loc_misc")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_nf_dqs,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "nand")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_4,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_5,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_6,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_SB2_sdio_data_7,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "sdio")),
//////////iso pinmux////////////////
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_0,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_1,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "standby_dbg"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_usb"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_iso"),
		RTK119X_FUNCTION(0x4, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "standby_dbg"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_usb"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_iso"),
		RTK119X_FUNCTION(0x4, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_vfd_cs_n,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "vfd"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_usb"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_iso")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_vfd_clk,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "vfd"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_usb"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_iso")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_vfd_d,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "vfd"),
		RTK119X_FUNCTION(0x2, "i2c2"),
		RTK119X_FUNCTION(0x3, "avcpu_ejtag_loc_iso")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ir_rx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "irrx"),
		RTK119X_FUNCTION(0x2, "standby_dbg")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ir_tx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "irtx"),
		RTK119X_FUNCTION(0x2, "i2c3")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur0_rx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart0"),
		RTK119X_FUNCTION(0x2, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur0_tx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart0"),
		RTK119X_FUNCTION(0x2, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur1_rx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart1_loc_iso"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_ur"),
		RTK119X_FUNCTION(0x3, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur1_tx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart1_loc_iso"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_ur"),
		RTK119X_FUNCTION(0x3, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur1_cts_n,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart1_loc_iso"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_ur")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ur1_rts_n,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "uart1_loc_iso"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_ur")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_i2c_scl_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c0")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_i2c_sda_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c0")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_etn_led_link,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "etn_led"),
		RTK119X_FUNCTION(0x2, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_etn_led_rxtx,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "etn_led"),
		RTK119X_FUNCTION(0x2, "pwm")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_i2c_scl_6,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c6")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_i2c_sda_6,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "i2c6")),	
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_21,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_22,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_23,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_24,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_iso_gpio_25,
		RTK119X_FUNCTION(0x0, "gpio")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_tx_ctl,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_txd_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_txd_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_txd_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_txd_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rxc,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rx_ctl,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rxd_0,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rxd_1,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "rmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rxd_2,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_rxd_3,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_mdio,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "fephy")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_mdc,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii"),
		RTK119X_FUNCTION(0x2, "fephy")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_rgmii_txc,
		RTK119X_FUNCTION(0x0, "gpio"),
		RTK119X_FUNCTION(0x1, "rgmii")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_pwm_23_open_drain_switch,
		RTK119X_FUNCTION(0x0, "normal"),
		RTK119X_FUNCTION(0x1, "open_drain")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_pwm_01_open_drain_switch,
		RTK119X_FUNCTION(0x0, "normal"),
		RTK119X_FUNCTION(0x1, "open_drain")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ejtag_avcpu_loc,
		RTK119X_FUNCTION(0x1, "avcpu_ejtag_loc_iso"),
		RTK119X_FUNCTION(0x2, "avcpu_ejtag_loc_nf")),
	RTK119X_PIN(RTK_PINCTRL_PIN_PISO_ai_loc,
		RTK119X_FUNCTION(0x1, "ai_loc_iso_ur"),
		RTK119X_FUNCTION(0x2, "ai_loc_iso_usb")),
};

#endif /* __PINCTRL_RTK119X_H */
