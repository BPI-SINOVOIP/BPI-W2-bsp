/* Copyright 2013 Google Inc. All Rights Reserved. */
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/sched.h>
#include <linux/semaphore.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>

#include <soc/realtek/rtk_cpu.h>

#ifdef CONFIG_POWER_CONTROL
#include <linux/power-control.h>
#endif

#include "ve3.h"
#include "compat_ve3.h"
#include "dwl_defs.h"
#include "../puwrap.h"

#define HANTRO_DEC_REGS 265

#define DEV_NAME "[RTK_VE3]"
#define HANTRO_DEC_FIRST_REG 0
#define HANTRO_DEC_LAST_REG	 HANTRO_DEC_REGS-1
#define HANTRO_DEV_NAME "ve3"

/* Logic module IRQs */
#define HXDEC_NO_IRQ -1
/* module defaults */
#define DEC_IO_SIZE (HANTRO_DEC_REGS * 4) /* bytes, PP regs included
within dec regs. */
#define DEC_IRQ HXDEC_NO_IRQ

static const int DecHwId[] = {0x6732};

unsigned long base_port = -1;
volatile u8 *base_address = NULL;

unsigned long s_pll_phy_register = 0;
unsigned long s_pll_virt_register = 0;
unsigned long s_pll_size_register = 0;
unsigned long s_bonding_phy_register = 0;
unsigned long s_bonding_size_register = 0;

u64 multicorebase[HXDEC_MAX_CORES] = {-1};

int ve3_irq = DEC_IRQ;
int elements = 0;

#ifndef VM_RESERVED	/*for kernel up to 3.7.0 version*/
# define  VM_RESERVED   (VM_DONTEXPAND | VM_DONTDUMP)
#endif

/* module_param(name, type, perm) */
module_param(base_port, ulong, 0);
module_param(ve3_irq, int, 0);
module_param_array(multicorebase, ulong, &elements, 0);

static int hantrodec_major = 0; /* dynamic allocation */
static struct miscdevice s_ve3_dev;

/* here's all the must remember stuff */
typedef struct{
	char *buffer;
	unsigned int iosize;
	volatile u8 *hwregs[HXDEC_MAX_CORES];
	int irq;
	int cores;
	struct fasync_struct *async_queue_dec;
	struct fasync_struct *async_queue_pp;
} hantrodec_t;

static hantrodec_t hantrodec_data; /* dynamic allocation? */

static int ReserveIO(void);
static void ReleaseIO(void);

static void ResetAsic(hantrodec_t * dev);

#ifdef HANTRODEC_DEBUG
static void dump_regs(hantrodec_t *dev);
#endif

/* IRQ handler */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18))
static irqreturn_t hantrodec_isr(int irq, void *dev_id, struct pt_regs *regs);
#else
static irqreturn_t hantrodec_isr(int irq, void *dev_id);
#endif

static u32 dec_regs[HXDEC_MAX_CORES][DEC_IO_SIZE/4];
static u32 asic_dec_regs[HXDEC_MAX_CORES][DEC_IO_SIZE/4];
struct semaphore dec_core_sem;

static int dec_irq = 0;
static int dec_release = 0;

static atomic_t irq_rx = ATOMIC_INIT(0);
static atomic_t irq_tx = ATOMIC_INIT(0);

static struct file* dec_owner[HXDEC_MAX_CORES];

static spinlock_t owner_lock = __SPIN_LOCK_UNLOCKED(owner_lock);

DECLARE_WAIT_QUEUE_HEAD(dec_wait_queue);

DECLARE_WAIT_QUEUE_HEAD(hw_queue);

#define DWL_CLIENT_TYPE_PP 4U
#define DWL_CLIENT_TYPE_VP9_DEC 11U
#define DWL_CLIENT_TYPE_HEVC_DEC 12U

static u32 cfg[HXDEC_MAX_CORES];

static struct clk *s_ve3_clk;
static struct reset_control *rstc_ve3 = NULL;
#ifdef CONFIG_POWER_CONTROL
static struct power_control *s_pctrl_ve3;
#endif

static void ve3_clk_disable(struct clk *clk);
static int ve3_clk_enable(struct clk *clk);
static struct clk *ve3_clk_get(struct device *dev);
static void ve3_clk_put(struct clk *clk);
#ifdef CONFIG_POWER_CONTROL
static void ve3_pctrl_off(struct power_control *pctrl);
static void ve3_pctrl_on(struct power_control *pctrl);
static struct power_control *ve3_pctrl_get(void);
#endif

static void ve3_wrapper_setup(volatile u8 * base)
{
	unsigned int ctrl_1 = __raw_readl(base+0x3F00);
	unsigned int ctrl_2 = __raw_readl(base+0x3F04);
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_B00)
		ctrl_1 = (ctrl_1 & ~0x7) | 0x3; /* ve3_ack_div_sel 'b011 = 8 */
	else
		ctrl_1 = (ctrl_1 & ~0x7) | 0x2; /* ve3_ack_div_sel 'b010 = 16 //HW has bug, we must use this value */
	ctrl_1 |= 0x10; /* ve3_axi2cti_en */
	ctrl_2 = (ctrl_2 & ~0x3f) | 0x1a; /* ve3_cti_cmd_depth for 1296 timing issue */
	__raw_writel(ctrl_1, (base+0x3F00));
	__raw_writel(ctrl_2, (base+0x3F04));
}

