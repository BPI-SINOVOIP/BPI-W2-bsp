#include "ir_input.h"
#include "rtk_ir.h"
#include <linux/pinctrl/consumer.h>
//#include <linux/input.h>

static int _rtk_ir_setkeycode(struct input_dev *dev, const struct input_keymap_entry *ke, unsigned int *old_keycode);
static int _rtk_ir_getkeycode(struct input_dev *dev, struct input_keymap_entry *ke);

extern int rtk_ir_setkeycode(unsigned int scancode, unsigned int new_keycode, unsigned int *p_old_keycode, unsigned long *keybit_addr);
extern int rtk_ir_getkeycode(unsigned int scancode, unsigned int *p_keycode);

extern void rtk_ir_set_keybit(unsigned long *addr);
extern void rtk_ir_set_relbit(unsigned long *addr);


struct rtk_ir_data {
	unsigned int irq;
	struct input_dev *input_dev;
	u8 keypressed;
	u32 keycode;
	atomic_t reportCount;
};

static struct rtk_ir_data *data = NULL;

long int Input_Keybit_Length = sizeof(data->input_dev->keybit); 

int rtk_ir_input_init(void)
{
	struct input_dev *input_dev;

	int result;
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		result = -ENOMEM;
		goto exit;
	}
	input_dev = input_allocate_device();
	if (!input_dev) {
		result = -ENOMEM;
		printk(KERN_ERR "rtk IR: can't allocate input device.\n");
		goto fail_alloc_input_dev;
	}

	atomic_set(&data->reportCount, 0);

	data->input_dev = input_dev;

//	data->input_dev->evbit[0] = BIT_MASK(EV_KEY) |BIT(EV_REL) |BIT(EV_REP);
	data->input_dev->evbit[0] = BIT_MASK(EV_KEY) |BIT(EV_REL);
	data->input_dev->name = "venus_IR_input";
	data->input_dev->phys = "rtk/input0";
	
	data->input_dev->setkeycode = _rtk_ir_setkeycode;
	data->input_dev->getkeycode = _rtk_ir_getkeycode;

	rtk_ir_set_keybit(data->input_dev->keybit);
	rtk_ir_set_relbit(data->input_dev->relbit);

	result = input_register_device(data->input_dev);
	if (result) {
		printk(KERN_ERR "rtk IR: cannot register input device.\n");
		goto fail_register_input_dev;
	}
/*
	pinctrl = devm_pinctrl_get_select_default(&(data->input_dev->dev));
	if (IS_ERR(pinctrl)) {
		printk(KERN_ERR "rtk IR: pinctrl cannot select default state.\n");
		goto fail_pinctrl_select_default;
	}
*/
	return 0;
/*
fail_pinctrl_select_default:
	input_unregister_device(data->input_dev);
*/
fail_register_input_dev:
	input_free_device(data->input_dev);
fail_alloc_input_dev:
	kfree(data);
exit:
	return -1;
}

void rtk_ir_input_report_key(uint32_t keycode)
{
	atomic_inc(&data->reportCount);
	data->keycode = keycode;
	input_report_key(data->input_dev, data->keycode, 1);
	input_sync(data->input_dev);	
}

void rtk_ir_input_report_end(void)
{
	if (atomic_read(&data->reportCount) != 1)//Should not happen
		pr_err("[IR input] report key not in pairs, reportCount(%d)\n",atomic_read(&data->reportCount));

	atomic_set(&data->reportCount, 0);
	input_report_key(data->input_dev, data->keycode, 0);
	input_sync(data->input_dev);
}

static int _rtk_ir_setkeycode(struct input_dev *dev, const struct input_keymap_entry *ke, unsigned int *old_keycode)
{
	unsigned int scancode;
	unsigned int new_keycode;

	if (input_scancode_to_scalar(ke, &scancode))
		return -EINVAL;
	new_keycode = ke->keycode;

	rtk_ir_setkeycode(scancode, new_keycode, old_keycode, data->input_dev->keybit);
	return 0;
}

static int _rtk_ir_getkeycode(struct input_dev *dev, struct input_keymap_entry *ke)
{
	unsigned int scancode;
	unsigned int keycode;

	if (input_scancode_to_scalar(ke, &scancode))
		return -EINVAL;

	if (-1 != rtk_ir_getkeycode(scancode, &keycode))
	{
		ke->keycode = keycode;
		ke->len = sizeof(scancode);
		memcpy(&ke->scancode, &scancode, sizeof(scancode));
		return 0;
	}

	keycode = KEY_RESERVED; //not found, set to KEY_RESERVED
	ke->keycode = keycode;
	ke->len = sizeof(scancode);
	memcpy(&ke->scancode, &scancode, sizeof(scancode));

	return 0;
}
