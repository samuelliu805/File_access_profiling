# Compiler
CC = gcc
CFLAGS = -g -Wall -std=c99

# Directories
# SRC_DIR = src
BIN_DIR = bin
TEMP_DIR = temp

SRC = $(shell find . -name *.c)

all: clean dirs
	# $(CC) $(CFLAGS) $(SRC_DIR)/main.c $(SRC_DIR)/strace/strace.c -o $(BIN_DIR)/test
	$(CC) $(CFLAGS) $(SRC) -o $(BIN_DIR)/test

dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(TEMP_DIR)

test:
	$(BIN_DIR)/./test

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(TEMP_DIR)