static void ve3_pll_setting(unsigned long offset, unsigned int value, unsigned int bOverwrite, unsigned int bEnable)
{
	if (s_pll_phy_register == 0 || s_pll_virt_register == 0 || s_pll_size_register == 0) {
		pr_warn("%s In[%s][%d] didn't get pll register\n", DEV_NAME, __FUNCTION__, __LINE__);
		return;
	} else if (offset > s_pll_size_register) {
		pr_warn("%s In[%s][%d] offset over than register size\n", DEV_NAME, __FUNCTION__, __LINE__);
		return;
	}

	if (bOverwrite == 1) {
		__raw_writel(value, (volatile u8 *)(s_pll_virt_register+offset));
	} else {
		if (bEnable)
			__raw_writel(__raw_readl((volatile u8 *)(s_pll_virt_register+offset)) | value, (volatile u8 *)(s_pll_virt_register+offset));
		else
			__raw_writel(__raw_readl((volatile u8 *)(s_pll_virt_register+offset)) & value, (volatile u8 *)(s_pll_virt_register+offset));
	}
}

static void ReadCoreConfig(hantrodec_t *dev)
{
	int i, c;
	u32 reg, tmp;

	memset(cfg, 0, sizeof(cfg));

	for(c = 0; c < dev->cores; c++) {
		/* Decoder configuration */
		reg = ioread32(dev->hwregs[c] + HANTRODEC_SYNTH_CFG_2 * 4);

		tmp = (reg >> DWL_HEVC_E) & 0x3U;
		if(tmp)
			pr_info("%s core[%d] has HEVC\n", DEV_NAME, c);
		cfg[c] |= tmp ? 1 << DWL_CLIENT_TYPE_HEVC_DEC : 0;

		tmp = (reg >> DWL_VP9_E) & 0x03U;
		if(tmp)
			pr_info("%s core[%d] has VP9\n", DEV_NAME, c);
		cfg[c] |= tmp ? 1 << DWL_CLIENT_TYPE_VP9_DEC : 0;

		/* Post-processor configuration */
		reg = ioread32(dev->hwregs[c] + HANTRODECPP_SYNTH_CFG * 4);

		tmp = (reg >> DWL_PP_E) & 0x01U;
		if(tmp)
			pr_info("%s core[%d] has PP\n", DEV_NAME, c);
		cfg[c] |= tmp ? 1 << DWL_CLIENT_TYPE_PP : 0;

		for(i = 0; i <= HANTRO_DEC_LAST_REG; i++)
			asic_dec_regs[c][i] = ioread32(dev->hwregs[c] + i*4);
	}
}

static int CoreHasFormat(const u32 *cfg, int core, u32 format)
{
	return (cfg[core] & (1 << format)) ? 1 : 0;
}

int GetDecCore(long core, hantrodec_t *dev, struct file* filp)
{
	int success = 0;
	unsigned long flags;

	spin_lock_irqsave(&owner_lock, flags);
	if(dec_owner[core] == NULL ) {
		dec_owner[core] = filp;
		success = 1;
	}

	spin_unlock_irqrestore(&owner_lock, flags);

	return success;
}

int GetDecCoreAny(long *core, hantrodec_t *dev, struct file* filp,
				  unsigned long format)
{
	int success = 0;
	long c;

	*core = -1;

	for(c = 0; c < dev->cores; c++) {
		/* a free core that has format */
		if(CoreHasFormat(cfg, c, format) && GetDecCore(c, dev, filp)) {
			success = 1;
			*core = c;
			break;
		}
	}

	return success;
}

long ReserveDecoder(hantrodec_t *dev, struct file* filp, unsigned long format)
{
	long core = -1;

	/* reserve a core */
	if (down_interruptible(&dec_core_sem))
		return -ERESTARTSYS;

	/* lock a core that has specific format*/
	if(wait_event_interruptible(hw_queue,
								GetDecCoreAny(&core, dev, filp, format) != 0 ))
		return -ERESTARTSYS;

	return core;
}

void ReleaseDecoder(hantrodec_t *dev, long core)
{
	u32 status;
	unsigned long flags;

	status = ioread32(dev->hwregs[core] + HANTRODEC_IRQ_STAT_DEC_OFF);

	/* make sure HW is disabled */
	if(status & HANTRODEC_DEC_E)
	{
		pr_info("%s DEC[%li] still enabled -> reset\n", DEV_NAME, core);

		/* abort decoder */
		status |= HANTRODEC_DEC_ABORT | HANTRODEC_DEC_IRQ_DISABLE;
		iowrite32(status, dev->hwregs[core] + HANTRODEC_IRQ_STAT_DEC_OFF);
	}

	spin_lock_irqsave(&owner_lock, flags);

	dec_owner[core] = NULL;

	spin_unlock_irqrestore(&owner_lock, flags);

	up(&dec_core_sem);

	wake_up_interruptible_all(&hw_queue);
}

long DecFlushRegs(hantrodec_t *dev, struct core_desc *core)
{
	long ret = 0, i;

	u32 id = core->id;

	ret = copy_from_user(dec_regs[id], (u32 *)core->regs, HANTRO_DEC_REGS*4);
	if (ret)
	{
		PDEBUG("%s copy_from_user failed, returned %li\n", DEV_NAME, ret);
		return -EFAULT;
	}

	/* write all regs but the status reg[1] to hardware */
	for(i = 2; i <= HANTRO_DEC_LAST_REG; i++)
		iowrite32(dec_regs[id][i], dev->hwregs[id] + i*4);

	/* write the status register, which may start the decoder */
	iowrite32(dec_regs[id][1], dev->hwregs[id] + 4);

	PDEBUG("%s flushed registers on core %d\n", DEV_NAME, id);

	return 0;
}

