#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

void init_memtrace();
void close_memtrace();
void* MALLOC(int size, char* file, int line, const char *func);
void* REALLOC(void* p, int size, char* file, int line, const char *func);
void FREE(void* p, char* file, int line, const char *func);

#define malloc(t) MALLOC(t, __FILE__, __LINE__, __func__)
#define realloc(p, t) REALLOC(p, t, __FILE__, __LINE__, __func__)
#define free(p) FREE(p, __FILE__, __LINE__, __func__)

#endif
