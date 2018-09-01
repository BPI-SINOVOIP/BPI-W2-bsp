/* RTK usb init, clock, reset, power gpio*/
#include <common.h>
#include <linux/string.h>
//#include <stdio.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <asm/arch/usb.h>
#include <asm/arch/usb-phy.h>
#include <asm/arch/cpu.h>

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug



// CRT_SOFT_RESET usb part
#define rstn_type_c 		(0x1 << 20)
#define rstn_usb 			(0x1 << 19)
#define rstn_usb_phy2 		(0x1 << 18)
#define rstn_usb_phy1 		(0x1 << 17)
#define rstn_usb_phy0 		(0x1 << 16)
#define rstn_usb_host_mac 	(0x1 << 15)
#define rstn_usb_drd_mac 	(0x1 << 14)
// CRT_CLOCK_ENABLE usb part
#define clk_en_usb 			(0x1 << 16)
#define clk_en_usb_host1 	(0x1 << 15)
#define clk_en_usb_host2 	(0x1 << 14)
#define clk_en_usb_drd 		(0x1 << 13)

void rtk_usb_clock_init(void)
{
	void *reset = (void *)ISO_CRT_BASE + 0x0;
	void *clk_en = (void *)ISO_CRT_BASE + 0x4;

	int reset_pll_flag = rstn_usb_phy0 | rstn_usb_phy1 | rstn_usb_phy2;
	int reset_usb_flag = rstn_usb_drd_mac | rstn_usb_host_mac |
		                 rstn_type_c | rstn_usb;

	int clk_en_domain_flag = clk_en_usb;

	int clk_en_phy_flag = clk_en_usb_host1 | clk_en_usb_host2 | clk_en_usb_drd;

	LTRACEF("Realtek-usb: init start soft_reset=%x, clock_enable=%x\n",
		    (uint32_t)(readl((volatile u32*)reset)),
		    (uint32_t)(readl((volatile u32*)clk_en)));

	//Enable PLL
	writel(reset_pll_flag | readl((volatile u32*)reset), (volatile u32*) reset);

	mdelay(200);
	LTRACEF("Realtek-usb: Enable PLL soft_reset=%x, clock_enable=%x\n",
		    (uint32_t)(readl((volatile u32*)reset)),
		    (uint32_t)(readl((volatile u32*)clk_en)));

	//Turn on USB clk
	writel(clk_en_domain_flag | readl((volatile u32*)clk_en),
		    (volatile u32*) clk_en);
	writel(~clk_en_domain_flag & readl((volatile u32*)clk_en),
		    (volatile u32*) clk_en);
	mdelay(10);

	LTRACEF("Realtek-usb: trigger CLK_EN_USB soft_reset=%x, clock_enable=%x\n",
		    (uint32_t)(readl((volatile u32*)reset)),
		    (uint32_t)(readl((volatile u32*)clk_en)));

	writel(reset_usb_flag | readl((volatile u32*)reset), (volatile u32*) reset);
	mdelay(10);
	LTRACEF("Realtek-usb: Turn on all RSTN_USB soft_reset=%x, clock_enable=%x\n",
		    (uint32_t)(readl((volatile u32*)reset)),
		    (uint32_t)(readl((volatile u32*)clk_en)));

	writel(clk_en_domain_flag | readl((volatile u32*)clk_en),
		    (volatile u32*) clk_en);
	mdelay(10);
	writel(clk_en_phy_flag | readl((volatile u32*)clk_en),
		    (volatile u32*) clk_en);
	LTRACEF("Realtek-usb: Turn on CLK_EN_USB soft_reset=%x, clock_enable=%x\n",
		(uint32_t)(readl((volatile u32*)reset)),
		(uint32_t)(readl((volatile u32*)clk_en)));

	LTRACEF("Realtek-usb: Turn on USB OK soft_reset=%x, clock_enable=%x\n",
		(uint32_t)(readl((volatile u32*)reset)),
		(uint32_t)(readl((volatile u32*)clk_en)));
}

