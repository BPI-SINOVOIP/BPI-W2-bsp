/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */


#include <linux/clk.h>   // clk_get
#include <linux/clk-provider.h>
#include <linux/reset.h> // reset_control_get
#include <linux/delay.h>
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include <soc/realtek/power-control.h>
#include <soc/realtek/rtk_cpu.h>
#include "rtl865x_asicBasic.h"
#include "rtl865x_asicCom.h"
#include "rtl865x_asicL2.h"
#include "asicRegs.h"
#include "crt_sys_reg.h"
#include "iso_reg.h"
#include "sb2_reg.h"
#include "sata_reg.h"

//#define RTL_DEBUG       1
#ifdef RTL_DEBUG
#define DBG(fmt, ...) printk(KERN_ERR "%s:%d: " fmt "\n", \
			__func__, __LINE__, ## __VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#define CLK_SYS_PHYSICAL_BASE	SYS_SOFT_RESET1
#define CLK_SYS_LEN		0x20000
extern void __iomem *rtl_hwnat_clk_mmio;
#define CLK_SYS_READ_MEM32(reg)		READ_MEM32((reg - CLK_SYS_PHYSICAL_BASE + (uintptr_t)rtl_hwnat_clk_mmio))
#define CLK_SYS_WRITE_MEM32(reg, val)	WRITE_MEM32((reg - CLK_SYS_PHYSICAL_BASE + (uintptr_t)rtl_hwnat_clk_mmio), val)

#define SATA_WRP_PHYSICAL_BASE	SATA_SATA_MAC_IN
#define SATA_WRP_LEN		0x100
extern void __iomem *rtl_hwnat_sata_mmio;
#define SATA_WRP_READ_MEM32(reg)	READ_MEM32((reg - SATA_WRP_PHYSICAL_BASE + (uintptr_t)rtl_hwnat_sata_mmio))
#define SATA_WRP_WRITE_MEM32(reg, val)	WRITE_MEM32((reg - SATA_WRP_PHYSICAL_BASE + (uintptr_t)rtl_hwnat_sata_mmio), val)

extern rtl8651_tblAsic_ethernet_t	rtl8651AsicEthernetTable[];
extern uint8 hwnat_mac0_enable; /* 0: interface used by SATA, 1: interface used by NAT */
extern uint8 hwnat_mac0_mode; /* 0:RGMII to PHY, 1:SGMII to PHY, 2: RGMII to MAC, 3: SGMII to MAC */
extern uint8 hwnat_mac5_conn_to; /* 0:PHY, 1:MAC */
extern uint8 hwnat_rgmii_voltage; /* 1:1.8V, 2:2.5V, 3:3.3V */
extern uint8 hwnat_rgmii_enable; /* 0:disable, 1:enable */

