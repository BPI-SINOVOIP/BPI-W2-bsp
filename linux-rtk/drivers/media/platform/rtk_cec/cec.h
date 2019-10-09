/*
 *  Copyright (C) 2016 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __CEC_H__
#define __CEC_H__

#include <linux/device.h>
#include "cm_buff.h"

typedef struct {
	unsigned long id;
	char *name;
	struct device dev;
} cec_device;

extern int cec_device_en[2];
extern int *cec_device_pthis[2];

#define to_cec_device(x)  container_of(x, cec_device, dev)

static inline void *cec_get_drvdata(cec_device *device)
{
	return dev_get_drvdata(&device->dev);
}

static inline void cec_set_drvdata(cec_device *device, void *data)
{
	struct device *dev = &device->dev;

	dev_set_drvdata(dev, data);
}

typedef struct {
	char *name;
	struct device_driver drv;

	int (*probe)(cec_device *dev);
	void (*remove)(cec_device *dev);
	int (*xmit)(cec_device *dev, cm_buff *cmg, unsigned long flags);
	cm_buff *(*read)(cec_device *dev, unsigned long flags);
	int (*enable)(cec_device *dev, unsigned char on_off);
	int (*set_rx_mask)(cec_device *dev, unsigned short addr);
	int (*set_physical_addr)(cec_device *dev, unsigned short phy_addr);
	int (*set_cec_version)(cec_device *dev, unsigned char version);
	int (*set_device_vendor_id)(cec_device *dev, unsigned long vendor_id);
	int (*set_stanby_mode)(cec_device *dev, unsigned long mode);
	int (*set_retry_num)(cec_device *dev, unsigned long num);
	int (*suspend)(cec_device *dev);
	int (*resume)(cec_device *dev);
	int (*get_physical_addr)(cec_device *dev);
} cec_driver;

extern int register_cec_device(cec_device *device);
extern void unregister_cec_device(cec_device *device);

#define _BIT(x)         (1UL << x)
#define TEST_BIT(x, i) (x & (1<<i))
#define STANBY_RESPONSE_GIVE_POWER_STATUS       _BIT(0)
#define STANBY_RESPONSE_POOL                    _BIT(1)
#define STANBY_RESPONSE_GIVE_PHYSICAL_ADDR      _BIT(2)
#define STANBY_RESPONSE_GET_CEC_VERISON         _BIT(3)
#define STANBY_RESPONSE_GIVE_DEVICE_VENDOR_ID   _BIT(4)
#define STANBY_WAKEUP_BY_ROUTING_INFO           _BIT(26)
#define STANBY_WAKEUP_BY_ROUTING_CHANGE         _BIT(27)
#define STANBY_WAKEUP_BY_REQUEST_AUDIO_SYSTEM   _BIT(28)
#define STANBY_WAKEUP_BY_USER_CONTROL           _BIT(29)
#define STANBY_WAKEUP_BY_IMAGE_VIEW_ON          _BIT(30)
#define STANBY_WAKEUP_BY_SET_STREAM_PATH        _BIT(31)

#define to_cec_driver(x)  container_of(x, cec_driver, drv)

extern int register_cec_driver(cec_driver *driver);
extern void unregister_cec_driver(cec_driver *driver);

typedef enum {
	CEC_VERSION_1_1                         = 0x00,
	CEC_VERSION_1_2                         = 0x01,
	CEC_VERSION_1_2A                        = 0x02,
	CEC_VERSION_1_3                         = 0x03,
	CEC_VERSION_1_3A                        = 0x04,
	CEC_VERSION_1_4                         = 0x05,
	CEC_VERSION_UNKNOWN                     = 0xFF,
} CEC_VERSION;

#define CEC_WAKEUP_BY_SET_STREAM_PATH       0x01
#define CEC_WAKEUP_BY_PLAY_CMD              0x02
#define CEC_WAKEUP_BY_IMAGE_VIEW_ON         0x04
#define CEC_MSG_GET_CEC_VERSION             0x9F
#define CEC_MSG_CEC_VERSION                 0x9E
#define CEC_MSG_REPORT_POWER_STATUS         0x90
#define CEC_MSG_GIVE_DEVICE_POWER_STATUS    0x8F
#define CEC_MSG_GIVE_DEVICE_VENDOR_ID       0x8C
#define CEC_MSG_DEVICE_VENDOR_ID            0x87
#define CEC_MSG_SET_STREAM_PATH             0x86
#define CEC_MSG_REPORT_PHYSICAL_ADDRESS     0x84
#define CEC_MSG_GIVE_PHYSICAL_ADDRESS       0x83
#define CEC_MSG_ROUTING_INFO                0x81
#define CEC_MSG_ROUTING_CHANGE              0x80
#define CEC_MSG_REQUEST_SYSTEM_AUDIO        0x70
#define CEC_MSG_USER_CONTROL_PRESSED        0x44
#define CEC_MSG_PLAY                        0x41
#define CEC_MSG_STANDBY                     0x36
#define CEC_MSG_TEXT_VIEW_ON                0x0D
#define CEC_MSG_IMAGE_VIEW_ON               0x04
#define CEC_MSG_FEATURE_ABORT               0x00

#define CEC_DEVICE_TV                       0x00
#define CEC_DEVICE_RECORDING_DEVICE         0x01
#define CEC_DEVICE_RESERVED                 0x02
#define CEC_DEVICE_TUNER                    0x03
#define CEC_DEVICE_PLAYBACK_DEVICE          0x04
#define CEC_DEVICE_AUDIO_SYSTEM             0x05
#define CEC_DEVICE_PURE_CEC_SWITCH          0x06
#define CEC_DEVICE_VIDEO_PROCESSOR          0x07

#define CEC_POWER_STATUS_ON                 0x00
#define CEC_POWER_STATUS_STANDBY            0x01
#define CEC_POWER_STATUS_STANDBY_TO_ON      0x02
#define CEC_POWER_STATUS_ON_TO_STANDBY      0x03

#define CEC_ABORT_UNKNOWN_OPCODE            0x00
#define CEC_ABORT_NOT_IN_CORECT_MODE        0x01
#define CEC_ABORT_CAN_NOT_PROVIDE_SOURCE    0x02
#define CEC_ABORT_INVALID_OPERAND           0x03
#define CEC_ABORT_REFUSED                   0x04

#define CEC_USER_CONTROL_POWER_TOGGLE       0x6B
#define CEC_USER_CONTROL_POWER_ON           0x6D
#define CEC_USER_CONTROL_POWER              0x40

#endif

