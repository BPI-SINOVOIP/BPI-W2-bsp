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
BOOTARRAY_FW_TABLE_RSA_KEY = "rsa_key1_2048.pem"
SCS_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
ATF_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
PCPU_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.tee.pem"
DTE_FW_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.fw.pem"
AFW_EXTERNAL_PUBLIC_RSA_KEY = "rsa_key_2048.fw.pem"

# ********************************************************************
# NOCS Certificate and Params Attributes
# ********************************************************************
Size_of_SCS_Params_Area = 0x2160
Address_of_SCS_Params_Area = 0x80000000
SegmentID_EXT = 0x0
Mask_MSID =  0x0
Version_EXT = 0x0
Mask_Vers = 0x0

#*****************SCS_Params*******************
Address_of_SCS_Auxcode_Area = 0x80000000
Size_of_SCS_Auxcode_Area = 0x15000
Address_of_SCS_DTEBootcode_Area = 0x10120000
STR_Default_Region_Min_Size = 0xC00000
Scrambling_Activation = 0x0
FlashProtection_Activation = 0x1
RSKPS_Activation = 0x10120000
SCS_Total_Area_Size_1 = 0x20000
SCS_Total_Area_Size_2 = 0x40000
SCS_Total_Area_Size_3 = 0x80000
SCS_Total_Area_Size_4 = 0x100000
SCS_Total_Area_Size_Selection = 0x2
FlashProtectionKey = "aes_128bit_key.bin"
#FlashProtectionRootKey = "flash_protection_root_key.bin"

#*****************RTK_Params*******************
Address_of_BL31_Area = 0x80001000
Address_of_TEEOS_Area = 0x10200000
Address_of_AVFW_Area = 0x0F900000
STR_Min_Size_of_TEEOS_Area = 0x1000
STR_Min_Size_of_AVFW_Area = 0x1000
Number_of_Scramble_Key = 0x10

# TEE Protect Region
Address_of_TEE_Region = 0x10200000
Size_of_TEE_Region = 0xC00000
Protected_of_TEE_Region = 0xD0801
Key_Idx_of_TEE_Region = 0x0

# AVFW_TEXT Protect Region
Address_of_AVFW_TEXT_Region = 0x0F900000
Size_of_AVFW_TEXT_Region = 0x307000
Protected_of_AVFW_TEXT_Region = 0xD8801
Key_Idx_of_AVFW_TEXT_Region = 0x1

# AVFW_DATA Protect Region
Address_of_AVFW_DATA_Region = 0x0FC07000
Size_of_AVFW_DATA_Region = 0x1F9000
Protected_of_AVFW_DATA_Region = 0xDA801
Key_Idx_of_AVFW_DATA_Region = 0x2

# AVFW_ISR Protect Region
Address_of_AVFW_ISR_Region = 0x0
Size_of_AVFW_ISR_Region = 0x1000
Protected_of_AVFW_ISR_Region = 0x48801
Key_Idx_of_AVFW_ISR_Region = 0x3

# AVFW_ENTRY Protect Region
Address_of_AVFW_ENTRY_Region = 0x2000
Size_of_AVFW_ENTRY_Region = 0x1000
Protected_of_AVFW_ENTRY_Region = 0x48801
Key_Idx_of_AVFW_ENTRY_Region = 0x4

#Video_Pool Protect Region
Address_of_Video_Pool_Region = 0x32b00000
Size_of_Video_Pool_Region = 0x12C00000
Protected_of_Video_Pool_Region = 0xD9818
Key_Idx_of_Video_Pool_Region = 0x5

#User Protect Region
Address_of_User_Region = 0x0
Size_of_User_Region = 0x0
Protected_of_User_Region = 0x0
Key_Idx_of_User_Region = 0x6

#REE Region 1
Address_of_REE_Region_1 = 0x1000
Size_of_REE_Region_1 = 0x1000
Key_Idx_of_REE_Region_1 = 0x7

#REE Region 2
Address_of_REE_Region_2 = 0x3000
Size_of_REE_Region_2 = 0xF8FD000
Key_Idx_of_REE_Region_2 = 0x8

#REE Region 3
Address_of_REE_Region_3 = 0x0FE00000
Size_of_REE_Region_3 = 0x300000
Key_Idx_of_REE_Region_3 = 0x9

#REE Region 4
Address_of_REE_Region_4 = 0x13C00000
Size_of_REE_Region_4 = 1EF00000
Key_Idx_of_REE_Region_4 = 0xA

#REE Region 5
Address_of_REE_Region_5 = 0x45700000
Size_of_REE_Region_5 = 0x3A900000
Key_Idx_of_REE_Region_5 = 0xB

#REE Region 6
Address_of_REE_Region_6 = 0x0
Size_of_REE_Region_6 = 0xDEADBEEF
Key_Idx_of_REE_Region_6 = 0xC

#REE Region 7
Address_of_REE_Region_7 = 0x0
Size_of_REE_Region_7 = 0xDEADBEEF
Key_Idx_of_REE_Region_7 = 0xD

#REE Region 8
Address_of_REE_Region_8 = 0x0
Size_of_REE_Region_8 = 0xDEADBEEF
Key_Idx_of_REE_Region_8 = 0xE

STR_Default_Region_Start_Address = 0x280000
STR_Resume_Mode = 0x0
STR_Address_of_BL31_Area = 0x0
STR_Size_of_BL31_Area = 0x0
TEEOS_SegmentID_EXT = 0x0
TEEOS_Mask_MSID = 0x0
TEEOS_Version_EXT = 0x0
TEEOS_Mask_Vers = 0x0

PCPU_FW_Version_EXT=0x0
PCPU_FW_SegmentID_EXT=0x0

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
Config_PCPU_Code_File_Name = "pcpu_fw.bin"
Config_DTE_Bootcode_File_Name = "FSBL_DDR-00.00.bin"
Config_SECURE_OS = TRUE
Config_SECURE_OS_File_Name = "secure-os-00.00.bin"
Config_BL31 = TRUE
Config_BL31_File_Name = "bl31.bin"


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
#User_Defined =          FPGA "1"
User_Defined =          RTK_FLASH_EMMC "1"


