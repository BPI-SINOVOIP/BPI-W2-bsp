

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

include inc/$(PRJ).inc
LOAD_ADDR = 0x01500000

# ********************************************************************
# Directories specifics.
# ********************************************************************

PERL    = perl
RM      = rm -rf
CD      = cd
CAT     = cat
CP      = cp
SED     = sed

CONFIGCONV_SCRIPT    = configconv.pl

TOP_DIR              = $(shell cd .; pwd)
ROOT_DIR	     = ../../arch/arm/include/asm/arch/
TOOLS_DIR            = $(TOP_DIR)/tools
#BIN_DIR             = $(TOP_DIR)/bin
IMAGE_DIR            = $(TOP_DIR)/image
INCLUDE_DIR          = $(TOP_DIR)/include
SCRIPT_DIR           = $(TOOLS_DIR)/script

ifeq ($(CHIP_TYPE), 0000)
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern64_0000.pl
else
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern64_0001.pl
endif

HW_SETTING_DIR       = $(IMAGE_DIR)/hw_setting
HW_SETTING_MAKER_DIR = $(TOOLS_DIR)/hw_setting_maker
BINDALLBIN_MAKER_DIR = $(TOOLS_DIR)/bindAllBins

SHA_DIR    = $(TOOLS_DIR)/do_sha256
RTSSL_DIR  = $(TOOLS_DIR)/RtSSL
OBFUSE_DIR  = $(TOOLS_DIR)/obfuse
OPENSSL    = openssl
SCRIPT_DIR = $(TOOLS_DIR)/script
CRC32_DIR  = $(TOOLS_DIR)/crc32
NF_PROFILER_DIR  = $(TOOLS_DIR)/nf_profiler

HW_SETTING_TARGET = $(HW_SETTING_DIR)/$(Board_HWSETTING).bin
ifeq ($(SUB_CHIP_ID), )
HW_SETTING_TARGET_RAW_FILE = $(HW_SETTING_DIR)/$(CHIP_ID)/$(CUSTOMER_ID)/$(CHIP_TYPE)/$(Board_HWSETTING).config
else
HW_SETTING_TARGET_RAW_FILE = $(HW_SETTING_DIR)/$(SUB_CHIP_ID)/$(CUSTOMER_ID)/$(CHIP_TYPE)/$(Board_HWSETTING).config
endif
HW_SETTING_TARGET_PADDING = $(HW_SETTING_DIR)/$(Board_HWSETTING)_padding.bin
HW_SETTING_TARGET_ALL_PADDING = $(HW_SETTING_DIR)/$(Board_HWSETTING)_padding_all.bin
HW_SETTING_TARGET_ENC = $(TOP_DIR)/image/hw_setting/$(Board_HWSETTING)_enc.bin
HW_SETTING_TARGET_INVERSE = $(Board_HWSETTING)_inv.bin
HW_SETTING_TARGET_ALL = $(TOP_DIR)/$(Board_HWSETTING)_all.bin
HW_SETTING_TARGET_ENC_ALL = $(TOP_DIR)/$(Board_HWSETTING)_enc_all.bin

#bind all bins
BINDALLBIN_UTIL	     = bindAllBins
BIND_FOLDER	     =	Bind
HW_SETTING_TARGET_FINAL = $(BIND_FOLDER)/hwsetting.bin
HW_SETTING_HEADER_FINAL = $(BIND_FOLDER)/hwsetting_header.bin

HW_SETTING_HEADER_FINAL_PADDING = $(BIND_FOLDER)/hwsetting_header_padding.bin
HW_SETTING_HEADER_FINAL_DIGEST = $(BIND_FOLDER)/hwsetting_header_digest.bin
HW_SETTING_HEADER_64B = $(BIND_FOLDER)/hwsetting_header_64B.bin
HW_SETTING_HEADER_FINAL_ENC = $(BIND_FOLDER)/hwsetting_header_enc.bin
UBOOT_FINAL = $(BIND_FOLDER)/uboot.bin
UBOOT2_FINAL = $(BIND_FOLDER)/uboot2.bin
RESCUE_FINAL = $(BIND_FOLDER)/rescue.bin
FSBL_FINAL = $(BIND_FOLDER)/fsbl.bin
FSBL_VM_FINAL = $(BIND_FOLDER)/fsbl_vm.bin
FSBL_OS_FINAL = $(BIND_FOLDER)/fsbl_os.bin
BL31_FINAL = $(BIND_FOLDER)/bl31.bin
RSA_BIN_FW_FINAL = $(BIND_FOLDER)/rsa_bin_fw.bin
RSA_BIN_TEE_FINAL = $(BIND_FOLDER)/rsa_bin_tee.bin
HW_SETTING_PADDING_FINAL = $(BIND_FOLDER)/hwsetting_padding.bin
BOOTCODE_BOOT_PADDING_FINAL = $(BIND_FOLDER)/uboot_padding.bin
LINUX_RESCUE_PADDING_FINAL = $(BIND_FOLDER)/rescue_padding.bin
FSBL_PADDING_FINAL = $(BIND_FOLDER)/fsbl_padding.bin
FSBL_VM_PADDING_FINAL = $(BIND_FOLDER)/fsbl_vm_padding.bin
FSBL_OS_PADDING_FINAL = $(BIND_FOLDER)/fsbl_os_padding.bin
BL31_PADDING_FINAL = $(BIND_FOLDER)/bl31_padding.bin
RSA_BIN_FW_PADDING_FINAL = $(BIND_FOLDER)/rsa_bin_fw_padding.bin
RSA_BIN_TEE_PADDING_FINAL = $(BIND_FOLDER)/rsa_bin_tee_padding.bin
OBFUSE  = $(OBFUSE_DIR)/obfuse_$(CHIP_TYPE)
OBFUSE_H  = $(OBFUSE_DIR)/obfuse_h
UBOOT_ENC	     = boot_enc

