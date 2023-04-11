#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "mem_stack.h"
#include "myfunctions.h"

// makeCommands doesn't have any previous assumptions other than that MALLOC has been defined and bound properly.
// it creates a Commands struct pointer, initializes it, and returns it.
Commands* makeCommands() {

	pushStack("makeCommands"); // push the function name onto the stack
	Commands* com = (Commands*)malloc(sizeof(Commands)); // create a new Commands struct pointer
	com -> size = 0;
	com -> capacity = 10;
	com -> data = (char**)malloc(sizeof(char*) * com->capacity); // initialize the contents of the struct.

	return com; // return the pointer.

}

// Add simply adds the new command entry that we want to place into the given Commands struct.
// We assume that newEntry is a valid C-string with a null terminator. It returns nothing.
void add(Commands* c, char* newEntry) {

	pushStack("add"); // push the function name onto the stack.
	if ( c->size == c->capacity) { // make sure that the capacity hasn't been reached.
		c->capacity *= 1.5;
		c->data = (char**)realloc(c->data, c->capacity * sizeof(char*)); // if so, resize it.
	}
	c->data[c->size] = (char*)malloc(strlen(newEntry) * sizeof(char) + 1); // otherwise just allocate memory in the array.
	strcpy(c->data[c->size], newEntry); // copy the string to this new memory
	c->size++; // increment the size and exit the function

}

// displayCommands is a debugging function as well as provides the ability to display the contents of the commands array.
// it assumes that c has been initialized and is a valid Commands pointer. It doesn't return anything.
void displayCommands(Commands* c) {

	pushStack("displayCommands"); // push the function name onto the stack.
	for (int i = 0; i < c->size; i++) { // start from the first item to the last,
		printf("Line %d - Command from Array: %s\n", i, c->data[i]); // print out the index and the value.
	}

}

// This function assumes that the passed in Commands struct has been initialized and is not an invalid pointer.
void freeCom(Commands* c) {

	pushStack("freeCom"); // push the function name onto the stack.
	for (int i = 0; i < c->size; i++) { // from the start of the array to the last item...
		free(c->data[i]); // free the memory given to each item in the list.
	}
	free(c->data); // free the array itself.
	free(c); // finally free the struct itself and exit.

}