long DecRefreshRegs(hantrodec_t *dev, struct core_desc *core)
{
	long ret, i;
	u32 id = core->id;

	/* user has to know exactly what they are asking for */
	if(core->size != (HANTRO_DEC_REGS * 4))
		return -EFAULT;

	/* read all registers from hardware */
	for(i = 0; i <= HANTRO_DEC_LAST_REG; i++)
		dec_regs[id][i] = ioread32(dev->hwregs[id] + i*4);

	/* put registers to user space*/
	ret = copy_to_user((u32 *)core->regs, dec_regs[id], HANTRO_DEC_REGS*4);
	if (ret)
	{
		PDEBUG("%s copy_to_user failed, returned %li\n", DEV_NAME, ret);
		return -EFAULT;
	}

	return 0;
}

static int CheckDecIrq(hantrodec_t *dev, int id)
{
	unsigned long flags;
	int rdy = 0;

	const u32 irq_mask = (1 << id);

	spin_lock_irqsave(&owner_lock, flags);

	if(dec_irq & irq_mask)
	{
		/* reset the wait condition(s) */
		dec_irq &= ~irq_mask;
		rdy = 1;
	}

	spin_unlock_irqrestore(&owner_lock, flags);

	return rdy;
}

long WaitDecReadyAndRefreshRegs(hantrodec_t *dev, struct core_desc *core)
{
	u32 id = core->id;

	PDEBUG("%s wait_event_interruptible DEC[%d]\n", DEV_NAME, id);

	if(wait_event_interruptible(dec_wait_queue, CheckDecIrq(dev, id)))
	{
		PDEBUG("%s DEC[%d]  wait_event_interruptible interrupted\n", DEV_NAME, id);
		return -ERESTARTSYS;
	}

	atomic_inc(&irq_tx);

	/* refresh registers */
	return DecRefreshRegs(dev, core);
}

static int CheckCoreIrq(hantrodec_t *dev, const struct file *filp, int *id)
{
	unsigned long flags;
	int rdy = 0, n = 0;

	do
	{
		u32 irq_mask = (1 << n);

		spin_lock_irqsave(&owner_lock, flags);

		if(dec_irq & irq_mask)
		{
			if (dec_owner[n] == filp)
			{
				/* we have an IRQ for our client */

				/* reset the wait condition(s) */
				dec_irq &= ~irq_mask;

				/* signal ready core no. for our client */
				*id = n;

				rdy = 1;

				spin_unlock_irqrestore(&owner_lock, flags);
				break;
			}
			else if(dec_owner[n] == NULL)
			{
				/* zombie IRQ */
				pr_info("%s IRQ on core[%d], but no owner!!!\n", DEV_NAME, n);

				/* reset the wait condition(s) */
				dec_irq &= ~irq_mask;
				if (dec_release == 1) /* RTK, workaround for memory leak when decoder release */
				{
					dec_release = 0;
					*id = n;
					rdy = 1;
					spin_unlock_irqrestore(&owner_lock, flags);
					break;
				}
			}
		}

		spin_unlock_irqrestore(&owner_lock, flags);

		n++; /* next core */
	}
	while(n < dev->cores);

	return rdy;
}

long WaitCoreReady(hantrodec_t *dev, const struct file *filp, int *id)
{
	PDEBUG("%s wait_event_interruptible CORE\n", DEV_NAME);

	if(wait_event_interruptible(dec_wait_queue, CheckCoreIrq(dev, filp, id)))
	{
		PDEBUG("%s CORE  wait_event_interruptible interrupted\n", DEV_NAME);
		return -ERESTARTSYS;
	}

	atomic_inc(&irq_tx);

	return 0;
}

