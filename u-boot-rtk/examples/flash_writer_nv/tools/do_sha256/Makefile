##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Tue Jun 29 13:52:53 2004
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
#include ../../../../include/MakeConfig

PROG_LIB_NAME = do_sha256.a
PROG_NAME  = do_sha256

rm=/bin/rm -f
CC = gcc
LD = gcc
AR = ar
RANLIB = ranlib

CFLAGS = -DSYS_UNIX=1 -shared -D_GNU_SOURCE -Wall -Werror
CPPFLAGS = 

INCLUDES = -I/usr/local/mipsel-linux/include -I../../Include

HEADERS = sha256.h

SRCS = sha256.c do_sha256.c

OBJS = sha256.o do_sha256.o

.c.o.cpp: 
	$(rm) $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $*.c

#all: $(PROG_LIB_NAME)
all: $(PROG_NAME)

$(PROG_LIB_NAME) : $(OBJS) $(SRCS) $(HEADERS)
	$(AR) -rcs $(PROG_LIB_NAME) $(OBJS) $(LIBS)
	$(RANLIB) $(PROG_LIB_NAME)

$(PROG_NAME) : $(OBJS) $(HEADERS)
	$(LD) $(LDFLAGS) -o $(PROG_NAME) $(OBJS)

clean:
	$(rm) $(OBJS) $(PROG_LIB_NAME) core* *~
