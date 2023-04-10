#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myfunctions.h"
#include "commands.h"
#include "linked_list.h"

#define LINE_LEN 1024 //give 1KB of memory for a line, the line will undoubtedly be shorter, but just in case...

int main() {

	char buffer[LINE_LEN];

	printf("Initialized input buffer.\n");

	init_memtrace();

	printf("Initialized memtrace.\n");

	Commands* com_arr = makeCommands(); // use our pseudo constructor to make a Commands object for us.
	// printf("Initialized commands array.\n");
	Header* list_head = initHead();
	// printf("Initialized linked list\n");

	// code goes here

	while (fgets(buffer, LINE_LEN, stdin) != NULL) {

		buffer[strcspn(buffer, "\n")] = '\0';

		add(com_arr, buffer);

		insert(list_head, buffer);

	}

	displayCommands(com_arr);
	displayList(list_head);

	// code ends here
	
	freeCom(com_arr); // free up the memory given by makeCommands()
	freeList(list_head); // free up the memory given to our linked list.
	com_arr = NULL;
	list_head = NULL;
	close_memtrace();

	return 0; // program executed completely and successfully.

}
