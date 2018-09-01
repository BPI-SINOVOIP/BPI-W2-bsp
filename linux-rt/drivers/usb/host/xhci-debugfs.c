
#include <linux/uaccess.h>
#include <linux/debugfs.h>
#include <linux/slab.h>
#include "xhci.h"

#define XHCI_INIT_VALUE 0x0

#define TO_NEXT(next, size, inc) \
do { 				\
	size -= inc; 	\
	next += inc; 	\
} while (0)

static struct dentry *xhci_debug_root;

static void xhci_dbgfs_regs(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u32 temp;

	inc = snprintf(next, size, "// xHCI capability registers at %p:\n",
			xhci->cap_regs);
	TO_NEXT(next, size, inc);
	temp = readl(&xhci->cap_regs->hc_capbase);
	inc = snprintf(next, size, "// @%p = 0x%x (CAPLENGTH AND HCIVERSION)\n",
			&xhci->cap_regs->hc_capbase, temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "//   CAPLENGTH: 0x%x\n",
			(unsigned int) HC_LENGTH(temp));
	TO_NEXT(next, size, inc);
#if 0
	inc = snprintf(next, size, "//   HCIVERSION: 0x%x\n",
			(unsigned int) HC_VERSION(temp));
	TO_NEXT(next, size, inc);
#endif

	inc = snprintf(next, size, "// xHCI operational registers at %p:\n", xhci->op_regs);
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->run_regs_off);
	inc = snprintf(next, size, "// @%p = 0x%x RTSOFF\n",
			&xhci->cap_regs->run_regs_off,
			(unsigned int) temp & RTSOFF_MASK);
	TO_NEXT(next, size, inc);

	inc = snprintf(next, size, "// xHCI runtime registers at %p:\n", xhci->run_regs);
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->db_off);
	inc = snprintf(next, size, "// @%p = 0x%x DBOFF\n", &xhci->cap_regs->db_off, temp);
	TO_NEXT(next, size, inc);

	inc = snprintf(next, size, "// Doorbell array at %p:\n", xhci->dba);
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_cap_regs(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u32 temp;

	inc = snprintf(next, size, "xHCI capability registers at %p:\n", xhci->cap_regs);
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->hc_capbase);
	inc = snprintf(next, size, "CAPLENGTH AND HCIVERSION 0x%x:\n",
			(unsigned int) temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "CAPLENGTH: 0x%x\n",
			(unsigned int) HC_LENGTH(temp));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "HCIVERSION: 0x%x\n",
			(unsigned int) HC_VERSION(temp));
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->hcs_params1);
	inc = snprintf(next, size, "HCSPARAMS 1: 0x%x\n",
			(unsigned int) temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Max device slots: %u\n",
			(unsigned int) HCS_MAX_SLOTS(temp));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Max interrupters: %u\n",
			(unsigned int) HCS_MAX_INTRS(temp));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Max ports: %u\n",
			(unsigned int) HCS_MAX_PORTS(temp));
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->hcs_params2);
	inc = snprintf(next, size, "HCSPARAMS 2: 0x%x\n",
			(unsigned int) temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Isoc scheduling threshold: %u\n",
			(unsigned int) HCS_IST(temp));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Maximum allowed segments in event ring: %u\n",
			(unsigned int) HCS_ERST_MAX(temp));
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->hcs_params3);
	inc = snprintf(next, size, "HCSPARAMS 3 0x%x:\n",
			(unsigned int) temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Worst case U1 device exit latency: %u\n",
			(unsigned int) HCS_U1_LATENCY(temp));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Worst case U2 device exit latency: %u\n",
			(unsigned int) HCS_U2_LATENCY(temp));
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->hcc_params);
	inc = snprintf(next, size, "HCC PARAMS 0x%x:\n", (unsigned int) temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  HC generates %s bit addresses\n",
			HCC_64BIT_ADDR(temp) ? "64" : "32");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  FIXME: more HCCPARAMS debugging\n");
	TO_NEXT(next, size, inc);

	temp = readl(&xhci->cap_regs->run_regs_off);
	inc = snprintf(next, size, "RTSOFF 0x%x:\n", temp & RTSOFF_MASK);
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_command_reg(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u32 temp;

	temp = readl(&xhci->op_regs->command);
	inc = snprintf(next, size, "USBCMD 0x%x:\n", temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  HC is %s\n",
			(temp & CMD_RUN) ? "running" : "being stopped");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  HC has %sfinished hard reset\n",
			(temp & CMD_RESET) ? "not " : "");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Event Interrupts %s\n",
			(temp & CMD_EIE) ? "enabled " : "disabled");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Host System Error Interrupts %s\n",
			(temp & CMD_HSEIE) ? "enabled " : "disabled");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  HC has %sfinished light reset\n",
			(temp & CMD_LRESET) ? "not " : "");
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_status(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u32 temp;

	temp = readl(&xhci->op_regs->status);
	inc = snprintf(next, size, "USBSTS 0x%x:\n", temp);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  Event ring is %sempty\n",
			(temp & STS_EINT) ? "not " : "");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  %sHost System Error\n",
			(temp & STS_FATAL) ? "WARNING: " : "No ");
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "  HC is %s\n",
			(temp & STS_HALT) ? "halted" : "running");
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_op_regs(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	inc = snprintf(next, size, "xHCI operational registers at %p:\n", xhci->op_regs);
	TO_NEXT(next, size, inc);
	xhci_dbgfs_print_command_reg(xhci, &next, &size);
	xhci_dbgfs_print_status(xhci, &next, &size);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_ports(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	__le32 __iomem *addr;
	int i, j;
	int ports;
	char *names[NUM_PORT_REGS] = {
		"status",
		"power",
		"link",
		"reserved",
	};

	ports = HCS_MAX_PORTS(xhci->hcs_params1);
	addr = &xhci->op_regs->port_status_base;
	for (i = 0; i < ports; i++) {
		for (j = 0; j < NUM_PORT_REGS; ++j) {
			inc = snprintf(next, size, "%p port %s reg = 0x%x\n",
					addr, names[j],
					(unsigned int) readl(addr));
			TO_NEXT(next, size, inc);
			addr++;
		}
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_ir_set(struct xhci_hcd *xhci, int set_num,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	struct xhci_intr_reg __iomem *ir_set = &xhci->run_regs->ir_set[set_num];
	void __iomem *addr;
	u32 temp;
	u64 temp_64;

	addr = &ir_set->irq_pending;
	temp = readl(addr);
	if (temp == XHCI_INIT_VALUE)
		return;

	inc = snprintf(next, size, "  %p: ir_set[%i]\n", ir_set, set_num);
	TO_NEXT(next, size, inc);

	inc = snprintf(next, size, "  %p: ir_set.pending = 0x%x\n", addr,
			(unsigned int)temp);
	TO_NEXT(next, size, inc);

	addr = &ir_set->irq_control;
	temp = readl(addr);
	inc = snprintf(next, size, "  %p: ir_set.control = 0x%x\n", addr,
			(unsigned int)temp);
	TO_NEXT(next, size, inc);

	addr = &ir_set->erst_size;
	temp = readl(addr);
	inc = snprintf(next, size, "  %p: ir_set.erst_size = 0x%x\n", addr,
			(unsigned int)temp);
	TO_NEXT(next, size, inc);

	addr = &ir_set->rsvd;
	temp = readl(addr);
	if (temp != XHCI_INIT_VALUE) {
		inc = snprintf(next, size, "  WARN: %p: ir_set.rsvd = 0x%x\n",
				addr, (unsigned int)temp);
		TO_NEXT(next, size, inc);
	}

	addr = &ir_set->erst_base;
	temp_64 = xhci_read_64(xhci, addr);
	inc = snprintf(next, size, "  %p: ir_set.erst_base = @%08llx\n",
			addr, temp_64);
	TO_NEXT(next, size, inc);

	addr = &ir_set->erst_dequeue;
	temp_64 = xhci_read_64(xhci, addr);
	inc = snprintf(next, size, "  %p: ir_set.erst_dequeue = @%08llx\n",
			addr, temp_64);
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_run_regs(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u32 temp;
	int i;

	inc = snprintf(next, size, "xHCI runtime registers at %p:\n", xhci->run_regs);
	TO_NEXT(next, size, inc);
	temp = readl(&xhci->run_regs->microframe_index);
	inc = snprintf(next, size, "  %p: Microframe index = 0x%x\n",
			&xhci->run_regs->microframe_index,
			(unsigned int) temp);
	TO_NEXT(next, size, inc);
	for (i = 0; i < 7; ++i) {
		temp = readl(&xhci->run_regs->rsvd[i]);
		if (temp != XHCI_INIT_VALUE) {
			inc = snprintf(next, size, "  WARN: %p: Rsvd[%i] = 0x%x\n",
					&xhci->run_regs->rsvd[i],
					i, (unsigned int) temp);
			TO_NEXT(next, size, inc);
		}
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_registers(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	xhci_dbgfs_print_cap_regs(xhci, &next, &size);
	xhci_dbgfs_print_op_regs(xhci, &next, &size);
	xhci_dbgfs_print_ports(xhci, &next, &size);
	xhci_dbgfs_print_run_regs(xhci, &next, &size);
	xhci_dbgfs_print_ir_set(xhci, 0, &next, &size);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_print_trb_offsets(struct xhci_hcd *xhci, union xhci_trb *trb,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	int i;
	for (i = 0; i < 4; ++i) {
		inc = snprintf(next, size, "Offset 0x%x = 0x%x\n",
				i*4, trb->generic.field[i]);
		TO_NEXT(next, size, inc);
	}

done:
	*sizep = size;
	*nextp = next;
}

/**
 * Debug a transfer request block (TRB).
 */
static void xhci_dbgfs_trb(struct xhci_hcd *xhci, union xhci_trb *trb,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u64	address;
	u32	type = le32_to_cpu(trb->link.control) & TRB_TYPE_BITMASK;

	switch (type) {
	case TRB_TYPE(TRB_LINK):
		inc = snprintf(next, size, "Link TRB:\n");
		TO_NEXT(next, size, inc);
		xhci_dbgfs_print_trb_offsets(xhci, trb, &next, &size);

		address = le64_to_cpu(trb->link.segment_ptr);
		inc = snprintf(next, size, "Next ring segment DMA address = 0x%llx\n", address);
		TO_NEXT(next, size, inc);

		inc = snprintf(next, size, "Interrupter target = 0x%x\n",
			 GET_INTR_TARGET(le32_to_cpu(trb->link.intr_target)));
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "Cycle bit = %u\n",
			 le32_to_cpu(trb->link.control) & TRB_CYCLE);
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "Toggle cycle bit = %u\n",
			 le32_to_cpu(trb->link.control) & LINK_TOGGLE);
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "No Snoop bit = %u\n",
			 le32_to_cpu(trb->link.control) & TRB_NO_SNOOP);
		TO_NEXT(next, size, inc);
		break;
	case TRB_TYPE(TRB_TRANSFER):
		address = le64_to_cpu(trb->trans_event.buffer);
		/*
		 * FIXME: look at flags to figure out if it's an address or if
		 * the data is directly in the buffer field.
		 */
		inc = snprintf(next, size, "DMA address or buffer contents= %llu\n", address);
		TO_NEXT(next, size, inc);
		break;
	case TRB_TYPE(TRB_COMPLETION):
		address = le64_to_cpu(trb->event_cmd.cmd_trb);
		inc = snprintf(next, size, "Command TRB pointer = %llu\n", address);
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "Completion status = %u\n",
			 GET_COMP_CODE(le32_to_cpu(trb->event_cmd.status)));
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "Flags = 0x%x\n",
			 le32_to_cpu(trb->event_cmd.flags));
		TO_NEXT(next, size, inc);
		break;
	default:
		inc = snprintf(next, size, "Unknown TRB with TRB type ID %u\n",
				(unsigned int) type>>10);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_print_trb_offsets(xhci, trb, &next, &size);
		break;
	}

done:
	*sizep = size;
	*nextp = next;
}

/**
 * Debug a segment with an xHCI ring.
 *
 * @return The Link TRB of the segment, or NULL if there is no Link TRB
 * (which is a bug, since all segments must have a Link TRB).
 *
 * Prints out all TRBs in the segment, even those after the Link TRB.
 *
 * XXX: should we print out TRBs that the HC owns?  As long as we don't
 * write, that should be fine...  We shouldn't expect that the memory pointed to
 * by the TRB is valid at all.  Do we care about ones the HC owns?  Probably,
 * for HC debugging.
 */
static void xhci_dbgfs_segment(struct xhci_hcd *xhci, struct xhci_segment *seg,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	int i;
	u64 addr = seg->dma;
	union xhci_trb *trb = seg->trbs;

	for (i = 0; i < TRBS_PER_SEGMENT; ++i) {
		trb = &seg->trbs[i];
		inc = snprintf(next, size, "@%016llx %08x %08x %08x %08x\n", addr,
			 lower_32_bits(le64_to_cpu(trb->link.segment_ptr)),
			 upper_32_bits(le64_to_cpu(trb->link.segment_ptr)),
			 le32_to_cpu(trb->link.intr_target),
			 le32_to_cpu(trb->link.control));
		TO_NEXT(next, size, inc);
		addr += sizeof(*trb);
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_ring_ptrs(struct xhci_hcd *xhci, struct xhci_ring *ring,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	inc = snprintf(next, size, "Ring deq = %p (virt), 0x%llx (dma)\n",
			ring->dequeue,
			(unsigned long long)xhci_trb_virt_to_dma(ring->deq_seg,
							    ring->dequeue));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "Ring deq updated %u times\n",
			ring->deq_updates);
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "Ring enq = %p (virt), 0x%llx (dma)\n",
			ring->enqueue,
			(unsigned long long)xhci_trb_virt_to_dma(ring->enq_seg,
							    ring->enqueue));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "Ring enq updated %u times\n",
			ring->enq_updates);
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

/**
 * Debugging for an xHCI ring, which is a queue broken into multiple segments.
 *
 * Print out each segment in the ring.  Check that the DMA address in
 * each link segment actually matches the segment's stored DMA address.
 * Check that the link end bit is only set at the end of the ring.
 * Check that the dequeue and enqueue pointers point to real data in this ring
 * (not some other ring).
 */
static void xhci_dbgfs_ring(struct xhci_hcd *xhci, struct xhci_ring *ring,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	/* FIXME: Throw an error if any segment doesn't have a Link TRB */
	struct xhci_segment *seg;
	struct xhci_segment *first_seg = ring->first_seg;
	xhci_dbgfs_segment(xhci, first_seg, &next, &size);

	if (!ring->enq_updates && !ring->deq_updates) {
		inc = snprintf(next, size, "  Ring has not been updated\n");
		TO_NEXT(next, size, inc);
		goto done;
	}
	for (seg = first_seg->next; seg != first_seg; seg = seg->next)
		xhci_dbgfs_segment(xhci, seg, &next, &size);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_ep_rings(struct xhci_hcd *xhci,
		unsigned int slot_id, unsigned int ep_index,
		struct xhci_virt_ep *ep,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	int i;
	struct xhci_ring *ring;

	if (ep->ep_state & EP_HAS_STREAMS) {
		for (i = 1; i < ep->stream_info->num_streams; i++) {
			ring = ep->stream_info->stream_rings[i];
			inc = snprintf(next, size, "Dev %d endpoint %d stream ID %d:\n",
				slot_id, ep_index, i);
			TO_NEXT(next, size, inc);
			xhci_dbgfs_segment(xhci, ring->deq_seg, &next, &size);
		}
	} else {
		ring = ep->ring;
		if (!ring)
			goto done;
		inc = snprintf(next, size, "Dev %d endpoint ring %d:\n",
				slot_id, ep_index);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_segment(xhci, ring->deq_seg, &next, &size);
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_erst(struct xhci_hcd *xhci, struct xhci_erst *erst,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;


	u64 addr = erst->erst_dma_addr;
	int i;
	struct xhci_erst_entry *entry;

	for (i = 0; i < erst->num_entries; ++i) {
		entry = &erst->entries[i];
		inc = snprintf(next, size, "@%016llx %08x %08x %08x %08x\n",
			 addr,
			 lower_32_bits(le64_to_cpu(entry->seg_addr)),
			 upper_32_bits(le64_to_cpu(entry->seg_addr)),
			 le32_to_cpu(entry->seg_size),
			 le32_to_cpu(entry->rsvd));
		TO_NEXT(next, size, inc);
		addr += sizeof(*entry);
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_cmd_ptrs(struct xhci_hcd *xhci,
		char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	u64 val;

	val = xhci_read_64(xhci, &xhci->op_regs->cmd_ring);
	inc = snprintf(next, size, "// xHC command ring deq ptr low bits + flags = @%08x\n",
			lower_32_bits(val));
	TO_NEXT(next, size, inc);
	inc = snprintf(next, size, "// xHC command ring deq ptr high bits = @%08x\n",
			upper_32_bits(val));
	TO_NEXT(next, size, inc);

done:
	*sizep = size;
	*nextp = next;
}

/* Print the last 32 bytes for 64-byte contexts */
static void dbgfs_rsvd64(struct xhci_hcd *xhci, u64 *ctx, dma_addr_t dma,
		  char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	int i;
	for (i = 0; i < 4; ++i) {
		inc = snprintf(next, size, "@%p (virt) @%08llx "
			 "(dma) %#08llx - rsvd64[%d]\n",
			 &ctx[4 + i], (unsigned long long)dma,
			 ctx[4 + i], i);
		TO_NEXT(next, size, inc);

		dma += 8;
	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_slot_ctx(struct xhci_hcd *xhci, struct xhci_container_ctx *ctx,
		  char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	/* Fields are 32 bits wide, DMA addresses are in bytes */
	int field_size = 32 / 8;
	int i;

	struct xhci_slot_ctx *slot_ctx = xhci_get_slot_ctx(xhci, ctx);
	dma_addr_t dma = ctx->dma +
		((unsigned long)slot_ctx - (unsigned long)ctx->bytes);
	int csz = HCC_64BYTE_CONTEXT(xhci->hcc_params);

	inc = snprintf(next, size, "Slot Context:\n");
	TO_NEXT(next, size, inc);

	inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - dev_info\n",
			&slot_ctx->dev_info,
			(unsigned long long)dma, slot_ctx->dev_info);
	TO_NEXT(next, size, inc);
	dma += field_size;
	inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - dev_info2\n",
			&slot_ctx->dev_info2,
			(unsigned long long)dma, slot_ctx->dev_info2);
	TO_NEXT(next, size, inc);
	dma += field_size;
	inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - tt_info\n",
			&slot_ctx->tt_info,
			(unsigned long long)dma, slot_ctx->tt_info);
	TO_NEXT(next, size, inc);
	dma += field_size;
	inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - dev_state\n",
			&slot_ctx->dev_state,
			(unsigned long long)dma, slot_ctx->dev_state);
	TO_NEXT(next, size, inc);
	dma += field_size;
	for (i = 0; i < 4; ++i) {
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - rsvd[%d]\n",
				&slot_ctx->reserved[i], (unsigned long long)dma,
				slot_ctx->reserved[i], i);
		TO_NEXT(next, size, inc);
		dma += field_size;
	}

	if (csz)
		dbgfs_rsvd64(xhci, (u64 *)slot_ctx, dma, &next, &size);

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_ep_ctx(struct xhci_hcd *xhci,
		     struct xhci_container_ctx *ctx,
		     unsigned int last_ep,
		     char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;

	int i, j;
	int last_ep_ctx = 31;
	/* Fields are 32 bits wide, DMA addresses are in bytes */
	int field_size = 32 / 8;
	int csz = HCC_64BYTE_CONTEXT(xhci->hcc_params);

	if (last_ep < 31)
		last_ep_ctx = last_ep + 1;
	for (i = 0; i < last_ep_ctx; ++i) {
		unsigned int epaddr = xhci_get_endpoint_address(i);
		struct xhci_ep_ctx *ep_ctx = xhci_get_ep_ctx(xhci, ctx, i);
		dma_addr_t dma = ctx->dma +
			((unsigned long)ep_ctx - (unsigned long)ctx->bytes);

		inc = snprintf(next, size, "%s Endpoint %02d Context (ep_index %02d):\n",
				usb_endpoint_out(epaddr) ? "OUT" : "IN",
				epaddr & USB_ENDPOINT_NUMBER_MASK, i);
		TO_NEXT(next, size, inc);
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - ep_info\n",
				&ep_ctx->ep_info,
				(unsigned long long)dma, ep_ctx->ep_info);
		TO_NEXT(next, size, inc);
		dma += field_size;
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - ep_info2\n",
				&ep_ctx->ep_info2,
				(unsigned long long)dma, ep_ctx->ep_info2);
		TO_NEXT(next, size, inc);
		dma += field_size;
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08llx - deq\n",
				&ep_ctx->deq,
				(unsigned long long)dma, ep_ctx->deq);
		TO_NEXT(next, size, inc);
		dma += 2*field_size;
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - tx_info\n",
				&ep_ctx->tx_info,
				(unsigned long long)dma, ep_ctx->tx_info);
		TO_NEXT(next, size, inc);
		dma += field_size;
		for (j = 0; j < 3; ++j) {
			inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - rsvd[%d]\n",
					&ep_ctx->reserved[j],
					(unsigned long long)dma,
					ep_ctx->reserved[j], j);
			TO_NEXT(next, size, inc);
			dma += field_size;
		}

		if (csz)
			dbgfs_rsvd64(xhci, (u64 *)ep_ctx, dma, &next, &size);

	}

done:
	*sizep = size;
	*nextp = next;
}

