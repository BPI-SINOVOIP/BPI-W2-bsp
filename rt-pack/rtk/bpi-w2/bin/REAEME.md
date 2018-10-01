# update spi romcode (BPI-W2)

----------------------------------------------
(uboot) boot from sd (Press ESC key)
----------------------------------------------
0. pc: copy spirom-bpi-w2.bin to (SDCARD FAT32) BPI-BOOT
1. bpi-w2: run cmd
```
	fatload sd 0:1 0x01500000 spirom-bpi-w2.bin
	go 0x01500000
```

----------------------------------------------
(android lk) boot from emmc (Press ESC key)
----------------------------------------------
0. pc: copy spirom-bpi-w2.bin to (USB DISK FAT32) BPI-BOOT
1. bpi-w2: run cmd
```
	usb start
	fatload usb 0:1 0x01500000 spirom-bpi-w2.bin
	chain 0x01500000
```

