##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Tue Jun 29 13:52:53 2004
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
#include ../../../../include/MakeConfig

rm=/bin/rm -f
#CROSS = sde

CC = gcc
LD = gcc
AR = ar
RANLIB = ranlib

#CC = ${CROSS}-gcc
#LD = ${CROSS}-ld
#AR = $(CROSS)-ar
#RANLIB = $(CROSS)-ranlib

PROG_LIB_NAME = liblogo_changer.a
PROG_NAME = logo_changer
CFLAGS = -D_GNU_SOURCE -DSYS_UNIX=1 -shared -Wall -Werror
CPPFLAGS =

INCLUDES = -I/usr/local/mipsel-linux/include -I../../Include

HEADERS = logo.h SpuGen.h vo_reg.h

SRCS = logo.c SpuGen.c

OBJS = logo.o SpuGen.o

.c.o.cpp:
	$(rm) $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $*.c

#all: $(PROG_LIB_NAME)
all: $(PROG_NAME)

$(PROG_LIB_NAME) : $(OBJS) $(SRCS) $(HEADERS)
	$(AR) -rcs $(PROG_LIB_NAME) $(OBJS) $(LIBS)
	$(RANLIB) $(PROG_LIB_NAME)

$(PROG_NAME) : $(OBJS) $(SRCS) $(HEADERS)
	$(LD) $(LDFLAGS) -o $(PROG_NAME) $(OBJS)

clean:
	$(rm) $(OBJS) $(PROG_LIB_NAME) core* *~ VO_UpdateLogo.txt
