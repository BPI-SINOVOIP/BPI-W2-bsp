/*
 * rtd139x_suspend.c - power management driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

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
#include <linux/of_address.h>
#include <linux/reboot.h>
#include <linux/clocksource.h>
#include <linux/clockchips.h>
#include <linux/cpu_pm.h>
#include <linux/vmalloc.h>
#include <linux/tick.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/irqchip/arm-gic.h>
#include <asm/system_misc.h>
#include <asm/cacheflush.h>
#include <asm/suspend.h>
#include <soc/realtek/memory.h>
#include <soc/realtek/rtk_cpu.h>

#include "rtd139x_suspend.h"

#define DEV_NAME "RTD139x_PM"
#define SYS_GROUP1_CK_SEL 0x98000018
#define SYS_PLL_SCPU1 0x98000104
#define SUSPEND_VERSION_MASK(v) ((v&0xffff) << 16)
#define BT_WAKEUP_IGPIO(n) (0x1 << n)//n:0 to 20
#define CPU0_RESUME_ADDR 0x000006A4

static int suspend_version = 2;
static unsigned int suspend_context;

void __iomem *RTK_CRT_BASE;
void __iomem *RTK_AIO_BASE;
void __iomem *RTK_ISO_BASE;
void __iomem *RTK_TVE_BASE;
void __iomem *RTK_SB2_BASE;
void __iomem *RTK_MISC_BASE;
void __iomem *RTK_GIC_DIST_BASE;
void __iomem *RTK_CPU_WRAPPER_BASE;

#define rtk_suspend_shm_func(_name, _offset, _def) \
void rtk_suspend_##_name##_set(unsigned int val) \
{ \
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT; \
	writel(__cpu_to_be32(SUSPEND_MAGIC_MASK | _def##_MASK(val)), \
	&(ipc->_offset)); \
} \
unsigned int rtk_suspend_##_name##_get(void) \
{ \
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT; \
	unsigned int val = __be32_to_cpu(readl(&(ipc->_offset))); \
	if (SUSPEND_MAGIC_GET(val) != SUSPEND_MAGIC_KEY) { \
		pr_err("[%s] Error! val = 0x%08x\n", DEV_NAME, val); \
		return -1; \
	} \
	return _def##_GET(val); \
}

rtk_suspend_shm_func(wakeup_flags, suspend_wakeup_flag, WAKEUP_FLAGS);
rtk_suspend_shm_func(resume_state, acpu_resume_state, RESUME_STATE);
rtk_suspend_shm_func(resume_data, acpu_resume_state, RESUME_DATA);
rtk_suspend_shm_func(gpio_wakeup_en, gpio_wakeup_enable, GPIO_WAKEUP_EN);
rtk_suspend_shm_func(gpio_wakeup_act, gpio_wakeup_activity, GPIO_WAKEUP_ACT);
rtk_suspend_shm_func(gpio_out_en, gpio_output_change_enable,
	GPIO_OUTPUT_CHANGE_EN);
rtk_suspend_shm_func(gpio_out_act, gpio_output_change_activity,
	GPIO_OUTPUT_CHANGE_ACT);
rtk_suspend_shm_func(gpio_wakeup_en2, gpio_wakeup_enable2, GPIO_WAKEUP_EN2);
rtk_suspend_shm_func(gpio_wakeup_act2, gpio_wakeup_activity2,
	GPIO_WAKEUP_ACT2);
rtk_suspend_shm_func(gpio_out_en2, gpio_output_change_enable2,
	GPIO_OUTPUT_CHANGE_EN2);
rtk_suspend_shm_func(gpio_out_act2, gpio_output_change_activity2,
	GPIO_OUTPUT_CHANGE_ACT2);

rtk_suspend_shm_func(gpio_wakeup_en3, gpio_wakeup_enable3, GPIO_WAKEUP_EN3);
rtk_suspend_shm_func(gpio_wakeup_act3, gpio_wakeup_activity3,
	GPIO_WAKEUP_ACT3);

rtk_suspend_shm_func(timer_sec, audio_reciprocal_timer_sec,
	AUDIO_RECIPROCAL_TIMER);

static void hexdump(char *note, unsigned char *buf, unsigned int len)
{
	pr_crit("%s\n", note);
	print_hex_dump(KERN_CONT, "", DUMP_PREFIX_OFFSET, 16, 1, buf, len,
		false);
}

void acpu_set_flag(uint32_t flag)
{
	struct rtk_ipc_shm __iomem *ipc = (void __iomem *)IPC_SHM_VIRT;

	writel(__cpu_to_be32(SUSPEND_VERSION_MASK(suspend_version)),
		&(ipc->suspend_mask));

	if (suspend_version == 1)
		writel(__cpu_to_be32(flag), &(ipc->suspend_flag));
	else
		writel(__cpu_to_be32(flag | AUTHOR_MASK(AUTHOR_SCPU)),
			&(ipc->suspend_flag));
}

void notify_acpu(enum _notify_flag flag)
{
	pr_info("[%s] Notify ACPU, flag= %d\n", DEV_NAME, flag);

	switch (flag) {
	case NOTIFY_SUSPEND_TO_RAM:
	case NOTIFY_SUSPEND_TO_COOLBOOT:
	case NOTIFY_SUSPEND_TO_WFI:
		if (suspend_version == 1) {
			acpu_set_flag(0x000018ff);
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

int rtk_suspend_wakeup_acpu(void)
{
	pr_info("[%s] Wakeup ACPU\n", DEV_NAME);

	writel(0x00000000, RTK_SB2_BASE + 0x138);
	__delay(1000);
	writel(0x00000008, RTK_CRT_BASE + 0x328);
	writel(0x0000ace7, RTK_CRT_BASE + 0x320);
	writel(0x0000000c, RTK_CRT_BASE + 0x328);
	__delay(1000);
	return 0;
}

struct _memory_verified_handle {
	unsigned char *memAddress;
	size_t memByte;
};

struct _memory_verified_handle phys_wb_area[] = {
	{(unsigned char *)0x0a000000, 0x20},
	{(unsigned char *)0x0a001000, 0x20}
};

unsigned char memory_verified_datagen(int i)
{
	return (unsigned char) (i & 0xff);
}

struct _memory_verified_handle *memory_verified_handle_create(size_t byte)
{
	int i = 0;

	struct _memory_verified_handle *handle =
		(struct _memory_verified_handle *)
		kmalloc(sizeof(struct _memory_verified_handle), GFP_KERNEL);

	if (!handle)
		return NULL;

	/*
	 * > 32KB : vmalloc
	 * < 32KB : kmalloc
	 */
	if (byte > 0x8000)
		handle->memAddress = vmalloc(byte);
	else
		handle->memAddress = kmalloc(byte, GFP_KERNEL);

	if (!handle->memAddress) {
		kfree(handle);
		return NULL;
	}

	for (i = 0; i < byte ; i++)
		handle->memAddress[i] = memory_verified_datagen(i);

	handle->memByte = byte;

	return handle;
}

