#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Header* init() {

	Header* newHead = (Header*)malloc(sizeof(Header));
	newHead -> size = 0;
	newHead -> head = NULL;
	newHead -> current = NULL;

	return newHead;
}

void insert(Header* head, char* line) {

	LinkNode* newLink = (LinkNode*)malloc(sizeof(LinkNode));
	newLink -> data = (char*)malloc(sizeof(char) * strlen(line));
	strcpy(newLink->data, line);
	newLink -> next = NULL;

	if ( head->current == NULL ) {
		head->head = newLink;
		head->current = newLink;
	}
	else {
		head->current->next = newLink;
		head->current = newLink;
	}
	head->size++;
}

void displayList(Header* head) {

	LinkNode* current = head->head;
	int i = 0;
	while(current != NULL) {
		printf("Link %d - Data in link: %s\n", i++, current->data);
		current = current->next;
	}

}

void freeList(Header* head) {

	LinkNode* current = head->head;
	LinkNode* temp;
	while (current != NULL) {
		free(current->data);
		temp = current->next;
		free(current);
		current = temp;
	}
	free(head);

}

