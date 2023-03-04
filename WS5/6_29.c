#include <stdio.h>
#include <string.h>
#include <math.h>


void IntToReverseBinary (int integerValue, char *binaryValue);
void StringReverse(char *inputString, char *reversedString);

int main() {

	int input;

	scanf("%d", &input);
	
	int length = (int) (ceil( (log10(input) / log10(2) ) )+1);

	char reverseBinary[length];

	IntToReverseBinary(input, reverseBinary);

	char normalBinary[length];
	StringReverse(normalBinary, reverseBinary);

	printf("%s\n", normalBinary); 

	return 0;

}

void StringReverse(char *inputString, char *reversedString) {

	int normalIndex = 0;
	for (int i = strlen(reversedString)-1; i >= 0; i-- ) {
		inputString[normalIndex++] = reversedString[i];
	}
	inputString[normalIndex] = '\0';
}



void IntToReverseBinary (int integerValue, char *binaryValue) {

	int index = 0;
	int result;

	while (integerValue > 0) {
		
		result = integerValue % 2;
		binaryValue[index++] = result == 0 ? '0' : '1';
		integerValue /= 2;

	}

	binaryValue[index] = '\0';

}
