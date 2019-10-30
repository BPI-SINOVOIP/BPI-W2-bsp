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

include inc/$(PRJ).inc
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

ifeq ($(CHIP_TYPE), 0000)
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern64_0000.pl
else
GEN_RSA_PATTERN      = $(SCRIPT_DIR)/gen_rsa_pattern64_0001.pl
endif

HW_SETTING_MAKER_DIR = $(TOOLS_DIR)/hw_setting_maker
HW_SETTING_DIR       =$(TOP_DIR)/hw_setting
HW_SETTING_TARGET = $(HW_SETTING_DIR)/out/$(Board_HWSETTING).bin
HW_SETTING_TARGET_ENC = $(HW_SETTING_DIR)/out/$(Board_HWSETTING)_enc.bin
HW_SETTING_TARGET_DIGEST = $(HW_SETTING_DIR)/out/$(Board_HWSETTING)_digest.bin
HW_SETTING_TARGET_DIGEST_ENC = $(HW_SETTING_DIR)/out/$(Board_HWSETTING)_digest_enc.bin
HW_SETTING_TARGET_FINAL = $(HW_SETTING_DIR)/out/$(Board_HWSETTING)_final.bin
HW_SETTING_TARGET_RAW_FILE = $(HW_SETTING_DIR)/$(CHIP_ID)/$(CUSTOMER_ID)/$(CHIP_TYPE)/$(Board_HWSETTING).config

BINDALLBIN_MAKER_DIR = $(TOOLS_DIR)/bindAllBins

SHA_DIR    = $(TOOLS_DIR)/do_sha256
RTSSL_DIR  = $(TOOLS_DIR)/RtSSL
OBFUSE_DIR  = $(TOOLS_DIR)/obfuse
OPENSSL    = openssl
SCRIPT_DIR = $(TOOLS_DIR)/script
CRC32_DIR  = $(TOOLS_DIR)/crc32
NF_PROFILER_DIR  = $(TOOLS_DIR)/nf_profiler

#bind all bins
BINDALLBIN_UTIL	     = bindAllBins
BIND_FOLDER	     =	Bind

#emmc bootarray fw table
EMMC_BOOTARRAY_FW_TABLE = $(BIND_FOLDER)/eMMC_bootarray_fw_table.bin
EMMC_BOOTARRAY_FW_TABLE_PADDING = $(BIND_FOLDER)/eMMC_bootarray_fw_table_padding.bin
EMMC_BOOTARRAY_FW_TABLE_ALL = $(BIND_FOLDER)/eMMC_bootarray_fw_table_all.bin
EMMC_BOOTARRAY_FW_TABLE_ENC = $(BIND_FOLDER)/eMMC_bootarray_fw_table_enc.bin
EMMC_BOOTARRAY_FW_TABLE_DIGEST = $(BIND_FOLDER)/eMMC_bootarray_fw_table_digest.bin
EMMC_BOOTARRAY_FW_TABLE_DIGEST_ENC = $(BIND_FOLDER)/eMMC_bootarray_fw_table_digest_enc.bin
EMMC_BOOTARRAY_FW_TABLE_FINAL = $(BIND_FOLDER)/eMMC_bootarray_fw_table_final.bin
#spi bootarray fw table
SPI_BOOTARRAY_FW_TABLE = $(BIND_FOLDER)/spi_bootarray_fw_table.bin
SPI_BOOTARRAY_FW_TABLE_PADDING = $(BIND_FOLDER)/spi_bootarray_fw_table_padding.bin
SPI_BOOTARRAY_FW_TABLE_ALL = $(BIND_FOLDER)/spi_bootarray_fw_table_all.bin
SPI_BOOTARRAY_FW_TABLE_ENC = $(BIND_FOLDER)/spi_bootarray_fw_table_enc.bin
SPI_BOOTARRAY_FW_TABLE_DIGEST = $(BIND_FOLDER)/spi_bootarray_fw_table_digest.bin
SPI_BOOTARRAY_FW_TABLE_DIGEST_ENC = $(BIND_FOLDER)/spi_bootarray_fw_table_digest_enc.bin
SPI_BOOTARRAY_FW_TABLE_FINAL = $(BIND_FOLDER)/spi_bootarray_fw_table_final.bin
#nand bootarray fw table 128KB
NAND_BOOTARRAY_FW_TABLE_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_128KB.bin
NAND_BOOTARRAY_FW_TABLE_PADDING_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_padding_128KB.bin
NAND_BOOTARRAY_FW_TABLE_ALL_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_all_128KB.bin
NAND_BOOTARRAY_FW_TABLE_ENC_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_enc_128KB.bin
NAND_BOOTARRAY_FW_TABLE_DIGEST_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_digest_128KB.bin
NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_digest_enc_128KB.bin
NAND_BOOTARRAY_FW_TABLE_FINAL_128KB = $(BIND_FOLDER)/nand_bootarray_fw_table_final_128KB.bin
#nand bootarray fw table 256KB
NAND_BOOTARRAY_FW_TABLE_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_256KB.bin
NAND_BOOTARRAY_FW_TABLE_PADDING_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_padding_256KB.bin
NAND_BOOTARRAY_FW_TABLE_ALL_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_all_256KB.bin
NAND_BOOTARRAY_FW_TABLE_ENC_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_enc_256KB.bin
NAND_BOOTARRAY_FW_TABLE_DIGEST_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_digest_256KB.bin
NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_digest_enc_256KB.bin
NAND_BOOTARRAY_FW_TABLE_FINAL_256KB = $(BIND_FOLDER)/nand_bootarray_fw_table_final_256KB.bin
#NOCS Certificate
NOCS_CERTIFICATE = $(BIND_FOLDER)/NOCS_Certificate.bin
NOCS_CERTIFICATE_DIGEST = $(BIND_FOLDER)/NOCS_Certificate_digest.bin
NOCS_CERTIFICATE_DIGEST_ENC = $(BIND_FOLDER)/NOCS_Certificate_digest_enc.bin
NOCS_CERTIFICATE_FINAL = $(BIND_FOLDER)/NOCS_Certificate_final.bin
#ATF Certificate
ATF_CERTIFICATE = $(BIND_FOLDER)/ATF_Certificate.bin
ATF_CERTIFICATE_DIGEST = $(BIND_FOLDER)/ATF_Certificate_digest.bin
ATF_CERTIFICATE_DIGEST_ENC = $(BIND_FOLDER)/ATF_Certificate_digest_enc.bin
ATF_CERTIFICATE_FINAL = $(BIND_FOLDER)/ATF_Certificate_final.bin
#PCPU Certificate
PCPU_CERTIFICATE = $(BIND_FOLDER)/PCPU_Certificate.bin
PCPU_CERTIFICATE_DIGEST = $(BIND_FOLDER)/PCPU_Certificate_digest.bin
PCPU_CERTIFICATE_DIGEST_ENC = $(BIND_FOLDER)/PCPU_Certificate_digest_enc.bin
PCPU_CERTIFICATE_FINAL = $(BIND_FOLDER)/PCPU_Certificate_final.bin
#DTE_FW Certificate
DTE_FW_CERTIFICATE = $(BIND_FOLDER)/DTE_FW_Certificate.bin
DTE_FW_CERTIFICATE_DIGEST = $(BIND_FOLDER)/DTE_FW_Certificate_digest.bin
DTE_FW_CERTIFICATE_DIGEST_ENC = $(BIND_FOLDER)/DTE_FW_Certificate_digest_enc.bin
DTE_FW_CERTIFICATE_FINAL = $(BIND_FOLDER)/DTE_FW_Certificate_final.bin
#AFW Certificate
AFW_CERTIFICATE = $(BIND_FOLDER)/AFW_Certificate.bin
AFW_CERTIFICATE_DIGEST = $(BIND_FOLDER)/AFW_Certificate_digest.bin
AFW_CERTIFICATE_DIGEST_ENC = $(BIND_FOLDER)/AFW_Certificate_digest_enc.bin
AFW_CERTIFICATE_FINAL = $(BIND_FOLDER)/AFW_Certificate_final.bin
#SCS_Parmas_Area
SCS_PARAMS_AREA = $(BIND_FOLDER)/SCS_Params_Area.bin
SCS_PARAMS_AREA_DIGEST = $(BIND_FOLDER)/SCS_Params_Area_digest.bin
SCS_PARAMS_AREA_DIGEST_ENC = $(BIND_FOLDER)/SCS_Params_Area_digest_enc.bin
SCS_PARAMS_AREA_FINAL= $(BIND_FOLDER)/SCS_Params_Area_final.bin
#RTK_Params_Area
RTK_PARAMS_AREA = $(BIND_FOLDER)/RTK_Params_Area.bin
RTK_PARAMS_AREA_DIGEST = $(BIND_FOLDER)/RTK_Params_Area_digest.bin
RTK_PARAMS_AREA_DIGEST_ENC = $(BIND_FOLDER)/RTK_Params_Area_digest_enc.bin
RTK_PARAMS_AREA_FINAL= $(BIND_FOLDER)/RTK_Params_Area_final.bin

