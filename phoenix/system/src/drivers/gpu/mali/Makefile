PWD=$(shell pwd)

MALI_ARCH?=arm64
MALI_CROSS_COMPILE?=asdk64-linux-

#MALI_KDS_ROOT=drivers/base/kds
#MALI_UMP_ROOT=drivers/base/ump/src
MALI_KBASE_ROOT=drivers/gpu/arm/midgard

install: build
#	@echo $(PWD)/$(MALI_KDS_ROOT)/kds.ko
#	@echo $(PWD)/$(MALI_UMP_ROOT)/ump.ko
	@echo $(PWD)/$(MALI_KBASE_ROOT)/mali_kbase.ko

build:
	@echo $(TARGET_KDIR)
#	$(MAKE) -C $(MALI_KDS_ROOT) 	KDIR=${TARGET_KDIR}
#	$(MAKE) -C $(MALI_UMP_ROOT) 	KDIR=${TARGET_KDIR}
	$(MAKE) -C $(MALI_KBASE_ROOT) 	KDIR=${TARGET_KDIR}

clean:
#	$(MAKE) -C $(MALI_KDS_ROOT) 	KDIR=${TARGET_KDIR} clean
#	$(MAKE) -C $(MALI_UMP_ROOT) 	KDIR=${TARGET_KDIR} clean
	$(MAKE) -C $(MALI_KBASE_ROOT) 	KDIR=${TARGET_KDIR} clean
