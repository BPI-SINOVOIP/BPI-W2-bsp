# Copyright (C) 1991-2014 Free Software Foundation, Inc.
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
#	Specific makefile for stdio-common.
#
include ../option-groups.mak

subdir	:= stdio-common

headers	:= stdio_ext.h printf.h bits/printf-ldbl.h bits/stdio_lim.h

routines	:=							      \
	ctermid cuserid							      \
	_itoa _itowa itoa-digits itoa-udigits itowa-digits		      \
	vfprintf vprintf printf_fp reg-printf printf-prs printf_fphex	      \
	reg-modifier reg-type						      \
	printf_size fprintf printf snprintf sprintf asprintf dprintf	      \
	vfscanf								      \
	fscanf scanf sscanf						      \
	perror psignal							      \
	tmpfile tmpfile64 tmpnam tmpnam_r tempnam tempname		      \
	getline getw putw						      \
	remove rename renameat						      \
	flockfile ftrylockfile funlockfile				      \
	isoc99_scanf isoc99_vscanf isoc99_fscanf isoc99_vfscanf isoc99_sscanf \
	isoc99_vsscanf							      \
	psiginfo
# Ideally, _itowa and itowa-digits would be in this option group as
# well, but it is used unconditionally by printf_fp and printf_fphex,
# and it didn't seem straightforward to disentangle it.
routines-$(OPTION_POSIX_C_LANG_WIDE_CHAR) +=				      \
	vfwprintf vfwscanf

include ../Makeconfig

aux	:= errlist siglist printf-parsemb fxprintf
aux-$(OPTION_POSIX_C_LANG_WIDE_CHAR) += printf-parsewc

tests := tstscanf test_rdwr test-popen tstgetln test-fseek \
	 temptest tst-fileno test-fwrite tst-ungetc tst-ferror \
	 xbug errnobug \
	 bug1 bug2 bug3 bug4 bug5 bug6 bug7 bug8 bug9 bug10 bug11 bug12 bug13 \
	 tfformat tiformat tllformat tstdiomisc tst-printfsz \
	 scanf1 scanf2 scanf3 scanf4 scanf5 scanf7 scanf8 scanf9 scanf10 \
	 scanf11 scanf12 tst-tmpnam tst-cookie tst-obprintf \
	 tst-fseek tst-fmemopen tst-gets \
	 tst-sprintf tst-rndseek tst-fdopen tst-fphex \
	 tst-popen tst-unlockedio tst-fmemopen2 tst-put-error tst-fgets \
	 tst-fwrite bug16 bug17 tst-sprintf2 bug18 \
	 bug19 tst-popen2 scanf14 scanf15 bug21 bug22 scanf16 scanf17 \
	 tst-setvbuf1 bug23 bug24 bug-vfprintf-nargs tst-sprintf3 bug25 \
	 tst-printf-round bug26
tests-$(OPTION_EGLIBC_LOCALE_CODE) \
      += tst-sscanf tst-swprintf test-vfprintf bug14 scanf13 tst-grouping
tests-$(OPTION_POSIX_WIDE_CHAR_DEVICE_IO) \
      += tst-perror bug19a bug20 tst-long-dbl-fphex tst-fphex-wide
tests-$(OPTION_POSIX_C_LANG_WIDE_CHAR) \
      += bug18a tst-swscanf tst-wc-printf

test-srcs = tst-unbputc tst-printf

include ../Rules

ifeq ($(run-built-tests),yes)
.PHONY: do-tst-unbputc do-tst-printf
tests: do-tst-unbputc do-tst-printf

do-tst-unbputc: $(objpfx)tst-unbputc.out
$(objpfx)tst-unbputc.out: tst-unbputc.sh $(objpfx)tst-unbputc
	$(SHELL) $< $(common-objpfx) '$(test-program-prefix)'

do-tst-printf: $(objpfx)tst-printf.out
$(objpfx)tst-printf.out: tst-printf.sh $(objpfx)tst-printf
	$(SHELL) $< $(common-objpfx) '$(test-program-prefix)'
endif

CFLAGS-vfprintf.c = -Wno-uninitialized
CFLAGS-vfwprintf.c = -Wno-uninitialized
CFLAGS-tst-printf.c = -Wno-format
CFLAGS-tstdiomisc.c = -Wno-format
CFLAGS-scanf4.c = -Wno-format
CFLAGS-scanf7.c = -Wno-format
CFLAGS-tst-printfsz.c = -Wno-format

CFLAGS-tmpfile.c = -fexceptions
CFLAGS-tmpfile64.c = -fexceptions
CFLAGS-tempname.c = -fexceptions
CFLAGS-psignal.c = -fexceptions
CFLAGS-vprintf.c = -fexceptions
CFLAGS-cuserid.c = -fexceptions

CFLAGS-vfprintf.c += $(exceptions)
CFLAGS-fprintf.c += $(exceptions)
CFLAGS-printf.c += $(exceptions)
CFLAGS-vfwprintf.c += $(exceptions)
CFLAGS-vfscanf.c += $(exceptions)
CFLAGS-vfwscanf.c += $(exceptions)
CFLAGS-fscanf.c += $(exceptions)
CFLAGS-scanf.c += $(exceptions)
CFLAGS-isoc99_vfscanf.c += $(exceptions)
CFLAGS-isoc99_vscanf.c += $(exceptions)
CFLAGS-isoc99_fscanf.c += $(exceptions)
CFLAGS-isoc99_scanf.c += $(exceptions)
CFLAGS-errlist.c = $(fno-unit-at-a-time)
CFLAGS-siglist.c = $(fno-unit-at-a-time)

# The following is a hack since we must compile scanf1{5,7}.c without any
# GNU extension.  The latter are needed, though, when internal headers
# are used.  So made sure we see the installed headers first.
CFLAGS-scanf15.c = -I../libio -I../stdlib -I../wcsmbs -I../time -I../string \
		   -I../wctype
CFLAGS-scanf17.c = -I../libio -I../stdlib -I../wcsmbs -I../time -I../string \
		   -I../wctype

# We know the test has a format string problem.
CFLAGS-tst-sprintf.c = -Wno-format
tst-sprintf-ENV = LOCPATH=$(common-objpfx)localedata
tst-sscanf-ENV = LOCPATH=$(common-objpfx)localedata
tst-swprintf-ENV = LOCPATH=$(common-objpfx)localedata
tst-swscanf-ENV = LOCPATH=$(common-objpfx)localedata
test-vfprintf-ENV = LOCPATH=$(common-objpfx)localedata
scanf13-ENV = LOCPATH=$(common-objpfx)localedata
bug14-ENV = LOCPATH=$(common-objpfx)localedata
tst-grouping-ENV = LOCPATH=$(common-objpfx)localedata

CPPFLAGS += $(libio-mtsafe)

$(objpfx)tst-setvbuf1.out: tst-setvbuf1.expect $(objpfx)tst-setvbuf1
	$(test-program-cmd) > $@ 2>&1
	cmp tst-setvbuf1.expect $@

ifeq ($(build-shared),yes)
link-libm = $(common-objpfx)math/libm.so
else
link-libm = $(common-objpfx)math/libm.a
endif
$(objpfx)tst-printf-round: $(link-libm)
