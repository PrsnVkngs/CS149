#include <stdio.h>

int main() {

	int userNum, x;
	scanf("%d %d", &userNum, &x);

	printf("%d %d %d\n", userNum/x, (userNum/x)/x, ((userNum/x)/x)/x);

	return 0;
}

