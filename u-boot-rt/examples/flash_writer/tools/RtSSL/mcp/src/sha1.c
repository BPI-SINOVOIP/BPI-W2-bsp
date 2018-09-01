#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "sha1.h"

   
/*------------------------------------------------------------------
 * Func : SHA1_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA1_DigestInit(MCP_MD_CTX* ctx)
{   
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;
    
    if (pSha1)        
    {
        memset(pSha1, 0, sizeof(SHA1_CTX));
        EVP_MD_CTX_init(&pSha1->Ctx);        
        EVP_DigestInit(&pSha1->Ctx, EVP_sha1());    
        return 0;
    }
                
    return -1;
}




/*------------------------------------------------------------------
 * Func : SHA1_DigestUpdate
 *
 * Desc : Update SHA1 Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   : 
 *        DataLen : Data Length  
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA1_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;
    EVP_DigestUpdate(&pSha1->Ctx, pData, DataLen);
    return 0;
}



/*------------------------------------------------------------------
 * Func : SHA1_DigestFinal
 *
 * Desc : Finished AES_H Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *        pHashLen : Length of hash value
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA1_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{        
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;    
    unsigned int HashLen;         
    EVP_DigestFinal(&pSha1->Ctx, pSha1->Hash, &HashLen);    
    memcpy(pHash, pSha1->Hash , HashLen);    
    return 0;
}



/*------------------------------------------------------------------
 * Func : SHA1_DigestPeek
 *
 * Desc : Peek current Hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA1_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{    
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;    
    memcpy(pHash, pSha1->Hash , 20);    
    return 0;
}




/*------------------------------------------------------------------
 * Func : SHA1_DigestCleanup
 *
 * Desc : Clean up SHA1 context
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA1_DigestCleanup(MCP_MD_CTX* ctx)
{   
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;                
    EVP_MD_CTX_cleanup(&pSha1->Ctx);
    return 0;
}


static const MCP_MD sha1_md = 
{
    .type       = MCP_MD_SHA1_H,
    .digest_sz  = 20,
    .block_size = 64,   
    .ctx_size   = sizeof(SHA1_CTX),
    .init       = SHA1_DigestInit,
    .update     = SHA1_DigestUpdate,
    .final      = SHA1_DigestFinal,
    .peek       = SHA1_DigestPeek,
    .cleanup    = SHA1_DigestCleanup,
};


MCP_MD *MCP_sha1(void)
{
    return (MCP_MD*) &sha1_md;
}



///////////////////////////////////////////////////////////////////////////////////
// for MARS SHA_1 generation
///////////////////////////////////////////////////////////////////////////////////



/*---------------------------------------------------------------------- 
 * Func : _dump_data 
 *
 * Desc : dump data in memory
 *
 * Parm : data : start address of data
 *        len  : length of data
 *
 * Retn : N/A
 *----------------------------------------------------------------------*/ 
static void _dump_data(unsigned char* data, unsigned int len)
{
    int i;                  
    for (i=0; i<len; i++)
    {
        if ((i & 0xF)==0)
            printf("\n %04x | ", i);                    
        printf("%02x ", data[i]);                    
    }    
}


/*------------------------------------------------------------------
 * Func : MARS_SHA1_DigestUpdate
 *
 * Desc : Update SHA1 Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   : 
 *        DataLen : Data Length  
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MARS_SHA1_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;
    
    unsigned int  HashLen;                 
        
    EVP_DigestUpdate(&pSha1->Ctx, pData, DataLen);        
                            
    EVP_DigestFinal(&pSha1->Ctx, pSha1->Hash, &HashLen);
        
    //_dump_data(pSha1->Hash, HashLen);        

    // restart        
    EVP_MD_CTX_cleanup(&pSha1->Ctx); 
    
    EVP_DigestInit(&pSha1->Ctx, EVP_sha1());                // restart 
    
    EVP_DigestUpdate(&pSha1->Ctx, pSha1->Hash, HashLen);    // feed in the hash value       
          
    return 0;
}



/*------------------------------------------------------------------
 * Func : MARS_SHA1_DigestPeek
 *
 * Desc : Peek current Hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MARS_SHA1_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{    
    SHA1_CTX* pSha1 = (SHA1_CTX*) ctx->md_data;    
    memcpy(pHash, pSha1->Hash , 20);    
    return 0;
}


static const MCP_MD Mars_sha1_md = 
{
    .type       = MCP_MD_SHA1_H,
    .digest_sz  = 20,
    .block_size = 64,        
    .ctx_size   = sizeof(SHA1_CTX),
    .init       = SHA1_DigestInit,
    .update     = MARS_SHA1_DigestUpdate,
    .final      = MARS_SHA1_DigestPeek,
    .peek       = MARS_SHA1_DigestPeek,
    .cleanup    = SHA1_DigestCleanup,
};



MCP_MD *MCP_mars_sha1(void)
{    
    return (MCP_MD*) &Mars_sha1_md;
}
