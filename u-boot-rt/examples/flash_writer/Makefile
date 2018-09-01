

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

# ********************************************************************
# u-boot's makefile will pass the PRJ setting to here
# ********************************************************************
#PRJ = 6227_c0000_b0000
#PRJ = 6227_c0000_b0000_fpga_emmc_DCAS_secure_enc
#PRJ = 6227_c0000_b0000_fpga_emmc
#PRJ = 6227_c0000_b0000_fpga_emmc_tv005_l4300
#PRJ = 6227_c0000_b0000_fpga_emmc_RTK_secure_enc
#PRJ = 6227_c0000_b0000_fpga_nand_DCAS_secure_enc
#PRJ = 6227_c0000_b0000_fpga_nand
#PRJ = 6227_c0000_b0000_fpga_nand_random
#PRJ = 6227_c0000_b0000_fpga_nand_RTK_secure_enc
#PRJ = 6227_c0000_b0000_fpga_spi_DCAS_secure_enc
#PRJ = 6227_c0000_b0000_fpga_spi
#PRJ = 6227_c0000_b0000_fpga_spi_RTK_secure_enc
include $(PRJ).inc
LOAD_ADDR = 0x01500000

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

VERSION = $(Param_companyID).$(Param_boardID).$(Param_version)
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
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern.pl
HW_SETTING_DIR       = $(IMAGE_DIR)/hw_setting
HW_SETTING_MAKER_DIR = $(TOOLS_DIR)/hw_setting_maker
BINDALLBIN_MAKER_DIR = $(TOOLS_DIR)/bindAllBins

SHA_DIR    = $(TOOLS_DIR)/do_sha256
RTSSL_DIR  = $(TOOLS_DIR)/RtSSL
OBFUSE_DIR  = $(TOOLS_DIR)/obfuse
OPENSSL    = openssl
SCRIPT_DIR = $(TOOLS_DIR)/script
CRC32_DIR  = $(TOOLS_DIR)/crc32

HW_SETTING_TARGET = $(HW_SETTING_DIR)/$(Board_HWSETTING).bin
HW_SETTING_TARGET_RAW_FILE = $(HW_SETTING_DIR)/$(CHIP_ID)/$(CUSTOMER_ID)/$(CHIP_TYPE)/$(Board_HWSETTING).config
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
HW_SETTING_HEADER_FINAL_ENC = $(BIND_FOLDER)/hwsetting_header_enc.bin
UBOOT_FINAL = $(BIND_FOLDER)/uboot.bin
UBOOT2_FINAL = $(BIND_FOLDER)/uboot2.bin
RESCUE_FINAL = $(BIND_FOLDER)/rescue.bin
FSBL_FINAL = $(BIND_FOLDER)/fsbl.bin
FSBL_OS_FINAL = $(BIND_FOLDER)/fsbl_os.bin
BL31_FINAL = $(BIND_FOLDER)/bl31.bin
RSA_BIN_FW_FINAL = $(BIND_FOLDER)/rsa_bin_fw.bin
RSA_BIN_TEE_FINAL = $(BIND_FOLDER)/rsa_bin_tee.bin
HW_SETTING_PADDING_FINAL = $(BIND_FOLDER)/hwsetting_padding.bin
BOOTCODE_BOOT_PADDING_FINAL = $(BIND_FOLDER)/uboot_padding.bin
LINUX_RESCUE_PADDING_FINAL = $(BIND_FOLDER)/rescue_padding.bin
FSBL_PADDING_FINAL = $(BIND_FOLDER)/fsbl_padding.bin
FSBL_OS_PADDING_FINAL = $(BIND_FOLDER)/fsbl_os_padding.bin
BL31_PADDING_FINAL = $(BIND_FOLDER)/bl31_padding.bin
RSA_BIN_FW_PADDING_FINAL = $(BIND_FOLDER)/rsa_bin_fw_padding.bin
RSA_BIN_TEE_PADDING_FINAL = $(BIND_FOLDER)/rsa_bin_tee_padding.bin
OBFUSE  = $(OBFUSE_DIR)/obfuse
ifeq ($(Config_Uboot_Enc), TRUE)
UBOOT_ENC	     = boot_enc
else
UBOOT_ENC	     = 
endif
SIM_MODE	     = 
TRUE_SYB             = TRUE
ifeq ($(TRUE_SYB),$(filter $(TRUE_SYB),$(Config_Simulation_Mode) $(Config_USB_MP_Mode))) 
#ifeq ($(Config_Simulation_Mode), TRUE) 
SIM_MODE             = simulation
endif
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

#BIN_ARGS            = "hw_setting="$(HW_SETTING_TARGET_INVERSE)
ifeq ($(Config_Secure_Key), TRUE)
BIN_ARGS	    = "hw_setting="$(HW_SETTING_TARGET_ENC_ALL)
else
ifeq ($(Config_USB_MP_Mode), FALSE)
BIN_ARGS            = "hw_setting="$(HW_SETTING_TARGET_ALL)
else
BIN_ARGS            = "hw_setting="$(HW_SETTING_TARGET_ENC_ALL)
endif
endif

ifeq ($(WATCHDOG_CONFIG), "WATCHDOG_ENABLE")
Board_WATCHDOG = RTD299X.watchdog_enable
else
Board_WATCHDOG = RTD299X.watchdog_disable
endif

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

ifeq ($(strip $(Config_NOR_BOOT_NAND)), TRUE)
    ROM2_IN_NOR = 1
else
    ROM2_IN_NOR = 0
endif

ifeq ($(strip $(Logo_Source)), FLASH)
    LOGO_TARGET = $(IMAGE_DIR)/$(Logo_File_Name).dat
    LOGO_EXIST = 1

    ifeq ($(strip $(Logo_Type)), NTSC)
        LOGO_STR = _ntsc
    endif

    ifeq ($(strip $(Logo_Type)), PAL)
        LOGO_STR = _pal
    endif

    ifeq ($(strip $(Logo_Type)), 1080p50)
        LOGO_STR = _1080p50
    endif

    ifeq ($(strip $(Logo_Type)), 1080p60)
        LOGO_STR = _1080p60
    endif

    BIN_ARGS += "logo="$(LOGO_TARGET)
else
    LOGO_EXIST = 0
endif

ifeq ($(strip $(Logo2_Source)), FLASH)
    LOGO2_TARGET = $(IMAGE_DIR)/$(Logo2_File_Name).dat
    LOGO2_EXIST = 1
    
    ifeq ($(strip $(Logo2_Type)), NTSC)
        LOGO2_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo2_Type)), PAL)
        LOGO2_STR = _pal
    endif
    
    ifeq ($(strip $(Logo2_Type)), 1080p50)
        LOGO2_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo2_Type)), 1080p60)
        LOGO2_STR = _1080p60
    endif
    
    BIN_ARGS += "logo2="$(LOGO2_TARGET)
else
    LOGO2_EXIST = 0
endif

ifeq ($(strip $(Logo3_Source)), FLASH)
    LOGO3_TARGET = $(IMAGE_DIR)/$(Logo3_File_Name).dat
    LOGO3_EXIST = 1
    
    ifeq ($(strip $(Logo3_Type)), NTSC)
        LOGO3_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo3_Type)), PAL)
        LOGO3_STR = _pal
    endif
    
    ifeq ($(strip $(Logo3_Type)), 1080p50)
        LOGO3_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo3_Type)), 1080p60)
        LOGO3_STR = _1080p60
    endif
    
    BIN_ARGS += "logo3="$(LOGO3_TARGET)
else
    LOGO3_EXIST = 0
endif

ifeq ($(strip $(Logo4_Source)), FLASH)
    LOGO4_TARGET = $(IMAGE_DIR)/$(Logo4_File_Name).dat
    LOGO4_EXIST = 1

    ifeq ($(strip $(Logo4_Type)), NTSC)
        LOGO4_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo4_Type)), PAL)
        LOGO4_STR = _pal
    endif
    
    ifeq ($(strip $(Logo4_Type)), 1080p50)
        LOGO4_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo4_Type)), 1080p60)
        LOGO4_STR = _1080p60
    endif
    
    BIN_ARGS += "logo4="$(LOGO4_TARGET)
