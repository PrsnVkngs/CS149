#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

void init_memtrace();
void close_memtrace();
void* MALLOC(int size, char* file, int line, const char *func);
void* REALLOC(void* p, int size, char* file, int line, const char *func);
void FREE(void* p, char* file, int line, const char *func);

#endif
