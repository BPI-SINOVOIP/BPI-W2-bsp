/*
 * alc5680.c  --  ALC5680 SPI driver
 *
 * Copyright 2018 Realtek Semiconductor Corp.
 * Author: Oder Chiou <oder_chiou@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/input.h>
#include <linux/spi/spi.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/pm_qos.h>
#include <linux/sysfs.h>
#include <linux/clk.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>
#include <linux/i2c.h>
#include <linux/of_gpio.h>
#include <soc/realtek/rtk_regmap.h>

#define HELLO_BLUE_GENIE	0X03
#define ALEXA 			0X04
#define SESAMEE 		0X05
#define BAIDU 			0X76

#define ALC5680_SPI_REG_DRIVER_CTRL0    0x18009060
#define ALC5680_SPI_REG_DRIVER_CTRL1    0x18009064
#define REG_KEY_WORD_START              0x18009080

#define SILENCE_MODE_OUTRING_BASE       0x600008f8
#define SILENCE_MODE_OUTRING_LIMIT      0x600008fc
#define SILENCE_MODE_OUTRING_WP         0x60000908

#define ALC5680_SPI_DEVICE_ID           0x18008004
#define MUSIC_MODE_OUTRING_BASE         0x18006900
#define MUSIC_MODE_OUTRING_LIMIT        0x18006904
#define MUSIC_MODE_OUTRING_WP           0x1800690c

#define ALC5680_SPI_WOV_MUSIC_MODE   (0)
#define ALC5680_SPI_WOV_SILENCE_MODE (1)

#define REG_DSP_MUTE_STATE              0x1800C192
#define REG_DSP_VOICE_DIRECTION         0x180000C8


static unsigned char gpio_cs_pin;
static unsigned char gpio_reset_pin;
static unsigned short spi_bus_num = 0;
static struct spi_device *spi_device;

static unsigned int outring_base  = 0;
static unsigned int outring_limit = 0;
static unsigned int outring_wp    = 0;
static unsigned int outring_rp    = 0;

static unsigned int alc5680_spi_reg_dsp_connect = 0;
static unsigned int alc5680_spi_reg_vol_up = 0;
static unsigned int alc5680_spi_reg_vol_down = 0;
static unsigned int alc5680_spi_reg_dsp_mute = 0;

static uint8_t voice_led_position_01 = 0xFF;
static uint8_t voice_led_position_02 = 0xFF;

static void fl3236_set_led(uint8_t led_position_01, uint8_t  led_position_02, int on_ff);


static void convert_mic_position_to_led_position(int voice_direction) {

	if ( voice_direction > 0 && voice_direction <= 30 ) {
		voice_led_position_01 =  9;
		voice_led_position_02 =  8;
	} else if ( voice_direction > 30 && voice_direction <= 60 ) {
		voice_led_position_01 =  8;
		voice_led_position_02 =  7;
	} else if ( voice_direction > 60 && voice_direction <= 90 ) {
		voice_led_position_01 =  7;
		voice_led_position_02 =  6;
	} else if ( voice_direction > 90 && voice_direction <= 120 ) {
		voice_led_position_01 =  6;
		voice_led_position_02 =  5;
	} else if ( voice_direction > 120 && voice_direction <= 150 ) {
		voice_led_position_01 =  5;
		voice_led_position_02 =  4;
	} else if ( voice_direction > 150 && voice_direction <= 180 ) {
		voice_led_position_01 =  4;
		voice_led_position_02 =  3;
	} else if ( voice_direction >= -180 && voice_direction <= -150 ) {
		voice_led_position_01 =  3;
		voice_led_position_02 =  2;
	} else if ( voice_direction >= -150 && voice_direction <= -120 ) {
		voice_led_position_01 =  2;
		voice_led_position_02 =  1;
	} else if ( voice_direction >= -120 && voice_direction <= -90 ) {
		voice_led_position_01 =  1;
		voice_led_position_02 = 12;
	} else if ( voice_direction >= -90 && voice_direction <= -60 ) {
		voice_led_position_01 = 12;
		voice_led_position_02 = 11;
	} else if ( voice_direction >= -60 && voice_direction <= -30 ) {
		voice_led_position_01 = 11;
		voice_led_position_02 = 10;
	} else if ( voice_direction >= -30 && voice_direction <= -0 ) {
		voice_led_position_01 = 10;
		voice_led_position_02 =  9;
	} else {
		printk("unknown voice position:%d\r\n", voice_direction);
		voice_led_position_01 =  0xFF;
		voice_led_position_02 =  0xFF;
	}
}

/*****************************************************************************
 ****** below spi driver                                             *********           
 *****************************************************************************
 */


static unsigned int alc5680_spi_read32(struct spi_device *spi, unsigned int addr, 
					unsigned char cs_pin)
{
	struct spi_message	msg;
	struct spi_transfer	xfer[2];	 
	unsigned char 		tx_buf[9] = {0};
	unsigned char 		rx_buf[4];
	int			val;
	int			error = 0;

	spi_message_init(&msg);
	memset(xfer, 0, sizeof(xfer));
	
	xfer[0].tx_buf = tx_buf;
	xfer[0].rx_buf = NULL; 
	xfer[0].len = 9;
	spi_message_add_tail(&xfer[0], &msg);

	xfer[1].tx_buf = NULL; 
	xfer[1].rx_buf = rx_buf;
	xfer[1].len = 4;
	spi_message_add_tail(&xfer[1], &msg);

	tx_buf[0] = 0x02;
	tx_buf[1] = (addr >> 24) & 0xff;
	tx_buf[2] = (addr >> 16) & 0xff;
	tx_buf[3] = (addr >> 8) & 0xff;
	tx_buf[4] = addr & 0xff;

	gpio_set_value(cs_pin, 0);
	error = spi_sync(spi, &msg);
	gpio_set_value(cs_pin, 1);

	if (error) {
		pr_err("%s : spi_sync error !!!\n", __func__);
		return error;
	}

	val =  ((unsigned int)(rx_buf[0]) << 24) | ((unsigned int)(rx_buf[1]) << 16) |
		((unsigned int)(rx_buf[2]) << 8) | ((unsigned int)(rx_buf[3]) << 0) ;

	//pr_err("%s : spi_sync ok val=0x%x !!!\n", __func__, val);

	return val;
}

