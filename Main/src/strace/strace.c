/*

please run the fellowing command and place thread.txt under the Main folder

strace -tt -T -o thread.txt PROGRAM_PATH

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../victims/victim.h"

#include "strace.h"
// #include "stracePrivate.h"

#define COMMAND_LENGTH 200

const int TESTING = 1;

const int lineLength = 200;

/* no longer necessary
operationList* strace (const char *programName, const int pathType) {
	
	char command[COMMAND_LENGTH] = "cd temp; strace -tt -T -o thread.txt ";
	int i = -1, j = 0;
	
	while (command[++i] != 0);
	if (pathType != 0) {
		command[i++] = '.';
		command[i++] = '.';
		command[i++] = '/';
	}
	while (i < COMMAND_LENGTH && *(programName + j) != 0) { command[i++] = *(programName + j++); }
	command[i] = '\n';
	// system("cd temp; strace -tt -T -o thread.txt PROGRAM_PATH");
	system(command);
	return parser("temp/thread.txt");
} */

// private

// file fileDescriptor mapper
// doesn't avoid duplicates
char* descriptorMapper (int d, mapList *mp) {
	map *prev = mp->head, *current;
	while (prev->next != NULL) {
		current = prev->next;
		if (d == current->d) return current->path;
		prev = prev->next;
	}
	return NULL;
}

char* update (int d, int update, mapList *mp) {
	map *prev = mp->head, *current;
	while (prev->next != NULL) {
		current = prev->next;
		if (d == current->d){
			current->d = update;
			return current->path;
		}
		prev = prev->next;
	}
	return NULL;
}


void addToMapList (int d, char *path, mapList *mp) {
	map *m = malloc(sizeof(map));
	m->d = d;
	m->path = path;
	m->next = mp->head->next;
	mp->head->next = m;
}

void deleteFromMap (int d, mapList *mp) {
	map *prev = mp->head, *current;
	while (prev->next != NULL) {
		current = prev->next;
		if (d == current->d) {
			prev->next = current->next;
			free(current->path);
			free(current);
			return;
		}
		prev = prev->next;
	}
}

// end file fileDescriptor mapper

// parser

operationList* parser (const char *threadFileName) {
	
	operationList *opList = createOPList();
	
	FILE *f = fopen(threadFileName, "r");
	
	char *line = malloc(sizeof(char) * lineLength);
	
	int pathLength = 100;
	int startTimeLength = 15;
	
	char *startTime;
	int type;
	int fileDescriptor,updatednumber;
	char *path;
	unsigned long long int size;
	double duration;
	
	mapList *mp = malloc(sizeof(mapList));
	mp->head = malloc(sizeof(map));
	mp->head->next = NULL;
	
	if (TESTING) {
		type = -1;
		type++;
	}
	while (fgets(line, lineLength, f) != NULL) {
	
		startTime = (char*) calloc(startTimeLength + 1, sizeof(char));
		size = -1;
		
		int i = 16;
		
		if (strncmp((line + i), "open", 4) == 0) {
			type = 0;
			path = (char*) calloc(pathLength, sizeof(char));
			sscanf(line, "%[^ ] %*[^\"]\"%[^\"]\"%*[^=]= %d <%lf>", startTime, path, &fileDescriptor, &duration);
			addToMapList (fileDescriptor, path, mp);
		} else if (strncmp((line + i), "read", 4) == 0) {
			type = 1;
			sscanf(line, "%[^ ] %*[^(](%d,%*[^=]= %lld <%lf>", startTime, &fileDescriptor, &size, &duration);
		} else if (strncmp((line + i), "write", 5) == 0) {
			type = 2;
			sscanf(line, "%[^ ] %*[^(](%d,%*[^=]= %lld <%lf>", startTime, &fileDescriptor, &size, &duration);
		} else if (strncmp((line + i), "close", 5) == 0) {
			type = 3;
			sscanf(line, "%[^ ] %*[^(](%d)%*[^<]<%lf>", startTime, &fileDescriptor, &duration);
		} else if (strncmp((line + i), "dup2", 4) == 0) {
			sscanf(line, "%[^ ] %*[^(](%d, %d)%*[^<]<%lf>", startTime, &fileDescriptor,&updatednumber, &duration);
			path = update(fileDescriptor,updatednumber, mp);
		} else {
			type = 4;
		}
		if (type != 0) {
			path = descriptorMapper(fileDescriptor, mp);
			if (path == NULL) path = "NULL";
		}
		
		if (type != 4) {
			addOP (path, type, startTime, duration, size, opList);
		}
		
		if (type == 3) deleteFromMap(fileDescriptor, mp);
		
		free(startTime);
		// free(path); // free from deleteFromMap()
		
		for (int i = 0; i < lineLength; i++) *(line + i) = 0;
		
	} // end while
	
	free(line);
	
	free(mp->head);
	free(mp);
	fclose(f);
	return opList;
	
}

// end parser

unsigned long long int getNumOfBytes (operationList *opList, char *path, int type) {
	return totalSize (opList, path, type);
}

void deleteOPList_0 (operationList *opList) {
	deleteOPList(opList);
}
