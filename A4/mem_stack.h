#ifndef MEM_STACK_H
#define MEM_STACK_H

typedef struct { // define a struct to hold the contents of the function stack trace.

	char** stack; // create an array to hold each string
	int size; // track the size of the stack
	int top; // track the top of the stack as well.

} Stack;

Stack* initStack(); // function to initialize the Stack.
void pushStack(char* function); // we want a function to push the given string to the stack
void popStack(); // we want to be able to pop items off the stack too
void displayStack(); // we also want to to be able to display the stack without popping items off of it.
void freeStack(); // we want to be able to free the memory given to the stack as well.

#endif
