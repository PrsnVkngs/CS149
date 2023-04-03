#include "linked_list.h"

Header* init() {

	Header* newHead = (Header*)malloc(sizeof(Header));
	newHead -> size = 0;
	newHead -> head = NULL;
	newHead -> current = NULL;

	return newHead;
}

void insert(Header* head, char* line) {

	LinkNode* newLink = (LinkNode*)malloc(sizeof(LinkNode));
	newLink -> next = NULL;

}

void displayList(Header* head) {
}

void freeList(Header* head) {
}

