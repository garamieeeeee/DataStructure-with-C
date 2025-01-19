#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct StackNode {
	ElementType data;
	struct StackNode* link;
}StackNode;

typedef struct {
	StackNode* top;//연결리스트의 헤드 포인터 역할
}LinkedStackType;

void Init(LinkedStackType* s);
int IsEmpty(LinkedStackType* s);
void Push(LinkedStackType* s, ElementType data);
ElementType Pop(LinkedStackType* s);
ElementType Peek(LinkedStackType* s);
void PrintStack(LinkedStackType* s);

#endif
