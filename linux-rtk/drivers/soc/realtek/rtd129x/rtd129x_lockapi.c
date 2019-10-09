/*
 * rtd129x_lockapi.c - Realtek lock API
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 */

#define pr_fmt(fmt) "lockapi: " fmt

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <asm/system_misc.h>
#include <asm/atomic.h>

#include <soc/realtek/rtd129x_lockapi.h>
#include <soc/realtek/rtk_cpu.h>

static long locakapi_lcounter;
static int locakapi_counter;
static int iemmc_flag;
static int ichip_id;
static int ichip_revision;
static int imagic_num;
static unsigned int debug_nop_count;

struct semaphore lockapi_sema;
spinlock_t lockapi_slock;
//static int lockapi_flags;
static DEFINE_MUTEX(lockapi_mutex);

#if 0 /* defined but not used */
static atomic_t lockapi_atom = ATOMIC_INIT(0);
#endif

static struct device *myproc_lockapi_dev;
static char caller_name1[MAX_LOG_MSG_LEN];
static char caller_name2[MAX_LOG_MSG_LEN];
static char caller_name3[MAX_LOG_MSG_LEN];

static char caller_name1emmc[MAX_LOG_MSG_LEN];
static char caller_name2emmc[MAX_LOG_MSG_LEN];
static char caller_name3emmc[MAX_LOG_MSG_LEN];

static char caller_name1dwc3[MAX_LOG_MSG_LEN];
static char caller_name2dwc3[MAX_LOG_MSG_LEN];
static char caller_name3dwc3[MAX_LOG_MSG_LEN];

static char caller_name1debug[MAX_LOG_MSG_LEN];
static char caller_name2debug[MAX_LOG_MSG_LEN];
static char caller_name3debug[MAX_LOG_MSG_LEN];

/*
 *
 *
 *
 */
int lockapi_trylock( unsigned long * pflags )
{
	int iret;

	iret = LOCKAPI_NO_ERR;

#if defined(EN_SPINLOCK) || defined(EN_SPINLOCK_IRQ)
	if( spin_trylock( &lockapi_slock ) == 0 ) {
		iret = -LOCKAPI_ERR_BUSY;
	}
	else {
		iret = LOCKAPI_NO_ERR;
	}
#endif
#ifdef EN_SEMAPHORE
	if( down_trylock( &lockapi_sema ) == 0 ) {
		iret = LOCKAPI_NO_ERR;
	}
	else {
		iret = -LOCKAPI_ERR_BUSY;
	}
#endif
#ifdef EN_MUTEX
	if( mutex_trylock() == 1 ) {
		iret = LOCKAPI_NO_ERR;
	}
	else {
		iret = -LOCKAPI_ERR_BUSY;
	}
#endif
	return iret;
}

int lockapi_lock( unsigned long * pflags )
{
	int iret;

	iret = LOCKAPI_NO_ERR;

#ifdef EN_SPINLOCK
	spin_lock( &lockapi_slock);
#endif
#ifdef EN_SPINLOCK_IRQ
	spin_lock_irqsave( &lockapi_slock, (*pflags) );
#endif
#ifdef EN_SEMAPHORE
	iret = down_interruptible( &lockapi_sema );
#endif
#ifdef EN_MUTEX
	mutex_lock(&lockapi_mutex);
#endif
	return iret;
}

int lockapi_unlock( unsigned long flags )
{
	int iret;

	iret = LOCKAPI_NO_ERR;

#ifdef EN_SPINLOCK
	spin_unlock( &lockapi_slock);
#endif
#ifdef EN_SPINLOCK_IRQ
	spin_unlock_irqrestore( &lockapi_slock, flags );
#endif
#ifdef EN_SEMAPHORE
	up( &lockapi_sema );
#endif
#ifdef EN_MUTEX
	mutex_lock(&lockapi_mutex);
#endif
	return LOCKAPI_NO_ERR;
}


/*
 *
 *
 *
 */
int _rtk_lockapi_trylock( unsigned long * pflags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_trylock(pflags);

	if( iret != LOCKAPI_NO_ERR )
		return iret;

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name1, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name1, log_msg );
		else
			strcpy( caller_name1, "log name over 128" );
	}
	else {
		strcpy( caller_name1, "no log msg" );
	}

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_trylock);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */


