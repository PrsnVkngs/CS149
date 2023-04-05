#ifndef LINKED_LIST_H 
#define LINKED_LIST_H 

typedef struct LinkNode {

	char* data;
	struct LinkNode* next;

} LinkNode;

typedef struct {

	int size;
	LinkNode* head;
	LinkNode* current;

} Header;

Header* initHead();
void insert(Header* head, char* line);
void displayList(Header* head);
void freeList(Header* head);

#endif 
