#include <stdio.h>

int main() {

	int count;
	scanf("%d", &count);

	int numbers[count];

	for(int i = 0; i < count; i++) {

		scanf("%d", &numbers[i]);

	}

	int smallest, smaller;

	smallest = numbers[0]; // smallest number
	smaller = numbers[1]; // 2nd smallest number

	for (int n = 2; n < count; n++) {
		
		if (numbers[n] < smallest) {
			smaller = smallest;
			smallest = numbers[n];
		}
		else if (numbers[n] < smaller) {
			smaller = numbers[n];
		}

	}

	printf("%d and %d\n", smallest, smaller);

	return 0;

}
