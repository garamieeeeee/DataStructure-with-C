#ifndef LINKEDCIRCULARQUEUE_H
#define LINKEDCIRCULARQUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct CQueueNode { //C Queue: 원형 큐
	ElementType data;
	struct CQueueNode* link;
}CQueueNode;

typedef struct {
	CQueueNode* front;
	CQueueNode* rear;
}LinkedCQueueType; //연결된 원형큐

void Init(LinkedCQueueType* cq);
int IsEmpty(LinkedCQueueType* cq);
void Enqueue(LinkedCQueueType* cq, ElementType data);
ElementType Dequeue(LinkedCQueueType* cq);
ElementType Peek(LinkedCQueueType* cq);
void PrintQueue(LinkedCQueueType* cq);

#endif
