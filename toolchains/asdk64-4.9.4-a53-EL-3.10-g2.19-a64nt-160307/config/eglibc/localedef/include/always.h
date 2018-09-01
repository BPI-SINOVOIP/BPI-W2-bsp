#include "config.h"
#include <features.h>
#define internal_function
#define attribute_hidden
#define __md5_process_bytes md5_process_bytes
#define __md5_process_block md5_process_block
#define __md5_buffer md5_buffer
#define weak_alias(A, B)
#define alloca(SIZE) __builtin_alloca (SIZE)

#ifndef HAVE_OBSTACK_PRINTF
#define HAVE_OBSTACK_PRINTF 1
#define WANT_OBSTACK_PRINTF 1
struct obstack;
extern int obstack_printf (struct obstack *, const char *, ...);
#endif

#ifndef HAVE_GETDELIM
#define HAVE_GETDELIM 1
#define WANT_GETDELIM 1
#include <stdio.h>
#include <sys/types.h>
ssize_t getdelim (char **, size_t *, int, FILE *);
#endif

#ifndef HAVE_ASPRINTF
#define HAVE_ASPRINTF 1
#define WANT_ASPRINTF 1
extern int asprintf (char **, const char *, ...);
#endif

#ifndef HAVE_VASPRINTF
#define HAVE_VASPRINTF 1
#define WANT_VASPRINTF 1
#include <stdarg.h>
int vasprintf (char **, const char *, va_list);
#endif

#ifndef HAVE_PROGRAM_INVOCATION_NAME
#define HAVE_PROGRAM_INVOCATION_NAME 1
extern const char *program_invocation_name;
#endif
/* For argp-help.c.  */
#define HAVE_DECL_PROGRAM_INVOCATION_NAME 1

#ifndef HAVE_PROGRAM_INVOCATION_SHORT_NAME
#define HAVE_PROGRAM_INVOCATION_SHORT_NAME 1
extern const char *program_invocation_short_name;
#endif
/* For argp-help.c.  */
#define HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME 1

#ifndef HAVE___COMPAR_FN_T
#define HAVE___COMPAR_FN_T 1
typedef int (*__compar_fn_t) (const void *, const void *);
#endif

#ifndef HAVE_COMPARISON_FN_T
#define HAVE_COMPARISON_FN_T 1
#include <stdlib.h>
typedef __compar_fn_t comparison_fn_t;
#endif

/* If euidaccess() isn't provided, just check whether the file exists.  */
#ifndef HAVE_EUIDACCESS
#define HAVE_EUIDACCESS 1
#include <sys/types.h>
#include <sys/stat.h>
static inline int
euidaccess (const char *filename, int mode)
{
  struct stat st;
  return stat (filename, &st);
}
#endif

#ifndef HAVE_OFF64_T
#define HAVE_OFF64_T 1
typedef long long off64_t;
#endif

#ifndef HAVE_BLKSIZE_T
#define HAVE_BLKSIZE_T 1
typedef long blksize_t;
#endif

#ifndef HAVE_INT_FAST32_T
#define HAVE_INT_FAST32_T 1
typedef int int_fast32_t;
#endif

#ifndef HAVE_MEMPCPY
#define HAVE_MEMPCPY 1
#include <string.h>
static inline void *
mempcpy (void *dest, const void *src, size_t n)
{
  return (char *) memcpy (dest, src, n) + n;
}
#endif

#ifndef HAVE_STRCHRNUL
#define HAVE_STRCHRNUL 1
static inline char *
strchrnul (const char *s, int ch)
{
  while (*s != 0 && *s != ch)
    s++;
  return (char *) s;
}
#define __strchrnul strchrnul
#endif

#ifndef HAVE_STRNDUP
#define HAVE_STRNDUP 1
#include <string.h>
#include <stdlib.h>
static inline char *
strndup (const char *s, size_t n)
{
  size_t len;
  char *result;

  len = strlen (s);
  n = len > n ? n : len;
  result = malloc (n + 1);
  if (result)
    {
      memcpy (result, s, n);
      result[n] = 0;
    }
  return result;
}
#endif

#ifndef HAVE_STPCPY
#define HAVE_STPCPY 1
#include <string.h>
static inline char *
stpcpy (char *dest, const char *src)
{
  return strcpy (dest, src) + strlen (src);
}
#endif

#ifndef HAVE_STRSEP
#define HAVE_STRSEP 1
#include <string.h>
static inline char *
strsep (char **stringp, const char *delim)
{
  char *start, *end;

  start = *stringp;
  end = *stringp;
  while (end != 0 && strchr (delim, *end) == 0)
    if (*end++ == 0)
      end = 0;
  if (end)
    *end++ = 0;
  *stringp = end;
  return start;
}
#endif

/* Disable file locking unless all the features that glibc needs
   are available.  */
#ifndef _GNU_SOURCE
#include <stdio_ext.h>
#include <sys/file.h>
#include <unistd.h>
#undef lockf
#define lockf(FD, CMD, OFF) 0
#undef lockf64
#define lockf64(FD, CMD, OFF) 0
#undef __fsetlocking
#define __fsetlocking(FILE, TYPE) (void) 0
#undef putc_unlocked
#define putc_unlocked(CH, FILE) putc (CH, FILE)
#undef putchar_unlocked
#define putchar_unlocked(CH) putchar (CH)
#undef putwc_unlocked
#define putwc_unlocked(CH, FILE) putwc (CH, FILE)
#undef feof_unlocked
#define feof_unlocked(FILE) feof (FILE)
#undef fgets_unlocked
#define fgets_unlocked(BUF, LEN, FILE) fgets (BUF, LEN, FILE)
#undef fputs_unlocked
#define fputs_unlocked(STR, FILE) fputs (STR, FILE)
#undef fwrite_unlocked
#define fwrite_unlocked(BUF, SIZE, NELEM, FILE) fwrite (BUF, SIZE, NELEM, FILE)
#endif

#include <stdbool.h>
#include <stdint.h>
