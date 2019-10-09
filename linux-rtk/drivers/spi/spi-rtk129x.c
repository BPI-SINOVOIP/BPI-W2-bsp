/*
 * Realtek SPI driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_bitbang.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/suspend.h>
#include <linux/clk.h>
#include <linux/reset.h>

#define SPI_CONTROL		0x0
	#define SPI_CLK_DIV(n)		((n)<<16)

#define SPI_CS_TIMING	0x4
	#define TCS_high(n)		(n<<16)
	#define TCS_end(n)		(n<<8)
	#define TCS_start(n)	(n<<0)
	#define DEFAULT_TIMING	(TCS_high(0)|TCS_end(0x10)|TCS_start(0))

#define SPI_AUX_CTRL	0x8
	#define CS0_EN			(1<<0)
	#define CS1_EN			(1<<1)
	#define MASTER_MODE_EN	(0<<8)
	#define SLAVE_MODE_EN	(1<<8)
	#define DEFAULT_AUX		(CS0_EN | MASTER_MODE_EN)

#define SPI_CMD_DUMMY	0xC
	#define INST_BIT_LEN(n)	(n<<16)

#define SPI_SO_CTRL		0x10
	#define READ_CMD		(0<<31)
	#define WRITE_CMD		(1<<31)
	#define ADDR_BIT_LEN(n)	(n<<22)
	#define DATA_BIT_LEN(n)	(n<<0)

#define SPI_SI_CTRL		0x14
	#define RD_BIT_LEN(n)	(n<<0)

#define SPI_W_FIFO		0x18
#define SPI_R_FIFO		0x1C
#define SPI_INST		0x20
#define SPI_ADDR		0X24

#define SPI_CTRL		0x28
	#define CMD_ENABLE		(1<<0)

#define SPI_INT			0x30
	#define CMD_DONE		(1<<0)


#define RTK_SPI_RXDATA	0
#define RTK_SPI_TXDATA	4
#define RTK_SPI_STATUS	8
#define RTK_SPI_CONTROL	12
#define RTK_SPI_SLAVE_SEL	20

#define RTK_SPI_STATUS_ROE_MSK	0x8
#define RTK_SPI_STATUS_TOE_MSK	0x10
#define RTK_SPI_STATUS_TMT_MSK	0x20
#define RTK_SPI_STATUS_TRDY_MSK	0x40
#define RTK_SPI_STATUS_RRDY_MSK	0x80
#define RTK_SPI_STATUS_E_MSK		0x100

#define RTK_SPI_CONTROL_IROE_MSK	0x8
#define RTK_SPI_CONTROL_ITOE_MSK	0x10
#define RTK_SPI_CONTROL_ITRDY_MSK	0x40
#define RTK_SPI_CONTROL_IRRDY_MSK	0x80
#define RTK_SPI_CONTROL_IE_MSK	0x100
#define RTK_SPI_CONTROL_SSO_MSK	0x400

#define RTK_SPI_DUMMY_LEN 0
#define RTK_SPI_MAX_WRITE_LEN 17
#define RTK_SPI_MAX_READ_LEN 16

#define RTK_SPI_BASE_CLK		256000000
#define RTK_SPI_MAX_CLK			 25600000	/* for RF4CE device */

static int cs_ctrl_gpio = -1;

#if 0
	#define RTK_SPI_DBG(args...) printk(args)
#else
	#define RTK_SPI_DBG(args...)
#endif

struct rtk_gspi_devstate {
	unsigned int	hz;
	u8		sck_div;
};

struct rtk_gspi {
	/* bitbang has to be first */
	struct spi_bitbang bitbang;
	struct completion done;

	void __iomem *base;
	int irq;
	int len;
	int count;
	int bytes_per_word;
	unsigned long imr;

	/* data buffers */
	const unsigned char *tx;
	unsigned char *rx;

	struct clk		*clk;
	struct spi_master	*master;
	struct spi_device	*curdev;
	struct device		*dev;
};

static inline struct rtk_gspi *rtk_gspi_to_hw(struct spi_device *sdev)
{
	return spi_master_get_devdata(sdev->master);
}


