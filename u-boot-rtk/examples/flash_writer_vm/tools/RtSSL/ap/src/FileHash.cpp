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
#include "FileHash.h"  
#include "FileCipher.h"  
#include "mcp.h"
#include "Progress.h"




/*------------------------------------------------------------------
 * Func : FileHashing
 *
 * Desc : Compute Hash value of a file
 *
 * Parm : digest   : hash engine
 *        fname    : file to hash
 *        block_sz : block size of a file
 *        offset   : start address 
 *        length   : length of the data
 *        hash     : hash value
 *        flags    : debug flags
 *         
 * Retn : <0 failed, others length of hash value
 *------------------------------------------------------------------*/  
int FileHashing(
    MCP_MD*                 digest,
    const char*             fname,    
    unsigned long           block_sz,
    unsigned long           offset,
    unsigned long           length,
    unsigned char           hash[MAX_HASH_LENGTH],
    unsigned char           flags    
    )
{               
    FILE*           fd;
    MCP_MD_CTX      ctx;    
    unsigned char*  p_buff;
    unsigned int    hash_len = 0;        
    unsigned long   block_id = 0;
    unsigned long   proc_len = 0;                
    Progress        prog_bar(0, length, 20);
    
    //printf("file hashing. fname=%s, block_sz=%d, offset=%lu, length = %lu\n",
    //        fname, block_sz, offset, length);
                                       
    if (!(fd = fopen(fname, "rb")))
    {        
        printf("Compute hash value failed - open file failed\n");
        goto err_open_file_failed; 
    }    
    
    if (!(p_buff = (unsigned char*) malloc(block_sz + 32)))
    {
        printf("Compute hash value failed - alloc memory failed\n");
        goto err_alloc_memory_failed;    
    }            
    
    //-----------------------------------
    // start
    //-----------------------------------    
    //printf("offset=%d, length=%d\n", offset, length);
    fseek(fd, offset, SEEK_SET);            
        
    MCP_MD_CTX_init(&ctx);        
    
    MCP_DigestInit(&ctx, digest);                            
            
    while (length && !feof(fd))
    {
        int len = fread(p_buff, 1, (length >block_sz) ? block_sz : length, fd);        
                                
        if (len > 0)
        {                                                                           
            MCP_DigestUpdate(&ctx, p_buff, len);                                                                              

            if (flags & HASH_VERBOSE_MODE)
            {   
                if (MCP_DigestPeek(&ctx, hash, &hash_len)==0)
                {                    
                    printf("\n********* Block[%d] : %d-%d **********\n", block_id++, proc_len, proc_len+len);
                                                                    
                    dump_mem_with_text("hash value", hash, hash_len);                                                                                 
                }                    
            }                          
            length   -= len;
            proc_len += len;  
                
            if (flags & HASH_SHOW_PROGRESS)            
                prog_bar.Show(proc_len);
        }
    }            
    
    MCP_DigestFinal(&ctx, hash, &hash_len);     
    
    MCP_MD_CTX_cleanup(&ctx);   
    
    if (flags & HASH_VERBOSE_MODE)    
        dump_mem_with_text("hash value compute completed : hash value", hash, hash_len);    

    if (flags & HASH_SHOW_PROGRESS)            
        printf("\n");
        
    free(p_buff);
    
    fclose(fd);
    
    return hash_len;
           
err_invalid_region:
    free(p_buff);                    
    
err_alloc_memory_failed:
    fclose(fd);
            
err_open_file_failed:    
    
    return -1;
}



/*------------------------------------------------------------------
 * Func : DoHash
 *
 * Desc : Compute Hash value of a file
 *
 * Parm : FName : file name
 *        
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int DoHash(
    HASH_CMD*               cmd,
    unsigned char           hash[MAX_HASH_LENGTH]
    )
{    
    MCP_MD* digest = MCP_GetDigestByName(cmd->algo_str);    
    int  hash_len = -1;
        
    if (!digest)
    {
        printf("Generate hash failed - unknown algorithm %s\n", cmd->algo_str);
        return -1;
    }                  
    
    if (cmd->fmt.type == FMT_NAND_IMAGE)
    {        
        if (StripNandImgae(cmd->sfile, ".sfile.strip", &cmd->fmt.nand)<0)                    
        {
            printf("Generate hash value failed - strip Nand image file failed\n");
            return -1;
        }            
            
        cmd->sfile = ".sfile.strip";
    }    
                                 
    hash_len = FileHashing(digest, cmd->sfile, (cmd->block_size) ? cmd->block_size : DEFAULT_HASH_BLOCK_SIZE, cmd->offset, cmd->length, hash, cmd->vmode);
      
    return SignHashValue(&cmd->sign, hash, hash_len);                    
}



/*------------------------------------------------------------------
 * Func : SignHashValue
 *
 * Desc : Sign Hash value
 *
 * Parm : algo : file name 
 *         
 * Retn : < 0 : failed, other : length of signed value
 *------------------------------------------------------------------*/
