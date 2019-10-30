# ********************************************************************
# Board Components
# ********************************************************************
# flag                      value
# ********************************************************************
Board_CPU =                 RTD161x
##Board_Chip_Rev =          [161x]
Board_Chip_Rev =            161x

Board_HWSETTING =          RTD161x_hwsetting_BOOT_2DDR4_8Gb_s2666


# ********************************************************************
# Thor Sign Keys
# ********************************************************************
SCS_ROOT_PUBLIC_RSA_KEY = "rsa_key1_2048.pem"
TEE_ROOT_PUBLIC_RSA_KEY = "rsa_key2_2048.pem"
BOOTARRAY_FW_TABLE_RSA_KEY = "bootarray_fw_table_rsa_key.pem"
SCS_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
ATF_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
PCPU_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
DTE_FW_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.fw.pem"
AFW_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.fw.pem"

# ********************************************************************
# NOCS Certificate and Params Attributes
# ********************************************************************
#Size_of_SCS_Params_Area is fixed to 0x2200
Address_of_SCS_Params_Area = 0x8001d668
SegmentID_EXT = 0x0
Mask_MSID =  0x0
Version_EXT = 0x0
Mask_Vers = 0xFFFFFFFF

#DTE_Bootcode_RTK_Area will be padding to this fixed size
Size_of_DTEBootcode_RTK_Area=0x100000

#*****************SCS_Params*******************
Address_of_SCS_Auxcode_Area = 0x80000000
#Size_of_SCS_Auxcode_Area is fixed to 64KB
Address_of_SCS_DTEBootcode_Area = 0x10120000
#Size_of_SCS_DTEBootcode_Area will be calculated in nocs_data_maker.pl according to the total are size
#Flash_Address_of_SCS_Auxcode_Area is fixed to 0x2600: NOCS_Certificate size (0x400) + SCS_Params size (8552 aligned to 8704=0x2200)
#Flash_Address_of_SCS_DTE_Boot_Code_Area is fixed to 0x12600: Auxcode Area Flash address + 64KB(0x10000)
STR_Default_Region_Min_Size = 0xC00000
Scrambling_Activation = 0x0
FlashProtection_Activation = 0x1
RSKPS_Activation = 0x0

#1: 352KB
#2: 512KB
#3: 768KB
#4: 1024KB

# NOTICE start: Please don't change the format of variables as below, otherwise, you have to change the build_fig.sh
SCS_Total_Area_Size_1 = 0x2B000
SCS_Total_Area_Size_2 = 0x80000
SCS_Total_Area_Size_3 = 0xc0000
SCS_Total_Area_Size_4 = 0x100000
SCS_Total_Area_Size_Selection = 0x1
# NOTICE end

FlashProtectionKey = "aes_128bit_key.bin"
#FlashProtectionRootKey = "flash_protection_root_key.bin"
PCPU_AES_KEY = $(IMAGE_DIR)/pcpu_aes_key.bin

#*****************RTK_Params*******************
Address_of_BL31_Area = 0
Address_of_TEEOS_Area = 0
Address_of_AVFW_Area = 0
STR_Min_Size_of_TEEOS_Area = 0
STR_Min_Size_of_AVFW_Area = 0
Number_of_Scramble_Key = 0

# TEE Protect Region
Address_of_TEE_Region = 0
Size_of_TEE_Region = 0
Protected_of_TEE_Region = 0
Key_Idx_of_TEE_Region = 0

# AVFW_TEXT Protect Region
Address_of_AVFW_TEXT_Region = 0
Size_of_AVFW_TEXT_Region = 0
Protected_of_AVFW_TEXT_Region = 0
Key_Idx_of_AVFW_TEXT_Region = 0

# AVFW_DATA Protect Region
Address_of_AVFW_DATA_Region = 0
Size_of_AVFW_DATA_Region = 0
Protected_of_AVFW_DATA_Region = 0
Key_Idx_of_AVFW_DATA_Region = 0

# AVFW_ISR Protect Region
Address_of_AVFW_ISR_Region = 0
Size_of_AVFW_ISR_Region = 0
Protected_of_AVFW_ISR_Region = 0
Key_Idx_of_AVFW_ISR_Region = 0

