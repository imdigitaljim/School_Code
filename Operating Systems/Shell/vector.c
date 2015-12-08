#ifndef VECTOR_C
#define VECTOR_C

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void buildVector(vector *v) {
	v->capacity = 4;
	v->currentNum = 0;
	v->data = malloc(sizeof(void *) * v->capacity);
}

void clearVector(vector *v) {
	v->currentNum = 0;
	v->capacity = 4;
	freeVector(v);
	v->data = malloc(sizeof(void *) * v->capacity);
}

void freeVector(vector *v) {
	free(v->data);
}

int vectorEmpty(vector *v) {
	if (v->data) {
		return 1;
	}
	return 0;
}

void deleteVectorIndex(vector *v, int index) {
	int loop = index;
	if(index >= 0 && index < v->currentNum) {
		while(loop > 0 && loop != v->currentNum - 1)
			v->data[loop] = v->data[++loop];
		v->currentNum--;
		if(v->currentNum > 0 && v->currentNum == v->capacity / 4)
			vectorResize(v, v->capacity / 2);
	}
}

void vectorPushBack(vector *v, void *data) {
	if (v->capacity == v->currentNum)
		vectorResize(v, v->capacity * 2);
	v->data[v->currentNum++] = data;
}

void vectorPopBack(vector *v) {
	if (v->currentNum > 0 && v->currentNum == v->capacity / 4)
	{
		vectorResize(v, v->capacity / 2);
		v->currentNum--;
	}
	else if(v->currentNum > 0)
		v->currentNum--;
}

void vectorSet(vector *v, void *data, int index) {
	if (index >= 0 && index < v->currentNum)
		v->data[index] = data;
	else if (index >= 0 && index == v->currentNum)
		vectorPushBack(v, data);
}

void* vectorGet(vector *v, int index) {
	if (index >= 0 && index < v->currentNum)
		return v->data[index];
	return NULL;
}

static void vectorResize(vector *v, int newCapacity) {
	void **data = realloc(v->data, sizeof(void *) * newCapacity);
	if (data) {
		v->data = data;
		v->capacity = newCapacity;
	}
}

void* vectorFront(vector *v) {
	return v->data[0];
}

void *vectorBack(vector *v) {
	return v->data[(vectorCurrentNum(v) - 1)];
}

int vectorCurrentNum(vector *v) {
	return v->currentNum;
}

int vectorCapacity(vector *v) {
	return v->capacity;
}

void vectorPrintPath(vector *v) {
	int i;
	printf(" ");
	for(i = 0; i < vectorCurrentNum(v); i++)
		printf("/%s", (char *) vectorGet(v, i));
	printf("=>");
}

int vectorFindData(vector *v, void *data) {
	int result, i;
	for(i = 0; i < vectorCurrentNum(v); i++) {
		if(strcmp(data, vectorGet(v, i)) == 0) {
			return i;
		}
	}
	return -1;
}

#endif
