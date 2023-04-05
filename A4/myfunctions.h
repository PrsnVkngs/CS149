#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

FILE* memtrace_file;

void init_memtrace();
void* MALLOC(int size, char* file, int line, const char *func);
void* REALLOC(void* p, int size, char* file, int line, const char *func);
void* FREE(int size, char* file, int line, const char *func);

#endif
