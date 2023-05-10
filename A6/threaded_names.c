#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 31
#define MAX_NAMES 100
#define NUM_THREADS 2

typedef struct {
    char key[MAX_NAME_LEN];
    int value;
} NameEntry;

typedef struct {
    NameEntry *entries;
} HashSet;

typedef struct {
    char *filename;
    int thread_id;
    HashSet *set;
} ThreadData;

unsigned int hash_name(char *name) {
    unsigned int hash = 5381;
    int c;

    while ((c = *name++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % MAX_NAMES;
}

HashSet *create_hash_set() {
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

pthread_mutex_t logMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t setMutex = PTHREAD_MUTEX_INITIALIZER;
int logIndex = 1;

void logprint(char *message) {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d/%m/%Y %I:%M:%S %p", timeinfo);

    printf("Logindex %d, thread %ld, PID %d, %s: %s\n", logIndex, pthread_self(), getpid(), buffer, message);
}

void *processFile(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    FILE *nameFile;
    char line[MAX_LINE_LEN];
    char name[MAX_NAME_LEN + 1];
    int line_num = 1;

    logprint(data->logMutex, data->logIndex, "opened file", data->filename);

    nameFile = fopen(data->filename, "r");
    if (nameFile == NULL) {
        logprint(data->logMutex, data->logIndex, "failed to open file", data->filename);
        pthread_exit(NULL);
    }

    while (fgets(line, MAX_LINE_LEN, nameFile) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            fprintf(stderr, "Warning - Line %d is empty.\n", line_num);
            continue;
        }

        if (sscanf(line, "%30[^\n]", name) == 1) {
            pthread_mutex_lock(data->countMutex);
            put(data->set, name);
            pthread_mutex_unlock(data->countMutex);
        } 
	else {
            printf("error reading line %d\n", line_num);
        }
        line_num++;
    }

    fclose(nameFile);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    pthread_t thread1, thread2;
    pthread_mutex_t countMutex, logMutex, threadDataMutex;
    pthread_mutex_init(&countMutex, NULL);
    pthread_mutex_init(&logMutex, NULL);
    pthread_mutex_init(&threadDataMutex, NULL);

    int logIndex = 0;
    HashSet *set = create_hash_set();

    ThreadData data1 = {argv[1], set, &countMutex, &logMutex, &threadDataMutex, &logIndex};
    ThreadData data2 = {argv[2], set, &countMutex, &logMutex, &threadDataMutex, &logIndex};

    pthread_create(&thread1, NULL, processFile, (void *)&data1);
    pthread_create(&thread2, NULL, processFile, (void *)&data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    displayResults(set);

    freeSet(set);

    pthread_mutex_destroy(&countMutex);
    pthread_mutex_destroy(&logMutex);
    pthread_mutex_destroy(&threadDataMutex);

    return 0;
}

