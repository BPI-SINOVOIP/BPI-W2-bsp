SHELL=/bin/bash
TOP = $(PWD)/../../..
include $(TOP)/make.include

KSRC := $(LINUX_KERNEL_PATH)
MODULE_NAME := rtk_btusb

#$(MODULE_NAME)-y += $(bt_core).o

obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-y := rtk_bt.o rtk_coex.o rtk_misc.o

all: modules

modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE="$(CROSS_COMPILE)" -C $(KSRC) M=$(shell pwd)  modules

strip:
	$(CROSS_COMPILE)strip $(MODULE_NAME).ko --strip-unneeded

.PHONY: modules clean

clean:
	rm -fr Module.symvers ; rm -fr Module.markers ; rm -fr modules.order
	rm -fr *.mod.c *.mod *.o .*.cmd *.ko *~
	rm -fr .tmp_versions
