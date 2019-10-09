/*
 * ve1.c
 *
 * linux device driver for VE1.
 *
 * Copyright (C) 2006 - 2013  REALTEK INC.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/wait.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/kfifo.h>
#include <linux/fs.h>
#include <linux/export.h>
#include <linux/miscdevice.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <soc/realtek/rtk_cpu.h>

#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif

#ifdef CONFIG_POWER_CONTROL
#include <linux/power-control.h>
#endif

#include "ve1config.h"
#include "ve1.h"
#include "compat_ve1.h"
#include "../puwrap.h"

//#define ENABLE_DEBUG_MSG
#ifdef ENABLE_DEBUG_MSG
#define DPRINTK(args...) pr_info(args);
#else
#define DPRINTK(args...)
#endif /* ENABLE_DEBUG_MSG */

#define DEV_NAME "[RTK_VE1]"
#define DISABLE_ORIGIN_SUSPEND
#define USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT

/* definitions to be changed as customer  configuration */
/* if you want to have clock gating scheme frame by frame */
/* #define VPU_SUPPORT_CLOCK_CONTROL */

/* if the driver want to use interrupt service from kernel ISR */
#define VPU_SUPPORT_ISR

/* if the platform driver knows the name of this driver */
/* VPU_PLATFORM_DEVICE_NAME */
#define VPU_SUPPORT_PLATFORM_DRIVER_REGISTER

/* if this driver knows the dedicated video memory address */
#ifndef CONFIG_RTK_RESERVE_MEMORY
#ifdef CONFIG_RTK_PLATFORM_FPGA
#define VPU_SUPPORT_RESERVED_VIDEO_MEMORY
#endif
#endif

#define VPU_PLATFORM_DEVICE_NAME "vdec"
#define VPU_CLK_NAME "vcodec"
#define VPU_DEV_NAME "vpu"

/* if the platform driver knows this driver */
/* the definition of VPU_REG_BASE_ADDR and VPU_REG_SIZE are not meaningful */

#define VPU_REG_BASE_ADDR 0x98040000
#define VPU_REG_SIZE (0x4000*MAX_NUM_VPU_CORE)
#define MS_TO_NS(x) (x * 1E6L)

#ifdef VPU_SUPPORT_ISR
#define VE1_IRQ_NUM (85)
#define VE2_IRQ_NUM (86)
#endif

/* this definition is only for realtek FPGA board env */
/* so for SOC env of customers can be ignored */

#ifndef VM_RESERVED	/*for kernel up to 3.7.0 version*/
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif

typedef struct vpu_drv_context_t {
	struct fasync_struct *async_queue;
	unsigned long interrupt_reason_ve1;
#ifdef SUPPORT_MULTI_INST_INTR
	unsigned long interrupt_reason_ve2[MAX_NUM_INSTANCE];
#else
	unsigned long interrupt_reason_ve2;
#endif
	unsigned long interrupt_reason_ve3;
	/* !<< device reference count. Not instance count */
	u32 open_count;
} vpu_drv_context_t;

/* To track the allocated memory buffer */
typedef struct vpudrv_buffer_pool_t {
	struct list_head list;
	struct vpudrv_buffer_t vb;
	struct file *filp;
} vpudrv_buffer_pool_t;

/* To track the instance index and buffer in instance pool */
typedef struct vpudrv_instanace_list_t {
	struct list_head list;
	unsigned long inst_idx;
	unsigned long core_idx;
	struct file *filp;
} vpudrv_instanace_list_t;

typedef struct vpudrv_instance_pool_t {
	unsigned char codecInstPool[MAX_NUM_INSTANCE][MAX_INST_HANDLE_SIZE];
	long long pendingInstIdxPlus1;
	void *pendingInst;
} vpudrv_instance_pool_t;

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
#define VPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE 0x0b800000 //(62*1024*1024)
#define VPU_DRAM_PHYSICAL_BASE 0x03200000 //0x86C00000
#include "vmm.h"
static video_mm_t s_vmem;
static vpudrv_buffer_t s_video_memory = {0};
#endif /*VPU_SUPPORT_RESERVED_VIDEO_MEMORY*/

static int vpu_hw_reset(u32 coreIdx);
#ifdef CONFIG_POWER_CONTROL
static void vpu_pctrl_off(struct power_control *pctrl);
static void vpu_pctrl_on(struct power_control *pctrl);
static struct power_control *vpu_pctrl_get(u32 coreIdx);
#endif /* CONFIG_POWER_CONTROL */

/* end customer definition */
static vpudrv_buffer_t s_instance_pool = {0};
static vpudrv_buffer_t s_common_memory = {0};
static vpu_drv_context_t s_vpu_drv_context;
static struct miscdevice s_vpu_dev;

static struct clk *s_vpu_clk_ve1;
static struct clk *s_vpu_clk_ve2;
static struct clk *s_vpu_clk_ve2_bpu;
static struct clk *s_vpu_clk_ve3;
static struct clk *s_vpu_clk_sysh;
static struct clk *s_vpu_pll_ve1;
static struct clk *s_vpu_pll_ve2;
static struct device *p_vpu_dev;
static int s_vpu_open_ref_count;

#ifdef VPU_SUPPORT_ISR
static int s_ve1_irq = VE1_IRQ_NUM;
static int s_ve2_irq = VE2_IRQ_NUM;
#endif /* VPU_SUPPORT_ISR */

#ifdef CONFIG_POWER_CONTROL
static struct power_control *s_pctrl_ve1;
static struct power_control *s_pctrl_ve2;
static struct power_control *s_pctrl_ve3;
#endif /* CONFIG_POWER_CONTROL */

static int ve_cti_en = 1;
/* FIX ME after ver.B IC */
static int ve_idle_en = 0;

static vpudrv_buffer_t s_vpu_register = {0};
static vpudrv_buffer_t s_dc_register = {0};
static vpudrv_buffer_t s_bond_register = {0};

static atomic_t s_interrupt_flag_ve1;
static wait_queue_head_t s_interrupt_wait_q_ve1;
#ifdef SUPPORT_MULTI_INST_INTR
static atomic_t s_interrupt_flag_ve2[MAX_NUM_INSTANCE];
static wait_queue_head_t s_interrupt_wait_q_ve2[MAX_NUM_INSTANCE];
typedef struct kfifo kfifo_t;
static kfifo_t s_interrupt_pending_q_ve2[MAX_NUM_INSTANCE];
#else
static atomic_t s_interrupt_flag_ve2;
static wait_queue_head_t s_interrupt_wait_q_ve2;
#endif
static atomic_t s_interrupt_flag_ve3;
static wait_queue_head_t s_interrupt_wait_q_ve3;

static spinlock_t s_vpu_lock = __SPIN_LOCK_UNLOCKED(s_vpu_lock);
static spinlock_t s_ve1_lock = __SPIN_LOCK_UNLOCKED(s_ve1_lock);
static spinlock_t s_ve2_lock = __SPIN_LOCK_UNLOCKED(s_ve2_lock);
static spinlock_t s_ve3_lock = __SPIN_LOCK_UNLOCKED(s_ve3_lock);
static DEFINE_SEMAPHORE(s_vpu_sem);
static struct list_head s_vbp_head = LIST_HEAD_INIT(s_vbp_head);
static struct list_head s_inst_list_head = LIST_HEAD_INIT(s_inst_list_head);

static vpu_bit_firmware_info_t s_bit_firmware_info[MAX_NUM_VPU_CORE];

#define BIT_BASE 0x0000
#define BIT_INT_STS (BIT_BASE + 0x010)
#define BIT_INT_REASON (BIT_BASE + 0x174)
#define BIT_INT_CLEAR (BIT_BASE + 0x00C)
#define VE_CTRL_REG (BIT_BASE + 0x3000)
#define VE_CTI_GRP_REG (BIT_BASE + 0x3004)
#define VE_INT_STS_REG (BIT_BASE + 0x3020)

#define W5_REG_BASE 0x0000
#define W5_VPU_INT_CLEAR (W5_REG_BASE + 0x003C)
#define W5_VPU_INT_STS (W5_REG_BASE + 0x0044)
#define W5_VPU_INT_REASON (W5_REG_BASE + 0x004c)
#define W5_VPU_INT_REASON_CLEAR (W5_REG_BASE + 0x0034)
#ifdef SUPPORT_MULTI_INST_INTR
#define W5_RET_BS_EMPTY_INST        (W5_REG_BASE + 0x01E4)
#define W5_RET_QUEUE_CMD_DONE_INST  (W5_REG_BASE + 0x01E8)
#define W5_RET_DONE_INSTANCE_INFO   (W5_REG_BASE + 0x01FC)
typedef enum {
    INT_WAVE5_INIT_VPU          = 0,
    INT_WAVE5_WAKEUP_VPU        = 1,
    INT_WAVE5_SLEEP_VPU         = 2,
    INT_WAVE5_CREATE_INSTANCE   = 3,
    INT_WAVE5_FLUSH_INSTANCE    = 4,
    INT_WAVE5_DESTORY_INSTANCE  = 5,
    INT_WAVE5_INIT_SEQ          = 6,
    INT_WAVE5_SET_FRAMEBUF      = 7,
    INT_WAVE5_DEC_PIC           = 8,
    INT_WAVE5_ENC_PIC           = 8,
    INT_WAVE5_ENC_SET_PARAM     = 9,
    INT_WAVE5_DEC_QUERY         = 14,
    INT_WAVE5_BSBUF_EMPTY       = 15,
    INT_WAVE5_BSBUF_FULL        = 15,
} Wave5InterruptBit;
#endif

#define W5_VE_CTRL_REG (W5_REG_BASE + 0x3E00)
#define W5_VE_CTI_GRP_REG (W5_REG_BASE + 0x3E04)

#ifdef CONFIG_PM
/* implement to power management functions */
#define BIT_CODE_RUN (BIT_BASE + 0x000)
#define BIT_CODE_DOWN (BIT_BASE + 0x004)
#define BIT_CODE_RESET (BIT_BASE + 0x014)
#define BIT_BUSY_FLAG (BIT_BASE + 0x160)
#define BIT_RUN_COMMAND (BIT_BASE + 0x164)
#define BIT_RUN_INDEX (BIT_BASE + 0x168)
#define BIT_RUN_COD_STD (BIT_BASE + 0x16C)

/* WAVE5 registers */
#define W5_VPU_BUSY_STATUS (W5_REG_BASE + 0x0070)

#define W5_RET_SUCCESS (W5_REG_BASE + 0x0110)
#define W5_RET_FAIL_REASON (W5_REG_BASE + 0x0114)

/* WAVE5 INIT, WAKEUP */
#define W5_PO_CONF (W5_REG_BASE + 0x0000)
#define W5_VCPU_CUR_PC	 (W5_REG_BASE + 0x0004)

#define W5_VPU_INT_ENABLE (W5_REG_BASE + 0x0048)

#define W5_RESET_REQ (W5_REG_BASE + 0x0050)
#define W5_RESET_STATUS (W5_REG_BASE + 0x0054)

#define W5_VPU_REMAP_CTRL (W5_REG_BASE + 0x0060)
#define W5_VPU_REMAP_VADDR	(W5_REG_BASE + 0x0064)
#define W5_VPU_REMAP_PADDR (W5_REG_BASE + 0x0068)
#define W5_VPU_REMAP_PROC_START (W5_REG_BASE + 0x006C)
#define W5_VPU_BUSY_STATUS (W5_REG_BASE + 0x0070)

#define W5_REMAP_CODE_INDEX 0

enum {
	W5_INT_INIT_VPU = 0,
	W5_INT_DEC_PIC_HDR = 1,
	W5_INT_FINI_SEQ = 2,
	W5_INT_DEC_PIC = 3,
	W5_INT_SET_FRAMEBUF = 4,
	W5_INT_FLUSH_DEC = 5,
	W5_INT_GET_FW_VERSION = 9,
	W5_INT_QUERY_DEC = 10,
	W5_INT_SLEEP_VPU = 11,
	W5_INT_WAKEUP_VPU = 12,
	W5_INT_CHANGE_INT = 13,
	W5_INT_CREATE_INSTANCE = 14,
	/*!<< Bitstream buffer empty */
	W5_INT_BSBUF_EMPTY = 15,
	W5_INT_ENC_SLICE_INT = 15,
};

#define W5_HW_OPTION (W5_REG_BASE + 0x0124)
#define W5_CODE_SIZE (W5_REG_BASE + 0x011C)
/* Note: W5_INIT_CODE_BASE_ADDR should be aligned to 4KB */
#define W5_ADDR_CODE_BASE (W5_REG_BASE + 0x0118)
#define W5_CODE_PARAM (W5_REG_BASE + 0x0120)
/* Note: W5_INIT_STACK_BASE_ADDR should be aligned to 4KB */
#define W5_ADDR_STACK_BASE (W5_REG_BASE + 0x012C)
#define W5_STACK_SIZE (W5_REG_BASE + 0x0130)
#define W5_INIT_VPU_TIME_OUT_CNT (W5_REG_BASE + 0x0134)

