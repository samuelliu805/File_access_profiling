#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define INIT_CAPACITY 10
typedef struct treeNode 
{
    char* data;                 // file or directory name
    int num_children;           // number of file/dir contained in this node
    int capacity;               // capacity of children list
    int level;                  // level of this directory, root is set to 0
    struct treeNode** children; // list of directories or files
} Node;

/*
 * PUBLIC 
 * init_var -- initialize everything for a tree
 * This function initialize all necessary variables for a tree. 
 * It will return a dynamically allocated empty root Node
 * 
 * @return: empty root node of a new tree       
 */
Node * init_var();

/*
 * PUBLIC 
 * clear -- clear all memory of a tree
 * This function frees all allocated memory of a tree data structure.
 *
 * @params: root -- root node of the tree to be cleared
 */
void clear(Node * root);
/*
 * PUBLIC 
 * insert -- insert path into a tree
 * This function takes a file path string, parse it using '/' as delimiter, 
 * and insert every segment of the file path to a tree recursively
 *
 * @params: filename    -- the full file path
 *          root        -- root node of the tree
 *          thisLevel   -- current level of node, 0 by default (if it is absolute file path)
 * 
 */
void insertPath (char * filename, Node * root);

/*
 * PUBLIC 
 * printTree -- print a tree to a given file pointer
 * This function prints the tree to given stream
 *
 * @params: outfp   -- given file pointer for output
 *          root    -- root node of the tree
 * 
 */
void printTree(FILE* outfp, Node * root);

#endif