int memory_verified_release(struct _memory_verified_handle *handle)
{
	int ret = 0, i = 0;
	unsigned char data;

	if (!handle) {
		pr_err("[%s] handle is NULL !\n", DEV_NAME);
		return -1;
	}

	if (!handle->memByte) {
		ret = -2;
		pr_info("[%s] handle %p ", DEV_NAME, (void *) handle);
		pr_info("(memByte = %ld, memAddress = 0x%08lx)\n",
			(long int) handle->memByte,
			(unsigned long) handle->memAddress);

		if (handle->memAddress)
			goto free1;
		else
			goto free0;
	}

	for (i = 0 ; i < handle->memByte ; i++) {
		data = memory_verified_datagen(i);

		if (handle->memAddress[i] != data) {
			pr_info("[%s] handle %p memAddress[0x%x]",
				DEV_NAME, (void *) handle, i);
			pr_info("=> 0x%x != 0x%x (%ld bytes at 0x%08lx)\n",
				handle->memAddress[i], data,
				(long int) handle->memByte,
				(unsigned long) handle->memAddress);
			ret = -4;
		}
	}

	if (ret == -4) {
		pr_err("[%s] memory phyAddt 0x%08llx\n",
			DEV_NAME, __pa(handle->memAddress));
		hexdump("[%s] memory verified error\n",
			handle->memAddress, handle->memByte);
	}

free1:
	kfree(handle->memAddress);
free0:
	kfree(handle);

	return ret;
}

struct _memory_verified_handle *memory_writeback_handle_create(
	struct _memory_verified_handle *phys_area)
{
	void *tmp_addr;

	struct _memory_verified_handle *handle =
		(struct _memory_verified_handle *)
		kmalloc(sizeof(struct _memory_verified_handle), GFP_KERNEL);

	if (!handle)
		goto out;

	handle->memAddress = kmalloc(phys_area->memByte, GFP_KERNEL);

	if (!handle->memAddress) {
		kfree(handle);
		handle = NULL;
		goto out;
	}

	handle->memByte = phys_area->memByte;
	tmp_addr = phys_to_virt((phys_addr_t) phys_area->memAddress);
	hexdump("[RTD139x_PM] Before write back dump:",
		(unsigned char *) tmp_addr, phys_area->memByte);
	memcpy(handle->memAddress, tmp_addr, phys_area->memByte);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(handle->memAddress, phys_area->memByte);
#else
	__flush_dcache_area(handle->memAddress, phys_area->memByte);
#endif /* CONFIG_ARCH_MULTI_V7 */
out:
	return handle;
}

int memory_writeback_release(struct _memory_verified_handle *handle,
	struct _memory_verified_handle *phys_area)
{
	int ret = 0;
	void *tmp_addr;

	if (!handle) {
		ret = -1;
		goto out;
	}

	if (!handle->memAddress) {
		ret = -1;
		goto free_out;
	}

	tmp_addr = phys_to_virt((phys_addr_t)phys_area->memAddress);
	hexdump("[RTD139x_PM] Resume back dump:**********************",
		(unsigned char *) tmp_addr, phys_area->memByte);
	memcpy(tmp_addr, handle->memAddress, handle->memByte);
#if defined(CONFIG_ARCH_MULTI_V7)
	v7_flush_kern_dcache_area(tmp_addr, phys_area->memByte);
#else
	__flush_dcache_area(tmp_addr, phys_area->memByte);
#endif /* CONFIG_ARCH_MULTI_V7 */
	hexdump("[RTD139x_PM] After write back dump:",
		(unsigned char *) tmp_addr, phys_area->memByte);

	kfree(handle->memAddress);

free_out:
	kfree(handle);
out:
	return ret;
}

int rtk_suspend_valid(suspend_state_t state)
{
	return state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
}

static int notrace rtk_iso_suspend(unsigned long param)
{
	enum _suspend_mode mode = (enum _suspend_mode)param;
	int max_count = 100;
	int i = 0;

	pr_info("[%s] Flush Cache ...\n", DEV_NAME);

	flush_cache_all();

#ifdef CONFIG_SMP
	dsb(ishst);
	sev();
#endif

	pr_info("[%s] Ready to Suspend ! (mode:%d)\n", DEV_NAME, mode);

#if defined(CONFIG_ARCH_MULTI_V7)
	if (mode == SUSPEND_TO_COOLBOOT) {
		notify_acpu(NOTIFY_SUSPEND_TO_COOLBOOT);
		pr_info("BL31 enter DDR self refresh\n");
		asm volatile(".arch_extension sec" : : : "cc");
		asm volatile("ldr r0, =0x8400ff05" : : : "cc");
		asm volatile("isb" : : : "cc");
		asm volatile("smc #0" : : : "cc");
		asm volatile("isb" : : : "cc");
	} else if (mode == SUSPEND_TO_RAM) {
		notify_acpu(NOTIFY_SUSPEND_TO_RAM);
		pr_info("BL31 enter DDR self refresh\n");
		asm volatile(".arch_extension sec" : : : "cc");
		asm volatile("ldr r0, =0x8400ff05" : : : "cc");
		asm volatile("isb" : : : "cc");
		asm volatile("smc #0" : : : "cc");
		asm volatile("isb" : : : "cc");
	} else {
		pr_err("[%s] Suspend Mode Not Support : %d\n", DEV_NAME, mode);
		BUG();
	}
#else
	if (mode == SUSPEND_TO_COOLBOOT) {
		notify_acpu(NOTIFY_SUSPEND_TO_COOLBOOT);
		pr_info("BL31 enter DDR self refresh\n");
		asm volatile("ldr x0, =0x8400ff05" : : : "cc");
		asm volatile("isb" : : : "cc");
		asm volatile("smc #0" : : : "cc");
		asm volatile("isb" : : : "cc");
	} else if (mode == SUSPEND_TO_RAM) {
		notify_acpu(NOTIFY_SUSPEND_TO_RAM);
		pr_info("BL31 enter DDR self refresh\n");
		asm volatile("ldr x0, =0x8400ff05" : : : "cc");
		asm volatile("isb" : : : "cc");
		asm volatile("smc #0" : : : "cc");
		asm volatile("isb" : : : "cc");
	} else {
		pr_err("[%s] Suspend Mode Not Support : %d\n", DEV_NAME, mode);
		BUG();
	}
#endif /* CONFIG_ARCH_MULTI_V7 */
	for (i = max_count; i > 0 ; i--)
		__delay(10000000);

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
	int j;
	int irq;
	unsigned int mask;
	unsigned int temp;
	static unsigned int data[32];
	void __iomem *irq_state = RTK_GIC_DIST_BASE + 0x200;

	switch (state) {
	case IRQ_REPORT_PREPARE:
		for (i = 0 ; i < 32 ; i++)
			data[i] = *(unsigned int *)
				(irq_state + (i * 4));
		break;
	case IRQ_REPORT_PRINT:
		for (i = 0 ; i < 32 ; i++) {
			irq = i * 32;
			temp = *(unsigned int *)(irq_state + (i * 4));
			if (temp != data[i]) {
				pr_warn("[%s] Interrupt Addr:0x%08lx State: 0x%08x",
					DEV_NAME,
					(unsigned long)(irq_state + (i * 4)),
					data[i]);
				pr_warn(" => 0x%08x\n", temp);

				for (j = 0 ; j < 32 ; j++) {
					mask = 0x1U << j;
					if (mask & temp)
						pr_warn("[%s] IRQ: %d\n",
							DEV_NAME, (irq + j));
				}
			}
		}
		break;
	default:
		pr_err("[%s] Unknow CMD! %d\n", DEV_NAME, state);
	}
}

