/*
 * Virtual Memory Map support
 *
 * (C) 2007 sgi. Christoph Lameter.
 *
 * Virtual memory maps allow VM primitives pfn_to_page, page_to_pfn,
 * virt_to_page, page_address() to be implemented as a base offset
 * calculation without memory access.
 *
 * However, virtual mappings need a page table and TLBs. Many Linux
 * architectures already map their physical space using 1-1 mappings
 * via TLBs. For those arches the virtual memory map is essentially
 * for free if we use the same page size as the 1-1 mappings. In that
 * case the overhead consists of a few additional pages that are
 * allocated to create a view of memory for vmemmap.
 *
 * The architecture is expected to provide a vmemmap_populate() function
 * to instantiate the mapping.
 */
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/bootmem.h>
#include <linux/memremap.h>
#include <linux/highmem.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/memblock.h>
#include <asm/dma.h>
#include <asm/pgalloc.h>
#include <asm/pgtable.h>

extern int saving_section_page_table_xen_low;
extern int saving_section_page_table;

/*
 * Allocate a block of memory to be used to back the virtual memory map
 * or to back the page tables that are used to create the mapping.
 * Uses the main allocators if they are available, else bootmem.
 */

static void * __ref __earlyonly_bootmem_alloc(int node,
				unsigned long size,
				unsigned long align,
				unsigned long goal)
{
	return memblock_virt_alloc_try_nid(size, align, goal,
					    BOOTMEM_ALLOC_ACCESSIBLE, node);
}

static void *vmemmap_buf;
static void *vmemmap_buf_end;

void * __meminit vmemmap_alloc_block(unsigned long size, int node)
{
	/* If the main allocator is up use that, fallback to bootmem. */
	if (slab_is_available()) {
		struct page *page;

		if (node_state(node, N_HIGH_MEMORY))
			page = alloc_pages_node(
				node, GFP_KERNEL | __GFP_ZERO | __GFP_REPEAT,
				get_order(size));
		else
			page = alloc_pages(
				GFP_KERNEL | __GFP_ZERO | __GFP_REPEAT,
				get_order(size));
		if (page)
			return page_address(page);
		return NULL;
	} else
		return __earlyonly_bootmem_alloc(node, size, size,
				__pa(MAX_DMA_ADDRESS));
}

/* need to make sure size is all the same during early stage */
static void * __meminit alloc_block_buf(unsigned long size, int node)
{
	void *ptr;

	if (!vmemmap_buf)
		return vmemmap_alloc_block(size, node);

	/* take the from buf */
	ptr = (void *)ALIGN((unsigned long)vmemmap_buf, size);
	if (ptr + size > vmemmap_buf_end)
		return vmemmap_alloc_block(size, node);

	vmemmap_buf = ptr + size;

	return ptr;
}

static unsigned long __meminit vmem_altmap_next_pfn(struct vmem_altmap *altmap)
{
	return altmap->base_pfn + altmap->reserve + altmap->alloc
		+ altmap->align;
}

static unsigned long __meminit vmem_altmap_nr_free(struct vmem_altmap *altmap)
{
	unsigned long allocated = altmap->alloc + altmap->align;

	if (altmap->free > allocated)
		return altmap->free - allocated;
	return 0;
}

/**
 * vmem_altmap_alloc - allocate pages from the vmem_altmap reservation
 * @altmap - reserved page pool for the allocation
 * @nr_pfns - size (in pages) of the allocation
 *
 * Allocations are aligned to the size of the request
 */
static unsigned long __meminit vmem_altmap_alloc(struct vmem_altmap *altmap,
		unsigned long nr_pfns)
{
	unsigned long pfn = vmem_altmap_next_pfn(altmap);
	unsigned long nr_align;

	nr_align = 1UL << find_first_bit(&nr_pfns, BITS_PER_LONG);
	nr_align = ALIGN(pfn, nr_align) - pfn;

	if (nr_pfns + nr_align > vmem_altmap_nr_free(altmap))
		return ULONG_MAX;
	altmap->alloc += nr_pfns;
	altmap->align += nr_align;
	return pfn + nr_align;
}

