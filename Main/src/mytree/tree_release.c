#include <fcntl.h>
#include "tree.h"
#include "../strace/strace.h" 

void usage();
int search_memo(char **memo, char * str, int size);

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
                          //                          char bytes[1000];
                          char path[1000]; 
                          char ** memoPath = (char **)malloc(100* sizeof(char *));
                          int memo_size = 0;
                          for (i = 0; i < opList->size; i++)
                          {

                              if (strcmp("NULL", opList->list[i]->path) && !search_memo(memoPath, opList->list[i]->path, memo_size))
                              {
                                  sprintf(path, "%s (total read: %d bytes; total write: %d bytes)", 
                                  opList->list[i]->path,
                                  (int)getNumOfBytes(opList, opList->list[i]->path, READ), 
                                  (int)getNumOfBytes(opList, opList->list[i]->path, WRITE)); 
                                    
                                  //strcpy(path, opList->list[i]->path);
                                  //strcat(path, bytes);


                                  //strcat (opList->list[i]->path, bytes);
                                  insertPath(path, root);
                                  memoPath[memo_size++] = strdup(opList->list[i]->path);
                              }
                          }

                          deleteOPList_0(opList);
                          fclose(thread_fp);
                          for (i = 0; i < memo_size; i++)
                          {
                              free(memoPath[i]);
                          }
                          free(memoPath);
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

int search_memo(char **memo, char * str, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (!strcmp (memo[i], str))
        {
            return 1;
        }
    }
    return 0;
}