static int rtk_suspend_to_wfi(void)
{
#if 0
	void __iomem *reg_sel = ioremap(SYS_GROUP1_CK_SEL, 0x4);
	void __iomem *reg_pll = ioremap(SYS_PLL_SCPU1, 0x4);
#endif

	notify_acpu(NOTIFY_SUSPEND_TO_WFI);

	rtk_suspend_irq_report(IRQ_REPORT_PREPARE);
#if 0
	/* switch clk_scpu to osc (27 MHz) */
	pr_info("[%s] switch scpu_clk to osc\n", DEV_NAME);
	writel(readl(reg_sel) | 0x4, reg_sel);

	/* disable pll_scpu*/
	pr_info("[%s] disable scpu_pll\n", DEV_NAME);
	writel(0x4, reg_pll);
#endif
	pr_info("[%s] wait for interrupt\n", DEV_NAME);

	asm("WFI");

#if 0
	/* enable pll_scpu, delay to wait it stable */
	pr_info("[%s] enable scpu_pll\n", DEV_NAME);
	writel(0x3, reg_pll);
	__delay(100);

	/* NOTE: ACPU also set SYS_GROUP1_CK_SEL later */
	pr_info("[%s] switch scpu_clk to scpu_pll\n", DEV_NAME);
	writel(readl(reg_sel) & ~0x4, reg_sel);

	iounmap(reg_pll);
	iounmap(reg_sel);
#endif
	rtk_suspend_irq_report(IRQ_REPORT_PRINT);

	return 0;
}

static int rtk_suspend_to_ram(void)
{
	const int  MEM_VERIFIED_CNT = 20;
	int ret = 0;
	int i = 0;
	int size_tmp1 = 0;
	int size_tmp2 = 0;
	int size_tmp3 = 0;
	struct _memory_verified_handle *mem_vhandle[MEM_VERIFIED_CNT];
	struct _memory_verified_handle **mem_wbhandle;
	void __iomem *resumeAddr = RTK_ISO_BASE + CPU0_RESUME_ADDR;
	unsigned int ISODummy1Data = readl(resumeAddr);

	pr_info("[%s] CPU Resume vaddr: 0x%08lx paddr: 0x%08lx\n",
		DEV_NAME, (unsigned long)cpu_resume,
		(unsigned long)__pa(cpu_resume));

	hexdump("CPU Resume Entry Dump:",
		(unsigned char *) cpu_resume, 0x100);

#if defined(CONFIG_ARCH_MULTI_V7)
	asm volatile(".arch_extension sec" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("mov r1, %0" : : "r" (__pa(cpu_resume)) : "cc");
	/* RTK_SET_KERNEL_REUMSE_ENTRY */
	asm volatile("ldr r0, =0x8400ff04" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
#else
	asm volatile("isb" : : : "cc");
	asm volatile("mov x1, %0" : : "r" (__pa(cpu_resume)) : "cc");
	/* RTK_SET_KERNEL_REUMSE_ENTRY */
	asm volatile("ldr x0, =0x8400ff04" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
#endif /* CONFIG_ARCH_MULTI_V7 */

	BUG_ON(!irqs_disabled());

	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		mem_vhandle[i] = memory_verified_handle_create(0x4000);

	size_tmp1 = sizeof(phys_wb_area);
	size_tmp2 = sizeof(struct _memory_verified_handle);
	size_tmp3 = sizeof(struct _memory_verified_handle *);
	mem_wbhandle = kmalloc(size_tmp1 / size_tmp2 * size_tmp3, GFP_KERNEL);
	if (mem_wbhandle) {
		for (i = 0 ; i < (size_tmp1 / size_tmp2) ; i++)
			mem_wbhandle[i] = memory_writeback_handle_create(
					&phys_wb_area[i]);
	}

	ret = cpu_suspend((unsigned long)SUSPEND_TO_RAM, rtk_iso_suspend);

	if (ret)
		return ret;

	/* Restore iso dummy data */
	writel(ISODummy1Data, resumeAddr);

	writel(readl(RTK_ISO_BASE + 0x0418) | BIT(0), RTK_ISO_BASE + 0x0418);
	writel(readl(RTK_ISO_BASE + 0x0410) & ~BIT(10), RTK_ISO_BASE + 0x0410);

	rtk_suspend_irq_report(IRQ_REPORT_PRINT);

	rtk_suspend_wakeup_acpu();

	flush_cache_all();

	pr_info("[%s] Resume Memory Verifying ... State 0\n", DEV_NAME);
	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		memory_verified_release(mem_vhandle[i]);


	pr_info("[%s] Resume Memory Verifying ... State 1\n", DEV_NAME);
	for (i = 0 ; i < MEM_VERIFIED_CNT; i++)
		mem_vhandle[i] = memory_verified_handle_create(0x4000);

	for (i = 0 ; i < MEM_VERIFIED_CNT ; i++)
		memory_verified_release(mem_vhandle[i]);

	if (mem_wbhandle) {
		for (i = 0 ; i < (size_tmp1 / size_tmp2) ; i++)
			memory_writeback_release(
				mem_wbhandle[i], &phys_wb_area[i]);
		kfree(mem_wbhandle);
	}

#ifdef CONFIG_SMP
	dsb(ishst);
	sev();
#endif

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
	int i = 0;
	unsigned int val;
	unsigned int mask;
	int tmp;

	/* IGPIO0 ~ IGPIO23 */
	val = rtk_suspend_gpio_out_en_get();
	for (i = 0 ; i < GPIO_OUTPUT_CHANGE_EN_BITS ; i++) {
		mask = 0x1U << i;

		if (!(val & mask))
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			(rtk_suspend_gpio_out_act_get() & mask) ?
			"HIGH" : "LOW");
		tmp = (rtk_suspend_gpio_out_act_get() & mask) ? 1 : 0;
		gpio_direction_output(i + SUSPEND_ISO_GPIO_BASE, tmp);
	}

	/* IGPIO24 ~ IGPIO47 */
	val = rtk_suspend_gpio_out_en2_get();
	i = GPIO_OUTPUT_CHANGE_EN_BITS;
	for (; i < GPIO_OUTPUT_CHANGE_EN_BITS + GPIO_OUTPUT_CHANGE_EN2_BITS  ; i++) {
		mask = 0x1U << (i - GPIO_OUTPUT_CHANGE_EN_BITS);

		if (!(val & mask))
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			(rtk_suspend_gpio_out_act2_get() & mask) ?
			"HIGH" : "LOW");
		tmp = (rtk_suspend_gpio_out_act2_get() & mask) ? 1 : 0;
		gpio_direction_output(i+SUSPEND_ISO_GPIO_BASE, tmp);
	}

}

void rtk_suspend_gpip_output_change_resume(void)
{
	int i = 0;
	unsigned int val;
	unsigned int mask;
	int tmp;

	/* IGPIO0 ~ IGPIO23 */
	val = rtk_suspend_gpio_out_en_get();
	for (i = 0 ; i < GPIO_OUTPUT_CHANGE_EN_BITS ; i++) {
		mask = 0x1U << i;

		if (!(val & mask))
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			(rtk_suspend_gpio_out_act_get() & mask) ?
			"LOW" : "HIGH");
		tmp = (rtk_suspend_gpio_out_act_get() & mask) ? 0 : 1;
		gpio_direction_output(i + SUSPEND_ISO_GPIO_BASE, tmp);
	}

	/* IGPIO24 ~ IGPIO47 */
	val = rtk_suspend_gpio_out_en2_get();
	i = GPIO_OUTPUT_CHANGE_EN_BITS;
	for (; i < GPIO_OUTPUT_CHANGE_EN_BITS + GPIO_OUTPUT_CHANGE_EN2_BITS; i++) {
		mask = 0x1U << (i - GPIO_OUTPUT_CHANGE_EN_BITS);

		if (!(val & mask))
			continue;

		pr_info("[%s] gpio:%d set ouput =>  %s\n",
			DEV_NAME, i + SUSPEND_ISO_GPIO_BASE,
			(rtk_suspend_gpio_out_act2_get() & mask) ?
			"LOW" : "HIGH");
		tmp = (rtk_suspend_gpio_out_act2_get() & mask) ? 0 : 1;
		gpio_direction_output(i + SUSPEND_ISO_GPIO_BASE, tmp);
	}

}

