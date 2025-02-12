#ifndef ARRAYCIRCULARQUEUE_H
#define ARRAYCIRCULARQUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int ElementType;

typedef struct {
	ElementType queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void Error(char* message);
QueueType* CreateQueue();
int IsEmpty(QueueType* q);
int IsFull(QueueType* q);
void Enqueue(QueueType* q, ElementType data);
ElementType Dequeue(QueueType* q);
ElementType Peek(QueueType* q);
void DestroyQueue(QueueType** q);
void PrintQueue(QueueType* q);

#endif
