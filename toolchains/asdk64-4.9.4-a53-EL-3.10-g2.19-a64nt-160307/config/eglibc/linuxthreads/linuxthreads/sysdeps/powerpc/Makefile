ifeq ($(subdir):$(elf),linuxthreads:yes)
# See CFLAGS-initfini.s above; this is the same code.
CFLAGS-pt-initfini.s += -fpic -O1
endif
ifeq ($(subdir),csu)
gen-as-const-headers += tcb-offsets.sym
endif
