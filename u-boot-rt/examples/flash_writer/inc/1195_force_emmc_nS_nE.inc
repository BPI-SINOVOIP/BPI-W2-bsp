# ********************************************************************
# Board Components
# ********************************************************************
# flag                      value
# ********************************************************************
Board_CPU =                 RTD1195
##Board_Chip_Rev =          [1195]
Board_Chip_Rev =            1195

##### QA Board Ver.A 4Layer HWSETTING selection note ##############
#DC1: 512MB x 2
#Speed: 1600
#####################################################################
#Board_HWSETTING =           RTD1195.hwsetting_BGA_2DDR.4Gb.s1600_v1

##### QA Board Ver.A 4Layer HWSETTING selection note ##############
#DC1: 512MB x 2
#Speed: 1333
#####################################################################
Board_HWSETTING =           RTD1195.hwsetting_BGA_2DDR.4Gb.s1333_v1


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
Config_FLASH_TYPE =NULL

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
##Config_Uboot_Enc =         [TRUE | FALSE]
Config_Secure_Key =          FALSE
Config_Uboot_Enc =           FALSE
Config_Secure_RSA_Key_File = "rsa_key_2048.pem"
Config_Secure_AES_Key_File_Name = aes_128bit_key.bin

# ********************************************************************
# Config for USB MP Mode
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_USB_MP_Mode = [TRUE | FALSE]
Config_USB_MP_Mode =   FALSE
Config_USB_Secure_AES_Key0_File = aes_usb_256bit_key.bin

# ********************************************************************
# Config for Simulation Mode (ignore RSA calculation)
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Simulation_Mode = [TRUE | FALSE]
Config_Simulation_Mode =  FALSE

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
#User_Defined =          FPGA "1"
#User_Defined = 	     ROMCODE_ON_SPI
User_Defined = 		     CR_MEMORY_DUMP "1"
User_Defined =           FPGA_BOOT_EMMC "1"



