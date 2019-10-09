/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/system.h>
#include <asm/armv8/mmu.h>

#ifdef CONFIG_BSP_REALTEK
#include <asm/arch/system.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_SYS_DCACHE_OFF
void set_pgtable_section(u64 *page_table, u64 index, u64 section,
			 u64 memory_type)
{
	u64 value;

	value = section | PMD_TYPE_SECT | PMD_SECT_AF;
	value |= PMD_ATTRINDX(memory_type);
	page_table[index] = value;
}

/* to activate the MMU we need to set up virtual memory */
static void mmu_setup(void)
{
	u64 i, j;
	unsigned int el;
	bd_t *bd = gd->bd;
	u64 *page_table = (u64 *)gd->arch.tlb_addr;

	/* Setup an identity-mapping for all spaces */
	for (i = 0; i < (PGTABLE_SIZE >> 3); i++) {
		set_pgtable_section(page_table, i, i << SECTION_SHIFT,
				    MT_DEVICE_NGNRNE);
	}

	/* Setup an identity-mapping for all RAM space */
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		ulong start = bd->bi_dram[i].start;
		ulong end = bd->bi_dram[i].start + bd->bi_dram[i].size;
		for (j = start >> SECTION_SHIFT;
		     j < end >> SECTION_SHIFT; j++) {
			set_pgtable_section(page_table, j, j << SECTION_SHIFT,
					    MT_NORMAL);
		}
	}

#ifdef CONFIG_BSP_REALTEK	// map RBUS region
	for (i = RBUS_ADDR >> SECTION_SHIFT ; i <= RBUS_END >> SECTION_SHIFT ; i++ )
		set_pgtable_section(page_table, i, i << SECTION_SHIFT, MT_DEVICE_NGNRE);
#endif

	/* load TTBR0 */
	el = current_el();
	if (el == 1) {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL1_IPS_BITS,
				  MEMORY_ATTRIBUTES);
	} else if (el == 2) {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL2_IPS_BITS,
				  MEMORY_ATTRIBUTES);
	} else {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL3_IPS_BITS,
				  MEMORY_ATTRIBUTES);
	}
	/* enable the mmu */
	set_sctlr(get_sctlr() | CR_M);
}

void mmu_set_region(u64 start, u64 size, u64 memory_type)
{
	u64 i;
	u64 *page_table = (u64 *)gd->arch.tlb_addr;

	for (i = start >> SECTION_SHIFT ; i <= (start + size) >> SECTION_SHIFT ; i++ )
		set_pgtable_section(page_table, i, i << SECTION_SHIFT, memory_type);

	flush_dcache_all();
	__asm_invalidate_tlb_all();
}

/*
 * Performs a invalidation of the entire data cache at all levels
 */
void invalidate_dcache_all(void)
{
	__asm_invalidate_dcache_all();
}

/*
 * Performs a clean & invalidation of the entire data cache at all levels.
 * This function needs to be inline to avoid using stack.
 * __asm_flush_l3_cache return status of timeout
 */
inline void flush_dcache_all(void)
{
	int ret;

	__asm_flush_dcache_all();
	ret = __asm_flush_l3_cache();
	if (ret)
		printf("flushing dcache returns 0x%x\n", ret);
	else
		printf("flushing dcache successfully.\n");
}

/*
 * Invalidates range in all levels of D-cache/unified cache
 */
void invalidate_dcache_range(unsigned long start, unsigned long stop)
{
	//debug("%s, start %lx end %lx\n", __func__, start, stop); 
	__asm_flush_dcache_range(start, stop);
}

/*
 * Flush range(clean & invalidate) from all levels of D-cache/unified cache
 */
void flush_dcache_range(unsigned long start, unsigned long stop)
{
	//debug("%s, start %lx end %lx\n", __func__, start, stop); 
	__asm_flush_dcache_range(start, stop);
}

void dcache_enable(void)
{
	/* The data cache is not active unless the mmu is enabled */
	if (!(get_sctlr() & CR_M)) {
		invalidate_dcache_all();
		__asm_invalidate_tlb_all();
		mmu_setup();
	}

	set_sctlr(get_sctlr() | CR_C);
}

void dcache_disable(void)
{
	uint32_t sctlr;

	sctlr = get_sctlr();

	/* if cache isn't enabled no need to disable */
	if (!(sctlr & CR_C) && !(sctlr & CR_M))
		return;

	set_sctlr(sctlr & ~(CR_C|CR_M));

	flush_dcache_all();
	__asm_invalidate_tlb_all();
}

int dcache_status(void)
{
	return (get_sctlr() & CR_C) != 0;
}

