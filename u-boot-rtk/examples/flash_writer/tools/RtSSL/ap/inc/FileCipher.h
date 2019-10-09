#ifndef __FILE_CIPHER_H__
#define __FILE_CIPHER_H__


typedef enum {
    CIPHER_ALGO_UNKNOWN,    
    CIPHER_ALGO_AES_128_ECB,  
    CIPHER_ALGO_AES_128_CBC,  
    CIPHER_ALGO_AES_256_ECB,  
    CIPHER_ALGO_AES_256_CBC,  
    CIPHER_ALGO_RSA,  
}CIPHER_ALGO;


typedef enum {
    CIPHER_DECRYPTION = 0,
    CIPHER_ENCRYPTION = 1,
    CIPHER_HELP,
    CIPHER_UNKNOWN  
}CIPHER_OPERATION;


typedef enum {
    NO_PADDING,
    PADDING_ZEROS,        
    PADDING_ONES
}PADDING_ALGO;

typedef struct {
    unsigned char       op_code;        // 
    char*               algo_str;       // hash algo
    char*               sfile;          // input file
    char*               dfile;          // output file                
    char*               key_str;        // key
    char*               iv_str;         // initial vector
    char*               padding_str;    // padding algo
}ENC_CMD;


int EncryptFile(ENC_CMD* cmd);

CIPHER_ALGO  GetCipherAlgoID(const char* algo_str);
PADDING_ALGO GetPaddingAlgo(const char* padding_str);
int PaddingData(PADDING_ALGO algo, unsigned char* p_data, unsigned long data_len, unsigned long aligment);

#endif  // __FILE_CIPHER_H__

