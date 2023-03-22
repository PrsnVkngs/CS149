#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define LINE_LENGTH 30
#define MAX_PARAMS 4
#define LINE_COUNT 100

int main(void) {

	char buffer[LINE_LENGTH*2];
	char input[LINE_LENGTH+1];
	char* temp; //= (char *) malloc(LINE_LENGTH * sizeof(char)); //TODO don't forget to free.
	// char* command = (char *) malloc(LINE_LENGTH * sizeof(char)); 
	char command[LINE_LENGTH];
	// char** argv = (char **) malloc(MAX_PARAMS * sizeof(char *)); // assume max 4 parameters 
	char argv[MAX_PARAMS+1][LINE_LENGTH];	
	int argc;
	int pid;
	int commandNo = 1;

	//for(int mem = 0; mem < MAX_PARAMS; mem++) {
	//	argv[mem] = (char *) malloc(LINE_LENGTH * sizeof(char));
	//}

	while(fgets(buffer, LINE_LENGTH*2, stdin) != NULL) {

		strncpy(input, buffer, LINE_LENGTH);
		argc = 0;
		temp = strtok(input, " ");
		strcpy(command, temp);

		printf("temp = %s\n", temp);

		while(temp != NULL && argc < MAX_PARAMS) {

			strcpy(argv[argc++], temp);
			temp = strtok(NULL, " ");

		}

		strcpy(argv[argc], "NULL");

		pid = fork();

		if(pid == -1) {
			perror("Fork failure.");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0) {
			char out_name[20], err_name[20];
			sprintf(out_name, "%d.out", getpid());
			sprintf(err_name, "%d.err", getpid());

			/*
			FILE* out_file = freopen(out_name, "w", stdout);
			FILE* err_file = freopen(err_name, "w", stderr); 
			//TODO might have to use dup2 depending on the execvp behavior.

			if (out_file == NULL || err_file == NULL) {
				perror("File opening in child process %d failed.\n", getpid());
				exit(EXIT_FAILURE);
			}
			*/

			int out_fd = open(out_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
			int err_fd = open(err_name, O_WRONLY | O_CREAT | O_APPEND, 0777);

			if (dup2(out_fd, STDOUT_FILENO) < 0 || dup2(err_fd, STDERR_FILENO) < 0) {
				perror("Dup2 file descriptor replacement failed.");
			}
			// close(out_fd);
			// close(err_fd);
			
			char* arguments[] = {argv[0], argv[1], argv[2], argv[3], argv[4] };

			printf("Starting command %d: child %d of parent %d\n", commandNo, getpid(), getppid());
			int exec_result = execvp(command, arguments);

			fprintf(stderr, "execvp in child %d failed with error code %d\n", getpid(), exec_result);

			exit(EXIT_FAILURE);


		}

		commandNo++;
		/*
		printf("Command: %s\n", command);
		int i = 0;
		while(i < argc){
			printf("Arg %d is %s\n", i++, argv[i]);
		}
		*/

	}

	/*
	free(temp);	
	for(int i = 0; i < MAX_PARAMS; i++){
		printf("Address %d in argv is %p\n", i, argv[i]);

		free(argv[i]);
	}
	free(command);
	free(argv);
	*/

	return 0;

}
