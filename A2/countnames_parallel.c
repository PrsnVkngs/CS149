/*
 * Description: This program serves as a microservice to count the names in a given file.
 * Author Name: Oskar Attar
 * Author Email: oskar.attar@sjsu.edu
 * Last modified date: 03/03/2023
 * Creation date: 2/18/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 31 //this value is for when we scan in the line, just to bullet proof our code.
#define MAX_NAMES 100

/*
 * this struct is for the entries in the set, and has a key variable which stores the name,
 * as well as an integer value for the number of occurences this name has made in the file.
 */
typedef struct {
	char key[MAX_NAME_LEN];
	int value;
} NameEntry;

/*
 * struct for the HashSet, is also assigned a name with typedef.
 */
typedef struct {	
	NameEntry *entries; // we will assign this to the base address of some 
			    // allocated memory equal to the
			    // total size of the set times the size of NameEntry. 
			    // Therefore, we can treat it as an array.
} HashSet;


/*
 * Hash_name is the hash function that the hash_set relies on. It utilizes a slightly modified 
 * DJB2 algorithm, where it uses integers instead of longs, because the keyspace of this application
 * is relatively small.
 * Assumes that the name passed in is a valid name array with ascii valued chars.
 * Returns an integer remainder of the hash function result within the size of the set.
 */
unsigned int hash_name(char *name) {
	// Given that we are given the names of each person, 
	// and we know from the assignment statement that they are 
	// in ASCII format, we can utilize the DJB2 hash function to create a hash for the name. 
	// A simple sum of
	// ASCII values proved to be inadequate in testing because different 
	// combinations of values could result
	// in the same hash.
	unsigned int hash = 5381;
	int c;

	while ( (c = *name++) ) {
		hash = ( (hash << 5) + hash) + c;
	}

	return hash % MAX_NAMES;

}

/*
 * The create hash set function is akin to a constructor in other languages.
 * It acts as a way for a user to initialize a HashSet and get an address pointing to it.
 * Assumes that there is enough memory present to allocate to the HashSet and its entries.
 * Returns a pointer to the HashSet object.
 */
HashSet *create_hash_set() {
	HashSet *set = (HashSet *) malloc(sizeof(HashSet));
	set -> entries = (NameEntry *) calloc(MAX_NAMES, sizeof(NameEntry));
	return set;
}


/*
 * The put function takes in an address to a HashSet, and a name, then hashes the name and inserts it
 * into the map. It uses linear collision detection/resolution.
 * Assumes: That set and name are valid pointers.
 * No return value.
 * */
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

/*
 *displayResults does as is named. It goes through the HashSet entries one by one,
 and checks if there is a value present. If there is, the method prints it out. If not, it skips that entry.
Assumption: The set pointer passed in is valid and not null.
 */
void displayResults(HashSet *set) {

	for (int i = 0; i < MAX_NAMES; i++) {
		if (set->entries[i].value != 0) {
			printf("%s\t-\t%d\n", set->entries[i].key, set->entries[i].value);
		}
	}

}

/**
 * This function is a shortcut function that frees the memory allocated to the HashSet 
 * including the memory given to its entries.
 * Assumption: The hashset pointer given is valid and is not a null pointer.
 * */
void freeSet(HashSet *set) {

	free(set->entries);
	free(set);

}


int main(int argc, char *argv[]) {

	// the following if statement checks if the program is given two (or more) files.
	// If not, we assume that the user has not provided a file on the command line.
	if (argc < 2) {
		printf("No file name provided.\nType '%s <filenames>', each separated by a space, instead.\n", argv[0]);
		return 1;
	}

	// the following code with the if statement attempts to open the file.
	// If the file pointer is a null pointer then we throw an error and terminate the program.	

	HashSet *set = create_hash_set(); // creates a new HashSet variable from the method. 

	char line[MAX_LINE_LEN]; // temporary variable for the loop to hold the value read in by fgets
	char name[MAX_NAME_LEN+1]; // temporary variable to hold the name that we scan from the line variable.
	int line_num = 1; // counter variable to keep track of which line we are on for error messages.

	/* *
	 *
	 * This while loop uses the return value of fgets to get the value of the line that it is
	 * currently on. It then replaces the newline character with an end of line character.
	 * Next, it checks if the line is empty or not. 
	 * If it is, then it prints out an error message, then continues to the next line in the file.
	 * If it isn't empty, the program continues. Next it uses sscanf to ensure that there is a name
	 * that is being read into the name temp variable. While not necessary, it is an extra layer
	 * of protection for the code. Finally, it pushes the read line to the HashSet.
	 *
	 * */
	int fileNum = 1;
	int countPipe[2];
	pid_t pid;

	if (pipe(countPipe)) == -1 {
		fprintf(stderr, "Pipe creation failed.\n");
		return 1;
	}

	for (fileNum = 1; fileNum < argc-1; fileNum++) {
	       pid = fork();
	}

	if ( pid < 0 ) {
		fprintf(stderr, "Fork failed at process: %d.\n", getpid());
		return 1;
	}



	while(fgets(line, MAX_LINE_LEN, nameFile) != NULL) {

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) == 0) {
			fprintf(stderr, "Warning - Line %d is empty.\n", line_num);
			continue;
		}

		if ( sscanf(line, "%30[^\n]", name) == 1 ) {

			put(set, name);

		}
		else {
			printf("error reading line %d\n", line_num);
		}
		line_num++;
	}

	displayResults(set); // calls the display results function to show the counts of all the names.

	fclose(nameFile); // close the file that we are reading from.
			 
	freeSet(set); // free the memory allocated to the HashSet.

	return 0;

}
