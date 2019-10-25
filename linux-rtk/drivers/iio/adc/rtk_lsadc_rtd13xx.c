/*
 * Realtek Low Speed ADC driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hwmon.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_address.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/reset.h>

#include "rtk_lsadc_rtd13xx.h"

/*
#define rtd_inb(offset)			(*(volatile unsigned char *)(offset))
#define rtd_inw(offset)			(*(volatile unsigned short *)(offset))
#define rtd_inl(offset)			(*(volatile unsigned long *)(offset))

#define rtd_outb(offset,val)	(*(volatile unsigned char *)(offset) = val)
#define rtd_outw(offset,val)	(*(volatile unsigned short *)(offset) = val)
#define rtd_outl(offset,val)	(*(volatile unsigned long *)(offset) = val)
*/
#define LSADC_IRQ_DEFINED 	(1)
#define SA_SHIRQ		IRQF_SHARED
#define LSADC_READL(reg)        readl((void __iomem *)(reg + (uintptr_t)(pc->lsadc_addr)))
#define LSADC_WRITEL(val, reg)  writel(val, (void __iomem *)(reg + (uintptr_t)(pc->lsadc_addr)))

struct rtk_lsadc_pad_info {
	uint			activate;
	uint			ctrl_mode;
	uint			pad_sw;
	uint			threshold;
	uint			vref_sel;
};

struct rtk_lsadc_info {
	struct rtk_lsadc_pad_info	padInfoSet[2];
	uint				pad0_adc_val;
	uint				pad1_adc_val;
	uint				irq;
	uint				clk_gating_en;
};

struct rtk_lsadc_device {
	struct device			*dev;
	struct rtk_lsadc_info		lsadc[1];
	uint				crt_lsadc_pg_val;
	void __iomem			*crt_lsadc_pg_addr;
	void __iomem			*isr_addr;
	void __iomem			*lsadc_addr;
};

#ifdef LSADC_IRQ_DEFINED
static irqreturn_t lsadc0_interrupt_pad(int irq, void *dev)
{
	struct rtk_lsadc_device *pc = dev;
	uint status_reg;
	uint pad0_reg, pad1_reg;
	uint pad0_int, pad1_int;
	uint new_adc_val=0;
	int interrupt_flag=0;

	interrupt_flag = ISR_MASK_LSADC0_INT & readl(pc->isr_addr);

	{
		status_reg = LSADC_READL(LSADC0_STATUS_ADDR);

		pad0_int = LSADC_STATUS_MASK_PAD0_STATUS & status_reg;
		pad1_int = LSADC_STATUS_MASK_PAD1_STATUS & status_reg;

		pad0_reg = LSADC_READL(LSADC0_PAD0_ADDR);
		pad1_reg = LSADC_READL(LSADC0_PAD1_ADDR);
		pr_err("--- lsadc0_interrupt_pad :  pad0_adc=0x%0x, pad1_adc=0x%0x \n",pc->lsadc[0].pad0_adc_val,pc->lsadc[0].pad1_adc_val);

		if(pad0_int) {
			new_adc_val = pad0_reg & LSADC0_PAD_MASK_ADC_VAL;
			pr_err(" lsadc0_interrupt_pad : pad0 interrupt! status_reg=0x%x , adc_val=> from [%d] to [%d] \n",
			status_reg, pc->lsadc[0].pad0_adc_val,new_adc_val);
			if( pc->lsadc[0].pad0_adc_val > new_adc_val ) {
				pr_err(" lsadc0_interrupt_pad : pad0 adc became smaller! \n\n");
			}
			else {
				pr_err(" lsadc0_interrupt_pad : pad0 adc became bigger! \n\n");
			}
			pc->lsadc[0].pad0_adc_val=new_adc_val;
		}

		if(pad1_int) {
			new_adc_val = pad1_reg & LSADC0_PAD_MASK_ADC_VAL;
			pr_err(" lsadc0_interrupt_pad : pad1 interrupt! status_reg=0x%x , adc_val=> from [%d] to [%d] \n",
			status_reg, pc->lsadc[0].pad1_adc_val,new_adc_val);
			if( pc->lsadc[0].pad1_adc_val > new_adc_val ) {
				pr_err(" lsadc0_interrupt_pad : pad1 adc became smaller! \n\n");
			}
			else {
				pr_err(" lsadc0_interrupt_pad : pad1 adc became bigger! \n\n");
			}
			pc->lsadc[0].pad1_adc_val=new_adc_val;
		}

		status_reg = status_reg | ( LSADC_STATUS_MASK_PAD0_STATUS | LSADC_STATUS_MASK_PAD1_STATUS);  // reset INT flag
		LSADC_WRITEL(status_reg, LSADC0_STATUS_ADDR);

		return IRQ_HANDLED;
	}
}
#endif

