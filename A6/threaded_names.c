#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 31
#define MAX_NAMES 100

//thread mutex lock for access to the log index
//TODO you need to use this mutexlock for mutual exclusion
//when you print log messages from each thread
pthread_mutex_t message_lock = PTHREAD_MUTEX_INITIALIZER;
//thread mutex lock for critical sections of allocating THREAD_DATA
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t t_data_lock = PTHREAD_MUTEX_INITIALIZER;
//thread mutex lock for access to the name counts data structure
//TODO you need to use this mutexlock for mutual exclusion
pthread_mutex_t insert_lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_runner(void *);
void log_print(char* message, pthread_t threadId);

pthread_t tid1, tid2;
//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
typedef struct THREAD_DATA_STRUCT {
    pthread_t creator;
} THREAD_DATA;

THREAD_DATA *p = NULL;
//variable for indexing of messages by the logging function.
int logIndex = 0;
int *logip = &logIndex;

typedef struct {
    char key[MAX_NAME_LEN];
    int value;
} NameEntry;

typedef struct {
    NameEntry *entries;
} HashSet;

unsigned int hash_name(char *name) {
    unsigned int hash = 5381;
    int c;

    while ((c = *name++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % MAX_NAMES;
}

HashSet* create_hash_set() {
    HashSet *set = (HashSet *)malloc(sizeof(HashSet));
    set->entries = (NameEntry *)calloc(MAX_NAMES, sizeof(NameEntry));
    return set;
}

void put(HashSet *set, char *name) {
    unsigned int index = hash_name(name);

    while (set->entries[index].value != 0) {
        if (strcmp(set->entries[index].key, name) == 0) {
            set->entries[index].value++;
            return;
        }
        index = (index + 1) % MAX_NAMES;
    }

    strcpy(set->entries[index].key, name);
    set->entries[index].value += 1;
}

void displayResults(HashSet *set) {
    for (int i = 0; i < MAX_NAMES; i++) {
        if (set->entries[i].value != 0) {
            printf("%s\t-\t%d\n", set->entries[i].key, set->entries[i].value);
        }
    }
}

void freeSet(HashSet *set) {
    free(set->entries);
    free(set);
}

/*********************************************************
// function main
*********************************************************/

HashSet* set = NULL;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    set = create_hash_set();

//TODO similar interface as A2: give as command-line arguments three filenames of numbers (the numbers in the files are newline-separated).
    printf("create first thread\n");
    pthread_create(&tid1, NULL, thread_runner, argv[1]);
    printf("create second thread\n");
    pthread_create(&tid2, NULL, thread_runner, argv[2]);
    printf("wait for first thread to exit\n");
    pthread_join(tid1, NULL);
    printf("first thread exited\n");
    printf("wait for second thread to exit\n");
    pthread_join(tid2, NULL);
    printf("second thread exited\n");
//TODO print out the sum variable with the sum of all the numbers

    displayResults(set);
    freeSet(set);

    exit(0);
}//end main
/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
void* thread_runner(void* x) {
    pthread_t me;
    me = pthread_self();
    printf("This is thread %lu (p=%p)\n", me, p);
    pthread_mutex_lock(&t_data_lock); // critical section starts
    if (p == NULL) {
        p = (THREAD_DATA *) malloc(sizeof(THREAD_DATA));
        p->creator = me;
    }
    pthread_mutex_unlock(&t_data_lock); // critical section ends
    if (p == NULL || p->creator != me) {
        printf("This is thread %lu and I can access the THREAD_DATA %p\n", me, p);
    } else {
        printf("This is thread %lu and I created THREAD_DATA %p\n", me, p);
    }

    FILE *nameFile = fopen(x, "r");

    // file open critical section
    pthread_mutex_lock(&message_lock);
    char message[50];
    sprintf(message, "I have opened this file: %s\n", (char*)x);
    log_print(message, me);
    pthread_mutex_unlock(&message_lock);

    char line[MAX_LINE_LEN];
    char name[MAX_NAME_LEN + 1];
    int line_num = 1;

    if (nameFile == NULL) {
        pthread_exit(NULL);
    }

    while (fgets(line, MAX_LINE_LEN, nameFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            fprintf(stderr, "Warning - Line %d is empty.\n", line_num);
            continue;
        }

        if (sscanf(line, "%30[^\n]", name) == 1) {
            pthread_mutex_lock(&insert_lock);
            put(set, name);
            pthread_mutex_unlock(&insert_lock);
        } else {
            printf("error reading line %d\n", line_num);
        }
        line_num++;
    }

    fclose(nameFile);

/**
* //TODO implement any thread name counting functionality you need.
* Assign one file per thread. Hint: you can either pass each argv filename as a
thread_runner argument from main.
* Or use the logIndex to index argv, since every thread will increment the
logIndex anyway
* when it opens a file to print a log message (e.g. logIndex could also index
argv)....
* //Make sure to use any mutex locks appropriately
*/
// TODO use mutex to make this a start of a critical section
// critical section starts
    pthread_mutex_lock(&t_data_lock);
    if (p != NULL && p->creator == me) {
	char buff[75];
	sprintf(buff, "This is thread %lu and I delete THREAD_DATA\n", me);
	log_print(buff, me);
/**
* TODO Free the THREADATA object.
* Freeing should be done by the same thread that created it.
* See how the THREAD_DATA was created for an example of how this is done.
*/

        free(p);
        p = NULL;

    } else {
	char buff[75];
	sprintf(buff, "This is thread %lu and I can access the THREAD_DATA", me);
	log_print(buff, me);
    }
    pthread_mutex_unlock(&t_data_lock);
// TODO critical section ends
    pthread_exit(NULL);
//return NULL;
    return NULL;
}//end thread_runner

// This is a critical section piece of code, need a mutex lock before and after it.
void log_print(char* message, pthread_t threadId) {

    time_t rawTime;
    struct tm *timeInfo;
    char buffer[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(buffer, sizeof(buffer), "%d/%m/%Y %I:%M:%S %p", timeInfo);

    printf("Logindex %d, thread %lu, PID %d, %s: %s\n", logIndex++, threadId, (int) getpid(), buffer, message);

}
