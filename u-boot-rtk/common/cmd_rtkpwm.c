/*
 * Control GPIO pins on the fly
 *
 * Copyright (c) 2008-2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <command.h>

#include <asm/arch/pwm.h>

enum pwm_cmd {
	PWM_INIT,
	PWM_SHOW,
	PWM_ENABLE,
	PWM_DUTY,
	PWM_FREQ,
};

static int do_pwm(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	uint id = 0, value = 0;
	uint loc = 0;
	//int ret;
	
	id = 0xdeadbeef;
	value = 0xdeadbeef;

	if (argc < 2)
		return CMD_RET_USAGE;

	switch (*argv[1]) {
	case 'i': /* init */
#ifdef CONFIG_RTK_PWM
		rtk_pwm_init();
#endif /* CONFIG_RTK_PWM */
		return 0;

	case 's': /* show */
#ifdef CONFIG_RTK_PWM
		rtk_pwm_show();
#endif /* CONFIG_RTK_PWM */
		return 0;

	case 'e': /* enable */
		if (argc >= 5) {
			id = (uint) simple_strtoul(argv[2], NULL, 10);
			loc = (uint) simple_strtoul(argv[3], NULL, 10);
			value = (uint) simple_strtoul(argv[4], NULL, 10);
#ifdef CONFIG_RTK_PWM
			_rtk_pwm_pinmux(id, loc, value);
			if (pwm_enable(id, value) == 0)
				return 0;
#endif /* CONFIG_RTK_PWM */
		}
		break;

	case 'd': /* duty */
		if (argc >= 4) {
			id = (uint) simple_strtoul(argv[2], NULL, 10);
			value = (uint) simple_strtoul(argv[3], NULL, 10);
#ifdef CONFIG_RTK_PWM
			if (pwm_set_duty_rate(id, value) == 0)
				return 0;
#endif /* CONFIG_RTK_PWM */
		} else if (argc == 3) {
			id = (uint) simple_strtoul(argv[2], NULL, 10);
#ifdef CONFIG_RTK_PWM
			if (pwm_get_duty_rate(id, &value) == 0) {
				printf("PWM %d duty rate %d%%\n", id, value);
				return 0;
			}
#endif /* CONFIG_RTK_PWM */
		}
		break;
	case 'f': /* freq */
		if (argc >= 4) {
			id = (uint) simple_strtoul(argv[2], NULL, 10);
			value = (uint) simple_strtoul(argv[3], NULL, 10);
#ifdef CONFIG_RTK_PWM
			if (pwm_set_freq(id, value) == 0)
				return 0;
#endif /* CONFIG_RTK_PWM */
		} else if (argc == 3) {
			id = (uint) simple_strtoul(argv[2], NULL, 10);
#ifdef CONFIG_RTK_PWM
			if (pwm_get_freq(id, &value) == 0) {
				printf("PWM %d output frequency %d HZ\n", id, value);
				return 0;
			}
#endif /* CONFIG_RTK_PWM */
		}
	}
	
	printf("\nid 0x%x, value 0x%x\n\n", id, value); /* [-Werror=unused-but-set-variable] */

	return CMD_RET_USAGE;
}

U_BOOT_CMD(pwm, 5, 0, do_pwm,
	"Control PWM 0,1,2,3",
	"\t init                      --- set pin mux and PWM initial values\n"
	"\t show                      --- show current setting of PWM 0 ~ 3\n"
	"\t enable <ID> <loc> <1|0>   --- turn on/off PWM <ID> <location>\n"
	"\t duty <ID> [<duty_rate>]   --- get/set duty rate of PWM <ID>\n"
	"\t freq <ID> [<target freq>] --- get/set target frequency of PWM <ID>\n"
	"Parameters:\n"
	"\t ID : <0-3>\n"
	"\t loc : <0-1>\n"
	"\t duty_rate : <0-100>\n"
	"\t freq : <1-52735>\n");

