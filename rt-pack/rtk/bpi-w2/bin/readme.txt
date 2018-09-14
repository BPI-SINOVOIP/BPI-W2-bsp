#
## update spi romcode (BPI-W2)
#
###############################################################
## (uboot) boot from sd
## copy spirom-bpi-w2.bin to SDCARD FAT32 BPI-BOOT
#
###############################################################
fatload sd 0:1 spirom-bpi-w2.bin
go 0x01500000

###############################################################
#
## (android lk) boot from emmc
## copy spirom-bpi-w2.bin to USB DISK FAT32 BPI-BOOT
## Press ESC key
#
###############################################################
usb start
fatload usb 0:1 0x01500000 spirom-bpi-w2.bin
chain 0x01500000
