##############################################
# Tool Chain
##############################################
CC        = g++
AR        = ar
RM        = rm -vf
MAKEFLAGS = --no-print-directory	
CFLAGS =
##############################################
# PATH
##############################################
OPENSSL_PATH ?= /usr/local/ssl

##############################################
# export control
##############################################
export   

##############################################
# Make
##############################################
SUBDIRS  := mcp ap

.PHONY: clean_lib rb test all clean $(SUBDIRS) 
     
all :  clean 
	@set -e; for i in $(SUBDIRS); do $(MAKE) -C $$i; done;			
	
clean_lib:
	@$(RM) $(MYLIB)  
	
clean: clean_lib
	@set -e; for i in $(SUBDIRS); do $(MAKE) clean -C $$i; done;
	@$(RM) *.bak *~	

test:
	@$(MAKE) link -C $(UNIT_TEST_PATH)

rb: clean all
	