static ssize_t rtk_lsadc0_show_info(struct device *dev, struct device_attribute
			      *devattr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	uint ctrl_reg;
	uint analog_ctrl_reg;
	uint pad0_reg, pad1_reg;
	uint lsadc_status_reg;
	uint pad0_set[5], pad1_set[5];
	char padBuffer[512], tmpBuf[64];
	int isr_value=0;
	int i=0;

	isr_value = readl(pc->isr_addr);
	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);
	analog_ctrl_reg = LSADC_READL(LSADC0_ANALOG_CTRL_ADDR);

	if( (ctrl_reg & LSADC_CTRL_MASK_ENABLE) == 0 ) {
		ctrl_reg = ctrl_reg | LSADC_CTRL_MASK_ENABLE ;
		LSADC_WRITEL(ctrl_reg, LSADC0_CTRL_ADDR);
		pr_info("--- rtk_lsadc0_show_info  :    write ctrl_enable	ctrl_reg=0x%x  ---  \n",ctrl_reg);
	}

	pad0_reg = LSADC_READL(LSADC0_PAD0_ADDR);
	pad1_reg = LSADC_READL(LSADC0_PAD1_ADDR);

	pc->lsadc[0].pad0_adc_val = pad0_reg & LSADC0_PAD_MASK_ADC_VAL;
	pc->lsadc[0].pad1_adc_val = pad1_reg & LSADC0_PAD_MASK_ADC_VAL;

	strcpy(padBuffer, "info:\n");
	for(i=0; i<5; i++) {
		pad0_set[i] = LSADC_READL(LSADC0_PAD0_LEVEL_SET0_ADDR+(i*4));
		pad1_set[i] = LSADC_READL(LSADC0_PAD1_LEVEL_SET0_ADDR+(i*4));
		sprintf(tmpBuf, "set_idx=%d:pad0_set=0x%0x pad1_set=0x%0x\n",i, pad0_set[i],pad1_set[i]);
		strcat(padBuffer, tmpBuf);
	}

	return sprintf(buf, "rtk_lsadc0_show_info--\n isr_value=0x%x \n ctrl_reg=0x%x \n lsadc_status_reg=0x%x\n analog_ctrl_reg=0x%x\n pad0_reg=0x%x\n pad1_reg=0x%x \n pad0_adc=0x%x\n pad1_adc=0x%x  \n %s" ,
		isr_value, ctrl_reg ,lsadc_status_reg,analog_ctrl_reg ,pad0_reg,pad1_reg,pc->lsadc[0].pad0_adc_val ,pc->lsadc[0].pad1_adc_val ,padBuffer);
}

ssize_t rtk_lsadc0_show_debounce(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	uint ctrl_reg;
	uint lsadc_status_reg;
	int isr_value = 0 ;
	int debounce_cnt = 0;

	isr_value = readl(pc->isr_addr);
	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);

	debounce_cnt = (ctrl_reg & LSADC0_CTRL_DEBOUNCE_MASK) >> 20;

	pr_info("--- debug : rtk_lsadc0_show_debounce : ctrl_reg=0x%x, isr_value=0x%x, lsadc_status_reg=0x%x \n    debounce_cnt=%d (0~15) ---- \n",
		ctrl_reg, isr_value, lsadc_status_reg, debounce_cnt);

	return sprintf(buf, "%d\n", debounce_cnt);
}

