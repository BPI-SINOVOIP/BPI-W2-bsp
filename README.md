# BPI-W2-bsp

Overview
------------
This project is for banana-pi W2 board, including U-boot and Linux Kernel 4.9.x.

How to build both U-boot and Linux kernel
------------------------------------------
1. Clone this code to a host PC on which the Ubuntu 16.04 is installed
2. Run script build.sh
```
	./build.sh
```
3. Select 1 to build both uboot and kernel
4. Both new uboot and kernel will be generated in folder SD when it completes

How to update both u-boot and Linux kernel
--------------------------------------------
If you don't have tools for banana-pi products, please run below commands to install them:
```
	apt-get install pv
	curl -sL https://github.com/BPI-SINOVOIP/bpi-tools/raw/master/bpi-tools | sudo -E bash
```
1. Install SD card to this host PC, please ensure image(Ubuntu, Debian, ...) is installed on this SD card
2. Enter folder SD which is generated after building
3. Run below command to update u-boot and Linux kernel
```
	bpi-update -c bpi-w2.conf -d /dev/sdX
	or
	bpi-update -d /dev/sdX

	and update u-boot (if changed or first time)

	bpi-bootsel 100MB/BPI-W2-720P-2k.img.gz /dev/sdX
```
4. After it completes, move SD to W2 board
5. Press power button to activate this board

How to install images on SD card
------------------------------------------
1. Downloading image for W2 board from http://forum.banana-pi.org/c/Banana-pi-BPI-W2/BPI-W2-image
2. Running below command to burn this image to SD card which must be larger than 8GB
```
		bpi-copy <image file> /dev/sd<drive letter>

		Example: bpi-copy ubuntu.img /dev/sdf
```
3. Install this SD to W2 board
4. Press power button a few seconds to activate this board. The default baud rate of serial port is 115200, the default username/password are root/bananapi