/*------------------------------------------------------------------------------
 Function name   : hantrodec_ioctl
 Description	 : communication method to/from the user space

 Return type	 : long
------------------------------------------------------------------------------*/
static long hantrodec_ioctl(struct file *filp, unsigned int cmd,
	unsigned long arg)
{
	int err = 0;
	long tmp;

#ifdef HW_PERFORMANCE
	struct timeval *end_time_arg;
#endif

	PDEBUG("%s ioctl cmd 0x%08x\n", DEV_NAME, cmd);
	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != HANTRODEC_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > HANTRODEC_IOC_MAXNR)
		return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *) arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *) arg, _IOC_SIZE(cmd));

	if (err)
		return -EFAULT;

	switch (cmd)
	{
	case HANTRODEC_IOC_CLI:
		disable_irq(hantrodec_data.irq);
		break;
	case HANTRODEC_IOC_STI:
		enable_irq(hantrodec_data.irq);
		break;
	case HANTRODEC_IOCGHWOFFSET:
		__put_user(multicorebase[0], (unsigned long *) arg);
		break;
	case HANTRODEC_IOCGHWIOSIZE:
		__put_user(hantrodec_data.iosize, (unsigned int *) arg);
		break;
	case HANTRODEC_BONDINGOFFSET:
		__put_user(s_bonding_phy_register, (unsigned long *) arg);
		break;
	case HANTRODEC_BONDINGIOSIZE:
		__put_user(s_bonding_size_register, (unsigned int *) arg);
		break;
	case HANTRODEC_IOC_MC_OFFSETS:
	{
		tmp = copy_to_user((u64 *) arg, multicorebase, sizeof(multicorebase));
		if (err)
		{
			PDEBUG("%s copy_to_user failed, returned %li\n", DEV_NAME, tmp);
			return -EFAULT;
		}
		break;
	}
	case HANTRODEC_IOC_MC_CORES:
		__put_user(hantrodec_data.cores, (unsigned int *) arg);
		break;
	case HANTRODEC_IOCS_DEC_PUSH_REG:
	{
		struct core_desc core;

		/* get registers from user space*/
		tmp = copy_from_user(&core, (void*)arg, sizeof(struct core_desc));
		if (tmp)
		{
			PDEBUG("%s copy_from_user failed, returned %li\n", DEV_NAME tmp);
			return -EFAULT;
		}

		DecFlushRegs(&hantrodec_data, &core);
		break;
	}
	case HANTRODEC_IOCS_DEC_PULL_REG:
	{
		struct core_desc core;

		/* get registers from user space*/
		tmp = copy_from_user(&core, (void*)arg, sizeof(struct core_desc));
		if (tmp)
		{
			PDEBUG("%s copy_from_user failed, returned %li\n", DEV_NAME, tmp);
			return -EFAULT;
		}

		return DecRefreshRegs(&hantrodec_data, &core);
	}
	case HANTRODEC_IOCH_DEC_RESERVE:
	{
		PDEBUG("%s Reserve DEC core, format = %li\n", DEV_NAME, arg);
		return ReserveDecoder(&hantrodec_data, filp, arg);
	}
	case HANTRODEC_IOCT_DEC_RELEASE:
	{
		if(arg >= hantrodec_data.cores || dec_owner[arg] != filp)
		{
			PDEBUG("%s bogus DEC release, core = %li\n", DEV_NAME, arg);
			return -EFAULT;
		}

		PDEBUG("%s Release DEC, core = %li\n", DEV_NAME, arg);

		ReleaseDecoder(&hantrodec_data, arg);

		break;
	}
	case HANTRODEC_IOCX_DEC_WAIT:
	{
		struct core_desc core;

		/* get registers from user space */
		tmp = copy_from_user(&core, (void*)arg, sizeof(struct core_desc));
		if (tmp)
		{
			PDEBUG("%s copy_from_user failed, returned %li\n", DEV_NAME, tmp);
			return -EFAULT;
		}

		return WaitDecReadyAndRefreshRegs(&hantrodec_data, &core);
	}
	case HANTRODEC_IOCG_CORE_WAIT:
	{
		int id;
		tmp = WaitCoreReady(&hantrodec_data, filp, &id);
		__put_user(id, (int *) arg);
		return tmp;
	}
	case HANTRODEC_IOX_ASIC_ID:
	{
		u32 id;
		__get_user(id, (u32*)arg);

		if(id >= hantrodec_data.cores)
		{
			return -EFAULT;
		}
		id = ioread32(hantrodec_data.hwregs[id]);
		__put_user(id, (u32 *) arg);
	}
	break;
	case HANTRODEC_DEBUG_STATUS:
	{
		pr_info("%s dec_irq = 0x%08x \n", DEV_NAME, dec_irq);
		pr_info("%s IRQs received/sent2user = %d / %d \n",
			DEV_NAME, atomic_read(&irq_rx), atomic_read(&irq_tx));

		for (tmp = 0; tmp < hantrodec_data.cores; tmp++)
		{
			pr_info("%s dec_core[%li] %s\n",
				DEV_NAME, tmp, dec_owner[tmp] == NULL ? "FREE" : "RESERVED");
		}
	}
	break;
	case HANTRODEC_SET_CLOCK_ENABLE:
	{
		u32 clkgate;

		if (get_user(clkgate, (u32 __user *) arg))
			return -EFAULT;

		PDEBUG("%s HANTRODEC_SET_CLOCK_ENABLE:%d\n", DEV_NAME, clkgate);

		if (clkgate)
		{
#ifdef CONFIG_POWER_CONTROL
			pr_info("%s before pctrl_on for laterncy watching!!\n", DEV_NAME);
			ve3_pctrl_on(s_pctrl_ve3);
			pr_info("%s after pctrl_on for laterncy watching!!\n", DEV_NAME);
#endif
			ve3_clk_enable(s_ve3_clk);
			ve3_wrapper_setup(base_address);
			msleep(1);
			dec_release = 0;
		}
		else
		{
			ve3_clk_disable(s_ve3_clk);
#ifdef CONFIG_POWER_CONTROL
			ve3_pctrl_off(s_pctrl_ve3);
#endif
		}
	}
	break;
	case HANTRODEC_GET_ASIC_REVISION:
	{
		__put_user(get_rtd129x_cpu_revision()|get_rtd129x_cpu_id(), (unsigned int *) arg);
	}
	break;
	case HANTRODEC_RESET_CLK_GATING:
	{
		PDEBUG("%s HANTRODEC_RESET_CLK_GATING\n", DEV_NAME);
		ve3_clk_disable(s_ve3_clk);
		reset_control_reset(rstc_ve3);
		ve3_clk_enable(s_ve3_clk);

		ve3_wrapper_setup(base_address);
		//msleep(1);
	}
	break;
	case HANTRODEC_NOTIFY_RELEASE:
	{
		dec_release = 1;
		dec_irq |= (1 << 0);
		wake_up_interruptible_all(&dec_wait_queue);
	}
	break;
	case HANTRODEC_GET_ASIC_REG:
	{
		struct core_desc core;

		/* get registers from user space*/
		tmp = copy_from_user(&core, (void*)arg, sizeof(struct core_desc));
		if (tmp)
		{
			PDEBUG("%s copy_from_user failed, returned %li\n", DEV_NAME, tmp);
			return -EFAULT;
		}

		tmp = copy_to_user((u32 *)core.regs, asic_dec_regs[core.id], HANTRO_DEC_REGS*4);
		if (tmp)
		{
			PDEBUG("%s copy_to_user failed, returned %li\n", DEV_NAME, tmp);
			return -EFAULT;
		}
	}
	break;
	default:
		return -ENOTTY;
	}

	return 0;
}

