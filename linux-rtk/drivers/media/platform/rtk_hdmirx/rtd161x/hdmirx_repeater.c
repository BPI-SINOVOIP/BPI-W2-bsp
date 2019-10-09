/*
 * hdmirx_repeater.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "hdmirx_video_dev.h"

#include "v4l2_hdmi_dev.h"
#include "hdmirx_reg.h"
#include "mipi_wrapper.h"

#include "rx_drv/hdmiInternal.h"

#if HDMI_REPEATER_SUPPORT
void __iomem *pll_hdmi2_vaddr;
void __iomem *disp_pll_vaddr;

void __iomem *pll_ldo1_vaddr;
void __iomem *pll_ldo2_vaddr;
void __iomem *pll_ldo3_vaddr;
void __iomem *pll_ldo4_vaddr;
void __iomem *pll_ldo5_vaddr;

int hdmi_repeater_mode = 0;/* 0:regular mode, 1:repeater mode */

/*=================== extern Variable/Function ===================*/
extern MIPI_TOP_INFO mipi_top;

extern void Hdmi_SetHPD(char high);
/*======================================================*/

void Set_Hdmitx_source(unsigned char repeater)
{
	unsigned int reg_val;

	if (repeater) {
		/* Bit25:Bit24 */
		reg_val = readl(pll_ldo3_vaddr)&0xFCFFFFFF;

		/* Set TX clock input from RX */
		writel(reg_val|(1<<25), pll_ldo3_vaddr);

		/* Set TX data input from RX */
		writel((1<<26)|(1<<25), disp_pll_vaddr);

		/* Enable HDMI repeater 1.4 mode */
		hdmi_rx_reg_write32(HDMIRPT, 0x1, HDMI_RX_PHY);
	} else {
		/*Set TX clock input from TX */
		writel(readl(pll_ldo3_vaddr)&0xFCFFFFFF, pll_ldo3_vaddr);

		/* Set TX data input from TX */
		writel((1<<26), disp_pll_vaddr);

		/* Disable HDMI repeater mode */
		hdmi_rx_reg_write32(HDMIRPT, 0x0, HDMI_RX_PHY);
	}
}

void Set_Hdmitx_PLL(void)
{
	unsigned int tmds;

	if (!hdmi_repeater_mode)
		return;

	tmds = rxphy_get_clk()*27/256;
	if (HDMI_TMDS_CPS_get_pll_div2_en(hdmi_rx_reg_read32(HDMI_TMDS_CPS, HDMI_RX_MAC)))
		tmds = tmds*2;

	HDMIRX_INFO("Set TX PLL, TMDS(%u)", tmds);

	if (tmds > 155) {
		/* 297MHz */
		writel(0x00190034, pll_ldo1_vaddr);
		writel(0x03fc00ff, pll_ldo2_vaddr);
		writel(0x00bed800, pll_ldo3_vaddr);
		writel(0x0a00c6d3, pll_ldo4_vaddr);
		writel(0x00000526, pll_ldo5_vaddr);
		writel(0x00020210, pll_hdmi2_vaddr);
	} else if (tmds > 140) {
		/* 148.5MHz */
		writel(0x19001005, pll_ldo1_vaddr);
		writel(0x03fc00ff, pll_ldo2_vaddr);
		writel(0x00bed800, pll_ldo3_vaddr);
		writel(0x0a00c000, pll_ldo4_vaddr);
		writel(0x00000100, pll_ldo5_vaddr);
		writel(0x00040221, pll_hdmi2_vaddr);
	} else if (tmds > 70) {
		/* 74.25MHz */
		writel(0x0000000f, pll_ldo1_vaddr);
		writel(0x015400f0, pll_ldo2_vaddr);
		writel(0x00249000, pll_ldo3_vaddr);
		writel(0x0000c092, pll_ldo4_vaddr);
		writel(0x00000002, pll_ldo5_vaddr);
		writel(0x00060232, pll_hdmi2_vaddr);
	} else {
		/* 27MHz */
		writel(0x00000c0f, pll_ldo1_vaddr);
		writel(0x035400f0, pll_ldo2_vaddr);
		writel(0x003c7000, pll_ldo3_vaddr);
		writel(0x0000c092, pll_ldo4_vaddr);
		writel(0x00000307, pll_ldo5_vaddr);
		writel(0x00080243, pll_hdmi2_vaddr);
	}

	Set_Hdmitx_source(1);
}

int Get_Hdmi_repeater_mode(void)
{
	return hdmi_repeater_mode;
}

void Set_Hdmi_repeater_mode(int enable)
{

	if (hdmi_repeater_mode == enable)
		return;

	if (enable) {
		HDMIRX_INFO("Enable HDMI repeater mode");
		pll_hdmi2_vaddr = ioremap(0x98000194, 0x4);
		pll_ldo1_vaddr = ioremap(0x98000230, 0x4);
		pll_ldo2_vaddr = ioremap(0x98000234, 0x4);
		pll_ldo3_vaddr = ioremap(0x98000238, 0x4);
		pll_ldo4_vaddr = ioremap(0x9800023C, 0x4);
		pll_ldo5_vaddr = ioremap(0x98000240, 0x4);
		disp_pll_vaddr = ioremap(0x98000024, 0x4);

		if (mipi_top.hdmi_rx_init) {
			Hdmi_SetHPD(0);
			usleep_range(500000, 600000);
			Hdmi_SetHPD(1);
		}

	} else {
		HDMIRX_INFO("Disable HDMI repeater mode");
		Set_Hdmitx_source(0);

		iounmap(pll_hdmi2_vaddr);
		iounmap(pll_ldo1_vaddr);
		iounmap(pll_ldo2_vaddr);
		iounmap(pll_ldo3_vaddr);
		iounmap(pll_ldo4_vaddr);
		iounmap(pll_ldo5_vaddr);
		iounmap(disp_pll_vaddr);
	}

	hdmi_repeater_mode = enable;
}
#endif
