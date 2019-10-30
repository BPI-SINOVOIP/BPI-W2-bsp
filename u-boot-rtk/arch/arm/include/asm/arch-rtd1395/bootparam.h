#ifndef __BOOT_PARAM_H__
#define __BOOT_PARAM_H__

typedef enum {
	POWER_STATE_OFF = 0,
	POWER_STATE_ON,
} POWER_STATE_T;

typedef struct {
	unsigned int prev_power_state;
	unsigned int boot_logo_enable;
	unsigned int boot_music_enable;
	unsigned int backlight_value;
	unsigned int custom_video1_leng;
	unsigned int custom_video2_leng;
	unsigned int custom_audio1_leng;
	unsigned int custom_audio2_leng;
} bootparam_t;

void get_bootparam(void);
void get_layout(void);
int get_one_step_info(void);
void set_blue_logo_info(void);

#ifdef CONFIG_CUSTOMIZE_NEMO
#define ADDR_VE1_BIN_SWAP 0x0D800000
#define ADDR_SPLASH_H264_MP2 0x0D880000
#define ADDR_SPLASH_H264  0x0D900000
#define SIZE_VE1_BIN_SWAP 0x39000 //228 KB
#define SIZE_SPLASH_H264  0x21C00 //135 KB
#define SIZE_SPLASH_H264_MP2 0x17C00 //95 KB
#define ANIMATION_TOTAL_ADDR 0x0D800000
#define ANIMATION_TOTAL_SIZE 0x01800000 //24 MB
#define ANIMATION_AUDIO_ADDR 0x0DA00000
#define ANIMATION_AUDIO_SIZE 0x400000 //4 MB
#define BOOT_VE1_BIN_FILE_NAME				FACTORY_HEADER_FILE_NAME"ve1.bin.swap"
#define BOOT_SPLASH_H264_FILE_NAME			FACTORY_HEADER_FILE_NAME"splash_h264.h264"
#define BOOT_SPLASH_H264_MP2_FILE_NAME		FACTORY_HEADER_FILE_NAME"splash_h264.mp2"

int set_memo_animation_file(void);
void set_memo_animation_info(void);
#endif

extern bootparam_t bootparam;

#endif /* #define __BOOT_PARAM_H__ */

