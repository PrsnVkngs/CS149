#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#undef malloc
#undef realloc
#undef free

#include "mem_stack.h"

void init_memtrace();
void close_memtrace();
Stack* getStack();
void* MALLOC(int size, char* file, int line);
void* REALLOC(void* p, int size, char* file, int line);
void FREE(void* p, char* file, int line);

#define malloc(t) MALLOC(t, __FILE__, __LINE__)
#define realloc(p, t) REALLOC(p, t, __FILE__, __LINE__)
#define free(p) FREE(p, __FILE__, __LINE__)

#endif
