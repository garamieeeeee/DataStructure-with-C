#ifndef DYNAMICARRAYLINEARQUEUE_H
#define DYNAMICARRAYLINEARQUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct {
	ElementType* queue;
	int front, rear;
	int capacity;
}QueueType;

void Error(char* message);
QueueType* CreateQueue(int capacity);
int IsEmpty(QueueType* q);
int IsFull(QueueType* q);
void resizeQueue(QueueType* q);
void Enqueue(QueueType* q, ElementType data);
ElementType Dequeue(QueueType* q);
ElementType Peek(QueueType* q);
void DestroyQueue(QueueType** q);
void PrintQueue(QueueType* q);

#endif