else
    LOGO4_EXIST = 0
endif

ifeq ($(strip $(Logo5_Source)), FLASH)
    LOGO5_TARGET = $(IMAGE_DIR)/$(Logo5_File_Name).dat
    LOGO5_EXIST = 1
    
    ifeq ($(strip $(Logo5_Type)), NTSC)
        LOGO5_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo5_Type)), PAL)
        LOGO5_STR = _pal
    endif
    
    ifeq ($(strip $(Logo5_Type)), 1080p50)
        LOGO5_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo5_Type)), 1080p60)
        LOGO5_STR = _1080p60
    endif
    
    BIN_ARGS += "logo5="$(LOGO5_TARGET)
else
    LOGO5_EXIST = 0
endif

ifeq ($(strip $(Logo6_Source)), FLASH)
    LOGO6_TARGET = $(IMAGE_DIR)/$(Logo6_File_Name).dat
    LOGO6_EXIST = 1
    
    ifeq ($(strip $(Logo6_Type)), NTSC)
        LOGO6_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo6_Type)), PAL)
        LOGO6_STR = _pal
    endif
    
    ifeq ($(strip $(Logo6_Type)), 1080p50)
        LOGO6_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo6_Type)), 1080p60)
        LOGO6_STR = _1080p60
    endif
    
    BIN_ARGS += "logo6="$(LOGO6_TARGET)
else
    LOGO6_EXIST = 0
endif

ifeq ($(strip $(Logo7_Source)), FLASH)
    LOGO7_TARGET = $(IMAGE_DIR)/$(Logo7_File_Name).dat
    LOGO7_EXIST = 1
    
    ifeq ($(strip $(Logo7_Type)), NTSC)
        LOGO7_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo7_Type)), PAL)
        LOGO7_STR = _pal
    endif
    
    ifeq ($(strip $(Logo7_Type)), 1080p50)
        LOGO7_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo7_Type)), 1080p60)
        LOGO7_STR = _1080p60
    endif
    
    BIN_ARGS += "logo7="$(LOGO7_TARGET)
else
    LOGO7_EXIST = 0
endif

ifeq ($(strip $(Logo8_Source)), FLASH)
    LOGO8_TARGET = $(IMAGE_DIR)/$(Logo8_File_Name).dat
    LOGO8_EXIST = 1
    
    ifeq ($(strip $(Logo8_Type)), NTSC)
        LOGO8_STR = _ntsc
    endif
    
    ifeq ($(strip $(Logo8_Type)), PAL)
        LOGO8_STR = _pal
    endif
    
    ifeq ($(strip $(Logo8_Type)), 1080p50)
        LOGO8_STR = _1080p50
    endif
    
    ifeq ($(strip $(Logo8_Type)), 1080p60)
        LOGO8_STR = _1080p60
    endif
    
    BIN_ARGS += "logo8="$(LOGO8_TARGET)
else
    LOGO8_EXIST = 0
endif

ifeq ($(strip $(secure)), on)
    SECURE_PACK = 1
else
    SECURE_PACK = 0
endif

ifeq ($(strip $(test_secure)), on)
    TEST_SECURE_PACK= 1
else
    TEST_SECURE_PACK= 0
endif

# burn NAND flash in FPGA
ifeq ($(strip $(flash_type)), nand)
    CFLAGS += -D_FPGA_NAND_
endif


#####################################################
###Check the different types of chip to set bootimage
ifeq ($(CHIP_TYPE), 0002)
	ifeq ($(FLASH_TYPE), RTK_FLASH_SPI)
        BOOT_IMAGE_FOLDER = B00_spi_bootimage
	else ifneq ($(Config_BL31), TRUE)
        BOOT_IMAGE_FOLDER = B00_woTEE_bootimage
	else
        BOOT_IMAGE_FOLDER = B00_bootimage
	endif
else
	ifeq ($(CHIP_TYPE), 1001)
        BOOT_IMAGE_FOLDER = 1293_bootimage
	else
        BOOT_IMAGE_FOLDER = A01_bootimage
	endif
endif
#####################################################


PRJ_CONFIG_TARGET               = $(PRJ_INC_DIR)/project_config.h
#ifeq ($(Config_SPI_BOOT_FISRT), NAND)
#RESET_TARGET                    = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/romcode-new-spi-first-nand-2nd.bin
#endif
#ifeq ($(Config_SPI_BOOT_FISRT), EMMC)
#RESET_TARGET                    = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/romcode-new-emmc-first.bin
#endif
#ifeq ($(Config_SPI_BOOT_FISRT), SPI)
#RESET_TARGET                    = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/romcode-new-spi-first.bin
#endif
RESET_TARGET                    = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/bootmon-new.bin
MIPS_RESET_TARGET               = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/mips-bootmon-new.bin
ROM2_RESET_TARGET               = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/bootmon-new.bin
JUMPER_TARGET			= $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/jumper-00.00.bin
UBOOT64_TARGET			= $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/u-boot64.bin
ARM_REDIR_TARGET                = $(TOP_DIR)/../redirect/redirect_packed.bin

ifeq ($(strip $(Config_SPI_BOOTCODE2)), TRUE)
    BOOTCODE_UBOOT_TARGET       = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/uboot_textbase_0x00020000.bin
else
    BOOTCODE_UBOOT_TARGET       = $(TOP_DIR)/../../u-boot.bin
endif

ifdef BOOTCODE_IS_LK
    BOOTCODE_UBOOT_TARGET       = $(BOOTCODE_LK_PATH)
endif

BOOTCODE_UBOOT_TARGET_SIM       = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/uboot_simulation.bin
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

BOOTCODE3_UBOOT_TARGET          = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/uboot_textbase_0x00020000.bin
BOOTCODE3_BOOT_TARGET           = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed.bin
BOOTCODE3_BOOT_HASH_TARGET      = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed_hash.bin
BOOTCODE3_BOOT_HASH_TARGET_AES  = $(TOP_DIR)/bootpart3_uboot_plus_redirect_packed_hash.bin.aes
BOOTCODE3_BOOT_PADDING_TARGET   = $(TOP_DIR)/bootpart3_uboot_sha256_padding.bin
BOOTCODE3_BOOT_DIGEST_TARGET    = $(TOP_DIR)/bootpart3_uboot_sha256_digest.bin
BOOTCODE3_BOOT_SIGNATURE_TARGET = bootcode3_signature.bin

FSBL_TARGET            = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/$(Config_FSBL_File_Name)
FSBL_DIGEST_TARGET     = $(TOP_DIR)/fsbl_sha256_digest.bin
FSBL_SIGNATURE_TARGET  = $(TOP_DIR)/fsbl_signature_digest.bin
FSBL_TARGET_PADDING    = $(TOP_DIR)/fsbl_padding.bin
FSBL_HASH_TARGET       = $(TOP_DIR)/fsbl_hash.bin
FSBL_HASH_TARGET_AES   = $(TOP_DIR)/fsbl_hash.bin.aes

FSBL_OS_TARGET            = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/$(Config_FSBL_OS_File_Name)
FSBL_OS_DIGEST_TARGET     = $(TOP_DIR)/fsbl_os_sha256_digest.bin
FSBL_OS_SIGNATURE_TARGET  = $(TOP_DIR)/fsbl_os_signature_digest.bin
FSBL_OS_TARGET_PADDING    = $(TOP_DIR)/fsbl_os_padding.bin
FSBL_OS_HASH_TARGET       = $(TOP_DIR)/fsbl_os_hash.bin
FSBL_OS_HASH_TARGET_AES   = $(TOP_DIR)/fsbl_os_hash.bin.aes

