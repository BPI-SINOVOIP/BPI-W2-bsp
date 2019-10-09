/*
 * hdcp.h - RTK hdcp tx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _HDCP_H_
#define _HDCP_H_


/********************************/
/* Structures related to ioctl  */
/********************************/

/* HDCP key size in 32-bit words */
#define DESHDCP_KEY_SIZE 160
#define HDCP_PK_SIZE 280
#define HDCP_Aksv_SIZE 5

/* HDCP ioctl */
#include <linux/ioctl.h>
#include <linux/types.h>
#include <asm/io.h>

struct hdcp_encrypt_control {
	uint32_t in_key[DESHDCP_KEY_SIZE];
	uint32_t *out_key;
};

struct hdcp_enable_control {
	uint8_t PK[HDCP_PK_SIZE];
	uint8_t Aksv[HDCP_Aksv_SIZE];
	int nb_retry;
};

#define MAX_SHA_DATA_SIZE       645
#define MAX_SHA_VPRIME_SIZE     20
#define SHA_BLK_SIZE   64
#define SHA1_HASH_SIZE   5
#define KSVLIST_SIZE   640

/* For HDCP2.2 repeater */
#define RECEIVERID_SIZE (40/8)
#define MAX_DEVICECOUNT (32)

struct hdcp_sha_in {
	uint8_t data[MAX_SHA_DATA_SIZE];
	uint32_t byte_counter;
	uint8_t vprime[MAX_SHA_VPRIME_SIZE];
};

struct hdcp_wait_control {
	uint32_t event;
	struct hdcp_sha_in *data;
};

struct hdcp_ksvlist_info {
	uint8_t Aksv[HDCP_Aksv_SIZE];
	uint8_t ksvlist[KSVLIST_SIZE];
	uint8_t bstatus[2];
	uint32_t device_count;
	uint8_t Bksv[HDCP_Aksv_SIZE];
};


struct H2_RepeaterAuthSendRxIdList_PayLoad {
	unsigned char Rxinfo[2];
	unsigned char Seq_num[3];
	unsigned char VPrime[32]; //V_SIZE/2
	unsigned char Receiver_ID_LIST[RECEIVERID_SIZE*MAX_DEVICECOUNT]; //V_SIZE/2
	unsigned char maxDevsExceeded; /* true if devcount > 31*/
	unsigned char maxCascadeExceeded;   /* true if depth > 4*/
	unsigned char deviceCount;
	unsigned char depth;
	unsigned char HDCP2_0_repeater_downstream;
	unsigned char HDCP1_device_downstream;
} __attribute__((packed));


enum {
	HDCP_ENABLE,
	HDCP_DISABLE,
	HDCP_QUERY_STATUS,
	HDCP_QUERY_SINK_HDCP_CAPABLE,
	HDCP_GET_DOWNSTREAM_KSVLIST,
	HDCP_SET_22_CIPHER,
	HDCP_CONTROL_22_CIPHER,
	HDCP_SET_22_REPEATER_INFO,
};

/* HDCP state */
#define HDCP_STATE_DISABLED             0
#define HDCP_STATE_INIT                 1
#define HDCP_STATE_AUTH_1ST_STEP        2
#define HDCP_STATE_AUTH_2ND_STEP        3
#define HDCP_STATE_AUTH_3RD_STEP        4
#define HDCP_STATE_AUTH_FAIL_RESTARTING 5
#define HDCP_STATE_AUTH_FAILURE         6

/* HDCP events */
#define HDCP_EVENT_STEP1	(1 << 0x0)
#define HDCP_EVENT_STEP2	(1 << 0x1)
#define HDCP_EVENT_EXIT		(1 << 0x2)

/* HDCP user space status */
#define HDCP_US_NO_ERR		(0 << 8)
#define HDCP_US_FAILURE		(1 << 8)

#ifdef __KERNEL__

#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/fs.h>


enum hdcp_repeater {
	HDCP_RECEIVER = 0,
	HDCP_REPEATER = 1
};

enum encryption_state {
	HDCP_ENC_OFF = 0x0,
	HDCP_ENC_ON  = 0x1
};

enum ri_state {
	HDCP_RI_OFF = 0x0,
	HDCP_RI_ON  = 0x1
};

