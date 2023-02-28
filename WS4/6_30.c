#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4) {

	int max = num1;

	if ( num2 > max ) {
		max = num2;
	}
	if ( num3 > max ) {
		max = num3;
	}
	if ( num4 > max ) {
		max = num4;
	}

	return max;

}

int MinNumber(int num1, int num2, int num3, int num4) {

	int min = num1;

	if ( num2 < min ) {
		min = num2;
	}
	if ( num3 < min ) {
		min = num3;
	}
	if ( num4 < min ) {
		min = num4;
	}

	return min;

}

int main() {

	int n1, n2, n3, n4;

	scanf("%d %d %d %d", &n1, &n2, &n3, &n4);

	int min = MinNumber(n1, n2, n3, n4);
	int max = MaxNumber(n1, n2, n3, n4);

	printf("Maximum is %d\n", max);
	printf("Minimum is %d\n", min);

	return 0;

}

