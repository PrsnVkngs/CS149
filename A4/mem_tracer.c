#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myfunctions.h"
#include "commands.h"
#include "linked_list.h"
#include "mem_stack.h"

#define LINE_LEN 1024 //give 1KB of memory for a line, the line will undoubtedly be shorter, but just in case...

int main() {

	char buffer[LINE_LEN]; // create an input buffer with size of the line length

	init_memtrace(); // initialize the memory trace file, which stores when memory gets allocated, reallocated and deallocated.
	initStack(); // initialize the function stack trace as well.

	pushStack("main"); // push main onto the stack
	Commands* com_arr = makeCommands(); // use our pseudo constructor to make a Commands object for us.
	Header* list_head = initHead(); // initialize the header node in the list.

	// code goes here

	while (fgets(buffer, LINE_LEN, stdin) != NULL) { // loop until fgets recieves the EOF signal.

		buffer[strcspn(buffer, "\n")] = '\0'; // replace the newline that fgets read in with a null terminator

		add(com_arr, buffer); // add the command to the array

		insert(list_head, buffer); // as well as the linked list.

	}

	// the following two commands have been commented out for the final submission but can be uncommented.
	// the assumption is that the submission only wants the output on stdout to be the stack trace.
	// displayCommands(com_arr); // display all the commands in the array
	// displayList(list_head); // display all the commands again from the linked list.

	// code ends here
	
	// maintainence and cleanup starts here
	
	freeCom(com_arr); // free up the memory given by makeCommands()
	freeList(list_head); // free up the memory given to our linked list.
	displayStack(); // display the stack as per assignment requirements.
	// NOTE: we display the stack here instead of above since free list and free com are also function calls that should go on the stack.
	freeStack(); // after we displayed the stack, we free the memory given to it.
	com_arr = NULL; // set the command array to NULL after we freed it to avoid issues & to follow good practice.
	list_head = NULL; // same here as above.
	close_memtrace(); // close the memory trace.out file

	return 0; // program executed completely and successfully.

}
