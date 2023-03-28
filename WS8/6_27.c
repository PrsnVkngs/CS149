#include <stdio.h>
#include <string.h>

#define MAX_CHARS 50

int main() {

	char searchKey;
	char word[MAX_CHARS];

	scanf("%c", &searchKey);
	fgets(word, MAX_CHARS, stdin);

	word[strcspn(word, "\n")] = '\0';

	int occurences = 0;

	for(int i = 0; i < strlen(word); i++) {
		if (word[i] == searchKey) {
			occurences++;
		}
	}

	printf("%d %c", occurences, searchKey);
	if (occurences != 1) {
		printf("'s\n");
	}
	else {
		printf("\n");
	}

	return 0;

}