/* WAVE5 Wave5BitIssueCommand */
#define W5_CORE_INDEX (W5_REG_BASE + 0x0104)
#define W5_INST_INDEX (W5_REG_BASE + 0x0108)
#define W5_COMMAND (W5_REG_BASE + 0x0100)
#define W5_VPU_HOST_INT_REQ (W5_REG_BASE + 0x0038)

/* Product register */
#define VPU_PRODUCT_CODE_REGISTER   (BIT_BASE + 0x1044)

#ifndef DISABLE_ORIGIN_SUSPEND
static u32 s_vpu_reg_store[MAX_NUM_VPU_CORE][64];
#endif
#endif /* CONFIG_PM */

/*
 * common struct and definition
 */
#define ReadVpuRegister(addr, core) *(volatile unsigned int *)(s_vpu_register.virt_addr + (0x4000 * core) + addr)
#define WriteVpuRegister(addr, val, core) *(volatile unsigned int *)(s_vpu_register.virt_addr + (0x4000 * core) + addr) = (unsigned int)val
#define WriteVpu(addr, val) *(volatile unsigned int *)(addr) = (unsigned int)val;

struct clk *vpu_clk_get(struct device *dev, u32 coreIdx)
{
	if (coreIdx == 0)
		return clk_get(dev, "clk_ve1");
	else if (coreIdx == 1)
		return clk_get(dev, "clk_ve2");
	else
		return clk_get(dev, "clk_ve3");
	//return clk_get(dev, VPU_CLK_NAME);
}

void vpu_clk_put(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk)))
		clk_put(clk);
}

unsigned long vpu_clk_get_rate(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))) {
		DPRINTK("%s vpu_clk_get_rate\n", DEV_NAME);
		return clk_get_rate(clk);
	}

	return 0;
}

int vpu_clk_enable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))) {
#if 0 /* the bellow is for EVB.*/
		{
			struct clk *s_vpuext_clk = NULL;
			s_vpuext_clk = clk_get(NULL, "vcore");
			if (s_vpuext_clk) {
				DPRINTK("%s vcore clk=%p\n", DEV_NAME, s_vpuext_clk);
				clk_enable(s_vpuext_clk);
			}

			DPRINTK("%s vbus clk=%p\n", DEV_NAME, s_vpuext_clk);
			if (s_vpuext_clk) {
				s_vpuext_clk = clk_get(NULL, "vbus");
				clk_enable(s_vpuext_clk);
			}
		}
#endif /* for EVB. */

		DPRINTK("%s vpu_clk_enable\n", DEV_NAME);
		return clk_prepare_enable(clk)/*clk_enable(clk)*/;
	}

	return 0;
}

void vpu_clk_disable(struct clk *clk)
{
	if (!(clk == NULL || IS_ERR(clk))) {
		DPRINTK("%s vpu_clk_disable\n", DEV_NAME);
		//clk_disable(clk);
		while (__clk_is_enabled(clk))
			clk_disable_unprepare(clk);
	}
}

static int vpu_clk_pll_set_rate(struct clk *clk, unsigned int rate)
{
	struct clk *pclk;

	/* check if the parent clk is clk_sysh */
	pclk = clk_get_parent(clk);
	if (clk_is_match(pclk, s_vpu_clk_sysh)) {
	        pr_warn("[VPUDRV] %s: set clk_sysh is not allowed\n", __func__);
		return -EPERM;
	}

	/* set rate */
	clk_set_rate(clk, rate);

	return 0;
}

static void ve1_wrapper_setup(unsigned int coreIdx)
{
	unsigned int ctrl_1;
	unsigned int ctrl_2;

	/* coreIdx == 0 or coreIdx == 2 */
	if ((coreIdx & (1 << 0)) != 0 || (coreIdx & (1 << 2)) != 0) {
		ctrl_1 = ReadVpuRegister(VE_CTRL_REG, 0);
		ctrl_2 = ReadVpuRegister(VE_CTI_GRP_REG, 0);
		ctrl_1 |= (ve_cti_en << 1 | ve_idle_en << 6);
		/* ve1_cti_cmd_depth for 1296 timing issue */
		ctrl_2 = (ctrl_2 & ~(0x3f << 24)) | (0x1a << 24);
		WriteVpuRegister(VE_CTRL_REG, ctrl_1, 0);
		WriteVpuRegister(VE_CTI_GRP_REG, ctrl_2, 0);
		if ((coreIdx & (1 << 2)) != 0) {
			WriteVpuRegister(VE_CTRL_REG, ctrl_1, 2);
		}
	}

	/* coreIdx == 1 */
	if ((coreIdx & (1 << 1)) != 0) {
		ctrl_1 = ReadVpuRegister(W5_VE_CTRL_REG, 1);
		ctrl_2 = ReadVpuRegister(W5_VE_CTI_GRP_REG, 1);
		ctrl_1 |= (ve_cti_en << 1 | ve_idle_en << 6);
		/* ve2_cti_cmd_depth for 1296 timing issue */
		ctrl_2 = (ctrl_2 & ~(0x3f << 24)) | (0x1a << 24);
		WriteVpuRegister(W5_VE_CTRL_REG, ctrl_1, 1);
		WriteVpuRegister(W5_VE_CTI_GRP_REG, ctrl_2, 1);
	}
}

int vpu_hw_reset(u32 coreIdx)
{
	struct reset_control *rstc;

#if 1 /* RTK, workaround for demo */
	DPRINTK("%s request vpu reset from application\n", DEV_NAME);

	if (coreIdx == 0)
		rstc = reset_control_get(p_vpu_dev, "ve1");
	else if (coreIdx == 1)
		rstc = reset_control_get(p_vpu_dev, "ve2");
	else
		rstc = reset_control_get(p_vpu_dev, "ve3");
	if (IS_ERR_OR_NULL(rstc))
	{
		DPRINTK("%s failed to get reset control for core %d\n", DEV_NAME, coreIdx);
	}
	else {
		reset_control_reset(rstc);
		reset_control_put(rstc);
	}

	ve1_wrapper_setup((1 << coreIdx));
#endif
	return 0;
}

static int vpu_alloc_dma_buffer(vpudrv_buffer_t *vb)
{
	unsigned int ret;

	if (!vb)
		return -1;

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	UNUSED_PARAMETER(ret);
	vb->phys_addr = (unsigned long)vmem_alloc(&s_vmem, vb->size, 0);
	if ((unsigned long)vb->phys_addr  == (unsigned long)-1) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, vb->size);
		return -1;
	}

	vb->base = (unsigned long)(s_video_memory.base + (vb->phys_addr - s_video_memory.phys_addr));
#elif defined(CONFIG_RTK_RESERVE_MEMORY)
	ret = pu_alloc_dma_buffer(vb->size, &vb->phys_addr, &vb->base, vb->mem_type);
	if (ret == -1) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, vb->size);
		return -1;
	}
#else
	UNUSED_PARAMETER(ret);
	vb->base = (unsigned long)dma_alloc_coherent(s_vpu_dev.this_device, PAGE_ALIGN(vb->size), (dma_addr_t *) (&vb->phys_addr), GFP_DMA | GFP_KERNEL);
	if ((void *)(vb->base) == NULL) {
		pr_err("%s Physical memory allocation error size=%d\n", DEV_NAME, vb->size);
		return -1;
	}
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */

	DPRINTK("%s base:0x%lx, phy_addr:0x%lx, size:%d\n", DEV_NAME, vb->base, vb->phys_addr, vb->size);
	return 0;
}

static void vpu_free_dma_buffer(vpudrv_buffer_t *vb)
{
	if (!vb)
		return;

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (vb->base)
		vmem_free(&s_vmem, vb->phys_addr, 0);
#elif defined(CONFIG_RTK_RESERVE_MEMORY)
	pu_free_dma_buffer(vb->base, vb->phys_addr);
#else
	if (vb->base) {
		dma_free_coherent(s_vpu_dev.this_device, PAGE_ALIGN(vb->size), (void *)vb->base, vb->phys_addr);
	}
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */
}

/* size=40 for Android M */
#define PTHREAD_MUTEX_T_HANDLE_SIZE 40

static int vpu_free_instances(struct file *filp)
{
	vpudrv_instanace_list_t *vil, *n;
	vpudrv_instance_pool_t *vip;
	void *vip_base;
	int instance_pool_size_per_core;
	void *vdi_mutexes_base;
	const int PTHREAD_MUTEX_T_DESTROY_VALUE = 0xdead10cc;

	DPRINTK("%s vpu_free_instances\n", DEV_NAME);

	/* s_instance_pool.size  assigned to the size of all core once call VDI_IOCTL_GET_INSTANCE_POOL by user. */
	instance_pool_size_per_core = (s_instance_pool.size/MAX_NUM_VPU_CORE);

	list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
		if (vil->filp == filp) {
			int i, j;
			for (i = 0; i < MAX_NUM_INSTANCE; i++) /* reset dovi flag */
			{
				for (j = 0; j < MAX_NUM_VPU_CORE; j++)
				{
					pu_set_dovi_flag(j, i, 0);
				}
			}

			vip_base = (void *)(s_instance_pool.base + (instance_pool_size_per_core*vil->core_idx));
			DPRINTK("%s vpu_free_instances detect instance crash instIdx=%d, coreIdx=%d, vip_base=%p, instance_pool_size_per_core=%d\n", DEV_NAME, (int)vil->inst_idx, (int)vil->core_idx, vip_base, (int)instance_pool_size_per_core);
			vip = (vpudrv_instance_pool_t *)vip_base;

			if (vip) {
				/* only first 4 byte is key point(inUse of CodecInst in vpuapi) to free the corresponding instance. */
				memset(&vip->codecInstPool[vil->inst_idx], 0x00, 4);

				if (vil->inst_idx == (vip->pendingInstIdxPlus1-1) && vip->pendingInst != 0) {
					pr_warn("%s vil->inst_idx:%d, vil->core_idx:%d is pending, clear in here\n", DEV_NAME, (int)vil->inst_idx, (int)vil->core_idx);
					vip->pendingInst = 0;
					vip->pendingInstIdxPlus1 = 0;
				}

				vdi_mutexes_base = (vip_base + (instance_pool_size_per_core - PTHREAD_MUTEX_T_HANDLE_SIZE*4));
				DPRINTK("%s vpu_free_instances : force to destroy vdi_mutexes_base=%p in userspace \n", DEV_NAME, vdi_mutexes_base);
				if (vdi_mutexes_base) {
					int i;
					for (i = 0; i < 4; i++) {
						memcpy(vdi_mutexes_base, &PTHREAD_MUTEX_T_DESTROY_VALUE, PTHREAD_MUTEX_T_HANDLE_SIZE);
						vdi_mutexes_base += PTHREAD_MUTEX_T_HANDLE_SIZE;
					}
				}
			}
			s_vpu_open_ref_count--;
			list_del(&vil->list);
			kfree(vil);
		}
	}
	return 1;
}

static int vpu_free_buffers(struct file *filp)
{
	vpudrv_buffer_pool_t *pool, *n;
	vpudrv_buffer_t vb;

	DPRINTK("%s vpu_free_buffers\n", DEV_NAME);

	list_for_each_entry_safe(pool, n, &s_vbp_head, list) {
		if (pool->filp == filp) {
			vb = pool->vb;
			if (vb.base) {
				vpu_free_dma_buffer(&vb);
				list_del(&pool->list);
				kfree(pool);
			}
		}
	}

	return 0;
}

static irqreturn_t ve1_irq_handler(int irq, void *dev_id)
{
	vpu_drv_context_t *dev = (vpu_drv_context_t *)dev_id;

	/* this can be removed. it also work in VPU_WaitInterrupt of API function */
	int core = 0;
	unsigned long interrupt_reason_ve1 = 0;
	unsigned int vpu_int_sts_ve1 = 0;
	unsigned long flags;
	int int_sts = ReadVpuRegister(VE_INT_STS_REG, 0);

	core = (int_sts & (1 << 0) ? 0 : 2);
	//DPRINTK("%s [+]%s\n", DEV_NAME, __func__);

	/* it means that we didn't get an information the current core from API layer. No core activated.*/
	if (s_bit_firmware_info[core].size == 0) {
		pr_err("[VPUDRV] :  s_bit_firmware_info[core].size is zero\n");
		return IRQ_HANDLED;
	}

	vpu_int_sts_ve1 = ReadVpuRegister(BIT_INT_STS, core);
	if (vpu_int_sts_ve1) {
		interrupt_reason_ve1 = ReadVpuRegister(BIT_INT_REASON, core);
		WriteVpuRegister(BIT_INT_REASON, 0, core);
		WriteVpuRegister(BIT_INT_CLEAR, 0x1, core);
	}

	//DPRINTK("%s VE1 intr_reason: 0x%08lx\n", DEV_NAME, dev->interrupt_reason_ve1);

	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN); /* notify the interrupt to user space */

	if (vpu_int_sts_ve1) {
		if (core == 0) {
			spin_lock_irqsave(&s_ve1_lock, flags);
			dev->interrupt_reason_ve1 = interrupt_reason_ve1;
			atomic_set(&s_interrupt_flag_ve1, 1);
			smp_wmb();
			spin_unlock_irqrestore(&s_ve1_lock, flags);
			wake_up_interruptible(&s_interrupt_wait_q_ve1);
		} else {
			spin_lock_irqsave(&s_ve3_lock, flags);
			dev->interrupt_reason_ve3 = interrupt_reason_ve1;
			atomic_set(&s_interrupt_flag_ve3, 1);
			smp_wmb();
			spin_unlock_irqrestore(&s_ve3_lock, flags);
			wake_up_interruptible(&s_interrupt_wait_q_ve3);
		}
		//DPRINTK("%s [-]%s\n", DEV_NAME, __func__);
	}

	return IRQ_HANDLED;
}

#ifdef SUPPORT_MULTI_INST_INTR
static inline u32 get_inst_idx(u32 reg_val)
{
	u32 inst_idx;
	int i;
	for (i=0; i < MAX_NUM_INSTANCE; i++)
	{
		if(((reg_val >> i)&0x01) == 1)
			break;
	}
	inst_idx = i;
	return inst_idx;
}

static u32 get_vpu_inst_idx(vpu_drv_context_t *dev, u32 *reason, u32 empty_inst, u32 done_inst, u32 other_inst)
{
	u32 inst_idx;
	u32 reg_val;
	u32 int_reason;

	int_reason = *reason;
	DPRINTK("%s [+]%s, int_reason=0x%x, empty_inst=0x%x, done_inst=0x%x\n", DEV_NAME, __func__, int_reason, empty_inst, done_inst);

	if (int_reason & (1 << INT_WAVE5_BSBUF_EMPTY))
	{
		reg_val = empty_inst;
		inst_idx = get_inst_idx(reg_val);
		*reason = (1 << INT_WAVE5_BSBUF_EMPTY);
		DPRINTK("%s	%s, W5_RET_BS_EMPTY_INST reg_val=0x%x, inst_idx=%d\n", DEV_NAME, __func__, reg_val, inst_idx);
		goto GET_VPU_INST_IDX_HANDLED;
	}

	if (int_reason & (1 << INT_WAVE5_DEC_PIC))
	{
		reg_val = done_inst;
		inst_idx = get_inst_idx(reg_val);
		*reason  = (1 << INT_WAVE5_DEC_PIC);
		DPRINTK("[VPUDRV]  %s, W5_RET_QUEUE_CMD_DONE_INST DEC_PIC reg_val=0x%x, inst_idx=%d\n", __func__, reg_val, inst_idx);
		goto GET_VPU_INST_IDX_HANDLED;
	}

	if (int_reason & (1 << INT_WAVE5_INIT_SEQ))
	{
		reg_val = done_inst;
		inst_idx = get_inst_idx(reg_val);
		*reason  = (1 << INT_WAVE5_INIT_SEQ);
		DPRINTK("[VPUDRV]  %s, W5_RET_QUEUE_CMD_DONE_INST INIT_SEQ reg_val=0x%x, inst_idx=%d\n", __func__, reg_val, inst_idx);
		goto GET_VPU_INST_IDX_HANDLED;
	}

	// if  interrupt is not for empty and dec_pic and init_seq.
	reg_val = (other_inst&0xFF);
	inst_idx = reg_val;
	*reason  = int_reason;
	DPRINTK("%s	%s, W5_RET_DONE_INSTANCE_INFO reg_val=0x%x, inst_idx=%d\n", DEV_NAME, __func__, reg_val, inst_idx);
GET_VPU_INST_IDX_HANDLED:

	DPRINTK("%s [-]%s, inst_idx=%d. *reason=0x%x\n", DEV_NAME, __func__, inst_idx, *reason);

	return inst_idx;
}
#endif
static irqreturn_t ve2_irq_handler(int irq, void *dev_id)
{
	vpu_drv_context_t *dev = (vpu_drv_context_t *)dev_id;

	/* this can be removed. it also work in VPU_WaitInterrupt of API function */
	int core = 1;
	unsigned int vpu_int_sts_ve2 = 0;
	unsigned long flags;
#ifdef SUPPORT_MULTI_INST_INTR
	u32 intr_reason = 0;
	u32 intr_inst_index = 0;
#endif

	//DPRINTK("%s [+]%s\n", DEV_NAME, __func__);

	if (s_bit_firmware_info[core].size == 0) {/* it means that we didn't get an information the current core from API layer. No core activated.*/
		pr_err("[VPUDRV] :  s_bit_firmware_info[core].size is zero\n");
		return IRQ_HANDLED;
	}

	vpu_int_sts_ve2 = ReadVpuRegister(W5_VPU_INT_STS, core);
	if (vpu_int_sts_ve2) {
#ifdef SUPPORT_MULTI_INST_INTR
		u32 intr_reason_reg;
		u32 empty_inst;
		u32 done_inst;
		u32 other_inst;

		intr_reason_reg = ReadVpuRegister(W5_VPU_INT_REASON, core);
		empty_inst = ReadVpuRegister(W5_RET_BS_EMPTY_INST, core);
		done_inst = ReadVpuRegister(W5_RET_QUEUE_CMD_DONE_INST, core);
		other_inst = ReadVpuRegister(W5_RET_DONE_INSTANCE_INFO, core);

		DPRINTK("%s %s reason=0x%x, empty_inst=0x%x, done_inst=0x%x, other_inst=0x%x \n", DEV_NAME,  __func__, intr_reason_reg, empty_inst, done_inst, other_inst);

		intr_reason = intr_reason_reg;

		intr_inst_index = get_vpu_inst_idx(dev, &intr_reason, empty_inst, done_inst, other_inst);
#ifdef SUPPORT_MULTI_INST_INTR_ERROR_CHECK
		if (intr_inst_index >= 0 && intr_inst_index < MAX_NUM_INSTANCE)
		{
#define FIX_MULTI_INSTANCE_CLEAR_BS_EMPTY_AT_HOST
#ifdef FIX_MULTI_INSTANCE_CLEAR_BS_EMPTY_AT_HOST
			if (intr_reason == (1 << INT_WAVE5_BSBUF_EMPTY))
			{
				empty_inst = empty_inst & ~(1 << intr_inst_index);
				WriteVpuRegister(W5_RET_BS_EMPTY_INST, empty_inst, core);
				DPRINTK("[VPUDRV]   %s, W5_RET_BS_EMPTY_INST Clear empty_inst=0x%x, intr_inst_index=%d\n", __func__, empty_inst, intr_inst_index);
			}
#endif
		}
		if (intr_inst_index >= 0 && intr_inst_index < MAX_NUM_INSTANCE) {
			if (!kfifo_is_full(&s_interrupt_pending_q_ve2[intr_inst_index])) {
				kfifo_in(&s_interrupt_pending_q_ve2[intr_inst_index], &intr_reason, sizeof(u32));
			}
			else {
				pr_err("%s :  kfifo_is_full kfifo_count=%d \n", DEV_NAME, kfifo_len(&s_interrupt_pending_q_ve2[intr_inst_index]));
			}
		}
		else {
			pr_err("%s :  intr_inst_index is wrong intr_inst_index=%d \n", DEV_NAME, intr_inst_index);
		}

#else
		kfifo_in(&s_interrupt_pending_q_ve2[intr_inst_index], &intr_reason, sizeof(u32));
#endif
		WriteVpuRegister(W5_VPU_INT_REASON_CLEAR, intr_reason, core);
#else
		unsigned long interrupt_reason_ve2 = 0;
		interrupt_reason_ve2 = ReadVpuRegister(W5_VPU_INT_REASON, core);
		WriteVpuRegister(W5_VPU_INT_REASON_CLEAR, interrupt_reason_ve2, core);
#endif
		WriteVpuRegister(W5_VPU_INT_CLEAR, 0x1, core);
	}
	DPRINTK("%s VE2 intr_reason: 0x%08lx, intr_inst_index:%d\n", DEV_NAME, intr_reason, intr_inst_index);

	if (dev->async_queue)
		kill_fasync(&dev->async_queue, SIGIO, POLL_IN);	/* notify the interrupt to user space */

	if (vpu_int_sts_ve2) {
#ifdef SUPPORT_MULTI_INST_INTR
#ifdef SUPPORT_MULTI_INST_INTR_ERROR_CHECK
		if (intr_inst_index >= 0 && intr_inst_index < MAX_NUM_INSTANCE) {
			spin_lock_irqsave(&s_ve2_lock, flags);
			atomic_set(&s_interrupt_flag_ve2[intr_inst_index], 1);
			spin_unlock_irqrestore(&s_ve2_lock, flags);
			wake_up_interruptible(&s_interrupt_wait_q_ve2[intr_inst_index]);
		}
#else
		spin_lock_irqsave(&s_ve2_lock, flags);
		atomic_set(&s_interrupt_flag_ve2[intr_inst_index], 1);
		spin_unlock_irqrestore(&s_ve2_lock, flags);
		wake_up_interruptible(&s_interrupt_wait_q_ve2[intr_inst_index]);
#endif
#else
		spin_lock_irqsave(&s_ve2_lock, flags);
		dev->interrupt_reason_ve2 = interrupt_reason_ve2;
		atomic_set(&s_interrupt_flag_ve2, 1);
		smp_wmb();
		spin_unlock_irqrestore(&s_ve2_lock, flags);
		wake_up_interruptible(&s_interrupt_wait_q_ve2);
#endif
		DPRINTK("%s [-]%s\n", DEV_NAME, __func__);
	}

	return IRQ_HANDLED;
}

static int vpu_open(struct inode *inode, struct file *filp)
{
	DPRINTK("%s [+] %s\n", DEV_NAME, __func__);
	spin_lock(&s_vpu_lock);

	s_vpu_drv_context.open_count++;

	filp->private_data = (void *)(&s_vpu_drv_context);
	spin_unlock(&s_vpu_lock);

	DPRINTK("%s [-] %s\n", DEV_NAME, __func__);

	return 0;
}

