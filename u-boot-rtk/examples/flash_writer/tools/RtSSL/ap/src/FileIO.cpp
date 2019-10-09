#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include "auxfun.h" 
#include "FileIO.h" 





/*------------------------------------------------------------------
 * Func : AppendDataToFile
 *
 * Desc : Append Data to the end of file
 *
 * Parm : file : file name
 *        data : data to append
 *        len  : length of data
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int GetFileLength(const char* fname)
{    
    FILE* fd = fopen(fname, "rb");
    int  len = -1;    
    
    if (fd)
    {        
        fseek(fd, 0, SEEK_END);            
        len = ftell(fd);        
        fclose(fd);        
    }   
    return len;
}

/*------------------------------------------------------------------
 * Func : WriteDataToFile
 *
 * Desc : Write Data to a file
 *
 * Parm : file : file name
 *        data : data to append
 *        len  : length of data
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int WriteDataToFile(
    const char*             file, 
    unsigned char*          data,
    unsigned int            len
    )
{    
    FILE* fd = fopen(file, "w+");
    int   ret = -1;                
    
    if (fd)            
    {
        ret = fwrite(data, 1, len ,fd); 
        fclose(fd);
        return ret;
    }        
    
    return -1;                
}



/*------------------------------------------------------------------
 * Func : WriteFileDataToFile
 *
 * Desc : Write Data form a file
 *
 * Parm : src_file : file name
 *        target_file : target file
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int WriteFileDataToFile(
    const char*             src_file, 
    const char*             target_file    
    )
{    
    FILE* fd1 = fopen(src_file, "rb");
    FILE* fd2 = fopen(target_file, "w+");
    int   ret = -1;
    unsigned char buff[512];
    unsigned long length;
    
    if (fd1 && fd2)            
    {
        while((ret = fread(buff, 1, 512, fd1))>0)                                
            fwrite(buff, 1,ret, fd2);    // write data to file... 
                    
        ret = 0;
    }        
    
    if (fd1)
        fclose(fd1);
        
    if (fd2)
        fclose(fd2);
                
    return ret;                
}


/*------------------------------------------------------------------
 * Func : AppendDataToFile
 *
 * Desc : Append Data to the end of file
 *
 * Parm : file : file name
 *        data : data to append
 *        len  : length of data
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int AppendDataToFile(
    const char*             file, 
    unsigned char*          data,
    unsigned int            len
    )
{    
    FILE* fd = fopen(file, "r+b");
    int   ret = -1;                
    
    if (fd)            
    {
        fseek(fd, 0, SEEK_END);    
        ret = fwrite(data, 1, len ,fd); 
        fclose(fd);
        return ret;
    }        
    
    return -1;                
}



/*------------------------------------------------------------------
 * Func : AppendFileDataToFile
 *
 * Desc : Append Data form a file to the end of another file
 *
 * Parm : src_file : file name
 *        target_file : target file
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int AppendFileDataToFile(
    const char*             src_file, 
    const char*             target_file    
    )
{    
    FILE* fd1 = fopen(src_file, "rb");
    FILE* fd2 = fopen(target_file, "r+b");
    int   ret = -1;
    unsigned char buff[512];
    unsigned long length;
    
    if (fd1 && fd2)            
    {
        fseek(fd2, 0, SEEK_END);
               
        while((ret = fread(buff, 1, 512, fd1))>0)                                
            fwrite(buff, 1,ret, fd2);    // write data to file... 
                    
        ret = 0;
    }        
    
    if (fd1)
        fclose(fd1);
        
    if (fd2)
        fclose(fd2);
                
    return ret;                
}

int AppendPaddingDataToFile(
    const char*             target_file,
    unsigned char verbose
    )
{    
    FILE* fd = fopen(target_file, "r+b");
    int   ret = -1;
    unsigned char buff[128];
    unsigned long length;
    unsigned long num_of_bits;
    unsigned int pad_len;
    int i, j, tmp;
    
    if (fd)            
    {
        fseek(fd, 0, SEEK_END);
        
        length = ftell(fd);
        
        num_of_bits = length << 3;
        
        pad_len = 1;
        while ((length + pad_len) % 64 != 56)
            pad_len++;
        pad_len += 8;

        if( verbose ) {
        	printf("*** length = %lx\n", length ); 
        	printf("*** num_of_bits = %lx\n", num_of_bits ); 
        	printf("*** pad_len = %lx\n", pad_len ); 
        }

		memset( buff, 0, sizeof(buff) );
		
		buff[0] = 0x80;
		for (i = pad_len - 8, j = 32; j >= 0; j -= 32) {
			tmp = (int) ((long long)num_of_bits >> j);
			buff[i++] = (tmp >> 24) & 0xff;
			buff[i++] = (tmp >> 16) & 0xff;
			buff[i++] = (tmp >> 8) & 0xff;
			buff[i++] =  tmp & 0xff;
		}
		
		fwrite(buff, 1, pad_len, fd);    // write data to file... 
               
        ret = 0;
    }        
    
    if (fd)
        fclose(fd);
                
    return ret;                
}

/*------------------------------------------------------------------
 * Func : StripDataFromFile
 *
 * Desc : Strip Data from end of file
 *
 * Parm : file : file name 
 *        len  : length of data to strip
 *         
 * Retn : <0 : failed, others : number of stripped
 *------------------------------------------------------------------*/
