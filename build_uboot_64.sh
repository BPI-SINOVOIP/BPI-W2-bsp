#!/bin/bash
TOPDIR=`pwd`
TOOLCHAIN=asdk64-4.9.4-a53-EL-3.10-g2.19-a64nt-160307
export PATH=$TOPDIR/toolchains/$TOOLCHAIN/bin:$PATH
cd u-boot-rt
./bpi-w2.sh
