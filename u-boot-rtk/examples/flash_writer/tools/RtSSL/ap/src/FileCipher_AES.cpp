#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <string.h> 
#include <ctype.h> 
#include <openssl/evp.h>
#include "auxfun.h" 
#include "FileIO.h"  
#include "FileCipher.h"  
  

#define dbg_print       
//#define dbg_print(args...)      do {printf(args); fflush(stdout);} while(0)   


static int EVP_CIPHER_CTX_init_no_padding(
    EVP_CIPHER_CTX*         ctx,
    const EVP_CIPHER*       pCipher,   
    unsigned char           EnDe,
    unsigned char*          pKey,
    unsigned char*          pIV
    )
{        
    EVP_CIPHER_CTX_init(ctx); 
    
    if (EnDe)
    {
        if (!EVP_EncryptInit(ctx, pCipher, NULL, NULL))
            return -1;
                
        EVP_CIPHER_CTX_set_padding(ctx, 0);        
        
        if (!EVP_EncryptInit(ctx, NULL, pKey, pIV))
            return -1;
    }
    else        
    {        
        if (!EVP_DecryptInit(ctx, pCipher, NULL, NULL))
            return -1;
                
        EVP_CIPHER_CTX_set_padding(ctx, 0);        
        
        if (!EVP_DecryptInit(ctx, NULL, pKey, pIV))
            return -1;    
    }    
        
    return 0;        
}            





/*******************************************************************************
 * FUNC : AES_CBC_FileEncryption
 * DESC : Decrypt File Encryption with CTS (Cipher Text Strealing)
 * PARM : 
 * RET  : NA
 *******************************************************************************/   
int AES_CBC_FileEncryption(    
    unsigned char           EnDe,
    unsigned char           Key[32],    
    unsigned char           IV[32],      
    const char*             FileIn,
    const char*             FileOut,
    PADDING_ALGO            pad_algo,
    CIPHER_ALGO		    algo
    )
{           
    unsigned char   Buff[512 * 1024];                
    unsigned char   BuffOut[512 * 1024];
    unsigned long   BuffLen;
    unsigned long   dec_len;
    unsigned char*  pIn;
    unsigned char*  pOut;    
    unsigned char*  pSn1;    
    FILE*           fd1;
    FILE*           fd2;
    int             ret = 0;      
    int             BlockSize;                
    int             DataLen;
    int             ShortBlock;   
    int             outl;                                              
    EVP_CIPHER_CTX  ctx;                
        
    //---------------------------------------                    
    // Init Ciphe 
    //---------------------------------------
    if (algo == CIPHER_ALGO_AES_128_CBC)
    {
    	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_128_cbc(), EnDe, Key, IV)<0)
		return -1;
    }
    else if (algo == CIPHER_ALGO_AES_256_CBC)
    {    
	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_256_cbc(), EnDe, Key, IV)<0)
        	return -1;         
    }           
    
    BlockSize = EVP_CIPHER_CTX_block_size(&ctx);
    BuffLen   = ((sizeof(Buff) / BlockSize)-1) * BlockSize;   // guaranteed that the data buffer is block alignment and reserve the last block as the sn1                     
    pSn1      = &BuffOut[BuffLen];
    memcpy(pSn1, IV, BlockSize);                              // set pSn1 as default value    
    
    //---------------------------------------                    
    // Open File length                        
    //---------------------------------------
    fd1 = fopen(FileIn, "rb");
    fd2 = fopen(".tmp", "wb");
    
    if (!fd1 || !fd2)
        goto err_open_file_failed;                                     
            
    //---------------------------------------                    
    // Start Decrypt
    //---------------------------------------            
                    
    while(!feof(fd1))
    {                                                
        DataLen = fread(Buff, 1, BuffLen, fd1);
                                                
        if (DataLen < 0)                                         
            continue;                
            
        DataLen = PaddingData(pad_algo, Buff, DataLen, BlockSize);    // do data padding if necessary
                
        ShortBlock = DataLen % BlockSize;     
        DataLen   -= ShortBlock;
                                                                               
        dbg_print("DataLen=%d, ShortBlock=%d\n", DataLen, ShortBlock);  
        
        pIn     = Buff;
        pOut    = BuffOut;              
                                                                    
        if (DataLen)
        {                                      
            if (EnDe)
            {                
                if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pIn, DataLen))
                    goto err_decrypt_fail;
                         
                pIn  += DataLen; 
                pOut += DataLen;
                                              
                memcpy(pSn1, pOut-BlockSize, BlockSize);       // back up last cipher text
            }
            else
            {
                if (!EVP_DecryptUpdate(&ctx, pOut, &outl, pIn, DataLen))
                    goto err_decrypt_fail;
                         
                pIn  += DataLen; 
                pOut += DataLen;
                                              
                memcpy(pSn1, pIn-BlockSize, BlockSize);       // back up last cipher text
            }
        }                
        
        if (ShortBlock)                                              
        {                                   
    	    if (algo == CIPHER_ALGO_AES_128_CBC)
    	    {
            	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_128_ecb(), 1, Key, 0)<0)
                	goto err_decrypt_fail;                                                        
	    }
    	    else if (algo == CIPHER_ALGO_AES_256_CBC)
    	    {
            	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_256_ecb(), 1, Key, 0)<0)
                	goto err_decrypt_fail;                                                        
	    }
            
            if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pSn1, (DataLen) ? (DataLen - ShortBlock) : BlockSize)) // encrypt the last cypher text
                goto err_decrypt_fail;
            
            for (int i=0; i<ShortBlock; i++)
                pOut[i] ^= pIn[i];                                
        }                     
        
        fwrite(BuffOut, 1, DataLen + ShortBlock, fd2);                    
    }    
         
    //---------------------------------------                    
    // Clean Up
    //---------------------------------------                  
