#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector {
	void **data;
	int capacity;
	int currentNum;
} vector;

void buildVector(vector *v); /*Create an empty vector of size 4*/
void clearVector(vector *v); /*Restore a vector to default (empty, size 4)*/ 
void freeVector(vector *v);  /*Perform dynamic cleanup*/
int vectorEmpty(vector *v);  /*Test to see if vector is empty*/
void deleteVectorIndex(vector *v, int index); /*Deletes an index in vector*/

void vectorPushBack(vector *v, void *data);/*Add element to end of vector*/
void vectorPopBack(vector *v);             /*Remove element from end of vector*/
void vectorSet(vector *v, void *data, int index);/*Set a specific index to be a value*/
void* vectorGet(vector *v, int index);     /*Returns value and an index in vector*/
static void vectorResize(vector *v, int newCapacity);/*Resize the vector*/

void* vectorFront(vector *v); /*Returns the first value in the vector*/
void* vectorBack(vector *v);  /*Returns the last value in the vector*/
int vectorCurrentNum(vector *v);/*Returns the number of values in vector*/
int vectorCapacity(vector *v);/*Returns the capacity of the vector*/

void vectorPrintPath(vector *v); /*Prints vector contents in the form of a path*/
int vectorFindData(vector *v, void *data);/*Finds an instruction index, returns -1 if invalid*/

#endif
