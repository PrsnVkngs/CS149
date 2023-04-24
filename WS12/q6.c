/*
 * If we make an array of ints with malloc, then free it, we will get a random value because the memory at this address does not belong to us anymore and can have anything in it at this point.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

	int** nums = (int**)malloc( 100 * sizeof(int*));

	for(int i = 0; i < 100; i++) {
		nums[i] = (int*)malloc(sizeof(int));
	}

	for(int i = 0; i < 100; i++) {
		free(nums[i]);
	}
	free(nums);

	printf("Val at nums[2] = %d\n", *nums[2]);

	return 0;
}
