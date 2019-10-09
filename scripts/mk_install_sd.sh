#!/bin/bash

DEVICE=
VARIANT=
BOARD=
TARGET=

echo "--------------------------------------------------------------------------------"
echo "  1. W2"
echo "--------------------------------------------------------------------------------"

read -p "Please choose a target to install(1): " board
echo

if [ -z "${board}" ]; then
	echo -e "\033[31mNo install target choose \033[0m"
	exit 1
fi

case ${board} in
	1) BOARD="W2";;
esac

TARGET=SD/bpi-$(echo ${BOARD} | tr '[A-Z]' '[a-z]')

if [ ! -d ${TARGET} ]; then
	echo -e "\033[31mtarget install files does not exist, please check the build. \033[0m"
	exit 1
fi

echo "--------------------------------------------------------------------------------"
echo "  1. HDMI 720P"
echo "--------------------------------------------------------------------------------"

read -p "Please choose a type to install(1): " type
echo

if [ -z "${type}" ]; then
        echo -e "\033[31mNo install type choose \033[0m"
	exit 1
fi

case ${type} in
        1) VARIANT="720P";;
esac

read -p "Please type the SD device(/dev/sdX): " DEVICE
echo

if [ ! -b ${DEVICE} ]; then
	echo -e "\033[31mNo SD device exists \033[0m"
	exit 1
fi

read -p  "${VARIANT} type will be intalled to ${DEVICE}, [Y/n] " input
echo

case ${input} in
	[yY]) echo "Yes";;
	[nN]) echo "No, stop install";;
	*)
	  echo -e "\033[31mInvalid input \033[0m"
	  exit 1
	  ;;
esac

echo

BOOTLOADER=${TARGET}/100MB/BPI-${BOARD}-${VARIANT}-2k.img.gz

## download bootloader
if [ ! -f ${BOOTLOADER} ]; then
	echo -e "\033[31mbootloader download file not exist, please check you build. \033[0m"
	exit 1
fi

echo "sudo gunzip -c ${BOOTLOADER} | dd of=${DEVICE} bs=1024 seek=2"
sudo gunzip -c ${BOOTLOADER} | sudo dd of=${DEVICE} bs=1024 seek=2
sync
echo
echo "bootloader download finished"
echo

## boot and root
cd ${TARGET}
if command -v bpi-update > /dev/null 2>&1; then
	sudo bpi-update -d ${DEVICE}
else
	cd -
	echo -e "\033[31mbpi-update command not exists, please install it before run this script, more reference to https://github.com/BPI-SINOVOIP/bpi-tools \033[0m"
	exit 1
fi
cd -

## end

