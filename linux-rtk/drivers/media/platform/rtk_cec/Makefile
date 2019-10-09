#
# Makefile for CEC linux kernel module.
#

obj-$(CONFIG_CEC)  += cec_core.o cm_buff.o cec_dev.o

obj-$(CONFIG_CEC) += adapter/
obj-$(CONFIG_XEN_CECDEV_BACKEND) += xen/cecback.o
obj-$(CONFIG_XEN_CECDEV_FRONTEND) += xen/cecfront.o xen/cecdev.o