BL31_TARGET            = $(TOP_DIR)/bootimage/$(BOOT_IMAGE_FOLDER)/$(Config_BL31_File_Name)
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

LINUX_RESCUE_TARGET           = $(IMAGE_DIR)/$(Rescue_File_Name)
LINUX_RESCUE_TARGET_PADDING   = $(TOP_DIR)/$(Rescue_File_Name)_sha256_padding.bin
LINUX_RESCUE_TARGET_ALL_PADDING  = $(TOP_DIR)/$(Rescue_File_Name)_sha256_padding_all.bin
LINUX_RESCUE_DIGEST_TARGET    = $(TOP_DIR)/$(Rescue_File_Name)_sha256_digest.bin
LINUX_RESCUE_HASH_TARGET      = $(TOP_DIR)/$(Rescue_File_Name)_hash_target.bin
LINUX_RESCUE_HASH_TARGET_ENC  = $(TOP_DIR)/$(Rescue_File_Name)_hash_target_enc.bin
LINUX_RESCUE_SIGNATURE_TARGET = $(Rescue_File_Name)_signature.bin
LINUX_RESCUE_HASH_TARGET_AES  = $(TOP_DIR)/$(Rescue_File_Name)_hash_target.aes

ifeq ($(ENV), $(CYGWIN_ENV))
	LOGO_CHANGER = $(LOGO_CHANGER_DIR)/logo_changer.exe
	HW_SETTING_MAKER_AP	= generate_config.exe
	RTSSL_EXE = $(RTSSL_DIR)/RtSSL.exe
	SHA_EXE = $(SHA_DIR)/do_sha256.exe
	INVERSE = inverse.exe
endif

ifeq ($(ENV), $(LINUX_ENV))
	LOGO_CHANGER = $(LOGO_CHANGER_DIR)/logo_changer
	HW_SETTING_MAKER_AP	= generate_config
	RTSSL_EXE = $(RTSSL_DIR)/RtSSL
	SHA_EXE = $(SHA_DIR)/do_sha256
	INVERSE = inverse
endif

PACKAGE_PRJ_CONFIG = $(PACKAGE_DIR)/project_config.h
PACKAGE_HWSETTING  = $(PACKAGE_DIR)/hwsetting.bin
PACKAGE_BOOTCODE   = $(PACKAGE_DIR)/boot_target.bin
PACKAGE_LOGO       = $(PACKAGE_DIR)/logo.bin
PACKAGE_LOGO2      = $(PACKAGE_DIR)/logo2.bin
PACKAGE_LOGO3      = $(PACKAGE_DIR)/logo3.bin
PACKAGE_LOGO4      = $(PACKAGE_DIR)/logo4.bin
PACKAGE_LOGO5      = $(PACKAGE_DIR)/logo5.bin
PACKAGE_LOGO6      = $(PACKAGE_DIR)/logo6.bin
PACKAGE_LOGO7      = $(PACKAGE_DIR)/logo7.bin
PACKAGE_LOGO8      = $(PACKAGE_DIR)/logo8.bin
PACKAGE_LINUX_BK   = $(PACKAGE_DIR)/rescue.bin

BIN_ARGS += "resetrom="$(RESET_TARGET)
BIN_ARGS += "mips_resetrom="$(MIPS_RESET_TARGET)
BIN_ARGS += "hasharray="$(BOOTCODE_BOOT_HASH_TARGET2)
ifeq ($(Config_Uboot64_Mode), TRUE)
BIN_ARGS += "hasharray64="$(UBOOT64_TARGET)
endif
#BIN_ARGS += "signature="$(SIGNATURE_TARGET).reverse
ifeq ($(Config_Simulation_Mode), TRUE)
BIN_ARGS += "signature="$(BOOTCODE_BOOT_DIGEST_TARGET)
else
BIN_ARGS += "signature="$(SIGNATURE_TARGET)
endif
ifeq ($(strip $(Config_SPI_BOOTCODE2)), TRUE)
    ifeq ($(Config_Secure_Key), TRUE)
		BIN_ARGS += "bootcode2_boot_hasharray="$(BOOTCODE2_BOOT_HASH_TARGET_AES)
    else
		BIN_ARGS += "bootcode2_boot_hasharray="$(BOOTCODE2_BOOT_HASH_TARGET)
    endif	
endif
ifeq ($(strip $(Config_SPI_BOOTCODE3)), TRUE)
    ifeq ($(Config_Secure_Key), TRUE)
    	BIN_ARGS += "bootcode3_boot_hasharray="$(BOOTCODE3_BOOT_HASH_TARGET_AES)
    else
    	BIN_ARGS += "bootcode3_boot_hasharray="$(BOOTCODE3_BOOT_HASH_TARGET)
    endif
endif

ifeq ($(strip $(Rescue_Source)), FLASH)
    RESCUE_STR              = _rsq
    ifeq ($(Config_Secure_Key), TRUE)
        BIN_ARGS           += "linux_rescue="$(LINUX_RESCUE_HASH_TARGET_AES)
    else
        BIN_ARGS           += "linux_rescue="$(LINUX_RESCUE_HASH_TARGET)
    endif
    ifeq ($(Config_Simulation_Mode), TRUE)
    BIN_ARGS           += "linux_rescue_signature="$(LINUX_RESCUE_DIGEST_TARGET)
    else
    BIN_ARGS           += "linux_rescue_signature="$(LINUX_RESCUE_SIGNATURE_TARGET)
    endif
    ifeq ($(Config_USB_MP_Mode), TRUE)
    BIN_ARGS           += "linux_rescue="$(LINUX_RESCUE_HASH_TARGET_AES)
    BIN_ARGS           += "linux_rescue_signature="$(LINUX_RESCUE_SIGNATURE_TARGET)
    endif
endif

ifeq ($(strip $(Rescue_Source)), USB)

endif

ifeq ($(Config_Secure_Key), TRUE)
	#BIN_ARGS += "hwsetting_sig_image="$(HW_SETTING_SIG_IMG)
	#BIN_ARGS += "dcas_key_sig_image="$(DCAS_KEY_SIG_IMG)
endif

ifeq ($(Config_FSBL), TRUE)
    ifeq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "fsbl="$(FSBL_HASH_TARGET_AES)
    else
        BIN_ARGS += "fsbl="$(FSBL_TARGET_PADDING)
    endif
    ifeq ($(Config_Simulation_Mode), TRUE)
	BIN_ARGS += "fsbl_signature="$(FSBL_DIGEST_TARGET)
    else ifneq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "fsbl_signature="$(FSBL_DIGEST_TARGET)
    else
	BIN_ARGS += "fsbl_signature="$(FSBL_SIGNATURE_TARGET)
    endif
endif
ifeq ($(Config_FSBL_OS), TRUE)
    ifeq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "fsbl_os="$(FSBL_OS_HASH_TARGET_AES)
    else
        BIN_ARGS += "fsbl_os="$(FSBL_OS_TARGET_PADDING)
    endif
    ifeq ($(Config_Simulation_Mode), TRUE)
	BIN_ARGS += "fsbl_os_signature="$(FSBL_OS_DIGEST_TARGET)
    else ifneq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "fsbl_os_signature="$(FSBL_OS_DIGEST_TARGET)
    else
	BIN_ARGS += "fsbl_os_signature="$(FSBL_OS_SIGNATURE_TARGET)
    endif
endif
ifeq ($(Config_BL31), TRUE)
    ifeq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "bl31="$(BL31_HASH_TARGET_AES)
    else
        BIN_ARGS += "bl31="$(BL31_TARGET_PADDING)
    endif
    ifeq ($(Config_Simulation_Mode), TRUE)
	BIN_ARGS += "bl31_signature="$(BL31_DIGEST_TARGET)
    else ifneq ($(Config_Secure_Key), TRUE)
        BIN_ARGS += "bl31_signature="$(BL31_DIGEST_TARGET)
    else
	BIN_ARGS += "bl31_signature="$(BL31_SIGNATURE_TARGET)
    endif