void rtd129x_hwnat_set_sata_pllddsa(struct device *dev)
{
	uint32 val;
	/* GET reset control */
	struct reset_control *rstc_sata_0 = reset_control_get(dev, "sata_0");
	struct reset_control *rstc_sata_phy_0 = reset_control_get(dev, "sata_phy_0");
	struct reset_control *rstc_sata_phy_pow_0 = reset_control_get(dev, "sata_phy_pow_0");
	struct reset_control *rstc_sata_func_exist_0 = reset_control_get(dev, "sata_func_exist_0");
	struct reset_control *rstc_sds_phy = reset_control_get(dev, "rstn_sds_phy");

	/* GET clock */
	struct clk *clk_en_sata_0 = clk_get(dev, "sata_0");
	struct clk *clk_en_sata_alive_0 = clk_get(dev, "sata_alive_0");
	struct clk *clk_en_sata_1 = clk_get(dev, "sata_1");
	struct clk *clk_en_sata_alive_1 = clk_get(dev, "sata_alive_1");

	/* release SATA0 reset */
	#if 1
	/* DEASSERT: set rstn bit to 1 */
	reset_control_deassert(rstc_sata_0);
	reset_control_deassert(rstc_sata_phy_0);
	reset_control_deassert(rstc_sata_phy_pow_0);
	reset_control_deassert(rstc_sata_func_exist_0);
	#else
	val = CLK_SYS_READ_MEM32(SYS_SOFT_RESET1);
	val |= (1 << SYS_SOFT_RESET1_rstn_sata_0_shift);
	val |= (1 << SYS_SOFT_RESET1_rstn_sata_phy_0_shift);
	val |= (1 << SYS_SOFT_RESET1_rstn_sata_phy_pow_0_shift);
	val |= (1 << SYS_SOFT_RESET1_sata_func_exist_0_shift);
	CLK_SYS_WRITE_MEM32(SYS_SOFT_RESET1, val);
	#endif
	mdelay(10);

	/* SATA0 clock enable */
	#if 1
	clk_prepare_enable(clk_en_sata_0);
	clk_prepare_enable(clk_en_sata_alive_0);
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE1);
	val |= (1 << SYS_CLOCK_ENABLE1_clk_en_sata_0_shift);
	val |= (1 << SYS_CLOCK_ENABLE1_clk_en_sata_alive_0_shift);
	CLK_SYS_WRITE_MEM32(SYS_CLOCK_ENABLE1, val);
	#endif
	mdelay(10);

	/* SATA1 clock enable */
	#if 1
	clk_prepare_enable(clk_en_sata_1);
	clk_prepare_enable(clk_en_sata_alive_1);
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE2);
	val |= (1 << SYS_CLOCK_ENABLE2_clk_en_sata_1_shift);
	val |= (1 << SYS_CLOCK_ENABLE2_clk_en_sata_alive_1_shift);
	CLK_SYS_WRITE_MEM32(SYS_CLOCK_ENABLE2, val);
	#endif
	mdelay(10);

	/* release SERDES reset */
	#if 1
	/* DEASSERT: set rstn bit to 1 */
	reset_control_deassert(rstc_sds_phy);
	#else
	val = CLK_SYS_READ_MEM32(SYS_SOFT_RESET2);
	val |= (1 << SYS_SOFT_RESET2_rstn_sds_phy_shift);
	CLK_SYS_WRITE_MEM32(SYS_SOFT_RESET2, val);
	#endif
	mdelay(10);

	/* PLL DDSA turn on */
	CLK_SYS_WRITE_MEM32(SYS_PLL_SSC_DIG_DDSA1, 0x6800);

	val = CLK_SYS_READ_MEM32(SYS_PLL_DDSA2);
	val |= (1 << SYS_PLL_DDSA2_REG_PLLDDSA_POW_shift);
	val |= (1 << SYS_PLL_DDSA2_REG_PLLDDSA_RSTB_shift);
	CLK_SYS_WRITE_MEM32(SYS_PLL_DDSA2, val);

	udelay(1000);

	val = CLK_SYS_READ_MEM32(SYS_PLL_DDSA2);
	val &= ~(1 << SYS_PLL_DDSA2_REG_PLLDDSA_OEB_shift);
	CLK_SYS_WRITE_MEM32(SYS_PLL_DDSA2, val);

	udelay(1000);

	val = CLK_SYS_READ_MEM32(SYS_PLL_SSC_DIG_DDSA0);
	val &= ~(1 << SYS_PLL_SSC_DIG_DDSA0_REG_GRAN_AUTO_RST_DDSA_shift);
	val |= (1 << SYS_PLL_SSC_DIG_DDSA0_RSTB_DDSA_shift);
	CLK_SYS_WRITE_MEM32(SYS_PLL_SSC_DIG_DDSA0, val);

	udelay(1000);

	val = CLK_SYS_READ_MEM32(SYS_PLL_SSC_DIG_DDSA0);
	val |= (1 << SYS_PLL_SSC_DIG_DDSA0_OC_EN_DDSA_shift);
	CLK_SYS_WRITE_MEM32(SYS_PLL_SSC_DIG_DDSA0, val);
	mdelay(50);

	reset_control_put(rstc_sata_0);
	reset_control_put(rstc_sata_phy_0);
	reset_control_put(rstc_sata_phy_pow_0);
	reset_control_put(rstc_sata_func_exist_0);
	reset_control_put(rstc_sds_phy);
}

void rtd129x_hwnat_set_pllddsb(struct device *dev)
{
	uint32 val;
	struct clk *clk_pllddsb = clk_get(dev, "pll_ddsb");

	/* check if it is alreay set */
	val = CLK_SYS_READ_MEM32(SYS_PLL_DDSB2);
	if (SYS_PLL_DDSB2_get_REG_PLLDDSB_OEB(val) == 0 /* enable */) {
		clk_prepare_enable(clk_pllddsb);
		return;
	}

	/* 432MHz */
	CLK_SYS_WRITE_MEM32(SYS_PLL_SSC_DIG_DDSB1, 0x6800);

	/* PLLDDSB power on */
	val = CLK_SYS_READ_MEM32(SYS_PLL_DDSB2);
	val |= 1 << SYS_PLL_DDSB2_REG_PLLDDSB_POW_shift; /* power on */
	val |= 1 << SYS_PLL_DDSB2_REG_PLLDDSB_RSTB_shift; /* test clock enable */
	CLK_SYS_WRITE_MEM32(SYS_PLL_DDSB2, val);

	udelay(1000);

	/* CLK_PLLDDSB output enable control */
	val = CLK_SYS_READ_MEM32(SYS_PLL_DDSB2);
	val &= ~(1 << SYS_PLL_DDSB2_REG_PLLDDSB_OEB_shift); /* enable */
	CLK_SYS_WRITE_MEM32(SYS_PLL_DDSB2, val);
	clk_prepare_enable(clk_pllddsb);
}

void rtd129x_hwnat_reset_nat(struct device *dev)
{
	/* GET clock */
	struct clk *clk_en_nat = clk_get(dev, "nat");

	/* GET reset control */
	struct reset_control *rstc_nat = reset_control_get(dev, "nat");

	/* GET power control */
	struct power_control *pctrl = power_control_get("pctrl_nat");

	clk_disable_unprepare(clk_en_nat);
	reset_control_assert(rstc_nat);

	power_control_power_off(pctrl);

	mdelay(10);

	power_control_power_on(pctrl);

	reset_control_deassert(rstc_nat);
	clk_prepare_enable(clk_en_nat);

	reset_control_put(rstc_nat);
}

