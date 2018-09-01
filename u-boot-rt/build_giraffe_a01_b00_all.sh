mkdir -p DVRBOOT_OUT/hw_setting

########### Build 2G DDR4 2133 #############
make mrproper; make rtd1295_qa_defconfig; make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_2133_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_2133_DDR4_2X8Gb-drm.bin

########### Build 1G DDR4 2133 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_4Gb_s2133
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR4_4Gb_s2133.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR4_4Gb_s2133.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_2133_DDR4_2X4Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_4Gb_s2133 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_2133_DDR4_2X4Gb-drm.bin

########### Build 1G DDR3 1600 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1600
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1600.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1600.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_2X4Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1600 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_2X4Gb-drm.bin

########### Build 1G DDR3 1866 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1866
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1866.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1866.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1866_DDR3_2X4Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_4Gb_s1866 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1866_DDR3_2X4Gb-drm.bin

########### Build 2G DDR3 1600 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1600
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1600.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1600.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_2X8Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1600 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_2X8Gb-drm.bin

########### Build 2G DDR3 1866 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1866
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1866.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1866.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1866_DDR3_2X8Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8Gb_s1866 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1866_DDR3_2X8Gb-drm.bin

########### Build 1.5G DDR3 1600 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8+4Gb_s1600
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8+4Gb_s1600.bin ./DVRBOOT_OUT/hw_setting/RTD1295_hwsetting_BOOT_2DDR3_8+4Gb_s1600.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_1X8Gb+1X4Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR3_8+4Gb_s1600 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_A01_emmc_1600_DDR3_1X8Gb+1X4Gb-drm.bin

########### Build B00 2G DDR4 2133 #############
make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133 CONFIG_CHIP_TYPE=0002
cp ./examples/flash_writer/image/hw_setting/RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133.bin ./DVRBOOT_OUT/hw_setting/RTD1295_B00_hwsetting_BOOT_2DDR4_8Gb_s2133.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_B00_emmc_2133_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133 CONFIG_CHIP_TYPE=0002 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1295_B00_emmc_2133_DDR4_2X8Gb-drm.bin

########### Build A01 1296 2G DDR4 1600 #############
make mrproper; make rtd1296_qa_defconfig; make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600
cp ./examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600.bin ./DVRBOOT_OUT/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_A01_emmc_1600_DDR4_4X4Gb.bin

make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_A01_emmc_1600_DDR4_4X4Gb-drm.bin

########### Build A01 1296 3G DDR4 1600 #############
make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1600
cp ./examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1600.bin ./DVRBOOT_OUT/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1600.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_A01_emmc_1600_DDR4_2X8+2X4Gb.bin

make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1600 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_A01_emmc_1600_DDR4_2X8+2X4Gb-drm.bin

########### Build B00 1296 2G DDR4 1866 #############
make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866 CONFIG_CHIP_TYPE=0002
cp ./examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866.bin ./DVRBOOT_OUT/hw_setting/RTD1296_B00_hwsetting_BOOT_4DDR4_4Gb_s1866.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_4X4Gb.bin

make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866 CONFIG_CHIP_TYPE=0002 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_4X4Gb-drm.bin

########### Build B00 1296 3G DDR4 1866 #############
make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1866 CONFIG_CHIP_TYPE=0002
cp ./examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1866.bin ./DVRBOOT_OUT/hw_setting/RTD1296_B00_hwsetting_BOOT_4DDR4_8+4Gb_s1866.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_2X8+2X4Gb.bin

make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8+4Gb_s1866 CONFIG_CHIP_TYPE=0002 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_2X8+2X4Gb-drm.bin

########### Build B00 1296 4G DDR4 1866 #############
make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8Gb_s1866 CONFIG_CHIP_TYPE=0002
cp ./examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_8Gb_s1866.bin ./DVRBOOT_OUT/hw_setting/RTD1296_B00_hwsetting_BOOT_4DDR4_8Gb_s1866.bin
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_4X8Gb.bin

make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_8Gb_s1866 CONFIG_CHIP_TYPE=0002 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer/dvrboot.exe.bin ./DVRBOOT_OUT/1296_B00_emmc_1866_DDR4_4X8Gb-drm.bin

