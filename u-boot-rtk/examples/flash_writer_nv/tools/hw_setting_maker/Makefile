
RM = rm -f
HOSTCC = gcc
SRC = generate_config.c
TARGET = generate_config 

#OPTION += -static

all: $(TARGET)

$(TARGET): $(SRC)
#	$(CC) $(OPTION) $^ -o $(OUTPUT)
	$(HOSTCC) $^ -o $(TARGET)
	chmod +x $(TARGET)


.PHONY: clean
clean:
	$(RM) *.o $(TARGET)

