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

#define HDMI_B_TEST_COUNT_MAX  1

#define	ManualZ0  0xE

/* TMDS clock define */
#define TMDS_6G     5688
#define TMDS_5G     4740
#define TMDS_4G     3792
#define TMDS_3G     2844
#define TMDS_1p5G   1422

#define Fore_Koff_Range  1 /* Range maybe 0  1  2   3 */
#define Fore_Koff_FIX    1

/*=================== Global Variable ===========================*/
UINT8 bSCDC_Enable_flag, bSCDC_debounce_cnt, bUPdata_flag;/* For hdmi 2.0 SCDC set flag */
HDMIRX_PHY_IDLE_PATCH_T hdmi_phy_idle_patch;
HDMIRX_IOCTL_STRUCT_T hdmi_ioctl_struct;

u_int32_t clock_bound_3g;
u_int32_t clock_bound_1p5g;
u_int32_t clock_bound_110m;
u_int32_t clock_bound_45m;

/* For DFE close timing setting */
UINT8 bDFE_Close_Flag, bDFE_Close_Cnt;
/*=========================================================*/

extern void Hdmi_HdcpFSM(void);

#if HDMI2p0
extern u_int8_t bHDMI_6G_flag;
extern u_int8_t b6G_detect_cnt;
#endif
extern HDMI_INFO_T hdmi;

const HDMI_PHY_PARAM_T hdmi_phy_param[] = {
/* QC 2016/01/18 */
/*  B_upper           M_code              PI_DIV              RATE_SEL                    CK_CS                   *EQ_manual                     CDR_KP                          CDR_KI                 *EQ_gain                 CK_Icp            pscaler			band_name */
/*             B_lower             N_code           DEMUX                   *CK_LDOD                      CK_RS                     *CDR_bias                       *CDR_KP2                  CDR_KD                *EQ_bias                   PR			vsel_ldo */
	{5860, 2844,    16,     0,     0,     1,      0x0,      0x3,      0x4,      0x2,      0x2,      0x1,    (0x08<<0),      0x0,      0x1,      0x0,    0x0,    0x1,    0x3,    0x0, 0x0,      7,   "300M~6000M half rate"},  /* 300~600 M */
	{2844, 1422,    36,     2,     1,     2,      0x1,      0x3,      0x4,      0x2,      0x4,      0x1,    (0x20<<0),      0x4,      0x1,      0x0,    0x1,    0x1,    0x7,    0x0, 0x0,      7,   "150M~300M full rate"},	  /* 150~300 M */
	{1422,  711,    36,     1,     2,     3,      0x2,      0x3,      0x4,      0x2,      0x9,      0x1,    (0x20<<0),      0x0,      0x0,      0x0,    0x1,    0x1,    0x7,    0x1, 0x0,      7,   "75M~150M full rate+DS1"},/* 75~150 M */
	{ 711,  355,    36,     0,     3,     3,      0x2,      0x3,      0x4,      0x2,      0x4,      0x1,    (0x10<<0),      0x0,      0x0,      0x0,    0x1,    0x1,    0x7,    0x2, 0x0,      7,   "37.5M~75M full rate+DS2"},	/* 37.5~75M */
	{ 355,  128,    76,     0,     4,     3,      0x2,      0x3,      0x4,      0x7,      0x4,      0x1,    (0x10<<0),      0x0,      0x0,      0x0,    0x1,    0x1,    0x3,    0x3, 0x0,      7,   "13.5M~37M full rate+DS3"}, /* 13.5M~ 37.5M */
};

void HDMI_MAG2_SetDFE_Close(void);

void hdmi_z0_set(unsigned char port, unsigned char lane, unsigned char enable)
{
	unsigned int bmask = 0;

	if (lane&LN_Z300POW)
		bmask |= Z0POW_reg_z0_z300pow(1<<port);

	if (lane&LN_CK)
		bmask |= Z0POW_reg_z0_z0pow_ck(1<<port);

	if (lane&LN_B)
		bmask |= Z0POW_reg_z0_z0pow_b(1<<port);

	if (lane&LN_G)
		bmask |= Z0POW_reg_z0_z0pow_g(1<<port);

	if (lane&LN_R)
		bmask |= Z0POW_reg_z0_z0pow_r(1<<port);

	hdmi_rx_reg_mask32(Z0POW, ~bmask, enable?bmask:0, HDMI_RX_PHY);
}

void Z0_Calibration(void)
{
	/* Z0 disable,Z0 manual=11000 */
	hdmi_rx_reg_mask32(Z0K, ~(Z0K_reg_z0_z0pow_mask|Z0K_reg_z0_stune_mask), 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(Z0K, ~(Z0K_reg_z0_adjr_0_mask|Z0K_reg_z0_adjr_1_mask|Z0K_reg_z0_adjr_2_mask),
		(Z0K_reg_z0_adjr_0(ManualZ0)|Z0K_reg_z0_adjr_1(ManualZ0)|Z0K_reg_z0_adjr_2(ManualZ0)), HDMI_RX_PHY);
}

void HDMI_MHL_Mode_Detect_Sel(UINT8 bHDMI_mode)
{
	if (bHDMI_mode) {
		hdmi_rx_reg_mask32(P0_CK1, ~p0_ck_2_CK_MD_REF_SEL, p0_ck_2_CK_MD_REF_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P1_CK1, ~p1_ck_2_CK_MD_REF_SEL, p1_ck_2_CK_MD_REF_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P2_CK1, ~p2_ck_2_CK_MD_REF_SEL, p2_ck_2_CK_MD_REF_SEL, HDMI_RX_PHY);
	} else {
		/* HHL mode */
		hdmi_rx_reg_mask32(P0_CK1, ~p0_ck_2_CK_MD_REF_SEL, 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P1_CK1, ~p1_ck_2_CK_MD_REF_SEL, 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P2_CK1, ~p2_ck_2_CK_MD_REF_SEL, 0, HDMI_RX_PHY);
	}
}

void Forground_EQ(void)
{
	/* Forground manual */
	/* Port0 */
	hdmi_rx_reg_mask32(P0_B1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_R1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(P1_B1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P1_G1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P1_R1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(P2_B1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P2_G1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P2_R1, ~(P1_b_1_FORE_KOFF_ADJR), _BIT20, HDMI_RX_PHY);

	HDMIRX_DEBUG("[%s] EQ manual 0x%08x", __func__, hdmi_rx_reg_read32(P1_B1, HDMI_RX_PHY));
}

void Hdmi_TriggerbMeasurement(UINT8 bport)
{
	/* mode dect set release */
	hdmi_rx_reg_mask32(REGD42, ~REGD42_p0_ck_md_rstb_mask, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD44, ~REGD44_p1_ck_md_rstb_mask, 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD46, ~REGD46_p2_ck_md_rstb_mask, 0, HDMI_RX_PHY);

	hdmi_rx_reg_mask32(REGD42, ~REGD42_p0_ck_md_rstb_mask, REGD42_p0_ck_md_rstb_mask, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD44, ~REGD44_p1_ck_md_rstb_mask, REGD44_p1_ck_md_rstb_mask, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD46, ~REGD46_p2_ck_md_rstb_mask, REGD46_p2_ck_md_rstb_mask, HDMI_RX_PHY);

	/* HDMI_PRINTF("Hdmi_TriggerbMeasurement\n"); */
	if (bport == 0)
		hdmi_rx_reg_mask32(REGD43, ~REGD43_p0_ck_md_ok_mask, REGD43_p0_ck_md_ok_mask, HDMI_RX_PHY);
	else if (bport == 1)
		hdmi_rx_reg_mask32(REGD45, ~REGD45_p1_ck_md_ok_mask, REGD45_p1_ck_md_ok_mask, HDMI_RX_PHY);
	else if (bport == 2)
		hdmi_rx_reg_mask32(REGD47, ~REGD47_p2_ck_md_ok_mask, REGD47_p2_ck_md_ok_mask, HDMI_RX_PHY);

	/* PMM clk detect function disable */
	hdmi_rx_reg_mask32(CLKDETCR, ~_BIT0, 0, HDMI_RX_MAC);
	/* Clr PMM clk detect flag */
	hdmi_rx_reg_mask32(CLKDETSR, ~_BIT0, _BIT0, HDMI_RX_MAC);
	/* PMM clk detect function enable */
	hdmi_rx_reg_mask32(CLKDETCR, ~_BIT0, _BIT0, HDMI_RX_MAC);
}

void Hdmi_PhyInit(void)
{
	/* Enable bandgap power */
	hdmi_rx_reg_mask32(BG, ~BG_reg_bg_pow_mask, BG_reg_bg_pow_mask, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(TOP_IN, ~(_BIT20|_BIT21), _BIT20, HDMI_RX_PHY);

	/* Dfault hdmi mode (other :MHL3.0 mode ) */
	HDMI_MHL_Mode_Detect_Sel(1);/* HDMI mode */

	Forground_EQ();

	/* Set z0 manual */
	Z0_Calibration();

	HDMI_MHL_Mode_Detect_Sel(1);
}

char Hdmi_IsbReady(void)
{
	if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC) & HDMI_Force_3G)/* For test CTS 3G */
		return TRUE;

	if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC) & MHL3_BYPASS_CBUS_CLK)
		return TRUE;

	if (REGD43_get_p0_ck_md_ok(hdmi_rx_reg_read32(REGD43, HDMI_RX_PHY)) == 0)
		return FALSE;
	else
		return TRUE;

	return TRUE;
}

