MODULE_NAME := buflock

ccflags-y := -I$(obj)/inc
ccflags-y += -I$(obj)/uapi
ccflags-y += -DMODULE_NAME='"$(MODULE_NAME)"'

obj-y   := $(MODULE_NAME).o
$(MODULE_NAME)-objs := src/buflock.o
