#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/cpu.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/reboot.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/cpu_pm.h>
#include <linux/vmalloc.h>
#include <linux/tick.h>
#include <linux/slab.h>
//#include <mach/gpio.h>
#include <asm/io.h>
#include <asm/system_misc.h>
#include <asm/cacheflush.h>
#include <asm/psci.h>
#include <asm/suspend.h>

#include "rtd119x_ip_power.h"
#include "rtd119x_suspend.h"

__maybe_unused static int   debug               = 1;
__maybe_unused static int   warning             = 1;
__maybe_unused static int   info                = 1;

static int                  suspend_version     = 2;
static enum _suspend_mode   suspend_mode        = SUSPEND_TO_COOLBOOT;
#if 1 // legacy
static int                  wifi_gpio           = -1;
#endif

extern void rtk119x_prepare_cpus(unsigned int max_cpus);
extern void rtk_clocksource_suspend(void);
extern void rtk_clocksource_resume(void);
extern int arch_timer_suspend(void);
extern void arch_timer_resume(void);

extern volatile void __iomem *rpc_ringbuf_base;
extern volatile void __iomem *rpc_common_base;

#define dprintk(msg...) if (debug)   { printk(KERN_DEBUG    "D/SUSPEND: " msg); }
#define eprintk(msg...) if (1)       { printk(KERN_ERR      "E/SUSPEND: " msg); }
#define wprintk(msg...) if (warning) { printk(KERN_WARNING  "W/SUSPEND: " msg); }
#define iprintk(msg...) if (info)    { printk(KERN_INFO     "I/SUSPEND: " msg); }

#define SUSPEND_VERSION_MASK(v)     ((v&0xffff) << 16)
#define BT_WAKEUP_IGPIO(n)	        (0x1 << n)//n:0 to 20
#define RTK_VIRT_ADDR_MAP(addr)     (RBUS_BASE_VIRT + ((unsigned int)addr - RBUS_BASE_PHYS))
#define WRITE_REG_INT32U(addr,val)  writel(val, IOMEM(RTK_VIRT_ADDR_MAP(addr)))

static void hexdump(char *note, unsigned char *buf, unsigned int len)
{
	if (debug) {
		printk(KERN_CRIT "%s\n", note);
		print_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET,
				16, 1,
				buf, len, false);
	}
}

void acpu_set_flag(uint32_t flag)
{
	struct RTK119X_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	writel(__cpu_to_be32(SUSPEND_VERSION_MASK(suspend_version)), &(ipc->suspend_mask));
    if (suspend_version == 1)
        writel(__cpu_to_be32(flag), &(ipc->suspend_flag));
    else
        writel(__cpu_to_be32(flag | AUTHOR_MASK(AUTHOR_SCPU)), &(ipc->suspend_flag));
}

void notify_acpu(enum _notify_flag flag)
{
    switch (flag) {
        case NOTIFY_SUSPEND_TO_RAM:
        case NOTIFY_SUSPEND_TO_COOLBOOT:
        case NOTIFY_SUSPEND_TO_WFI:
            if (suspend_version == 1) {
                acpu_set_flag(0x000018ff); //suspend
                return;
            }
            break;
        case NOTIFY_RESUME_PLATFORM:
            if (suspend_version == 1) {
                acpu_set_flag(0x00000000);
                return;
            }
            break;
        default:
            break;
    }
    if (suspend_version == 1)
        return;
    acpu_set_flag(NOTIFY_MASK(flag));
}

void acpu_set_bt_wakeup_host(int igpio_num,bool active_high)
{
	struct RTK119X_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;
	dprintk("%s: igpio_num(%d) active_level(%u)\n",__func__,igpio_num,active_high);
	if(active_high)
		writel(__cpu_to_be32(0xEA800000|BT_WAKEUP_IGPIO(igpio_num)), &(ipc->bt_wakeup_flag));
	else
		writel(__cpu_to_be32(0xEA000000|BT_WAKEUP_IGPIO(igpio_num)), &(ipc->bt_wakeup_flag));
}

