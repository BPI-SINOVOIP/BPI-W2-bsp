/*
 * hdmiPhy.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "hdmiInternal.h"


/*
 * Marco or Definitions
 */
#ifndef IRQ_HANDLED
#define IRQ_HANDLED  1
#define IRQ_NONE     0
#endif


#define CLOCK_TOLERANCE()     (phy_st.clk_tolerance)
#define CLK_DEBOUNCE_CNT        7 /* Set 2, it will easy to set phy in background and influence others */
#define CLK_DEBOUNCE_SHORT_CNT  1 /* To prevent Tx HDCP handshake too fast */
#define NOCLK_DEBOUNCE_CNT      8 /* Count for confirm it's no clock, (QD980>5, has sudden no clock and clear scdc) */
#define CLK_UNSTABLE_CNT        2 /* Count for clock unstable change */

#define TMDS_CHAR_ERR_PERIOD    4
#define TMDS_CHAR_ERR_THREAD    8
#define TMDS_CHAR_ERR_MAX_LOOP  8 /* TMDS_CHAR_ERR_PERIOD*2 is safe */

#define TMDS_BIT_ERR_PERIOD     16
#define TMDS_BIT_ERR_THREAD     32
#define TMDS_BIT_ERR_MAX_LOOP   32 /* TMDS_BIT_ERR_PERIOD*2 is safe */

#define MAX_ERR_DETECT_TIMES    10

#define ManualZ0                0x12
#define HDMI_EQ_LE_NOT_ZERO_ENABLE



/* TMDS clock define */
#define TMDS_6G     5688
#define TMDS_5G     4740
#define TMDS_4G     3792
#define TMDS_3G     2844
#define TMDS_1p5G   1422


/* Fvco = (Fi*M*Prescalar*CMU_SEL_D4)/N */
HDMI_PHY_PARAM_T hdmi_phy_param[] = {
	/* 300~600 M */
	{.b_upper = 5860, .b_lower = 2844, .M_code = 16, .N_code = 0,
	 .PI_DIV = 0, .DEMUX = 1, .RATE_SEL = 0x0, .CK_LDOD = 0x3, .CK_CS = 0x3,
	 .CK_RS = 0x2, .EQ_adj = 0x2, .CDR_bias = 0x1, .CDR_KP = (0x8 << 0), .CDR_KP2 = 0x0,
	 .CDR_KI = 0x1, .CDR_KD = 0x0, .EQ_gain = 0x0, .EQ_bias = 0x1, .CK_Icp = 0x7,
	 .PR = 0x0, .pscaler = 0x0, .vsel_ldo = 7, .CMU_SEL_D4 = 0x0, .Icp_DUL = 0x0,
	 .PI_CSEL = 0x0, .PI_CURRENT = 0x0, .PI_ISEL = 0x0, .EN_CAP = 0x0, .CMU_KVCO = 0x1,
	 .band_name = "300M~600M half rate"},
	/* 150~300 M For LG UD generator issue to change Kp 5=>6 , M/N => 20/2 */
	{.b_upper = 2844, .b_lower = 1422, .M_code = 36, .N_code = 1,
	 .PI_DIV = 1, .DEMUX = 2, .RATE_SEL = 0x1, .CK_LDOD = 0x3, .CK_CS = 0x3,
	 .CK_RS = 0x2, .EQ_adj = 0x4, .CDR_bias = 0x1, .CDR_KP = (0x20 << 0), .CDR_KP2 = 0x4,
	 .CDR_KI = 0x1, .CDR_KD = 0x0, .EQ_gain = 0x1, .EQ_bias = 0x1, .CK_Icp = 0x4,
	 .PR = 0x0, .pscaler = 0x1, .vsel_ldo = 7, .CMU_SEL_D4 = 0x0, .Icp_DUL = 0x0,
	 .PI_CSEL = 0x0, .PI_CURRENT = 0x0, .PI_ISEL = 0x0, .EN_CAP = 0x0, .CMU_KVCO = 0x1,
	 .band_name = "150M~300M full rate"},
	/* 75~150 M */
	{.b_upper = 1422, .b_lower = 711, .M_code = 36, .N_code = 0,
	 .PI_DIV = 2, .DEMUX = 3, .RATE_SEL = 0x2, .CK_LDOD = 0x3, .CK_CS = 0x3,
	 .CK_RS = 0x2, .EQ_adj = 0x9, .CDR_bias = 0x1, .CDR_KP = (0x20 << 0), .CDR_KP2 = 0x0,
	 .CDR_KI = 0x0, .CDR_KD = 0x0, .EQ_gain = 0x1, .EQ_bias = 0x1, .CK_Icp = 0x6,
	 .PR = 0x1, .pscaler = 0x1, .vsel_ldo = 7, .CMU_SEL_D4 = 0x0, .Icp_DUL = 0x0,
	 .PI_CSEL = 0x0, .PI_CURRENT = 0x0, .PI_ISEL = 0x0, .EN_CAP = 0x0, .CMU_KVCO = 0x1,
	 .band_name = "75M~150M full rate+DS1"},
	/* 37.5~75M */
	{.b_upper = 711, .b_lower = 355, .M_code = 76, .N_code = 0,
	 .PI_DIV = 3, .DEMUX = 3, .RATE_SEL = 0x2, .CK_LDOD = 0x3, .CK_CS = 0x3,
	 .CK_RS = 0x2, .EQ_adj = 0x4, .CDR_bias = 0x1, .CDR_KP = (0x10 << 0), .CDR_KP2 = 0x0,
	 .CDR_KI = 0x0, .CDR_KD = 0x0, .EQ_gain = 0x1, .EQ_bias = 0x1, .CK_Icp = 0x6,
	 .PR = 0x2, .pscaler = 0x1, .vsel_ldo = 7, .CMU_SEL_D4 = 0x0, .Icp_DUL = 0x1,
	 .PI_CSEL = 0x0, .PI_CURRENT = 0x0, .PI_ISEL = 0x0, .EN_CAP = 0x0, .CMU_KVCO = 0x1,
	 .band_name = "37.5M~75M full rate+DS2"},
	/* 13.5M~ 37.5M */
	{.b_upper = 355, .b_lower = 128, .M_code = 76, .N_code = 0,
	 .PI_DIV = 4, .DEMUX = 3, .RATE_SEL = 0x2, .CK_LDOD = 0x3, .CK_CS = 0x3,
	 .CK_RS = 0x7, .EQ_adj = 0x4, .CDR_bias = 0x1, .CDR_KP = (0x10 << 0), .CDR_KP2 = 0x0,
	 .CDR_KI = 0x0, .CDR_KD = 0x0, .EQ_gain = 0x1, .EQ_bias = 0x1, .CK_Icp = 0x4,
	 .PR = 0x3, .pscaler = 0x1, .vsel_ldo = 7, .CMU_SEL_D4 = 0x1, .Icp_DUL = 0x1,
	 .PI_CSEL = 0x0, .PI_CURRENT = 0x0, .PI_ISEL = 0x0, .EN_CAP = 0x0, .CMU_KVCO = 0x1,
	 .band_name = "13.5M~37M full rate+DS3"},
};


HDMI_PHY_PARAM2_T hdmi_phy_param2[] = {
	{.fvco_upper = 6000, .fvco_lower = 5500, .CMU_KVCO = 0x1, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x4, .PI_ISEL = 0x0, .PI_CSEL = 0x0},
	{.fvco_upper = 5500, .fvco_lower = 5000, .CMU_KVCO = 0x1, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x4, .PI_ISEL = 0x0, .PI_CSEL = 0x0},
	{.fvco_upper = 5000, .fvco_lower = 4000, .CMU_KVCO = 0x1, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x1, .PI_ISEL = 0x0, .PI_CSEL = 0x1},
	{.fvco_upper = 4000, .fvco_lower = 3000, .CMU_KVCO = 0x0, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x0, .PI_ISEL = 0x1, .PI_CSEL = 0x2},
	{.fvco_upper = 3000, .fvco_lower = 2500, .CMU_KVCO = 0x0, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x0, .PI_ISEL = 0x1, .PI_CSEL = 0x3},
	{.fvco_upper = 2500, .fvco_lower = 2000, .CMU_KVCO = 0x0, .EN_CAP = 0x0, .CCO_BAND_SEL = 0x0, .PI_ISEL = 0x1, .PI_CSEL = 0x3},
};

typedef enum {
	PHY_PROC_INIT,
	PHY_PROC_RECORD,
	PHY_PROC_CLOSE_ADP,
	PHY_PROC_RECOVER_6G_LONGCABLE,
	PHY_PROC_RECOVER_6G_LONGCABLE_RECORD,
	PHY_PROC_RECOVER_6G_LONGCABLE_CLOSE_ADP,
	PHY_PROC_RECOVER_MI,
	PHY_PROC_DONE,
} HDMIRX_PHY_PROC_T;


typedef struct {
	unsigned char vth;
	unsigned char tap0;
	unsigned char tap0max;
	unsigned char tap0min;
	unsigned char tap1;
	unsigned char le;
	unsigned char lemax;
	unsigned char lemin;
	signed char tap2;
} HDMIRX_PHY_DFE_T;

typedef struct {
	unsigned int clk;
	unsigned int clk_pre;
	unsigned int clk_debounce_count;
	unsigned int clk_unstable_count;
	unsigned int noclk_debounce_count;
	unsigned int clk_tolerance;
	unsigned char clk_stable;

	unsigned char rxphy_40x;

	HDMIRX_PHY_PROC_T phy_proc_state;

	unsigned int char_err_loop;
	unsigned int char_err_occurred;
	unsigned char detect_6g_longcable;

	unsigned int bit_err_loop;
	unsigned int bit_err_occurred;

	unsigned int error_detect_count;
	HDMIRX_PHY_DFE_T dfe_t[3];

} HDMIRX_PHY_STRUCT_T;


/*
 * Variables
 */
unsigned int clock_bound_3g;
unsigned int clock_bound_1p5g;
unsigned int clock_bound_110m;
unsigned int clock_bound_45m;

HDMIRX_PHY_STRUCT_T phy_st;

unsigned int phy_isr_en;

HDMIRX_STATE_STRUCT_T hdmirx_state;


/*
 * Funtion Declarations
 */
unsigned char rxphy_measure(void);
unsigned char rxphy_is_clock_stable(unsigned int clk_tmp);
void rxphy_job(void);

void lib_hdmi_wdg_rst(unsigned char rst);
void lib_hdmi_afifo_enable(unsigned char enable);
void lib_hdmi_mac_reset(void);
//void lib_hdmi_mac_release(void);
void lib_hdmi_dfe_power(unsigned char en);
#ifdef CONFIG_POWER_SAVING_MODE
void lib_hdmi_eq_pi_power_en(unsigned char en);
#endif
void lib_hdmi_eq_bias_band_setting(unsigned int b);

void lib_hdmi_set_dfe(unsigned int b, unsigned char dfe_mode);
void lib_hdmi_set_dfe_mid_band(unsigned int b_clk, int dfe_mode);
void lib_hdmi_dfe_manual_set(void);
unsigned char lib_hdmi_dfe_tap0_fix(void);
void lib_hdmi_tap0_fix_small_swing(void);