int StripDataFromFile(
    const char*             fname,    
    unsigned int            len
    )
{    
    int flen = GetFileLength(fname);
    
    if (flen < len)
        return -1;
            
    truncate(fname, flen - len);    
        
    return len;                
}




/*******************************************************************************
 * FUNC : DumpDataToStdout
 * DESC : Dump Data to stdout
 * PARM : NA
 * RET  : NA
 *******************************************************************************/ 
int DumpDataToStdout(const char* log_file)
{
    unsigned char buff[1024];    
    FILE*         fd = fopen(log_file,"rb");
    int           len;    
    int           ret = -1;
    if (fd)
    {
        while(!feof(fd))
        {
            len = fread(buff, 1, 1024, fd);

            for (int i=0; i<len; i++)            
            {
                printf("%02x", buff[i]);
            }            
        }
        printf("\n");
        fclose(fd);   
        ret = 0;     
    }
    return ret;        
}



/*******************************************************************************
 * FUNC : DumpFileToStdout
 * DESC : Dump File to stdout
 * PARM : NA
 * RET  : NA
 *******************************************************************************/ 
int DumpFileToStdout(const char* log_file)
{
    unsigned char buff[1024];    
    FILE*         fd = fopen(log_file,"r");
    int           len;    
    int           ret = -1;
    if (fd)
    {
        while(!feof(fd))
        {
            len = fread(buff, 1, 1023, fd);
            
            if (len>0)
            {
                buff[len]=0;
                printf("%s", buff);
            }            
        }
        printf("\n");
        fclose(fd);   
        ret = 0;     
    }
    return ret;        
}


/*******************************************************************************
 * FUNC : DumpDataFromStdin
 * DESC : Dump Data from stdin
 * PARM : NA
 * RET  : NA
 *******************************************************************************/ 
int DumpDataFromStdin(const char* log_file)
{
    unsigned char buff[1024];
    unsigned char bin_buff[512];    
    FILE*         fd = fopen(log_file,"wb");
    int           len;    
    int           ret = -1;
    if (fd)
    {
        while(!feof(stdin))
        {
            len = fread(buff, 1, 1024, stdin);
            
            if (len<0)
                continue;

            if (buff[len-1]==10)
                buff[len-1]=0;                                        
                                           
            len = _str_to_bytes((const char*) buff, bin_buff, 512);
                            
            fwrite(bin_buff, 1, len, fd);
        }
        fclose(fd);   
        ret = 0;     
    }
    return ret;        
}



/*------------------------------------------------------------------
 * Func : ReadDataFromFile
 *
 * Desc : Read Data from a file
 *
 * Parm : file  : file name 
 *        data  : read data buffer
 *        len   : size of data to read
 *        offset: offset 
 *         
 * Retn : <0 : failed, others : number of byte read
 *------------------------------------------------------------------*/
int ReadDataFromFile(const char* fname, unsigned char* data, unsigned long len, unsigned long offset)
{
    FILE* fd = fopen(fname,  "rb");
    int ret = -1;
    
    if (fd) 
    {                        
        ret = fseek(fd, offset, SEEK_SET);
        
        if (ret==0)        
            ret = fread(data, 1, len, fd);
    
        fclose(fd);
    }
    
    return  ret;         
}




