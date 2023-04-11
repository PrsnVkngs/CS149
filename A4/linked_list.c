#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "mem_stack.h"
#include "myfunctions.h"

// initHead is an initializer/constructor function. It makes no prior assumptions other than that MALLOC and memtrace_file has been initialized.
// The function will create a new Head node for a linked list, initialize the struct's contents and return the pointer to the caller.
// the head node is in reality a dummy node to track the head and tail of the list.
Header* initHead() {

	pushStack("initHead"); // push the function name to the stack
	Header* newHead = (Header*)malloc(sizeof(Header)); // allocate some memory for the head node.
	newHead -> size = 0; 
	newHead -> head = NULL;
	newHead -> current = NULL; // initialize the size, head and tail(current) to their appropriate values.

	return newHead; // return the pointer to the caller.
}

// Insert assumes that the head variable points to a valid pointer, and that char is also a valid C-string.
// The function will use the head pointer to quickly insert the new node it creates to the tail of the list using the current reference.
void insert(Header* head, char* line) {

	pushStack("insert"); // push the function name to the stack
	LinkNode* newLink = (LinkNode*)malloc(sizeof(LinkNode)); // create a new link node pointer.
	newLink -> data = (char*)malloc(sizeof(char) * strlen(line) + 1); // allocate some memory inside the link node for the string.
	strcpy(newLink->data, line); // copy the string to the struct.
	newLink -> next = NULL; // initialize the next pointer to null since this is the new tail of the list.

	if ( head->current == NULL ) { // base case: size = 0
		head->head = newLink;
		head->current = newLink; // head = tail = newLink which contains line, since the size is 1 after this.
	}
	else {
		head->current->next = newLink; // add the new node to the current end of the list.
		head->current = newLink; // move the tail pointer of the list to to the new link.
	}
	head->size++; // increment the size and exit.
}

// displayList is a debugging function as well as providing the ability to print the contents of the list given.
// it assumes that the passed list is a valid Header pointer. it returns nothing.
// the function simply loops through each link of the node, printing the value that is in each node.
void displayList(Header* head) {

	pushStack("displayList"); // push the function name to the stack
	LinkNode* current = head->head; // make a temporary variable to hold the front of the list.
	int i = 0; // initialize a temp counter so the function can track which link we are looking at.
	while(current != NULL) { // exit condition: current is at the end of the list.
		printf("Link %d - Data in link: %s\n", i++, current->data); // print the data inside the link.
		current = current->next; // move to the next node.
	}

}

// freeList frees up the memory given to the linked list including the header node.
// it assumes that the given Header pointer is a valid pointer. It will return nothing.
// it does basically the same as displayList, going through each item and freeing the memory given to it iteratively.
void freeList(Header* head) {

	pushStack("freeList"); // push the function name to the stack
	LinkNode* current = head->head; // temp node to store the node we're working with.
	LinkNode* temp; // temp node to hold the next node while we free the memory associated with the current node.
	while (current != NULL) { // exit condition: current is at the tail of the node.
		free(current->data); // free the memory associated with the string in the node.
		temp = current->next; // allow temp to hold the referene to the next node in the link. 
		free(current); // free the memory associated with the current node.
		current = temp; // make the current node advance to the next.
	} // repeat until we free the end of the list
	free(head); // once this is done, we can free the memory given to the head of the list and exit.

}