int _rtk_lockapi_lock( unsigned long * pflags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_lock(pflags);

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name2, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name2, log_msg );
		else
			strcpy( caller_name2, "log name over 128" );
	}
	else {
		strcpy( caller_name2, "no log msg" );
	}
	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_lock);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */
int _rtk_lockapi_unlock( unsigned long flags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name3, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name3, log_msg );
		else
			strcpy( caller_name3, "log name over 128" );
	}
	else {
		strcpy( caller_name3, "no log msg" );
	}

	if( locakapi_counter ) {
		locakapi_counter--;
	}
	else {
		printk(KERN_ERR "locakapi:counter %d is zero, unlock twice?\n", locakapi_counter);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1, caller_name2, caller_name3);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1emmc, caller_name2emmc, caller_name3emmc);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1dwc3, caller_name2dwc3, caller_name3dwc3);
	}

	UNLOCK_NOP_DELAY;

	iret = lockapi_unlock(flags);

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_unlock);

/*
 *
 *
 *
 */
int _rtk_lockapi_trylock2( unsigned long * pflags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_trylock(pflags);

	if( iret != LOCKAPI_NO_ERR )
		return iret;

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name1emmc, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name1emmc, log_msg );
		else
			strcpy( caller_name1emmc, "log name over 128" );
	}
	else {
		strcpy( caller_name1emmc, "no log msg" );
	}

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_trylock2);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */


int _rtk_lockapi_lock2( unsigned long * pflags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_lock(pflags);

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;
	iemmc_flag = 1;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name2emmc, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name2emmc, log_msg );
		else
			strcpy( caller_name2emmc, "log name over 128" );
	}
	else {
		strcpy( caller_name2emmc, "no log msg" );
	}
	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_lock2);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */
int _rtk_lockapi_unlock2( unsigned long flags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name3emmc, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name3emmc, log_msg );
		else
			strcpy( caller_name3emmc, "log name over 128" );
	}
	else {
		strcpy( caller_name3emmc, "no log msg" );
	}

	if( locakapi_counter ) {
		locakapi_counter--;
	}
	else {
		printk(KERN_ERR "locakapi2:counter %d is zero, unlock twice?\n", locakapi_counter);
		printk(KERN_ERR "locakapi2:log %s, %s, %s\n", caller_name1, caller_name2, caller_name3);
		printk(KERN_ERR "locakapi2:log %s, %s, %s\n", caller_name1emmc, caller_name2emmc, caller_name3emmc);
		printk(KERN_ERR "locakapi2:log %s, %s, %s\n", caller_name1dwc3, caller_name2dwc3, caller_name3dwc3);
	}
	iemmc_flag = 0;

	UNLOCK_NOP_DELAY;

	iret = lockapi_unlock(flags);

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_unlock2);

/*
 *
 *
 *
 */
int _rtk_lockapi_trylock3( unsigned long * pflags, char * log_msg, int log_line )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_trylock(pflags);

	if( iret != LOCKAPI_NO_ERR )
		return iret;

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name1dwc3, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			sprintf(caller_name1dwc3, "%s %d", log_msg, log_line);
		else
			strcpy( caller_name1dwc3, "log name over 128" );
	}
	else {
		strcpy( caller_name1dwc3, "no log msg" );
	}

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_trylock3);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */


int _rtk_lockapi_lock3( unsigned long * pflags, char * log_msg, int log_line )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = lockapi_lock(pflags);

	LOCK_NOP_DELAY;

	locakapi_counter++;
	locakapi_lcounter++;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name2dwc3, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			sprintf(caller_name2dwc3, "%s %d", log_msg, log_line);
		else
			strcpy( caller_name2dwc3, "log name over 128" );
	}
	else {
		strcpy( caller_name2dwc3, "no log msg" );
	}
	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_lock3);

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */
int _rtk_lockapi_unlock3( unsigned long flags, char * log_msg, int log_line )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int nop_loop;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name3dwc3, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			sprintf(caller_name3dwc3, "%s %d", log_msg, log_line);
		else
			strcpy( caller_name3dwc3, "log name over 128" );
	}
	else {
		strcpy( caller_name3dwc3, "no log msg" );
	}

	if( locakapi_counter ) {
		locakapi_counter--;
	}
	else {
		printk(KERN_ERR "locakapi3:counter %d is zero, unlock twice?\n", locakapi_counter);
		printk(KERN_ERR "locakapi3:log %s, %s, %s\n", caller_name1, caller_name2, caller_name3);
		printk(KERN_ERR "locakapi3:log %s, %s, %s\n", caller_name1emmc, caller_name2emmc, caller_name3emmc);
		printk(KERN_ERR "locakapi3:log %s, %s, %s\n", caller_name1dwc3, caller_name2dwc3, caller_name3dwc3);
	}

	UNLOCK_NOP_DELAY;

	iret = lockapi_unlock(flags);

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}
EXPORT_SYMBOL_GPL(_rtk_lockapi_unlock3);

