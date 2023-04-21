#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Process {

	int pid;
	int index;
	char* command;
	int startTime;
	int endTime; // TODO replace these if there is a more appropriate type in time.h

}; 

typedef struct HashTable {

	int size;
	int capacity;
	Process** processes;

};

void initTable();
void newProcess(int pid, int index);
void hash();

#endif
