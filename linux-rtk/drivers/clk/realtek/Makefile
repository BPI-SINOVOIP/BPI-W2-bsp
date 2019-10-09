obj-$(CONFIG_COMMON_CLK_REALTEK) += clk-rtk.o
obj-$(CONFIG_COMMON_CLK_DUMMY) += clk-dummy.o

clk-rtk-y += common.o
clk-rtk-y += clk-mmio-mux.o
clk-rtk-y += clk-mmio-gate.o
clk-rtk-y += cgc.o
clk-rtk-y += reset.o
clk-rtk-y += clk-pll.o
clk-rtk-y += cc-platform.o

clk-rtk-$(CONFIG_COMMON_CLK_RTD119X) += cc-rtd119x.o
clk-rtk-$(CONFIG_COMMON_CLK_RTD129X) += cc-rtd129x.o
clk-rtk-$(CONFIG_COMMON_CLK_RTD139X) += cc-rtd139x.o
clk-rtk-$(CONFIG_COMMON_CLK_RTD16XX) += cc-rtd16xx.o


