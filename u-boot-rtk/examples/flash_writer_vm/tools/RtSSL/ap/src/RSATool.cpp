#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "auxfun.h" 
#include "FileIO.h"   
#include "RSATool.h" 
  
  


/////////////////////// SHELL /////////////////////



/*------------------------------------------------------------------
 * Func : ParseRSACommand
 *
 * Desc : Parse RSA Command
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int ParseRSACommand(int argc, char *argv[], RSA_CMD* cmd)
{    
    long     val = 0;            
    int      i;
        
    if (argc < 3)            
        return 0;    
        
    cmd->op_code = RSA_CMD_HELP;   
    cmd->numbits = RSA_DEFAULT_NUM_BITS;                     
      
    if (strcmp(argv[2], "-gen")==0)                                         
        cmd->op_code = RSA_CMD_GEN_RSA;                     
    else if (strcmp(argv[2],"-print")==0)             
        cmd->op_code = RSA_CMD_PRINT_RSA;
    else if (strcmp(argv[2],"-check")==0)                     
        cmd->op_code = RSA_CMD_VERIFY;
    else if (strcmp(argv[2],"-help")==0)             
        cmd->op_code = RSA_CMD_HELP;    
    else
    {
        printf("RtSSL Error: invalid opcode %s for RSA operation, please use './RtSSL rsa -help' to get more information\n", argv[2]); 
        return 0;
    }                    
    
    for (i=3; i<argc; i++)
    {                                                        
        if (strcmp(argv[i], "-i")==0)                                         
            cmd->sfile = argv[++i];              // input file                            
        else if (strcmp(argv[i],"-o")==0)             
            cmd->dfile = argv[++i];              // destination file            
        else if (strncmp(argv[i],"-b=",3)==0)
        {
            if (_str_to_long(argv[i]+3, &val, 10)< 0)
            {
                printf("RtSSL Error: invalid number of bits '%s', please use './RtSSL rsa -help' to get more information\n", argv[2]);                 
                return -1;
            } 

            cmd->numbits = val;                      
        }           
        else
        {   
            if (cmd->op_code==RSA_CMD_PRINT_RSA)
            {
                if (strcmp(argv[i], "-modulous")==0)
                {                    
                    cmd->flags = RSA_KEY_INFO_N;
                    continue;
                }                    
                else if (strcmp(argv[i],"-pub_exp")==0)
                {                    
                    cmd->flags = RSA_KEY_INFO_E;
                    continue;
                }                    
                else if (strcmp(argv[i],"-pri_exp")==0)
                {                    
                    cmd->flags = RSA_KEY_INFO_D;
                    continue;
                }                    
                else if (strcmp(argv[i],"-all")==0)                                             
                {                    
                    cmd->flags = RSA_KEY_INFO_ALL;                
                    continue;
                }
                                        
            }                  
            printf("unknown parameter %s\n", argv[i]);
            return -1;
        }                                                
    }       

    return 0;            
}




/*------------------------------------------------------------------
 * Func : DoRSAHelp
 *
 * Desc : Do Help
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoRSAHelp()
{    
    printf("                                                    \n");    
    printf(" @@@ Realtek RSA Tool                               \n");
    printf("                                                    \n");    
    printf(" Format : RtSSL rsa <opcode> <params>               \n");    
    printf("                                                    \n");        
    printf("   <opcode> : operations                            \n");
    printf("      -gen     : generate a rsa key file            \n");
    printf("      -check   : verify the consistency of arsa key \n");        
    printf("      -print   : print components of a private key of a rsa key file \n");        
    printf("                                                    \n");        
    printf("  Generate a rsa key :                               \n");    
    printf("                                                    \n");        
    printf("    RtSSL rsa -gen [-b=<number of bits>] [-pub_exp=<public exp>] -o <output>\n");        
    printf("                                                    \n");    
    printf("    <number of bits> : length of RSA key in bits    \n");     
    printf("                       default: 1024                \n");        
    printf("                                                    \n");            
    printf("  Export a rsa key :                                 \n");    
    printf("                                                    \n");        
    printf("    RtSSL rsa -pubout -i <key file> -o <output>     \n");        
    printf("                                                    \n");                    
    printf("  Verify a rsa key :                                 \n");    
    printf("                                                    \n");        
    printf("    RtSSL rsa -check -i <key file>                  \n");        
    printf("                                                    \n");                
    printf("  Print a rsa key :                                 \n");    
    printf("                                                    \n");        
    printf("    RtSSL rsa -print <info> -i <key file> -o <output> \n");        
    printf("                                                    \n");       
    printf("    <info> : what info to print                     \n");     
    printf("         -all      : all info                       \n");   
    printf("         -modulous : print modulous only            \n");        
    printf("         -pub_exp  : print public exponent          \n");        
    printf("         -pri_exp  : print private exponent         \n");        
    printf("                                                    \n");            
    return 0;
}




/*------------------------------------------------------------------
 * Func : DoRSACommand
 *
 * Desc : Execute RSA Command
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoRSACommand(RSA_CMD* cmd)
{
    int  ret = 0;    
    RSA* rsa = NULL;

    switch(cmd->op_code)
    {        
    case RSA_CMD_GEN_RSA:
        ret = GenerateRSAKey(cmd->numbits, RSA_DEFAULT_PUBLIC_EXPONENT, cmd->dfile);      
        break;        
        
    case RSA_CMD_PRINT_RSA:      
        
        rsa = ReadRSAKey(cmd->sfile);
        
        if (!rsa)
        {
            printf("RtSSL Error: Print RSA key failed, read rsa key failed\n");                 
            return -1;
        }            
        
        PrintRSAKey(rsa, cmd->flags, cmd->dfile);
        return 0;        
  
    case RSA_CMD_VERIFY:   
        
        rsa = ReadRSAKey(cmd->sfile);
        
        if (!rsa)
        {
            printf("RtSSL Error: Verify RSA key failed, read rsa key failed\n");                 
            return -1;
        }            
    
        ret = RSA_check_key(rsa);
        
        if (ret <0)
        {
            printf("RtSSL Error: Verify RSA key failed, error occur while checking rsa key '%s'\n", cmd->sfile);                 
            return ret;
        }            
            
        if (ret)        
            printf("RtSSL Info: RSA Key '%s' is correct\n", cmd->sfile);            
        else            
            printf("RtSSL Info: RSA Key '%s' is wrong\n", cmd->sfile);
                    
        return 0;                                
        
    case RSA_CMD_EXP_PUBLIC:                             
    
    default:                
    case RSA_CMD_HELP:
        ret = DoRSAHelp();
        break;            
    }     
            
    return ret;        
}



/////////////////////////////////////////////////////////////////////
// RSA APIs
/////////////////////////////////////////////////////////////////////



/*------------------------------------------------------------------
 * Func : ShowError
 *
 * Desc : Display Error Message
 * 
 * Parm : N/A
 * 
 * Retn : N/A
 *------------------------------------------------------------------*/ 
