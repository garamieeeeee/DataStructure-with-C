#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;

typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}DequeType;

void Error(char* message);
void InitDeque(DequeType* dq);
int IsEmpty(DequeType* dq);
int IsFull(DequeType* dq);
void PrintDequeue(DequeType* dq);
void AddRear(DequeType* dq, element data);
element DeleteFront(DequeType* dq);
element GetFront(DequeType* dq);
void AddFront(DequeType* dq, element data);
element DeleteRear(DequeType* dq);
element GetRear(DequeType* dq);

#endif
