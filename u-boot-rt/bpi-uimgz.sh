#!/bin/bash

BOARD=bpi-w2
if [ -z $BOARD ] ; then
	echo "usage: $0 BOARD"
	exit 1
fi

echo ${BOARD}
PADBIN=pad.bin
UBOOTBIN=u-boot.bin
UBOOTIMG=u-boot-2015.07-${BOARD}-2k.img
if [ ! -f ${PADBIN} ] ; then
	dd if=/dev/zero of=${PADBIN} bs=1k count=38
fi
if [ -f ${UBOOTBIN} ] ; then
	cat ${PADBIN} ${UBOOTBIN} > ${UBOOTIMG}
fi
rm -f ${UBOOTIMG}.gz
gzip $UBOOTIMG
