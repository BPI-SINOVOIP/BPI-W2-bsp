#ifndef DRIVERS_CLOCK_ADJUST_RTK_WIFI_H_
#define DRIVERS_CLOCK_ADJUST_RTK_WIFI_H_

#ifdef CONFIG_RTK_SDIO_CLK_ADJUST
extern void rtk_adjust_clock_for_wifi(unsigned int channel,unsigned int ch_offset, unsigned int bwmode);
#define PRI_CH_OFFSET_DONT_CARE		0
#define PRI_CH_OFFSET_LOWER		1
#define PRI_CH_OFFSET_UPPER		2

#define	CH_WIDTH_20	0
#define	CH_WIDTH_40	1
#define	CH_WIDTH_80	2

struct _sdio_clk_reg {
	unsigned int reg1a4;
	unsigned int reg1a8;
};

typedef struct _wifi_sdio_clk_tbl {
	int channel;
	unsigned char lower;
	unsigned char upper;
	struct _sdio_clk_reg map[2];
} wifi_sdio_clk_tbl;
#endif

#endif
