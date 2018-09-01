#ifndef _TIMER_H_
#include <sysdefs.h>
#include "dvrboot_inc/timer.h"
#include "dvrboot_inc/mis_reg.h"
#endif

//#define TIMER_COUNTER_MODE
//=================================================================================================
// Name: InitTimer
// Description: Initial Register for Timer
// Input: 
//   - timerID : timer id
//   - dwInit : init time
//
// Output: 
//   - -1 : init fail, incorrect timer id
//   - 1 : successful
//=================================================================================================
UINT32 InitTimer(unsigned int timerID, unsigned int dwInit)
{
    //TimerID for timer 0 / 1 only since timer 2 is SWC timer
    if (timerID >= 2)
        return -1;

	//Set The Initial Value
	REG32(MIS_TC0TVR+timerID*4) = dwInit;

	//Disable Interrupt
	REG32(MIS_TC0ICR+timerID*4) = TIMERINFO_INTERRUPT_DISABLE;
	
	//Disable Timer
	REG32(MIS_TC0CR+timerID*4) = TIMERINFO_TIMER_DISABLE;

    #ifdef TIMER_COUNTER_MODE
	//Enable Timer Mode
	REG32(MIS_TC0CR+timerID*4) = TIMERINFO_INTERRUPT_ENABLE;
    #else
	// Clear Interrupt Pending (must after enable)
	REG32(MIS_UMSK_ISR) = ((timerID+1)<<6);
	//Enable Timer Mode
	REG32(MIS_TC0CR+timerID*4) = TIMERINFO_TIMER_ENABLE;
    #endif
    return 1;
}

UINT32 DisableTimer(UINT32 timerID)
{
    //TimerID for timer 0 / 1 only since timer 2 is SWC timer
    if (timerID >= 2) return -1;

    //timer0
	//Disable Interrupt
	REG32(MIS_TC0ICR+timerID*4) = TIMERINFO_INTERRUPT_DISABLE;
	
	//Disable Timer
	REG32(MIS_TC0CR+timerID*4) = TIMERINFO_TIMER_DISABLE;   
    
    return 1;
}

bool SystemTimeout(UINT32 timerID, UINT32 limit)
{
	bool	bIoStatus = FALSE;

    //TimerID for timer 0 / 1 only since timer 2 is SWC timer
    if (timerID >= 2) return FALSE;

    #ifdef TIMER_COUNTER_MODE
	if(REG32(MIS_TC0CVR+timerID*4) > limit)
        return bIoStatus = TRUE;
    else
        return FALSE;
    
    #else
	if(REG32(MIS_UMSK_ISR) & ((timerID+1)<<6))
	{
		bIoStatus = TRUE;
	}
    #endif

	return bIoStatus;
}


//=================================================================================================
// Name: mdelay
// Description: Delay in ms
// Input: 
//	- timerID : timer id
//   - dwMiniSecond : delay peroid in minisecond
//
// Output: None
//=================================================================================================
void mdelay(unsigned int dwMiniSecond)
{
    UINT32 delayTime=0;
#ifdef ENV_SIMULATION
	//Initial Timer 7
	delayTime = 1*TIMERINFO_MSEC;
	InitTimer(TIMERID_0, delayTime);
#else
	//Initial Timer 7
	delayTime = dwMiniSecond*TIMERINFO_MSEC;
	InitTimer(TIMERID_0, delayTime);
#endif
	//Wait for Interrupt Pending Status
	while(SystemTimeout(TIMERID_0, delayTime) == FALSE);
}
void udelay(unsigned int dwMicroSecond)
{
    UINT32 delayTime=0;
#ifdef ENV_SIMULATION
    delayTime = 1*TIMERINFO_USEC;
	InitTimer(TIMERID_0, delayTime);
#else
    delayTime = dwMicroSecond*TIMERINFO_USEC;
	InitTimer(TIMERID_0, delayTime);
#endif
    //Wait for Interrupt Pending Status
    while(SystemTimeout(TIMERID_0, delayTime) == FALSE);	
}
