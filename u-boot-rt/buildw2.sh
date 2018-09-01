#source a.env

show_usage()
{
        echo "!!!!!!!!!!!!! wrong argument !!!!!!!!!!!!!"
        echo "usage: shell_cmd argu1"
        echo "argu1: emmc  | sd"
        echo "example:"
        echo "       (1) ./buildw2.sh sd"
        echo "       (2) ./buildw2.sh emmc"
        exit 1
}

if [ "$1" = "sd" ]; then
	make clean;make rtd1296_sd_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002 BUILD_BOOTCODE_ONLY=true
	exit 1
else
	make clean;make rtd1296_emmc_bananapi_defconfig;make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866 CONFIG_CHIP_TYPE=0002

	mv examples/flash_writer/image/hw_setting/RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866*.bin image/
	mv examples/flash_writer/dvrboot.exe.bin image/
	exit 1
fi

show_usage
