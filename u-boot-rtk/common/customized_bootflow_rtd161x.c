#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <search.h>
#include <errno.h>
#include <malloc.h>
#include <psci.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/factorylib_ro.h>
#include <customized.h>
#include <rtc.h>
#include <asm/arch/platform_lib/board/power.h>
#include <asm/arch/cpu.h>
#include <asm/arch/ir.h>

#include <asm/arch/rtk_ipc_shm.h>
#include <watchdog.h>

#define SETMASK(bits, pos)          (((-1U) >> (32-bits))  << (pos))
#define CLRMASK(bits, pos)          (~(SETMASK(bits, pos)))
#define SET_VAL(val,bits,pos)       ((val << pos) & SETMASK(bits, pos))
#define GET_VAL(reg,bits,pos)       ((reg & SETMASK(bits, pos)) >> pos)
#define PWR_KEY_IGPIO	2

extern BOOT_MODE boot_mode;
extern int ipc_ir_set;
extern int getISOGPIO(int ISOGPIO_NUM);

#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1

#define REBOOT_MAGIC		0xaabbcc00
#define REBOOT_MAGIC_SHIFT	8
#define REBOOT_ACTION_VALID(v)	!((REBOOT_MAGIC ^ (v)) >> REBOOT_MAGIC_SHIFT)

#define ACPU_NOTIFY_MAGIC	(0xea000000)
#define ACPU_POWUP_SOURCE(reg)	GET_VAL(reg, 8, 16)
#define BOOT_REASON_VALID(x)	(!((ACPU_NOTIFY_MAGIC ^ (x)) >> 24))

#define ACRECOVERY_PATH		FACTORY_HEADER_FILE_NAME"ACRECOVERY"
#define POWER_STAT_PATH		FACTORY_HEADER_FILE_NAME"SHUTDOWN"
#define POWER_UP_RTC_PATH	FACTORY_HEADER_FILE_NAME"RTC"
#define WAKE_ON_LAN_PATH	FACTORY_HEADER_FILE_NAME"WAKEONLAN"

#define SUSPEND_ISO_GPIO_SIZE 86

struct suspend_param {
	unsigned int wakeup_source;
	unsigned int timerout_val;
	char wu_gpio_en[SUSPEND_ISO_GPIO_SIZE];
	char wu_gpio_act[SUSPEND_ISO_GPIO_SIZE];
	struct RTK119X_ipc_shm_ir irda_info;
}__attribute__((packed));

struct suspend_param *pcpu_data;

enum {
	PUP_NONE = 0,
	PUP_UNKNOWN,
	PUP_IR,
	PUP_GPIO,
	PUP_LAN,
	PUP_ALARM,
	PUP_TIMER,
	PUP_CEC,
	PUP_MAX, // always place at last
} POWER_UP_REASON;

const char *const pup_reason_str[] = {
	"None",
	"Unknown",
	"IR",
	"GPIO",
	"LAN",
	"ALARM",
	"TIMER",
	"CEC"
};

unsigned int wake_up_src =
	fWAKEUP_ON_IR |
	fWAKEUP_ON_GPIO |
	fWAKEUP_ON_CEC;

void set_shared_memory_ir_tbl(struct RTK119X_ipc_shm_ir *tbl_addr)
{
	memcpy(&ipc_ir, tbl_addr, sizeof(ipc_ir));
	ipc_ir_set = 1;
}

static int check_acpu_boot_notification(void)
{
	unsigned int boot_reason = rtd_inl(ACPU_BOOT_NOTIFY);

	printf("%s, boot-reason : 0x%08x\n", __func__, boot_reason);
	rtd_outl(ACPU_BOOT_NOTIFY, ~0);

	if (REBOOT_ACTION_VALID(boot_reason)) {
		printf("Reboot triggered by Kernel\n");
		return 1;
	}

	if (BOOT_REASON_VALID(boot_reason)) { // check if valid, and which source
		boot_reason = ACPU_POWUP_SOURCE(boot_reason);

		if (boot_reason < PUP_MAX)
			printf("ACPU notify Power-UP source %s\n", pup_reason_str[boot_reason]);
		else
			printf("Couldn't identify ACPU Power-UP source 0x%x\n", boot_reason);

		return 1;
	}

	return 0;
}

