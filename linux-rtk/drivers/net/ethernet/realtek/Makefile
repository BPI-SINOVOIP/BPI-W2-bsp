#
# Makefile for the Realtek network device drivers.
#

obj-$(CONFIG_8139CP) += 8139cp.o
obj-$(CONFIG_8139TOO) += 8139too.o
obj-$(CONFIG_ATP) += atp.o
obj-$(CONFIG_R8169) += r8169.o
obj-$(CONFIG_R8168) += r8168/
obj-$(CONFIG_R8125) += r8125/
ifeq ($(CONFIG_ARCH_RTD119X),y)
obj-$(CONFIG_R8169SOC) += r8169soc_rtd119x.o
else
obj-$(CONFIG_R8169SOC) += r8169soc.o
endif
