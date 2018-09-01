/**
 * rtk-rts5400.c - Realtek RTS5400 Type C driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>

#include <linux/delay.h>

#include <linux/io.h>
#include <linux/suspend.h>

#define RTS5400_MAX_WRITE_DATA_LEN 32

static struct tcpm_command {
	u8 cmd;
	u8 wr_data_len;
	u8 data[RTS5400_MAX_WRITE_DATA_LEN];
} __packed;

#define PING_STATUS_CMD_STATUS(n) (n & 0x3)
#define PING_STATUS_DATA_LEN(n) ((n & 0xFC) >> 2)

static struct tcpm_command_status {
	u8 cmd_status:2;
#define PING_STATUS_IN_PORCESS 	0x0
#define PING_STATUS_COMPLETE 	0x1
#define PING_STATUS_DEFERRED 	0x2
#define PING_STATUS_ERROR 		0x3
	u8 data_len:6;
} __packed;

static struct pd_ic_status {
	u8 reservrd1;
	u8 reservrd2;
	u8 reservrd3;
	u8 main_ver;
	u8 sub_ver;
	u8 sub_ver2;
	u8 reservrd4;
	u8 reservrd5;
	u8 pd_tc;
#define IC_STATUS_PD_READY(n) (n & 0x1)
#define IC_STATUS_TC_CONNECT(n) ((n >> 3) & 0x1)
	uint32_t reservrd6;
	u8 sm_ready;
#define IC_STATUS_SMB_READY(n) (n & 0x1)
	u8 reservrd7;
	u8 reservrd8;
	uint32_t reservrd9;
} __packed;

static struct pd_status_change {//TODO
	uint32_t reservrd;
} __packed;

static struct pd_status_info {
	struct pd_status_change status_change; /* bit 0-31 */
	u8 supply:1;
#define PD_STATUS_INFO_NO_SUPPULY 	0x0
#define PD_STATUS_INFO_SUPPULY 		0x1
	u8 port_op_mode:3;
#define PD_STATUS_INFO_NO_CONSUMER 	0x0
#define PD_STATUS_INFO_USB_DEFAULT 	0x1
#define PD_STATUS_INFO_BC 			0x2
#define PD_STATUS_INFO_PD 			0x3
#define PD_STATUS_INFO_USB_1_5A 	0x4
#define PD_STATUS_INFO_USB_3_0A 	0x5
	u8 insertion_detect:1;
#define PD_STATUS_INFO_NO_CABLE 	0x0
#define PD_STATUS_INFO_CABLE_DETECT 0x1
	u8 pd_capable_cable:1;
#define PD_STATUS_INFO_NO_PD_CABLE 	0x0
#define PD_STATUS_INFO_PD_CABLE 	0x1
	u8 power_direction:1;
#define PD_STATUS_INFO_CONSUMER 	0x0
#define PD_STATUS_INFO_PROVIDER 	0x1
	u8 connect_status:1;
#define PD_STATUS_INFO_UNATTACHED 	0x0
#define PD_STATUS_INFO_ATTACHED 	0x1
	u8 port_partner_flag; /* bit 40-47 */
#define PD_STATUS_INFO_PARTNER_USB 	0x0
#define PD_STATUS_INFO_PARTNER_ALT 	0x1
	uint32_t request_data_obj; /* bit 48-79 */
	u8 port_partner_type:3; /* bit 80-82 */
#define PD_STATUS_INFO_PARTNER_DFP 	0x1
#define PD_STATUS_INFO_PARTNER_UFP 	0x2
#define PD_STATUS_INFO_PARTNER_PC 	0x3
#define PD_STATUS_INFO_PARTNER_PC_UFP 0x4
#define PD_STATUS_INFO_PARTNER_DA 	0x5
#define PD_STATUS_INFO_PARTNER_AAA 	0x6
	u8 battery_charging_status:2;
	u8 pd_sourcing_Vconn:1;
	u8 pd_responsible_for_Vconn:1;
	u8 pd_ams:1;
	u8 last_ams:4; /* bit 88-91 */
	u8 port_partner_not_support_pd:1;
	u8 plug_direction:1;
	u8 dp_role:1;