OBFUSE  = $(OBFUSE_DIR)/obfuse
TRUE_SYB             = TRUE
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

ifeq ($(WATCHDOG_CONFIG), "WATCHDOG_ENABLE")
Board_WATCHDOG = RTD299X.watchdog_enable
else
Board_WATCHDOG = RTD299X.watchdog_disable
endif

BINARY_TO_ASCII     = $(TOOLS_DIR)/script/binary2ascii.pl
STR2BIN             = $(TOOLS_DIR)/script/str2bin.pl
REVERSE_BIN         = $(TOOLS_DIR)/script/revsre.pl
BIN2HEX	            = $(TOOLS_DIR)/script/bin2hex.pl
BIN2HEX_EMMC	    = $(TOOLS_DIR)/script/bin2hex_e.pl
REVERSE_RSA         = $(TOOLS_DIR)/script/reverse_rsa_data.pl
REVERSE_PL          = $(TOOLS_DIR)/script/reverse.pl
TMP_RSA_OUT         = rsa_enc.bin
REAL_RSA_OUT        = $(TOP_DIR)/msg.bin
RRMODN              = $(TOP_DIR)/RRModN.bin
NP_INV32            = $(TOP_DIR)/np_inv32.bin

#Thor_HW_keyladder
#from otp 3&4
AES_SCK1_PATH        = $(IMAGE_DIR)/aes_sck_flash1.bin
#from otp 5&6
AES_SCK2_PATH        = $(IMAGE_DIR)/aes_sck_flash2.bin
#from otp 7&8
AES_SCK3_PATH        = $(IMAGE_DIR)/aes_sck_flash3.bin
AES_VENDOR_ID_PATH        = $(IMAGE_DIR)/aes_vendor_id.bin
AES_MODULE_ID_PATH        = $(IMAGE_DIR)/aes_module_id.bin

PRJ_CONFIG_TARGET               = $(PRJ_INC_DIR)/project_config.h
SCPU_RESET_TARGET               = $(TOP_DIR)/bootimage/$(CHIP_ID)/scpu_reset_rom.bin
PCPU_RESET_TARGET               = $(TOP_DIR)/bootimage/$(CHIP_ID)/pcpu_reset_rom.bin
ACPU_RESET_TARGET               = $(TOP_DIR)/bootimage/$(CHIP_ID)/acpu_reset_rom.bin

AUXCODE_TARGET	      		= $(TOP_DIR)/bootimage/$(CHIP_ID)/$(Config_Auxcode_File_Name)
AUXCODE_TARGET_AES			= $(BIND_FOLDER)/auxcode.bin.aes
AUXCODE_AREA				= $(BIND_FOLDER)/Auxcode_Area.bin
AUXCODE_AREA_DIGEST 		= $(BIND_FOLDER)/Auxcode_Area_digest.bin
AUXCODE_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/Auxcode_Area_digest_enc.bin
AUXCODE_AREA_FINAL			= $(BIND_FOLDER)/Auxcode_Area_final.bin

PCPU_AES_KEY					= $(IMAGE_DIR)/pcpu_aes_key.bin
PCPU_CODE_TARGET	      		= $(TOP_DIR)/bootimage/$(CHIP_ID)/$(Config_PCPU_Code_File_Name)
PCPU_CODE_TARGET2	      		= $(BIND_FOLDER)/pcpu_code.bin
PCPU_CODE_TARGET_AES			= $(BIND_FOLDER)/pcpu_code.bin.aes
PCPU_CODE_AREA				= $(BIND_FOLDER)/PCPU_Code_Area.bin
PCPU_CODE_AREA_DIGEST 		= $(BIND_FOLDER)/PCPU_Code_Area_digest.bin
PCPU_CODE_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/PCPU_Code_Area_digest_enc.bin
PCPU_CODE_AREA_FINAL			= $(BIND_FOLDER)/PCPU_Code_Area_final.bin

SECURE_OS_TARGET	      		= $(TOP_DIR)/bootimage/$(CHIP_ID)/$(Config_SECURE_OS_File_Name)
SECURE_OS_TARGET_AES			= $(BIND_FOLDER)/secure_os.bin.aes
SECURE_OS_AREA				= $(BIND_FOLDER)/Secure_OS_Area.bin
SECURE_OS_AREA_DIGEST 		= $(BIND_FOLDER)/Secure_OS_Area_digest.bin
SECURE_OS_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/Secure_OS_Area_digest_enc.bin
SECURE_OS_AREA_FINAL			= $(BIND_FOLDER)/Secure_OS_Area_final.bin