ssize_t rtk_lsadc0_store_debounce(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	uint ctrl_reg;
	uint lsadc_status_reg;
	int isr_value = 0 ;
	int debounce_cnt = 0;
	int value = 0;

	isr_value = readl(pc->isr_addr);
	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);

	debounce_cnt = ( ctrl_reg & LSADC0_CTRL_DEBOUNCE_MASK ) >> 20;

	if(buf ==NULL) {
		pr_err("--- debug : rtk_lsadc0_store_debounce	====  buffer is null, return \n");
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : rtk_lsadc0_store_debounce : get value=%d \n", value);

	if(debounce_cnt == value) {
		pr_err("--- debug : rtk_lsadc0_store_debounce	====  the same, do nothing (value=%d) \n", value);
		return count;
	}
	if(value > 15 || value < 0) {
		pr_err("--- debug : rtk_lsadc0_store_debounce	====  value (%d) out of range, (valid data => 0-15) \n", value);
		return count;
	}

	debounce_cnt = value;

	ctrl_reg =(ctrl_reg & (~LSADC0_CTRL_DEBOUNCE_MASK))|(debounce_cnt << 20);
	LSADC_WRITEL(ctrl_reg, LSADC0_CTRL_ADDR);
	pr_err("--- debug : rtk_lsadc0_store0_debounce : write ctrl_reg=0x%x debounce_cnt=%d \n", ctrl_reg, debounce_cnt);

	isr_value = readl(pc->isr_addr);
	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);

	pr_info("--- debug : rtk_lsadc0_store_debounce : ctrl_reg=0x%x, isr_value=0x%x, lsadc_status_reg=0x%x \n    debounce_cnt=%d ---- \n",
		ctrl_reg, isr_value, lsadc_status_reg, debounce_cnt);

	return count;
}

ssize_t rtk_lsadc0_show_threshold0(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);
	uint pad_reg;
	uint threshold;

	pad_reg = LSADC_READL(LSADC0_PAD0_ADDR);
	threshold = (pad_reg & LSADC_PAD_MASK_THRESHOLD) >> 16;

	pr_info("--- debug : %s : pad_reg = 0x%x\n    threshold = %d (0~63) ---- \n",
		__func__, pad_reg, threshold);

	return sprintf(buf, "%d\n", threshold);
}

ssize_t rtk_lsadc0_store_threshold0(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);
	uint pad_reg;
	uint threshold;
	int value = 0;

	pad_reg = LSADC_READL(LSADC0_PAD0_ADDR);

	threshold = (pad_reg & LSADC_PAD_MASK_THRESHOLD) >> 16;

	if(buf ==NULL) {
		pr_err("--- debug : %s ====  buffer is null, return \n", __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : %s : get value = %d \n", __func__, value);

	if(threshold == value) {
		pr_err("--- debug : %s ====  the same, do nothing (value = %d) \n", __func__, value);
		return count;
	}
	if(value > 63 || value < 0) {
		pr_err("--- debug : %s ====  value (%d) out of range, (valid data => 0-63) \n", __func__, value);
		return count;
	}

	threshold = value;

	pad_reg = (pad_reg & ~LSADC_PAD_MASK_THRESHOLD) | (threshold << 16);
	LSADC_WRITEL(pad_reg, LSADC0_PAD0_ADDR);
	pr_err("--- debug : %s : write pad_reg = 0x%x threshold = %d \n", __func__, pad_reg, threshold);

	return count;
}

ssize_t rtk_lsadc0_show_threshold1(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);
	uint pad_reg;
	uint threshold;

	pad_reg = LSADC_READL(LSADC0_PAD1_ADDR);
	threshold = (pad_reg & LSADC_PAD_MASK_THRESHOLD) >> 16;

	pr_info("--- debug : %s : pad_reg = 0x%x\n    threshold = %d (0~63) ---- \n",
		__func__, pad_reg, threshold);

	return sprintf(buf, "%d\n", threshold);
}

ssize_t rtk_lsadc0_store_threshold1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);
	uint pad_reg;
	uint threshold;
	int value = 0;

	pad_reg = LSADC_READL(LSADC0_PAD1_ADDR);

	threshold = (pad_reg & LSADC_PAD_MASK_THRESHOLD) >> 16;

	if(buf ==NULL) {
		pr_err("--- debug : %s ====  buffer is null, return \n", __func__);
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : %s : get value = %d \n", __func__, value);

	if(threshold == value) {
		pr_err("--- debug : %s ====  the same, do nothing (value = %d) \n", __func__, value);
		return count;
	}
	if(value > 63 || value < 0) {
		pr_err("--- debug : %s ====  value (%d) out of range, (valid data => 0-63) \n", __func__, value);
		return count;
	}

	threshold = value;

	pad_reg = (pad_reg & ~LSADC_PAD_MASK_THRESHOLD) | (threshold << 16);
	LSADC_WRITEL(pad_reg, LSADC0_PAD1_ADDR);
	pr_err("--- debug : %s : write pad_reg = 0x%x threshold = %d \n", __func__, pad_reg, threshold);

	return count;
}

