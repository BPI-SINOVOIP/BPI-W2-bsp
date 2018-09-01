#if WANT_OBSTACK_PRINTF
#include <obstack.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int
obstack_printf (struct obstack *obstack, const char *format, ...)
{
  va_list ap;
  char *string;
  int result;

  va_start (ap, format);
  result = vasprintf (&string, format, ap);
  obstack_grow (obstack, string, strlen (string) + 1);
  free (string);
  va_end (ap);
  return result;
}

#endif
