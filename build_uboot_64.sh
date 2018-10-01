#!/bin/bash
TOPDIR=`pwd`
#TOOLCHAIN=asdk64-4.9.4-a53-EL-3.10-g2.19-a64nt-160307
TOOLCHAIN=gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
cd u-boot-rt
./bpi-w2.sh