static void rtk_gspi_chipsel(struct spi_device *spi, int value)
{
	unsigned int cspol;
	cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;
	if (value == BITBANG_CS_INACTIVE)
		cspol = !cspol;

	RTK_SPI_DBG("chipsel(%d), set GPIO%d value(%u)\n", value, cs_ctrl_gpio, cspol);
	gpio_set_value(cs_ctrl_gpio, cspol);

}

static int rtk_gspi_update_state(struct spi_device *spi,
				    struct spi_transfer *t)
{
	struct rtk_gspi *hw = rtk_gspi_to_hw(spi);
	struct rtk_gspi_devstate *cs = spi->controller_state;
	unsigned int hz;
	unsigned int div;
	unsigned long clk;

	hz  = t ? t->speed_hz : spi->max_speed_hz;

	if (!hz)
		hz = spi->max_speed_hz;

	if (hz > RTK_SPI_MAX_CLK)
		hz = RTK_SPI_MAX_CLK;

	if (cs->hz != hz) {
		clk = RTK_SPI_BASE_CLK;
		div = DIV_ROUND_UP(clk, hz);

		RTK_SPI_DBG("temporary div = %d\n", div);
		if (div <= 4) {
			div = 4;
			cs->sck_div = 2;
		} else if (div == 5) {
			cs->sck_div = 0x11;
		} else if (div == 7) {
			cs->sck_div = 0x12;
		} else if (div <= 16) {
			div = ((div + 1) / 2) * 2;
			cs->sck_div = div / 2;
		} else if (div <= 20) {
			div = 20;
			cs->sck_div = 9;
		} else if (div <= 24) {
			div = 24;
			cs->sck_div = 0xa;
		} else if (div <= 48) {
			div = 48;
			cs->sck_div = 0xb;
		} else if (div <= 256) {
			div = 256;
			cs->sck_div = 0xc;
		} else if (div <= 512) {
			div = 512;
			cs->sck_div = 0xd;
		} else if (div <= 2048) {
			div = 2048;
			cs->sck_div = 0xe;
		} else {
			div = 2560;
			cs->sck_div = 0xf;
		}

		dev_dbg(&spi->dev, "pre-scaler=%d (wanted %d, got %ld)\n",
			div, hz, clk / div );

		RTK_SPI_DBG("old hz = %d, new hz = %d, clk = %d, div = %d, sck_div = %d\n", cs->hz, hz, clk, div, cs->sck_div);
		cs->hz = hz;
	}
	else
		return 1;

	return 0;
}

static int rtk_gspi_setupxfer(struct spi_device *spi, struct spi_transfer *t)
{
	struct rtk_gspi *hw = rtk_gspi_to_hw(spi);
	struct rtk_gspi_devstate *cs = spi->controller_state;

	if(!rtk_gspi_update_state(spi, t)) {
		writel(SPI_CLK_DIV(cs->sck_div) | BIT(8), hw->base + SPI_CONTROL);

		RTK_SPI_DBG("%s:%d: cs->sck_div = %d, SPI_CONTROL = 0x%x\n", __func__, __LINE__, cs->sck_div, readl(hw->base + SPI_CONTROL));
	}

	return 0;
}

static int rtk_gspi_setup(struct spi_device *spi)
{
	struct rtk_gspi *hw = rtk_gspi_to_hw(spi);
	struct rtk_gspi_devstate *cs = spi->controller_state;

	/* allocate settings on the first call */
	if (!cs) {
		cs = kzalloc(sizeof(struct rtk_gspi_devstate), GFP_KERNEL);
		if (!cs)
			return -ENOMEM;

		cs->hz = -1;
		spi->controller_state = cs;
	}

	/* initialise the state from the device */
	rtk_gspi_setupxfer(spi, NULL);

	//spin_lock(&hw->bitbang.lock);
	if (!hw->bitbang.busy) {
		hw->bitbang.chipselect(spi, BITBANG_CS_INACTIVE);
	}
	//spin_unlock(&hw->bitbang.lock);


	return 0;
}

static void rtk_gspi_cleanup(struct spi_device *spi)
{
	struct rtk_gspi_devstate *cs = spi->controller_state;
	if (cs) {
		kfree(cs);
	}
}