static void xhci_dbgfs_ctx(struct xhci_hcd *xhci,
		  struct xhci_container_ctx *ctx,
		  unsigned int last_ep,
		  char **nextp, unsigned *sizep)
{
	unsigned		inc;
	unsigned		size = *sizep;
	char			*next = *nextp;
	int i;
	/* Fields are 32 bits wide, DMA addresses are in bytes */
	int field_size = 32 / 8;
	dma_addr_t dma = ctx->dma;
	int csz = HCC_64BYTE_CONTEXT(xhci->hcc_params);

	if (ctx->type == XHCI_CTX_TYPE_INPUT) {
		struct xhci_input_control_ctx *ctrl_ctx =
			xhci_get_input_control_ctx(ctx);
		if (!ctrl_ctx) {
			inc = snprintf(next, size, "Could not get input context, bad type.\n");
			TO_NEXT(next, size, inc);
			goto done;
		}

		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - drop flags\n",
			 &ctrl_ctx->drop_flags, (unsigned long long)dma,
			 ctrl_ctx->drop_flags);
		TO_NEXT(next, size, inc);

		dma += field_size;
		inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - add flags\n",
			 &ctrl_ctx->add_flags, (unsigned long long)dma,
			 ctrl_ctx->add_flags);
		TO_NEXT(next, size, inc);

		dma += field_size;
		for (i = 0; i < 6; ++i) {
			inc = snprintf(next, size, "@%p (virt) @%08llx (dma) %#08x - rsvd2[%d]\n",
				 &ctrl_ctx->rsvd2[i], (unsigned long long)dma,
				 ctrl_ctx->rsvd2[i], i);
			TO_NEXT(next, size, inc);
			dma += field_size;
		}

		if (csz)
			dbgfs_rsvd64(xhci, (u64 *)ctrl_ctx, dma, &next, &size);
	}

	xhci_dbgfs_slot_ctx(xhci, ctx, &next, &size);
	xhci_dbgfs_ep_ctx(xhci, ctx, last_ep, &next, &size);

