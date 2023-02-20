#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 50 //this value is for when we scan in the line, just to bullet proof our code.
#define MAX_NAMES 100

typedef struct {
	char key[MAX_NAME_LEN];
	int value;
} NameEntry;

typedef struct {
	int size;
	NameEntry *entry;
} HashSet;

int hash_name(char *name) {
	// Given that we are given the names of each person, and we know from the assignment statement that they are 
	// in ASCII format, we can make a simple hash function that just sums up the ASCII values of the characters 
	// in the name.
	int sum = 0;

	for(int i = 0; i < strlen(name); i++) {
		sum += name[i];
	}
	return sum % 100;	
}

HashSet *create_hash_set(int size) {
	HashSet *set = (HashSet *) malloc(sizeof(HashSet));
	set -> size = size;
	set -> entry = (NameEntry *) calloc(size, sizeof(NameEntry));
	return set;
}



int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("No file name provided.\nType '%s <filename>' instead.", argv[0]);
		return 1;
	}

	FILE *nameFile = fopen(argv[1], "r");
	if (nameFile == NULL) {
		printf("The program could not find the file %s.\n", argv[1]);
		return 1;
	}

	char line[MAX_LINE_LEN];
	char name[MAX_NAME_LEN+1];
	int name_count[MAX_NAMES] = {0};
	int line_num = 1;

	while(fgets(line, MAX_LINE_LEN, nameFile) != NULL) {

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0) {
			printf("Warning - Line %d is empty.", line_num);
			continue;
		}

		if ( sscanf(line, "%30[^\n]", name) == 1 ) {

			for (int i = 0; i < MAX_NAMES; i++) {
				if (name_count[i] == 0 || strcmp(name, (char *) &name_count[i]) == 0) {
					strcpy( (char *) &name_count[i], name);
					name_count[i+1]++;
					break;
				}
			}
		}
		else {
			printf("error reading line %d\n", line_num);
		}

		line_num++;

	}

	for (int i = 0; i < MAX_NAMES; i++) {
		if (name_count[i] == 0) {
			continue;
		}
		printf("%s - %d\n", (char *) &name_count[i], name_count[i+1]);

	}

	fclose(nameFile);

	return 0;

}
