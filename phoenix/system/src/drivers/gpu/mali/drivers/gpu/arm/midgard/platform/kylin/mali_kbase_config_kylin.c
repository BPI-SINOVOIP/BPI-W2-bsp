/*
 *
 * (C) COPYRIGHT 2011-2014 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the
 * GNU General Public License version 2 as published by the Free Software
 * Foundation, and any use by you of this program is subject to the terms
 * of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained
 * from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 */



#include <linux/ioport.h>
#include <linux/delay.h>
#ifdef CONFIG_POWER_CONTROL
#include <linux/power-control.h>
#endif
#include <linux/clk-provider.h>
#include <linux/reset-helper.h>
#include <linux/reset.h>

#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0)
#include <linux/pm_opp.h>
#else /* Linux >= 3.13 */
/* In 3.13 the OPP include header file, types, and functions were all
 *  * renamed. Use the old filename for the include, and define the new names to
 *   * the old, when an old kernel is detected.
 *    */
#include <linux/opp.h>
#define dev_pm_opp opp
#define dev_pm_opp_get_voltage opp_get_voltage
#define dev_pm_opp_get_opp_count opp_get_opp_count
#define dev_pm_opp_find_freq_ceil opp_find_freq_ceil
#endif /* Linux >= 3.13 */

#include <mali_kbase.h>
#include <mali_kbase_defs.h>
#include <mali_kbase_config.h>

#define HARD_RESET_AT_POWER_OFF 0
#define ENALBE_DYNAMIC_L2_SD_DS

#define RBUS_BASE 0x98000000
#define RBUS_RANGE 0x100000

#define GPU_PLL_FREQ         (0x980005a4 - RBUS_BASE)
#define GPU_PLL_POWER_ON     (0x980001c4 - RBUS_BASE)
#define GPU_PLL_ON_OC_EN     (0x980005a0 - RBUS_BASE)
#define STD_PG_OUT           (0x980003a4 - RBUS_BASE)
#define PG_SWITCH_INTERRUPT  (0x980003ac - RBUS_BASE)
#define GPU_RESET            (0x98000000 - RBUS_BASE)
#define GPU_CLOCK            (0x9800000c - RBUS_BASE)

#define L2_CLOCK             (0x98054000 - RBUS_BASE)
#define L2_PWR_RSTN          (0x9805409c - RBUS_BASE)
#define L2_BISR              (0x98054020 - RBUS_BASE)
#define L2_BISR_CHECK        (0x98054044 - RBUS_BASE)
#define L2_HOLD_REMAP        (0x9805409c - RBUS_BASE)
#define GPU_POWER_ON_CORES   (0x98050180 - RBUS_BASE)
#define GPU_POWER_ON_TILERS  (0x98050190 - RBUS_BASE)
#define GPU_POWER_ON_L2      (0x980501a0 - RBUS_BASE)
#define GPU_STATUS_OF_CORES  (0x98050140 - RBUS_BASE)
#define GPU_STATUS_OF_TILERS (0x98050150 - RBUS_BASE)
#define GPU_STATUS_OF_L2     (0x98050160 - RBUS_BASE)
#define GPU_POWER_OFF_CORES  (0x980501c0 - RBUS_BASE)
#define GPU_POWER_OFF_TILERS (0x980501d0 - RBUS_BASE)
#define GPU_POWER_OFF_L2     (0x980501e0 - RBUS_BASE)

#define WAIT_USLEEP_TIME         800
void __iomem * rbus_base;

struct reset_control *rstc_gpu = NULL;

#ifdef CONFIG_POWER_CONTROL
static struct power_control *pctrl_core1 = NULL;
static struct power_control *pctrl_core2 = NULL;
static struct power_control *pctrl_core3 = NULL;
static struct power_control *pctrl = NULL;
bool isPowerOn = false;
struct mutex gpu_pctrl_lock;