#else	/* CONFIG_SYS_DCACHE_OFF */

void invalidate_dcache_all(void)
{
}

void flush_dcache_all(void)
{
}

void invalidate_dcache_range(unsigned long start, unsigned long stop)
{
}

void flush_dcache_range(unsigned long start, unsigned long stop)
{
}

void dcache_enable(void)
{
}

void dcache_disable(void)
{
}

int dcache_status(void)
{
	return 0;
}

#endif	/* CONFIG_SYS_DCACHE_OFF */

#ifndef CONFIG_SYS_ICACHE_OFF

void icache_enable(void)
{
	__asm_invalidate_icache_all();
	set_sctlr(get_sctlr() | CR_I);
}

void icache_disable(void)
{
	set_sctlr(get_sctlr() & ~CR_I);
}

int icache_status(void)
{
	return (get_sctlr() & CR_I) != 0;
}

void invalidate_icache_all(void)
{
	__asm_invalidate_icache_all();
}

#else	/* CONFIG_SYS_ICACHE_OFF */

void icache_enable(void)
{
}

void icache_disable(void)
{
}

int icache_status(void)
{
	return 0;
}

void invalidate_icache_all(void)
{
}

#endif	/* CONFIG_SYS_ICACHE_OFF */

/*
 * Enable dCache & iCache, whether cache is actually enabled
 * depend on CONFIG_SYS_DCACHE_OFF and CONFIG_SYS_ICACHE_OFF
 */
void __weak enable_caches(void)
{
	icache_enable();
	dcache_enable();
}

/*
 * Flush range from all levels of d-cache/unified-cache
 */
void flush_cache(unsigned long start, unsigned long size)
{
	flush_dcache_range(start, start + size);
}

#ifdef CONFIG_CMD_CACHETEST
void dcache_disable_no_flush(void)
{
	uint32_t sctlr;

	sctlr = get_sctlr();

	/* if cache isn't enabled no need to disable */
	if (!(sctlr & CR_C))
		return;

	set_sctlr(sctlr & ~(CR_C|CR_M));
}

static void mmu_setup_wt(void) // To set up cache as writethrough
{
	u64 i, j;
	unsigned int el;
	bd_t *bd = gd->bd;
	u64 *page_table = (u64 *)gd->arch.tlb_addr;

	/* Setup an identity-mapping for all spaces */
	for (i = 0; i < (PGTABLE_SIZE >> 3); i++) {
		set_pgtable_section(page_table, i, i << SECTION_SHIFT,
				    MT_DEVICE_NGNRNE);
	}

	/* Setup an identity-mapping for all RAM space */
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		ulong start = bd->bi_dram[i].start;
		ulong end = bd->bi_dram[i].start + bd->bi_dram[i].size;
		for (j = start >> SECTION_SHIFT;
		     j < end >> SECTION_SHIFT; j++) {
			set_pgtable_section(page_table, j, j << SECTION_SHIFT,
					    MT_NORMAL);
		}
	}

#ifdef CONFIG_BSP_REALTEK	// map RBUS region
	for (i = RBUS_ADDR >> SECTION_SHIFT ; i <= RBUS_END >> SECTION_SHIFT ; i++ )
		set_pgtable_section(page_table, i, i << SECTION_SHIFT, MT_DEVICE_NGNRE);
#endif

	/* load TTBR0 */
	el = current_el();
	if (el == 1) {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL1_IPS_BITS,
				  MEMORY_ATTRIBUTES_WT);
	} else if (el == 2) {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL2_IPS_BITS,
				  MEMORY_ATTRIBUTES_WT);
	} else {
		set_ttbr_tcr_mair(el, gd->arch.tlb_addr,
				  TCR_FLAGS | TCR_EL3_IPS_BITS,
				  MEMORY_ATTRIBUTES_WT);
	}
	/* enable the mmu */
	set_sctlr(get_sctlr() | CR_M);
}

void dcache_enable_wt(void)
{
	/* The data cache is not active unless the mmu is enabled */
	if (!(get_sctlr() & CR_M)) {
		invalidate_dcache_all();
		__asm_invalidate_tlb_all();
		mmu_setup_wt();
	}

	set_sctlr(get_sctlr() | CR_C);
}

void reset_cache_write_through(void)
{
	icache_disable();
	invalidate_icache_all();
	dcache_disable();
	invalidate_dcache_all();

	icache_enable();
	dcache_enable_wt();
}

void reset_cache_write_back(void)
{
	icache_disable();
	invalidate_icache_all();
	dcache_disable();
	invalidate_dcache_all();

	enable_caches();
}
#endif
