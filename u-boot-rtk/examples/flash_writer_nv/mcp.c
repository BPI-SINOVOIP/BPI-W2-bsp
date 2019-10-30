
/***********************************************************************
 *
 *  mcp.c
 *
 *  Implementation of hardware CP module
 *
 * 
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>

#include <sysdefs.h>
//#include <syserror.h>
//#include <string.h>
//#include <stdio.h>
#include "dvrboot_inc/mcp.h"
#include "dvrboot_inc/util.h"//modify by angus

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned int mcp_dscpt_addr;

/************************************************************************
 *  Public function 
 ************************************************************************/
//extern void sys_dcache_flush_all(void);

/************************************************************************
 *  Static variables
 ************************************************************************/
// reserve 2 descriptor for do_mcp (writer pointer cannot be equal to limit)
// (must be 8B boundary)
//static t_mcp_descriptor mcp_dscpt[2] __attribute__ ((aligned (8)));


/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int do_mcp(t_mcp_descriptor *dscpt);
static t_mcp_descriptor *alloc_mcp_descriptor(void);
static void update_initial_vector(t_mcp_descriptor *dscpt, UINT8 *vector);
static int load_otp(void);

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/


int AES_CBC_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;
	
	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1045;	// key from OTP
	}
	else {
		dscpt->mode = 0x0045;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = (UINT32) src_addr;
	dscpt->dst_addr = (UINT32) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}

int AES_CBC_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;
	
	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1065;	// key from OTP
	}
	else {
		dscpt->mode = 0x0065;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = (UINT32) src_addr;
	dscpt->dst_addr = (UINT32) dst_addr;
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_decrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;
	
	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1005;	// key from OTP
	}
	else {
		dscpt->mode = 0x0005;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_ECB_encrypt(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr, UINT32 key[4])
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;
	
	if (key == NULL) {
		if (load_otp())
			return -2;

		dscpt->mode = 0x1025;	// key from OTP
	}
	else {
		dscpt->mode = 0x0025;	// key from descriptor
		dscpt->key[0] = key[0];
		dscpt->key[1] = key[1];
		dscpt->key[2] = key[2];
		dscpt->key[3] = key[3];
	}

	dscpt->src_addr =  PHYS((UINT32)src_addr );
	dscpt->dst_addr =  PHYS((UINT32)dst_addr );
	dscpt->length = length;

	return do_mcp(dscpt);
}


int AES_hash_one(UINT8 *src_addr, UINT32 length, UINT8 *dst_addr)
{
	t_mcp_descriptor *dscpt;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;
	
	// only once
	dscpt->mode = 0x27;
	dscpt->ini_key[0] = AES_H_IV_0;
	dscpt->ini_key[1] = AES_H_IV_1;
	dscpt->ini_key[2] = AES_H_IV_2;
	dscpt->ini_key[3] = AES_H_IV_3;
	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	return do_mcp(dscpt);
}


int AES_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, INT32 block_size)
{
	t_mcp_descriptor *dscpt;
	UINT8 *src_ptr;
	int res;
	
	if ((src_addr == NULL) || (dst_addr == NULL))
		return -1;

	if ((length <= 0) || (block_size <= 0))
		return -1;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	// IV from dscpt, AES hash
	dscpt->mode = 0x27;
	dscpt->ini_key[0] = AES_H_IV_0;
	dscpt->ini_key[1] = AES_H_IV_1;
	dscpt->ini_key[2] = AES_H_IV_2;
	dscpt->ini_key[3] = AES_H_IV_3;
	src_ptr = src_addr;
	dscpt->dst_addr = (UINT32) dst_addr;
	
	res = 0;
	while (length > 0) {
		dscpt->src_addr = (UINT32) src_ptr;
		dscpt->length = length < block_size ? length: block_size;
		length -= block_size;
		
		res = do_mcp(dscpt);
		if (res)
			return res;
		
		if (length > 0) {
			// update descriptor for next block
			update_initial_vector(dscpt, (UINT8 *)dst_addr);
			src_ptr += dscpt->length;
		} 
		else
			break;
	}
	
	return res;
}


