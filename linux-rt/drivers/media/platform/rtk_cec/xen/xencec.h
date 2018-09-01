
#ifndef __XEN_PUBLIC_CEC_H__
#define __XEN_PUBLIC_CEC_H__

#include <xen/interface/io/ring.h>
#include "../cec.h"
#include "../cec_dev.h"

#define CEC_OP_OPEN		0
#define CEC_OP_ENABLE		1
#define CEC_OP_SET_RXMASK	2
#define CEC_OP_SET_LOGICAL	3
#define CEC_OP_SET_PHYSICAL	4
#define CEC_OP_SEND_MSG		5
#define CEC_OP_RCV_MSG		6
#define CEC_OP_STANDBY		7
#define CEC_OP_CEC_VER		8
#define CEC_OP_VENDER_ID	9
#define CEC_OP_RETRY_NUM	10
#define CEC_NAME_LENGTH		20
#define CEC_CMB_LENGTH		128

struct cec_request {
	int req_id;

	int op;
	int rdev_id;
	void *dev;
	union {
		char cec_name[CEC_NAME_LENGTH];
		char data[CEC_CMB_LENGTH];
		unsigned long arg;
	};
	int len;
};

struct cec_response {
	int rsp_id;
	int req_id;
    
	int op;
	int rdev_id;
	int retval;
	int errval;
	void *ptr;
	char data[CEC_CMB_LENGTH];
};

DEFINE_RING_TYPES(cec, struct cec_request, struct cec_response);

struct cec_front_info {
	struct xenbus_device *dev;
	struct cec_front_ring ring;
	struct mutex lock;

	int ring_ref;
	unsigned int evtchn;
	unsigned int irq;

	int connected;
	volatile int wait_done;
	int req_id;
};

extern void *cec_front_open(struct cec_front_info *info, char *path);
extern int cec_front_set_param(struct cec_front_info *info, void *dev, unsigned int cmd, unsigned long arg);
extern int cec_front_send_message(struct cec_front_info *info, void *dev, char *data, int len);
extern int cec_front_rcv_message(struct cec_front_info *info, void *dev, char *data, int len);
extern int xen_cec_register(struct cec_front_info *info);
#endif