#define PD_STATUS_INFO_DP_SINK 		0x0
#define PD_STATUS_INFO_DP_SOURCE 	0x1
	u8 pd_connect:1;
#define PD_STATUS_INFO_PD_NOT_EXCHANGE 0x0
#define PD_STATUS_INFO_PD_EXCHANGE 	0x1
	u8 reservrd1;
	u8 alt_mode_status:3;
	u8 reservrd2:5;
} __packed;

#define PDO_TYPE(n) (n&0x1)
#define PDO_TYPE_SINK 0x0
#define PDO_TYPE_SOURCE 0x1
#define PDO_TCPM(n) ((n&0x1) << 1)
#define PDO_TCPM_TCPM 0x0
#define PDO_TCPM_PARTNER 0x1
#define PDO_OFFEST(n) ((n&0x7) << 2)
#define PDO_NUM(n) ((n&0x7) << 5)

static struct source_fix_pdo {
	u16 max_current:10;
	u16 valtage:10;
	u8 peak_current:2;
	u8 reservrd:3;
	u8 data_role_swap:1;
	u8 usb_comm_capable:1;
	u8 external_power:1;
	u8 usb_suspend:1;
	u8 dual_role_power:1;
	u8 power_type:2;
} __packed;

static struct source_var_pdo {
	u16 max_current:10;
	u16 min_valtage:10;
	u16 max_valtage:10;
	u8 power_type:2;
} __packed;

static struct source_bat_pdo {
	u16 max_current:10;
	u16 min_valtage:10;
	u16 max_valtage:10;
	u8 power_type:2;
} __packed;

static struct sink_fix_pdo {
	u16 op_current:10;
	u16 valtage:10;
	u8 peak_current:2;
	u8 reservrd:3;
	u8 data_role_swap:1;
	u8 usb_comm_capable:1;
	u8 external_power:1;
	u8 higher_capability:1;
	u8 dual_role_power:1;
	u8 power_type:2;
} __packed;

static struct sink_var_pdo {
	u16 op_current:10;
	u16 min_valtage:10;
	u16 max_valtage:10;
	u8 power_type:2;
} __packed;

static struct sink_bat_pdo {
	u16 op_current:10;
	u16 min_valtage:10;
	u16 max_valtage:10;
	u8 power_type:2;
} __packed;

static struct common_pdo {
	uint32_t reservrd:30;
	u8 power_type:2;
#define PDO_INFO_POWER_TYPE_FIX 0x0
#define PDO_INFO_POWER_TYPE_BAT 0x1
#define PDO_INFO_POWER_TYPE_VAR 0x2
} __packed;

union pdo_info {
	struct source_fix_pdo so_f;
	struct source_var_pdo so_v;
	struct source_bat_pdo so_b;
	struct sink_fix_pdo si_f;
	struct sink_var_pdo si_v;
	struct sink_bat_pdo si_b;
	struct common_pdo com;
};

static struct rdo_info {
	uint32_t reservrd_todo:28; //TODO
	uint32_t obj_pos:3;
	uint32_t reservrd:1;
} __packed;

#define PD_AMS_PR_SWAP 		0x01
#define PD_AMS_DR_SWAP 		0x02
#define PD_AMS_VCONN_SWAP 	0x03
#define PD_AMS_SOURCE_CAP 	0x04
#define PD_AMS_REQUEST 		0x05
#define PD_AMS_SOFT_RESET 	0x06
#define PD_AMS_HARD_RESET 	0x07
#define PD_AMS_GOTO_MIN 	0x08
#define PD_AMS_GET_SNK_CAP 	0x09
#define PD_AMS_GET_SRC_CAP 	0x0A

static struct rts5400_dev {
	struct i2c_client *client;
	struct device *dev;
	bool no_device;

	struct pd_ic_status ic_status;
	struct pd_status_info status_info;

	unsigned int pow_gpio;
} g_rts5400;