static int check_rtc_expire(void)
{
	char *buff = NULL;
	struct rtc_time alarm_record, rtc_curr, alarm_tmp;
	int length = 0;
	unsigned long curr_sec, alarm_sec;

	if (factory_read(POWER_UP_RTC_PATH, &buff, &length)) {
		printf("%s:RTC not detected in factory\n", __func__);
		/* Disabled due to uP flage change:
		 * Need check if both ACRECOVERY and SHUTDOWN are set.
		 */
		return -1;
	}

	if (length != sizeof(struct rtc_time)) {
		printf("%s:RTC format not match\n", __func__);
		return 0;
	}

	memcpy(&alarm_record, buff, sizeof(struct rtc_time));
	// If we found that RTC clock is not working, but there
	// is an ALARM record, just boot-up since we can't identify the time.
	if (rtc_get(&rtc_curr)) {
		printf("%s:RTC read fail, boot-up directly!\n", __func__);
		return 1;
	}

	//curr_sec = mktime(rtc_curr.tm_year, rtc_curr.tm_mon, rtc_curr.tm_mday,
	//			rtc_curr.tm_hour, rtc_curr.tm_min, rtc_curr.tm_sec);
	curr_sec = rtc_mktime(&rtc_curr);
	printf("Current-RTC: Date: %4d-%02d-%02d Time: %2d:%02d:%02d\n",
		rtc_curr.tm_year, rtc_curr.tm_mon, rtc_curr.tm_mday,
		rtc_curr.tm_hour, rtc_curr.tm_min, rtc_curr.tm_sec);
	// rtc_time for RTC ALARM is set with following format :
	// tm_year : offset from 1900
	// tm_mon : count from 0~11
	// tm_sec : not available
	//alarm_sec = mktime(alarm_record.tm_year + 1900, alarm_record.tm_mon + 1, alarm_record.tm_mday,
	//			alarm_record.tm_hour, alarm_record.tm_min, 0);
	//to_tm(alarm_sec, &alarm_record);
	memcpy(&alarm_tmp, &alarm_record, sizeof(struct rtc_time));
	alarm_tmp.tm_year += 1900;
	alarm_tmp.tm_mon += 1;
	alarm_tmp.tm_sec = 0;
	alarm_sec = rtc_mktime(&alarm_tmp);
	rtc_to_tm(alarm_sec, &alarm_record);
	printf("ALARM-RTC: Date: %4d-%02d-%02d Time: %2d:%02d:%02d\n",
		alarm_record.tm_year, alarm_record.tm_mon, alarm_record.tm_mday,
		alarm_record.tm_hour, alarm_record.tm_min, alarm_record.tm_sec);

	if ((curr_sec + 30) >= alarm_sec)
		return 1;

	// Need to reset ALARM since interrupt config will drop after reset/power-cycle
	if(rtc_alarm_set(&alarm_record)) {
		printf("%s: ALARM set fail, boot-up directly\n", __func__);
		return 1;
	}

	return 0;
}

void cmd_bl31_set_pm_param(unsigned int pcpu_data)
{
	//process set pm param
	asm volatile("isb" : : : "cc");
	asm volatile("mov x1, %0" : : "r" (pcpu_data) : "cc");
	asm volatile("ldr x0, =0x8400ff04" : : : "cc");
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
}

void cmd_bl31_pcpu_power_off(void)
{
	//process pcpu power off
	asm volatile("mov x1, %0" : :"r"(0): "cc");
	asm volatile("mov x2, %0" : :"r"(0): "cc");
	asm volatile("mov x3, %0" : :"r"(0): "cc");
	asm volatile("mov x0, %0" : :"r"(PSCI_0_2_FN_SYSTEM_OFF): "cc"); //function id
	asm volatile("isb" : : : "cc");
	asm volatile("smc #0" : : : "cc");
	asm volatile("isb" : : : "cc");
}

