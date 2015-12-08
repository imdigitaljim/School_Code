#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main(void)
{
	int i;
	int g;
	g = 20;
	vector v;
	buildVector(&v);

	vectorPushBack(&v, &g);
	vectorPushBack(&v, &g);
	vectorPushBack(&v, &g);
	vectorPushBack(&v, &g);

	for (i = 0; i < vectorCurrentNum(&v); i++)
		printf("%d ", *((int*)  vectorGet(&v, i)));
	printf("\n");

	clearVector(&v);
   
	vectorSet(&v, "Greetings", 0);
	vectorPushBack(&v, "Planet");

	for (i = 0; i < vectorCurrentNum(&v); i++)
		printf("%s ", (char *) vectorGet(&v, i));
	printf("\n");

	clearVector(&v);
	vectorPushBack(&v, "~");
	vectorPushBack(&v, "COP3101");
	vectorPushBack(&v, "Project1");
	vectorPrintPath(&v);
	printf("%d\n", vectorFindData(&v, "Project1"));
	printf("%s\n", (char *) vectorFront(&v));
	printf("%s\n", (char *) vectorBack(&v));
	deleteVectorIndex(&v, 0);
	vectorPrintPath(&v);
	printf("\n");


	freeVector(&v);
}
