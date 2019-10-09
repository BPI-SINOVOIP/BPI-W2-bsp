/*
 * hdmiEDID.c - RTK hdmi rx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/string.h>
#include <linux/types.h>

#include "v4l2_hdmi_dev.h"
#include "mipi_wrapper.h"
#include "hdmiEDID.h"
#include "hdmirx_reg.h"
#include "hdmiInternal.h"

/*=================== extern Variable/Function ===================*/
extern MIPI_TOP_INFO mipi_top;

extern void Hdmi_SetHPD(char high);

#ifdef CONFIG_RTK_HDMITX
extern int hdmitx_switch_get_state(void);
#endif
/*======================================================*/

static void hotplug_pulses_work_fun(struct work_struct *work);
static DECLARE_WORK(hotplug_pulses_work, hotplug_pulses_work_fun);

HDMIRX_DTS_EDID_TBL_T hdmirx_edid;
HDMIRX_DTS_EDID_TBL_T hdmirx_edid2p0;
static int rx_edid_version = 0;/* 0:HDMI 1.4 , 1:HDMI 2.0 */

static void hotplug_pulses_work_fun(struct work_struct *work)
{
	HDMIRX_INFO("Set hotplug pulse");

	Hdmi_SetHPD(0);
	msleep(1000);
	Hdmi_SetHPD(1);
}

void HdmiRx_hotplug_pulses(void)
{
	if (!mipi_top.hdmi_rx_init)
		return;

	schedule_work(&hotplug_pulses_work);
}

char EDIDIsValid(unsigned char *EDID)
{
	if (EDID == NULL)
		return false;

	if ((EDID[0] != 0x0) || (EDID[1] != 0xff) || (EDID[6] != 0xff) || (EDID[7] != 0x0))
		return false;

	return true;
}


unsigned char drvif_EDIDLoad(unsigned char *EDID, int len)
{
	int i;

	if (EDIDIsValid(EDID) == false)
		return false;

	/* Disable DDC func, write EDID data to sram */
	hdmi_rx_reg_mask32(DDC2_EDID_CR, ~DDC2_EDID_CR_edid_en_mask, DDC2_EDID_CR_edid_en(0), HDMI_RX_DDC);


	for (i = 0; i < len; i++)  {
		/* total 0 ~ 127 */
		hdmi_rx_reg_write32(DDC2_DDC_SIR, i, HDMI_RX_DDC);
		hdmi_rx_reg_write32(DDC2_DDC_SAP, EDID[i], HDMI_RX_DDC);
	}

	/* Set to No Debounce */
	hdmi_rx_reg_write32(DDC2_I2C_CR, 0x00, HDMI_RX_DDC);

	/* Enable DDC func */
	hdmi_rx_reg_mask32(DDC2_EDID_CR, ~DDC2_EDID_CR_edid_en_mask, DDC2_EDID_CR_edid_en(1), HDMI_RX_DDC);

	return true;
}

void drvif_EDID_DDC12_AUTO_Enable(char enable)
{
	hdmi_rx_reg_mask32(DDC2_EDID_CR, ~(DDC2_EDID_CR_ddc2_force_mask | DDC2_EDID_CR_ddc2b_force_mask),
				(DDC2_EDID_CR_ddc2_force(0) | DDC2_EDID_CR_ddc2b_force((enable)?0:1)), HDMI_RX_DDC);

}

unsigned char HdmiRx_change_edid_physical_addr(unsigned char byteMSB, unsigned char byteLSB)
{
	unsigned char ret = false;
	unsigned char block_tag = 0;
	unsigned char block_size;
	unsigned char offset;
	unsigned char offset_max;
	unsigned int i;
	unsigned int sum = 0;
	HDMIRX_DTS_EDID_TBL_T *EDID_table;

	if ((rx_edid_version == 1) && (hdmirx_edid2p0.valid == true))
		EDID_table = &hdmirx_edid2p0;
	else
		EDID_table = &hdmirx_edid;

	offset = 0x84;/* First data block */
	offset_max = 0x80+EDID_table->EDID[0x82];

	while (offset < offset_max) {
		block_tag = EDID_table->EDID[offset] >> 4;
		block_size = EDID_table->EDID[offset] & 0xF;

		if (block_tag == 6) {
			/* Physical Address offset */
			offset += 4;
			break;
		}

		/* Next block */
		offset = offset + block_size + 1;
	}

	/* Make sure found VSDB */
	if (block_tag != 6) {
		HDMIRX_ERROR(" Change EDID physical addr fail, couldn't find vendor specific data block\n");
		return false;
	}

	/* Repeater PA Increment */
	if ((byteMSB&0x0F) == 0x0) {
		byteMSB = byteMSB | 0x1;
	} else if ((byteLSB&0xF0) == 0x0) {
		byteLSB = byteLSB | 0x10;
	} else if ((byteLSB&0x0F) == 0) {
		byteLSB = byteLSB | 0x1;
	} else {
		byteMSB = 0xFF;
		byteLSB = 0xFF;
	}

	HDMIRX_INFO("Set Physical Addr = 0x%02x%02x", byteMSB, byteLSB);
	EDID_table->EDID[offset] = byteMSB;
	EDID_table->EDID[offset+1] = byteLSB;

	/* Calculate and set checksum */
	for (i = 0x80; i < 0xFF; i++)
		sum += EDID_table->EDID[i];
	EDID_table->EDID[0xFF] = (0x100-(sum&0xFF))&0xFF;

	/* Reload EDID table */
	ret = drvif_EDIDLoad(EDID_table->EDID, 256);

	return ret;
}

