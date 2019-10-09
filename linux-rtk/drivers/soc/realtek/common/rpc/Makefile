ccflags-y	+= -Idrivers/video/fbdev/rtk
ccflags-y += -I$(srctree)/drivers/staging/android
ccflags-$(CONFIG_RTK_RPC)	+= -Idrivers/soc/realtek/common
ccflags-$(CONFIG_RTK_RPC)	+= -Idrivers/soc/realtek/common/include
obj-$(CONFIG_RTK_RPC)	+= rtk_rpc.o
obj-$(CONFIG_RTK_RPC)	+= rtk_rpc_intr.o
obj-$(CONFIG_RTK_RPC)	+= rtk_rpc_poll.o
obj-$(CONFIG_RTK_RPC)	+= rtk_rpc_kern.o
