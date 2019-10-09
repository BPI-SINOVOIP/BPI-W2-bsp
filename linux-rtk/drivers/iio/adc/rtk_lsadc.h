/*
 *
 * Realtek Low Speed ADC driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef  __RTD1295_LSADC_H_
#define  __RTD1295_LSADC_H_
#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_ARCH_RTD129x)
#define CRT_LSADC_CLK_ADDR                   (0x98000450)
#define CRT_LSADC_CLK_EN_VALUE               (4)
#endif /* CONFIG_ARCH_RTD129x */

#define CRT_LSADC_PG_VALUE                   (0x00000002)
#define CRT_LSADC_VDDMUX_EN_MASK             (0x00000002)
#define CRT_LSADC_VDDMUX_EN_OFFSET           (1)
#define CRT_LSADC_VDD_MUX2_MASK              (0x0000003C)
#define CRT_LSADC_VDD_MUX2_OFFSET            (2)
#define CRT_LSADC_VDD_MUX1_MASK              (0x000003C0)
#define CRT_LSADC_VDD_MUX1_OFFSET            (6)
#define CRT_LSADC_VDDMUX_SEL_MASK            (0x00000400)
#define CRT_LSADC_VDDMUX_SEL_OFFSET          (10)

#if defined(CONFIG_ARCH_RTD129x)
#define ISR_MASK_LSADC0_INT              (0x00200000)
#define ISR_MASK_LSADC1_INT              (0x00400000)
#elif defined(CONFIG_ARCH_RTD139x)
#define ISR_MASK_LSADC0_INT              (0x00010000)
#define ISR_MASK_LSADC1_INT              (0x00020000)
#endif /* CONFIG_ARCH_RTD129x | CONFIG_ARCH_RTD139x */


//#define LSADC_ANALOG_CTRL_VALUE              (0x00011101)
#define LSADC_ANALOG_CTRL_VALUE              (0x00000001)
#define LSADC_STATUS_ENABLE_IRQ              (0x03000000)
#define LSADC_CTRL_MASK_ENABLE               (0x00000001)
#define LSADC_CTRL_MASK_SEL_WAIT             (0x80000000)
#define LSADC0_CTRL_DEBOUNCE_CNT             (0x00800000)
#define LSADC0_CTRL_DEBOUNCE_MASK            (0x00F00000)
#define LSADC1_CTRL_DEBOUNCE_CNT             (0x00800000)
#define LSADC1_CTRL_DEBOUNCE_MASK            (0x00FF0000)
#define LSADC1_CTRL_VDD_GND_SEL_MASK         (0x00000030)

#define LSADC1_CTRL_MASK_VDD_GND_EN          (0x00000010)
#define LSADC1_CTRL_MASK_VDD_GND_SEL         (0x00000020)

#define LSADC0_PAD0_ADDR                     (0x00000000)
#define LSADC0_PAD1_ADDR                     (0x00000004)

#define LSADC0_CTRL_ADDR                     (0x00000020)
#define LSADC0_STATUS_ADDR                   (0x00000024)
#define LSADC0_ANALOG_CTRL_ADDR              (0x00000028)
//#define LSADC0_PERI_TOP_DEBUG_ADDR           (0x0000002c)

#define LSADC0_PAD0_LEVEL_SET0_ADDR          (0x00000030)
#define LSADC0_PAD0_LEVEL_SET1_ADDR          (0x00000034)
#define LSADC0_PAD0_LEVEL_SET2_ADDR          (0x00000038)
#define LSADC0_PAD0_LEVEL_SET3_ADDR          (0x0000003c)
#define LSADC0_PAD0_LEVEL_SET4_ADDR          (0x00000040)
#define LSADC0_PAD0_LEVEL_SET5_ADDR          (0x00000044)

