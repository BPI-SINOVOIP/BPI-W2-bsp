
RM = rm -f
HOSTCC = gcc
SRC = bindAllBins.c
TARGET = bindAllBins

#OPTION += -static

ifeq ($(BOOT),yes)
DEFINE+=-DBootPartition_StartUp
endif

all: $(TARGET)

$(TARGET): $(SRC)
#	$(CC) $(OPTION) $^ -o $(OUTPUT)
	$(HOSTCC) $^ -o $(TARGET) $(DEFINE)
#	gcc $^ -o $(TARGET)
	chmod +x $(TARGET)


.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

