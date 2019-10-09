# Copyright (C) 2007-2014 Realtek Semiconductor Corporation.
# Makefile for HDCP 1.x linux kernel module.
#

ccflags-y += -I$(srctree)/drivers/media/platform/rtk_hdmitx/

obj-$(CONFIG_RTK_HDCP_1x) += hdcp.o
hdcp-$(CONFIG_RTK_HDCP_1x) := hdcp_top.o hdcp_lib.o hdcp_ddc.o

ifndef CONFIG_RTK_HDCP_1x_TEE
hdcp-$(CONFIG_RTK_HDCP_1x) += hdcp_lib_hw.o
endif
