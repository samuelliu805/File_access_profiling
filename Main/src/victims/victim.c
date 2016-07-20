#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "victim.h"

int comparePath (const void *s1, const void *s2) {
	operation *op1 = *((operation **) s1);
	operation *op2 = *((operation **) s2);
	int output = compareStr(op1->path, PATH_LENGTH, op2->path, PATH_LENGTH);
	if (output != 0) {
		return output;
	} else {
		return compareStartTime(s1, s2);
	}
	
}

int compareType (const void *s1, const void *s2) {
	operation *op1 = *((operation **) s1);
	operation *op2 = *((operation **) s2);
	return op1->type - op2->type;
}

int compareStartTime (const void *s1, const void *s2) {
	operation *op1 = *((operation **) s1);
	operation *op2 = *((operation **) s2);
	return compareStr(op1->startTime, StartTime_LENGTH, op2->startTime, StartTime_LENGTH);
}

int compareDuration (const void *s1, const void *s2) {
	operation *op1 = *((operation **) s1);
	operation *op2 = *((operation **) s2);
	if (op1->duration == op2->duration) {
		return 0;
	} else {
		return (op1->duration > op2->duration) ? 1 : -1;
	}
}

int compareSize (const void *s1, const void *s2) {
	operation *op1 = *((operation **) s1);
	operation *op2 = *((operation **) s2);
	if (op1->size == op2->size) {
		return 0;
	} else {
		return (op1->size > op2->size) ? 1 : -1;
	}
}

void cpyStr (char *a, int aL, char *b, int bL) { // copy b to a
	int length = (aL < bL) ? aL : bL;
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
		i++;
		j++;
	}
	return l1 - l2;
}


// input:	[type]\t[startTime]\t[duration]\t[size]\t[path]
// output:	open	14:48:55.120775	0.000051	-1	/etc/ld.so.cache
void printOPList (char *format, operationList *opList) {
	char *flagList[] = {
		"path",
		"type",
		"startTime",
		"duration",
		"size"
	};
	int numOfFlag = 5;
	char *typeC;
	operation *op;
	for (int i = 0; i < opList->size; i++) {
		op = *(opList->list + i);
		int j = -1;
		while (format[++j] != 0) {
			if (strncmp((format + j), "\[", 2) == 0) {
				printf("[");
				j++;
				// continue;
			} else if (format[j] == '[') {
				for (int k = 0; k < numOfFlag; k++) {
					// printf("%s\t%d\n\n", flagList[k], strlen(flagList[k]));
					if (strncmp((format + j + 1), flagList[k], strlen(flagList[k])) == 0) {
						switch (k) {
							case 0:
								printf("%s", op->path);
								break;
							case 1:
								switch (op->type) {
									case 0: typeC = "open"; break;
									case 1: typeC = "read"; break;
									case 2: typeC = "write"; break;
									case 3: typeC = "close"; break;
								}
								printf("%s", typeC);
								break;
							case 2:
								printf("%s", op->startTime);
								break;
							case 3:
								printf("%f", op->duration);
								break;
							case 4:
								printf("%lld", op->size);
								break;
						}
						j += strlen(flagList[k]) + 1;
						break;
					}
				}
			} else {
				printf("%c", format[j]);
			} // end if;
		} // end while
		printf("\n");
	} // end for
}

void addOP (char *path, int type, char *startTime, double duration, unsigned long long int size, operationList *opList) {
	operation *op = malloc(sizeof(operation));
	strncpy(op->path, path, PATH_LENGTH);
	
    op->type = type;
	op->startTime = calloc(StartTime_LENGTH, sizeof(char));
	strncpy(op->startTime, startTime, StartTime_LENGTH);
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

void deleteOPList (operationList *opList) {
	operation *op;
	for (int i = 0; i < opList->size; i++) {
		op = *(opList->list + i);
		free(op->startTime);
		free(op);
	}
	free(opList->list);
	free(opList);
}

void pushOP (operation *op, operationList *opList) {
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



void testSort (operationList *opList) {
	// printOPList("aaa [type]\t[startTime]\t[duration]\t[size]\t[path]", opList);
	// printf("\n\n");
	qsort(opList->list, opList->size, sizeof(operation*), comparePath);
	printOPList("[startTime]\t[type]\t[duration]\t[size]\t[path]", opList);
}