static int rtk_suspend_enter(suspend_state_t suspend_state)
{
	int ret = 0;

	pr_info("[%s] Platform Suspend Enter ...\n", DEV_NAME);

	if (!rtk_suspend_valid(suspend_state)) {
		pr_err("[%s] suspend_state:%d not support !\n",
			DEV_NAME, (int) suspend_state);
		return  -EINVAL;
	}

	switch (suspend_state) {
	case PM_SUSPEND_STANDBY:
		ret = rtk_suspend_to_wfi();

		suspend_context++;

		pr_info("[%s] Platform Resume ...\n", DEV_NAME);
		notify_acpu(NOTIFY_RESUME_PLATFORM);
		break;
	case PM_SUSPEND_MEM:
		rtk_suspend_gpip_output_change_suspend();

		ret = rtk_suspend_to_ram();

		suspend_context++;

		if (ret) {
			pr_err("[%s] ERROR ! to suspend! (%d)\n",
				DEV_NAME, ret);
			BUG();
			break;
		}

		pr_info("[%s] Platform Resume ...\n", DEV_NAME);

		notify_acpu(NOTIFY_RESUME_PLATFORM);
		rtk_suspend_gpip_output_change_resume();

		break;
	default:
		ret = -EINVAL;
		break;
	}

	return  ret;
}

