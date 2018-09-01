#
# Makefile for CEC linux kernel module.
#

ccflags-y += -I$(srctree)/drivers/video/fbdev/rtk
ccflags-y += -I$(srctree)/drivers/media/platform/rtk_mhltx
ccflags-y += -I$(srctree)/drivers/staging/android

EXTRA_CFLAGS += -I ../

ifndef CONFIG_XEN
ccflags-y += -D USE_ION_AUDIO_HEAP
endif

obj-$(CONFIG_RTK_CEC) += rtk_cec.o
