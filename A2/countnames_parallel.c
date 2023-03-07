/*
 * Description: This program serves as a microservice to count the names in a given file.
 * Author Name: Oskar Attar
 * Author Email: oskar.attar@sjsu.edu
 * Last modified date: 03/06/2023
 * Creation date: 3/03/2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 31 //this value is for when we scan in the line, just to bullet proof our code.
#define MAX_NAMES 100

/*
 * this struct is for the entries in the set, and has a key variable which stores the name,
 * as well as an integer value for the number of occurences this name has made in the file.
 */
typedef struct Name {
	char key[MAX_NAME_LEN];
	int value;
	struct Name *next;
} NameEntry;

/*
 * struct for the HashSet, is also assigned a name with typedef.
 */
typedef struct {	
	NameEntry entries[MAX_NAMES]; // we will assign this to the base address of some 
			    // allocated memory equal to the
			    // total size of the set times the size of NameEntry. 
			    // Therefore, we can treat it as an array.
} HashSet;


/*
 * Hash_name is the hash function that the hash_set relies on. It utilizes a slightly modified 
 * FNV-1a algorithm, where it uses integers instead of longs, because the keyspace of this application
 * is relatively small. In A1, we used the DJB2 algorithm. We are going to try the FNV 1a algorithm here.
 * Assumes that the name passed in is a valid name array with ascii valued chars.
 * Returns an integer remainder of the hash function result within the size of the set.
 */
unsigned int hash_name(char *name) {

	unsigned int OFFSET = 0x811c9dc5;
	unsigned int PRIME = 0x01000193;

	unsigned int hash = OFFSET;

	while (*name) {
		hash ^= (unsigned int)(*name++);
		hash *= PRIME;
	}

	return hash % MAX_NAMES;

	/* unsigned int hash = 5381;
	int c;

	while ( (c = *name++) ) {
		hash = ( (hash << 5) + hash) + c;
	}

	return hash % MAX_NAMES;
	*/ // DJB2 code just incase it needs to be reverted.

}

/*
 * The create hash set function is akin to a constructor in other languages.
 * It acts as a way for a user to initialize a HashSet and get an address pointing to it.
 * Assumes that there is enough memory present to allocate to the HashSet and its entries.
 * Returns a pointer to the HashSet object.
 */
HashSet *create_hash_set() {
	HashSet *set = (HashSet *) malloc(sizeof(HashSet));
//	set -> entries = (NameEntry *) calloc(MAX_NAMES, sizeof(NameEntry));
	return set;
}


/*
 * the put function takes in an address to a hashset, and a name, then hashes the name and inserts it
 * into the map. it uses linear collision detection/resolution.
 * assumes: that set and name are valid pointers.
 * no return value.
 * */
void put_inc(HashSet *set, char *name) {

	unsigned int index = hash_name(name);
	
	NameEntry *currentname = &set->entries[index];

//	printf("the value associate with the name: %s at index %d is %d\n", currentname->key, index, currentname->value);
	if ( currentname->value == 0 ) {
		strcpy(currentname->key, name);
		currentname->value=1;
		currentname->next = NULL;
		return;
	}

	while (true) {

		if (strcmp(currentname->key, name) == 0) {
			currentname->value+=1;
			return;
		}
		
		if ( currentname->next == NULL ) {
			break;
		}
		currentname = currentname->next;

	}

	// printf("collision occurred for %s, creating bucket at %d\n", name, index);

	NameEntry *newentry = calloc(1, sizeof(NameEntry));

	newentry->value = 1;
	strcpy(newentry->key, name);
	newentry->next = NULL;

	currentname->next = newentry;

	return;

	/*
	while (set->entries[index].value != 0) {
		if (strcmp(set->entries[index].key, name) == 0) {
			set->entries[index].value++;
			return;
		}
		printf("Trying to insert %s, however, %s is occupying it at index %d.\n", name, set->entries[index].key, index);
		index = (index+1) % MAX_NAMES;
	}

	strcpy(set->entries[index].key, name);
	set->entries[index].value+=1; */ // old code for preservation purpose.
}


/*
 * Overloaded version of the put function takes in an address to a hashset, and a name, and a value to add then hashes the name and inserts it
 * into the map. it uses linear collision detection/resolution.
 * assumes: that set and name are valid pointers.
 * no return value.
 * */
void put_val(HashSet *set, char *name, int value) {

	unsigned int index = hash_name(name);
	
	NameEntry *currentname = &set->entries[index];

//	printf("the value associate with the name: %s at index %d is %d\n", currentname->key, index, currentname->value);
	if ( currentname->value == 0 ) {
		strcpy(currentname->key, name);
		currentname->value=value;
		currentname->next = NULL;
		return;
	}

	while (true) {

		if (strcmp(currentname->key, name) == 0) {
			currentname->value+=value;
			return;
		}
		
		if ( currentname->next == NULL ) {
			break;
		}
		currentname = currentname->next;

	}

	// printf("collision occurred for %s, creating bucket at %d\n", name, index);

	NameEntry *newentry = calloc(1, sizeof(NameEntry));

	newentry->value = value;
	strcpy(newentry->key, name);
	newentry->next = NULL;

	currentname->next = newentry;

	return;
}