static bool gpu_pctrl_get(void)
{
    bool isPctrlGet = 0;
    pctrl_core1 = power_control_get("pctrl_gpu_core_1");
    pctrl_core2 = power_control_get("pctrl_gpu_core_2");
    pctrl_core3 = power_control_get("pctrl_gpu_core_3");
    pctrl = power_control_get("pctrl_gpu");

    if ((pctrl_core1 != NULL) && (pctrl_core2 != NULL)
        && (pctrl_core3 != NULL) && (pctrl != NULL)) {
        isPctrlGet = 1;
    }
    return isPctrlGet;
}

static void gpu_pctrl_on(void)
{
    mutex_lock(&gpu_pctrl_lock);
    if (!isPowerOn) {
        if (!(pctrl_core1 == NULL || IS_ERR(pctrl_core1))) {
            power_control_power_on(pctrl_core1);
        }

        if (!(pctrl_core2 == NULL || IS_ERR(pctrl_core2))) {
            power_control_power_on(pctrl_core2);
        }

        if (!(pctrl_core3 == NULL || IS_ERR(pctrl_core3))) {
            power_control_power_on(pctrl_core3);
        }

        if (!(pctrl == NULL || IS_ERR(pctrl))) {
            power_control_power_on(pctrl);
        }
        isPowerOn = true;
    }
    mutex_unlock(&gpu_pctrl_lock);
}

static void gpu_pctrl_off(void)
{
    mutex_lock(&gpu_pctrl_lock);
    if (isPowerOn) {
        if (!(pctrl_core1 == NULL || IS_ERR(pctrl_core1))) {
            power_control_power_off(pctrl_core1);
        }

        if (!(pctrl_core2 == NULL || IS_ERR(pctrl_core2))) {
            power_control_power_off(pctrl_core2);
        }

        if (!(pctrl_core3 == NULL || IS_ERR(pctrl_core3))) {
            power_control_power_off(pctrl_core3);
        }

        if (!(pctrl == NULL || IS_ERR(pctrl))) {
            power_control_power_off(pctrl);
        }
        isPowerOn = false;
    }
    mutex_unlock(&gpu_pctrl_lock);
}
#endif

static void enable_gpu_clock(struct kbase_device *kbdev)
{
    //printk(KERN_ALERT "Enable gpu Clock\n");
    //u32 value = readl(rbus_base + GPU_CLOCK);
    //writel((value | 0x800), rbus_base + GPU_CLOCK);
    clk_enable(kbdev->clock);
}

static void disable_gpu_clock(struct kbase_device *kbdev)
{
    //printk(KERN_ALERT "Disable gpu Clock\n");
    //u32 value = readl(rbus_base + GPU_CLOCK);
    //writel((value & ~0x800), rbus_base + GPU_CLOCK);
    while (__clk_is_enabled(kbdev->clock))
        clk_disable(kbdev->clock);
}

static void l2_sd_ds_disable(void)
{
    u32 regValue;
    //printk(KERN_ALERT, "L2 SD & DS disable\n");
    writel(0x301, rbus_base + STD_PG_OUT);
    usleep_range(10, 10);
    regValue = readl(rbus_base + PG_SWITCH_INTERRUPT); //0x0000_0004
    if (regValue != 0x4)
        printk(KERN_ALERT "address[0x%x] = 0x%x (0x0004)\n", (RBUS_BASE + PG_SWITCH_INTERRUPT), regValue);
    writel(0x4, rbus_base + PG_SWITCH_INTERRUPT);
}

static void l2_sd_ds_enable(void)
{
    u32 regValue;
    //printk(KERN_ALERT, "L2 SD & DS Enable\n");
    writel(0x300, rbus_base + STD_PG_OUT);
    usleep_range(10, 10);
    regValue = readl(rbus_base + PG_SWITCH_INTERRUPT); //0x0000_0004
    if (regValue != 0x4)
        printk(KERN_ALERT "address[0x%x] = 0x%x (0x0004)\n", (RBUS_BASE + PG_SWITCH_INTERRUPT), regValue);
    writel(0x4, rbus_base + PG_SWITCH_INTERRUPT);
}

