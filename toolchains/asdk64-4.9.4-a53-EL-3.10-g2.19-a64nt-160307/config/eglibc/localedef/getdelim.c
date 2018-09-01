#if WANT_GETDELIM
#include <stdio.h>
#include <stdlib.h>

ssize_t
getdelim (char **lineptr, size_t *n, int delimiter, FILE *file)
{
  size_t count;
  int ch;

  if (*lineptr == NULL || *n == 0)
    {
      *n = 100;
      *lineptr = malloc (*n);
      if (*lineptr == NULL)
	return -1;
    }

  count = 0;
  while ((ch = fgetc (file)) != EOF)
    {
      if (*n <= count + 1)
	{
	  *n *= 2;
	  *lineptr = realloc (*lineptr, *n);
	  if (*lineptr == NULL)
	    return -1;
	}
      (*lineptr)[count++] = ch;
      if (ch == delimiter)
	{
	  (*lineptr)[count] = 0;
	  return count;
	}
    }
  return -1;
}

#endif
