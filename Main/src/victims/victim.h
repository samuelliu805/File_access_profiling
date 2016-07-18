#define PATH_LENGTH 100
#define StartTime_LENGTH 15

typedef struct operation { // linked list
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
void printOPList_0 (operationList *opList);

void addOP (char *path, int type, char *startTime, double duration, unsigned long long int size, operationList *opList);
operationList* createOPList ();
void deleteOPList ();
void pushOP (operation *op, operationList *opList);


unsigned long long int totalSize (operationList *opList, char *path, int type);

/*

typedef struct operation { // linked list
	int type; // 0: open; 1: read; 2: write; 3: close
	char *startTime;
	double duration;
	unsigned long long int size; // in Byte; -1 if type = 0 || 3
	struct operation *next;
	// int thread;
} operation;

typedef struct victim { // files that had been accessed
	char path[PATH_LENGTH];
	// int fileDescriptor; // tempID
	struct operation *first;
} victim;

typedef struct priorityQ { // queue
	int size;
	int length;
	struct victim *list; // array
} priorityQ;

priorityQ* createQ ();
void deleteQ ();

void pushOperation (
	char *path,
	const int type,
	char *startTime,
	const double duration,
	unsigned long long int size
);
void deleteOperation ();

*/