/*
 *displayResults does as is named. It goes through the HashSet entries one by one,
 and checks if there is a value present. If there is, the method prints it out. If not, it skips that entry.
Assumption: The set pointer passed in is valid and not null.
 */
void displayResults(HashSet *set) {

	NameEntry *nullptr = NULL;

	NameEntry *temp;
	for (int i = 0; i < MAX_NAMES; i++) {
		temp = &set->entries[i];
		while (temp!=nullptr) {
			if (temp->value != 0) {
				printf("%s\t-\t%d\n", temp->key, temp->value);
			}
			temp = temp->next;
		}
	}

}

/**
 * This function is a shortcut function that frees the memory allocated to the HashSet 
 * including the memory given to its entries.
 * Assumption: The hashset pointer given is valid and is not a null pointer.
 * */
void freeSet(HashSet *set) {

	NameEntry *nullptr = NULL;

	NameEntry *curr;
	NameEntry *next;
	for (int i = 0; i < MAX_NAMES; i++) {
		curr = &set->entries[i];
		while (curr != nullptr || curr->value != 0) {
			next = curr -> next;
			//printf("about to free memory address: %p | in a bucket at index: %d - name here is: %s\n", curr, i, curr->key);
			free (curr);
			curr = next;
		}
	}
	printf("freed buckets\n");	
	free(set->entries);
	free(set);

}
/*
 * This function takes in a HashSet pointer, as well as an array of data values to 
 * take in and aggregate into the set. Then it goes through the array and adds it to the hashset. 
 *
 */
void aggregateSet(HashSet *result, NameEntry data[]) {

	NameEntry *nullptr = NULL;

	NameEntry current;
	for (int i = 0; i < MAX_NAMES; i++) {
		current = data[i];
		while ( &current != nullptr && current.value != 0 ) {	
			put_val(result, current.key, current.value);
			current = *current.next;
		}
	}

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

	// printf("Args passed in:\n%s %s %s", argv[0], argv[1], argv[2]);

	if (pipe(countPipe) == -1) {
		fprintf(stderr, "Pipe creation failed.\n");
		return 1;
	}

	for (fileNum = 1; fileNum < argc; fileNum++) {
		pid = fork();
	

		if ( pid < 0 ) {
			fprintf(stderr, "Fork failed at process: %d.\n", getpid());
			return 1;
		}
		else if ( pid == 0 ) {
			// printf("The file we are trying to open in the child is %s\n", argv[fileNum]);
			//
			HashSet *set = create_hash_set();

			close (countPipe[0]); // close read end of pipe.

			FILE *nameFile = fopen(argv[fileNum], "r");
			if (nameFile == NULL) {
				fprintf(stderr, "File open for file %s failed.\n", argv[fileNum]);
				return 1;
			}

			// printf("Child process %d running.\n", getpid());

			while(fgets(line, MAX_LINE_LEN, nameFile) != NULL) {

				line[strcspn(line, "\n")] = '\0';

				if (strlen(line) == 0) {
					fprintf(stderr, "Warning - Line %d is empty.\n", line_num);
					continue;
				}

				if ( sscanf(line, "%30[^\n]", name) == 1 ) {

					put_inc(set, name);

				}
				else {
					fprintf(stderr, "error reading line %d\n", line_num);
				}
				line_num++;
			}

			//  displayResults(set);
			// write the data back to the pipe here.
			// printf("%p is the address of the set in child: %d, the size of hashset is: %lu, and SzOf entries is: %lu\n", 
					// set, getpid(), sizeof(set), sizeof(set->entries));

			
			write(countPipe[1], set->entries, sizeof(set->entries));
			freeSet(set); // we can read the set into memory in the parent process, but if we free the memory here,
			// we will get a segfault.
			fclose(nameFile);
			close(countPipe[1]);

			return 0;

		}
	}
	
	if ( pid != 0 ) {

		close(countPipe[1]); // close write end of pipe.
				     
		HashSet *results = create_hash_set();

		// HashSet *childResult = malloc(sizeof(HashSet));
		NameEntry child_results[MAX_NAMES];

		for (int i = 1; i < argc; i++) {
			if (wait(NULL) < 0 ) {
				continue;
			}
			read(countPipe[0], &child_results, sizeof(child_results));
			printf("successfully read in data from pipe\n");
			for (int i = 0; i < MAX_NAMES; i++) {
				if (child_results[i].value != 0) {
					printf("%s - %d\n", child_results[i].key, child_results[i].value);
				}
			}
			// aggregateSet(results, child_results);

			printf("Finished %d loop(s)\n", i);
		}

		displayResults(results);

		// freeSet(results);	

		close(countPipe[0]);

		return 0;

	}

}