/*static int vpu_ioctl(struct inode *inode, struct file *filp, u_int cmd, u_long arg) // for kernel 2.6.9*/
static long vpu_ioctl(struct file *filp, u_int cmd, u_long arg)
{
	int ret = 0;
	struct vpu_drv_context_t *dev = (struct vpu_drv_context_t *)filp->private_data;

	switch (cmd) {
	case VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY:
	{
		vpudrv_buffer_pool_t *vbp;

		DPRINTK("%s [+]VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY\n", DEV_NAME);

		ret = down_interruptible(&s_vpu_sem);
		if (ret == 0) {
			vbp = kzalloc(sizeof(*vbp), GFP_KERNEL);
			if (!vbp) {
				up(&s_vpu_sem);
				return -ENOMEM;
			}

			ret = copy_from_user(&(vbp->vb), (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
			if (ret) {
				kfree(vbp);
				up(&s_vpu_sem);
				return -EFAULT;
			}

			ret = vpu_alloc_dma_buffer(&(vbp->vb));
			if (ret == -1) {
				ret = -ENOMEM;
				kfree(vbp);
				up(&s_vpu_sem);
				break;
			}

			ret = copy_to_user((void __user *)arg, &(vbp->vb), sizeof(vpudrv_buffer_t));
			if (ret) {
				kfree(vbp);
				ret = -EFAULT;
				up(&s_vpu_sem);
				break;
			}

			vbp->filp = filp;
			spin_lock(&s_vpu_lock);
			list_add(&vbp->list, &s_vbp_head);
			spin_unlock(&s_vpu_lock);

			up(&s_vpu_sem);
		}
		DPRINTK("%s [-]VDI_IOCTL_ALLOCATE_PHYSICAL_MEMORY\n", DEV_NAME);
	}
	break;
	case VDI_IOCTL_FREE_PHYSICALMEMORY:
	{
		vpudrv_buffer_pool_t *vbp, *n;
		vpudrv_buffer_t vb;

		DPRINTK("%s [+]VDI_IOCTL_FREE_PHYSICALMEMORY\n", DEV_NAME);

		ret = down_interruptible(&s_vpu_sem);
		if (ret == 0) {
			ret = copy_from_user(&vb, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
			if (ret) {
				up(&s_vpu_sem);
				return -EACCES;
			}

			if (vb.base)
				vpu_free_dma_buffer(&vb);

			spin_lock(&s_vpu_lock);
			list_for_each_entry_safe(vbp, n, &s_vbp_head, list) {
				if (vbp->vb.phys_addr == vb.phys_addr/*vbp->vb.base == vb.base*/) {
					list_del(&vbp->list);
					kfree(vbp);
					break;
				}
			}
			spin_unlock(&s_vpu_lock);

			up(&s_vpu_sem);
		}
		DPRINTK("%s [-]VDI_IOCTL_FREE_PHYSICALMEMORY\n", DEV_NAME);
	}
	break;
	case VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO:
	{
#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
		DPRINTK("%s [+]VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO\n", DEV_NAME);
		if (s_video_memory.base != 0) {
			ret = copy_to_user((void __user *)arg, &s_video_memory, sizeof(vpudrv_buffer_t));
			if (ret != 0)
				ret = -EFAULT;
		} else {
			ret = -EFAULT;
		}
		DPRINTK("%s [-]VDI_IOCTL_GET_RESERVED_VIDEO_MEMORY_INFO\n", DEV_NAME);
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */
	}
	break;

	case VDI_IOCTL_WAIT_INTERRUPT:
	{
		vpudrv_intr_info_t info;
		unsigned long flags;
#ifdef SUPPORT_MULTI_INST_INTR
		u32 intr_inst_index;
		u32 intr_reason_in_q;
		u32 interrupt_flag_in_q;
#endif
		DPRINTK("[VPUDRV][+]VDI_IOCTL_WAIT_INTERRUPT\n");
		ret = copy_from_user(&info, (vpudrv_intr_info_t *)arg, sizeof(vpudrv_intr_info_t));
		if (ret != 0)
			return -EFAULT;

		/* VE1 */
		if (info.core_idx == 0) {
			smp_rmb();
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q_ve1, atomic_read(&s_interrupt_flag_ve1) != 0, msecs_to_jiffies(info.timeout));
			if (!ret) {
				ret = -ETIME;
				break;
			}

			if (signal_pending(current)) {
				ret = -ERESTARTSYS;
				break;
			}

			//DPRINTK("[VPUDRV] s_interrupt_flag_ve1(%d), reason(0x%08lx)\n", atomic_read(&s_interrupt_flag_ve1), dev->interrupt_reason_ve1);
			spin_lock_irqsave(&s_ve1_lock, flags);
			atomic_set(&s_interrupt_flag_ve1, 0);
			smp_wmb();
			info.intr_reason = dev->interrupt_reason_ve1;
			dev->interrupt_reason_ve1 = 0;
			spin_unlock_irqrestore(&s_ve1_lock, flags);
		} else if (info.core_idx == 1) { /* VE2 */
#ifdef USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT
			ktime_t ktime;
			unsigned long delay_in_ms = 1L;
			ktime = ktime_set(0, MS_TO_NS(delay_in_ms));
			//ktime = ktime_set(0, MS_TO_NS((u64)info.timeout));
#endif /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */

#ifdef SUPPORT_MULTI_INST_INTR
			intr_inst_index = info.intr_inst_index;

			intr_reason_in_q = 0;
			interrupt_flag_in_q = kfifo_out(&s_interrupt_pending_q_ve2[intr_inst_index], &intr_reason_in_q, sizeof(u32));
			DPRINTK("%s interrupt_flag_in_q:%d, intr_inst_index:%d, intr_reason_in_q:%d, kfifo_count=%d\n", DEV_NAME, interrupt_flag_in_q, intr_inst_index, intr_reason_in_q, kfifo_len(&s_interrupt_pending_q_ve2[intr_inst_index]));
			if (interrupt_flag_in_q > 0)
			{
				dev->interrupt_reason_ve2[intr_inst_index] = intr_reason_in_q;
				DPRINTK("%s Interrupt Remain : intr_inst_index=%d, intr_reason_in_q=0x%x, interrupt_flag_in_q=%d\n", DEV_NAME, intr_inst_index, intr_reason_in_q, interrupt_flag_in_q);
				goto INTERRUPT_REMAIN_IN_QUEUE;
			}
#ifdef SUPPORT_MULTI_INST_INTR_ERROR_CHECK
			else {
				dev->interrupt_reason_ve2[intr_inst_index] = 0;
			}
#endif

#ifdef USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT
			ret = wait_event_interruptible_hrtimeout(s_interrupt_wait_q_ve2[intr_inst_index], atomic_read(&s_interrupt_flag_ve2[intr_inst_index]) != 0, ktime);
#else /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q_ve2[intr_inst_index], atomic_read(&s_interrupt_flag_ve2[intr_inst_index]) != 0, msecs_to_jiffies(info.timeout));
#endif /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */

#else /* SUPPORT_MULTI_INST_INTR */
			smp_rmb();
#ifdef USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT
			ret = wait_event_interruptible_hrtimeout(s_interrupt_wait_q_ve2, atomic_read(&s_interrupt_flag_ve2) != 0, ktime);
#else /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q_ve2, atomic_read(&s_interrupt_flag_ve2) != 0, msecs_to_jiffies(info.timeout));
#endif /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */
#endif /* SUPPORT_MULTI_INST_INTR */

#ifdef USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT
			if (ret) {
				ret = -ETIME;
				break;
			}
#else /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */
			if (!ret) {
				ret = -ETIME;
				break;
			}
#endif /* USE_HRTIMEOUT_INSTEAD_OF_TIMEOUT */

			if (signal_pending(current)) {
				ret = -ERESTARTSYS;
				break;
			}

#ifdef SUPPORT_MULTI_INST_INTR
			intr_reason_in_q = 0;
			interrupt_flag_in_q = kfifo_out(&s_interrupt_pending_q_ve2[intr_inst_index], &intr_reason_in_q, sizeof(u32));
			if (interrupt_flag_in_q > 0) {
				dev->interrupt_reason_ve2[intr_inst_index] = intr_reason_in_q;
			}
#endif

#ifdef SUPPORT_MULTI_INST_INTR
			DPRINTK("%s inst_index(%d), s_interrupt_flag(%d), reason(0x%08lx), kfifo_count=%d\n", DEV_NAME, intr_inst_index, s_interrupt_flag_ve2[intr_inst_index], dev->interrupt_reason_ve2[intr_inst_index], kfifo_len(&s_interrupt_pending_q_ve2[intr_inst_index]));
#else
			//DPRINTK("%s	s_interrupt_flag(%d), reason(0x%08lx)\n", DEV_NAME, s_interrupt_flag_ve2, dev->interrupt_reason_ve2);
#endif

INTERRUPT_REMAIN_IN_QUEUE:

			spin_lock_irqsave(&s_ve2_lock, flags);
#ifdef SUPPORT_MULTI_INST_INTR
			info.intr_reason = dev->interrupt_reason_ve2[intr_inst_index];
			atomic_set(&s_interrupt_flag_ve2[intr_inst_index], 0);
			dev->interrupt_reason_ve2[intr_inst_index] = 0;
#else
			atomic_set(&s_interrupt_flag_ve2, 0);
			smp_wmb();
			info.intr_reason = dev->interrupt_reason_ve2;
			dev->interrupt_reason_ve2 = 0;
#endif
			spin_unlock_irqrestore(&s_ve2_lock, flags);
		} else { /* VE3 */
			smp_rmb();
			ret = wait_event_interruptible_timeout(s_interrupt_wait_q_ve3, atomic_read(&s_interrupt_flag_ve3) != 0, msecs_to_jiffies(info.timeout));
			if (!ret) {
				ret = -ETIME;
				break;
			}

			if (signal_pending(current)) {
				ret = -ERESTARTSYS;
				break;
			}

			//DPRINTK("[VPUDRV] s_interrupt_flag_ve3(%d), reason(0x%08lx)\n", atomic_read(&s_interrupt_flag_ve3), dev->interrupt_reason_ve3);
			spin_lock_irqsave(&s_ve3_lock, flags);
			atomic_set(&s_interrupt_flag_ve3, 0);
			smp_wmb();
			info.intr_reason = dev->interrupt_reason_ve3;
			dev->interrupt_reason_ve3 = 0;
			spin_unlock_irqrestore(&s_ve3_lock, flags);
		}

		ret = copy_to_user((void __user *)arg, &info, sizeof(vpudrv_intr_info_t));
		DPRINTK("[VPUDRV][-]VDI_IOCTL_WAIT_INTERRUPT, info.intr_reason[%d]:0x%x\n", intr_inst_index, info.intr_reason);
		if (ret != 0)
			return -EFAULT;
	}
	break;
	case VDI_IOCTL_SET_CLOCK_GATE:
	{
		u32 clkgate;

		//DPRINTK("[VPUDRV][+]VDI_IOCTL_SET_CLOCK_GATE\n");
		if (get_user(clkgate, (u32 __user *) arg))
			return -EFAULT;
#ifdef VPU_SUPPORT_CLOCK_CONTROL
		if (clkgate)
			vpu_clk_enable(s_vpu_clk);
		else
			vpu_clk_disable(s_vpu_clk);
#endif /* VPU_SUPPORT_CLOCK_CONTROL */
		//DPRINTK("[VPUDRV][-]VDI_IOCTL_SET_CLOCK_GATE\n");
	}
	break;
	case VDI_IOCTL_GET_INSTANCE_POOL:
	{
		DPRINTK("%s [+]VDI_IOCTL_GET_INSTANCE_POOL\n", DEV_NAME);

		ret = down_interruptible(&s_vpu_sem);
		if (ret == 0) {
			if (s_instance_pool.base != 0) {
				ret = copy_to_user((void __user *)arg, &s_instance_pool, sizeof(vpudrv_buffer_t));
				if (ret != 0)
					ret = -EFAULT;
			} else {
				ret = copy_from_user(&s_instance_pool, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
				if (ret == 0) {
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
					s_instance_pool.size = PAGE_ALIGN(s_instance_pool.size);
					s_instance_pool.base = (unsigned long)vmalloc(s_instance_pool.size);
					s_instance_pool.phys_addr = s_instance_pool.base;

					if (s_instance_pool.base != 0) {
#else
					if (vpu_alloc_dma_buffer(&s_instance_pool) != -1) {
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
						memset((void *)s_instance_pool.base, 0x0, s_instance_pool.size); /*clearing memory*/
						ret = copy_to_user((void __user *)arg, &s_instance_pool, sizeof(vpudrv_buffer_t));
						if (ret == 0) {
							/* success to get memory for instance pool */
							up(&s_vpu_sem);
							break;
						}
					}

				}
				ret = -EFAULT;
			}

			up(&s_vpu_sem);
		}

		DPRINTK("%s [-]VDI_IOCTL_GET_INSTANCE_POOL\n", DEV_NAME);
	}
	break;
	case VDI_IOCTL_GET_COMMON_MEMORY:
	{
		DPRINTK("%s [+]VDI_IOCTL_GET_COMMON_MEMORY\n", DEV_NAME);
		if (s_common_memory.base != 0) {
			ret = copy_to_user((void __user *)arg, &s_common_memory, sizeof(vpudrv_buffer_t));
			if (ret != 0)
				ret = -EFAULT;
		} else {
			ret = copy_from_user(&s_common_memory, (vpudrv_buffer_t *)arg, sizeof(vpudrv_buffer_t));
			if (ret == 0) {
				if (vpu_alloc_dma_buffer(&s_common_memory) != -1) {
					ret = copy_to_user((void __user *)arg, &s_common_memory, sizeof(vpudrv_buffer_t));
					if (ret == 0) {
						/* success to get memory for common memory */
						break;
					}
				}
			}

			ret = -EFAULT;
		}
		DPRINTK("%s [-]VDI_IOCTL_GET_COMMON_MEMORY\n", DEV_NAME);
	}
	break;
	case VDI_IOCTL_OPEN_INSTANCE:
	{
		vpudrv_inst_info_t inst_info;
		vpudrv_instanace_list_t *vil, *n;

		vil = kzalloc(sizeof(*vil), GFP_KERNEL);
		if (!vil)
			return -ENOMEM;

		if (copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t))) {
			kfree(vil);
			return -EFAULT;
		}

		vil->inst_idx = inst_info.inst_idx;
		vil->core_idx = inst_info.core_idx;
		vil->filp = filp;

		spin_lock(&s_vpu_lock);
		list_add(&vil->list, &s_inst_list_head);

		inst_info.inst_open_count = 0; /* counting the current open instance number */
		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			if (vil->core_idx == inst_info.core_idx)
				inst_info.inst_open_count++;
		}
		spin_unlock(&s_vpu_lock);

		s_vpu_open_ref_count++; /* flag just for that vpu is in opened or closed */

		if (copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t))) {
			kfree(vil);
			return -EFAULT;
		}

		DPRINTK("%s VDI_IOCTL_OPEN_INSTANCE core_idx=%d, inst_idx=%d, s_vpu_open_ref_count=%d, inst_open_count=%d\n", DEV_NAME, (int)inst_info.core_idx, (int)inst_info.inst_idx, s_vpu_open_ref_count, inst_info.inst_open_count);
	}
	break;
	case VDI_IOCTL_CLOSE_INSTANCE:
	{
		vpudrv_inst_info_t inst_info;
		vpudrv_instanace_list_t *vil, *n;

		DPRINTK("%s [+]VDI_IOCTL_CLOSE_INSTANCE\n", DEV_NAME);
		if (copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t)))
			return -EFAULT;

		spin_lock(&s_vpu_lock);
		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			if (vil->inst_idx == inst_info.inst_idx && vil->core_idx == inst_info.core_idx) {
				list_del(&vil->list);
				kfree(vil);
				break;
			}
		}

		inst_info.inst_open_count = 0; /* counting the current open instance number */
		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			if (vil->core_idx == inst_info.core_idx)
				inst_info.inst_open_count++;
		}
