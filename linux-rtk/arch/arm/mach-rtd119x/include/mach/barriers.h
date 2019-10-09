/*
 * Realtek memory barrier header.
 *
 */

#ifndef __MACH_BARRIERS_H
#define __MACH_BARRIERS_H

extern void rtk_bus_sync(void);

#define rmb()		dsb()
#define wmb()		do { dmb(); rtk_bus_sync(); } while (0)
#define mb()		wmb()

#endif	/* __MACH_BARRIERS_H */
