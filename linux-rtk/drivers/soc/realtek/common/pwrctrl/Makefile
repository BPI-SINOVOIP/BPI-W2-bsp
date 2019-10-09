# core
obj-$(CONFIG_POWER_CONTROL)         += pwrctrl_core.o
obj-$(CONFIG_POWER_CONTROL_DEBUGFS) += pwrctrl_debugfs.o

obj-$(CONFIG_POWER_CONTROL_REALTEK) += pwrctrl-rtk.o

pwrctrl-rtk-y += pwrctrl-pd.o
pwrctrl-rtk-y += pwrctrl-pd-sram.o
ifeq (y, $(CONFIG_POWER_CONTROL_RTD129X))
pwrctrl-rtk-y += pwrctrl-pd-sram_ch.o
endif
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD129X) += pwrctrl-rtd129x.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD139X) += pwrctrl-rtd139x.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD16XX) += pwrctrl-rtd16xx.o
