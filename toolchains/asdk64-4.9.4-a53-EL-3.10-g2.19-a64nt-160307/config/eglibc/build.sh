#!/bin/bash
#
# Realtek Semiconductor Corp.
#
# Tony Wu (tonywu@realtek.com)
# Dec. 7, 2010
#

NUM_ARGS=5

if [ $# -ne $NUM_ARGS ]
then
    echo "usage: $0 function cpu dir_build dir_eglibc dir_stage"
    exit 1
fi

SDK=$1
FUNCTION=$2
DIR_BUILD=$3
DIR_GLIBC=$4
DIR_STAGE=$5

case "$SDK" in
"asdk")
	TARGET_MARCH=""
	TARGET_NAME=arm-linux-gnueabi
	TARGET_PREFIX=arm-linux-gnueabi
	CONFIG_SPECIFIC=""
	;;
"asdk64")
	TARGET_MARCH=""
	TARGET_NAME=aarch64-linux
	TARGET_PREFIX=aarch64-linux
	CONFIG_SPECIFIC=""
	;;
"msdk")
	TARGET_MARCH="-mips32r2"
	TARGET_NAME=mips-linux
	TARGET_PREFIX=mips-linux
	CONFIG_SPECIFIC="--with-mips-plt"
	;;
"rsdk")
	TARGET_MARCH="-march=4281"
	TARGET_NAME=mips-linux
	TARGET_PREFIX=mips-linux
	CONFIG_SPECIFIC="--with-mips-plt"
	;;
"*")
	echo "unknown processor"
	exit 1
	;;
esac

TARGET_CROSS=${TARGET_PREFIX}-
TARGET_CC=${TARGET_CROSS}gcc
TARGET_OPT="-Os -pipe -funit-at-a-time"

##
## eglibc_make
##
eglibc_make()
{
  multi_cfg=$1
  multi_dir=$2

  TARGET_CFLAGS="$TARGET_MARCH $multi_cfg"
  TARGET_LIBPATH="$multi_dir"
  TARGET_OBJPATH="$( echo "$multi_cfg" | sed -r -e 's/[ =]/-/g' )"

  if [[ $multi_cfg =~ '-msoft-float' ]]; then
      CONFIG_FLOAT="--without-fp"
  else
      CONFIG_FLOAT="--with-fp"
  fi

  BUILD_CC="gcc"
  AR="${TARGET_CROSS}ar"
  AS="${TARGET_CROSS}gcc -c ${TARGET_CFLAGS}"
  LD="${TARGET_CROSS}ld"
  NM="${TARGET_CROSS}nm"
  CC="${TARGET_CROSS}gcc ${TARGET_CFLAGS}"
  CXX="${TARGET_CROSS}g++ ${TARGET_CFLAGS}"
  RANLIB="${TARGET_CROSS}ranlib"
  CFLAGS="${TARGET_OPT}"
  export BUILD_CC AR AS LD NM CC CXX RANLIB CFLAGS

  DIR_SUMP=${DIR_STAGE}/eglibc-${FUNCTION}-${TARGET_OBJPATH}
  mkdir -p ${DIR_SUMP}/libc
  cp ${DIR_GLIBC}/libc/option-groups.defaults ${DIR_SUMP}/libc/option-groups.config

  case "${FUNCTION}" in
  "prepare")
    CONFIG_PREFIX=/usr
    ;;
  "install")
    CONFIG_PREFIX=
    ;;
  esac

  (cd ${DIR_SUMP};					\
	${DIR_GLIBC}/libc/configure			\
		--prefix=${CONFIG_PREFIX}		\
		--build=i686-pc-linux			\
		--host=${TARGET_NAME}			\
		--enable-kernel=2.6.23			\
		--with-headers=${DIR_STAGE}/sysroot/usr/include \
		--disable-werror			\
		--disable-profile			\
		--disable-multi-arch			\
		--with-tls				\
		--with-__thread				\
		--with-elf				\
		${CONFIG_FLOAT}				\
		${CONFIG_SPECIFIC}			\
		--without-gd				\
		--without-cvs				\
		--without-selinux			\
		--enable-obsolete-rpc			\
		--enable-add-ons			\
  )

  case "${FUNCTION}" in
  "prepare")
    if [ ! -f ${DIR_STAGE}/.eglibc-bootstrap ]; then
	make -C ${DIR_SUMP}				\
		install-headers				\
		install_root=${DIR_STAGE}/sysroot	\
		install-bootstrap-headers=yes || exit
	touch ${DIR_STAGE}/.eglibc-bootstrap
    fi

    (cd ${DIR_SUMP};							\
        mkdir -p ${DIR_STAGE}/sysroot/usr/lib/${TARGET_LIBPATH};	\
        make csu/subdir_lib;						\
        cp csu/crt*.o ${DIR_STAGE}/sysroot/usr/lib/${TARGET_LIBPATH};	\
        ${CC} ${CFLAGS} -nostdlib -shared -x c /dev/null		\
            -o ${DIR_STAGE}/sysroot/usr/lib/${TARGET_LIBPATH}/libc.so	\
    )
    ;;
  "install")
    make -C ${DIR_SUMP} all || exit
    make -C ${DIR_SUMP} install install_root=${DIR_STAGE}/tmpfs

    mkdir -p ${DIR_BUILD}/lib/${TARGET_LIBPATH}
    cp -a ${DIR_STAGE}/tmpfs/lib/* ${DIR_BUILD}/lib/${TARGET_LIBPATH}
    if [ ! -f ${DIR_STAGE}/.eglibc-headered ]; then
	  cp -a ${DIR_STAGE}/tmpfs/include/* ${DIR_BUILD}/include
    else
	  cp -a ${DIR_STAGE}/tmpfs/include/gnu/stubs-*.h \
		${DIR_BUILD}/include/gnu
    fi
    rm -rf ${DIR_STAGE}/tmpfs
    touch ${DIR_STAGE}/.eglibc-headered

    (cd ${DIR_BUILD}/lib/${TARGET_LIBPATH};		\
        for f in libc.so libpthread.so libgcc_s.so ; do \
            if [ -f $f ] ; then				\
                sed -i -e 's,/lib/,,g' $f ;		\
            fi						\
        done						\
    )
    ;;
  esac
}

##
## config
##
eglibc_init()
{
  mkdir -p ${DIR_STAGE}/sysroot/usr
  mkdir -p ${DIR_STAGE}/sysroot/usr/lib

  case "${FUNCTION}" in
  "prepare")
    mkdir -p ${DIR_STAGE}/sysroot/usr/include
    cp -a ${DIR_GLIBC}/../kernel-${SDK}/* ${DIR_STAGE}/sysroot/usr/include
    ;;
  "install")
    mkdir -p ${DIR_BUILD}/include
    cp -a ${DIR_GLIBC}/../kernel-${SDK}/* ${DIR_BUILD}/include
    ;;
  esac
}

#.;
#tls;@fuse-tls
#armv7;@march=armv7-a
#armv7/tls;@march=armv7-a@fuse-tls

##
## compile and install
##
eglibc_init

multilibs=( $(${TARGET_CROSS}gcc -print-multi-lib) )

for multilib in "${multilibs[@]}"; do
    multi_cfg="$( echo "${multilib#*;}" | sed -r -e 's/@/ -/g;' )"
    multi_dir="${multilib%%;*}"
    eglibc_make "$multi_cfg" "$multi_dir"
done
