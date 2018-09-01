#ifdef HAVE_DIRENT_H
#include_next <dirent.h>
#endif

#ifndef HAVE_READDIR64
#define HAVE_READDIR64 1
#define readdir64(DIR) readdir (DIR)
#define dirent64 dirent
#endif

#ifndef IFTODT
#define DT_UNKNOWN 1000
#define DT_REG 1001
#define DT_DIR 1002
#define IFTODT(MODE) \
  (S_ISDIR (MODE) ? DT_DIR : S_ISREG (MODE) ? DT_REG : DT_UNKNOWN)
#endif