void lib_hdmi_dfe_second_flow(unsigned int b_clk);
void lib_hdmi_load_le_max(void);
void lib_hdmi_dfe_examine_le_coef(unsigned int b_clk);
void lib_hdmi_set_dfe_close(void);
void lib_hdmi_dfe_record_enable(unsigned char onoff);
unsigned char lib_hdmi_dfe_is_record_enable(void);
void lib_hdmi_dfe_init_vth(unsigned char bgr, unsigned char value);
void lib_hdmi_dfe_init_tap0(unsigned char bgr, unsigned char value);
void lib_hdmi_dfe_init_tap1(unsigned char bgr, unsigned char value);
void lib_hdmi_dfe_init_tap2(unsigned char bgr, signed char value);
void lib_hdmi_dfe_init_le(unsigned char bgr, unsigned char value);
void lib_hdmi_dfe_load_in_adp(unsigned char bgr, unsigned int option);
unsigned char lib_hdmi_dfe_get_vth(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap0(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap0max(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap0min(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap1(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap1max(unsigned char lane);
unsigned char lib_hdmi_dfe_get_tap1min(unsigned char lane);
char lib_hdmi_dfe_get_tap2(unsigned char lane);
unsigned char lib_hdmi_dfe_get_le(unsigned char lane);
unsigned char lib_hdmi_dfe_get_lemax(unsigned char lane);
unsigned char lib_hdmi_dfe_get_lemin(unsigned char lane);

void lib_hdmi_cmu_pll_en(unsigned char enable);
void lib_hdmi_demux_ck_vcopll_rst(unsigned char rst);
void lib_hdmi_dfe_rst(unsigned char rst);
void lib_hdmi_cdr_rst(unsigned char rst);
void lib_hdmi_wdog(void);
void lib_hdmi_dfe_config_setting(void);
void lib_hdmi_set_phy_table(HDMI_PHY_PARAM_T *phy_param);
void lib_hdmi_cco_band_config(unsigned int bclk, HDMI_PHY_PARAM_T *phy_param);

unsigned char lib_hdmi_acdr_check_result(void);
void lib_hdmi_fg_koffset_manual_adjust(unsigned int r, unsigned int g, unsigned int b);
void lib_hdmi_fg_koffset_manual(void);
void lib_hdmi_fg_koffset_auto(void);
void lib_hdmi_fg_koffset_proc(void);
void lib_hdmi_fg_koffset_disable(void);
void lib_hdmi_z0_calibration(void);

void lib_hdmi_char_err_rst(unsigned char rst);
void lib_hdmi_char_err_start(unsigned char conti_mode, unsigned char period);
unsigned char lib_hdmi_char_err_det_done(void);
unsigned char lib_hdmi_char_err_get_error(unsigned int *r_err, unsigned int *g_err, unsigned int *b_err);
void lib_hdmi_bit_err_start(unsigned char conti_mode, unsigned char period);
unsigned char lib_hdmi_bit_err_det_done(void);
unsigned char lib_hdmi_bit_err_get_error(unsigned int *r_err, unsigned int *g_err, unsigned int *b_err);

#if 1/* Only for jtest */
void debug_hdmi_dfe_scan(void);
#endif


void rxphy_isr_set(unsigned char en)
{
	phy_isr_en = en;
}

void rxphy_init_struct(void)
{
	memset(&phy_st, 0, sizeof(HDMIRX_PHY_STRUCT_T));
}

int rxphy_isr(void)
{
	if (phy_isr_en) {

		if (rxphy_measure())
			rxphy_job();
		else
			hdmi_reset_video_state();

		//hdmi_check_connection_state();

		lib_hdmi2p0_scdc_update_flag();
	}

	return IRQ_HANDLED;

}

unsigned char rxphy_measure(void)
{
	unsigned int clk_tmp = 0;
	unsigned char clk_stable_prev = phy_st.clk_stable;

	if (lib_hdmi_is_clk_ready()) {
		clk_tmp = lib_hdmi_get_clock();
#if HDMI2p0
		/* Check scdc flag */
		hdmi2p0_check_tmds_config();
#endif
	}

	lib_hdmi_trigger_measure_start();

	if (clk_tmp > VALID_MIN_CLOCK) {
#if HDMI2p0
		/* It's possible for 40x only when clock=(3G~6G)/4 */
		if ((hdmi2p0_get_clock40x_flag()) &&
			(clk_tmp < 1422 && clk_tmp > 699)) {
			clk_tmp <<= 2;/* HDMI2.0, change clock to clock*4 */
			phy_st.rxphy_40x = 1;
		}
#endif

		if (HDMI_ABS(clk_tmp, phy_st.clk_pre) < CLOCK_TOLERANCE()) {
			/* Get valid clock and close to previous clock */
			if (rxphy_is_clock_stable(clk_tmp)) {
				phy_st.clk_stable = 1;
				phy_st.clk = clk_tmp;
			}
			phy_st.clk_unstable_count = 0;
		} else if (phy_st.clk_unstable_count < CLK_UNSTABLE_CNT) {
			/* Get valid clock but different with previous clock, count for debouncing */
			phy_st.clk_unstable_count++;
		} else {
			/* Get valid clock but different with previous clock */
			phy_st.clk = 0;
			phy_st.clk_pre = clk_tmp;
			phy_st.clk_tolerance = MAX(clk_tmp>>7, 5);
			phy_st.clk_debounce_count = 0;
			phy_st.clk_unstable_count = 0;
			phy_st.clk_stable = 0;
			phy_st.phy_proc_state = PHY_PROC_INIT;
		}

		phy_st.noclk_debounce_count = 0;

	} else {
		/* clk_tmp <= VALID_MIN_CLOCK */
		if (phy_st.noclk_debounce_count < NOCLK_DEBOUNCE_CNT) {
			/* NO clock, and start debouncing */
			phy_st.noclk_debounce_count++;
		} else {
			/* NO clock, really!!  Then reset clk_info */
			if (phy_st.clk_pre) {
				phy_st.clk_pre = 0;
				phy_st.clk = 0;
				phy_st.clk_debounce_count = 0;
				phy_st.clk_unstable_count = 0;
				phy_st.clk_stable = 0;
				phy_st.phy_proc_state = PHY_PROC_INIT;
			}

			hdmi2p0_reset_scdc_toggle();
			if (phy_st.rxphy_40x) {
				/* NO clock, and reset clk_info and then reset SCDC */
				lib_hdmi2p0_reset_scdc();
				phy_st.rxphy_40x = 0;
			}
		}
	}

	lib_hdmi_trigger_measure_stop();

	if (clk_stable_prev != phy_st.clk_stable) {

		HDMI_PRINTF("clk_stable from %d to %d\n", clk_stable_prev,
			phy_st.clk_stable);

		lib_hdmi_misc_variable_initial();
	}

	if (phy_st.clk_stable)
		return TRUE;
	else
		return FALSE;

}

/**
 * rxphy_is_clock_stable
 *
 * Return: 1 when clock is stable
 */
unsigned char rxphy_is_clock_stable(unsigned int clk_tmp)
{
	if (phy_st.clk_debounce_count >= CLK_DEBOUNCE_CNT)
		return 1;
	else
		phy_st.clk_debounce_count++;

	return 0;
}

void rxphy_job(void)
{
	switch (phy_st.phy_proc_state) {
	case PHY_PROC_INIT:
		hdmi_set_phy(phy_st.clk);

		hdmi_reset_meas_counter();

		if (phy_st.clk <= clock_bound_45m)
			phy_st.phy_proc_state = PHY_PROC_CLOSE_ADP;
		else
			phy_st.phy_proc_state = PHY_PROC_RECORD;

		break;
	case PHY_PROC_RECORD:
		if (hdmi_dfe_record(phy_st.clk))
			phy_st.phy_proc_state = PHY_PROC_CLOSE_ADP;
		else
			break;
	case PHY_PROC_CLOSE_ADP:
		if (hdmi_dfe_close(phy_st.clk, PHY_PROC_CLOSE_ADP)) {
#if HDMI2p0
			hdmi2p0_detect_config();
#endif
			phy_st.phy_proc_state = PHY_PROC_DONE;
		}
		break;
	case PHY_PROC_DONE:

		break;
	/* Belowing are for recovery flow in check_mode stage */
	case PHY_PROC_RECOVER_6G_LONGCABLE:
		hdmi_dfe_hi_speed(phy_st.clk);
		phy_st.phy_proc_state = PHY_PROC_RECOVER_6G_LONGCABLE_RECORD;
		break;
	case PHY_PROC_RECOVER_6G_LONGCABLE_RECORD:
		if (hdmi_dfe_record(phy_st.clk))
			phy_st.phy_proc_state = PHY_PROC_RECOVER_6G_LONGCABLE_CLOSE_ADP;
		else
			break;
	case PHY_PROC_RECOVER_6G_LONGCABLE_CLOSE_ADP:
		hdmi_dfe_close(phy_st.clk, PHY_PROC_RECOVER_6G_LONGCABLE_CLOSE_ADP);
		phy_st.phy_proc_state = PHY_PROC_DONE;
		break;
	case PHY_PROC_RECOVER_MI:
		hdmi_dfe_mi_speed(phy_st.clk);
		phy_st.phy_proc_state = PHY_PROC_RECORD;
		break;
	default:
		phy_st.phy_proc_state = PHY_PROC_INIT;
		break;
	}

}

void rxphy_force_clear_clk_st(void)
{
	/*
	 * case 1: clk=1080p50->1080p60, timing changed, but clock is the same, then force to re-set phy
	 * case 2: clk=4k2kp60->1080p60, timing changed, but clock is the same, then force to re-set phy (also need to clear SCDC)
	 */
	rxphy_init_struct();
}

unsigned int rxphy_get_clk(void)
{
	return phy_st.clk;
}

unsigned char rxphy_is_clk_stable(void)
{
	return phy_st.clk_stable;
}

unsigned char rxphy_get_setphy_done(void)
{
	return (phy_st.phy_proc_state == PHY_PROC_DONE);
}

void rxphy_reset_setphy_proc(void)
{
	phy_st.phy_proc_state = PHY_PROC_INIT;
	HDMI_PRINTF("%s\n", __func__);
}

void hdmi_dfe_recovery_6g_long_cable(void)
{
	phy_st.phy_proc_state = PHY_PROC_RECOVER_6G_LONGCABLE;
}

void hdmi_dfe_recovery_mi_speed(void)
{
	phy_st.phy_proc_state = PHY_PROC_RECOVER_MI;
}

void hdmi_set_phy(unsigned int b)
{
	unsigned char mode;
	bool b_mode_found = 0;
	HDMI_PHY_PARAM_T *p_phy_table;
	unsigned char tb_size = 0;

	HDMI_PRINTF("%s  b=%d\n", __func__, b);

	if (b == 0)
		return;

	lib_hdmi_mac_reset();

	lib_hdmi_cdr_rst(1);
	lib_hdmi_demux_ck_vcopll_rst(1);
	lib_hdmi_wdg_rst(1);
	lib_hdmi_cmu_pll_en(0);
	HDMI_DELAYMS(20);
	lib_hdmi_eq_bias_band_setting(b);

	p_phy_table = hdmi_phy_param;
	tb_size = sizeof(hdmi_phy_param)/sizeof(HDMI_PHY_PARAM_T);

	HDMI_PRINTF("phy table size=%d\n", tb_size);
	for (mode = 0; mode < tb_size; mode++) {
		if (p_phy_table[mode].b_upper > b && p_phy_table[mode].b_lower <= b) {
			lib_hdmi_cco_band_config(b, &p_phy_table[mode]);
			lib_hdmi_set_phy_table(&p_phy_table[mode]);

			b_mode_found = 1;
			break;
		}
	}

	if (!b_mode_found) {
		HDMI_PRINTF("Not Found in PhyMode (b=%d)\n", b);
		return;
	}

#ifdef CONFIG_POWER_SAVING_MODE
	lib_hdmi_eq_pi_power_en(1);
#endif
	HDMI_DELAYMS(20);

	lib_hdmi_wdg_rst(0);

	lib_hdmi_wdog();
	lib_hdmi_cmu_pll_en(1);
	HDMI_DELAYMS(5);

	lib_hdmi_demux_ck_vcopll_rst(0);
	HDMI_DELAYMS(50);

	lib_hdmi_cdr_rst(0);

	HDMI_DELAYMS(30);

	lib_hdmi_dfe_config_setting();

	lib_hdmi_fg_koffset_disable();

	if (b > clock_bound_110m)
		lib_hdmi_set_dfe(b, 3);
	else if ((b > clock_bound_45m) && (b < clock_bound_110m))
		lib_hdmi_set_dfe_mid_band(b, 2);
	else
		lib_hdmi_dfe_manual_set();

	HDMI_DELAYMS(1);
	lib_hdmi_mac_release();

}

unsigned char hdmi_dfe_record(unsigned int clk)
{
	if (lib_hdmi_dfe_is_record_enable()) {
		lib_hdmi_dfe_record_enable(0);
		return TRUE;
	} else {
		lib_hdmi_dfe_record_enable(1);
		return FALSE;
	}
}

unsigned char hdmi_dfe_close(unsigned int clk, unsigned char phy_state)
{
	unsigned char lane;

	lib_hdmi_set_dfe_close();


	switch (phy_state) {
	case PHY_PROC_CLOSE_ADP:
		if (clk > 2900)/*  > 3G */
			lib_hdmi_load_le_max();
		else
			lib_hdmi_dfe_examine_le_coef(clk);
		break;
	case PHY_PROC_RECOVER_6G_LONGCABLE_CLOSE_ADP:
		hdmi_dfe_6g_long_cable_patch();
		break;
	default:
		break;
	}

	for (lane = 0; lane < 3; lane++) {
		phy_st.dfe_t[lane].tap0max = lib_hdmi_dfe_get_tap0max(lane);
		phy_st.dfe_t[lane].tap0min = lib_hdmi_dfe_get_tap0min(lane);
		phy_st.dfe_t[lane].vth = lib_hdmi_dfe_get_vth(lane);
		phy_st.dfe_t[lane].tap0 = lib_hdmi_dfe_get_tap0(lane);
		phy_st.dfe_t[lane].tap1 = lib_hdmi_dfe_get_tap1(lane);
		phy_st.dfe_t[lane].tap2 = lib_hdmi_dfe_get_tap2(lane);
		phy_st.dfe_t[lane].le = lib_hdmi_dfe_get_le(lane);
		phy_st.dfe_t[lane].lemax = lib_hdmi_dfe_get_lemax(lane);
		phy_st.dfe_t[lane].lemin = lib_hdmi_dfe_get_lemin(lane);
	}

	hdmi_dump_dfe_para();

	return TRUE;
}

void hdmi_dfe_hi_speed(unsigned int b_clk)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_power(1);
	HDMI_DELAYMS(1);
	/* ENABLE  VTH & TAP0 */
	lib_hdmi_dfe_init_vth((LN_R|LN_G|LN_B), 0x03);
	lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), 0x14);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth), HDMI_RX_DFE);

	lib_hdmi_dfe_second_flow(b_clk);

	lib_hdmi_dfe_init_tap1((LN_R|LN_G|LN_B), 0x0c);
	lib_hdmi_dfe_init_tap2((LN_R|LN_G|LN_B), 0x00);
	lib_hdmi_dfe_init_le((LN_R|LN_G|LN_B), 0x08);

	if (b_clk > 2700) {
		/* 3G need tap2 but below not need */
		hdmi_rx_reg_mask32(REG_DFE_EN_L0,
			~(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
			(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L1,
			~(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
			(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L2,
			~(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
			(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
			HDMI_RX_DFE);
	} else {
		hdmi_rx_reg_mask32(REG_DFE_EN_L0,
			~(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
			(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE),
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L1,
			~(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
			(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE),
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L2,
			~(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
			(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE),
			HDMI_RX_DFE);
	}

}

void hdmi_dfe_6g_long_cable_patch(void)
{
	signed char tap2;
	unsigned char lemax;

	tap2 = lib_hdmi_dfe_get_tap2(1);
	lib_hdmi_dfe_init_tap2(LN_G, MIN(tap2+6, 10));

	lemax = lib_hdmi_dfe_get_lemax(1);
	lemax += lib_hdmi_dfe_get_tap1max(1);
	lib_hdmi_dfe_init_tap1(LN_G, MIN(lemax+4, 63));

	HDMI_PRINTF("%s end\n", __func__);
}

void hdmi_dfe_mi_speed(unsigned int b_clk)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_power(1);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
		(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
		(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
		(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
		HDMI_RX_DFE);
}

#if TMDS_ERR_DET_SHORT_PERIOD

void hdmi_open_err_detect(void)
{
	phy_st.error_detect_count = 0;
}


unsigned char hdmi_err_detect_stop(void)
{
	if (phy_st.error_detect_count > MAX_ERR_DETECT_TIMES) {
		return 1;
	} else {
		++phy_st.error_detect_count;
		return 0;
	}

}

#endif

unsigned char hdmi_char_err_detection(void)
{
	unsigned int r_err = 0, g_err = 0, b_err = 0;

#if TMDS_ERR_DET_SHORT_PERIOD
	if (hdmi_err_detect_stop())
		return 0;
#endif

	if (phy_st.char_err_loop == 0) {
		lib_hdmi_char_err_start(0, TMDS_CHAR_ERR_PERIOD);
		phy_st.char_err_loop++;

	} else {
		if (lib_hdmi_char_err_get_error(&r_err, &g_err, &b_err)) {
			phy_st.char_err_loop = 0;
			phy_st.detect_6g_longcable = 0;

			if ((g_err > TMDS_CHAR_ERR_THREAD) &&
				(r_err < 10) && (b_err < 10) &&
				((phy_st.dfe_t[1].le+phy_st.dfe_t[1].tap1) > 10))
				phy_st.detect_6g_longcable = 1;

			if ((r_err > TMDS_CHAR_ERR_THREAD) || (g_err > TMDS_CHAR_ERR_THREAD) || (b_err > TMDS_CHAR_ERR_THREAD))
				HDMI_PRINTF("[CHAR_ERR](%d, %d, %d)\n", r_err, g_err, b_err);

			return 1;
		}

		if (phy_st.char_err_loop > TMDS_CHAR_ERR_MAX_LOOP) {
			phy_st.char_err_loop = 0;
			phy_st.detect_6g_longcable = 0;
			HDMI_PRINTF("[CHAR_ERR] Life is too short.\n");
		} else {
			phy_st.char_err_loop++;
		}

	}

	return 0;

}

unsigned char hdmi_bit_err_detection(void)
{
	unsigned int r_err = 0, g_err = 0, b_err = 0;

#if TMDS_ERR_DET_SHORT_PERIOD
	if (hdmi_err_detect_stop())
		return 0;
#endif

	if (phy_st.bit_err_loop == 0) {
		lib_hdmi_bit_err_start(0, TMDS_BIT_ERR_PERIOD);
		phy_st.bit_err_loop++;

	} else {
		if (lib_hdmi_bit_err_get_error(&r_err, &g_err, &b_err)) {
			phy_st.bit_err_loop = 0;

			if ((r_err > TMDS_BIT_ERR_THREAD) || (g_err > TMDS_BIT_ERR_THREAD) || (b_err > TMDS_BIT_ERR_THREAD)) {
				HDMI_PRINTF("[BIT_ERR](%d, %d, %d)\n", r_err, g_err, b_err);
				return 1;
			}
			/* HDMI_PRINTF("[BIT_ERR](%d, %d, %d)\n", r_err, g_err, b_err); */
			return 0;
		}

		if (phy_st.bit_err_loop > TMDS_BIT_ERR_MAX_LOOP) {
			phy_st.bit_err_loop = 0;
			HDMI_PRINTF("[BIT_ERR] Life is too short.\n");
		} else {
			phy_st.bit_err_loop++;
		}

	}

	return 0;

}

unsigned char hdmi_is_long_cable(void)
{
	return phy_st.detect_6g_longcable;
}

void hdmi_dump_dfe_para(void)
{
	unsigned char lane;

	for (lane = 0; lane < 3; lane++) {
		HDMI_PRINTF("********************Lane%d******************\n", lane);
		HDMI_PRINTF("[DFE] Lane%d Vth=0x%x\n", lane, phy_st.dfe_t[lane].vth);
		HDMI_PRINTF("[DFE] Lane%d Tap0=0x%x, max=0x%02x, min=0x%02x\n",
			lane, phy_st.dfe_t[lane].tap0, phy_st.dfe_t[lane].tap0max, phy_st.dfe_t[lane].tap0min);

		HDMI_PRINTF("[DFE] Lane%d Tap1=0x%02x, Tap2=%+d\n",
			lane, phy_st.dfe_t[lane].tap1, phy_st.dfe_t[lane].tap2);

		HDMI_PRINTF("[DFE] Lane%d LE=0x%02x, max=0x%02x, min=0x%02x\n",
			lane, phy_st.dfe_t[lane].le, phy_st.dfe_t[lane].lemax, phy_st.dfe_t[lane].lemin);
	}
}

#ifdef CONFIG_POWER_SAVING_MODE
void hdmi_phy_pw_saving(unsigned char port)
{
	lib_hdmi_cdr_rst(1);
	lib_hdmi_demux_ck_vcopll_rst(1);

	lib_hdmi_eq_pi_power_en(0);
	lib_hdmi_cmu_pll_en(0);
}
#endif

void lib_hdmi_trigger_measurement(void)
{
	hdmi_rx_reg_mask32(REGD56, ~REGD56_p0_ck_md_rstb_mask, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD56,
		~REGD56_p0_ck_md_rstb_mask, REGD56_p0_ck_md_rstb_mask, HDMI_RX_PHY);
	hdmi_rx_reg_write32(REGD57, REGD57_p0_ck_md_ok_mask, HDMI_RX_PHY);
}

void lib_hdmi_trigger_measure_start(void)
{
	hdmi_rx_reg_mask32(REGD56, ~REGD56_p0_ck_md_rstb_mask, 0, HDMI_RX_PHY);
}

void lib_hdmi_trigger_measure_stop(void)
{
	hdmi_rx_reg_mask32(REGD56,
		~REGD56_p0_ck_md_rstb_mask, REGD56_p0_ck_md_rstb_mask, HDMI_RX_PHY);
}

unsigned char lib_hdmi_is_clk_ready(void)
{
	hdmi_rx_reg_write32(REGD57, REGD57_p0_ck_md_ok_mask, HDMI_RX_PHY);
	HDMI_DELAYUS(20);

	if (REGD57_get_p0_ck_md_ok(hdmi_rx_reg_read32(REGD57, HDMI_RX_PHY)))
		return TRUE;
	else
		return FALSE;
}

unsigned int lib_hdmi_get_clock(void)
{
	unsigned int b;

	b = REGD57_get_p0_ck_md_count(hdmi_rx_reg_read32(REGD57, HDMI_RX_PHY));
	return b;
}

void lib_hdmi_phy_init(void)
{
	/* Enable bandgap power */
	hdmi_rx_reg_mask32(TOP_IN, ~TOP_IN_BIAS_POW, TOP_IN_BIAS_POW, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(TOP_IN, ~(TOP_IN_REG_IBHN_TUNE), _BIT20, HDMI_RX_PHY);
	lib_hdmi_cmu_pll_en(1);
	HDMI_PRINTF("ENABLE_reg=0x%08x\n", hdmi_rx_reg_read32(ENABLE, HDMI_RX_PHY));

	hdmi_rx_reg_mask32(TOP_IN, ~(TOP_IN_CK_TX_0), (TOP_IN_CK_TX_0), HDMI_RX_PHY);

	/* Default hdmi mode */
	lib_hdmi_ck_md_ref_sel();
	lib_hdmi_fg_koffset_manual_adjust(0x10, 0x10, 0x10);

	lib_hdmi_z0_calibration();

	hdmi_rx_reg_mask32(P0_CK1,
		~(p0_ck_2_CMU_CKIN_SEL | p0_ck_2_ACDR_CBUS_REF |
		p0_ck_2_CK_MD_DET_SEL | p0_CMU_CKAFE_ENHANCE_BIAS |
		p0_CK_2_CKD2S_EN0 | P0_CK1_reg_p0_ck_1_mask),
		(p0_ck_2_CMU_CKIN_SEL | p0_ck_2_ACDR_CBUS_REF |
		p0_ck_2_CK_MD_DET_SEL | p0_CMU_CKAFE_ENHANCE_BIAS |
		p0_CK_2_CKD2S_EN0 | p0_ck_1_port_bias | p0_ck_1_CKAFE_POW),
		HDMI_RX_PHY);
	/* When ac on, need this for hdcp auth */
	hdmi_rx_reg_mask32(P0_CK2,
		~P0_ck_8_LDO_EN_mask, P0_ck_8_LDO_EN_mask, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(P0_R2, ~P0_b_DEMUX_BBPD_RSTB, P0_b_DEMUX_BBPD_RSTB, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G2, ~P0_b_DEMUX_BBPD_RSTB, P0_b_DEMUX_BBPD_RSTB, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_B2, ~P0_b_DEMUX_BBPD_RSTB, P0_b_DEMUX_BBPD_RSTB, HDMI_RX_PHY);

}


void lib_hdmi_z0_set(unsigned char lane, unsigned char enable)
{
	unsigned int bmask = 0;

	if (lane&LN_CK)
		bmask |= Z0POW_reg_z0_z0pow_ck(1);

	if (lane&LN_B)
		bmask |= Z0POW_reg_z0_z0pow_b(1);

	if (lane&LN_G)
		bmask |= Z0POW_reg_z0_z0pow_g(1);

	if (lane&LN_R)
		bmask |= Z0POW_reg_z0_z0pow_r(1);

	if (!bmask)
		return;

	hdmi_rx_reg_mask32(Z0POW, ~bmask, enable?bmask:0, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(TOP_IN,
		~(TOP_IN_Z0_FIX_SELECT_0), enable?(TOP_IN_Z0_FIX_SELECT_0):0, HDMI_RX_PHY);

}


/**
 * lib_hdmi_z300_sel
 *
 * @mode: 0-active mode, 1-vcm mode
 */
void lib_hdmi_z300_sel(unsigned char mode)
{
	if (mode)
		hdmi_rx_reg_mask32(Z0POW, ~(Z0POW_reg_z0_z300_sel(1)), Z0POW_reg_z0_z300_sel(1), HDMI_RX_PHY);
	else
		hdmi_rx_reg_mask32(Z0POW, ~(Z0POW_reg_z0_z300_sel(1)), 0, HDMI_RX_PHY);
}


void lib_hdmi_ck_md_ref_sel(void)
{
	hdmi_rx_reg_mask32(P0_CK1, ~p0_ck_2_CK_MD_REF_SEL, p0_ck_2_CK_MD_REF_SEL, HDMI_RX_PHY);
}


void lib_hdmi_wdg_rst(unsigned char rst)
{
	if (rst)
		hdmi_rx_reg_mask32(P0_CK3,
			~(P0_ck_9_CMU_PFD_RSTB|_BIT3|P0_ck_9_CMU_WDRST|_BIT1),
			(_BIT3|P0_ck_9_CMU_WDRST), HDMI_RX_PHY);/* PFD_RSTB  reset */
	else
		hdmi_rx_reg_mask32(P0_CK3,
			~(P0_ck_9_CMU_PFD_RSTB|_BIT3|P0_ck_9_CMU_WDRST|_BIT1),
			(P0_ck_9_CMU_PFD_RSTB|_BIT1), HDMI_RX_PHY);/* release, normal */
}


void lib_hdmi_afifo_enable(unsigned char enable)
{
	if (enable)
		hdmi_rx_reg_mask32(HDMI_CH_CR,
			~(HDMI_CH_CR_r_ch_afifo_en_mask|HDMI_CH_CR_g_ch_afifo_en_mask|HDMI_CH_CR_b_ch_afifo_en_mask),
			(HDMI_CH_CR_r_ch_afifo_en_mask|HDMI_CH_CR_g_ch_afifo_en_mask|HDMI_CH_CR_b_ch_afifo_en_mask),
			HDMI_RX_MAC);
	else
		hdmi_rx_reg_mask32(HDMI_CH_CR,
			~(HDMI_CH_CR_r_ch_afifo_en_mask|HDMI_CH_CR_g_ch_afifo_en_mask|HDMI_CH_CR_b_ch_afifo_en_mask),
			0, HDMI_RX_MAC);
}

void lib_hdmi_mac_reset(void)
{
	hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0, ~(HDMI_TMDS_DPC_SET0_dpc_en_mask), 0, HDMI_RX_MAC);
	lib_hdmi_afifo_enable(0);
	/* Disable TMDS input */
	hdmi_rx_reg_mask32(HDMI_TMDS_PWDCTL,
		~(HDMI_TMDS_PWDCTL_ebip_mask|HDMI_TMDS_PWDCTL_egip_mask|HDMI_TMDS_PWDCTL_erip_mask|HDMI_TMDS_PWDCTL_ecc_mask),
		0, HDMI_RX_MAC);
	/* HDMI&DVI function disable */
	hdmi_rx_reg_mask32(HDMI_TMDS_Z0CC, ~HDMI_TMDS_Z0CC_hde_mask, 0, HDMI_RX_MAC);
}

void lib_hdmi_mac_release(void)
{
	HDMI_DELAYMS(1);
	hdmi_rx_reg_mask32(HDMI_TMDS_Z0CC, ~HDMI_TMDS_Z0CC_hde_mask, HDMI_TMDS_Z0CC_hde(1), HDMI_RX_MAC);

	HDMI_DELAYMS(1);
	/* Enable TMDS input */
	hdmi_rx_reg_mask32(HDMI_TMDS_PWDCTL,
		~(HDMI_TMDS_PWDCTL_ebip_mask|HDMI_TMDS_PWDCTL_egip_mask|HDMI_TMDS_PWDCTL_erip_mask|HDMI_TMDS_PWDCTL_ecc_mask),
		(HDMI_TMDS_PWDCTL_ebip(1)|HDMI_TMDS_PWDCTL_egip(1)|HDMI_TMDS_PWDCTL_erip(1)|HDMI_TMDS_PWDCTL_ecc(1)),
		HDMI_RX_MAC);
	HDMI_DELAYMS(1);
	lib_hdmi_afifo_enable(1);
	hdmi_rx_reg_mask32(HDMI_TMDS_DPC_SET0,
		~HDMI_TMDS_DPC_SET0_dpc_en_mask, HDMI_TMDS_DPC_SET0_dpc_en_mask, HDMI_RX_MAC);
}

void lib_hdmi_dfe_power(unsigned char en)
{
	hdmi_rx_reg_mask32(P0_B3, ~(P0_b_9_DFE_ADAPTION_POW_EN|P0_b_9_DFE_TAP_EN), (P0_DFE_ADAPTION_EN((en != 0))|P0_b_tap_en(0x3)), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G3, ~(P0_b_9_DFE_ADAPTION_POW_EN|P0_b_9_DFE_TAP_EN), (P0_DFE_ADAPTION_EN((en != 0))|P0_b_tap_en(0x3)), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_R3, ~(P0_b_9_DFE_ADAPTION_POW_EN|P0_b_9_DFE_TAP_EN), (P0_DFE_ADAPTION_EN((en != 0))|P0_b_tap_en(0x3)), HDMI_RX_PHY);
}

void lib_hdmi_eq_set_clock_boundary(void)
{
	clock_bound_3g = TMDS_3G;
	clock_bound_1p5g = TMDS_1p5G;
	clock_bound_45m = 430;
	clock_bound_110m = 1042;

	/* HDMI_PRINTF("clock_bound_3g=%d\n", clock_bound_3g); */
}

#ifdef CONFIG_POWER_SAVING_MODE
void lib_hdmi_eq_pi_power_en(unsigned char en)
{
	if (en) {
		hdmi_rx_reg_mask32(P0_B2, ~(P0_b_5_EQ_POW), P0_b_5_EQ_POW, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_G2, ~(P0_b_5_EQ_POW), P0_b_5_EQ_POW, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_R2, ~(P0_b_5_EQ_POW), P0_b_5_EQ_POW, HDMI_RX_PHY);

		HDMI_DELAYUS(10);

		hdmi_rx_reg_mask32(P0_B2, ~(P0_b_8_POW_PR), P0_b_8_POW_PR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_G2, ~(P0_b_8_POW_PR), P0_b_8_POW_PR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_R2, ~(P0_b_8_POW_PR), P0_b_8_POW_PR, HDMI_RX_PHY);
	} else {
		hdmi_rx_reg_mask32(P0_B2, ~(P0_b_8_POW_PR|P0_b_5_EQ_POW), 0x0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_G2, ~(P0_b_8_POW_PR|P0_b_5_EQ_POW), 0x0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_R2, ~(P0_b_8_POW_PR|P0_b_5_EQ_POW), 0x0, HDMI_RX_PHY);
	}

}
#endif

void lib_hdmi_eq_bias_band_setting(unsigned int b)
{
	UINT32 B1_addr, G1_addr, R1_addr;
	UINT32 B2_addr, G2_addr, R2_addr;
	UINT32 B3_addr, G3_addr, R3_addr;

	B1_addr = P0_B1;
	B2_addr = P0_B2;
	B3_addr = P0_B3;
	G1_addr = P0_G1;
	G2_addr = P0_G2;
	G3_addr = P0_G3;
	R1_addr = P0_R1;
	R2_addr = P0_R2;
	R3_addr = P0_R3;

	lib_hdmi_eq_set_clock_boundary();

	hdmi_rx_reg_mask32(B2_addr, ~P0_b_6_TAP0_LE_ISO, P0_b_6_TAP0_LE_ISO, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G2_addr, ~P0_b_6_TAP0_LE_ISO, P0_b_6_TAP0_LE_ISO, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R2_addr, ~P0_b_6_TAP0_LE_ISO, P0_b_6_TAP0_LE_ISO, HDMI_RX_PHY);


	if (b > clock_bound_3g) {
		/* Over  3G HBR */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA | P0_b_7_LEQ_ISEL_400uA | P0_b_6_LEQ_BIT_RATE_HBR | P0_b_6_LEQ_BIT_RATE_HBR | P0_b_6_TAP0_HBR | P0_b_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA | P0_b_7_LEQ_ISEL_400uA | P0_g_6_LEQ_BIT_RATE_HBR | P0_g_6_LEQ_BIT_RATE_HBR | P0_g_6_TAP0_HBR | P0_b_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_r_7_TAP0_ISEL|P0_r_7_LEQ_ISEL|P0_r_6_LEQ_BIT_RATE|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA | P0_b_7_LEQ_ISEL_400uA | P0_r_6_LEQ_BIT_RATE_HBR | P0_r_6_LEQ_BIT_RATE_HBR | P0_r_6_TAP0_HBR | P0_b_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);

		/* B */
		hdmi_rx_reg_mask32(B3_addr,
			~(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_mask|P0_b_10_DFE_PREAMP_ISEL_mask|P0_b_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_400uA|P0_b_10_DFE_PREAMP_ISEL_400uA|P0_b_10_DFE_SUMAMP_LP_MANUALOFF),
			HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr,
			~(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_mask|P0_g_10_DFE_PREAMP_ISEL_mask|P0_g_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_400uA|P0_g_10_DFE_PREAMP_ISEL_400uA|P0_g_10_DFE_SUMAMP_LP_MANUALOFF),
			HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr,
			~(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_mask|P0_r_10_DFE_PREAMP_ISEL_mask|P0_r_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_400uA|P0_r_10_DFE_PREAMP_ISEL_400uA|P0_r_10_DFE_SUMAMP_LP_MANUALOFF),
			HDMI_RX_PHY);

		/* LEQ_BIT_RATE */
		hdmi_rx_reg_mask32(B1_addr, ~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), P1_b_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr, ~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), P1_g_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr, ~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), P1_r_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr, ~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr, ~(P0_g_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr, ~(P0_r_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);

		/* PR sel */
		/* B */
		hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);

	} else if (b > clock_bound_1p5g) {
		/* 3G ~1.5G */

		/* B lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA|P0_b_7_LEQ_ISEL_200uA|P0_b_6_LEQ_BIT_RATE_MBR|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ_1X),
			HDMI_RX_PHY);

		/*G lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_g_7_TAP0_ISEL_400uA|P0_g_7_LEQ_ISEL_200uA|P0_g_6_LEQ_BIT_RATE_MBR|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ_1X),
			HDMI_RX_PHY);

		/*R lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_r_7_TAP0_ISEL|P0_r_7_LEQ_ISEL|P0_r_6_LEQ_BIT_RATE|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ),
			(P0_r_7_TAP0_ISEL_400uA|P0_r_7_LEQ_ISEL_200uA|P0_r_6_LEQ_BIT_RATE_MBR|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ_1X),
			HDMI_RX_PHY);

		/* B */
		hdmi_rx_reg_mask32(B3_addr,
			~(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_mask|P0_b_10_DFE_PREAMP_ISEL_mask|P0_b_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_400uA|P0_b_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr,
			~(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_mask|P0_g_10_DFE_PREAMP_ISEL_mask|P0_g_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_400uA|P0_g_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr,
			~(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_mask|P0_r_10_DFE_PREAMP_ISEL_mask|P0_r_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_400uA|P0_r_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);

		/* LEQ_BIT_RATE */
		hdmi_rx_reg_mask32(B1_addr,
			~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), (P1_b_2_LEQ_BIT_RATE_MBR|P0_b_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr,
			~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), (P1_g_2_LEQ_BIT_RATE_MBR|P0_g_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr,
			~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), (P1_r_2_LEQ_BIT_RATE_MBR|P0_r_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);

		/* PR sel */
		/* B */
		hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
	} else {
		/* Under 1.5G */

		/*B lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_5_LEQ_CURRENT_ADJ_1X|P0_b_7_TAP0_ISEL_400uA), HDMI_RX_PHY);

		/* G lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_g_5_LEQ_CURRENT_ADJ_1X|P0_g_7_TAP0_ISEL_400uA), HDMI_RX_PHY);

		/*R lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_r_7_TAP0_ISEL|P0_r_7_LEQ_ISEL|P0_r_6_LEQ_BIT_RATE|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ),
			(P0_r_5_LEQ_CURRENT_ADJ_1X|P0_r_7_TAP0_ISEL_400uA), HDMI_RX_PHY);

		/* B */
		hdmi_rx_reg_mask32(B3_addr,
			~(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_mask|P0_b_10_DFE_PREAMP_ISEL_mask|P0_b_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_b_11_ACDR_RATE_SEL_HALF_RATE|P0_b_10_DFE_SUMAMP_ISEL_400uA|P0_b_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr,
			~(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_mask|P0_g_10_DFE_PREAMP_ISEL_mask|P0_g_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_g_11_ACDR_RATE_SEL_HALF_RATE|P0_g_10_DFE_SUMAMP_ISEL_400uA|P0_g_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr,
			~(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_mask|P0_r_10_DFE_PREAMP_ISEL_mask|P0_r_10_DFE_SUMAMP_LP_MANUALOFF),
			(P0_r_11_ACDR_RATE_SEL_HALF_RATE|P0_r_10_DFE_SUMAMP_ISEL_400uA|P0_r_10_DFE_PREAMP_ISEL_400uA),
			HDMI_RX_PHY);

		/* LEQ_BIT_RATE */
		hdmi_rx_reg_mask32(B1_addr,
			~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), P0_b_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr,
			~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), P0_g_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr,
			~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), P0_r_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_b_7_PI_ISEL | p0_b_8_ACDR_CLK_SEL | P0_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);

		/* PR sel */
		/* B */
		hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* G */
		hdmi_rx_reg_mask32(G3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
		/* R */
		hdmi_rx_reg_mask32(R3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
	}

}


void lib_hdmi_set_dfe(unsigned int b, unsigned char dfe_mode)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_power(1);
	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~(REG_DFE_MODE_adapt_mode_mask | REG_DFE_MODE_edge_det_mode_mask |
		REG_DFE_MODE_transition_only_mask | REG_DFE_MODE_tap1_delay_mask |
		REG_DFE_MODE_tap24_delay_mask | REG_DFE_MODE_le_delay_mask |
		REG_DFE_MODE_servo_delay_mask | REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_dfe_adapt_rstb_mask | REG_DFE_MODE_tap0_notrans_mask),
		REG_DFE_MODE_adapt_mode(dfe_mode) | REG_DFE_MODE_edge_det_mode(0) |
		REG_DFE_MODE_transition_only_mask | REG_DFE_MODE_tap1_delay(1) |
		REG_DFE_MODE_tap24_delay(1) | REG_DFE_MODE_le_delay(1) |
		REG_DFE_MODE_servo_delay(1) | REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_tap0_notrans_mask, HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_DFE_EN_L0_clk_inv_lane0_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x8), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_DFE_EN_L1_clk_inv_lane1_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x8), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_DFE_EN_L2_clk_inv_lane2_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x8), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap1_init_lane0(0xc)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3)),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap1_init_lane0(0xc)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3)),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap1_init_lane0(0xc)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3)),
		HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DFE);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);

	HDMI_DELAYMS(1);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);

	/* Adapt reset release */
	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~REG_DFE_MODE_dfe_adapt_rstb_mask, REG_DFE_MODE_dfe_adapt_rstb_mask, HDMI_RX_DFE);
	/* set run length = 4 */
	hdmi_rx_reg_mask32(REG_DFE_GAIN,
		~REG_DFE_GAIN_trans_rlength_mask, REG_DFE_GAIN_trans_rlength(2), HDMI_RX_DFE);

	/* Set tap tap1 tap2 max min value */
	if (b < 2844 && b > 1420) {
		/* 3G ~1.5G */
		hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
			~(REG_DFE_LIMIT0_tap1_min_mask|REG_DFE_LIMIT0_tap2_max_mask|REG_DFE_LIMIT0_tap2_min_mask),
			(REG_DFE_LIMIT0_tap1_min(0x10)|REG_DFE_LIMIT0_tap2_max(0x14)|REG_DFE_LIMIT0_tap2_min(0xa)),
			HDMI_RX_DFE);

		hdmi_rx_reg_mask32(REG_DFE_LIMIT2,
			~REG_DFE_LIMIT2_tap0_max_mask, REG_DFE_LIMIT2_tap0_max(0x24), HDMI_RX_DFE);
	} else {
		hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
			~(REG_DFE_LIMIT0_tap1_min_mask|REG_DFE_LIMIT0_tap2_max_mask|REG_DFE_LIMIT0_tap2_min_mask),
			REG_DFE_LIMIT0_tap1_min(0x35)|REG_DFE_LIMIT0_tap2_max(0x14)|REG_DFE_LIMIT0_tap2_min(0x0),
			HDMI_RX_DFE);

		hdmi_rx_reg_mask32(REG_DFE_LIMIT2,
			~REG_DFE_LIMIT2_tap0_max_mask, REG_DFE_LIMIT2_tap0_max(0x24), HDMI_RX_DFE);
	}

	/* Vth_min=0,Vth_max=0x7,Vth_th=0,Tap0_th=0 */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT1,
		~(REG_DFE_LIMIT1_vth_min_mask | REG_DFE_LIMIT1_vth_max_mask |
		REG_DFE_LIMIT1_vth_threshold_mask | REG_DFE_LIMIT1_tap0_threshold_mask |
		REG_DFE_LIMIT1_tap0_adjust_mask | REG_DFE_LIMIT1_tap1_trans_mask),
		REG_DFE_LIMIT1_vth_min(0) | REG_DFE_LIMIT1_vth_max(0x7) |
		REG_DFE_LIMIT1_tap0_adjust(0x02) | REG_DFE_LIMIT1_tap1_trans(1),
		HDMI_RX_DFE);

	/* ENABLE  VTH & TAP0 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DFE);

	HDMI_DELAYMS(5);

	lib_hdmi_dfe_second_flow(b);
	HDMI_DELAYMS(10);
	lib_hdmi_fg_koffset_proc();

	lib_hdmi_tap0_fix_small_swing();
	HDMI_DELAYMS(10);
	lib_hdmi_fg_koffset_proc();
	HDMI_DELAYMS(1);

	if (b > 2700) {
		/* 3G need tap2 but below not need */
		hdmi_rx_reg_mask32(REG_DFE_EN_L0,
			~(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
			REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2,
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L1,
			~(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
			REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2,
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L2,
			~(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
			REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2,
			HDMI_RX_DFE);
	} else {
		hdmi_rx_reg_mask32(REG_DFE_EN_L0,
			~(REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE | REG_dfe_adapt_en_lane0_TAP2),
			REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_LE,
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L1,
			~(REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE | REG_dfe_adapt_en_lane1_TAP2),
			REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_LE,
			HDMI_RX_DFE);
		hdmi_rx_reg_mask32(REG_DFE_EN_L2,
			~(REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE | REG_dfe_adapt_en_lane2_TAP2),
			REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_LE,
			HDMI_RX_DFE);
	}

}

void lib_hdmi_set_dfe_mid_band(unsigned int b_clk, int dfe_mode)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_power(1);

	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~(REG_DFE_MODE_adapt_mode_mask | REG_DFE_MODE_edge_det_mode_mask |
		REG_DFE_MODE_transition_only_mask | REG_DFE_MODE_tap1_delay_mask |
		REG_DFE_MODE_tap24_delay_mask | REG_DFE_MODE_le_delay_mask |
		REG_DFE_MODE_servo_delay_mask | REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_dfe_adapt_rstb_mask | REG_DFE_MODE_tap0_notrans_mask),
		REG_DFE_MODE_adapt_mode(dfe_mode) | REG_DFE_MODE_edge_det_mode(0) |
		REG_DFE_MODE_transition_only(1) | REG_DFE_MODE_tap1_delay(1) |
		REG_DFE_MODE_tap24_delay(1) | REG_DFE_MODE_le_delay(1) |
		REG_DFE_MODE_servo_delay(1) | REG_DFE_MODE_gray_en(1) |
		REG_DFE_MODE_tap0_notrans(1), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_DFE_EN_L0_clk_inv_lane0_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		REG_DFE_EN_L2_timer_ctrl_en_lane2(1) | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x5), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_DFE_EN_L1_clk_inv_lane1_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		REG_DFE_EN_L2_timer_ctrl_en_lane2(1) | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x5), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_DFE_EN_L2_clk_inv_lane2_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		REG_DFE_EN_L2_timer_ctrl_en_lane2(1) | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x5), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask|REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0)|REG_DFE_INIT0_L0_tap0_init_lane0(0x14)|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), _BIT19|_BIT21|_BIT23, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), _BIT19|_BIT21|_BIT23, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), _BIT19|_BIT21|_BIT23, HDMI_RX_DFE);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DFE);

	HDMI_DELAYMS(1);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DFE);


	/* Adapt reset release */
	hdmi_rx_reg_mask32(REG_DFE_MODE, ~(REG_DFE_MODE_dfe_adapt_rstb_mask), REG_DFE_MODE_dfe_adapt_rstb_mask, HDMI_RX_DFE);
	/* Set run length = 4 */
	hdmi_rx_reg_mask32(REG_DFE_GAIN, ~(REG_DFE_GAIN_trans_rlength_mask), REG_DFE_GAIN_trans_rlength(2), HDMI_RX_DFE);

	/* Set tap tap1 tap2 max min value */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
		~(REG_DFE_LIMIT0_tap1_min_mask|REG_DFE_LIMIT0_tap2_max_mask|REG_DFE_LIMIT0_tap2_min_mask),
		REG_DFE_LIMIT0_tap1_min(0x35)|REG_DFE_LIMIT0_tap2_max(0x14)|REG_DFE_LIMIT0_tap2_min(0xa),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_LIMIT2,
		~(REG_DFE_LIMIT2_tap0_max_mask), REG_DFE_LIMIT2_tap0_max(0x24), HDMI_RX_DFE);

	/* Vth_min=0,Vth_max=0x7,Vth_th=0,Tap0_th=0 */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT1,
		~(REG_DFE_LIMIT1_vth_min_mask | REG_DFE_LIMIT1_vth_max_mask |
		REG_DFE_LIMIT1_vth_threshold_mask | REG_DFE_LIMIT1_tap0_threshold_mask |
		REG_DFE_LIMIT1_tap0_adjust_mask | REG_DFE_LIMIT1_tap1_trans_mask),
		REG_DFE_LIMIT1_vth_min(0) | REG_DFE_LIMIT1_vth_max(0x7) |
		REG_DFE_LIMIT1_tap0_adjust(0x02) | REG_DFE_LIMIT1_tap1_trans(1),
		HDMI_RX_DFE);

	/* ENABLE  VTH & TAP0 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DFE);

	HDMI_DELAYMS(10);

	lib_hdmi_dfe_second_flow(b_clk);
	lib_hdmi_fg_koffset_proc();

	lib_hdmi_tap0_fix_small_swing();
	lib_hdmi_fg_koffset_proc();

	/* ENABLE  VTH & TAP0 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DFE);

}

void lib_hdmi_dfe_manual_set(void)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_rst(0);

	/* Disable dfe */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~REG_DFE_EN_L0_dfe_adapt_en_lane0_mask, 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~REG_DFE_EN_L1_dfe_adapt_en_lane1_mask, 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~REG_DFE_EN_L2_dfe_adapt_en_lane2_mask, 0, HDMI_RX_DFE);

	/* Adaptive mode sel */
	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~REG_DFE_MODE_adapt_mode_mask, REG_DFE_MODE_adapt_mode(3), HDMI_RX_DFE);

	/* lane0 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~REG_DFE_EN_L0_le_min_lane0_mask, REG_DFE_EN_L0_le_min_lane0(0xf), HDMI_RX_DFE);
	/* lane1 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~REG_DFE_EN_L1_le_min_lane1_mask, REG_DFE_EN_L1_le_min_lane1(0xf), HDMI_RX_DFE);
	/* lane2 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~REG_DFE_EN_L2_le_min_lane2_mask, REG_DFE_EN_L2_le_min_lane2(0xf), HDMI_RX_DFE);

	/* lane0 tap1 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~REG_DFE_INIT0_L0_tap1_init_lane0_mask, REG_DFE_INIT0_L0_tap1_init_lane0(5), HDMI_RX_DFE);
	/* lane1 tap1 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~REG_DFE_INIT0_L1_tap1_init_lane1_mask, REG_DFE_INIT0_L1_tap1_init_lane1(5), HDMI_RX_DFE);
	/* lane2 tap1 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~REG_DFE_INIT0_L2_tap1_init_lane2_mask, REG_DFE_INIT0_L2_tap1_init_lane2(5), HDMI_RX_DFE);

	/* lane0 tap0 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~REG_DFE_INIT0_L0_tap0_init_lane0_mask, REG_DFE_INIT0_L0_tap0_init_lane0(0x14), HDMI_RX_DFE);
	/* lane1 tap0 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~REG_DFE_INIT0_L1_tap0_init_lane1_mask, REG_DFE_INIT0_L1_tap0_init_lane1(0x14), HDMI_RX_DFE);
	/* lane2 tap0 initial */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~REG_DFE_INIT0_L2_tap0_init_lane2_mask, REG_DFE_INIT0_L2_tap0_init_lane2(0x14), HDMI_RX_DFE);

	/* lane0  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~REG_DFE_INIT1_L0_load_in_init_lane0_mask, REG_DFE_INIT1_L0_load_in_init_lane0(3), HDMI_RX_DFE);
	/* lane1  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~REG_DFE_INIT1_L1_load_in_init_lane1_mask, REG_DFE_INIT1_L1_load_in_init_lane1(3), HDMI_RX_DFE);
	/* lane2  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~REG_DFE_INIT1_L2_load_in_init_lane2_mask, REG_DFE_INIT1_L2_load_in_init_lane2(3), HDMI_RX_DFE);

	HDMI_DELAYUS(10);

	/* lane0  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~REG_DFE_INIT1_L0_load_in_init_lane0_mask, 0, HDMI_RX_DFE);
	/* lane1  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~REG_DFE_INIT1_L1_load_in_init_lane1_mask, 0, HDMI_RX_DFE);
	/* lane2  initial load */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~REG_DFE_INIT1_L2_load_in_init_lane2_mask, 0, HDMI_RX_DFE);

	lib_hdmi_fg_koffset_proc();

}


