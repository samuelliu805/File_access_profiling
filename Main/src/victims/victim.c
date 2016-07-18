#include <stdio.h>
#include <stdlib.h>

#include "victim.h"

void cpyStr (char *a, int aL, char *b, int bL) { // copy b to a
	int length = (aL > bL) ? aL : bL;
	for (int i = 0; i < length; i++) {
		*(a + i) = *(b + i);
	}
}

int compareStr (char* a, int l1, char* b, int l2) {
	int i = 0, j = 0;
	while (i < l1 && j < l2) {
		if (*(a + i) != *(b + j)) {
			return *(a + i) - *(b + j);
		}
	}
	return l1 - l2;
}


// input:	[type]\t[startTime]\t[duration]\t[size]\t[path]
// output:	open	14:48:55.120775	0.000051	-1	/etc/ld.so.cache
void printOPList (char *format ,operationList *opList) {

}

void printOPList_0 (operationList *opList) { // for testing purposes
	char *typeC;
	operation *op;
	for (int i = 0; i < opList->size; i++) {
		op = *(opList->list + i);
		switch (op->type) {
			case 0: typeC = "open"; break;
			case 1: typeC = "read"; break;
			case 2: typeC = "write"; break;
			case 3: typeC = "close"; break;
		}
		printf("%s\tstartTime = %s\tduration = %f\tsize = %lld\tpath = %s\n", typeC, op->startTime, op->duration, op->size, op->path);
	}
}

void addOP (char *path, int type, char *startTime, double duration, unsigned long long int size, operationList *opList) {
    //printf("add op\n");
	operation *op = malloc(sizeof(operation));
	cpyStr(op->path, PATH_LENGTH, path, PATH_LENGTH);
	
    op->type = type;
	op->startTime = calloc(StartTime_LENGTH, sizeof(char));
	cpyStr(op->startTime, StartTime_LENGTH, startTime, StartTime_LENGTH);
	op->duration = duration;
	op->size = size;
	pushOP(op, opList);
}

operationList* createOPList () {
	operationList *opList = malloc(sizeof(operationList));
	opList->size = 0;
	opList->length = 2;
	opList->list = malloc(opList->length * sizeof(operation*));
	return opList;
}

void deleteOPList () {
	// ...
}

void pushOP (operation *op, operationList *opList) {
    //printf("push op\n");
	if (opList->size == opList->length) {
		opList->length *= 1.5;
		opList->list = realloc(opList->list, opList->length * sizeof(operation*));
	}
	*(opList->list + opList->size++) = op;
}



unsigned long long int totalSize (operationList *opList, char *path, int type) {
	unsigned long long int output = 0;
	for (int i = 0; i < opList->size; i++) {
		if ( strcmp(opList->list[i]->path, path) == 0 ) {
			if (opList->list[i]->type == type) {
				output += opList->list[i]->size;
			}
		}
	}
	return output;
}



/*
priorityQ* createQ () {
	priorityQ *q = malloc(sizeof(priorityQ));
	q->size = 0;
	q->length = 10;
	q->list = malloc(sizeof(victim) * length);
	return q;
}

void pushQ (priorityQ* q, victim* v) {
	
	if (q->size == q->length) {
		q->length *= 1.5;
		q->list = realloc(q->list, sizeof(victim) * length);
	}
	*(q->list + q->size++) = v;
	
	int cIndex = q->size - 1, pIndex, compare;
	while (cIndex > 0) {
		pIndex = (cIndex - 1) / 2;
		compare = comparePath(v->path, PATH_LENGTH, (q->list + pIndex)->path, PATH_LENGTH);
		if (compare == 0) {
			pushOperation (q->list + pIndex, v);
			*(q->list + cIndex) = *(q->list + q->size--);
			int newPIndex = cIndex, newCIndex1, newCIndex, newCIndex2, newCompare;
			while (newPIndex < q->size) {
				newCIndex1 = newPIndex * 2 + 1;
				newCIndex2 = newPIndex * 2 + 2;
				if (newCIndex1 >= q->size) { // no child
					break;
				} else if (newCIndex2 >= q->size) {
					newCIndex = newCIndex1;
				} else if (comparePath((q->list + newCIndex1)->path, PATH_LENGTH, (q->list + newCIndex2)->path, PATH_LENGTH) < 0) {
					newCIndex = newCIndex1;
				} else {
					newCIndex = newCIndex2;
				}
				if (comparePath((q->list + newPIndex)->path, PATH_LENGTH, (q->list + newCIndex)->path, PATH_LENGTH) > 0) {
					// ... swap?
				} else {
					break;
				}
			}
			break;
		} else if (compare < 0) {
			*(q->list + cIndex) = *(q->list + pIndex);
			*(q->list + pIndex) = v;
			cIndex = pIndex;
		} else {
			break;
		}
	}
	
}



void pushOperation (victim* v1, victim* v2) {}

void deleteQ () {}

victim* createVictim () {
	
}

void pushOperation (
	char *path,
	const int type,
	char *startTime,
	const double duration,
	unsigned long long int size
) {
	operation *oper = malloc(sizeof(operation));
	oper->type = type;
	oper->startTime = startTime;
	oper->duration = duration;
	oper->size = size;
	oper->next = NULL;
	// ...
}

void deleteOperation () {}

*/
