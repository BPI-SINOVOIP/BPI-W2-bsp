/*
 * Copyright (c) 2010, Oracle America, Inc.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name of the "Oracle America, Inc." nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* fixincludes should not add extern "C" to this file */
/*
 * Rpc additions to <sys/types.h>
 */
#ifndef _RPC_TYPES_H
#define _RPC_TYPES_H 1

typedef int bool_t;
typedef int enum_t;
/* This needs to be changed to uint32_t in the future */
typedef unsigned long rpcprog_t;
typedef unsigned long rpcvers_t;
typedef unsigned long rpcproc_t;
typedef unsigned long rpcprot_t;
typedef unsigned long rpcport_t;

#define        __dontcare__    -1

#ifndef FALSE
#      define  FALSE   (0)
#endif

#ifndef TRUE
#      define  TRUE    (1)
#endif

#ifndef NULL
#      define  NULL 0
#endif

#include <stdlib.h>		/* For malloc decl.  */
#define mem_alloc(bsize)	malloc(bsize)
/*
 * XXX: This must not use the second argument, or code in xdr_array.c needs
 * to be modified.
 */
#define mem_free(ptr, bsize)	free(ptr)

#ifndef makedev /* ie, we haven't already included it */
#include <sys/types.h>
#endif

#if defined __APPLE_CC__ || defined __FreeBSD__
# define __u_char_defined
# define __daddr_t_defined
#endif

#ifndef __u_char_defined
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
#if __WORDSIZE == 64
typedef long int quad_t;
typedef unsigned long int u_quad_t;
#elif defined __GLIBC_HAVE_LONG_LONG
typedef long long int quad_t;
typedef unsigned long long int u_quad_t;
#endif
typedef u_quad_t fsid_t;
# define __u_char_defined
#endif
#if !defined(__daddr_t_defined) && defined(linux)
typedef long int daddr_t;
typedef char *caddr_t;
# define __daddr_t_defined
#endif

#include <sys/time.h>
#include <sys/param.h>

#include <netinet/in.h>

#ifndef INADDR_LOOPBACK
#define       INADDR_LOOPBACK         (u_long)0x7F000001
#endif
#ifndef MAXHOSTNAMELEN
#define        MAXHOSTNAMELEN  64
#endif

#endif /* rpc/types.h */
