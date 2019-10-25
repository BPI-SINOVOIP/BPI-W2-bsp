ifeq ($(CONFIG_FB_RTK_FPGA),y)
obj-$(CONFIG_FB_RTK) += dc2fpga/
else
obj-$(CONFIG_FB_RTK) += dc2vo/
endif

obj-$(CONFIG_FB_RTK) += rtk_fb.o
obj-$(CONFIG_VFB_RTK) += rtk_vfb.o
obj-$(CONFIG_FB_RTK) += rtk_fb_RPC.o
obj-$(CONFIG_FB_RTK) += rtk_fb_freelogo.o

