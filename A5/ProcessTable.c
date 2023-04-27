//
// Created by Oskar Aria on 4/25/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ProcessTable.h"

void initTable() {
    table = (Process**)calloc(TABLE_SIZE, sizeof(Process*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }
}

unsigned int hash(int pid) {
    return pid % TABLE_SIZE;
}

void insert(int pid, int index, char* com[MAX_PARAMS]) {

    unsigned int result = hash(pid);
    printf("In insert, The hash for pid %d is %d.\n", pid, result);

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

    // Allocate memory for the command array
    p->command = (char**)malloc(sizeof(char*) * (items+1));
    for (int i = 0; i < items; i ++ ) {
        p->command[i] = NULL;
    }

    for(int i = 0; i < items; i++) {
        printf("Allocated memory for item %d\n", i);
        p->command[i] = (char*)malloc(sizeof(char) * strlen(com[i]) + 1);
        strcpy(p->command[i], com[i]);
    }
    p->command[items] = NULL;
    printf("terminated list\n");

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
    printf("Inserted the item into the list.\n");
}


Process* get(int pid) {
    unsigned int result = hash(pid);
    printf("In get, The hash for pid %d is %d.\n", pid, result);
    Process* p = table[result];

    // Check if the first element in the list is NULL
    if (p == NULL) {
        return NULL;
    }

    // Traverse the list and check for NULL pointers
    while (p->pid != pid) {
        if (p->next == NULL) {
            // Process with the given PID was not found
            return NULL;
        }
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
    unsigned int result = hash(pid);
    Process* p = table[result];

    // Check if the first element in the list is NULL
    if (p == NULL) {
        printf("Error: Process with PID %d not found.\n", pid);
        return;
    }

    // Traverse the list and check for NULL pointers
    while (p->pid != pid) {
        if (p->next == NULL) {
            // Process with the given PID was not found
            printf("Error: Process with PID %d not found.\n", pid);
            return;
        }
        p = p->next;
    }

    clock_gettime(CLOCK_MONOTONIC, &p->end_t);
}
// end updateEnd


void freeTable() {
    Process* curr;
    Process* next;
    for (int i = 0; i < TABLE_SIZE; i++) {
        curr = table[i];
        while (curr != NULL) {
            for ( int m = 0; m < curr->params; m++ ) {
                free(curr->command[m]);
            }
            free(curr->command);
            next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(table);
}