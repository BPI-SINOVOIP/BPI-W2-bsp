/*
 * Realtek pulse-width-modulation controller driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/pwm.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/sysfs.h>

// RTK define here
#define RTK_DEF_PWM_IDX     (0)     // default use PWM idx set to 0

#define RTK_ADDR_PWM_OCD    (0x0)
#define RTK_ADDR_PWM_CD     (0x4)
#define RTK_ADDR_PWM_CSD    (0x8)

#define RTK_PWM_OCD_SHIFT       (8)
#define RTK_PWM_CD_SHIFT        (8)
#define RTK_PWM_CSD_SHIFT       (4)

#define RTK_PWM_OCD_MASK       (0xff)
#define RTK_PWM_CD_MASK        (0xff)
#define RTK_PWM_CSD_MASK       (0xf)

#define RTK_PWM_OCD_DEFAULT      	(0xff)
#define RTK_PWM_CD_DEFAULT       	(0x1)
#define RTK_PWM_CSD_DEFAULT     	(0x1)

#define NUM_PWM 4
#define DEV_NAME "[RTK_PWM]"

#ifdef CONFIG_RTK_PWM_DEBUG
#define PWM_DEBUG(args...) pr_info(args);
#else
#define PWM_DEBUG(args...)
#endif /* RTK_PWM_DEBUG */

struct RTK119X_pwm_map {
	int duty_rate;
	int ocd_data;
	int cd_data;
};

struct rtd1295_pwm_chip {
	struct pwm_chip		chip;
	struct device		*dev;
	void __iomem		*mmio_pwm_reg_base;
	spinlock_t	lock;
	int			proc_id;
	int			base_freq;
	int			out_freq[NUM_PWM]; //Hz
	int			duty_rate[NUM_PWM];
	int			enable[NUM_PWM];
	int			clksrc_div[NUM_PWM];
	int			clkout_div[NUM_PWM];
	int			clk_duty[NUM_PWM];
};