void rtd129x_hwnat_set_etn_clk(struct device *dev)
{
	uint32 val;
	/* GET clock */
	struct clk *clk_en_nat = clk_get(dev, "nat");
	struct clk *clk_en_etn_sys = clk_get(dev, "etn_sys");
	struct clk *clk_en_etn_250m = clk_get(dev, "etn_250m");

	/* GET reset control */
	struct reset_control *rstc_gmac = reset_control_get(dev, "gmac");
	struct reset_control *rstc_gphy = reset_control_get(dev, "gphy");
	struct reset_control *rstc_nat = reset_control_get(dev, "nat");

	/* check if it is alreay set */
	#if 1
	if (__clk_is_enabled(clk_en_nat) == 1 /* enable */)
		return;
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE2);
	if (SYS_CLOCK_ENABLE2_get_clk_en_nat(val) == 1 /* enable */)
		return;
	#endif

	/* reset bit of gphy */
	#if 1
	/* DEASSERT: set rstn bit to 1 */
	reset_control_deassert(rstc_gmac);
	reset_control_deassert(rstc_gphy);
	#else
	val = CLK_SYS_READ_MEM32(ISO_SOFT_RESET);
	val |= 1 << ISO_SOFT_RESET_rstn_gmac_shift; /* reset gmac */
	val |= 1 << ISO_SOFT_RESET_rstn_gphy_shift; /* reset gphy */
	CLK_SYS_WRITE_MEM32(ISO_SOFT_RESET, val);
	#endif

	udelay(1000);

	/* Ethernet Boot up bypass gphy ready mode */
	val = CLK_SYS_READ_MEM32(ISO_ETN_TESTIO);
	val &= ~(1 << ISO_ETN_TESTIO_etn_bpsgphy_mode_shift); /* no-bypass */
	CLK_SYS_WRITE_MEM32(ISO_ETN_TESTIO, val);

	/* Ethernet Boot up disable dbus clock gating */
	val = CLK_SYS_READ_MEM32(ISO_ETN_DBUS_CTRL);
	val &= ~(1 << ISO_ETN_DBUS_CTRL_iso_etn_pwr_ctrl_en_shift); /* disable */
	CLK_SYS_WRITE_MEM32(ISO_ETN_DBUS_CTRL, val);

	/* clock enable bit for etn clock & etn 250MHz */
	#if 1
	clk_prepare_enable(clk_en_etn_sys);
	clk_prepare_enable(clk_en_etn_250m);
	#else
	val = CLK_SYS_READ_MEM32(ISO_CLOCK_ENABLE);
	val |= 1 << ISO_CLOCK_ENABLE_clk_en_etn_sys_shift;
	val |= 1 << ISO_CLOCK_ENABLE_clk_en_etn_250m_shift;
	CLK_SYS_WRITE_MEM32(ISO_CLOCK_ENABLE, val);
	#endif

	/* clock enable bit for etn clock & etn 250MHz */
	#if 1
	clk_disable_unprepare(clk_en_etn_sys);
	clk_disable_unprepare(clk_en_etn_250m);
	#else
	val = CLK_SYS_READ_MEM32(ISO_CLOCK_ENABLE);
	val &= ~(1 << ISO_CLOCK_ENABLE_clk_en_etn_sys_shift);
	val &= ~(1 << ISO_CLOCK_ENABLE_clk_en_etn_250m_shift);
	CLK_SYS_WRITE_MEM32(ISO_CLOCK_ENABLE, val);
	#endif

	/* reset bit of gmac */
	#if 1
	/* DEASSERT: set rstn bit to 1 */
	reset_control_deassert(rstc_gmac);
	#else
	val = CLK_SYS_READ_MEM32(ISO_SOFT_RESET);
	val |= 1 << ISO_SOFT_RESET_rstn_gmac_shift;
	CLK_SYS_WRITE_MEM32(ISO_SOFT_RESET, val);
	#endif

	udelay(1000);

	/* clock enable bit for NAT */
	#if 1
	clk_prepare_enable(clk_en_nat);
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE2);
	val |= 1 << SYS_CLOCK_ENABLE2_clk_en_nat_shift; /* enable */
	CLK_SYS_WRITE_MEM32(SYS_CLOCK_ENABLE2, val);
	#endif

	/* clock enable bit for NAT */
	#if 1
	clk_disable_unprepare(clk_en_nat);
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE2);
	val &= ~(1 << SYS_CLOCK_ENABLE2_clk_en_nat_shift); /* disable */
	CLK_SYS_WRITE_MEM32(SYS_CLOCK_ENABLE2, val);
	#endif

	/* reset bit of NAT */
	#if 1
	/* DEASSERT: set rstn bit to 1 */
	reset_control_deassert(rstc_nat);
	#else
	val = CLK_SYS_READ_MEM32(SYS_SOFT_RESET1);
	val |= (1 << SYS_SOFT_RESET1_rstn_nat_shift); /* reset */
	CLK_SYS_WRITE_MEM32(SYS_SOFT_RESET1, val);
	#endif

	/* clock enable bit for NAT */
	#if 1
	clk_prepare_enable(clk_en_nat);
	#else
	val = CLK_SYS_READ_MEM32(SYS_CLOCK_ENABLE2);
	val |= 1 << SYS_CLOCK_ENABLE2_clk_en_nat_shift; /* enable */
	CLK_SYS_WRITE_MEM32(SYS_CLOCK_ENABLE2, val);
	#endif

	reset_control_put(rstc_gmac);
	reset_control_put(rstc_gphy);
	reset_control_put(rstc_nat);
}

