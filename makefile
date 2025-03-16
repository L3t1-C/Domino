
# Variables
CC = gcc
CFLAGS = -Wall -std=c99 -O2 --pedantic
SRCS = $(wildcard src/*.c main.c)
OBJS = $(SRCS:.c=.o)
TARGET = iap

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

