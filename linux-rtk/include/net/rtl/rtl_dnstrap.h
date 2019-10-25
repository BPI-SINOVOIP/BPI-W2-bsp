/*
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef _RTL_DNS_TRAP_H
#define _RTL_DNS_TRAP_H

//#define DBG_DNS_TRAP

#if defined(DBG_DNS_TRAP)
	#define DBGP_DNS_TRAP(format, arg...) 	  \
		do {printk(format , ## arg);}while(0)
#else
	#define DBGP_DNS_TRAP(format, arg...)
#endif

typedef struct _header {
	unsigned short int	id;
	unsigned short		u;

	short int	qdcount;
	short int	ancount;
	short int	nscount;
	short int	arcount;
} dnsheader_t;

extern int br_dns_filter_enter(struct sk_buff *skb);
extern int is_dns_packet(struct sk_buff *skb);
extern int dns_filter_enable;

extern int br_dns_filter_init(void);
extern void br_dns_filter_exit(void);


#endif	/* _RTL_DNS_TRAP_H */