static void ShowError(void)
{
	unsigned long err_code;
	char err_msg[512];

	err_code = ERR_get_error();
	ERR_error_string(err_code, err_msg);
	printf("=> %s\n", err_msg);
	printf("=>lib err : %s\n", ERR_lib_error_string(err_code));
	printf("=>func err : %s\n", ERR_func_error_string(err_code));
	printf("=>reason err :  %s\n", ERR_reason_error_string(err_code));
}


#ifdef RSA_USE_SYSTEM_CALL

/*------------------------------------------------------------------
 * Func : GenerateRSAKey
 *
 * Desc : Generate RSA Key
 * 
 * Parm : 
 *
 * Retn : handle of RSA key
 *------------------------------------------------------------------*/
int GenerateRSAKey(int numbit, unsigned long pub_exp, char *outfile)
{
    char buff[256];
        
    if (outfile == NULL) 
    {		
        printf("generte rsa key failed - no output file specified\n");
		return -1;
	}
			
    if (pub_exp==3)            
        sprintf(buff, "openssl genrsa -out %s -3 %d\n", outfile, numbit);    
    else    
        sprintf(buff, "openssl genrsa -out %s %d\n", outfile, numbit);         
        
    return system(buff);
}

    
#else


/*------------------------------------------------------------------
 * Func : GenerateRSAKey
 *
 * Desc : Generate RSA Key
 * 
 * Parm : 
 *
 * Retn : handle of RSA key
 *------------------------------------------------------------------*/