static void set_ext_phy(uint32_t phyid, uint32_t page, uint32_t reg, uint32_t val)
{
	/* change to the page */
	rtl8651_setAsicEthernetPHYReg(phyid, 31, page);

	/* write PHY reg */
	rtl8651_setAsicEthernetPHYReg(phyid, reg, val);

	/* change to page 0 */
	rtl8651_setAsicEthernetPHYReg(phyid, 31, 0);
}

static uint32_t get_ext_phy(uint32_t phyid, uint32_t page, uint32_t reg)
{
	uint32_t val;

	/* change to the page */
	rtl8651_setAsicEthernetPHYReg(phyid, 31, page);

	/* read PHY reg */
	rtl8651_getAsicEthernetPHYReg(phyid, reg, &val);

	/* change to page 0 */
	rtl8651_setAsicEthernetPHYReg(phyid, 31, 0);

	return val;
}

void rtd129x_hwnat_set_rgmii0_init(void)
{
	uint32_t val;

	if (hwnat_rgmii_enable > 0) {
	/* Mux to MDC/MDIO */
	CLK_SYS_WRITE_MEM32(SB2_MUXPAD_RG0, 0x05555555);
	}

	/* SB2 spec, 1.8V/2.5V/3.3V */
	switch (hwnat_rgmii_voltage){
	case 1: /* 1.8V */
		/* RGMII0 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG0, 0); /* fast */

		/* RGMII0 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG1, 0x44444444); /* 4mA */

		/* RGMII0 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG2, 0x24444444); /* 4mA */
		break;
	case 2: /* 2.5V */
		/* RGMII0 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG0, 0); /* fast */

		/* RGMII0 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG1, 0x44444444); /* 4mA */

		/* RGMII0 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG2, 0x64444444);
		break;
	case 3: /* 3.3V */
	default:
		/* RGMII0 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG0, 0x3f);

		/* RGMII0 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG1, 0);

		/* RGMII0 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG2, 0xa4000000);
	}

	/* switch gphy channel for internal control */
	val = CLK_SYS_READ_MEM32(ISO_POWERCUT_ETN);
	val &= ~(1 << ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en_shift); /* internal */
	CLK_SYS_WRITE_MEM32(ISO_POWERCUT_ETN, val);

	/* switch gphy channel for NAT */
	val = CLK_SYS_READ_MEM32(ISO_POWERCUT_ETN);
	val |= (1 << ISO_POWERCUT_ETN_etn_gphy_switch_nat_shift); /* NAT */
	CLK_SYS_WRITE_MEM32(ISO_POWERCUT_ETN, val);
}

void rtd129x_hwnat_set_rgmii1_init(void)
{
	uint32_t val;

	if (hwnat_rgmii_enable > 0) {
	/* Mux to MDC/MDIO */
	CLK_SYS_WRITE_MEM32(SB2_MUXPAD_RG1, 0x05555555);

	/* SB2 spec, mux MDC&MDIO pin for RGMII */
	val = CLK_SYS_READ_MEM32(SB2_MUXPAD_RG0) & ~(0xf << SB2_MUXPAD_RG0_rgmii0_mdio_shift);
	val |= 0x5 << SB2_MUXPAD_RG0_rgmii0_mdio_shift;
	CLK_SYS_WRITE_MEM32(SB2_MUXPAD_RG0, val);
	}

	/* SB2 spec, 1.8V/2.5V/3.3V */
	switch (hwnat_rgmii_voltage){
	case 1: /* 1.8V */
		/* RGMII1 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG3, 0); /* fast */

		/* RGMII1 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG4, 0x44444444); /* 4mA */

		/* RGMII1 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG5, 0x24004444);
		break;
	case 2: /* 2.5V */
		/* RGMII1 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG3, 0); /* fast */

		/* RGMII1 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG4, 0x44444444); /* 4mA */

		/* RGMII1 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG5, 0x64004444);
		break;
	case 3: /* 3.3V */
	default:
		/* RGMII1 pad slew-rate control */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG3, 0x3f);

		/* RGMII1 TXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG4, 0);

		/* RGMII1 RXD pad driven current selection */
		CLK_SYS_WRITE_MEM32(SB2_PFUNC_RG5, 0xa4000000);
	}

	/* switch gphy channel for internal control */
	val = CLK_SYS_READ_MEM32(ISO_POWERCUT_ETN);
	val &= ~(1 << ISO_POWERCUT_ETN_gphy_mdio_outside_ctrl_en_shift); /* internal */
	CLK_SYS_WRITE_MEM32(ISO_POWERCUT_ETN, val);

	/* switch gphy channel for NAT */
	val = CLK_SYS_READ_MEM32(ISO_POWERCUT_ETN);
	val |= (1 << ISO_POWERCUT_ETN_etn_gphy_switch_nat_shift); /* NAT */
	CLK_SYS_WRITE_MEM32(ISO_POWERCUT_ETN, val);
}