int Hdmi_get_b_value(void)
{
	u_int8_t  bTimeout = 5;
	int wValue;

	if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC) & MHL3_BYPASS_CBUS_CLK)
		return 710;


	hdmi_rx_reg_mask32(REGD43, ~REGD43_p0_ck_md_ok_mask, REGD43_p0_ck_md_ok_mask, HDMI_RX_PHY);
	do {
		HDMI_DELAYMS(1);
		bTimeout--;
	} while ((!REGD43_get_p0_ck_md_ok(hdmi_rx_reg_read32(REGD43, HDMI_RX_PHY))) && (bTimeout));

	/* HDMI_PRINTF("Hdmi_get_b_value = %d\n", bTimeout); */
	if (bTimeout != 0) {
		hdmi_rx_reg_mask32(REGD43, ~REGD43_p0_ck_md_ok_mask, REGD43_p0_ck_md_ok_mask, HDMI_RX_PHY);
		wValue = REGD43_get_p0_ck_md_count(hdmi_rx_reg_read32(REGD43, HDMI_RX_PHY));
	} else {
		wValue = 0;
	}

	return wValue;
}

void hdmi_clear_b_struct(void)
{
	hdmi_ioctl_struct.b_pre = 0;
	hdmi_ioctl_struct.b_count = 0;
	hdmi_ioctl_struct.b  = 0;
}

void CMU_Reset(UINT8 benable)
{
	if (benable == 0) {
		/* Release (power on) */
		HDMI_PRINTF("CMU_Release\n");
		hdmi_rx_reg_mask32(ENABLE, ~(ENABLE_reg_p0_en_cmu_mask), (ENABLE_reg_p0_en_cmu_mask), HDMI_RX_PHY);
	} else {
		/* Reset (power off) */
		HDMI_PRINTF("CMU_Reset\n");
		hdmi_rx_reg_mask32(ENABLE, ~(ENABLE_reg_p0_en_cmu_mask), (0), HDMI_RX_PHY);
	}
}

void DEMUX_RESET(UINT8 benable)
{
	if (benable == 0) {
		/* Release */
		hdmi_rx_reg_mask32(RST, ~(RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask),
			(RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask), HDMI_RX_PHY);

		hdmi_rx_reg_mask32(RST, ~(RST_p0_ck_pllrstb_mask|RST_p0_ck_vcorstb_mask),
			(RST_p0_ck_pllrstb_mask|RST_p0_ck_vcorstb_mask), HDMI_RX_PHY);

		hdmi_rx_reg_mask32(RST, ~RST_dfe_rstn_n_mask, RST_dfe_rstn_n_mask, HDMI_RX_PHY);
	} else {
		hdmi_rx_reg_mask32(RST, ~RST_dfe_rstn_n_mask, 0, HDMI_RX_PHY);

		hdmi_rx_reg_mask32(RST, ~(RST_p0_ck_pllrstb_mask|RST_p0_ck_vcorstb_mask),
			0, HDMI_RX_PHY);

		hdmi_rx_reg_mask32(RST, ~(RST_p0_r_demux_rstb_mask|RST_p0_g_demux_rstb_mask|RST_p0_b_demux_rstb_mask),
			0, HDMI_RX_PHY);
	}
}


void CDR_RESET(UINT8 benable)
{
	if (benable == 0) {
		/* Release */
		hdmi_rx_reg_mask32(REGD0,
			~(REGD0_p0_r_dig_rst_n_mask | REGD0_p0_g_dig_rst_n_mask |
			REGD0_p0_b_dig_rst_n_mask | REGD0_p0_r_cdr_rst_n_mask |
			REGD0_p0_g_cdr_rst_n_mask | REGD0_p0_b_cdr_rst_n_mask),
			(REGD0_p0_r_dig_rst_n_mask | REGD0_p0_g_dig_rst_n_mask |
			REGD0_p0_b_dig_rst_n_mask | REGD0_p0_r_cdr_rst_n_mask |
			REGD0_p0_g_cdr_rst_n_mask | REGD0_p0_b_cdr_rst_n_mask),
			HDMI_RX_PHY);
		/* HDMI_PRINTF("[HDMI] DEMUX_release\n"); */
	} else {
		/* Reset */
		hdmi_rx_reg_mask32(REGD0, ~(REGD0_p0_r_dig_rst_n_mask|REGD0_p0_g_dig_rst_n_mask|REGD0_p0_b_dig_rst_n_mask),
			0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(REGD0, ~(REGD0_p0_r_cdr_rst_n_mask|REGD0_p0_g_cdr_rst_n_mask|REGD0_p0_b_cdr_rst_n_mask),
			0, HDMI_RX_PHY);
		/* HDMI_PRINTF("[HDMI] CDR_RESET\n"); */
	}
}


void DIC_AFIFO_ENABLE(u_int8_t enable)
{
	if (enable == 1) {
		HDMI_PRINTF("DIC_AFIFO_ENABLE\n");
		hdmi_rx_reg_mask32(CH_CR,
			~(CH_CR_r_ch_afifo_en_mask|CH_CR_g_ch_afifo_en_mask|CH_CR_b_ch_afifo_en_mask),
			(CH_CR_r_ch_afifo_en_mask|CH_CR_g_ch_afifo_en_mask|CH_CR_b_ch_afifo_en_mask), HDMI_RX_MAC);
	} else {
		hdmi_rx_reg_mask32(CH_CR,
			~(CH_CR_r_ch_afifo_en_mask|CH_CR_g_ch_afifo_en_mask|CH_CR_b_ch_afifo_en_mask),
			0, HDMI_RX_MAC);
	}
}

void CLOSE_RST_MAC(void)
{
	hdmi_rx_reg_mask32(TMDS_DPC_SET0, ~(TMDS_DPC_SET0_dpc_en_mask), 0, HDMI_RX_MAC);
	/* Dic fifio reset */
	DIC_AFIFO_ENABLE(0);

	/* Disable TMDS input */
	hdmi_rx_reg_mask32(TMDS_PWDCTL,
		~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),
		0, HDMI_RX_MAC);
	/* HDMI&DVI function disable */
	hdmi_rx_reg_mask32(TMDS_Z0CC, ~TMDS_Z0CC_hde_mask, 0, HDMI_RX_MAC);

	/* Analog cdr reset */
	CDR_RESET(1);
	DEMUX_RESET(1);
	CMU_Reset(1);
}

void OPEN_RST_MAC(void)
{
	hdmi_rx_reg_mask32(TMDS_Z0CC, ~TMDS_Z0CC_hde_mask, TMDS_Z0CC_hde(1), HDMI_RX_MAC);
	usleep_range(1000, 1100);
	HDMI_PRINTF("0xb800d01c=0x%x--MAC reset\n",
		hdmi_rx_reg_read32(TMDS_PWDCTL, HDMI_RX_MAC));

	/* Enable TMDS input */
	hdmi_rx_reg_mask32(TMDS_PWDCTL,
		~(TMDS_PWDCTL_ebip_mask|TMDS_PWDCTL_egip_mask|TMDS_PWDCTL_erip_mask|TMDS_PWDCTL_ecc_mask),
		(TMDS_PWDCTL_ebip(1)|TMDS_PWDCTL_egip(1)|TMDS_PWDCTL_erip(1)|TMDS_PWDCTL_ecc(1)), HDMI_RX_MAC);

	usleep_range(1000, 1100);
	HDMI_PRINTF("0xb800d01c=0x%x--MAC set\n",
		hdmi_rx_reg_read32(TMDS_PWDCTL, HDMI_RX_MAC));

	DIC_AFIFO_ENABLE(1);
	hdmi_rx_reg_mask32(TMDS_DPC_SET0, ~(TMDS_DPC_SET0_dpc_en_mask), TMDS_DPC_SET0_dpc_en_mask, HDMI_RX_MAC);
}

void DFE_POWER(u_int8_t enable)
{
	if (enable) {
		hdmi_rx_reg_mask32(P0_B3, ~(P1_b_9_DFE_ADAPTION_POW_EN|P1_b_9_DFE_TAP_EN), (P1_b_9_DFE_ADAPTION_POW_EN|DFE_HDMI_RX_PHY_P1_b_tap_en(0x3)), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_G3, ~(P1_b_9_DFE_ADAPTION_POW_EN|P1_b_9_DFE_TAP_EN), (P1_b_9_DFE_ADAPTION_POW_EN|DFE_HDMI_RX_PHY_P1_b_tap_en(0x3)), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(P0_R3, ~(P1_b_9_DFE_ADAPTION_POW_EN|P1_b_9_DFE_TAP_EN), (P1_b_9_DFE_ADAPTION_POW_EN|DFE_HDMI_RX_PHY_P1_b_tap_en(0x3)), HDMI_RX_PHY);
	}
}

void SetClockBoundary(void)
{
	clock_bound_3g = TMDS_3G;
	clock_bound_1p5g = TMDS_1p5G;
	clock_bound_45m = 430;
	clock_bound_110m = 1042;
	HDMI_PRINTF("[HDMI] clock_bound_3g=%d\n", clock_bound_3g);
}

void EQ_bias_band_setting(u_int32_t b)
{
	UINT32 B1_addr, G1_addr, R1_addr;
	UINT32 B2_addr, G2_addr, R2_addr;
	UINT32 B3_addr, G3_addr, R3_addr;

	DFE_POWER(1);

	B1_addr = P0_B1;
	B2_addr = P0_B2;
	B3_addr = P0_B3;
	G1_addr = P0_G1;
	G2_addr = P0_G2;
	G3_addr = P0_G3;
	R1_addr = P0_R1;
	R2_addr = P0_R2;
	R3_addr = P0_R3;

	SetClockBoundary();

	if (b > clock_bound_3g) {
		/* Over  3G HBR */

#if 1/* QC 2016/01/18 */
		/*B lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA|P0_b_7_LEQ_ISEL_400uA|P0_b_6_LEQ_BIT_RATE_HBR|P0_b_6_LEQ_BIT_RATE_HBR|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);
		/*G lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA|P0_b_7_LEQ_ISEL_400uA|P0_g_6_LEQ_BIT_RATE_HBR|P0_g_6_LEQ_BIT_RATE_HBR|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);

		/* R lane */
		/* tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_r_7_TAP0_ISEL|P0_r_7_LEQ_ISEL|P0_r_6_LEQ_BIT_RATE|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA|P0_b_7_LEQ_ISEL_400uA|P0_r_6_LEQ_BIT_RATE_HBR|P0_r_6_LEQ_BIT_RATE_HBR|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ_1p25X),
			HDMI_RX_PHY);
#endif

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
#if 1/* QC 2016/01/18 */
		hdmi_rx_reg_mask32(B1_addr, ~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), P1_b_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr, ~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), P1_g_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr, ~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), P1_r_2_LEQ_BIT_RATE_HBR, HDMI_RX_PHY);
