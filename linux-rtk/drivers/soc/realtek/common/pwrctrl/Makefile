obj-$(CONFIG_POWER_CONTROL)         += pwrctrl_core.o
obj-$(CONFIG_POWER_CONTROL_REALTEK) += pwrctrl-rtk.o

pwrctrl-rtk-y += pwrctrl-pd.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_PD_SRAM) += pwrctrl-pd-sram.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_PD_SRAM_CH) += pwrctrl-pd-sram_ch.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_PD_SIMPLE) += pwrctrl-pd-simple.o

pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD129X) += pwrctrl-rtd129x.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD139X) += pwrctrl-rtd139x.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD16XX) += pwrctrl-rtd16xx.o
pwrctrl-rtk-$(CONFIG_POWER_CONTROL_RTD13XX) += pwrctrl-rtd13xx.o