static int alc5680_spi_write32(struct spi_device *spi, unsigned int addr, 
					unsigned int val, unsigned char cs_pin)
{
	struct spi_message	msg;
	struct spi_transfer	xfer[1];	 
	unsigned char		tx_buf[10] = {0};
	int			error = 0;

	spi_message_init(&msg);
	memset(xfer, 0, sizeof(xfer));
	
	xfer[0].tx_buf = tx_buf;
	xfer[0].rx_buf = NULL; 
	xfer[0].len = 9;
	spi_message_add_tail(&xfer[0], &msg);

	tx_buf[0] = 0x03;
	tx_buf[1] = (addr >> 24) & 0xff;
	tx_buf[2] = (addr >> 16) & 0xff;
	tx_buf[3] = (addr >> 8) & 0xff;
	tx_buf[4] = addr & 0xff;
	tx_buf[5] = (val >> 24) & 0xff;
	tx_buf[6] = (val >> 16) & 0xff;
	tx_buf[7] = (val >> 8) & 0xff;
	tx_buf[8] = val & 0xff;	

	gpio_set_value(cs_pin, 0);
	error = spi_sync(spi, &msg);
	gpio_set_value(cs_pin, 1);

	if (error) {
		pr_err("%s : spi_sync error !!!\n", __func__);
	}

	return error;
}

static int alc5680_spi_burst_read(struct spi_device *spi, unsigned int addr, unsigned char *rx_buf,
					unsigned int len, unsigned char cs_pin)
{
	struct spi_message	msg;
	struct spi_transfer	xfer[2];	 
	unsigned char 		tx_buf[9] = {0};
	unsigned char 		tmp_buf[4];
	unsigned int 		len8 = len & 0xfffffff8;
	int 			i, error = 0;

	if (len8 == 0) { 
		return 0;
	}

	spi_message_init(&msg);
	memset(xfer, 0, sizeof(xfer));
	
	xfer[0].tx_buf = tx_buf;
	xfer[0].rx_buf = NULL; 
	xfer[0].len = 9;
	spi_message_add_tail(&xfer[0], &msg);

	xfer[1].tx_buf = NULL; 
	xfer[1].rx_buf = rx_buf;
	xfer[1].len = len8;
	spi_message_add_tail(&xfer[1], &msg);

	tx_buf[0] = 0x04;
	tx_buf[1] = (addr >> 24) & 0xff;
	tx_buf[2] = (addr >> 16) & 0xff;
	tx_buf[3] = (addr >> 8) & 0xff;
	tx_buf[4] = addr & 0xff;

	gpio_set_value(cs_pin, 0);
	error = spi_sync(spi, &msg);
	gpio_set_value(cs_pin, 1);

	if (error) {
		pr_err("%s : spi_sync error !!!\n", __func__);
		return error;
	}

	/* MSB ---> LSB */
	for (i = 0; i < len8; i += 8) {
		tmp_buf[0] = rx_buf[i + 0];
		tmp_buf[1] = rx_buf[i + 1];
		tmp_buf[2] = rx_buf[i + 2];
		tmp_buf[3] = rx_buf[i + 3];
		rx_buf[i + 0] = rx_buf[i + 7];
		rx_buf[i + 1] = rx_buf[i + 6];
		rx_buf[i + 2] = rx_buf[i + 5];
		rx_buf[i + 3] = rx_buf[i + 4];
		rx_buf[i + 4] = tmp_buf[3];
		rx_buf[i + 5] = tmp_buf[2];
		rx_buf[i + 6] = tmp_buf[1];
		rx_buf[i + 7] = tmp_buf[0];

	}  
	
	return len8;
}

static unsigned char alc5680_spi_get_wov_mode(struct spi_device *spi_device,  unsigned char cs_pin)
{
	unsigned int value;
	
	value = alc5680_spi_read32(spi_device, ALC5680_SPI_REG_DRIVER_CTRL1, cs_pin);
	
	return (value & 0x01) ? 1 : 0;
}

static void alc5680_spi_set_wov_mode(struct spi_device *spi_device, unsigned char wov_mode, unsigned char cs_pin)
{

	unsigned int value;
	value = alc5680_spi_read32(spi_device, ALC5680_SPI_REG_DRIVER_CTRL1, cs_pin);

	if (wov_mode == ALC5680_SPI_WOV_SILENCE_MODE) {
	
		alc5680_spi_write32(spi_device, ALC5680_SPI_REG_DRIVER_CTRL1, value |  0x00000001, cs_pin);
		outring_base  = alc5680_spi_read32(spi_device, SILENCE_MODE_OUTRING_BASE, cs_pin);
		outring_limit = alc5680_spi_read32(spi_device, SILENCE_MODE_OUTRING_LIMIT, cs_pin);
		outring_wp    = alc5680_spi_read32(spi_device, SILENCE_MODE_OUTRING_WP, cs_pin);

	} else if (wov_mode == ALC5680_SPI_WOV_MUSIC_MODE) {

		alc5680_spi_write32(spi_device, ALC5680_SPI_REG_DRIVER_CTRL1, value & ~0x00000001, cs_pin);
		outring_base  = alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_BASE, cs_pin);
		outring_limit = alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_LIMIT, cs_pin);
		outring_wp    = alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_WP, cs_pin);

    }
	
	outring_limit = ((outring_limit >> 2) + 1) << 2;

	pr_info("outring: %08X ~ %08X\r\n", outring_base, outring_limit);

	outring_rp = outring_wp;
		
}