static void * __meminit altmap_alloc_block_buf(unsigned long size,
		struct vmem_altmap *altmap)
{
	unsigned long pfn, nr_pfns;
	void *ptr;

	if (size & ~PAGE_MASK) {
		pr_warn_once("%s: allocations must be multiple of PAGE_SIZE (%ld)\n",
				__func__, size);
		return NULL;
	}

	nr_pfns = size >> PAGE_SHIFT;
	pfn = vmem_altmap_alloc(altmap, nr_pfns);
	if (pfn < ULONG_MAX)
		ptr = __va(__pfn_to_phys(pfn));
	else
		ptr = NULL;
	pr_debug("%s: pfn: %#lx alloc: %ld align: %ld nr: %#lx\n",
			__func__, pfn, altmap->alloc, altmap->align, nr_pfns);

	return ptr;
}

/* need to make sure size is all the same during early stage */
void * __meminit __vmemmap_alloc_block_buf(unsigned long size, int node,
		struct vmem_altmap *altmap)
{
	if (altmap)
		return altmap_alloc_block_buf(size, altmap);
	return alloc_block_buf(size, node);
}

void __meminit vmemmap_verify(pte_t *pte, int node,
				unsigned long start, unsigned long end)
{
	unsigned long pfn = pte_pfn(*pte);
	int actual_node = early_pfn_to_nid(pfn);

	if (node_distance(actual_node, node) > LOCAL_DISTANCE)
		pr_warn("[%lx-%lx] potential offnode page_structs\n",
			start, end - 1);
}

pte_t * __meminit vmemmap_pte_populate(pmd_t *pmd, unsigned long addr, int node)
{
	pte_t *pte = pte_offset_kernel(pmd, addr);
	if (pte_none(*pte)) {
		pte_t entry;
		void *p = alloc_block_buf(PAGE_SIZE, node);
		if (!p)
			return NULL;
		entry = pfn_pte(__pa(p) >> PAGE_SHIFT, PAGE_KERNEL);
		set_pte_at(&init_mm, addr, pte, entry);
	}
	return pte;
}

pmd_t * __meminit vmemmap_pmd_populate(pud_t *pud, unsigned long addr, int node)
{
	pmd_t *pmd = pmd_offset(pud, addr);
	if (pmd_none(*pmd)) {
		void *p = vmemmap_alloc_block(PAGE_SIZE, node);
		if (!p)
			return NULL;
		pmd_populate_kernel(&init_mm, pmd, p);
	}
	return pmd;
}

pud_t * __meminit vmemmap_pud_populate(pgd_t *pgd, unsigned long addr, int node)
{
	pud_t *pud = pud_offset(pgd, addr);
	if (pud_none(*pud)) {
		void *p = vmemmap_alloc_block(PAGE_SIZE, node);
		if (!p)
			return NULL;
		pud_populate(&init_mm, pud, p);
	}
	return pud;
}

pgd_t * __meminit vmemmap_pgd_populate(unsigned long addr, int node)
{
	pgd_t *pgd = pgd_offset_k(addr);
	if (pgd_none(*pgd)) {
		void *p = vmemmap_alloc_block(PAGE_SIZE, node);
		if (!p)
			return NULL;
		pgd_populate(&init_mm, pgd, p);
	}
	return pgd;
}

int __meminit vmemmap_populate_basepages(unsigned long start,
					 unsigned long end, int node)
{
	unsigned long addr = start;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	for (; addr < end; addr += PAGE_SIZE) {
		pgd = vmemmap_pgd_populate(addr, node);
		if (!pgd)
			return -ENOMEM;
		pud = vmemmap_pud_populate(pgd, addr, node);
		if (!pud)
			return -ENOMEM;
		pmd = vmemmap_pmd_populate(pud, addr, node);
		if (!pmd)
			return -ENOMEM;
		pte = vmemmap_pte_populate(pmd, addr, node);
		if (!pte)
			return -ENOMEM;
		vmemmap_verify(pte, node, addr, addr + PAGE_SIZE);
	}

	return 0;
}

