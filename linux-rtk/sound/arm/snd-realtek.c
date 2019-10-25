/**
 * snd-realtek.c - Realtek alsa driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/wait.h>
#include <linux/moduleparam.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/hrtimer.h>
#include <linux/mutex.h>
#include <linux/ioctl.h> /* needed for the _IOW etc stuff used later */
#include <linux/syscalls.h> /* needed for the _IOW etc stuff used later */
#include <linux/mpage.h>
#include <linux/dcache.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/math64.h>
#include <linux/dma-mapping.h>
#include <linux/suspend.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/control.h>
#include <sound/pcm.h>
#include <sound/rawmidi.h>
#include <sound/initval.h>
#include <asm/cacheflush.h>
#include "snd-realtek.h"
#include <rtk_rpc.h>
#include "snd-realtek-compress.h"

#ifdef CONFIG_RTK_XEN_SUPPORT
#include <xen/xen.h>
#endif

#ifdef RTK_TRACE_ALSA_EN
#define RTK_TRACE_ALSA(format, ...) printk(KERN_ALERT format, ##__VA_ARGS__);
#else
#define RTK_TRACE_ALSA(format, ...)
#endif

#define MIS_CLK90K_TM_LO_reg            0x9801B540
#define MIS_CLK90K_TM_HI_reg            0x9801B544
#define SYS_CLOCK_ENABLE2               0x98000010

#define ENDIAN_CHANGE(x) ((((x)&0xff000000)>>24)|(((x)&0x00ff0000)>>8)|(((x)&0x0000ff00)<<8)|(((x)&0x000000ff)<<24))
#define SHARE_MEM_SIZE 8
#define SHARE_MEM_SIZE_LATENCY sizeof(ALSA_LATENCY_INFO)
#define LPCM_2CH_16BITS (4)

#define SND_REALTEK_DRIVER "snd_alsa_rtk"
#define SND_REALTEK_DRIVER_I2S_IN "snd_alsa_rtk_i2s_in"
#define SND_REALTEK_DRIVER_NONPCM_IN "snd_alsa_rtk_nonpcm_in"
#define SND_REALTEK_DRIVER_AUDIO_IN "snd_alsa_rtk_audio_in"
#define SND_REALTEK_DRIVER_AUDIO_V2_IN "snd_alsa_rtk_audio_v2_in"
#define SND_REALTEK_DRIVER_AUDIO_V3_IN "snd_alsa_rtk_audio_v3_in"
#define SND_REALTEK_DRIVER_AUDIO_V4_IN "snd_alsa_rtk_audio_v4_in"

#ifndef MIN
#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#endif

static int snd_card_playback_open(snd_pcm_substream_t * substream);
static int snd_card_playback_close(snd_pcm_substream_t * substream);
static int snd_card_playback_ioctl(struct snd_pcm_substream *substream,  unsigned int cmd, void *arg);
static int snd_card_hw_params(snd_pcm_substream_t * substream, snd_pcm_hw_params_t * hw_params);
static int snd_card_hw_free(snd_pcm_substream_t * substream);
static int snd_card_playback_prepare(snd_pcm_substream_t * substream);
static int snd_card_playback_trigger(snd_pcm_substream_t * substream, int cmd);
static snd_pcm_uframes_t snd_card_playback_pointer(snd_pcm_substream_t * substream);

static int snd_card_capture_open(snd_pcm_substream_t * substream);
static int snd_card_capture_i2s_open(snd_pcm_substream_t * substream);
static int snd_card_capture_nonpcm_open(snd_pcm_substream_t * substream);
static int snd_card_capture_audio_open(snd_pcm_substream_t * substream);
static int snd_card_capture_audio_v2_open(snd_pcm_substream_t * substream);
static int snd_card_capture_audio_v3_open(snd_pcm_substream_t * substream);
static int snd_card_capture_audio_v4_open(snd_pcm_substream_t * substream);
static int snd_card_capture_close(snd_pcm_substream_t * substream);
static int snd_card_capture_close_audio(snd_pcm_substream_t * substream);
static int snd_card_capture_ioctl(struct snd_pcm_substream *substream,  unsigned int cmd, void *arg);
static int snd_card_capture_prepare(snd_pcm_substream_t * substream);
static int snd_card_capture_trigger(snd_pcm_substream_t * substream, int cmd);
static int snd_card_capture_hw_free(snd_pcm_substream_t * substream);
static snd_pcm_uframes_t snd_card_capture_pointer(snd_pcm_substream_t * substream);
static unsigned int snd_capture_monitor_delay(struct snd_pcm_substream *substream);
int snd_card_capture_get_time_info(struct snd_pcm_substream *substream,
			struct timespec *system_ts, struct timespec *audio_ts,
			struct snd_pcm_audio_tstamp_config *audio_tstamp_config,
			struct snd_pcm_audio_tstamp_report *audio_tstamp_report);
static int snd_realtek_hw_capture_malloc_pts_ring(snd_pcm_runtime_t *runtime);
static int snd_realtek_hw_capture_init_PTS_ringheader_of_AI(snd_pcm_runtime_t *runtime);
static void snd_card_capture_setup_pts(snd_pcm_runtime_t *runtime, AUDIO_DEC_PTS_INFO *pPkt);
int snd_realtek_capture_check_hdmirx_enable(void);
char *snd_realtek_capture_get_stream_name(void);
static void snd_card_capture_handle_HDMI_plug_out(snd_pcm_substream_t * substream);


static enum hrtimer_restart snd_card_timer_function(struct hrtimer *timer);
static enum hrtimer_restart snd_card_capture_lpcm_timer_function(struct hrtimer *timer);
static void snd_card_capture_timer_function(unsigned long data);
static void snd_card_capture_calculate_pts(snd_pcm_runtime_t *runtime, long nPeriodCount);

static unsigned long valid_free_size(unsigned long base, unsigned long limit, unsigned long rp, unsigned long wp);
static unsigned long ring_add(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, unsigned int bytes);
static unsigned long ring_valid_data(unsigned long ring_base, unsigned long ring_limit, unsigned long ring_rp, unsigned long ring_wp);
static unsigned long buf_memcpy2_ring(unsigned long base, unsigned long limit, unsigned long ptr, char* buf, unsigned long size);
static int ring_check_ptr_valid_32(unsigned int ring_rp, unsigned int ring_wp, unsigned int ptr);
static long ring_memcpy2_buf(char* buf,unsigned long base, unsigned long limit, unsigned long ptr, unsigned int size);
static unsigned long ring_minus(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, int bytes);

static int snd_realtek_hw_free_ring (snd_pcm_runtime_t *runtime);
static int snd_RTK_volume_info(snd_kcontrol_t * kcontrol, snd_ctl_elem_info_t * uinfo);
static int snd_RTK_volume_get(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol);
static int snd_RTK_volume_put(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol);
static int snd_RTK_capsrc_info(snd_kcontrol_t * kcontrol, snd_ctl_elem_info_t * uinfo);
static int snd_RTK_capsrc_get(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol);
static int snd_RTK_capsrc_put(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol);

static int snd_realtek_hw_capture_free_ring(snd_pcm_runtime_t *runtime);
static long snd_card_get_ring_data(RINGBUFFER_HEADER *pRing_BE, RINGBUFFER_HEADER *pRing_LE);
static void ring1_to_ring2_general_64(AUDIO_RINGBUF_PTR_64* ring1, AUDIO_RINGBUF_PTR_64* ring2, long size, char* dmem_buf);

/************************************************************************/
/* GLOBAL                                                                     */
/************************************************************************/
static struct platform_device *devices[SNDRV_CARDS] = {NULL};
static bool snd_card_enable[SNDRV_CARDS] = {1, [1 ... (SNDRV_CARDS - 1)] = 0};    // only one sound card
static int pcm_substreams[SNDRV_CARDS] = {[0 ... (SNDRV_CARDS - 1)] = 2};
static int pcm_capture_substreams[SNDRV_CARDS] = {[0 ... (SNDRV_CARDS - 1)] = 1};
static snd_card_t *snd_RTK_cards[SNDRV_CARDS] = SNDRV_DEFAULT_PTR;
static int snd_open_count = 0;
static int snd_open_ai_count = 0;
static char *snd_pcm_id[] = {SND_REALTEK_DRIVER, SND_REALTEK_DRIVER_I2S_IN, SND_REALTEK_DRIVER_NONPCM_IN,
								SND_REALTEK_DRIVER_AUDIO_IN, SND_REALTEK_DRIVER_AUDIO_V2_IN,
								SND_REALTEK_DRIVER_AUDIO_V3_IN, SND_REALTEK_DRIVER_AUDIO_V4_IN}; // multiple PCM instances in 1 sound card
static unsigned int rtk_dec_ao_buffer = RTK_DEC_AO_BUFFER_SIZE;
static void __iomem *clk90k_vaddr_hi = NULL;
static void __iomem *clk90k_vaddr_lo = NULL;
static void __iomem *sys_clk_en2_virt = NULL;

static spinlock_t playback_lock;
static spinlock_t capture_lock;
static int dec_out_msec = 0;
static int mtotal_latency = 0;
static int *g_ShareMemPtr = NULL;
static ALSA_LATENCY_INFO *g_ShareMemPtr2 = NULL;
static ALSA_LATENCY_INFO *g_ShareMemPtr3 = NULL;

static bool is_suspend = false;

#ifdef USE_ION_AUDIO_HEAP
struct ion_client *alsa_client;
static struct ion_handle *alsa_playback_handle = NULL;
static struct ion_handle *dec_out_handle[8] = {NULL};
static struct ion_handle *sharemem_handle = NULL;
static struct ion_handle *sharemem_handle2 = NULL;
static struct ion_handle *sharemem_handle3 = NULL;
static struct ion_handle *alsa_capture_handle = NULL;
static struct ion_handle *enc_in_handle[2] = {NULL};
static struct ion_handle *enc_lpcm_handle = NULL;
static struct ion_handle *enc_pts_handle = NULL;
static char gRtkDriverName[] = SND_REALTEK_DRIVER;

static ion_phys_addr_t g_ShareMemPtr_dat = 0;
static ion_phys_addr_t g_ShareMemPtr_dat2 = 0;
static ion_phys_addr_t g_ShareMemPtr_dat3 = 0;
#else
static dma_addr_t g_ShareMemPtr_dat;
static dma_addr_t g_ShareMemPtr_dat2;
static dma_addr_t g_ShareMemPtr_dat3;
#endif

static snd_kcontrol_new_t snd_mars_controls[] = {
MARS_VOLUME("Master Volume", 0, MIXER_ADDR_MASTER),
MARS_CAPSRC("Master Capture Switch", 0, MIXER_ADDR_MASTER),
MARS_VOLUME("Synth Volume", 0, MIXER_ADDR_SYNTH),
//MARS_CAPSRC("Synth Capture Switch", 0, MIXER_ADDR_MASTER),
//MARS_VOLUME("Line Volume", 0, MIXER_ADDR_LINE),
//MARS_CAPSRC("Line Capture Switch", 0, MIXER_ADDR_MASTER),
//MARS_VOLUME("Mic Volume", 0, MIXER_ADDR_MIC),
//MARS_CAPSRC("Mic Capture Switch", 0, MIXER_ADDR_MASTER),
//MARS_VOLUME("CD Volume", 0, MIXER_ADDR_CD),
//MARS_CAPSRC("CD Capture Switch", 0, MIXER_ADDR_MASTER)
};

static snd_pcm_ops_t snd_card_rtk_playback_ops = {
	.open =         snd_card_playback_open,
	.close =        snd_card_playback_close,
	.ioctl =        snd_card_playback_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_hw_free,
	.prepare =      snd_card_playback_prepare,
	.trigger =      snd_card_playback_trigger,
	.pointer =      snd_card_playback_pointer,
	.copy =         NULL,
	.silence =      NULL,
};