#ifdef CONFIG_REGULATOR
static void gpu_set_voltage(struct kbase_device *kbdev)
{
    int err = 0;
    int i = 0;
    struct dev_pm_opp *opp;
    unsigned long voltage = 1000000;
    unsigned long freq = 0;
    u32 flags = 0;

    //find max freq and volatag in table
    if (kbdev->devfreq_profile.max_state > 0) {
        for (i = 0; i < kbdev->devfreq_profile.max_state; i++) {
            //printk(KERN_ALERT "kbdev freq[%d] = %d\n", i, kbdev->devfreq_profile.freq_table[i]);
            if (freq < kbdev->devfreq_profile.freq_table[i])
                freq = kbdev->devfreq_profile.freq_table[i];
        }

        rcu_read_lock();
        opp = devfreq_recommended_opp(kbdev->dev, &freq, flags);
        voltage = dev_pm_opp_get_voltage(opp);
        rcu_read_unlock();
        //printk(KERN_ALERT "kbdev max freq %u voltage %u\n", freq, voltage);
    }

    //set max voltage in device tree
    err = regulator_set_voltage(kbdev->regulator, voltage, voltage);
    if (err) {
        dev_err(kbdev->dev, "Failed to set voltage (%d)\n", err);
    }

    usleep_range(500, 500);
}
#endif
#ifndef CONFIG_OF
static struct kbase_io_resources io_resources = {
	.job_irq_number = 99,
	.mmu_irq_number = 100,
	.gpu_irq_number = 98,
	.io_memory_region = {
			     .start = 0x98050000,
			     .end = 0x9805FFFF}
};
#endif

static int pm_callback_power_on(struct kbase_device *kbdev)
{
    enable_gpu_clock(kbdev);

#ifdef CONFIG_POWER_CONTROL
    gpu_pctrl_on();
#endif

#ifdef ENALBE_DYNAMIC_L2_SD_DS
    l2_sd_ds_enable();
#endif
    return 1;
}

static void pm_callback_power_off(struct kbase_device *kbdev)
{
#if HARD_RESET_AT_POWER_OFF
	/* Cause a GPU hard reset to test whether we have actually idled the GPU
	 * and that we properly reconfigure the GPU on power up.
	 * Usually this would be dangerous, but if the GPU is working correctly it should
	 * be completely safe as the GPU should not be active at this point.
	 * However this is disabled normally because it will most likely interfere with
	 * bus logging etc.
	 */
	KBASE_TRACE_ADD(kbdev, CORE_GPU_HARD_RESET, NULL, NULL, 0u, 0);
	kbase_os_reg_write(kbdev, GPU_CONTROL_REG(GPU_COMMAND), GPU_COMMAND_HARD_RESET);
#endif

#ifdef ENALBE_DYNAMIC_L2_SD_DS
    l2_sd_ds_disable();
#endif

#ifdef CONFIG_POWER_CONTROL
    gpu_pctrl_off();
#endif

    disable_gpu_clock(kbdev);
}

static void pm_callback_power_suspend(struct kbase_device *kbdev)
{
    //printk(KERN_ALERT "[+][GPU] %s %d\n", __FUNCTION__, __LINE__);
#ifdef CONFIG_REGULATOR
    if (kbdev->regulator && kbdev->clock) {
        gpu_set_voltage(kbdev);
    }
#endif

#ifdef CONFIG_POWER_CONTROL
    gpu_pctrl_off();
#endif

    if (kbdev->clock) {
        //clk_disable_unprepare(kbdev->clock);
        disable_gpu_clock(kbdev);
    }

    //printk(KERN_ALERT "[-][GPU] %s %d\n", __FUNCTION__, __LINE__);
}