/*------------------------------------------------------------------
 * Func : MemoryToFile
 *
 * Desc : Convert a block of memory to a temp file
 *
 * Parm : file  : file name 
 *        data  : read data buffer
 *        len   : size of data to read
 *         
 * Retn : <0 : failed, others : number of bytes written
 *------------------------------------------------------------------*/
int MemoryToFile(const char* fname, unsigned char* data, unsigned long len)
{
    FILE* fd = fopen(fname,  "wb");
    int ret = -1;
    
    if (fd) 
    {                                                
        ret = fwrite(data, 1, len, fd);    
        fclose(fd);
    }
    
    return  ret;         
}



int ParseFileFmt(
    const char*             fmt_str, 
    FILE_FORMAT*            fmt
    )
{    
    fmt->type = (unsigned char) FMT_RAW_DATA;
    
    if (fmt_str)
    {                    
        if (strcmp(fmt_str, "raw_data")==0)                    
            return 0;
                
        if (sscanf(fmt_str,"nand:%lu:%lu", &fmt->nand.data_block_size, &fmt->nand.spare_area_size)==2)                               
        {                
            fmt->type = (unsigned char) FMT_NAND_IMAGE;            
            return 0;            
        }
        
        return -1;
    }   
     
    return 0;    
}



//////////////////////////////////////////////////////////////////////
// for NAND file
//////////////////////////////////////////////////////////////////////



int StripNandImgae(
    const char*             fin, 
    const char*             fout, 
    NAND_FORMAT*            fmt
    )
{
    FILE* fd1 = fopen(fin,  "rb");    
    FILE* fd2 = fopen(fout, "wb");                    
    int   block_size  = fmt->data_block_size + fmt->spare_area_size;
    int   block_count = -1;
    unsigned char* p_buff = NULL;    
    
    if (fmt->type != FMT_NAND_IMAGE)
        return -1;
    
    if (!fd1 || !fd2 || !(p_buff = (unsigned char*) malloc(block_size)))                                                                  
        goto end_proc;        
                    
        
    block_count = 0;
                        
    while(!feof(fd1))
    {
        int len = fread(p_buff, 1, block_size, fd1);
        
        if (len > fmt->data_block_size)
        {
            fwrite(p_buff, 1, fmt->data_block_size, fd2);            
            block_count++;
        }                
    }
            
end_proc:
    if (fd1)    fclose(fd1);            
    if (fd2)    fclose(fd2);
    if (p_buff) free(p_buff);        
        
    if (block_count <0)
        printf("strip image file failed\n");       
         
    return (block_count * fmt->data_block_size);
}



int FileConv_ASCIIToBinrary(const char* fin, const char* fout)
{
    FILE* fd1 = fopen(fin,  "r");    
    FILE* fd2 = fopen(fout, "wb");                                
    char ascii[257];    
    unsigned char bin[128];   
    int len;
    
    if (!fd1 || !fd2)
        goto end_proc;                                        
                        
    while(!feof(fd1))
    {
        int len = fread(ascii, 1, 256, fd1);
        
        ascii[len] = 0;
        
        if (len > 0)
        {
            len = _str_to_bytes(ascii, bin, sizeof(bin));
            
            if (len > 0)            
                fwrite(bin, 1, len, fd2);                        
        }                
    }
            
end_proc:
    if (fd1)    fclose(fd1);            
    if (fd2)    fclose(fd2);    
         
    return 0;
}




int FileConv_BinraryToASCII(
    const char*             fin, 
    const char*             fout, 
    unsigned long           block_size,
    char*                   separator
    )
{
    FILE* fd1 = fopen(fin,  "rb");    
    FILE* fd2 = fopen(fout, "w");                                
    char ascii[257];    
    unsigned char bin[128];   
    int len;
    int i;
    unsigned long conv_len = 0;
    unsigned long data_len = 0;                 
    
    if (!fd1 || !fd2)
        goto end_proc;         
        
    if (block_size==0)
        block_size = 0xFFFFFFFF;                                               

    fseek(fd1, 0, SEEK_END);            
    data_len = ftell(fd1);                                                
    fseek(fd1, 0, SEEK_SET); 
                        
    while(data_len)
    {
        int len = (data_len > 128) ? 128 : data_len; 
        
        len = fread(bin, 1, len, fd1);                
        
        for (i=0; i<len; i++)
        {
            fprintf(fd2, "%02x", bin[i]);     
            conv_len++;  
            data_len--;                     
            
            if (separator && data_len && conv_len>=block_size)
            {     
                fprintf(fd2, "%c", *separator); 
                conv_len = 0;
            }
        }        
    }
   
end_proc:
    if (fd1)    fclose(fd1);            
    if (fd2)    fclose(fd2);    
         
    return 0;
}



