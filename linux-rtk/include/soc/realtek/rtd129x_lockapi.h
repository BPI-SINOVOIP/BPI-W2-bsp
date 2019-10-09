/*
 * rtd129x_lockapi.h
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#ifndef _RTD129x_LOCKAPI_H_
#define _RTD129x_LOCKAPI_H_

//#define EN_SPINLOCK
#define EN_SPINLOCK_IRQ
//#define EN_SEMAPHORE
//#define EN_MUTEX

#define LINE2STR_DETAIL(x) #x
#define LINE2STR(x) LINE2STR_DETAIL(x)
#define _AT_(X) __FILE__ " " LINE2STR(X)
#define _at_(X) X " " LINE2STR(__LINE__)

#if defined(EN_SPINLOCK) || defined(EN_SPINLOCK_IRQ) || defined(EN_SEMAPHORE) || defined(EN_MUTEX)
#ifdef CONFIG_ARCH_RTD129x
    #define LOCKAPI_EN
    #define rtk_lockapi_trylock(X,Y)         _rtk_lockapi_trylock(&X,Y)
    #define rtk_lockapi_lock(X,Y)            _rtk_lockapi_lock(&X,Y)
    #define rtk_lockapi_unlock(X,Y)          _rtk_lockapi_unlock(X,Y)

    #define rtk_lockapi_trylock2(X,Y)        _rtk_lockapi_trylock2(&X,Y)
    #define rtk_lockapi_lock2(X,Y)           _rtk_lockapi_lock2(&X,Y)
    #define rtk_lockapi_unlock2(X,Y)         _rtk_lockapi_unlock2(X,Y)

    #define rtk_lockapi_trylock3(X,Y,Z)        _rtk_lockapi_trylock3(&X,Y,Z)
    #define rtk_lockapi_lock3(X,Y,Z)         _rtk_lockapi_lock3(&X,Y,Z)
    #define rtk_lockapi_unlock3(X,Y,Z)       _rtk_lockapi_unlock3(X,Y,Z)
#else
    #define rtk_lockapi_trylock(X,Y)
    #define rtk_lockapi_lock(X,Y)
    #define rtk_lockapi_unlock(X,Y)

    #define rtk_lockapi_trylock2(X,Y)
    #define rtk_lockapi_lock2(X,Y)
    #define rtk_lockapi_unlock2(X,Y)

    #define rtk_lockapi_trylock3(X,Y,Z)
    #define rtk_lockapi_lock3(X,Y,Z)
    #define rtk_lockapi_unlock3(X,Y,Z)
#endif /* CONFIG_ARCH_RTD129x */
#else
    #define rtk_lockapi_trylock(X,Y)
    #define rtk_lockapi_lock(X,Y)
    #define rtk_lockapi_unlock(X,Y)

    #define rtk_lockapi_trylock2(X,Y)
    #define rtk_lockapi_lock2(X,Y)
    #define rtk_lockapi_unlock2(X,Y)

    #define rtk_lockapi_trylock3(X,Y,Z)
    #define rtk_lockapi_lock3(X,Y,Z)
    #define rtk_lockapi_unlock3(X,Y,Z)
#endif

#define LOCKAPI_MAGICNUM (0xdeadbeef)
#define LOCKAPI_BY_PASS (0xbeefdead)
#define MAX_LOG_MSG_LEN  (64)

#define LOCK_NOP_DELAY_CNT (30)
#define UNLOCK_NOP_DELAY_CNT (30)

#define LOCK_NOP_DELAY \
{ \
	nop_loop = LOCK_NOP_DELAY_CNT; \
	while(nop_loop--){ \
		asm volatile("nop" : : : ); \
	} \
}

#define UNLOCK_NOP_DELAY \
{ \
	nop_loop = UNLOCK_NOP_DELAY_CNT; \
	while(nop_loop--){ \
		asm volatile("nop" : : : ); \
	} \
}

enum lockapi_errortype {
	LOCKAPI_NO_ERR = 0,
	LOCKAPI_ERR_BUSY = 1,
	LOCKAPI_ERR_TIMEOUT = 2,
	LOCKAPI_ERR_RELOCK = 3,
	LOCKAPI_ERR_REUNLOCK = 4,
	LOCKAPI_ERR_DRV_NOT_READY = 99,
	LOCKAPI_ERR_UNKNOW = 100,
};

void lockapi_show_status( void );

int _rtk_lockapi_trylock( unsigned long * pflags, char * log_msg );
int _rtk_lockapi_lock( unsigned long * pflags, char * log_msg );
int _rtk_lockapi_unlock( unsigned long flags, char * log_msg );

int _rtk_lockapi_trylock2( unsigned long * pflags, char * log_msg );
int _rtk_lockapi_lock2( unsigned long * pflags, char * log_msg );
int _rtk_lockapi_unlock2( unsigned long flags, char * log_msg );

int _rtk_lockapi_trylock3( unsigned long * pflags, char * log_msg, int log_line );
int _rtk_lockapi_lock3( unsigned long * pflags, char * log_msg, int log_line );
int _rtk_lockapi_unlock3( unsigned long flags, char * log_msg, int log_line );

#endif //_RTD129x_LOCKAPI_H_