BL31_TARGET	      		= $(TOP_DIR)/bootimage/$(CHIP_ID)/$(Config_BL31_File_Name)
BL31_TARGET_AES			= $(BIND_FOLDER)/bl31.bin.aes
BL31_AREA				= $(BIND_FOLDER)/BL31_Area.bin
BL31_AREA_DIGEST 		= $(BIND_FOLDER)/BL31_Area_digest.bin
BL31_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/BL31_Area_digest_enc.bin
BL31_AREA_FINAL			= $(BIND_FOLDER)/BL31_Area_final.bin

DTE_BOOTCODE_TARGET	      		= $(TOP_DIR)/bootimage/$(CHIP_ID)/$(Config_DTE_Bootcode_File_Name)
DTE_BOOTCODE_TARGET_AES			= $(BIND_FOLDER)/dte_bootcode.bin.aes
DTE_BOOTCODE_AREA				= $(BIND_FOLDER)/DTE_Bootcode_Area.bin
DTE_BOOTCODE_AREA_DIGEST 		= $(BIND_FOLDER)/DTE_Bootcode_Area_digest.bin
DTE_BOOTCODE_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/DTE_Bootcode_Area_digest_enc.bin
DTE_BOOTCODE_AREA_FINAL			= $(BIND_FOLDER)/DTE_Bootcode_Area_final.bin

DTE_BOOTCODE_RTK_TARGET_SIM       = $(TOP_DIR)/bootimage/$(CHIP_ID)/uboot_simulation.bin
ifdef BOOTCODE_IS_LK
	DTE_BOOTCODE_RTK_TARGET       = $(BOOTCODE_LK_PATH)
else
	DTE_BOOTCODE_RTK_TARGET       = $(TOP_DIR)/../../u-boot.bin
endif

DTE_BOOTCODE_RTK_TARGET_AES			= $(BIND_FOLDER)/dte_bootcode_rtk.bin.aes
DTE_BOOTCODE_RTK_AREA				= $(BIND_FOLDER)/DTE_Bootcode_RTK_Area.bin
DTE_BOOTCODE_RTK_AREA_DIGEST 		= $(BIND_FOLDER)/DTE_Bootcode_RTK_Area_digest.bin
DTE_BOOTCODE_RTK_AREA_DIGEST_ENC 	= $(BIND_FOLDER)/DTE_Bootcode_RTK_Area_digest_enc.bin
DTE_BOOTCODE_RTK_AREA_FINAL			= $(BIND_FOLDER)/DTE_Bootcode_RTK_Area_final.bin

#---------------------------NOCS DATA START------------------------------#
NOCS_ARGS= "size_of_scs_params_area="$(Size_of_SCS_Params_Area) \
"address_of_scs_params_area="$(Address_of_SCS_Params_Area) \
"segmentid_ext="$(SegmentID_EXT) \
"mask_msid="$(Mask_MSID) \
"version_ext="$(Version_EXT) \
"mask_vers="$(Mask_Vers) \
"address_of_scs_auxcode_area="$(Address_of_SCS_Auxcode_Area) \
"size_of_scs_auxcode_area="$(Size_of_SCS_Auxcode_Area) \
"address_of_scs_dtebootcode_area="$(Address_of_SCS_DTEBootcode_Area) \
"str_default_region_min_size="$(STR_Default_Region_Min_Size) \
"scrambling_activation="$(Scrambling_Activation) \
"flashprotection_activation="$(FlashProtection_Activation) \
"rskps_activation="$(RSKPS_Activation) \
"scs_total_area_size_1"=$(SCS_Total_Area_Size_1) \
"scs_total_area_size_2"=$(SCS_Total_Area_Size_2) \
"scs_total_area_size_3"=$(SCS_Total_Area_Size_3) \
"scs_total_area_size_4"=$(SCS_Total_Area_Size_4) \
"scs_total_area_size_selection"=$(SCS_Total_Area_Size_Selection)

