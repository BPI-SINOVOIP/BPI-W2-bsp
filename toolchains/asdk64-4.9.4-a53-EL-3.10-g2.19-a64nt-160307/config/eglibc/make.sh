#!/bin/bash
#
# Realtek Semiconductor Corp.
#
# Tony Wu (tonywu@realtek.com)
# Dec. 7, 2010
#

if [ $# -lt 2 ]; then
    echo "usage: $0 dir_wrapper cflags"
    exit 1
fi

DIR_RSDK=$1; shift
TARGET_MARCH=$*

DIR_LIBC=${DIR_RSDK}/config/eglibc
DIR_SUMP=${DIR_RSDK}/sump
DIR_TMPFS=${DIR_RSDK}/tmpfs

if [[ `basename $DIR_RSDK` =~ 'asdk64-' ]] && [[ $TARGET_MARCH =~ 'armv8-a' ]] ; then
	CONFIG_ARCH=aarch64
	CONFIG_SPECIFIC=""
        TARGET_NAME=aarch64-linux
        TARGET_CROSS=${TARGET_NAME}-

elif [[ $TARGET_MARCH =~ 'arm' ]] || [[ $TARGET_MARCH =~ 'cortex' ]]; then
	CONFIG_ARCH=arm
	CONFIG_SPECIFIC=""
        TARGET_NAME=arm-linux-gnueabi
        TARGET_CROSS=${TARGET_NAME}-
fi

if [[ $TARGET_MARCH =~ 'mips' ]]; then
	CONFIG_ARCH=mips
	CONFIG_SPECIFIC="--with-mips-plt"
        TARGET_NAME=mips-linux
        TARGET_CROSS=${TARGET_NAME}-
fi

if [[ $TARGET_MARCH =~ '-msoft-float' ]]; then
	CONFIG_FLOAT='--without-fp'
else
	CONFIG_FLOAT='--with-fp'
fi

BUILD_CC="gcc"
AR="${TARGET_CROSS}ar"
AS="${TARGET_CROSS}gcc -c ${TARGET_MARCH}"
LD="${TARGET_CROSS}ld"
NM="${TARGET_CROSS}nm"
CC="${TARGET_CROSS}gcc ${TARGET_MARCH}"
CXX="${TARGET_CROSS}g++ ${TARGET_MARCH}"
RANLIB="${TARGET_CROSS}ranlib"
CFLAGS="-Os -pipe -funit-at-a-time"
export BUILD_CC AR AS LD NM CC CXX RANLIB CFLAGS

##
## config
##
mkdir -p ${DIR_SUMP}
cp ${DIR_LIBC}/libc/option-groups.defaults ${DIR_SUMP}/option-groups.config

cd ${DIR_SUMP}
${DIR_LIBC}/libc/configure					\
	--prefix=					\
	--build=i686-pc-linux				\
	--host=${TARGET_NAME}				\
	--with-headers=${DIR_RSDK}/include		\
	--enable-shared					\
	--disable-werror				\
	--disable-profile				\
	--disable-multi-arch				\
	${CONFIG_FLOAT}					\
	${CONFIG_SPECIFIC}				\
	--with-tls					\
	--with-elf					\
	--with-__thread					\
	--without-gd					\
	--without-cvs					\
	--without-selinux				\
	--enable-obsolete-rpc				\
	--enable-add-ons

##
## compile and install
##
make all || exit 1
make install install_root=${DIR_TMPFS} || exit 1

for f in ${DIR_TMPFS}/lib/libc.so ${DIR_TMPFS}/lib/libpthread.so ; do 
    if [ -f $$f -a ! -L $$f ] ; then
        sed -i -e 's,/lib/,,g' $$f ;
    fi
done

##
## postifx
##
cp ${DIR_SUMP}/nptl/libpthread_pic.a ${DIR_TMPFS}/lib/libpthread_pic.a
cp ${DIR_SUMP}/libpthread.map ${DIR_TMPFS}/lib/libpthread_pic.map
mkdir ${DIR_TMPFS}/lib/libpthread_pic
cp ${DIR_SUMP}/nptl/crt*.o ${DIR_TMPFS}/lib/libpthread_pic
