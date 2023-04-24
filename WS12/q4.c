/*
 * Both valgrind and gdb can be used to detect the memory leak that we will encounter in this situation.
 * The program will not encounter any issues at runtime, and will actually work just fine.
 * However, under the hood we are losing memory to the program, which the OS is not able to reclaim, so it has a big flaw that we cant' see. 
 * Comments & Answers
 */

#include <stdio.h>
#include <stdlib.h>

int main() {

	int* some_num = (int*)malloc(sizeof(int));
	printf("We allocated some memory the size of an int, but we forgot to free it!\n");

	return 0;

}
