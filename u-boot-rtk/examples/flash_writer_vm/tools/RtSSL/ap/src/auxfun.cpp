#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h> 
#include <string.h> 
#include <ctype.h> 
#include "auxfun.h"
 
#ifdef CYGWIN
#include <asm/socket.h>
#endif

/**
 Linux (POSIX) implementation of _kbhit().
 Morgan McGuire, morgan@cs.brown.edu
 */
int _kbhit() 
{    
    int bytesWaiting;
     
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term);
    setbuf(stdin, NULL);                // flush stin buffer
    ioctl(0, FIONREAD, &bytesWaiting);  // read how much data in the buffer
    term.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &term);       
            
    return bytesWaiting;
}



int _str_to_long(char *str, long* p_val, unsigned char base)
{
    char*     p;
    long int  val;   
    
    base = (base == 8 || base == 10 || base == 16 || base == 32) ? base : 0;
    val = strtol(str,&p,base);
            
    if (*p=='\0') {                        
        *p_val = val;
        return 0;               
    }   
         
    return -1;                
}


int _str_to_long_with_range(char *str, long* p_val, unsigned char base, unsigned long min, unsigned long max)
{
    if (_str_to_long(str, p_val, base)<0)            
        return  -1;
    
    return (*p_val >= min && *p_val <= max) ? 0 : -1;            
}


int _get_bytes_with_text(const char* title, unsigned char* pBuff, unsigned char Len)
{
    printf("%s\n",title);
    return _get_bytes(pBuff, Len);
}



/*******************************************************************************
 * FUNC : _str_to_bytes
 * DESC : convert string to byte array.
 * PARM : 
 * RET  : number of bytes readed
 *******************************************************************************/
int _str_to_bytes(const char* str, unsigned char* pBuff, unsigned int Len)
{    
    char*           ptr = (char*) str;    
    unsigned long   len;    
    unsigned long   nBytes;    
                        
    len = strlen(str);
    
    // get number of bytes
    nBytes = (len +1) >>1;       
    
    if (nBytes > Len) 
    {
        printf("convert str to bytes failed - no enough memory (nBytes =%d, BuffLen = %d)\n",nBytes, Len);
        return -1;
    }                
    
    for (int i=0; i<nBytes; i++)
    {        
        char     tmp[3] = {0,0,0};            
        char*    p;
        long int val;  
        
        if (i==0 && (len & 0x01))
        {            
            tmp[0]= '0';
            tmp[1]= *ptr++;                    
        }
        else
        {
            tmp[0]= *ptr++;
            tmp[1]= *ptr++;                    
        }            
        
        if ((val=strtol(tmp,&p,16))<0)
        {
            printf("convert str to bytes failed - '%s' is not in hex format\n", str);
            return -1;
        }
        
        pBuff[i] = (unsigned char) val;             
    }                
    
    //dump_mem(pBuff, nBytes);    

    return nBytes;
}




/*******************************************************************************
 * FUNC : _get_bytes
 * DESC : get number of bytes.
 * PARM : 
 * RET  : number of bytes readed
 *******************************************************************************/
int _get_bytes(unsigned char* pBuff, unsigned char Len)
{    
#if 1            
    char buff[256];    
    int  len;
    if (fgets_ex(buff, sizeof(buff))<0)
        return -1;    
            
    return _str_to_bytes(buff, pBuff, Len);        
    
#else    
    char            buff[256] = {'0'};    
    char*           ptr;    
    unsigned long   len;    
    unsigned long   nBytes;    
            
    if (fgets_ex(buff+1, sizeof(buff)-1)<0)
        return -1;
        
    len = strlen(buff) -1;
    
    // get number of bytes
    nBytes = (len +1) >>1;       
    
    if (nBytes > Len) 
    {
        printf("_get_bytes function failed, no enough memory (nBytes =%d, BuffLen = %d)\n",nBytes, Len);
        return -1;
    }
    
    ptr = (len & 0x01) ? buff : buff+1;     
    
    for (int i=0; i<nBytes; i++)
    {        
        char     str[3] = {0,0,0};            
        char*    p;
        long int val;  
        
        str[0]= *ptr++;
        str[1]= *ptr++;        
        
        if ((val=strtol(str,&p,16))<0)
        {
            printf("input - '%s' is not hex format\n", buff);
            return -1;
        }
        
        pBuff[i] = (unsigned char) val;             
    }    
        
    dump_mem(pBuff, nBytes);
                
    return nBytes;
#endif    
}


/*******************************************************************************
 * FUNC : fgets_ex
 * DESC : this function was used to get data from stdin
 *        to get the correct input data, we must guarantee
 *        that the input buffer was empty before user input 
 * PARM : 
 * RET  : FUNCTION_SUCCESS / FUNCTION_ERROR
 *******************************************************************************/
int fgets_ex(char* buf, int len)
{                
    int remain = _kbhit();  // unwanted data in the buffer before keyin
    int str_len;    
    char tmp[256];    
    
    while(1)
    {                 
        memset (tmp,0,sizeof(tmp));
        
        //printf("remain=%d \n",remain);
        if (fgets(tmp, 255, stdin)==NULL){
            //printf("fgets=-1\n");
            return -1;          
        }
        
        //printf("got string =%s \n",tmp);
            
        str_len = strlen(tmp);                                                           
                        
        if (str_len > remain) {
                        
            str_len -= remain;  // actual length whout remain data
            
            if (str_len >= (len-1)) {
                printf("string length more than input buffer %d\n",len);
                return -1;
            }
                
            //memcpy(buf, &tmp[remain], str_len);
            strncpy(buf, &tmp[remain], len);                 
            str_len = strlen(buf);               
            //dump_mem((unsigned char*)buf, str_len);        
            if (buf[str_len-1]=='\n')
                buf[str_len-1] = 0;
                                    
            //printf("got string =%s \n",buf);
            return 0;
        }
        else {                       
            //printf("str_len=%d \n",str_len);                   
            remain -= str_len;   // drop all data
            continue;
        }
    }
}


