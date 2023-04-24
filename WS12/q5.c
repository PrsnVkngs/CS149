/*
 * The program in this case allocates memory for a bunch of integers, and it can hold values from nums[0] to nums[99].
 * However, when we try to access the value and set a value to something at nums[100], we run into some undefined behavior.
 * This is because there is a number of things that could happen when we execute the program.
 * 1. The most simple of them all is that nothing happens and the program simply overwrites whatever is at nums[100]. Keep in mind that nums[100] doesn't belong to nums.
 * 2. The program could also crash as the runtime environment detected that we tried to access a value out of bounds of the array.
 * 3. The compiler actually caught this problem at runtime, although this isn't guaranteed as it depends on how the code is and how the compiler works.
 * In our particular case, the program went through with compilation, but we got a segmentation fault.
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

	int** nums = (int**)malloc(sizeof(int**));
	for(int i = 0; i < 100; i++) {
		nums[i] = (int*)malloc(sizeof(int));
	}

	*nums[100] = 10;

	return 0;

}