#usb temp data
SHA1_DATA_ORG	     = usb_sha1_data_org.bin
SHA1_DATA	     = usb_sha1_data.bin
SHA1_DATA_PADDING    = usb_sha1_data_padding.bin
SHA2_DATA_ORG	     = usb_sha2_data_org.bin
SHA2_DATA	     = usb_sha2_data.bin
SHA2_DATA_PADDING    = usb_sha2_data_padding.bin
SH1		     = usb_sh1.bin
SH2		     = usb_sh2.bin
RS1		     = usb_rs1.bin
RS2		     = usb_rs2.bin
RS2_ENC		     = usb_rs2_enc.bin
B1		     = usb_b1.bin
B1_ENC		     = usb_b1_enc.bin

DRAM_STR            = _$(Board_DRAM_Block)x$(Board_DRAM_Number)

BIN_ARGS	    = "hw_setting="$(HW_SETTING_TARGET_ENC_ALL)

LOGO_CHANGER_DIR    = $(TOOLS_DIR)/logo_changer

LOGO_BMP_PATH       = $(IMAGE_DIR)/$(Logo_File_Name)
LOGO_DAT_PATH       = $(IMAGE_DIR)/$(Logo_File_Name).dat
LOGO_INF_PATH       = $(IMAGE_DIR)/$(Logo_File_Name).inf

LOGO2_BMP_PATH      = $(IMAGE_DIR)/$(Logo2_File_Name)
LOGO2_DAT_PATH      = $(IMAGE_DIR)/$(Logo2_File_Name).dat
LOGO2_INF_PATH      = $(IMAGE_DIR)/$(Logo2_File_Name).inf

LOGO3_BMP_PATH      = $(IMAGE_DIR)/$(Logo3_File_Name)
LOGO3_DAT_PATH      = $(IMAGE_DIR)/$(Logo3_File_Name).dat
LOGO3_INF_PATH      = $(IMAGE_DIR)/$(Logo3_File_Name).inf

LOGO4_BMP_PATH      = $(IMAGE_DIR)/$(Logo4_File_Name)
LOGO4_DAT_PATH      = $(IMAGE_DIR)/$(Logo4_File_Name).dat
LOGO4_INF_PATH      = $(IMAGE_DIR)/$(Logo4_File_Name).inf

LOGO5_BMP_PATH      = $(IMAGE_DIR)/$(Logo5_File_Name)
LOGO5_DAT_PATH      = $(IMAGE_DIR)/$(Logo5_File_Name).dat
LOGO5_INF_PATH      = $(IMAGE_DIR)/$(Logo5_File_Name).inf

LOGO6_BMP_PATH      = $(IMAGE_DIR)/$(Logo6_File_Name)
LOGO6_DAT_PATH      = $(IMAGE_DIR)/$(Logo6_File_Name).dat
LOGO6_INF_PATH      = $(IMAGE_DIR)/$(Logo6_File_Name).inf

LOGO7_BMP_PATH      = $(IMAGE_DIR)/$(Logo7_File_Name)
LOGO7_DAT_PATH      = $(IMAGE_DIR)/$(Logo7_File_Name).dat
LOGO7_INF_PATH      = $(IMAGE_DIR)/$(Logo7_File_Name).inf

LOGO8_BMP_PATH      = $(IMAGE_DIR)/$(Logo8_File_Name)
LOGO8_DAT_PATH      = $(IMAGE_DIR)/$(Logo8_File_Name).dat
LOGO8_INF_PATH      = $(IMAGE_DIR)/$(Logo8_File_Name).inf

#SPLIT_AES_KEY      = $(TOOLS_DIR)/script/split_AES_key.pl
BINARY_TO_ASCII     = $(TOOLS_DIR)/script/binary2ascii.pl
STR2BIN             = $(TOOLS_DIR)/script/str2bin.pl
REVERSE_BIN         = $(TOOLS_DIR)/script/revsre.pl
BIN2HEX	            = $(TOOLS_DIR)/script/bin2hex.pl
BIN2HEX_EMMC	    = $(TOOLS_DIR)/script/bin2hex_e.pl
REVERSE_RSA         = $(TOOLS_DIR)/script/reverse_rsa_data.pl
REVERSE_PL          = $(TOOLS_DIR)/script/reverse.pl
RSA_KEY_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File)
RSA_INF_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File).inf
RSA_BIN_PATH        = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File).bin
RSA_KEY_FW_PATH     = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_FW_File)
RSA_INF_FW_PATH     = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_FW_File).inf
RSA_BIN_FW_PATH     = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_FW_File).bin
RSA_KEY_TEE_PATH    = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_TEE_File)
RSA_INF_TEE_PATH    = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_TEE_File).inf
RSA_BIN_TEE_PATH    = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_TEE_File).bin
RSA_KEY0_PATH       = $(IMAGE_DIR)/$(Config_Secure_RSA_Key0_File)
RSA_INF0_PATH       = $(IMAGE_DIR)/$(Config_Secure_RSA_Key0_File).inf
TMP_RSA_OUT         = rsa_enc.bin
REAL_RSA_OUT        = $(TOP_DIR)/msg.bin
RRMODN              = $(TOP_DIR)/RRModN.bin
NP_INV32            = $(TOP_DIR)/np_inv32.bin
AES_KEY_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key_File_Name)
AES_SEED_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Seed_File_Name)
AES_SEED_PATH_ENC    = $(IMAGE_DIR)/$(Config_Secure_AES_Seed_File_Name).enc
AES_KEY1_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key1_File_Name)
AES_KEY2_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key2_File_Name)
AES_KEY3_PATH        = $(IMAGE_DIR)/$(Config_Secure_AES_Key3_File_Name)
AES128_KEY_PATH     = $(IMAGE_DIR)/$(Config_USB_Secure_AES_Key0_File)
#AES_INF_PATH       = $(IMAGE_DIR)/$(Config_Secure_AES_Key_File).inf
#AES_SEED_PATH      = $(IMAGE_DIR)/$(Config_Secure_AES_Seed_File_Name)

