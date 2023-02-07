#include <stdio.h>

int main() {
	int num1;
	int num2;
	char eol; // end of line place holder.
	printf("Enter integer:\n");

	scanf("%d", &num1);

	printf("You entered: %d\n", num1);

	printf("%d squared is %d\n", num1, (num1*num1) );
	printf("And %d cubed is %d\n", num1, (num1*num1*num1) );

	scanf("%c", &eol); // clear buffer of newlines
	printf("Enter another integer: \n");
	
	scanf("%d", &num2);

	printf("%d + %d is %d\n", num1, num2, (num1+num2) );
	printf("%d * %d is %d\n", num1, num2, (num1*num2) );

	return 0;

}