static void pm_callback_power_resume(struct kbase_device *kbdev)
{
    //printk(KERN_ALERT "[+][GPU] %s %d\n", __FUNCTION__, __LINE__);
    int err = 0;
    //u32 regValue;

#ifdef CONFIG_REGULATOR
    if (kbdev->regulator && kbdev->clock) {
        gpu_set_voltage(kbdev);
    }
#endif

    //writel(0x8212, rbus_base + GPU_PLL_FREQ); // 520MHz
    writel(0x40E3, rbus_base + GPU_PLL_FREQ); // 300MHz
    writel(0x7, rbus_base + GPU_PLL_POWER_ON);    // power on GPU PLL & release RSTB
    writel(0xD, rbus_base + GPU_PLL_ON_OC_EN);    // turn on OC_EN_GPU & release RSTB
    usleep_range(WAIT_USLEEP_TIME, WAIT_USLEEP_TIME);
    writel(0x3, rbus_base + GPU_PLL_POWER_ON);    // enable GPU PLL OEB

    //////////////////////////////////////////////////////////////////////////////////////
    if (rstc_gpu == NULL) {
        u32 value = readl(rbus_base + GPU_RESET);
        writel((value | 0x40000), rbus_base + GPU_RESET);
    } else {
        reset_control_deassert(rstc_gpu);
    }

    if (kbdev->clock) {
        //err = clk_prepare_enable(kbdev->clock);
        enable_gpu_clock(kbdev);
        if (err) {
            dev_err(kbdev->dev, "Failed to prepare and enable clock (%d)\n", err);
        }
    }
    usleep_range(1000, 1000);

    //////////////////////////////////////////////////////////////////////////////////////
#if 0
    //printk(KERN_ALERT "L2 BISR Reset\n");
    writel(0x20, rbus_base + L2_CLOCK); //Assert L2 clock
    writel(0x1, rbus_base + L2_PWR_RSTN);
    writel(0x3, rbus_base + L2_PWR_RSTN);
    usleep_range(500, 500);
    regValue = readl(rbus_base + L2_BISR); //0x0000_0020
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0020)\n", (RBUS_BASE + L2_BISR), regValue);
    regValue = readl(rbus_base + L2_BISR_CHECK); //0x0000_0000
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0000)\n", (RBUS_BASE + L2_BISR_CHECK), regValue);
    writel(0xf, rbus_base + L2_HOLD_REMAP);
    writel(0x0, rbus_base + L2_CLOCK); //De-Assert L2 clock
#endif

#ifdef CONFIG_POWER_CONTROL
    gpu_pctrl_on();
#endif
    //printk(KERN_ALERT "[-][GPU] %s %d\n", __FUNCTION__, __LINE__);
}

struct kbase_pm_callback_conf pm_callbacks = {
	.power_on_callback = pm_callback_power_on,
	.power_off_callback = pm_callback_power_off,
	.power_suspend_callback = pm_callback_power_suspend,
	.power_resume_callback = pm_callback_power_resume
};

static struct kbase_platform_config kylin_platform_config = {
#ifndef CONFIG_OF
	.io_resources = &io_resources
#endif
};

struct kbase_platform_config *kbase_get_platform_config(void)
{
	printk(KERN_ALERT "kylin %s %d\n", __FUNCTION__, __LINE__);
	return &kylin_platform_config;
}

int kbase_platform_early_init(void)
{
    /* Nothing needed at this stage */
    return 0;
}