static void alc5680_spi_clear_button_states(struct spi_device *spi_device, unsigned char cs_pin)
{
	alc5680_spi_write32(spi_device, alc5680_spi_reg_dsp_connect, 0, cs_pin);
	alc5680_spi_write32(spi_device, alc5680_spi_reg_vol_up, 0, cs_pin);
    alc5680_spi_write32(spi_device, alc5680_spi_reg_vol_down, 0, cs_pin);
    alc5680_spi_write32(spi_device, alc5680_spi_reg_dsp_mute, 0, cs_pin);

}

static unsigned char alc5680_spi_get_mute_state(struct spi_device *spi_device, unsigned char cs_pin)
{
	unsigned char value;

	value = alc5680_spi_read32(spi_device, REG_DSP_MUTE_STATE, cs_pin);
	if (value & 0x00000200) {
		return 1;
	}else {
		return 0;
	}
}

static unsigned int alc5680_spi_get_outring_size(void)
{
	if (outring_limit > outring_base + 4) {
		return outring_limit - outring_base;
	}else {
		return 0;
	}
}

static unsigned int alc5680_spi_fetch_data_dma(struct spi_device *spi_device, unsigned char *buf, unsigned int bufsize, unsigned char cs_pin)
{
	unsigned int idx = 0;
	unsigned int value;
	unsigned int desire_len;
	unsigned int read_len = 0, read_len2 = 0;
	unsigned int target_wp;

	do {
		if (bufsize < 4) 
			break;
	
		outring_wp = alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_WP, cs_pin);
		target_wp = outring_wp;
	
		if (outring_rp == target_wp)
			break;
	
		// Burst read need 8 byte alignment, so we make rp 8 byte alignment
		if (outring_rp & 0x00000004 != 0) {
			value = alc5680_spi_read32(spi_device, outring_rp, cs_pin);
	
			// NOTICE: PCM data is LSB, not MSB
			buf[idx]   = (value & 0x000000FF) >>  0;
			buf[idx+1] = (value & 0x0000FF00) >>  8;
			buf[idx+2] = (value & 0x00FF0000) >> 16;
			buf[idx+3] = (value & 0xFF000000) >> 24;
	
			idx += 4;
			outring_rp += 4;
			if (outring_rp >= outring_limit) 
				outring_rp = outring_base;
			bufsize -= 4;
		}
	
		if (outring_rp == target_wp) 
			break;
		
		if (bufsize < 8) 
			break;
	
		if (outring_rp < target_wp) {
			desire_len = (bufsize > (target_wp - outring_rp)) ? (target_wp - outring_rp) : bufsize;
			read_len = alc5680_spi_burst_read(spi_device, outring_rp, buf + idx, desire_len, cs_pin);
			idx += read_len;
			outring_rp += read_len;
			if (outring_rp >= outring_limit) {
				outring_rp = outring_base;
			}	
		} else {
			desire_len = (bufsize > (outring_limit - outring_rp)) ? (outring_limit - outring_rp) : bufsize;
			read_len = alc5680_spi_burst_read(spi_device, outring_rp, buf + idx, desire_len, cs_pin);
			idx += read_len;
			bufsize -= read_len;
			outring_rp = outring_base;
		
			if (bufsize > 0) {
				desire_len = (bufsize > (target_wp - outring_rp)) ? (target_wp - outring_rp) : bufsize;
				read_len = alc5680_spi_burst_read(spi_device, outring_rp, buf + idx, desire_len, cs_pin);
				idx += read_len;
				outring_rp += read_len;
				if (outring_rp >= outring_limit) {
					outring_rp = outring_base;
				}
			}
		}
	} while (0);
	
	return idx;
}			

static int alc5680_spi_get_voice_direction(struct spi_device *spi_device, unsigned char cs_pin)
{
	int direction_sign, direction_exponent, direction_transformed;
	int direction_mantisse1, direction_mantisse2;
	unsigned int value = alc5680_spi_read32(spi_device, REG_DSP_VOICE_DIRECTION, cs_pin);
	
	/*
	 * The value of direction is hexadecimal floating point.
	 * We need to transform it to decimal.
	 */
	
	/* Check the sign bit */
	if ((value >> 31) == 0)
		direction_sign = 1;
	else
		direction_sign = -1;
	
	/* Extract the exponent value */
	value = value & 0x7FFFFFFF;
	direction_exponent = (value >> 23);
	
	/* Extract the mantisse value */
	value = value & 0x7FFFFF;
	direction_mantisse1 = (value >> 19);
	
	value = value & 0x7FFFF;
	direction_mantisse2 = (value >> 15);
	
	/*
	 * We didn't support floating point computation.
	 * The approximate value of direction can be computed by
	 * multiplying all value before divisor.
	 */	
	direction_transformed = direction_sign * ((256 + direction_mantisse1*16 + direction_mantisse2) * (1<<(direction_exponent-127))) / 256;

	return direction_transformed;
}