/* I2C transfer */
static struct tcpm_command_status __rts5400_get_ping_status(
		const struct i2c_client *client)
{
	int ret;
	struct tcpm_command_status status;
	status.cmd_status = 0;
	status.data_len = 0;

	ret = i2c_smbus_read_byte(client);
	if (ret < 0) {
		dev_err(&client->dev, "%s get error %d\n", __func__, ret);
		return status;
	}
	status.cmd_status = PING_STATUS_CMD_STATUS(ret);
	status.data_len = PING_STATUS_DATA_LEN(ret);
	return status;
}

static int __rts5400_block_read(const struct i2c_client *client,
		struct tcpm_command *command)
{
	int ret;
	int data_len = command->wr_data_len + 1;
	u8 *buffer;

	buffer = kzalloc(data_len, GFP_KERNEL);

	ret = i2c_smbus_read_i2c_block_data(client, command->cmd,
			data_len, buffer);

	if (ret < 0)
		dev_err(&client->dev, "block read failed\n");
	else {
		memcpy(&command->data, buffer + 1, command->wr_data_len);
		ret = buffer[0];
	}

	kfree(buffer);

	return ret;
}

static int __rts5400_block_write(struct i2c_client *client,
		struct tcpm_command *command)
{
	int ret;

	ret = i2c_smbus_write_block_data(client, command->cmd,
			command->wr_data_len, &command->data);
	return ret;
}

static int __rts5400_transfer(const struct rts5400_dev *rts5400,
		struct tcpm_command *w_cmd, struct tcpm_command *r_cmd)
{
	struct device *dev = rts5400->dev;
	struct i2c_client *client = rts5400->client;
	struct tcpm_command_status status;
	int retry = 100;
	int ret = -ENODEV;

	if (rts5400->no_device) {
		dev_dbg("%s Error! NO rts5400\n", __func__);
		return ret;
	}
	dev_dbg(dev, "%s start write command 0x%x,wr_data_len %d, sub_command 0x%x\n",
			__func__, w_cmd->cmd, w_cmd->wr_data_len, w_cmd->data[0]);

	ret = __rts5400_block_write(client, w_cmd);

	if (ret < 0) {
		dev_err(dev, "%s block write error %d", __func__, ret);
		return ret;
	}

	while (--retry) {
		mdelay(1);
		status = __rts5400_get_ping_status(client);
		if (status.cmd_status == PING_STATUS_COMPLETE) {
			break;
		} else if (status.cmd_status == PING_STATUS_ERROR) {
			dev_err(dev, "%s get ping status error %d\n", __func__, status.cmd_status);
			break;
		}
	}
	if (!retry) {
		dev_err(dev, "%s get ping status TIMEOUT\n", __func__);
		return -ETIMEDOUT;
	} else
		dev_dbg(dev, "%s get ping status 0x%x, data_len %d\n",
				__func__, status.cmd_status, status.data_len);

	if (r_cmd->wr_data_len == 0xff)
		r_cmd->wr_data_len = status.data_len;

	if (r_cmd->wr_data_len > 0) {
		dev_dbg(dev, "%s start read command 0x%x,wr_data_len %d\n",
			__func__, r_cmd->cmd, r_cmd->wr_data_len);

		ret = __rts5400_block_read(client, r_cmd);
		if (ret < 0)
			dev_err(dev, "%s block read error %d\n", __func__, ret);
	}
	if (status.cmd_status == PING_STATUS_ERROR)
		return -3;
	else
		return ret;
}