# ************************ RTK_Params **********************#
NOCS_ARGS+="address_of_bl31_area="$(Address_of_BL31_Area) \
"address_of_teeos_area="$(Address_of_TEEOS_Area) \
"address_of_avfw_area="$(Address_of_AVFW_Area) \
"str_min_size_of_teeos_area="$(STR_Min_Size_of_TEEOS_Area) \
"str_min_size_of_avfw_area="$(STR_Min_Size_of_AVFW_Area) \
"number_of_scramble_key="$(Number_of_Scramble_Key)
#TEE Protect Region
NOCS_ARGS+="address_of_tee_region="$(Address_of_TEE_Region) \
"size_of_tee_region="$(Size_of_TEE_Region) \
"protected_of_tee_region="$(Protected_of_TEE_Region) \
"key_idx_of_tee_region="$(Key_Idx_of_TEE_Region)
# AVFW_TEXT Protect Region
NOCS_ARGS+="address_of_avfw_text_region="$(Address_of_AVFW_TEXT_Region) \
"size_of_avfw_text_region="$(Size_of_AVFW_TEXT_Region) \
"protected_of_avfw_text_region="$(Protected_of_AVFW_TEXT_Region) \
"key_idx_of_avfw_text_region="$(Key_Idx_of_AVFW_TEXT_Region) \
# AVFW_DATA Protect Region
NOCS_ARGS+="address_of_avfw_data_region="$(Address_of_AVFW_DATA_Region) \
"size_of_avfw_data_region="$(Size_of_AVFW_DATA_Region) \
"protected_of_avfw_data_region="$(Protected_of_AVFW_DATA_Region) \
"key_idx_of_avfw_data_region="$(Key_Idx_of_AVFW_DATA_Region)
# AVFW_ISR Protect Region
NOCS_ARGS+="address_of_avfw_isr_region="$(Address_of_AVFW_ISR_Region) \
"size_of_avfw_isr_region="$(Size_of_AVFW_ISR_Region) \
"protected_of_avfw_isr_region="$(Protected_of_AVFW_ISR_Region) \
"key_idx_of_avfw_isr_region="$(Key_Idx_of_AVFW_ISR_Region)
# AVFW_ENTRY Protect Region
NOCS_ARGS+="address_of_avfw_entry_region="$(Address_of_AVFW_ENTRY_Region) \
"size_of_avfw_entry_region="$(Size_of_AVFW_ENTRY_Region) \
"protected_of_avfw_entry_region="$(Protected_of_AVFW_ENTRY_Region) \
"key_idx_of_avfw_entry_region="$(Key_Idx_of_AVFW_ENTRY_Region)
# Video_Pool Protect Region
NOCS_ARGS+="address_of_video_pool_region="$(Address_of_Video_Pool_Region) \
"size_of_video_pool_region="$(Size_of_Video_Pool_Region) \
"protected_of_video_pool_region="$(Protected_of_Video_Pool_Region) \
"key_idx_of_video_pool_region="$(Key_Idx_of_Video_Pool_Region)
# User Protect Region
NOCS_ARGS+="address_of_user_region="$(Address_of_User_Region) \
"size_of_user_region="$(Size_of_User_Region) \
"protected_of_user_region="$(Protected_of_User_Region) \
"key_idx_of_user_region="$(Key_Idx_of_User_Region)
# REE Region 1
NOCS_ARGS+="address_of_ree_region_1="$(Address_of_REE_Region_1) \
"size_of_ree_region_1="$(Size_of_REE_Region_1) \
"key_idx_of_ree_region_1="$(Key_Idx_of_REE_Region_1)
# REE Region 2
NOCS_ARGS+="address_of_ree_region_2="$(Address_of_REE_Region_2) \
"size_of_ree_region_2="$(Size_of_REE_Region_2) \
"key_idx_of_ree_region_2="$(Key_Idx_of_REE_Region_2)
# REE Region 3
NOCS_ARGS+="address_of_ree_region_3="$(Address_of_REE_Region_3) \
"size_of_ree_region_3="$(Size_of_REE_Region_3) \
"key_idx_of_ree_region_3="$(Key_Idx_of_REE_Region_3)
# REE Region 4
NOCS_ARGS+="address_of_ree_region_4="$(Address_of_REE_Region_4) \
"size_of_ree_region_4="$(Size_of_REE_Region_4) \
"key_idx_of_ree_region_4="$(Key_Idx_of_REE_Region_4)
# REE Region 5
NOCS_ARGS+="address_of_ree_region_5="$(Address_of_REE_Region_5) \
"size_of_ree_region_5="$(Size_of_REE_Region_5) \
"key_idx_of_ree_region_5="$(Key_Idx_of_REE_Region_5)
# REE Region 6
NOCS_ARGS+="address_of_ree_region_6="$(Address_of_REE_Region_6) \
"size_of_ree_region_6="$(Size_of_REE_Region_6) \
"key_idx_of_ree_region_6="$(Key_Idx_of_REE_Region_6)
# REE Region 7
NOCS_ARGS+="address_of_ree_region_7="$(Address_of_REE_Region_7) \
"size_of_ree_region_7="$(Size_of_REE_Region_7) \
"key_idx_of_ree_region_7="$(Key_Idx_of_REE_Region_7)
# REE Region 8
NOCS_ARGS+="address_of_ree_region_8="$(Address_of_REE_Region_8) \
"size_of_ree_region_8="$(Size_of_REE_Region_8) \
"key_idx_of_ree_region_8="$(Key_Idx_of_REE_Region_8)

NOCS_ARGS+="str_default_region_start_address="$(STR_Default_Region_Start_Address) \
"str_resume_mode="$(STR_Resume_Mode) \
"str_address_of_bl31_area="$(STR_Address_of_BL31_Area) \
"str_size_of_bl31_area="$(STR_Size_of_BL31_Area) \
"teeos_segmentid_ext="$(TEEOS_SegmentID_EXT) \
"teeos_mask_msid="$(TEEOS_Mask_MSID) \
"teeos_version_ext="$(TEEOS_Version_EXT) \
"teeos_mask_vers="$(TEEOS_Mask_Vers) \
"pcpu_fw_version_ext="$(PCPU_FW_Version_EXT) \
"pcpu_fw_segmentid_ext="$(PCPU_FW_SegmentID_EXT)

#hwsetting 8KB binary in SCS_Params's External_Ram_Params
NOCS_ARGS += "hwsetting_file_path="$(HW_SETTING_TARGET)

#sign key in certificate
NOCS_ARGS += "scs_external_pub_rsa_key="$(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY).bin.rev \
"atf_external_pub_rsa_key="$(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY).bin.rev \
"pcpu_external_pub_rsa_key="$(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY).bin.rev \
"dte_fw_external_pub_rsa_key="$(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY).bin.rev \
"afw_external_pub_rsa_key="$(IMAGE_DIR)/$(AFW_EXTERNAL_PUBLIC_RSA_KEY).bin.rev

#aes_enc key in Parms area
NOCS_ARGS += "flash_protection_key="$(IMAGE_DIR)/$(FlashProtectionKey) \
"nagrata_protection_key="$(IMAGE_DIR)/$(NagraTAProtectionKey) \
"atf_protection_key="$(IMAGE_DIR)/$(ATFProtectionKey) \
"dte_protection_key="$(IMAGE_DIR)/$(DTEProtectionKey)

NOCS_ARGS +="auxcode_file_path="$(AUXCODE_TARGET) \
"pcpu_code_file_path="$(PCPU_CODE_TARGET) \
"dte_bootcode_file_path="$(DTE_BOOTCODE_TARGET) \
"dte_bootcode_rtk_file_path="$(DTE_BOOTCODE_RTK_TARGET)

ifeq ($(Config_SECURE_OS), TRUE)
	NOCS_ARGS +="secure_os_file_path="$(SECURE_OS_TARGET)
endif

ifeq ($(Config_BL31), TRUE)
	NOCS_ARGS +="bl31_file_path="$(BL31_TARGET)
endif


TARGET_EXE             = $(TOP_DIR)/dvrboot.exe

STR2BIN                = $(SCRIPT_DIR)/str2bin.pl
PACKAGE_TARGET         = $(PACKAGE_DIR)/package_MP.tar


ifeq ($(ENV), $(CYGWIN_ENV))
	HW_SETTING_MAKER_AP	= generate_config.exe
	RTSSL_EXE = $(RTSSL_DIR)/RtSSL.exe
	SHA_EXE = $(SHA_DIR)/do_sha256.exe
	INVERSE = inverse.exe
	NF_PROFILER_EXE = $(NF_PROFILER_DIR)/nf_profiler.exe
endif

ifeq ($(ENV), $(LINUX_ENV))
	HW_SETTING_MAKER_AP	= generate_config
	RTSSL_EXE = $(RTSSL_DIR)/RtSSL
	SHA_EXE = $(SHA_DIR)/do_sha256
	INVERSE = inverse
	NF_PROFILER_EXE = $(NF_PROFILER_DIR)/nf_profiler
endif

PACKAGE_PRJ_CONFIG = $(PACKAGE_DIR)/project_config.h
PACKAGE_BOOTCODE   = $(PACKAGE_DIR)/boot_target.bin

