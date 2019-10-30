#include "cache.h"
#include "sysdefs.h"
#include "dvrboot_inc/mis_reg.h"
#include "dvrboot_inc/sys_reg.h"
#include "dvrboot_inc/util.h"
#include "dvrboot_inc/mcp.h"
#include "dvrboot_inc/string.h"
#include "dvrboot_inc/timer.h"

void __flush_cache_all(void);
void __invalidate_tlb_all(void);

static inline int log_2_n_round_up(unsigned int n)
{
	int log2n = -1;
	unsigned int temp = n;

	while (temp) {
		log2n++;
		temp >>= 1;
	}

	if (n & (n - 1))
		return log2n + 1; /* not power of 2 - round up */
	else
		return log2n; /* power of 2 */
}

static inline unsigned int current_el(void)
{
    unsigned int el;
    asm volatile("mrs %0, CurrentEL" : "=r" (el) : : "cc");
    return el >> 2;
}

static inline void set_sctlr(unsigned int val)
{
    unsigned int el;

    el = current_el();
    if (el == 1)
        asm volatile("msr sctlr_el1, %0" : : "r" (val) : "cc");
    else if (el == 2)
        asm volatile("msr sctlr_el2, %0" : : "r" (val) : "cc");
    else
        asm volatile("msr sctlr_el3, %0" : : "r" (val) : "cc");

    asm volatile("isb");
}

static inline unsigned int get_sctlr(void)
{
    unsigned int el, val;
    el = current_el();

    if (el == 1)
        asm volatile("mrs %0, sctlr_el1" : "=r" (val) : : "cc");
    else if (el == 2)
        asm volatile("mrs %0, sctlr_el2" : "=r" (val) : : "cc");
    else
        asm volatile("mrs %0, sctlr_el3" : "=r" (val) : : "cc");
    return val;
}

void disable_dcache(void)
{
    u32 sctlr;
    sctlr = get_sctlr();

    /* if cache isn't enabled no need to disable */
    if (!(sctlr & SCTLR_EL3_C) && !(sctlr & SCTLR_EL3_M))
        return;

    set_sctlr(sctlr & ~(SCTLR_EL3_C|SCTLR_EL3_M));
    __flush_cache_all();
    __invalidate_tlb_all();
}

