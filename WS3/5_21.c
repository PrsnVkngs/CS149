#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_LENGTH 11

int main() {

	int num_words;
	scanf("%d ", &num_words);

	char **word = malloc(num_words * sizeof(char *));
	char input[WORD_LENGTH];

	for(int i = 0; i < num_words; i++) {
		
		scanf("%s ", input);
		word[i] = malloc( (strlen(input)+1) * sizeof(char) );
		strcpy( word[i], input);

	}

	char containing;
	scanf(" %c", &containing);
	char search[WORD_LENGTH];
	bool toPrint;

	for(int i = 0; i < num_words; i++) {
		
		toPrint = false;
		strcpy(search, word[i]);
		for(int n = 0; n < strlen(search); n++) {
			if (search[n] == containing) {
				toPrint = true;
				break;
			}
		}

		if ( toPrint ) {
			printf("%s,", word[i]);
		}

	}
	printf("\n");


	return 0;

}

