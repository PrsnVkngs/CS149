#include <stdio.h>

int main() {

	int base10Num;
	scanf("%d", &base10Num);

	while ( base10Num != 0 ) {

		printf("%d", base10Num % 2);
		base10Num /= 2;

	}

	printf("\n");

	return 0;

}