static void rtk_gspi_write(struct rtk_gspi *hw)
{
	unsigned int txd,temp,i,j;
	unsigned int write_len,data_byte_len,fifo_data_byte_len,offset=0;

	RTK_SPI_DBG("%s len(%u)\n", __func__,hw->len);

	write_len = hw->len;

	if((write_len<1) || (hw->tx==NULL))
		return;

	while(write_len)
	{
		if(write_len>=RTK_SPI_MAX_WRITE_LEN)
			data_byte_len = RTK_SPI_MAX_WRITE_LEN;
		else
			data_byte_len = write_len;

		fifo_data_byte_len = data_byte_len-1;

		if(data_byte_len==1)//Write FIFO can't be empty
		{
			writel((INST_BIT_LEN(0x4) | RTK_SPI_DUMMY_LEN), hw->base + SPI_CMD_DUMMY);//tr
			writel((ADDR_BIT_LEN(0x0) | WRITE_CMD | DATA_BIT_LEN(0x4)), hw->base + SPI_SO_CTRL);
			RTK_SPI_DBG("%s tx[%u] 0x%02x\n", __func__,offset,hw->tx[offset]);
			RTK_SPI_DBG("%s write 0x%08x to INST\n", __func__,hw->tx[offset]>>4);
			RTK_SPI_DBG("%s write 0x%08x to FIFO\n", __func__,hw->tx[offset]&0xF);
			writel((hw->tx[offset]>>4), hw->base + SPI_INST);//4  //4bit
			writel((hw->tx[offset]&0xF), hw->base + SPI_W_FIFO);//
		}
		else
		{
			writel((INST_BIT_LEN(0x8) | RTK_SPI_DUMMY_LEN), hw->base + SPI_CMD_DUMMY);//tr
			writel((ADDR_BIT_LEN(0x0) | WRITE_CMD | DATA_BIT_LEN(fifo_data_byte_len<<3)), hw->base + SPI_SO_CTRL);
			RTK_SPI_DBG("%s tx[%u] 0x%02x\n", __func__,offset,hw->tx[offset]);
			RTK_SPI_DBG("%s write 0x%08x to INST\n", __func__,hw->tx[offset]);
			writel(hw->tx[offset], hw->base + SPI_INST);//First byte
		}
		writel(RD_BIT_LEN(0x0), hw->base + SPI_SI_CTRL);//Note:read bit len cat't be 0x20

		//Write FIFO
		txd = 0;
		j=1;
		for(i=fifo_data_byte_len+offset; i>=offset+1; i--)
		{
			temp = hw->tx[i]<<(8*(j-1));
			txd = txd + temp;
			RTK_SPI_DBG("%s tx[%u] 0x%02x\n", __func__,i,hw->tx[i]);
			if(j==4)
			{
				RTK_SPI_DBG("%s write 0x%08x to FIFO\n", __func__,txd);
				writel(txd, hw->base + SPI_W_FIFO);
				txd = 0;
				j=1;
				continue;
			}
			else if(i==(offset+1))
			{
				RTK_SPI_DBG("%s write 0x%08x to FIFO\n", __func__,txd);
				writel(txd, hw->base + SPI_W_FIFO);
			}
			j++;
		}

		writel(0x100, hw->base + SPI_CTRL); // reset r/w fifo
		writel(CMD_ENABLE, hw->base + SPI_CTRL);

		while (!(readl(hw->base + SPI_INT) & CMD_DONE))
			cpu_relax();

		writel(CMD_DONE, hw->base + SPI_INT);// clear
		offset += RTK_SPI_MAX_WRITE_LEN;
		write_len = write_len - data_byte_len;
	}

	return;

}