enum av_mute {
	AV_MUTE_SET = 0x01,
	AV_MUTE_CLEAR = 0x10
};

enum sink_hdcp_capable {
	HDCP_INCAPABLE = 0,
	HDCP_CAPABLE = 1
};

enum {
	HDCP_22_CIPHER_DEFAULT,
	HDCP_22_CIPHER_PAUSE,
	HDCP_22_CIPHER_RESUME,
};

/***************************/
/* Definitions             */
/***************************/

/* Status / error codes */
#define HDCP_OK                 0
#define HDCP_DDC_ERROR          1
#define HDCP_AUTH_FAILURE       2
#define HDCP_AKSV_ERROR         3
#define HDCP_3DES_ERROR         4
#define HDCP_SHA1_ERROR         5
#define HDCP_DRIVER_ERROR       6
#define HDCP_CANCELLED_AUTH     7

#define HDCP_INFINITE_REAUTH    0x100
#define HDCP_MAX_FAIL_MESSAGES  3

/* FIXME: should be 300ms delay between HDMI start frame event and HDCP enable
 * (to respect 7 VSYNC delay in 24 Hz)
 */
#define HDCP_ENABLE_DELAY       300
#define HDCP_R0_DELAY           110
#define HDCP_KSV_TIMEOUT_DELAY  5000
#define HDCP_REAUTH_DELAY       1000

/* Event source */
#define HDCP_SRC_SHIFT          8
#define HDCP_IOCTL_SRC          (0x1 << HDCP_SRC_SHIFT)
#define HDCP_HDMI_SRC           (0x2 << HDCP_SRC_SHIFT)
#define HDCP_IRQ_SRC            (0x4 << HDCP_SRC_SHIFT)
#define HDCP_WORKQUEUE_SRC      (0x8 << HDCP_SRC_SHIFT)

/* Workqueue events */
/* Note: HDCP_ENABLE_CTL, HDCP_R0_EXP_EVENT, HDCP_KSV_TIMEOUT_EVENT and
 * HDCP_AUTH_REATT_EVENT can be cancelled by HDCP disabling
 */
#define HDCP_ENABLE_CTL         (HDCP_IOCTL_SRC         | 0)
#define HDCP_DISABLE_CTL        (HDCP_IOCTL_SRC         | 1)
#define HDCP_START_FRAME_EVENT  (HDCP_HDMI_SRC          | 2)
#define HDCP_STOP_FRAME_EVENT   (HDCP_HDMI_SRC          | 3)
#define HDCP_HPD_LOW_EVENT      (HDCP_IRQ_SRC           | 4)
#define HDCP_RI_FAIL_EVENT      (HDCP_IRQ_SRC           | 5)
#define HDCP_KSV_LIST_RDY_EVENT (HDCP_IRQ_SRC           | 6)

#define HDCP_R0_EXP_EVENT       (HDCP_WORKQUEUE_SRC     | 7)
#define HDCP_KSV_TIMEOUT_EVENT  (HDCP_WORKQUEUE_SRC     | 8)
#define HDCP_AUTH_REATT_EVENT   (HDCP_WORKQUEUE_SRC     | 9)
/* #define HDCP_R0_CHECK_EVENT   (HDCP_WORKQUEUE_SRC     | 0xa) */

/* IRQ status */
#define HDCP_IRQ_RI_FAIL 0x01
#define HDCP_IRQ_KSV_RDY 0x02

enum hdcp_states {
	HDCP_DISABLED,
	HDCP_ENABLE_PENDING,
	HDCP_AUTHENTICATION_START,
	HDCP_WAIT_R0_DELAY,
	HDCP_WAIT_KSV_LIST,
	HDCP_LINK_INTEGRITY_CHECK,
	HDCP_KEY_ENCRYPTION_ONGOING
};

enum hdmi_states {
	HDMI_STOPPED,
	HDMI_STARTED
};

struct hdcp_delayed_work {
	struct delayed_work work;
	int event;
};