int rtk_rts5400_get_IC_status(void)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	int ret, i;
	struct tcpm_command w_cmd, r_cmd;
	struct pd_ic_status *ic_status = &rts5400->ic_status;

	w_cmd.cmd = 0x3A;
	w_cmd.wr_data_len = 0x1;
	w_cmd.data[0] = 0x14;
	r_cmd.cmd = 0x80;
	r_cmd.wr_data_len = 0x14;
	memset(&r_cmd.data, 0, RTS5400_MAX_WRITE_DATA_LEN);

	dev_dbg(rts5400->dev, "Enter %s\n", __func__);

	ret = __rts5400_transfer(rts5400, &w_cmd, &r_cmd);

	if (ret < 0) {
		dev_err(rts5400->dev, "%s I2C transfer fails\n", __func__);
		return ret;
	}

	//for (i = 0; i < r_cmd.wr_data_len; i++) {
	//	dev_dbg(rts5400->dev, "Data#%d : 0x%x\n", i, r_cmd.data[i]);
	//}
	memcpy(ic_status, &r_cmd.data, r_cmd.wr_data_len);

	dev_info(rts5400->dev, "RTS5400 Main_version %d Sub_version %d Sub_version_2 %d\n",
			ic_status->main_ver, ic_status->sub_ver, ic_status->sub_ver2);

	dev_info(rts5400->dev, "SMBus %sready, PD %sready, TypeC %sconnect\n",
			IC_STATUS_SMB_READY(ic_status->sm_ready)?"":"NOT ",
			IC_STATUS_PD_READY(ic_status->pd_tc)?"":"NOT ",
			IC_STATUS_TC_CONNECT(ic_status->pd_tc)?"":"NOT ");

	dev_dbg(rts5400->dev, "Exit %s return cmd %x, wr_data_len %d\n", __func__,
			r_cmd.cmd, r_cmd.wr_data_len);

	ret = IC_STATUS_SMB_READY(ic_status->sm_ready)
			& IC_STATUS_PD_READY(ic_status->pd_tc)
			& IC_STATUS_TC_CONNECT(ic_status->pd_tc);

	return ret;
}

int rtk_rts5400_get_status(void)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	int ret, i;
	struct tcpm_command w_cmd, r_cmd;
	struct pd_status_info *status_info = &rts5400->status_info;

	w_cmd.cmd = 0x9;
	w_cmd.wr_data_len = 0x3;
	w_cmd.data[0] = 0x0;
	w_cmd.data[1] = 0;
	w_cmd.data[2] = 0x0D;
	r_cmd.cmd = 0x80;
	r_cmd.wr_data_len = 0xff;
	memset(&r_cmd.data, 0, RTS5400_MAX_WRITE_DATA_LEN);

	dev_dbg(rts5400->dev, "Enter %s\n", __func__);

	ret = __rts5400_transfer(rts5400, &w_cmd, &r_cmd);

	if (ret < 0) {
		dev_err(rts5400->dev, "%s I2C transfer fails\n", __func__);
		return ret;
	}

	//for (i = 0; i < r_cmd.wr_data_len; i++) {
	//	dev_dbg(rts5400->dev, "Data#%d : 0x%x\n", i, r_cmd.data[i]);
	//}

	memcpy(status_info, &r_cmd.data, r_cmd.wr_data_len);

	dev_info(rts5400->dev, "[Status Info] Externally Powered supply %d, Port OP mode %d, Insertion Detect %d\n",
			status_info->supply, status_info->port_op_mode, status_info->insertion_detect);
	dev_info(rts5400->dev, "[Status Info] PD Capable Cable %d, Power Direction %d\n",
			status_info->pd_capable_cable, status_info->power_direction);
	dev_info(rts5400->dev, "[Status Info] Connect Status %d, Port Partner Flags %d\n",
			status_info->connect_status, status_info->port_partner_flag);
	dev_info(rts5400->dev, "[Status Info] Request Data Object 0x%x\n", status_info->request_data_obj);
	dev_info(rts5400->dev, "[Status Info] Port Partner Type %d\n", status_info->port_partner_type);
	dev_info(rts5400->dev, "[Status Info] Battery Charging Status %d\n", status_info->battery_charging_status);
	dev_info(rts5400->dev, "[Status Info] PD Sourcing Vconn %d\n", status_info->pd_sourcing_Vconn);
	dev_info(rts5400->dev, "[Status Info] PD AMS is %s\n", status_info->pd_ams?"in progress":"ready");
	dev_info(rts5400->dev, "[Status Info] DP Role: %s\n", status_info->dp_role?"Sink":"Source");
	dev_info(rts5400->dev, "[Status Info] PD %sexchanged pd message and goodcrc\n", status_info->pd_connect?"":"NOT ");
	dev_info(rts5400->dev, "[Status Info] Alt mode status 0x%x\n", status_info->alt_mode_status);

	dev_dbg(rts5400->dev, "Exit %s return cmd %x, wr_data_len %d\n", __func__,
			r_cmd.cmd, r_cmd.wr_data_len);

	return ret;
}

