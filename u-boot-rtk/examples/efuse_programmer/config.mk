TARGET_ARCH=aarch64

ifeq ($(TARGET_ARCH),aarch64)
CC=aarch64-linux-gcc
LD=aarch64-linux-ld
OBJDUMP=aarch64-linux-objdump
OBJCOPY=aarch64-linux-objcopy
endif