static int rtk_suspend_begin(suspend_state_t suspend_state)
{
	pr_info("[%s] Suspend Begin\n", DEV_NAME);

	if (!rtk_suspend_valid(suspend_state)) {
		pr_err("[%s] suspend_state:%d not Support!\n",
			DEV_NAME, (int) suspend_state);
		return -EINVAL;
	}

	switch (suspend_state) {
	case PM_SUSPEND_STANDBY:
		cpu_idle_poll_ctrl(true);
		break;
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
	pr_info("[%s] Suspend End\n", DEV_NAME);

	notify_acpu(NOTIFY_RESUME_END);
	cpu_idle_poll_ctrl(false);
}

const struct platform_suspend_ops rtk_suspend_ops = {
	.begin = rtk_suspend_begin,
	.end = rtk_suspend_end,
	.enter = rtk_suspend_enter,
	.valid = rtk_suspend_valid,
};

static void rtk_poweroff(void)
{
	pr_info("[%s] Power off\n", DEV_NAME);

	rtk_suspend_to_coolboot();

	return;
};

static void rtk_gpio_init_wu(struct device_node *nd)
{
	const u32 *prop_en;
	const u32 *prop_act;
	int wu_gpio_en = 0;
	int wu_gpio_act = 0;
	int wu_gpio_list = 0;
	int en;
	int act;
	int wu_gpio;
	int gpio_iso_num;
	int tmp;
	unsigned int val;
	int i = 0;

	wu_gpio_list = of_gpio_named_count(nd, "wakeup-gpio-list");
	prop_en = of_get_property(nd, "wakeup-gpio-enable", &wu_gpio_en);
	prop_act = of_get_property(nd, "wakeup-gpio-activity", &wu_gpio_act);
	wu_gpio_en  /= sizeof(u32);
	wu_gpio_act /= sizeof(u32);

	pr_info("[%s] wakeup-gpio Cnt: en(%d) act(%d) list(%d)\n",
		DEV_NAME, wu_gpio_en, wu_gpio_act, wu_gpio_list);

	if (wu_gpio_en != 0 && (wu_gpio_en == wu_gpio_act)
		&& (wu_gpio_act == wu_gpio_list)) {

		for (i = 0 ; i < wu_gpio_list ; i++) {
			en  = of_read_number(prop_en, 1 + i);
			act = of_read_number(prop_act, 1 + i);
			wu_gpio = of_get_named_gpio(nd, "wakeup-gpio-list", i);
			gpio_iso_num = wu_gpio - SUSPEND_ISO_GPIO_BASE;

			if (!en) {
				pr_err("[%s] wakeup-gpio[%d] States is disable!",
					DEV_NAME, i);
				pr_err(" (en:%d act:%d gpio:%d)\n",
					en, act, wu_gpio);
				continue;
			}

			tmp = gpio_iso_num < 0 || gpio_iso_num;
			if (tmp >= SUSPEND_ISO_GPIO_SIZE) {
				pr_err("[%s] wakeup-gpio[%d] Out of iso range!",
					DEV_NAME, i);

				pr_err(" (en:%d act:%d gpio:%d)\n",
					en, act, wu_gpio);
				continue;
			}

			if (gpio_request(wu_gpio, nd->name)) {
				pr_err("[%s] wakeup-gpio[%d] Request failed!",
					DEV_NAME, i);
				pr_err(" (en:%d act:%d gpio:%d)\n",
					en, act, wu_gpio);
			} else {
				gpio_free(wu_gpio);
			}

			gpio_direction_input(wu_gpio);

			pr_info("[%s] wakeup-gpio[%d] Successful registration!",
				DEV_NAME, i);
			pr_info(" (en:%d act:%d gpio:%d)\n",
				en, act, wu_gpio);

			/* IGPIO0 ~ IGPIO23 */
			if (gpio_iso_num < GPIO_WAKEUP_EN_BITS) {
				val = rtk_suspend_gpio_wakeup_en_get();
				tmp = gpio_iso_num;
				val = en ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_en_set(val);

				val = rtk_suspend_gpio_wakeup_act_get();
				tmp = gpio_iso_num;
				val = act ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_act_set(val);
			} else if (gpio_iso_num >= GPIO_WAKEUP_EN_BITS && gpio_iso_num < GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS) {
				/* IGPIO24 ~ IGPIO47 */
				val = rtk_suspend_gpio_wakeup_en2_get();
				tmp = (gpio_iso_num - GPIO_WAKEUP_EN_BITS);
				val = en ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_en2_set(val);

				val = rtk_suspend_gpio_wakeup_act2_get();
				tmp = (gpio_iso_num - GPIO_WAKEUP_EN_BITS);
				val = act ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_act2_set(val);
			} else {
				/* IGPIO48 ~ IGPIO56 */
				val = rtk_suspend_gpio_wakeup_en3_get();
				tmp = (gpio_iso_num - GPIO_WAKEUP_EN2_BITS - GPIO_WAKEUP_EN_BITS);
				val = en ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_en3_set(val);

				val = rtk_suspend_gpio_wakeup_act3_get();
				tmp = (gpio_iso_num - GPIO_WAKEUP_EN2_BITS - GPIO_WAKEUP_EN_BITS);
				val = act ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_wakeup_act3_set(val);
			}
		}
	}
}

static void rtk_gpio_init_out(struct device_node *nd)
{
	const u32 *prop_en;
	const u32 *prop_act;
	int out_gpio_en = 0;
	int out_gpio_act = 0;
	int out_gpio_list = 0;
	int en;
	int act;
	int gpio_iso_num;
	int output_change_gpio;
	int tmp;
	unsigned int val;
	int i = 0;

	out_gpio_list = of_gpio_named_count(nd, "gpio-output-change-list");
	prop_en = of_get_property(nd, "gpio-output-change-enable",
		&out_gpio_en);
	prop_act = of_get_property(nd, "gpio-output-change-activity",
		&out_gpio_act);
	out_gpio_en /= sizeof(u32);
	out_gpio_act /= sizeof(u32);

	pr_info("[%s] gpio-output-change Cnt: en(%d) act(%d) list(%d)\n",
			DEV_NAME, out_gpio_en, out_gpio_act, out_gpio_list);

	if (out_gpio_en != 0 && (out_gpio_en == out_gpio_act)
		&& (out_gpio_act == out_gpio_list)) {

		for (i = 0 ; i < out_gpio_list ; i++) {
			en  = of_read_number(prop_en, 1 + i);
			act = of_read_number(prop_act, 1 + i);
			output_change_gpio = of_get_named_gpio(nd,
				"gpio-output-change-list", i);
			gpio_iso_num = output_change_gpio -
				SUSPEND_ISO_GPIO_BASE;

			if (!en) {
				pr_warn("[%s] gpio-output-change[%d]",
					DEV_NAME, i);
				pr_warn(" States is disable! ");
				pr_warn("(en:%d act:%d gpio:%d)\n",
					en, act, output_change_gpio);
				continue;
			}

			if (gpio_iso_num < 0 ||
				gpio_iso_num >= SUSPEND_ISO_GPIO_SIZE) {
				pr_err("[%s] gpio-output-change[%d]",
					DEV_NAME, i);
				pr_err(" Out of iso range! ");
				pr_err("(en:%d act:%d gpio:%d)\n",
					en, act, output_change_gpio);
				continue;
			}

			if (gpio_request(output_change_gpio, nd->name)) {
				pr_err("[%s] gpio-output-change[%d]",
					DEV_NAME, i);
				pr_err(" Request failed! ");
				pr_err("(en:%d act:%d gpio:%d)\n",
					en, act, output_change_gpio);
			} else {
				gpio_free(output_change_gpio);
			}

			pr_info("[%s] gpio-output-change[%d]",
				DEV_NAME, i);
			pr_info(" Successful registration! ");
			pr_info("(en:%d act:%d gpio:%d)\n",
				en, act, output_change_gpio);

			/* IGPIO0 ~ IGPIO23 */
			if (gpio_iso_num < GPIO_OUTPUT_CHANGE_EN_BITS) {
				val = rtk_suspend_gpio_out_en_get();
				tmp = gpio_iso_num;
				val = en ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_out_en_set(val);

				val = rtk_suspend_gpio_out_act_get();
				tmp = gpio_iso_num;
				val = act ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_out_act_set(val);
			} else if (gpio_iso_num >= GPIO_OUTPUT_CHANGE_EN_BITS && gpio_iso_num < GPIO_WAKEUP_EN_BITS + GPIO_OUTPUT_CHANGE_EN2_BITS) {
				/* IGPIO24 ~ IGPIO47 */
				val = rtk_suspend_gpio_out_en2_get();
				tmp = gpio_iso_num -
					GPIO_OUTPUT_CHANGE_EN_BITS;
				val = en ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_out_en2_set(val);

				val = rtk_suspend_gpio_out_act2_get();
				tmp = gpio_iso_num -
					GPIO_OUTPUT_CHANGE_EN_BITS;
				val = act ?
					val | (0x1U << tmp) :
					val & ~(0x1U << tmp);
				rtk_suspend_gpio_out_act2_set(val);
			}
		}
	}
}

static void rtk_gpio_init(struct device_node *nd)
{
	rtk_gpio_init_wu(nd);
	rtk_gpio_init_out(nd);
}

int __init rtk_suspend_init(void)
{
	struct device_node *p_suspend_nd = NULL;
	struct device_node *p_gic_nd = NULL;
	struct device_node *p_cpu_wrapper_nd = NULL;
	const u32 *prop;
	int size;
	int temp;

	acpu_set_flag(0x00000000);
	rtk_suspend_wakeup_flags_set(0);
	rtk_suspend_resume_state_set(RESUME_NONE);
	rtk_suspend_resume_data_set(0);
	rtk_suspend_gpio_wakeup_en_set(0);
	rtk_suspend_gpio_wakeup_act_set(0);
	rtk_suspend_gpio_out_en_set(0);
	rtk_suspend_gpio_out_act_set(0);
	rtk_suspend_gpio_wakeup_en2_set(0);
	rtk_suspend_gpio_wakeup_act2_set(0);
	rtk_suspend_gpio_out_en2_set(0);
	rtk_suspend_gpio_out_act2_set(0);
	rtk_suspend_gpio_wakeup_en3_set(0);
	rtk_suspend_gpio_wakeup_act3_set(0);
	rtk_suspend_timer_sec_set(0);

	pr_info("[%s] Initial Power Management Driver\n", DEV_NAME);

	p_suspend_nd =
		of_find_compatible_node(NULL, NULL, "Realtek,power-management");
	p_gic_nd =
		of_find_compatible_node(NULL, NULL, "arm,gic-400");
	p_cpu_wrapper_nd =
		of_find_compatible_node(NULL, NULL, "Realtek,rtk-scpu_wrapper");

	RTK_CPU_WRAPPER_BASE = of_iomap(p_cpu_wrapper_nd, 0);
	RTK_GIC_DIST_BASE = of_iomap(p_gic_nd, 0);
	RTK_CRT_BASE = of_iomap(p_suspend_nd, 0);
	RTK_AIO_BASE = of_iomap(p_suspend_nd, 1);
	RTK_ISO_BASE = of_iomap(p_suspend_nd, 2);
	RTK_TVE_BASE = of_iomap(p_suspend_nd, 3);
	RTK_SB2_BASE = of_iomap(p_suspend_nd, 4);
	RTK_MISC_BASE = of_iomap(p_suspend_nd, 5);

	if (p_suspend_nd && of_device_is_available(p_suspend_nd)) {

		rtk_gpio_init(p_suspend_nd);

		/* wakeup flags */
		prop = of_get_property(p_suspend_nd, "wakeup-flags", &size);
		if (prop) {
			temp = of_read_number(prop, 1);
			if (temp < 0) {
				pr_err("[%s] Set wakeup-flags error! 0x%x\n",
					DEV_NAME, temp);
				rtk_suspend_wakeup_flags_set(
					fWAKEUP_ON_IR | fWAKEUP_ON_GPIO |
					fWAKEUP_ON_ALARM | fWAKEUP_ON_CEC);
				pr_info("[%s] wakeup flags set default : 0x%x\n",
					DEV_NAME,
					rtk_suspend_wakeup_flags_get());
			} else {
				rtk_suspend_wakeup_flags_set(temp);
				pr_info("[%s] Set set wakeup-flags = 0x%x\n",
					DEV_NAME,
					rtk_suspend_wakeup_flags_get());
			}
		} else {
			rtk_suspend_wakeup_flags_set(
				fWAKEUP_ON_IR | fWAKEUP_ON_GPIO |
				fWAKEUP_ON_ALARM | fWAKEUP_ON_CEC);
			pr_info("[%s] Wakeup Flags Set Default : 0x%x\n",
				DEV_NAME, rtk_suspend_wakeup_flags_get());
		}
	}

	suspend_set_ops(&rtk_suspend_ops);

	if (of_device_is_system_power_controller(p_suspend_nd)) {
		if (!pm_power_off) {
			pr_info("[%s] as system-power-controller\n", DEV_NAME);
			pm_power_off = rtk_poweroff;
		} else {
			pr_warn("[%s] pm_power_off is already defined\n",
				DEV_NAME);
		}
	}

	return 0;
}

subsys_initcall(rtk_suspend_init);

#ifdef CONFIG_SYSFS
#define RTK_SUSPEND_ATTR(_name) \
{ \
	.attr = {.name = #_name, .mode = 0644}, \
	.show =  rtk_suspend_##_name##_show, \
	.store = rtk_suspend_##_name##_store, \
}

static enum _suspend_wakeup rtk_suspend_decode_wakeup(const char *buf,
	size_t n)
{
	const char *const *s;
	char *p;
	int len;
	int i;

	p = memchr(buf, '\n', n);
	len = p ? p - buf : n;

	for (i = 0 ; i < eWAKEUP_ON_MAX ; i++) {
		s = &rtk_suspend_wakeup_states[i];
		if (*s && len == strlen(*s) && !strncmp(buf, *s, len))
			return i;
	}

	return eWAKEUP_ON_MAX;
}

static ssize_t rtk_suspend_wakeup_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val = rtk_suspend_wakeup_flags_get();

	for (i = 0 ; i < eWAKEUP_ON_MAX ; i++) {

		if (val & (0x1U << i))
			n += sprintf(buf + n, " * ");
		else
			n += sprintf(buf + n, "   ");
		n += sprintf(buf + n, "%s\n", rtk_suspend_wakeup_states[i]);
	}
	n += sprintf(buf + n, "\n");
	return n;
}

static ssize_t rtk_suspend_wakeup_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	enum _suspend_wakeup wakeup = rtk_suspend_decode_wakeup(buf, count);

	if (wakeup < eWAKEUP_ON_MAX) {
		rtk_suspend_wakeup_flags_set(
			rtk_suspend_wakeup_flags_get() ^ (0x1U << wakeup));
		return count;
	}
	return -ENOMEM;
}

