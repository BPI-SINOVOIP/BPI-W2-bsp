# ********************************************************************
# Board Components
# ********************************************************************
# flag                      value
# ********************************************************************
Board_CPU =                 RTD1195
##Board_Chip_Rev =          [1195]
Board_Chip_Rev =            1195
##Board_HWSETTING =         [qa | qa.1DDR | qa.1DDR.QFP | qa.2DDR]
#Board_HWSETTING =           RTD2993_4DDR_661MHz_OK_Phase8a2_20130305_pupd2_Demo

##### Demo Board Ver.C HWSETTING selection note #####################
# DC1: 4Gbit x 2 (1GByte)@661MHz / DC2: 4Gbit x 2 (1GByte)@661MHz
#####################################################################
#Board_HWSETTING =			RTD2993_4DDR_Demo_Ver.C_DC1_4Gbx2_661M_DC2_4Gbx2_661M

##### Demo Board Ver.C HWSETTING selection note #####################
# DC1: 2Gbit x 2 (512MByte)@661MHz / DC2: 2Gbit x 2 (512MByte)@661MHz
#####################################################################
#Board_HWSETTING =			RTD2993_4DDR_Demo_Ver.C_DC1_2Gbx2_661M_DC2_2Gbx2_661M

##### Demo Board Ver.C HWSETTING selection note #####################
# DC1: 4Gbit x 2 (1GByte)@661MHz / DC2: 4Gbit x 1 (512MByte)@661MHz
#####################################################################
#Board_HWSETTING =			RTD2993_3DDR_Demo_Ver.C_DC1_4Gbx2_661M_DC2_4Gbx1_661M

##### Demo Board Ver.C HWSETTING selection note #####################
# DC1: 2Gbit x 2 (512MByte)@661MHz / DC2: 4Gbit x 1 (512MByte)@661MHz
#####################################################################
#Board_HWSETTING =			RTD2993_3DDR_Demo_Ver.C_DC1_2Gbx2_661M_DC2_4Gbx1_661M

##### Demo Board Ver.D 4Layer HWSETTING selection note ##############
# DC1: 4Gbit x 2 (1GByte)@800MHz / DC2: 4Gbit x 2 (1GByte)@800MHz
#####################################################################
#Board_HWSETTING =			RTD2993_4DDR_Demo_Ver.D_4L_DC1_4Gbx2_800M_DC2_4Gbx2_800M

##### FPGA Board Ver.A 4Layer HWSETTING selection note ##############
# DC1: 512MB x 1 @1000MHz
#####################################################################
#Board_HWSETTING =			RTD1195.fpga.512M_1DDR
Board_HWSETTING = 			RTD1195.hwsetting_sample

##Board_DRAM_Block =        [64 | 128 | 256 ]M
Board_DRAM_Block =          128
##Board_DRAM_Number =       [1 | 2]
Board_DRAM_Number =         1
##Board_SATA =              [default | NULL]
Board_SATA =                NULL
##Board_IDE =               [default | NULL]
Board_IDE =                 NULL
##Board_USB_Driver =        [Enabled| Disabled]
Board_USB_Driver =          Disabled
##Board_IDE2                [default | NULL]
Board_IDE2 =                NULL
##Board_LAN =               [8139cp | NULL]
Board_LAN =                 NULL
##Board_RTC =               [default | NULL]
Board_RTC =                 NULL
##Board_VFD =               [default | Customize1,2 | NULL]
Board_VFD =                 NULL
##Board_GPIO =              [default | Customize1,2 | NULL]
Board_GPIO =                NULL
##Board_PWM =               [default | Customize1,2 | NULL]
Board_PWM =                 NULL
##Board_TVD =               [default | Customize1,2 | NULL]
Board_TVD =                 NULL

# ********************************************************************
# GPIO setup
# ********************************************************************
# flag                      value
# ********************************************************************
## GPIO operations are leave to customer in the source code
## Please refer to source code for detailed implementation in
## Custom/gpio_ctrl.c and Custom/gpio_ctrl.h

## pin function selection
#GPIO_MUXPAD0 =             0x03030020     // address: 1800_0350
##GPIO_MUXPAD1 =           [User_defined] // address: 1800_0354
#GPIO_MUXPAD2 =             0x00000500     // address: 1800_0358
#GPIO_MUXPAD3 =             0x00000540     // address: 1800_035c
##GPIO_MUXPAD4 =           [User_defined] // address: 1800_0360
##GPIO_MUXPAD5 =           [User_defined] // address: 1800_0364
##GPIO_MUXPAD6 =           [User_defined] // address: 1800_0368
##GPIO_MUXPAD7 =           [User_defined] // address: 1800_036c

## GPIO direction selection
##GPIO_GP0DIR =            [User_defined] // address: 1801_b100
##GPIO_GP1DIR =            [User_defined] // address: 1801_b104
#GPIO_GP2DIR =              0x00003d80     // address: 1801_b108
##GPIO_GP3DIR =            [User_defined] // address: 1801_b10c

