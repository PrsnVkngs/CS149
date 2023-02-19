#include <stdio.h>

int main() {

	int count, low, high;

	scanf("%d", &count);

	int numbers[count];

	for(int i = 0; i < count; i++) {
		scanf("%d", &numbers[i]);
	}

	scanf("%d %d", &low, &high);

	for(int n = 0; n < count; n++) {

		if (numbers[n] >= low && numbers[n] <= high) {
			printf("%d,", numbers[n]);
		}

	}
	printf("\n");

	return 0;

}
