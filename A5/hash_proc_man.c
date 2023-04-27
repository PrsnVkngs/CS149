#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
// all of our imports.
#include "ProcessTable.h"

#define RESTART_THRESHOLD 2

int quickWrite(char* filename, char* data); // method declaration (prototype) so that the main function knows what it is.
int startProcess(int commandNo, char command[], char* argv[], int restarted);

int main(void) {

    char buffer[LINE_LENGTH]; // fgets buffer. longer than the line length in case a command longer than 30 is entered.
    char input[LINE_LENGTH]; // the actual input, + 1 for null terminator.
    char* temp; // temp string so we can tokenize the command.
    char command[LINE_LENGTH]; // the command, such as ls.
    char* argv[MAX_PARAMS+1]; // the argument list.
    int argc; // argument count.
    int pid; // pid of the fork.
    int commandNo = 1; // the command number in the order that the parent received them.
    initTable();

    while(fgets(buffer, LINE_LENGTH, stdin) != NULL) { // read in a bigger line as a buffer just in case we enter a line that is longer that we expect.

        strncpy(input, buffer, LINE_LENGTH); // copy the exact length of the command to the input variable.

        argc = 0; // initialize number of arguments to zero.
        temp = strtok(input, " "); // get the first item on the input stream.
        temp[strcspn(temp, "\n")] = '\0'; // replace newline with null terminator.
        strcpy(command, temp); // put the command on the command variable.

        while(temp != NULL && argc < MAX_PARAMS) {

            temp[strcspn(temp, "\n")] = '\0'; // replace newline with null terminator.
            argv[argc++] = temp; // add the parameter to the parameter list.
            temp = strtok(NULL, " "); // go to the next token.

        }

        argv[argc] = NULL; // add null at the end of the list of args.

        startProcess(commandNo, command, argv, 0);

        commandNo++; // increment program number

    }

    int childPID;
    int status;
    char write_file[20];
    char message[50];
    printf("Now going to wait for processes to finish.\n");
    while((childPID = wait(&status)) > 0) {

        sprintf(write_file, "%d.out", childPID);

        Process* p = get(childPID);
        updateEnd(childPID);
        double elapsed = (double)(p->end_t.tv_sec - p->start_t.tv_sec);
//        if ( elapsed > 2.0 ) {
//            quickWrite(write_file, "RESTARTING\n\0");
//        }
        sprintf(message, "Finished child %d pid of parent %d", childPID, getpid());
        quickWrite(write_file, message); // repeat for the finish message.
        sprintf(message, "Finished at %.2fd, with a duration of %.2f.\n", (double)p->end_t.tv_sec, elapsed);
        quickWrite(write_file, message);


        sprintf(write_file, "%d.err", childPID); // put the filename on the file in the variable.

        printf("Elapsed time is %.2f", elapsed);
        if ( elapsed > 2.0 ) {
            // quickWrite(write_file, "RESTARTING\n\0");
            startProcess(p->index, p->command[0], p->command, 1);
        }
        else {
            quickWrite(write_file, "Spawning too fast.");
        }
        if (status == 0) {
            sprintf(message, "Exited with exitcode = %d", status); // set the message to "exited".
        }
        else if(status == 15 || status == 9 || status == 2 || status == 3) {
            sprintf(message, "Process was killed with code: %d", status); // set message to "killed".
            // remove_proc(childPID);
            continue;
        }


    }

    freeTable();

    return 0; // end of program.

}

int startProcess(int commandNo, char command[], char* argv[], int restarted) {

    int pid = fork();

    if(pid == -1) {
        perror("Fork failure.");
        exit(EXIT_FAILURE); // if fork failed, then print error message and exit.
    }
    else if(pid == 0) {
        char out_name[20], err_name[20];
        sprintf(out_name, "%d.out", getpid());
        sprintf(err_name, "%d.err", getpid()); // create the filenames with the child's pid.

        int out_fd = open(out_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
        int err_fd = open(err_name, O_WRONLY | O_CREAT | O_APPEND, 0777); // open the files and get their file descriptor number.

        if (dup2(out_fd, STDOUT_FILENO) < 0 || dup2(err_fd, STDERR_FILENO) < 0) {
            perror("Dup2 file descriptor replacement failed.");
            exit(EXIT_FAILURE); // ensure that both dup2 calls succeeded, otherwise, print error message and exit with failure code.
        }

        if ( restarted == 1 ) {
            printf("RESTARTING");
            fprintf(stderr, "RESTARTING");
        }
        printf("Starting command %d: child %d of parent %d\n", commandNo, getpid(), getppid());
        int exec_result = execvp(command, argv); // execvp should take over from here.

        fprintf(stderr, "execvp in child %d failed with error code %d\n", getpid(), exec_result);

        close(out_fd);
        close(err_fd);
        exit(EXIT_FAILURE); // in-case execvp fails, we print an error message, then close the file descriptors we opened and exit with a failure code.

    }
    else {
        insert(pid, commandNo, argv);
    }

    return pid;

}

/*
this function, quickWrite, takes in a filename, and a string of data.
The function writes the given data to the filename passed in and closes it. It will return 1 for failure and 0 for success.
*/
int quickWrite(char* filename, char* data) {

    FILE* fp = fopen(filename, "a"); // open a file with the given filename.

    if (fp == NULL) {
        perror("file opening failed.\n"); // ensure that the open worked, if not return failure.
        return 1;
    }

    fputs(data, fp); // put the data and a newline at the end of the file.
    fputs("\n", fp);
    fclose(fp); // close the file and return 0.

    return 0;

}