#define rtk_suspend_shm_func(_name, _offset, _def)                                  \
void rtk_suspend_##_name##_set(unsigned int val)                                    \
{                                                                                   \
	struct RTK119X_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;             \
    writel(__cpu_to_be32(SUSPEND_MAGIC_MASK | _def##_MASK(val)), &(ipc->_offset));   \
}                                                                                   \
unsigned int rtk_suspend_##_name##_get(void)                                        \
{                                                                                   \
	struct RTK119X_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;             \
    unsigned int val = __be32_to_cpu(readl(&(ipc->_offset)));                       \
    if (SUSPEND_MAGIC_GET(val) != SUSPEND_MAGIC_KEY) {                              \
        eprintk("[%s] Error! val = 0x%08x\n", __func__, val);                       \
        return -1;                                                                  \
    }                                                                               \
    return _def##_GET(val);                                                         \
}

rtk_suspend_shm_func(wakeup_flags,                  suspend_wakeup_flag,                WAKEUP_FLAGS);
rtk_suspend_shm_func(resume_state,                  acpu_resume_state,                  RESUME_STATE);
rtk_suspend_shm_func(resume_data,                   acpu_resume_state,                  RESUME_DATA);
rtk_suspend_shm_func(gpio_wakeup_en,                gpio_wakeup_enable,                 GPIO_WAKEUP_EN);
rtk_suspend_shm_func(gpio_wakeup_act,               gpio_wakeup_activity,               GPIO_WAKEUP_ACT);
rtk_suspend_shm_func(gpio_output_change_en,         gpio_output_change_enable,          GPIO_OUTPUT_CHANGE_EN);
rtk_suspend_shm_func(gpio_output_change_act,        gpio_output_change_activity,        GPIO_OUTPUT_CHANGE_ACT);
rtk_suspend_shm_func(timer_sec,                     audio_reciprocal_timer_sec,         AUDIO_RECIPROCAL_TIMER);

static int suspend_mode_stored = 0;

int rtk_set_suspend_mode(const char *buf, int *n)
{
    const char *p;
    int len;
    int ret = 0;
    char *mode = "mem\n";

    p = memchr(buf, '\n', *n);
    len = p ? p - buf : *n;

    if (strncmp(buf, "standby", len) == 0) {
        pr_debug("[RTD119x_PM] GET state = standby\n");
        pr_debug("[RTD119x_PM] SET state = mem, suepend_mode = wfi\n");
        suspend_mode = SUSPEND_TO_WFI;
        mode = NULL;
    } else if (strncmp(buf, "sleep", len) == 0) {
        pr_debug("[RTD119x_PM] GET state = sleep\n");
        pr_debug("[RTD119x_PM] SET state = mem, suepend_mode = ram\n");
        suspend_mode = SUSPEND_TO_RAM;
    } else if (strncmp(buf, "off", len) == 0) {
         pr_debug("[RTD119x_PM] GET state = off\n");
         pr_debug("[RTD119x_PM] SET state = mem, suepend_mode = coolboot\n");
        suspend_mode = SUSPEND_TO_COOLBOOT;
    } else if (strncmp(buf, "mem", len) == 0) {
        if (suspend_mode_stored) {
            pr_info("[RTD119x_PM] GET state = mem, suepend_mode = %s\n", rtk_suspend_states[suspend_mode]);
            pr_info("[RTD119x_PM] compatible mode: suepend_mode will be reset AFTER THIS SUSPEND\n");
        } else {
            pr_debug("[RTD119x_PM] GET state = mem\n");
            pr_debug("[RTD119x_PM] SET state = mem, suepend_mode = ram\n");
            suspend_mode = SUSPEND_TO_RAM;
        }
    } else
        return 0;

    suspend_mode_stored = 0;

    if (mode) {
        *n = strlen(mode);
        strncpy((char *)buf, mode, *n);
    }

    return ret;
}
EXPORT_SYMBOL(rtk_set_suspend_mode);

int rtk_suspend_wakeup_etn(void)
{
    void __iomem * reg;

    /* Release reset */
    reg = IOMEM(RTK_VIRT_ADDR_MAP(0x18000000));
    writel(readl(reg) | BIT(14), reg);

    __delay(100);

    /* Turn on clock */
    reg = IOMEM(RTK_VIRT_ADDR_MAP(0x1800000c));
    writel(readl(reg) | BIT(9), reg);

    return 0;
}

int rtk_suspend_wakeup_acpu(void)
{
    WRITE_REG_INT32U(0x1801a138, 0x00000000);
    __delay(1000);
    WRITE_REG_INT32U(0x18000328, 0x00000008);
    WRITE_REG_INT32U(0x18000320, 0x0000ace7);
    WRITE_REG_INT32U(0x18000328, 0x0000000c);
    __delay(1000);
    return 0;
}

struct _memory_verified_handle {
    unsigned char * memAddress;
    size_t memByte;
};

typedef struct _memory_verified_handle * memory_verified_handle_t;

unsigned char memory_verified_datagen(int i)
{
    return (unsigned char) (i & 0xff);
}

struct _memory_verified_handle * memory_verified_handle_create(size_t byte)
{
    int i;
    struct _memory_verified_handle * handle =
        (struct _memory_verified_handle *) kmalloc(sizeof(struct _memory_verified_handle), GFP_KERNEL);

    if (!handle)
        return NULL;

    /*
     * > 32KB : vmalloc
     * < 32KB : kmalloc
     */
    if (byte > 0x8000)
        handle->memAddress = (char *) vmalloc(byte);
    else
        handle->memAddress = (char *) kmalloc(byte, GFP_KERNEL);

    if (!handle->memAddress) {
        kfree(handle);
        return NULL;
    }

    for (i=0; i<byte; i++)
        handle->memAddress[i] = memory_verified_datagen(i);

    handle->memByte = byte;

    return handle;
}

int memory_verified_release(struct _memory_verified_handle * handle)
{
    int ret = 0,i;
    if (!handle) {
        eprintk("[%s] handle is NULL!!!\n",__func__);
        return -1;
    }

    if (!handle->memByte) {
        ret = -2;
        eprintk("[%s] handle %p (memByte = %ld, memAddress = 0x%08x)\n",
                __func__, (void *) handle, (long int) handle->memByte, (unsigned int) handle->memAddress);
        if (handle->memAddress)
            goto free1;
        else
            goto free0;
    }

    for (i=0; i < handle->memByte; i++) {
        unsigned char data = memory_verified_datagen(i);
        if (handle->memAddress[i] != data) {
            eprintk("[%s] handle %p memAddress[0x%x] => 0x%x != 0x%x (%ld bytes at 0x%08x)\n",
                    __func__, (void *) handle, i, handle->memAddress[i], data,
                    (long int) handle->memByte, (unsigned int) handle->memAddress);
            ret = -4;
#if 0
            {
                unsigned int startByte = (i & ~0xfUL);
                unsigned int sizeByte = 0xf0;
                if ((startByte + sizeByte) > handle->memByte)
                    sizeByte = handle->memByte - startByte;
                eprintk("memory phyAddt 0x%08x\n", virt_to_phys(&handle->memAddress[i]));
                hexdump("memory verified error\n", &handle->memAddress[startByte], sizeByte);
            }
#endif
        }

    }

#if 1
    if (ret == -4) {
        eprintk("memory phyAddt 0x%08x\n", virt_to_phys(handle->memAddress))
        hexdump("memory verified error\n", handle->memAddress, handle->memByte);
    }
#endif

free1:
    kfree(handle->memAddress);
free0:
    kfree(handle);

    return ret;
}

int rtk_suspend_valid(suspend_state_t state)
{
    return state == PM_SUSPEND_MEM;
}

static int notrace rtk_iso_suspend(unsigned long param)
{
    enum _suspend_mode mode = (enum _suspend_mode)param;

    // TEDTED
    //arch_timer_suspend();

    iprintk("[%s] flush cache...\n", __func__);
    flush_cache_all();                  
    outer_flush_all();
    //outer_disable();

    dsb_sev();

    iprintk("[%s] Ready to suspend! (mode:%d)", __func__, mode);
    if (mode == SUSPEND_TO_COOLBOOT)
        notify_acpu(NOTIFY_SUSPEND_TO_COOLBOOT);
    else if (mode == SUSPEND_TO_RAM)
        notify_acpu(NOTIFY_SUSPEND_TO_RAM);
    else {
        eprintk("[%s] Suspend Mode Not Support : %d\n",__func__,mode);
        BUG();
    }

    //v7_exit_coherency_flush(louis);

    {
        int MaxCounter = 100,i = 0;
        for (i=MaxCounter; i>0; i--) {
            __delay(10000000);
            //asm("WFI");
        }
    }

    BUG();

    return  -EINVAL;
}

enum irq_report_state {
    IRQ_REPORT_PREPARE,
    IRQ_REPORT_PRINT,
};

static void rtk_suspend_irq_report(enum irq_report_state state)
{
    int i;
    static unsigned int data [32];
    void __iomem * interrupt_state = IOMEM(0xff011200);

    switch (state) {
        case IRQ_REPORT_PREPARE:
            for (i=0;i <32; i++)
                data[i] = *(volatile unsigned int *)(interrupt_state + (i * 4));
            break;
        case IRQ_REPORT_PRINT:
            for (i=0;i <32; i++) {
                unsigned int temp = 
                    *(volatile unsigned int *)(interrupt_state + (i * 4));
                if (temp != data[i]) {
                    int j,irq = i * 32;
                    wprintk("[%s] Interrupt Addr:0x%08x State: 0x%08x => 0x%08x\n",
                            __func__, (unsigned int)(interrupt_state + (i*4)),
                            data[i], temp);
                    for (j=0; j<32; j++) {
                        unsigned int mask = 0x1U << j;
                        if (mask & temp)
                            wprintk("[%s] IRQ: %d\n",__func__,(irq+j));
                    }
                }
            }
            break;
        default:
            eprintk("[%s] Unknow CMD! %d\n", __func__, state);
    }
}

static int rtk_suspend_to_wfi(void)
{
    notify_acpu(NOTIFY_SUSPEND_TO_WFI);

    rtk_suspend_irq_report(IRQ_REPORT_PREPARE);

    iprintk("[%s] wait for interrupt...............\n", __func__);
    asm("WFI");

    rtk_suspend_irq_report(IRQ_REPORT_PRINT);

    return 0;
}

static int rtk_suspend_to_ram(void)
{
    const int  MEM_VERIFIED_CNT = 20;
    int ret = 0, i;
    memory_verified_handle_t mem_vhandle[MEM_VERIFIED_CNT];
    void __iomem * resumeAddr   = IOMEM(RTK_VIRT_ADDR_MAP(ISO_DUMMY1));
    unsigned int ISODummy1Data  = readl(resumeAddr);

    iprintk("[%s] cpu resume vaddr:0x%08x paddr:0x%08x\n", __func__,
            (unsigned int)v7_cpu_resume,(unsigned int)virt_to_phys(v7_cpu_resume));

    hexdump("v7_cpu_resume", (unsigned char *) v7_cpu_resume, 0x100);
    writel(virt_to_phys(v7_cpu_resume), resumeAddr);

    BUG_ON(!irqs_disabled());

    cpu_pm_enter();

#ifdef CONFIG_ARM_ARCH_TIMER
    
    //TEDTED
    //rtk_clocksource_suspend();
	//clocksource_suspend();
    //clockevents_suspend();
    //arch_timer_suspend();
#endif

    for (i=0; i<MEM_VERIFIED_CNT; i++)
        mem_vhandle[i] = memory_verified_handle_create(0x4000);

    rtk_suspend_irq_report(IRQ_REPORT_PREPARE);

    ret = cpu_suspend((unsigned long)SUSPEND_TO_RAM, rtk_iso_suspend);

    if (ret)
        return ret;

    /* Restore iso dummy data */
    writel(ISODummy1Data, resumeAddr);

    //writel(0xFFFFFFFE, IOMEM(0xfe007008));
    writel(readl(IOMEM(0xfe007418)) | BIT(0), IOMEM(0xfe007418));
    writel(readl(IOMEM(0xfe007410)) & ~BIT(10), IOMEM(0xfe007410));

#ifdef CONFIG_ARM_ARCH_TIMER
    
    // TEDTED
    //arch_timer_resume();
    //rtk_clocksource_resume();
    writel(0x1, IOMEM(0xff018000));
#endif

    rtk_suspend_irq_report(IRQ_REPORT_PRINT);

    rtk_suspend_wakeup_acpu();
    rtk_suspend_wakeup_etn();

    writel(readl(IOMEM(0xfe01d100)) & ~BIT(5), IOMEM(0xfe01d100));		// wrap_a7 issue nCORERESET
    //mcpm_cpu_powered_up();

    cpu_pm_exit();
    //clockevents_resume();
	//clocksource_resume();

    rtk119x_prepare_cpus(NR_CPUS);
    outer_resume();

    iprintk("[%s] resume memory verifying ... state 0\n", __func__);
    for (i=0; i<MEM_VERIFIED_CNT; i++)
        memory_verified_release(mem_vhandle[i]);


    iprintk("[%s] resume memory verifying ... state 1\n", __func__);
    for (i=0; i<MEM_VERIFIED_CNT; i++)
        mem_vhandle[i] = memory_verified_handle_create(0x4000);

    for (i=0; i<MEM_VERIFIED_CNT; i++)
        memory_verified_release(mem_vhandle[i]);

	dsb_sev();
    return ret;
}

static int rtk_suspend_to_coolboot(void)
{
    int ret = 0;
    ret = cpu_suspend((unsigned long)SUSPEND_TO_COOLBOOT, rtk_iso_suspend);
    return ret;
}

void rtk_suspend_gpip_output_change_suspend(void)
{
    int i;
    unsigned int val = rtk_suspend_gpio_output_change_en_get();
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        unsigned int mask = 0x1U << i;

        if (!(val & mask))
            continue;

        iprintk("[%s] gpio:%d set ouput =>  %s\n", __func__, i+SUSPEND_ISO_GPIO_BASE, 
                (rtk_suspend_gpio_output_change_act_get() & mask) ? "HIGH" : "LOW")

        gpio_direction_output(i+SUSPEND_ISO_GPIO_BASE,
                (rtk_suspend_gpio_output_change_act_get() & mask) ? 1 : 0 );
    }
}

void rtk_suspend_gpip_output_change_resume(void)
{
    int i;
    unsigned int val = rtk_suspend_gpio_output_change_en_get();
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        unsigned int mask = 0x1U << i;

        if (!(val & mask))
            continue;

        iprintk("[%s] gpio:%d set ouput =>  %s\n", __func__, i+SUSPEND_ISO_GPIO_BASE,
                (rtk_suspend_gpio_output_change_act_get() & mask) ? "LOW" : "HIGH")

        gpio_direction_output(i+SUSPEND_ISO_GPIO_BASE,
                (rtk_suspend_gpio_output_change_act_get() & mask) ? 0 : 1 );
    }
}