static ssize_t rtk_suspend_resume_state_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int n = 0;
	unsigned int val = rtk_suspend_resume_state_get();

	if (val >= RESUME_MAX_STATE) {
		n += sprintf(buf + n, "(not ready)\n");
		goto done;
	}

	if (val == RESUME_GPIO)
		n += sprintf(buf + n, " %s %d\n",
			rtk_suspend_resume_states[val],
			rtk_suspend_resume_data_get() + SUSPEND_ISO_GPIO_BASE);
	else
		n += sprintf(buf + n, " %s %d\n",
			rtk_suspend_resume_states[val],
			rtk_suspend_resume_data_get());

done:
	n += sprintf(buf + n, " (write reset => change state to 'none')\n");
	return n;
}

static ssize_t rtk_suspend_resume_state_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	const char *const s = "reset";
	char *p;
	int len;

	p = memchr(buf, '\n', count);

	len = p ? p - buf : count;

	if (s && len == strlen(s) && !strncmp(buf, s, len))
		rtk_suspend_resume_state_set(RESUME_NONE);

	return count;
}

static ssize_t rtk_suspend_gpio_wakeup_en_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val;
	unsigned int val2;
	unsigned int val3;

	val = rtk_suspend_gpio_wakeup_en_get();
	val2 = rtk_suspend_gpio_wakeup_en2_get();
	val3 = rtk_suspend_gpio_wakeup_en3_get();

	if ((val == -1U) && (val2 == -1U) && (val3 == -1U))
		return sprintf(buf, "(not ready)\n");

	n += sprintf(buf + n, " En | GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < GPIO_WAKEUP_EN_BITS ; i++) {
		if (val == -1U)
			n += sprintf(buf + n, "	| %d\n", i);
		else if (val & (0x1U << i))
			n += sprintf(buf + n, "  * | %d\n", i);
		else
			n += sprintf(buf + n, "	| %d\n", i);
	}

	for (i = 0 ; i < GPIO_WAKEUP_EN2_BITS ; i++) {
		if (val2 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_EN_BITS);
		else if (val2 & (0x1U << i))
			n += sprintf(buf + n, "  * | %d\n",
				i + GPIO_WAKEUP_EN_BITS);
		else
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_EN_BITS);
	}

	for (i = 0 ; i < GPIO_WAKEUP_EN3_BITS ; i++) {
		if (val3 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS);
		else if (val3 & (0x1U << i))
			n += sprintf(buf + n, "  * | %d\n",
				i + GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS);
		else
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS);
	}
	n += sprintf(buf + n, "\n");
	return n;

}

