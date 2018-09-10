/************************************************************************
 *
 *  project_config.h
 *
 *  external parameters was included in this file
 * 
 *
 ************************************************************************/

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
//********************************************************************
//Board Components
//********************************************************************
//flag                      value
//********************************************************************
#define Board_CPU_RTD1295
#define Board_Chip_Rev_1295
#define Board_HWSETTING_RTD1296_hwsetting_BOOT_4DDR4_4Gb_s1866
//********************************************************************
//Config
//********************************************************************
//flag                      value
//********************************************************************        
#define Config_Encryption_FALSE
#define Config_NOR_BOOT_NAND_FALSE
#define Config_SPI_BOOT_FISRT_SPI
#define RTK_FLASH_SPI
//********************************************************************
//config password to allow input from UART when secure boot (maximum 255)
//********************************************************************
//flag                      value
//********************************************************************
//********************************************************************
//RSA key file & AES key file (under bin/image)
//********************************************************************
//flag                      value
//********************************************************************
#define Config_Secure_Key_FALSE
#define Config_Uboot_Enc_FALSE
#define Config_Secure_RSA_Key_File			"rsa_key_2048___pem"
#define Config_Secure_RSA_Key_FW_File			"rsa_key_2048___fw.pem"
#define Config_Secure_RSA_Key_TEE_File			"rsa_key_2048___tee.pem"
#define Config_Secure_AES_Key_File_Name			aes_128bit_key___bin
//********************************************************************
//Config for USB MP Mode
//********************************************************************
//flag                      value
//********************************************************************
#define Config_USB_MP_Mode_FALSE
#define Config_USB_Secure_AES_Key0_File			aes_usb_128bit_key___bin
//********************************************************************
//Config for Simulation Mode (ignore RSA calculation)
//********************************************************************
//flag                      value
//********************************************************************
#define Config_Simulation_Mode_FALSE
#define Config_Jumper_Mode_FALSE
#define Config_Uboot64_Mode_FALSE
#define Config_Uboot64_for_SPI_FALSE
//********************************************************************
//Config for SecureBoot Loader & Secure OS
//********************************************************************
//flag                      value
//********************************************************************
#define Config_FSBL_TRUE
//FSBL jump to 0x00020000, CPU1/2/3 jump to 0x00020000
//Config_FSBL_File_Name = fsbl-loader-00.00.bin
//FSBL jump to 0x00100000, CPU1/2/3 jump to 0x00100000
//Config_FSBL_File_Name = fsbl-loader-00.00-bootcode-addr-0x00100000.bin
//FSBL jump to 0x00100000, CPU1/2/3 jump to 0x00020000
#define Config_FSBL_File_Name			fsbl-loader-00___00-bootcode-addr-0x00100000-0x00020000.bin
//********************************************************************
//Boot parameters
//********************************************************************
//flag                      value
//********************************************************************
#define Param_MAC_hi			0x00112233
#define Param_MAC_lo			0x44550000
//********************************************************************
//Logo attribute
//********************************************************************
//flag                      value
//********************************************************************
#define Logo_Source_NULL
#define Logo_Type_NTSC
#define Logo_File_Name			"realtek_ntsc1.bmp"
//********************************************************************
//Rescue Linux attribute
//********************************************************************
//flag                      value
//********************************************************************
#define Rescue_Source_NULL
#define Rescue_File_Name			vmlinux.rescue.phoenix.bin
//********************************************************************
//user defined
//********************************************************************
//flag                      value
//********************************************************************
#define SPI_ERASE_1MB_ONLY
#define NOT_REBOOT_AFTER_FLASHING
#endif //#ifndef EXTERN_PARAM_H	
