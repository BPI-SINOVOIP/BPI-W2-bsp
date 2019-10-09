/*
 * hdmirx_clk_ctrl.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/of.h>

#include <linux/reset.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <soc/realtek/power-control.h>

#include "hdmirx_clk_ctrl.h"

unsigned int init_flag;
struct reset_control *reset_mipi;
struct reset_control *reset_rxwrap;
struct reset_control *reset_hdmirx;
struct reset_control *reset_cbustx;
struct reset_control *reset_cbus_iso;
struct reset_control *reset_cbustx_iso;
struct reset_control *reset_cbusrx_iso;
struct clk *clk_mipi;
struct clk *clk_hdmirx;
struct clk *clk_cbustx;
struct clk *clk_cbus_osc_iso;
struct clk *clk_cbus_iso;
struct clk *clk_cbustx_iso;
struct clk *clk_cbusrx_iso;
struct power_control *pctrl_hdmirx;
struct power_control *pctrl_mipi;

unsigned char is_clock_enabled(HDMI_CLK_TYPE clk_type)
{
	unsigned char ret_value;

	ret_value = false;

	if (clk_type&CLK_MIPI)
		ret_value = __clk_is_enabled(clk_mipi);

	return ret_value;
}

void hdmirx_reset_control(HDMI_CLK_TYPE clk_type, HDMI_CLK_CTL enable)
{
	if (clk_type&RST_MIPI) {
		if (enable)
			reset_control_deassert(reset_mipi);
		else
			reset_control_assert(reset_mipi);
	}
}

void hdmirx_clock_control(HDMI_CLK_TYPE clk_type, HDMI_CLK_CTL enable)
{
	if (clk_type&CLK_HDMIRX) {

		if ((!reset_hdmirx) || (!clk_hdmirx))
			HDMIRX_ERROR("[%s] CLK_HDMIRX fail", __func__);

		if (enable) {
			reset_control_deassert(reset_hdmirx);

			if (init_flag & CLK_HDMIRX) {
				clk_enable(clk_hdmirx);
			} else {
				clk_prepare_enable(clk_hdmirx);
				init_flag |= CLK_HDMIRX;
			}

			power_control_power_on(pctrl_hdmirx);
		} else { /* if not enable */
			power_control_power_off(pctrl_hdmirx);
			clk_disable(clk_hdmirx);
			reset_control_assert(reset_hdmirx);
		}

	} /* end if if (clk_type&CLK_HDMIRX) */

	if (clk_type&CLK_RXWRAP) {

		if (!reset_rxwrap)
			HDMIRX_ERROR("[%s] CLK_RXWRAP fail", __func__);

		if (enable)
			reset_control_deassert(reset_rxwrap);
		else
			reset_control_assert(reset_rxwrap);
	}

	if (clk_type&CLK_MIPI) {

		if ((!reset_mipi) || (!clk_mipi))
			HDMIRX_ERROR("[%s] CLK_MIPI fail", __func__);

		if (enable) {
			reset_control_deassert(reset_mipi);

			if (init_flag&CLK_MIPI) {
				clk_enable(clk_mipi);
			} else {
				clk_prepare_enable(clk_mipi);
				init_flag |= CLK_MIPI;
			}

			power_control_power_on(pctrl_mipi);
		} else { /* if not enable */
			power_control_power_off(pctrl_mipi);
			clk_disable(clk_mipi);
			reset_control_assert(reset_mipi);
		}
	} /* end of if (clk_type&CLK_MIPI)*/

	if (clk_type&CLK_CBUS) {

		if ((!reset_cbustx) || (!reset_cbus_iso) || (!reset_cbustx_iso) ||
			(!reset_cbusrx_iso) || (!clk_cbustx) || (!clk_cbus_osc_iso) ||
			(!clk_cbus_iso) || (!clk_cbustx_iso) || (!clk_cbusrx_iso))
			HDMIRX_ERROR("[%s] CLK_CBUS fail", __func__);

		if (enable) {
			reset_control_deassert(reset_cbustx);
			reset_control_deassert(reset_cbus_iso);
			reset_control_deassert(reset_cbustx_iso);
			reset_control_deassert(reset_cbusrx_iso);

			if (init_flag&CLK_CBUS) {
				clk_enable(clk_cbus_osc_iso);
				clk_enable(clk_cbus_iso);
				clk_enable(clk_cbustx_iso);
				clk_enable(clk_cbusrx_iso);
			} else {
				clk_prepare_enable(clk_cbus_osc_iso);
				clk_prepare_enable(clk_cbus_iso);
				clk_prepare_enable(clk_cbustx_iso);
				clk_prepare_enable(clk_cbusrx_iso);
				init_flag |= CLK_CBUS;
			}
		} else { /* if not enable */
			clk_disable(clk_cbus_osc_iso);
			clk_disable(clk_cbus_iso);
			clk_disable(clk_cbustx_iso);
			clk_disable(clk_cbusrx_iso);

			reset_control_assert(reset_cbustx);
			reset_control_assert(reset_cbus_iso);
			reset_control_assert(reset_cbustx_iso);
			reset_control_assert(reset_cbusrx_iso);
		}
	} /* end of if (clk_type&CLK_CBUS)*/

}

void hdmirx_clock_init(struct platform_device *pdev)
{
	init_flag = 0;

	reset_mipi = reset_control_get(&pdev->dev, "mipi");
	reset_rxwrap = reset_control_get(&pdev->dev, "hdmirx_wrap");
	reset_hdmirx = reset_control_get(&pdev->dev, "hdmirx");
	reset_cbustx = reset_control_get(&pdev->dev, "cbus_tx");
	reset_cbus_iso = reset_control_get(&pdev->dev, "cbus");
	reset_cbustx_iso = reset_control_get(&pdev->dev, "cbustx");
	reset_cbusrx_iso = reset_control_get(&pdev->dev, "cbusrx");

	clk_mipi = clk_get(&pdev->dev, "mipi");
	clk_hdmirx = clk_get(&pdev->dev, "hdmirx");
	clk_cbustx = clk_get(&pdev->dev, "cbus_tx");
	clk_cbus_osc_iso = clk_get(&pdev->dev, "cbus_osc");
	clk_cbus_iso = clk_get(&pdev->dev, "cbus_sys");
	clk_cbustx_iso = clk_get(&pdev->dev, "cbustx_sys");
	clk_cbusrx_iso = clk_get(&pdev->dev, "cbusrx_sys");

	pctrl_hdmirx = power_control_get("pctrl_disp_hdmi_rx");/* HDMI RX SRAM */
	pctrl_mipi = power_control_get("pctrl_disp_mipi");/* MIPI SRAM */
}

