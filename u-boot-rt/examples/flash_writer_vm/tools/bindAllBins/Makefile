
RM = rm -f
CC = gcc
SRC = bindAllBins.c
TARGET = bindAllBins

#OPTION += -static

ifeq ($(BOOT),yes)
DEFINE += -DBootPartition_StartUp
endif

all: $(TARGET)

$(TARGET): $(SRC)
#	$(CC) $(OPTION) $^ -o $(OUTPUT)
	$(HOSTCC) $^ -o $(TARGET) $(DEFINE)
	chmod +x $(TARGET)


.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

