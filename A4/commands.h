#ifndef COMMANDS_H
#define COMMANDS_H 

typedef struct { // define a new struct for the array. 
	char** data; // the contents of the array
	int size; // the current number of elements in the array
	int capacity; // the total capacity of the array
} Commands;

Commands* makeCommands(); // constructor/initializer function
void add(Commands* c, char* newEntry); // add a string to the given struct
void displayCommands(Commands* c); // display the contents of the array
void freeCom(Commands* c); // free the memory given to the struct and the array 

#endif 