unsigned char lib_hdmi_dfe_tap0_fix(void)
{
	unsigned char i, tap0max[3], tap0[3];
	unsigned char tap0_max_of_3, tap0_min_of_3;

	/* Read Tap0 max */
	for (i = 0; i < 3; i++) {
		tap0max[i] = lib_hdmi_dfe_get_tap0max(i);
		tap0[i] = lib_hdmi_dfe_get_tap0(i);
	}

	if ((tap0max[0] > 2) && (tap0max[1] > 2) && (tap0max[2] > 2))
		return FALSE;

	tap0_max_of_3 = MAX(tap0[0], MAX(tap0[1], tap0[2]));
	tap0_min_of_3 = MIN(tap0[0], MIN(tap0[1], tap0[2]));

	if ((tap0_max_of_3 - tap0_min_of_3) < 8)
		return FALSE;

	HDMI_PRINTF("%s\n", __func__);
	lib_hdmi_dfe_init_vth((LN_R|LN_G|LN_B), 0x03);
	lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), 0x14);

#if 1
	HDMI_DELAYUS(300);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DFE);

	HDMI_DELAYUS(700);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(1), HDMI_RX_DFE);

	HDMI_DELAYMS(10);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		0, HDMI_RX_DFE);
#endif

	return TRUE;
}


