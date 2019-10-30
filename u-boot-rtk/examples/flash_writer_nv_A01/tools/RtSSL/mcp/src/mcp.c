#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcp.h"
#include "aes_h.h"



/*------------------------------------------------------------------
 * Func : MCP_MD_CTX_init
 *
 * Desc : init MCP MD context
 *
 * Parm : N/A
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
void MCP_MD_CTX_init(MCP_MD_CTX *ctx)
{
    memset(ctx, 0, sizeof(MCP_MD_CTX));
}



/*------------------------------------------------------------------
 * Func : MCP_MD_CTX_cleanup
 *
 * Desc : clean up context
 *
 * Parm : N/A
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MCP_MD_CTX_cleanup(MCP_MD_CTX *ctx)
{   
    if (ctx)
    {
        if (ctx->digest) 
            ((MCP_MD*)ctx->digest)->cleanup(ctx);
            
        if (ctx->md_data)                    
            free(ctx->md_data);
            
        memset(ctx, 0, sizeof(MCP_MD_CTX));            

        return 0;
    }       
    
    return -1;
}



/*------------------------------------------------------------------
 * Func : MCP_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx
 *        type : tpye of md engine
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MCP_DigestInit(MCP_MD_CTX* ctx, const MCP_MD* type)
{
    ctx->digest  = (void*) type;
    ctx->md_data = malloc(type->ctx_size);
    memset(ctx->md_data, 0, type->ctx_size);
    return type->init(ctx);
}



/*------------------------------------------------------------------
 * Func : MCP_DigestUpdate
 *
 * Desc : Update MCP Digest
 *
 * Parm : ctx  : context of md ctx
 *        pData : 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MCP_DigestUpdate(
    MCP_MD_CTX*             ctx, 
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{        
    return (ctx && ctx->digest) ? ((MCP_MD*)ctx->digest)->update(ctx, pData, DataLen) : -1;
}




/*------------------------------------------------------------------
 * Func : MCP_DigestFinal
 *
 * Desc : Finished MCP Digest and output the hash value
 *
 * Parm : ctx       : context of md ctx
 *        pHash     : digest output
 *        pHashLen  : size of digest
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MCP_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash, 
    unsigned int*           pHashLen
    )
{    
    *pHashLen = ((MCP_MD*)ctx->digest)->digest_sz;
    return (ctx && ctx->digest) ? ((MCP_MD*)ctx->digest)->final(ctx, pHash) : -1;
}




/*------------------------------------------------------------------
 * Func : MCP_DigestPeek
 *
 * Desc : Read out the hash value
 *
 * Parm : ctx       : context of md ctx
 *        pHash     : digest output
 *        pHashLen  : size of digest
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int MCP_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash, 
    unsigned int*           pHashLen
    )
{    
    *pHashLen = ((MCP_MD*)ctx->digest)->digest_sz;
    return (ctx && ctx->digest) ? ((MCP_MD*)ctx->digest)->peek(ctx, pHash) : -1;
}



/*------------------------------------------------------------------
 * Func : MCP_GetDigestByName
 *
 * Desc : get MCP_MD by name
 *
 * Parm : name : name of the algorithm
 *         
 * Retn : handle of MCP MD
 *------------------------------------------------------------------*/
MCP_MD* MCP_GetDigestByName(const char* name)
{    
    if (strcmp(name,"aes_h")==0)                
        return MCP_aes_h();    
        
    if (strcmp(name,"mars_aes_h")==0)           
        return MCP_mars_aes_h();        
                                   
    if (strcmp(name,"sha1")==0)           
        return MCP_sha1();      
        
    if (strcmp(name,"mars_sha1")==0)           
        return MCP_mars_sha1();              
        
    if (strcmp(name,"sha256")==0)           
        return MCP_sha256();                         
        
    if (strcmp(name,"crc32")==0)           
        return MCP_crc32();                
        
    if (strcmp(name,"rcic")==0)           
        return MCP_rcic();                      
                                           
    return NULL;
}