void rtk_usb_clock_stop(void)
{
	void *reset = (void *)ISO_CRT_BASE + 0x0;
	void *clk_en = (void *)ISO_CRT_BASE + 0x4;

	int reset_pll_flag = rstn_usb_phy0 | rstn_usb_phy1 | rstn_usb_phy2;
	int reset_usb_flag = rstn_type_c | rstn_usb | rstn_usb_drd_mac |
		    rstn_usb_host_mac;

	int clk_en_domain_flag = clk_en_usb;

	int clk_en_phy_flag = clk_en_usb_host1 | clk_en_usb_host2 | clk_en_usb_drd;

	//Stop PLL
	writel(~(reset_pll_flag | reset_usb_flag) &
		    readl((volatile u32*)reset), (volatile u32*) reset);

	writel(~(clk_en_domain_flag | clk_en_phy_flag) &
		    readl((volatile u32*)clk_en), (volatile u32*) clk_en);

	TRACEF("Realtek-usb: stop soft_reset=%x, clock_enable=%x\n",
		(uint32_t)(readl((volatile u32*)reset)),
		(uint32_t)(readl((volatile u32*)clk_en)));
}

// for none define GPIO
/* define 1295 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#ifndef USB_PORT0_GPIO_TYPE
#define USB_PORT0_GPIO_TYPE "NO_DEFINE"
#define USB_PORT0_GPIO_NUM 0
#endif
#ifndef USB_PORT0_TYPE_C_SWITCH_GPIO_TYPE
#define USB_PORT0_TYPE_C_SWITCH_GPIO_TYPE "NO_DEFINE"
#define USB_PORT0_TYPE_C_SWITCH_GPIO_NUM 0
#endif
/* Port 1, xhci u2 host */
#ifndef USB_PORT1_GPIO_TYPE
#define USB_PORT1_GPIO_TYPE "NO_DEFINE"
#define USB_PORT1_GPIO_NUM  0
#endif
/* Port 2, xhci u2 host */
#ifndef USB_PORT2_GPIO_TYPE
#define USB_PORT2_GPIO_TYPE "NO_DEFINE"
#define USB_PORT2_GPIO_NUM  0
#endif

#define USB_GPIO(GPIO_TYPE, NUM, enable) \
do {  \
	LTRACEF("SET %s #%d enable=%d\n", GPIO_TYPE, NUM, enable); \
	if (!strcmp(GPIO_TYPE, "ISOGPIO")) \
		setISOGPIO(NUM, enable); \
	else if (strcmp(GPIO_TYPE, "NONE")) \
		printf("ERROR GPIO Type %s\n", GPIO_TYPE); \
} while (0)

/* PORT0, XHCI DRD, TYPE C */
#define USB_PORT0_POWER(enable) \
do { \
	USB_GPIO(USB_PORT0_GPIO_TYPE, USB_PORT0_GPIO_NUM, !enable); \
} while (0)

#define USB_PORT0_SWITCH(enable) \
do { \
	USB_GPIO(USB_PORT0_TYPE_C_SWITCH_GPIO_TYPE, \
		    USB_PORT0_TYPE_C_SWITCH_GPIO_NUM, enable); \
} while (0)

/* PORT1, XHCI u2host */
#define USB_PORT1_POWER(enable) \
do { \
	USB_GPIO(USB_PORT1_GPIO_TYPE, USB_PORT1_GPIO_NUM, !enable); \
} while (0)

/* PORT2, XHCI u2host */
#define USB_PORT2_POWER(enable) \
do { \
	USB_GPIO(USB_PORT2_GPIO_TYPE, USB_PORT2_GPIO_NUM, !enable); \
} while (0)
#define ENABLE_EXTERNAL_RD 0x20000000
#define ENABLE_INTERNAL_RD 0x2
#define UFP_CC1_CODE 0x03D6E801
#define UFP_CC2_CODE 0x02D2E781
#define UFP_CC1_COMP 0x01C1D877
#define UFP_CC2_COMP 0x05CDDA77
#define DFP_3A_CC1_CODE 0x03D6E871
#define DFP_3A_CC2_CODE 0x02D2E7F1
#define DFP_3A_CC1_COMP 0x01C1D877
#define DFP_3A_CC2_COMP 0x05CDDA77