void lib_hdmi_tap0_fix_small_swing(void)
{
	HDMI_PRINTF("%s\n", __func__);

	lib_hdmi_dfe_init_vth((LN_R|LN_G|LN_B), 0x03);
	lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), 0x14);

	HDMI_DELAYUS(300);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DFE);

	HDMI_DELAYUS(700);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(1), HDMI_RX_DFE);

	HDMI_DELAYMS(10);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth), 0, HDMI_RX_DFE);

}


void lib_hdmi_dfe_second_flow(unsigned int b_clk)
{
	unsigned char i, tap0max[3];

	HDMI_DELAYUS(300);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(1), HDMI_RX_DFE);
	HDMI_DELAYMS(10);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth), 0, HDMI_RX_DFE);

	if (b_clk > 5000)
		lib_hdmi_dfe_tap0_fix();

	/* Read Tap0 max */
	for (i = 0; i < 3; i++) {
		tap0max[i] = lib_hdmi_dfe_get_tap0max(i);
		tap0max[i] = (tap0max[i] > 2)?(tap0max[i]-2):0;
	}

	/* LOAD TAP0 max -1  & Vth 4 */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap0_init_lane0(tap0max[0])|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap0_init_lane0(tap0max[1])|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap0_init_lane0(tap0max[2])|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DFE);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH),
		LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH),
		LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH),
		LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH, HDMI_RX_DFE);
	HDMI_DELAYUS(100);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~(LOAD_IN_INIT_TAP0|LOAD_IN_INIT_VTH), 0, HDMI_RX_DFE);

}

