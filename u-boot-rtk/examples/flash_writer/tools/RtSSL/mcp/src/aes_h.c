#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include "aes_h.h"

/*
static void dump_mem(unsigned char* pData, unsigned short Len)
{
    int i,j,c;
    
    printf("------------------------------------------------------------\n");
    printf("ADDRESS   00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F \n");
    printf("------------------------------------------------------------\n");    
    for (i=0; i<Len; i+=16)
    {                       
        printf("%08x  ", i);                          
                    
        for (j=0; j<16; j++)    
        {
            c = i+j;
            if (c<Len)
                printf("%02x ", pData[c]);                        
            else
                printf("-- ");            
                            
            if ((c & 0x07)==0x07)
                printf("  ");            
        }
        
        printf(" ");
        
        for (j=0; j<16; j++)    
        {   
            int c = i+j;                    
            if (c<Len && isprint(pData[c]))                         
                printf("%c", (char) pData[c]);
            else                               
                printf(".");
        }
        
        printf("\n");               
    }
    printf("------------------------------------------------------------\n");
}


static void dump_mem_with_text(const char* str, unsigned char* pData, unsigned short Len)
{
    printf(">>>>>>>>>>>> %s <<<<<<<<<<<<<\n", str);
    dump_mem(pData, Len);
}
*/


/*------------------------------------------------------------------
 * Func : _Do_AES_H_Hash
 *
 * Desc : Compute AES_H value
 *
 * Parm : Hash    : Initial value of Hash Value or Hash value output
 *        pData   : Data to compute
 *        DataLen : Data Length (should be 16 bytes alignment)
 *         
 * Retn : 0
 *------------------------------------------------------------------*/
int _Do_AES_H_Hash(
    unsigned char           Hash[16],
    unsigned char*          pData, 
    unsigned long           DataLen
    )
{       
    EVP_CIPHER_CTX ctx;
    unsigned char  HashOut[16];
    unsigned long* plHash = (unsigned long*) Hash;     
    unsigned long* plHashOut = (unsigned long*) HashOut;
    int            Outl = 0;                   
    //int i;
    
    if (DataLen & 0xF)
    {              
        printf("Input data of AES_H should be 16 byte alignment\n");
        return -1;
    }    
        
    while(DataLen)
    {                                              
        //printf("\n\n>>>>>>>>>>>>>>Iteration %d <<<<<<<<<<<<<<<\n\n", i++);

        EVP_CIPHER_CTX_init(&ctx); 
           
        //dump_mem_with_text("Xi ", pData, 16);        
        
        if (!EVP_EncryptInit(&ctx, EVP_aes_128_ecb(), pData, NULL))
            return -1;                
                
        //dump_mem_with_text("Hi-1 ", Hash, 16);                
        
        if (!EVP_EncryptUpdate(&ctx, HashOut, &Outl, Hash, 16))       // compute hash value
            return -1;   
        
           
        //dump_mem_with_text("AES-E(Hi, Hi-1) ", pHashOut, 16);            
        
        plHashOut[0] ^= plHash[0];
        plHashOut[1] ^= plHash[1];
        plHashOut[2] ^= plHash[2];
        plHashOut[3] ^= plHash[3];
        
        memcpy(Hash, HashOut, 16);
        pData   += 16;
        DataLen -= 16;    
        
        EVP_EncryptFinal(&ctx, HashOut, &Outl);               
        
        EVP_CIPHER_CTX_cleanup(&ctx); 
    }            
    
    return 0;                    
}



   