static void rtk_gspi_read(struct rtk_gspi *hw)
{
	unsigned int rxd,i;
	unsigned int read_len,data_byte_len,offset=0;

	RTK_SPI_DBG("%s len(%u)\n", __func__,hw->len);

	read_len = hw->len;

	while(read_len)
	{
		if(read_len>=RTK_SPI_MAX_READ_LEN)
			data_byte_len = RTK_SPI_MAX_READ_LEN;
		else
			data_byte_len = read_len;

		writel((INST_BIT_LEN(0x0) | RTK_SPI_DUMMY_LEN), hw->base + SPI_CMD_DUMMY);//tr
		writel((ADDR_BIT_LEN(0x0) | READ_CMD), hw->base + SPI_SO_CTRL);
		writel(0x100, hw->base + SPI_CTRL); // reset r/w fifo
		writel(RD_BIT_LEN(data_byte_len<<3), hw->base + SPI_SI_CTRL);//Note:read bit len cat't be 0x20
		writel(CMD_ENABLE, hw->base + SPI_CTRL);
		RTK_SPI_DBG("%s READ CMD, read len(%u)\n", __func__,data_byte_len);
		while (!(readl(hw->base + SPI_INT) & CMD_DONE))
			cpu_relax();
		writel(CMD_DONE, hw->base + SPI_INT);

		//Read FIFO
		rxd = readl(hw->base + SPI_R_FIFO);
		RTK_SPI_DBG("%s read 0x%08x from FIFO\n", __func__,rxd);
		for(i=1; i<=data_byte_len; i++)
		{
			hw->rx[offset+data_byte_len-i] = rxd&0xff;
			RTK_SPI_DBG("%s rx[%u] 0x%02x\n", __func__,offset+data_byte_len-i,hw->rx[offset+data_byte_len-i]);
			rxd = rxd >>8;
			if(i%4==0&&(i<data_byte_len))
			{
				rxd = readl(hw->base + SPI_R_FIFO);
				RTK_SPI_DBG("%s read 0x%08x from FIFO\n", __func__,rxd);
			}
		}
		offset += RTK_SPI_MAX_READ_LEN;

		read_len = read_len - data_byte_len;
	}

	return;

}

static int rtk_gspi_txrx(struct spi_device *spi, struct spi_transfer *t)
{
	struct rtk_gspi *hw = rtk_gspi_to_hw(spi);
	struct spi_transfer *transfer;

	transfer = t;

	hw->tx = transfer->tx_buf;
	hw->rx = transfer->rx_buf;
	hw->len = transfer->len;

	if(hw->tx!=NULL)
		rtk_gspi_write(hw);
	else if(hw->rx!=NULL)
		rtk_gspi_read(hw);

	return hw->len;

}


static int rtk_gspi_probe(struct platform_device *pdev)
{
	struct rtk_gspi_platform_data *platp = pdev->dev.platform_data;
	struct rtk_gspi *hw;
	struct spi_master *master;
	struct clk *clk = clk_get(&pdev->dev, NULL);
	struct reset_control *rstc = reset_control_get(&pdev->dev, NULL);

	int err = -ENODEV;

	if (WARN_ON(!(pdev->dev.of_node)))
	{
		pr_err("[GSPI] Error: No node\n");
		return -err;
	}

	master = spi_alloc_master(&pdev->dev, sizeof(struct rtk_gspi));
	if (!master)
		return err;

	/* Enable clk and release reset module */
	reset_control_deassert(rstc);	// release reset
	clk_prepare_enable(clk);		// enable clk

	/* Setup the master default state. */
	//master->bus_num = pdev->id;
	master->bus_num = 0;
	master->num_chipselect = 16;
	master->mode_bits = SPI_MODE_0;
	master->setup = rtk_gspi_setup;
	master->cleanup = rtk_gspi_cleanup;
	//RTK_SPI_DBG("%s bus_num %d, #cs %d, mode 0x%x, pdev->id %d\n", __func__, master->bus_num, master->num_chipselect, master->mode_bits, pdev->id);

	hw = spi_master_get_devdata(master);
	platform_set_drvdata(pdev, hw);
	dev_set_drvdata(&pdev->dev, hw);

	/* Setup the state for the bitbang driver */
	hw->bitbang.master = spi_master_get(master);
	if (!hw->bitbang.master)
		return err;
	hw->bitbang.setup_transfer = rtk_gspi_setupxfer;
	hw->bitbang.chipselect = rtk_gspi_chipsel;
	hw->bitbang.txrx_bufs = rtk_gspi_txrx;

	/* Find and map resources */
	hw->base = of_iomap(pdev->dev.of_node, 0);
	if (!hw->base)
		goto exit_busy;
	writel(SPI_CLK_DIV(8) | BIT(8), hw->base + SPI_CONTROL);//Clock 15.43MHz, clk_div:16, phase adj
	writel(DEFAULT_TIMING,  hw->base + SPI_CS_TIMING);
	writel(DEFAULT_AUX,     hw->base + SPI_AUX_CTRL);

	/* store hw info */
	hw->clk = clk;

	/* Request gpio */
	cs_ctrl_gpio = of_get_named_gpio(pdev->dev.of_node, "spi-cs-gpio", 0);
	if (cs_ctrl_gpio < 0)
		pr_err("[GSPI][%s] could not get gpio from of ",__FUNCTION__);
	else
		pr_err("[GSPI] spi-cs-gpio(%d)\n",cs_ctrl_gpio);

	/* Find platform data */
	if (!platp)
		hw->bitbang.master->dev.of_node = pdev->dev.of_node;

	/* Register spi controller */
	err = spi_bitbang_start(&hw->bitbang);
	if (err)
		goto exit;
	dev_info(&pdev->dev, "base %p, irq %d\n", hw->base, hw->irq);

	return 0;

exit_busy:
	err = -EBUSY;
exit:
	dev_set_drvdata(&pdev->dev, NULL);
	platform_set_drvdata(pdev, NULL);
	spi_master_put(master);
	return err;
}

