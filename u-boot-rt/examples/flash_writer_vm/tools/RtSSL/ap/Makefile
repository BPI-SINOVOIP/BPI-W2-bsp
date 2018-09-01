##############################################
# Environment
##############################################
PLATFORM = LINUX
#PLATFORM = CYGWIN
STATIC_LINK ?= Y

MYLIB   = lib/FileHash.a
HOSTCC  = g++
AR      = ar
VPATH   = obj inc src 
OPENSSL_PATH ?= /usr/local/ssl
LIB_PATH ?= /usr/lib 
MCP_PATH = ../mcp
OPENSSL_CONFIG_PATH = /usr/include/x86_64-linux-gnu/

ifneq ($(findstring CYGWIN, $(PLATFORM)),)
    MYPROG  = ../RtSSL.exe
else
    MYPROG  = ../RtSSL
endif     


##############################################
# Dependancy
##############################################
INCS   = -I inc -I $(OPENSSL_PATH)/include/ -I $(MCP_PATH)/inc -I $(OPENSSL_CONFIG_PATH)
LIBS   = -ldl -L $(OPENSSL_PATH)/lib -lcrypto -lssl ../mcp/lib/libmcp.a
OBJS   =  RtSSL.o auxfun.o FileIO.o Progress.o
OBJS  +=  FileHash.o 
OBJS  +=  FileCipher.o
OBJS  +=  FileCipher_AES.o 
OBJS  +=  FileCipher_RSA.o RSATool.o 

CFLAGS += -g -D$(PLATFORM) 
CFLAGS += -DRSA_USE_SYSTEM_CALL

ifeq ($(STATIC_LINK), Y)
LDFLAGS += -static
endif

##############################################
# DEBUG
##############################################

#CFLAGS += -DSHOW_BLOCK_HASH_VALUE



##############################################
# Make
##############################################
all : $(MYLIB) $(MYPROG)

%.o:%.cpp
	@$(HOSTCC) $(CFLAGS) $(INCS) -c $< -o obj/$@		
	
$(MYLIB): $(OBJS)
	@set -e; for i in $(OBJS); do $(AR) rcv $(MYLIB) obj/$$i; done;	
	
$(MYPROG): $(MYLIB)
	@$(HOSTCC) $(LDFLAGS) $^ $(LIBS) -o $(MYPROG) 		
	
link:	
	@$(RM) $(MYPROG)
	@$(HOSTCC) $(CFLAGS) $(MYLIB) $(LIBS) -o $(MYPROG) 		
	
clean:	
	@$(RM) src/*~ src/*.bak 	
	@$(RM) inc/*~ inc/*.bak
	@$(RM) obj/*	
	@$(RM) *~ *.bak *.o $(MYPROG) $(MYLIB)

install: $(MYPROG)
	@cp  $(MYPROG)   /usr/local/bin