/*
 *
 *
 *
 */
static int rtk_lockapi_init(void)
{
	ichip_id = 0;//get_rtd129x_cpu_id();
	ichip_revision = get_rtd129x_cpu_revision();
	locakapi_counter = 0;
	locakapi_lcounter = 0;
	iemmc_flag = 0;
	memset( caller_name1, 0, MAX_LOG_MSG_LEN );
	memset( caller_name2, 0, MAX_LOG_MSG_LEN );
	memset( caller_name3, 0, MAX_LOG_MSG_LEN );
	memset( caller_name1emmc, 0, MAX_LOG_MSG_LEN );
	memset( caller_name2emmc, 0, MAX_LOG_MSG_LEN );
	memset( caller_name3emmc, 0, MAX_LOG_MSG_LEN );
	memset( caller_name1dwc3, 0, MAX_LOG_MSG_LEN );
	memset( caller_name2dwc3, 0, MAX_LOG_MSG_LEN );
	memset( caller_name3dwc3, 0, MAX_LOG_MSG_LEN );
	memset( caller_name1debug, 0, MAX_LOG_MSG_LEN );
	memset( caller_name2debug, 0, MAX_LOG_MSG_LEN );
	memset( caller_name3debug, 0, MAX_LOG_MSG_LEN );
	strcpy( caller_name1, "clear" );
	strcpy( caller_name2, "clear" );
	strcpy( caller_name3, "clear" );
	strcpy( caller_name1emmc, "clear" );
	strcpy( caller_name2emmc, "clear" );
	strcpy( caller_name3emmc, "clear" );
	strcpy( caller_name1dwc3, "clear" );
	strcpy( caller_name2dwc3, "clear" );
	strcpy( caller_name3dwc3, "clear" );
	strcpy( caller_name1debug, "clear" );
	strcpy( caller_name2debug, "clear" );
	strcpy( caller_name3debug, "clear" );
	imagic_num = LOCKAPI_MAGICNUM;

	printk(KERN_ERR "****** %s %d, chip: id=0x%08x, revision=0x%08x\n", __FUNCTION__, __LINE__, ichip_id, ichip_revision);

	// ID: 0x9801a200
	// Rev.: 0x9801a204
	if( ichip_revision >= (int)RTD129x_CHIP_REVISION_B00 )
	{
		imagic_num = LOCKAPI_BY_PASS;
		printk(KERN_ERR "****** %s %d, bypass mode\n", __FUNCTION__, __LINE__);
	}


	sema_init( &lockapi_sema, 1 );
	spin_lock_init( &lockapi_slock );

	return 0;
}
arch_initcall(rtk_lockapi_init);

int debug_lockapi_lock( unsigned long * pflags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int looptest;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	iret = LOCKAPI_NO_ERR;//lockapi_lock(pflags);

	locakapi_counter++;
	locakapi_lcounter++;

	looptest = debug_nop_count;
	while(looptest--) {
		asm volatile("nop" : : : );
	}

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name2debug, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name2debug, log_msg );
		else
			strcpy( caller_name2debug, "log name over 128" );
	}
	else {
		strcpy( caller_name2debug, "no log msg" );
	}
	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}

/*
 * Input 1: please use __FUNCTION__ or others readable log mesage
 *
 *
 */
