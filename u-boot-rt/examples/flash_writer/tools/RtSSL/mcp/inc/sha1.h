#ifndef __SHA1_H__
#define __SHA1_H__

#include "mcp.h"

typedef struct {
    EVP_MD_CTX      Ctx;
    unsigned char   Hash[20];       // for Mars SHA1
}SHA1_CTX;


#endif // __SHA1_H__ 
