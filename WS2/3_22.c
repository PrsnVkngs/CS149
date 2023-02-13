#include <stdio.h>

int main() {

	int n1, n2, n3;

	scanf("%d %d %d", &n1, &n2, &n3);

	int smallest = n1;

	if ( smallest > n2 ) {

		smallest = n2;
	}
	if ( smallest > n3 ) {
		smallest = n3;
	}

	printf("%d\n", smallest);

	return 0;
}

