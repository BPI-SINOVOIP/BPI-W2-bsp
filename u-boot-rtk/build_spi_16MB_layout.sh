###########
########### config copy from rtd1296_spi_defconfig
########### it were base on NAS spi projcet
########### basic option:
###########                CONFIG_NAS_ENABLE
###########                CONFIG_BOOT_FROM_SPI
###########                CONFIG_BFS_SUPPORT_KERNEL_ROOTFS  
###########                CONFIG_BFS_SUPPORT_LOGO_IMG  
###########                CONFIG_BSF_SUPPORT_BACKUP_SPI_IMG  
###########                xxxx  
make clean;make rtd1296_spi_16MB_defconfig;make CONFIG_CHIP_TYPE=0002