// for HDMI-RX in
static snd_pcm_ops_t snd_card_rtk_capture_ops = {
	.open =         snd_card_capture_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for I2S in
static snd_pcm_ops_t snd_card_rtk_capture_i2s_ops = {
	.open =         snd_card_capture_i2s_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for non-pcm-in flow in
static snd_pcm_ops_t snd_card_rtk_capture_nonpcm_ops = {
	.open =         snd_card_capture_nonpcm_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for audio processing CS demo
static snd_pcm_ops_t snd_card_rtk_capture_audio_ops = {
	.open =         snd_card_capture_audio_open,
	.close =        snd_card_capture_close_audio,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for audio processing v2 DMIC LOOPBACK
static snd_pcm_ops_t snd_card_rtk_capture_audio_v2_ops = {
	.open =         snd_card_capture_audio_v2_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for audio processing v3 SPEECH RECOGNITION FROM DMIC
static snd_pcm_ops_t snd_card_rtk_capture_audio_v3_ops = {
	.open =         snd_card_capture_audio_v3_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

// for audio processing v4 SPEECH RECOGNITION FROM I2S
static snd_pcm_ops_t snd_card_rtk_capture_audio_v4_ops = {
	.open =         snd_card_capture_audio_v4_open,
	.close =        snd_card_capture_close,
	.ioctl =        snd_card_capture_ioctl,
	.hw_params =    snd_card_hw_params,
	.hw_free =      snd_card_capture_hw_free,
	.prepare =      snd_card_capture_prepare,
	.trigger =      snd_card_capture_trigger,
	.pointer =      snd_card_capture_pointer,
	.copy =         NULL,
	.silence =      NULL,
	.get_time_info = snd_card_capture_get_time_info
};

static snd_pcm_hardware_t snd_card_playback =
{
	.info               = RTK_DMP_PLAYBACK_INFO,
	.formats            = RTK_DMP_PLAYBACK_FORMATS,
	.rates              = RTK_DMP_PLYABACK_RATES,
	.rate_min           = RTK_DMP_PLAYBACK_RATE_MIN,
	.rate_max           = RTK_DMP_PLAYBACK_RATE_MAX,
	.channels_min       = RTK_DMP_PLAYBACK_CHANNELS_MIN,
	.channels_max       = RTK_DMP_PLAYBACK_CHANNELS_MAX,
	.buffer_bytes_max   = RTK_DMP_PLAYBACK_MAX_BUFFER_SIZE,
	.period_bytes_min   = RTK_DMP_PLAYBACK_MIN_PERIOD_SIZE,
	.period_bytes_max   = RTK_DMP_PLAYBACK_MAX_PERIOD_SIZE,
	.periods_min        = RTK_DMP_PLAYBACK_PERIODS_MIN,
	.periods_max        = RTK_DMP_PLAYBACK_PERIODS_MAX,
	.fifo_size          = RTK_DMP_PLAYBACK_FIFO_SIZE,
};

static snd_pcm_hardware_t snd_card_mars_capture =
{
	.info               = RTK_DMP_CAPTURE_INFO,
	.formats            = RTK_DMP_CAPTURE_FORMATS,
	.rates              = RTK_DMP_CAPTURE_RATES,
	.rate_min           = RTK_DMP_CAPTURE_RATE_MIN,
	.rate_max           = RTK_DMP_CAPTURE_RATE_MAX,
	.channels_min       = RTK_DMP_CAPTURE_CHANNELS_MIN,
	.channels_max       = RTK_DMP_CAPTURE_CHANNELS_MAX,
	.buffer_bytes_max   = RTK_DMP_CAPTURE_MAX_BUFFER_SIZE,
	.period_bytes_min   = RTK_DMP_CAPTURE_MIN_PERIOD_SIZE,
	.period_bytes_max   = RTK_DMP_CAPTURE_MAX_PERIOD_SIZE,
	.periods_min        = RTK_DMP_CAPTURE_PERIODS_MIN,
	.periods_max        = RTK_DMP_CAPTURE_PERIODS_MAX,
	.fifo_size          = RTK_DMP_CAPTURE_FIFO_SIZE,
};

static snd_pcm_hardware_t snd_card_mars_capture_audio =
{
	.info                   = SNDRV_PCM_INFO_MMAP |
							SNDRV_PCM_INFO_MMAP_VALID |
							SNDRV_PCM_INFO_INTERLEAVED,
	.formats                = SNDRV_PCM_FMTBIT_S16_LE,
	.rates					= SNDRV_PCM_RATE_16000,
	.rate_min				= 16000,
	.rate_max 				= 16000,
	.period_bytes_min       = 64,
	.period_bytes_max       = 4096,
	.periods_min            = 4,
	.periods_max            = 1024,
	.channels_min           = 1,
	.channels_max           = 1,
	.buffer_bytes_max       = 32*1024,
};

/************************************************************************/
/* MODULE                                                               */
/************************************************************************/
module_param_array(snd_card_enable, bool, NULL, 0444);
MODULE_PARM_DESC(snd_card_enable, "Enable this mars soundcard.");
module_param_array(pcm_substreams, int, NULL, 0444);
MODULE_PARM_DESC(pcm_substreams, "PCM substreams # (1-16) for mars driver.");

/************************************************************************/
/* FUNCTION                                                             */
/************************************************************************/
int snd_monitor_audio_data_queue(void)
{
    /*
    int audioLatency = 0;
    if (g_ShareMemPtr)
    {
        audioLatency = *g_ShareMemPtr;
        audioLatency = ENDIAN_CHANGE(audioLatency);
    }
    else
    {
        //ALSA_WARNING("NO exist share memory !!\n");
    }

    //ALSA_VitalPrint("audiofw total latency %d (dec_out_msec %d ao_out_msec %d)\n", ret + dec_out_msec, dec_out_msec, ret);
    audioLatency += dec_out_msec;
    return audioLatency;
    */
    return mtotal_latency;
}

int snd_monitor_audio_data_queue_new(struct snd_pcm_substream *substream)
{
    int audioLatency = 0;
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    if (g_ShareMemPtr2) {

        uint64_t pcmPTS;
        uint64_t curPTS;
        uint64_t diffPTS;
        unsigned int sum = 0;
        unsigned int latency = 0;
        unsigned int ptsL = 0;
        unsigned int ptsH = 0;
        unsigned int in_wp = 0;
        //unsigned int in_rp = 0;

        int retry = 0;
        uint64_t inHWRingWp;
        uint64_t outHWRingWp;
        unsigned int wp_buffer;
        unsigned int wp_frame;

        //to get ALSA_LATENCY_INFO frmo fw
        if (g_ShareMemPtr3) {
            memcpy(g_ShareMemPtr3, g_ShareMemPtr2, SHARE_MEM_SIZE_LATENCY);

            latency = ENDIAN_CHANGE(g_ShareMemPtr3->latency);
            ptsL = ENDIAN_CHANGE(g_ShareMemPtr3->ptsL);
            ptsH = ENDIAN_CHANGE(g_ShareMemPtr3->ptsH);
            sum = ENDIAN_CHANGE(g_ShareMemPtr3->sum);
            in_wp = ENDIAN_CHANGE(g_ShareMemPtr3->decin_wp) & 0x0fffffff;
            //in_rp = ENDIAN_CHANGE(g_ShareMemPtr3->decin_rp) & 0x0fffffff;

            // make sure all of ALSA_LATENCY_INFO are updated.
            while (sum != (latency + ptsL)) {
                if (retry > 100) {
                    if (ptsL < sum) {
                        latency = sum - ptsL;
                    }
                    break;
                }
                memcpy(g_ShareMemPtr3, g_ShareMemPtr2, SHARE_MEM_SIZE_LATENCY);
                latency = ENDIAN_CHANGE(g_ShareMemPtr3->latency);
                ptsL = ENDIAN_CHANGE(g_ShareMemPtr3->ptsL);
                ptsH = ENDIAN_CHANGE(g_ShareMemPtr3->ptsH);
                sum = ENDIAN_CHANGE(g_ShareMemPtr3->sum);
                in_wp = ENDIAN_CHANGE(g_ShareMemPtr3->decin_wp) & 0x0fffffff;
                //in_rp = ENDIAN_CHANGE(g_ShareMemPtr3->decin_rp) & 0x0fffffff;
                retry++;
            }
        }
        //printk("alsa pcm latency %u, ptsL %u, ptsH %u, sum %u, in_wp %u \n", latency, ptsL, ptsH, sum, in_wp);
        inHWRingWp = (unsigned int)(ntohl(dpcm->decInRing[0].writePtr));//physical address
        outHWRingWp = (unsigned int)(ntohl(dpcm->decOutRing[0].writePtr));//physical address

        pcmPTS = (((uint64_t)ptsH<< 32) | ((uint64_t)ptsL));
        curPTS = snd_card_get_90k_pts();
        diffPTS = curPTS - pcmPTS;

        wp_frame = 0;
        if (in_wp != inHWRingWp) {
            wp_buffer = ring_valid_data(dpcm->decInRing_LE[0].beginAddr
                            ,dpcm->decInRing_LE[0].beginAddr + dpcm->decInRing_LE[0].size
                            ,(in_wp & 0x0fffffff)
                            ,inHWRingWp);
            wp_frame = bytes_to_frames(runtime, wp_buffer);
        }
        // old audio fw only has latency without ptsL and wp
        if (in_wp == 0 && ptsL == 0) {
            if (g_ShareMemPtr) {
                audioLatency = *g_ShareMemPtr;
                audioLatency = ENDIAN_CHANGE(audioLatency);
                audioLatency += dec_out_msec;
            }
        } else {
            unsigned long queuebuffer = (wp_frame + (runtime->control->appl_ptr - dpcm->nTotalWrite))*1000000 / runtime->rate; 
            audioLatency = latency + queuebuffer - div64_ul(diffPTS * 1000,90);
            audioLatency = audioLatency / 1000;
        }

        if (audioLatency < 0) {
            audioLatency = 0;
        }
    } else if (g_ShareMemPtr) {
        audioLatency = *g_ShareMemPtr;
        audioLatency = ENDIAN_CHANGE(audioLatency);
        audioLatency += dec_out_msec;
    } else {
        ALSA_WARNING("NO exist share memory !!\n");
    }

    mtotal_latency = audioLatency;

    return audioLatency;
}

int snd_realtek_capture_check_hdmirx_enable(void)
{
#define HDMI_RX_CLK_BIT 24
    int ret = 0;
    if(sys_clk_en2_virt)
    {
        ret = (int)readl(sys_clk_en2_virt);
        ret = (ret>> HDMI_RX_CLK_BIT) & 0x1;
    }
    return ret;
}

char *snd_realtek_capture_get_stream_name(void)
{
    return gRtkDriverName;
}

static int snd_realtek_hw_check_audio_ready(void) 
{
    wait_queue_head_t     waitQueue;        /* for blocking read */
    int ret = 0;

    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    // Initialize wait queue...
    init_waitqueue_head(&waitQueue);

    ret = wait_event_interruptible_timeout(waitQueue, RPC_TOAGENT_CHECK_AUDIO_READY() == 0, HZ);

    if ( ret <= 0 )
        return 1;   // fail
    else 
        return 0;   // success
}

static int snd_realtek_hw_capture_init_ringheader_of_AI(snd_pcm_runtime_t *runtime)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    RINGBUFFER_HEADER *pAIRingHeader = dpcm->nAIRing;
    RINGBUFFER_HEADER *pAIRingHeader_LE = dpcm->nAIRing_LE;
    AUDIO_RPC_RINGBUFFER_HEADER nRingHeader;
    int ch;

    // init ring header
    for(ch = 0; ch < runtime->channels; ++ch)
    {
        //pAIRingHeader_LE[ch].beginAddr = (unsigned long)dpcm->pAIRingData[ch];
        pAIRingHeader_LE[ch].beginAddr = (unsigned long)dpcm->phy_pAIRingData[ch];
        pAIRingHeader_LE[ch].size = dpcm->nRingSize;
        pAIRingHeader_LE[ch].readPtr[0] = pAIRingHeader_LE[ch].beginAddr;
        pAIRingHeader_LE[ch].writePtr = pAIRingHeader_LE[ch].beginAddr;
        pAIRingHeader_LE[ch].numOfReadPtr = 1;

        pAIRingHeader[ch].beginAddr = htonl((unsigned long)pAIRingHeader_LE[ch].beginAddr);
        pAIRingHeader[ch].size = htonl(pAIRingHeader_LE[ch].size);
        pAIRingHeader[ch].readPtr[0] = htonl(pAIRingHeader_LE[ch].readPtr[0]);
        pAIRingHeader[ch].writePtr = htonl(pAIRingHeader_LE[ch].writePtr);
        pAIRingHeader[ch].numOfReadPtr = htonl(pAIRingHeader_LE[ch].numOfReadPtr);

        //nRingHeader.pRingBufferHeaderList[ch] = (unsigned int) (pAIRingHeader + ch);
        nRingHeader.pRingBufferHeaderList[ch] = (unsigned long) (pAIRingHeader + ch) - (unsigned long)dpcm + dpcm->phy_addr;

        //ALSA_VitalPrint("[ALSA ringHeader %x %x]\n", ch, nRingHeader.pRingBufferHeaderList[ch]);
        ALSA_DbgPrint("[ALSA %d ring %x %x %x %x]\n", ch, (unsigned int)pAIRingHeader_LE[ch].beginAddr
            , (unsigned int)pAIRingHeader_LE[ch].size, (unsigned int)pAIRingHeader_LE[ch].readPtr[0]
            , (unsigned int)pAIRingHeader_LE[ch].writePtr);
    }

    // init AI ring header
    nRingHeader.instanceID = dpcm->AIAgentID;
    nRingHeader.pinID = PCM_OUT;
    nRingHeader.readIdx = -1;
    nRingHeader.listSize =  runtime->channels;

    // RPC set AI ring header
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    return 0;
}

static int snd_realtek_hw_capture_destroy_LPCM_ringheader_of_Audio(snd_pcm_runtime_t *runtime)
{
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	RINGBUFFER_HEADER *pAIRingHeader = &dpcm->nLPCMRing;
	RINGBUFFER_HEADER *pAIRingHeader_LE = &dpcm->nLPCMRing_LE;
	AUDIO_RPC_RINGBUFFER_HEADER nRingHeader;

	// init ring header
	pAIRingHeader_LE->beginAddr = (unsigned int)dpcm->phy_pLPCMData;
	pAIRingHeader_LE->size = dpcm->nLPCMRingSize;
	pAIRingHeader_LE->readPtr[0] = pAIRingHeader_LE->beginAddr;
	pAIRingHeader_LE->writePtr = pAIRingHeader_LE->beginAddr;
	pAIRingHeader_LE->numOfReadPtr = 1;

	pAIRingHeader->beginAddr = htonl((unsigned int)pAIRingHeader_LE->beginAddr);
	pAIRingHeader->size = htonl(pAIRingHeader_LE->size);
	pAIRingHeader->readPtr[0] = htonl(pAIRingHeader_LE->readPtr[0]);
	pAIRingHeader->writePtr = htonl(pAIRingHeader_LE->writePtr);
	pAIRingHeader->numOfReadPtr = htonl(pAIRingHeader_LE->numOfReadPtr);

	nRingHeader.pRingBufferHeaderList[0] = (int)((unsigned long) pAIRingHeader - (unsigned long)dpcm + dpcm->phy_addr);

	// init AI ring header
	nRingHeader.instanceID = dpcm->AIAgentID;
	nRingHeader.readIdx = -1;
	nRingHeader.listSize = 0;

	if(dpcm->source_in == ENUM_AIN_AUDIO)
		nRingHeader.pinID = APP_LPCM_OUT;
	else
		nRingHeader.pinID = BASE_BS_OUT;

	// RPC set AI ring header
	if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -1;
	};

	return 0;
}

static int snd_realtek_hw_capture_init_LPCM_ringheader_of_AI(snd_pcm_runtime_t *runtime)
{
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	RINGBUFFER_HEADER *pAIRingHeader = &dpcm->nLPCMRing;
	RINGBUFFER_HEADER *pAIRingHeader_LE = &dpcm->nLPCMRing_LE;
	AUDIO_RPC_RINGBUFFER_HEADER nRingHeader;

	// init ring header
	pAIRingHeader_LE->beginAddr = (unsigned int)dpcm->phy_pLPCMData;
	pAIRingHeader_LE->size = dpcm->nLPCMRingSize;
	pAIRingHeader_LE->readPtr[0] = pAIRingHeader_LE->beginAddr;
	pAIRingHeader_LE->writePtr = pAIRingHeader_LE->beginAddr;
	pAIRingHeader_LE->numOfReadPtr = 1;

	pAIRingHeader->beginAddr = htonl((unsigned int)pAIRingHeader_LE->beginAddr);
	pAIRingHeader->size = htonl(pAIRingHeader_LE->size);
	pAIRingHeader->readPtr[0] = htonl(pAIRingHeader_LE->readPtr[0]);
	pAIRingHeader->writePtr = htonl(pAIRingHeader_LE->writePtr);
	pAIRingHeader->numOfReadPtr = htonl(pAIRingHeader_LE->numOfReadPtr);

	nRingHeader.pRingBufferHeaderList[0] = (int)((unsigned long) pAIRingHeader - (unsigned long)dpcm + dpcm->phy_addr);

	// init AI ring header
	nRingHeader.instanceID = dpcm->AIAgentID;
	nRingHeader.readIdx = -1;
	nRingHeader.listSize = 1;

	if(dpcm->source_in == ENUM_AIN_AUDIO)
		nRingHeader.pinID = APP_LPCM_OUT;
	else
		nRingHeader.pinID = BASE_BS_OUT;

	// RPC set AI ring header
	if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -1;
	};

	return 0;
}

static int snd_realtek_hw_capture_init_PTS_ringheader_of_AI(snd_pcm_runtime_t *runtime)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    RINGBUFFER_HEADER *pAIRingHeader = &dpcm->nPTSRingHdr;
    RINGBUFFER_HEADER *pAIRingHeader_LE, nAIRingHeader_LE;
    AUDIO_RPC_RINGBUFFER_HEADER nRingHeader;
    pAIRingHeader_LE = &nAIRingHeader_LE;

    dpcm->nPTSRing.base = (unsigned long)dpcm->nPTSMem.pVirt;
    dpcm->nPTSRing.wp = dpcm->nPTSRing.rp = dpcm->nPTSRing.base;
    dpcm->nPTSRing.limit = dpcm->nPTSRing.base + dpcm->nPTSMem.size;

    // init ring header
    pAIRingHeader_LE->beginAddr = (unsigned int)dpcm->nPTSMem.pPhy;
    pAIRingHeader_LE->size = dpcm->nPTSMem.size;
    pAIRingHeader_LE->readPtr[0] = pAIRingHeader_LE->beginAddr;
    pAIRingHeader_LE->writePtr = pAIRingHeader_LE->beginAddr;
    pAIRingHeader_LE->numOfReadPtr = 1;

    pAIRingHeader->beginAddr = htonl((unsigned int)pAIRingHeader_LE->beginAddr);
    pAIRingHeader->size = htonl(pAIRingHeader_LE->size);
    pAIRingHeader->readPtr[0] = htonl(pAIRingHeader_LE->readPtr[0]);
    pAIRingHeader->writePtr = htonl(pAIRingHeader_LE->writePtr);
    pAIRingHeader->numOfReadPtr = htonl(pAIRingHeader_LE->numOfReadPtr);

    nRingHeader.pRingBufferHeaderList[0] = (int)((unsigned long) pAIRingHeader - (unsigned long)dpcm + dpcm->phy_addr);

    // init AI ring header
    nRingHeader.instanceID = dpcm->AIAgentID;
    nRingHeader.pinID = MESSAGE_QUEUE;
    nRingHeader.readIdx = -1;
    nRingHeader.listSize = 1;
    
    // RPC set AI ring header
    //if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, runtime->channels) < 0) {
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    return 0;
}


// init ringheader of decoder_outring and AO_inring
static int snd_realtek_hw_init_ringheader_of_DEC_AO(snd_pcm_runtime_t *runtime)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    RINGBUFFER_HEADER *pAORingHeader = dpcm->decOutRing;
    AUDIO_RPC_RINGBUFFER_HEADER nRingHeader;
    int ch, j;

    // init ring header
    //for(ch = 0 ; ch < 8 ; ++ch)
    for (ch = 0 ; ch < runtime->channels ; ++ch) {
        //pAORingHeader[ch].beginAddr = htonl((unsigned long)dpcm->decOutData[ch]);
        pAORingHeader[ch].beginAddr = (unsigned int)htonl(dpcm->phy_decOutData[ch]);
        pAORingHeader[ch].size = htonl(dpcm->nRingSize);
        for (j = 0 ; j < 4 ; ++j)
            pAORingHeader[ch].readPtr[j] = pAORingHeader[ch].beginAddr;
        pAORingHeader[ch].writePtr = pAORingHeader[ch].beginAddr;
        pAORingHeader[ch].numOfReadPtr = htonl(1);
    }

    // init DEC outring header
    nRingHeader.instanceID = dpcm->DECAgentID;
    nRingHeader.pinID = PCM_OUT;
    //nRingHeader.pRingBufferHeaderList[0] = (unsigned int) &dpcm->decOutRing[0];
    //nRingHeader.pRingBufferHeaderList[1] = (unsigned int) &dpcm->decOutRing[1];
    for (ch = 0 ; ch < runtime->channels ; ++ch)
        nRingHeader.pRingBufferHeaderList[ch] = (unsigned long)&dpcm->decOutRing[ch] - (unsigned long)dpcm + dpcm->phy_addr;
    nRingHeader.readIdx = -1;
    nRingHeader.listSize = runtime->channels;

    // RPC set DEC outring header
    //if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, runtime->channels) < 0) {
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    // init AO inring header
    nRingHeader.instanceID = dpcm->AOAgentID;
    nRingHeader.pinID = dpcm->AOpinID;
    //nRingHeader.pRingBufferHeaderList[0] = (unsigned int) &dpcm->decOutRing[0];
    //nRingHeader.pRingBufferHeaderList[1] = (unsigned int) &dpcm->decOutRing[1];
    for (ch = 0 ; ch < runtime->channels ; ++ch)
        nRingHeader.pRingBufferHeaderList[ch] = (unsigned long)&dpcm->decOutRing[ch] - (unsigned long)dpcm + dpcm->phy_addr;
    nRingHeader.readIdx = 0;
    nRingHeader.listSize = runtime->channels;

    // RPC set AO inring header
    //if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, runtime->channels) < 0) {
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&nRingHeader, nRingHeader.listSize) < 0) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    return 0;
}

// connet decoder and AO by RPC
static int snd_realtek_hw_init_connect_decoder_ao(snd_card_RTK_pcm_t *dpcm)
{   
    AUDIO_RPC_CONNECTION nConnection;

    nConnection.desInstanceID = dpcm->AOAgentID;            
    nConnection.srcInstanceID = dpcm->DECAgentID;
    nConnection.srcPinID = PCM_OUT;
    nConnection.desPinID = dpcm->AOpinID;

    if (RPC_TOAGENT_CONNECT_SVC(&nConnection)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    };
    return 0;
}

// 1. init decoder in_ring
// 2. init decoder inband ring
static int snd_realtek_hw_init_decoder_ring(snd_pcm_runtime_t *runtime) {
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    AUDIO_RPC_RINGBUFFER_HEADER ringbuf_header;
    
    // init HW inring header
    //printk("dma buffer virAddr %lx\n", (unsigned long) runtime->dma_area);
    //printk("dma buffer phyAddr %lx\n", (unsigned long) runtime->dma_addr);
    //printk("dma buffer size         %d\n", (unsigned long) runtime->dma_bytes);
    dpcm->decInRing[0].beginAddr = htonl((unsigned int)runtime->dma_addr);
    dpcm->decInRing[0].bufferID = htonl(RINGBUFFER_STREAM);
    dpcm->decInRing[0].size = htonl(frames_to_bytes(runtime, runtime->buffer_size));
    dpcm->decInRing[0].writePtr = dpcm->decInRing[0].beginAddr; 
    dpcm->decInRing[0].readPtr[0] = dpcm->decInRing[0].beginAddr;
    dpcm->decInRing[0].readPtr[1] = dpcm->decInRing[0].beginAddr;
    dpcm->decInRing[0].readPtr[2] = dpcm->decInRing[0].beginAddr;
    dpcm->decInRing[0].readPtr[3] = dpcm->decInRing[0].beginAddr;
    dpcm->decInRing[0].numOfReadPtr = htonl(1);

    //printk("[INRING] writeAddr %x\n", htonl(dpcm->decInRing[0].writePtr));
    // init HW inring (little endian)
    dpcm->decInRing_LE[0].beginAddr = ((unsigned int)runtime->dma_addr);
    dpcm->decInRing_LE[0].size = frames_to_bytes(runtime, runtime->buffer_size);
    dpcm->decInRing_LE[0].writePtr = dpcm->decInRing_LE[0].beginAddr;
    dpcm->decInRing_LE[0].readPtr[0] = dpcm->decInRing_LE[0].beginAddr;
    dpcm->decInRing_LE[0].readPtr[1] = dpcm->decInRing_LE[0].beginAddr;
    dpcm->decInRing_LE[0].readPtr[2] = dpcm->decInRing_LE[0].beginAddr;
    dpcm->decInRing_LE[0].readPtr[3] = dpcm->decInRing_LE[0].beginAddr;

    //printk("[INRING LE] writeAddr %x\n", dpcm->decInRing_LE[0].writePtr);
    // init RPC ring header
    ringbuf_header.instanceID = dpcm->DECAgentID;
    ringbuf_header.pinID = BASE_BS_IN;
    ringbuf_header.pRingBufferHeaderList[0] = (unsigned long)dpcm->decInRing - (unsigned long)dpcm + dpcm->phy_addr;
    ringbuf_header.readIdx = 0;
    ringbuf_header.listSize = 1;

    // RPC set decoder in_ring
    //if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&ringbuf_header, runtime->channels)) 
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&ringbuf_header, ringbuf_header.listSize)) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    };

    // init inband ring header
    dpcm->decInbandRing.beginAddr = htonl((int)((unsigned long)dpcm->decInbandData - (unsigned long)dpcm + dpcm->phy_addr));
    //TRACE_CODE("[INBAND RING] beginAddr %x\n", dpcm->decInbandRing.beginAddr);
    dpcm->decInbandRing.size = htonl(sizeof(dpcm->decInbandData));
    dpcm->decInbandRing.readPtr[0] = dpcm->decInbandRing.beginAddr;
    dpcm->decInbandRing.writePtr = dpcm->decInbandRing.beginAddr;
    dpcm->decInbandRing.numOfReadPtr = htonl(1);

    // init RPC ring header
    ringbuf_header.instanceID = dpcm->DECAgentID;
    ringbuf_header.pinID = INBAND_QUEUE;
    ringbuf_header.pRingBufferHeaderList[0] = (unsigned long)&dpcm->decInbandRing - (unsigned long)dpcm + dpcm->phy_addr; //physical
    ringbuf_header.readIdx = 0;
    ringbuf_header.listSize = 1;

    //if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&ringbuf_header, runtime->channels)) 
    if (RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&ringbuf_header, ringbuf_header.listSize)) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    };
    return 0;
}

