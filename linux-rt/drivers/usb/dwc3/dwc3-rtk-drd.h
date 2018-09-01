/**
 * dwc3-rtk-drd.h - Realtek DWC3 Specific Glue layer
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DRIVERS_USB_DWC3_RTK_DRD_H
#define __DRIVERS_USB_DWC3_RTK_DRD_H

#include "core.h"
#include "gadget.h"
#include "io.h"

extern int dwc3_drd_to_host(struct dwc3 *dwc);
extern int dwc3_drd_to_device(struct dwc3 *dwc);
extern int dwc3_drd_to_stop_all(struct dwc3 *dwc);

#endif /* __DRIVERS_USB_DWC3_RTK_CORE_H */

