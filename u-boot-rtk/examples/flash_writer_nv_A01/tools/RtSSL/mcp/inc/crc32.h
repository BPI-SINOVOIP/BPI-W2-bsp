#ifndef __CRC32_H__
#define __CRC32_H__

#include "mcp.h"

typedef struct {
    EVP_MD_CTX      Ctx;    
	unsigned long   key;	        // really 33-bit key, counting implicit 1 top-bit
	unsigned long   crchighbit;
	unsigned long   val;	
}CRC32_CTX;


#endif // __CRC32_H__ 
