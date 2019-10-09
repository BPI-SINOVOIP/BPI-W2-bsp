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
#include "FileCipher_AES.h"  
#include "FileCipher_RSA.h"  
  



/*------------------------------------------------------------------
 * Func : GetCipherAlgoID
 *
 * Desc : Get Cipher Algorithm By Name
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
CIPHER_ALGO GetCipherAlgoID(const char* algo_str)
{    
    if (strcmp(algo_str,"aes_128_ecb")==0)      return CIPHER_ALGO_AES_128_ECB;    
    else if (strcmp(algo_str,"aes_128_cbc")==0) return CIPHER_ALGO_AES_128_CBC;            
    else if (strcmp(algo_str,"aes_256_ecb")==0)      return CIPHER_ALGO_AES_256_ECB;    
    else if (strcmp(algo_str,"aes_256_cbc")==0) return CIPHER_ALGO_AES_256_CBC;            
    else if (strcmp(algo_str,"rsa")==0)         return CIPHER_ALGO_RSA;   
    else                                        return CIPHER_ALGO_UNKNOWN;     
}





/*******************************************************************************
 * FUNC : EncryptFile
 * DESC : Encrypt File
 * PARM : NA
 * RET  : NA
 *******************************************************************************/   
int EncryptFile(ENC_CMD* cmd)
{
    switch(GetCipherAlgoID(cmd->algo_str))            
    {
    case CIPHER_ALGO_AES_128_ECB:             
    case CIPHER_ALGO_AES_128_CBC:            
    case CIPHER_ALGO_AES_256_ECB:             
    case CIPHER_ALGO_AES_256_CBC:            
        return AES_FileEncryption(cmd);        
        
    case CIPHER_ALGO_RSA:
        return RSA_FileEncryption(cmd);        
        
    default:        
    case CIPHER_ALGO_UNKNOWN:                                
        printf("invalid cipher - %s\n", cmd->algo_str);        
    }
    
    return -1;
}




/*------------------------------------------------------------------
 * Func : PaddingData
 *
 * Desc : Get Cipher Algorithm By Name
 *
 * Parm : algo     : padding algorithm
 *        p_data   : length of data
 *        data_len : data length
 *        aligment : data alignment
 *
 * Retn : <0 : failed, other : length of padded data
 *------------------------------------------------------------------*/
int PaddingData(
    PADDING_ALGO        algo, 
    unsigned char*      p_data, 
    unsigned long       data_len,
    unsigned long       aligment
    )
{
    int pad_size = 0;
    int sb_size = 0;
        
    
    switch(algo)
    {            
    case PADDING_ZEROS:
    case PADDING_ONES:                                    
                
        if ((sb_size = data_len % aligment))
        {
            pad_size = aligment - sb_size;
            memset(&p_data[data_len], (algo==PADDING_ZEROS) ? 0 : 0xFF, pad_size);            
        }
        break;
    }    
    
    return data_len + pad_size;                 
}




/*------------------------------------------------------------------
 * Func : GetPaddingAlgo
 *
 * Desc : Get Cipher Algorithm By Name
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
PADDING_ALGO GetPaddingAlgo(const char* padding_str)
{
    if (padding_str)
    {
        if (strcmp(padding_str,"none")==0)     return NO_PADDING;    
        else if (strcmp(padding_str,"0")==0)   return PADDING_ZEROS;            
        else if (strcmp(padding_str,"1")==0)   return PADDING_ONES;   
        else                                return NO_PADDING;     
    }
    
    return NO_PADDING;                 
}

