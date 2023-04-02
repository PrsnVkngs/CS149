#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 512 // define an input buffer size of 512 bytes.

char* substring(const char* full_string, int start_index, int end_index); // takes in a string and substrings it from start to end.
char** split_line(const char* line); // takes in a line, and splits it by a comma and returns 2 char strings.
void free_line(char** line); // frees the space allocated to the above char**.

int main() {
	
	while ( 1 ) { // To extend the program to work until the user wants to quit, simply enclose the code in a while loop.

		char input_buffer[BUFFER_SIZE];

		printf("Enter two words, separated by a comma(enter 'q' to quit):\n");
	
		fgets(input_buffer, BUFFER_SIZE-1, stdin);

		if ( input_buffer[0] == 'q' && input_buffer[1] == '\n' ) {
			printf("Goodbye!\n");
			exit(EXIT_SUCCESS);
		}

		input_buffer[strcspn(input_buffer, "\n")] = '\0';

		if ( strcspn(input_buffer, ",") == strlen(input_buffer) ) { // strcspn searches for a comma. If it doesn't find it, it returns the length of the string. We check for this and throw and error and exit the program if this is the case.
			fprintf(stderr, "Error: No comma in string.\n");
			exit(EXIT_FAILURE);
		}

		// fprintf(stderr, "The line that was read in was -%s-\n", input_buffer);

		char** words = split_line(input_buffer);

		printf("First word: -%s-\nSecond word: -%s-\n", words[0], words[1]);
		// dashes are added in the output to show that there are no spaces, leading nor trailing.

		free_line(words);
		words = NULL; // free the memory associated with words and set the poitner to null to avoid issues.
		
		// fflush(stdin);

	}

	return 0;

}

char** split_line(const char* line) {

	char** words = (char**)malloc(sizeof(char*) * 2); // request memory for two char pointers.
	words[0] = NULL; // initialize them to NULL for now.
	words[1] = NULL;
	
	int comma_loc = strcspn(line, ","); // find where the comma is in the line.

	char buffer[strlen(line)]; // create a buffer the size of the line.
	strncpy(buffer, line, comma_loc); // copy characters up until just before the comma.

	int start_index = 0, 
	    end_index = comma_loc - 1; // define the start and end indexes for the word.

	while ( isspace(buffer[start_index]) ) { // check for whitespace and advance the index if we see whitespace.
		start_index++;
	}
	while ( isspace(buffer[end_index]) ) { // same as above, but for trailing instead of leading whitespace.
		end_index--;
	}
	
	int length_of_word = end_index - start_index + 1; // get the length of the word by subtracting the start and end index.
	// fprintf(stderr, "Start Index = %d, End Index = %d", start_index, end_index);
	// fprintf(stderr, "the contents of the buffer for the first word is: -%s- low = %d\n", buffer, length_of_word);

	words[0] = (char*)malloc( sizeof(char) * (length_of_word + 1) ); // allocate memory for the word + 1 for the null terminator.
	strncpy(words[0], buffer+start_index, length_of_word); // copy the word to the new memory.
	words[0][length_of_word] = '\0';
	
	strcpy(buffer, (line+comma_loc+1)); // move the second word into the buffer.

	start_index = 0; // make the start index 0 again.
	end_index = strlen(buffer)-1; // end index is simply the stringlength of the buffer.
				    // now we simply repeat the same as above for the second word.

	while ( isspace(buffer[start_index]) ) {
		start_index++;
	}
	while ( isspace(buffer[end_index]) ) {
		end_index--;
	}

	length_of_word = end_index - start_index + 1;

	// fprintf(stderr, "Start Index = %d, End Index = %d", start_index, end_index);
	// fprintf(stderr, "the contents of the buffer for the second word is: -%s- low = %d\n", buffer, length_of_word);

	words[1] = (char*)malloc( sizeof(char) * (length_of_word + 1) );
	strncpy(words[1], buffer+start_index, length_of_word);
	words[1][length_of_word] = '\0'; // append null terminator just in case.

	// now the words are in two char arrays pointed to by the words**
	
	return words;

}

/*
 * We are assuming that the variable, line, that is passed in as a parameter comes in as we made it in the split_line function.
 */
void free_line(char** line) {

	free(line[0]);
	free(line[1]);
	free(line);

}