/*******************************************************************************
 * FUNC : get_yes_no
 * DESC : get yes or no
 * PARM : 
 * RET  : 0 / -1
 *******************************************************************************/ 
int _get_yes_no()
{        
    char     buf[20];
    char*    p;
    long int val;
            
    while(1)
    {   
        fflush(stdin);        
        usleep(10); 
                                           
        if (fgets_ex(buf,sizeof(buf))==0)
        {                                            
            if (sscanf(buf,"%s",buf)!=EOF)  // get string from buffer (Add \0 add end of string)
            {                
                if (strcmp(buf ,"y")==0)
                    return 1;                
                else if (strcmp(buf ,"n")==0)
                    return 0;                               
                else
                    printf("\nUnknown Input > %s\n", buf);                                                      
            }
        }
    }        
}



/*******************************************************************************
 * FUNC : get_number
 * DESC : get number 
 * PARM : pval : user specified value output
 * RET  : 0 / -1
 *******************************************************************************/ 
int _get_number(long int* pval)
{        
    char     buf[20];
    char*    p;
    long int val;
            
    while(1)
    {   
        fflush(stdin);        
        usleep(10); 
                                           
        if (fgets_ex(buf,sizeof(buf))==0)
        {                                            
            if (sscanf(buf,"%s",buf)!=EOF)  // get string from buffer (Add \0 add end of string)
            {                
                if (_str_to_long(buf ,&val, 10)==0) {
                    *pval = val;
                    return 0;
                }                    
                else {
                    printf("\nUnknown Input > %s", buf);                  
                    return -1;                                        
                }
            }
        }
    }        
}



/*******************************************************************************
 * FUNC : show_menu
 * DESC : show menu
 * PARM : p_menu : menu to display
 * RET  : 0 / -1
 *******************************************************************************/ 
void show_menu(const char* title, menu_item* p_items, unsigned long n_item)
{
    long int i;
    
    while(1)
    {
        fflush(stdin);
        
        printf("\n\n");
        printf(" _________________________\n");
        printf("| %s  |\n", title);
        printf(" -------------------------\n");
        printf("\n");
        
        for(i=0; i<n_item; i++)
        {
            printf("%2d) %s\n", i+1, p_items[i].item_desc);                
        }
        
        printf(" 0) Exit\n"); 
        printf("\n");
        printf("Press 0 to eixt \n");
        printf("\n");
                
        i = 0xFF; 
                       
        if(_get_number(&i)==0)
        {                
            if (i==0)
            {
                printf("\n");                
                return;
            }
            else if (i>0 && i<= n_item+1)
            {
                p_items[i-1].test_func();
            }                        
        }                
    };
}




/*******************************************************************************
 * FUNC : show_list
 * DESC : show menu
 * PARM : p_list : list to display
 * RET  : 0 / -1
 *******************************************************************************/ 
unsigned long show_list(const char* title, list_item* p_items, unsigned long n_item)
{
    long int i;
    
    while(1)
    {
        fflush(stdin);
        
        printf("\n\n");
        printf(" _________________________\n");
        printf("| %s  |\n", title);
        printf(" -------------------------\n");
        printf("\n");
        
        for(i=0; i < n_item; i++)
        {
            printf("%2d) %s\n", i, p_items[i].item_desc);
        }
                        
        printf("\n");
                
        i = 0xFF; 
                       
        if(_get_number(&i)==0)
        {                
            if (i< n_item)
            {
                printf("\n");
                return p_items[i].val;
            }    
            else
            {
                printf("invalid input %d\n", i);
            }                    
        }                
    };
}



void dump_mem(unsigned char* pData, unsigned short Len)
{
    printf("------------------------------------------------------------\n");
    printf("ADDRESS   00 01 02 03 04 05 06 07   08 09 0A 0B 0C 0D 0E 0F \n");
    printf("------------------------------------------------------------\n");    
    for (int i=0; i<Len; i+=16)
    {                       
        printf("%08x  ", i);                          
                    
        for (int j=0; j<16; j++)    
        {
            int c = i+j;
            if (c<Len)
                printf("%02x ", pData[c]);                        
            else
                printf("-- ");            
                            
            if ((c & 0x07)==0x07)
                printf("  ");            
        }
        
        printf(" ");
        
        for (int j=0; j<16; j++)    
        {   
            int c = i+j;                    
            if (c<Len && isprint(pData[c]))                         
                printf("%c", (char) pData[c]);
            else                               
                printf(".");
        }
        
        printf("\n");               
    }
    printf("------------------------------------------------------------\n");
}


void dump_mem_with_text(const char* str, unsigned char* pData, unsigned short Len)
{
    printf(">>>>>>>>>>>> %s <<<<<<<<<<<<<\n", str);
    dump_mem(pData, Len);
}


void dump_hex(unsigned char* pData, unsigned short Len)
{    
    for (int i=0; i<Len; i++)                                   
        printf("%02x", pData[i]);                                    
    printf("\n");                                            
}


int get_file_size(const char* fname)
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
