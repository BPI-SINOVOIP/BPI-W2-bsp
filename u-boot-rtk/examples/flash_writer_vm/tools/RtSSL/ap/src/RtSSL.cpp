#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "auxfun.h"
#include "FileIO.h"
#include "RtSSL.h"



//////////////////////////////////////////////////////////////////////
// Cipher
//////////////////////////////////////////////////////////////////////


unsigned char str_to_cmd_type(const char* str)
{
    if      (strcmp(str,"enc")==0)   return CMD_CIPHER;
    else if (strcmp(str,"dgst")==0)  return CMD_DIGEST;
    else if (strcmp(str,"rsa")==0)   return CMD_RSA;
    else if (strcmp(str,"file")==0)  return CMD_FILE;
    else if (strcmp(str,"help")==0)  return CMD_HELP;
    else if (strcmp(str,"ver")==0)   return CMD_VERSION;
    else                             return CMD_UNKNOWN;
}


/*------------------------------------------------------------------
 * Func : ParseCommand
 *
 * Desc : Parse Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int ParseCommand(int argc, char *argv[], CMD_STR* cmd)
{
    memset(cmd,0, sizeof(CMD_STR));
    cmd->type = CMD_HELP;

    if (argc > 1)
    {
        cmd->type = str_to_cmd_type(argv[1]);

        switch(cmd->type)
        {
        case CMD_DIGEST:
            return ParseHashCommand(argc, argv, cmd);

        case CMD_CIPHER:
            return ParseCipherCommand(argc, argv, cmd);

        case CMD_RSA:
            return ParseRSACommand(argc, argv, &cmd->rsa);

        case CMD_FILE:
            return ParseFileCommand(argc, argv, &cmd->file);

        case CMD_HELP:
        case CMD_VERSION:
            return 0;

        default:
            printf("RtSSL Error: Unknown command type %s, \n", argv[1]);
        }
    }

    return 0;
}




/*------------------------------------------------------------------
 * Func : Execute Command
 *
 * Desc : Execute Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoCommand(CMD_STR* cmd)
{
    switch(cmd->type)
    {
    case CMD_DIGEST:
        return DoHashCommand(&cmd->hash);

    case CMD_CIPHER:
        return DoCipherCommand(&cmd->enc);

    case CMD_RSA:
        return DoRSACommand(&cmd->rsa);

    case CMD_FILE:
        return DoFileCommand(&cmd->file);

    case CMD_HELP:
        return DoHelp();

    case CMD_VERSION:
        return 0;
    }

    return 0;
}



//////////////////////////////////////////////////////////////////////
// Help
//////////////////////////////////////////////////////////////////////



/*------------------------------------------------------------------
 * Func : DoHelpCommand
 *
 * Desc : Do Help
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoHelp()
{
    printf("                                                    \n");
    printf(" @@@ RtSSL : Realtek SSL tool                       \n");
    printf("                                                    \n");
    printf(" Format : RtSSL <opcode> [<params>]                 \n");
    printf("                                                    \n");
    printf("   <opcode> : operations                            \n");
    printf("      dgst  : Hash Value Operation                  \n");
    printf("      enc   : File Encryption/Decryption            \n");
    printf("      rsa   : RSA key Operation                     \n");
    printf("      file  : File Operation                        \n");
    printf("      help  : Help                                  \n");
    printf("                                                    \n");
    return 0;
}




//////////////////////////////////////////////////////////////////////
// Cipher
//////////////////////////////////////////////////////////////////////



/*------------------------------------------------------------------
 * Func : ParseCipherCommand
 *
 * Desc : Parse Cipher Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int ParseCipherCommand(int argc, char *argv[], CMD_STR* cmd)
{
    ENC_CMD* enc = &cmd->enc;

    if (argc < 3)
    {
        enc->op_code = CIPHER_HELP;
        printf("\nRtSSL Error: No enough parameters for enc command, please use './RtSSL enc -h' to get more information\n\n");
        return -1;
    }

    if (strcmp(argv[2],"-d")==0)
        enc->op_code = CIPHER_DECRYPTION;
    else if (strcmp(argv[2],"-e")==0)
        enc->op_code = CIPHER_ENCRYPTION;
    else if (strcmp(argv[2],"-h")==0)
    {
        enc->op_code = CIPHER_HELP;
        return 0;
    }
    else
    {
        printf("RtSSL Error: no opcode specified, please use './RtSSL enc -h' to get more information\n");
        return -1;
    }

    if (argc <3)
    {
        printf("RtSSL Error: no algo specified, please use 'enc -h' to get more information\n");
        return -1;
    }
    else if (*argv[3]!='-')
    {
        printf("RtSSL Error: invalid algo %s, please use 'enc -h' to get more information\n", argv[3]);
        return -1;
    }

    enc->algo_str = argv[3]+1;
    //printf("enc->algo_str=%s\n",enc->algo_str);

    for (int i=4; i<argc; i++)
    {
        if (strcmp(argv[i],     "-i")==0)
            enc->sfile = argv[++i];              // input file
        else if (strcmp(argv[i],"-o")==0)
            enc->dfile = argv[++i];              // destination file
        else if (strcmp(argv[i],"-k")==0)
            enc->key_str = argv[++i];            // key
        else if (strcmp(argv[i],"-iv")==0)
            enc->iv_str = argv[++i];             // iv
        else if (strcmp(argv[i], "-p")==0)
            enc->padding_str = argv[++i];        // padding algo
        else
        {
            printf("unknown parameter %s\n", argv[i]);
            return -1;
        }
    }

    if (enc->op_code==CIPHER_UNKNOWN)
    {
        printf("RtSSL Error: no opcode specified, please use './RtSSL enc' to get more information\n");
        return -1;
    }

    return 0;
}



/*------------------------------------------------------------------
 * Func : DoHelpCommand
 *
 * Desc : Do Help
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoCipherHelp()
{
    printf("                                                    \n");
    printf(" @@@ RtSSL Encryption/Decryption Command            \n");
    printf("                                                    \n");
    printf(" Format : RtSSL enc <opcode> <algo> -i <input> [-o <output>]\n");
    printf("                    -k <key> [-iv <iv>]] [-p <pad_algo>]\n");
    printf("                                                    \n");
    printf("   <opcode> : operations                            \n");
    printf("      -e  : encrypt a file                          \n");
    printf("      -d  : decrypt a file                          \n");
    printf("      -h  : print help message                      \n");
    printf("                                                    \n");
    printf("   <algo> : which algorithm to use                  \n");
    printf("      -aes_128_ecb  : aes ecb with 128 bits key     \n");
    printf("      -aes_128_cbc  : aes cbc with 128 bits key & iv\n");
    printf("      -aes_256_ecb  : aes ecb with 256 bits key     \n");
    printf("      -aes_256_cbc  : aes cbc with 256 bits key & iv\n");
    printf("      -rsa          : rsa                           \n");
    printf("                                                    \n");
    printf("   <input>  : specify data input                    \n");
    printf("       stdin      : data comes form stdin           \n");
    printf("       file name  : data comes form a file          \n");
    printf("                                                    \n");
    printf("   <output> : specify data output                   \n");
    printf("       stdout     : output data to stdout           \n");
    printf("       file name  : output data to a file           \n");
    printf("                                                    \n");
    printf("   <key>  : key that used for data encryption/decryption\n");
    printf("   <iv>   : initial vactor that used for data encryption/decryption \n");
    printf("                                                     \n");
    printf("   <pad_algo> : padding algorithm                    \n");
    printf("       none : no padding (default)                   \n");
    printf("       0    : pad data with bit 0                    \n");
    printf("       1    : pad data with bit 1                    \n");
    printf("                                                     \n");
    printf(" Example:                                            \n");
    printf("                                                     \n");
    printf("   Encrypt file with aes_128_ecb cipher              \n");
    printf("                                                     \n");
    printf("      ./RtSSL enc -e -aes_128_ecb -k 112233445566 -i README -o README.e \n");
    printf("                                                     \n");
    printf("   Decrypt file with aes_128_ecb cipher              \n");
    printf("                                                     \n");
    printf("      ./RtSSL enc -d -aes_128_ecb -k 112233445566 -i README.e -o README.d \n");
    printf("                                                     \n");
    printf("   Display help message                              \n");
    printf("                                                     \n");
    printf("      ./RtSSL enc -h  or  ./RtSSL enc                \n");
    printf("                                                     \n");
    return 0;
}



/*------------------------------------------------------------------
 * Func : DoCipherCommand
 *
 * Desc : Execute Cipher Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoCipherCommand(ENC_CMD* cmd)
{
    int ret = 0;
    //printf("cmd->op_code = %d\n",cmd->op_code);
    switch(cmd->op_code)
    {
    case CIPHER_ENCRYPTION:
    case CIPHER_DECRYPTION:
        if (strcmp(cmd->sfile, "stdin")==0)
            DumpDataFromStdin(cmd->sfile);

        ret = EncryptFile(cmd);

        if (ret==0 && strcmp(cmd->dfile, "stdout")==0)
            DumpDataToStdout(cmd->dfile);
        break;

    default:
    case CIPHER_HELP:
        ret = DoCipherHelp();
        break;
    }
    return ret;
}




//////////////////////////////////////////////////////////////////////
// Hash
//////////////////////////////////////////////////////////////////////


/*------------------------------------------------------------------
 * Func : ParseHashCommand
 *
 * Desc : Parse Hash Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int ParseHashCommand(int argc, char *argv[], CMD_STR* cmd)
{
    HASH_CMD* hash = &cmd->hash;
    long      val;

    hash->op_code  = DIGEST_UNKNOWN;
    hash->sfile    = "stdin";
    hash->dfile    = "stdout";
    hash->offset   = FILE_START;
    hash->length   = FILE_END;

     // get algorithm
    if (argc < 3)
    {
        hash->op_code  = DIGEST_HELP;
        return 0;
    }

    if (*argv[2]!='-')
    {
        printf("RtSSL Error: invalid algo %s, please use 'dgst -h' to get more information\n", argv[2]);
        hash->op_code  = DIGEST_HELP;
        return 0;
    }

    hash->algo_str = argv[2]+1;


    //printf("hash->algo_str=%s\n",hash->algo_str);

    // get parameter
    for (int i=3; i<argc; i++)
    {
        if (strcmp(argv[i],"-i")==0)
        {
            hash->sfile   = argv[++i];
        }
        else if (strcmp(argv[i],"-o")==0)
        {
            hash->dfile   = argv[++i];
        }
        else if (strcmp(argv[i],"-g")==0)
        {
            hash->op_code = DIGEST_GENERATE_HASH_VALUE;
        }
        else if (strcmp(argv[i],"-c")==0)
        {
            hash->op_code = DIGEST_CHECK_HASH_VALUE;
        }
        else if (strcmp(argv[i],"-a")==0)
        {
            hash->op_code = DIGEST_APPEND_HASH_VALUE;
            hash->append_padding = 0;
        }
        else if (strcmp(argv[i],"-ap")==0)
        {
            hash->op_code = DIGEST_APPEND_HASH_VALUE;
            hash->append_padding = 1;
        }
        else if (strcmp(argv[i],"-aps")==0)
        {
            hash->op_code = DIGEST_APPEND_HASH_VALUE;
            hash->append_padding = 1;
            hash->append_sha256 = 1;
        }
        else if (strcmp(argv[i],"-ohash")==0)
        {
            hash->output_hash = 1;
            hash->dhashfile = argv[++i];
        }
        else if (strcmp(argv[i],"-r")==0)
        {
            hash->op_code = DIGEST_STRIP_HASH_VALUE;
        }
        else if (strcmp(argv[i],"-t")==0)
        {
            if (ParseFileFmt(argv[++i], &hash->fmt)<0)
            {
                printf("Parse hash command failed - unknown file format\n", argv[i-1]);
                return -1;
            }
        }
        else if (strncmp(argv[i],"-b=",3)==0)
        {
            if (_str_to_long(argv[i]+3, &val, 10)< 0)
            {
                printf("Parse hash command failed - invalid block size : %s \n", argv[i]+3);
                return -1;
            }

            hash->block_size = val;
        }
        else if (strncmp(argv[i],"-s=",3)==0)
        {
            if (sscanf(argv[i], "-s=%c", &hash->separator)!=1)
            {
                printf("Parse hash command failed - invalid separator : %s \n", argv[i]+3);
                return -1;
            }

            //printf("hash->separator=%c\n", hash->separator);
            hash->vmode |= HASH_OUT_WITH_SEPARATOR;
        }
        else if (strncmp(argv[i],"-ofmt=",6)==0)
        {
            if (strcmp(argv[i]+6, "ascii")==0)
                hash->vmode |= HASH_OUT_IN_ASCII;
            else if (strcmp(argv[i]+6, "binary")==0)
                hash->vmode &= ~HASH_OUT_IN_ASCII;
            else
            {
                printf("Parse hash command failed - invalid output format : %s \n", argv[i]+6);
                return -1;
            }
        }
        else if (strncmp(argv[i],"-range=",7)==0)
        {
            if (sscanf(argv[i], "-range=%lu:%lu", &hash->offset, &hash->length)!=2 || hash->length <= hash->offset)
            {
                printf("Parse hash command failed - invalid range setting : %s \n", argv[i]+7);
                return -1;
            }

            if (hash->length <= hash->offset)
            {
                printf("Parse hash command failed - end address should larger than start address\n", argv[i]+7);
                return -1;
            }

            hash->length -= hash->offset;   // compute real hash length
            //printf("offset=%d, length=%d\n", hash->offset, hash->length);
        }
        else if (strncmp(argv[i],"-v",2)==0)
        {
            hash->vmode |= HASH_VERBOSE_MODE;
        }
        else if (strncmp(argv[i],"-p",2)==0)
        {
            hash->vmode |= HASH_SHOW_PROGRESS;
        }
        else if (strncmp(argv[i],"-B",2)==0)
        {
            hash->vmode |= HASH_FOR_EACH_BLOCK;
        }
        else if (strncmp(argv[i],"-sign",5)==0)
        {
            i++;

            if (*argv[i]!='-')
            {
                printf("RtSSL Error: invalid sign algo %s, please use './RtSSL dgst' to get more information\n", argv[i]);
                return -1;
            }

            hash->sign.algo_str = argv[i++]+1;

            for (; i < argc; i++)
            {
                if (strcmp(argv[i],"-k")==0)
                {
                    hash->sign.key_str = argv[++i];
                    continue;
                }

                if (strcmp(argv[i],"-iv")==0)
                {
                    hash->sign.iv_str  = argv[++i];
                    continue;
                }

                i--;
                break;
            }
        }
        else
        {
            printf("RtSSL Error: Parse dgst command failed - unknown parameter \'%s\' \n", argv[i]);
            return -1;
        }
    }

    if (hash->op_code == DIGEST_UNKNOWN)
    {
            printf("RtSSL Error: no operation specified, please use './RtSSL dgst' for more infomation\n");
        hash->op_code  = DIGEST_HELP;
    }

    return 0;
}




/*------------------------------------------------------------------
 * Func : DoDigestHelp
 *
 * Desc : Do Digest Help
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoDigestHelp()
{
    printf("                                                    \n");
    printf(" @@@ RtSSL Digest Command                           \n");
    printf("                                                    \n");
    printf(" Format : RtSSL dgst <algo> <opcode> -i <input> [-t <fmt>][-b=<block_size>]\n");
    printf("          [ -o <output>] [-of <ofmt>] [-s <separator>] [-range=<ofst>:<end>] [-v] [-B]\n");
    printf("          [ -ohash <ohash>] [-sign <sign_algo> -k <key> [-iv <iv>]] \n");
    printf("                                                    \n");
    printf("   <algo> : algorithm that use to generate hash value\n");
    printf("      -aes_h       : aes_h hash                     \n");
    printf("      -mars_aes_h  : mars format aes_h hash         \n");
    printf("      -sha1        : sha1 hash                      \n");
    printf("      -mars_sha1   : mars format sha1 hash          \n");
    printf("      -sha256      : sha256 hash                    \n");
    printf("      -crc32       : crc32 hash                     \n");
    printf("      -rcic        : rcic hash                      \n");
    printf("                                                    \n");
    printf("   <opcode> : operations                            \n");
    printf("      -g  : generate hash value for a file          \n");
    printf("      -a  : append hash value to a file             \n");
    printf("      -ap : append padding and hash value to a file \n");
    printf("      -aps: append padding, sha256 and hash value to a file\n");
    printf("      -r  : remove hash value of a file             \n");
    printf("      -c  : check hash value of a file              \n");
    printf("                                                    \n");
    printf("   <input>  : specify data input                    \n");
    printf("       stdin      : data comes form stdin           \n");
    printf("       file name  : data comes form a file          \n");
    printf("                                                    \n");
    printf("   <fmt>  : specified input file type               \n");
    printf("       raw_data  : raw data                         \n");
    printf("       nand:<data block size>:<spare_area_size>  : nand image format\n");
    printf("                                                    \n");
    printf("   <output>  : specify data output                  \n");
    printf("       stdout     : data output to stdout           \n");
    printf("       file name  : data output to a file           \n");
    printf("                                                    \n");
    printf("   <ohash>  : output hash as one fole               \n");
    printf("       file name  : hash data output to a file      \n");
    printf("       only valid if opcode is -a, -ap or -aps      \n");
    printf("                                                    \n");
    printf("   <ofmt> : output format                           \n");
    printf("       bin    : binary (for file mode only)         \n");
    printf("       ascii  : ascii                               \n");
    printf("                                                    \n");
    printf("   <separator> : character(s) that used to divide two hash value (for ascii ofmt only) \n");
    printf("                                                    \n");
    printf("   <block_size>  : number of bytes data for one hash\n");
    printf("                                                    \n");
    printf("   <-v>  : vebose mode                              \n");
    printf("                                                    \n");
    printf("   <-p>  : show progress                            \n");
    printf("                                                    \n");
    printf("   <-B>  : hash for each block                      \n");
    printf("                                                    \n");
    printf("   <sign_algo>   : algorithm that used to sign the hash value\n");
    printf("      -rsa          : sign with ras                  \n");
    printf("      -aes_128_ecb  : sign with 128bits aes in ecb mode\n");
    printf("      -aes_128_cbc  : sign with 128bits aes in cbc mode\n");
    printf("                                                     \n");
    printf("   <key>         : key that used to sign hash value  \n");
    printf("   <iv>          : initial vactor that used to sign hash value  \n");
    printf("                                                     \n");
    return 0;
}



/*------------------------------------------------------------------
 * Func : DoHashCommand
 *
 * Desc : Execute Hash Command
 *
 * Parm :
 *
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoHashCommand(HASH_CMD* cmd)
{
    const char* target_file;
    char* sign_algo_str;
    int ret = -1;

    #define HASH_OUT_TEMP    ".hash.out"
    #define SHA256_OUT_TEMP  ".sha256.out"

    switch(cmd->op_code)
    {
    case DIGEST_GENERATE_HASH_VALUE:
    case DIGEST_APPEND_HASH_VALUE:

        if (strcmp(cmd->sfile, "stdin")==0)
            DumpDataFromStdin(cmd->sfile);

        target_file = cmd->dfile;

		if( cmd->append_sha256 ) {
			sign_algo_str = cmd->sign.algo_str; // save original algo_str of struct sign
			cmd->sign.algo_str = NULL;
			cmd->dfile = SHA256_OUT_TEMP;
        	GenerateHashValue(cmd);
        	cmd->sign.algo_str = sign_algo_str; // restore original algo_str of struct sign
        	cmd->length = FILE_END; // ??
        	cmd->offset = 0;// ??
		}

        cmd->dfile = HASH_OUT_TEMP;
        GenerateHashValue(cmd);

        // output data
        switch(cmd->op_code)
        {
        case DIGEST_GENERATE_HASH_VALUE:

            if ((cmd->vmode & HASH_OUT_IN_ASCII) || strcmp(target_file, "stdout")==0)
                FileConv_BinraryToASCII(HASH_OUT_TEMP, target_file, GetSignedHashLength(cmd->algo_str, &cmd->sign), (cmd->vmode & HASH_OUT_WITH_SEPARATOR) ? &cmd->separator : NULL);
            else
                rename(HASH_OUT_TEMP, target_file);

            if (strcmp(target_file, "stdout")==0)
                DumpFileToStdout(target_file);
            break;

        case DIGEST_APPEND_HASH_VALUE:
			if (cmd->append_padding) {
				AppendPaddingDataToFile(cmd->sfile, (cmd->vmode & HASH_VERBOSE_MODE));
			}
			if (cmd->append_sha256) {
				if (AppendFileDataToFile(SHA256_OUT_TEMP, cmd->sfile)<0) {
                	printf("unable to append sha256 data to '%s' -  add sha256 data to file failed\n", cmd->sfile);
                }
            	else {
                	printf("sha256 data has been append to '%s' successed\n", cmd->sfile);
                }
			}
			if (cmd->output_hash) {
				WriteFileDataToFile(HASH_OUT_TEMP, cmd->dhashfile);
			}

            if (AppendFileDataToFile(HASH_OUT_TEMP, cmd->sfile)<0) {
                printf("unable to append hash value to '%s' -  add hash value to file failed\n", cmd->sfile);
            }
            else {
                printf("hash value has been append to '%s' successed\n", cmd->sfile);
            }
            break;
        }
        break;

    case DIGEST_CHECK_HASH_VALUE:
    case DIGEST_STRIP_HASH_VALUE:

        ret = CheckHashValue(cmd);

        if (ret<0)
        {
            printf("\nhash value of '%s' is wrong\n", cmd->sfile);
            printf("\nthis file might damaged or no hash vaule exists\n");
        }
        else
        {
            printf("\nhash value of '%s' is correct\n", cmd->sfile);

            if (cmd->op_code==DIGEST_STRIP_HASH_VALUE)
            {
                if (StripDataFromFile(cmd->sfile, ret)<0)
                    printf("\nstrip hash value of '%s' failed - remove hash value failed\n", cmd->sfile);
                else
                    printf("\nhash value of '%s' has been removed\n", cmd->sfile);
            }
        }
        break;

    case DIGEST_HELP:
        DoDigestHelp();
    }

    return ret;
}



/*******************************************************************************
 * FUNC : main
 * DESC : main test function
 * PARM : NA
 * RET  : NA
 *******************************************************************************/
int main(int argc, char *argv[])
{
    CMD_STR cmd;

    if (ParseCommand(argc, argv, &cmd) <0)
        return -1;

    DoCommand(&cmd);

    return 0;
}