static ssize_t rtk_suspend_gpio_wakeup_en_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#endif

	if (val < GPIO_WAKEUP_EN_BITS)
		rtk_suspend_gpio_wakeup_en_set(
			rtk_suspend_gpio_wakeup_en_get() ^ (0x1U << val));
	else if ((val >= GPIO_WAKEUP_EN_BITS) && (val < GPIO_WAKEUP_EN_BITS + GPIO_WAKEUP_EN2_BITS))
		rtk_suspend_gpio_wakeup_en2_set(
			rtk_suspend_gpio_wakeup_en2_get() ^ (0x1U <<
			(val-GPIO_WAKEUP_EN_BITS)));
	else
		rtk_suspend_gpio_wakeup_en3_set(
			rtk_suspend_gpio_wakeup_en3_get() ^ (0x1U <<
			(val-GPIO_WAKEUP_EN_BITS-GPIO_WAKEUP_EN2_BITS)));
	return count;
}

static ssize_t rtk_suspend_gpio_wakeup_act_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val;
	unsigned int val2;
	unsigned int val3;

	val = rtk_suspend_gpio_wakeup_act_get();
	val2 = rtk_suspend_gpio_wakeup_act2_get();
	val3 = rtk_suspend_gpio_wakeup_act3_get();

	if ((val == -1U) && (val2 == -1U) && (val3 == -1U))
		return sprintf(buf, "(not ready)\n");

	n += sprintf(buf + n, " Act| GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < GPIO_WAKEUP_ACT_BITS ; i++) {
		if (val == -1U)
			n += sprintf(buf + n, "	| %d\n", i);
		else if (!(rtk_suspend_gpio_wakeup_en_get() & (0x1U << i)))
			n += sprintf(buf + n, "	| %d\n", i);
		else if (val & (0x1U << i))
			n += sprintf(buf + n, "  H | %d\n", i);
		else
			n += sprintf(buf + n, "  L | %d\n", i);
	}

	for (i = 0 ; i < GPIO_WAKEUP_ACT2_BITS ; i++) {
		if (val2 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_ACT_BITS);
		else if (!(rtk_suspend_gpio_wakeup_en2_get() & (0x1U << i)))
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_ACT_BITS);
		else if (val2 & (0x1U << i))
			n += sprintf(buf + n, "  H | %d\n",
				i + GPIO_WAKEUP_ACT_BITS);
		else
			n += sprintf(buf + n, "  L | %d\n",
				i + GPIO_WAKEUP_ACT_BITS);
	}

	for (i = 0 ; i < GPIO_WAKEUP_ACT3_BITS ; i++) {
		if (val3 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_ACT_BITS + GPIO_WAKEUP_ACT2_BITS);
		else if (!(rtk_suspend_gpio_wakeup_en3_get() & (0x1U << i)))
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_WAKEUP_ACT_BITS + GPIO_WAKEUP_ACT2_BITS);
		else if (val3 & (0x1U << i))
			n += sprintf(buf + n, "  H | %d\n",
				i + GPIO_WAKEUP_ACT_BITS + GPIO_WAKEUP_ACT2_BITS);
		else
			n += sprintf(buf + n, "  L | %d\n",
				i + GPIO_WAKEUP_ACT_BITS + GPIO_WAKEUP_ACT2_BITS);
	}
	n += sprintf(buf + n, "\n");

	return n;
}

static ssize_t rtk_suspend_gpio_wakeup_act_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);
	int tmp;

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#endif

	if (val < GPIO_WAKEUP_ACT_BITS) {
		tmp = (0x1U << val);
		if (rtk_suspend_gpio_wakeup_en_get() & tmp)
			rtk_suspend_gpio_wakeup_act_set(
				rtk_suspend_gpio_wakeup_act_get() ^ tmp);
	} else {
		tmp = (0x1U << (val - GPIO_WAKEUP_ACT_BITS));
		if (rtk_suspend_gpio_wakeup_en2_get() & tmp) {
			rtk_suspend_gpio_wakeup_act2_set(
				rtk_suspend_gpio_wakeup_act2_get() ^
				(0x1U << (val-GPIO_WAKEUP_ACT_BITS)));
		}
	}

	return count;
}