/*------------------------------------------------------------------
 * Func : AES_H_CTX_Init
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_CTX_Init(AES_H_CTX* p_this)
{
    const unsigned char InitHash[16] = 
    {
        0x2D, 0xC2, 0xDF, 0x39, 0x42, 0x03, 0x21, 0xD0,
        0xCE, 0xF1, 0xFE, 0x23, 0x74, 0x02, 0x9D, 0x95        
    };
    
    memset(p_this, 0, sizeof(AES_H_CTX));
    memcpy(p_this->Hash, InitHash, 16);
    return 0;
}   


   
   
/*------------------------------------------------------------------
 * Func : AES_H_DigestInit
 *
 * Desc : Initial MCP Digest
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_DigestInit(MCP_MD_CTX* ctx)
{                
    AES_H_CTX* p_aesh = (AES_H_CTX*) ctx->md_data;
    
    if (p_aesh)
    {
        AES_H_CTX_Init(p_aesh);                                
        return 0;
    }
    
    return -1;        
}



/*------------------------------------------------------------------
 * Func : MCP_DigestUpdate
 *
 * Desc : Update MCP Digest
 *
 * Parm : ctx  : context of md ctx
 *        type : tpye of md engine
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_DigestUpdate(
    MCP_MD_CTX*             ctx,
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{                    
    AES_H_CTX*     p_this = (AES_H_CTX*) ctx->md_data;    
    unsigned int   Len = 0;
    
    //-------------------------------------------
    // comopute the data in reamain buffer first
    //-------------------------------------------
    if (p_this->RemainBytes)
    {
        Len = 16 - p_this->RemainBytes;

        if (DataLen < Len)
            Len = DataLen;

        // put the data to buffer
        memcpy(&p_this->Remain[p_this->RemainBytes], pData, Len);        
        p_this->RemainBytes += Len;
        pData               += Len;
        DataLen             -= Len;

        // compute hash value of reamain data
        if (p_this->RemainBytes==16)
        {
            _Do_AES_H_Hash(p_this->Hash, p_this->Remain, p_this->RemainBytes);
            p_this->ByteCount += p_this->RemainBytes;
            p_this->RemainBytes = 0;
        }
    }

        
    //-------------------------------------------
    // comopute data in the data buffer
    //-------------------------------------------
    if (DataLen)
    {                
        Len = DataLen & ~0xF;        
        
        _Do_AES_H_Hash(p_this->Hash, pData, Len);
                
        p_this->ByteCount += Len;                
        pData             += Len;                                
        DataLen           -= Len;
                
        if (DataLen)
        {            
            memcpy(p_this->Remain, pData, DataLen);                        
            p_this->RemainBytes = DataLen;
        }
    }
        
    return 0;                    
}




/*------------------------------------------------------------------
 * Func : AES_H_DigestFinal
 *
 * Desc : Finished AES_H Digest
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *        pHashLen : Length of hash value
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    )
{    
    AES_H_CTX* p_this = (AES_H_CTX*) ctx->md_data;
    unsigned char PaddingData[32];
    unsigned char PaddingLen = 16 - p_this->RemainBytes;        
    unsigned long long DataLen = p_this->ByteCount + p_this->RemainBytes;

    //printf("DataLen = %llu, ByteCount =%lu, RemainByte=%lu\n", DataLen, p_this->ByteCount, p_this->RemainBytes);
    //dump_mem_with_text("hash value before padding", p_this->Hash, 16);
    
    memset(PaddingData, 0, sizeof(PaddingData));        
    PaddingData[0] = 0x80;
    
    if (PaddingLen <= 8)
        PaddingLen += 16;       
    PaddingData[PaddingLen - 8] = (unsigned char) (DataLen >> 53) & 0xFF;
    PaddingData[PaddingLen - 7] = (unsigned char) (DataLen >> 45) & 0xFF;
    PaddingData[PaddingLen - 6] = (unsigned char) (DataLen >> 37) & 0xFF;
    PaddingData[PaddingLen - 5] = (unsigned char) (DataLen >> 29) & 0xFF;    
    PaddingData[PaddingLen - 4] = (unsigned char) (DataLen >> 21) & 0xFF;
    PaddingData[PaddingLen - 3] = (unsigned char) (DataLen >> 13) & 0xFF;
    PaddingData[PaddingLen - 2] = (unsigned char) (DataLen >>  5) & 0xFF;
    PaddingData[PaddingLen - 1] = (unsigned char) (DataLen <<  3) & 0xFF;

    //dump_mem_with_text("padded data", PaddingData, PaddingLen);

    AES_H_DigestUpdate(ctx, PaddingData, PaddingLen);

    memcpy(pHash, p_this->Hash, 16);
    
    AES_H_CTX_Init(p_this);     
    
    return 0;                
}



/*------------------------------------------------------------------
 * Func : AES_H_DigestPeek
 *
 * Desc : Peek current hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_DigestPeek(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    )
{        
    memcpy(pHash, ((AES_H_CTX*)ctx->md_data)->Hash, 16);
    return 0;
}




/*------------------------------------------------------------------
 * Func : AES_H_DigestCleanup
 *
 * Desc : Clean up AES_H context
 *
 * Parm : ctx  : context of md ctx 
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int AES_H_DigestCleanup(MCP_MD_CTX* ctx)
{        
    AES_H_CTX* p_this = (AES_H_CTX*) ctx->md_data;
    memset(p_this, 0, sizeof(AES_H_CTX));
    return 0;
}



static const MCP_MD aes_h_md = 
{
    .type       = MCP_MD_AES_H,
    .digest_sz  = 16,
    .block_size = 16,        
    .ctx_size   = sizeof(AES_H_CTX),        
    .init       = AES_H_DigestInit,
    .update     = AES_H_DigestUpdate,
    .final      = AES_H_DigestFinal,
    .peek       = AES_H_DigestPeek,
    .cleanup    = AES_H_DigestCleanup,
};



MCP_MD *MCP_aes_h(void)
{
    return (MCP_MD*) &aes_h_md;
}



///////////////////////////////////////////////////////////////////////////////////
// for MARS AES H generation
///////////////////////////////////////////////////////////////////////////////////




/*------------------------------------------------------------------
 * Func : MCP_DigestUpdate
 *
 * Desc : Update MCP Digest
 *
 * Parm : ctx  : context of md ctx
 *        type : tpye of md engine
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MARS_AES_H_DigestUpdate(
    MCP_MD_CTX*             ctx, 
    unsigned char*          pData, 
    unsigned int            DataLen
    )
{   
    int ret; 
    unsigned char Hash[16];
    unsigned int  HashLen;
        
    ret  = AES_H_DigestUpdate(ctx, pData, DataLen);
    ret |= AES_H_DigestFinal(ctx, Hash);
        
    memcpy(((AES_H_CTX*)ctx->md_data)->Hash, Hash, 16);    // reset initial value of hash value
        
    return ret;              
}




/*------------------------------------------------------------------
 * Func : MARS_AES_H_DigestFinal
 *
 * Desc : Finished AES_H Digest and output the hash value
 *
 * Parm : ctx      : context of md ctx
 *        pHash    : Hash value output
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int MARS_AES_H_DigestFinal(
    MCP_MD_CTX*             ctx,
    unsigned char*          pHash
    )
{        
    AES_H_CTX* p_this = (AES_H_CTX*) ctx->md_data;    
    memcpy(pHash, p_this->Hash, 16);
    AES_H_CTX_Init(p_this);     
    return 0;
}


static const MCP_MD mars_aes_h_md = 
{
    .type       = MCP_MD_MARS_AES_H,
    .digest_sz  = 16,
    .block_size = 16,
    .ctx_size   = sizeof(AES_H_CTX),                
    .init       = AES_H_DigestInit,
    .update     = MARS_AES_H_DigestUpdate,
    .final      = MARS_AES_H_DigestFinal,
    .peek       = AES_H_DigestPeek,
    .cleanup    = AES_H_DigestCleanup, 
};



MCP_MD *MCP_mars_aes_h(void)
{
    return (MCP_MD*) &mars_aes_h_md;
}