ssize_t pwm_show_dutyRate0(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_dutyRate0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_enable0(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_enable0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clksrcDiv0(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clksrcDiv0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clkoutDiv0(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clkoutDiv0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_out_freq0(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_out_freq0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_dutyRate1(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_dutyRate1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_enable1(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_enable1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clksrcDiv1(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clksrcDiv1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clkoutDiv1(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clkoutDiv1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_out_freq1(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_out_freq1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_dutyRate2(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_dutyRate2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_enable2(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_enable2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clksrcDiv2(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clksrcDiv2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clkoutDiv2(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clkoutDiv2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_out_freq2(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_out_freq2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_dutyRate3(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_dutyRate3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_enable3(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_enable3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clksrcDiv3(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clksrcDiv3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_clkoutDiv3(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_clkoutDiv3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

ssize_t pwm_show_out_freq3(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t pwm_store_out_freq3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count);

static DEVICE_ATTR(dutyRate0, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_dutyRate0, pwm_store_dutyRate0);
static DEVICE_ATTR(enable0, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_enable0, pwm_store_enable0);
static DEVICE_ATTR(clksrcDiv0, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clksrcDiv0, pwm_store_clksrcDiv0);
static DEVICE_ATTR(clkoutDiv0, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clkoutDiv0, pwm_store_clkoutDiv0);
static DEVICE_ATTR(out_freq0, S_IRUGO, pwm_show_out_freq0, pwm_store_out_freq0);

static DEVICE_ATTR(dutyRate1, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_dutyRate1, pwm_store_dutyRate1);
static DEVICE_ATTR(enable1, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_enable1, pwm_store_enable1);
static DEVICE_ATTR(clksrcDiv1, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clksrcDiv1, pwm_store_clksrcDiv1);
static DEVICE_ATTR(clkoutDiv1, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clkoutDiv1, pwm_store_clkoutDiv1);
static DEVICE_ATTR(out_freq1, S_IRUGO, pwm_show_out_freq1, pwm_store_out_freq1);

static DEVICE_ATTR(dutyRate2, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_dutyRate2, pwm_store_dutyRate2);
static DEVICE_ATTR(enable2, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_enable2, pwm_store_enable2);
static DEVICE_ATTR(clksrcDiv2, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clksrcDiv2, pwm_store_clksrcDiv2);
static DEVICE_ATTR(clkoutDiv2, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clkoutDiv2, pwm_store_clkoutDiv2);
static DEVICE_ATTR(out_freq2, S_IRUGO, pwm_show_out_freq2, pwm_store_out_freq2);

static DEVICE_ATTR(dutyRate3, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_dutyRate3, pwm_store_dutyRate3);
static DEVICE_ATTR(enable3, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_enable3, pwm_store_enable3);
static DEVICE_ATTR(clksrcDiv3, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clksrcDiv3, pwm_store_clksrcDiv3);
static DEVICE_ATTR(clkoutDiv3, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), pwm_show_clkoutDiv3, pwm_store_clkoutDiv3);
static DEVICE_ATTR(out_freq3, S_IRUGO, pwm_show_out_freq3, pwm_store_out_freq3);

static struct attribute *pwm_dev_attrs[] = {
	&dev_attr_dutyRate0.attr,
	&dev_attr_enable0.attr,
	&dev_attr_clksrcDiv0.attr,
	&dev_attr_clkoutDiv0.attr,
	&dev_attr_out_freq0.attr,
	&dev_attr_dutyRate1.attr,
	&dev_attr_enable1.attr,
	&dev_attr_clksrcDiv1.attr,
	&dev_attr_clkoutDiv1.attr,
	&dev_attr_out_freq1.attr,
	&dev_attr_dutyRate2.attr,
	&dev_attr_enable2.attr,
	&dev_attr_clksrcDiv2.attr,
	&dev_attr_clkoutDiv2.attr,
	&dev_attr_out_freq2.attr,
	&dev_attr_dutyRate3.attr,
	&dev_attr_enable3.attr,
	&dev_attr_clksrcDiv3.attr,
	&dev_attr_clkoutDiv3.attr,
	&dev_attr_out_freq3.attr,
	NULL,
};

static struct attribute_group pwm_dev_attr_group = {
	.attrs		= pwm_dev_attrs,
};

static inline struct rtd1295_pwm_chip *to_rtd1295_pwm_chip(struct pwm_chip *chip)
{
	return container_of(chip, struct rtd1295_pwm_chip, chip);
}

#define to_pwm_device(d) return container_of(d, struct rtd1295_pwm_chip, chip);

int set_real_freq_by_target_freq(struct rtd1295_pwm_chip *pc, int hwpwm, int target_freq) {
	int base_freq = pc->base_freq;
	int real_freq;
	int ocd, csd, div, opt_div;
	div = base_freq / target_freq;

	{
		// give a div to get max ocd and min csd
		int min_ocd = 0;
		int max_ocd = 255;
		int min_csd = 0;
		int max_csd = 15;
		int i;
		// find max bit
		for (i = 0; i < 32; i++) {
			if ((div << i) & BIT(31)) {
				break;
			}
		}
		csd = (32 - (i + 8)) - 1;
		if (csd > max_csd) csd = max_csd;
		else if (csd < min_csd) csd = min_csd;

		ocd = (div >> (csd + 1)) - 1;
		if (ocd > max_ocd) ocd = max_ocd;
		else if (ocd < min_ocd) ocd = min_ocd;

		opt_div = BIT(csd + 1)*(ocd + 1);
		PWM_DEBUG("%s target_div=%d, real_div=%d, osd=%d, ocd=%d\n", DEV_NAME, div, opt_div, csd, ocd);
	}

	real_freq = base_freq / opt_div;
	pc->clkout_div[hwpwm] = ocd;
	pc->clksrc_div[hwpwm] = csd;

	pc->out_freq[hwpwm] = real_freq;

	PWM_DEBUG("%s hwpwm=%d, target_freq=%d, real_freq=%d, osd=%d, ocd=%d\n",
		DEV_NAME, hwpwm, target_freq, pc->out_freq[hwpwm], pc->clksrc_div[hwpwm], pc->clkout_div[hwpwm]);

	return real_freq;
}

int set_real_period_by_target_period(struct rtd1295_pwm_chip *pc, int hwpwm, int target_period_ns) {
	int base_ns = 1000000000;
	int real_period_ns;
	int target_freq, real_freq;

	target_freq = base_ns / target_period_ns;
	real_freq = set_real_freq_by_target_freq(pc, hwpwm, target_freq);
	real_period_ns = base_ns / real_freq;

	PWM_DEBUG("%s hwpwm=%d, target_period_ns=%d (freq=%d), real_period_ns=%d (real_freq=%d), osd=%d, ocd=%d\n",
		DEV_NAME, hwpwm, target_period_ns, target_freq, real_period_ns, real_freq,
		pc->clksrc_div[hwpwm], pc->clkout_div[hwpwm]);

	return real_period_ns;
}

int set_real_freq_by_target_div(struct rtd1295_pwm_chip *pc, int hwpwm, int clksrc_div, int clkout_div) {
	int base_freq = pc->base_freq;
	int real_freq, div;

	div = BIT(clksrc_div + 1) * (clkout_div + 1);
	real_freq = base_freq / div;

	pc->clkout_div[hwpwm] = clkout_div;
	pc->clksrc_div[hwpwm] = clksrc_div;

	pc->out_freq[hwpwm] = real_freq;

	PWM_DEBUG("%s real_freq=%d, osd=%d, ocd=%d\n",
			DEV_NAME, pc->out_freq[hwpwm], pc->clksrc_div[hwpwm], pc->clkout_div[hwpwm]);

	return real_freq;
}

int set_clk_duty(struct rtd1295_pwm_chip *pc, int hwpwm, int duty_rate) {
	int clkout_div = pc->clkout_div[hwpwm];
	if (duty_rate < 0) duty_rate = 0;
	if (duty_rate > 100) duty_rate = 100;

	pc->duty_rate[hwpwm] = duty_rate;
	pc->clk_duty[hwpwm] = (duty_rate * (clkout_div + 1) / 100) - 1;

	if (pc->clk_duty[hwpwm] < 0) pc->clk_duty[hwpwm] = 0;
	if (pc->clk_duty[hwpwm] > clkout_div) pc->clk_duty[hwpwm] = clkout_div;

	return 0;
}

static void pwm_set_register(struct rtd1295_pwm_chip *pc, int hwpwm)
{
	u32 value;
	int clkout_div = 0;
	int clk_duty = 0;
	int clksrc_div = 0;
	if(pc==NULL) {
		pr_err("%s %s -- parameter error!-- \n", DEV_NAME, __func__);
		return;
	}

	if (pc->enable[hwpwm]) {
		clkout_div = pc->clkout_div[hwpwm];
		clk_duty = pc->clk_duty[hwpwm];
		clksrc_div = pc->clksrc_div[hwpwm];
	}

	PWM_DEBUG("%s %s -- set index %d OCD=%d,CD=%d,CSD=%d\n",
		DEV_NAME, __func__, hwpwm, clkout_div, clk_duty, clksrc_div);

	spin_lock(&pc->lock);
	value = readl(pc->mmio_pwm_reg_base + RTK_ADDR_PWM_OCD);
	value &= ~(RTK_PWM_OCD_MASK << (hwpwm*RTK_PWM_OCD_SHIFT));
	value |= clkout_div << (hwpwm*RTK_PWM_OCD_SHIFT);
	writel(value, pc->mmio_pwm_reg_base + RTK_ADDR_PWM_OCD);

	value = readl(pc->mmio_pwm_reg_base + RTK_ADDR_PWM_CD);
	value &= ~(RTK_PWM_CD_MASK << (hwpwm*RTK_PWM_CD_SHIFT));
	value |= clk_duty << (hwpwm*RTK_PWM_CD_SHIFT);
	writel(value, pc->mmio_pwm_reg_base + RTK_ADDR_PWM_CD);

	value = readl(pc->mmio_pwm_reg_base + RTK_ADDR_PWM_CSD);
	value &= ~(RTK_PWM_CSD_MASK << (hwpwm*RTK_PWM_CSD_SHIFT));
	value |= clksrc_div << (hwpwm*RTK_PWM_CSD_SHIFT);
	writel(value, pc->mmio_pwm_reg_base + RTK_ADDR_PWM_CSD);
	spin_unlock(&pc->lock);

	PWM_DEBUG("%s %s -- done! \n", DEV_NAME, __func__);
}

static int rtd1295_pwm_config(struct pwm_chip *chip, struct pwm_device *pwm,
			    int duty_ns, int period_ns)
{
	struct rtd1295_pwm_chip *pc = to_rtd1295_pwm_chip(chip);
	int real_period_ns, duty_rate;

	PWM_DEBUG("%s %s ---- hwpwm=%d, enable=%d duty_ns=%d period_ns=%d\n",
		DEV_NAME, __func__, pwm->hwpwm, pc->enable[pwm->hwpwm], duty_ns, period_ns);
	real_period_ns = set_real_period_by_target_period(pc, pwm->hwpwm, period_ns);
	duty_rate = duty_ns *100 / period_ns;

	set_clk_duty(pc, pwm->hwpwm, duty_rate);

	pwm_set_register(pc, pwm->hwpwm);

	return 0;
}

static int rtd1295_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct rtd1295_pwm_chip *pc = to_rtd1295_pwm_chip(chip);

	PWM_DEBUG("%s %s ---- hwpwm=%d, enable=%d \n",
		DEV_NAME, __func__, pwm->hwpwm, pc->enable[pwm->hwpwm]);
	pc->enable[pwm->hwpwm] = 1;
	pwm_set_register(pc, pwm->hwpwm);

	return 0;
}

static void rtd1295_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct rtd1295_pwm_chip *pc = to_rtd1295_pwm_chip(chip);

	PWM_DEBUG("%s %s ---- disable PWM[%d] now !\n",
		DEV_NAME, __func__, pwm->hwpwm);
	pc->enable[pwm->hwpwm] = 0;
	pwm_set_register(pc, pwm->hwpwm);
}

static const struct pwm_ops rtd1295_pwm_ops = {
	.config = rtd1295_pwm_config,
	.enable = rtd1295_pwm_enable,
	.disable = rtd1295_pwm_disable,
	.owner = THIS_MODULE,
};

/** define show/store API for each file here **/
static ssize_t pwm_show_dutyRate(struct device *dev, struct device_attribute *attr, char *buf, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s called : hwpwm=%d, dutyRate=> pc->dutyRate=[%d]--- \n",
		DEV_NAME, __func__, hwpwm, pc->duty_rate[hwpwm]);

	return sprintf(buf, "%d%%\n", pc->duty_rate[hwpwm]);
}

static ssize_t pwm_store_dutyRate(struct device *dev, struct device_attribute *attr, const char *buf, size_t count, int hwpwm)
{
	int value=0;
	int ret=-1;
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s called : hwpwm=%d, count:%ld ",
		DEV_NAME, __func__, hwpwm, count);

	if( count < 1 ) {
		pr_err("%s %s , count is too small, return \n",
			DEV_NAME, __func__);
		return count;
	}
	ret = kstrtoint(buf, 10, &value);
	if ( ret != 0 ) {
		pr_err("%s %s , parse buf error! ret=%d \n",
			DEV_NAME, __func__, ret);
		return count;
	}
	PWM_DEBUG("%s value:[%d] \n", DEV_NAME, value);
	if( value < 0 || value > 100 ) {
		pr_err("%s %s  ====  input should between 0 ~ 100 \n",
			DEV_NAME, __func__);
		return count;
	}
	if( pc->duty_rate[hwpwm] == value ) {
		pr_err(" %s %s -- dutyRate value is not change, return! \n",
			DEV_NAME, __func__);
		return count;
	}
	else {
		pr_err("%s %s -- assign [%d] to duty_rate now! \n",
			DEV_NAME, __func__, value);

		set_clk_duty(pc, hwpwm, value);
		pwm_set_register(pc, hwpwm);
	}

	return count;
}

static ssize_t pwm_show_enable(struct device *dev, struct device_attribute *attr, char *buf, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s : hwpwm=%d, enable=%d---- \n",
		DEV_NAME, __func__, hwpwm, pc->enable[hwpwm]);

	return sprintf(buf, "%d\n", pc->enable[hwpwm]);
}

static ssize_t pwm_store_enable(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);
	int value=0;

	if(buf ==NULL) {
		pr_err("%s %s	====  buffer is null, return \n",
			DEV_NAME, __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	if( pc->enable[hwpwm] == value ) {
		pr_err("%s %s	====  the same, do nothing (hwpwm=%d, value=%d) \n",
			DEV_NAME, __func__, hwpwm, value);
		return count;
	}

	pc->enable[hwpwm] = value;
	pwm_set_register(pc, hwpwm);

	PWM_DEBUG("%s %s  ====  done \n",
		DEV_NAME, __func__);
	return count;
}

static ssize_t pwm_show_clksrcDiv(struct device *dev, struct device_attribute *attr, char *buf, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s called : hwpwm=%d, clksrc_div=%d---- \n",
		DEV_NAME, __func__, hwpwm, pc->clksrc_div[hwpwm]);

	return sprintf(buf, "%d\n", pc->clksrc_div[hwpwm]);
}

static ssize_t pwm_store_clksrcDiv(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	int value=0;
	if(buf ==NULL) {
		pr_err("%s %s  ====  buffer is null, return \n",
			DEV_NAME, __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	if(value < 0 || value > 15) {
		pr_err("%s %s  ====  input should between 0 ~ 15 \n",
			DEV_NAME, __func__);
		return count;
	}

	if(pc->clksrc_div[hwpwm] == value) {
		pr_err("%s %s  ====  hwpwm=%d, input is the same=%d, do nothing! \n",
			DEV_NAME, __func__, hwpwm, value);
		return count;
	}

	set_real_freq_by_target_div(pc, hwpwm, value, pc->clkout_div[hwpwm]);

	pwm_set_register(pc, hwpwm);

	PWM_DEBUG("%s %s  ====  done (hwpwm=%d, value=%d) \n",
		DEV_NAME, __func__, hwpwm, value);
	return count;
}

static ssize_t pwm_show_clkoutDiv(struct device *dev, struct device_attribute *attr, char *buf, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s : hwpwm=%d, clkout_div=%d---- \n",
		DEV_NAME, __func__, hwpwm, pc->clkout_div[hwpwm]);

	return sprintf(buf, "%d\n", pc->clkout_div[hwpwm]);
}

static ssize_t pwm_store_clkoutDiv(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	int value=0;
	if(buf ==NULL) {
		pr_err("%s %s  ====  buffer is null, return \n",
			DEV_NAME, __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	if(value < 0 || value > 255) {
		pr_err("%s %s  ====  input should between 0 ~ 255 \n",
			DEV_NAME, __func__);
		return count;
	}

	if(pc->clkout_div[hwpwm] == value) {
		pr_err("%s %s  ====  hwpwm=%d, input is the same=%d, do nothing! \n",
			DEV_NAME, __func__, hwpwm, value);
		return count;
	}

	set_real_freq_by_target_div(pc, hwpwm, pc->clksrc_div[hwpwm], value);

	pwm_set_register(pc, hwpwm);

	PWM_DEBUG("%s %s  ====  done (hwpwm=%d, value=%d) \n",
		DEV_NAME, __func__, hwpwm, value);
	return count;
}

static ssize_t pwm_show_out_freq(struct device *dev, struct device_attribute *attr, char *buf, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	PWM_DEBUG("%s %s : hwpwm=%d, out_freq=%dHz---- \n",
		DEV_NAME, __func__, hwpwm, pc->out_freq[hwpwm]);

	return sprintf(buf, "%dHz\n", pc->out_freq[hwpwm]);
}

static ssize_t pwm_store_out_freq(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count, int hwpwm)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);

	int value=0;
	if(buf ==NULL) {
		pr_err("%s %s  ====  buffer is null, return \n", DEV_NAME, __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	if(value < 0 || value > 27000000) {
		pr_err("%s %s  ====  input should between 0 ~ 27MHz \n",
			DEV_NAME, __func__);
		return count;
	}

	if(pc->out_freq[hwpwm] == value) {
		pr_err("%s %s  ====  hwpwm=%d, input is the same=%d, do nothing! \n",
			DEV_NAME, __func__, hwpwm, value);
		return count;
	}

	set_real_freq_by_target_freq(pc, hwpwm, value);

	/* update CD since OCD is changed */
	set_clk_duty(pc, hwpwm, pc->duty_rate[hwpwm]);

	pwm_set_register(pc, hwpwm);

	PWM_DEBUG("%s %s  ====  done (hwpwm=%d, value=%d) \n",
		DEV_NAME, __func__, hwpwm, value);
	return count;
}


ssize_t pwm_show_dutyRate0(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_dutyRate(dev, attr, buf, 0);
}

ssize_t pwm_store_dutyRate0(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return pwm_store_dutyRate(dev, attr, buf, count, 0);
}

ssize_t pwm_show_enable0(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_enable(dev, attr, buf, 0);
}

ssize_t pwm_store_enable0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_enable(dev, attr, buf, count, 0);
}

ssize_t pwm_show_clksrcDiv0(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clksrcDiv(dev, attr, buf, 0);
}

ssize_t pwm_store_clksrcDiv0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clksrcDiv(dev, attr, buf, count, 0);
}

ssize_t pwm_show_clkoutDiv0(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clkoutDiv(dev, attr, buf, 0);
}

ssize_t pwm_store_clkoutDiv0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clkoutDiv(dev, attr, buf, count, 0);
}

ssize_t pwm_show_out_freq0(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_out_freq(dev, attr, buf, 0);
}

ssize_t pwm_store_out_freq0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_out_freq(dev, attr, buf, count, 0);
}

ssize_t pwm_show_dutyRate1(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_dutyRate(dev, attr, buf, 1);
}

ssize_t pwm_store_dutyRate1(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return pwm_store_dutyRate(dev, attr, buf, count, 1);
}

ssize_t pwm_show_enable1(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_enable(dev, attr, buf, 1);
}

ssize_t pwm_store_enable1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_enable(dev, attr, buf, count, 1);
}

ssize_t pwm_show_clksrcDiv1(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clksrcDiv(dev, attr, buf, 1);
}

ssize_t pwm_store_clksrcDiv1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clksrcDiv(dev, attr, buf, count, 1);
}

ssize_t pwm_show_clkoutDiv1(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clkoutDiv(dev, attr, buf, 1);
}

ssize_t pwm_store_clkoutDiv1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clkoutDiv(dev, attr, buf, count, 1);
}

ssize_t pwm_show_out_freq1(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_out_freq(dev, attr, buf, 1);
}

ssize_t pwm_store_out_freq1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_out_freq(dev, attr, buf, count, 1);
}

ssize_t pwm_show_dutyRate2(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_dutyRate(dev, attr, buf, 2);
}

ssize_t pwm_store_dutyRate2(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return pwm_store_dutyRate(dev, attr, buf, count, 2);
}

ssize_t pwm_show_enable2(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_enable(dev, attr, buf, 2);
}

ssize_t pwm_store_enable2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_enable(dev, attr, buf, count, 2);
}

ssize_t pwm_show_clksrcDiv2(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clksrcDiv(dev, attr, buf, 2);
}

ssize_t pwm_store_clksrcDiv2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clksrcDiv(dev, attr, buf, count, 2);
}

ssize_t pwm_show_clkoutDiv2(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clkoutDiv(dev, attr, buf, 2);
}

ssize_t pwm_store_clkoutDiv2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clkoutDiv(dev, attr, buf, count, 2);
}

ssize_t pwm_show_out_freq2(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_out_freq(dev, attr, buf, 2);
}

ssize_t pwm_store_out_freq2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_out_freq(dev, attr, buf, count, 2);
}

ssize_t pwm_show_dutyRate3(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_dutyRate(dev, attr, buf, 3);
}

ssize_t pwm_store_dutyRate3(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	return pwm_store_dutyRate(dev, attr, buf, count, 3);
}

ssize_t pwm_show_enable3(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_enable(dev, attr, buf, 3);
}

ssize_t pwm_store_enable3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_enable(dev, attr, buf, count, 3);
}

ssize_t pwm_show_clksrcDiv3(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clksrcDiv(dev, attr, buf, 3);
}

ssize_t pwm_store_clksrcDiv3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clksrcDiv(dev, attr, buf, count, 3);
}

ssize_t pwm_show_clkoutDiv3(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_clkoutDiv(dev, attr, buf, 3);
}

ssize_t pwm_store_clkoutDiv3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_clkoutDiv(dev, attr, buf, count, 3);
}

ssize_t pwm_show_out_freq3(struct device *dev, struct device_attribute *attr, char *buf)
{
	return pwm_show_out_freq(dev, attr, buf, 3);
}

ssize_t pwm_store_out_freq3(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	return pwm_store_out_freq(dev, attr, buf, count, 3);
}


static int rtd1295_pwm_probe(struct platform_device *pdev)
{
	struct rtd1295_pwm_chip *pwm;
	struct device_node *node = pdev->dev.of_node;
	struct device_node *pwm0, *pwm1, *pwm2, *pwm3;
	int ret=0;
	u32 val=0;
	int i;

	PWM_DEBUG("%s %s ---- \n", DEV_NAME, __func__);

	pwm = devm_kzalloc(&pdev->dev, sizeof(*pwm), GFP_KERNEL);
	if (!pwm) {
		dev_err(&pdev->dev, "failed to allocate memory\n");
		return -ENOMEM;
	}
	pwm->proc_id = pdev->id;
	pwm->dev = &pdev->dev;

	platform_set_drvdata(pdev, pwm);

	pwm->mmio_pwm_reg_base = of_iomap(node, 0);

	spin_lock_init(&pwm->lock);

	pwm->base_freq = 27000000;
	for (i=0; i<NUM_PWM; i++) {
		pwm->out_freq[i] = 0;
		pwm->enable[i] = 0;
		pwm->clkout_div[i] = RTK_PWM_OCD_MASK;
		pwm->clksrc_div[i] = RTK_PWM_CD_DEFAULT;
		pwm->clk_duty[i] = RTK_PWM_CSD_DEFAULT;
		pwm->duty_rate[i] = 0;
	}

	pwm0 = of_get_child_by_name(node, "pwm_0");
	if (!pwm0) {
		dev_err(&pdev->dev, "could not find [pwm_0] sub-node\n");
		return -EINVAL;
	}

	pwm1 = of_get_child_by_name(node, "pwm_1");
	if (!pwm1) {
		dev_err(&pdev->dev, "could not find [pwm_1] sub-node\n");
		return -EINVAL;
	}

	pwm2 = of_get_child_by_name(node, "pwm_2");
	if (!pwm2) {
		dev_err(&pdev->dev, "could not find [pwm_2] sub-node\n");
		return -EINVAL;
	}

	pwm3 = of_get_child_by_name(node, "pwm_3");
	if (!pwm3) {
		dev_err(&pdev->dev, "could not find [pwm_3] sub-node\n");
		return -EINVAL;
	}

	/* PWM0 */
	if (!of_property_read_u32(pwm0, "clkout_div", &val))
		pwm->clkout_div[0] = val;

	if (!of_property_read_u32(pwm0, "clksrc_div", &val))
		pwm->clksrc_div[0] = val;

	set_real_freq_by_target_div(pwm, 0, pwm->clksrc_div[0], pwm->clkout_div[0]);

	if (!of_property_read_u32(pwm0, "enable", &val))
		pwm->enable[0] = val;

	if(!of_property_read_u32(pwm0, "duty_rate", &val))
		set_clk_duty(pwm, 0, val);

	pr_info("%s %s - hwpwm=(%d) enable=(%d) duty_rate=(%d) clksrc_div=(%d) clkout_div=(%d)---  \n",
		DEV_NAME, __func__, 0, pwm->enable[0], pwm->duty_rate[0], pwm->clksrc_div[0], pwm->clkout_div[0]);
	pr_info("%s %s - defualt output frequence = %dHz ---  \n",
		DEV_NAME, __func__, pwm->out_freq[0]);

	/* PWM1 */
	if (!of_property_read_u32(pwm1, "clkout_div", &val))
		pwm->clkout_div[1] = val;

	if (!of_property_read_u32(pwm1, "clksrc_div", &val))
		pwm->clksrc_div[1] = val;

	set_real_freq_by_target_div(pwm, 1, pwm->clksrc_div[1], pwm->clkout_div[1]);

	if (!of_property_read_u32(pwm1, "enable", &val))
		pwm->enable[1] = val;

	if(!of_property_read_u32(pwm1, "duty_rate", &val))
		set_clk_duty(pwm, 1, val);

	pr_info("%s %s - hwpwm=(%d) enable=(%d) duty_rate=(%d) clksrc_div=(%d) clkout_div=(%d)---  \n",
		DEV_NAME, __func__, 1, pwm->enable[1], pwm->duty_rate[1], pwm->clksrc_div[1], pwm->clkout_div[1]);
	pr_info("%s %s - defualt output frequence = %dHz ---  \n",
		DEV_NAME, __func__, pwm->out_freq[1]);

	/* PWM2 */
	if (!of_property_read_u32(pwm2, "clkout_div", &val))
		pwm->clkout_div[2] = val;

	if (!of_property_read_u32(pwm2, "clksrc_div", &val))
		pwm->clksrc_div[2] = val;

	set_real_freq_by_target_div(pwm, 2, pwm->clksrc_div[2], pwm->clkout_div[2]);

	if (!of_property_read_u32(pwm2, "enable", &val))
		pwm->enable[2] = val;

	if(!of_property_read_u32(pwm2, "duty_rate", &val))
		set_clk_duty(pwm, 2, val);

	pr_info("%s %s - hwpwm=(%d) enable=(%d) duty_rate=(%d) clksrc_div=(%d) clkout_div=(%d)---  \n",
		DEV_NAME, __func__, 2, pwm->enable[2], pwm->duty_rate[2], pwm->clksrc_div[2], pwm->clkout_div[2]);
	pr_info("%s %s - defualt output frequence = %dHz ---  \n",
		DEV_NAME, __func__, pwm->out_freq[2]);

	/* PWM3 */
	if (!of_property_read_u32(pwm3, "clkout_div", &val))
		pwm->clkout_div[3] = val;

	if (!of_property_read_u32(pwm3, "clksrc_div", &val))
		pwm->clksrc_div[3] = val;

	set_real_freq_by_target_div(pwm, 3, pwm->clksrc_div[3], pwm->clkout_div[3]);

	if (!of_property_read_u32(pwm3, "enable", &val))
		pwm->enable[3] = val;

	if(!of_property_read_u32(pwm3, "duty_rate", &val))
		set_clk_duty(pwm, 3, val);

	pr_info("%s %s - hwpwm=(%d) enable=(%d) duty_rate=(%d) clksrc_div=(%d) clkout_div=(%d)---  \n",
		DEV_NAME, __func__, 3, pwm->enable[3], pwm->duty_rate[3], pwm->clksrc_div[3], pwm->clkout_div[3]);
	pr_info("%s %s - defualt output frequence = %dHz ---  \n",
		DEV_NAME, __func__, pwm->out_freq[3]);

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &rtd1295_pwm_ops;
	pwm->chip.base = 0; // -1;
	pwm->chip.npwm = NUM_PWM;
	pwm->chip.can_sleep = true;

	ret = sysfs_create_group(&pdev->dev.kobj, &pwm_dev_attr_group);
	if (ret < 0) {
		dev_err(&pdev->dev, "sysfs_create_group() failed: %d\n", ret);
		return ret;
	}

	ret = pwmchip_add(&pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		sysfs_remove_group(&pdev->dev.kobj, &pwm_dev_attr_group);
		return ret;
	}

	for (i=0; i<NUM_PWM; i++)
		pwm_set_register(pwm, i);

	PWM_DEBUG("%s %s --  done! !\n", DEV_NAME, __func__);

	return 0;
}

static int rtd1295_pwm_remove(struct platform_device *pdev)
{
	struct rtd1295_pwm_chip *pc = platform_get_drvdata(pdev);
	int i;

	for (i=0; i<NUM_PWM; i++) {
		pc->enable[i] = 0;
		pwm_set_register(pc, i);
	}
	sysfs_remove_group(&pdev->dev.kobj, &pwm_dev_attr_group);

	PWM_DEBUG("%s %s ---- \n", DEV_NAME, __func__);

	return pwmchip_remove(&pc->chip);
}

static const struct of_device_id rtd1295_pwm_of_match[] = {
	{ .compatible = "Realtek,rtd1295-pwm" },
	{ }
};
MODULE_DEVICE_TABLE(of, rtd1295_pwm_of_match);

static struct platform_driver rtd1295_pwm_platform_driver = {
	.driver = {
		.name		= "pwm",
		.owner		= THIS_MODULE,
		.of_match_table = of_match_ptr(rtd1295_pwm_of_match),
	},
	.probe = rtd1295_pwm_probe,
	.remove = rtd1295_pwm_remove,
};
module_platform_driver(rtd1295_pwm_platform_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("REALTEK Corporation");
MODULE_ALIAS("platform:rtd1295-pwm");