# Hercules_HW_keyladder
AES_SCK_PATH        = $(IMAGE_DIR)/aes_sck_flash.bin
AES_SCK_VM_PATH        = $(IMAGE_DIR)/aes_sck_flash_vm.bin
AES_VENDOR_ID_PATH        = $(IMAGE_DIR)/aes_vendor_id.bin
AES_MODULE_ID_PATH        = $(IMAGE_DIR)/aes_module_id.bin

PRJ_CONFIG_TARGET               = $(PRJ_INC_DIR)/project_config.h
RESET_TARGET                    = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/bootmon-new.bin
MIPS_RESET_TARGET               = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/mips-bootmon-new.bin
ROM2_RESET_TARGET               = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/bootmon-new.bin
ARM_REDIR_TARGET                = $(TOP_DIR)/../redirect/redirect_packed.bin

BOOTCODE_UBOOT_TARGET       = $(TOP_DIR)/../../u-boot.bin

ifdef BOOTCODE_IS_LK
    BOOTCODE_UBOOT_TARGET       = $(BOOTCODE_LK_PATH)
endif

BOOTCODE_UBOOT_TARGET_SIM       = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/uboot_simulation.bin
BOOTCODE_BOOT_TARGET            = $(TOP_DIR)/uboot_packed.bin
BOOTCODE_BOOT_TARGET_TMP	= $(TOP_DIR)/uboot_packed_tmp.bin
BOOTCODE_BOOT_TARGET_ENC        = $(TOP_DIR)/uboot_packed_enc.bin
BOOTCODE_BOOT_TARGET_PADDING    = $(TOP_DIR)/uboot_packed_padding.bin
BOOTCODE_BOOT_HASH_TARGET       = $(TOP_DIR)/uboot_packed_hash.bin
BOOTCODE_BOOT_HASH_TARGET_AES   = $(TOP_DIR)/uboot_plus_redirect_packed_hash.bin.aes
BOOTCODE_BOOT_TARGET_ALL_PADDING = $(TOP_DIR)/sha256_padding_all.bin
BOOTCODE_BOOT_PADDING_TARGET    = $(TOP_DIR)/sha256_padding.bin
BOOTCODE_BOOT_DIGEST_TARGET     = $(TOP_DIR)/sha256_digest.bin
BOOTCODE_BOOT_HASH_TARGET2      = $(TOP_DIR)/hash_target.bin
SIGNATURE_TARGET                = signature.bin

BOOTCODE2_UBOOT_TARGET          = $(TOP_DIR)/../../u-boot.bin
BOOTCODE2_BOOT_TARGET           = $(TOP_DIR)/bootpart2_uboot_plus_redirect_packed.bin
BOOTCODE2_BOOT_HASH_TARGET      = $(TOP_DIR)/bootpart2_uboot_plus_redirect_packed_hash.bin
BOOTCODE2_BOOT_HASH_TARGET_AES  = $(TOP_DIR)/bootpart2_uboot_plus_redirect_packed_hash.bin.aes
BOOTCODE2_BOOT_PADDING_TARGET   = $(TOP_DIR)/bootpart2_uboot_sha256_padding.bin
BOOTCODE2_BOOT_DIGEST_TARGET    = $(TOP_DIR)/bootpart2_uboot_sha256_digest.bin
BOOTCODE2_BOOT_SIGNATURE_TARGET = bootcode2_signature.bin

BOOTCODE3_UBOOT_TARGET          = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/uboot_textbase_0x00020000.bin
BOOTCODE3_BOOT_TARGET           = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed.bin
BOOTCODE3_BOOT_HASH_TARGET      = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed_hash.bin
BOOTCODE3_BOOT_HASH_TARGET_AES  = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed_hash.bin.aes
BOOTCODE3_BOOT_PADDING_TARGET   = $(TOP_DIR)/bootpart3_uboot_sha256_padding.bin
BOOTCODE3_BOOT_DIGEST_TARGET    = $(TOP_DIR)/bootpart3_uboot_sha256_digest.bin
BOOTCODE3_BOOT_SIGNATURE_TARGET = bootcode3_signature.bin

FSBL_TARGET            = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/$(Config_FSBL_File_Name)
FSBL_VM_TARGET         = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/$(Config_FSBL_VM_File_Name)

FSBL_DIGEST_TARGET     = $(TOP_DIR)/fsbl_sha256_digest.bin
FSBL_SIGNATURE_TARGET  = $(TOP_DIR)/fsbl_signature_digest.bin
FSBL_TARGET_PADDING    = $(TOP_DIR)/fsbl_padding.bin
FSBL_HASH_TARGET       = $(TOP_DIR)/fsbl_hash.bin
FSBL_HASH_TARGET_AES   = $(TOP_DIR)/fsbl_hash.bin.aes

