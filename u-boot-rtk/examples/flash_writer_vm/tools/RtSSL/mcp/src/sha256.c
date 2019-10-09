#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "sha256.h"


/*------------------------------------------------------------------
 * Func : SHA256_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestInit(MCP_MD_CTX* ctx)
{   
    SHA256_CTX* pSHA256 = (SHA256_CTX*) ctx->md_data;
    
    if (pSHA256)        
    {
        memset(pSHA256, 0, sizeof(SHA256_CTX));
        EVP_MD_CTX_init(&pSHA256->Ctx);
        EVP_DigestInit(&pSHA256->Ctx, EVP_sha256());
        return 0;
    }
                
    return -1;
}



/*------------------------------------------------------------------
 * Func : SHA256_DigestUpdate
 *
 * Desc : Update SHA256 Digest
 *
 * Parm : ctx     : context of md ctx
 *        pData   : 
 *        DataLen : Data Length  
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{
    SHA256_CTX* pSHA256 = (SHA256_CTX*) ctx->md_data;
    EVP_DigestUpdate(&pSHA256->Ctx, pData, DataLen);
    return 0;
}



/*------------------------------------------------------------------
 * Func : SHA256_DigestFinal
 *
 * Desc : Finished AES_H Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{        
    SHA256_CTX* pSHA256 = (SHA256_CTX*) ctx->md_data;    
    unsigned int HashLen;         
    EVP_DigestFinal(&pSHA256->Ctx, pSHA256->Hash, &HashLen);    
    memcpy(pHash, pSHA256->Hash , HashLen);    
    return 0;
}



/*------------------------------------------------------------------
 * Func : SHA256_DigestPeek
 *
 * Desc : Peek current Hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    ) 
{    
    SHA256_CTX* pSHA256 = (SHA256_CTX*) ctx->md_data;    
    memcpy(pHash, pSHA256->Hash , 32);    
    return 0;
}




/*------------------------------------------------------------------
 * Func : SHA256_DigestCleanup
 *
 * Desc : Clean up SHA256 context
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int SHA256_DigestCleanup(MCP_MD_CTX* ctx)
{   
    SHA256_CTX* pSHA256 = (SHA256_CTX*) ctx->md_data;                
    EVP_MD_CTX_cleanup(&pSHA256->Ctx);
    return 0;
}


static const MCP_MD SHA256_md = 
{
    .type       = MCP_MD_SHA256,
    .digest_sz  = 32,
    .block_size = 64,   
    .ctx_size   = sizeof(SHA256_CTX),
    .init       = SHA256_DigestInit,
    .update     = SHA256_DigestUpdate,
    .final      = SHA256_DigestFinal,
    .peek       = SHA256_DigestPeek,
    .cleanup    = SHA256_DigestCleanup,
};


MCP_MD *MCP_sha256(void)
{
    return (MCP_MD*) &SHA256_md;
}