int FileCompare(const char* fin1, const char* fin2)
{       
    unsigned char buff[2][2048];
    int data_len = GetFileLength(fin1);
    int ret = -1;
    FILE* fd1 = NULL;    
    FILE* fd2 = NULL; 
    
    if (data_len<=0 || data_len!=GetFileLength(fin2))
        goto end_proc;
    
    fd1 = fopen(fin1, "rb");    
    fd2 = fopen(fin2, "rb");    
    
    if (!fd1 || !fd2)
        goto end_proc;
                
    while(data_len)
    {                
        unsigned long len = data_len;        
        
        if (len > 2048)
            len = 2048;
                        
        if (fread(buff[0], 1, len, fd1)!=len)
        {
            printf("error: read data form %s failed\n", fin1);            
            goto end_proc;
        }       
        
        if (fread(buff[1], 1, len, fd2)!=len)
        {
            printf("error: read data form %s failed\n", fin2);            
            goto end_proc;
        }                 
        
        if (memcmp(buff[0],buff[1], len)!=0)
            goto end_proc;
            
        data_len -= len;        
    }
    
    ret = 0;
    
end_proc:
    if (fd1) fclose(fd1);            
    if (fd2) fclose(fd2);                             
    return ret;    
}
    


int FileCut(const char* fin, const char* fout, unsigned long start, unsigned long end)
{
    FILE* fd1 = fopen(fin,  "rb");    
    FILE* fd2 = fopen(fout, "wb");    
    unsigned char buff[4096];
        
    if (!fd1 || !fd2)
    {
        if (!fd1)        
            printf("error: open file - %s failed\n", fin);
        
        if (!fd2)        
            printf("error: open file - %s failed\n", fout);
                
        goto end_proc;
    }
                   
    fseek(fd1, start, SEEK_SET);  // jump to start address        

    while(end > start && !feof(fd1))
    {
        unsigned long len = end - start;
        int ret;
        
        if (len > sizeof(buff))
            len = sizeof(buff);
                        
        if ((ret = fread(buff, 1, len, fd1))<=0)
        {
            printf("error: read data form %s failed\n", fin);
            goto end_proc;
        }            
        
        fwrite(buff, 1, ret, fd2);
        start += ret;
    }

end_proc:
    if (fd1) fclose(fd1);            
    if (fd2) fclose(fd2);
         
    return 0;
}



/////////////////////// SHELL /////////////////////