int debug_lockapi_unlock( unsigned long flags, char * log_msg )
{
#ifdef LOCKAPI_EN
	int iret;
	int ilen;
	unsigned int looptest;

	if( imagic_num == LOCKAPI_BY_PASS )
		return LOCKAPI_NO_ERR;

	if( imagic_num != LOCKAPI_MAGICNUM )
		return -LOCKAPI_ERR_DRV_NOT_READY;

	if( log_msg ) {
		ilen = strlen(log_msg);
		memset( caller_name3debug, 0, MAX_LOG_MSG_LEN );
		if( ilen < MAX_LOG_MSG_LEN )
			strcpy( caller_name3debug, log_msg );
		else
			strcpy( caller_name3debug, "log name over 128" );
	}
	else {
		strcpy( caller_name3debug, "no log msg" );
	}

	if( locakapi_counter ) {
		locakapi_counter--;
	}
	else {
		printk(KERN_ERR "locakapi:counter %d is zero, unlock twice?\n", locakapi_counter);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1debug, caller_name2debug, caller_name3debug);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1emmc, caller_name2emmc, caller_name3emmc);
		printk(KERN_ERR "locakapi:log %s, %s, %s\n", caller_name1dwc3, caller_name2dwc3, caller_name3dwc3);
	}

	looptest = debug_nop_count;
	while(looptest--) {
		asm volatile("nop" : : : );
	}

	iret = LOCKAPI_NO_ERR;//lockapi_unlock(flags);

	return iret;
#else
	return LOCKAPI_NO_ERR;
#endif
}


/*
 *
 *
 *
 */
void debug_lockapi_entry( int mode, unsigned int refloop, unsigned int nop_loop )
{
	unsigned long start_jiffies;
	unsigned long end_jiffies;
	unsigned long flags;
	unsigned int looptest;

	debug_nop_count = nop_loop;

	start_jiffies = end_jiffies = 0;

	if( mode == 0 ) {
		looptest = refloop;
		printk(KERN_ERR "start\n");
		start_jiffies = jiffies;
		while( looptest-- ) {
			debug_lockapi_lock(&flags,"_");
		}
		end_jiffies = jiffies;
		printk(KERN_ERR "end, %lud, %lud in loop %d, nop loop %d\n", start_jiffies, end_jiffies, refloop, debug_nop_count);
	}
	if( mode == 1 ) {
		looptest = refloop;
		locakapi_counter = looptest<<1;
		printk(KERN_ERR "start\n");
		start_jiffies = jiffies;
		while( looptest-- ) {
			debug_lockapi_unlock(flags,"_");
		}
		end_jiffies = jiffies;
		printk(KERN_ERR "end, %lud, %lud in loop %d, nop loop %d\n", start_jiffies, end_jiffies, refloop, debug_nop_count);
	}
	if( mode == 2 ) {
		looptest = refloop;
		printk(KERN_ERR "start\n");
		start_jiffies = jiffies;
		while( looptest-- ) {
			debug_lockapi_lock(&flags,"_");
			debug_lockapi_unlock(flags,"_");
		}
		end_jiffies = jiffies;
		printk(KERN_ERR "end, %lud, %lud in loop %d, nop loop %d\n", start_jiffies, end_jiffies, refloop, debug_nop_count);
	}
}
/*
 *
 *
 *
 */
void lockapi_show_status( void )
{
	printk(KERN_ERR "\n--------------------------------------------------------------------------\n");
	printk(KERN_ERR "****** chip id 0x%08x\n", ichip_id);
	printk(KERN_ERR "****** chip rev. 0x%08x\n", ichip_revision);
	printk(KERN_ERR "****** magic_num 0x%08x(%s)\n", imagic_num, (imagic_num == LOCKAPI_BY_PASS) ? "bypass" : "--" );
	printk(KERN_ERR "****** iemmc_flag %d\n", iemmc_flag);
	printk(KERN_ERR "****** locakapi_counter %d\n", locakapi_counter);
	printk(KERN_ERR "****** locakapi_lcounter %ld\n", locakapi_lcounter);
	printk(KERN_ERR "****** caller_name %s, %s, %s\n", caller_name1, caller_name2, caller_name3);
	printk(KERN_ERR "****** caller_name %s, %s, %s\n", caller_name1emmc, caller_name2emmc, caller_name3emmc);
	printk(KERN_ERR "****** caller_name %s, %s, %s\n", caller_name1dwc3, caller_name2dwc3, caller_name3dwc3);
#if defined(EN_SPINLOCK)
	printk(KERN_ERR "****** EN_SPINLOCK defined\n");
#endif
#if defined(EN_SPINLOCK_IRQ)
	printk(KERN_ERR "****** EN_SPINLOCK_IRQ defined\n");
#endif
#if defined(EN_SEMAPHORE)
	printk(KERN_ERR "****** EN_SEMAPHORE defined\n");
#endif
#if defined(EN_MUTEX)
	printk(KERN_ERR "****** EN_MUTEX defined\n");
#endif
#if !defined(LOCKAPI_EN)
	printk(KERN_ERR "****** Lock api is not enabled\n");
#endif
}
EXPORT_SYMBOL_GPL(lockapi_show_status);

