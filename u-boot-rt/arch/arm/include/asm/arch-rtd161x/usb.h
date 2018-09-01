/* define rtk usb init api */
#pragma once

#define ISO_CRT_BASE 0x98007088

enum controller_type {
	HOST_CTRL = 1,
	DEVICE_CTRL = 2,
};

enum class_type {
	DWC3_XHCI = 1,
	OTG_EHCI = 2,
};

/* HOST Setting */
#define USB_HOST_NUM 2 // xhci_drd, xhci_u2host

#define USB_HOST0_ENABLE 1 // xhci_drd
#define USB_HOST0_CTRL_ID 0
#define USB_HOST0_TYPE DWC3_XHCI
#define USB_HOST0_WRAP_ADDR 0x98013200
#define USB_HOST0_ADDR 0x98020000

#define USB_HOST1_ENABLE 1 // xhci_u2host
#define USB_HOST1_CTRL_ID 1
#define USB_HOST1_TYPE DWC3_XHCI
#define USB_HOST1_WRAP_ADDR 0x98013C00
#define USB_HOST1_ADDR 0x98029000

#define DEFINE_HOST_PROP(str) \
static inline u32 GET_HOST_##str(int index) \
{ \
	switch (index) { \
	case 0: return USB_HOST0_##str; \
	case 1: return USB_HOST1_##str; \
	default: printf("%s ERROR host index %d\n", __func__, index); \
	} \
	return -1; \
}

#define GET_HOST_PROP(str, index) GET_HOST_##str(index)

DEFINE_HOST_PROP(ENABLE)
DEFINE_HOST_PROP(CTRL_ID)
DEFINE_HOST_PROP(TYPE)
DEFINE_HOST_PROP(WRAP_ADDR)
DEFINE_HOST_PROP(ADDR)

/* Device Setting */
#define USB_DEVICE_NUM 1

#define USB_DEVICE0_ENABLE 1
#define USB_DEVICE0_CTRL_ID 0
#define USB_DEVICE0_TYPE DWC3_XHCI
#define USB_DEVICE0_WRAP_ADDR 0x98013200
#define USB_DEVICE0_ADDR 0x98020000

#define DEFINE_DEVICE_PROP(str) \
static inline u32 GET_DEVICE_##str(int index) \
{ \
	switch (index) { \
	case 0: return USB_DEVICE0_##str; \
	default: printf("ERROR device index %d\n", index); \
	} \
	return -1; \
}

#define GET_DEVICE_PROP(str, index) GET_DEVICE_##str(index)

DEFINE_DEVICE_PROP(ENABLE)
DEFINE_DEVICE_PROP(CTRL_ID)
DEFINE_DEVICE_PROP(TYPE)
DEFINE_DEVICE_PROP(WRAP_ADDR)
DEFINE_DEVICE_PROP(ADDR)

#define USB_TYPEC_CTRL_CC1_0 	0x98007220
#define USB_TYPEC_CTRL_CC1_1 	0x98007224
#define USB_TYPEC_CTRL_CC2_0 	0x98007228
#define USB_TYPEC_CTRL_CC2_1 	0x9800722C
#define USB_TYPEC_STS 			0x98007230
#define USB_TYPEC_CTR 			0x98007234

struct rtk_usb {
	int controller_id;
	enum controller_type controller_type;
	enum class_type class_type;
	u32 reg_base;
	u32 wrap_base;

	size_t port_count;
	struct usb2_phy *usb2phy;
	struct usb3_phy *usb3phy;

	int ctrl_count;
};

void rtk_usb_clock_init(void);
void rtk_usb_clock_stop(void);

void rtk_usb_power_on(void);
void rtk_usb_power_off(void);

int rtk_usb_device_init(struct rtk_usb **rtk_usb);
int rtk_usb_device_stop(struct rtk_usb **rtk_usb);

int rtk_usb_host_init(struct rtk_usb **rtk_usb);
int rtk_usb_host_stop(struct rtk_usb **rtk_usb);

