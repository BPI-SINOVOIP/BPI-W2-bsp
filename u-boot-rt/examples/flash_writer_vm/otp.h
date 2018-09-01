#ifndef __OTP_H__
#define __OTP_H__

#ifdef __OTP_C__
	#define EXTERN_CALL
#else
	#define EXTERN_CALL extern
#endif

EXTERN_CALL int get_boot_flash_type_from_gpio(void);
EXTERN_CALL unsigned char get_secure_type_from_efuse(void);
EXTERN_CALL unsigned char check_secure_boot(void);
EXTERN_CALL const char * get_secure_type_name(void);

typedef enum nandecctype
{
	NAND_ECC_TYPE_6_12_BIT,
	NAND_ECC_TYPE_40BIT=1,
	NAND_ECC_TYPE_43BIT,
	NAND_ECC_TYPE_65BIT,
	NAND_ECC_TYPE_72BIT,
	NAND_ECC_TYPE_24BIT,
	NAND_ECC_TYPE_DUMMY,
	NAND_ECC_TYPE_16BIT,
	NAND_ECC_TOTAL_TYPE
}nandecctype_t;
#endif /* end of file */