/*------------------------------------------------------------------
 * Func : ParseFileCommand
 *
 * Desc : Parse File Command
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int ParseFileCommand(int argc, char *argv[], FILE_CMD* cmd)
{    
    long     val = 0;            
    int      i;
        
    cmd->op_code = FILE_CMD_HELP;        
    
    if (argc <= 2)                        
        return 0;                        
      
    if (strcmp(argv[2], "-conv")==0)              
    {                                   
        cmd->op_code = FILE_CMD_CONVERT;                         
        
        if (argc <= 3)
        {
            printf("RtSSL Error: no fmt argument specified, please use './RtSSL file -help' to get more information\n"); 
            return 0;
        }   
                     
        if (strcmp(argv[3], "-ascii_to_bin")==0)                                         
            cmd->fmt = CNV_FMT_ASCII_TO_BINRARY; 
        else if (strcmp(argv[3],"-bin_to_ascii")==0)             
            cmd->fmt = CNV_FMT_BINRARY_TO_ASCII; 
        else 
        {
            printf("RtSSL Error: invalid fmt argument -%s specified, please use './RtSSL file -help' to get more information\n", argv[3]); 
            return 0;
        }            
    }        
    else if (strcmp(argv[2],"-cut")==0)         
    {
        cmd->op_code = FILE_CMD_CUT;
        
        if (argc <= 3)
        {
            printf("RtSSL Error: no fmt argument specified, please use './RtSSL file -help' to get more information\n"); 
            return 0;
        }
                
        if (sscanf(argv[3], "%lu:%lu", &cmd->start, &cmd->end)!=2)
        {
            printf("RtSSL Error: invalid region argument -%s specified, please use './RtSSL file -help' to get more information\n", argv[3]); 
            return 0;
        }
    }           
    else if (strcmp(argv[2],"-cmp")==0)         
    {
        cmd->op_code = FILE_CMD_CMP;
        
        if (argc < 5)
        {
            printf("RtSSL Error: no enough argument specified, please use './RtSSL file -help' to get more information\n"); 
            return 0;
        }
             
        cmd->sfile = argv[3];         
        cmd->sfile1 = argv[4];   
        return 0;     
    }           
    else if (strcmp(argv[2],"-help")==0)         
    {                          
        cmd->op_code = FILE_CMD_HELP;    
    }        
    else
    {        
        printf("RtSSL Error: invalid opcode %s for File operation, please use './RtSSL file -help' to get more information\n", argv[2]); 
        return 0;
    }                    
               
    fflush(stdout); 
    for (i=3; i<argc; i++)
    {                                                        
        if (strcmp(argv[i], "-i")==0)                                         
            cmd->sfile = argv[++i];              // input file                            
        else if (strcmp(argv[i],"-o")==0)             
            cmd->dfile = argv[++i];              // destination file                    
    }       

    return 0;            
}




/*------------------------------------------------------------------
 * Func : DoFileHelp
 *
 * Desc : Do Help
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoFileHelp()
{    
    printf("                                                    \n");    
    printf(" @@@ Realtek File Tool                               \n");
    printf("                                                    \n");    
    printf(" Format : RtSSL file <opcode> <params>               \n");    
    printf("                                                    \n");        
    printf("   <opcode> : operations                            \n");
    printf("      -conv : convert file format                   \n");    
    printf("      -cut  : cut file                              \n");    
    printf("      -cmp  : compare files                         \n");    
    printf("      -help : print help message                    \n"); 
    printf("                                                    \n");        
    printf(" Convert file format :                              \n");    
    printf("                                                    \n");        
    printf("  RtSSL file -conv <fmt> -i <input> -o <output>   \n");        
    printf("                                                    \n");    
    printf("    <fmt> : convert format                          \n");     
    printf("        -ascii_to_bin : convert ascii file to binaray format \n");                    
    printf("        -bin_to_ascii : convert binrary file to acsii format \n");
    printf("                                                    \n");        
    printf(" Cut file :                                         \n");        
    printf("                                                    \n");        
    printf("  RtSSL file -cut <start>:<end> -i <input> -o <output> \n");        
    printf("                                                    \n");    
    printf("    <strat> : start address (Dec)                   \n");                 
    printf("    <end>   : end address (Dec)                     \n");         
    printf("                                                    \n");    
    printf("                                                    \n");        
    printf(" Compare Files :                                   \n");        
    printf("                                                    \n");        
    printf("  RtSSL file -cmp <file1> <file2>                   \n");        
    printf("                                                    \n");     
    return 0;
}




/*------------------------------------------------------------------
 * Func : DoFileCommand
 *
 * Desc : Execute RSA Command
 *
 * Parm : 
 *         
 * Retn : <0 : failed, 0 : success
 *------------------------------------------------------------------*/
int DoFileCommand(FILE_CMD* cmd)
{
    int  ret = 0;

    switch(cmd->op_code)
    {        
    case FILE_CMD_CONVERT:
        
        switch(cmd->fmt)
        {
        case CNV_FMT_ASCII_TO_BINRARY:
            
            return FileConv_ASCIIToBinrary(cmd->sfile, cmd->dfile);
            
        case CNV_FMT_BINRARY_TO_ASCII:                        
            
            return FileConv_BinraryToASCII(cmd->sfile, cmd->dfile, FILE_END , NULL);
            
        default:
            printf("not support yet\n");
        }
        break;        
    
    case FILE_CMD_CUT:
        
        return FileCut(cmd->sfile, cmd->dfile, cmd->start, cmd->end);
        
    case FILE_CMD_CMP:        
        
        if (FileCompare(cmd->sfile, cmd->sfile1)!=0)            
        {
            printf("file %s and %s are not equal!!\n", cmd->sfile, cmd->sfile1);   
            ret = -1;
        }                     
        else
            printf("file %s and %s are equal\n", cmd->sfile, cmd->sfile1);                        
        break;        
        
    default:                
    case FILE_CMD_HELP:
        ret = DoFileHelp();
        break;            
    }     
            
    return ret;        
}
