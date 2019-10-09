/*
 * irq-rtd119x.h - RTK irq mux driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef IRQ_RTD119x_H_
#define IRQ_RTD119x_H_

#define IRQ_INMUX 32

enum misc_int_en {
	MISC_INT_FAIL = 0xFF,
	MISC_INT_RVD = 0xFE,
	MISC_INT_EN_GSPI = 27,
	MISC_INT_EN_I2C2 = 26,
	MISC_INT_EN_I2C3 = 23,
	MISC_INT_EN_LSADC = 21,
	MISC_INT_EN_GPIODA = 20,
	MISC_INT_EN_GPIOA = 19,
	MISC_INT_EN_I2C4 = 15,
	MISC_INT_EN_I2C5 = 14,
	MISC_INT_EN_RTC_DATE = 12,
	MISC_INT_EN_RTC_HOUR = 11,
	MISC_INT_EN_RTC_MIN = 10,
	MISC_INT_EN_UR1_TO = 5,
	MISC_INT_EN_I2C1 = 4,
	MISC_INT_EN_UR1 = 3,
};

enum iso_int_en {
	ISO_INT_FAIL = 0xFF,
	ISO_INT_RVD = 0xFE,
	ISO_INT_EN_CEC = 22,
	ISO_INT_EN_GPIODA = 20,
	ISO_INT_EN_GPIOA = 19,
	ISO_INT_EN_RTC_ALARM = 13,
	ISO_INT_EN_RTC_HSEC = 12,
	ISO_INT_EN_I2C6 = 10,
	ISO_INT_EN_I2C0 = 8,
	ISO_INT_EN_IRDA = 5,
	ISO_INT_EN_UR0 = 2,
};

unsigned char irq_map_tab[2][IRQ_INMUX] = {
	{
		MISC_INT_FAIL,          /* Bit0 */
		MISC_INT_FAIL,          /* Bit1 */
		MISC_INT_RVD,           /* Bit2 */
		MISC_INT_EN_UR1,        /* Bit3 */
		MISC_INT_EN_I2C1,       /* Bit4 */
		MISC_INT_EN_UR1_TO,     /* Bit5 */
		MISC_INT_RVD,           /* Bit6 */
		MISC_INT_RVD,           /* Bit7 */
		MISC_INT_FAIL,          /* Bit8 */
		MISC_INT_RVD,           /* Bit9 */
		MISC_INT_EN_RTC_MIN,    /* Bit10 */
		MISC_INT_EN_RTC_HOUR,   /* Bit11 */
		MISC_INT_EN_RTC_DATE,   /* Bit12 */
		MISC_INT_FAIL,          /* Bit13 */
		MISC_INT_EN_I2C5,       /* Bit14 */
		MISC_INT_EN_I2C4,       /* Bit15 */
		MISC_INT_FAIL,          /* Bit16 */
		MISC_INT_FAIL,          /* Bit17 */
		MISC_INT_FAIL,          /* Bit18 */
		MISC_INT_EN_GPIOA,      /* Bit19 */
		MISC_INT_EN_GPIODA,     /* Bit20 */
		MISC_INT_EN_LSADC,      /* Bit21 */
		MISC_INT_FAIL,          /* Bit22 */
		MISC_INT_EN_I2C3,       /* Bit23 */
		MISC_INT_FAIL,          /* Bit24 */
		MISC_INT_FAIL,          /* Bit25 */
		MISC_INT_EN_I2C2,       /* Bit26 */
		MISC_INT_EN_GSPI,       /* Bit27 */
		MISC_INT_FAIL,          /* Bit28 */
		MISC_INT_FAIL,          /* Bit29 */
		MISC_INT_FAIL,          /* Bit30 */
		MISC_INT_FAIL,          /* Bit31 */
	},
	{
                ISO_INT_FAIL,           /* Bit0 */
                ISO_INT_RVD,            /* Bit1 */
                ISO_INT_EN_UR0,         /* Bit2 */
                ISO_INT_FAIL,           /* Bit3 */
                ISO_INT_FAIL,           /* Bit4 */
                ISO_INT_EN_IRDA,        /* Bit5 */
                ISO_INT_FAIL,           /* Bit6 */
                ISO_INT_RVD,            /* Bit7 */
                ISO_INT_EN_I2C0,        /* Bit8 */
                ISO_INT_RVD,            /* Bit9 */
                ISO_INT_EN_I2C6,        /* Bit10 */
                ISO_INT_FAIL,           /* Bit11 */
                ISO_INT_EN_RTC_HSEC,    /* Bit12 */
                ISO_INT_EN_RTC_ALARM,   /* Bit13 */
                ISO_INT_RVD,            /* Bit14 */
                ISO_INT_RVD,            /* Bit15 */
                ISO_INT_RVD,            /* Bit16 */
                ISO_INT_RVD,            /* Bit17 */
                ISO_INT_RVD,            /* Bit18 */
                ISO_INT_EN_GPIOA,       /* Bit19 */
                ISO_INT_EN_GPIODA,      /* Bit20 */
                ISO_INT_FAIL,           /* Bit21 */
                ISO_INT_EN_CEC,         /* Bit22 */
                ISO_INT_FAIL,           /* Bit23 */
                ISO_INT_FAIL,           /* Bit24 */
                ISO_INT_FAIL,           /* Bit25 */
                ISO_INT_FAIL,           /* Bit26 */
                ISO_INT_FAIL,           /* Bit27 */
                ISO_INT_FAIL,           /* Bit28 */
                ISO_INT_FAIL,           /* Bit29 */
                ISO_INT_FAIL,           /* Bit30 */
                ISO_INT_FAIL,           /* Bit31 */
        }
};

#endif /* IRQ_RTD119x_H_ */