done:
	*sizep = size;
	*nextp = next;

}

#ifdef CONFIG_DYNAMIC_DEBUG
struct debug_buffer {
	ssize_t (*fill_func)(struct debug_buffer *);	/* fill method */
	struct usb_bus *bus;
	struct mutex mutex;	/* protect filling of buffer */
	size_t count;		/* number of characters filled into buffer */
	char *output_buf;
	size_t alloc_size;
};

static int debug_slot = MAX_HC_SLOTS;

static ssize_t fill_ep_ring_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;
	struct xhci_container_ctx *in_ctx, *out_ctx;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);
	for (i = 0; i < MAX_HC_SLOTS; i++) {
		if (!xhci->devs[i])
			continue;

		if (debug_slot != i && debug_slot != MAX_HC_SLOTS)
			continue;

		in_ctx = xhci->devs[i]->in_ctx;
		out_ctx = xhci->devs[i]->out_ctx;

		inc = scnprintf(next, size, "Slot %d input context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, in_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

		inc = scnprintf(next, size, "Slot %d output context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, out_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

		for (j = 0; j < XHCI_MAX_RINGS_CACHED; j++) {
			struct xhci_virt_ep *ep = &xhci->devs[i]->eps[j];
			struct xhci_ring *ep_ring = ep->ring;

			inc = scnprintf(next, size, "Slot %d ep_index %d endpoint ring @%p\n",
					i, j, ep_ring);
			TO_NEXT(next, size, inc);
			if (ep) xhci_dbgfs_ep_rings(xhci, i, j, ep, &next, &size);
		}
	}

	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

static ssize_t fill_event_ring_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);

	inc = scnprintf(next, size, "ERST memory map follows:\n");
	TO_NEXT(next, size, inc);

	xhci_dbgfs_erst(xhci, &xhci->erst, &next, &size);

	inc = scnprintf(next, size, "Dump Event Ring @%p\n", xhci->event_ring);
	TO_NEXT(next, size, inc);

	xhci_dbgfs_ring_ptrs(xhci, xhci->event_ring, &next, &size);

	xhci_dbgfs_ring(xhci, xhci->event_ring, &next, &size);

	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

static ssize_t fill_cmd_ring_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);

	inc = scnprintf(next, size, "Dump Command Ring @%p\n", xhci->cmd_ring);
	TO_NEXT(next, size, inc);

	xhci_dbgfs_ring_ptrs(xhci, xhci->cmd_ring, &next, &size);
	xhci_dbgfs_cmd_ptrs(xhci, &next, &size);
	xhci_dbgfs_ring(xhci, xhci->cmd_ring, &next, &size);

	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

