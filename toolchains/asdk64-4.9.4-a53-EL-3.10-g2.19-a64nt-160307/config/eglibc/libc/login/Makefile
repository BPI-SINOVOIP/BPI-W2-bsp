# Copyright (C) 1996-2014 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

#
#	Sub-makefile for login portion of the library.
#
include ../option-groups.mak

subdir	:= login

headers	:= utmp.h bits/utmp.h lastlog.h pty.h

routines := getpt grantpt unlockpt ptsname ptsname_r_chk
routines-$(OPTION_EGLIBC_UTMP) \
	 += getutent getutent_r getutid getutline getutid_r getutline_r \
	    utmp_file utmpname updwtmp
routines-$(OPTION_EGLIBC_GETLOGIN) += getlogin getlogin_r getlogin_r_chk
routines-$(OPTION_EGLIBC_BSD) += setlogin

CFLAGS-grantpt.c = -DLIBEXECDIR='"$(libexecdir)"'

others-$(OPTION_EGLIBC_UTMP) += utmpdump

include ../Makeconfig

ifeq (yes,$(build-pt-chown))
others += pt_chown
others-pie = pt_chown
install-others-programs = $(inst_libexecdir)/pt_chown
endif

subdir-dirs = programs
vpath %.c programs

tests := tst-utmp tst-utmpx tst-grantpt

# Build the -lutil library with these extra functions.
extra-libs-$(OPTION_EGLIBC_UTMP) := libutil
extra-libs-others := $(extra-libs-y)

libutil-routines:= login login_tty logout logwtmp openpty forkpty

include ../Rules

CFLAGS-getpt.c = -fexceptions

ifeq (yesyes,$(have-fpie)$(build-shared))
pt_chown-cflags += $(pie-ccflag)
endif
ifeq (yes,$(have-ssp))
pt_chown-cflags += -fstack-protector
endif
ifeq (yes,$(have-libcap))
libcap = -lcap
endif
CFLAGS-pt_chown.c = $(pt_chown-cflags)
LDLIBS-pt_chown = $(libcap)
ifeq (yesyes,$(have-fpie)$(build-shared))
LDFLAGS-pt_chown = -Wl,-z,now
endif

# pt_chown needs to be setuid root.
$(inst_libexecdir)/pt_chown: $(objpfx)pt_chown $(+force)
	$(make-target-directory)
	-$(INSTALL_PROGRAM) -m 4755 -o root $< $@