#define LSADC0_PAD1_LEVEL_SET0_ADDR          (0x00000048)
#define LSADC0_PAD1_LEVEL_SET1_ADDR          (0x0000004c)
#define LSADC0_PAD1_LEVEL_SET2_ADDR          (0x00000050)
#define LSADC0_PAD1_LEVEL_SET3_ADDR          (0x00000054)
#define LSADC0_PAD1_LEVEL_SET4_ADDR          (0x00000058)
#define LSADC0_PAD1_LEVEL_SET5_ADDR          (0x0000005c)

//#define LSADC0_INT_PAD0_ADDR                 (0x00000078)
//#define LSADC0_INT_PAD1_ADDR                 (0x0000007c)
#define LSADC0_POWER_ADDR                    (0x00000080)
#define LSADC0_CLK_GATING_EN                 (0x00000001)
#define LSADC1_CLK_GATING_EN                 (0x00000002)

#define LSADC0_PAD_MASK_ACTIVE               (0x80000000)
#define LSADC0_PAD_MASK_THRESHOLD            (0x00FF0000)
#define LSADC0_PAD_MASK_SW                   (0x00001000)
#define LSADC0_PAD_MASK_CTRL                 (0x00000100)
#define LSADC0_PAD_MASK_ADC_VAL              (0x0000003F)
#define LSADC1_PAD_MASK_ADC_VAL              (0x0000007F)


#define LSADC1_PAD0_ADDR                     (0x00000100)
#define LSADC1_PAD1_ADDR                     (0x00000104)

#define LSADC1_CTRL_ADDR                     (0x00000120)
#define LSADC1_STATUS_ADDR                   (0x00000124)
#define LSADC1_ANALOG_CTRL_ADDR              (0x00000128)
//#define LSADC1_PERI_TOP_DEBUG_ADDR           (0x0000012c)

#define LSADC1_PAD0_LEVEL_SET0_ADDR          (0x00000130)
#define LSADC1_PAD0_LEVEL_SET1_ADDR          (0x00000134)
#define LSADC1_PAD0_LEVEL_SET2_ADDR          (0x00000138)
#define LSADC1_PAD0_LEVEL_SET3_ADDR          (0x0000013c)
#define LSADC1_PAD0_LEVEL_SET4_ADDR          (0x00000140)
#define LSADC1_PAD0_LEVEL_SET5_ADDR          (0x00000144)

#define LSADC1_PAD1_LEVEL_SET0_ADDR          (0x00000148)
#define LSADC1_PAD1_LEVEL_SET1_ADDR          (0x0000014c)
#define LSADC1_PAD1_LEVEL_SET2_ADDR          (0x00000150)
#define LSADC1_PAD1_LEVEL_SET3_ADDR          (0x00000154)
#define LSADC1_PAD1_LEVEL_SET4_ADDR          (0x00000158)
#define LSADC1_PAD1_LEVEL_SET5_ADDR          (0x0000015c)

//#define LSADC1_INT_PAD0_ADDR                 (0x00000178)
//#define LSADC1_INT_PAD1_ADDR                 (0x0000017c)
#define LSADC1_POWER_ADDR                    (0x00000180)

// define LSADC0_STATUS and LSADC1_STATUS MASK
#define LSADC_STATUS_MASK_PAD0_STATUS       (0x00000001)
#define LSADC_STATUS_MASK_PAD1_STATUS       (0x00000002)
#define LSADC_STATUS_MASK_PAD_CTRL_0        (0x00001000)
#define LSADC_STATUS_MASK_PAD_CTRL_4        (0x00010000)
#define LSADC_STATUS_MASK_ADC_BUSY          (0x00080000)
#define LSADC_STATUS_MASK_PAD_CNT           (0x00F00000)
#define LSADC_STATUS_MASK_IRQ_EN            (0x03000000)

// define LSADC0_PAD0/LSADC0_PAD1/LSADC1_PAD0/LSADC1_PAD1 MASK
#define LSADC_PAD_MASK_ACTIVE               (0x80000000)
#define LSADC_PAD_MASK_VREF_SEL             (0x01000000)
#define LSADC_PAD_MASK_THRESHOLD            (0x00FF0000)
#define LSADC_PAD_MASK_SW                   (0x00001000)
#define LSADC_PAD_MASK_CTRL                 (0x00000100)