static int rtk_suspend_enter(suspend_state_t suspend_state)
{
    int ret = 0;
    iprintk("[%s]\n",__func__);

    if (!rtk_suspend_valid(suspend_state)) {
        eprintk("[%s] suspend_state:%d not support!\n", __func__, (int) suspend_state);
        return  -EINVAL;
    }

    switch(suspend_state) {
        case PM_SUSPEND_MEM:

            iprintk("[%s] rtk_ip_power_off() ...\n", __func__);
            
            rtk_ip_power_off();

#if 1 // legacy
            if (wifi_gpio != -1) {
                iprintk("[%s] wifi gpio : POWER DOWN ...\n", __func__);
                gpio_direction_output(wifi_gpio, 0);
            }
#endif

            rtk_suspend_gpip_output_change_suspend();

            if (suspend_mode == SUSPEND_TO_WFI)
                ret = rtk_suspend_to_wfi();
            else if (suspend_mode == SUSPEND_TO_COOLBOOT)
                ret = rtk_suspend_to_coolboot();
            else if (suspend_mode == SUSPEND_TO_RAM)
                ret = rtk_suspend_to_ram();
            else
                BUG();

            if (ret) {
                eprintk("[%s] ERROR!!!!! to suspend! (%d)\n",__func__,ret);
                BUG();
                break;
            }

            iprintk("[%s] platform resume ...\n", __func__);
            notify_acpu(NOTIFY_RESUME_PLATFORM);

#if 1 // legacy
            if (wifi_gpio != -1)
                gpio_direction_output(wifi_gpio, 1);	//power up
#endif
            rtk_suspend_gpip_output_change_resume();

            rtk_ip_power_on();

            break;
        default:
            ret = -EINVAL;
            break;
    }
    return  ret;
}

