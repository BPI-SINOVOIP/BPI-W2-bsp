#include <linux/clockchips.h>
#include <linux/clocksource.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/io.h>

#define TIMER0 0
#define TIMER1 1
#define TIMER2 2
#define TIMER_MAX (TIMER2 + 1)

#define SYSTEM_TIMER TIMER0

#define COUNTER 0
#define TIMER 1

#define TR_EN (1 << 31)
#define TR_MODE (1 << 30)
#define TR_PAUSE (1 << 29)
#define TR_INT_EN (1 << 31)

#define MISC_OFFSET 0x0001B000
#define UMSK_ISR_OFFSET 0x00000008
#define ISR_OFFSET 0x0000000C
#define UMSK_ISR_SWC 0x00000010
#define ISR_SWC 0x00000014
#define SETTING_SWC 0x00000018
#define FAST_INT_EN_0 0x0000001C
#define FAST_INT_EN_1 0x00000020
#define FAST_ISR 0x00000024
#define MISC_DBG 0x0000002C
#define MISC_DUMMY 0x00000030

#define TCTVR_OFFSET 0x00000500
#define TCCVR_OFFSET 0x0000050C
#define TCCR_OFFSET 0x00000518
#define TCICR_OFFSET 0x00000524

#define RTK_TIMER_HZ CONFIG_HZ

/* HW timer command enum description */
enum hwtimer_commands {
	HWT_START = 0x80, /* Start a timer/counter */
	HWT_STOP, /* Stop a timer/counter */
	HWT_PAUSE, /* Pause a timer/counter */
	HWT_RESUME, /* Restart a timer/counter */
	HWT_INT_ENABLE, /* Enable timer/counter interrupt */
	HWT_INT_DISABLE, /* Disable timer/counter interrupt */
	HWT_INT_CLEAR, /* Clear timer/counter interrupt pending bit */
};

int TC_SHIFT[2] = {
	(1 << 6),
	(1 << 7),
};

struct _suspend_data {
	unsigned int value;
	unsigned char mode;
};

struct rtk_clock_event_device {
	int index;
	struct clock_event_device *evt;
	struct irqaction *irq_action;
};

static struct _suspend_data sTimerSuspendData[TIMER_MAX];

static void __iomem *timer_base;
unsigned long clk_freq;
int oneshot_mode;

#define MISC_BASE(pa) (timer_base + pa)
#define rtk_setbits(offset, Mask) \
	__raw_writel(((__raw_readl(offset) | Mask)), offset)
#define rtk_clearbits(offset, Mask) \
	__raw_writel(((__raw_readl(offset) & ~Mask)), offset)

unsigned char rtk_timer_get_mode(unsigned char id)
{
	unsigned int reg = __raw_readl(MISC_BASE(TCCR_OFFSET + (id << 2)));

	return (reg & TR_MODE) ? TIMER : COUNTER;
}

int rtk_timer_control(unsigned char id, unsigned int cmd)
{
	switch (cmd) {
	case HWT_INT_CLEAR:
		rtk_setbits(MISC_BASE(UMSK_ISR_OFFSET), TC_SHIFT[id] | 0x1);
		break;
	case HWT_START:
		rtk_setbits(MISC_BASE(TCCR_OFFSET + (id << 2)), TR_EN);
		break;
	case HWT_STOP:
		rtk_clearbits(MISC_BASE(TCCR_OFFSET + (id << 2)), TR_EN);
		break;
	case HWT_PAUSE:
		rtk_setbits(MISC_BASE(TCCR_OFFSET + (id << 2)), TR_PAUSE);
		break;
	case HWT_RESUME:
		rtk_clearbits(MISC_BASE(TCCR_OFFSET + (id << 2)), TR_PAUSE);
		break;
	case HWT_INT_ENABLE:
		rtk_setbits(MISC_BASE(TCICR_OFFSET + (id << 2)), TR_INT_EN);
		break;
	case HWT_INT_DISABLE:
		rtk_clearbits(MISC_BASE(TCICR_OFFSET + (id << 2)), TR_INT_EN);
		break;
	default:
		return 1;
	}
	return 0;
}

int rtk_timer_get_value(unsigned char id)
{
	/* get the current timer's value */
	return __raw_readl(MISC_BASE(TCCVR_OFFSET + (id << 2)));
}

int rtk_timer_set_value(unsigned char id, unsigned int value)
{
	/* set the timer's initial value */
	__raw_writel(value, MISC_BASE(TCCVR_OFFSET + (id << 2)));
	return 0;
}

int rtk_timer_set_target(unsigned char id, unsigned int value)
{
	/* set the timer's initial value */
	__raw_writel(value, MISC_BASE(TCTVR_OFFSET + (id << 2)));
	return 0;
}

