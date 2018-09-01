/*
 * rtd16xx_suspend.h - power management driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#ifndef RTD16XX_SUSPEND_H_
#define RTD16XX_SUSPEND_H_

#include <soc/realtek/rtk_ipc_shm.h>
#include <soc/realtek/rtk_pm.h>

#define SETMASK(bits, pos) (((-1U) >> (32-bits)) << (pos))
#define CLRMASK(bits, pos) (~(SETMASK(bits, pos)))
#define SET_VAL(val,bits,pos) ((val << pos) & SETMASK(bits, pos))
#define GET_VAL(reg,bits,pos) ((reg & SETMASK(bits, pos)) >> pos)

#define AUTHOR_SHIFFT 30
#define AUTHOR_BITS 2
#define AUTHOR_MASK(val) SET_VAL(val,AUTHOR_BITS,AUTHOR_SHIFFT)
#define AUTHOR_GET(reg) GET_VAL(reg,AUTHOR_BITS,AUTHOR_SHIFFT)
#define AUTHOR_IS_SCPU(reg) (AUTHOR_GET(reg) == AUTHOR_SCPU)
#define AUTHOR_IS_ACPU(reg) (AUTHOR_GET(reg) == AUTHOR_ACPU)

#define NOTIFY_SHIFFT 0
#define NOTIFY_BITS 8
#define NOTIFY_MASK(val) SET_VAL(val,NOTIFY_BITS,NOTIFY_SHIFFT)
#define NOTIFY_GET(reg) GET_VAL(reg,NOTIFY_BITS,NOTIFY_SHIFFT)

#define SUSPEND_ISO_GPIO_BASE 0
#define SUSPEND_ISO_GPIO_SIZE 86

#define SUSPEND_MAGIC_KEY 0xEA
#define SUSPEND_MAGIC_SHIFFT 24
#define SUSPEND_MAGIC_BITS 8
#define SUSPEND_MAGIC_MASK (SUSPEND_MAGIC_KEY << SUSPEND_MAGIC_SHIFFT)
#define SUSPEND_MAGIC_GET(val) GET_VAL(val, 8, 24)

#define WAKEUP_FLAGS_SHIFFT	 0
#define WAKEUP_FLAGS_BITS (eWAKEUP_ON_MAX)
#define WAKEUP_FLAGS_MASK(val) SET_VAL(val, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)
#define WAKEUP_FLAGS_GET(reg) GET_VAL(reg, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)

#define RESUME_STATE_SHIFFT 16
#define RESUME_STATE_BITS 8
#define RESUME_STATE_MASK(val) SET_VAL(val, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)
#define RESUME_STATE_GET(reg) GET_VAL(reg, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)

#define RESUME_DATA_SHIFFT 0
#define RESUME_DATA_BITS 16
#define RESUME_DATA_MASK(val) SET_VAL(val, RESUME_DATA_BITS, RESUME_DATA_SHIFFT)
#define RESUME_DATA_GET(reg) GET_VAL(reg, RESUME_DATA_BITS, RESUME_DATA_SHIFFT)

#define AUDIO_RECIPROCAL_TIMER_SHIFFT 0
#define AUDIO_RECIPROCAL_TIMER_BITS 24
#define AUDIO_RECIPROCAL_TIMER_MASK(val) SET_VAL(val, AUDIO_RECIPROCAL_TIMER_BITS, AUDIO_RECIPROCAL_TIMER_SHIFFT)
#define AUDIO_RECIPROCAL_TIMER_GET(reg) GET_VAL(reg, AUDIO_RECIPROCAL_TIMER_BITS, AUDIO_RECIPROCAL_TIMER_SHIFFT)

enum {
	AUTHOR_SCPU = 0x1,
	AUTHOR_ACPU,
};

enum _notify_flag{
	NOTIFY_NONE,
	NOTIFY_SUSPEND_TO_RAM = 0x01,
	NOTIFY_SUSPEND_TO_COOLBOOT,
	NOTIFY_SUSPEND_TO_WFI,

	NOTIFY_RESUME_PLATFORM = 0x10,
	NOTIFY_RESUME_END,
	NOTIFY_SCPU_READY,
	NOTIFY_ACPU_READY,
};

enum _suspend_mode {
	SUSPEND_TO_RAM,
	SUSPEND_TO_COOLBOOT,
	SUSPEND_TO_WFI,
	MAX_SUSPEND_MODE,
};

enum _suspend_wakeup {
	eWAKEUP_ON_LAN,
	eWAKEUP_ON_IR,
	eWAKEUP_ON_GPIO,
	eWAKEUP_ON_ALARM,
	eWAKEUP_ON_TIMER,
	eWAKEUP_ON_CEC,
	eWAKEUP_ON_MAX,
};

enum _wakeup_flags {
	fWAKEUP_ON_LAN = 0x1U << eWAKEUP_ON_LAN,
	fWAKEUP_ON_IR = 0x1U << eWAKEUP_ON_IR,
	fWAKEUP_ON_GPIO = 0x1U << eWAKEUP_ON_GPIO,
	fWAKEUP_ON_ALARM = 0x1U << eWAKEUP_ON_ALARM,
	fWAKEUP_ON_TIMER = 0x1U << eWAKEUP_ON_TIMER,
	fWAKEUP_ON_CEC = 0x1U << eWAKEUP_ON_CEC,
};

enum _RESUME_STATE {
	RESUME_NONE	 = 0,
	RESUME_UNKNOW,
	RESUME_IR,
	RESUME_GPIO,
	RESUME_LAN,
	RESUME_ALARM,
	RESUME_TIMER,
	RESUME_CEC,
	RESUME_MAX_STATE,
};

struct suspend_param {
	unsigned int wakeup_source;
	unsigned int timerout_val;
	char wu_gpio_en[SUSPEND_ISO_GPIO_SIZE];
	char wu_gpio_act[SUSPEND_ISO_GPIO_SIZE];
}__attribute__((packed));;

extern const char *const rtk_suspend_resume_states[RESUME_MAX_STATE];
extern const char *const rtk_suspend_wakeup_states[eWAKEUP_ON_MAX];
extern const char *const rtk_suspend_states[MAX_SUSPEND_MODE];

#endif /* RTD16XX_SUSPEND_H_ */
