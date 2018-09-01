mkdir -p DVRBOOT_OUT/hw_setting

########### Build 2G DDR4 2133 #############
make mrproper; make rtd1395_qa_defconfig; make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0000-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2133_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2133_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2133_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2133_DDR4_2X8Gb-drm.bin

########### Build 2G DDR4 2133 no power saving #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133_no_power_saving
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0000-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133_no_power_saving.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2133_no_power_saving_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2133_no_power_saving_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133_no_power_saving CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2133_no_power_saving_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2133_no_power_saving_DDR4_2X8Gb-drm.bin

########### Build 2G DDR4 2400 #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0000-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2400_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2400_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A00_emmc_2400_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A00_emmc_2400_DDR4_2X8Gb-drm.bin

########### Build a01 2G DDR4 1600 #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1600 CHIP_TYPE=0001
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0001-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1600.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_1600_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_1600_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1600 CHIP_TYPE=0001 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_1600_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_1600_DDR4_2X8Gb-drm.bin

########### Build a01 2G DDR4 1866 #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1866 CHIP_TYPE=0001
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0001-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1866.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_1866_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_1866_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s1866 CHIP_TYPE=0001 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_1866_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_1866_DDR4_2X8Gb-drm.bin

########### Build a01 2G DDR4 2133 #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133 CHIP_TYPE=0001
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0001-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_2133_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_2133_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2133 CHIP_TYPE=0001 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_2133_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_2133_DDR4_2X8Gb-drm.bin

########### Build a01 2G DDR4 2400 #############
make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400 CHIP_TYPE=0001
cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/0001-RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400.bin
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_2400_DDR4_2X8Gb.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_2400_DDR4_2X8Gb.bin

make Board_HWSETTING=RTD1395_hwsetting_BOOT_2DDR4_8Gb_s2400 CHIP_TYPE=0001 CONFIG_TEE_OS_DRM=TRUE
cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-1395_A01_emmc_2400_DDR4_2X8Gb-drm.bin
cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/1395_A01_emmc_2400_DDR4_2X8Gb-drm.bin