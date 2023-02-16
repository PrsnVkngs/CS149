#include <stdio.h>
#include <stdbool.h>

#define MAX_NUMS 9 

int main() {

	int nums[MAX_NUMS];

	int input, count = 0;

	bool max_cnt_violated = true;

	
	while ( count <= MAX_NUMS ) {

		count++;

		scanf("%d", &input);

		if (input < 0 ) {
			max_cnt_violated = false;
			break;
		}

		nums[count-1] = input;

	}
		
	printf("Middle item: %d\n", nums[(count-1)/2]);
	
	return 0;

}