endif
ifeq ($(Config_Secure_Improve), TRUE)
	BIN_ARGS += "Kpublic_fw="$(RSA_BIN_FW_HASH_TARGET_AES)
	BIN_ARGS += "Kpublic_tee="$(RSA_BIN_TEE_HASH_TARGET_AES)
    ifeq ($(Config_Simulation_Mode), TRUE)
	BIN_ARGS += "Kpublic_fw_signature="$(RSA_BIN_FW_DIGEST_TARGET)
	BIN_ARGS += "Kpublic_tee_signature="$(RSA_BIN_TEE_DIGEST_TARGET)
    else
	BIN_ARGS += "Kpublic_fw_signature="$(RSA_BIN_FW_SIGNATURE_TARGET)
	BIN_ARGS += "Kpublic_tee_signature="$(RSA_BIN_TEE_SIGNATURE_TARGET)
    endif
endif
ifeq ($(Config_RSA_Key_Pub_Embed), TRUE)
	BIN_ARGS           += "rsa_pub="$(RSA_KEY_PUB_FILE)
endif
# ********************************************************************
# Function.
# ********************************************************************
#$(call rsa-sign, input_binary, output_padding, output_digest, input_rsa_key_file, output_signature)
rsa-sign =                                                             \
	$(SHA_EXE) $(1) $(2) $(3);                                     \
	$(RTSSL_EXE) enc -e -rsa -i $(3) -k $(4) -o $(5);

#---------------------------------------------------------------------
#$(call hwrsa-sign, rsa_key_text, clear_data, enc_data)
hwrsa-sign =                                                                                          \
        $(OPENSSL) rsa -text -in $(1) -out $(1).text;                                           \
        dd if=$(BOOTCODE_UBOOT_TARGET) of=224b.bin bs=224 count=1;                                    \
        cat 224b.bin $(2) > clear_data.bin;                                                           \
        $(OPENSSL) rsautl -inkey $(1) -sign -raw -in clear_data.bin -out $(TMP_RSA_OUT);   \
        $(GEN_RSA_PATTERN) --key $(1).text --msg $(TMP_RSA_OUT) --binary;                                  \
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

# For PowerPC there's no need to compile standalone applications as a
# relocatable executable.  The relocation data is not needed, and
# also causes the entry point of the standalone application to be
# inconsistent.
ifeq ($(ARCH),powerpc)
AFLAGS := $(filter-out $(RELFLAGS),$(AFLAGS))
CFLAGS := $(filter-out $(RELFLAGS),$(CFLAGS))
CPPFLAGS := $(filter-out $(RELFLAGS),$(CPPFLAGS))
endif

#########################################################################
# Assign FLASH_TYPE for hw setting in flash_writer_u
ifndef FLASH_TYPE
FLASH_TYPE = RTK_FLASH_SPI
endif
#########################################################################


# We don't want gcc reordering functions if possible.  This ensures that an
# application's entry point will be the first function in the application's
# source file.
#CFLAGS_NTR := $(call cc-option,-fno-toplevel-reorder)
#CFLAGS += $(CFLAGS_NTR) -I$(INCLUDE_DIR)
#CFLAGS = -g -Os -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv7-a  -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security  -fno-toplevel-reorder 
CFLAGS = -g -Os -fno-common -ffixed-r8 -D__KERNEL__ -fno-builtin -ffreestanding -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__  -march=armv8-a -D__EL__ -D__ARM_ARCH_8A__
#CFLAGS += -msoft-float -marm -mabi=aapcs-linux -mno-thumb-interwork

ifeq ($(BOOT),yes)
CFLAGS += -DBootPartition_StartUp
endif


ifeq ($(Board_CPU), RTD1295)
    CFLAGS += -DCONFIG_RTD1295
endif

CFLAGS += $(INCDIRS)
all:	clean configconv hw_setting b2a get_config $(OBJS) $(SSOBJS) $(LIB) $(ELF) $(SREC) $(BIN)

clean:
	-rm -f $(TARGET_EXE) *.o *.reverse temp_target_array.h *.bin *.map *.dis *.srec
	#-rm -rf $(PACKAGE_DIR) $(SIGNATURE_TARGET).reverse
	-rm -rf $(PACKAGE_DIR) $(SIGNATURE_TARGET)
	-rm -rf $(TOP_DIR)/$(BIND_FOLDER)
	-rm $(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL)
	-rm -rf $(TOP_DIR)/Bind
	-rm -f $(TOP_DIR)/image/realtek_ntsc1.bmp.dat
	-rm -f $(TOP_DIR)/image/realtek_ntsc1.bmp.inf
	-rm -f $(TOP_DIR)/image/rsa_key_2048.fw.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key_2048.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key_2048.tee.pem.bin.rev
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
		@mkdir -p install_a
		#@cp -rf $(HW_SETTING_TARGET_INVERSE) install_a/hw_setting.bin
		cat $(HW_SETTING_HEADER_FINAL) $(HW_SETTING_TARGET_FINAL) > install_a/hw_setting.bin		
#		@cp -rf $(IMAGE_DIR)/$(Rescue_File_Name) install_a/
#                ifeq ($(Config_Uboot_Enc), TRUE)
#			@cp -rf $(BOOTCODE_BOOT_HASH_TARGET2).aes install_a/
#                else
		cat $(UBOOT_FINAL) > install_a/uboot.bin
ifeq ($(Config_FSBL), TRUE)
		cat $(FSBL_FINAL) > install_a/fsbl.bin
endif
ifeq ($(Config_FSBL_OS), TRUE)
		cat $(FSBL_OS_FINAL) > install_a/tee.bin
endif
ifeq ($(Config_BL31), TRUE)
		cat $(BL31_FINAL) > install_a/bl31.bin
endif
ifeq ($(Config_Secure_Improve), TRUE)
		cat $(RSA_BIN_FW_FINAL) > install_a/rsa_bin_fw.bin
		cat $(RSA_BIN_TEE_FINAL) > install_a/rsa_bin_tee.bin
endif
ifeq ($(Config_SPI_BOOTCODE2), TRUE)
		cat $(UBOOT2_FINAL) > install_a/uboot2.bin
		./create_hd.pl $(UBOOT2_FINAL) > install_a/bootcode2.hdr
endif
#                endif
#        ifeq ($(Config_Secure_Key), TRUE)
#			@cd install_a/; $(RTSSL_EXE) dgst -sha256 -aps -i $(Rescue_File_Name) -sign -rsa -k $(RSA_KEY_FILE)
#			@cd install_a/; $(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(Rescue_File_Name) -o $(Rescue_File_Name).aes
#			@rm install_a/$(Rescue_File_Name)
#			@mv install_a/$(Rescue_File_Name).aes install_a/$(Rescue_File_Name)
#        else
#			@cd install_a/; $(RTSSL_EXE) dgst -sha256 -ap -i $(Rescue_File_Name)
#        endif
		@cd install_a/; tar cf ../../../bootloader.tar *
		@rm -rf install_a/

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

#configconv: logo1 logo2 logo3 logo4 logo5 logo6 logo7 logo8 rsa_key aes_seed rsa_key0
configconv: logo1
	$(PERL) $(SCRIPT_DIR)/$(CONFIGCONV_SCRIPT) \
		$(INCLUDE_DIR)/project_config_f.h \
		$(TOP_DIR)/$(PRJ).inc \
		$(IMAGE_DIR)/$(Logo_File_Name).inf \
		$(IMAGE_DIR)/$(Logo2_File_Name).inf \
		$(IMAGE_DIR)/$(Logo3_File_Name).inf \
		$(IMAGE_DIR)/$(Logo4_File_Name).inf \
		$(IMAGE_DIR)/$(Logo5_File_Name).inf \
		$(IMAGE_DIR)/$(Logo6_File_Name).inf \
		$(IMAGE_DIR)/$(Logo7_File_Name).inf \
		$(IMAGE_DIR)/$(Logo8_File_Name).inf \
		$(RSA_INF_PATH) \
		$(RSA_INF0_PATH)


