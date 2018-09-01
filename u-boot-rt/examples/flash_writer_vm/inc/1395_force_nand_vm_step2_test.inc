# ********************************************************************
# Board Components
# ********************************************************************
# flag                      value
# ********************************************************************
Board_CPU =                 RTD1395
##Board_Chip_Rev =          [1395]
Board_Chip_Rev =            1395

Board_HWSETTING =           RTD1395_hwsetting_nand_BOOT_2DDR4_8Gb_s1866
						

# ********************************************************************
# Config
# ********************************************************************
# flag                      value
# ********************************************************************
##Board_Security =         [TRUE | FALSE]
Config_Encryption =        FALSE
##Config_NOR_BOOT_NAND =   [TRUE | FALSE]
Config_NOR_BOOT_NAND =     FALSE
##Config_SPI_BOOT_FISRT =  [SPI | EMMC | NAND]
Config_SPI_BOOT_FISRT =    SPI
##Config_SPI_BOOTCODE2  =  [TRUE | FALSE]
#Config_SPI_BOOTCODE2 =     FALSE
##Config_SPI_BOOTCODE3  =  [TRUE | FALSE]
#Config_SPI_BOOTCODE3 =     FALSE
##Config_FLASH_TYPE = [SPI | EMMC | NAND]
Config_FLASH_TYPE =	NULL


# ********************************************************************
# config password to allow input from UART when secure boot (maximum 255)
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Secure_Disable_Uart = [TRUE | FALSE]
##Config_Secure_Disable_Uart =   FALSE
##Config_Secure_Uart =  "1234512345123451234512345"


# ********************************************************************
# RSA key file & AES key file (under bin/image)
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Secure_KEY =        [TRUE | FALSE]
##Config_VM_Enc =         	 [TRUE | FALSE]
Config_Secure_Key =          FALSE
Config_VM_Enc =           	 FALSE
Config_Secure_RSA_Key_File = "rsa_key_2048.pem"
Config_Secure_RSA_Key_FW_File = "rsa_key_2048.fw.pem"
Config_Secure_RSA_Key_TEE_File = "rsa_key_2048.tee.pem"
Config_Secure_AES_Key_File_Name = aes_128bit_key.bin
Config_Secure_AES_Key1_File_Name = aes_128bit_key_1.bin
Config_Secure_AES_Key2_File_Name = aes_128bit_key_2.bin
Config_Secure_AES_Key3_File_Name = aes_128bit_key_3.bin


# ********************************************************************
# Config for Simulation Mode - only use BOOTCODE_UBOOT_TARGET_SIM, don't ignore RSA calculation
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Uboot_Sim_Mode = [TRUE | FALSE]
Config_Uboot_Sim_Mode =  FALSE

# ********************************************************************
# Config for SecureBoot Loader & Secure OS
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_FSBL = [TRUE | FALSE]
Config_FSBL = TRUE
Config_FSBL_File_Name = fsbl-loader-nand-00.00.bin.enc
Config_FSBL_OS = TRUE
Config_FSBL_OS_File_Name = fsbl-os-00.00.bin.enc
Config_BL31 = TRUE
Config_BL31_File_Name = bl31.bin.enc

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
# Logo attribute
# ********************************************************************
# flag                      value
# ********************************************************************
##Logo_Source =             [FLASH | NULL]
Logo_Source =               NULL
##Logo_Type =               [NTSC | PAL | 1080p50 | 1080p60]
Logo_Type =                 NTSC
##Logo_File_Name =          [LOCAL | User_defined]
Logo_File_Name =            "realtek_ntsc1.bmp"

# ********************************************************************
# Rescue Linux attribute
# ********************************************************************
# flag                      value
# ********************************************************************
##Rescue Linux included modules will be configured by Linux Makeconfig,
##not by boot config. If rescue is included into flash image,
##user must specify Rescue_Flash_File_Name to identify which
##rescue should be merged into flash image

##Rescue_Switch =           [FLASH | USB | NULL]
Rescue_Source =             NULL
##Rescue_File_Name =        [rescue loading parameters]
Rescue_File_Name =          vmlinux.rescue.phoenix.bin

# ********************************************************************
# user defined
# ********************************************************************
# flag                      value
# ********************************************************************
#User_Defined =               FPGA "1"
#User_Defined =      	     ROMCODE_ON_SPI
#User_Defined = 		     CR_MEMORY_DUMP "1"
User_Defined =               FPGA_BOOT_NAND "1"


