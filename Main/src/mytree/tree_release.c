#include "tree.h"

void usage();

int main (int argc, char * argv[])
{
    /*
       Node * root = init_var();

       printTree(stdout, root);
       clear(root);
       */

    char read = 0;
    char * filename = NULL;
    int fflag = 0, lflag = 0;
    while ((read = getopt(argc, argv, "f:l:")) != -1)
    {
        switch (read)
        {
            case 'f': fflag = 1;
                      filename = optarg;
                      break;
            case 'l': lflag = 1;
                      break;
            default : usage();
                      return -1;
        }
    }

    if (fflag && lflag)
    {
        usage();
        return -1;
    }

    Node * root = init_var();
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
        int i = 0;
        for (i = 2; i < argc; i++)
        {
            insertPath(argv[i],root);
        }


    }
    else 
    {
        usage();
        clear(root);
        return -1;
    }

    printTree(stdout, root);
    clear(root);
    return 0;
}

void usage()
{
    fprintf(stderr, "You may only have one flag!\nUsage: ./tree [-f filename] [-l filepath1 filepath2 ...]\n");
}


