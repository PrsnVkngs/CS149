#include <stdio.h>

#define NAME_MAX 50

int main(){

	char name[NAME_MAX];
	fgets(name, NAME_MAX, stdin);

	printf("Hello %s, and welcome to CS Online!\n", name);

	return 0;

}