static int snd_realtek_hw_capture_run(snd_card_RTK_capture_pcm_t *dpcm) 
{
    // AI pause
    if (RPC_TOAGENT_PAUSE_SVC(dpcm->AIAgentID)) 
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1; 
    }

    // AI run
    if(RPC_TOAGENT_RUN_SVC(dpcm->AIAgentID))
    {
        ALSA_WARNING("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    return 0;
}

static int snd_realtek_hw_resume(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    // decoder run & AO run
    if (RPC_TOAGENT_RUN_SVC(dpcm->DECAgentID)) {
        ALSA_WARNING("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }
    if (RPC_TOAGENT_RUN_SVC((dpcm->AOAgentID | dpcm->AOpinID))) {
        ALSA_WARNING("[%s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }
    return 0;
}

int writeInbandCmd(snd_card_RTK_pcm_t *dpcm, void *data, int len)
{
    //snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    unsigned long base, limit, wp;
    base = (unsigned long)dpcm->decInbandData;
    limit = base + sizeof(dpcm->decInbandData);
    wp = base + (unsigned long)(ntohl(dpcm->decInbandRing.writePtr) - ntohl(dpcm->decInbandRing.beginAddr));

    //ALSA_VitalPrint("base %x limit %x wp %x\n", (long)base, (long)limit, (long)wp);
    wp = buf_memcpy2_ring(base, limit, wp, (char *)data, (unsigned long)len);
    dpcm->decInbandRing.writePtr = ntohl((int)(wp - base) + ntohl(dpcm->decInbandRing.beginAddr));
    //TRACE_CODE("[INBAND RING] writeAddr %x\n", dpcm->decInbandRing.writePtr);
    return len;
}

// ring is big-endian
int snd_realtek_hw_ring_write(RINGBUFFER_HEADER* ring, void *data, int len, unsigned int offset)
{
    unsigned long base, limit, wp;

    //Convert to virtual address
    base = (unsigned long)(ntohl(ring->beginAddr)) + offset;
    limit = base + ntohl(ring->size);
    wp = (unsigned long)(ntohl(ring->writePtr)) + offset;
    ALSA_VitalPrint("base %x limit %x wp %x \n", (unsigned int)base, (unsigned int)limit, (unsigned int)wp);
    //TRACE_CODE("base %x limit %x wp %x \n", (long)base, (long)limit, (long)wp);
    wp = buf_memcpy2_ring((long)base, (long)limit, (long)wp, (char *)data, (long)len);
    ring->writePtr = htonl(wp - offset); // record physical address
    return len;
}

/* The setting for different channel mapping. 
   This will send rpc for AFW.
 */
static unsigned int snd_choose_channel_mapping(int num_channels)
{
	unsigned int channel_mapping_info;
	switch (num_channels)
	{
		case 1:
			channel_mapping_info = (0x1) << 6;
			break;
		case 2:
			channel_mapping_info = (0x3) << 6;
			break;
		case 4:
			channel_mapping_info = (0x33) << 6;
			break;
		case 6:
			channel_mapping_info = (0x3F) << 6;
			break;
		case 8:
			channel_mapping_info = (0x63F) << 6;
			break;
		default:
			channel_mapping_info = (0x3) << 6;
			break;
	}
	
	return channel_mapping_info;
}

// AO pause
// decoder pause
// decoder run
// decoder flush
// write decoder info into inband of decoder
static int snd_realtek_hw_init_decoder_info(snd_pcm_runtime_t *runtime) 
{
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    AUDIO_DEC_NEW_FORMAT cmd;
    AUDIO_RPC_SENDIO sendio;

    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    // AO pause
    if (RPC_TOAGENT_PAUSE_SVC(dpcm->AOAgentID | dpcm->AOpinID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1; 
    }

    // decoder pause
    //if (RPC_TOAGENT_PAUSE_SVC(dpcm->DECAgentID))
    if (RPC_TOAGENT_STOP_SVC(dpcm->DECAgentID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // decoder flush
    sendio.instanceID = dpcm->DECAgentID;
    sendio.pinID = dpcm->DECpinID;
    if (RPC_TOAGENT_FLUSH_SVC(&sendio)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // decoder run
    if (RPC_TOAGENT_RUN_SVC(dpcm->DECAgentID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    cmd.audioType = htonl(AUDIO_LPCM_DECODER_TYPE); 
    cmd.header.type = htonl(AUDIO_DEC_INBAMD_CMD_TYPE_NEW_FORMAT);
    cmd.header.size = htonl(sizeof(AUDIO_DEC_NEW_FORMAT));
    cmd.privateInfo[0] = htonl(runtime->channels);
    cmd.privateInfo[1] = htonl(runtime->sample_bits);
    cmd.privateInfo[2] = htonl(runtime->rate);
    cmd.privateInfo[3] = htonl(0);
    cmd.privateInfo[4] = htonl(snd_choose_channel_mapping(runtime->channels));  // privateInfo[4]&0x3FFFC0)>>6; // bit[6:21] for wave channel mask
    cmd.privateInfo[5] = htonl(0);
    cmd.privateInfo[6] = htonl(0);  // (a_format->privateData[0]&0x1)<<4 : float or not
    cmd.privateInfo[7] = htonl(0);

    switch (runtime->format)
    {
        case SNDRV_PCM_FORMAT_S16_BE:
        case SNDRV_PCM_FORMAT_U16_BE:
        case SNDRV_PCM_FORMAT_S24_BE:
        case SNDRV_PCM_FORMAT_U24_BE:
        case SNDRV_PCM_FORMAT_S32_BE:
        case SNDRV_PCM_FORMAT_U32_BE:
        case SNDRV_PCM_FORMAT_S24_3BE:
        case SNDRV_PCM_FORMAT_U24_3BE:
        case SNDRV_PCM_FORMAT_S20_3BE:      
        case SNDRV_PCM_FORMAT_U20_3BE:
        case SNDRV_PCM_FORMAT_S18_3BE:
        case SNDRV_PCM_FORMAT_U18_3BE:
        case SNDRV_PCM_FORMAT_FLOAT_BE:
        case SNDRV_PCM_FORMAT_FLOAT64_BE:
        case SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE:
            cmd.privateInfo[7]  = htonl(AUDIO_BIG_ENDIAN);
            break;

        case SNDRV_PCM_FORMAT_S8:
        case SNDRV_PCM_FORMAT_U8:
        case SNDRV_PCM_FORMAT_S16_LE:
        case SNDRV_PCM_FORMAT_U16_LE:
        case SNDRV_PCM_FORMAT_S24_LE:
        case SNDRV_PCM_FORMAT_U24_LE:
        case SNDRV_PCM_FORMAT_S32_LE:
        case SNDRV_PCM_FORMAT_U32_LE:
        case SNDRV_PCM_FORMAT_S24_3LE:
        case SNDRV_PCM_FORMAT_U24_3LE:
        case SNDRV_PCM_FORMAT_S20_3LE:
        case SNDRV_PCM_FORMAT_U20_3LE:
        case SNDRV_PCM_FORMAT_S18_3LE:
        case SNDRV_PCM_FORMAT_U18_3LE:
        case SNDRV_PCM_FORMAT_FLOAT_LE:
        case SNDRV_PCM_FORMAT_FLOAT64_LE:
        case SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE:
        case SNDRV_PCM_FORMAT_MU_LAW:
        case SNDRV_PCM_FORMAT_A_LAW:
        case SNDRV_PCM_FORMAT_IMA_ADPCM:
        case SNDRV_PCM_FORMAT_MPEG:
        case SNDRV_PCM_FORMAT_GSM:
        case SNDRV_PCM_FORMAT_SPECIAL:
        default:
            cmd.privateInfo[7]  = htonl(AUDIO_LITTLE_ENDIAN);
            break;
    }

    cmd.wPtr = dpcm->decInRing[0].writePtr;
    //printk("[test] dpcm->decInRing[0].beginAddr %lx\n" , cmd.wPtr); //decoder buffer ring physical address

#ifdef CONFIG_64BIT
    writeInbandCmd(dpcm, &cmd, sizeof(AUDIO_DEC_NEW_FORMAT));
#else
    //snd_realtek_hw_ring_write(((unsigned long)dpcm->decInbandRing - (unsigned long)dpcm + dpcm->phy_addr), &cmd, sizeof(AUDIO_DEC_NEW_FORMAT)); 
    snd_realtek_hw_ring_write(&dpcm->decInbandRing, &cmd, sizeof(AUDIO_DEC_NEW_FORMAT), (unsigned long)dpcm - (unsigned long)dpcm->phy_addr); 
#endif
    //ALSA_VitalPrint("[ALSA LPCM ch %d sample_bit %d sample rate %d]\n", runtime->channels, runtime->sample_bits, runtime->rate);
    return 0;
}

// decoder stop
// AO pause
// AO stop
// decoder flush
// destroy decoder
static int snd_realtek_reprepare(snd_pcm_runtime_t *runtime) 
{
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    AUDIO_RPC_SENDIO sendio;
	
	// DHCKYLIN-2822 disable get_latency before destroy decoder instance
    if (dpcm->DECAgentID) {
        RPC_TOAGENT_PUT_SHARE_MEMORY(NULL, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
        RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY(NULL, NULL, 0, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
    }
	
	// decoder stop
    if (RPC_TOAGENT_STOP_SVC(dpcm->DECAgentID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // AO pause
    if (RPC_TOAGENT_PAUSE_SVC(dpcm->AOAgentID | dpcm->AOpinID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1; 
    }
	
	// AO stop
    if (RPC_TOAGENT_STOP_SVC(dpcm->AOAgentID | dpcm->AOpinID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1; 
    }

    // decoder flush
    sendio.instanceID = dpcm->DECAgentID;
    sendio.pinID = dpcm->DECpinID;
    if (RPC_TOAGENT_FLUSH_SVC(&sendio)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }

	// destroy decoder
    if (RPC_TOAGENT_DESTROY_SVC(dpcm->DECAgentID)) {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -1;
    }
	
	// free decoder InBand ring
	memset(dpcm->decInbandData, 0, sizeof(unsigned int)*64);

	// free ao in_ring
	// decoder out_ring = ao in_ring
	snd_realtek_hw_free_ring(runtime);

	return 0;
}

// malloc ring buffer for AI.
static int snd_realtek_hw_capture_malloc_ring(snd_pcm_runtime_t *runtime)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    int ch , bMallocSuccess = 1;
#ifdef USE_ION_AUDIO_HEAP
    ion_phys_addr_t dat;
    size_t len;
#endif
    for(ch = 0 ; ch < runtime->channels ; ++ch)
    {
        if(dpcm->pAIRingData[ch])
        {
            ALSA_WARNING("[re-malloc error !!! %s %d]\n", __FUNCTION__, __LINE__);
#ifdef USE_ION_AUDIO_HEAP
            if(alsa_client != NULL && enc_in_handle[ch] != NULL)
            {
                ion_unmap_kernel(alsa_client, enc_in_handle[ch]);
                ion_free(alsa_client, enc_in_handle[ch]);
                enc_in_handle[ch] = NULL;
            }
#else
            dma_free_coherent(NULL, RTK_ENC_AI_BUFFER_SIZE, dpcm->pAIRingData[ch], dpcm->phy_pAIRingData[ch]);
#endif
            dpcm->pAIRingData[ch] = NULL;
        }

#ifdef USE_ION_AUDIO_HEAP
        //printk("%s create enc_in_handle[%d]\n", __FUNCTION__, ch);
        enc_in_handle[ch] = ion_alloc(alsa_client, RTK_ENC_AI_BUFFER_SIZE, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

        if (IS_ERR(enc_in_handle[ch])) {
             ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
             return bMallocSuccess;
        }

        if(ion_phys(alsa_client, enc_in_handle[ch], &dat, &len) != 0)
        {
            snd_realtek_hw_capture_free_ring(runtime);
            ALSA_WARNING("[malloc ch %d fail and terminate %s %d]\n", ch, __FUNCTION__, __LINE__);
            return bMallocSuccess;
        }

        dpcm->phy_pAIRingData[ch] = dat;
        dpcm->pAIRingData[ch] = ion_map_kernel(alsa_client, enc_in_handle[ch]);
        ALSA_VitalPrint("[ALSA ch %d phy %x vir %p]\n", ch, (unsigned int)dpcm->phy_pAIRingData[ch], dpcm->pAIRingData[ch]);
#else
        void *addr = 0;
        addr = dma_alloc_coherent(NULL, RTK_ENC_AI_BUFFER_SIZE, &dpcm->phy_pAIRingData[ch], GFP_KERNEL);
        if(!addr)
        {
            snd_realtek_hw_capture_free_ring(runtime);
            printk("[malloc ch %d fail and terminate %s %d]\n", ch, __FUNCTION__, __LINE__);
            return bMallocSuccess;
        }
        dpcm->pAIRingData[ch] = addr;
#endif   
        dpcm->nRingSize = RTK_ENC_AI_BUFFER_SIZE;
    }

    bMallocSuccess = 0; //Success
    return bMallocSuccess;
}

static int snd_realtek_hw_capture_malloc_lpcm_ring(snd_pcm_runtime_t *runtime)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

    int bMallocSuccess = 1;

#ifdef USE_ION_AUDIO_HEAP
    ion_phys_addr_t dat;
    size_t len;

    //printk("%s create enc_lpcm_handle\n", __FUNCTION__);
    enc_lpcm_handle = ion_alloc(alsa_client, RTK_ENC_LPCM_BUFFER_SIZE, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(enc_lpcm_handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        return bMallocSuccess;
    }

    if(ion_phys(alsa_client, enc_lpcm_handle, &dat, &len) != 0)
    {
        printk("[malloc fail and terminate %s %d]\n", __FUNCTION__, __LINE__);
        return bMallocSuccess;
    }

    dpcm->phy_pLPCMData= dat;
    dpcm->pLPCMData = ion_map_kernel(alsa_client, enc_lpcm_handle);
    ALSA_VitalPrint("[ALSA LPCM phy %x vir %p]\n", (unsigned int)dpcm->phy_pLPCMData, dpcm->pLPCMData);
#else
    void *addr = 0;
    addr = dma_alloc_coherent(NULL, RTK_ENC_LPCM_BUFFER_SIZE, &dpcm->phy_pLPCMData,  GFP_KERNEL);
    if(!addr)
    {
        printk("[malloc fail and terminate %s %d]\n", __FUNCTION__, __LINE__);
        return bMallocSuccess;
    }
    dpcm->pLPCMData = addr;
#endif
    dpcm->nLPCMRingSize = RTK_ENC_LPCM_BUFFER_SIZE;

    bMallocSuccess = 0; //Success
    return bMallocSuccess;
}

static int snd_realtek_hw_capture_malloc_pts_ring(snd_pcm_runtime_t *runtime)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

    int bMallocSuccess = -1;

    ion_phys_addr_t dat;
    size_t len;

    //printk("%s create enc_lpcm_handle\n", __FUNCTION__);
    dpcm->nPTSMem.size = RTK_ENC_PTS_BUFFER_SIZE;
    enc_pts_handle = ion_alloc(alsa_client, RTK_ENC_PTS_BUFFER_SIZE, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

    if (IS_ERR(enc_pts_handle)) {
        ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
        return bMallocSuccess;
    }

    if(ion_phys(alsa_client, enc_pts_handle, &dat, &len) != 0)
    {
        printk("[malloc fail and terminate %s %d]\n", __FUNCTION__, __LINE__);
        return bMallocSuccess;
    }

    dpcm->nPTSMem.pPhy = dat;
    dpcm->nPTSMem.pVirt = ion_map_kernel(alsa_client, enc_pts_handle);
    ALSA_VitalPrint("[ALSA PTS phy %x vir %p]\n"
        , (unsigned int)dpcm->nPTSMem.pPhy, dpcm->nPTSMem.pVirt);

    bMallocSuccess = 0; //Success
    return bMallocSuccess;
}


// in decoder-AO path, malloc AO in_ring
static int snd_realtek_hw_malloc_ring(snd_pcm_runtime_t *runtime)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    int ch, bMallocSuccess = 1;
#ifdef USE_ION_AUDIO_HEAP
    ion_phys_addr_t dat;
    size_t len;
#endif

    for (ch = 0 ; ch < runtime->channels ; ++ch) {
        if (dpcm->decOutData[ch]) {
            printk("[re-malloc error !!! %s %d]\n", __FUNCTION__, __LINE__);
#ifdef USE_ION_AUDIO_HEAP
            if (alsa_client != NULL && dec_out_handle[ch] != NULL) {
                ion_unmap_kernel(alsa_client, dec_out_handle[ch]);
                ion_free(alsa_client, dec_out_handle[ch]);
                dec_out_handle[ch] = NULL;
            }
#else
            dma_free_coherent(NULL, rtk_dec_ao_buffer, dpcm->decOutData[ch], dpcm->phy_decOutData[ch]);
#endif
            dpcm->decOutData[ch] = NULL;
        }

#ifdef USE_ION_AUDIO_HEAP
        //printk("%s create dec_out_handle[%d]\n", __FUNCTION__, ch);
        dec_out_handle[ch] = ion_alloc(alsa_client, rtk_dec_ao_buffer, 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

        if (IS_ERR(dec_out_handle[ch])) {
            ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
            return bMallocSuccess;
        }

        if (ion_phys(alsa_client, dec_out_handle[ch], &dat, &len) != 0) {
            snd_realtek_hw_free_ring(runtime);
            printk("[malloc ch %d fail and terminate %s %d]\n", ch, __FUNCTION__, __LINE__);
            return bMallocSuccess;
        }

        dpcm->phy_decOutData[ch] = dat;
        dpcm->decOutData[ch] = ion_map_kernel(alsa_client, dec_out_handle[ch]);
#else
        void *addr = 0;

        addr = dma_alloc_coherent(NULL, rtk_dec_ao_buffer, &dpcm->phy_decOutData[ch], GFP_KERNEL);
        if(!addr)
        {
            snd_realtek_hw_free_ring(runtime);
            printk("[malloc ch %d fail and terminate %s %d]\n", ch, __FUNCTION__, __LINE__);
            return bMallocSuccess;
        }

        dpcm->decOutData[ch] = addr;
#endif

        dpcm->nRingSize = rtk_dec_ao_buffer;
        //printk("[test]AO Inring buffer ch %d (vir)address %x (phy)address %x\n", ch, dpcm->decOutData[ch], dpcm->phy_decOutData[ch]);
    }

    bMallocSuccess = 0; //Success
    return bMallocSuccess;
}

static int snd_realtek_hw_create_AI(snd_pcm_substream_t *substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

    if (snd_open_ai_count >= MAX_AI_DEVICES) 
    {
        ALSA_WARNING("[too more AI %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if(RPC_TOAGENT_CREATE_AI_AGENT(dpcm))
    {
        ALSA_WARNING("[err %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    snd_open_ai_count ++;
    return 0;
}

static int snd_realtek_hw_get_AI(snd_pcm_substream_t *substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

    if (snd_open_ai_count >= MAX_AI_DEVICES)
    {
        ALSA_WARNING("[too more AI %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if(RPC_TOAGENT_GET_AI_AGENT(dpcm))
    {
        ALSA_WARNING("[err %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    snd_open_ai_count ++;
    return 0;
}

// get AO flash pin ID
static int snd_realtek_hw_open(snd_pcm_substream_t *substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;

    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    if (snd_open_count >= MAX_PCM_SUBSTREAMS) {
        ALSA_WARNING("[opened audio stream count excess %d]\n", MAX_PCM_SUBSTREAMS);
        return -1;
    }

    // get ao flash pin ID
    if ((dpcm->AOpinID = RPC_TOAGENT_GET_AO_FLASH_PIN(dpcm)) < 0) {
        ALSA_WARNING("[can't get flash pin %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // init volume
    dpcm->volume = 31;
    
    snd_open_count ++;
    ALSA_VitalPrint("[ALSA Open AO AgentID = %d pinID = %d]\n", dpcm->AOAgentID, dpcm->AOpinID);
    return 0;
}

// check if AO exists
// return 0(success), 1(fail)
static int snd_realtek_hw_init(snd_card_RTK_pcm_t *dpcm) 
{
    //TRACE_CODE("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);

    if (dpcm->bHWinit != 0) 
        return 0;

    if (snd_realtek_hw_check_audio_ready()) 
    {
        return -1;
    }

    if (RPC_TOAGENT_CREATE_AO_AGENT(&dpcm->AOAgentID, AUDIO_ALSA_OUT))
    {
        ALSA_WARNING("[No AO agent %s %d]\n", __FUNCTION__, __LINE__);
        return -1;
    }
    dpcm->bHWinit = 1;

    return 0;
}

static int snd_realtek_hw_close(snd_card_RTK_pcm_t *dpcm)
{
	AUDIO_RPC_RINGBUFFER_HEADER RBuf;
	int ret = 0;
	int i;
	int channel_max = 8;

	/* re-initialize ring buffer with null ring */
	RBuf.instanceID = dpcm->AOAgentID;
	RBuf.pinID = dpcm->AOpinID;
	RBuf.readIdx = 0;
	RBuf.listSize = 0;
	for ( i = 0; i < channel_max; i++)
		RBuf.pRingBufferHeaderList[i] = 0;

	/* stop AO */
	ret = RPC_TOAGENT_INITRINGBUFFER_HEADER_SVC(&RBuf, channel_max);

	dec_out_msec = 0;
	return ret;
}

static int snd_realtek_hw_capture_free_ring(snd_pcm_runtime_t *runtime)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    int ch;

    printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

	switch(dpcm->source_in)
	{
		case ENUM_AIN_AUDIO_V2:
		case ENUM_AIN_AUDIO_V3:
		case ENUM_AIN_AUDIO_V4:
			break;
		default:
			// free AI in_ring
			for (ch = 0; ch < runtime->channels; ch++)
			{
				if(dpcm->pAIRingData[ch] != NULL)
				{
#ifdef USE_ION_AUDIO_HEAP
					if(alsa_client != NULL && enc_in_handle[ch] != NULL)
					{
						ion_unmap_kernel(alsa_client, enc_in_handle[ch]);
						ion_free(alsa_client, enc_in_handle[ch]);
						enc_in_handle[ch] = NULL;
					}
#else
					dma_free_coherent(NULL, RTK_ENC_AI_BUFFER_SIZE, dpcm->pAIRingData[ch], dpcm->phy_pAIRingData[ch]);
#endif
					dpcm->pAIRingData[ch] = NULL;
				}
			}
			break;
	}

	// free AI lpcm ring
	if(dpcm->nAIFormat == AUDIO_ALSA_FORMAT_16BITS_LE_LPCM ||
	dpcm->nAIFormat == AUDIO_ALSA_FORMAT_24BITS_LE_LPCM)
	{
#ifdef USE_ION_AUDIO_HEAP
		if(alsa_client != NULL && enc_lpcm_handle != NULL)
		{
			ion_unmap_kernel(alsa_client, enc_lpcm_handle);
			ion_free(alsa_client, enc_lpcm_handle);
			enc_lpcm_handle = NULL;
		}
#else
		dma_free_coherent(NULL, RTK_ENC_LPCM_BUFFER_SIZE, dpcm->pLPCMData, dpcm->phy_pLPCMData);
#endif
	}

#ifdef CAPTURE_USE_PTS_RING
	// free AI pts ring
	if(alsa_client != NULL && enc_pts_handle != NULL)
	{
		ion_unmap_kernel(alsa_client, enc_pts_handle);
		ion_free(alsa_client, enc_pts_handle);
		enc_pts_handle = NULL;
	}
#endif

	return 0;
}

static int snd_realtek_hw_free_ring (snd_pcm_runtime_t *runtime)
{
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
    int ch;

    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    for (ch = 0; ch < dpcm->last_channel; ch++)
    {
        if(dpcm->decOutData[ch] != NULL)
        {
#ifdef USE_ION_AUDIO_HEAP
            if(alsa_client != NULL && dec_out_handle[ch] != NULL)
            {
                ion_unmap_kernel(alsa_client, dec_out_handle[ch]);
                ion_free(alsa_client, dec_out_handle[ch]);
                dec_out_handle[ch] = NULL;
            }
#else
            dma_free_coherent(NULL, rtk_dec_ao_buffer, dpcm->decOutData[ch], dpcm->phy_decOutData[ch]);
#endif
            dpcm->decOutData[ch] = NULL;
        }
    }
    //TRACE_CODE("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    return 0;
}

static void snd_card_runtime_free(snd_pcm_runtime_t *runtime)
{
    snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	struct ion_handle *alsa_playback_handle_free = NULL;
	alsa_playback_handle_free = dpcm->inRingHandle;
    ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    
    //snd_realtek_hw_free_ring(runtime);
#ifdef USE_ION_AUDIO_HEAP
    if (alsa_client != NULL && alsa_playback_handle_free != NULL)
    {
        //printk("%s free handle %p \n", __FUNCTION__, alsa_playback_handle_free);
        ion_unmap_kernel(alsa_client, alsa_playback_handle_free);
        ion_free(alsa_client, alsa_playback_handle_free);
        alsa_playback_handle_free = NULL;
    }
#else
    dma_free_coherent(NULL, 4096, dpcm, dpcm->phy_addr);
#endif
    runtime->private_data = NULL;
}

static void snd_card_capture_runtime_free(snd_pcm_runtime_t *runtime)
{
    ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
#ifndef USE_ION_AUDIO_HEAP
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
#endif

#ifdef USE_ION_AUDIO_HEAP
    if(alsa_client != NULL && alsa_capture_handle != NULL)
    {
        printk("%s free alsa_capture_handle\n", __FUNCTION__);
        ion_unmap_kernel(alsa_client, alsa_capture_handle);
        ion_free(alsa_client, alsa_capture_handle);
        alsa_capture_handle = NULL;
    }
#else
    dma_free_coherent(NULL, 4096, dpcm, dpcm->phy_addr);
#endif
    runtime->private_data = NULL;
}

static int snd_card_playback_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = NULL;
	int ret = ENOMEM;
#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;
#endif

	printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
#if 0
	if(is_suspend)
	{
		ALSA_VitalPrint("[ALSA %s %d] suspend\n", __FUNCTION__, __LINE__);
		return ret;
	}
#endif

#ifdef USE_ION_AUDIO_HEAP
	alsa_playback_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);
	printk("%s create alsa_playback_handle %p\n", __FUNCTION__, alsa_playback_handle);

	if (IS_ERR(alsa_playback_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if (ion_phys(alsa_client, alsa_playback_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_playback_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
	dpcm->inRingHandle = alsa_playback_handle;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if(!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif

	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_runtime_free;

	// check if AO exists
	if (snd_realtek_hw_init(dpcm))
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEDIUM;
		goto fail;
	}

	memcpy(&runtime->hw, &snd_card_playback, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->nEOSState = SND_REALTEK_EOS_STATE_NONE;
	if (snd_realtek_hw_open(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *) (substream->pcm->card->private_data);

	// init dec_out_msec
	dec_out_msec = 0;

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	dpcm->hr_timer.function = &snd_card_timer_function;

#ifdef DEBUG_RECORD
	dpcm->ai_count = snd_open_count;
	if (dpcm->ai_count > 1){
		/* Create the file needs to after initalizing the sysem. */
		dpcm->fp = filp_open("/data/debug_record.wav", O_RDWR | O_CREAT, 0644);
		if (IS_ERR(dpcm->fp)){
			ALSA_WARNING("[create file error %s %d]\n", __FUNCTION__, __LINE__);
		}
		dpcm->pos =0;
	}
#endif

	spin_lock_init(&playback_lock);

	dpcm->card->mixer_volume[MIXER_ADDR_MASTER][0] = dpcm->card->mixer_volume[MIXER_ADDR_MASTER][1] = RPC_TOAGENT_GET_VOLUME(dpcm);

	ret = 0;

	if (g_ShareMemPtr == NULL)
	{
#ifdef USE_ION_AUDIO_HEAP
		//printk("%s create sharemem_handle\n", __FUNCTION__);
		sharemem_handle = ion_alloc(alsa_client, SHARE_MEM_SIZE, 32, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

		if (IS_ERR(sharemem_handle)) {
			ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		if (ion_phys(alsa_client, sharemem_handle, &g_ShareMemPtr_dat, &len) != 0)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		g_ShareMemPtr = ion_map_kernel(alsa_client, sharemem_handle);
		//printk("phy %p vir %p\n", g_ShareMemPtr_dat, g_ShareMemPtr);
#else
		g_ShareMemPtr = dma_alloc_coherent(NULL, SHARE_MEM_SIZE, &g_ShareMemPtr_dat, GFP_KERNEL);
		if(!g_ShareMemPtr)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}
		//printk("g_ShareMemPtr %p\n", g_ShareMemPtr);
#endif
		memset(g_ShareMemPtr, 0, SHARE_MEM_SIZE);
		//RPC_TOAGENT_PUT_SHARE_MEMORY((void *)g_ShareMemPtr_dat, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
    }

	if (g_ShareMemPtr2 == NULL)
	{
#ifdef USE_ION_AUDIO_HEAP
		//printk("%s create sharemem_handle\n", __FUNCTION__);
		sharemem_handle2 = ion_alloc(alsa_client, SHARE_MEM_SIZE_LATENCY, 32, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

		if (IS_ERR(sharemem_handle2)) {
			ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		if (ion_phys(alsa_client, sharemem_handle2, &g_ShareMemPtr_dat2, &len) != 0)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		g_ShareMemPtr2 = ion_map_kernel(alsa_client, sharemem_handle2);
		//printk("phy %p vir %p\n", g_ShareMemPtr_dat, g_ShareMemPtr);
#else
		g_ShareMemPtr2 = dma_alloc_coherent(NULL, SHARE_MEM_SIZE_LATENCY, &g_ShareMemPtr_dat2, GFP_KERNEL);
		if(!g_ShareMemPtr2)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}
		//printk("g_ShareMemPtr %p\n", g_ShareMemPtr);
#endif
		memset(g_ShareMemPtr2, 0, SHARE_MEM_SIZE_LATENCY);
		//move to snd_card_playback_prepare to set RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY
		//RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY((void *)g_ShareMemPtr_dat, (void *)g_ShareMemPtr_dat2, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
	}

	if (g_ShareMemPtr3 == NULL)
	{
#ifdef USE_ION_AUDIO_HEAP
		//printk("%s create sharemem_handle\n", __FUNCTION__);
		sharemem_handle3 = ion_alloc(alsa_client, SHARE_MEM_SIZE_LATENCY, 32, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

		if (IS_ERR(sharemem_handle3)) {
			ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		if (ion_phys(alsa_client, sharemem_handle3, &g_ShareMemPtr_dat3, &len) != 0)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}

		g_ShareMemPtr3 = ion_map_kernel(alsa_client, sharemem_handle3);
		//printk("phy %p vir %p\n", g_ShareMemPtr_dat, g_ShareMemPtr);
#else
		g_ShareMemPtr3 = dma_alloc_coherent(NULL, SHARE_MEM_SIZE_LATENCY, &g_ShareMemPtr_dat3, GFP_KERNEL);
		if(!g_ShareMemPtr3)
		{
			printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
			goto fail;
		}
		//printk("g_ShareMemPtr %p\n", g_ShareMemPtr);
#endif
		memset(g_ShareMemPtr3, 0, SHARE_MEM_SIZE_LATENCY);
	}

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if (alsa_client != NULL && alsa_playback_handle != NULL) {
		printk("%s free alsa_playback_handle\n", __FUNCTION__);
		ion_unmap_kernel(alsa_client, alsa_playback_handle);
		ion_free(alsa_client, alsa_playback_handle);
		alsa_playback_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

// it's for HDMI-RX
static int snd_card_capture_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	printk("[ALSA %s %s %d]\n",substream->pcm->name, __FUNCTION__, __LINE__);

	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_HDMIRX;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	//spin_lock_init(&dpcm->nLock);
	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		printk("%s free alsa_capture_handle\n", __FUNCTION__);
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

// it's for HDMI-RX nonpcm in
static int snd_card_capture_nonpcm_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	printk("[ALSA %s %s %d]\n",substream->pcm->name, __FUNCTION__, __LINE__);

	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	//spin_lock_init(&dpcm->nLock);
	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		printk("%s free alsa_capture_handle\n", __FUNCTION__);
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

// it's for I2S
static int snd_card_capture_i2s_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	printk("[ALSA %s %s %d]\n",substream->pcm->name, __FUNCTION__, __LINE__);

	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_I2S;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	//spin_lock_init(&dpcm->nLock);
	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		printk("%s free alsa_capture_handle\n", __FUNCTION__);
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

// it's for audio in
#ifdef CONFIG_REALTEK_FL3236
extern void fl3236_enable_light(void);
#endif
static int snd_card_capture_audio_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture_audio, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_AUDIO;

	// get AI, AI is already
	if (snd_realtek_hw_get_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

#ifdef CONFIG_REALTEK_FL3236
	fl3236_enable_light();
#endif

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

static int snd_card_capture_audio_v2_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture_audio, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_AUDIO_V2;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

static int snd_card_capture_audio_v3_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture_audio, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_AUDIO_V3;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

static int snd_card_capture_audio_v4_open(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = NULL;
	int ret = ENOMEM;

#ifdef USE_ION_AUDIO_HEAP
	ion_phys_addr_t dat;
	size_t len;

	if(alsa_capture_handle)
	{
		ALSA_WARNING("ERR more than 1 capture instance!!!\n");
	}

	alsa_capture_handle = ion_alloc(alsa_client, sizeof(snd_card_RTK_capture_pcm_t), 1024, RTK_PHOENIX_ION_HEAP_AUDIO_MASK, AUDIO_ION_FLAG);

	if (IS_ERR(alsa_capture_handle)) {
		ALSA_WARNING("[%s %d ion_alloc fail]\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	if(ion_phys(alsa_client, alsa_capture_handle, &dat, &len) != 0) {
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = ion_map_kernel(alsa_client, alsa_capture_handle);
	memset(dpcm, 0, len);
	dpcm->phy_addr = dat;
#else
	dma_addr_t dat;
	void *p;

	p = dma_alloc_coherent(NULL, sizeof(snd_card_RTK_pcm_t), &dat, GFP_KERNEL);
	if (!p)
	{
		printk("[%s %d] alloc memory faild\n", __FUNCTION__, __LINE__);
		goto fail;
	}

	dpcm = p;
	dpcm->phy_addr = dat;
#endif
	// private data
	runtime->private_data = dpcm;
	runtime->private_free = snd_card_capture_runtime_free;

	memcpy(&runtime->hw, &snd_card_mars_capture_audio, sizeof(struct snd_pcm_hardware));
	dpcm->substream = substream;
	dpcm->source_in = ENUM_AIN_AUDIO_V4;

	// create AI
	if (snd_realtek_hw_create_AI(substream) < 0)
	{
		ALSA_WARNING("[error %s %d]\n", __FUNCTION__, __LINE__);
		ret = -ENOMEM;
		goto fail;
	}

	dpcm->card = (RTK_snd_card_t *)(substream->pcm->card->private_data);

	// init hr timer
	hrtimer_init(&dpcm->hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	spin_lock_init(&capture_lock);

	ALSA_VitalPrint("[ALSA %s END]\n", __FUNCTION__);

	ret = 0;

	return ret;
fail:

#ifdef USE_ION_AUDIO_HEAP
	if(alsa_client != NULL && alsa_capture_handle != NULL)
	{
		ion_unmap_kernel(alsa_client, alsa_capture_handle);
		ion_free(alsa_client, alsa_capture_handle);
		alsa_capture_handle = NULL;
		dpcm = NULL;
	}
#else
	if(p)
	{
		dma_free_coherent(NULL, sizeof(snd_card_RTK_capture_pcm_t), p, dat);
		dpcm = NULL;
	}
#endif

	return ret;
}

#ifdef CONFIG_REALTEK_FL3236
extern void fl3236_disable_light(void);
#endif
static int snd_card_capture_close_audio(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	ktime_t remaining;
	int ret = -1;

	if(snd_open_ai_count)
	{
		if (RPC_TOAGENT_AI_DISCONNECT_ALSA_AUDIO(runtime))
		{
			ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
			goto exit;
		}
	}

	snd_realtek_hw_capture_destroy_LPCM_ringheader_of_Audio(runtime);
#ifdef CONFIG_REALTEK_FL3236
	fl3236_disable_light();
#endif

	/* destroy the hr timer */
	remaining = hrtimer_get_remaining(&dpcm->hr_timer);
	if(ktime_to_ns(remaining) > 0)
		ndelay(ktime_to_ns(remaining));
	ret = hrtimer_cancel(&dpcm->hr_timer);
	if (ret){
		ALSA_WARNING("The timer still alive...\n");
		goto exit;
	}

	ret = 0;
exit:

	snd_realtek_hw_capture_free_ring(runtime);

	if(snd_open_ai_count > 0)
		snd_open_ai_count--;
	return ret;
}

static int snd_card_capture_close(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	ktime_t remaining;
	int ret = -1;

	printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

	if(snd_open_ai_count)
	{
		if (RPC_TOAGENT_DESTROY_AI_FLOW_SVC(dpcm->AIAgentID))
		{
			ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
			goto exit;
		}
	}

	/* destroy the hr timer */
	remaining = hrtimer_get_remaining(&dpcm->hr_timer);
	if(ktime_to_ns(remaining) > 0)
		ndelay(ktime_to_ns(remaining));
	ret = hrtimer_cancel(&dpcm->hr_timer);
	if (ret){
		ALSA_WARNING("The timer still alive...\n");
		goto exit;
	}

	ret = 0;
exit:

	snd_realtek_hw_capture_free_ring(runtime);

	if(snd_open_ai_count > 0)
		snd_open_ai_count--;
	return ret;
}

static int snd_card_playback_close(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	AUDIO_RPC_SENDIO sendio;
	ktime_t remaining;
	int ret = 0;

	printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

	// DHCKYLIN-2822 disable get_latency before destroy decoder instance
	if (dpcm->DECAgentID) {
		RPC_TOAGENT_PUT_SHARE_MEMORY(NULL, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
		RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY(NULL, NULL, 0, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
	}

	if (dpcm->AOpinID) {
		/* stop decoder */
		if(dpcm->DECAgentID)
			RPC_TOAGENT_STOP_SVC(dpcm->DECAgentID);

		// AO pause
		if (RPC_TOAGENT_PAUSE_SVC(dpcm->AOAgentID | dpcm->AOpinID)) {
			ret = -1;
			goto exit;
		}

		if (dpcm->bInitRing != 0) {
			// decoder flush
			sendio.instanceID = dpcm->DECAgentID;
			sendio.pinID = dpcm->DECpinID;

			if (RPC_TOAGENT_FLUSH_SVC(&sendio)) {
				ret = -1;
				goto exit;
			}
			snd_realtek_hw_close(dpcm);
		}

		/* destroy decoder instance if exist */
		if (dpcm->DECAgentID)
			RPC_TOAGENT_DESTROY_SVC(dpcm->DECAgentID);
	}
	else {
		return -1;
	}

#ifdef DEBUG_RECORD
	/* Close the record file */
	if (dpcm->ai_count > 1)
		filp_close(dpcm->fp,NULL);
#endif

	/* destroy the hr timer */
	remaining = hrtimer_get_remaining(&dpcm->hr_timer);
	if(ktime_to_ns(remaining) > 0)
		ndelay(ktime_to_ns(remaining));
	ret = hrtimer_cancel(&dpcm->hr_timer);
	if (ret){
		ALSA_WARNING("The timer still alive...\n");
		goto exit;
	}

exit:
	RPC_TOAGENT_RELEASE_AO_FLASH_PIN(dpcm);
	snd_open_count--;

	snd_realtek_hw_free_ring(runtime);

	if ((g_ShareMemPtr || g_ShareMemPtr2 || g_ShareMemPtr3) && snd_open_count == 0) {
#ifdef USE_ION_AUDIO_HEAP
		if (alsa_client != NULL && sharemem_handle != NULL) {
			//printk("%s destory sharemem_handle\n", __FUNCTION__);
			ion_unmap_kernel(alsa_client, sharemem_handle);
			ion_free(alsa_client, sharemem_handle);
			sharemem_handle = NULL;
		}

		if (alsa_client != NULL && sharemem_handle2 != NULL) {
			ion_unmap_kernel(alsa_client, sharemem_handle2);
			ion_free(alsa_client, sharemem_handle2);
			sharemem_handle2 = NULL;
		}

		if (alsa_client != NULL && sharemem_handle3 != NULL) {
			ion_unmap_kernel(alsa_client, sharemem_handle3);
			ion_free(alsa_client, sharemem_handle3);
			sharemem_handle3 = NULL;
		}
#else
		dma_free_coherent(NULL, 4096, g_ShareMemPtr, g_ShareMemPtr_dat);
		dma_free_coherent(NULL, 4096, g_ShareMemPtr2, g_ShareMemPtr_dat2);
		dma_free_coherent(NULL, 4096, g_ShareMemPtr3, g_ShareMemPtr_dat3);
#endif
		g_ShareMemPtr = NULL;
		g_ShareMemPtr2 = NULL;
		g_ShareMemPtr3 = NULL;
    }

	return ret;
}

static unsigned int snd_capture_monitor_delay(struct snd_pcm_substream *substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    unsigned int sample_rate = runtime->rate;
    unsigned int ret = 0;
    unsigned long base, limit, rp, wp;
    unsigned int pcm_size;  // unit: sample
    unsigned int pcm_latency;   // unit ms
    unsigned int lpcm_size; // unit: sample
    unsigned int lpcm_latency;  // unit:ms

    // calculate the size of PCM (input of AI)
    base = (unsigned long)(dpcm->nAIRing_LE[0].beginAddr);
    limit = (unsigned long)(dpcm->nAIRing_LE[0].beginAddr + dpcm->nAIRing_LE[0].size);
    wp = (unsigned long)(ntohl(dpcm->nAIRing[0].writePtr));
    rp = (unsigned long)(ntohl(dpcm->nAIRing[0].readPtr[0]));
    pcm_size = ring_valid_data(base, limit, rp, wp) >> 2;
    //printk(KERN_ALERT "AI pcm %x %x %x %x\n", (int)base, (int)limit, (int)wp, (int)rp);

    // calculate the size of LPCM (output of AI)
    base = (unsigned long)(dpcm->nLPCMRing_LE.beginAddr);
    limit = (unsigned long)(dpcm->nLPCMRing_LE.beginAddr + dpcm->nLPCMRing_LE.size);
    wp = (unsigned long)(ntohl(dpcm->nLPCMRing.writePtr));
    rp = (unsigned long)(ntohl(dpcm->nLPCMRing.readPtr[0]));
    lpcm_size = ring_valid_data(base, limit, rp, wp);
    switch(dpcm->nAIFormat)
    {
        case AUDIO_ALSA_FORMAT_16BITS_LE_LPCM:
            lpcm_size >>= 2;    // 2ch, 2bytes per sample
            break;
        case AUDIO_ALSA_FORMAT_24BITS_LE_LPCM:
            lpcm_size /= 6; // 2ch, 3bytes per sample
            break;
        default:
            ALSA_WARNING("capture err, %d @ %s %d\n", dpcm->nAIFormat, __FUNCTION__, __LINE__);
    }
    //printk(KERN_ALERT "AI lpcm %x %x %x %x\n", (int)base, (int)limit, (int)wp, (int)rp);

    // calculate leatency
    pcm_latency = (pcm_size * 1000) / sample_rate;
    lpcm_latency = (lpcm_size * 1000) / sample_rate;
    ret = pcm_latency + lpcm_latency;
    //printk(KERN_ALERT "AI latency %x + %x = %x\n", pcm_latency, lpcm_latency, ret);

    return ret;
}

static int snd_card_capture_ioctl(struct snd_pcm_substream *substream,  unsigned int cmd, void *arg)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	int delay_ms;
	unsigned int *volume = NULL;

    TRACE_CODE("[%s %s %d cmd %d]\n", __FILE__, __FUNCTION__, __LINE__, cmd);
    ALSA_VitalPrint("[%s %d cmd %d]\n",__FUNCTION__, __LINE__, cmd);

    switch (cmd) 
    {
        case SNDRV_PCM_IOCTL_VOLUME_SET:
			volume = (unsigned int *)arg;
			return RPC_TOAGENT_SET_SOFTWARE_AI_FLASH_VOLUME(dpcm, *volume);
            break;
        case SNDRV_PCM_IOCTL_VOLUME_GET:
            break;
        case SNDRV_PCM_IOCTL_GET_FW_DELAY:
            delay_ms = snd_capture_monitor_delay(substream);
            put_user(delay_ms, (unsigned int*) arg);
            break;
        default:
            return snd_pcm_lib_ioctl(substream, cmd, arg);
            break;
    }
    return 0;
}

static int snd_card_playback_ioctl(struct snd_pcm_substream *substream,  unsigned int cmd, void *arg)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	struct AUDIO_RPC_EQUALIZER_MODE *equalizer_mode;

	//printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

	switch (cmd)
	{
		case SNDRV_PCM_IOCTL_VOLUME_SET:
		{
			printk("[ALSA SET VOLUME]\n");
			get_user(dpcm->volume, (int *) arg);
			if (dpcm->volume < 0)
				dpcm->volume = 0;
			if (dpcm->volume > 31)
				dpcm->volume = 31;
			RPC_TOAGENT_SET_AO_FLASH_VOLUME(substream);
			break;
		}
		case SNDRV_PCM_IOCTL_VOLUME_GET:
		{
			put_user(dpcm->volume, (int *) arg);
			break;
		}
		case SNDRV_PCM_IOCTL_GET_LATENCY:
		{
			int mLatency = 0;

			mLatency = snd_monitor_audio_data_queue_new(substream);

			put_user(mLatency, (int *) arg);
			break;
		}
		case SNDRV_PCM_IOCTL_GET_FW_DELAY:
		{
			int mLatency = 0;
			snd_pcm_sframes_t n = 0;

			mLatency = snd_monitor_audio_data_queue_new(substream);

			n = (mLatency * runtime->rate) / 1000;
			put_user(n, (snd_pcm_sframes_t *) arg);
			break;
		}
		case SNDRV_PCM_IOCTL_EQ_SET:
		{
			equalizer_mode = kmalloc(sizeof(struct AUDIO_RPC_EQUALIZER_MODE), GFP_KERNEL);
			if(copy_from_user((void *)equalizer_mode, (void *)arg, sizeof(struct AUDIO_RPC_EQUALIZER_MODE)))
				printk("%s %d copy data fail\n",__func__, __LINE__);
			RPC_TOAGENT_SET_EQ(dpcm, equalizer_mode);
			break;
		}
		default:
			return snd_pcm_lib_ioctl(substream, cmd, arg);
			break;
	}
	return 0;
}

static snd_pcm_uframes_t snd_card_capture_pointer(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	snd_pcm_uframes_t ret = 0;

	// update hw_ptr
	ret = dpcm->nTotalWrite % runtime->buffer_size;
	return ret;
}

static snd_pcm_uframes_t snd_card_playback_pointer(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	snd_pcm_uframes_t ret = 0;

	// update runtime->status->hw_ptr
	ret = dpcm->nTotalRead % runtime->buffer_size;
	return ret;
}

static int snd_card_capture_prepare_32bits_BE(snd_pcm_substream_t * substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

    TRACE_CODE("[ @ %s %d]\n", __FUNCTION__, __LINE__);
    // malloc AI ring buf
    if(snd_realtek_hw_capture_malloc_ring(runtime))
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }

    // init AI ring header
    if(snd_realtek_hw_capture_init_ringheader_of_AI(runtime))
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }

	// config for different protocol
	if (dpcm->source_in == ENUM_AIN_HDMIRX)
		RPC_TOAGENT_AI_CONFIG_HDMI_RX_IN(dpcm); // config HDMI-RX
	else if (dpcm->source_in == ENUM_AIN_I2S)
		RPC_TOAGENT_AI_CONFIG_I2S_IN(dpcm); // config I2S

    // private info
    if(RPC_TOAGENT_AI_CONNECT_ALSA(runtime))
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }

    // configure
#if 0
    if(RPC_TOAGENT_CONFIGURE_AI_HW(runtime))
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }
#endif

    // run
    if(snd_realtek_hw_capture_run(dpcm))
    {
        ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }

    dpcm->nStartTimer.function = (void (*) (unsigned long))snd_card_capture_timer_function;

    return 0;
}

static int snd_card_capture_prepare_LPCM_audio(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

	printk("[ @ %s %d]\n", __FUNCTION__, __LINE__);
	// malloc AI ring buf
	if(snd_realtek_hw_capture_malloc_ring(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// malloc LPCM ring buf
	if(snd_realtek_hw_capture_malloc_lpcm_ring(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// init LPCM ring header of AI
	if(snd_realtek_hw_capture_init_LPCM_ringheader_of_AI(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// private info
	if(RPC_TOAGENT_AI_CONNECT_ALSA(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	dpcm->hr_timer.function = &snd_card_capture_lpcm_timer_function;

	return 0;
}

static int snd_card_capture_prepare_LPCM(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

	printk("[ @ %s %d]\n", __FUNCTION__, __LINE__);

	switch(dpcm->source_in)
	{
		case ENUM_AIN_AUDIO_V2:
		case ENUM_AIN_AUDIO_V3:
		case ENUM_AIN_AUDIO_V4:
			break;
		default:
			// malloc AI ring buf
			if(snd_realtek_hw_capture_malloc_ring(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}

			// init ring header of AI
			if(snd_realtek_hw_capture_init_ringheader_of_AI(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}

#ifdef CAPTURE_USE_PTS_RING
			// malloc PTS ring buf
			if(snd_realtek_hw_capture_malloc_pts_ring(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}

			// init PTS ring header of AI
			if(snd_realtek_hw_capture_init_PTS_ringheader_of_AI(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}
#endif
			break;
	}

	// malloc LPCM ring buf
	if(snd_realtek_hw_capture_malloc_lpcm_ring(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// init LPCM ring header of AI
	if(snd_realtek_hw_capture_init_LPCM_ringheader_of_AI(runtime))
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// config for different protocol
	switch(dpcm->source_in)
	{
		case ENUM_AIN_AUDIO_V2:
		case ENUM_AIN_AUDIO_V3:
		case ENUM_AIN_AUDIO_V4:
			// For audio processing flow, doing connect alsa before config audio v2 or v3
			if(RPC_TOAGENT_AI_CONNECT_ALSA(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}
			RPC_TOAGENT_AI_CONFIG_AUDIO_IN(dpcm); // config audio v2 or v3
			break;
		case ENUM_AIN_HDMIRX:
			RPC_TOAGENT_AI_CONFIG_HDMI_RX_IN(dpcm); // config HDMI-RX
			break;
		case ENUM_AIN_I2S:
			RPC_TOAGENT_AI_CONFIG_I2S_IN(dpcm); // config I2S
			break;
		default:
			break;
	}

	// private info
	switch(dpcm->source_in)
	{
		case ENUM_AIN_AUDIO_V2:
		case ENUM_AIN_AUDIO_V3:
		case ENUM_AIN_AUDIO_V4:
			break;
		default:
			if(RPC_TOAGENT_AI_CONNECT_ALSA(runtime))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}
			break;
	}

	// run
	switch(dpcm->source_in)
	{
		case ENUM_AIN_AUDIO_V2:
		case ENUM_AIN_AUDIO_V3:
		case ENUM_AIN_AUDIO_V4:
			break;
		default:
			if(snd_realtek_hw_capture_run(dpcm))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}
			break;
	}

	dpcm->hr_timer.function = &snd_card_capture_lpcm_timer_function;

	return 0;
}

static int snd_card_capture_prepare(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;

	ALSA_WARNING("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
	if(runtime->status->state == SNDRV_PCM_STATE_XRUN)
	{
		ALSA_WARNING("[SNDRV_PCM_STATE_XRUN appl_ptr %d hw_ptr %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
	}

	/* Setup the hr timer using ktime */
	dpcm->ktime = ktime_set(0 ,(runtime->period_size * 1000) / runtime->rate * 1000 * 1000); //ms to ns

	printk("\n\n\n");
	printk("[capture : rate %d channels %d format %x\n", runtime->rate, runtime->channels, runtime->format);
	printk("   period_size %d periods %d\n", (int)runtime->period_size, (int)runtime->periods);
	printk("   buffer_size %d period_jiffies %d\n", (int)runtime->buffer_size, (int)dpcm->nPeriodJiffies);
	printk("   start_threshold %d stop_threshold %d]\n", (int)runtime->start_threshold, (int)runtime->stop_threshold);
	printk("\n\n\n");

	switch (runtime->access)
	{
		case SNDRV_PCM_ACCESS_MMAP_INTERLEAVED:
		case SNDRV_PCM_ACCESS_RW_INTERLEAVED:
			switch(runtime->format)
			{
				case SNDRV_PCM_FORMAT_S16_LE:
					TRACE_CODE("[SNDRV_PCM_FORMAT_S16_LE]\n");
					dpcm->nAIFormat = AUDIO_ALSA_FORMAT_16BITS_LE_LPCM;
					break;
				case SNDRV_PCM_FORMAT_S24_LE:
					TRACE_CODE("[SNDRV_PCM_FORMAT_S24_LE]\n");
					ALSA_WARNING("[ALSA write .wav header err]\n");
					printk("[ALSA byte #32 of .wav should be 8=>6 manually]\n");
					dpcm->nAIFormat = AUDIO_ALSA_FORMAT_24BITS_LE_LPCM;
					break;
				default:
					ALSA_WARNING("[unsupport format %d %s %d]\n", runtime->format
						, __FUNCTION__, __LINE__);
					return -1;
			}
			break;
		case SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED:
		case SNDRV_PCM_ACCESS_RW_NONINTERLEAVED:
		default:
			ALSA_WARNING("[unsupport access @ %s %d]\n", __FUNCTION__, __LINE__);
			return -1;
	}

	if(dpcm->bInitRing)
	{
		dpcm->nTotalWrite = 0;
		ALSA_WARNING("[Re-Prepare %d %d %s %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr, __FUNCTION__, __LINE__);
		return 0;
	}

	dpcm->nPeriodBytes = frames_to_bytes(runtime, runtime->period_size);
	dpcm->nFrameBytes = frames_to_bytes(runtime, 1);

	switch(dpcm->nAIFormat)
	{
		case AUDIO_ALSA_FORMAT_32BITS_BE_PCM:
			ALSA_WARNING("ALSA: unsupport @ %s %d\n", __FUNCTION__, __LINE__);
			if(snd_card_capture_prepare_32bits_BE(substream))
			{
				ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
				return -ENOMEM;
			}
			break;
		case AUDIO_ALSA_FORMAT_16BITS_LE_LPCM:
		case AUDIO_ALSA_FORMAT_24BITS_LE_LPCM:
			if(dpcm->source_in == ENUM_AIN_AUDIO){
				if(snd_card_capture_prepare_LPCM_audio(substream))
				{
					ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
					return -ENOMEM;
				}
			}else{
				if(snd_card_capture_prepare_LPCM(substream))
				{
					ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
					return -ENOMEM;
				}
			}
			break;
		default:
			ALSA_WARNING("[ALSA err %s %d]\n", __FUNCTION__, __LINE__);
			break;
	}

	dpcm->bInitRing = 1;

	return 0;
}

static int snd_card_playback_prepare(snd_pcm_substream_t * substream)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	printk("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

	if (is_suspend) {
		ALSA_WARNING("[ALSA %s %d] suspend\n", __FUNCTION__, __LINE__);
		return 0;
	}

	if (runtime->status->state == SNDRV_PCM_STATE_XRUN) {
		ALSA_WARNING("[SNDRV_PCM_STATE_XRUN appl_ptr %d hw_ptr %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
	}

	/* Setup the hr timer using ktime .
	 * For more precise compute the ktime in us.
	 */
	dpcm->ktime = ktime_set(0 ,(runtime->period_size * 1000) * 1000 / runtime->rate * 1000); //ms to ns

	if (dpcm->bInitRing) {
		/* Reset the information about playback.
		 * nPreHWPtr will influence the next information update in timer function.
		 */
		dpcm->nHWReadSize = 0;
		dpcm->nTotalRead = 0;
		dpcm->nTotalWrite = 0;
		dpcm->nPreHWPtr = 0;
		dpcm->nPre_appl_ptr = 0;
		/*	DHCKYLIN-2193:
			1.  pasue and stop AO and decoder, then destory the decoder for re-sending NewFormat.
			2.  re-send NewFormat cmd to audio f/w when alsa is reconfigured.
		 */
		snd_realtek_reprepare(runtime);
		printk("[Re-Prepare %d %d %s %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr, __FUNCTION__, __LINE__);
	}

	printk("[======START======]\n");
	printk("[playback : rate %d channels %d]\n", runtime->rate, runtime->channels);
	printk("[period_size %d periods %d]\n", (int)runtime->period_size, (int)runtime->periods);
	printk("[buffer_size %d ktime %d]\n", (int)runtime->buffer_size, (int)ktime_to_ns(dpcm->ktime));
	printk("[start_threshold %d stop_threshold %d]\n", (int)runtime->start_threshold, (int)runtime->stop_threshold);
	printk("[runtime->access %d]\n", runtime->access);
	printk("[runtime->format %d]\n", runtime->format);
	printk("[runtime->frame_bits %d]\n", runtime->frame_bits);
	printk("[runtime->sample_bits %d]\n", runtime->sample_bits);
	printk("[runtime->silence_threshold %d]\n", (int)runtime->silence_threshold);
	printk("[runtime->silence_size %d]\n", (int)runtime->silence_size);
	printk("[runtime->boundary %d]\n", (int)runtime->boundary);
	printk("[runtime->min_align %d]\n", (int)runtime->min_align);
	printk("[runtime->hw_ptr_base %x]\n", (unsigned int)runtime->hw_ptr_base);
	printk("[runtime->dma_area %x]\n", (unsigned int)(uintptr_t)runtime->dma_area);
	printk("[======END======]\n");

	dpcm->nPeriodBytes = frames_to_bytes(runtime, runtime->period_size);

	// create decoder agent
	if (RPC_TOAGENT_CREATE_DECODER_AGENT(&dpcm->DECAgentID, &dpcm->DECpinID)) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	if (g_ShareMemPtr != NULL && g_ShareMemPtr2 != NULL) {
		printk("to set latency of DECAgentID %d  \n", dpcm->DECAgentID);
		RPC_TOAGENT_PUT_SHARE_MEMORY_LATENCY((void *)g_ShareMemPtr_dat, (void *)g_ShareMemPtr_dat2, dpcm->DECAgentID, ENUM_PRIVATEINFO_AUDIO_GET_SHARE_MEMORY_FROM_ALSA);
	}

	// malloc ao_inring
	if (snd_realtek_hw_malloc_ring(runtime)) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// init ringheader of decoder_outring and AO_inring
	if (snd_realtek_hw_init_ringheader_of_DEC_AO(runtime)) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// connet decoder and AO by RPC
	if (snd_realtek_hw_init_connect_decoder_ao(dpcm)) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// 1. init decoder in_ring
	// 2. init decoder inband ring
	if (snd_realtek_hw_init_decoder_ring(runtime)) {
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	// AO pause
	// decoder pause
	// decoder run
	// decoder flush
	// write decoder info into inband of decoder
	if (snd_realtek_hw_init_decoder_info(runtime)) {
		ALSA_WARNING("[%s %d]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	if (snd_realtek_hw_resume(dpcm)) {
		ALSA_WARNING("[%s %d]\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}

	dpcm->last_channel = runtime->channels;
	dpcm->bInitRing = 1;

	return 0;
}

static long snd_card_get_ring_data(RINGBUFFER_HEADER *pRing_BE, RINGBUFFER_HEADER *pRing_LE)
{
    unsigned long base, limit, rp, wp, data_size;

    base = (unsigned long)pRing_LE->beginAddr;
    limit= (unsigned long)(pRing_LE->beginAddr + pRing_LE->size);
    //wp = (long)SND_UNCACHE_ADDRESS(ntohl(pRing_BE->writePtr));
    //rp = (long)SND_UNCACHE_ADDRESS(ntohl(pRing_BE->readPtr[0]));
    wp = (unsigned long)(ntohl(pRing_BE->writePtr));
    rp = (unsigned long)(ntohl(pRing_BE->readPtr[0]));
    //printk("[�� b %x l %x r %x w %x]\n", base, limit, rp, wp);
    data_size = ring_valid_data(base, limit, rp, wp);
    return data_size;
}

// copy data from ring(AI) to dma_buf
#define COPY_FUNC(nFrameSize, p, pRingRp) \
{\
    int i,temp;\
    for(i=0 ; i<nFrameSize ; ++i)\
    {\
        temp = (int)(*pRingRp[0]);\
        temp = ENDIAN_CHANGE(temp);\
        *p = (short)(temp >> 9);\
        p++;\
        temp = (int)(*pRingRp[1]);\
        temp = ENDIAN_CHANGE(temp);\
        *p = (short)(temp >> 9);\
        p++;\
        pRingRp[0]++;\
        pRingRp[1]++;\
    }\
}

// copy data from AI_ring to dma_buf
static void snd_card_capture_copy(snd_pcm_runtime_t *runtime, long nPeriodCount)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    snd_pcm_uframes_t nFrameSize = nPeriodCount * runtime->period_size;
    snd_pcm_uframes_t dma_wp = dpcm->nTotalWrite % runtime->buffer_size;
    snd_pcm_uframes_t wrap_size = runtime->buffer_size - dma_wp;
    int *pRingRp[2];    // kernel virtual address
    unsigned long nRingLimit[2];    // kernel virtual address
    unsigned long temp;
    int i, loop0, loop1;
    short *p = NULL;

    for(i=0 ; i<2 ; ++i)
    {
        temp = (unsigned long)dpcm->pAIRingData[i];
        temp += (dpcm->nAIRing_LE[i].readPtr[0] - dpcm->nAIRing_LE[i].beginAddr);
        pRingRp[i] = (int *)temp;        
        nRingLimit[i] = (unsigned long)(dpcm->pAIRingData[i]) + (unsigned long)dpcm->nAIRing_LE[i].size;
    }
    
    if(nFrameSize > wrap_size)
    {
        p = (short *)(runtime->dma_area + LPCM_2CH_16BITS * dma_wp);
        if((unsigned long)(pRingRp[0] + wrap_size) > nRingLimit[0])
        {
            loop0 = (nRingLimit[0] - (unsigned long)pRingRp[0]) >> 2;
            loop1 = wrap_size - loop0;
            COPY_FUNC(loop0, p, pRingRp);
            pRingRp[0] = (int *)dpcm->pAIRingData[0];
            pRingRp[1] = (int *)dpcm->pAIRingData[1];
            COPY_FUNC(loop1, p, pRingRp);
        }
        else
        {
            COPY_FUNC(wrap_size, p, pRingRp);
        }

        p = (short *)(runtime->dma_area);
        nFrameSize -= wrap_size;
        if((unsigned long)(pRingRp[0] + nFrameSize) > nRingLimit[0])
        {
            loop0 = (nRingLimit[0] - (unsigned long)pRingRp[0]) >> 2;
            loop1 = nFrameSize - loop0;
            COPY_FUNC(loop0, p, pRingRp);
            pRingRp[0] = (int *)dpcm->pAIRingData[0];
            pRingRp[1] = (int *)dpcm->pAIRingData[1];
            COPY_FUNC(loop1, p, pRingRp);
        }
        else
        {
            COPY_FUNC(nFrameSize, p, pRingRp);
        }
    }
    else
    {
        p = (short *)(runtime->dma_area + LPCM_2CH_16BITS * dma_wp);
        if((unsigned long)(pRingRp[0] + nFrameSize) > nRingLimit[0])
        {
            loop0 = (nRingLimit[0] - (unsigned long)pRingRp[0]) >> 2;
            loop1 = nFrameSize - loop0;
            COPY_FUNC(loop0, p, pRingRp);
            pRingRp[0] = (int *)dpcm->pAIRingData[0];
            pRingRp[1] = (int *)dpcm->pAIRingData[1];
            COPY_FUNC(loop1, p, pRingRp);
        }
        else
        {
            COPY_FUNC(nFrameSize, p, pRingRp);
        }
    }
}

static long ring_memcpy2_buf(char* buf,unsigned long base, unsigned long limit, unsigned long ptr, unsigned int size)
{
	if (ptr + size <= limit)
	{					
		memcpy(buf,(char*)ptr,size);			
	}
	else
	{
		int i = limit-ptr;
		memcpy((char*)buf,(char*)ptr,i);
		memcpy((char*)(buf+i),(char*)base,size-i);
	}
	
	ptr += size;
	if (ptr >= limit)
	{
		ptr = base + (ptr-limit);
	}	
	return ptr;
}

uint64_t snd_card_get_90k_pts(void)
{
    uint64_t ret = 0;

    if(clk90k_vaddr_hi && clk90k_vaddr_lo)
    {
        ret = (uint64_t)readl(clk90k_vaddr_lo);
        ret |= (((uint64_t)readl(clk90k_vaddr_hi)) << 32);
    }
    else
    {
        ALSA_WARNING("%p %p @ %s\n", clk90k_vaddr_hi, clk90k_vaddr_lo, __func__);
    }

    return ret;
}

static void snd_card_capture_setup_pts(snd_pcm_runtime_t *runtime, AUDIO_DEC_PTS_INFO *pPkt)
{
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	uint64_t curPTS;
	unsigned int pcm_pts_hi, pcm_pts_lo;
	uint64_t pcmPTS = 0;
	uint64_t diffPTS;

	curPTS = snd_card_get_90k_pts();
	pcm_pts_hi = ntohl(pPkt->PTSH);
	pcm_pts_lo = ntohl(pPkt->PTSL);

	pcmPTS = (((uint64_t)pcm_pts_hi) << 32) | ((uint64_t)pcm_pts_lo);

	diffPTS = curPTS - pcmPTS;

	//ALSA_VitalPrint("pcm pts %x %x\n", pcm_pts_hi, pcm_pts_lo);
	//ALSA_VitalPrint("cur pts %x %x\n", (unsigned int)(curPTS >> 32), (unsigned int)curPTS);
	//ALSA_VitalPrint("pcm dely %d ms\n", (int)((diffPTS * 1000) / 90000));

	ktime_get_ts(&dpcm->ts);
	dpcm->ts.tv_sec -= (div64_ul(diffPTS, 90000));
	dpcm->ts.tv_nsec -= (div64_ul(diffPTS * 100000, 9));
	//ALSA_VitalPrint("cap ts %x\n\n", (unsigned int)dpcm->ts.tv_sec);
}

static void snd_card_capture_calculate_pts(snd_pcm_runtime_t *runtime, long nPeriodCount)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    //snd_pcm_uframes_t nFrameSize = nPeriodCount * runtime->period_size;
    AUDIO_DEC_PTS_INFO nPkt[2];
    AUDIO_RINGBUF_PTR_64 *pRing = &dpcm->nPTSRing;
    unsigned long temp_rp;
    unsigned int lpcm_rp = dpcm->nLPCMRing_LE.readPtr[0];
    unsigned int nPkt_ptr[2] = {0};
    unsigned int wp_offset, rp_offset, loop_count=0;
    //unsigned long old_rp = pRing->rp;

    // refresh wp of pts_ring
    wp_offset = ntohl(dpcm->nPTSRingHdr.writePtr) - (unsigned int)dpcm->nPTSMem.pPhy;
    pRing->wp = pRing->base + (unsigned long)wp_offset;

    //ALSA_VitalPrint("#pkt %d\n", (int)(ring_valid_data(pRing->base, pRing->limit, pRing->rp, pRing->wp) / sizeof(AUDIO_DEC_PTS_INFO)));

    ////////////////////////////
    // find corresponding pts //
    ////////////////////////////
    // get the first PTS
    if(ring_valid_data(pRing->base, pRing->limit, pRing->rp, pRing->wp) >= sizeof(AUDIO_DEC_PTS_INFO))
    {
        temp_rp = ring_memcpy2_buf((char *)&nPkt[0], pRing->base, pRing->limit, pRing->rp, sizeof(AUDIO_DEC_PTS_INFO));
    }
    else
    {
        ALSA_WARNING("Err @ %s %d\n", __func__, __LINE__);
        goto exit;
    }
    do
    {
        if(ring_valid_data(pRing->base, pRing->limit, temp_rp, pRing->wp) >= sizeof(AUDIO_DEC_PTS_INFO))
        {
            ring_memcpy2_buf((char *)&nPkt[1], pRing->base, pRing->limit, temp_rp, sizeof(AUDIO_DEC_PTS_INFO));
        }
        else
        {
            if(loop_count == 0)
            {
                snd_card_capture_setup_pts(runtime, &nPkt[0]);
                goto exit;
            }
            else
            {
                // get the last packet as PTS needed
                snd_card_capture_setup_pts(runtime, &nPkt[0]);
                pRing->rp = ring_minus(pRing->base, pRing->limit, temp_rp, sizeof(AUDIO_DEC_PTS_INFO));
                break;
            }
        }

        nPkt_ptr[0] = ntohl(nPkt[0].wPtr);
        nPkt_ptr[1] = ntohl(nPkt[1].wPtr);
        //ALSA_VitalPrint("lpcm %x pkt %x %x\n", lpcm_rp, nPkt_ptr[0], nPkt_ptr[1]);
        if(ring_check_ptr_valid_32(nPkt_ptr[0], nPkt_ptr[1], lpcm_rp))
        {
            // get PTS
            snd_card_capture_setup_pts(runtime, &nPkt[0]);

            pRing->rp = ring_minus(pRing->base, pRing->limit, temp_rp, sizeof(AUDIO_DEC_PTS_INFO));
            break;
        }
        else
        {
            temp_rp = ring_add(pRing->base, pRing->limit, temp_rp, sizeof(AUDIO_DEC_PTS_INFO));
            nPkt[0] = nPkt[1];
        }

        loop_count++;
    }while(1);

    // update rp
    //ALSA_VitalPrint("pts rp %lx => %lx\n", old_rp, pRing->rp);
    rp_offset = pRing->rp - pRing->base;
    dpcm->nPTSRingHdr.readPtr[0] = htonl((unsigned int)dpcm->nPTSMem.pPhy + rp_offset);

exit:
/*  ALSA_VitalPrint("lpcm_rp %x time %x\n", lpcm_rp, (unsigned int)dpcm->ts.tv_sec);
    ALSA_VitalPrint("pts b %x l %x w %x r %x\n"
        , (unsigned int)ntohl(dpcm->nPTSRingHdr.beginAddr)
        , (unsigned int)(ntohl(dpcm->nPTSRingHdr.beginAddr) + dpcm->nPTSMem.size)
        , (unsigned int)ntohl(dpcm->nPTSRingHdr.writePtr), (unsigned int)ntohl(dpcm->nPTSRingHdr.readPtr[0])); */
    return;
}

static void snd_card_capture_LPCM_copy(snd_pcm_runtime_t *runtime, long nPeriodCount)
{
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    snd_pcm_uframes_t nFrameSize = nPeriodCount * runtime->period_size;
    snd_pcm_uframes_t dma_wp = dpcm->nTotalWrite % runtime->buffer_size;
    AUDIO_RINGBUF_PTR_64 src_ring, dst_ring;

    src_ring.base = (unsigned long)dpcm->pLPCMData;
    src_ring.limit = (unsigned long)(src_ring.base + dpcm->nLPCMRing_LE.size);
    src_ring.rp = src_ring.base 
        + (unsigned long)(dpcm->nLPCMRing_LE.readPtr[0] - dpcm->nLPCMRing_LE.beginAddr);

    dst_ring.base = (unsigned long)runtime->dma_area;
    dst_ring.limit = (unsigned long)(runtime->dma_area + runtime->buffer_size * dpcm->nFrameBytes);
    dst_ring.wp = (unsigned long)(runtime->dma_area + dma_wp * dpcm->nFrameBytes);

    ring1_to_ring2_general_64(&src_ring, &dst_ring, nFrameSize * dpcm->nFrameBytes, NULL);
}

#if _DBG_CHECK_AI_HW_RING_DATA_EN
static void snd_card_capture_lpcm_check_ringBuf(unsigned int data)
{
    snd_pcm_substream_t * substream = (snd_pcm_substream_t *)data;
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    long nDataOfAIInring = 0;
    long nDataOfAILpcmRing = 0;
    nDataOfAIInring = snd_card_get_ring_data(dpcm->nAIRing, dpcm->nAIRing_LE) >> 2;
    nDataOfAILpcmRing = snd_card_get_ring_data(&dpcm->nLPCMRing, &dpcm->nLPCMRing_LE) / dpcm->nFrameBytes;
#if 0
    {
        long wp, rp, base, limit;        
        base = (long)dpcm->nAIRing_LE[0].beginAddr;
        limit= (long)(dpcm->nAIRing_LE[0].beginAddr + dpcm->nAIRing_LE[0].size);
        wp = (long)(ntohl(dpcm->nAIRing[0].writePtr));
        rp = (long)(ntohl(dpcm->nAIRing[0].readPtr[0]));
        ALSA_VitalPrint("[ALSA AI HW_ring b %x l %x w %x r %x]\n", base, limit, wp, rp);
    }
#endif
    ALSA_VitalPrint("[ALSA AI size %x data %x LPCM size %x data %x]\n"
        , dpcm->nAIRing_LE[0].size >> 2, nDataOfAIInring, dpcm->nLPCMRing_LE.size / dpcm->nFrameBytes, nDataOfAILpcmRing / dpcm->nFrameBytes);
}
#endif

int snd_card_capture_get_time_info(struct snd_pcm_substream *substream,
			struct timespec *system_ts, struct timespec *audio_ts,
			struct snd_pcm_audio_tstamp_config *audio_tstamp_config,
			struct snd_pcm_audio_tstamp_report *audio_tstamp_report)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    //ALSA_VitalPrint("%s\n", __func__);
    *system_ts = dpcm->ts;
    return 0;
}

static void snd_card_capture_handle_HDMI_plug_out(snd_pcm_substream_t * substream)
{
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    unsigned int nPeriodCount = 1;
    snd_pcm_uframes_t nFrameSize = nPeriodCount * runtime->period_size;
    snd_pcm_uframes_t dma_wp = dpcm->nTotalWrite % runtime->buffer_size;
    AUDIO_RINGBUF_PTR_64 dst_ring;
    char *pBuf = kmalloc(nFrameSize * dpcm->nFrameBytes, GFP_KERNEL);
    unsigned long free_size;

    if(pBuf == NULL)
    {
        ALSA_SEC_PRINT(1, "malloc FAILED @ %s %d\n", __func__, __LINE__);
        return;
    }

    free_size = snd_pcm_capture_hw_avail(runtime);
    if(free_size <= runtime->period_size)
    {
        ALSA_SEC_PRINT(1, "over flow %d %d @ %s %d\n", (int)free_size, (int)runtime->period_size, __func__, __LINE__);
        return;
    }

    ALSA_SEC_PRINT(2, " @ %s\n", __func__);
    // copy MUTE to DMA buffer
    memset(pBuf, 0, nFrameSize * dpcm->nFrameBytes);
    dst_ring.base = (unsigned long)runtime->dma_area;
    dst_ring.limit = (unsigned long)(runtime->dma_area + runtime->buffer_size * dpcm->nFrameBytes);
    dst_ring.wp = (unsigned long)(runtime->dma_area + dma_wp * dpcm->nFrameBytes);
    buf_memcpy2_ring(dst_ring.base, dst_ring.limit, dst_ring.wp, pBuf, nFrameSize * dpcm->nFrameBytes);
    kfree(pBuf);

    // paste time stamp
   	ktime_get_ts(&dpcm->ts);

    dpcm->nTotalWrite += nPeriodCount * runtime->period_size;
    snd_pcm_period_elapsed(substream);
}

static enum hrtimer_restart snd_card_capture_lpcm_timer_function(struct hrtimer *timer)
{
	snd_card_RTK_capture_pcm_t *dpcm =
		container_of(timer, snd_card_RTK_capture_pcm_t, hr_timer);
	snd_pcm_substream_t *substream = dpcm->substream;
	snd_pcm_runtime_t *runtime = substream->runtime;

	snd_pcm_uframes_t nRingDataFrame, free_size;
	long nRingDataSize; // bytes
	unsigned int nPeriodCount = 0, free_period;

	if(dpcm->enHRTimer == HRTIMER_RESTART)
	{

		if(ring_valid_data(0
			, (unsigned long)runtime->boundary
			, (unsigned long)runtime->control->appl_ptr
			, (unsigned long)runtime->status->hw_ptr) > runtime->buffer_size)
		{
			ALSA_WARNING("[hw_ptr %d appl_ptr %d %d @ %s %d]\n"
				, (int)runtime->status->hw_ptr
				, (int)runtime->control->appl_ptr
				, (int)runtime->buffer_size, __FUNCTION__, __LINE__);
		}

		_DBG_CHECK_AI_HW_RING_DATA(data);

		// check if HDMI-RX plug out
		if(dpcm->source_in == ENUM_AIN_HDMIRX)
		{
			if(snd_realtek_capture_check_hdmirx_enable() == 0)
			{
				snd_card_capture_handle_HDMI_plug_out(substream);
				goto SET_TIMER;
			}
		}

		nRingDataSize = snd_card_get_ring_data(&dpcm->nLPCMRing, &dpcm->nLPCMRing_LE);
		nRingDataFrame = nRingDataSize / dpcm->nFrameBytes;
		if(nRingDataFrame >= runtime->period_size)
		{
			nPeriodCount = nRingDataFrame / runtime->period_size;

			if(nPeriodCount == runtime->periods)
				nPeriodCount--;

			// check overflow
			{
				free_size = runtime->buffer_size - ring_valid_data(0
					, (unsigned long)runtime->boundary
					, (unsigned long)runtime->control->appl_ptr
					, (unsigned long)runtime->status->hw_ptr);
				free_period = free_size / runtime->period_size;
				nPeriodCount = MIN(nPeriodCount, free_period);
				if(nPeriodCount == 0)
					goto SET_TIMER;
			}

			// copy data from LPCM_ring to dma_buf
			snd_card_capture_LPCM_copy(runtime, nPeriodCount);

#ifdef CAPTURE_USE_PTS_RING
			// calculate PTS
			switch(dpcm->source_in)
			{
				case ENUM_AIN_AUDIO:
				case ENUM_AIN_AUDIO_V2:
				case ENUM_AIN_AUDIO_V3:
				case ENUM_AIN_AUDIO_V4:
					break;
				default:
					snd_card_capture_calculate_pts(runtime, nPeriodCount);
					break;
			}
#endif

			// update LPCM_ring rp.
			dpcm->nLPCMRing_LE.readPtr[0] = (unsigned int)ring_add(
				(unsigned long)dpcm->nLPCMRing_LE.beginAddr
				, (unsigned long)(dpcm->nLPCMRing_LE.beginAddr + dpcm->nLPCMRing_LE.size)
				, (unsigned long)(dpcm->nLPCMRing_LE.readPtr[0])
				, nPeriodCount * runtime->period_size * dpcm->nFrameBytes);
			dpcm->nLPCMRing.readPtr[0] = htonl(dpcm->nLPCMRing_LE.readPtr[0]);

			dpcm->nTotalWrite += nPeriodCount * runtime->period_size;

			// update runtime->status->hw_ptr
			snd_pcm_period_elapsed(substream);
		}

SET_TIMER:
		/* Set up the next time */
		hrtimer_forward_now(timer, dpcm->ktime);

		return HRTIMER_RESTART;
	}
	else
	{
		return HRTIMER_NORESTART;
	}
}

static void snd_card_capture_timer_function(unsigned long data)
{
    snd_pcm_substream_t * substream = (snd_pcm_substream_t *)data;
    snd_pcm_runtime_t *runtime = substream->runtime;
    snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
    snd_pcm_uframes_t nRingDataFrame;  
    unsigned long flags;
    long nRingDataSize;
    unsigned int nPeriodCount = 0;
    int ch;

    if(ring_valid_data(0, runtime->boundary, runtime->control->appl_ptr, runtime->status->hw_ptr) > runtime->buffer_size)
    {
        ALSA_WARNING("[hw_ptr %d appl_ptr %d %s %d]\n", (int)runtime->status->hw_ptr, (int)runtime->control->appl_ptr, __FUNCTION__, __LINE__);
    }

#if 0   // DEBUG: check wp/rp
    ALSA_SEC_PRINT(2, "[���� state %d appl_ptr %d hw_ptr %d]\n", (int)runtime->status->state, (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
#endif

    // fresh wp
    for(ch=0 ; ch<2 ; ++ch)
        dpcm->nAIRing_LE[ch].writePtr = ntohl(dpcm->nAIRing[ch].writePtr);

    nRingDataSize = snd_card_get_ring_data(dpcm->nAIRing, dpcm->nAIRing_LE);
    nRingDataFrame = nRingDataSize >> 2;    // 1 PCM = 32 bits.
    if(nRingDataFrame >= runtime->period_size)
    {
        nPeriodCount = nRingDataFrame / runtime->period_size;
        if(nPeriodCount == runtime->periods)
            nPeriodCount--;

        // dma wirte too faster ?? (NOT sure)

        // copy data from AI_ring to dma_buf
        snd_card_capture_copy(runtime, nPeriodCount);

        // update AI_ring rp.
        for(ch=0 ; ch<2 ; ++ch)
        {
            dpcm->nAIRing_LE[ch].readPtr[0] = ring_add((unsigned long)dpcm->nAIRing_LE[ch].beginAddr
                , (unsigned long)(dpcm->nAIRing_LE[ch].beginAddr + dpcm->nAIRing_LE[ch].size)
                , (unsigned long)dpcm->nAIRing_LE[ch].readPtr[0]
                , nPeriodCount * runtime->period_size * 4 /* 1 PCM = 32 bits */);
            dpcm->nAIRing[ch].readPtr[0] = (unsigned int)htonl(dpcm->nAIRing_LE[ch].readPtr[0]);
        }

        dpcm->nTotalWrite += nPeriodCount * runtime->period_size;
        snd_pcm_period_elapsed(substream);
    }

    // set timer
    dpcm->nStartTimer.expires = dpcm->nPeriodJiffies + jiffies;
    //spin_lock_irqsave(&dpcm->nLock, flags);
    spin_lock_irqsave(&capture_lock, flags);
    if(dpcm->bStop)
        dpcm->bStop = 0;
    else
        add_timer(&dpcm->nStartTimer);
    //spin_unlock_irqrestore(&dpcm->nLock, flags);
    spin_unlock_irqrestore(&capture_lock, flags);
}

static enum hrtimer_restart snd_card_timer_function(struct hrtimer *timer)
{
	snd_card_RTK_pcm_t *dpcm =
			container_of(timer, snd_card_RTK_pcm_t, hr_timer);
	snd_pcm_substream_t *substream = dpcm->substream;
	snd_pcm_runtime_t *runtime = substream->runtime;

	snd_pcm_uframes_t nReadAddSize = 0;
	unsigned int nPeriodCount = 0;
	unsigned int HWRingRp;
	unsigned int HWRingFreeSize;
	unsigned int HWRingFreeFrame;
	static unsigned long dbg_count = 0;
	int dec_out_valid_size = 0;

	if(dpcm->enHRTimer == HRTIMER_RESTART)
	{
		//calculate AOInring msec
		dec_out_valid_size = ring_valid_data(
			(unsigned int)ntohl(dpcm->decOutRing[0].beginAddr),
			(unsigned int)ntohl(dpcm->decOutRing[0].beginAddr) + rtk_dec_ao_buffer,
			(unsigned int)ntohl(dpcm->decOutRing[0].readPtr[0]),
			(unsigned int)ntohl(dpcm->decOutRing[0].writePtr));
		//printk("dec_out_valid_size %d\n", dec_out_valid_size);
		if (dec_out_valid_size > 0 && dec_out_valid_size <= dpcm->nRingSize)
			dec_out_msec = ((dec_out_valid_size >> 2) * 1000) / runtime->rate;
		else
			dec_out_msec = 0;
		//printk("dec_out_msec %d\n", dec_out_msec);

		if (runtime->control->appl_ptr == runtime->status->hw_ptr)
		{
			ALSA_WARNING("[appl_ptr %d = hw_ptr %s %d]\n", (int)runtime->control->appl_ptr, __FUNCTION__, __LINE__);
			ALSA_WARNING("Need to check why data didn't send to alsa\n");
		}

		// update HW rp (the pointer of AFW read)
		HWRingRp = (unsigned int)(ntohl(dpcm->decInRing[0].readPtr[0]));//physical address
		dpcm->decInRing_LE[0].readPtr[0] = HWRingRp;
		dpcm->nHWPtr = bytes_to_frames(runtime, (unsigned long)HWRingRp - (unsigned long)dpcm->decInRing_LE[0].beginAddr);

#ifdef DEBUG_RECORD
		if (dpcm->ai_count > 1){
			dpcm->fs = get_fs();
			set_fs(KERNEL_DS);
			if (dpcm->nHWPtr >= dpcm->nPreHWPtr)
			{
				// 4 = 2 channel * 2 (16 bits = 2 bytes), using frames to btyes
				vfs_write(dpcm->fp, runtime->dma_area + frames_to_bytes(runtime, dpcm->nPreHWPtr), frames_to_bytes(runtime,dpcm->nHWPtr - dpcm->nPreHWPtr), &dpcm->pos);
			}
			else{
				nReadAddSize = ring_valid_data(0, runtime->buffer_size, dpcm->nPreHWPtr, dpcm->nHWPtr);

				vfs_write(dpcm->fp, runtime->dma_area + frames_to_bytes(runtime, dpcm->nPreHWPtr), frames_to_bytes(runtime, runtime->buffer_size - dpcm->nPreHWPtr), &dpcm->pos);
				vfs_write(dpcm->fp, runtime->dma_area, frames_to_bytes(runtime, nReadAddSize - (runtime->buffer_size - dpcm->nPreHWPtr)), &dpcm->pos);
			}
			set_fs(dpcm->fs);
		}
#endif

		// update HW read size
		if (dpcm->nHWPtr != dpcm->nPreHWPtr)
		{
			nReadAddSize = ring_valid_data(0, runtime->buffer_size, dpcm->nPreHWPtr, dpcm->nHWPtr);

			/* Control the rp for application.
			 * 1. If data more than half buffer means the ability is enough,
			 *    we can update length of the half buffer to rp.
			 * 2. If data less than half buffer means the ability is not enough,
			 *    we just update one period size length to rp avoiding SW-3490 problem.
			 */
			if (nReadAddSize > (runtime->buffer_size >> 1))
			{
				nReadAddSize = runtime->buffer_size >> 1;
				dpcm->nHWPtr = ring_add(0, runtime->buffer_size, dpcm->nPreHWPtr, nReadAddSize);
				//ALSA_WARNING("[ALSA maybe hang because Jitter %d, runtime->buffer size %d]\n", (int)nReadAddSize, (int)runtime->buffer_size);
			}
			else if (nReadAddSize <= (runtime->buffer_size >> 1) && nReadAddSize >= runtime->period_size)
			{
				nReadAddSize = runtime->period_size;
				dpcm->nHWPtr = ring_add(0, runtime->buffer_size, dpcm->nPreHWPtr, nReadAddSize);
				//ALSA_WARNING("[ALSA maybe hang because Jitter %d, runtime->buffer size %d]\n", (int)nReadAddSize, (int)runtime->buffer_size);
			}

			dpcm->nHWReadSize += nReadAddSize;
			dpcm->nTotalRead = ring_add(0,
				runtime->boundary,
				dpcm->nTotalRead,
				nReadAddSize);
		}

		// update wp (the pointer application send data to alsa)
		nPeriodCount = ring_valid_data(0, runtime->boundary, dpcm->nTotalWrite, runtime->control->appl_ptr) / runtime->period_size;

		if (nPeriodCount == runtime->periods)
			nPeriodCount--;

		//printk("\033[0;33;33m [INRING LE %d] base %x limit %x\033[m\n",
		//    __LINE__, dpcm->decInRing_LE[0].beginAddr, dpcm->decInRing_LE[0].beginAddr + dpcm->decInRing_LE[0].size);
		//printk("\033[0;33;33m [INRING LE %d] wp %x rp %x HWRingRp %x\033[m\n",
		//    __LINE__, dpcm->decInRing_LE[0].writePtr, dpcm->decInRing_LE[0].readPtr[0], HWRingRp);

		// Check the buffer available size between alsa and AFW
		HWRingFreeSize = valid_free_size(dpcm->decInRing_LE[0].beginAddr,
			dpcm->decInRing_LE[0].beginAddr + dpcm->decInRing_LE[0].size,
			HWRingRp,
			dpcm->decInRing_LE[0].writePtr);

		HWRingFreeFrame = bytes_to_frames(runtime, HWRingFreeSize);

		if ((runtime->period_size * nPeriodCount) > HWRingFreeFrame)
			nPeriodCount = HWRingFreeFrame / runtime->period_size;

		if (HWRingFreeSize <= dpcm->nPeriodBytes)
			nPeriodCount = 0;

		if (nPeriodCount)
		{
			//printk("[INRING LE] wp %x update 0x%x bytes\n", dpcm->decInRing_LE[0].writePtr, frames_to_bytes(runtime, runtime->period_size * nPeriodCount));
			dpcm->decInRing_LE[0].writePtr = ring_add(dpcm->decInRing_LE[0].beginAddr
				, dpcm->decInRing_LE[0].beginAddr + dpcm->decInRing_LE[0].size
				, dpcm->decInRing_LE[0].writePtr
				, frames_to_bytes(runtime, runtime->period_size * nPeriodCount));

			dpcm->nTotalWrite = ring_add(0,
				runtime->boundary,
				dpcm->nTotalWrite,
				runtime->period_size * nPeriodCount);

			// update wp (tell AFW the write pointer from application is update)
			dpcm->decInRing[0].writePtr = htonl(dpcm->decInRing_LE[0].writePtr);//record physical address
			//printk("\033[0;33;33m [INRING LE %d update] wp %x rp %x\033[m\n", __LINE__, dpcm->decInRing_LE[0].writePtr, dpcm->decInRing_LE[0].readPtr[0]);
		}

		//printk("[nReadAddSize %d pre %d cur %d %d]\n", nReadAddSize, dpcm->nPreHWPtr, dpcm->nHWPtr, dpcm->nHWReadSize);
		//printk("[nTotalWrite %d nTotalRead %d nPeriodCount %d]\n", dpcm->nTotalWrite, dpcm->nTotalRead, nPeriodCount);

		if (runtime->status->state == SNDRV_PCM_STATE_DRAINING) {
			switch (dpcm->nEOSState) {
				case SND_REALTEK_EOS_STATE_NONE:
					if (RPC_TOAGENT_INBAND_EOS_SVC(dpcm) < 0)
					{
						ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
					}
					dpcm->nEOSState = SND_REALTEK_EOS_STATE_FINISH;
					break;
				case SND_REALTEK_EOS_STATE_FINISH:
					if (dpcm->nTotalWrite == dpcm->nTotalRead)
					{
						DEBUG_CODE("[snd_pcm_period_elapsed]\n");
						dpcm->nHWReadSize = 0;
						snd_pcm_period_elapsed(substream);
					}
					break;
				default:
					break;
			}
		} else {
			if (dpcm->nHWReadSize >= runtime->period_size) {
				dpcm->nHWReadSize %= runtime->period_size;
				DEBUG_CODE("[snd_pcm_period_elapsed]\n");
				snd_pcm_period_elapsed(substream);
			}
		}

		// check if wp and rp of android and AFW both stop
		if (dpcm->nHWPtr == dpcm->nPreHWPtr && runtime->control->appl_ptr == dpcm->nPre_appl_ptr)
			dbg_count++;
		else
			dbg_count = 0;

		if (dbg_count >= (HZ << 1))
		{
			ALSA_WARNING("[state %d]\n", (int)runtime->status->state);
			ALSA_WARNING("[runtime->control->appl_ptr %d runtime->status->hw_ptr %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
			ALSA_WARNING("[dpcm->nTotalWrite %d dpcm->nTotalRead %d dpcm->nHWPtr %d]\n", (int)dpcm->nTotalWrite, (int)dpcm->nTotalRead, (int)dpcm->nHWPtr);
			ALSA_WARNING("[b %x l %x w %x r %x]\n",
				(unsigned int)(ntohl(dpcm->decInRing[0].beginAddr)),
				(unsigned int)((ntohl(dpcm->decInRing[0].beginAddr)) + dpcm->decInRing_LE[0].size),
				(unsigned int)(ntohl(dpcm->decInRing[0].writePtr)),
				(unsigned int)(ntohl(dpcm->decInRing[0].readPtr[0])));
			ALSA_WARNING("[HWRingRp %x nPeriodCount %d runtime->periods %d]\n", HWRingRp, nPeriodCount, runtime->periods);
			ALSA_WARNING("[snd_pcm_playback_avail %d runtime->control->avail_min %d]\n", (int)snd_pcm_playback_avail(runtime), (int)runtime->control->avail_min);
			dbg_count = 0;
		}

		dpcm->nPreHWPtr = dpcm->nHWPtr;
		dpcm->nPre_appl_ptr = runtime->control->appl_ptr;

		/* Set up the next time */
		hrtimer_forward_now(timer, dpcm->ktime);

		return HRTIMER_RESTART;
	}
	else
	{
		return HRTIMER_NORESTART;
	}
}

static int snd_card_capture_trigger(snd_pcm_substream_t * substream, int cmd)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_capture_pcm_t *dpcm = runtime->private_data;
	int ret = 0;
	unsigned long flags;

	// error checking
	if(snd_pcm_capture_avail(runtime) > runtime->buffer_size
		|| snd_pcm_capture_hw_avail(runtime) > runtime->buffer_size)
	{
		ALSA_WARNING("[ERROR BUG %d %s %s %d]\n", cmd, __FILE__, __FUNCTION__, __LINE__);
		ALSA_WARNING("[state %d appl_ptr %d hw_ptr %d %d]\n", runtime->status->state, (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr, (int)runtime->buffer_size);
	}

	switch(cmd)
	{
		case SNDRV_PCM_TRIGGER_START:
			printk("[ALSA trigger start appl_ptr %d hw_ptr %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
			dpcm->enHRTimer = HRTIMER_RESTART;
			hrtimer_start(&dpcm->hr_timer, dpcm->ktime, HRTIMER_MODE_REL);
			break;
		case SNDRV_PCM_TRIGGER_STOP:
			printk("[ALSA trigger stop appl_ptr %d hw_ptr %d]\n", (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
			spin_lock_irqsave(&capture_lock, flags);
			dpcm->enHRTimer = HRTIMER_NORESTART;
			spin_unlock_irqrestore(&capture_lock, flags);
			hrtimer_try_to_cancel(&dpcm->hr_timer);
			break;
		default:
			ret = -EINVAL;
	}

	return ret;
}

static int snd_card_playback_trigger(snd_pcm_substream_t * substream, int cmd)
{
	snd_pcm_runtime_t *runtime = substream->runtime;
	snd_card_RTK_pcm_t *dpcm = runtime->private_data;
	int ret = 0;
	unsigned long flags;

	if (cmd != SNDRV_PCM_TRIGGER_SUSPEND && is_suspend) {
		ALSA_VitalPrint("[ALSA %s %d] suspend\n", __FUNCTION__, __LINE__);
		return 0;
	}

	// error checking
	if (snd_pcm_playback_avail(runtime) > runtime->buffer_size
		|| snd_pcm_playback_hw_avail(runtime) > runtime->buffer_size)
	{
		ALSA_WARNING("[ERROR BUG %s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
		ALSA_WARNING("[state %d appl_ptr %d hw_ptr %d]\n", runtime->status->state, (int)runtime->control->appl_ptr, (int)runtime->status->hw_ptr);
		ALSA_WARNING("[dpcm->nTotalWrite %d dpcm->nTotalRead %d]\n", (int)dpcm->nTotalWrite, (int)dpcm->nTotalRead);
	}

	switch(cmd)
	{
		case SNDRV_PCM_TRIGGER_STOP:
			spin_lock_irqsave(&playback_lock, flags);
			dpcm->enHRTimer = HRTIMER_NORESTART;
			spin_unlock_irqrestore(&playback_lock, flags);
			hrtimer_try_to_cancel(&dpcm->hr_timer);
			break;

		case SNDRV_PCM_TRIGGER_START:
			dpcm->enHRTimer = HRTIMER_RESTART;
			hrtimer_start(&dpcm->hr_timer, dpcm->ktime, HRTIMER_MODE_REL);
			break;

		case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			spin_lock_irqsave(&playback_lock, flags);
			dpcm->enHRTimer = HRTIMER_NORESTART;
			spin_unlock_irqrestore(&playback_lock, flags);
			break;

		case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			dpcm->enHRTimer = HRTIMER_RESTART;
			hrtimer_start(&dpcm->hr_timer, dpcm->ktime, HRTIMER_MODE_REL);
			break;

		case SNDRV_PCM_TRIGGER_SUSPEND:
			spin_lock_irqsave(&playback_lock, flags);
			ALSA_WARNING("[+]SNDRV_PCM_TRIGGER_SUSPEND\n");
			dpcm->enHRTimer = HRTIMER_NORESTART;
			ALSA_WARNING("[-]SNDRV_PCM_TRIGGER_SUSPEND\n");
			spin_unlock_irqrestore(&playback_lock, flags);
			break;

		case SNDRV_PCM_TRIGGER_RESUME:
			ALSA_WARNING("[+]SNDRV_PCM_TRIGGER_RESUME\n");
			dpcm->enHRTimer = HRTIMER_RESTART;
			hrtimer_start(&dpcm->hr_timer, dpcm->ktime, HRTIMER_MODE_REL);
			ALSA_WARNING("[-]SNDRV_PCM_TRIGGER_RESUME\n");
			break;

		default:
			ALSA_WARNING("[err %d %s %d]\n", cmd, __FUNCTION__, __LINE__);
			ret = -EINVAL;
	}

	return ret;
}

static int snd_card_hw_params(snd_pcm_substream_t * substream, snd_pcm_hw_params_t * hw_params)
{
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    int err;
    //ALSA_VitalPrint("[ALSA %s demand %d Bytes]\n", __FUNCTION__, params_buffer_bytes(hw_params));
    TRACE_CODE("[ALSA %s demand %d Bytes]\n", __FUNCTION__, params_buffer_bytes(hw_params));
    err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
    if (err != 0 && err != 1) {
        ALSA_WARNING("[fail %s %d]\n", __FUNCTION__, __LINE__);
    }
    return err;
}

static int snd_card_capture_hw_free(snd_pcm_substream_t * substream)
{
    DEBUG_CODE("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    return snd_pcm_lib_free_pages(substream);
}

static int snd_card_hw_free(snd_pcm_substream_t * substream)
{
    TRACE_CODE("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    return snd_pcm_lib_free_pages(substream);
}

static unsigned long ring_valid_data(unsigned long ring_base, unsigned long ring_limit, unsigned long ring_rp, unsigned long ring_wp)
{
	if (ring_wp >= ring_rp)
	{
		return (ring_wp-ring_rp);
	}
	else
	{
		return (ring_limit-ring_base)-(ring_rp-ring_wp);
	}
}

static unsigned long ring_add(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, unsigned int bytes)
{
	ptr += bytes;
	if (ptr >= ring_limit)
	{
		ptr = ring_base + (ptr-ring_limit);
	}
	return ptr;
}

static unsigned long ring_minus(unsigned long ring_base, unsigned long ring_limit, unsigned long ptr, int bytes)
{
	ptr -= bytes;

	if (ptr < ring_base)
		ptr = ring_limit-(ring_base-ptr);

	return ptr;
}

static unsigned long valid_free_size(unsigned long base, unsigned long limit, unsigned long rp, unsigned long wp)
{
	return (limit-base)-ring_valid_data(base,limit,rp,wp)-1;
}

static int ring_check_ptr_valid_32(unsigned int ring_rp, unsigned int ring_wp, unsigned int ptr)
{
	if (ring_wp >= ring_rp)
	{
		return (ptr < ring_wp && ptr >= ring_rp);
	}
	else
	{
		return (ptr >= ring_rp || ptr < ring_wp);
	}
}

static unsigned long buf_memcpy2_ring(unsigned long base, unsigned long limit, unsigned long ptr, char* buf, unsigned long size)
{
	if (ptr + size <= limit)
	{
		memcpy((char*)ptr,buf,size);
	}
	else
	{
		int i = limit-ptr;
		memcpy((char*)ptr,(char*)buf,i);
		memcpy((char*)base,(char*)(buf+i),size-i);
	}

	ptr += size;
	if (ptr >= limit)
	{
		ptr = base + (ptr-limit);
	}
	return ptr;
}

// create PCM instance
static int __init snd_card_create_PCM_instance(
RTK_snd_card_t *pSnd,
int instance_idx,
int playback_substreams,
int capture_substreams)
{
	snd_pcm_t *pcm = NULL;
	struct snd_pcm_substream *p = NULL;
	int err;
	int i;

	printk("[%s %s %d]\n", __FILE__, __FUNCTION__, __LINE__);
	RTK_TRACE_ALSA("%d %d @ %s %d\n", playback_substreams, capture_substreams, __func__, __LINE__);

	// create PCM instance
	if ((err = snd_pcm_new(pSnd->card
		, snd_pcm_id[instance_idx] /* id string */
		, instance_idx
		, playback_substreams
		, capture_substreams
		, &pcm)) < 0)    // for Jupiter Capture Count = 0 (ie. there is no ain)
	{
		ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
		return err;
	}

	// set OPs
	switch(instance_idx)
	{
		case 0:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_card_rtk_playback_ops);
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER);
			break;
		case 1:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_i2s_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_I2S_IN);
			break;
		case 2:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_nonpcm_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_NONPCM_IN);
			break;
		case 3:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_audio_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_AUDIO_IN);
			break;
		case 4:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_audio_v2_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_AUDIO_V2_IN);
			break;
		case 5:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_audio_v3_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_AUDIO_V3_IN);
			break;
		case 6:
			snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_card_rtk_capture_audio_v4_ops);
			sprintf(pcm->name, SND_REALTEK_DRIVER_AUDIO_V4_IN);
			break;
		default:
			ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
			break;
	}

	pcm->private_data = pSnd;
	pcm->info_flags = 0;

	p = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	for (i = 0; i < playback_substreams; i++)
	{
		p->dma_buffer.dev.dev = snd_dma_continuous_data(GFP_KERNEL);
#ifdef USE_ION_AUDIO_HEAP
		p->dma_buffer.dev.type = SNDRV_DMA_TYPE_ION_PLAYBACK;
#else
		p->dma_buffer.dev.type = SNDRV_DMA_TYPE_CONTINUOUS;
#endif
		p = p->next;
	}

	p = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	for (i = 0; i < capture_substreams; i++)
	{
		p->dma_buffer.dev.dev = snd_dma_continuous_data(GFP_KERNEL);
#ifdef USE_ION_AUDIO_HEAP
		p->dma_buffer.dev.type = SNDRV_DMA_TYPE_ION_CAPTURE;
#else
		p->dma_buffer.dev.type = SNDRV_DMA_TYPE_CONTINUOUS;
#endif
		p = p->next;
	}

	snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,snd_pcm_alt_chmaps, 8, 0, NULL);
	pSnd->pcm = pcm;

#if 0
	/* NOTE: this may fail */
	if (err = snd_pcm_lib_preallocate_pages_for_all(pcm,
			SNDRV_DMA_TYPE_CONTINUOUS,
			snd_dma_continuous_data(GFP_KERNEL),
			32*1024,
			32*1024))
	{
		printk("snd_pcm_lib_preallocate_pages failed\n");
	}
#endif

	return 0;
}

void snd_realtek_hw_playback_volume_work(struct work_struct *work) {
	RTK_snd_card_t *mars = container_of(work, RTK_snd_card_t, work_volume);
	printk("[%s %d]\n", __FUNCTION__, __LINE__);
	RPC_TOAGENT_SET_VOLUME(mars->mixer_volume[MIXER_ADDR_MASTER][0]);
}

static int __init snd_card_mars_new_mixer(RTK_snd_card_t * pRTK_card)
{
    snd_card_t *card = pRTK_card->card;
    unsigned int idx;
    int err;

    spin_lock_init(&pRTK_card->mixer_lock);
    INIT_WORK(&pRTK_card->work_volume, snd_realtek_hw_playback_volume_work);
    
    strcpy(card->mixername, "RTK_Mixer");

    // add snc_control
    for (idx = 0; idx < ARRAY_SIZE(snd_mars_controls); idx++) {
        if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_mars_controls[idx], pRTK_card))) < 0)
        {
            ALSA_WARNING("[snd_ctl_add faile %s %d]\n", __FUNCTION__, __LINE__);
            return err;
        }
    }
    return 0;
}

static int snd_RTK_volume_info(snd_kcontrol_t * kcontrol, snd_ctl_elem_info_t * uinfo)
{
    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);
    uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
    // Jupiter only Master Volume can control
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 31;
    return 0;
}

static int snd_RTK_volume_get(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol)
{
    RTK_snd_card_t *mars = snd_kcontrol_chip(kcontrol);
    unsigned long flags;
    int addr = kcontrol->private_value;

    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);

    spin_lock_irqsave(&mars->mixer_lock, flags);
    switch(addr) {
        case MIXER_ADDR_MASTER:
            mars->mixer_volume[addr][1] = mars->mixer_volume[addr][0] ;
            break;
        default:
            break;
    }
    ucontrol->value.integer.value[0] = mars->mixer_volume[addr][0];
    ucontrol->value.integer.value[1] = mars->mixer_volume[addr][1];
    spin_unlock_irqrestore(&mars->mixer_lock, flags);
    return 0;
}

#define cpy_func(dst, src, size, dmem_buf) memcpy(dst, src, size)

static void ring1_to_ring2_general_64(AUDIO_RINGBUF_PTR_64* ring1, AUDIO_RINGBUF_PTR_64* ring2, long size, char* dmem_buf)
{
    if (ring1->rp + size <= ring1->limit)
    {
        if (ring2->wp + size <= ring2->limit)
        {
                        
            cpy_func((char*)ring2->wp,(char*)ring1->rp,size,dmem_buf);          
        }
        else
        {
            int i = ring2->limit-ring2->wp;
            cpy_func((char*)ring2->wp,(char*)ring1->rp,i,dmem_buf);
            cpy_func((char*)ring2->base,(char*)(ring1->rp+i),size-i,dmem_buf);

        }
    }
    else
    {
        if (ring2->wp + size <= ring2->limit)
        {
            int i = ring1->limit-ring1->rp;
            cpy_func((char*)ring2->wp,(char*)ring1->rp,i,dmem_buf);
            cpy_func((char*)(ring2->wp+i),(char*)(ring1->base),size-i,dmem_buf);
        }
        else
        {
            int i,j;
            i = ring1->limit-ring1->rp;
            j = ring2->limit-ring2->wp;
            if (j <= i)
            {
                cpy_func((char*)ring2->wp,(char*)ring1->rp,j,dmem_buf);
                cpy_func((char*)ring2->base,(char*)(ring1->rp+j),i-j,dmem_buf);
                cpy_func((char*)(ring2->base+i-j),(char*)(ring1->base),size-i,dmem_buf);
            }
            else
            {
                cpy_func((char*)ring2->wp,(char*)ring1->rp,i,dmem_buf);
                cpy_func((char*)(ring2->wp+i),(char*)ring1->base,j-i,dmem_buf);
                cpy_func((char*)ring2->base,(char*)(ring1->base+j-i),size-j,dmem_buf);
            }
        }       
    }
    
    ring1->rp += size;
    if (ring1->rp >= ring1->limit)
    {
        ring1->rp = ring1->base + (ring1->rp-ring1->limit);
    }

    ring2->wp += size;
    if (ring2->wp >= ring2->limit)
    {
        ring2->wp = ring2->base + (ring2->wp-ring2->limit);
    }   
}


static int snd_RTK_volume_put(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol)
{
    RTK_snd_card_t *mars = snd_kcontrol_chip(kcontrol);
    unsigned long flags;
    int change, addr = kcontrol->private_value;
    int master;

    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);

    master = ucontrol->value.integer.value[0];
    if (master < 0) {
        master = 0;
    } 
    if (master > 31) {
        master = 31; 
    }
    
    spin_lock_irqsave(&mars->mixer_lock, flags);
    change = mars->mixer_volume[addr][0] != master;
    mars->mixer_volume[addr][0] = master;
    mars->mixer_volume[addr][1] = master;
    spin_unlock_irqrestore(&mars->mixer_lock, flags);
    if (addr ==MIXER_ADDR_MASTER) { 
        schedule_work(&mars->work_volume);
    }
        
    return change;
}

static int snd_RTK_capsrc_info(snd_kcontrol_t * kcontrol, snd_ctl_elem_info_t * uinfo)
{
    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);
    uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
    uinfo->count = 2;
    uinfo->value.integer.min = 0;
    uinfo->value.integer.max = 1;
    return 0;
}
 
static int snd_RTK_capsrc_get(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol)
{
    RTK_snd_card_t *mars = snd_kcontrol_chip(kcontrol);
    unsigned long flags;
    int addr = kcontrol->private_value;

    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);
    spin_lock_irqsave(&mars->mixer_lock, flags);
    ucontrol->value.integer.value[0] = mars->capture_source[addr][0];
    ucontrol->value.integer.value[1] = mars->capture_source[addr][1];
    spin_unlock_irqrestore(&mars->mixer_lock, flags);
    return 0;
}

static int snd_RTK_capsrc_put(snd_kcontrol_t * kcontrol, snd_ctl_elem_value_t * ucontrol)
{
    RTK_snd_card_t *mars = snd_kcontrol_chip(kcontrol);
    unsigned long flags;
    int change, addr = kcontrol->private_value;
    int left, right;
    //printk("[ALSA %s %d\n", __FUNCTION__, __LINE__);

    left = ucontrol->value.integer.value[0] & 1;
    right = ucontrol->value.integer.value[1] & 1;
    spin_lock_irqsave(&mars->mixer_lock, flags);
    change = mars->capture_source[addr][0] != left &&
             mars->capture_source[addr][1] != right;
    mars->capture_source[addr][0] = left;
    mars->capture_source[addr][1] = right;
    spin_unlock_irqrestore(&mars->mixer_lock, flags);
    return change;
}

#ifdef CONFIG_SYSFS

static ssize_t alsa_latency_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int mLatency = 0;
    mLatency = snd_monitor_audio_data_queue();

    return sprintf(buf, "%u\n", mLatency);
}

static ssize_t alsa_raw_delay_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    int mRawDelay = 0;
    mRawDelay = snd_monitor_raw_data_queue();

    return sprintf(buf, "%u\n", mRawDelay);
}

static ssize_t alsa_active_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%u\n", rtk_dec_ao_buffer);
}

static ssize_t alsa_active_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    unsigned long val;

    if (kstrtoul(buf, 10, &val) < 0)
        return -EINVAL;

    //ALSA_VitalPrint("rtk_dec_ao value %d\n", val);
    if (val >= 4096 && val <= (12*1024))
        rtk_dec_ao_buffer = val;
    else
        ALSA_WARNING("set dec_ao_buffer failed! (size must be from 4k to 12k)\n");

    return count;
}

static struct kobj_attribute alsa_active_attr =
    __ATTR(dec_ao_buffer_size, 0644, alsa_active_show, alsa_active_store);

static struct kobj_attribute alsa_latency_attr =
    __ATTR(latency, 0444, alsa_latency_show, NULL);

static struct kobj_attribute alsa_raw_delay_attr =
    __ATTR(rawdelay, 0444, alsa_raw_delay_show, NULL);

static struct attribute *alsa_attrs[] = {
    &alsa_active_attr.attr,
    &alsa_latency_attr.attr,
    &alsa_raw_delay_attr.attr,
    NULL,
};

static struct attribute_group rtk_alsa_attr_group = {
    .attrs = alsa_attrs,
};

static struct kobject *alsa_kobj;

static int __init alsa_sysfs_init(void)
{
    int ret;

    alsa_kobj = kobject_create_and_add("rtk_alsa", kernel_kobj);
    if (!alsa_kobj)
        return -ENOMEM;
    ret = sysfs_create_group(alsa_kobj, &rtk_alsa_attr_group);
    if (ret)
        kobject_put(alsa_kobj);
    return ret;
}
#endif

static int snd_card_probe(struct platform_device *devptr)
{
    snd_card_t *card;
    RTK_snd_card_t *pRTKSnd;
    int dev = devptr->id;
    int idx, err;

    TRACE_CODE("[%s %s %d] dev %d\n", __FILE__, __FUNCTION__, __LINE__, dev);
    RTK_TRACE_ALSA("[+] @ %s\n", __func__);

    // create sound card
    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    err = snd_card_new(
        &devptr->dev,
        -1, /* -1 ; idx == -1 == 0xffff means: take any free slot*/
        SND_REALTEK_DRIVER, /* describe ID string of sound card */
        THIS_MODULE,
        sizeof(RTK_snd_card_t), // size of private_data
        &card);
    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    if (err < 0)
        return err;

    // private data
    pRTKSnd = (RTK_snd_card_t *)card->private_data;
    pRTKSnd->card = card;

    for (idx = 0; idx < MAX_PCM_DEVICES ; idx++)
    {
        // create PCM instance
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
        if ((err = snd_card_create_PCM_instance(pRTKSnd, idx
            , pcm_substreams[dev], pcm_capture_substreams[dev])) < 0)
        {
            ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
            goto __nodev;
        }
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);

        // create Compress instance
        if ((err = snd_card_create_compress_instance(pRTKSnd, idx)) < 0) {
            ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
            goto __nodev;
        }
    }

	// create another instance ONLY for capture AI I2S in
	snd_card_create_PCM_instance(pRTKSnd, 1, 0, 1);

	// create instance ONLY for capture AI nonpcm in
	snd_card_create_PCM_instance(pRTKSnd, 2, 0, 1);

	// create instance ONLY for capture AI audio in
	snd_card_create_PCM_instance(pRTKSnd, 3, 0, 1);

	// create instance ONLY for capture AI audio v2 in
	snd_card_create_PCM_instance(pRTKSnd, 4, 0, 1);

	// create instance ONLY for capture AI audio v3 in
	snd_card_create_PCM_instance(pRTKSnd, 5, 0, 1);

    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    if ((err = snd_card_mars_new_mixer(pRTKSnd)) < 0)
        goto __nodev;
    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);

    strcpy(card->driver, SND_REALTEK_DRIVER);
    strcpy(card->shortname, SND_REALTEK_DRIVER);
    sprintf(card->longname, SND_REALTEK_DRIVER);

    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    if ((err = snd_card_register(card)) == 0) {
        snd_RTK_cards[dev] = card;
        platform_set_drvdata(devptr, card);
        RTK_TRACE_ALSA("[-] @ %s %d\n", __func__, __LINE__);
        return 0;
    }

    // error handling
__nodev:
    ALSA_WARNING("[%s %d fail]\n", __FUNCTION__, __LINE__);
    snd_card_free(card);
    return err;
}

static int snd_card_remove(struct platform_device *devptr)
{
    struct snd_card *card = platform_get_drvdata(devptr);

    RTK_TRACE_ALSA("[+] @ %s\n", __func__);
    if (card) {
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
        snd_card_free(card);
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
        platform_set_drvdata(devptr, NULL);
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    }

    RTK_TRACE_ALSA("[-] @ %s\n", __func__);
    return 0;
}

#ifdef CONFIG_PM
static int rtk_alsa_suspend(struct device *pdev)
{
    struct snd_card *card = dev_get_drvdata(pdev);

    //snd_card_t *card = snd_RTK_cards[0];
    struct RTK_snd_card *pRTKSnd = card->private_data;

    ALSA_VitalPrint("[+]%s %d\n", __FUNCTION__, __LINE__);
    snd_power_change_state(card, SNDRV_CTL_POWER_D3hot);

    is_suspend = true;
    snd_pcm_suspend_all(pRTKSnd->pcm);

    ALSA_VitalPrint("[-]%s %d\n", __FUNCTION__, __LINE__);
    return 0;
}

static int rtk_alsa_resume(struct device *pdev)
{
    struct snd_card *card = dev_get_drvdata(pdev);

    ALSA_VitalPrint("[+]%s %d\n", __FUNCTION__, __LINE__);
    snd_power_change_state(card, SNDRV_CTL_POWER_D0);
    is_suspend = false;

    ALSA_VitalPrint("[-]%s %d\n", __FUNCTION__, __LINE__);
    return 0;
}

static SIMPLE_DEV_PM_OPS(rtk_alsa_pm, rtk_alsa_suspend, rtk_alsa_resume);
#define RTK_ALSA_PM_OPS &rtk_alsa_pm
#else
#define RTK_ALSA_PM_OPS NULL
#endif

static struct platform_driver rtk_alsa_driver = {
    .probe      = snd_card_probe,
    .remove     = snd_card_remove,
    .driver     = {
        .name   = SND_REALTEK_DRIVER,
        .owner  = THIS_MODULE,
        .pm     = RTK_ALSA_PM_OPS,
    },
};

static void rtk_alsa_unregister_all(void)
{
    int i;

    ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);

    for(i = 0; i < ARRAY_SIZE(devices); ++i)
        platform_device_unregister(devices[i]);
    platform_driver_unregister(&rtk_alsa_driver);
}

static int __init RTK_alsa_card_init(void)
{
    int i, cards, ret, err;
#ifdef CONFIG_RTK_XEN_SUPPORT
    if (xen_domain() && xen_initial_domain()) {
        RTK_TRACE_ALSA("%s: skip on dom0\n", __func__);
        return 0;
    }
#endif
    RTK_TRACE_ALSA("[+] @ %s\n", __func__);
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    err = platform_driver_register(&rtk_alsa_driver);
    RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
    if (err < 0)
        goto RETURN_ERR;

#ifdef USE_ION_AUDIO_HEAP
	if (IS_ERR_OR_NULL(rtk_phoenix_ion_device))
		goto RETURN_ERR;
    alsa_client = ion_client_create(rtk_phoenix_ion_device, "ALSADriver");
#endif

#ifdef CONFIG_SYSFS
    ret = alsa_sysfs_init();
    if (ret)
        ALSA_VitalPrint("%s: unable to create sysfs entry\n", __FUNCTION__);
#endif

    cards = 0;
    for (i = 0; i < SNDRV_CARDS && snd_card_enable[i]; i++)
    {
        struct platform_device *device;
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
        device = platform_device_register_simple(SND_REALTEK_DRIVER, i, NULL, 0);
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);

        if (IS_ERR(device))
        {
            continue;
        }

        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);
        if (!platform_get_drvdata(device)) {
            platform_device_unregister(device);
            continue;
        }
        RTK_TRACE_ALSA(" @ %s %d\n", __func__, __LINE__);

        devices[i] = device;
        cards++;
    }

    if (!cards)
    {
        ALSA_VitalPrint("[ALSA %s %d fail]\n", __FUNCTION__, __LINE__);
        rtk_alsa_unregister_all();
        err = -ENODEV;
        goto RETURN_ERR;
    }

    clk90k_vaddr_hi = ioremap(MIS_CLK90K_TM_HI_reg, 4);
    clk90k_vaddr_lo = ioremap(MIS_CLK90K_TM_LO_reg, 4);
    sys_clk_en2_virt = ioremap(SYS_CLOCK_ENABLE2, 4);

    RTK_TRACE_ALSA("[-] @ %s %d\n", __func__, __LINE__);
    return 0;

RETURN_ERR:
    RTK_TRACE_ALSA("[-] @ %s %d\n", __func__, __LINE__);
    return err;
}

static void __exit RTK_alsa_card_exit(void)
{
#ifdef CONFIG_RTK_XEN_SUPPORT
    if (xen_domain() && xen_initial_domain()) {
        RTK_TRACE_ALSA("%s: skip on dom0\n", __func__);
        return;
    }
#endif
    //ALSA_VitalPrint("[ALSA %s %d]\n", __FUNCTION__, __LINE__);
    RTK_TRACE_ALSA("[+] @ %s\n", __func__);

    iounmap(clk90k_vaddr_hi);
    clk90k_vaddr_hi = NULL;
    iounmap(clk90k_vaddr_lo);
    clk90k_vaddr_lo = NULL;
    iounmap(sys_clk_en2_virt);
    sys_clk_en2_virt  = NULL;

#ifdef USE_ION_AUDIO_HEAP
    if (alsa_client != NULL)
    {
        printk("%s ion_client_destroy\n", __FUNCTION__);
        ion_client_destroy(alsa_client);
    }
#endif

    rtk_alsa_unregister_all();
    RTK_TRACE_ALSA("[-] @ %s\n", __func__);
}

module_init(RTK_alsa_card_init);
module_exit(RTK_alsa_card_exit);

EXPORT_SYMBOL(snd_realtek_capture_check_hdmirx_enable);
EXPORT_SYMBOL(snd_realtek_capture_get_stream_name);
