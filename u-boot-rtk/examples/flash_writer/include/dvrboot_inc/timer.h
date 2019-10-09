//=================================================================================================
// Copyright (c) 2013 Realtek Semiconductor Corp. All Rights Reserved.
//
// Filename: timer.h
// Abstract:
//   Timer registers & API definition
//
// History:
//	 2013-04				louisyang			Modify for phoenix
//=================================================================================================

#ifndef _TIMER_H_
#define _TIMER_H_

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

//=================================================================================================
#ifndef FPGA
#define TIMERINFO_BASE_CLOCK				(50000000)	//T = 1/50M = 20ns
#define TIMERINFO_BASE_UNIT					20			// 20ns
#else
//#define TIMERINFO_BASE_CLOCK				(27000000)	//T = 1/27M = 37ns
//#define TIMERINFO_BASE_UNIT					37			// 37ns
#define TIMERINFO_BASE_CLOCK				(33000000)	//T = 1/33M = 30ns
#define TIMERINFO_BASE_UNIT					30			// 30ns
#endif
#define TIMERINFO_SEC                       1000000000/TIMERINFO_BASE_UNIT
#define TIMERINFO_MSEC                      1000000/TIMERINFO_BASE_UNIT
#define TIMERINFO_USEC                      1000/TIMERINFO_BASE_UNIT

//=================================================================================================
//Related Register Information of Timer
//in phoenix design, we use tc0 swc timer as default
#define TIMERINFO_INTERRUPT_ENABLE			0x80000000
#define TIMERINFO_INTERRUPT_DISABLE			0x00000000
#define TIMERINFO_TIMER_ENABLE				0xC0000000
#define TIMERINFO_TIMER_DISABLE				0x00000000


#define TIMERID_0    0
#define TIMERID_1    1
#define TIMERID_2    2
//=================================================================================================
UINT32 InitTimer(UINT32 timerID, unsigned int dwInit);
void mdelay(unsigned int dwMiniSecond);
void udelay(unsigned int dwMicroSecond);
//=================================================================================================
#endif
