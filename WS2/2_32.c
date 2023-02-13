#include <stdio.h>

int main() {

	int currMonth, lastMonth;

	scanf("%d %d", &currMonth, &lastMonth);

	printf("This house is $%d. The change is $%d since last month.\n",
	currMonth, currMonth - lastMonth);
	printf("The estimated monthly mortgage is $%0.2lf\n",
	(currMonth * 0.051 ) / 12.0);

	return 0;

}