FSBL_VM_DIGEST_TARGET     = $(TOP_DIR)/fsbl_vm_sha256_digest.bin
FSBL_VM_SIGNATURE_TARGET  = $(TOP_DIR)/fsbl_vm_signature_digest.bin
FSBL_VM_TARGET_PADDING    = $(TOP_DIR)/fsbl_vm_padding.bin
FSBL_VM_HASH_TARGET       = $(TOP_DIR)/fsbl_vm_hash.bin
FSBL_VM_HASH_TARGET_AES   = $(TOP_DIR)/fsbl_vm_hash.bin.aes

FSBL_OS_TARGET            = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/$(Config_FSBL_OS_File_Name)
FSBL_OS_DIGEST_TARGET     = $(TOP_DIR)/fsbl_os_sha256_digest.bin
FSBL_OS_SIGNATURE_TARGET  = $(TOP_DIR)/fsbl_os_signature_digest.bin
FSBL_OS_TARGET_PADDING    = $(TOP_DIR)/fsbl_os_padding.bin
FSBL_OS_HASH_TARGET       = $(TOP_DIR)/fsbl_os_hash.bin
FSBL_OS_HASH_TARGET_AES   = $(TOP_DIR)/fsbl_os_hash.bin.aes

BL31_TARGET            = $(TOP_DIR)/bootimage/$(CHIP_ID)/$(CHIP_TYPE)/$(Config_BL31_File_Name)
BL31_DIGEST_TARGET     = $(TOP_DIR)/bl31_sha256_digest.bin
BL31_SIGNATURE_TARGET  = $(TOP_DIR)/bl31_signature_digest.bin
BL31_TARGET_PADDING    = $(TOP_DIR)/bl31_padding.bin
BL31_HASH_TARGET       = $(TOP_DIR)/bl31_hash.bin
BL31_HASH_TARGET_AES   = $(TOP_DIR)/bl31_hash.bin.aes

RSA_BIN_FW_TARGET             = $(RSA_BIN_FW_PATH).rev
RSA_BIN_FW_DIGEST_TARGET      = $(TOP_DIR)/rsa_pub_digest.fw.bin
RSA_BIN_FW_SIGNATURE_TARGET   = $(TOP_DIR)/rsa_pub_signature_digest.fw.bin
RSA_BIN_FW_TARGET_PADDING     = $(TOP_DIR)/rsa_pub_padding.fw.bin
RSA_BIN_FW_HASH_TARGET        = $(TOP_DIR)/rsa_pub_hash.fw.bin
RSA_BIN_FW_HASH_TARGET_AES    = $(TOP_DIR)/rsa_pub_hash.fw.bin.aes
RSA_BIN_TEE_TARGET            = $(RSA_BIN_TEE_PATH).rev
RSA_BIN_TEE_DIGEST_TARGET     = $(TOP_DIR)/rsa_pub_digest.tee.bin
RSA_BIN_TEE_SIGNATURE_TARGET  = $(TOP_DIR)/rsa_pub_signature_digest.tee.bin
RSA_BIN_TEE_TARGET_PADDING    = $(TOP_DIR)/rsa_pub_padding.tee.bin
RSA_BIN_TEE_HASH_TARGET       = $(TOP_DIR)/rsa_pub_hash.tee.bin
RSA_BIN_TEE_HASH_TARGET_AES   = $(TOP_DIR)/rsa_pub_hash.tee.bin.aes
#-------------------------------------------------------------------------------
TARGET_EXE             = $(TOP_DIR)/dvrboot.exe
HW_SETTING_DIGEST_ENC = hwsetting_digest_enc.bin

STR2BIN                = $(SCRIPT_DIR)/str2bin.pl
PACKAGE_TARGET         = $(PACKAGE_DIR)/package_MP.tar
RSA_KEY_FILE           = $(IMAGE_DIR)/$(Config_Secure_RSA_Key_File)
RSA_KEY0_FILE          = $(IMAGE_DIR)/$(Config_Secure_RSA_Key0_File)
RSA_KEY_PUB_FILE       = $(IMAGE_DIR)/rsa_pub.bin.rev
HW_SETTING_DIGEST      = hwsetting_digest.bin
HW_SETTING_SIGNATURE   = hwsetting_signature.bin
HW_SETTING_SIG_IMG     = hwsetting_sig_image.bin

LOGO_CHANGER = $(LOGO_CHANGER_DIR)/logo_changer
HW_SETTING_MAKER_AP	= generate_config
RTSSL_EXE = $(RTSSL_DIR)/RtSSL
SHA_EXE = $(SHA_DIR)/do_sha256
INVERSE = inverse
NF_PROFILER_EXE = $(NF_PROFILER_DIR)/nf_profiler

PACKAGE_PRJ_CONFIG = $(PACKAGE_DIR)/project_config.h
PACKAGE_HWSETTING  = $(PACKAGE_DIR)/hwsetting.bin
PACKAGE_BOOTCODE   = $(PACKAGE_DIR)/boot_target.bin

BIN_ARGS += "resetrom="$(RESET_TARGET)
BIN_ARGS += "mips_resetrom="$(MIPS_RESET_TARGET)
BIN_ARGS += "hasharray="$(BOOTCODE_BOOT_HASH_TARGET2)
BIN_ARGS += "signature="$(SIGNATURE_TARGET)

