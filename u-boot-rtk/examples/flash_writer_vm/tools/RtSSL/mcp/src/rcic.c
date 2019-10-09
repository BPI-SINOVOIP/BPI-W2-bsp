#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "rcic.h"


   
/*------------------------------------------------------------------
 * Func : RCIC_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int RCIC_DigestInit(MCP_MD_CTX* ctx)
{   
    RCIC_CTX* pRCIC = (RCIC_CTX*) ctx->md_data;
    
    if (pRCIC)        
    {
        pRCIC->key = 0x4c11db7;
        pRCIC->val[0] = 0;
        pRCIC->val[1] = 0;
        pRCIC->crchighbit = 0x80000000;        
        return 0;
    }
                
    return -1;
}


int RCIC_DigestUpdateBytes(
    MCP_MD_CTX*             ctx,
    unsigned long           id,
    unsigned char           byte    
    )
{
    RCIC_CTX* pRCIC = (RCIC_CTX*) ctx->md_data;
    unsigned long crc = pRCIC->val[id];
    unsigned long crchighbit = pRCIC->crchighbit;
    unsigned long key = pRCIC->key;            
	unsigned long i;
	unsigned long bit;    	
	
	//printf("crc=%08x, byte=%02x, \n", crc, byte);
	for (i=0x80; i; i>>=1) 
	{    
		bit = crc & crchighbit;    		
        
		crc<<=1;
		    		
		if (byte & i) 
		    bit^= crchighbit;
		    
		if (bit) 
		    crc^= key;
	}  	 
	
	pRCIC->val[id] = crc;
    return 0;
}



/*------------------------------------------------------------------
 * Func : RCIC_DigestUpdate
 *
 * Desc : Update RCIC Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   : 
 *        DataLen : Data Length  
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int RCIC_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{    
    unsigned long sn = 0;
    //printf("RCIC_DigestUpdate=%08x\n", DataLen);
    
    if (DataLen & 0x7)
    {
         printf("Do RCIC Update failed, input data size (%d) is not multiple of 8 bytes\n", DataLen);
         return -1;
    }
    
    while(DataLen >= 8)
    {            
        RCIC_DigestUpdateBytes(ctx, 1, pData[0]);
        RCIC_DigestUpdateBytes(ctx, 1, pData[1]);
        RCIC_DigestUpdateBytes(ctx, 1, pData[2]);
        RCIC_DigestUpdateBytes(ctx, 1, pData[3]);
        RCIC_DigestUpdateBytes(ctx, 0, pData[4]);
        RCIC_DigestUpdateBytes(ctx, 0, pData[5]);
        RCIC_DigestUpdateBytes(ctx, 0, pData[6]);
        RCIC_DigestUpdateBytes(ctx, 0, pData[7]);          	
        DataLen -= 8;    
        pData += 8;          	 
    }
    
    return 0;
}



/*------------------------------------------------------------------
 * Func : RCIC_DigestFinal
 *
 * Desc : Finished AES_H Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *        pHashLen : Length of hash value
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int RCIC_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{
    RCIC_CTX* pRCIC = (RCIC_CTX*) ctx->md_data;      
    MCP_MD_CTX sha_256;    
    int HashLen = 0;

    RCIC_DigestPeek(ctx, pHash);
    
    // do sha 256     
    MCP_MD_CTX_init(&sha_256);
    MCP_DigestInit(&sha_256, MCP_sha256());    
    MCP_DigestUpdate(&sha_256, pHash, 8);
    MCP_DigestFinal(&sha_256, pHash, &HashLen);
    MCP_MD_CTX_cleanup(&sha_256);
    
    return HashLen;          
}



/*------------------------------------------------------------------
 * Func : RCIC_DigestPeek
 *
 * Desc : Peek current Hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int RCIC_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{    
    RCIC_CTX* pRCIC = (RCIC_CTX*) ctx->md_data;    
    pHash[0] = (pRCIC->val[1]>>24) & 0xFF;
    pHash[1] = (pRCIC->val[1]>>16) & 0xFF;
    pHash[2] = (pRCIC->val[1]>>8) & 0xFF;
    pHash[3] = (pRCIC->val[1]) & 0xFF;
    pHash[4] = (pRCIC->val[0]>>24) & 0xFF;
    pHash[5] = (pRCIC->val[0]>>16) & 0xFF;
    pHash[6] = (pRCIC->val[0]>>8) & 0xFF;
    pHash[7] = (pRCIC->val[0]) & 0xFF;     
    return -1;      
}



/*------------------------------------------------------------------
 * Func : RCIC_DigestCleanup
 *
 * Desc : Clean up RCIC context
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int RCIC_DigestCleanup(MCP_MD_CTX* ctx)
{   
    RCIC_CTX* pRCIC = (RCIC_CTX*) ctx->md_data;                
    return 0;
}


static const MCP_MD RCIC_md = 
{
    .type       = MCP_MD_RCIC,
    .digest_sz  = 32,
    .block_size = 8,   
    .ctx_size   = sizeof(RCIC_CTX),
    .init       = RCIC_DigestInit,
    .update     = RCIC_DigestUpdate,
    .final      = RCIC_DigestFinal,
    .peek       = RCIC_DigestPeek,
    .cleanup    = RCIC_DigestCleanup,
};


MCP_MD *MCP_rcic(void)
{
    return (MCP_MD*) &RCIC_md;
}

