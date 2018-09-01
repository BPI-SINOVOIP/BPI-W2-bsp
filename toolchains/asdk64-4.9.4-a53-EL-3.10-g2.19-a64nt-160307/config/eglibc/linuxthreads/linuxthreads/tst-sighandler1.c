/* Copyright (C) 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <limits.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *
tf (void *arg)
{
  int fd = (long) arg;
  int pid = getpid ();
#ifdef TIMED
  struct timespec ts;
#endif

  if (pthread_mutex_lock (&mutex) != 0)
    {
      puts ("Could not lock mutex in thread");
      return (void *) 1L;
    }

  write (fd, &pid, sizeof (int));

  if (pthread_mutex_unlock (&mutex2) != 0)
    {
      puts ("Could not unlock mutex2 in thread");
      return (void *) 1L;
    }

#ifdef TIMED
  ts.tv_sec = INT_MAX;
  ts.tv_nsec = 0;
  if (pthread_cond_timedwait (&cond, &mutex, &ts) != 0)
    {
      puts ("pthread_cond_wait failed in thread");
      return (void *) 1L;
    }
#else
  if (pthread_cond_wait (&cond, &mutex) != 0)
    {
      puts ("pthread_cond_wait failed in thread");
      return (void *) 1L;
    }
#endif

  if (pthread_mutex_unlock (&mutex) != 0)
    {
      puts ("Could not unlock mutex in thread");
      return (void *) 1L;
    }

  return NULL;
}

static void
sig_segv (int unused)
{
  exit (2);
}

int
do_test (void)
{
  int fds[2];
  pthread_t thr;

  if (pipe (fds) < 0)
    {
      printf ("couldn't create pipe: %m\n");
      return 1;
    }

  pid_t pid = fork ();
  if (pid < 0)
    {
      printf ("fork failed: %m\n");
      return 1;
    }

  if (!pid)
    {
      void *ret;

      close (fds[0]);
      signal (SIGSEGV, sig_segv);
      pthread_mutex_lock (&mutex2);
      pthread_create (&thr, NULL, tf, (void *) (long) (fds[1]));
      /* Wait for the thread to go into cond_wait.  */
      pthread_mutex_lock (&mutex2);
      pthread_mutex_lock (&mutex);
      write (fds[1], "", 1);
      pthread_join (thr, &ret);
      exit (0);
    }

  close (fds[1]);

  int child_pid;
  if (TEMP_FAILURE_RETRY (read (fds[0], &child_pid, sizeof (int)))
      != sizeof (int))
    {
      puts ("could not read pid from child");
      return 1;
    }

  char dummy;
  if (TEMP_FAILURE_RETRY (read (fds[0], &dummy, 1)) != 1)
    {
      puts ("could not read sync byte from child");
      return 1;
    }

  close (fds[0]);

  /* The sync byte may come immediately after the mutex is released;
     wait a little bit more to make sure the thread has suspended, to
     test the right bug.  */
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 200000000;
  nanosleep (&ts, NULL);

  kill (child_pid, SIGSEGV);

  pid_t termpid;
  int status;
  termpid = TEMP_FAILURE_RETRY (waitpid (pid, &status, 0));
  if (termpid == -1)
    {
      printf ("waitpid failed: %m\n");
      return 1;
    }
  else if (termpid != pid)
    {
      printf ("waitpid returned %ld != %ld\n",
	      (long int) termpid, (long int) pid);
      return 1;
    }
  else if (!WIFEXITED (status) || WEXITSTATUS (status) != 2)
    {
      puts ("child hasn't exited with exit status 2");
      return 1;
    }

  return 0;
}

#define TEST_FUNCTION do_test ()
#include "../test-skeleton.c"
