#ifndef COMMANDS_H
#define COMMANDS_H 

typedef struct {
	char** data; // this element is private, however, since we can't declare things as private, we just have to be honorable about not accessing this variable.
	int size;
	int capacity;
} Commands;

Commands* makeCommands();
void add(Commands* c, char* newEntry);
void displayCommands(Commands* c);
void freeCom(Commands* c);

#endif 
