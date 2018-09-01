

##############################################
# Environment
##############################################

PLATFORM = LINUX
#PLATFORM = CYGWIN

MYLIB   = lib/libmcp.a
HOSTCC  = gcc
AR      = ar
VPATH   = obj inc src 
OPENSSL_PATH ?= /usr/local/ssl
OPENSSL_CONFIG_PATH = /usr/include/x86_64-linux-gnu/
 

##############################################
# Dependancy
##############################################
INCS   = -I inc -I $(OPENSSL_PATH)/include/ -I $(OPENSSL_CONFIG_PATH)
OBJS   =  mcp.o 
OBJS  +=  aes_h.o
OBJS  +=  sha1.o
OBJS  +=  sha256.o
OBJS  +=  crc32.o
OBJS  +=  rcic.o

##############################################
# Make
##############################################
all : $(MYLIB) 

%.o:%.c
	@$(HOSTCC) $(CFLAGS) -I inc $(INCS) -c $< -o obj/$@		
	
$(MYLIB): $(OBJS)
	@set -e; for i in $(OBJS); do $(AR) rcv $(MYLIB) obj/$$i; done;		
	
clean:	
	@$(RM) src/*~ src/*.bak 	
	@$(RM) inc/*~ inc/*.bak
	@$(RM) obj/*	
	@$(RM) *~ *.bak *.o $(MYPROG) $(MYLIB)
