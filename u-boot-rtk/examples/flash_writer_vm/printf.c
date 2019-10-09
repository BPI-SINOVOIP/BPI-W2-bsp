#include <stdarg.h>
#include "TinyStdio/tinystdio.h"
#include "dvrboot_inc/ctype.h"
#include "sysdefs.h"
#include "uart.h"

#if 0
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)   __builtin_va_end(v)
#endif

int __printf(const char* fmt,  ...)
{
    int ret;
    char buffer[100];
    va_list args;

    va_start (args, fmt);    
    ret = tfp_vsprintf(buffer, fmt, args);
    prints(buffer);
    va_end (args);

    return ret;
}