void lib_hdmi_load_le_max(void)
{
	unsigned char lemax[3];

	HDMI_PRINTF("%s\n", __func__);

	/* Read LE max */
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_LE_MAX), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(0), HDMI_RX_DFE);
	lemax[0] = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(1), HDMI_RX_DFE);
	lemax[1] = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(2), HDMI_RX_DFE);
	lemax[2] = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_TAP1_MAX), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(0), HDMI_RX_DFE);
	lemax[0] += REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(1), HDMI_RX_DFE);
	lemax[1] += REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(2), HDMI_RX_DFE);
	lemax[2] += REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));

	/* LOAD LE max */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(lemax[0]), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(lemax[1]), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(lemax[2]), HDMI_RX_DFE);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
	HDMI_DELAYUS(10);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);

}

void lib_hdmi_dfe_examine_le_coef(unsigned int b_clk)
{
	unsigned char max_tap0, min_tap0;

	max_tap0 = MAX(lib_hdmi_dfe_get_tap0(0), MAX(lib_hdmi_dfe_get_tap0(1), lib_hdmi_dfe_get_tap0(2)));
	min_tap0 = MIN(lib_hdmi_dfe_get_tap0(0), MIN(lib_hdmi_dfe_get_tap0(1), lib_hdmi_dfe_get_tap0(2)));

	HDMI_PRINTF ("%s-(max=%d, min=%d, b_clk=%d)\n",
		__func__, max_tap0, min_tap0, b_clk);

	if ((max_tap0-min_tap0 > 10) && ((b_clk > 2000) && (b_clk < 2200))) {
		if (lib_hdmi_dfe_get_le(0) < 1) {
			hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
				~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(0x1), HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
				~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
				~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);
			HDMI_PRINTF("[RELE_L0] LE reload 0x1\n");
		}

		if (lib_hdmi_dfe_get_le(1) < 1) {
			hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
				~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(0x1), HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);
			HDMI_PRINTF("[RELE_L1] LE reload 0x1\n");
		}

		if (lib_hdmi_dfe_get_le(2) < 4) {
			hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
				~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), REG_DFE_INIT0_L0_tap1_init_lane0(0x6), HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
				~(LOAD_IN_INIT_TAP1), LOAD_IN_INIT_TAP1, HDMI_RX_DFE);
			HDMI_DELAYUS(10);
			hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
				~(LOAD_IN_INIT_TAP1), 0, HDMI_RX_DFE);
			HDMI_PRINTF("[RELE_L2] LE reload 0x6\n");
		}
	}

}