static int rtk_timer_set_mode(unsigned char id, unsigned char mode)
{
	switch (mode) {
	case COUNTER:
		rtk_clearbits((MISC_BASE(TCCR_OFFSET + (id << 2))), TR_MODE);
		break;
	case TIMER:
		rtk_setbits((MISC_BASE(TCCR_OFFSET + (id << 2))), TR_MODE);
		break;
	default:
		return 1;
	}

	return 0;
}

static irqreturn_t rtk_clock_event_isr(int irq, void *dev_id)
{
	struct rtk_clock_event_device *clkevt;
	struct clock_event_device *evt;
	int nr = 0;

	clkevt = (struct rtk_clock_event_device *) dev_id;
	evt = clkevt->evt;
	nr = clkevt->index;

	rtk_setbits(MISC_BASE(ISR_OFFSET), TC_SHIFT[nr]);

	if (oneshot_mode)
		rtk_timer_control(nr, HWT_INT_DISABLE);

	evt->event_handler(evt);

	return IRQ_HANDLED;
}

static int rtk_clkevt_set_next(int nr, unsigned long cycles,
	struct clock_event_device *evt)
{
	int ret = 0;

	rtk_timer_control(nr, HWT_STOP);

	rtk_timer_set_target(nr, cycles);

	rtk_timer_control(nr, HWT_START);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return ret;
}

static void rtk_clocksource0_suspend(struct clocksource *cs)
{
	int nr = TIMER1;

	pr_info("[RTK-TIMER0] Enter %s\n", __func__);

	for (nr = 0 ; nr < TIMER_MAX ; nr++)
		sTimerSuspendData[nr].value = rtk_timer_get_value(nr);

	pr_info("[RTK-TIMER0] Exit %s\n", __func__);
}

static void rtk_clocksource0_resume(struct clocksource *cs)
{
	int nr = TIMER1;

	pr_info("[RTK-TIMER0] Enter %s\n", __func__);

	for (nr = 0 ; nr < TIMER_MAX ; nr++)
		rtk_timer_set_value(nr, sTimerSuspendData[nr].value);

	pr_info("[RTK-TIMER0] Exit %s\n", __func__);

}

static void rtk_clocksource1_suspend(struct clocksource *cs)
{
	int nr = TIMER1;

	pr_info("[RTK-TIMER1] Enter %s\n", __func__);

	for (nr = 0 ; nr < TIMER_MAX ; nr++)
		sTimerSuspendData[nr].value = rtk_timer_get_value(nr);

	pr_info("[RTK-TIMER1] Exit %s\n", __func__);
}

static void rtk_clocksource1_resume(struct clocksource *cs)
{
	int nr = TIMER1;

	pr_info("[RTK-TIMER1] Enter %s\n", __func__);

	for (nr = 0 ; nr < TIMER_MAX ; nr++)
		rtk_timer_set_value(nr, sTimerSuspendData[nr].value);

	pr_info("[RTK-TIMER1] Exit %s\n", __func__);
}

static int rtk_timer0_set_next(unsigned long cycles,
	struct clock_event_device *evt)
{
	return rtk_clkevt_set_next(TIMER0, cycles, evt);
}

static cycle_t rtk_read_sched_clock0(struct clocksource *cs)
{
	return (cycle_t)rtk_timer_get_value(TIMER0);
}

static int rtk_tm0_set_state_periodic(struct clock_event_device *cev)
{
	int nr = 0;

	oneshot_mode = 0;
	pr_info("[RTK-TIMER%d] set mode: periodic\n", nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);
	rtk_timer_set_value(nr, sTimerSuspendData[nr].value);
	rtk_timer_set_target(nr, DIV_ROUND_UP(clk_freq, HZ));
	rtk_timer_set_mode(nr, TIMER);
	rtk_timer_control(nr, HWT_START);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return 0;
}

static int rtk_tm0_set_state_oneshot(struct clock_event_device *cev)
{
	int nr = 0;

	oneshot_mode = 1;
	/* period set, and timer enabled in 'next event' hook */
	pr_info("[RTK-TIMER%d] set mode: oneshot\n", nr);
	rtk_timer_control(nr, HWT_STOP);
	rtk_timer_set_mode(nr, COUNTER);
	rtk_timer_control(nr, HWT_START);

	return 0;
}

static int rtk_tm0_set_state_oneshot_stopped(struct clock_event_device *cev)
{
	int nr = 0;

	pr_info("[RTK-TIMER%d] set mode: stopped\n", nr);
	rtk_timer_control(nr, HWT_STOP);

	return 0;
}

