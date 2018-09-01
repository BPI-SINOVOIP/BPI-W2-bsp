#ifndef __ASM_ARCH_RTK119X_PM_H__
#define __ASM_ARCH_RTK119X_PM_H__

#include <soc/realtek/rtk_ipc_shm.h>

#define ISO_DUMMY1  0x18007054
#define ISO_DUMMY2  0x18007058

#define SETMASK(bits, pos)		    (((-1U) >> (32-bits))  << (pos))
#define CLRMASK(bits, pos)		    (~(SETMASK(bits, pos)))
#define SET_VAL(val,bits,pos)       ((val << pos) & SETMASK(bits, pos))
#define GET_VAL(reg,bits,pos)       ((reg & SETMASK(bits, pos)) >> pos)

#define AUTHOR_SHIFFT           30
#define AUTHOR_BITS             2
#define AUTHOR_MASK(val)        SET_VAL(val,AUTHOR_BITS,AUTHOR_SHIFFT)
#define AUTHOR_GET(reg)         GET_VAL(reg,AUTHOR_BITS,AUTHOR_SHIFFT)
#define AUTHOR_IS_SCPU(reg)     (AUTHOR_GET(reg) == AUTHOR_SCPU)
#define AUTHOR_IS_ACPU(reg)     (AUTHOR_GET(reg) == AUTHOR_ACPU)

#define NOTIFY_SHIFFT           0
#define NOTIFY_BITS             8
#define NOTIFY_MASK(val)        SET_VAL(val,NOTIFY_BITS,NOTIFY_SHIFFT)
#define NOTIFY_GET(reg)         GET_VAL(reg,NOTIFY_BITS,NOTIFY_SHIFFT)

#define SUSPEND_ISO_GPIO_BASE                   60
#define SUSPEND_ISO_GPIO_SIZE                   21

#define SUSPEND_MAGIC_KEY                       0xEA
#define SUSPEND_MAGIC_SHIFFT                    24
#define SUSPEND_MAGIC_BITS                      8
#define SUSPEND_MAGIC_MASK                      (SUSPEND_MAGIC_KEY << SUSPEND_MAGIC_SHIFFT)
#define SUSPEND_MAGIC_GET(val)                  GET_VAL(val, 8, 24)

#define WAKEUP_FLAGS_SHIFFT                     0
#define WAKEUP_FLAGS_BITS                       (eWAKEUP_ON_MAX)
#define WAKEUP_FLAGS_MASK(val)                  SET_VAL(val, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)
#define WAKEUP_FLAGS_GET(reg)                   GET_VAL(reg, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)

#define RESUME_STATE_SHIFFT                     16
#define RESUME_STATE_BITS                       8
#define RESUME_STATE_MASK(val)                  SET_VAL(val, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)
#define RESUME_STATE_GET(reg)                   GET_VAL(reg, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)

#define RESUME_DATA_SHIFFT                      0
#define RESUME_DATA_BITS                        16
#define RESUME_DATA_MASK(val)                   SET_VAL(val, RESUME_DATA_BITS, RESUME_DATA_SHIFFT)
#define RESUME_DATA_GET(reg)                    GET_VAL(reg, RESUME_DATA_BITS, RESUME_DATA_SHIFFT)

#define GPIO_WAKEUP_EN_SHIFFT                   0
#define GPIO_WAKEUP_EN_BITS                     21
#define GPIO_WAKEUP_EN_MASK(val)                SET_VAL(val, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)
#define GPIO_WAKEUP_EN_GET(reg)                 GET_VAL(reg, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)

#define GPIO_WAKEUP_ACT_SHIFFT                  0
#define GPIO_WAKEUP_ACT_BITS                    21
#define GPIO_WAKEUP_ACT_MASK(val)               SET_VAL(val, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)
#define GPIO_WAKEUP_ACT_GET(reg)                GET_VAL(reg, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)