static void alc5680_spi_init_btn_reg(struct spi_device *spi_device, unsigned char cs_pin) 
{
	unsigned int addr;
	
	addr = alc5680_spi_read32(spi_device, 0x180000D8, cs_pin);
	alc5680_spi_reg_vol_up = addr;
	alc5680_spi_reg_vol_down = addr + 0x04;
	alc5680_spi_reg_dsp_connect = addr + 0x08;
	alc5680_spi_reg_dsp_mute = addr + 0x0C;
}
/*****************************************************************************
 ****** below alsa driver                                            *********           
 *****************************************************************************
 */
struct alc5680_dsp {
	struct device *dev;
	struct spi_device *spi_dev;
	struct delayed_work copy_work;
	struct mutex dma_lock;
	struct snd_pcm_substream *substream;
	unsigned int buf_base, buf_limit, buf_rp;
	size_t buf_size;
	size_t dma_offset;
	//size_t dsp_offset;
};

static const struct snd_pcm_hardware alc5680_spi_pcm_hardware = {
	.info                   = SNDRV_PCM_INFO_MMAP |
							SNDRV_PCM_INFO_MMAP_VALID |
							SNDRV_PCM_INFO_INTERLEAVED,
	.formats                = SNDRV_PCM_FMTBIT_S16_LE,
	.rates					= SNDRV_PCM_RATE_16000,
	.rate_min				= 16000,
	.rate_max 				= 16000,
	.period_bytes_min       = 64,
	.period_bytes_max       = 1024*256,
	.periods_min            = 32,
	.periods_max            = 1024,
	.channels_min           = 1,
	.channels_max           = 1,
	.buffer_bytes_max       = 1024*256,
};

static void alc5680_spi_copy_work(struct work_struct *work)
{
	struct alc5680_dsp *alc5680_dsp =
			container_of(work, struct alc5680_dsp, copy_work.work);
	struct snd_pcm_runtime *runtime;
	size_t period_bytes, truncated_bytes = 0;
	
	mutex_lock(&alc5680_dsp->dma_lock);
	if (!alc5680_dsp->substream) {
		dev_err(alc5680_dsp->dev, "No pcm substream\n");
		goto done;
	}
	
	runtime = alc5680_dsp->substream->runtime;
	
	period_bytes = snd_pcm_lib_period_bytes(alc5680_dsp->substream);
	if ((alc5680_dsp->dma_offset + period_bytes) >= runtime->dma_bytes)
		alc5680_dsp->dma_offset = 0;
	
	outring_wp   = alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_WP, gpio_cs_pin);
	
	if (alc5680_dsp->buf_rp + period_bytes <= alc5680_dsp->buf_limit) {
		
		if ((alc5680_dsp->buf_rp + period_bytes > outring_wp) && (alc5680_dsp->buf_rp < outring_wp))
			period_bytes = outring_wp - alc5680_dsp->buf_rp;
	
		alc5680_spi_burst_read(alc5680_dsp->spi_dev, alc5680_dsp->buf_rp,
				runtime->dma_area + alc5680_dsp->dma_offset,
				period_bytes, gpio_cs_pin);

		if (alc5680_dsp->buf_rp + period_bytes == alc5680_dsp->buf_limit)
				alc5680_dsp->buf_rp = alc5680_dsp->buf_base;
		else
				alc5680_dsp->buf_rp += period_bytes;
	} else {		
		 if ((alc5680_dsp->buf_rp < outring_wp) && (alc5680_dsp->buf_limit > outring_wp)) {
			period_bytes = outring_wp -  alc5680_dsp->buf_rp;

			alc5680_spi_burst_read(alc5680_dsp->spi_dev, alc5680_dsp->buf_rp,
				runtime->dma_area + alc5680_dsp->dma_offset,
				period_bytes, gpio_cs_pin);
				
			alc5680_dsp->buf_rp += period_bytes;
		}
		else {			
			truncated_bytes = alc5680_dsp->buf_limit - alc5680_dsp->buf_rp;
			
			if (outring_wp < (alc5680_dsp->buf_base + period_bytes - truncated_bytes))
				period_bytes = outring_wp - alc5680_dsp->buf_base + truncated_bytes;
			
			alc5680_spi_burst_read(alc5680_dsp->spi_dev, alc5680_dsp->buf_rp,
					runtime->dma_area + alc5680_dsp->dma_offset,
					truncated_bytes, gpio_cs_pin);
					
			alc5680_spi_burst_read(alc5680_dsp->spi_dev, alc5680_dsp->buf_base,
					runtime->dma_area + alc5680_dsp->dma_offset +
					truncated_bytes, period_bytes - truncated_bytes, gpio_cs_pin);
	
			alc5680_dsp->buf_rp = alc5680_dsp->buf_base +
					period_bytes - truncated_bytes;
		}
	}
	
	alc5680_dsp->dma_offset += period_bytes;
	
	//alc5680_dsp->dsp_offset += period_bytes;
	
	snd_pcm_period_elapsed(alc5680_dsp->substream);
	
	//if (alc5680_dsp->dsp_offset < alc5680_dsp->buf_size)
	schedule_delayed_work(&alc5680_dsp->copy_work, 4);

done:
	mutex_unlock(&alc5680_dsp->dma_lock);

}

static int alc5680_spi_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	//runtime->hw = alc5680_spi_pcm_hardware; 
	memcpy(&runtime->hw, &alc5680_spi_pcm_hardware, sizeof(struct snd_pcm_hardware));

	return 0;
}

static int alc5680_spi_pcm_close(struct snd_pcm_substream *substream)
{

	return 0;
}