static int rtk_suspend_begin(suspend_state_t suspend_state)
{
    dprintk("%s\n",__func__);

    if (!rtk_suspend_valid(suspend_state)) {
        eprintk("[%s] suspend_state:%d not support!\n", __func__, (int) suspend_state);
        return  -EINVAL;
    }

    switch(suspend_state) {
        case PM_SUSPEND_MEM:
            cpu_idle_poll_ctrl(true);
            break;
        default:
            return  -EINVAL;
    }
	return 0;
}

static void rtk_suspend_end(void)
{
    dprintk("%s\n",__func__);
    notify_acpu(NOTIFY_RESUME_END);
	cpu_idle_poll_ctrl(false);
}

struct platform_suspend_ops rtk_suspend_ops = {
	.begin		= rtk_suspend_begin,
	.end		= rtk_suspend_end,
	.enter		= rtk_suspend_enter,
	.valid		= rtk_suspend_valid,
};

#ifdef CONFIG_NAS_GPIO_SHUTDOWN
extern unsigned char *gpio_shutdown_list;
static void rtk_nas_poweroff(void)
{
    int i, value;

    for (i=0; i<ARCH_NR_GPIOS; i++){
        value = (int)(gpio_shutdown_list[i]);
        if(0 == value)
            continue;
        gpio_free(i);
        if(gpio_request(i, NULL)){
            dprintk("[%s]GPIO %d request error\n",__func__, i);
            continue;
        }
        gpio_direction_output(i, value-1);
        gpio_free(i);
    }

    /* machine_halt() */
    local_irq_disable();
    while (1);

    return;
}
#else
static void rtk_poweroff_to_suspend_prepare(void)
{
    printk(KERN_INFO "[RTD119x_PM] Power off to Suspend Prepare.\n");

    suspend_mode = SUSPEND_TO_COOLBOOT;
    pm_suspend(PM_SUSPEND_MEM);
    return;
};

