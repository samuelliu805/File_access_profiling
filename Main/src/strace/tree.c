#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tree.h"

/* defined macros (Currently for printing in Mac OS X)*/
#define INIT_CAPACITY 10
#define T_FRAME "\342\224\234"
#define H_BAR "\342\224\200"
#define V_BAR "\342\224\202"
#define BOTTOM "\342\224\224"

/* Global Variables */
int *finished = NULL; // a list keeping track of whether a node has finished printing all its children. 0 for finished and 1 for not
int finishedCap = 0; // capacity of finished list
int finishedNum = 0; // number of elements in the finished list

/* main function for demo */
int main (int argc, char * argv[])
{
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = "";
    root->num_children = 0;
    root->capacity = INIT_CAPACITY;
    root->children = (Node**)malloc(sizeof(Node*) * INIT_CAPACITY);
    root->level = 0;
    finished = (int *) malloc(sizeof(int) * INIT_CAPACITY);
    finishedCap = INIT_CAPACITY;
    int i = 0;
    for (i = 1; i < argc; i++)
    {
        insert(argv[i],root,0);
    }

    printTree(stdout, root);
    deleteTree(root);
    free(finished);
    return 0;
}


void insert (char * filename, Node* root, int thisLevel)
{
    if (filename == NULL || !strcmp("", filename)) return ;
    char * next = filename;
    char * curr = filename;
    int flag = 0;
    Node * child = NULL;
    
    // get current directory name or filename
    while (*curr != '\0')
    {
        if (*curr == '/')
        {
            *curr = '\0';
            next = curr + 1;
            flag = 1;
        }
        else 
        {
            curr++;
        }
    }
    if (!flag) next = NULL;

    //if no such directory ever exists, create one
    //else, recursively create nodes for directory
    if ((child = search(filename, root)) == NULL)
    {
 
        // reallocate when children is full 
        if (root->num_children < root -> capacity)
        {
            root->capacity *= 2;
            root->children = (Node **)realloc(root->children, root->capacity*sizeof(Node*));
        }

        // initialization of a new node
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = filename; 
        newNode->capacity = INIT_CAPACITY;
        newNode->num_children = 0;
        newNode->level = thisLevel;
        newNode->children = (Node **) malloc(sizeof(Node *) * INIT_CAPACITY);
        (root->children)[root->num_children] = newNode;
        root->num_children++;


        insert(next, newNode, ++thisLevel);

    }
    else 
    {
        insert(next, child, ++thisLevel);
    }
    return; 
}

Node* search (char * filename_rel, Node * curr)
{
    int i = 0;
    Node ** curr_children = curr->children;
    if (curr_children == NULL)
    {
        return NULL;
    }
    for (i = 0; i < curr->num_children; i++)
    {
        if (!strcmp(curr_children[i]->data, filename_rel))
        {
            return curr_children[i]; 
        }
    }
    return NULL;
}

void print (FILE *outfp, char * toPrint, int num)
{
    int i = 0;
    for (i = 0; i < num; i++)
    {
        fprintf(outfp, "%s",toPrint);
    }
}

void printPrefix (FILE * outfp, int index)
{

    int i = 0;
    for (i = 0; i < index; i++)
    {
        if (i != index - 1)
        {
            if (!finished[i]) 
            {
                print (outfp, V_BAR, 1);
            }
            else 
            {
                print (outfp," ", 1);
            }
            print (outfp, " ", 3);
        }
        else
        {
            if (!finished[i])
            {
                print (outfp, T_FRAME, 1);
            }
            else 
            {
                print (outfp, BOTTOM, 1);
            }
            print (outfp, H_BAR, 2);
            print (outfp, " ", 1);
        }
    }


}

void printTree(FILE * outfp, Node* root)
{
    if (finishedNum == finishedCap)
    {
        finishedCap *= 2;
        finished = (int *)realloc(finished, finishedCap);
    }

    finished[root->level] = 0;    
    finishedNum++;
    printPrefix (outfp, root->level); 
    print(outfp, root->data, 1);
    print(outfp, "\n", 1);
    int i = 0;
    for (i = 0; i < root->num_children; i++)
    {
        if (i == root->num_children - 1)
        {
            finished[root->level] = 1;
        }
        printTree (outfp, root->children[i]);
    }
}

void deleteTree(Node * root)
{

    int i = 0;
    for (i = 0; i < root->num_children; i++)
    {
        deleteTree(root->children[i]);
    }
    free(root->children);
    free(root);
}
