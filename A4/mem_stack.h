#ifndef MEM_STACK_H
#define MEM_STACK_H

typedef struct {

	char** stack;
	int size;
	int top;

} Stack;

Stack* initStack();
void pushStack(Stack* s);
void popStack(Stack* s);
void displayStack(Stack* s);
void freeStack(Stack* s);

#endif
