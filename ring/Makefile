CC      = gcc
CFLAGS ?= -std=c11 -Wall -Wextra -O2 -g
TARGET   = test_ring.exe
SRCS     = ring.c test.c

TMP  := $(CURDIR)
TEMP := $(CURDIR)
export TMP TEMP

all: $(TARGET)

$(TARGET): $(SRCS) ring.h
	$(CC) $(CFLAGS) $(SRCS) -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: all test clean