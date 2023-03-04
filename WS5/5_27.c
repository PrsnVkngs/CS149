#include <stdio.h>
#include <string.h>

#define MAX_LINE 50

int main() {

	char line[MAX_LINE];

	while(1) {

		fgets(line, MAX_LINE, stdin);

		line[strcspn(line, "\n")] = '\0';

		if ( !strcmp(line, "done") || !strcmp(line, "Done") || !strcmp(line, "d") ) {
			break;
		}

		for (int c = strlen(line)-1; c >= 0; c--) {
			printf("%c", line[c]);
		}
		printf("\n");

	}

	return 0;

}