struct hdcp {
	void __iomem *hdcp_base_addr;
	unsigned int hdcp_irq_num;
	struct mutex lock;
	struct hdcp_enable_control *en_ctrl;
	enum hdmi_states hdmi_state;
	enum hdcp_states hdcp_state;
	int auth_state;
	struct delayed_work *pending_start;
	/* Following variable should store works submitted from workqueue
	 * context
	 * WARNING: only ONE work at a time can be stored (no conflict
	 * should happen). It is used to allow cancelled pending works when
	 * disabling HDCP
	 */
	struct delayed_work *pending_wq_event;
	int retry_cnt;
	int fail_cnt;
	int av_mute_needed;
	int print_messages;
	int dss_state;
	int hdmi_restart;
	int hpd_low;
	spinlock_t spinlock;
	struct workqueue_struct *workqueue;
	int hdcp_up_event;
	int hdcp_down_event;
	bool hdcp_keys_loaded;
	int hdcp_enabled;
	int hdcp2p2_enabled;
};

/**
 * riv           : hw_riv_1_(1-2)
 * ks_xor_lc128  : sw_key_1_(1-4)
 * frame_num     : frame_num_(1-2)
 * frame_num_add : frame_num_add_(1-2)
 * data_num      : data_num
 * data_num_add  : data_num_add
 * hdcp_22_en    : hdcp_22_ctrl:hdcp_22_en
 * aes_sw_en     : hdcp_22_ctrl:aes_sw_en
 */
struct HDCP_22_CIPHER_INFO {
	unsigned long long frame_num;
	unsigned long long frame_num_add;
	unsigned int data_num;
	unsigned int data_num_add;
	unsigned int rsvd_1;
	unsigned int rsvd_2;
	unsigned int rsvd_3;
	unsigned char riv[8];
	unsigned char ks_xor_lc128[16];
	unsigned char hdcp_22_en;
	unsigned char aes_sw_en;
	unsigned char rsvd_4;
	unsigned char rsvd_5;
};

extern struct hdcp hdcp;
extern struct hdcp_sha_in sha_input;
extern struct hdcp_ksvlist_info ksvlist_info;

/***************************/
/* Macros for accessing HW */
/***************************/

#define WR_REG_32(base, offset, val)    writel(val, (volatile unsigned int*)(base + offset))
#define RD_REG_32(base, offset)         readl((volatile unsigned int*)(base + offset))


#undef FLD_MASK
#define FLD_MASK(start, end)    (((1 << (start - end + 1)) - 1) << (end))
#undef FLD_VAL
#define FLD_VAL(val, start, end) (((val) << end) & FLD_MASK(start, end))
#define FLD_GET(val, start, end) (((val) & FLD_MASK(start, end)) >> (end))
#define FLD_MOD(orig, val, start, end) \
	(((orig) & ~FLD_MASK(start, end)) | FLD_VAL(val, start, end))

#define WR_FIELD_32(base, offset, start, end, val) \
	WR_REG_32(base, offset, FLD_MOD(RD_REG_32(base, offset), val, start, end))

#define RD_FIELD_32(base, offset, start, end) \
	((RD_REG_32(base, offset) & FLD_MASK(start, end)) >> (end))


#define __RTK_HDCP_GENERIC_DEBUG__  0

#if __RTK_HDCP_GENERIC_DEBUG__
#define HDCP_DEBUG(format, ...) printk("HDCP_DEBUG: " format "\n", ## __VA_ARGS__)
#else
#define HDCP_DEBUG(format, ...)
#endif

#define HDCP_ERROR(format, ...) printk(KERN_ERR "HDCP_ERROR: " format "\n", ## __VA_ARGS__)
#define HDCP_INFO(format, ...) printk(KERN_WARNING "HDCP_INFO: " format "\n", ## __VA_ARGS__)

/***************************/
/* Function prototypes     */
/***************************/

/* IP control */
int hdcp_lib_disable(void);
int hdcp_lib_step1_start(void);
int hdcp_lib_step1_r0_check(void);
int hdcp_lib_step2(void);
int hdcp_lib_irq(void);
void hdcp_lib_auto_ri_check(bool state);
void hdcp_lib_auto_bcaps_rdy_check(bool state);
void hdcp_lib_set_av_mute(enum av_mute av_mute_state);
int hdcp_lib_r0_check(void);
int hdcp_lib_query_sink_hdcp_capable(void);
void hdcp_lib_set_22_cipher(struct HDCP_22_CIPHER_INFO *arg);
void hdcp_lib_control_22_cipher(int control_flag);

#endif /* __KERNEL__ */

#endif /* _HDCP_H_ */