# AVFW_ENTRY Protect Region
Address_of_AVFW_ENTRY_Region = 0
Size_of_AVFW_ENTRY_Region = 0
Protected_of_AVFW_ENTRY_Region = 0
Key_Idx_of_AVFW_ENTRY_Region = 0

#Video_Pool Protect Region
Address_of_Video_Pool_Region = 0
Size_of_Video_Pool_Region = 0
Protected_of_Video_Pool_Region = 0
Key_Idx_of_Video_Pool_Region = 0

#User Protect Region
Address_of_User_Region = 0
Size_of_User_Region = 0
Protected_of_User_Region = 0
Key_Idx_of_User_Region = 0

#REE Region 1
Address_of_REE_Region_1 = 0
Size_of_REE_Region_1 = 0
Key_Idx_of_REE_Region_1 = 0

#REE Region 2
Address_of_REE_Region_2 = 0
Size_of_REE_Region_2 = 0
Key_Idx_of_REE_Region_2 = 0

#REE Region 3
Address_of_REE_Region_3 = 0
Size_of_REE_Region_3 = 0
Key_Idx_of_REE_Region_3 = 0

#REE Region 4
Address_of_REE_Region_4 = 0
Size_of_REE_Region_4 = 0
Key_Idx_of_REE_Region_4 = 0

#REE Region 5
Address_of_REE_Region_5 = 0
Size_of_REE_Region_5 = 0
Key_Idx_of_REE_Region_5 = 0

#REE Region 6
Address_of_REE_Region_6 = 0
Size_of_REE_Region_6 = 0
Key_Idx_of_REE_Region_6 = 0

#REE Region 7
Address_of_REE_Region_7 = 0
Size_of_REE_Region_7 = 0
Key_Idx_of_REE_Region_7 = 0

#REE Region 8
Address_of_REE_Region_8 = 0
Size_of_REE_Region_8 = 0
Key_Idx_of_REE_Region_8 = 0

STR_Default_Region_Start_Address = 0
STR_Resume_Mode = 0
STR_Address_of_BL31_Area = 0
STR_Size_of_BL31_Area = 0
TEEOS_SegmentID_EXT = 0
TEEOS_Mask_MSID = 0
TEEOS_Version_EXT = 0
TEEOS_Mask_Vers = 0

PCPU_FW_SegmentID_EXT = 0
PCPU_FW_Mask_MSID = 0
PCPU_FW_Version_EXT = 0
PCPU_FW_Mask_Vers = 0

NagraTAProtectionKey = "aes_128bit_key_1.bin"
ATFProtectionKey = "aes_128bit_key_2.bin"
DTEProtectionKey = "aes_128bit_key_3.bin"

# ********************************************************************
# Config for Security, TRUE will encrypt the DTE_Bootcode_RTK(LK or uboot64)
# ********************************************************************
Config_Secure_Improve = FALSE

# ********************************************************************
# Config for Simulation Mode - only use BOOTCODE_UBOOT_TARGET_SIM, don't ignore RSA calculation
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Uboot_Sim_Mode = [TRUE | FALSE]
Config_Uboot_Sim_Mode =  FALSE

# ********************************************************************
# Config for Auxcode/BL31/TEE OS
# ********************************************************************
# flag                      value
# ********************************************************************
Config_Auxcode_File_Name = "Aux_code-00.00.bin"
Config_PCPU_Code_File_Name = "PCPU_Code_Area_rtk_final.bin"
Config_DTE_Bootcode_File_Name = "FSBL_DDR-00.00.bin"
Config_SECURE_OS = TRUE
Config_SECURE_OS_File_Name = "fsbl-nand-os-00.00.bin.slim"
Config_BL31 = TRUE
Config_BL31_File_Name = "bl31.bin"
Config_RTK_PARAM_AREA_File_Name = "RTK_Params_Area_final.bin"


# ********************************************************************
# Boot parameters
# ********************************************************************
# flag                      value
# ********************************************************************
##Param_MAC_hi =            mac[0:3]
Param_MAC_hi =              0x00112233
##Param_MAC_lo =            mac[4:5]
Param_MAC_lo =              0x44550000


# ********************************************************************
# user defined
# ********************************************************************
# flag                      value
# ********************************************************************
#User_Defined =               FPGA "1"
#User_Defined =               DUMP_NAND_FLASH "1"
User_Defined =               RTK_FLASH_NAND "1"


