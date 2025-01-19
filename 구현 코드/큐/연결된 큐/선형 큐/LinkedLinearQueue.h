#ifndef  LINKEDLINEARQUEUE
#define LINKEDLINEARQUEUE

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct QueueNode {
	ElementType data;
	struct QueueNode* link;
}QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkedQueueType;

void Init(LinkedQueueType* q);
int IsEmpty(LinkedQueueType* q);
void Enqueue(LinkedQueueType* q, ElementType data);
ElementType Dequeue(LinkedQueueType* q);
ElementType Peek(LinkedQueueType* q);
void PrintQueue(LinkedQueueType* q);

#endif