$(LOGO_CHANGER):
	cd $(LOGO_CHANGER_DIR);\
	make

$(RTSSL_EXE):
	cd $(RTSSL_DIR);\
	make LIB_PATH=/usr/lib64 STATIC_LINK=N
	
logo1: $(LOGO_CHANGER)
	$(LOGO_CHANGER) $(LOGO_BMP_PATH) $(LOGO_DAT_PATH) $(LOGO_INF_PATH)

logo2: 
	$(LOGO_CHANGER) $(LOGO2_BMP_PATH) $(LOGO2_DAT_PATH) $(LOGO2_INF_PATH)

logo3: 
	$(LOGO_CHANGER) $(LOGO3_BMP_PATH) $(LOGO3_DAT_PATH) $(LOGO3_INF_PATH)

logo4: 
	$(LOGO_CHANGER) $(LOGO4_BMP_PATH) $(LOGO4_DAT_PATH) $(LOGO4_INF_PATH)
	
logo5: 
	$(LOGO_CHANGER) $(LOGO5_BMP_PATH) $(LOGO5_DAT_PATH) $(LOGO5_INF_PATH)

logo6: 
	$(LOGO_CHANGER) $(LOGO6_BMP_PATH) $(LOGO6_DAT_PATH) $(LOGO6_INF_PATH)
	
logo7: 
	$(LOGO_CHANGER) $(LOGO7_BMP_PATH) $(LOGO7_DAT_PATH) $(LOGO7_INF_PATH)	
	
logo8: 
	$(LOGO_CHANGER) $(LOGO8_BMP_PATH) $(LOGO8_DAT_PATH) $(LOGO8_INF_PATH)		
		
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

rsa_key0:
	if [ $(Config_Secure_RSA_Key0_File) ]; then \
			echo Config_Secure_RSA0_MODULUS=\"`$(RTSSL_EXE) rsa -print -modulous -i $(RSA_KEY0_PATH)`\" > $(RSA_INF0_PATH) ;\
	else \
		echo "Config_Secure_RSA_Key0_File not defined in $(PRJ).inc"; \
	fi
	
$(HW_SETTING_MAKER_AP):
	$(CD) $(HW_SETTING_MAKER_DIR);\
	$(MAKE);

$(BINDALLBIN_UTIL):
	$(CD) $(BINDALLBIN_MAKER_DIR);\
	make clean;$(MAKE);
		
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
	$(MAKE)

#b2a: marge_boot_target target_encrypt 
#b2a: rsa_key rsa_key0 merge_bootcode_target merge_bootcode2_target merge_bootcode3_target target_encrypt bootcode2_target_encrypt bootcode3_target_encrypt linux_rescue_encrypt dcas_key
b2a: rsa_key merge_hwsetting_target merge_bootcode_target target_encrypt linux_rescue_encrypt fsbl fsbl_os bl31 secure_improve
	#generate header must prior to real bind job
       ifeq ($(TRUE_SYB),$(filter $(TRUE_SYB),$(Config_Secure_Key) $(Config_USB_MP_Mode))) 
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl secure header $(SIM_MODE) $(UBOOT_ENC)
	#$(RTSSL_EXE) enc -e -aes_128_ecb -i $(HW_SETTING_HEADER_FINAL) -o $(HW_SETTING_HEADER_FINAL_ENC) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	$(OBFUSE) $(RTSSL_EXE) 97 $(AES_SEED_PATH) $(AES_KEY_PATH) $(HW_SETTING_HEADER_FINAL) $(HW_SETTING_HEADER_FINAL_ENC)
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl secure $(SIM_MODE) $(UBOOT_ENC)
	cat $(HW_SETTING_HEADER_FINAL) > $(HW_SETTING_HEADER_FINAL).dec
	cat $(HW_SETTING_HEADER_FINAL_ENC) > $(HW_SETTING_HEADER_FINAL)
       else ifeq ($(Config_FSBL), TRUE)	
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl header $(SIM_MODE) $(UBOOT_ENC)
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fsbl $(SIM_MODE) $(UBOOT_ENC)
       else
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) header $(SIM_MODE) $(UBOOT_ENC)
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) $(SIM_MODE) $(UBOOT_ENC)
       endif
	$(BIN2HEX) $(BIND_FOLDER)/bind.bin $(BIND_FOLDER)/bind.bin.hex
	./bin2ascii $(BIN_ARGS) > temp_target_array.h

$(INVERSE):
	cc inverse.c -o $(INVERSE);\
	chmod +x $(INVERSE)

