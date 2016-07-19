#include "tree.h"
#include "../strace/strace.h" 

void usage();

int main (int argc, char * argv[])
{
    char read = 0;
    char * filename = NULL;
    int fflag = 0, lflag = 0, i = 0;
    while ((read = getopt(argc, argv, "f:l:")) != -1)
    {
        switch (read)
        {
            case 'f': fflag = 1;
                      filename = optarg;
                      break;
            case 'l': lflag = 1;
                      break;
            default : break;
                    
        }
    }

    Node * root = init_var();
    if (fflag && lflag)
    {
        usage();
        return -1;
    }

    if (fflag)
    {
        FILE * fp = fopen(filename, "r");
        char * buf = NULL;
        size_t size = 0;
        ssize_t num_read = 0;
        while ((num_read = getline(&buf, &size, fp)) != -1)
        {
            buf[strlen(buf) - 1] = '\0';
            //printf ("%s\n", buf);
            insertPath(buf, root); 
        }
    }
    else if (lflag)
    {
        for (i = 2; i < argc; i++)
        {
            insertPath(argv[i],root);
        }
    }    
    else 
    {
        if (fopen("thread.txt", "r") == NULL) 
        {
            fprintf(stderr, "No 'thread.txt' exists in current directory!\n");
            return -1; 
        }
	    operationList *opList = parser("thread.txt"); 
        char bytes[1000];
        char path[1000]; 
        for (i = 0; i < opList->size; i++)
        {
            sprintf(bytes, " (total read: %d bytes; total write: %d bytes)", (int)getNumOfBytes(opList, opList->list[i]->path, READ), 
                                                              (int)getNumOfBytes(opList, opList->list[i]->path, WRITE));
            strcpy(path, opList->list[i]->path);
            strcat(path, bytes);
            insertPath(path, root);
        }

    }
    
    printTree(stdout, root);
    clear(root);
    return 0;
}

void usage()
{
    fprintf(stderr, "You may only have one flag!\nUsage: ./tree [-f filename] [-l filepath1 filepath2 ...]\n");
}


