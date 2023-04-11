#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mem_stack.h"
#include "myfunctions.h"

static Stack* s = NULL;

// initStack is a constructor/initializer for the function stack trace.
// it only assumes that MALLOC and memtrace_file has been initialized in myfunctions.c
// It will create a new stack pointer, initialize the struct's contents, initialize the static stack, and return it to the user.
Stack* initStack() {

	Stack* newStack = (Stack*) malloc( sizeof(Stack) ); // create the stack pointer.
	newStack-> size = 10; // hold enough for 10 functions for now.
	newStack-> top = 0; // new stack so top of it is the bottom.
	newStack-> stack = (char**) malloc( sizeof(char*) * newStack->size ); // allocate memory for the stack
	s = newStack; // set the static stack pointer to the one we just created.

	return newStack; // return the stack to the user. 

}

// pushStack pushes the string given to the stack. it assumes that initStack has been called before and it worked as intended.
// it returns nothing.
void pushStack(char* function) {

	if ( s->top >= s->size ) { // check if the top of the stack is higher than the size of the stack.
		s->size+=10; // increase the size by 10
		s->stack = (char**) realloc(s->stack, s->size * sizeof(char*) ); // reallocate memory for the stack.
	}

	s->stack[s->top] = (char*) malloc( sizeof(char) * strlen(function) + 1 ); // allocate memory at the current top of the stack for the string representing the function call.
	strcpy(s->stack[s->top], function); // copy the function name into this space.
	s->top++; // move the top up one and exit.
}

// popStack removes an item off the top of the stack. It just frees the memory and exits after moving the top down.
// It assumes that the Stack* s has been initialized. It will return nothing.
void popStack() {

	if ( s->top < 0 ) { // check if the stack is empty 
		fprintf(stderr, "The stack is empty.\n"); // if so, alert the user and exit the function.
		exit(1);
	}

	free(s->stack[s->top]); // free the memory at the top of the stack and move the top down one.
	s->top--;

}

// displayStack is a feature that allows you to display the contents of the stack without popping items off of it.
// it assumes that the Stack* s has been initialized. It will return nothing.
void displayStack() {

	for (int i = 0; i < s->top; i++) { // top from the bottom of the stack to the top
		printf("The item at layer %d of the stack is %s\n", i, s->stack[i]); // print each item on the stack on the way up.
	}
	// NOTE: we can reverse this as if it were recursive by reversing the conditions
	// ex: base case i = s->top, maintainence condition: i > 0, loop action: i--
}

// freeStack simply frees the memory given to the Stack* s. It assumes that it has been initialized and is not null.
// it doesn't return anything and just frees the memory given to the struct.
void freeStack() {

	for (int i = 0; i < s->top; i++) { // go from the bottom up, freeing the elements as you go.
		free(s->stack[i]);
	}
	free(s->stack); // additionally, free the memory given to the array itself
	free(s); // finally free the memory given to the struct.

}