static void rtk_poweroff_to_suspend(void)
{
    printk(KERN_INFO "[RTD119x_PM] Power off to Suspend.\n");
    return;
};
#endif

int __init rtk_suspend_init(void)
{
    struct device_node  *p_suspend_nd       = NULL;
	struct device_node  *p_bt_wakeup_nd     = NULL;

    acpu_set_flag(0x00000000);
    rtk_suspend_wakeup_flags_set(0);
    rtk_suspend_resume_state_set(RESUME_NONE);
    rtk_suspend_resume_data_set(0);
    rtk_suspend_gpio_wakeup_en_set(0);
    rtk_suspend_gpio_wakeup_act_set(0);
    rtk_suspend_gpio_output_change_en_set(0);
    rtk_suspend_gpio_output_change_act_set(0);
    rtk_suspend_timer_sec_set(0);

	p_suspend_nd = of_find_compatible_node(NULL, NULL, "Realtek,suspend");

    if (p_suspend_nd && of_device_is_available(p_suspend_nd)) {
        const u32 *prop;
        int size;

        {
            int cnt_wakeup_gpio_en = 0;
            int cnt_wakeup_gpio_act = 0;
            int cnt_wakeup_gpio_list    = of_gpio_named_count(p_suspend_nd, "wakeup-gpio-list");
            const u32 * prop_en         = of_get_property(p_suspend_nd, "wakeup-gpio-enable", &cnt_wakeup_gpio_en);
            const u32 * prop_act        = of_get_property(p_suspend_nd, "wakeup-gpio-activity", &cnt_wakeup_gpio_act);

            cnt_wakeup_gpio_en  /= sizeof(u32);
            cnt_wakeup_gpio_act /= sizeof(u32);

            iprintk("[%s:%d] wakeup-gpio Cnt: en(%d) act(%d) list(%d)\n", __func__, __LINE__,
                    cnt_wakeup_gpio_en,
                    cnt_wakeup_gpio_act,
                    cnt_wakeup_gpio_list);

            if (cnt_wakeup_gpio_en != 0
                    && (cnt_wakeup_gpio_en == cnt_wakeup_gpio_act)
                    && (cnt_wakeup_gpio_act == cnt_wakeup_gpio_list))
            {
                int i;
                for (i=0;i<cnt_wakeup_gpio_list;i++) {

                    int en  = of_read_number(prop_en,   1 + i);
                    int act = of_read_number(prop_act,  1 + i);
                    int wakeup_gpio = of_get_named_gpio(p_suspend_nd, "wakeup-gpio-list", i);
                    int gpio_iso_num = wakeup_gpio - SUSPEND_ISO_GPIO_BASE;

                    if (!en) {
                        wprintk("[%s] wakeup-gpio[%d] States is disable! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, wakeup_gpio);
                        continue;
                    }

                    if (!gpio_is_valid(wakeup_gpio)) {
                        eprintk("[%s] wakeup-gpio[%d] Validation failed! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, wakeup_gpio);
                        continue;
                    }

                    if(gpio_request(wakeup_gpio, p_suspend_nd->name)) {
                        eprintk("[%s] wakeup-gpio[%d] Request failed! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, wakeup_gpio);
                        continue;
                    }

                    if (gpio_iso_num < 0 || gpio_iso_num >= SUSPEND_ISO_GPIO_SIZE) {
                        eprintk("[%s] wakeup-gpio[%d] Out of iso range! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, wakeup_gpio);
                        continue;
                    }

                    iprintk("[%s] wakeup-gpio[%d] Successful registration! (en:%d act:%d gpio:%d)\n",
                            __func__, i, en, act, wakeup_gpio);

                    {
                        unsigned int val;
                        val = rtk_suspend_gpio_wakeup_en_get();
                        if (val == -1U)
                            val = 0;
                        if (en)
                            val |= (0x1U << gpio_iso_num);
                        else
                            val &= ~(0x1U << gpio_iso_num);
                        rtk_suspend_gpio_wakeup_en_set(val);

                        val = rtk_suspend_gpio_wakeup_act_get();
                        if (act)
                            val |= (0x1U << gpio_iso_num);
                        else
                            val &= ~(0x1U << gpio_iso_num);
                        rtk_suspend_gpio_wakeup_act_set(val);
                    }


                }

            }
        }


        {
            int cnt_output_change_gpio_en = 0;
            int cnt_output_change_gpio_act = 0;
            int cnt_output_change_gpio_list     = of_gpio_named_count(p_suspend_nd, "gpio-output-change-list");
            const u32 * prop_en                 = of_get_property(p_suspend_nd,     "gpio-output-change-enable", &cnt_output_change_gpio_en);
            const u32 * prop_act                = of_get_property(p_suspend_nd,     "gpio-output-change-activity", &cnt_output_change_gpio_act);

            cnt_output_change_gpio_en  /= sizeof(u32);
            cnt_output_change_gpio_act /= sizeof(u32);

            iprintk("[%s:%d] gpio-output-change Cnt: en(%d) act(%d) list(%d)\n", __func__, __LINE__,
                    cnt_output_change_gpio_en,
                    cnt_output_change_gpio_act,
                    cnt_output_change_gpio_list);

            if (cnt_output_change_gpio_en != 0
                    && (cnt_output_change_gpio_en == cnt_output_change_gpio_act)
                    && (cnt_output_change_gpio_act == cnt_output_change_gpio_list))
            {
                int i;
                for (i=0;i<cnt_output_change_gpio_list;i++) {
                    int en  = of_read_number(prop_en,   1 + i);
                    int act = of_read_number(prop_act,  1 + i);
                    int output_change_gpio = of_get_named_gpio(p_suspend_nd, "gpio-output-change-list", i);
                    int gpio_iso_num = output_change_gpio - SUSPEND_ISO_GPIO_BASE;

                    if (!en) {
                        wprintk("[%s] gpio-output-change[%d] States is disable! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, output_change_gpio);
                        continue;
                    }

                    if (!gpio_is_valid(output_change_gpio)) {
                        eprintk("[%s] gpio-output-change[%d] Validation failed! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, output_change_gpio);
                        continue;
                    }

                    if(gpio_request(output_change_gpio, p_suspend_nd->name)) {
                        eprintk("[%s] gpio-output-change[%d] Request failed! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, output_change_gpio);
                        continue;
                    }

                    if (gpio_iso_num < 0 || gpio_iso_num >= SUSPEND_ISO_GPIO_SIZE) {
                        eprintk("[%s] gpio-output-change[%d] Out of iso range! (en:%d act:%d gpio:%d)\n",
                                __func__, i, en, act, output_change_gpio);
                        continue;
                    }

                    iprintk("[%s] gpio-output-change[%d] Successful registration! (en:%d act:%d gpio:%d)\n",
                            __func__, i, en, act, output_change_gpio);

                    {
                        unsigned int val;
                        val = rtk_suspend_gpio_output_change_en_get();
                        if (val == -1U)
                            val = 0;
                        if (en)
                            val |= (0x1U << gpio_iso_num);
                        else
                            val &= ~(0x1U << gpio_iso_num);
                        rtk_suspend_gpio_output_change_en_set(val);

                        val = rtk_suspend_gpio_output_change_act_get();
                        if (act)
                            val |= (0x1U << gpio_iso_num);
                        else
                            val &= ~(0x1U << gpio_iso_num);
                        rtk_suspend_gpio_output_change_act_set(val);
#if 1 // legacy
                        acpu_set_bt_wakeup_host(gpio_iso_num,(act)?1:0);
#endif
                    }
                }
            }
        }

#if 0 // legacy
        /*
         * WiFi GPIO
         */
        wifi_gpio = of_get_named_gpio(p_suspend_nd, "realtek,wifi-gpio", 0);
        if (gpio_is_valid(wifi_gpio)) {
            if(gpio_request(wifi_gpio, p_suspend_nd->name))
                eprintk("%s ERROR Request wifi gpio fail\n",__func__);
        } else {
            wprintk("%s ERROR wifi gpio is not valid\n",__func__);
        }
#endif

        /*
         * Suspend Mode
         */
        prop = of_get_property(p_suspend_nd, "suspend-mode", &size);
        if (prop) {
            int temp = of_read_number(prop,1);
            if (temp > MAX_SUSPEND_MODE || temp < 0) {
                eprintk("[%s] set suspend-mode error! %d (default:%d) \n",__func__,temp,(int)suspend_mode);
            } else {
                suspend_mode = temp;
                iprintk("[%s] set suspend-mode = %s\n",__func__, rtk_suspend_states[suspend_mode]);
            }
        }

        /*
         * wakeup flags
         */
        prop = of_get_property(p_suspend_nd, "wakeup-flags", &size);
        if (prop) {
            int temp = of_read_number(prop,1);
            if (temp < 0) {
                eprintk("[%s] set wakeup-flags error! 0x%x\n", __func__, temp);
                rtk_suspend_wakeup_flags_set(fWAKEUP_ON_IR|fWAKEUP_ON_GPIO|fWAKEUP_ON_ALARM|fWAKEUP_ON_CEC);
                iprintk("[%s] wakeup flags set default : 0x%x\n", __func__, rtk_suspend_wakeup_flags_get());
            } else {
                rtk_suspend_wakeup_flags_set(temp);
                iprintk("[%s] set set wakeup-flags = 0x%x\n",__func__, rtk_suspend_wakeup_flags_get());
            }
        } else {
            rtk_suspend_wakeup_flags_set(fWAKEUP_ON_IR|fWAKEUP_ON_GPIO|fWAKEUP_ON_ALARM|fWAKEUP_ON_CEC);
            iprintk("[%s] wakeup flags set default : 0x%x\n", __func__, rtk_suspend_wakeup_flags_get());
        }
    }

#if 1 // legacy
	p_bt_wakeup_nd = of_find_compatible_node(NULL, NULL, "Realtek,bt_wakeup_host");

    if (p_bt_wakeup_nd && of_device_is_available(p_bt_wakeup_nd)) {
        int bt_wakeup_gpio = of_get_named_gpio(p_bt_wakeup_nd, "realtek,bt-wakeup-gpio", 0);
        const char *activity_level;
        if (!gpio_is_valid(bt_wakeup_gpio))
        {
            //BUG();
            eprintk("%s ERROR bt_wakeup_host gpio is not valid\n",__func__);
        }
        if(gpio_request(bt_wakeup_gpio, p_bt_wakeup_nd->name))
        {
            //BUG();
            eprintk("%s ERROR Request bt_wakeup_host gpio fail\n",__func__);
        }
        if(of_property_read_string(p_bt_wakeup_nd, "activity_level", &activity_level) < 0)
        {
			//BUG();
			eprintk("%s ERROR get bt_wakeup_host activity level fail\n",__func__);
        }
        else
        {
			if(bt_wakeup_gpio>=60)
			{
				if (!strcmp(activity_level, "low"))
					acpu_set_bt_wakeup_host(bt_wakeup_gpio-60,0);
				else
					acpu_set_bt_wakeup_host(bt_wakeup_gpio-60,1);
			}
		}
    }
#endif

	suspend_set_ops(&rtk_suspend_ops);

#ifdef CONFIG_NAS_GPIO_SHUTDOWN
	pm_power_off = rtk_nas_poweroff;
#else
  pm_power_off_prepare = rtk_poweroff_to_suspend_prepare;
  pm_power_off = rtk_poweroff_to_suspend;
#endif

	return 0;
}

arch_initcall(rtk_suspend_init);

#ifdef CONFIG_SYSFS
#define RTK_SUSPEND_ATTR(_name)             \
{                                           \
    .attr = {.name = #_name, .mode = 0644}, \
    .show =  rtk_suspend_##_name##_show,    \
    .store = rtk_suspend_##_name##_store,   \
}

static enum _suspend_mode rtk_suspend_decode_mode(const char *buf, size_t n)
{
	const char * const *s;
	char *p;
	int len;
    int i;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

    for (i=0;i<MAX_SUSPEND_MODE;i++) {
        s = &rtk_suspend_states[i];
        if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
            return i;
    }

	return MAX_SUSPEND_MODE;
}

static ssize_t rtk_suspend_mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    for (i=0;i<MAX_SUSPEND_MODE;i++) {
        if (i == suspend_mode)
            n += sprintf(buf+n, "=> ");
        else
            n += sprintf(buf+n, "   ");
        n += sprintf(buf+n, "%s\n",rtk_suspend_states[i]);
    }
    n += sprintf(buf+n, "\n");
    return n;
}

static ssize_t rtk_suspend_mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    enum _suspend_mode mode = rtk_suspend_decode_mode(buf,count);
    if (mode < MAX_SUSPEND_MODE) {
        suspend_mode = mode;
        return count;
    }
    return -ENOMEM;
}

static enum _suspend_wakeup rtk_suspend_decode_wakeup(const char *buf, size_t n)
{
	const char * const *s;
	char *p;
	int len;
    int i;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

    for (i=0;i<eWAKEUP_ON_MAX;i++) {
        s = &rtk_suspend_wakeup_states[i];
        if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
            return i;
    }

	return eWAKEUP_ON_MAX;
}

static ssize_t rtk_suspend_wakeup_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    unsigned int val = rtk_suspend_wakeup_flags_get();
    for (i=0;i<eWAKEUP_ON_MAX;i++) {

        if (val & (0x1U << i))
            n += sprintf(buf+n, " * ");
        else
            n += sprintf(buf+n, "   ");
        n += sprintf(buf+n, "%s\n", rtk_suspend_wakeup_states[i]);
    }
    n += sprintf(buf+n, "\n");
    return n;
}

static ssize_t rtk_suspend_wakeup_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    enum _suspend_wakeup wakeup = rtk_suspend_decode_wakeup(buf,count);
    if (wakeup < eWAKEUP_ON_MAX) {
        rtk_suspend_wakeup_flags_set(rtk_suspend_wakeup_flags_get() ^ (0x1U << wakeup));
        return count;
    }
    return -ENOMEM;
}

static ssize_t rtk_suspend_resume_state_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    unsigned int val = rtk_suspend_resume_state_get();
    if (val >= RESUME_MAX_STATE)
        return sprintf(buf, "(not ready)\n");

    if (val == RESUME_GPIO)
        return sprintf(buf, " %s %d\n",rtk_suspend_resume_states[val], rtk_suspend_resume_data_get() + SUSPEND_ISO_GPIO_BASE);
    else
        return sprintf(buf, " %s %d\n",rtk_suspend_resume_states[val], rtk_suspend_resume_data_get());
}

static ssize_t rtk_suspend_resume_state_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    return count;
}

static ssize_t rtk_suspend_gpio_wakeup_en_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    unsigned int val = rtk_suspend_gpio_wakeup_en_get();
    if (val == -1U)
        return sprintf(buf, "(not ready)\n");

    n += sprintf(buf+n, " En | GPIO(ISO)\n");
    n += sprintf(buf+n, " ---+----------\n");
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        if (val & (0x1U << i))
            n += sprintf(buf+n, "  * |  %d\n",i);
        else
            n += sprintf(buf+n, "    |  %d\n",i);
    }
    n += sprintf(buf+n, "\n");
    return n;

}

