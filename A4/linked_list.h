#ifndef LINKED_LIST.H
#define LINKED_LIST.H

typedef struct {

	char* data;
	LinkNode* next;

} LinkNode;

typedef struct {

	int size;
	LinkNode* head;
	LinkNode* current;

} Header;

Header* init();
void insert(Header* head, char* line);
void displayList(Header* head);
void freeList(Header* head);

#endif
