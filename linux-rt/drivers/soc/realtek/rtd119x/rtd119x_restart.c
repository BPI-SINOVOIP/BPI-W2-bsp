#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/delay.h>

#include <asm/io.h>
#include <asm/system_misc.h>

static void __iomem * wdt_base;
static int wdt_oe;
static void __iomem * rst_ctrl_base;
unsigned int rst_ctrl_reg_offset = 0;

#define WDT_CLR		4
#define WDT_CTL		0
#define WDT_OVERFLOW	0xC
#define WDT_NMI         8
#define WDT_RSTB_CNT	0x40
#define WDT_OE		0x44

#define RESET_MAGIC	0xAABBCC00

typedef enum{
	RESET_ACTION_NO_ACTION = 0,
	RESET_ACTION_FASTBOOT,
	RESET_ACTION_ABNORMAL = 0xff,
}RESET_ACTION;

static void setup_restart_action(RESET_ACTION action)
{
	unsigned int reset_action = RESET_MAGIC;

	if (!rst_ctrl_base) {
		pr_err("%s, Skip set reset action\n", __func__);
		return;
	}

	switch (action) {
		case RESET_ACTION_FASTBOOT:
			reset_action |= RESET_ACTION_FASTBOOT;
			break;
		default:
			break;
	}

	writel(reset_action, rst_ctrl_base + rst_ctrl_reg_offset);
}

void rtk_machine_restart(char mode, const char *cmd)
{
	if (cmd) {
		if (!strncmp("bootloader", cmd, 11)) {
			setup_restart_action(RESET_ACTION_FASTBOOT);
		} else {
			setup_restart_action(RESET_ACTION_NO_ACTION);
		}
	} else {
		setup_restart_action(RESET_ACTION_NO_ACTION);
	}

	if (wdt_oe >= 0)
		writel(wdt_oe, wdt_base + WDT_OE);

	writel(0x00800000, wdt_base + WDT_RSTB_CNT);
	writel(BIT(0), wdt_base + WDT_CLR);
	writel(0x00800000, wdt_base + WDT_OVERFLOW);
	writel(0x000000FF, wdt_base + WDT_CTL);
	while (1)
		mdelay(100);
}

static struct of_device_id rtk_restart_ids[] = {
	{.compatible = "Realtek,rtk-watchdog", .data = rtk_machine_restart},
	{}
};

static struct of_device_id rtk_reset_control_ids[] = {
	{.compatible = "Realtek,rtk-rstctrl"},
	{}
};

static int rtk_setup_restart(void)
{
	const struct of_device_id *of_id;
	struct device_node *np;

	/* setup Watchdog */
	np = of_find_matching_node(NULL, rtk_restart_ids);
	if (WARN(!np, "Unable to setup watchdog restart"))
		return 1;

	wdt_base = of_iomap(np, 0);
	WARN(!wdt_base, "failed to map IO base for watchdog");

	if (of_property_read_u32_index(np, "rst-oe", 0, &wdt_oe))
		wdt_oe = -1;

	of_id = of_match_node(rtk_restart_ids, np);
	WARN(!of_id, "restart not available");

	arm_pm_restart = of_id->data;

#ifdef CONFIG_ARCH_RTD129X
	/* setup Reset Control */
	np = of_find_matching_node(NULL, rtk_reset_control_ids);
	if (WARN(!np, "Unable to setup reset-control"))
		return 1;

	rst_ctrl_base = of_iomap(np, 0);
	WARN(!rst_ctrl_base, "failed to map IO base for reset-control");

	if (of_property_read_u32_index(np, "rst-reg-offset", 0, &rst_ctrl_reg_offset)) {
		pr_err("reset-control rst-reg-offset not defined");
		rst_ctrl_base = NULL;
		return 1;
	}

	printk("rst-control : base %p, offset 0x%x\n", rst_ctrl_base, rst_ctrl_reg_offset);
	setup_restart_action(RESET_ACTION_ABNORMAL);

#endif
	return 0;
}

arch_initcall(rtk_setup_restart);