BIN_ARGS = "scpu_resetrom="$(SCPU_RESET_TARGET)
BIN_ARGS += "pcpu_resetrom="$(PCPU_RESET_TARGET)
BIN_ARGS += "acpu_resetrom="$(ACPU_RESET_TARGET)
BIN_ARGS += "acpu_resetrom="$(ACPU_RESET_TARGET)
BIN_ARGS += "nocs_certificate="$(NOCS_CERTIFICATE_FINAL)
BIN_ARGS += "atf_certificate="$(ATF_CERTIFICATE_FINAL)
BIN_ARGS += "pcpu_certificate="$(PCPU_CERTIFICATE_FINAL)
BIN_ARGS += "dte_fw_certificate="$(DTE_FW_CERTIFICATE_FINAL)
BIN_ARGS += "afw_certificate="$(AFW_CERTIFICATE_FINAL)
BIN_ARGS += "scs_params_area="$(SCS_PARAMS_AREA_FINAL)
BIN_ARGS += "rtk_params_area="$(RTK_PARAMS_AREA_FINAL)
BIN_ARGS += "auxcode_area="$(AUXCODE_AREA_FINAL)
BIN_ARGS += "pcpu_code_area="$(PCPU_CODE_AREA_FINAL)
BIN_ARGS += "dte_bootcode_area="$(DTE_BOOTCODE_AREA_FINAL)
BIN_ARGS += "dte_bootcode_rtk_area="$(DTE_BOOTCODE_RTK_AREA_FINAL)

ifeq ($(Config_SECURE_OS), TRUE)
    BIN_ARGS += "secure_os="$(SECURE_OS_AREA_FINAL)
endif

ifeq ($(Config_BL31), TRUE)
    BIN_ARGS += "bl31="$(BL31_AREA_FINAL)
endif

#Thor hwrsa doesn't require r^2 mod n and np_inv
hwrsa-sign-npinv64 =                                                                                          \
    $(OPENSSL) rsa -text -in $(1) -out $(1).text;                                           \
	$(OPENSSL) rsautl -inkey $(1) -sign -in $(2) -out $(TMP_RSA_OUT);			\
	$(GEN_RSA_PATTERN) --key $(1).text --msg $(TMP_RSA_OUT) --binary;      \
	cat $(REAL_RSA_OUT) > $(3)
	#cat $(REAL_RSA_OUT) $(RRMODN) $(NP_INV32) > $(3)

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
COBJS	:= dvrmain.o util.o flashdev_n.o flashdev_s.o flashdev_e.o rtkemmc.o strlen.o strstr.o strtoul.o ctype.o mcp.o otp.o timer.o cache.o BootPartition_wrapper.o dprintf.o
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

# We don't want gcc reordering functions if possible.  This ensures that an
# application's entry point will be the first function in the application's
# source file.
#CFLAGS_NTR := $(call cc-option,-fno-toplevel-reorder)
#CFLAGS += $(CFLAGS_NTR) -I$(INCLUDE_DIR)
#CFLAGS = -g -Os -fno-common -ffixed-r8 -msoft-float  -D__KERNEL__ -fno-builtin -ffreestanding -nostdinc -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__ -marm  -mabi=aapcs-linux -mno-thumb-interwork -march=armv7-a  -Wall -Wstrict-prototypes -fno-stack-protector -Wno-format-nonliteral -Wno-format-security  -fno-toplevel-reorder
CFLAGS = -g -Os -fno-common -ffixed-r8 -D__KERNEL__ -fno-builtin -ffreestanding -isystem $(gcclibdir)/../include -pipe  -DCONFIG_ARM -D__ARM__  -march=armv8-a -D__EL__ -D__ARM_ARCH_8A__
#CFLAGS += -msoft-float -marm -mabi=aapcs-linux -mno-thumb-interwork

ifeq ($(Board_CPU), RTD1295)
    CFLAGS += -DCONFIG_RTD1295
endif

CFLAGS += $(INCDIRS)
all:	clean configconv bind_folder b2a get_config $(OBJS) $(SSOBJS) $(LIB) $(ELF) $(SREC) $(BIN)

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
	-rm -f $(TOP_DIR)/image/aes_128bit_key.bin.enc
	-rm -f $(TOP_DIR)/image/aes_128bit_key_1.bin.enc
	-rm -f $(TOP_DIR)/image/aes_128bit_key_2.bin.enc
	-rm -f $(TOP_DIR)/image/aes_128bit_key_3.bin.enc
	-rm -f $(TOP_DIR)/image/rsa_key_2048.fw.pem.text
	-rm -f $(TOP_DIR)/image/rsa_key1_2048.pem.bin
	-rm -f $(TOP_DIR)/image/rsa_key1_2048.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key1_2048.pem.text
	-rm -f $(TOP_DIR)/image/rsa_key2_2048.pem.bin
	-rm -f $(TOP_DIR)/image/rsa_key2_2048.pem.bin.rev
	-rm -f $(TOP_DIR)/image/rsa_key2_2048.pem.text
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
		cat $(DTE_BOOTCODE_RTK_AREA_FINAL) > install_a/lk.bin
		cat $(NAND_BOOTARRAY_FW_TABLE_FINAL_128KB) > install_a/bootarray_fw_table_128KB.bin
		cat $(NAND_BOOTARRAY_FW_TABLE_FINAL_256KB) > install_a/bootarray_fw_table_256KB.bin
		cat $(NOCS_CERTIFICATE_FINAL) $(SCS_PARAMS_AREA_FINAL) > install_a/scs_area.bin
		cat $(AUXCODE_AREA_FINAL) > install_a/auxcode.bin
		cat $(DTE_BOOTCODE_AREA_FINAL) > install_a/dte_bootcode.bin
		cat $(ATF_CERTIFICATE_FINAL) $(PCPU_CERTIFICATE_FINAL) $(AFW_CERTIFICATE_FINAL) $(DTE_FW_CERTIFICATE_FINAL) > install_a/certificate_area.bin
		cat $(RTK_PARAMS_AREA_FINAL) > install_a/rtk_params.bin

ifeq ($(Config_SECURE_OS), TRUE)
		cat $(SECURE_OS_AREA_FINAL) > install_a/tee_area.bin
endif
ifeq ($(Config_BL31), TRUE)
		cat $(BL31_AREA_FINAL) > install_a/bl31_area.bin
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


$(LOGO_CHANGER):
	cd $(LOGO_CHANGER_DIR);\
	make

$(RTSSL_EXE):
	cd $(RTSSL_DIR);\
	make LIB_PATH=/usr/lib64 STATIC_LINK=N


$(HW_SETTING_MAKER_AP):
	$(CD) $(HW_SETTING_MAKER_DIR);\
	make;