void lib_hdmi_set_dfe_close(void)
{
	HDMI_PRINTF("%s", __func__);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth |
		REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_TAP2 |
		REG_dfe_adapt_en_lane0_LE),
		0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth |
		REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_TAP2 |
		REG_dfe_adapt_en_lane1_LE),
		0, HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth |
		REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_TAP2 |
		REG_dfe_adapt_en_lane2_LE),
		0, HDMI_RX_DFE);

	/* Limit value record */
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DFE);

	hdmirx_state.DEF_ready = 1;

}

void lib_hdmi_dfe_record_enable(unsigned char onoff)
{
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(onoff), HDMI_RX_DFE);
}

unsigned char lib_hdmi_dfe_is_record_enable(void)
{
	unsigned char temp;

	temp = REG_DFE_READBACK_get_record_limit_en(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return temp;
}

void lib_hdmi_dfe_init_vth(unsigned char bgr, unsigned char value)
{
	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
			~REG_DFE_INIT0_L2_vth_init_lane2_mask,
			REG_DFE_INIT0_L2_vth_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
			~REG_DFE_INIT0_L1_vth_init_lane1_mask,
			REG_DFE_INIT0_L2_vth_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
			~REG_DFE_INIT0_L0_vth_init_lane0_mask,
			REG_DFE_INIT0_L0_vth_init_lane0(value), HDMI_RX_DFE);


	lib_hdmi_dfe_load_in_adp(bgr, LOAD_IN_INIT_VTH);
}

void lib_hdmi_dfe_init_tap0(unsigned char bgr, unsigned char value)
{
	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
			~REG_DFE_INIT0_L2_tap0_init_lane2_mask,
			REG_DFE_INIT0_L2_tap0_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
			~REG_DFE_INIT0_L1_tap0_init_lane1_mask,
			REG_DFE_INIT0_L1_tap0_init_lane1(value), HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
			~REG_DFE_INIT0_L0_tap0_init_lane0_mask,
			REG_DFE_INIT0_L0_tap0_init_lane0(value), HDMI_RX_DFE);

	lib_hdmi_dfe_load_in_adp(bgr, LOAD_IN_INIT_TAP0);
}

void lib_hdmi_dfe_init_tap1(unsigned char bgr, unsigned char value)
{
	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
			~REG_DFE_INIT0_L2_tap1_init_lane2_mask,
			REG_DFE_INIT0_L2_tap1_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
			~REG_DFE_INIT0_L1_tap1_init_lane1_mask,
			REG_DFE_INIT0_L1_tap1_init_lane1(value), HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
			~REG_DFE_INIT0_L0_tap1_init_lane0_mask,
			REG_DFE_INIT0_L0_tap1_init_lane0(value), HDMI_RX_DFE);

	lib_hdmi_dfe_load_in_adp(bgr, LOAD_IN_INIT_TAP1);
}

void lib_hdmi_dfe_init_tap2(unsigned char bgr, signed char value)
{
	if (value < 0)
		value = 0x20|((-value)&0x1f);
	else
		value = (value&0x1f);

	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
			~REG_DFE_INIT0_L2_tap2_init_lane2_mask,
			REG_DFE_INIT0_L2_tap2_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
			~REG_DFE_INIT0_L1_tap2_init_lane1_mask,
			REG_DFE_INIT0_L1_tap2_init_lane1(value), HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
			~REG_DFE_INIT0_L0_tap2_init_lane0_mask,
			REG_DFE_INIT0_L0_tap2_init_lane0(value), HDMI_RX_DFE);

	lib_hdmi_dfe_load_in_adp(bgr, LOAD_IN_INIT_TAP2);
}

void lib_hdmi_dfe_init_le(unsigned char bgr, unsigned char value)
{
	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_EN_L2,
			~REG_DFE_EN_L2_le_init_lane2_mask,
			REG_DFE_EN_L2_le_init_lane2(value), HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_EN_L1,
			~REG_DFE_EN_L1_le_init_lane1_mask,
			REG_DFE_EN_L1_le_init_lane1(value), HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_EN_L0,
			~REG_DFE_EN_L0_le_init_lane0_mask,
			REG_DFE_EN_L0_le_init_lane0(value), HDMI_RX_DFE);

	lib_hdmi_dfe_load_in_adp(bgr, LOAD_IN_INIT_LE);
}

void lib_hdmi_dfe_load_in_adp(unsigned char bgr, unsigned int option)
{
	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(option), option, HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(option), option, HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(option), option, HDMI_RX_DFE);


	HDMI_DELAYUS(10);

	if (bgr&LN_R)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(option), 0, HDMI_RX_DFE);

	if (bgr&LN_G)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(option), 0, HDMI_RX_DFE);

	if (bgr&LN_B)
		hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(option), 0, HDMI_RX_DFE);

}

unsigned char lib_hdmi_dfe_get_vth(unsigned char lane)
{
	unsigned char coef_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_coef_sel_mask,
		REG_DFE_READBACK_coef_sel(COEF_VTH), HDMI_RX_DFE);

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask,
		REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	coef_data = REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return coef_data;
}

unsigned char lib_hdmi_dfe_get_tap0(unsigned char lane)
{
	unsigned char coef_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_coef_sel_mask, REG_DFE_READBACK_coef_sel(COEF_TAP0), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	coef_data = REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return coef_data;
}

unsigned char lib_hdmi_dfe_get_tap0max(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_TAP0_MAX), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}

unsigned char lib_hdmi_dfe_get_tap0min(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_TAP0_MIN), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}

unsigned char lib_hdmi_dfe_get_tap1(unsigned char lane)
{
	unsigned char coef_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_coef_sel_mask, REG_DFE_READBACK_coef_sel(COEF_TAP1), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	coef_data = REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return coef_data;
}

unsigned char lib_hdmi_dfe_get_tap1max(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_TAP1_MAX), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}

unsigned char lib_hdmi_dfe_get_tap1min(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_TAP1_MIN), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}

char lib_hdmi_dfe_get_tap2(unsigned char lane)
{
	unsigned char coef;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_coef_sel_mask, REG_DFE_READBACK_coef_sel(COEF_TAP2), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	coef = get_TAP2_coef_sign(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE)) ? \
		-get_TAP2_coef(REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE))) :
		get_TAP2_coef(REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE)));

	return coef;
}

unsigned char lib_hdmi_dfe_get_le(unsigned char lane)
{
	unsigned char coef_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_coef_sel_mask, REG_DFE_READBACK_coef_sel(COEF_LE), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	coef_data = REG_DFE_READBACK_get_coef_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return coef_data;
}

unsigned char lib_hdmi_dfe_get_lemax(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_LE_MAX), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}

unsigned char lib_hdmi_dfe_get_lemin(unsigned char lane)
{
	unsigned char limit_data;

	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_limit_sel_mask, REG_DFE_READBACK_limit_sel(LIMIT_LE_MIN), HDMI_RX_DFE);
	hdmi_rx_reg_mask32(REG_DFE_READBACK,
		~REG_DFE_READBACK_lane_sel_mask, REG_DFE_READBACK_lane_sel(lane), HDMI_RX_DFE);

	limit_data = REG_DFE_READBACK_get_limit_data(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DFE));
	return limit_data;
}



void lib_hdmi_cmu_pll_en(unsigned char enable)
{
	hdmi_rx_reg_mask32(ENABLE,
		~ENABLE_reg_p0_en_cmu_mask, enable?ENABLE_reg_p0_en_cmu_mask:0, HDMI_RX_PHY);
}

/**
 * lib_hdmi_demux_ck_vcopll_rst
 *
 * @rst: 1-reset, 0-normal working operation
 */
void lib_hdmi_demux_ck_vcopll_rst(unsigned char rst)
{
	if (rst) {
		lib_hdmi_dfe_rst(1);
		hdmi_rx_reg_mask32(RST,
			~(RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask), 0, HDMI_RX_PHY);
	} else {
		hdmi_rx_reg_mask32(RST,
			~(RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask),
			RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask, HDMI_RX_PHY);
		lib_hdmi_dfe_rst(0);
	}

}

/**
 * lib_hdmi_dfe_rst
 *
 * @rst: 1-reset, 0-normal working operation
 */
void lib_hdmi_dfe_rst(unsigned char rst)
{
	hdmi_rx_reg_mask32(HDMI_CTS_FIFO_CTL,
		~HDMI_CTS_FIFO_CTL_dfe_rstn_n_mask, rst?0:HDMI_CTS_FIFO_CTL_dfe_rstn_n_mask, HDMI_RX_MAC);

}

/**
 * lib_hdmi_cdr_rst
 *
 * @rst: 1-reset, 0-normal working operation
 */