ssize_t rtk_lsadc_show_vdd_mux_sel(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux_sel = 0;

	vdd_mux_sel = (readl(pc->crt_lsadc_pg_addr) & CRT_LSADC_VDDMUX_SEL_MASK) >> CRT_LSADC_VDDMUX_SEL_OFFSET;

	pr_info("--- debug : rtk_lsadc_show_vdd_mux_sel : vdd_mux_sel=%d (0:VDD1; 1:VDD2) ---- \n", vdd_mux_sel);

	return sprintf(buf, "%d\n", vdd_mux_sel);
}

ssize_t rtk_lsadc_store_vdd_mux_sel(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux_sel = 0;
	int value=0;
	uint crt_lsadc_pg_val;

	crt_lsadc_pg_val = readl(pc->crt_lsadc_pg_addr);
	vdd_mux_sel = (crt_lsadc_pg_val & CRT_LSADC_VDDMUX_SEL_MASK) >> CRT_LSADC_VDDMUX_SEL_OFFSET;

	if(buf ==NULL) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux_sel	====  buffer is null, return \n");
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux_sel : get value=%d \n", value);

	if(vdd_mux_sel == value) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux_sel	====  the same, do nothing (value=%d) \n", value);
		return count;
	}
	if(value > 1 || value < 0) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux_sel	====  value (%d) out of range, (valid data => 0-1) \n", value);
		return count;
	}

	vdd_mux_sel = value;

	crt_lsadc_pg_val = (crt_lsadc_pg_val & (~CRT_LSADC_VDDMUX_SEL_MASK)) | (vdd_mux_sel << CRT_LSADC_VDDMUX_SEL_OFFSET);
	pc->crt_lsadc_pg_val = crt_lsadc_pg_val;
	writel(pc->crt_lsadc_pg_val, pc->crt_lsadc_pg_addr);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux_sel : write crt_lsadc_pg_val=0x%x vdd_mux_sel=%d \n", crt_lsadc_pg_val, vdd_mux_sel);

	return count;
}

ssize_t rtk_lsadc_show_vdd_mux1(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux1 = 0;

	vdd_mux1 = (readl(pc->crt_lsadc_pg_addr) & CRT_LSADC_VDD_MUX1_MASK) >> CRT_LSADC_VDD_MUX1_OFFSET;

	pr_info("--- debug : rtk_lsadc_show_vdd_mux1 : vdd_mux1=%d (VDD1 input MUX select) ---- \n", vdd_mux1);

	return sprintf(buf, "%d\n", vdd_mux1);
}

ssize_t rtk_lsadc_store_vdd_mux1(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux1 = 0;
	int value=0;
	uint crt_lsadc_pg_val;

	crt_lsadc_pg_val = readl(pc->crt_lsadc_pg_addr);
	vdd_mux1 = (crt_lsadc_pg_val & CRT_LSADC_VDD_MUX1_MASK) >> CRT_LSADC_VDD_MUX1_OFFSET;

	if(buf ==NULL) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux1	====  buffer is null, return \n");
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux1 : get value=%d \n", value);

	if(vdd_mux1 == value) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux1	====  the same, do nothing (value=%d) \n", value);
		return count;
	}
	if(value > 15 || value < 0) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux1	====  value (%d) out of range, (valid data => 0-15) \n", value);
		return count;
	}

	vdd_mux1 = value;

	crt_lsadc_pg_val = (crt_lsadc_pg_val & (~CRT_LSADC_VDD_MUX1_MASK)) | (vdd_mux1 << CRT_LSADC_VDD_MUX1_OFFSET);
	pc->crt_lsadc_pg_val = crt_lsadc_pg_val;
	writel(pc->crt_lsadc_pg_val, pc->crt_lsadc_pg_addr);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux1 : write crt_lsadc_pg_val=0x%x vdd_mux1=%d \n", crt_lsadc_pg_val, vdd_mux1);

	return count;
}

ssize_t rtk_lsadc_show_vdd_mux2(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux2 = 0;

	vdd_mux2 = (readl(pc->crt_lsadc_pg_addr) & CRT_LSADC_VDD_MUX2_MASK) >> CRT_LSADC_VDD_MUX2_OFFSET;

	pr_info("--- debug : rtk_lsadc_show_vdd_mux2 : vdd_mux2=%d (VDD2 input MUX select) ---- \n", vdd_mux2);

	return sprintf(buf, "%d\n", vdd_mux2);
}