void HdmiRx_save_tx_physical_addr(unsigned char byteMSB, unsigned char byteLSB)
{
	hdmirx_edid.tx_phy_addr[0] = byteMSB;
	hdmirx_edid.tx_phy_addr[1] = byteLSB;

	hdmirx_edid2p0.tx_phy_addr[0] = byteMSB;
	hdmirx_edid2p0.tx_phy_addr[1] = byteLSB;

	if (mipi_top.hdmi_rx_init) {
		if ((byteMSB != 0xEE) || (byteLSB != 0xEE))
			HdmiRx_change_edid_physical_addr(byteMSB, byteLSB);

		schedule_work(&hotplug_pulses_work);
	}
}


void HdmiRx_Save_DTS_EDID_Table(HDMIRX_DTS_EDID_TBL_T *dts_edid)
{
	memcpy(hdmirx_edid.EDID, dts_edid->EDID, 256);
	hdmirx_edid.tx_phy_addr[0] = 0xEE;
	hdmirx_edid.tx_phy_addr[1] = 0xEE;
	hdmirx_edid.valid = true;
}

void HdmiRx_Save_DTS_EDID2p0_Table(HDMIRX_DTS_EDID_TBL_T *dts_edid)
{
	memcpy(hdmirx_edid2p0.EDID, dts_edid->EDID, 256);
	hdmirx_edid2p0.tx_phy_addr[0] = 0xEE;
	hdmirx_edid2p0.tx_phy_addr[1] = 0xEE;
	hdmirx_edid2p0.valid = true;
}

void HdmiRx_SetEDID_version(int version)
{
	int old_version;
	HDMIRX_DTS_EDID_TBL_T *EDID_table;

	old_version = rx_edid_version;

	if (version == 1) {
		if (hdmirx_edid2p0.valid == true) {
			rx_edid_version = 1;
			EDID_table = &hdmirx_edid2p0;
		} else {
			HDMIRX_ERROR("Set EDID version fail, 2.0 EDID table not exists");
			rx_edid_version = 0;
			EDID_table = &hdmirx_edid;
		}
	} else {
		rx_edid_version = 0;
		EDID_table = &hdmirx_edid;
	}

	if (old_version != rx_edid_version) {
		HDMIRX_INFO("Change EDID to %s version", rx_edid_version?"2.0":"1.4");

		if (mipi_top.hdmi_rx_init) {
			Hdmi_SetHPD(0);
			drvif_Hdmi2p0_Scdc_Reset();
		}

		if ((EDID_table->tx_phy_addr[0] != 0xEE) ||
			(EDID_table->tx_phy_addr[1] != 0xEE))
			HdmiRx_change_edid_physical_addr(EDID_table->tx_phy_addr[0], EDID_table->tx_phy_addr[1]);
		else
			drvif_EDIDLoad(EDID_table->EDID, 256);

		HDMI_DELAYMS(1000);
		if (mipi_top.hdmi_rx_init)
			Hdmi_SetHPD(1);
	}

}

void HdmiRx_ChangeCurrentEDID(unsigned char *edid)
{
	/* HDMIRX_INFO("HdmiRx_ChangeCurrentEDID"); */

	if (rx_edid_version) {
		memcpy(hdmirx_edid.EDID, edid, 256);
		hdmirx_edid.valid = true;
		HdmiRx_SetEDID_version(0);
	} else {
		memcpy(hdmirx_edid2p0.EDID, edid, 256);
		hdmirx_edid2p0.valid = true;
		HdmiRx_SetEDID_version(1);
	}
}

int HdmiRx_GetEDID_version(void)
{
	return rx_edid_version;
}

unsigned char HdmiRx_EnableEDID(void)
{
	int i;
	unsigned char ret = false;
	HDMIRX_DTS_EDID_TBL_T *EDID_table;

	if ((rx_edid_version == 1) && (hdmirx_edid2p0.valid == true))
		EDID_table = &hdmirx_edid2p0;
	else
		EDID_table = &hdmirx_edid;

	if (EDID_table->valid) {
/* HDMI 1.4 CTS 9-5, Physical Address Handling */
#ifdef CONFIG_RTK_HDMITX
		/* Wait HDMI TX */
		if (hdmitx_switch_get_state() == 1) {
			for (i = 0; i < 5; i++) {
				if ((EDID_table->tx_phy_addr[0] == 0xEE) &&
					(EDID_table->tx_phy_addr[1] == 0xEE))
					HDMI_DELAYMS(500);
				else
					break;
			}
		}

		if ((EDID_table->tx_phy_addr[0] != 0xEE) ||
			(EDID_table->tx_phy_addr[1] != 0xEE))
			ret = HdmiRx_change_edid_physical_addr(EDID_table->tx_phy_addr[0], EDID_table->tx_phy_addr[1]);
		else
#endif
		ret = drvif_EDIDLoad(EDID_table->EDID, 256);
		drvif_EDID_DDC12_AUTO_Enable(0);
	}

	if (!ret)
		HDMIRX_ERROR("Enable EDID fail, EDID table not exists or invalid");

	return ret;
}

