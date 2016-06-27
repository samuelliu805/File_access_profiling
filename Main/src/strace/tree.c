#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tree.h"

#define INIT_CAPACITY 10

int main (int argc, char * argv[])
{
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = "";
    root->num_children = 0;
    root->capacity = INIT_CAPACITY;
    root->children = (Node**)malloc(sizeof(Node*) * INIT_CAPACITY);
    int i = 0;
    for (i = 1; i < argc; i++)
    {
        insert(argv[i],root);
    }
    printTree(stdout, root);
    deleteTree(root);
    return 0;
}


int insert (char * filename, Node* root)
{
    char * next = filename;
    char * curr = filename;
    Node * child = NULL;
    while (*curr != '\0')
    {
        if (*curr == '/')
        {
            *curr = '\0';
            next = curr + 1;
        }
        curr++;
    }
    
    if ((child = search(filename, root)) == NULL)
    {
        //TODO: 
        //CASE 1 -- num_children < capacity --> add
        //CASE 2 -- num_children >= capacity --> realloc (2x) ; add;
        //
        //add    -- malloc node; init vals;   
    }
    else 
    {
        insert(next, child);
    }
    return 0; 
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

void printTree(FILE * outfp, Node* root)
{

}

void deleteTree(Node * root)
{

}
