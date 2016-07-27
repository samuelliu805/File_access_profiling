#define PATH_LENGTH 1000
#define StartTime_LENGTH 15

typedef struct operation {
	char path[PATH_LENGTH];
	int type; // 0: open; 1: read; 2: write; 3: close
	char *startTime;
	double duration;
	unsigned long long int size; // in Byte; -1 if type = 0 || 3
	// struct operation *next;
	// int thread;
} operation;

typedef struct operationList { // array
	int size;
	int length;
	struct operation **list;
} operationList;

void cpyStr (char *a, int aL, char *b, int bL);
int compareStr (char* a, int l1, char* b, int l2);
void printOPList (char *format, operationList *opList, char *fileName);

int compareFunc (const void *s1, const void *s2);
int comparePath (const void *s1, const void *s2);
int compareType (const void *s1, const void *s2);
int compareStartTime (const void *s1, const void *s2);
int compareDuration (const void *s1, const void *s2);
int compareSize (const void *s1, const void *s2);
int compareEqual (const void *s1, const void *s2);

void addOP (char *path, int type, char *startTime, double duration, unsigned long long int size, operationList *opList);
operationList* createOPList ();
void deleteOPList (operationList *opList);
void pushOP (operation *op, operationList *opList);


unsigned long long int totalSize (operationList *opList, char *path, int type);


// int (*pickCompareFunc())(const *void, const *void);
int (*pickCompareFunc())(const void *s1, const void *s2);
void testSort (operationList *opList, int *priority, int priorityLen);