static ssize_t rtk_suspend_gpio_wakeup_en_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    long val;
    int ret = kstrtol(buf, 10, &val);
    if (ret < 0)
        return -ENOMEM;

    if (val >= SUSPEND_ISO_GPIO_SIZE)
        return -ENOMEM;

#if 0
    return count;
#endif

    rtk_suspend_gpio_wakeup_en_set(rtk_suspend_gpio_wakeup_en_get() ^ (0x1U << val));

    return count;
}

static ssize_t rtk_suspend_gpio_wakeup_act_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    unsigned int val = rtk_suspend_gpio_wakeup_act_get();
    if (val == -1U)
        return sprintf(buf, "(not ready)\n");

    n += sprintf(buf+n, " Act| GPIO(ISO)\n");
    n += sprintf(buf+n, " ---+----------\n");
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        if (!(rtk_suspend_gpio_wakeup_en_get() &  (0x1U << i)))
            n += sprintf(buf+n, "    |  %d\n",i);
        else if (val & (0x1U << i))
            n += sprintf(buf+n, "  H |  %d\n",i);
        else
            n += sprintf(buf+n, "  L |  %d\n",i);
    }
    n += sprintf(buf+n, "\n");

    return n;
}

static ssize_t rtk_suspend_gpio_wakeup_act_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    long val;
    int ret = kstrtol(buf, 10, &val);
    if (ret < 0)
        return -ENOMEM;

    if (val >= SUSPEND_ISO_GPIO_SIZE)
        return -ENOMEM;

