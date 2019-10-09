########### create spi bootcode, load 2nd SD bootcode and jumpping
########### mkdir -p DVRBOOT_OUT/hw_setting

show_usage()
{
	echo "!!!!!!!!!!!!! wrong argument !!!!!!!!!!!!!"
	echo "usage: shell_cmd argu1 argu2"
	echo "argu1: 1295 | 1296"
	echo "argu2: a01  | b00"
	echo "argu3: spi  | sd"
	echo "example:"
	echo "       (1) ./build_bananapi.sh 1295 a01 spi"
	echo "       (2) ./build_bananapi.sh 1295 b00 spi"
	echo "       (3) ./build_bananapi.sh 1296 a01 spi"
	echo "       (4) ./build_bananapi.sh 1296 b00 spi"
	echo "       (5) ./build_bananapi.sh 1295 a01 sd"
	echo "       (6) ./build_bananapi.sh 1295 b00 sd"
	echo "       (7) ./build_bananapi.sh 1296 a01 sd"
	echo "       (8) ./build_bananapi.sh 1296 b00 sd"
	echo "       (5) ./build_bananapi.sh 1295 a01 emmc"
	echo "       (6) ./build_bananapi.sh 1295 b00 emmc"
	echo "       (7) ./build_bananapi.sh 1296 a01 emmc"
	echo "       (8) ./build_bananapi.sh 1296 b00 emmc"
	echo "NOTE:  1295 for giraffe board(2xDDR4, total 2GB)"
	echo "       1296 for saola board(4xDDR4, total 2GB)"
	echo "       Please add your code for others"
	exit 1
}

if [ "$1" = "1295" ]; then
	if [ "$2" = "a01" ]; then
		if [ "$3" = "spi" ]; then
			make clean;make rtd1295_spi_bananapi_defconfig;make CONFIG_CHIP_TYPE=0001
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "sd" ]; then
			make clean;make rtd1295_sd_bananapi_defconfig;make CONFIG_CHIP_TYPE=0001 BUILD_BOOTCODE_ONLY=true
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "emmc" ]; then
			make clean;make rtd1295_emmc_bananapi_defconfig;make CONFIG_CHIP_TYPE=0001
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
	fi
	if [ "$2" = "b00" ]; then
		if [ "$3" = "spi" ]; then
			make clean;make rtd1295_spi_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "sd" ]; then
			make clean;make rtd1295_sd_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002 BUILD_BOOTCODE_ONLY=true
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "emmc" ]; then
			make clean;make rtd1295_emmc_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
	fi
fi

if [ "$1" = "1296" ]; then
	if [ "$2" = "a01" ]; then
		if [ "$3" = "spi" ]; then
			make clean;make rtd1296_spi_bananapi_defconfig;make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600 CONFIG_CHIP_TYPE=0001
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "sd" ]; then
			make clean;make rtd1296_sd_bananapi_defconfig;make CONFIG_CHIP_TYPE=0001 BUILD_BOOTCODE_ONLY=true
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "emmc" ]; then
			make clean;make rtd1296_emmc_bananapi_defconfig;make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1600 CONFIG_CHIP_TYPE=0001
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
	fi
	if [ "$2" = "b00" ]; then
		if [ "$3" = "spi" ]; then
			make clean;make rtd1296_spi_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "sd" ]; then
			make clean;make rtd1296_sd_bananapi_defconfig;make CONFIG_CHIP_TYPE=0002 BUILD_BOOTCODE_ONLY=true
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
		if [ "$3" = "emmc" ]; then
			make clean;make rtd1296_emmc_bananapi_defconfig;make Board_HWSETTING=RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866 CONFIG_CHIP_TYPE=0002
			ls -l ~/workingdir/tftp_dir/bootcode
			exit 1
		fi
	fi
fi

show_usage

#make clean;make rtd1295_spi_bananapi_defconfig;make
#make clean;make rtd1296_spi_bananapi_defconfig;make
#ls -l ~/workingdir/tftp_dir/bootcode