#define GPIO_OUTPUT_CHANGE_EN_SHIFFT            0
#define GPIO_OUTPUT_CHANGE_EN_BITS              21
#define GPIO_OUTPUT_CHANGE_EN_MASK(val)         SET_VAL(val, GPIO_OUTPUT_CHANGE_EN_BITS, GPIO_OUTPUT_CHANGE_EN_SHIFFT)
#define GPIO_OUTPUT_CHANGE_EN_GET(reg)          GET_VAL(reg, GPIO_OUTPUT_CHANGE_EN_BITS, GPIO_OUTPUT_CHANGE_EN_SHIFFT)

#define GPIO_OUTPUT_CHANGE_ACT_SHIFFT           0
#define GPIO_OUTPUT_CHANGE_ACT_BITS             21
#define GPIO_OUTPUT_CHANGE_ACT_MASK(val)        SET_VAL(val, GPIO_OUTPUT_CHANGE_ACT_BITS, GPIO_OUTPUT_CHANGE_ACT_SHIFFT)
#define GPIO_OUTPUT_CHANGE_ACT_GET(reg)         GET_VAL(reg, GPIO_OUTPUT_CHANGE_ACT_BITS, GPIO_OUTPUT_CHANGE_ACT_SHIFFT)

#define AUDIO_RECIPROCAL_TIMER_SHIFFT           0
#define AUDIO_RECIPROCAL_TIMER_BITS             24
#define AUDIO_RECIPROCAL_TIMER_MASK(val)        SET_VAL(val, AUDIO_RECIPROCAL_TIMER_BITS, AUDIO_RECIPROCAL_TIMER_SHIFFT)
#define AUDIO_RECIPROCAL_TIMER_GET(reg)         GET_VAL(reg, AUDIO_RECIPROCAL_TIMER_BITS, AUDIO_RECIPROCAL_TIMER_SHIFFT)

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

const char *const rtk_suspend_states[MAX_SUSPEND_MODE] = {
    [SUSPEND_TO_RAM]        = "ram",
    [SUSPEND_TO_COOLBOOT]   = "coolboot",
    [SUSPEND_TO_WFI]        = "wfi",
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

const char *const rtk_suspend_wakeup_states[eWAKEUP_ON_MAX] = {
    [eWAKEUP_ON_LAN]        = "lan",
    [eWAKEUP_ON_IR]         = "ir",
    [eWAKEUP_ON_GPIO]       = "gpio",
    [eWAKEUP_ON_ALARM]      = "alarm",
    [eWAKEUP_ON_TIMER]      = "timer",
    [eWAKEUP_ON_CEC]        = "cec",
};

enum _wakeup_flags {
    fWAKEUP_ON_LAN          = 0x1U << eWAKEUP_ON_LAN,
    fWAKEUP_ON_IR           = 0x1U << eWAKEUP_ON_IR,
    fWAKEUP_ON_GPIO         = 0x1U << eWAKEUP_ON_GPIO,
    fWAKEUP_ON_ALARM        = 0x1U << eWAKEUP_ON_ALARM,
    fWAKEUP_ON_TIMER        = 0x1U << eWAKEUP_ON_TIMER,
    fWAKEUP_ON_CEC          = 0x1U << eWAKEUP_ON_CEC,
};

enum _RESUME_STATE {
    RESUME_NONE     = 0,
    RESUME_UNKNOW,
    RESUME_IR,
    RESUME_GPIO,
    RESUME_LAN,
    RESUME_ALARM,
    RESUME_TIMER,
    RESUME_CEC,
    RESUME_MAX_STATE,
};

const char *const rtk_suspend_resume_states[RESUME_MAX_STATE] = {
    [RESUME_NONE]        = "none",
    [RESUME_UNKNOW]      = "unknow",
    [RESUME_IR]          = "ir",
    [RESUME_GPIO]        = "gpio",
    [RESUME_LAN]         = "lan",
    [RESUME_ALARM]       = "alarm",
    [RESUME_TIMER]       = "timer",
    [RESUME_CEC]         = "cec",
};

extern void v7_cpu_resume(void);
#endif
