#ifndef GENERICSTACK_H
#define GENERICSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void* data;
	int elementSize;
}Node;

typedef struct {
	int capacity;
	int top;
	Node* nodes;
}StackType;

void CreateStack(StackType** s, int elementSize);
void DestroyStack(StackType** s);
void Push(StackType* s, void* data);
void* Pop(StackType* s);
void* Peek(StackType* s);
int IsFull(StackType* s);
int IsEmpty(StackType* s);

#endif
