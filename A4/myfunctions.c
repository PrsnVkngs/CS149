#include <stdio.h>
#include <stdlib.h>

#include "myfunctions.h"

memtrace_file = NULL;

void init_memtrace() {

	memtrace_file = fopen("memtrace.out", "w");
	if (!memtrace_file) {
		fprintf(stderr, "File memtrace.out was not able to be opened for writing.\n");
		exit(EXIT_FAILURE);
	}

}

void* MALLOC(int size, char* file, int line, const char *func) {

	void* p; 
}

void* REALLOC(void* p, int size, char* file, int line, const char *func) {
}

void* FREE(int size, char* file, int line, const char *func) {
}
