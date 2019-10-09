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

static void set_csselr(unsigned int level, unsigned int type)
{	UINT32 csselr = level << 1 | type;

	/* Write to Cache Size Selection Register(CSSELR) */
	//asm volatile ("mcr p15, 2, %0, c0, c0, 0" : : "r" (csselr));
     asm volatile("msr csselr_el1, %x0" : : "r" (csselr));
}

static unsigned int get_ccsidr(void)
{
	unsigned int ccsidr;

	/* Read current CP15 Cache Size ID Register */
	//asm volatile ("mrc p15, 1, %0, c0, c0, 0" : "=r" (ccsidr));
    asm volatile("mrs %x0, ccsidr_el1" : "=r" (ccsidr));
	return ccsidr;
}

static unsigned int get_clidr(void)
{
	unsigned int clidr;

	/* Read current CP15 Cache Level ID Register */
	//asm volatile ("mrc p15,1,%0,c0,c0,1" : "=r" (clidr));
    asm volatile ("mrs     %x0, clidr_el1" : "=r" (clidr));
	return clidr;
}

static void v7_clean_inval_dcache_level_setway(unsigned int level, unsigned int num_sets,
					       unsigned int num_ways, unsigned int way_shift,
					       unsigned int log2_line_len)
{
	int way, set, setway;

	/*
	 * For optimal assembly code:
	 *	a. count down
	 *	b. have bigger loop inside
	 */
	for (way = num_ways - 1; way >= 0 ; way--) {
		for (set = num_sets - 1; set >= 0; set--) {
			setway = (level << 1) | (set << log2_line_len) |
				 (way << way_shift);
			/*
			 * Clean & Invalidate data/unified
			 * cache line by set/way
			 */
			/*asm volatile ("	mcr p15, 0, %0, c7, c14, 2"
					: : "r" (setway));*/
            asm volatile (" DC CIVAC, %0" : : "r" (setway));
		}
	}
	/* DSB to make sure the operation is complete */
	CP15DSB;
}

static void v7_inval_dcache_level_setway(unsigned int level, unsigned int num_sets,
					 unsigned int num_ways, unsigned int way_shift,
					 unsigned int log2_line_len)
{
	int way, set, setway;

	/*
	 * For optimal assembly code:
	 *	a. count down
	 *	b. have bigger loop inside
	 */
	for (way = num_ways - 1; way >= 0 ; way--) {
		for (set = num_sets - 1; set >= 0; set--) {
			setway = (level << 1) | (set << log2_line_len) |
				 (way << way_shift);
			/* Invalidate data/unified cache line by set/way */
			/*asm volatile ("	mcr p15, 0, %0, c7, c6, 2"
					: : "r" (setway));*/
            asm volatile (" DC ISW, %0" : : "r" (setway));
		}
	}
	/* DSB to make sure the operation is complete */
	CP15DSB;
}

static void v7_maint_dcache_level_setway(unsigned int level, unsigned int operation)
{
	unsigned int ccsidr;
	unsigned int num_sets, num_ways, log2_line_len, log2_num_ways;
	unsigned int way_shift;

	set_csselr(level, ARMV7_CSSELR_IND_DATA_UNIFIED);

	ccsidr = get_ccsidr();

	log2_line_len = ((ccsidr & CCSIDR_LINE_SIZE_MASK) >>
				CCSIDR_LINE_SIZE_OFFSET) + 2;
	/* Converting from words to bytes */
	log2_line_len += 2;

	num_ways  = ((ccsidr & CCSIDR_ASSOCIATIVITY_MASK) >>
			CCSIDR_ASSOCIATIVITY_OFFSET) + 1;
	num_sets  = ((ccsidr & CCSIDR_NUM_SETS_MASK) >>
			CCSIDR_NUM_SETS_OFFSET) + 1;
	/*
	 * According to ARMv7 ARM number of sets and number of ways need
	 * not be a power of 2
	 */
	log2_num_ways = log_2_n_round_up(num_ways);

	way_shift = (32 - log2_num_ways);
	if (operation == ARMV7_DCACHE_INVAL_ALL) {
		v7_inval_dcache_level_setway(level, num_sets, num_ways,
				      way_shift, log2_line_len);
	}
	else if (operation == ARMV7_DCACHE_CLEAN_INVAL_ALL) {
		v7_clean_inval_dcache_level_setway(level, num_sets, num_ways,
						   way_shift, log2_line_len);
	}
}

void v7_maint_dcache_all(unsigned int operation)
{
	unsigned int level, cache_type, level_start_bit = 0;

	unsigned int clidr = get_clidr();

	for (level = 0; level < 7; level++) {
		cache_type = (clidr >> level_start_bit) & 0x7;
		if ((cache_type == ARMV7_CLIDR_CTYPE_DATA_ONLY) ||
		    (cache_type == ARMV7_CLIDR_CTYPE_INSTRUCTION_DATA) ||
		    (cache_type == ARMV7_CLIDR_CTYPE_UNIFIED))
			v7_maint_dcache_level_setway(level, operation);
		level_start_bit += 3;
	}
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
    if (!(sctlr & CR_C) && !(sctlr & CR_M))
        return;

    set_sctlr(sctlr & ~(CR_C|CR_M));
    __flush_cache_all();
    __invalidate_tlb_all();
}