merge_hwsetting_target: $(SHA_EXE)
    ifeq ($(Config_USB_MP_Mode), FALSE)
	$(SHA_EXE) $(HW_SETTING_TARGET) $(HW_SETTING_PADDING_FINAL) $(HW_SETTING_DIGEST)
	cat $(HW_SETTING_TARGET) $(HW_SETTING_PADDING_FINAL) > $(HW_SETTING_TARGET_PADDING)
     ifeq ($(Config_Secure_Key), TRUE)
	# for secure boot
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(HW_SETTING_DIGEST), $(HW_SETTING_DIGEST_ENC))
	#$(RTSSL_EXE) enc -e -rsa -i $(HW_SETTING_DIGEST) -k $(RSA_KEY_FILE) -o $(HW_SETTING_DIGEST_ENC)
	#$(RTSSL_EXE) enc -e -aes_128_ecb -i $(HW_SETTING_TARGET_PADDING) -o $(HW_SETTING_TARGET_ENC) -k `hexdump -e '8/1 "%02x"' $(AES_SEED_PATH_ENC)`
	$(OBFUSE) $(RTSSL_EXE) 97 $(AES_SEED_PATH) $(AES_KEY_PATH) $(HW_SETTING_TARGET_PADDING) $(HW_SETTING_TARGET_ENC)
	#$(REVERSE_RSA) $(HW_SETTING_DIGEST_ENC)
        ifeq ($(Config_Simulation_Mode), TRUE)
	cat $(HW_SETTING_TARGET_ENC) $(HW_SETTING_DIGEST) > $(HW_SETTING_TARGET_ENC_ALL)
        else
	cat $(HW_SETTING_TARGET_ENC) $(HW_SETTING_DIGEST_ENC) > $(HW_SETTING_TARGET_ENC_ALL)
        endif
	cat $(HW_SETTING_TARGET_ENC_ALL) > $(HW_SETTING_TARGET_FINAL)
     else
	# non-secure
	cat $(HW_SETTING_TARGET_PADDING) $(HW_SETTING_DIGEST) > $(HW_SETTING_TARGET_ALL)
	cat $(HW_SETTING_TARGET_ALL) > $(HW_SETTING_TARGET_FINAL)
     endif
    else
        #encryption mechanism for usb mp mode
	#$(RTSSL_EXE) enc -e -aes_128_ecb -i $(HW_SETTING_TARGET) -o $(HW_SETTING_TARGET_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	#cat $(HW_SETTING_TARGET_ENC) $(AES128_KEY_PATH) > $(SHA1_DATA_ORG)
	cat $(HW_SETTING_TARGET) $(AES128_KEY_PATH) > $(SHA1_DATA_ORG)
	$(SHA_EXE) $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) $(HW_SETTING_DIGEST)
	cat $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) > $(SHA1_DATA)
	cat $(SHA1_DATA) > $(HW_SETTING_TARGET_PADDING)
	cat $(SHA1_DATA_PADDING) > $(HW_SETTING_PADDING_FINAL)
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(HW_SETTING_DIGEST) -o $(RS2_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	cat $(SHA1_DATA) $(RS2_ENC) > $(B1)
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(B1) -o $(B1_ENC) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	cat $(B1_ENC) > $(HW_SETTING_TARGET_ENC_ALL)
	cat $(HW_SETTING_TARGET_ENC_ALL) > $(HW_SETTING_TARGET_FINAL)
    endif

merge_bootcode_target: $(INVERSE)
	# copy u-boot.bin to local, bin2ascii need to know its size in output file 
ifeq ($(Config_Simulation_Mode), TRUE)
	cp $(BOOTCODE_UBOOT_TARGET_SIM) ./u-boot.bin
	cat $(BOOTCODE_UBOOT_TARGET_SIM) > $(BOOTCODE_BOOT_TARGET)
    ifeq ($(Board_FPGA), V6)
		cp $(BOOTCODE_UBOOT_TARGET) .
		cat $(BOOTCODE_UBOOT_TARGET) > $(BOOTCODE_BOOT_TARGET)
    endif
    ifeq ($(Board_FPGA), V7)
		cp $(BOOTCODE_UBOOT_TARGET) .
		cat $(BOOTCODE_UBOOT_TARGET) > $(BOOTCODE_BOOT_TARGET)
    endif
else
    ifeq ($(Config_ROM2), TRUE)
		cp $(ROM2_RESET_TARGET) $(BOOTCODE_UBOOT_TARGET)
		cp $(BOOTCODE_UBOOT_TARGET) .
		cat $(ROM2_RESET_TARGET) > $(BOOTCODE_BOOT_TARGET)
   else
        ifeq ($(Config_Uboot_Sim_Mode), TRUE)
		cp $(BOOTCODE_UBOOT_TARGET_SIM) ./u-boot.bin
		cat $(BOOTCODE_UBOOT_TARGET_SIM) > $(BOOTCODE_BOOT_TARGET)
        else
		cp $(BOOTCODE_UBOOT_TARGET) .
		cat $(BOOTCODE_UBOOT_TARGET) > $(BOOTCODE_BOOT_TARGET)
        endif
   endif
endif

ifeq ($(Config_Jumper_Mode), TRUE)
	cp $(BOOTCODE_BOOT_TARGET) $(BOOTCODE_BOOT_TARGET_TMP)
	cat $(JUMPER_TARGET) $(BOOTCODE_BOOT_TARGET_TMP) > $(BOOTCODE_BOOT_TARGET)
endif


merge_bootcode2_target: $(INVERSE)
	# copy bootcode2 fw to local, bin2ascii need to know its size in output file 
	cp $(BOOTCODE2_UBOOT_TARGET) .
	cp $(BOOTCODE2_UBOOT_TARGET) ./bootcode2_u-boot.bin
	cp $(BOOTCODE2_UBOOT_TARGET) $(BIND_FOLDER)/uboot2.bin
	cat $(BOOTCODE2_UBOOT_TARGET) > $(BOOTCODE2_BOOT_TARGET)

merge_bootcode3_target: $(INVERSE)
	# fix me
	cp $(BOOTCODE_UBOOT_TARGET) $(BOOTCODE3_UBOOT_TARGET)
	# copy bootcode3 fw to local, bin2ascii need to know its size in output file 
	cp $(BOOTCODE3_UBOOT_TARGET) .
	cp $(BOOTCODE3_UBOOT_TARGET) ./bootcode3_u-boot.bin
	cat $(BOOTCODE3_UBOOT_TARGET) > $(BOOTCODE3_BOOT_TARGET)

target_encrypt: $(SHA_EXE)
    ifeq ($(Config_USB_MP_Mode), FALSE)
	$(SHA_EXE) $(BOOTCODE_BOOT_TARGET) $(BOOTCODE_BOOT_PADDING_FINAL) $(BOOTCODE_BOOT_DIGEST_TARGET)
	cat $(BOOTCODE_BOOT_TARGET) $(BOOTCODE_BOOT_PADDING_FINAL) > $(BOOTCODE_BOOT_TARGET_PADDING)
     ifeq ($(Config_Uboot_Enc), TRUE)
	# for uboot enc
	#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH).enc` -i $(BOOTCODE_BOOT_TARGET_PADDING) -o $(BOOTCODE_BOOT_HASH_TARGET).aes
	$(OBFUSE) $(RTSSL_EXE) 92 $(AES_KEY1_PATH) $(AES_KEY_PATH) $(AES_KEY2_PATH) $(AES_KEY3_PATH) $(BOOTCODE_BOOT_TARGET_PADDING) $(BOOTCODE_BOOT_HASH_TARGET).aes
    	# to b2a
	cat $(BOOTCODE_BOOT_HASH_TARGET).aes > $(BOOTCODE_BOOT_HASH_TARGET2)
    	# to install_a
	cat $(BOOTCODE_BOOT_HASH_TARGET).aes > $(BOOTCODE_BOOT_HASH_TARGET2).aes
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(BOOTCODE_BOOT_DIGEST_TARGET), $(SIGNATURE_TARGET))	
	#$(RTSSL_EXE) enc -e -rsa -i $(BOOTCODE_BOOT_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(SIGNATURE_TARGET)
	#$(REVERSE_RSA) $(SIGNATURE_TARGET)
	#cat $(SIGNATURE_TARGET) > $(SIGNATURE_TARGET).org
	#cat $(SIGNATURE_TARGET).rev > $(SIGNATURE_TARGET)
        ifeq ($(Config_Simulation_Mode), TRUE)
	cat $(BOOTCODE_BOOT_HASH_TARGET2) $(BOOTCODE_BOOT_DIGEST_TARGET) > $(UBOOT_FINAL)
        else
	cat $(BOOTCODE_BOOT_HASH_TARGET2) $(SIGNATURE_TARGET) > $(UBOOT_FINAL)
        endif
     else
	cat $(BOOTCODE_BOOT_TARGET_PADDING) > $(BOOTCODE_BOOT_HASH_TARGET2)
	cat $(BOOTCODE_BOOT_DIGEST_TARGET) > $(SIGNATURE_TARGET)
	cat $(BOOTCODE_BOOT_HASH_TARGET2) $(SIGNATURE_TARGET) > $(UBOOT_FINAL)
     endif
    else
        #encryption mechanism for usb mp mode
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(BOOTCODE_BOOT_TARGET) -o $(BOOTCODE_BOOT_TARGET_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	cat $(BOOTCODE_BOOT_TARGET_ENC) $(AES128_KEY_PATH) > $(SHA1_DATA_ORG)
	$(SHA_EXE) $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) $(SH1)
	cat $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) > $(SHA1_DATA)
	cat $(SHA1_DATA_PADDING) > $(BOOTCODE_BOOT_PADDING_FINAL)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(SH1), $(RS1))
	#$(RTSSL_EXE) enc -e -rsa -i $(SH1) -k $(RSA_KEY_FILE) -o $(RS1)
	#$(REVERSE_RSA) $(RS1)
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(RS1) -o $(RS2_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(SHA1_DATA) -o $(BOOTCODE_BOOT_HASH_TARGET2) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(RS2_ENC) -o $(SIGNATURE_TARGET) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	cat $(BOOTCODE_BOOT_HASH_TARGET2) $(SIGNATURE_TARGET) > $(UBOOT_FINAL)
    endif

bootcode2_target_encrypt: $(SHA_EXE)
	cp $(BOOTCODE2_BOOT_TARGET) $(BOOTCODE2_BOOT_HASH_TARGET)
	$(RTSSL_EXE) dgst -sha256 -g -i $(BOOTCODE2_BOOT_HASH_TARGET) -o $(BOOTCODE2_BOOT_DIGEST_TARGET)
	$(RTSSL_EXE) enc -e -rsa -i $(BOOTCODE2_BOOT_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(BOOTCODE2_BOOT_SIGNATURE_TARGET)
	./reverse.pl $(BOOTCODE2_BOOT_SIGNATURE_TARGET) > $(BOOTCODE2_BOOT_SIGNATURE_TARGET).reverse
    ifeq ($(Config_Secure_Key), TRUE)
		$(RTSSL_EXE) dgst -sha256 -aps -i $(BOOTCODE2_BOOT_HASH_TARGET) -sign -rsa -k $(RSA_KEY_FILE)
		$(RTSSL_EXE) enc -e -aes_128_cbc -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(BOOTCODE2_BOOT_HASH_TARGET) -o $(BOOTCODE2_BOOT_HASH_TARGET_AES)
		cp $(BOOTCODE2_BOOT_HASH_TARGET_AES) $(UBOOT2_FINAL)
    else
		$(RTSSL_EXE) dgst -sha256 -ap -i $(BOOTCODE2_BOOT_HASH_TARGET)
		cp $(BOOTCODE2_BOOT_HASH_TARGET) $(UBOOT2_FINAL)
    endif

bootcode3_target_encrypt: $(SHA_EXE)
	cp $(BOOTCODE3_BOOT_TARGET) $(BOOTCODE3_BOOT_HASH_TARGET)
	$(RTSSL_EXE) dgst -sha256 -g -i $(BOOTCODE3_BOOT_HASH_TARGET) -o $(BOOTCODE3_BOOT_DIGEST_TARGET)
	$(RTSSL_EXE) enc -e -rsa -i $(BOOTCODE3_BOOT_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(BOOTCODE3_BOOT_SIGNATURE_TARGET)
	./reverse.pl $(BOOTCODE3_BOOT_SIGNATURE_TARGET) > $(BOOTCODE3_BOOT_SIGNATURE_TARGET).reverse
    ifeq ($(Config_Secure_Key), TRUE)
		$(RTSSL_EXE) dgst -sha256 -aps -i $(BOOTCODE3_BOOT_HASH_TARGET) -sign -rsa -k $(RSA_KEY_FILE)
		$(RTSSL_EXE) enc -e -aes_128_cbc -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(BOOTCODE3_BOOT_HASH_TARGET) -o $(BOOTCODE3_BOOT_HASH_TARGET_AES)
    else
		$(RTSSL_EXE) dgst -sha256 -ap -i $(BOOTCODE3_BOOT_HASH_TARGET)
    endif
	
linux_rescue_encrypt: $(SHA_EXE)
ifeq ($(strip $(Rescue_Source)), FLASH)
	$(SHA_EXE) $(LINUX_RESCUE_TARGET) $(LINUX_RESCUE_PADDING_FINAL) $(LINUX_RESCUE_DIGEST_TARGET)
	cat $(LINUX_RESCUE_TARGET) $(LINUX_RESCUE_PADDING_FINAL) > $(LINUX_RESCUE_TARGET_PADDING)
	cp $(LINUX_RESCUE_TARGET_PADDING) $(LINUX_RESCUE_HASH_TARGET)
    ifeq ($(Config_USB_MP_Mode), FALSE)
    ifeq ($(Config_Secure_Key), TRUE)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(LINUX_RESCUE_DIGEST_TARGET), $(LINUX_RESCUE_SIGNATURE_TARGET))
	#$(RTSSL_EXE) enc -e -rsa -i $(LINUX_RESCUE_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(LINUX_RESCUE_SIGNATURE_TARGET)
	#$(REVERSE_RSA) $(LINUX_RESCUE_SIGNATURE_TARGET)
	#cat $(LINUX_RESCUE_SIGNATURE_TARGET) > $(LINUX_RESCUE_SIGNATURE_TARGET)
	$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(LINUX_RESCUE_HASH_TARGET) -o $(LINUX_RESCUE_HASH_TARGET_AES)
        ifeq ($(Config_Simulation_Mode), TRUE)
	cat $(LINUX_RESCUE_HASH_TARGET_AES) $(LINUX_RESCUE_DIGEST_TARGET) > $(RESCUE_FINAL)
        else
	cat $(LINUX_RESCUE_HASH_TARGET_AES) $(LINUX_RESCUE_SIGNATURE_TARGET) > $(RESCUE_FINAL)
        endif
    else
	cat $(LINUX_RESCUE_DIGEST_TARGET) > $(LINUX_RESCUE_SIGNATURE_TARGET)
	cat $(LINUX_RESCUE_HASH_TARGET) $(LINUX_RESCUE_SIGNATURE_TARGET) > $(RESCUE_FINAL)
    endif
    else
        #encryption mechanism for usb mp mode
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(LINUX_RESCUE_HASH_TARGET) -o $(LINUX_RESCUE_HASH_TARGET_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	cat $(LINUX_RESCUE_HASH_TARGET_ENC) $(AES128_KEY_PATH) > $(SHA1_DATA_ORG)
	$(SHA_EXE) $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) $(SH1)
	cat $(SHA1_DATA_ORG) $(SHA1_DATA_PADDING) > $(SHA1_DATA)
	cat $(SHA1_DATA_PADDING) > $(LINUX_RESCUE_PADDING_FINAL)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(SHA1), $(RS1))
	#$(RTSSL_EXE) enc -e -rsa -i $(SH1) -k $(RSA_KEY_FILE) -o $(RS1)
	#$(REVERSE_RSA) $(RS1)
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(RS1) -o $(RS2_ENC) -k `hexdump -e '8/1 "%02x"' $(AES128_KEY_PATH)`
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(SHA1_DATA) -o $(LINUX_RESCUE_HASH_TARGET_AES) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	$(RTSSL_EXE) enc -e -aes_128_ecb -i $(RS2_ENC) -o $(LINUX_RESCUE_SIGNATURE_TARGET) -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)`
	cat $(LINUX_RESCUE_HASH_TARGET_AES) $(LINUX_RESCUE_SIGNATURE_TARGET) > $(RESCUE_FINAL)
    endif
endif
fsbl:
    ifeq ($(Config_FSBL), TRUE)
	$(SHA_EXE) $(FSBL_TARGET) $(FSBL_PADDING_FINAL) $(FSBL_DIGEST_TARGET)
	cat $(FSBL_TARGET) $(FSBL_PADDING_FINAL) > $(FSBL_TARGET_PADDING)
        ifeq ($(Config_Secure_Key), TRUE)
	cp $(FSBL_TARGET_PADDING) $(FSBL_HASH_TARGET)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(FSBL_DIGEST_TARGET), $(FSBL_SIGNATURE_TARGET))
	#$(RTSSL_EXE) enc -e -rsa -i $(FSBL_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(FSBL_SIGNATURE_TARGET)
	#$(REVERSE_RSA) $(FSBL_SIGNATURE_TARGET)
	#cat $(FSBL_SIGNATURE_TARGET) > $(FSBL_SIGNATURE_TARGET)
	#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_SEED_PATH_ENC)` -i $(FSBL_HASH_TARGET) -o $(FSBL_HASH_TARGET_AES)
	$(OBFUSE) $(RTSSL_EXE) 97 $(AES_SEED_PATH) $(AES_KEY_PATH) $(FSBL_HASH_TARGET) $(FSBL_HASH_TARGET_AES)
                ifeq ($(Config_Simulation_Mode), TRUE)
			cat $(FSBL_HASH_TARGET_AES) $(FSBL_DIGEST_TARGET) > $(FSBL_FINAL)
                else
			cat $(FSBL_HASH_TARGET_AES) $(FSBL_SIGNATURE_TARGET) > $(FSBL_FINAL)	
                endif
        else
		cat $(FSBL_TARGET_PADDING) $(FSBL_DIGEST_TARGET) > $(FSBL_FINAL)	
        endif
    endif