static int alc5680_spi_hw_params(struct snd_pcm_substream *substream,
                               struct snd_pcm_hw_params *hw_params)
{
	struct alc5680_dsp *alc5680_dsp = snd_pcm_substream_chip(substream);
	int ret;

	mutex_lock(&alc5680_dsp->dma_lock);
	ret = snd_pcm_lib_alloc_vmalloc_buffer(substream,
					params_buffer_bytes(hw_params));
	alc5680_dsp->substream = substream;
	mutex_unlock(&alc5680_dsp->dma_lock);
	
	return ret;
}

static int alc5680_spi_hw_free(struct snd_pcm_substream *substream)
{
	struct alc5680_dsp *alc5680_dsp = snd_pcm_substream_chip(substream);
	int i;
	
	cancel_delayed_work_sync(&alc5680_dsp->copy_work);

	mutex_lock(&alc5680_dsp->dma_lock);
	alc5680_dsp->substream = NULL;
	mutex_unlock(&alc5680_dsp->dma_lock);
	
	/* all LED off */
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 0);
	
	return snd_pcm_lib_free_vmalloc_buffer(substream);
}

static int alc5680_spi_prepare(struct snd_pcm_substream *substream)
{
	struct alc5680_dsp *alc5680_dsp = snd_pcm_substream_chip(substream);

	alc5680_dsp->dma_offset = 0;
	//alc5680_dsp->dsp_offset = 0;
	
	/**
	* The address area x1800XXXX is the register address, and it cannot
	* support spi burst read perfectly. So we use the spi burst read
	* individually to make sure the data correctly.
	*/

	alc5680_dsp->buf_base	= alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_BASE, gpio_cs_pin);
	alc5680_dsp->buf_limit	= alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_LIMIT, gpio_cs_pin) + 0x2;
	alc5680_dsp->buf_rp	= alc5680_spi_read32(spi_device, MUSIC_MODE_OUTRING_WP, gpio_cs_pin);

	return 0;
}


static int alc5680_spi_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct alc5680_dsp *alc5680_dsp = snd_pcm_substream_chip(substream);
	int i;
	
	if (cmd == SNDRV_PCM_TRIGGER_START) {
		if (alc5680_dsp->buf_base && alc5680_dsp->buf_limit &&
			alc5680_dsp->buf_rp){

			/* all LED off */
			for (i = 1; i < 12 ; i++)
				fl3236_set_led(i, i+1, 0);

			/* Get the voice direction and show the light*/
			convert_mic_position_to_led_position(alc5680_spi_get_voice_direction(alc5680_dsp->spi_dev, gpio_cs_pin));
			fl3236_set_led(voice_led_position_01, voice_led_position_02, 1);

			schedule_delayed_work(&alc5680_dsp->copy_work, 0);
		}
	}
	
	return 0;
}

static snd_pcm_uframes_t alc5680_spi_pcm_pointer(
                struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct alc5680_dsp *alc5680_dsp = snd_pcm_substream_chip(substream);

	return bytes_to_frames(runtime, alc5680_dsp->dma_offset);
}

static int alc5680_spi_pcm_ioctl(struct snd_pcm_substream *substream,  unsigned int cmd, void *arg)
{
	printk("%s %d cmd %x\n",__func__, __LINE__, cmd);

	switch (cmd) 
    {
		case SNDRV_PCM_IOCTL_HW_REFINE:
			printk("%s %d cmd %x\n",__func__, __LINE__, cmd);
			return 0;
		case SNDRV_PCM_IOCTL_HW_PARAMS:
			printk("%s %d cmd %x\n",__func__, __LINE__, cmd);
			return 0;
        default:
			printk("%s %d cmd %x\n",__func__, __LINE__, cmd);
            return snd_pcm_lib_ioctl(substream, cmd, arg);
            break; 
    }

    return 0;
}


static const struct snd_pcm_ops alc5680_capture_ops = {
	.open		 = alc5680_spi_pcm_open,
	.close		 = alc5680_spi_pcm_close,
	.ioctl		 = alc5680_spi_pcm_ioctl,
	.hw_params	 = alc5680_spi_hw_params,
	.hw_free	 = alc5680_spi_hw_free,
	.prepare	 = alc5680_spi_prepare,
	.trigger	 = alc5680_spi_trigger,
	.pointer	 = alc5680_spi_pcm_pointer,
	.mmap		 = snd_pcm_lib_mmap_vmalloc,
	.page		 = snd_pcm_lib_get_vmalloc_page,
};

