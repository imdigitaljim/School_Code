#include <stdio.h>

int main() {
	printf("Two int declarations/assignments\nand one declaration/addition/assignment:\n");
	int i = 1;
	int j = 2;
	int k = i + j;
	printf("Two ints %i and %i\n", i, j);
	printf("Result of simple addition: %i\n", k);
	printf("5 total printouts...\n");
	printf("6 total printouts...\n");
	printf("7 total printouts...\n");
	printf("and 10 system calls!\n");
	return 0;	
}