fsbl_os:
    ifeq ($(Config_FSBL_OS), TRUE)
	$(SHA_EXE) $(FSBL_OS_TARGET) $(FSBL_OS_PADDING_FINAL) $(FSBL_OS_DIGEST_TARGET)
	cat $(FSBL_OS_TARGET) $(FSBL_OS_PADDING_FINAL)  > $(FSBL_OS_TARGET_PADDING)
        ifeq ($(Config_Secure_Key), TRUE)
		cp $(FSBL_OS_TARGET_PADDING) $(FSBL_OS_HASH_TARGET)
		$(call hwrsa-sign, $(RSA_KEY_TEE_PATH), $(FSBL_OS_DIGEST_TARGET), $(FSBL_OS_SIGNATURE_TARGET))
		#$(RTSSL_EXE) enc -e -rsa -i $(FSBL_OS_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(FSBL_OS_SIGNATURE_TARGET)
		#$(REVERSE_RSA) $(FSBL_OS_SIGNATURE_TARGET)
		#cat $(FSBL_OS_SIGNATURE_TARGET) > $(FSBL_OS_SIGNATURE_TARGET)
		#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_SEED_PATH_ENC)` -i $(FSBL_OS_HASH_TARGET) -o $(FSBL_OS_HASH_TARGET_AES)
		$(OBFUSE) $(RTSSL_EXE) 93 $(AES_KEY1_PATH) $(AES_KEY_PATH) $(AES_KEY2_PATH) $(AES_KEY3_PATH) $(FSBL_OS_HASH_TARGET) $(FSBL_OS_HASH_TARGET_AES)
                ifeq ($(Config_Simulation_Mode), TRUE)
			cat $(FSBL_OS_HASH_TARGET_AES) $(FSBL_OS_DIGEST_TARGET) > $(FSBL_OS_FINAL)
                else
			cat $(FSBL_OS_HASH_TARGET_AES) $(FSBL_OS_SIGNATURE_TARGET) > $(FSBL_OS_FINAL)
                endif
        else
		cat $(FSBL_OS_TARGET_PADDING) $(FSBL_OS_DIGEST_TARGET) > $(FSBL_OS_FINAL)	
        endif
    endif