$(BINDALLBIN_UTIL):
	$(CD) $(BINDALLBIN_MAKER_DIR);\
	make clean;make;

bind_folder:  $(BINDALLBIN_UTIL)
	#bind stuff
	@mkdir $(BIND_FOLDER);
	@cp $(SCPU_RESET_TARGET) $(BIND_FOLDER)/scpu_reset_rom.bin;
	@cp $(PCPU_RESET_TARGET) $(BIND_FOLDER)/pcpu_reset_rom.bin;
	@cp $(ACPU_RESET_TARGET) $(BIND_FOLDER)/acpu_reset_rom.bin;

$(SHA_EXE):
	cd $(SHA_DIR);\
	rm do_sha256;\
	make

$(NF_PROFILER_EXE):
	cd $(NF_PROFILER_DIR);\
	make clean; make;
rsa_key: $(RTSSL_EXE)
	chmod +x reverse.pl
	chmod +x bin2ascii
	chmod +x $(RTSSL_EXE)
	chmod +x $(STR2BIN)
	chmod +x $(REVERSE_PL)
	chmod +x $(BINARY_TO_ASCII)
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(SCS_ROOT_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(SCS_ROOT_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(SCS_ROOT_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(SCS_ROOT_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY).bin.rev
	$(STR2BIN) `$(RTSSL_EXE) rsa -print -modulous -i $(IMAGE_DIR)/$(AFW_EXTERNAL_PUBLIC_RSA_KEY)` > $(IMAGE_DIR)/$(AFW_EXTERNAL_PUBLIC_RSA_KEY).bin
	$(REVERSE_PL) $(IMAGE_DIR)/$(AFW_EXTERNAL_PUBLIC_RSA_KEY).bin > $(IMAGE_DIR)/$(AFW_EXTERNAL_PUBLIC_RSA_KEY).bin.rev

nocs_data_block:
	# obfuse 10: nagra_ta_protection_root_key, 12: atf_protection_root_key, 14: dte_protection_root_key, 18: aux_protection_key

ifeq ($(FlashProtectionRootKey), "")
	$(OBFUSE) $(RTSSL_EXE) 18 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(IMAGE_DIR)/$(FlashProtectionKey) $(IMAGE_DIR)/$(FlashProtectionKey).enc
else ifndef FlashProtectionRootKey
	$(OBFUSE) $(RTSSL_EXE) 18 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(IMAGE_DIR)/$(FlashProtectionKey) $(IMAGE_DIR)/$(FlashProtectionKey).enc
else
	openssl enc -e -aes-128-ecb -K `hexdump -e '16/1 "%02x"' $(IMAGE_DIR)/$(FlashProtectionRootKey)` -nopad -in $(IMAGE_DIR)/$(FlashProtectionKey) -out $(IMAGE_DIR)/$(FlashProtectionKey).enc
endif

	$(OBFUSE) $(RTSSL_EXE) 10 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(IMAGE_DIR)/$(NagraTAProtectionKey) $(IMAGE_DIR)/$(NagraTAProtectionKey).enc
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(IMAGE_DIR)/$(ATFProtectionKey) $(IMAGE_DIR)/$(ATFProtectionKey).enc
	$(OBFUSE) $(RTSSL_EXE) 14 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(IMAGE_DIR)/$(DTEProtectionKey) $(IMAGE_DIR)/$(DTEProtectionKey).enc
	$(OBFUSE) $(RTSSL_EXE) 18 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(AUXCODE_TARGET) $(AUXCODE_TARGET_AES)
	#openssl enc -e -aes-128-cbc -K `hexdump -e '16/1 "%02x"' $(PCPU_AES_KEY)` -nopad -iv 00000000000000000000000000000000 -in $(PCPU_CODE_TARGET) -out $(PCPU_CODE_TARGET_AES)
ifneq ($(FlashProtection_Activation), 0x0)
	openssl enc -e -aes-128-ecb -K `hexdump -e '16/1 "%02x"' $(IMAGE_DIR)/$(FlashProtectionKey)` -nopad -in $(DTE_BOOTCODE_TARGET) -out $(DTE_BOOTCODE_TARGET_AES)
endif

	./nocs_data_maker.pl $(NOCS_ARGS)
	#generate NOCS_CERTIFICATE_FINAL
	$(SHA_EXE) $(NOCS_CERTIFICATE) tmp_padding.bin $(NOCS_CERTIFICATE_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(SCS_ROOT_PUBLIC_RSA_KEY), $(NOCS_CERTIFICATE_DIGEST), $(NOCS_CERTIFICATE_DIGEST_ENC))
	cat $(NOCS_CERTIFICATE) $(NOCS_CERTIFICATE_DIGEST_ENC) > $(NOCS_CERTIFICATE_FINAL)
	#generate ATF_CERTIFICATE_FINAL
	$(SHA_EXE) $(ATF_CERTIFICATE) tmp_padding.bin $(ATF_CERTIFICATE_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY), $(ATF_CERTIFICATE_DIGEST), $(ATF_CERTIFICATE_DIGEST_ENC))
	cat $(ATF_CERTIFICATE) $(ATF_CERTIFICATE_DIGEST_ENC) > $(ATF_CERTIFICATE_FINAL)
	#generate PCPU_CERTIFICATE_FINAL
	$(SHA_EXE) $(PCPU_CERTIFICATE) tmp_padding.bin $(PCPU_CERTIFICATE_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY), $(PCPU_CERTIFICATE_DIGEST), $(PCPU_CERTIFICATE_DIGEST_ENC))
	cat $(PCPU_CERTIFICATE) $(PCPU_CERTIFICATE_DIGEST_ENC) > $(PCPU_CERTIFICATE_FINAL)
	#generate DTE_FW_CERTIFICATE_FINAL
	$(SHA_EXE) $(DTE_FW_CERTIFICATE) tmp_padding.bin $(DTE_FW_CERTIFICATE_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY), $(DTE_FW_CERTIFICATE_DIGEST), $(DTE_FW_CERTIFICATE_DIGEST_ENC))
	cat $(DTE_FW_CERTIFICATE) $(DTE_FW_CERTIFICATE_DIGEST_ENC) > $(DTE_FW_CERTIFICATE_FINAL)
	#generate AFW_CERTIFICATE_FINAL
	$(SHA_EXE) $(AFW_CERTIFICATE) tmp_padding.bin $(AFW_CERTIFICATE_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(TEE_ROOT_PUBLIC_RSA_KEY), $(AFW_CERTIFICATE_DIGEST), $(AFW_CERTIFICATE_DIGEST_ENC))
	cat $(AFW_CERTIFICATE) $(AFW_CERTIFICATE_DIGEST_ENC) > $(AFW_CERTIFICATE_FINAL)
	#generate SCS_Params
	$(SHA_EXE) $(SCS_PARAMS_AREA) tmp_padding.bin $(SCS_PARAMS_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY), $(SCS_PARAMS_AREA_DIGEST), $(SCS_PARAMS_AREA_DIGEST_ENC))
	cat $(SCS_PARAMS_AREA).tmp1 $(HW_SETTING_TARGET) $(SCS_PARAMS_AREA).tmp2 $(IMAGE_DIR)/$(FlashProtectionKey).enc $(SCS_PARAMS_AREA_DIGEST_ENC) > $(SCS_PARAMS_AREA_FINAL)
	#generate RTK_Params
	$(SHA_EXE) $(RTK_PARAMS_AREA) tmp_padding.bin $(RTK_PARAMS_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY), $(RTK_PARAMS_AREA_DIGEST), $(RTK_PARAMS_AREA_DIGEST_ENC))
	cat $(RTK_PARAMS_AREA).tmp $(IMAGE_DIR)/$(ATFProtectionKey).enc $(IMAGE_DIR)/$(DTEProtectionKey).enc $(RTK_PARAMS_AREA_DIGEST_ENC) > $(RTK_PARAMS_AREA_FINAL)
	#generate Auxcode_Area
	$(SHA_EXE) $(AUXCODE_AREA) tmp_padding.bin $(AUXCODE_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY), $(AUXCODE_AREA_DIGEST), $(AUXCODE_AREA_DIGEST_ENC))
	cat $(AUXCODE_TARGET_AES) $(AUXCODE_AREA).tmp $(AUXCODE_AREA_DIGEST_ENC) > $(AUXCODE_AREA_FINAL)
	#generate PCPU_Code_Area
	$(SHA_EXE) $(PCPU_CODE_AREA) tmp_padding.bin $(PCPU_CODE_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(PCPU_EXTERNAL_PUBLIC_RSA_KEY), $(PCPU_CODE_AREA_DIGEST), $(PCPU_CODE_AREA_DIGEST_ENC))
	openssl enc -e -aes-128-cbc -K `hexdump -e '16/1 "%02x"' $(PCPU_AES_KEY)` -nopad -iv 00000000000000000000000000000000 -in $(PCPU_CODE_TARGET2) -out $(PCPU_CODE_TARGET_AES)
	cat $(PCPU_CODE_TARGET_AES) $(PCPU_CODE_AREA).tmp $(PCPU_CODE_AREA_DIGEST_ENC) > $(PCPU_CODE_AREA_FINAL)
	#generate DTE_Bootcode_Area
	$(SHA_EXE) $(DTE_BOOTCODE_AREA) tmp_padding.bin $(DTE_BOOTCODE_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(SCS_EXTERNAL_PUBLIC_RSA_KEY), $(DTE_BOOTCODE_AREA_DIGEST), $(DTE_BOOTCODE_AREA_DIGEST_ENC))
