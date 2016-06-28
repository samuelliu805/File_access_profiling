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
//    deleteTree(root);
    return 0;
}


int insert (char * filename, Node* root)
{
    if (filename == NULL || !strcmp("", filename)) return 0;
    char * next = filename;
    char * curr = filename;
    int flag = 0;
    Node * child = NULL;
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
    
    if ((child = search(filename, root)) == NULL)
    {
        //TODO: 
        //CASE 1 -- num_children < capacity --> add
        //CASE 2 -- num_children >= capacity --> realloc (2x) ; add;
        //
        //add    -- malloc node; init vals;   
        if (root->num_children < root -> capacity)
        {
            root->capacity *= 2;
            root->children = (Node **)realloc(root->children, root->capacity*sizeof(Node*));
        }
    
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = filename; 
        newNode->capacity = INIT_CAPACITY;
        newNode->num_children = 0;
        newNode->children = (Node **) malloc(sizeof(Node *) * INIT_CAPACITY);
        (root->children)[root->num_children] = newNode;
        root->num_children++;
        insert(next, newNode);


        
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
    fprintf(outfp, "%s\nchildren: \n", root->data);
    int i = 0;
    for (i = 0; i < root->num_children; i++)
    {
        printTree (outfp, root->children[i]);
    }

}

void deleteTree(Node * root)
{

}
