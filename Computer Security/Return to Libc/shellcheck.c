#include <stdio.h>

int main(){
	printf("%x\n", (unsigned int)getenv("MYSHELL"));
	system(getenv("MYSHELL"));
	return 0;
}