/*
 * any read request will free coherent memory, eg.
 * cat /dev/rtk_lockapi
 *
 */
static ssize_t
myproc_lockapi_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	lockapi_show_status();
	return 0;
}

/*
 * any write request will alloc coherent memory, eg.
 * echo xxxxxxx > /dev/rtk_lockapi
 *
 */
static ssize_t
myproc_lockapi_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	char input[128] = {0};
	char * ptr_input;
	int str_len;
	int reminder_str_len;
	int ret_val;
	unsigned int input_nop_count;
	unsigned int test_loop;
	int test_mode;

	ptr_input = input;
	str_len = count-1;
	reminder_str_len = str_len;

	if( ( 1 < count ) && ( count < 128 ) ) {
		ret_val = copy_from_user(input, buf, (count-1));
	}
	else {
		printk(KERN_ERR "****** %s %03d, invalid count(%d)\n", __FUNCTION__, __LINE__, (int)count);
		return count;
	}
	printk(KERN_ERR "****** %s %03d, input = %s\n", __FUNCTION__, __LINE__, input);
	printk(KERN_ERR "****** %s %03d -----------------------------------------\n", __FUNCTION__, __LINE__);

	test_mode = -1;
	input_nop_count = 0;
	test_loop = 0;

	if( strncmp( ptr_input, "lock", 4 ) == 0 ) {
		if( str_len > 5 ) {
			ptr_input += 5;
			reminder_str_len -= 5;
		}
		test_mode = 0;
	}
	else if( strncmp( ptr_input, "unlock", 6 ) == 0 ) {
		if( str_len > 7 ) {
			ptr_input += 7;
			reminder_str_len -= 7;
		}
		test_mode = 1;
	}
	else if( strncmp( ptr_input, "lockunlock", 10 ) == 0 ) {
		if( str_len > 11 ) {
			ptr_input += 11;
			reminder_str_len -= 11;
		}
		test_mode = 2;
	}

	if( reminder_str_len ) {
		if( strncmp( ptr_input, "A", 1 ) == 0 ) {
			test_loop = 10000000;
			ptr_input++;
			reminder_str_len--;
		}
		else if( strncmp( ptr_input, "B", 1 ) == 0 ) {
			test_loop = 20000000;
			ptr_input++;
			reminder_str_len--;
		}
		else if( strncmp( ptr_input, "C", 1 ) == 0 ) {
			test_loop = 30000000;
			ptr_input++;
			reminder_str_len--;
		}
	}

	if( reminder_str_len ) {
		input_nop_count = simple_strtol(ptr_input, &ptr_input + reminder_str_len, 10);
		input_nop_count = input_nop_count * 10;
	}
	printk(KERN_ERR "****** %s %03d, mode %d, test_loop=%d, nop count %d\n", __FUNCTION__, __LINE__, test_mode, test_loop, input_nop_count);

	debug_lockapi_entry(test_mode, test_loop, input_nop_count);

	return count;
}

static const struct file_operations myproc_lockapi_fops = {
	.owner =    THIS_MODULE,
	.read  =    myproc_lockapi_read,
	.write =    myproc_lockapi_write,
};

static struct miscdevice myproc_lockapi_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "rtk_lockapi",
	.fops = &myproc_lockapi_fops,
};

static int __init proc_lockapi_init(void)
{
	int ret = 0;

	ret = misc_register(&myproc_lockapi_misc);
	if (unlikely(ret)) {
		pr_err("failed to register cma test misc device!\n");
		return ret;
	}
	myproc_lockapi_dev = myproc_lockapi_misc.this_device;
	myproc_lockapi_dev->coherent_dma_mask = ~0;
	_dev_info(myproc_lockapi_dev, "registered.\n");

	return ret;
}
module_init(proc_lockapi_init);

static void __exit proc_lockapi_exit(void)
{
	misc_deregister(&myproc_lockapi_misc);
}
module_exit(proc_lockapi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jinn <jinn.cheng@reaktek.com>");
MODULE_DESCRIPTION("kernel module to help the debug of lockapi");
MODULE_ALIAS("PROC LOCKAPI");