int customize_check_normal_boot(void)
{
	char *dst_addr;
	int dst_length;
	int save = 0;
	int rtc = 0;
	struct RTK119X_ipc_shm_ir tmp_ipc_ir;
	int key_stat = getISOGPIO(PWR_KEY_IGPIO);

	printf("Power-Key stat:%d\n", key_stat);

	// Always say yes if bootmode isn't normal boot
	if (boot_mode != BOOT_NORMAL_MODE)
		return 1;

	// Check ACPU notification first (RTC-ALARM / Power-Button / WOL)
	if (check_acpu_boot_notification()) {
		printf("%s : bootup from ACPU notify\n", __func__);
		goto bootup;
	}

	// Check RTC expiration
	rtc = check_rtc_expire();
	if (rtc > 0) {
		printf("%s : bootup from RTC expire\n", __func__);
		goto bootup;
	}

	// Check ACRECOVERY, if set, need to check power status
	if (!factory_read(ACRECOVERY_PATH, &dst_addr, &dst_length)) {
		printf("%s: ACRECOVERY detected\n", __func__);
		if (!factory_read(POWER_STAT_PATH, &dst_addr, &dst_length)) {
			printf("%s: device was in shutdown stat, skip normal boot!\n", __func__);
		} else {
			printf("%s: device normal boot from AC-Recovery\n", __func__);
			goto bootup;
		}
	}
#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1_PHASE_1
	/* Power is cut-off by uP if both ACRECOVERY and RTC is not set. */
	else if(rtc < 0){
		printf("%s: power up by button\n", __func__);
		goto bootup;
	}
#endif
	if (!factory_read(WAKE_ON_LAN_PATH, &dst_addr, &dst_length)) {
		unsigned int lanwake = rtd_inl(0x980160d0);
		printf("%s: wake-on-lan detected\n", __func__);
		rtd_outl(0x980160d0, lanwake | 0x80000000);
	}


#ifdef CONFIG_POWER_DOWN_S5

#if defined(CONFIG_CMD_I2C) && defined(CONFIG_APW8889_S5)
	printf("pmic-apw8889: config sleep mode\n");
	run_command_list("i2c dev 0", -1, 0);
	run_command_list("i2c mw 12 08 33", -1, 0);
#if defined(CONFIG_APW8889_S5_DC5_SHUTDOWN)
	run_command_list("i2c mw 12 09 32", -1, 0);
#endif
	run_command_list("i2c mw 12 11 28", -1, 0);
	run_command_list("i2c mw 12 12 1C", -1, 0);
#endif

	memset(&tmp_ipc_ir, 0, sizeof(tmp_ipc_ir));
	IR_init();
	IR_config_wakeup_keys(&tmp_ipc_ir);

	/* Send to wake up source to pcpu fw by bl31 */
	pcpu_data = malloc(sizeof(struct suspend_param));
	memset(pcpu_data, 0, sizeof(struct suspend_param));
	pcpu_data->wakeup_source = SWAPEND32(fWAKEUP_ON_IR | fWAKEUP_ON_GPIO | fWAKEUP_ON_LAN);
	pcpu_data->wu_gpio_en[PWR_KEY_IGPIO] = 1;
	pcpu_data->wu_gpio_act[PWR_KEY_IGPIO] = 0;
	pcpu_data->irda_info = tmp_ipc_ir;
	flush_cache((unsigned int)(uintptr_t)pcpu_data, sizeof(struct suspend_param));
	cmd_bl31_set_pm_param((unsigned int)(uintptr_t)pcpu_data);

	// First, disable pmic reset so dummy register could be passed
	disable_soc_full_reset();

	/* Send the smc command to bl31, let pcpu do power off */
	cmd_bl31_pcpu_power_off();

#endif // CONFIG_POWER_DOWN_S5

	return 0;

bootup:
	if (!factory_read(POWER_STAT_PATH, &dst_addr, &dst_length)) {
		// clear SHUTDOWN FLAG
		factory_delete(POWER_STAT_PATH);
		save = 1;
	}

	// clear RTC ?? or Kernel will clear it ??
	//factory_delete(POWER_UP_RTC_PATH);

	if(save)
		factory_save();

	return 1;
}
#endif // CONFIG_CUSTOMIZE_BOOTFLOW_1