static int alc5680_spi_probe(struct spi_device *spi_device)
{
	struct snd_card		*card;
	struct snd_pcm 		*pcm;
	struct alc5680_dsp 	*alc5680_dsp;
	unsigned int value;
	int retval;

	/* create alsa device & driver */
	retval = snd_card_new(&spi_device->dev, -1, "snd_card_alc5680", THIS_MODULE,
                              sizeof(struct alc5680_dsp), &card);
	if (retval < 0) {
		pr_err("%s , snd_card_new error\n", __func__);
		goto out;
	}

	retval = snd_pcm_new(card, "snd_alc5680",
                        0, 0, 1, &pcm);
	if (retval < 0) {
		pr_err("%s , snd_pcm_new error\n", __func__);
		goto out;
	}

	strcpy(pcm->name, "alc5680");
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &alc5680_capture_ops);	
	
	alc5680_dsp = devm_kzalloc(&spi_device->dev, sizeof(struct alc5680_dsp),
                        GFP_KERNEL);

	pcm->private_data = alc5680_dsp;

	alc5680_dsp->dev = &spi_device->dev;
	alc5680_dsp->spi_dev = spi_device;

	mutex_init(&alc5680_dsp->dma_lock);
	INIT_DELAYED_WORK(&alc5680_dsp->copy_work, alc5680_spi_copy_work);
	spi_set_drvdata(spi_device, alc5680_dsp);
	
	retval = snd_card_register(card);
	if (retval < 0) {
		pr_err("%s , snd_card_register error\n", __func__);
		goto out;
	}

	/* Check the device id */
	value = alc5680_spi_read32(spi_device, ALC5680_SPI_DEVICE_ID, gpio_cs_pin);
	pr_info("%s device id is 0x%x\n",__func__, value);
	
	/* doing something init */	
	alc5680_spi_set_wov_mode(spi_device, ALC5680_SPI_WOV_MUSIC_MODE, gpio_cs_pin );
	alc5680_spi_clear_button_states(spi_device, gpio_cs_pin);	
	alc5680_spi_init_btn_reg(spi_device, gpio_cs_pin);

	/* doing this for what ??? */
	value = alc5680_spi_read32(spi_device, 0x18008208, gpio_cs_pin);
	value = value | 0x200000;
	alc5680_spi_write32(spi_device, 0x18008208, value, gpio_cs_pin);

	if (outring_base == 0xDEADBEEF || outring_limit - outring_base <= 4) {
        retval = -EIO;
	}	

out:
	return retval;

}

static int alc5680_spi_remove(struct spi_device *spi_device)
{

	return 0;
}

static struct spi_board_info alc5680_info = {
	.modalias       = "alc5680",
	.chip_select	= 0,
	.max_speed_hz  	= 2*1000*1000,
	.mode 		= SPI_MODE_0,	
};


static struct spi_driver alc5680_spi_driver = {
	.driver			= {
		.name  	= "alc5680",
		.owner 	= THIS_MODULE,
	},
	.probe       	= alc5680_spi_probe,
	.remove       	= alc5680_spi_remove,
};

/*****************************************************************************
******* below i2c driver                                            *********           
******************************************************************************
*/

struct alc5680_priv {

	struct regmap *regmap;
};

static const struct regmap_config alc5680_regmap = {
	.reg_bits = 16,
	.val_bits = 16,
	.max_register = 0xffff,
};

static void alc5680_i2c_write_32(struct alc5680_priv *alc5680, u32 reg, u32 val)
{

	regmap_write(alc5680->regmap, 0x0001, reg & 0xffff);
	regmap_write(alc5680->regmap, 0x0002, reg >> 16);
	regmap_write(alc5680->regmap, 0x0003, val & 0xffff);
	regmap_write(alc5680->regmap, 0x0004, val >> 16);
	regmap_write(alc5680->regmap, 0x0000, 0x0003);

}

static void alc5680_i2c_write_16(struct alc5680_priv *alc5680, u32 reg, u16 val)
{

	regmap_write(alc5680->regmap, 0x0001, reg & 0xffff);
	regmap_write(alc5680->regmap, 0x0002, reg >> 16);
	regmap_write(alc5680->regmap, 0x0003, val & 0xffff);
	regmap_write(alc5680->regmap, 0x0000, 0x0001);

}

static void alc5680_i2c_read_32(struct alc5680_priv *alc5680, u32 reg, u32 *val)
{
	u16 buf[2];

	regmap_write(alc5680->regmap, 0x0001, reg & 0xffff);
	regmap_write(alc5680->regmap, 0x0002, reg >> 16);
	regmap_write(alc5680->regmap, 0x0000, 0x0002);
	regmap_read(alc5680->regmap, 0x0003, &buf[0]); 
	regmap_read(alc5680->regmap, 0x0004, &buf[1]);
	*val = 	buf[1] << 16 | buf[0]; 
}

static void alc5680_i2c_read_16(struct alc5680_priv *alc5680, u32 reg, u16 *val)
{
	regmap_write(alc5680->regmap, 0x0001, reg & 0xffff);
	regmap_write(alc5680->regmap, 0x0002, reg >> 16);
	regmap_write(alc5680->regmap, 0x0000, 0x0002);
	regmap_read(alc5680->regmap, 0x0003, val); 
}


static int alc5680_get_version(struct alc5680_priv *alc5680)
{	
	unsigned int value = 0;

	alc5680_i2c_read_32(alc5680, 0x7000A004, &value);
      	value = value>>24;

	if(value == HELLO_BLUE_GENIE )
		pr_info("VERSION:HELLO_BLUE_GENIE\n");
	else if(value == ALEXA)
		pr_info("VERSION:ALEXA\n");
	else if(value == SESAMEE)
		pr_info("VERSION:Zhima kaimen\n");
	else if(value == BAIDU)
		pr_info("VERSION:Xiao du xiao du\n");
	else
		pr_info("NON-DEFINE VERSION ADDR=0X7000A004 %x\n",value);
	
	return value;

}

static void alc5680_set_volume(struct alc5680_priv *alc5680, unsigned char left, unsigned char right)
{
	alc5680_i2c_write_16(alc5680, 0x1800C02C, left<<8|right);
}

static void alc5680_get_volume(struct alc5680_priv *alc5680, unsigned short *value)
{
	alc5680_i2c_read_16(alc5680, 0x1800C02C, value);
}

static int alc5680_i2c_probe(struct i2c_client *i2c,
                             const struct i2c_device_id *id)
{
	struct alc5680_priv *alc5680;
	int i, ret;

	pr_info("%s id->name =%s i2c->name=%s i2c->addr=0x%x \n", __func__, id->name, i2c->name, i2c->addr);
	alc5680 = devm_kzalloc(&i2c->dev, sizeof(struct alc5680_priv),
                               GFP_KERNEL);
	if (alc5680 == NULL)
		return -ENOMEM;
	alc5680->regmap = devm_rtk_regmap_i2c_init(&i2c->dev, i2c, &alc5680_regmap);

	if (IS_ERR(alc5680->regmap))
		return PTR_ERR(alc5680->regmap);

	alc5680_get_version(alc5680);
	alc5680_set_volume(alc5680, 200, 200);
	return 0;
}