ifeq ($(Config_FSBL), TRUE)
        BIN_ARGS += "fsbl="$(FSBL_FINAL)
endif

ifeq ($(Config_FSBL_VM), TRUE)
        BIN_ARGS += "fsbl_vm="$(FSBL_VM_FINAL)
endif

ifeq ($(Config_FSBL_OS), TRUE)
        BIN_ARGS += "fsbl_os="$(FSBL_OS_FINAL)
endif

ifeq ($(Config_BL31), TRUE)
        BIN_ARGS += "bl31="$(BL31_FINAL)
endif

ifeq ($(Config_Secure_Improve), TRUE)
	BIN_ARGS += "Kpublic_fw="$(RSA_BIN_FW_HASH_TARGET_AES)
	BIN_ARGS += "Kpublic_tee="$(RSA_BIN_TEE_HASH_TARGET_AES)
	BIN_ARGS += "Kpublic_fw_signature="$(RSA_BIN_FW_SIGNATURE_TARGET)
	BIN_ARGS += "Kpublic_tee_signature="$(RSA_BIN_TEE_SIGNATURE_TARGET)
endif
ifeq ($(Config_RSA_Key_Pub_Embed), TRUE)
	BIN_ARGS += "rsa_pub="$(RSA_KEY_PUB_FILE)
endif

#Hercules hwrsa np_inv is 8B
hwrsa-sign-npinv64 =                                                                                          \
        $(OPENSSL) rsa -text -in $(1) -out $(1).text;                                           \
	$(OPENSSL) rsautl -inkey $(1) -sign -in $(2) -out $(TMP_RSA_OUT);			\
	$(GEN_RSA_PATTERN) --key $(1).text --msg $(TMP_RSA_OUT) --binary;      \
	cat $(REAL_RSA_OUT) $(RRMODN) $(NP_INV32) > $(3)

include $(TOP_DIR)/config.mk

ELF-$(ARCH)  :=
ELF-$(BOARD) :=
ELF-$(CPU)   :=
ELF-y        := dvrboot.exe

#ELF-$(CONFIG_SMC91111)        += smc91111_eeprom
#ELF-$(CONFIG_SMC911X)         += smc911x_eeprom
#ELF-$(CONFIG_SPI_FLASH_ATMEL) += atmel_df_pow2
#ELF-i386                      += 82559_eeprom
#ELF-mpc5xxx                   += interrupt
#ELF-mpc8xx                    += test_burst timer
#ELF-mpc8260                   += mem_to_mem_idma2intr
#ELF-ppc                       += sched
#ELF-oxc                       += eepro100_eeprom

#
# Some versions of make do not handle trailing white spaces properly;
# leading to build failures. The problem was found with GNU Make 3.80.
# Using 'strip' as a workaround for the problem.
#
ELF := $(strip $(ELF-y) $(ELF-$(ARCH)) $(ELF-$(BOARD)) $(ELF-$(CPU)))

SREC := $(addsuffix .srec,$(ELF))
BIN  := $(addsuffix .bin,$(ELF))
DIS  := $(addsuffix .dis,$(ELF))

SOBJS	:= temp_target_array.o
SOBJS	+= start64.o cache64.o 
COBJS	:= dvrmain.o util.o flashdev_n.o flashdev_s.o flashdev_e.o rtkemmc.o strlen.o strstr.o strtoul.o ctype.o mcp.o otp.o timer.o cache.o BootPartition_wrapper.o 
COBJS   += printf.o TinyStdio/tinystdio.o
#LIB	= $(obj)libstubs.o
LIB	= $(obj)

LIBAOBJS-$(ARCH)     := 
LIBAOBJS-$(CPU)      :=
LIBAOBJS := $(LIBAOBJS-$(ARCH)) $(LIBAOBJS-$(CPU))

#LIBCOBJS = stubs.o 
LIBCOBJS = 

LIBOBJS	= $(addprefix $(obj),$(LIBAOBJS) $(LIBCOBJS))

SRCS	:= $(COBJS:.o=.c) $(LIBCOBJS:.o=.c) $(LIBAOBJS:.o=.S) $(SOBJS:.o=.S)
OBJS	:= $(addprefix $(obj),$(COBJS))
SSOBJS	:= $(addprefix $(obj),$(SOBJS))

gcclibdir := $(shell dirname `$(CC) -print-libgcc-file-name`)

CPPFLAGS += -I.. -I$(INCLUDE_DIR) -I$(TOP_DIR)/include
INCDIRS =  -I$(TOP_DIR)/../../include -I.. -I$(INCLUDE_DIR) -I$(ROOT_DIR)

# We don't want gcc reordering functions if possible.  This ensures that an
# application's entry point will be the first function in the application's
# source file.
#CFLAGS_NTR := $(call cc-option,-fno-toplevel-reorder)
#CFLAGS += $(CFLAGS_NTR) -I$(INCLUDE_DIR)
#CFLAGS = -g -Os -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv7-a  -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security  -fno-toplevel-reorder 
CFLAGS = -g -Os -fno-common -ffixed-r8 -D__KERNEL__ -fno-builtin -ffreestanding -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__  -march=armv8-a -D__EL__ -D__ARM_ARCH_8A__
#CFLAGS += -msoft-float -marm -mabi=aapcs-linux -mno-thumb-interwork

ifeq ($(Config_Boot1_Rescue),TRUE)
    CFLAGS += -DBOOT1_RESCUE
