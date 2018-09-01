#ifndef __HAMC_256__
#define __HAMC_256__

#include "dvrboot_inc/util.h"


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int  uint32_t;
typedef unsigned long uint64_t;






struct HASH_CTX;  // forward decl
#define SHA256_DIGEST_SIZE 32


typedef struct HASH_VTAB {
    void (* const init)(struct HASH_CTX *);
    void (* const update)(struct HASH_CTX *, const void *, int);
    const uint8_t *(* const final)(struct HASH_CTX *);
    const uint8_t *(* const hash)(const void *, int, uint8_t *);
    int size;
} HASH_VTAB;


typedef struct HASH_CTX {
    const HASH_VTAB *f;
    uint64_t count;
    uint8_t buf[64];
    uint32_t state[8];  // upto SHA2
} HASH_CTX;

#define HASH_init(ctx) (ctx)->f->init(ctx)
#define HASH_update(ctx, data, len) (ctx)->f->update(ctx, data, len)
#define HASH_final(ctx) (ctx)->f->final(ctx)
#define HASH_hash(data, len, digest) (ctx)->f->hash(data, len, digest)
#define HASH_size(ctx) (ctx)->f->size

typedef HASH_CTX SHA256_CTX;


/* function declaration*/
extern void SHA256_init(SHA256_CTX *ctx);
extern void SHA256_update(SHA256_CTX *ctx, const void *data, int len);
extern const uint8_t *SHA256_final(SHA256_CTX *ctx);




#endif
