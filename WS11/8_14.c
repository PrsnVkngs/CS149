#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ContactNode {

	char* contactName;
	char* contactPhoneNumber;
	struct ContactNode* nextNode;

} ContactNode;

// ---- InitializeContactNode -----
// Assumes that the inputs: name & phone number are valid c-strings
// Returns a pointer to a new ContactNode.
ContactNode* InitializeContactNode(char* name, char* phone) {

	ContactNode* newContact = (ContactNode*)malloc(sizeof(ContactNode));

	newContact -> contactName = (char*)malloc(strlen(name) * sizeof(char) + 1);
	strcpy(newContact -> contactName, name);

	newContact -> contactPhoneNumber = (char*)malloc(strlen(phone) * sizeof(char) + 1);
	strcpy(newContact -> contactPhoneNumber, phone);

	newContact -> nextNode = NULL;

	return newContact;

}

// ---- GetName ---- 
// Accessor function. Assumes the input: ContactNode is valid.
// Returns the string with the name that is contained in the struct.
char* GetName(ContactNode* contact) {

	return contact -> contactName;

}

// ---- GetPhoneNumber ----
// Accessor function. Assumes the input: ContactNode is valid.
// Returns the string which contains the phone number in the passed in struct.
char* GetPhoneNumber(ContactNode* contact) {

	return contact -> contactPhoneNumber;

}

// ---- InsertAfter ---- 
// Function takes in the node and another node and inserts it after the given node.
// Assumes that the given node is valid, as well as the new one that we insert.
// Returns an integer representing success or failure. (0 success, 1 failure);
int InsertAfter(ContactNode* current, ContactNode* next) {

	current->nextNode = next;

	return 0;

}

// ---- GetNext ----
// Accessor function. Returns the pointer to the next node in the linked list of the given node.
// Assumes that the passed node is valid.
ContactNode* GetNext(ContactNode* node) {

	return node->nextNode;

}

// ---- PrintContactNode ----
// Display function. Prints out the contents of the node.
// Assumes that the passed Node is valid.
// Void return value.
void PrintContactNode(ContactNode* node) {

	printf("Name: %s\nPhone Number: %s\n", node->contactName, node->contactPhoneNumber);

}

// ---- FreeNode ----
// Memory handler function. Assumes the passed Node is valid.
// Frees the memory that was given to this node during the init function.
// No return value (void)
void FreeNode(ContactNode* node) {

	free(node->contactName);
	free(node->contactPhoneNumber);
	free(node);

}

#define MAX_LINE 512

int main() {

	char tname[MAX_LINE];
	char tnumber[MAX_LINE];
	char control;

	ContactNode* dummyHead = InitializeContactNode("Dummy Head\0", "123-456-7890\0");
	ContactNode* tail = dummyHead;
	ContactNode* newLink;

	while (1) {

		printf("Enter a name: ");
		fgets(tname, MAX_LINE, stdin);
		printf("Enter a phone number (xxx-xxx-xxxx): ");
		fgets(tnumber, MAX_LINE, stdin);

		tname[strcspn(tname, "\n")] = '\0';
		tnumber[strcspn(tnumber, "\n")] = '\0';

		newLink = InitializeContactNode(tname, tnumber);
		if (InsertAfter(tail, newLink) == 0) {
			tail = newLink;
		}

		printf("Continue? (y/n)");
		scanf(" %c", &control);

		if (control == 'n') {
			break;
		}

		int c;
		while((c = getchar()) != '\n' && c != EOF);

	}
	newLink = NULL; // don't need to worry about freeing this since it will be freed with the list.

	// reuse tail as "temp".
	tail = dummyHead->nextNode;
	while (tail != NULL) {

		PrintContactNode(tail);
		tail = tail->nextNode;

	}

	// we can reuse the variables we already made. Dummy head can be "current" and tail can be "temp".
	while (dummyHead != NULL) {

		tail = dummyHead->nextNode;
		FreeNode(dummyHead);
		dummyHead = tail;

	}

	return 0;

}

