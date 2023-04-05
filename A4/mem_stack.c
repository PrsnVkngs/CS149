#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_stack.h"

Stack* initStack() {

	Stack* newStack = (Stack*) malloc( sizeof(Stack) );
	newStack-> size = 10; // hold enough for 10 functions for now.
	newStack-> top = 0; // new stack so top of it is the bottom.
	newStack-> memout = fopen("memtrace.out", "w");
	if ( memout == NULL ) {
		fprintf(stderr, "File opening of memtrace.out in mem_stack failed.\n");
		free (newStack);
		newStack = NULL;
		return newStack;
	}
	newStack-> stack = (char**) malloc ( sizeof(char*) * newStack->size ); // allocate memory for the stack.

	return newStack;

}

void pushStack(Stack* s, char* function) {

	if ( s->top == s->size ) {
		s->stack = (char**) realloc (s->stack, (s->size+10) * sizeof(char*) );
	}

	s->stack[s->top] = (char*) malloc ( sizeof(char) * strlen(function) + 1 );
	strcpy(s->stack[s->top], function);
	printCall(function);
}

void popStack(Stack* s) {
}

void printCall(char* function) {
}

void displayStack(Stack* s) {
}

void freeStack(Stack* s) {
}