#ifdef SUPPORT_MULTI_INST_INTR
		if(inst_info.core_idx == 1)
			kfifo_reset(&s_interrupt_pending_q_ve2[inst_info.inst_idx]);
#endif
		spin_unlock(&s_vpu_lock);

		s_vpu_open_ref_count--; /* flag just for that vpu is in opened or closed */

		if (copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t)))
			return -EFAULT;

		DPRINTK("%s VDI_IOCTL_CLOSE_INSTANCE core_idx=%d, inst_idx=%d, s_vpu_open_ref_count=%d, inst_open_count=%d\n", DEV_NAME, (int)inst_info.core_idx, (int)inst_info.inst_idx, s_vpu_open_ref_count, inst_info.inst_open_count);
	}
	break;
	case VDI_IOCTL_GET_INSTANCE_NUM:
	{
		vpudrv_inst_info_t inst_info;
		vpudrv_instanace_list_t *vil, *n;
		DPRINTK("%s [+]VDI_IOCTL_GET_INSTANCE_NUM\n", DEV_NAME);

		ret = copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t));
		if (ret != 0)
			break;

		inst_info.inst_open_count = 0;

		spin_lock(&s_vpu_lock);
		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			if (vil->core_idx == inst_info.core_idx)
				inst_info.inst_open_count++;
		}
		spin_unlock(&s_vpu_lock);

		ret = copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t));

		DPRINTK("%s VDI_IOCTL_GET_INSTANCE_NUM core_idx=%d, inst_idx=%d, open_count=%d\n", DEV_NAME, (int)inst_info.core_idx, (int)inst_info.inst_idx, inst_info.inst_open_count);

	}
	break;
	case VDI_IOCTL_RESET:
	{
		u32 coreIdx;
		if (get_user(coreIdx, (u32 __user *) arg))
			return -EFAULT;
		vpu_hw_reset(coreIdx);
	}
	break;
	case VDI_IOCTL_GET_REGISTER_INFO:
	{
		DPRINTK("%s [+]VDI_IOCTL_GET_REGISTER_INFO\n", DEV_NAME);
		ret = copy_to_user((void __user *)arg, &s_vpu_register, sizeof(vpudrv_buffer_t));
		if (ret != 0)
			ret = -EFAULT;
		DPRINTK("%s [-]VDI_IOCTL_GET_REGISTER_INFO s_vpu_register.phys_addr=0x%lx, s_vpu_register.virt_addr=0x%lx, s_vpu_register.size=%d\n", DEV_NAME, s_vpu_register.phys_addr, s_vpu_register.virt_addr, s_vpu_register.size);
	}
	break;
	/* RTK ioctl */
	case VDI_IOCTL_SET_RTK_CLK_GATING:
	{
		vpu_clock_info_t clockInfo;
		struct clk *s_vpu_clk;
#ifdef CONFIG_POWER_CONTROL
		struct power_control *pctrl;
#endif
		DPRINTK("%s [+]VDI_IOCTL_SET_RTK_CLK_GATING\n", DEV_NAME);
		ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;

		/* VE1 */
		if (clockInfo.core_idx == 0) {
			s_vpu_clk = s_vpu_clk_ve1;
#ifdef CONFIG_POWER_CONTROL
			pctrl = s_pctrl_ve1;
#endif
		} else if (clockInfo.core_idx == 1) {/* VE2 */
			s_vpu_clk = s_vpu_clk_ve2;
#ifdef CONFIG_POWER_CONTROL
			pctrl = s_pctrl_ve2;
#endif
		} else {
			s_vpu_clk = s_vpu_clk_ve3;
#ifdef CONFIG_POWER_CONTROL
			pctrl = s_pctrl_ve3;
#endif
		}

		if (clockInfo.enable == 1) {
			if (s_vpu_clk == s_vpu_clk_ve3)
			{
#ifdef CONFIG_POWER_CONTROL
				vpu_pctrl_on(s_pctrl_ve1);
#endif
				vpu_clk_enable(s_vpu_clk_ve1);
			}

#ifdef CONFIG_POWER_CONTROL
			vpu_pctrl_on(pctrl);
#endif
			vpu_clk_enable(s_vpu_clk);
			if (s_vpu_clk == s_vpu_clk_ve2)
				vpu_clk_enable(s_vpu_clk_ve2_bpu);
			ve1_wrapper_setup((1 << clockInfo.core_idx));
		} else {
			vpu_clk_disable(s_vpu_clk);
#ifdef CONFIG_POWER_CONTROL
			vpu_pctrl_off(pctrl);
#endif
			if (s_vpu_clk == s_vpu_clk_ve3)
			{
				if (__clk_get_enable_count(s_vpu_clk_ve1) == 0)
				{
					vpu_clk_disable(s_vpu_clk_ve1);
#ifdef CONFIG_POWER_CONTROL
					vpu_pctrl_off(s_pctrl_ve1);
#endif
				}
			}
		}
		DPRINTK("%s [-]VDI_IOCTL_SET_RTK_CLK_GATING clockInfo.core_idx:%d, clockInfo.enable:%d\n", DEV_NAME, clockInfo.core_idx, clockInfo.enable);
	}
	break;
	case VDI_IOCTL_SET_RTK_CLK_PLL:
	{
		vpu_clock_info_t clockInfo;
		struct clk *s_vpu_clk;
		DPRINTK("%s [+]VDI_IOCTL_SET_RTK_CLK_PLL\n", DEV_NAME);
		ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;

		s_vpu_clk = clockInfo.core_idx == 1 ? s_vpu_clk_ve2 : s_vpu_clk_ve1;
		if (vpu_clk_pll_set_rate(s_vpu_clk, clockInfo.value))
			break;
		ve1_wrapper_setup((1 << clockInfo.core_idx));
		DPRINTK("%s [-]VDI_IOCTL_SET_RTK_CLK_PLL clockInfo.core_idx:%d, clockInfo.value:0x%x\n", DEV_NAME, clockInfo.core_idx, clockInfo.value);
	}
	break;
	case VDI_IOCTL_GET_RTK_CLK_PLL:
	{
		vpu_clock_info_t clockInfo;
		struct clk *s_vpu_clk;

		DPRINTK("%s [+]VDI_IOCTL_GET_RTK_CLK_PLL\n", DEV_NAME);
		ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;

		s_vpu_clk = clockInfo.core_idx == 1 ? s_vpu_clk_ve2 : s_vpu_clk_ve1;
		clockInfo.value = (unsigned int)clk_get_rate(s_vpu_clk);
		ret = copy_to_user((vpu_clock_info_t *)arg, &clockInfo, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;
		DPRINTK("%s [-]VDI_IOCTL_GET_RTK_CLK_PLL clockInfo.core_idx:%d, clockInfo.value:%d\n", DEV_NAME, clockInfo.core_idx, clockInfo.value);
	}
	break;
	case VDI_IOCTL_SET_RTK_CLK_SELECT:
	{
		vpu_clock_info_t clockInfo;
		struct clk *s_vpu_clk;
		struct clk *s_pclk = NULL;

		DPRINTK("%s [+]VDI_IOCTL_SET_RTK_CLK_SELECT\n", DEV_NAME);
		ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;

		s_vpu_clk = clockInfo.core_idx == 1 ? s_vpu_clk_ve2 : s_vpu_clk_ve1;
		switch(clockInfo.value)
		{
			case VE_PLL_SYSH:
				s_pclk = s_vpu_clk_sysh;
				break;
			case VE_PLL_VE1:
				s_pclk = s_vpu_pll_ve1;
				break;
			case VE_PLL_VE2:
				s_pclk = s_vpu_pll_ve2;
				break;
			default:
				pr_warn("%s  %s %d, wrong value:0x%x\n", DEV_NAME, __func__, __LINE__, clockInfo.value);
				break;
		}
		if (s_pclk != NULL)
			clk_set_parent(s_vpu_clk, s_pclk);

		DPRINTK("%s [-]VDI_IOCTL_SET_RTK_CLK_SELECT clockInfo.core_idx:%d, clockInfo.value:0x%x\n", DEV_NAME, clockInfo.core_idx, clockInfo.value);
	}
	break;
	case VDI_IOCTL_GET_RTK_CLK_SELECT:
	{
		vpu_clock_info_t clockInfo;
		struct clk *s_vpu_clk;
		struct clk *s_pclk;
		DPRINTK("%s [+]VDI_IOCTL_GET_RTK_CLK_SELECT\n", DEV_NAME);
		ret = copy_from_user(&clockInfo, (vpu_clock_info_t *)arg, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;

		s_vpu_clk = clockInfo.core_idx == 1 ? s_vpu_clk_ve2 : s_vpu_clk_ve1;
		s_pclk = clk_get_parent(s_vpu_clk);
		if (clk_is_match(s_pclk, s_vpu_clk_sysh))
		{
			clockInfo.value = (unsigned int)VE_PLL_SYSH;
		}
		else if (clk_is_match(s_pclk, s_vpu_pll_ve1))
		{
			clockInfo.value = (unsigned int)VE_PLL_VE1;
		}
		else if (clk_is_match(s_pclk, s_vpu_pll_ve2))
		{
			clockInfo.value = (unsigned int)VE_PLL_VE2;
		}

		ret = copy_to_user((vpu_clock_info_t *)arg, &clockInfo, sizeof(vpu_clock_info_t));
		if (ret != 0)
			break;
		DPRINTK("%s [-]VDI_IOCTL_GET_RTK_CLK_SELECT clockInfo.core_idx:%d, clockInfo.value:%d\n", DEV_NAME, clockInfo.core_idx, clockInfo.value);
	}
	break;
	case VDI_IOCTL_GET_RTK_SUPPORT_TYPE:
	{
		ret = copy_to_user((void __user *)arg, &s_bond_register, sizeof(vpudrv_buffer_t));
		if (ret != 0)
			ret = -EFAULT;
	}
	break;
	case VDI_IOCTL_GET_RTK_DCSYS_INFO:
	{
		ret = copy_to_user((void __user *)arg, &s_dc_register, sizeof(vpudrv_buffer_t));
		if (ret != 0)
			ret = -EFAULT;
	}
	break;
	case VDI_IOCTL_GET_RTK_ASIC_REVISION:
	{
		__put_user(get_rtd129x_cpu_revision()|get_rtd129x_cpu_id(), (unsigned int *) arg);
	}
	break;
	case VDI_IOCTL_SET_RTK_DOVI_FLAG:
	{
		vpudrv_dovi_info_t doviInfo;
		DPRINTK("%s [+]VDI_IOCTL_SET_RTK_DOVI_FLAG\n", DEV_NAME);
		ret = copy_from_user(&doviInfo, (vpudrv_dovi_info_t *)arg, sizeof(vpudrv_dovi_info_t));
		if (ret != 0)
			break;

		doviInfo.enable = pu_set_dovi_flag(doviInfo.core_idx, doviInfo.inst_idx, doviInfo.enable);

		ret = copy_to_user((vpudrv_dovi_info_t *)arg, &doviInfo, sizeof(vpudrv_dovi_info_t));
		if (ret != 0)
			break;
		DPRINTK("%s [-]VDI_IOCTL_SET_RTK_DOVI_FLAG doviInfo.core_idx:%d, doviInfo.inst_idx:%d, doviInfo.value:%d\n", DEV_NAME, doviInfo.core_idx, doviInfo.inst_idx, doviInfo.enable);
	}
	break;
	case VDI_IOCTL_GET_TOTAL_INSTANCE_NUM:
	{
		vpudrv_inst_info_t inst_info;
		vpudrv_instanace_list_t *vil, *n;
		DPRINTK("%s [+]VDI_IOCTL_GET_TOTAL_INSTANCE_NUM\n", DEV_NAME);

		ret = copy_from_user(&inst_info, (vpudrv_inst_info_t *)arg, sizeof(vpudrv_inst_info_t));
		if (ret != 0)
			break;

		inst_info.inst_open_count = 0;

		spin_lock(&s_vpu_lock);
		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			inst_info.inst_open_count++;
		}
		spin_unlock(&s_vpu_lock);

		ret = copy_to_user((void __user *)arg, &inst_info, sizeof(vpudrv_inst_info_t));

		DPRINTK("%s VDI_IOCTL_GET_TOTAL_INSTANCE_NUM core_idx=%d, inst_idx=%d, open_count=%d\n", DEV_NAME, (int)inst_info.core_idx, (int)inst_info.inst_idx, inst_info.inst_open_count);

	}
	break;
	default:
	{
		pr_err("%s No such IOCTL, cmd is %d\n", DEV_NAME, cmd);
	}
	break;
	}

	return ret;
}