struct page * __meminit sparse_mem_map_populate(unsigned long pnum, int nid)
{
	unsigned long start;
	unsigned long end;
	struct page *map;

	map = pfn_to_page(pnum * PAGES_PER_SECTION);
	start = (unsigned long)map;
	end = (unsigned long)(map + PAGES_PER_SECTION);

#if 0
	DDDD("map %p, pnum %lld, PAGES_PER_SECTION 0x%08x, nid %d",
		map, pnum, PAGES_PER_SECTION, nid);
	DDDD("start 0x%llx", start);
	DDDD("end   0x%llx", end);
	DDDD("memblock.memory.cnt %d", memblock.memory.cnt);
	DDDD("saving_section_page_table %d", saving_section_page_table);
#endif

#ifndef CONFIG_ARM64_64K_PAGES
	/* workaroud for memory saving */
	/* only for memory size less than 1-GB system */
	/* suppose using continuous memory block */
	/*                                     */
	/*             pnum 0 +---------+                   */
	/*           /        +  PMD 0  |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 1  |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 2  |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 3  |                   */
	/*  1GB     <         +---------+                   */
	/* (section0)|        +  PMD 4  |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 5  |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 6  |                   */
	/*           |        +---------+                   */
	/*           \        +  PMD 7  |                   */
	/*             pnum 1 +---------+                   */
	/*           /        +  PMD 8  | PMD_lower         */
	/*           |        +---------+                   */
	/*           |        +  PMD 9  |         PMD_start */
	/*           |        +---------+                   */
	/*           |        +  PMD 10 |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 11 |                   */
	/*  1GB     <         +---------+                   */
	/* (section1)|        +  PMD 12 |         PMD_end   */
	/*           |        +---------+                   */
	/*           |        +  PMD 13 |                   */
	/*           |        +---------+                   */
	/*           |        +  PMD 14 |                   */
	/*           |        +---------+                   */
	/*           \        +  PMD 15 |                   */
	/*             pnum 2 +---------+                   */
	/*           /        +  PMD 16 | PMD_upper         */
	/*           |        +---------+                   */
	/*           |        +  PMD 17 |                   */
	/*           |        +---------+                   */
	/*                                                  */
	if( saving_section_page_table &&
		(memblock.memory.cnt == 1) )
	{
		#define PMD_MEM_SIZE (((PAGES_PER_SECTION>>3)<<PAGE_SHIFT))
		unsigned long PMD_lower;
		unsigned long PMD_uppder;
		unsigned long PMD_start;
		unsigned long PMD_count;
		unsigned long PMD_end;
		unsigned long start_phy;
		unsigned long end_phy;

		PMD_lower = pnum<<3;
		PMD_uppder = PMD_lower+8;
		PMD_start = memblock.memory.regions[0].base / PMD_MEM_SIZE;
		PMD_count = (memblock.memory.regions[0].size+PMD_MEM_SIZE-1)
			/ PMD_MEM_SIZE;
		PMD_end = PMD_start + PMD_count;

		//DDDD("PMD_start 0x%llx", PMD_start);
		//DDDD("PMD_count 0x%llx", PMD_count);
		//DDDD("PMD_end   0x%llx", PMD_end);

		if(PMD_start > PMD_lower) { /* not fall in valid range */
			start = (unsigned long)(map +
				((PMD_start-PMD_lower)*(PAGES_PER_SECTION>>3)));
		}

		if(PMD_end < PMD_uppder) { /* not fall in valid range */
			end = (unsigned long)(map +
				((PMD_end-PMD_lower)*(PAGES_PER_SECTION>>3)));
		}

		start_phy = (pnum * PAGES_PER_SECTION) << PAGE_SHIFT;
		end_phy = ((pnum+1) * PAGES_PER_SECTION) << PAGE_SHIFT;

		//DDDD("updated: start 0x%llx", start);
		//DDDD("updated: end   0x%llx", end);
	}

