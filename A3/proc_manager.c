#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINE_LENGTH 30
#define MAX_PARAMS 4
#define LINE_COUNT 100

int main(void) {

	char input[LINE_LENGTH+1];
	char* temp;
	char* command; 
	char** argv; // assume max 4 parameters
	int argc;

	while(fgets(input, LINE_LENGTH+1, stdin) != NULL) {

		argc = 0;
		temp = strtok(input, " ");
		command = temp;

		printf("temp = %s\n", temp);

		while(temp != NULL && argc < MAX_PARAMS) {

			argv[argc++] = temp;
			temp = strtok(NULL, " ");

		}

		printf("Command: %s\n", command);
		int i = 0;
		while(i < argc){
			printf("Arg %d is %s ", i++, argv[i]);
		}

	}

	return 0;

}
