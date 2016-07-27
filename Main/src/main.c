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
    
	int priority[] = {2, 4, 5};
	// int priority[] = {2};
	testSort (opList, priority, 3);
	// testSort (opList, priority, 1);
	
	printOPList("[type]\t[startTime]\t[duration]\t[size]\t[path]", opList, "output.txt");
	
	deleteOPList(opList);
	fclose(f);
	return 0;
	
}