static int rtk_tm0_set_state_shutdown(struct clock_event_device *cev)
{
	int nr = 0;

	pr_info("[RTK-TIMER%d] set mode: shutdown\n", nr);
	sTimerSuspendData[nr].value = rtk_timer_get_value(nr);
	sTimerSuspendData[nr].mode = rtk_timer_get_mode(nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);

	return 0;
}

static int rtk_tm0_tick_resume(struct clock_event_device *cev)
{
	int nr = 0;

	pr_info("[RTK-TIMER%d] set mode: CLOCK_EVT_MODE_RESUME\n", nr);
	rtk_timer_set_value(nr, sTimerSuspendData[nr].value);
	rtk_timer_set_target(nr, DIV_ROUND_UP(clk_freq, HZ));
	rtk_timer_set_mode(nr, sTimerSuspendData[nr].mode);
	rtk_timer_control(nr, HWT_RESUME);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return 0;
}

static struct clocksource rtk_cs0 = {
	.name = "rtk_timer0_counter",
	.rating = 400,
	.read = rtk_read_sched_clock0,
	.mask = CLOCKSOURCE_MASK(32),
	.flags = CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend = rtk_clocksource0_suspend,
	.resume = rtk_clocksource0_resume,
};

static struct clock_event_device timer0_clockevent = {
	.rating = 400,
	.shift = 32,
	.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event = rtk_timer0_set_next,
	.set_state_periodic = rtk_tm0_set_state_periodic,
	.set_state_oneshot = rtk_tm0_set_state_oneshot,
	.set_state_oneshot_stopped = rtk_tm0_set_state_oneshot_stopped,
	.set_state_shutdown = rtk_tm0_set_state_shutdown,
	.tick_resume = rtk_tm0_tick_resume,

};

static struct irqaction timer0_irq = {
	.flags = IRQF_TIMER | IRQF_IRQPOLL,
	.handler = rtk_clock_event_isr,
	.dev_id = &timer0_clockevent,
};

static int rtk_timer1_set_next(unsigned long cycles,
	struct clock_event_device *evt)
{
	return rtk_clkevt_set_next(TIMER1, cycles, evt);
}

static cycle_t rtk_read_sched_clock1(struct clocksource *cs)
{
	return (cycle_t)rtk_timer_get_value(TIMER1);
}

static int rtk_tm1_set_state_periodic(struct clock_event_device *cev)
{
	int nr = 1;

	pr_info("[RTK-TIMER%d] set mode: periodic\n", nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);
	rtk_timer_set_value(nr, sTimerSuspendData[nr].value);
	rtk_timer_set_target(nr, DIV_ROUND_UP(clk_freq, HZ));
	rtk_timer_set_mode(nr, TIMER);
	rtk_timer_control(nr, HWT_START);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return 0;
}

static int rtk_tm1_set_state_oneshot(struct clock_event_device *cev)
{
	int nr = 1;

	/* period set, and timer enabled in 'next event' hook */
	pr_info("[RTK-TIMER%d] set mode: oneshot\n", nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);
	rtk_timer_set_value(nr, sTimerSuspendData[nr].value);
	rtk_timer_set_target(nr, DIV_ROUND_UP(clk_freq, HZ));
	rtk_timer_set_mode(nr, COUNTER);
	rtk_timer_control(nr, HWT_START);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return 0;
}

static int rtk_tm1_set_state_oneshot_stopped(struct clock_event_device *cev)
{
	int nr = 1;

	pr_info("[RTK-TIMER%d] set mode: stopped\n", nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);

	return 0;
}

static int rtk_tm1_set_state_shutdown(struct clock_event_device *cev)
{
	int nr = 1;

	pr_info("[RTK-TIMER%d] set mode: shutdown\n", nr);
	sTimerSuspendData[nr].value = rtk_timer_get_value(nr);
	sTimerSuspendData[nr].mode = rtk_timer_get_mode(nr);
	rtk_timer_control(nr, HWT_INT_DISABLE);
	rtk_timer_control(nr, HWT_STOP);

	return 0;
}

static int rtk_tm1_tick_resume(struct clock_event_device *cev)
{
	int nr = 1;

	pr_info("[RTK-TIMER%d] set mode: CLOCK_EVT_MODE_RESUME\n", nr);
	rtk_timer_set_value(nr, sTimerSuspendData[nr].value);
	rtk_timer_set_target(nr, DIV_ROUND_UP(clk_freq, HZ));
	rtk_timer_set_mode(nr, sTimerSuspendData[nr].mode);
	rtk_timer_control(nr, HWT_RESUME);
	rtk_timer_control(nr, HWT_INT_ENABLE);

	return 0;
}