int rtk_rts5400_get_PDO(int pdo_type, int pdo, int offset,
		int num, u8 *value)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	int ret, i;
	struct tcpm_command w_cmd, r_cmd;
	union pdo_info *pdo_inf;

	w_cmd.cmd = 0x8;
	w_cmd.wr_data_len = 0x3;
	w_cmd.data[0] = 0x83;
	w_cmd.data[1] = 0;
	w_cmd.data[2] = PDO_TYPE(pdo_type) | PDO_TCPM(pdo) | PDO_OFFEST(offset) | PDO_NUM(num);
	r_cmd.cmd = 0x80;
	r_cmd.wr_data_len = 0xff;
	memset(&r_cmd.data, 0, RTS5400_MAX_WRITE_DATA_LEN);

	dev_dbg(rts5400->dev, "Enter %s\n", __func__);

	ret = __rts5400_transfer(rts5400, &w_cmd, &r_cmd);

	if (ret < 0) {
		dev_err(rts5400->dev, "%s I2C transfer fails\n", __func__);
		return ret;
	}

	dev_dbg(rts5400->dev, "[PDO status] %s %s PDO, offset %d, num %d\n",
			pdo?"Partner":"TCPM", pdo_type?"Source":"Sink", offset, num);

	//for (i = 0; i < r_cmd.wr_data_len; i++) {
	//	dev_dbg(rts5400->dev, "Data#%d : 0x%x\n", i, r_cmd.data[i]);
	//}

	for (i = 0; i < r_cmd.wr_data_len; i = i + 4) {
		pdo_inf = (union pdo_info *)&r_cmd.data[i];

		if (pdo == PDO_TYPE_SOURCE && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_FIX) {
			dev_info(rts5400->dev, "[PDO status] %s Fix PDO, valtage %d mV\n",
				pdo_type?"Source":"Sink", (pdo_inf->so_f.valtage) * 50);
		} else if (pdo == PDO_TYPE_SOURCE && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_VAR) {
			dev_info(rts5400->dev, "[PDO status] %s Var PDO\n", pdo_type?"Source":"Sink");
		} else if (pdo == PDO_TYPE_SOURCE && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_BAT) {
			dev_info(rts5400->dev, "[PDO status] %s Bat PDO\n", pdo_type?"Source":"Sink");
		} else if (pdo == PDO_TYPE_SINK && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_FIX) {
			dev_info(rts5400->dev, "[PDO status] %s Fix PDO, valtage %d mV\n",
				pdo_type?"Source":"Sink", (pdo_inf->si_f.valtage) * 50);
		} else if (pdo == PDO_TYPE_SINK && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_VAR) {
			dev_info(rts5400->dev, "[PDO status] %s Var PDO\n", pdo_type?"Source":"Sink");
		} else if (pdo == PDO_TYPE_SINK && pdo_inf->com.power_type == PDO_INFO_POWER_TYPE_BAT) {
			dev_info(rts5400->dev, "[PDO status] %s Var PDO\n", pdo_type?"Source":"Sink");
		}
	}
	dev_dbg(rts5400->dev, "Exit %s return cmd %x, wr_data_len %d\n", __func__,
			r_cmd.cmd, r_cmd.wr_data_len);

	if (ret > 0) {
		if (value != NULL) {
			memcpy(value, &r_cmd.data, r_cmd.wr_data_len);
		}
		return r_cmd.wr_data_len;
	}
	return ret;
}

