
RM = rm -f
CC = gcc
SRC = nf_profiler.c
TARGET = nf_profiler

#OPTION += -static

all: $(TARGET)

$(TARGET): $(SRC)
#	$(CC) $(OPTION) $^ -o $(OUTPUT)
	$(CC) $^ -o $(TARGET)
	chmod +x $(TARGET)

.PHONY: list 
list:
	svn export http://cadinfo.realtek.com.tw/svn/col/DVR/branches/phoenix/bootcode/uboot/examples/flash_writer_u/include/flash/flash_nand_list.h

.PHONY: clean
clean:
	$(RM) *.o $(TARGET) *.bin

