#ifndef __FILE_HASH_H__
#define __FILE_HASH_H__


#define MAX_HASH_LENGTH             1024
#define DEFAULT_HASH_BLOCK_SIZE     (512*1024)
#include "FileIO.h"


typedef struct {
    char*  algo_str;       // sign algorithm
    char*  key_str;        // key
    char*  iv_str;         // initial vector
}SIGN_ALGO;


typedef struct {
    unsigned char       op_code;        // should be                                                 
    unsigned char       vmode;        // should be                                                 
    unsigned char       append_padding;
    unsigned char       append_sha256;
    unsigned char       output_hash;
    char*               algo_str;       // hash algo
    char*               sfile;          // input file
    char*               dfile;          // output file
    char*               dhashfile;      // output file
    FILE_FORMAT         fmt;
    unsigned long       block_size;   
    unsigned long       offset;         // data offset
    unsigned long       length;         // length    
    SIGN_ALGO           sign;
    char                separator;
    
}HASH_CMD;

#define HASH_VERBOSE_MODE    0x80
#define HASH_SHOW_PROGRESS   0x40
#define HASH_FOR_EACH_BLOCK  0x20
#define HASH_OUT_IN_ASCII        0x08
#define HASH_OUT_WITH_SEPARATOR  0x04


typedef enum {
    DIGEST_UNKNOWN,
    DIGEST_HELP,
    DIGEST_GENERATE_HASH_VALUE,
    DIGEST_APPEND_HASH_VALUE,
    DIGEST_STRIP_HASH_VALUE,
    DIGEST_CHECK_HASH_VALUE,
};


int SignHashValue(SIGN_ALGO* sign, unsigned char* hash, unsigned int hash_len);

int GenerateHashValue(HASH_CMD* cmd);

int CheckHashValue(HASH_CMD* cmd);

int GetSignedHashLength(const char* hash_algo, SIGN_ALGO* sign);  

#endif  //__FILE_HASH_H__
