#include <stdio.h>
#include <stdbool.h>

void printSpaces(int spaces);
void printNum(int n, int cnt, bool endline);

int main() {

	int baseInt;
	int headInt;

	scanf("%d %d", &baseInt, &headInt);
	getchar();

	printSpaces(4);
	printNum(headInt, 1, true);

	printSpaces(4);
	printNum(headInt, 2, true);

	printNum(baseInt, 4, false);
	printNum(headInt, 3, true);

	printNum(baseInt, 4, false);
	printNum(headInt, 4, true);

	printNum(baseInt, 4, false);
	printNum(headInt, 3, true);

	printSpaces(4);
	printNum(headInt, 2, true);

	printSpaces(4);
	printNum(headInt, 1, true);


	return 0;
}

void printSpaces(int spaces) {
	for(int i = 0; i < spaces; i++) {
		printf(" ");
	}
}

void printNum(int n, int cnt, bool endline) {
	for(int i = 0; i < cnt; i++) {
		printf("%d", n);
	}
	if ( endline ) {
		printf("\n");
	}
}