#endif

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr, ~(P1_b_7_PI_ISEL|P1_b_8_BY_PASS_PR|P1_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr, ~(P1_g_7_PI_ISEL|P1_g_8_BY_PASS_PR|P1_g_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr, ~(P1_r_7_PI_ISEL|P1_r_8_BY_PASS_PR|P1_r_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);

		/* PR sel */
		if ((b > TMDS_5G) && (b < TMDS_6G)) {
			/* 5G~6G */
			/* B */
			hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, 0, HDMI_RX_PHY);
			/* G */
			hdmi_rx_reg_mask32(G3_addr, ~P0_g_12_PR, 0, HDMI_RX_PHY);
			/* R */
			hdmi_rx_reg_mask32(R3_addr, ~P0_r_12_PR, 0, HDMI_RX_PHY);
		} else if ((b > TMDS_4G) && (b < TMDS_5G)) {
			/* 4G~5G */
			/* B */
			hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, _BIT24, HDMI_RX_PHY);
			/* G */
			hdmi_rx_reg_mask32(G3_addr, ~P0_g_12_PR, _BIT24, HDMI_RX_PHY);
			/*R */
			hdmi_rx_reg_mask32(R3_addr, ~P0_r_12_PR, _BIT24, HDMI_RX_PHY);
		} else {
			/* 3G~ 4G */
			/* B */
			hdmi_rx_reg_mask32(B3_addr, ~P0_b_12_PR, _BIT25, HDMI_RX_PHY);
			/* G */
			hdmi_rx_reg_mask32(G3_addr, ~P0_g_12_PR, _BIT25, HDMI_RX_PHY);
			/* R */
			hdmi_rx_reg_mask32(R3_addr, ~P0_r_12_PR, _BIT25, HDMI_RX_PHY);
		}
		HDMI_PRINTF("bias_band > 3G\n");

	} else if (b > clock_bound_1p5g) {
		/* 3G ~1.5G */

		/* B lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_7_TAP0_ISEL_400uA|P0_b_7_LEQ_ISEL_200uA|P0_b_6_LEQ_BIT_RATE_MBR|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ_1X),
			HDMI_RX_PHY);

		/* G lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_g_7_TAP0_ISEL_400uA|P0_g_7_LEQ_ISEL_200uA|P0_g_6_LEQ_BIT_RATE_MBR|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ_1X),
			HDMI_RX_PHY);

		/* R lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
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
#if 1/* QC 2016/01/18 */
		hdmi_rx_reg_mask32(B1_addr, ~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), (P1_b_2_LEQ_BIT_RATE_MBR|P0_b_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr, ~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), (P1_g_2_LEQ_BIT_RATE_MBR|P0_g_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr, ~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), (P1_r_2_LEQ_BIT_RATE_MBR|P0_r_CLK_PIX2_RATE_SEL), HDMI_RX_PHY);
#endif

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr, ~(P1_b_7_PI_ISEL|P1_b_8_BY_PASS_PR|P1_b_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr, ~(P1_g_7_PI_ISEL|P1_g_8_BY_PASS_PR|P1_g_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr, ~(P1_r_7_PI_ISEL|P1_r_8_BY_PASS_PR|P1_r_6_LEQ_PASSIVE_CORNER), 0, HDMI_RX_PHY);
		HDMI_PRINTF("Bias_band = 1.5G~3G\n");
	} else {
		/* Under 1.5G */

		/* B lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
#if 1/* QC 2016/01/18 */
		hdmi_rx_reg_mask32(B2_addr,
			~(P0_b_7_TAP0_ISEL|P0_b_7_LEQ_ISEL|P0_b_6_LEQ_BIT_RATE|P0_b_6_TAP0_HBR|P0_b_5_LEQ_CURRENT_ADJ),
			(P0_b_5_LEQ_CURRENT_ADJ_1X|P0_b_7_TAP0_ISEL_400uA),
			HDMI_RX_PHY);

		/* G lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(G2_addr,
			~(P0_g_7_TAP0_ISEL|P0_g_7_LEQ_ISEL|P0_g_6_LEQ_BIT_RATE|P0_g_6_TAP0_HBR|P0_g_5_LEQ_CURRENT_ADJ),
			(P0_g_5_LEQ_CURRENT_ADJ_1X|P0_g_7_TAP0_ISEL_400uA),
			HDMI_RX_PHY);

		/* R lane, tap0_ISEL   LEQ_ISEL   EQ_bit_rate  tap_HBR */
		hdmi_rx_reg_mask32(R2_addr,
			~(P0_r_7_TAP0_ISEL|P0_r_7_LEQ_ISEL|P0_r_6_LEQ_BIT_RATE|P0_r_6_TAP0_HBR|P0_r_5_LEQ_CURRENT_ADJ),
			(P0_r_5_LEQ_CURRENT_ADJ_1X|P0_r_7_TAP0_ISEL_400uA),
			HDMI_RX_PHY);
#endif

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
#if 1/* QC 2016/01/18 */
		hdmi_rx_reg_mask32(B1_addr, ~(P1_b_2_LEQ_BIT_RATE_mask|P0_b_CLK_PIX2_RATE_SEL), P0_b_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G1_addr, ~(P1_g_2_LEQ_BIT_RATE_mask|P0_g_CLK_PIX2_RATE_SEL), P0_g_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R1_addr, ~(P1_r_2_LEQ_BIT_RATE_mask|P0_r_CLK_PIX2_RATE_SEL), P0_r_CLK_PIX2_RATE_SEL, HDMI_RX_PHY);
#endif

		/* PI_SEL  & pr bypass */
		hdmi_rx_reg_mask32(B2_addr, ~(P1_b_7_PI_ISEL|P1_b_8_BY_PASS_PR|P1_b_6_LEQ_PASSIVE_CORNER), _BIT16, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(G2_addr, ~(P1_g_7_PI_ISEL|P1_g_8_BY_PASS_PR|P1_g_6_LEQ_PASSIVE_CORNER), _BIT16, HDMI_RX_PHY);
		hdmi_rx_reg_mask32(R2_addr, ~(P1_r_7_PI_ISEL|P1_r_8_BY_PASS_PR|P1_r_6_LEQ_PASSIVE_CORNER), _BIT16, HDMI_RX_PHY);
		HDMI_PRINTF("bias_band <1.5G\n");
	}

}

