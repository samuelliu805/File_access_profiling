#define PATH_LENGTH 100

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