void rtk_usb_power_on(void)
{
	int check, type_c_have_device = 0;
	int internal_rd = 0;

	USB_PORT0_SWITCH(0);
	mdelay(10);

	if (internal_rd) {
		writel(UFP_CC1_COMP, (volatile u32*) USB_TYPEC_CTRL_CC1_1);
		writel(UFP_CC2_COMP, (volatile u32*) USB_TYPEC_CTRL_CC2_1);
		writel(UFP_CC1_CODE | ENABLE_INTERNAL_RD,
			    (volatile u32*) USB_TYPEC_CTRL_CC1_0);
		writel(UFP_CC2_CODE | ENABLE_INTERNAL_RD,
			    (volatile u32*) USB_TYPEC_CTRL_CC2_0);
	} else {
		writel(UFP_CC1_COMP, (volatile u32*) USB_TYPEC_CTRL_CC1_1);
		writel(UFP_CC2_COMP, (volatile u32*) USB_TYPEC_CTRL_CC2_1);
		writel(UFP_CC1_CODE | ENABLE_EXTERNAL_RD,
			    (volatile u32*) USB_TYPEC_CTRL_CC1_0);
		writel(UFP_CC2_CODE, (volatile u32*) USB_TYPEC_CTRL_CC2_0);
	}
	mdelay(10);

	check = readl((volatile u32*)USB_TYPEC_STS);
		LTRACEF("Realtek-usb: UFP check type_c cc status=0x%x\n", check);
	if ((check & 0x7) != 0x0) {
		TRACEF("Realtek-usb: UFP cc1 detect type_c have power (status=0x%x)\n",
			    check);
		goto out;
	} else if ((check & 0x38) != 0x0) {
		TRACEF("Realtek-usb: UFP cc2 detect type_c have power (status=0x%x)\n",
			    check);
		goto out;
	}

	writel(DFP_3A_CC1_COMP, (volatile u32*) USB_TYPEC_CTRL_CC1_1);
	writel(DFP_3A_CC2_COMP, (volatile u32*) USB_TYPEC_CTRL_CC2_1);
	writel(DFP_3A_CC1_CODE, (volatile u32*) USB_TYPEC_CTRL_CC1_0);
	writel(DFP_3A_CC2_CODE, (volatile u32*) USB_TYPEC_CTRL_CC2_0);

	mdelay(1);

	check = readl((volatile u32*)USB_TYPEC_STS);
	LTRACEF("Realtek-usb: DFP check type_c cc status=0x%x\n", check);
	if ((check & 0x7) != 0x7) {
		LTRACEF("Realtek-usb: DFP cc1 detect (status=0x%x)\n", check);
		type_c_have_device = 1;
	} else if ((check & 0x38) != 0x38) {
		LTRACEF("Realtek-usb: DFP cc2 detect (status=0x%x)\n", check);
		type_c_have_device = 1;
	}

	//Type C 5V
	if (type_c_have_device) {
		TRACEF("Realtek-usb: Turn on port 0 power (QA board)\n");
		USB_PORT0_SWITCH(1);
	}

out:
	//Usb2 5V
	LTRACEF("Realtek-usb: Turn on port 0, 1 and 2 power\n");
	USB_PORT0_POWER(1);
	USB_PORT1_POWER(1);
	USB_PORT2_POWER(1);
}

void rtk_usb_power_off(void)
{
	USB_PORT0_POWER(0);
	USB_PORT1_POWER(0);
	USB_PORT2_POWER(0);
}

