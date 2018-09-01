/* Initialization in nss_files module.
   Copyright (C) 2011-2014 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef USE_NSCD

#include <string.h>
#include <nscd/nscd.h>


#define TF(id, filename, ...)					\
static union							\
{								\
  struct traced_file file;					\
  char buf[sizeof (struct traced_file) + sizeof (filename)];	\
} id##_traced_file =						\
  {								\
    .file =							\
    {								\
      __VA_ARGS__						\
    }								\
  }

TF (pwd, "/etc/passwd");
TF (grp, "/etc/group");
TF (hst, "/etc/hosts");
TF (resolv, "/etc/resolv.conf", .call_res_init = 1);
TF (serv, "/etc/services");
TF (netgr, "/etc/netgroup");


void
_nss_files_init (void (*cb) (size_t, struct traced_file *))
{
  strcpy (pwd_traced_file.file.fname, "/etc/passwd");
  cb (pwddb, &pwd_traced_file.file);

  strcpy (grp_traced_file.file.fname, "/etc/group");
  cb (grpdb, &grp_traced_file.file);

  strcpy (hst_traced_file.file.fname, "/etc/hosts");
  cb (hstdb, &hst_traced_file.file);

  strcpy (resolv_traced_file.file.fname, "/etc/resolv.conf");
  cb (hstdb, &resolv_traced_file.file);

  strcpy (serv_traced_file.file.fname, "/etc/services");
  cb (servdb, &serv_traced_file.file);

  strcpy (netgr_traced_file.file.fname, "/etc/netgroup");
  cb (netgrdb, &netgr_traced_file.file);
}

#endif
