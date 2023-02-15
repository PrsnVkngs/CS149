#include <stdio.h>

int main() {

	int sum = 0, max = 0, cnt = -1, num = 0;

	while ( num >= 0 ) {

		cnt++;

		if ( num > max ) {
			max = num;
		}

		sum += num;

		scanf("%d", &num);

	}

	printf("%d %0.2lf\n", max, (double)sum/cnt);

	return 0;

}