static int rtk_gspi_remove(struct platform_device *dev)
{
	struct rtk_gspi *hw = platform_get_drvdata(dev);
	struct spi_master *master = hw->bitbang.master;

	spi_bitbang_stop(&hw->bitbang);
	platform_set_drvdata(dev, NULL);
	dev_set_drvdata(&dev->dev, NULL);
	spi_master_put(master);
	return 0;
}

#ifdef CONFIG_PM

static int rtk_gspi_suspend(struct device *dev)
{
	//struct rtk_gspi *hw = dev_get_drvdata(dev);
	printk(KERN_ERR "[RTK_SPI] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RTK_SPI] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[RTK_SPI] %s Suspend mode\n", __func__);
	}

	printk(KERN_ERR "[RTK_SPI] Exit %s\n", __func__);

	return 0;
}

static int rtk_gspi_resume(struct device *dev)
{
	struct rtk_gspi *hw = dev_get_drvdata(dev);

	printk(KERN_ERR "[RTK_SPI] Enter %s\n", __func__);

	if(RTK_PM_STATE == PM_SUSPEND_STANDBY){
		//For idle mode
		printk(KERN_ERR "[RTK_SPI] %s Idle mode\n", __func__);
	}else{
		//For suspend mode
		printk(KERN_ERR "[RTK_SPI] %s Suspend mode\n", __func__);
	}


	writel(SPI_CLK_DIV(8) | BIT(8), hw->base + SPI_CONTROL);//Clock 15.43MHz, clk_div:16, phase adj
	writel(DEFAULT_TIMING,  hw->base + SPI_CS_TIMING);
	writel(DEFAULT_AUX,     hw->base + SPI_AUX_CTRL);

	printk(KERN_ERR "[RTK_SPI] Exit %s\n", __func__);

	return 0;
}

static const struct dev_pm_ops rtk_gspi_pm_ops = {
	.suspend		= rtk_gspi_suspend,
	.resume			= rtk_gspi_resume,
};

#define RTK_GSPI_PM_OPS	(&rtk_gspi_pm_ops)

#else /* !CONFIG_PM */
#define RTK_GSPI_PM_OPS	NULL
#endif /* !CONFIG_PM */

static const struct of_device_id rtk_gspi_match[] = {
	{ .compatible = "Realtek,rtk129x-spi", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_gspi_match);


static struct platform_driver rtk_gspi_driver = {
	.probe = rtk_gspi_probe,
	.remove = rtk_gspi_remove,
	.driver = {
		.name = "rtk-gspi",
		.owner = THIS_MODULE,
		.pm = RTK_GSPI_PM_OPS,
		.of_match_table = of_match_ptr(rtk_gspi_match),
	},
};
module_platform_driver(rtk_gspi_driver);

MODULE_DESCRIPTION("Realtek GSPI driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtk129x-gspi");

