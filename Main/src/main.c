#define _GNU_SOURCE // enables getline
#include <stdio.h>
#include <stdlib.h>

#include "strace/strace.h"
// #include "victims/victim.h"
#include "main.h"

int main() {
	
	FILE * f = NULL;
    if ((f = fopen("thread.txt", "r")) == NULL) {
        fprintf(stderr, "No 'thread.txt' exists in current directory!\n");
        return -1; 
    }
	
	operationList *opList = parser("thread.txt");
    
	// printOPList_0 (opList);
	testSort(opList);
	
	deleteOPList(opList);
	fclose(f);
	return 0;
	
}
