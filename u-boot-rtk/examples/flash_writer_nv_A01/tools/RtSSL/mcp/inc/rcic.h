#ifndef __RCIC_H__
#define __RCIC_H__

#include "mcp.h"

typedef struct {
    EVP_MD_CTX      Ctx;    
	unsigned long   key;	        // really 33-bit key, counting implicit 1 top-bit
	unsigned long   crchighbit;
	unsigned long   val[2];	
	unsigned char   crc_seed[2][4];
}RCIC_CTX;


#endif // __RCIC_H__ 
