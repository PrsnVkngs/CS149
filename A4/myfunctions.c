#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "myfunctions.h"

FILE* memtrace_file = NULL;

void init_memtrace() {

	memtrace_file = fopen("memtrace.out", "w");
	// printf("memtrace file = %p\n", memtrace_file);
	if (!memtrace_file) {
		fprintf(stderr, "File memtrace.out was not able to be opened for writing.\n");
		exit(EXIT_FAILURE);
	}

}

void* MALLOC(int size, char* file, int line) {

#undef malloc
	// printf("Entered malloc\n");
	void* p = malloc(size);
	// printf("Allocated memory for the new pointer\n");
	fprintf(memtrace_file, "File %s, line %d, allocated new memory segment at address %p to size %d\n", file, line, p, size);
	// fprintf(stderr, "File %s, line %d allocated mem at %p of size %d\n", file, line, p, size);

#define malloc(size) MALLOC(size, __FILE__, __LINE__)
	return p;

}

void* REALLOC(void* p, int size, char* file, int line) {

#undef realloc
	void* new_p = realloc(p, size);
	fprintf(memtrace_file, "File %s, line %d, reallocated new memory segment at address %p to new size %d\n", file, line, new_p, size);
	// fprintf(stderr, "File %s, line %d, reallocated memory at %p size %d\n", file, line, new_p, size);

#define realloc(p, t) REALLOC(p, t, __FILE__, __LINE__)
	return new_p;

}

void FREE(void* p, char* file, int line) {
#undef free

	fprintf(memtrace_file, "File %s, line %d deallocated memory segment at address %p\n", file, line, p);
	free(p);
	// fprintf(stderr, "Freed memory at line %d\n", line);

#define free(p) FREE(p, __FILE__, __LINE__)

}

void close_memtrace() {

	fclose(memtrace_file);

}

// #undef malloc
// #define malloc(size) MALLOC(size, __FILE__, __LINE__, __func__)

// #undef realloc
// #define realloc(p, size) REALLOC(p, size, __FILE__, __LINE__, __func__)

// #undef free
// #define free(p) FREE(p, __FILE__, __LINE__, __func__)