int rtk_usb_device_init(struct rtk_usb **rtk_usb)
{
	struct rtk_usb *rtkusb;
	size_t count = USB_DEVICE_NUM;
	size_t ctrl_count, i, j;

	ctrl_count = 0;
	for (i = 0; i < count; i++) {
		if (GET_DEVICE_PROP(ENABLE, i) == 1)
			ctrl_count++;
	}

	*rtk_usb = malloc(sizeof(struct rtk_usb) * ctrl_count);
	memset(*rtk_usb, 0, sizeof(struct rtk_usb) * ctrl_count);

	j = 0;
	for (i = 0; i < count; i++) {
		if (GET_DEVICE_PROP(ENABLE, i) == 0)
			continue;
		rtkusb = &((*rtk_usb)[j]);
		rtkusb->controller_id = GET_DEVICE_PROP(CTRL_ID, i);
		rtkusb->controller_type = DEVICE_CTRL;
		rtkusb->class_type = GET_DEVICE_PROP(TYPE, i);
		rtkusb->reg_base = GET_DEVICE_PROP(ADDR, i);
		rtkusb->wrap_base = GET_DEVICE_PROP(WRAP_ADDR, i);

		get_rtk_usb_phy2(rtkusb);
		get_rtk_usb_phy3(rtkusb);

		rtkusb->ctrl_count = ctrl_count - j;

		LTRACEF("i=%d rtkusb@%p, controller_id=%d, controller_type=%d\n",
			    (int)i, rtkusb, rtkusb->controller_id, rtkusb->controller_type);
		LTRACEF("     class_type=%d, reg_base=0x%x, wrap_base=0x%x\n",
			    rtkusb->class_type, rtkusb->reg_base, rtkusb->wrap_base);
		LTRACEF("     usb2phy@%p, usb3phy@%p, ctrl_count=%d\n",
			    rtkusb->usb2phy, rtkusb->usb3phy, rtkusb->ctrl_count);
		j++;
	}
	return ctrl_count;
}

int rtk_usb_device_stop(struct rtk_usb **rtk_usb)
{
	if (*rtk_usb) {
		free(*rtk_usb);
		*rtk_usb = NULL;
	}
	return 0;
}

int rtk_usb_host_init(struct rtk_usb **rtk_usb)
{
	struct rtk_usb *rtkusb;
	size_t count = USB_HOST_NUM;
	size_t ctrl_count, i, j;

	LTRACEF("Realtek USB: Host count=%d\n", (int)count);

	ctrl_count = 0;
	for (i = 0; i < count; i++) {
		if (GET_HOST_PROP(ENABLE, i) == 1)
			ctrl_count++;
	}

	*rtk_usb = malloc(sizeof(struct rtk_usb) * ctrl_count);
	memset(*rtk_usb, 0, sizeof(struct rtk_usb) * ctrl_count);

	j = 0;
	for (i = 0; i < count; i++) {
		if (GET_HOST_PROP(ENABLE, i) == 0)
			continue;
		rtkusb = &((*rtk_usb)[j]);
		rtkusb->controller_id = GET_HOST_PROP(CTRL_ID, i);
		rtkusb->controller_type = HOST_CTRL;
		rtkusb->class_type = GET_HOST_PROP(TYPE, i);
		rtkusb->reg_base = GET_HOST_PROP(ADDR, i);
		rtkusb->wrap_base = GET_HOST_PROP(WRAP_ADDR, i);

		get_rtk_usb_phy2(rtkusb);
		get_rtk_usb_phy3(rtkusb);

		rtkusb->ctrl_count = ctrl_count - j;

		LTRACEF("i=%d rtkusb@%p, controller_id=%d, controller_type=%d\n",
			    (int)i, rtkusb, rtkusb->controller_id, rtkusb->controller_type);
		LTRACEF("     class_type=%d, reg_base=0x%x, wrap_base=0x%x\n",
			    rtkusb->class_type, rtkusb->reg_base, rtkusb->wrap_base);
		LTRACEF("     usb2phy@%p, usb3phy@%p, ctrl_count=%d\n",
			    rtkusb->usb2phy, rtkusb->usb3phy, rtkusb->ctrl_count);

		j++;
	}
	return ctrl_count;

	return 0;
}

int rtk_usb_host_stop(struct rtk_usb **rtk_usb)
{
	if (*rtk_usb) {
		free(*rtk_usb);
		*rtk_usb = NULL;
	}
	return 0;
}