static ssize_t fill_context_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;
	struct xhci_container_ctx *in_ctx, *out_ctx;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);
	for (i = 0; i < MAX_HC_SLOTS; i++) {
		if (!xhci->devs[i])
			continue;

		if (debug_slot != i && debug_slot != MAX_HC_SLOTS)
			continue;

		in_ctx = xhci->devs[i]->in_ctx;
		out_ctx = xhci->devs[i]->out_ctx;

		inc = scnprintf(next, size, "Slot %d input context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, in_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

		inc = scnprintf(next, size, "Slot %d output context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, out_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

	}
	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

static ssize_t fill_registers_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;
	struct xhci_container_ctx *in_ctx, *out_ctx;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);

	xhci_dbgfs_print_registers(xhci, &next, &size);

	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

static ssize_t fill_dump_all_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct xhci_hcd		*xhci;
	unsigned long		flags;
	unsigned		inc, size;
	char			*next;
	int i,j;
	struct xhci_container_ctx *in_ctx, *out_ctx;

	hcd = bus_to_hcd(buf->bus);
	xhci = hcd_to_xhci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&xhci->lock, flags);

	xhci_dbgfs_print_registers(xhci, &next, &size);

	inc = scnprintf(next, size, "Dump Command Ring @%p\n", xhci->cmd_ring);
	TO_NEXT(next, size, inc);

	xhci_dbgfs_ring_ptrs(xhci, xhci->cmd_ring, &next, &size);
	xhci_dbgfs_cmd_ptrs(xhci, &next, &size);
	xhci_dbgfs_ring(xhci, xhci->cmd_ring, &next, &size);


	inc = scnprintf(next, size, "ERST memory map follows:\n");
	TO_NEXT(next, size, inc);

	xhci_dbgfs_erst(xhci, &xhci->erst, &next, &size);

	inc = scnprintf(next, size, "Dump Event Ring @%p\n", xhci->event_ring);
	TO_NEXT(next, size, inc);

	xhci_dbgfs_ring_ptrs(xhci, xhci->event_ring, &next, &size);

	xhci_dbgfs_ring(xhci, xhci->event_ring, &next, &size);

	for (i = 0; i < MAX_HC_SLOTS; i++) {
		if (!xhci->devs[i])
			continue;
		in_ctx = xhci->devs[i]->in_ctx;
		out_ctx = xhci->devs[i]->out_ctx;

		inc = scnprintf(next, size, "Slot %d input context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, in_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

		inc = scnprintf(next, size, "Slot %d output context\n", i);
		TO_NEXT(next, size, inc);
		xhci_dbgfs_ctx(xhci, out_ctx, XHCI_MAX_RINGS_CACHED, &next, &size);

		for (j = 0; j < XHCI_MAX_RINGS_CACHED; j++) {
			struct xhci_virt_ep *ep = &xhci->devs[i]->eps[j];
			struct xhci_ring *ep_ring = ep->ring;

			inc = scnprintf(next, size, "Slot %d ep_index %d endpoint ring @%p\n",
					i, j, ep_ring);
			TO_NEXT(next, size, inc);
			if (ep) xhci_dbgfs_ep_rings(xhci, i, j, ep, &next, &size);
		}
	}

	spin_unlock_irqrestore (&xhci->lock, flags);

	inc = scnprintf(next, size, "Print Done (buffer use %d/%d bytes)..\n",
			buf->alloc_size - size, buf->alloc_size);
	TO_NEXT(next, size, inc);

	return strlen(buf->output_buf);
}

