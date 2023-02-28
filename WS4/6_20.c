#include <stdio.h>

double LapsToMiles(double laps) {

	return laps * 0.25;
}

int main() {

	double numLaps;

	scanf("%lf", &numLaps);

	double miles = LapsToMiles(numLaps);

	printf("%0.2lf\n", miles);

	return 0;

}