end_proc:
        
    if (fd1) fclose(fd1);        
    if (fd2) fclose(fd2);       
        
    if (ret==0)        
        rename(".tmp", FileOut);    
    
    EVP_CIPHER_CTX_cleanup(&ctx); 
          
    return ret;     
    
//---------------------------------------                    
// Error Handling
//---------------------------------------            
err_decrypt_fail:
    printf("error_occur during Enc/Dec\n");        
    ret = -1;
    goto end_proc;    
    
err_open_file_failed:
    
    if (!fd1)
        printf("Decrypt File failed - open source file '%s' failed\n", FileIn);        
        
    if (!fd2)
        printf("Decrypt File failed - open tmp file '.tmp' failed\n");       
    
    ret = -1;        
    goto end_proc;      
}





/*******************************************************************************
 * FUNC : AES_ECB_FileEncryption
 * DESC : Decrypt File Encryption with CTS (Cipher Text Strealing)
 * PARM : 
 * RET  : NA
 *******************************************************************************/   
int AES_ECB_FileEncryption(    
    unsigned char           EnDe,
    unsigned char           Key[32],
    const char*             FileIn,
    const char*             FileOut,
    PADDING_ALGO            pad_algo,
    CIPHER_ALGO		    algo
    )
{           
    unsigned char   Buff[512 * 1024];                
    unsigned char   BuffOut[512 * 1024];
    unsigned long   BuffLen;
    unsigned long   dec_len;
    unsigned char*  pIn;
    unsigned char*  pOut;    
    unsigned char*  pSn1;    
    FILE*           fd1;
    FILE*           fd2;
    int             ret = 0;      
    int             BlockSize;                
    int             DataLen;
    int             ShortBlock;   
    int             outl;        
    int             flen;       
    int	            sig_len=0;                               
    EVP_CIPHER_CTX  ctx;                
        
    //---------------------------------------                    
    // Init Ciphe 
    //---------------------------------------
    if (algo == CIPHER_ALGO_AES_128_ECB)
    {
	sig_len=16;
    	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_128_ecb(), EnDe, Key, NULL)<0)
        	return -1;        
    }            
    else if (algo == CIPHER_ALGO_AES_256_ECB)
    {
	sig_len=32;
    	if (EVP_CIPHER_CTX_init_no_padding(&ctx, EVP_aes_256_ecb(), EnDe, Key, NULL)<0)
        	return -1;        
    }            
    
    BlockSize = EVP_CIPHER_CTX_block_size(&ctx);
    BuffLen   = ((sizeof(Buff) / BlockSize)-1) * BlockSize;   // guaranteed that the data buffer is block alignment and reserve the last block as the sn1                     
    pSn1      = &BuffOut[BuffLen];    
    
    //---------------------------------------                    
    // Open File length                        
    //---------------------------------------
    fd1 = fopen(FileIn, "rb");
    fd2 = fopen(".tmp", "wb");
    
    if (!fd1 || !fd2)
        goto err_open_file_failed;     
        
    fseek(fd1,0,SEEK_END);
    flen = ftell(fd1);                      
    fseek(fd1,0,SEEK_SET);
    
    if (flen < sig_len && pad_algo==NO_PADDING)        
        dbg_print("Info Enc/Dec - input data less than %d Bytes(%d) without padding, these data will remain clear\n", sig_len,flen);            
            
    //---------------------------------------                    
    // Start Decrypt
    //---------------------------------------            
                    
    while(!feof(fd1))
    {                       
        if (flen > BuffLen && (flen - BuffLen) > BlockSize)
            DataLen = fread(Buff, 1, BuffLen-sig_len, fd1);
        else            
            DataLen = fread(Buff, 1, BuffLen, fd1);
                                            
        if (DataLen < 0)                                         
            continue;                
                
        flen      -= DataLen;                                                                       
        
        DataLen    = PaddingData(pad_algo, Buff, DataLen, BlockSize);    // do data padding if necessary        
        
        ShortBlock = DataLen % BlockSize;     
        DataLen   -= ShortBlock;
                                                       
        dbg_print("DataLen=%d, ShortBlock=%d\n", DataLen, ShortBlock);  
        
        pIn     = Buff;
        pOut    = BuffOut;              
                                                                    
        if (DataLen)
        {                                        
            if (EnDe)
            {                
                if (ShortBlock==0)
                {
                    if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pIn, DataLen))
                        goto err_decrypt_fail;
                }                 
                else
                {
                    // encrypt last n-2 blocks
                    if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pIn, DataLen - BlockSize))
                        goto err_decrypt_fail;
                        
                    // encrypt last terminated block
                    pIn  += DataLen - BlockSize + ShortBlock;
                    pOut += DataLen - BlockSize + ShortBlock;                                 
    
                    if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pIn, BlockSize))
                        goto err_encrypt_fail;
                    
                    memcpy(pIn, pOut, BlockSize);
                
                    // encrypt last n-1 block                
                    pIn  -= ShortBlock;            
                    pOut -= ShortBlock;

                    if (!EVP_EncryptUpdate(&ctx, pOut, &outl, pIn, BlockSize))
                        goto err_encrypt_fail;                                 
                }                            
            }
            else
            {
                if (ShortBlock==0)
                {
                    if (!EVP_DecryptUpdate(&ctx, pOut, &outl, pIn, DataLen))
                        goto err_decrypt_fail;                                                                                                              
                }                 
                else
                {
                    // decrypt last n-1 blocks
                    if (!EVP_DecryptUpdate(&ctx, pOut, &outl, pIn, DataLen))
                        goto err_decrypt_fail;
                
                    pIn  += DataLen; 
                    pOut += DataLen;        
                    
                    memcpy(pIn - BlockSize, pOut - BlockSize, BlockSize);
                
                    // decrypt last terminated block
                    pIn  -= (BlockSize - ShortBlock);
                    pOut -= (BlockSize - ShortBlock);
                                                                        
                    if (!EVP_DecryptUpdate(&ctx, pOut, &outl, pIn, BlockSize))
                        goto err_decrypt_fail;                                                       
                }                                    
            }    
            
            fwrite(BuffOut, 1, DataLen + ShortBlock, fd2);                                
        }                
        else
        {
            fwrite(Buff, 1, ShortBlock, fd2);               // leave it clear
        }                        
    }    
         
    //---------------------------------------                    
    // Clean Up
    //---------------------------------------                  