/* troubleshooting help: expose state in debugfs */

static int debug_ep_ring_open(struct inode *, struct file *);
static int debug_event_ring_open(struct inode *, struct file *);
static int debug_cmd_ring_open(struct inode *, struct file *);
static int debug_context_open(struct inode *, struct file *);
static int debug_registers_open(struct inode *, struct file *);
static int debug_dump_all_open(struct inode *, struct file *);

static ssize_t debug_output(struct file*, char __user*, size_t, loff_t*);
static int debug_close(struct inode *, struct file *);

static ssize_t debug_set_slot_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos);

static const struct file_operations debug_ep_ring_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_ep_ring_open,
	.read		= debug_output,
	.write		= debug_set_slot_write,
	.release	= debug_close,
	.llseek		= default_llseek,
};
static const struct file_operations debug_event_ring_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_event_ring_open,
	.read		= debug_output,
	.release	= debug_close,
	.llseek		= default_llseek,
};
static const struct file_operations debug_cmd_ring_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_cmd_ring_open,
	.read		= debug_output,
	.release	= debug_close,
	.llseek		= default_llseek,
};
static const struct file_operations debug_context_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_context_open,
	.read		= debug_output,
	.write		= debug_set_slot_write,
	.release	= debug_close,
	.llseek		= default_llseek,
};
static const struct file_operations debug_registers_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_registers_open,
	.read		= debug_output,
	.release	= debug_close,
	.llseek		= default_llseek,
};
static const struct file_operations debug_dump_all_fops = {
	.owner		= THIS_MODULE,
	.open		= debug_dump_all_open,
	.read		= debug_output,
	.release	= debug_close,
	.llseek		= default_llseek,
};

