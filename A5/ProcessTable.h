//
// Created by Oskar Aria on 4/25/2023.
//

#ifndef PROCESSTABLE_H
#define PROCESSTABLE_H

#include <time.h>

#define LINE_LENGTH 1024 // the length of the line that we can process.
#define MAX_PARAMS 10 // the max number of parameters that we can support.
#define TABLE_SIZE 100

typedef struct ProcessNode {

    int pid;
    int index;
    int params;
    struct timespec start_t;
    struct timespec end_t;
    char** command;
    struct ProcessNode* next;

} Process;

static Process** table;

void initTable();
unsigned int hash(int pid);
void insert(int pid, int index, char* com[MAX_PARAMS]);
Process* get(int pid);
void remove_proc(int pid);
void updateEnd(int pid);
void freeTable();

#endif //PROCESSTABLE_H