endif

ifeq ($(Board_CPU), RTD1295)
    CFLAGS += -DCONFIG_RTD1295
endif

CFLAGS += $(INCDIRS)
all:	clean configconv hw_setting b2a get_config $(OBJS) $(SSOBJS) $(LIB) $(ELF) $(SREC) $(BIN)

clean:
	-rm -f $(TARGET_EXE) *.o *.reverse temp_target_array.h *.bin *.map *.dis *.srec *.aes *.a
	#-rm -rf $(PACKAGE_DIR) $(SIGNATURE_TARGET).reverse
	-rm -rf $(PACKAGE_DIR) $(SIGNATURE_TARGET)
	-rm -rf $(TOP_DIR)/$(BIND_FOLDER)
	-rm $(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL)
	-rm -rf $(TOP_DIR)/Bind
	-rm -rf $(TOP_DIR)/install_a
	-rm -f $(TOP_DIR)/enc.dat
	-rm -f $(TOP_DIR)/image/realtek_ntsc1.bmp.dat
	-rm -f $(TOP_DIR)/image/realtek_ntsc1.bmp.inf
	-rm -f $(TOP_DIR)/image/rsa_key_2048.fw.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key_2048.fw.pem.bin
	-rm -f $(TOP_DIR)/image/rsa_key_2048.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key_2048.tee.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key_2048.pem.bin
	-rm -f $(TOP_DIR)/image/rsa_key_2048.pem.text
	-rm -f $(TOP_DIR)/image/rsa_key_2048.tee.pem.bin
	-rm -f $(TOP_DIR)/image/rsa_key_2048.tee.pem.text
	-rm -f $(TOP_DIR)/include/project_config_f.h
	-rm -f $(TOP_DIR)/tools/RtSSL/RtSSL
	-rm -f $(TOP_DIR)/tools/hw_setting_maker/generate_config
	echo $(TOP_DIR)
#########################################################################
$(LIB):	$(obj).depend $(LIBOBJS)
	$(call cmd_link_o_target, $(LIBOBJS))

#$(ELF):
#$(obj)%:	$(obj)%.o $(LIB) 
#		$(LD) $(LDFLAGS) -g -Ttext $(CONFIG_STANDALONE_LOAD_ADDR) \
#			-o $@ -e $(SYM_PREFIX)$(notdir $(<:.o=)) $< $(LIB) \
#			-L$(gcclibdir) -lgcc

$(ELF): 	$(LIB) 
		$(LD) $(LDFLAGS) -g -Ttext $(LOAD_ADDR) \
			-o $@ -e start $(SOBJS) $(COBJS) $(LIB) \
			-L$(gcclibdir) -lgcc -Map dvrboot.map

$(SREC):
$(obj)%.srec:	$(obj)%
		$(OBJCOPY) -O srec $< $@ 2>/dev/null

$(BIN):
$(obj)%.bin:	$(obj)%
		$(OBJCOPY) -O binary $< $@ 2>/dev/null
		$(OBJDUMP) -DS $<  >$(DIS)
		# pack related binary files for install_a
		@rm -rf install_a
		@mkdir -p install_a
		#@cp -rf $(HW_SETTING_TARGET_INVERSE) install_a/hw_setting.bin
		cat $(HW_SETTING_HEADER_FINAL) $(HW_SETTING_TARGET_FINAL) > install_a/hw_setting.bin		
		cat $(UBOOT_FINAL) > install_a/lk.bin
ifeq ($(Config_FSBL), TRUE)
		cat $(FSBL_FINAL) > install_a/fsbl.bin
endif
ifeq ($(Config_FSBL_VM), TRUE)
		cat $(FSBL_VM_FINAL) > install_a/fsbl_vm.bin
endif
ifeq ($(Config_FSBL_OS), TRUE)
		cat $(FSBL_OS_FINAL) > install_a/tee_enc.bin
endif
ifeq ($(Config_BL31), TRUE)
		cat $(BL31_FINAL) > install_a/bl31_enc.bin
endif
ifeq ($(Config_Secure_Improve), TRUE)
		cat $(RSA_BIN_FW_FINAL) > install_a/rsa_bin_fw.bin
		cat $(RSA_BIN_TEE_FINAL) > install_a/rsa_bin_tee.bin
endif
		@cd install_a/; tar cf ../../../bootloader_lk.tar *
		#@rm -rf install_a/

#########################################################################


# defines $(obj).depend target
#include $(SRCTREE)/rules.mk

#sinclude $(obj).depend

OBJ_DIR=.
ASM=$(CC)
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c  $< -o $@

