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
	char* temp; //= (char *) malloc(LINE_LENGTH * sizeof(char)); //TODO don't forget to free.
	// char* command = (char *) malloc(LINE_LENGTH * sizeof(char)); 
	char command[LINE_LENGTH];
	// char** argv = (char **) malloc(MAX_PARAMS * sizeof(char *)); // assume max 4 parameters 
	char argv[MAX_PARAMS][LINE_LENGTH];
	char* nullptr = NULL;
	int argc;

	//for(int mem = 0; mem < MAX_PARAMS; mem++) {
	//	argv[mem] = (char *) malloc(LINE_LENGTH * sizeof(char));
	//}

	while(fgets(input, LINE_LENGTH+1, stdin) != NULL) {

		argc = 0;
		temp = strtok(input, " ");
		strcpy(command, temp);

		printf("temp = %s\n", temp);

		while(temp != NULL && argc < MAX_PARAMS) {

			strcpy(argv[argc++], temp);
			temp = strtok(NULL, " ");

		}

		// strcpy(argv[argc], nullptr);

		printf("Command: %s\n", command);
		int i = 0;
		while(i < argc){
			printf("Arg %d is %s\n", i++, argv[i]);
		}

	}

	// free(temp);	
	/*for(int i = 0; i < MAX_PARAMS; i++){
		printf("Address %d in argv is %p\n", i, argv[i]);

		free(argv[i]);
	}
	free(command);
	free(argv);
*/
	return 0;

}
