#ifdef HAVE_SYS_MMAN_H
#include_next <sys/mman.h>
#endif

#ifndef HAVE_MMAP64
#define HAVE_MMAP64 1
#define mmap64(START, LENGTH, PROT, FLAGS, FD, OFFSET) \
  mmap (START, LENGTH, PROT, FLAGS, FD, OFFSET)
#endif
