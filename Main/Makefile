# Compiler
CC = gcc
CFLAGS = -g -Wall 

# Directories
SRC_DIR = src
BIN_DIR = bin
TEMP_DIR = temp
TREE_DIR = src/mytree
STRACE_DIR = src/strace
VICTIMS_DIR = src/victims
OBJ_DIR = .objs

#SRC = $(shell find . -name *.c)

all: dirs mytree test

dirs: $(OBJ_DIR) 
	
$(OBJ_DIR) : 
	@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/mytree.o : $(TREE_DIR)/tree.c $(TREE_DIR)/tree.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/mytree_release.o : $(TREE_DIR)/tree_release.c $(TREE_DIR)/tree.h $(STRACE_DIR)/strace.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/strace.o : $(STRACE_DIR)/strace.c $(STRACE_DIR)/strace.h $(VICTIMS_DIR)/victim.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/victim.o : $(VICTIMS_DIR)/victim.c $(VICTIMS_DIR)/victim.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/main.o : $(SRC_DIR)/main.c $(SRC_DIR)/main.h $(STRACE_DIR)/strace.h
	$(CC) -c $(CFLAGS) $< -o $@

mytree : $(OBJ_DIR)/mytree.o $(OBJ_DIR)/mytree_release.o $(OBJ_DIR)/strace.o $(OBJ_DIR)/victim.o
	$(CC) $^ -o $@

test : $(OBJ_DIR)/main.o $(OBJ_DIR)/strace.o $(OBJ_DIR)/victim.o
	$(CC) $^ -o $@	


#test:
#	$(BIN_DIR)/./test

clean:
	rm -rf mytree test $(OBJ_DIR)