int SHA1_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[5])
{
	t_mcp_descriptor *dscpt;
	
	if ((src_addr == NULL) || (dst_addr == NULL))
		return -1;

	dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;

	dscpt->mode = 0x0004;

	if (iv == NULL) {
		// Mars style (always the same IV)
		dscpt->key[0] = SHA1_IV_0;
		dscpt->key[1] = SHA1_IV_1;
		dscpt->key[2] = SHA1_IV_2;
		dscpt->key[3] = SHA1_IV_3;
		dscpt->key[4] = SHA1_IV_4;
	}
	else {
		dscpt->key[0] = iv[0];
		dscpt->key[1] = iv[1];
		dscpt->key[2] = iv[2];
		dscpt->key[3] = iv[3];
		dscpt->key[4] = iv[4];
	}

	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;

	return do_mcp(dscpt);
}

int SHA256_hash(UINT8 *src_addr, INT32 length, UINT8 *dst_addr, UINT32 iv[8])
{
	t_mcp_descriptor *dscpt;
	
	if ((src_addr == NULL) || (dst_addr == NULL) || (length <= 0))
		return -1;

    dscpt = alloc_mcp_descriptor();
	if (dscpt == NULL)
	        return -1;


	dscpt->mode = 0xb;

	if (iv == NULL) {
		dscpt->key[0] = SHA256_H0;
		dscpt->key[1] = SHA256_H1;
		dscpt->key[2] = SHA256_H2;
		dscpt->key[3] = SHA256_H3;
		dscpt->key[4] = SHA256_H4;
		dscpt->key[5] = SHA256_H5;
		dscpt->ini_key[0] = SHA256_H6;
		dscpt->ini_key[1] = SHA256_H7;
	}
	else {
		dscpt->key[0] = iv[0];
		dscpt->key[1] = iv[1];
		dscpt->key[2] = iv[2];
		dscpt->key[3] = iv[3];
		dscpt->key[4] = iv[4];
		dscpt->key[5] = iv[5];
		dscpt->ini_key[0] = iv[6];
		dscpt->ini_key[1] = iv[7];
	}

	dscpt->src_addr = PHYS((UINT32) src_addr);
	dscpt->dst_addr = PHYS((UINT32) dst_addr);
	dscpt->length = length;
	
	return do_mcp(dscpt);
}


static int do_mcp(t_mcp_descriptor *dscpt)
{
#ifdef MCP_DEBUG
	int i;
#endif
	int res;
	int count;

	if (dscpt == NULL)
		return -1;
	
	sys_dcache_flush_all();
	
	// disable interrupt
	rtd_outl(K_MCP_EN, 0xfe);

	// disable go bit
	rtd_outl(K_MCP_CTRL, 0x2);

	// set ring buffer register
	rtd_outl(K_MCP_BASE, PHYS(((UINT32) dscpt)) );
	rtd_outl(K_MCP_LIMIT, PHYS(((UINT32) dscpt + sizeof(t_mcp_descriptor) * 2) ));
	rtd_outl(K_MCP_RDPTR, PHYS(((UINT32) dscpt) ));
	rtd_outl(K_MCP_WRPTR, PHYS(((UINT32) dscpt + sizeof(t_mcp_descriptor)) )); // writer pointer cannot be equal to limit

	//hexdump("[do_mcp]dscpt:", dscpt, sizeof(t_mcp_descriptor));
	//hexdump("[do_mcp]KSEG1(dscpt):", KSEG1(dscpt), sizeof(t_mcp_descriptor));
	
	//hexdump("[do_mcp]src_addr:", dscpt->src_addr, dscpt->length);
#ifdef MCP_DEBUG
	printf("MCP descriptor (addr 0x%x):\n", (UINT32) dscpt);
	printf("word 0: %x\n", dscpt->mode);
	printf("word 1~6:\n");
	for (i = 0; i < sizeof(dscpt->key)/sizeof(int); i++) {
		printf("\t%x\n", dscpt->key[i]);
	}

	printf("word 7~10:\n");
	for (i = 0; i < sizeof(dscpt->ini_key)/sizeof(int); i++) {
		printf("\t%x\n", dscpt->ini_key[i]);
	}

	printf("word 11: %x\n", dscpt->src_addr);
	printf("word 12: %x\n", dscpt->dst_addr);
	printf("word 13: %x\n", dscpt->length);
	//printf("src_addr:%x, dst_addr:%x, length:%x\n", dscpt->src_addr, dscpt->dst_addr, dscpt->length);
	printf("\nMCP ring buffer registers:\n");
	printf("\tMCP_BASE: 0x%x\n\tMCP_LIMIT: 0x%x\n\tMCP_RDPTR: 0x%x\n\tMCP_WRPTR: 0x%x\n", 
		REG32(MCP_BASE), REG32(MCP_LIMIT), REG32(MCP_RDPTR), REG32(MCP_WRPTR));
#endif

	//asm(".set mips3");
	asm("DSB SY");
	//asm(".set mips1");

	// change endian
	//REG32(K_MCP_CTRL) = 0x8; //we don't have to do this due to SCPU is little endian

	// go
	rtd_outl(K_MCP_CTRL, 0x3);
	count = 0;
	while ((rtd_inl(K_MCP_STATUS) & 0x6) == 0) {
		count++;
		if (count == 0x800000) {
#ifdef MCP_DEBUG
			printf("%s timeout\n", __FUNCTION__);
			printf("REG32(MCP_CTRL): 0x%x\n", REG32(K_MCP_CTRL));
			printf("REG32(MCP_STATUS): 0x%x\n", REG32(K_MCP_STATUS));
#endif
			return -3;
		}
	}

#ifdef MCP_DEBUG
	printf("mcp done counter: 0x%x\n", count);
	printf("MCP status: 0x%x\n", REG32(K_MCP_STATUS));
#endif

	// check result
	if (rtd_inl(K_MCP_STATUS) & 0x2)
		res = 0;		// ring buffer is empty
	else if (rtd_inl(K_MCP_STATUS) & 0x4)
		res = -1;		// error happened
	else
		res = -2;		// ???

	// clear MCP register
	rtd_outl(K_MCP_CTRL, 0x2);
	rtd_outl(K_MCP_STATUS, 0x6);
	
	sys_dcache_flush_all();
	
	return res;
}

