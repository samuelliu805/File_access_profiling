#include <stdio.h>
#include <stdlib.h>

#include "../victims/victim.h"

#include "strace.h"
#include "stracePrivate.h"

#define COMMAND_LENGTH 200

const int TESTING = 1;

const int lineLength = 200;

void strace (const char *programName, const int pathType) {
	
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
	parser("temp/thread.txt");
}

// private

void parser (const char *threadFileName) {
	
	FILE *f = fopen(threadFileName, "r");
	
	char *line = malloc(sizeof(char) * lineLength);
	
	int pathLength = 200;
	int startTimeLength = 15;
	
	char *startTime;
	int type;
	int fileDescriptor;
	char *path;
	unsigned long long int size;
	double duration;
	
	if (TESTING) {
		type = -1;
		type++;
	}
	
	while (fgets(line, lineLength, f) != NULL) {
		
		startTime = (char*) calloc(startTimeLength, sizeof(char));
		path = (char*) calloc(pathLength, sizeof(char));
		
		int i = 16;
		
		if (
			*(line + i + 0) == 'o' &&
			*(line + i + 1) == 'p' &&
			*(line + i + 2) == 'e' &&
			*(line + i + 3) == 'n'
		) {
			type = 0;
			sscanf(line, "%[^ ] %*[^\"]\"%[^\"]\"%*[^=]= %d <%lf>", startTime, path, &fileDescriptor, &duration);
			if (TESTING) {
				printf("%s", line);
				printf("open (%d)\n", fileDescriptor);
				printf("\n");
			}
		} else if (
			*(line + i + 0) == 'r' &&
			*(line + i + 1) == 'e' &&
			*(line + i + 2) == 'a' &&
			*(line + i + 3) == 'd'
		) {
			type = 1;
			sscanf(line, "%[^ ] %*[^(](%d,%*[^=]= %lld <%lf>", startTime, &fileDescriptor, &size, &duration);
		} else if (
			*(line + i + 0) == 'w' &&
			*(line + i + 1) == 'r' &&
			*(line + i + 2) == 'i' &&
			*(line + i + 3) == 't' &&
			*(line + i + 4) == 'e'
		) {
			type = 2;
			sscanf(line, "%[^ ] %*[^(](%d,%*[^=]= %lld <%lf>", startTime, &fileDescriptor, &size, &duration);
		} else if (
			*(line + i + 0) == 'c' &&
			*(line + i + 1) == 'l' &&
			*(line + i + 2) == 'o' &&
			*(line + i + 3) == 's' &&
			*(line + i + 4) == 'e'
		) {
			type = 3;
			sscanf(line, "%[^ ] %*[^(](%d)%*[^<]<%lf>", startTime, &fileDescriptor, &duration);
			if (TESTING) {
				printf("%s", line);
				printf("close (%d)\n", fileDescriptor);
				printf("\n");
			}
		} else {
			type = 4;
		}
		
		// ...
		
		// free(startTime);
		// free(path);
		for (int i = 0; i < lineLength; i++) *(line + i) = 0;
	} // end while
	
	free(line);
	
}