static struct debug_buffer *alloc_buffer(struct usb_bus *bus,
				ssize_t (*fill_func)(struct debug_buffer *))
{
	struct debug_buffer *buf;

	buf = kzalloc(sizeof(struct debug_buffer), GFP_KERNEL);

	if (buf) {
		buf->bus = bus;
		buf->fill_func = fill_func;
		mutex_init(&buf->mutex);
		buf->alloc_size = 100*PAGE_SIZE;
	}

	return buf;
}

static int fill_buffer(struct debug_buffer *buf)
{
	int ret = 0;

	if (!buf->output_buf)
		buf->output_buf = vmalloc(buf->alloc_size);

	if (!buf->output_buf) {
		ret = -ENOMEM;
		goto out;
	}

	ret = buf->fill_func(buf);

	if (ret >= 0) {
		buf->count = ret;
		ret = 0;
	}

out:
	return ret;
}

static ssize_t debug_output(struct file *file, char __user *user_buf,
			    size_t len, loff_t *offset)
{
	struct debug_buffer *buf = file->private_data;
	int ret = 0;

	mutex_lock(&buf->mutex);
	if (buf->count == 0) {
		ret = fill_buffer(buf);
		if (ret != 0) {
			mutex_unlock(&buf->mutex);
			goto out;
		}
	}
	mutex_unlock(&buf->mutex);

	ret = simple_read_from_buffer(user_buf, len, offset,
				      buf->output_buf, buf->count);

out:
	return ret;
}

