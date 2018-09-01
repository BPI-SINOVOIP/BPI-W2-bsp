#
# Makefile for CEC linux kernel module.
#

ccflags-y += -I$(srctree)/drivers/video/fbdev/rtk
ccflags-y += -I$(srctree)/drivers/media/platform/rtk_mhltx
ccflags-y += -I$(srctree)/drivers/staging/android

obj-$(CONFIG_RTK_DPTX)  += dptx_core.o dptx_switch.o dptx_hwapi.o dptx_rpc.o dptx_edid.o
