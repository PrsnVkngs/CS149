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
	NameEntry *entries; // we will assign this to the base address of some allocated memory equal to the
			    // total size of the set times the size of NameEntry. Therefore, we can treat it as an array.
} HashSet;

unsigned int hash_name(char *name) {
	// Given that we are given the names of each person, and we know from the assignment statement that they are 
	// in ASCII format, we can utilize the DJB2 hash function to create a hash for the name. A simple sum of
	// ASCII values proved to be inadequate in testing because different combinations of values could result
	// in the same hash.
	unsigned int hash = 5381;
	int c;

	while ( (c = *name++) ) {
		hash = ( (hash << 5) + hash) + c;
	}

	return hash % MAX_NAMES;

}

HashSet *create_hash_set() {
	HashSet *set = (HashSet *) malloc(sizeof(HashSet));
	set -> entries = (NameEntry *) calloc(MAX_NAMES, sizeof(NameEntry));
	return set;
}

void put(HashSet *set, char *name) {

	unsigned int index = hash_name(name);

	while (set->entries[index].value != 0) {
		if (strcmp(set->entries[index].key, name) == 0) {
			set->entries[index].value++;
			return;
		}
		index = (index+1) % MAX_NAMES;
	}

	strcpy(set->entries[index].key, name);
	set->entries[index].value+=1;
}

void displayResults(HashSet *set) {

	for (int i = 0; i < MAX_NAMES; i++) {
		if (set->entries[i].value != 0) {
			printf("Name: %s\t\tAppearances: %d", set->entries[i].key, set->entries[i].value);
		}
	}

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

	// add hashmap here

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
