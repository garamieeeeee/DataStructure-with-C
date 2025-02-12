#ifndef ARRAYSTACK_H
#define ARRAY_STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int ElementType;

typedef struct {
	ElementType stack[MAX_STACK_SIZE];
	int top;
}StackType;

void Error(char* message);
StackType* CreateStack();
int IsEmpty(StackType* s);
int IsFull(StackType* s);
void Push(StackType* s, ElementType data);
ElementType Pop(StackType* s);
ElementType Peek(StackType* s);
void DestroyStack(StackType** s);
int GetSize(StackType* s);
void PrintStack(StackType* s);

#endif