void lib_hdmi_cdr_rst(unsigned char rst)
{
	if (rst) {
		hdmi_rx_reg_mask32(REGD0,
			~(REGD0_p0_r_dig_rst_n_mask|REGD0_p0_g_dig_rst_n_mask|REGD0_p0_b_dig_rst_n_mask), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(REGD0,
			~(REGD0_p0_r_cdr_rst_n_mask|REGD0_p0_g_cdr_rst_n_mask|REGD0_p0_b_cdr_rst_n_mask), 0, HDMI_RX_PHY);
	} else {
		hdmi_rx_reg_mask32(REGD0,
			~(REGD0_p0_r_dig_rst_n_mask | REGD0_p0_g_dig_rst_n_mask | REGD0_p0_b_dig_rst_n_mask |
			REGD0_p0_r_cdr_rst_n_mask | REGD0_p0_g_cdr_rst_n_mask | REGD0_p0_b_cdr_rst_n_mask),
			REGD0_p0_r_dig_rst_n(1) | REGD0_p0_g_dig_rst_n(1) | REGD0_p0_b_dig_rst_n(1) |
			REGD0_p0_r_cdr_rst_n(1) | REGD0_p0_g_cdr_rst_n(1) | REGD0_p0_b_cdr_rst_n(1),
			HDMI_RX_PHY);
	}

}

void lib_hdmi_wdog(void)
{

	hdmi_rx_reg_write32(REGD20, 0xE4E84505, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD21,
		~(REGD21_reg_p0_wd_sdm_en_mask), 0, HDMI_RX_PHY);
	HDMI_DELAYMS(5);
	hdmi_rx_reg_mask32(REGD21,
		~(REGD21_reg_p0_wd_sdm_en_mask), REGD21_reg_p0_wd_sdm_en_mask, HDMI_RX_PHY);

}

void lib_hdmi_dfe_config_setting(void)
{
	lib_hdmi_mac_afifo_enable();
}


void lib_hdmi_set_phy_table(HDMI_PHY_PARAM_T *phy_param)
{
	unsigned int wReg1, wReg2, wCk1Reg, wCk2Reg, ck_md_sel;
	unsigned int B2REG, G2REG, R2REG;
	unsigned int B3REG, G3REG, R3REG;

	wReg1 = REGD21;
	wReg2 = REGD0;
	wCk1Reg = P0_CK1;
	B2REG = P0_B2;
	G2REG = P0_G2;
	R2REG = P0_R2;
	B3REG = P0_B3;
	G3REG = P0_G3;
	R3REG = P0_R3;
	wCk2Reg = P0_CK2;
	ck_md_sel = REGD56;

	hdmi_rx_reg_mask32(B3REG, ~(P0_b_12_PI_CSEL|P0_b_12_PI_CURRENT), (phy_param->PI_CURRENT<<28)|(phy_param->PI_CSEL<<24), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G3REG, ~(P0_g_12_PI_CSEL|P0_g_12_PI_CURRENT), (phy_param->PI_CURRENT<<28)|(phy_param->PI_CSEL<<24), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R3REG, ~(P0_r_12_PI_CSEL|P0_r_12_PI_CURRENT), (phy_param->PI_CURRENT<<28)|(phy_param->PI_CSEL<<24), HDMI_RX_PHY);

	/* M code set */
	hdmi_rx_reg_mask32(wReg1, ~REGD21_reg_p0_n_code_mask, phy_param->M_code<<REGD21_reg_p0_n_code_shift, HDMI_RX_PHY);

	/* N code */
	hdmi_rx_reg_mask32(wCk1Reg, ~(p0_ck_3_CMU_N_code|p0_ck_3_CMU_PREDIVN), phy_param->N_code<<18, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(wCk1Reg, ~(p0_ck_3_CMU_SEL_D4), phy_param->CMU_SEL_D4 << 16, HDMI_RX_PHY);

	/* PI_DIV */
	hdmi_rx_reg_mask32(B2REG, ~P0_b_8_PR_RATE_SEL, phy_param->PI_DIV<<26, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G2REG, ~P0_b_8_PR_RATE_SEL, phy_param->PI_DIV<<26, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R2REG, ~P0_b_8_PR_RATE_SEL, phy_param->PI_DIV<<26, HDMI_RX_PHY);

	/* DEMUX */
	hdmi_rx_reg_mask32(B2REG, ~(P0_b_8_DEMUX|P0_b_7_PI_ISEL), (phy_param->DEMUX<<29)|(phy_param->PI_ISEL<<16), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G2REG, ~(P0_b_8_DEMUX|P0_b_7_PI_ISEL), (phy_param->DEMUX<<29)|(phy_param->PI_ISEL<<16), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R2REG, ~(P0_b_8_DEMUX|P0_b_7_PI_ISEL), (phy_param->DEMUX<<29)|(phy_param->PI_ISEL<<16), HDMI_RX_PHY);

	hdmi_rx_reg_mask32(wCk2Reg,
		~(P0_ck_5_CMU_SEL_R1_mask | P0_ck_5_CMU_SEL_PUMP_DB_mask |
		P0_ck_5_CMU_SEL_PUMP_I_mask | P0_ck_6_CMU_SEL_CS_mask |
		P0_ck_6_CMU_EN_CAP_mask | P0_ck_6_CMU_BIG_KVCO_mask |
		P0_ck_7_CMU_BYPASS_PI_mask | P0_ck_8_CMU_SEL_CP_mask |
		P0_ck_8_CMU_BPPSR_mask | P0_ck_8_LDO_EN_mask |
		P0_ck_8_VSEL_LDO_A_mask),
		(phy_param->CK_RS<<0) | (phy_param->Icp_DUL<<3) |
		(phy_param->CK_Icp<<4) | (phy_param->CK_CS<<8) |
		(phy_param->EN_CAP << 12) | (phy_param->CMU_KVCO << 13) |
		P0_ck_7_CMU_BYPASS_PI_mask | P0_CMU_BPPSR(phy_param->pscaler) |
		P0_ck_8_LDO_EN_mask | P0_VSEL_LDO(3), HDMI_RX_PHY);

	hdmi_rx_reg_mask32(wReg2,
		~(REGD5_reg_p1_rate_sel_mask | REGD0_reg_p0_kp_mask |
		REGD0_reg_p0_ki_mask | REGD0_reg_p0_bypass_sdm_int_mask),
		REGD5_reg_p1_rate_sel(phy_param->RATE_SEL) | (phy_param->CDR_KP<<REGD0_reg_p0_kp_shift) |
		(phy_param->CDR_KI<<REGD0_reg_p0_ki_shift) | REGD0_reg_p0_bypass_sdm_int_mask, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(ck_md_sel,
		~REGD56_reg_p0_ck_md_sel_mask, REGD56_reg_p0_ck_md_sel(0), HDMI_RX_PHY);

}



void lib_hdmi_cco_band_config(unsigned int bclk, HDMI_PHY_PARAM_T *phy_param)
{
	HDMI_PHY_PARAM2_T *phy_param2 = &hdmi_phy_param2[0];
	unsigned char i = 0, tabsize = 0;
	unsigned int Fvco;
	unsigned int tmds_b = bclk;

	/* Fvco=[(Fin x prescaler x SEL_D4 x M_Code) กา N_Code ] */
	/* Fin=[(b+1)x27กา256] */

	if (hdmi2p0_get_clock40x_flag()) {
		if (((bclk >> 2) < 1422) && ((bclk >> 2) > 699))
			tmds_b = (bclk >> 2);
	}

	/* cco band */
	Fvco = (tmds_b + 1) * 27 * (phy_param->pscaler ? 1 : 2) * (1 << phy_param->CMU_SEL_D4) * (phy_param->M_code + 4);
	Fvco = (Fvco / (1 << phy_param->N_code)) >> 8;

	tabsize = sizeof(hdmi_phy_param2)/sizeof(HDMI_PHY_PARAM2_T);

	for (i = 0 ; i < tabsize ; ++i) {
		if ((Fvco >= hdmi_phy_param2[i].fvco_lower) && (Fvco < phy_param2[i].fvco_upper))
			break;
	}
	HDMI_PRINTF("Fvco=%x-----------------------------------------\n", Fvco);
	if (i >= tabsize) {
		HDMI_PRINTF("Not Found in PHY_PARAM2 (Fvco=%d)\n", Fvco);
		return;
	}

	phy_param2 = &hdmi_phy_param2[i];

	hdmi_rx_reg_mask32(P0_CK2,
		~(P0_ck_8_CCO_BAND_SEL_mask),
		P0_CCO_BAND_SEL(phy_param2->CCO_BAND_SEL), HDMI_RX_PHY);

}


unsigned char lib_hdmi_acdr_check_result(void)
{
	HDMI_PRINTF("lib_hdmi_acdr_check_result skip\n");
	return TRUE;
}


void lib_hdmi_fg_koffset_manual_adjust(unsigned int r, unsigned int g, unsigned int b)
{

	hdmi_rx_reg_mask32(P0_R1, ~P0_b_1_FORE_KOFF_ADJR, r<<16, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G1, ~P0_b_1_FORE_KOFF_ADJR, g<<16, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_B1, ~P0_b_1_FORE_KOFF_ADJR, b<<16, HDMI_RX_PHY);

}

void lib_hdmi_fg_koffset_manual(void)
{

	hdmi_rx_reg_mask32(P0_R1, ~P0_r_4_FORE_KOFF_AUTOK, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G1, ~P0_g_4_FORE_KOFF_AUTOK, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_B1, ~P0_b_4_FORE_KOFF_AUTOK, 0, HDMI_RX_PHY);

}

#define FORE_KOFF_RANGE  1  /* range maybe 0  1  2   3 */
void lib_hdmi_fg_koffset_auto(void)
{
	UINT8 i, k_cnt;
	UINT32 w_b_addr_control, w_g_addr_control, w_r_addr_control;
	UINT32 w_b_addr_result, w_g_addr_result, w_r_addr_result;
	volatile u_int32_t koff_r_result ;
	volatile u_int32_t  koff_g_result;
	volatile u_int32_t  koff_b_result;

	w_b_addr_control = P0_B1;
	w_g_addr_control = P0_G1;
	w_r_addr_control = P0_R1;
	w_b_addr_result = P0_B4;
	w_g_addr_result = P0_G4;
	w_r_addr_result = P0_R4;

	/* Initial circuit power */
	hdmi_rx_reg_mask32(w_b_addr_control,
		~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control,
		~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control,
		~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK, HDMI_RX_PHY);
	/* Cut input off */
	hdmi_rx_reg_mask32(w_b_addr_control,
		~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control,
		~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control,
		~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);

	/* For b lane */
	for (i = 0; i < FORE_KOFF_RANGE+1; i++) {
		hdmi_rx_reg_mask32(w_b_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);

		/* Set k off range */
		hdmi_rx_reg_mask32(w_b_addr_control,
			~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);

		/* Start cal */
		hdmi_rx_reg_mask32(w_b_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		k_cnt = 100;
		while (!((hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY))&P0_B4_reg_p0_b_koffok_mask) && --k_cnt)
			HDMI_DELAYUS(200);

		if (k_cnt == 0)
			HDMI_PRINTF("[ERROR] %s: func err(B)\n", __func__);

		koff_b_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask))
			break;

		if (i == FORE_KOFF_RANGE)
			HDMI_PRINTF("[ERROR] %s: out of B range (value=%d)\n", __func__, i);
	}


	/* For g lane */
	for (i = 0; i < FORE_KOFF_RANGE+1; i++) {
		hdmi_rx_reg_mask32(w_g_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);

		/* Set k off range */
		hdmi_rx_reg_mask32(w_g_addr_control,
			~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);

		/* Start cal */
		hdmi_rx_reg_mask32(w_g_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		k_cnt = 100;
		while (!((hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY))&P0_B4_reg_p0_b_koffok_mask) && --k_cnt)
			HDMI_DELAYUS(200);

		if (k_cnt == 0)
			HDMI_PRINTF("[ERROR] %s: func err(G)\n", __func__);

		koff_g_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask))
			break;

		if (i == FORE_KOFF_RANGE)
			HDMI_PRINTF("[ERROR] %s: out of G range (value=%d)\n", __func__, i);

	}


	/* For r lane */
	for (i = 0; i < FORE_KOFF_RANGE+1; i++) {
		hdmi_rx_reg_mask32(w_r_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);

		/* Set k off range */
		hdmi_rx_reg_mask32(w_r_addr_control,
			~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);

		/* Start cal */
		hdmi_rx_reg_mask32(w_r_addr_control,
			~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		k_cnt = 100;
		while (!((hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY))&P0_B4_reg_p0_b_koffok_mask) && --k_cnt)
			HDMI_DELAYUS(200);

		if (k_cnt == 0)
			HDMI_PRINTF("[ERROR] %s: func err(R)\n", __func__);

		koff_r_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask))
			break;

		if (i == FORE_KOFF_RANGE)
			HDMI_PRINTF("[ERROR] %s: out of R range (value=%d)\n", __func__, i);

	}

	/* Cut input on */
	hdmi_rx_reg_mask32(w_b_addr_control, ~P0_b_1_inputoff, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control, ~P0_b_1_inputoff, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control, ~P0_b_1_inputoff, 0, HDMI_RX_PHY);

	HDMI_PRINTF("FG KOFFSET=(b=%d,g=%d,r=%d)\n", koff_b_result, koff_g_result, koff_r_result);

}