ssize_t rtk_lsadc_store_vdd_mux2(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct rtk_lsadc_device *pc = platform_get_drvdata(pdev);

	int vdd_mux2 = 0;
	int value=0;
	uint crt_lsadc_pg_val;

	crt_lsadc_pg_val = readl(pc->crt_lsadc_pg_addr);
	vdd_mux2 = (crt_lsadc_pg_val & CRT_LSADC_VDD_MUX2_MASK) >> CRT_LSADC_VDD_MUX2_OFFSET;

	if(buf ==NULL) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux2	====  buffer is null, return \n");
		return count;
	}
	sscanf(buf, "%d", &value);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux2 : get value=%d \n", value);

	if(vdd_mux2 == value) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux2	====  the same, do nothing (value=%d) \n", value);
		return count;
	}
	if(value > 15 || value < 0) {
		pr_err("--- debug : rtk_lsadc_store_vdd_mux2	====  value (%d) out of range, (valid data => 0-15) \n", value);
		return count;
	}

	vdd_mux2 = value;

	crt_lsadc_pg_val = (crt_lsadc_pg_val & (~CRT_LSADC_VDD_MUX2_MASK)) | (vdd_mux2 << CRT_LSADC_VDD_MUX2_OFFSET);
	pc->crt_lsadc_pg_val = crt_lsadc_pg_val;
	writel(pc->crt_lsadc_pg_val, pc->crt_lsadc_pg_addr);

	pr_err("--- debug : rtk_lsadc_store_vdd_mux2 : write crt_lsadc_pg_val=0x%x vdd_mux2=%d \n", crt_lsadc_pg_val, vdd_mux2);

	return count;
}

static DEVICE_ATTR(debounce0, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc0_show_debounce, rtk_lsadc0_store_debounce);
static DEVICE_ATTR(threshold00, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc0_show_threshold0, rtk_lsadc0_store_threshold0);
static DEVICE_ATTR(threshold01, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc0_show_threshold1, rtk_lsadc0_store_threshold1);
static DEVICE_ATTR(vdd_mux_sel, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc_show_vdd_mux_sel, rtk_lsadc_store_vdd_mux_sel);
static DEVICE_ATTR(vdd_mux1, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc_show_vdd_mux1, rtk_lsadc_store_vdd_mux1);
static DEVICE_ATTR(vdd_mux2, ((S_IRUGO | S_IWUGO) & ~S_IWOTH), rtk_lsadc_show_vdd_mux2, rtk_lsadc_store_vdd_mux2);
static DEVICE_ATTR(info0, S_IRUGO, rtk_lsadc0_show_info, NULL);

static struct attribute *rtk_attr_base[] = {
	&dev_attr_info0.attr,
	&dev_attr_debounce0.attr,
	&dev_attr_threshold00.attr,
	&dev_attr_threshold01.attr,
	&dev_attr_vdd_mux_sel.attr,
	&dev_attr_vdd_mux1.attr,
	&dev_attr_vdd_mux2.attr,
	NULL
};

static const struct attribute_group rtk_group_base = {
	.attrs = rtk_attr_base,
};