static uint32_t rtd129x_hwnat_set_serdes_sgmii_init(void)
{
	uint32 val;
	uint32 cnt;

	/* SB2, PHY select as SGMII */
	/* RX50 ohms turn on, MBias enable, Band Gap enable */
	val = CLK_SYS_READ_MEM32(SB2_SATA_PHY_CTRL);
	val |= (1 << SB2_SATA_PHY_CTRL_sata_bg_en_0_shift);
	val |= (1 << SB2_SATA_PHY_CTRL_sata_mbias_en_0_shift);
	val |= (1 << SB2_SATA_PHY_CTRL_sata_rx50_link_0_shift);
	CLK_SYS_WRITE_MEM32(SB2_SATA_PHY_CTRL, val);
	mdelay(50);
	DBG("SB2_SATA_PHY_CTRL 0x%08x = 0x%08x, val = 0x%08x", SB2_SATA_PHY_CTRL, CLK_SYS_READ_MEM32(SB2_SATA_PHY_CTRL), val);

	/* switch to SGMII */
	val = CLK_SYS_READ_MEM32(SB2_SATA_PHY_CTRL);
	val &= ~(1 << SB2_SATA_PHY_CTRL_sata_sgmii_sel_shift);
	CLK_SYS_WRITE_MEM32(SB2_SATA_PHY_CTRL, val);
	mdelay(200);
	DBG("SB2_SATA_PHY_CTRL 0x%08x = 0x%08x, val = 0x%08x", SB2_SATA_PHY_CTRL, CLK_SYS_READ_MEM32(SB2_SATA_PHY_CTRL), val);

	/* Beginning of SATA PHY register tuning */
	/* SATA DPHY control by NAT enable */
	val = READ_MEM32(NAT_WRP_SERDES);
	val |= (1 << NAT_WRP_SERDES_sata_phy_mdio_en_shift);
	WRITE_MEM32(NAT_WRP_SERDES, val);
	DBG("NAT_WRP_SERDES 0x%lx = 0x%08x, val = 0x%08x", NAT_WRP_SERDES, READ_MEM32(NAT_WRP_SERDES), val);

	/* SATA PHY reg13[8:7]=00, choose 1.25GHz */
	/* PHY ID 6 means SATA SGMII internal PHY */
	rtl8651_getAsicEthernetPHYReg(6, 13, &val);
	val &= ~(3 << 7);
	rtl8651_setAsicEthernetPHYReg(6, 13, val);
	mdelay(50);
	DBG("SATA PHY ID 6 reg 13 = 0x%08x", val);

	/* 5GHz tuning */
	rtl8651_setAsicEthernetPHYReg(6, 4, 0x52f5);
	mdelay(50);
	rtl8651_setAsicEthernetPHYReg(6, 5, 0xead7);
	mdelay(50);
	rtl8651_setAsicEthernetPHYReg(6, 6, 0x000c);
	mdelay(50);
	rtl8651_setAsicEthernetPHYReg(6, 10, 0xa653);
	mdelay(50);
	rtl8651_setAsicEthernetPHYReg(6, 1, 0xa860);
	mdelay(200);
	rtl8651_setAsicEthernetPHYReg(7, 0, 0xd433);
	mdelay(50);
	rtl8651_setAsicEthernetPHYReg(7, 1, 0x22aa);
	mdelay(50);

	/* Ending of SATA PHY register tuning */
	/* SATA DPHY control by SATA enable */
	val = READ_MEM32(NAT_WRP_SERDES);
	val &= ~(1 << NAT_WRP_SERDES_sata_phy_mdio_en_shift);
	WRITE_MEM32(NAT_WRP_SERDES, val);
	DBG("NAT_WRP_SERDES 0x%lx = 0x%08x, val = 0x%08x", NAT_WRP_SERDES, READ_MEM32(NAT_WRP_SERDES), val);

	/* SERDES IP clock enable */
	val = READ_MEM32(NAT_WRP_SERDES);
	val |= (1 << NAT_WRP_SERDES_serdes_clk_en_shift);
	WRITE_MEM32(NAT_WRP_SERDES, val);
	mdelay(50);
	DBG("NAT_WRP_SERDES 0x%lx = 0x%08x, val = 0x%08x", NAT_WRP_SERDES, READ_MEM32(NAT_WRP_SERDES), val);

	/* Sdsif IP clock enable */
	val = READ_MEM32(NAT_WRP_SERDES);
	val |= (1 << NAT_WRP_SERDES_sdsif_clk_en_shift);
	WRITE_MEM32(NAT_WRP_SERDES, val);
	mdelay(50);
	DBG("NAT_WRP_SERDES 0x%lx = 0x%08x, val = 0x%08x", NAT_WRP_SERDES, READ_MEM32(NAT_WRP_SERDES), val);

	/* wait for phy ready, clock fine-tuned */
#define PHY_RETRY_CNT	30
	for (cnt = 0; cnt < PHY_RETRY_CNT; cnt++) {
		mdelay(100);
		val = SATA_WRP_READ_MEM32(SATA_SATA_PHY_MON);
		if (SATA_SATA_PHY_MON_get_phy_calibrated_0(val) == 1 &&
			SATA_SATA_PHY_MON_get_phy_rdy_0(val) == 1)
			break;
	}
	if (cnt >= PHY_RETRY_CNT) {
		printk("Wait SATA_SATA_PHY_MON timeout, val = 0x%08x\n", val);
		return 1;
	} else
		DBG("cnt = %d", cnt);

	/* SERDES/NAT spec, SERDES auto mode */
	val = READ_MEM32(HWNAT_SERDES_SDS_REG02);
	val &= ~(3 << 8);
	WRITE_MEM32(HWNAT_SERDES_SDS_REG02, val);

	/* wait for SERDES link up */
#define SERDES_RETRY_CNT	30
	for (cnt = 0; cnt < SERDES_RETRY_CNT; cnt++) {
		mdelay(100);
		val = READ_MEM32(SERDES_WRP_SDS_MISC);
		if ((val & (1 << SERDES_WRP_SDS_MISC_sds_link_ok_sum_shift)) > 0 &&
			 (val & (1 << SERDES_WRP_SDS_MISC_sds_link_ok_shift)) > 0)
			break;
	}
	if (cnt >= SERDES_RETRY_CNT) {
		printk("Wait SerDes link timeout, val = 0x%08x\n", val);
		return 2;
	} else
		DBG("cnt = %d", cnt);

	return 0;
}

