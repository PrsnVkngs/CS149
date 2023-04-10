#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_stack.h"
#include "myfunctions.h"

static Stack* s = NULL;

Stack* initStack() {

// #undef malloc
	Stack* newStack = (Stack*) malloc( sizeof(Stack) );
	fprintf(stderr, "Gave memory to the stack head.\n");
	newStack-> size = 10; // hold enough for 10 functions for now.
	newStack-> top = 0; // new stack so top of it is the bottom.
	newStack-> stack = (char**) malloc( sizeof(char*) * newStack->size ); // allocate memory for the stack
	fprintf(stderr, "Gave memory to the stack data.\n");
	s = newStack;
// #define malloc(size) MALLOC(size, __FILE__, __LINE__, __func__)
	return newStack;

}



// TODO move the stack holder to the main funciton. change int memory to accept a stack pointer. finish tomorrow.

void pushStack(char* function) {

	if ( s->top >= s->size ) {
		fprintf(stderr, "Stack too big\n");
		s->stack = (char**) realloc(s->stack, (s->size+10) * sizeof(char*) );
		s->size+=10;
	}

	fprintf(stderr, "Making a new stack item\n");
	s->stack[s->top] = (char*) malloc( sizeof(char) * strlen(function) + 1 );
	strcpy(s->stack[s->top], function);
	s->top++;
}

void popStack() {

	if ( s->top < 0 ) {
		fprintf(stderr, "The stack is empty.\n");
		exit(1);
	}

	free(s->stack[s->top]);
	s->top--;

}

void displayStack() {

	for (int i = 0; i < s->top; i++) {
		printf("The item at layer %d of the stack is %s\n", i, s->stack[i]);
	}

}

void freeStack() {

	for (int i = 0; i < s->top; i++) {
		free(s->stack[i]);
	}
	free(s->stack);
	free(s);

}