static int __init rtk_lsadc_probe(struct platform_device *pdev)
{
	struct rtk_lsadc_device *priv, *pc;
	struct device_node *lsadc0_pad0_node, *lsadc0_pad1_node;
	int ret = -EINVAL, val;
	uint ctrl_reg;
	uint analog_ctrl_reg;
	uint pad0_reg, pad1_reg;
	uint lsadc_status_reg;
	uint irq_num;
	uint clk_gating_en, lsadc_power_reg;
	uint vdd_mux_sel, vdd_mux1, vdd_mux2, vdd_mux_en;
	struct clk *clk;
	struct reset_control *rstc;

	pr_info("--- debug : rtk_lsadc_probe \n");

	lsadc0_pad0_node = of_get_child_by_name(pdev->dev.of_node, "rtk-lsadc0-pad0");
	if (!lsadc0_pad0_node) {
		dev_err(&pdev->dev, "could not find [rtk-lsadc0-pad0] sub-node\n");
		return -EINVAL;
	}
	lsadc0_pad1_node = of_get_child_by_name(pdev->dev.of_node, "rtk-lsadc0-pad1");
	if (!lsadc0_pad1_node) {
		dev_err(&pdev->dev, "could not find [rtk-lsadc0-pad1] sub-node\n");
		return -EINVAL;
	}

	/* Request IRQ */
	irq_num = irq_of_parse_and_map(pdev->dev.of_node, 0);

	pc = priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&pdev->dev, "failed to allocate memory\n");
		return -ENOMEM;
	}

	priv->dev = &pdev->dev;
	priv->lsadc[0].irq = irq_num;
	priv->isr_addr = of_iomap(pdev->dev.of_node, 0);
	priv->lsadc_addr = of_iomap(pdev->dev.of_node, 1);
	priv->crt_lsadc_pg_addr = of_iomap(pdev->dev.of_node, 2);

	platform_set_drvdata(pdev, priv);

	if (!of_property_read_u32(pdev->dev.of_node, "clk_gating_en", &clk_gating_en)) {
		priv->lsadc[0].clk_gating_en = clk_gating_en;
	}

	// set CRT LSADC_PG from device tree
	if (!of_property_read_u32(pdev->dev.of_node, "vdd_mux_sel", &vdd_mux_sel) &&
			!of_property_read_u32(pdev->dev.of_node, "vdd_mux1", &vdd_mux1) &&
			!of_property_read_u32(pdev->dev.of_node, "vdd_mux2", &vdd_mux2) &&
			!of_property_read_u32(pdev->dev.of_node, "vdd_mux_en", &vdd_mux_en)) {
		priv->crt_lsadc_pg_val = ((vdd_mux_sel << CRT_LSADC_VDDMUX_SEL_OFFSET) & CRT_LSADC_VDDMUX_SEL_MASK) |
								 ((vdd_mux1 << CRT_LSADC_VDD_MUX1_OFFSET) & CRT_LSADC_VDD_MUX1_MASK) |
								 ((vdd_mux2 << CRT_LSADC_VDD_MUX2_OFFSET) & CRT_LSADC_VDD_MUX2_MASK) |
								 ((vdd_mux_en << CRT_LSADC_VDDMUX_EN_OFFSET) & CRT_LSADC_VDDMUX_EN_MASK);
	} else {
		priv->crt_lsadc_pg_val = CRT_LSADC_PG_VALUE;
	}


	// set LSADC0 pad0 from device tree : [pad_idx0]
	if (!of_property_read_u32(lsadc0_pad0_node, "activate", &val))
		priv->lsadc[0].padInfoSet[0].activate=val;

	if (!of_property_read_u32(lsadc0_pad0_node, "ctrl_mode", &val))
		priv->lsadc[0].padInfoSet[0].ctrl_mode=val;

	if (!of_property_read_u32(lsadc0_pad0_node, "sw_idx", &val)){
		if(val == 1)
			priv->lsadc[0].padInfoSet[0].pad_sw=val;
		else
			priv->lsadc[0].padInfoSet[0].pad_sw=0;
	}

	if (!of_property_read_u32(lsadc0_pad0_node, "voltage_threshold", &val))
		priv->lsadc[0].padInfoSet[0].threshold=val;

	// set LSADC0 pad1 from device tree : [pad_idx1]
	if (!of_property_read_u32(lsadc0_pad1_node, "activate", &val))
		priv->lsadc[0].padInfoSet[1].activate=val;
	else
		priv->lsadc[0].padInfoSet[1].activate=0;

	if (!of_property_read_u32(lsadc0_pad1_node, "ctrl_mode", &val))
		priv->lsadc[0].padInfoSet[1].ctrl_mode=val;

	if (!of_property_read_u32(lsadc0_pad1_node, "sw_idx", &val)){
		if(val == 1)
			priv->lsadc[0].padInfoSet[1].pad_sw=val;
		else
			priv->lsadc[0].padInfoSet[1].pad_sw=0;
	}

	if (!of_property_read_u32(lsadc0_pad1_node, "voltage_threshold", &val))
		priv->lsadc[0].padInfoSet[1].threshold=val;


	clk = clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk)) {
		clk = NULL;
		pr_err("can't get LSADC clock\n");
	} else {
		clk_prepare_enable(clk);
	}


	rstc = reset_control_get(&pdev->dev, NULL);
	if (IS_ERR(rstc)) {
		pr_err("can't get LSADC reset\n");
	} else {
		reset_control_deassert(rstc);
		reset_control_put(rstc);
	}

	lsadc_power_reg = LSADC_READL(LSADC0_POWER_ADDR) & ~(LSADC0_CLK_GATING_EN);
	if(priv->lsadc[0].clk_gating_en == 1)
		lsadc_power_reg |= LSADC0_CLK_GATING_EN;

	LSADC_WRITEL(lsadc_power_reg, LSADC0_POWER_ADDR);
	pr_info("--- debug :    write lsadc0_power_reg=0x%x  --  \n\n",lsadc_power_reg);

	// Initial Ananlog_ctrl value to 0x00011101
	LSADC_WRITEL(LSADC_ANALOG_CTRL_VALUE, LSADC0_ANALOG_CTRL_ADDR);
	mdelay(100);

	//LSADC0
	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	analog_ctrl_reg = LSADC_READL(LSADC0_ANALOG_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);
	pad0_reg = LSADC_READL(LSADC0_PAD0_ADDR);
	pad1_reg = LSADC_READL(LSADC0_PAD1_ADDR);

	pr_err("--- debug :   from device tree: pad0=[activate=%d, ctrl_mode=%d, pad_sw=%d, threshold=%d]---  \n",
			priv->lsadc[0].padInfoSet[0].activate, priv->lsadc[0].padInfoSet[0].ctrl_mode, priv->lsadc[0].padInfoSet[0].pad_sw, priv->lsadc[0].padInfoSet[0].threshold);
	pr_err("--- debug :   from device tree: pad1=[activate=%d, ctrl_mode=%d, pad_sw=%d, threshold=%d]---  \n\n",
			priv->lsadc[0].padInfoSet[1].activate, priv->lsadc[0].padInfoSet[1].ctrl_mode, priv->lsadc[0].padInfoSet[1].pad_sw, priv->lsadc[0].padInfoSet[1].threshold);

	pr_err("--- debug :  current value =   ctrl_reg=0x%x, lsadc_status_reg=0x%x, pad0_reg=0x%x, pad1_reg=0x%x ---- \n",
		ctrl_reg, lsadc_status_reg,pad0_reg,pad1_reg );

	if( priv->lsadc[0].padInfoSet[0].activate==1) {
		pad0_reg = pad0_reg | LSADC_PAD_MASK_ACTIVE ;
		if( priv->lsadc[0].padInfoSet[0].ctrl_mode == 1 )
			pad0_reg = pad0_reg | LSADC_PAD_MASK_CTRL;
		else
			pad0_reg = pad0_reg & ~(LSADC_PAD_MASK_CTRL);

		if( priv->lsadc[0].padInfoSet[0].pad_sw == 1 )
			pad0_reg = pad0_reg | LSADC_PAD_MASK_SW;
		else
			pad0_reg = pad0_reg & ~(LSADC_PAD_MASK_SW);

		if(priv->lsadc[0].padInfoSet[0].threshold <=0xFF && priv->lsadc[0].padInfoSet[0].threshold >=0 )
			pad0_reg = pad0_reg | (LSADC_PAD_MASK_THRESHOLD & (priv->lsadc[0].padInfoSet[0].threshold << 16 ));

		LSADC_WRITEL(pad0_reg, LSADC0_PAD0_ADDR);
		pr_info("--- debug :    write pad0_reg=0x%x ---  \n",pad0_reg);
	}
	if( priv->lsadc[0].padInfoSet[1].activate==1) {
		pad1_reg = pad1_reg | LSADC_PAD_MASK_ACTIVE ;
		if( priv->lsadc[0].padInfoSet[1].ctrl_mode == 1 )
			pad1_reg = pad1_reg | LSADC_PAD_MASK_CTRL;
		else
			pad1_reg = pad1_reg & ~(LSADC_PAD_MASK_CTRL);

		if( priv->lsadc[0].padInfoSet[1].pad_sw == 1 )
			pad1_reg = pad1_reg | LSADC_PAD_MASK_SW;
		else
			pad1_reg = pad1_reg & ~(LSADC_PAD_MASK_SW);

		if(priv->lsadc[0].padInfoSet[1].threshold <=0xFF && priv->lsadc[0].padInfoSet[1].threshold >=0 )
			pad1_reg = pad1_reg | (LSADC_PAD_MASK_THRESHOLD & (priv->lsadc[0].padInfoSet[1].threshold << 16 ));

		LSADC_WRITEL(pad1_reg, LSADC0_PAD1_ADDR);
		pr_info("--- debug :    write pad1_reg=0x%x  ---  \n",pad1_reg);
	}

	ctrl_reg = ctrl_reg | LSADC_CTRL_MASK_ENABLE | LSADC0_CTRL_DEBOUNCE_CNT | LSADC_CTRL_MASK_SEL_WAIT ;
	LSADC_WRITEL(ctrl_reg, LSADC0_CTRL_ADDR);
	pr_err("--- debug :    rtk_lsadc0_probe	ctrl_reg=0x%x  irq_num=%d---  \n",ctrl_reg, irq_num);

	if( (lsadc_status_reg & LSADC_STATUS_MASK_IRQ_EN) != LSADC_STATUS_MASK_IRQ_EN ) {
		lsadc_status_reg = lsadc_status_reg | LSADC_STATUS_MASK_IRQ_EN ;
		LSADC_WRITEL(lsadc_status_reg, LSADC0_STATUS_ADDR);
		pr_info("--- debug :    write lsadc_status_reg=0x%x  --  \n\n",lsadc_status_reg);
	}

