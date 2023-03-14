#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARACTERS 50

int main() {

	char phrase[MAX_CHARACTERS];

	fgets(phrase, MAX_CHARACTERS, stdin);

	phrase[strcspn(phrase, "\n")] = '\0';

	int l = 0, r = strlen(phrase) - 1;

	while (l < r ) {

		while(phrase[l] == ' ') {
			l++;
		}
		while(phrase[r] == ' ') {
			r--;
		}

		if(tolower(phrase[l]) != tolower(phrase[r])) {
			printf("not a palindrome: %s\n", phrase);
			return 0;
		}

		l++;
		r--;

	}

	printf("palindrome: %s\n", phrase);

	return 0;

}