static ssize_t rtk_suspend_gpio_out_en_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val;
	unsigned int val2;

	val = rtk_suspend_gpio_out_en_get();
	val2 = rtk_suspend_gpio_out_en2_get();
	if ((val == -1U) && (val2 == -1U) && (val2 == -1U))
		return sprintf(buf, "(not ready)\n");

	n += sprintf(buf + n, " En | GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < GPIO_OUTPUT_CHANGE_EN_BITS ; i++) {
		if (val == -1U)
			n += sprintf(buf + n, "	| %d\n", i);
		else if (val & (0x1U << i))
			n += sprintf(buf + n, "  * | %d\n", i);
		else
			n += sprintf(buf + n, "	| %d\n", i);
	}

	for (i = 0 ; i < GPIO_OUTPUT_CHANGE_EN2_BITS ; i++) {
		if (val2 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_OUTPUT_CHANGE_EN_BITS);
		else if (val2 & (0x1U << i))
			n += sprintf(buf + n, "  * | %d\n",
				i + GPIO_OUTPUT_CHANGE_EN_BITS);
		else
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_OUTPUT_CHANGE_EN_BITS);
	}
	n += sprintf(buf + n, "\n");
	return n;

}

static ssize_t rtk_suspend_gpio_out_en_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#endif

	if (val < GPIO_OUTPUT_CHANGE_EN_BITS)
		rtk_suspend_gpio_out_en_set(
			rtk_suspend_gpio_out_en_get() ^ (0x1U << val));
	else
		rtk_suspend_gpio_out_en2_set(rtk_suspend_gpio_out_en2_get() ^
			(0x1U << (val-GPIO_OUTPUT_CHANGE_EN_BITS)));

	return count;
}

static ssize_t rtk_suspend_gpio_out_act_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	int i;
	int n = 0;
	unsigned int val;
	unsigned int val2;

	val = rtk_suspend_gpio_out_act_get();
	val2 = rtk_suspend_gpio_out_act2_get();

	if ((val == -1U) && (val2 == -1U))
		return sprintf(buf, "(not ready)\n");

	n += sprintf(buf + n, " Act| GPIO(ISO)\n");
	n += sprintf(buf + n, " ---+----------\n");
	for (i = 0 ; i < GPIO_OUTPUT_CHANGE_ACT_BITS ; i++) {
		if (val == -1U)
			n += sprintf(buf + n, "	| %d\n", i);
		else if (!(rtk_suspend_gpio_out_en_get() & (0x1U << i)))
			n += sprintf(buf + n, "	| %d\n", i);
		else if (val & (0x1U << i))
			n += sprintf(buf + n, "  H | %d\n", i);
		else
			n += sprintf(buf + n, "  L | %d\n", i);
	}

	for (i = 0 ; i < GPIO_WAKEUP_ACT2_BITS ; i++) {
		if (val2 == -1U)
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_OUTPUT_CHANGE_ACT_BITS);
		else if (!(rtk_suspend_gpio_out_en2_get() &  (0x1U << i)))
			n += sprintf(buf + n, "	| %d\n",
				i + GPIO_OUTPUT_CHANGE_ACT_BITS);
		else if (val2 & (0x1U << i))
			n += sprintf(buf + n, "  H | %d\n",
				i + GPIO_OUTPUT_CHANGE_ACT_BITS);
		else
			n += sprintf(buf + n, "  L | %d\n",
				i + GPIO_OUTPUT_CHANGE_ACT_BITS);
	}
	n += sprintf(buf + n, "\n");

	return n;
}

static ssize_t rtk_suspend_gpio_out_act_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);
	int tmp;

	if (ret < 0)
		return -ENOMEM;

	if (val >= SUSPEND_ISO_GPIO_SIZE)
		return -ENOMEM;

#if 1
	return count;
#endif

	if (val < GPIO_OUTPUT_CHANGE_ACT_BITS) {
		if (rtk_suspend_gpio_out_en_get() &  (0x1U << val)) {
			tmp = (0x1U << val);
			rtk_suspend_gpio_out_act_set(
				rtk_suspend_gpio_out_act_get() ^ tmp);
		}
	} else {
		if (rtk_suspend_gpio_out_en2_get() &
			(0x1U << (val-GPIO_OUTPUT_CHANGE_ACT_BITS))) {
			tmp = (0x1U << (val-GPIO_OUTPUT_CHANGE_ACT_BITS));
			rtk_suspend_gpio_out_act2_set(
				rtk_suspend_gpio_out_act2_get() ^ tmp);
		}
	}

	return count;
}

static ssize_t rtk_suspend_timer_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, " %d sec (reciprocal timer)\n",
		rtk_suspend_timer_sec_get());
}

static ssize_t rtk_suspend_timer_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
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

static ssize_t rtk_suspend_context_show(struct kobject *kobj,
	struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", suspend_context);
}

static ssize_t rtk_suspend_context_store(struct kobject *kobj,
	struct kobj_attribute *attr, const char *buf, size_t count)
{
	long val;
	int ret = kstrtol(buf, 10, &val);

	if (ret < 0)
		return -ENOMEM;

	suspend_context = val;
	return count;
}

#ifdef CONFIG_RTK_XEN_SUPPORT
void rtk_domu_suspend_context_increase(void)
{
	suspend_context++;
}
#endif

static struct kobj_attribute rtk_suspend_wakeup_attr =
	RTK_SUSPEND_ATTR(wakeup);
static struct kobj_attribute rtk_suspend_resume_state_attr =
	RTK_SUSPEND_ATTR(resume_state);
static struct kobj_attribute rtk_suspend_gpio_wakeup_en_attr =
	RTK_SUSPEND_ATTR(gpio_wakeup_en);
static struct kobj_attribute rtk_suspend_gpio_wakeup_act_attr =
	RTK_SUSPEND_ATTR(gpio_wakeup_act);
static struct kobj_attribute rtk_suspend_gpio_out_en_attr =
	RTK_SUSPEND_ATTR(gpio_out_en);
static struct kobj_attribute rtk_suspend_gpio_out_act_attr =
	RTK_SUSPEND_ATTR(gpio_out_act);
static struct kobj_attribute rtk_suspend_timer_attr =
	RTK_SUSPEND_ATTR(timer);
static struct kobj_attribute rtk_suspend_context_attr =
	RTK_SUSPEND_ATTR(context);

static struct attribute *rtk_suspend_attrs[] = {
	&rtk_suspend_wakeup_attr.attr,
	&rtk_suspend_resume_state_attr.attr,
	&rtk_suspend_gpio_wakeup_en_attr.attr,
	&rtk_suspend_gpio_wakeup_act_attr.attr,
	&rtk_suspend_gpio_out_en_attr.attr,
	&rtk_suspend_gpio_out_act_attr.attr,
	&rtk_suspend_timer_attr.attr,
	&rtk_suspend_context_attr.attr,
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

module_init(suspend_sysfs_init);
#endif