int GenerateRSAKey(int numbit, unsigned long pub_exp, char *outfile)
{
	RSA *rsa;
	BIO *out;
	const EVP_CIPHER *enc = NULL;
	int res = 1;

	// create file or use stdout instead
	if (outfile == NULL) 
		out = BIO_new_fp(stdout, BIO_NOCLOSE);
	else 
		out = BIO_new_file(outfile, "w");

	if (out == NULL) {
		ShowError();
		return -1;
	}
    
	rsa = RSA_generate_key(numbit, pub_exp, NULL, NULL);
	if (rsa == NULL) {
		ShowError();
		res = -2;
		goto generate_RSA_final;
	}

#if 1
	// save RSA key
	if (!PEM_write_bio_RSAPrivateKey(out, rsa, enc, NULL, 0, NULL, NULL)) 
	    goto generate_RSA_final;
#endif
	res = 0;	

generate_RSA_final:
	if (rsa) RSA_free(rsa);
	if (out) BIO_free_all(out);
		
	return res;
}	
  

#endif  





/*------------------------------------------------------------------
 * Func : ReadRSAKey
 *
 * Desc : Read RSA Key
 * 
 * Parm : 
 *
 * Retn : handle of RSA key
 *------------------------------------------------------------------*/
RSA* ReadRSAKey(char *infile)
{
	RSA *rsa;
	BIO *in, *out;
	EVP_PKEY *pkey = NULL;

	if (infile == NULL) {
		printf("invalid argument\n");
		return NULL;
	}

	in = BIO_new_file(infile, "r"); 
	if (in == NULL) {
		printf("open %s failed\n", infile);
		ShowError();
		return NULL;
	}

	pkey = (EVP_PKEY *) PEM_read_bio_PrivateKey(in, NULL, NULL, NULL);
	rsa = pkey == NULL ? NULL : (RSA *) EVP_PKEY_get1_RSA(pkey);
	EVP_PKEY_free(pkey);

	if (rsa == NULL) {
		printf("get RSA key failed\n");
		ShowError();
	}
    
	if (in) BIO_free_all(in);
	return rsa;
}
  
  


/*------------------------------------------------------------------
 * Func : PrintRSAKey
 *
 * Desc : PrintRSAKey
 * 
 * Parm : 
 *
 * Retn : handle of RSA key
 *------------------------------------------------------------------*/
void PrintRSAKey(RSA *rsa, unsigned char inf, char* outfile)
{
	BIO *out;
    int key_info = RSA_KEY_INFO_N;
    
	if (rsa == NULL) {
		printf("RSA key is null!\n");
		return;
	}
		
	// create file or use stdout instead
	if (outfile == NULL) 
		out = BIO_new_fp(stdout, BIO_NOCLOSE);
	else 
		out = BIO_new_file(outfile, "w");

	if (out == NULL) 
    {
        printf("RtSSL Error: RSA_DumpKeyInfo RSA key info failed, open output file failed\n");
		ShowError();
		return;
	}    
            
	switch(inf)
	{
    case RSA_KEY_INFO_ALL:	    		
	    RSA_print(out, rsa, 0);	
	    break;
    case RSA_KEY_INFO_N:
        BN_print(out,rsa->n);
        break;
    case RSA_KEY_INFO_E:
        BN_print(out,rsa->e);
        break;
    case RSA_KEY_INFO_D:
        BN_print(out,rsa->d);
        break;
    }	   
    BIO_printf(out,"\n"); 
	BIO_free_all(out);	
}
    



/*------------------------------------------------------------------
 * Func : load_data_from_file
 *
 * Desc : load data to memory
 * 
 * Parm : 
 * Retn : <0 failed, others length of hash value
 *------------------------------------------------------------------*/ 
