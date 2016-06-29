#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct treeNode 
{
    char* data;
    int num_children;
    int capacity;
    int level;
    struct treeNode** children;
} Node;

int insert(char *filename, Node * root, int thisLevel);
Node* search(char *filename, Node * curr);
void printTree(FILE* outfp, Node * root);
void deleteTree(Node * root);

#endif