ifneq ($(FlashProtection_Activation), 0x0)
	cat $(DTE_BOOTCODE_TARGET_AES) $(DTE_BOOTCODE_AREA).tmp $(DTE_BOOTCODE_AREA_DIGEST_ENC) > $(DTE_BOOTCODE_AREA_FINAL)
else
	cat $(DTE_BOOTCODE_AREA) $(DTE_BOOTCODE_AREA_DIGEST_ENC) > $(DTE_BOOTCODE_AREA_FINAL)
endif

hw_setting: $(HW_SETTING_MAKER_AP)
	$(HW_SETTING_MAKER_DIR)/$(HW_SETTING_MAKER_AP) $(HW_SETTING_TARGET_RAW_FILE) $(HW_SETTING_TARGET)
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(HW_SETTING_TARGET) $(HW_SETTING_TARGET_ENC)
	$(SHA_EXE) $(HW_SETTING_TARGET) tmp_padding.bin $(HW_SETTING_TARGET_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(BOOTARRAY_FW_TABLE_RSA_KEY), $(HW_SETTING_TARGET_DIGEST), $(HW_SETTING_TARGET_DIGEST_ENC))
	cat $(HW_SETTING_TARGET_ENC) $(HW_SETTING_TARGET_DIGEST_ENC) > $(HW_SETTING_TARGET_FINAL)