int rtk_rts5400_init_pd_ams(u8 pd_ams)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	int ret, i;
	struct tcpm_command w_cmd, r_cmd;

	w_cmd.cmd = 0x8;
	w_cmd.wr_data_len = 0x3;
	w_cmd.data[0] = 0x20;
	w_cmd.data[1] = 0;
	w_cmd.data[2] = pd_ams;
	r_cmd.cmd = 0x80;
	r_cmd.wr_data_len = 0x0;
	memset(&r_cmd.data, 0, RTS5400_MAX_WRITE_DATA_LEN);

	dev_dbg(rts5400->dev, "Enter %s pd_ams=%x\n", __func__, pd_ams);

	ret = __rts5400_transfer(rts5400, &w_cmd, &r_cmd);

	if (ret < 0) {
		dev_err(rts5400->dev, "%s I2C transfer fails\n", __func__);
		return ret;
	}

	dev_dbg(rts5400->dev, "Exit %s\n", __func__);

	return ret;
}

/* Type C */
bool rtk_rts5400_is_enabled(void)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	struct device *dev = rts5400->dev;

	return !rts5400->no_device;
}

bool rtk_rts5400_is_UFP_attached(void)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	struct device *dev = rts5400->dev;
	struct pd_status_info *status_info = &rts5400->status_info;

	return status_info->port_partner_type == PD_STATUS_INFO_PARTNER_UFP;
}

int rtk_rts5400_set_type_c_soft_reset(void)
{
	int ret = 0;

	ret = rtk_rts5400_init_pd_ams(PD_AMS_SOFT_RESET);

	return ret;
}

int rtk_rts5400_get_current_pdo_voltage(void)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	struct device *dev = rts5400->dev;
	struct pd_status_info *status_info = &rts5400->status_info;
	struct rdo_info *rdo = NULL;
	union pdo_info *pdo = NULL;
	int offest;
	int ret = -1;
	u8 *buffer;

	dev_dbg(dev, "Enter %s\n", __func__);
	if (status_info->request_data_obj == 0x0) {
		dev_err(dev, "%s NO request_data_obj", __func__);
		return ret;
	} else
		rdo = &status_info->request_data_obj;

	offest = (rdo->obj_pos - 1) * 4;

	dev_dbg(dev, "%s rdo->obj_pos=%d, offest=%d", __func__,
			rdo->obj_pos, offest);

	if (offest < 0) {
		dev_err(dev, "%s Error! rdo->obj_pos=%d, offest=%d",
			__func__, rdo->obj_pos, offest);
		return ret;
	}

	buffer = kzalloc(7*4, GFP_KERNEL);

	ret = rtk_rts5400_get_PDO(PDO_TYPE_SOURCE, PDO_TCPM_PARTNER, 0, 7, buffer);

	if (ret < 0) {
		dev_err(dev, "%s rtk_rts5400_get_PDO fail(ret=%d)", __func__, ret);
		kfree(buffer);
		return ret;
	}
	pdo = buffer + offest;

	if (pdo != NULL && pdo->com.power_type == PDO_INFO_POWER_TYPE_FIX) {
		dev_info(rts5400->dev, "Current Partner Source Fix PDO, "
				"valtage %d mV\n", (pdo->so_f.valtage) * 50);
		ret = pdo->so_f.valtage * 50;
	}

	kfree(buffer);
	dev_dbg(dev, "Exit %s\n", __func__);
	return ret;
}

