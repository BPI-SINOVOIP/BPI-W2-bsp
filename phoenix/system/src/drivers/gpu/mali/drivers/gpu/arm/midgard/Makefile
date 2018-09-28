#
# (C) COPYRIGHT 2010-2016, 2017 ARM Limited. All rights reserved.
#
# This program is free software and is provided to you under the terms of the
# GNU General Public License version 2 as published by the Free Software
# Foundation, and any use by you of this program is subject to the terms
# of such GNU licence.
#
# A copy of the licence is included with the program, and can also be obtained
# from Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA  02110-1301, USA.
#
#

export CONFIG_MALI_MIDGARD=m
# export # CONFIG_MALI_MIPE_ENABLED is not set
# export CONFIG_MALI_MIDGARD_DVFS=y
export CONFIG_MALI_MIDGARD_RT_PM=y
export CONFIG_MALI_PLATFORM_THIRDPARTY=y
export CONFIG_MALI_PLATFORM_THIRDPARTY_NAME="kylin"

# export CONFIG_MALI_GATOR_SUPPORT=y
# export CONFIG_MALI_MIDGARD_ENABLE_TRACE=y
# export CONFIG_MALI_DEBUG_SHADER_SPLIT_FS=y
# export CONFIG_MALI_DEBUG=y
# export CONFIG_MALI_TRACE_TIMELINE=y

# export CONFIG_MALI_SYSTEM_TRACE=y
# export CONFIG_UMP=y
# export CONFIG_KDS=y
# export CONFIG_MALI_NO_MALI=y
# export CONFIG_DMA_SHARED_BUFFER=y
# export CONFIG_DMA_SHARED_BUFFER_USES_KDS=y

KDIR ?= /lib/modules/$(shell uname -r)/build

BUSLOG_PATH_RELATIVE = $(CURDIR)/../../../..
UMP_PATH_RELATIVE = $(CURDIR)/../../../base/ump
KBASE_PATH_RELATIVE = $(CURDIR)
KDS_PATH_RELATIVE = $(CURDIR)/../../../..
ifeq ($(CONFIG_UMP), y)
EXTRA_SYMBOLS = $(UMP_PATH_RELATIVE)/src/Module.symvers
endif

ifeq ($(MALI_UNIT_TEST), 1)
	EXTRA_SYMBOLS += $(KBASE_PATH_RELATIVE)/tests/internal/src/kernel_assert_module/linux/Module.symvers
endif

ifeq ($(CONFIG_MALI_FPGA_BUS_LOGGER),y)
#Add bus logger symbols
EXTRA_SYMBOLS += $(BUSLOG_PATH_RELATIVE)/drivers/base/bus_logger/Module.symvers
endif

# GPL driver supports KDS
ifeq ($(CONFIG_KDS), y)
EXTRA_SYMBOLS += $(KDS_PATH_RELATIVE)/drivers/base/kds/Module.symvers
endif

# we get the symbols from modules using KBUILD_EXTRA_SYMBOLS to prevent warnings about unknown functions
all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) EXTRA_CFLAGS="-I$(CURDIR)/../../../../include -I$(CURDIR)/../../../../tests/include $(SCONS_CFLAGS)" $(SCONS_CONFIGS) KBUILD_EXTRA_SYMBOLS="$(EXTRA_SYMBOLS)" modules

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean
