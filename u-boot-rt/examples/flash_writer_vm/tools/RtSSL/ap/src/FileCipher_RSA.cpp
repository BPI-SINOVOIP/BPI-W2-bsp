#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "auxfun.h" 
#include "FileIO.h"  
#include "FileCipher.h"  
#include "RSATool.h"  
  
  

/*------------------------------------------------------------------
 * Func : RSA_FileEncryption
 *
 * Desc : Encryption/Decryption Data with RSA Cipher
 *
 * Parm : 
 * Retn : <0 failed, others length of hash value
 *------------------------------------------------------------------*/  
int RSA_FileEncryption(ENC_CMD* cmd)
{             
    RSA* rsa;
    
    if (GetCipherAlgoID(cmd->algo_str)!=CIPHER_ALGO_RSA)
        return -1;
        
    if (!cmd->sfile)            
    {        
        printf("Do RSA_FileEncryption failed - no input file specified\n");
        return -1;
    }

    if (!cmd->dfile)            
    {
        printf("Do RSA_FileEncryption failed - no output file specified\n");        
        return -1;
    }

    if (!cmd->key_str)
    {   
        printf("Do RSA_FileEncryption failed - No RSA Key file specified\n");
        return -1;                        
    }           
        
    rsa = ReadRSAKey(cmd->key_str); 
    
    //PrintRSAKey(rsa);
    
    switch(cmd->op_code)
    {                    
    case CIPHER_ENCRYPTION:
        if (SignRSA(cmd->sfile, cmd->dfile, rsa)<0)                   
        {        
            printf("Do RSA_FileEncryption failed - Sign RSA failed\n");
            return -1;                        
        }                
        break;
        
    case CIPHER_DECRYPTION:    
        if (UnsignRSA(cmd->sfile, cmd->dfile, rsa)<0)                   
        {        
            printf("Do RSA_FileDecryption failed - Unsign RSA failed\n");
            return -1;                        
        }               
        break;                       
    }
           
    return 0;
}