int load_data_from_file(char *infile, unsigned char **buf, int *buf_size)
{
	FILE *fp;

	fp = fopen(infile, "r");
	if (fp == NULL) 
		return -1;
	
	fseek(fp, 0, SEEK_END);
	*buf_size = ftell(fp);
	rewind(fp);
	*buf = (unsigned char*) malloc(*buf_size);

	if (*buf == NULL) {
		//printf("malloc(%d) failed\n", *buf_size);
		fclose(fp);
		return -1;
	}
	
	//memset(*buf, 0, *buf_size);
	fread(*buf, sizeof(char), *buf_size, fp);
	fclose(fp);
	return 0;
}





/*------------------------------------------------------------------
 * Func : SignRSA
 *
 * Desc : Sign with RSA
 *
 
 * Parm : 
 * Retn : <0 failed, others for success
 *------------------------------------------------------------------*/ 
int SignRSA(
    char*                   infile, 
    char*                   outfile, 
    RSA*                    rsa
    )
{
	BIO *out;
	unsigned char *inbuf, *outbuf;
	int inbuf_size, outbuf_size;
	int res;

	if ((infile == NULL) || (rsa == NULL) ) 
    {
		printf("SignRSA failed - invalid argument\n");
		return -1;
	}

	if (load_data_from_file(infile, &inbuf, &inbuf_size)) {
		printf("SignRSA failed - read from %s failed\n", infile);
		return -1;
	}

	outbuf_size = RSA_size(rsa);
	outbuf = (unsigned char*) malloc(outbuf_size);
	if (outbuf == NULL) {
		printf("malloc(%d) failed\n", outbuf_size);
		BIO_free(out);
		return -1;
	}

	res = RSA_private_encrypt(inbuf_size, inbuf, outbuf, rsa, RSA_PKCS1_PADDING);
	if (res == -1) {
        printf("SignRSA failed - encrypt data with provate key failed\n");
        printf("inbuf_size = %d, inbuf=%p, outbuf=%p\n", inbuf_size, inbuf, outbuf);
        
		ShowError();
		BIO_free(out);
		return -1;
	}

	// write the size of the signature (i.e., RSA_size(rsa))
	if (outfile == NULL)
		// output to stdout
		out = BIO_new_fp(stdout, BIO_NOCLOSE);
	else
		out = BIO_new_file(outfile, "w");
	
	if (out == NULL) {
		ShowError();
		return -1;
	}

	BIO_write(out, outbuf, res);
	//dump_mem_with_text("res",outbuf, res);
	BIO_free(out);
	return res;
}
 






/*------------------------------------------------------------------
 * Func : UnsignRSA
 *
 * Desc : Unsign with RSA
 *
 
 * Parm : 
 * Retn : <0 failed, others for success
 *------------------------------------------------------------------*/ 
int UnsignRSA(
    char*                   infile, 
    char*                   outfile, 
    RSA*                    rsa
    )
{
	BIO *out;
	unsigned char *inbuf, *outbuf;
	int inbuf_size, outbuf_size;
	int res;

	if ((infile == NULL) || (rsa == NULL) ) 
    {
		printf("SignRSA failed - invalid argument\n");
		return -1;
	}

	if (load_data_from_file(infile, &inbuf, &inbuf_size)) {
		printf("SignRSA failed - read from %s failed\n", infile);
		return -1;
	}

	outbuf_size = RSA_size(rsa);
	outbuf = (unsigned char*) malloc(outbuf_size);
	if (outbuf == NULL) {
		printf("malloc(%d) failed\n", outbuf_size);
		BIO_free(out);
		return -1;
	}

	res = RSA_public_decrypt(inbuf_size, inbuf, outbuf, rsa, RSA_PKCS1_PADDING);
	if (res == -1) {
        printf("UnsignRSA failed - decrypt data with public key failed\n");
        printf("inbuf_size = %d, inbuf=%p, outbuf=%p\n", inbuf_size, inbuf, outbuf);
        
		ShowError();
		BIO_free(out);
		return -1;
	}

	// write the size of the signature (i.e., RSA_size(rsa))
	if (outfile == NULL)
		// output to stdout
		out = BIO_new_fp(stdout, BIO_NOCLOSE);
	else
		out = BIO_new_file(outfile, "w");
	
	if (out == NULL) {
		ShowError();
		return -1;
	}

	BIO_write(out, outbuf, res);
	//dump_mem_with_text("res",outbuf, res);
	BIO_free(out);
	return res;
}
 

