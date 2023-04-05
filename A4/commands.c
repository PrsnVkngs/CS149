#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "myfunctions.h"

Commands* makeCommands() {

	Commands* com = (Commands*)malloc(sizeof(Commands));
	com -> size = 0;
	com -> capacity = 10;
	com -> data = (char**)malloc(sizeof(char*) * com->capacity);

	return com;

}

// Add simply adds the new command entry that we want to place into the given Commands struct.
// We assume that newEntry is a valid C-string with a null terminator. It returns nothing.
void add(Commands* c, char* newEntry) {

	if ( c->size == c->capacity) {
		c->capacity *= 1.5;
		c->data = (char**)realloc(c->data, c->capacity * sizeof(char*));
	}
	c->data[c->size] = (char*)malloc(strlen(newEntry) * sizeof(char) + 1);
	strcpy(c->data[c->size], newEntry);
	c->size++;

}

void displayCommands(Commands* c) {

	for (int i = 0; i < c->size; i++) {
		printf("Line %d - Command from Array: %s\n", i, c->data[i]);
	}

}

// This function assumes that the passed in Commands struct has been initialized and is not an invalid pointer.
void freeCom(Commands* c) {

	for (int i = 0; i < c->capacity; i++) { // TODO this might throw an error when testing, depending on add implementation.
		free(c->data[i]);
	}
	free(c->data);
	free(c);

}