end_proc:
        
    if (fd1) fclose(fd1);        
    if (fd2) fclose(fd2);       
        
    if (ret==0)        
        rename(".tmp", FileOut);    
    
    EVP_CIPHER_CTX_cleanup(&ctx); 
          
    return ret;     
    
//---------------------------------------                    
// Error Handling
//---------------------------------------                
err_encrypt_fail:
err_decrypt_fail:
    printf("error_occur during Enc/Dec\n");        
    ret = -1;
    goto end_proc;    
    
err_open_file_failed:
    
    if (!fd1)
        printf("Enc/Dec File failed - open source file '%s' failed\n", FileIn);        
        
    if (!fd2)
        printf("Enc/Dec File failed - open tmp file '.tmp' failed\n");       
    
    ret = -1;        
    goto end_proc;              
}



/*------------------------------------------------------------------
 * Func : AES_FileEncryption
 *
 * Desc : Encryption/Decryption Data with AES Cipher
 *
 * Parm : 
 * Retn : <0 failed, others length of hash value
 *------------------------------------------------------------------*/  
int AES_FileEncryption(ENC_CMD* cmd)
{
    unsigned char key[64];
    unsigned char iv[64];
    int key_len = -1;
    int iv_len  = -1;    
    
    memset(key, 0, sizeof(key));
    memset(iv,  0, sizeof(iv));
    
    if (!cmd->sfile)            
    {        
        printf("Do AES_FileEncryption failed - no input file specified\n");
        return -1;
    }
    
    if (!cmd->dfile)            
    {
        printf("Do AES_FileEncryption failed - no output file specified\n");        
        return -1;
    }
        
    if (cmd->key_str)
    {        
        key_len = _str_to_bytes(cmd->key_str, key, sizeof(key));
        
        if (key_len < 0)
        {
            printf("Do AES_FileEncryption failed - invalid key value - %s\n", cmd->key_str);
            return -1;
        }
    }       
    else
    {        
        printf("Do AES_FileEncryption failed - No Key specified\n");
        return -1;   
    }        
        
    if (cmd->iv_str)    
    {                
        iv_len = _str_to_bytes(cmd->iv_str, iv, sizeof(iv));
        if (iv_len<0)        
        {
            printf("Do AES_FileEncryption failed - invalid iv value - %s\n", cmd->iv_str);
            return -1;
        }            
    }               
    
    switch(GetCipherAlgoID(cmd->algo_str))            
    {
    case CIPHER_ALGO_AES_128_ECB:             
    case CIPHER_ALGO_AES_256_ECB:             
        return AES_ECB_FileEncryption(cmd->op_code, key, cmd->sfile, cmd->dfile, GetPaddingAlgo(cmd->padding_str), GetCipherAlgoID(cmd->algo_str));
    
    case CIPHER_ALGO_AES_128_CBC:            
    case CIPHER_ALGO_AES_256_CBC:            
        return AES_CBC_FileEncryption(cmd->op_code, key, iv, cmd->sfile, cmd->dfile, GetPaddingAlgo(cmd->padding_str), GetCipherAlgoID(cmd->algo_str));        
    }
    
    return -1;               
}
