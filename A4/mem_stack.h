#ifndef MEM_STACK_H
#define MEM_STACK_H

typedef struct {

	char** stack;
	int size;
	int top;

} Stack;

Stack* initStack();
Stack* getStack();
void pushStack(char* function);
void popStack();
void displayStack();
void freeStack();

#endif
