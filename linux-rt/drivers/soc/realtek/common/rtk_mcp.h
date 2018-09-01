/*
 * rtk_mcp.h - MCP driver
 *
 * Copyright (c) 2017 Realtek Semiconductor Corp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 */

#define CP_REG_BASE 0x0
#define TP_REG_BASE 0x0
#define CP_OTP_LOAD (CP_REG_BASE + 0x19c)

/* for SCPU */
/* MCP General Registers */
#define MCP_CTRL (CP_REG_BASE + 0x100)
#define MCP_STATUS (CP_REG_BASE + 0x104)
#define MCP_EN (CP_REG_BASE + 0x108)

/* MCP Ring-Buffer Registers */
#define MCP_BASE (CP_REG_BASE + 0x10c)
#define MCP_LIMIT (CP_REG_BASE + 0x110)
#define MCP_RDPTR (CP_REG_BASE + 0x114)
#define MCP_WRPTR (CP_REG_BASE + 0x118)
#define MCP_DES_COUNT (CP_REG_BASE + 0x134)
#define MCP_DES_COMPARE (CP_REG_BASE + 0x138)

/* MCP Ini_Key Registers */
#define MCP_DES_INI_KEY (CP_REG_BASE + 0x11C)
#define MCP_AES_INI_KEY (CP_REG_BASE + 0x124)

/* CP Power Management */
#define PWM_CTRL (CP_REG_BASE + 0x1e0)

/* TP registers */
#define TP_KEY_INFO_0 (TP_REG_BASE + 0x58)
#define TP_KEY_INFO_1 (TP_REG_BASE + 0x5c)
#define TP_KEY_CTRL (TP_REG_BASE + 0x60)

#if 1

#define SET_TP_KEY_CTRL(x,y) writel((x), (volatile unsigned int*) (TP_KEY_CTRL+y))
#define SET_TP_KEYINFO_0(x,y) writel((x), (volatile unsigned int*) (TP_KEY_INFO_0+y))
#define SET_TP_KEYINFO_1(x,y) writel((x), (volatile unsigned int*) (TP_KEY_INFO_1+y))

#define SET_MCP_CTRL(x,y) writel((x), (volatile unsigned int*) (MCP_CTRL+y))
#define SET_MCP_STATUS(x,y) writel((x), (volatile unsigned int*) (MCP_STATUS+y))
#define SET_MCP_EN(x,y) writel((x), (volatile unsigned int*) (MCP_EN+y))
#define SET_MCP_BASE(x,y) writel((x), (volatile unsigned int*) (MCP_BASE+y))
#define SET_MCP_LIMIT(x,y) writel((x), (volatile unsigned int*) (MCP_LIMIT+y))
#define SET_MCP_RDPTR(x,y) writel((x), (volatile unsigned int*) (MCP_RDPTR+y))
#define SET_MCP_WRPTR(x,y) writel((x), (volatile unsigned int*) (MCP_WRPTR+y))
#define SET_MCP_OTP_LOAD(x,y) writel((x), (volatile unsigned int*) (CP_OTP_LOAD+y)) /* for Jupiter only */
#define SET_MCP_DES_COUNT(x,y) writel((x), (volatile unsigned int*) (MCP_DES_COUNT+y))
#define SET_MCP_DES_COMPARE(x,y) writel((x), (volatile unsigned int*) (MCP_DES_COMPARE+y))

#define SET_PWM_CTRL(x,y) writel((x), (volatile unsigned int*) (PWM_CTRL+y))

#define GET_MCP_CTRL(y) readl((volatile unsigned int*) (MCP_CTRL+y))
#define GET_MCP_STATUS(y) readl((volatile unsigned int*) (MCP_STATUS+y))
#define GET_MCP_EN(y) readl((volatile unsigned int*) (MCP_EN+y))
#define GET_MCP_BASE(y) readl((volatile unsigned int*) (MCP_BASE+y))
#define GET_MCP_LIMIT(y) readl((volatile unsigned int*) (MCP_LIMIT+y))
#define GET_MCP_RDPTR(y) readl((volatile unsigned int*) (MCP_RDPTR+y))
#define GET_MCP_WRPTR(y) readl((volatile unsigned int*) (MCP_WRPTR+y))
#define GET_MCP_OTP_LOAD(y) readl((volatile unsigned int*) (CP_OTP_LOAD+y)) /* for Jupiter only */
#define GET_MCP_DES_COUNT(y) readl((volatile unsigned int*) (MCP_DES_COUNT+y))
#define GET_MCP_DES_COMPARE(y) readl((volatile unsigned int*) (MCP_DES_COMPARE+y))