void HDMI_Set_Phy_Table(u_int8_t mode)
{
	u_int32_t wReg1, wReg2, wCk1Reg, wCk2Reg, ck_md_sel;
	u_int32_t B2Reg, G2REG, R2REG;

	wReg1 = REGD16;
	wReg2 = REGD0;
	wCk1Reg = P0_CK1;
	B2Reg = P0_B2;
	G2REG = P0_G2;
	R2REG = P0_R2;
	wCk2Reg = P0_CK2;
	ck_md_sel = REGD42;

	/* Set M & N & PI_DIV & DEMUX   */
	/* M code */
	hdmi_rx_reg_mask32(wReg1, ~REGD16_reg_p0_n_code_mask,
		hdmi_phy_param[mode].M_code<<REGD16_reg_p0_n_code_shift, HDMI_RX_PHY);
	/* N code */
	hdmi_rx_reg_mask32(wCk1Reg, ~(p1_ck_3_CMU_N_code|p1_ck_3_CMU_PREDIVN),
		hdmi_phy_param[mode].N_code<<P0_CK1_reg_p0_ck_3_CMU_N_code_shift, HDMI_RX_PHY);

	/* PI_DIV code */
	hdmi_rx_reg_mask32(B2Reg, ~P0_b_8_PR_RATE_SEL, hdmi_phy_param[mode].PI_DIV<<P0_B2_reg_p0_b_8_PR_RATE_SEL_shift, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G2REG, ~P0_b_8_PR_RATE_SEL, hdmi_phy_param[mode].PI_DIV<<P0_B2_reg_p0_b_8_PR_RATE_SEL_shift, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R2REG, ~P0_b_8_PR_RATE_SEL, hdmi_phy_param[mode].PI_DIV<<P0_B2_reg_p0_b_8_PR_RATE_SEL_shift, HDMI_RX_PHY);

	/* DEMUX code */
	hdmi_rx_reg_mask32(B2Reg, ~P0_b_8_DEMUX, hdmi_phy_param[mode].DEMUX<<P0_B2_reg_p0_b_8_DEMUX_shift, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(G2REG, ~P0_b_8_DEMUX, hdmi_phy_param[mode].DEMUX<<P0_B2_reg_p0_b_8_DEMUX_shift, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(R2REG, ~P0_b_8_DEMUX, hdmi_phy_param[mode].DEMUX<<P0_B2_reg_p0_b_8_DEMUX_shift, HDMI_RX_PHY);

	/* LDO enable, CMU VCO select */
	hdmi_rx_reg_mask32(wCk2Reg,
		~(P0_ck_5_CMU_SEL_R1_mask | P0_ck_5_CMU_SEL_PUMP_I_mask |
		P0_ck_6_CMU_BIG_KVCO_mask | P0_ck_7_CMU_BYPASS_PI_mask |
		P0_ck_8_LDO_EN_mask | P0_ck_8_VSEL_LDO_D_mask |
		P0_ck_8_VSEL_LDO_A_mask),
		((hdmi_phy_param[mode].CK_RS<<0) | (hdmi_phy_param[mode].CK_Icp<<4) |
		P0_ck_6_CMU_BIG_KVCO_mask | P0_ck_7_CMU_BYPASS_PI_mask | P0_ck_8_LDO_EN_mask |
		DFE_HDMI_RX_PHY_P0_VSEL_LDO_A(hdmi_phy_param[mode].vsel_ldo)),
		HDMI_RX_PHY);

	/* KP set */
	hdmi_rx_reg_mask32(wReg2,
		~(REGD0_reg_p0_kp_mask|REGD0_reg_p0_bypass_sdm_int_mask|REGD5_reg_p1_rate_sel_mask),
		((hdmi_phy_param[mode].CDR_KP<<REGD0_reg_p0_kp_shift)|REGD0_reg_p0_bypass_sdm_int_mask|(REGD5_reg_p1_rate_sel(hdmi_phy_param[mode].RATE_SEL))),
		HDMI_RX_PHY);

	hdmi_rx_reg_mask32(ck_md_sel, ~REGD42_reg_p0_ck_md_sel_mask, REGD42_reg_p0_ck_md_sel(0), HDMI_RX_PHY);

#if 1/* QC 2016/01/18 */
	hdmi_rx_reg_mask32(wCk2Reg, ~(P1_ck_6_CMU_SEL_CS_mask), hdmi_phy_param[mode].CK_CS<<8, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(wReg2, ~(REGD0_reg_p0_ki_mask), hdmi_phy_param[mode].CDR_KI<<REGD0_reg_p0_ki_shift, HDMI_RX_PHY);
#endif
}

void PHY_DFE_Setting(UINT8 mode)
{
	hdmi_rx_reg_mask32(REGD21,
		~(REGD28_reg_p1_auto_mode_mask | REGD28_reg_p1_adp_en_manual_mask | REGD28_reg_p1_adp_time_mask |
		REGD28_reg_p1_calib_time_mask | REGD28_reg_p1_calib_late_mask | REGD28_reg_p1_vco_coarse_mask |
		REGD28_reg_p1_divide_num_mask | REGD28_reg_p1_init_time_mask),
		(REGD28_reg_p1_adp_en_manual_mask | _BIT25 | _BIT20 | _BIT18 | _BIT16 | _BIT15 | _BIT9 | _BIT7 | _BIT1),
		HDMI_RX_PHY);


	hdmi_rx_reg_mask32(REGD24, ~(REGD31_reg_p1_cp_time_mask|REGD31_reg_p1_timer_4_mask), (REGD31_reg_p1_cp_time(4)|REGD31_reg_p1_timer_4(2)), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD25, ~(REGD32_reg_p1_timer_5_mask|REGD32_reg_p1_timer_6_mask), REGD32_reg_p1_timer_6(7), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD26,
		~(REGD33_reg_p1_rxidle_bypass_mask|REGD33_reg_p1_slope_band_mask|REGD33_reg_p1_old_mode_mask|_BIT15),
		(REGD33_reg_p1_rxidle_bypass_mask|REGD33_reg_p1_slope_band(8)|_BIT15),
		HDMI_RX_PHY);

	/* Digital part Reg setting */
	hdmi_rx_reg_mask32(PHY_FIFO_CR,
		~(PHY_FIFO_CR_port0_b_afifo_en_mask | PHY_FIFO_CR_port0_b_flush_mask |
		PHY_FIFO_CR_port0_g_afifo_en_mask | PHY_FIFO_CR_port0_g_flush_mask |
		PHY_FIFO_CR_port0_r_afifo_en_mask | PHY_FIFO_CR_port0_r_flush_mask),
		(PHY_FIFO_CR_port0_b_afifo_en_mask | PHY_FIFO_CR_port0_b_flush_mask |
		PHY_FIFO_CR_port0_g_afifo_en_mask | PHY_FIFO_CR_port0_g_flush_mask |
		PHY_FIFO_CR_port0_r_afifo_en_mask | PHY_FIFO_CR_port0_r_flush_mask),
		HDMI_RX_MAC);
}

void DFE_second_flow(void)
{
	UINT8 bLan0_TAP0Max;
	UINT8 bLan1_TAP0Max;
	UINT8 bLan2_TAP0Max;

	HDMI_PRINTF("[DFE open] ENABLE  VTH & TAP0\n");
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(1), HDMI_RX_DEF);
	HDMI_PRINTF("[DFE open] ENABLE  VTH & TAP0\n");
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~(REG_dfe_adapt_en_lane0_TAP0|REG_dfe_adapt_en_lane0_Vth), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~(REG_dfe_adapt_en_lane1_TAP0|REG_dfe_adapt_en_lane1_Vth), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~(REG_dfe_adapt_en_lane2_TAP0|REG_dfe_adapt_en_lane2_Vth), 0, HDMI_RX_DEF);

	/* Read Tap0 max */
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 0<<limit_set_lane_shift, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, 0, HDMI_RX_DEF);
	usleep_range(10000, 11000);
	bLan0_TAP0Max = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));
	HDMI_PRINTF("[DFE open] TAP0 MAX lane0 =%x\n", bLan0_TAP0Max);

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 1<<limit_set_lane_shift, HDMI_RX_DEF);
	bLan1_TAP0Max = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));
	HDMI_PRINTF("[DFE open] TAP0 MAX lane1 =%x\n", bLan1_TAP0Max);

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 2<<limit_set_lane_shift, HDMI_RX_DEF);
	bLan2_TAP0Max = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));
	HDMI_PRINTF("[DFE open] TAP0 MAX lane2 =%x\n", bLan2_TAP0Max);

	/* LOAD TAP0 max -1  & Vth 4 */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap0_init_lane0(bLan0_TAP0Max-1))|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap0_init_lane0(bLan1_TAP0Max-1))|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap0_init_lane0_mask|REG_DFE_INIT0_L0_vth_init_lane0_mask),
		(REG_DFE_INIT0_L0_tap0_init_lane0(bLan2_TAP0Max-1))|REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0,
		~(load_in_init_lane0_tap0|load_in_init_lane0_vth),
		(load_in_init_lane0_tap0|load_in_init_lane0_vth), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1,
		~(load_in_init_lane0_tap0|load_in_init_lane0_vth),
		(load_in_init_lane0_tap0|load_in_init_lane0_vth), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2,
		~(load_in_init_lane0_tap0|load_in_init_lane0_vth),
		(load_in_init_lane0_tap0|load_in_init_lane0_vth), HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(load_in_init_lane0_tap0|load_in_init_lane0_vth), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(load_in_init_lane0_tap0|load_in_init_lane0_vth), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(load_in_init_lane0_tap0|load_in_init_lane0_vth), 0, HDMI_RX_DEF);

}

void PHY_FORE_KOFF(void)
{
	UINT32 w_b_addr_control;
	UINT32 w_g_addr_control;
	UINT32 w_r_addr_control;
	UINT32 w_b_addr_result;
	UINT32 w_g_addr_result;
	UINT32 w_r_addr_result;
	UINT32 koff_r_result;
	UINT32 koff_g_result;
	UINT32 koff_b_result;
	UINT8 i;
	UINT8 j;

	w_b_addr_control = P0_B1;
	w_g_addr_control = P0_G1;
	w_r_addr_control = P0_R1;
	w_b_addr_result = P0_B4;
	w_g_addr_result = P0_G4;
	w_r_addr_result = P0_R4;

	/* Initial circuit power */
	hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK|P0_b_4_FORE_POW_FORE_KOFF),
		(P0_b_3_FORE_EN_FORE_KOFF|P0_b_4_FORE_KOFF_AUTOK), HDMI_RX_PHY);
	/* Cut input off */
	hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_1_inputoff), P0_b_1_inputoff, HDMI_RX_PHY);

	/* For b lane */
	for (i = 0; i < Fore_Koff_Range+1; i++) {
#if Fore_Koff_FIX
		hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);
#endif
		/* Set k off range */
		hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);
		/* Start cal */
		hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		j = 0;
		while (!((hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY)) & P0_B4_reg_p0_b_koffok_mask)) {
			if (j >= 3) {
				HDMIRX_INFO("Wait b lane koff timeout\n");
				break;
			}
			usleep_range(10000, 11000);/* Wait for koffok */
			j++;
		}

		if (hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)

		/* For dummy write , or koff_g_result can't up date */
		koff_b_result = 0x01;
		koff_b_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_b_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)) {
			HDMI_PRINTF("PHY_FORE_KOFF range =%x OK ! B lane fore =0x%x\n",
				i, koff_b_result);
			break;
		}

		HDMI_PRINTF("PHY_FORE_KOFF range%u out of B range\n", i);

	}


	/* For g lane */
	for (i = 0; i < Fore_Koff_Range+1; i++) {
#if  Fore_Koff_FIX
		hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);
#endif
		/* Set k off range */
		hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);

		/* Start cal */
		hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		j = 0;
		while (!((hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY)) & P0_B4_reg_p0_b_koffok_mask)) {
			if (j >= 3) {
				HDMIRX_INFO("Wait g lane koff timeout\n");
				break;
			}
			usleep_range(10000, 11000);/* Wait for koffok */
			j++;
		}

		if (hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)
			koff_g_result = 0x01;/* For dummy write , or koff_g_result can't up date */

		koff_g_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_g_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)) {
			HDMI_PRINTF("PHY_FORE_KOFF range =%d OK ! G lane fore =%x\n",
				i, koff_g_result);
			break;
		}

		HDMI_PRINTF("PHY_FORE_KOFF range%u out of G range\n", i);
	}


	/* For r lane */
	for (i = 0; i < 3+1; i++) {
#if Fore_Koff_FIX
		hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), 0, HDMI_RX_PHY);
