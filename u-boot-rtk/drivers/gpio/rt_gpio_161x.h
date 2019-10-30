#define PMUX_BASE_ISO	0x9804E000
#define PMUX_BASE_MISC  0x9804F000


#define PADDRI_4_8 1
#define PADDRI_2_4 0
#define PADDRI_UNSUPPORT 0xFFFF

#define PCOF_UNSUPPORT 0xFFFF
#define PMUX_UNSUPPORT 0xFFFF

#define PULL_DISABLE	0
#define PULL_DOWN		1
#define PULL_UP			2



struct rtk_pin_regmap{
	unsigned int pmux_base;
	unsigned int pmux_regoff;
	unsigned int pmux_regbit;
	unsigned int pmux_regbitmsk;
	unsigned int pcof_regoff;
	unsigned int pcof_regbit;
	unsigned int pcof_cur_strgh;//0 : 2&4mA   1:4&8mA
};

int getGPIO(int GPIO_NUM);
int setGPIO(int GPIO_NUM, int value);
int getISOGPIO(int ISOGPIO_NUM);
int setISOGPIO(int ISOGPIO_NUM, int value);
int setGPIO_pullsel(unsigned int GPIO_NUM, unsigned char pull_sel);
int setISOGPIO_pullsel(int ISOGPIO_NUM, unsigned char pull_sel);


static const struct rtk_pin_regmap pin_regmap[] = {
	/*GPIO*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 0, "gpio_0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 1, "gpio_1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  2, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 2, "gpio_2")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  5, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 3, "gpio_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit =  8, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 4, "gpio_4")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 11, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 5, "gpio_5")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 14, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 6, "gpio_6")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 17, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x014, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 7, "gpio_7")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 18, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 8, "gpio_8")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 19, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 9, "gpio_9")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 20, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 10, "gpio_10")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 21, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x018, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 11, "gpio_11")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 22, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 12, "gpio_12")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 13, "gpio_13")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 14, "gpio_14")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 28, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 15, "gpio_15")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 30, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 16, "gpio_16")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x000, .pmux_regbit = 31, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 17, "gpio_17")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 18, "gpio_18")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x01C, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 19, "gpio_19")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  2, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 20, "gpio_20")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  4, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 21, "gpio_21")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  6, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 22, "gpio_22")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit =  8, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 23, "gpio_23")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x00C, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 24, "demod_agc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 10, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 25, "gpio_25")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 13, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 26, "gpio_26")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 16, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 27, "gpio_27")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 19, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 28, "gpio_28")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 22, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x020, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 29, "gpio_29")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 25, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x020, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 30, "gpio_30")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 26, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x020, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 31, "gpio_31")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 32, "sd3_cmd")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 33, "sd3_clk")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 34, "gpio_34")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x004, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 35, "gpio_35")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x00C, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 36, "sd3_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x010, .pcof_regbit = 8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 37, "sd3_data_1")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 15, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x010, .pcof_regbit = 20, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 38, "sd3_data_2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 17, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 39, "sd3_data_3")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 40, "gpio_40")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 41, "gpio_41")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x024, .pcof_regbit = 26, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 42, "gpio_42")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 43, "gpio_43")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 44, "gpio_44")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x028, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 45, "gpio_45")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x02C, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 46, "gpio_46")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 47, "gpio_47")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 23, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x02C, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 48, "gpio_48")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 24, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x02C, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 49, "gpio_49")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 50, "gpio_50")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x008, .pmux_regbit = 27, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x02C, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 51, "gpio_51")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 52, "gpio_52")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  3, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 3, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 53, "ir_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  5, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x030, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 54, "ur0_rx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  6, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x030, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 55, "ur0_tx")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit =  0, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 56, "usb_cc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit =  7, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 57, "gpio_57")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 10, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 58, "gpio_58")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 59, "gpio_59")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 60, "gpio_60")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 31, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 61, "gpio_61")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 21, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x034, .pcof_regbit = 3, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 62, "gpio_62")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 24, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 7, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 63, "gpio_63")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 25, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 11, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 64, "gpio_64")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 26, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x034, .pcof_regbit = 15, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 65, "gpio_65")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 28, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 19, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 66, "gpio_66")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 29, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 23, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 67, "gpio_67")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 30, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x034, .pcof_regbit = 27, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 68, "gpio_68")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x010, .pmux_regbit =  1, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 69, "usb_cc2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 20, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 70, "tp_sync")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 23, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 71, "tp_valid")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 26, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 72, "tp_clk")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x014, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 73, "tp_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x014, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 74, "tp_data_1")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  3, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 75, "tp_data_2")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  6, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 76, "tp_data_3")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit =  9, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 77, "tp_data_4")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 12, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 78, "tp_data_5")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 15, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 79, "tp_data_6")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x008, .pmux_regbit = 18, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x018, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 80, "tp_data_7")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 25, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 81, "hif_data_0")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 27, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x02C, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 82, "hif_rdy")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x000, .pmux_regbit = 29, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x030, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 83, "hif_clk")*/
	{.pmux_base = PMUX_BASE_MISC,.pmux_regoff = 0x004, .pmux_regbit =  0, .pmux_regbitmsk = 0x7,	.pcof_regoff = 0x030, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 84, "hif_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x00C, .pmux_regbit = 31, .pmux_regbitmsk = 0x1,	.pcof_regoff = 0x038, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_2_4}, /*(P_ISO_BASE + 85, "gpio_85")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  0, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 86, "ur2_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  2, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 87, "gspi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  4, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 88, "sdio_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  6, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 89, "hi_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit =  8, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 90, "hi_width")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 10, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 91, "debug_p2s_enable")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 11, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 92, "sf_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 12, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 93, "arm_trace_dbg_en")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 13, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 94, "pwm_01_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 14, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 95, "pwm_23_open_drain_en_loc0")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 15, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 96, "pwm_01_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 16, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 97, "pwm_23_open_drain_en_loc1")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 17, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 98, "ejtag_avcpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 99, "ejtag_scpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 23, .pmux_regbitmsk = 0x1,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 100, "ejtag_scpu_loc")*/
	{.pmux_base = PMUX_BASE_ISO, .pmux_regoff = 0x048, .pmux_regbit = 24, .pmux_regbitmsk = 0x3,	.pcof_regoff = PCOF_UNSUPPORT, .pcof_regbit = 0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 101, "i2c_tg")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  1, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x018, .pcof_regbit = 24, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 102, "emmc_rst")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  3, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 103, "emmc_dd_sb")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  5, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 16, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 104, "emmc_clk")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  7, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x01C, .pcof_regbit = 28, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 105, "emmc_cmd")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit =  9, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 9, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 106, "emmc_data_0")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 11, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x020, .pcof_regbit = 21, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 107, "emmc_data_1")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 13, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 1, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 108, "emmc_data_2")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 15, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 13, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 109, "emmc_data_3")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 17, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x024, .pcof_regbit = 25, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 110, "emmc_data_4")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 19, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 5, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 111, "emmc_data_5")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 21, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 17, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 112, "emmc_data_6")*/
	{.pmux_base = PMUX_BASE_MISC, .pmux_regoff = 0x000, .pmux_regbit = 23, .pmux_regbitmsk = 0x3,	.pcof_regoff = 0x028, .pcof_regbit = 29, .pcof_cur_strgh = PADDRI_UNSUPPORT}, /*(P_ISO_BASE + 113, "emmc_data_7")*/
};


