#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct treeNode 
{
    char* data; //file or directory name
    int num_children; // number of file/dir contained in this node
    int capacity; // capacity of children list
    int level; // level of this directory, root is set to 0
    struct treeNode** children; // list of directories or files
} Node;


/*
 * PUBLIC insert -- insert path into a tree
 *
 */
void insert(char *filename, Node * root, int thisLevel);

/*
 * PUBLIC printTree -- print a tree to a given file pointer
 *
 */
void printTree(FILE* outfp, Node * root);

/*
 * PUBLIC deleteTree -- free memory of a tree
 *
 */
void deleteTree(Node * root);


static void print (FILE *outfp, char * toPrint, int num);
static void printPrefix (FILE * outfp, int index);
static Node* search(char *filename, Node * curr);


#endif