#define GET_PWM_CTRL(y) readl((volatile unsigned int*) (PWM_CTRL+y))

#endif

//for IOCTL
#define MCP_DESC_ENTRY_COUNT 64
#define MCP_IOCTL_DO_COMMAND 0x70000001
#define MCP_IOCTL_TEST_AES_H 0x71000001

#define MCP_BCM_ECB 0x0
#define MCP_BCM_CBC 0x1
#define MCP_BCM_CTR 0x2

#define MCP_WRITE_DATA (0x01)
#define MCP_RING_EMPTY (0x01 <<1)
#define MCP_ERROR (0x01 <<2)
#define MCP_COMPARE (0x01 <<3)

#define MCP_GO (0x01<<1)
#define MCP_IDEL (0x01<<2)
#define MCP_SWAP (0x01<<3)
#define MCP_CLEAR (0x01<<4)

// Descriptor Definition
#define MARS_MCP_MODE(x) (x & 0x1F)

#define MCP_ALGO_DES 0x00
#define MCP_ALGO_3DES 0x01
#define MCP_ALGO_RC4 0x02
#define MCP_ALGO_MD5 0x03
#define MCP_ALGO_SHA_1 0x04
#define MCP_ALGO_AES 0x05
#define MCP_ALGO_AES_G 0x06
#define MCP_ALGO_AES_H 0x07
#define MCP_ALGO_CMAC 0x08
#define MCP_ALGO_SHA256 0x0b

#define MARS_MCP_BCM(x) ((x & 0x3) << 6)
#define MCP_BCM_ECB 0x0
#define MCP_BCM_CBC 0x1
#define MCP_BCM_CTR 0x2

#define MARS_MCP_ENC(x) ((x & 0x1) << 5)

#define MARS_MCP_KEY_SEL(x) ((x & 0x1) << 12)
#define MCP_KEY_SEL_OTP 0x1
#define MCP_KEY_SEL_DESC 0x0

#define MARS_MCP_IV_SEL(x) ((x & 0x1) << 11)
#define MCP_IV_SEL_REG 0x1
#define MCP_IV_SEL_DESC 0x0

#define MCP_AES_ECB_Decryption(key, p_in, p_out, len) MCP_AES_Decryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)
#define MCP_AES_ECB_Encryption(key, p_in, p_out, len) MCP_AES_Encryption(MCP_BCM_ECB, key, NULL, p_in, p_out, len)

#define mcp_dump_data_with_text(data, len ,fmt, args...)  do {\
								printk(fmt, ## args);\
								mcp_dump_mem(data, len);\
								}while(0)

/* Debug */
//#define MCP_DEBUG_EN
#ifdef MCP_DEBUG_EN
#define mcp_debug(fmt, args...) printk("[MCP] Debug, " fmt, ## args)
#else
#define mcp_debug(fmt, args...)
#endif

#define mcp_info(fmt, args...) printk("[MCP] " fmt, ## args)
#define mcp_warning(fmt, args...) pr_err("[MCP] Warning, " fmt, ## args)

typedef struct {
	uint32_t flags;
	uint32_t key[6];
	uint32_t iv[4];
	uint32_t data_in; /* data in : physical address */
	uint32_t data_out; /* data out : physical address */
	uint32_t length; /* data length */
}mcp_desc;

typedef struct {
	union {
		mcp_desc __user *p_desc;
		uint64_t padding_p_desc;
	};

	uint32_t n_desc;
	int32_t reserved;
}mcp_desc_set;

/* 256 bit SHA256 initial vector */
#define SHA256_H0		0x6A09E667
#define SHA256_H1		0xBB67AE85
#define SHA256_H2		0x3C6EF372
#define SHA256_H3		0xA54FF53A
#define SHA256_H4		0x510E527F
#define SHA256_H5		0x9B05688C
#define SHA256_H6		0x1F83D9AB
#define SHA256_H7		0x5BE0CD19
