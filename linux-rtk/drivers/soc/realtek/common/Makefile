obj-y += rtk_memory_remap.o rtk_barrier.o rtk_sb2_dbg.o rtk_dc_sys_dbg.o
obj-y += rtk_chip.o
obj-y += dummy_uctrl.o
obj-$(CONFIG_RTK_DC_SYS_PC) += rtk_dc_sys_pc.o
obj-$(CONFIG_RTK_DC_SYS_PC_DEBUGFS) += rtk_dc_sys_pc-debugfs.o
obj-$(CONFIG_RTK_DC_SYS_PC_EDEV) += rtk_dc_sys_pc-edev.o
obj-$(CONFIG_RTK_DC_SYS_PC_UIODEV) += rtk_dc_sys_pc-uio.o
obj-y += rtk_sb2_sem.o
obj-$(CONFIG_RTK_RPC) += rpc/
obj-${CONFIG_RTK_REGMAP_I2C} += rtk_regmap_i2c.o
obj-$(CONFIG_RTK_MMIO) += rtk_mmio.o
obj-$(CONFIG_ION_RTK) += rtk_ion_of.o
obj-$(CONFIG_RTK_MCP) += rtk_mcp.o rtk_sha1.o
obj-y += pwrctrl/
obj-y += info/
obj-$(CONFIG_RTK_HSE) += hse/

# debug features
obj-$(CONFIG_RTK_REGISTER_TRACKER) += debug/rdbg.o
obj-$(CONFIG_RTK_PM_RUNTIME_DEBUG) += debug/rpm_sysfs.o