int SignHashValue(SIGN_ALGO* sign, unsigned char* hash, unsigned int hash_len)
{
    ENC_CMD enc;
    int ret;
    int flen;
    
    if (sign->algo_str)
    {
        memset(&enc, 0, sizeof(ENC_CMD));
        enc.op_code  = CIPHER_ENCRYPTION;
        enc.algo_str = sign->algo_str;    
        enc.sfile    = ".hash_in";
        enc.dfile    = ".hash_out";
        enc.key_str  = sign->key_str;
        enc.iv_str   = sign->iv_str;

        MemoryToFile(".hash_in", hash, hash_len);
    
        EncryptFile(&enc);
        hash_len = GetFileLength(".hash_out");        
        ReadDataFromFile(".hash_out", hash, hash_len, 0);
    }        
    
    return hash_len;    
}




/*------------------------------------------------------------------
 * Func : GetSignedHashLength
 *
 * Desc : this function will return a length of hash value after sign
 *
 * Parm : algo : file name 
 *        hash_algo : has algo
 *         
 * Retn : < 0 : failed, other : length of signed value
 *------------------------------------------------------------------*/
int GetSignedHashLength(const char* hash_algo, SIGN_ALGO* sign)
{
    MCP_MD* digest = MCP_GetDigestByName(hash_algo);
    unsigned char hash[MAX_HASH_LENGTH];    
    return (sign && digest) ? SignHashValue(sign, hash, digest->digest_sz) : 0;          
}





/*------------------------------------------------------------------
 * Func : GenerateHashValue
 *
 * Desc : Compute Hash value of a file
 *
 * Parm : FName : file name
 *        
 *         
 * Retn : N/A
 *------------------------------------------------------------------*/
int GenerateHashValue(
    HASH_CMD*               cmd
    )
{    
    unsigned char hash[MAX_HASH_LENGTH];            
    unsigned long data_length = 0;
    unsigned long segment_size = 0;
    unsigned long hash_len = 0;
    FILE* fout;
    int ret;
                
    data_length = (cmd->length!=FILE_END) ? cmd->length : GetFileLength(cmd->sfile);        
        
    segment_size = (cmd->vmode & HASH_FOR_EACH_BLOCK) ? cmd->block_size : data_length;   

    fout = fopen(cmd->dfile, "wb");                  
    
    if (fout==NULL)
    {
        printf("\ncompute hash value of '%s' failed, open tmp hash file -'%s' failed\n", cmd->dfile); 
        return -1;
    }

    cmd->length = segment_size;
                            
    while(data_length >= segment_size)
    {                                           
        if ((ret = DoHash(cmd, hash))<0)
        {
            printf("\ncompute hash value of '%s' failed\n", cmd->sfile);  
            return -1;
        }

        fwrite(hash, 1, ret, fout);                                              
        
        // generate hash for next block 
        cmd->offset += segment_size;
        data_length -= segment_size;
        hash_len += ret;
    }
    
    fclose(fout);    
                  
    return ret;
}    


#define HASH_TMP1   ".hash1.tmp"
#define HASH_TMP2   ".hash2.tmp"

/*------------------------------------------------------------------
 * Func : CheckHashValue
 *
 * Desc : Check File Hash Value
 *
 * Parm : cmd : file name
 *         
 * Retn : < 0 : failed, success : length of hash value
 *------------------------------------------------------------------*/  
int CheckHashValue(HASH_CMD* cmd)
{        
    int hash_len = GetSignedHashLength(cmd->algo_str, &cmd->sign);
    int ret = -1;        
    unsigned long file_size = GetFileLength(cmd->sfile);
    unsigned long data_length;
     
    if (cmd->offset > file_size)             
        return -1;
        
    if (cmd->length==FILE_END)        
    {
        data_length = file_size-cmd->offset;
        
        if (cmd->vmode & HASH_FOR_EACH_BLOCK)
            hash_len *= (data_length/(cmd->block_size+hash_len));
                                    
        data_length -= hash_len;              
        cmd->length = data_length;
    }
    else 
    {        
        data_length = cmd->length;    
        if (cmd->vmode & HASH_FOR_EACH_BLOCK)
            hash_len *= (data_length/(cmd->block_size));   
    }

    //printf("file size = %d, ofst=%d, length=%d, data_len=%d, hash_len=%d\n", 
    //        file_size, cmd->offset,cmd->length, data_length, hash_len);        

    FileCut(cmd->sfile, HASH_TMP1, file_size-hash_len, file_size);       
    
    //printf("ofst = %d, length=%d\n", cmd->offset,cmd->length);            
          
    cmd->dfile  = HASH_TMP2;
    GenerateHashValue(cmd);
    
    if (FileCompare(HASH_TMP1, HASH_TMP2)<0)
        return -1;

    return hash_len;        
}
