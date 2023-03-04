#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	pid_t pid;
	int i;

	for (i = 0; i < 4; i++) {
		pid = fork();

		if (pid < 0) {
			printf("Fork has failed.\n");
			return 1;
		}
		else if (pid == 0) {
			printf("hello world from PID %d!\n", getpid());
			return 0;
		}

	}

	for (i = 0; i < 4; i++) {
		wait(NULL);
	}

	return 0;

}