#endif
		/* Set k off range */
		hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_1_FORE_KOFF_RANGE), i<<21, HDMI_RX_PHY);

		/* Start cal */
		hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_4_FORE_POW_FORE_KOFF), P0_b_4_FORE_POW_FORE_KOFF, HDMI_RX_PHY);

		/* Wait finish cal */
		/* QC 2016/01/18 */
		j = 0;
		while (!((hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY))&P0_B4_reg_p0_b_koffok_mask)) {
			if (j >= 3) {
				HDMIRX_INFO("Wait R lane koff timeout\n");
				break;
			}
			usleep_range(10000, 11000);/* Wait for koffok */
			j++;
		}

		if (hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)
			koff_r_result = 0x01;/* For dummy write , or koff_g_result can't up date */

		koff_r_result = P0_B4_get_reg_p0_b_koff_sel(hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY));

		if (!(hdmi_rx_reg_read32(w_r_addr_result, HDMI_RX_PHY) & P0_B4_reg_p0_b_koff_bound_mask)) {
			HDMI_PRINTF("PHY_FORE_KOFF range =%x OK ! R lane fore =0x%x\n",
				i, koff_r_result);
			break;
		}

		HDMI_PRINTF("PHY_FORE_KOFF range%u out of R range\n", i);
	}

	/* Cut input on */
	hdmi_rx_reg_mask32(w_b_addr_control, ~(P0_b_1_inputoff), 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_g_addr_control, ~(P0_b_1_inputoff), 0, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(w_r_addr_control, ~(P0_b_1_inputoff), 0, HDMI_RX_PHY);

	HDMI_PRINTF("PHY_FORE_KOFF B lane fore =%x ,G lane fore =%x,R lane fore =%x\n",
		koff_b_result, koff_g_result, koff_r_result);

}

void LOAD_LE_MAX(void)
{
	UINT8 bLan0_LEMax;
	UINT8 bLan1_LEMax;
	UINT8 bLan2_LEMax;

	/* Read Tap0 max */
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 0<<limit_set_lane_shift, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, limit_sel(4), HDMI_RX_DEF);

	bLan0_LEMax = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 1<<limit_set_lane_shift, HDMI_RX_DEF);
	bLan1_LEMax = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, 2<<limit_set_lane_shift, HDMI_RX_DEF);
	bLan2_LEMax = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	HDMI_PRINTF("[PHY][DFE open] LE MAX lane0 =0x%x\n", bLan0_LEMax);
	HDMI_PRINTF("[PHY][DFE open] LE MAX lane1 =0x%x\n", bLan1_LEMax);
	HDMI_PRINTF("[PHY][DFE open] LE MAX lane2 =0x%x\n", bLan2_LEMax);

    /* Load LE max */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0, ~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), (REG_DFE_INIT0_L0_tap1_init_lane0(bLan0_LEMax)), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1, ~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), (REG_DFE_INIT0_L0_tap1_init_lane0(bLan1_LEMax)), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2, ~(REG_DFE_INIT0_L0_tap1_init_lane0_mask), (REG_DFE_INIT0_L0_tap1_init_lane0(bLan2_LEMax)), HDMI_RX_DEF);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(load_in_init_lane0_tap1), (load_in_init_lane0_tap1), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(load_in_init_lane0_tap1), (load_in_init_lane0_tap1), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(load_in_init_lane0_tap1), (load_in_init_lane0_tap1), HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(load_in_init_lane0_tap1), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(load_in_init_lane0_tap1), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(load_in_init_lane0_tap1), 0, HDMI_RX_DEF);
}

void Dump_DFE_Para(u_int8_t lane)
{
	UINT8 bLEmax;
	UINT8 bLEmin;
	UINT8 bTap0min;
	UINT8 bTap0max;
	UINT8 bTap1;

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_lane_mask, lane<<limit_set_lane_shift, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, 0, HDMI_RX_DEF);

	bTap0max = get_Tap0_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, limit_sel(1), HDMI_RX_DEF);

	bTap0min = get_Tap0_min(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, limit_sel(4), HDMI_RX_DEF);

	bLEmax = get_LEQ_max(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~limit_set_mask, limit_sel(5), HDMI_RX_DEF);

	bLEmin = get_LEQ_min(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	/* Read DFE result */
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_lane_mask, lane<<coef_set_lane_shift, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_mask, 0, HDMI_RX_DEF);

	HDMI_PRINTF("[PHY] ********************Lane%d******************\n", lane);
	HDMI_PRINTF("[PHY] Lane%d Tap0 max = 0x%02x, min = 0x%02x\n", lane, bTap0max, bTap0min);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_mask, coef_sel(1), HDMI_RX_DEF);

	HDMI_PRINTF("[PHY] Lane%d COEF Tap0=0x%02x\n",
		lane, get_TAP0_coef(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF)));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_mask, coef_sel(2), HDMI_RX_DEF);

	bTap1 = get_TAP1_coef(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_mask, coef_sel(3), HDMI_RX_DEF);

	HDMI_PRINTF("Tap1=0x%02x, Tap2=%+d\n",
		bTap1, (get_TAP2_coef_sign(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF))) ?
		-get_TAP2_coef(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF)) : get_TAP2_coef(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF)));

	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~coef_set_mask, coef_sel(7), HDMI_RX_DEF);

	HDMI_PRINTF("[PHY] Lane%d LE max = 0x%02x, min = 0x%02x\n", lane, bLEmax, bLEmin);

	HDMI_PRINTF("[PHY] Lane%d LE COEF = 0x%x\n\n",
		lane, get_LE1_coef(hdmi_rx_reg_read32(REG_DFE_READBACK, HDMI_RX_DEF)));

}

void HDMI_MAG2_SetDFE(int b, int dfe_mode)
{
	HDMI_PRINTF("[PHY][%s] b(%d) dfe_mode(%d)\n", __func__, b, dfe_mode);
	/* Script file */
	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~(REG_DFE_MODE_adapt_mode_mask |
		REG_DFE_MODE_edge_det_mode_mask |
		REG_DFE_MODE_transition_only_mask |
		REG_DFE_MODE_tap1_delay_mask |
		REG_DFE_MODE_tap24_delay_mask |
		REG_DFE_MODE_le_delay_mask |
		REG_DFE_MODE_servo_delay_mask |
		REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_dfe_adapt_rstb_mask |
		REG_DFE_MODE_tap0_notrans_mask |
		REG_DFE_MODE_servo_notrans_mask),
		(REG_DFE_MODE_adapt_mode(dfe_mode) |
		REG_DFE_MODE_edge_det_mode(0) |
		REG_DFE_MODE_transition_only_mask |
		REG_DFE_MODE_tap1_delay(1) |
		REG_DFE_MODE_tap24_delay(1) |
		REG_DFE_MODE_le_delay(1) |
		REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_tap0_notrans_mask |
		REG_DFE_MODE_servo_notrans_mask |
		_BIT16),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_DFE_EN_L0_clk_inv_lane0_mask |
		REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask |
		REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask |
		REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask |
		REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) |
		REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(22),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_DFE_EN_L1_clk_inv_lane1_mask |
		REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask |
		REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask |
		REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask |
		REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) |
		REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(22),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_DFE_EN_L2_clk_inv_lane2_mask |
		REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask |
		REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask |
		REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask |
		REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) |
		REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(22),
		HDMI_RX_DEF);

	/* Set initial value  TAP0 TAP1 TAP2 TAP3 */
	/* Tap1 =0xc Tap0 =0xc servo =0xf */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0xc) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0xc) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0xc) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);

	/* Adapt reset release */
	hdmi_rx_reg_mask32(REG_DFE_MODE, ~(REG_DFE_MODE_dfe_adapt_rstb_mask), REG_DFE_MODE_dfe_adapt_rstb_mask, HDMI_RX_DEF);
	/* Set run length = 4 */
	hdmi_rx_reg_mask32(REG_DFE_GAIN, ~(REG_DFE_GAIN_trans_rlength_mask), REG_DFE_GAIN_trans_rlength(2), HDMI_RX_DEF);
	/* Set tap tap1 tap2 max min value */
#if 1/* QC 2016/01/18 */
	if ((b < 2844) &&  (b > 1420)) {
		/* 3G ~1.5G */
		hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
			~(REG_DFE_LIMIT0_tap0_max_mask | REG_DFE_LIMIT0_tap1_min_mask |
			REG_DFE_LIMIT0_tap2_max_mask | REG_DFE_LIMIT0_tap2_min_mask),
			REG_DFE_LIMIT0_tap0_max(0x18) | REG_DFE_LIMIT0_tap1_min(0x10) |
			REG_DFE_LIMIT0_tap2_max(0x0a) | REG_DFE_LIMIT0_tap2_min(0x19),
			HDMI_RX_DEF);
	} else {
		hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
			~(REG_DFE_LIMIT0_tap0_max_mask | REG_DFE_LIMIT0_tap1_min_mask |
			REG_DFE_LIMIT0_tap2_max_mask | REG_DFE_LIMIT0_tap2_min_mask),
			REG_DFE_LIMIT0_tap0_max(0x18) | REG_DFE_LIMIT0_tap1_min(0x35) |
			REG_DFE_LIMIT0_tap2_max(0x0a) | REG_DFE_LIMIT0_tap2_min(0x19),
			HDMI_RX_DEF);
	}
#endif
	/* Vth_min=0, Vth_max=0x7, Vth_th=0, Tap0_th=0 */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT1,
		~(REG_DFE_LIMIT1_vth_min_mask | REG_DFE_LIMIT1_vth_max_mask |
		REG_DFE_LIMIT1_vth_threshold_mask | REG_DFE_LIMIT1_tap0_threshold_mask |
		REG_DFE_LIMIT1_tap0_adjust_mask | REG_DFE_LIMIT1_tap1_trans_mask),
		REG_DFE_LIMIT1_vth_min(0) | REG_DFE_LIMIT1_vth_max(0x7) |
		REG_DFE_LIMIT1_tap0_adjust(0x02) | REG_DFE_LIMIT1_tap1_trans_mask,
		HDMI_RX_DEF);
	/* ENABLE  VTH & TAP0 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth),
		REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth, HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth),
		REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth, HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth),
		REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth, HDMI_RX_DEF);

	usleep_range(50000, 51000);/* Delay before turn off TAP0 adjust(DFE_second_flow) */

