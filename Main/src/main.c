#define _GNU_SOURCE // enables getline
#include <stdio.h>
#include <stdlib.h>

#include "strace/strace.h"
// #include "victims/victim.h"
#include "main.h"

int main() {
	
	/* no longer necessary
	int pathType = getPathType();
	char *programName = readProgramName();
	operationList *opList = strace (programName, pathType);
	printOPList_0(opList);
	
	free(programName); */
	
    if (fopen("thread.txt", "r") == NULL) 
    {
        fprintf(stderr, "No 'thread.txt' exists in current directory!\n");
        return -1; 
    }
    //system ("pwd");
	operationList *opList = parser("thread.txt");
    printf ("%d %d\n", opList->size, opList->length);
    printOPList_0 (opList);
	return 0;
	
}


/* no longer necessary

int getPathType () {
	int type = -1;
	while (type != 0 && type != 1) {
		printf("path type (0: absolute; 1: relative): ");
		scanf("%d", &type);
	}
	getchar();
	return type;
}

char* readProgramName() {
	
	char *programName;
	size_t programNameLength = 100;
	size_t programNameActLength;
	int i;
	
	programName = malloc(sizeof(char) * programNameLength);
	
	printf("please enter the program that you want to execute: ");
	programNameActLength = getline(&programName, &programNameLength, stdin);
	// *(programName + programNameActLength - 1) = 0;
	
	i = programNameActLength;
	
	while (i >= 0) {
		if (
			*(programName + i) == '\n' ||
			*(programName + i) == '\r' ||
			*(programName + i) == '\t' ||
			*(programName + i) == ' '
		) {
			*(programName + i) = 0;
			i--;
		} else {
			break;
		}
	}
	
	return programName;
	
} */