#if 0
    return count;
#endif

    if (rtk_suspend_gpio_wakeup_en_get() &  (0x1U << val))
        rtk_suspend_gpio_wakeup_act_set(rtk_suspend_gpio_wakeup_act_get() ^ (0x1U << val));

    return count;
}

static ssize_t rtk_suspend_gpio_output_change_en_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    unsigned int val = rtk_suspend_gpio_output_change_en_get();
    if (val == -1U)
        return sprintf(buf, "(not ready)\n");

    n += sprintf(buf+n, " En | GPIO(ISO)\n");
    n += sprintf(buf+n, " ---+----------\n");
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        if (val & (0x1U << i))
            n += sprintf(buf+n, "  * |  %d\n",i);
        else
            n += sprintf(buf+n, "    |  %d\n",i);
    }
    n += sprintf(buf+n, "\n");
    return n;

}

static ssize_t rtk_suspend_gpio_output_change_en_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    long val;
    int ret = kstrtol(buf, 10, &val);
    if (ret < 0)
        return -ENOMEM;

    if (val >= SUSPEND_ISO_GPIO_SIZE)
        return -ENOMEM;

#if 0
    return count;
#endif

    rtk_suspend_gpio_output_change_en_set(rtk_suspend_gpio_output_change_en_get() ^ (0x1U << val));

    return count;
}