#if 1/* QC 2016/01/18 */
	DFE_second_flow();

	PHY_FORE_KOFF();

	/* Enable TAP1 & LE */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP1|REG_dfe_adapt_en_lane0_LE|REG_dfe_adapt_en_lane0_TAP2),
		(REG_dfe_adapt_en_lane0_TAP1|REG_dfe_adapt_en_lane0_LE|REG_dfe_adapt_en_lane0_TAP2),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP1|REG_dfe_adapt_en_lane1_LE|REG_dfe_adapt_en_lane1_TAP2),
		(REG_dfe_adapt_en_lane1_TAP1|REG_dfe_adapt_en_lane1_LE|REG_dfe_adapt_en_lane1_TAP2),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP1|REG_dfe_adapt_en_lane2_LE|REG_dfe_adapt_en_lane2_TAP2),
		(REG_dfe_adapt_en_lane2_TAP1|REG_dfe_adapt_en_lane2_LE|REG_dfe_adapt_en_lane2_TAP2),
		HDMI_RX_DEF);
#endif

	bDFE_Close_Flag = 1;

	/* Close DEF */
	usleep_range(80000, 85000);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(1), HDMI_RX_MAC);
	usleep_range(70000, 75000);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(0), HDMI_RX_MAC);
	usleep_range(70000, 75000);
	HDMI_MAG2_SetDFE_Close();

}

void HDMI_MAG2_SetDFE_MS_speed(int b, int dfe_mode)
{
	HDMI_PRINTF("[PHY][%s] b(%d) dfe_mode(%d)\n", __func__, b, dfe_mode);

	hdmi_rx_reg_mask32(REG_DFE_MODE,
		~(REG_DFE_MODE_adapt_mode_mask | REG_DFE_MODE_edge_det_mode_mask |
		REG_DFE_MODE_transition_only_mask | REG_DFE_MODE_tap1_delay_mask |
		REG_DFE_MODE_tap24_delay_mask | REG_DFE_MODE_le_delay_mask |
		REG_DFE_MODE_servo_delay_mask | REG_DFE_MODE_gray_en_mask |
		REG_DFE_MODE_dfe_adapt_rstb_mask | REG_DFE_MODE_tap0_notrans_mask |
		REG_DFE_MODE_servo_notrans_mask),
		REG_DFE_MODE_adapt_mode(dfe_mode) | REG_DFE_MODE_edge_det_mode(0) |
		REG_DFE_MODE_transition_only_mask | REG_DFE_MODE_tap1_delay(1) |
		REG_DFE_MODE_tap24_delay(1) | REG_DFE_MODE_le_delay(1) |
		REG_DFE_MODE_gray_en_mask | REG_DFE_MODE_tap0_notrans_mask |
		REG_DFE_MODE_servo_notrans_mask | _BIT16,
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_DFE_EN_L0_clk_inv_lane0_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_DFE_EN_L1_clk_inv_lane1_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask|REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_DFE_EN_L2_clk_inv_lane2_mask | REG_DFE_EN_L2_timer_ctrl_en_lane2_mask |
		REG_DFE_EN_L2_reduce_adapt_gain_lane2_mask | REG_DFE_EN_L2_rl_det_en_lane2_mask |
		REG_DFE_EN_L2_rl_threshold_lane2_mask | REG_DFE_EN_L2_dfe_adapt_en_lane2_mask |
		REG_DFE_EN_L2_le_min_lane2_mask | REG_DFE_EN_L2_le_init_lane2_mask |
		REG_DFE_EN_L2_tap4_init_lane2_mask),
		(REG_DFE_EN_L2_timer_ctrl_en_lane2_mask | REG_DFE_EN_L2_reduce_adapt_gain_lane2(2)) |
		REG_DFE_EN_L2_rl_threshold_lane2(1) | REG_DFE_EN_L2_le_min_lane2(0x18) |
		REG_DFE_EN_L2_le_init_lane2(0x3),
		HDMI_RX_DEF);

	/* Set initial value	TAP0 TAP1 TAP2 TAP3 */
	/* Tap1 =0xc Tap0 =0xc servo =0xf */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2,
		~(REG_DFE_INIT0_L0_tap1_init_lane0_mask | REG_DFE_INIT0_L0_tap0_init_lane0_mask |
		REG_DFE_INIT0_L0_servo_init_lane0_mask | REG_DFE_INIT0_L0_vth_init_lane0_mask),
		REG_DFE_INIT0_L0_tap1_init_lane0(0x0) | REG_DFE_INIT0_L0_tap0_init_lane0(0xc) |
		REG_DFE_INIT0_L0_servo_init_lane0(0xf) | REG_DFE_INIT0_L0_vth_init_lane0(0x3),
		HDMI_RX_DEF);

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_init1_rev1_lane0_mask), (_BIT19|_BIT21|_BIT23), HDMI_RX_DEF);

	/* Load initial data */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), REG_DFE_INIT1_L0_load_in_init_lane0_mask, HDMI_RX_DEF);

	HDMI_PRINTF("[PHY][DFE open] DFE load initial value\n");

	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~(REG_DFE_INIT1_L0_load_in_init_lane0_mask), 0, HDMI_RX_DEF);

	/* Adapt reset release */
	hdmi_rx_reg_mask32(REG_DFE_MODE, ~(REG_DFE_MODE_dfe_adapt_rstb_mask), REG_DFE_MODE_dfe_adapt_rstb_mask, HDMI_RX_DEF);
	/* Set run length = 4 */
	hdmi_rx_reg_mask32(REG_DFE_GAIN, ~(REG_DFE_GAIN_trans_rlength_mask), REG_DFE_GAIN_trans_rlength(2), HDMI_RX_DEF);
	/* Set tap tap1 tap2 max min value */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT0,
		~(REG_DFE_LIMIT0_tap0_max_mask|REG_DFE_LIMIT0_tap1_min_mask|REG_DFE_LIMIT0_tap2_max_mask|REG_DFE_LIMIT0_tap2_min_mask),
		(REG_DFE_LIMIT0_tap0_max(0x18)|REG_DFE_LIMIT0_tap1_min(0x35)|REG_DFE_LIMIT0_tap2_max(0x0a)|REG_DFE_LIMIT0_tap2_min(0x19)),
		HDMI_RX_DEF);
	/* Vth_min=0,Vth_max=0x7,Vth_th=0,Tap0_th=0 */
	hdmi_rx_reg_mask32(REG_DFE_LIMIT1,
		~(REG_DFE_LIMIT1_vth_min_mask | REG_DFE_LIMIT1_vth_max_mask |
		REG_DFE_LIMIT1_vth_threshold_mask | REG_DFE_LIMIT1_tap0_threshold_mask |
		REG_DFE_LIMIT1_tap0_adjust_mask | REG_DFE_LIMIT1_tap1_trans_mask),
		REG_DFE_LIMIT1_vth_min(0) | REG_DFE_LIMIT1_vth_max(0x7) |
		REG_DFE_LIMIT1_tap0_adjust(0x02) | REG_DFE_LIMIT1_tap1_trans_mask,
		HDMI_RX_DEF);
	/* ENABLE  VTH & TAP0 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~(REG_dfe_adapt_en_lane0_TAP0|REG_dfe_adapt_en_lane0_Vth), (REG_dfe_adapt_en_lane0_TAP0|REG_dfe_adapt_en_lane0_Vth), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~(REG_dfe_adapt_en_lane1_TAP0|REG_dfe_adapt_en_lane1_Vth), (REG_dfe_adapt_en_lane1_TAP0|REG_dfe_adapt_en_lane1_Vth), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~(REG_dfe_adapt_en_lane2_TAP0|REG_dfe_adapt_en_lane2_Vth), (REG_dfe_adapt_en_lane2_TAP0|REG_dfe_adapt_en_lane2_Vth), HDMI_RX_DEF);
	HDMI_PRINTF("[PHY][DFE open] ENABLE  VTH & TAP0\n");
	/* ENABLE TAP1 & LE */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~(REG_dfe_adapt_en_lane0_TAP1|REG_dfe_adapt_en_lane0_LE), (REG_dfe_adapt_en_lane0_TAP1), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~(REG_dfe_adapt_en_lane1_TAP1|REG_dfe_adapt_en_lane1_LE), (REG_dfe_adapt_en_lane1_TAP1), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~(REG_dfe_adapt_en_lane2_TAP1|REG_dfe_adapt_en_lane2_LE), (REG_dfe_adapt_en_lane2_TAP1), HDMI_RX_DEF);
	HDMI_PRINTF("[PHY][DFE open] ENABLE TAP1\n");

	bDFE_Close_Flag = 1;

	/* Close DEF */
	usleep_range(80000, 85000);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(1), HDMI_RX_MAC);
	usleep_range(70000, 75000);
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(0), HDMI_RX_MAC);
	usleep_range(75000, 76000);
	HDMI_MAG2_SetDFE_Close();

}