static int alc5680_i2c_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id alc5680_i2c_id[] = {
	{ "rtk,alc5680", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, alc5680_i2c_id);

static const struct of_device_id alc5680_of_id[] = {
	{ .compatible = "rtk,alc5680", },
	{ /* senitel */ }
};
MODULE_DEVICE_TABLE(of, alc5680_of_id);


static struct i2c_driver alc5680_i2c_driver = {
	.driver = {
		.name = "rtk,alc5680",
		.owner = THIS_MODULE,
		.of_match_table = alc5680_of_id,
	},
	.probe =    alc5680_i2c_probe,
	.remove =   alc5680_i2c_remove,
	.id_table = alc5680_i2c_id,
};

/*****************************************************************************
******* below fl3236 led i2c driver                                  *********           
******************************************************************************
*/
struct fl3236_priv {

	struct regmap *regmap;
};


struct fl3236_priv *fl3236;


static const struct regmap_config fl3236_regmap = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0xffff,
};

static void fl3236_set_led(uint8_t led_position_01, uint8_t  led_position_02, int on_off)
{
	/* pwm luminous intensity */
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3 + 1, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3 + 1, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_01-1)*3 + 2, 0x80);
	regmap_write(fl3236->regmap, 0x01+(led_position_02-1)*3 + 2, 0x80);

	/* LED Control */
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3 + 1, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3 + 1, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_01-1)*3 + 2, on_off);
	regmap_write(fl3236->regmap, 0x26+(led_position_02-1)*3 + 2, on_off);

	/* pwm Update */
	regmap_write(fl3236->regmap, 0x25, 0);
}

static int fl3236_i2c_probe(struct i2c_client *i2c,
                             const struct i2c_device_id *id)
{
	int i, ret;

	pr_err("%s id->name =%s i2c->name=%s i2c->addr=0x%x \n", __func__, id->name, i2c->name, i2c->addr);
	fl3236 = devm_kzalloc(&i2c->dev, sizeof(struct fl3236_priv),
						GFP_KERNEL);
	if (fl3236 == NULL)
		return -ENOMEM;

	fl3236->regmap = devm_rtk_regmap_i2c_init(&i2c->dev, i2c, &fl3236_regmap);

	if (IS_ERR(fl3236->regmap))
		return PTR_ERR(fl3236->regmap);

	/* Reset */
	regmap_write(fl3236->regmap, 0x4f, 0);

	/* Normal operation */
	regmap_write(fl3236->regmap, 0x00, 1);

	/* all LED on */
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 1);
	
	mdelay(1000);
	
	for (i = 1; i < 12 ; i++)
		fl3236_set_led(i, i+1, 0);

	return 0;
}