/* init and probe */
static int rtk_rts5400_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct rts5400_dev *rts5400 = &g_rts5400;
	struct device *dev = &client->dev;
	struct device_node	*node = dev->of_node;
	unsigned int gpio, power_on_12v = 0;

	int i, ret;
	u8 val;
	dev_dbg(dev, "Enter %s\n", __func__);

	memset(rts5400, 0, sizeof(rts5400));

	rts5400->client = client;
	rts5400->dev = dev;

	i2c_set_clientdata(client, rts5400);

	ret = rtk_rts5400_get_IC_status();
	if (ret < 0) {
		dev_err(dev, "[RTS5400] rtk_rts5400_get_IC_status fail (ret=%d)\n", ret);
		rts5400->no_device = true;
	} else {
		ret = rtk_rts5400_get_status();
		if (ret < 0)
			dev_err(dev, "[RTS5400] rtk_rts5400_get_status fail (ret=%d)\n", ret);
		ret = rtk_rts5400_get_PDO(PDO_TYPE_SOURCE, PDO_TCPM_TCPM, 0, 7, NULL);
		if (ret < 0)
			dev_err(dev, "[RTS5400] rtk_rts5400_get_PDO "
				"(PDO_TYPE_SOURCE, PDO_TCPM_TCPM) fail (ret=%d)\n", ret);
		ret = rtk_rts5400_get_PDO(PDO_TYPE_SOURCE, PDO_TCPM_PARTNER, 0, 7, NULL);
		if (ret < 0)
			dev_err(dev, "[RTS5400] rtk_rts5400_get_PDO "
				"PDO_TYPE_SOURCE, PDO_TCPM_PARTNER) fail (ret=%d)\n", ret);
		ret = rtk_rts5400_get_PDO(PDO_TYPE_SINK, PDO_TCPM_TCPM, 0, 7, NULL);
		if (ret < 0)
			dev_err(dev, "[RTS5400] rtk_rts5400_get_PDO "
				"(PDO_TYPE_SINK, PDO_TCPM_TCPM) fail (ret=%d)\n", ret);
		ret = rtk_rts5400_get_PDO(PDO_TYPE_SINK, PDO_TCPM_PARTNER, 0, 7, NULL);
		if (ret < 0)
			 dev_err(dev, "[RTS5400] rtk_rts5400_get_PDO "
				"(PDO_TYPE_SINK, PDO_TCPM_PARTNER) fail (ret=%d)\n", ret);

		ret = rtk_rts5400_get_current_pdo_voltage();

		if (ret >= 12000)
			power_on_12v = 1;

		gpio = of_get_named_gpio(node, "realtek,12v-power-gpio", 0);

		if (gpio_is_valid(gpio)) {
			rts5400->pow_gpio = gpio;
			dev_info(dev, "%s get 12V power-gpio (id=%d) OK\n", __func__, gpio);
			if (gpio_direction_output(gpio, power_on_12v))
				dev_err(dev, "%s ERROR set 12v power (= 0) fail\n", __func__);
			else
				dev_info(dev, "%s Power %s 12v\n", __func__, power_on_12v?"on":"off");
		 } else {
			dev_err(dev, "Error 12V-power-gpio no found");
			rts5400->pow_gpio = -1;
		}
	}

	dev_dbg(dev, "Exit %s\n", __func__);

	return 0;
}

#ifdef CONFIG_SUSPEND
static int rtk_rts5400_suspend(struct device *dev)
{
	dev_dbg(dev, "Enter %s\n", __func__);

	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}

static int rtk_rts5400_resume(struct device *dev)
{
	dev_dbg(dev, "Enter %s\n", __func__);

	dev_dbg(dev, "Exit %s\n", __func__);
	return 0;
}
#else

#define rtk_rts5400_suspend NULL
#define rtk_rts5400_resume NULL

#endif

static const struct dev_pm_ops rtk_rts5400_pm_ops = {
	.suspend    = rtk_rts5400_suspend,
	.resume     = rtk_rts5400_resume,
};

static const struct i2c_device_id rtk_rts5400_ids[] = {
	{"rtk-rts5400", 0},
	{ },
};
MODULE_DEVICE_TABLE(i2c, rtk_rts5400_ids);

static struct i2c_driver rtk_rts5400_driver = {
	.driver = {
		.name = "rtk_rts5400",
		.owner = THIS_MODULE,
		.pm = &rtk_rts5400_pm_ops,
	},
	.probe = rtk_rts5400_probe,
	.id_table = rtk_rts5400_ids,
};

module_i2c_driver(rtk_rts5400_driver);

MODULE_DESCRIPTION("RTS5400 Type C Port Manager Driver");
MODULE_AUTHOR("Stanley Chang");
MODULE_LICENSE("GPL");
