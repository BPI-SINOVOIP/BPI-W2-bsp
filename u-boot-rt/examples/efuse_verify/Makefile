#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

LOAD_ADDR = 0x01610000
STATIC_LIB = ../../static_lib/libefuse.verify.a
# ********************************************************************
# Detect compiling environment.
# ********************************************************************
UNAME = $(shell uname)
LINUX_ENV = "LINUX"
CYGWIN_ENV = "CYGWIN"
ENV = $(CYGWIN_ENV)	# default

ifneq "$(filter Linux%,$(UNAME))" ""
ENV = $(LINUX_ENV)
endif

ifneq "$(filter CYGWIN%,$(UNAME))" ""
ENV = $(CYGWIN_ENV)
endif

# ********************************************************************
# Directories specifics.
# ********************************************************************

PERL    = perl
RM      = rm -rf
CD      = cd
CAT     = cat
CP      = cp

TOP_DIR         = $(shell cd .; pwd)
INCLUDE_DIR     = $(TOP_DIR)/include

TOP_DIR              = $(shell cd .; pwd)
TOOLS_DIR            = $(TOP_DIR)/../flash_writer/tools
SCRIPT_DIR           = $(TOOLS_DIR)/script
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern.pl
GEN_LENGTH_HEADER    = $(SCRIPT_DIR)/gen_length_header.pl
OUTPUT_PATH          = $(TOP_DIR)/out

OPENSSL    = openssl
SHA_DIR    = $(TOOLS_DIR)/do_sha256
SHA_EXE    = $(SHA_DIR)/do_sha256
OBFUSECATOR = $(TOP_DIR)/../flash_writer/tools/obfuse/obfuse
EFUSE_PROGRAMMER = $(TOP_DIR)/../efuse_programmer/efuse_programmer.bin
EFUSE_PROGRAMMER_PADDING = $(TOP_DIR)/efuse_programmer.padding
EFUSE_PROGRAMMER_DIGEST  = $(TOP_DIR)/efuse_programmer.digest
EFUSE_PROGRAMMER_FINAL   = $(TOP_DIR)/efuse_programmer.final
EFUSE_PROGRAMMER_FINAL_ENC   = $(TOP_DIR)/efuse_programmer.final.enc
EFUSE_PROGRAMMER_DIGEST_ENC  = $(TOP_DIR)/efuse_programmer.digest.enc
EFUSE_PROGRAMMER_COMPLETE_ENC = $(TOP_DIR)/out/efuse_programmer.complete.enc
EFUSE_PROGRAMMER_LENGTH_HEADER = $(TOP_DIR)/efuse_programmer.header
BOOTCODE_UBOOT_TARGET       = $(TOP_DIR)/../../u-boot.bin
TMP_RSA_OUT         = rsa_enc.bin
REAL_RSA_OUT        = $(TOP_DIR)/msg.bin
RRMODN              = $(TOP_DIR)/RRModN.bin
NP_INV32            = $(TOP_DIR)/np_inv32.bin
RTSSL_EXE = $(TOP_DIR)/../../examples/flash_writer/tools/RtSSL/RtSSL
STR2BIN_PL = $(TOP_DIR)/../../examples/flash_writer/tools/script/str2bin.pl
REVERSE_PL = $(TOP_DIR)/../../examples/flash_writer/tools/script/reverse.pl
RSA_KEY_FILE = $(TOP_DIR)/secure_key/rsa_key_2048.verify.pem
#RSA_KEY_TEXT_PATH = $(TOP_DIR)/secure_key/rsa_key_2048.verify.text
RSA_PUB_BIN = $(TOP_DIR)/secure_key/rsa_pub.verify.bin
RSA_PUB_REV_BIN = $(TOP_DIR)/secure_key/rsa_pub_rev.bin
ORG_RSA_PUB_FW_REV_BIN = $(TOP_DIR)/../../examples/flash_writer/image/rsa_key_2048.fw.pem.bin.rev
ORG_RSA_PUB_TEE_REV_BIN = $(TOP_DIR)/../../examples/flash_writer/image/rsa_key_2048.tee.pem.bin.rev
AES_KEY_TARGET = $(TOP_DIR)/secure_key/aes_128bit_key.verify.dec.bin
AES_KEY_ENC = $(TOP_DIR)/secure_key/aes_128bit_key.verify.enc.bin

BIN_ARGS      = "rsa_pub_key="$(RSA_PUB_REV_BIN)
BIN_ARGS         += "aes_key="$(AES_KEY_ENC)
#-------------------------------------------------
include $(TOP_DIR)/config.mk

ELF-y        := $(OUTPUT_PATH)/efuse_verify

#
# Some versions of make do not handle trailing white spaces properly;
# leading to build failures. The problem was found with GNU Make 3.80.
# Using 'strip' as a workaround for the problem.
#
ELF := $(strip $(ELF-y))

SREC := $(addsuffix .srec,$(ELF))
BIN  := $(addsuffix .bin,$(ELF))
DIS  := $(addsuffix .dis,$(ELF))


SOBJS	:= temp_target_array.o
SOBJS	+= start64.o
#COBJS	:= verifymain.o util.o  strlen.o strstr.o strtoul.o ctype.o mcp.o efuse.o timer.o cache_v7.o obfuseLib.o
GOBJS	:= verifymain.o util.o  mcp.o efuse.o timer.o cache_v7.o obfuseLib.o #for build static library
COBJS	:= strlen.o strstr.o strtoul.o ctype.o
LIB	= $(obj)

LIBCOBJS = 

LIBOBJS	= $(addprefix $(obj),$(LIBAOBJS) $(LIBCOBJS))

