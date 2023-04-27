//
// Created by Oskar Aria on 4/25/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProcessTable.h"

void initTable() {
    table = (Process**)malloc(sizeof(Process*) * TABLE_SIZE);
}

unsigned int hash(int pid) {

    unsigned int value = 5381;
    while (pid > 0) {
        value += (pid%10);
        value = value << 2;
        pid /= 10;
    }

    return value % TABLE_SIZE;

}

void insert(int pid, int index, char* com[MAX_PARAMS]) {

    Process* p = (Process*)malloc(sizeof(Process));
    p->pid = pid;
    p->index = index;
    clock_gettime(CLOCK_MONOTONIC, &p->start_t);
    int items = 0;
    for(; items < MAX_PARAMS; items++) {
        if (com[items] == NULL) {
            break;
        }
    }
    p->params = items;
    for(int i = 0; i < items; i++) {
        p->command[i] = (char*)malloc(sizeof(char) * strlen(com[i]));
        strcpy(p->command[i], com[i]);
    }

    unsigned int result = hash(pid);
    printf("In insert, The hash for pid %d is %d.\n", pid, result);

    if (table[result] == NULL) {
        table[result] = p;
    }
    else {
        Process* curr = table[result];
        while(curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = p;
    }
}

Process* get(int pid) {
    unsigned int result = hash(pid);
    printf("In get, The hash for pid %d is %d.\n", pid, result);
    Process* p = table[result];
    while (p->pid != pid && p->next != NULL) {
        p = p->next;
    }
    return p;
}

void remove_proc(int pid) {
    unsigned index = hash(pid);
    if (table[index] != NULL && table[index]->next == NULL) {
        free(table[index]);
        table[index] = NULL;
    }
    else {
        Process* curr = table[index];
        Process* prev = NULL;
        while (curr->pid != pid && curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        if (prev != NULL) {
            prev->next = curr->next;
            free(curr);
        }
    }
}

void updateEnd(int pid) {

    Process* p = table[hash(pid)];
    while ( p->pid != pid && p->next != NULL ) {
        p = p->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &p->end_t);
}

void freeTable() {
    Process* curr;
    Process* next;
    for (int i = 0; i < TABLE_SIZE; i++) {
        curr = table[i];
        while (curr != NULL) {
            for ( int m = 0; m < curr->params; m++ ) {
                free(curr->command[m]);
            }
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(table);
}