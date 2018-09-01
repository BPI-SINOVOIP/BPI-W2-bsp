#include <errno.h>
#include <error.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void *
dummy (void *x)
{
  return NULL;
}

static char buf[sizeof "something\n"];

static int
do_test (void)
{
  FILE *f;
  pthread_t p;
  int err;

  f = popen ("echo something", "r");
  if (f == NULL)
    error (EXIT_FAILURE, errno, "popen failed");
  if (fgets (buf, sizeof (buf), f) == NULL)
    error (EXIT_FAILURE, 0, "fgets failed");
  if (strcmp (buf, "something\n"))
    error (EXIT_FAILURE, 0, "read wrong data");
  if (pclose (f))
    error (EXIT_FAILURE, errno, "pclose returned non-zero");
  if ((err = pthread_create (&p, NULL, dummy, NULL)))
    error (EXIT_FAILURE, err, "pthread_create failed");
  if ((err = pthread_join (p, NULL)))
    error (EXIT_FAILURE, err, "pthread_join failed");
  exit (0);
}

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"
