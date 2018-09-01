/*
 * regif - xen regulator device interface
 *
 * Copyright (C) 2016 Realtek Semiconductor Corporation
 * Copyright (C) 2016 Cheng-Yu Lee <cylee12@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __XEN_PUBLIC_IO_REGIF_H__
#define __XEN_PUBLIC_IO_REGIF_H__

#include <xen/interface/io/ring.h>

#define REGIF_OP_BIND_NAME         0
#define REGIF_OP_GET_N_VOLTAGES    1
#define REGIF_OP_GET_VOLT_TABLE_N  2
#define REGIF_OP_GET_CONSTRAINTS   3
#define REGIF_OP_SET_VOLT          4
#define REGIF_OP_GET_VOLT          5

static const char *regif_op_strings [] = {
	[REGIF_OP_BIND_NAME] = "bind_name",
	[REGIF_OP_GET_N_VOLTAGES] = "get_n_voltages",
	[REGIF_OP_GET_VOLT_TABLE_N] = "get_volt_table_n",
	[REGIF_OP_GET_CONSTRAINTS] = "get_constraints",
	[REGIF_OP_SET_VOLT] = "set_volt",
	[REGIF_OP_GET_VOLT] = "get_volt",
};

static inline const char *regif_op_string(int op)
{
	return regif_op_strings[op];
}


#define VREG_CONSTRAINTS_MAX_VOLT   0
#define VREG_CONSTRAINTS_MIN_VOLT   1
#define VREG_CONSTRAINTS_ALWAYS_ON  2
#define VREG_CONSTRAINTS_BOOT_ON    3
#define VREG_CONSTRAINTS_VALID_OPS  4

#define REGIF_OK       0
#define REGIF_ERROR    1

#define REGIF_NAME_LENGTH        20

struct regif_request {
	int req_id;

	int op;
	int rdev_id;
	union {
		/* dummy */
		int dummy;
		/* regulator name */
		char regulator_name[REGIF_NAME_LENGTH];
		/* voltage selector */
		int vsel;
		/* constraint selector */
		int csel;
	};

};

struct regif_response {
	int rsp_id;
	int req_id;

	int op;
	int rdev_id;
	int retval;
	int errval;
};

/*  DEFINE the following structures for ring
 *   struct regif_sring
 *   struct regif_front_ring
 *   struct regif_back_ring
 */
DEFINE_RING_TYPES(regif, struct regif_request, struct regif_response);


#endif /* __XEN_PUBLIC_IO_BLKIF_H__ */