## GPIO output value
##GPIO_GP0DATO =           [User_defined] // address: 1801_b110
##GPIO_GP1DATO =           [User_defined] // address: 1801_b114
#GPIO_GP2DATO =             0x00003c00     // address: 1801_b118
##GPIO_GP3DATO =           [User_defined] // address: 1801_b11c

# ********************************************************************
# Config
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_Product =         [avhdd | pvrbox | eqc]
Config_Product =           eqc
##Board_Security =         [TRUE | FALSE]
Config_Encryption =        FALSE
##Config_PLL_Prog =        [TRUE | FALSE]
Config_PLL_Prog =          FALSE
##Config_Time_Evaluatino = [TRUE | FALSE]
Config_Time_Evaluation =   FALSE
##Config_NOR_BOOT_NAND =   [TRUE | FALSE]
Config_NOR_BOOT_NAND =     FALSE
##Config_SPI_BOOT_FISRT =  [SPI | EMMC | NAND]
Config_SPI_BOOT_FISRT =    SPI
##Config_SPI_BOOTCODE2  =  [TRUE | FALSE]
#Config_SPI_BOOTCODE2 =     FALSE
##Config_SPI_BOOTCODE3  =  [TRUE | FALSE]
#Config_SPI_BOOTCODE3 =     FALSE

# ********************************************************************
# config HDMI Keys
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_HDMI_Key1 =  [value]
##Config_HDMI_Key2 =  [value]
##Config_HDMI_Key3 =  [value]
##Config_HDMI_Key4 =  [value]
##Config_HDMI_Key5 =  [value]
##Config_HDMI_Key6 =  [value]

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
Config_Simulation_Mode =  TRUE

# ********************************************************************
# Config for SecureBoot Loader & Secure OS
# ********************************************************************
# flag                      value
# ********************************************************************
##Config_FSBL = [TRUE | FALSE]
Config_FSBL = TRUE
Config_FSBL_OS = TRUE
Config_FSBL_File_Name = fsbl-loader-00.00.bin
Config_FSBL_OS_File_Name = fsbl-os-00.00.bin

# ********************************************************************
# Boot parameters
# ********************************************************************
# flag                      value
# ********************************************************************

##Param_companyID =         [value]
Param_companyID =           "0000"
##Param_boardID =           [value]
Param_boardID =             "0000"
##Param_version =           [value]
Param_version =             "0001"
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

##Logo2_Source =            [FLASH | NULL]
Logo2_Source =              NULL
##Logo2_Type =              [NTSC | PAL]
Logo2_Type =                NTSC
##Logo2_File_Name =         [LOCAL | User_defined]
Logo2_File_Name =           "realtek_ntsc2.bmp"

##Logo3_Source =            [FLASH | NULL]
Logo3_Source =              NULL
##Logo3_Type =              [NTSC | PAL]
Logo3_Type =                NTSC
##Logo3_File_Name =         [LOCAL | User_defined]
Logo3_File_Name =           "realtek_ntsc3.bmp"

##Logo4_Source =            [FLASH | NULL]
Logo4_Source =              NULL
##Logo4_Type =              [NTSC | PAL]
Logo4_Type =                NTSC
##Logo4_File_Name =         [LOCAL | User_defined]
Logo4_File_Name =           "realtek_ntsc4.bmp"

##Logo5_Source =            [FLASH | NULL]
Logo5_Source =              NULL
##Logo5_Type =              [NTSC | PAL]
Logo5_Type =                NTSC
##Logo5_File_Name =         [LOCAL | User_defined]
Logo5_File_Name =           "realtek_ntsc5.bmp"


##Logo6_Source =            [FLASH | NULL]
Logo6_Source =              NULL
##Logo6_Type =              [NTSC | PAL]
Logo6_Type =                NTSC
##Logo6_File_Name =         [LOCAL | User_defined]
Logo6_File_Name =           "realtek_ntsc_enter_rescue.bmp"

##Logo7_Source =            [FLASH | NULL]
Logo7_Source =              NULL
##Logo7_Type =              [NTSC | PAL]
Logo7_Type =                NTSC
##Logo7_File_Name =         [LOCAL | User_defined]
Logo7_File_Name =           "RTD1263_720x480_24bit_NoHDD.bmp"

