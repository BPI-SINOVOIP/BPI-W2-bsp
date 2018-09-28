#!/bin/bash
#$Header: $
#$Change: $
#$DateTime: $

export GP_CHIP=GP712

make \
KERNELDIR=${_UWPROJECTSROOT}/gpHub/P601_Raspberry_PI/bin/v2.0.0.0/kernel3.18.14+_RPi1_B/ \
CROSS_COMPILE=${_UWPROJECTSROOT}/gpHub/TOOL_RPi/bin/arm-gcc-4.7.1/bin/arm-bcm2708hardfp-linux-gnueabi- \
ARCH=arm \
EXTRA_CFLAGS="-I\$(src)/RPi_3_2_27 -D${GP_CHIP}" \
$@