static t_mcp_descriptor *alloc_mcp_descriptor(void)
{
	//static unsigned int mcp_dscpt_addr;
	t_mcp_descriptor *current;

#ifdef ROM_DEBUG
	prints("===> mcp_dscpt_addr: 0x");
	print_hex(mcp_dscpt_addr);
	prints("\n");
#endif

	// check if pool is full (descriptor address overflow)
	if ((mcp_dscpt_addr + sizeof(t_mcp_descriptor) > CP_DSCPT_POOL_MAX_ADDR)  || (mcp_dscpt_addr == 0)) {
		// wrap-around (allocate from base)
		mcp_dscpt_addr = CP_DSCPT_POOL_BASE_ADDR;
		// reset pool
		memset((char *)CP_DSCPT_POOL_BASE_ADDR, 0, CP_DSCPT_POOL_SIZE);
	}

	current = (t_mcp_descriptor *)mcp_dscpt_addr;
	memset(current, 0, sizeof(t_mcp_descriptor));
	mcp_dscpt_addr += sizeof(t_mcp_descriptor);	// move forward

#ifdef ROM_DEBUG
	prints(__FUNCTION__);
	prints("\n\tmcp_dscpt_addr: 0x");
	print_hex(mcp_dscpt_addr);
	prints(", return dscpt: 0x");
	print_hex((UINT32) current);
	prints("\n");
#endif

	return current;

}


static void update_initial_vector(t_mcp_descriptor *dscpt, UINT8 *vector)
{
	if ((dscpt == NULL) || (vector == NULL))
		return;
	
	dscpt->ini_key[0] = (vector[0] << 24) | (vector[1] << 16) | (vector[2] << 8) | vector[3];
	dscpt->ini_key[1] = (vector[4] << 24) | (vector[5] << 16) | (vector[6] << 8) | vector[7];
	dscpt->ini_key[2] = (vector[8] << 24) | (vector[9] << 16) | (vector[10] << 8) | vector[9];
	dscpt->ini_key[3] = (vector[12] << 24) | (vector[13] << 16) | (vector[14] << 8) | vector[15];
}

static int load_otp(void)
{
	unsigned int i;

	rtd_outl(CP_OTP_LOAD, 0x1);
	for( i = 0; i < 0x10000; i++ ) {
		if ((rtd_inl(CP_OTP_LOAD) & 0x1) == 0) {
			return 0;
		}
	}
#ifdef MCP_DEBUG
	printf("%s timeout\n", __FUNCTION__);
#endif
	return -1;
}
