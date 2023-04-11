#ifndef LINKED_LIST_H 
#define LINKED_LIST_H 

typedef struct LinkNode { // define a struct for each node in the list.

	char* data; // string for the command that we will store.
	struct LinkNode* next; // reference to the next node.

} LinkNode;

typedef struct { // define a struct for the header/tracker of the list.

	int size; // the number of nodes in the list.
	LinkNode* head; // reference to the head of the list
	LinkNode* current; // reference to the tail of the list

} Header;

Header* initHead(); // initializer / constructor for the head of the list.
void insert(Header* head, char* line); // function to insert into the list/
void displayList(Header* head); // function to display the list 
void freeList(Header* head); // free the memory given to the list.

#endif 