static struct clocksource rtk_cs1 = {
	.name = "rtk_timer1_counter",
	.rating = 400,
	.read = rtk_read_sched_clock1,
	.mask = CLOCKSOURCE_MASK(32),
	.flags = CLOCK_SOURCE_IS_CONTINUOUS,
	.suspend = rtk_clocksource1_suspend,
	.resume = rtk_clocksource1_resume,
};

static struct clock_event_device timer1_clockevent = {
	.rating = 400,
	.shift = 32,
	.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_next_event = rtk_timer1_set_next,
	.set_state_periodic = rtk_tm1_set_state_periodic,
	.set_state_oneshot = rtk_tm1_set_state_oneshot,
	.set_state_oneshot_stopped = rtk_tm1_set_state_oneshot_stopped,
	.set_state_shutdown = rtk_tm1_set_state_shutdown,
	.tick_resume = rtk_tm1_tick_resume,
};

static struct irqaction timer1_irq = {
	.flags = IRQF_TIMER,
	.handler = rtk_clock_event_isr,
	.dev_id = &timer1_clockevent,
};

static struct rtk_clock_event_device rtk_evt[] = {
	{ 0, &timer0_clockevent, &timer0_irq },
	{ 1, &timer1_clockevent, &timer1_irq },
};

void rtk_clockevent_init(int index, const char *name, void __iomem *base,
	int irq, unsigned long freq)
{
	struct rtk_clock_event_device *clkevt = &rtk_evt[index];
	struct clock_event_device *evt = clkevt->evt;

	timer_base = base;
	clk_freq = freq;
	evt->irq = irq;
	evt->name = name;
	evt->cpumask = cpumask_of(smp_processor_id());

	memset(sTimerSuspendData, 0, sizeof(sTimerSuspendData[0]) * TIMER_MAX);

	clkevt->irq_action->name = name;
	clkevt->irq_action->irq = irq;
	clkevt->irq_action->dev_id = clkevt;

	setup_irq(irq, clkevt->irq_action);

	clockevents_config_and_register(evt, clk_freq, 0xF, UINT_MAX);
}

void rtk_clocksource_init(int index)
{
	struct clocksource *cs = &rtk_cs0;
	struct clocksource *cs1 = &rtk_cs1;

	pr_info("[RTK-TIMER%d] clocksource %d register HZ\n", index, index);

	if (index == 0) {
		if (clocksource_register_hz(cs, clk_freq))
			pr_err("[RTK-TIMER%d] timer%d can't register clocksource\n",
				index, index);
	} else {
		if (clocksource_register_hz(cs1, clk_freq))
			pr_err("[RTK-TIMER%d] timer%d can't register clocksource\n",
				index, index);
	}
}

static int __init rtk_timer0_init(struct device_node *np)
{
	int ret = 0;
	void __iomem *iobase;
	int irq = 0;
	int rate = 0;

	iobase = of_iomap(np, 0);
	if (!iobase) {
		pr_err("[RTK-TIMER0] failed to get base address\n");
		return 1;
	}

	irq = irq_of_parse_and_map(np, 0);
	if (irq <= 0) {
		pr_err("[RTK-TIMER0] can't parse IRQ\n");
		return 1;
	}

	ret = of_property_read_u32(np, "clock-frequency", &rate);
	if (ret) {
		pr_err("[RTK-TIMER0] can't get clock-frequency\n");
		return 1;
	}

	rtk_clockevent_init(TIMER0, np->name, iobase, irq, rate);
	rtk_clocksource_init(TIMER0);

	return ret;
}

static int __init rtk_timer1_init(struct device_node *np)
{
	int ret = 0;
	void __iomem *iobase;
	int irq = 0;
	int rate = 0;

	iobase = of_iomap(np, 0);
	if (!iobase) {
		pr_err("[RTK-TIMER1] failed to get base address\n");
		return 1;
	}

	irq = irq_of_parse_and_map(np, 0);
	if (irq <= 0) {
		pr_err("[RTK-TIMER1] can't parse IRQ\n");
		return 1;
	}

	ret = of_property_read_u32(np, "clock-frequency", &rate);
	if (ret) {
		pr_err("[RTK-TIMER1] can't get clock-frequency\n");
		return 1;
	}

	rtk_clockevent_init(TIMER1, np->name, iobase, irq, rate);
	rtk_clocksource_init(TIMER1);

	return ret;
}

CLOCKSOURCE_OF_DECLARE(realtek_timer0, "realtek,rtk-timer0", rtk_timer0_init);
CLOCKSOURCE_OF_DECLARE(realtek_timer1, "realtek,rtk-timer1", rtk_timer1_init);
