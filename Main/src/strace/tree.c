#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tree.h"

#define INIT_CAPACITY 10

void print (FILE *outfp, char * toPrint, int num);
void printPrefix (FILE * outfp, int index);


int level = 0;
int maxLenIndex = -1;
int maxLenCap = 0;
int *maxLen = NULL;

int main (int argc, char * argv[])
{
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = "";
    root->num_children = 0;
    root->capacity = INIT_CAPACITY;
    root->children = (Node**)malloc(sizeof(Node*) * INIT_CAPACITY);
    root->level = 0;
    maxLen = (int *) malloc(sizeof(int) * INIT_CAPACITY);
    maxLenCap = INIT_CAPACITY;
    int i = 0;
    for (i = 1; i < argc; i++)
    {
        insert(argv[i],root,0);
    }

    printf ("[");
    for (i = 0; i <= maxLenIndex; i++)
    {
        printf("%d ", maxLen[i]);
    }
    printf("]\n");
    printf("maxLenIndex: %d\n", maxLenIndex);
   // printPrefix (stdout, 2);
    printTree(stdout, root);
    //    deleteTree(root);
    return 0;
}


int insert (char * filename, Node* root, int thisLevel)
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
        newNode->level = thisLevel;
        newNode->children = (Node **) malloc(sizeof(Node *) * INIT_CAPACITY);
        (root->children)[root->num_children] = newNode;
        root->num_children++;


        if (maxLenIndex < thisLevel)
        {
            if (maxLenCap == maxLenIndex)
            {
                maxLen = (int *) realloc(maxLen, 2*maxLenCap);
                maxLenCap *= 2;
            }
            maxLen[thisLevel] = strlen(filename);
            maxLenIndex++;
        }
        else 
        {
            if ((int)strlen(filename) > maxLen[thisLevel])
            {
                maxLen[thisLevel] = strlen(filename);
            }

        }
        insert(next, newNode, ++thisLevel);



    }
    else 
    {
        insert(next, child, ++thisLevel);
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
        if (i == index - 1) fprintf (outfp, "|");
        else fprintf (outfp, " ");
        if (i != index - 1)
        {
            print(outfp, " ", maxLen[i] + 3);
        }
    }
}

void printTree(FILE * outfp, Node* root)
{
    /*
       fprintf(outfp, "%s\nchildren: \n", root->data);
       int i = 0;
       for (i = 0; i < root->num_children; i++)
       {
       printTree (outfp, root->children[i]);
       }
       */


    //printf ("data: %s, level: %d, root level %d\n", root->data, level, root->level);
    if (root->level != 0)
    {
        if (root->level <= level)
        {
            printPrefix(outfp, root->level); 
            print(outfp, "-", maxLen[root->level - 1] + 3);
        }
        else
        {
            ;
            //print(outfp, "-", 4);
        }
    }
    //  printf("num_children -- %d\n", root->num_children);


    if (root->num_children == 0)
    {
        print(outfp, root->data, 1);
        print(outfp, "\n", 1);
        level = root->level;
        return;
    }
    else
    {
        print(outfp, root->data, 1);
        level = root->level;
        if (root->level != 0)
            print(outfp, "-", maxLen[root->level] - strlen(root->data) + 4);
        else 
            print(outfp,"-", 2);
            
        int i = 0;
        for (i = 0; i < root->num_children; i++)
        {
            printTree(outfp, root->children[i]);
        }
    }

}

void deleteTree(Node * root)
{

}