##Logo8_Source =            [FLASH | NULL]
Logo8_Source =              NULL
##Logo8_Type =              [NTSC | PAL]
Logo8_Type =                NTSC
##Logo8_File_Name =         [LOCAL | User_defined]
Logo8_File_Name =           "realtek_ntsc_OTG.bmp"
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
Rescue_Source =             FLASH
##Rescue_Install_Key =      [0x09(TAB) | 0x20(SPACE) | (ESC)]
Rescue_Install_Key =        0x09
##Rescue_GPIO_Switch =      [TRUE | FALSE]
Rescue_GPIO_Switch = FALSE
##Rescue_Install_With_GPIO_Address = [value]
##Rescue_Install_With_GPIO_Address = 0xb801b124
##Rescue_Install_With_GPIO_Mask = [value]
##Rescue_Install_With_GPIO_Mask = 0x10000000
##Rescue_Install_With_GPIO_Value = [value]
##Rescue_Install_With_GPIO_Value = 0x00000000	// low active
##Rescue_Loader_Param =     [rescue loading parameters]
Rescue_Loader_Param =       ""
##Rescue_File_Name =        [rescue loading parameters]
Rescue_File_Name =          vmlinux.rescue.phoenix.bin
# ********************************************************************
# Linux attribute
# ********************************************************************
# flag                      value
# ********************************************************************
## Disc partition will be created followed
## by part.txt under the installation disc.

##Linux_Source =            [FLASH | IDE]
Linux_Source =              FLASH
##Linux_Loader_Param =      [linux loading parameters]
Linux_Loader_Param =        "go 803bc000 rootfstype=squashfs root=31:02 mtdparts="

# ********************************************************************
# USB OTG device mode attribute
# ********************************************************************
# flag                      value
# ********************************************************************
## bootcode will detect specified GPIO pin for USB OTG device mode,
## if GPIO is high, bootcode will slow down system speed and disable
## unnecessary PLL/clock in order to reduce power consumption

##USB_OTG_mode =            [Enabled| Disabled]
USB_OTG_mode =              Disabled
##USB_OTG_mode_ISO_GPIO_Number =[value]
#USB_OTG_mode_ISO_GPIO_Number =  2
##USB_OTG_mode_ISO_GPIO_Value = [0 | 1] //0: active low; 1: active high
#USB_OTG_mode_ISO_GPIO_Value =   0x1
##USB_OTG_mode_lower_speed =[Enabled| Disabled]
#USB_OTG_mode_lower_speed = Disabled

# ********************************************************************
# Shell Setup
# ********************************************************************
# flag                      value
# ********************************************************************
##Cmd_compare =             [On | Off]
Cmd_compare =               On
##Cmd_comptime =            [On]
Cmd_comptime =              On
##Cmd_copy =                [On | Off]
Cmd_copy =                  On
##Cmd_cp0 =                 [On | Off]
Cmd_cp0 =                   Off
##Cmd_cp1 =                 [On | Off]
Cmd_cp1 =                   Off
##Cmd_disk =                [On | Off]
Cmd_disk =                  Off
##Cmd_dump =                [On | Off]
Cmd_dump =                  On
##Cmd_erase =               [On | Off]
Cmd_erase =                 On
##Cmd_fill =                [On | Off]
Cmd_fill =                  On
##Cmd_format =              [On | Off]
Cmd_format =                Off
##Cmd_freadwrite =          [On | Off]
Cmd_freadwrite =            On
##Cmd_go =                  [On]
Cmd_go =                    On
##Cmd_help =                [On | Off]
Cmd_help =                  On
##Cmd_info =                [On]
Cmd_info =                  On
##Cmd_iping =               [On | Off]
Cmd_iping =                 On
##Cmd_load =                [On]
Cmd_load =                  On
##Cmd_port =                [On | Off]
Cmd_port =                  On
##Cmd_reset =               [On | Off]
Cmd_reset =                 On
##Cmd_setenv =              [On]
Cmd_setenv =                On
##Cmd_stty =                [On | Off]
Cmd_stty =                  On
##Cmd_test =                [On | Off]
Cmd_test =                  On
##Cmd_continue =            [On | Off]
Cmd_continue =              On
##Cmd_saveenv =             [On | Off]
Cmd_saveenv =               On
##Cmd_lzma =                [On | Off]
Cmd_lzma =                  On
##Cmd_wait =                [On | Off]
Cmd_wait =                  On

# ********************************************************************
# user defined
# ********************************************************************
# flag                      value
# ********************************************************************
##User_Defined =            user specified definition
##   !!!! attention !!!!
##   system_parameters_1 and system_parameters_2 are reserved!!
##   please do not use those two parameter names
##User_Defined =            system_parameters_3
User_Defined =              system_parameters_4 "12V5V_GPIO=35,hion cr_pw=b100-1f"

#// set default value of shellstart and shellstartdelay (used with Config_Auto_Test_DDR)
#User_Defined =              default_shellstart "test ram 0xa1000000 0x1000 0x1"
#User_Defined =              default_shellstartdelay "0"
User_Defined =               FPGA "1"
#User_Defined = 		     ROMCODE_ON_SPI
User_Defined = 		     CR_MEMORY_DUMP "1"
User_Defined =               FPGA_BOOT_EMMC "1"

User_Defined = 		     Baud_Divisor 0x12

#User_Defined =		     Audio_Mute_GPIO	0xb8007104
#User_Defined =		     Audio_Mute_Bit	0x8
#User_Defined =              USE_GBIT