static void rtd129x_phy_8211f_init(int phyid, bool flow_ctrl_en)
{
	uint32_t val;
	uint32_t id1, id2;

	/* read PHY ID */
	rtl8651_getAsicEthernetPHYReg(phyid, 2, &id1);
	rtl8651_getAsicEthernetPHYReg(phyid, 3, &id2);
	DBG("PHY ID %d, ID1 0x%x, ID2 0x%x", phyid, id1, id2);
	if (id1 == 0x1c && id2 == 0xc916) { /* for RTL8211F & RTL8211FS only */
		/* disable RTL8211F CLK_OUT */
		val = get_ext_phy(phyid, 0xa43, 25) & ~(1 << 0);
		set_ext_phy(phyid, 0xa43, 25, val);

		/* enable RTL8211F RXC SSC */
		set_ext_phy(phyid, 0xc44, 19, 0x5f00);
		mdelay(50); /* minimum reset time 50mS */

		/* enable RTL8211F system clock SSC */
		set_ext_phy(phyid, 0xc44, 23, 0x4f00);
		val = get_ext_phy(phyid, 0xa43, 25) | (1 << 3);
		set_ext_phy(phyid, 0xa43, 25, val);

		/* use MDC/MDIO to issue SW reset of PHY 8211F */
		rtl8651_getAsicEthernetPHYReg(phyid, 0, &val);
		val |= PHY_RESET;
		rtl8651_setAsicEthernetPHYReg(phyid, 0, val);
		mdelay(20); /* minimum reset time 20mS */
	}

	/* read PHY reg 4 */
	rtl8651_getAsicEthernetPHYReg(phyid, 4, &val);

	if((flow_ctrl_en == true) && ((val & CAPABLE_PAUSE) == 0))
		val |= CAPABLE_PAUSE;
	else if((flow_ctrl_en == false) && ((val & CAPABLE_PAUSE) > 0))
		val &= ~CAPABLE_PAUSE;
	else
		return;

	/* write PHY reg 4 */
	rtl8651_setAsicEthernetPHYReg(phyid, 4, val);

	/* restart auto-negotiation */
	rtl8651_getAsicEthernetPHYReg(phyid, 0, &val);
	val |= RESTART_AUTONEGO;
	rtl8651_setAsicEthernetPHYReg(phyid, 0, val);
}

