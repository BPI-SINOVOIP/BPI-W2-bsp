#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "crc32.h"


   
/*------------------------------------------------------------------
 * Func : CRC32_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int CRC32_DigestInit(MCP_MD_CTX* ctx)
{   
    CRC32_CTX* pCRC32 = (CRC32_CTX*) ctx->md_data;
    
    if (pCRC32)        
    {
        pCRC32->key = 0x4c11db7;
        pCRC32->val = 0;
        pCRC32->crchighbit = 0x80000000;        
        return 0;
    }
                
    return -1;
}




/*------------------------------------------------------------------
 * Func : CRC32_DigestUpdate
 *
 * Desc : Update CRC32 Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   : 
 *        DataLen : Data Length  
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int CRC32_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{
    CRC32_CTX* pCRC32 = (CRC32_CTX*) ctx->md_data;
    unsigned long crc = pCRC32->val;
    unsigned long crchighbit = pCRC32->crchighbit;
    unsigned long key = pCRC32->key;        
    
    //printf("CRC32_DigestUpdate=%08x\n", DataLen);
    
    while(DataLen)
    {    
    	unsigned long i;
    	unsigned long bit;    	
    	
    	//printf("crc=%08x, byte=%02x, \n", crc, *pData);
    	for (i=0x80; i; i>>=1) 
    	{    
    		bit = crc & crchighbit;    		
    		
    		crc<<=1;
    		    		
    		if (*pData & i) 
    		    bit^= crchighbit;
    		    
    		if (bit) 
    		    crc^= key;
    	}
    	
    	pData++;
    	DataLen--;    	 
    }
	
	pCRC32->val = crc;
    return 0;
}



/*------------------------------------------------------------------
 * Func : CRC32_DigestFinal
 *
 * Desc : Finished AES_H Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *        pHashLen : Length of hash value
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int CRC32_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{
    return CRC32_DigestPeek(ctx, pHash);          
}



/*------------------------------------------------------------------
 * Func : CRC32_DigestPeek
 *
 * Desc : Peek current Hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output 
 *         
 * Retn : 0 : success, others : failed
 *------------------------------------------------------------------*/
int CRC32_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{    
    CRC32_CTX* pCRC32 = (CRC32_CTX*) ctx->md_data;    
    pHash[3] = (pCRC32->val>>24) & 0xFF;
    pHash[2] = (pCRC32->val>>16) & 0xFF;
    pHash[1] = (pCRC32->val>>8) & 0xFF;
    pHash[0] = (pCRC32->val) & 0xFF;
    return 0;      
}



/*------------------------------------------------------------------
 * Func : CRC32_DigestCleanup
 *
 * Desc : Clean up CRC32 context
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int CRC32_DigestCleanup(MCP_MD_CTX* ctx)
{   
    CRC32_CTX* pCRC32 = (CRC32_CTX*) ctx->md_data;                
    return 0;
}


static const MCP_MD CRC32_md = 
{
    .type       = MCP_MD_CRC32,
    .digest_sz  = 4,
    .block_size = 1,   
    .ctx_size   = sizeof(CRC32_CTX),
    .init       = CRC32_DigestInit,
    .update     = CRC32_DigestUpdate,
    .final      = CRC32_DigestFinal,
    .peek       = CRC32_DigestPeek,
    .cleanup    = CRC32_DigestCleanup,
};


MCP_MD *MCP_crc32(void)
{
    return (MCP_MD*) &CRC32_md;
}