static int debug_close(struct inode *inode, struct file *file)
{
	struct debug_buffer *buf = file->private_data;

	if (buf) {
		vfree(buf->output_buf);
		kfree(buf);
	}

	return 0;
}

static int debug_ep_ring_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_ep_ring_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

static ssize_t debug_set_slot_write(struct file *file,
		const char __user *ubuf, size_t count, loff_t *ppos)
{
	static struct dentry *reg_file = NULL;
	struct debug_buffer *dbuf = file->private_data;
	char			buf[32];
	int 			ret;

	if (copy_from_user(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		return -EFAULT;

	if (!strncmp(buf, "all", 3)) {
		debug_slot = MAX_HC_SLOTS;
	} else {
		int id;
		ret = sscanf(buf, "%d", &id);
		if (ret >= 1 && id >= 0 && id <= MAX_HC_SLOTS) {
			debug_slot = id;
		} else {
			pr_err("Error: to set slot id = %d (MAX = %d)\n", id, MAX_HC_SLOTS);
		}
	}

	return count;
}

static int debug_event_ring_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_event_ring_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

static int debug_cmd_ring_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_cmd_ring_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

static int debug_context_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_context_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

static int debug_registers_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_registers_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

static int debug_dump_all_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private, fill_dump_all_buffer);

	return file->private_data ? 0 : -ENOMEM;
}