/*------------------------------------------------------------------------------
 Function name   : hantrodec_open
 Description	 : open method

 Return type	 : int
------------------------------------------------------------------------------*/

static int hantrodec_open(struct inode *inode, struct file *filp)
{
	PDEBUG("%s dev opened\n", DEV_NAME);
	return 0;
}

/*------------------------------------------------------------------------------
 Function name   : hantrodec_release
 Description	 : Release driver

 Return type	 : int
------------------------------------------------------------------------------*/

static int hantrodec_release(struct inode *inode, struct file *filp)
{
	int n;
	hantrodec_t *dev = &hantrodec_data;

	PDEBUG("%s closing ...\n", DEV_NAME);

	for(n = 0; n < dev->cores; n++)
	{
		if(dec_owner[n] == filp)
		{
			PDEBUG("%s releasing dec core %i lock\n", DEV_NAME, n);
			ReleaseDecoder(dev, n);
		}
	}

	PDEBUG("%s closed\n", DEV_NAME);
	return 0;
}

static int ve3_mmap(struct file *fp, struct vm_area_struct *vm)
{
	if ((vm->vm_pgoff == (multicorebase[0]>>PAGE_SHIFT)) || (vm->vm_pgoff == (s_bonding_phy_register>>PAGE_SHIFT)))
	{
		unsigned long pfn;

		vm->vm_flags |= VM_IO | VM_RESERVED;
		vm->vm_page_prot = pgprot_noncached(vm->vm_page_prot);
		pfn = vm->vm_pgoff;

		return remap_pfn_range(vm, vm->vm_start, pfn, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
	}
	else
	{
		vm->vm_flags |= VM_IO | VM_RESERVED;
		vm->vm_page_prot = pgprot_writecombine(vm->vm_page_prot);

		return remap_pfn_range(vm, vm->vm_start, vm->vm_pgoff, vm->vm_end-vm->vm_start, vm->vm_page_prot) ? -EAGAIN : 0;
	}
}

/* VFS methods */
static struct file_operations hantrodec_fops =
{
	.owner = THIS_MODULE,
	.open = hantrodec_open,
	.release = hantrodec_release,
	.unlocked_ioctl = hantrodec_ioctl,
	.compat_ioctl = compat_hantrodec_ioctl,
	.fasync = NULL,
	.mmap = ve3_mmap
};

/*------------------------------------------------------------------------------
 Function name   : hantrodec_init
 Description	 : Initialize the driver

 Return type	 : int
------------------------------------------------------------------------------*/

int __init hantrodec_init(void)
{
	int result = 0;

	PDEBUG("%s module init\n", DEV_NAME);

#if 0 //Fuchun, move to probe function
	int i = 0;
	pr_info("%s dec/pp kernel module\n", DEV_NAME);

	multicorebase[0] = base_port;
	elements = 1;
	pr_info("%s Init single core at 0x%08x IRQ=%i\n",
		DEV_NAME, multicorebase[0], ve3_irq);

	hantrodec_data.iosize = DEC_IO_SIZE;
	hantrodec_data.irq = ve3_irq;

	for(i=0; i< HXDEC_MAX_CORES; i++)
	{
		hantrodec_data.hwregs[i] = 0;
		/* If user gave less core bases that we have by default,
		 * invalidate default bases
		 */
		if(elements && i>=elements)
		{
			multicorebase[i] = -1;
		}
	}

	hantrodec_data.async_queue_dec = NULL;

	result = register_chrdev(hantrodec_major, "hantrodec", &hantrodec_fops);
	if(result < 0)
	{
		pr_info("%s unable to get major %d\n", DEV_NAME, hantrodec_major);
		goto err;
	}
	else if(result != 0)	/* this is for dynamic major */
	{
		hantrodec_major = result;
	}

	result = ReserveIO();
	if(result < 0)
	{
		goto err;
	}

	memset(dec_owner, 0, sizeof(dec_owner));

	sema_init(&dec_core_sem, hantrodec_data.cores);

	/* read configuration fo all cores */
	ReadCoreConfig(&hantrodec_data);

	/* reset hardware */
	ResetAsic(&hantrodec_data);

	/* get the IRQ line */
	if(ve3_irq > 0) {
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 18))
		result = request_irq(ve3_irq, hantrodec_isr, SA_INTERRUPT | SA_SHIRQ, "VE3_CODEC_IRQ", (void *) &hantrodec_data);
#else
		result = request_irq(ve3_irq, hantrodec_isr, IRQF_SHARED, "VE3_CODEC_IRQ", (void *) &hantrodec_data);
#endif
		if(result != 0) {
			if(result == -EINVAL)
				pr_err("%s Bad irq number or handler\n", DEV_NAME);
			else if(result == -EBUSY)
				pr_err("%s IRQ <%d> busy, change your config\n", DEV_NAME, hantrodec_data.irq);

			ReleaseIO();
			goto err;
		}
	}else{
		pr_info("%s IRQ not in use!\n", DEV_NAME);
	}

	return 0;