static ssize_t rtk_suspend_gpio_output_change_act_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int i,n = 0;
    unsigned int val = rtk_suspend_gpio_output_change_act_get();
    if (val == -1U)
        return sprintf(buf, "(not ready)\n");

    n += sprintf(buf+n, " Act| GPIO(ISO)\n");
    n += sprintf(buf+n, " ---+----------\n");
    for (i=0;i<SUSPEND_ISO_GPIO_SIZE;i++) {
        if (!(rtk_suspend_gpio_output_change_en_get() &  (0x1U << i)))
            n += sprintf(buf+n, "    |  %d\n",i);
        else if (val & (0x1U << i))
            n += sprintf(buf+n, "  H |  %d\n",i);
        else
            n += sprintf(buf+n, "  L |  %d\n",i);
    }
    n += sprintf(buf+n, "\n");

    return n;
}

static ssize_t rtk_suspend_gpio_output_change_act_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    long val;
    int ret = kstrtol(buf, 10, &val);
    if (ret < 0)
        return -ENOMEM;

    if (val >= SUSPEND_ISO_GPIO_SIZE)
        return -ENOMEM;

#if 0
    return count;
#endif

    if (rtk_suspend_gpio_output_change_en_get() &  (0x1U << val))
        rtk_suspend_gpio_output_change_act_set(rtk_suspend_gpio_output_change_act_get() ^ (0x1U << val));

    return count;
}

static ssize_t rtk_suspend_timer_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, " %d sec (reciprocal timer)\n", rtk_suspend_timer_sec_get());
}

static ssize_t rtk_suspend_timer_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    long val;
    int ret = kstrtol(buf, 10, &val);
    if (ret < 0)
        return -ENOMEM;

    if (val > (AUDIO_RECIPROCAL_TIMER_GET(-1UL)))
        return -ENOMEM;

    rtk_suspend_timer_sec_set(val);
    return count;
}

static struct kobj_attribute rtk_suspend_mode_attr                          = RTK_SUSPEND_ATTR(mode);
static struct kobj_attribute rtk_suspend_wakeup_attr                        = RTK_SUSPEND_ATTR(wakeup);
static struct kobj_attribute rtk_suspend_resume_state_attr                  = RTK_SUSPEND_ATTR(resume_state);
static struct kobj_attribute rtk_suspend_gpio_wakeup_en_attr                = RTK_SUSPEND_ATTR(gpio_wakeup_en);
static struct kobj_attribute rtk_suspend_gpio_wakeup_act_attr               = RTK_SUSPEND_ATTR(gpio_wakeup_act);
static struct kobj_attribute rtk_suspend_gpio_output_change_en_attr         = RTK_SUSPEND_ATTR(gpio_output_change_en);
static struct kobj_attribute rtk_suspend_gpio_output_change_act_attr        = RTK_SUSPEND_ATTR(gpio_output_change_act);
static struct kobj_attribute rtk_suspend_timer_attr                         = RTK_SUSPEND_ATTR(timer);

static struct attribute *rtk_suspend_attrs[] = {
	&rtk_suspend_mode_attr.attr,
	&rtk_suspend_wakeup_attr.attr,
	&rtk_suspend_resume_state_attr.attr,
	&rtk_suspend_gpio_wakeup_en_attr.attr,
	&rtk_suspend_gpio_wakeup_act_attr.attr,
	&rtk_suspend_gpio_output_change_en_attr.attr,
	&rtk_suspend_gpio_output_change_act_attr.attr,
	&rtk_suspend_timer_attr.attr,
    NULL,
};

static struct attribute_group rtk_suspend_attr_group = {
	.attrs = rtk_suspend_attrs,
};

static struct kobject *rtk_suspend_kobj;

static int __init suspend_sysfs_init(void)
{
    int ret;

    rtk_suspend_kobj = kobject_create_and_add("suspend", kernel_kobj);
    if (!rtk_suspend_kobj)
        return -ENOMEM;
    ret = sysfs_create_group(rtk_suspend_kobj, &rtk_suspend_attr_group);
    if (ret)
        kobject_put(rtk_suspend_kobj);
    return ret;
}

module_init(suspend_sysfs_init)
#endif
