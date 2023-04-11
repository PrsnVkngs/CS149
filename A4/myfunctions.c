#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "myfunctions.h"

FILE* memtrace_file = NULL; // store a reference to a file that we will be writing to over the course of the program to track the memory usage of every malloc, realloc and free.

// init memtrace is our constructor / initializer function. It initializes the memtrace_file object.
void init_memtrace() {

	memtrace_file = fopen("memtrace.out", "w");
	// printf("memtrace file = %p\n", memtrace_file);
	if (!memtrace_file) {
		fprintf(stderr, "File memtrace.out was not able to be opened for writing.\n");
		exit(EXIT_FAILURE);
	}

}

// MALLOC is our custom implementation of malloc that copies the stdlib behavior and adds memory usage tracking.
void* MALLOC(int size, char* file, int line) {

#undef malloc // unbind MALLOC from malloc, so that the stdlib behavior is used here.

	void* p = malloc(size); // use stdlib malloc
	fprintf(memtrace_file, "File %s, line %d, allocated new memory segment at address %p to size %d\n", file, line, p, size);
	// print the memory usage tracking to the file.

#define malloc(size) MALLOC(size, __FILE__, __LINE__) // rebind it for subsequent calls.
	return p; // return the pointer to the user.

}

// REALLOC is our custom implementation of realloc that copies the stdlib behavior and adds memory usage tracking.
void* REALLOC(void* p, int size, char* file, int line) {

#undef realloc // unbind REALLOC so that the stdlib behavior is used.
	void* new_p = realloc(p, size); // use stdlib realloc
	fprintf(memtrace_file, "File %s, line %d, reallocated new memory segment at address %p to new size %d\n", file, line, new_p, size); // print the memory usage to the memtrace file.

#define realloc(p, t) REALLOC(p, t, __FILE__, __LINE__) // rebind it for subsequent calls.
	return new_p; // return the address of the new memory.

}

// FREE is our custom implementation of free that copies the stdlib behavior and adds memory usage tracking.
void FREE(void* p, char* file, int line) {
#undef free // unbind FREE so that the stdlib behavior is used.

	fprintf(memtrace_file, "File %s, line %d deallocated memory segment at address %p\n", file, line, p); // print out which address is having its memory de-allocated.
	free(p); // free aforementioned memory.

#define free(p) FREE(p, __FILE__, __LINE__) // rebind FREE for subsequent calls.

}

// close memtrace basically does the opposite of init_memtrace. it is a destructor and closes the memtrace_file in this source file.
void close_memtrace() {

	fclose(memtrace_file);

}