err:
	pr_info("%s module not inserted\n", DEV_NAME);
	unregister_chrdev(hantrodec_major, "hantrodec");

#endif
	return result;
}

/*------------------------------------------------------------------------------
 Function name   : hantrodec_cleanup
 Description	 : clean up

 Return type	 : int
------------------------------------------------------------------------------*/

void __exit hantrodec_cleanup(void)
{
#if 0 //Fuchun, move to remove function
	hantrodec_t *dev = &hantrodec_data;

	/* reset hardware */
	ResetAsic(dev);

	/* free the IRQ */
	if(dev->irq != -1)
		free_irq(dev->irq, (void *) dev);

	ReleaseIO();

	misc_deregister(&s_ve3_dev);
#endif
	pr_info("%s module exit\n", DEV_NAME);
	return;
}

static int ve3_probe(struct platform_device *pdev)
{
	int err = 0, i;
	struct resource res;
	void __iomem *iobase;
	int irq;
	struct device_node *node = pdev->dev.of_node;

	pr_info("%s ve3_probe\n", DEV_NAME);

	of_address_to_resource(node, 0, &res);
	iobase = of_iomap(node, 0);

	base_port = res.start;
	base_address = (volatile u8 *)iobase;
	hantrodec_data.iosize = res.end - res.start + 1;

	pr_info("%s base address get from DTB physical base addr=0x%lx, virtual base=0x%lx, size=0x%x(actually=0x%x)\n",
		DEV_NAME, base_port, (unsigned long)base_address, hantrodec_data.iosize, DEC_IO_SIZE);

	of_address_to_resource(node, 1, &res);
	iobase = of_iomap(node, 1);

	s_pll_phy_register = res.start;
	s_pll_virt_register = (unsigned long)iobase;
	s_pll_size_register = res.end - res.start + 1;

	of_address_to_resource(node, 2, &res);
	s_bonding_phy_register = res.start;
	s_bonding_size_register = res.end - res.start + 1;

	s_ve3_dev.minor = MISC_VE3_MINOR;
	s_ve3_dev.name = HANTRO_DEV_NAME;
	s_ve3_dev.fops = &hantrodec_fops;
	s_ve3_dev.parent = NULL;
	if (misc_register(&s_ve3_dev)) {
		pr_info("%s failed to register misc device.", DEV_NAME);
		goto ERROR_PROVE_DEVICE;
	}

	irq = irq_of_parse_and_map(node, 0);
	if (irq <= 0)
		panic("Can't parse IRQ");

	ve3_irq = irq;

	if (pdev)
		s_ve3_clk = ve3_clk_get(&pdev->dev);
	else
		s_ve3_clk = ve3_clk_get(NULL);

	if (!s_ve3_clk)
		pr_err("%s fail to get clock controller, but, do not treat as error, \n", DEV_NAME);
	else
		pr_info("%s get clock controller s_ve3_clk=0x%p\n", DEV_NAME, s_ve3_clk);

#ifdef CONFIG_POWER_CONTROL
	s_pctrl_ve3 = ve3_pctrl_get();
	ve3_pctrl_on(s_pctrl_ve3);
#endif

	rstc_ve3 = reset_control_get(&pdev->dev, NULL);

	/* RTK clock setting */
	ve3_pll_setting(0x114, PLL_CLK_594, 1, 0); // VE1 PLL
	ve3_pll_setting(0x118, (0x7), 1, 0); // VE1 PLL disable
	__delay(100);
	ve3_pll_setting(0x118, (0x3), 1, 0); // VE1 PLL enable
	reset_control_deassert(rstc_ve3); // RESET disable
	ve3_clk_enable(s_ve3_clk);

	ve3_wrapper_setup(base_address);
	msleep(1);
	pr_info("%s Get cti: 0x%x\n", DEV_NAME, __raw_readl(base_address+0x3F00));

	/* hantrodec_init start */
	pr_info("%s dec kernel module\n", DEV_NAME);

	multicorebase[0] = base_port;
	elements = 1;
	pr_info("%s Init single core at 0x%16llx IRQ=%i\n",
		DEV_NAME, multicorebase[0], ve3_irq);

	hantrodec_data.iosize = DEC_IO_SIZE;
	hantrodec_data.irq = ve3_irq;

	for (i = 0 ; i < HXDEC_MAX_CORES ; i++) {
		hantrodec_data.hwregs[i] = 0;
		/* If user gave less core bases that we have by default,
		 * invalidate default bases
		 */
		if(elements && i>=elements)
			multicorebase[i] = -1;
	}

	hantrodec_data.async_queue_dec = NULL;

	err = ReserveIO();
	if(err < 0)
		goto ERROR_PROVE_DEVICE;

	memset(dec_owner, 0, sizeof(dec_owner));

	sema_init(&dec_core_sem, hantrodec_data.cores);

	/* read configuration fo all cores */
	ReadCoreConfig(&hantrodec_data);

	/* reset hardware */
	ResetAsic(&hantrodec_data);

	/* get the IRQ line */
	if(ve3_irq > 0) {
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 18))
		err = request_irq(ve3_irq, hantrodec_isr, SA_INTERRUPT | SA_SHIRQ, "VE3_CODEC_IRQ", (void *) &hantrodec_data);
#else
		err = request_irq(ve3_irq, hantrodec_isr, IRQF_SHARED, "VE3_CODEC_IRQ", (void *) &hantrodec_data);
