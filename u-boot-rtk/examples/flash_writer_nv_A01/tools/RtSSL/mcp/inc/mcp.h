#ifndef __MCP_H__
#define __MCP_H__


#ifdef __cplusplus
extern "C" {
#endif 


typedef enum {
    MCP_MD_AES_H,
    MCP_MD_MARS_AES_H,
    MCP_MD_SHA1_H,
    MCP_MD_MARS_SHA1_H,
    MCP_MD_SHA256,
    MCP_MD_CRC32,
    MCP_MD_RCIC,
}MCP_MD_TYPES;


typedef struct 
{
    void*     digest;
    void*     md_data;
}MCP_MD_CTX;


typedef struct 
{
    int type;                           /* type id*/
    int digest_sz;                      /* digest size */
    int block_size;                     /* the block size for each operation */
    int ctx_size;                       /* how big does the ctx->md_data need to be */    
    int (*init)(MCP_MD_CTX* ctx);       /* initial md conext */          
    int (*update)(MCP_MD_CTX *ctx,unsigned char* pData, unsigned int DataLen);
    int (*final)(MCP_MD_CTX *ctx, unsigned char* pHash);    
    int (*peek)(MCP_MD_CTX *ctx, unsigned char* pHash);    
    int (*cleanup)(MCP_MD_CTX *ctx);
    
}MCP_MD;


void MCP_MD_CTX_init    (MCP_MD_CTX *ctx);
int  MCP_MD_CTX_cleanup (MCP_MD_CTX *ctx);
int  MCP_DigestInit     (MCP_MD_CTX* ctx, const MCP_MD* type);
int  MCP_DigestUpdate   (MCP_MD_CTX* ctx, unsigned char* pData, unsigned int DataLen);
int  MCP_DigestFinal    (MCP_MD_CTX* ctx,unsigned char* pHash,unsigned int* pHashLen);
int  MCP_DigestPeek     (MCP_MD_CTX* ctx,unsigned char* pHash,unsigned int* pHashLen);


extern MCP_MD* MCP_GetDigestByName(const char* name);

extern MCP_MD* MCP_aes_h(void);
extern MCP_MD *MCP_mars_aes_h(void);
extern MCP_MD *MCP_mars_aes_h_with_aes_enc(void);
extern MCP_MD* MCP_sha1(void);
extern MCP_MD* MCP_mars_sha1(void);
extern MCP_MD* MCP_sha256(void);
extern MCP_MD* MCP_crc32(void);
extern MCP_MD* MCP_rcic(void);

#ifdef __cplusplus
}
#endif 


#endif // __MCP_H__
