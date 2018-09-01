/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for Mars CP module 
 *
 ************************************************************************/

#ifndef MCP_H
#define MCP_H

//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>
#include <sysdefs.h>

/************************************************************************
 *  Definition
 ************************************************************************/
#define  CP_REG_BASE		0xb8015000
	
#define  CP_OTP_LOAD		(CP_REG_BASE + 0x19c)

#if 0	
	//for KCPU & ACPU
	/* MCP General Registers */
#define  K_MCP_CTRL		(CP_REG_BASE + 0x900)
#define  K_MCP_STATUS		(CP_REG_BASE + 0x904)
#define  K_MCP_EN		(CP_REG_BASE + 0x908)
	
	/* MCP Ring-Buffer Registers */
#define  K_MCP_BASE		(CP_REG_BASE + 0x90c)
#define  K_MCP_LIMIT		(CP_REG_BASE + 0x910)
#define  K_MCP_RDPTR		(CP_REG_BASE + 0x914)
#define  K_MCP_WRPTR		(CP_REG_BASE + 0x918)
#define  K_MCP_DES_COUNT	(CP_REG_BASE + 0x934)
#define  K_MCP_DES_COMPARE	(CP_REG_BASE + 0x938)
	
	/* MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY	(CP_REG_BASE + 0x91C)
#define  K_MCP_AES_INI_KEY	(CP_REG_BASE + 0x924)
#else
	//for SCPU
	/* MCP General Registers */
#define  K_MCP_CTRL		(CP_REG_BASE + 0x100)
#define  K_MCP_STATUS		(CP_REG_BASE + 0x104)
#define  K_MCP_EN		(CP_REG_BASE + 0x108)
	
	/* MCP Ring-Buffer Registers */
#define  K_MCP_BASE		(CP_REG_BASE + 0x10c)
#define  K_MCP_LIMIT		(CP_REG_BASE + 0x110)
#define  K_MCP_RDPTR		(CP_REG_BASE + 0x114)
#define  K_MCP_WRPTR		(CP_REG_BASE + 0x118)
#define  K_MCP_DES_COUNT	(CP_REG_BASE + 0x134)
#define  K_MCP_DES_COMPARE	(CP_REG_BASE + 0x138)
	
	/* MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY	(CP_REG_BASE + 0x11C)
#define  K_MCP_AES_INI_KEY	(CP_REG_BASE + 0x124)

#endif
#define CP_DESCRIPTOR_ADDR	(0xa000ff00 - UBOOT_DDR_OFFSET)	/* CP descriptor address */
#define CP_DSCPT_POOL_BASE_ADDR	(0xa0010000 - UBOOT_DDR_OFFSET)	/* CP descriptor pool base address */
#define CP_DSCPT_POOL_SIZE	0x800		/* CP descriptor pool size */
#define CP_DSCPT_POOL_MAX_ADDR	(CP_DSCPT_POOL_BASE_ADDR + CP_DSCPT_POOL_SIZE)


typedef struct mcp_descriptor
{
    UINT32 mode;
    UINT32 key[6];
    UINT32 ini_key[4];
    UINT32 src_addr;
    UINT32 dst_addr;
    UINT32 length;
} t_mcp_descriptor ;

/* 128 bit of AES_H initial vector(h0) */
#define AES_H_IV_0		0x2dc2df39
#define AES_H_IV_1		0x420321d0
#define AES_H_IV_2		0xcef1fe23
#define AES_H_IV_3		0x74029d95

/* 160 bit SHA1 initial vector */
#define SHA1_IV_0		0x67452301
#define SHA1_IV_1		0xEFCDAB89
#define SHA1_IV_2		0x98BADCFE
#define SHA1_IV_3		0x10325476
#define SHA1_IV_4		0xC3D2E1F0

#define SHA1_SIZE		20
#define SHA256_SIZE		32

//#define MCP_DEBUG
/************************************************************************
 *  Public functions
 ************************************************************************/
int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_CBC_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_ECB_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4]);
int AES_hash_one(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr);
int AES_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, INT32 block_size);
int SHA1_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[5]);

#endif /* #ifndef MCP_H */
