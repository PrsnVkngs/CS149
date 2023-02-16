#include <stdio.h>

int main() {

	int number_inputs;

	scanf("%d", &number_inputs);

	int numbers[number_inputs];
	
	for(int i = 0; i < number_inputs; i++ ) {

		scanf("%d", &numbers[i]);

	}
	
	int threshold;

	scanf("%d", &threshold);

	for(int i = 0; i < number_inputs; i++ ) {

		if ( numbers[i] <= threshold ) {
			printf("%d,", numbers[i]);
		}
	}

	return 0;
}	