void create_xhci_debug_files(struct xhci_hcd *xhci)
{
	struct usb_bus *bus = &xhci_to_hcd(xhci)->self;

	if (!xhci_debug_root) {
		xhci_debug_root = debugfs_create_dir("xhci", usb_debug_root);
		if (!xhci_debug_root) {
			xhci_err(xhci, "Create debugfs dir xhci Fail\n");
			return;
		}
	}

	xhci->debug_dir = debugfs_create_dir(bus->bus_name, xhci_debug_root);
	if (!xhci->debug_dir)
		return;

	if (!debugfs_create_file("ep_ring", S_IRUGO | S_IWUSR, xhci->debug_dir, bus,
						&debug_ep_ring_fops))
		goto file_error;

	if (!debugfs_create_file("event_ring", S_IRUGO, xhci->debug_dir, bus,
						&debug_event_ring_fops))
		goto file_error;

	if (!debugfs_create_file("cmd_ring", S_IRUGO, xhci->debug_dir, bus,
						&debug_cmd_ring_fops))
		goto file_error;

	if (!debugfs_create_file("context", S_IRUGO | S_IWUSR, xhci->debug_dir, bus,
						&debug_context_fops))
		goto file_error;

	if (!debugfs_create_file("registers", S_IRUGO, xhci->debug_dir, bus,
						    &debug_registers_fops))
		goto file_error;

	if (!debugfs_create_file("dump_all", S_IRUGO, xhci->debug_dir, bus,
						&debug_dump_all_fops))
		goto file_error;

	return;

file_error:
	debugfs_remove_recursive(xhci->debug_dir);
}

void remove_xhci_debug_files(struct xhci_hcd *xhci)
{
	if (xhci->debug_dir) {
		debugfs_remove_recursive(xhci->debug_dir);
		xhci->debug_dir = NULL;
	}
}
#endif