#endif

		if(err != 0) {
			if(err == -EINVAL)
				pr_err("%s Bad irq number or handler\n", DEV_NAME);
			else if(err == -EBUSY)
				pr_err("%s IRQ <%d> busy, change your config\n",
					DEV_NAME, hantrodec_data.irq);
			ReleaseIO();
			goto ERROR_PROVE_DEVICE;
		}
	} else
		pr_info("%s IRQ not in use!\n", DEV_NAME);

	pr_info("%s module inserted. Major = %d\n", DEV_NAME, hantrodec_major);
	/* hantrodec_init end */

	ve3_clk_disable(s_ve3_clk);
#ifdef CONFIG_POWER_CONTROL
	ve3_pctrl_off(s_pctrl_ve3);
#endif
	return 0;

ERROR_PROVE_DEVICE:

	pr_info("%s module not inserted\n", DEV_NAME);

	if (rstc_ve3 != NULL)
		reset_control_put(rstc_ve3);

	ve3_clk_put(s_ve3_clk);
	misc_deregister(&s_ve3_dev);

	return err;
}

static int ve3_remove(struct platform_device *pdev)
{
	hantrodec_t *dev = (hantrodec_t *)&hantrodec_data;

	pr_info("%s ve3_remove\n", DEV_NAME);

	/* reset hardware */
	ResetAsic(dev);

	/* free the IRQ */
	if(dev->irq != -1)
	{
		free_irq(dev->irq, (void *) dev);
	}

	ReleaseIO();

	if (rstc_ve3 != NULL)
		reset_control_put(rstc_ve3);

	ve3_clk_put(s_ve3_clk);

	misc_deregister(&s_ve3_dev);

	pr_info("%s hantrodec: module removed\n", DEV_NAME);

	return 0;
}

#ifdef CONFIG_PM
static int ve3_suspend(struct device *pdev)
{

	pr_info("%s Enter %s\n", DEV_NAME, __func__);

#ifdef CONFIG_POWER_CONTROL
	ve3_pctrl_on(s_pctrl_ve3);
#endif
	ve3_clk_enable(s_ve3_clk);

	if (dec_owner[0] != NULL)
	{
		up(&dec_core_sem);
		wake_up_interruptible_all(&hw_queue);
		wake_up_interruptible_all(&dec_wait_queue);
		dec_irq = 0;
		dec_owner[0] = NULL;
	}

	ve3_clk_disable(s_ve3_clk);
#ifdef CONFIG_POWER_CONTROL
	ve3_pctrl_off(s_pctrl_ve3);
#endif

	pr_info("%s Exit %s\n", DEV_NAME, __func__);

	return 0;
}

static int ve3_resume(struct device *pdev)
{
	pr_info("%s Enter %s\n", DEV_NAME,  __func__);

#ifdef CONFIG_POWER_CONTROL
	ve3_pctrl_on(s_pctrl_ve3);
#endif
	ve3_clk_enable(s_ve3_clk);
	/* RTK clock setting */
	ve3_pll_setting(0x114, PLL_CLK_594, 1, 0); // VE1 PLL
	ve3_pll_setting(0x118, (0x7), 1, 0); // VE1 PLL disable
	__delay(100);
	ve3_pll_setting(0x118, (0x3), 1, 0); // VE1 PLL enable
	ve3_clk_disable(s_ve3_clk);
#ifdef CONFIG_POWER_CONTROL
	ve3_pctrl_off(s_pctrl_ve3);
#endif

	pr_info("%s  Exit %s\n", DEV_NAME, __func__);

	return 0;
}
#else
#define ve3_suspend NULL
#define ve3_resume NULL
#endif /* !CONFIG_PM */

/*------------------------------------------------------------------------------
 Function name   : ReserveIO
 Description	 : IO reserve

 Return type	 : int
------------------------------------------------------------------------------*/
static int ReserveIO(void)
{
	int i;

	for (i = 0 ; i < HXDEC_MAX_CORES ; i++) {
		if (multicorebase[i] != -1) {
#if 0
			if (!request_mem_region(multicorebase[i], hantrodec_data.iosize, "hantrodec0")) {
				pr_info("%s failed to reserve HW regs\n", DEV_NAME);
				return -EBUSY;
			}

			hantrodec_data.hwregs[i] = (volatile u8 *) ioremap_nocache(multicorebase[i], hantrodec_data.iosize);
#else
			hantrodec_data.hwregs[i] = base_address;
#endif
			if (hantrodec_data.hwregs[i] == NULL ) {
				pr_info("%s failed to ioremap HW regs\n", DEV_NAME);
				ReleaseIO();
				return -EBUSY;
			}
			hantrodec_data.cores++;
		}
	}

	return 0;
}

/*------------------------------------------------------------------------------
 Function name : releaseIO
 Description	 : release

 Return type : void
------------------------------------------------------------------------------*/

static void ReleaseIO(void)
{
	int i;

	for (i = 0 ; i < hantrodec_data.cores ; i++) {
#if 0
		if (hantrodec_data.hwregs[i])
			iounmap((void *) hantrodec_data.hwregs[i]);
		release_mem_region(multicorebase[i], hantrodec_data.iosize);
#endif
	}
}

