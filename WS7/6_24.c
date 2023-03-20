#include <stdio.h>

void SwapValues(int* v1, int* v2, int* v3, int* v4);

int main() {

	int val1, val2, val3, val4;

	scanf("%d %d %d %d", &val1, &val2, &val3, &val4);

	SwapValues(&val1, &val2, &val3, &val4);

	printf("%d %d %d %d\n", val1, val2, val3, val4);
	
	return 0;

}

void SwapValues(int* v1, int* v2, int* v3, int* v4) {
	
	int temp = *v1;

	*v1 = *v2;
	*v2 = temp;

	temp = *v3;
	*v3 = *v4;
	*v4 = temp;

}

