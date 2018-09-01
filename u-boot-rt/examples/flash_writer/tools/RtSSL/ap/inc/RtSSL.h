#ifndef __FILE_HASH_GENERATOR_H__
#define __FILE_HASH_GENERATOR_H__

#include "FileCipher.h"
#include "FileHash.h"
#include "RSATool.h"


typedef enum {
    CMD_UNKNOWN,
    CMD_DIGEST,
    CMD_CIPHER,    
    CMD_RSA,  
    CMD_FILE, 
    CMD_HELP,
    CMD_VERSION,
};

    
typedef struct{        
        
    unsigned char  type;            // command type        
    
    union {
        
        HASH_CMD    hash;
    
        ENC_CMD     enc;
        
        RSA_CMD     rsa;
        
        FILE_CMD    file;
    };
    
}CMD_STR;



///////////////////////////////////////////////////////////
// Hash
///////////////////////////////////////////////////////////
int ParseHashCommand(int argc, char *argv[], CMD_STR* cmd);
int DoHashCommand(HASH_CMD* cmd);


///////////////////////////////////////////////////////////
// Cipher
///////////////////////////////////////////////////////////
int ParseCipherCommand(int argc, char *argv[], CMD_STR* cmd);
int DoCipherCommand(ENC_CMD* cmd);


///////////////////////////////////////////////////////////
// Misc
///////////////////////////////////////////////////////////
int DoHelp();



#endif // __FILE_HASH_GENERATOR_H__
