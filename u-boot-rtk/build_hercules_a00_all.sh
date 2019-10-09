mkdir -p DVRBOOT_OUT/hw_setting

make mrproper; make rtd1395_qa_defconfig;

########### Build Hercules A00 #############
CHIP_TYPE=0000
HWSETTING_DIR=examples/flash_writer_vm/image/hw_setting/rtd1395/demo/$CHIP_TYPE
BUILD_HWSETTING_LIST=`ls $HWSETTING_DIR`

for hwsetting in $BUILD_HWSETTING_LIST
do
	hwsetting=`echo $hwsetting | cut -d '.' -f 1`
	echo %%%%%%%% RTD1395 -- $CHIP_TYPE -- $hwsetting %%%%%%
	if [[ $hwsetting == *"NAND"* ]]; then
		echo "NAND hwsetting skip"
		continue
	fi
	
	#Build the normal version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.bypass.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting
	cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/$CHIP_TYPE-$hwsetting.bin
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A00-$hwsetting.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A00-$hwsetting.bin
	
	#Build the drm version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.drm.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A00-$hwsetting-drm.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A00-$hwsetting-drm.bin
	
	#Build the atv version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.atv.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A00-$hwsetting-atv.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A00-$hwsetting-atv.bin
	
	#Build the vmx version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.vmx.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A00-$hwsetting-vmx.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A00-$hwsetting-vmx.bin
	
	#Reset to normal version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.bypass.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
done



########### Build Hercules A01 #############
CHIP_TYPE=0001
HWSETTING_DIR=examples/flash_writer_vm/image/hw_setting/rtd1395/demo/$CHIP_TYPE
BUILD_HWSETTING_LIST=`ls $HWSETTING_DIR`

for hwsetting in $BUILD_HWSETTING_LIST
do
	hwsetting=`echo $hwsetting | cut -d '.' -f 1`
	echo %%%%%%%% RTD1395 -- $CHIP_TYPE -- $hwsetting %%%%%%
	if [[ $hwsetting == *"NAND"* ]]; then
		echo "NAND hwsetting skip"
		continue
	fi
	
	#Build the normal version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.bypass.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting CHIP_TYPE=$CHIP_TYPE
	cp ./examples/flash_writer_vm/install_a/hw_setting.bin ./DVRBOOT_OUT/hw_setting/$CHIP_TYPE-$hwsetting.bin
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A01-$hwsetting.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A01-$hwsetting.bin
	
	#Build the drm version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.drm.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting CHIP_TYPE=$CHIP_TYPE
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A01-$hwsetting-drm.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A01-$hwsetting-drm.bin
	
	#Build the atv version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.atv.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting CHIP_TYPE=$CHIP_TYPE
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A01-$hwsetting-atv.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A01-$hwsetting-atv.bin
	
	#Build the vmx version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.vmx.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
	make Board_HWSETTING=$hwsetting CHIP_TYPE=$CHIP_TYPE
	cp ./examples/flash_writer_vm/Bind/emmc.bind.bin ./DVRBOOT_OUT/hw_setting/Recovery-A01-$hwsetting-vmx.bin
	cp ./examples/flash_writer_vm/dvrboot.exe.bin ./DVRBOOT_OUT/A01-$hwsetting-vmx.bin
	
	#Reset to normal version
	cp ./examples/flash_writer_vm/image/tee_os/$CHIP_TYPE/fsbl-os-00.00.bin.bypass.enc ./examples/flash_writer_vm/bootimage/rtd1395/$CHIP_TYPE/fsbl-os-00.00.bin.enc
done