void lib_hdmi_fg_koffset_proc(void)
{

	lib_hdmi_fg_koffset_auto();
	lib_hdmi_cdr_rst(1);
	HDMI_DELAYUS(20);
	lib_hdmi_cdr_rst(0);
	HDMI_DELAYMS(10);

}

void lib_hdmi_fg_koffset_disable(void)
{

	hdmi_rx_reg_mask32(P0_B1, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_POW_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G1, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_POW_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_R1, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_POW_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), 0, HDMI_RX_PHY);

}

void lib_hdmi_z0_calibration(void)
{
	hdmi_rx_reg_mask32(Z0K,
		~(Z0K_reg_z0_adjr_0_mask | Z0K_reg_z0_adjr_1_mask | Z0K_reg_z0_adjr_2_mask),
		Z0K_reg_z0_adjr_0(ManualZ0) | Z0K_reg_z0_adjr_1(ManualZ0) | Z0K_reg_z0_adjr_2(ManualZ0),
		HDMI_RX_PHY);
}


void lib_hdmi_char_err_rst(unsigned char rst)
{
	if (rst) {
		hdmi_rx_reg_mask32(HDMI_CERCR, ~(HDMI_CERCR_en_mask), 0, HDMI_RX_MAC);
		hdmi_rx_reg_mask32(HDMI_CERCR,
			~(HDMI_CERCR_valid_reset_mask|HDMI_CERCR_reset_err_det_mask|HDMI_CERCR_reset_mask),
			(HDMI_CERCR_valid_reset_mask|HDMI_CERCR_reset_err_det_mask|HDMI_CERCR_reset_mask),
			HDMI_RX_MAC);
	} else {
		hdmi_rx_reg_mask32(HDMI_CERCR,
			~(HDMI_CERCR_valid_reset_mask|HDMI_CERCR_reset_err_det_mask|HDMI_CERCR_reset_mask),
			0, HDMI_RX_MAC);
	}
}

void lib_hdmi_char_err_start(unsigned char conti_mode, unsigned char period)
{
	hdmi_rx_reg_mask32(HDMI_CERCR, ~(HDMI_CERCR_en_mask), 0, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_CERCR,
		~(HDMI_CERCR_ch_locked_reset_mask|HDMI_CERCR_reset_mask),
		HDMI_CERCR_ch_locked_reset_mask|HDMI_CERCR_reset_mask, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_CERCR,
		~(HDMI_CERCR_valid_reset_mask|HDMI_CERCR_keep_err_det_mask),
		HDMI_CERCR_valid_reset_mask|HDMI_CERCR_keep_err_det_mask, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_CERCR,
		~(HDMI_CERCR_period_mask|HDMI_CERCR_mode_mask),
		HDMI_CERCR_period(period)|HDMI_CERCR_mode(conti_mode), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_CERCR,
		~(HDMI_CERCR_ch_locked_reset_mask|HDMI_CERCR_reset_mask), 0, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_CERCR,
		~(HDMI_CERCR_valid_reset_mask|HDMI_CERCR_keep_err_det_mask), 0, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_CERCR,
		~HDMI_CERCR_refer_implem_mask, HDMI_CERCR_refer_implem_mask, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_CERCR,
		~HDMI_CERCR_en_mask, HDMI_CERCR_en_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_char_err_det_done(void)
{
	unsigned char temp;

	temp = !HDMI_CERCR_get_en(hdmi_rx_reg_read32(HDMI_CERCR, HDMI_RX_MAC));
	return temp;
}

unsigned char lib_hdmi_char_err_get_error(unsigned int *r_err, unsigned int *g_err, unsigned int *b_err)
{
	unsigned int reg_val;

	reg_val = hdmi_rx_reg_read32(HDMI_CERCR, HDMI_RX_MAC);
	if (HDMI_CERCR_get_en(reg_val) &&
		(!HDMI_CERCR_get_ch0_over_max_err_num(reg_val) &&
		!HDMI_CERCR_get_ch1_over_max_err_num(reg_val) &&
		!HDMI_CERCR_get_ch2_over_max_err_num(reg_val)))
		return 0;/* Not yet finish counting */

	*b_err = HDMI_CERSR0_get_err_cnt0_video(hdmi_rx_reg_read32(HDMI_CERSR0, HDMI_RX_MAC));
	*g_err = HDMI_CERSR0_get_err_cnt1_video(hdmi_rx_reg_read32(HDMI_CERSR0, HDMI_RX_MAC));
	*r_err = HDMI_CERSR1_get_err_cnt2_video(hdmi_rx_reg_read32(HDMI_CERSR1, HDMI_RX_MAC));

	return 1;
}

void lib_hdmi_bit_err_start(unsigned char conti_mode, unsigned char period)
{
	/* Disable */
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_en_mask, 0, HDMI_RX_MAC);
	/* Reset cnt */
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_reset_mask, HDMI_VIDEO_BIT_ERR_DET_reset_mask, HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_mode_mask, HDMI_VIDEO_BIT_ERR_DET_mode(conti_mode), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_period_mask, HDMI_VIDEO_BIT_ERR_DET_period(period), HDMI_RX_MAC);
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_thd_mask, HDMI_VIDEO_BIT_ERR_DET_thd(1), HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_reset_mask, 0, HDMI_RX_MAC);

	/* wclr_out */
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_STATUS_B,
		~(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		HDMI_RX_MAC);

	/* wclr_out */
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_STATUS_G,
		~(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		HDMI_RX_MAC);

	/* wclr_out */
	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_STATUS_R,
		~(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		(HDMI_VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask |
		HDMI_VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		HDMI_RX_MAC);

	hdmi_rx_reg_mask32(HDMI_VIDEO_BIT_ERR_DET,
		~HDMI_VIDEO_BIT_ERR_DET_en_mask, HDMI_VIDEO_BIT_ERR_DET_en_mask, HDMI_RX_MAC);
}

unsigned char lib_hdmi_bit_err_det_done(void)
{
	unsigned char temp;

	temp = !HDMI_VIDEO_BIT_ERR_DET_get_en(hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_DET, HDMI_RX_MAC));
	return temp;
}

unsigned char lib_hdmi_bit_err_get_error(unsigned int *r_err, unsigned int *g_err, unsigned int *b_err)
{
	if (HDMI_VIDEO_BIT_ERR_DET_get_en(hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_DET, HDMI_RX_MAC)))
		return 0;/* Not yet finish counting */

	*r_err = HDMI_VIDEO_BIT_ERR_STATUS_R_get_bit_err_cnt_r(hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_R, HDMI_RX_MAC));
	*g_err = HDMI_VIDEO_BIT_ERR_STATUS_G_get_bit_err_cnt_g(hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_G, HDMI_RX_MAC));
	*b_err = HDMI_VIDEO_BIT_ERR_STATUS_B_get_bit_err_cnt_b(hdmi_rx_reg_read32(HDMI_VIDEO_BIT_ERR_STATUS_B, HDMI_RX_MAC));

	return 1;
}


#if BIST_DFE_SCAN
/*
 * Debug Functions
 */
void debug_hdmi_dfe_scan(void)
{
	signed char dfe_arg;
	unsigned int bit_r_err, bit_g_err, bit_b_err, ch_r_err, ch_g_err, ch_b_err;
	unsigned char mode;

	for (dfe_arg = 0; dfe_arg < 0x24; dfe_arg++) {
		lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), dfe_arg);
		//lib_hdmi_dfe_init_tap1((LN_R|LN_G|LN_B), dfe_arg);
		//lib_hdmi_dfe_init_tap2((LN_R|LN_G|LN_B), dfe_arg);
		HDMI_DELAYUS(100);

		lib_hdmi_bit_err_start(0, 10);
		lib_hdmi_char_err_start(0, 10);

		while (!lib_hdmi_bit_err_get_error(&bit_r_err, &bit_g_err, &bit_b_err))
			HDMI_DELAYMS(20);

		while (!lib_hdmi_char_err_get_error(&ch_r_err, &ch_g_err, &ch_b_err))
			HDMI_DELAYMS(20);

		HDMI_PRINTF("tap0=%02d, [CH](%05d, %05d, %05d); [BIT](%05d, %05d, %05d)\n",
			dfe_arg, ch_r_err, ch_g_err, ch_b_err, bit_r_err, bit_g_err, bit_b_err);
	}

	lib_hdmi_dfe_init_tap0(LN_B, phy_st.dfe_t[0].tap0);
	lib_hdmi_dfe_init_tap0(LN_G, phy_st.dfe_t[1].tap0);
	lib_hdmi_dfe_init_tap0(LN_R, phy_st.dfe_t[2].tap0);


	mode = REG_DFE_MODE_get_adapt_mode(hdmi_rx_reg_read32(REG_DFE_MODE, HDMI_RX_DFE));


	if (mode == 2) {
		for (dfe_arg = 0; dfe_arg < 60; dfe_arg++) {
			//lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), dfe_arg);
			//lib_hdmi_dfe_init_tap1((LN_R|LN_G|LN_B), dfe_arg);
			lib_hdmi_dfe_init_le((LN_R|LN_G|LN_B), dfe_arg);
			//lib_hdmi_dfe_init_tap2((LN_R|LN_G|LN_B), dfe_arg);
			HDMI_DELAYUS(100);

			lib_hdmi_bit_err_start(0, 10);
			lib_hdmi_char_err_start(0, 10);

			while (!lib_hdmi_bit_err_get_error(&bit_r_err, &bit_g_err, &bit_b_err))
				HDMI_DELAYMS(20);

			while (!lib_hdmi_char_err_get_error(&ch_r_err, &ch_g_err, &ch_b_err))
				HDMI_DELAYMS(20);

			HDMI_PRINTF("le=%02d, [CH](%05d, %05d, %05d); [BIT](%05d, %05d, %05d)\n",
				dfe_arg, ch_r_err, ch_g_err, ch_b_err, bit_r_err, bit_g_err, bit_b_err);
		}

		lib_hdmi_dfe_init_le(LN_B, phy_st.dfe_t[0].le);
		lib_hdmi_dfe_init_le(LN_G, phy_st.dfe_t[1].le);
		lib_hdmi_dfe_init_le(LN_R, phy_st.dfe_t[2].le);

	} else {
		/* mode 3 */
		for (dfe_arg = 0; dfe_arg < 60; dfe_arg++) {
			//lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), dfe_arg);
			lib_hdmi_dfe_init_tap1((LN_R|LN_G|LN_B), dfe_arg);
			//lib_hdmi_dfe_init_tap2((LN_R|LN_G|LN_B), dfe_arg);
			HDMI_DELAYUS(100);

			lib_hdmi_bit_err_start(0, 10);
			lib_hdmi_char_err_start(0, 10);

			while (!lib_hdmi_bit_err_get_error(&bit_r_err, &bit_g_err, &bit_b_err))
				HDMI_DELAYMS(20);

			while (!lib_hdmi_char_err_get_error(&ch_r_err, &ch_g_err, &ch_b_err))
				HDMI_DELAYMS(20);

			HDMI_PRINTF("le=%02d, [CH](%05d, %05d, %05d); [BIT](%05d, %05d, %05d)\n",
				dfe_arg, ch_r_err, ch_g_err, ch_b_err, bit_r_err, bit_g_err, bit_b_err);
		}

		lib_hdmi_dfe_init_tap1(LN_B, phy_st.dfe_t[0].tap1+phy_st.dfe_t[0].le);
		lib_hdmi_dfe_init_tap1(LN_G, phy_st.dfe_t[1].tap1+phy_st.dfe_t[1].le);
		lib_hdmi_dfe_init_tap1(LN_R, phy_st.dfe_t[2].tap1+phy_st.dfe_t[2].le);
	}


	for (dfe_arg = -15; dfe_arg < 15; dfe_arg++) {
		//lib_hdmi_dfe_init_tap0((LN_R|LN_G|LN_B), dfe_arg);
		//lib_hdmi_dfe_init_tap1((LN_R|LN_G|LN_B), dfe_arg);
		lib_hdmi_dfe_init_tap2((LN_R|LN_G|LN_B), dfe_arg);
		HDMI_DELAYUS(100);

		lib_hdmi_bit_err_start(0, 10);
		lib_hdmi_char_err_start(0, 10);

		while (!lib_hdmi_bit_err_get_error(&bit_r_err, &bit_g_err, &bit_b_err))
			HDMI_DELAYMS(20);

		while (!lib_hdmi_char_err_get_error(&ch_r_err, &ch_g_err, &ch_b_err))
			HDMI_DELAYMS(20);

		HDMI_PRINTF("tap2=%02d, [CH](%05d, %05d, %05d); [BIT](%05d, %05d, %05d)\n",
			dfe_arg, ch_r_err, ch_g_err, ch_b_err, bit_r_err, bit_g_err, bit_b_err);
	}

	lib_hdmi_dfe_init_tap2(LN_B, phy_st.dfe_t[0].tap2);
	lib_hdmi_dfe_init_tap2(LN_G, phy_st.dfe_t[1].tap2);
	lib_hdmi_dfe_init_tap2(LN_R, phy_st.dfe_t[2].tap2);

}
#endif