bl31:
    ifeq ($(Config_BL31), TRUE)
	$(SHA_EXE) $(BL31_TARGET) $(BL31_PADDING_FINAL) $(BL31_DIGEST_TARGET)
	cat $(BL31_TARGET) $(BL31_PADDING_FINAL)  > $(BL31_TARGET_PADDING)
        ifeq ($(Config_Secure_Key), TRUE)
		cp $(BL31_TARGET_PADDING) $(BL31_HASH_TARGET)
		$(call hwrsa-sign, $(RSA_KEY_TEE_PATH), $(BL31_DIGEST_TARGET), $(BL31_SIGNATURE_TARGET))
		#$(RTSSL_EXE) enc -e -rsa -i $(FSBL_OS_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(FSBL_OS_SIGNATURE_TARGET)
		#$(REVERSE_RSA) $(FSBL_OS_SIGNATURE_TARGET)
		#cat $(FSBL_OS_SIGNATURE_TARGET) > $(FSBL_OS_SIGNATURE_TARGET)
		#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_SEED_PATH_ENC)` -i $(FSBL_OS_HASH_TARGET) -o $(FSBL_OS_HASH_TARGET_AES)
		$(OBFUSE) $(RTSSL_EXE) 93 $(AES_KEY1_PATH) $(AES_KEY_PATH) $(AES_KEY2_PATH) $(AES_KEY3_PATH) $(BL31_HASH_TARGET) $(BL31_HASH_TARGET_AES)
                ifeq ($(Config_Simulation_Mode), TRUE)
			cat $(BL31_HASH_TARGET_AES) $(Bl31_DIGEST_TARGET) > $(BL31_FINAL)
                else
			cat $(BL31_HASH_TARGET_AES) $(BL31_SIGNATURE_TARGET) > $(BL31_FINAL)
                endif
        else
		cat $(BL31_TARGET_PADDING) $(BL31_DIGEST_TARGET) > $(BL31_FINAL)	
        endif
    endif
secure_improve:
    ifeq ($(Config_Secure_Improve), TRUE)
	$(SHA_EXE) $(RSA_BIN_FW_TARGET) $(RSA_BIN_FW_PADDING_FINAL) $(RSA_BIN_FW_DIGEST_TARGET)
	cat $(RSA_BIN_FW_TARGET) $(RSA_BIN_FW_PADDING_FINAL)  > $(RSA_BIN_FW_TARGET_PADDING)
	cp $(RSA_BIN_FW_TARGET_PADDING) $(RSA_BIN_FW_HASH_TARGET)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(RSA_BIN_FW_DIGEST_TARGET), $(RSA_BIN_FW_SIGNATURE_TARGET))
	#$(RTSSL_EXE) enc -e -rsa -i $(RSA_BIN_FW_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(RSA_BIN_FW_SIGNATURE_TARGET)
	#$(REVERSE_RSA) $(RSA_BIN_FW_SIGNATURE_TARGET)
	#cat $(RSA_BIN_FW_SIGNATURE_TARGET) > $(RSA_BIN_FW_SIGNATURE_TARGET)
	$(OBFUSE) $(RTSSL_EXE) 91 $(AES_KEY1_PATH) $(AES_KEY_PATH) $(AES_KEY2_PATH) $(AES_KEY3_PATH) $(RSA_BIN_FW_HASH_TARGET) $(RSA_BIN_FW_HASH_TARGET_AES)
	#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(RSA_BIN_FW_HASH_TARGET) -o $(RSA_BIN_FW_HASH_TARGET_AES)
        ifeq ($(Config_Simulation_Mode), TRUE)
	cat $(RSA_BIN_FW_HASH_TARGET_AES) $(RSA_BIN_FW_DIGEST_TARGET) > $(RSA_BIN_FW_FINAL)
        else
	cat $(RSA_BIN_FW_HASH_TARGET_AES) $(RSA_BIN_FW_SIGNATURE_TARGET) > $(RSA_BIN_FW_FINAL)
        endif
	$(SHA_EXE) $(RSA_BIN_TEE_TARGET) $(RSA_BIN_TEE_PADDING_FINAL) $(RSA_BIN_TEE_DIGEST_TARGET)
	cat $(RSA_BIN_TEE_TARGET) $(RSA_BIN_TEE_PADDING_FINAL)  > $(RSA_BIN_TEE_TARGET_PADDING)
	cp $(RSA_BIN_TEE_TARGET_PADDING) $(RSA_BIN_TEE_HASH_TARGET)
	$(call hwrsa-sign, $(RSA_KEY_PATH), $(RSA_BIN_TEE_DIGEST_TARGET), $(RSA_BIN_TEE_SIGNATURE_TARGET))
	#$(RTSSL_EXE) enc -e -rsa -i $(RSA_BIN_TEE_DIGEST_TARGET) -k $(RSA_KEY_FILE) -o $(RSA_BIN_TEE_SIGNATURE_TARGET)
	#$(REVERSE_RSA) $(RSA_BIN_TEE_SIGNATURE_TARGET)
	#cat $(RSA_BIN_TEE_SIGNATURE_TARGET) > $(RSA_BIN_TEE_SIGNATURE_TARGET)
	$(OBFUSE) $(RTSSL_EXE) 91 $(AES_KEY1_PATH) $(AES_KEY_PATH) $(AES_KEY2_PATH) $(AES_KEY3_PATH) $(RSA_BIN_TEE_HASH_TARGET) $(RSA_BIN_TEE_HASH_TARGET_AES)
	#$(RTSSL_EXE) enc -e -aes_128_ecb -k `hexdump -e '8/1 "%02x"' $(AES_KEY_PATH)` -i $(RSA_BIN_TEE_HASH_TARGET) -o $(RSA_BIN_TEE_HASH_TARGET_AES)
        ifeq ($(Config_Simulation_Mode), TRUE)
	cat $(RSA_BIN_TEE_HASH_TARGET_AES) $(RSA_BIN_TEE_DIGEST_TARGET) > $(RSA_BIN_TEE_FINAL)
        else
	cat $(RSA_BIN_TEE_HASH_TARGET_AES) $(RSA_BIN_TEE_SIGNATURE_TARGET) > $(RSA_BIN_TEE_FINAL)
        endif
    endif
	
get_config:
	$(SED) -i 's/Config_FLASH_TYPE.*/$(FLASH_TYPE)/g' $(INCLUDE_DIR)/project_config_f.h;	