#define PORT0_TYPECFG_MASK		(3<<0)
static uint32_t rtd129x_switch_init(void)
{
	uint32_t val, ret = 0;

	/* Disable EEE by default */
	WRITE_MEM32(EEECR, 0);
	WRITE_MEM32(EEEABICR1, 0);

	/* clear unused fields */
	/* arrange embedded PHY ID for MAC1=PHY8, MAC2=PHY9, MAC3=PHYa */
	val = READ_MEM32(EPIDR) & ~(Port_embPhyID_MASK(1) | Port_embPhyID_MASK(2) | Port_embPhyID_MASK(3));
	val |= Port_embPhyID(8, 1) | Port_embPhyID(9, 2) | Port_embPhyID(0xa, 3);
	WRITE_MEM32(EPIDR, val);

	//MAC0
	if (hwnat_mac0_enable > 0) {
		if ((hwnat_mac0_mode & 1) == 0 /*RGMII*/) {
			/* PHYID assignment */
			/* RGMII1/MAC0 */
			/* arrange external PHY ID for port 0 */
			val = READ_MEM32(PCRP0) & ~ExtPHYID_MASK;
			val |= (rtl8651AsicEthernetTable[0].phyId  << ExtPHYID_OFFSET);
			WRITE_MEM32(PCRP0, val);

			/* interface assignment */
			/* NAT spec, embedded SGMII for RTD1295, external RGMII for RTD1296 */
			val = READ_MEM32(PITCR) & ~PORT0_TYPECFG_MASK;
			val |= Port0_TypeCfg_GMII_MII_RGMII;
			WRITE_MEM32(PITCR, val);

			/* RGMII timing tuning */
			/* tx_dly_mode = 1 */
			val = get_ext_phy(rtl8651AsicEthernetTable[0].phyId, 0xd08, 17);
			val |= (1 << 8);
			set_ext_phy(rtl8651AsicEthernetTable[0].phyId, 0xd08, 17, val);

			/* RGMII mode */
			val = READ_MEM32(P0GMIICR) & ~CFG_GMAC_MASK;
			val |= CFG_GMAC_RGMII;
			WRITE_MEM32(P0GMIICR, val);

			/* external PHY RTL8211F init */
			rtd129x_phy_8211f_init(rtl8651AsicEthernetTable[0].phyId, true);
		} else {	/*SGMII*/
			/* due to Kylin-Cut-A bug, MDC/MDIO interface not working, need to patch */
			if (get_rtd129x_cpu_revision() == RTD129x_CHIP_REVISION_A00) {
				/* PHYID assignment */
				/* SGMII/MAC0 */
				/* arrange external PHY ID for port 0 */
				val = READ_MEM32(PCRP0) & ~ExtPHYID_MASK;
				val |= (rtl8651AsicEthernetTable[0].phyId  << ExtPHYID_OFFSET);
				WRITE_MEM32(PCRP0, val);

				// NAT spec, external RGMII, for patch MDIO setting
				val = READ_MEM32(PITCR) & ~PORT0_TYPECFG_MASK;
				val |= Port0_TypeCfg_GMII_MII_RGMII;
				WRITE_MEM32(PITCR, val);

				/* external PHY RTL8211F init */
				rtd129x_phy_8211f_init(rtl8651AsicEthernetTable[0].phyId, true);

				/* external PHY RTL8211FS tuning, enlarge SGMII signal amplitude to be 800mV */
				set_ext_phy(rtl8651AsicEthernetTable[0].phyId, 0xdcd, 0x10, 0x1176);
				set_ext_phy(rtl8651AsicEthernetTable[0].phyId, 0xdcd, 0x11, 0xb490);

				/* NAT spec, embedded SGMII */
				val = READ_MEM32(PITCR) & ~PORT0_TYPECFG_MASK;
				val |= Port0_TypeCfg_UTP;
				WRITE_MEM32(PITCR, val);

				/* NAT spec, GMII MAC mode */
				val = READ_MEM32(P0GMIICR) & ~CFG_GMAC_MASK;
				val |= CFG_GMAC_GMII_MII_MAC | Conf_done;
				WRITE_MEM32(P0GMIICR, val);

				/* SerDes init */
				ret = rtd129x_hwnat_set_serdes_sgmii_init();
			} else {
				/* PHYID assignment */
				/* SGMII/MAC0 */
				/* arrange embedded PHY ID for port 0 */
				val = READ_MEM32(EPIDR) & ~Port_embPhyID_MASK(0);
				val |= Port_embPhyID(rtl8651AsicEthernetTable[0].phyId, 0);
				WRITE_MEM32(EPIDR, val);

				/* NAT spec, embedded SGMII */
				val = READ_MEM32(PITCR) & ~PORT0_TYPECFG_MASK;
				val |= Port0_TypeCfg_UTP;
				WRITE_MEM32(PITCR, val);

				/* NAT spec, GMII MAC mode */
				val = READ_MEM32(P0GMIICR) & ~CFG_GMAC_MASK;
				val |= CFG_GMAC_GMII_MII_MAC | Conf_done;
				WRITE_MEM32(P0GMIICR, val);

				/* NAT spec, cascade internal MDIO bus and external MDIO bus,
				   ECO in Kylin A01 to solve */
				val = READ_MEM32(NAT_WRP_DMY_B);
				val |= (1 << 2);
				WRITE_MEM32(NAT_WRP_DMY_B, val);

				/* NAT spec, update link patner ability to sds ability automatically */
				//WRITE_MEM32(0x981c9100, (READ_MEM32(0x981c9100) | (0x1 << 0)));
				val = READ_MEM32(NAT_WRP_DMY_A);
				val |= (1 << 0);
				WRITE_MEM32(NAT_WRP_DMY_A, val);

				/* SerDes init */
				ret = rtd129x_hwnat_set_serdes_sgmii_init();

				/* external PHY RTL8211F init */
				rtd129x_phy_8211f_init(rtl8651AsicEthernetTable[0].phyId, true);
			}
		}
	}


	/* GPHY/MAC4 */
	/* arrange embedded PHYID for port 4 */
	val = READ_MEM32(EPIDR) & ~Port_embPhyID_MASK(4);
	val |= Port_embPhyID(rtl8651AsicEthernetTable[4].phyId, 4);
	WRITE_MEM32(EPIDR, val);

#define PORT4_TYPECFG_MASK		(3<<8)
	/* NAT spec, choose embedded GMII GPHY */
	val = READ_MEM32(PITCR) & ~PORT4_TYPECFG_MASK;
	val |= Port4_TypeCfg_UTP; /* UTP interface */
	WRITE_MEM32(PITCR, val);

	/* external PHY RTL8211F init */
	rtd129x_phy_8211f_init(rtl8651AsicEthernetTable[4].phyId, true);


	/* RGMII0/MAC5 */
	/* arrange external RTL8211FS PHYID=PHY1 */
	val = READ_MEM32(PCRP5) & ~ExtPHYID_MASK;
	val |= (rtl8651AsicEthernetTable[5].phyId  << ExtPHYID_OFFSET); /* PHY ID 1 */
	WRITE_MEM32(PCRP5, val);

#define PORT5_TYPECFG_MASK		(3<<10)
	/* NAT spec, choose external RGMII */
	val = READ_MEM32(PITCR) & ~PORT5_TYPECFG_MASK;
	val |= Port5_TypeCfg_GMII_MII_RGMII; /* GMII/MII interface */
	WRITE_MEM32(PITCR, val);

	/* RGMII mode for RTL8211F */
	val = READ_MEM32(P5GMIICR) & ~CFG_GMAC_MASK;
	val |= CFG_GMAC_RGMII;
	WRITE_MEM32(P5GMIICR, val);

	/* RGMII timing tuning */
	/* We use PHY TX delay to instead of it */

	/* external PHY RTL8211F init */
	rtd129x_phy_8211f_init(rtl8651AsicEthernetTable[5].phyId, true);

	/* external PHY RGMII timing tuning */
	/* tx_dly_mode = 1 */
	val = get_ext_phy(rtl8651AsicEthernetTable[5].phyId, 0xd08, 17);
	val |= (1 << 8);
	set_ext_phy(rtl8651AsicEthernetTable[5].phyId, 0xd08, 17, val);

	return ret;
}