$(OBJ_DIR)/%.o: %.S
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.s
	$(ASM) $(ASFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

#########################################################################

configconv:
	$(PERL) $(SCRIPT_DIR)/$(CONFIGCONV_SCRIPT) \
		$(INCLUDE_DIR)/project_config_f.h \
		$(TOP_DIR)/inc/$(PRJ).inc \
		$(RSA_INF_PATH) \
		$(RSA_INF0_PATH)

$(RTSSL_EXE):
	cd $(RTSSL_DIR);\
	make LIB_PATH=/usr/lib64 STATIC_LINK=N
		
rsa_key: $(RTSSL_EXE)
	chmod +x reverse.pl
	chmod +x bin2ascii
	chmod +x $(RTSSL_EXE)
	chmod +x $(STR2BIN)
	chmod +x $(REVERSE_PL)
	chmod +x $(BINARY_TO_ASCII)
	if [ $(Config_Secure_RSA_Key_File) ]; then \
		$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY_PATH)` > $(RSA_BIN_PATH);\
		$(REVERSE_PL) $(RSA_BIN_PATH) > $(RSA_BIN_PATH).rev; \
	else \
		echo "Config_Secure_RSA_Key_File not defined in $(PRJ).inc"; \
	fi
	if [ $(Config_Secure_RSA_Key_FW_File) ]; then \
		$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY_FW_PATH)` > $(RSA_BIN_FW_PATH);\
		$(REVERSE_PL) $(RSA_BIN_FW_PATH) > $(RSA_BIN_FW_PATH).rev; \
	else \
		echo "Config_Secure_RSA_Key_FW_File not defined in $(PRJ).inc"; \
	fi
	if [ $(Config_Secure_RSA_Key_TEE_File) ]; then \
		$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY_TEE_PATH)` > $(RSA_BIN_TEE_PATH);\
		$(REVERSE_PL) $(RSA_BIN_TEE_PATH) > $(RSA_BIN_TEE_PATH).rev; \
	else \
		echo "Config_Secure_RSA_Key_File not defined in $(PRJ).inc"; \
	fi

	
$(HW_SETTING_MAKER_AP):
	$(CD) $(HW_SETTING_MAKER_DIR);\
	make;

$(BINDALLBIN_UTIL):
	$(CD) $(BINDALLBIN_MAKER_DIR);\
	make clean;make;
		
hw_setting: $(HW_SETTING_MAKER_AP) $(BINDALLBIN_UTIL)
	#bind stuff
	@mkdir $(BIND_FOLDER);
	@cp $(RESET_TARGET) $(BIND_FOLDER)/arm_romcode.bin;
	@cp $(MIPS_RESET_TARGET) $(BIND_FOLDER)/mips_romcode.bin;
	$(CD) $(HW_SETTING_MAKER_DIR);\
	./$(HW_SETTING_MAKER_AP) $(HW_SETTING_TARGET_RAW_FILE) $(HW_SETTING_DIR)/$(Board_HWSETTING).bin

$(SHA_EXE):
	cd $(SHA_DIR);\
	rm do_sha256;\
	make

$(NF_PROFILER_EXE):
	cd $(NF_PROFILER_DIR);\
	make clean; make;


b2a: rsa_key merge_hwsetting_target merge_bootcode_target target_encrypt fsbl fsbl_vm fsbl_os bl31 secure_improve $(SHA_EXE) $(NF_PROFILER_EXE)
	# generate header must prior to real bind job
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl secure header $(UBOOT_ENC)
	# modify for HEADER SHA256 
	$(RTSSL_EXE) dgst -sha256 -g -i $(HW_SETTING_HEADER_FINAL) -o $(HW_SETTING_HEADER_FINAL_DIGEST)
	cat $(HW_SETTING_HEADER_FINAL) > $(HW_SETTING_HEADER_64B)
	cat $(HW_SETTING_HEADER_64B) $(HW_SETTING_HEADER_FINAL_DIGEST) > $(HW_SETTING_HEADER_FINAL)
	$(OBFUSE_H) $(RTSSL_EXE) 97 $(AES_MODULE_ID_PATH) $(AES_MODULE_ID_PATH) $(AES_SCK_PATH) $(AES_VENDOR_ID_PATH) $(HW_SETTING_HEADER_FINAL) $(HW_SETTING_HEADER_FINAL_ENC)      
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl secure $(UBOOT_ENC)
	cat $(HW_SETTING_HEADER_FINAL) > $(HW_SETTING_HEADER_FINAL).dec
	cat $(HW_SETTING_HEADER_FINAL_ENC) > $(HW_SETTING_HEADER_FINAL)
	$(BIN2HEX) $(BIND_FOLDER)/bind.bin $(BIND_FOLDER)/bind.bin.hex
	$(BIN2HEX_EMMC) $(BIND_FOLDER)/emmc.bind.bin $(BIND_FOLDER)/emmc_bind.bin.hex
	./bin2ascii $(BIN_ARGS) > temp_target_array.h

$(INVERSE):
	cc inverse.c -o $(INVERSE);\
	chmod +x $(INVERSE)

merge_hwsetting_target: $(SHA_EXE)
	$(SHA_EXE) $(HW_SETTING_TARGET) $(HW_SETTING_PADDING_FINAL) $(HW_SETTING_DIGEST)
	cat $(HW_SETTING_TARGET) $(HW_SETTING_PADDING_FINAL) > $(HW_SETTING_TARGET_PADDING)
	$(call hwrsa-sign-npinv64, $(RSA_KEY_PATH), $(HW_SETTING_DIGEST), $(HW_SETTING_DIGEST_ENC))
	$(OBFUSE_H) $(RTSSL_EXE) 97 $(AES_MODULE_ID_PATH) $(AES_MODULE_ID_PATH) $(AES_SCK_PATH) $(AES_VENDOR_ID_PATH) $(HW_SETTING_TARGET_PADDING) $(HW_SETTING_TARGET_ENC) 
	cat $(HW_SETTING_TARGET_ENC) $(HW_SETTING_DIGEST_ENC) > $(HW_SETTING_TARGET_ENC_ALL)
	cat $(HW_SETTING_TARGET_ENC_ALL) > $(HW_SETTING_TARGET_FINAL)

merge_bootcode_target: $(INVERSE)
	# copy u-boot.bin to local, bin2ascii need to know its size in output file 
ifeq ($(Config_Uboot_Sim_Mode), TRUE)
	cp $(BOOTCODE_UBOOT_TARGET_SIM) ./u-boot.bin
	cat $(BOOTCODE_UBOOT_TARGET_SIM) > $(BOOTCODE_BOOT_TARGET)
else
	cp $(BOOTCODE_UBOOT_TARGET) .
	cat $(BOOTCODE_UBOOT_TARGET) > $(BOOTCODE_BOOT_TARGET)
endif

target_encrypt: $(SHA_EXE)
	$(SHA_EXE) $(BOOTCODE_BOOT_TARGET) $(BOOTCODE_BOOT_PADDING_FINAL) $(BOOTCODE_BOOT_DIGEST_TARGET)
	cat $(BOOTCODE_BOOT_TARGET) $(BOOTCODE_BOOT_PADDING_FINAL) > $(BOOTCODE_BOOT_TARGET_PADDING)
ifeq ($(Config_Secure_Improve), TRUE)
	$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(BOOTCODE_BOOT_TARGET_PADDING) -o $(BOOTCODE_BOOT_HASH_TARGET).aes
	# for b2a
	cat $(BOOTCODE_BOOT_HASH_TARGET).aes > $(BOOTCODE_BOOT_HASH_TARGET2)
	$(call hwrsa-sign-npinv64, $(RSA_KEY_FW_PATH), $(BOOTCODE_BOOT_DIGEST_TARGET), $(SIGNATURE_TARGET))
	cat $(BOOTCODE_BOOT_HASH_TARGET2) $(SIGNATURE_TARGET) > $(UBOOT_FINAL)
else
	# for b2a
	cp $(BOOTCODE_BOOT_TARGET_PADDING) $(BOOTCODE_BOOT_HASH_TARGET2)
	cp $(BOOTCODE_BOOT_DIGEST_TARGET) $(SIGNATURE_TARGET)
	cat $(BOOTCODE_BOOT_TARGET_PADDING) $(BOOTCODE_BOOT_DIGEST_TARGET) > $(UBOOT_FINAL)
endif
	
fsbl:
ifeq ($(Config_FSBL), TRUE)
	cp $(FSBL_TARGET) $(FSBL_FINAL)
endif

fsbl_vm:
ifeq ($(Config_FSBL_VM), TRUE)
	cp $(FSBL_VM_TARGET) $(FSBL_VM_FINAL)
endif

fsbl_os:
ifeq ($(Config_FSBL_OS), TRUE)
	cp $(FSBL_OS_TARGET) $(FSBL_OS_FINAL)
endif

bl31:
ifeq ($(Config_BL31), TRUE)
	cp $(BL31_TARGET) $(BL31_FINAL)
endif

secure_improve:
ifeq ($(Config_Secure_Improve), TRUE)
	# rsa key fw
	$(SHA_EXE) $(RSA_BIN_FW_TARGET) $(RSA_BIN_FW_PADDING_FINAL) $(RSA_BIN_FW_DIGEST_TARGET)
	cat $(RSA_BIN_FW_TARGET) $(RSA_BIN_FW_PADDING_FINAL)  > $(RSA_BIN_FW_TARGET_PADDING)
	cp $(RSA_BIN_FW_TARGET_PADDING) $(RSA_BIN_FW_HASH_TARGET)
	$(call hwrsa-sign-npinv64, $(RSA_KEY_PATH), $(RSA_BIN_FW_DIGEST_TARGET), $(RSA_BIN_FW_SIGNATURE_TARGET))
	$(OBFUSE_H) $(RTSSL_EXE) 97 $(AES_MODULE_ID_PATH) $(AES_MODULE_ID_PATH) $(AES_SCK_PATH) $(AES_VENDOR_ID_PATH) $(RSA_BIN_FW_HASH_TARGET) $(RSA_BIN_FW_HASH_TARGET_AES) 
	cat $(RSA_BIN_FW_HASH_TARGET_AES) $(RSA_BIN_FW_SIGNATURE_TARGET) > $(RSA_BIN_FW_FINAL)
	
	# rsa key tee
	$(SHA_EXE) $(RSA_BIN_TEE_TARGET) $(RSA_BIN_TEE_PADDING_FINAL) $(RSA_BIN_TEE_DIGEST_TARGET)
	cat $(RSA_BIN_TEE_TARGET) $(RSA_BIN_TEE_PADDING_FINAL)  > $(RSA_BIN_TEE_TARGET_PADDING)
	cp $(RSA_BIN_TEE_TARGET_PADDING) $(RSA_BIN_TEE_HASH_TARGET)
	$(call hwrsa-sign-npinv64, $(RSA_KEY_PATH), $(RSA_BIN_TEE_DIGEST_TARGET), $(RSA_BIN_TEE_SIGNATURE_TARGET))
	$(OBFUSE_H) $(RTSSL_EXE) 97 $(AES_MODULE_ID_PATH) $(AES_MODULE_ID_PATH) $(AES_SCK_PATH) $(AES_VENDOR_ID_PATH) $(RSA_BIN_TEE_HASH_TARGET) $(RSA_BIN_TEE_HASH_TARGET_AES) 
	cat $(RSA_BIN_TEE_HASH_TARGET_AES) $(RSA_BIN_TEE_SIGNATURE_TARGET) > $(RSA_BIN_TEE_FINAL)
endif
	
get_config:
	$(SED) -i 's/Config_FLASH_TYPE.*/$(FLASH_TYPE)/g' $(INCLUDE_DIR)/project_config_f.h;	
