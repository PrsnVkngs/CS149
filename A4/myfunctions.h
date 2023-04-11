#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H
// we want functions to do some of the following things:
void init_memtrace(); // initialize the memory tracking file
void close_memtrace(); // close the memory tracking file
void* MALLOC(int size, char* file, int line); // Define our custom MALLOC
void* REALLOC(void* p, int size, char* file, int line); // Define our custom REALLOC
void FREE(void* p, char* file, int line); // Define our custom FREE

#define malloc(t) MALLOC(t, __FILE__, __LINE__) // rebind the base behaviors of each function to the custom functions.
#define realloc(p, t) REALLOC(p, t, __FILE__, __LINE__)
#define free(p) FREE(p, __FILE__, __LINE__)

#endif