static ssize_t vpu_read(struct file *filp, char __user *buf, size_t len, loff_t *ppos)
{
	return -1;
}

static int compat_get_vpu_bit_firmware_info_data(
	compat_vpu_bit_firmware_info_t __user *data32,
	vpu_bit_firmware_info_t __user *data)
{
	//compat_uint_t s;
	compat_uint_t c;
	compat_ulong_t r;
	compat_ushort_t b[512];
	int err;

	//err = get_user(s, &data32->size);
	//err |= put_user(s, &data->size);
	err = get_user(c, &data32->core_idx);
	err |= put_user(c, &data->core_idx);
	err |= get_user(r, &data32->reg_base_offset);
	err |= put_user(r, &data->reg_base_offset);
	err |= copy_from_user(b, data32->bit_code, sizeof(b));
	err |= copy_to_user(data->bit_code, b, sizeof(b));

	return err;
};

static ssize_t vpu_write(struct file *filp, const char __user *buf, size_t len, loff_t *ppos)
{

	/* DPRINTK("[VPUDRV] vpu_write len=%d\n", (int)len); */
	if (!buf) {
		pr_err("%s vpu_write buf = NULL error \n", DEV_NAME);
		return -EFAULT;
	}

	if (len == sizeof(vpu_bit_firmware_info_t) || len == sizeof(compat_vpu_bit_firmware_info_t))	{
		vpu_bit_firmware_info_t *bit_firmware_info;

		bit_firmware_info = kmalloc(sizeof(vpu_bit_firmware_info_t), GFP_KERNEL);
		if (!bit_firmware_info) {
			pr_err("%s vpu_write  bit_firmware_info allocation error\n", DEV_NAME);
			return -EFAULT;
		}

		if (len == sizeof(vpu_bit_firmware_info_t)) {
			if (copy_from_user(bit_firmware_info, buf, len)) {
				pr_err("%s vpu_write copy_from_user error for bit_firmware_info\n", DEV_NAME);
				kfree(bit_firmware_info);
				return -EFAULT;
			}
		}
#ifdef CONFIG_COMPAT
		 else {
			int err;
			compat_vpu_bit_firmware_info_t __user *data32;
			vpu_bit_firmware_info_t __user *data;

			data32 = (compat_vpu_bit_firmware_info_t __user *) buf;
			data = compat_alloc_user_space(sizeof(*data));
			if (data == NULL) {
				kfree(bit_firmware_info);
				return -EFAULT;
			}

			err = compat_get_vpu_bit_firmware_info_data(data32, data);
			if (err) {
				kfree(bit_firmware_info);
				return err;
			}

			if (copy_from_user(bit_firmware_info, data, sizeof(vpu_bit_firmware_info_t))) {
				pr_err("%s vpu_write copy_from_user error for bit_firmware_info\n", DEV_NAME);
				kfree(bit_firmware_info);
				return -EFAULT;
			}
			bit_firmware_info->size = sizeof(vpu_bit_firmware_info_t);
		}
#endif /* CONFIG_COMPAT */

		if (bit_firmware_info->size == sizeof(vpu_bit_firmware_info_t)) {
			DPRINTK("%s vpu_write set bit_firmware_info coreIdx=0x%x, reg_base_offset=0x%x size=0x%x, bit_code[0]=0x%x\n",
					DEV_NAME, bit_firmware_info->core_idx, (int)bit_firmware_info->reg_base_offset, bit_firmware_info->size, bit_firmware_info->bit_code[0]);

			if (bit_firmware_info->core_idx > MAX_NUM_VPU_CORE) {
				pr_err("%s vpu_write coreIdx[%d] is exceeded than MAX_NUM_VPU_CORE[%d]\n", DEV_NAME, bit_firmware_info->core_idx, MAX_NUM_VPU_CORE);
				kfree(bit_firmware_info);
				return -ENODEV;
			}

			memcpy((void *)&s_bit_firmware_info[bit_firmware_info->core_idx], bit_firmware_info, sizeof(vpu_bit_firmware_info_t));
			kfree(bit_firmware_info);

			return len;
		}

		kfree(bit_firmware_info);
	}

	return -1;
}

static int vpu_release(struct inode *inode, struct file *filp)
{
	int ret = 0;
	DPRINTK("%s vpu_release\n", DEV_NAME);

	ret = down_interruptible(&s_vpu_sem);
	if (ret == 0) {
		/* found and free the not handled buffer by user applications */
		vpu_free_buffers(filp);
		/* found and free the not closed instance by user applications */
		vpu_free_instances(filp);
		s_vpu_drv_context.open_count--;
		if (s_vpu_drv_context.open_count == 0) {
			if (s_instance_pool.base) {
				DPRINTK("%s free instance pool\n", DEV_NAME);
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
				vfree((const void *)s_instance_pool.base);
#else
				vpu_free_dma_buffer(&s_instance_pool);
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
				s_instance_pool.base = 0;
			}
#if 0 /* Fuchun 20150909, we must not free instance pool and common memory */
			if (s_common_memory.base) {
				DPRINTK("%s free common memory\n", DEV_NAME);
				vpu_free_dma_buffer(&s_common_memory);
				s_common_memory.base = 0;
			}
#endif
		}
	}
	up(&s_vpu_sem);

	return 0;
}

static int vpu_fasync(int fd, struct file *filp, int mode)
{
	struct vpu_drv_context_t *dev = (struct vpu_drv_context_t *)filp->private_data;
	return fasync_helper(fd, filp, mode, &dev->async_queue);
}

static int vpu_map_to_register(struct file *fp, struct vm_area_struct *vm)
{
	unsigned long pfn;

	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	pfn = vm->vm_pgoff;

	return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
}

static int vpu_map_to_physical_memory(struct file *fp, struct vm_area_struct *vm)
{
#ifdef CONFIG_RTK_RESERVE_MEMORY
	return pu_mmap_dma_buffer(vm);
#else
	vm->vm_flags |= VM_IO | VM_RESERVED;
	vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);

	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
#endif /* CONFIG_RTK_RESERVE_MEMORY */
}

static int vpu_map_to_instance_pool_memory(struct file *fp, struct vm_area_struct *vm)
{
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
	int ret;
	long length = vm->vm_end - vm->vm_start;
	unsigned long start = vm->vm_start;
	char *vmalloc_area_ptr = (char *)s_instance_pool.base;
	unsigned long pfn;

	vm->vm_flags |= VM_RESERVED;

	/* loop over all pages, map it page individually */
	while (length > 0) {
		pfn = vmalloc_to_pfn(vmalloc_area_ptr);
		ret = remap_pfn_range(vm, start, pfn, PAGE_SIZE, PAGE_SHARED);
		if (ret < 0) {
			return ret;
		}
		start += PAGE_SIZE;
		vmalloc_area_ptr += PAGE_SIZE;
		length -= PAGE_SIZE;
	}

	return 0;
#else
	vm->vm_flags |= VM_RESERVED;
	vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
	return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
}

/*!
 * @brief memory map interface for vpu file operation
 * @return  0 on success or negative error code on error
 */
static int vpu_mmap(struct file *fp, struct vm_area_struct *vm)
{
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
	if (vm->vm_pgoff == 0)
		return vpu_map_to_instance_pool_memory(fp, vm);

	if ((vm->vm_pgoff == (s_vpu_register.phys_addr>>PAGE_SHIFT))
	|| (vm->vm_pgoff == (s_bond_register.phys_addr>>PAGE_SHIFT))
	|| (vm->vm_pgoff == (s_dc_register.phys_addr>>PAGE_SHIFT)))
		return vpu_map_to_register(fp, vm);

	return vpu_map_to_physical_memory(fp, vm);
#else
	if (vm->vm_pgoff) {
		if (vm->vm_pgoff == (s_instance_pool.phys_addr>>PAGE_SHIFT))
			return vpu_map_to_instance_pool_memory(fp, vm);

		return vpu_map_to_physical_memory(fp, vm);
	} else {
		return vpu_map_to_register(fp, vm);
	}
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
}

struct file_operations vpu_fops = {
	.owner = THIS_MODULE,
	.open = vpu_open,
	.read = vpu_read,
	.write = vpu_write,
	/*.ioctl = vpu_ioctl, // for kernel 2.6.9*/
	.unlocked_ioctl = vpu_ioctl,
	.compat_ioctl = compat_vpu_ioctl,
	.release = vpu_release,
	.fasync = vpu_fasync,
	.mmap = vpu_mmap,
};


