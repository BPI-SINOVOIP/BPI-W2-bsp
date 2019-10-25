/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/kernel.h>
//#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/string.h>
#include <linux/if.h>
#include <asm/uaccess.h> /* jiffies */
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include "AsicDriver/asicRegs.h"
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL2.h"


#define RTL_DEBUG       1
#ifdef RTL_DEBUG
#define DBG(fmt, ...) printk(KERN_ERR "%s:%d: " fmt "\n", \
			__func__, __LINE__, ## __VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

extern rtl8651_tblAsic_ethernet_t	rtl8651AsicEthernetTable[];
extern uint8 hwnat_mac0_enable; /* 0: interface used by SATA, 1: interface used by NAT */
extern uint8 hwnat_mac0_mode; /* 0:RGMII, 1:SGMII */
extern uint8 hwnat_mac5_conn_to; /* 0:PHY, 1:MAC */

typedef struct link_mon_s {
	uint8_t name[IFNAMSIZ];
	struct timer_list sec_timer; /* kernel timer */
	struct work_struct work_q; /* work queue (interrupt in the lower half of the method) */
	uint32_t counter; /* into the statistics of the number of interrupts */
	uint32_t interval;
} link_mon_t;
static link_mon_t mac0_sgmii_lnk;

#define TIMER_OVER 1 /* call interval */


void rtd129x_mac0_sgmii_link_chk(void)
{
	uint32_t val, remote_ablity;
	static uint8_t lnk_state = 0;
	uint8_t speed, duplex;

	/* 1. Get link status */
	val = READ_MEM32(SERDES_WRP_SDS_LINK) >> SERDES_WRP_SDS_LINK_partner_ablity_shift;
	remote_ablity = val;
	//DBG("SERDES_WRP_SDS_LINK_partner_ablity = 0x%05x", val);
	if ((val & SERDES_WRP_SDS_LINK_partner_fib_linkok) == 0) {
		if (lnk_state == 0)
			return;
		else
			lnk_state = 0;

		/* clear local ability */
		WRITE_MEM32(SERDES_WRP_SDS_LINK, 0);

		/* update MAC0 as force 10M link down */
		val = READ_MEM32(PCRP0) & ~(PauseFlowControl_MASK | AutoNegoSts_MASK | PollLinkStatus | ForceLink);
		val |= EnForceMode | ForceSpeed10M | EnablePHYIf;
		DBG("link down!");
		WRITE_MEM32(PCRP0, val);

		rtl8651_setAsicEthernetLinkStatus(0, FALSE);

	} else {
		if (lnk_state == 1)
			return;
		else
			lnk_state = 1;

		speed = val & 3;
		duplex = val & (1 << 2);

		/* 2. Force link down */
		val = READ_MEM32(PCRP0) & ~(PauseFlowControl_MASK | PollLinkStatus | ForceLink);
		val |= EnForceMode | EnablePHYIf;
		//DBG("PCRP0 = 0x%08x", val);
		WRITE_MEM32(PCRP0, val);

		/* 3. Wait for all queues empty */
		for (;;) {
			val = READ_MEM32(P0_DCR0);
			if (val > 0)
				goto retry;

			val = READ_MEM32(P0_DCR1);
			if (val > 0)
				goto retry;

			val = READ_MEM32(P0_DCR2);
			if (val > 0)
				goto retry;

			val = READ_MEM32(P0_DCR3);
			if ((val & 0xFFFFFC00) > 0)
				goto retry;

			break;
retry:
			//mdelay(100);
			lnk_state = 0;
			DBG("val 0x%08x, P0_DCR0: 0x%08x 0x%08x 0x%08x 0x%08x", val, READ_MEM32(P0_DCR0),
				READ_MEM32(P0_DCR1), READ_MEM32(P0_DCR2), READ_MEM32(P0_DCR3));
			return;
		}

		/* Set local ablity as remote ablity */
		WRITE_MEM32(SERDES_WRP_SDS_LINK, remote_ablity);

		/* 4. Force new speed, duplex and link up */
		val = READ_MEM32(PCRP0) & ~(PauseFlowControl_MASK | AutoNegoSts_MASK | PollLinkStatus);
		val |= EnForceMode | ForceLink | PauseFlowControlEtxErx | EnablePHYIf;
		switch (speed) {
		case 2:
			val |= ForceSpeed1000M;
			DBG("Speed: 1000M");
			break;
		case 1:
			val |= ForceSpeed100M;
			DBG("Speed: 100M");
			break;
		case 0:
		default:
			DBG("Speed: 10M");
			val |= ForceSpeed10M;
		}
		if (duplex > 0) {
			val |= ForceDuplex;
			DBG("Full duplex");
		} else {
			DBG("Half duplex");
		}
		//DBG("PCRP0 = 0x%08x", val);
		WRITE_MEM32(PCRP0, val);

		rtl8651_setAsicEthernetLinkStatus(0, TRUE);
	}

}

/* timer interrupt service routine */
static void sec_timer_function(unsigned long data)
{
	link_mon_t *ln = (link_mon_t *) data;
	//scheduler work queue
	if (schedule_work(&ln->work_q) == 0) {
		DBG("cannot schedule work!!!");
	}
	ln->counter++;
	//DBG("Timer Expired interval is %d!!", ln->interval);
	//DBG("name [%s] counter =%d", ln->name, ln->counter);
}

//Register a kernel timer
static void sec_timer_register (struct timer_list * ptimer, uintptr_t data) {
	link_mon_t *ln = (link_mon_t *) data;
	DBG("periodic task: name [%s] interval %d secs", ln->name, ln->interval);
	init_timer(ptimer);
	ptimer->data = data;
	ptimer->expires = jiffies + (ln->interval * HZ);
	ptimer->function = sec_timer_function;
	add_timer(ptimer);
}

//timer bottom half handler function
static void lnk_mon_fetch_thread (struct work_struct * work)
{
	link_mon_t *ln = container_of(work, struct link_mon_s, work_q);
	rtd129x_mac0_sgmii_link_chk();
	mod_timer(&ln->sec_timer, jiffies + (ln->interval * HZ));
}

void rtk_polling_mac0_lnk_status(void)
{
	memset(&mac0_sgmii_lnk, 0, sizeof(struct link_mon_s));
	strcpy(mac0_sgmii_lnk.name, "mac0_sgmii");
	mac0_sgmii_lnk.interval = TIMER_OVER;
	sec_timer_register(&mac0_sgmii_lnk.sec_timer, (uintptr_t) &mac0_sgmii_lnk);
	INIT_WORK(&mac0_sgmii_lnk.work_q, lnk_mon_fetch_thread);
}