SRCS	:= $(COBJS:.o=.c) $(LIBCOBJS:.o=.c) $(LIBAOBJS:.o=.S) $(SOBJS:.o=.S)
OBJS	:= $(addprefix $(obj),$(COBJS))
SSOBJS	:= $(addprefix $(obj),$(SOBJS))


gcclibdir := $(shell dirname `$(CC) -print-libgcc-file-name`)

CPPFLAGS += -I.. -I$(INCLUDE_DIR) -I$(TOP_DIR)/include
INCDIRS =  -I$(TOP_DIR)/../../include -I.. -I$(INCLUDE_DIR) 

# For PowerPC there's no need to compile standalone applications as a
# relocatable executable.  The relocation data is not needed, and
# also causes the entry point of the standalone application to be
# inconsistent.
ifeq ($(ARCH),powerpc)
AFLAGS := $(filter-out $(RELFLAGS),$(AFLAGS))
CFLAGS := $(filter-out $(RELFLAGS),$(CFLAGS))
CPPFLAGS := $(filter-out $(RELFLAGS),$(CPPFLAGS))
endif

#---------------------------------------------------------------------
#$(call hwrsa-sign, rsa_key_text, clear_data, enc_data)
hwrsa-sign =                                                                                          \
        $(OPENSSL) rsa -text -in $(1) -out $(1).text;                                           \
        dd if=$(BOOTCODE_UBOOT_TARGET) of=224b.bin bs=224 count=1;                                    \
        cat 224b.bin $(2) > clear_data.bin;                                                           \
        $(OPENSSL) rsautl -inkey $(1) -sign -raw -in clear_data.bin -out $(TMP_RSA_OUT);   \
        $(GEN_RSA_PATTERN) --key $(1).text --msg $(TMP_RSA_OUT) --binary;                                  \
        cat $(REAL_RSA_OUT) $(RRMODN) $(NP_INV32) > $(3)

# We don't want gcc reordering functions if possible.  This ensures that an
# application's entry point will be the first function in the application's
# source file.
#CFLAGS = -g -O2 -fno-common -fzero-initialized-in-bss -msoft-float -mthumb-interwork -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem $(gcclibdir)/../include -pipe -DCONFIG_ARM -D__ARM__ -marm -mabi=aapcs-linux -march=armv8-a -D__EL__
CFLAGS = -g -Os -fno-common -ffixed-r8 -D__KERNEL__ -fno-builtin -ffreestanding -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__  -march=armv8-a -D__EL__ -D__ARM_ARCH_8A__
CFLAGS += $(INCDIRS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
		$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
		$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

all:	clean gen_key b2a $(OBJS) $(SSOBJS) $(LIB) $(ELF) $(SREC) $(BIN)

gen_key:
	#sw method
	$(STR2BIN_PL) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY_FILE)` > $(RSA_PUB_BIN)
	$(REVERSE_PL) $(RSA_PUB_BIN) > $(RSA_PUB_REV_BIN)
	#hw method
	$(OBFUSECATOR) $(RTSSL_EXE) 98 $(AES_KEY_TARGET) dummy $(AES_KEY_ENC) dummy
b2a:
	./bin2ascii $(BIN_ARGS) > temp_target_array.h

clean:
	-rm -f $(ELF) $(COBJS) $(SOBJS) temp_target_array.h *.bin *.map *.dis *.srec efuse_verify*.* efuse_programmer*.* efuse_programmer $(OUTPUT_PATH)/*
	
gen_lib:
	$(AR) rcs $(STATIC_LIB) $(GOBJS)
#########################################################################
$(LIB):	$(obj).depend $(LIBOBJS)
	$(call cmd_link_o_target, $(LIBOBJS))

$(ELF): 	$(LIB) 
		$(LD) $(LDFLAGS) -g -Ttext $(LOAD_ADDR) \
			-o $@ -e start $(SOBJS) $(COBJS) $(LIB) $(STATIC_LIB) \
			-L$(gcclibdir) -lgcc -Map efuse_verify.map

$(SREC):
$(obj)%.srec:	$(obj)%
		$(OBJCOPY) -O srec $< $@ 2>/dev/null

$(BIN):
$(obj)%.bin:	$(obj)%
		$(OBJCOPY) -O binary $< $@ 2>/dev/null
		$(OBJDUMP) -DS $<  >$(DIS)
		$(SHA_EXE) $(EFUSE_PROGRAMMER) $(EFUSE_PROGRAMMER_PADDING) $(EFUSE_PROGRAMMER_DIGEST)
		cat $(EFUSE_PROGRAMMER) $(EFUSE_PROGRAMMER_PADDING) > $(EFUSE_PROGRAMMER_FINAL)
		$(RTSSL_EXE) enc -e -aes_128_cbc -i $(EFUSE_PROGRAMMER_FINAL) -o $(EFUSE_PROGRAMMER_FINAL_ENC) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_TARGET)`
		$(call hwrsa-sign, $(RSA_KEY_FILE), $(EFUSE_PROGRAMMER_DIGEST), $(EFUSE_PROGRAMMER_DIGEST_ENC))
		$(GEN_LENGTH_HEADER) $(EFUSE_PROGRAMMER_FINAL_ENC) $(EFUSE_PROGRAMMER_LENGTH_HEADER) 
		cat $(EFUSE_PROGRAMMER_LENGTH_HEADER) $(EFUSE_PROGRAMMER_FINAL_ENC) $(EFUSE_PROGRAMMER_DIGEST_ENC) > $(EFUSE_PROGRAMMER_COMPLETE_ENC)
OBJ_DIR=.
ASM=$(CC)
$(OBJ_DIR)/%.o: %.c
		$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o: %.S
		$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.s
		$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@
