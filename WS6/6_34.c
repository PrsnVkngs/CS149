#include <stdio.h>

int isArrayMult10(int list[], int size); // int value represents a boolean where 0 is false and 1 is true. 2 will represent mixed.

int main() {

	int size;
	scanf("%d", &size);

	int numbers[size];

	int count = 0;
	while (count < size) {
		scanf("%d", &numbers[count]);
		count++;
	}

	switch (isArrayMult10(numbers, size)) {
		case 0:
			printf("no multiples of 10\n");
			break;
		case 1:
			printf("all multiples of 10\n");
			break;
		case 2:
			printf("mixed results\n");
			break;

	}

	return 0;
}

int isArrayMult10(int list[], int size) {

	int multiples10 = 0;

	for (int i = 0; i < size; i++) {
		// printf("%d ", list[i]);
		if (list[i] % 10 == 0) {
			multiples10++;
		}

	}

	// printf("\nThe number of multiples of 10 found: %d\n", multiples10);

	if ( multiples10 == 0 ) {
		return 0;
	}
	else if ( multiples10 == size ) {
		return 1;
	}
	else {
		return 2;
	}

}