/*------------------------------------------------------------------------------
 Function name   : hantrodec_isr
 Description	 : interrupt handler

 Return type	 : irqreturn_t
------------------------------------------------------------------------------*/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18))
irqreturn_t hantrodec_isr(int irq, void *dev_id, struct pt_regs *regs)
#else
irqreturn_t hantrodec_isr(int irq, void *dev_id)
#endif
{
	unsigned long flags;
	unsigned int handled = 0;
	int i;

	hantrodec_t *dev = (hantrodec_t *) dev_id;
	u32 irq_status_dec;

	spin_lock_irqsave(&owner_lock, flags);

	for (i = 0 ; i < dev->cores ; i++) {
		volatile u8 *hwregs = dev->hwregs[i];

		/* interrupt status register read */
		irq_status_dec = ioread32(hwregs + HANTRODEC_IRQ_STAT_DEC_OFF);

		if(irq_status_dec & HANTRODEC_DEC_IRQ) {
			/* clear dec IRQ */
			irq_status_dec &= (~HANTRODEC_DEC_IRQ);
			iowrite32(irq_status_dec, hwregs + HANTRODEC_IRQ_STAT_DEC_OFF);

			PDEBUG("%s decoder IRQ received! core %d\n", DEV_NAME, i);

			atomic_inc(&irq_rx);

			dec_irq |= (1 << i);

			wake_up_interruptible_all(&dec_wait_queue);
			handled++;
		}
	}

	spin_unlock_irqrestore(&owner_lock, flags);

	if(!handled)
		PDEBUG("%s IRQ received, but not VE3's!\n", DEV_NAME);

	return IRQ_RETVAL(handled);
}

/*------------------------------------------------------------------------------
 Function name   : ResetAsic
 Description	 : reset asic

 Return type	 :
------------------------------------------------------------------------------*/
void ResetAsic(hantrodec_t * dev)
{
	int i;
	int j;
	u32 status;

	for (j = 0 ; j < dev->cores ; j++) {
		status = ioread32(dev->hwregs[j] + HANTRODEC_IRQ_STAT_DEC_OFF);

		if( status & HANTRODEC_DEC_E) {
			/* abort with IRQ disabled */
			status = HANTRODEC_DEC_ABORT | HANTRODEC_DEC_IRQ_DISABLE;
			iowrite32(status, dev->hwregs[j] + HANTRODEC_IRQ_STAT_DEC_OFF);
		}

		for (i = 4 ; i < dev->iosize ; i += 4) {
			iowrite32(0, dev->hwregs[j] + i);
		}
	}
}

/*------------------------------------------------------------------------------
 Function name   : dump_regs
 Description	 : Dump registers

 Return type	 :
------------------------------------------------------------------------------*/
#ifdef HANTRODEC_DEBUG
void dump_regs(hantrodec_t *dev)
{
	int i,c;

	PDEBUG("%s Reg Dump Start\n", DEV_NAME);
	for(c = 0 ; c < dev->cores ; c++) {
		for(i = 0 ; i < dev->iosize ; i += 4*4) {
			PDEBUG("%s \toffset %04X: %08X  %08X  %08X  %08X\n",
				DEV_NAME,
				i,
				ioread32(dev->hwregs[c] + i),
				ioread32(dev->hwregs[c] + i + 4),
				ioread32(dev->hwregs[c] + i + 16),
				ioread32(dev->hwregs[c] + i + 24));
		}
	}
	PDEBUG("%s Reg Dump End\n", DEV_NAME);
}
#endif

struct clk *ve3_clk_get(struct device *dev)
{
	return clk_get(dev, "clk_ve3");
}

void ve3_clk_put(struct clk *clk)
{
	if (clk)
		clk_put(clk);
}

int ve3_clk_enable(struct clk *clk)
{
	if (clk) {
		PDEBUG("%s ve3_clk_enable\n", DEV_NAME);
		return clk_prepare_enable(clk);
	}
	return 0;
}

void ve3_clk_disable(struct clk *clk)
{
	if (clk) {
		PDEBUG("%s ve3_clk_disable\n", DEV_NAME);
		while(__clk_is_enabled(clk))
			clk_disable_unprepare(clk);
	}
}

#ifdef CONFIG_POWER_CONTROL
struct power_control *ve3_pctrl_get(void)
{
	return power_control_get("pctrl_ve3");
}

void ve3_pctrl_on(struct power_control *pctrl)
{
	if (!(pctrl == NULL || IS_ERR(pctrl))) {
		printk(KERN_INFO "ve3_pctrl_on\n");
		power_control_power_on(pctrl);
	}
}

void ve3_pctrl_off(struct power_control *pctrl)
{
	if (!(pctrl == NULL || IS_ERR(pctrl))) {
		printk(KERN_INFO "ve3_pctrl_off\n");
		power_control_power_off(pctrl);
	}
}
#endif

static const struct of_device_id rtk_ve3_dt_match[] = {
	{.compatible = "Realtek,rtk1295-ve3"},
	{}
};
MODULE_DEVICE_TABLE(of, rtk_ve3_dt_match);

const struct dev_pm_ops rtk_ve3_pmops = {
	.suspend = ve3_suspend,
	.resume = ve3_resume,
};

static struct platform_driver rtk_ve3_driver = {
	.driver = {
		.name = "rtk-ve3",
		.owner = THIS_MODULE,
		.of_match_table = rtk_ve3_dt_match,
		.pm = &rtk_ve3_pmops,
	},
	.probe = ve3_probe,
	.remove = ve3_remove,
};

module_platform_driver(rtk_ve3_driver);

module_init(hantrodec_init);
module_exit(hantrodec_cleanup);

/* module description */
MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("A customer using RTK VPU, Inc.");
MODULE_DESCRIPTION("Driver module for VE3");
