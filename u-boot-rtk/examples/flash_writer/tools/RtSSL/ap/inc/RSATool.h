#ifndef __RSA_TOOL_H__ 
#define __RSA_TOOL_H__ 

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

typedef enum {
    RSA_CMD_UNKNOWN,    
    RSA_CMD_HELP,    
    RSA_CMD_GEN_RSA,    
    RSA_CMD_PRINT_RSA,    
    RSA_CMD_VERIFY,    
    RSA_CMD_EXP_PUBLIC,    
}RSA_CMD_ID;


#define RSA_DEFAULT_NUM_BITS           1024
#define RSA_DEFAULT_PUBLIC_EXPONENT    65537 

typedef struct {
    unsigned char       op_code;        //     
    char*               sfile;          // input file
    char*               dfile;          // output file
    unsigned int        numbits;        // length of rsa key    
    unsigned char       flags;
}RSA_CMD;


typedef enum {
    RSA_KEY_INFO_N   = 0x01,    
    RSA_KEY_INFO_E   = 0x02,    
    RSA_KEY_INFO_D   = 0x04,       
    RSA_KEY_INFO_P   = 0x08,       
    RSA_KEY_INFO_Q   = 0x10,   
    RSA_KEY_INFO_ALL = 0x00,   
}RSA_KEY_INFO;

//////////////////////// Low Level APIs ////////////////////////////

extern int GenerateRSAKey(int numbit, unsigned long pub_exp, char *outfile);   
extern RSA* ReadRSAKey(char *infile);
extern void PrintRSAKey(RSA *rsa, unsigned char inf, char* outfile);
extern int SignRSA(char* infile, char* outfile, RSA* rsa);
extern int UnsignRSA(char* infile, char* outfile, RSA* rsa);

/////////////////////// SHELL /////////////////////
extern int DoRSACommand(RSA_CMD* cmd);
extern int ParseRSACommand(int argc, char *argv[], RSA_CMD* cmd);

#endif // __RSA_TOOL_H__ 