#ifndef LITTLE_ENDIAN	// apply BIG_ENDIAN
typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     sel_wait:4;
		unsigned int     sel_adc_ck:4;
		unsigned int     debounce_cnt:4;
		unsigned int     reserved_0:4;
		unsigned int     dout_test_in:8;
		unsigned int     reserved_1:6;
		unsigned int     test_en:1;
		unsigned int     enable:1;
	};
} ST_LSADC0_ctrl;

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     reserved_0:14;
		unsigned int     jd_sbias:2;
		unsigned int     reserved_1:2;
		unsigned int     jd_adsbias:2;
		unsigned int     jd_dummy:2;
		unsigned int     reserved_2:1;
		unsigned int     jd_svr:1;
		unsigned int     reserved_3:3;
		unsigned int     jd_adcksel:1;
		unsigned int     reserved_4:3;
		unsigned int     jd_power:1;
	};
} ST_LSADC0_analog_ctrl;

typedef union
{
	unsigned int		regValue;
	struct
	{
		unsigned int     pad_active:1;
		unsigned int     reserved_0:7;
		unsigned int     pad_thred:8;
		unsigned int     pad_sw:4;
		unsigned int     reserved_1:3;
		unsigned int     pad_ctrl:1;
		unsigned int     reserved_2:2;
		unsigned int     adc_val:6;
	};
} ST_LSADC0_pad;

typedef union
{
	unsigned int		regValue;
	struct
	{
		unsigned int     irq_en:8;
		unsigned int     pad_cnt:4;
		unsigned int     adc_busy:1;
		unsigned int     reserved_0:2;
		unsigned int     pad_ctrl:5;
		unsigned int     reserved_1:10;
		unsigned int     pad1_status:1;
		unsigned int     pad0_status:1;
	};
} ST_LSADC0_status;


#else	// apply LITTLE_ENDIAN

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     enable:1;
		unsigned int     test_en:1;
		unsigned int     reserved_1:6;
		unsigned int     dout_test_in:8;
		unsigned int     reserved_0:4;
		unsigned int     debounce_cnt:4;
		unsigned int     sel_adc_ck:4;
		unsigned int     sel_wait:4;
	};
} ST_LSADC0_ctrl;

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     jd_power:1;
		unsigned int     reserved_4:3;
		unsigned int     jd_adcksel:1;
		unsigned int     reserved_3:3;
		unsigned int     jd_svr:1;
		unsigned int     reserved_2:1;
		unsigned int     jd_dummy:2;
		unsigned int     jd_adsbias:2;
		unsigned int     reserved_1:2;
		unsigned int     jd_sbias:2;
		unsigned int     reserved_0:14;
	};
} ST_LSADC0_analog_ctrl;

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     adc_val:6;
		unsigned int     reserved_2:2;
		unsigned int     pad_ctrl:1;
		unsigned int     reserved_1:3;
		unsigned int     pad_sw:4;
		unsigned int     pad_thred:8;
		unsigned int     reserved_0:7;
		unsigned int     pad_active:1;
	};
} ST_LSADC0_pad;

typedef union
{
	unsigned int		regValue;
	struct
	{
		unsigned int     pad0_status:1;
		unsigned int     pad1_status:1;
		unsigned int     reserved_1:10;
		unsigned int     pad_ctrl:5;
		unsigned int     reserved_0:2;
		unsigned int     adc_busy:1;
		unsigned int     pad_cnt:4;
		unsigned int     irq_en:8;
	};
} ST_LSADC0_status;



#endif

extern int lsadc_init(int index, int voltage_mode);
extern int lsdac_get(int index);

#ifdef __cplusplus
}
#endif

#endif//__RTD1295_LSADC_H_

