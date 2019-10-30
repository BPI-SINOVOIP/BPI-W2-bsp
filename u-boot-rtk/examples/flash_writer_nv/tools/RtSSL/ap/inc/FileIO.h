#ifndef __FILE_IO_H__
#define __FILE_IO_H__



typedef enum {
    FMT_RAW_DATA,
    FMT_NAND_IMAGE    
};


typedef struct {    
    unsigned char   type;
    unsigned long   data_block_size;
    unsigned long   spare_area_size;          
}NAND_FORMAT;


typedef union 
{
    unsigned char   type;        
    NAND_FORMAT     nand;        
}FILE_FORMAT;

#define FILE_START          0
#define FILE_END            0xFFFFFFFF

int ReadDataFromFile(const char* fname, unsigned char* data, unsigned long len, unsigned long offset);

int MemoryToFile(const char* fname, unsigned char* data, unsigned long len);

int DumpDataToStdout(const char* fname);

int DumpFileToStdout(const char* fname);

int DumpDataFromStdin(const char* fname);

int GetFileLength(const char* fname);

int WriteDataToFile(const char* fname, unsigned char* data, unsigned int len);

int WriteFileDataToFile(const char* src_file, const char* target_file);

int AppendDataToFile(const char* fname, unsigned char* data, unsigned int len);

int AppendFileDataToFile(const char* src_file, const char* target_file);

int AppendPaddingDataToFile(const char* target_file, unsigned char verbose);

int StripDataFromFile(const char* fname, unsigned int len);

int FileCut(const char* fin, const char* fout, unsigned long start, unsigned long end);

int FileCompare(const char* fin1, const char* fin2);

int ParseFileFmt(const char* fmt_str, FILE_FORMAT* fmt);

// for NAND file

int StripNandImgae(const char* fin, const char* fout, NAND_FORMAT* fmt);

// convert from binary to ascii

int FileConv_BinraryToASCII(
    const char*             fin, 
    const char*             fout, 
    unsigned long           block_size,
    char*                   block_separator
    );

/////////////////////// SHELL /////////////////////
typedef enum {
    FILE_CMD_CONVERT,    
    FILE_CMD_CUT,  
    FILE_CMD_CMP,  
    FILE_CMD_HELP,    
}FILE_OPERATION;

typedef enum {
    CNV_FMT_ASCII_TO_BINRARY,
    CNV_FMT_BINRARY_TO_ASCII,
}CNV_FMT;

typedef struct {
    unsigned char       op_code;        
    unsigned char       fmt;
    unsigned long       start;
    unsigned long       end;
    char*               sfile;          // input file
    char*               sfile1;         // input file
    char*               dfile;          // output file                           
}FILE_CMD;


extern int DoFileCommand(FILE_CMD* cmd);
extern int ParseFileCommand(int argc, char *argv[], FILE_CMD* cmd);

    
#endif //__FILE_IO_H__