#ifdef LSADC_IRQ_DEFINED

	if (request_irq(priv->lsadc[0].irq, lsadc0_interrupt_pad, IRQF_SHARED, "lsadc0", priv)< 0)
	{
		pr_err("--- debug : unable to request LSADC0 irq#%d\n", priv->lsadc[0].irq);
		goto err;
	}
	// Enable IRQ for pad0/pad1, set LSADC0_STATUS to 0x0300000
	LSADC_WRITEL(LSADC_STATUS_ENABLE_IRQ, LSADC0_STATUS_ADDR);

#endif // LSADC_IRQ_DEFINED

	ctrl_reg = LSADC_READL(LSADC0_CTRL_ADDR);
	lsadc_status_reg = LSADC_READL(LSADC0_STATUS_ADDR);
	analog_ctrl_reg = LSADC_READL(LSADC0_ANALOG_CTRL_ADDR);
	pad0_reg = LSADC_READL(LSADC0_PAD0_ADDR);
	pad1_reg = LSADC_READL(LSADC0_PAD1_ADDR);

	priv->lsadc[0].pad0_adc_val = pad0_reg & LSADC0_PAD_MASK_ADC_VAL;
	priv->lsadc[0].pad1_adc_val = pad1_reg & LSADC0_PAD_MASK_ADC_VAL;

	pr_err("--- debug :  set value =   ctrl_reg=0x%x, lsadc_status_reg=0x%x, pad0_reg=0x%x, pad1_reg=0x%x ---- \n\n\n",
		ctrl_reg, lsadc_status_reg, pad0_reg, pad1_reg);

	// Init CRT LSADC PG
	writel(priv->crt_lsadc_pg_val, priv->crt_lsadc_pg_addr);
	pr_err("--- debug :    write crt_lsadc_pg_val=0x%x  --  \n",priv->crt_lsadc_pg_val);

	/* Register sysfs hooks */
	ret = sysfs_create_group(&pdev->dev.kobj, &rtk_group_base);
	if (ret)
		goto out_err_register;

	return 0;

out_err_register:
	pr_err("--- debug :    sysfs_create_group() failed, ret = %d\n", ret);
	sysfs_remove_group(&pdev->dev.kobj, &rtk_group_base);
err:
	return ret;
}

static int rtk_lsadc_remove(struct platform_device *pdev)
{
	struct rtk_lsadc_device *priv = platform_get_drvdata(pdev);
	sysfs_remove_group(&pdev->dev.kobj, &rtk_group_base);
#ifdef LSADC_IRQ_DEFINED
	free_irq(priv->lsadc[0].irq, priv);
#endif
	return 0;
}

static const struct of_device_id rtk_lsadc_of_match[] = {
	{ .compatible = "realtek,rtk-lsadc" },
	{ }
};
MODULE_DEVICE_TABLE(of, rtk_lsadc_of_match);


static struct platform_driver rtk_lsadc_platform_driver = {
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "rtk-lsadc",
		.of_match_table = rtk_lsadc_of_match,
	},
	.probe 		= rtk_lsadc_probe,
	.remove 	= rtk_lsadc_remove,
};
module_platform_driver(rtk_lsadc_platform_driver);

MODULE_DESCRIPTION("RTK LSADC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk-lsadc");


