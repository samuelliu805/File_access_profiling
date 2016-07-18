#include "../victims/victim.h"

operationList* strace (const char *programName, const int pathType);

// private

typedef struct map {
	int d;
	char *path;
	struct map *next;
} map;

typedef struct mapList { // stack
	struct map *head;
} mapList;

char* descriptorMapper (int d, mapList *mp);
void addToMapList (int d, char *path, mapList *mp);
void deleteFromMap (int d, mapList *mp);

operationList* parser (const char *threadFileName);

unsigned long long int getNumOfBytes (operationList *opList, char *path, int type);