static uint32_t rtd129x_system_init(struct device *dev)
{
	uint32_t val;
	uint32_t i;

	/* PLLDDSB power on */
	val = get_rtd129x_cpu_id();
	if ((val != RTK1295_CPU_ID) && (val != RTK1296_CPU_ID))
		return val;

	rtd129x_hwnat_set_pllddsb(dev);
	rtd129x_hwnat_set_etn_clk(dev);

	//MAC0
	if (hwnat_mac0_enable > 0) {
		if ((hwnat_mac0_mode & 1) == 0 /*RGMII*/) {
			rtd129x_hwnat_set_rgmii1_init();
		} else {	/*SGMII*/
			/* workaround: set each MAC to force mode */
			for(i = 0; i < 5; i++) {
				val = READ_MEM32(PCRP0+i*4) | EnForceMode;
				WRITE_MEM32(PCRP0+i*4, val);
			}

			rtd129x_hwnat_set_sata_pllddsa(dev);
		}
	}

	//MAC5
	rtd129x_hwnat_set_rgmii0_init();

	return 0;
}

#if 0
static void rtd129x_nic_setting(void)
{
	// setting system_based_flow_control_registers
	WRITE_MEM32(SBFCR0, 0x000001e4);
	WRITE_MEM32(SBFCR1, 0x01600184);
	WRITE_MEM32(SBFCR2, 0x00a200e8);

	WRITE_MEM32(FCCR0, 0x3f3f3f3f);
	WRITE_MEM32(FCCR1, 0x003f3f3f);
	WRITE_MEM32(PQPLGR, 0x00545454);

	WRITE_MEM32(QRR, 0x0);

	WRITE_MEM32(PBFCR0, 0x00049249);

	WRITE_MEM32(PBFCR0, 0x00610092);
	WRITE_MEM32(PBFCR1, 0x00610092);
	WRITE_MEM32(PBFCR2, 0x00610092);
	WRITE_MEM32(PBFCR3, 0x00610092);
	WRITE_MEM32(PBFCR4, 0x00610092);
	WRITE_MEM32(PBFCR5, 0x00610092);
	WRITE_MEM32(PBFCR6, 0x00610092);

	WRITE_MEM32(QDBFCRP0G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP0G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP0G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP1G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP1G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP1G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP2G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP2G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP2G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP3G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP3G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP3G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP4G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP4G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP4G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP5G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP5G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP5G2, 0x001a0025);
	WRITE_MEM32(QDBFCRP6G0, 0x001a0025);
	WRITE_MEM32(QDBFCRP6G1, 0x001a0025);
	WRITE_MEM32(QDBFCRP6G2, 0x001a0025);

	WRITE_MEM32(QPKTFCRP0G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP0G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP0G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP1G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP1G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP1G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP2G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP2G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP2G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP3G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP3G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP3G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP4G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP4G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP4G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP5G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP5G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP5G2, 0x000f001b);
	WRITE_MEM32(QPKTFCRP6G0, 0x000f001b);
	WRITE_MEM32(QPKTFCRP6G1, 0x000f001b);
	WRITE_MEM32(QPKTFCRP6G2, 0x000f001b);

	WRITE_MEM32(IQFCTCR, 0x009600c8);
}
#endif

void rtd129x_hwnat_clk_init(struct device *dev)
{
	uint32_t ret = 0;
	struct power_control *pctrl = power_control_get("pctrl_nat");

	power_control_power_on(pctrl);

	if ((ret = rtd129x_system_init(dev)) != 0) {
		printk("Unknown RTD129X chip, ID = 0x%08x\n", ret);
		return;
	}
	else
		DBG("rtd129x_system_init() ok!");

	if ((ret = rtd129x_switch_init()) != 0) {
		switch(ret) {
		case 1:
			printk("Error: SGMII PHY not ready.\n");
			break;
		case 2:
			printk("Error: SGMII link fail.\n");
			break;
		default:
			printk("Error: rtd129x_switch_init() failed with unknown reason.\n");
		}
		return;
	}
	else
		DBG("rtd129x_switch_init() ok!");

#if 0
	rtd129x_nic_setting();
	DBG("rtd129x_nic_setting() ok!");
#endif
}

