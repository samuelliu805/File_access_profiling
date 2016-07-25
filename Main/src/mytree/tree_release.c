#include <fcntl.h>
#include "tree.h"
#include "../strace/strace.h" 

void usage();

void usage()
{
    fprintf(stderr, "\n\n\tUsage: ./filetree [-t parsefile_name] [-o output_filename] [-f path_filename] [-l filepath1 filepath2 ...]\n\n\n");
}


int main (int argc, char * argv[])
{
    char read = 0;
    char * filename = NULL;
    int flag = 0, i = 0, index = 0;
    Node * root = init_var();
    FILE *outfp = stdout;
    while ((read = getopt(argc, argv, "f:l:t:o:")) != -1)
    {
        switch (read)
        {
            case 'f': {
                          flag = 1;
                          filename = optarg;
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
                          break;
                      }
            case 'l': {
                          flag = 1;
                          index = optind-1;
                          while(index < argc){
                              if(argv[index][0] != '-')
                              {
                                  /* check if optarg is next switch */
                                  insertPath(argv[index], root);  
                                  index++;
                              }
                              else break;
                          }
                          optind = index;
                          break;
                      }
            case 't': {
                          flag = 1;
                          FILE * thread_fp = NULL;
                          if ((thread_fp = fopen(optarg, "r")) == NULL) 
                          {
                              fprintf(stderr, "No '%s' exists in current directory!\n", optarg);
                              return -1; 
                          }
                          operationList *opList = parser(optarg); 
                          char bytes[1000];
                          char path[1000]; 
                          for (i = 0; i < opList->size; i++)
                          {
                              sprintf(bytes, " (total read: %d bytes; total write: %d bytes)", 
                                      (int)getNumOfBytes(opList, opList->list[i]->path, READ), 
                                      (int)getNumOfBytes(opList, opList->list[i]->path, WRITE));
                              strcpy(path, opList->list[i]->path);
                              strcat(path, bytes);
                              insertPath(path, root);
                          }

                          deleteOPList_0(opList);
                          fclose(thread_fp);

                          break;
                      }
                      
            case 'o': {
                          outfp = fopen(optarg,"w");
                          break;
                      }
            default : ;
                      


        }
    }

    if (!flag) 
    {
        usage();
        clear(root);
        fclose(outfp);
        return -1;
    }

    //FILE * x = stdout;
    printTree(outfp, root);
    clear(root);
    fclose(outfp);
    return 0;
}


