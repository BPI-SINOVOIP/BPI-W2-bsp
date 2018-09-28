make clean
make EXTRA_CFLAGS="-DGP712" GP_CHIP=GP712 modules
mv greenpeak_GP712_drv.ko GP712_drv.ko
