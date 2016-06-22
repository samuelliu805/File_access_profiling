#include <stdio.h>
#include <stdlib.h>

#include "victim.h"

priorityQ* createQ () {
	priorityQ *q = malloc(sizeof(priorityQ));
	q->size = 0;
	q->length = 0;
	q->list = NULL;
	return q;
}

void deleteQ () {}

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
