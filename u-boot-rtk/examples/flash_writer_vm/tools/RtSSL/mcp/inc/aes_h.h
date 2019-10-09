#ifndef __AES_H_H__
#define __AES_H_H__

#include "mcp.h"


typedef struct {    
    unsigned char Hash[16];
    unsigned long ByteCount;
    
    // if the data is not 16 bytes alignment. the remain data will
    // be but over here.
    unsigned char Remain[32]; 
    unsigned char RemainBytes;
}AES_H_CTX;


#endif // __AES_H_H__ 
