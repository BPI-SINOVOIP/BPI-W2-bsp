#$Header: $
#$Change: $
#$DateTime: $
#
# Copyright (C) 2014, GreenPeak Technologies
#
# support@greenpeak.com
# www.greenpeak.com
#
# This file is part of the GP kernel module.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
# Alternatively, see http://www.gnu.org/licenses/gpl-2.0.txt
#

#ifneq ($(KERNELRELEASE),)
# called from kernel build system

#include Kbuild

#else
#
PWD := $(shell pwd)
ifndef TOP
        TOP = ../..
endif
include $(TOP)/make.include
KERNELDIR := $(LINUX_KERNEL_PATH)
EXTRA_CFLAGS="-DGP712"

GP_CHIP=GP712
ARCH="aarch64"
CC="${CROSS_COMPILE}gcc"
AR="${CROSS_COMPILE}ar"
LINK="${CROSS_COMPILE}ld"
OBJCOPY="${CROSS_COMPILE}objcopy"
OBJDUMP="${CROSS_COMPILE}objdump"
SIZE="${CROSS_COMPILE}size -A"
NM="${CROSS_COMPILE}nm"

all: modules

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) EXTRA_CFLAGS="-DGP712" GP_CHIP=GP712 modules

install:
	install -p -m 644 *.ko ../../bin/

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

help:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) help

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

.PHONY: modules modules_install help clean

#endif