void DFE_Manual_Set(void)
{
	u_int8_t lane;

	/* DFE register release */
	hdmi_rx_reg_mask32(RST, ~RST_dfe_rstn_n_mask, RST_dfe_rstn_n_mask, HDMI_RX_PHY);

	/* Disable dfe */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~(REG_DFE_EN_L0_clk_inv_lane0_mask|REG_DFE_EN_L0_dfe_adapt_en_lane0_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~(REG_DFE_EN_L1_clk_inv_lane1_mask|REG_DFE_EN_L1_dfe_adapt_en_lane1_mask), 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~(REG_DFE_EN_L2_clk_inv_lane2_mask|REG_DFE_EN_L2_dfe_adapt_en_lane2_mask), 0, HDMI_RX_DEF);

	/* Adaptive mode sel */
	hdmi_rx_reg_mask32(REG_DFE_MODE, ~REG_DFE_MODE_adapt_mode_mask, REG_DFE_MODE_adapt_mode(3), HDMI_RX_DEF);

	/* lane0 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0, ~REG_DFE_EN_L0_le_min_lane0_mask, REG_DFE_EN_L0_le_min_lane0(0xf), HDMI_RX_DEF);
	/* lane1 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L1, ~REG_DFE_EN_L1_le_min_lane1_mask, REG_DFE_EN_L1_le_min_lane1(0xf), HDMI_RX_DEF);
	/* lane2 LE coefficient min */
	hdmi_rx_reg_mask32(REG_DFE_EN_L2, ~REG_DFE_EN_L2_le_min_lane2_mask, REG_DFE_EN_L2_le_min_lane2(0xf), HDMI_RX_DEF);

	/* tap1 initial,  lane0/lane1/lane2 */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0, ~REG_DFE_INIT0_L0_tap1_init_lane0_mask, REG_DFE_INIT0_L0_tap1_init_lane0(5), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1, ~REG_DFE_INIT0_L1_tap1_init_lane1_mask, REG_DFE_INIT0_L1_tap1_init_lane1(5), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2, ~REG_DFE_INIT0_L2_tap1_init_lane2_mask, REG_DFE_INIT0_L2_tap1_init_lane2(5), HDMI_RX_DEF);

	/* tap0 initial, lane0/lane1/lane2 */
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L0, ~REG_DFE_INIT0_L0_tap0_init_lane0_mask, REG_DFE_INIT0_L0_tap0_init_lane0(0xc), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L1, ~REG_DFE_INIT0_L1_tap0_init_lane1_mask, REG_DFE_INIT0_L1_tap0_init_lane1(0xc), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT0_L2, ~REG_DFE_INIT0_L2_tap0_init_lane2_mask, REG_DFE_INIT0_L2_tap0_init_lane2(0xc), HDMI_RX_DEF);

	/* DEF initial load, lane0/lane1/lane2 */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~REG_DFE_INIT1_L0_load_in_init_lane0_mask, REG_DFE_INIT1_L0_load_in_init_lane0(3), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~REG_DFE_INIT1_L1_load_in_init_lane1_mask, REG_DFE_INIT1_L1_load_in_init_lane1(3), HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~REG_DFE_INIT1_L2_load_in_init_lane2_mask, REG_DFE_INIT1_L2_load_in_init_lane2(3), HDMI_RX_DEF);
	HDMI_DELAYMS(1);
	/* DEF initial load done */
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L0, ~REG_DFE_INIT1_L0_load_in_init_lane0_mask, 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L1, ~REG_DFE_INIT1_L1_load_in_init_lane1_mask, 0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_INIT1_L2, ~REG_DFE_INIT1_L2_load_in_init_lane2_mask, 0, HDMI_RX_DEF);

	/* Enable tap1~4 B/G/R */
	hdmi_rx_reg_mask32(P0_B3, ~P0_B_DFE_TAPEN4321, P0_B_DFE_TAPEN4321, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_G3, ~P0_G_DFE_TAPEN4321, P0_G_DFE_TAPEN4321, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P0_R3, ~P0_R_DFE_TAPEN4321, P0_R_DFE_TAPEN4321, HDMI_RX_PHY);

	for (lane = 0; lane < 3; lane++)
		Dump_DFE_Para(lane);

	hdmi_ioctl_struct.DEF_ready = 1;
}

void HDMI_MAG2_SetDFE_Close(void)
{
	u_int8_t lane;

#if 1/* QC 2016/01/18 */
	hdmi_rx_reg_mask32(REG_DFE_EN_L0,
		~(REG_dfe_adapt_en_lane0_TAP0 | REG_dfe_adapt_en_lane0_Vth |
		REG_dfe_adapt_en_lane0_TAP1 | REG_dfe_adapt_en_lane0_TAP2 |
		REG_dfe_adapt_en_lane0_LE),
		0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L1,
		~(REG_dfe_adapt_en_lane1_TAP0 | REG_dfe_adapt_en_lane1_Vth |
		REG_dfe_adapt_en_lane1_TAP1 | REG_dfe_adapt_en_lane1_TAP2 |
		REG_dfe_adapt_en_lane1_LE),
		0, HDMI_RX_DEF);
	hdmi_rx_reg_mask32(REG_DFE_EN_L2,
		~(REG_dfe_adapt_en_lane2_TAP0 | REG_dfe_adapt_en_lane2_Vth |
		REG_dfe_adapt_en_lane2_TAP1 | REG_dfe_adapt_en_lane2_TAP2 |
		REG_dfe_adapt_en_lane2_LE),
		0, HDMI_RX_DEF);
#endif

	/* limit value record */
	hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask,
		REG_DFE_READBACK_record_limit_en(0), HDMI_RX_DEF);


	/* Read result max and min value */
	for (lane = 0; lane < 3; lane++)
		Dump_DFE_Para(lane);

	bDFE_Close_Flag = 0;
	bDFE_Close_Cnt = 0;
	hdmi_ioctl_struct.DEF_ready = 1;
	HDMI_PRINTF("[PHY][DFE open] HDMI_MAG2_SetDFE_Close\n");
}


void SetupTMDSPhy(u_int32_t b, char force)
{
	u_int8_t mode, dfe_mode = 3;
	bool b_mode_found = 0;

	if ((HDMI_ABS(hdmi_ioctl_struct.b, b) < 20) && (force == 0))
		return;

	if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC)&MHL_HDMI_PHY_BYPASS)
		return;

	hdmi_ioctl_struct.b = b;
	hdmi_ioctl_struct.b_change = 1;
	hdmi_phy_idle_patch.idle_count = 0;
#if HDMI2p0
	b6G_detect_cnt = 0;
#endif

	hdmi_rx_reg_mask32(HDCP_CR, ~HDCP_CR_hdcp_en_mask, 0, HDMI_RX_MAC);

	CLOSE_RST_MAC();

	EQ_bias_band_setting(b);

	for (mode = 0; mode < 5; mode++) {
		if (hdmi_phy_param[mode].b_upper > b && hdmi_phy_param[mode].b_lower <= b) {
			HDMI_Set_Phy_Table(mode);
			b_mode_found = 1;
			break;
		}
	}

	if (!b_mode_found) {
		HDMI_PRINTF("Not Found in PhyMode (b=%d)\n", b);
		return;
	}

	hdmi_rx_reg_mask32(RST, ~(P1_ck_9_CMU_WDRST), P1_ck_9_CMU_WDRST, HDMI_RX_PHY);

	/* PFD_RSTB	release */
	hdmi_rx_reg_mask32(P0_CK3, ~(P0_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), (P0_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P1_CK3, ~(P1_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), (P1_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), HDMI_RX_PHY);
	hdmi_rx_reg_mask32(P2_CK3, ~(P2_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), (P2_ck_9_CMU_PFD_RSTB|P0_ck_9_CMU_WDRST), HDMI_RX_PHY);

	CMU_Reset(0);
	DEMUX_RESET(0);
	CDR_RESET(0);

	hdmi_rx_reg_write32(REGD15, 0xE4E84505, HDMI_RX_PHY);
	hdmi_rx_reg_mask32(REGD16, ~(_BIT31), _BIT31, HDMI_RX_PHY);

	PHY_DFE_Setting(mode);

	if (b > clock_bound_110m)
		HDMI_MAG2_SetDFE(b, dfe_mode);
	else if ((b > clock_bound_45m) && (b < clock_bound_110m))
		HDMI_MAG2_SetDFE_MS_speed(b, 2);
	else
		DFE_Manual_Set();

	/* Prevent influence HDCP2.2 */
	if (hdmi_ioctl_struct.hdcp_state < HDCPRX_STATE_2P2_DISCOVER)
		hdmi_rx_reg_mask32(HDCP_CR, ~HDCP_CR_hdcp_en_mask, HDCP_CR_hdcp_en_mask, HDMI_RX_MAC);

	OPEN_RST_MAC();

	HDMI_PRINTF("****************** ");
	HDMI_PRINTF("setup phy[0805] %d %d", hdmi_ioctl_struct.b, b);
	HDMI_PRINTF("******************\n");
}

bool HDMI_Bit_Err_One_Time_Detect(u_int8_t period, u_int16_t thd)
{
	u_int32_t tout = 60;

	/* Mode */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_mode_mask, 0, HDMI_RX_MAC);
	/* Period */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_period_mask, VIDEO_BIT_ERR_DET_period(period), HDMI_RX_MAC);
	/* thd */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_thd_mask, VIDEO_BIT_ERR_DET_thd(thd), HDMI_RX_MAC);

	/* disable */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_en_mask, 0, HDMI_RX_MAC);
	/* reset cnt */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_reset_mask, VIDEO_BIT_ERR_DET_reset_mask, HDMI_RX_MAC);
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_reset_mask, 0, HDMI_RX_MAC);
	HDMI_DELAYMS(1);

	/* For clear, wclr_out */
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_STATUS_B,
		~(VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask,
		HDMI_RX_MAC);
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_STATUS_G,
		~(VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask,
		HDMI_RX_MAC);
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_STATUS_R,
		~(VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask),
		VIDEO_BIT_ERR_STATUS_B_no_dis_reset_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_thd_b_mask |
		VIDEO_BIT_ERR_STATUS_B_bit_err_b_mask | VIDEO_BIT_ERR_STATUS_B_bit_err_cnt_of_b_mask,
		HDMI_RX_MAC);

	HDMI_DELAYMS(1);
	hdmi_rx_reg_mask32(VIDEO_BIT_ERR_DET, ~VIDEO_BIT_ERR_DET_en_mask, VIDEO_BIT_ERR_DET_en_mask, HDMI_RX_MAC);

	while (VIDEO_BIT_ERR_DET_get_en(hdmi_rx_reg_read32(VIDEO_BIT_ERR_DET, HDMI_RX_MAC)) && tout--)
		HDMI_DELAYMS(1);

	HDMI_PRINTF("[PHY][BER] B bit_err_cnt=%d, G bit_err_cnt=%d, R bit_err_cnt=%d\n",
		VIDEO_BIT_ERR_STATUS_B_get_bit_err_cnt_b(hdmi_rx_reg_read32(VIDEO_BIT_ERR_STATUS_B, HDMI_RX_MAC)),
		VIDEO_BIT_ERR_STATUS_B_get_bit_err_thd_b(hdmi_rx_reg_read32(VIDEO_BIT_ERR_STATUS_G, HDMI_RX_MAC)),
		VIDEO_BIT_ERR_STATUS_R_get_bit_err_cnt_r(hdmi_rx_reg_read32(VIDEO_BIT_ERR_STATUS_R, HDMI_RX_MAC)));
	return TRUE;
}


int HdmiMeasureVedioClock(void)
{
	u_int32_t b;

	if (hdmi_rx_reg_read32(HDMI_GPVS, HDMI_RX_MAC) & _BIT5) {
		/* RSV1 received */
		hdmi_ioctl_struct.avi_info_in = 1;
		hdmi_rx_reg_write32(HDMI_GPVS, _BIT5, HDMI_RX_MAC);
		hdmi_ioctl_struct.avi_info_miss_cnt = 0;
	} else {
		hdmi_ioctl_struct.avi_info_miss_cnt++;
		if (hdmi_ioctl_struct.avi_info_miss_cnt > 200) {
			/* HDMI_PRINTF("AVI info miss %x\n", hdmiport_in(HDMI_HDMI_ACRCR_RO_VADDR)); */
			hdmi_ioctl_struct.avi_info_in = 0;
			hdmi_ioctl_struct.avi_info_miss_cnt = 0;
		}
	}

	if (Hdmi_IsbReady() == TRUE) {
		if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC) & HDMI_Force_3G) {
			HDMI_PRINTF("HDMI 3G force mode\n");
			b =  2815;/* 3G mode */
		} else {
			b =  Hdmi_get_b_value();
#if HDMI2p0
			b = (bHDMI_6G_flag?4:1)*b;
#endif
		}

		hdmi_ioctl_struct.b_debouce_count = 0;
		if ((HDMI_ABS(b, hdmi_ioctl_struct.b_pre) < 20) && (b > 116)) {
			if (hdmi_ioctl_struct.b_count >= HDMI_B_TEST_COUNT_MAX) {
				if (!(hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC)&MHL_HDMI_SETPHY_BYPASS))
					SetupTMDSPhy(b, 0);

				hdmi_ioctl_struct.b_count = 0;
			} else {
				hdmi_ioctl_struct.b_count++;
			}
		} else {
			hdmi_clear_b_struct();
			hdmi_ioctl_struct.b_pre = b;
		}
		Hdmi_TriggerbMeasurement(GET_HDMI_CHANNEL());
	} else {
		/* HDMI is not ready */
		Hdmi_TriggerbMeasurement(GET_HDMI_CHANNEL());
		hdmi_ioctl_struct.b_debouce_count++;

		if (hdmi_ioctl_struct.b_debouce_count < 2)
			return 0;

		hdmi_clear_b_struct();
		hdmi_ioctl_struct.b_debouce_count = 0;
		return 0;
	}

	return -1;
}

#if HDMI_PHY_IDLE_PATCH_ENABLE
void HdmiPhyElectricalIdlePatch(void)
{
	if (hdmi_ioctl_struct.b != 0 && HDMI_ABS(hdmi_ioctl_struct.b, hdmi_ioctl_struct.b_pre) < 20) {
		if ((hdmi_phy_idle_patch.apstatus == HDMIRX_DETECT_FAIL) || (hdmi_phy_idle_patch.apstatus == HDMIRX_DETECT_AVMUTE)) {
			hdmi_phy_idle_patch.idle_count++;
			if (hdmi_phy_idle_patch.idle_count >= HDMI_PHY_IDLE_PATCH_COUNT) {
				HDMIRX_INFO("PHY idle count %d, reset PHY\n", hdmi_phy_idle_patch.idle_count);

				if (!(hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC)&MHL_HDMI_SETPHY_BYPASS))
					SetupTMDSPhy(hdmi_ioctl_struct.b, 1);
			}
		}
	}
}
#endif


int rtd_hdmiRx_cmd(u_int8_t cmd,  void *arg)
{
	switch ((HDMIRX_IOCTL_T) cmd) {
	case IOCTRL_HDMI_PHY_START:
		HDMIRX_DEBUG("[%s] IOCTRL_HDMI_PHY_START", __func__);
		hdmi_ioctl_struct.b = 0;
		hdmi_ioctl_struct.b_change = 0;
		hdmi_ioctl_struct.b_pre = 0;
		hdmi_ioctl_struct.b_count = 0;
		hdmi_ioctl_struct.LG_patch_timer = 0;
		hdmi_phy_idle_patch.idle_count = 0;
		hdmi_ioctl_struct.hotplug_delay_count = 0;

		/* port 0 auto mode */
		hdmi_rx_reg_mask32(REGD42, ~REGD42_reg_p0_ck_md_auto_mask, REGD42_reg_p0_ck_md_auto_mask, HDMI_RX_PHY);
		/* port 1 auto mode */
		hdmi_rx_reg_mask32(REGD44, ~REGD44_reg_p1_ck_md_auto_mask, REGD44_reg_p1_ck_md_auto_mask, HDMI_RX_PHY);
		/* port2 auto mode */
		hdmi_rx_reg_mask32(REGD46, ~REGD46_reg_p2_ck_md_auto_mask, REGD46_reg_p2_ck_md_auto_mask, HDMI_RX_PHY);
		/* PMM clk detect enable */
		hdmi_rx_reg_mask32(CLKDETCR, ~_BIT0, _BIT0, HDMI_RX_MAC);
		Hdmi_TriggerbMeasurement(HDMI_CHANNEL0);
		break;

	case IOCTRL_HDMI_PHY_STOP:
		HDMIRX_DEBUG("[%s] IOCTRL_HDMI_PHY_STOP", __func__);
		hdmi_ioctl_struct.b = 0;
		hdmi_ioctl_struct.b_change = 0;
		hdmi_ioctl_struct.b_pre = 0;
		hdmi_ioctl_struct.LG_patch_timer = 0;
		hdmi_phy_idle_patch.idle_count = 0;
		hdmi_ioctl_struct.hotplug_delay_count = 0;

		/* port 0 auto mode */
		hdmi_rx_reg_mask32(REGD42, ~REGD42_reg_p0_ck_md_auto_mask, 0, HDMI_RX_PHY);
		/* port 1 auto mode */
		hdmi_rx_reg_mask32(REGD44, ~REGD44_reg_p1_ck_md_auto_mask, 0, HDMI_RX_PHY);
		/* port2 auto mode */
		hdmi_rx_reg_mask32(REGD46, ~REGD46_reg_p2_ck_md_auto_mask, 0, HDMI_RX_PHY);
		/* PMM clk detect disable */
		hdmi_rx_reg_mask32(CLKDETCR, ~_BIT0, 0, HDMI_RX_MAC);
		break;

	case IOCTRL_HDMI_GET_STRUCT:
		/* HDMIRX_DEBUG("[%s] IOCTRL_HDMI_GET_STRUCT",  __func__); */
		memcpy(arg, &hdmi_ioctl_struct, sizeof(HDMIRX_IOCTL_STRUCT_T));
		hdmi_ioctl_struct.b_change = 0;
		break;

	case IOCTRL_HDMI_SET_TIMER:
		HDMIRX_DEBUG("[%s] IOCTRL_HDMI_SET_TIMER", __func__);
		memcpy(&(hdmi_ioctl_struct.timer), arg, sizeof(hdmi_ioctl_struct.timer));
		break;

	case IOCTRL_HDMI_GET_TIMER:
		HDMIRX_DEBUG("[%s] IOCTRL_HDMI_GET_TIMER", __func__);
		memcpy(arg, &(hdmi_ioctl_struct.timer), sizeof(hdmi_ioctl_struct.timer));
		break;

	case IOCTRL_HDMI_SET_APSTATUS:
		/* HDMIRX_DEBUG("[%s] IOCTRL_HDMI_SET_APSTATUS",  __func__); */
		hdmi_phy_idle_patch.apstatus  = (HDMIRX_APSTATUS_T) (unsigned long) arg;

		if (hdmi_phy_idle_patch.apstatus != HDMIRX_DETECT_FAIL)
			hdmi_phy_idle_patch.idle_count = 0;

		break;

	default:
		break;
	}

	return 0;
}

void rtd_hdmiPhy_ISR(void)
{
	unsigned int hdmi_psap_addr = hdmi_rx_reg_read32(HDMI_PSAP, HDMI_RX_MAC);

	if (hdmi_ioctl_struct.LG_patch_timer != 0)
		hdmi_ioctl_struct.LG_patch_timer--;

	if (hdmi_ioctl_struct.timer != 0)
		hdmi_ioctl_struct.timer--;

	HdmiMeasureVedioClock();

#if HDMI_PHY_IDLE_PATCH_ENABLE
	HdmiPhyElectricalIdlePatch();
#endif

	Hdmi_HdcpFSM();

	if (bDFE_Close_Flag == 1) {
		if (bDFE_Close_Cnt == 2)
			hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(1), HDMI_RX_MAC);
		else if (bDFE_Close_Cnt == 3)
			hdmi_rx_reg_mask32(REG_DFE_READBACK, ~REG_DFE_READBACK_record_limit_en_mask, REG_DFE_READBACK_record_limit_en(0), HDMI_RX_MAC);
		bDFE_Close_Cnt++;
		if (bDFE_Close_Cnt >= 3)
			HDMI_MAG2_SetDFE_Close();
	}

	/* Bit Error check */
	if (hdmi_rx_reg_read32(HDMI_AFCR, HDMI_RX_MAC)&MHL_HDMI_Bit_Error_check) {
#if HDMI2p0
		if (bHDMI_6G_flag == 1)
			drvif_Hdmi2p0_Error_Count();
		else
#endif
		HDMI_Bit_Err_One_Time_Detect(100, 20);
	}

	hdmi_rx_reg_write32(HDMI_PSAP, hdmi_psap_addr, HDMI_RX_MAC);
}