static int vpu_probe(struct platform_device *pdev)
{
	int err = 0;
	u32 bonding_value;
	unsigned long virt_addr;
	struct resource res;
	void __iomem *iobase;
	int irq;
	struct device_node *node = pdev->dev.of_node;
	struct reset_control *rstc_ve1, *rstc_ve2, *rstc_ve3;
#if 0 //Fuchun disable 20160204, set clock gating by vdi.c
	unsigned int val = 0;
#endif

	pr_info("%s vpu_probe\n", DEV_NAME);

	of_address_to_resource(node, 0, &res);
	iobase = of_iomap(node, 0);

	s_vpu_register.phys_addr = res.start;
	s_vpu_register.virt_addr = (unsigned long)iobase;
	s_vpu_register.size = res.end - res.start + 1;

	pr_info("%s vpu base address get from DTB physical base addr=0x%lx, virtual base=0x%lx, size=0x%x\n", DEV_NAME, s_vpu_register.phys_addr, s_vpu_register.virt_addr, s_vpu_register.size);

	of_address_to_resource(node, 1, &res);
	iobase = of_iomap(node, 1);

	s_dc_register.phys_addr = res.start;
	s_dc_register.virt_addr = (unsigned long)iobase;
	s_dc_register.size = res.end - res.start + 1;

	s_vpu_dev.minor = MISC_VE1_MINOR;
	s_vpu_dev.name = VPU_DEV_NAME;
	s_vpu_dev.fops = &vpu_fops;
	s_vpu_dev.parent = NULL;
	if (misc_register(&s_vpu_dev)) {
		pr_err("%s failed to register misc device.", DEV_NAME);
		goto ERROR_PROVE_DEVICE;
	}

	of_address_to_resource(node, 2, &res);
	iobase = of_iomap(node, 2);

	s_bond_register.phys_addr = res.start;
	s_bond_register.virt_addr = (unsigned long)iobase;
	s_bond_register.size = res.end - res.start + 1;

	virt_addr = (unsigned long)iobase;
	bonding_value = __raw_readl((volatile u8 *)virt_addr);

	pr_info("%s res.start:0x%llx, bonding_value:0x%x\n", DEV_NAME, res.start, bonding_value);

	s_vpu_clk_ve1 = vpu_clk_get(&pdev->dev, 0);
	s_vpu_clk_ve2 = vpu_clk_get(&pdev->dev, 1);
	s_vpu_clk_ve3 = vpu_clk_get(&pdev->dev, 2);
	s_vpu_clk_ve2_bpu = clk_get(&pdev->dev, "clk_ve2_bpu");
	s_vpu_clk_sysh = clk_get(&pdev->dev, "clk_sysh");
	s_vpu_pll_ve1 = clk_get(&pdev->dev, "pll_ve1");
	s_vpu_pll_ve2 = clk_get(&pdev->dev, "pll_ve2");

#ifdef CONFIG_POWER_CONTROL
	s_pctrl_ve1 = vpu_pctrl_get(0);
	s_pctrl_ve2 = vpu_pctrl_get(1);
	s_pctrl_ve3 = vpu_pctrl_get(2);
#endif

	p_vpu_dev = &pdev->dev;

#ifdef VPU_SUPPORT_CLOCK_CONTROL
	vpu_clk_enable(s_vpu_clk_ve1);
	vpu_clk_enable(s_vpu_clk_ve2);
	vpu_clk_enable(s_vpu_clk_ve2_bpu);
	vpu_clk_enable(s_vpu_clk_ve3);
#endif

	irq = irq_of_parse_and_map(node, 0);
	if (irq <= 0)
		panic("Can't parse IRQ");

	s_ve1_irq = irq;
	pr_info("%s s_ve1_irq:%d want to register ve1_irq_handler\n", DEV_NAME, s_ve1_irq);
	err = request_irq(s_ve1_irq, ve1_irq_handler, 0, "VE1_CODEC_IRQ", (void *)(&s_vpu_drv_context));
	err = 0;
	if (err != 0) {
		if (err == -EINVAL)
			pr_err("%s Bad s_ve1_irq number or handler\n", DEV_NAME);
		else if (err == -EBUSY)
			pr_err("%s s_ve1_irq <%d> busy, change your config\n", DEV_NAME, s_ve1_irq);
		goto ERROR_PROVE_DEVICE;
	}

	irq = irq_of_parse_and_map(node, 1);
	if (irq <= 0)
		panic("Can't parse IRQ");

	s_ve2_irq = irq;
	pr_info("%s s_ve2_irq:%d want to register ve2_irq_handler\n", DEV_NAME, s_ve2_irq);
	err = request_irq(s_ve2_irq, ve2_irq_handler, 0, "VE2_CODEC_IRQ", (void *)(&s_vpu_drv_context));
	if (err != 0) {
		if (err == -EINVAL)
			pr_err("%s Bad s_ve2_irq number or handler\n", DEV_NAME);
		else if (err == -EBUSY)
			pr_err("%s s_ve2_irq <%d> busy, change your config\n", DEV_NAME, s_ve2_irq);
		goto ERROR_PROVE_DEVICE;
	}

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	s_video_memory.size = VPU_INIT_VIDEO_MEMORY_SIZE_IN_BYTE;
	s_video_memory.phys_addr = VPU_DRAM_PHYSICAL_BASE;
	s_video_memory.base = (unsigned long)ioremap_nocache(s_video_memory.phys_addr, PAGE_ALIGN(s_video_memory.size));
	if (!s_video_memory.base) {
		pr_err("%s fail to remap video memory physical phys_addr=0x%x, base=0x%x, size=%d\n", DEV_NAME, (int)s_video_memory.phys_addr, (int)s_video_memory.base, (int)s_video_memory.size);
		goto ERROR_PROVE_DEVICE;
	}

	if (vmem_init(&s_vmem, s_video_memory.phys_addr, s_video_memory.size) < 0) {
		pr_err("%s fail to init vmem system\n", DEV_NAME);
		goto ERROR_PROVE_DEVICE;
	}
	pr_info("%s success to probe vpu device with reserved video memory phys_addr=0x%x, base = 0x%x\n", DEV_NAME, (int) s_video_memory.phys_addr, (int)s_video_memory.base);
#else
	pr_info("%s success to probe vpu device with non reserved video memory\n", DEV_NAME);
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */

#ifndef CONFIG_RTK_PLATFORM_FPGA
	/* RESET disable */
	rstc_ve1 = reset_control_get(&pdev->dev, "ve1");
	rstc_ve2 = reset_control_get(&pdev->dev, "ve2");
	rstc_ve3 = reset_control_get(&pdev->dev, "ve3");

	reset_control_deassert(rstc_ve1);
	reset_control_deassert(rstc_ve2);
	reset_control_deassert(rstc_ve3);

	reset_control_put(rstc_ve1);
	reset_control_put(rstc_ve2);
	reset_control_put(rstc_ve3);

#endif /* CONFIG_RTK_PLATFORM_FPGA */

#ifdef CONFIG_POWER_CONTROL
	vpu_pctrl_off(s_pctrl_ve1);
	vpu_pctrl_off(s_pctrl_ve2);
	vpu_pctrl_off(s_pctrl_ve3);
#endif /* CONFIG_POWER_CONTROL */

#if 0 /* Fuchun disable 20160204, set clock gating by vdi.c */
	val = ReadVpuRegister(VE_CTRL_REG, 0);
	val |= (ve_cti_en << 1 | ve_idle_en << 6);
	WriteVpuRegister(VE_CTRL_REG, val, 0);

	pr_info("%s VE1_CTRL_REG = 0x%08x (0x%08x)\n", DEV_NAME, val, ReadVpuRegister(VE_CTRL_REG, 0));

	val = ReadVpuRegister(W5_VE_CTRL_REG, 1);
	val |= (ve_cti_en << 1 | ve_idle_en << 6);
	WriteVpuRegister(W5_VE_CTRL_REG, val, 1);

	pr_info("%s VE2_CTRL_REG = 0x%08x (0x%08x)\n", DEV_NAME, val, ReadVpuRegister(W5_VE_CTRL_REG, 1));
#endif

	return 0;


ERROR_PROVE_DEVICE:

	misc_deregister(&s_vpu_dev);

	return err;
}

static int vpu_remove(struct platform_device *pdev)
{
	DPRINTK("%s vpu_remove\n", DEV_NAME);

#ifdef VPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	if (s_instance_pool.base) {
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
		vfree((const void *)s_instance_pool.base);
#else
		vpu_free_dma_buffer(&s_instance_pool);
#endif /* VPU_SUPPORT_PLATFORM_DRIVER_REGISTER */
		s_instance_pool.base = 0;
	}

	if (s_common_memory.base) {
		vpu_free_dma_buffer(&s_common_memory);
		s_common_memory.base = 0;
	}

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_video_memory.base) {
		iounmap((void *)s_video_memory.base);
		s_video_memory.base = 0;
		vmem_exit(&s_vmem);
	}
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */

	misc_deregister(&s_vpu_dev);

#ifdef VPU_SUPPORT_ISR
	if (s_ve1_irq)
		free_irq(s_ve1_irq, &s_vpu_drv_context);
	if (s_ve2_irq)
		free_irq(s_ve2_irq, &s_vpu_drv_context);
#endif /* VPU_SUPPORT_ISR */


	vpu_clk_put(s_vpu_clk_ve3);
	vpu_clk_put(s_vpu_clk_ve1);
	vpu_clk_put(s_vpu_clk_ve2);
	vpu_clk_put(s_vpu_clk_ve2_bpu);

#endif /* VPU_SUPPORT_PLATFORM_DRIVER_REGISTER */

	return 0;
}

#ifdef CONFIG_PM
/* DO NOT CHANGE */
#define WAVE5_STACK_SIZE (8*1024)
#define W5_MAX_CODE_BUF_SIZE (512*1024)
#define W5_CMD_INIT_VPU (0x0001)
#define W5_CMD_SLEEP_VPU (0x0400)
#define W5_CMD_WAKEUP_VPU (0x0800)

#ifndef DISABLE_ORIGIN_SUSPEND
static void Wave5BitIssueCommand(u32 cmd)
{
	WriteVpuRegister(W5_VPU_BUSY_STATUS, 1, 1);
	WriteVpuRegister(W5_CORE_INDEX,  0, 1);
	/* coreIdx = ReadVpuRegister(W5_VPU_BUSY_STATUS, 1);*/
	/* coreIdx = 0;*/
	/* WriteVpuRegister(W5_INST_INDEX,  (instanceIndex&0xffff)|(codecMode<<16), 1);*/
	WriteVpuRegister(W5_COMMAND, cmd, 1);
	WriteVpuRegister(W5_VPU_HOST_INT_REQ, 1, 1);

	return;
}
#endif /* DISABLE_ORIGIN_SUSPEND */

static int vpu_suspend(struct device *pdev)
{
	pr_info("%s Enter %s\n", DEV_NAME, __func__);

#ifdef CONFIG_POWER_CONTROL
	vpu_pctrl_on(s_pctrl_ve1);
	vpu_pctrl_on(s_pctrl_ve2);
	vpu_pctrl_on(s_pctrl_ve3);
#endif
	vpu_clk_enable(s_vpu_clk_ve1);
	vpu_clk_enable(s_vpu_clk_ve2);
	vpu_clk_enable(s_vpu_clk_ve2_bpu);
	vpu_clk_enable(s_vpu_clk_ve3);

	/* RTK wrapper */
	ve1_wrapper_setup((1 << 2) | (1 << 1) | 1);

	if (s_vpu_open_ref_count > 0) {
#ifdef DISABLE_ORIGIN_SUSPEND
		vpudrv_instanace_list_t *vil, *n;
		vpudrv_instance_pool_t *vip;
		void *vip_base;
		int instance_pool_size_per_core;
		vpudrv_buffer_pool_t *pool, *nn;
		vpudrv_buffer_t vb;
		s_vpu_drv_context.open_count = 0;
		s_vpu_open_ref_count = 0;

		/* s_instance_pool.size  assigned to the size of all core once call VDI_IOCTL_GET_INSTANCE_POOL by user. */
		instance_pool_size_per_core = (s_instance_pool.size/MAX_NUM_VPU_CORE);

		wake_up_interruptible_all(&s_interrupt_wait_q_ve1);
		atomic_set(&s_interrupt_flag_ve1, 0);
		wake_up_interruptible_all(&s_interrupt_wait_q_ve3);
		atomic_set(&s_interrupt_flag_ve3, 0);

#ifdef SUPPORT_MULTI_INST_INTR
		{
			int i;
			for (i=0; i<MAX_NUM_INSTANCE; i++) {
				wake_up_interruptible_all(&s_interrupt_wait_q_ve2[i]);
				atomic_set(&s_interrupt_flag_ve2[i], 0);
			}
		}
#else
		atomic_set(&s_interrupt_flag_ve2, 0);
#endif

		list_for_each_entry_safe(vil, n, &s_inst_list_head, list) {
			vip_base = (void *)(s_instance_pool.base + (instance_pool_size_per_core*vil->core_idx));
			vip = (vpudrv_instance_pool_t *)vip_base;
			if (vip) {
				/* only first 4 byte is key point(inUse of CodecInst in vpuapi) to free the corresponding instance. */
				memset(&vip->codecInstPool[vil->inst_idx], 0x00, 4);
			}
			list_del(&vil->list);
			kfree(vil);
		}

		list_for_each_entry_safe(pool, nn, &s_vbp_head, list) {
			vb = pool->vb;
			if (vb.base) {
				vpu_free_dma_buffer(&vb);
			}
			list_del(&pool->list);
			kfree(pool);
		}

		if (s_instance_pool.base) {
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
			vfree((const void *)s_instance_pool.base);
#else
			vpu_free_dma_buffer(&s_instance_pool);
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
			s_instance_pool.base = 0;
		}
#else /* else of DISABLE_ORIGIN_SUSPEND */
		int i;
		int core;
		unsigned long timeout = jiffies + HZ; /* vpu wait timeout to 1sec */
		int product_code = 0;

		for (core = 0; core < MAX_NUM_VPU_CORE; core++) {
			if (s_bit_firmware_info[core].size == 0)
				continue;
			product_code = ReadVpuRegister(VPU_PRODUCT_CODE_REGISTER, core);
			if (PRODUCT_CODE_W_SERIES(product_code)) {
				while (ReadVpuRegister(W5_VPU_BUSY_STATUS, core)) {
					if (time_after(jiffies, timeout)) {
						DPRINTK("%s SLEEP_VPU BUSY timeout", DEV_NAME);
						goto DONE_SUSPEND;
					}
				}
				Wave5BitIssueCommand(W5_CMD_SLEEP_VPU);

				while (ReadVpuRegister(W5_VPU_BUSY_STATUS, core)) {
					if (time_after(jiffies, timeout)) {
						DPRINTK("%s SLEEP_VPU BUSY timeout", DEV_NAME);
						goto DONE_SUSPEND;
					}
				}
				if (ReadVpuRegister(W5_RET_SUCCESS, core) == 0) {
					DPRINTK("%s SLEEP_VPU failed [0x%x]", DEV_NAME, ReadVpuRegister(W5_RET_FAIL_REASON, core));
					goto DONE_SUSPEND;
				}
			} else {
				while (ReadVpuRegister(BIT_BUSY_FLAG, core)) {
					if (time_after(jiffies, timeout))
						goto DONE_SUSPEND;
				}

				for (i = 0; i < 64; i++)
					s_vpu_reg_store[core][i] = ReadVpuRegister(BIT_BASE+(0x100+(i * 4)), core);
			}
		}
#endif /* end of DISABLE_ORIGIN_SUSPEND */
	}

	vpu_clk_disable(s_vpu_clk_ve3);
	vpu_clk_disable(s_vpu_clk_ve1);
	vpu_clk_disable(s_vpu_clk_ve2);
	vpu_clk_disable(s_vpu_clk_ve2_bpu);
#ifdef CONFIG_POWER_CONTROL
	vpu_pctrl_off(s_pctrl_ve3);
	vpu_pctrl_off(s_pctrl_ve1);
	vpu_pctrl_off(s_pctrl_ve2);
#endif /* CONFIG_POWER_CONTROL */

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return 0;

#ifndef DISABLE_ORIGIN_SUSPEND
DONE_SUSPEND:
#endif

	vpu_clk_disable(s_vpu_clk_ve3);
	vpu_clk_disable(s_vpu_clk_ve1);
	vpu_clk_disable(s_vpu_clk_ve2);
	vpu_clk_disable(s_vpu_clk_ve2_bpu);
#ifdef CONFIG_POWER_CONTROL
	vpu_pctrl_off(s_pctrl_ve3);
	vpu_pctrl_off(s_pctrl_ve1);
	vpu_pctrl_off(s_pctrl_ve2);
#endif /* CONFIG_POWER_CONTROL */

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return -EAGAIN;
}

