#ifndef __SHA256_H__
#define __SHA256_H__

#include "mcp.h"

typedef struct {
    EVP_MD_CTX      Ctx;    
    unsigned char   Hash[32];
}SHA256_CTX;


#endif // __SHA256_H__ 
