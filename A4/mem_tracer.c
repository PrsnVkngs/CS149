#include <stdio.h>
#include <stdlib.h>

#define LINE_LEN 1024 //give 1KB of memory for a line, the line will undoubtedly be shorter, but just in case...

typedef struct {
	char** data; // this element is private, however, since we can't declare things as private, we just have to be honorable about not accessing this variable.
	int size;
	int capacity;
} Commands;

void add(Commands* c, char* newEntry) {

	if ( c->size == myStruct->capacity) {
		c->capacity *= 2;
		c->data = realloc(c->data, c->capacity * sizeof(char*));
	}
	c->data[c->size] = newEntry;
	c->size++;

}


int main() {

	char buffer[LINE_LEN];



	return 0; // program executed completely and successfully.

}