static const struct i2c_device_id fl3236_i2c_id[] = {
	{ "rtk,fl3236", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, fl3236_i2c_id);

static const struct of_device_id fl3236_of_id[] = {
	{ .compatible = "rtk,fl3236", },
	{ /* senitel */ }
};
MODULE_DEVICE_TABLE(of, fl3236_of_id);


static struct i2c_driver fl3236_i2c_driver = {
	.driver = {
		.name = "rtk,fl3236",
		.owner = THIS_MODULE,
		.of_match_table = fl3236_of_id,
	},
	.probe =    fl3236_i2c_probe,
//	.remove =   fl3236_i2c_remove,
	.id_table = fl3236_i2c_id,
};

/*****************************************************************************
******* below  alc5640 i2c driver                                    *********           
******************************************************************************
*/
struct alc5640_priv {

	struct regmap *regmap;
};


struct alc5640_priv *alc5640;

static const struct regmap_config alc5640_regmap = {
	.reg_bits = 8,
	.val_bits = 16,
	.max_register = 0xff,
};

static const struct reg_default alc5640_reg_defaults[] = {
	{ .reg = 0x00, .def = 0x0000, },
	{ .reg = 0xfa, .def = 0x0801, },
	{ .reg = 0x81, .def = 0x0f06, },
	{ .reg = 0x82, .def = 0x0800, },
	{ .reg = 0x63, .def = 0xf818, },
	{ .reg = 0x61, .def = 0x9800, },
	{ .reg = 0x64, .def = 0x0200, },
	{ .reg = 0x03, .def = 0x4848, },
	{ .reg = 0x2a, .def = 0x1414, },
	{ .reg = 0x45, .def = 0x6000, },
	{ .reg = 0x53, .def = 0x3000, },
	{ .reg = 0x70, .def = 0x8008, },
	{ .reg = 0x73, .def = 0x0110, },
	{ .reg = 0x80, .def = 0x5000, },
	{ .reg = 0x8e, .def = 0x0019, },
	{ .reg = 0x8f, .def = 0x3100, },
	{ .reg = 0x91, .def = 0x0f00, },
	{ .reg = 0x6a, .def = 0x003d, },
	{ .reg = 0x6c, .def = 0x2600, },
	{ .reg = 0x48, .def = 0x3800, },
	{ .reg = 0x49, .def = 0x1800, },
	{ .reg = 0x01, .def = 0x4848, },
	{ .reg = 0x61, .def = 0x9801, },
	{ .reg = 0xbb, .def = 0x8308, },
	{ .reg = 0x4a, .def = 0x0000, },
	
};

static int alc5640_i2c_probe(struct i2c_client *i2c,
                             const struct i2c_device_id *id)
{
	int i, ret;
	void __iomem	*pad_mux;
	
	pr_err("%s id->name =%s i2c->name=%s i2c->addr=0x%x \n", __func__, id->name, i2c->name, i2c->addr);
	alc5640 = devm_kzalloc(&i2c->dev, sizeof(struct alc5640_priv),
						GFP_KERNEL);
	if (fl3236 == NULL)
		return -ENOMEM;
	
	alc5640->regmap = devm_rtk_regmap_i2c_init(&i2c->dev, i2c, &alc5640_regmap);
	
	if (IS_ERR(alc5640->regmap))
		return PTR_ERR(alc5640->regmap);
	
	/* Set the padmux before doing setting */
	pad_mux = ioremap(0x9804d008, 0x120);
	writel(0x281540, pad_mux);
	
	/* init */
	for (i = 0;  i < 25;  i++) {
		regmap_write(alc5640->regmap, alc5640_reg_defaults[i].reg, alc5640_reg_defaults[i].def);
		mdelay(1);
	}

	return 0;
}

static const struct i2c_device_id alc5640_i2c_id[] = {
	{ "rtk,alc5640", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, alc5640_i2c_id);

static const struct of_device_id alc5640_of_id[] = {
	{ .compatible = "rtk,alc5640", },
	{ /* senitel */ }
};
MODULE_DEVICE_TABLE(of, alc5640_of_id);

static struct i2c_driver alc5640_i2c_driver = {
	.driver = {
		.name = "rtk,alc5640",
		.owner = THIS_MODULE,
		.of_match_table = alc5640_of_id,
	},
	.probe =    alc5640_i2c_probe,
//	.remove =   alc5640_i2c_remove,
	.id_table = alc5640_i2c_id,
};

static int rtk_alc5680_probe(struct platform_device *pdev)
{
	struct spi_master *spi_master;
	int                error;
	void __iomem	*gpio;
	
	/* get chip select gpio , init */
	gpio_cs_pin = of_get_gpio(pdev->dev.of_node, 0);
	gpio_request(gpio_cs_pin, "rtk_alc5680");
	gpio_direction_output(gpio_cs_pin,0);
	gpio_set_value(gpio_cs_pin,1);
	
	/* Set the pinmux before doing reset */
	gpio = ioremap(0x9801a910, 0x120);
	writel(0x6DB, gpio);
	gpio = ioremap(0x9801b100, 0x120);
	writel(0xe90000, gpio);
		
	gpio_reset_pin = of_get_gpio(pdev->dev.of_node, 1);
	pr_err("%s gpio_reset_pin=0x%x \n", __func__, gpio_reset_pin);
	gpio_request(gpio_reset_pin, "rtk_alc5680");
	gpio_direction_output(gpio_reset_pin,0);
	gpio_set_value(gpio_reset_pin,1);
	
	mdelay(2000); //wait for alc5520 is ready
	
	/* Recovery the pinmux after doing reset */
	gpio = ioremap(0x9801a910, 0x120);
	writel(0x000cf6db, gpio);
	gpio = ioremap(0x9801b100, 0x120);
	writel(0x00e90040, gpio);

	/* create spi device & driver */
	error = spi_register_driver(&alc5680_spi_driver);
	if (error < 0) {
		printk(KERN_ERR "spi_register_driver() returned %d\n", error);
		return error;
	}

	spi_master = spi_busnum_to_master(spi_bus_num);
	if (!spi_master) {
		printk(KERN_ERR "spi_busnum_to_master(%d) returned NULL\n", spi_bus_num);
		spi_unregister_driver(&alc5680_spi_driver);
		error = -ENODEV;
		return error;
	}

	spi_device = spi_new_device(spi_master, &alc5680_info);
	if (!spi_device) {
		printk(KERN_ERR "spi_new_device() returned NULL\n");
		spi_master_put(spi_master);
		return -EPERM;
	}

	spi_master_put(spi_master);

	/* create i2c driver */
	error = i2c_add_driver(&alc5680_i2c_driver);
	if (error) {
		printk(KERN_ERR "Fail to register ALC5680 I2C driver: %d\n",
			error); 
	}
	
	error = i2c_add_driver(&fl3236_i2c_driver);
	if (error) {
		printk(KERN_ERR "Fail to register FL3236 I2C driver: %d\n",
			error); 
	}
	
	error = i2c_add_driver(&alc5640_i2c_driver);
	if (error) {
		printk(KERN_ERR "Fail to register ALC5640 I2C driver: %d\n",
			error); 
	}

	return 0;
}

static int rtk_alc5680_remove(struct platform_device *pdev)
{

	spi_unregister_driver(&alc5680_spi_driver);
	i2c_del_driver(&alc5680_i2c_driver);
	return 0;
}

static const struct of_device_id rtk_alc5680_dt_ids[] = {
	{ .compatible = "Realtek,rtk-alc5680", },
	{},
};
MODULE_DEVICE_TABLE(of, rtk_alc5680_dt_ids);


static struct platform_driver rtk_alc5680_driver = {
    .probe = rtk_alc5680_probe,
    .remove = rtk_alc5680_remove,
    .driver = {
		.name = "rtk_alc5680",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(rtk_alc5680_dt_ids),
	},
};

module_platform_driver(rtk_alc5680_driver);


MODULE_AUTHOR("Cy Huang");
MODULE_DESCRIPTION("ALC5680 Kernel Driver");
MODULE_LICENSE("GPL");

