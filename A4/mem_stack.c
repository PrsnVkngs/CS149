#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_stack.h"
#include "myfunctions.h"

Stack* initStack() {

	Stack* newStack = (Stack*) malloc( sizeof(Stack) );
	newStack-> size = 10; // hold enough for 10 functions for now.
	newStack-> top = 0; // new stack so top of it is the bottom.
	newStack-> stack = (char**) malloc( sizeof(char*) * newStack->size ); // allocate memory for the stack

	return newStack;

}

static Stack* memory_stack;
// TODO move the stack holder to the main funciton. change int memory to accept a stack pointer. finish tomorrow.
void makeStack() {

	memory_stack = initStack();

}

Stack* getStack() {

	return memory_stack;

}

void pushStack(Stack* s, const char* function) {

	if ( s->top == s->size ) {
		s->stack = (char**) realloc(s->stack, (s->size+10) * sizeof(char*) );
	}

	s->stack[s->top] = (char*) malloc( sizeof(char) * strlen(function) + 1 );
	strcpy(s->stack[s->top], function);
	s->top++;
}

void popStack(Stack* s) {

	if ( s->top < 0 ) {
		fprintf(stderr, "The stack is empty.\n");
		exit(1);
	}

	free(s->stack[s->top]);
	s->top--;

}

void displayStack(Stack* s) {

	for (int i = 0; i < s->top; i++) {
		printf("The item at layer %d of the stack is %s\n", i, s->stack[i]);
	}

}

void freeStack(Stack* s) {

	for (int i = 0; i < s->top; i++) {
		free(s->stack[i]);
	}
	free(s->stack);
	free(s);

}