	if( saving_section_page_table_xen_low )
	{
		/* for low memory dom0 system, its memory layout maybe present in */
		/* non-continuous block. For example:                             */
		/* root@OpenWrt:/# cat /sys/kernel/debug/memblock/memory          */
		/* 0: 0x0000000033800000..0x000000003bffffff                      */
		/* 1: 0x000000003e000000..0x000000003f7fffff                      */
		#define PMD_MEM_SIZE (((PAGES_PER_SECTION>>3)<<PAGE_SHIFT))
		unsigned long PMD_lower;
		unsigned long PMD_uppder;
		unsigned long PMD_start;
		unsigned long PMD_end;
		unsigned long start_phy;
		unsigned long end_phy;

		printk("old: start 0x%llx", start);
		printk("old: end   0x%llx", end);

		PMD_lower = pnum<<3;
		PMD_uppder = PMD_lower+8;
		PMD_start = memblock.memory.regions[0].base / PMD_MEM_SIZE;
		PMD_end = (memblock.memory.regions[memblock.memory.cnt-1].base +
			memblock.memory.regions[memblock.memory.cnt-1].size +
			PMD_MEM_SIZE-1) / PMD_MEM_SIZE;

		printk("\033[1;33m" "PMD_start %d" "\033[m\n", PMD_start);
		printk("\033[1;33m" "PMD_end %d" "\033[m\n", PMD_end);

		if(PMD_start > PMD_lower) { /* not fall in valid range */
			start = (unsigned long)(map +
				((PMD_start-PMD_lower)*(PAGES_PER_SECTION>>3)));
		}

		if(PMD_end < PMD_uppder) { /* not fall in valid range */
			end = (unsigned long)(map +
				((PMD_end-PMD_lower)*(PAGES_PER_SECTION>>3)));
		}

		start_phy = (pnum * PAGES_PER_SECTION) << PAGE_SHIFT;
		end_phy = ((pnum+1) * PAGES_PER_SECTION) << PAGE_SHIFT;

		printk("updated: start 0x%llx", start);
		printk("updated: end   0x%llx", end);
	}
#endif
	if (vmemmap_populate(start, end, nid))
		return NULL;

	return map;
}

void __init sparse_mem_maps_populate_node(struct page **map_map,
					  unsigned long pnum_begin,
					  unsigned long pnum_end,
					  unsigned long map_count, int nodeid)
{
	unsigned long pnum;
	unsigned long size = sizeof(struct page) * PAGES_PER_SECTION;
	void *vmemmap_buf_start;

	size = ALIGN(size, PMD_SIZE);
	vmemmap_buf_start = __earlyonly_bootmem_alloc(nodeid, size * map_count,
			 PMD_SIZE, __pa(MAX_DMA_ADDRESS));

	if (vmemmap_buf_start) {
		vmemmap_buf = vmemmap_buf_start;
		vmemmap_buf_end = vmemmap_buf_start + size * map_count;
	}

	for (pnum = pnum_begin; pnum < pnum_end; pnum++) {
		struct mem_section *ms;

		if (!present_section_nr(pnum))
			continue;

		map_map[pnum] = sparse_mem_map_populate(pnum, nodeid);
		if (map_map[pnum])
			continue;
		ms = __nr_to_section(pnum);
		pr_err("%s: sparsemem memory map backing failed some memory will not be available\n",
		       __func__);
		ms->section_mem_map = 0;
	}

	if (vmemmap_buf_start) {
		/* need to free left buf */
		memblock_free_early(__pa(vmemmap_buf),
				    vmemmap_buf_end - vmemmap_buf);
		vmemmap_buf = NULL;
		vmemmap_buf_end = NULL;
	}
}
