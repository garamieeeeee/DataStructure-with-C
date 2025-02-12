#ifndef DYNAMICARRAYSTACK_H
#define DYNAMICARRAYSTACK_H 

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct {
	ElementType* stack;
	int capacity;
	int top;
}StackType;

void Error(char* message);
StackType* CreateStack(int capacity);
int IsEmpty(StackType* s);
int IsFull(StackType* s);
void Push(StackType* s, ElementType data);
ElementType Pop(StackType* s);
ElementType Peek(StackType* s);
void DestroyStack(StackType** s);
int GetSize(StackType* s);
void PrintStack(StackType* s);

#endif