b2a: rsa_key hw_setting copy_bootcode_target $(SHA_EXE) $(NF_PROFILER_EXE) nocs_data_block secure_os bl31 target_encrypt
	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL) fw_table
	#eMMC bootarray fw table encrypt&sign
	$(SHA_EXE) $(EMMC_BOOTARRAY_FW_TABLE) $(EMMC_BOOTARRAY_FW_TABLE_PADDING) $(EMMC_BOOTARRAY_FW_TABLE_DIGEST)
	cat $(EMMC_BOOTARRAY_FW_TABLE) $(EMMC_BOOTARRAY_FW_TABLE_PADDING) > $(EMMC_BOOTARRAY_FW_TABLE_ALL)
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(BOOTARRAY_FW_TABLE_RSA_KEY), $(EMMC_BOOTARRAY_FW_TABLE_DIGEST), $(EMMC_BOOTARRAY_FW_TABLE_DIGEST_ENC))
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(EMMC_BOOTARRAY_FW_TABLE_ALL) $(EMMC_BOOTARRAY_FW_TABLE_ENC)
	cat $(EMMC_BOOTARRAY_FW_TABLE_ENC) $(EMMC_BOOTARRAY_FW_TABLE_DIGEST_ENC) > $(EMMC_BOOTARRAY_FW_TABLE_FINAL)
	#SPI bootarray fw table encrypt&sign
	$(SHA_EXE) $(SPI_BOOTARRAY_FW_TABLE) $(SPI_BOOTARRAY_FW_TABLE_PADDING) $(SPI_BOOTARRAY_FW_TABLE_DIGEST)
	cat $(SPI_BOOTARRAY_FW_TABLE) $(SPI_BOOTARRAY_FW_TABLE_PADDING) > $(SPI_BOOTARRAY_FW_TABLE_ALL)
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(BOOTARRAY_FW_TABLE_RSA_KEY), $(SPI_BOOTARRAY_FW_TABLE_DIGEST), $(SPI_BOOTARRAY_FW_TABLE_DIGEST_ENC))
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(SPI_BOOTARRAY_FW_TABLE_ALL) $(SPI_BOOTARRAY_FW_TABLE_ENC)
	cat $(SPI_BOOTARRAY_FW_TABLE_ENC) $(SPI_BOOTARRAY_FW_TABLE_DIGEST_ENC) > $(SPI_BOOTARRAY_FW_TABLE_FINAL)
	#NAND bootarray fw table encrypt&sign 128KB
	$(SHA_EXE) $(NAND_BOOTARRAY_FW_TABLE_128KB) $(NAND_BOOTARRAY_FW_TABLE_PADDING_128KB) $(NAND_BOOTARRAY_FW_TABLE_DIGEST_128KB)
	cat $(NAND_BOOTARRAY_FW_TABLE_128KB) $(NAND_BOOTARRAY_FW_TABLE_PADDING_128KB) > $(NAND_BOOTARRAY_FW_TABLE_ALL_128KB)
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(BOOTARRAY_FW_TABLE_RSA_KEY), $(NAND_BOOTARRAY_FW_TABLE_DIGEST_128KB), $(NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_128KB))
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(NAND_BOOTARRAY_FW_TABLE_ALL_128KB) $(NAND_BOOTARRAY_FW_TABLE_ENC_128KB)
	cat $(NAND_BOOTARRAY_FW_TABLE_ENC_128KB) $(NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_128KB) > $(NAND_BOOTARRAY_FW_TABLE_FINAL_128KB)
	#NAND bootarray fw table encrypt&sign 256KB
	$(SHA_EXE) $(NAND_BOOTARRAY_FW_TABLE_256KB) $(NAND_BOOTARRAY_FW_TABLE_PADDING_256KB) $(NAND_BOOTARRAY_FW_TABLE_DIGEST_256KB)
	cat $(NAND_BOOTARRAY_FW_TABLE_256KB) $(NAND_BOOTARRAY_FW_TABLE_PADDING_256KB) > $(NAND_BOOTARRAY_FW_TABLE_ALL_256KB)
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(BOOTARRAY_FW_TABLE_RSA_KEY), $(NAND_BOOTARRAY_FW_TABLE_DIGEST_256KB), $(NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_256KB))
	$(OBFUSE) $(RTSSL_EXE) 12 $(AES_SCK1_PATH) $(AES_VENDOR_ID_PATH) $(AES_MODULE_ID_PATH) $(NAND_BOOTARRAY_FW_TABLE_ALL_256KB) $(NAND_BOOTARRAY_FW_TABLE_ENC_256KB)
	cat $(NAND_BOOTARRAY_FW_TABLE_ENC_256KB) $(NAND_BOOTARRAY_FW_TABLE_DIGEST_ENC_256KB) > $(NAND_BOOTARRAY_FW_TABLE_FINAL_256KB)

	$(BINDALLBIN_MAKER_DIR)/$(BINDALLBIN_UTIL)
	$(BIN2HEX) $(BIND_FOLDER)/bind.bin $(BIND_FOLDER)/bind.bin.hex
	$(BIN2HEX_EMMC) 0 $(BIND_FOLDER)/uda_emmc.bind.bin $(BIND_FOLDER)/uda_emmc.bind.bin.hex
	$(BIN2HEX_EMMC) 1 $(BIND_FOLDER)/boot_emmc.bind.bin $(BIND_FOLDER)/boot_emmc.bind.bin.hex
	./bin2ascii $(BIN_ARGS) > temp_target_array.h

$(INVERSE):
	cc inverse.c -o $(INVERSE);\
	chmod +x $(INVERSE)

copy_bootcode_target: $(INVERSE)
ifeq ($(Config_Uboot_Sim_Mode), TRUE)
	cp $(DTE_BOOTCODE_RTK_TARGET_SIM) ./u-boot.bin
	cat $(DTE_BOOTCODE_RTK_TARGET_SIM) > $(DTE_BOOTCODE_RTK_TARGET)
endif
	cp $(DTE_BOOTCODE_RTK_TARGET) .


target_encrypt: $(SHA_EXE)
	#generate DTE_Bootcode_RTK_Area
	$(SHA_EXE) $(DTE_BOOTCODE_RTK_AREA) tmp_padding.bin $(DTE_BOOTCODE_RTK_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(DTE_FW_EXTERNAL_PUBLIC_RSA_KEY), $(DTE_BOOTCODE_RTK_AREA_DIGEST), $(DTE_BOOTCODE_RTK_AREA_DIGEST_ENC))
ifeq ($(Config_Secure_Improve), TRUE)
	openssl enc -e -aes-128-ecb -K `hexdump -e '16/1 "%02x"' $(IMAGE_DIR)/$(DTEProtectionKey)` -nopad -in $(DTE_BOOTCODE_RTK_TARGET) -out $(DTE_BOOTCODE_RTK_TARGET_AES)
	cat $(DTE_BOOTCODE_RTK_TARGET_AES) $(DTE_BOOTCODE_RTK_AREA).tmp $(DTE_BOOTCODE_RTK_AREA_DIGEST_ENC) > $(DTE_BOOTCODE_RTK_AREA_FINAL)
else
	cat $(DTE_BOOTCODE_RTK_AREA) $(DTE_BOOTCODE_RTK_AREA_DIGEST_ENC) > $(DTE_BOOTCODE_RTK_AREA_FINAL)
endif

secure_os:
ifeq ($(Config_SECURE_OS), TRUE)
	$(SHA_EXE) $(SECURE_OS_AREA) tmp_padding.bin $(SECURE_OS_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY), $(SECURE_OS_AREA_DIGEST), $(SECURE_OS_AREA_DIGEST_ENC))
	openssl enc -e -aes-128-ecb -K `hexdump -e '16/1 "%02x"' $(IMAGE_DIR)/$(ATFProtectionKey)` -nopad -in $(SECURE_OS_TARGET) -out $(SECURE_OS_TARGET_AES)
	cat $(SECURE_OS_TARGET_AES) $(SECURE_OS_AREA).tmp $(SECURE_OS_AREA_DIGEST_ENC) > $(SECURE_OS_AREA_FINAL)
endif

bl31:
ifeq ($(Config_BL31), TRUE)
	$(SHA_EXE) $(BL31_AREA) tmp_padding.bin $(BL31_AREA_DIGEST);rm tmp_padding.bin
	$(call hwrsa-sign-npinv64, $(IMAGE_DIR)/$(ATF_EXTERNAL_PUBLIC_RSA_KEY), $(BL31_AREA_DIGEST), $(BL31_AREA_DIGEST_ENC))
	openssl enc -e -aes-128-ecb -K `hexdump -e '16/1 "%02x"' $(IMAGE_DIR)/$(ATFProtectionKey)` -nopad -in $(BL31_TARGET) -out $(BL31_TARGET_AES)
	cat $(BL31_TARGET_AES) $(BL31_AREA).tmp $(BL31_AREA_DIGEST_ENC) > $(BL31_AREA_FINAL)
endif


get_config:
	$(SED) -i 's/Config_FLASH_TYPE.*/$(FLASH_TYPE)/g' $(INCLUDE_DIR)/project_config_f.h;
