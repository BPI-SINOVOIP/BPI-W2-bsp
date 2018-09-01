/* If OPTION_EGLIBC_NIS is disabled, nscd can't get this from libnsl.so;
   we need our own copy.  */
#include "../nis/nis_hash.c"