static int vpu_resume(struct device *pdev)
{
	pr_info("%s Enter %s\n", DEV_NAME, __func__);

#ifdef CONFIG_POWER_CONTROL
	vpu_pctrl_on(s_pctrl_ve1);
	vpu_pctrl_on(s_pctrl_ve2);
	vpu_pctrl_on(s_pctrl_ve3);
#endif /* CONFIG_POWER_CONTROL */

	vpu_clk_enable(s_vpu_clk_ve1);
	vpu_clk_enable(s_vpu_clk_ve2);
	vpu_clk_enable(s_vpu_clk_ve2_bpu);
	vpu_clk_enable(s_vpu_clk_ve3);

	//RTK wrapper
	ve1_wrapper_setup((1 << 2) | (1 << 1) | 1);

#ifdef DISABLE_ORIGIN_SUSPEND
#else /* else of DISABLE_ORIGIN_SUSPEND */
	int i;
	int core;
	int regVal;
	int product_code = 0;
	unsigned long timeout = jiffies + HZ; /* vpu wait timeout to 1sec */
	unsigned long code_base;
	unsigned long stack_base;
	u32 val;
	u32 code_size;
	u32 stack_size;
	u32 remap_size;
	u32 hwOption  = 0;

	for (core = 0; core < MAX_NUM_VPU_CORE; core++) {

		if (s_bit_firmware_info[core].size == 0) {
			continue;
		}

		product_code = ReadVpuRegister(VPU_PRODUCT_CODE_REGISTER, core);

		if (PRODUCT_CODE_W_SERIES(product_code)) {

			code_base = s_common_memory.phys_addr;
			/* ALIGN TO 4KB */
			code_size = (W5_MAX_CODE_BUF_SIZE&~0xfff);
			if (code_size < s_bit_firmware_info[core].size*2) {
				goto DONE_WAKEUP;
			}
			stack_base = code_base + code_size;
			stack_size = WAVE5_STACK_SIZE;

			/*---- LOAD BOOT CODE*/
			//for (i = 0; i < 512; i++) {
			//	val = s_bit_firmware_info[core].bit_code[i];
			//	WriteVpu(code_base+(i*4), val);
			//}

			regVal = 0;
			WriteVpuRegister(W5_PO_CONF, regVal, core);

			/* Reset All blocks */
			regVal = 0x7ffffff;
			WriteVpuRegister(W5_RESET_REQ, regVal, core);	/*Reset All blocks*/

			/* Waiting reset done */
			while (ReadVpuRegister(W5_RESET_STATUS, core)) {
				if (time_after(jiffies, timeout))
					goto DONE_WAKEUP;
			}

			WriteVpuRegister(W5_RESET_REQ, 0, core);

			/* remap page size */
			remap_size = (code_size >> 12) & 0x1ff;
			regVal = 0x80000000 | (W5_REMAP_CODE_INDEX<<12) | (0 << 16) | (1<<11) | remap_size;
			WriteVpuRegister(W5_VPU_REMAP_CTRL,	 regVal, core);
			WriteVpuRegister(W5_VPU_REMAP_VADDR,	0x00000000, core);	/* DO NOT CHANGE! */
			WriteVpuRegister(W5_VPU_REMAP_PADDR,	code_base, core);
			WriteVpuRegister(W5_ADDR_CODE_BASE,	 code_base, core);
			WriteVpuRegister(W5_CODE_SIZE,		  code_size, core);
			WriteVpuRegister(W5_CODE_PARAM,		 0, core);
			WriteVpuRegister(W5_INIT_VPU_TIME_OUT_CNT,   timeout, core);

			/* Stack */
			WriteVpuRegister(W5_ADDR_STACK_BASE, stack_base, core);
			WriteVpuRegister(W5_STACK_SIZE,	  stack_size, core);
			WriteVpuRegister(W5_HW_OPTION, hwOption, core);

			/* Interrupt */
			regVal  = (1<<W5_INT_DEC_PIC_HDR);
			regVal |= (1<<W5_INT_DEC_PIC);
			regVal |= (1<<W5_INT_QUERY_DEC);
			regVal |= (1<<W5_INT_SLEEP_VPU);
			regVal |= (1<<W5_INT_BSBUF_EMPTY);

			WriteVpuRegister(W5_VPU_INT_ENABLE,  regVal, core);

			Wave5BitIssueCommand(W5_CMD_INIT_VPU);
			WriteVpuRegister(W5_VPU_REMAP_PROC_START, 1, core);

			while (ReadVpuRegister(W5_VPU_BUSY_STATUS, core)) {
				if (time_after(jiffies, timeout))
					goto DONE_WAKEUP;
			}

			if (ReadVpuRegister(W5_RET_SUCCESS, core) == 0) {
				DPRINTK("%s WAKEUP_VPU failed [0x%x]", DEV_NAME, ReadVpuRegister(W5_RET_FAIL_REASON, core));
				goto DONE_WAKEUP;
			}
		} else {

			WriteVpuRegister(BIT_CODE_RUN, 0, core);

			/*---- LOAD BOOT CODE*/
			for (i = 0; i < 512; i++) {
				val = s_bit_firmware_info[core].bit_code[i];
				WriteVpuRegister(BIT_CODE_DOWN, ((i << 16) | val), core);
			}

			for (i = 0 ; i < 64 ; i++)
				WriteVpuRegister(BIT_BASE+(0x100+(i * 4)), s_vpu_reg_store[core][i], core);

			WriteVpuRegister(BIT_BUSY_FLAG, 1, core);
			WriteVpuRegister(BIT_CODE_RESET, 1, core);
			WriteVpuRegister(BIT_CODE_RUN, 1, core);

			while (ReadVpuRegister(BIT_BUSY_FLAG, core)) {
				if (time_after(jiffies, timeout))
					goto DONE_WAKEUP;
			}

		}

	}
#endif /* end of DISABLE_ORIGIN_SUSPEND */

	if (s_vpu_open_ref_count == 0) {
		vpu_clk_disable(s_vpu_clk_ve3);
		vpu_clk_disable(s_vpu_clk_ve1);
		vpu_clk_disable(s_vpu_clk_ve2);
		vpu_clk_disable(s_vpu_clk_ve2_bpu);
#ifdef CONFIG_POWER_CONTROL
		vpu_pctrl_off(s_pctrl_ve3);
		vpu_pctrl_off(s_pctrl_ve1);
		vpu_pctrl_off(s_pctrl_ve2);
#endif /* CONFIG_POWER_CONTROL */
	}

#ifndef DISABLE_ORIGIN_SUSPEND
DONE_WAKEUP:
#endif /* DISABLE_ORIGIN_SUSPEND */

	if (s_vpu_open_ref_count > 0) {
		vpu_clk_enable(s_vpu_clk_ve3);
		vpu_clk_enable(s_vpu_clk_ve1);
		vpu_clk_enable(s_vpu_clk_ve2);
		vpu_clk_enable(s_vpu_clk_ve2_bpu);
#ifdef CONFIG_POWER_CONTROL
		vpu_pctrl_off(s_pctrl_ve3);
		vpu_pctrl_off(s_pctrl_ve1);
		vpu_pctrl_off(s_pctrl_ve2);
#endif /* CONFIG_POWER_CONTROL */
	}

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return 0;
}
#else
static int vpu_suspend(struct device *pdev);
static int vpu_resume(struct device *pdev);
#endif /* CONFIG_PM */

static int __init vpu_init(void)
{
	int res = 0;

#ifdef SUPPORT_MULTI_INST_INTR
	int i;
#endif
	DPRINTK("%s begin vpu_init\n", DEV_NAME);
#ifdef SUPPORT_MULTI_INST_INTR
	for (i=0; i<MAX_NUM_INSTANCE; i++) {
		init_waitqueue_head(&s_interrupt_wait_q_ve2[i]);
	}

	for (i=0; i<MAX_NUM_INSTANCE; i++) {
#ifdef SUPPORT_MULTI_INST_INTR_ERROR_CHECK
#define MAX_INTERRUPT_QUEUE (16*MAX_NUM_INSTANCE)
#else
#define MAX_INTERRUPT_QUEUE 16
#endif
		res = kfifo_alloc(&s_interrupt_pending_q_ve2[i], MAX_INTERRUPT_QUEUE*sizeof(u32), GFP_KERNEL);
		if (res) {
			DPRINTK("%s kfifo_alloc failed 0x%x\n", DEV_NAME, res);
		}
	}
#else
	init_waitqueue_head(&s_interrupt_wait_q_ve2);
#endif

	init_waitqueue_head(&s_interrupt_wait_q_ve1);
	init_waitqueue_head(&s_interrupt_wait_q_ve3);
	s_common_memory.base = 0;
	s_instance_pool.base = 0;

	DPRINTK("%s end vpu_init result=0x%x\n", DEV_NAME, res);
	return res;
}

static void __exit vpu_exit(void)
{
#ifdef VPU_SUPPORT_PLATFORM_DRIVER_REGISTER
	DPRINTK("%s vpu_exit\n", DEV_NAME);
#else

	vpu_clk_put(s_vpu_clk_ve3);
	vpu_clk_put(s_vpu_clk_ve1);
	vpu_clk_put(s_vpu_clk_ve2);
	vpu_clk_put(s_vpu_clk_ve2_bpu);

	if (s_instance_pool.base) {
#ifdef USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY
		vfree((const void *)s_instance_pool.base);
#else
		vpu_free_dma_buffer(&s_instance_pool);
#endif /* USE_VMALLOC_FOR_INSTANCE_POOL_MEMORY */
		s_instance_pool.base = 0;
	}

	if (s_common_memory.base) {
		vpu_free_dma_buffer(&s_common_memory);
		s_common_memory.base = 0;
	}

#ifdef VPU_SUPPORT_RESERVED_VIDEO_MEMORY
	if (s_video_memory.base) {
		iounmap((void *)s_video_memory.base);
		s_video_memory.base = 0;

		vmem_exit(&s_vmem);
	}
#endif /* VPU_SUPPORT_RESERVED_VIDEO_MEMORY */

	misc_deregister(&s_vpu_dev);

#ifdef VPU_SUPPORT_ISR
	if (s_ve1_irq)
		free_irq(s_ve1_irq, &s_vpu_drv_context);
	if (s_ve2_irq)
		free_irq(s_ve2_irq, &s_vpu_drv_context);
#endif /* VPU_SUPPORT_ISR */

#ifdef SUPPORT_MULTI_INST_INTR
	{
		int i;
		for (i=0; i<MAX_NUM_INSTANCE; i++) {
			kfifo_free(&s_interrupt_pending_q_ve2[i]);
		}
	}
#endif
#endif /* VPU_SUPPORT_PLATFORM_DRIVER_REGISTER */

	return;
}

MODULE_AUTHOR("A customer using RTK VPU, Inc.");
MODULE_DESCRIPTION("VPU linux driver");
MODULE_LICENSE("GPL");

module_init(vpu_init);
module_exit(vpu_exit);

#ifdef CONFIG_POWER_CONTROL
struct power_control *vpu_pctrl_get(u32 coreIdx)
{
	if (coreIdx == 0)
		return power_control_get("pctrl_ve1");
	else if (coreIdx == 1)
		return power_control_get("pctrl_ve2");
	else
		return power_control_get("pctrl_ve3");
}

void vpu_pctrl_on(struct power_control *pctrl)
{
	if (!(pctrl == NULL || IS_ERR(pctrl))) {
		DPRINTK("%s vpu_pctrl_on\n", DEV_NAME);
		power_control_power_on(pctrl);
	}
}

void vpu_pctrl_off(struct power_control *pctrl)
{
	if (!(pctrl == NULL || IS_ERR(pctrl))) {
		DPRINTK("%s vpu_pctrl_off\n", DEV_NAME);
		power_control_power_off(pctrl);
	}
}
#endif /* CONFIG_POWER_CONTROL */

static const struct of_device_id rtk_ve1_dt_match[] = {
	{ .compatible = "Realtek,rtk16xx-ve1" },
	{}
};
MODULE_DEVICE_TABLE(of, rtk_ve1_dt_match);

const struct dev_pm_ops rtk_ve1_pmops = {
	.suspend = vpu_suspend,
	.resume = vpu_resume,
};

static struct platform_driver rtk_ve1_driver = {
	.driver = {
		.name = "rtk-ve1",
		.owner = THIS_MODULE,
		.of_match_table = rtk_ve1_dt_match,
		.pm = &rtk_ve1_pmops,
	},
	.probe = vpu_probe,
	.remove = vpu_remove,
};

module_platform_driver(rtk_ve1_driver);