int kbase_platform_init(struct kbase_device *kbdev)
{
	//printk(KERN_ALERT "[+] kylin %s %d\n", __FUNCTION__, __LINE__);
    /* Nothing needed at this stage */

    //printk(KERN_ALERT "initialize GPU hw setting\n");
    u64 reg_start = RBUS_BASE;
    size_t reg_size = RBUS_RANGE;
    u32 regValue;

    //printk(KERN_ALERT "%s %d\n", __FUNCTION__, __LINE__);
    rbus_base = ioremap(reg_start, reg_size);
    if (!rbus_base) {
        printk(KERN_ALERT "Can't ioremap register window\n");
        return 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //printk(KERN_ALERT, "PLL setting\n");
    writel(0x8212, rbus_base + GPU_PLL_FREQ); // 520MHz
    //writel(0x9A12, rbus_base + GPU_PLL_FREQ); // 601MHz
    writel(0x7, rbus_base + GPU_PLL_POWER_ON);    // power on GPU PLL & release RSTB
    writel(0xD, rbus_base + GPU_PLL_ON_OC_EN);    // turn on OC_EN_GPU & release RSTB
    usleep_range(WAIT_USLEEP_TIME, WAIT_USLEEP_TIME);
    writel(0x3, rbus_base + GPU_PLL_POWER_ON);    // enable GPU PLL OEB

    //////////////////////////////////////////////////////////////////////////////////////
    u32 value;
    rstc_gpu = reset_control_get(kbdev->dev, NULL);
    if (rstc_gpu == NULL) {
        printk(KERN_ALERT "[gpu %s %d] can not get gpu reset\n", __FUNCTION__, __LINE__);
        value = readl(rbus_base + GPU_RESET);
        writel((value | 0x40000), rbus_base + GPU_RESET);
    } else {
        reset_control_deassert(rstc_gpu);
    }
    //printk(KERN_ALERT "[gpu %s %d] enable gpu clock\n", __FUNCTION__, __LINE__);
    if (kbdev->clock == NULL) {
        printk(KERN_ALERT "[gpu %s %d] can not get gpu clock, enable gpu clock by regiter\n", __FUNCTION__, __LINE__);
        value = readl(rbus_base + GPU_CLOCK);
        writel((value | 0x800), rbus_base + GPU_CLOCK);
    } else {
        enable_gpu_clock(kbdev);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    //printk(KERN_ALERT "L2 BISR Reset\n");
    writel(0x20, rbus_base + L2_CLOCK); //Assert L2 clock
    writel(0x1, rbus_base + L2_PWR_RSTN);
    writel(0x3, rbus_base + L2_PWR_RSTN);
    usleep_range(WAIT_USLEEP_TIME, WAIT_USLEEP_TIME);
    regValue = readl(rbus_base + L2_BISR); //0x0000_0020
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0020)\n", (RBUS_BASE + L2_BISR), regValue);
    regValue = readl(rbus_base + L2_BISR_CHECK); //0x0000_0000
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0000)\n", (RBUS_BASE + L2_BISR_CHECK), regValue);
    writel(0xf, rbus_base + L2_HOLD_REMAP);
    writel(0x0, rbus_base + L2_CLOCK); //De-Assert L2 clock

    //////////////////////////////////////////////////////////////////////////////////////
    //printk(KERN_ALERT "GPU core power on\n");
    writel(0x7, rbus_base + GPU_POWER_ON_CORES);
    writel(0x1, rbus_base + GPU_POWER_ON_TILERS);
    writel(0x1, rbus_base + GPU_POWER_ON_L2);
    usleep_range(WAIT_USLEEP_TIME, WAIT_USLEEP_TIME);
    regValue = readl(rbus_base + GPU_STATUS_OF_CORES); //0x0000_0007
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0007)\n", (RBUS_BASE + GPU_STATUS_OF_CORES), regValue);
    regValue = readl(rbus_base + GPU_STATUS_OF_TILERS); //0x0000_0001
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0001)\n", (RBUS_BASE + GPU_STATUS_OF_TILERS), regValue);
    regValue = readl(rbus_base + GPU_STATUS_OF_L2); //0x0000_0001
    //printk(KERN_ALERT "address[0x%x] = 0x%x (0x0001)\n", (RBUS_BASE + GPU_STATUS_OF_L2), regValue);

    //////////////////////////////////////////////////////////////////////////////////////
#ifndef ENALBE_DYNAMIC_L2_SD_DS
    l2_sd_ds_enable();
#endif

#ifdef CONFIG_POWER_CONTROL
    mutex_init(&gpu_pctrl_lock);
    if (!gpu_pctrl_get()) {
        printk(KERN_WARNING "can not get gpu pctrl\n");
    }
#endif

	//printk(KERN_ALERT "[-] kylin %s %d\n", __FUNCTION__, __LINE__);
    return 0;
}
