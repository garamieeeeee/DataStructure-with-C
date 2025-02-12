#ifndef ARRAYCIRCULARDEQUE_H
#define ARRAYCIRCULARDEQUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int ElementType;

typedef struct {
	int front, rear;
	ElementType deque[MAX_QUEUE_SIZE];
}DequeType;

void Error(char* message);
DequeType* CreateDeque();
int IsEmpty(DequeType* dq);
int IsFull(DequeType* dq);
void PrintDequeue(DequeType* dq);
void AddRear(DequeType* dq, ElementType data);
ElementType DeleteFront(DequeType* dq);
ElementType GetFront(DequeType* dq);
void AddFront(DequeType* dq, ElementType data);
ElementType DeleteRear(DequeType* dq);
ElementType GetRear(DequeType* dq);
void DestroyDeque(DequeType** dq);

#endif
