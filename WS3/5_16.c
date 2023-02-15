#include <stdio.h>
#include <string.h>

int main() {

	int inputNums[20];
	char input[256];
	fgets(input, 256, stdin);
	char *token = strtok(input, " ");
	int count = 0;
	int num = 0;
	
	while ( count < 20 && token != NULL ) {

		sscanf(token, "%d", &num);

		inputNums[count] = num;
		count++;

		token = strtok(NULL, " ");

	}

	//printf("%d nums, first num is %d", count, inputNums[0]);

	for ( int i = count-1; i >= 0; i-- ) {

		printf("%d,", inputNums[i]);

	}
	printf("\n");

	return 0;

}

